# García Santoyo, Lissethe Alejandra 17110106
# Sistemas de visión artificial y procesamiento de imágenes
# Chapter 4:"Detectando y rastreando diferentes partes del cuerpo"
# Archive: "programa_4_17110106.py"
# Un sistema robusto es más fácil de entrenar cuando se quirn detectar objetos o partes con
# características únicas, afortunadamente los elementos de la cara son así, en esta sección
# vamos a desarrollar un programa detector de ojos y sobremontar una imagen de unos lentes.

# Diversión detectando ojos.

import cv2
import numpy as np

face_cascade = cv2.CascadeClassifier('/home/pi/opencv/opencv-4.1.2/data/haarcascades/haarcascade_frontalface_alt.xml')
eye_cascade = cv2.CascadeClassifier('/home/pi/opencv/opencv-4.1.2/data/haarcascades/haarcascade_eye.xml')

if face_cascade.empty():
    raise IOError("No está disponible para cargar el archivo classificador de cascada xml")

if eye_cascade.empty():
    raise IOError("No ha sido posible cargar el archivo clasificador de cascada xml")

img = cv2.imread('input.jpg')
glasses_img = cv2.imread('glasses.jpg')

#cap = cv2.VideoCapture(-1)
#ds_factor = 1.0

gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

centers = []
faces = face_cascade.detectMultiScale(gray, 1.3, 5)
for (x, y ,w ,h) in faces:
    roi_gray = gray[y:y+h, x:x+w]
    roi_color = img[y:y+h, x:x+w]
        
    eyes = eye_cascade.detectMultiScale(roi_gray)
    for (x_eye, y_eye, w_eye, h_eye) in eyes:
        centers.append((x + int(x_eye + 0.5 * w_eye), (y + int(y_eye + 0.5 * h_eye))))
        

if len(centers) > 0 :
    # el factor de 2.12 es adaptable dependiendo del tamaño de la cara
    glasses_width = 55 + abs(centers[1][0] - centers[0][0])
    overlay_img = np.ones(img.shape, np.uint8) * 255
    h, w = glasses_img.shape[:2]
    scaling_factor = glasses_width / w
    overlay_glasses = cv2.resize(glasses_img, None, fx = scaling_factor, fy = scaling_factor, interpolation = cv2.INTER_AREA)
    x = centers[0][0] if centers[0][0] < centers[1][0] else centers[1][0]
    
    # Adaptamos las localizaiones de X e Y; dependiendo del tamaño de la cara
    x -= int(0.22 * overlay_glasses.shape[1])
    y += int(0.7 * overlay_glasses.shape[0])
    
    h, w = overlay_glasses.shape[:2]
    print(overlay_glasses)
    overlay_img[y:y+h, x:x+w] = overlay_glasses
    # Creamos la máscara
    gray_glasses = cv2.cvtColor(overlay_img, cv2.COLOR_BGR2GRAY)
    ret, mask = cv2.threshold(gray_glasses, 110, 255, cv2.THRESH_BINARY)
    mask_inv = cv2.bitwise_not(mask)
    temp = cv2.bitwise_and(img, img, mask = mask)
    temp2 = cv2.bitwise_and(overlay_img, overlay_img, mask = mask_inv)
    final_img = cv2.add(temp, temp2)
    
    cv2.imshow("Dectetor de ojos", img)
    cv2.imshow("Lentes", final_img)
    cv2.waitKey()
    cv2.destroyAllWindows()
    
    