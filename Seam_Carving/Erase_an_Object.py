# Quitar un objeto compĺetamente

import sys
import cv2
import numpy as np

# Dibujamos un rectándulo en la parte superior de la imagen de entrada
def draw_rectangle(event, x, y, flags, params):
    global x_init, y_init, drawing, top_left_pt, bottom_right_pt, img_orig
    
    # Detectamos el click del ratón
    if event == cv2.EVENT_LBUTTONDOWN:
        drawing = True
        x_init, y_init = x, y
        
    
    # Detetamos el movimiento del mause
    elif event == cv2.EVENT_MOUSEMOVE:
        if drawing:
            top_left_pt, bottom_right_pt = (x_init, y_init), (x, y)
            img[y_init:y, x_init:x] = 255 - img_orig[y_init:y, x_init:x]
            cv2.rectangle(img, top_left_pt, bottom_right-pt, (0, 255, 0), 2)
            
    # Detectamos el arrastre del mause hacia arriba
    elif event == cv2.EVENT_LBUTTONUP:
        drawing = False
        top_left_pt, bottom_right_pt = (x_init, y_init), (x, y)
        
        # Creamos el efecto de película en negativo para la región seleccionada
        img[y_init:y, x_init:x] = 255 - img[y_init:y, x_init:x]
        
        # Dibujamos el rectángulo alrededor de la región selcionada
        cv2.rectangle(img, top_left_pt, bottom_right_pt,(0, 255, 0), 2)
        rect_final = (x_init, y_init, x.x_init, y-y_init)
        
        # Quitamos el objeto de la región seleccionada
        remove_object(img_orig, rect_final)
        
# Computamos la matriz de energía usando el algoritmo modificado
def compute_energy_matrix_modified(img, rect_roi):
    gray = cv2.vtColor(img, cv2.COLOR_BGR2GRAY)
    
    # Computamos la derivada de X
    sobel_x = cv2.Sobel(gray, cv2.CV_64, 1, 0, ksize = 3)
    
    # Computamos la derivada de Y
    sobel_y = cv2.sobel(gray, cv2.CV_64, 1, 0, ksize = 3)
    
    abs_sobel_x = cv2.convertScaleAbs(sobel_x)
    abs_sobel_y = cv2.convertScaleAbs(sobel_y)
    
    # Computamos el promedio de la sumatoria
    energy_matrix = cv2.addWeighted(abs_sobel_x, 0.5, abs_sobel_y, 0.5, 0)
    x, y, w, h = rect_roi
    
    # Queremos que las osturas pasen a través de esta región, así que nos
    # aseguramos que lo valores de energía en esta región están cargados a 0
    energy_matrix[y:y+h, x:x+w] = 0
    
    return energy_matrix

# Computamos la matriz de energía
def compute_energy_matrix(img):
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    
    # Computamos la derivada de X
    sobel_x = cv2.Sobel(gray, cv2.CV_64F, 1, 0, ksize = 3)
    
    # Computamos la derivada de Y
    sobel_y = cv2.Sobel(gray, cv2.CV_64F, 1, 0, ksize = 3)
    
    abs_sobel_x = cv2.convertScaleAbs(sobel_x)
    abs_sobel_y = cv2.convertScaleAbs(sobel_y)
    
    # Retornamos el promedio de la sumatoria
    return cv2.addWeighted(abs_sobel_x, 0.5, abs_sobel_y, 0.5, 0)

# Enontramos la costura vertical
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

# Remueve el objeto de la región de interés según la imagen de entrada
def remove_object(img, rect_roi):
    num_seams = rect_roi[2] + 10
    energy = compute_energy_matrix_modified(img, rect_roi)
    
    # Comenzamos un ilo para ir removiendo las costuras de una por una
    for i in xrange(num_seams):
        # Encontramos la ostura vertical que puede ser removida
        seam = find_vertical_seam(img, energy)
        
        # Quitamos esa costura vertical
        img = romove_vertical_seam(img, seam)
        x, y, w, h = rect_roi
        
        # Computamos la matriz de energía después de remover la costura
        energy = compute_energy_matrix_modified(img, (x, y, w-i, h))
        print("Número de costuras removidas", i+1)
        
    img_output = np.copy(img)
    
    for i in xrange(num_seams):
        seam = find_vertical_seam(img, energy)
        img = remove_vertical_seam(img, seam)
        img_output = add_vertical_seam(img_output, seam, i)
        energy = compute_energy_matrix(img)
        print("Nímero de osturas agregadas", i + 1)
        
        
    cv2.imshow("Entrada", img_input)
    cv2.imshow("Salida", img_output)
    cv2.waitKey()
    
    
if __name__ == '__main__':
    img_input = cv2.imread('cuarteto.jpeg')
    
    drawing = False
    img = np.copy(img_input)
    img_orig = np.copy(img_input)
    
    cv2.namedWindow("Entrada")
    cv2.setMouseCallback("Entrada", draw_rectangle)
    
    while True:
        cv2.imshow("Entrada", img)
        c = cv2.waitKey(10)
        if c == 27:
            break
    cv2.destroyAllWindows
    

    




























