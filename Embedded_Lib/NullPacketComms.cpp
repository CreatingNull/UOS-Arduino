/*
	NullPacketComms - Library for packet based, byte-payload communications using the Arduino UART. 
	Uses 2 byte addressing for simple function based filtering, or IO addressing.
	Has some error detection built in, such as length defined payload, and longitudinal redundancy checks.
	Originally written by Steve Richardson in 2015.
	This was written in my spare time as a hobby and as such is distributed under the MIT license (See footer).
*/

#include "Arduino.h"
#include "NullPacketComms.h"

NullPacketComms::NullPacketComms() {
}

bool NullPacketComms::init_port(unsigned long baud_rate, uint8_t buffer_size) {
    max_packet_len = buffer_size;
	packet_payload[max_packet_len-6];
	packet[max_packet_len];
	packet_tx[max_packet_len];
    switch (baud_rate) {
        case 115200:
            Serial.begin(baud_rate);
            break;
        case 9600:
            Serial.begin(baud_rate);
            break;
        default:
            return false;
    }
    return true;
}

bool NullPacketComms::close_port() {
    Serial.end();
    return true;
}

bool NullPacketComms::read_packet() {
    int packet_length = 0;
    int read_delay = 10;
    byte LRC = 0;
    bool complete = false;
    bool checksum_match = false;
    debug_probe = 128;
    while (Serial.available() > 0) {
        byte incoming = Serial.read();
        if (packet_length == 0) { //header
            if (incoming == '>') { packet[packet_length] = incoming; LRC = 0; packet_length++; }
        }
        else if (packet_length >= 1 && packet_length <= 3) { //to address, from address length
            packet[packet_length] = incoming; LRC = (LRC + incoming) & 0xff; packet_length++;
        }
        else if (packet_length >= 4 && packet_length <= 3+packet[3]) { //payload
            packet[packet_length] = incoming; LRC = (LRC + incoming) & 0xff; packet_length++;
        }
        else if (packet_length == 4+packet[3]) { //checksum
            packet[packet_length] = incoming; packet_length++;
            LRC = ((LRC ^ 0xff) + 1) & 0xff;
            if (LRC == packet[packet_length-1]) { checksum_match = true;}
        }
        else if (packet_length = 5+packet[3]) { //footer
            if (incoming == '<') {
                packet[packet_length] = incoming; packet_length++;
                complete = true;
            }
        }
        if (!complete && Serial.available() == 0) { //if the next byte hasn't arrived yet, delay based on baud
            for (int i=0; i<read_delay; i++) {
                if (Serial.available() > 0) {break;}
                delay(1);
            }
        }
    }
    if (complete && checksum_match) {
        process_packet(packet_length);
    }
	return complete && checksum_match;
}

int NullPacketComms::flush_rx_buffer() {
    int c = 0;
    while (Serial.available() > 0) {
        Serial.read();
        c++;
    }
    return c;
}

bool NullPacketComms::process_packet(uint8_t packet_len) {
    packet_target_address = packet[1];
    packet_payload_len = packet[3];
    for (int i = 0; i<packet_payload_len; i++) {
        packet_payload[i] = packet[i+4];
    }
	return true;
}

int NullPacketComms::generate_packet_data(byte payload[], uint8_t payload_len, uint8_t remote_address, uint8_t local_address, byte packet_tx[]) {
    int byte_count = 0;
    byte LRC = 0;
    packet_tx[byte_count] = '>'; byte_count++; //start packet
    packet_tx[byte_count] = remote_address; LRC = (LRC+packet_tx[byte_count]) & 0xff; byte_count++; //to address
    packet_tx[byte_count] = local_address; LRC = (LRC+packet_tx[byte_count]) & 0xff; byte_count++; //from address
    packet_tx[byte_count] = payload_len; LRC = (LRC+packet_tx[byte_count]) & 0xff; byte_count++; //data length
    //populate payload
    for (int i = 0; i < payload_len; i++) {
        packet_tx[byte_count] = payload[i]; LRC = (LRC+packet_tx[byte_count]) & 0xff; byte_count++;
    }
    LRC = ((LRC ^ 0xff) + 1) & 0xff;
    packet_tx[byte_count] = LRC; byte_count++; //longitudinal redundancy checksum
    packet_tx[byte_count] = '<'; byte_count++; //end packet
    return byte_count;
}

bool NullPacketComms::return_ack(uint8_t error_code, uint8_t remote_address, uint8_t local_address) {
    byte data[1] = {error_code};
    uint8_t byte_len = generate_packet_data(data, 1, remote_address, local_address, packet_tx);
	return send_packet(packet_tx, byte_len);
}

bool NullPacketComms::send_packet(byte packet_tx[], uint8_t packet_len) {
    uint8_t count_bytes = 0;
    for (int i = 0; i < packet_len; i++) {
        count_bytes += Serial.write(packet_tx[i]);
    }
    Serial.flush();
    if (count_bytes != packet_len-1) {
        return false;
    }
    return true;
}

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