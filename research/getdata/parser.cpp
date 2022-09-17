/* This file is intended to be used to help parse the original data that is returned by the cURL
 * http requests found in requestor.cpp.
 */

#include <iostream>
#include <string>

using namespace std;

/* extractOriginalData: a function whose purpose it is to extract the original data - 
 * the important financial statements of a given company from a large HTTP response body.
 *
 * param "readBuffer": the readBuffer is the string used to collect the HTTP response body,
 * 					   and will be dissected by this function to return the important bits
 * 
 * returns: an unparsed part of an HTTP response body
 */
char* extractOriginalData(string readBuffer) {
	const char* reader = readBuffer.c_str();
	int i = 0, n = 0;
	bool atData = false;

	// memory allocation for original data string
	char* origData = (char *)malloc(sizeof(char) * 99999);
	if (origData == NULL) {
		throw "extractOriginalData: Error, unable to malloc";
	}

	// finds the start of the Original Data field in the HTTP response
	while (! atData) {
		if (reader[i] == 'o' && reader[i + 8] == 'D' && reader[i + 15] == '[') {
			i += 16;
			break;
		} else {
			i += 1;
		}
	}

	// copies the original data string to own string
	while (reader[i] != ']') {
		origData[n] = reader[i];
		n += 1;
		i += 1;
	}

	// tack on sentinel character and return the string
	origData[n] = '\0';
	return origData;
}

/* separateField: a function that tears off a chunk of a larger string as a separated field
 *
 * param "keywordStr": the name of the section to be torn off
 * param "originalData": the originalData input
 *
 * returns: the section of the original data input with the header == keyword
 */
char* separateField(string keywordStr, string originalData) {
	const char* origData = originalData.c_str();
	const char* keyword = keywordStr.c_str();

	// memory allocation for separating a specified field (as a string)
	char* sepField = (char *)malloc(sizeof(char) * 9999);
	if (sepField == NULL) {
		throw "separateField: Error, unable to malloc";
	}

	int i = 0, j = 0;
	int len = strlen(keyword);
	bool atField = false, atData = false;

	// finds the beginning of the field in question
	while (! atField) {
		for (int n = 0; n < len; n++) {
			if (keyword[n] != origData[i + n]) {
				break;
			} else if (n == len - 1 && keyword[n] == origData[i + n]) {
				atField = true;
			}
		}
		i += 1;
	}

	// finds the start of the actual useful data entries
	while (! atData) {
		if (origData[i] == 'd' && origData[i + 2] == 'v' && origData[i + 3] == '>' && origData[i + 5] == ',') {
			atData = true;
			i += 6;
		} else {
			i += 1;
		}
	}

	// copies field name into own string
	for (int k = 0; k < len; k++) {
		sepField[j] = keyword[k];
		j += 1;
	}

	// formatting
	sepField[j] = ';';
	sepField[j + 1] = ' ';
	j += 2;

	// copies data entries into own string
	while (origData[i] != '}') {
		sepField[j] = origData[i];
		j += 1;
		i += 1;
	}

	// tack on sentinel character and return
	sepField[j] = '\0';
	return sepField;
}

/* parseToString: a function that takes an unparsed chunk of text (originalData),
 *				  and parses it into a cleaned string representing the given company's
 *				  financial statements
 *
 * param "origData": an unparsed, uncleaned string to be parsed and cleaned
 * 
 * returns: parsed, cleaned string, with form:
 * 		"Revenue; date:num, date:num, ... | GrossProfit; date:num, date:num, ... "
 */
string parseToString(string origData) {
	// Revenue, Gross Profit, EBITDA, Basic EPS	
	string rev(separateField("Revenue", origData));
	string gp(separateField("Gross Profit", origData));
	string ebitda(separateField("EBITDA", origData));
	string bEPS(separateField("Basic EPS", origData));	
	
	// return formatted string of all major financial statement fields	
	return rev + "|" + gp + "|" + ebitda + "|" + bEPS;
}

/* pricingParser: a function whose aim is to take the http response from requestPrices and parse it
 *
 * param "dataStr": an unparsed, uncleaned string to be parsed and cleaned by this function
 *
 * returns: parsed, cleaned string of pricing history
 */
char* pricingParser(string dataStr) {
	const char* data = dataStr.c_str();
	int len = strlen(data);	
	int i = 0, j = 0;
	bool atEnd = false, atBeginning = false;
	
	// memory allocation for price data
	char* priceData = (char *)malloc(sizeof(char) * len);
	if (priceData == NULL) {
		throw "pricingParser: Error, unable to malloc";
	}

	// finds the beginning of the pricing history data
	while (! atBeginning) {
	       if (data[i] == '{' && data[i + 1] == '"' && data[i + 2] == 'p' && data[i + 7] == 's') {
			atBeginning == true;
			i += 10;
			break;
		} else {
			i += 1;
		}
	}

	// copies pricing history data into own string until the end of the data
	while (! atEnd) {
		if (data[i] == ',' && data[i + 1] == '"' && data[i + 2] == 'i' && data[i + 4] == 'P' && data[i + 5] == 'e') {
			atEnd = true;
		} else {	
			priceData[j] = data[i];
			i += 1;
			j += 1;
		}
	}

	// tack on sentinel character and return pricing data
	priceData[j] = '\0';
	return priceData;
}















