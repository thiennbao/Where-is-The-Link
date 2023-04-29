
string Ipath(char** map, int xStart, int yStart, int xEnd, int yEnd) {
    if (yStart == yEnd) {
        // Horizontal
        if (xStart < xEnd) {
            // Right
            for (int x=xStart+1; x<xEnd; x++) {
                if (map[yStart][x] != '0') {
                    return "";
                }
            }
            return string(xEnd - xStart, 'd');
        } else {
            // Left
            for (int x=xStart-1; x>xEnd; x--) {
                if (map[yStart][x] != '0') {
                    return "";
                }
            }
            return string(xStart - xEnd, 'a');
        }
    } else if (xStart == xEnd) {
        // Vertical
        if (yStart < yEnd) {
            // Down
            for (int y=yStart+1; y<yEnd; y++) {
                if (map[y][xStart] != '0') {
                    return "";
                }
            }
            return string(yEnd - yStart, 's');
        } else {
            // Up
            for (int y=yStart-1; y>yEnd; y--) {
                if (map[y][xStart] != '0') {
                    return "";
                }
            }
            return string(yStart - yEnd, 'w');
        }
    }
}

string IIpath(char** map, int xStart, int yStart, int xEnd, int yEnd) {
    string Ihor, Iver;

    // Horizontal then Vertical
    Ihor = Ipath(map, xStart, yStart, xEnd, yStart);
    Iver = Ipath(map, xEnd, yStart, xEnd, yEnd);
    if (Ihor != "" && Iver != "" && map[yStart][xEnd] == '0') {
        return Ihor + Iver;
    }

    // Vertical then Horizontal
    Iver = Ipath(map, xStart, yStart, xStart, yEnd);
    Ihor = Ipath(map, xStart, yEnd, xEnd, yEnd);
    if (Ihor != "" && Iver != "" && map[yEnd][xStart] == '0') {
        return Iver + Ihor;
    }

    return "";
}

string IIIpath(char** map, int xStart, int yStart, int xEnd, int yEnd) {
    string Lline;

    // Right
    for (int x=xStart+1; map[yStart][x] != '\0'; x++) {
        if (map[yStart][x] != '0') {
            break;
        }
        Lline = IIpath(map, x, yStart, xEnd, yEnd);
        if (Lline != "") {
            return string(x - xStart, 'd') + Lline;
        }
    }

    // Left
    for (int x=xStart-1; map[yStart][x] != '\0'; x--) {
        if (map[yStart][x] != '0') {
            break;
        }
        Lline = IIpath(map, x, yStart, xEnd, yEnd);
        if (Lline != "") {
            return string(xStart - x, 'a') + Lline;
        }
    }

    // Down
    for (int y=yStart+1; map[y][xStart] != '\0'; y++) {
        if (map[y][xStart] != '0') {
            break;
        }
        Lline = IIpath(map, xStart, y, xEnd, yEnd);
        if (Lline != "") {
            return string(y - yStart, 's')+ Lline;
        }
    }

    // Up
    for (int y=yStart-1; map[y][xStart] != '\0'; y--) {
        if (map[y][xStart] != '0') {
            break;
        }
        Lline = IIpath(map, xStart, y, xEnd, yEnd);
        if (Lline != "") {
            return string(yStart - y, 'w') + Lline;
        }
    }

    return "";
}

string findPath(char** map, int xStart, int yStart, int xEnd, int yEnd) {
    if (map[yStart][xStart] == map[yEnd][xEnd] && (xStart != xEnd || yStart != yEnd)) {
        string path;
        
        path = Ipath(map, xStart, yStart, xEnd, yEnd);
        if (path != "") {
            return path;
        }
        path = IIpath(map, xStart, yStart, xEnd, yEnd);
        if (path != "") {
            return path;
        }
        path = IIIpath(map, xStart, yStart, xEnd, yEnd);
        if (path != "") {
            return path;
        }
    }
    return "";
}