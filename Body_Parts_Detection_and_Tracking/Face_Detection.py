# OpenCV provee de un buen marco de referencia para la detección de rostros, sólo necesitamos
# cargar el archivo de cascada y usarlo para detectar caras en una imagen.

# Detectando y rastreando rostros.

import cv2
import numpy as np

face_cascade = cv2.CascadeClassifier('/home/pi/opencv/opencv-4.1.2/data/haarcascades/haarcascade_frontalface_default.xml')
#face_cascade.empty()

cap = cv2.VideoCapture(-1)

scaling_factor = 1.0

while True:
    ret, frame = cap.read()
    frame = cv2.resize(frame, None, fx = scaling_factor, fy = scaling_factor, interpolation = cv2.INTER_AREA)
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    
    face_rects = face_cascade.detectMultiScale(gray, 1.3, 5, minSize=(30, 30), flags=cv2.CASCADE_SCALE_IMAGE) # detecta objetos de diferentes tamaños en la imagen de entrada
    for (x, y, w, h) in face_rects:
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 3)
        #roi_gray = gray[y:y + h, x:x + w]
        #roi_color = frame[y:y + h, x:x + w]
        
    cv2.imshow("Detector de rostros", frame)
    
    c = cv2.waitKey(1)
    if c == 27:
        break
    
#cv2.imshow('Frame', frame)    
cap.release()
cv2.destroyAllWindows()

