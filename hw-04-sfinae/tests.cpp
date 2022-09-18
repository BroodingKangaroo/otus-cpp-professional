#include <gtest/gtest.h>

#include "print_ip.h"

#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <sstream>

TEST(HW04_SFINAE, TestIntegral) {
    {
        std::stringstream ss;
        int8_t test1 = -1;
        EXPECT_NO_THROW(print_ip(test1, ss));
        EXPECT_EQ("255", ss.str());
    }
    
    {
        std::stringstream ss;
        int16_t test2 = 0;
        EXPECT_NO_THROW(print_ip(test2, ss));
        EXPECT_EQ("0.0", ss.str());
    }

    {
        std::stringstream ss;
        int32_t test3 = 2130706433;
        EXPECT_NO_THROW(print_ip(test3, ss));
        EXPECT_EQ("127.0.0.1", ss.str());
    }

    {
        std::stringstream ss;
        int64_t test4 = 8875824491850138409;
        EXPECT_NO_THROW(print_ip(test4, ss));
        EXPECT_EQ("123.45.67.89.101.112.131.41", ss.str());
    }
}

TEST(HW04_SFINAE, TestString) {
    {
        std::stringstream ss;
        std::string test1 = "Hello, World!";
        EXPECT_NO_THROW(print_ip(test1, ss));
        EXPECT_EQ(test1, ss.str());
        ss.clear();
    }
    {   
        std::stringstream ss;
        const char * test2 = "Hello, World!";
        EXPECT_NO_THROW(print_ip(test2, ss));
        EXPECT_EQ(test2, ss.str());
        ss.clear();
    }
}

TEST(HW04_SFINAE, TestVectorList) {
    {
        std::stringstream ss;
        std::vector test1 { 100, 200, 300, 400 };
        print_ip(test1, ss);
        EXPECT_EQ("100.200.300.400", ss.str());
    }

    {
        std::stringstream ss;
        std::list test2 { 400, 300, 200, 100 };
        print_ip(test2, ss);
        EXPECT_EQ("400.300.200.100", ss.str());
    }
}

TEST(HW04_SFINAE, TestTuple) {
    std::stringstream ss;
    std::tuple test1 { 123, 456, 789, 0 };
    print_ip(test1, ss);
    EXPECT_EQ("123.456.789.0", ss.str());
}