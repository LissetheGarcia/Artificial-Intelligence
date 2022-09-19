# Seguimiento basado en el espacio de color

import cv2
import numpy as np


# Capturamos el uadro de entrada desde la webcam
def get_frame(cap, scaling_factor):
    # Capturamos el video desde el objeto del video
    ret, frame = cap.read()
    # Redimensionamos el cuadro de entrada
    frame = cv2.resize(frame, None, fx=scaling_factor,
    fy=scaling_factor, interpolation=cv2.INTER_AREA)
    
    return frame


if __name__=='__main__':
    cap = cv2.VideoCapture(0)
    scaling_factor = 0.5
    # Iteramos hasta que el usuario presione la tecla 'ESC'
    while True:
        frame = get_frame(cap, scaling_factor)
        # Convertimos de HSV a espaio de color
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        # Definimos'azul' en el rango HSV del espacio de colores
        lower = np.array([60,100,100])
        upper = np.array([180,255,255])
        # Delimitamos la imagen HSV a sólo el color que hemos elegido
        mask = cv2.inRange(hsv, lower, upper)
        # Bitwise-AND mask and original image
        res = cv2.bitwise_and(frame, frame, mask=mask)
        res = cv2.medianBlur(res, 5)
        cv2.imshow('Original image', frame)
        cv2.imshow('Color Detector', res)
        
        # Corroboramos si el usuario presionó la tecla 'ESC'
        c = cv2.waitKey(5)
        if c == 27:
            break
        
cv2.destroyAllWindows()
