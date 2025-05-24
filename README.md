# OpenWiFiControl
# Detección de Clientes mediante Red WiFi Abierta con ESP8266

![ESP8266](https://upload.wikimedia.org/wikipedia/commons/3/3f/ESP8266-01.jpg)

## 🔍 Descripción

Este proyecto utiliza un microcontrolador ESP8266 configurado como punto de acceso (Access Point) para detectar dispositivos con WiFi activado que se conectan a una red abierta. Una vez conectados, se recolecta información como la dirección MAC, IP asignada y tiempo de conexión. Estos datos se envían por puerto serie y son almacenados por un script Python en un archivo `.csv`, que actúa como base de datos local.

Es ideal para estrategias de marketing, estudios de tráfico de personas en locales, o como base para sistemas de conteo anónimo.

---

## 🧰 Requisitos

### 🖥️ Hardware:

* 📶 Placa ESP8266 (NodeMCU, Wemos D1 Mini, etc.)
* 🔌 Cable USB para programación

### 💻 Software:

* Arduino IDE
* Python 3.x
* Spyder, VSCode o cualquier editor Python

---

## ⚙️ Parte 1: Código para ESP8266

### 🛠️ Instalación del entorno:

1. Abrí Arduino IDE
2. Ir a `Archivo > Preferencias`
3. En "Gestor de URLs adicionales de tarjetas", agregá:

```
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```

4. Ir a `Herramientas > Placa > Gestor de placas`, buscá `esp8266` y hacé clic en instalar

### 🔌 Selección de placa y puerto:

* Placa: `NodeMCU 1.0 (ESP-12E Module)` o la que corresponda
* Puerto: Verificado en `Administrador de dispositivos > Puertos (COM)`

### 📥 Cargar el siguiente código:

```cpp
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
}// 
```

---

## 🐍 Parte 2: Recolector de datos en Python

### 📦 Instalación de dependencias:

```bash
pip install pyserial
```

### 🧾 Script Python: `pythonredwifi.py`

```python
import serial
import csv
import time
from datetime import datetime

# Configura el puerto serial (ajustá el nombre de COM según tu sistema)
puerto = serial.Serial('COM6', 115200, timeout=1)
time.sleep(2)  # Esperar al inicio

# Archivo CSV
archivo = open("registro_wifi.csv", mode="a", newline="")
writer = csv.writer(archivo)
writer.writerow(["Fecha", "Hora", "MAC", "IP", "Tiempo_conectado_seg"])

print("Escuchando datos desde ESP8266...")

try:
    while True:
        linea = puerto.readline().decode("utf-8").strip()
        if linea.startswith("DATA;"):
            partes = linea.split(";")
            if len(partes) == 4:
                now = datetime.now()
                fecha = now.strftime("%Y-%m-%d")
                hora = now.strftime("%H:%M:%S")
                mac = partes[1]
                ip = partes[2]
                tiempo = partes[3]

                writer.writerow([fecha, hora, mac, ip, tiempo])
                print(f"{fecha} {hora} -> MAC: {mac} | IP: {ip} | {tiempo} seg")
except KeyboardInterrupt:
    print("Interrumpido por el usuario.")
    archivo.close()
    puerto.close() # Código Python...
```

### ▶️ Ejecución

* Conectá la placa ESP8266 a tu PC
* Verificá el puerto COM correcto
* Ejecutá el script Python desde tu entorno o consola:

```bash
python recolector_datos_wifi_esp8266.py
```

---

## 📊 Resultados Esperados

Un archivo llamado `registro_wifi.csv` que contiene registros como estos:

| Fecha      | Hora     | MAC               | IP          | Tiempo\_conectado\_seg |
| ---------- | -------- | ----------------- | ----------- | ---------------------- |
| 2025-05-18 | 14:00:05 | 8A-F2-15-93-01-AC | 192.168.4.2 | 45                     |

---

## ⚠️ Consideraciones Finales

* ✅ Verificar siempre que el puerto serie esté disponible
* 📢 Informar a los clientes mediante carteles sobre la recolección pasiva de datos
* 🔐 Esta es una implementación educativa. Para uso en producción se requieren medidas de seguridad adicionales.

---

## 👤 Autor

**Kevin Alcalde**
