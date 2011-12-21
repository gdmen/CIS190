#pragma once

#include <map>
#include "PlayerModel.h"
#include "Constants.h"

class UnitModel{
	public:
		UnitModel();
		UnitModel(double strength_modifier, int moves, Unit_Enum type, PlayerModel* p, int minRange, int maxRange);
		int getMinRange();
		int getMaxRange();
		int getHealth();
		void reduceHealth(int reduction);
		int getMoves();
		Unit_Enum getType();
		double getStrengthModifier();
		int getMovesNeeded(Terrain_Enum terrain);
		bool canMove();
		void moved();
		PlayerModel* getPlayer();
		bool hasMoved;

	protected:
		map<Terrain_Enum, int> terrain_movement_mapping;

	private:
		int health, moves, minRange, maxRange;
		double strength_modifier;
		Unit_Enum type;
		PlayerModel* player;
};
