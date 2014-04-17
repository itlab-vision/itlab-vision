#include "photoeffects.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

using namespace cv;

TEST(photoeffects, WarmifyInvalidImageFormat)
{
    Mat image(100, 100, CV_8UC3);
    Mat dst;

    EXPECT_ERROR(CV_StsAssert, warmify(image, dst, 30));
}

TEST(photoeffects, WamifyTest)
{
    Mat image(100, 100, CV_8UC3);
    Mat dst;
    Vec3b intensity_src;
    Vec3b intensity_dst;

    EXPECT_EQ(0, warmify(image, dst, 30));
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            // blue_dst = blue_src
            intensity_src = image.at<Vec3b>(i, j);
            intensity_dst = dst.at<Vec3b>(i, j);
            EXPECT_LE (intensity_dst[0] - 1, intensity_src[0]);
            EXPECT_GE (intensity_dst[0] + 1, intensity_src[0]);
        }
    }
}
