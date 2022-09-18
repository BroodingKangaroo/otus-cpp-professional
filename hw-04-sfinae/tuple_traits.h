/**
 * @file tuple_traits.h
 * @author Maksim Halavaty (max.golovatyi@gmail.com)
 * @brief The set of meta functions for std::tuple processing.
 * @version 0.1
 * @date 2022-09-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <tuple>
#include <iostream>
#include <type_traits>

/**
 * @brief Declaration of the struct that recursively finds out whether the tuple
 * has the same types in it or not. All the calculation is done at the compile time.
 * 
 * @tparam T The type that is compared to other types in tuple.
 * @tparam Tuple The type of the tuple.
 */
template<typename T, typename Tuple>
struct tuple_has_same_types_impl;

/**
 * @brief This is the base case. The type T is the only one existing in the tuple, so we set the value to true.
 * 
 * @tparam T The type that is compared to other types in tuple.
 */
template<typename T>
struct tuple_has_same_types_impl<T, std::tuple<>>
{
    static constexpr bool value = true;
};

/**
 * @brief This is the case when there is only one type left in tuple. So we set value to true if Type == Rest, 
 * and to false otherwise.
 * 
 * @tparam Type The type that is compared to other types in tuple.
 * @tparam Rest The type that is left in tuple.
 */
template <typename Type, typename Rest>
struct tuple_has_same_types_impl<Type, std::tuple<Rest>> {
    static constexpr bool value = std::is_same_v<Type, Rest>;
};

/**
 * @brief The main struct that does all the heavy lifting. Recursively compares types in tuple to Type
 * one by one until one of the base cases are called.
 * 
 * @tparam Type The type that is compared to other types in tuple.
 * @tparam First The type that is extracted from tuple by partial specialization.
 * @tparam Rest All of the other types left in tuple.
 */
template <typename Type, typename First, typename... Rest>
struct tuple_has_same_types_impl<Type, std::tuple<First, Rest...>> {
    using RestTuple = std::tuple<Rest...>;
    static constexpr bool value = std::is_same_v<Type, First> && tuple_has_same_types_impl<Type, RestTuple>::value;
};

/**
 * @brief Declaration of the struct that starts recursive chain to find out whether the tuple
 * has the same types in it or not. All the calculation is done at the compile time.
 * 
 * @tparam Tuple The type of the tuple.
 */
template <typename Tuple>
struct is_tuple_has_same_types;

/**
 * @brief Specialization to extract one type from the tuple to start recursive call chain.
 * 
 * @tparam First The type that is extracted from tuple by partial specialization.
 * @tparam Rest All of the other types left in tuple.
 */
template <typename First, typename... Rest>
struct is_tuple_has_same_types<std::tuple<First, Rest...>> {
    using RestTuple = std::tuple<Rest...>;
    static constexpr bool value = tuple_has_same_types_impl<First, RestTuple>::value;
};

/**
 * @brief Template function to recursively print std::tuple.
 * 
 * @tparam i A number that represents current position being printed.
 * @tparam Types The rypes of the tuple.
 * @param t The tuple itself.
 * @param out A stream to output ip in.
 */
template <size_t i = 0, typename... Types>
constexpr void print_tuple(std::tuple<Types...>& t, std::ostream & out = std::cout) {
    if constexpr (i == 0)
        out << std::get<i>(t);
    else
        out << "." << std::get<i>(t);
    if constexpr (i + 1 != sizeof...(Types))
        print_tuple<i + 1>(t, out);
}