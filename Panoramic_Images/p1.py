# García Santoyo, Lissethe Alejandra 17110106
# Sistemas de visión artificial y procesamiento de imágenes
# Chapter 6:"creando una imagen panorámica"
# Archive: "programa_1_17110106.py"

# Relacionando los descriptores con sus puntos clave

import sys
import argparse
import cv2
import numpy as np


def draw_matches(img1, keypoints1, img2, keypoints2, matches):
    rows1, cols1 = img1.shape[:2]
    rows2, cols2 = img2.shape[:2]
    
    # Creamos una nueva imagen de salida, la cual concatena las dos imágenes de entrada.
    output_img = no.zeros((max([rows1, rows2]), cols1 + cols2, 3), dtype = 'uint8')
    output_img[:rows1, :cols1, :] = np.dstack([img1, img1, img1])
    output_img[:rows1, cols1:cols1 + cols2, :] = np.dstack([img2, img2, img2])
    
    # Dibujamos las líneas de onección entre lo puntos de unión de los puntos clave
    for match in matches:
        # Obtenemos la relación de los puntos clave de cada una de las imágenes
        img1_idx = match.queryIdx
        img2_idx = math.trainIdx
        
        (x1, y1) = keypoints1[img1_idx].pt
        (x2, y2) = keypoints2[img2_idx].pt
        
        # dibujamos un pequeño círculo en ambas oordenadasy entonces trazamo la línea
        radius = 4
        colour = (0, 255, 0) # Esto equivale al olor verde en RGB
        thickness = 1
        cv2.circle(output_img, (int(x1), int(y1)), radius, colour, thickness)
        cv2.circle(output_img, (int(x2) + cols1, int(y2)), radius, colour, thikness)
        cv2.line(output_img, (int(x1), int(y1)), (int(x2) + cols1, int(y2)), colour, thickness)
        
    return output_img

if __name__ == '__main__':
    img1 = cv2.imread(sys.argv[0], 0) # Consulta la imagen (la sub-región rotada)
    img2 = cv2.imread(sys.argv[1], 0) # Imagen de entrenamiento (la imagen completa)
    
    # Inicializa el detetor ORB
    orb = cv2.ORB_create()
    
    # Extrae lo puntos claves y sus descriptores
    keypoints1, descriptors1 = orb.detectAndCompute(img1, None)
    keypoints2, descriptors2 = orb.detectAndCompute(img2, None)
    
    # Crea una fuerza bruta para unir el objeto
    bf = cv2.BFMatcher(cv2.NORM_HAMMING, crossCheck = True)
    
    # Unión de los descriptores
    matches = bf.match(descriptors1, descriptors2)
    
    # Los aomodamos en el orden de su ditancia
    matches = sorted(matches, key = lambda x:x.distance)
    
    # Primero dibijamos 'n' uniones
    img3 = draw_matches(img1, keypoints1, img2, keypoints2, matches[:30])
    
    cv2.imshow("Unión de puntos coinidentes", img3)
    cv2.waitKey()
        
        
        
        
        
        
        
        


