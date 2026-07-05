/**
 * @file Os_Callout_Stubs.c
 * @brief Public header: Os.h (This module provided by Nippon Seiki should be left unchanged by FPT.)
 * @details Overview: Implementation of OSEK/VDX OS hook functions for the HSM module.
 */

/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *            Module: Os
 *           Program: HSM_Vector_SLP1
 *          Customer: Nippon Seiki Co., Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: CYT4BFCCJDQ0BZEGS
 *    License Scope : The usage is restricted to CBD2300020_D00
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Os_Callout_Stubs.c
 *   Generation Time: 2024-03-21 16:36:46
 *           Project: vHsmConfig - Version 1.0
 *          Delivery: CBD2300020_D00
 *      Tool Version: DaVinci Configurator Classic 5.26.35 SP2
 *
 *
 *********************************************************************************************************************/

#define OS_CALLOUT_STUBS_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Os.h"

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK OS_Callout_Stubs_Include>
 *********************************************************************************************************************/
#include "EcuM.h"
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

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
 * @brief OSEK/VDX OS startup hook function
 * @note This function is called by the operating system during the startup phase before
 *       any application task is started. It allows for application-specific initialization
 *       that must be performed in a specific timing relative to the OS initialization.
 *       The current implementation is empty, as initialization is handled elsewhere.
 */
/* author Vector Informatik GmbH */
/* date 2024 */
/************************************************************************************************/
#if OS_CFG_STARTUPHOOK_SYSTEM == STD_ON
# define OS_START_SEC_STARTUPHOOK_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

FUNC(void, OS_STARTUPHOOK_CODE) StartupHook(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK OS_Callout_Stubs_StartupHook>
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>
 *********************************************************************************************************************/

}

# define OS_STOP_SEC_STARTUPHOOK_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif /* OS_CFG_STARTUPHOOK_SYSTEM */


/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |StatusType |Fatalerror |Error code indicating the reason for OS shutdown |
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
 * @brief OSEK/VDX OS shutdown hook function
 * @note This function is called by the operating system when it is about to shut down due
 *       to a fatal error. It allows for application-specific cleanup actions before system
 *       shutdown. In this implementation, it calls EcuM_Shutdown() to perform a controlled
 *       shutdown of the ECU, regardless of the specific error that triggered the OS shutdown.
 */
/* author Vector Informatik GmbH */
/* date 2024 */
/************************************************************************************************/
#if OS_CFG_SHUTDOWNHOOK_SYSTEM == STD_ON
# define OS_START_SEC_SHUTDOWNHOOK_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

FUNC(void, OS_SHUTDOWNHOOK_CODE) ShutdownHook(StatusType Fatalerror)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK OS_Callout_Stubs_ShutdownHook>
 *********************************************************************************************************************/
  EcuM_Shutdown();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>
 *********************************************************************************************************************/

}

# define OS_STOP_SEC_SHUTDOWNHOOK_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif /* OS_CFG_SHUTDOWNHOOK_SYSTEM */


/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |StatusType |Error |Error code indicating the type of OS error detected |
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
 * |Os_ErrorInformationType |CurrentError |Structure containing detailed information about the OS error |
 * |uint8 |endless |Control variable for the error handling loop (1 = continue, 0 = exit) |
 * @brief OSEK/VDX OS error hook function
 * @note This function is called by the operating system when an error is detected during
 *       API execution. It retrieves detailed error information using Os_GetDetailedError()
 *       and enters an infinite loop for most error types, effectively halting the system.
 *       
 *       The function only allows execution to continue if the specific error is an overload
 *       condition (OS_STATUS_OVERLOAD), which might be recoverable. For all other errors,
 *       the system will remain in the loop, requiring a reset to recover.
 *       
 *       This implementation provides a simple error handling strategy focused on fail-stop
 *       behavior for critical errors.
 */
/* author Vector Informatik GmbH */
/* date 2024 */
/************************************************************************************************/
#if OS_CFG_ERRORHOOK_SYSTEM == STD_ON
# define OS_START_SEC_ERRORHOOK_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

FUNC(void, OS_ERRORHOOK_CODE) ErrorHook(StatusType Error)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK OS_Callout_Stubs_ErrorHook>
 *********************************************************************************************************************/
  Os_ErrorInformationType CurrentError;
  volatile uint8 endless = 1u;
  (void)Os_GetDetailedError(&CurrentError);
  while(endless == TRUE)
  {
    if(CurrentError.DetailedError == OS_STATUS_OVERLOAD)
    {
      break;
    }
  }
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>
 *********************************************************************************************************************/

}

# define OS_STOP_SEC_ERRORHOOK_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif /* OS_CFG_ERRORHOOK_SYSTEM */


/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |StatusType |Fatalerror |Error code indicating the type of protection violation |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |ProtectionReturnType |result |PRO_SHUTDOWN to request system shutdown |
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
 * @brief OSEK/VDX OS protection hook function
 * @note This function is called by the operating system when a protection violation is detected
 *       (such as memory access violations, execution timing violations, or stack overflows).
 *       
 *       The implementation always returns PRO_SHUTDOWN, instructing the OS to shut down the
 *       system in response to any protection violation. This conservative approach ensures
 *       that the system does not continue execution when protection boundaries have been
 *       breached, which could lead to unpredictable behavior.
 *       
 *       Alternative return values not used here include:
 *       - PRO_IGNORE: Continue execution (potentially unsafe)
 *       - PRO_KILLTASKISR: Kill only the offending task/ISR
 *       - PRO_KILLAPPL_RESTART: Kill the application and restart it
 */
/* author Vector Informatik GmbH */
/* date 2024 */
/************************************************************************************************/
#if OS_CFG_PROTECTIONHOOK_SYSTEM == STD_ON
# define OS_START_SEC_PROTECTIONHOOK_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

FUNC(ProtectionReturnType, OS_PROTECTIONHOOK_CODE) ProtectionHook(StatusType Fatalerror)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK OS_Callout_Stubs_ProtectionHook>
 *********************************************************************************************************************/
  return PRO_SHUTDOWN;
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>
 *********************************************************************************************************************/

}

# define OS_STOP_SEC_PROTECTIONHOOK_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif /* OS_CFG_PROTECTIONHOOK_SYSTEM */


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
 * @brief OSEK/VDX OS pre-task hook function
 * @note This function is called by the operating system before a task is started or resumed.
 *       It allows for task-specific setup operations to be performed before task execution.
 *       
 *       The current implementation is empty, as no pre-task operations are required in this
 *       application. This hook can be used for operations such as:
 *       - Setting up task-specific monitoring
 *       - Resource accounting
 *       - Task execution timing measurement
 *       - Debug tracing
 */
/* author Vector Informatik GmbH */
/* date 2024 */
/************************************************************************************************/
#if OS_CFG_PRETASKHOOK == STD_ON
# define OS_START_SEC_PRETASKHOOK_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

FUNC(void, OS_PRETASKHOOK_CODE) PreTaskHook(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK OS_Callout_Stubs_PreTaskHook>
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>
 *********************************************************************************************************************/

}

# define OS_STOP_SEC_PRETASKHOOK_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif /* OS_CFG_PRETASKHOOK */


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
 * @brief OSEK/VDX OS post-task hook function
 * @note This function is called by the operating system after a task has completed execution
 *       or been preempted. It allows for task-specific cleanup operations to be performed
 *       after task execution.
 *       
 *       The current implementation is empty, as no post-task operations are required in this
 *       application. This hook can be used for operations such as:
 *       - Cleanup of task-specific resources
 *       - Logging task execution statistics
 *       - Memory leak detection
 *       - Performance monitoring
 */
/* author Vector Informatik GmbH */
/* date 2024 */
/************************************************************************************************/
#if OS_CFG_POSTTASKHOOK == STD_ON
# define OS_START_SEC_POSTTASKHOOK_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

FUNC(void, OS_POSTTASKHOOK_CODE) PostTaskHook(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK OS_Callout_Stubs_PostTaskHook>
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>
 *********************************************************************************************************************/

}

# define OS_STOP_SEC_POSTTASKHOOK_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif /* OS_CFG_POSTTASKHOOK */


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
 * @brief OS panic hook function
 * @note This function is called by the operating system when an unrecoverable internal error
 *       is detected that prevents further operation. Unlike the ErrorHook which handles API
 *       errors, this hook is triggered by critical system-level failures.
 *       
 *       The current implementation is empty, as the system defaults to a hardware reset in
 *       panic situations. In a more sophisticated implementation, this hook could:
 *       - Log critical diagnostic information before reset
 *       - Store crash dumps to non-volatile memory
 *       - Trigger external watchdog or supervisory circuits
 *       - Attempt to put the system into a safe state before shutdown
 */
/* author Vector Informatik GmbH */
/* date 2024 */
/************************************************************************************************/
#if OS_CFG_PANICHOOK == STD_ON
# define OS_START_SEC_PANICHOOK_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

FUNC(void, OS_PANICHOOK_CODE) Os_PanicHook(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK OS_Callout_Stubs_PanicHook>
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>
 *********************************************************************************************************************/

}

# define OS_STOP_SEC_PANICHOOK_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif /* OS_CFG_PANICHOOK */



/* Unrecognized User Blocks */
#if 0
#endif


/**********************************************************************************************************************
 *  END OF FILE: Os_Callout_Stubs.c
 *********************************************************************************************************************/
