/*
 *	UOS Arduino Firmware
 *	See <https://wiki.nulltek.xyz/projects/uos/>
 *
 *	Copyright © 2023 Steve Richardson (Creating Null)
 *	See LICENSE.md
 *	<https://github.com/CreatingNull/UOS-Arduino/>
 *
 *	Pin functions, low level wrapper functions.
 */

// Resets IO state from the recorded states in RAM.
bool reinit_io_from_ram() {
  for (uint8_t i = 0; i < sizeof(GPIO_PINS); i++) {
    if (!write_io(GPIO_PINS[i], GPIO_PIN_STATES[i], NO_PERSIST)) {
      return false;
    }
  }
  return true;
}

// Configures an io pin and sets its state.
bool write_io(uint8_t pin_index, uint8_t state, uint8_t persist) {
  uint8_t array_index =
      find_in_sorted_array(pin_index, GPIO_PINS, sizeof(GPIO_PINS));
  if (array_index == 255) return false;  // not valid pin
  uint8_t prior_state = GPIO_PIN_STATES[array_index];
  if (persist == RAM_PERSIST) GPIO_PIN_STATES[array_index] = state;
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
  // Reset state as this is an error case.
  if (persist == RAM_PERSIST) GPIO_PIN_STATES[pin_index] = prior_state;
  return false;
}

// Reads the response from a configured input pin.
int read_io(uint8_t pin_index, uint8_t io_type, uint8_t persist) {
  switch (io_type) {
    case GPIO_INPUT:  // DIO input
      return digitalRead(pin_index);
    case ADC_INPUT:  // AIO input
      return analogRead(pin_index);
  }
  return -1;  // Error case
}
