# Creación de imágenes panorámicas

import sys
import argparse
import cv2
import numpy as np


def argument_parser():
    parser = argparse.ArgumentParser(description = 'Tratar dos imágenes par juntarlas')
    parser.add_argument("--query-image", dest = "query_image", required = True, help = "Primera imagen que necesita ser tratada")
    parser.add_argument("--train.image", dest = "train_image", required = True, help = "Segunda imagen a ser tratada")
    parser.add_argument("--min-match-count", dest = "min_match_count", type = int, required = False, default = 10, help = "Número mínimo de relaciones requeridas")
    
    return  parser

# Unir la img2 a la imfg1 usando la homología de la matriz H


def warpImages(img1, img2, H):
    rows1, cols1 = img1.shape[:2]
    rows2, cols2 = img2.shape[:2]
    
    list_of_points_1 = np.float32([[0, 0], [0, rows1], [cols1, rows1], [cols1, 0]]).reshape(-1, 1, 2)
    temp_points = np.float32([[0, 0], [0, rows2], [cols2, rows2], [cols2, 0]]).reshape(-1, 1, 2)
    list_of_points_2 = cv2.perpectiveTransform(temp_points, H)
    list_of_points = np.concatenate((list_of_points_1, list_of_points_2), axis = 0)
    
    [x_min, y_min] = np.int32(list_of_points.min(axis = 0).ravel() - 0.5)
    [x_max, y_max] = np.int32(list_of_points.max(axis = 0).ravel() + 0.5)
    translation_dist = [-x_min, -y_min]
    H_translation = np.array([[1, 0, translation_dist[0]], [0, 1, translation_dist[1]], [0, 0, 1]])
    
    output_img = cv2.warpPerspective(img2, H_translation.dot(H), (x_max - x_min, y_max - y_min))
    output_img[translation_dist[1]:rows1 + translation_dist[1], translation_dist[0]:cols1 + translation_dist[0]] = img1
    
    return output_img

if __name__ == "__main__":
    args = argument_parser().parse_args()
    img1 = cv2.imread(args.query_image, 0)
    img2 = cv2.imread(args.train_image, 0)
    min_match_count = args.min_match_count
    
    cv2.imshow("Query image", img1)
    cv2.imshow("Train image", img2)
    
    # Inicializamos el detetor SIFT
    sift = cv2.SIFT_create()
    
    # Extraemo los puntos clave y los desriptores
    keypoints1, descriptors1 = sift.detectAndCompute(img1, None)
    keypoints2, descriptors2 = sift.detectAndcompute(img2, None)
    
    # Inicializamos los parámetros para la relación de Flann
    FLANN_INDEX_KDTREE = 0
    index_params = dict(algorithm = FLANN_INDEX_KDTREE, trees = 5)
    searh_params = dict(checks = 50)
    
    # Inicializamos el rtelacionador Flann
    flann = cv2.FlannBasedMatcher(index_params, search_params)
    
    # computamos las relaciones
    matches = flann.knnMatch(descriptors1, descriptors2, k = 2)
    
    # Guardamos todas las buenas uniones por cada test de radio de Lowe
    for m1, m2 in matches:
        if m1.distance < 0.7 + m2.ditance:
            good_matches.append(m1)
            
    if len(good_matches) > min_match_count:
        src_pts = np.float32([keypoints1[good_match.queryIdx].pt for good_match in good_matches]).reshape(-1, 1, 2)
        dst_pts = np.float32([keypoints2[good_match.trainIdx].pt for good_match in good_matches]).reshape(-1, 1, 2)
        
        M, mask = cv2.findHomography(src_pts, dst_pts, cv2.RANSAC, 0.5)
        result = warpImages(img2, img1, M)
        
        cv2.imshow("Imagen panorámica", result)
        
        cv2.waitKey()
        
    else:
        print("No tenemos suficiente número de relaciones entre las 2 imágenes")
        print("Se encontraron solamente %d relaiones. Se necesitan al menos %d relaciones" % (len(good_matches), min_match_count))
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
