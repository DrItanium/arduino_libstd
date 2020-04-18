/**
 * @file
 * Platform detection routines 
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

#ifndef LIBSTD_PLATFORM_H__
#define LIBSTD_PLATFORM_H__
#ifdef __AVR__
#define TARGET_AVR
#endif
#ifdef __arm__
#define TARGET_ARM
#endif

#ifdef ARDUINO
#define ARDUINO_ENABLED
#endif

#if defined(TARGET_ARM) && defined(ARDUINO_ENABLED)
#define TARGET_ARM_ARDUINO
#endif 



#ifndef TARGET_AVR
#define HAS_STL
#endif

// So that YCM analyzes my implementation
#ifdef YCM_VERIFY_WRAPPER_IMPL
#   ifdef HAS_STL
#      undef HAS_STL
#   endif
#endif

#if defined(TARGET_ARM) && defined(ARDUINO_ENABLED) 
#define CUSTOM_NEW_IMPL_REQUIRED
#endif 

constexpr bool platformIsArduino() noexcept {
#ifdef ARDUINO_ENABLED
    return true;
#else
    return false;
#endif
}

constexpr bool platformIsAVR() noexcept {
#ifdef TARGET_AVR
    return true;
#else
    return false;
#endif
}

constexpr bool targetIsAtTiny85() noexcept {
    if constexpr (platformIsAVR()) {
#ifdef __AVR_ATtiny85__
        return true;
#else
        return false;
#endif
    } else {
        return false;
    }
}

constexpr bool targetIsArm() noexcept {
#ifdef TARGET_ARM
    return true;
#else 
    return false;
#endif
}

constexpr bool platformIsAmd64() noexcept {
#ifdef __x86_64__
    return true;
#else
    return false;
#endif
}

#endif // end LIBSTD_PLATFORM_H__
