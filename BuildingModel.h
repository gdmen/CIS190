#pragma once

#include "PlayerModel.h"

class BuildingModel{
	public:
	  BuildingModel(int income, PlayerModel* p);
	  int getIncome();

	protected:
		int income;
		PlayerModel* p;
};
