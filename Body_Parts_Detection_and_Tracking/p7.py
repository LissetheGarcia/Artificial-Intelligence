# Un sistema robusto es más fácil de entrenar cuando se quirn detectar objetos o partes con
# características únicas, afortunadamente los elementos de la cara son así, en esta sección
# vamos a desarrollar un programa detector de bocas para sobremontar un bigotín.

# Tiempo de un bigotazo.

import cv2
import numpy as np


mouth = cv2.CascadeClassifier('/home/pi/opencv/opencv_contrib-4.1.2/modules/face/data/cascades/haarcascade_mcs_mouth.xml')

if mouth.empty():
    raise IOError("No fue enconytrado el archivo xml haarcascades")

moustache_mask = cv2.imread('moustache.png')
h_mask, _mask = moustache_mask.shape[:2]

cap = cv2.VideoCapture(-1)
s_f = 1.0

while True:
    ret, frame = cap.read()
    frame = cv2.resize(frame, None, fx = s_f, fy = s_f, interpolation = cv2.INTER_AREA)
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    
    mouth_rects = mouth.detectMultiScale(gray, 1.7, 11)
    if len(mouth_rects) > 0:
        (x, y, w, h) = mouth_rects[0]
        h, w =  int(0.6 * h), int(1.2 * w)
        x -= int(0.05 * w)
        y -= int(0.55 * h)
        frame_roi = frame[y:y+h, x:x+w]
        moustache_mask_small = cv2.resize(moustache_mask, (w, h), interpolation = cv2.INTER_AREA)
        
        gray_mask = cv2.cvtColor(moustache_mask_small, cv2.COLOR_BGR2GRAY)
        ret, mask = cv2.threshold(gray_mask, 50, 255, cv2.THRESH_BINARY_INV)
        mask_inv = cv2.bitwise_not(mask)
        masked_mouth = cv2.bitwise_and(moustache_mask_small, moustache_mask_small, mask = mask)
        masked_frame = cv2.bitwise_and(frame_roi, frame_roi, mask = mask_inv)
        frame[y:y+h, x:x+w] = cv2.add(masked_mouth, masked_frame)
        
        cv2.imshow("Bigotes", frame)
        
        c = cv2.waitKey(-1)
        if c == 27:
            break


        
cap.release()
cv2.destroyAllWindows()
