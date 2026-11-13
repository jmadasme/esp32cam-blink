# Referencias · ESP32-CAM Blink

Documentación externa que se usó para entender el hardware, los protocolos y las
libertades del proyecto. No es una bibliografía decorativa: cada enlace apunta a
la fuente que explica una decisión concreta.

## Fuentes técnicas

| Fuente | Para qué se consultó |
|---|---|
| [arduino-esp32](https://docs.espressif.com/projects/arduino-esp32/en/latest/) | Core Arduino para ESP32. |
| [Arduino Documentation](https://docs.arduino.cc/) | Referencia de placas, IDE y API. |

## Versiones de este repositorio

`esp32cam-blink`

Cada carpeta puede tener dependencias y versiones distintas. Cuando el código
depende de una versión específica, esa versión está declarada en el README o en
el archivo de configuración de la carpeta, no en este documento.

## Criterio de preservación

- El código y los documentos se copiaron desde la carpeta original de trabajo.
- Se excluyeron `.git`, dependencias instaladas, compilados, registros y bases
  de datos locales.
- Se redactaron tokens, claves privadas y contraseñas detectadas en texto.
- Las plantillas `.example`, `.sample` y los valores de demostración se
  conservan porque documentan la configuración esperada.

## Limitaciones conocidas

La ESP32-CAM falla por alimentación o por el modo de carga, pero es fácil culpar a la cámara o al código equivocado.

La documentación de cada versión describe el alcance real. Si una función no
está implementada, se dice; si un hardware no fue probado, también.
