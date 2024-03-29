
char** generateMap(char saving[mapWidth*mapHeight]) {
    char** map = new char* [mapHeight];
    for (int i=0; i<mapHeight; i++) {
        map[i] = new char [mapWidth];
    }

    // Load saving
    if (strcmp(saving, "") != 0) {
        for (int y=0; y<mapHeight; y++) {
            for (int x=0; x<mapWidth; x++) {
                map[y][x] = saving[y*mapWidth + x];
            }
        }
        return map;
    }

    // Set all to Space
    for (int y=0; y<mapHeight; y++) {
        for (int x=0; x<mapWidth; x++) {
            map[y][x] = ' ';
        }
    }

    // Calculate occurrence
    int n = (mapWidth-2) * (mapHeight-2) / charNum;
    if (n % 2 != 0) {
        n--;
    }
    int blank = (mapWidth-2) * (mapHeight-2) - charNum * n;
    int occur[charNum];
    for (int i=0; i<charNum; i++) {
        occur[i] = n;
        if (blank > 0) {
            occur[i] += 2;
            blank -= 2;
        }
    }

    // Fill the map randomly
    srand(time(0));
    int ch;
    for (int y=1; y<mapHeight-1; y++) {
        for (int x=1; x<mapWidth-1; x++) {
            do {
                ch = rand()%charNum;
            } while (occur[ch] == 0);
            occur[ch] --;
            map[y][x] = char(65 + ch);
        }
    }
    
    return map;
}

char** getBackground(int level) {
    char** background = new char* [mapHeight*cellHeight];
    for (int i=0; i<mapHeight*cellHeight; i++) {
        background[i] = new char [mapWidth*cellWidth + 1];
    }

    ifstream ifs("assets/background.dat");
    if (ifs.is_open()) {
        ifs.seekg((mapWidth*cellWidth+1)*mapHeight*cellHeight*level, ios::beg);
        for (int i=0; i<mapHeight*cellHeight; i++) {
            ifs.read(background[i], mapWidth*cellWidth + 1);
            mask(background[i]);
        }
    }

    return background;
}

void clearLevel(char** map, char** background) {
    // Clear map
    for (int i=0; i<mapHeight; i++) {
        delete [] map[i];
    }
    delete [] map;
    // Clear background
    for (int i=0; i<mapHeight*cellHeight; i++) {
        delete [] background[i];
    }
    delete [] background;
}

void showLevelContext(int level) {
    ifstream ifs("assets/levelInfo.dat", ios::binary);
    if (ifs.is_open()) {
        LevelInfo lvInfo;
        ifs.seekg(sizeof(LevelInfo) * level, ios::beg);
        ifs.read((char *) &lvInfo, sizeof(LevelInfo));
        mask(lvInfo.levelContext);
        mask(lvInfo.levelFeature);

        int line = 1, i = 0;
        GoTo(xStart, 5);
        while (lvInfo.levelContext[i] != '\0') {
            if (lvInfo.levelContext[i] == '\n') {
                GoTo(xStart, 5 + line);
                line ++;
            } else {
                cout << lvInfo.levelContext[i];
                Sleep(20);
            }
            i ++;
        }

        GoTo(xStart, 5 + line + 2);
        cout << lvInfo.levelFeature;
        Sleep(1000);
        GoTo(xStart, 5 + line + 4);
        cout << "Press any key to continue...";
        while(kbhit()) getch();
        getch();

        system("cls");
    }
}

void act(char** map, char** background, coord &cur, coord &start, coord &end, bool &isPause) {
    char ch = getch();

    coord prev = cur;
    if (ch == keyRight || ch == 'd') {
        // Move right
        cur.x = (cur.x == mapWidth - 2) ? 1 : cur.x + 1;
        updateCell(prev, map[prev.y][prev.x], background, cur, start);
        updateCell(cur, map[cur.y][cur.x], background, cur, start);
    } else if (ch == keyLeft || ch == 'a') {
        // Move left
        cur.x = (cur.x == 1) ? mapWidth - 2 : cur.x - 1;
        updateCell(prev, map[prev.y][prev.x], background, cur, start);
        updateCell(cur, map[cur.y][cur.x], background, cur, start);
    } else if (ch == keyDown || ch == 's') {
        // Move down
        cur.y = (cur.y == mapHeight - 2) ? 1 : cur.y + 1;
        updateCell(prev, map[prev.y][prev.x], background, cur, start);
        updateCell(cur, map[cur.y][cur.x], background, cur, start);
    } else if (ch == keyUp || ch == 'w') {
        // Move up
        cur.y = (cur.y == 1) ? mapHeight - 2 : cur.y - 1;
        updateCell(prev, map[prev.y][prev.x], background, cur, start);
        updateCell(cur, map[cur.y][cur.x], background, cur, start);
    } else if (ch == keyEnter || ch == ' ') {
        // Pick
        if (map[cur.y][cur.x] != ' ') {
            if (start.x == 0) {
                start.x = cur.x;
                start.y = cur.y;
                updateCell(prev, map[prev.y][prev.x], background, cur, start);
            } else {
                end.x = cur.x;
                end.y = cur.y;
            }
        }
    } else if (ch == keyEsc) {
        isPause = true;
    }
}

bool isOver(char** map) {
    for (int y=0; y<mapHeight; y++) {
        for (int x=0; x<mapWidth; x++) {
            if (map[y][x] != ' ') {
                return false;
            }
        }
    }
    return true;
}

bool isImpossible(char** map) {
    for (int y=1; y<mapHeight-1; y++) {
        for (int x=1; x<mapWidth-1; x++) {
            if (map[y][x] != ' ') {
                for (int i=1; i<mapHeight-1; i++) {
                    for (int j=1; j<mapWidth-1; j++) {
                        if (map[i][j] != ' ' && findPath(map, {x, y}, {j, i}) != "")  {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

void Play(string &page, int &level, Player &player) {

    showLevelContext(level);

    // Set up
    char** map = generateMap(player.saving[level].map);
    char** background = getBackground(level);
    coord cur = {player.saving[level].x, player.saving[level].y}, start = {0, 0}, end = {0, 0};
    int score = player.saving[level].score, startTime = time(0);
    bool isPause = false;

    // Print level info
    GoTo(mapWidth*cellWidth, 4);
    cout << "Level: " << level+1;
    GoTo(mapWidth*cellWidth, 6);
    cout << "Player: " << (strcmp(player.name, "") == 0 ? "Guest" : player.name);

    // Draw initial map
    drawMap(map, background, cur, start, level);

    // Game loop
    while (true) {

        // Reset screen
        GoTo(xStart, 0);
        SetColor('M', 'O');
        GoTo(mapWidth*cellWidth, 8);
        cout << "Score:     ";
        GoTo(mapWidth*cellWidth + 6, 8);
        cout << score - (time(0) - startTime) * 20;

        // Logic handle
        Levels[level](map, background, cur, start, end, score);

        // Checking map
        if (isOver(map)) {
            break;
        }
        while (isImpossible(map)) {
            for (int y=1; y<mapHeight-1; y++) {
                for (int x=1; x<mapWidth-1; x++) {
                    coord randCoord = {rand()%(mapWidth-2) + 1, rand()%(mapHeight-2) + 1};
                    swap(map[y][x], map[randCoord.y][randCoord.x]);
                    updateCell({x, y}, map[y][x], background, cur, start);
                    updateCell(randCoord, map[randCoord.y][randCoord.x], background, cur, start);
                }
            }
        }

        // Player's action
        act(map, background, cur, start, end, isPause);
        if (isPause) {
            int pauseTime = time(0);
            system("cls");
            SetColor('M', 'O');
            bool isQuit;
            displayPauseScreen(isQuit);
            if (isQuit) {
                // Save and quit
                player.saving[level].x = cur.x;
                player.saving[level].y = cur.y;
                player.saving[level].score = score - (time(0) - startTime) * 20;
                for (int y=0; y<mapHeight; y++) {
                    for (int x=0; x<mapWidth; x++) {
                        player.saving[level].map[y*mapWidth + x] = map[y][x];
                    }
                }
                update(player, level);

                clearLevel(map, background);
                page = "level";
                return;
            } else {
                system("cls");
                drawMap(map, background, cur, start, level);
                isPause = false;
                startTime += time(0) - pauseTime;
            }
        };
    }

    // After game
    // Delete map
    clearLevel(map, background);

    // Clear saving
    Saving empty;
    player.saving[level] = empty;

    // Update record
    score -= (time(0) - startTime) * 20;
    if (level == player.level && level < 3) {
        player.level ++;
    }
    if (score > player.score[level]) {
        player.score[level] = score;
    }
    if (strcmp(player.name, "") != 0) {
        update(player, level);
    }

    // After game screen
    SetColor('M', 'O');
    system("cls");
    drawLogo();
    GoTo(xStart, yStart - 3);
    cout << "YOU WIN !!!";
    GoTo(xStart, yStart);
    cout << "Your score in this level: " << score;
    GoTo(xStart, yStart + 2);
    cout << "Your best score in this level: " << player.score[level];
    GoTo(xStart, yStart + 4);
    cout << "Your total score: " << player.score[0] + player.score[1] + player.score[2] + player.score[3];

    GoTo(xStart, yStart + 7);
    cout << "Press any key to continue...";
    while(kbhit()) getch();
    getch();
    system("cls");

    if (level == 3) {
        // End game outro
        showLevelContext(4);

        char** qr = getBackground(4);
        for (int y=0; y<mapHeight; y++) {
            for (int x=1; x<mapWidth-1; x++) {
                updateCell({x, y}, ' ', qr, {0, 0}, {0, 0});
            }
        }
        SetColor('M', 'O');
        GoTo(mapWidth*cellWidth - 8, 4);
        cout << "No rickroll trust me";
        GoTo(mapWidth*cellWidth - 8, 8);
        cout << "Press any key to continue...";
        getch();
        system("cls");

        page = "level";
    } else {
        displayAfterGameScreen(page, level);
    }
}
