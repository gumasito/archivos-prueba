from datetime import datetime 
print("\nCalculadora de edad")

año_actual = datetime.now().year #datetime.now() saca la fecha exacta de este momento (dia,mes,año,segundo, minuto y hora)

año_nacimiento = int(input("En que año naciste? "))

edad= año_actual - año_nacimiento

print(f"Tu edad es... {edad}")

