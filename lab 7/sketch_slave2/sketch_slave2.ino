bool is_address = true;
byte address;
bool is_command = false;
byte command;

float temperature_C = 0;

String number_to_string;
byte message[] = {};

ISR(USART_TX_vect) {
  PORTD &= ~(1 << PD2);
}

ISR(ADC_vect) {
  float Vin = ADC * 5.0 / 1024;
  temperature_C = (Vin - 0.5) * 100; 
}

void setWriteModeRS485() {
  PORTD |= 1 << PD2;
  ADCSRA |= 1 << ADSC;
  delay(1);
}

int writeData(float number) {
  number_to_string = String(number);
  
  byte message[number_to_string.length() + 2] = {};
  for (int i = 0; i < number_to_string.length(); i++){
    switch (number_to_string[i]) {
      case '0':
        message[i] = 0x0A;
        break;
      case '1':
        message[i] = 0x1A;
        break;
      case '2':
        message[i] = 0x2A;
        break;
      case '3':
        message[i] = 0x3A;
        break;
      case '4':
        message[i] = 0x4A;
        break;
      case '5':
        message[i] = 0x5A;
        break;
      case '6':
        message[i] = 0x6A;
        break;
      case '7':
        message[i] = 0x7A;
        break;
      case '8':
        message[i] = 0x8A;
        break;  
      case '9':
        message[i] = 0x9A;
        break;
      case '.':
        message[i] = 0xFF;
        break;
      default:
        break;
      } 
  }

  byte reflected[number_to_string.length()];
  for (int i = 0; i < number_to_string.length(); i++) {
    reflected[i] = ReverseByte(message[i]);
  }
  message[number_to_string.length()] = 0x00;
  message[number_to_string.length() + 1] = 0x00;
  unsigned short checkSum = Compute_CRC8(reflected);
  byte firstByteOfCheckSum = (checkSum >> 8) & 0xFF;
  byte secondByteOfCheckSum = checkSum & 0xFF;

  message[number_to_string.length()] = firstByteOfCheckSum;
  message[number_to_string.length() + 1] = secondByteOfCheckSum;

  for (int i = 0; i < 7; i++) {
    Serial.write(message[i]);
  }
}

void setup() {
  
  DDRD = 0b00000111;
  PORTD = 0b11111000;

  Serial.begin(9600, SERIAL_8N1);
  UCSR0B |= (1 << UCSZ02) | (1 << TXCIE0);
  UCSR0A |= (1 << MPCM0);

  delay(1);
  address = 0xEA;
  
  DDRC = 0x00;
  PORTC = 0b11111110;
  ADMUX = 1 << REFS0;
  ADCSRA = (1 << ADEN)|(1 << ADIE)|(1 << ADPS2)|(1 << ADPS1);
  
  pinMode(A0, INPUT);
}

void loop() {
  if (Serial.available()) {
    byte from_serial = Serial.read();
    if (is_address) {
      if (address == from_serial) {
        is_address = false;
        is_command = true;
        UCSR0A &= ~(1 << MPCM0);
      }
    } else if (is_command) {
      command = from_serial;
      is_command = false;
      if (from_serial == 0xB1) {
        is_address = true;
        setWriteModeRS485();
        
        writeData(temperature_C);     
      }
    }
  }
}

unsigned short Compute_CRC8(byte* bytes) {
  const unsigned short generator = 0xD5;
  unsigned short crc = 0x00;

  for (int b = 0; b < 5; b++) {
    crc ^= (unsigned short) (bytes[b] << 8);

    for (int i = 0; i < 8; i++) {
      if ((crc & 0x8000) != 0) {
        crc = (unsigned short) ((crc << 1) ^ generator);
      } else {
        crc <<= 1;
      }
    }
  }
  unsigned short reflected_result = Reflect8(crc);
  return reflected_result;
}

unsigned short Reflect8(unsigned short val) {
  unsigned short resVal = 0;
  for (int i = 0; i < 16; i++) {
    if ((val & (1 << i)) != 0) {
      resVal |= (unsigned short)(1 << (15 - i));
    }
  }
  return resVal;
}

byte ReverseByte(byte b) {
  int a = 0;
  for (int i = 0; i < 8; i++) {
    if ((b & (1 << i)) != 0) {
      a |= 1 << (7 - i);
    }
  }
  return (byte) a;
}

int CombineBytes(byte b1, byte b2) {
  int combined = b1 << 8 | b2;
  return combined;
}
