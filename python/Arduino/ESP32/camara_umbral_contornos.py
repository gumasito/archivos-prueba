import cv2
import numpy as np

url = "rtsp://manita:LhJasYK3oc2WEce81T@192.168.100.152:554/stream1"
cap = cv2.VideoCapture(url)


while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        print("Error abriendo camara")
        break
    print(frame)
    print("holi")
    #t convertir colores
    #? cv2.cvtColor(frame,cv2.#COLOR_A_PONER)
    #? blur = cv2.GaussianBlur(frame,#cantidad_de_blur(5,5),#setear_valor_extra(0)(#0 para automatico))
    #? umbral(blanco y negro) _,thresh = cv2.threshold(frame,(borde_umbral)127,(si_pasan_blanco)255,cv2.THRESH_BINARY(metodo_conversion))(el "_" es para tomar valores que no se necesitan)
    #? cv2.dilate(frame, None, iterations=3) es para hacer crecer las zonas blancas en las imagenes, modificandolas y hacer parecer que se unen
    #? cv2.erode(imagen, None, iterations=3) Lo contrario a dilate
    #? 
    gris  = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
    __, frame_raro = cv2.threshold(gris, 127, 255, cv2.THRESH_BINARY)

    contours, _ = cv2.findContours(frame_raro, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

# Crear imagen negra para dibujar contornos
    contour_img = np.zeros_like(frame_raro)

# Dibujar todos los contornos en blanco
    cv2.drawContours(contour_img, contours, -1, (255), thickness=2)
    
    cv2.resize(frame_raro,(320,240))
    cv2.imshow("camara",contour_img)
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
cap.release()
cv2.destroyAllWindows()