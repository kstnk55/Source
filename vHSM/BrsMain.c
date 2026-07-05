/**
 * @file BrsMain.c
 * @brief Public header: BrsMain.h
 * @details Overview: Main file of Vector Basic Runtime System (BRS) implementing system initialization, cyclic task management, and exception handling
 */
 
#define _BRSMAIN_C_
 
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "BrsMain.h"
#include "system_cyt4bf.h"
#include "cmsis_ghs.h"
#include "CoreIso.h"
 
#if !defined (_MICROSOFT_C_VTT_)
# if (BRSHW_SOURCECODE_TEMPLATE_VERSION >= 0x0103u)
  #include "vBrs_Lcfg.h"
# endif
#else
  #include "CANoeAPI.h"
  #include <stdio.h>
  #include "Os.h"
#endif
 
 
#if defined (BRS_ENABLE_TESTSUITE_SUPPORT)
  #include "BrsTestsuite.h"
#endif
 
#include "DualBank_Manager_FblTransition.h"
/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
#if (BRSMAIN_VERSION != 0x0210u)
  #error "Header and source file are inconsistent!"
#endif
#if (BRSMAIN_BUGFIX_VERSION != 0x01u)
  #error "Different versions of bugfix in Header and Source used!"
#endif
 
/* BRS_GENERATED_HW_CONFIG_VERSION is generated into vBrsCfg.h by Cfg5 vBrs generator */
#if (BRS_GENERATED_HW_CONFIG_VERSION < 373U)
  #error "Version of vBrs Generator too old! Please update it."
#endif
 
/**********************************************************************************************************************
 *  CONFIGURATION CHECK
 *********************************************************************************************************************/
#if defined (BRS_ENABLE_OS_INTERRUPT_ONLY) && defined (BRS_ENABLE_OS_MULTICORESUPPORT)
  #error "OS MultiCore support is not supported together with OS INTERRUPT_ONLY UseCase!"
#endif
 
#if defined (BRS_ENABLE_OS_MULTICORESUPPORT)
  #error "This file was filtered for SingleCore UseCase, but MultiCore UseCase is configured!"
#endif
 
/**********************************************************************************************************************
 *  DEFINITION + MACROS
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  GLOBAL VARIABLES
 *********************************************************************************************************************/
 
/**
 * @def BRSMAIN_CYCLIC_MAX_CALLBACKS
 * @value 2U
 * @resolution -
 * @brief Maximum number of callback functions that can be registered for each cyclic time interval
 */
#if defined (BRS_ENABLE_1MS_HANDLER)
# if !defined (BRSMAIN_CYCLIC_MAX_CALLBACKS)
  #define BRSMAIN_CYCLIC_MAX_CALLBACKS 2u
# endif
 
  #define START_SEC_VAR_NOINIT_UNSPECIFIED
  #include "MemMap.h"
 
/**
 * @brief Data structure to store function pointers and counter for cyclic callbacks
 * @datasize
 */
  typedef struct
  {
    void (*FunctionPointer[BRSMAIN_CYCLIC_MAX_CALLBACKS]) (void); /**< Array of function pointers for callbacks */
    uint8 FunctionCounter; /**< Counter tracking the number of registered callbacks */
  }brsMain_Cyclic_Callbacks;
  #define STOP_SEC_VAR
  #include "MemMap.h"
#endif /*BRS_ENABLE_1MS_HANDLER*/
 
 
#if !defined (_MICROSOFT_C_VTT_)
extern volatile brsMain_ResetReasonType brsMain_ResetReason;
#endif
 
#if (JUMP_TO_FBL_ENABLE == STD_ON)
extern uint16 ResetCounter;
#endif
 
/**********************************************************************************************************************
 *  GLOBAL CONST VARIABLES
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  LOCAL VARIABLES
 *********************************************************************************************************************/
#if defined (BRS_ENABLE_1MS_HANDLER)
  #define START_SEC_VAR_ZERO_INIT_16BIT
  #include "MemMap.h"
 
/**
 * @type uint16
 * @var brsMain_CallCounter1ms
 * @brief Counter tracking the number of calls to BrsMainCyclic1ms function for timing calculations
 * @unit -
 * @scope Local Variables
 * @section -
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |- |- |- |- |- |
 */
  static volatile uint16 brsMain_CallCounter1ms;
 
/**
 * @type uint16
 * @var brsMain_CallCounter1sec
 * @brief Counter tracking the number of seconds elapsed based on 1000 calls to BrsMainCyclic1ms
 * @unit -
 * @scope Local Variables
 * @section -
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |- |- |- |- |- |
 */
  static volatile uint16 brsMain_CallCounter1sec;
  #define STOP_SEC_VAR
  #include "MemMap.h"
 
  #define START_SEC_VAR_NOINIT_UNSPECIFIED
  #include "MemMap.h"
 
/**
 * @type brsMain_Cyclic_Callbacks
 * @var brsMain_Cyclic_Callbacks_Background
 * @brief Structure to store function pointers for background task cycle callbacks
 * @unit -
 * @scope Local Variables
 * @section -
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |- |- |- |- |- |
 */
  static brsMain_Cyclic_Callbacks brsMain_Cyclic_Callbacks_Background;
 
/**
 * @type brsMain_Cyclic_Callbacks
 * @var brsMain_Cyclic_Callbacks_1ms
 * @brief Structure to store function pointers for 1ms cycle callbacks
 * @unit -
 * @scope Local Variables
 * @section -
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |- |- |- |- |- |
 */
  static brsMain_Cyclic_Callbacks brsMain_Cyclic_Callbacks_1ms;
 
/**
 * @type brsMain_Cyclic_Callbacks
 * @var brsMain_Cyclic_Callbacks_10ms
 * @brief Structure to store function pointers for 10ms cycle callbacks
 * @unit -
 * @scope Local Variables
 * @section -
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |- |- |- |- |- |
 */
  static brsMain_Cyclic_Callbacks brsMain_Cyclic_Callbacks_10ms;
 
/**
 * @type brsMain_Cyclic_Callbacks
 * @var brsMain_Cyclic_Callbacks_100ms
 * @brief Structure to store function pointers for 100ms cycle callbacks
 * @unit -
 * @scope Local Variables
 * @section -
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |- |- |- |- |- |
 */
  static brsMain_Cyclic_Callbacks brsMain_Cyclic_Callbacks_100ms;
 
/**
 * @type brsMain_Cyclic_Callbacks
 * @var brsMain_Cyclic_Callbacks_250ms
 * @brief Structure to store function pointers for 250ms cycle callbacks
 * @unit -
 * @scope Local Variables
 * @section
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |- |- |- |- |- |
 */
  static brsMain_Cyclic_Callbacks brsMain_Cyclic_Callbacks_250ms;
 
/**
 * @type brsMain_Cyclic_Callbacks
 * @var brsMain_Cyclic_Callbacks_500ms
 * @brief Structure to store function pointers for 500ms cycle callbacks
 * @unit -
 * @scope Local Variables
 * @section
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |- |- |- |- |- |
 */
  static brsMain_Cyclic_Callbacks brsMain_Cyclic_Callbacks_500ms;
 
/**
 * @type brsMain_Cyclic_Callbacks
 * @var brsMain_Cyclic_Callbacks_1000ms
 * @brief Structure to store function pointers for 1000ms cycle callbacks
 * @unit -
 * @scope -
 * @section Local Variables
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |- |- |- |- |- |
 */
  static brsMain_Cyclic_Callbacks brsMain_Cyclic_Callbacks_1000ms;
  #define STOP_SEC_VAR
  #include "MemMap.h"
#endif /*BRS_ENABLE_1MS_HANDLER*/
 
#if defined (BRS_ENABLE_OS_INTERRUPT_ONLY)
  #define START_SEC_VAR_ZERO_INIT_32BIT
  #include "MemMap.h"
 
/**
 * @type uint32
 * @var brsMain_SuspendAllCounter
 * @brief Counter for tracking nested calls to SuspendAllInterrupts in OS interrupt-only mode
 * @unit -
 * @scope Local Variables
 * @section -
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |- |- |- |- |- |
 */
  static volatile uint32 brsMain_SuspendAllCounter;
  #define STOP_SEC_VAR
  #include "MemMap.h"
#endif
 
/**********************************************************************************************************************
 *  LOCAL CONST VARIABLES
 *********************************************************************************************************************/
# if defined (_MICROSOFT_C_VTT_)
/**
 * @def BRSMAIN_ERRORBUFFERSIZE
 * @value 120
 * @resolution -
 * @brief Size of the error message buffer used in VTT (Virtual Target) environment for exception handling
 */
  #define BRSMAIN_ERRORBUFFERSIZE  120
#endif
 
/**********************************************************************************************************************
 *  PROTOTYPES OF GLOBAL FUNCTIONS
 *********************************************************************************************************************/
#if defined (BRS_FBL_NO_ECUMINIT)
extern void FblMain(void);
#endif
 
/**********************************************************************************************************************
 *  PROTOTYPES OF LOCAL FUNCTIONS
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#if !defined (_MICROSOFT_C_VTT_)
# if defined (BRS_ENABLE_SUPPORT_LEDS)
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
 * |- |- |- |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @brief Wrapper function for toggling the LED pin via BrsMainTogglePin
 * @note This function serves as a wrapper for the BrsMainTogglePin function with the LED pin parameter,
 *       making it suitable for registration as a callback function in the cyclic task system
 */
/* author Vector Informatik GmbH */
/* date 2022 */
/************************************************************************************************/
void BrsMainWrapperTogglePinLED(void)
{
  BrsMainTogglePin(BRSMAIN_TOGGLEPIN_LED);
}
# endif
 
# if defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN)
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
 * |- |- |- |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @brief Wrapper function for toggling the watchdog pin via BrsMainTogglePin
 * @note This function serves as a wrapper for the BrsMainTogglePin function with the watchdog pin parameter,
 *       making it suitable for registration as a callback function in the cyclic task system
 */
/* author Vector Informatik GmbH */
/* date 2022 */
/************************************************************************************************/
void BrsMainWrapperTogglePinWD(void)
{
  BrsMainTogglePin(BRSMAIN_TOGGLEPIN_WD);
}
# endif
 
# if defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
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
 * |- |- |- |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @brief Wrapper function for toggling the custom pin via BrsMainTogglePin
 * @note This function serves as a wrapper for the BrsMainTogglePin function with the custom pin parameter,
 *       making it suitable for registration as a callback function in the cyclic task system
 */
/* author Vector Informatik GmbH */
/* date 2022 */
/************************************************************************************************/
void BrsMainWrapperTogglePinCustom(void)
{
  BrsMainTogglePin(BRSMAIN_TOGGLEPIN_CUSTOM);
}
# endif
#endif /*!_MICROSOFT_C_VTT_*/
 
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
 * |uint16 |brsMain_CallCounter1ms |Initialized to 0 for new timing cycle |
 * |uint16 |brsMain_CallCounter1sec |Initialized to 0 for new second counting |
 * |brsMain_Cyclic_Callbacks |brsMain_Cyclic_Callbacks_Background |FunctionCounter initialized to 0 |
 * |brsMain_Cyclic_Callbacks |brsMain_Cyclic_Callbacks_1ms |FunctionCounter initialized to 0 |
 * |brsMain_Cyclic_Callbacks |brsMain_Cyclic_Callbacks_10ms |FunctionCounter initialized to 0 |
 * |brsMain_Cyclic_Callbacks |brsMain_Cyclic_Callbacks_100ms |FunctionCounter initialized to 0 |
 * |brsMain_Cyclic_Callbacks |brsMain_Cyclic_Callbacks_250ms |FunctionCounter initialized to 0 |
 * |brsMain_Cyclic_Callbacks |brsMain_Cyclic_Callbacks_500ms |FunctionCounter initialized to 0 |
 * |brsMain_Cyclic_Callbacks |brsMain_Cyclic_Callbacks_1000ms |FunctionCounter initialized to 0 |
 * |uint32 |brsMain_SuspendAllCounter |Initialized to 0 when OS interrupt-only mode is enabled |
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
 * @brief Main initialization routine for configuring hardware and BrsMain cyclic mechanisms
 * @note This function initializes the Basic Runtime System
 */
/* author Vector Informatik GmbH */
/* date 2022 */
/************************************************************************************************/
void BrsMainInit(void)
{
#if defined (BRSMAIN_BRSMAININIT_CALLOUT)
  BrsTestsuite_BrsMain_BrsMainInit();
#endif
 
 
#if (!defined (BRS_FBL_NO_ECUMINIT)) && (!defined (_MICROSOFT_C_VTT_))
# if !defined (BRS_ENABLE_PREFER_PLL_WATCHDOG_INIT)
  /* If preferred feature is acivated, initialization will take place in BrsMain_MemoryInit_StageOne_Hook(). */
#  if defined (BRSHW_PREINIT_AVAILABLE)
  BrsHwPreInitPowerOn();
#  endif
 
#  if defined (BRS_ENABLE_WATCHDOG)
  BrsHwWatchdogInitPowerOn();
#  endif
 
#  if defined (BRS_ENABLE_PLLCLOCKS)
  BrsHwPllInitPowerOn();
#  endif
# endif
 
# if defined (BRS_ENABLE_PORT)
  BrsHwPortInitPowerOn();
# endif
 
# if defined (BRS_ENABLE_FBL_SUPPORT)
#  if defined (BRSHW_DISABLE_ECC_AVAILABLE)
  BrsHwDisableEccErrorReporting();
#  endif
# endif
#endif
 
#if defined (BRS_ENABLE_1MS_HANDLER)
  brsMain_CallCounter1ms = 0u;
  brsMain_CallCounter1sec = 0u;
 
  brsMain_Cyclic_Callbacks_Background.FunctionCounter = 0u;
  brsMain_Cyclic_Callbacks_1ms.FunctionCounter        = 0u;
  brsMain_Cyclic_Callbacks_10ms.FunctionCounter       = 0u;
  brsMain_Cyclic_Callbacks_100ms.FunctionCounter      = 0u;
  brsMain_Cyclic_Callbacks_250ms.FunctionCounter      = 0u;
  brsMain_Cyclic_Callbacks_500ms.FunctionCounter      = 0u;
  brsMain_Cyclic_Callbacks_1000ms.FunctionCounter     = 0u;
#endif /*BRS_ENABLE_1MS_HANDLER*/
 
#if !defined (_MICROSOFT_C_VTT_)
# if defined (BRS_ENABLE_SUPPORT_LEDS)
  BrsMainRegisterCyclic(BrsMainWrapperTogglePinLED, BRSMAIN_CYCLETIME_500MS);
# endif
 
# if defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN)
  BrsMainRegisterCyclic(BrsMainWrapperTogglePinWD, BRSMAIN_CYCLETIME_250MS);
# endif
 
# if defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
  BrsMainRegisterCyclic(BrsMainWrapperTogglePinCustom, BRSMAIN_CYCLETIME_1000MS);
# endif
#endif
 
#if defined (BRS_ENABLE_OS_INTERRUPT_ONLY)
  brsMain_SuspendAllCounter = 0u;
#endif
}
 
#if defined (BRS_ENABLE_1MS_HANDLER)
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |void (*)(void) |FunctionPointer |Pointer to callback function that takes no arguments and returns void |
 * |brsMain_Cyclic_Cycletime |Cycletime |Enumeration value specifying the desired callback interval (BACKGROUND, 1MS, 10MS, 100MS, 250MS, 500MS, or 1000MS) |
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
 * |brsMain_Cyclic_Callbacks |brsMain_Cyclic_Callbacks_Background |Checked to ensure it has space for additional callbacks |
 * |brsMain_Cyclic_Callbacks |brsMain_Cyclic_Callbacks_1ms |Checked to ensure it has space for additional callbacks |
 * |brsMain_Cyclic_Callbacks |brsMain_Cyclic_Callbacks_10ms |Checked to ensure it has space for additional callbacks |
 * |brsMain_Cyclic_Callbacks |brsMain_Cyclic_Callbacks_100ms |Checked to ensure it has space for additional callbacks |
 * |brsMain_Cyclic_Callbacks |brsMain_Cyclic_Callbacks_250ms |Checked to ensure it has space for additional callbacks |
 * |brsMain_Cyclic_Callbacks |brsMain_Cyclic_Callbacks_500ms |Checked to ensure it has space for additional callbacks |
 * |brsMain_Cyclic_Callbacks |brsMain_Cyclic_Callbacks_1000ms |Checked to ensure it has space for additional callbacks |
 * |uint8 |BRSMAIN_CYCLIC_MAX_CALLBACKS |Constant defining the maximum number of callbacks per time interval |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |brsMain_Cyclic_Callbacks |brsMain_Cyclic_Callbacks_Background |Updated with new callback function if Background cycle is selected |
 * |brsMain_Cyclic_Callbacks |brsMain_Cyclic_Callbacks_1ms |Updated with new callback function if 1ms cycle is selected |
 * |brsMain_Cyclic_Callbacks |brsMain_Cyclic_Callbacks_10ms |Updated with new callback function if 10ms cycle is selected |
 * |brsMain_Cyclic_Callbacks |brsMain_Cyclic_Callbacks_100ms |Updated with new callback function if 100ms cycle is selected |
 * |brsMain_Cyclic_Callbacks |brsMain_Cyclic_Callbacks_250ms |Updated with new callback function if 250ms cycle is selected |
 * |brsMain_Cyclic_Callbacks |brsMain_Cyclic_Callbacks_500ms |Updated with new callback function if 500ms cycle is selected |
 * |brsMain_Cyclic_Callbacks |brsMain_Cyclic_Callbacks_1000ms |Updated with new callback function if 1000ms cycle is selected |
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
 * @brief Registers a function to be called cyclically at a specified time interval
 * @note This function adds a callback function to the appropriate array based on the specified cycle time.
 */
/* author Vector Informatik GmbH */
/* date 2022 */
/************************************************************************************************/
void BrsMainRegisterCyclic(void (*FunctionPointer)(void), brsMain_Cyclic_Cycletime Cycletime)
{
#if defined (BRSMAIN_BRSMAINREGISTERCYCLIC_CALLOUT)
  BrsTestsuite_BrsMain_BrsMainRegisterCyclic(FunctionPointer, Cycletime);
#endif
 
  switch (Cycletime)
  {
    case BRSMAIN_CYCLETIME_BACKGROUND:
      if (brsMain_Cyclic_Callbacks_Background.FunctionCounter >= BRSMAIN_CYCLIC_MAX_CALLBACKS)
      {
        BrsMainExceptionHandler(kBrsIllegalParameter, BRSERROR_MODULE_BRSMAIN, (uint16)(__LINE__));
      }
      brsMain_Cyclic_Callbacks_Background.FunctionPointer[brsMain_Cyclic_Callbacks_Background.FunctionCounter] = FunctionPointer;
      brsMain_Cyclic_Callbacks_Background.FunctionCounter++;
      break;
 
    case BRSMAIN_CYCLETIME_1MS:
      if (brsMain_Cyclic_Callbacks_1ms.FunctionCounter >= BRSMAIN_CYCLIC_MAX_CALLBACKS)
      {
        BrsMainExceptionHandler(kBrsIllegalParameter, BRSERROR_MODULE_BRSMAIN, (uint16)(__LINE__));
      }
      brsMain_Cyclic_Callbacks_1ms.FunctionPointer[brsMain_Cyclic_Callbacks_1ms.FunctionCounter] = FunctionPointer;
      brsMain_Cyclic_Callbacks_1ms.FunctionCounter++;
      break;
 
    case BRSMAIN_CYCLETIME_10MS:
      if (brsMain_Cyclic_Callbacks_10ms.FunctionCounter >= BRSMAIN_CYCLIC_MAX_CALLBACKS)
      {
        BrsMainExceptionHandler(kBrsIllegalParameter, BRSERROR_MODULE_BRSMAIN, (uint16)(__LINE__));
      }
      brsMain_Cyclic_Callbacks_10ms.FunctionPointer[brsMain_Cyclic_Callbacks_10ms.FunctionCounter] = FunctionPointer;
      brsMain_Cyclic_Callbacks_10ms.FunctionCounter++;
      break;
 
    case BRSMAIN_CYCLETIME_100MS:
      if (brsMain_Cyclic_Callbacks_100ms.FunctionCounter >= BRSMAIN_CYCLIC_MAX_CALLBACKS)
      {
        BrsMainExceptionHandler(kBrsIllegalParameter, BRSERROR_MODULE_BRSMAIN, (uint16)(__LINE__));
      }
      brsMain_Cyclic_Callbacks_100ms.FunctionPointer[brsMain_Cyclic_Callbacks_100ms.FunctionCounter] = FunctionPointer;
      brsMain_Cyclic_Callbacks_100ms.FunctionCounter++;
      break;
 
    case BRSMAIN_CYCLETIME_250MS:
      if (brsMain_Cyclic_Callbacks_250ms.FunctionCounter >= BRSMAIN_CYCLIC_MAX_CALLBACKS)
      {
        BrsMainExceptionHandler(kBrsIllegalParameter, BRSERROR_MODULE_BRSMAIN, (uint16)(__LINE__));
      }
      brsMain_Cyclic_Callbacks_250ms.FunctionPointer[brsMain_Cyclic_Callbacks_250ms.FunctionCounter] = FunctionPointer;
      brsMain_Cyclic_Callbacks_250ms.FunctionCounter++;
      break;
 
    case BRSMAIN_CYCLETIME_500MS:
      if (brsMain_Cyclic_Callbacks_500ms.FunctionCounter >= BRSMAIN_CYCLIC_MAX_CALLBACKS)
      {
        BrsMainExceptionHandler(kBrsIllegalParameter, BRSERROR_MODULE_BRSMAIN, (uint16)(__LINE__));
      }
      brsMain_Cyclic_Callbacks_500ms.FunctionPointer[brsMain_Cyclic_Callbacks_500ms.FunctionCounter] = FunctionPointer;
      brsMain_Cyclic_Callbacks_500ms.FunctionCounter++;
      break;
 
    case BRSMAIN_CYCLETIME_1000MS:
      if (brsMain_Cyclic_Callbacks_1000ms.FunctionCounter >= BRSMAIN_CYCLIC_MAX_CALLBACKS)
      {
        BrsMainExceptionHandler(kBrsIllegalParameter, BRSERROR_MODULE_BRSMAIN, (uint16)(__LINE__));
      }
      brsMain_Cyclic_Callbacks_1000ms.FunctionPointer[brsMain_Cyclic_Callbacks_1000ms.FunctionCounter] = FunctionPointer;
      brsMain_Cyclic_Callbacks_1000ms.FunctionCounter++;
      break;
 
    default:
      BrsMainExceptionHandler(kBrsIllegalParameter, BRSERROR_MODULE_BRSMAIN, (uint16)(__LINE__));
      break;
  }
}
#endif /*BRS_ENABLE_1MS_HANDLER*/
 
#if (!defined (BRS_ENABLE_FBL_SUPPORT)) && (!defined (BRS_ENABLE_OS_INTERRUPT_ONLY))
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |void |- |Task does not return but terminates itself |
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
 * @brief AUTOSAR OS task responsible for initializing the AUTOSAR stack by calling EcuM_StartupTwo()
 * @note This task is started once by the OS during system initialization.
 */
/* author Vector Informatik GmbH */
/* date 2022 */
/************************************************************************************************/
TASK(Default_Init_Task)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task();
#endif
 
#if defined (BRS_ENABLE_OS_MULTICORESUPPORT)
  /* Workaround for RTE ESCAN00078832 */
  /* Use this code, if you get a Det Error at the end of Rte_Start() on MasterCore */
  /* Rte_Start() on the SlaveCores has to be called first, before Rte_Start() on MasterCore */
  /* SET THIS InitTask TO FULL PREEMPTIVE (OsTaskSchedule) within OsConfig! */
  /*while(Rte_InitState_1 != RTE_STATE_INIT)
  {
    (void)Schedule();
  }*/
#endif /*BRS_ENABLE_OS_MULTICORESUPPORT*/
 
#if defined (BRS_ENABLE_TESTSUITE_SUPPORT)
  BrsTestsuiteInit();
#endif
 
#if defined (BRS_ENABLE_HSM_SUPPORT)
  vHsm_StartupTwo();
#else
  EcuM_StartupTwo();
#endif
 
  (void)TerminateTask();
}
 
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |void |- |Task does not return but terminates itself |
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
 * @brief AUTOSAR OS trusted task that enables interrupt sources by calling Os_InitialEnableInterruptSources()
 * @note This task is started once by the OS during system initialization.
 */
/* author Vector Informatik GmbH */
/* date 2022 */
/************************************************************************************************/
TASK(Default_Init_Task_Trusted)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_TRUSTED_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Trusted();
#endif
 
  Os_InitialEnableInterruptSources(FALSE);
 
  (void)TerminateTask();
}
 
#endif
 
#if defined (BRS_ENABLE_1MS_HANDLER)
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
 * |brsMain_Cyclic_Callbacks |brsMain_Cyclic_Callbacks_1ms |Array of callback functions to execute every 1ms |
 * |brsMain_Cyclic_Callbacks |brsMain_Cyclic_Callbacks_10ms |Array of callback functions to execute every 10ms |
 * |brsMain_Cyclic_Callbacks |brsMain_Cyclic_Callbacks_100ms |Array of callback functions to execute every 100ms |
 * |brsMain_Cyclic_Callbacks |brsMain_Cyclic_Callbacks_250ms |Array of callback functions to execute every 250ms |
 * |brsMain_Cyclic_Callbacks |brsMain_Cyclic_Callbacks_500ms |Array of callback functions to execute every 500ms |
 * |brsMain_Cyclic_Callbacks |brsMain_Cyclic_Callbacks_1000ms |Array of callback functions to execute every 1000ms |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint16 |brsMain_CallCounter1ms |Incremented each call; reset to 0 every 1000 calls |
 * |uint16 |brsMain_CallCounter1sec |Incremented every 1000ms (once per second) |
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
 * |uint8 |cycliccounter |Loop counter used when iterating through the callback function arrays |
 * @brief One millisecond cyclic handler that executes registered callbacks at various time intervals
 * @note This function serves as the central timing engine for the BRS system.
 */
/* author Vector Informatik GmbH */
/* date 2022 */
/************************************************************************************************/
void BrsMainCyclic1ms(void)
{
  uint8 cycliccounter;
 
#if defined (BRSMAIN_BRSMAINCYCLIC1MS_CALLOUT)
  BrsTestsuite_BrsMain_BrsMainCyclic1ms();
#endif
 
  brsMain_CallCounter1ms++;
 
  for (cycliccounter=0u; cycliccounter<brsMain_Cyclic_Callbacks_1ms.FunctionCounter; cycliccounter++)
  {
    brsMain_Cyclic_Callbacks_1ms.FunctionPointer[cycliccounter]();
  }
 
  if (brsMain_CallCounter1ms %10 == 0)
  {
    for (cycliccounter=0u; cycliccounter<brsMain_Cyclic_Callbacks_10ms.FunctionCounter; cycliccounter++)
    {
      brsMain_Cyclic_Callbacks_10ms.FunctionPointer[cycliccounter]();
    }
  }
 
  if (brsMain_CallCounter1ms %100 == 0)
  {
    for (cycliccounter=0u; cycliccounter<brsMain_Cyclic_Callbacks_100ms.FunctionCounter; cycliccounter++)
    {
      brsMain_Cyclic_Callbacks_100ms.FunctionPointer[cycliccounter]();
    }
  }
 
  if (brsMain_CallCounter1ms %250 == 0)
  {
    for (cycliccounter=0u; cycliccounter<brsMain_Cyclic_Callbacks_250ms.FunctionCounter; cycliccounter++)
    {
      brsMain_Cyclic_Callbacks_250ms.FunctionPointer[cycliccounter]();
    }
  }
 
  if (brsMain_CallCounter1ms %500 == 0)
  {
    for (cycliccounter=0u; cycliccounter<brsMain_Cyclic_Callbacks_500ms.FunctionCounter; cycliccounter++)
    {
      brsMain_Cyclic_Callbacks_500ms.FunctionPointer[cycliccounter]();
    }
  }
 
  if (brsMain_CallCounter1ms %1000 == 0)
  {
    for (cycliccounter=0u; cycliccounter<brsMain_Cyclic_Callbacks_1000ms.FunctionCounter; cycliccounter++)
    {
      brsMain_Cyclic_Callbacks_1000ms.FunctionPointer[cycliccounter]();
    }
    brsMain_CallCounter1ms = 0u;
    brsMain_CallCounter1sec++;
  }
}
 
# if (!defined (BRS_ENABLE_FBL_SUPPORT)) && (!defined (BRS_ENABLE_OS_INTERRUPT_ONLY))
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |void |- |No return value; task runs in an infinite loop |
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
 * |EventMaskType |ev |Stores event mask received from OS to determine which event triggered the task |
 * @brief AUTOSAR OS task that cyclically executes the 1ms handler function BrsMainCyclic1ms
 * @note This task is started once by the OS at system initialization and runs in an infinite loop.
 */
/* author Vector Informatik GmbH */
/* date 2022 */
/************************************************************************************************/
TASK(BrsMainTask)
{
  EventMaskType ev;
 
#if defined (BRSMAIN_BRSMAINTASK_CALLOUT)
  BrsTestsuite_BrsMain_BrsMainTask();
#endif
 
  (void)SetRelAlarm(BrsCyclicAlarm_1ms, OS_MS2TICKS_SystemTimer(1), OS_MS2TICKS_SystemTimer(1));
 
  for(;;)
  {
    (void)WaitEvent(BrsEvCyclicAlarm_1ms);
    (void)GetEvent(BrsMainTask, &ev);
    (void)ClearEvent(ev);
    if(ev & BrsEvCyclicAlarm_1ms)
    {
      /* 1ms event detected, call the ms handler */
      BrsMainCyclic1ms();
    }
  }
}
 
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |void |- |No return value; task runs in an infinite loop |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |brsMain_Cyclic_Callbacks |brsMain_Cyclic_Callbacks_Background |Structure containing background task callbacks to be executed |
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
 * |uint8 |cycliccounter |Loop counter for iterating through background callback functions |
 * @brief AUTOSAR OS task that executes registered background callbacks in a continuous loop
 * @note This task runs at the lowest priority level and executes all functions registered with
 *       BRSMAIN_CYCLETIME_BACKGROUND through BrsMainRegisterCyclic().
 */
/* author Vector Informatik GmbH */
/* date 2022 */
/************************************************************************************************/
TASK(BrsMainBackgroundTask)
{
  uint8 cycliccounter;
 
#if defined (BRSMAIN_BRSMAINBACKGROUNDTASK_CALLOUT)
  BrsTestsuite_BrsMain_BrsMainBackgroundTask();
#endif
 
  for(;;)
  {
# if defined (_MICROSOFT_C_VTT_)
    CANoeAPI_ConsumeTicks(100);
# endif
 
    for (cycliccounter=0u; cycliccounter<brsMain_Cyclic_Callbacks_Background.FunctionCounter; cycliccounter++)
    {
      brsMain_Cyclic_Callbacks_Background.FunctionPointer[cycliccounter]();
    }
 
    (void)Schedule();
  }
}
# endif /*!BRS_ENABLE_FBL_SUPPORT&&!BRS_ENABLE_OS_INTERRUPT_ONLY*/
#endif /*BRS_ENABLE_1MS_HANDLER*/
 
 
#if defined (BRS_ENABLE_SUPPORT_LEDS)          || \
    defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN) || \
    defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
# if !defined (BRS_ENABLE_PORT)
  #define BRSHW_PORT_LOGIC_HIGH STD_HIGH
  #define BRSHW_PORT_LOGIC_LOW STD_LOW
# endif
# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_START_SEC_RAM_CODE
  #include "Brs_MemMap.h"
# endif
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |brsMain_TogglePin |Pin |Enumeration value specifying which pin to toggle (LED, WD, or CUSTOM) |
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
 * |uint8 |BRSHW_PORT_LOGIC_HIGH |Constant defining the logical high state value |
 * |uint8 |BRSHW_PORT_LOGIC_LOW |Constant defining the logical low state value |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8 |BrsMain_ToggleSwitch_LED |Counter for LED pin toggling state, incremented with each call |
 * |uint8 |BrsMain_ToggleSwitch_WD |Counter for watchdog pin toggling state, incremented with each call |
 * |uint8 |BrsMain_ToggleSwitch_CUSTOM |Counter for custom pin toggling state, incremented with each call |
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
 * @brief Function to toggle the state of a specified GPIO pin as a visual indicator or watchdog trigger
 * @note This function toggles the specified GPIO pin between high and low states with each call.
 */
/* author Vector Informatik GmbH */
/* date 2022 */
/************************************************************************************************/
void BrsMainTogglePin(brsMain_TogglePin Pin)
{
  #define START_SEC_VAR_NOINIT_UNSPECIFIED
  #include "MemMap.h"
#if defined (BRS_ENABLE_SUPPORT_LEDS)
  static uint8 BrsMain_ToggleSwitch_LED = BRSHW_PORT_LOGIC_HIGH;
#endif
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN)
  static uint8 BrsMain_ToggleSwitch_WD = BRSHW_PORT_LOGIC_HIGH;
#endif
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
  static uint8 BrsMain_ToggleSwitch_CUSTOM = BRSHW_PORT_LOGIC_HIGH;
#endif
  #define STOP_SEC_VAR
  #include "MemMap.h"
 
  switch (Pin)
  {
#if defined (BRS_ENABLE_SUPPORT_LEDS)
    case BRSMAIN_TOGGLEPIN_LED:
# if defined (BRS_ENABLE_PORT)
      BrsHwPort_SetLevel(BRSHW_PORT_LED, BrsMain_ToggleSwitch_LED & 0x01);
# else
      Dio_WriteChannel(BrsHw_DioChannel_ToggleLED, BrsMain_ToggleSwitch_LED & 0x01);
# endif
      BrsMain_ToggleSwitch_LED++;
      break;
#endif /*BRS_ENABLE_SUPPORT_LEDS*/
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN)
    case BRSMAIN_TOGGLEPIN_WD:
# if defined (BRS_ENABLE_PORT)
      BrsHwPort_SetLevel(BRSHW_PORT_TOGGLE_WD, BrsMain_ToggleSwitch_WD & 0x01);
# else
      Dio_WriteChannel(BrsHw_DioChannel_ToggleWdPin, BrsMain_ToggleSwitch_WD & 0x01);
# endif
      BrsMain_ToggleSwitch_WD++;
      break;
#endif /*BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN*/
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
    case BRSMAIN_TOGGLEPIN_CUSTOM:
# if defined (BRS_ENABLE_PORT)
      BrsHwPort_SetLevel(BRSHW_PORT_TOGGLE_CUSTOM, BrsMain_ToggleSwitch_CUSTOM & 0x01);
# else
      Dio_WriteChannel(BrsHw_DioChannel_ToggleCustomPin, BrsMain_ToggleSwitch_CUSTOM & 0x01);
# endif
      BrsMain_ToggleSwitch_CUSTOM++;
      break;
#endif /*BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN*/
    default:
      BrsMainExceptionHandler(kBrsIllegalParameter, BRSERROR_MODULE_BRSHW, (uint16)(__LINE__));
      break;
  }
}
# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_STOP_SEC_RAM_CODE
  #include "Brs_MemMap.h"
# endif
#endif /*BRS_ENABLE_SUPPORT_LEDS||BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN||BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN*/
 
#if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_START_SEC_RAM_CODE
  #include "Brs_MemMap.h"
#endif
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8 |ErrorCode |Caller-specific error code identifying the type of assertion failure |
 * |uint8 |ModuleCode |Identifier of the module where the assertion failed (CI constant) |
 * |uint16 |LineNumber |Source code line number where the assertion failed or function was called |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |void |- |Function does not return under normal circumstances (infinite loop) |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint16 |BRSMAIN_ERRORBUFFERSIZE |Size of buffer for error message formatting in VTT mode |
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
 * |volatile uint8 |BrsMain_Continue |Debug control variable that can be set to 1 to exit the infinite loop |
 * |char[] |error |Buffer for formatted error message in VTT mode |
 * @brief Central exception handler for fatal error conditions in the BRS system
 * @note This function serves as the central exception handler for the entire BRS system.
 */
/* author Vector Informatik GmbH */
/* date 2022 */
/************************************************************************************************/
void BrsMainExceptionHandler(uint8 ErrorCode, uint8 ModuleCode, uint16 LineNumber)
{
#if defined (BRSMAIN_BRSMAINEXCEPTIONHANDLER_CALLOUT)
  BrsTestsuite_BrsMain_BrsMainExceptionHandler();
#endif
 
#if defined (BRS_ENABLE_SAFECTXSUPPORT)
  while(1)
  {}
 
#else
# if defined (_MICROSOFT_C_VTT_)
  char error[BRSMAIN_ERRORBUFFERSIZE];
 
  sprintf_s(error, BRSMAIN_ERRORBUFFERSIZE, "BrsMainExceptionHandler Code: [0x%x] ModuleCode: [0x%x] LineNumber: [0x%x]", ErrorCode, ModuleCode, LineNumber);
 
  CANoeAPI_WriteString(error);
  ShutdownOS(0);
 
# else
  volatile uint8 BrsMain_Continue;
  BrsMain_Continue = 0u;
 
#if !defined (BRS_ENABLE_FBL_SUPPORT) /* FBL is always running in polling mode with interrupts disabled */
  DisableAllInterrupts();
#endif
 
  while (BrsMain_Continue == 0u)
  {
    /* Set BrsMain_Continue to 1 to continue here.
     *  If the debugger is not able to show the stack properly, this mechanism can be used to find the
     *  source of the exception. */
  }
# endif
#endif
}
#if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_STOP_SEC_RAM_CODE
  #include "Brs_MemMap.h"
#endif
 
#if !defined (_MICROSOFT_C_VTT_)
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |brsMain_ResetReasonType |resetReason |Type of reset that occurred (software reset or other reset) |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |brsMain_ResetReasonType |brsMain_ResetReason |Global variable storing the reset reason determined at startup |
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
 * @brief Retrieves the reason for the last system reset
 * @note This function is a wrapper around the previously existing BrsHwGetResetReason functionality.
 */
/* author Vector Informatik GmbH */
/* date 2022 */
/************************************************************************************************/
brsMain_ResetReasonType BrsMainGetResetReason(void)
{
  return brsMain_ResetReason;
}
#endif /*_MICROSOFT_C_VTT_*/
 
#if defined (BRS_ENABLE_OS_INTERRUPT_ONLY)
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
 * |uint32 |brsMain_SuspendAllCounter |Counter tracking nested calls to suspend interrupts |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |brsMain_SuspendAllCounter |Incremented to track nesting level of interrupt suspension |
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
 * @brief Wrapper function for SuspendAllInterrupts in OS Interrupt-Only mode
 * @note This function provides a replacement for the standard SuspendAllInterrupts() API
 */
/* author Vector Informatik GmbH */
/* date 2022 */
/************************************************************************************************/
void BrsMainSuspendAllInterrupts(void)
{
  if (brsMain_SuspendAllCounter==0u)
  {
    DisableAllInterrupts();
  }
 
  brsMain_SuspendAllCounter++;
}
 
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
 * |uint32 |brsMain_SuspendAllCounter |Counter tracking nested calls to suspend interrupts |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |brsMain_SuspendAllCounter |Decremented to track nesting level of interrupt suspension |
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
 * @brief Wrapper function for ResumeAllInterrupts in OS Interrupt-Only mode
 * @note This function provides a replacement for the standard ResumeAllInterrupts() API
 */
/* author Vector Informatik GmbH */
/* date 2022 */
/************************************************************************************************/
void BrsMainResumeAllInterrupts(void)
{
  if (brsMain_SuspendAllCounter!=0u)
  {
    brsMain_SuspendAllCounter--;
 
    if (brsMain_SuspendAllCounter==0u)
    {
      EnableAllInterrupts();
    }
  }
}
#endif
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |int |returnValue |Always returns 0, though function should never return in normal operation |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |BrsMain_CoreConfig_Size |Size of the core configuration array |
 * |struct |BrsMain_CoreConfig[] |Array containing core-specific configuration data |
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
 * |uint32 |coreID |ID of the current processor core (in multi-core configurations) |
 * |uint32 |i |Loop counter for searching through core configuration array |
 * @brief Main entry point of the BRS system
 * @note This function is the central entry point of the Basic Runtime System, called by the
 *       startup code.
 */
/* author Vector Informatik GmbH */
/* date 2022 */
/************************************************************************************************/
int main(void)
{
#if !defined (_MICROSOFT_C_VTT_)
# if (BRS_CPU_CORE_AMOUNT>1) || (BRSHW_SOURCECODE_TEMPLATE_VERSION >= 0x0103u)
  uint32 coreID = BrsHw_GetCore();
# endif
# if (BRSHW_SOURCECODE_TEMPLATE_VERSION >= 0x0103u) && ((!defined (BRS_ENABLE_FBL_SUPPORT)) || (defined (BRS_FBL_EXCEPTIONTABLE_IN_RAM)))
  uint32 i;
# endif
#endif
 
#if defined (BRSMAIN_MAIN_CALLOUT)
  BrsTestsuite_BrsMain_main();
#endif
 
#if !defined (_MICROSOFT_C_VTT_)
  BrsHwDisableInterruptAtPowerOn();
 
# if (BRSHW_SOURCECODE_TEMPLATE_VERSION >= 0x0103u)
#  if (!defined (BRS_ENABLE_FBL_SUPPORT)) || (defined (BRS_FBL_EXCEPTIONTABLE_IN_RAM))
  /* For FBL UseCase, only needed, if functionality to activate the additional ExceptionTable
     in RAM is enabled (vBRSGeneral/vBRSFblSupportExceptionTableInRam) */
 
  /* Search for valid Exception- and Interrupt Table in BrsMain_CoreConfig[]
     (vBRS generated into vBrs_Lcfg.c) */
  for (i=0u; i<BrsMain_CoreConfig_Size; i++)
  {
    if (BrsMain_CoreConfig[i].PhysicalCoreId == coreID)
    {
      BrsHw_ExceptionTable_Init(BrsMain_CoreConfig[i].ExcVecLabel, BrsMain_CoreConfig[i].IntVecLabel);
      i=BrsMain_CoreConfig_Size+1u;
    }
  }
 
  /* Check, if no valid core config was found */
  if (i==BrsMain_CoreConfig_Size)
    BrsMainExceptionHandler(kBrsInvalidCoreConfig, BRSERROR_MODULE_BRSMAIN, (uint16)(__LINE__));
#  endif
# endif /*BRSHW_SOURCECODE_TEMPLATE_VERSION>=0x0103u*/
 
# if (BRS_CPU_CORE_AMOUNT>1)
  if (coreID == BRSHW_INIT_CORE_ID)
# endif
#endif
  {
    // BrsMainInit();
    __enable_irq();
    SystemInit();
    /* Init Memory Protection for MPU, SMPU and PPU */
    CoreIso_Init();
  }
 
#if defined (BRS_FBL_NO_ECUMINIT)
  // FblMain();
 
#else
# if (!defined (BRS_ENABLE_FBL_SUPPORT)) || (defined (_MICROSOFT_C_VTT_))
#  if defined (BRS_ENABLE_OS_INTERRUPT_ONLY)
  /* OS is configured for UseCase Interrupt Only (/MICROSAR/Os/OsOS/OsUseCase) */
  Os_InitInterruptOnly();
#  else
  Os_InitMemory();
  Os_Init();
#  endif
# endif
# if (JUMP_TO_FBL_ENABLE == STD_ON)
  TransitionToFBL();
# endif
# if defined (BRS_ENABLE_HSM_SUPPORT)
  vHsm_Init();
# else
  EcuM_Init(); /* never returns */
# endif
#endif /*else BRS_FBL_NO_ECUMINIT*/
 
  BrsMainExceptionHandler(kBrsIllegalReturnFromMain, BRSERROR_MODULE_BRSMAIN, (uint16)(__LINE__));
 
  return 0;
}
 
/***********************************************************************************************************************
 *  Additional UserCode can be placed here
 **********************************************************************************************************************/
 
 
 