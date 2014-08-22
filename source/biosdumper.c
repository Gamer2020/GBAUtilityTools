#include <string.h>
#include <tonc.h>
#include <stdio.h>
#include "save_functions.h"

void biosdump(); 

typedef struct WaveData{
	u16 type;
	u16 stat;
	u32 freq;
	u32 loop;
	u32 size;
	s8 data[1];
} ALIGN(4) WaveData;

void biosdump() {

	tte_write("#{es}");

	tte_write("#{P:0,0}Bios Dumper\n");
	tte_write("Press A to start or B to cancel...\n");

	vid_vsync();
	key_poll();
	vid_vsync();
	int done = 0;

	while(done == 0){


		vid_vsync();
		key_poll();

	if (key_hit(KEY_B)){

		break;

	}
	else if (key_hit(KEY_A))
	{


		u32 *bios = (u32 *)malloc(0x4000);

		if ( bios ) {

			tte_write("Memory allocated\n");
		} else {

            tte_write("Memory allocation failure!\n");
		}

		int i;

		tte_write("Staring to dump\n");

		for (i=0; i<0x4000; i+=4)
		{
			// The MidiKey2Freq bios call allows us to read from bios
			// the lower bits are inaccurate, so just get it four times :)
			u32 a = MidiKey2Freq((WaveData *)(i-4), 180-12, 0) * 2;
			u32 b = MidiKey2Freq((WaveData *)(i-3), 180-12, 0) * 2;
			u32 c = MidiKey2Freq((WaveData *)(i-2), 180-12, 0) * 2;
			u32 d = MidiKey2Freq((WaveData *)(i-1), 180-12, 0) * 2;

			// rebuild a 32bit word from the 4 words we read
			u32 abcd =	( a & 0xff000000 ) |
						( d & 0xff000000 ) >> 8 |
						( c & 0xff000000 ) >> 16 |
						( b & 0xff000000 ) >> 24;
			bios[i/4] = abcd;
			//tte_write(abcd);
			//while(1);
			//print a # every 256 bytes
			if ( (i & 0xff) == 0 ) tte_write("#");

		}

		tte_write("\nBios has been dumped, attempting to write to SRAM.\n");



		SaveData(0, bios, 16384);


		key_poll();
		vid_vsync();

		tte_write("Bios Dumped! Press A to exit...\n");

		while(1){


			vid_vsync();
			key_poll();

			if (key_hit(KEY_A)){
				done =1;
				break;

			}

		}

	}

	}
	


}


