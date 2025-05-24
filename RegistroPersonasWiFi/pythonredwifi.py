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
    puerto.close()
