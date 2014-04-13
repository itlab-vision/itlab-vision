#include "photoeffects.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

using namespace cv;

TEST(photoeffects, FilmGrainInvalidImageFormat)
{
    Mat src(10, 20, CV_8UC2);
    Mat dst;

    EXPECT_ERROR(CV_StsAssert, filmGrain(src,dst,5));
}
TEST(photoeffects, FilmGrainTest) {
    Mat imageWithOneChannel(10, 20, CV_8UC1);
    Mat imageWithThreeChannel(10,20,CV_8UC3);
    Mat dst;
    EXPECT_EQ(0, filmGrain(imageWithOneChannel,dst,5));
    EXPECT_EQ(0, filmGrain(imageWithThreeChannel,dst,5));
}
