#include "precomp.h"
#include "GameController.h"

GameController::GameController(PlayerModel* p1, PlayerModel* p2, GameMapModel* map){
	this->p1 = p1;
	this->p2 = p2;
	this->map = map;
}
void GameController::selectSquare(int row, int col){
	UnitModel* unit = map->units[row][col];
	BuildingModel* building = map->buildings[row][col];
	if(building != NULL){
		if(building->getType() == BASE && ((BaseModel*)building)->canProduce()){
			//TODO:
			//GUI.displayBaseMenu();
		}
	}else if(unit != NULL){
		if(unit->canMove()){
			//clear highlighted
			map->populateHighlighted();
			map->populateAttack();
			map->setSelected(row, col);
			setMoveHighlighted(row, col);
		}else{
			map->populateHighlighted();
			map->populateAttack();
			map->setSelected(-1,-1);
		}
	}else if(map->highlighted[row][col]){
		unit = map->units[map->getRowSelected()][map->getColSelected()];
		map->units[row][col] = unit;
		map->units[map->getRowSelected()][map->getColSelected()] = NULL;
		unit->moved();
		map->populateHighlighted();
		map->populateAttack();
		if(setAttackHighlighted(row, col)){
			//TODO:
			//GUI.displayUnitAttackMenu();
		}
	}else if(map->attack[row][col]){
		UnitModel* atk_unit = map->units[map->getRowSelected()][map->getColSelected()];
		attack(atk_unit, unit);
		bool continue_atk = true;
		if(atk_unit->getHealth() <= 0){
			map->units[map->getRowSelected()][map->getColSelected()] = NULL;
			continue_atk = false;
		} if(unit->getHealth() <= 0){
			map->units[row][col] = NULL;
			continue_atk = false;
		} if(continue_atk){
			attack(unit, atk_unit);
		}
	}else{
		//is random click
		map->populateHighlighted();
		map->populateAttack();
	}
}

void GameController::attack(UnitModel* attacker, UnitModel* defender){
	defender->reduceHealth(	(int)(attacker->getHealth() *
							attacker->getStrengthModifier()));
}
vector<Node*> GameController::generateGraph(){
	vector<Node*> graph;
	Node* reference_array[MAP_HEIGHT][MAP_WIDTH];
	for(int row = 0; row < MAP_HEIGHT; row++){
		for(int col = 0; col < MAP_WIDTH; col++){
			reference_array[row][col] = NULL;
			if(map->units[row][col] != NULL){
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
				if(row-1 >= 0){
					if(map->units[row-1][col] != NULL){
						n->neighbors.push_back(reference_array[row-1][col]);
					}
				} if(row+1 <= MAP_HEIGHT){
					if(map->units[row+1][col] != NULL){
						n->neighbors.push_back(reference_array[row+1][col]);
					}
				} if(col-1 >= 0){
					if(map->units[row][col-1] != NULL){
						n->neighbors.push_back(reference_array[row][col-1]);
					}
				} if(col+1 <= MAP_WIDTH){
					if(map->units[row][col+1] != NULL){
						n->neighbors.push_back(reference_array[row][col+1]);
					}
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

bool GameController::setMoveHighlighted(int row, int col){
	UnitModel* unit = map->units[map->getRowSelected()][map->getColSelected()];
	vector<Node*> graph = generateGraph();
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
		graph.erase(graph.begin() + u_index);
	}
	for(unsigned int i = 0; i < graph.size(); i++){
		Node* n = graph.at(i);
		if(n->distance < unit->getMoves()){
			map->highlighted[map->getRowSelected()][map->getColSelected()];
		}
	}
	return true;
}
bool GameController::setAttackHighlighted(int row, int col){
	if(row-1 >= 0){
		map->attack[row-1][col] = true;
	} if(row+1 <= MAP_HEIGHT){
		map->attack[row+1][col] = true;
	} if(col-1 >= 0){
		map->attack[row][col-1] = true;
	} if(col+1 <= MAP_WIDTH){
		map->attack[row][col+1] = true;
	}
	return true;
}