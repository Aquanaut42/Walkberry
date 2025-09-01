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

// Pictures path
char *Songsbmp = "./pic/Songs.bmp";
char *Albumsbmp = "./pic/Albums.bmp";
char *Artistsbmp = "./pic/Artists.bmp";
char *Playlistbmp = "./pic/Playlist.bmp";
char *whiteScreen = "./pic/White_board.bmp";

UBYTE PlayBackBar = 0; // Playback bar at the bottom of the screen 1=visible, 0=not visible

// Current selections for filtering
char current_artist[FIELD_SIZE] = "";
char current_album[FIELD_SIZE] = "";

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
function: Builds the unique album and artist list from the music library
******************************************************************************/
/* shared album storage used by both printing and touch check */
static char album_list[512][FIELD_SIZE];
static int album_count = 0;

/* Build unique album list from lib, safe checks */
void build_album_list(const MusicLibrary *lib) {
    album_count = 0;

    if (lib == NULL) {
        printf("build_album_list: lib is NULL\n");
        return;
    }
    if (lib->songs == NULL) {
        printf("build_album_list: lib->songs is NULL\n");
        return;
    }

    for (size_t i = 0; i < lib->count; i++) {
        const char *alb = lib->songs[i].album;
        if (alb == NULL || alb[0] == '\0') continue; // skip empty
        /* avoid overflow of single album name */
        for (int j = 0; j < album_count; j++) {
            if (strncmp(alb, album_list[j], FIELD_SIZE) == 0) { // compare safely
                alb = NULL; // mark as seen
                break;
            }
        }
        if (alb == NULL) continue;
        if (album_count < 512) {
            strncpy(album_list[album_count], lib->songs[i].album, FIELD_SIZE - 1);
            album_list[album_count][FIELD_SIZE - 1] = '\0';
            album_count++;
        } else {
            break; // reached capacity
        }
    }
}
void build_album_list_ByArtist(const MusicLibrary *lib) {
    album_count = 0;

    if (lib == NULL) {
        printf("build_album_list: lib is NULL\n");
        return;
    }
    if (lib->songs == NULL) {
        printf("build_album_list: lib->songs is NULL\n");
        return;
    }

    for (size_t i = 0; i < lib->count; i++) {
        const char *alb = lib->songs[i].album;
        const char *art = lib->songs[i].artist;

        // skip empty album names
        if (alb == NULL || alb[0] == '\0') continue;

        // filter: only include albums for current_artist (if set)
        if (current_artist[0] != '\0') {  
            if (art == NULL || strcmp(art, current_artist) != 0) {
                continue; // skip albums not matching current_artist
            }
        }

        // avoid duplicates
        int duplicate = 0;
        for (int j = 0; j < album_count; j++) {
            if (strncmp(alb, album_list[j], FIELD_SIZE) == 0) {
                duplicate = 1;
                break;
            }
        }
        if (duplicate) continue;

        // add album
        if (album_count < 512) {
            strncpy(album_list[album_count], alb, FIELD_SIZE - 1);
            album_list[album_count][FIELD_SIZE - 1] = '\0';
            album_count++;
            printf("%s\n", alb); // debug print
        } else {
            break; // reached capacity
        }
    }
}


static char artist_list[512][FIELD_SIZE];
static int artist_count = 0;

/* Build unique artist list from lib, safe checks */
void build_artist_list(const MusicLibrary *lib) {
    artist_count = 0;

    if (lib == NULL) {
        printf("build_artist_list: lib is NULL\n");
        return;
    }
    if (lib->songs == NULL) {
        printf("build_artist_list: lib->songs is NULL\n");
        return;
    }

    for (size_t i = 0; i < lib->count; i++) {
        const char *alb = lib->songs[i].artist;
        if (alb == NULL || alb[0] == '\0') continue; // skip empty
        /* avoid overflow of single artist name */
        for (int j = 0; j < artist_count; j++) {
            if (strncmp(alb, artist_list[j], FIELD_SIZE) == 0) { // compare safely
                alb = NULL; // mark as seen
                break;
            }
        }
        if (alb == NULL) continue;
        if (artist_count < 512) {
            strncpy(artist_list[artist_count], lib->songs[i].artist, FIELD_SIZE - 1);
            artist_list[artist_count][FIELD_SIZE - 1] = '\0';
            artist_count++;
        } else {
            break; // reached capacity
        }
    }
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

	// Reset current selections
	current_artist[FIELD_SIZE - 1] = '\0';
	current_album[FIELD_SIZE - 1] = '\0';

}
//*****************************************************************************/

/******************************************************************************
function: Draw the song menu
******************************************************************************/
typedef struct {
    const char *title;
    int track_no;
} SongEntry;

int parse_track_number(const char *title) {
    if (!title) return 9999; // push untitled to end
    char *endptr;
    int num = strtol(title, &endptr, 10);
    if (endptr == title) return 9999; // no number at start
    return num;
}

int compare_songentry(const void *a, const void *b) {
    const SongEntry *sa = (const SongEntry*)a;
    const SongEntry *sb = (const SongEntry*)b;
    return sa->track_no - sb->track_no;
}

void PrintSongMenu(const MusicLibrary *lib, int scroll){
	
    Clear(WHITE);
	if (lib == NULL) return;
    if (lib->songs == NULL) return;

	SongEntry album_songs[512]; // Temporary storage for songs
	int song_count = 0;

    if (current_album[0] == '\0') { // if no album selected, show all songs

		// print "Songs" as header
        DrawString_EN(1, 1, "Songs", &Font24, WHITE, BLACK); 

		// collect all songs
		for (size_t i = 0; i < lib->count; i++) {
			if ( lib->songs[i].album ) { // skip songs with no album (should not happen)
				album_songs[song_count].title = lib->songs[i].title ? lib->songs[i].title : "(untitled)"; // parse the title (plus safe check)
				album_songs[song_count].track_no = parse_track_number(album_songs[song_count].title); // parse track number
				song_count++;
			}
		}

    } else {	// If an album is selected, show songs from that album only
		
		// Print the album name as header
		char header[FIELD_SIZE * 2];
		snprintf(header, sizeof(header), "%s", current_album);
		DrawString_EN(1, 1, header, &Font24, WHITE, BLACK); 

		// collect songs from current_album
		for (size_t i = 0; i < lib->count; i++) {
			if (lib->songs[i].album && strcmp(lib->songs[i].album, current_album) == 0) { // skip songs that aren't in the current_album and has no album (should not happen)
				album_songs[song_count].title = lib->songs[i].title ? lib->songs[i].title : "(untitled)"; // parse the title (plus safe check)
				album_songs[song_count].track_no = parse_track_number(album_songs[song_count].title); // parse track number
				song_count++;
			}
		}
		
	}

	qsort(album_songs, song_count, sizeof(SongEntry), compare_songentry); // sort by track number

    // Pagination logic (rows per page = 10)
    int rows_per_page = 10;
    int start_index = scroll * rows_per_page;
    int end_index = start_index + rows_per_page;
    if (end_index > song_count) end_index = song_count;

    if (song_count == 0) { // nothing to draw, placeholder
    	DrawString_EN(10, 30, "(no songs)", &Font20, WHITE, BLACK);
	} else { // draw each song title
		for (int i = start_index; i < end_index; i++) {

			int y = 30 + (i - start_index) * 20;
			const char *title = album_songs[i].title;
			if (title && strlen(title) > 3) {
				title += 3; // skip first 3 characters
			}
			DrawString_EN(10, y, title, &Font20, WHITE, BLACK);
		}
	}

	// The playback bar at the bottom of the screen
	if ( PlayBackBar == 1 ) { 
		PlayBackBarBottom("Current Song", 380, 50); 
	}
}
//****************************************************************************/

/******************************************************************************
function: Draw the Album menu
******************************************************************************/
void PrintAlbumMenu(const MusicLibrary *lib, int scroll) {

	Clear(WHITE);
	if (lib == NULL) return;
    if (lib->songs == NULL) return;

    if (current_artist[0] == '\0') { // if no artist selected, show all albums

		build_album_list(lib); // Refresh album list
		DrawString_EN(1, 1, "Albums", &Font24, WHITE, BLACK);

		// Pagination logic (rows per page = 15)
		int rows_per_page = 15;
		int start = scroll * rows_per_page;
		int end = start + rows_per_page;
		if (start >= album_count) {
			// nothing to draw
			DrawString_EN(10, 30, "(no albums)", &Font20, WHITE, BLACK);
			return;
		}
		if (end > album_count) end = album_count;

		for (int i = start; i < end; i++) {
			int y = 30 + (i - start) * 20; // start below header
			DrawString_EN(10, y, album_list[i], &Font20, WHITE, BLACK);
		}
		
		if ( PlayBackBar == 1 ) { 
			PlayBackBarBottom("Current Song", 380, 50); 
		}
        return;
    }
	// -------- artist mode -------- (albums from current_artist only)
	build_album_list_ByArtist(lib); // Refresh album list with artist filter

    char header[FIELD_SIZE * 2];
    snprintf(header, sizeof(header), "%s", current_artist);
    DrawString_EN(1, 1, header, &Font24, WHITE, BLACK);

	// Pagination logic (rows per page = 15)
	int rows_per_page = 15;
	int start = scroll * rows_per_page;
	int end = start + rows_per_page;
	if (start >= album_count) {
		// nothing to draw
		DrawString_EN(10, 30, "(no albums)", &Font20, WHITE, BLACK);
		return;
	}
	if (end > album_count) end = album_count;

	for (int i = start; i < end; i++) {
		int y = 30 + (i - start) * 20; // start below header
		DrawString_EN(10, y, album_list[i], &Font20, WHITE, BLACK);
	}
		
	if ( PlayBackBar == 1 ) { 
		PlayBackBarBottom("Current Song", 380, 50); 
	}
    return;
}
//*****************************************************************************/

/******************************************************************************
function: Check the Album menu for touches and update if needed
******************************************************************************/
void CheckAlbumMenu(const MusicLibrary *lib, int scroll) {

    int rows_per_page = 15;
    int start = scroll * rows_per_page;

    int x = ICNT86_Dev_Now.X[0]; // touch X coordinate

    // quick sanity check on coordinates (adjust depending on your screen orientation)
    if (x < 30) return; // touched header or above

    int row = (x - 30) / 20; // 0-based row on page
    if (row < 0 || row >= rows_per_page) return;

    int actual_index = start + row;
    if (actual_index < 0 || actual_index >= album_count) return;

    // copy into current_album safely
    strncpy(current_album, album_list[actual_index], FIELD_SIZE - 1);
    
    printf("CheckAlbumMenu: selected album index=%d name='%s' (y=%d)\n",
           actual_index, current_album, x);
}
//*****************************************************************************/

/******************************************************************************
function: Check the Artist menu for touches and update if needed
******************************************************************************/
void CheckArtistMenu(const MusicLibrary *lib, int scroll) {

    int rows_per_page = 15;
    int start = scroll * rows_per_page;

    int x = ICNT86_Dev_Now.X[0]; // touch X coordinate

    // quick sanity check on coordinates (adjust depending on your screen orientation)
    if (x < 30) return; // touched header or above

    int row = (x - 30) / 20; // 0-based row on page
    if (row < 0 || row >= rows_per_page) return;

    int actual_index = start + row;
    if (actual_index < 0 || actual_index >= artist_count) return;

    // copy into current_artist safely
    strncpy(current_artist, artist_list[actual_index], FIELD_SIZE - 1);
    
    printf("CheckArtistMenu: selected artist index=%d name='%s' (y=%d)\n",
           actual_index, current_artist, x);
}
//*****************************************************************************/

/******************************************************************************
function: Draw the Artist menu
******************************************************************************/
void PrintArtistMenu(const MusicLibrary *lib, int scroll){
	
    Clear(WHITE);

	DrawString_EN(1, 1, "Artists", &Font24, WHITE, BLACK); 

	// Temporary storage for unique artist
    char artists[512][FIELD_SIZE]; // parallel array for artist
    int artist_count = 0;

    // Collect unique albums
    for (size_t i = 0; i < lib->count; i++) {
        int seen = 0;
        for (int j = 0; j < artist_count; j++) {
            if (strcmp(lib->songs[i].artist, artists[j]) == 0) {
                seen = 1;
                break;
            }
        }
        if (seen == 0 && artist_count < 512) {
            strncpy(artists[artist_count], lib->songs[i].artist, FIELD_SIZE - 1);
            artists[artist_count][FIELD_SIZE - 1] = '\0';
            artist_count++;
        }
    }

    // Pagination logic
    int start = scroll * 10;
    int end = start + 15;
    if (end > artist_count) end = artist_count;

    // Draw albums
    for (int i = start; i < end; i++) {
        int y = 30 + (i - start) * 20; // start below header
        char buf[FIELD_SIZE * 2];
        snprintf(buf, sizeof(buf), "%s", artists[i]);
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
int ChechMenu(const MusicLibrary *lib, int scroll, int Page)
{
	
	if(ICNT_Scan()==1 || (ICNT86_Dev_Now.X[0] == ICNT86_Dev_Old.X[0] && 
						  ICNT86_Dev_Now.Y[0] == ICNT86_Dev_Old.Y[0])) {
		return Page;	// No update needed
	}

	// Check touches and update Page
	switch(Page) {
		case 0: // If it's in the main menu
			if(ICNT86_Dev_Now.X[0] > 10 && ICNT86_Dev_Now.X[0] < 70) Page = 1;
			else if(ICNT86_Dev_Now.X[0] > 80 && ICNT86_Dev_Now.X[0] < 140) Page = 2;
			else if(ICNT86_Dev_Now.X[0] > 150 && ICNT86_Dev_Now.X[0] < 210) Page = 3;
			else if(ICNT86_Dev_Now.X[0] > 220 && ICNT86_Dev_Now.X[0] < 280) Page = 4;
			break;
		case 1:	
			//PrintSongMenu(lib, scroll);
			break;
		case 2: // Album menu
			CheckAlbumMenu(lib, scroll);
			if (current_album[0] != '\0') {
				Page = 1; // show songs for selected album
			}
			break;
		case 3: // Artist menu
			CheckArtistMenu(lib, scroll);
			if (current_artist[0] != '\0') {
				Page = 2; // show albums for selected artist
			}
			break;
		case 4:
			//PrintPlaylisttMenu();
			break;
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
		    current_album[0] = '\0';
		    current_artist[0] = '\0';
			PrintMainMenu();
			break;
		case 1:	
			PrintSongMenu(lib, scroll);
			break;
		case 2:
			PrintAlbumMenu(lib, scroll);
			break;
		case 3:
			PrintArtistMenu(lib, scroll);
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
