/* A file meant to amalgamate all getting, cleaning, and information parsing 
 * functions.
 */

#include <iostream>
#include <string>

#include "requestor.cpp"
#include "parser.cpp"
#include "listconstructor.cpp"

/* getReturns: gets the returns from day to day
 * (open - closed) / open
 * 
 * param "open": list of day-open historical price data
 * param "close": list of day-close historical price data
 * 
 * returns: list of returns per day
 */
double* getReturns(double* open, double* close) {
    double *returns = (double *)malloc(sizeof(double) * 1850);
    if (returns == NULL) {
        throw "getReturns: Error, unable to malloc";
    }

    for (int i = 0; i < 1825; i++) {
        returns[i] = (open[i] - close[i]) / open[i];
    }

    return returns;
}

/* getFinancialStatements: gets financial statements
 *
 * 
 */

/* getPriceHistory: gets historical price data
 *
 * param "ticker": ticker of the company in question
 * param "date": the current date
 * 
 * param "open": outparameter for opening prices
 * param "high": outparameter for highest price
 * param "low": outparameter for lowest price
 * param "close": outparameter for closing price
 * param "adjclose": outparameter for adjusted closing price
 * param "volume": outparameter for volume
 * param "returns": outparameter for returns
 */
void getPriceHistory(string ticker, string date, double **open, double **high, double **low, double **close, double **adjclose, double **volume, double **returns) {
    string PricesData = requestPrices(ticker, date);
	PricesData = pricingParser(PricesData);

    *open = PricesToList("open", PricesData);
    *high = PricesToList("high", PricesData);
    *low = PricesToList("low", PricesData);
    *close = PricesToList("close", PricesData);
    *adjclose = PricesToList("adjclose", PricesData);
    *volume = PricesToList("volume", PricesData);
    *returns = getReturns(*open, *close);
}