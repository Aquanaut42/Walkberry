#include "ScreenFunction.h"
#include "MusicLibrary.hpp"

int main()
{
	ScreenSetup();

	MusicLibrary lib;
    lib.scanFolder("/path/to/music");
    std::cout << "Library contains " << lib.songs.size() << " songs.\n";
    lib.printSongs();

	//---------------------------------
	// This is the main loop
	//---------------------------------
	while(1) {

		UpdateScreen();

		DEV_Delay_ms(50);
	}
	//---------------------------------

	return 0;
}
