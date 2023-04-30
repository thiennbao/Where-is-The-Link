
// Level's feature

void Normal(char** map, int xStart, int yStart, int xEnd, int yEnd) {
    string path = findPath(map, xStart, yStart, xEnd, yEnd);
    if (path != "") {
        map[yStart][xStart] = map[yEnd][xEnd] = '0';
    }
}