// Description: Purely a file that handles the API of the COMMs handler

// executes the pending instruction and updates system memory where required
bool handle_comms() {
  switch (instruction_address) {
    case 64:  // raw digital IO override.
      if ((instruction_len % 3) != 0) {
        return false;
      }  // the data is wrong
      for (int i = 0; i < instruction_len / 3; i++) {
        if (instruction_payload[uint8_t(i * 3 + 1)] == 0) {  // DIO Output
          if (!write_IO(instruction_payload[uint8_t(i * 3)],
                        instruction_payload[uint8_t(i * 3 + 2)],
                        instruction_payload[uint8_t(i * 3 + 1)])) {
            return false;
          }  // the system cant process the action
        } else if (instruction_payload[uint8_t(i * 3 + 1)] == 1) {  // DIO Input
          return daq_instruction(1);
        }
      }
      return true;  // all actions completed successfully
    case 68:        // reset IO from RAM
      if (instruction_len == 0) {
        return reinit_io_from_ram();
      }
      return false;
    case 85:  // Sample Analog IO
      return daq_instruction(0);
    case 250:  // Return Device / Version Information
      return daq_instruction(2);
    case 251:  // Return Digital Pin Infomation
      return daq_instruction(3);
  }
  return false;
}

// Data Aquisition function, handling commands that have a return payload.
// Type 0 = Analogue Read,
// Type 1 = Digital Read
// Type 2 = Device Identity
// Type 3 = Digital Pin Config
bool daq_instruction(uint8_t daq_type) {
  uint8_t response_payload_len = instruction_len;
  if (daq_type == 0) {  // two byte result
    response_payload_len =
        response_payload_len * 2;  // 1 input byte has 2 output bytes
  } else if (daq_type == 1) {      // 1 byte result
    response_payload_len =
        uint8_t(response_payload_len / 3);  // 3 input bytes per output byte
  } else if (daq_type == 2) {               // System Info
    response_payload_len = 4;               // PATCH . MINOR . MAJOR . DEVICE
  } else if (daq_type == 3) {               // 1 input byte has 6 output bytes
    response_payload_len = response_payload_len * 6;
  }
  byte payload[response_payload_len];
  switch (daq_type) {  // populate the payload from the system
    case 0:            // Analogue read
      for (int i = 0; i < instruction_len; i++) {
        if (instruction_payload[i] <
            8) {  // form payload 2*packet len bytes in little endian
          A_PIN_STATES[instruction_payload[i]] =
              read_IO(instruction_payload[i], 1);
          payload[2 * i] = lowByte(A_PIN_STATES[instruction_payload[i]]);
          payload[2 * i + 1] = highByte(A_PIN_STATES[instruction_payload[i]]);
        } else {
          payload[2 * i] = 255;
          payload[2 * i + 1] = 255;
        }
      }
      break;
    case 1:  // Digital read
      for (int i = 0; i < instruction_len; i++) {
        payload[i] = read_IO(instruction_payload[i], 0);
      }
      break;
    case 2:  // System Info
      payload[0] = VER_PATCH;
      payload[1] = VER_MINOR;
      payload[2] = VER_MAJOR;
      payload[3] = IDENTITY;
      break;
    case 3:  // Digital Pin Config
      for (int i = 0; i < instruction_len; i++) {
        if (*portModeRegister(digitalPinToPort(instruction_payload[i])) &
            digitalPinToBitMask(instruction_payload[i])) {  // check if output
          payload[i * 6] = 0;
        } else {  // Is an input
          payload[i * 6] = 1;
        }
        payload[i * 6 + 1] =
            digitalRead(instruction_payload[i]);              // check level
        payload[i * 6 + 2] = IO_DEF[instruction_payload[i]];  // check ram mode
        payload[i * 6 + 3] =
            IO_STATES[instruction_payload[i]];          // check ram level
        payload[i * 6 + 4] = EEPROM.read(100 + instruction_payload[i] * 2);  // check eeprom mode
        payload[i * 6 + 5] =
            EEPROM.read(100 + instruction_payload[i] * 2 + 1);  // check eeprom level
      }
      break;
  }
  // ack is already sent so fire off the response packet now
  uint8_t ret_len = comms.generate_packet_data(
      payload, response_payload_len, 0, instruction_address, comms.packet_tx);
  return comms.send_packet(comms.packet_tx, ret_len);
}
