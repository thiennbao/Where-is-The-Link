
void drawCell(coord co, char content, bool isDouble, bool isHightLight) {

    char border[2][6] = {
        {char(218), char(191), char(192), char(217), char(196), char(179)}, // ┌ ┐ └ ┘ ─ │
        {char(201), char(187), char(200), char(188), char(205), char(186)}, // ╔ ╗ ╚ ╝ ═ ║
    };

    // Color
    int textColor = isDouble ? (isHightLight ? 'P' : 'O') : content;
    SetColor('M', textColor);

    // Border top
    GoTo(cellWidth*co.x, cellHeight*co.y);
    cout << border[isDouble][0] << string(cellWidth - 2, border[isDouble][4]) << border[isDouble][1];
    // Border left & right
    for (int y=1; y<cellHeight-1; y++) {
        GoTo(cellWidth * co.x, cellHeight * co.y + y);
        cout << border[isDouble][5] << string(cellWidth-2, ' ') << border[isDouble][5];
    }
    // Border bottom
    GoTo(cellWidth*co.x, cellHeight*co.y + cellHeight-1);
    cout << border[isDouble][2] << string(cellWidth - 2, border[isDouble][4]) << border[isDouble][3];
    // Content
    GoTo(cellWidth*co.x + cellWidth/2, cellHeight*co.y + cellHeight/2);
    cout << content;
}

void drawBackground(coord co, char** background, bool isHightLight) {

    char border[2][6] = {
        {' ', ' ', ' ', ' ', ' ', ' '}, // No border
        {char(201), char(187), char(200), char(188), char(205), char(186)}, // ╔ ╗ ╚ ╝ ═ ║
    };

    // Border top
    GoTo(cellWidth*co.x, cellHeight*co.y);
    SetColor(background[cellHeight*co.y][cellWidth*co.x], 'P');
    cout << border[isHightLight][0];
    for (int x=1; x<cellWidth-1; x++) {
        SetColor(background[cellHeight*co.y][cellWidth*co.x + x], 'P');
        cout << border[isHightLight][4];
    }
    SetColor(background[cellHeight*co.y][cellWidth*co.x + cellWidth - 1], 'P');
    cout << border[isHightLight][1];
    // Border left & right
    for (int y=1; y<cellHeight-1; y++) {
        GoTo(cellWidth*co.x, cellHeight*co.y + y);
        SetColor(background[cellHeight*co.y + y][cellWidth*co.x], 'P');
        cout << border[isHightLight][5];
        for (int x=1; x<cellWidth-1; x++) {
            SetColor(background[cellHeight*co.y + y][cellWidth*co.x + x], 'P');
            cout << " ";
        }
        SetColor(background[cellHeight*co.y + y][cellWidth*co.x + cellWidth - 1], 'P');
        cout << border[isHightLight][5];
    }
    // Border bottom
    GoTo(cellWidth*co.x, cellHeight*co.y + cellHeight-1);
    SetColor(background[cellHeight*co.y + cellHeight - 1][cellWidth*co.x], 'P');
    cout << border[isHightLight][2];
    for (int x=1; x<cellWidth-1; x++) {
        SetColor(background[cellHeight*co.y + cellHeight - 1][cellWidth*co.x + x], 'P');
        cout << border[isHightLight][4];
    }
    SetColor(background[cellHeight*co.y + cellHeight - 1][cellWidth*co.x + cellWidth - 1], 'P');
    cout << border[isHightLight][3];
}

void drawVoid(coord co) {
    SetColor('M', 'M');
    for (int y=0; y<cellHeight; y++) {
        GoTo(cellWidth*co.x, cellHeight*co.y + y);
        cout << string(cellWidth, ' ');
    }
}

void updateCell(coord co, char content, char** background, coord cur, coord pick) {
    bool isCur = co.x == cur.x && co.y == cur.y;
    bool isPicked = co.x == pick.x && co.y == pick.y;

    if (content != ' ') {
        drawCell(co, content, isPicked || isCur, isCur);
    } else {
        drawBackground(co, background, isCur);
    }
}

void drawMap(char** map, char** background, coord cur, coord start, int level) {
    if (level == 3) {
        for (int y=0; y<=cur.y+1; y++) {
            for (int x=0; x<=cur.x+1; x++) {
                updateCell({x, y}, map[y][x], background, cur, start);
            }
        }
    } else {
        for (int y=0; y<mapHeight; y++) {
            for (int x=0; x<mapWidth; x++) {
                updateCell({x, y}, map[y][x], background, cur, start);
            }
        }
    }
}

void drawLine(char cur, char next, coord &start, char** background, bool isDraw) {
    char line[2][6] = {
        {' ', ' ', ' ', ' ', ' ', ' '}, // For clearing
        {char(218), char(191), char(192), char(217), char(196), char(179)}, // ┌ ┐ └ ┘ ─ │
    };


    if (cur == 'a' || cur == 'd') {
        // Horizontal line
        for (int i=0; i<cellWidth-1; i++) {
            // Left if A and vice versa
            start.x += (cur == 'a' ? -1 : 1);
            GoTo(start.x, start.y);
            SetColor(background[start.y][start.x], 'P');
            cout << line[isDraw][4];
        }
        start.x += (cur == 'a' ? -1 : 1);
    } else if (cur == 'w' || cur == 's') {
        // Vertical line
        for (int i=0; i<cellHeight-1; i++) {
            // Up if W and vice versa
            start.y += (cur == 'w' ? -1 : 1);
            GoTo(start.x, start.y);
            SetColor(background[start.y][start.x], 'P');
            cout << line[isDraw][5];
        }
        start.y += (cur == 'w' ? -1 : 1);
    }
    // Last char
    GoTo(start.x, start.y);
    SetColor(background[start.y][start.x], 'P');
    if (cur == next) {
        // Line
        if (cur == 'a' || cur == 'd') {
            cout << line[isDraw][4];
        } else if (cur == 'w' || cur == 's') {
            cout << line[isDraw][5];
        }
    } else {
        // Corner
        if ((cur == 'a' && next == 'w') || (cur == 's' && next == 'd')) {
            cout << line[isDraw][2];
        } else if ((cur == 'a' && next == 's') || (cur == 'w' && next == 'd')) {
            cout << line[isDraw][0];
        } else if ((cur == 'd' && next == 'w') || (cur == 's' && next == 'a')) {
            cout << line[isDraw][3];
        } else if ((cur == 'd' && next == 's') || (cur == 'w' && next == 'a')) {
            cout << line[isDraw][1];
        }
    }
}

void drawPath(string path, coord start, char** background) {
    coord co;
    // Draw
    co = {start.x*cellWidth + cellWidth/2, start.y*cellHeight + cellHeight/2};
    for (int i=0; i<path.size(); i++) {
        drawLine(path[i], path[i+1], co, background, true);
    }
    // Wait
    Sleep(100);
    // Clear
    co = {start.x*cellWidth + cellWidth/2, start.y*cellHeight + cellHeight/2};
    for (int i=0; i<path.size(); i++) {
        drawLine(path[i], path[i+1], co, background, false);
    }
}