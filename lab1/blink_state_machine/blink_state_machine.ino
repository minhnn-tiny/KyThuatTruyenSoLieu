
#define INIT 0
#define ON 1
#define OFF 2

int state;
unsigned long T_on, T_off;
unsigned long count;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  state = INIT;
  count = 0;
  T_on = 300;
  T_off = 200;
}

void loop() {
  switch (state) {
    case INIT:
      digitalWrite(LED_BUILTIN, HIGH);
      count = 0;
      state = ON;
      break;
    case ON:
      if (count > T_on) {
        state = OFF;
        count = 0;
        digitalWrite(LED_BUILTIN, HIGH);
      }
      count++;
      break;
    case OFF:
      if (count > T_off) {
        state = ON;
        count = 0;
        digitalWrite(LED_BUILTIN, LOW);
      }
      count++;
      break;
    default:
      break;
  }
  delay(10);
}
