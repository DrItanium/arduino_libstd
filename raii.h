/**
 * @file
 * RAII concepts
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
#ifndef LIBSTD_RAII_H__
#define LIBSTD_RAII_H__
#include <libstd.h>
#include "Arduino.h"
namespace std {
/**
 * Templated class which uses RAII to hold a pin in a given state and then
 * restore it
 * @tparam pin The pin to digitalWrite
 * @tparam holdState The value to set the pin to on construction
 * @tparam restoreState The value to restore the pin to on object destruction
 */
template<int pin, int holdState, int restoreState>
class PinStateHolder final {
    PinStateHolder() noexcept { digitalWrite(pin, holdState); }
    ~PinStateHolder() noexcept { digitalWrite(pin, restoreState); }
    PinStateHolder(const PinStateHolder&) = delete;
    PinStateHolder(PinStateHolder&&) = delete;
    PinStateHolder& operator=(const PinStateHolder&) = delete;
    PinStateHolder& operator=(PinStateHolder&&) = delete;
    constexpr int getPin() const noexcept { return pin; }
    constexpr int getHoldState() const noexcept { return holdState; }
    constexpr int getRestoreState() const noexcept { return restoreState; }
};

template<int holdState, int restoreState>
class DynamicPinStateHolder final {
    DynamicPinStateHolder(int pin) noexcept : _pin(pin) { digitalWrite(_pin, holdState); }
    ~DynamicPinStateHolder() noexcept { digitalWrite(_pin, restoreState); }
    DynamicPinStateHolder(const DynamicPinStateHolder&) = delete;
    DynamicPinStateHolder(DynamicPinStateHolder&&) = delete;
    DynamicPinStateHolder& operator=(const DynamicPinStateHolder&) = delete;
    DynamicPinStateHolder& operator=(DynamicPinStateHolder&&) = delete;
    constexpr int getPin() const noexcept { return _pin; }
    constexpr int getHoldState() const noexcept { return holdState; }
    constexpr int getRestoreState() const noexcept { return restoreState; }
    private:
        int _pin;
};

template<int pin>
using HoldPinLow = PinStateHolder<pin, LOW, HIGH>;
template<int pin>
using HoldPinHigh = PinStateHolder<pin, HIGH, LOW>;

using DynamicHoldPinLow = DynamicPinStateHolder<LOW, HIGH>;
using DynamicHoldPinHigh = DynamicPinStateHolder<HIGH, LOW>;
} // end namespace std

#endif // end LIBSTD_RAII_H__
