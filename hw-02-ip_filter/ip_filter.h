#pragma once

#include <cstdint>
#include <vector>
#include <istream>
#include <ostream>
#include <functional>

struct Ip {
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
};

class IpFilter {
public:
    static IpFilter makeFilter(std::istream & in);

    IpFilter filter(const std::function<bool(const Ip &)> & compare) const;

    IpFilter sort(const std::function<bool(const Ip &, const Ip &)> & compare) const;

    void print(std::ostream & out) const;

private:
    void read(std::istream & fin);

    std::vector<Ip> m_ips;
};