/*
	NullPacketComms - Library for packet based, byte-payload communications using the Arduino UART. 
	Uses 2 byte addressing for simple function based filtering, or IO addressing.
	Has some error detection built in, such as length defined payload, and longitudinal redundancy checks.
	Originally written by Steve Richardson in 2015.
	This was written in my spare time as a hobby and as such is distributed under the MIT license (See footer).
*/

#ifndef NullPacketComms_h
#define NullPacketComms_h

#include "Arduino.h"
class NullPacketComms {
	public:
	NullPacketComms();
	uint8_t max_packet_len;
	byte packet_tx[];
	bool init_port(unsigned long baud_rate, uint8_t buffer_size);
	bool read_packet();
	bool process_packet(uint8_t packet_len);
	int flush_rx_buffer();
	bool close_port();
	uint8_t packet_target_address;
	uint8_t packet_payload_len;
	byte packet_payload[];
    bool return_ack(uint8_t error_code, uint8_t remote_address, uint8_t local_address);
    int generate_packet_data(byte payload[], uint8_t payload_len, uint8_t remote_address, uint8_t local_address, byte packet_tx[]);
    bool send_packet(byte packet_tx[], uint8_t packet_len);
    uint8_t debug_probe;
	private:
	byte packet[];
	uint8_t __max_packet_length;
	uint8_t __max_read_delay;
};

#endif

/*
Copyright (c) 2019 Steve Richardson

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/