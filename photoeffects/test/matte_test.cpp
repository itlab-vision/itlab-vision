#include <gtest/gtest.h>
#include "photoeffects.hpp"

using namespace cv;

TEST(photoeffects, MatteTest)
{
    Mat image(10, 20, CV_8UC3);
    Point fisrtpoint(0,0);
    Point secondpoint(10,20);
    EXPECT_EQ(0, matte(image, image, fisrtpoint, secondpoint, 1.0f));
}