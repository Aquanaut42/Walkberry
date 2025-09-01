#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include <pthread.h>	//pthread_create()
#include "GUI_BMPfile.h"

int ScreenSetup();
int ChechMenu(Page);
int UpdateScreen(const MusicLibrary *lib, int scroll, int Page);

#endif