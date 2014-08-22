#include "biosdumper.h"
#include "save_functions.h"
#include "buttontest.h"
#include "rtc.h"
#include "soundtest.h"

extern void MainMenu();
extern void draw_main_menu();
extern void waitsecs(int secs);
extern void CreditDevkitArmandtonc();

int mainmenuselected = 0;
