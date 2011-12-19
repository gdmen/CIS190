#include "Constants.h"
#include "GameMapModel.h"

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
	View(GameMapModel* map,  CL_GraphicContext& _gc, CL_GraphicContext& _menugc, int p1, int p2);

	void drawTerrain(Terrain_Enum terrains[MAP_HEIGHT][MAP_WIDTH]);

	void drawBuildings(BuildingModel* buildings[MAP_HEIGHT][MAP_WIDTH]);

	void drawUnits(UnitModel* units[MAP_HEIGHT][MAP_WIDTH]);

	void redrawMap(GameMapModel* map);

	void highlight(int row, int col);

	void highlightArea(bool area[MAP_HEIGHT][MAP_WIDTH]);

	void attack(int row, int col);

	void attackArea(bool area[MAP_HEIGHT][MAP_WIDTH]);

	void showButtons();

	void showPlayer(int curPlayer);

	void showBuildMenu();

	void showActionMenu();

	void showScore(int p1, int p2);

	void redrawStatus(int p1, int p2);
};