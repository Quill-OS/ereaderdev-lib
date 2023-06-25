#include "devbattery.h"

int getBatteryLevel(device* dev) {
    QFile batteryFileDev;
    batteryFileDev.setFileName(dev->batterySysfs + "/capacity");
    if (!batteryFileDev.open(QIODevice::ReadOnly)) {
        return -1;
    }
    QString readed = batteryFileDev.readAll();
    batteryFileDev.close();
    return readed.toInt();
}
