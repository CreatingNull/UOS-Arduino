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
  switch (instruction_address_) {
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
    case 79:
      // Reset IO from RAM.
      return init_io_from_ram();
  }
  return false;  // Unsupported instruction.
}

// Executes instructions against GPIO.
bool gpio_instruction(bool output, uint8_t persist) {
  // Check the payload is correct length.
  if ((instruction_len_ % 2) != 0) return false;
  // Execute each instruction received.
  for (uint8_t i = 0; i < instruction_len_ / 2; i++) {
    uint8_t pin = instruction_payload_[uint8_t(i * 2)];
    switch (instruction_payload_[uint8_t(i * 2 + 1)]) {
      // Check the level byte
      case 0:
        if (output && !write_io(pin, GPIO_OUTPUT_LOW, persist))
          // Failed setting GPIO output low
          return false;
        else if (!output) {  // Input operation no pullup.
          int level = read_io(pin, GPIO_INPUT, persist);
          if (level == -1) return false;  // failed read
          byte payload[1] = {lowByte(level)};
          if (com_.writePacket(instruction_address_, payload, 1) < 2)
            return false;
        }
        break;
      case 1:  // set high
        if (output && !write_io(pin, GPIO_OUTPUT_HIGH, persist))
          // Failed setting GPIO output high
          return false;
        else if (!output) {  // Input operation pullup enabled.
          int level = read_io(pin, GPIO_INPUT_PULLUP, persist);
          if (level == -1) return false;  // failed read
          byte payload[1] = {lowByte(level)};
          if (com_.writePacket(instruction_address_, payload, 1) < 2)
            return false;
        }
        break;
      default:
        return false;  // instruction not formed correctly
    }
  }
  return true;  // All commands executed successfully.
}
