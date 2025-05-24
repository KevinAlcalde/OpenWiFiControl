#include <ESP8266WiFi.h>

struct Dispositivo {
  uint8_t mac[6];
  IPAddress ip;
  unsigned long tiempoInicio;
};

Dispositivo dispositivos[10];
int total = 0;

void setup() {
  Serial.begin(115200);
  WiFi.softAP("Red_Local_Publica"); // red sin contraseña
  Serial.println("Red WiFi abierta iniciada...");
}

void loop() {
  int cantidad = WiFi.softAPgetStationNum();
  struct station_info *lista = wifi_softap_get_station_info();
  struct station_info *estacion = lista;

  Serial.println("---- NUEVA LECTURA ----");
  Serial.print("Dispositivos conectados: ");
  Serial.println(cantidad);

  int index = 0;
  while (estacion != NULL && index < 10) {
    IPAddress ip = IPAddress((uint32_t)estacion->ip.addr);
    uint8_t* mac = estacion->bssid;

    // Mostrar en Serial
    Serial.print("MAC: ");
    for (int i = 0; i < 6; i++) {
      if (i > 0) Serial.print(":");
      Serial.print(mac[i], HEX);
    }

    Serial.print(" | IP: ");
    Serial.print(ip);
    Serial.print(" | Tiempo conectado (s): ");
    if (dispositivos[index].tiempoInicio == 0) {
      dispositivos[index].tiempoInicio = millis();
      dispositivos[index].ip = ip;
      memcpy(dispositivos[index].mac, mac, 6);
    }
    unsigned long tiempo = (millis() - dispositivos[index].tiempoInicio) / 1000;
    Serial.println(tiempo);

    // Enviar datos por serial para Python
    Serial.print("DATA;");
    for (int i = 0; i < 6; i++) {
      if (i > 0) Serial.print("-");
      Serial.print(mac[i], HEX);
    }
    Serial.print(";");
    Serial.print(ip);
    Serial.print(";");
    Serial.println(tiempo);

    estacion = STAILQ_NEXT(estacion, next);
    index++;
  }

  wifi_softap_free_station_info();
  delay(10000);
}
