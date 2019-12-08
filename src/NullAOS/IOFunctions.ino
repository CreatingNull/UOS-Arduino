//Description: UART Pin Level Functions, low level wrapper functions

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
    case 0: //DIO output
      if ((level == 0 || level == 1)){ //&& exists_in_byte_array(pin_index, DIO, DIO_LEN, true)) { //todo do we want to re-implement this or move it to the pre-vetting stage?
        if (get_pin_mode(pin_index) != OUTPUT) { pinMode(pin_index, OUTPUT); }; 
        digitalWrite(pin_index, level); 
        return true;
      }
      break;
    case 1: //DIO input
      if (level == 0) { //input with pullup disabled
        if (get_pin_mode(pin_index) != INPUT) { pinMode(pin_index, INPUT); }
        return true;
      }
      else if (level == 1) { //input with pullup enabled
        if (get_pin_mode(pin_index) != INPUT_PULLUP) { pinMode(pin_index, INPUT_PULLUP); }
        return true;
      }
      break;
  }
  return false;
}


int read_IO(uint8_t pin_index, uint8_t io_type) {
  switch(io_type) {
    case 0: //DIO input
      return digitalRead(pin_index);
    case 1: //AIO input
      return analogRead(pin_index);
  }
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
