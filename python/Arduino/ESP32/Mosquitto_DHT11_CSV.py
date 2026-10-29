import paho.mqtt.client as mqtt
from datetime import datetime

def on_message(client, userdata, msg):
    data = msg.payload.decode()
    topic = msg.topic
    now = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    if (topic == "prueba/t"):
        with open("python\\Arduino\\ESP32\\dht11.csv", "a") as f:
            f.write("Temperatura recibida es de:")
            f.write(f"{now},{data}\n")
    elif (topic == "prueba/h"):
        with open("python\\Arduino\\ESP32\\dht11.csv", "a") as f:
            f.write("Humedad recibida es de:")
            f.write(f"{now},{data}\n")
    else:
        with open("python\\Arduino\\ESP32\\dht11.csv", "a") as f:
            f.write("Todo junto: ")
            f.write(f"{now},{data}\n")

client = mqtt.Client()
client.connect("192.168.100.85", 1883)
client.subscribe("prueba/dht21")
client.subscribe("prueba/t")
client.subscribe("prueba/h")
client.on_message = on_message
client.loop_forever()
