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
	string industry;
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

	double *revenue, *grossProfit, *operatingIncome, *netIncome, *EBITDA;
	int num;
	getIncomeStatements(ticker, name, &revenue, &grossProfit, &operatingIncome, &netIncome, &EBITDA, &num);
	


	double momentum = avgToStrength(open);
	double volatility = beta(returns, SNPreturns);

	security sec;
	sec.ticker = ticker;
	sec.industry = "";
	sec.strength = momentum;
	sec.risk = volatility;

	return sec;
}

/* calcStrength: calculates strength of a security based on industry
 *
 * param "industry": string representing the industry of a company
 * 
 * returns: a weight scheme for equity strength, depending on the industry
 */

// Struct for weighting scheme
struct weight {
	int momentumMult;
	int volatilityMult;
	int marginMult;
};






