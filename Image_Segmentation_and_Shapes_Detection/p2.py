# García Santoyo, Lissethe Alejandra 17110106
# Sistemas de visión artificial y procesamiento de imágenes
# Chapter 8:"Detectando formas y segmentando una imagen"
# Archive: "programa_2_17110106.py"

# Formas convexas

import sys

import cv2
import numpy as np

# La entrada es una imagen a color
def get_contours(img):
    # Convertimos la imagen a escala de grises
    img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    
    # Delimitamos la imagen de entrada
    ret, thresh = cv2.threshold(img_gray, 127, 255, 0)
    
    # Encontramos los contornos de la imagen
    contours, hierarchy = cv2.findContours(thresh, 2, 1)
    
    return contours

if __name__ == '__main__':
    img = cv2.imread('figs.png')
    
    # Iteramos sobre el extracto de contornos
    for contour in get_contours(img):
        # Extraemos las partes convexas del contorno
        hull = cv2.convexHull(contour, returnPoints = False)
        
        # Extraemo las partes con convexidad obtenidas en el paso anterior
        defects = cv2.convexityDefects(contour, hull)
        
        if defects is None:
            continue
        
        # Dibuja las líneas y círculos para mostrar los defectos
        for i in range(defects.shape[0]):
            start_defect, end_defect, far_defect, _ = defects[i, 0]
            start = tuple(contour[start_defect][0])
            end = tuple(contour[end_defect][0])
            far = tuple(contour[far_defect][0])
            cv2.circle(img, far, 5, (128, 0, 0), -1)
            cv2.drawContours(img, [contour], -1, (0, 0, 0), 3)
            
cv2.imshow('Defectos de convexidad', img)
cv2.waitKey(0)
cv2.destroyAllWindows()
    

