/* calculates Beta
 */

/* mean: calculates the mean returns of the last n number of days
 *
 * param "n": number of days from which to calculate
 * param "data": a list of historical returns, from newest to oldest
 * 
 * returns: the mean return of a given number of days
 */
double mean(int n, double* data) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    return sum / n;
}

/* covariance: calculate the covariance between variable x and variable y
 * x is the return of the individual stock
 * y is the return of the market
 * 
 * param "sec": sec is the list of historical returns of the security in question
 * param "snp": snp is the list of historical returns of the S&P 500
 * 
 * returns: the calculated covariance between the given security and the S&P
 */
double covariance(double *sec, double *snp) {
    int numDays = 1255; // five year time span (trading days only)
    double meanX = mean(numDays, sec), meanY = mean(numDays, snp);
    double sum = 0.0;

    for (int i = 0; i < numDays; i++) {
        sum += (sec[i] - meanX) * (snp[i] - meanY);
    }

    return sum / (numDays - 1);
}

/* variance: calculate the variance of a variable x
 * x is the return of an individual stock
 *
 * param "sec": sec is the list of historical returns of the given security
 * 
 * returns: the calculated variance of a given security
 */
double variance(double *sec) {
    int numDays = 1255; // five year time span (trading days only)
    double meanX = mean(numDays, sec); 
    double sum = 0.0;

    for (int i = 0; i < numDays; i++) {
        sum += (sec[i] - meanX) * (sec[i] - meanX);
    }

    return sum / (numDays - 1);
}

/* beta: calculate beta [covariance / variance] over time period 5 years
 *
 * param "sec": sec is the list of historical returns of the security in question
 * param "snp": snp is the list of historical returns of the S&P 500
 * 
 * returns: calculated financial beta
 */
double beta(double *sec, double* snp) {
    return covariance(sec, snp) / variance(sec);
}