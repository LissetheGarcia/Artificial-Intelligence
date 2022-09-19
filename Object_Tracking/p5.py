# García Santoyo, Lissethe Alejandra 17110106
# Sistemas de visión artificial y procesamiento de imágenes
# Chapter 9:"Seguimiento de objetos"
# Archive: "programa_5_17110106.py"

# Resta de fondo

import cv2
import numpy as np


# Captura el cuadro de entrada
def get_frame(cap, scaling_factor=0.5):
    ret, frame = cap.read()
    # Redimensiona el cuadro
    frame = cv2.resize(frame, None, fx=scaling_factor,
    fy=scaling_factor, interpolation=cv2.INTER_AREA)
    
    return frame


if __name__=='__main__':
    # Inicializa la captura del objeto en el video
    cap = cv2.VideoCapture(0)
    # Crea un fondo que extrae el objeto
    bgSubtractor = cv2.bgsegm.createBackgroundSubtractorMOG()
    #########bgSubtractor = cv2.BackgroundSubtractor.apply()
    history = 100
    # Iteramos hasta que el usuario presione la tecla 'ESC'
    while True:
        frame = get_frame(cap, 0.5)
        # Aplicamos el modelos de substracción del fondo con el cuadro de entrada
        mask = bgSubtractor.apply(frame,
        learningRate=1.0/history)
        # Convertimos de escala de grises a 3 canales RGB
        mask = cv2.cvtColor(mask, cv2.COLOR_GRAY2BGR)
        cv2.imshow('Input frame', frame)
        cv2.imshow('Moving Objects', mask & frame)
        # Check if the user pressed the ESC key
        c = cv2.waitKey(10)
        if c == 27:
            break
        
cap.release()
cv2.destroyAllWindows()
