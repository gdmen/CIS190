#include "precomp.h"
#include "InfantryModel.h"

InfantryModel::InfantryModel(PlayerModel* p)
: UnitModel(0.5/*TODO: edit strength modifiers*/,
			3,
			INFANTRY,
			p,
			1,
			1){
	terrain_movement_mapping[ROAD] = 1;
	terrain_movement_mapping[ROAD2] = 1;
	terrain_movement_mapping[ROAD_UL] = 1;
	terrain_movement_mapping[ROAD_UR] = 1;
	terrain_movement_mapping[ROAD_LL] = 1;
	terrain_movement_mapping[ROAD_LR] = 1;
	terrain_movement_mapping[PLAIN] = 1;
	terrain_movement_mapping[MOUNTAIN] = 2;
}
