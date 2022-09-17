/* This is the structout file. It is responsible for constructing the researched value and feeding it
 * onto the portfolio construction algorithm.
 */

#include <iostream>
#include <string>

#include "getdata/getdata.cpp"

#include "priceanalysis/movingavg.cpp"
#include "riskanalysis/beta.cpp"


using namespace std;

struct security {
	string ticker;
	double strength;
	double risk;
};

/* construct: takes a ticker, company name, and the current date and constructs
 * 			  a struct representing the company that includes the ticker, strength, and risk
 */
security construct(string ticker, string name, string date) {
	double *open, *high, *low, *close, *adjclose, *volume, *returns;
	double *SNPopen, *SNPhigh, *SNPlow, *SNPclose, *SNPadjclose, *SNPvolume, *SNPreturns;
	getPriceHistory(ticker, date, &open, &high, &low, &close, &adjclose, &volume, &returns);
	getPriceHistory("^GSPC", date, &SNPopen, &SNPhigh, &SNPlow, &SNPclose, &SNPadjclose, &SNPvolume, &SNPreturns);

	

	



	double momentum = avgToStrength(open);
	double volatility = beta(returns, SNPreturns);

	security sec;
	sec.ticker = ticker;
	sec.strength = momentum;
	sec.risk = volatility;

	return sec;
}





