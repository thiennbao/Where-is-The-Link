
void drawBox(char ch, coord co, int color, bool isDouble) {
    SetColor(0, color);
    if (isDouble) {
        GoTo(cellWidth*co.x, cellHeight*co.y);
        cout << char(201) << char(205) << char(205) << char(205) << char(187);
        GoTo(cellWidth*co.x, cellHeight*co.y+1);
        cout << char(186) << " " << ch << " " << char(186);
        GoTo(cellWidth*co.x, cellHeight*co.y+2);
        cout << char(200) << char(205) << char(205) << char(205) << char(188);
    } else {
        GoTo(cellWidth*co.x, cellHeight*co.y);
        cout << char(218) << char(196) << char(196) << char(196) << char(191);
        GoTo(cellWidth*co.x, cellHeight*co.y+1);
        cout << char(179) << " " << ch << " " << char(179);
        GoTo(cellWidth*co.x, cellHeight*co.y+2);
        cout << char(192) << char(196) << char(196) << char(196) << char(217);        
    }
}
void drawCell(char** map, coord co, coord cur, coord pick) {
    if (co.x == cur.x && co.y == cur.y) {
        drawBox(map[co.y][co.x], co, 15, true); // 15 -> Bright White
    } else if (map[co.y][co.x] != ' ') {
        if (co.x == pick.x && co.y == pick.y) {
            drawBox(map[co.y][co.x], co, 7, true); // 7 -> White
        } else {
            if (map[co.y][co.x] == 'G') {
                drawBox(map[co.y][co.x], co, 13, false); // G -> 7 -> White -> 13 -> Light Purple
            } else if (map[co.y][co.x] == 'H') {
                drawBox(map[co.y][co.x], co, 14, false); // H -> 8 -> Gray -> 14 -> Light Yellow
            } else {
                drawBox(map[co.y][co.x], co, (int) map[co.y][co.x] - 64, false);
            }
        }
    } else {
        GoTo(cellWidth*co.x, cellHeight*co.y);
        cout << "     ";
        GoTo(cellWidth*co.x, cellHeight*co.y+1);
        cout << "     ";
        GoTo(cellWidth*co.x, cellHeight*co.y+2);
        cout << "     ";
    }
}

void drawLine(char cur, char next, coord &start) {
    if (cur == 'a' || cur == 'd') {
        // Horizontal line
        for (int i=0; i<cellWidth-1; i++) {
            // Left if A and vice versa
            start.x += (cur == 'a' ? -1 : 1);
            GoTo(start.x, start.y);
            cout << char(196);
        }
        start.x += (cur == 'a' ? -1 : 1);
    } else if (cur == 'w' || cur == 's') {
        // Vertical line
        for (int i=0; i<cellHeight-1; i++) {
            // Up if W and vice versa
            start.y += (cur == 'w' ? -1 : 1);
            GoTo(start.x, start.y);
            cout << char(179);
        }
        start.y += (cur == 'w' ? -1 : 1);
    }
    // Last char
    GoTo(start.x, start.y);
    if (cur == next) {
        // Line
        if (cur == 'a' || cur == 'd') {
            cout << char(196);
        } else if (cur == 'w' || cur == 's') {
            cout << char(179);
        }
    } else {
        // Corner
        if ((cur == 'a' && next == 'w') || (cur == 's' && next == 'd')) {
            cout << char(192);
        } else if ((cur == 'a' && next == 's') || (cur == 'w' && next == 'd')) {
            cout << char(218);
        } else if ((cur == 'd' && next == 'w') || (cur == 's' && next == 'a')) {
            cout << char(217);
        } else if ((cur == 'd' && next == 's') || (cur == 'w' && next == 'a')) {
            cout << char(191);
        }
    }
}
void drawPath(string path, coord start) {
    coord co = {start.x*cellWidth + cellWidth/2, start.y*cellHeight + cellHeight/2};
    for (int i=0; i<path.size(); i++) {
        drawLine(path[i], path[i+1], co);
    }
}


// Level's feature

bool Normal(char** map, coord cur, coord &start, coord &end) {

    // Map handle
    string path = findPath(map, start, end);
    if (path != "") {
        drawPath(path, start);
        Sleep(500);
        map[start.y][start.x] = map[end.y][end.x] = ' ';
    }

    // Reset picking
    if (end.x != 0) {
        start = end = {0, 0};
    }

    // Draw map
    for (int y=0; y<mapHeight; y++) {
        for (int x=0; x<mapWidth; x++) {
            drawCell(map, {x, y}, cur, start);
        }
    }

    return !(path == "");
}

bool Falldown(char** map, coord cur, coord &start, coord &end) {

    // Map handle
    string path = findPath(map, start, end);
    if (path != "") {
        map[start.y][start.x] = map[end.y][end.x] = ' ';

        // Fall down
        if (start.y > end.y) {
            swap(start, end);
        }
        for (int y=start.y; y>1; y--) {
            swap(map[y][start.x], map[y-1][start.x]);
        }
        for (int y=end.y; y>1; y--) {
            swap(map[y][end.x], map[y-1][end.x]);
        }
    }

    // Reset picking
    if (end.x != 0) {
        start = end = {0, 0};
    }

    // Draw map
    for (int y=0; y<mapHeight; y++) {
        for (int x=0; x<mapWidth; x++) {
            drawCell(map, {x, y}, cur, start);
        }
    }

    return !(path == "");
}

bool Messup(char** map, coord cur, coord &start, coord &end) {

    // Map handle
    string path = findPath(map, start, end);
    if (path != "") {
        map[start.y][start.x] = map[end.y][end.x] = ' ';

        // Messup
        for (int y=1; y<mapHeight-1; y++) {
            for (int x=1; x<mapWidth-1; x++) {
                swap(map[y][x], map[rand()%(mapHeight-2) + 1][rand()%(mapWidth-2) + 1]);
            }
        }
    }

    // Reset picking
    if (end.x != 0) {
        start = end = {0, 0};
    }

    // Draw map
    for (int y=0; y<mapHeight; y++) {
        for (int x=0; x<mapWidth; x++) {
            drawCell(map, {x, y}, cur, start);
        }
    }

    return !(path == "");
}

bool Dark(char** map, coord cur, coord &start, coord &end) {
    // Map handle
    string path = findPath(map, start, end);
    if (path != "") {
        map[start.y][start.x] = map[end.y][end.x] = ' ';
    }

    // Reset picking
    if (end.x != 0) {
        start = end = {0, 0};
    }

    // Draw map
    for (int y=0; y<mapHeight; y++) {
        for (int x=0; x<mapWidth; x++) {
            if ((cur.x-1 <= x && x <= cur.x+1) && (cur.y-1 <= y && y <= cur.y+1)) {
                drawCell(map, {x, y}, cur, start);
            } else {
                GoTo(cellWidth*x, cellHeight*y);
                cout << "     ";
                GoTo(cellWidth*x, cellHeight*y+1);
                cout << "     ";
                GoTo(cellWidth*x, cellHeight*y+2);
                cout << "     ";
            }
        }
    }

    return path != "";
}

bool (*Levels[4])(char** map, coord cur, coord &start, coord &end) = {&Normal, &Falldown, &Messup, &Dark};