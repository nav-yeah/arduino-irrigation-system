#include <DHT.h>

#define SOIL_PIN      A0
#define WATER_PIN     A1
#define LDR_PIN       A2
#define DHT_PIN       2
#define RELAY_PIN     7
#define DHT_TYPE      DHT11

DHT dht(DHT_PIN, DHT_TYPE);

const int SOIL_DRY   = 500;
const int WATER_LOW  = 200;
const int LIGHT_MIN  = 300;

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  dht.begin();
}

void loop() {
  int soil       = analogRead(SOIL_PIN);
  int water      = analogRead(WATER_PIN);
  int light      = analogRead(LDR_PIN);
  float temp     = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.print("Soil: ");     Serial.print(soil);
  Serial.print(" | Water: "); Serial.print(water);
  Serial.print(" | Light: "); Serial.print(light);
  Serial.print(" | Temp: ");  Serial.print(temp);
  Serial.print("C | Humidity: "); Serial.print(humidity);
  Serial.println("%");

  bool soilDry        = soil  > SOIL_DRY;
  bool waterAvailable = water > WATER_LOW;
  bool isDaytime      = light > LIGHT_MIN;

  if (soilDry && waterAvailable && isDaytime) {
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Pump: ON");
  } else {
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Pump: OFF");
  }

  delay(2000);
}
