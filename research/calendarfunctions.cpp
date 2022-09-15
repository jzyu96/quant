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

bool isLeap?(int year) {
	return (year % 4 == 0 && year % 400 != 0);
}

date stringToDate(string d) {
	int y, m, day;
	sscanf(d, "%i-%i-%i", &y, &m, &day);
	return date{y, m, day};

double distTime(string date1, string date2) {
	date d1 = stringToDate(date1), d2 = stringToDate(date2);
	return dist = d1.year - d2.year + (d1.month - d2.month) / 12 + (d1.day - d2.day) / 365;
}


