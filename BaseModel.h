#pragma once

#include "BuildingModel.h"

class BaseModel: public BuildingModel{
	public:
		BaseModel(int income, PlayerModel* p);
    bool canProduce();
    void resetProduction();
    
  private:
    bool can_produce;
};
