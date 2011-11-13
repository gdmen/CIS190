#pragma once

#include "BuildingModel.h"

class HeadquartersModel: public BuildingModel{
	public:
		HeadquartersModel(int income, PlayerModel* p);
		Building_Enum getType();
};
