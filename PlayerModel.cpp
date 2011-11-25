#include "precomp.h"
#include "PlayerModel.h"

PlayerModel::PlayerModel(string name, int num){
	this->name = name;
	this->num = num;
	this->wealth = 0;
}
string PlayerModel::getName(){
	return name;
}

int PlayerModel::number(){
	return num;
}
void PlayerModel::addBuilding(BuildingModel* b){
	buildings.push_back(b);
}
//sums income from all buildings
int PlayerModel::getWealth(){
	return wealth;
}

void PlayerModel::reduceWealth(int x){
	wealth-=x;
}
int PlayerModel::calculateIncome(){
	int sum = 0;
	for(unsigned int i = 0; i < buildings.size(); i++){
		sum += buildings.at(i)->getIncome();
	}
	return sum;
}

int PlayerModel::increaseWealth(){
	int income = calculateIncome();
	wealth+=income;
	return wealth;
}