/* This is the requestor program; the purpose of this file is to gather financial data
 * on a given ticker from a website of our choice. This data will be passed onto another
 * program whose duty will be to parse the data. Data will be gathered by this program via
 * a GET request through HTTP or HTTPS. 
 */

#include <iostream>
#include <string>
#include <cstring>
#include <curl/curl.h>

using namespace std;

/* WriteCallback is a transparent function to the user; its purpose is to record the
 * response of the HTTP request
 */
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
	((string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

/* constructPricesURL: takes the ticker and the name and constructs the URL of the stock price history page
 * of the given company on macrotrends.net
 *
 * param "ticker": ticker of the given security
 * param "name": name of the given security
 * 
 * returns: URL as described above
 */
string constructPricesURL(string ticker, string name) {
	return "https://www.macrotrends.net/stocks/charts/" + ticker + "/" + name + "/stock-price-history";
}

/* requestPrices: formulates and sends an HTTP request via cURL, and downloads the stock price
 * 				  history linked at that page
 *
 * param "ticker": the ticker of a given security
 * param "name": the name of a given security
 * 
 * returns: a csv file representing past stock prices
 */
string requestPrices(string ticker, string name) {
	CURL *curl;
	CURLcode resp;
	string readBuffer, originalData, parsedData;
	string url = constructPricesURL(ticker, name) + "/MacroTrends_Data_Download_" + ticker + ".cs";	
	

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		resp = curl_easy_perform(curl);
		if (resp == CURLE_OK) {
			long http_code;
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
			cout << http_code << endl;
		}
		curl_easy_cleanup(curl);

		// originalData = extractOriginalData(readBuffer);

		
	}

	return parsedData;
}

/* constructFSURL: takes the ticker and the name and constructs the URL of the financial-statements page
 * of the given company on macrotrends.net
 *
 * param "ticker": ticker of the given security
 * param "name": name of the given security
 * 
 * returns: URL as described above
 */
string constructFSURL(string ticker, string name) {
	return "https://www.macrotrends.net/stocks/charts/" + ticker + "/" + name + "/financial-statements";
}

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

/* parseToString: a function that takes an unparsed chunk of text (originalData),
 *				  and parses it into a cleaned string representing the given company's
 *				  financial statements
 *
 * param "origData": an unparsed, uncleaned string to be parsed and cleaned
 * 
 * returns: parsed, cleaned string, with form:
 * 		"Revenue; "
 * 
 * 
 */
string parseToString(string origData) {
	return "parsed";
}

/* requestFS: formulates and sends an HTTP request via cURL
 *
 * param "ticker": the ticker of a given security
 * param "name": the name of a given security
 * 
 * returns: a string representing the parsed data
 */
string requestFS(string ticker, string name) {
	CURL *curl;
	CURLcode resp;
	string readBuffer, originalData, parsedData;
	string url = constructFSURL(ticker, name);	

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		resp = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		originalData = extractOriginalData(readBuffer);
		parsedData = parseToString(originalData);

		cout << parsedData << endl;
	}

	return parsedData;
}






