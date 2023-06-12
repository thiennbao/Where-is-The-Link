
void displayAuthMenu(string &page) {

    drawLogo();
    GoTo(xStart, yStart - 3);
    cout << "LOG IN TO SAVE YOUR PROGRESS";
    string options[3] = {"LOG IN", "SIGN UP", "GUEST"};

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
                page = "login";
            } else if (option == 1) {
                page = "signup";
            } else {
                page = "level";
            }
            break;
        } else if (ch == keyLeft || ch == 'a' || ch == keyEsc) {
            // Back to Main menu
            page = "menu";
            break;
        }
    }
}

void displayLoginForm(string &page, Player &player) {

    drawLogo();
    GoTo(xStart, yStart - 3);
    cout << "LOG IN";
    string options[3] = {"NAME", "PASSWORD", "LOG IN"};

    string form[2];
    int option = 0;
    while (true) {
        
        // Page
        // Print option
        for (int i=0; i<3; i++) {
            GoTo(xStart, yStart + 2*i);
            if (i == option) {
                cout << ">> " + options[i];
            } else {
                cout << "   " + options[i];
            }
        }
        // Print user inputs
        for (int i=0; i<2; i++) {
            GoTo(xStart + 15, yStart + 2*i);
            cout << "   " << form[i];
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
            if (option <= 1) {
                // Hide the previous input
                GoTo(xStart + 15, yStart + option*2);
                cout << string(3 + form[option].size(), ' ');
                // Fill the form
                GoTo(xStart + 15, yStart + option*2);
                cout << ">> ";
                getline(cin, form[option]);
                form[option].resize(50);
            } else {
                // Log in
                login(player, form[0], form[1]);
                page = (strcmp(player.name, "") != 0) ? "level" : "login";
                break;
            }
        } else if (ch == keyLeft || ch == 'a' || ch == keyEsc) {
            // Back to Auth menu
            page = "auth";
            break;
        }
    }
}

void displaySignupForm(string &page, Player &player) {

    drawLogo();
    GoTo(xStart, yStart - 3);
    cout << "SIGN UP";
    string options[3] = {"NAME", "PASSWORD", "SIGN UP"};

    string form[2];
    int option = 0;
    while (true) {
        
        // Page
        // Print options
        for (int i=0; i<3; i++) {
            GoTo(xStart, yStart + 2*i);
            if (i == option) {
                cout << ">> " + options[i];
            } else {
                cout << "   " + options[i];
            }
        }
        // Print user inputs
        for (int i=0; i<2; i++) {
            GoTo(xStart + 15 , yStart + 2*i);
            cout << "   " << form[i];
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
            if (option <= 1) {
                // Hide the previous input
                GoTo(xStart + 15, yStart + option*2);
                cout << string(3 + form[option].size(), ' ');
                // Fill the form
                GoTo(xStart + 15, yStart + option*2);
                cout << ">> ";
                getline(cin, form[option]);
                form[option].resize(50);
            } else {
                // Sign up
                signup(player, form[0], form[1]);
                page = (strcmp(player.name, "") != 0) ? "level" : "signup";
                break;
            }
        } else if (ch == keyLeft || ch == 'a' || ch == keyEsc) {
            // Back to Auth menu
            page = "auth";
            break;
        }
    }
}

void displayAfterAuthMenu(string &page, Player &player) {

    drawLogo();
    GoTo(xStart, yStart - 3);
    cout << "WELCOME";
    string options[2] = {"PLAY", "LOG OUT"};

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
            if (option == 0) {
                page = "level";
            } else {
                // log out here
                logout(player);
                page = "menu";
            }
            break;
        } else if (ch == keyLeft || ch == 'a' || ch == keyEsc) {
            page = "menu";
            break;
        }
    }
}