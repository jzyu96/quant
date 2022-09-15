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
	char* origData = (char *)malloc(sizeof(char) * 99999);
	if (origData == NULL) {
		throw "extractOriginalData: Error, unable to malloc";
	}

	while (! atData) {
		if (reader[i] == 'o' && reader[i + 8] == 'D' && reader[i + 15] == '[') {
			i += 16;
			break;
		} else {
			i += 1;
		}
	}

	while (reader[i] != ']') {
		origData[n] = reader[i];
		n += 1;
		i += 1;
	}

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
	char* sepField = (char *)malloc(sizeof(char) * 9999);
	if (sepField == NULL) {
		throw "separateField: Error, unable to malloc";
	}
	int i = 0, j = 0;
	int len = strlen(keyword);
	bool atField = false, atData = false;

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

	while (! atData) {
		if (origData[i] == 'd' && origData[i + 2] == 'v' && origData[i + 3] == '>' && origData[i + 5] == ',') {
			atData = true;
			i += 6;
		} else {
			i += 1;
		}
	}

	for (int k = 0; k < len; k++) {
		sepField[j] = keyword[k];
		j += 1;
	}

	sepField[j] = ';';
	sepField[j + 1] = ' ';
	j += 2;

	while (origData[i] != '}') {
		sepField[j] = origData[i];
		j += 1;
		i += 1;
	}

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
	
	return rev + "|" + gp + "|" + ebitda + "|" + bEPS;
}




