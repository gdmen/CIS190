#pragma once

#include "BuildingModel.h"
#include "UnitModel.h"
#include "GameMapModel.h"
#include "PlayerModel.h"
#include "Constants.h"
#include <algorithm>
#include <vector>

using namespace std;

class Node{
	public:
		vector<Node*> neighbors;
		int row;
		int col;
		int distance;
		Node* previous;
};
class GameController{
	public:
		GameController(PlayerModel* p1, PlayerModel* p2, GameMapModel* map);
		void selectSquare(int row, int col);

	private:
		PlayerModel* p1;
		PlayerModel* p2;
		GameMapModel* map;
		void attack(UnitModel* attacker, UnitModel* defender);
		bool setMoveHighlighted(int row, int col);
		bool setAttackHighlighted(int row, int col);
		vector<Node*> generateGraph();
};