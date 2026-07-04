/**
 * @file BrsMainStartup.c
 * @brief Public header: BrsMain.h
 * @details Overview: Vector Basic Runtime System module providing startup routines and memory initialization functionality
 */
 
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
/** \file  File:  BrsMainStartup.c
 *      Project:  Vector Basic Runtime System
 *       Module:  BrsMain
 *
 *  \brief Description:  Vector Basic Runtime System module source for startup routines.
 *
 *  \attention Please note:
 *    The demo and example programs only show special aspects of the software. With regard to the fact
 *    that these programs are meant for demonstration purposes only, Vector Informatik liability shall be
 *    expressly excluded in cases of ordinary negligence, to the extent admissible by law or statute.
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to BrsMain.h.
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
/** @cond INTERNAL */
#define _BRSMAINSTARTUP_C_
/** @endcond */
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "BrsMain.h"
 
#include "vLinkGen_Lcfg.h"
 
/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
#if (BRSMAIN_VERSION != 0x0210u)
  #error "Header and source file are inconsistent!"
#endif
#if (BRSMAIN_BUGFIX_VERSION != 0x01u)
  #error "Different versions of bugfix in Header and Source used!"
#endif
 
/**********************************************************************************************************************
 *  CONFIGURATION CHECK
 *********************************************************************************************************************/
#if (!defined (BRS_INIT_PATTERN_BLOCKS))           || \
    (!defined (BRS_INIT_PATTERN_HARDRESET_BLOCKS)) || \
    (!defined (BRS_INIT_PATTERN_AREAS))            || \
    (!defined (BRS_INIT_PATTERN_HARDRESET_AREAS))
  #error "Your environment is missing the mandatory init pattern. They should be generated out of vBRS in Configurator5."
#endif
 
#if (VLINKGEN_CFG_MAJOR_VERSION != 2u)
  #error "This StartUpCode is dependent to the vLinkGen version! vLinkGen major version does not fit!"
#else
# if (VLINKGEN_CFG_MINOR_VERSION < 4u)
  #error "This StartUpCode is dependent to the vLinkGen version! Your vLinkGen minor version is too old!"
# endif
#endif
 
#if defined (BRS_ENABLE_OS_MULTICORESUPPORT)
  #error "This file was filtered for SingleCore UseCase, but MultiCore UseCase is configured!"
#endif
 
/**********************************************************************************************************************
 *  DEFINITION + MACROS
 *********************************************************************************************************************/
 
/**
 * @def BrsHwGetResetReasonStartup
 * @value BrsHwGetResetReason()
 * @resolution
 * @brief Wrapper for compatibility with older platforms not yet using the Template 1.03 API
 */
#if (BRSHW_SOURCECODE_TEMPLATE_VERSION < 0x0103u)
  /* Wrapper for platforms, not yet transferred into Brs_Template 1.03 */
  #define BrsHwGetResetReasonStartup() BrsHwGetResetReason()
  #define brsMain_ResetReasonType brsHw_ResetReasonType
  #define BRSMAIN_RESET_SW BRSHW_RESET_SW
#endif
 
/**********************************************************************************************************************
 *  GLOBAL VARIABLES
 *********************************************************************************************************************/
/** @cond INTERNAL */
#if (BRSHW_SOURCECODE_TEMPLATE_VERSION >= 0x0103u)
  #define BRS_START_SEC_SHARED_VAR
  #include "Brs_MemMap.h"
#endif
/** @endcond */
/**
 * @type brsMain_ResetReasonType
 * @var brsMain_ResetReason
 * @brief Global variable that stores the reason for the last system reset
 * @unit -
 * @scope Global variable
 * @section -
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |- |- |- |- |- |
 */
volatile brsMain_ResetReasonType brsMain_ResetReason;
/** @cond INTERNAL */
#if (BRSHW_SOURCECODE_TEMPLATE_VERSION >= 0x0103u)
  #define BRS_STOP_SEC_SHARED_VAR
  #include "Brs_MemMap.h"
#endif
/** @endcond */
/**********************************************************************************************************************
 *  GLOBAL CONST VARIABLES
 *********************************************************************************************************************/
 
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
static void Brs_MemoryZeroInit(const vLinkGen_MemAreaSet *memAreaSet, uint32 InitPattern, uint32 coreId);
static void Brs_MemoryInit(const vLinkGen_RamMemAreaSet *memAreasSet, uint32 coreId);
 
/**********************************************************************************************************************
 *  FUNCTION DEFINITIONS
 *********************************************************************************************************************/
  /* This code is only needed for the first instance in the system */
/** @cond INTERNAL */
# if (BRSHW_SOURCECODE_TEMPLATE_VERSION >= 0x0103u)
  #define BRS_START_SEC_STARTUP_CODE
  #include "Brs_MemMap.h"
# endif
/** @endcond */
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
 * |brsMain_ResetReasonType |brsMain_ResetReason |Stores the reset reason determined by BrsHwGetResetReasonStartup() |
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
 * @brief Unified pre-main startup routine called by the assembler startup code
 * @note This function is the entry point for system initialization before main() is called.
 */
/* author Vector Informatik GmbH */
/* date 2022 */
/************************************************************************************************/
void Brs_PreMainStartup(void)
{
#if defined (BRSHW_EARLYINIT_AVAILABLE)
  BrsHwEarlyInitPowerOn();
#endif
 
  brsMain_ResetReason = BrsHwGetResetReasonStartup();
 
  Brs_ApplicationEntry();
 
  BrsMainExceptionStartup(); /* Illegal return from main */
}
/** @cond INTERNAL */
# if (BRSHW_SOURCECODE_TEMPLATE_VERSION >= 0x0103u)
  #define BRS_STOP_SEC_STARTUP_CODE
  #include "Brs_MemMap.h"
# endif
/** @endcond */
 
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
 * |brsMain_ResetReasonType |brsMain_ResetReason |Used to determine if memory areas should be initialized (not for software reset) |
 * |vLinkGen_MemAreaSet |vLinkGen_ZeroInit_*_BlocksSet |Memory block sets for zero initialization at different stages |
 * |vLinkGen_MemAreaSet |vLinkGen_ZeroInit_*_GroupsSet |Memory group sets for zero initialization at different stages |
 * |vLinkGen_RamMemAreaSet |vLinkGen_Init_*_GroupsSet |Memory group sets for initialization at different stages |
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
 * |uint32 |coreID |Identifier of the current processor core for multi-core support |
 * @brief Unified application entry point that performs staged memory initialization
 * @note This function is the central application entry point called by Brs_PreMainStartup().
 */
/* author Vector Informatik GmbH */
/* date 2022 */
/************************************************************************************************/
void Brs_ApplicationEntry(void)
{
  uint32 coreID;
 
  coreID = BrsHw_GetCore();
 
  BrsMain_MemoryInit_StageZero_Hook(coreID);
 
#if (VLINKGEN_CFG_NUM_ZERO_INIT_ZERO_GROUPS>1uL)
  /* vLinkGen_ZeroInit_Zero_GroupsSet contains vLinkGen VarSectionGroups, configured with Init Policy "ZERO_INIT" and Init Stage "ZERO" */
  Brs_MemoryZeroInit(&vLinkGen_ZeroInit_Zero_GroupsSet, BRS_INIT_PATTERN_AREAS, coreID);
#endif
 
#if (VLINKGEN_CFG_NUM_INIT_ZERO_GROUPS>1uL)
  /* vLinkGen_Init_Zero_GroupsSet contains vLinkGen VarSectionGroups, configured with Init Policy "INIT" and Init Stage "ZERO" */
  Brs_MemoryInit(&vLinkGen_Init_Zero_GroupsSet, coreID);
#endif
 
  BrsMain_MemoryInit_StageHardReset_Hook(coreID);
 
#if (VLINKGEN_CFG_NUM_ZERO_INIT_HARD_RESET_BLOCKS>1uL)
  if (brsMain_ResetReason != BRSMAIN_RESET_SW)
  {
    /* vLinkGen_ZeroInit_HardReset_BlocksSet contains vLinkGen memory region blocks, configured with Init Stage "HARD_RESET_ONLY" */
    Brs_MemoryZeroInit(&vLinkGen_ZeroInit_HardReset_BlocksSet, BRS_INIT_PATTERN_HARDRESET_BLOCKS, coreID);
  }
#endif
 
#if (VLINKGEN_CFG_NUM_ZERO_INIT_HARD_RESET_GROUPS>1uL)
  if (brsMain_ResetReason != BRSMAIN_RESET_SW)
  {
    /* vLinkGen_ZeroInit_HardReset_GroupsSet contains vLinkGen VarSectionGroups, configured with Init Policy "ZERO_INIT" and Init Stage "HARD_RESET_ONLY" */
    Brs_MemoryZeroInit(&vLinkGen_ZeroInit_HardReset_GroupsSet, BRS_INIT_PATTERN_HARDRESET_AREAS, coreID);
  }
#endif
 
#if (VLINKGEN_CFG_NUM_INIT_HARD_RESET_GROUPS>1uL)
  if (brsMain_ResetReason != BRSMAIN_RESET_SW)
  {
    /* vLinkGen_Init_HardReset_GroupsSet contains vLinkGen VarSectionGroups, configured with Init Policy "INIT" and Init Stage "HARD_RESET_ONLY" */
    Brs_MemoryInit(&vLinkGen_Init_HardReset_GroupsSet, coreID);
  }
#endif
 
  BrsMain_MemoryInit_StageOne_Hook(coreID);
 
#if (VLINKGEN_CFG_NUM_ZERO_INIT_ONE_BLOCKS>1uL)
  /* vLinkGen_ZeroInit_One_BlocksSet contains vLinkGen memory region blocks, configured with Init Stage "ONE" */
  /* QAC Deviations: (No 1279) This macro define for register access and provided by Vector. So, this warning can ignore and doesn't affect to the current behavior*/
  Brs_MemoryZeroInit(&vLinkGen_ZeroInit_One_BlocksSet, BRS_INIT_PATTERN_BLOCKS, coreID);
#endif
 
#if (VLINKGEN_CFG_NUM_ZERO_INIT_ONE_GROUPS>1uL)
  /* vLinkGen_ZeroInit_One_GroupsSet contains vLinkGen VarSectionGroups, configured with Init Policy "ZERO_INIT" and Init Stage "ONE" */
  /* QAC Deviations: (No 1279) This macro define for register access and provided by Vector. So, this warning can ignore and doesn't affect to the current behavior*/
  Brs_MemoryZeroInit(&vLinkGen_ZeroInit_One_GroupsSet, BRS_INIT_PATTERN_AREAS, coreID);
#endif
 
#if (VLINKGEN_CFG_NUM_INIT_ONE_GROUPS>1uL)
  /* vLinkGen_Init_One_GroupsSet contains vLinkGen VarSectionGroups, configured with Init Policy "INIT" and Init Stage "ONE" */
  Brs_MemoryInit(&vLinkGen_Init_One_GroupsSet, coreID);
#endif
 
  BrsMain_MemoryInit_StageTwo_Hook(coreID);
 
#if (VLINKGEN_CFG_NUM_ZERO_INIT_TWO_GROUPS>1uL)
  /* vLinkGen_ZeroInit_Two_GroupsSet contains vLinkGen VarSectionGroups, configured with Init Policy "ZERO_INIT" and Init Stage "TWO" */
  Brs_MemoryZeroInit(&vLinkGen_ZeroInit_Two_GroupsSet, BRS_INIT_PATTERN_AREAS, coreID);
#endif
 
#if (VLINKGEN_CFG_NUM_INIT_TWO_GROUPS>1uL)
  /* vLinkGen_Init_Two_GroupsSet contains vLinkGen VarSectionGroups, configured with Init Policy "INIT" and Init Stage "TWO" */
  Brs_MemoryInit(&vLinkGen_Init_Two_GroupsSet, coreID);
#endif
 
  BrsMain_MemoryInit_StageThree_Hook(coreID);
 
#if (VLINKGEN_CFG_NUM_ZERO_INIT_THREE_GROUPS>1uL)
  /* vLinkGen_ZeroInit_Three_GroupsSet contains vLinkGen VarSectionGroups, configured with Init Policy "ZERO_INIT" and Init Stage "THREE" */
  Brs_MemoryZeroInit(&vLinkGen_ZeroInit_Three_GroupsSet, BRS_INIT_PATTERN_AREAS, coreID);
#endif
 
#if (VLINKGEN_CFG_NUM_INIT_THREE_GROUPS>1uL)
  /* vLinkGen_Init_Three_GroupsSet contains vLinkGen VarSectionGroups, configured with Init Policy "INIT" and Init Stage "THREE" */
  Brs_MemoryInit(&vLinkGen_Init_Three_GroupsSet, coreID);
#endif
 
  BrsMain_PreMainHook(coreID);
 
  (void)main();
 
  BrsMainExceptionHandler(kBrsIllegalReturnFromMain, BRSERROR_MODULE_BRSMAIN, (uint16)(__LINE__));
}
 
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |const vLinkGen_MemAreaSet* |memAreaSet |Pointer to structure array containing memory areas to be initialized |
 * |uint32 |InitPattern |Value pattern to be written to memory (typically 0 or other specified pattern) |
 * |uint32 |coreId |ID of the current CPU core in multi-core systems |
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
 * |uint32 |i |Loop counter for iterating through the memory areas array |
 * |volatile uint32* |memPtr |Pointer to the current memory location being initialized (when assembly function not used) |
 * @brief Generic routine for initializing RAM areas to a specified pattern (typically zero)
 * @note This function performs zero-initialization of RAM memory areas as specified by the vLinkGen
 *       configuration.
 */
/* author Vector Informatik GmbH */
/* date 2022 */
/************************************************************************************************/
static void Brs_MemoryZeroInit(const vLinkGen_MemAreaSet *memAreaSet, uint32 InitPattern, uint32 coreId)
{
  uint32 i;
#if !defined (BRSHW_ASM_MEMORY_ZERO_INIT_LOOP_AVAILABLE)
  volatile uint32 *memPtr;
#endif
 
  for (i=0u; i<memAreaSet->Num; i++) /* QAC Deviations: (No 2824) The memAreaSet pointer pointer already points to a hardware address right in this function. */
  {
    if ((memAreaSet->Areas[i].Core==coreId) && ((memAreaSet->Areas[i].End - memAreaSet->Areas[i].Start) > 0U)) /* QAC Deviations: (No 2824) The memAreaSet pointer pointer already points to a hardware address right in this function. */
    {
#if defined (BRSHW_ASM_MEMORY_ZERO_INIT_LOOP_AVAILABLE)
      BrsHw_AsmMemoryZeroInitLoop(memAreaSet->Areas[i].Start, memAreaSet->Areas[i].End, InitPattern);
 
#else
      memPtr = (volatile uint32*)memAreaSet->Areas[i].Start;
      while ((uint32)memPtr < memAreaSet->Areas[i].End)
      {
        *memPtr = InitPattern; /* QAC Deviations: (No 2814) The memPtr pointer already points to a hardware address right in this function. */
        memPtr++; /* QAC Deviations: (No 2824) The memPtr pointer pointer already points to a hardware address right in this function. */
      }
#endif /*else BRSHW_ASM_MEMORY_ZERO_INIT_LOOP_AVAILABLE*/
    }
  }
}
 
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |const vLinkGen_RamMemAreaSet* |memAreasSet |Pointer to structure array containing RAM memory areas to be initialized from ROM |
 * |uint32 |coreId |ID of the current CPU core in multi-core systems |
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
 * |uint32 |i |Loop counter for iterating through the memory areas array |
 * |volatile uint32* |memPtr |Pointer to the current RAM memory location being initialized |
 * |volatile uint32* |romPtr |Pointer to the current ROM memory location containing initialization data |
 * @brief Generic routine for copying initialized data from ROM to RAM
 * @note This function copies initialized data from ROM to RAM for memory areas that require specific
 *       initial values.
 */
/* author Vector Informatik GmbH */
/* date 2022 */
/************************************************************************************************/
static void Brs_MemoryInit(const vLinkGen_RamMemAreaSet *memAreasSet, uint32 coreId)
{
  volatile uint32 *memPtr;
  volatile uint32 *romPtr;
  uint32 i;
 
  for (i=0u; i<memAreasSet->Num; i++) /* QAC Deviations: (No 2824) The memAreaSet pointer pointer already points to a hardware address right in this function. */
  {
    if ((memAreasSet->Areas[i].Core==coreId) && ((memAreasSet->Areas[i].End - memAreasSet->Areas[i].Start) > 0U)) /* QAC Deviations: (No 2824) The memAreaSet pointer pointer already points to a hardware address right in this function. */
    {
      if ((memAreasSet->Areas[i].End - memAreasSet->Areas[i].Start) != (memAreasSet->Areas[i].Romend - memAreasSet->Areas[i].Romstart))
      {
        /* Defined size in rom does not match ram size */
        BrsMainExceptionHandler(kBrsIllegalParameter, BRSERROR_MODULE_BRSMAINSTARTUP, (uint16)(__LINE__));
      }
 
      memPtr = (volatile uint32*)memAreasSet->Areas[i].Start;
      romPtr = (volatile uint32*)memAreasSet->Areas[i].Romstart;
      while ((uint32)memPtr < memAreasSet->Areas[i].End)
      {
        *memPtr = *romPtr; /* QAC Deviations: (No 2814) The memPtr, romPtr pointer already points to a hardware address right in this function. */
        memPtr++; /* QAC Deviations: (No 2824) The memPtr pointer pointer already points to a hardware address right in this function. */
        romPtr++; /* QAC Deviations: (No 2824) The romPtr pointer pointer already points to a hardware address right in this function. */
      }
    }
  }
}
 
#if !defined (_MICROSOFT_C_VTT_)
/** @cond INTERNAL */
  /* This code is only needed for the first instance in the system */
#  if (BRSHW_SOURCECODE_TEMPLATE_VERSION >= 0x0103u)
  #define BRS_START_SEC_STARTUP_CODE
  #include "Brs_MemMap.h"
#  endif
/** @endcond */
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
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
 * |volatile uint8 |BrsMainStartup_Continue |Debug control variable that can be set to 1 to exit the infinite loop |
 * @brief Central exception handler for errors during startup phase
 * @note This function serves as a specialized exception handler specifically for errors that occur
 *       during the startup phase, before the main exception handler is fully initialized. It enters
 *       an infinite loop to halt execution when a critical error is detected.
 */
/* author Vector Informatik GmbH */
/* date 2022 */
/************************************************************************************************/
void BrsMainExceptionStartup(void)
{
  volatile uint8 BrsMainStartup_Continue;
  BrsMainStartup_Continue = 0u;
  while ((uint32)BrsMainStartup_Continue == 0u)
  {
    /* Set BrsMainStartup_Continue to 1 to continue here.
     *  If the debugger is not able to show the stack properly, this mechanism can be used to find the
     *  source of the exception. */
  }
}
/** @cond INTERNAL */
#  if (BRSHW_SOURCECODE_TEMPLATE_VERSION >= 0x0103u)
  #define BRS_STOP_SEC_STARTUP_CODE
  #include "Brs_MemMap.h"
#  endif
/** @endcond */
#endif /*_MICROSOFT_C_VTT_*/
 
 