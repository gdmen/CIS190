#include "precomp.h"
#include "UnitModel.h"

UnitModel::UnitModel(double strength_modifier, int moves, Unit_Enum type, PlayerModel* p, int minRange, int maxRange){
	this->strength_modifier = strength_modifier;
	this->moves = moves;
	this->type = type;
	this->player = p;
	this->health = 10;
	this->hasMoved = true;
	this->minRange = minRange;
	this->maxRange = maxRange;
}
int UnitModel::getMinRange(){
	return minRange;
}
int UnitModel::getMaxRange(){
	return maxRange;
}
int UnitModel::getHealth(){
	return health;
}
void UnitModel::reduceHealth(int reduction){
	health -= reduction;
}
int UnitModel::getMoves(){
	return moves;
}
Unit_Enum UnitModel::getType(){
	return type;
}
double UnitModel::getStrengthModifier(){
	return strength_modifier;
}
int UnitModel::getMovesNeeded(Terrain_Enum terrain){
	return terrain_movement_mapping[terrain];
}
bool UnitModel::canMove(){
	return !hasMoved;
}
void UnitModel::moved(){
	hasMoved = true;
}
PlayerModel* UnitModel::getPlayer(){
	return player;
}
