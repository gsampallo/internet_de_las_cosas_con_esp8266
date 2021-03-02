import pyowm
import datetime
import paho.mqtt.client as mqtt

api_key = 'su_apiKey' # Reemplazar por el API Key Propio

owm = pyowm.OWM(api_key)
observation = owm.weather_at_place('Corrientes,AR')
w = observation.get_weather()

sunrise_time = int(w.get_sunrise_time())
sunrise_str = datetime.datetime.fromtimestamp(sunrise_time).strftime('%H')
amanecer = int(sunrise_str)

anochecer = int(datetime.datetime.fromtimestamp(int(w.get_sunset_time())).strftime('%H'))

hora = datetime.datetime.now().hour
print("Hora actual",hora)
print("Amanecer",amanecer)
print("Anochecer",anochecer)

client = mqtt.Client()
client.connect("iot.eclipse.org")

if(hora >= amanecer and hora < anochecer):
    print("Off")
    client.publish("experiencia12", "Off")
else:
    print("On")
    client.publish("experiencia12", "On")

client.disconnect()
