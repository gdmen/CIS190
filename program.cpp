
#include "precomp.h"
#include "program.h"
#include <ClanLib/application.h>

CL_ClanApplication clanapp(&Program::main);

int Program::main(const std::vector<CL_String> &args)
{
	CL_SetupCore setup_core;
	CL_SetupDisplay setup_display;
	CL_SetupGL setup_gl;
	CL_SetupGL1 setup_gl1;
	CL_SetupSWRender setup_swrender;
	CL_SetupGUI setup_gui;
	CL_SetupSound setup_sound;
	CL_SetupVorbis setup_vorbis;
	CL_SetupMikMod setup_mikmod;
	CL_SetupNetwork setup_network;
	
	return 0;
}
