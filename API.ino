/*
 *	UOS Arduino Firmware
 *	See <https://wiki.nulltek.xyz/projects/uos/>
 *
 *	Copyright © 2023 Steve Richardson (Creating Null)
 *	See LICENSE.md
 *	<https://github.com/CreatingNull/UOS-Arduino/>
 *
 *	Handles the COMMs level API of UOS Project
 */

// executes the pending instruction and updates system memory where required
bool handle_comms() {
  switch (instruction_address) {
    case 60:
      // Set GPIO Output and don't persist
      return gpio_instruction(true, NO_PERSIST);
    case 61:
      // Read GPIO Input and don't persist
      return gpio_instruction(false, NO_PERSIST);
    case 70:
      // Set GPIO Output and persists in RAM
      return gpio_instruction(true, RAM_PERSIST);
    case 71:
      // Read GPIO Input and persists to RAM
      return gpio_instruction(false, RAM_PERSIST);
  }
  return false;  // Unsupported instruction.
}

// Executes instructions against GPIO.
bool gpio_instruction(bool output, uint8_t persist) {  // 70, 71
  // Check the payload is correct length.
  if ((instruction_len % 2) != 0) return false;
  // Execute each instruction received.
  for (uint8_t i = 0; i < instruction_len / 2; i++) {
    uint8_t pin = instruction_payload[uint8_t(i * 2)];
    switch (instruction_payload[uint8_t(i * 2 + 1)]) {
      // Check the level byte
      case 0:
        if (output && !write_io(pin, GPIO_OUTPUT_LOW, persist))
          // Failed setting GPIO output low
          return false;
        break;
      case 1:  // set high
        if (output && !write_io(pin, GPIO_OUTPUT_HIGH, persist))
          // Failed setting GPIO output high
          return false;
        break;
      default:
        return false;  // instruction not formed correctly
    }
  }
  return false;
}
