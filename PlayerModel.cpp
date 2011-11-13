#include "precomp.h"
#include "PlayerModel.h"

PlayerModel::PlayerModel(string name){
	this->name = name;
}
string PlayerModel::getName(){
	return name;
}
void PlayerModel::addBuilding(BuildingModel* b){
	buildings.push_back(b);
}
//sums income from all buildings
int PlayerModel::getIncome(){
	int income = 0;
	for(unsigned int i = 0; i < buildings.size(); i++){
		income += buildings.at(i)->getIncome();
	}
	return income;
}
