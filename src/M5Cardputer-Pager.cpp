#include "M5Cardputer.h"

#define bgColor 0x18E4
#define statusbarColor PURPLE
#define Display M5Cardputer.Display
int retroDelay = 10;
int screen = -1;
int menuSelection = 0;
bool menuForward = 0;
bool menuBackward = 0;
char* mainMenuItems[] = {"Settings", "About", "Exit"};
int mainMenuSize = 2;

float getBatteryVoltage() {
    float batteryADCValue = analogRead(G10) * 2.0f;
    float batteryVoltage = (batteryADCValue / 4095.0) * 3300.0; 
    return batteryVoltage;
}
void initMainMenu() {
    Display.setTextColor(WHITE, bgColor);
    Display.setCursor(0, 10);
    Display.setFont(&fonts::Font0);
    for (int i = 0; i <= mainMenuSize; i++) {
        Display.setCursor(0, 30 + (i * 15));
        Display.setTextColor(i == menuSelection ? GREEN : WHITE, bgColor);
        Display.print(i == menuSelection ? "> " : "  ");
        Display.println(mainMenuItems[i]);
    }
}

void buildInterface() {
    for (int h = 0; h < Display.height(); h += 5) {
        Display.fillRect(0, 0, Display.width(), h, bgColor);
        delay(retroDelay);
    }
    for (int h = 0; h > -20; h -= 4) {
        Display.fillRect(0, 135, Display.width(), h, statusbarColor);
        delay(retroDelay);
    }
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
    Display.println("Display resolution: " + String(Display.width()) + "x" + String(Display.height())+ "\n");
    delay(250);
    Display.println("Ready! \nPress ANY key to continue...\n");
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
void updateStatusBar() {
    showBatteryVoltage();
    showIPv4();
    
}
void handleKeyPress() {
    if (M5Cardputer.Keyboard.isChange()) {
        if(M5Cardputer.Keyboard.isKeyPressed('.')) {
            if(menuSelection < mainMenuSize) {
                menuSelection++;
            } else {
                menuSelection = 0;
            }
        } else if(M5Cardputer.Keyboard.isKeyPressed(';')) {
            if(menuSelection > 0) {
                menuSelection--;
            } else {
                menuSelection = mainMenuSize;
            }
        } else if(M5Cardputer.Keyboard.isKeyPressed('/')) {
            menuForward = 1;
            menuBackward = 0;
        } else if (M5Cardputer.Keyboard.isKeyPressed(',')) {
            menuForward = 0;
            menuBackward = 1;
        }
    }
}
void initSettingsMenu() {
    Display.setTextColor(WHITE, statusbarColor);
    Display.setCursor(100, 123);
    Display.print("Settings");
}
void handleScreens() {
    if(menuForward) {
        screen = menuSelection;
        menuForward = 0;
        buildInterface();
    } else if(menuBackward) {
        screen = -1;
        menuBackward = 0;
        buildInterface();
    } else if(screen == 0) {
        initSettingsMenu();
    } else if(screen == 1) {
        //initAbout();
    } else {
        initMainMenu();
    }
}
void loop()
{
    M5Cardputer.update();
    handleScreens();
    updateStatusBar();
    handleKeyPress();
    delay(30);
}