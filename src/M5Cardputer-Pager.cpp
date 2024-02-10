#include "M5Cardputer.h"
#include "MenuFunctions.h"
#include "StatusBar.h"
#define Display M5Cardputer.Display

int retroDelay = 10;
void buildInterface(int time)
{
    for (int h = 0; h < Display.height(); h += 5)
    {
        Display.fillRect(0, 0, Display.width(), h, 0x18E4);
        delay(time);
    }
    for (int h = 0; h > -20; h -= 4)
    {
        Display.fillRect(0, 135, Display.width(), h, PURPLE);
        delay(time);
    }
}

void setup()
{
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
    Display.println("Display resolution: " + String(Display.width()) + "x" + String(Display.height()) + "\n");
    delay(250);
    Display.println("Display brightness: " + String(Display.getBrightness()) + "\n");
    delay(250);
    Display.println("Ready! \nPress ANY key to continue...\n");
    bool exitLoop = true;
    while (exitLoop)
    {
        M5Cardputer.update();
        if (M5Cardputer.Keyboard.isPressed())
            exitLoop = false;
    }
    Display.clearDisplay();
    buildInterface(retroDelay);
}

void loop()
{
    M5Cardputer.update();
    MenuFunctions::handleNavigation();
    if(MenuFunctions::handleConfirm()) {
        buildInterface(0);
    }
    MenuFunctions::handleScreens();
    StatusBar::update();
    delay(30);
}