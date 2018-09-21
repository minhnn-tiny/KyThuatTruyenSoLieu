
#define sensor 0

enum state_t {
  INIT = 0,
  OPEN,
  CLOSE,
};
state_t state;
unsigned long TIME_OUT;
unsigned long time_begin;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(sensor, INPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  state = INIT;
  TIME_OUT = 3000;
  time_begin = 0;
}

void loop() {
  switch (state) {
    case INIT:
      if (digitalRead(sensor) == 0) {
        state = OPEN;
        digitalWrite(LED_BUILTIN, LOW);
      }
      break;
    case OPEN:
      if (digitalRead(sensor) == 1) {
        state = CLOSE;
        time_begin = millis();
      }
      break;
    case CLOSE:
      if (digitalRead(sensor) == 0) {
        state = OPEN;
      }
      if(millis() - time_begin > TIME_OUT){
        digitalWrite(LED_BUILTIN, HIGH);
        state = INIT;
      }
      break;
    default:
      break;
  }
}
