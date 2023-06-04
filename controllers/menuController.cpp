
void displayMainMenu(string &page, Player player) {

    GoTo(0, yStart - 4);
    cout << "MAIN MENU";
    string options[4] = {"START", "LEADERBOARD", "HOW TO PLAY", "QUIT GAME"};

    int option = 0;
    while (true) {

        // Page
        for (int i=0; i<4; i++) {
            GoTo(0, yStart + 2*i);
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
            option = (option == 0) ? 3 : option - 1;
        } else if (ch == keyDown || ch == 's') {
            // Down
            option = (option == 3) ? 0 : option + 1;
        } else if (ch == keyRight || ch == 'd' || ch == ' ' || ch == keyEnter) {
            // Next
            if (option == 0) {
                page = (strcmp(player.name, "") == 0) ? "auth" : "after auth";
            } else if (option == 1) {
                page = "leaderboard";
            } else if (option == 2) {
                page = "help";
            } else {
                page = "quit";
            }
            break;
        }
    }
}

void displayLeaderBoard(string &page) {
    GoTo(0, yStart - 4);
    cout << "LEADER BOARD";

    while (true) {
        char ch = getch();
        if (ch == keyLeft || ch == 'a' || ch == keyEsc) {
            // Back to Main menu
            page = "menu";
            break;
        }
    }
}

void displayHelp(string &page) {
    GoTo(0, yStart - 4);
    cout << "HOW TO PLAY";

    while (true) {
        char ch = getch();
        if (ch == keyLeft || ch == 'a' || ch == keyEsc) {
            // Back to Main menu
            page = "menu";
            break;
        }
    }
}