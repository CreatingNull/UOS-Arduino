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
    case 90:
      // Sample ADC with pullup disabled
      return adc_instruction(false);
    case 91:
      // Sample ADC with pullup enabled.
      return adc_instruction(true);
    case 250:
      // Get Firmware Details.
      return firmware_details();
  }
  return false;  // Unsupported instruction.
}

// Returns the firmware details as a packet.
bool firmware_details() {
  // [PATCH][MINOR][MAJOR][DEVICE][API]
  byte response_payload[5] = {VER_PATCH, VER_MINOR, VER_MAJOR, IDENTITY,
                              API_VERSION};
  if (com_.writePacket(instruction_address_, response_payload,
                       sizeof(response_payload)) < 4)
    return false;
  return true;
}

// executes ADC reads are returns the response packet.
bool adc_instruction(bool pullup_enabled) {
  // Check the payload is correct length
  if (instruction_len_ == 0) return false;
  // Figure out the size of the response payload
  uint8_t response_payload_len = (uint8_t)instruction_len_ * 2;
  uint8_t response_payload[response_payload_len];
  for (uint8_t i = 0; i < instruction_len_; i++) {
    uint8_t pin = instruction_payload_[i];
    int level =
        read_io(pin, pullup_enabled ? ADC_INPUT_PULLUP : ADC_INPUT, NO_PERSIST);
    if (level == -1) return false;
    response_payload[2 * i] = lowByte(level);
    response_payload[2 * i + 1] = highByte(level);
  }
  if (com_.writePacket(instruction_address_, response_payload,
                       response_payload_len) < 4)
    return false;
  return true;
}

// Executes instructions against GPIO, returns response packet if required.
bool gpio_instruction(bool output, uint8_t persist) {
  // Check the payload is correct length.
  if ((instruction_len_ % 2) != 0 || instruction_len_ == 0) return false;
  // Response payload for input instructions.
  byte response_payload[instruction_len_];
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
          response_payload[i] = lowByte(level);
        }
        break;
      case 1:  // set high
        if (output && !write_io(pin, GPIO_OUTPUT_HIGH, persist))
          // Failed setting GPIO output high
          return false;
        else if (!output) {  // Input operation pullup enabled.
          int level = read_io(pin, GPIO_INPUT_PULLUP, persist);
          if (level == -1) return false;  // failed read
          response_payload[i] = lowByte(level);
        }
        break;
      default:
        return false;  // instruction not formed correctly
    }
  }
  if (!output && com_.writePacket(instruction_address_, response_payload,
                                  instruction_len_) < 4)
    return false;
  return true;  // All commands executed successfully.
}
