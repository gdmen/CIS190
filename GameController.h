#pragma once

#include "BuildingModel.h"
#include "UnitModel.h"
#include "GameMapModel.h"
#include "PlayerModel.h"
#include "Constants.h"
#include "View.h"
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
		GameController(PlayerModel* p1, PlayerModel* p2, PlayerModel* neutral, GameMapModel* map, View* view);
		Menu_Enum selectSquare(int row, int col, int current_player);
		void resetForTurn(int current_player);
	private:
		PlayerModel* p1;
		PlayerModel* p2;
		PlayerModel* neutral;
		GameMapModel* map;
		View* view;
		void attack(UnitModel* attacker, UnitModel* defender);
		bool setMoveHighlighted(int row, int col, int current_player);
		bool setAttackHighlighted(int row, int col, int current_player);
		void resetUnits();
		vector<Node*> generateGraph(int current_player);
};