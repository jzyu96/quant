#include <iostream>
#include "research/structout.cpp"

int main() {

	security sec = construct("TSLA", "tesla");
	std::cout << sec.ticker  << "\n";

	return 0;
}
