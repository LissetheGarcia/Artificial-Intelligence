# BRIEF (Binary Robust Independent elemntary Features)

import cv2
import numpy as np

gray_img= cv2.imread('house.jpeg', 0)
### gray_img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# Iniciamos el detector FAST
#fast = cv2.xfeatures2d.DescriptorExtractor_create("BRIEF")
fast = cv2.FastFeatureDetector_create()
#brief = cv2.DescriptorExtractor_create()
brief = cv2.BRISK_create()

# Encuentra lo puntos clave con STAR
keypoints = fast.detect(gray_img, None)

# Computamos lo descriptores con "BRIEF"
keypoints, descriptors = brief.compute(gray_img, keypoints)

gray_keypoints = cv2.drawKeypoints(gray_img, keypoints, np.array([]), (0, 255, 0), cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)

cv2.imshow("BRIEF keypoints", gray_keypoints)
cv2.waitKey()
