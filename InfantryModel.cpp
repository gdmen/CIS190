#include "InfantryModel.h"

InfantryModel::InfantryModel(PlayerModel* p)
: UnitModel(1/*TODO: edit strength modifiers*/,
			3,
			INFANTRY,
			p){
	terrain_movement_mapping[ROAD] = 1;
	terrain_movement_mapping[PLAIN] = 1;
	terrain_movement_mapping[MOUNTAIN] = 2;
}
