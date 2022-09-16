/* This file is meant to create and calculate the simple moving average based on the price data
 *
 *
 *
 */

/* simpleMovingAVG: calculates the simple moving average of the last n number of days
 *
 * param "n": number of days from which to calculate
 * param "data": a list of historical prices, from newest to oldest
 * 
 * returns: the simple moving average of a given number of days
 */
double simpleMovingAVG(int n, double* data) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    return sum / n;
}

/* avgToStrength: returns strength based on how much higher 5 day is higher than
 *                the 200 day
 *
 * param: "data": a list of historical prices, from newest to oldest
 * 
 * returns: a double, which is the ratio of 5 day moving avg to 200 day moving avg
 *          meant to represent momentum strength
 */
double avgToStrength(double * data) {
    double Avg5 = simpleMovingAVG(5, data);
    double Avg200 = simpleMovingAVG(200, data);
    return Avg5/Avg200;
}