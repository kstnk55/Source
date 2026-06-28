/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2022 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/** \file  File:  BrsHw.c
 *      Project:  Vector Basic Runtime System
 *       Module:  BrsHw for platform Cypress Traveo2
 *     Template:  This file is reviewed according to Brs_Template@Implementation[1.03.05]
 *
 *  \brief Description:  This is the hardware specific code file for Vector Basic Runtime System (BRS).
 *
 *  \attention Please note:
 *    The demo and example programs only show special aspects of the software. With regard to the fact
 *    that these programs are meant for demonstration purposes only, Vector Informatik liability shall be
 *    expressly excluded in cases of ordinary negligence, to the extent admissible by law or statute.
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to BrsHw.h.
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  EXAMPLE CODE ONLY
 *  -------------------------------------------------------------------------------------------------------------------
 *  This Example Code is only intended for illustrating an example of a possible BSW integration and BSW configuration.
 *  The Example Code has not passed any quality control measures and may be incomplete. The Example Code is neither
 *  intended nor qualified for use in series production. The Example Code as well as any of its modifications and/or
 *  implementations must be tested with diligent care and must comply with all quality requirements which are necessary
 *  according to the state of the art before their use.
 *********************************************************************************************************************/
 
#define _BRSHW_C_
#define BRSHW_SOURCE
 
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "BrsHw.h"
 
#if !defined (BRS_ENABLE_FBL_SUPPORT)
  #include "Os.h"
#endif
 
/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
#if (BRSHW_VERSION != 0x0200u)
  #error "Header and source file are inconsistent!"
#endif
#if (BRSHW_BUGFIX_VERSION != 0x03u)
  #error "Different versions of bugfix in Header and Source used!"
#endif
 
/**********************************************************************************************************************
 *  CONFIGURATION CHECK
 *********************************************************************************************************************/
#if defined (BRS_COMP_GHS)
 
#else
  #error "Unknown compiler specified!"
#endif
 
/**********************************************************************************************************************
 *  DEFINITION + MACROS
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  GLOBAL VARIABLES
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  GLOBAL CONST VARIABLES
 *********************************************************************************************************************/
/*
 * Description: These constants are used to propagate the Versions over
 *              module boundaries.The version numbers are BCD coded. E.g. a sub
 *              version of 23 is coded with 0x23, a bug fix version of 9 is
 *              coded 0x09.
 */
uint8 const kBrsHwMainVersion   = (uint8)(BRSHW_VERSION >> 8);
uint8 const kBrsHwSubVersion    = (uint8)(BRSHW_VERSION & 0xFF);
uint8 const kBrsHwBugfixVersion = (uint8)(BRSHW_BUGFIX_VERSION);
 
/**********************************************************************************************************************
 *  LOCAL VARIABLES AND LOCAL HW REGISTERS
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  CONTROLLER CONFIGURATION REGISTERS
 *********************************************************************************************************************/
/*******************************************************************************
 * Reset control registers
 ********************************************************************************/
#define BRSHW_CM4_SCS_AIRCR          BRSHW_IOS(uint32, 0xE000ED0Cul) /* Reset control registers for Cortex-M4 */
 
/*Seems there is an issue in the RM for the Body Entry, address of the RES_CAUSE register is wrong*/
/*#define BRSHW_RESET_CAUSE            BRSHW_IOS(uint32, 0x40261800ul)*/ /* Reset cause observation register */
#define BRSHW_RESET_CAUSE_COPY       BRSHW_IOS(uint32, 0x28013FF0ul) /* Reset cause copy address */
#define BRSHW_RESET_CAUSE2_COPY      BRSHW_IOS(uint32, 0x28013FF4ul) /* Reset cause 2 copy address */
#define BRSHW_RESET_CAUSE_COPY_COLD  BRSHW_IOS(uint32, 0x28013FF8ul) /* Reset cause copy (keep cold boot reason) address */
 
#define BRSHW_SWRESET_TRIGGERT_MASK  (0x00000010ul)
 
#if defined (BRS_ENABLE_WATCHDOG)
/*******************************************************************************
 *  Watchdog registers
 ********************************************************************************/
  #define BRS_WDT_CTL   BRSHW_IOS(uint32, 0x4026C000ul)  /* Watchdog counter control register */
  #define BRS_WDT_LOCK   BRSHW_IOS(uint32, 0x4026C040ul) /* Watchdog LOCK*/
#endif /*BRS_ENABLE_WATCHDOG*/
 
#if defined (BRS_ENABLE_PLLCLOCKS)
/*******************************************************************************
 *  PLL & Clocking registers
 ********************************************************************************/
# if defined (BRS_DERIVATIVE_GROUP_TRAVEO2_BH)
  #define BRSHW_CLK_ECO_CONFIG                BRSHW_IOS(uint32, 0x4026151CUL)
  #define BRSHW_CLK_ECO_CONFIG2               BRSHW_IOS(uint32, 0x40261544UL)
  #define BRSHW_CLK_ECO_STATUS                BRSHW_IOS(uint32, 0x40261524UL)
  #define BRSHW_CLK_OUTPUT_FAST               BRSHW_IOS(uint32, 0x40260140UL)
  #define BRSHW_CLK_OUTPUT_SLOW               BRSHW_IOS(uint32, 0x40260144UL)
  #define BRSHW_CLK_TIMER_CTL                 BRSHW_IOS(uint32, 0x40261504UL)
  /* DSI_MUXn, CLK_PATHn : n=0 for FLL, n=1 for PLL0, n=2 for PLL1, n=3 for PLL400M0, n=4 for PLL400M1, n=5 for CLK_PATH5 */
  #define BRSHW_CLK_DSI_SELECT(n)             BRSHW_IOS(uint32, 0x40260100UL + n * 0x4U)
  #define BRSHW_CLK_PATH_SELECT(n)            BRSHW_IOS(uint32, 0x40261200UL + n * 0x4U)
  /* CLK_HFn : n = [0, 7] */
  #define BRSHW_CLK_ROOT_SELECT(n)            BRSHW_IOS(uint32, 0x40261240UL + n * 0x4U)
  #define BRSHW_CLK_PLL0_CONFIG               BRSHW_IOS(uint32, 0x40261600UL)
  #define BRSHW_CLK_PLL0_STATUS               BRSHW_IOS(uint32, 0x40261640UL)
  #define BRSHW_CLK_PLL400M0_CONFIG           BRSHW_IOS(uint32, 0x40261900UL)  
  #define BRSHW_CLK_PLL400M0_CONFIG2          BRSHW_IOS(uint32, 0x40261904UL)
  #define BRSHW_CLK_PLL400M0_CONFIG3          BRSHW_IOS(uint32, 0x40261908UL)
  #define BRSHW_CLK_PLL400M0_STATUS           BRSHW_IOS(uint32, 0x4026190CUL)
 
  #define BRSHW_PERI_GR_CLOCK_CTL(n)          BRSHW_IOS(uint32, 0x40004000UL + n * 0x40U) /* PERI_GRn_CLOCK_CTL : n = 0,1,2,3,4,5,6,8 or 9 */
  #define BRSHW_PERI_GR_SL_CTL(n)             BRSHW_IOS(uint32, 0x40004010UL + n * 0x40U) /* PERI_GRn_SL_CTL : n = 0,1,2,3,4,5,6,8 or 9 */  
  #define BRSHW_PERI_PCLK_GR0_DIV_CMD         BRSHW_IOS(uint32, 0x40040000UL)
  #define BRSHW_PERI_PCLK_GR0_CLOCK_CTL(n)    BRSHW_IOS(uint32, 0x40040C00UL + n * 0x4U) /* 15 configurable peripheral clocks : n = [0, 14] */
  #define BRSHW_PERI_PCLK_GR0_DIV_8_CTL(n)    BRSHW_IOS(uint32, 0x40041000UL + n * 0x4U) /* 4 8-bit dividers  : n = [0, 3] */
  #define BRSHW_PERI_PCLK_GR0_DIV_16_CT(n)    BRSHW_IOS(uint32, 0x40041400UL + n * 0x4U) /* 3 16-bit dividers : n = [0, 2] */
  #define BRSHW_PERI_PCLK_GR0_DIV_24_5_CTL(n) BRSHW_IOS(uint32, 0x40041C00UL + n * 0x4U) /* 1 24.5-bit divider : n = 0 */
  #define BRSHW_PERI_PCLK_GR1_DIV_CMD         BRSHW_IOS(uint32, 0x40042000UL)
  #define BRSHW_PERI_PCLK_GR1_CLOCK_CTL(n)    BRSHW_IOS(uint32, 0x40042C00UL + n * 0x4U) /* 154 configurable peripheral clocks : n = [0, 153] */
  #define BRSHW_PERI_PCLK_GR1_DIV_8_CTL(n)    BRSHW_IOS(uint32, 0x40043000UL + n * 0x4U) /* 19 8-bit dividers  : n = [0, 18] */
  #define BRSHW_PERI_PCLK_GR1_DIV_16_CT(n)    BRSHW_IOS(uint32, 0x40043400UL + n * 0x4U) /* 20 16-bit dividers : n = [0, 19] */
  #define BRSHW_PERI_PCLK_GR1_DIV_24_5_CTL(n) BRSHW_IOS(uint32, 0x40043C00UL + n * 0x4U) /* 21 24.5-bit dividers : n = [0, 20] */
 
  #define BRSHW_FLASHC_FLASH_CTL              BRSHW_IOS(uint32, 0x40240000UL)
  #define BRSHW_CPUSS_RAM0_CTL                BRSHW_IOS(uint32, 0x40201300UL)
  #define BRSHW_CPUSS_RAM1_CTL                BRSHW_IOS(uint32, 0x40201380UL)
  #define BRSHW_CPUSS_RAM2_CTL                BRSHW_IOS(uint32, 0x402013A0UL)
  #define BRSHW_CPUSS_ROM_CTL                 BRSHW_IOS(uint32, 0x402013C4UL)
  #define BRSHW_CPUSS_SYSTICK_CTL             BRSHW_IOS(uint32, 0x40201600UL)
  #define BRSHW_CPUSS_SLOW_CLOCK_CTL          BRSHW_IOS(uint32, 0x40201008UL)
  #define BRSHW_CPUSS_PERI_CLOCK_CTL          BRSHW_IOS(uint32, 0x4020100CUL)
  #define BRSHW_CPUSS_MEM_CLOCK_CTL           BRSHW_IOS(uint32, 0x40201010UL)
  #define BRSHW_CPUSS_FAST_0_CLOCK_CTL        BRSHW_IOS(uint32, 0x40200008UL)
  #define BRSHW_CPUSS_FAST_1_CLOCK_CTL        BRSHW_IOS(uint32, 0x40200408UL)
  #define BRSHW_CPUSS_TRC_DBG_CLOCK_CTL       BRSHW_IOS(uint32, 0x40200320UL)
 
# else
  #define BRSHW_FLASHC_FLASH_CTL      BRSHW_IOS(uint32, 0x40240000ul) /* a register to set-up the Wait States for Flash */
  #define BRSHW_CPUSS_RAM0_CTL        BRSHW_IOS(uint32, 0x40201300ul) /* a register to set-up the Wait States for RAM0 */
  #define BRSHW_CPUSS_RAM1_CTL        BRSHW_IOS(uint32, 0x40201380ul) /* a register to set-up the Wait States for RAM1 */
  #define BRSHW_CPUSS_ROM_CTL         BRSHW_IOS(uint32, 0x402013C4ul) /* a register to set-up the Wait States for ROM */
 
  #define BRSHW_CLK_TRIM_ECO_CTL      BRSHW_IOS(uint32, 0x4026301Cul)
  #define BRSHW_CLK_TRIM_ECO_CTL2     BRSHW_IOS(uint32, 0x40263020ul)
 
  #define BRSHW_CLK_DSI_SELECT(n)     BRSHW_IOS(uint32, 0x40260100ul+ 0x4 * n)
  #define BRSHW_CLK_OUTPUT_FAST       BRSHW_IOS(uint32, 0x40260140ul)
  #define BRSHW_CLK_OUTPUT_SLOW       BRSHW_IOS(uint32, 0x40260144ul)
  #define BRSHW_CLK_CAL_CNT1          BRSHW_IOS(uint32, 0x40260148ul)
  #define BRSHW_CLK_CAL_CNT2          BRSHW_IOS(uint32, 0x4026014Cul)
 
  #define BRSHW_CLK_PATH_SELECT(n)    BRSHW_IOS(uint32, 0x40261200ul+ 0x4 * n) /* n = 0..2 , CLK_PATHn , n must be the same as specified by ROOT_MUX in BRSHW_CLK_ROOT_SELECT*/
 
  #define BRSHW_CLK_ROOT_SELECT(n)    BRSHW_IOS(uint32, 0x40261240ul+ 0x4 * n)
  #define BRSHW_CLK_SELECT            BRSHW_IOS(uint32, 0x40261500ul)
  #define BRSHW_CLK_TIMER_CTL         BRSHW_IOS(uint32, 0x40261504ul)
  #define BRSHW_CLK_ILO0_CONFIG       BRSHW_IOS(uint32, 0x40261508ul)
  #define BRSHW_CLK_IMO_CONFIG        BRSHW_IOS(uint32, 0x40261518ul)
  #define BRSHW_CLK_ECO_CONFIG        BRSHW_IOS(uint32, 0x4026151Cul)
  #define BRSHW_CLK_ECO_STATUS        BRSHW_IOS(uint32, 0x40261524ul)
  #define BRSHW_CLK_FLL_CONFIG        BRSHW_IOS(uint32, 0x40261530ul)
  #define BRSHW_CLK_FLL_CONFIG2       BRSHW_IOS(uint32, 0x40261534ul)
  #define BRSHW_CLK_FLL_CONFIG3       BRSHW_IOS(uint32, 0x40261538ul)
  #define BRSHW_CLK_FLL_CONFIG4       BRSHW_IOS(uint32, 0x4026153Cul)
  #define BRSHW_CLK_FLL_STATUS        BRSHW_IOS(uint32, 0x40261540ul)
  #define BRSHW_CLK_PLL_CONFIG(n)     BRSHW_IOS(uint32, 0x40261600ul+ 0x4 * n)
  #define BRSHW_CLK_PLL_STATUS(n)     BRSHW_IOS(uint32, 0x40261640ul+ 0x4 * n)
 
  #define BRSHW_PERI_GR0_CLOCK_CTL    BRSHW_IOS(uint32, 0x40004000ul)
  #define BRSHW_PERI_GR0_SL_CTL       BRSHW_IOS(uint32, 0x40004010ul)
  #define BRSHW_PERI_GR1_CLOCK_CTL    BRSHW_IOS(uint32, 0x40004020ul)
  #define BRSHW_PERI_GR1_SL_CTL       BRSHW_IOS(uint32, 0x40004030ul)
  #define BRSHW_PERI_GR2_CLOCK_CTL    BRSHW_IOS(uint32, 0x40004040ul)
  #define BRSHW_PERI_GR2_SL_CTL       BRSHW_IOS(uint32, 0x40004050ul)
  #define BRSHW_PERI_GR3_CLOCK_CTL    BRSHW_IOS(uint32, 0x40004060ul)
  #define BRSHW_PERI_GR3_SL_CTL       BRSHW_IOS(uint32, 0x40004070ul)
  #define BRSHW_PERI_GR5_CLOCK_CTL    BRSHW_IOS(uint32, 0x400040A0ul)
  #define BRSHW_PERI_GR5_SL_CTL       BRSHW_IOS(uint32, 0x400040B0ul)
  #define BRSHW_PERI_GR6_CLOCK_CTL    BRSHW_IOS(uint32, 0x400040C0ul)
  #define BRSHW_PERI_GR6_SL_CTL       BRSHW_IOS(uint32, 0x400040D0ul)
  #define BRSHW_PERI_GR9_CLOCK_CTL    BRSHW_IOS(uint32, 0x40004120ul)
  #define BRSHW_PERI_GR9_SL_CTL       BRSHW_IOS(uint32, 0x40004130ul)
 
  #define BRSHW_PERI_DIV_CMD          BRSHW_IOS(uint32, 0x40000400ul)
  #define BRSHW_PERI_DIV_8_CTL(n)     BRSHW_IOS(uint32, 0x40001000ul + 0x4 * n) /* n=0..31 (32 x 8bit divider) */
  #define BRSHW_PERI_DIV_16_CTL(n)    BRSHW_IOS(uint32, 0x40001400ul + 0x4 * n) /* n=0..15 (16 x 16bit divider) */
  #define BRSHW_PERI_DIV_24_5_CTL(n)  BRSHW_IOS(uint32, 0x40001C00ul + 0x4 * n) /* n=0..7  (8 x 24.5bit divider) */
  #define BRSHW_PERI_CLOCK_CTL(n)     BRSHW_IOS(uint32, 0x40000C00ul + 0x4 * n) /* n=0..109 (110 programmable peripheral clocks) */
 
  #define BRSHW_CM4_CLOCK_CTL         BRSHW_IOS(uint32, 0x40200008ul)
  #define BRSHW_CM0_CLOCK_CTL         BRSHW_IOS(uint32, 0x40201008ul)
# endif /*BRS_DERIVATIVE_GROUP_TRAVEO2_BH*/
#endif /*BRS_ENABLE_PLLCLOCKS*/
 
#if defined (BRS_ENABLE_PORT)
/*******************************************************************************
 *  GPIO, Port configuration registers
 ********************************************************************************/
  /*--- Base address definitions ---*/
  #define BRS_GPIO_PRT_BASE         0x40310000UL
  #define BRS_HSIOM_PRT_BASE        0x40300000UL
 
  /*--- Register definitions ---*/
  #define BRS_GPIO_PRT_OUT(g)          BRSHW_IOS(uint32, BRS_GPIO_PRT_BASE + g*0x080u)          /* Port g output data register */
  #define BRS_GPIO_PRT_OUT_CLR(g)      BRSHW_IOS(uint32, BRS_GPIO_PRT_BASE + g*0x080U + 0x004U) /* Port g output data clear register */
  #define BRS_GPIO_PRT_OUT_SET(g)      BRSHW_IOS(uint32, BRS_GPIO_PRT_BASE + g*0x080U + 0x008U) /* Port g output data set register */
  #define BRS_GPIO_PRT_OUT_INV(g)      BRSHW_IOS(uint32, BRS_GPIO_PRT_BASE + g*0x080U + 0x00CU) /* Port g output data invert register */
 
  #define BRS_GPIO_PRT_IN(g)           BRSHW_IOS(uint32, BRS_GPIO_PRT_BASE + g*0x080U + 0x010U) /* Port g input state register */
 
  #define BRS_GPIO_PRT_INTR(g)         BRSHW_IOS(uint32, BRS_GPIO_PRT_BASE + g*0x080U + 0x014U) /* Port g interrupt status register */
  #define BRS_GPIO_PRT_INTR_MASK(g)    BRSHW_IOS(uint32, BRS_GPIO_PRT_BASE + g*0x080U + 0x018U) /* Port g interrupt mask register */
  #define BRS_GPIO_PRT_INTR_MASKED(g)  BRSHW_IOS(uint32, BRS_GPIO_PRT_BASE + g*0x080U + 0x01CU) /* Port g interrupt masked status register */
  #define BRS_GPIO_PRT_INTR_SET(g)     BRSHW_IOS(uint32, BRS_GPIO_PRT_BASE + g*0x080U + 0x020U) /* Port g interrupt set register */
 
  #define BRS_GPIO_PRT_INTR_CFG(g)     BRSHW_IOS(uint32, BRS_GPIO_PRT_BASE + g*0x080U + 0x040U) /* Port g interrupt configuration register */
 
  #define BRS_GPIO_PRT_CFG(g)          BRSHW_IOS(uint32, BRS_GPIO_PRT_BASE + g*0x080U + 0x044U) /* Port g configuration register */
  #define BRS_GPIO_PRT_CFG_IN(g)       BRSHW_IOS(uint32, BRS_GPIO_PRT_BASE + g*0x080U + 0x048U) /* Port g input configuration register */
  #define BRS_GPIO_PRT_CFG_OUT(g)      BRSHW_IOS(uint32, BRS_GPIO_PRT_BASE + g*0x080U + 0x04CU) /* Port g output configuration register */
 
  #define BRS_HSIOM_PRT_PORT_SEL0(g)   BRSHW_IOS(uint32, BRS_HSIOM_PRT_BASE + g*0x010U + 0x000U) /* HSIOM (High-Speed IO-Mux) port select register 0*/
  #define BRS_HSIOM_PRT_PORT_SEL1(g)   BRSHW_IOS(uint32, BRS_HSIOM_PRT_BASE + g*0x010U + 0x004U) /* HSIOM (High-Speed IO-Mux) port select register 1*/
#endif /*BRS_ENABLE_PORT*/
 
/**********************************************************
 *  CM4 Interrupt Controller/Multiplexer
 *********************************************************/
#define CPUSS_CM4_SYSTEM_BASE  0x4020A000uL
#define CPUSS_CM4_SYSTEM_INT_CTL(x)    BRSHW_IOS(uint32, CPUSS_CM4_SYSTEM_BASE + x*4U) /* System Cortex-M4 Interrupt Control Register */
 
/**********************************************************
 *  CM7 Interrupt Controller/Multiplexer
 *********************************************************/
#define CPUSS_CM7_SYSTEM_BASE  0x4020A000uL
#define CPUSS_CM7_SYSTEM_INT_CTL(x, y)  (*(volatile uint32*) (CPUSS_CM7_SYSTEM_BASE + ((x) * 0x2000U) + ((y) * 4UL)))
 
#define CPUSS_SYSTEM_INT_CTL_ENABLED_BIT  (1uL << 31) /* CPUSS_CM4_SYSTEM_INT_CTL Regiter: ENABLED flag */
 
/**********************************************************************************************************************
 *  LOCAL VARIABLES
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  LOCAL CONST VARIABLES
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  PROTOTYPES OF GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/* part of ArmCommon */
 
/**********************************************************************************************************************
 *  PROTOTYPES OF LOCAL FUNCTIONS
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#if defined (BRS_DERIVATIVE_GROUP_TRAVEO2_BH)
/* clear lock bit of CM7 CRTL for multiple writes of VTOR */
  BRS_SECTION_CODE(brsStartup)
  BRS_GLOBAL(brsPreAsmStartupHook)
  BRS_MULTILINE_ASM_BEGIN()
  BRS_LABEL(brsPreAsmStartupHook)
  /* clear lock bit of CM7_0 */
  __as1(ldr r0, =0x4020000C)
  __as1(ldr r1, [r0])
  __as1(ldr r2, =0xFFFFFFF7)
  __as2(and r1, r1, r2)
  __as1(str r1, [r0])
 
# if (BRS_CPU_CORE_AMOUNT > 1)
  /* clear lock bit of CM7_1 */
  __as1(ldr r0, =0x4020040C)
  __as1(ldr r1, [r0])
  __as1(ldr r2, =0xFFFFFFF7)
  __as2(and r1, r1, r2)
  __as1(str r1, [r0])
# endif
 
  BRS_BRANCH(coreRegisterInit)
  BRS_MULTILINE_ASM_END()
  BRS_GLOBAL_END()
  BRS_SECTION_CODE(text)
#endif /*BRS_DERIVATIVE_GROUP_TRAVEO2_BH*/
 
#if defined (BRS_ENABLE_WATCHDOG)
/*****************************************************************************/
/* @brief      This function must be used to initialize the Watchdog.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsMainInit() at power on initialization
 *****************************************************************************/
void BrsHwWatchdogInitPowerOn(void)
{
  /* WDG unlock: Lock release musst be performed in a two different write accesses */
  BRS_WDT_LOCK = 0x00000001;
  __asm("NOP");
  BRS_WDT_LOCK = 0x00000002;
 
  /*1. Step: WDT_LOCK = 0x1
  * 2. Step: WDT_LOCK = 0x2
  */
 
  /*dissable Watchdog ENABLE=0*/
  BRS_WDT_CTL = (0U << 31U);
  __asm("NOP");
  __asm("NOP");
  __asm("NOP");
 
  /*WDG lock in a single write*/
  BRS_WDT_LOCK = (3U << 0U);
}
#endif /*BRS_ENABLE_WATCHDOG*/
 
#if defined (BRS_ENABLE_PLLCLOCKS)
/*****************************************************************************/
/* @brief      This function must be used to initialize the PLL.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsMainInit() at power on initialization
 *****************************************************************************/
void BrsHwPllInitPowerOn(void)
{
  /* Configuration checks */
#if (BRS_TIMEBASE_CLOCK > BRS_CPU_MAX_FREQUENCY)
  #error "The selected derivative does not support frequencies above BRS_CPU_MAX_FREQUENCY (please find the defined value inside the Cfg5 BRS PreConfig for your Derivative)."
#endif
 
  uint32 idx;
#if defined (BRS_PLL_GROUP_A) || defined (BRS_PLL_GROUP_A1)
/*
 * PLL/Clock initialization for Traveo-II Body-Entry
 */
# if ((BRS_OSC_CLK == 16) || (BRS_OSC_CLK == 24)) && (BRS_TIMEBASE_CLOCK == 160) && (BRS_PERIPH_CLOCK == 160)
  /*0.1 External Oscillator (ECO) setup */
  BRSHW_CLK_TRIM_ECO_CTL &= 0xFFFF0000;
  BRSHW_CLK_TRIM_ECO_CTL |= 0x00002FC6;
 
  /* 0. enable ECO (external crystal osc) */
  BRSHW_CLK_ECO_CONFIG |= 0x80000000;
 
  /* 1. wait until ECO is stable */
  while ((BRSHW_CLK_ECO_STATUS & 0x00000003) != 0x00000003);
 
  /* 2. select DSI source = ILO and PLL source = ECO (external crystal osc) */
  BRSHW_CLK_DSI_SELECT(0) = 0x00000010;  /*ILO #0 selected*/
  BRSHW_CLK_PATH_SELECT(1) = 0x00000002;  /*ECO selected*/
  BRSHW_CLK_PATH_SELECT(0) = 0x00000002;  /*ECO selected*/
  BRSHW_CLK_PATH_SELECT(2) = 0x00000002;  /*ECO selected*/
  BRSHW_CLK_OUTPUT_FAST    = 0x00000011;
 
  /* 3. set FEEDBACK_DIV, REFERENCE_DIV, and OUTPUT_DIV
      Input frequency: Fref
      Output frequency: PLL_OUT
      Reference div: Q
      Feedback div: P
 
      Fref = 16MHz
 
      Fpfd = Fref / Q. It must be in the range 4 MHz to 8 MHz
      => 16MHz / Q -> Q = 4, Fpfd = 4MHz
 
      VCO = Fpfd * P. It must be in the range 170 MHz to 400 MHz.
      => 4MHz * P ->  P = 80, VCO = 320MHz
 
      PLL_OUT = VCO / OUTPUT_DIV. It must be in the range 11 MHz to 160 MHz.
      => 320MHz / OUTPUT_DIV -> OUTPUT_DIV = 2, PLL_OUT = 160MHz
 
      CM4 clock = CLK_HF = PLL_OUT = 160MHz
      CM0 clock = CLK_SLOW = CLK_HF / 2 = 80MHz
      CLK_PERI = CLK_HF / 2 = 80MHz
      CAN/LIN clock = CLK_GR5 = CLK_PERI / 1 = 80MHz
      SMARTIO clock = CLK_GR3 = CLK_PERI / 1 = 80MHz
      SerialCommsBlock = SCB clock = CLK_GR6 = CLK_PERI / 1 = 80MHz
      SMARTIO PCLK = CLK_PERI / 2 = 40MHz
      CANFD PCLK = CLK_PERI / 2 = 40MHz
      LIN PCLK = CLK_PERI / 2 = 40MHz
      SCB PCLK = CLK_PERI / 2 = 40MHz
  */
#  if (BRS_OSC_CLK == 16)
  BRSHW_CLK_PLL_CONFIG(0) = 0x00020450;
#  elif (BRS_OSC_CLK == 24)
  BRSHW_CLK_PLL_CONFIG(0) = 0x00020650;
#  else
  #error "Only (BRS_OSC_CLK=16 & BRS_OSC_CLK == 24 is currently supported for Traveo-II B-E!"
#  endif
 
  /* 4. wait at least on cycle */
  BRSHWNOP10();
 
  /* 4.4 Set-up of the wait states for Flash, RAM0, RAM1 and ROM */
 
  /* Wait state for Flash MAIN_WS[3:0] = 1 */
  BRSHW_FLASHC_FLASH_CTL |= 0x00000001;
 
  /* Wait states for RAM0, RAM1 und ROM */
  /* SLOW_WS[1:0] = '1' (from 100 MHz to 160 MHz of clk_hf.)*/
  /* FAST_WS[9:8] = '1' (should FAST_WS <= SLOW_WS) */
  BRSHW_CPUSS_RAM0_CTL |= 0x00000101;
  BRSHW_CPUSS_RAM1_CTL |= 0x00000101;
  BRSHW_CPUSS_ROM_CTL  |= 0x00000101;
 
  /* 8. select PLL=Clock Path #1 for HF_CLK with predivider=NO_DIV (1) */
  BRSHW_CLK_ROOT_SELECT(0) = 0x00000101;
  BRSHW_CLK_ROOT_SELECT(1) = 0x00000101;
  BRSHWNOP10();
  BRSHW_CLK_ROOT_SELECT(0) |= 0x80000000;
  BRSHW_CLK_ROOT_SELECT(1) |= 0x80000000;
 
  /* 9. select MCore SYSTICK Timer clk source = CLK_HF0 / 2 */
  /* has to be divided, as timer frequency has to be lower than 100MHz */
  /* BRSHW_CLK_TIMER_CTL = 0x00000101; Obsolete. Do not use in new design. Keep default value in new designs.*/
  /* BRSHWNOP10(); */
  /* BRSHW_CLK_TIMER_CTL |= 0x80000000; Obsolete. Do not use in new design. Keep default value in new designs.*/
 
  /* 10. select dividers: CLK_PERI = CLK_HF0 / 2, CLK_SLOW = CLK_HF0 / 1 */
  BRSHW_CM0_CLOCK_CTL = 0x01000000;
 
  /* 11. select divider: CLK_FAST = CLK_HF0 / 1 */
  BRSHW_CM4_CLOCK_CTL = 0x00000000;  /* if 0 than div = 1, if 1 than div = 2 */
 
  /* 12. select divider for peripheral group 5 (CAN+LIN): CLK_GR5=CLK_PERI / 1 */
  BRSHW_PERI_GR5_CLOCK_CTL = 0x00000000;
 
  /* 13. select divider for peripheral group 3 (SMARTIO/TCPWM): CLK_GR3=CLK_PERI / 1 */
  BRSHW_PERI_GR3_CLOCK_CTL = 0x00000000;
 
  /* 14. select divider for peripheral group 6 (SerialCommsBlock = SCB): CLK_GR6=CLK_PERI / 1 */
  BRSHW_PERI_GR6_CLOCK_CTL = 0x00000000;
 
  /* 15. peripheral group 0+1+2+3+5+6 -> all peripheral slaves enabled */
  BRSHW_PERI_GR0_SL_CTL = 0x0000FFFF;
  BRSHW_PERI_GR1_SL_CTL = 0x0000FFFF;
  BRSHW_PERI_GR2_SL_CTL = 0x0000FFFF;
  BRSHW_PERI_GR3_SL_CTL = 0x0000FFFF;
  BRSHW_PERI_GR5_SL_CTL = 0x0000FFFF;
  BRSHW_PERI_GR6_SL_CTL = 0x0000FFFF;
 
  /* 16. setup peripheral 8bit clock dividers, one divider per module:
     SMARTIO, CANFD, LIN, SCB */
  /* disable divider 8bit divider #0 for SMARTIO */
  BRSHW_PERI_DIV_CMD = 0x43FF0000;
  /* wait until disabled */
  while (((BRSHW_PERI_DIV_CMD & 0x40000000) != 0) || (((BRSHW_PERI_DIV_8_CTL(0)) & 0x00000001) != 0));
  /* configure 8bit divider #0 = CLK_PERI / 2 => 40MHz */
  BRSHW_PERI_DIV_8_CTL(0) = 0x00000100;
  /* enable divider 8bit divider #0 */
  BRSHW_PERI_DIV_CMD = 0x83FF0000;
  /* wait until enabled */
  while (((BRSHW_PERI_DIV_CMD & 0x80000000) != 0) || (((BRSHW_PERI_DIV_8_CTL(0)) & 0x00000001) == 0));
 
  /* disable divider 8bit divider #1 for CANFD */
  BRSHW_PERI_DIV_CMD = 0x43FF0001;
  /* wait until disabled */
  while (((BRSHW_PERI_DIV_CMD & 0x40000000) != 0) || (((BRSHW_PERI_DIV_8_CTL(1)) & 0x00000001) != 0));
  /* configure 8bit divider #1 = CLK_PERI / 2 => 40MHz */
  BRSHW_PERI_DIV_8_CTL(1) = 0x00000100;
  /* enable divider 8bit divider #1 */
  BRSHW_PERI_DIV_CMD = 0x83FF0001;
  /* wait until enabled */
  while (((BRSHW_PERI_DIV_CMD & 0x80000000) != 0) || (((BRSHW_PERI_DIV_8_CTL(1)) & 0x00000001) == 0));
 
  /* disable divider 8bit divider #2 for LIN */
  BRSHW_PERI_DIV_CMD = 0x43FF0002;
  /* wait until disabled */
  while (((BRSHW_PERI_DIV_CMD & 0x40000000) != 0) || (((BRSHW_PERI_DIV_8_CTL(2)) & 0x00000001) != 0));
  /* configure 8bit divider #2 = CLK_PERI / 2 => 40MHz */
  BRSHW_PERI_DIV_8_CTL(2) = 0x00000100;
  /* enable divider 8bit divider #2 */
  BRSHW_PERI_DIV_CMD = 0x83FF0002;
  /* wait until enabled */
  while (((BRSHW_PERI_DIV_CMD & 0x80000000) != 0) || (((BRSHW_PERI_DIV_8_CTL(2)) & 0x00000001) == 0));
 
  /* disable divider 8bit divider #3 for SCB */
  BRSHW_PERI_DIV_CMD = 0x43FF0003;
  /* wait until disabled */
  while (((BRSHW_PERI_DIV_CMD & 0x40000000) != 0) || (((BRSHW_PERI_DIV_8_CTL(3)) & 0x00000001) != 0));
  /* configure 8bit divider #3 = CLK_PERI / 2 => 40MHz */
  BRSHW_PERI_DIV_8_CTL(3) = 0x00000100;
  /* enable divider 8bit divider #3 */
  BRSHW_PERI_DIV_CMD = 0x83FF0003;
  /* wait until enabled */
  while (((BRSHW_PERI_DIV_CMD & 0x80000000) != 0) || (((BRSHW_PERI_DIV_8_CTL(3)) & 0x00000001) == 0));
 
  /* disable divider 8bit divider #3 for SCB */
  BRSHW_PERI_DIV_CMD = 0x43FF0004;
  /* wait until disabled */
  while (((BRSHW_PERI_DIV_CMD & 0x40000000) != 0) || (((BRSHW_PERI_DIV_8_CTL(4)) & 0x00000001) != 0));
  /* configure 8bit divider #3 = CLK_PERI / 2 => 40MHz */
  BRSHW_PERI_DIV_8_CTL(3) = 0x00000F00;
  /* enable divider 8bit divider #3 */
  BRSHW_PERI_DIV_CMD = 0x83FF0004;
  /* wait until enabled */
  while (((BRSHW_PERI_DIV_CMD & 0x80000000) != 0) || (((BRSHW_PERI_DIV_8_CTL(4)) & 0x00000001) == 0));
 
  /* add Test clock for LIN */
  /* disable divider divider #2 for LIN */
  BRSHW_PERI_DIV_CMD = 0x43FF0301;
  /* wait until disabled */
  while (((BRSHW_PERI_DIV_CMD & 0x40000000) != 0) || (((BRSHW_PERI_DIV_24_5_CTL(1)) & 0x00000001) != 0));
  /* configure  divider #2 = CLK_PERI / ?? => 16 * baudrate */
#if (baudrate == 19200)
  BRSHW_PERI_DIV_24_5_CTL(1) = 0x00010468;
#elif  (baudrate == 10417)
  BRSHW_PERI_DIV_24_5_CTL(1) = 0x0001E000;
#elif  (baudrate == 11177)
  BRSHW_PERI_DIV_24_5_CTL(1) = 0x0001BF58;
#elif  (baudrate == 2000)
  BRSHW_PERI_DIV_24_5_CTL(1) = 0x0009C400;
#elif  (baudrate == 20000)
  BRSHW_PERI_DIV_24_5_CTL(1) = 0x0000FA00;
#else
  BRSHW_PERI_DIV_24_5_CTL(1) = 0x00010468;
#endif
  /* enable divider divider #2 */
  BRSHW_PERI_DIV_CMD = 0x83FF0301;
  /* wait until enabled */
  while (((BRSHW_PERI_DIV_CMD & 0x80000000) != 0) || (((BRSHW_PERI_DIV_24_5_CTL(1)) & 0x00000001) == 0));
 
  /* 17. configure peripheral clock multiplexer for modules: SMARTIO, CANFD, LIN, SCB */
  /* select 8bit divider #0 for SMARTIO #12, #13, #14, #15, #16 */
 /* BRSHW_PERI_CLOCK_CTL(1) = 0x00000000;
  BRSHW_PERI_CLOCK_CTL(2) = 0x00000000;
  BRSHW_PERI_CLOCK_CTL(3) = 0x00000000;
  BRSHW_PERI_CLOCK_CTL(4) = 0x00000000;
  BRSHW_PERI_CLOCK_CTL(5) = 0x00000000;*/
  /* select 8bit divider #1 for CANFD0_CLOCK_CAN0 */
  BRSHW_PERI_CLOCK_CTL(6) = 0x00000001;
  /* select 8bit divider #1 for CANFD0_CLOCK_CAN1 */
  BRSHW_PERI_CLOCK_CTL(7) = 0x00000001;
  /* select 8bit divider #1 for CANFD0_CLOCK_CAN2 */
  BRSHW_PERI_CLOCK_CTL(8) = 0x00000001;
  /* select 8bit divider #1 for CANFD1_CLOCK_CAN0 */
  BRSHW_PERI_CLOCK_CTL(9) = 0x00000001;
  /* select 8bit divider #1 for CANFD1_CLOCK_CAN1 */
  BRSHW_PERI_CLOCK_CTL(10) = 0x00000001;
  /* select 8bit divider #1 for CANFD1_CLOCK_CAN2 */
  BRSHW_PERI_CLOCK_CTL(11) = 0x00000001;
  /* select 8bit divider #2 for LIN_CLOCK_CH_EN0 */
  BRSHW_PERI_CLOCK_CTL(12) = 0x00000301;
  /* select 8bit divider #2 for LIN_CLOCK_CH_EN1 */
  BRSHW_PERI_CLOCK_CTL(13) = 0x00000002;
  /* select 8bit divider #2 for LIN_CLOCK_CH_EN2 */
  BRSHW_PERI_CLOCK_CTL(14) = 0x00000002;
  /* select 8bit divider #2 for LIN_CLOCK_CH_EN3 */
  BRSHW_PERI_CLOCK_CTL(15) = 0x00000002;
  /* select 8bit divider #2 for LIN_CLOCK_CH_EN4 */
  BRSHW_PERI_CLOCK_CTL(16) = 0x00000002;
  /* select 8bit divider #2 for LIN_CLOCK_CH_EN5 */
  BRSHW_PERI_CLOCK_CTL(17) = 0x00000002;
  /* select 8bit divider #2 for LIN_CLOCK_CH_EN6 */
  BRSHW_PERI_CLOCK_CTL(18) = 0x00000002;
  /* select 8bit divider #2 for LIN_CLOCK_CH_EN7 */
  BRSHW_PERI_CLOCK_CTL(19) = 0x00000002;
  /* select 8bit divider #3 for SCB0_CLOCK */
  BRSHW_PERI_CLOCK_CTL(20) = 0x00000003;
  /* select 8bit divider #3 for SCB1_CLOCK */
  BRSHW_PERI_CLOCK_CTL(21) = 0x00000003;
  /* select 8bit divider #3 for SCB2_CLOCK */
  BRSHW_PERI_CLOCK_CTL(22) = 0x00000003;
  /* select 8bit divider #3 for SCB3_CLOCK */
  BRSHW_PERI_CLOCK_CTL(23) = 0x00000003;
  /* select 8bit divider #3 for SCB4_CLOCK */
  BRSHW_PERI_CLOCK_CTL(24) = 0x00000003;
  /* select 8bit divider #3 for SCB5_CLOCK */
  BRSHW_PERI_CLOCK_CTL(25) = 0x00000003;
  /* select 8bit divider #3 for SCB6_CLOCK */
  BRSHW_PERI_CLOCK_CTL(26) = 0x00000003;
  /* select 8bit divider #3 for SCB7_CLOCK */
  BRSHW_PERI_CLOCK_CTL(27) = 0x00000003;
 
  /* select divider for FBL clock sources */
 
  /*select 8bit divider #0 for TCPWM counter 0*/
  BRSHW_PERI_CLOCK_CTL(106) = 0x00000000;
  /*select 8bit divider #0 for TCPWM counter 1*/
  BRSHW_PERI_CLOCK_CTL(107) = 0x00000000;
 
  /*select 8bit divider #0 for TCPWM counter 0*/
  BRSHW_PERI_CLOCK_CTL(116) = 0x00000000;
  /*select 8bit divider #0 for TCPWM counter 1*/
  BRSHW_PERI_CLOCK_CTL(117) = 0x00000000;
  /*select 8bit divider #0 for TCPWM counter 2*/
  BRSHW_PERI_CLOCK_CTL(118) = 0x00000000;
 
  /* 5. Enable PLL */
  BRSHW_CLK_PLL_CONFIG(0) |= 0x80000000;
 
  /* 6. wait at least 1us - 160MHz core clock -> 6.25ns/cycle, 1 cycle per NOP, 1us/6.25ns=160 NOPS required! */
  for (idx=0; idx<17; idx++) BRSHWNOP10();
 
  /* 7. wait until PLL is locked (needs about 50us) */
  while ((BRSHW_CLK_PLL_STATUS(0) & 0x00000001) == 0);
 
# else
  #error "Only (BRS_OSC_CLK=24 || BRS_OSC_CLK=16 && BRS_TIMEBASE_CLOCK=160 && BRS_PERIPH_CLOCK=80) is currently supported for Traveo-II B-E!"
# endif /*BRS_OSC_CLK==16&&BRS_TIMEBASE_CLOCK==160&&BRS_PERIPH_CLOCK==80*/
#endif /*BRS_PLL_GROUP_A||BRS_PLL_GROUP_A1*/
 
#if defined (BRS_PLL_GROUP_B)
/*
 * PLL/Clock initialization for Traveo-II Body-High
 */
# if (BRS_OSC_CLK == 16) && (BRS_PERIPH_CLOCK == 320)
  /* 1.0 Setup the External Crystal Oscillator (ECO) */
  BRSHW_CLK_ECO_CONFIG2 = 0x00003FC6;
  /* 1.1 Enable the ECO */
  BRSHW_CLK_ECO_CONFIG |= 0x80000000;
  /* 1.2 Wait until ECO is stable */
  while (0x00000003 != (BRSHW_CLK_ECO_STATUS & 0x00000003));
 
  /* 2.0 Set DSI Mux clock to Internal Low-speed Oscillator #0 (ILO0) */
  BRSHW_CLK_DSI_SELECT(1) = 0x00000010;
  BRSHW_CLK_DSI_SELECT(3) = 0x00000010;
  /* 2.1 Set ECO as the fREF (16 MHz) to PLL0, without Spread Spectrum Clock Generation */
  BRSHW_CLK_PATH_SELECT(1) = 0x00000002;
  BRSHWNOP10();
  /* 2.2 Set ECO as the fREF (16 MHz) to PLL400M0 (PLL2), with Spread Spectrum Clock Generation and fractional operation */
  BRSHW_CLK_PATH_SELECT(3) = 0x00000002;
  BRSHWNOP10();
 
  
  /* 3.0 Set PLL400M0 output frequency to 350 MHz
   * Set PLL400M0 bypass mux to PLL_REF before changing the configuration
   * Static phase error window = 20 ns, Auto BYPASS_SEL, Disable spreading mode
   * fOUT = (FEEDBACK_DIV + FRAC_DIV/2^24) * (fREF / REFERENCE_DIV) / (OUTPUT_DIV)
   * FEEDBACK_DIV = 175, REFERENCE_DIV = 4, OUTPUT_DIV = 2, FRAC_DIV = 0
   */
  BRSHW_CLK_PLL400M0_CONFIG = 0x20020116;
  BRSHWNOP10();
  BRSHWNOP10(); // added
  BRSHWNOP10(); // added
  BRSHWNOP10(); // added
  BRSHWNOP10(); // added
  BRSHW_CLK_PLL400M0_CONFIG = BRS_TIMEBASE_CLOCK / 2; /* st FEEDBACK_DIV according to configured core frequency */
  BRSHWNOP10(); // added
  BRSHWNOP10(); // added
  BRSHWNOP10(); // added
  BRSHWNOP10(); // added
  BRSHW_CLK_PLL400M0_CONFIG |= 0x00020400; /* set other dividers */
  __asm("NOP");
  /* 3.1 Enable PLL#2 (PLL400M0) */
  BRSHW_CLK_PLL400M0_CONFIG |= 0x80000000;
  /* 3.2 Wait at least 1us (fPLL400M0 = 350 MHz) */
  for(idx = 0; idx < 36; idx++)
  {
    BRSHWNOP10();
  }
  /* 3.3 Wait until PLL400M0 is locked */
  while ((uint32)0 == (BRSHW_CLK_PLL400M0_STATUS & 0x00000001));
 
  /* 4.0 Set CLK_FAST_0 divider for CM7_0 (Divide CLK_HF1 by 1) */
  BRSHW_CPUSS_FAST_0_CLOCK_CTL = 0x00000000;
  /* 4.1 Set CLK_FAST_1 divider for CM7_1 (Divide CLK_HF1 by 1) */
  BRSHW_CPUSS_FAST_1_CLOCK_CTL = 0x00000000;
 
  /* 5.0 Select CLK_PATHx (PLL400M0) as a source to CLK_HF1 root clock, and enable the clock root
   * BRSHW_CLK_ROOT_SELECT(1) = 0x00000103; according to TvII B-H TRM No. 002-24402 Rev.A, Sep. 12, 2018
   * BRSHW_CLK_ROOT_SELECT(1) = 0x00000101; CLK_PATH1 is configured for PLL400M0 on HSR-5152 and HSR-5149
   */
  BRSHW_CLK_ROOT_SELECT(1) = 0x80000101;
  BRSHWNOP10();
 
  /* 6.0 Set PLL0 output frequency to 160 MHz
   * Set PLL0 bypass mux to PLL_REF before changing the configuration
   * Static phase error window = 20.66 ns, Auto BYPASS_SEL
   * fOUT = (FEEDBACK_DIV) * (fREF / REFERENCE_DIV) / (OUTPUT_DIV)
   * FEEDBACK_DIV = 80, REFERENCE_DIV = 4, OUTPUT_DIV = 2, VCO freq = 320 MHz
   */
  BRSHW_CLK_PLL0_CONFIG = 0x20020116;
  BRSHWNOP10();
  BRSHW_CLK_PLL0_CONFIG = 0x00020450;
  __asm("NOP");
  /* 6.1 Enable PLL0 */
  BRSHW_CLK_PLL0_CONFIG |= 0x80000000;
  /* 6.2 Wait at least 1us (fPLL0 = 160 MHz) */
  for(idx = 0; idx < 17; idx++)
  {
    BRSHWNOP10();
  }
  /* 6.3 Wait until PLL0 is locked */
  while ((uint32)0 == (BRSHW_CLK_PLL0_STATUS & 0x00000001));
 
  /* 7.0 Set SysTick timer clock to 80 MHz (must be less than 100 MHz) */
  /* BRSHW_CLK_TIMER_CTL -> Obsolete. Do not use in new designs.
   *                        Keep default value in new designs.
   * accord to
   * TRAVEO (TM) II AUTOMOTIVE BODY CONTROLLER HIGH REGISTERS TECHNICAL
   * REFERENCE MANUAL (TRM)(TVII-B-H-8M) Document No. 002-24402 Rev. *F
   * and
   * TRAVEO (TM) II AUTOMOTIVE BODY CONTROLLER HIGH REGISTERS TECHNICAL
   * REFERENCE MANUAL (TRM)(TVII-B-H-4M) Document No. 002-27182 Rev. *A
   * default: TIMER_DIV=7
   */
  /* BRSHW_CPUSS_SYSTICK_CTL default: select "clk_lf"
   * (per default: ILO=32768Hz) as systick clock source
   */
 
  /* 8.0 Set CLK_MEM to 80 MHz (Divide CLK_HF0 by 2) */
  BRSHW_CPUSS_MEM_CLOCK_CTL = 0x00000100;
  /* 8.1 Set CLK_SLOW to 40 MHz (Divide CLK_MEM by 2). CLK_SLOW = CLK_GR0 = CLK_GR1 = CLK_GR2 */
  BRSHW_CPUSS_SLOW_CLOCK_CTL = 0x00000100;
  /* 8.2 Set CLK_PERI to 80 MHz (Divide CLK_HF0 by 2) */
  BRSHW_CPUSS_PERI_CLOCK_CTL = 0x00000100;
  /* 8.3 Set CLK_TRC_DBG to 40 MHz (Divide CLK_HF0 by 4) */
  BRSHW_CPUSS_TRC_DBG_CLOCK_CTL = 0x00000300;
 
  /* 9.0 Set CLK_GR3 to 80 MHz for TCPWM[0], SMARTIO and event generator (Divide CLK_PERI by 1) */
  BRSHW_PERI_GR_CLOCK_CTL(3) = 0x00000000;
  /* 9.1 Set CLK_GR4 to 40 MHz for SDHC (Divide CLK_PERI by 2) */
  BRSHW_PERI_GR_CLOCK_CTL(4) = 0x00000100;
  /* 9.2 Set CLK_GR8 to 80 MHz for AUDIOSS (Divide CLK_PERI by 1) */
  BRSHW_PERI_GR_CLOCK_CTL(8) = 0x00000000;
 
  /* 10.0 Set wait states for ROM/SRAM/FLASH */
  BRSHW_FLASHC_FLASH_CTL |= 0x00000001;
  BRSHW_CPUSS_ROM_CTL = 0x00000101;
  BRSHW_CPUSS_RAM0_CTL |= 0x00000101;
  BRSHW_CPUSS_RAM1_CTL |= 0x00000101;
  BRSHW_CPUSS_RAM2_CTL |= 0x00000101;
 
  /* 10.1 Set CLK_PATH1 (PLL0) as a source to CLK_HF0 root clock
   * BRSHW_CLK_ROOT_SELECT(0) = 0x00000101; according to TvII B-H TRM No. 002-24402 Rev.A, Sep. 12, 2018
   * BRSHW_CLK_ROOT_SELECT(0) = 0x00000103; CLK_PATH3 is configured for PLL0 on HSR-5152 and HSR-5149
   */
  BRSHW_CLK_ROOT_SELECT(0) = 0x00000103;
  BRSHWNOP10();
 
  /* 10.2 Enable peripheral slaves for GR3, GR4 and GR8 (root clock CLK_HF0) */
  BRSHW_PERI_GR_SL_CTL(3) |= 0x00000008;
  BRSHW_PERI_GR_SL_CTL(4) |= 0x00000010;
  BRSHW_PERI_GR_SL_CTL(8) |= 0x00000100;
 
  /* 11.0 Set CLK_GR5 to 40 MHz for CANFD, FlexRay, LIN and TCPWM[1] (Divide CLK_HF2 by 4) */
  BRSHW_PERI_GR_CLOCK_CTL(5) = 0x00000300;
  /* 11.1 Set CLK_GR6 to 80 MHz for SCB "Serial Communications Block" (Divide CLK_HF2 by 2) */
  BRSHW_PERI_GR_CLOCK_CTL(6) = 0x00000100;
  /* 11.2 Set CLK_GR9 to 26.67 MHz for SAR ADC (Divide CLK_HF2 by 6) */
  BRSHW_PERI_GR_CLOCK_CTL(9) = 0x00000500;
 
  /* 12.0 Set CLK_PATH1 (PLL0) as a source to CLK_HF2 root clock, and enable the clock root
   * BRSHW_CLK_ROOT_SELECT(2) = 0x00000101; according to TvII B-H TRM No. 002-24402 Rev.A, Sep. 12, 2018
   * BRSHW_CLK_ROOT_SELECT(2) = 0x00000103; CLK_PATH3 is configured for PLL0 on HSR-5152 and HSR-5149
   */
  BRSHW_CLK_ROOT_SELECT(2) = 0x00000103;
  BRSHWNOP10();
  BRSHW_CLK_ROOT_SELECT(2) |= 0x80000000;
 
  /* 12.1 Enable peripheral slaves for GR5, GR6 and GR9 (root clock CLK_HF2) */
  BRSHW_PERI_GR_SL_CTL(5) |= 0x00000020;
  BRSHW_PERI_GR_SL_CTL(6) |= 0x00000040;
  BRSHW_PERI_GR_SL_CTL(9) |= 0x00000200;
  /* 12.2 Enable peripheral slaves for GR0, GR1 and GR2 */
  BRSHW_PERI_GR_SL_CTL(0) |= 0x00000001;
  BRSHW_PERI_GR_SL_CTL(1) |= 0x00000002;
  BRSHW_PERI_GR_SL_CTL(2) |= 0x00000004;
 
  /* Set peripheral clock divider for CANFD */
  /* 13.0 Disable 8-bit divider#0 */
  BRSHW_PERI_PCLK_GR1_DIV_CMD = 0x43FF0000;
  /* 13.1 Wait until 8-bit divider#0 is disabled */
  while (((uint32)0 != ((BRSHW_PERI_PCLK_GR1_DIV_8_CTL(0)) & 0x00000001)) || ((uint32)0 != (BRSHW_PERI_PCLK_GR1_DIV_CMD & 0x40000000)));
  /* 13.2 Set 8-bit divider#0 to 40 MHz (Divide CLK_HF2 by 4) */
  BRSHW_PERI_PCLK_GR1_DIV_8_CTL(0) |= 0x00000300;
  /* 13.3 Enable 8-bit divider#0 */
  BRSHW_PERI_PCLK_GR1_DIV_CMD = 0x83FF0000;
  /* 13.4 Wait until 8-bit divider#0 is enabled */
  while(((uint32)0 == ((BRSHW_PERI_PCLK_GR1_DIV_8_CTL(0)) & 0x00000001)) || ((uint32)0 != (BRSHW_PERI_PCLK_GR1_DIV_CMD & 0x80000000)));
  /* 13.5 Select 8-bit divider#0 for CAN#0 Channel#n : n = [0, 4] */
  for(idx = 0; idx < 5; idx++)
  {
    BRSHW_PERI_PCLK_GR1_CLOCK_CTL(idx) = 0x00000000;
  }
  /* 13.6 Select 8-bit divider#0 for CAN#1 Channel#n : n = [0, 4] */
  for(idx = 5; idx < 10; idx++)
  {
    BRSHW_PERI_PCLK_GR1_CLOCK_CTL(idx) = 0x00000000;
  }
 
  /* Set peripheral clock divider for LIN*/  
  /* 14.0 Disable 24.5-bit divider#1 */
  BRSHW_PERI_PCLK_GR1_DIV_CMD = 0x43FF0301;
  /* 14.1 Wait until 24.5-bit divider#1 is disabled */
  while (((uint32)0 != ((BRSHW_PERI_PCLK_GR1_DIV_24_5_CTL(1)) & 0x00000001)) || ((uint32)0 != (BRSHW_PERI_PCLK_GR1_DIV_CMD & 0x40000000)));
  /* 14.2 Set 24.5-bit divider#1 to ... */
  /* now use 24.5 devider -> CLK_HF2 is actually 350MHz  */
#if (baudrate == 19200)
  BRSHW_PERI_PCLK_GR1_DIV_24_5_CTL(1) = 0x00047350;
#elif  (baudrate == 10417)
  BRSHW_PERI_PCLK_GR1_DIV_24_5_CTL(1) = 0x000833F0;
#elif  (baudrate == 11177)
  BRSHW_PERI_PCLK_GR1_DIV_24_5_CTL(1) = 0x0007A528;
#elif  (baudrate == 2000)
  BRSHW_PERI_PCLK_GR1_DIV_24_5_CTL(1) = 0x002AB980;
#elif  (baudrate == 20000)
  BRSHW_PERI_PCLK_GR1_DIV_24_5_CTL(1) = 0x000445C0;
#else /* default baudrate 19200 */
  BRSHW_PERI_PCLK_GR1_DIV_24_5_CTL(1) = 0x00047350;
#endif
  /* 14.3 Enable 24.5-bit divider#1 */
  BRSHW_PERI_PCLK_GR1_DIV_CMD = 0x83FF0301;
  /* 14.4 Wait until 24.5-bit divider#1 is enabled */
  while(((uint32)0 == ((BRSHW_PERI_PCLK_GR1_DIV_24_5_CTL(1)) & 0x00000001)) || ((uint32)0 != (BRSHW_PERI_PCLK_GR1_DIV_CMD & 0x80000000)));
  /* 14.5 Select 24.5-bit divider#1 for LIN channel#n : n = [0, 20] */
  for(idx = 10; idx < 31; idx++)
  {
    BRSHW_PERI_PCLK_GR1_CLOCK_CTL(idx) = 0x00000301;
  }
 
  /* Set peripheral clock divider for FlexRay */
  /* 15.0 Disable 8-bit divider#2 */
  BRSHW_PERI_PCLK_GR1_DIV_CMD = 0x43FF0002;
  /* 15.1 Wait until 8-bit divider#2 is disabled */
  while (((uint32)0 != ((BRSHW_PERI_PCLK_GR1_DIV_8_CTL(2)) & 0x00000001)) || ((uint32)0 != (BRSHW_PERI_PCLK_GR1_DIV_CMD & 0x40000000)));
  /* 15.2 Set 8-bit divider#2 to 40 MHz (Divide CLK_HF2 by 4) */
  BRSHW_PERI_PCLK_GR1_DIV_8_CTL(2) |= 0x00000300;
  /* 15.3 Enable 8-bit divider#2 */
  BRSHW_PERI_PCLK_GR1_DIV_CMD = 0x83FF0002;
  /* 15.4 Wait until 8-bit divider#2 is enabled */
  while(((uint32)0 == ((BRSHW_PERI_PCLK_GR1_DIV_8_CTL(2)) & 0x00000001)) || ((uint32)0 != (BRSHW_PERI_PCLK_GR1_DIV_CMD & 0x80000000)));
  /* 15.5 Select 8-bit divider#2 for FlexRay clock */
  BRSHW_PERI_PCLK_GR1_CLOCK_CTL(41) = 0x00000002;
 
  /* Set peripheral clock divider for Serial communications Block (SCB) */
  /* 16.0 Disable 8-bit divider#3 */
  BRSHW_PERI_PCLK_GR1_DIV_CMD = 0x43FF0003;
  /* 16.1 Wait until 8-bit divider#3 is disabled */
  while (((uint32)0 != ((BRSHW_PERI_PCLK_GR1_DIV_8_CTL(3)) & 0x00000001)) || ((uint32)0 != (BRSHW_PERI_PCLK_GR1_DIV_CMD & 0x40000000)));
  /* 16.2 Set 8-bit divider#3 to 40 MHz (Divide CLK_HF2 by 4) */
  BRSHW_PERI_PCLK_GR1_DIV_8_CTL(3) |= 0x00000300;
  /* 16.3 Enable 8-bit divider#3 */
  BRSHW_PERI_PCLK_GR1_DIV_CMD = 0x83FF0003;
  /* 16.4 Wait until 8-bit divider#3 is enabled */
  while(((uint32)0 == ((BRSHW_PERI_PCLK_GR1_DIV_8_CTL(3)) & 0x00000001)) || ((uint32)0 != (BRSHW_PERI_PCLK_GR1_DIV_CMD & 0x80000000)));
  /* Select 8-bit divider#3 for SCB#n : n = [0, 10] */
  for(idx = 30; idx < 41; idx++)
  {
    BRSHW_PERI_PCLK_GR1_CLOCK_CTL(idx) = 0x00000003;
  }
 
  /* Set peripheral clock divider for SMARTIO */
  /* 17.0 Disable 8-bit divider#0 */
  BRSHW_PERI_PCLK_GR0_DIV_CMD = 0x43FF0000;
  /* 17.1 Wait until 8-bit divider#0 is disabled */
  while (((uint32)0 != ((BRSHW_PERI_PCLK_GR0_DIV_8_CTL(0)) & 0x00000001)) || ((uint32)0 != (BRSHW_PERI_PCLK_GR0_DIV_CMD & 0x40000000)));
  /* 17.2 Set 8-bit divider#0 to 40 MHz (Divide CLK_PERI by 2) */
  BRSHW_PERI_PCLK_GR0_DIV_8_CTL(0) |= 0x00000100;
  /* 17.3 Enable 8-bit divider#0 */
  BRSHW_PERI_PCLK_GR0_DIV_CMD = 0x83FF0000;
  /* 17.4 Wait until 8-bit divider#0 is enabled */
  while(((uint32)0 == ((BRSHW_PERI_PCLK_GR0_DIV_8_CTL(0)) & 0x00000001)) || ((uint32)0 != (BRSHW_PERI_PCLK_GR0_DIV_CMD & 0x80000000)));
  /* 17.5 Select 8-bit divider#0 for Smart I/O #n : n = 12, 13, 14, 15 or 17 */
  for(idx = 1; idx < 6; idx++)
  {
    BRSHW_PERI_PCLK_GR0_CLOCK_CTL(idx) = 0x00000000;
  }
 
  /* 17.6 Select 8-bit divider CLK_GR3 for TCPWM[0] timer */
  BRSHW_PERI_PCLK_GR0_CLOCK_CTL(12) = 0x00000000;
  BRSHW_PERI_PCLK_GR0_CLOCK_CTL(13) = 0x00000000;
 
  /* 18.0 Set peripheral clock divider for Ethernet
   * CLK_GR4 (40 MHz), CLK_MEM (80 MHz) or CLK_HF0 (160 MHz) can be configured as a source clock to Ethernet PHY
   * (Tx_CLK, Rx_CLK, REF_CLK) in the Ethernet MAC module according to the PHY interface
   */
 
# else
  #error "Only (BRS_OSC_CLK=16 && BRS_PERIPH_CLOCK=320) is currently supported for Traveo-II B-H!"
# endif /*BRS_OSC_CLK==16&&BRS_PERIPH_CLOCK==320*/
#endif /*BRS_PLL_GROUP_B*/
}
#endif /*BRS_ENABLE_PLLCLOCKS*/
 
#if defined (BRS_ENABLE_PORT)
/*******************************************************************************
 *  Port Pin initialization helper functions for usage of BrsHw_Ports.h
 *******************************************************************************/
/*****************************************************************************/
/* @brief      This function configures the drive mode for a port pin.
 * @pre        Drive mode configuartions available within BrsHw_Ports.h
 * @param[in]  p - brsHw_Port_PortType, to be initialized.
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsHwPortInitPowerOn() locally.
 *****************************************************************************/
void BrsHwSetPortDriveMode(brsHw_Port_PortType p)
{
if (p.portAlternative != BRSHW_PORT_ALT_GPIO)
  {
    BRS_GPIO_PRT_CFG(p.portGroup) &= ~(uint32)(0x7 << 4U*p.portNumber);
    BRS_GPIO_PRT_CFG(p.portGroup) |= (uint32)(p.portDriveMode << 4U*p.portNumber);
  }
}
 
/*****************************************************************************/
/* @brief      This function sets port alternative mode registers
 *             and the drive mode of the port pin.
 * @pre        Port pin configuartions available within BrsHw_Ports.h and
 *             no DrvPort used for port pin initialization.
 * @param[in]  p - brsHw_Port_PortType, to be initialized.
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsHwInitPortInput() and
 *             BrsHwInitPortOutput() locally.
 *****************************************************************************/
void BrsHwInitPortAlternative(brsHw_Port_PortType p)
{
  if (p.portNumber < 4u)
  {
    BRS_HSIOM_PRT_PORT_SEL0(p.portGroup) &= ~(( 0x1Fu << (p.portNumber*8U) ));
    BRS_HSIOM_PRT_PORT_SEL0(p.portGroup) |= (uint32)( p.portAlternative << (p.portNumber*8U) );
  }
  else
  {
    BRS_HSIOM_PRT_PORT_SEL1(p.portGroup) &= ~(( 0x1Fu << ((p.portNumber-4U)*8U) ));
    BRS_HSIOM_PRT_PORT_SEL1(p.portGroup) |= (uint32)( p.portAlternative << ((p.portNumber-4U)*8U) );
  }
  BrsHwSetPortDriveMode(p);
  /*
   * Alternative function of PortNumbers: 0, 1, 2, 3
   * is defined by lower 5 bits of HSIOM_PRT_PORT_SEL0 register
   *
   * Alternative function of PortNumbers: 4, 5, 6, 7
   * is defined by lower 5 bits of HSIOM_PRT_PORT_SEL1 register
  */
}
 
/*****************************************************************************/
/* @brief      This function configures a port pin as input pin.
 * @pre        Port pin configurations available within BrsHw_Ports.h and
 *             no DrvPort used for port pin initialization.
 * @param[in]  p - brsHw_Port_PortType, to be initialized.
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsHwPortInitPowerOn() and
 *             provided to external modules (e.g. driver testsuits).
 *****************************************************************************/
void BrsHwInitPortInput(brsHw_Port_PortType p)
{
  if (p.portAlternative == BRSHW_PORT_ALT_GPIO)
  {
    BRS_GPIO_PRT_CFG(p.portGroup) |= (1U << (3U + 4U*p.portNumber)) | (0U << (0U + 4U*p.portNumber));
    /* Bit 3: IN_EN - Intput pin enable bit -> '1' (Pin input buffer enabled)
     * Bit 2-0: Drive_Mode - High Impedance mode -> 000 (0x0)
     * General rule to set PortNumber_x configuration:
     * Bit 0-3: PortNumber0
     * Bit 4-7: PortNumber1
     * Bit 11-8: PortNumber2
     * Bit 15-12: PortNumber3
     * ...
     * Bit 31-28: PortNumber7
     */
 
    /* Default setting BRS_GPIO_PRT_CFG_IN = 0x00000000
     * --> CMOS input
     *  BRS_GPIO_PRT_CFG_IN(p.PortGroup) = (0u << p.portNumber); --> CMOS
     *  BRS_GPIO_PRT_CFG_IN(p.PortGroup) = (1u << p.portNumber); --> TTL
     */
  }
  else
  {
    BRS_GPIO_PRT_CFG(p.portGroup) |= (1U << (3U + 4U*p.portNumber)) | (0U << (0U + 4U*p.portNumber));
    BrsHwInitPortAlternative(p);
  }
}
 
/*****************************************************************************/
/* @brief      This function configures a port pin as output pin.
 * @pre        Port pin configurations available within BrsHw_Ports.h and
 *             no DrvPort used for port pin initialization.
 * @param[in]  p - brsHw_Port_PortType, to be initialized.
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsHwPortInitPowerOn() and
 *             provided to external modules (e.g. driver testsuits).
 *****************************************************************************/
void BrsHwInitPortOutput(brsHw_Port_PortType p)
{
  if (p.portAlternative == BRSHW_PORT_ALT_GPIO)
  {
    BRS_GPIO_PRT_CFG(p.portGroup) &= ~((0xFU << (4U*p.portNumber)));
    BRS_GPIO_PRT_CFG(p.portGroup) |= ((0x6U << (4U*p.portNumber)));
    /* Bit 3: IN_EN - Intput pin enable bit -> '0' (Pin input buffer disabled & pin output enabled)
     * Bit 2-0: Drive_Mode - Strong -> 110 (0x6)
     * General rule to set PortNumber_x configuration:
     * Bit 0-3: PortNumber0
     * Bit 4-7: PortNumber1
     * Bit 11-8: PortNumber2
     * Bit 15-12: PortNumber3
     * ...
     * Bit 31-28: PortNumber7
     */
 
    BRS_GPIO_PRT_OUT_CLR(p.portGroup) = (1u << p.portNumber);
    /* set output to 0 */
  }
  else
  {
    /* Disable the IN_EN0(Input Buffer) for the IO. */
    BRS_GPIO_PRT_CFG(p.portGroup) &= ~(1UL << (3UL + 4UL*p.portNumber));
    BrsHwInitPortAlternative(p);
  }
}
 
/*****************************************************************************/
/* @brief      This function configures a port pin as input and output pin.
 * @pre        Port pin configurations available within BrsHw_Ports.h and
 *             no DrvPort used for port pin initialization.
 * @param[in]  p - brsHw_Port_PortType, to be initialized.
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsHwPortInitPowerOn() and
 *             provided to external modules (e.g. driver testsuits).
 *****************************************************************************/
void BrsHwInitPortInputOutput(brsHw_Port_PortType p)
{
  if (p.portAlternative == BRSHW_PORT_ALT_GPIO)
  {
    BRS_GPIO_PRT_CFG(p.portGroup) &= ~((0xFU << (4U*p.portNumber))); /* Clear the Bits for the configured port number */
    BRS_GPIO_PRT_CFG(p.portGroup) |= ((0xEU << (4U*p.portNumber)));
    /* Bit 3: IN_EN - Intput pin enable bit -> '1' (Pin input buffer enabled)
     * Bit 2-0: Drive_Mode - Strong -> 110 (0x6)
     * General rule to set PortNumber_x configuration:
     * Bit 0-3: PortNumber0
     * Bit 4-7: PortNumber1
     * Bit 11-8: PortNumber2
     * Bit 15-12: PortNumber3
     * ...
     * Bit 31-28: PortNumber7
     */
 
    /* Default setting BRS_GPIO_PRT_CFG_IN = 0x00000000
     * --> CMOS input
     *  BRS_GPIO_PRT_CFG_IN(p.PortGroup) = (0u << p.portNumber); --> CMOS
     *  BRS_GPIO_PRT_CFG_IN(p.PortGroup) = (1u << p.portNumber); --> TTL
     */
 
    BRS_GPIO_PRT_OUT_CLR(p.portGroup) = (1u << p.portNumber);
    /* set output to 0 */
  }
  else
  {
    BrsHwInitPortAlternative(p);
  }
}
 
# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_START_SEC_RAM_CODE
  #include "Brs_MemMap.h"
# endif
/*****************************************************************************/
/* @brief      This function sets the output level of a port pin.
 * @pre        Port pin configurations available within BrsHw_Ports.h,
 *             no DrvPort used for port pin initialization and
 *             transferred port pin has to be initialized as output pin with
 *             GPIO functionality.
 * @param[in]  p     - brsHw_Port_PortType, to be set,
 *             Level - level, port pin has to be set to
 *                     (BRSHW_PORT_LOGIC_LOW or BRSHW_PORT_LOGIC_HIGH).
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsHwPortInitPowerOn() and
 *             provided to external modules (e.g. BrsMainTogglePin()).
 *****************************************************************************/
void BrsHwPort_SetLevel(brsHw_Port_PortType p, uint8 Level)
{
  if( Level == 0u)
    BRS_GPIO_PRT_OUT_CLR(p.portGroup) = (1u << (p.portNumber));
  else if( Level == 1u)
    BRS_GPIO_PRT_OUT_SET(p.portGroup) = (1u << (p.portNumber));
}
 
/*****************************************************************************/
/* @brief      This function reads the input level of a port pin.
 * @pre        Port pin configurations available within BrsHw_Ports.h,
 *             no DrvPort used for port pin initialization and
 *             transferred port pin has to be initialized as input pin with
 *             GPIO functionality.
 * @param[in]  p - brsHw_Port_PortType, to be read.
 * @param[out] -
 * @return     Level, read from port pin
 *             (BRSHW_PORT_LOGIC_LOW or BRSHW_PORT_LOGIC_HIGH).
 * @context    Function is provided to external modules.
 *****************************************************************************/
uint8 BrsHwPort_GetLevel(brsHw_Port_PortType p)
{
  uint32 temp;
  temp = BRS_GPIO_PRT_IN(p.portGroup);
  temp &= (1 << p.portNumber);
 
  if(temp != 0x00000000)
  {
    return BRSHW_PORT_LOGIC_HIGH;
  }
  else
  {
    return BRSHW_PORT_LOGIC_LOW;
  }
}
# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_STOP_SEC_RAM_CODE
  #include "Brs_MemMap.h"
# endif
 
/*****************************************************************************/
/* @brief      This function must be used to initialize the used ports.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsMainInit() at power on initialization
 *****************************************************************************/
void BrsHwPortInitPowerOn(void)
{
#if defined (BRS_ENABLE_SUPPORT_LEDS)
  BrsHwInitPortOutput(BRSHW_PORT_LED);
 
  /* Set LED on EVB demo board to show the system is alive */
  BrsMainTogglePin(BRSMAIN_TOGGLEPIN_LED);
#endif
 
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN)
  BrsHwInitPortOutput(BRSHW_PORT_TOGGLE_WD);
#endif
 
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
  BrsHwInitPortOutput(BRSHW_PORT_TOGGLE_CUSTOM);
#endif
 
/*******************************************************************************
 *  CAN driver
 *******************************************************************************/
#if defined (BRS_ENABLE_CAN_SUPPORT)
# if defined (BRS_ENABLE_CAN_CHANNEL_0)
  BrsHwInitPortOutput(BRSHW_PORT_CAN0_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN0_RX);
#  if defined(_BRSHW_PORT_CAN0_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN0_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN0_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
#  if defined (_BRSHW_PORT_CAN0_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN0_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN0_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_CAN_CHANNEL_0*/
 
# if defined (BRS_ENABLE_CAN_CHANNEL_1)
  BrsHwInitPortOutput(BRSHW_PORT_CAN1_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN1_RX);
#  if defined(_BRSHW_PORT_CAN1_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN1_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN1_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
#  if defined (_BRSHW_PORT_CAN1_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN1_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN1_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_CAN_CHANNEL_1*/
 
# if defined (BRS_ENABLE_CAN_CHANNEL_2)
  BrsHwInitPortOutput(BRSHW_PORT_CAN2_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN2_RX);
#  if defined(_BRSHW_PORT_CAN2_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN2_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN2_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
#  if defined (_BRSHW_PORT_CAN2_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN2_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN2_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_CAN_CHANNEL_2*/
 
# if defined (BRS_ENABLE_CAN_CHANNEL_3)
  BrsHwInitPortOutput(BRSHW_PORT_CAN3_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN3_RX);
#  if defined(_BRSHW_PORT_CAN3_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN3_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN3_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
#  if defined (_BRSHW_PORT_CAN3_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN3_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN3_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_CAN_CHANNEL_3*/
 
# if defined (BRS_ENABLE_CAN_CHANNEL_4)
  BrsHwInitPortOutput(BRSHW_PORT_CAN4_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN4_RX);
#  if defined(_BRSHW_PORT_CAN4_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN4_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN4_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
#  if defined (_BRSHW_PORT_CAN4_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN4_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN4_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_CAN_CHANNEL_4*/
 
# if defined (BRS_ENABLE_CAN_CHANNEL_5)
  BrsHwInitPortOutput(BRSHW_PORT_CAN5_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN5_RX);
#  if defined(_BRSHW_PORT_CAN5_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN5_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN5_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
#  if defined (_BRSHW_PORT_CAN5_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN5_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN5_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_CAN_CHANNEL_5*/
 
# if defined (BRS_ENABLE_CAN_CHANNEL_6)
  BrsHwInitPortOutput(BRSHW_PORT_CAN6_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN6_RX);
#  if defined(_BRSHW_PORT_CAN6_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN6_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN6_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
#  if defined (_BRSHW_PORT_CAN6_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN6_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN6_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_CAN_CHANNEL_6*/
 
# if defined (BRS_ENABLE_CAN_CHANNEL_7)
  BrsHwInitPortOutput(BRSHW_PORT_CAN7_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN7_RX);
#  if defined(_BRSHW_PORT_CAN7_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN7_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN7_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
#  if defined (_BRSHW_PORT_CAN7_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN7_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN7_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_CAN_CHANNEL_7*/
 
# if defined (BRS_ENABLE_CAN_CHANNEL_8)
  BrsHwInitPortOutput(BRSHW_PORT_CAN8_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN8_RX);
#  if defined(_BRSHW_PORT_CAN8_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN8_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN8_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
#  if defined (_BRSHW_PORT_CAN8_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN8_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN8_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_CAN_CHANNEL_8*/
 
# if defined (BRS_ENABLE_CAN_CHANNEL_9)
  BrsHwInitPortOutput(BRSHW_PORT_CAN9_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN9_RX);
#  if defined(_BRSHW_PORT_CAN9_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN9_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN9_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
#  if defined (_BRSHW_PORT_CAN9_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN9_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN9_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_CAN_CHANNEL_9*/
#endif /*BRS_ENABLE_CAN_SUPPORT*/
 
/*******************************************************************************
 *  LIN driver
 *******************************************************************************/
#if defined (BRS_ENABLE_LIN_SUPPORT)
# if defined (BRS_ENABLE_LIN_CHANNEL_0)
  BrsHwInitPortOutput(BRSHW_PORT_LIN0_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN0_RX);
#  if defined(_BRSHW_PORT_LIN0_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_LIN0_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_LIN0_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_LIN_CHANNEL_0*/
 
# if defined (BRS_ENABLE_LIN_CHANNEL_1)
  BrsHwInitPortOutput(BRSHW_PORT_LIN1_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN1_RX);
#  if defined(_BRSHW_PORT_LIN1_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_LIN1_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_LIN1_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_LIN_CHANNEL_1*/
 
# if defined (BRS_ENABLE_LIN_CHANNEL_2)
  BrsHwInitPortOutput(BRSHW_PORT_LIN2_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN2_RX);
#  if defined (_BRSHW_PORT_LIN2_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_LIN2_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_LIN2_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_LIN_CHANNEL_2*/
 
# if defined (BRS_ENABLE_LIN_CHANNEL_3)
  BrsHwInitPortOutput(BRSHW_PORT_LIN3_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN3_RX);
#  if defined(_BRSHW_PORT_LIN3_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_LIN3_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_LIN3_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_LIN_CHANNEL_3*/
 
# if defined (BRS_ENABLE_LIN_CHANNEL_4)
  BrsHwInitPortOutput(BRSHW_PORT_LIN4_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN4_RX);
#  if defined(_BRSHW_PORT_LIN4_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_LIN4_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_LIN4_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_LIN_CHANNEL_4*/
 
# if defined (BRS_ENABLE_LIN_CHANNEL_5)
  BrsHwInitPortOutput(BRSHW_PORT_LIN5_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN5_RX);
#  if defined(_BRSHW_PORT_LIN5_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_LIN5_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_LIN5_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*BRS_ENABLE_LIN_CHANNEL_5*/
 
# if defined (BRS_ENABLE_LIN_CHANNEL_6) || defined (BRS_ENABLE_LIN_CHANNEL_7) || \
     defined (BRS_ENABLE_LIN_CHANNEL_8) || defined (BRS_ENABLE_LIN_CHANNEL_9) || \
     defined (BRS_ENABLE_LIN_CHANNEL_10) || defined (BRS_ENABLE_LIN_CHANNEL_11)
  #error "Port config for your LIN channel not yet implemented"
# endif
#endif /*BRS_ENABLE_LIN_SUPPORT*/
 
/*******************************************************************************
 *  FLEXRAY driver
 *******************************************************************************/
#if defined (BRS_ENABLE_FLEXRAY_SUPPORT)
  #error "FlexRay pins not yet supported"
#endif
 
/*******************************************************************************
 *  ETHERNET driver
 *******************************************************************************/
  /* Eth0 */
#if defined (BRS_ENABLE_ETHERNET_SUPPORT)
  /* -- Transmitter signals -- */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_REFCLK);
  BrsHwInitPortInput(BRSHW_PORT_ETH0_TXCLK);
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXD0);
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXD1);
# if defined (_BRSHW_PORT_ETH0_TXD2)
  /* Transmit signal 2 is obsolete within RMII */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXD2);
# endif
# if defined (_BRSHW_PORT_ETH0_TXD3)
  /* Transmit signal 3 is obsolete within RMII */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXD3);
# endif
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXEN);
# if defined (_BRSHW_PORT_ETH0_TXER)
  /* Transmit Error signal is only optional within MII and obsolete within RMII */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXER);
# endif
 
  /* -- Receiver signals -- */
# if defined (_BRSHW_PORT_ETH0_RXCLK)
  /* Receive clock signal is obsolete within RMII */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXCLK);
# endif
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXD0);
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXD1);
# if defined (_BRSHW_PORT_ETH0_RXD2)
  /* Receive signal 2 is obsolete within RMII */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXD2);
# endif
# if defined (_BRSHW_PORT_ETH0_RXD3)
  /* Receive signal 3 is obsolete within RMII */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXD3);
# endif
# if defined (_BRSHW_PORT_ETH0_RXERR)
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXERR);
# endif
  BrsHwInitPortInput(BRSHW_PORT_ETH0_CRSDV);
 
  /* -- Management signals -- */
  BrsHwInitPortInputOutput(BRSHW_PORT_ETH0_MDIO);
# if defined (_BRSHW_PORT_ETH0_MDC)
  /* Management data clock not always needed */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_MDC);
# endif
 
# if defined (_BRSHW_PORT_ETH0_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_ETH0_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
# endif
 
  /* Eth1 */
# if defined (BRS_EVA_BOARD_8M_320_CPU_BOARD)
  /* -- Transmitter signals -- */
  BrsHwInitPortInput(BRSHW_PORT_ETH1_TXCLK);
  BrsHwInitPortOutput(BRSHW_PORT_ETH1_TXD0);
  BrsHwInitPortOutput(BRSHW_PORT_ETH1_TXD1);
# if defined (_BRSHW_PORT_ETH1_TXD2)
  /* Transmit signal 2 is obsolete within RMII */
  BrsHwInitPortOutput(BRSHW_PORT_ETH1_TXD2);
# endif
# if defined (_BRSHW_PORT_ETH1_TXD3)
  /* Transmit signal 3 is obsolete within RMII */
  BrsHwInitPortOutput(BRSHW_PORT_ETH1_TXD3);
# endif
  BrsHwInitPortOutput(BRSHW_PORT_ETH1_TXEN);
# if defined (_BRSHW_PORT_ETH0_TXERR)
  /* Transmit Error signal is only optional within MII and obsolete within RMII */
  BrsHwInitPortOutput(BRSHW_PORT_ETH1_TXERR);
# endif
 
  /* -- Receiver signals -- */
# if defined (_BRSHW_PORT_ETH1_RXCLK)
  /* Receive clock signal is obsolete within RMII */
  BrsHwInitPortInput(BRSHW_PORT_ETH1_RXCLK);
# endif
  BrsHwInitPortInput(BRSHW_PORT_ETH1_RXD0);
  BrsHwInitPortInput(BRSHW_PORT_ETH1_RXD1);
# if defined (_BRSHW_PORT_ETH1_RXD2)
  /* Receive signal 2 is obsolete within RMII */
  BrsHwInitPortInput(BRSHW_PORT_ETH1_RXD2);
# endif
# if defined (_BRSHW_PORT_ETH1_RXD3)
  /* Receive signal 3 is obsolete within RMII */
  BrsHwInitPortInput(BRSHW_PORT_ETH1_RXD3);
# endif
# if defined (_BRSHW_PORT_ETH1_RXERR)
  BrsHwInitPortInput(BRSHW_PORT_ETH1_RXERR);
# endif
  BrsHwInitPortInput(BRSHW_PORT_ETH1_CRSDV);
 
  /* -- Management signals -- */
  BrsHwInitPortInputOutput(BRSHW_PORT_ETH1_MDIO);
# if defined (_BRSHW_PORT_ETH1_MDC)
  /* Management data clock not always needed */
  BrsHwInitPortOutput(BRSHW_PORT_ETH1_MDC);
# endif
  BrsHwInitPortInput(BRSHW_PORT_ETH1_REFCLK);
# if defined (_BRSHW_PORT_ETH1_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_ETH1_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_ETH1_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
# endif
#endif /* BRS_EVA_BOARD_8M_320_CPU_BOARD */
#endif /*BRS_ENABLE_ETHERNET_SUPPORT*/
 
/*******************************************************************************
 *  I2C driver
 *******************************************************************************/
#if defined (BRS_ENABLE_I2C_SUPPORT)
# if defined (BRS_ENABLE_I2C_CHANNEL_0)
  BrsHwInitPortOutput(BRSHW_PORT_I2C0_CLK);
  BrsHwInitPortInputOutput(BRSHW_PORT_I2C0_DATA);
# endif
 
# if defined (BRS_ENABLE_I2C_CHANNEL_1)
  BrsHwInitPortOutput(BRSHW_PORT_I2C1_CLK);
  BrsHwInitPortInputOutput(BRSHW_PORT_I2C1_DATA);
# endif
#endif /*BRS_ENABLE_I2C_SUPPORT*/
 
/*******************************************************************************
 *  HYPERBUS driver
 ********************************************************************************/
#if defined (BRS_ENABLE_HYPERBUS_SUPPORT)
/* All ports must be configured as input/output (Input buffer on). Otherwise HB is not working! */
# if defined (BRS_ENABLE_HYPERBUS_CHANNEL_0)
  BrsHwInitPortInput(BRSHW_PORT_HYPERBUS0_DATA0);
  BrsHwInitPortInput(BRSHW_PORT_HYPERBUS0_DATA1);
  BrsHwInitPortInput(BRSHW_PORT_HYPERBUS0_DATA2);
  BrsHwInitPortInput(BRSHW_PORT_HYPERBUS0_DATA3);
  BrsHwInitPortInput(BRSHW_PORT_HYPERBUS0_DATA4);
  BrsHwInitPortInput(BRSHW_PORT_HYPERBUS0_DATA5);
  BrsHwInitPortInput(BRSHW_PORT_HYPERBUS0_DATA6);
  BrsHwInitPortInput(BRSHW_PORT_HYPERBUS0_DATA7);
  BrsHwInitPortInput(BRSHW_PORT_HYPERBUS0_CLK);
  BrsHwInitPortInput(BRSHW_PORT_HYPERBUS0_RWDS);
  BrsHwInitPortInput(BRSHW_PORT_HYPERBUS0_SEL0);
  BrsHwInitPortInput(BRSHW_PORT_HYPERBUS0_SEL1);
# endif /*BRS_ENABLE_HYPERBUS_CHANNEL_0*/
 
# if defined (BRS_ENABLE_HYPERBUS_CHANNEL_1)
  BrsHwInitPortInput(BRSHW_PORT_HYPERBUS1_DATA0);
  BrsHwInitPortInput(BRSHW_PORT_HYPERBUS1_DATA1);
  BrsHwInitPortInput(BRSHW_PORT_HYPERBUS1_DATA2);
  BrsHwInitPortInput(BRSHW_PORT_HYPERBUS1_DATA3);
  BrsHwInitPortInput(BRSHW_PORT_HYPERBUS1_DATA4);
  BrsHwInitPortInput(BRSHW_PORT_HYPERBUS1_DATA5);
  BrsHwInitPortInput(BRSHW_PORT_HYPERBUS1_DATA6);
  BrsHwInitPortInput(BRSHW_PORT_HYPERBUS1_DATA7);
  BrsHwInitPortInput(BRSHW_PORT_HYPERBUS1_CLK);
  BrsHwInitPortInput(BRSHW_PORT_HYPERBUS1_RWDS);
  BrsHwInitPortInput(BRSHW_PORT_HYPERBUS1_SEL0);
  BrsHwInitPortInput(BRSHW_PORT_HYPERBUS1_SEL1);
# endif /*BRS_ENABLE_HYPERBUS_CHANNEL_1*/
#endif /*BRS_ENABLE_HYPERBUS_SUPPORT*/
 
/*******************************************************************************
 *  SPI driver
 *******************************************************************************/
#if defined (BRS_ENABLE_SPI_SUPPORT)
# if defined (BRS_ENABLE_SPI_CHANNEL_0)
  BrsHwInitPortOutput(BRSHW_PORT_SPI0_CLK);
  BrsHwInitPortOutput(BRSHW_PORT_SPI0_MOSI);
  BrsHwInitPortInputOutput(BRSHW_PORT_SPI0_MISO);
  BrsHwInitPortOutput(BRSHW_PORT_SPI0_CS);
# endif
#endif /*BRS_ENABLE_SPI_SUPPORT*/
}
#endif /*BRS_ENABLE_PORT*/
 
/* BrsHwDisableInterruptAtPowerOn() is part of ArmCommon */
 
/* BrsHwSoftwareResetECU() is performed according to the ARM Spec and is part of ArmCommon */
 
#if defined (BRS_FIRST_EXECUTION_INSTANCE)
/* This code is only needed for the first instance/executable in the system */
#define BRS_START_SEC_STARTUP_CODE
#include "Brs_MemMap.h"
/*****************************************************************************/
/* @brief      Get reset reason
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     Reset reason
 * @context    Function is called from BrsMainStartup to determine if reset
 *             was triggered through software call (BrsHwSoftwareResetECU()).
 *             The result is stored by BrsMainStartup in the global variable
 *             brsMain_ResetReason. It should only be called once, during
 *             startup. The old API name BrsHwGetResetReason() is remapped
 *             to BrsMainGetResetReason.
 *****************************************************************************/
brsMain_ResetReasonType BrsHwGetResetReasonStartup(void)
{
  /* Catch "Reset Cause Copy" */
  if (BrsHw_GetCore() == BRSHW_INIT_CORE_ID)
  {
    BRSHW_RESET_CAUSE_COPY_COLD = BRSHW_RESET_CAUSE_COPY;
  }
 
  /* Determined based on the ResetCause stored in shared memory. */
  if(BRSHW_RESET_CAUSE_COPY & BRSHW_SWRESET_TRIGGERT_MASK)
  {
    /* Software Reset */
    return BRSMAIN_RESET_SW;
  }
  else
  {
    /* Other Reset */
    return BRSMAIN_RESET_OTHER;
  }
}
#define BRS_STOP_SEC_STARTUP_CODE
#include "Brs_MemMap.h"
#endif /*BRS_FIRST_EXECUTION_INSTANCE*/
 
/* BrsHwTime100NOP() is part of ArmCommon */
 
#if defined (BRS_ENABLE_SAFECTXSUPPORT)
/*****************************************************************************/
/* @brief      This API is used to enable hardware access in untrusted mode
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function must be called after all depending peripheral modules
 *             are supplied by proper clocks AND before the OS is started.
 *****************************************************************************/
void BrsHw_EnableHwAccess(void)
{
  /* nothing to be done for this platform yet (or never tested) */
  #error "Hardware access in UserMode not yet supported for your specific derivative!"
}
#endif /*BRS_ENABLE_SAFECTXSUPPORT*/
 
/*****************************************************************************/
/* @brief      This API is used to read the core ID of the actual running core
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     Core ID of the actual running core
 * @context    Function is e.g. called from main@BrsMain, to only call HW-init
 *             code once, on the boot core.
 *             In MultiCore setups, additional BRSHW_INIT_CORE_ID must be
 *             declared inside BrsHw.h, to configure the proper core ID value
 *             of that boot core.
 *****************************************************************************/
uint32 BrsHw_GetCore(void)
{
  return ((BRSHW_CPUSS_IDENTITY >> 8u) & BRSHW_CPUSS_IDENTITY_MASK);
}
 
/* BrsHw_EnableInterrupt() is part of ArmCommon */
 
/* BrsHw_DisableInterrupt() is part of ArmCommon */
 
/* BrsHw_TriggerSoftwareInterrupt() is part of ArmCommon */
 
#if defined (BRS_DERIVATIVE_GROUP_TRAVEO2_BH)
/*****************************************************************************/
/* @brief      This API is used to enable an external interrupt and route it
 *             to the Cortex-M7 core on TraveoII Body High derivatives.
 * @pre        -
 * @param[in]  SystemInterruptSource that has to be enabled.
 * @param[in]  CoreInterruptSource that has to be enabled.
 *             Only core interrupt sources [0...7] can be mapped to external interrupts.
 * @param[out] -
 * @return     -
 * @context
 *****************************************************************************/
void BrsHw_EnableExternalInterrupt(uint32 SystemInterruptSource, uint32 CoreInterruptSource)
{
  uint32 coreId = BrsHw_GetCore();
  /* Enable the core interrupt source */
  NVIC_ISER((uint32)(CoreInterruptSource/32)) = (1UL << (CoreInterruptSource%32));
  /* Enable the system interrupt source. */
  CPUSS_CM7_SYSTEM_INT_CTL(coreId, SystemInterruptSource) =  CPUSS_SYSTEM_INT_CTL_ENABLED_BIT | CoreInterruptSource;
}
 
/*****************************************************************************/
/* @brief      This API is used to disable an external interrupt for the
               Cortex-M7 core on TraveoII Body High derivatives.
 * @pre        -
 * @param[in]  SystemInterruptSource that has to be disabled.
 * @param[out] -
 * @return     -
 * @context
 *****************************************************************************/
void BrsHw_DisableExternalInterrupt(uint32 SystemInterruptSource)
{
  uint32 coreId = BrsHw_GetCore();
  /* Disable the system interrupt source. */
  CPUSS_CM7_SYSTEM_INT_CTL(coreId, SystemInterruptSource) &= ~(CPUSS_SYSTEM_INT_CTL_ENABLED_BIT);
}
 
#else
/*****************************************************************************/
/* @brief      This API is used to enable an external interrupt and route it
 *             to the Cortex-M4 core on TraveoII Body Entry derivatives.
 * @pre        -
 * @param[in]  SystemInterruptSource that has to be enabled.
 * @param[in]  CoreInterruptSource that has to be enabled.
 *             Only core interrupt sources [0...7] can be mapped to external interrupts.
 * @param[out] -
 * @return     -
 * @context
 *****************************************************************************/
void BrsHw_EnableExternalInterrupt(uint32 SystemInterruptSource, uint32 CoreInterruptSource)
{
  /* Enable the core interrupt source */
  NVIC_ISER((uint32)(CoreInterruptSource/32)) = (1UL << (CoreInterruptSource%32));
  /* Enable the system interrupt source. */
  CPUSS_CM4_SYSTEM_INT_CTL(SystemInterruptSource) = CPUSS_SYSTEM_INT_CTL_ENABLED_BIT | CoreInterruptSource;
}
 
/*****************************************************************************/
/* @brief      This API is used to disable an external interrupt for the
               Cortex-M4 core on TraveoII Body Entry derivatives.
 * @pre        -
 * @param[in]  SystemInterruptSource that has to be disabled.
 * @param[out] -
 * @return     -
 * @context
 *****************************************************************************/
void BrsHw_DisableExternalInterrupt(uint32 SystemInterruptSource)
{
  /* Disable the system interrupt source. */
  CPUSS_CM4_SYSTEM_INT_CTL(SystemInterruptSource) &= ~(CPUSS_SYSTEM_INT_CTL_ENABLED_BIT);
}
#endif /*BRS_DERIVATIVE_GROUP_Traveo2_x*/
 
#if defined (BRS_ENABLE_OS_MULTICORESUPPORT)
/*****************************************************************************/
/* @brief      This API is used as sync barrier. It is used to unlock cores
 *             that are locked in the Startup code. The implementation is only
 *             needed on platforms, where all cores are started automatically
 *             after a power-on reset. All additional cores are looped, until
 *             the boot core reaches this function.
 * @pre        -
 * @param[in]  uint32 coreId
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsMainStartup on the boot core.
 *****************************************************************************/
void BrsHw_UnlockCores(uint32 coreId)
{
  /* The mechanism is not used/needed on this platform */
}
#endif /*BRS_ENABLE_OS_MULTICORESUPPORT*/
 
 