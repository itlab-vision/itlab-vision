#include <gtest/gtest.h>

#include "photoeffects.hpp"

using namespace cv;

TEST(photoeffects, FadeColorTest) {
    Mat imageWithOneChannel(10, 20, CV_8UC1);
    Mat imageWithThreeChannel(10,20,CV_8UC3);
    Mat imageWithTwoChannel(10,20,CV_8UC2),dst;

    EXPECT_EQ(0, fadeColor(imageWithOneChannel,dst,Point(5,5),Point(5,10)));
    EXPECT_EQ(0, fadeColor(imageWithThreeChannel,dst,Point(5,5),Point(5,10)));
    EXPECT_EQ(1, fadeColor(imageWithTwoChannel,dst,Point(5,5),Point(5,10)));
    EXPECT_EQ(2, fadeColor(imageWithOneChannel,dst,Point(50,5),Point(5,10)));
    EXPECT_EQ(2, fadeColor(imageWithOneChannel,dst,Point(5,5),Point(5,-10)));
    EXPECT_EQ(3, fadeColor(imageWithOneChannel,dst,Point(5,5),Point(5,5)));
}
