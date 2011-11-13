#include "HeadquartersModel.h"

HeadquartersModel::HeadquartersModel(int income, PlayerModel* p)
: BuildingModel(income, p){
}
Building_Enum HeadquartersModel::getType(){
	return HEADQUARTERS;
}
