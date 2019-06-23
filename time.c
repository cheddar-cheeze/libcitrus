#include <stdio.h>
#include <time.h>

/*
 * formats ISO8061 time into a POSIX time structure
 */

//2019-06-21T18:01:17.625000+00:00

struct tm *timefmt(const char *str, struct tm *tm)
{
	int year;
	
	sscanf(str, "%i-%i-%iT%i:%i:%i", &year, &tm->tm_mday, &tm->tm_mon, &tm->tm_mday, &tm->tm_hour &tm->tm_min, &tm->tm_sec);
	tm->tm_year = (year - 1900);	
	
	return tm;
}
