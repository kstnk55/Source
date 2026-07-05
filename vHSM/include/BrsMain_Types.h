/**
 * @file     BrsMain_Types.h
 * @brief    Public header: vBrsCfg.h, BrsMain.h
 * @details  Overview: This file contains the core type definitions used by the Vector Basic Runtime System (BRS). These types are essential for configuring multi-core behavior, memory layout, and system startup. This module provided by Vector should be left unchanged by FPT.
 */
/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/** \file  File:  BrsMain_Types.h
 *      Project:  Vector Basic Runtime System
 *       Module:  BrsMain
 *
 *  \brief Description:  Vector Basic Runtime System types header for vBrs generated structures.
 *
 *  \attention Please note:
 *    The demo and example programs only show special aspects of the software. With regard to the fact
 *    that these programs are meant for demonstration purposes only, Vector Informatik liability shall be
 *    expressly excluded in cases of ordinary negligence, to the extent admissible by law or statute.
 *********************************************************************************************************************/

#ifndef _BRSMAIN_TYPES_H_
#define _BRSMAIN_TYPES_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  MODULE VERSION
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  CONFIGURATION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL TYPE DEFINITIONS
 *********************************************************************************************************************/

/**
 * @brief    Enumeration to distinguish between cores running an AUTOSAR (ASR) OS and those running a non-AUTOSAR system.
 */
typedef enum
{
  NON_ASR = 0, /**< Indicates that no AUTOSAR OS is configured for the core. */
  ASR = 4096   /**< Indicates that an AUTOSAR OS is configured for the core. */
}brsCoreAsrType;

/**
 * @type     P2CONST(void, TYPEDEF, AUTOMATIC)
 * @var      Brs_AddressOfConstType
 * @brief    Defines a pointer type for constant addresses, typically used for pointing to memory locations like vector tables or stack labels. This is equivalent to `const void*`.
 * @unit     -
 * @scope    Global Type
 * @section  -
 * @par      Initial setting
 * |RAM0     |RAM1     |RAM2     |RAM3     |RAM4     |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |-        |-        |-        |-        |-        |
 */
typedef P2CONST(void, TYPEDEF, AUTOMATIC) Brs_AddressOfConstType;

/**
 * @def      BRS_DEFINE_ADDRESS_UNUSED
 * @value    (Brs_AddressOfConstType)0xFFFFFFFFU
 * @resolution -
 * @brief    Defines a marker value for an unused or invalid address, represented as the maximum 32-bit unsigned integer.
 */
#define BRS_DEFINE_ADDRESS_UNUSED (Brs_AddressOfConstType)0xFFFFFFFFU

/**
 * @brief    Structure to define the configuration properties for each core in a multi-core system, including its identity, memory layout, and operating mode.
 * @datasize 24 bytes
 */
typedef struct
{
  uint32 LogicalCoreId;           /**< The logical ID assigned to this core within the BRS configuration. */
  uint32 PhysicalCoreId;          /**< The physical hardware ID of this core as identified by the microcontroller. */
  Brs_AddressOfConstType StartupStackEndLabel; /**< A pointer to the end (highest address) of the startup stack for this core. */
  uint32 StartupStackSize;        /**< The total size of the startup stack in bytes. */
  brsCoreAsrType CoreIsAsr;       /**< Flag indicating whether the core is configured to run an AUTOSAR OS or not. */
  Brs_AddressOfConstType ExcVecLabel;          /**< A pointer to the start of the exception vector table for this core. */
  Brs_AddressOfConstType IntVecLabel;          /**< A pointer to the start of the interrupt vector table for this core. */
}brsMain_CoreType;

/**
 * @brief    Enumeration to identify the reason for the last system reset, used to adapt initialization logic.
 */
typedef enum
{
  BRSMAIN_RESET_SW,    /**< The reset was triggered by a software call (e.g., via BrsHwSoftwareResetECU). */
  BRSMAIN_RESET_OTHER  /**< The reset was triggered by any other source (e.g., power-on, watchdog, brown-out). */
}brsMain_ResetReasonType;

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL VARIABLES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#endif /*_BRSMAIN_TYPES_H_*/
