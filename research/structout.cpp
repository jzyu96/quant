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
	
	string FSorigData = requestFS(ticker, name);
	FSorigData = extractOriginalData(FSorigData);

	// cout << "Showing all parsed data" << endl << parseToString(FSorigData);


	string revDataStr = separateField("Revenue", FSorigData);
	cout << revDataStr << endl;

	double* revData = strToList(revDataStr); 
	
	for (int i = 0; i < 13; i++) {
		cout << revData[i] << endl;
	}

	sec.ticker = ticker;
	sec.strength = 0.0;
	sec.risk = 0.0;


	return sec;
}





