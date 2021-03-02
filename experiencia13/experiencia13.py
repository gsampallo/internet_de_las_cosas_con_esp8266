import paho.mqtt.client as mqtt
import time

nombreArchivo = 'accesos.txt'

def on_connect(client, userdata, flags, rc):
    client.subscribe("PUERTA")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print(time.strftime("%d-%m-%Y %H:%M:%S",
                         time.localtime())+
                         " "+msg.topic+" "+
                         str(msg.payload))

    mensaje = str(msg.payload)
    horario = time.strftime("%d-%m-%Y %H:%M:%S", time.localtime())
    with open(nombreArchivo,'a') as file_object:
        file_object.write(horario)
        file_object.write(mensaje)
        file_object.write("\n")
    
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("iot.eclipse.org", 1883, 60)

client.loop_forever()