#define BUTTON_PIN 28
#define LED_SIZE 8
#define DELAY 700

int led_pins[LED_SIZE];
int is_button_activated = 0;

void setup() {
  for(int i = 0; i < LED_SIZE; i++)
  {
    // ініціалізуємо піни від 30 по 37
    led_pins[i] = 30 + i;
    pinMode(led_pins[i], OUTPUT);
  }
  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
  if (digitalRead(BUTTON_PIN) == 1)
  {
    is_button_activated = 1;
  }
  if (is_button_activated && digitalRead(BUTTON_PIN) == 0)
  {
    for (int i = 0; i < LED_SIZE / 2; i++)
    {
      digitalWrite(led_pins[i], HIGH);
      delay(DELAY);
      digitalWrite(led_pins[i], LOW);
      digitalWrite(led_pins[LED_SIZE - 1 - i], HIGH);
      delay(DELAY);
      digitalWrite(led_pins[LED_SIZE - 1 - i], LOW);
    }
    is_button_activated = 0;
  }
}
