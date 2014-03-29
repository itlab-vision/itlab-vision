#include <gtest/gtest.h>

#include "photoeffects.hpp"

using namespace cv;

TEST(photoeffects, AntiqueTest) 
{
    Mat src(10, 10, CV_8UC1);
    Mat texture(10, 10, CV_8UC1);
    Mat dst;
    EXPECT_EQ(0, antique(src,texture,dst));
}
