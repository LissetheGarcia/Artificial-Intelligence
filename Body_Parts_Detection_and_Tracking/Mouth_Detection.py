# Un sistema robusto es más fácil de entrenar cuando se quirn detectar objetos o partes con
# características únicas, afortunadamente los elementos de la cara son así, en esta sección
# vamos a desarrollar un programa detector de bocas

# Detectando bocas.

import cv2
import numpy as np

mouth = cv2.CascadeClassifier('/home/pi/opencv/opencv_contrib-4.1.2/modules/face/data/cascades/haarcascade_mcs_mouth.xml')

if mouth.empty():
    raise IOError("No fue enconytrado el archivo xml haarcascades")

cap = cv2.VideoCapture(-1)
s_f = 1.0

while True:
    ret, frame = cap.read()
    frame = cv2.resize(frame, None, fx = s_f, fy = s_f, interpolation = cv2.INTER_AREA)
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    
    mouth_rects = mouth.detectMultiScale(gray, 1.7, 11)
    for (x, y, w, h) in mouth_rects:
        y = int(y - 0.15 * h)
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 3)
        
    cv2.imshow("Detector de bocas", frame)
    
    c = cv2.waitKey(1)
    if c == 27:
        break
    
cap.release()
cv2.destroyAllWindows()
    
