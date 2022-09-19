# García Santoyo, Lissethe Alejandra 17110106
# Sistemas de visión artificial y procesamiento de imágenes
# Chapter 4:"Detectando y rastreando diferentes partes del cuerpo"
# Archive: "programa_8_17110106.py"
# Un sistema robusto es más fácil de entrenar cuando se quiren detectar objetos o partes con
# características únicas, afortunadamente los elementos de la cara son así, en esta sección
# vamos a desarrollar un programa detector de narices.

# Detectando una nariz.

import cv2
import numpy as np

nose = cv2.CascadeClassifier('/home/pi/opencv/opencv_contrib-4.1.2/modules/face/data/cascades/haarcascade_mcs_nose.xml')

if nose.empty():
    raise IOError("No fue encontrado el archivo xml haarcascades")

cap = cv2.VideoCapture(-1)
s_f = 1.0

while True:
    ret, frame = cap.read()
    frame = cv2.resize(frame, None, fx = s_f, fy = s_f, interpolation = cv2.INTER_AREA)
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    
    nose_rects = nose.detectMultiScale(gray, 1.3, 5)
    for (x, y, w, h) in nose_rects:
        y = int(y - 0.15 * h)
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 3)
        
    cv2.imshow("Detector de nariz", frame)
    
    c = cv2.waitKey(1)
    if c == 27:
        break
    
cap.release()
cv2.destroyAllWindows()