#pragma once

#include <iostream>

#include "../../aux/security.h"

using namespace std;

struct secList {
	security sec;
    secList* next;
};