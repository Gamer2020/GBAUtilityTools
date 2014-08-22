#include "rtc_strings.h"

typedef struct RTCTime
{
	u16 year;
	u8 month;
	u8 day;
	u8 dayofweek;
	u8 hours;
	u8 minutes;
	u8 seconds;
} RTCTime;

extern void RTC_Main();

extern void RTC_TurnOn();
extern void RTC_GetTime();

	extern void rtc_cmd(int v);
	extern void rtc_data(int v);
	extern int rtc_read(void);
	extern void rtc_enable(void);
	extern int rtc_check(void);
	extern int rtc_get(char *data);

