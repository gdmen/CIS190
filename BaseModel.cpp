#include "precomp.h"
#include "BaseModel.h"

BaseModel::BaseModel(int income, PlayerModel* p)
: BuildingModel(BASE, income, p){
  can_produce = true;
}
bool BaseModel::canProduce(){
  if(can_produce){
    can_produce = false;
    return true;
  }
  return false;
}
void BaseModel::resetProduction(){
  can_produce = true;
}
