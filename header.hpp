#include <iostream>
#include <windows.h>
#include <conio.h>

#define keyUp 72
#define keyDown 80
#define keyLeft 75
#define keyRight 77
#define keyEnter 13
#define keyEsc 27

using namespace std;

// Forward Declarations
void MenuController(int &option);
void displayMainMenu(int &option);

void AuthController(int &option);
void displayAuthMenu(int &option);

void LevelController(int &option);
void displayLevelMenu(int &option);

// Code
#include "console/console.cpp"

#include "controllers/menuController.cpp"
#include "controllers/authController.cpp"
#include "controllers/levelController.cpp"