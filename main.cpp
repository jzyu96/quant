#include <iostream>
#include "research/constructor.cpp"

using namespace std;

int main() {

	security sec = construct("TSLA", "tesla", "2022-09-15");
	cout << sec.ticker  << "\n";

	return 0;
}
