/* This is the structout file. It is responsible for constructing the researched value and feeding it
 * onto the portfolio construction algorithm.
 */

#include <iostream>
#include <string>

#include "getdata/requestor.cpp"
#include "getdata/parser.cpp"
#include "getdata/listconstructor.cpp"


using namespace std;

struct security {
	string ticker;
	double strength;
	double risk;
};

security construct(string ticker, string name) {
	security sec;

	/*	
	string FSorigData = requestFS(ticker, name);
	FSorigData = extractOriginalData(FSorigData);

	// cout << "Showing all parsed data" << endl << parseToString(FSorigData);


	string revDataStr = separateField("Revenue", FSorigData);
	cout << revDataStr << endl;

	int len;
	double* revData = strToList(revDataStr, &len); 	

	for (int i = 0; i < len; i++) {
		cout << revData[i] << endl;
	}
	*/

	string PricesData = requestPrices(ticker);

	PricesData = pricingParser(PricesData);

	double* openData = listFromKey("open", PricesData);	

	cout << openData[0] << endl;

	sec.ticker = ticker;
	sec.strength = 0.0;
	sec.risk = 0.0;


	return sec;
}





