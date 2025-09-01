#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include <pthread.h>	//pthread_create()
#include "GUI_BMPfile.h"
#include "musiclibrary.h"

int ScreenSetup();
int ChechMenu(const MusicLibrary *lib, int scroll, int Page);
int UpdateScreen(const MusicLibrary *lib, int scroll, int Page);
void build_album_list(const MusicLibrary *lib);
void build_artist_list(const MusicLibrary *lib);

#endif
