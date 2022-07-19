#include "ip_filter.h"

#include <algorithm>
#include <sstream>

IpFilter IpFilter::makeFilter(std::istream & in) {
    IpFilter ip_filter;
    ip_filter.read(in);
    return ip_filter;
}

IpFilter IpFilter::filter(const std::function<bool(const Ip &)> & compare) const {
    IpFilter ip_filter(*this);
    ip_filter.m_ips.erase(std::remove_if(ip_filter.m_ips.begin(), ip_filter.m_ips.end(), std::not_fn(compare)), ip_filter.m_ips.end());
    return ip_filter;
}

IpFilter IpFilter::sort(const std::function<bool(const Ip &, const Ip &)> & compare) const {
    IpFilter ip_filter(*this);
    std::sort(ip_filter.m_ips.begin(), ip_filter.m_ips.end(), compare);
    return ip_filter;
}

void IpFilter::print(std::ostream & out) const {
    for (const auto & ip : m_ips) {
        out << ip.a << "." << ip.b << "." << ip.c << "." << ip.d << std::endl;
    }
}

void IpFilter::read(std::istream & fin) {
    auto parseRow = [](const std::string & row) {
        Ip ip;
        char dot;
        std::string buffer;
        std::stringstream ss(row);
        ss >> ip.a >> dot >> ip.b >> dot >> ip.c >> dot >> ip.d >> buffer >> buffer;
        return ip;
    };

    std::string buffer;
    while(std::getline(fin, buffer)) {
        m_ips.emplace_back(parseRow(buffer));
    }
}