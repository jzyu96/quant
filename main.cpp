#include <iostream>
#include "research/constructor.cpp"

#include "aux/industry.h"
#include "aux/industryCSV.cpp"
#include "aux/industries/auto.csv"


using namespace std;

int main() {
	
	industry autoInd = CSVtoIndustry("auto");
	cout << autoInd.count << endl;


	/*

	security sec = construct("TSLA", "tesla", "auto", "2022-09-16");
	cout << sec.ticker  << endl;
	cout << sec.strength << endl;
	cout << sec.risk << endl;


	*/

	return 0;
}
