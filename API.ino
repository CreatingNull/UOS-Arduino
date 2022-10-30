/*
 *	UOS Arduino Firmware
 *	See <https://wiki.nulltek.xyz/projects/uos/>
 *
 *	Copyright © 2022 Steve Richardson (Creating Null)
 *	See LICENSE.md
 *	<https://github.com/CreatingNull/UOS-Arduino/>
 *
 *	Handles the COMMs level API of UOS Project
 */

// executes the pending instruction and updates system memory where required
bool handle_comms() {
  switch (instruction_address) {
    case 60:
      // Set GPIO Output non-volatile.
      return set_gpio_outputs();
  }
  return false;  // Unsupported instruction.
}

// Executes instructions for setting GPIO outputs.
bool set_gpio_outputs() {  // 60
  // Check the payload is correct length.
  if ((instruction_len % 2) != 0) return false;
  // Execute each instruction received.
  for (int i = 0; i < instruction_len / 2; i++) {
    switch (instruction_payload[uint8_t(i * 2 + 1)]) {
      // Check the level byte
      case 0:  // set low
        if (!write_io(instruction_payload[uint8_t(i * 2)], GPIO_OUTPUT_LOW))
          return false;
        break;
      case 1:  // set high
        if (!write_io(instruction_payload[uint8_t(i * 2)], GPIO_OUTPUT_HIGH))
          return false;
        break;
      default:
        return false;  // instruction not formed correctly
    }
  }
  return false;
}
