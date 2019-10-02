/**
 * Copyright (c) 2019, Joshua Scoggins
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

// simple type_traits implementation

namespace std {
template<typename T> struct remove_const { using type = T; };
template<typename T> struct remove_const<const T> { using type = T; };
template<typename T> struct remove_volatile { using type = T; };
template<typename T> struct remove_volatile<volatile T> { using type = T; };
template<typename T>
struct remove_cv {
    using type = typename std::remove_volatile<typename std::remove_const<T>::type>::type;
};
#if __cplusplus >= 201402L
template<typename T>
using remove_const_t = typename remove_const<T>::type;
template<typename T>
using remove_volatile_t = typename remove_volatile<T>::type;
template<typename T>
using remove_cv_t = typename remove_cv<T>::type;
#endif

template<typename T>
struct is_void : is_same<void, typename remove_cv<T>::type> { };
#if __cplusplus >= 201703L
template<typename T>
inline constexpr bool is_void_v = is_void<T>::value;
#endif
} // end namespace std
