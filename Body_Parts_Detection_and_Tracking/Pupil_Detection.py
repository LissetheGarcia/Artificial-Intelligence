# Un sistema robusto es más fácil de entrenar cuando se quiren detectar objetos o partes con
# características únicas, afortunadamente los elementos de la cara son así, en esta sección
# vamos a desarrollar un programa detector de pupilas.

# Detector de pupilas

import math

import cv2
import numpy as np

img = cv2.imread('input1.jpg')
s_f = 0.7

img = cv2.resize(img, None, fx = s_f, fy = s_f, interpolation = cv2.INTER_AREA)
cv2.imshow("Imagen de entrada", img)
gray = cv2.cvtColor(-img, cv2.COLOR_BGR2GRAY)

ret, thresh_gray = cv2.threshold(gray, 220, 255, cv2.THRESH_BINARY_INV)
countours, hierarchy = cv2.findContours(thresh_gray, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)

for countour in countours:
    area = cv2.contourArea(countour)
    rect = cv2.boundingRect(countour)
    x, y, width, height = rect
    radius = 0.25 * (width + height)
    
    area_condition = (100 <= area <= 200)
    symmetry_condition = (abs(1 - float(width)/float(height)) <= 0.2)
    
    fill_condition = (abs(1 - (area / math.pi * math.pow(radius, 2.0))) <= 0.3)
    
    if area_condition and symmetry_condition and fill_condition:
        cv2.circle(img, int(x + radius), int(y + radius), int(1.3 * radius), (0, 180, 0), -1)
        
cv2.imshow("Detector de pupilas", img)
    
cv2.waitKey()
cv2.destroyAllWindows()
    
