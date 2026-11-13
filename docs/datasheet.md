# Datasheet — ESP32-CAM Blink LED

## Identificación del proyecto

| Campo               | Valor                               |
|---------------------|-------------------------------------|
| Nombre              | ESP32-CAM Blink LED                 |
| Versión             | 1.0.0                               |
| Placa objetivo      | ESP32-CAM (AI-Thinker)              |
| Microcontrolador    | ESP32-D0WD-V3                       |
| Fecha de creación   | 2026-06-30                          |
| Tipo de proyecto    | Firmware embebido / Blink demo      |

## Especificaciones eléctricas

| Parámetro                | Mínimo | Típico | Máximo | Unidad |
|--------------------------|--------|--------|--------|--------|
| Voltaje de alimentación  | 4.5    | 5.0    | 5.5    | V      |
| Corriente en reposo      | —      | 60     | —      | mA     |
| Corriente con LED ON     | —      | 250    | 300    | mA     |
| Voltaje lógico GPIO      | 3.0    | 3.3    | 3.6    | V      |
| Frecuencia CPU           | —      | 240    | —      | MHz    |

## Pines de conexión

| Pin del conector | Señal   | Dirección | Conexión externa              |
|------------------|---------|-----------|-------------------------------|
| Pin 1            | 5V      | Entrada   | Alimentación 5V desde USB-TTL |
| Pin 2            | GND     | —         | Tierra común                  |
| Pin 3            | GPIO 1  | Salida    | TX → RX del USB-TTL (Serial)  |
| Pin 4            | GPIO 3  | Entrada   | RX ← TX del USB-TTL (Serial)  |
| Pin 5            | GPIO 0  | Entrada   | GND durante programación      |
| Pin 6            | GPIO 4  | Salida    | LED Flash blanco integrado    |

## Comunicación serie

| Parámetro         | Valor       |
|-------------------|-------------|
| Baudrate          | 115200      |
| Data bits         | 8           |
| Paridad           | Ninguna     |
| Stop bits         | 1           |
| Flow control      | Ninguno     |
| Terminal          | `arduino-cli monitor -p /dev/ttyUSB0 -c baudrate=115200` |

### Formato de salida

```
ESP32-CAM Blink iniciado
LED Flash en GPIO 4 | Ciclo: 1000ms ON / 1000ms OFF
LED ON
LED OFF
LED ON
LED OFF
...
```

## Configuración de fábrica (software)

| Constante          | Valor  | Descripción                          |
|--------------------|--------|--------------------------------------|
| `LED_FLASH_PIN`    | 4      | GPIO del LED de flash                |
| `BAUD_RATE`        | 115200 | Velocidad del puerto serie            |
| `BLINK_DELAY_MS`   | 1000   | Intervalo de conmutación del LED (ms) |

## Características mecánicas

| Parámetro                | Valor              |
|--------------------------|--------------------|
| Dimensiones de la placa  | 27 × 40.5 × 4.5 mm |
| Peso                     | ~9 g               |
| Conector de antena       | U.FL / IPEX        |
| Conector de cámara       | FPC de 24 pines    |
| Ranura microSD           | Sí, lateral        |

## Condiciones ambientales

| Parámetro         | Rango             |
|-------------------|-------------------|
| Temperatura operación | -20 °C a 85 °C |
| Humedad relativa  | 0% a 90% (sin condensación) |

## Indicadores LED

| LED        | Color  | GPIO | Comportamiento                |
|------------|--------|------|-------------------------------|
| Flash      | Blanco | 4    | Parpadea 1s ON / 1s OFF       |

## Notas de aplicación

1. **Alimentación**: No alimentar la ESP32-CAM directamente desde el pin de 3.3V del USB-TTL si el LED flash se usará por períodos prolongados. Usar la entrada de 5V que alimenta el regulador AMS1117-3.3 onboard.
2. **Disipación**: El LED flash puede alcanzar temperaturas elevadas (>60 °C) tras minutos de funcionamiento continuo. No obstruir la ventilación.
3. **Programación**: El proceso de upload requiere poner GPIO 0 a GND y presionar RST. Tras el upload, quitar GPIO 0 de GND y presionar RST nuevamente.
