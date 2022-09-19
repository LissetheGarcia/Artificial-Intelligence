;
; Automaticas_Operaciones.asm
;---------------------------------------------------------------------------------------------
;SUMA


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

;------------------------------------------------------------------------------------------------
;RESTA
	

       .equ ddato1=0x101
	   .equ ddato2=0x103
	   .equ resta=0x106
    lds r16,ddato1     ;Carga en el dato 1 un número de 16 bits con signo
	lds r17,ddato2     ;Carga en el dato 2 un número de 16 bits con signo
	sub r16,r17       ;Resta lo que esté en la memoria de r16 con r17
	sts 0x105,r16     ;Guarda el resultado de la resta en r16
	lds r16,0x100     ;Cambia la direccion de memoria del r16 a 0x100
	lds r17,0x102     ;Cambia la direccion de memoria del r17 a 0x102
	sbc r16,r17       ;Ejecuta la resta con acarreo
	sts 0x104,r16     ;Guarda lo que esté en r16 en el espacio 0x105
	eor r16,r16       ;Pone la parte más significativa del registro en ceros
	sbc r16,r16       ;Ejecuta la resta con acarreo
	sts resta,r16     ;Guarda el resultado final de la resta en 0x106

;------------------------------------------------------------------------------------------------
;MULTIPLICACIÓN


       .equ dddato1=0x101
	   .equ dddato2=0x102
	   .equ multiplicacion1=0x105
	   .equ multiplicacion2=0x111

	   lds r16,dddato1     ; Cargamos un número de 16 bits con signo en r16
	   lds r17,dddato2     ; Cargamos un número de 8 bits con signo en r17
	   mul r16,r17       ; Multiplica el dato de r17 con r16, ambos con signo
	   sts multiplicacion1,r16     ; Guarda el resultado de la multiplicación de r16 en esa posicion de memoria
	   sts 0x107,r1       ; El resultado de la multiplicacion con el bit más significativo es cargado en 0x107
	   sts 0x106,r0       ; El resultado de la multiplicación con el bit menos significativo es cargado en 0x106
	   sts 0x113,r0       ; Guardamos el bit de desplazamiento que deberá sumarse
	   mov r3,r0          ; Movemos el registro r0 a r3, y que al limpiarse el buffer se podría perder el dato
	   clr r16            ; Limpia lo que hay en r16
	   clr r17            ; Limpia lo que hay en r17
	   clr r0             ; Limpia lo que hay en r0
	   clr r1             ; Limpia lo que hay en r1
	   lds r16,0x100      ; Cargamos los siguientes 8 bits del número en r16
	   lds r17,dddato2      ; Cargamos el valor por lo que se deben multiplicar los bits restantes en r17
	   mul r16,r17        ; Ejecuta la multiplicación de lo que esté en los registros señalados
	   sts multiplicacion2,r16     ; Guarda el resultado de la multiplicación de r16 en esa posicion de memoria
	   sts 0x109,r1       ; El resultado de la multiplicacion con el bit más significativo es cargado en 0x110
	   sts 0x108,r0       ; El resultado de la multiplicación con el bit menos significativo es cargado en 0x109
	   sts 0x112,r1       ; Guardamos el bit de desplazamiento que deberá sumarse
	   mov r4,r1          ; Movemos el registro r1 a r4, y que al limpiarse el buffer se podría perder el dato
	   add r3,r4          ; Llevamos a cabo la suma de los registros con corrimiento
	   sts 0x115,r3       ; Mostramos la parte alta en un nuevo espacio de memoria
	   sts 0x114,r0       ; Mostramos la parte baja en un nuevo espacio de memoria
	
	
;------------------------------------------------------------------------------------------------
;DIVISIÓN
 		.equ num=0x101
		.equ den=0x103
		.equ coc=0x105
		.equ res=0x107	
		.equ res_inc=0x109

    		lds r16,num         ; Carga en el numerador un numero de 16 bits con signo...
			lds r17,den         ; Carga en el denominador un numero de 16 bits con signo...
			mov r4,r17          ; Hace una copia del denominador en r4
		    mov r5,r16          ; Hace una copia del numerador en r5
		    eor r17,r17         ; Limpia r17

menor:
            
		   sts coc,r17          ; En r17 aparece el resultado del cociente

loop:       
			cp r5,r4            ; Compara el numerador con el denominador
			brlt menor
			;nop
			inc r17             ; Incrementa el número de ciclo, lo cual usaremos para obtener el cociente y el residuo
			sub r5,r4           ; Al numerador se substrae n veces el denominador
			sts res,r5          ; Guarda el resultado de la resta en res, que es el residuo
			cp  r4,r5           ; Compara el numerador con el denominador
			brlo loop           ; Hace un salto si r5 es menor a r4
			nop                 ; Salta a su destino
			cp  r5,r4           ; Compara el numerador con el denominador para ver si son iguales
			breq menorEQ           
			nop
menorEQ:
            
		   sts coc,r17          ; En r17 aparece el resultado del cociente
           clr r16              ; Preparamos r16 para poner el residuo
		   lds r16,0x100        ; Cargamos la parte menos significativa del numerador en este espacio de memoria
		   lds r17,0x102        ; Cargamos la parte menos significativa del denominador en este espacio de memoria
		   mov r1,r16           ; Hacemos una copia del numerador en r1
		   mov r2,r17           ; Hacemos una copia del denominador en r2
		   sub r16,r17          ; Hacemos la resta de las partes faltantes 
		   sts res,r16          ; Cargamos el residuo en el espacio de res

;------------------------------------------------------------------------------------------------


