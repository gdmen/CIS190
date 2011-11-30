#include "precomp.h"
#include "Constants.h"
#include <iostream>
#include <Windows.h>
#include "GameMapModel.h"
#include <sstream>
using namespace std;

/*
TODO:
VIEW receives: an array of Terrains, Buildings, Units, and bool places to HighLight
*/


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

class View
{
private:
	Terrain_Enum terrains[MAP_HEIGHT][MAP_WIDTH];
	//UnitModel* units[MAP_HEIGHT][MAP_WIDTH];
	//BuildingModel* buildings[MAP_HEIGHT][MAP_WIDTH];
	CL_Rect rect;
	CL_GraphicContext gc;
	CL_GraphicContext menu_gc;


public:
	View(GameMapModel* map,  CL_GraphicContext& _gc, CL_GraphicContext& _menugc, int p1, int p2){
		gc = _gc;
		menu_gc = _menugc;

		rect = CL_Rect(0,0,PIECE_SIZE,PIECE_SIZE);
		drawTerrain(map->terrain);
		drawBuildings(map->buildings);
		drawUnits(map->units);
		showPlayer(1);
		showButtons();
		showScore(p1,p2);

	}

	void drawTerrain(Terrain_Enum terrains[MAP_HEIGHT][MAP_WIDTH]){
		CL_PixelBuffer plain = CL_PNGProvider::load("tiles/plain.png");
		CL_PixelBuffer mountain = CL_PNGProvider::load("tiles/mountain1.png");
		CL_PixelBuffer road = CL_PNGProvider::load("tiles/road_h.png");

		for(int i = 0;i < MAP_HEIGHT;++i)
		{
			for(int j = 0;j<MAP_WIDTH;++j)
			{
				if(terrains[i][j] == PLAIN)
					gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,plain,rect);
				else if(terrains[i][j] == MOUNTAIN)
					gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,mountain,rect);
				else if(terrains[i][j] == ROAD)
					gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,road,rect);
			}
		}
	}

	void drawBuildings(BuildingModel* buildings[MAP_HEIGHT][MAP_WIDTH]){
		CL_PixelBuffer p1_base = CL_PNGProvider::load("tiles/r_factory.png");
		CL_PixelBuffer p1_city = CL_PNGProvider::load("tiles/r_city.png");
		CL_PixelBuffer p1_hq = CL_PNGProvider::load("tiles/r_hq.png");
		CL_PixelBuffer p2_base = CL_PNGProvider::load("tiles/b_factory.png");
		CL_PixelBuffer p2_city = CL_PNGProvider::load("tiles/b_city.png");
		CL_PixelBuffer p2_hq = CL_PNGProvider::load("tiles/b_hq.png");
		for(int i = 0;i < MAP_HEIGHT;++i)
		{
			for(int j = 0;j<MAP_WIDTH;++j)
			{
				if(buildings[i][j] && ((buildings[i][j]->getPlayer())->number())==1){
					if(buildings[i][j]->getType() == BASE)
						gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,p1_base,rect);
					else if(buildings[i][j]->getType() == CITY)
						gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,p1_city,rect);
					else if(buildings[i][j]->getType() == HEADQUARTERS)
						gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,p1_hq,rect);
				}
				else if(buildings[i][j] && ((buildings[i][j]->getPlayer())->number())==2){
					if(buildings[i][j]->getType() == BASE)
						gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,p2_base,rect);
					else if(buildings[i][j]->getType() == CITY)
						gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,p2_city,rect);
					else if(buildings[i][j]->getType() == HEADQUARTERS)
						gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,p2_hq,rect);

				}
			}
		}

	}

	void drawUnits(UnitModel* units[MAP_HEIGHT][MAP_WIDTH]){
		CL_PixelBuffer p1_infantry = CL_PNGProvider::load("units/r_infantry.png");
		CL_PixelBuffer p1_mech = CL_PNGProvider::load("units/r_bazooka.png");
		CL_PixelBuffer p1_artillery = CL_PNGProvider::load("units/r_artillery.png");
		CL_PixelBuffer p1_tank = CL_PNGProvider::load("units/r_tank.png");
		CL_PixelBuffer p2_infantry = CL_PNGProvider::load("units/b_infantry.png");
		CL_PixelBuffer p2_mech = CL_PNGProvider::load("units/b_bazooka.png");
		CL_PixelBuffer p2_artillery = CL_PNGProvider::load("units/b_artillery.png");
		CL_PixelBuffer p2_tank = CL_PNGProvider::load("units/b_tank.png");
		for(int i = 0;i < MAP_HEIGHT;++i)
		{
			for(int j = 0;j<MAP_WIDTH;++j)
			{
				if(units[i][j] && ((units[i][j]->getPlayer())->number())==1){
					if(units[i][j]->getType() == INFANTRY)
						gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,p1_infantry,rect);
					else if(units[i][j]->getType() == MECH)
						gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,p1_mech,rect);
					else if(units[i][j]->getType() == ARTILLERY)
						gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,p1_artillery,rect);
					else if(units[i][j]->getType() == TANK)
						gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,p1_tank,rect);
				}
				if(units[i][j] && ((units[i][j]->getPlayer())->number())==2){
					if(units[i][j]->getType() == INFANTRY)
						gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,p2_infantry,rect);
					else if(units[i][j]->getType() == MECH)
						gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,p2_mech,rect);
					else if(units[i][j]->getType() == ARTILLERY)
						gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,p2_artillery,rect);
					else if(units[i][j]->getType() == TANK)
						gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,p2_tank,rect);
				}
			}
		}

	}

	void redrawMap(GameMapModel* map){
		drawTerrain(map->terrain);
		drawBuildings(map->buildings);
		drawUnits(map->units);

	}

	void highlight(int row, int col){
		CL_Rect rect = CL_Rect(col*PIECE_SIZE,row*PIECE_SIZE, (col+1)*PIECE_SIZE,(row+1)*PIECE_SIZE);

		CL_Draw::box(gc,rect,CL_Colorf::red);

	}

	void highlightArea(bool area[MAP_HEIGHT][MAP_WIDTH]){
		for(int i = 0;i<MAP_HEIGHT;++i)
			for(int j = 0; j< MAP_WIDTH; ++j)
				if(area[i][j])
				{
					CL_Rect rect = CL_Rect(j*PIECE_SIZE,i*PIECE_SIZE, (j+1)*PIECE_SIZE,(i+1)*PIECE_SIZE);
					CL_Draw::box(gc,rect,CL_Colorf::red);
				}


	}

	void showButtons(){
		CL_Rect area(0,0,300,30);
		CL_PixelBuffer buttons = CL_PNGProvider::load("menus/buttons.png");
		CL_PixelBuffer plain = CL_PNGProvider::load("tiles/plain.png");
		menu_gc.draw_pixels(0,180.0,buttons,area);
	}

	void showPlayer(int curPlayer){
		CL_Rect area(0,0,300,150);
		CL_PixelBuffer p1;
		if(curPlayer == 1)
			p1 = CL_PNGProvider::load("menus/player1.png");
		else
			p1 = CL_PNGProvider::load("menus/player2.png");
		menu_gc.draw_pixels(0,0,p1,area);
	}

	void showBuildMenu(){
		CL_Rect area(0,0,300,150);
		CL_PixelBuffer menu = CL_PNGProvider::load("menus/build.png");
		menu_gc.draw_pixels(0,0,menu,area);

	}


	void showActionMenu(){
		CL_Rect area(0,0,300,150);
		CL_PixelBuffer menu = CL_PNGProvider::load("menus/action.png");
		menu_gc.draw_pixels(0,0,menu,area);

	}

	void showScore(int p1, int p2){
		char buf1[8];
		char buf2[8];
		itoa(p1,buf1,10);
		itoa(p2,buf2,10);
		string score1 = string(buf1);
		string score2 = string(buf2);
		CL_Rect area(0,0,300,30);
		CL_PixelBuffer status = CL_PNGProvider::load("menus/score.png");
		menu_gc.draw_pixels(0,150.0,status,area);
		CL_Font font_tahoma(gc,"Tahoma",16);
		font_tahoma.draw_text(menu_gc, 0,160, score1, CL_Colorf::black);
		font_tahoma.draw_text(menu_gc, 150,160, score2, CL_Colorf::black);
	}

	void redrawStatus(int p1, int p2){
		showScore(p1, p2);
		showButtons();
	}
};

class EventHandler
{
private:
	bool quit;
	CL_Slot mousepress;
	CL_Slot menu_mousepress;
	View* newView;
	GameMapModel* map;
	CL_DisplayWindow* window;
	CL_DisplayWindow* menu_window;
	PlayerModel* p1;
	PlayerModel* p2;
	int currentPlayer;
	Menu_Enum currentMenu;
	int curRow;
	int curCol;
public:

	void on_window_close()
	{
		quit = true;
	}

	bool inMap(int row, int col){
		return row<MAP_HEIGHT && col <MAP_WIDTH;

	}

	bool isHighlighted(int row, int col){
		return map->highlighted[row][col];
	}

	bool canMove(int row, int col){
		if(map->units[row][col]!=NULL)
			return true;
		return false;
	}

	bool canBuild(int row, int col){
		BuildingModel* b = map->buildings[row][col];
		if(b && b->getType()==BASE && b->getPlayer()->number() == currentPlayer)
			return true;
		return false;
	}

	bool isQuit(int x, int y){
		return (x<150 && x>0 && y>180 && y<210);
	}

	bool endTurn(int x, int y){
		return (x>150 && x<300 && y>180 && y<210);
	}

	bool isWait(int x, int y){
		return (x>100 && x<200 && y>30 && y<60);
	}

	bool isAttack(int x, int y){
		return (x>100 && x<200 && y>60 && y<90);
	}

	bool isCapture(int x, int y){
		return (x>100 && x<200 && y>90 && y<120);
	}

	bool isInfantry(int x, int y){
		return (x>0 && x<150 && y>30 && y<60);
	}

	bool isMech(int x, int y){
		return (x>0 && x<150 && y>60 && y<90); 
	}

	bool isArtillery(int x, int y){
		return (x>0 && x<150 && y>90 && y<120);
	}

	bool isTank(int x, int y){
		return (x>0 && x<150 && y>120 && y<150);
	}
	void handleMenuMousePress(const CL_InputEvent &evt, const CL_InputState &state)
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
		if(endTurn(x,y)){
			if(currentPlayer == 1) currentPlayer = 2;
			else currentPlayer = 1;
			newView->redrawStatus(p1->getWealth(),p2->getWealth());
			newView->showPlayer(currentPlayer);
			menu_window->flip();
		}
		else if(isQuit(x,y)){
			quit = true;
		}
		else{

			switch(currentMenu){

			case ACTION: 
				if(isWait(x,y)){
					//grey out unit, clear highlighting, redraw map, redraw menu default
					newView->redrawMap(map);
					window->flip();
				}
				else if(isAttack(x,y)){
					//if it can attack, redraw map, calculate attack highlighting, redraw menu
				}
				else if(isCapture(x,y)){
					//if it can capture, update #buildings captured, update building array, redraw map/menu/clear highlighting
				}
				break;
			case BUILD:
				PlayerModel* curPlayer;
				if(currentPlayer == 1)
					curPlayer = p1;
				else
					curPlayer = p2;
				if(isInfantry(x,y) && curPlayer->getWealth()>INFANTRY_COST){
					map->units[curRow][curCol] = new InfantryModel(curPlayer);
					curPlayer->reduceWealth(INFANTRY_COST);
				}
				else if(isMech(x,y) && curPlayer->getWealth()>MECH_COST){
					map->units[curRow][curCol] = new MechModel(curPlayer);
					curPlayer->reduceWealth(MECH_COST);
				}
				else if(isArtillery(x,y) && curPlayer->getWealth()>ARTILLERY_COST){
					map->units[curRow][curCol] = new ArtilleryModel(curPlayer);
					curPlayer->reduceWealth(ARTILLERY_COST);
				}
				else if(isTank(x,y) && curPlayer->getWealth()>TANK_COST){
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

			
			default:
				break;
		}

		//menu_window->flip();
	}
}
void handleMousePress(const CL_InputEvent &evt, const CL_InputState &state)
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
		if(canMove(row,col)){
			//todo
			
		}
		else if(canBuild(row,col)){
			newView->showBuildMenu();
			currentMenu = BUILD;
			newView->redrawStatus(p1->getWealth(),p2->getWealth());
			menu_window->flip();
		}
		else{
			newView->showPlayer(currentPlayer);
			currentMenu = DEFAULT;
			newView->redrawStatus(p1->getWealth(),p2->getWealth());
			menu_window->flip();
			newView-> redrawMap(map);
			newView -> highlight(row,col);
			window->flip();
		}


		//	newView -> highlightArea(highlightedArea);


	}


}
void init(){
	currentPlayer = 1;
	p1->increaseWealth();
	p2->increaseWealth();

}
void run()
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
	map = new GameMapModel(p1,p2);
	init();
	newView = new View(map,gc,menu_gc,p1->getWealth(),p2->getWealth());
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



};

class Program
{
public:
	static int main(const std::vector<CL_String> &args)
	{
		CL_SetupCore setup_core;
		CL_SetupDisplay setup_display;
		CL_SetupGL setup_gl;

		try
		{
			EventHandler example;
			example.run();
		}
		catch(CL_Exception &exception)
		{
			// Create a console window for text-output if not available
			CL_ConsoleWindow console("Console", 80, 160);
			CL_Console::write_line("Error: " + exception.get_message_and_stack_trace());

			console.display_close_message();

			return -1;
		}

		return 0;
	}
};
CL_ClanApplication app(&Program::main);