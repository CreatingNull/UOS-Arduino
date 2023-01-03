/*
 *	UOS Arduino Firmware
 *	See <https://wiki.nulltek.xyz/projects/uos/>
 *
 *	Copyright © 2023 Steve Richardson (Creating Null)
 *	See LICENSE.md
 *	<https://github.com/CreatingNull/UOS-Arduino/>
 *
 *  Supported device compile-time configurations.
 */

// GPIO_PINS - Defines a numerically sorted array with
// the pins numbers available for GPIO functionality.

// GPIO_STATES - Defines the RAM reset states of the
// pins.

// ADC_PINS - Defines a alias sorted arrays with
// the pin numbers for adc pins.
// The position of the pin in the array should match
// the alias index. Eg: A1 should be ADC_PINS[1]

// Hardware definitions for Arduino Nano
#if defined(ARDUINO_AVR_NANO)
const uint8_t GPIO_PINS[] = {2,  3,  4,  5,  6,  7,  8,  9,  10,
                             11, 12, 13, 14, 15, 16, 17, 18, 19};
uint8_t GPIO_PIN_STATES[] = {
    GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT,
    GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT,
    GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT};
const uint8_t ADC_PINS[] = {A0, A1, A2, A3, A4, A5, A6, A7};

// Hardware definitions for Arduino Uno
#elif defined(ARDUINO_AVR_UNO)  // 2x fewer ADC pins
const uint8_t GPIO_PINS[] = {2,  3,  4,  5,  6,  7,  8,  9,  10,
                             11, 12, 13, 14, 15, 16, 17, 18, 19};
uint8_t GPIO_PIN_STATES[] = {
    GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT,
    GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT,
    GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT};
const uint8_t ADC_PINS[] = {A0, A1, A2, A3, A4, A5};

// Hardware definitions for Arduino Pico
#elif defined(ARDUINO_RASPBERRY_PI_PICO)
const uint8_t GPIO_PINS[] = {};
uint8_t GPIO_PIN_STATES[] = {};
const uint8_t ADC_PINS[] = {};

#endif
// Dont compile for an undefined target as we have
// no idea what that hardware supports.
