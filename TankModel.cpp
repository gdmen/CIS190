#include "precomp.h"
#include "TankModel.h"

TankModel::TankModel(PlayerModel* p)
: UnitModel(.9/*TODO: edit strength modifiers*/,
			6,
			TANK,
			p,
			1,
			1){
	terrain_movement_mapping[ROAD] = 1;
	terrain_movement_mapping[ROAD2] = 1;
	terrain_movement_mapping[ROAD_UL] = 1;
	terrain_movement_mapping[ROAD_UR] = 1;
	terrain_movement_mapping[ROAD_LL] = 1;
	terrain_movement_mapping[ROAD_LR] = 1;
	terrain_movement_mapping[PLAIN] = 2;
	terrain_movement_mapping[MOUNTAIN] = 10;
}
