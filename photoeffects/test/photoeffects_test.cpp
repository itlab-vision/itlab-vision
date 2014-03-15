#include <gtest/gtest.h>

#include "photoeffects.hpp"

TEST(photoeffects, PassingTest) {
    EXPECT_TRUE(true);
}

TEST(photoeffects, SepiaTest) {
    EXPECT_EQ(2, sepia(2));
}