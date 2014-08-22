/*
 * buttontest.c
 *
 *  Created on: Jul 16, 2013
 *      Author: Gamer2020
 */

#include <stdio.h>
#include <string.h>
#include <tonc.h>
#include "buttontest.h"


void buttontest()
{



	vid_vsync();
	key_poll();
	while(key_is_up(KEY_B)){

		vid_vsync();
		key_poll();


			tte_write("#{es}");

		tte_write("#{P:0,0}GBA Button Test\n");
		tte_write("Hold buttons to test. B will exit.\n");

		if (key_held(KEY_L)){
			tte_write("L\n");
		}

		if (key_held(KEY_R)){
			tte_write("R\n");
		}

		if (key_held(KEY_UP)){
			tte_write("Up\n");
		}

		if (key_held(KEY_DOWN)){
			tte_write("Down\n");
		}

		if (key_held(KEY_LEFT)){
			tte_write("Left\n");
		}

		if (key_held(KEY_RIGHT)){
			tte_write("Right\n");
		}



		if (key_held(KEY_START)){
			tte_write("Start\n");
		}

		if (key_held(KEY_SELECT)){
			tte_write("Select\n");
		}

		if (key_held(KEY_A)){
			tte_write("A\n");
		}

		if (key_held(KEY_B)){
			tte_write("B\n");
		}

		vid_vsync();
		key_poll();

	}

}
