
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


// Level's feature

void Normal(char** map, coord cur, coord &start, coord &end) {

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
            drawCell(map, {x, y}, cur, start);
        }
    }
}

void Falldown(char** map, coord cur, coord &start, coord &end) {

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
}

void Messup(char** map, coord cur, coord &start, coord &end) {

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
}

void Dark(char** map, coord cur, coord &start, coord &end) {
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
}

void (*Levels[4])(char** map, coord cur, coord &start, coord &end) = {&Normal, &Falldown, &Messup, &Dark};