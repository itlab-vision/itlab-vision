#include <gtest/gtest.h>

#include "photoeffects.hpp"

using namespace cv;

TEST(photoeffects, BoostColorTest)
{
    Mat image(10, 10, CV_32FC3), dst;

    EXPECT_EQ(0, boost_color(image, 0.5f, dst));
}

TEST(photoeffects, BoostColorTestBadIntensity)
{
    Mat image(10, 10, CV_32FC3), dst;

    EXPECT_EQ(2, boost_color(image, -1.0f, dst));
    EXPECT_EQ(2, boost_color(image, 2.0f, dst));
}

TEST(photoeffects, BoostColorTestBadImage)
{
    Mat image(10, 10, CV_8UC1), dst;

    EXPECT_EQ(1, boost_color(image, 0.5f, dst));
}