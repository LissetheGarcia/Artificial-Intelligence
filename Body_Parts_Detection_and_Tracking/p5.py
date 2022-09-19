# García Santoyo, Lissethe Alejandra 17110106
# Sistemas de visión artificial y procesamiento de imágenes
# Chapter 4:"Detectando y rastreando diferentes partes del cuerpo"
# Archive: "programa_5_17110106.py"
# Un sistema robusto es más fácil de entrenar cuando se quirn detectar objetos o partes con
# características únicas, afortunadamente los elementos de la cara son así, en esta sección
# vamos a desarrollar un programa detector de orejas.

# Detectando orejas.

import cv2
import numpy as np

left_ear_cascade = cv2.CascadeClassifier('/home/pi/opencv/opencv_contrib-4.1.2/modules/face/data/cascades/haarcascade_mcs_leftear.xml')
right_ear_cascade = cv2.CascadeClassifier('/home/pi/opencv/opencv_contrib-4.1.2/modules/face/data/cascades/haarcascade_mcs_rightear.xml')

if left_ear_cascade.empty():
    raise IOError("No fue posible cargar los archivos xml haarcascade")

if right_ear_cascade.empty():
    raise IOError("No fue posible cargar los archivos xml haarcascade")

cap = cv2.VideoCapture(-1)
s_f = 1.0

while True:
    ret, frame = cap.read()
    frame = cv2.resize(frame, None, fx = s_f, fy = s_f, interpolation = cv2.INTER_AREA)
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    
    left_ear = left_ear_cascade.detectMultiScale(gray, 1.3, 5)
    right_ear = right_ear_cascade.detectMultiScale(gray, 1.3, 5)
    
    for (x, y, w, h) in left_ear:
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 3)
        
    for (x, y, w, h) in right_ear:
        cv2.rectangle(frame, (x, y), (x+w, y+h), (255, 0, 0), 3)
        
    cv2.imshow("Detector de orejas", frame)
    
    c = cv2.waitKey(1)
    if c == 27:
        break
    
cap.release()
cv2.destroyAllWindows()