#include <NullPacketComms.h>
#define UNKNOWN_PIN 0xFF
#define IDENTITY 0x00
#define VER_MAJOR 0x00
#define VER_MINOR 0x03
#define VER_PATCH 0x00

// Author: Steve Richardson
// Software Name: NullAOS
// Description: UART Arduino operating system, top-level sketch.

const int hsc_key = 0;  // Hardware software compatibility, increments with
                        // versions when new features become available.
const uint8_t PIN_DEF[] = {
    2, 3, 4,  5,  6,  7,
    8, 9, 10, 11, 12, 13};  // Digital PINs mapped in this program
uint8_t IO_def[] = {1, 1, 1, 1, 1, 1,
                    1, 1, 1, 1, 1, 1};  // 0 is output 1 is input
uint8_t IO_lvl[] = {0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0};  // the level on the pins 1 is High 0 is Low
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
uint8_t instruction_payload[24];
bool sys_serial_backlog = false;
NullPacketComms comms;

// configures the NPC serial port to start handling packets, re-initialises IO
// to default state
void setup() {
  comms.init_port(115200, 32);
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
  if (Serial.available() > 0 && !pending_instruction) {
    pending_instruction = comms.read_packet();
    // take a deep copy of the instruction
    instruction_address = comms.packet_target_address;
    instruction_len = comms.packet_payload_len;
    for (int i = 0; i < instruction_len; i++) {
      instruction_payload[i] = comms.packet_payload[i];
    }
    comms.flush_rx_buffer();
    sys_serial_backlog = false;
    if (!pending_instruction) {
      comms.return_ack(1, 0, instruction_address);
    }
    comms.return_ack(0, 0, instruction_address);
  } else {
    sys_serial_backlog = true;
  }
}

// Checks if any instructions are pending and calls the handler if they are
void process_instruction() {
  if (pending_instruction) {
    bool good_data = handle_comms();
    // if (good_data) { comms.return_ack(0, 0, comms.packet_target_address);
    // } else { comms.return_ack(comms.debug_probe, 0,
    // comms.packet_target_address); }
    pending_instruction = false;
  } else if (sys_serial_backlog) {
    // comms.flush_rx_buffer();
    sys_serial_backlog = false;
  }
}
