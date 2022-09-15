/* This is the list constructor program that takes a formatted string containing parsed and cleaned financial data
 * and returns several different arrays, including, but not limited to Revenue, Gross Profit, and EBITDA.
 */

#include <iostream>
#include <string>

/* strToList: takes a string and turns it into a list 
 *
 * param "data": a string containing yearly data
 * param "num": out parameter for number of numbers in the array
 *
 * returns: a list of a specific data category, in yearly order, starting with most recent
 */
double* strToList(string data, int *num) {
	int i = 0, j = 0, k = 0, n = 1; // count number of commas; num commas + 1 = num data entries
	while (data[i] != '\0') {
		if (data[i] == ',') {
			n += 1;
		}
		i += 1;
	}

	double* dataList = (double *)malloc(sizeof(double) * n);
	if (dataList == NULL) {
		throw "strToList: Error, unable to malloc";
	}

	while (data[j] != '\0') {
		if (data[j] == ':') {
			j += 2;
			string num = "";
			while (data[j] != '"') {
				num += data[j];
				j += 1;
			}
			if (num == "") {
				num = "0.0";
			}
			dataList[k] = stod(num);
			k += 1;
		} else {
			j += 1;
		}
	}

	*num = n;
	return dataList;
}


