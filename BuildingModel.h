#pragma once

#include "PlayerModel.h"
#include "Enums.h"

class BuildingModel{
	public:
		BuildingModel(int income, PlayerModel* p);
		int getIncome();
		PlayerModel* getPlayer();
		virtual Building_Enum getType() = 0;

	private:
		PlayerModel* player;
		int income;
};
