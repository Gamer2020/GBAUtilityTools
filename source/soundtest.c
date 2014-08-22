#include <stdio.h>
#include <string.h>
#include <tonc.h>
#include <maxmod.h>
#include "soundbank.h"
#include "soundtest.h"
#include "soundbank_bin.h"



void soundtest()
{


			tte_write("#{es}");

		tte_write("#{P:0,0}GBA Sound Test\n");
		tte_write("A song should now be playing.\n");
		tte_write("Pressing B will exit.\n");

		vid_vsync();
		key_poll();

		mmStart( MOD_SMACHOOSEAPLAYER, MM_PLAY_LOOP );

		while(key_is_up(KEY_B)){

			vid_vsync();

			mmFrame();

			key_poll();

		}

		mmStop();

}
