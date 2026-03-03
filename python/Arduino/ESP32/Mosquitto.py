import paho.mqtt.client as mqtt

broker = "192.168.100.85"
topic = "prueba/camara/movimiento"

client = mqtt.Client()
client.connect(broker,1883,60)

client.publish(topic,"Movimiento Detectado")
client.disconnect()