# FAST(Features From Accelerated Segment Test).

import cv2
import numpy as np

gray_img = cv2.imread('herramienta.jpg', 0)

fast = cv2.FastFeatureDetector_create()

# Detecta los puntos clave
keypoints = fast.detect(gray_img, None)
print ("Número de puntos claves sin una supresión máxima", len(keypoints))

# dibuja los puntos claves en la superficie de la imagen de entrada
img_keypoints_with_nonmax = cv2.drawKeypoints(gray_img, keypoints, np.array([]), (0, 0, 255), cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
cv2.imshow("FAST keypoints - with non max suppression", img_keypoints_with_nonmax)

# Detecta los puntos clave nuevamente
keypoints = fast.detect(gray_img, None)
print ("Número de puntos claves sin una supresión máxima: ", len(keypoints))

# dibuja los puntos claves en la superficie de la imagen de entrada
img_keypoints_without_nonmax = cv2.drawKeypoints(gray_img, keypoints, np.array([]), (0, 0, 255), cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
cv2.imshow("FAST keypoints - without non max suppression", img_keypoints_without_nonmax)

cv2.waitKey()




