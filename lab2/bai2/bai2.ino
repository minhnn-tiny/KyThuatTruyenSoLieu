
#define LED 16


char temp;
void setup() {
  Serial.begin(9600);
  digitalWrite(LED, HIGH);
  pinMode(LED, OUTPUT);
}
//
void loop() {
//  if (Serial.available()) {
    temp = Serial.read();
    if (temp == 'o' || temp == 'O')
      digitalWrite(LED, LOW);
    else if (temp == 'f' || temp == 'F')
      digitalWrite(LED, HIGH);
//  }
}
