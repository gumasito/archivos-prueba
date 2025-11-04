import re
text= "La fecha es 14/11/2007 y el telefono es +54-3498-458-917"
pattern = r"\d{2}/\d{2}/\d{4}"
pattern2 = r"\W\d{2}\W\d{4}\W\d{3}\W\d{3}$"
replacement = "Fecha oculta"
new_text = re.sub(pattern,replacement,text) #.sub lo que hace es reemplazar valores, en este caso reemplaza "pattern (patron encontrado), por replacement ("Fecha oculta"), en el texto"
new_text2 = re.sub(pattern2, "Numero Oculto", new_text)
print(f"Texto modificado: {new_text2}")

#reemplazando todas las vocales por el asterisco

cadena = "hola como te va en esta noche de soledad?"
cadena_new = re.sub("[aeiou]", "*", cadena)
print(cadena_new)

email = "example@example.com"

pattern = "[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}" #Explicando :c
                                                            #"-" separa 
                                                            #% valida (no se que, pero valida)
                                                            #+, solo valida si encuentra "1" coinicidencia o mas, menos de "1", no
                                                            #{2,} dos digitos hasta cualquiera
result = re.match(pattern,email)

if result:
    print("El correo es valido")
else: print("El correo es invalido")

#direcciones URL validas

url = "text texto blah blah blah url a continuacion https://www.google.com"
pattern_url ="https?://[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}"#el "?" no busca coincidencias, o solo 1, si encuentra mas de 1, no las muestra
result_url = re.findall(pattern_url,url)
print(result_url)

texto_url= "el numero es +54 3498 458 917 y +54 3498 431 272"
patron_url = r"\+\d{2}\s\d{4}\s\d{3}\s\d{3}$"
apa = re.sub(patron_url,"(numero unknown)",texto_url)
print(apa)