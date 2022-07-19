#include "lib.h"

#include <gtest/gtest.h>

TEST(HW01_HelloWorld, TestVersion) {
    EXPECT_TRUE(version() > 0);
}