import pyttsx3
from datetime import datetime
from zoneinfo import ZoneInfo
data = ZoneInfo("America/Argentina/Buenos_Aires")
hora = datetime.now(data)   
ahora = hora.strftime("Son las %H:%M del %d de %B de %Y")
print(ahora)
engine = pyttsx3.init()

engine.say(f"Hola, {ahora}")
engine.runAndWait()