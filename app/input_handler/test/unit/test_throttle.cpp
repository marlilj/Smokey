
#include "gtest/gtest.h"
#include "../../include/throttle.hpp"

#include <vector>

TEST(ThrottleTest, NoChangeInValue) {
    std::vector<int> expected_return{};
    EXPECT_EQ (expected_return, calculateThrottleCurve(10, 10));
}

TEST(ThrottleTest, IncrementingValue) {
    // EXPECT_EQ (18.0, square‑root (324.0));
    // EXPECT_EQ (25.4, square‑root (645.16));
    // EXPECT_EQ (50.3321, square‑root (2533.310224));
}

TEST(ThrottleTest, DecreasingValue) {
    // EXPECT_EQ (18.0, square‑root (324.0));
    // EXPECT_EQ (25.4, square‑root (645.16));
    // EXPECT_EQ (50.3321, square‑root (2533.310224));
}