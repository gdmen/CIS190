#pragma once

#include "Constants.h"
#include "PlayerModel.h"
#include "UnitModel.h"
#include "BuildingModel.h"
#include "BaseModel.h"
#include "HeadquartersModel.h"
#include "CityModel.h"
#include "InfantryModel.h"
#include "ArtilleryModel.h"
#include "TankModel.h"
#include "MechModel.h"

class GameMapModel{
	public:
		GameMapModel(PlayerModel* p1, PlayerModel* p2, PlayerModel* neutral);
		Terrain_Enum terrain[MAP_HEIGHT][MAP_WIDTH];
		
		UnitModel* units[MAP_HEIGHT][MAP_WIDTH];
		BuildingModel* buildings[MAP_HEIGHT][MAP_WIDTH];
		
		bool highlighted[MAP_HEIGHT][MAP_WIDTH];
		// highlight in red when in the second stage of attacking
		// (if move-and-attacked, and there is a choice of whom to attack)
		bool attack[MAP_HEIGHT][MAP_WIDTH];

		void setSelected(int row, int col);
		int getRowSelected();
		int getColSelected();

		void populateTerrain();
		void populateUnits();
		void populateBuildings(PlayerModel* p1, PlayerModel* p2, PlayerModel* neutral);
		void populateHighlighted();
		void populateAttack();

	private:
		int row_selected, col_selected;
};
