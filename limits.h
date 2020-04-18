/**
 * @file
 * Limits impl
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

#ifndef LIBSTD_LIMITS_H__
#define LIBSTD_LIMITS_H__
#include "platform.h"

#ifdef HAS_STL
#include <limits>
#else
namespace std {
    // taken from https://en.cppreference.com/w/cpp/header/limits
    enum float_round_style {
        round_indeterminate       = -1,
        round_toward_zero         =  0,
        round_to_nearest          =  1,
        round_toward_infinity     =  2,
        round_toward_neg_infinity =  3,
    };

    enum float_denorm_style {
        denorm_indeterminate = -1,
        denorm_absent        =  0,
        denorm_present       =  1,
    };
    template<typename T> 
    class numeric_limits {
        public:
            static constexpr bool is_specialized = false;

            static constexpr T min() noexcept { return T(); }
            static constexpr T max() noexcept { return T(); }
            static constexpr T lowest() noexcept { return T(); }

            static constexpr int digits       = 0;
            static constexpr int digits10     = 0;
            static constexpr int max_digits10 = 0;

            static constexpr bool is_signed  = false;
            static constexpr bool is_integer = false;
            static constexpr bool is_exact   = false;
            static constexpr int radix = 0;
            static constexpr T epsilon() noexcept { return T(); }
            static constexpr T round_error() noexcept { return T(); }

            static constexpr int min_exponent = 0;
            static constexpr int min_exponent10 = 0;
            static constexpr int max_exponent = 0;
            static constexpr int max_exponent10 = 0;

            static constexpr bool has_infinity = false;
            static constexpr bool has_quiet_NaN = false;
            static constexpr bool has_signaling_NaN = false;
            static constexpr float_denorm_style has_denom = denorm_absent;
            static constexpr bool has_denom_loss = false;
            static constexpr T infinity() noexcept { return T(); }
            static constexpr T quiet_NaN() noexcept { return T(); }
            static constexpr T signaling_NaN() noexcept { return T(); }
            static constexpr T denorm_min() noexcept { return T(); }

            static constexpr bool is_iec559 = false;
            static constexpr bool is_bounded = false;
            static constexpr bool is_modulo = false;

            static constexpr bool traps = false;
            static constexpr bool tinyness_before = false;
            static constexpr float_round_style round_style = round_toward_zero;
    };
    template<> 
    class numeric_limits<bool> {
        public:
            static constexpr bool is_specialized = true;
            static constexpr bool min() noexcept { return false; }
            static constexpr bool max() noexcept { return true; }
            static constexpr bool lowest() noexcept { return false; }

            static constexpr int digits = 1;
            static constexpr int digits10 = 0;
            static constexpr int max_digits10 = 0;

            static constexpr bool is_signed = false;
            static constexpr bool is_integer = true;
            static constexpr bool is_exact = true;
            static constexpr int radix = 2;
            static constexpr bool epsilon() noexcept { return 0; }
            static constexpr bool round_error() noexcept { return 0; }

            static constexpr int min_exponent = 0;
            static constexpr int min_exponent10 = 0;
            static constexpr int max_exponent = 0;
            static constexpr int max_exponent10 = 0;

            static constexpr bool has_infinity = false;
            static constexpr bool has_quiet_NaN = false;
            static constexpr bool has_signaling_NaN = false;
            static constexpr float_denorm_style has_denorm = denorm_absent;
            static constexpr bool has_denorm_loss = false;
            static constexpr bool infinity() noexcept { return 0; }
            static constexpr bool quiet_NaN() noexcept { return 0; }
            static constexpr bool signaling_NaN() noexcept { return 0; }
            static constexpr bool denorm_min() noexcept { return 0; }

            static constexpr bool is_iec559 = false;
            static constexpr bool is_bounded = true;
            static constexpr bool is_modulo = false;

            static constexpr bool traps = false;
            static constexpr bool tinyness_before = false;
            static constexpr float_round_style round_style = round_toward_zero;
    };
    /// @todo implement specializations for the rest of the numerical types

} // end namespace std
#endif
#endif // end LIBSTD_LIMITS_H__
