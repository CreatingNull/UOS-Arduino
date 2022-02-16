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

#include <EEPROM.h>
#include <NullPacketComms.h>
#define UNKNOWN_PIN 0xFF
#define IDENTITY 0x00
#define VER_MAJOR 0x00
#define VER_MINOR 0x05
#define VER_PATCH 0x00

const int hsc_key = 0;  // Hardware software compatibility, increments with
                        // versions when new features become available.
const uint8_t PIN_DEF[] = {
    0, 1, 2, 3,  4,  5,  6,
    7, 8, 9, 10, 11, 12, 13};  // Digital PINs mapped in this program
uint8_t IO_DEF[] = {1, 1, 1, 1, 1, 1, 1,
                    1, 1, 1, 1, 1, 1, 1};  // 0 is output 1 is input
uint8_t IO_STATES[] = {
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0};  // the level on the pins 1 is High 0 is Low
const uint8_t A_PIN_DEF[] = {
    A0, A1, A2, A3, A4, A5, A6, A7};  // analogue pins mapped in this program
uint8_t A_PIN_PULLUP[] = {
    0, 0, 0, 0,
    0, 0, 0, 0};  // analogue pin pullup state, 0 disabled, 1 enabled
word A_PIN_STATES[] = {
    65535, 65535, 65535, 65535, 65535,
    65535, 65535, 65535};  // the last read taken on the analogue pins, none /
                           // bad read is max word value
const uint8_t home_address = 1;
bool sys_ram_integrity = true;
bool pending_instruction = false;  // has the system cleared the last
                                   // instruction
uint8_t instruction_address = 255;
uint8_t instruction_len = 0;
uint8_t instruction_payload[58];
bool sys_serial_backlog = false;
NullPacketComms com = NullPacketComms();

// configures the NPC serial port to start handling packets, re-initialises IO
// to default state
void setup() {
  com.begin(115200);
  sys_ram_integrity = reinit_io_from_ram();
}

// OS functional loop, monitoring incoming commands and executing them
void loop() {
  serial_poll();
  process_instruction();
}

// Obtains the incoming instruction checks the data is good and returns an ack
// packet
void serial_poll() {
  // todo I think we should be doing an rough API vet / sanity check when the
  // packet comes in rather than on execution
  if (com.available() > 0 && !pending_instruction) {
    pending_instruction = com.readPacket();
    // take a deep copy of the instruction
    instruction_address = com.target_;
    instruction_len = com.len_;
    for (int i = 0; i < instruction_len; i++) {
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
