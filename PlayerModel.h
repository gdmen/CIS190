#pragma once

#include <string>
#include <vector>
#include "BuildingModel.h"
using namespace std;

class PlayerModel{
	public:
	  PlayerModel(string name);
	  string getName();
	  void addBuilding(BuildingModel* b);

	protected:
	  string name;
	  vector<BuildingModel*> buildings;
};
