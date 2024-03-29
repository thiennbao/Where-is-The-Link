
struct Saving {
    int x = 1, y = 1, score = 0;
    char map[mapWidth*mapHeight] = "";
};
struct Player {
    char mask = 0;
    char name[50] = "";
    char pass[50] = "";

    int level = 0;
    int score[4] = {0, 0, 0, 0};
    Saving saving[4];
};

void login(Player &player, string name, string pass) {

    ifstream ifs("assets/player.dat", ios::binary);
    if (!ifs.is_open()) {
        return;
    }

    Player checkPlayer;
    while (!ifs.eof()) {
        ifs.read((char*) &checkPlayer, sizeof(Player));
        // Check if player exists
        mask(checkPlayer.name, checkPlayer.mask);
        if (strcmp(name.c_str(), checkPlayer.name) == 0) {

            // Check password
            mask(checkPlayer.pass, checkPlayer.mask);
            if ((strcmp(pass.c_str(), checkPlayer.pass) == 0)) {
                // Success
                player = checkPlayer;
            } else {
                // Fail
                GoTo(xStart, yStart + 8);
                cout << "Wrong password !!!";
                getch();
            }

            ifs.close();
            return;
        }
    }

    ifs.close();
    GoTo(xStart, yStart + 8);
    cout << "Player does not exist !!!";
    getch();
}

void signup(Player &player, string name, string pass) {

    ifstream ifs("assets/player.dat", ios::binary);
    if (!ifs.is_open()) {
        return;
    }

    // Check if player exists
    Player checkPlayer;
    while (!ifs.eof()) {
        ifs.read((char*) &checkPlayer, sizeof(Player));
        mask(checkPlayer.name, checkPlayer.mask);
        if (strcmp(name.c_str(), checkPlayer.name) == 0) {
            GoTo(xStart, yStart + 8);
            cout << "This player already exists !!!";
            getch();
            ifs.close();
            return;
        }
    }
    ifs.close();

    // Add player
    Player newPlayer;
    srand(time(0));
    newPlayer.mask = 128 + rand()%128;
    strcpy(newPlayer.name, name.c_str());
    mask(newPlayer.name, newPlayer.mask);
    strcpy(newPlayer.pass, pass.c_str());
    mask(newPlayer.pass, newPlayer.mask);

    ofstream ofs("assets/player.dat", ios::binary | ios::app);
    ofs.write((char*) &newPlayer, sizeof(Player));
    ofs.close();

    player = newPlayer;
}

void logout(Player &player) {
    Player emptyPlayer;
    player = emptyPlayer;
}

void update(Player player, int level) {

    ifstream ifs("assets/player.dat", ios::binary);
    if (!ifs.is_open()) {
        return;
    }

    // Get player list
    ifs.seekg(0, ios::end);
    const int playerNum = ifs.tellg() / sizeof(Player);
    ifs.seekg(0, ios::beg);
    Player playerList[playerNum];
    for (int i=0; i<playerNum; i++) {
        ifs.read((char *) &playerList[i], sizeof(Player));
    }
    ifs.close();

    // Update
    for (int i=0; i<playerNum; i++) {
        mask(playerList[i].name, playerList[i].mask);
        if (strcmp(player.name, playerList[i].name) == 0) {
            // Saving
            playerList[i].saving[level] = player.saving[level];
            // Update
            if (strcmp(player.saving[player.level].map, "") == 0) {
                if (player.level > playerList[i].level) {
                    playerList[i].level = player.level;
                }
                for (int lv=0; lv<4; lv++) {
                    if (player.score[lv] > playerList[i].score[lv]) {
                        playerList[i].score[lv] = player.score[lv];
                    }
                }
            }
            mask(playerList[i].name, playerList[i].mask);
            break;
        }
        mask(playerList[i].name, playerList[i].mask);
    }

    // Sort
    for (int i=1; i<playerNum; i++) {

        Player curPlayer = playerList[i];

        int playerScore = 0;
        for (int lv=0; lv<4; lv++) {
            playerScore += curPlayer.score[lv];
        }

        int j;
        for (j=i; j>0; j--) {
            int prevPlayerScore = 0;
            for (int lv=0; lv<4; lv++) {
                prevPlayerScore += playerList[j-1].score[lv];
            }

            if (prevPlayerScore < playerScore) {
                playerList[j] = playerList[j-1]; 
            } else {
                break;
            }
        }

        playerList[j] = curPlayer;
    }

    // Write to file
    ofstream ofs("assets/player.dat", ios::binary);
    for (int i=0; i<playerNum; i++) {
        ofs.write((char *) &playerList[i], sizeof(Player));
    }
    ofs.close();
}
