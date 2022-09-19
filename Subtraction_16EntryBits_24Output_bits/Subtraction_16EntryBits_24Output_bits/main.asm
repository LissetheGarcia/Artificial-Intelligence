;
; Resta_entrada 16 bits_salida 24 bits.asm
;
; Created: 06/09/2019 09:20:39 p. m.
; Author : Villarruel Ram�rez, Luis Fabi�n
; Author : Torres Ramos, Javier Alejandro 
; Author : Garc�a Santoyo, Lissethe Alejandra
;
;Direcci�n dato1 = 0x100:0x101
;Direcci�n dato2 = 0x102:0x103
;Direcci�n resta = 0x106

       .equ dato1=0x101
	   .equ dato2=0x103
	   .equ resta=0x106
    lds r16,dato1     ;Carga en el dato 1 un n�mero de 16 bits con signo
	lds r17,dato2     ;Carga en el dato 2 un n�mero de 16 bits con signo
	sub r16,r17       ;Resta lo que est� en la memoria de r16 con r17
	sts 0x105,r16     ;Guarda el resultado de la resta en r16
	lds r16,0x100     ;Cambia la direccion de memoria del r16 a 0x100
	lds r17,0x102     ;Cambia la direccion de memoria del r17 a 0x102
	sbc r16,r17       ;Ejecuta la resta con acarreo
	sts 0x104,r16     ;Guarda lo que est� en r16 en el espacio 0x105
	eor r16,r16       ;Pone la parte m�s significativa del registro en ceros
	sbc r16,r16       ;Ejecuta la resta con acarreo
	sts resta,r16     ;Guarda el resultado final de la resta en 0x106




  
