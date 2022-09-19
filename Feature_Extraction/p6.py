# García Santoyo, Lissethe Alejandra 17110106
# Sistemas de visión artificial y procesamiento de imágenes
# Chapter 5:"Extrayendo características de una imagen"
# Archive: "programa_6_17110106.py"


# ORB (Oriented FAST and rotated BRIEF)

import cv2
import numpy as np

input_img = cv2.imread('station.jpg')
gray_img = cv2.cvtColor(input_img, cv2.COLOR_BGR2GRAY)

# Importando las características ORB
orb = cv2.ORB_create()

# Encuentra los puntos claves con ORB
keypoints = orb.detect(gray_img, None)

# Computa los descriptores on ORB
keypoints, descriptors = orb.compute(gray_img, keypoints)

# Dibuja solo las ubicaiones de los puntos clave sin tamaño u orientación
final_keypoints = cv2.drawKeypoints(gray_img, keypoints, np.array([]), (0, 0, 255), cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)

cv2.imshow("ORB Keypoints", final_keypoints)
cv2.waitKey()