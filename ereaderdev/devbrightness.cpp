#include "devbrightness.h"

void setWhiteBrightness(device* dev, int value) {
    int device = -1;
    if ((device = open("/dev/ntx_io", O_RDWR)) < 0) {
        QFile brightnessFileDev;
        brightnessFileDev.setFileName(dev->frontlightSettings.frontlightDevWhite);
        if (!brightnessFileDev.open(QIODevice::ReadWrite)) {
            return void();
        }
        QDataStream out(&brightnessFileDev);
        out << value;
        brightnessFileDev.close();
    }
    else {
        ioctl(device, 241, value);
        close(device);
    }
}

int getWhiteBrightness(device* dev) {
    if(dev->frontlightSettings.hasReadWhitefrontlight == true) {
        QFile brightnessFileDev;
        brightnessFileDev.setFileName(dev->frontlightSettings.frontlightDevWhiteRead);
        if (!brightnessFileDev.open(QIODevice::ReadOnly)) {
            return -1;
        }
        // TODO: add below and above checks
        QString readed = brightnessFileDev.readAll().trimmed();
        brightnessFileDev.close();
        return readed.toInt();
    }
    return -1;
}
