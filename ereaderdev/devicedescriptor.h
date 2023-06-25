#ifndef DEVICEDESCRIPTOR_H
#define DEVICEDESCRIPTOR_H

// Needed
#include "ereaderdev_global.h"

// The namespace & dev* names are because it can't conflict with platform manager
// No other way to do it
namespace ereaderdev {
enum deviceName
{
    unknownName,
    KoboTouchAB,
    KoboTouchC,
    KoboMini,
    KoboGlo,
    KoboGloHD,
    KoboTouch2,
    KoboAura,
    KoboAuraHD,
    KoboAuraH2O,
    KoboAuraH2O2_v1,
    KoboAuraH2O2_v2,
    KoboAuraOne,
    KoboAura2,
    KoboAura2_v2,
    KoboClaraHD,
    KoboForma,
    KoboLibraH2O,
    KoboNia,
    KoboNia_a,
    KoboNia_c,
    KoboElipsa,
    KoboSage,
    KoboLibra2,
    KoboClara2E
};

// Add others :D
enum deviceModel
{
    unknownModel,
    n306,
    n306a,
    n306c,
};

enum deviceCodeName
{
    unknownCodeName,
    trilogy,
    pixie,
    kraken,
    alyssum,
    pika,
    phoenix,
    dragon,
    dahlia,
    snow,
    dayLight, // it's in time.h
    star,
    nova,
    frost,
    storm,
    europa,
    cadmus,
    io,
    goldFinch,
    luna,
};

struct devTouchscreenSettings
{
    bool swapXY = true;
    bool invertX = true;
    bool invertY = false;
    bool hasMultitouch = true;
};

struct devFrontlightSettings
{
    bool hasFrontLight = true;
    int frontlightMin = 0;
    int frontlightMax = 100;
    bool hasReadWhitefrontlight = false; // I'm not sure here
    bool hasNaturalLight = false;
    bool hasNaturalLightMixer = false;
    bool naturalLightInverted = false;
    int naturalLightMin = 0;
    int naturalLightMax = 100;

    QString frontlightDevWhiteRead = "/sys/class/backlight/mxc_msp430.0/actual_brightness";
    QString frontlightDevWhite = "/sys/class/backlight/mxc_msp430.0/brightness";
    QString frontlightDevMixer = "/sys/class/backlight/lm3630a_led/color";
    QString frontlightDevRed = "/sys/class/backlight/lm3630a_led1a";
    QString frontlightDevGreen = "/sys/class/backlight/lm3630a_ledb";
};


struct device
{
    deviceName name = unknownName;
    deviceModel model = unknownModel;
    deviceCodeName codeName = unknownCodeName;

    int modelNumber;
    int mark = 6;
    int dpi;
    int width;
    int height;
    qreal physicalWidth;
    qreal physicalHeight;

    // TODO: what is this
    bool hasKeys = false;
    bool canToggleChargingLED = false;

    // New devices *may* be REAGL-aware, but generally don't expect explicit REAGL requests, default to not.
    bool isREAGL = false;

    // Unused for now
    bool hasGSensor = false;

    devTouchscreenSettings touchscreenSettings;
    devFrontlightSettings frontlightSettings;

    // MXCFB_WAIT_FOR_UPDATE_COMPLETE ioctls are generally reliable
    bool hasReliableMxcWaitFor = true;
    // Sunxi devices require a completely different fb backend...
    bool isSunxi = false;

    // Standard sysfs path to the battery directory
    QString batterySysfs = "/sys/class/power_supply/mc13892_bat";
    // Stable path to the NTX input device
    QString ntxDev = "/dev/input/event0";
    // Stable path to the Touch input device
    QString touchDev = "/dev/input/event1";
    // Stable path to the Power Button input device
    QString powerDev = "null";
};

device determineDevice();
QString logDevice(device* dev);
}


#endif // DEVICEDESCRIPTOR_H
