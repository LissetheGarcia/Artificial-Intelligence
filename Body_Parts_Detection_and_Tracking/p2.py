# García Santoyo, Lissethe Alejandra 17110106
# Sistemas de visión artificial y procesamiento de imágenes
# Chapter 4:"Detectando y rastreando diferentes partes del cuerpo"
# Archive: "programa_2_17110106.py"
# OpenCV provee de un buen marco de referencia para la detección de rostros, sólo necesitamos
# cargar el archivo de cascada y usarlo para detectar caras en una imagen y posteriormente,
# montar alguna máscara.

# diversión con la detección de rostros

import cv2
import numpy as np

face_cascade = cv2.CascadeClassifier('/home/pi/opencv/opencv-4.1.2/data/haarcascades/haarcascade_frontalface_alt.xml')

face_mask = cv2.imread('skull.png')
#cv2.imshow('mask', face_mask)
h_mask, w_mask = face_mask.shape[:2]

if face_cascade.empty():
    raise IOError('No ha sido posible cargar el archivo clasificador de cascada xml')

cap = cv2.VideoCapture(-1)
scaling_factor = 1.0

while True:
    ret, frame = cap.read()
    frame = cv2.resize(frame, None, fx = scaling_factor, fy = scaling_factor, interpolation = cv2.INTER_AREA)
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    face_rects = face_cascade.detectMultiScale(gray, 1.3, 5, minSize=(30, 30), flags=cv2.CASCADE_SCALE_IMAGE)
    for (x, y, w, h) in face_rects:
        if h > 0 and w > 0:
            # Ajusta lo alto y lo ancho de los parámetros dependiendo de los tamaños y sus
            # localizaciones, se necesita estar probando con estos valores para aegurarse de que
            # se ha hecho bien
            h, w = int(1.4 * h), int(1.0 * w)
            y -= int(0.2 * h)
            
            # Extraemos la región de interés desde la imagen
            frame_roi = frame[y:y+h, x:x+w]
            face_mask_small = cv2.resize(face_mask, (w, h), interpolation = cv2.INTER_AREA)
            
            # Convertimos la imagen de color a escala de grises y la delimitamos
            gray_mask = cv2.cvtColor(face_mask_small, cv2.COLOR_BGR2GRAY)
            ret, mask = cv2.threshold(gray_mask, 180, 255, cv2.THRESH_BINARY_INV)
            
            # Creamos una máscara inversa
            mask_inv = cv2.bitwise_not(mask)
            
            # Usamos la máscara para extraer la región de la cara de interés
            masked_face = cv2.bitwise_and(face_mask_small, face_mask_small, mask = mask)
            
            # Usamos la máscara inversa para obtener la parte remanente de la imagen
            masked_frame = cv2.bitwise_and(frame_roi, frame_roi, mask = mask_inv)
            
            # Agregamos las 2 imágenes para obtener la salida final
            frame[y:y+h, x:x+w] = cv2.add(masked_face, masked_frame)
            
    cv2.imshow('Máscara',frame)
    c = cv2.waitKey(1)
    if c == 27:
        break
    
cap.release()
cv2.destroyAllWindows()