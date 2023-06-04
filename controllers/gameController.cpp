
void displayLevelMenu(string &page, int &level, int playerLevel) {

    GoTo(0, yStart - 4);
    cout << "LEVEL";
    string options[4] = {"LEVEL 1", "LEVEL 2", "LEVEL 3", "LEVEL 4"};

    int option = 0;
    while (true) {
        
        // Page
        for (int i=0; i<4; i++) {
            GoTo(0, yStart + 2*i);
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