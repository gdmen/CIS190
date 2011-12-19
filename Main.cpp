#include "precomp.h"
#include <Windows.h>
#include "EventHandler.h"

/*
TODO:
VIEW receives: an array of Terrains, Buildings, Units, and bool places to HighLight
*/

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