import random
import string
print("\nBienvenidos al creador de contraseñas randoms :)")

longitud = int(input("Elige la longitud de la contraseña: "))

caracteres = string.ascii_letters + string.digits + string.ascii_letters
contraseña = "".join(random.choice(caracteres) for _ in range(longitud))
print(f"\nTu contraseña segura es: {contraseña}")
