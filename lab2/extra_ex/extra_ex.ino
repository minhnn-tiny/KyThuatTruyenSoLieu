#include <string.h>
#define LED 16
#define TIME_OUT 5000
#define BUFFER_SIZE 100

typedef enum {
  RECEIVING,
  ACK,
} State;

State state;
char temp;
bool led_state;
char buff[BUFFER_SIZE];
String on_ack = "open#";
String off_ack = "off#";

void setup() {
  Serial.begin(9600);
  state = RECEIVING;
  pinMode(LED, OUTPUT);
  led_state = 1;
  strcpy(buff, "") ;
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
  switch (state) {
    case RECEIVING:
      if (is_time_out(time_begin)) {
        time_begin = millis();
        strcpy(buff, "");
      }
      if (Serial.available()) {
        temp = Serial.read();
        strcat(buff, &temp);
        time_begin = millis();
        if (temp == '#') {
          state = ACK;
        }
      }
      break;
    case ACK:
      if ((strcmp(&buff[strlen(buff) - 5], &on_ack[0])) == 0) {
        led_state = 0;
        digitalWrite(LED, led_state);
        Serial.println("LED ON");
        state = RECEIVING;
      }
      else if ((strcmp(&buff[strlen(buff) - 4], &off_ack[0])) == 0) {
        led_state = 1;
        digitalWrite(LED, led_state);
        Serial.println("LED OFF");
        state = RECEIVING;
      }
      else {
        Serial.println("command fail");
        Serial.println(&buff[strlen(buff) - 5]);
        state = RECEIVING;
        time_begin = millis();
        strcpy(buff, "");
      }
      break;
    default:
      break;
  }
}
