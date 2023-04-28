
struct Player {
    char name[50] = "";
    char pass[50] = "";

    int level = 0;
};

void login(Player &player, string name, string pass) {

    ifstream ifs("resources/player.dat", ios::binary);
    if (!ifs.is_open()) {
        return;
    }

    Player checkPlayer;
    while (!ifs.eof()) {
        ifs.read((char*) &checkPlayer, sizeof(Player));
        // Check if player exists
        if (strcmp(name.c_str(), checkPlayer.name) == 0) {

            // Check password
            if ((strcmp(pass.c_str(), checkPlayer.pass) == 0)) {
                // Success
                player = checkPlayer;
            } else {
                // Fail
                cout << "Wrong password !!!";
                getch();
            }

            ifs.close();
            return;
        }
    }

    ifs.close();
    cout << "Player does not exist !!!";
    getch();
}

void signup(Player &player, string name, string pass) {

    ifstream ifs("resources/player.dat", ios::binary);
    if (!ifs.is_open()) {
        return;
    }

    // Check if player exists
    Player checkPlayer;
    while (!ifs.eof()) {
        ifs.read((char*) &checkPlayer, sizeof(Player));
        if (strcmp(name.c_str(), checkPlayer.name) == 0) {
            cout << "This player already exists !!!";
            getch();
            ifs.close();
            return;
        }
    }
    ifs.close();

    // Add player
    strcpy(player.name, name.c_str());
    strcpy(player.pass, pass.c_str());

    ofstream ofs("resources/player.dat", ios::binary | ios::app);
    ofs.write((char*) &player, sizeof(Player));
    ofs.close();
}

void logout(Player &player) {
    strcpy(player.name, "");
}
