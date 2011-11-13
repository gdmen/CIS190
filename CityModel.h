#pragma once

#include "BuildingModel.h"

class CityModel: public BuildingModel{
	public:
		CityModel(int income, PlayerModel* p);
};
