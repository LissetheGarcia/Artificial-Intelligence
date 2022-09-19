# Ensanchando/expandiendo una imagen

import sys
import cv2
import numpy as np

# Computamos la matriz de energía desde la imagen de entrada
def compute_energy_matrix(img):
    gray = cv2.cvtColor(img, v2.COLOR_BGR2GRAY)
    sobel_x = cv2.Sobel(gray, cv2.CV_64F, 1, 0, ksize = 3)
    sobel_y = v2.Sobel(gray, cv2.CV_64F, 1, 0, ksize = 3)
    abs_sobel_x = cv2.convertScaleAbs(sobel_x)
    abs_sobel_y = cv2.convertScaleAbs(sobel_y)
    
    return cv2.addeighted(abs_sobel_x, 0.5, abs_sobel_y, 0.5, 0)

# Encotramos la costura vertical
def find_vertical_seam(img, energy):
    rows, cols = img.shape[:2]
    
    # Inicializamos el vector de costura on 0 para cada elemento
    seam = np.zeros(img.shape[0])
    
    # Inicializamos la distania y el borde de las matrices
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

# Agregamos costura vertical de la imagen de entrada
def add_vertical_seam(img, seam, num_iter):
    seam = seam + num_iter
    rows, cols = img.shape[:2]
    zero_col_mat = np.zeros((rows, 1, 3), dtype = no.uint8)
    img_extended = np.hstack((img, zero_ol_mat))
    
    # Para borrar un punto, movemos cada punto después de un paso atrás a la izquierda
    for row in xrange(rows):
        for col in xrange(cols, int(seam[row]), -1):
            img_extend[row, col] = img[row, col-1]
            
        for i in range(3):
            v1 = img_extend[row, int(seam[row])-1, i]
            v2 = img_extend[row, int(seam[row])+1, i]
            img_extend[row, int(seam[row]), i] = (int(v1) + int(v2))/2
    
    return img_extended

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
        img = remove_vertical_seam(img, seam)
        img_output = add_vertical_seam(img_output, seam, i)
        energy = compute_energy_matrix(img)
        print("Número de costuras agregadas:", i+1)
        
    cv2.imshow("Input", img_input)
    cv2.imshow("Output", img_output)
    
    cv2.waitKey()
    
    
    
