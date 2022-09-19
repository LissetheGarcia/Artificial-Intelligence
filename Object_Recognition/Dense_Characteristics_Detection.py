# Detector de características densas

import cv2
import numpy as np
#import create_features
#from ..common import my_ds


class DenseDetector(object):
    def __init__(self, step_size=20, feature_scale=40,img_bound=20):
        # Creamos un detector de características densas
        ####self.detector = cv2.FeatureDetector_create("Dense")
        self.detector = cv2.xfeatures2d.SIFT_create()
        ####self.detector = cv2.FeatureDetector_create("Dense")
        # Lo inicializamos con todos los parámetros requeridos
        self.detector.setInt("initXyStep", step_size)
        self.detector.setInt("initFeatureScale", feature_scale)
        self.detector.setInt("initImgBound", img_bound)
        
        
    def detect(self, img):
        # Corremos el detector de características en la imagen de entrada
        return self.detector.detect(img)


if __name__=='__main__':
    input_image = cv2.imread('img.jpg')
    input_image_sift = np.copy(input_image)
    # Convertimos a escala de grises
    gray_image = cv2.cvtColor(input_image, cv2.COLOR_BGR2GRAY)
    keypoints = DenseDetector(20,20,5).detect(input_image)
    # Dibujamos los puntos claves sobre la imagen de entrada
    input_image = cv2.drawKeypoints(input_image, keypoints,
    flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
    # Mostramos la imagen de salida
    cv2.imshow('Dense feature detector', input_image)
    # Inicializamos el objeto 'SIFT'
    sift = cv2.SIFT()
    # Detectamos los puntos claves usando SIFT
    keypoints = sift.detect(gray_image, None)
    # Dibujamos los puntos clave SIFT en la imagen de entrada
    input_image_sift = cv2.drawKeypoints(input_image_sift,
    keypoints,
    flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
    
    # Mostramos la imagen de salida
    cv2.imshow('SIFT detector', input_image_sift)
    # Esperamos hasta que el usuario presione la tecla de salida
    cv2.waitKey()
