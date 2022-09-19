# García Santoyo, Lissethe Alejandra 17110106
# Sistemas de visión artificial y procesamiento de imágenes
# Chapter 3:"Cartoonizing an image"
# Archive: "programa_5_17110106.py"
# Ahora que sabemos manipular la webcam a través de de entradas por medio del teclado o del
# mouse, vamos a ver cómo convertir una imagen en caricatura bicromática o a color.

# Caracaturizando una imagen.

import cv2
import numpy as np

def cartoonize_img(img, ds_factor = 4, sketch_mode = False):
    # Convertimos la imagen a escala de grises
    img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    
    # Aplicando el filtro median para la imagen en ecala de grises
    img_gray = cv2.medianBlur(img_gray, 7)
    
    # Detectamos las esquinas de la imagen y la delimitamos
    edges = cv2.Laplacian(img_gray, cv2.CV_8U, ksize = 5)
    ret, mask = cv2.threshold(edges, 100, 255, cv2.THRESH_BINARY_INV)
    
    # 'Mask' es el bosquejo de la imagen
    if sketch_mode:
        return cv2.cvtColor(mask, cv2.COLOR_GRAY2BGR)
    
    # Redimensiona la imagen a una menor para una computación más rápida
    img_small = cv2.resize(img, None, fx = 1.0/ds_factor, fy = 1.0/ds_factor, interpolation = cv2.INTER_AREA)
    num_repetitions = 10
    sigma_color = 5
    sigma_space = 7
    size = 5
    
    # Aplicamos filtro bilateral a la imagen múltiples veces
    for i in range(num_repetitions):
        img_small = cv2.bilateralFilter(img_small, size, sigma_color, sigma_space)
        img_output = cv2.resize(img_small, None, fx = ds_factor, fy = ds_factor, interpolation = cv2.INTER_AREA)
        
    dst = np.zeros(img_gray.shape)
    
    # agreamos las líneas de contorno gruesasa la imagen usando el operador 'and'
    dst = cv2.bitwise_and(img_output, img_output, mask = mask)
    return dst

if __name__ == '__main__':
    cap = cv2.VideoCapture(-1)
    
    cur_char = -1
    prev_char = -1
    
    while True:
        ret, frame = cap.read()
        frame = cv2.resize(frame, None, fx = 1.0, fy = 1.0, interpolation = cv2.INTER_AREA)
        
        c = cv2.waitKey(1)
        if c == 27:
            break
        
        if c > -1 and c != prev_char:
            cur_char = c
        prev_char = c
        
        if c == ord('s'):
            cv2.imshow("Cartoonize", cartoonize_img(frame, sketch_mode = True))
            
        elif c == ord('c'):
            cv2.imshow("Cartoonize", cartoonize_img(frame, sketch_mode = False))
        
        else:
            cv2.imshow("Cartoonize", frame)
            
    cap.release()
    cv2.destroyAllWindows()
                       
                       
        