;
; Multiplicacion_entrada 16 bits_salida 24 bits.asm
;Dirección dato1 = 0x101
;Dirección dato2 = 0x102
;Dirección multiplicacion = 0x103

       .equ dato1=0x101
	   .equ dato2=0x102
	   .equ multiplicacion1=0x105
	   .equ multiplicacion2=0x111

	   lds r16,dato1     ; Cargamos un número de 16 bits con signo en r16
	   lds r17,dato2     ; Cargamos un número de 8 bits con signo en r17
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
	   lds r17,dato2      ; Cargamos el valor por lo que se deben multiplicar los bits restantes en r17
	   mul r16,r17        ; Ejecuta la multiplicación de lo que esté en los registros señalados
	   sts multiplicacion2,r16     ; Guarda el resultado de la multiplicación de r16 en esa posicion de memoria
	   sts 0x109,r1       ; El resultado de la multiplicacion con el bit más significativo es cargado en 0x110
	   sts 0x108,r0       ; El resultado de la multiplicación con el bit menos significativo es cargado en 0x109
	   sts 0x112,r1       ; Guardamos el bit de desplazamiento que deberá sumarse
	   mov r4,r1          ; Movemos el registro r1 a r4, y que al limpiarse el buffer se podría perder el dato
	   add r3,r4          ; Llevamos a cabo la suma de los registros con corrimiento
	   sts 0x115,r3       ; Mostramos la parte alta en un nuevo espacio de memoria
	   sts 0x114,r0       ; Mostramos la parte baja en un nuevo espacio de memoria
	
