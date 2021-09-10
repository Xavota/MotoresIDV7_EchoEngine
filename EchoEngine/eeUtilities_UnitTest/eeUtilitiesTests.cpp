#include "../eeUtilities/include/eePrerequisitesUtilities.h"

#include <gtest/gtest.h>

#include "../eeUtilities/include/eeVector2.h"

TEST(eeUtilities, Basic_Type_Sizes)
{
  EXPECT_EQ(sizeof(eeEngineSDK::int8), 1);
  EXPECT_EQ(sizeof(eeEngineSDK::int16), 2);
  EXPECT_EQ(sizeof(eeEngineSDK::int32), 4);
  EXPECT_EQ(sizeof(eeEngineSDK::int64), 8);

  EXPECT_EQ(sizeof(eeEngineSDK::uint8), 1);
  EXPECT_EQ(sizeof(eeEngineSDK::uint16), 2);
  EXPECT_EQ(sizeof(eeEngineSDK::uint32), 4);
  EXPECT_EQ(sizeof(eeEngineSDK::uint64), 8);

  EXPECT_EQ(sizeof(eeEngineSDK::WCHAR), 2);
  EXPECT_EQ(sizeof(eeEngineSDK::ANSICHAR), 1);
  EXPECT_EQ(sizeof(eeEngineSDK::UNICHAR), 2);
  EXPECT_EQ(sizeof(eeEngineSDK::unchar), 1);

  EXPECT_EQ(sizeof(eeEngineSDK::TYPE_OF_NULL), 4);
  EXPECT_EQ(sizeof(eeEngineSDK::SIZE_T), 8);
}

TEST(eeUtilities, Vector2)
{
  eeEngineSDK::Vector2f vf;
  EXPECT_EQ(vf, eeEngineSDK::Vector2f(0.0f, 0.0f));

  vf = eeEngineSDK::Vector2f(-3.0f, 1.0f);
  EXPECT_EQ(vf, eeEngineSDK::Vector2f(-3.0f, 1.0f));

  eeEngineSDK::Vector2f vf2(-3.0f, 4.0f);
  EXPECT_EQ(vf2, eeEngineSDK::Vector2f(-3.0f, 4.0f));

  EXPECT_EQ(vf.dot(vf2), 13.0f);

  EXPECT_EQ(vf.distance(vf2), 3.0f);

  EXPECT_EQ(vf2.length(), 5.0f);
}

int main(int argc, char** argv) {
  int stop;
  ::testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();
  std::cin >> stop;
  return 0;
}