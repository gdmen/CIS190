#include "precomp.h"
#include "ArtilleryModel.h"

ArtilleryModel::ArtilleryModel(PlayerModel* p)
: UnitModel(0.8/*TODO: edit strength modifiers*/,
			5,
			ARTILLERY,
			p,
			2,
			3){
	terrain_movement_mapping[ROAD] = 1;
	terrain_movement_mapping[ROAD2] = 1;
	terrain_movement_mapping[ROAD_UL] = 1;
	terrain_movement_mapping[ROAD_UR] = 1;
	terrain_movement_mapping[ROAD_LL] = 1;
	terrain_movement_mapping[ROAD_LR] = 1;
	terrain_movement_mapping[PLAIN] = 2;
	terrain_movement_mapping[MOUNTAIN] = 10;
}
