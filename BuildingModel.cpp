#include "precomp.h"
#include "BuildingModel.h"
#include "PlayerModel.h"

BuildingModel::BuildingModel(int income, PlayerModel* p){
	this->income = income;
	this->player = p;
}
int BuildingModel::getIncome(){
	return income;
}
PlayerModel* BuildingModel::getPlayer(){
	return player;
}