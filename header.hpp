#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <cstring>

#define keyUp 72
#define keyDown 80
#define keyLeft 75
#define keyRight 77
#define keyEnter 13
#define keyEsc 27

using namespace std;

// Util
#include "console/console.cpp"
#include "account/account.cpp"
#include "game/matching.cpp"

// Forward Declarations
void MenuController(int &option);
void displayMainMenu(int &option);

void AuthController(int &option, Player &player);
void displayAuthMenu(int &option);
void loginForm(Player &player);
void signupForm(Player &player);
void displayAfterAuthMenu(int &option);

void LevelController(int &option);
void displayLevelMenu(int &option);

// Code
#include "controllers/menuController.cpp"
#include "controllers/authController.cpp"
#include "controllers/levelController.cpp"