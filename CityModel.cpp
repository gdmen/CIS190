#include "precomp.h"
#include "CityModel.h"

CityModel::CityModel(int income, PlayerModel* p)
: BuildingModel(income, p){
}
Building_Enum CityModel::getType(){
	return CITY;
}
