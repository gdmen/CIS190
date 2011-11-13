#pragma once

#include "BuildingModel.h"

class BaseModel: public BuildingModel{
	public:
		BaseModel(int income, PlayerModel* p);
		Building_Enum getType();
};
