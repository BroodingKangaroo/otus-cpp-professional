#include "lib.h"

#include <gtest/gtest.h>

TEST(HelloWorld, TestVersion) {
    EXPECT_TRUE(version() > 0);
}