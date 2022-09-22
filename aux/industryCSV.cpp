#include <iostream>
#include <cstdio>
#include "industry.h"

using namespace std;

#define MAX_IND_FILENAME 30
#define MAX_CSV_LEN 500

/* IndustryToCSV:
 *
 *
void IndustryToCSV(string indName) {
    char write_file[MAX_IND_FILENAME];
    sprintf(write_file, "%s.csv", indName);
    FILE *write = fopen(write_file, "w");



}
*/

/* CSVtoIndustry:
 *
 */
industry CSVtoIndustry(string indNameStr) {
    const char *indName = indNameStr.c_str();
    char read_file[MAX_IND_FILENAME];
    sprintf(read_file, "%s.csv", indName);
    FILE *read = fopen(read_file, "r");

    cout << "made it here" << endl;
    int c = fgetc(read), i = 0, n = 0;

    cout << "made it here" << endl;

    

    char** structs = (char **)malloc(sizeof(char*) * 7);
    for (int j = 0; j < 7; j++) {
        char arr[MAX_CSV_LEN];
        structs[j] = arr;
    }

    while (c != EOF) {
        int k = 0;
        while (c != EOF && c != ',') {
            structs[n][k] = c;
            k += 1;
            i += 1;
            c = fgetc(read);
        }
        structs[n][k] = '\n';
        n += 1;
    }

    industry retInd;
    retInd.count = stoi(structs[0]);
    retInd.tickers = NULL;
    retInd.currentRatio = stod(structs[2]);
    retInd.debtEquityRatio = stod(structs[3]);
    retInd.grossMargin = stod(structs[4]);
    retInd.netProfitMargin = stod(structs[5]);
    retInd.invTurnoverRatio = stod(structs[2]);

    return retInd;
}