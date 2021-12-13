bool isAddress = true;
byte address;
bool isCommand = false;
byte command;
byte data;

#define ZERO 0x00
#define TWO  0x01 
#define NINE  0x02 
#define DOT  0xFF
byte test;

void writeData() {
  byte message[12] = {
    TWO, NINE, DOT,         // 2 9 .
    ZERO, NINE, DOT,        // 0 9 .
    TWO, ZERO, ZERO, TWO,   // 2 0 0 2
    0x00, 0x00
  };

  byte reflected[10];
  for (int i = 0; i < 10; i++) {
    reflected[i] = ReverseByte(message[i]);
  }

  unsigned short checkSum = Compute_CRC8(reflected);
  byte firstByteOfCheckSum = (checkSum >> 8) & 0xFF;
  byte secondByteOfCheckSum = checkSum & 0xFF;

  message[10] = firstByteOfCheckSum;
  message[11] = secondByteOfCheckSum;
for(int k = 0; k < 5; k++){
  for (int i = 0; i < 12; i++) {
    if(k==2 && i==0){
      test=message[i];
      Serial.write((test<<3));
   
      }
      else if (k==3 && i==3){
           test=0x03;
      Serial.write(test);
        }
      else{
    Serial.write(message[i]);
      }
  }
  }
}

void setWriteModeRS485() {
  PORTD |= 1 << PD2;
  delay(1);
}

// переривання по завершенню передачі
ISR(USART_TX_vect)
{
  PORTD &= ~(1 << PD2); 
}

void setup() {
  delay(1000);

  DDRD = 0b00000111;
  PORTD = 0b11111000;
  // Интерфейс USART предназначен для коммуникации с периферией, такой как ПК. Передача и прием данных
  // может осуществляться на разных скоростях в синхронном и асинхронном режиме, а также с контролем четности,
  // различной длиной блока данных и др. В общем в нем есть все необходимое для обеспечения безошибочной коммуникации
  // между устройствами.
  /*
    Полный дуплекс (независимые прием и передача)
    Асинхронный и синхронный режим
    Внешняя/внутренняя синхронизация
    Высокое разрешение генератора скорости передачи
    Выбор длинны блока данных (5 - 9 бит) и длинны стоп бита (1 - 2)
    Проверка четности
    Проверка переполнения данных 
    Проверка на ошибки 
    Фильтрация паразитных шумов
    Прерывания
    Мультипроцессорный режим работы
    Двойная скорость в асинхронном режиме
   */
  Serial.begin(9600, SERIAL_8N1);
  // задає біт UCSZ02, який описаний тут: "Біти UCSZn2, поєднані з бітом UCSZn1: 0 в UCSRnC, встановлюють
  // кількість бітів даних (Символ SiZe) у кадрі. використання приймача та передавача ". Це в основному
  // дозволяє вам вибрати 9-бітовий серійний номер (8 біт є більш поширеним)
  // бит TXCIE0 регистра UCSR0B - разрешение прерывания при завершении передачи если установлен в 1.
  UCSR0B |= (1 << UCSZ02) | (1 << TXCIE0);
  // бит MPCM0 регистра UCSR0A - режим микропроцессорного обмена
  UCSR0A |= (1 << MPCM0);

  delay(1);

  address = 0x2D;
}

void loop() {
  data = (~PIND);
  data = data >> 3;
  if (Serial.available()) {
    byte inByte = Serial.read();
    if (isAddress) {
      if (address == inByte) {
          isAddress = false;
          isCommand = true;
          // присвоєння через логічне І (дивимось на бітики нинішнього значення і на це і присвоюємо їхнє логічне І
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

////////////////////////////////////////////////////////

unsigned short Compute_CRC8(byte* bytes) {
  const unsigned short generator = 0xD5;
  unsigned short crc = 0x00;

  for (int b = 0; b < 10; b++) {
    crc ^= (unsigned short) (bytes[b] << 8);

    for (int i = 0; i < 8; i++) {
      if ((crc & 0x8000) != 0) {
        crc = (unsigned short) ((crc << 1) ^ generator);
      } else {
        crc <<= 1;
      }
    }
  }
  unsigned short myNewResult = Reflect8(crc);
  return myNewResult;
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

// це є функція, в якій ми можемо реверснути байт, тобто вот всі його бітики поміняти
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
