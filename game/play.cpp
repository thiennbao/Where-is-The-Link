
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

bool move(char** map, coord &cur, coord &start, coord &end) {
    char ch = getch();
    if (ch == keyRight || ch == 'd') {
        if (cur.x == mapWidth - 2) {
            cur.x = 1;
        }  else {
            cur.x ++;
        }
    } else if (ch == keyLeft || ch == 'a') {
        if (cur.x == 1) {
            cur.x = mapWidth - 2;
        } else {
            cur.x --;
        }
    } else if (ch == keyDown || ch == 's') {
        if (cur.y == mapHeight - 2) {
            cur.y = 1;
        }  else {
            cur.y ++;
        }
    } else if (ch == keyUp || ch == 'w') {
        if (cur.y == 1) {
            cur.y = mapHeight - 2;
        } else {
            cur.y --;
        }
    } else if (ch == keyEnter || ch == ' ') {
        if (map[cur.y][cur.x] != ' ') {
            if (start.x == 0) {
                start.x = cur.x;
                start.y = cur.y;
            } else {
                end.x = cur.x;
                end.y = cur.y;
            }
        }
    } 
    else if (ch == keyEsc) {
        if (getch() == keyEsc) {
            system("cls");
            SetColor(0, 7);
            GoTo(0, 12);
            cout << "Save a quit (A) - Continue (D)";
            while (true) {   
                ch = getch();
                if (ch == keyRight || ch == 'd') {
                    system("cls");
                    return true;
                } else if (ch == keyLeft || ch == 'a') {
                    return false;
                }
            }
        }
    }
    return true;
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

void Play(int level, Player &player) {
    // Set up
    char** map = generateMap(player.saving[level].map);
    coord cur = {player.saving[level].x, player.saving[level].y}, start = {0, 0}, end = {0, 0};
    int score = player.saving[level].score, startTime = time(0);

    GoTo(mapWidth*cellWidth, 4);
    cout << "Level: " << level+1;
    GoTo(mapWidth*cellWidth, 4);
    cout << "Player: " << (strcmp(player.name, "") == 0 ? "Guest" : player.name);

    // Game loop
    while (true) {
        ClearScreen();

        SetColor(0, 7);
        GoTo(mapWidth*cellWidth, 8);
        cout << "Score:     ";
        GoTo(mapWidth*cellWidth + 6, 8);
        cout << score - (time(0) - startTime) * 20;

        if ((*Levels[level])(map, cur, start, end)) {

            score += 100;

            if (isOver(map)) {
                break;
            }

            while (isImpossible(map)) {
                for (int y=1; y<mapHeight-1; y++) {
                    for (int x=1; x<mapWidth-1; x++) {
                        swap(map[y][x], map[rand()%(mapHeight-2) + 1][rand()%(mapWidth-2) + 1]);
                    }
                }
            }
        }

        if (!move(map, cur, start, end)) {
            // Saving
            player.saving[level].x = cur.x;
            player.saving[level].y = cur.y;
            player.saving[level].score = score - (time(0) - startTime) * 20;
            for (int y=0; y<mapHeight; y++) {
                for (int x=0; x<mapWidth; x++) {
                    player.saving[level].map[y*mapWidth + x] = map[y][x];
                }
            }
            update(player, level);

            for (int i=0; i<mapHeight; i++) {
                delete [] map[i];
            }
            delete [] map;
            return;
        };
    }

    // After game
    score -= (time(0) - startTime) * 20;
    for (int i=0; i<mapHeight; i++) {
        delete [] map[i];
    }
    delete [] map;

    Saving empty;
    player.saving[level] = empty;

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
    system("cls");
    SetColor(0, 7);
    GoTo(0, 12);
    cout << "YOU WIN !!!";
    GoTo(0, 14);
    cout << "Your score in this level: " << score;
    GoTo(0, 16);
    cout << "Your best score in this level: " << player.score[level];
    GoTo(0, 18);
    cout << "Your total score: " << player.score[0] + player.score[1] + player.score[2] + player.score[3];

    GoTo(0, 20);
    cout << "Back to Level Menu (A) - Play again (Space) - Next level (D)";
    while (true) {
        char ch = getch();
        if (ch == keyRight || ch == 'd') {
            system("cls");
            if (level < 3) {
                Play(level+1, player);
            }
            break;
        } else if (ch == ' ') {
            system("cls");
            Play(level, player);
            break;
        } else if (ch == keyLeft || ch == 'a') {
            break;
        }
    }
}
