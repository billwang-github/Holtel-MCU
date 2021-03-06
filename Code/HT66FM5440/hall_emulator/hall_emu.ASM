; Generated by holtek-gcc v3.19, Thu Aug 01 10:51:02 2019
; 
; Configuration:
;       with long instruction
;       Single ROM, Multi-RAM
;       bits_per_rom_unit:16
;       with mp1
;       with tbhp, address(0x9)
;          Use tabrd-const
;       
; SFR address of long-instruction arch:
;    mp0 = -1,1,0
;    mp1 = 4,3,2
;    mp2 = 14,13,12
;    tbp = 9,7,8
;    acc = 5
;    pcl = 6
;    status = 10
;    bp = 11
;    intc = 21
;       
;       
; use 'tabrdc' instead of 'tabrd'
;       

#pragma translator "holtek-gcc 4.6.4" "3.19" "build 20130711"
; Rebuild 115

ir equ [2]
mp equ [3]
sbp equ [4]
acc equ [5]
bp equ [11]
tblp equ [7]
tbhp equ [9]
status equ [10]
c equ [10].0
ac equ [10].1
z equ [10].2
ov equ [10].3
cz equ [10].6
sc equ [10].7
intc equ [21]
mdu0r0 equ [73h]
mdu0r1 equ [74h]
mdu0ctrl equ [75h]
mduwr0 equ [76h]
mduwr1 equ [77h]
mduwr2 equ [78h]
mduwr3 equ [7ah]
mduwr4 equ [7bh]
mduwr5 equ [7ch]
mduwrctrl equ [7dh]

extern ra:byte
extern rb:byte
extern rc:byte
extern rd:byte
extern re:byte
extern rf:byte
extern rg:byte
extern rh:byte
extern _Crom2Prom:near
extern _Crom2PromNext:near

RAMBANK 0 @BITDATASEC, @BITDATASEC1
@HCCINIT	.section 'data'
@HCCINIT0	.section 'data'
@BITDATASEC	 .section 'data'
@BITDATASEC1	 .section 'data'

#pragma debug scope 1 1
	extern __DELAY3:near
	extern __DELAYX3:near
	extern __DELAYX6:near
	extern __DELAYY5:near
	extern __DELAYY3:near
	extern _builtin_holtek_delay_2:byte
#line 19 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
public _hall_state
@HCCINIT0_hall_state .section 'data'
_hall_state	db 2 dup(0)
#pragma debug variable 12 1 _hall_state "hall_state"

@HCCINIT .section 'data'
public _cnt_hall_period
@HCCINIT	.section 'data'
#line 22 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
@HCCINIT_cnt_hall_period .section 'data'
_cnt_hall_period label byte
#pragma debug variable 12 1 _cnt_hall_period "cnt_hall_period"
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT_cnt_hall_period .section 'data'
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT_cnt_hall_period .section 'data'
public _cnt_1ms
#line 23 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
@HCCINIT_cnt_1ms .section 'data'
_cnt_1ms label byte
#pragma debug variable 12 1 _cnt_1ms "cnt_1ms"
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT_cnt_1ms .section 'data'
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT_cnt_1ms .section 'data'
public _hall_period
#line 24 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
@HCCINIT_hall_period .section 'data'
_hall_period label byte
#pragma debug variable 12 1 _hall_period "hall_period"
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT_hall_period .section 'data'
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT_hall_period .section 'data'
public _hall_60d
#line 24 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
@HCCINIT_hall_60d .section 'data'
_hall_60d label byte
#pragma debug variable 12 1 _hall_60d "hall_60d"
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT_hall_60d .section 'data'
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT_hall_60d .section 'data'
public _hall_120d
#line 24 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
@HCCINIT_hall_120d .section 'data'
_hall_120d label byte
#pragma debug variable 12 1 _hall_120d "hall_120d"
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT_hall_120d .section 'data'
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT_hall_120d .section 'data'
public _hall_180d
#line 24 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
@HCCINIT_hall_180d .section 'data'
_hall_180d label byte
#pragma debug variable 12 1 _hall_180d "hall_180d"
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT_hall_180d .section 'data'
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT_hall_180d .section 'data'
public _hall_240d
#line 24 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
@HCCINIT_hall_240d .section 'data'
_hall_240d label byte
#pragma debug variable 12 1 _hall_240d "hall_240d"
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT_hall_240d .section 'data'
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT_hall_240d .section 'data'
public _hall_300d
#line 24 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
@HCCINIT_hall_300d .section 'data'
_hall_300d label byte
#pragma debug variable 12 1 _hall_300d "hall_300d"
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT_hall_300d .section 'data'
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT_hall_300d .section 'data'
public _cnt_pwm_period
#line 25 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
@HCCINIT_cnt_pwm_period .section 'data'
_cnt_pwm_period label byte
#pragma debug variable 12 1 _cnt_pwm_period "cnt_pwm_period"
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT_cnt_pwm_period .section 'data'
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT_cnt_pwm_period .section 'data'
public _pwm_period
#line 25 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
@HCCINIT_pwm_period .section 'data'
_pwm_period label byte
#pragma debug variable 12 1 _pwm_period "pwm_period"
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT_pwm_period .section 'data'
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT_pwm_period .section 'data'
public _pwm_duty
#line 25 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
@HCCINIT_pwm_duty .section 'data'
_pwm_duty label byte
#pragma debug variable 12 1 _pwm_duty "pwm_duty"
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT_pwm_duty .section 'data'
	db 0
@ROMDATA_BASE .section inpage 'code'
	db 0
@HCCINIT_pwm_duty .section 'data'
___intc0 equ [21]
___pa equ [35]
public _main
#pragma debug scope 2 1
#line 34 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
IFDEF WITH_DEFAULT_STARTUP
extern _main_initial0:near
extern _main_startup:near
ENDIF

ROMBANK 0 @start
@start .section com_l 'code'
_main_startup1:
@start .section com_e 'code'
	jmp _main

_main .section 'code'
_main proc
#line 37 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	call _IO_Init
#line 40 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	call _TimeBase_Init
#line 41 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	set [21].0
#line 42 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,10
	mov _cnt_1ms[0],a
	clr _cnt_1ms[1]
#line 43 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	jmp _L2
_L3:
#line 45 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
;# 45 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c" 1
	clr wdt
_L2:
#line 43 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,_cnt_1ms[0]
	mov ra,a
	mov a,_cnt_1ms[1]
	mov rb,a
	mov a,ra
	or a,rb
	snz z
	jmp _L3
#line 48 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,100
	mov _pwm_period[0],a
	clr _pwm_period[1]
#line 49 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,20
	mov _pwm_duty[0],a
	clr _pwm_duty[1]
#line 51 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,5
	mov _hall_state[0],a
	clr _hall_state[1]
#line 52 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,-24
	mov _Hall_Period_Init_2[0],a
	mov a,38
	mov _Hall_Period_Init_2[1],a
	call _Hall_Period_Init
#line 53 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	call _TM1_Init
_L9:
#line 57 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,20
	mov _cnt_1ms[0],a
	clr _cnt_1ms[1]
#line 58 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	jmp _L4
_L5:
#line 60 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
;# 60 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c" 1
	clr wdt
_L4:
#line 58 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,_cnt_1ms[0]
	mov ra,a
	mov a,_cnt_1ms[1]
	mov rb,a
	mov a,ra
	or a,rb
	snz z
	jmp _L5
#line 63 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,_hall_period[0]
	mov ra,a
	mov a,_hall_period[1]
	mov rb,a
	mov a,242
	sub a,ra
	mov a,1
	sbc a,rb
	sz c
	jmp _L6
#line 64 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,_hall_period[0]
	mov ra,a
	mov a,_hall_period[1]
	mov rb,a
	mov a,196
	addm a,ra
	mov a,255
	adcm a,rb
	mov a,ra
	mov _hall_period[0],a
	mov a,rb
	mov _hall_period[1],a
	mov a,ra
	mov _Hall_Period_Init_2[0],a
	mov a,rb
	mov _Hall_Period_Init_2[1],a
	call _Hall_Period_Init
_L6:
#line 66 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,[35]
	mov ra,a
	mov a,16
	andm a,ra
	snz ra
	jmp _L7
#line 67 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,40
	mov _pwm_duty[0],a
	clr _pwm_duty[1]
	jmp _L8
_L7:
#line 69 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,20
	mov _pwm_duty[0],a
	clr _pwm_duty[1]
_L8:
#line 71 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
;# 71 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c" 1
	clr wdt
#line 72 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	jmp _L9
	jmp $
_main endp

@dummy proc
	call _main
@dummy endp

#line 72 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
#pragma debug scope 1 1
public _Hall_Period_Init
#pragma debug scope 3 1
#line 81 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
_Hall_Period_Init .section 'code'
_Hall_Period_Init proc
public _Hall_Period_Init_2
    local _Hall_Period_Init_2 db 2 dup(?)	; 2,0
#pragma debug variable 12 3 _Hall_Period_Init_2+0 "period"
#line 82 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,_hall_period[0]
	mov ra,a
	mov a,_hall_period[1]
	mov rb,a
	mov a,ra
	or a,rb
	sz z
	jmp _L11
#line 84 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	jmp _L12
_L13:
;# 84 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c" 1
	clr wdt
_L12:
	mov a,_hall_state[0]
	mov ra,a
	mov a,_hall_state[1]
	mov rb,a
	mov a,ra
	xor a,5
	or a,rb
	snz z
	jmp _L13
#line 85 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	jmp _L14
_L15:
;# 85 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c" 1
	clr wdt
_L14:
	mov a,_hall_state[0]
	mov ra,a
	mov a,_hall_state[1]
	mov rb,a
	mov a,ra
	or a,rb
	snz z
	jmp _L15
_L11:
#line 88 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,_Hall_Period_Init_2[0]
	mov _hall_period[0],a
	mov a,_Hall_Period_Init_2[1]
	mov _hall_period[1],a
	mov a,_hall_period[0]
	mov ra,a
	mov a,_hall_period[1]
	mov rb,a
	rrca intc
	clr intc.0
	mov a,ra
	mov mduwr0,a
	mov a,rb
	mov mduwr1,a
	mov a,6
	mov mduwr4,a
	mov a,0
	mov mduwr5,a
	mov a,6
_LI1:
	sdz acc
	jmp _LI1
	mov a,mduwr0
	mov ra,a
	mov a,mduwr1
	mov rb,a
	sz c
	set intc.0
	mov a,ra
	mov _hall_60d[0],a
	mov a,rb
	mov _hall_60d[1],a
	mov a,_hall_period[0]
	mov ra,a
	mov a,_hall_period[1]
	mov rb,a
	rrca intc
	clr intc.0
	mov a,ra
	mov mduwr0,a
	mov a,rb
	mov mduwr1,a
	mov a,3
	mov mduwr4,a
	mov a,0
	mov mduwr5,a
	mov a,6
_LI2:
	sdz acc
	jmp _LI2
	mov a,mduwr0
	mov ra,a
	mov a,mduwr1
	mov rb,a
	sz c
	set intc.0
	mov a,ra
	mov _hall_120d[0],a
	mov a,rb
	mov _hall_120d[1],a
	mov a,_hall_period[0]
	mov ra,a
	mov a,_hall_period[1]
	mov rb,a
	clr c
	rrc rb
	rrc ra
	mov a,ra
	mov _hall_180d[0],a
	mov a,rb
	mov _hall_180d[1],a
#line 89 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,_hall_120d[0]
	mov ra,a
	mov a,_hall_120d[1]
	mov rb,a
	clr c
	rlc ra
	rlc rb
	mov a,ra
	mov _hall_240d[0],a
	mov a,rb
	mov _hall_240d[1],a
	mov a,_hall_180d[0]
	mov rc,a
	mov a,_hall_180d[1]
	mov rd,a
	mov a,_hall_120d[0]
	mov ra,a
	mov a,_hall_120d[1]
	mov rb,a
	mov a,rc
	addm a,ra
	mov a,rd
	adcm a,rb
	mov a,ra
	mov _hall_300d[0],a
	mov a,rb
	mov _hall_300d[1],a
	ret
_Hall_Period_Init endp
#line 89 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
#pragma debug scope 1 1
___pb equ [38]
___pbc equ [39]
___papu equ [34]
___pac equ [36]
public _IO_Init
#pragma debug scope 4 1
#line 94 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
_IO_Init .section 'code'
_IO_Init proc
#line 96 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	clr [38].0
#line 97 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	clr [39].0
#line 98 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	clr [38].1
#line 99 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	clr [39].1
#line 100 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	clr [38].2
#line 101 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	clr [39].2
#line 104 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	set [35].3
	set [35].4
#line 105 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	set [34].3
	set [34].4
#line 106 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	set [36].3
	set [36].4
#line 109 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	clr [35].5
#line 110 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	clr [36].5
	ret
_IO_Init endp
#line 110 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
#pragma debug scope 1 1
___ptm1c0 equ [327]
___ptm1c1 equ [328]
___ptm1al equ [331]
___ptm1ah equ [332]
___intc2 equ [23]
___mfi5 equ [30]
public _TM1_Init
#pragma debug scope 5 1
#line 114 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
_TM1_Init .section 'code'
_TM1_Init proc
#line 115 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,32
	lmov [327],a
#line 116 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,193
	lmov [328],a
#line 118 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,10
	lmov [331],a
#line 119 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	lclr [332]
#line 121 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	clr [23].7
#line 122 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	clr [30].5
#line 123 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	set [30].1
#line 124 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	set [23].3
#line 126 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	lclr [327].3
#line 127 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	lset [327].3
	ret
_TM1_Init endp
#line 127 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
#pragma debug scope 1 1
public _ISR_TM1
#pragma debug scope 6 1
#line 131 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
@ISR_TM1_code .section at 44 'code'
ifdef INTERRUPT_DELAY
	nop
endif
	mov r1,a
	mov a,status
ifndef INTERRUPT_DELAY
	mov r2,a
endif
	jmp _ISR_TM1
#pragma debug scope 1 1
@dummy44 proc
	call _ISR_TM1
@dummy44 endp
#pragma debug scope 7 1
_ISR_TM1 .section 'code'
_ISR_TM1 proc
ifdef INTERRUPT_DELAY
	mov r2,a
endif
#line 132 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
;# 132 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c" 1
	clr wdt
#line 134 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,_cnt_pwm_period[0]
	mov ra,a
	mov a,_cnt_pwm_period[1]
	mov rb,a
	inc ra
	sz z
	inc rb
	mov a,ra
	mov _cnt_pwm_period[0],a
	mov a,rb
	mov _cnt_pwm_period[1],a
	mov a,_pwm_period[0]
	mov rc,a
	mov a,_pwm_period[1]
	mov rd,a
	mov a,ra
	sub a,rc
	mov a,rb
	sbc a,rd
	snz c
	jmp _L19
#line 135 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	clr _cnt_pwm_period[0]
	clr _cnt_pwm_period[1]
_L19:
#line 137 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,_cnt_pwm_period[0]
	mov rc,a
	mov a,_cnt_pwm_period[1]
	mov rd,a
	mov a,_pwm_duty[0]
	mov ra,a
	mov a,_pwm_duty[1]
	mov rb,a
	mov a,rc
	sub a,ra
	mov a,rd
	sbc a,rb
	sz c
	jmp _L20
#line 138 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	set [35].5
	jmp _L21
_L20:
#line 140 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	clr [35].5
_L21:
#line 142 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,_cnt_hall_period[0]
	mov ra,a
	mov a,_cnt_hall_period[1]
	mov rb,a
	inc ra
	sz z
	inc rb
	mov a,ra
	mov _cnt_hall_period[0],a
	mov a,rb
	mov _cnt_hall_period[1],a
	mov a,_hall_period[0]
	mov rc,a
	mov a,_hall_period[1]
	mov rd,a
	mov a,ra
	sub a,rc
	mov a,rb
	sbc a,rd
	snz c
	jmp _L22
#line 143 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	clr _cnt_hall_period[0]
	clr _cnt_hall_period[1]
_L22:
#line 145 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,_hall_state[0]
	mov ra,a
	mov a,_hall_state[1]
	mov rb,a
	mov a,ra
	or a,rb
	sz z
	jmp _L24
	mov a,ra
	xor a,1
	or a,rb
	sz z
	jmp _L25
	mov a,ra
	xor a,2
	or a,rb
	sz z
	jmp _L26
	mov a,ra
	xor a,3
	or a,rb
	sz z
	jmp _L27
	mov a,ra
	xor a,4
	or a,rb
	sz z
	jmp _L28
	mov a,ra
	xor a,5
	or a,rb
	sz z
	jmp _L29
	jmp _L37
_L24:
#line 148 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,_hall_60d[0]
	mov ra,a
	mov a,_hall_60d[1]
	mov rb,a
	mov a,255
	add a,ra
	mov rc,a
	mov a,255
	adc a,rb
	mov rd,a
	mov a,_cnt_hall_period[0]
	mov ra,a
	mov a,_cnt_hall_period[1]
	mov rb,a
	mov a,rc
	sub a,ra
	mov a,rd
	sbc a,rb
	snz cz
	jmp _L30
#line 150 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	set [38].0
	clr [38].1
	clr [38].2
#line 151 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,1
	mov _hall_state[0],a
	clr _hall_state[1]
#line 153 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	jmp _L31
_L30:
	jmp _L31
_L25:
#line 155 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,_hall_120d[0]
	mov ra,a
	mov a,_hall_120d[1]
	mov rb,a
	mov a,255
	add a,ra
	mov rc,a
	mov a,255
	adc a,rb
	mov rd,a
	mov a,_cnt_hall_period[0]
	mov ra,a
	mov a,_cnt_hall_period[1]
	mov rb,a
	mov a,rc
	sub a,ra
	mov a,rd
	sbc a,rb
	snz cz
	jmp _L32
#line 157 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	set [38].0
	set [38].1
	clr [38].2
#line 158 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,2
	mov _hall_state[0],a
	clr _hall_state[1]
#line 160 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	jmp _L31
_L32:
	jmp _L31
_L26:
#line 162 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,_hall_180d[0]
	mov ra,a
	mov a,_hall_180d[1]
	mov rb,a
	mov a,255
	add a,ra
	mov rc,a
	mov a,255
	adc a,rb
	mov rd,a
	mov a,_cnt_hall_period[0]
	mov ra,a
	mov a,_cnt_hall_period[1]
	mov rb,a
	mov a,rc
	sub a,ra
	mov a,rd
	sbc a,rb
	snz cz
	jmp _L33
#line 164 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	clr [38].0
	set [38].1
	clr [38].2
#line 165 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,3
	mov _hall_state[0],a
	clr _hall_state[1]
#line 167 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	jmp _L31
_L33:
	jmp _L31
_L27:
#line 169 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,_hall_240d[0]
	mov ra,a
	mov a,_hall_240d[1]
	mov rb,a
	mov a,255
	add a,ra
	mov rc,a
	mov a,255
	adc a,rb
	mov rd,a
	mov a,_cnt_hall_period[0]
	mov ra,a
	mov a,_cnt_hall_period[1]
	mov rb,a
	mov a,rc
	sub a,ra
	mov a,rd
	sbc a,rb
	snz cz
	jmp _L34
#line 171 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	clr [38].0
	set [38].1
	set [38].2
#line 172 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,4
	mov _hall_state[0],a
	clr _hall_state[1]
#line 174 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	jmp _L31
_L34:
	jmp _L31
_L28:
#line 176 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,_hall_300d[0]
	mov ra,a
	mov a,_hall_300d[1]
	mov rb,a
	mov a,255
	add a,ra
	mov rc,a
	mov a,255
	adc a,rb
	mov rd,a
	mov a,_cnt_hall_period[0]
	mov ra,a
	mov a,_cnt_hall_period[1]
	mov rb,a
	mov a,rc
	sub a,ra
	mov a,rd
	sbc a,rb
	snz cz
	jmp _L35
#line 178 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	clr [38].0
	clr [38].1
	set [38].2
#line 179 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,5
	mov _hall_state[0],a
	clr _hall_state[1]
#line 181 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	jmp _L31
_L35:
	jmp _L31
_L29:
#line 183 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,_hall_period[0]
	mov ra,a
	mov a,_hall_period[1]
	mov rb,a
	mov a,255
	add a,ra
	mov rc,a
	mov a,255
	adc a,rb
	mov rd,a
	mov a,_cnt_hall_period[0]
	mov ra,a
	mov a,_cnt_hall_period[1]
	mov rb,a
	mov a,rc
	sub a,ra
	mov a,rd
	sbc a,rb
	snz cz
	jmp _L36
#line 185 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	set [38].0
	clr [38].1
	set [38].2
#line 186 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	clr _hall_state[0]
	clr _hall_state[1]
#line 188 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	jmp _L31
_L36:
	jmp _L31
_L37:
#line 190 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	clr [38].0
	clr [38].1
	clr [38].2
#line 191 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	;nop
_L31:
#line 194 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	clr [23].7
#line 195 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	clr [30].5
	mov a,r2
	mov status,a
	mov a,r1
	reti
_ISR_TM1 endp

#line 195 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
#pragma debug scope 1 1
___tbc equ [275]
___mfi7 equ [32]
___intc3 equ [24]
public _TimeBase_Init
#pragma debug scope 8 1
#line 199 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
_TimeBase_Init .section 'code'
_TimeBase_Init proc
#line 200 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,192
	lmov [275],a
#line 201 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	set [32].3
#line 202 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	clr [32].7
#line 203 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	set [24].3
#line 204 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	clr [24].7
	ret
_TimeBase_Init endp
#line 204 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
#pragma debug scope 1 1
public _ISR_TimeBase
#pragma debug scope 9 1
#line 208 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
@ISR_TimeBase_code .section at 60 'code'
ifdef INTERRUPT_DELAY
	nop
endif
	mov r1,a
	mov a,status
ifndef INTERRUPT_DELAY
	mov r2,a
endif
	jmp _ISR_TimeBase
#pragma debug scope 1 1
@dummy60 proc
	call _ISR_TimeBase
@dummy60 endp
#pragma debug scope 10 1
_ISR_TimeBase .section 'code'
_ISR_TimeBase proc
ifdef INTERRUPT_DELAY
	mov r2,a
endif
#line 209 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
;# 209 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c" 1
	clr wdt
#line 210 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,_cnt_1ms[0]
	mov ra,a
	mov a,_cnt_1ms[1]
	mov rb,a
	mov a,ra
	or a,rb
	sz z
	jmp _L40
#line 211 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,_cnt_1ms[0]
	mov ra,a
	mov a,_cnt_1ms[1]
	mov rb,a
	mov a,255
	addm a,ra
	mov a,255
	adcm a,rb
	mov a,ra
	mov _cnt_1ms[0],a
	mov a,rb
	mov _cnt_1ms[1],a
_L40:
#line 212 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	clr [24].7
#line 213 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	clr [32].7
	mov a,r2
	mov status,a
	mov a,r1
	reti
_ISR_TimeBase endp

#line 213 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
#pragma debug scope 1 1
___opoms equ [366]
___opa0cal equ [368]
___opcm equ [367]
___cmpc equ [114]
___mptc1 equ [75]
___ocps equ [68]
public _Comparator_Init
#pragma debug scope 11 1
#line 223 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
_Comparator_Init .section 'code'
_Comparator_Init proc
#line 224 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,67
	lmov [366],a
#line 225 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,48
	lmov [368],a
#line 227 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,30
	lmov [367],a
#line 228 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	set [114].0
#line 229 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	set [75].3
#line 230 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	clr [75].0
#line 231 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	set [75].0
#line 232 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	mov a,42
	mov [68],a
#line 233 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	set [21].2
#line 234 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	clr [21].5
	ret
_Comparator_Init endp
#line 234 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
#pragma debug scope 1 1
public _ISR_OCP
#pragma debug scope 12 1
#line 242 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
@ISR_OCP_code .section at 8 'code'
ifdef INTERRUPT_DELAY
	nop
endif
	mov r1,a
	mov a,status
ifndef INTERRUPT_DELAY
	mov r2,a
endif
	jmp _ISR_OCP
#pragma debug scope 1 1
@dummy8 proc
	call _ISR_OCP
@dummy8 endp
#pragma debug scope 13 1
_ISR_OCP .section 'code'
_ISR_OCP proc
ifdef INTERRUPT_DELAY
	mov r2,a
endif
#line 243 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
	clr [21].5
	mov a,r2
	mov status,a
	mov a,r1
	reti
_ISR_OCP endp

#line 243 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
#pragma debug scope 1 1
#pragma debug struct_begin 42 "__intc0_bits"
#pragma debug field 21 8 0 1 "__emi" ;0,1
#pragma debug field 21 8 0 1 "__int_pri1e" ;1,1
#pragma debug field 21 8 0 1 "__int_pri2e" ;2,1
#pragma debug field 21 8 0 1 "__int_pri3e" ;3,1
#pragma debug field 21 8 0 1 "__int_pri1f" ;4,1
#pragma debug field 21 8 0 1 "__int_pri2f" ;5,1
#pragma debug field 21 8 0 1 "__int_pri3f" ;6,1
#pragma debug field 21 8 0 1 ;7,1
#pragma debug struct_end
#pragma debug union_begin 43 ""
#pragma debug field 2 42 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 43 1 ___intc0 "__intc0" 1
#pragma debug struct_begin 44 "__intc2_bits"
#pragma debug field 21 8 0 1 "__int_pri8e" ;0,1
#pragma debug field 21 8 0 1 "__int_pri9e" ;1,1
#pragma debug field 21 8 0 1 "__int_pri10e" ;2,1
#pragma debug field 21 8 0 1 "__int_pri11e" ;3,1
#pragma debug field 21 8 0 1 "__int_pri8f" ;4,1
#pragma debug field 21 8 0 1 "__int_pri9f" ;5,1
#pragma debug field 21 8 0 1 "__int_pri10f" ;6,1
#pragma debug field 21 8 0 1 "__int_pri11f" ;7,1
#pragma debug struct_end
#pragma debug union_begin 45 ""
#pragma debug field 2 44 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 45 1 ___intc2 "__intc2" 1
#pragma debug struct_begin 46 "__intc3_bits"
#pragma debug field 21 8 0 1 "__int_pri12e" ;0,1
#pragma debug field 21 8 0 1 "__int_pri13e" ;1,1
#pragma debug field 21 8 0 1 "__int_pri14e" ;2,1
#pragma debug field 21 8 0 1 "__int_pri15e" ;3,1
#pragma debug field 21 8 0 1 "__int_pri12f" ;4,1
#pragma debug field 21 8 0 1 "__int_pri13f" ;5,1
#pragma debug field 21 8 0 1 "__int_pri14f" ;6,1
#pragma debug field 21 8 0 1 "__int_pri15f" ;7,1
#pragma debug struct_end
#pragma debug union_begin 47 ""
#pragma debug field 2 46 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 47 1 ___intc3 "__intc3" 1
#pragma debug struct_begin 48 "__mfi5_bits"
#pragma debug field 21 8 0 1 "__tm1pe" ;0,1
#pragma debug field 21 8 0 1 "__tm1ae" ;1,1
#pragma debug field 21 8 0 2 ;2,2
#pragma debug field 21 8 0 1 "__tm1pf" ;4,1
#pragma debug field 21 8 0 1 "__tm1af" ;5,1
#pragma debug field 21 8 0 2 ;6,2
#pragma debug struct_end
#pragma debug union_begin 49 ""
#pragma debug field 2 48 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 49 1 ___mfi5 "__mfi5" 1
#pragma debug struct_begin 50 "__mfi7_bits"
#pragma debug field 21 8 0 1 "__iice" ;0,1
#pragma debug field 21 8 0 1 "__uarte" ;1,1
#pragma debug field 21 8 0 1 "__lve" ;2,1
#pragma debug field 21 8 0 1 "__tbe" ;3,1
#pragma debug field 21 8 0 1 "__iicf" ;4,1
#pragma debug field 21 8 0 1 "__uartf" ;5,1
#pragma debug field 21 8 0 1 "__lvf" ;6,1
#pragma debug field 21 8 0 1 "__tbf" ;7,1
#pragma debug struct_end
#pragma debug union_begin 51 ""
#pragma debug field 2 50 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 51 1 ___mfi7 "__mfi7" 1
#pragma debug struct_begin 52 "__papu_bits"
#pragma debug field 21 8 0 1 "__papu0" ;0,1
#pragma debug field 21 8 0 1 "__papu1" ;1,1
#pragma debug field 21 8 0 1 "__papu2" ;2,1
#pragma debug field 21 8 0 1 "__papu3" ;3,1
#pragma debug field 21 8 0 1 "__papu4" ;4,1
#pragma debug field 21 8 0 1 "__papu5" ;5,1
#pragma debug field 21 8 0 1 "__papu6" ;6,1
#pragma debug field 21 8 0 1 "__papu7" ;7,1
#pragma debug struct_end
#pragma debug union_begin 53 ""
#pragma debug field 2 52 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 53 1 ___papu "__papu" 1
#pragma debug struct_begin 54 "__pa_bits"
#pragma debug field 21 8 0 1 "__pa0" ;0,1
#pragma debug field 21 8 0 1 "__pa1" ;1,1
#pragma debug field 21 8 0 1 "__pa2" ;2,1
#pragma debug field 21 8 0 1 "__pa3" ;3,1
#pragma debug field 21 8 0 1 "__pa4" ;4,1
#pragma debug field 21 8 0 1 "__pa5" ;5,1
#pragma debug field 21 8 0 1 "__pa6" ;6,1
#pragma debug field 21 8 0 1 "__pa7" ;7,1
#pragma debug struct_end
#pragma debug union_begin 55 ""
#pragma debug field 2 54 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 55 1 ___pa "__pa" 1
#pragma debug struct_begin 56 "__pac_bits"
#pragma debug field 21 8 0 1 "__pac0" ;0,1
#pragma debug field 21 8 0 1 "__pac1" ;1,1
#pragma debug field 21 8 0 1 "__pac2" ;2,1
#pragma debug field 21 8 0 1 "__pac3" ;3,1
#pragma debug field 21 8 0 1 "__pac4" ;4,1
#pragma debug field 21 8 0 1 "__pac5" ;5,1
#pragma debug field 21 8 0 1 "__pac6" ;6,1
#pragma debug field 21 8 0 1 "__pac7" ;7,1
#pragma debug struct_end
#pragma debug union_begin 57 ""
#pragma debug field 2 56 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 57 1 ___pac "__pac" 1
#pragma debug struct_begin 58 "__pb_bits"
#pragma debug field 21 8 0 1 "__pb0" ;0,1
#pragma debug field 21 8 0 1 "__pb1" ;1,1
#pragma debug field 21 8 0 1 "__pb2" ;2,1
#pragma debug field 21 8 0 1 "__pb3" ;3,1
#pragma debug field 21 8 0 1 "__pb4" ;4,1
#pragma debug field 21 8 0 1 "__pb5" ;5,1
#pragma debug field 21 8 0 1 "__pb6" ;6,1
#pragma debug field 21 8 0 1 "__pb7" ;7,1
#pragma debug struct_end
#pragma debug union_begin 59 ""
#pragma debug field 2 58 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 59 1 ___pb "__pb" 1
#pragma debug struct_begin 60 "__pbc_bits"
#pragma debug field 21 8 0 1 "__pbc0" ;0,1
#pragma debug field 21 8 0 1 "__pbc1" ;1,1
#pragma debug field 21 8 0 1 "__pbc2" ;2,1
#pragma debug field 21 8 0 1 "__pbc3" ;3,1
#pragma debug field 21 8 0 1 "__pbc4" ;4,1
#pragma debug field 21 8 0 1 "__pbc5" ;5,1
#pragma debug field 21 8 0 1 "__pbc6" ;6,1
#pragma debug field 21 8 0 1 "__pbc7" ;7,1
#pragma debug struct_end
#pragma debug union_begin 61 ""
#pragma debug field 2 60 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 61 1 ___pbc "__pbc" 1
#pragma debug struct_begin 62 "__ocps_bits"
#pragma debug field 21 8 0 1 "__ocpat" ;0,1
#pragma debug field 21 8 0 1 "__ocpab" ;1,1
#pragma debug field 21 8 0 1 "__ocpbt" ;2,1
#pragma debug field 21 8 0 1 "__ocpbb" ;3,1
#pragma debug field 21 8 0 1 "__ocpct" ;4,1
#pragma debug field 21 8 0 1 "__ocpcb" ;5,1
#pragma debug field 21 8 0 2 ;6,2
#pragma debug struct_end
#pragma debug union_begin 63 ""
#pragma debug field 2 62 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 63 1 ___ocps "__ocps" 1
#pragma debug struct_begin 64 "__mptc1_bits"
#pragma debug field 21 8 0 1 "__ocpse" ;0,1
#pragma debug field 21 8 0 1 ;1,1
#pragma debug field 21 8 0 1 "__ahlhe" ;2,1
#pragma debug field 21 8 0 1 "__ishe" ;3,1
#pragma debug field 21 8 0 1 "__capche" ;4,1
#pragma debug field 21 8 0 1 "__capohe" ;5,1
#pragma debug field 21 8 0 1 "__pswe" ;6,1
#pragma debug field 21 8 0 1 "__pswd" ;7,1
#pragma debug struct_end
#pragma debug union_begin 65 ""
#pragma debug field 2 64 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 65 1 ___mptc1 "__mptc1" 1
#pragma debug struct_begin 66 "__cmpc_bits"
#pragma debug field 21 8 0 1 "__c0en" ;0,1
#pragma debug field 21 8 0 1 "__c1en" ;1,1
#pragma debug field 21 8 0 1 "__c2en" ;2,1
#pragma debug field 21 8 0 1 "__c3en" ;3,1
#pragma debug field 21 8 0 1 "__c0hyen" ;4,1
#pragma debug field 21 8 0 1 "__c1hyen" ;5,1
#pragma debug field 21 8 0 1 "__c2hyen" ;6,1
#pragma debug field 21 8 0 1 "__c3hyen" ;7,1
#pragma debug struct_end
#pragma debug union_begin 67 ""
#pragma debug field 2 66 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 67 1 ___cmpc "__cmpc" 1
#pragma debug struct_begin 68 "__tbc_bits"
#pragma debug field 21 8 0 4 ;0,4
#pragma debug field 21 8 0 1 "__tb0" ;4,1
#pragma debug field 21 8 0 1 "__tb1" ;5,1
#pragma debug field 21 8 0 1 "__tbck" ;6,1
#pragma debug field 21 8 0 1 "__tbon" ;7,1
#pragma debug struct_end
#pragma debug union_begin 69 ""
#pragma debug field 2 68 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 69 1 ___tbc "__tbc" 1
#pragma debug struct_begin 70 "__ptm1c0_bits"
#pragma debug field 21 8 0 3 ;0,3
#pragma debug field 21 8 0 1 "__pt1on" ;3,1
#pragma debug field 21 8 0 1 "__pt1ck0" ;4,1
#pragma debug field 21 8 0 1 "__pt1ck1" ;5,1
#pragma debug field 21 8 0 1 "__pt1ck2" ;6,1
#pragma debug field 21 8 0 1 "__pt1pau" ;7,1
#pragma debug struct_end
#pragma debug union_begin 71 ""
#pragma debug field 2 70 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 71 1 ___ptm1c0 "__ptm1c0" 1
#pragma debug struct_begin 72 "__ptm1c1_bits"
#pragma debug field 21 8 0 1 "__pt1cclr" ;0,1
#pragma debug field 21 8 0 1 "__pt1capts" ;1,1
#pragma debug field 21 8 0 1 "__pt1pol" ;2,1
#pragma debug field 21 8 0 1 "__pt1oc" ;3,1
#pragma debug field 21 8 0 1 "__pt1io0" ;4,1
#pragma debug field 21 8 0 1 "__pt1io1" ;5,1
#pragma debug field 21 8 0 1 "__pt1m0" ;6,1
#pragma debug field 21 8 0 1 "__pt1m1" ;7,1
#pragma debug struct_end
#pragma debug union_begin 73 ""
#pragma debug field 2 72 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 73 1 ___ptm1c1 "__ptm1c1" 1
#pragma debug variable 8 1 ___ptm1al "__ptm1al" 1
#pragma debug variable 8 1 ___ptm1ah "__ptm1ah" 1
#pragma debug struct_begin 74 "__opoms_bits"
#pragma debug field 21 8 0 1 "__opa0vs0" ;0,1
#pragma debug field 21 8 0 1 "__opa0vs1" ;1,1
#pragma debug field 21 8 0 1 "__opa0vs2" ;2,1
#pragma debug field 21 8 0 3 ;3,3
#pragma debug field 21 8 0 1 "__cmp0_eg0" ;6,1
#pragma debug field 21 8 0 1 "__cmp0_eg1" ;7,1
#pragma debug struct_end
#pragma debug union_begin 75 ""
#pragma debug field 2 74 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 75 1 ___opoms "__opoms" 1
#pragma debug variable 8 1 ___opcm "__opcm" 1
#pragma debug struct_begin 76 "__opa0cal_bits"
#pragma debug field 21 8 0 1 "__a0of0" ;0,1
#pragma debug field 21 8 0 1 "__a0of1" ;1,1
#pragma debug field 21 8 0 1 "__a0of2" ;2,1
#pragma debug field 21 8 0 1 "__a0of3" ;3,1
#pragma debug field 21 8 0 1 "__a0of4" ;4,1
#pragma debug field 21 8 0 1 "__a0ofm" ;5,1
#pragma debug field 21 8 0 1 "__a0rs" ;6,1
#pragma debug field 21 8 0 1 ;7,1
#pragma debug struct_end
#pragma debug union_begin 77 ""
#pragma debug field 2 76 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 77 1 ___opa0cal "__opa0cal" 1
extern r1:byte
extern r2:byte
#line 34 "D:\WORK\Project\Github\Holtel-MCU\Code\HT66FM5440\hall_emulator\hall_emu.c"
@code .section at 0 'code'
	jmp _main_startup1


; 
; Generated by holtek-gcc v3.19, Thu Aug 01 10:51:02 2019
; Rebuild 115
; end of file
