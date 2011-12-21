#include "precomp.h"
#include "ArtilleryModel.h"

ArtilleryModel::ArtilleryModel(PlayerModel* p)
: UnitModel(0.8/*TODO: edit strength modifiers*/,
			5,
			ARTILLERY,
			p){
	terrain_movement_mapping[ROAD] = 1;
	terrain_movement_mapping[PLAIN] = 2;
	terrain_movement_mapping[MOUNTAIN] = -1;
}
