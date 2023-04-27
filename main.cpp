#include "header.hpp"

int main() {

    // Console settings
    SetWindowSize(120, 30);
    SetScreenBufferSize(120, 30);
    DisableResizeWindow();
    DisableCtrlButton(false, true, false);
    DisableSelection();
    ShowCur(false);
    SetConsoleTitle(TEXT("Where's The Link"));

    // Game
    int option = 0;

    while (true) {

        switch (option) {

            // Menu
            case 0:
                MenuController(option);
                break;

            // Auth
            case 1:
                AuthController(option);
                break;

            // Game play
            case 2:
                LevelController(option);
                break;

            // Quit
            case 3:
                return 0;
        }
    }
}