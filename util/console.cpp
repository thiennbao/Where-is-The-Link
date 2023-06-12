
void ShowCur(bool CursorVisibility) {
    CONSOLE_CURSOR_INFO ConCurInf = {10, CursorVisibility};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConCurInf);
}

void SetColor(char background_color, char text_color) {
    int colorCode[16] = {
        4, 6, 2, 3, 1, 5, // A - B - C - D - E - F: Normal Red, Yellow, Green, Aqua, Blue, Purple
        12, 14, 10, 11, 9, 13, // G - H - I - J - K - L Light Red, Yellow, Green, Aqua, Blue, Purple
        0, 8, 7, 15 // M - N - O - P Black, Gray, White, Bright White   
    };
    int color_code = colorCode[background_color - 65] * 16 + colorCode[text_color - 65];
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_code);
}

void GoTo(SHORT posX, SHORT posY) {
    COORD Position = {posX, posY};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position);
}