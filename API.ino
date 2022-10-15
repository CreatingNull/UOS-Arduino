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
    case 64:
      // raw digital IO override.
      if ((instruction_len % 3) != 0) {
        return false;  // the payload is wrong for this instruction type
      }
      // Execute each instruction received.
      for (int i = 0; i < instruction_len / 3; i++) {
        if (instruction_payload[uint8_t(i * 3 + 1)] == 0) {
          // DIO Output
          switch (instruction_payload[uint8_t(i * 3 + 2)]) {
            // Check the level byte
            case 0:  // set low
              if (!write_io(instruction_payload[uint8_t(i * 3)],
                            GPIO_OUTPUT_LOW))
                return false;
              break;
            case 1:  // set high
              if (!write_io(instruction_payload[uint8_t(i * 3)],
                            GPIO_OUTPUT_HIGH))
                return false;
              break;
            default:
              return false;  // instruction not formed correctly
          }
        }
      }
      return true;  // all actions completed successfully
  }
  return false;
}
