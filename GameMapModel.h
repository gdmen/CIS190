#pragma once

#include "Enums.h"
#include "PlayerModel.h"
#include "UnitModel.h"
#include "BuildingModel.h"

class GameMapModel{
	public:
		GameMapModel();
		Terrain_Enum terrain[10][10];
		/*
		UnitModel units[10][10];
		BuildingModel buildings[10][10];
		*/
		bool highlighted[10][10];
		// highlight in red when in the second stage of attacking
		// (if move-and-attacked, and there is a choice of whom to attack)
		bool attack[10][10];

	private:
		void populateTerrain();
		void populateUnits();
		void populateBuildings();
		void populateHighlighted();
		void populateAttack();
};
