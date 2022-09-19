# García Santoyo, Lissethe Alejandra 17110106
# Sistemas de visión artificial y procesamiento de imágenes
# Chapter 9:"Seguimiento de objetos"
# Archive: "programa_1_17110106.py"

# Diferenciación de trama

import cv2


# Computa la diferencia de tramas
def frame_diff(prev_frame, cur_frame, next_frame):
    # Diferencia absoluta entre el uadro actual y el siguiente
    diff_frames1 = cv2.absdiff(next_frame, cur_frame)
    # Diferenia absoluta entre el cuadro actual y en cuadro previo
    diff_frames2 = cv2.absdiff(cur_frame, prev_frame)
    # Retorna el resultado bit a bit de 'AND' entre los dos imágenes resultantes
    return cv2.bitwise_and(diff_frames1, diff_frames2)


# REtorna el uadro desde la webcam
def get_frame(cap):
    # Captura el cuadro
    ret, frame = cap.read()
    # Redimensionamos la imagen
    frame = cv2.resize(frame, None, fx=scaling_factor,
    fy=scaling_factor, interpolation=cv2.INTER_AREA)
    
    # Retornamos una imagen en escala de grises
    return cv2.cvtColor(frame, cv2.COLOR_RGB2GRAY)

if __name__=='__main__':
    cap = cv2.VideoCapture(0)
    scaling_factor = 0.5
    prev_frame = get_frame(cap)
    cur_frame = get_frame(cap)
    next_frame = get_frame(cap)
    # Iteramos hasta que el usuario presione la tecla "ESC"
    while True:
        # Desplegamos el resultado de la diferenia de uadro
        cv2.imshow("Object Movement", frame_diff(prev_frame,
        cur_frame, next_frame))
        # Actualizamos las variables
        prev_frame = cur_frame
        cur_frame = next_frame
        next_frame = get_frame(cap)
        # Corroboramos si el usuario presionó 'ESC'
        key = cv2.waitKey(10)
        if key == 27:
            break
        
cv2.destroyAllWindows()