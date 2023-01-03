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
bool init_io_from_ram() {
  for (uint8_t i = 0; i < sizeof(GPIO_PINS); i++) {
    if (!write_io(GPIO_PINS[i], GPIO_PIN_STATES[i], NO_PERSIST)) {
      return false;
    }
  }
  return true;
}

// Configures an io pin and sets its state.
bool write_io(uint8_t pin_index, uint8_t state, uint8_t persist) {
  switch (state) {
    case GPIO_OUTPUT_LOW:
      if (!persist_state(pin_index, state, persist)) return false;
      pinMode(pin_index, OUTPUT);
      digitalWrite(pin_index, LOW);
      return true;
    case GPIO_OUTPUT_HIGH:
      if (!persist_state(pin_index, state, persist)) return false;
      pinMode(pin_index, OUTPUT);
      digitalWrite(pin_index, HIGH);
      return true;
    case GPIO_INPUT:
      if (!persist_state(pin_index, state, persist)) return false;
      pinMode(pin_index, INPUT);
      return true;
    case GPIO_INPUT_PULLUP:
      if (!persist_state(pin_index, state, persist)) return false;
      pinMode(pin_index, INPUT_PULLUP);
      return true;
    case ADC_INPUT:
      if (!persist_state(pin_index, state, persist)) return false;
      pinMode(pin_index, INPUT);
      return true;
    case ADC_INPUT_PULLUP:
      if (!persist_state(pin_index, state, persist)) return false;
      pinMode(pin_index, INPUT_PULLUP);
      return true;
  }
  return false;
}

// Reads the response from a configured input pin.
int read_io(uint8_t pin_index, uint8_t state, uint8_t persist) {
  // First configure any pin modes.
  if (!write_io(pin_index, state, persist)) return -1;
  switch (state) {
    case GPIO_INPUT:  // DIO input
      return digitalRead(pin_index);
    case GPIO_INPUT_PULLUP:
      return digitalRead(pin_index);
    case ADC_INPUT:  // AIO input
      return analogRead(pin_index);
    case ADC_INPUT_PULLUP:
      return analogRead(pin_index);
  }
  return -1;  // Error case
}

// Saves the configuration of the pin
bool persist_state(uint8_t pin_index, uint8_t state, uint8_t persist) {
  // Even if not persisting this should run to ensure pins are valid for
  // operation.
  if (state == ADC_INPUT || state == ADC_INPUT_PULLUP) {  // ADC Pin Operation
    uint8_t array_index =
        find_in_sorted_array(pin_index, ADC_PINS, sizeof(ADC_PINS));
    if (array_index == 255) return false;  // pin not found
    if (persist == RAM_PERSIST) {
      // look up the aliased GPIO pin index if it exists
      uint8_t alias_index =
          find_in_sorted_array(pin_index, GPIO_PINS, sizeof(GPIO_PINS));
      // you can't persist on analog pins without a GPIO alias.
      if (alias_index == 255) return false;
      GPIO_PIN_STATES[alias_index] = state;
    }
  } else {  // GPIO Pin Operation
    uint8_t array_index =
        find_in_sorted_array(pin_index, GPIO_PINS, sizeof(GPIO_PINS));
    if (array_index == 255) return false;  // pin not found
    if (persist == RAM_PERSIST) {
      GPIO_PIN_STATES[array_index] = state;
    }
  }
  return true;
}
