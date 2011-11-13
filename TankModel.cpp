#include "precomp.h"
#include "TankModel.h"

TankModel::TankModel(PlayerModel* p)
: UnitModel(1/*TODO: edit strength modifiers*/,
			6,
			TANK,
			p){
	terrain_movement_mapping[ROAD] = 1;
	terrain_movement_mapping[PLAIN] = 2;
	terrain_movement_mapping[MOUNTAIN] = -1;
}
