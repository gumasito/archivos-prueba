import cv2
import mediapipe as mp

mp_hands = mp.solutions.hands
mp_drawing = mp.solutions.drawing_utils

hands = mp_hands.Hands(
    static_image_mode=False,
    max_num_hands=2,
    min_detection_confidence=0.5,
    min_tracking_confidence=0.5
)

cap = cv2.VideoCapture(0)

while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        print("No se pudo capturar el video")
        break
    
    # Convertir a RGB (corrección del código original)
    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    result = hands.process(rgb_frame)

    if result.multi_hand_landmarks:
        for hand_landmarks in result.multi_hand_landmarks:
            mp_drawing.draw_landmarks(
                frame, hand_landmarks, mp_hands.HAND_CONNECTIONS
            )
            
            # Obtener coordenadas de los dedos
            thumb_tip = hand_landmarks.landmark[4]   # Punta del pulgar
            thumb_base = hand_landmarks.landmark[2]  # Base del pulgar
            
            # Comprobar si el pulgar está arriba
            if thumb_tip.y < thumb_base.y:  # La coordenada "y" menor significa más arriba
                cv2.putText(frame, "Pulgar arriba!", (50, 50), 
                            cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2, cv2.LINE_AA)

    cv2.imshow("Deteccion de manos", frame)

    if cv2.waitKey(1) & 0xFF == ord("q"):
        break

cap.release()
cv2.destroyAllWindows()
hands.close()
