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

#ifndef DEVICES_H
#define DEVICES_H

// Pin States
// Additional States should be added to IO.check_pin_support
#define IO_NONE 0
#define GPIO_OUTPUT_LOW 1
#define GPIO_OUTPUT_HIGH 2
#define GPIO_INPUT 3
#define GPIO_INPUT_PULLUP 4
#define ADC_INPUT 5
#define ADC_INPUT_PULLUP 6
// PIN Specs
#define SPEC_GPIO_OUTPUT 0x01
#define SPEC_GPIO_INPUT 0x02
#define SPEC_ADC_INPUT 0x04

#define NO_PERSIST 0
#define RAM_PERSIST 1
#define EEPROM_PERSIST 2

// IDENTITY - The standardised UOS Identity.

// PINS - Defines a numerically sorted array with
// the pins numbers available.

// PIN_SPECS - Defines the capability of the defined pin.
// Bitfield - 7654 3210
// (MSB) 7 - Reserved
// 6 - Reserved
// 5 - Reserved
// 4 - Reserved
// 3 - Reserved
// 2 - ADC Input
// 1 - Digital Input
// (LSB) 0 - Digital Output

// PIN_STATES - Defines the RAM reset states of the
// pins.

// Hardware definitions for Arduino Nano
#if defined(ARDUINO_AVR_NANO)
const uint8_t IDENTITY = 1;
const uint8_t PINS[] = {2,  3,  4,  5,  6,  7,  8,  9,  10, 11,
                        12, 13, 14, 15, 16, 17, 18, 19, 20, 21};
const uint8_t PIN_SPECS[] = {
    /*2*/ 0x03,  /*3*/ 0x03,  /*4*/ 0x03,  /*5*/ 0x03,  /*6*/ 0x03,
    /*7*/ 0x03,  /*8*/ 0x03,  /*9*/ 0x03,  /*10*/ 0x03, /*11*/ 0x03,
    /*12*/ 0x03, /*13*/ 0x03, /*14*/ 0x03, /*15*/ 0x03, /*16*/ 0x03,
    /*17*/ 0x07, /*18*/ 0x07, /*19*/ 0x07, /*20*/ 0x04, /*21*/ 0x04,
};
uint8_t PIN_STATES[] = {
    /*2*/ GPIO_INPUT,  /*3*/ GPIO_INPUT,  /*4*/ GPIO_INPUT,
    /*5*/ GPIO_INPUT,  /*6*/ GPIO_INPUT,  /*7*/ GPIO_INPUT,
    /*8*/ GPIO_INPUT,  /*9*/ GPIO_INPUT,  /*10*/ GPIO_INPUT,
    /*11*/ GPIO_INPUT, /*12*/ GPIO_INPUT, /*13*/ GPIO_INPUT,
    /*14*/ GPIO_INPUT, /*15*/ GPIO_INPUT, /*16*/ GPIO_INPUT,
    /*17*/ GPIO_INPUT, /*18*/ GPIO_INPUT, /*19*/ GPIO_INPUT,
    /*20*/ IO_NONE,    /*21*/ IO_NONE};

// Hardware definitions for Arduino Uno
#elif defined(ARDUINO_AVR_UNO)  // 2x fewer ADC pins
const uint8_t IDENTITY = 2;
const uint8_t PINS[] = {2,  3,  4,  5,  6,  7,  8,  9,  10,
                        11, 12, 13, 14, 15, 16, 17, 18, 19};
const uint8_t PIN_SPECS[] = {
    /*2*/ 0x03,  /*3*/ 0x03,  /*4*/ 0x03,  /*5*/ 0x03,  /*6*/ 0x03,
    /*7*/ 0x03,  /*8*/ 0x03,  /*9*/ 0x03,  /*10*/ 0x03, /*11*/ 0x03,
    /*12*/ 0x03, /*13*/ 0x03, /*14*/ 0x03, /*15*/ 0x03, /*16*/ 0x03,
    /*17*/ 0x07, /*18*/ 0x07, /*19*/ 0x07,
};
uint8_t PIN_STATES[] = {
    GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT,
    GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT,
    GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT, GPIO_INPUT};

// Hardware definitions for Arduino Pico
#elif defined(ARDUINO_RASPBERRY_PI_PICO)
const uint8_t IDENTITY = 3;
const uint8_t PINS[] = {};
const uint8_t PIN_SPECS[] = {};
uint8_t PIN_STATES[] = {};

#endif
// Dont compile for an undefined target as we have
// no idea what that hardware supports.

#endif  // Header guard
