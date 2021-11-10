////////////////////////////////////////////////
// NOLINTs allowed:
// protected class member unit_test since gtest standard is non private class members
// every TEST_F since they throw warning regarding 'testing::internal::TestFactoryBase *' with a newly created
// 'gsl::owner<>' [cppcoreguidelines-owning-memory]
////////////////////////////////////////////////

#include <gtest/gtest.h>

// #include "min_fil.hpp"

// using namespace smokey;

using ::testing::_;
// using ::testing::Return;

class SmokeyTest : public ::testing::Test {
public:
  void SetUp() {
  }
  };

int argument_01 {};
bool argument_02 {};
bool something {};

using namespace ::testing;

bool smokey_something() {
  bool smokey_return_something;
    return smokey_return_something;
  }

// NOLINTNEXTLINE
TEST_F(argument_01, argument_02) {
  EXPECT_CALL(something(true));
  EXPECT_TRUE(smokey_something());
  // EXPECT_FALSE
  // ASSERT_EQ
  // ASSERT_NEQ

  /*
  EXPECT: Reports failed test but continues anyway.
  ASSERT: Reports and stops execution on failed test.
  */
}