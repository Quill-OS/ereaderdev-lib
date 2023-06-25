#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H

#include "ereaderdev_global.h"
#include "devicedescriptor.h"

using namespace ereaderdev;

void setWhiteBrightness(device* dev, int value);
int getWhiteBrightness(device* dev);

#endif // BRIGHTNESS_H
