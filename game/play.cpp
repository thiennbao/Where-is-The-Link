
char** generateMap() {
    char** map = new char* [mapHeight];
    for (int i=0; i<mapHeight; i++) {
        map[i] = new char [mapWidth];
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

void move(char** map, coord &cur, coord &start, coord &end) {
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

void Play(int level) {
    // Set up
    char** map = generateMap();
    coord cur = {1, 1}, start = {0, 0}, end = {0, 0};
    
    // Game loop
    while (!isOver(map)) {
        ClearScreen();

        (*Levels[level])(map, cur, start, end);

        move(map, cur, start, end);
    }

    // After game
    for (int i=0; i<mapHeight; i++) {
        delete [] map[i];
    }
    delete [] map;

    // After game screen
    system("cls");
    cout << "YOU WIN !!!";
    getch();
}