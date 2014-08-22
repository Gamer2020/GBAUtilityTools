#include <string.h>
#include <tonc.h>
#include <stdio.h>
#include "rtc.h"



int haveRTC;
RTCTime myTime;

#define UNBCD(x) (((x) & 0xF) + (((x) >> 4) * 10))

char main_tmp[50];


void RTC_Main()
{

	tte_write("#{es}");

	tte_write("#{P:0,0}RTC Test\n");
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
		RTC_TurnOn();

		if (haveRTC ==1){

			RTC_GetTime();


			tte_write(Hoursofday[myTime.hours]);
			tte_write(":");

			tte_write(Mins_secs[myTime.minutes]);


						tte_write(":");

						tte_write(Mins_secs[myTime.seconds]);

						tte_write(" on ");

						tte_write(day_of_week[myTime.dayofweek]);

						tte_write(". the ");

						tte_write(DaysinMonNum[myTime.day]);

						tte_write(" of ");

						tte_write(Months_short[myTime.month - 1]);

						tte_write(". of ");


						tte_write(YearsToCome[(myTime.year - 1990)]);

						tte_write("\n");

			tte_write("RTC displayed! Press A to exit...\n");

		}else{
			tte_write("RTC not detected!\nPress A to exit...\n");
		}


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

void RTC_TurnOn()
{
	rtc_enable();
	haveRTC = rtc_check();
	rtc_get(main_tmp);
}

void RTC_GetTime()
{
	char data[7];



	rtc_get(data);

	myTime.year = UNBCD(data[0]) + 2000;
	myTime.month = UNBCD(data[1]);
	myTime.day = UNBCD(data[2] & 0x3F);
	myTime.dayofweek = UNBCD(data[3] & 0x3F); //rtc_read();
	myTime.hours = UNBCD(data[4] & 0x3F);
	myTime.minutes = UNBCD(data[5]);
	myTime.seconds = UNBCD(data[6]);

}

#define RTC_DATA ((volatile u16 *)0x080000C4)
#define RTC_RW ((volatile u16 *)0x080000C6)
#define RTC_ENABLE ((volatile u16 *)0x080000C8)

void rtc_cmd(int v)
{
	int l;
	u16 b;

	v = v<<1;

	for(l=7; l>=0; l--)
	{
		b = (v>>l) & 0x2;
		*RTC_DATA = b | 4;
		*RTC_DATA = b | 4;
		*RTC_DATA = b | 4;
		*RTC_DATA = b | 5;
	}
}

void rtc_data(int v)
{
	int l;
	u16 b;

	v = v<<1;

	for(l=0; l<8; l++)
	{
		b = (v>>l) & 0x2;
		*RTC_DATA = b | 4;
		*RTC_DATA = b | 4;
		*RTC_DATA = b | 4;
		*RTC_DATA = b | 5;
	}
}

int rtc_read(void)
{
	int j,l;
	u16 b;
	int v = 0;


	for(l=0; l<8; l++)
	{
		for(j=0;j<5; j++)
			*RTC_DATA = 4;
		*RTC_DATA = 5;
		b = *RTC_DATA;
		v = v | ((b & 2)<<l);
	}

	v = v>>1;

	return v;
}

static int check_val = 0;

void rtc_enable(void)
{
	*RTC_ENABLE = 1;

	*RTC_DATA = 1;
	*RTC_DATA = 5;
	*RTC_RW = 7;

	rtc_cmd(0x63);

	*RTC_RW = 5;

	check_val =  rtc_read();
}

// Normally returns 0x40
int rtc_check(void)
{
	return (check_val != 0);
}

int rtc_get(char *data)
{
	int i;

	*RTC_DATA = 1;
	*RTC_RW = 7;

	*RTC_DATA = 1;
	*RTC_DATA = 5;

	rtc_cmd(0x65);

	*RTC_RW = 5;

	for(i=0; i<4; i++)
		data[i] = (char)rtc_read();

	*RTC_RW = 5;

	for(i=4; i<7; i++)
		data[i] = (char)rtc_read();

	return 0;
}
