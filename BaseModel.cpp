#include "precomp.h"
#include "BaseModel.h"

BaseModel::BaseModel(int income, PlayerModel* p)
: BuildingModel(income, p){
}
Building_Enum BaseModel::getType(){
	return BASE;
}
