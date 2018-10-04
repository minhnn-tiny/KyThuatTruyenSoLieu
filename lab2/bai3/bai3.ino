
#define LED 16
#define TIME_OUT 5000

typedef enum {
  INIT = 0,
  REV_O,
  REV_F1,
} State;

State state;
char temp;
bool led_state;
void setup() {
  Serial.begin(9600);
  state = INIT;
  pinMode(LED, OUTPUT);
  led_state = 1;
  digitalWrite(LED, led_state);
}

bool is_time_out(unsigned long time_begin) {
  if (millis() - time_begin > TIME_OUT) {
    Serial.println("TIME OUT!!");
    return 1;
  }
  return 0;
}

unsigned long time_begin;
void loop() {
  if (Serial.available()) {
    temp = Serial.read();
    switch (state) {
      case INIT:
        //        led_state = 1;/
        if (temp == 'O' || temp == 'o') {
          state = REV_O;
          time_begin = millis();
        }
        break;
      case REV_O:
        if (is_time_out(time_begin)) {
          state = INIT;
        }
        else {
          if (temp == 'N' || temp == 'n') {
            led_state = 0;
            digitalWrite(LED, led_state);
            state = INIT;
          }
          else if (temp == 'F' || temp == 'f') {
            state = REV_F1;
            time_begin = millis();
          }
          else if (temp == '\n') {
            state = state;
          }
          else {
            state = INIT;
          }
        }
        break;
      case REV_F1:
        if (is_time_out(time_begin)) {
          state = INIT;
        }
        else {
          if (temp == 'F' || temp == 'f') {
            led_state = 1;
            digitalWrite(LED, led_state);
            state = INIT;
          }
        }
        break;
      default:
        break;
    }
  }
}
