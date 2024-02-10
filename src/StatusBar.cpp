#include "StatusBar.h"
#define Display M5Cardputer.Display
namespace StatusBar
{

    float getBatteryVoltage()
    {
        float batteryADCValue = analogRead(G10) * 2.0f;
        float batteryVoltage = (batteryADCValue / 4095.0) * 3300.0;
        return batteryVoltage;
    }
    void showBatteryVoltage()
    {
        float batteryVoltage = getBatteryVoltage();
        Display.setTextColor(GREEN, PURPLE);
        Display.setCursor(200, 123);
        Display.print(batteryVoltage / 1000);
        Display.print("v");
    }
    void showIPv4()
    {
        Display.setTextColor(GREEN, PURPLE);
        Display.setCursor(10, 123);
        Display.println("10.0.0.148/24"); // fake ipv4, for now
    }
    void update()
    {
        showBatteryVoltage();
        showIPv4();
    }

}