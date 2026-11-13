/*
 * ESP32-CAM Blink LED
 * ===================
 * Placa:  ESP32-CAM (AI-Thinker)
 * LED:    Flash blanco integrado en GPIO 4 (activo HIGH)
 * Ciclo:  1s ON / 1s OFF
 * Serial: 115200 baud
 *
 * Mapa de pines:
 *   GPIO 4  - LED Flash (OUTPUT)
 *   GPIO 1  - U0TXD (Serial TX al adaptador USB-TTL)
 *   GPIO 3  - U0RXD (Serial RX desde adaptador USB-TTL)
 */

// Constantes
const int LED_FLASH_PIN = 4;     // GPIO del LED de flash integrado
const int BAUD_RATE = 115200;     // Velocidad del monitor serie
const int BLINK_DELAY_MS = 1000;  // 1 segundo por estado
const int LED_ON = HIGH;          // Activo alto
const int LED_OFF = LOW;          // Activo bajo

void setup() {
  // Inicializar monitor serie
  Serial.begin(BAUD_RATE);
  delay(100);  // Pequeña pausa para que el serial se estabilice

  // Configurar pin del LED como salida
  pinMode(LED_FLASH_PIN, OUTPUT);

  // Asegurar LED apagado al inicio
  digitalWrite(LED_FLASH_PIN, LED_OFF);

  // Mensaje de inicio
  Serial.println("ESP32-CAM Blink iniciado");
  Serial.print("LED Flash en GPIO ");
  Serial.print(LED_FLASH_PIN);
  Serial.print(" | Ciclo: ");
  Serial.print(BLINK_DELAY_MS);
  Serial.print("ms ON / ");
  Serial.print(BLINK_DELAY_MS);
  Serial.println("ms OFF");
}

void loop() {
  // Encender LED
  digitalWrite(LED_FLASH_PIN, LED_ON);
  Serial.println("LED ON");
  delay(BLINK_DELAY_MS);

  // Apagar LED
  digitalWrite(LED_FLASH_PIN, LED_OFF);
  Serial.println("LED OFF");
  delay(BLINK_DELAY_MS);
}
