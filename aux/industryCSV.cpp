#include <iostream>
#include <stdio.h>
#include "industry.h"

#define MAX_ORDER_LEN 1000
#define MAX_TEST_FILENAME 30

/* IndustryToCSV:
 *
 */
void IndustryToCSV(string indName) {
    char read_file[MAX_TEST_FILENAME];
    sprintf(read_file, "%s.csv", indName);
    FILE *read = fopen(read_file, "r");
    int c = fgetc(read);

    while (c != EOF) {

    }


}

/* CSVtoIndustry:
 *
 */
industry CSVtoIndustry(string indName) {
    char write_file[MAX_TEST_FILENAME];
    sprintf(write_file, "%s.csv", indName);
    FILE *write = fopen(write_file, "w");



    industry ind;

    return ind;
}