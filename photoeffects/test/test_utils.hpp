#pragma once

#include <gtest/gtest.h>
#include <opencv2/core/core.hpp>


int suppressAssertionMessage(int, const char *, const char *,
                            const char *, int, void *);


#define EXPECT_ERROR(expectedErrorCode, expr) \
{\
    cv::setBreakOnError(false);\
    cv::redirectError(suppressAssertionMessage);\
    int errorCode = 0;\
    try\
    {\
        (expr);\
    }\
    catch (cv::Exception & e)\
    {\
        errorCode = e.code;\
    }\
    cv::setBreakOnError(true);\
    cv::redirectError(0);\
    EXPECT_EQ((int)(expectedErrorCode), errorCode);\
}
