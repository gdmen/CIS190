#include "precomp.h"
#include "View.h"

View::View(GameMapModel* map,  CL_GraphicContext& _gc, CL_GraphicContext& _menugc, int p1, int p2){
	gc = _gc;
	menu_gc = _menugc;

	rect = CL_Rect(0,0,PIECE_SIZE,PIECE_SIZE);
	health_rect = CL_Rect(0,0,8,8);
	drawTerrain(map->terrain);
	drawBuildings(map->buildings);
	drawUnits(map->units);
	showPlayer(1);
	showButtons();
	showScore(p1,p2);

}

void View::drawTerrain(Terrain_Enum terrains[MAP_HEIGHT][MAP_WIDTH]){
	CL_PixelBuffer plain = CL_PNGProvider::load("tiles/plain.png");
	CL_PixelBuffer mountain = CL_PNGProvider::load("tiles/mountain1.png");
	CL_PixelBuffer road = CL_PNGProvider::load("tiles/road_h.png");
	CL_PixelBuffer road2 = CL_PNGProvider::load("tiles/road_v.png");
	CL_PixelBuffer road_ur = CL_PNGProvider::load("tiles/road_bl.png");
	CL_PixelBuffer road_ul = CL_PNGProvider::load("tiles/road_br.png");
	CL_PixelBuffer road_lr = CL_PNGProvider::load("tiles/road_tl.png");
	CL_PixelBuffer road_ll = CL_PNGProvider::load("tiles/road_tr.png");
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
			else if(terrains[i][j] == ROAD2)
				gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,road2,rect);
			else if(terrains[i][j] == ROAD_UL)
				gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,road_ul,rect);
			else if(terrains[i][j] == ROAD_UR)
				gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,road_ur,rect);
			else if(terrains[i][j] == ROAD_LL)
				gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,road_ll,rect);
			else if(terrains[i][j] == ROAD_LR)
				gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,road_lr,rect);

		}
	}
}

void View::drawBuildings(BuildingModel* buildings[MAP_HEIGHT][MAP_WIDTH]){
	CL_PixelBuffer p1_base = CL_PNGProvider::load("tiles/r_factory.png");
	CL_PixelBuffer p1_city = CL_PNGProvider::load("tiles/r_city.png");
	CL_PixelBuffer p1_hq = CL_PNGProvider::load("tiles/r_hq.png");
	CL_PixelBuffer p2_base = CL_PNGProvider::load("tiles/b_factory.png");
	CL_PixelBuffer p2_city = CL_PNGProvider::load("tiles/b_city.png");
	CL_PixelBuffer p2_hq = CL_PNGProvider::load("tiles/b_hq.png");
	CL_PixelBuffer n_base = CL_PNGProvider::load("tiles/n_factory.png");
	CL_PixelBuffer n_city = CL_PNGProvider::load("tiles/n_city.png");
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

			}else if(buildings[i][j] && ((buildings[i][j]->getPlayer())->number())==0){
				if(buildings[i][j]->getType() == BASE)
					gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,n_base,rect);
				else if(buildings[i][j]->getType() == CITY)
					gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,n_city,rect);
			}
		}
	}

}

CL_PixelBuffer View::getHealth(int health){
	if(health == 1)
		return CL_PNGProvider::load("health/one.png");
	if(health == 2)
		return CL_PNGProvider::load("health/two.png");
	if(health == 3)
		return CL_PNGProvider::load("health/three.png");
	if(health == 4)
		return CL_PNGProvider::load("health/four.png");
	if(health == 5)
		return CL_PNGProvider::load("health/five.png");
	if(health == 6)
		return CL_PNGProvider::load("health/six.png");
	if(health == 7)
		return CL_PNGProvider::load("health/seven.png");
	if(health == 8)
		return CL_PNGProvider::load("health/eight.png");
	if(health == 9)
		return CL_PNGProvider::load("health/nine.png");
	else
		return CL_PNGProvider::load("health/ten.png");
	
}
void View::drawUnits(UnitModel* units[MAP_HEIGHT][MAP_WIDTH]){
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
				if(units[i][j]->getType() == INFANTRY){
					gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,p1_infantry,rect);
					
				}
				else if(units[i][j]->getType() == MECH){
					gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,p1_mech,rect);
				}
				else if(units[i][j]->getType() == ARTILLERY){
					gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,p1_artillery,rect);
				}
				else if(units[i][j]->getType() == TANK){
					gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,p1_tank,rect);
				}
				gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,getHealth(units[i][j]->getHealth()),health_rect);
			}
			if(units[i][j] && ((units[i][j]->getPlayer())->number())==2){
				if(units[i][j]->getType() == INFANTRY){
					gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,p2_infantry,rect);
				}
				else if(units[i][j]->getType() == MECH){
					gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,p2_mech,rect);
				}
				else if(units[i][j]->getType() == ARTILLERY){
					gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,p2_artillery,rect);
				}
				else if(units[i][j]->getType() == TANK){
					gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,p2_tank,rect);
				}
				gc.draw_pixels((float)j*PIECE_SIZE,(float)i*PIECE_SIZE,getHealth(units[i][j]->getHealth()),health_rect);
			}
		}
	}

}

void View::redrawMap(GameMapModel* map){
	drawTerrain(map->terrain);
	drawBuildings(map->buildings);
	drawUnits(map->units);

}

void View::highlight(int row, int col){
	CL_Rect rect = CL_Rect(col*PIECE_SIZE,row*PIECE_SIZE, (col+1)*PIECE_SIZE,(row+1)*PIECE_SIZE);

	CL_Draw::box(gc,rect,CL_Colorf::yellow);

}

void View::highlightArea(bool area[MAP_HEIGHT][MAP_WIDTH]){
	for(int i = 0;i<MAP_HEIGHT;++i)
		for(int j = 0; j< MAP_WIDTH; ++j)
			if(area[i][j]){
				highlight(i, j);
			}
}

void View::attack(int row, int col){
	CL_Rect rect = CL_Rect(col*PIECE_SIZE,row*PIECE_SIZE, (col+1)*PIECE_SIZE,(row+1)*PIECE_SIZE);

	CL_Draw::box(gc,rect,CL_Colorf::red);

}

void View::attackArea(bool area[MAP_HEIGHT][MAP_WIDTH]){
	for(int i = 0;i<MAP_HEIGHT;++i)
		for(int j = 0; j< MAP_WIDTH; ++j)
			if(area[i][j]){
				attack(i, j);
			}
}

void View::showButtons(){
	CL_Rect area(0,0,300,30);
	CL_PixelBuffer buttons = CL_PNGProvider::load("menus/buttons.png");
	CL_PixelBuffer plain = CL_PNGProvider::load("tiles/plain.png");
	menu_gc.draw_pixels(0,180.0,buttons,area);
}

void View::showPlayer(int curPlayer){
	CL_Rect area(0,0,300,150);
	CL_PixelBuffer p1;
	if(curPlayer == 1)
		p1 = CL_PNGProvider::load("menus/player1.png");
	else
		p1 = CL_PNGProvider::load("menus/player2.png");
	std::cout << "here\n";
	menu_gc.draw_pixels(0,0,p1,area);
	std::cout << "after here\n";
}

void View::showBuildMenu(){
	CL_Rect area(0,0,300,150);
	CL_PixelBuffer menu = CL_PNGProvider::load("menus/build.png");
	menu_gc.draw_pixels(0,0,menu,area);

}


void View::showActionMenu(){
	CL_Rect area(0,0,300,150);
	CL_PixelBuffer menu = CL_PNGProvider::load("menus/action.png");
	menu_gc.draw_pixels(0,0,menu,area);

}

void View::showScore(int p1, int p2){
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

void View::showPlayerWon(int player){
	CL_PixelBuffer menu;
	CL_Rect area(0,0,300,150);
	if(player == 1)
	 menu = CL_PNGProvider::load("menus/p1won.png");
	else
		menu = CL_PNGProvider::load("menus/p2won.png");
	menu_gc.draw_pixels(0,0,menu,area);
}
void View::redrawStatus(int p1, int p2){
	showScore(p1, p2);
	showButtons();
}