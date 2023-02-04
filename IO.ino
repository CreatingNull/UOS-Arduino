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
  for (uint8_t i = 0; i < sizeof(PINS); i++) {
    if (!write_io(PINS[i], PIN_STATES[i], NO_PERSIST)) {
      return false;
    }
  }
  return true;
}

// Configures an io pin and sets its state.
bool write_io(uint8_t pin_index, uint8_t state, uint8_t persist) {
  if (!check_pin_support(pin_index, state)) return false;
  switch (state) {
    case IO_NONE:
      return true;
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
      digitalWrite(pin_index, LOW);  // Disable pull-up if enabled
      return true;
    case GPIO_INPUT_PULLUP:
      if (!persist_state(pin_index, state, persist)) return false;
      pinMode(pin_index, INPUT_PULLUP);
      return true;
    case ADC_INPUT:
      if (!persist_state(pin_index, state, persist)) return false;
      pinMode(pin_index, INPUT);
      digitalWrite(pin_index, LOW);  // Disable pull-up if enabled
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
  if (!check_pin_support(pin_index, state)) return false;
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

// Check Pin supports a state
bool check_pin_support(uint8_t pin_index, uint8_t state) {
  uint8_t array_index = find_in_sorted_array(pin_index, PINS, sizeof(PINS));
  if (array_index == 255) return false;  // pin not found
  uint8_t requirement = 255;  // All functionality, so no match by default
  switch (state) {
    case IO_NONE:
      requirement = 0;  // All pins have IO_NONE functionality.
      break;
    case GPIO_OUTPUT_LOW:
    case GPIO_OUTPUT_HIGH:
      requirement = SPEC_GPIO_OUTPUT;
      break;
    case GPIO_INPUT:
    case GPIO_INPUT_PULLUP:
      requirement = SPEC_GPIO_INPUT;
      break;
    case ADC_INPUT:
    case ADC_INPUT_PULLUP:
      requirement = SPEC_ADC_INPUT;
      break;
  }
  return (PIN_SPECS[array_index] && requirement) != 0;
}

// Saves the configuration of the pin
bool persist_state(uint8_t pin_index, uint8_t state, uint8_t persist) {
  // Even if not persisting this should run to ensure pins are valid for
  // operation.
  uint8_t array_index = find_in_sorted_array(pin_index, PINS, sizeof(PINS));
  if (array_index == 255) return false;  // pin not found
  if (persist == RAM_PERSIST) PIN_STATES[array_index] = state;
  return true;
}
