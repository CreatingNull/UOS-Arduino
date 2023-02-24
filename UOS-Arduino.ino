/*
 *	UOS Arduino Firmware
 *	See <https://wiki.nulltek.xyz/projects/uos/>
 *
 *	Copyright © 2023 Steve Richardson (Creating Null)
 *	See LICENSE.md
 *	<https://github.com/CreatingNull/UOS-Arduino/>
 *
 *	Top level sketch for the firmware.
 */

#include <Arduino.h>
#include <EEPROM.h>
#include <NullPacketComms.h>

#include "Devices.h"

#define VER_MAJOR 0
#define VER_MINOR 7
#define VER_PATCH 0
#define API_VERSION 0

bool pending_instruction_ = false;

uint8_t instruction_address_ = 255;
uint8_t instruction_len_ = 0;
uint8_t instruction_payload_[58];

NullPacketComms com_ = NullPacketComms();

// configures the NPC serial port to start handling packets, re-initialises IO
// to default state
void setup() {
  com_.begin(115200);
  init_io_from_ram();
}

// OS functional loop, monitoring incoming commands and executing them
void loop() {
  serial_poll();
  process_instruction();
}

// Obtains the incoming instruction checks the data is good and returns an ack
// packet
void serial_poll() {
  // packet comes in rather than on execution
  if (com_.available() > 0 && !pending_instruction_) {
    pending_instruction_ = com_.readPacket();
    // take a deep copy of the instruction
    instruction_address_ = com_.target_;
    instruction_len_ = com_.len_;
    for (uint8_t i = 0; i < instruction_len_; i++) {
      instruction_payload_[i] = com_.payload_[i];
    }
  }
}

// Checks if any instructions are pending and calls the handler if they are
void process_instruction() {
  if (pending_instruction_) {
    handle_comms();
    pending_instruction_ = false;
  }
}
