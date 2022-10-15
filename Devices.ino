/*
 *	UOS Arduino Firmware
 *	See <https://wiki.nulltek.xyz/projects/uos/>
 *
 *	Copyright © 2022 Steve Richardson (Creating Null)
 *	See LICENSE.md
 *	<https://github.com/CreatingNull/UOS-Arduino/>
 *
 *  Supported device compile-time configurations.
 */

// GPIO_PINS - Defines a numerically sorted array with
// the pins numbers available for GPIO functionality.

// GPIO_STATES - Defines the RAM reset states of the
// pins.

// Hardware definitions for Arduino Nano
#if defined(ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_UNO)
const uint8_t GPIO_PINS[] = {};
const uint8_t GPIO_PIN_STATES[] = {};
const uint8_t ADC_PINS[] = {};
const uint8_t ADC_PIN_STATES[] = {};
// Hardware definitions for Arduin Pico
#elif defined(ARDUINO_RASPBERRY_PI_PICO)
const uint8_t GPIO_PINS[] = {};
const uint8_t GPIO_PIN_STATES[] = {};
const uint8_t ADC_PINS[] = {};
const uint8_t ADC_PIN_STATES[] = {};
#endif
// Dont compile for an undefined target as we have
// no idea what that hardware supports.
