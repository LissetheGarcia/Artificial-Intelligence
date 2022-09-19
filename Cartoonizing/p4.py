# García Santoyo, Lissethe Alejandra 17110106
# Sistemas de visión artificial y procesamiento de imágenes
# Chapter 3:"Cartoonizing an image"
# Archive: "programa_4_17110106.py"
# Vamos a ver cómo usar el mouse para interactuar con el video mostrado a través de la webcam.
# Podremos usar el mouse para seleccionar una región y entonces aplicar un filtro negativo.

# Interactuando con un video de transmisión en vivo a través de la webcam.

import cv2
import numpy as np

y_init = 0

def draw_rectangle(event, x, y, flags, params):
    global x_init, drawing, top_left_pt, bottom_right_pt
    
    if event == cv2.EVENT_LBUTTONDOWN:
        drawing = True
        x_init, y_int = x, y
        
    elif event == cv2.EVENT_MOUSEMOVE:
        if drawing:
            top_left_pt = (min(x_init, x), min(y_init, y))
            bottom_right_pt = (max(x_init, x), max(y_init, y))
            img[y_init:y, x_init:x] = 255 - img[y_init:y, x_init:x]
    
    elif event == cv2.EVENT_LBUTTONUP:
        drawing = False
        top_left_pt = (min(x_init, x), min(y_init, y))
        bottom_right_pt = (max(x_init, x), max(y_init, y))
        img[y_init:y, x_init:x] = 255 - img[y_init:y, x_init:x]
        
if __name__ == '__main__':
    drawing = False
    top_left_pt, bottom_right_pt = (-1, -1), (-1, -1)
    
    cap = cv2.VideoCapture(-1)
    
    # Corrobora que la cámara esté abierta correctamente
    if not cap.isOpened():
        raise IOError("No fue posible abrir la camara web")
    
    cv2.namedWindow("Camara web")
    cv2.setMouseCallback("Camara web", draw_rectangle)
    
    while True:
        ret, frame = cap.read()
        img = cv2.resize(frame, None, fx = 0.5, fy = 0.5, interpolation = cv2.INTER_AREA)
        (x0, y0), (x1, y1) = top_left_pt, bottom_right_pt
        img[y0:y1, x0:x1] = 255 - img[y0:y1, x0:x1]
        
        cv2.imshow("Camara web", img)
        
        c = cv2.waitKey(1)
        if c == 27:
            break
        
    cap.release()
    cv2.destroyAllWindows()
    


