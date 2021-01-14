/*
        NullPacketComms - Library for packet based, byte-payload communications
   using the Arduino UART. Uses 2 byte addressing for simple function based
   filtering, or IO addressing. Has some error detection built in, such as
   length defined payload, and longitudinal redundancy checks. Originally
   written by Steve Richardson in 2015. This was written in my spare time as a
   hobby and as such is distributed under the MIT License (See LICENSE.md).
*/

#ifndef NullPacketComms_h
#define NullPacketComms_h

#include <Arduino.h>

class NullPacketComms {
 public:
  NullPacketComms();
  uint8_t max_packet_len;
  byte packet_tx[32];
  bool init_port(unsigned long baud_rate, uint8_t buffer_size);
  bool read_packet();
  bool process_packet(uint8_t packet_len);
  int flush_rx_buffer();
  bool close_port();
  uint8_t packet_target_address;
  uint8_t packet_payload_len;
  byte packet_payload[32];
  bool return_ack(uint8_t error_code, uint8_t remote_address,
                  uint8_t local_address);
  int generate_packet_data(byte payload[], uint8_t payload_len,
                           uint8_t remote_address, uint8_t local_address,
                           byte packet_tx[]);
  bool send_packet(byte packet_tx[], uint8_t packet_len);
  uint8_t debug_probe;

 private:
  byte packet[32];
};

#endif