
void drawBox(char ch, int x, int y, int color, bool isDouble) {
    SetColor(0, color);
    if (isDouble) {
        GoTo(cellWidth*x, cellHeight*y);
        cout << char(201) << char(205) << char(205) << char(205) << char(187);
        GoTo(cellWidth*x, cellHeight*y+1);
        cout << char(186) << " " << ch << " " << char(186);
        GoTo(cellWidth*x, cellHeight*y+2);
        cout << char(200) << char(205) << char(205) << char(205) << char(188);
    } else {
        GoTo(cellWidth*x, cellHeight*y);
        cout << char(218) << char(196) << char(196) << char(196) << char(191);
        GoTo(cellWidth*x, cellHeight*y+1);
        cout << char(179) << " " << ch << " " << char(179);
        GoTo(cellWidth*x, cellHeight*y+2);
        cout << char(192) << char(196) << char(196) << char(196) << char(217);        
    }
}
void drawCell(char** map, int x, int y, int xCur, int yCur, int xPick, int yPick) {
    if (x == xCur && y == yCur) {
        drawBox(map[y][x], x, y, 15, true); // 15 -> Bright White
    } else if (map[y][x] != ' ') {
        if (x == xPick && y == yPick) {
            drawBox(map[y][x], x, y, 7, true); // 7 -> White
        } else {
            if (map[y][x] == 'G') {
                drawBox(map[y][x], x, y, 13, false); // G -> 7 -> White -> 13 -> Light Purple
            } else if (map[y][x] == 'H') {
                drawBox(map[y][x], x, y, 14, false); // H -> 8 -> Gray -> 14 -> Light Yellow
            } else {
                drawBox(map[y][x], x, y, (int) map[y][x] - 64, false);
            }
        }
    } else {
        GoTo(cellWidth*x, cellHeight*y);
        cout << "     ";
        GoTo(cellWidth*x, cellHeight*y+1);
        cout << "     ";
        GoTo(cellWidth*x, cellHeight*y+2);
        cout << "     ";
    }
}


// Level's feature

void Normal(char** map, int xCur, int yCur, int xPick, int yPick) {
    for (int y=0; y<mapHeight; y++) {
        for (int x=0; x<mapWidth; x++) {
            drawCell(map, x, y, xCur, yCur, xPick, yPick);
        }
    }
}