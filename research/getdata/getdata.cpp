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
    double *returns = (double *)malloc(sizeof(double) * 1500);
    if (returns == NULL) {
        throw "getReturns: Error, unable to malloc";
    }

    for (int i = 0; i < 1500; i++) {
        returns[i] = (open[i] - close[i]) / open[i];
    }

    return returns;
}

/* getIncomeStatements: gets financial statements
 * important: Revenue, Gross Profit, Operating Income, Net Income, EBITDA 
 *
 * param "ticker": ticker of the given company
 * param "name": name of the given company
 * param "revenue": outparameter for revenue
 * param "grossProfit": outparameter for gross profit
 * param "opIncome": outparameter for operating income
 * param "netIncome": outparameter for net income
 * param "EBITDA": outparameter for EBITDA
 * param "num": outparameter for number of columns
 * 
 * returns: as out parameters
 */
void getIncomeStatements(string ticker, string name, double **revenue, double **grossProfit, double **opIncome, double **netIncome, double **EBITDA, int *num) {
    string url = constructISurl(ticker, name);
    string originalData = extractOriginalData(request(url));
    int n;

    *revenue = FSToList(separateField("Revenue", originalData), &n);
    *grossProfit = FSToList(separateField("Gross Profit", originalData), &n);
    *opIncome = FSToList(separateField("Operating Income", originalData), &n);
    *netIncome = FSToList(separateField("Net Income", originalData), &n);
    *EBITDA = FSToList(separateField("EBITDA", originalData), &n);
    *num = n;
}

/* getBalanceSheet: gets balance sheet
 * important:
 *
 * param "ticker": ticker of the given company
 * param "name": name of the given company
 * param "assets": out parameter for total assets
 * param "liabilities": out parameter for total liabilities
 * param "num": out parameter for number of entries in assets and liabilities
 * 
 * returns: as out parameters lists of quarterly overall assets and liabilities
 */
void getBalanceSheet(string ticker, string name, double **assets, double **liabilities, int *num) {
    string url = constructBSurl(ticker, name);
    string originalData = extractOriginalData(request(url));
    int n;

    char* assetStr = separateField("Total Assets", originalData);
    char* liabilityStr = separateField("Total Liabilities", originalData);

    *assets = FSToList(assetStr, &n);
    *liabilities = FSToList(liabilityStr, &n);
    *num = n;
}

/* getCashFlow: gets cash flow statement
 * important: Cash Flow From Operating Activities, Net Change in Property Plant and Equipment
 *
 * param "ticker": ticker of the given company
 * param "name": name of the given company
 * param "opActs": out parameter for cash flow from operating activities
 * param "ppe": out parameter for Net Change in Property, Plant, and Equipment
 * param "num": out parameter for number of columns
 * 
 * returns: as out parameters
 */
void getCashFlow(string ticker, string name, double **opActs, double **ppe, int *num) {
    string url = constructCFSurl(ticker, name);
    string originalData = extractOriginalData(request(url));
    int n;

    char* opActsStr = separateField("Cash Flow From Operating Activities", originalData);
    char* ppeStr = separateField("Net Change In Property, Plant, And Equipment", originalData);

    *opActs = FSToList(opActsStr, &n);
    *ppe = FSToList(ppeStr, &n);
    *num = n;
}

/* getKeyRatios: gets key financial ratios
 * important: current ratio, debt/equity, gross margin, net profit margin, inventory turnover ratio
 *
 * param "ticker": ticker of the given company
 * param "name": name of the given company
 * param "curRat": outparameter for current ratio
 * param "debEqu": outparameter for debt/equity ratio
 * param "groMar": outparameter for gross margin
 * param "netPro": outparameter for net progit margin
 * param "invRat": outparameter for inventory turnover ratio
 * param "num": outparameter for number of columns
 * 
 * returns: as out parameters
 */
void getKeyRatios(string ticker, string name, double **curRat, double **debEqu, double **groMar, double **netPro, double **invRat, int *num) {
    string url = constructKFRurl(ticker, name);
    string originalData = extractOriginalData(request(url));
    int n;

    *curRat = FSToList(separateField("Current Ratio", originalData), &n);
    *debEqu = FSToList(separateField("debt-equity-ratio", originalData), &n);
    *groMar = FSToList(separateField("Gross Margin", originalData), &n);
    *netPro = FSToList(separateField("Net Profit", originalData), &n);
    *invRat = FSToList(separateField("Inventory Turnover Ratio", originalData), &n);
    *num = n;
}

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
    string url = constructPricesURL(ticker, date);
    string PricesData = request(url);
	PricesData = pricingParser(PricesData);

    *open = PricesToList("open", PricesData);
    *high = PricesToList("high", PricesData);
    *low = PricesToList("low", PricesData);
    *close = PricesToList("close", PricesData);
    *adjclose = PricesToList("adjclose", PricesData);
    *volume = PricesToList("volume", PricesData);
    *returns = getReturns(*open, *close);
}