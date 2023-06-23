
void displayMainMenu(string &page, Player player) {

    drawLogo();
    GoTo(xStart, yStart - 3);
    cout << "MAIN MENU";
    string options[4] = {"START", "LEADERBOARD", "HOW TO PLAY", "QUIT GAME"};

    int option = 0;
    while (true) {

        // Page
        for (int i=0; i<4; i++) {
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

    drawLogo();
    GoTo(xStart, yStart - 3);
    cout << "LEADER BOARD";

    ifstream ifs("assets/player.dat", ios::binary);
    if (ifs.is_open()) {
        Player topPlayer;
        for (int i=0; i<5; i++) {
            ifs.read((char *) &topPlayer, sizeof(Player));
            if (ifs.eof()) {
                break;
            }
            mask(topPlayer.name, topPlayer.mask);
            string name = string(topPlayer.name);
            name.resize(52, '.');
            int score = 0;
            for (int lv=0; lv<4; lv++) {
                score += topPlayer.score[lv];
            }

            GoTo(xStart, yStart + 2*i);
            cout << name;
            GoTo(xStart + 52, yStart + 2*i);
            cout << score;
        }
        ifs.close();
    }

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

    drawLogo();
    GoTo(xStart, yStart - 3);
    cout << "HOW TO PLAY";

    GoTo(xStart, yStart);
    cout << "- Your task is to match 2 cells in the same character to remove them within 3 lines";
    GoTo(xStart, yStart + 1);
    cout << "- You score 100 points per 2 cells and lose 20 points per 1 second passed";
    GoTo(xStart, yStart + 3);
    cout << "Moving: WASD or Arrow key";
    GoTo(xStart, yStart + 5);
    cout << "Picking: Space or Enter";
    GoTo(xStart, yStart + 7);
    cout << "Going back: Esc";

    while (true) {
        char ch = getch();
        if (ch == keyLeft || ch == 'a' || ch == keyEsc) {
            // Back to Main menu
            page = "menu";
            break;
        }
    }
}

void displayQuitConfirm(string &page) {
    
    drawLogo();
    GoTo(xStart, yStart - 3);
    cout << "DO YOU WANT TO QUIT GAME";
    string options[2] = {"NO", "YES"};

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
            page = (option == 1) ? "exit" : "menu";
            break;
        }
    }
}