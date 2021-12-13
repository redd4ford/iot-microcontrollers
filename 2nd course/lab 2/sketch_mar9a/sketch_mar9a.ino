#define DELAY 700
#define FIRST_BUTTON_PIN 26
#define SECOND_BUTTON_PIN 28
#define LED_SIZE 8

const int led_pins[] = {30, 31, 32, 33, 34, 35, 36, 37};

bool is_first_button_activated = false;
bool is_second_button_activated = false;

void setup() {
  for (auto led : led_pins) {
    pinMode(led, OUTPUT);
  }
  pinMode(FIRST_BUTTON_PIN, INPUT_PULLUP);
  pinMode(SECOND_BUTTON_PIN, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    int inByte = Serial.read();
    if (inByte == '1') {
      is_first_button_activated = true;
    }

    else if (inByte == '2')
    {
      is_second_button_activated = true;
    }
  }
    if (!digitalRead(FIRST_BUTTON_PIN) || is_first_button_activated) {
    Serial.write("1");
    is_first_button_activated = false;
    
    for (int i = 0; i < LED_SIZE / 2; i++) {
      digitalWrite(led_pins[i], HIGH);
      delay(DELAY);
      digitalWrite(led_pins[i], LOW);
    
      digitalWrite(led_pins[LED_SIZE - i - 1], HIGH);
      delay(DELAY);
      digitalWrite(led_pins[LED_SIZE - i - 1], LOW);
    }
  }
  if (!digitalRead(SECOND_BUTTON_PIN) || is_second_button_activated) {
    Serial.write("2");
    is_second_button_activated = false;

    for (int i = 0; i < LED_SIZE; i++) {
      digitalWrite(led_pins[i], HIGH);
      delay(DELAY);
      digitalWrite(led_pins[i], LOW);
    }
  }

}
