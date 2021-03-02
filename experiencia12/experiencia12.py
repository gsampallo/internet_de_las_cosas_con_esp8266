import datetime
import paho.mqtt.client as mqtt

client = mqtt.Client()
client.connect("iot.eclipse.org")

hora = datetime.datetime.now().hour

if(hora > 8 and hora < 20):
    
    print(hora,"Off")
    client.publish("experiencia12", "Off")
else:
    print(hora,"On")
    client.publish("experiencia12", "On")

client.disconnect()
