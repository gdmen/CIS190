#include "precomp.h"
#include "GameMapModel.h"
GameMapModel::GameMapModel(PlayerModel* p1, PlayerModel* p2, PlayerModel* neutral){
	populateTerrain();
	populateUnits();
	populateBuildings(p1,p2,neutral);
	populateHighlighted();
	populateAttack();


}
void GameMapModel::populateTerrain(){
	for(int i = 0; i<MAP_HEIGHT;++i)
			for(int j = 0;j<MAP_WIDTH;++j){
			
			 if((i == 1 || i == MAP_HEIGHT-2) && (j >= 1 && j <= MAP_WIDTH-2))
					terrain[i][j] = ROAD;
				else if 	((j == 1 || j == MAP_WIDTH-2)	&& (i >= 1 && i < MAP_HEIGHT-1))
					terrain[i][j] = ROAD2;
			else
				terrain[i][j] = PLAIN;
				
			}
		terrain[1][1] = ROAD_UL;
		terrain[1][MAP_WIDTH-2] = ROAD_UR;
		terrain[MAP_HEIGHT-2][1] = ROAD_LL;
		terrain[MAP_HEIGHT-2][MAP_WIDTH-2] = ROAD_LR;
		for(int m = 0; m < MAP_HEIGHT;++m)
			for(int n = MAP_WIDTH/2 -1;n<MAP_WIDTH/2+1; ++n)
				if(m!=1 && m!=MAP_HEIGHT-2)
					terrain[m][n] = MOUNTAIN;
	
}
void GameMapModel::populateUnits(){
	for(int i = 0; i<MAP_HEIGHT;++i)
			for(int j = 0;j<MAP_WIDTH;++j)
				units[i][j] = NULL;
}
void GameMapModel::populateBuildings(PlayerModel* p1, PlayerModel* p2, PlayerModel* neutral){
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

	buildings[2][2] = new CityModel(1000,neutral);
	buildings[2][MAP_WIDTH-3] = new CityModel(1000,neutral);
	buildings[MAP_HEIGHT-3][2] = new CityModel(1000,neutral);
	buildings[MAP_HEIGHT-3][MAP_WIDTH-3] = new CityModel(1000,neutral);
	buildings[MAP_HEIGHT/2-1][MAP_WIDTH/2-2] = new BaseModel(1000,neutral);
	buildings[MAP_HEIGHT/2][MAP_WIDTH/2-2] = new BaseModel(1000,neutral);
	buildings[MAP_HEIGHT/2-1][MAP_WIDTH/2+1] = new BaseModel(1000,neutral);
	buildings[MAP_HEIGHT/2][MAP_WIDTH/2+1] = new BaseModel(1000,neutral);
	buildings[0][MAP_WIDTH-1] = new BaseModel(1000,neutral);
	buildings[MAP_HEIGHT-1][0] = new BaseModel(1000,neutral);
	neutral->addBuilding(buildings[2][2]);
	neutral->addBuilding(buildings[2][MAP_WIDTH-3]);
	neutral->addBuilding(buildings[MAP_HEIGHT-3][2]);
	neutral->addBuilding(buildings[MAP_HEIGHT-3][MAP_WIDTH-3]);
	neutral->addBuilding(buildings[MAP_HEIGHT/2-1][MAP_WIDTH/2-2]);
	neutral->addBuilding(buildings[MAP_HEIGHT/2][MAP_WIDTH/2-2]);
	neutral->addBuilding(buildings[MAP_HEIGHT/2-1][MAP_WIDTH/2+1]);
	neutral->addBuilding(buildings[MAP_HEIGHT/2][MAP_WIDTH/2+1]);
	neutral->addBuilding(buildings[0][MAP_WIDTH-1]);
	neutral->addBuilding(buildings[MAP_HEIGHT-1][0]);
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
void GameMapModel::setSelected(int row, int col){
	row_selected = row;
	col_selected = col;
}
int GameMapModel::getRowSelected(){
	return row_selected;
}
int GameMapModel::getColSelected(){
	return col_selected;
}