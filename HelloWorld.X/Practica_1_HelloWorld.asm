; TODO INSERT CONFIG CODE HERE USING CONFIG BITS GENERATOR
; PIC16F15313 Configuration Bit Settings

; Assembly source line config statements

#include "p16f15313.inc"

; CONFIG1
; __config 0xFF8F
 __CONFIG _CONFIG1, _FEXTOSC_ECH & _RSTOSC_HFINT32 & _CLKOUTEN_OFF & _CSWEN_ON & _FCMEN_ON
; CONFIG2
; __config 0xFFFF
 __CONFIG _CONFIG2, _MCLRE_ON & _PWRTE_OFF & _LPBOREN_OFF & _BOREN_ON & _BORV_LO & _ZCD_OFF & _PPS1WAY_ON & _STVREN_ON
; CONFIG3
; __config 0xFF9F
 __CONFIG _CONFIG3, _WDTCPS_WDTCPS_31 & _WDTE_OFF & _WDTCWS_WDTCWS_7 & _WDTCCS_SC
; CONFIG4
; __config 0xFFFF
 __CONFIG _CONFIG4, _BBSIZE_BB512 & _BBEN_OFF & _SAFEN_OFF & _WRTAPP_OFF & _WRTB_OFF & _WRTC_OFF & _WRTSAF_OFF & _LVP_ON
; CONFIG5
; __config 0xFFFF
 __CONFIG _CONFIG5, _CP_OFF   
    
STR_SIZE equ 0x0B

;-----------------------------------------------------------------------
RES_VECT  CODE    0x0000            ; processor reset vector
    GOTO    START                   ; go to beginning of program

; TODO ADD INTERRUPTS HERE IF USED

;-----------------------------------------------------------------------
    
MAIN_PROG CODE                      ; let linker place main program
 
;-----------------------------------------------------------------------

    ; Configuracion del micro para la practica
START
    call    SETUP
    
    ; Codigo de la practica
loop_forever    
    call    LOOP
    
    goto    loop_forever

;-----------------------------------------------------------------------
SETUP  
     
    ; TODO -> Add initialization code here
    BANKSEL PORTA ;
    CLRF PORTA ;Init PORTA
    BANKSEL LATA ;Data Latch
    CLRF LATA ;
    BANKSEL ANSELA ;
    CLRF ANSELA ;digital I/O
    BANKSEL TRISA ;
    MOVLW B'00000001' ;
    MOVWF TRISA ;and set R
    
    
    ; inicializa 'cuenta' al tamagno de 'destino'
    bankisel cuenta
    movlw    STR_SIZE
    movwf    cuenta
    
    ; selecciona el banco de memoria de 'destino'
    ; y pon su direccion en nuestro apuntador 'FSR'
    bankisel destino
    movlw    low destino
    movwf    FSR0L
    movlw    high destino
    movwf    FSR0H
    
limpia: 
    ; limpia la localidad apuntada por 'indf' en 'destino'
    clrf     INDF0
    incf     FSR0, f
    decfsz   cuenta, f
    bra      limpia
    
    return

;-----------------------------------------------------------------------
LOOP     
          
    ; TODOD -> Add your program here
    
    ; inicia nuestro contador de letras a copiar
    bankisel cuenta
    movlw    STR_SIZE
    movwf    cuenta
    
    ; apunta en FSR0 el lugar donde pondremos nuestro texto
    movlw    low destino
    movwf    FSR0L
    movlw    high destino
    movwf    FSR0H

    ; en 'temp' pondremos el indice de la letra a copiar
    movlw    low origen
    movwf    temp
    
copia:
    ; apunta la parte alta del PC -Rpogram Counter- a la direccion de 'origen'
    movlw    high origen
    movwf    PCLATH
    ; pon en 'W' nuestro indice 'temp'
    movf     temp, W
    
    ; hay tres maneras de copiar datos del area de programa *rom* a la de 
    ; datos *ram*, aqui estamos usando el formato 'retlw K'
    callw
    
    ; mueve nuestra letra a su destino apuntado por 'INDF0' accorde a la 
    ; direccion en FSR0
    movwf    INDF0
    
    ; incrementa la posicion a copiar en 'destino', el indice en 'origen' y
    ; nuestra cuenta de caracteres a copiar (decrementandolo)
    incf     FSR0, f
    incf     temp, f
    decfsz   cuenta, f
    bra      copia
    
    ; terminamos, no regresamos a repetir la copia
    goto $
    
done:    
    return

;-----------------------------------------------------------------------    
 
; RECUERDA, Esta es una arquitectura HARVARD donde los espacios de 
;           memoria para programa y por lo tanto constantes como este 
;           texto, estan separadas de los datos!!! 
;
; PREGUNTA: Porque anteponemos a cada letra un '0x34'?
;           (La respuesta tiene que ver con la longitud en bits de las
;           instrucciones y la tabla de instrucciones de este micro)
 
origen  db   0x34, "H", 0x34, "e", 0x34, "l", 0x34, "l", 0x34, "o"
        db   0x34, " "
        db   0x34, "W", 0x34, "o", 0x34, "r", 0x34, "l", 0x34, "d"    

; OBJETIVO: Al final de la practica en esta area se debera leer
;           'Hello World' en el debugger
  
        UDATA
destino res  STR_SIZE
cuenta  res  1
temp    res  1
    
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    END
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
