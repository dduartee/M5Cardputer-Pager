#ifndef STATUSBAR_FUNCTION_H
#define STATUSBAR_FUNCTION_H
#include "M5Cardputer.h"

namespace StatusBar
{

        float getBatteryVoltage();
        void showBatteryVoltage();
        void showIPv4();
        void update();
}

#endif