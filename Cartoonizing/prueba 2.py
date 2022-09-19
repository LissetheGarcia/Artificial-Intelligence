import cv2
import cv2 as cv
import time
cv.NamedWindow("cam", 1)#crea ventana
captura = cv.CaptureFromCAM(0)#captura de video, el numero 0 puede variar, en caso de no funcionar intenta con -1 o 1
cv.SetCaptureProperty(captura,cv.CV_CAP_PROP_FRAME_WIDTH, 640)#establece el ancho de la captura de video
cv.SetCaptureProperty(captura,cv.CV_CAP_PROP_FRAME_HEIGHT, 480);#establece el largo de la captura de video
#si no hay captura de video cerrar todo
if not captura:
    print ("Error con WebCam")
    sys.exit(1)
while True:
    img = cv.QueryFrame(captura)#crea una imagen o frame con la captura de video
    if img is None:#si no hay imagen sale del ciclo while
        break
    cv.ShowImage("cam", img)#muestra la imagen o frame en pantalla
    if cv.WaitKey(10) == 27:#espera a la tecla ESC para detener el programa
        break
cv.DestroyAllWindows()