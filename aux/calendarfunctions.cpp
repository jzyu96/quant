/* This file will include calendar functions, which will be necessary in determining
 * times and differences in time and gaps in data. Generally, each year will be seen as
 * 1 unit.
 */

#include <iostream>
#include <string>

#include "date.h"

using namespace std;

/* isLeap: boolean function that returns if a year is a leap year
 */
bool isLeap(int year) {
	return (year % 4 == 0 && year % 400 != 0);
}

/* stringToDate: converts a string date into a struct date
 */
date stringToDate(string dateStr) {
	const char* dateChar = dateStr.c_str();
	int y, m, d;
	char buffer[12];
	sscanf(dateChar, "%d-%d-%d", &y, &m, &d);

	return date{y, m, d};
}

/* dateToStr: converts a struct date into a string date
 */
string dateToStr(date d) {
	char buffer[12];
	sprintf(buffer, "%i-%i-%i", d.year, d.month, d.day);
	return buffer;
}

/* distTime: functions that calculates the distance between two dates, taking a year to be
 * 		equal to 1.
 */
double distTime(string date1, string date2) {
	date d1 = stringToDate(date1), d2 = stringToDate(date2);
	return d1.year - d2.year + (d1.month - d2.month) / 12 + (d1.day - d2.day) / 365;
}

/* dateToSeconds: takes a date and calculates number of seconds since jan 1st 1970
 */
int dateToSeconds(date d) {
	int numDays = 365.25 * (d.year - 1970) + 365.25 / 12 * (d.month - 1) + d.day;
	int seconds = numDays * 86400;
	return seconds;
}