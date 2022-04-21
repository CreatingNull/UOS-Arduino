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
  for (int i = 0; i < sizeof(PIN_DEF); i++) {
    if (!write_IO(PIN_DEF[i], IO_STATES[i], IO_DEF[i])) {
      return false;
    }
  }
  for (int i = 0; i < sizeof(A_PIN_DEF); i++) {  // initialise the analog inputs
    if (A_PIN_PULLUP[i] == 1) {
      pinMode(A_PIN_DEF[i], INPUT_PULLUP);
    } else {
      pinMode(A_PIN_DEF[i], INPUT);
    }
  }
  return true;
}

bool write_IO(uint8_t pin_index, uint8_t level, uint8_t io_type) {
  switch (io_type) {
    case 0:  // DIO output
      if ((level == 0 || level == 1)) {
        pinMode(pin_index, OUTPUT);
        digitalWrite(pin_index, level);
        return true;
      }
      break;
    case 1:              // DIO input
      if (level == 0) {  // input with pullup disabled
        pinMode(pin_index, INPUT);
        return true;
      } else if (level == 1) {  // input with pullup enabled
        pinMode(pin_index, INPUT_PULLUP);
        return true;
      }
      break;
  }
  return false;
}

int read_IO(uint8_t pin_index, uint8_t io_type) {
  switch (io_type) {
    case 0:  // DIO input
      return digitalRead(pin_index);
    case 1:  // AIO input
      return analogRead(pin_index);
  }
  return -1;  // Error case
}
