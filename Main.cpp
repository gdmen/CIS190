#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/application.h>
#include <ClanLib/gui.h>
#include <ClanLib/GUI/Components/window.h>
#include <ClanLib/GUI/gui_manager.h>

/*
TODO:
VIEW receives: an array of Terrains, Buildings, Units, and bool places to HighLight
*/

#define WIDTH_OFFSET 7
#define HEIGHT_OFFSET 28
#define MAP_HEIGHT 5
#define MAP_WIDTH 10
#define PIECE_SIZE 32
enum Terrain_Type {PLAIN, MOUNTAIN, ROAD};
enum Unit_Type {NONE, INFANTRY, MECH, TANK, ARTILLERY};
enum Building_Type {EMPTY, HEADQUARTERS, BASE, CITY};


class View
{
private:
	Terrain_Type terrains[MAP_HEIGHT][MAP_WIDTH];
	Unit_Type units[MAP_HEIGHT][MAP_WIDTH];
	Building_Type buildings[MAP_HEIGHT][MAP_WIDTH];
	CL_Rect rect;
	CL_GraphicContext gc;

public:
	View(Terrain_Type _terrains[MAP_HEIGHT][MAP_WIDTH], Unit_Type _units[MAP_HEIGHT][MAP_WIDTH], Building_Type _buildings[MAP_HEIGHT][MAP_WIDTH],  CL_GraphicContext& _gc){
		gc = _gc;
		rect = CL_Rect(0,0,PIECE_SIZE,PIECE_SIZE);
		draw_terrain(_terrains);
		draw_buildings(_buildings);
		draw_units(_units);
		
	/*	CL_GUIManager gui_manager;
		CL_GUITopLevelDescription desc;
		desc.set_title("ClanLib GUI");
		desc.set_size(CL_Size( 500, 500 ), false);
		CL_GUIComponent window(&gui_manager, desc);
		window.set_geometry(CL_Rect(0, 0, 500, 300));
		CL_PushButton button1(&window);
		button1.set_geometry(CL_Rect(100, 100, 200, 120));
		button1.set_text("Okay!");
		button1.func_clicked().set(this, &View::on_button1_clicked, &button1);*/
		
	}
	void on_button1_clicked(CL_PushButton* button)
	{
		button->exit_with_code(0);
	}
	void draw_terrain(Terrain_Type terrains[MAP_HEIGHT][MAP_WIDTH]){
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

	void draw_buildings(Building_Type buildings[MAP_HEIGHT][MAP_WIDTH]){


	}

	void draw_units(Unit_Type units[MAP_HEIGHT][MAP_WIDTH]){

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

};

class EventHandler
{
private:
	bool quit;
	CL_Slot mousepress;
	View* newView;
	Terrain_Type terrains[MAP_HEIGHT][MAP_WIDTH];
	bool highlightedArea[MAP_HEIGHT][MAP_WIDTH];
	CL_DisplayWindow* window;
public:

	void on_window_close()
	{
		quit = true;
	}

	bool inMap(int row, int col){
		return row<MAP_HEIGHT && col <MAP_WIDTH;

	}
	void handleMousePress(const CL_InputEvent &evt, const CL_InputState &state)
	{
		CL_Point pt = evt.mouse_pos;
		int x = pt.x;
		int y = pt.y;

		int col = x/PIECE_SIZE;
		int row = y/PIECE_SIZE;
		if(inMap(row,col)){
			newView -> draw_terrain(terrains);
			newView -> highlight(row,col);
			newView -> highlightArea(highlightedArea);
			window->flip();
		}


	}
	void run()
	{
		quit = false;
	
		
	  
	 window = new CL_DisplayWindow("Game Map",MAP_WIDTH*PIECE_SIZE+WIDTH_OFFSET, MAP_HEIGHT*PIECE_SIZE+HEIGHT_OFFSET);
		CL_InputContext ic = window->get_ic();
		CL_InputDevice mouse = ic.get_mouse();
		CL_Slot slot_quit = window->sig_window_close().connect(this, &EventHandler::on_window_close);
		mousepress =mouse.sig_key_down().connect(this,&EventHandler::handleMousePress);
		CL_GraphicContext gc = window->get_gc();
		CL_InputDevice keyboard = window->get_ic().get_keyboard();
		for(int i = 0; i<MAP_HEIGHT;++i)
			for(int j = 0;j<MAP_WIDTH;++j){
				terrains[i][j] = PLAIN;
				highlightedArea[i][j] = true;
			}
			newView = new View(terrains,NULL,NULL,gc);
			window->flip();
			while (!quit)
			{
				if(keyboard.get_keycode(CL_KEY_ESCAPE) == true)
					quit = true;
					
				// draw_sunset(gc);
				// window.get_gc().clear(CL_Colorf::white);

				/*CL_PixelBuffer plain = CL_PNGProvider::load("tiles/plain.png");
				CL_PixelBuffer mountain = CL_PNGProvider::load("tiles/mountain1.png");
				CL_PixelBuffer road = CL_PNGProvider::load("tiles/road_h.png");
				CL_Rect rect = CL_Rect(0,0,32,32);
				for(int i = 0;i<MAP_HEIGHT;++i)
				{
				for(int j = 0;j<MAP_WIDTH;++j)
				{
				if(terrains[i][j] == PLAIN)
				gc.draw_pixels(j*PIECE_SIZE,i*PIECE_SIZE,plain,rect);
				else if(terrains[i][j] == MOUNTAIN)
				gc.draw_pixels(j*PIECE_SIZE,i*PIECE_SIZE,mountain,rect);
				else if(terrains[i][j] == ROAD)
				gc.draw_pixels(j*PIECE_SIZE,i*PIECE_SIZE,road,rect);
				}
				}*/
				/* CL_PixelBuffer infantry = CL_PNGProvider::load("units/g_infantry.png");
				CL_PixelBuffer artillery = CL_PNGProvider::load("units/b_artillery.png");
				CL_PixelBuffer plain = CL_PNGProvider::load("tiles/plain.png");
				CL_Rect rect = CL_Rect(1,0,32,32);
				gc.draw_pixels(0,0,plain,rect);
				gc.draw_pixels(0,0,infantry,rect);
				CL_Draw::box(gc,rect,CL_Colorf::red);*/

				//window.flip();
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