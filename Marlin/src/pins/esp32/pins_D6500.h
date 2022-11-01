/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

/**
 * FYSETC E4 pin assignments
 *
 * 3D printer control board based on the ESP32 microcontroller.
 * Supports 4 stepper drivers, heated bed, single hotend.
 */

#include "env_validate.h"

#if EXTRUDERS > 1 || E_STEPPERS > 1
  #error "D6500 E4 only supports 1 E stepper."
#elif HAS_MULTI_HOTEND
  #error "D6500 E4 only supports 1 hotend / E stepper."
#endif

#define BOARD_INFO_NAME       "D6500"

#include "pins_ESPA_common.h"

// Override pin config for best routing
// Step pins: [14], [16], [27], [33]
// Dir, En Pins: [4], [12], [17], [21], [22], [25], [26], [32]
// End Stops: 15, 34, 35
// Fan: 13
// Heater: 2
// Temp: 36
// end override pin config for best routing

#if HAS_TMC_UART
  //
  // TMC2209 stepper drivers
  //

  //
  // Hardware serial 1
  //
  #define X_HARDWARE_SERIAL              Serial1
  #define Y_HARDWARE_SERIAL              Serial1
  #define Z_HARDWARE_SERIAL              Serial1
  #define E0_HARDWARE_SERIAL             Serial1

  #define TMC_BAUD_RATE 115200
#endif

/**
 * Hardware serial pins
 *
 * Override these pins in Configuration.h or Configuration_adv.h if needed.
 *
 * Note: Serial2 can be defined using HARDWARE_SERIAL2_RX and HARDWARE_SERIAL2_TX
 *       but MRR ESPA does not have enough spare pins for such reassignment.
 */
#ifndef HARDWARE_SERIAL1_RX
  #define HARDWARE_SERIAL1_RX                 -1
#endif
#ifndef HARDWARE_SERIAL1_TX
  #define HARDWARE_SERIAL1_TX                 -1
#endif
