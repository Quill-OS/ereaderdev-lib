#include "devbrightness.h"
#include "generalfunctions.h"

#include <QDebug>
#include <QProcess>

// Don't touch this. ever.
void setWhiteBrightness(device* dev, int value) {
    qDebug() << "Setting brightness in libreaderdev";
    int device = -1;
    if ((device = open("/dev/ntx_io", O_RDWR)) < 0) {
        QFile brightnessFileDev(dev->frontlightSettings.frontlightDevWhite);
        qDebug() << "Opening brightness sys device" << dev->frontlightSettings.frontlightDevWhite;
        if (brightnessFileDev.open(QIODevice::WriteOnly | QIODevice::Text) == false) {
            qDebug() << "Failed to open brightness sys device";
        } else {
            qDebug() << "Opened file";
        }

        QTextStream out(&brightnessFileDev);
        out << value;
        brightnessFileDev.close();
        qDebug() << "Writed the stream";

        bool error = false;
        if (out.status() != QDataStream::Ok) {
            error = true;
            qDebug() << "Error writing to file. Status: " << out.status();
        }

        int brghTmp = getWhiteBrightness(dev);
        qDebug() << "brghTmp check:" << brghTmp;
        if(brghTmp != value) {
            error = true;
            qDebug() << "Get brightness check failed";
        }

        if(error == true) {
            qDebug() << "Executing fallback echo...";
            {
                QString command = "/system-bin/echo " + QString::number(value) + " > " + dev->frontlightSettings.frontlightDevWhite;
                qDebug() << "Executing:" << command;
                execShell(command.toStdString().c_str());
            }
            {
                QString command = "/bin/echo " + QString::number(value) + " > " + dev->frontlightSettings.frontlightDevWhite;
                qDebug() << "Executing:" << command;
                execShell(command.toStdString().c_str());
            }

            int brghTmp = getWhiteBrightness(dev);
            qDebug() << "2 brghTmp check:" << brghTmp;
            if(brghTmp != value) {
                qDebug() << "Get brightness check failed even after echo";
                QProcess process;

                QStringList arguments;
                arguments << QString::number(value) << ">" << dev->frontlightSettings.frontlightDevWhite;
                process.start("/system-bin/echo", arguments);

                if (!process.waitForFinished()) {
                    qDebug() << "Failed to execute the echo command - second try";
                } else {
                    qDebug() << "Process finished:" << process.exitCode() << process.arguments();
                }
            }
        }
    }
    else {
        qDebug() << "Setting brightness via ioctl";
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
