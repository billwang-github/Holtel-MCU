;; 16 bits x 16 bits 
#include HT66FM5440.inc

public _vara1 
public _varb1 			;; define the function and parameters as public
public _vara2
public _varb2 			;; define the function and parameters as public
public _vara3
public _varb3

public _mul16x16
_mul16x16 .section page 'code'
_mul16x16 proc 		;; define function with proc/endp
	local _vara1 db 2 dup (?) ;; define parameters
	local _varb1 db 2 dup (?)
	local _result db 4 dup (?) ;; define local variables	
	mov a, _vara1[0]
	mov mdu1r0 , a
	mov a, _varb1[0]
	mov mdu1r4 , a
	mov a, _vara1[1]
	mov mdu1r1 , a
	mov a, _varb1[1]
	mov mdu1r5 , a			

	mov a, mdu1r0
	mov _result[0], a
	mov a, mdu1r1
	mov _result[1], a
	mov a, mdu1r2
	mov _result[2], a
	mov a, mdu1r3
	mov _result[3], a		
	ret
_mul16x16 endp

public _div16_16 ; vara2/varb2
_div16_16 .section page 'code'
_div16_16 proc 		;; define function with proc/endp
	local _vara2 db 2  dup(?)
	local _varb2 db 2  dup(?)			;; define the function and parameters as public		
	local _quo1 db 2 dup (?) ;; define local variables	
	local _rem1 db 2 dup (?) ;; define local variables		
	mov a, _vara2[0]
	mov mdu1r0 , a
	mov a, _vara2[1]
	mov mdu1r1 , a
	mov a, _varb2[0]
	mov mdu1r4 , a
	mov a, _varb2[1]
	mov mdu1r5 , a			

	mov a, mdu1r0
	mov _quo1[0], a
	mov a, mdu1r1
	mov _quo1[1], a
	mov a, mdu1r4
	mov _rem1[2], a
	mov a, mdu1r5
	mov _rem1[3], a		
	ret
_div16_16 endp

public _div32_16 ; vara3/varb3
_div32_16 .section page 'code'
_div32_16 proc 		;; define function with proc/endp
	local _vara3 db 4  dup(?)
	local _varb3 db 2  dup(?)			;; define the function and parameters as public		
	local _quo2 db 4 dup (?) ;; define local variables	
	local _rem2 db 2 dup (?) ;; define local variables		
	mov a, _vara3[0]
	mov mdu1r0 , a
	mov a, _vara3[1]
	mov mdu1r1 , a
	mov a, _vara3[2]
	mov mdu1r2 , a
	mov a, _vara3[3]
	mov mdu1r3 , a			
	mov a, _varb3[0]
	mov mdu1r4 , a		
	mov a, _varb3[1]
	mov mdu1r5 , a		
		
	mov a, mdu1r0
	mov _quo2[0], a
	mov a, mdu1r1
	mov _quo2[1], a
	mov a, mdu1r2
	mov _quo2[2], a
	mov a, mdu1r3
	mov _quo2[3], a		
	mov a, mdu1r4
	mov _rem2[2], a
	mov a, mdu1r5
	mov _rem2[3], a		
	ret
_div32_16 endp