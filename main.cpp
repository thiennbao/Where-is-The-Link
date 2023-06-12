#include "header.hpp"
int main() {

    // Console settings
    ShowCur(false);
    SetConsoleTitle(TEXT("Where's The Link"));

    // Game
    Player player;
    int level = 0;

    string page = "menu";
    while (true) {
        system("cls");
        if (page == "menu") {
            displayMainMenu(page, player);
        } else if (page == "leaderboard") {
            displayLeaderBoard(page);
        } else if (page == "help") {
            displayHelp(page);
        } else if (page == "quit") {
            displayQuitConfirm(page);
        } else if (page == "auth") {
            displayAuthMenu(page);
        } else if (page == "login") {
            displayLoginForm(page, player);
        } else if (page == "signup") {
            displaySignupForm(page, player);
        } else if (page == "after auth") {
            displayAfterAuthMenu(page, player);
        } else if (page == "level") {
            displayLevelMenu(page, level, player.level);
        } else if (page == "play") {
            Play(page, level, player);
        } else if (page == "exit") {
            return 0;
        }
    }
}