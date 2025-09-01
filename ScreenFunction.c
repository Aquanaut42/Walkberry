#include "ScreenFunction.h"
#include "EPD_2in9_V2.h"
#include "ICNT86X.h"
#include "time.h"
#include "Draw/paintScreen.h"
#include "../Fonts/fonts.h"
#include "musiclibrary.h"

extern ICNT86_Dev ICNT86_Dev_Now, ICNT86_Dev_Old;
extern int IIC_Address;
static pthread_t t1, t2;
UBYTE flag_2in9=1, dis_lock=1, dis_flag=1;	
UBYTE *BlackImage, *BlackImage_ASYNC;

char *Songsbmp = "./pic/Songs.bmp";
char *Albumsbmp = "./pic/Albums.bmp";
char *Artistsbmp = "./pic/Artists.bmp";
char *Playlistbmp = "./pic/Playlist.bmp";
char *whiteScreen = "./pic/White_board.bmp";

UBYTE PlayBackBar = 0; // Playback bar at the bottom of the screen 1=visible, 0=not visible
UBYTE ReFlag = 0;

/******************************************************************************
// This function is made so the software closes when i press "ctrl + c"
******************************************************************************/
void Handler_2in9(int signo)
{
    //System Exit
    printf("\r\nHandler_2in9:exit\r\n");
	EPD_2IN9_V2_Sleep();
	DEV_Delay_ms(1000);
	flag_2in9 = 0;
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
    DEV_ModuleExit();
    exit(0);
}
//*****************************************************************************/

/******************************************************************************
// This function monitors the touch screen
******************************************************************************/
void *pthread_irq_2in9(void *arg)
{
	while(flag_2in9) {
		if(DEV_Digital_Read(INT) == 0) {
			ICNT86_Dev_Now.Touch = 1;
			// printf("!");
		}
		else {
			ICNT86_Dev_Now.Touch = 0;
		}
		DEV_Delay_ms(0.01);
	}
	printf("thread1:exit\r\n");
	pthread_exit(NULL);
}
//*****************************************************************************/

/******************************************************************************
// Waits for dis_flag to be set, then does a partial display refresh using BlackImage_ASYNC.
******************************************************************************/
void *pthread_dis_2in9(void *arg)
{
	while(flag_2in9) {
		if(dis_flag) {
			dis_lock = 1;
			EPD_2IN9_V2_Display_Partial(BlackImage_ASYNC);
			dis_flag = 0;
			dis_lock = 0;
			printf("ASYNC display over, unlock \r\n");
		}
		else {
			dis_lock = 0;
		}
		// DEV_Delay_ms(0.01);
	}
	
	printf("thread2:exit\r\n");
	pthread_exit(NULL);
}
//*****************************************************************************/

/******************************************************************************
function: Draw the Playback bar at the bottom of the screen
******************************************************************************/
void PlayBackBarBottom( const char *song, int timeTotal, int timeNow ){
        ClearSquare( 250, 0, 296, 125, WHITE );
        DrawLineHorizontal(0, 250, 130, BLACK, 1);
        DrawLineHorizontal(10, 260, 120, BLACK, 1);
        DrawLineHorizontal(10, 265, 120, BLACK, 1);
        DrawLineVertical(260, 10, 265, BLACK, 1);
        DrawLineVertical(260, 119, 265, BLACK, 1);

        for ( int i = 0 ; i < (int)(( (float)timeNow / timeTotal ) * 109) ; i++ ){
                DrawLineVertical( 260, 10 + i, 265, BLACK, 1 );
        }

        DrawString_EN(10, 275, song, &Font20, WHITE, BLACK);

}
//*****************************************************************************/

/******************************************************************************
function: Draw the main menu
******************************************************************************/
void PrintMainMenu(){

    Clear(WHITE);
    GUI_ReadBmp(Songsbmp, 30, 10);
    GUI_ReadBmp(Albumsbmp, 30, 80);
    GUI_ReadBmp(Artistsbmp, 30, 150);
    GUI_ReadBmp(Playlistbmp, 30, 220);

}
//*****************************************************************************/

/******************************************************************************
function: Draw the song menu
******************************************************************************/
void PrintSongMenu(const MusicLibrary *lib, int scroll){
	
    Clear(WHITE);

	DrawString_EN(1, 1, "Songs", &Font24, WHITE, BLACK); 

	int start = scroll * 10;
	int end = start + 15;
	if(end > lib->count) end = lib->count;

	for (int i = start; i < end; i++) {
		int y = 30 + (i - start) * 20; // start below header
		DrawString_EN(10, y, lib->songs[i].title, &Font20, WHITE, BLACK);
	}
	
	if ( PlayBackBar == 1 ) { 
		PlayBackBarBottom("Current Song", 380, 50); 
	}

}
//*****************************************************************************/

/******************************************************************************
function: Draw the Album menu
******************************************************************************/
void PrintAlbumMenu(const MusicLibrary *lib, int scroll) {
    Clear(WHITE);

    DrawString_EN(1, 1, "Albums", &Font24, WHITE, BLACK);

    // Temporary storage for unique albums
    char albums[512][FIELD_SIZE];  // adjust size if needed
    char artists[512][FIELD_SIZE]; // parallel array for artist
    int album_count = 0;

    // Collect unique albums
    for (size_t i = 0; i < lib->count; i++) {
        bool seen = false;
        for (int j = 0; j < album_count; j++) {
            if (strcmp(lib->songs[i].album, albums[j]) == 0 &&
                strcmp(lib->songs[i].artist, artists[j]) == 0) {
                seen = true;
                break;
            }
        }
        if (!seen && album_count < 512) {
            strncpy(albums[album_count], lib->songs[i].album, FIELD_SIZE - 1);
            albums[album_count][FIELD_SIZE - 1] = '\0';
            strncpy(artists[album_count], lib->songs[i].artist, FIELD_SIZE - 1);
            artists[album_count][FIELD_SIZE - 1] = '\0';
            album_count++;
        }
    }

    // Pagination logic
    int start = scroll * 10;
    int end = start + 15;
    if (end > album_count) end = album_count;

    // Draw albums
    for (int i = start; i < end; i++) {
        int y = 30 + (i - start) * 20; // start below header
        char buf[FIELD_SIZE * 2];
        snprintf(buf, sizeof(buf), "%s (%s)", albums[i], artists[i]);
        DrawString_EN(10, y, buf, &Font20, WHITE, BLACK);
    }

    if (PlayBackBar == 1) {
        PlayBackBarBottom("Current Album", 380, 50);
    }
}

//*****************************************************************************/

/******************************************************************************
function: Draw the Artist menu
******************************************************************************/
void PrintArtistMenu(){
	
    Clear(WHITE);

	DrawString_EN(1, 1, "Artists", &Font24, WHITE, BLACK); 

	GUI_ReadBmp(Artistsbmp, 40, 80);

}
//*****************************************************************************/

/******************************************************************************
function: Draw the Artist menu
******************************************************************************/
void PrintPlaylisttMenu(){
	
    Clear(WHITE);

	DrawString_EN(1, 1, "Playlists", &Font24, WHITE, BLACK); 

	GUI_ReadBmp(Playlistbmp, 40, 80);

}
//*****************************************************************************/

/******************************************************************************
function: Setup the screen and draw the main menu
******************************************************************************/
int ScreenSetup() {
	printf("Starting screen setup");
	IIC_Address = 0x48;
    
    signal(SIGINT, Handler_2in9);
    DEV_ModuleInit();
    
    pthread_create(&t1, NULL, pthread_irq_2in9, NULL);
    
    EPD_2IN9_V2_Init();
    EPD_2IN9_V2_Clear();
    
    ICNT_Init();
    DEV_Delay_ms(100);

    // Create a new image buffer
    UWORD Imagesize = ((EPD_2IN9_V2_WIDTH % 8 == 0) ? (EPD_2IN9_V2_WIDTH / 8) : (EPD_2IN9_V2_WIDTH / 8 + 1)) * EPD_2IN9_V2_HEIGHT;
    if ((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL || 
        (BlackImage_ASYNC = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to allocate memory for images.\r\n");
        return -1;
    }

    // Initialize image
    NewImage(BlackImage, EPD_2IN9_V2_WIDTH, EPD_2IN9_V2_HEIGHT, 90, WHITE);
    SelectImage(BlackImage);
    Clear(WHITE);

    // Only draw the main menu at startup
    PrintMainMenu();

    // Send to display
    EPD_2IN9_V2_Display_Base(BlackImage);
    memcpy(BlackImage_ASYNC, BlackImage, Imagesize);

    // Start display thread
    pthread_create(&t2, NULL, pthread_dis_2in9, NULL);

	printf("End screen setup");
	return 1; // setup success
}
//*****************************************************************************/

/******************************************************************************
function: This updates the page select in the main menu
******************************************************************************/
int ChechMenu(int Page)
{
	
	if(ICNT_Scan()==1 || (ICNT86_Dev_Now.X[0] == ICNT86_Dev_Old.X[0] && 
						  ICNT86_Dev_Now.Y[0] == ICNT86_Dev_Old.Y[0])) {
		return Page;	// No update needed
	}

	// Check touches and update Page
	if(Page == 0) { // If it's in the main menu
		if(ICNT86_Dev_Now.X[0] > 10 && ICNT86_Dev_Now.X[0] < 70) Page = 1;
		else if(ICNT86_Dev_Now.X[0] > 80 && ICNT86_Dev_Now.X[0] < 140) Page = 2;
		else if(ICNT86_Dev_Now.X[0] > 150 && ICNT86_Dev_Now.X[0] < 210) Page = 3;
		else if(ICNT86_Dev_Now.X[0] > 220 && ICNT86_Dev_Now.X[0] < 280) Page = 4;
	}

	// Update old touch
	ICNT86_Dev_Old.X[0] = ICNT86_Dev_Now.X[0];
	ICNT86_Dev_Old.Y[0] = ICNT86_Dev_Now.Y[0];

	return Page; // return page selected (0 means staying in the main menu)
}
//*****************************************************************************/

/******************************************************************************
function: This updates the screen if needed
******************************************************************************/
int UpdateScreen(const MusicLibrary *lib, int scroll, int Page)
{

	switch(Page) {
		case 0:
			PrintMainMenu();
			break;
		case 1:	
			PrintSongMenu(lib, scroll);
			break;
		case 2:
			PrintAlbumMenu();
			break;
		case 3:
			PrintArtistMenu();
			break;
		case 4:
			PrintPlaylisttMenu();
			break;
	}
	EPD_2IN9_V2_Display_Partial_Wait(BlackImage);

	// Update old touch
	ICNT86_Dev_Old.X[0] = ICNT86_Dev_Now.X[0];
	ICNT86_Dev_Old.Y[0] = ICNT86_Dev_Now.Y[0];

	
	return 1; // update succes
}
//*****************************************************************************/
