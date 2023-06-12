#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <time.h>

#define windowWidth 120
#define windowHeight 30
#define xStart 20
#define yStart 15

#define keyUp 72
#define keyDown 80
#define keyLeft 75
#define keyRight 77
#define keyEnter 13
#define keyEsc 27

#define mapWidth 18
#define mapHeight 10
#define charNum 12
#define cellWidth 5
#define cellHeight 3

using namespace std;

#include "util/util.hpp"
#include "controllers/controllers.hpp"
#include "game/game.hpp"