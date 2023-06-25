QT -= gui

TEMPLATE = lib
DEFINES += EREADERDEV_LIBRARY

CONFIG += c++17

QMAKE_CXXFLAGS += -Wno-missing-field-initializers

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    devbattery.cpp \
    devbrightness.cpp \
    devicedescriptor.cpp \
    generalfunctions.cpp

HEADERS += \
    devbattery.h \
    devbrightness.h \
    devicedescriptor.h \
    ereaderdev_global.h \
    generalfunctions.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DESTDIR = build/
OBJECTS_DIR = build/.obj
MOC_DIR = build/.moc
RCC_DIR = build/.rcc
UI_DIR = build/.ui
