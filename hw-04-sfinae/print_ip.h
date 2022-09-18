/**
 * @file print_ip.h
 * @author Maksim Halavaty (max.golovatyi@gmail.com)
 * @brief The set of functions that allows to print ip address from integers, string, vector, list and tuple.
 * @version 0.1
 * @date 2022-09-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include "tuple_traits.h"

#include <iostream>
#include <tuple>
#include <list>
#include <vector>
#include <type_traits>
#include <string>

/**
 * @brief Specialization of a printing ip function for an integral type. Every byte of the number is printed as
 * a separate part of an ip.
 * 
 * @tparam T A type, that can only be an integral type.
 * @param ip A number, that represents an ip.
 * @param out A stream to output ip in.
 */
template <typename T, std::enable_if_t<std::is_integral_v<typename std::decay_t<T>>, int> = 0>
void print_ip(T && ip, std::ostream & out = std::cout) {
    auto * pointer = reinterpret_cast<unsigned char *>(&ip);
    out << int(pointer[sizeof(T) - 1]);
    for (int i = int(sizeof(T)) - 2; i >=0 ; --i) {
        out << "." << int(pointer[i]);
    }
}

/**
 * @brief Specialization of a printing ip function for a std::string. Can also be called with all the types the std::string
 * can be constructed with. The ip is printed as it is without any changes.
 * 
 * @tparam T A type, that represents a string.
 * @param ip A string, that represents an ip.
 * @param out A stream to output ip in.
 */
template <typename T, std::enable_if_t<std::is_constructible_v<std::string, typename std::decay_t<T>>, int> = 0>
void print_ip(T && ip, std::ostream & out = std::cout) {
    out << ip;
}

/**
 * @brief Specialization of a printing ip function for a std::list and std::vector.
 * Every element of std::vector or std::list is considered a separate part of an ip.
 * 
 * @tparam T A type, that can only be std::vector or std::list.
 * @param ip std::vector or std::list, that represents an ip.
 * @param out A stream to output ip in.
 */
template <typename T, std::enable_if_t<
        std::is_same_v<std::list<typename std::decay_t<T>::value_type>, typename std::decay_t<T>>
        || std::is_same_v<std::vector<typename std::decay_t<T>::value_type>, typename std::decay_t<T>>, int> = 0>
void print_ip(T && ip, std::ostream & out = std::cout) {
    if (ip.empty())
        return;
    out << ip.front();
    auto it = std::next(ip.begin());
    while (it != ip.end()) {
        out << "." << *it;
        it = std::next(it);
    }
}

/**
 * @brief Specialization of a printing ip function for a std::tuple. Only the tuple with the same
 * types can be allowed, for example std::tuple<int, int> is allowed and std::tuple<int, long> is not.
 * 
 * @tparam T A type, that can only be a tuple with the same types.
 * @param ip std::tuple, that represents an ip.
 * @param out A stream to output ip in.
 */
template <typename T, std::enable_if_t<is_tuple_has_same_types<std::decay_t<T>>::value, int> = 0>
void print_ip(T && ip, std::ostream & out = std::cout) {
    print_tuple(ip, out);
}