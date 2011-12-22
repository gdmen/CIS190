#include "precomp.h"
#include "MechModel.h"

MechModel::MechModel(PlayerModel* p)
: UnitModel(0.6/*TODO: edit strength modifiers*/,
			2,
			MECH,
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
	terrain_movement_mapping[MOUNTAIN] = 1;
}
