/**
 * @file BrsHw.c
 * @brief Public header: BrsHw.h
 * @details Overview: Hardware-specific implementation for the Vector Basic Runtime System (BRS) on Cypress Traveo2 HSM Core platform
 */
/** @cond INTERNAL */
#define _BRSHW_C_
#define BRSHW_SOURCE
/** @endcond */
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
#if (BRSHW_BUGFIX_VERSION != 0x01u)
  #error "Different versions of bugfix in Header and Source used!"
#endif
 
/**********************************************************************************************************************
 *  CONFIGURATION CHECK
 *********************************************************************************************************************/
#if defined (BRS_COMP_GHS)
 
#else
  #error "Unknown compiler specified!"
#endif
 
#if defined (BRS_ENABLE_PORT)                  || \
    defined (BRS_ENABLE_SAFECTXSUPPORT)        || \
    defined (BRS_ENABLE_OS_MULTICORESUPPORT)   || \
    defined (BRS_ENABLE_CAN_SUPPORT)           || \
    defined (BRS_ENABLE_LIN_SUPPORT)           || \
    defined (BRS_ENABLE_FLEXRAY_SUPPORT)       || \
    defined (BRS_ENABLE_ETHERNET_SUPPORT)      || \
    defined (BRS_ENABLE_I2C_SUPPORT)           || \
    defined (BRS_ENABLE_HYPERBUS_SUPPORT)      || \
    defined (BRS_ENABLE_SPI_SUPPORT)           || \
    defined (BRS_ENABLE_SUPPORT_LEDS)          || \
    defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN) || \
    defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
  #error "Configured Feature(s) not supported by this implementation for a dedicated HSM Core UseCase!"
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
 
/**
 * @type uint8
 * @value Extracted from BRSHW_VERSION
 * @resolution -
 * @brief Main version number of the BrsHw module in BCD encoding (e.g., 0x02 for version 2)
 */
uint8 const kBrsHwMainVersion   = (uint8)(BRSHW_VERSION >> 8u);
 
/**
 * @type uint8
 * @value Extracted from BRSHW_VERSION
 * @resolution -
 * @brief Sub version number of the BrsHw module in BCD encoding (e.g., 0x00 for version 0)
 */
uint8 const kBrsHwSubVersion    = (uint8)(BRSHW_VERSION & 0xFFu);
 
/**
 * @type uint8
 * @value BRSHW_BUGFIX_VERSION
 * @resolution -
 * @brief Bugfix version number of the BrsHw module in BCD encoding (e.g., 0x01 for version 1)
 */
uint8 const kBrsHwBugfixVersion = (uint8)(BRSHW_BUGFIX_VERSION);
 
/**********************************************************************************************************************
 *  LOCAL VARIABLES AND LOCAL HW REGISTERS
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  CONTROLLER CONFIGURATION REGISTERS
 *********************************************************************************************************************/
 
/**
 * @def BRSHW_CM4_SCS_AIRCR
 * @value BRSHW_IOS(uint32, 0xE000ED0Cu)
 * @resolution -
 * @brief Reset control register address for the Cortex-M4 core, used to initiate software resets
 */
#define BRSHW_CM4_SCS_AIRCR          BRSHW_IOS(uint32, 0xE000ED0Cu) /* Reset control registers for Cortex-M4 */
 
/**
 * @def BRSHW_RESET_CAUSE
 * @value BRSHW_IOS(uint32, 0x40261800u)
 * @resolution -
 * @brief Register address for observing the cause of system reset events
 */
#define BRSHW_RESET_CAUSE            BRSHW_IOS(uint32, 0x40261800u) /* Reset cause observation register */
 
/**
 * @def BRSHW_RESET_CAUSE2
 * @value BRSHW_IOS(uint32, 0x40261804u)
 * @resolution -
 * @brief Secondary register address for additional reset cause information
 */
#define BRSHW_RESET_CAUSE2           BRSHW_IOS(uint32, 0x40261804u) /* Reset cause observation register 2 */
 
/**
 * @def BRSHW_RESET_CAUSE_COPY
 * @value BRSHW_IOS(uint32, 0x28013FF0u)
 * @resolution -
 * @brief Memory address for storing a backup copy of the reset cause register for later analysis
 */
#define BRSHW_RESET_CAUSE_COPY       BRSHW_IOS(uint32, 0x28013FF0u) /* Reset cause copy address */
 
/**
 * @def BRSHW_RESET_CAUSE2_COPY
 * @value BRSHW_IOS(uint32, 0x28013FF4u)
 * @resolution -
 * @brief Memory address for storing a backup copy of the reset cause 2 register for later analysis
 */
#define BRSHW_RESET_CAUSE2_COPY      BRSHW_IOS(uint32, 0x28013FF4u) /* Reset cause 2 copy address */
 
/**
 * @def BRSHW_SWRESET_TRIGGERT_MASK
 * @value 0x00000010u
 * @resolution -
 * @brief Bit mask used to identify software-triggered reset events in the reset cause registers
 */
#define BRSHW_SWRESET_TRIGGERT_MASK  (0x00000010u)
 
#if defined (BRS_ENABLE_WATCHDOG)
  /*******************************************************************************
    Watchdog registers
  ********************************************************************************/
 
  /**
   * @def BRS_WDT_CTL
   * @value BRSHW_IOS(uint32, 0x4026C000u)
   * @resolution -
   * @brief Watchdog timer control register address for configuring watchdog behavior
   */
  #define BRS_WDT_CTL   BRSHW_IOS(uint32, 0x4026C000u)  /* Watchdog counter control register */
 
  /**
   * @def BRS_WDT_LOCK
   * @value BRSHW_IOS(uint32, 0x4026C040u)
   * @resolution -
   * @brief Watchdog lock register address for protecting watchdog configuration from unwanted modifications
   */
  #define BRS_WDT_LOCK   BRSHW_IOS(uint32, 0x4026C040u) /* Watchdog LOCK*/
#endif /*BRS_ENABLE_WATCHDOG*/
 
#if defined (BRS_ENABLE_PLLCLOCKS)
  /*******************************************************************************
    PLL & Clocking registers
  ********************************************************************************/
# if defined (BRS_PLL_GROUP_A) /* Body Entry */
 
  /**
   * @def BRSHW_FLASHC_FLASH_CTL
   * @value BRSHW_IOS(uint32, 0x40240000u)
   * @resolution -
   * @brief Register address for configuring flash memory wait states based on system clock frequency
   */
  #define BRSHW_FLASHC_FLASH_CTL      BRSHW_IOS(uint32, 0x40240000u) /* a register to set-up the Wait States for Flash */
 
  /**
   * @def BRSHW_CPUSS_RAM0_CTL
   * @value BRSHW_IOS(uint32, 0x40201300u)
   * @resolution -
   * @brief Register address for configuring RAM0 memory wait states based on system clock frequency
   */
  #define BRSHW_CPUSS_RAM0_CTL        BRSHW_IOS(uint32, 0x40201300u) /* a register to set-up the Wait States for RAM0 */
 
  /**
   * @def BRSHW_CPUSS_RAM1_CTL
   * @value BRSHW_IOS(uint32, 0x40201380u)
   * @resolution -
   * @brief Register address for configuring RAM1 memory wait states based on system clock frequency
   */
  #define BRSHW_CPUSS_RAM1_CTL        BRSHW_IOS(uint32, 0x40201380u) /* a register to set-up the Wait States for RAM1 */
 
  /**
   * @def BRSHW_CPUSS_ROM_CTL
   * @value BRSHW_IOS(uint32, 0x402013C4u)
   * @resolution -
   * @brief Register address for configuring ROM memory wait states based on system clock frequency
   */
  #define BRSHW_CPUSS_ROM_CTL         BRSHW_IOS(uint32, 0x402013C4u) /* a register to set-up the Wait States for ROM */
 
  /**
   * @def BRSHW_CLK_TRIM_ECO_CTL
   * @value BRSHW_IOS(uint32, 0x4026301Cu)
   * @resolution -
   * @brief External crystal oscillator trim control register for fine-tuning oscillator performance
   */
  #define BRSHW_CLK_TRIM_ECO_CTL      BRSHW_IOS(uint32, 0x4026301Cu)
 
  /**
   * @def BRSHW_CLK_TRIM_ECO_CTL2
   * @value BRSHW_IOS(uint32, 0x40263020u)
   * @resolution -
   * @brief Secondary external crystal oscillator trim control register for additional configuration
   */
  #define BRSHW_CLK_TRIM_ECO_CTL2     BRSHW_IOS(uint32, 0x40263020u)
 
  /**
   * @def BRSHW_CLK_DSI_SELECT
   * @value BRSHW_IOS(uint32, 0x40260100u)
   * @resolution -
   * @brief Clock DSI selection register for configuring clock distribution
   */
  #define BRSHW_CLK_DSI_SELECT        BRSHW_IOS(uint32, 0x40260100u)
 
  /**
   * @def BRSHW_CLK_PATH_SELECT
   * @value BRSHW_IOS(uint32, (0x40261200u+ 0x4 * n))
   * @resolution -
   * @brief Clock path selection register for configuring the source of each clock path (n = 0..2)
   */
  #define BRSHW_CLK_PATH_SELECT(n)    BRSHW_IOS(uint32, (0x40261200u+ 0x4 * n)) /* n = 0..2 , CLK_PATHn , n must be the same as specified by ROOT_MUX in BRSHW_CLK_ROOT_SELECT*/
 
  /**
   * @def BRSHW_CLK_ROOT_SELECT
   * @value BRSHW_IOS(uint32, 0x40261240u)
   * @resolution -
   * @brief Root clock selection register for choosing the main system clock source
   */
  #define BRSHW_CLK_ROOT_SELECT       BRSHW_IOS(uint32, 0x40261240u)
 
  /**
   * @def BRSHW_CLK_TIMER_CTL
   * @value BRSHW_IOS(uint32, 0x40261504u)
   * @resolution -
   * @brief Timer clock control register for configuring timer-related clock settings
   */
  #define BRSHW_CLK_TIMER_CTL         BRSHW_IOS(uint32, 0x40261504u)
 
  /**
   * @def BRSHW_CLK_ECO_CONFIG
   * @value BRSHW_IOS(uint32, 0x4026151Cu)
   * @resolution -
   * @brief External crystal oscillator configuration register for initial setup
   */
  #define BRSHW_CLK_ECO_CONFIG        BRSHW_IOS(uint32, 0x4026151Cu)
 
  /**
   * @def BRSHW_CLK_ECO_STATUS
   * @value BRSHW_IOS(uint32, 0x40261524u)
   * @resolution -
   * @brief External crystal oscillator status register for monitoring oscillator state
   */
  #define BRSHW_CLK_ECO_STATUS        BRSHW_IOS(uint32, 0x40261524u)
 
  /**
   * @def BRSHW_CLK_PLL_CONFIG
   * @value BRSHW_IOS(uint32, 0x40261600u)
   * @resolution -
   * @brief PLL configuration register for setting frequency multiplication/division factors
   */
  #define BRSHW_CLK_PLL_CONFIG        BRSHW_IOS(uint32, 0x40261600u)
 
  /**
   * @def BRSHW_CLK_PLL_STATUS
   * @value BRSHW_IOS(uint32, 0x40261640u)
   * @resolution -
   * @brief PLL status register for monitoring PLL lock state and operation
   */
  #define BRSHW_CLK_PLL_STATUS        BRSHW_IOS(uint32, 0x40261640u)
 
  /**
   * @def BRSHW_CM0_CLOCK_CTL
   * @value BRSHW_IOS(uint32, 0x40201008u)
   * @resolution -
   * @brief CM0+ processor clock control register for managing the Cortex-M0+ core clock
   */
  #define BRSHW_CM0_CLOCK_CTL         BRSHW_IOS(uint32, 0x40201008u)
# endif /*BRS_PLL_GROUP_A*/
 
# if defined (BRS_PLL_GROUP_B) /* Body High */
 
  /**
   * @def BRSHW_CLK_ECO_CONFIG
   * @value BRSHW_IOS(uint32, 0x4026151CU)
   * @resolution -
   * @brief External crystal oscillator configuration register for Body High variant
   */
  #define BRSHW_CLK_ECO_CONFIG                BRSHW_IOS(uint32, 0x4026151CU)
 
  /**
   * @def BRSHW_CLK_ECO_CONFIG2
   * @value BRSHW_IOS(uint32, 0x40261544U)
   * @resolution -
   * @brief Secondary external crystal oscillator configuration register for Body High variant
   */
  #define BRSHW_CLK_ECO_CONFIG2               BRSHW_IOS(uint32, 0x40261544U)
 
  /**
   * @def BRSHW_CLK_ECO_STATUS
   * @value BRSHW_IOS(uint32, 0x40261524U)
   * @resolution -
   * @brief External crystal oscillator status register for Body High variant
   */
  #define BRSHW_CLK_ECO_STATUS                BRSHW_IOS(uint32, 0x40261524U)
 
  /**
   * @def BRSHW_CLK_TIMER_CTL
   * @value BRSHW_IOS(uint32, 0x40261504U)
   * @resolution -
   * @brief Timer clock control register for Body High variant
   */
  #define BRSHW_CLK_TIMER_CTL                 BRSHW_IOS(uint32, 0x40261504U)
 
  /**
   * @def BRSHW_CLK_DSI_SELECT
   * @value BRSHW_IOS(uint32, (0x40260100U + n * 0x4U))
   * @resolution -
   * @brief DSI multiplexer selection registers for various clock sources in Body High variant
   */
  #define BRSHW_CLK_DSI_SELECT(n)             BRSHW_IOS(uint32, (0x40260100U + (uint32)(n) * 0x4U))
 
  /**
   * @def BRSHW_CLK_PATH_SELECT
   * @value BRSHW_IOS(uint32, (0x40261200U + n * 0x4U))
   * @resolution -
   * @brief Clock path selection registers for Body High variant (n=0 for FLL to n=5 for CLK_PATH5)
   */
  #define BRSHW_CLK_PATH_SELECT(n)            BRSHW_IOS(uint32, (0x40261200U + n * 0x4U))
 
  /**
   * @def BRSHW_CLK_ROOT_SELECT
   * @value BRSHW_IOS(uint32, (0x40261240U + n * 0x4U))
   * @resolution -
   * @brief High-frequency clock selection registers (CLK_HFn) for Body High variant (n = 0-7)
   */
  #define BRSHW_CLK_ROOT_SELECT(n)            BRSHW_IOS(uint32, (0x40261240U + n * 0x4U))
 
  /**
   * @def BRSHW_CLK_PLL_CONFIG0
   * @value BRSHW_IOS(uint32, 0x40261600U)
   * @resolution -
   * @brief PLL0 configuration register for Body High variant
   */
  #define BRSHW_CLK_PLL_CONFIG0               BRSHW_IOS(uint32, 0x40261600U)
 
  /**
   * @def BRSHW_CLK_PLL_STATUS0
   * @value BRSHW_IOS(uint32, 0x40261640U)
   * @resolution -
   * @brief PLL0 status register for Body High variant
   */
  #define BRSHW_CLK_PLL_STATUS0               BRSHW_IOS(uint32, 0x40261640U)
 
  /**
   * @def BRSHW_FLASHC_FLASH_CTL
   * @value BRSHW_IOS(uint32, 0x40240000U)
   * @resolution -
   * @brief Flash controller wait states configuration register for Body High variant
   */
  #define BRSHW_FLASHC_FLASH_CTL              BRSHW_IOS(uint32, 0x40240000U)
 
  /**
   * @def BRSHW_CPUSS_RAM0_CTL
   * @value BRSHW_IOS(uint32, 0x40201300U)
   * @resolution -
   * @brief RAM0 wait states configuration register for Body High variant
   */
  #define BRSHW_CPUSS_RAM0_CTL                BRSHW_IOS(uint32, 0x40201300U)
 
  /**
   * @def BRSHW_CPUSS_RAM1_CTL
   * @value BRSHW_IOS(uint32, 0x40201380U)
   * @resolution -
   * @brief RAM1 wait states configuration register for Body High variant
   */
  #define BRSHW_CPUSS_RAM1_CTL                BRSHW_IOS(uint32, 0x40201380U)
 
  /**
   * @def BRSHW_CPUSS_RAM2_CTL
   * @value BRSHW_IOS(uint32, 0x402013A0U)
   * @resolution -
   * @brief RAM2 wait states configuration register for Body High variant
   */
  #define BRSHW_CPUSS_RAM2_CTL                BRSHW_IOS(uint32, 0x402013A0U)
 
  /**
   * @def BRSHW_CPUSS_ROM_CTL
   * @value BRSHW_IOS(uint32, 0x402013C4U)
   * @resolution -
   * @brief ROM wait states configuration register for Body High variant
   */
  #define BRSHW_CPUSS_ROM_CTL                 BRSHW_IOS(uint32, 0x402013C4U)
 
  /**
   * @def BRSHW_CPUSS_SYSTICK_CTL
   * @value BRSHW_IOS(uint32, 0x40201600U)
   * @resolution -
   * @brief System tick timer control register for Body High variant
   */
  #define BRSHW_CPUSS_SYSTICK_CTL             BRSHW_IOS(uint32, 0x40201600U)
 
  /**
   * @def BRSHW_CPUSS_SLOW_CLOCK_CTL
   * @value BRSHW_IOS(uint32, 0x40201008U)
   * @resolution -
   * @brief Slow clock control register for Body High variant
   */
  #define BRSHW_CPUSS_SLOW_CLOCK_CTL          BRSHW_IOS(uint32, 0x40201008U)
 
  /**
   * @def BRSHW_CPUSS_PERI_CLOCK_CTL
   * @value BRSHW_IOS(uint32, 0x4020100CU)
   * @resolution -
   * @brief Peripheral clock control register for Body High variant
   */
  #define BRSHW_CPUSS_PERI_CLOCK_CTL          BRSHW_IOS(uint32, 0x4020100CU)
 
  /**
   * @def BRSHW_CPUSS_MEM_CLOCK_CTL
   * @value BRSHW_IOS(uint32, 0x40201010U)
   * @resolution -
   * @brief Memory clock control register for Body High variant
   */
  #define BRSHW_CPUSS_MEM_CLOCK_CTL           BRSHW_IOS(uint32, 0x40201010U)
 
  /**
   * @def BRSHW_CPUSS_FAST_0_CLOCK_CTL
   * @value BRSHW_IOS(uint32, 0x40200008U)
   * @resolution -
   * @brief Fast clock 0 control register for Body High variant
   */
  #define BRSHW_CPUSS_FAST_0_CLOCK_CTL        BRSHW_IOS(uint32, 0x40200008U)
 
  /**
   * @def BRSHW_CPUSS_FAST_1_CLOCK_CTL
   * @value BRSHW_IOS(uint32, 0x40200408U)
   * @resolution -
   * @brief Fast clock 1 control register for Body High variant
   */
  #define BRSHW_CPUSS_FAST_1_CLOCK_CTL        BRSHW_IOS(uint32, 0x40200408U)
 
  /**
   * @def BRSHW_CPUSS_TRC_DBG_CLOCK_CTL
   * @value BRSHW_IOS(uint32, 0x40200320U)
   * @resolution -
   * @brief Trace and debug clock control register for Body High variant
   */
  #define BRSHW_CPUSS_TRC_DBG_CLOCK_CTL       BRSHW_IOS(uint32, 0x40200320U)
# endif /*BRS_PLL_GROUP_B*/
#endif /*BRS_ENABLE_PLLCLOCKS*/
/**********************************************************************************************************************
 *  LOCAL VARIABLES
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  LOCAL CONST VARIABLES
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  PROTOTYPES OF GLOBAL FUNCTIONS
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  PROTOTYPES OF LOCAL FUNCTIONS
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  FUNCTION DEFINITIONS
 *********************************************************************************************************************/
 
#if defined (BRS_ENABLE_WATCHDOG)
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |void |- |No return value |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Output registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |BRS_WDT_LOCK |Watchdog lock register used to protect against unwanted configuration changes |
 * |uint32 |BRS_WDT_CTL |Watchdog control register used to enable/disable and configure watchdog timer |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @brief Initializes the watchdog timer on system power-up by disabling it for development purposes
 * @note This function follows a specific sequence to unlock the watchdog protection, disable the watchdog timer, and then relock the protection. The unlock sequence requires two separate write operations to BRS_WDT_LOCK register with specific values (0x1 followed by 0x2). After disabling the watchdog, the protection is restored by writing 0x3 to BRS_WDT_LOCK.
 */
/* author Vector Informatik GmbH */
/* date 2023 */
/************************************************************************************************/
void BrsHwWatchdogInitPowerOn(void)
{
  /* WDG unlock: Lock release musst be performed in a two different write accesses */
  BRS_WDT_LOCK = 0x00000001U;
  __asm("NOP");
  BRS_WDT_LOCK = 0x00000002U;
 
  /*1. Step: WDT_LOCK = 0x1
  * 2. Step: WDT_LOCK = 0x2
  */
 
  /*dissable Watchdog ENABLE=0*/
  BRS_WDT_CTL = (uint32)(0U << 31U);
  __asm("NOP");
  __asm("NOP");
  __asm("NOP");
 
  /*WDG lock in a single write*/
  BRS_WDT_LOCK = (uint32)(3U << 0U);
}
#endif /*BRS_ENABLE_WATCHDOG*/
 
#if defined (BRS_ENABLE_PLLCLOCKS)
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |void |- |No return value |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |BRSHW_CLK_ECO_STATUS |External crystal oscillator status register for monitoring oscillator stability |
 * |uint32 |BRSHW_CLK_PLL_STATUS |PLL status register for monitoring PLL lock state |
 * |uint32 |BRSHW_CLK_PLL_STATUS0 |PLL0 status register for Body High variant |
 * @par Output registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |BRSHW_CLK_TRIM_ECO_CTL |External crystal oscillator trim control register (Body Entry) |
 * |uint32 |BRSHW_CLK_ECO_CONFIG |External crystal oscillator configuration register to enable the oscillator |
 * |uint32 |BRSHW_CLK_DSI_SELECT |Clock DSI selection register for selecting clock sources |
 * |uint32 |BRSHW_CLK_PATH_SELECT |Clock path selection registers to configure the source of each clock path |
 * |uint32 |BRSHW_CLK_PLL_CONFIG |PLL configuration register for setting frequency parameters |
 * |uint32 |BRSHW_FLASHC_FLASH_CTL |Flash wait states configuration register |
 * |uint32 |BRSHW_CPUSS_RAM0_CTL |RAM0 wait states configuration register |
 * |uint32 |BRSHW_CPUSS_RAM1_CTL |RAM1 wait states configuration register |
 * |uint32 |BRSHW_CPUSS_RAM2_CTL |RAM2 wait states configuration register (Body High only) |
 * |uint32 |BRSHW_CPUSS_ROM_CTL |ROM wait states configuration register |
 * |uint32 |BRSHW_CLK_ROOT_SELECT |Root clock selection register for system clock source |
 * |uint32 |BRSHW_CLK_TIMER_CTL |Timer clock control register |
 * |uint32 |BRSHW_CM0_CLOCK_CTL |CM0+ processor clock control register (Body Entry) |
 * |uint32 |BRSHW_CLK_ECO_CONFIG2 |Secondary ECO configuration register (Body High) |
 * |uint32 |BRSHW_CPUSS_MEM_CLOCK_CTL |Memory clock control register (Body High) |
 * |uint32 |BRSHW_CPUSS_SLOW_CLOCK_CTL |Slow clock control register (Body High) |
 * |uint32 |BRSHW_CPUSS_PERI_CLOCK_CTL |Peripheral clock control register (Body High) |
 * |uint32 |BRSHW_CPUSS_TRC_DBG_CLOCK_CTL |Trace and debug clock control register (Body High) |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @brief Initializes the PLL and clock system to configure system frequencies based on external crystal oscillator
 * @note This function configures the clock system
/* author Vector Informatik GmbH */
/* date 2023 */
/************************************************************************************************/
void BrsHwPllInitPowerOn(void)
{
#if defined (BRS_PLL_GROUP_A)
# if (BRS_OSC_CLK == 16) && (BRS_TIMEBASE_CLOCK == 100) && (BRS_PERIPH_CLOCK == 100)
  /*0.1 External Oscillator (ECO) setup */
  BRSHW_CLK_TRIM_ECO_CTL &= 0xFFFF0000;
  BRSHW_CLK_TRIM_ECO_CTL |= 0x00002FC6;
 
  /* 0. enable ECO (external crystal osc) */
  BRSHW_CLK_ECO_CONFIG |= 0x80000000;
 
  /* 1. wait until ECO is stable */
  while ((BRSHW_CLK_ECO_STATUS & 0x00000003) != 0x00000003);
 
  /* 2. select DSI source = ILO and PLL source = ECO (external crystal osc) */
  BRSHW_CLK_DSI_SELECT = 0x00000010;  /*ILO #0 selected*/
  BRSHW_CLK_PATH_SELECT(1) = 0x00000002;  /*ECO selected*/
 
  /* 3. set FEEDBACK_DIV (50), REFERENCE_DIV (4), and OUTPUT_DIV (2)
    Input frequency: Fref
    Output frequency: PLL_OUT
    Reference div: Q
    Feedback div: P
 
    Fref = 16MHz
 
    Fpfd = Fref / Q. It must be in the range 4 MHz to 8 MHz
    => 16MHz / Q -> Q = 4, Fpfd = 4MHz
 
    VCO = Fpfd * P. It must be in the range 170 MHz to 400 MHz.
    => 4MHz * P ->  P = 50, VCO = 200MHz
 
    PLL_OUT = VCO / OUTPUT_DIV. It must be in the range 11 MHz to 160 MHz.
    => 200MHz / OUTPUT_DIV -> OUTPUT_DIV = 2, PLL_OUT = 100MHz
 
    CM4 clock = CLK_HF = PLL_OUT = 100MHz
    CM0 clock = CLK_SLOW = CLK_PERI / 1 = 100MHz
    CLK_PERI = CLK_HF / 1 = 100MHz
  */
  BRSHW_CLK_PLL_CONFIG = 0x00020432u;
 
  /* 4. wait at least on cycle */
  BRSHWNOP10();
 
  /* 4.4 Set-up of the wait states for Flash, RAM0, RAM1 and ROM */
 
  /* Wait state for Flash MAIN_WS[3:0] = 1 */
  BRSHW_FLASHC_FLASH_CTL |= 0x00000001u;
 
  /* Wait states for RAM0, RAM1 und ROM */
  /* SLOW_WS[1:0] = '1' (from 100 MHz to 160 MHz of clk_hf.)*/
  /* FAST_WS[9:8] = '1' (should FAST_WS <= SLOW_WS) */
  BRSHW_CPUSS_RAM0_CTL |= 0x00000101u;
  BRSHW_CPUSS_RAM1_CTL |= 0x00000101u;
  BRSHW_CPUSS_ROM_CTL  |= 0x00000101u;
 
  /* 8. select PLL=Clock Path #1 for HF_CLK with predivider=NO_DIV (1) */
  BRSHW_CLK_ROOT_SELECT = 0x00000001u;
  BRSHWNOP10();
  BRSHW_CLK_ROOT_SELECT |= 0x80000000u;
 
  /* 9. select MCore SYSTICK Timer clk source = CLK_HF0 / 2 */
  /* has to be divided, as timer frequency has to be lower than 100MHz */
  BRSHW_CLK_TIMER_CTL = 0x00000101u;
  BRSHWNOP10();
  BRSHW_CLK_TIMER_CTL |= 0x80000000u;
 
  /* 10. select dividers: CLK_PERI = CLK_HF0 / 1, CLK_SLOW = CLK_PERI / 1  */
  BRSHW_CM0_CLOCK_CTL = 0x00000000u;
 
  /* 11. Enable PLL */
  BRSHW_CLK_PLL_CONFIG |= 0x80000000u;
 
  /* 12. wait at least 1us - 100MHz core clock -> 10ns/cycle, 1 cycle per NOP, 1us/10ns=100 NOPS required! */
  BrsHwTime100NOP();
 
  /* 13. wait until PLL is locked (needs about 50us) */
  while ((BRSHW_CLK_PLL_STATUS & 0x00000001u) == 0u);
 
# else
  #error "Only (BRS_OSC_CLK=16 && BRS_TIMEBASE_CLOCK=100 && BRS_PERIPH_CLOCK=100) is currently supported for Traveo-II B-E!"
# endif /*else BRS_OSC_CLK, BRS_TIMEBASE_CLOCK, BRS_PERIPH_CLOCK*/
#endif /*BRS_PLL_GROUP_A*/
 
#if defined (BRS_PLL_GROUP_B)
/* PLL/Clock initialization for Traveo-II Body-High */
# if (BRS_OSC_CLK == 16) && (BRS_TIMEBASE_CLOCK == 100) && (BRS_PERIPH_CLOCK == 100)
  /* 1.0 Setup the External Crystal Oscillator (ECO) */
  BRSHW_CLK_ECO_CONFIG2 = 0x00003FC6U;
 
  /* 1.1 Enable the ECO */
  BRSHW_CLK_ECO_CONFIG |= 0x80000000u;
 
  /* 1.2 Wait until ECO is stable */
  while (0x00000003u != (BRSHW_CLK_ECO_STATUS & 0x00000003u));
 
  /* 2.0 Set DSI Mux clock to Internal Low-speed Oscillator #0 (ILO0) */
  BRSHW_CLK_DSI_SELECT(1) = 0x00000010U;
  BRSHW_CLK_DSI_SELECT(3) = 0x00000010U;
 
  /* 2.1 Set ECO as the fREF (16 MHz) to PLL0, without Spread Spectrum Clock Generation */
  BRSHW_CLK_PATH_SELECT(1) = 0x00000002U;
 
  BRSHWNOP10();
 
  /* 2.2 Set ECO as the fREF (16 MHz) to PLL400M0 (PLL2), with Spread Spectrum Clock Generation and fractional operation */
  BRSHW_CLK_PATH_SELECT(3) = 0x00000002U;
 
  BRSHWNOP10();
 
  /* 6.0 Set PLL#2 output frequency to 100 MHz
   * Set PLL#2 bypass mux to PLL_REF before changing the configuration
   * Static phase error window = 20.66 ns, Auto BYPASS_SEL
   * fOUT = (FEEDBACK_DIV) * (fREF / REFERENCE_DIV) / (OUTPUT_DIV)
   * FEEDBACK_DIV = 50, REFERENCE_DIV = 4, OUTPUT_DIV = 2, VCO freq = 200 MHz
   */
  BRSHW_CLK_PLL_CONFIG0 = 0x20020116U;
  BRSHWNOP10();
  BRSHW_CLK_PLL_CONFIG0 = 0x00020432U;
  __asm("NOP");
 
  /* 6.1 Enable PLL#2 */
  BRSHW_CLK_PLL_CONFIG0 |= 0x80000000u;
 
  /* 6.2 Wait at least 1us (fPLL = 100 MHz) */
  BrsHwTime100NOP();
 
  /* 6.3 Wait until PLL#2 is locked */
  while ((uint32)0 == (BRSHW_CLK_PLL_STATUS0 & 0x00000001u));
 
  /* 8.0 Set CLK_MEM to 100 MHz (Divide CLK_HF0 by 1) */
  BRSHW_CPUSS_MEM_CLOCK_CTL = 0x00000000U;
  /* 8.1 Set CLK_SLOW to 100 MHz (Divide CLK_MEM by 1). CLK_SLOW = CLK_GR0 = CLK_GR1 = CLK_GR2 */
  BRSHW_CPUSS_SLOW_CLOCK_CTL = 0x00000000U;
  /* 8.2 Set CLK_PERI to 100 MHz (Divide CLK_HF0 by 1) */
  BRSHW_CPUSS_PERI_CLOCK_CTL = 0x00000000U;
  /* 8.3 Set CLK_TRC_DBG to 50 MHz (Divide CLK_HF0 by 2) */
  BRSHW_CPUSS_TRC_DBG_CLOCK_CTL = 0x00000100U;
 
  /* 10.0 Set wait states for ROM/SRAM/FLASH */
  BRSHW_FLASHC_FLASH_CTL |= 0x00000001u;
  BRSHW_CPUSS_ROM_CTL     = 0x00000101u;
  BRSHW_CPUSS_RAM0_CTL   |= 0x00000101u;
  BRSHW_CPUSS_RAM1_CTL   |= 0x00000101u;
  BRSHW_CPUSS_RAM2_CTL   |= 0x00000101u;
 
  /* 10.1 Set CLK_PATH3 (PLL#2) as a source to CLK_HF0 root clock */
  BRSHW_CLK_ROOT_SELECT(0) = 0x00000103U;
 
# else
  #error "Only (BRS_OSC_CLK=16 && BRS_TIMEBASE_CLOCK=100 && BRS_PERIPH_CLOCK=100) is currently supported for Traveo-II B-H!"
# endif /*else BRS_OSC_CLK, BRS_TIMEBASE_CLOCK, BRS_PERIPH_CLOCK*/
#endif /*BRS_PLL_GROUP_B*/
}
#endif /*BRS_ENABLE_PLLCLOCKS*/
 
/* BrsHwDisableInterruptAtPowerOn() is part of ArmCommon */
 
/* BrsHw_ExceptionTable_Init() is part of ArmCommon */
 
/* BrsHwSoftwareResetECU() is performed according to the ARM Spec and is part of ArmCommon */
 
 
/* This code is only needed for the first instance/executable in the system */
/** @cond INTERNAL */
#define BRS_START_SEC_STARTUP_CODE
/** @endcond */
#include "Brs_MemMap.h"
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |brsMain_ResetReasonType |resetReason |Reset reason identifier (BRSMAIN_RESET_SW: software reset, BRSMAIN_RESET_OTHER: any other reset type) |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |BRSHW_RESET_CAUSE |Reset cause observation register to determine the source of reset |
 * |uint32 |BRSHW_RESET_CAUSE2 |Secondary reset cause observation register for additional reset sources |
 * @par Output registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |BRSHW_RESET_CAUSE_COPY |Backup memory location to store reset cause value for later analysis |
 * |uint32 |BRSHW_RESET_CAUSE2_COPY |Backup memory location to store secondary reset cause value |
 * |uint32 |BRSHW_RESET_CAUSE |Reset cause register is cleared after reading to prepare for next reset event |
 * |uint32 |BRSHW_RESET_CAUSE2 |Secondary reset cause register is cleared after reading |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @brief Determines the reason for the system reset by examining hardware reset cause registers
 * @note This function should only be called once during system startup. It reads the hardware reset cause registers
 */
/* author Vector Informatik GmbH */
/* date 2023 */
/************************************************************************************************/
brsMain_ResetReasonType BrsHwGetResetReasonStartup(void)
{
  /* Stores the ResetCause register value to shared memory and clear the register. */
  BRSHW_RESET_CAUSE_COPY = BRSHW_RESET_CAUSE;
  BRSHW_RESET_CAUSE = 0xFFFFFFFFu;
  BRSHW_RESET_CAUSE2_COPY = BRSHW_RESET_CAUSE2;
  BRSHW_RESET_CAUSE2 = 0xFFFFFFFFu;
 
  /* Determined based on the ResetCause stored in shared memory. */
  if((BRSHW_RESET_CAUSE_COPY & BRSHW_SWRESET_TRIGGERT_MASK) != 0u)
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
/** @cond INTERNAL */
#define BRS_STOP_SEC_STARTUP_CODE
/** @endcond */
#include "Brs_MemMap.h"
 
 
/* BrsHwTime100NOP() is part of ArmCommon */
 
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |coreId |Core identifier number (always 0 in this implementation since only SingleCore is supported) |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Output registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @brief Returns the core identifier of the currently executing CPU core
 * @note This function is called from main to determine if the current core is the boot core
 */
/* author Vector Informatik GmbH */
/* date 2023 */
/************************************************************************************************/
uint32 BrsHw_GetCore(void)
{
  /* only SingleCore supported up to now */
  return 0u;
}
 
/* BrsHw_EnableInterrupt() is part of ArmCommon */
 
/* BrsHw_DisableInterrupt() is part of ArmCommon */
 
/* BrsHw_TriggerSoftwareInterrupt() is part of ArmCommon */
 
 