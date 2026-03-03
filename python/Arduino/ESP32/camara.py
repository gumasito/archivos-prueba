import cv2

url = "rtsp://manita:LhJasYK3oc2WEce81T@192.168.100.152:554/stream1"

cap = cv2.VideoCapture(url)

while True:
    ret, frame = cap.read()

    if not ret:
        print("No se pudo leer el stream")
        break

    cv2.imshow("Camara Tapo", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
