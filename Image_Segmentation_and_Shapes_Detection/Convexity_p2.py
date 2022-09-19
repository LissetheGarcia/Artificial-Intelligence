# Formas convexas parte 2

import sys

import cv2
import numpy as np

# La entrada es una imagen a color
def get_contours(img):
    img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    ret, thresh = cv2.threshold(img_gray, 127, 255, 0)
    contours, hierarchy = cv2.findContours(thresh, 2, 1)
    
    return contours

if __name__ == '__main__':
    img = cv2.imread('figs.png')
    
    # Iteramos sobre los contornos extraídos
    for contour in get_contours(img):
        orig_contour = contour
        epsilon = 0.01 * cv2.arcLength(contour, True)
        contour = cv2.approxPolyDP(contour, epsilon, True)
        
        # Extraemos el casco convexo y los defectos de convexidad
        hull = cv2.convexHull(contour, returnPoints = False)
        defects = cv2.convexityDefects(contour, hull)
        
        if defects is None:
            continue
        
        # Dibuja las líneas y círculos para mostrar los defetos
        for i in range(defects.shape[0]):
            start_defect, end_defect, far_defect, _ = defects[i, 0]
            start = tuple(contour[start_defect][0])
            end = tuple(contour[end_defect][0])
            far = tuple(contour[far_defect][0])
            cv2.circle(img, far, 7, (255, 0, 0), -1)
            cv2.drawContours(img, [orig_contour], -1, (0, 0, 0), 3)
            
cv2.imshow('Defectos de convexidad', img)
cv2.waitKey(0)
cv2.destroyAllWindows()
    

            