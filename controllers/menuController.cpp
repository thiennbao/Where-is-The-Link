
void MenuController(int &option) {

    int menuOption = 0;

    while (true) {

        system("cls");
        displayMainMenu(menuOption);

        if (menuOption == 0) {
            // Auth menu
            option = 1;
            break;

        } else if (menuOption == 1) {
            // Leader board
            system("cls");
            cout << "Leader board";

        } else if (menuOption == 2) {
            // Help
            system("cls");
            cout << "How to play";

        } else {
            // Quit the game
            option = 3;
            break;
            
        }
    }
}

void displayMainMenu(int &option) {
    char ch;
    while (true) {
        
        // Display the menu
        ClearScreen();
        // DrawLogo();

        cout << "MAIN MENU";

        int yStart = 12;
        string options[4] = {"START", "LEADERBOARD", "HOW TO PLAY", "QUIT GAME"};
        for (int i=0; i<4; i++) {
            yStart += 2;
            GoTo(0, yStart);
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
        }
    }
}