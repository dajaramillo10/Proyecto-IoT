Este proyecto consiste en la implementación de un sistema IoT para la monitorización ambiental en la Reserva Natural Cerro Pinel en Florencia Caquetá. El código se encarga de recopilar datos de diversos sensores y enviarlos a la plataforma ThingSpeak para su análisis.

-Requisitos

Antes de ejecutar el código, asegúrate de tener instalados los siguientes componentes:

1. Arduino IDE

-Descarga e instala el Arduino IDE en tu computadora.
-Añade la placa ESP32 al Arduino IDE:
 -Ve a Archivo > Preferencias.
 -En el campo "Additional Board Manager URLs", añade https://dl.espressif.com/dl/package_esp32_index.json.
 -Luego, ve a Herramientas > Placa > Gestor de placas y busca "esp32" para instalarla.

2. Librerías Arduino

Asegúrate de instalar las siguientes librerías en el Arduino IDE:
-WiFi (por defecto en la instalación para ESP32).
-ThingSpeak (instalable desde el gestor de librerías).
-DHT sensor library (busca "DHT" en el gestor de librerías e instala la versión de Adafruit).

-Configuración

1. Conexión de sensores:

-Conecta los sensores de acuerdo con las definiciones de pines en el código:
 -DHT11: Pin 13.
 -Sensor de luz (TEMT6000): Pin 32.
 -Sensor de sonido: Pin 34.
 -Sensor de lluvia: Pin 35.
 -Higrómetro (humedad del suelo): Pin 33.

En este caso se definieron esos pines, si deseas usar otro pin simplemente haz el cambio.

2. Credenciales WiFi:

-Asegúrate de modificar las variables ssid y password en el código con los datos de tu red WiFi.
 
3. Plataforma ThingSpeak:

-Configura un canal en ThingSpeak y obtiene tu channelID y writeAPIKey.
-Reemplaza estos valores en el código antes de subirlo a la placa ESP32.

-Ejecución

1. Subir el código:

-Conecta tu ESP32 a la computadora y selecciona la placa y puerto correctos en el Arduino IDE.
-Sube el código a la ESP32.

2. Visualización de datos:

-Los datos de los sensores se enviarán automáticamente a tu canal de ThingSpeak. Puedes visualizar los datos en gráficos en tiempo real a través del panel de control de ThingSpeak.
