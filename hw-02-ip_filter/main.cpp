#include "ip_filter.h"

#include <fstream>
#include <iostream>

int main() {
    std::ifstream fin("ip_filter.txt");

    auto ip_filter = IpFilter::makeFilter(fin).sort([](const Ip & lhs, const Ip & rhs) {
        return std::tie(lhs.a, lhs.b, lhs.c, lhs.d) > std::tie(rhs.a, rhs.b, rhs.c, rhs.d);
    });

    // reverse lexicographic order

    ip_filter.print(std::cout);

    // reverse lexicographic order, but the first byte is equal to 1

    ip_filter.filter([](const Ip & ip) {
        return ip.a == 1;
    }).print(std::cout);

    // reverse lexicographic order, but the first byte is equal to 46 and the second byte is equal to 70

    ip_filter.filter([](const Ip & ip) {
        return ip.a == 46 && ip.b == 70;
    }).print(std::cout);

    // reverse lexicographic order, but any byte is equal to 46

    ip_filter.filter([](const Ip & ip) {
        return ip.a == 46 || ip.b == 46 || ip.c == 46 || ip.d == 46;
    }).print(std::cout);

    return 0;
}