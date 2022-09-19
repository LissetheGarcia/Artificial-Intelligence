;
; Suma_entrada 16 bits_salida 24 bits.asm
;
; Created: 06/09/2019 08:43:46 p. m.
; Author : Villarruel Ramírez, Luis Fabián
; Author : Torres Ramos, Javier Alejandro 
; Author : García Santoyo, Lissethe Alejandra
;
;Dirección dato1 = 0x100:0x101
;Dirección dato2 = 0x102:0x103
;Dirección suma  = 0x104


       .equ dato1=0x101
	   .equ dato2=0x103
	   .equ suma=0x106
    lds r16,dato1     ;Carga en el dato 1 un número de 16 bits con signo
	lds r17,dato2     ;Carga en el dato 2 un número de 16 bits con signo
	add r16,r17       ;Suma lo que esté en la memoria de r16 con r17
	sts 0x105,r16     ;Guarda el resultado de la suma en r16
	lds r16,0x100     ;Cambia la direccion de memoria del r16 a 0x100
	lds r17,0x102     ;Cambia la direccion de memoria del r17 a 0x102
	adc r16,r17       ;Ejecuta la suma con acarreo
	sts 0x104,r16     ;Guarda lo que esté en r16 en el espacio 0x105
	eor r16,r16       ;Pone la parte más significativa del registro en ceros
	adc r16,r16       ;Ejecuta la suma con acarreo
	sts suma,r16      ;Guarda el resultado final de la suma en 0x104


    
