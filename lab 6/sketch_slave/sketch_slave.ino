#define Y 0x01
#define E 0x02
#define H 0x03
#define O 0x04
#define R 0x05
#define V 0x6A
#define A 0x07
#define I 0x08
#define K 0x09
#define L 0x0A
#define T 0x3A
#define E 0x0B
#define S 0x0C
#define N 0x0D

#define _ 0x00

byte res;
bool isAddress = true;
byte address;
bool isCommand = false;
byte command;
byte data;

void setWriteModeRS485() {
  PORTD |= 1 << PD2;
  delay(1);
}

// переривання по завершенню передачі
ISR(USART_TX_vect) {
  PORTD &= ~(1 << PD2); 
}

// функція шоб віддавати дані на мій майстер
int writeData() {
  byte message[31] = {
    Y, E, H, O, R, O, V, A, _, // Yehorova 
    V, I, K, T, O, R, I, I, A, _, // Viktoriia 
    O, L, E, K, S, I, I, V, N, A, // Oleksiivna
    0x00, 0x00
  };

  byte reflected[29];
  for (int i = 0; i < 29; i++) {
    reflected[i] = ReverseByte(message[i]);
  }

  unsigned short checkSum = Compute_CRC8(reflected);
  byte firstByteOfCheckSum = (checkSum >> 8) & 0xFF;
  byte secondByteOfCheckSum = checkSum & 0xFF;

  message[29] = firstByteOfCheckSum;
  message[30] = secondByteOfCheckSum;

  // спотворення - в нас є п'ять різних записів.
  // перший слейв передає прізвище, ім'я, по батькові
  // і в мене там має бути спотворення в другому і п'ятому кейсі
  // фактично, я просто виловлюю той момент і виловлюю конкретний біт і виконую побітовий зсув вліво
  for(int k = 0; k < 5; k++){
  for (int i = 0; i < 31; i++) {
    if(k == 1 && i == 2) {
      res = message[i];
      Serial.write((1<<res));
    }
    else if (k == 4 && i == 3) {
      res = message[i];
      Serial.write((0 << res)|(2 << res)|(5 << res));
    }
    else{
      Serial.write(message[i]);
    }
   
  }
  }
}

void setup() {
  delay(1000);
  DDRD = 0b00000111;
  PORTD = 0b11111000;

  Serial.begin(9600, SERIAL_8N1);
  UCSR0B |= (1 << UCSZ02) | (1 << TXCIE0);
  UCSR0A |= (1 << MPCM0);

  delay(1);

  address = 0x2B;
}

void loop() {
  if (Serial.available()) {
    byte inByte = Serial.read();
    if (isAddress) {
      if (address == inByte) {
          isAddress = false;
          isCommand = true;
          UCSR0A &= ~(1 << MPCM0);
        }
    } else if (isCommand) {
      command = inByte;
      isCommand = false;
      if (command = 0xB1) {
          isAddress = true;
          setWriteModeRS485();
          writeData();
      }
    }
  }
}

///////////////////////////////////////////////////////

unsigned short Compute_CRC8(byte* bytes) {
  const unsigned short generator = 0xD5;
  unsigned short crc = 0x0Compute_C0;

  for (int b = 0; b < 29; b++) {
    crc ^= (unsigned short) (bytes[b] << 8);

    for (int i = 0; i < 8; i++) {
      if ((crc & 0x8000) != 0) { // найбільш значущий біт засетано, зсуваємо реєстр і виконуємо XOR, враховуючи 9й біт
        crc = (unsigned short) ((crc << 1) ^ generator);
      } else {
        crc <<= 1; // не засетано, тому йдем до наступного біта
      }
    }
  }
  unsigned short result = Reflect8(crc);
  return result;
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
