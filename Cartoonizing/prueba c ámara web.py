import sys 
sys.path.append("C:\\opencv\\build\\python\\2.7") 
import cv2 
import cv2.cv as cv 
import time 

# Set resolution 
cap = cv2.VideoCapture(0) 
print "Frame default resolution: (" + str(cap.get(cv.CV_CAP_PROP_FRAME_WIDTH)) + "; " + str(cap.get(cv.CV_CAP_PROP_FRAME_HEIGHT)) + ")") 
cap.set(cv.CV_CAP_PROP_FRAME_WIDTH, 800) 
cap.set(cv.CV_CAP_PROP_FRAME_HEIGHT, 600) 
print "Frame resolution set to: (" + str(cap.get(cv.CV_CAP_PROP_FRAME_WIDTH)) + "; " + str(cap.get(cv.CV_CAP_PROP_FRAME_HEIGHT)) + ")" 

# Acquire frame 
capture = cv.CreateCameraCapture(0) 
img = cv.QueryFrame(capture) 
