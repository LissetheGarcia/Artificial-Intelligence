# García Santoyo, Lissethe Alejandra 17110106
# Sistemas de visión artificial y procesamiento de imágenes
# Chapter 3:"Cartoonizing an image"
# Archive: "programa_2_17110106.py"
# Ahora que sabemos capturar en pantalla un video en vivo desde la cámara web, vamos a ver
# cómo usar el teclado para interactuar con la ventana del video en vivo.

# Entradas de teclado.

import argparse # Importamos la librería analizadora de opciones de línea de comandos, argumentos y subcomandos
import cv2 # Importamos la librería de OpenCV

def argument_parser(): # Creamos la función analizadora de línea
    parser = argparse.ArgumentParser(description = "Cambia el color del espacio de la entrada del video usando teclas para el control que estan en el teclado, las teclas de control son: grayscale-'g', yuv-'y', HSV-'h'")
    return parser

if __name__ == '__main__': # Constructor
    args = argument_parser().parse_args()
    
    cap = cv2.VideoCapture(-1) # Captura cada cuadro de la webcam
    
    # Checa si la cámara está abierta correctamente
    if not cap.isOpened():
        raise IOError("No fue posible abrir la cámara web")
    
    cur_char = -1 # Inicializamos el caracter actual
    prev_char = -1 # Inicializamos el cvaracter previo
    
    while True: # Mantenemos actualizado cada cuadro de imagen tomado desde la webcam
        # Lee el cuadro presente en la webcam
        ret, frame = cap.read()
        
        # Redimensiona el cuadro presente de la cámara web
        frame = cv2.resize(frame, None, fx = 0.5, fy = 0.5, interpolation = cv2.INTER_AREA)
        
        c = cv2.waitKey(1)
        
        if c == 27:
            break
        
        if c < -1 and c != prev_char:
            cur_char = c
        prev_char = c
        
        if c == ord('g'):
            output = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            #ret, frame = cap.read()
            #frame = cv2.resize(frame, None, fx = 0.5, fy = 0.5, interpolation = cv2.INTER_AREA)
            #cv2.imshow("Grayscale", output)
        elif c == ord('y'):
            output = cv2.cvtColor(frame, cv2.COLOR_BGR2YUV)
        elif c == ord('h'):
            output = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        else:
            output = frame
            
        cv2.imshow('Webcam', output) # Muestra la salida según la tecla de entrada
        #cv2.waitKey()
        
    cap.release()
    cv2.destroyAllWindows() 
        
        
    