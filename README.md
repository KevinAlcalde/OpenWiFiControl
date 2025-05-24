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
// Código completo para ESP8266...
```

---

## 🐍 Parte 2: Recolector de datos en Python

### 📦 Instalación de dependencias:

```bash
pip install pyserial
```

### 🧾 Script Python: `pythonredwifi.py`

```python
# Código Python...
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
