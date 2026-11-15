# ESP32-CAM Blink · ESP32-CAM · Blink

![Estado](https://img.shields.io/badge/estado-preservado-2A9D8F?style=flat-square)
![Versiones](https://img.shields.io/badge/versiones-1-457B9D?style=flat-square)
![Sección](https://img.shields.io/badge/sección-iot-5B7C99?style=flat-square)
![Licencia](https://img.shields.io/badge/licencia-MIT-06141b?style=flat-square)

> Un blink mínimo sobre la placa AI-Thinker con OV2640, para verificar alimentación y GPIO antes de pelear con video.

Este repositorio reúne **1 versión** de ESP32-CAM Blink en `versions/`.
Cada carpeta conserva el contenido original de su etapa, sin `.git`, dependencias
instaladas ni binarios pesados. La documentación de operación y de código está en
[`docs/`](docs/), y el sitio del proyecto en [`docs/index.html`](docs/index.html).

## Índice de versiones

| Versión | Qué aporta | Archivos |
|---|---|---:|
| [`esp32cam-blink`](versions/esp32cam-blink/) | Blink de GPIO4 a 1 segundo, pensado como prueba de bring-up de la ESP32-CAM. | 5 |

La versión de referencia de esta familia es **`esp32cam-blink`**: es la que se usa
para el README base y para los documentos canónicos. Las demás se mantienen
completas para que se pueda reconstruir la evolución y comparar decisiones.

## Arranque rápido

```bash
git clone https://github.com/jmadasme/esp32cam-blink.git
cd esp32cam-blink/versions/esp32cam-blink
arduino-cli compile --fqbn esp32:esp32:esp32cam .
```

Para cargar, GPIO0 debe estar a GND y la placa necesita una fuente de 5 V estable. El LED es GPIO4 en la AI-Thinker.

<!-- ficha -->
## Ficha de evaluación

**Madurez global: 3.2/5**

| Criterio | Nota | Evidencia |
|---|---:|---|
| Madurez | 1/5 | Un sketch de pocas decenas de líneas, sin estado, sensores ni manejo de errores. |
| Reproducibilidad | 5/5 | Sin dependencias externas; compila con el core ESP32 y el FQBN esp32cam declarado. |
| Documentación | 4/5 | Datasheet con consumos y pines, más guía de desarrollador con estructura del código y pruebas. |
| Honestidad de límites | 4/5 | Aclara que no usa la cámara y que el parpadeo no valida el sensor OV2640. |
| Valor demostrativo | 2/5 | Demuestra el bring-up y la toolchain de carga, con un alcance deliberadamente mínimo. |
| Facilidad de despliegue | 3/5 | Cargar exige adaptador USB-TTL y la secuencia GPIO0/RST; no hay auto-reset ni placa con puerto integrado. |

Prueba de bring-up correcta y honesta sobre su alcance: sirve para descartar alimentación y modo de carga antes de abordar la cámara o el video.

## Lo que no funcionó

### esp32cam-blink — Alimentación insuficiente

La placa consume unos 250 mA con el LED encendido y no debe alimentarse desde el pin de 3,3 V del adaptador USB-TTL. El datasheet indica usar la entrada de 5 V del regulador y una fuente estable, porque la caída de tensión es el fallo más habitual en esta placa.

### esp32cam-blink — Carga manual con GPIO0 y RST

El upload exige poner GPIO0 a GND, pulsar RST, cargar y volver a resetear sin ese puente. No hay auto-reset por USB, de modo que omitir la secuencia deja la placa en modo normal y el puerto no responde como se espera.

## Preguntas típicas

**¿Por qué no inicia la cámara?**

Este sketch no la usa. Su objetivo es probar la placa y la carga.

**¿Qué LED parpadea?**

El de flash, conectado a GPIO4 en la AI-Thinker.

**¿Puedo usar otra placa?**

Sí, cambiando el pin del LED y el FQBN.

**¿Necesito la cámara conectada?**

No para el blink.

**¿Es un proyecto educativo?**

Sí, es la primera práctica de la placa.

<!-- /ficha -->

## Documentación

- [`docs/datasheet.md`](docs/datasheet.md) — instalación, operación y límites.
- [`docs/developer.md`](docs/developer.md) — arquitectura, módulos y extensión.
- [`docs/REFERENCES.md`](docs/REFERENCES.md) — estándares, librerías y fuentes.
- [`docs/index.html`](docs/index.html) — página del proyecto (GitHub Pages).

## El proyecto en detalle

### ESP32-CAM Blink LED

Proyecto Arduino minimalista que hace parpadear el LED de flash blanco integrado (GPIO 4) de la placa **ESP32-CAM (AI-Thinker)** con un ciclo de 1 segundo encendido y 1 segundo apagado.

### Principio de funcionamiento

La ESP32-CAM AI-Thinker tiene un LED de flash blanco de alta intensidad montado en la PCB junto a la lente de la cámara OV2640. Este LED está conectado al GPIO 4 del ESP32 y es controlado mediante un transistor MOSFET de canal N que permite conmutarlo con la lógica de 3.3V del microcontrolador.

El sketch configura el GPIO 4 como salida digital y alterna su estado entre HIGH y LOW cada 1000 ms, generando un parpadeo continuo.

### Especificaciones técnicas

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

### Mapa de pines

| Pin    | Modo    | Conexión                         | Notas                                    |
|--------|---------|----------------------------------|------------------------------------------|
| GPIO 4 | OUTPUT  | LED Flash blanco integrado       | HIGH = encendido, LOW = apagado          |
| GPIO 1 | U0TXD   | TX del monitor serie             | Conectar al RX del adaptador USB-TTL     |
| GPIO 3 | U0RXD   | RX del monitor serie             | Conectar al TX del adaptador USB-TTL     |
| 5V     | POWER   | Alimentación 5V                  | Conectar al VCC del adaptador USB-TTL    |
| GND    | POWER   | Tierra común                     | Conectar al GND del adaptador USB-TTL    |
| GPIO 0 | INPUT   | Boot mode (programación)         | Conectar a GND durante el upload         |

### Diagrama de conexión

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

### Requisitos previos

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

### Instalación y uso

#### 1. Clonar o copiar los archivos

```bash
git clone <url-del-repositorio>
cd esp32cam-blink
```

#### 2. Compilar

```bash
arduino-cli compile --fqbn esp32:esp32:esp32cam esp32cam-blink.ino
```

#### 3. Subir a la placa

1. Conecta **GPIO 0 a GND** (modo programación).
2. Presiona el botón **RST** (reset) de la ESP32-CAM.
3. Ejecuta:
   ```bash
   arduino-cli upload -p /dev/ttyUSB0 --fqbn esp32:esp32:esp32cam esp32cam-blink.ino
   ```
4. Al finalizar, **desconecta GPIO 0 de GND** y presiona **RST** nuevamente.

#### 4. Verificar funcionamiento

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

### Calibración

No requiere calibración. Si se desea cambiar la velocidad de parpadeo, modificar la constante `BLINK_DELAY_MS` en `esp32cam-blink.ino`:

```cpp
const int BLINK_DELAY_MS = 500;  // Parpadeo más rápido (0.5 segundos)
```

### Advertencias

- ⚠️ **Alimentación**: La ESP32-CAM consume hasta ~300 mA con el LED encendido. Asegúrate de que el adaptador USB-TTL pueda suministrar al menos 500 mA.
- ⚠️ **Polaridad**: Verifica las conexiones TX ↔ RX cruzadas entre el adaptador y la ESP32-CAM.
- ⚠️ **GPIO 0**: No olvides conectar GPIO 0 a GND durante la programación y desconectarlo después.
- ⚠️ **Cámara OV2640**: No se utiliza en este proyecto, pero su presencia no interfiere con el LED de flash.
- 🔥 **El LED de flash puede calentarse**: El LED blanco es de alta potencia. No tocar directamente durante el funcionamiento prolongado.

### Archivos del proyecto

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

### Licencia

Proyecto educativo de código abierto.

---

Licencia MIT © 2026 jmadasme. Las versiones se publican como material de
referencia; los nombres de hardware y marcas pertenecen a sus respectivos dueños.
