#include <gtest/gtest.h>

#include "photoeffects.hpp"

using namespace cv;

TEST(photoeffects, BoostColorTest)
{
    Mat image(10, 10, CV_8UC1);

    EXPECT_EQ(10, boost_color(image, 0, image));
}