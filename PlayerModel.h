#pragma once

#include <string>
#include <vector>
#include "BuildingModel.h"
using namespace std;

class PlayerModel{
	public:
		PlayerModel(string name, int num);
		string getName();
		int number();
		void addBuilding(BuildingModel* b);
		void removeBuilding(BuildingModel* b);
		//sums income from all buildings
		int getWealth();
		int calculateIncome();
		int increaseWealth();
		void reduceWealth(int x);

	protected:
		string name;
		int num;
		int wealth;
		vector<BuildingModel*> buildings;
};
