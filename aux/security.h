#pragma once

#include <iostream>
#include "date.h"

using namespace std;

struct security {
	string ticker;
	string industry;
	date dateAdded;
	double strength;
	double risk;
};