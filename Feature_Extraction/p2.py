# García Santoyo, Lissethe Alejandra 17110106
# Sistemas de visión artificial y procesamiento de imágenes
# Chapter 5:"Extrayendo características de una imagen"
# Archive: "programa_2_17110106.py"
# usaremos el algoritmo de deteción de esquinas "Harris Corner Detector". Un punto de esquina
# es donde ambos eigenvalores tendrían valores grandes.

# Detectando las esquinas de Shi-Tomasi.

import cv2
import numpy as np

img = cv2.imread('box1.jpg')
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

corners = cv2.goodFeaturesToTrack(gray, 7, 0.05, 25)
corners = np.float32(corners)

for item in corners:
    x, y = item[0]
    cv2.circle(img, (x,y), 5, 255, -1)
    

cv2.imshow("Equinas de Shi-Tomasi", img)
cv2.waitKey()
