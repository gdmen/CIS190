#include "precomp.h"
#include "EventHandler.h"

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

void EventHandler::on_window_close()
{
	quit = true;
}

bool EventHandler::inMap(int row, int col){
	return row<MAP_HEIGHT && col <MAP_WIDTH;

}

bool EventHandler::isHighlighted(int row, int col){
	return map->highlighted[row][col];
}

bool EventHandler::canMove(int row, int col){
	if(map->units[row][col]!=NULL)
		return true;
	return false;
}

bool EventHandler::canBuild(int row, int col){
	BuildingModel* b = map->buildings[row][col];
	if(b && b->getType()==BASE && b->getPlayer()->number() == currentPlayer)
		return true;
	return false;
}

bool EventHandler::isQuit(int x, int y){
	return (x<150 && x>0 && y>180 && y<210);
}

bool EventHandler::endTurn(int x, int y){
	return (x>150 && x<300 && y>180 && y<210);
}

bool EventHandler::isWait(int x, int y){
	return (x>100 && x<200 && y>30 && y<60);
}

bool EventHandler::isAttack(int x, int y){
	return (x>100 && x<200 && y>60 && y<90);
}

bool EventHandler::isCapture(int x, int y){
	return (x>100 && x<200 && y>90 && y<120);
}

bool EventHandler::isInfantry(int x, int y){
	return (x>0 && x<150 && y>30 && y<60);
}

bool EventHandler::isMech(int x, int y){
	return (x>0 && x<150 && y>60 && y<90); 
}

bool EventHandler::isArtillery(int x, int y){
	return (x>0 && x<150 && y>90 && y<120);
}

bool EventHandler::isTank(int x, int y){
	return (x>0 && x<150 && y>120 && y<150);
}
void EventHandler::handleMenuMousePress(const CL_InputEvent &evt, const CL_InputState &state)
{
	CL_Point pt = evt.mouse_pos;
	int x = pt.x;
	int y = pt.y;
	std::string s;
	std::stringstream out;
	out << x << endl;
	s = out.str();
	wstring stemp = s2ws(s);
	LPCWSTR str = stemp.c_str();
	//OutputDebugString(str);
	if(endTurn(x,y)){
		if(currentPlayer == 1) currentPlayer = 2;
		else currentPlayer = 1;
		controller->resetForTurn(currentPlayer);
		newView->redrawStatus(p1->getWealth(),p2->getWealth());
		newView->showPlayer(currentPlayer);
		newView->redrawMap(map);
		newView->highlightArea(map->highlighted);
		newView->attackArea(map->attack);
		window->flip();
		menu_window->flip();
	}
	else if(isQuit(x,y)){
		quit = true;
	}
	else{

		switch(currentMenu){
			case BUILD:
				PlayerModel* curPlayer;
				if(currentPlayer == 1)
					curPlayer = p1;
				else
					curPlayer = p2;
				if(isInfantry(x,y) && curPlayer->getWealth()>=INFANTRY_COST){
					map->units[curRow][curCol] = new InfantryModel(curPlayer);
					curPlayer->reduceWealth(INFANTRY_COST);
				}
				else if(isMech(x,y) && curPlayer->getWealth()>=MECH_COST){
					map->units[curRow][curCol] = new MechModel(curPlayer);
					curPlayer->reduceWealth(MECH_COST);
				}
				else if(isArtillery(x,y) && curPlayer->getWealth()>=ARTILLERY_COST){
					map->units[curRow][curCol] = new ArtilleryModel(curPlayer);
					curPlayer->reduceWealth(ARTILLERY_COST);
				}
				else if(isTank(x,y) && curPlayer->getWealth()>=TANK_COST){
					map->units[curRow][curCol] = new TankModel(curPlayer);
					curPlayer->reduceWealth(TANK_COST);
				}
				else break;

				newView->redrawMap(map);
				window->flip();
				menu_window->get_gc().clear(CL_Colorf::white);
				newView->showPlayer(currentPlayer);
				newView->redrawStatus(p1->getWealth(),p2->getWealth());
				menu_window->flip();
				break;

			default:
				break;
		}

		//menu_window->flip();
	}
}
void EventHandler::handleMousePress(const CL_InputEvent &evt, const CL_InputState &state)
{
	CL_Point pt = evt.mouse_pos;
	int x = pt.x;
	int y = pt.y;

	std::string s;
	std::stringstream out;
	out << x << endl;
	s = out.str();
	wstring stemp = s2ws(s);
	LPCWSTR str = stemp.c_str();
	OutputDebugString(str);

	int col = x/PIECE_SIZE;
	int row = y/PIECE_SIZE;
	curRow = row;
	curCol = col;
	if(inMap(row,col)){
		currentMenu = controller->selectSquare(row, col, currentPlayer);
		
		
		newView->redrawStatus(p1->getWealth(),p2->getWealth());
		menu_window->flip();
		newView->redrawMap(map);
		newView->highlightArea(map->highlighted);
		newView->attackArea(map->attack);
		window->flip();
	}


}
void EventHandler::init(){
	currentPlayer = 1;
	p1->increaseWealth();

}
void EventHandler::run()
{
	quit = false;
	CL_DisplayWindowDescription menu_description("Menu");
	menu_description.set_position(CL_Rect(100,100,100+MENU_WIDTH+WIDTH_OFFSET,100+MENU_HEIGHT+HEIGHT_OFFSET),false);
	window = new CL_DisplayWindow("Game Map",MAP_WIDTH*PIECE_SIZE+WIDTH_OFFSET, MAP_HEIGHT*PIECE_SIZE+HEIGHT_OFFSET);
	menu_window = new CL_DisplayWindow(menu_description);
	CL_InputContext ic = window->get_ic();
	CL_InputDevice mouse = ic.get_mouse();

	CL_InputContext menu_ic = menu_window->get_ic();
	CL_InputDevice menu_mouse = menu_ic.get_mouse();
	menu_mousepress =menu_mouse.sig_key_down().connect(this,&EventHandler::handleMenuMousePress);

	CL_Slot slot_quit = window->sig_window_close().connect(this, &EventHandler::on_window_close);
	mousepress =mouse.sig_key_down().connect(this,&EventHandler::handleMousePress);
	CL_GraphicContext gc = window->get_gc();
	CL_GraphicContext menu_gc = menu_window->get_gc();
	CL_InputDevice keyboard = window->get_ic().get_keyboard();
	p1 = new PlayerModel("Bob",1);
	p2 = new PlayerModel("Alice",2);
	neutral = new PlayerModel("Neutral",0);
	map = new GameMapModel(p1,p2,neutral);
	init();
	newView = new View(map,gc,menu_gc,p1->getWealth(),p2->getWealth());
	controller = new GameController(p1, p2, neutral, map, newView);
	window->flip();
	menu_window->flip();


	while (!quit)
	{
		if(keyboard.get_keycode(CL_KEY_ESCAPE) == true)
			quit = true;

		CL_KeepAlive::process();

		CL_System::sleep(10);
	}
}