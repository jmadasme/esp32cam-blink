# ESP32-CAM Blink LED

Proyecto Arduino minimalista que hace parpadear el LED de flash blanco integrado (GPIO 4) de la placa **ESP32-CAM (AI-Thinker)** con un ciclo de 1 segundo encendido y 1 segundo apagado.

## Principio de funcionamiento

La ESP32-CAM AI-Thinker tiene un LED de flash blanco de alta intensidad montado en la PCB junto a la lente de la cámara OV2640. Este LED está conectado al GPIO 4 del ESP32 y es controlado mediante un transistor MOSFET de canal N que permite conmutarlo con la lógica de 3.3V del microcontrolador.

El sketch configura el GPIO 4 como salida digital y alterna su estado entre HIGH y LOW cada 1000 ms, generando un parpadeo continuo.

## Especificaciones técnicas

| Parámetro               | Valor                     |
|-------------------------|---------------------------|
| Placa                   | ESP32-CAM (AI-Thinker)    |
| Microcontrolador        | ESP32-D0WD-V3 (Xtensa LX6 dual-core @ 240 MHz) |
| LED                     | Flash blanco integrado en GPIO 4 |
| Ciclo de parpadeo       | 1s ON / 1s OFF            |
| Flash usado             | 298 KB (9% de 4 MB)       |
| RAM usada               | 22 KB (6% de 320 KB)      |
| Puerto serie            | 115200 baud               |
| FQBN                    | `esp32:esp32:esp32cam`    |

## Mapa de pines

| Pin    | Modo    | Conexión                         | Notas                                    |
|--------|---------|----------------------------------|------------------------------------------|
| GPIO 4 | OUTPUT  | LED Flash blanco integrado       | HIGH = encendido, LOW = apagado          |
| GPIO 1 | U0TXD   | TX del monitor serie             | Conectar al RX del adaptador USB-TTL     |
| GPIO 3 | U0RXD   | RX del monitor serie             | Conectar al TX del adaptador USB-TTL     |
| 5V     | POWER   | Alimentación 5V                  | Conectar al VCC del adaptador USB-TTL    |
| GND    | POWER   | Tierra común                     | Conectar al GND del adaptador USB-TTL    |
| GPIO 0 | INPUT   | Boot mode (programación)         | Conectar a GND durante el upload         |

## Diagrama de conexión

```
┌──────────────────────────────────┐
│       ADAPTADOR USB-TTL          │
│  ┌───────────┐    ┌──────────┐   │
│  │  USB a PC │    │ PINES:   │   │
│  │           │    │ TX  ─────┼───┼──── GPIO 3 (U0RXD)
│  │           │    │ RX  ─────┼───┼──── GPIO 1 (U0TXD)
│  │           │    │ 5V  ─────┼───┼──── VCC (5V)
│  │           │    │ GND ─────┼───┼──── GND
│  └───────────┘    └──────────┘   │
└──────────────────────────────────┘
         │
         │ USB
         ▼
      [PC/Laptop]
```

**Nota:** La ESP32-CAM no tiene puerto USB nativo. Requiere un adaptador USB-TTL (FTDI, CP2102, CH340, etc.) conectado a sus pines serie.

## Requisitos previos

1. **Arduino CLI** instalado (`arduino-cli`)
2. **Core ESP32** instalado:
   ```bash
   arduino-cli core install esp32:esp32
   ```
3. **Adaptador USB-TTL** (FTDI/CP2102/CH340) conectado a la ESP32-CAM:
   - TX del adaptador → GPIO 3 (U0RXD) de la ESP32-CAM
   - RX del adaptador → GPIO 1 (U0TXD) de la ESP32-CAM
   - 5V del adaptador → VCC de la ESP32-CAM
   - GND del adaptador → GND de la ESP32-CAM
4. Permisos de acceso al puerto serie (`dialout` en Linux)

## Instalación y uso

### 1. Clonar o copiar los archivos

```bash
git clone <url-del-repositorio>
cd esp32cam-blink
```

### 2. Compilar

```bash
arduino-cli compile --fqbn esp32:esp32:esp32cam esp32cam-blink.ino
```

### 3. Subir a la placa

1. Conecta **GPIO 0 a GND** (modo programación).
2. Presiona el botón **RST** (reset) de la ESP32-CAM.
3. Ejecuta:
   ```bash
   arduino-cli upload -p /dev/ttyUSB0 --fqbn esp32:esp32:esp32cam esp32cam-blink.ino
   ```
4. Al finalizar, **desconecta GPIO 0 de GND** y presiona **RST** nuevamente.

### 4. Verificar funcionamiento

El LED blanco de la ESP32-CAM debe comenzar a parpadear (1s encendido, 1s apagado).

Para ver los mensajes del monitor serie:
```bash
arduino-cli monitor -p /dev/ttyUSB0 -c baudrate=115200
```

Deberías ver:
```
ESP32-CAM Blink iniciado
LED Flash en GPIO 4 | Ciclo: 1000ms ON / 1000ms OFF
LED ON
LED OFF
LED ON
LED OFF
...
```

## Calibración

No requiere calibración. Si se desea cambiar la velocidad de parpadeo, modificar la constante `BLINK_DELAY_MS` en `esp32cam-blink.ino`:

```cpp
const int BLINK_DELAY_MS = 500;  // Parpadeo más rápido (0.5 segundos)
```

## Advertencias

- ⚠️ **Alimentación**: La ESP32-CAM consume hasta ~300 mA con el LED encendido. Asegúrate de que el adaptador USB-TTL pueda suministrar al menos 500 mA.
- ⚠️ **Polaridad**: Verifica las conexiones TX ↔ RX cruzadas entre el adaptador y la ESP32-CAM.
- ⚠️ **GPIO 0**: No olvides conectar GPIO 0 a GND durante la programación y desconectarlo después.
- ⚠️ **Cámara OV2640**: No se utiliza en este proyecto, pero su presencia no interfiere con el LED de flash.
- 🔥 **El LED de flash puede calentarse**: El LED blanco es de alta potencia. No tocar directamente durante el funcionamiento prolongado.

## Archivos del proyecto

```
esp32cam-blink/
├── esp32cam-blink.ino   # Sketch principal
├── README.md            # Esta documentación
├── PLAN.md              # Plan de implementación
├── AUDIT_REPORT.md      # Informe de auditoría
├── .gitignore           # Exclusiones git
└── docs/
    ├── datasheet.md     # Documentación de usuario
    └── developer.md     # Documentación técnica del código
```

## Licencia

Proyecto educativo de código abierto.
