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
    Mat imageWithThreeChannel(10, 20, CV_8UC3);
    Mat dst;
    EXPECT_EQ(0, filmGrain(imageWithOneChannel, dst, 5));
    EXPECT_EQ(0, filmGrain(imageWithThreeChannel, dst, 5));
}
TEST(photoeffects, FilmGrainRegressionTest)
{
    string input = "./testdata/filmGrain_test.png";
    string expectedOutput = "./testdata/filmGrain_test_result.png";

    Mat image = imread(input, CV_LOAD_IMAGE_COLOR);
    Mat rightDst = imread(expectedOutput, CV_LOAD_IMAGE_COLOR);

    if (image.empty())
        FAIL() << "Can't read " + input + " image";
    if (rightDst.empty())
        FAIL() << "Can't read " + input + " image";

    Mat dst;
    theRNG()=RNG(0);
    EXPECT_EQ(0, filmGrain(image, dst, 8));

    Mat diff = abs(rightDst - dst);
    Mat mask = diff.reshape(1) > 1;
    EXPECT_EQ(0, countNonZero(mask));
}
