#include <WiFi.h>
#include <ThingSpeak.h>
#include "DHT.h"

#define DHTPIN 13            //DHT11
#define DHTTYPE DHT11        // DHT 11
#define TEMT6000_PIN 32      // luminosidad
#define SOUND_SENSOR_PIN 34  //sonido
#define RAIN_SENSOR_PIN 35   // Sensor de lluvia
const int humsuelo = 33;  //Higrometro(humedad suelo)
int valHumsuelo;

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "CERRO PINEL";
const char* password = "Stefania26";

unsigned long channelID = 2429118;
const char* writeAPIKey = "2MH3XPTLWH70GCDH";

WiFiClient cliente;

void setup() {
  Serial.begin(115200);
  pinMode(humsuelo, INPUT);
  pinMode(TEMT6000_PIN, INPUT);
  pinMode(RAIN_SENSOR_PIN, INPUT);  // Sensor de lluvia como entrada
  delay(1000);

  Serial.println("Sensores Instalados y listos");
  dht.begin();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Conectado al WiFi");
  ThingSpeak.begin(cliente);
  delay(5000);
}

void loop() {
  delay(5000);
  medicion();

  if (ThingSpeak.writeFields(channelID, writeAPIKey) == 200) {
    Serial.println("Datos enviados a ThingSpeak!");
  } else {
    Serial.println("Error al enviar datos a ThingSpeak.");
  }

  delay(10000);
}

void medicion() {
  float temperatura = dht.readTemperature();
  float humedad = dht.readHumidity();

  valHumsuelo = map(analogRead(humsuelo), 4092, 0, 0, 100);                                                                                                                 



  float reading = analogRead(TEMT6000_PIN);  //Read light level
  Serial.print("Reading: ");
  Serial.println(reading);

  double volts = reading * 5.0 / 1024.0;
  Serial.print("Volts: ");
  Serial.println(volts);

  int soundValue = analogRead(SOUND_SENSOR_PIN);

  // Lectura del sensor de lluvia
  int valorLluvia = analogRead(RAIN_SENSOR_PIN);
  String estadoLluvia;
  if (valorLluvia > 950)
    estadoLluvia = "No hay lluvia";
  else if (valorLluvia <= 950 && valorLluvia > 600)
    estadoLluvia = "Llueve";
  else if (valorLluvia <= 600 && valorLluvia > 300)
    estadoLluvia = "Aguacero";
  else
    estadoLluvia = "Se inundó esto!";

  Serial.println("Estado del sensor de lluvia: " + estadoLluvia);

  Serial.print("Temperatura registrada: ");
  Serial.print(temperatura);
  Serial.println("°C");
  Serial.print("Humedad registrada: ");
  Serial.print(humedad);
  Serial.println("%");
  Serial.print("Humedad del suelo: ");
  Serial.print(valHumsuelo);
  Serial.println(" %");
  Serial.print("Lux: ");
  float lux2 = analogRead(TEMT6000_PIN) * 0.9765625;  // 1000 / 1024 = 0.9765625
  Serial.println(lux2);
  Serial.print("Valor del sensor de sonido: ");
  Serial.println(soundValue);
  Serial.println("");

  ThingSpeak.setField(1, temperatura);
  ThingSpeak.setField(2, humedad);
  ThingSpeak.setField(3, valHumsuelo);
  ThingSpeak.setField(4, lux2);
  ThingSpeak.setField(5, soundValue);
  ThingSpeak.setField(6, valorLluvia);
}
