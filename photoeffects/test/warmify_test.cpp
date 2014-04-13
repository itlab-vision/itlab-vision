#include <gtest/gtest.h>
#include "photoeffects.hpp"

using namespace cv;

TEST(photoeffects, WarmifyTest)
{
    Mat image(100, 100, CV_8UC3), dst;
    EXPECT_EQ(0, warmify(image, dst, 30));
}
