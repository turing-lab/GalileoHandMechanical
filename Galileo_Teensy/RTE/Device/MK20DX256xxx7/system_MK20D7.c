/*
** ###################################################################
**     Processors:          MK20DX64VLH7
**                          MK20DX128VLH7
**                          MK20DX256VLH7
**                          MK20DX64VLK7
**                          MK20DX128VLK7
**                          MK20DX256VLK7
**                          MK20DX128VLL7
**                          MK20DX256VLL7
**                          MK20DX64VMB7
**                          MK20DX128VMB7
**                          MK20DX256VMB7
**                          MK20DX128VML7
**                          MK20DX256VML7
**
**     Compilers:           ARM Compiler
**                          Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**
**     Reference manual:    Kxx (P1 silicon) Sub-Family Reference Manual Rev. 0, draft A Oct 2011
**     Version:             rev. 1.0, 2012-01-15
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright: 2012 Freescale Semiconductor, Inc. All Rights Reserved.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**     - rev. 1.0 (2012-01-15)
**         Initial public version.
**
** ###################################################################
*/

/**
 * @file MK20D7
 * @version 1.0
 * @date 2012-01-15
 * @brief Device specific configuration file for MK20D7 (implementation file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include "MK20D7.h"

  #define DEFAULT_SYSTEM_CLOCK            72000000u /* Default System clock value */
  #define DISABLE_WDOG                            1

/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */

uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;

/* ----------------------------------------------------------------------------
   -- SystemInit()
   ---------------------------------------------------------------------------- */

void SystemInit (void) {
#if (DISABLE_WDOG)  // 15.02.2012 Added by ARM 
  /* Disable the WDOG module */
  /* WDOG_UNLOCK: WDOGUNLOCK=0xC520 */
  WDOG->UNLOCK = (uint16_t)0xC520u;     /* Key 1 */
  /* WDOG_UNLOCK : WDOGUNLOCK=0xD928 */
  WDOG->UNLOCK  = (uint16_t)0xD928u;    /* Key 2 */
  /* WDOG_STCTRLH: ??=0,DISTESTWDOG=0,BYTESEL=0,TESTSEL=0,TESTWDOG=0,??=0,STNDBYEN=1,WAITEN=1,STOPEN=1,DBGEN=0,ALLOWUPDATE=1,WINEN=0,IRQRSTEN=0,CLKSRC=1,WDOGEN=0 */
  WDOG->STCTRLH = (uint16_t)0x01D2u;
#endif /* (DISABLE_WDOG) */
	
	SIM->CLKDIV1 = SIM_CLKDIV1_OUTDIV1(0x00) |
                SIM_CLKDIV1_OUTDIV2(0x01) |
                SIM_CLKDIV1_OUTDIV3(0x03) |
                SIM_CLKDIV1_OUTDIV4(0x03); /* Set the system prescalers to safe value */
  /* SIM_SCGC5: PORTA=1 */
  SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;   /* Enable clock gate for ports to enable pin routing */
  if ((PMC->REGSC & PMC_REGSC_ACKISO_MASK) != 0x0U) {
    /* PMC_REGSC: ACKISO=1 */
    PMC->REGSC |= PMC_REGSC_ACKISO_MASK; /* Release IO pads after wakeup from VLLS mode. */
  }
  /* SIM_CLKDIV1: OUTDIV1=0,OUTDIV2=1,OUTDIV3=1,OUTDIV4=2,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
  SIM->CLKDIV1 = SIM_CLKDIV1_OUTDIV1(0x00) |
                SIM_CLKDIV1_OUTDIV2(0x01) |
                SIM_CLKDIV1_OUTDIV3(0x01) |
                SIM_CLKDIV1_OUTDIV4(0x02); /* Update system prescalers */
  /* SIM_SOPT2: PLLFLLSEL=1 */
  SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK; /* Select PLL as a clock source for various peripherals */
  /* SIM_SOPT1: OSC32KSEL=3 */
  SIM->SOPT1 |= SIM_SOPT1_OSC32KSEL(0x03); /* LPO 1kHz oscillator drives 32 kHz clock for various peripherals */
  /* PORTA_PCR18: ISF=0,MUX=0 */
  PORTA->PCR[18] &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  /* PORTA_PCR19: ISF=0,MUX=0 */
  PORTA->PCR[19] &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  /* Switch to FBE Mode */
  /* MCG_C2: LOCRE0=0,??=0,RANGE0=2,HGO0=0,EREFS0=1,LP=0,IRCS=0 */
  MCG->C2 = (MCG_C2_RANGE0(0x02) | MCG_C2_EREFS0_MASK);
  /* OSC_CR: ERCLKEN=1,??=0,EREFSTEN=0,??=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  OSC->CR = OSC_CR_ERCLKEN_MASK;
  /* MCG_C7: OSCSEL=0 */
  MCG->C7 &= (uint8_t)~(uint8_t)(MCG_C7_OSCSEL_MASK);
  /* MCG_C1: CLKS=2,FRDIV=4,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
  MCG->C1 = (MCG_C1_CLKS(0x02) | MCG_C1_FRDIV(0x04) | MCG_C1_IRCLKEN_MASK);
  /* MCG_C4: DMX32=0,DRST_DRS=0 */
  MCG->C4 &= (uint8_t)~(uint8_t)((MCG_C4_DMX32_MASK | MCG_C4_DRST_DRS(0x03)));
  /* MCG_C5: ??=0,PLLCLKEN0=0,PLLSTEN0=0,PRDIV0=7 */
  MCG->C5 = MCG_C5_PRDIV0(0x07);
  /* MCG_C6: LOLIE0=0,PLLS=0,CME0=0,VDIV0=0x0C */
  MCG->C6 = MCG_C6_VDIV0(0x0C);
	while((MCG->S & MCG_S_OSCINIT0_MASK) == 0x00U) { /* Check that the oscillator is running */
  }
  while((MCG->S & MCG_S_IREFST_MASK) != 0x00U) { /* Check that the source of the FLL reference clock is the external reference clock. */
  }
  while((MCG->S & 0x0CU) != 0x08U) {    /* Wait until external reference clock is selected as MCG output */
  }
  /* Switch to PBE Mode */
  /* MCG_C6: LOLIE0=0,PLLS=1,CME0=0,VDIV0=0x0C */
  MCG->C6 = (MCG_C6_PLLS_MASK | MCG_C6_VDIV0(0x0C));
  while((MCG->S & 0x0CU) != 0x08U) {    /* Wait until external reference clock is selected as MCG output */
  }
  while((MCG->S & MCG_S_LOCK0_MASK) == 0x00U) { /* Wait until locked */
  }
  /* Switch to PEE Mode */
  /* MCG_C1: CLKS=0,FRDIV=4,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
  MCG->C1 = (MCG_C1_CLKS(0x00) | MCG_C1_FRDIV(0x04) | MCG_C1_IRCLKEN_MASK);
  while((MCG->S & 0x0CU) != 0x0CU) {    /* Wait until output of the PLL is selected */
  }
	
	PORTA->PCR[4] = (uint32_t)((PORTA->PCR[4] & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK
               )) | (uint32_t)(
                PORT_PCR_MUX(0x07)
               ));
        /* Initialization of the RCM module */
  /* RCM_RPFW: RSTFLTSEL=0 */
  RCM->RPFW &= (uint8_t)~(uint8_t)(RCM_RPFW_RSTFLTSEL(0x1F));
  /* RCM_RPFC: RSTFLTSS=0,RSTFLTSRW=0 */
  RCM->RPFC &= (uint8_t)~(uint8_t)(
               RCM_RPFC_RSTFLTSS_MASK |
               RCM_RPFC_RSTFLTSRW(0x03)
              );
      /* Initialization of the PMC module */
  /* PMC_LVDSC1: LVDACK=1,LVDIE=0,LVDRE=1,LVDV=0 */
  PMC->LVDSC1 = (uint8_t)((PMC->LVDSC1 & (uint8_t)~(uint8_t)(
                PMC_LVDSC1_LVDIE_MASK |
                PMC_LVDSC1_LVDV(0x03)
               )) | (uint8_t)(
                PMC_LVDSC1_LVDACK_MASK |
                PMC_LVDSC1_LVDRE_MASK
               ));
  /* PMC_LVDSC2: LVWACK=1,LVWIE=0,LVWV=0 */
  PMC->LVDSC2 = (uint8_t)((PMC->LVDSC2 & (uint8_t)~(uint8_t)(
                PMC_LVDSC2_LVWIE_MASK |
                PMC_LVDSC2_LVWV(0x03)
               )) | (uint8_t)(
                PMC_LVDSC2_LVWACK_MASK
               ));
  /* PMC_REGSC: BGEN=0,ACKISO=0,BGBE=0 */
  PMC->REGSC &= (uint8_t)~(uint8_t)(
                PMC_REGSC_BGEN_MASK |
                PMC_REGSC_ACKISO_MASK |
                PMC_REGSC_BGBE_MASK
               );
  /* SMC_PMPROT: ??=0,??=0,AVLP=0,??=0,ALLS=0,??=0,AVLLS=0,??=0 */
  SMC->PMPROT = 0x00U;                  /* Setup Power mode protection register */
	
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate (void) {
}
