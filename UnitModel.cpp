#include "UnitModel.h"

UnitModel::UnitModel(double strength_modifier, int moves, Unit_Enum type, PlayerModel* p){
	this->strength_modifier = strength_modifier;
	this->moves = moves;
	this->type = type;
	this->player = p;
	this->health = 10;
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
void UnitModel::reduceMoves(int num_moves){
	moves -= num_moves;
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
PlayerModel* UnitModel::getPlayer(){
	return player;
}
