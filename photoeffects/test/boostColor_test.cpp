#include <gtest/gtest.h>

#include "photoeffects.hpp"

using namespace cv;

TEST(photoeffects, BoostColorTest)
{
    Mat image(10, 10, CV_32FC3), dst;

    EXPECT_EQ(0, boostColor(image, dst, 0.5f));
}

TEST(photoeffects, BoostColorTestBadIntensity)
{
    Mat image(10, 10, CV_32FC3), dst;

    EXPECT_EQ(2, boostColor(image, dst, -1.0f));
    EXPECT_EQ(2, boostColor(image, dst, 2.0f));
}

TEST(photoeffects, BoostColorTestBadImage)
{
    Mat image(10, 10, CV_8UC1), dst;

    EXPECT_EQ(1, boostColor(image, dst, 0.5f));
}