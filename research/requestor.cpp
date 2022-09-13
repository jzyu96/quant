/* This is the requestor program; the purpose of this file is to gather financial data
 * on a given ticker from a website of our choice. This data will be passed onto another
 * program whose duty will be to parse the data. Data will be gathered by this program via
 * a GET request through HTTP or HTTPS. 
 */

#include <iostream>
#include <string>
#include <curl/curl.h>

using namespace std;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
	((string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

string constructURL(string ticker) {
	return "https://www.macrotrends.net/stocks/charts/" + ticker;
}

void request(string ticker) {
	CURL *curl;
	CURLcode resp;
	string readBuffer;
	string url = "https://www.macrotrends.net/stocks/charts/ASO/academy-sports-and-outdoors/financial-statements";	

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		resp = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		cout << readBuffer << endl;
	}
}






