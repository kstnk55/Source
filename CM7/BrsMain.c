/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2023 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/** \file  File:  BrsMain.c
 *      Project:  Vector Basic Runtime System
 *       Module:  BrsMain
 *
 *  \brief Description:  Main file of BRS contains
 *                       - Main function (called from StartUpCode and calls stack entry EcuM_Init())
 *                       - Call of BrsHw HW initialization routines
 *                       - 1ms handler, with support of cycle functions with several cycle times
 *                       - Default_Init_Task, Main and Background Task which can be used by the operating system
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
 
#define _BRSMAIN_C_
 
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "cy_project.h"          /* for D-CACHE / MPU */
#include "cy_device_headers.h"   /* for D-CACHE / MPU */
 
#include "BrsMain.h"
 
#if !defined (_MICROSOFT_C_VTT_)
  #include "vBrs_Lcfg.h"
#else
  #include "CANoeAPI.h"
  #include <stdio.h>
  #include "Os.h"
#endif
 
#if defined (BRS_ENABLE_TESTSUITE_SUPPORT)
  #include "BrsTestsuite.h"
#endif
 
#if !defined (_MICROSOFT_C_VTT_)
#include "BrsMain_Appl.h"
#endif
 
#include "Rte_Main.h" /*add atec sugiura*/
#include "Os.h"
#include "vMemAccM.h"
/* IVI */
#include "IVI_NVM_Ext.h"
/* IVI */
 
/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
#if (BRSMAIN_VERSION != 0x0211u)
  #error "Header and source file are inconsistent!"
#endif
#if (BRSMAIN_BUGFIX_VERSION != 0x02u)
  #error "Different versions of bugfix in Header and Source used!"
#endif
 
/* BRS_GENERATED_HW_CONFIG_VERSION is generated into vBrsCfg.h by Cfg5 vBrs generator */
#if (BRS_GENERATED_HW_CONFIG_VERSION < 384U)
  #error "Version of vBrs Generator too old! Please update it."
#endif
 
/**********************************************************************************************************************
 *  CONFIGURATION CHECK
 *********************************************************************************************************************/
#if !defined (_MICROSOFT_C_VTT_)
# if (BRSHW_SOURCECODE_TEMPLATE_VERSION < 0x0103u)
  #error "This BrsMain version requires a BrsHw package with a minimum template version of 1.03.00!"
# endif
#endif
 
#if defined (BRS_ENABLE_OS_INTERRUPT_ONLY) && defined (BRS_ENABLE_OS_MULTICORESUPPORT)
  #error "OS MultiCore support is not supported together with OS INTERRUPT_ONLY UseCase!"
#endif
 
 
/**********************************************************************************************************************
 *  DEFINITION + MACROS
 *********************************************************************************************************************/
/* D-CACHE / MPU ---> */
#define BRS_ENABLE_MPU                 (STD_ON)
#define BRS_ENABLE_DCACHE              (STD_ON)
 
/* Address define - CM7 common */
#define BACKGROUND_REGION_ADDR         (0x00000000ul)       /* Back Ground Region Start Address */
#define CM7_SELF_ITCM_REGION_ADDR      (0x00000000ul)       /* Self Instruction TCM RAM Region Start Address */
#define CODE_FLASH_A_REGION_ADDR       (0x10000000ul)       /* Code Flash Bank-A Region Start Address */
#define CODE_FLASH_B_REGION_ADDR       (0x12000000ul)       /* Code Flash Bank-B Region Start Address */
#define WORK_FLASH_REGION_ADDR         (0x14000000ul)       /* Work Flash Region Start Address */
#define CM7_SELF_DTCM_REGION_ADDR      (0x20000000ul)       /* Self Data TCM RAM Region Start Address */
#define SRAM_REGION_ADDR               (0x28000000ul)       /* System RAM Region Start Address */
#define PERI_REGISTER_REGION_ADDR      (0x40000000ul)       /* Peripheral Register Region Start Address */
#define SMIF0_XIP_REGION_ADDR          (0x60000000ul)       /* SMIF Channel 0 XIP Region Start Address */
#define ARM_SYS_REGISTER_REGION_ADDR   (0xE0000000ul)       /* ARM System Registers Region Start Address */
 
/* Address define - CM7_0 */
#define SRAM_CM70_NO_ACCESS_1_ADDR        (0x28000000ul)       /* SRAM: CM7_0 Not Access Area (System Reserve + M0+ Retention, 64KB) */
#define SRAM_CM70_CA_ENABLE_1_ADDR        (0x28020000ul)       /* SRAM: CM7_0 Cache Enable Area 1 Start Address (MICROSAR BSW Cached) */
#define SRAM_CM70_CA_ENABLE_2_ADDR        (0x28040000ul)       /* SRAM: CM7_0 Cache Enable Area 2 Start Address (Meter Cached) */
 
/* Address define - CM7_1 */
#define CODE_FLASH_A_CM71_ACCESS_1_ADDR   (0x10080000ul)       /* CodeFlash: CM7_1 Access Allow Area 1 Start Address */
#define CODE_FLASH_A_CM71_ACCESS_2_ADDR   (0x10100000ul)       /* CodeFlash: CM7_1 Access Allow Area 2 Start Address */
#define CODE_FLASH_A_CM71_ACCESS_3_ADDR   (0x10280000ul)       /* CodeFlash: CM7_1 Access Allow Area 3 Start Address (App Graphic) */
#define SRAM_CM71_ACCESS_1_ADDR           (0x28010000ul)       /* SRAM: CM7_1 Access Allow Area 1 Start Address (BootMgr Retention 2KB) */
#define SRAM_CM71_ACCESS_2_ADDR           (0x28018000ul)       /* SRAM: CM7_1 Access Allow Area 2 Start Address (M0+/M7 Shared Mem 16KB) */
#define SRAM_CM71_ACCESS_3_ADDR           (0x2801C000ul)       /* SRAM: CM7_1 Access Allow Area 3 Start Address (Graphic Retention 4KB) */
#define SRAM_CM71_ACCESS_4_ADDR           (0x28060000ul)       /* SRAM: CM7_1 Access Allow Area 4 Start Address (BSW Satelite sub1 + RTE sub2-7, 128KB) */
#define SRAM_CM71_ACCESS_5_ADDR           (0x28080000ul)       /* SRAM: CM7_1 Access Allow Area 5 Start Address (Graphic SRAM) */
 
#define MPU_SUB_REGION_ALL_EN          (0x00ul)
#define MPU_SUB_REGION_0_DIS           (0x01ul)
#define MPU_SUB_REGION_1_DIS           (0x02ul)
#define MPU_SUB_REGION_2_DIS           (0x04ul)
#define MPU_SUB_REGION_3_DIS           (0x08ul)
#define MPU_SUB_REGION_4_DIS           (0x10ul)
#define MPU_SUB_REGION_5_DIS           (0x20ul)
#define MPU_SUB_REGION_6_DIS           (0x40ul)
#define MPU_SUB_REGION_7_DIS           (0x80ul)
 
#define MPU_CFG_ARRAY_SIZE(array) (sizeof(array)/sizeof(cy_stc_mpu_region_cfg_t))
/* <--- D-CACHE / MPU */
 
/**********************************************************************************************************************
 *  GLOBAL VARIABLES
 *********************************************************************************************************************/
#if defined (BRS_ENABLE_1MS_HANDLER)
# if !defined (BRSMAIN_CYCLIC_MAX_CALLBACKS)
  #define BRSMAIN_CYCLIC_MAX_CALLBACKS 2u
# endif
 
  #define START_SEC_VAR_NOINIT_UNSPECIFIED
  #include "MemMap.h"
  typedef struct
  {
    void (*FunctionPointer[BRSMAIN_CYCLIC_MAX_CALLBACKS]) (void);
    uint8 FunctionCounter;
  }brsMain_Cyclic_Callbacks;
  #define STOP_SEC_VAR
  #include "MemMap.h"
#endif /*BRS_ENABLE_1MS_HANDLER*/
 
#if !defined (_MICROSOFT_C_VTT_)
extern volatile brsMain_ResetReasonType brsMain_ResetReason;
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
   * \var brsMain_CallCounter1ms
   *      Counter for calls of the function BrsMainCyclic1ms
   */
  static volatile uint16 brsMain_CallCounter1ms;
 
  /**
   * \var brsMain_CallCounter1sec
   *      Counter for 1000 calls of the function BrsMainCyclic1ms
   */
  static volatile uint16 brsMain_CallCounter1sec;
  #define STOP_SEC_VAR
  #include "MemMap.h"
 
  #define START_SEC_VAR_NOINIT_UNSPECIFIED
  #include "MemMap.h"
  static brsMain_Cyclic_Callbacks brsMain_Cyclic_Callbacks_Background;
  static brsMain_Cyclic_Callbacks brsMain_Cyclic_Callbacks_1ms;
  static brsMain_Cyclic_Callbacks brsMain_Cyclic_Callbacks_10ms;
  static brsMain_Cyclic_Callbacks brsMain_Cyclic_Callbacks_100ms;
  static brsMain_Cyclic_Callbacks brsMain_Cyclic_Callbacks_250ms;
  static brsMain_Cyclic_Callbacks brsMain_Cyclic_Callbacks_500ms;
  static brsMain_Cyclic_Callbacks brsMain_Cyclic_Callbacks_1000ms;
  #define STOP_SEC_VAR
  #include "MemMap.h"
#endif /*BRS_ENABLE_1MS_HANDLER*/
 
#if defined (BRS_ENABLE_OS_INTERRUPT_ONLY)
  #define START_SEC_VAR_ZERO_INIT_32BIT
  #include "MemMap.h"
  static volatile uint32 brsMain_SuspendAllCounter;
  #define STOP_SEC_VAR
  #include "MemMap.h"
#endif
 
/**********************************************************************************************************************
 *  LOCAL CONST VARIABLES
 *********************************************************************************************************************/
# if defined (_MICROSOFT_C_VTT_)
  #define BRSMAIN_ERRORBUFFERSIZE  120
#endif
 
/* D-CACHE / MPU ---> */
#if (BRS_ENABLE_MPU == STD_ON)
static const cy_stc_mpu_region_cfg_t C_MpuConfig70[] = {
        /* addr                                 size                 permission                      attribute                       execute                     srd                                                                       enable       */
        { BACKGROUND_REGION_ADDR,               CY_MPU_SIZE_4GB,     CY_MPU_ACCESS_P_NO_ACCESS,      CY_MPU_ATTR_STR_ORD_DEV,        CY_MPU_INST_ACCESS_DIS,     MPU_SUB_REGION_ALL_EN,                                                    CY_MPU_ENABLE },
        {   CM7_SELF_ITCM_REGION_ADDR,          CY_MPU_SIZE_64KB,    CY_MPU_ACCESS_P_FULL_ACCESS,    CY_MPU_ATTR_STR_ORD_DEV,        CY_MPU_INST_ACCESS_EN,      MPU_SUB_REGION_ALL_EN,                                                    CY_MPU_ENABLE },
/*�{*///{   CODE_FLASH_A_REGION_ADDR,           CY_MPU_SIZE_4MB,     CY_MPU_ACCESS_P_RO,             CY_MPU_ATTR_NORM_MEM_WT,        CY_MPU_INST_ACCESS_EN,      (MPU_SUB_REGION_0_DIS | MPU_SUB_REGION_6_DIS | MPU_SUB_REGION_7_DIS),     CY_MPU_ENABLE },
/*��*/  {   CODE_FLASH_A_REGION_ADDR,           CY_MPU_SIZE_4MB,     CY_MPU_ACCESS_P_RO,             CY_MPU_ATTR_NORM_MEM_WT,        CY_MPU_INST_ACCESS_EN,      (MPU_SUB_REGION_0_DIS),                                                   CY_MPU_ENABLE },
        {   CODE_FLASH_B_REGION_ADDR,           CY_MPU_SIZE_4MB,     CY_MPU_ACCESS_P_RO,             CY_MPU_ATTR_STR_ORD_DEV,        CY_MPU_INST_ACCESS_DIS,     MPU_SUB_REGION_ALL_EN,                                                    CY_MPU_ENABLE },
        {   WORK_FLASH_REGION_ADDR,             CY_MPU_SIZE_128KB,   CY_MPU_ACCESS_P_RO,             CY_MPU_ATTR_NORM_SHR_MEM_NC,    CY_MPU_INST_ACCESS_DIS,     (MPU_SUB_REGION_6_DIS),                                                   CY_MPU_ENABLE },
        {   CM7_SELF_DTCM_REGION_ADDR,          CY_MPU_SIZE_16KB,    CY_MPU_ACCESS_P_FULL_ACCESS,    CY_MPU_ATTR_STR_ORD_DEV,        CY_MPU_INST_ACCESS_DIS,     MPU_SUB_REGION_ALL_EN,                                                    CY_MPU_ENABLE },
/*�{*///{   SRAM_REGION_ADDR,                   CY_MPU_SIZE_1MB,     CY_MPU_ACCESS_P_FULL_ACCESS,    CY_MPU_ATTR_NORM_SHR_MEM_NC,    CY_MPU_INST_ACCESS_DIS,     (MPU_SUB_REGION_4_DIS | MPU_SUB_REGION_5_DIS | MPU_SUB_REGION_6_DIS | MPU_SUB_REGION_7_DIS),    CY_MPU_ENABLE },
/*��*/  {   SRAM_REGION_ADDR,                   CY_MPU_SIZE_1MB,     CY_MPU_ACCESS_P_FULL_ACCESS,    CY_MPU_ATTR_NORM_SHR_MEM_NC,    CY_MPU_INST_ACCESS_DIS,     MPU_SUB_REGION_ALL_EN,                                                    CY_MPU_ENABLE },
        {     SRAM_CM70_NO_ACCESS_1_ADDR,       CY_MPU_SIZE_64KB,    CY_MPU_ACCESS_P_NO_ACCESS,      CY_MPU_ATTR_STR_ORD_DEV,        CY_MPU_INST_ACCESS_DIS,     MPU_SUB_REGION_ALL_EN,                                                    CY_MPU_ENABLE },
        {     SRAM_CM70_CA_ENABLE_1_ADDR,       CY_MPU_SIZE_32KB,    CY_MPU_ACCESS_P_FULL_ACCESS,    CY_MPU_ATTR_NORM_MEM_WT,        CY_MPU_INST_ACCESS_DIS,     MPU_SUB_REGION_ALL_EN,                                                    CY_MPU_ENABLE },
        {     SRAM_CM70_CA_ENABLE_2_ADDR,       CY_MPU_SIZE_128KB,   CY_MPU_ACCESS_P_FULL_ACCESS,    CY_MPU_ATTR_NORM_MEM_WT,        CY_MPU_INST_ACCESS_DIS,     MPU_SUB_REGION_ALL_EN,                                                    CY_MPU_ENABLE },
        {   PERI_REGISTER_REGION_ADDR,          CY_MPU_SIZE_64MB,    CY_MPU_ACCESS_P_FULL_ACCESS,    CY_MPU_ATTR_SHR_DEV,            CY_MPU_INST_ACCESS_DIS,     MPU_SUB_REGION_ALL_EN,                                                    CY_MPU_ENABLE },
        {   SMIF0_XIP_REGION_ADDR,              CY_MPU_SIZE_128MB,   CY_MPU_ACCESS_P_FULL_ACCESS,    CY_MPU_ATTR_NORM_MEM_NC,        CY_MPU_INST_ACCESS_DIS,     MPU_SUB_REGION_ALL_EN,                                                    CY_MPU_ENABLE },
        {   ARM_SYS_REGISTER_REGION_ADDR,       CY_MPU_SIZE_512MB,   CY_MPU_ACCESS_P_FULL_ACCESS,    CY_MPU_ATTR_STR_ORD_DEV,        CY_MPU_INST_ACCESS_DIS,     MPU_SUB_REGION_ALL_EN,                                                    CY_MPU_ENABLE },
 
};
 
static const cy_stc_mpu_region_cfg_t C_MpuConfig71[] = {
        /* addr                                 size                 permission                      attribute                       execute                     srd                                                                       enable       */
        { BACKGROUND_REGION_ADDR,               CY_MPU_SIZE_4GB,     CY_MPU_ACCESS_P_NO_ACCESS,      CY_MPU_ATTR_STR_ORD_DEV,        CY_MPU_INST_ACCESS_DIS,     MPU_SUB_REGION_ALL_EN,                                                    CY_MPU_ENABLE },
        {   CODE_FLASH_A_CM71_ACCESS_1_ADDR,    CY_MPU_SIZE_512KB,   CY_MPU_ACCESS_P_RO,             CY_MPU_ATTR_NORM_MEM_WT,        CY_MPU_INST_ACCESS_EN,      (MPU_SUB_REGION_0_DIS),                                                   CY_MPU_ENABLE },
/*�{*///{   CODE_FLASH_A_CM71_ACCESS_2_ADDR,    CY_MPU_SIZE_256KB,   CY_MPU_ACCESS_P_RO,             CY_MPU_ATTR_NORM_MEM_WT,        CY_MPU_INST_ACCESS_EN,      MPU_SUB_REGION_ALL_EN,                                                    CY_MPU_ENABLE },
/*��*/  {   CODE_FLASH_A_CM71_ACCESS_2_ADDR,    CY_MPU_SIZE_1MB,     CY_MPU_ACCESS_P_RO,             CY_MPU_ATTR_NORM_MEM_WT,        CY_MPU_INST_ACCESS_EN,      MPU_SUB_REGION_ALL_EN,                                                    CY_MPU_ENABLE },
/*�{*///{   CODE_FLASH_A_CM71_ACCESS_3_ADDR,    CY_MPU_SIZE_512KB,   CY_MPU_ACCESS_P_RO,             CY_MPU_ATTR_NORM_MEM_WT,        CY_MPU_INST_ACCESS_EN,      (MPU_SUB_REGION_0_DIS | MPU_SUB_REGION_1_DIS | MPU_SUB_REGION_2_DIS),     CY_MPU_ENABLE },
/*��*/  {   CODE_FLASH_A_CM71_ACCESS_3_ADDR,    CY_MPU_SIZE_512KB,   CY_MPU_ACCESS_P_RO,             CY_MPU_ATTR_NORM_MEM_WT,        CY_MPU_INST_ACCESS_EN,      MPU_SUB_REGION_ALL_EN,                                                    CY_MPU_ENABLE },
/*�{*///{   SRAM_CM71_ACCESS_1_ADDR,            CY_MPU_SIZE_2KB,     CY_MPU_ACCESS_P_FULL_ACCESS,    CY_MPU_ATTR_NORM_SHR_MEM_NC,    CY_MPU_INST_ACCESS_DIS,     MPU_SUB_REGION_ALL_EN,                                                    CY_MPU_ENABLE },
/*��*/  {   SRAM_CM71_ACCESS_1_ADDR,            CY_MPU_SIZE_2KB,     CY_MPU_ACCESS_P_FULL_ACCESS,    CY_MPU_ATTR_NORM_SHR_MEM_NC,    CY_MPU_INST_ACCESS_DIS,     MPU_SUB_REGION_ALL_EN,                                                    CY_MPU_ENABLE },
        {   SRAM_CM71_ACCESS_2_ADDR,            CY_MPU_SIZE_16KB,    CY_MPU_ACCESS_P_FULL_ACCESS,    CY_MPU_ATTR_NORM_SHR_MEM_NC,    CY_MPU_INST_ACCESS_DIS,     MPU_SUB_REGION_ALL_EN,                                                    CY_MPU_ENABLE },
        {   SRAM_CM71_ACCESS_3_ADDR,            CY_MPU_SIZE_4KB,     CY_MPU_ACCESS_P_FULL_ACCESS,    CY_MPU_ATTR_NORM_SHR_MEM_NC,    CY_MPU_INST_ACCESS_DIS,     MPU_SUB_REGION_ALL_EN,                                                    CY_MPU_ENABLE },
/*�{*///{   SRAM_CM71_ACCESS_4_ADDR,            CY_MPU_SIZE_128KB,   CY_MPU_ACCESS_P_FULL_ACCESS,    CY_MPU_ATTR_NORM_SHR_MEM_NC,    CY_MPU_INST_ACCESS_DIS,     (MPU_SUB_REGION_0_DIS),                                                   CY_MPU_ENABLE },
/*��*/  {   SRAM_CM71_ACCESS_4_ADDR,            CY_MPU_SIZE_128KB,   CY_MPU_ACCESS_P_FULL_ACCESS,    CY_MPU_ATTR_NORM_SHR_MEM_NC,    CY_MPU_INST_ACCESS_DIS,     (MPU_SUB_REGION_0_DIS),                                                   CY_MPU_ENABLE },
        {   SRAM_CM71_ACCESS_5_ADDR,            CY_MPU_SIZE_128KB,   CY_MPU_ACCESS_P_FULL_ACCESS,    CY_MPU_ATTR_NORM_SHR_MEM_NC,    CY_MPU_INST_ACCESS_DIS,     MPU_SUB_REGION_ALL_EN,                                                    CY_MPU_ENABLE },
        {   PERI_REGISTER_REGION_ADDR,          CY_MPU_SIZE_64MB,    CY_MPU_ACCESS_P_FULL_ACCESS,    CY_MPU_ATTR_SHR_DEV,            CY_MPU_INST_ACCESS_DIS,     MPU_SUB_REGION_ALL_EN,                                                    CY_MPU_ENABLE },
        {   ARM_SYS_REGISTER_REGION_ADDR,       CY_MPU_SIZE_512MB,   CY_MPU_ACCESS_P_FULL_ACCESS,    CY_MPU_ATTR_STR_ORD_DEV,        CY_MPU_INST_ACCESS_DIS,     MPU_SUB_REGION_ALL_EN,                                                    CY_MPU_ENABLE },
 
};
#endif
/* <--- D-CACHE / MPU */
                     
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
void BrsMainWrapperTogglePinLED(void)
{
  BrsMainTogglePin(BRSMAIN_TOGGLEPIN_LED);
}
# endif
 
# if defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN)
void BrsMainWrapperTogglePinWD(void)
{
  BrsMainTogglePin(BRSMAIN_TOGGLEPIN_WD);
}
# endif
 
# if defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
void BrsMainWrapperTogglePinCustom(void)
{
  BrsMainTogglePin(BRSMAIN_TOGGLEPIN_CUSTOM);
}
# endif
#endif /*!_MICROSOFT_C_VTT_*/
 
/*****************************************************************************/
/* @brief      Main initialization routine.
 *             Contains configuration specific initialization of BrsHw parts
 *             and BrsMain specific mechanisms.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from main
 *****************************************************************************/
void BrsMainInit(void)
{
#if defined (BRSMAIN_BRSMAININIT_CALLOUT)
  BrsTestsuite_BrsMain_BrsMainInit();
#endif
 
#if !defined (_MICROSOFT_C_VTT_)
  BrsMain_Appl_Init();
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
# endif /*!BRS_ENABLE_PREFER_PLL_WATCHDOG_INIT*/
 
# if defined (BRS_ENABLE_PORT)
  BrsHwPortInitPowerOn();
# endif
 
# if defined (BRS_ENABLE_FBL_SUPPORT)
#  if defined (BRSHW_DISABLE_ECC_AVAILABLE)
  BrsHwDisableEccErrorReporting();
#  endif
# endif
#endif /*!BRS_FBL_NO_ECUMINIT&&!_MICROSOFT_C_VTT_*/
 
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
#endif /*!_MICROSOFT_C_VTT_*/
 
#if defined (BRS_ENABLE_OS_INTERRUPT_ONLY)
  brsMain_SuspendAllCounter = 0u;
#endif
}
 
#if defined (BRS_ENABLE_1MS_HANDLER)
/*****************************************************************************/
/* @brief      Routine to register cyclic callbacks.
 * @pre        Initialization of BrsMain was done threw call of BrsMainInit().
 * @param[in]  FunctionPointer has to be a pointer to a function of type
 *             void function(void).
 * @param[in]  Cycletime described the cycletime, the callback should be triggered.
 * @param[out] -
 * @return     -
 * @context    Function is called from modules that need cyclic callbacks.
 *****************************************************************************/
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
 
volatile uint32 gBarrierA = 0;
volatile uint32 gBarrierB = 0;
 
 
#if (!defined (BRS_ENABLE_FBL_SUPPORT)) && (!defined (BRS_ENABLE_OS_INTERRUPT_ONLY))
/*****************************************************************************/
/* @brief      InitTask to call EcuM_StartupTwo() on the MasterCore.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS.
 *****************************************************************************/
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
/************* add start *************/
  /* Initialization I (CoreM7-0) */
  while(!gBarrierB)
  {
    ; /* Wait for  Default_Init_Task_Core1*/
  }
  gBarrierA = 1;
   EcuM_StartupTwo();
 
  /* Initialization II (CoreM7-0) */
  while(Rte_InitState_1 != RTE_STATE_INIT)
  {
    ;
  }
  Rte_Start();
/************* add end  *************/
#endif
 
  (void)TerminateTask();
}
 
/*****************************************************************************/
/* @brief      InitTask to call Os_InitialEnableInterruptSources() on the MasterCore.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS. It is separated from
 *             Default_Init_Task() to allow the SafeContext partitioning UseCase.
 *****************************************************************************/
TASK(Default_Init_Task_Trusted)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_TRUSTED_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Trusted();
#endif
 
  Os_InitialEnableInterruptSources(FALSE);
 
 
  (void)TerminateTask();
}
 
# if defined (BRS_ENABLE_OS_MULTICORESUPPORT)
/*****************************************************************************/
/* @brief      InitTask to call EcuM_StartupTwo() on the 1st Core.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS on the 1st Core.
 *****************************************************************************/
TASK(Default_Init_Task_Core0)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_CORE0_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Core0();
#endif
/************* add start *************/
  /* Initialization I (CoreM7-1) */
  while(!gBarrierB)
  {
    ; /* Wait for  Default_Init_Task*/
  }
  gBarrierA = 1;
  EcuM_StartupTwo();
 
  /* Initialization II (CoreM7-1) */
  while(Rte_InitState_1 != RTE_STATE_INIT)
  {
    ;
  }
  Rte_Start();
/************* add end  *************/
 
  (void)TerminateTask();
}
 
/*****************************************************************************/
/* @brief      InitTask to call Os_InitialEnableInterruptSources() on the 1st Core.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS on the 1st Core. It is separated from
 *             Default_Init_Task_Core0() to allow the SafeContext partitioning UseCase.
 *****************************************************************************/
TASK(Default_Init_Task_Core0_Trusted)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_CORE0_TRUSTED_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Core0_Trusted();
#endif
 
  Os_InitialEnableInterruptSources(FALSE);
 
  (void)TerminateTask();
}
 
/*****************************************************************************/
/* @brief      InitTask to call EcuM_StartupTwo() on the 2nd Core.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS on the 2nd Core.
 *****************************************************************************/
TASK(Default_Init_Task_Core1)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_CORE1_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Core1();
#endif
 
/************* add start *************/
  gBarrierB = 1;
  while(!gBarrierA)
  {
    ;
  }
 
  EcuM_StartupTwo();
// /* IVI */
//  wvdFLSIF_Init();
// /* IVI */
 
  Rte_Start();
/************* add end  *************/
 
  (void)TerminateTask();
}
#if 1
/*****************************************************************************/
/* @brief      InitTask to call Os_InitialEnableInterruptSources() on the 2nd Core.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS on the 2nd Core. It is separated from
 *             Default_Init_Task_Core1() to allow the SafeContext partitioning UseCase.
 *****************************************************************************/
TASK(Default_Init_Task_Core1_Trusted)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_CORE1_TRUSTED_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Core1_Trusted();
#endif
 
  Os_InitialEnableInterruptSources(FALSE);
 
  (void)TerminateTask();
}
#endif
/*****************************************************************************/
/* @brief      InitTask to call EcuM_StartupTwo() on the 3rd Core.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS on the 3rd Core.
 *****************************************************************************/
TASK(Default_Init_Task_Core2)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_CORE2_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Core2();
#endif
 
  EcuM_StartupTwo();
 
  (void)TerminateTask();
}
 
/*****************************************************************************/
/* @brief      InitTask to call Os_InitialEnableInterruptSources() on the 3rd Core.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS on the 3rd Core. It is separated from
 *             Default_Init_Task_Core2() to allow the SafeContext partitioning UseCase.
 *****************************************************************************/
TASK(Default_Init_Task_Core2_Trusted)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_CORE2_TRUSTED_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Core2_Trusted();
#endif
 
  Os_InitialEnableInterruptSources(FALSE);
 
  (void)TerminateTask();
}
 
/*****************************************************************************/
/* @brief      InitTask to call EcuM_StartupTwo() on the 4th Core.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS on the 4th Core.
 *****************************************************************************/
TASK(Default_Init_Task_Core3)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_CORE3_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Core3();
#endif
 
  EcuM_StartupTwo();
 
  (void)TerminateTask();
}
 
/*****************************************************************************/
/* @brief      InitTask to call Os_InitialEnableInterruptSources() on the 4th Core.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS on the 4th Core. It is separated from
 *             Default_Init_Task_Core3() to allow the SafeContext partitioning UseCase.
 *****************************************************************************/
TASK(Default_Init_Task_Core3_Trusted)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_CORE3_TRUSTED_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Core3_Trusted();
#endif
 
  Os_InitialEnableInterruptSources(FALSE);
 
  (void)TerminateTask();
}
 
/*****************************************************************************/
/* @brief      InitTask to call EcuM_StartupTwo() on the 5th Core.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS on the 5th Core.
 *****************************************************************************/
TASK(Default_Init_Task_Core4)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_CORE4_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Core4();
#endif
 
  EcuM_StartupTwo();
 
  (void)TerminateTask();
}
 
/*****************************************************************************/
/* @brief      InitTask to call Os_InitialEnableInterruptSources() on the 5th Core.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS on the 5th Core. It is separated from
 *             Default_Init_Task_Core4() to allow the SafeContext partitioning UseCase.
 *****************************************************************************/
TASK(Default_Init_Task_Core4_Trusted)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_CORE4_TRUSTED_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Core4_Trusted();
#endif
 
  Os_InitialEnableInterruptSources(FALSE);
 
  (void)TerminateTask();
}
 
/*****************************************************************************/
/* @brief      InitTask to call EcuM_StartupTwo() on the 6th Core.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS on the 6th Core.
 *****************************************************************************/
TASK(Default_Init_Task_Core5)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_CORE5_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Core5();
#endif
 
  EcuM_StartupTwo();
 
  (void)TerminateTask();
}
 
/*****************************************************************************/
/* @brief      InitTask to call Os_InitialEnableInterruptSources() on the 6th Core.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS on the 6th Core. It is separated from
 *             Default_Init_Task_Core5() to allow the SafeContext partitioning UseCase.
 *****************************************************************************/
TASK(Default_Init_Task_Core5_Trusted)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_CORE5_TRUSTED_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Core5_Trusted();
#endif
 
  Os_InitialEnableInterruptSources(FALSE);
 
  (void)TerminateTask();
}
 
/*****************************************************************************/
/* @brief      InitTask to call EcuM_StartupTwo() on the 7th Core.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS on the 7th Core.
 *****************************************************************************/
TASK(Default_Init_Task_Core6)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_CORE6_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Core6();
#endif
 
  EcuM_StartupTwo();
 
  (void)TerminateTask();
}
 
/*****************************************************************************/
/* @brief      InitTask to call Os_InitialEnableInterruptSources() on the 7th Core.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS on the 7th Core. It is separated from
 *             Default_Init_Task_Core6() to allow the SafeContext partitioning UseCase.
 *****************************************************************************/
TASK(Default_Init_Task_Core6_Trusted)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_CORE6_TRUSTED_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Core6_Trusted();
#endif
 
  Os_InitialEnableInterruptSources(FALSE);
 
  (void)TerminateTask();
}
# endif /*BRS_ENABLE_OS_MULTICORESUPPORT*/
#endif /*!BRS_ENABLE_FBL_SUPPORT&&!BRS_ENABLE_OS_INTERRUPT_ONLY*/
 
#if defined (BRS_ENABLE_1MS_HANDLER)
/*****************************************************************************/
/* @brief      One millisecond handler for BrsMain
 *               - Executes retransmission of BRS TCC messages
 *               - Toggling of LED (alive signal)
 *               - BRS Test code (1s cyclic negative TCC response message)
 * @pre        Initialization of BrsMain was done threw call of BrsMainInit().
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called each millisecond either from the main loop
 *             or from the BRS main task (TASK(mainTask))
 *****************************************************************************/
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
/*****************************************************************************/
/* @brief      BrsMainTask executes the 1 millisecond handler
 *             The function initiates calls to BrsMainCyclic1ms
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS and activated by
 *             the OS event EvCyclicAlarm_1ms
 *****************************************************************************/
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
/*****************************************************************************/
/* @brief      This API is used to toggle a PortPin.
 *             Per default, the following parameters are available:
 *               BRSMAIN_TOGGLEPIN_LED
 *               BRSMAIN_TOGGLEPIN_WD
 *               BRSMAIN_TOGGLEPIN_CUSTOM
 *             Depending pins must be configured and initialized within BrsHw.
 * @pre        -
 * @param[in]  Pin to be toggled
 * @param[out] -
 * @return     -
 * @context    Function is called from all modules to set or clear a PortPin
 *****************************************************************************/
void BrsMainTogglePin(brsMain_TogglePin Pin)
{
  #define START_SEC_VAR_INIT_UNSPECIFIED
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
/*****************************************************************************/
/* @brief      This is the central exeption handler of BRS.
 *             All BRS modules and all CANbedded specific fatal error handler will
 *             call this API in case an assertion has failed.
 * @pre        -
 * @param[in]  ErrorCode shall hold the caller specific error code (uint8)
 * @param[in]  ModuleCode shall describe the caller; please use the CI constant as parameter (uint8)
 * @param[in]  LineNumber shall be the line where the assertion has failed, or,
 *             if not available on caller location, the line where this API is
 *             called from
 * @param[out] -
 * @return     -
 * @context    This function implements an endless loop with locked interrupts.
 *             The recommendation is to set a breakpoint on top of this function
 *             to see if any assertion has failed during the code execution.
 *             Due to an assertion has failed and the endless loop runs with
 *             locked global interrupts there will be no life after the call ...
 *****************************************************************************/
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
  BrsMain_Continue = 0;
 
#if !defined (BRS_ENABLE_FBL_SUPPORT) /* FBL is always running in polling mode with interrupts disabled */
  DisableAllInterrupts();
#endif
 
  while (BrsMain_Continue == 0)
  {
    /* Set BrsMain_Continue to 1 to continue here.
     *  If the debugger is not able to show the stack properly, this mechanism can be used to find the
     *  source of the exception. */
  }
# endif /*_MICROSOFT_C_VTT_*/
#endif /*BRS_ENABLE_SAFECTXSUPPORT*/
}
#if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_STOP_SEC_RAM_CODE
  #include "Brs_MemMap.h"
#endif
 
#if !defined (_MICROSOFT_C_VTT_)
/*****************************************************************************/
/* @brief      Get reset reason
 * @pre        BrsHwGetResetReasonStartup() is called first and the rest reason
 *             is saved in global variable brsMain_ResetReason.
 * @param[in]  -
 * @param[out] -
 * @return     Reset reason
 * @context    This is a wrapper function for previous BrsHwGetResetReason().
 *             This is to prevent multiple selection of reset reason
 *             registers, as this is not supported on all platforms.
 *             The HW registers for the reset reason are evaluated via a call
 *             of BrsHwGetResetReasonStartup() in Brs_PreMainStartup().
 *             The result is stored by BrsMainStartup in the global variable
 *             brsMain_ResetReason.
 *****************************************************************************/
brsMain_ResetReasonType BrsMainGetResetReason(void)
{
  return brsMain_ResetReason;
}
#endif /*_MICROSOFT_C_VTT_*/
 
#if defined (BRS_ENABLE_OS_INTERRUPT_ONLY)
  /* OS is configured for UseCase Interrupt Only (/MICROSAR/Os/OsOS/OsUseCase) */
/*****************************************************************************/
/* @brief      With OS UseCase "Interrupt Only" (/MICROSAR/Os/OsOS/OsUseCase),
 *             the default API SuspendAllInterrupts() is not functional.
 *             Instead, this wrapper function is handling nested calls and the
 *             alternative suspend API call.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Called by vBrs generated SchM stub in OS UseCase Interrupt Only.
 *****************************************************************************/
void BrsMainSuspendAllInterrupts(void)
{
  if (brsMain_SuspendAllCounter==0u)
  {
    DisableAllInterrupts();
  }
 
  brsMain_SuspendAllCounter++;
}
 
/*****************************************************************************/
/* @brief      With OS UseCase "Interrupt Only" (/MICROSAR/Os/OsOS/OsUseCase),
 *             the default API ResumeAllInterrupts() is not functional.
 *             Instead, this wrapper function is handling nested calls and the
 *             alternative resume API call.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Called by vBrs generated SchM stub in OS UseCase Interrupt Only.
 *****************************************************************************/
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
#endif /*BRS_ENABLE_OS_INTERRUPT_ONLY*/
 
/*****************************************************************************/
/*@brief      Main function
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     always 0 as the function is not expected to return
 * @context    Called by the startup code
 *****************************************************************************/
int main(void)
{
#if !defined (_MICROSOFT_C_VTT_)
  uint32 coreID = BrsHw_GetCore();
# if (!defined (BRS_ENABLE_FBL_SUPPORT)) || (defined (BRS_FBL_EXCEPTIONTABLE_IN_RAM))
  uint32 i;
# endif
#endif /*!_MICROSOFT_C_VTT_*/
 
#if defined (BRSMAIN_MAIN_CALLOUT)
  BrsTestsuite_BrsMain_main();
#endif
 
#if !defined (_MICROSOFT_C_VTT_)
  BrsHwDisableInterruptAtPowerOn();
 
# if (!defined (BRS_ENABLE_FBL_SUPPORT)) || (defined (BRS_FBL_EXCEPTIONTABLE_IN_RAM))
  /* For FBL UseCase, only needed, if functionality to activate the additional ExceptionTable
     in RAM is enabled (vBRSGeneral/vBRSFblSupportExceptionTableInRam) */
 
  /* Search for valid Exception- and Interrupt Table in BrsMain_CoreConfig[]
     (vBRS generated into vBrs_Lcfg.c) */
  for (i=0; i<BrsMain_CoreConfig_Size; i++)
  {
    if (BrsMain_CoreConfig[i].PhysicalCoreId == coreID)
    {
      BrsHw_ExceptionTable_Init(BrsMain_CoreConfig[i].ExcVecLabel, BrsMain_CoreConfig[i].IntVecLabel);
      i=BrsMain_CoreConfig_Size+1;
    }
  }
 
  /* Check, if no valid core config was found */
  if (i==BrsMain_CoreConfig_Size)
    BrsMainExceptionHandler(kBrsInvalidCoreConfig, BRSERROR_MODULE_BRSMAIN, (uint16)(__LINE__));
# endif
 
# if (BRS_CPU_CORE_AMOUNT>1)
  if (coreID == BRSHW_INIT_CORE_ID)
# endif
#endif /*!_MICROSOFT_C_VTT_*/
  {
    BrsMainInit();
  }
 
#if defined (BRS_FBL_NO_ECUMINIT)
  FblMain();
 
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
 
  vMemAccM_InitMemory();
  vMemAccM_Init();
 
/* D-CACHE / MPU ---> */
# if (BRS_ENABLE_MPU == STD_ON)
  SCB_DisableICache();
  SCB_InvalidateICache();
#  if (BRS_ENABLE_DCACHE == STD_ON)
  SCB_InvalidateDCache();
#  endif
 
  if (coreID == BRSHW_INIT_CORE_ID) {
    (void)Cy_MPU_Setup(C_MpuConfig70, (uint8_t)MPU_CFG_ARRAY_SIZE(C_MpuConfig70), CY_MPU_DISABLE_USE_DEFAULT_MAP, CY_MPU_DISABLED_DURING_FAULT_NMI);
  } else {
    (void)Cy_MPU_Setup(C_MpuConfig71, (uint8_t)MPU_CFG_ARRAY_SIZE(C_MpuConfig71), CY_MPU_DISABLE_USE_DEFAULT_MAP, CY_MPU_DISABLED_DURING_FAULT_NMI);
  }
 
  SCB_EnableICache();
#  if (BRS_ENABLE_DCACHE == STD_ON)
  SCB_EnableDCache();
#  endif
# endif
/* <--- D-CACHE / MPU */
 
# if defined (BRS_ENABLE_HSM_SUPPORT)
  vHsm_Init();
# else
  EcuM_Init(); /* never returns */
# endif
#endif /*else BRS_FBL_NO_ECUMINIT*/
 
  BrsMainExceptionHandler(kBrsIllegalReturnFromMain, BRSERROR_MODULE_BRSMAIN, (uint16)(__LINE__));
 
  return 0;
}
 
 
