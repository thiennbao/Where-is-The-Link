#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <time.h>

#define keyUp 72
#define keyDown 80
#define keyLeft 75
#define keyRight 77
#define keyEnter 13
#define keyEsc 27

#define mapWidth 6
#define mapHeight 6
#define charNum 4
#define cellWidth 5
#define cellHeight 3

using namespace std;

// Util
#include "console/console.cpp"
#include "account/account.cpp"
#include "game/matching.cpp"
#include "game/level.cpp"
#include "game/play.cpp"

// Forward Declarations
void MenuController(int &option);
void displayMainMenu(int &option);

void AuthController(int &option, Player &player);
void displayAuthMenu(int &option);
void loginForm(Player &player);
void signupForm(Player &player);
void displayAfterAuthMenu(int &option);

void LevelController(int &option, Player &player);
void displayLevelMenu(int &option, int level);

// Code
#include "controllers/menuController.cpp"
#include "controllers/authController.cpp"
#include "controllers/levelController.cpp"