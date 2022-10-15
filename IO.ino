/*
 *	UOS Arduino Firmware
 *	See <https://wiki.nulltek.xyz/projects/uos/>
 *
 *	Copyright © 2022 Steve Richardson (Creating Null)
 *	See LICENSE.md
 *	<https://github.com/CreatingNull/UOS-Arduino/>
 *
 *	Pin functions, low level wrapper functions.
 */

bool reinit_io_from_ram() {
  for (int i = 0; i < sizeof(GPIO_PINS); i++) {
    if (!write_io(GPIO_PINS[i], GPIO_PIN_STATES[i])) {
      return false;
    }
  }
  for (int i = 0; i < sizeof(ADC_PINS); i++) {  // initialise the analog inputs
    if (ADC_PIN_STATES[i] == 1) {
      pinMode(ADC_PINS[i], INPUT_PULLUP);
    } else {
      pinMode(ADC_PINS[i], INPUT);
    }
  }
  return true;
}

bool write_io(uint8_t pin_index, uint8_t state) {
  switch (state) {
    case GPIO_OUTPUT_LOW:
      pinMode(pin_index, OUTPUT);
      digitalWrite(pin_index, LOW);
      return true;
    case GPIO_OUTPUT_HIGH:
      pinMode(pin_index, OUTPUT);
      digitalWrite(pin_index, HIGH);
      return true;
    case GPIO_INPUT:
      pinMode(pin_index, INPUT);
      return true;
    case GPIO_INPUT_PULLUP:
      pinMode(pin_index, INPUT_PULLUP);
      return true;
  }
  return false;
}

int read_io(uint8_t pin_index, uint8_t io_type) {
  switch (io_type) {
    case 0:  // DIO input
      return digitalRead(pin_index);
    case 1:  // AIO input
      return analogRead(pin_index);
  }
  return -1;  // Error case
}
