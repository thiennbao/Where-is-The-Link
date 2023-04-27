
void AuthController(int &option) {

    int authOption = 0;

    while (true) {

        system("cls");
        displayAuthMenu(authOption);

        if (authOption == 0) {
            // Log in
            system("cls");
            cout << "Login";

        } else if (authOption == 1) {
            // Sign up
            system("cls");
            cout << "Sign up";

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