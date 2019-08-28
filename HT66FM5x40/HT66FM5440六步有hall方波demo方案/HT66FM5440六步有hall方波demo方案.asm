include HT66FM5440.inc

ds	.section	'data'
flag_motor_rpm	dbit

R_adcdatah		db		?
r_status		db		?
r_acc			db		?
r_restarcnt		db		?

cs	.section	at  000h	'code'
		ORG		0000H
		JMP		STAR
		org		0014h
		jmp		isr_captmover
		org		003ch
		jmp		isr_time_base

STAR:
		clr		EMI
		MOV		A,01H
		MOV		SMOD,A
		SNZ		HTO
		JMP		$-1				;wait for CLK	stable
		call	f_io_inital
		call	f_adc_inital
		call	f_time_baseinital
		call	f_captm_inital
		call	f_currentover_protect_inital
		call	f_motor_pwm_inital
		clr		r_restarcnt
		set		EMI
		
mainloop:
		clr		WDT
		call	f_motor_rpm_control
		SNZ		ISEOCB			;when adc Transfer finish will set ISEOCB high 
		JMP		mainloop
		LMOV	A,ISRH0			;read	ADC data by pilling
		MOV		R_adcdatah,A
		jmp		mainloop
		
;;-------------------
;;
;;-------------------
f_motor_rpm_control:		
		mov		a,20h
		sub		a,R_adcdatah
		sz		C
		jmp		clear_duty
		snz		flag_motor_rpm
		ret
		clr		flag_motor_rpm
		mov		a,R_adcdatah
		sub		a,DUTR0L
		sz		C
		jmp		inc_duty
		mov		a,R_adcdatah
		mov		DUTR0L,A
		mov		DUTR1L,a
		mov		DUTR2L,a		;motor Deceleration
		ret
clear_duty:
		clr		DUTR0L			;motor stop by vsp
		clr		DUTR1L
		clr		DUTR2L
		ret		
inc_duty:
		inc		DUTR0L			;motor accelerate slowly
		inc		DUTR1L
		inc		DUTR2L
		
		ret				
;;-------------------
;;
;;-------------------
f_io_inital:
		clr		PC
		mov		a,00h			;PC output
		mov		PCC,A
		mov		a,10111010b		;vsp input and pa5,pa4,pa3 input hall signal¡APA1 AS AP input detect currentover
		mov		PAC,A
		mov		a,00000100b
		lmov	PAPS0,A			;pa1 as ap inpout
		mov		a,01000000b		;pa7 turn into an6  as vsp input
		lmov	PAPS1,A
		mov		a,10101010b		;pc turn into pwm output
		lmov	PCPS0,A
		mov		a,00001010b
		lmov	PCPS1,A		
		ret
;;-------------------
;;
;;-------------------
f_adc_inital:
		mov		a,00000111b
		mov		ADCR0,a
		mov		a,01000100b
		mov		ADCR1,A
		mov		a,00000000b
		mov		ADCR2,A
		mov		a,00h
		lmov	ADCR3,A
		mov		a,00000111b		;auto scan adc change olny one is an6 	
		mov		ADISG1,A
		mov		a,00h
		mov		ADISG2,A
		mov		a,20
		mov		ADDL,A			;adc aotu scan star delay register
		mov		a,10h
		lmov	ADBYPS,A		;the switch must be open
		ret

;;-------------------
;;
;;-------------------
f_motor_pwm_inital:
		mov		a,00000001b
		mov		PWMC,A
		mov		a,00h
		lmov	PWMCS,A
		mov		a,00H
		mov		DUTR0H,A		;write dutrnh must to earlier than dutrnl
		mov		a,00h
		mov		DUTR0L,A
		mov		a,00h
		mov		DUTR1H,A
		mov		a,00h
		mov		DUTR1L,A
		mov		a,00h
		mov		DUTR2H,A
		mov		a,00h
		mov		DUTR2L,A
		mov		a,01h
		mov		PRDRH,A
		mov		a,00h
		mov		PRDRL,A
		set		PWMON
		
		mov		a,00001101b		;hardware mask model,Non complementary ,pwm output enable
		mov		MCF,A
		mov		a,01101001b		;fdt=fsys/2,dead time=0.1us&[9+1]=1us
		mov		DTS,A
		mov		a,00h
		mov		PLC,A
		
		mov		a,00h
		mov		INTEG0,A
		mov		a,11011011b		;no delay,hall sensor 120 degree,hall decode by hardware and enable
		mov		HDCR,A
		mov		a,00000110B					;CT/BB(1)
		lmov	HDCT0,A
		mov		a,00100100B					;AT/BB(3)
		lmov	HDCT1,A
		mov		a,00100001B					;AT/CB(2)
		lmov	HDCT2,A
		mov		a,00001001B					;BT/CB(6)
		lmov	HDCT3,A
		mov		a,00011000B					;BT/AB(4)
		lmov	HDCT4,A
		mov		a,00010010B					;CT/AB(5)
		lmov	HDCT5,A
		
		mov		a,00001001B					;BTCB(1)		
		lmov	HDCT6,A
		mov		a,00011000B					;BTAB(3)
		lmov	HDCT7,A
		mov		a,00010010B					;CTAB(2)
		lmov	HDCT8,A
		mov		a,00000110B					;CTBB(6)
		lmov	HDCT9,A
		mov		a,00100100B					;ATBB(4)
		lmov	HDCT10,A
		mov		a,00100001B					;ATCB(5)
		lmov	HDCT11,A
		
		mov		a,00101000b					;motor protect model choose 
		mov		MPTC1,A
		mov		a,00000101b
		mov		MPTC2,A
		mov		a,00h
		mov		OCPS,A
		
		ret
		
		
;;-------------------
;;
;;-------------------		
f_captm_inital:
		mov		a,01110000b				;FHA change,fh/128=6.4us
		mov		CAPTC0,A
		mov		a,01110010b				;rising edage avi
		mov		CAPTC1,A
		mov		a,0f4h
		mov		CAPTMAH,A
		mov		a,24H
		mov		CAPTMAL,A
		set		CAPTON
		set		INT_PRI5E
		
		ret
;;-------------------
;;
;;-------------------		
isr_captmover:
		mov		R_acc,A
		mov		a,STATUS
		mov		r_status,A
		inc		r_restarcnt
		mov		a,r_restarcnt
		sub		a,8
		snz		Z
		jmp		captmend
		SET		PSWE
		SET		PSWPS
		CLR		PSWD					;resatr motor
		NOP 
		NOP
		CLR		PSWE
		CLR		r_restarcnt
		clr		DUTR0L
		clr		DUTR1L
		clr		DUTR2L
		
captmend:
		clr		INT_PRI5F				
		mov		a,r_status
		mov		STATUS,A
		mov		a,R_acc		
		reti		
		
		
;;-------------------
;;
;;-------------------		
f_currentover_protect_inital:
		mov		a,00010001b
		mov		CMPC,A					;comp0 open
		mov		a,01000011b				;opa gain is 20
		lmov	OPOMS,A
		mov		a,52					;currentover is 1A~102
		lmov	OPCM,A
		mov		a,00010000b
		lmov	OPA0CAL,A
		RET		
		
						
;;-------------------
;;
;;-------------------
f_time_baseinital:
		mov		a,11110000b				
		lmov	TBC,A
		clr		TBF
		set		TBE
		clr		INT_PRI15F
		set		INT_PRI15E

		ret
;;-------------------
;;
;;-------------------
isr_time_base:
		mov		R_acc,A
		mov		a,STATUS
		mov		r_status,A
		
		clr		TBF
		set		flag_motor_rpm
		mov		a,r_status				;motro speed cintrol flag
		mov		STATUS,A
		mov		a,R_acc
		
		reti				
		
end
