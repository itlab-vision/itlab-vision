#include <gtest/gtest.h>

#include "photoeffects.hpp"

using namespace cv;

TEST(photoeffects, FadeColorTest) {
    Mat image(10, 20, CV_8UC1);

    EXPECT_EQ(0, fadeColor(image,image,Point(5,5),Point(5,10)));
}
