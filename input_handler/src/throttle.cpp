#include"../include/throttle.hpp"

std::vector<int> calculateThrottleCurve(int input_value, int previous_value) {
    /* This function gets a new input value and the previous value, and returns
     * a vector containing the sequential throttle responses. If the new value
     * is the same as the old, an empty vector is returned.
     */ 
    int size = std::abs(input_value - previous_value);
    std::vector<int> return_val(size);

    if (input_value > previous_value) {
        std::iota (return_val.begin(), return_val.end(), previous_value+1);
    } else if (input_value < previous_value) {
        std::iota(return_val.begin(), return_val.end(), input_value);
        std::reverse(return_val.begin(), return_val.end());
    }    

    return return_val;
}