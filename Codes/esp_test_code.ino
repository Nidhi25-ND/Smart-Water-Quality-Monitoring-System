#include <WiFi.h>
#include <HTTPClient.h>
#include <WebServer.h>

// WiFi credentials
const char* ssid = "Redmi Note 13 Pro+ 5G";
const char* password = "ShinChan";

// ThingSpeak API
String apiKey = "R3Y234WMJS2POPEU";
const char* server = "http://api.thingspeak.com/update";

// Web server
WebServer webServer(80);

// Serial from Arduino
HardwareSerial mySerial(2); // UART2

// Sensor values
String pH = "0";
String turbidity = "0";
String temperature = "0";

void handleRoot() {
  String html = "<!DOCTYPE html><html><head><meta http-equiv='refresh' content='5'>";
  html += "<title>Water Quality Dashboard</title></head><body>";
  html += "<h1>Smart Water Quality Monitoring</h1>";
  html += "<p><b>pH:</b> " + pH + "</p>";
  html += "<p><b>Turbidity (NTU):</b> " + turbidity + "</p>";
  html += "<p><b>Temperature (°C):</b> " + temperature + "</p>";
  html += "</body></html>";
  webServer.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600, SERIAL_8N1, 16, 17); // RX2=16, TX2=17

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");

  Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.localIP()); // ✅ Shows IP in Serial Monitor

  // Start web server
  webServer.on("/", handleRoot);
  webServer.begin();
  Serial.println("Web server started");
}

void loop() {
  webServer.handleClient();

  // Show IP address every 10 seconds
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 10000) {
    Serial.print("ESP32 IP address: ");
    Serial.println(WiFi.localIP());
    lastPrint = millis();
  }

  if (mySerial.available()) {
    String data = mySerial.readStringUntil('\n');
    Serial.println("Received: " + data);

    // Parse JSON manually
    int phIndex = data.indexOf("\"pH\":");
    int turbIndex = data.indexOf("\"turbidity\":");
    int tempIndex = data.indexOf("\"temperature\":");

    if (phIndex != -1 && turbIndex != -1 && tempIndex != -1) {
      pH = data.substring(phIndex + 5, data.indexOf(",", phIndex));
      turbidity = data.substring(turbIndex + 12, data.indexOf(",", turbIndex));
      temperature = data.substring(tempIndex + 13, data.indexOf("}", tempIndex));
    }

    // Send to ThingSpeak
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      String url = String(server) + "?api_key=" + apiKey +
                   "&field1=" + pH +
                   "&field2=" + turbidity +
                   "&field3=" + temperature;
      http.begin(url);
      int httpCode = http.GET();
      if (httpCode > 0) {
        Serial.println("ThingSpeak response: " + String(httpCode));
      } else {
        Serial.println("Error sending data");
      }
      http.end();
    }
  }
}

