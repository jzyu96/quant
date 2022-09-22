/* This file will be used to calculate the industry mean
 */

#include <iostream>
#include "../../aux/industry.h"

/* updateIndustryMean:
 *

struct industry {
    int count;
    char** tickers;
    double currentRatio;
    double debtEquityRatio;
    double grossMargin;
    double netProfitMargin;
    double invTurnoverRatio;
};


 * param "industryName": a string representing the industry
 * param ""
 */
industry addIndustryMeans(industry ind, char* ticker, double curRat, double debtEquity, double groMar, double netPro, double invTurn) {
    int n = ind.count + 1;
    ind.tickers[ind.count] = ticker;
    ind.currentRatio = (ind.currentRatio * ind.count + curRat) / n;
    ind.debtEquityRatio = (ind.debtEquityRatio * ind.count + debtEquity) / n;
    ind.grossMargin = (ind.grossMargin * ind.count + groMar) / n;
    ind.netProfitMargin = (ind.netProfitMargin * ind.count + netPro) / n;
    ind.invTurnoverRatio = (ind.invTurnoverRatio * ind.count + invTurn) / n;
    ind.count = n;

    return ind;
}



industry updateIndustryMeans(industry ind, char* ticker, double curRat, double debtEquity, double groMar, double netPro, double invTurn) {
    int n = ind.count - 1;
    ind.tickers[ind.count] = ticker;
    ind.currentRatio = (ind.currentRatio * n + curRat) / ind.count;
    ind.debtEquityRatio = (ind.debtEquityRatio * n + debtEquity) / ind.count;
    ind.grossMargin = (ind.grossMargin * n + groMar) / ind.count;
    ind.netProfitMargin = (ind.netProfitMargin * n + netPro) / ind.count;
    ind.invTurnoverRatio = (ind.invTurnoverRatio * n + invTurn) / ind.count;

    return ind;
}



