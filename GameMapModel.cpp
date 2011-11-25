#include "precomp.h"
#include "GameMapModel.h"
GameMapModel::GameMapModel(PlayerModel* p1, PlayerModel* p2){
	populateTerrain();
	populateUnits();
	populateBuildings(p1,p2);
	populateHighlighted();
	populateAttack();


}
void GameMapModel::populateTerrain(){
	for(int i = 0; i<MAP_HEIGHT;++i)
			for(int j = 0;j<MAP_WIDTH;++j){
				terrain[i][j] = PLAIN;
				
			}
}
void GameMapModel::populateUnits(){
	for(int i = 0; i<MAP_HEIGHT;++i)
			for(int j = 0;j<MAP_WIDTH;++j)
				units[i][j] = NULL;
}
void GameMapModel::populateBuildings(PlayerModel* p1, PlayerModel* p2){
	for(int i = 0; i<MAP_HEIGHT;++i)
			for(int j = 0;j<MAP_WIDTH;++j)
				buildings[i][j] = NULL;
				
	buildings[0][0] = new HeadquartersModel(1000,p1);
	buildings[0][1] = new BaseModel(1000,p1);
	buildings[1][0] = new BaseModel(1000,p1);
	buildings[0][2] = new CityModel(1000,p1);
	buildings[2][0] = new CityModel(1000,p1);

	p1->addBuilding(buildings[0][0]);
	p1->addBuilding(buildings[0][1]);
	p1->addBuilding(buildings[1][0]);
	p1->addBuilding(buildings[0][2]);
	p1->addBuilding(buildings[2][0]);
	buildings[MAP_HEIGHT-1][MAP_WIDTH-1] = new HeadquartersModel(1000,p2);
	buildings[MAP_HEIGHT-1][MAP_WIDTH-2] = new BaseModel(1000,p2);
	buildings[MAP_HEIGHT-2][MAP_WIDTH-1] = new BaseModel(1000,p2);
	buildings[MAP_HEIGHT-3][MAP_WIDTH-1] = new CityModel(1000,p2);
	buildings[MAP_HEIGHT-1][MAP_WIDTH-3] = new CityModel(1000,p2);
	p2->addBuilding(buildings[MAP_HEIGHT-1][MAP_WIDTH-1]);
	p2->addBuilding(buildings[MAP_HEIGHT-1][MAP_WIDTH-2]);
	p2->addBuilding(buildings[MAP_HEIGHT-2][MAP_WIDTH-1]);
	p2->addBuilding(buildings[MAP_HEIGHT-3][MAP_WIDTH-1]);
	p2->addBuilding(buildings[MAP_HEIGHT-1][MAP_WIDTH-3]);
}
void GameMapModel::populateHighlighted(){
	for(int i = 0; i<MAP_HEIGHT;++i)
			for(int j = 0;j<MAP_WIDTH;++j){
				highlighted[i][j] = false;
				
			}
}
void GameMapModel::populateAttack(){
	for(int i = 0; i<MAP_HEIGHT;++i)
			for(int j = 0;j<MAP_WIDTH;++j){
				attack[i][j] = false;
				
			}
}