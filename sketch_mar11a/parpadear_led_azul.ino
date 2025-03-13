#define LED_BUILTIN 2  // GPIO donde está el LED azul (ajusta si es necesario)

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // Enciende el LED
  delay(300);                        // Espera medio segundo
  digitalWrite(LED_BUILTIN, LOW);   // Apaga el LED
  delay(300);                        // Espera medio segundo
}