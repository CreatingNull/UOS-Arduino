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

// ADC_PINS - DDefines a numerically sorted arrays with
// the pin numbers for

// Hardware definitions for Arduino Nano
#if defined(ARDUINO_AVR_NANO)
const uint8_t GPIO_PINS[] = {2,  3,  4,  5,  6,  7,  8,  9,  10,
                             11, 12, 13, 14, 15, 16, 17, 18, 19};
uint8_t GPIO_PIN_STATES[] = {
    GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT,
    GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT,
    GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT};
const uint8_t ADC_PINS[] = {0, 1, 2, 3, 4, 5, 6, 7};
const uint8_t ADC_GPIO_ALIASING[] = {14, 15, 16, 17, 18, 19, 255, 255};
uint8_t ADC_PIN_STATES[] = {ADC_UNUSED, ADC_UNUSED, ADC_UNUSED,
                            ADC_UNUSED, ADC_UNUSED, ADC_UNUSED,
                            ADC_UNUSED, ADC_UNUSED, ADC_UNUSED};
// Hardware definitions for Arduino Uno
#elif defined(ARDUINO_AVR_UNO)  // 2x fewer ADC pins
const uint8_t GPIO_PINS[] = {2,  3,  4,  5,  6,  7,  8,  9,  10,
                             11, 12, 13, 14, 15, 16, 17, 18, 19};
uint8_t GPIO_PIN_STATES[] = {
    GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT,
    GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT,
    GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT};
const uint8_t ADC_PINS[] = {0, 1, 2, 3, 4, 5};
const uint8_t ADC_GPIO_ALIASING[] = {14, 15, 16, 17, 18, 19};
uint8_t ADC_PIN_STATES[] = {ADC_UNUSED, ADC_UNUSED, ADC_UNUSED, ADC_UNUSED,
                            ADC_UNUSED, ADC_UNUSED, ADC_UNUSED};
// Hardware definitions for Arduino Pico
#elif defined(ARDUINO_RASPBERRY_PI_PICO)
const uint8_t GPIO_PINS[] = {};
uint8_t GPIO_PIN_STATES[] = {};
const uint8_t ADC_PINS[] = {};
uint8_t ADC_PIN_STATES[] = {};
#endif
// Dont compile for an undefined target as we have
// no idea what that hardware supports.
