# García Santoyo, Lissethe Alejandra 17110106
# Sistemas de visión artificial y procesamiento de imágenes
# Chapter 3:"Cartoonizing an image"
# Archive: "programa_1_17110106.py"
# El siguiente código abrirá la cámera web, capturará los cuadros y los pondrá a escala con
# un factor de 2, y entonces, lo mostrará en una ventana. Se puede presionar la tecla Esc para salir.

# Accediendo a la cámara web.

import cv2 # Importa la librería de OpenCV

cap = cv2.VideoCapture(-1)


#cam = cv.CaptureFromCAM(-1) 


if not cap.isOpened(): # Checa si la cámara web está abierta correctamente
   raise IOError("No se pudo abrir la camara web") # Abre una ventana con el mensaje que está entre comillas

while True:
    ret, frame = cap.read() # Crea un ciclo infinito de cuadros hasta que es presionada la tecla de interrupción
    frame = cv2.resize(frame, None, fx = 0.5, fy = 0.5, interpolation = cv2.INTER_AREA)
    cv2.imshow('Entrada', frame)
    
    c = cv2.waitKey(1)
    if c == 27: # Se mantiene checando la tecla de interrupción (su valor en ASCII)
        break

cap.release()
cv2.destroyAllWindows()

