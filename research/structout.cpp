/* This is the structout file. It is responsible for constructing the researched value and feeding it
 * onto the portfolio construction algorithm.
 */

#include <iostream>
#include <string>
#include "requestor.cpp"

using namespace std;

struct security {
	string ticker;
	double strength;
	double risk;
};

security construct(string ticker, string name) {
	security sec;
	
	requestPrices(ticker, name);	

	sec.ticker = ticker;
	sec.strength = 0.0;
	sec.risk = 0.0;


	return sec;
}





