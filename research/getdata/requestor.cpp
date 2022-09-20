/* This is the requestor program; the purpose of this file is to gather financial data
 * on a given ticker from a website of our choice. This data will be passed onto another
 * program whose duty will be to parse the data. Data will be gathered by this program via
 * a GET request through HTTP or HTTPS. 
 */

#include <iostream>
#include <string>
#include <cstring>
#include <curl/curl.h>

#include "calendarfunctions.cpp"

using namespace std;

/* WriteCallback is a transparent function to the user; its purpose is to record the
 * response of the HTTP request
 */
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
	((string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

/* constructISURL: takes the ticker and the name and constructs the URL of the financial-statements, income statement
 * page of the given company on macrotrends.net
 *
 * param "ticker": ticker of the given security
 * param "name": name of the given security
 * 
 * returns: URL as described above
 */
string constructISurl(string ticker, string name) {
	return "https://www.macrotrends.net/stocks/charts/" + ticker + "/" + name + "/financial-statements?freq=Q";
}

/* constructBSURL: takes the ticker and the name and constructs the URL of the financial-statements, balance sheet
 * page of the given company on macrotrends.net
 *
 * param "ticker": ticker of the given security
 * param "name": name of the given security
 * 
 * returns: URL as described above
 */
string constructBSurl(string ticker, string name) {
	return "https://www.macrotrends.net/stocks/charts/" + ticker + "/" + name + "/balance-sheet?freq=Q";
}

/* constructCFSURL: takes the ticker and the name and constructs the URL of the financial-statements, key financial ratios
 * page of the given company on macrotrends.net
 *
 * param "ticker": ticker of the given security
 * param "name": name of the given security
 * 
 * returns: URL as described above
 */
string constructCFSurl(string ticker, string name) {
	return "https://www.macrotrends.net/stocks/charts/" + ticker + "/" + name + "/cash-flow-statement?freq=Q";
}


/* constructKFRURL: takes the ticker and the name and constructs the URL of the financial-statements, key financial ratios
 * page of the given company on macrotrends.net
 *
 * param "ticker": ticker of the given security
 * param "name": name of the given security
 * 
 * returns: URL as described above
 */
string constructKFRurl(string ticker, string name) {
	return "https://www.macrotrends.net/stocks/charts/" + ticker + "/" + name + "/financial-ratios?freq=Q";
}

/* constructPricesURL: takes the ticker of the given company and construct the URL of the historical prices
 * page for the company on yahoo finance. Daily prices for the past 5 years.
 *
 * param "ticker": ticker of the given company
 * param "d": a string representing the date [year-mo-da]
 *
 * returns: a string equal to the url of the yahoo finance historical pricing page
 */
string constructPricesURL(string ticker, string d) {
	date today = stringToDate(d);
	date fivePrior = today;
	fivePrior.year -= 5;
	string URL = "https://finance.yahoo.com/quote/" + ticker + "/history?period1=" +
				to_string(dateToSeconds(fivePrior)) + "&period2=" +
				to_string(dateToSeconds(today)) + "&interval=1d&filter=history&frequency=1d&includeAdjustedClose=true";
	return URL;
}

/* request: formulates and sends an HTTP request via cURL
 *
 * param "URL": a given URL to be requested
 *
 * returns: a string representing unparsed pricing data
 */
string request(string url) {
	CURL *curl;
	CURLcode resp;
	string readBuffer;

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
















