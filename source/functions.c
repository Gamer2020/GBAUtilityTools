#include <stdio.h>
#include <tonc.h>


//Small function that waits 60 frames x the input integer.
//60 frames should equal a second.
void waitsecs(int secs)
{
	int ii=0;

	while(++ii < (secs * 60))
	{		
		++ii;
		vid_vsync();
	}
}
