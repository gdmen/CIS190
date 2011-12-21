#include "precomp.h"
#include "BuildingModel.h"
#include "PlayerModel.h"

BuildingModel::BuildingModel(Building_Enum type, int income, PlayerModel* p){
	this->income = income;
	this->player = p;
	this->type = type;
}
int BuildingModel::getIncome(){
	return income;
}
PlayerModel* BuildingModel::getPlayer(){
	return player;
}
void BuildingModel::setPlayer(PlayerModel* p){
	this->player = p;
}
Building_Enum BuildingModel::getType(){
	return type;
}