/*
 *	UOS Arduino Firmware
 *	See <https://wiki.nulltek.xyz/projects/uos/>
 *
 *	Copyright © 2022 Steve Richardson (Creating Null)
 *	See LICENSE.md
 *	<https://github.com/CreatingNull/UOS-Arduino/>
 *
 *	Top level sketch for the firmware.
 */

#include <Arduino.h>
#include <EEPROM.h>
#include <NullPacketComms.h>

#define UNKNOWN_PIN 0xFF
#define IDENTITY 0x00
#define VER_MAJOR 0x01
#define VER_MINOR 0x00
#define VER_PATCH 0x00
#define API_VERSION 0

#define GPIO_OUTPUT_LOW 0
#define GPIO_OUTPUT_HIGH 1
#define GPIO_INPUT 2
#define GPIO_INPUT_PULLUP 3

bool pending_instruction = false;
bool sys_serial_backlog = false;

uint8_t instruction_address = 255;
uint8_t instruction_len = 0;
uint8_t instruction_payload[58];

NullPacketComms com = NullPacketComms();

// configures the NPC serial port to start handling packets, re-initialises IO
// to default state
void setup() {
  com.begin(115200);
  reinit_io_from_ram();
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
  if (com.available() > 0 && !pending_instruction) {
    pending_instruction = com.readPacket();
    // take a deep copy of the instruction
    instruction_address = com.target_;
    instruction_len = com.len_;
    for (uint8_t i = 0; i < instruction_len; i++) {
      instruction_payload[i] = com.payload_[i];
    }
  }
}

// Checks if any instructions are pending and calls the handler if they are
void process_instruction() {
  if (pending_instruction) {
    handle_comms();
    pending_instruction = false;
  }
}
