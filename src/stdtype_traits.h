/**
 * @file
 * Type traits impl
 * @copyright 
 * Copyright (c) 2019-2020, Joshua Scoggins
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */
#ifndef LIBSTD_TYPE_TRAITS_H__
#define LIBSTD_TYPE_TRAITS_H__
// simple type_traits implementation
#include <libstd.h>
#ifdef HAS_STL
#include <limits>
#else
namespace std {
template<typename T, T v>
struct integral_constant {
    using value_type = T;
    using type = std::integral_constant<T, v>;
    static constexpr T value = v;
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }
};

using true_type = std::integral_constant<bool, true>;
using false_type = std::integral_constant<bool, false>;

template<typename T, typename U>
struct is_same : false_type { };

template<typename T>
struct is_same<T, T> : true_type { };

template<typename T> struct remove_const { using type = T; };
template<typename T> struct remove_const<const T> { using type = T; };
template<typename T> struct remove_volatile { using type = T; };
template<typename T> struct remove_volatile<volatile T> { using type = T; };
template<typename T>
struct remove_cv {
    using type = typename std::remove_volatile<typename std::remove_const<T>::type>::type;
};

template<typename T>
struct is_void : is_same<void, typename remove_cv<T>::type> { };

template<typename T>
struct is_null_pointer : is_same<nullptr_t, remove_cv<T>::type> { };

#if __cplusplus >= 201402L
template<typename T>
using remove_const_t = typename remove_const<T>::type;
template<typename T>
using remove_volatile_t = typename remove_volatile<T>::type;
template<typename T>
using remove_cv_t = typename remove_cv<T>::type;
#if __cplusplus >= 201703L
template<typename T>
inline constexpr bool is_void_v = is_void<T>::value;

template<typename T, typename U>
inline constexpr bool is_same_v = is_same<T, U>::value;

template<typename T>
inline constexpr bool is_null_pointer_v = is_null_pointer<T>::value;
#endif
#endif

} // end namespace std
#endif // end HAS_STL
#endif // end LIBSTD_TYPE_TRAITS_H__
