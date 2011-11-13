#pragma once

class PlayerModel;
#include "Enums.h"

class BuildingModel{
	public:
		BuildingModel(Building_Enum type, int income, PlayerModel* p);
		int getIncome();
		PlayerModel* getPlayer();
		Building_Enum getType();

	private:
		PlayerModel* player;
		int income;
		Building_Enum type;
};
