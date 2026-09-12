#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>

// Pin definitions
#define PH_PIN A0
#define TURBIDITY_PIN A1
#define ONE_WIRE_BUS 2
#define LED_GREEN 10
#define LED_YELLOW 9
#define LED_RED 8

// OneWire for temperature sensor
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// SoftwareSerial for ESP32 comms
SoftwareSerial espSerial(3, 4); // RX=3 (from ESP32 TX2), TX=4 (to ESP32 RX2 via divider)

void setup() {
  Serial.begin(9600);       // Debug monitor
  espSerial.begin(9600);    // Link to ESP32
  sensors.begin();

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  Serial.println("Arduino UNO started...");
}

void loop() {
  // --- pH Sensor ---
  int phValue = analogRead(PH_PIN);
  float voltagePH = phValue * (5.0 / 1023.0);
  float pH = (7 + ((2.5 - voltagePH) / 0.18))-4; // calibration formula

  // --- Turbidity Sensor ---
  int turbidityValue = analogRead(TURBIDITY_PIN);
  float voltageTurb = turbidityValue * (5.0 / 1023.0);
  float turbidity = (voltageTurb * 100) * 0.5; // approximate NTU conversion

  // --- Temperature Sensor ---
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);

  // Debug prints
  Serial.print("pH: "); Serial.println(pH);
  Serial.print("Turbidity: "); Serial.println(turbidity);
  Serial.print("Temperature: "); Serial.println(temperature);

  // --- LED Logic ---
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);

if ((pH >= 6.5 && pH <= 8.5) && turbidity <= 55) {
  digitalWrite(LED_GREEN, HIGH);
} else if (((pH < 6.5 || pH > 8.5) && (pH >= 6.0 && pH <= 9.0)) ||
           (turbidity > 55 && turbidity <= 95)) {
  digitalWrite(LED_YELLOW, HIGH);
} else {
  digitalWrite(LED_RED, HIGH);
}

  // --- Send JSON to ESP32 ---
  String json = "{\"pH\":" + String(pH, 2) +
                ",\"turbidity\":" + String(turbidity, 2) +
                ",\"temperature\":" + String(temperature, 2) + "}";

  Serial.println("Sending JSON: " + json);
  espSerial.println(json); // Send to ESP32

  delay(2000);
}


