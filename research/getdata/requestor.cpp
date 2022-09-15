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
	}
	return readBuffer;
}






