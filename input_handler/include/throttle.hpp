#ifndef THROTTLE
#define THROTTLE

#include <vector>
#include <numeric>      /* iota */
#include <stdlib.h>     /* abs */
#include <algorithm>    /* reverse */

std::vector<int> calculateThrottleCurve(int input_value, int previous_value);

#endif