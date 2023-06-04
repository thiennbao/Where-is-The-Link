void SetWindowSize(SHORT width, SHORT height) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Right = width;
    WindowSize.Bottom = height;

    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}

void SetScreenBufferSize(SHORT width, SHORT height) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD NewSize;
    NewSize.X = width;
    NewSize.Y = height;

    SetConsoleScreenBufferSize(hStdout, NewSize);
}

void DisableResizeWindow() {
    HWND hWnd = GetConsoleWindow();
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) &~WS_SIZEBOX);
}

void DisableCtrlButton(bool Min, bool Max, bool Close) {
    HWND hWnd = GetConsoleWindow();
    HMENU hMenu = GetSystemMenu(hWnd, false);
    if (Min) {
        DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
    }
    if (Max) {
        DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
    }
    if (Close) {
        DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
    }
}

void DisableSelection() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

    SetConsoleMode(hStdin, ~ENABLE_QUICK_EDIT_MODE);
}

void ShowCur(bool CursorVisibility) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConCurInf;
    
    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = CursorVisibility;
    
    SetConsoleCursorInfo(handle, &ConCurInf);
}

void SetColor(char background_color, char text_color) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    int colorCode[16] = {
        4, 6, 2, 3, 1, 5, // A - B - C - D - E - F: Normal Red, Yellow, Green, Aqua, Blue, Purple
        12, 14, 10, 11, 9, 13, // G - H - I - J - K - L Light Red, Yellow, Green, Aqua, Blue, Purple
        0, 8, 7, 15 // M - N - O - P Black, Gray, White, Bright White   
    };
    
    int color_code = colorCode[background_color - 65] * 16 + colorCode[text_color - 65];

    SetConsoleTextAttribute(hStdout, color_code);
}

void GoTo(SHORT posX, SHORT posY) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = posX;
    Position.Y = posY;

    SetConsoleCursorPosition(hStdout, Position);
}

void ClearScreen() {
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}
