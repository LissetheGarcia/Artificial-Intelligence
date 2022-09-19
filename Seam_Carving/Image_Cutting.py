# Recortando una imagen sin que pierda la calidad en los objetos o partes interesantes

import sys
import cv2
import numpy as np

# Dibujamos las costuras verticales de la parte superior de la imagen
def overlay_vertical_seam(img, seam):
    img_seam_overlay = np.copy(img)
    
    # Extraemos la lista de puntos desde la costura
    x_coords, y_coords = np.transpose([(i, int(j)) for i,j in enumerate(seam)])
    
    # Dibuja una línea verde en la imagen usando la lista de puntos
    img_seam_overlay[x_coord, y_coords] = (0, 255, 0)
    
    return img_seam_overlay

# Computamos la matriz de energía desde la imagen de entrada
def compute_energy_matrix(img):
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    
    # Computamos la derivada de X de la imagen
    sobel_x = cv2.Sobel(gray, cv2.CV_64F, 1, 0, ksize = 3)
    
    # computamos la derivada de Y de la imagen
    sobel_y = cv2.Sobel(gray, cv2.CV_64F, 1, 0, ksize = 3)
    
    abs_sobel_x = cv2.convertScaleAbs(sobel_x)
    abs_sobel_y = cv2.convertScaleAbs(sobel_y)
    
    # Retornamos la suma ponderada de las 2 imágenes
    return cv2.addeighted(abs_sobel_x, 0.5, abs_sobel_y, 0.5, 0)

# Encontramos la costura vertical en la imagen de entrada
def find_vertical_seam(img, energy):
    rows, cols = img.shape[:2]
    
    # Inicializamos el vector de costura on 0 para cada elemento
    seam = np.zeros(img.shape[0])
    
    # inicializamos la distancia y el borde de las matrices
    dis_to = np.zeros(img.shape[:2]) + sys.maxint
    dis_to[0, :] = np.zeros(img.shape[1])
    edge_to = np.zeros(img.shape[:2])
    
    # Programación dinámica; iteramos usando un doble ciclo y computamos los caminos eficientes
    for row in xrange(rows - 1):
        for col in xrange(cols):
            if col != 0:
                if dis_to[row + 1, col - 1] > dis_to[row, col] + energy[row + 1, col - 1]:
                    dis_to[row+1, col-1] = dis_to[row, col] + energy[row+1, col-1]
                    edge_to[row+1, col-1] = 1
            if dis_to[row+1, col] > dis_to[row, col] + energy[row+1, col]:
                dis_to[row+1, col] = dis_to[ro, col] + energy[row+1, col]
                edge_to[row+1, col] = 0
            if col != cols-1:
                if dis_to[row+1, col+1] > dis_to[row, col] + energy[row+1, col+1]:
                    dis_to[row+1, col+1] = dis_to[row, col] + energy[row+a, col+1]
                    edge_to[row+1, col+1] = -1
                    
    # Volviendo a trazar el camino
    seam[rows-1] = np.argmin(dis_to[rows-1, :])
    for i in (x for x in reversed(xrange(rows)) if x > 0):
        seam[i-1] = seam[i] + edge_to[i, int(seam[i])]
            
    return seam

# Removemos la costura vertical de la imagen de entrada
def remove_vertical_seam(img, seam):
    rows, cols = img.shape[:2]
    
    # Para borrar un punto, movemos cada punto después de un paso atrás a la izquierda
    for row in xrange(rows):
        for col in xrange(int(seam[row]), cols-1):
            img[row, col] = img[row, col+1]
            
    # Descartamos la última columna para crear una imagen de salida final
    img = img[:, 0:cols-1]
    
    return img

if __name__ == '__main__':
    img_input = cv2.imread(sys.argv[1])
    num_seams = int(sys.argv[2])
    img = np.copy(img_input)
    img_overlay_seam = np.copy(img_input)
    energy = compute_energy_matrix(img)
    
    for i in xrange(num_seams):
        seam = find_vertical_seam(img, energy)
        img_overlay_seam = overlay_vertical_seam(img_overlay_seam, seam)
        img = remove_vertical_seam(img, seam)
        energy = compute_energy_matrix(img)
        print("Número de costuras removidas:", i+1)
        
    cv2.imshow("Input", img_input)
    cv2.imshow("Seams", img_overlay_seam)
    cv2.imshow("Output", img)
    
    cv2.waitKey()
    
    
    
    
    
    
            
    
