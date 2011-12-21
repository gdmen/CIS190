#include "precomp.h"
#include "GameController.h"

GameController::GameController(PlayerModel* p1, PlayerModel* p2, PlayerModel* neutral, GameMapModel* map, View* view){
	this->p1 = p1;
	this->p2 = p2;
	this->neutral = neutral;
	this->map = map;
	this->view = view;
}

bool GameController::hasWon(int current_player){
	int otherPlayer;
	if(current_player == 1) otherPlayer = 2;
	else otherPlayer = 1;
	int canProduce = 0;
	int numUnits = 0;
	int numHQ = 0;
	for(int i = 0; i < MAP_HEIGHT; ++i){
		for(int j = 0; j < MAP_WIDTH; ++j){
			if(map->buildings[i][j]){
				if(map->buildings[i][j]->getType() == HEADQUARTERS && map->buildings[i][j]->getPlayer()->number()==current_player){
					numHQ++;
					if(numHQ>1) return true;
				}
				if(map->buildings[i][j]->getType() == BASE && map->buildings[i][j]->getPlayer()->number() == otherPlayer)
					canProduce++;
				}
			if(map->units[i][j] && map->units[i][j]->getPlayer()->number() == otherPlayer)
				numUnits++;
		}
	}
	return (canProduce == 0 && numUnits == 0);				
}

void GameController::resetForTurn(int current_player){
	resetUnits();
	if(current_player == 1){
		p1->increaseWealth();
	}else if(current_player == 2){
		p2->increaseWealth();
	}
	map->populateHighlighted();
	map->populateAttack();
}
void GameController::resetUnits(){
	for(int row = 0; row < MAP_HEIGHT; row++){
		for(int col = 0; col < MAP_WIDTH; col++){
			UnitModel* unit = map->units[row][col];
			if(unit != NULL){
				unit->hasMoved = false;
			}
		}
	}
}
Menu_Enum GameController::selectSquare(int row, int col, int current_player){
	Menu_Enum menu_type = DEFAULT;
	UnitModel* unit = map->units[row][col];
	BuildingModel* building = map->buildings[row][col];
	if(unit != NULL && unit->getPlayer()->number() == current_player){
		if(unit->canMove()){
			//clear highlighted
			map->populateHighlighted();
			map->populateAttack();
			map->setSelected(row, col);
			setMoveHighlighted(row, col, current_player);
			setAttackHighlighted(row, col, current_player);
		}else{
			map->populateHighlighted();
			map->populateAttack();
			map->setSelected(-1,-1);
		}
	}else if(map->highlighted[row][col] && (building == NULL || (building->getPlayer()->number() != current_player || building->getType() != BASE))){
		if(map->getRowSelected() >= 0){
			unit = map->units[map->getRowSelected()][map->getColSelected()];
			if(unit != NULL && unit->canMove()){
				map->units[row][col] = unit;
				map->units[map->getRowSelected()][map->getColSelected()] = NULL;
				unit->moved();
				map->populateHighlighted();
				map->populateAttack();
				setAttackHighlighted(row, col, current_player);
				map->setSelected(row, col);
				view->showPlayer(current_player);
				return menu_type;
			}
		}
	}else if(map->attack[row][col]){
		map->populateHighlighted();
		map->populateAttack();
		UnitModel* atk_unit = map->units[map->getRowSelected()][map->getColSelected()];
		if(unit != NULL){
			atk_unit->moved();
			attack(atk_unit, unit);
			bool continue_atk = true;
			if(atk_unit->getHealth() <= 0){
				map->units[map->getRowSelected()][map->getColSelected()] = NULL;
				continue_atk = false;
			}if(unit->getHealth() <= 0){
				map->units[row][col] = NULL;
				continue_atk = false;
			}if(continue_atk &&
				(atk_unit->getType() != ARTILLERY && unit->getType() != ARTILLERY
				|| atk_unit->getType() == ARTILLERY && unit->getType() == ARTILLERY)){
				attack(unit, atk_unit);
				if(atk_unit->getHealth() <= 0){
					map->units[map->getRowSelected()][map->getColSelected()] = NULL;
				}if(unit->getHealth() <= 0){
					map->units[row][col] = NULL;
				}
			}
		}else if(building != NULL){
			capture(atk_unit, building, row, col);
		}
	}else if(building != NULL){
		map->populateHighlighted();
		map->populateAttack();
		if(building && building->getType() == BASE && building->getPlayer()->number() == current_player){
			view->showBuildMenu();
			menu_type = BUILD;
		}
		map->setSelected(-1,-1);
	}else{
		//is random click
		map->populateHighlighted();
		map->populateAttack();
		map->setSelected(-1,-1);
	}
	map->highlighted[row][col] = true;
	if(menu_type == DEFAULT){
		view->showPlayer(current_player);
	}
	return menu_type;
}

void GameController::attack(UnitModel* attacker, UnitModel* defender){
	if(attacker != NULL && defender != NULL){
		defender->reduceHealth(	(int)(attacker->getHealth() * attacker->getStrengthModifier()));
	}
}
void GameController::capture(UnitModel* attacker, BuildingModel* building, int row, int col){
	if(attacker != NULL && building != NULL){
		map->units[row][col] = attacker;
		map->units[map->getRowSelected()][map->getColSelected()] = NULL;
		attacker->moved();
		map->populateHighlighted();
		map->populateAttack();
		if(attacker->getType() != TANK || attacker->getType() != ARTILLERY){
			building->getPlayer()->removeBuilding(building);
			building->setPlayer(attacker->getPlayer());
			attacker->getPlayer()->addBuilding(building);
		}
	}
}
vector<Node*> GameController::generateGraph(int current_player){
	vector<Node*> graph;
	Node* reference_array[MAP_HEIGHT][MAP_WIDTH];
	for(int row = 0; row < MAP_HEIGHT; row++){
		for(int col = 0; col < MAP_WIDTH; col++){
			reference_array[row][col] = NULL;
			if(map->units[row][col] != NULL && (map->getRowSelected() != row || map->getColSelected() != col)){
				reference_array[row][col] = NULL;
			}else{
				Node* n = new Node();
				n->row = row;
				n->col = col;
				n->distance = MAX_DISTANCE;
				n->previous = NULL;
				reference_array[row][col] = n;
			}
		}
	}
	
	reference_array[map->getRowSelected()][map->getColSelected()]->distance = 0;

	for(int row = 0; row < MAP_HEIGHT; row++){
		for(int col = 0; col < MAP_WIDTH; col++){
			Node* n = reference_array[row][col];
			if(n != NULL){
				graph.push_back(n);
				if(row-1 >= 0 && reference_array[row-1][col] != NULL){
					n->neighbors.push_back(reference_array[row-1][col]);
				} if(row+1 < MAP_HEIGHT && reference_array[row+1][col] != NULL){
					n->neighbors.push_back(reference_array[row+1][col]);
				} if(col-1 >= 0 && reference_array[row][col-1] != NULL){
					n->neighbors.push_back(reference_array[row][col-1]);
				} if(col+1 < MAP_WIDTH && reference_array[row][col+1] != NULL){
					n->neighbors.push_back(reference_array[row][col+1]);
				}
			}
		}
	}
	return graph;
}

int getSmallestDistanceIndex(vector<Node*> graph){
	int index = -1;
	int min_distance = MAX_DISTANCE;
	for(unsigned int i = 0; i < graph.size(); i++){
		Node* n = graph.at(i);
		if(n->distance <= min_distance){
			min_distance = n->distance;
			index = i;
		}
	}
	return index;
}

bool GameController::setMoveHighlighted(int row, int col, int current_player){
	UnitModel* unit = map->units[map->getRowSelected()][map->getColSelected()];
	vector<Node*> graph = generateGraph(current_player);
	vector<Node*> result;
	while(graph.size() > 0){
		int u_index = getSmallestDistanceIndex(graph);
		Node* u = graph.at(u_index);
		if(u->distance == MAX_DISTANCE){
			break;
		}
		vector<Node*> neighbors = u->neighbors;
		for(unsigned int i = 0; i < neighbors.size(); i++){
			Node* v = neighbors.at(i);
			int alt = u->distance + unit->
									getMovesNeeded(map->terrain[v->row][v->col]);
			if(alt < v->distance){
				v->distance = alt;
				v->previous = u;
			}
		}
		result.push_back(graph.at(u_index));
		graph.erase(graph.begin() + u_index);
	}
	for(unsigned int i = 0; i < result.size(); i++){
		Node* n = result.at(i);
		if(n->distance <= unit->getMoves()){
			if(map->buildings[n->row][n->col] != NULL && map->buildings[n->row][n->col]->getPlayer()->number() != current_player){
				if(unit->getType() != TANK && unit->getType() != ARTILLERY){
					map->attack[n->row][n->col] = true;
				}else{
					map->highlighted[n->row][n->col] = true;
				}
			}else{
				map->highlighted[n->row][n->col] = true;
			}
		}
	}
	return true;
}
bool GameController::setAttackHighlighted(int row, int col, int current_player){
	UnitModel* unit = map->units[row][col];
	if(unit->getType() != ARTILLERY){
		if(row-1 >= 0){
			if(map->units[row-1][col] != NULL && map->units[row-1][col]->getPlayer()->number() != current_player)// ||
				//map->buildings[row-1][col] != NULL && map->buildings[row-1][col]->getPlayer()->number() != current_player)
				map->attack[row-1][col] = true;
		} if(row+1 < MAP_HEIGHT){
			if(map->units[row+1][col] != NULL && map->units[row+1][col]->getPlayer()->number() != current_player)// ||
				//map->buildings[row+1][col] != NULL && map->buildings[row+1][col]->getPlayer()->number() != current_player)
				map->attack[row+1][col] = true;
		} if(col-1 >= 0){
			if(map->units[row][col-1] != NULL && map->units[row][col-1]->getPlayer()->number() != current_player)// ||
				//map->buildings[row][col-1] != NULL && map->buildings[row][col-1]->getPlayer()->number() != current_player)
				map->attack[row][col-1] = true;
		} if(col+1 < MAP_WIDTH){
			if(map->units[row][col+1] != NULL && map->units[row][col+1]->getPlayer()->number() != current_player)// ||
				//map->buildings[row][col+1] != NULL && map->buildings[row][col+1]->getPlayer()->number() != current_player)
				map->attack[row][col+1]= true;
		}
	}else{
		for(int r = 0; r < MAP_HEIGHT; r++){
			for(int c = 0; c < MAP_WIDTH; c++){
				if(abs(r-row) + abs(c-col) >= unit->getMinRange() && abs(r-row) + abs(c-col) <= unit->getMaxRange()
					&& map->units[r][c] != NULL && map->units[r][c]->getPlayer()->number() != current_player){
					map->attack[r][c]= true;
				}
			}
		}
	}
	return true;
}