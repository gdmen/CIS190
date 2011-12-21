#include "Constants.h"
#include "GameMapModel.h"
#include <iostream>
#include <sstream>
#include "GameController.h"
using namespace std;

class EventHandler
{
private:
	bool quit;
	CL_Slot mousepress;
	CL_Slot menu_mousepress;
	View* newView;
	GameMapModel* map;
	GameController* controller;
	CL_DisplayWindow* window;
	CL_DisplayWindow* menu_window;
	PlayerModel* p1;
	PlayerModel* p2;
	PlayerModel* neutral;
	int currentPlayer;
	Menu_Enum currentMenu;
	int curRow;
	int curCol;
public:

	void on_window_close();

	bool inMap(int row, int col);

	bool isHighlighted(int row, int col);

	bool canMove(int row, int col);

	bool canBuild(int row, int col);

	bool isQuit(int x, int y);

	bool endTurn(int x, int y);

	bool isWait(int x, int y);
	bool isAttack(int x, int y);

	bool isCapture(int x, int y);

	bool isInfantry(int x, int y);

	bool isMech(int x, int y);

	bool isArtillery(int x, int y);

	bool isTank(int x, int y);
	void handleMenuMousePress(const CL_InputEvent &evt, const CL_InputState &state);
	void handleMousePress(const CL_InputEvent &evt, const CL_InputState &state);
	void init();
	void run();
};