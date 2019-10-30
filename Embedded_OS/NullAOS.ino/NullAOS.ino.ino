#include <NullPacketComms.h>
#define UNKNOWN_PIN 0xFF
//Author: Steve Richardson

const uint8_t PIN_DEF[] = {2,9,10,11,12,13}; // PINs mapped in this program
uint8_t IO_def[] = {0,0,0,0,0,0}; // 0 is output 1 is input
uint8_t IO_lvl[] = {0,1,1,1,1,1}; // the level on the pins 1 is High 0 is Low
uint8_t A_PIN_DEF[] = {A0,A1}; // analogue pins mapped in this program
uint8_t A_PIN_PULLUP[] = {0,0}; // analogue pin pullup state, 0 disabled, 1 enabled
word A_PIN_STATES[] = {65535,65535}; //the last read taken on the analogue pins, none / bad read is max word value
const uint8_t home_address = 1;
bool sys_ram_integrity = true;  
bool pending_instruction = false; //has the system cleared the last instruction
uint8_t instruction_address = 255;
uint8_t instruction_len = 0;
uint8_t instruction_payload[24];
bool sys_serial_backlog = false;
NullPacketComms comms;

void setup() { 
  comms.init_port(115200, 32); 
  sys_ram_integrity = reinit_io_from_ram();
}

bool reinit_io_from_ram() {
  for (int i = 0; i < sizeof(PIN_DEF); i++) {
    if (!write_IO(PIN_DEF[i], IO_lvl[i], IO_def[i])) {
      return false;
    }
  }
  for (int i=0; i<sizeof(A_PIN_DEF); i++) {  // initialise the analog inputs
    if (A_PIN_PULLUP[i] == 1) { pinMode(A_PIN_DEF[i], INPUT_PULLUP); }
    else { pinMode(A_PIN_DEF[i], INPUT); }
  }
  return true;
}


bool write_IO(uint8_t pin_index, uint8_t level, uint8_t io_type) {
  switch(io_type) {
    case (0): //DIO output
      if ((level == 0 || level == 1)){ //&& exists_in_byte_array(pin_index, DIO, DIO_LEN, true)) { 
        if (get_pin_mode(pin_index) != OUTPUT) { pinMode(pin_index, OUTPUT); }; 
        digitalWrite(pin_index, level); 
        return true;
      }
      break;
  }
  return false;
}

int read_IO(uint8_t pin_index, uint8_t io_type) {
  switch(io_type) {
    case(0): //DIO input
      break;
    case(1): //AIO input
      return analogRead(pin_index);
  }
}

bool exists_in_byte_array(uint8_t value, uint8_t arr[], uint8_t arr_len, bool ordered) {
  return true;
  if (ordered) { //do a binary search
    uint8_t low_range = 0;
    uint8_t high_range = arr_len-1;
    uint8_t index = uint8_t(high_range/2); //start in the middle
    for (uint8_t i = 0; i < arr_len; i++) {
      if (arr[index] == value) {
        return true;
      }
      else if (value < arr[index]) {
        high_range = index - 1;
      }
      else {
        low_range = index + 1;
      }
      uint8_t index_prior = index; 
      index = uint8_t((high_range + low_range)/2);
      if (index_prior == index) { return false; } //algorithm pooped out or value doesn't exist.
    }
  }
  else { //raw search
    for (int i = 0; i < arr_len; i++) {
      if (arr[i] == value) {
        return true;
      }
    }
  }
  return false;
}


void loop() {
  serial_poll();
  process_instruction();
}

void serial_poll() {
  if (Serial.available() > 0 && !pending_instruction) {
    pending_instruction = comms.read_packet();
    //take a deep copy of the instruction
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
  }
  else {
    sys_serial_backlog = true;
  }
}

void process_instruction() {
  if (pending_instruction) {
    bool good_data = handle_comms(); 
    //if (good_data) { comms.return_ack(0, 0, comms.packet_target_address); }
    //else { comms.return_ack(comms.debug_probe, 0, comms.packet_target_address); }
    pending_instruction = false;
  }
  else if (sys_serial_backlog) {
    //comms.flush_rx_buffer();
    sys_serial_backlog = false;
  }
}

bool handle_comms() {
  switch(instruction_address) {
    case 64: //raw digital IO override.
      if ((instruction_len % 3) != 0) { return false; } //the data is wrong
      for (int i = 0; i < instruction_len/3; i++) {
         if (!write_IO(              
          instruction_payload[uint8_t(i*3)], 
          instruction_payload[uint8_t(i*3+2)], 
          instruction_payload[uint8_t(i*3+1)])) { return false; } //the system cant process the action
      }
      return true; //all actions completed successfully 
    case 68: //reset IO from RAM
      if (instruction_len == 0) { 
         return reinit_io_from_ram();
      }
      return false;
    case 85: //Sample Analog IO
      byte payload[instruction_len*2];
      for (int i=0; i < instruction_len; i++) {
        if (instruction_payload[i] < 8) { // form payload 2*packet len bytes in little endian
          A_PIN_STATES[instruction_payload[i]] = read_IO(instruction_payload[i], 1);
          payload[2*i] = lowByte(A_PIN_STATES[instruction_payload[i]]);
          payload[2*i+1] = highByte(A_PIN_STATES[instruction_payload[i]]);
        }
        else {
          payload[2*i] = 255;
          payload[2*i+1] = 255;
        }
      }
      //ack is already sent so fire off the response packet now
      uint8_t ret_len = comms.generate_packet_data(payload, instruction_len*2, 0, instruction_address, comms.packet_tx); 
      return comms.send_packet(comms.packet_tx, ret_len);
    }
  return false; 
}

uint8_t get_pin_mode(uint8_t pin){
  uint8_t bit = digitalPinToBitMask(pin);
  uint8_t port = digitalPinToPort(pin);

  if (NOT_A_PIN == port) return UNKNOWN_PIN;
  if (0 == bit) return UNKNOWN_PIN;
  if (bit & bit - 1) return UNKNOWN_PIN;

  volatile uint8_t *reg, *out;
  reg = portModeRegister(port);
  out = portOutputRegister(port);

  if (*reg & bit) return OUTPUT;
  else if (*out & bit) return INPUT_PULLUP;
  else return INPUT;
}

