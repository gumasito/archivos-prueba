import cv2
import mediapipe as mp
from pyfirmata2 import Arduino
import time

# Conectar con el Arduino
# Inicializar MediaPipe
mp_hands = mp.solutions.hands
with mp_hands.Hands(max_num_hands = 1) as hands:
    mp_draw = mp.solutions.drawing_utils

    # Captura de cámara
    cap = cv2.VideoCapture(0)

    board = Arduino('COM9')  # Cambiá según tu puerto
    led_pin1 = 2
    led_pin2 = 3
    led_pin3 = 4
    led_pin4 = 5
    led_pin5 = 6
    time.sleep(1)


    def mano_abierta(landmarks):
        dedos_abiertos = 0
        # Detección simple para dedos (índice a meñique)
        tips = [8, 12, 16, 20]  # Índices de las puntas de los dedos

        for tip in tips:
            if landmarks[tip].y < landmarks[tip - 2].y:
                dedos_abiertos += 1
            # Pulgar (opcional, básico): tip 4 y su base tip 2
            if landmarks[4].x < landmarks[3].x:  # Mano derecha
                dedos_abiertos += 1
        return dedos_abiertos  # Mano abierta si hay al menos 4 dedos extendidos
    while cap.isOpened():
        ret, frame = cap.read()
        if not ret:
            print("No se pudo capturar el video")
            break

        img_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        results = hands.process(img_rgb)

        if results.multi_hand_landmarks:
            for hand_landmarks in results.multi_hand_landmarks:
                mp_draw.draw_landmarks(frame, hand_landmarks, mp_hands.HAND_CONNECTIONS)
                dedos = mano_abierta(hand_landmarks.landmark)
                if dedos == 1:
                    print("Un Dedo")
                    board.digital[led_pin1].write(1)
                    board.digital[led_pin3].write(0)
                    board.digital[led_pin2].write(0)
                    board.digital[led_pin4].write(0)
                    board.digital[led_pin5].write(0)
                elif dedos == 2:
                    print("Dos Dedos")
                    board.digital[led_pin1].write(1)
                    board.digital[led_pin2].write(1)
                    board.digital[led_pin3].write(0)
                    board.digital[led_pin4].write(0)
                    board.digital[led_pin5].write(0)
                elif dedos == 3:
                    print("Tres Dedos")
                    board.digital[led_pin1].write(1)
                    board.digital[led_pin2].write(1)
                    board.digital[led_pin3].write(1)
                    board.digital[led_pin4].write(0)
                    board.digital[led_pin5].write(0)
                elif dedos == 4:
                    print("Cuatro Dedos")
                    board.digital[led_pin1].write(1)
                    board.digital[led_pin2].write(1)
                    board.digital[led_pin3].write(1)
                    board.digital[led_pin4].write(1)
                    board.digital[led_pin5].write(0)
                elif dedos == 5:
                    print("Cinco Dedos")
                    board.digital[led_pin1].write(1)
                    board.digital[led_pin2].write(1)
                    board.digital[led_pin3].write(1)
                    board.digital[led_pin4].write(1)
                    board.digital[led_pin5].write(1)
                else:
                    print("Mano cerrada")
                    board.digital[led_pin1].write(0)
                    board.digital[led_pin2].write(0)
                    board.digital[led_pin3].write(0)
                    board.digital[led_pin4].write(0)
                    board.digital[led_pin5].write(0)

        cv2.imshow("Detección de Mano", frame)
        if cv2.waitKey(1) & 0xFF == 27:  # ESC para salir
            break
    print("Cerrando programa.")
    cap.release()
    cv2.destroyAllWindows()
    hands.close()