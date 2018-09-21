
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   
  delayMicroseconds(200000);
  digitalWrite(LED_BUILTIN, LOW);
  delayMicroseconds(200000);
}
