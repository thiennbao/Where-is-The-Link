#include "header.hpp"

int main() {

    // Console settings
    SetWindowSize(120, 30);
    SetScreenBufferSize(120, 30);
    DisableResizeWindow();
    DisableCtrlButton(false, true, false);
    DisableSelection();
    ShowCur(false);
    SetConsoleTitle(TEXT("Where's The Link"));

    getch();
    return 0;
}