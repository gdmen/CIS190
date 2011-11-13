#pragma once

#include <map>
#include "PlayerModel.h"
#include "Enums.h"

class UnitModel{
	public:
		UnitModel(double strength_modifier, int moves, Unit_Enum type, PlayerModel* p);
		int getHealth();
		void reduceHealth(int reduction);
		int getMoves();
		void reduceMoves(int num_moves);
		Unit_Enum getType();
		double getStrengthModifier();
		int getMovesNeeded(Terrain_Enum terrain);
		PlayerModel* getPlayer();

	protected:
		map<Terrain_Enum, int> terrain_movement_mapping;

	private:
		int health, moves;
		double strength_modifier;
		Unit_Enum type;
		PlayerModel* player;
};
