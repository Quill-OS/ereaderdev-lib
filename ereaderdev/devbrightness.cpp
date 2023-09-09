#include "devbrightness.h"
#include "generalfunctions.h"

#include <QDebug>
#include <QProcess>

void setWhiteBrightness(device* dev, int value) {
    qDebug() << "setWhiteBrightness new impl called with value" << value;
    int device = -1;
    if ((device = open("/dev/ntx_io", O_RDWR)) < 0) {
        qDebug() << "Using sys file system to set brightness";
        QFile file(dev->frontlightSettings.frontlightDevWhite);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            stream << value;
            file.close();
        }
        else {
            qDebug() << "Failed to set brightness";
        }
    }
    else {
        qDebug() << "Using NTX ioctl to set brightness";
        ioctl(device, 241, value);
        close(device);
    }
}

int getWhiteBrightness(device* dev) {
    if(dev->frontlightSettings.hasReadWhitefrontlight == true) {
        QFile brightnessFileDev(dev->frontlightSettings.frontlightDevWhiteRead);
        if (!brightnessFileDev.open(QIODevice::ReadOnly)) {
            return -1;
        }
        // TODO: add below and above checks
        QString readed = brightnessFileDev.readAll().trimmed();
        qDebug() << "Readed brightness" << readed;
        brightnessFileDev.close();
        return readed.toInt();
    }
    return -1;
}
