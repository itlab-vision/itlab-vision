#include <gtest/gtest.h>

#include "photoeffects.hpp"

using namespace cv;

TEST(photoeffects, SepiaTest) {
    Mat src(10, 10, CV_8UC1), dst;

    EXPECT_EQ(0, sepia(src, dst));
}
