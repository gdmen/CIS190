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
		//sums income from all buildings
		int getIncome();

	protected:
		string name;
		vector<BuildingModel*> buildings;
};
