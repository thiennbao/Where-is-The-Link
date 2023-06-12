
void displayLevelMenu(string &page, int &level, int playerLevel) {

    drawLogo();
    GoTo(xStart, yStart - 3);
    cout << "LEVEL";
    string options[4] = {"LEVEL 1", "LEVEL 2", "LEVEL 3", "LEVEL 4"};

    int option = 0;
    while (true) {
        
        // Page
        for (int i=0; i<4; i++) {
            GoTo(xStart, yStart + 2*i);
            if (i == option) {
                cout << ">> " + options[i];
            } else {
                cout << "   " + options[i];
                if (i > playerLevel) {
                    cout << " LOCKED";
                }
            }
        }

        // Move
        char ch = getch();
        if (ch == keyUp || ch == 'w') {
            // Up
            option = (option == 0) ? playerLevel : option - 1;
        } else if (ch == keyDown || ch == 's') {
            // Down
            option = (option == playerLevel) ? 0 : option + 1;
        } else if (ch == keyRight || ch == 'd' || ch == ' ' || ch == keyEnter) {
            // Next
            level = option;
            page = "play";
            break;
        } else if (ch == keyLeft || ch == 'a' || ch == keyEsc) {
            // Back
            page = "menu";
            break;
        }
    }
}

void displayPauseScreen(bool &isQuit) {

    drawLogo();
    GoTo(xStart, yStart - 3);
    cout << "PAUSE";
    string options[2] = {"CONTINUE", "SAVE AND QUIT"};

    int option = 0;
    while (true) {

        // Page
        for (int i=0; i<2; i++) {
            GoTo(xStart, yStart + 2*i);
            if (i == option) {
                cout << ">> " + options[i];
            } else {
                cout << "   " + options[i];
            }
        }

        // Move
        char ch = getch();
        if (ch == keyUp || ch == 'w') {
            // Up
            option = (option == 0) ? 1 : option - 1;
        } else if (ch == keyDown || ch == 's') {
            // Down
            option = (option == 1) ? 0 : option + 1;
        } else if (ch == keyRight || ch == 'd' || ch == ' ' || ch == keyEnter) {
            // Next
            isQuit = option == 1;
            break;
        }
    }
}

void displayAfterGameScreen(string &page, int &level) {

    drawLogo();
    GoTo(xStart, yStart - 3);
    cout << "YOU WIN !!!";
    string options[3] = {"BACK TO LEVEL MENU", "PLAY AGAIN", "NEXT LEVEL"};

    int option = 0;
    while (true) {

        // Page
        for (int i=0; i<3; i++) {
            GoTo(xStart, yStart + 2*i);
            if (i == option) {
                cout << ">> " + options[i];
            } else {
                cout << "   " + options[i];
            }
        }

        // Move
        char ch = getch();
        if (ch == keyUp || ch == 'w') {
            // Up
            option = (option == 0) ? 2 : option - 1;
        } else if (ch == keyDown || ch == 's') {
            // Down
            option = (option == 2) ? 0 : option + 1;
        } else if (ch == keyRight || ch == 'd' || ch == ' ' || ch == keyEnter) {
            // Next
            if (option == 0) {
                page = "level";
            } else if (option == 1) {
                page = "play";
            } else {
                if (level == 3) {
                    page = "level";
                } else {
                    level++;
                    page = "play";
                }
            }
            break;
        }
    }
}