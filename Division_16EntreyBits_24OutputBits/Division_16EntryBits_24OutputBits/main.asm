;
; Division_entrada 16 bits_salida 24 bits.asm
;
; Created: 07/09/2019 03:19:42 p. m.
; Author : Villarruel Ramírez, Luis Fabián
; Author : Torres Ramos, Javier Alejandro
; Author : García Santoyo, Lissethe Alejandra


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

			
	
			



