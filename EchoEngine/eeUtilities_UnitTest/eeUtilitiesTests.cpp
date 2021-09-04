#include <gtest/gtest.h>

#include "../eeUtilities/include/eeVector2.h"

TEST(eeUtilities, Basic_Type_Sizes)
{
  eeEngineSDK::Vector2f vf;
  EXPECT_EQ(vf, eeEngineSDK::Vector2f(0.0f, 0.0f));
}

int main(int argc, char** argv) {
  int stop;
  ::testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();
  std::cin >> stop;
  return 0;
}