#define BA 50
#define BB 51
#define BC 52
#define BD 53
#define BUZZER 38
#define BEEP_DELAY 400
#define DOT 30

const int DIGIT_PATTERNS[10] = {
  B1111110, // A B C D E F G 
  B0110000,
  B1101101,
  B1111001,
  B0110011,
  B1011011,
  B1011111,
  B1110000,
  B1111111,
  B1111011
};

bool is_running = true;
bool is_clear = false;
bool is_journal_mode = false;

int ofc_vf = 0;

struct Time
{
  uint8_t second, minute, hour;
};

Time T0 = {0, 0, 0};
Time time_buffer[10];

int curr_buffer_pos = 0;
int curr_journal_pos = 0;

int overflow_proteus = 0;

ISR(TIMER0_COMPA_vect)
{
  ofc_vf++;
  overflow_proteus++;
  if (overflow_proteus == 60){
    if (is_clear)
    {
      T0 = {0, 0, 0};
      is_clear = false;
    }
    if (is_running) 
    {
      if (++T0.second == 60)
      {
        T0.second = 0;
        if (++T0.minute == 60)
        {
          T0.minute = 0;
          if (++T0.hour == 24)
          {
            T0.hour = 0;
          }
        }
      }
    }
  overflow_proteus = -1;
  }
}

inline void seg7ShowTime();
inline void shortBeep();
inline void doubleShortBeep();

void setup()
{
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  pinMode(BA, INPUT_PULLUP);
  pinMode(BB, INPUT_PULLUP);
  pinMode(BC, INPUT_PULLUP);
  pinMode(BD, INPUT_PULLUP);

  noInterrupts();
  TCCR0A = WGM10;
  TCCR0B = (1 << WGM12) | (1 << CS02) | (1 << CS00);
  TIMSK0 = (1 << OCIE0A);
  OCR0A = 25000;
  interrupts();
}

void loop()
{
  int a = digitalRead(BA);
  int b = digitalRead(BB);
  int c = digitalRead(BC);
  int d = digitalRead(BD);
  if (T0.minute > 0 && T0.second == 00)
  {
    doubleShortBeep();
  }
  delay(30);

  if (is_journal_mode && !is_running && curr_buffer_pos > 0){
    if (ofc_vf >= 150){
      if (curr_journal_pos < curr_buffer_pos){
        T0 = time_buffer[curr_journal_pos];
        curr_journal_pos++;
      }
      else curr_journal_pos = 0;
      ofc_vf = 0;
      }
  }
  
  seg7ShowTime();
  if (!digitalRead(BA) && a)
  {
    shortBeep();
    is_running = !is_running;
    if (is_running)
    {
      is_clear = true;
    }
    is_journal_mode = false;
  }
  if (!digitalRead(BB) && b)
  {
    shortBeep();
    if (curr_buffer_pos > 9)
    {
      curr_buffer_pos = 0;
    }
    time_buffer[curr_buffer_pos] = T0;
    curr_buffer_pos++;
  }
  if (!digitalRead(BC) && c)
  {
    shortBeep();
    curr_buffer_pos = 0;
  }
  if (!digitalRead(BD) && d)
  {
    shortBeep();
    is_journal_mode = !is_journal_mode;
  }
  
}

inline void shortBeep()
{
  digitalWrite(BUZZER, HIGH);
  delay(BEEP_DELAY);
  digitalWrite(BUZZER, LOW);
}

inline void doubleShortBeep()
{
  digitalWrite(BUZZER, HIGH);
  delay(BEEP_DELAY * 2);
  digitalWrite(BUZZER, LOW);
}

void seg7ShowTime()
{
  int vertex[6] = {
      T0.hour / 10, T0.hour % 10,
      T0.minute / 10, T0.minute % 10,
      T0.second / 10, T0.second % 10
  };
  for (int i = 0; i < 6; i++)
  {
    int j = vertex[i];
    
    switch (i)
    {
    case 0:
      PORTA = B00000000;
      PORTA = B00000001;
      break;
      
    case 1:
      PORTA = B00000000;
      PORTA = B00000010;
      digitalWrite(DOT, 1);
      delay(3);
      digitalWrite(DOT, 0);
      break;
      
    case 2:
      PORTA = B00000000;
      PORTA = B00000100;
      break;
      
    case 3:
      PORTA = B00000000;
      PORTA = B00001000;
      digitalWrite(DOT, 1);
      delay(3);
      digitalWrite(DOT, 0);
      break;
      
    case 4:
      PORTA = B00000000;
      PORTA = B00010000;
      break;
      
    case 5:
      PORTA = B00000000;
      PORTA = B00100000;
      break;

    default:
      PORTA = B00000000;
      PORTA = B10000000;
      break;
    }
  PORTC = B000000;
  PORTC = DIGIT_PATTERNS[j];
  delayMicroseconds(4000);
  }
}
