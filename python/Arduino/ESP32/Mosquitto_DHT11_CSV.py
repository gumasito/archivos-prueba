import paho.mqtt.client as mqtt
from datetime import datetime

def on_message(client, userdata, msg):
    data = msg.payload.decode()
    now = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    with open("python\\Arduino\\ESP32\\dht11.csv", "a") as f:
        f.write(f"{now},{data}\n")

client = mqtt.Client()
client.connect("192.168.100.85", 1883)
client.subscribe("prueba/dht21")
client.on_message = on_message

client.loop_forever()
