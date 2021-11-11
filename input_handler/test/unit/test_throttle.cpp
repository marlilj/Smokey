
#include "gtest/gtest.h"
#include "../../include/throttle.hpp"

#include <vector>

TEST(ThrottleTest, NoChangeInValue) {
    std::vector<int> expected_return{};
    EXPECT_EQ (expected_return, calculateThrottleCurve(10, 10));
    EXPECT_EQ( 0, calculateThrottleCurve(10,10).size());
}

TEST(ThrottleTest, IncrementingValue) {
    std::vector<int> expected_return{11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    EXPECT_EQ (expected_return.size(), calculateThrottleCurve(20, 10).size());
    EXPECT_EQ (expected_return, calculateThrottleCurve(20, 10));
    expected_return = {100};
    EXPECT_EQ (expected_return, calculateThrottleCurve(100, 99));
}

TEST(ThrottleTest, DecreasingValue) {
    std::vector<int> expected_return{19, 18, 17, 16, 15, 14, 13, 12, 11, 10};
    EXPECT_EQ (expected_return.size(), calculateThrottleCurve(10, 20).size());
    EXPECT_EQ (expected_return, calculateThrottleCurve(10, 20));
    expected_return = {51};
    EXPECT_EQ (expected_return, calculateThrottleCurve(51, 52));
}