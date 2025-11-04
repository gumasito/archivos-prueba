import cv2
import mediapipe as mp
import pygame

mp_hands = mp.solutions.hands
mp_draw = mp.solutions.drawing_utils
pygame.mixer.init()
sounds = [
    pygame.mixer.Sound("/python/Mediapipe/#do.WAV"),    
    pygame.mixer.Sound("/python/Mediapipe/#fa.WAV"),   
    pygame.mixer.Sound("/python/Mediapipe/#sol.WAV")    
]
def dedos_abajo(punto,punta,base):
    return punto[punta].y > punto[base].y
cap = cv2.VideoCapture(0)
with mp_hands.Hands(max_num_hands = 1, min_detection_confidence = .5, min_tracking_confidence = .5) as hands:
    finger_state = [False] * 3
    while cap.isOpened():
        ret,frame = cap.read()
        if not ret: break
        frame = cv2.flip(frame,1)
        rgb_frame = cv2.cvtColor(frame , cv2.COLOR_BGR2RGB)
        results = hands.process(rgb_frame)
        if results.multi_hand_landmarks:
            for h,result in enumerate(results.multi_hand_landmarks):
                mp_draw.draw_landmarks(frame,result,mp_hands.HAND_CONNECTIONS)
                puntas = [8,12,16]
                bases = [5,9,13]
                for i in range(3):
                    dedo_indice = i + h * 3
                    if dedos_abajo(result.landmark,puntas[i],bases[i]):
                        if not finger_state[dedo_indice]:
                            sounds[dedo_indice].play()
                            finger_state[dedo_indice] = True
                    else: finger_state[dedo_indice] = False
        cv2.imshow("Hand Detection",frame)
        if cv2.waitKey(1) & 0xFF == 27:
            break
cap.release()
cv2.destroyAllWindows()
pygame.quit()