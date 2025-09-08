#include <WiFi.h>
#include <WebServer.h>  // Biblioteca WebServer para criar endpoints REST

// Configurações Wi-Fi
const char* ssid = "smart_city";
const char* password = "senai501";

// Pinos
const int ldrPin = 34;
const int ledVermelho = 14;
const int ledVerde = 25;
const int pirPin = 27;

// Servidor Web
WebServer server(80);

// Função para retornar dados dos sensores em JSON
void handleSensors() {
  int ldrValue = analogRead(ldrPin);
  float voltage = (ldrValue / 4095.0) * 3.3;
  bool salaClara = ldrValue < 1500;

  int pirRaw = digitalRead(pirPin);
  bool movimentoDetectado = (pirRaw == HIGH);

  // Controle dos LEDs
  if (salaClara) {
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledVermelho, LOW);
  } else {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledVermelho, HIGH);
  }

  // JSON
  String json = "{";
  json += "\"ldrValue\": " + String(ldrValue) + ",";
  json += "\"voltage\": " + String(voltage, 2) + ",";
  json += "\"luminosidade\": \"" + String(salaClara ? "CLARO" : "ESCURO") + "\",";
  json += "\"movimentoDetectado\": " + String(movimentoDetectado ? "true" : "false") + ",";
  json += "\"pirRaw\": " + String(pirRaw);
  json += "}";

  server.sendHeader("Access-Control-Allow-Origin", "*");

  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(115200);

  pinMode(ledVermelho, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(pirPin, INPUT);

  WiFi.begin(ssid, password);
  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi Conectado! IP: " + WiFi.localIP().toString());

  // Rota API
  server.on("/luminosidade", handleSensors);

  server.begin();
  Serial.println("Servidor iniciado.");
}

void loop() {
  server.handleClient();
}
