#include "ScreenFunction.h"
#include "song.h"
#include "musiclibrary.h"

#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>

#define CHIP "/dev/gpiochip0"
// List of GPIO pins (BCM numbering)
int pins[5] = {16, 20, 13, 19, 21}; 
// 20 = Round
// 16 = Play
// 13 = Up
// 19 = Down
// 21 = Large button
int power_pin = 26;	// The "power" GPIO

// Current page
UBYTE Page = 0;
UBYTE OldPage = 0;
// current page scroll level
int scroll = 0; 
int oldScroll = 0;

int main()
{

	// the music library
	MusicLibrary lib;
    init_library(&lib);

    // Scan your Music folder (adjust path if needed)
    scan_folder(&lib, "./Music");

    printf("Found %zu songs:\n", lib.count);
    print_songs(&lib);

	ScreenSetup();

	//--
	struct gpiod_chip *chip;
    struct gpiod_line *button_lines[5];
    struct gpiod_line *power_line;

    chip = gpiod_chip_open(CHIP);
    if (!chip) {
        perror("gpiod_chip_open");
        return 1;
    }

    // Configure buttons as inputs
    for (int i = 0; i < 5; i++) {
        button_lines[i] = gpiod_chip_get_line(chip, pins[i]);
        if (!button_lines[i]) {
            fprintf(stderr, "Failed to get GPIO %d\n", pins[i]);
            return 1;
        }
        if (gpiod_line_request_input(button_lines[i], "button") < 0) {
            fprintf(stderr, "Failed to request input on GPIO %d\n", pins[i]);
            return 1;
        }
    }

    // Configure power pin as output, set high
    power_line = gpiod_chip_get_line(chip, power_pin);
    if (!power_line) {
        fprintf(stderr, "Failed to get GPIO %d\n", power_pin);
        return 1;
    }
    if (gpiod_line_request_output(power_line, "power", 1) < 0) {
        fprintf(stderr, "Failed to request GPIO %d as output\n", power_pin);
        return 1;
    }

    printf("Power pin %d set HIGH, scanning buttons...\n", power_pin);
	//--

	Page = 0;
	//---------------------------------
	// This is the main loop
	//---------------------------------
	while(1) {
		
		// Check if the screen is pressed and the page needs to be changed
		OldPage = Page;
		Page = ChechMenu(Page);

		if ( OldPage != Page ) { // If the page needs to be updated
			scroll = 0; // reset scroll when i get to a new page
			UpdateScreen(&lib, scroll, Page);
		}

		for (int i = 0; i < 5; i++) { // Check every button

            int value = gpiod_line_get_value(button_lines[i]);

            if (value < 0) { // If the read gpio returns an error
                fprintf(stderr, "Error reading GPIO %d\n", pins[i]);
                continue;
            }
            if (value == 1) { // If the button is pressed

				if ( pins[i] == 13 ) scroll -= 1; // Scroll up
				if ( pins[i] == 19 ) scroll += 1; // Scroll down

				if(scroll < 0) scroll = 0; // Min scroll
				if(scroll > lib.count / 10) scroll = lib.count / 10; // Max scroll

				if ( pins[i] == 21 ) Page = 0; // return to the main menu

				UpdateScreen(&lib, scroll, Page);
            }
        }

		DEV_Delay_ms(50);
	}
	//---------------------------------
	
	free_library(&lib);	
	gpiod_chip_close(chip);

	return 0;
}
