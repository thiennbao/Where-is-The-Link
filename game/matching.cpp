
string Ipath(char** map, coord start, coord end) {
    if (start.y == end.y) {
        // Horizontal
        if (start.x < end.x) {
            // Right
            for (int x=start.x+1; x<end.x; x++) {
                if (map[start.y][x] != ' ') {
                    return "";
                }
            }
            return string(end.x - start.x, 'd');
        } else {
            // Left
            for (int x=start.x-1; x>end.x; x--) {
                if (map[start.y][x] != ' ') {
                    return "";
                }
            }
            return string(start.x - end.x, 'a');
        }
    } else if (start.x == end.x) {
        // Vertical
        if (start.y < end.y) {
            // Down
            for (int y=start.y+1; y<end.y; y++) {
                if (map[y][start.x] != ' ') {
                    return "";
                }
            }
            return string(end.y - start.y, 's');
        } else {
            // Up
            for (int y=start.y-1; y>end.y; y--) {
                if (map[y][start.x] != ' ') {
                    return "";
                }
            }
            return string(start.y - end.y, 'w');
        }
    }

    return "";
}

string IIpath(char** map, coord start, coord end) {
    string Ihor, Iver;

    // Horizontal then Vertical
    Ihor = Ipath(map, {start.x, start.y}, {end.x, start.y});
    Iver = Ipath(map, {end.x, start.y}, {end.x, end.y});
    if (Ihor != "" && Iver != "" && map[start.y][end.x] == ' ') {
        return Ihor + Iver;
    }

    // Vertical then Horizontal
    Iver = Ipath(map, {start.x, start.y}, {start.x, end.y});
    Ihor = Ipath(map, {start.x, end.y}, {end.x, end.y});
    if (Ihor != "" && Iver != "" && map[end.y][start.x] == ' ') {
        return Iver + Ihor;
    }

    return "";
}

string IIIpath(char** map, coord start, coord end) {
    string Lline;

    // Right
    for (int x=start.x+1; x<mapWidth; x++) {
        if (map[start.y][x] != ' ') {
            break;
        }
        Lline = IIpath(map, {x, start.y}, {end.x, end.y});
        if (Lline != "") {
            return string(x - start.x, 'd') + Lline;
        }
    }

    // Left
    for (int x=start.x-1; x>=0; x--) {
        if (map[start.y][x] != ' ') {
            break;
        }
        Lline = IIpath(map, {x, start.y}, {end.x, end.y});
        if (Lline != "") {
            return string(start.x - x, 'a') + Lline;
        }
    }

    // Down
    for (int y=start.y+1; y<mapHeight; y++) {
        if (map[y][start.x] != ' ') {
            break;
        }
        Lline = IIpath(map, {start.x, y}, {end.x, end.y});
        if (Lline != "") {
            return string(y - start.y, 's')+ Lline;
        }
    }

    // Up
    for (int y=start.y-1; y>=0; y--) {
        if (map[y][start.x] != ' ') {
            break;
        }
        Lline = IIpath(map, {start.x, y}, {end.x, end.y});
        if (Lline != "") {
            return string(start.y - y, 'w') + Lline;
        }
    }

    return "";
}

string findPath(char** map, coord start, coord end) {
    if (map[start.y][start.x] == map[end.y][end.x] && (start.x != end.x || start.y != end.y)) {
        string path;
        
        path = Ipath(map, {start.x, start.y}, {end.x, end.y});
        if (path != "") {
            return path;
        }
        path = IIpath(map, {start.x, start.y}, {end.x, end.y});
        if (path != "") {
            return path;
        }
        path = IIIpath(map, {start.x, start.y}, {end.x, end.y});
        if (path != "") {
            return path;
        }
    }
    return "";
}