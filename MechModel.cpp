#include "precomp.h"
#include "MechModel.h"

MechModel::MechModel(PlayerModel* p)
: UnitModel(0.6/*TODO: edit strength modifiers*/,
			2,
			MECH,
			p){
	terrain_movement_mapping[ROAD] = 1;
	terrain_movement_mapping[PLAIN] = 1;
	terrain_movement_mapping[MOUNTAIN] = 2;
}
