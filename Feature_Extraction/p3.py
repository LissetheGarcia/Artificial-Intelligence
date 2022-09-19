# García Santoyo, Lissethe Alejandra 17110106
# Sistemas de visión artificial y procesamiento de imágenes
# Chapter 5:"Extrayendo características de una imagen"
# Archive: "programa_3_17110106.py"
# usaremos el algoritmo de deteción de esquinas "SIFT". Un punto de esquina
# es donde ambos eigenvalores tendrían valores grandes.

# SIFT algoritmo.

import cv2
import numpy as np

img = cv2.imread('station.jpg')
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

surf = cv2.xfeatures2d.SURF_create(15000)

# Esta delimitación controla el número de puntos clave
#surf.hessianThreshold = 15000

kp, des = surf.detectAndCompute(gray, None)

img = cv2.drawKeypoints(img, kp, None, (0, 255, 0), 4)

cv2.imshow("SURF características", img)
cv2.waitKey()