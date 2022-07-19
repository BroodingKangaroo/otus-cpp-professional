#include <gtest/gtest.h>

#include "ip_filter.h"

#include <string>
#include <sstream>
#include <vector>
#include <fstream>
// #include <openssl/md5.h>

TEST(HW02_IpFilter, TestCreation) {
    std::string testData = "1.1.1.1\t0\t0\n"
    "1.2.1.1\t0\t0\n"
    "1.10.1.1\t0\t0";
    std::stringstream ss(testData);
    EXPECT_NO_THROW(IpFilter::makeFilter(ss));
}

TEST(HW02_IpFilter, TestPrint) {
    std::string testData = "1.1.1.1\t0\t0\n"
    "1.2.1.1\t0\t0\n"
    "1.10.1.1\t0\t0";
    std::string expectedTestData = "1.1.1.1\n"
    "1.2.1.1\n"
    "1.10.1.1\n";
    std::stringstream ss(testData);
    std::stringstream ssOut;
    IpFilter::makeFilter(ss).print(ssOut);
    EXPECT_EQ(expectedTestData, ssOut.str());
}

TEST(HW02_IpFilter, TestSort) {
    std::string testData = "1.10.1.1\t0\t0\n"
    "1.2.1.1\t0\t0\n"
    "1.1.1.1\t0\t0";
    std::string expectedTestData = "1.10.1.1\n"
    "1.2.1.1\n"
    "1.1.1.1\n";
    std::stringstream ss(testData);
    std::stringstream ssOut;
    IpFilter::makeFilter(ss).sort([](const Ip & lhs, const Ip & rhs) {
        return std::tie(lhs.a, lhs.b, lhs.c, lhs.d) > std::tie(rhs.a, rhs.b, rhs.c, rhs.d);
    }).print(ssOut);
    EXPECT_EQ(expectedTestData, ssOut.str());
}

TEST(HW02_IpFilter, TestFilter) {
    std::string testData = "1.10.1.1\t0\t0\n"
    "2.2.1.1\t0\t0\n"
    "3.1.1.1\t0\t0\n"
    "2.3.4.1\t0\t0";
    std::string expectedTestData = "2.2.1.1\n"
    "2.3.4.1\n";
    std::stringstream ss(testData);
    std::stringstream ssOut;
    IpFilter::makeFilter(ss).filter([](const Ip & ip){
        return ip.a == 2;
    }).print(ssOut);
    EXPECT_EQ(expectedTestData, ssOut.str());
}

TEST(HW02_IpFilter, TestSortFilter) {
    std::string testData = "1.10.1.1\t0\t0\n"
    "2.2.1.1\t0\t0\n"
    "3.1.1.1\t0\t0\n"
    "2.3.4.1\t0\t0";
    std::string expectedTestData = "2.3.4.1\n"
    "2.2.1.1\n";
    std::stringstream ss(testData);
    std::stringstream ssOut;
    IpFilter::makeFilter(ss).sort([](const Ip & lhs, const Ip & rhs) {
        return std::tie(lhs.a, lhs.b, lhs.c, lhs.d) > std::tie(rhs.a, rhs.b, rhs.c, rhs.d);
    }).filter([](const Ip & ip){
        return ip.a == 2;
    }).print(ssOut);
    EXPECT_EQ(expectedTestData, ssOut.str());
}

TEST(HW02_IpFilter, TestHashSum) {
    std::string testData = "1.10.1.1\t0\t0\n"
    "2.2.1.1\t0\t0\n"
    "3.1.1.1\t0\t0\n"
    "2.3.4.1\t0\t0";
    std::string expectedTestData = "2.3.4.1\n"
    "2.2.1.1\n";
    std::stringstream ss(testData);
    std::stringstream ssOut;
    IpFilter::makeFilter(ss).sort([](const Ip & lhs, const Ip & rhs) {
        return std::tie(lhs.a, lhs.b, lhs.c, lhs.d) > std::tie(rhs.a, rhs.b, rhs.c, rhs.d);
    }).filter([](const Ip & ip){
        return ip.a == 2;
    }).print(ssOut);
    EXPECT_EQ(expectedTestData, ssOut.str());
}