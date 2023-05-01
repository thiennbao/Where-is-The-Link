
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

void move(char** map, int &xCur, int &yCur, int &xStart, int &yStart, int &xEnd, int &yEnd, bool &swch) {
    char ch = getch();
    if (ch == keyRight || ch == 'd') {
        if (xCur == mapWidth - 2) {
            xCur = 1;
        }  else {
            xCur ++;
        }
    } else if (ch == keyLeft || ch == 'a') {
        if (xCur == 1) {
            xCur = mapWidth - 2;
        } else {
            xCur --;
        }
    } else if (ch == keyDown || ch == 's') {
        if (yCur == mapHeight - 2) {
            yCur = 1;
        }  else {
            yCur ++;
        }
    } else if (ch == keyUp || ch == 'w') {
        if (yCur == 1) {
            yCur = mapHeight - 2;
        } else {
            yCur --;
        }
    } else if (ch == keyEnter || ch == ' ') {
        if (map[yCur][xCur] != ' ') {
            if (swch) {
                xStart = xCur;
                yStart = yCur;
            } else {
                xEnd = xCur;
                yEnd = yCur;
            }
            swch = !swch;
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
    int xCur = 1, yCur = 1;
    int xStart = 0, yStart = 0, xEnd = 0, yEnd = 0;
    bool swch = true;
    string path;
    
    // Game loop
    while (true) {
        ClearScreen();

        Normal(map, xCur, yCur, xStart, yStart);

        move(map, xCur, yCur, xStart, yStart, xEnd, yEnd, swch);
        
        path = findPath(map, xStart, yStart, xEnd, yEnd);
        if (path != "") {
            map[yStart][xStart] = map[yEnd][xEnd] = ' ';
        }
        if (swch) {
            xStart = yStart = xEnd = yEnd = 0;
        }

        if (isOver(map)) {
            break;
        }
    }

    for (int i=0; i<mapHeight; i++) {
        delete [] map[i];
    }
    delete [] map;

    // After game screen
    system("cls");
    cout << "YOU WIN !!!";
    getch();
}