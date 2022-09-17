#include <iostream>
#include "research/constructor.cpp"

using namespace std;

int main() {

	security sec = construct("TSLA", "tesla", "2022-09-16");
	cout << endl;
	cout << sec.ticker  << endl;
	cout << sec.strength << endl;
	cout << sec.risk << endl;

	return 0;
}
