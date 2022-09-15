/* This file will include calendar functions, which will be necessary in determining
 * times and differences in time and gaps in data. Generally, each year will be seen as
 * 1 unit.
 */

#include <iostream>
#include <string>

using namespace std;

struct date {
	int year;
	int month;
	int day;
};

/* isLeap?: boolean function that returns if a year is a leap year
 */
bool isLeap?(int year) {
	return (year % 4 == 0 && year % 400 != 0);
}

/* stringToDate: converts a string date into a struct date
 */
date stringToDate(string d) {
	int y, m, day;
	sscanf(d, "%i-%i-%i", &y, &m, &day);
	return date{y, m, day};

/* distTime: functions that calculates the distance between two dates, taking a year to be
 * 		equal to 1.
 */
double distTime(string date1, string date2) {
	date d1 = stringToDate(date1), d2 = stringToDate(date2);
	return dist = d1.year - d2.year + (d1.month - d2.month) / 12 + (d1.day - d2.day) / 365;
}

/* yahooDate: takes a yahoo date and converts it to a normal calendar date
 */
date yahooDate(int yDay) {	// days since jan 1st 1970
	int days = yDay / 86400;
	

	return date{0, 0, 0};
}

