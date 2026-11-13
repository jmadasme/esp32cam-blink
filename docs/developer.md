# Guía para desarrolladores — ESP32-CAM Blink LED

## Estructura del código fuente

```
esp32cam-blink.ino
├── Cabecera (docstring del proyecto)
├── Constantes globales
│   ├── LED_FLASH_PIN   = 4
│   ├── BAUD_RATE       = 115200
│   ├── BLINK_DELAY_MS  = 1000
│   ├── LED_ON          = HIGH
│   └── LED_OFF         = LOW
├── void setup()
│   ├── Serial.begin(115200)
│   ├── delay(100)
│   ├── pinMode(4, OUTPUT)
│   ├── digitalWrite(4, LOW)
│   └── Serial.println("ESP32-CAM Blink iniciado")
└── void loop()
    ├── digitalWrite(4, HIGH)
    ├── Serial.println("LED ON")
    ├── delay(1000)
    ├── digitalWrite(4, LOW)
    ├── Serial.println("LED OFF")
    └── delay(1000)
```

## Dependencias

### Core
- **Plataforma**: `esp32:esp32` v3.3.10 (Espressif Systems)
- **Arduino framework**: Incluido en el core ESP32

### Librerías externas
Ninguna. El sketch usa únicamente las funciones built-in del core ESP32:
- `Serial` — Comunicación serie
- `pinMode()` — Configuración de pines
- `digitalWrite()` — Escritura digital
- `delay()` — Pausa bloqueante

No se requieren `#include` adicionales.

## Compilación

### Con arduino-cli
```bash
arduino-cli compile --fqbn esp32:esp32:esp32cam esp32cam-blink.ino
```

### Con Arduino IDE
1. Abrir `esp32cam-blink.ino`
2. Seleccionar placa: **AI Thinker ESP32-CAM**
3. Click en **Verificar** (✓)

## Subida (upload)

### Requisitos de hardware
1. Adaptador USB-TTL (FTDI, CP2102, CH340, etc.)
2. Conexiones:
   - TX (USB-TTL) → GPIO 3 (U0RXD)
   - RX (USB-TTL) → GPIO 1 (U0TXD)
   - 5V (USB-TTL) → VCC
   - GND (USB-TTL) → GND

### Proceso de programación
```
1. Conectar GPIO 0 a GND (entra en modo bootloader)
2. Presionar RST (reset)
3. Ejecutar upload
4. Desconectar GPIO 0 de GND
5. Presionar RST nuevamente → el firmware arranca
```

### Comando arduino-cli
```bash
arduino-cli upload -p /dev/ttyUSB0 --fqbn esp32:esp32:esp32cam esp32cam-blink.ino
```

## Monitor serie

```bash
arduino-cli monitor -p /dev/ttyUSB0 -c baudrate=115200
```

## Configuración de pines

| GPIO | Función       | Registro             | Configuración            |
|------|---------------|----------------------|--------------------------|
| 4    | LED Flash     | GPIO_OUT1_REG        | `pinMode(4, OUTPUT)`     |
| 1    | U0TXD (Serial)| UART_MEM_CONF_REG    | Configurado por `Serial` |
| 3    | U0RXD (Serial)| UART_MEM_CONF_REG    | Configurado por `Serial` |

## Modificación del comportamiento

### Cambiar velocidad de parpadeo
```cpp
const int BLINK_DELAY_MS = 500;  // Parpadeo cada 0.5 segundos
```

### Usar otro pin para el LED
```cpp
const int LED_FLASH_PIN = 2;  // Cambiar a GPIO 2 (LED azul integrado en algunas placas)
```

### Versión no bloqueante con millis()
```cpp
unsigned long previousMillis = 0;
const long interval = 1000;
bool ledState = LOW;

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(LED_FLASH_PIN, ledState);
    Serial.println(ledState ? "LED ON" : "LED OFF");
  }
}
```

## Pruebas

### Prueba 1: Compilación
```bash
arduino-cli compile --fqbn esp32:esp32:esp32cam esp32cam-blink.ino
```
Esperado: `Sketch uses 298188 bytes (9%) of program storage space.`

### Prueba 2: Upload
Verificar que el upload se completa sin errores y el chip se identifica.

### Prueba 3: Funcionamiento
Tras resetear la placa, el LED blanco debe parpadear y el monitor serie debe mostrar:
```
ESP32-CAM Blink iniciado
LED ON
LED OFF
...
```

### Prueba 4: Persistencia
Presionar RST. El LED debe reiniciar el ciclo desde el estado apagado.

## Notas de implementación

- **Arquitectura**: Sketch monofunción con `delay()` bloqueante. Es la implementación más simple y adecuada para un blink sin entradas ni sensores.
- **Serial**: Se usa `delay(100)` tras `Serial.begin()` para dar tiempo al periférico UART a estabilizarse antes del primer `println()`.
- **LED**: Se inicializa en LOW para asegurar estado apagado conocido.
- **Constantes**: Todas las constantes están agrupadas al inicio para facilitar su modificación.
- **Compatibilidad**: El código es compatible con cualquier placa basada en ESP32, solo requiere cambiar el FQBN de compilación y el pin del LED si es diferente.

## Mantenimiento futuro

Si se desea añadir funcionalidades (WiFi, cámara, sensores), se recomienda:
1. Migrar a una estructura con `millis()` no bloqueante.
2. Organizar el código en múltiples archivos .ino o .h/.cpp.
3. Usar máquinas de estado para gestionar múltiples periféricos.
4. Habilitar el watchdog del ESP32 para mayor robustez.
