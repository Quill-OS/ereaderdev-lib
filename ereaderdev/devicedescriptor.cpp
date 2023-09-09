#include "devicedescriptor.h"

#include "generalfunctions.h"
#include <QDebug>

#include <linux/fb.h>

namespace ereaderdev {

// Unknown
device KoboUnknown = {
    .name = unknownName,
    .model = unknownModel,
    .codeName = unknownCodeName,
    .mark = 4,
    .dpi = 200,
    .hasKeys = true,
    .touchscreenSettings = {.swapXY = false, .hasMultitouch = false},
    .frontlightSettings = {.hasFrontLight = false},
};

// Kobo Touch A/B:
device KoboTrilogyAB = {
    .name = KoboTouchAB,
    .model = unknownModel,
    .codeName = trilogy,
    .mark = 3,
    .dpi = 200,
    .hasKeys = true,
    .touchscreenSettings = {.swapXY = false, .hasMultitouch = false},
    .frontlightSettings = {.hasFrontLight = false},
};

// Kobo Touch C:
device KoboTrilogyC = {
    .name = KoboTouchC,
    .model = unknownModel,
    .codeName = trilogy,
    .mark = 4,
    .dpi = 200,
    .hasKeys = true,
    .touchscreenSettings = {.swapXY = false, .hasMultitouch = false},
    .frontlightSettings = {.hasFrontLight = false},
};

// Kobo Mini:
device KoboPixie = {
    .name = KoboMini,
    .model = unknownModel,
    .codeName = pixie,
    .mark = 4,
    .dpi = 200,
    .touchscreenSettings = {.hasMultitouch = false},
    .frontlightSettings = {.hasFrontLight = false},
};

// Kobo Glo:
device KoboKraken = {
    .name = KoboGlo,
    .model = unknownModel,
    .codeName = kraken,
    .mark = 4,
    .dpi = 212,
    .touchscreenSettings = {.hasMultitouch = false},
};

// Kobo Glo HD:
device KoboAlyssum = {
    .name = KoboGloHD,
    .model = unknownModel,
    .codeName = alyssum,
    .mark = 6,
    .dpi = 300,
};

// Kobo Touch 2.0:
device KoboPika = {
    .name = KoboTouch2,
    .model = unknownModel,
    .codeName = pika,
    .mark = 6,
    .dpi = 167,
    .frontlightSettings = {.hasFrontLight = false},

};

// Kobo Aura:
device KoboPhoenix = {
    .name = KoboAura,
    .model = unknownModel,
    .codeName = phoenix,
    .mark = 5,
    .dpi = 212,
    // NOTE: AFAICT, the Aura was the only one explicitly requiring REAGL requests...
    .isREAGL = true,
};

// Kobo Aura HD:
device KoboDragon = {
    .name = KoboAuraHD,
    .model = unknownModel,
    .codeName = dragon,
    .mark = 4,
    .dpi = 265,
    .touchscreenSettings = {.hasMultitouch = false},
};

// Kobo Aura H2O:
device KoboDahlia = {
    .name = KoboAuraH2O,
    .model = unknownModel,
    .codeName = dahlia,
    .mark = 5,
    .dpi = 265,
};

// Kobo Aura H2O2:
device KoboSnow = {
    .name = KoboAuraH2O2_v1,
    .model = unknownModel,
    .codeName = snow,
    .mark = 6,
    .dpi = 265,
    .touchscreenSettings = {.invertX = false},
    .frontlightSettings =
    {
        .hasNaturalLight = true,
        .frontlightDevWhite = "/sys/class/backlight/lm3630a_ledb",
        .frontlightDevRed = "/sys/class/backlight/lm3630a_led",
        .frontlightDevGreen = "/sys/class/backlight/lm3630a_leda",
    },
};

// Kobo Aura H2O2, Rev2:
//- @fixme Check if the Clara fix actually helps here... (#4015)
device KoboSnowRev2 = {
    .name = KoboAuraH2O2_v2,
    .model = unknownModel,
    .codeName = snow,
    .mark = 7,
    .dpi = 265,
    .frontlightSettings =
    {
        .hasNaturalLight = true,
        .frontlightDevWhite = "/sys/class/backlight/lm3630a_ledb",
        .frontlightDevRed = "/sys/class/backlight/lm3630a_leda",
    },
};

// Kobo Aura One:
device KoboDaylight = {
    .name = KoboAuraOne,
    .model = unknownModel,
    .codeName = dayLight,
    .mark = 6,
    .dpi = 300,
    .frontlightSettings = {.hasNaturalLight = true,
                           .frontlightDevWhite = "/sys/class/backlight/lm3630a_led1b",
                           .frontlightDevRed = "/sys/class/backlight/lm3630a_led1a",
                           .frontlightDevGreen = "/sys/class/backlight/lm3630a_ledb"},
    };

// Kobo Aura second edition:
device KoboStar = {
    .name = KoboAura2,
    .model = unknownModel,
    .codeName = star,
    .mark = 6,
    .dpi = 212,
};

// Kobo Aura second edition, Rev 2:
device KoboStarRev2 = {
    .name = KoboAura2_v2,
    .model = unknownModel,
    .codeName = star,
    .mark = 7,
    .dpi = 212,
};

// Kobo Clara HD:
device KoboNova = {
    .name = KoboClaraHD,
    .model = unknownModel,
    .codeName = nova,
    .mark = 7,
    .dpi = 300,
    .canToggleChargingLED = true,
    .frontlightSettings =
    {
        .hasNaturalLight = true,
        .hasNaturalLightMixer = true,
        .naturalLightInverted = true,
        .naturalLightMin = 0,
        .naturalLightMax = 10,
        .frontlightDevWhite = "/sys/class/backlight/mxc_msp430.0/brightness",
        .frontlightDevMixer = "/sys/class/backlight/lm3630a_led/color",
    },
};

// Kobo Forma:
// NOTE: Right now, we enforce Portrait orientation on startup to avoid getting touch coordinates wrong,
//       no matter the rotation we were started from (c.f., platform/kobo/koreader.sh).
// NOTE: For the FL, assume brightness is WO, and actual_brightness is RO!
//       i.e., we could have a real KoboPowerD:frontlightIntensityHW() by reading actual_brightness ;).
// NOTE: Rotation events *may* not be enabled if Nickel has never been brought up in that power cycle.
//       i.e., this will affect KSM users.
//       c.f., https://github.com/koreader/koreader/pull/4414#issuecomment-449652335
//       There's also a CM_ROTARY_ENABLE command, but which seems to do as much nothing as the STATUS one...
device KoboFrost = {
    .name = KoboForma,
    .model = unknownModel,
    .codeName = frost,
    .mark = 7,
    .dpi = 300,
    .hasKeys = true,
    .canToggleChargingLED = true,
    .hasGSensor = true,
    .frontlightSettings =
    {
        .hasNaturalLight = true,
        .hasNaturalLightMixer = true,
        // Warmth goes from 0 to 10 on the .name's side (our own internal scale is still normalized
        // to [0...100]) NOTE: Those three extra keys are *MANDATORY* if .frontlightDevMixer is set!
        .naturalLightInverted = true,
        .naturalLightMin = 0,
        .naturalLightMax = 10,
        .frontlightDevWhite = "/sys/class/backlight/mxc_msp430.0/brightness",
        .frontlightDevMixer = "/sys/class/backlight/tlc5947_bl/color",
    },
};

// Kobo Libra:
// NOTE: Assume the same quirks as the Forma apply.
device KoboStorm = {
    .name = KoboLibraH2O,
    .model = unknownModel,
    .codeName = storm,
    .mark = 7,
    .dpi = 300,
    .hasKeys = true,
    .canToggleChargingLED = true,
    .hasGSensor = true,
    .frontlightSettings =
    {
        .hasNaturalLight = true,
        .hasNaturalLightMixer = true,
        .naturalLightInverted = true,
        .naturalLightMin = 0,
        .naturalLightMax = 10,
        .frontlightDevWhite = "/sys/class/backlight/mxc_msp430.0/brightness",
        .frontlightDevMixer = "/sys/class/backlight/lm3630a_led/color",
    },
    // NOTE: The Libra apparently suffers from a mysterious issue where completely innocuous
    // WAIT_FOR_UPDATE_COMPLETE ioctls
    //       will mysteriously fail with a timeout (5s)...
    //       This obviously leads to *terrible* user experience, so, until more is understood avout the
    //       issue, bypass this ioctl on this .name. c.f.,
    //       https://github.com/koreader/koreader/issues/7340
    .hasReliableMxcWaitFor = false,
};

// Kobo Nia:
device KoboLuna = {
    .name = KoboNia,
    .model = n306,
    .codeName = luna,
    .mark = 7,
    .dpi = 212,
    .canToggleChargingLED = true,
    .frontlightSettings =
    {
        .hasReadWhitefrontlight = true,
        .frontlightDevWhiteRead = "/sys/class/backlight/mxc_msp430.0/actual_brightness",
        .frontlightDevWhite = "/sys/class/backlight/mxc_msp430.0/brightness"
    },
};

// Kobo Elipsa
device KoboEuropa = {
    .name = KoboElipsa,
    .model = unknownModel,
    .codeName = europa,
    .mark = 8,
    .dpi = 227,
    .canToggleChargingLED = true,
    .hasGSensor = true,
    .isSunxi = true,
    .batterySysfs = "/sys/class/power_supply/battery",
    .ntxDev = "/dev/input/by-path/platform-ntx_event0-event",
    .touchDev = "/dev/input/by-path/platform-0-0010-event",
};

// Kobo Sage
device KoboCadmus = {
    .name = KoboSage,
    .model = unknownModel,
    .codeName = cadmus,
    .mark = 8,
    .dpi = 300,
    .canToggleChargingLED = true,
    .hasGSensor = true,
    .frontlightSettings =
    {
        .hasNaturalLight = true,
        .hasNaturalLightMixer = true,
        .naturalLightInverted = false,
        .naturalLightMin = 0,
        .naturalLightMax = 10,
        .frontlightDevWhite = "/sys/class/backlight/mxc_msp430.0/brightness",
        .frontlightDevMixer = "/sys/class/leds/aw99703-bl_FL1/color",
    },
    .isSunxi = true,
    .batterySysfs = "/sys/class/power_supply/battery",
    .ntxDev = "/dev/input/by-path/platform-ntx_event0-event",
    .touchDev = "/dev/input/by-path/platform-0-0010-event",
};

// Kobo Libra 2
device KoboIo = {
    .name = KoboLibra2,
    .model = unknownModel,
    .codeName = io,
    .mark = 7,
    .dpi = 300,
    .canToggleChargingLED = true,
    .hasGSensor = true,
    .touchscreenSettings = {.invertX = false},
    .frontlightSettings =
    {
        .hasNaturalLight = true,
        .hasNaturalLightMixer = true,
        .naturalLightInverted = true,
        .naturalLightMin = 0,
        .naturalLightMax = 10,
        .frontlightDevWhite = "/sys/class/backlight/mxc_msp430.0/brightness",
        .frontlightDevMixer = "/sys/class/leds/aw99703-bl_FL1/color",
    },
    .batterySysfs = "/sys/class/power_supply/battery",
};

// Kobo Clara 2E
device KoboGoldfinch = {
    .name = KoboClara2E,
    .model = unknownModel,
    .codeName = goldFinch,
    .mark = 7,
    .dpi = 300,
    .canToggleChargingLED = true,
    .hasGSensor = true,
    .frontlightSettings =
    {
        .hasNaturalLight = true,
        .hasNaturalLightMixer = true,
        .naturalLightInverted = true,
        .naturalLightMin = 0,
        .naturalLightMax = 10,
        .frontlightDevWhite = "/sys/class/backlight/mxc_msp430.0/brightness",
        .frontlightDevMixer = "/sys/class/leds/aw99703-bl_FL1/color",
    },
    .batterySysfs = "/sys/class/power_supply/battery",
    .powerDev = "/dev/input/by-path/platform-bd71828-pwrkey-event",
};

static QRect determineGeometry(const fb_var_screeninfo &vinfo)
{
    int xoff = vinfo.xoffset;
    int yoff = vinfo.yoffset;
    int w = vinfo.xres;
    int h = vinfo.yres;
    return QRect(xoff, yoff, w, h);
}

static QSizeF determinePhysicalSize(const fb_var_screeninfo &vinfo, const QSize &res, int dpi = 300)
{
    int mmWidth = 0, mmHeight = 0;

    if (vinfo.width != 0 && vinfo.height != 0 && vinfo.width != UINT_MAX && vinfo.height != UINT_MAX)
    {
        mmWidth = vinfo.width;
        mmHeight = vinfo.height;
    }
    else
    {
        mmWidth = qRound(res.width() * 25.4 / dpi);
        mmHeight = qRound(res.height() * 25.4 / dpi);
    }

    return QSize(mmWidth, mmHeight);
}

device determineDevice()
{
    QString deviceName;
    if(QFile("/bin/kobo_config.sh").exists() == false) {
        qDebug() << "No /bin/kobo_config.sh script, trying DEVICE_CODENAME variable";
        deviceName = QString::fromLocal8Bit(qgetenv("DEVICE_CODENAME"));
    } else {
        deviceName = execShell("/bin/kobo_config.sh 2>/dev/null");
    }
    auto modelNumberStr = execShell("cut -f 6 -d ',' /mnt/onboard/.kobo/version | sed -e 's/^[0-]*//'");
    int modelNumber = modelNumberStr.toInt();

    device device;
    if (deviceName == "trilogy")
    {
        if (modelNumber == 310)
            device = KoboTrilogyAB;
        else  // if (modelNumber == 320)
            device = KoboTrilogyC; // I Hope this works and it's not the else at the end
    }
    else if (deviceName == "pixie")
    {
        device = KoboPixie;
    }
    else if (deviceName == "kraken")
    {
        device = KoboKraken;
    }
    else if (deviceName == "alyssum")
    {
        device = KoboAlyssum;
    }
    else if (deviceName == "pika")
    {
        device = KoboPika;
    }
    else if (deviceName == "phoenix")
    {
        device = KoboPhoenix;
    }
    else if (deviceName == "dragon")
    {
        device = KoboDragon;
    }
    else if (deviceName == "dahlia")
    {
        device = KoboDahlia;
    }
    else if (deviceName == "snow")
    {
        if (modelNumber == 374)
            device = KoboSnow;
        else  // if (modelNumber == 378)
            device = KoboSnowRev2;
    }
    else if (deviceName == "daylight")
    {
        device = KoboDaylight;
    }
    else if (deviceName == "star")
    {
        if (modelNumber == 375)
            device = KoboStar;
        else  // if (modelNumber == 379)
            device = KoboStarRev2;
    }
    else if (deviceName == "nova")
    {
        device = KoboNova;
    }
    else if (deviceName == "frost")
    {
        device = KoboFrost;
    }
    else if (deviceName == "storm")
    {
        device = KoboStorm;
    }
    else if (deviceName == "luna")
    {
        device = KoboLuna;
    }
    else if (deviceName == "europa")
    {
        device = KoboEuropa;
    }
    else if (deviceName == "cadmus")
    {
        device = KoboCadmus;
    }
    else if (deviceName == "io")
    {
        device = KoboIo;
    }
    else if (deviceName == "goldfinch")
    {
        device = KoboGoldfinch;
    }
    else
    {
        device = KoboUnknown;
    }

    QString fbDevice = QLatin1String("/dev/fb0");
    if (!QFile::exists(fbDevice))
        fbDevice = QLatin1String("/dev/graphics/fb0");
    if (!QFile::exists(fbDevice))
    {
        qWarning("Unable to figure out framebuffer device");
    }

    int mFbFd = -1;
    if (access(fbDevice.toLatin1().constData(), R_OK | W_OK) == 0) {
        mFbFd = open(fbDevice.toLatin1().constData(), O_RDWR);
    }

    if (mFbFd == -1)
    {
        if (access(fbDevice.toLatin1().constData(), R_OK) == 0) {
            mFbFd = open(fbDevice.toLatin1().constData(), O_RDONLY);
        }
    }

    // Open the device
    if (mFbFd == -1)
    {
        qErrnoWarning(errno, "Failed to open framebuffer %s", qPrintable(fbDevice));
    }

    fb_var_screeninfo vinfo;

    if (ioctl(mFbFd, FBIOGET_VSCREENINFO, &vinfo))
    {
        qErrnoWarning(errno, "Error reading variable information");
    }

    QRect geometry = determineGeometry(vinfo);

    auto mPhysicalSize = determinePhysicalSize(vinfo, geometry.size(), device.dpi);

    device.width = geometry.width();
    device.height = geometry.height();
    device.physicalWidth = mPhysicalSize.width();
    device.physicalHeight = mPhysicalSize.height();

    device.modelNumber = modelNumber;

    close(mFbFd);

    return device;
}

// Q_Enum and friends don't work
// Should be used only in logs, not in if else statements
QString logDevice(device* deviceToLog) {
    switch (deviceToLog->name)
    {
        case unknownName: return "unknownName";
        case KoboTouchAB: return "KoboTouchAB";
        case KoboTouchC: return "KoboTouchC";
        case KoboMini: return "KoboMini";
        case KoboGlo: return "KoboGlo";
        case KoboGloHD: return "KoboGloHD";
        case KoboTouch2: return "KoboTouch2";
        case KoboAura: return "KoboAura";
        case KoboAuraHD: return "KoboAuraHD";
        case KoboAuraH2O: return "KoboAuraH2O";
        case KoboAuraH2O2_v1: return "KoboAuraH2O2_v1";
        case KoboAuraH2O2_v2: return "KoboAuraH2O2_v2";
        case KoboAuraOne: return "KoboAuraOne";
        case KoboAura2: return "KoboAura2";
        case KoboAura2_v2: return "KoboAura2_v2";
        case KoboClaraHD: return "KoboClaraHD";
        case KoboForma: return "KoboForma";
        case KoboLibraH2O: return "KoboLibraH2O";
        case KoboNia: return "KoboNia";
        case KoboNia_a: return "KoboNia_a";
        case KoboNia_c: return "KoboNia_c";
        case KoboElipsa: return "KoboElipsa";
        case KoboSage: return "KoboSage";
        case KoboLibra2: return "KoboLibra2";
        case KoboClara2E: return "KoboClara2E";
    }
    return "unknownName";
}
}
