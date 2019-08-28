//	[VERSION] 1.4, 4
// Do not modify manually.

#ifndef _HT66FM5240_H_
#define _HT66FM5240_H_

#ifndef __DISABLE_HGCC_BUILD_IN__
#include "build-in.h"
#endif

#define DEFINE_ISR(isr_name, vector) void __attribute((interrupt(vector))) isr_name(void)

#define DEFINE_SFR(sfr_type, sfr, addr) static volatile sfr_type sfr __attribute__ ((at(addr)))

typedef unsigned char __sfr_byte;

//***********************************//
typedef struct {
	unsigned char __dmbp0 : 1;
	unsigned char : 7;
} __bp_bits;

typedef union {
	__bp_bits bits;
	__sfr_byte byte;
} __bp_type;

//***********************************//
typedef struct {
	unsigned char __c : 1;
	unsigned char __ac : 1;
	unsigned char __z : 1;
	unsigned char __ov : 1;
	unsigned char __pdf : 1;
	unsigned char __to : 1;
	unsigned char : 2;
} __status_bits;

typedef union {
	__status_bits bits;
	__sfr_byte byte;
} __status_type;

//***********************************//
typedef struct {
	unsigned char __hlclk : 1;
	unsigned char __idlen : 1;
	unsigned char __hto : 1;
	unsigned char __lto : 1;
	unsigned char : 1;
	unsigned char __cks0 : 1;
	unsigned char __cks1 : 1;
	unsigned char __cks2 : 1;
} __smod_bits;

typedef union {
	__smod_bits bits;
	__sfr_byte byte;
} __smod_type;

//***********************************//
typedef struct {
	unsigned char __vlvd0 : 1;
	unsigned char __vlvd1 : 1;
	unsigned char __vlvd2 : 1;
	unsigned char : 1;
	unsigned char __lvden : 1;
	unsigned char __lvdo : 1;
	unsigned char : 2;
} __lvdc_bits;

typedef union {
	__lvdc_bits bits;
	__sfr_byte byte;
} __lvdc_type;

typedef struct {
	unsigned char __lvs0 : 1;
	unsigned char __lvs1 : 1;
	unsigned char __lvs2 : 1;
	unsigned char __lvs3 : 1;
	unsigned char __lvs4 : 1;
	unsigned char __lvs5 : 1;
	unsigned char __lvs6 : 1;
	unsigned char __lvs7 : 1;
} __lvrc_bits;

typedef union {
	__lvrc_bits bits;
	__sfr_byte byte;
} __lvrc_type;

//***********************************//
typedef struct {
	unsigned char __ws0 : 1;
	unsigned char __ws1 : 1;
	unsigned char __ws2 : 1;
	unsigned char __we0 : 1;
	unsigned char __we1 : 1;
	unsigned char __we2 : 1;
	unsigned char __we3 : 1;
	unsigned char __we4 : 1;
} __wdtc_bits;

typedef union {
	__wdtc_bits bits;
	__sfr_byte byte;
} __wdtc_type;

//***********************************//
typedef struct {
	unsigned char : 4;
	unsigned char __tb0 : 1;
	unsigned char __tb1 : 1;
	unsigned char __tbck : 1;
	unsigned char __tbon : 1;
} __tbc_bits;

typedef union {
	__tbc_bits bits;
	__sfr_byte byte;
} __tbc_type;

//***********************************//
typedef struct {
	unsigned char __int1s0 : 1;
	unsigned char __int1s1 : 1;
	unsigned char : 6;
} __integ1_bits;

typedef union {
	__integ1_bits bits;
	__sfr_byte byte;
} __integ1_type;

//***********************************//
typedef struct {
	unsigned char __emi : 1;
	unsigned char __halle_mf0e : 1;
	unsigned char __int1e : 1;
	unsigned char __c0e : 1;
	unsigned char __hallf_mf0f : 1;
	unsigned char __int1f : 1;
	unsigned char __c0f : 1;
	unsigned char : 1;
} __intc0_bits;

typedef union {
	__intc0_bits bits;
	__sfr_byte byte;
} __intc0_type;

typedef struct {
	unsigned char __nfie : 1;
	unsigned char __mf1e : 1;
	unsigned char __lvde : 1;
	unsigned char __epwe : 1;
	unsigned char __nfif : 1;
	unsigned char __mf1f : 1;
	unsigned char __lvdf : 1;
	unsigned char __epwf : 1;
} __intc1_bits;

typedef union {
	__intc1_bits bits;
	__sfr_byte byte;
} __intc1_type;

typedef struct {
	unsigned char __mf2e : 1;
	unsigned char __mf3e : 1;
	unsigned char __mf4e : 1;
	unsigned char __mf5e : 1;
	unsigned char __mf2f : 1;
	unsigned char __mf3f : 1;
	unsigned char __mf4f : 1;
	unsigned char __mf5f : 1;
} __intc2_bits;

typedef union {
	__intc2_bits bits;
	__sfr_byte byte;
} __intc2_type;

typedef struct {
	unsigned char __iice : 1;
	unsigned char __uarte : 1;
	unsigned char __mf6e : 1;
	unsigned char __tbe : 1;
	unsigned char __iicf : 1;
	unsigned char __uartf : 1;
	unsigned char __mf6f : 1;
	unsigned char __tbf : 1;
} __intc3_bits;

typedef union {
	__intc3_bits bits;
	__sfr_byte byte;
} __intc3_type;

//***********************************//
typedef struct {
	unsigned char __halae : 1;
	unsigned char __halbe : 1;
	unsigned char __halce : 1;
	unsigned char : 1;
	unsigned char __halaf : 1;
	unsigned char __halbf : 1;
	unsigned char __halcf : 1;
	unsigned char : 1;
} __mfi0_bits;

typedef union {
	__mfi0_bits bits;
	__sfr_byte byte;
} __mfi0_type;

typedef struct {
	unsigned char __aeoce : 1;
	unsigned char __alime : 1;
	unsigned char __capoe : 1;
	unsigned char __capce : 1;
	unsigned char __aeocf : 1;
	unsigned char __alimf : 1;
	unsigned char __capof : 1;
	unsigned char __capcf : 1;
} __mfi1_bits;

typedef union {
	__mfi1_bits bits;
	__sfr_byte byte;
} __mfi1_type;

typedef struct {
	unsigned char __pwmd0e : 1;
	unsigned char __pwmd1e : 1;
	unsigned char __pwmd2e : 1;
	unsigned char __pwmpe : 1;
	unsigned char __pwmd0f : 1;
	unsigned char __pwmd1f : 1;
	unsigned char __pwmd2f : 1;
	unsigned char __pwmpf : 1;
} __mfi2_bits;

typedef union {
	__mfi2_bits bits;
	__sfr_byte byte;
} __mfi2_type;

typedef struct {
	unsigned char __tm2pe : 1;
	unsigned char __tm2ae : 1;
	unsigned char : 2;
	unsigned char __tm2pf : 1;
	unsigned char __tm2af : 1;
	unsigned char : 2;
} __mfi3_bits;

typedef union {
	__mfi3_bits bits;
	__sfr_byte byte;
} __mfi3_type;

typedef struct {
	unsigned char __tm0pe : 1;
	unsigned char __tm0ae : 1;
	unsigned char : 2;
	unsigned char __tm0pf : 1;
	unsigned char __tm0af : 1;
	unsigned char : 2;
} __mfi4_bits;

typedef union {
	__mfi4_bits bits;
	__sfr_byte byte;
} __mfi4_type;

typedef struct {
	unsigned char __tm1pe : 1;
	unsigned char __tm1ae : 1;
	unsigned char : 2;
	unsigned char __tm1pf : 1;
	unsigned char __tm1af : 1;
	unsigned char : 2;
} __mfi5_bits;

typedef union {
	__mfi5_bits bits;
	__sfr_byte byte;
} __mfi5_type;

typedef struct {
	unsigned char __tm3pe : 1;
	unsigned char __tm3ae : 1;
	unsigned char : 2;
	unsigned char __tm3pf : 1;
	unsigned char __tm3af : 1;
	unsigned char : 2;
} __mfi6_bits;

typedef union {
	__mfi6_bits bits;
	__sfr_byte byte;
} __mfi6_type;

//***********************************//
typedef struct {
	unsigned char __pawu0 : 1;
	unsigned char __pawu1 : 1;
	unsigned char __pawu2 : 1;
	unsigned char __pawu3 : 1;
	unsigned char __pawu4 : 1;
	unsigned char __pawu5 : 1;
	unsigned char __pawu6 : 1;
	unsigned char __pawu7 : 1;
} __pawu_bits;

typedef union {
	__pawu_bits bits;
	__sfr_byte byte;
} __pawu_type;

//***********************************//
typedef struct {
	unsigned char __papu0 : 1;
	unsigned char __papu1 : 1;
	unsigned char __papu2 : 1;
	unsigned char __papu3 : 1;
	unsigned char __papu4 : 1;
	unsigned char __papu5 : 1;
	unsigned char __papu6 : 1;
	unsigned char __papu7 : 1;
} __papu_bits;

typedef union {
	__papu_bits bits;
	__sfr_byte byte;
} __papu_type;

typedef struct {
	unsigned char __pa0 : 1;
	unsigned char __pa1 : 1;
	unsigned char __pa2 : 1;
	unsigned char __pa3 : 1;
	unsigned char __pa4 : 1;
	unsigned char __pa5 : 1;
	unsigned char __pa6 : 1;
	unsigned char __pa7 : 1;
} __pa_bits;

typedef union {
	__pa_bits bits;
	__sfr_byte byte;
} __pa_type;

typedef struct {
	unsigned char __pac0 : 1;
	unsigned char __pac1 : 1;
	unsigned char __pac2 : 1;
	unsigned char __pac3 : 1;
	unsigned char __pac4 : 1;
	unsigned char __pac5 : 1;
	unsigned char __pac6 : 1;
	unsigned char __pac7 : 1;
} __pac_bits;

typedef union {
	__pac_bits bits;
	__sfr_byte byte;
} __pac_type;

//***********************************//
typedef struct {
	unsigned char __pbpu0 : 1;
	unsigned char __pbpu1 : 1;
	unsigned char __pbpu2 : 1;
	unsigned char __pbpu3 : 1;
	unsigned char __pbpu4 : 1;
	unsigned char __pbpu5 : 1;
	unsigned char __pbpu6 : 1;
	unsigned char __pbpu7 : 1;
} __pbpu_bits;

typedef union {
	__pbpu_bits bits;
	__sfr_byte byte;
} __pbpu_type;

typedef struct {
	unsigned char __pb0 : 1;
	unsigned char __pb1 : 1;
	unsigned char __pb2 : 1;
	unsigned char __pb3 : 1;
	unsigned char __pb4 : 1;
	unsigned char __pb5 : 1;
	unsigned char __pb6 : 1;
	unsigned char __pb7 : 1;
} __pb_bits;

typedef union {
	__pb_bits bits;
	__sfr_byte byte;
} __pb_type;

typedef struct {
	unsigned char __pbc0 : 1;
	unsigned char __pbc1 : 1;
	unsigned char __pbc2 : 1;
	unsigned char __pbc3 : 1;
	unsigned char __pbc4 : 1;
	unsigned char __pbc5 : 1;
	unsigned char __pbc6 : 1;
	unsigned char __pbc7 : 1;
} __pbc_bits;

typedef union {
	__pbc_bits bits;
	__sfr_byte byte;
} __pbc_type;

//***********************************//
typedef struct {
	unsigned char __pcpu0 : 1;
	unsigned char __pcpu1 : 1;
	unsigned char __pcpu2 : 1;
	unsigned char __pcpu3 : 1;
	unsigned char __pcpu4 : 1;
	unsigned char __pcpu5 : 1;
	unsigned char : 2;
} __pcpu_bits;

typedef union {
	__pcpu_bits bits;
	__sfr_byte byte;
} __pcpu_type;

typedef struct {
	unsigned char __pc0 : 1;
	unsigned char __pc1 : 1;
	unsigned char __pc2 : 1;
	unsigned char __pc3 : 1;
	unsigned char __pc4 : 1;
	unsigned char __pc5 : 1;
	unsigned char : 2;
} __pc_bits;

typedef union {
	__pc_bits bits;
	__sfr_byte byte;
} __pc_type;

typedef struct {
	unsigned char __pcc0 : 1;
	unsigned char __pcc1 : 1;
	unsigned char __pcc2 : 1;
	unsigned char __pcc3 : 1;
	unsigned char __pcc4 : 1;
	unsigned char __pcc5 : 1;
	unsigned char : 2;
} __pcc_bits;

typedef union {
	__pcc_bits bits;
	__sfr_byte byte;
} __pcc_type;

//***********************************//
typedef struct {
	unsigned char __pdpu0 : 1;
	unsigned char __pdpu1 : 1;
	unsigned char __pdpu2 : 1;
	unsigned char __pdpu3 : 1;
	unsigned char : 4;
} __pdpu_bits;

typedef union {
	__pdpu_bits bits;
	__sfr_byte byte;
} __pdpu_type;

typedef struct {
	unsigned char __pd0 : 1;
	unsigned char __pd1 : 1;
	unsigned char __pd2 : 1;
	unsigned char __pd3 : 1;
	unsigned char : 4;
} __pd_bits;

typedef union {
	__pd_bits bits;
	__sfr_byte byte;
} __pd_type;

typedef struct {
	unsigned char __pdc0 : 1;
	unsigned char __pdc1 : 1;
	unsigned char __pdc2 : 1;
	unsigned char __pdc3 : 1;
	unsigned char : 4;
} __pdc_bits;

typedef union {
	__pdc_bits bits;
	__sfr_byte byte;
} __pdc_type;

//***********************************//
typedef struct {
	unsigned char __caps0 : 1;
	unsigned char __caps1 : 1;
	unsigned char : 1;
	unsigned char __capton : 1;
	unsigned char __captck0 : 1;
	unsigned char __captck1 : 1;
	unsigned char __captck2 : 1;
	unsigned char __captpau : 1;
} __captc0_bits;

typedef union {
	__captc0_bits bits;
	__sfr_byte byte;
} __captc0_type;

typedef struct {
	unsigned char __camclr : 1;
	unsigned char __capclr : 1;
	unsigned char __capfil : 1;
	unsigned char __capnfs : 1;
	unsigned char __capnft : 1;
	unsigned char __capen : 1;
	unsigned char __capeg0 : 1;
	unsigned char __capeg1 : 1;
} __captc1_bits;

typedef union {
	__captc1_bits bits;
	__sfr_byte byte;
} __captc1_type;

//***********************************//
typedef struct {
	unsigned char __acs0 : 1;
	unsigned char __acs1 : 1;
	unsigned char __acs2 : 1;
	unsigned char __acs3 : 1;
	unsigned char __adrfs : 1;
	unsigned char __adoff : 1;
	unsigned char __eocb : 1;
	unsigned char __adstr : 1;
} __adcr0_bits;

typedef union {
	__adcr0_bits bits;
	__sfr_byte byte;
} __adcr0_type;

typedef struct {
	unsigned char __adck0 : 1;
	unsigned char __adck1 : 1;
	unsigned char __adck2 : 1;
	unsigned char __adclve : 1;
	unsigned char __adchve : 1;
	unsigned char __pwis : 1;
	unsigned char __dlstr : 1;
	unsigned char __adsts : 1;
} __adcr1_bits;

typedef union {
	__adcr1_bits bits;
	__sfr_byte byte;
} __adcr1_type;

typedef struct {
	unsigned char __pwdis0 : 1;
	unsigned char __pwdis1 : 1;
	unsigned char : 6;
} __adcr2_bits;

typedef union {
	__adcr2_bits bits;
	__sfr_byte byte;
} __adcr2_type;

//***********************************//
typedef struct {
	unsigned char __pb0s0 : 1;
	unsigned char __pb0s1 : 1;
	unsigned char __pb1s0 : 1;
	unsigned char __pb1s1 : 1;
	unsigned char __pb2s0 : 1;
	unsigned char __pb2s1 : 1;
	unsigned char __pb2s2 : 1;
	unsigned char : 1;
} __pbps0_bits;

typedef union {
	__pbps0_bits bits;
	__sfr_byte byte;
} __pbps0_type;

typedef struct {
	unsigned char __pb3s0 : 1;
	unsigned char __pb3s1 : 1;
	unsigned char __pb4s0 : 1;
	unsigned char __pb4s1 : 1;
	unsigned char __pb5s0 : 1;
	unsigned char __pb5s1 : 1;
	unsigned char __pb6s0 : 1;
	unsigned char __pb6s1 : 1;
} __pbps1_bits;

typedef union {
	__pbps1_bits bits;
	__sfr_byte byte;
} __pbps1_type;

typedef struct {
	unsigned char __pb7s0 : 1;
	unsigned char __pb7s1 : 1;
	unsigned char : 6;
} __pbps2_bits;

typedef union {
	__pbps2_bits bits;
	__sfr_byte byte;
} __pbps2_type;

//***********************************//
typedef struct {
	unsigned char __intas0 : 1;
	unsigned char __intas1 : 1;
	unsigned char __intbs0 : 1;
	unsigned char __intbs1 : 1;
	unsigned char __intcs0 : 1;
	unsigned char __intcs1 : 1;
	unsigned char __hsel : 1;
	unsigned char : 1;
} __integ0_bits;

typedef union {
	__integ0_bits bits;
	__sfr_byte byte;
} __integ0_type;

//***********************************//
typedef struct {
	unsigned char __wrf : 1;
	unsigned char __lrf : 1;
	unsigned char __lvrf : 1;
	unsigned char : 4;
	unsigned char __fsyson : 1;
} __ctrl_bits;

typedef union {
	__ctrl_bits bits;
	__sfr_byte byte;
} __ctrl_type;

//***********************************//
typedef struct {
	unsigned char __hdcen : 1;
	unsigned char __frs : 1;
	unsigned char __brke : 1;
	unsigned char __hdms : 1;
	unsigned char __hals : 1;
	unsigned char __hdly_msel : 1;
	unsigned char __ctm_sel0 : 1;
	unsigned char __ctm_sel1 : 1;
} __hdcr_bits;

typedef union {
	__hdcr_bits bits;
	__sfr_byte byte;
} __hdcr_type;

//***********************************//
typedef struct {
	unsigned char __sha : 1;
	unsigned char __shb : 1;
	unsigned char __shc : 1;
	unsigned char : 5;
} __hdcd_bits;

typedef union {
	__hdcd_bits bits;
	__sfr_byte byte;
} __hdcd_type;

//***********************************//
typedef struct {
	unsigned char : 2;
	unsigned char __ahlhe : 1;
	unsigned char __ishe : 1;
	unsigned char __capche : 1;
	unsigned char __capohe : 1;
	unsigned char __pswe : 1;
	unsigned char __pswd : 1;
} __mptc1_bits;

typedef union {
	__mptc1_bits bits;
	__sfr_byte byte;
} __mptc1_type;

typedef struct {
	unsigned char __capops : 1;
	unsigned char __capcps : 1;
	unsigned char __isps : 1;
	unsigned char __ahlps : 1;
	unsigned char __pswps : 1;
	unsigned char : 3;
} __mptc2_bits;

typedef union {
	__mptc2_bits bits;
	__sfr_byte byte;
} __mptc2_type;

//***********************************//
typedef struct {
	unsigned char : 3;
	unsigned char __pt1on : 1;
	unsigned char __pt1ck0 : 1;
	unsigned char __pt1ck1 : 1;
	unsigned char __pt1ck2 : 1;
	unsigned char __pt1pau : 1;
} __ptm1c0_bits;

typedef union {
	__ptm1c0_bits bits;
	__sfr_byte byte;
} __ptm1c0_type;

typedef struct {
	unsigned char __pt1cclr : 1;
	unsigned char __pt1capts : 1;
	unsigned char __pt1pol : 1;
	unsigned char __pt1oc : 1;
	unsigned char __pt1io0 : 1;
	unsigned char __pt1io1 : 1;
	unsigned char __pt1m0 : 1;
	unsigned char __pt1m1 : 1;
} __ptm1c1_bits;

typedef union {
	__ptm1c1_bits bits;
	__sfr_byte byte;
} __ptm1c1_type;

typedef struct {
	unsigned char : 3;
	unsigned char __pt0on : 1;
	unsigned char __pt0ck0 : 1;
	unsigned char __pt0ck1 : 1;
	unsigned char __pt0ck2 : 1;
	unsigned char __pt0pau : 1;
} __ptm0c0_bits;

typedef union {
	__ptm0c0_bits bits;
	__sfr_byte byte;
} __ptm0c0_type;

typedef struct {
	unsigned char __pt0cclr : 1;
	unsigned char __pt0capts : 1;
	unsigned char __pt0pol : 1;
	unsigned char __pt0oc : 1;
	unsigned char __pt0io0 : 1;
	unsigned char __pt0io1 : 1;
	unsigned char __pt0m0 : 1;
	unsigned char __pt0m1 : 1;
} __ptm0c1_bits;

typedef union {
	__ptm0c1_bits bits;
	__sfr_byte byte;
} __ptm0c1_type;

typedef struct {
	unsigned char : 3;
	unsigned char __pt2on : 1;
	unsigned char __pt2ck0 : 1;
	unsigned char __pt2ck1 : 1;
	unsigned char __pt2ck2 : 1;
	unsigned char __pt2pau : 1;
} __ptm2c0_bits;

typedef union {
	__ptm2c0_bits bits;
	__sfr_byte byte;
} __ptm2c0_type;

typedef struct {
	unsigned char __pt2cclr : 1;
	unsigned char __pt2capts : 1;
	unsigned char __pt2pol : 1;
	unsigned char __pt2oc : 1;
	unsigned char __pt2io0 : 1;
	unsigned char __pt2io1 : 1;
	unsigned char __pt2m0 : 1;
	unsigned char __pt2m1 : 1;
} __ptm2c1_bits;

typedef union {
	__ptm2c1_bits bits;
	__sfr_byte byte;
} __ptm2c1_type;

//***********************************//
typedef struct {
	unsigned char __pwmld : 1;
	unsigned char __itcms0 : 1;
	unsigned char __itcms1 : 1;
	unsigned char __pwmon : 1;
	unsigned char __pcks0 : 1;
	unsigned char __pcks1 : 1;
	unsigned char __pwmms0 : 1;
	unsigned char __pwmms1 : 1;
} __pwmc_bits;

typedef union {
	__pwmc_bits bits;
	__sfr_byte byte;
} __pwmc_type;

typedef struct {
	unsigned char __pme0 : 1;
	unsigned char __pme1 : 1;
	unsigned char __pme2 : 1;
	unsigned char __pme3 : 1;
	unsigned char __pme4 : 1;
	unsigned char __pme5 : 1;
	unsigned char : 2;
} __pwmme_bits;

typedef union {
	__pwmme_bits bits;
	__sfr_byte byte;
} __pwmme_type;

typedef struct {
	unsigned char __pmd0 : 1;
	unsigned char __pmd1 : 1;
	unsigned char __pmd2 : 1;
	unsigned char __pmd3 : 1;
	unsigned char __pmd4 : 1;
	unsigned char __pmd5 : 1;
	unsigned char : 2;
} __pwmmd_bits;

typedef union {
	__pwmmd_bits bits;
	__sfr_byte byte;
} __pwmmd_type;

//***********************************//
typedef struct {
	unsigned char __pwms : 1;
	unsigned char __fmos : 1;
	unsigned char __mpwe : 1;
	unsigned char __mpwms : 1;
	unsigned char : 3;
	unsigned char __mskms : 1;
} __mcf_bits;

typedef union {
	__mcf_bits bits;
	__sfr_byte byte;
} __mcf_type;

typedef struct {
	unsigned char __fha : 1;
	unsigned char __fhb : 1;
	unsigned char __fhc : 1;
	unsigned char __gbt : 1;
	unsigned char __gab : 1;
	unsigned char __gat : 1;
	unsigned char : 2;
} __mcd_bits;

typedef union {
	__mcd_bits bits;
	__sfr_byte byte;
} __mcd_type;

//***********************************//
typedef struct {
	unsigned char : 5;
	unsigned char __dte : 1;
	unsigned char __dtcks0 : 1;
	unsigned char __dtcks1 : 1;
} __dts_bits;

typedef union {
	__dts_bits bits;
	__sfr_byte byte;
} __dts_type;

//***********************************//
typedef struct {
	unsigned char __patc : 1;
	unsigned char __pabc : 1;
	unsigned char __pbtc : 1;
	unsigned char __pbbc : 1;
	unsigned char __pctc : 1;
	unsigned char __pcbc : 1;
	unsigned char : 2;
} __plc_bits;

typedef union {
	__plc_bits bits;
	__sfr_byte byte;
} __plc_type;

//***********************************//
typedef struct {
	unsigned char : 1;
	unsigned char __i2cen : 1;
	unsigned char __i2cdbnc0 : 1;
	unsigned char __i2cdbnc1 : 1;
	unsigned char : 4;
} __iicc0_bits;

typedef union {
	__iicc0_bits bits;
	__sfr_byte byte;
} __iicc0_type;

typedef struct {
	unsigned char __iicrxak : 1;
	unsigned char __iicrnic : 1;
	unsigned char __iicsrw : 1;
	unsigned char __iictxak : 1;
	unsigned char __iichtx : 1;
	unsigned char __iichbb : 1;
	unsigned char __iichaas : 1;
	unsigned char __iichcf : 1;
} __iicc1_bits;

typedef union {
	__iicc1_bits bits;
	__sfr_byte byte;
} __iicc1_type;

typedef struct {
	unsigned char __iicdd0 : 1;
	unsigned char __iicdd1 : 1;
	unsigned char __iicdd2 : 1;
	unsigned char __iicdd3 : 1;
	unsigned char __iicdd4 : 1;
	unsigned char __iicdd5 : 1;
	unsigned char __iicdd6 : 1;
	unsigned char __iicdd7 : 1;
} __iicd_bits;

typedef union {
	__iicd_bits bits;
	__sfr_byte byte;
} __iicd_type;

typedef struct {
	unsigned char : 1;
	unsigned char __iica0 : 1;
	unsigned char __iica1 : 1;
	unsigned char __iica2 : 1;
	unsigned char __iica3 : 1;
	unsigned char __iica4 : 1;
	unsigned char __iica5 : 1;
	unsigned char __iica6 : 1;
} __iica_bits;

typedef union {
	__iica_bits bits;
	__sfr_byte byte;
} __iica_type;

typedef struct {
	unsigned char __i2ctos0 : 1;
	unsigned char __i2ctos1 : 1;
	unsigned char __i2ctos2 : 1;
	unsigned char __i2ctos3 : 1;
	unsigned char __i2ctos4 : 1;
	unsigned char __i2ctos5 : 1;
	unsigned char __i2ctof : 1;
	unsigned char __i2ctoen : 1;
} __i2ctoc_bits;

typedef union {
	__i2ctoc_bits bits;
	__sfr_byte byte;
} __i2ctoc_type;

//***********************************//
typedef struct {
	unsigned char __txif : 1;
	unsigned char __tidle : 1;
	unsigned char __rxif : 1;
	unsigned char __ridle : 1;
	unsigned char __oerr : 1;
	unsigned char __ferr : 1;
	unsigned char __nf : 1;
	unsigned char __perr : 1;
} __usr_bits;

typedef union {
	__usr_bits bits;
	__sfr_byte byte;
} __usr_type;

typedef struct {
	unsigned char __tx8 : 1;
	unsigned char __rx8 : 1;
	unsigned char __txbrk : 1;
	unsigned char __stops : 1;
	unsigned char __prt : 1;
	unsigned char __pren : 1;
	unsigned char __bno : 1;
	unsigned char __uarten : 1;
} __ucr1_bits;

typedef union {
	__ucr1_bits bits;
	__sfr_byte byte;
} __ucr1_type;

typedef struct {
	unsigned char __teie : 1;
	unsigned char __tiie : 1;
	unsigned char __rie : 1;
	unsigned char __wake : 1;
	unsigned char __adden : 1;
	unsigned char __brgh : 1;
	unsigned char __rxen : 1;
	unsigned char __txen : 1;
} __ucr2_bits;

typedef union {
	__ucr2_bits bits;
	__sfr_byte byte;
} __ucr2_type;

//***********************************//
typedef struct {
	unsigned char __brg0 : 1;
	unsigned char __brg1 : 1;
	unsigned char __brg2 : 1;
	unsigned char __brg3 : 1;
	unsigned char __brg4 : 1;
	unsigned char __brg5 : 1;
	unsigned char __brg6 : 1;
	unsigned char __brg7 : 1;
} __brg_bits;

typedef union {
	__brg_bits bits;
	__sfr_byte byte;
} __brg_type;

typedef struct {
	unsigned char __txrx0 : 1;
	unsigned char __txrx1 : 1;
	unsigned char __txrx2 : 1;
	unsigned char __txrx3 : 1;
	unsigned char __txrx4 : 1;
	unsigned char __txrx5 : 1;
	unsigned char __txrx6 : 1;
	unsigned char __txrx7 : 1;
} __txr_rxr_bits;

typedef union {
	__txr_rxr_bits bits;
	__sfr_byte byte;
} __txr_rxr_type;

//***********************************//
typedef struct {
	unsigned char __c0en : 1;
	unsigned char __c1en : 1;
	unsigned char __c2en : 1;
	unsigned char __c3en : 1;
	unsigned char __c0hyen : 1;
	unsigned char __c1hyen : 1;
	unsigned char __c2hyen : 1;
	unsigned char __c3hyen : 1;
} __cpc_bits;

typedef union {
	__cpc_bits bits;
	__sfr_byte byte;
} __cpc_type;

//***********************************//
typedef struct {
	unsigned char __hck_n0 : 1;
	unsigned char __hck_n1 : 1;
	unsigned char __hck_n2 : 1;
	unsigned char __hck_n3 : 1;
	unsigned char __hck_n4 : 1;
	unsigned char : 3;
} __hchk_num_bits;

typedef union {
	__hchk_num_bits bits;
	__sfr_byte byte;
} __hchk_num_type;

//***********************************//
typedef struct {
	unsigned char __hfr_sel0 : 1;
	unsigned char __hfr_sel1 : 1;
	unsigned char __hfr_sel2 : 1;
	unsigned char __hnf_en : 1;
	unsigned char : 4;
} __hnf_msel_bits;

typedef union {
	__hnf_msel_bits bits;
	__sfr_byte byte;
} __hnf_msel_type;

//***********************************//
typedef struct {
	unsigned char : 6;
	unsigned char __cins : 1;
	unsigned char __nf_byps : 1;
} __nf_vih_bits;

typedef union {
	__nf_vih_bits bits;
	__sfr_byte byte;
} __nf_vih_type;

typedef struct {
	unsigned char : 6;
	unsigned char __nfis0 : 1;
	unsigned char __nfis1 : 1;
} __nf_vil_bits;

typedef union {
	__nf_vil_bits bits;
	__sfr_byte byte;
} __nf_vil_type;

//***********************************//
typedef struct {
	unsigned char __rd : 1;
	unsigned char __rden : 1;
	unsigned char __wr : 1;
	unsigned char __wren : 1;
	unsigned char : 4;
} __eec_bits;

typedef union {
	__eec_bits bits;
	__sfr_byte byte;
} __eec_type;

//***********************************//
typedef struct {
	unsigned char __hcbd0 : 1;
	unsigned char __hctd0 : 1;
	unsigned char __hbbd0 : 1;
	unsigned char __hbtd0 : 1;
	unsigned char __habd0 : 1;
	unsigned char __hatd0 : 1;
	unsigned char : 2;
} __hdct0_bits;

typedef union {
	__hdct0_bits bits;
	__sfr_byte byte;
} __hdct0_type;

typedef struct {
	unsigned char __hcbd1 : 1;
	unsigned char __hctd1 : 1;
	unsigned char __hbbd1 : 1;
	unsigned char __hbtd1 : 1;
	unsigned char __habd1 : 1;
	unsigned char __hatd1 : 1;
	unsigned char : 2;
} __hdct1_bits;

typedef union {
	__hdct1_bits bits;
	__sfr_byte byte;
} __hdct1_type;

typedef struct {
	unsigned char __hcbd2 : 1;
	unsigned char __hctd2 : 1;
	unsigned char __hbbd2 : 1;
	unsigned char __hbtd2 : 1;
	unsigned char __habd2 : 1;
	unsigned char __hatd2 : 1;
	unsigned char : 2;
} __hdct2_bits;

typedef union {
	__hdct2_bits bits;
	__sfr_byte byte;
} __hdct2_type;

typedef struct {
	unsigned char __hcbd3 : 1;
	unsigned char __hctd3 : 1;
	unsigned char __hbbd3 : 1;
	unsigned char __hbtd3 : 1;
	unsigned char __habd3 : 1;
	unsigned char __hatd3 : 1;
	unsigned char : 2;
} __hdct3_bits;

typedef union {
	__hdct3_bits bits;
	__sfr_byte byte;
} __hdct3_type;

typedef struct {
	unsigned char __hcbd4 : 1;
	unsigned char __hctd4 : 1;
	unsigned char __hbbd4 : 1;
	unsigned char __hbtd4 : 1;
	unsigned char __habd4 : 1;
	unsigned char __hatd4 : 1;
	unsigned char : 2;
} __hdct4_bits;

typedef union {
	__hdct4_bits bits;
	__sfr_byte byte;
} __hdct4_type;

typedef struct {
	unsigned char __hcbd5 : 1;
	unsigned char __hctd5 : 1;
	unsigned char __hbbd5 : 1;
	unsigned char __hbtd5 : 1;
	unsigned char __habd5 : 1;
	unsigned char __hatd5 : 1;
	unsigned char : 2;
} __hdct5_bits;

typedef union {
	__hdct5_bits bits;
	__sfr_byte byte;
} __hdct5_type;

typedef struct {
	unsigned char __hcbd6 : 1;
	unsigned char __hctd6 : 1;
	unsigned char __hbbd6 : 1;
	unsigned char __hbtd6 : 1;
	unsigned char __habd6 : 1;
	unsigned char __hatd6 : 1;
	unsigned char : 2;
} __hdct6_bits;

typedef union {
	__hdct6_bits bits;
	__sfr_byte byte;
} __hdct6_type;

typedef struct {
	unsigned char __hcbd7 : 1;
	unsigned char __hctd7 : 1;
	unsigned char __hbbd7 : 1;
	unsigned char __hbtd7 : 1;
	unsigned char __habd7 : 1;
	unsigned char __hatd7 : 1;
	unsigned char : 2;
} __hdct7_bits;

typedef union {
	__hdct7_bits bits;
	__sfr_byte byte;
} __hdct7_type;

typedef struct {
	unsigned char __hcbd8 : 1;
	unsigned char __hctd8 : 1;
	unsigned char __hbbd8 : 1;
	unsigned char __hbtd8 : 1;
	unsigned char __habd8 : 1;
	unsigned char __hatd8 : 1;
	unsigned char : 2;
} __hdct8_bits;

typedef union {
	__hdct8_bits bits;
	__sfr_byte byte;
} __hdct8_type;

typedef struct {
	unsigned char __hcbd9 : 1;
	unsigned char __hctd9 : 1;
	unsigned char __hbbd9 : 1;
	unsigned char __hbtd9 : 1;
	unsigned char __habd9 : 1;
	unsigned char __hatd9 : 1;
	unsigned char : 2;
} __hdct9_bits;

typedef union {
	__hdct9_bits bits;
	__sfr_byte byte;
} __hdct9_type;

typedef struct {
	unsigned char __hcbd10 : 1;
	unsigned char __hctd10 : 1;
	unsigned char __hbbd10 : 1;
	unsigned char __hbtd10 : 1;
	unsigned char __habd10 : 1;
	unsigned char __hatd10 : 1;
	unsigned char : 2;
} __hdct10_bits;

typedef union {
	__hdct10_bits bits;
	__sfr_byte byte;
} __hdct10_type;

typedef struct {
	unsigned char __hcbd11 : 1;
	unsigned char __hctd11 : 1;
	unsigned char __hbbd11 : 1;
	unsigned char __hbtd11 : 1;
	unsigned char __habd11 : 1;
	unsigned char __hatd11 : 1;
	unsigned char : 2;
} __hdct11_bits;

typedef union {
	__hdct11_bits bits;
	__sfr_byte byte;
} __hdct11_type;

//***********************************//
typedef struct {
	unsigned char __opavs0 : 1;
	unsigned char __opavs1 : 1;
	unsigned char __opavs2 : 1;
	unsigned char : 3;
	unsigned char __cmp0_eg0 : 1;
	unsigned char __cmp0_eg1 : 1;
} __opoms_bits;

typedef union {
	__opoms_bits bits;
	__sfr_byte byte;
} __opoms_type;

typedef struct {
	unsigned char __aof0 : 1;
	unsigned char __aof1 : 1;
	unsigned char __aof2 : 1;
	unsigned char __aof3 : 1;
	unsigned char __aof4 : 1;
	unsigned char __aofm : 1;
	unsigned char __ars : 1;
	unsigned char : 1;
} __opacal_bits;

typedef union {
	__opacal_bits bits;
	__sfr_byte byte;
} __opacal_type;

//***********************************//
typedef struct {
	unsigned char : 3;
	unsigned char __pt3on : 1;
	unsigned char __pt3ck0 : 1;
	unsigned char __pt3ck1 : 1;
	unsigned char __pt3ck2 : 1;
	unsigned char __pt3pau : 1;
} __ptm3c0_bits;

typedef union {
	__ptm3c0_bits bits;
	__sfr_byte byte;
} __ptm3c0_type;

typedef struct {
	unsigned char __pt3cclr : 1;
	unsigned char __pt3capts : 1;
	unsigned char __pt3pol : 1;
	unsigned char __pt3oc : 1;
	unsigned char __pt3io0 : 1;
	unsigned char __pt3io1 : 1;
	unsigned char __pt3m0 : 1;
	unsigned char __pt3m1 : 1;
} __ptm3c1_bits;

typedef union {
	__ptm3c1_bits bits;
	__sfr_byte byte;
} __ptm3c1_type;

//***********************************//
typedef struct {
	unsigned char __pa0s0 : 1;
	unsigned char __pa0s1 : 1;
	unsigned char __pa1s0 : 1;
	unsigned char __pa1s1 : 1;
	unsigned char __pa2s0 : 1;
	unsigned char __pa2s1 : 1;
	unsigned char __pa3s0 : 1;
	unsigned char __pa3s1 : 1;
} __paps0_bits;

typedef union {
	__paps0_bits bits;
	__sfr_byte byte;
} __paps0_type;

typedef struct {
	unsigned char __pa4s0 : 1;
	unsigned char __pa4s1 : 1;
	unsigned char __pa5s0 : 1;
	unsigned char __pa5s1 : 1;
	unsigned char __pa6s0 : 1;
	unsigned char __pa6s1 : 1;
	unsigned char __pa7s0 : 1;
	unsigned char __pa7s1 : 1;
} __paps1_bits;

typedef union {
	__paps1_bits bits;
	__sfr_byte byte;
} __paps1_type;

//***********************************//
typedef struct {
	unsigned char __pc0s0 : 1;
	unsigned char __pc0s1 : 1;
	unsigned char __pc1s0 : 1;
	unsigned char __pc1s1 : 1;
	unsigned char __pc2s0 : 1;
	unsigned char __pc2s1 : 1;
	unsigned char __pc3s0 : 1;
	unsigned char __pc3s1 : 1;
} __pcps0_bits;

typedef union {
	__pcps0_bits bits;
	__sfr_byte byte;
} __pcps0_type;

typedef struct {
	unsigned char __pc4s0 : 1;
	unsigned char __pc4s1 : 1;
	unsigned char __pc5s0 : 1;
	unsigned char __pc5s1 : 1;
	unsigned char : 4;
} __pcps1_bits;

typedef union {
	__pcps1_bits bits;
	__sfr_byte byte;
} __pcps1_type;

//***********************************//
typedef struct {
	unsigned char __pd0s0 : 1;
	unsigned char __pd0s1 : 1;
	unsigned char __pd1s0 : 1;
	unsigned char __pd1s1 : 1;
	unsigned char __pd2s0 : 1;
	unsigned char __pd2s1 : 1;
	unsigned char __pd3s0 : 1;
	unsigned char __pd3s1 : 1;
} __pdps0_bits;

typedef union {
	__pdps0_bits bits;
	__sfr_byte byte;
} __pdps0_type;

//***********************************//
typedef struct {
	unsigned char __sclps : 1;
	unsigned char __sdaps : 1;
	unsigned char __c1nps0 : 1;
	unsigned char __c1nps1 : 1;
	unsigned char __txps0 : 1;
	unsigned char __rxps : 1;
	unsigned char __int1ps : 1;
	unsigned char : 1;
} __prm_bits;

typedef union {
	__prm_bits bits;
	__sfr_byte byte;
} __prm_type;

//***********************************//
DEFINE_SFR(__sfr_byte, __mp0, 0x01);
DEFINE_SFR(__sfr_byte, __mp1, 0x03);
DEFINE_SFR(__bp_type, __bp, 0x04);
DEFINE_SFR(__sfr_byte, __acc, 0x05);
DEFINE_SFR(__sfr_byte, __pcl, 0x06);
DEFINE_SFR(__sfr_byte, __tblp, 0x07);
DEFINE_SFR(__sfr_byte, __tblh, 0x08);
DEFINE_SFR(__sfr_byte, __tbhp, 0x09);
DEFINE_SFR(__status_type, __status, 0x0a);
DEFINE_SFR(__smod_type, __smod, 0x0b);
DEFINE_SFR(__lvdc_type, __lvdc, 0x0c);
DEFINE_SFR(__lvrc_type, __lvrc, 0x0d);
DEFINE_SFR(__wdtc_type, __wdtc, 0x0e);
DEFINE_SFR(__tbc_type, __tbc, 0x0f);
DEFINE_SFR(__integ1_type, __integ1, 0x10);
DEFINE_SFR(__intc0_type, __intc0, 0x11);
DEFINE_SFR(__intc1_type, __intc1, 0x12);
DEFINE_SFR(__intc2_type, __intc2, 0x13);
DEFINE_SFR(__intc3_type, __intc3, 0x14);
DEFINE_SFR(__mfi0_type, __mfi0, 0x15);
DEFINE_SFR(__mfi1_type, __mfi1, 0x16);
DEFINE_SFR(__mfi2_type, __mfi2, 0x17);
DEFINE_SFR(__mfi3_type, __mfi3, 0x18);
DEFINE_SFR(__mfi4_type, __mfi4, 0x19);
DEFINE_SFR(__mfi5_type, __mfi5, 0x1a);
DEFINE_SFR(__mfi6_type, __mfi6, 0x1b);
DEFINE_SFR(__pawu_type, __pawu, 0x1c);
DEFINE_SFR(__papu_type, __papu, 0x1d);
DEFINE_SFR(__pa_type, __pa, 0x1e);
DEFINE_SFR(__pac_type, __pac, 0x1f);
DEFINE_SFR(__pbpu_type, __pbpu, 0x20);
DEFINE_SFR(__pb_type, __pb, 0x21);
DEFINE_SFR(__pbc_type, __pbc, 0x22);
DEFINE_SFR(__pcpu_type, __pcpu, 0x23);
DEFINE_SFR(__pc_type, __pc, 0x24);
DEFINE_SFR(__pcc_type, __pcc, 0x25);
DEFINE_SFR(__pdpu_type, __pdpu, 0x26);
DEFINE_SFR(__pd_type, __pd, 0x27);
DEFINE_SFR(__pdc_type, __pdc, 0x28);
DEFINE_SFR(__captc0_type, __captc0, 0x29);
DEFINE_SFR(__captc1_type, __captc1, 0x2a);
DEFINE_SFR(__sfr_byte, __captmdl, 0x2b);
DEFINE_SFR(__sfr_byte, __captmdh, 0x2c);
DEFINE_SFR(__sfr_byte, __captmal, 0x2d);
DEFINE_SFR(__sfr_byte, __captmah, 0x2e);
DEFINE_SFR(__sfr_byte, __captmcl, 0x2f);
DEFINE_SFR(__sfr_byte, __captmch, 0x30);
DEFINE_SFR(__sfr_byte, __adrl, 0x31);
DEFINE_SFR(__sfr_byte, __adrh, 0x32);
DEFINE_SFR(__adcr0_type, __adcr0, 0x33);
DEFINE_SFR(__adcr1_type, __adcr1, 0x34);
DEFINE_SFR(__adcr2_type, __adcr2, 0x35);
DEFINE_SFR(__sfr_byte, __addl, 0x36);
DEFINE_SFR(__sfr_byte, __adlvdl, 0x37);
DEFINE_SFR(__sfr_byte, __adlvdh, 0x38);
DEFINE_SFR(__sfr_byte, __adhvdl, 0x39);
DEFINE_SFR(__sfr_byte, __adhvdh, 0x3a);
DEFINE_SFR(__pbps0_type, __pbps0, 0x3b);
DEFINE_SFR(__pbps1_type, __pbps1, 0x3c);
DEFINE_SFR(__pbps2_type, __pbps2, 0x3d);
DEFINE_SFR(__integ0_type, __integ0, 0x3e);
DEFINE_SFR(__ctrl_type, __ctrl, 0x3f);
DEFINE_SFR(__sfr_byte, __eea, 0x41);
DEFINE_SFR(__sfr_byte, __eed, 0x42);
DEFINE_SFR(__hdcr_type, __hdcr, 0x43);
DEFINE_SFR(__hdcd_type, __hdcd, 0x44);
DEFINE_SFR(__mptc1_type, __mptc1, 0x45);
DEFINE_SFR(__mptc2_type, __mptc2, 0x46);
DEFINE_SFR(__ptm1c0_type, __ptm1c0, 0x47);
DEFINE_SFR(__ptm1c1_type, __ptm1c1, 0x48);
DEFINE_SFR(__sfr_byte, __ptm1dl, 0x49);
DEFINE_SFR(__sfr_byte, __ptm1dh, 0x4a);
DEFINE_SFR(__sfr_byte, __ptm1al, 0x4b);
DEFINE_SFR(__sfr_byte, __ptm1ah, 0x4c);
DEFINE_SFR(__sfr_byte, __ptm1rpl, 0x4d);
DEFINE_SFR(__sfr_byte, __ptm1rph, 0x4e);
DEFINE_SFR(__ptm0c0_type, __ptm0c0, 0x4f);
DEFINE_SFR(__ptm0c1_type, __ptm0c1, 0x50);
DEFINE_SFR(__sfr_byte, __ptm0dl, 0x51);
DEFINE_SFR(__sfr_byte, __ptm0dh, 0x52);
DEFINE_SFR(__sfr_byte, __ptm0al, 0x53);
DEFINE_SFR(__sfr_byte, __ptm0ah, 0x54);
DEFINE_SFR(__sfr_byte, __ptm0rpl, 0x55);
DEFINE_SFR(__sfr_byte, __ptm0rph, 0x56);
DEFINE_SFR(__ptm2c0_type, __ptm2c0, 0x57);
DEFINE_SFR(__ptm2c1_type, __ptm2c1, 0x58);
DEFINE_SFR(__sfr_byte, __ptm2dl, 0x59);
DEFINE_SFR(__sfr_byte, __ptm2dh, 0x5a);
DEFINE_SFR(__sfr_byte, __ptm2al, 0x5b);
DEFINE_SFR(__sfr_byte, __ptm2ah, 0x5c);
DEFINE_SFR(__sfr_byte, __ptm2rpl, 0x5d);
DEFINE_SFR(__sfr_byte, __ptm2rph, 0x5e);
DEFINE_SFR(__pwmc_type, __pwmc, 0x5f);
DEFINE_SFR(__sfr_byte, __dutr0l, 0x60);
DEFINE_SFR(__sfr_byte, __dutr0h, 0x61);
DEFINE_SFR(__sfr_byte, __dutr1l, 0x62);
DEFINE_SFR(__sfr_byte, __dutr1h, 0x63);
DEFINE_SFR(__sfr_byte, __dutr2l, 0x64);
DEFINE_SFR(__sfr_byte, __dutr2h, 0x65);
DEFINE_SFR(__sfr_byte, __prdrl, 0x66);
DEFINE_SFR(__sfr_byte, __prdrh, 0x67);
DEFINE_SFR(__sfr_byte, __pwmrl, 0x68);
DEFINE_SFR(__sfr_byte, __pwmrh, 0x69);
DEFINE_SFR(__pwmme_type, __pwmme, 0x6a);
DEFINE_SFR(__pwmmd_type, __pwmmd, 0x6b);
DEFINE_SFR(__mcf_type, __mcf, 0x6c);
DEFINE_SFR(__mcd_type, __mcd, 0x6d);
DEFINE_SFR(__dts_type, __dts, 0x6e);
DEFINE_SFR(__plc_type, __plc, 0x6f);
DEFINE_SFR(__iicc0_type, __iicc0, 0x70);
DEFINE_SFR(__iicc1_type, __iicc1, 0x71);
DEFINE_SFR(__iicd_type, __iicd, 0x72);
DEFINE_SFR(__iica_type, __iica, 0x73);
DEFINE_SFR(__i2ctoc_type, __i2ctoc, 0x74);
DEFINE_SFR(__usr_type, __usr, 0x75);
DEFINE_SFR(__ucr1_type, __ucr1, 0x76);
DEFINE_SFR(__ucr2_type, __ucr2, 0x77);
DEFINE_SFR(__brg_type, __brg, 0x78);
DEFINE_SFR(__txr_rxr_type, __txr_rxr, 0x7a);
DEFINE_SFR(__cpc_type, __cpc, 0x7b);
DEFINE_SFR(__hchk_num_type, __hchk_num, 0x7c);
DEFINE_SFR(__hnf_msel_type, __hnf_msel, 0x7d);
DEFINE_SFR(__nf_vih_type, __nf_vih, 0x7e);
DEFINE_SFR(__nf_vil_type, __nf_vil, 0x7f);
DEFINE_SFR(__eec_type, __eec, 0x140);
DEFINE_SFR(__hdct0_type, __hdct0, 0x162);
DEFINE_SFR(__hdct1_type, __hdct1, 0x163);
DEFINE_SFR(__hdct2_type, __hdct2, 0x164);
DEFINE_SFR(__hdct3_type, __hdct3, 0x165);
DEFINE_SFR(__hdct4_type, __hdct4, 0x166);
DEFINE_SFR(__hdct5_type, __hdct5, 0x167);
DEFINE_SFR(__hdct6_type, __hdct6, 0x168);
DEFINE_SFR(__hdct7_type, __hdct7, 0x169);
DEFINE_SFR(__hdct8_type, __hdct8, 0x16a);
DEFINE_SFR(__hdct9_type, __hdct9, 0x16b);
DEFINE_SFR(__hdct10_type, __hdct10, 0x16c);
DEFINE_SFR(__hdct11_type, __hdct11, 0x16d);
DEFINE_SFR(__opoms_type, __opoms, 0x16e);
DEFINE_SFR(__sfr_byte, __opcm, 0x16f);
DEFINE_SFR(__opacal_type, __opacal, 0x170);
DEFINE_SFR(__ptm3c0_type, __ptm3c0, 0x171);
DEFINE_SFR(__ptm3c1_type, __ptm3c1, 0x172);
DEFINE_SFR(__sfr_byte, __ptm3dl, 0x173);
DEFINE_SFR(__sfr_byte, __ptm3dh, 0x174);
DEFINE_SFR(__sfr_byte, __ptm3al, 0x175);
DEFINE_SFR(__sfr_byte, __ptm3ah, 0x176);
DEFINE_SFR(__sfr_byte, __ptm3rpl, 0x177);
DEFINE_SFR(__sfr_byte, __ptm3rph, 0x178);
DEFINE_SFR(__paps0_type, __paps0, 0x17a);
DEFINE_SFR(__paps1_type, __paps1, 0x17b);
DEFINE_SFR(__pcps0_type, __pcps0, 0x17c);
DEFINE_SFR(__pcps1_type, __pcps1, 0x17d);
DEFINE_SFR(__pdps0_type, __pdps0, 0x17e);
DEFINE_SFR(__prm_type, __prm, 0x17f);
DEFINE_SFR(__sfr_byte, __iar0, 0x00);
DEFINE_SFR(__sfr_byte, __iar1, 0x02);

//***********************************//
#define _iar0     __iar0
#define _iar1     __iar1
#define _mp0      __mp0
#define _mp1      __mp1
#define _bp       __bp.byte
#define _acc      __acc
#define _pcl      __pcl
#define _tblp     __tblp
#define _tblh     __tblh
#define _tbhp     __tbhp
#define _status   __status.byte
#define _smod     __smod.byte
#define _lvdc     __lvdc.byte
#define _lvrc     __lvrc.byte
#define _wdtc     __wdtc.byte
#define _tbc      __tbc.byte
#define _integ1   __integ1.byte
#define _intc0    __intc0.byte
#define _intc1    __intc1.byte
#define _intc2    __intc2.byte
#define _intc3    __intc3.byte
#define _mfi0     __mfi0.byte
#define _mfi1     __mfi1.byte
#define _mfi2     __mfi2.byte
#define _mfi3     __mfi3.byte
#define _mfi4     __mfi4.byte
#define _mfi5     __mfi5.byte
#define _mfi6     __mfi6.byte
#define _pawu     __pawu.byte
#define _papu     __papu.byte
#define _pa       __pa.byte
#define _pac      __pac.byte
#define _pbpu     __pbpu.byte
#define _pb       __pb.byte
#define _pbc      __pbc.byte
#define _pcpu     __pcpu.byte
#define _pc       __pc.byte
#define _pcc      __pcc.byte
#define _pdpu     __pdpu.byte
#define _pd       __pd.byte
#define _pdc      __pdc.byte
#define _captc0   __captc0.byte
#define _captc1   __captc1.byte
#define _captmdl  __captmdl
#define _captmdh  __captmdh
#define _captmal  __captmal
#define _captmah  __captmah
#define _captmcl  __captmcl
#define _captmch  __captmch
#define _adrl     __adrl
#define _adrh     __adrh
#define _adcr0    __adcr0.byte
#define _adcr1    __adcr1.byte
#define _adcr2    __adcr2.byte
#define _addl     __addl
#define _adlvdl   __adlvdl
#define _adlvdh   __adlvdh
#define _adhvdl   __adhvdl
#define _adhvdh   __adhvdh
#define _pbps0    __pbps0.byte
#define _pbps1    __pbps1.byte
#define _pbps2    __pbps2.byte
#define _integ0   __integ0.byte
#define _ctrl     __ctrl.byte
#define _eea      __eea
#define _eed      __eed
#define _hdcr     __hdcr.byte
#define _hdcd     __hdcd.byte
#define _mptc1    __mptc1.byte
#define _mptc2    __mptc2.byte

#define _ptm1c0   __ptm1c0.byte
#define _ptm1c1   __ptm1c1.byte
#define _ptm1dl   __ptm1dl
#define _ptm1dh   __ptm1dh
#define _ptm1al   __ptm1al
#define _ptm1ah   __ptm1ah
#define _ptm1rpl  __ptm1rpl
#define _ptm1rph  __ptm1rph

#define _ptm0c0   __ptm0c0.byte
#define _ptm0c1   __ptm0c1.byte
#define _ptm0dl   __ptm0dl
#define _ptm0dh   __ptm0dh
#define _ptm0al   __ptm0al
#define _ptm0ah   __ptm0ah
#define _ptm0rpl  __ptm0rpl
#define _ptm0rph  __ptm0rph

#define _ptm2c0   __ptm2c0.byte
#define _ptm2c1   __ptm2c1.byte
#define _ptm2dl   __ptm2dl
#define _ptm2dh   __ptm2dh
#define _ptm2al   __ptm2al
#define _ptm2ah   __ptm2ah
#define _ptm2rpl  __ptm2rpl
#define _ptm2rph  __ptm2rph

#define _pwmc     __pwmc.byte
#define _dutr0l   __dutr0l
#define _dutr0h   __dutr0h
#define _dutr1l   __dutr1l
#define _dutr1h   __dutr1h
#define _dutr2l   __dutr2l
#define _dutr2h   __dutr2h
#define _prdrl    __prdrl
#define _prdrh    __prdrh
#define _pwmrl    __pwmrl
#define _pwmrh    __pwmrh
#define _pwmme    __pwmme.byte
#define _pwmmd    __pwmmd.byte
#define _mcf      __mcf.byte
#define _mcd      __mcd.byte
#define _dts      __dts.byte
#define _plc      __plc.byte
#define _iicc0    __iicc0.byte
#define _iicc1    __iicc1.byte
#define _iicd     __iicd.byte
#define _iica     __iica.byte
#define _i2ctoc   __i2ctoc.byte
#define _usr      __usr.byte
#define _ucr1     __ucr1.byte
#define _ucr2     __ucr2.byte
#define _brg      __brg.byte
#define _txr_rxr  __txr_rxr.byte
#define _cpc      __cpc.byte
#define _hchk_num __hchk_num.byte
#define _hnf_msel __hnf_msel.byte
#define _nf_vih   __nf_vih.byte
#define _nf_vil   __nf_vil.byte
#define _eec      __eec.byte
#define _hdct0    __hdct0.byte
#define _hdct1    __hdct1.byte
#define _hdct2    __hdct2.byte
#define _hdct3    __hdct3.byte
#define _hdct4    __hdct4.byte
#define _hdct5    __hdct5.byte
#define _hdct6    __hdct6.byte
#define _hdct7    __hdct7.byte
#define _hdct8    __hdct8.byte
#define _hdct9    __hdct9.byte
#define _hdct10   __hdct10.byte
#define _hdct11   __hdct11.byte
#define _opoms    __opoms.byte
#define _opcm     __opcm
#define _opacal   __opacal.byte

#define _ptm3c0   __ptm3c0.byte
#define _ptm3c1   __ptm3c1.byte
#define _ptm3dl   __ptm3dl
#define _ptm3dh   __ptm3dh
#define _ptm3al   __ptm3al
#define _ptm3ah   __ptm3ah
#define _ptm3rpl  __ptm3rpl
#define _ptm3rph  __ptm3rph

#define _paps0    __paps0.byte
#define _paps1    __paps1.byte
#define _pcps0    __pcps0.byte
#define _pcps1    __pcps1.byte
#define _pdps0    __pdps0.byte
#define _prm      __prm.byte

//***********************************//
#define _dmbp0    __bp.bits.__dmbp0
#define _c        __status.bits.__c
#define _ac       __status.bits.__ac
#define _z        __status.bits.__z
#define _ov       __status.bits.__ov
#define _pdf      __status.bits.__pdf
#define _to       __status.bits.__to
#define _hlclk    __smod.bits.__hlclk
#define _idlen    __smod.bits.__idlen
#define _hto      __smod.bits.__hto
#define _lto      __smod.bits.__lto
#define _cks0     __smod.bits.__cks0
#define _cks1     __smod.bits.__cks1
#define _cks2     __smod.bits.__cks2
#define _vlvd0    __lvdc.bits.__vlvd0
#define _vlvd1    __lvdc.bits.__vlvd1
#define _vlvd2    __lvdc.bits.__vlvd2
#define _lvden    __lvdc.bits.__lvden
#define _lvdo     __lvdc.bits.__lvdo
#define _lvs0     __lvrc.bits.__lvs0
#define _lvs1     __lvrc.bits.__lvs1
#define _lvs2     __lvrc.bits.__lvs2
#define _lvs3     __lvrc.bits.__lvs3
#define _lvs4     __lvrc.bits.__lvs4
#define _lvs5     __lvrc.bits.__lvs5
#define _lvs6     __lvrc.bits.__lvs6
#define _lvs7     __lvrc.bits.__lvs7

#define _ws0      __wdtc.bits.__ws0
#define _ws1      __wdtc.bits.__ws1
#define _ws2      __wdtc.bits.__ws2
#define _we0      __wdtc.bits.__we0
#define _we1      __wdtc.bits.__we1
#define _we2      __wdtc.bits.__we2
#define _we3      __wdtc.bits.__we3
#define _we4      __wdtc.bits.__we4

#define _tb0      __tbc.bits.__tb0
#define _tb1      __tbc.bits.__tb1
#define _tbck     __tbc.bits.__tbck
#define _tbon     __tbc.bits.__tbon
#define _int1s0   __integ1.bits.__int1s0
#define _int1s1   __integ1.bits.__int1s1
#define _emi      __intc0.bits.__emi
#define _halle_mf0e __intc0.bits.__halle_mf0e
#define _int1e    __intc0.bits.__int1e
#define _c0e      __intc0.bits.__c0e
#define _hallf_mf0f __intc0.bits.__hallf_mf0f
#define _int1f    __intc0.bits.__int1f
#define _c0f      __intc0.bits.__c0f
#define _nfie     __intc1.bits.__nfie
#define _mf1e     __intc1.bits.__mf1e
#define _lvde     __intc1.bits.__lvde
#define _epwe     __intc1.bits.__epwe
#define _nfif     __intc1.bits.__nfif
#define _mf1f     __intc1.bits.__mf1f
#define _lvdf     __intc1.bits.__lvdf
#define _epwf     __intc1.bits.__epwf
#define _mf2e     __intc2.bits.__mf2e
#define _mf3e     __intc2.bits.__mf3e
#define _mf4e     __intc2.bits.__mf4e
#define _mf5e     __intc2.bits.__mf5e
#define _mf2f     __intc2.bits.__mf2f
#define _mf3f     __intc2.bits.__mf3f
#define _mf4f     __intc2.bits.__mf4f
#define _mf5f     __intc2.bits.__mf5f
#define _iice     __intc3.bits.__iice
#define _uarte    __intc3.bits.__uarte
#define _mf6e     __intc3.bits.__mf6e
#define _tbe      __intc3.bits.__tbe
#define _iicf     __intc3.bits.__iicf
#define _uartf    __intc3.bits.__uartf
#define _mf6f     __intc3.bits.__mf6f
#define _tbf      __intc3.bits.__tbf
#define _halae    __mfi0.bits.__halae
#define _halbe    __mfi0.bits.__halbe
#define _halce    __mfi0.bits.__halce
#define _halaf    __mfi0.bits.__halaf
#define _halbf    __mfi0.bits.__halbf
#define _halcf    __mfi0.bits.__halcf
#define _aeoce    __mfi1.bits.__aeoce
#define _alime    __mfi1.bits.__alime
#define _capoe    __mfi1.bits.__capoe
#define _capce    __mfi1.bits.__capce
#define _aeocf    __mfi1.bits.__aeocf
#define _alimf    __mfi1.bits.__alimf
#define _capof    __mfi1.bits.__capof
#define _capcf    __mfi1.bits.__capcf

#define _pwmd0e   __mfi2.bits.__pwmd0e
#define _pwmd1e   __mfi2.bits.__pwmd1e
#define _pwmd2e   __mfi2.bits.__pwmd2e
#define _pwmpe    __mfi2.bits.__pwmpe
#define _pwmd0f   __mfi2.bits.__pwmd0f
#define _pwmd1f   __mfi2.bits.__pwmd1f
#define _pwmd2f   __mfi2.bits.__pwmd2f
#define _pwmpf    __mfi2.bits.__pwmpf

#define _tm2pe    __mfi3.bits.__tm2pe
#define _tm2ae    __mfi3.bits.__tm2ae
#define _tm2pf    __mfi3.bits.__tm2pf
#define _tm2af    __mfi3.bits.__tm2af

#define _tm0pe    __mfi4.bits.__tm0pe
#define _tm0ae    __mfi4.bits.__tm0ae
#define _tm0pf    __mfi4.bits.__tm0pf
#define _tm0af    __mfi4.bits.__tm0af

#define _tm1pe    __mfi5.bits.__tm1pe
#define _tm1ae    __mfi5.bits.__tm1ae
#define _tm1pf    __mfi5.bits.__tm1pf
#define _tm1af    __mfi5.bits.__tm1af

#define _tm3pe    __mfi6.bits.__tm3pe
#define _tm3ae    __mfi6.bits.__tm3ae
#define _tm3pf    __mfi6.bits.__tm3pf
#define _tm3af    __mfi6.bits.__tm3af

#define _pawu0    __pawu.bits.__pawu0
#define _pawu1    __pawu.bits.__pawu1
#define _pawu2    __pawu.bits.__pawu2
#define _pawu3    __pawu.bits.__pawu3
#define _pawu4    __pawu.bits.__pawu4
#define _pawu5    __pawu.bits.__pawu5
#define _pawu6    __pawu.bits.__pawu6
#define _pawu7    __pawu.bits.__pawu7

#define _papu0    __papu.bits.__papu0
#define _papu1    __papu.bits.__papu1
#define _papu2    __papu.bits.__papu2
#define _papu3    __papu.bits.__papu3
#define _papu4    __papu.bits.__papu4
#define _papu5    __papu.bits.__papu5
#define _papu6    __papu.bits.__papu6
#define _papu7    __papu.bits.__papu7

#define _pa0      __pa.bits.__pa0
#define _pa1      __pa.bits.__pa1
#define _pa2      __pa.bits.__pa2
#define _pa3      __pa.bits.__pa3
#define _pa4      __pa.bits.__pa4
#define _pa5      __pa.bits.__pa5
#define _pa6      __pa.bits.__pa6
#define _pa7      __pa.bits.__pa7

#define _pac0     __pac.bits.__pac0
#define _pac1     __pac.bits.__pac1
#define _pac2     __pac.bits.__pac2
#define _pac3     __pac.bits.__pac3
#define _pac4     __pac.bits.__pac4
#define _pac5     __pac.bits.__pac5
#define _pac6     __pac.bits.__pac6
#define _pac7     __pac.bits.__pac7

#define _pbpu0    __pbpu.bits.__pbpu0
#define _pbpu1    __pbpu.bits.__pbpu1
#define _pbpu2    __pbpu.bits.__pbpu2
#define _pbpu3    __pbpu.bits.__pbpu3
#define _pbpu4    __pbpu.bits.__pbpu4
#define _pbpu5    __pbpu.bits.__pbpu5
#define _pbpu6    __pbpu.bits.__pbpu6
#define _pbpu7    __pbpu.bits.__pbpu7

#define _pb0      __pb.bits.__pb0
#define _pb1      __pb.bits.__pb1
#define _pb2      __pb.bits.__pb2
#define _pb3      __pb.bits.__pb3
#define _pb4      __pb.bits.__pb4
#define _pb5      __pb.bits.__pb5
#define _pb6      __pb.bits.__pb6
#define _pb7      __pb.bits.__pb7

#define _pbc0     __pbc.bits.__pbc0
#define _pbc1     __pbc.bits.__pbc1
#define _pbc2     __pbc.bits.__pbc2
#define _pbc3     __pbc.bits.__pbc3
#define _pbc4     __pbc.bits.__pbc4
#define _pbc5     __pbc.bits.__pbc5
#define _pbc6     __pbc.bits.__pbc6
#define _pbc7     __pbc.bits.__pbc7

#define _pcpu0    __pcpu.bits.__pcpu0
#define _pcpu1    __pcpu.bits.__pcpu1
#define _pcpu2    __pcpu.bits.__pcpu2
#define _pcpu3    __pcpu.bits.__pcpu3
#define _pcpu4    __pcpu.bits.__pcpu4
#define _pcpu5    __pcpu.bits.__pcpu5

#define _pc0      __pc.bits.__pc0
#define _pc1      __pc.bits.__pc1
#define _pc2      __pc.bits.__pc2
#define _pc3      __pc.bits.__pc3
#define _pc4      __pc.bits.__pc4
#define _pc5      __pc.bits.__pc5

#define _pcc0     __pcc.bits.__pcc0
#define _pcc1     __pcc.bits.__pcc1
#define _pcc2     __pcc.bits.__pcc2
#define _pcc3     __pcc.bits.__pcc3
#define _pcc4     __pcc.bits.__pcc4
#define _pcc5     __pcc.bits.__pcc5

#define _pdpu0    __pdpu.bits.__pdpu0
#define _pdpu1    __pdpu.bits.__pdpu1
#define _pdpu2    __pdpu.bits.__pdpu2
#define _pdpu3    __pdpu.bits.__pdpu3

#define _pd0      __pd.bits.__pd0
#define _pd1      __pd.bits.__pd1
#define _pd2      __pd.bits.__pd2
#define _pd3      __pd.bits.__pd3

#define _pdc0     __pdc.bits.__pdc0
#define _pdc1     __pdc.bits.__pdc1
#define _pdc2     __pdc.bits.__pdc2
#define _pdc3     __pdc.bits.__pdc3

#define _caps0    __captc0.bits.__caps0
#define _caps1    __captc0.bits.__caps1
#define _capton   __captc0.bits.__capton
#define _captck0  __captc0.bits.__captck0
#define _captck1  __captc0.bits.__captck1
#define _captck2  __captc0.bits.__captck2
#define _captpau  __captc0.bits.__captpau
#define _camclr   __captc1.bits.__camclr
#define _capclr   __captc1.bits.__capclr
#define _capfil   __captc1.bits.__capfil
#define _capnfs   __captc1.bits.__capnfs
#define _capnft   __captc1.bits.__capnft
#define _capen    __captc1.bits.__capen
#define _capeg0   __captc1.bits.__capeg0
#define _capeg1   __captc1.bits.__capeg1
#define _acs0     __adcr0.bits.__acs0
#define _acs1     __adcr0.bits.__acs1
#define _acs2     __adcr0.bits.__acs2
#define _acs3     __adcr0.bits.__acs3
#define _adrfs    __adcr0.bits.__adrfs
#define _adoff    __adcr0.bits.__adoff
#define _eocb     __adcr0.bits.__eocb
#define _adstr    __adcr0.bits.__adstr
#define _adck0    __adcr1.bits.__adck0
#define _adck1    __adcr1.bits.__adck1
#define _adck2    __adcr1.bits.__adck2
#define _adclve   __adcr1.bits.__adclve
#define _adchve   __adcr1.bits.__adchve
#define _pwis     __adcr1.bits.__pwis
#define _dlstr    __adcr1.bits.__dlstr
#define _adsts    __adcr1.bits.__adsts
#define _pwdis0   __adcr2.bits.__pwdis0
#define _pwdis1   __adcr2.bits.__pwdis1
#define _pb0s0    __pbps0.bits.__pb0s0
#define _pb0s1    __pbps0.bits.__pb0s1
#define _pb1s0    __pbps0.bits.__pb1s0
#define _pb1s1    __pbps0.bits.__pb1s1
#define _pb2s0    __pbps0.bits.__pb2s0
#define _pb2s1    __pbps0.bits.__pb2s1
#define _pb2s2    __pbps0.bits.__pb2s2
#define _pb3s0    __pbps1.bits.__pb3s0
#define _pb3s1    __pbps1.bits.__pb3s1
#define _pb4s0    __pbps1.bits.__pb4s0
#define _pb4s1    __pbps1.bits.__pb4s1
#define _pb5s0    __pbps1.bits.__pb5s0
#define _pb5s1    __pbps1.bits.__pb5s1
#define _pb6s0    __pbps1.bits.__pb6s0
#define _pb6s1    __pbps1.bits.__pb6s1
#define _pb7s0    __pbps2.bits.__pb7s0
#define _pb7s1    __pbps2.bits.__pb7s1
#define _intas0   __integ0.bits.__intas0
#define _intas1   __integ0.bits.__intas1
#define _intbs0   __integ0.bits.__intbs0
#define _intbs1   __integ0.bits.__intbs1
#define _intcs0   __integ0.bits.__intcs0
#define _intcs1   __integ0.bits.__intcs1
#define _hsel     __integ0.bits.__hsel
#define _wrf      __ctrl.bits.__wrf
#define _lrf      __ctrl.bits.__lrf
#define _lvrf     __ctrl.bits.__lvrf
#define _fsyson   __ctrl.bits.__fsyson
#define _hdcen    __hdcr.bits.__hdcen
#define _frs      __hdcr.bits.__frs
#define _brke     __hdcr.bits.__brke
#define _hdms     __hdcr.bits.__hdms
#define _hals     __hdcr.bits.__hals
#define _hdly_msel __hdcr.bits.__hdly_msel
#define _ctm_sel0 __hdcr.bits.__ctm_sel0
#define _ctm_sel1 __hdcr.bits.__ctm_sel1
#define _sha      __hdcd.bits.__sha
#define _shb      __hdcd.bits.__shb
#define _shc      __hdcd.bits.__shc
#define _ahlhe    __mptc1.bits.__ahlhe
#define _ishe     __mptc1.bits.__ishe
#define _capche   __mptc1.bits.__capche
#define _capohe   __mptc1.bits.__capohe
#define _pswe     __mptc1.bits.__pswe
#define _pswd     __mptc1.bits.__pswd
#define _capops   __mptc2.bits.__capops
#define _capcps   __mptc2.bits.__capcps
#define _isps     __mptc2.bits.__isps
#define _ahlps    __mptc2.bits.__ahlps
#define _pswps    __mptc2.bits.__pswps
#define _pt1on    __ptm1c0.bits.__pt1on
#define _pt1ck0   __ptm1c0.bits.__pt1ck0
#define _pt1ck1   __ptm1c0.bits.__pt1ck1
#define _pt1ck2   __ptm1c0.bits.__pt1ck2
#define _pt1pau   __ptm1c0.bits.__pt1pau
#define _pt1cclr  __ptm1c1.bits.__pt1cclr
#define _pt1capts __ptm1c1.bits.__pt1capts
#define _pt1pol   __ptm1c1.bits.__pt1pol
#define _pt1oc    __ptm1c1.bits.__pt1oc
#define _pt1io0   __ptm1c1.bits.__pt1io0
#define _pt1io1   __ptm1c1.bits.__pt1io1
#define _pt1m0    __ptm1c1.bits.__pt1m0
#define _pt1m1    __ptm1c1.bits.__pt1m1
#define _pt0on    __ptm0c0.bits.__pt0on
#define _pt0ck0   __ptm0c0.bits.__pt0ck0
#define _pt0ck1   __ptm0c0.bits.__pt0ck1
#define _pt0ck2   __ptm0c0.bits.__pt0ck2
#define _pt0pau   __ptm0c0.bits.__pt0pau
#define _pt0cclr  __ptm0c1.bits.__pt0cclr
#define _pt0capts __ptm0c1.bits.__pt0capts
#define _pt0pol   __ptm0c1.bits.__pt0pol
#define _pt0oc    __ptm0c1.bits.__pt0oc
#define _pt0io0   __ptm0c1.bits.__pt0io0
#define _pt0io1   __ptm0c1.bits.__pt0io1
#define _pt0m0    __ptm0c1.bits.__pt0m0
#define _pt0m1    __ptm0c1.bits.__pt0m1
#define _pt2on    __ptm2c0.bits.__pt2on
#define _pt2ck0   __ptm2c0.bits.__pt2ck0
#define _pt2ck1   __ptm2c0.bits.__pt2ck1
#define _pt2ck2   __ptm2c0.bits.__pt2ck2
#define _pt2pau   __ptm2c0.bits.__pt2pau
#define _pt2cclr  __ptm2c1.bits.__pt2cclr
#define _pt2capts __ptm2c1.bits.__pt2capts
#define _pt2pol   __ptm2c1.bits.__pt2pol
#define _pt2oc    __ptm2c1.bits.__pt2oc
#define _pt2io0   __ptm2c1.bits.__pt2io0
#define _pt2io1   __ptm2c1.bits.__pt2io1
#define _pt2m0    __ptm2c1.bits.__pt2m0
#define _pt2m1    __ptm2c1.bits.__pt2m1
#define _pwmld    __pwmc.bits.__pwmld
#define _itcms0   __pwmc.bits.__itcms0
#define _itcms1   __pwmc.bits.__itcms1
#define _pwmon    __pwmc.bits.__pwmon
#define _pcks0    __pwmc.bits.__pcks0
#define _pcks1    __pwmc.bits.__pcks1
#define _pwmms0   __pwmc.bits.__pwmms0
#define _pwmms1   __pwmc.bits.__pwmms1
#define _pme0     __pwmme.bits.__pme0
#define _pme1     __pwmme.bits.__pme1
#define _pme2     __pwmme.bits.__pme2
#define _pme3     __pwmme.bits.__pme3
#define _pme4     __pwmme.bits.__pme4
#define _pme5     __pwmme.bits.__pme5
#define _pmd0     __pwmmd.bits.__pmd0
#define _pmd1     __pwmmd.bits.__pmd1
#define _pmd2     __pwmmd.bits.__pmd2
#define _pmd3     __pwmmd.bits.__pmd3
#define _pmd4     __pwmmd.bits.__pmd4
#define _pmd5     __pwmmd.bits.__pmd5
#define _pwms     __mcf.bits.__pwms
#define _fmos     __mcf.bits.__fmos
#define _mpwe     __mcf.bits.__mpwe
#define _mpwms    __mcf.bits.__mpwms
#define _mskms    __mcf.bits.__mskms
#define _fha      __mcd.bits.__fha
#define _fhb      __mcd.bits.__fhb
#define _fhc      __mcd.bits.__fhc
#define _gbt      __mcd.bits.__gbt
#define _gab      __mcd.bits.__gab
#define _gat      __mcd.bits.__gat
#define _dte      __dts.bits.__dte
#define _dtcks0   __dts.bits.__dtcks0
#define _dtcks1   __dts.bits.__dtcks1
#define _patc     __plc.bits.__patc
#define _pabc     __plc.bits.__pabc
#define _pbtc     __plc.bits.__pbtc
#define _pbbc     __plc.bits.__pbbc
#define _pctc     __plc.bits.__pctc
#define _pcbc     __plc.bits.__pcbc
#define _i2cen    __iicc0.bits.__i2cen
#define _i2cdbnc0 __iicc0.bits.__i2cdbnc0
#define _i2cdbnc1 __iicc0.bits.__i2cdbnc1
#define _iicrxak  __iicc1.bits.__iicrxak
#define _iicrnic  __iicc1.bits.__iicrnic
#define _iicsrw   __iicc1.bits.__iicsrw
#define _iictxak  __iicc1.bits.__iictxak
#define _iichtx   __iicc1.bits.__iichtx
#define _iichbb   __iicc1.bits.__iichbb
#define _iichaas  __iicc1.bits.__iichaas
#define _iichcf   __iicc1.bits.__iichcf
#define _iicdd0   __iicd.bits.__iicdd0
#define _iicdd1   __iicd.bits.__iicdd1
#define _iicdd2   __iicd.bits.__iicdd2
#define _iicdd3   __iicd.bits.__iicdd3
#define _iicdd4   __iicd.bits.__iicdd4
#define _iicdd5   __iicd.bits.__iicdd5
#define _iicdd6   __iicd.bits.__iicdd6
#define _iicdd7   __iicd.bits.__iicdd7
#define _iica0    __iica.bits.__iica0
#define _iica1    __iica.bits.__iica1
#define _iica2    __iica.bits.__iica2
#define _iica3    __iica.bits.__iica3
#define _iica4    __iica.bits.__iica4
#define _iica5    __iica.bits.__iica5
#define _iica6    __iica.bits.__iica6
#define _i2ctos0  __i2ctoc.bits.__i2ctos0
#define _i2ctos1  __i2ctoc.bits.__i2ctos1
#define _i2ctos2  __i2ctoc.bits.__i2ctos2
#define _i2ctos3  __i2ctoc.bits.__i2ctos3
#define _i2ctos4  __i2ctoc.bits.__i2ctos4
#define _i2ctos5  __i2ctoc.bits.__i2ctos5
#define _i2ctof   __i2ctoc.bits.__i2ctof
#define _i2ctoen  __i2ctoc.bits.__i2ctoen
#define _txif     __usr.bits.__txif
#define _tidle    __usr.bits.__tidle
#define _rxif     __usr.bits.__rxif
#define _ridle    __usr.bits.__ridle
#define _oerr     __usr.bits.__oerr
#define _ferr     __usr.bits.__ferr
#define _nf       __usr.bits.__nf
#define _perr     __usr.bits.__perr
#define _tx8      __ucr1.bits.__tx8
#define _rx8      __ucr1.bits.__rx8
#define _txbrk    __ucr1.bits.__txbrk
#define _stops    __ucr1.bits.__stops
#define _prt      __ucr1.bits.__prt
#define _pren     __ucr1.bits.__pren
#define _bno      __ucr1.bits.__bno
#define _uarten   __ucr1.bits.__uarten
#define _teie     __ucr2.bits.__teie
#define _tiie     __ucr2.bits.__tiie
#define _rie      __ucr2.bits.__rie
#define _wake     __ucr2.bits.__wake
#define _adden    __ucr2.bits.__adden
#define _brgh     __ucr2.bits.__brgh
#define _rxen     __ucr2.bits.__rxen
#define _txen     __ucr2.bits.__txen
#define _brg0     __brg.bits.__brg0
#define _brg1     __brg.bits.__brg1
#define _brg2     __brg.bits.__brg2
#define _brg3     __brg.bits.__brg3
#define _brg4     __brg.bits.__brg4
#define _brg5     __brg.bits.__brg5
#define _brg6     __brg.bits.__brg6
#define _brg7     __brg.bits.__brg7
#define _txrx0    __txr_rxr.bits.__txrx0
#define _txrx1    __txr_rxr.bits.__txrx1
#define _txrx2    __txr_rxr.bits.__txrx2
#define _txrx3    __txr_rxr.bits.__txrx3
#define _txrx4    __txr_rxr.bits.__txrx4
#define _txrx5    __txr_rxr.bits.__txrx5
#define _txrx6    __txr_rxr.bits.__txrx6
#define _txrx7    __txr_rxr.bits.__txrx7
#define _c0en     __cpc.bits.__c0en
#define _c1en     __cpc.bits.__c1en
#define _c2en     __cpc.bits.__c2en
#define _c3en     __cpc.bits.__c3en
#define _c0hyen   __cpc.bits.__c0hyen
#define _c1hyen   __cpc.bits.__c1hyen
#define _c2hyen   __cpc.bits.__c2hyen
#define _c3hyen   __cpc.bits.__c3hyen
#define _hck_n0   __hchk_num.bits.__hck_n0
#define _hck_n1   __hchk_num.bits.__hck_n1
#define _hck_n2   __hchk_num.bits.__hck_n2
#define _hck_n3   __hchk_num.bits.__hck_n3
#define _hck_n4   __hchk_num.bits.__hck_n4
#define _hfr_sel0 __hnf_msel.bits.__hfr_sel0
#define _hfr_sel1 __hnf_msel.bits.__hfr_sel1
#define _hfr_sel2 __hnf_msel.bits.__hfr_sel2
#define _hnf_en   __hnf_msel.bits.__hnf_en
#define _cins     __nf_vih.bits.__cins
#define _nf_byps  __nf_vih.bits.__nf_byps
#define _nfis0    __nf_vil.bits.__nfis0
#define _nfis1    __nf_vil.bits.__nfis1
#define _rd       __eec.bits.__rd
#define _rden     __eec.bits.__rden
#define _wr       __eec.bits.__wr
#define _wren     __eec.bits.__wren
#define _hcbd0    __hdct0.bits.__hcbd0
#define _hctd0    __hdct0.bits.__hctd0
#define _hbbd0    __hdct0.bits.__hbbd0
#define _hbtd0    __hdct0.bits.__hbtd0
#define _habd0    __hdct0.bits.__habd0
#define _hatd0    __hdct0.bits.__hatd0
#define _hcbd1    __hdct1.bits.__hcbd1
#define _hctd1    __hdct1.bits.__hctd1
#define _hbbd1    __hdct1.bits.__hbbd1
#define _hbtd1    __hdct1.bits.__hbtd1
#define _habd1    __hdct1.bits.__habd1
#define _hatd1    __hdct1.bits.__hatd1
#define _hcbd2    __hdct2.bits.__hcbd2
#define _hctd2    __hdct2.bits.__hctd2
#define _hbbd2    __hdct2.bits.__hbbd2
#define _hbtd2    __hdct2.bits.__hbtd2
#define _habd2    __hdct2.bits.__habd2
#define _hatd2    __hdct2.bits.__hatd2
#define _hcbd3    __hdct3.bits.__hcbd3
#define _hctd3    __hdct3.bits.__hctd3
#define _hbbd3    __hdct3.bits.__hbbd3
#define _hbtd3    __hdct3.bits.__hbtd3
#define _habd3    __hdct3.bits.__habd3
#define _hatd3    __hdct3.bits.__hatd3
#define _hcbd4    __hdct4.bits.__hcbd4
#define _hctd4    __hdct4.bits.__hctd4
#define _hbbd4    __hdct4.bits.__hbbd4
#define _hbtd4    __hdct4.bits.__hbtd4
#define _habd4    __hdct4.bits.__habd4
#define _hatd4    __hdct4.bits.__hatd4
#define _hcbd5    __hdct5.bits.__hcbd5
#define _hctd5    __hdct5.bits.__hctd5
#define _hbbd5    __hdct5.bits.__hbbd5
#define _hbtd5    __hdct5.bits.__hbtd5
#define _habd5    __hdct5.bits.__habd5
#define _hatd5    __hdct5.bits.__hatd5
#define _hcbd6    __hdct6.bits.__hcbd6
#define _hctd6    __hdct6.bits.__hctd6
#define _hbbd6    __hdct6.bits.__hbbd6
#define _hbtd6    __hdct6.bits.__hbtd6
#define _habd6    __hdct6.bits.__habd6
#define _hatd6    __hdct6.bits.__hatd6
#define _hcbd7    __hdct7.bits.__hcbd7
#define _hctd7    __hdct7.bits.__hctd7
#define _hbbd7    __hdct7.bits.__hbbd7
#define _hbtd7    __hdct7.bits.__hbtd7
#define _habd7    __hdct7.bits.__habd7
#define _hatd7    __hdct7.bits.__hatd7
#define _hcbd8    __hdct8.bits.__hcbd8
#define _hctd8    __hdct8.bits.__hctd8
#define _hbbd8    __hdct8.bits.__hbbd8
#define _hbtd8    __hdct8.bits.__hbtd8
#define _habd8    __hdct8.bits.__habd8
#define _hatd8    __hdct8.bits.__hatd8
#define _hcbd9    __hdct9.bits.__hcbd9
#define _hctd9    __hdct9.bits.__hctd9
#define _hbbd9    __hdct9.bits.__hbbd9
#define _hbtd9    __hdct9.bits.__hbtd9
#define _habd9    __hdct9.bits.__habd9
#define _hatd9    __hdct9.bits.__hatd9
#define _hcbd10   __hdct10.bits.__hcbd10
#define _hctd10   __hdct10.bits.__hctd10
#define _hbbd10   __hdct10.bits.__hbbd10
#define _hbtd10   __hdct10.bits.__hbtd10
#define _habd10   __hdct10.bits.__habd10
#define _hatd10   __hdct10.bits.__hatd10
#define _hcbd11   __hdct11.bits.__hcbd11
#define _hctd11   __hdct11.bits.__hctd11
#define _hbbd11   __hdct11.bits.__hbbd11
#define _hbtd11   __hdct11.bits.__hbtd11
#define _habd11   __hdct11.bits.__habd11
#define _hatd11   __hdct11.bits.__hatd11
#define _opavs0   __opoms.bits.__opavs0
#define _opavs1   __opoms.bits.__opavs1
#define _opavs2   __opoms.bits.__opavs2
#define _cmp0_eg0 __opoms.bits.__cmp0_eg0
#define _cmp0_eg1 __opoms.bits.__cmp0_eg1
#define _aof0     __opacal.bits.__aof0
#define _aof1     __opacal.bits.__aof1
#define _aof2     __opacal.bits.__aof2
#define _aof3     __opacal.bits.__aof3
#define _aof4     __opacal.bits.__aof4
#define _aofm     __opacal.bits.__aofm
#define _ars      __opacal.bits.__ars
#define _pt3on    __ptm3c0.bits.__pt3on
#define _pt3ck0   __ptm3c0.bits.__pt3ck0
#define _pt3ck1   __ptm3c0.bits.__pt3ck1
#define _pt3ck2   __ptm3c0.bits.__pt3ck2
#define _pt3pau   __ptm3c0.bits.__pt3pau
#define _pt3cclr  __ptm3c1.bits.__pt3cclr
#define _pt3capts __ptm3c1.bits.__pt3capts
#define _pt3pol   __ptm3c1.bits.__pt3pol
#define _pt3oc    __ptm3c1.bits.__pt3oc
#define _pt3io0   __ptm3c1.bits.__pt3io0
#define _pt3io1   __ptm3c1.bits.__pt3io1
#define _pt3m0    __ptm3c1.bits.__pt3m0
#define _pt3m1    __ptm3c1.bits.__pt3m1
#define _pa0s0    __paps0.bits.__pa0s0
#define _pa0s1    __paps0.bits.__pa0s1
#define _pa1s0    __paps0.bits.__pa1s0
#define _pa1s1    __paps0.bits.__pa1s1
#define _pa2s0    __paps0.bits.__pa2s0
#define _pa2s1    __paps0.bits.__pa2s1
#define _pa3s0    __paps0.bits.__pa3s0
#define _pa3s1    __paps0.bits.__pa3s1
#define _pa4s0    __paps1.bits.__pa4s0
#define _pa4s1    __paps1.bits.__pa4s1
#define _pa5s0    __paps1.bits.__pa5s0
#define _pa5s1    __paps1.bits.__pa5s1
#define _pa6s0    __paps1.bits.__pa6s0
#define _pa6s1    __paps1.bits.__pa6s1
#define _pa7s0    __paps1.bits.__pa7s0
#define _pa7s1    __paps1.bits.__pa7s1
#define _pc0s0    __pcps0.bits.__pc0s0
#define _pc0s1    __pcps0.bits.__pc0s1
#define _pc1s0    __pcps0.bits.__pc1s0
#define _pc1s1    __pcps0.bits.__pc1s1
#define _pc2s0    __pcps0.bits.__pc2s0
#define _pc2s1    __pcps0.bits.__pc2s1
#define _pc3s0    __pcps0.bits.__pc3s0
#define _pc3s1    __pcps0.bits.__pc3s1
#define _pc4s0    __pcps1.bits.__pc4s0
#define _pc4s1    __pcps1.bits.__pc4s1
#define _pc5s0    __pcps1.bits.__pc5s0
#define _pc5s1    __pcps1.bits.__pc5s1
#define _pd0s0    __pdps0.bits.__pd0s0
#define _pd0s1    __pdps0.bits.__pd0s1
#define _pd1s0    __pdps0.bits.__pd1s0
#define _pd1s1    __pdps0.bits.__pd1s1
#define _pd2s0    __pdps0.bits.__pd2s0
#define _pd2s1    __pdps0.bits.__pd2s1
#define _pd3s0    __pdps0.bits.__pd3s0
#define _pd3s1    __pdps0.bits.__pd3s1
#define _sclps    __prm.bits.__sclps
#define _sdaps    __prm.bits.__sdaps
#define _c1nps0   __prm.bits.__c1nps0
#define _c1nps1   __prm.bits.__c1nps1
#define _txps0    __prm.bits.__txps0
#define _rxps     __prm.bits.__rxps
#define _int1ps   __prm.bits.__int1ps

#define ___mkstr(x)                #x
#define __EEPROM_DATA(a, b, c, d, e, f, g, h) \
                         asm("eeprom_data .section 'eeprom'"); \
                         asm("db\t" ___mkstr(a));        \
                         asm("db\t" ___mkstr(b));        \
                         asm("db\t" ___mkstr(c));        \
                         asm("db\t" ___mkstr(d));        \
                         asm("db\t" ___mkstr(e));        \
                         asm("db\t" ___mkstr(f));        \
                         asm("db\t" ___mkstr(g));        \
                         asm("db\t" ___mkstr(h));        

#endif // _HT66FM5240_H_
