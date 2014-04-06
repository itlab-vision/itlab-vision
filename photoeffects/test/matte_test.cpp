#include <gtest/gtest.h>
#include "photoeffects.hpp"

using namespace cv;

TEST(photoeffects, MatteTest)
{
    Mat image(10, 20, CV_8UC3);
    Point topleft(0,0);
    Point bottomright(10,20);
    EXPECT_EQ(0, matte(image,topleft,bottomright,image));
}