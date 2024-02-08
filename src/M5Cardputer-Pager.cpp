#include "M5Cardputer.h"

#define backgroundColor 0x18E4
#define statusbarColor PURPLE
#define Display M5Cardputer.Display
int retroDelay = 30;
float getBatteryVoltage() {
    float batteryADCValue = analogRead(G10) * 2.0f;
    float batteryVoltage = (batteryADCValue / 4095.0) * 3300.0; 
    return batteryVoltage;
}
void buildInterface() {
    for (int h = 0; h < Display.height(); h += 5)
    {
        Display.fillRect(0, 0, Display.width(), h, backgroundColor);
        delay(retroDelay);
    }
    for (int h = 0; h > -20; h -= 4)
    {
        Display.fillRect(0, 135, Display.width(), h, statusbarColor);
        delay(retroDelay);
    }
    Display.setTextColor(WHITE, statusbarColor);
    Display.setCursor(100, 123);
    Display.println("Pager");
}

void setup() {
    auto cfg = M5.config();
    M5Cardputer.begin(cfg);
    Display.setBrightness(50);
    Display.setRotation(1);
    Display.fillScreen(BLACK);
    Display.setTextColor(GREEN, BLACK);
    Display.setFont(&fonts::Font0);
    Display.setCursor(0, 10);
    Display.println("Starting up...\n");
    delay(500);
    Display.println("display resolution: " + String(Display.width()) + "x" + String(Display.height())+ "\n");
    delay(250);
    Display.println("Ready! Press ANY key to continue...\n");
    bool exitLoop = true;
    while (exitLoop)
    {
        M5Cardputer.update();
        if (M5Cardputer.Keyboard.isPressed())   exitLoop = false;
    }
    Display.clearDisplay();
    buildInterface();
}

void showBatteryVoltage() {
    float batteryVoltage = getBatteryVoltage();
    Display.setTextColor(GREEN, statusbarColor);
    Display.setCursor(200, 123);
    Display.print(batteryVoltage/1000);
    Display.print("v");
}
void showIPv4() {
    Display.setTextColor(GREEN, statusbarColor);
    Display.setCursor(10, 123);
    Display.println("10.0.0.148/24"); // fake ipv4, for now
}
void loop()
{
    M5Cardputer.update();
    showBatteryVoltage();
    showIPv4();
    delay(100);
}