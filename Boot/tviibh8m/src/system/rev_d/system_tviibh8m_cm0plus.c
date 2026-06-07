/***************************************************************************//**
* \file system_tviibh8m_cm0plus.c
* \version 1.0
*
* The device system-source file.
*
********************************************************************************
* \copyright
* Copyright 2018-2021, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "cy_device_headers.h"
#include "cy_project.h"

#if CY_SYSTEM_USE_CLOCK == CY_SYSTEM_USE_ECO
    #define CY_SYSTEM_PLL_INPUT_SOURCE       CY_SYSCLK_CLKPATH_IN_ECO

  #if (CY_SYS_PLL400M_0_FREQ == CY_SYS_PLL400M_0_350MHz)
    // PLL_OUT = 16,000,000(Feco) / 4 * 175 / 2 = 350,000,000Hz
    // Restriction: 400,000,000 <= Fvco <= 800,000,000
    // This time, Fvco = 16,000,000 * 175 / 4 = 700,000,000.
    #define CY_SYSTEM_PLL0_CONFIG_REFDIV      (4UL)
    #define CY_SYSTEM_PLL0_CONFIG_FEEDBACKDIV (175UL)
    #define CY_SYSTEM_PLL0_CONFIG_OUTDIV      (2UL)
  #elif (CY_SYS_PLL400M_0_FREQ == CY_SYS_PLL400M_0_320MHz)
    // PLL_OUT = 16,000,000(Feco) / 2 * 80 / 2 = 320,000,000Hz
    // Restriction: 400,000,000 <= Fvco <= 800,000,000
    // This time, Fvco = 16,000,000 * 80 / 2 = 640,000,000.
    #define CY_SYSTEM_PLL0_CONFIG_REFDIV      (2UL)
    #define CY_SYSTEM_PLL0_CONFIG_FEEDBACKDIV (80UL)
    #define CY_SYSTEM_PLL0_CONFIG_OUTDIV      (2UL)
  #elif (CY_SYS_PLL400M_0_FREQ == CY_SYS_PLL400M_0_250MHz)
    // PLL_OUT = 16,000,000(Feco) / 4 * 125 / 2 = 250,000,000Hz
    // Restriction: 400,000,000 <= Fvco <= 800,000,000
    // This time, Fvco = 16,000,000 * 125 / 4 = 500,000,000.
    #define CY_SYSTEM_PLL0_CONFIG_REFDIV      (4UL)
    #define CY_SYSTEM_PLL0_CONFIG_FEEDBACKDIV (125UL)
    #define CY_SYSTEM_PLL0_CONFIG_OUTDIV      (2UL)
  #else
    // PLL_OUT = 16,000,000(Feco) / 1 * 30 / 3 = 160,000,000Hz
    // Restriction: 400,000,000 <= Fvco <= 800,000,000
    // This time, Fvco = 16,000,000 * 30 / 1 = 480,000,000.
    #define CY_SYSTEM_PLL0_CONFIG_REFDIV      (1UL)
    #define CY_SYSTEM_PLL0_CONFIG_FEEDBACKDIV (30UL)
    #define CY_SYSTEM_PLL0_CONFIG_OUTDIV      (3UL)
  #endif

    // PLL_OUT = 16,000,000(Feco) / 2 * 98.30399996 / 4 = 196607999.92Hz
    // Restriction: 400,000,000 <= Fvco <= 800,000,000
    // This time, Fvco = 16,000,000 * 98.30399996 / 2 = 786431999.
    #define CY_SYSTEM_PLL1_CONFIG_REFDIV      (2UL)
    #define CY_SYSTEM_PLL1_CONFIG_FB_INT      (98UL)
    #define CY_SYSTEM_PLL1_CONFIG_FB_FRAC     (5100273UL)
    #define CY_SYSTEM_PLL1_CONFIG_OUTDIV      (4UL)

    // PLL_OUT = 16,000,000(Feco) / 2 * 40 / 2 = 160,000,000Hz
    // Restriction: 170,000,000 <= Fvco <= 400,000,000
    // This time, Fvco = 16,000,000 * 40 / 2 = 320,000,000.
    #define CY_SYSTEM_PLL2_CONFIG_REFDIV      (2UL)
    #define CY_SYSTEM_PLL2_CONFIG_FEEDBACKDIV (40UL)
    #define CY_SYSTEM_PLL2_CONFIG_OUTDIV      (2UL)

    // PLL_OUT = 16,000,000(Feco) / 2 * 40 / 4 = 80,000,000Hz
    // Restriction: 170,000,000 <= Fvco <= 400,000,000
    // This time, Fvco = 16,000,000 * 30 / 2 = 240,000,000.
    #define CY_SYSTEM_PLL3_CONFIG_REFDIV      (2UL)
    #define CY_SYSTEM_PLL3_CONFIG_FEEDBACKDIV (40UL)
    #define CY_SYSTEM_PLL3_CONFIG_OUTDIV      (4UL)

#elif CY_SYSTEM_USE_CLOCK == CY_SYSTEM_USE_IMO
    #define CY_SYSTEM_PLL_INPUT_SOURCE CY_SYSCLK_CLKPATH_IN_IMO

  #if (CY_SYS_PLL400M_0_FREQ == CY_SYS_PLL400M_0_350MHz)
    // PLL_OUT = 8,000,000(Fimo) / 2 * 175 / 2 = 350,000,000Hz
    // Restriction: 400,000,000 < Fvco < 800,000,000
    // This time, Fvco = 8,000,000 * 175 / 2 = 700,000,000.
    #define CY_SYSTEM_PLL0_CONFIG_REFDIV      (2UL)
    #define CY_SYSTEM_PLL0_CONFIG_FEEDBACKDIV (175UL)
    #define CY_SYSTEM_PLL0_CONFIG_OUTDIV      (2UL)
  #elif (CY_SYS_PLL400M_0_FREQ == CY_SYS_PLL400M_0_320MHz)
    // PLL_OUT = 8,000,000(Fimo) / 1 * 80 / 2 = 320,000,000Hz
    // Restriction: 400,000,000 < Fvco < 800,000,000
    // This time, Fvco = 8,000,000 * 80 / 1 = 640,000,000.
    #define CY_SYSTEM_PLL0_CONFIG_REFDIV      (1UL)
    #define CY_SYSTEM_PLL0_CONFIG_FEEDBACKDIV (80UL)
    #define CY_SYSTEM_PLL0_CONFIG_OUTDIV      (2UL)
  #elif (CY_SYS_PLL400M_0_FREQ == CY_SYS_PLL400M_0_250MHz)
    // PLL_OUT = 8,000,000(Fimo) / 2 * 125 / 2 = 250,000,000Hz
    // Restriction: 400,000,000 < Fvco < 800,000,000
    // This time, Fvco = 8,000,000 * 80 / 2 = 500,000,000.
    #define CY_SYSTEM_PLL0_CONFIG_REFDIV      (2UL)
    #define CY_SYSTEM_PLL0_CONFIG_FEEDBACKDIV (125UL)
    #define CY_SYSTEM_PLL0_CONFIG_OUTDIV      (2UL)
  #else
    // PLL_OUT = 8,000,000(Fimo) / 1 * 60 / 3 = 160,000,000Hz
    // Restriction: 400,000,000 < Fvco < 800,000,000
    // This time, Fvco = 8,000,000 * 60 / 1 = 480,000,000.
    #define CY_SYSTEM_PLL0_CONFIG_REFDIV      (1UL)
    #define CY_SYSTEM_PLL0_CONFIG_FEEDBACKDIV (60UL)
    #define CY_SYSTEM_PLL0_CONFIG_OUTDIV      (3UL)
  #endif

    // PLL_OUT = 8,000,000(Feco) / 1 * 98.30399996 / 4 = 196607999.92Hz
    // Restriction: 400,000,000 <= Fvco <= 800,000,000
    // This time, Fvco = 8,000,000 * 98.30399996 / 1 = 786431999.
    #define CY_SYSTEM_PLL1_CONFIG_REFDIV      (1UL)
    #define CY_SYSTEM_PLL1_CONFIG_FB_INT      (98UL)
    #define CY_SYSTEM_PLL1_CONFIG_FB_FRAC     (5100273UL)
    #define CY_SYSTEM_PLL1_CONFIG_OUTDIV      (4UL)

    // PLL_OUT = 8,000,000(Fimo) / 1 * 40 / 2 = 160,000,000Hz
    // Restriction: 170,000,000 <= Fvco <= 400,000,000
    // This time, Fvco = 8,000,000 * 40 / 1 = 320,000,000.
    #define CY_SYSTEM_PLL2_CONFIG_REFDIV      (1UL)
    #define CY_SYSTEM_PLL2_CONFIG_FEEDBACKDIV (40UL)
    #define CY_SYSTEM_PLL2_CONFIG_OUTDIV      (2UL)

    // PLL_OUT = 8,000,000(Fimo) / 1 * 30 / 3 = 80,000,000Hz
    // Restriction: 170,000,000 <= Fvco <= 400,000,000
    // This time, Fvco = 8,000,000 * 30 / 1 = 240,000,000.
    #define CY_SYSTEM_PLL3_CONFIG_REFDIV      (1UL)
    #define CY_SYSTEM_PLL3_CONFIG_FEEDBACKDIV (30UL)
    #define CY_SYSTEM_PLL3_CONFIG_OUTDIV      (3UL)

#elif CY_SYSTEM_USE_CLOCK == CY_SYSTEM_USE_EXT

    #warning "Not implemented yet!!"

#endif


#define CY_SYS_PWR_CTL_KEY_OPEN  (0x05FAUL)
#define CY_SYS_PWR_CTL_KEY_CLOSE (0xFA05UL)

/* Define maximum retry attempts before transition to DeepSleep */
#define MAX_RETRY_BEFORE_DEEP_SLEEP           (3U)

/* Define TIMEOUT value in micro-second for each setting */
/* The value is determined based on actual measurement results and calibration */
#define TIMEOUT_ECO_SETTING                   (69000UL)
#define TIMEOUT_CLK_PATH1_SETTING             (6900UL)
#define TIMEOUT_CLK_PATH2_SETTING             (6900UL)
#define TIMEOUT_CLK_PATH3_SETTING             (6900UL)
#define TIMEOUT_CLK_PATH4_SETTING             (6900UL)

/* Register & value for system reset request */
#define CM0P_SCS_AIRCR  (*(volatile uint32_t*) 0xE000ED0CUL)
#define SYSTEM_RESET_REQUEST_VALUE (0x05FA0004UL)

/** Holds the SlowClk system core clock, which is the system clock frequency supplied to the SysTick timer and the
* processor core clock. This variable can be used by debuggers to query the frequency of the debug timer or to configure
* the trace clock speed.
*
* \attention Compilers must be configured to avoid removing this variable in case the application program is not using
* it. Debugging systems require the variable to be physically present in memory so that it can be examined to configure
* the debugger. */
uint32_t SystemCoreClock  = 0UL;

uint32_t cy_delayFreqHz   = 0UL;

uint32_t cy_delayFreqKhz  = 0UL;

uint32_t cy_delayFreqMhz  = 0UL;

uint32_t cy_delay32kMs    = 0UL;

static bool needDeepSleep = false;

static void SysLib_DelayUs(uint16_t microseconds);
static void SysLib_DelayCycles(uint32_t cycles);

#if ((CY_USE_PSVP == 0u) && (CY_SYS_VCCD_SOURCE == CY_SYS_VCCD_PMIC))
#define TIMING_MONZA_PMIC_ENABLE            (4)  // 0: Enable fastest timing, 8:Enable latest timing
#define WAIT_CYCLE_WHILE_DISTRIBUTING_CLOCK (50)
#endif

/*******************************************************************************
* Function Name: DeepSleepEntryandExit
****************************************************************************//**
*
* Transition to Deep Sleep power mode
*
*******************************************************************************/
static void DeepSleepEntryandExit (void)
{
    cy_en_srom_driver_status_t retVal;
    un_srom_api_args_t loadRegulatorTrimArg = {0ul};

    /* 2. Call LoadRegulatorTrims */
    loadRegulatorTrimArg.LoadRegulatorTrim.arg0.trim    = CY_SROM_LoadRegulatorTrim_LDO;
    loadRegulatorTrimArg.LoadRegulatorTrim.arg0.usecase = CY_SROM_LoadRegulatorTrim_DPSLP_Entry;
    loadRegulatorTrimArg.LoadRegulatorTrim.arg0.opcode  = CY_SROM_OP_LoadRegulatorTrim;

    retVal = Cy_Srom_CallApi(&loadRegulatorTrimArg, NULL);

    /* 3. Wait for API Completion, check status code */
    if (CY_SROM_DR_SUCCEEDED != retVal)
    {
        /* API returns Error, put system in an infinite loop, waiting for Watchdog Reset */
        // for(;;);
    }
    else
    {
        /* 4. No implementation for Reduce Current Consumption, the condition already met */

        /* 5. Transition to DeepSleep */
        (void)Cy_SysPm_DeepSleep(CY_SYSPM_WAIT_FOR_INTERRUPT);

    }

    /* 7. Trigger System reset when Cy_Srom_CallApi returns Error or Transition to DeepSleep failed */
    CM0P_SCS_AIRCR = SYSTEM_RESET_REQUEST_VALUE;

}

/*******************************************************************************
* Function Name: SystemInit
****************************************************************************//**
*
* Initializes the system
*
*******************************************************************************/
void SystemInit (void)
{
    uint8_t retryCounter;    /* Counter for retry attempt before transition to DeepSleep */
    uint32_t timeoutus;    /* TIMEOUT variable in micro-second */
    cy_en_srom_driver_status_t retVal;    /* Return value of SROM driver API */

#if defined(CY_SYSTEM_WDT_DISABLE)
    /* disable WDT */
    Cy_WDT_Disable();
#endif /* CY_SYSTEM_WDT_DISABLE */
    
#if (CY_USE_PSVP == 0u)

#if (CY_SYS_VCCD_SOURCE == CY_SYS_VCCD_PASS_TR)

    /***    Set clock LF source        ***/
    SRSS->unCLK_SELECT.stcField.u3LFCLK_SEL = CY_SYSCLK_LFCLK_IN_ILO0;

    /* Power Mode Setting */
    needDeepSleep = false;    /* Reset Deep sleep request */
    retryCounter = 0u;    /* Reset retry counter */
    do
    {
        retVal = Cy_Power_SwitchToTransistor(CY_SYSREGHC_VADJ_1V150);

        /* Retry handling */
        if (CY_SROM_DR_SUCCEEDED != retVal)
        {
            needDeepSleep = true;
            /* API returns Error, attempt a retry */
            retryCounter++;
        }
        else
        {
            needDeepSleep = false;
            /* API returns Success, no more retry */
            break;
        }

    } while (retryCounter < MAX_RETRY_BEFORE_DEEP_SLEEP);

    /* If the error is not resolved after 3 retries, transition to DeepSleep */
    if (true == needDeepSleep)
    {
        DeepSleepEntryandExit();
    }
    else
    {
        /* do nothing */
    }

#endif

    /*********** Setting wait state for ROM **********/
    CPUSS->unROM_CTL.stcField.u2SLOW_WS = 1u;
    CPUSS->unROM_CTL.stcField.u2FAST_WS = 0u;

    /*********** Setting wait state for RAM **********/
    CPUSS->unRAM0_CTL0.stcField.u2SLOW_WS = 1u;
    CPUSS->unRAM0_CTL0.stcField.u2FAST_WS = 0u;

    #if defined (CPUSS_RAMC1_PRESENT) && (CPUSS_RAMC1_PRESENT == 1UL)
    CPUSS->unRAM1_CTL0.stcField.u2SLOW_WS = 1u;
    CPUSS->unRAM1_CTL0.stcField.u2FAST_WS = 0u;
    #endif /* defined (CPUSS_RAMC1_PRESENT) && (CPUSS_RAMC1_PRESENT == 1UL) */

    #if defined (CPUSS_RAMC2_PRESENT) && (CPUSS_RAMC2_PRESENT == 1UL)
    CPUSS->unRAM2_CTL0.stcField.u2SLOW_WS = 1u;
    CPUSS->unRAM2_CTL0.stcField.u2FAST_WS = 0u;
    #endif /* defined (CPUSS_RAMC2_PRESENT) && (CPUSS_RAMC2_PRESENT == 1UL) */

    /*********** Setting wait state for FLASH **********/
    FLASHC->unFLASH_CTL.stcField.u4WS = 1u;

    /***    Set clock LF source        ***/
    SRSS->unCLK_SELECT.stcField.u3LFCLK_SEL = CY_SYSCLK_LFCLK_IN_ILO0;

#if CY_SYSTEM_USE_CLOCK == CY_SYSTEM_USE_ECO
    needDeepSleep = false;    /* Reset Deep sleep request */
    retryCounter = 0u;    /* Reset retry counter */
    /***    ECO port settings        ***/
    /* Default settings should be OK. */
    
    /* 1. Configure Trim and Configure TIMEOUT Value */
    /***    ECO setting and enabling        ***/
    // These values need to be confirmed
    SRSS->unCLK_ECO_CONFIG2.stcField.u3WDTRIM = 7u; // NS
    SRSS->unCLK_ECO_CONFIG2.stcField.u4ATRIM  = 14u; // NS
    SRSS->unCLK_ECO_CONFIG2.stcField.u2FTRIM  = 3u;
    SRSS->unCLK_ECO_CONFIG2.stcField.u2RTRIM  = 3u;
    SRSS->unCLK_ECO_CONFIG2.stcField.u3GTRIM  = 1u;
    SRSS->unCLK_ECO_CONFIG.stcField.u1AGC_EN = 0ul; // NS
    
    /* 2. Check if ECO_OK is already 1 */
    if (1ul == SRSS->unCLK_ECO_STATUS.stcField.u1ECO_OK)
    {
        /* ECO_OK is already enabled, end sequence with No Change */
    }
    else
    {
        do
        {
            timeoutus = TIMEOUT_ECO_SETTING; /* Configure TIMEOUT Value */

            /* 3. Write "1" to ECO_EN */
            SRSS->unCLK_ECO_CONFIG.stcField.u1ECO_EN = 1ul;

            /* 4. Check the state of ECO_OK and the state of TIMEOUT */
            /* 5. Subtract TIMEOUT value. */
            /* 6. Check if TIMEMOUT = 0 */
            for (; (0ul == SRSS->unCLK_ECO_STATUS.stcField.u1ECO_OK) && (0ul != timeoutus); timeoutus--)
            {
                /* Wait for 1 us */
                SysLib_DelayUs(1u);
            }

            /* Timeout handling */
            if (0ul == timeoutus)
            {
                needDeepSleep = true;
                /* Process ends with Timeout, attempt a retry */
                retryCounter++;
            }
            else
            {
                needDeepSleep = false;
                /* Process ends with Success, no more retry */
                break;
            }
        } while (retryCounter < MAX_RETRY_BEFORE_DEEP_SLEEP);
    }

    /* If the error is not resolved after 3 retries, transition to Deep Sleep */
    if (true == needDeepSleep)
    {
        DeepSleepEntryandExit();
    }
    else
    {
        /* do nothing */
    }

    while(SRSS->unCLK_ECO_STATUS.stcField.u1ECO_READY == 0ul);
#endif

#if defined(CY_SYSTEM_WCO_ENABLE)

    // Enable WCO
    BACKUP->unCTL.stcField.u1WCO_EN = 1ul;

#if 0 /* NS modified: stability waiting process move to M7. */
    // Wait until WCO status becomes OK
    while(BACKUP->unSTATUS.stcField.u1WCO_OK == 0ul);
#endif

#endif

    /***  Set CPUSS dividers as required        ***/
    /* CLK_MEM */
    CPUSS->unMEM_CLOCK_CTL.stcField.u8INT_DIV     = 0u; /* no division */

    /* CLK_SLOW */
    CPUSS->unSLOW_CLOCK_CTL.stcField.u8INT_DIV    = 1u; /* divided by 2 */

    /* CLK_PERI */
    CPUSS->unPERI_CLOCK_CTL.stcField.u8INT_DIV    = 1u; /* divided by 2 */

    /* CLK_TRC_DBG */
    CPUSS->unTRC_DBG_CLOCK_CTL.stcField.u8INT_DIV = 0u; /* divided by 1 */

    // No setting for CLK_GRx requred. Initial values (no division) should be ok.

    /***     PLL setting and enabling        ***/
    /* Settings for PLL400M #0 (CLK_PATH1) */
    needDeepSleep = false;    /* Reset Deep sleep request */
    retryCounter = 0u;    /* Reset retry counter */
    do
    {
        timeoutus = TIMEOUT_CLK_PATH1_SETTING;    /* Reset TIMEOUT */

        /* 1. Check bit enable of PLL400M0 clock */
        if (0ul != SRSS->CLK_PLL400M[0].unCONFIG.stcField.u1ENABLE)
        {
            /* PLL400M0 is already enabled, end sequence with No Change */
        }
        else
        {
            /* 2. PLL400M0 configuration */
            /* 3. No implimentation for Fractional Divider Settings, always disable */
            /* 4. No implimentation for SSCG Settings, always disable */
            SRSS->unCLK_PATH_SELECT[1/*PLL400M #0*/].stcField.u3PATH_MUX = CY_SYSTEM_PLL_INPUT_SOURCE;

            SRSS->CLK_PLL400M[0].unCONFIG2.stcField.u1FRAC_EN      = 0ul;     /* Disabled */

            SRSS->CLK_PLL400M[0].unCONFIG3.stcField.u10SSCG_DEPTH  = 0ul;     /* Reserved */
            SRSS->CLK_PLL400M[0].unCONFIG3.stcField.u3SSCG_RATE    = 0ul;     /* Modulation rate = fPFD/4096 */
            SRSS->CLK_PLL400M[0].unCONFIG3.stcField.u1SSCG_DITHER_EN = 0ul;   /* Reserved. Setting is not used internally */
            SRSS->CLK_PLL400M[0].unCONFIG3.stcField.u1SSCG_MODE    = 0ul;     /* Write "0" always */
            SRSS->CLK_PLL400M[0].unCONFIG3.stcField.u1SSCG_EN      = 0ul;     /* Disabled spreading mode */

            SRSS->CLK_PLL400M[0].unCONFIG.stcField.u5REFERENCE_DIV = CY_SYSTEM_PLL0_CONFIG_REFDIV; 
            SRSS->CLK_PLL400M[0].unCONFIG.stcField.u8FEEDBACK_DIV  = CY_SYSTEM_PLL0_CONFIG_FEEDBACKDIV; 
            SRSS->CLK_PLL400M[0].unCONFIG.stcField.u5OUTPUT_DIV    = CY_SYSTEM_PLL0_CONFIG_OUTDIV; 
            SRSS->CLK_PLL400M[0].unCONFIG.stcField.u2LOCK_DELAY    = 0ul;     /* Integer divider without spreading */
            SRSS->CLK_PLL400M[0].unCONFIG.stcField.u2BYPASS_SEL    = 0ul;     /* Auto */

            /* 5. Enable PLL400M0 clock */
            SRSS->CLK_PLL400M[0].unCONFIG.stcField.u1ENABLE        = 1ul;

            /* 6. Waiting for PLL400M0 locked */
            /* 7. Checking TIMEOUT value */
            for (; (0ul == SRSS->CLK_PLL400M[0].unSTATUS.stcField.u1LOCKED)  && (0ul != timeoutus); timeoutus--)
            {
                /* Wait for 1 us */
                SysLib_DelayUs(1u);
            }
        }

        /* Timeout handling */
        if (0ul == timeoutus)
        {
            needDeepSleep = true;
            /* Process ends with Timeout, attempt a retry */
            retryCounter++;
        }
        else
        {
            needDeepSleep = false;
            /* Process ends with Success, no more retry */
            break;
        }

    } while (retryCounter < MAX_RETRY_BEFORE_DEEP_SLEEP);

    /* If the error is not resolved after 3 retries, transition to Deep Sleep */
    if (true == needDeepSleep)
    {
        DeepSleepEntryandExit();
    }
    else
    {
        /* do nothing */
    }


    /* Settings for PLL400M #1 (CLK_PATH2) */
    needDeepSleep = false;    /* Reset Deep sleep request */
    retryCounter = 0u;   /* Reset retry counter */
    do
    {
        timeoutus = TIMEOUT_CLK_PATH2_SETTING;    /* Reset TIMEOUT */

        /* 1. Check bit enable of PLL400M1 clock */
        if (0ul != SRSS->CLK_PLL400M[1].unCONFIG.stcField.u1ENABLE)
        {
            /* PLL400M1 is already enabled, end sequence with No Change */
        }
        else
        {
            /* 2. PLL400M1 configuration */
            /* 3. No implimentation for Fractional Divider Settings, always disable */
            /* 4. No implimentation for SSCG Settings, always disable */
            SRSS->unCLK_PATH_SELECT[2/*PLL400M #1*/].stcField.u3PATH_MUX = CY_SYSTEM_PLL_INPUT_SOURCE;

            SRSS->CLK_PLL400M[1].unCONFIG2.stcField.u24FRAC_DIV    = CY_SYSTEM_PLL1_CONFIG_FB_FRAC;
            SRSS->CLK_PLL400M[1].unCONFIG2.stcField.u3FRAC_DITHER_EN  = 1ul; /* Enabled */
            SRSS->CLK_PLL400M[1].unCONFIG2.stcField.u1FRAC_EN      = 1ul;    /* Enabled */

            SRSS->CLK_PLL400M[1].unCONFIG3.stcField.u1SSCG_EN      = 0ul;    /* Disabled */

            SRSS->CLK_PLL400M[1].unCONFIG.stcField.u5REFERENCE_DIV = CY_SYSTEM_PLL1_CONFIG_REFDIV; 
            SRSS->CLK_PLL400M[1].unCONFIG.stcField.u8FEEDBACK_DIV  = CY_SYSTEM_PLL1_CONFIG_FB_INT; 
            SRSS->CLK_PLL400M[1].unCONFIG.stcField.u5OUTPUT_DIV    = CY_SYSTEM_PLL1_CONFIG_OUTDIV; 
            SRSS->CLK_PLL400M[1].unCONFIG.stcField.u2LOCK_DELAY    = 1ul;    /* Fractional division or spreading */
            SRSS->CLK_PLL400M[1].unCONFIG.stcField.u2BYPASS_SEL    = 0ul;    /* Auto */

            /* 5. Enable PLL400M1 clock */
            SRSS->CLK_PLL400M[1].unCONFIG.stcField.u1ENABLE        = 1ul;

            /* 6. Waiting for PLL400M1 locked */
            /* 7. Checking TIMEOUT value */
            for (; (0ul == SRSS->CLK_PLL400M[1].unSTATUS.stcField.u1LOCKED)  && (0ul != timeoutus); timeoutus--)
            {
                /* Wait for 1 us */
                SysLib_DelayUs(1u);
            }
        }

        /* Timeout handling */
        if (0ul == timeoutus)
        {
            needDeepSleep= true;
            /* Process ends with Timeout, attempt a retry */
            retryCounter++;
        }
        else
        {
            needDeepSleep = false;
            /* Process ends with Success, no more retry */
            break;
        }

    } while (retryCounter < MAX_RETRY_BEFORE_DEEP_SLEEP);

    /* If the error is not resolved after 3 retries, transition to Deep Sleep */
    if (true == needDeepSleep)
    {
        DeepSleepEntryandExit();
    }
    else
    {
        /* do nothing */
    }


    /* Settings for PLL #0 (CLK_PATH3) */
    needDeepSleep = false;    /* Reset Deep sleep request */
    retryCounter = 0u;    /* Reset retry counter */
    do
    {
        timeoutus = TIMEOUT_CLK_PATH3_SETTING;    /* Reset TIMEOUT */

        /* 8. Check bit enable of PLL200M0 clock */
        if (0ul != SRSS->unCLK_PLL_CONFIG[0].stcField.u1ENABLE)
        {
            /* PLL200M0 is already enabled, end sequence with No Change */
        }
        else
        {
            /* 9. PLL200M0 configuration */
            SRSS->unCLK_PATH_SELECT[3/*PLL #0*/].stcField.u3PATH_MUX = CY_SYSTEM_PLL_INPUT_SOURCE;

            SRSS->unCLK_PLL_CONFIG[0].stcField.u7FEEDBACK_DIV      = CY_SYSTEM_PLL2_CONFIG_FEEDBACKDIV;
            SRSS->unCLK_PLL_CONFIG[0].stcField.u5REFERENCE_DIV     = CY_SYSTEM_PLL2_CONFIG_REFDIV;
            SRSS->unCLK_PLL_CONFIG[0].stcField.u5OUTPUT_DIV        = CY_SYSTEM_PLL2_CONFIG_OUTDIV;
            SRSS->unCLK_PLL_CONFIG[0].stcField.u2LOCK_DELAY        = 0ul;    /* Normal operation */
            SRSS->unCLK_PLL_CONFIG[0].stcField.u1PLL_LF_MODE       = 0ul;    /* VCO frequency is [200MHz, 400MHz] Fvco = 400,000,000[Hz] */
            SRSS->unCLK_PLL_CONFIG[0].stcField.u2BYPASS_SEL        = 0ul;    /* Auto */

            /* 10. Enable PLL200M0 clock */
            SRSS->unCLK_PLL_CONFIG[0].stcField.u1ENABLE            = 1ul;

            /* 11. Waiting for PLL200M0 locked */
            /* 12. Checking TIMEOUT value */
            for (; (0ul == SRSS->unCLK_PLL_STATUS[0].stcField.u1LOCKED)  && (0ul != timeoutus); timeoutus--)
            {
                /* Wait for 1 us. */
                SysLib_DelayUs(1u);
            }
        }

        /* Timeout handling */
        if (0ul == timeoutus)
        {
            needDeepSleep = true;
            /* Process ends with Timeout, attempt a retry */
            retryCounter++;
        }
        else
        {
            needDeepSleep = false;
            /* Process ends with Success, no more retry */
            break;
        }

    } while (retryCounter < MAX_RETRY_BEFORE_DEEP_SLEEP);

    /* If the error is not resolved after 3 retries, transition to Deep Sleep */
    if (true == needDeepSleep)
    {
        DeepSleepEntryandExit();
    }
    else
    {
        /* do nothing */
    }


    /* Settings for PLL #1 (CLK_PATH4) */
    needDeepSleep = false;    /* Reset Deep sleep request */
    retryCounter = 0u;    /* Reset retry counter */

    do
    {
        timeoutus = TIMEOUT_CLK_PATH4_SETTING;    /* Reset TIMEOUT */

        /* 8. Check bit enable of PLL200M1 clock */
        if (0ul != SRSS->unCLK_PLL_CONFIG[1].stcField.u1ENABLE)
        {
            /* PLL200M1 is already enabled, end sequence with No Change */
        }
        else
        {
            /* 9. PLL200M1 configuration */
            SRSS->unCLK_PATH_SELECT[4/*PLL #1*/].stcField.u3PATH_MUX = CY_SYSTEM_PLL_INPUT_SOURCE;

            SRSS->unCLK_PLL_CONFIG[1].stcField.u7FEEDBACK_DIV      = CY_SYSTEM_PLL3_CONFIG_FEEDBACKDIV;
            SRSS->unCLK_PLL_CONFIG[1].stcField.u5REFERENCE_DIV     = CY_SYSTEM_PLL3_CONFIG_REFDIV;
            SRSS->unCLK_PLL_CONFIG[1].stcField.u5OUTPUT_DIV        = CY_SYSTEM_PLL3_CONFIG_OUTDIV;
            SRSS->unCLK_PLL_CONFIG[1].stcField.u2LOCK_DELAY        = 0ul;    /* Normal operation */
            SRSS->unCLK_PLL_CONFIG[1].stcField.u1PLL_LF_MODE       = 0ul;    /* VCO frequency is [200MHz, 400MHz] Fvco = 240,000,000[Hz] */
            SRSS->unCLK_PLL_CONFIG[1].stcField.u2BYPASS_SEL        = 0ul;    /* Auto */

            /* 10. Enable PLL200M1 clock */
            SRSS->unCLK_PLL_CONFIG[1].stcField.u1ENABLE            = 1ul;

            /* 11. Waiting for PLL200M1 locked */
            /* 12. Checking TIMEOUT value */
            for (; (0ul == SRSS->unCLK_PLL_STATUS[1].stcField.u1LOCKED)  && (0ul != timeoutus); timeoutus--)
            {
                /* Wait for 1 us. */
                SysLib_DelayUs(1u);
            }
        }

        /* Timeout handling */
        if (0ul == timeoutus)
        {
            needDeepSleep = true;
            /* Process ends with Timeout, attempt a retry */
            retryCounter++;
        }
        else
        {
            needDeepSleep = false;
            /* Process ends with Success, no more retry */
            break;
        }

    } while (retryCounter < MAX_RETRY_BEFORE_DEEP_SLEEP);

    /* If the error is not resolved after 3 retries, transition to Deep Sleep */
    if (true == needDeepSleep)
    {
        DeepSleepEntryandExit();
    }
    else
    {
        /* do nothing */
    }


    /***   Setting  PATH5  source        ***/
    SRSS->unCLK_PATH_SELECT[5].stcField.u3PATH_MUX = CY_SYSCLK_CLKPATH_IN_IMO;

    /***  Setting for each clk_hf        ***/
    struct {cy_en_hf_clk_dividers_t targetDiv; cy_en_hf_clk_sources_t source;} clkHfSetting[SRSS_NUM_HFROOT] = 
    {
        { .targetDiv = CY_SYSCLK_HFCLK_NO_DIVIDE,   .source = CY_SYSCLK_HFCLK_IN_CLKPATH3 /* PLL2: PLL200#0 */ }, // setting for clk_hf0
        { .targetDiv = CY_SYSCLK_HFCLK_NO_DIVIDE,   .source = CY_SYSCLK_HFCLK_IN_CLKPATH1 /* PLL0: PLL400#0 */ }, // setting for clk_hf1
        { .targetDiv = CY_SYSCLK_HFCLK_NO_DIVIDE,   .source = CY_SYSCLK_HFCLK_IN_CLKPATH4 /* PLL3: PLL200#1 */ }, // setting for clk_hf2
        { .targetDiv = CY_SYSCLK_HFCLK_DIVIDE_BY_2, .source = CY_SYSCLK_HFCLK_IN_CLKPATH3 /* PLL2: PLL200#0 */ }, // setting for clk_hf3
        { .targetDiv = CY_SYSCLK_HFCLK_DIVIDE_BY_4, .source = CY_SYSCLK_HFCLK_IN_CLKPATH2 /* PLL1: PLL400#1 */ }, // setting for clk_hf4
        { .targetDiv = CY_SYSCLK_HFCLK_NO_DIVIDE,   .source = CY_SYSCLK_HFCLK_IN_CLKPATH2 /* PLL1: PLL400#1 */ }, // setting for clk_hf5
        { .targetDiv = CY_SYSCLK_HFCLK_NO_DIVIDE,   .source = CY_SYSCLK_HFCLK_IN_CLKPATH3 /* PLL2: PLL200#0 */ }, // setting for clk_hf6
        { .targetDiv = CY_SYSCLK_HFCLK_NO_DIVIDE,   .source = CY_SYSCLK_HFCLK_IN_CLKPATH5 /* No PLL/FLL */     }, // setting for clk_hf7
    };

#if (CY_SYS_VCCD_SOURCE == CY_SYS_VCCD_PMIC)
    // Restriction 1. Enabling MONZA PMIC when the current comsumption is from 20 [mA] to 300 [mA]
    //                Please adjust "TIMING_MONZA_PMIC_ENABLE" defined above.
    // Restriction 2. The current rising time has to be more than 10 [us]
    //                Please adjust "WAIT_CYCLE_WHILE_DISTRIBUTING_CLOCK" defined above.
    for(int8_t i_clkHfNo = 0ul; i_clkHfNo < SRSS_NUM_HFROOT; i_clkHfNo++)
    {
        if(i_clkHfNo == TIMING_MONZA_PMIC_ENABLE)
        {
            uint32_t primaskBackup = __get_PRIMASK(); /* Save current "IRQ enable" state for later restoration */
            __set_PRIMASK(0);                         /* Ensure that IRQs are enabled because the switch-over to PMIC uses a system call */

            /***   Enabling MONZA PMIC     ***/
            Cy_Power_SwitchToPmic(CY_SYSREGHC_VADJ_1V100, CY_POWER_PMIC_ENABLE_HIGH, CY_POWER_PMIC_STATUS_ABNORMAL_LOW, 1000u);

            __set_PRIMASK(primaskBackup); /* Restore original "IRQ enable" state */
        }
        SRSS->unCLK_ROOT_SELECT[i_clkHfNo].stcField.u4ROOT_MUX   = clkHfSetting[i_clkHfNo].source;
        SRSS->unCLK_ROOT_SELECT[i_clkHfNo].stcField.u2ROOT_DIV   = CY_SYSCLK_HFCLK_DIVIDE_BY_8;
        SRSS->unCLK_ROOT_SELECT[i_clkHfNo].stcField.u1DIRECT_MUX = 1u; /* Select ROOT_MUX */
        SRSS->unCLK_ROOT_SELECT[i_clkHfNo].stcField.u1ENABLE     = 1u; /* 1 = enable */
        /* Gradually decrease the current root clock divider until the target divider is reached */
        for(int8_t i_divRegValue = 2; i_divRegValue >= clkHfSetting[i_clkHfNo].targetDiv; i_divRegValue--)
        {
            Cy_SysTick_DelayCoreCycle(WAIT_CYCLE_WHILE_DISTRIBUTING_CLOCK);
            SRSS->unCLK_ROOT_SELECT[i_clkHfNo].stcField.u2ROOT_DIV = i_divRegValue;
        }
        Cy_SysTick_DelayCoreCycle(WAIT_CYCLE_WHILE_DISTRIBUTING_CLOCK);
    }
#else
    for(int8_t i_clkHfNo = 0ul; i_clkHfNo < SRSS_NUM_HFROOT; i_clkHfNo++)
    {
        SRSS->unCLK_ROOT_SELECT[i_clkHfNo].stcField.u4ROOT_MUX   = clkHfSetting[i_clkHfNo].source;
        SRSS->unCLK_ROOT_SELECT[i_clkHfNo].stcField.u2ROOT_DIV   = clkHfSetting[i_clkHfNo].targetDiv;
        SRSS->unCLK_ROOT_SELECT[i_clkHfNo].stcField.u1DIRECT_MUX = 1u; /* Select ROOT_MUX */
        SRSS->unCLK_ROOT_SELECT[i_clkHfNo].stcField.u1ENABLE     = 1u; /* 1 = enable */
    }
#endif

    /* CLK_FAST_0 */
    CPUSS->unFAST_0_CLOCK_CTL.stcField.u8INT_DIV  = 0u; /* no division */
    CPUSS->unFAST_0_CLOCK_CTL.stcField.u5FRAC_DIV = 0u; /* no division */

    /* CLK_FAST_1 */
    CPUSS->unFAST_1_CLOCK_CTL.stcField.u8INT_DIV  = 0u; /* no division */
    CPUSS->unFAST_1_CLOCK_CTL.stcField.u5FRAC_DIV = 0u; /* no division */

    /***     Enabling ILO0        ***/
    Cy_WDT_Unlock();
    SRSS->unCLK_ILO0_CONFIG.stcField.u1ENABLE = 1;        /* 1 = enable */
    SRSS->unCLK_ILO0_CONFIG.stcField.u1ILO0_BACKUP = 1ul; /* Ilo HibernateOn */
    Cy_WDT_Lock();

#else
    /* Settings for PLL400M #0 (CLK_PATH1) */
    SRSS->CLK_PLL400M[0].unCONFIG.stcField.u1ENABLE = 1ul;      /* For PSVP, PLL#0 should be enabled to switch from 8MHz(IMO) to 24MHz */
    
    /* Configure all CLK_HFx to use the 24 MHz from this PLL */
    for(int8_t i_clkHfNo = 0ul; i_clkHfNo < SRSS_NUM_HFROOT; i_clkHfNo++)
    {
        SRSS->unCLK_ROOT_SELECT[i_clkHfNo].stcField.u4ROOT_MUX   = CY_SYSCLK_HFCLK_IN_CLKPATH1 /* PLL0: PLL400#0 */;
        SRSS->unCLK_ROOT_SELECT[i_clkHfNo].stcField.u2ROOT_DIV   = CY_SYSCLK_HFCLK_NO_DIVIDE;
        SRSS->unCLK_ROOT_SELECT[i_clkHfNo].stcField.u1DIRECT_MUX = 1u;                         /* Select ROOT_MUX */
        SRSS->unCLK_ROOT_SELECT[i_clkHfNo].stcField.u1ENABLE     = 1u;                         /* 1 = enable */
    }
    
#endif  // CY_USE_PSVP == 0u

    SystemCoreClockUpdate();
}

/*******************************************************************************
* Function Name: SystemCoreClockUpdate
****************************************************************************//**
*
* Updates variables with current clock settings
*
*******************************************************************************/
void SystemCoreClockUpdate (void)
{
    cy_stc_base_clk_freq_t freqInfo = 
    {
        .clk_imo_freq  = CY_CLK_IMO_FREQ_HZ,
        .clk_ext_freq  = CY_CLK_EXT_FREQ_HZ,
        .clk_eco_freq  = CY_CLK_ECO_FREQ_HZ,
        .clk_ilo0_freq = CY_CLK_HVILO0_FREQ_HZ,
        .clk_ilo1_freq = CY_CLK_HVILO1_FREQ_HZ,
        .clk_wco_freq  = CY_CLK_WCO_FREQ_HZ,
    };

    cy_en_sysclk_status_t retVal;
    retVal = Cy_SysClk_InitGetFreqParams(&freqInfo);
    CY_ASSERT(retVal == CY_SYSCLK_SUCCESS);
    retVal = Cy_SysClk_GetCoreFrequency(&SystemCoreClock);
    CY_ASSERT(retVal == CY_SYSCLK_SUCCESS);
    (void) retVal; // avoid "unused" compiler warning if NDEBUG is set
	
    cy_delayFreqHz   = SystemCoreClock;
    cy_delayFreqMhz  = ((cy_delayFreqHz + CY_DELAY_1M_MINUS_1_THRESHOLD) / CY_DELAY_1M_THRESHOLD);
    cy_delayFreqKhz  = (cy_delayFreqHz + CY_DELAY_1K_MINUS_1_THRESHOLD) / CY_DELAY_1K_THRESHOLD;
    cy_delay32kMs    = CY_DELAY_MS_OVERFLOW_THRESHOLD * cy_delayFreqKhz;
}

/*******************************************************************************
* Function Name: Cy_SysGetApplCoreStatus
****************************************************************************//**
*
* Gets the Cortex-M4/M7 core power mode.
*
* \return \ref group_system_config_cm_status_macro
*
*******************************************************************************/
uint32_t Cy_SysGetApplCoreStatus(uint8_t core)
{
    uint32_t regValue = 0;
    
    CY_ASSERT(core < CORE_MAX);

    if(core == CORE_CM7_0)
    {
        /* Get current power mode */
        regValue = CPUSS->unCM7_0_PWR_CTL.u32Register;
        regValue = (regValue >> CPUSS_CM7_0_PWR_CTL_PWR_MODE_Pos) & CPUSS_CM7_0_PWR_CTL_PWR_MODE_Msk;
    }
    else if(core == CORE_CM7_1)
    {
        /* Get current power mode */
        regValue = CPUSS->unCM7_1_PWR_CTL.u32Register;
        regValue = (regValue >> CPUSS_CM7_1_PWR_CTL_PWR_MODE_Pos) & CPUSS_CM7_1_PWR_CTL_PWR_MODE_Msk;
    }

    return (regValue);
}

/*******************************************************************************
* Function Name: Cy_SysEnableApplCore
****************************************************************************//**
*
* Enables the Cortex-M4/M7 core. The CPU is enabled once if it was in the disabled
* or retained mode. 
*
* \param vectorTableOffset The offset of the vector table base address from
* memory address 0x00000000. The offset should be multiple to 1024 bytes.
*
*******************************************************************************/
void Cy_SysEnableApplCore(uint8_t core, uint32_t vectorTableOffset)
{
    uint32_t cmStatus;
    uint32_t interruptState;
    un_CPUSS_CM7_0_PWR_CTL_t tPwrCtl0;
    un_CPUSS_CM7_1_PWR_CTL_t tPwrCtl1; 
    
    CY_ASSERT(core < CORE_MAX);

    interruptState = Cy_SaveIRQ();
    
    cmStatus = Cy_SysGetApplCoreStatus(core);
    if(cmStatus == CY_SYS_CM_STATUS_ENABLED)
    {
        // Set core into reset first, so that new settings can get effective
        // This branch is e.g. entered if a debugger is connected that would power-up the CM7,
        // but let it run in ROM boot or pause its execution by keeping CPU_WAIT bit set.
        Cy_SysResetApplCore(core);
    }
    
    // CLK_HF1, by default is disabled for use by CM7_0/1, hence enable
    SRSS->unCLK_ROOT_SELECT[1].stcField.u1ENABLE = 1;
        
    if(core == CORE_CM7_0)
    {           
        // Adjust the vector address
        CPUSS->unCM7_0_VECTOR_TABLE_BASE.u32Register = vectorTableOffset;
        
        // Enable the Power Control Key
        tPwrCtl0.stcField.u16VECTKEYSTAT = CY_SYS_PWR_CTL_KEY_OPEN;
        tPwrCtl0.stcField.u2PWR_MODE = CY_SYS_CM_STATUS_ENABLED;
        CPUSS->unCM7_0_PWR_CTL.u32Register = tPwrCtl0.u32Register;
        
        CPUSS->unCM7_0_CTL.stcField.u1CPU_WAIT = 0;
    } 
    else if(core == CORE_CM7_1)
    {            
        // Adjust the vector address
        CPUSS->unCM7_1_VECTOR_TABLE_BASE.u32Register = vectorTableOffset;
        
        // Enable the Power Control Key
        tPwrCtl1.stcField.u16VECTKEYSTAT = CY_SYS_PWR_CTL_KEY_OPEN;
        tPwrCtl1.stcField.u2PWR_MODE = CY_SYS_CM_STATUS_ENABLED;
        CPUSS->unCM7_1_PWR_CTL.u32Register = tPwrCtl1.u32Register;
        
        CPUSS->unCM7_1_CTL.stcField.u1CPU_WAIT = 0;
    }
    
    Cy_RestoreIRQ(interruptState);
}


/*******************************************************************************
* Function Name: Cy_SysDisableApplCore
****************************************************************************//**
*
* Disables the Cortex-M4/M7 core.
*
* \warning Do not call the function while the Cortex-M4 is executing because
* such a call may corrupt/abort a pending bus-transaction by the CPU and cause
* unexpected behavior in the system including a deadlock. Call the function
* while the Cortex-M4 core is in the Sleep or Deep Sleep low-power mode. Use
* the \ref group_syspm Power Management (syspm) API to put the CPU into the
* low-power modes. Use the \ref Cy_SysPm_ReadStatus() to get a status of the
* CPU.
*
*******************************************************************************/
void Cy_SysDisableApplCore(uint8_t core)
{
    un_CPUSS_CM7_0_PWR_CTL_t tPwrCtl0;
    un_CPUSS_CM7_1_PWR_CTL_t tPwrCtl1; 

    CY_ASSERT(core < CORE_MAX);

    if(core == CORE_CM7_0)
    {
        tPwrCtl0.stcField.u16VECTKEYSTAT = CY_SYS_PWR_CTL_KEY_OPEN;
        tPwrCtl0.stcField.u2PWR_MODE = CY_SYS_CM_STATUS_OFF;
        CPUSS->unCM7_0_PWR_CTL.u32Register = tPwrCtl0.u32Register; 
    }
    else if(core == CORE_CM7_1)
    {
        tPwrCtl1.stcField.u16VECTKEYSTAT = CY_SYS_PWR_CTL_KEY_OPEN;
        tPwrCtl1.stcField.u2PWR_MODE = CY_SYS_CM_STATUS_OFF;
        CPUSS->unCM7_1_PWR_CTL.u32Register = tPwrCtl1.u32Register; 
    }
}


/*******************************************************************************
* Function Name: Cy_SysRetainApplCore
****************************************************************************//**
*
* Retains the Cortex-M4/M7 core.
*
* \warning Do not call the function while the Cortex-M4 is executing because
* such a call may corrupt/abort a pending bus-transaction by the CPU and cause
* unexpected behavior in the system including a deadlock. Call the function
* while the Cortex-M4 core is in the Sleep or Deep Sleep low-power mode. Use
* the \ref group_syspm Power Management (syspm) API to put the CPU into the
* low-power modes. Use the \ref Cy_SysPm_ReadStatus() to get a status of the CPU.
*
*******************************************************************************/
void Cy_SysRetainApplCore(uint8_t core)
{
    uint32_t cmStatus;
    uint32_t  interruptState;
    un_CPUSS_CM7_0_PWR_CTL_t tPwrCtl0;
    un_CPUSS_CM7_1_PWR_CTL_t tPwrCtl1; 

    interruptState = Cy_SaveIRQ();
    
    cmStatus = Cy_SysGetApplCoreStatus(core);
    if(cmStatus == CY_SYS_CM_STATUS_ENABLED)
    {
        if(core == CORE_CM7_0)
        {
            tPwrCtl0.stcField.u16VECTKEYSTAT = CY_SYS_PWR_CTL_KEY_OPEN;
            tPwrCtl0.stcField.u2PWR_MODE = CY_SYS_CM_STATUS_RETAINED;
            CPUSS->unCM7_0_PWR_CTL.u32Register = tPwrCtl0.u32Register;
        }
        else if(core == CORE_CM7_1)
        {
            tPwrCtl1.stcField.u16VECTKEYSTAT = CY_SYS_PWR_CTL_KEY_OPEN;
            tPwrCtl1.stcField.u2PWR_MODE = CY_SYS_CM_STATUS_RETAINED;
            CPUSS->unCM7_1_PWR_CTL.u32Register = tPwrCtl1.u32Register;
        }
    }
    
    Cy_RestoreIRQ(interruptState);
}


/*******************************************************************************
* Function Name: Cy_SysResetApplCore
****************************************************************************//**
*
* Resets the Cortex-M4/M7 core.
*
* \warning Do not call the function while the Cortex-M4 is executing because
* such a call may corrupt/abort a pending bus-transaction by the CPU and cause
* unexpected behavior in the system including a deadlock. Call the function
* while the Cortex-M4 core is in the Sleep or Deep Sleep low-power mode. Use
* the \ref group_syspm Power Management (syspm) API to put the CPU into the
* low-power modes. Use the \ref Cy_SysPm_ReadStatus() to get a status of the CPU.
*
*******************************************************************************/
void Cy_SysResetApplCore(uint8_t core)
{
    un_CPUSS_CM7_0_PWR_CTL_t tPwrCtl0;
    un_CPUSS_CM7_1_PWR_CTL_t tPwrCtl1; 
    
    CY_ASSERT(core < CORE_MAX);

    if(core == CORE_CM7_0)
    {
        tPwrCtl0.stcField.u16VECTKEYSTAT = CY_SYS_PWR_CTL_KEY_OPEN;
        tPwrCtl0.stcField.u2PWR_MODE = CY_SYS_CM_STATUS_RESET;
        CPUSS->unCM7_0_PWR_CTL.u32Register = tPwrCtl0.u32Register; 
    }
    else if(core == CORE_CM7_1)
    {
        tPwrCtl1.stcField.u16VECTKEYSTAT = CY_SYS_PWR_CTL_KEY_OPEN;
        tPwrCtl1.stcField.u2PWR_MODE = CY_SYS_CM_STATUS_RESET;
        CPUSS->unCM7_1_PWR_CTL.u32Register = tPwrCtl1.u32Register; 
    }
}

/*******************************************************************************
* Function Name: SysLib_DelayUs
****************************************************************************//**
*
* Delays execution for a specified number of microseconds.
*
* This function calculates the required number of CPU cycles based on the
* system frequency and delays execution accordingly. It internally calls
* SysLib_DelayCycles() to perform the actual delay using a loop.
* 
* \par microseconds
* The number of microseconds to delay.
* author FPT 
* date 2025-10-29 
*******************************************************************************/
static void SysLib_DelayUs(uint16_t microseconds)
{
    uint32_t cyclesPerUs = (CY_INITIAL_TARGET_SLOW_FREQ + CY_DELAY_1M_THRESHOLD - 1UL) / CY_DELAY_1M_THRESHOLD;
    /* SysLib_DelayCycles takes 2 cycles. Therefore, the totalCycles need to be devided by 2 */
    uint32_t totalCycles = (uint32_t)microseconds * cyclesPerUs / 2 ;     
    SysLib_DelayCycles(totalCycles);
}

/*******************************************************************************
* Function Name: SysLib_DelayCycles
****************************************************************************//**
*
* Delays execution for a specified number of CPU cycles.
*
* This function uses a simple loop to introduce a delay. Each iteration
* consumes approximately two instruction cycles.
* 
* \par cycles
* The number of CPU cycles to delay.
* author FPT 
* date 2025-10-29 
*******************************************************************************/

static void SysLib_DelayCycles(uint32_t cycles)
{
    /* Use while loop for the delay, takes 2 instruction cycles to run */
    while(cycles--){ }
}
