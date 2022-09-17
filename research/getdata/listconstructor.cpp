/* This is the list constructor program that takes a formatted string containing parsed and cleaned financial data
 * and returns several different arrays, including, but not limited to Revenue, Gross Profit, and EBITDA.
 */

#include <iostream>
#include <string>

/* FSToList: takes a financial statements string and turns it into a list 
 *
 * param "data": a string containing yearly data
 * param "num": out parameter for number of numbers in the array
 *
 * returns: a list of a specific data category, in yearly order, starting with most recent
 */
double* FSToList(string data, int *num) {
	int i = 0, j = 0, k = 0, n = 1; 
	// count number of commas; num commas + 1 = num data entries
	while (data[i] != '\0') {
		if (data[i] == ',') {
			n += 1;
		}
		i += 1;
	}

	// allocate memory for the datalist
	double* dataList = (double *)malloc(sizeof(double) * n);
	if (dataList == NULL) {
		throw "strToList: Error, unable to malloc";
	}

	// constructing the list of dataentries
	while (data[j] != '\0') {
		if (data[j] == ':') {
			j += 2;
			// construct string, then convert to number
			string num = "";
			while (data[j] != '"') {
				num += data[j];
				j += 1;
			}
			// account for gaps in data
			if (num == "") {
				num = "0.0";
			}
			// set datalist entry
			dataList[k] = stod(num);
			k += 1;
		} else {
			j += 1;
		}
	}

	// set out-parameter and return result
	*num = n;
	return dataList;
}

/* PricesToList: takes a key, namely "date", "open", "high", "close", "low", "volume", or
 * 		"adjclose" and creates a list out of the larger data set, including only 
 * 		the necessary data
 * 
 * param "keyword": the keyword of the field of data to be extracted
 * param "dataStr": the overall data (in string form) to be parsed
 *
 * returns: a list of data for the given field
 */
double* PricesToList(string keyword, string dataStr) {
	const char* key = keyword.c_str();
	const char* data = dataStr.c_str();
	int keylen = strlen(key);
	int i = 0, n = 0;

	// allocate memory for list
	double* list = (double *)malloc(sizeof(double) * 2000);
	if (list == NULL) {
		throw "listFromKey: Error, unable to malloc";
	}

	// construct a list from given data
	while (data[i] != ']') {
		// finds start of each set of data entries
		if (data[i] == '{') { 
			bool atKey = false;
			string num = "";
			// finds the specified key within set of data entry
			while (! atKey) {
				for (int j = 0; j < keylen; j++) {
					if (data[i + j] != key[j]) {
						break;
					} else if (j == keylen - 1) {
						atKey = true;
						i += j + 2;
					}
				}
				i += 1;
			}
			// copies data at specified key
			while (data[i] != ',' && data[i] != '}') {
				num += data[i];
				i += 1;
			}
			// converts string to number and adds to list
			list[n] = stod(num);
			n += 1;
		}
		i += 1;
	}

	return list;
}
