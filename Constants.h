#pragma once

enum Terrain_Enum {ROAD, PLAIN, MOUNTAIN};
enum Unit_Enum {INFANTRY, MECH, ARTILLERY, TANK};
enum Building_Enum {HEADQUARTERS, BASE, CITY};
enum Menu_Enum {DEFAULT, ACTION, BUILD};


enum Cost_Enum {COST_INFANTRY = 1000, COST_MECH = 3000, COST_ARTILLERY = 7000, COST_TANK = 6000};

#define MENU_WIDTH 300
#define MENU_HEIGHT 210

#define WIDTH_OFFSET 7
#define HEIGHT_OFFSET 28
#define MAP_HEIGHT 5
#define MAP_WIDTH 10
#define MAX_DISTANCE (MAP_HEIGHT + MAP_WIDTH) * 2 //* 2 -> greatest terrain cost
#define PIECE_SIZE 32

#define INFANTRY_COST 1000
#define MECH_COST 3000
#define ARTILLERY_COST 6000
#define TANK_COST 7000