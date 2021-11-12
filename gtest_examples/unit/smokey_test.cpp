////////////////////////////////////////////////
// NOLINTs allowed:
// protected class member unit_test since gtest standard is non private class members
// every TEST_F since they throw warning regarding 'testing::internal::TestFactoryBase *' with a newly created
// 'gsl::owner<>' [cppcoreguidelines-owning-memory]
////////////////////////////////////////////////

#include <gtest/gtest.h>


class SmokeyTest : public ::testing::Test {
public:
  void SetUp() {}
  bool smokey_something() {
    bool smokey_return_something = true;
    return smokey_return_something;
  }
};

using namespace ::testing;

TEST_F(SmokeyTest, InitSuccess) {
  // EXPECT_CALL(something(true));
  EXPECT_TRUE(smokey_something());
  // EXPECT_FALSE
  // ASSERT_EQ
  // ASSERT_NEQ

  /*
  EXPECT: Reports failed test but continues anyway.
  ASSERT: Reports and stops execution on failed test.
  */
}