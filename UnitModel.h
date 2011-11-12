#pragma once

#include "PlayerModel.h"

class UnitModel{
	//TODO: add terrain : movement mapping
	public:
	  UnitModel(int damage, int health, int moves, PlayerModel* p);
	  
	  int getDamage();
	  int getHealth();
	  void reduceHealth(int reduction);
	  int getMoves();
	  void move(int num_moves);

	protected:
	  int damage, health, moves;
	  PlayerModel* p;
};
