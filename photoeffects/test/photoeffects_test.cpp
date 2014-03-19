#include <gtest/gtest.h>

#include "photoeffects.hpp"

using namespace cv;

TEST(photoeffects, PassingTest) {
    EXPECT_TRUE(true);
}

TEST(photoeffects, SepiaTest) {
    Mat image(10, 10, CV_8UC1);

    EXPECT_EQ(10, sepia(image));
}
TEST(photoeffects, FadeColorTest) {
    Mat image(10, 10, CV_8UC1);

    EXPECT_EQ(image, fadeColor(image));
}
