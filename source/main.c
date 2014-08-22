
#include <stdio.h>
#include <string.h>
#include <tonc.h>
#include <maxmod.h>
#include "soundbank.h"
#include "soundbank_bin.h"
#include "GBAUtilties.h"


int main()
{
	// Init interrupts and VBlank irq.

	irq_init(NULL);
	irq_add(II_VBLANK, mmVBlank);
	mmInitDefault( (mm_addr)soundbank_bin, 8 );
	
	CreditDevkitArmandtonc();

MainMenu();
	
	while(1)
	{
		VBlankIntrWait();
	}
	
	return 0;
}
void MainMenu()
{
	//This function brings up the main menu and has it do stuff.

	RegisterRamReset(RESET_GFX);

	REG_DISPCNT= DCNT_MODE0 | DCNT_BG0;

	tte_init_chr4c(0, 			// BG 0
		BG_CBB(0)|BG_SBB(31),	// Charblock 0; screenblock 31
		0xF000,					// Screen-entry offset
		bytes2word(1,2,0,0),	// Color attributes.
		CLR_WHITE, 			// White text
		&verdana9Font,			// Verdana 9 font
		NULL
		);

	vid_vsync();
	draw_main_menu();



	while(1){


		vid_vsync();
		mmFrame();
		key_poll();


//This code is still being worked on but it will handle what is selected on the menu.
		    if (key_hit(KEY_DOWN)){
		    	mainmenuselected++;
	           if (mainmenuselected > 3){
	        	   mainmenuselected = 3;
			   }

			    draw_main_menu();

			}else if (key_hit(KEY_UP)){
				mainmenuselected = mainmenuselected - 1;

			   if (mainmenuselected < 0){
				   mainmenuselected = 0;
			   }
			    draw_main_menu();
			}else if (key_hit(KEY_B)){

			}else if (key_hit(KEY_A)){

	          if (mainmenuselected == 0){
			  


	        	  biosdump();
	        	  vid_vsync();
	              draw_main_menu();
	
	
		   }else if (mainmenuselected == 1){
			   
			   buttontest();
			   vid_vsync();
			   draw_main_menu();
		   }else if (mainmenuselected == 2){

			   RTC_Main();
			   vid_vsync();
			   draw_main_menu();
		   }else if (mainmenuselected == 3){

			   soundtest();
			   vid_vsync();

			   draw_main_menu();
		   }

		}

	}
}

void draw_main_menu()
{
//This function handles the text for the menu and handles what option is currently selected.


	tte_write("#{es}");
	tte_write("#{P:0,0}   GBA Utility Tools v0.1 By: Gamer2020\n");

		if (mainmenuselected == 0){
			tte_write("  > Dump Bios\n");
		}else{
			tte_write("     Dump Bios\n");
		}

		if (mainmenuselected == 1){
			tte_write("  > Button Test\n");
		}else{
			tte_write("     Button Test\n");
		}

		if (mainmenuselected == 2){
			tte_write("  > RTC Test\n");
		}else{
			tte_write("     RTC Test\n");
		}
		if (mainmenuselected == 3){
			tte_write("  > Sound Test\n");
		}else{
			tte_write("     Sound Test\n");
		}

}

void CreditDevkitArmandtonc()
{
	RegisterRamReset(RESET_GFX);

	REG_DISPCNT= DCNT_MODE0 | DCNT_BG0;

	tte_init_chr4c(0, 			// BG 0
		BG_CBB(0)|BG_SBB(31),	// Charblock 0; screenblock 31
		0xF000,					// Screen-entry offset
		bytes2word(1,2,0,0),	// Color attributes.
		CLR_WHITE, 			// White text
		&verdana9Font,			// Verdana 9 font
		NULL
		);

	vid_vsync();
	tte_write("#{P:35,60}Credit to Wintermute for devkitARM!\n");
	tte_write("#{P:35,70}Credit to Cern for Tonc!");

	waitsecs(7);
}
