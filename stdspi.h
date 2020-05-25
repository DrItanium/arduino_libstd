/**
 * @file
 * Generic SPI Interface routines
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
#ifndef LIBSTD_SPI_H__
#define LIBSTD_SPI_H__
#include <stddef.h>
#include <SPI.h>
#include <type_traits.h>
#include <cstdint.h>
#include <raii.h>
namespace std::spi {

inline auto transfer(uint8_t value = 0x00) noexcept {
    return SPI.transfer(value);
}
inline auto transfer16(uint16_t value = 0) noexcept {
    return SPI.transfer16(value);
}
template<typename Opcode, std::enable_if_t<std::is_enum_v<Opcode>, int> = 0>
auto sendOpcode(Opcode opcode) noexcept {
    return transfer(static_cast<uint8_t>(opcode));
}

inline void begin() noexcept {
    SPI.begin();
}

inline void end() noexcept {
    SPI.end();
}

template<int pin>
using CSPinEnable = std::HoldPinLow<pin>;

// special routines for interfacing with SPI memory devices
/**
 * Read a single 8 bit value from a given address
 * @tparam Opcode the opcode to pull the Read entry from
 * @tparam cs the chip select pin to pull low for the lifetime of the action
 */
template<typename Opcode, int cs, uint32_t microsecondDelay = 0, std::enable_if_t<std::is_enum_v<Opcode>, int> = 0>
inline uint8_t read8(uint32_t address) noexcept {
    CSPinEnable<cs> holder;
    if constexpr (microsecondDelay > 0) {
        delayMicroseconds(microsecondDelay);
    }
    sendOpcode(Opcode::Read);
    // lower 24-bits are used
    transfer(address >> 16);
    transfer(address >> 8);
    transfer(address);
    return transfer();
}

template<typename Opcode, int cs, uint32_t microsecondDelay = 0, std::enable_if_t<std::is_enum_v<Opcode>, int> = 0>
inline void singleByteOp(Opcode opcode) noexcept {
    CSPinEnable<cs> holder;
    if constexpr (microsecondDelay > 0) {
        delayMicroseconds(microsecondDelay);
    }
    sendOpcode(opcode);
}

template<typename Opcode, int cs, bool mustEnableWrites = false, uint32_t microsecondDelay = 0, std::enable_if_t<std::is_enum_v<Opcode>, int> = 0>
inline void write8(uint32_t address, uint8_t value) noexcept {
    if constexpr (mustEnableWrites) {
        singleByteOp<Opcode, cs, microsecondDelay>(Opcode::WriteEnable);
    }
    CSPinEnable<cs> holder;
    if constexpr (microsecondDelay > 0) {
        delayMicroseconds(10);
    }
    sendOpcode(Opcode::Write);
    // lower 24-bits are used for address
    transfer(address >> 16);
    transfer(address >> 8);
    transfer(address);
    transfer(value);
}

/**
 * RAII class to disable SPI for until the class is deactivated
 */
class DisableTemporarily final {
    public:
        DisableTemporarily() {
            SPI.end();
        }
        ~DisableTemporarily() {
            SPI.begin();
        }
        DisableTemporarily(const DisableTemporarily&) = delete;
        DisableTemporarily(DisableTemporarily&&) = delete;
        DisableTemporarily& operator=(const DisableTemporarily&) = delete;
        DisableTemporarily& operator=(DisableTemporarily&&) = delete;
};



} // end namespace std::spi

#endif // end LIBSTD_SPI_H__
