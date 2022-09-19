# García Santoyo, Lissethe Alejandra 17110106
# Sistemas de visión artificial y procesamiento de imágenes
# Chapter 8:"Detectando formas y segmentando una imagen"
# Archive: "programa_1_17110106.py"

# Análisis de contornos y relación de tamaños

import sys

import cv2
import numpy as np



# Extraemos la referencia del contorno de la imagen de entrada
def get_ref_contour(img):
    ref_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    ret, thresh = cv2.threshold(ref_gray, 127, 255, 0)
    
    # Encontramos todos los contornos en la imagen limitada
    # para el segundo y tercer parámetros están restringidos a
    # un cierto número de valores posibles
    contours, hierarchy = cv2.findContours(thresh, 1, 2)
    
    # Extraemos los contornos relevantes en base al radio de área
    # Utilizamos el radio de área porque el límite de contorno de la
    # imagen principal es extraída también y no queremos eso
    # Con esto se asegurará que sólo estamos extrayendo el contorno
    # dentro de la imagen
    for contour in contours:
        area = cv2.contourArea(contour)
        img_area = img.shape[0] * img.shape[1]
        if 0.05 < area / float(img_area) < 0.8:
            return contour
        
# Extraemos todos los contornos de la imagen
def get_all_contours(img):
    ref_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    ret, thresh = cv2.threshold(ref_gray, 127, 255, 0)
    contours, hierarchy = cv2.findContours(thresh, 1, 2)
    return contours

if __name__ == '__main__':
    # Reference image
    img1 = cv2.imread('st.jpg')
    
    # La imagen de entrada contiene todas las diferentes formas
    img2 = cv2.imread('sh.jpg')
    
    # Extraemos el contorno de referencia
    ref_contour = get_ref_contour(img1)
    
    # Extraemos todos los contornos de la imagen de entrada
    input_contours = get_all_contours(img2)
    
    closest_contour = input_contours[0]
    min_dist = sys.maxsize
    
    # Encontramos el contorno más cercano
    for contour in input_contours:
        # Unimos las formas y tomamos la más cercana
        ret = cv2.matchShapes(ref_contour, contour, 1, 0.0)
        if ret < min_dist:
            min_dist = ret
            closest_contour = contour
            
cv2.drawContours(img2, [closest_contour], -1, (0, 0, 0), 3)
cv2.imshow('Salida', img2)
cv2.waitKey()
    