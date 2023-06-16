
// Level's feature

bool Normal(char** map, char** background, coord cur, coord &start, coord &end, int &score) {
    string path = findPath(map, start, end);
    if (path != "") {
        drawPath(path, start, background, false);
        score += 100;
        map[start.y][start.x] = map[end.y][end.x] = ' ';
        updateCell(start, map[start.y][start.x], background, cur, start);
        updateCell(end, map[end.y][end.x], background, cur, start);
    }
    // Reset picking
    if (end.x != 0) {
        updateCell(start, map[start.y][start.x], background, cur, {0, 0});
        start = end = {0, 0};
    }
}

bool Falldown(char** map, char** background, coord cur, coord &start, coord &end, int &score) {
    string path = findPath(map, start, end);
    if (path != "") {
        drawPath(path, start, background, false);
        score += 100;
        map[start.y][start.x] = map[end.y][end.x] = ' ';
        if (start.y > end.y) {
            swap(start, end);
        }
        for (int y=start.y; y>1; y--) {
            swap(map[y][start.x], map[y-1][start.x]);
        }
        for (int y=end.y; y>1; y--) {
            swap(map[y][end.x], map[y-1][end.x]);
        }
        for (int y=1; y<mapHeight-1; y++) {
            updateCell({start.x, y}, map[y][start.x], background, cur, start);
            updateCell({end.x, y}, map[y][end.x], background, cur, start);
        }
    }
    // Reset picking
    if (end.x != 0) {
        updateCell(start, map[start.y][start.x], background, cur, {0, 0});
        start = end = {0, 0};
    }
}

bool Messup(char** map, char** background, coord cur, coord &start, coord &end, int &score) {
    string path = findPath(map, start, end);
    if (path != "") {
        drawPath(path, start, background, false);
        score += 100;
        map[start.y][start.x] = map[end.y][end.x] = ' ';
        for (int y=1; y<mapHeight-1; y++) {
            for (int x=1; x<mapWidth-1; x++) {
                coord randCoord = {rand()%(mapWidth-2) + 1, rand()%(mapHeight-2) + 1};
                swap(map[y][x], map[randCoord.y][randCoord.x]);
                updateCell({x, y}, map[y][x], background, cur, start);
                updateCell(randCoord, map[randCoord.y][randCoord.x], background, cur, start);
            }
        }
    }
    // Reset picking
    if (end.x != 0) {
        updateCell(start, map[start.y][start.x], background, cur, {0, 0});
        start = end = {0, 0};
    }
}

bool Dark(char** map, char** background, coord cur, coord &start, coord &end, int &score) {
    string path = findPath(map, start, end);
    if (path != "") {
        drawPath(path, start, background, true);
        score += 100;
        map[start.y][start.x] = map[end.y][end.x] = ' ';
    }
    // Reset picking
    if (end.x != 0) {
        drawVoid(start);
        start = end = {0, 0};
    }
    // Update 5x5 cells arround
    for (int y=cur.y-2; y<=cur.y+2; y++) {
        for (int x=cur.x-2; x<=cur.x+2; x++) {
            coord co = {
                (x > 0) ? ((x < mapWidth-1) ? x : x - mapWidth + 2) : mapWidth - 2 + x,
                (y > 0) ? ((y < mapHeight-1) ? y : y - mapHeight + 2) : mapHeight - 2 + y
            };
            if (cur.x-1 <= co.x && co.x <= cur.x+1 && cur.y-1 <= co.y && co.y <= cur.y+1) {
                updateCell(co, map[co.y][co.x], background, cur, start);
            } else {
                drawVoid(co);
            }
        }
    }
}

bool (*Levels[4])(char** map, char** background, coord cur, coord &start, coord &end, int &score) = {&Normal, &Falldown, &Messup, &Dark};