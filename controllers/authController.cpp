
void AuthController(int &option, Player &player) {

    int authOption = 0;

    if (strcmp(player.name, "") == 0) {

        // Auth menu
        while (true) {

            system("cls");
            displayAuthMenu(authOption);

            if (authOption == 0) {
                // Log in
                system("cls");
                loginForm(player);
                if (strcmp(player.name, "") != 0) {
                    option = 2;
                    break;
                }

            } else if (authOption == 1) {
                // Sign up
                system("cls");
                signupForm(player);
                if (strcmp(player.name, "") != 0) {
                    option = 2;
                    break;
                }
                
            } else if (authOption == 2) {
                // Guest
                option = 2;
                break;

            } else {
                // Back to Main menu
                option = 0;
                break;
                
            }
        }

    } else {

        // After auth menu
        while (true) {

            system("cls");
            displayAfterAuthMenu(authOption);

            if (authOption == 0) {
                // Play
                option = 2;
                break;
            } else if (authOption == 1) {
                // Log out & Back to Main menu
                logout(player);
                option = 0;
                break;
            }  else {
                // Back to Main menu
                option = 0;
                break;
            }
        }
    }


}

void displayAuthMenu(int &option) {

    char ch;
    while (true) {
        
        // Display the menu
        ClearScreen();
        // DrawLogo();

        cout << "LOGIN TO SAVE YOUR PROGRESS";

        int yStart = 12;
        string options[3] = {"LOGIN", "SIGN UP", "GUEST"};
        for (int i=0; i<3; i++) {
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
                option = 2;
            } else {
                option--;
            }
        } else if (ch == keyDown || ch == 's') {
            // Down
            if (option == 2) {
                option = 0;
            } else {
                option++;
            }
        } else if (ch == keyRight || ch == 'd' || ch == ' ' || ch == keyEnter) {
            // Next
            break;
        } else if (ch == keyLeft || ch == 'a' || ch == keyEsc) {
            // Back
            option = 3;
            break;
        }
    }
}

void loginForm(Player &player) {

    int option = 0;
    string form[2];

    char ch;
    while (true) {
        
        // Display the form
        ClearScreen();
        // DrawLogo();

        cout << "LOGIN";

        int yStart = 12;
        string options[3] = {"NAME", "PASSWORD", "LOG IN"};
        // Print options
        for (int i=0; i<3; i++) {
            GoTo(0, yStart + 2*i);
            if (i == option) {
                cout << ">> " + options[i];
            } else {
                cout << "   " + options[i];
            }
        }
        // Print user inputs
        for (int i=0; i<2; i++) {
            GoTo(15, yStart + 2*i);
            cout << "   " << form[i];
        }

        // Move
        ch = getch();
        if (ch == keyUp || ch == 'w') {
            // Up
            if (option == 0) {
                option = 2;
            } else {
                option--;
            }
        } else if (ch == keyDown || ch == 's') {
            // Down
            if (option == 2) {
                option = 0;
            } else {
                option++;
            }
        } else if (ch == keyRight || ch == 'd' || ch == ' ' || ch == keyEnter) {
            // Next
            if (option <= 1) {
                // Hide the previous input
                GoTo(15, yStart + option*2);
                cout << string(3 + form[option].size(), ' ');
                // Fill the form
                GoTo(15, yStart + option*2);
                cout << ">> ";
                getline(cin, form[option]);
                form[option].resize(50);
                system("cls");
            } else {
                // Log in
                login(player, form[0], form[1]);
                break;
            }
        } else if (ch == keyLeft || ch == 'a' || ch == keyEsc) {
            // Back to Auth menu
            break;
        }
    }
}

void signupForm(Player &player) {

    int option = 0;
    string form[2];

    char ch;
    while (true) {
        
        // Display the form
        ClearScreen();
        // DrawLogo();

        cout << "SIGN UP";

        int yStart = 12;
        string options[3] = {"NAME", "PASSWORD", "SIGN UP"};
        // Print options
        for (int i=0; i<3; i++) {
            GoTo(0, yStart + 2*i);
            if (i == option) {
                cout << ">> " + options[i];
            } else {
                cout << "   " + options[i];
            }
        }
        // Print user inputs
        for (int i=0; i<2; i++) {
            GoTo(15, yStart + 2*i);
            cout << "   " << form[i];
        }

        // Move
        ch = getch();
        if (ch == keyUp || ch == 'w') {
            // Up
            if (option == 0) {
                option = 2;
            } else {
                option--;
            }
        } else if (ch == keyDown || ch == 's') {
            // Down
            if (option == 2) {
                option = 0;
            } else {
                option++;
            }
        } else if (ch == keyRight || ch == 'd' || ch == ' ' || ch == keyEnter) {
            // Next
            if (option <= 1) {
                // Hide the previous input
                GoTo(15, yStart + option*2);
                cout << string(3 + form[option].size(), ' ');
                // Fill the form
                GoTo(15, yStart + option*2);
                cout << ">> ";
                getline(cin, form[option]);
                form[option].resize(50);
                system("cls");
            } else {
                // Sign up
                signup(player, form[0], form[1]);
                break;
            }
        } else if (ch == keyLeft || ch == 'a' || ch == keyEsc) {
            // Back to Auth menu
            break;
        }
    }
}

void displayAfterAuthMenu(int &option) {

    char ch;
    while (true) {
        
        // Display the menu
        ClearScreen();
        // DrawLogo();

        cout << "WELCOME";

        int yStart = 12;
        string options[2] = {"PLAY", "LOG OUT"};
        for (int i=0; i<2; i++) {
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
                option = 1;
            } else {
                option--;
            }
        } else if (ch == keyDown || ch == 's') {
            // Down
            if (option == 1) {
                option = 0;
            } else {
                option++;
            }
        } else if (ch == keyRight || ch == 'd' || ch == ' ' || ch == keyEnter) {
            // Next
            break;
        } else if (ch == keyLeft || ch == 'a' || ch == keyEsc) {
            // Back
            option = 2;
            break;
        }
    }
}