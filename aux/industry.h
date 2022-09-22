#pragma once

#include <iostream>
using namespace std;

struct industry {
    int count;
    char** tickers;
    double currentRatio;
    double debtEquityRatio;
    double grossMargin;
    double netProfitMargin;
    double invTurnoverRatio;
};