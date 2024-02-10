#include "MenuFunctions.h"
#define Display M5Cardputer.Display
namespace MenuFunctions
{
    char *mainMenuItems[] = {"Settings", "About", "Exit"};
    int mainMenuSize = 2;
    char *settingsMenuItems[] = {"Back", "Wi-Fi", "Bluetooth", "Interface"};
    int settingsMenuSize = 3;
    int screen = -1;
    int menuSelection = 0;
    bool confirm = 0;
    void initMainMenu()
    {
        Display.setTextColor(WHITE, 0x18E4);
        Display.setCursor(0, 10);
        Display.setFont(&fonts::Font0);
        for (int i = 0; i <= mainMenuSize; i++)
        {
            Display.setCursor(0, 30 + (i * 15));
            Display.setTextColor(i == menuSelection ? GREEN : WHITE, 0x18E4);
            Display.print(i == menuSelection ? "> " : "  ");
            Display.println(mainMenuItems[i]);
        }
    }
    void initSettingsMenu()
    {
        Display.setTextColor(WHITE, 0x18E4);
        Display.setFont(&fonts::Font0);
        for (int i = 0; i <= settingsMenuSize; i++)
        {
            Display.setCursor(0, 30 + (i * 15));
            Display.setTextColor(i == menuSelection ? GREEN : WHITE, 0x18E4);
            Display.print(i == menuSelection ? "> " : "  ");
            Display.println(settingsMenuItems[i]);
        }
    }
    /**
     * Lida com a navegação do menu
     */
    void handleNavigation()
    {
        if (M5Cardputer.Keyboard.isChange())
        {
            if (M5Cardputer.Keyboard.isKeyPressed('.'))
            {
                if (menuSelection < mainMenuSize)
                    menuSelection++;
                else
                    menuSelection = 0;
            }
            else if (M5Cardputer.Keyboard.isKeyPressed(';'))
            {
                if (menuSelection > 0)
                    menuSelection--;
                else
                    menuSelection = mainMenuSize;
            }
            else if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER))
            {
                confirm = true;
            }
        }
    }

    /**
     * Lida com a tecla de confirmação ENTER
     */
    int handleConfirm()
    {
        if (confirm)
        {
            screen = menuSelection;
            confirm = false;
            menuSelection = 0;
            return 1;
        }
        return 0;
    }

    /**
     * Lida com a exibição de telas a partir do menu principal
     */
    void handleScreens()
    {
        if (screen == 0)
            initSettingsMenu();
        else if (screen == 1)
        {
            // initAbout();
        }
        else
            initMainMenu();
    }
}
