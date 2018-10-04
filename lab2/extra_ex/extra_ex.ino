#include <string.h>
#define LED 16
#define TIME_OUT 5000
#define BUFFER_SIZE 100

typedef enum {
  INIT = 0,
  REV_P_F,
  REV_E,
  REV_N,
  REV_F1,
  REV_SECUR_ON,
  REV_SECUR_OFF,
} State;

State state;
char temp;
bool led_state;
int idx;
void setup() {
  Serial.begin(9600);
  state = INIT;
  pinMode(LED, OUTPUT);
  led_state = 1;
  idx = 0;
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
        if (temp == 'O' || temp == 'o') {
          state = REV_P_F;
          time_begin = millis();
        }
        break;
      case REV_P_F:
        if (is_time_out(time_begin))
          state = INIT;
        else if (temp == 'P' || temp == 'p') {
          state = REV_E;
          time_begin = millis();
        }
        else if (temp == 'F' || temp == 'f') {
          state = REV_F1;
          time_begin = millis();
          
        }
        else  state = INIT;
        break;
      case REV_E:
        if (is_time_out(time_begin)) {
          state = INIT;
        }
        else if (temp == 'E' || temp == 'e') {
          state = REV_N;
          time_begin = millis();
        }
        else state = INIT;
        break;
      case REV_N:
        if (is_time_out(time_begin)) {
          state = INIT;
        }
        else if (temp == 'N' || temp == 'n') {
          state = REV_SECUR_ON;
          time_begin = millis();
        }
        else  state = INIT;
        break;
      case REV_F1:
        if (is_time_out(time_begin)) {
          state = INIT;
        }
        else if (temp == 'F' || temp == 'f') {
          state = REV_SECUR_OFF;
          time_begin = millis();
        }
        else  state = INIT;
        break;
      case REV_SECUR_ON:
        if (is_time_out(time_begin)) {
          state = INIT;
        }
        else if (temp == '#') {
          state = INIT;
          led_state = 0;
          digitalWrite(LED, led_state);
        }
        state = INIT;
        break;
      case REV_SECUR_OFF:
        if (is_time_out(time_begin)) {
          state = INIT;
        }
        else if (temp == '#') {
          led_state = 1;
          digitalWrite(LED, led_state);
        }
        state = INIT;
        break;
      default:
        break;
    }
  }
}
