# García Santoyo, Lissethe Alejandra 17110106
# Sistemas de visión artificial y procesamiento de imágenes
# Chapter 5:"Extrayendo características de una imagen"
# Archive: "programa_1_17110106.py"
# usaremos el algoritmo de deteción de esquinas "Harris Corner Detector". Un punto de esquina
# es donde ambos eigenvalores tendrían valores grandes.

# Detectando las esquinas.

import cv2
import numpy as np

img = cv2.imread('box1.jpg')
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

gray = np.float32(gray)

dst = cv2.cornerHarris(gray, 4, 5, 0.04) # Sólo para detectar esquinas filosas

# El resultado es dilatado para hacer las esquinas
dst = cv2.dilate(dst, None)

# Delimitamo para un valor óptimo, el ual deberá variar dependiendo de la imagen.
img[dst > 0.01 * dst.max()] = [0, 0, 0]

cv2.imshow("Equinas de Harris", img)
cv2.waitKey()



