#include <opencv2/opencv.hpp>
#include <opencv2/ts/ts_perf.hpp>
#include <iostream>
#include "photoeffects.hpp"
#include "perf_utils.hpp"

using namespace std;
using namespace cv;
using namespace perf;

PERF_TEST(photoeffects, boosColorPerf)
{
    string input = "./testdata/boostColor_test.png";
    Mat image = imread(input, CV_LOAD_IMAGE_COLOR);

    if (image.empty())
        FAIL() << "Can't read " + input + " image";

    Mat dst;
    TEST_CYCLE() boostColor(image, dst, 0.5f);

    cout << getRunningTime(calcMetrics()) << " ms" << endl;

    SANITY_CHECK_NOTHING()
}
