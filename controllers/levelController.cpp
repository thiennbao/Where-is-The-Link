
void LevelController(int &option) {

    int levelOption = 0;

    while (true) {

        system("cls");
        displayLevelMenu(levelOption);

        if (0 <= levelOption && levelOption <= 3) {
            // Play
            cout << "Play level " << levelOption;
        } else {
            // Back to Main menu
            option = 0;
            break;
        }   
    }
}

void displayLevelMenu(int &option) {
    char ch;
    while (true) {
        
        // Display the menu
        ClearScreen();
        // DrawLogo();

        cout << "LEVEL";

        int yStart = 12;
        string options[4] = {"LEVEL 1", "LEVEL 2", "LEVEL 3", "LEVEL 4"};
        for (int i=0; i<4; i++) {
            GoTo(0, yStart + 2*i);
            if (i == option) {
                cout << ">> " + options[i];
            } else {
                cout << "   " + options[i];
            }
        }

        // Move
        ch = getch();
        if (ch == keyUp || ch == 'w') {
            // Up
            if (option == 0) {
                option = 3;
            } else {
                option--;
            }
        } else if (ch == keyDown || ch == 's') {
            // Down
            if (option == 3) {
                option = 0;
            } else {
                option++;
            }
        } else if (ch == keyRight || ch == 'd' || ch == ' ' || ch == keyEnter) {
            // Next
            break;
        } else if (ch == keyLeft || ch == 'a' || ch == keyEsc) {
            // Back
            option = 4;
            break;
        }
    }
}