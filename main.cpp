#include <iostream>
#include "research/structout.cpp"

int main() {

	security sec = construct("AAPL", "apple");
	std::cout << sec.ticker  << "\n";

	return 0;
}
