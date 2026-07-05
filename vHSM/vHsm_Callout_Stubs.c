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
 *            Module: vHsm
 *           Program: HSM_Vector_SLP1
 *          Customer: Nippon Seiki Co., Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: CYT4BFCCJDQ0BZEGS
 *    License Scope : The usage is restricted to CBD2300020_D00
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: vHsm_Callout_Stubs.c
 *   Generation Time: 2024-07-24 18:58:51
 *           Project: vHsmConfig - Version 1.0
 *          Delivery: CBD2300020_D00
 *      Tool Version: DaVinci Configurator Classic 5.26.35 SP2
 *
 *
 *********************************************************************************************************************/
/**
 * @file      vHsm_Callout_Stubs.c
 * @brief     Public header: vHsm_Callout_Stubs.h
 * @details   Overview: Implements callout stub functions for the vHsm module, providing interfaces
 * to cryptographic services, NVM, and hardware-specific functionalities.
 */
 
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK User Version>                           DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
 
/*********************************************************************************************************************
    INCLUDES
 *********************************************************************************************************************/
/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */
/** @cond INTERNAL */
#define VHSM_CALLOUT_STUBS_SOURCE
/** @endcond */
#include "vHsm.h"
#include "Csm_Types.h"
#include "vHsm_Api.h"
#include "vHsm_Cfg.h"
#include "vHsm_Hal.h"
 
 
/**********************************************************************************************************************
 *  Additional configured User includes
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK UserIncludes>                           DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
 #include "vHsm_Core_SecureBoot.h"
 #include "vBrsCfg.h"
 #include "vHsm_Nvm.h"
 #include "Fls_30_vMemAccM.h"
#include "vHsm.h"
#if (VHSM_OS_SUPPORT == STD_OFF)
# include "Os_InterruptInt.h"
#endif
#include "cy_project.h"
#include "cy_device_headers.h"
#include "vMem_30_Traveo2Cyp01_Int.h"
#include "cyip_cpuss.h"
#include "DualBank_Manager_FblTransition.h"
#include "vHsm_Custom.h"
#include "Crypto_30_Hwa_Hw.h"
#include "cy_mpu.h"
#include "vHsm_Callout_Stubs.h"
#include "Crypto_30_LibCv_Services.h"
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
 
/* Includes for module initialization */
#include "CryIf.h"
#include "Crypto_30_Hwa.h"
#include "Crypto_30_LibCv.h"
#include "Csm.h"
#include "vMemAccM.h"
#include "Fls_30_vMemAccM.h"
#include "Fee_30_SmallSector.h"
#include "NvM.h"
 
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK UserDeclarations>                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**
 * @def LAYOUT_MAJOR_0
 * @value '0'
 * @resolution -
 * @brief Major version digit 0 for memory layout.
 */
#define LAYOUT_MAJOR_0    '0'
/**
 * @def LAYOUT_MAJOR_1
 * @value '1'
 * @resolution -
 * @brief Major version digit 1 for memory layout.
 */
#define LAYOUT_MAJOR_1    '1'
/**
 * @def LAYOUT_MINOR_0
 * @value '0'
 * @resolution -
 * @brief Minor version digit 0 for memory layout.
 */
#define LAYOUT_MINOR_0    '0'
/**
 * @def LAYOUT_MINOR_1
 * @value '1'
 * @resolution -
 * @brief Minor version digit 1 for memory layout.
 */
#define LAYOUT_MINOR_1    '1'
/**
 * @def LAYOUT_RELEASE_0
 * @value '0'
 * @resolution -
 * @brief Release version digit 0 for memory layout.
 */
#define LAYOUT_RELEASE_0  '0'
/**
 * @def LAYOUT_RELEASE_1
 * @value '1'
 * @resolution -
 * @brief Release version digit 1 for memory layout.
 */
#define LAYOUT_RELEASE_1  '1'
/**
 * @def LAYOUT_PATCH_0
 * @value '0'
 * @resolution -
 * @brief Patch version digit 0 for memory layout.
 */
#define LAYOUT_PATCH_0    '0'
/**
 * @def LAYOUT_PATCH_1
 * @value '1'
 * @resolution -
 * @brief Patch version digit 1 for memory layout.
 */
#define LAYOUT_PATCH_1    '1'
 
/**
 * @def GO_TO_SLEEP
 * @value 0xFFFFFFFFU
 * @resolution -
 * @brief Flag indicating the system is entering sleep mode.
 */
#define GO_TO_SLEEP 0xFFFFFFFFU
/**
 * @def GO_OUT_SLEEP
 * @value 0x00000000U
 * @resolution -
 * @brief Flag indicating the system is exiting sleep mode.
 */
#define GO_OUT_SLEEP 0x00000000U
/**
 * @def MEM_MAGIC_FLAG
 * @value STD_ON
 * @resolution -
 * @brief Macro to enable or disable memory magic flag functionality.
 */
#define MEM_MAGIC_FLAG STD_ON
 
/**
 * @def IPC_NOTIFY_INT_NUMBER
 * @value 7u
 * @resolution -
 * @brief IPC interrupt number for notification.
 */
#define IPC_NOTIFY_INT_NUMBER 7u
/**
 * @def USED_IPC_CHANNEL
 * @value 7u
 * @resolution -
 * @brief The IPC channel currently in use.
 */
#define USED_IPC_CHANNEL 7u
/**
 * @def PASSWORD_DAP_LENGTH
 * @value 16u
 * @resolution -
 * @brief Length of the Debug Access Port (DAP) password in bytes.
 */
#define PASSWORD_DAP_LENGTH 16u
/**
 * @def HASH_DAP_LENGTH
 * @value 32u
 * @resolution -
 * @brief Length of the hashed password for DAP in bytes.
 */
#define HASH_DAP_LENGTH 32u
/**
 * @def KEY_ER_DAP_LENGTH
 * @value 16u
 * @resolution -
 * @brief Length of the encrypted random number key for DAP in bytes.
 */
#define KEY_ER_DAP_LENGTH 16u
/**
 * @def RANDOM_NUMBER_DAP_LENGTH
 * @value 16u
 * @resolution -
 * @brief Length of the random number for DAP authentication in bytes.
 */
#define RANDOM_NUMBER_DAP_LENGTH 16u
 
/* IPC IRQ */
/**
 * @def IPC_CM0_SECURITY_INT_NUMBER
 * @value 1u
 * @resolution -
 * @brief IPC interrupt number for CM0+ security related communications.
 */
#define IPC_CM0_SECURITY_INT_NUMBER        1u
 
/**
 * @def IPC_DAP_LIFECYCLE_CHANNEL
 * @value 3u
 * @resolution -
 * @brief IPC channel used for life cycle stage management and Debug Access Port (DAP).
 */
#define IPC_DAP_LIFECYCLE_CHANNEL       3u
 
// #define IPC_RELEASE_INT_NUMBER  2   /* Release interrupt number. This interrupt is handled by notifier core (CM7) */ /* In this alive function polling is used instead of release IRQ */
 
/* Debug Access Port authentication status */
/**
 * @def STATUS_DAP_AUTHEN_OK
 * @value 0x00000000U
 * @resolution -
 * @brief DAP authentication successful status code.
 */
#define STATUS_DAP_AUTHEN_OK                (0x00000000U)
/**
 * @def STATUS_DAP_AUTHEN_NOT_OK
 * @value 0x10000000U
 * @resolution -
 * @brief DAP authentication failed status code.
 */
#define STATUS_DAP_AUTHEN_NOT_OK            (0x10000000U)
/**
 * @def STATUS_DAP_REQUEST_PW_ADDR
 * @value 0x20000000U
 * @resolution -
 * @brief DAP status for requesting password address.
 */
#define STATUS_DAP_REQUEST_PW_ADDR          (0x20000000U)
/**
 * @def STATUS_DAP_PW_INCONSISTENT
 * @value 0x30000000U
 * @resolution -
 * @brief DAP status for inconsistent password.
 */
#define STATUS_DAP_PW_INCONSISTENT          (0x30000000U)
/**
 * @def STATUS_DAP_RN_FAIL
 * @value 0x40000000U
 * @resolution -
 * @brief DAP status for random number generation failure.
 */
#define STATUS_DAP_RN_FAIL                  (0x40000000U)
/**
 * @def STATUS_DAP_SEND_R
 * @value 0x50000000U
 * @resolution -
 * @brief DAP status for sending random number.
 */
#define STATUS_DAP_SEND_R                   (0x50000000U)
/**
 * @def STATUS_DAP_RECEIVE_KEY_ER
 * @value 0x60000000U
 * @resolution -
 * @brief DAP status for receiving encrypted random number key.
 */
#define STATUS_DAP_RECEIVE_KEY_ER           (0x60000000U)
/**
 * @def STATUS_DAP_ENCRYPT_JOB_NOT_OK
 * @value 0x70000000U
 * @resolution -
 * @brief DAP status for encryption job failure.
 */
#define STATUS_DAP_ENCRYPT_JOB_NOT_OK       (0x70000000U)
/**
 * @def STATUS_DAP_RECEIVE_P
 * @value 0x80000000U
 * @resolution -
 * @brief DAP status for receiving password.
 */
#define STATUS_DAP_RECEIVE_P                (0x80000000U)
/**
 * @def STATUS_DAP_HASH_FAIL
 * @value 0x90000000U
 * @resolution -
 * @brief DAP status for hashing failure.
 */
#define STATUS_DAP_HASH_FAIL                (0x90000000U)
/**
 * @def STATUS_DAP_SEND_PW_ADDR
 * @value 0xA0000000U
 * @resolution -
 * @brief DAP status for sending password address.
 */
#define STATUS_DAP_SEND_PW_ADDR             (0xA0000000U)
 
 /* Traveo2 registers */
#include "cyreg_cpuss.h"
/**
 * @def CPUSS_CM4_VECTOR_TABLE_BASE
 * @value 0x40200200U
 * @resolution -
 * @brief Base address for the Cortex-M4 vector table.
 */
# define CPUSS_CM4_VECTOR_TABLE_BASE   (*(volatile uint32*) 0x40200200U)
/**
 * @def CPUSS_CM4_PWR_CTL
 * @value 0x40201200U
 * @resolution -
 * @brief Power control register for Cortex-M4.
 */
# define CPUSS_CM4_PWR_CTL             (*(volatile uint32*) 0x40201200U)
/**
 * @def CPUSS_CM7_0_VECTOR_TABLE_BASE
 * @value 0x40200200U
 * @resolution -
 * @brief Base address for the Cortex-M7_0 vector table.
 */
# define CPUSS_CM7_0_VECTOR_TABLE_BASE (*(volatile uint32*) 0x40200200U)
/**
 * @def CPUSS_CM7_1_VECTOR_TABLE_BASE
 * @value 0x40200600U
 * @resolution -
 * @brief Base address for the Cortex-M7_1 vector table.
 */
# define CPUSS_CM7_1_VECTOR_TABLE_BASE (*(volatile uint32*) 0x40200600U)
/**
 * @def CPUSS_CM7_0_PWR_CTL
 * @value 0x40201200U
 * @resolution -
 * @brief Power control register for Cortex-M7_0.
 */
# define CPUSS_CM7_0_PWR_CTL           (*(volatile uint32*) 0x40201200U)
/**
 * @def CPUSS_CM7_1_PWR_CTL
 * @value 0x40201210U
 * @resolution -
 * @brief Power control register for Cortex-M7_1.
 */
# define CPUSS_CM7_1_PWR_CTL           (*(volatile uint32*) 0x40201210U)
/**
 * @def CLK_ROOT_SELECT
 * @value 0x40261244U
 * @resolution -
 * @brief Clock root select register.
 */
# define CLK_ROOT_SELECT               (*(volatile uint32*) 0x40261244U)
/**
 * @def FLASHC_FLASH_CTL
 * @value 0x40240000U
 * @resolution -
 * @brief Flash controller control register.
 */
# define FLASHC_FLASH_CTL              (*(volatile uint32*) 0x40240000U)
/**
 * @def FLASH_WORK_ERR_SILENT
 * @value 1uL << 22u
 * @resolution -
 * @brief Work ECC error silent enabled bitmask for flash.
 */
# define FLASH_WORK_ERR_SILENT         (1uL << 22u) /*!< Work ECC error silent enabled. */
/* Define for secure boot reset counter */
/**
 * @def NOP10()
 * @brief Macro to insert 10 NOP (No Operation) instructions for delay or synchronization.
 */
#define NOP10() do { \
  __asm(" NOP");          \
  __asm(" NOP");          \
  __asm(" NOP");          \
  __asm(" NOP");          \
  __asm(" NOP");          \
  __asm(" NOP");          \
  __asm(" NOP");          \
  __asm(" NOP");          \
  __asm(" NOP");          \
  __asm(" NOP");          \
  } while(0)
/**
 * @def CPUSS_RAM0_PWR_MACRO_CTL0
 * @value 0x40201340U
 * @resolution -
 * @brief Power macro control register 0 for CPUSS RAM0.
 */
#define CPUSS_RAM0_PWR_MACRO_CTL0 (*(volatile uint32*) 0x40201340U)
/**
 * @def RESET_COUNTER_LIMIT
 * @value 2UL
 * @resolution -
 * @brief Limit for the reset counter in secure boot.
 */
#define RESET_COUNTER_LIMIT (2UL)
/**
 * @def SRAM_RETAIN_VALUE
 * @value 0x05FA0002UL
 * @resolution -
 * @brief Value to retain in SRAM during specific low-power modes.
 */
#define SRAM_RETAIN_VALUE (0x05FA0002UL)
 
/**
 * @def ZERO_NUM
 * @value 0U
 * @resolution -
 * @brief Numeric constant for zero.
 */
#define ZERO_NUM (0U)
/**
 * @def ONE_NUM
 * @value 1U
 * @resolution -
 * @brief Numeric constant for one.
 */
#define ONE_NUM (1U)
/**
 * @def SHIFT_8_BIT
 * @value 8U
 * @resolution -
 * @brief Bit shift value for 8 bits.
 */
#define SHIFT_8_BIT (8U)
/**
 * @def SHIFT_16_BIT
 * @value 16U
 * @resolution -
 * @brief Bit shift value for 16 bits.
 */
#define SHIFT_16_BIT (16U)
/**
 * @def SHIFT_24_BIT
 * @value 24U
 * @resolution -
 * @brief Bit shift value for 24 bits.
 */
#define SHIFT_24_BIT (24U)
 
/**
 * @def UID_32_BIT_SIZE
 * @value 4U
 * @resolution -
 * @brief Size of Unique ID in 32-bit words.
 */
#define UID_32_BIT_SIZE (4U)
/**
 * @def UID_1_BYTE_SIZE
 * @value 15U
 * @resolution -
 * @brief Size of Unique ID in bytes, excluding null terminator.
 */
#define UID_1_BYTE_SIZE (15U)
/**
 * @def ARRAY_SIZE_8BYTE
 * @value 8U
 * @resolution -
 * @brief Standard array size of 8 bytes.
 */
#define ARRAY_SIZE_8BYTE (8U)
/**
 * @def ARRAY_SIZE_16BYTE
 * @value 16U
 * @resolution -
 * @brief Standard array size of 16 bytes.
 */
#define ARRAY_SIZE_16BYTE (16U)
 
/**
 * @def WORKFLASH_FLAG_SIZE
 * @value 8U
 * @resolution -
 * @brief Size of the WorkFlash flag in bytes.
 */
#define WORKFLASH_FLAG_SIZE (8U)
/**
 * @def WORKFLASH_PENDING_STATE
 * @value 1U
 * @resolution -
 * @brief State indicating a pending operation in WorkFlash.
 */
#define WORKFLASH_PENDING_STATE (1U)
 
/**
 * @def WORKFLASH_READWRITE_SIZE
 * @value 4U
 * @resolution -
 * @brief Size for WorkFlash read/write operations in bytes.
 */
#define WORKFLASH_READWRITE_SIZE (4U)
 
/**
 * @def WORKFLASH_WRITE_START_ADDR
 * @value 0x14030200U
 * @resolution -
 * @brief Start address for WorkFlash write operations.
 */
#define WORKFLASH_WRITE_START_ADDR (0x14030200U)
/**
 * @def WORKFLASH_WRITE_LAST_ADDR
 * @value 0x14038000U
 * @resolution -
 * @brief Last address for WorkFlash write operations.
 */
#define WORKFLASH_WRITE_LAST_ADDR (0x14038000U)
 
/**
 * @def WORKFLASH_WRITE_START_ADDR2
 * @value 0x14030000U
 * @resolution -
 * @brief Alternate start address for WorkFlash write operations.
 */
#define WORKFLASH_WRITE_START_ADDR2 (0x14030000U)
/**
 * @def WORKFLASH_WRITE_LAST_ADDR2
 * @value 0x14030100U
 * @resolution -
 * @brief Alternate last address for WorkFlash write operations.
 */
#define WORKFLASH_WRITE_LAST_ADDR2 (0x14030100U)
 
 
/**
 * @def WORKFLASH_ERASE_SIZE
 * @value 128U
 * @resolution -
 * @brief Size of WorkFlash erase block in bytes.
 */
#define WORKFLASH_ERASE_SIZE (128U)
/**
 * @def WORKFLASH_ERASE_LAST_IDX
 * @value 256U
 * @resolution -
 * @brief Last index for WorkFlash erase operations (corresponds to 0x14038000UL).
 */
#define WORKFLASH_ERASE_LAST_IDX (256U) /* 0x14038000UL */
/**
 * @def WORKFLASH_ERASE_START_ADDR
 * @value 0x14030000U
 * @resolution -
 * @brief Start address for WorkFlash erase operations.
 */
#define WORKFLASH_ERASE_START_ADDR (0x14030000U)
 
/**
 * @def WORKFLASH_OLD_LAYOUT
 * @value 0U
 * @resolution -
 * @brief Identifier for an old WorkFlash memory layout.
 */
#define WORKFLASH_OLD_LAYOUT (0U)
/**
 * @def WORKFLASH_NEW_LAYOUT
 * @value 1U
 * @resolution -
 * @brief Identifier for a new WorkFlash memory layout.
 */
#define WORKFLASH_NEW_LAYOUT (1U)
 
/**
 * @def SECUREBOOT_DTC_NO_ERROR
 * @value 0x00U
 * @resolution -
 * @brief DTC code indicating no error during secure boot.
 */
#define SECUREBOOT_DTC_NO_ERROR (0x00U)
/**
 * @def SECUREBOOT_DTC_CODEFLASH_A
 * @value 0x01U
 * @resolution -
 * @brief DTC code for an error in CodeFlash Bank A during secure boot.
 */
#define SECUREBOOT_DTC_CODEFLASH_A (0x01U)
/**
 * @def SECUREBOOT_DTC_CODEFLASH_B
 * @value 0x02U
 * @resolution -
 * @brief DTC code for an error in CodeFlash Bank B during secure boot.
 */
#define SECUREBOOT_DTC_CODEFLASH_B (0x02U)
/**
 * @def APP_A_FAIL
 * @value 0x0A0AU
 * @resolution -
 * @brief Status code indicating failure of Application A.
 */
#define APP_A_FAIL (0x0A0AU)
/**
 * @def APP_A_OK
 * @value 0xAAAAU
 * @resolution -
 * @brief Status code indicating Application A is OK.
 */
#define APP_A_OK (0xAAAAU)
/**
 * @def APP_B_FAIL
 * @value 0x0B0BU
 * @resolution -
 * @brief Status code indicating failure of Application B.
 */
#define APP_B_FAIL (0x0B0BU)
/**
 * @def APP_B_OK
 * @value 0xBBBBU
 * @resolution -
 * @brief Status code indicating Application B is OK.
 */
#define APP_B_OK (0xBBBBU)
 
/**
 * @def GET_NR_OF_ARRAY_ELEMENTS
 * @value (sizeof(array) / sizeof(array[0]))
 * @resolution -
 * @brief Calculates the number of elements in a given array.
 */
#define GET_NR_OF_ARRAY_ELEMENTS(array)         (sizeof(array) / sizeof(array[0]))
/* Set Cortex-M MPU settings */
/**
 * @def MPU_CONFIG_LIST
 * @brief Macro placeholder for MPU configuration list.
 * @resolution -
 */
#define MPU_CONFIG_LIST
 
/* Specifies enable/disable privileged software access to the default memory map */
/**
 * @def MPU_PRIV_DEF_ENA
 * @value 4U
 * @resolution -
 * @brief Defines the MPU setting for privileged software access to the default memory map.
 */
#define MPU_PRIV_DEF_ENA            (4U)  /* =CY_MPU_USE_DEFAULT_MAP_AS_BG */
 
/* Specifies enable/disable the operation of MPU during hard fault, NMI, and FAULTMASK handlers */
/**
 * @def MPU_HF_NMI_ENA
 * @value 0U
 * @resolution -
 * @brief Defines the MPU setting for operation during hard fault, NMI, and FAULTMASK handlers.
 */
#define MPU_HF_NMI_ENA              (0U)  /* =CY_MPU_DISABLED_DURING_FAULT_NMI */
 
/**
 * @def BACKGROUND_REGION_ADDR
 * @value 0x00000000u
 * @resolution -
 * @brief Start address of the Background Memory Region.
 */
#define BACKGROUND_REGION_ADDR       (0x00000000u) // Back Ground Region Start Address
/**
 * @def CODE_FLASH_REGION_ADDR
 * @value 0x10000000u
 * @resolution -
 * @brief Start address of the Code Flash Memory Region.
 */
#define CODE_FLASH_REGION_ADDR       (0x10000000u) // Code Flash Region Start Address
/**
 * @def WORK_FLASH_REGION_ADDR
 * @value 0x14000000u
 * @resolution -
 * @brief Start address of the Work Flash Memory Region.
 */
#define WORK_FLASH_REGION_ADDR       (0x14000000u) // Work Flash Region Start Address
/**
 * @def SRAM_REGION_ADDR
 * @value 0x28000000u
 * @resolution -
 * @brief Start address of the System RAM Memory Region.
 */
#define SRAM_REGION_ADDR             (0x28000000u) // System RAM Region Start Address
/**
 * @def PERI_REGISTER_REGION_ADDR
 * @value 0x40000000u
 * @resolution -
 * @brief Start address of the Peripheral Register Memory Region.
 */
#define PERI_REGISTER_REGION_ADDR    (0x40000000u) // Peripheral Register Region Start Address
/**
 * @def ARM_SYS_REGISTER_REGION_ADDR
 * @value 0xE0000000u
 * @resolution -
 * @brief Start address of the ARM System Registers Memory Region.
 */
#define ARM_SYS_REGISTER_REGION_ADDR (0xE0000000u) // ARM System Registers Region Start Address
 
/**
 * @def RAM_DENIED_REGION_1_ADDR
 * @value 0x28008000u
 * @resolution -
 * @brief Start address of RAM denied region 1 (32KB).
 */
#define RAM_DENIED_REGION_1_ADDR     (0x28008000u) //32KB
/**
 * @def RAM_DENIED_REGION_2_ADDR
 * @value 0x28018000u
 * @resolution -
 * @brief Start address of RAM denied region 2 (32KB or 64KB).
 */
#define RAM_DENIED_REGION_2_ADDR     (0x28018000u) //32KB or 64KB
// #define RAM_DENIED_REGION_2_1_ADDR   (0x28020000ul) //32KB
// #define RAM_DENIED_REGION_3_ADDR     (0x28028000ul) //256KB
// #define RAM_DENIED_REGION_4_ADDR     (0x28068000ul) //64KB
// #define RAM_DENIED_REGION_5_ADDR     (0x28078000ul) //32KB
 
/**
 * @def RAM_DENIED_REGION_3_ADDR
 * @value 0x28020000u
 * @resolution -
 * @brief Start address of RAM denied region 3 (128KB - 64KB).
 */
#define RAM_DENIED_REGION_3_ADDR     (0x28020000u) //128KB - 64KB
/**
 * @def RAM_DENIED_REGION_3_1_ADDR
 * @value 0x28030000u
 * @resolution -
 * @brief Start address of RAM denied region 3_1 (128KB - 32KB).
 */
#define RAM_DENIED_REGION_3_1_ADDR   (0x28030000u) //128KB - 32KB
/**
 * @def RAM_DENIED_REGION_3_2_ADDR
 * @value 0x28038000u
 * @resolution -
 * @brief Start address of RAM denied region 3_2 (128KB - 16KB).
 */
#define RAM_DENIED_REGION_3_2_ADDR   (0x28038000u) //128KB - 16KB
/**
 * @def RAM_DENIED_REGION_3_3_ADDR
 * @value 0x2803C000u
 * @resolution -
 * @brief Start address of RAM denied region 3_3 (128KB - 16KB).
 */
#define RAM_DENIED_REGION_3_3_ADDR   (0x2803C000u) //128KB - 16KB
/**
 * @def RAM_DENIED_REGION_4_ADDR
 * @value 0x28040000u
 * @resolution -
 * @brief Start address of RAM denied region 4 (256KB).
 */
#define RAM_DENIED_REGION_4_ADDR     (0x28040000u) //256KB
/**
 * @def RAM_DENIED_REGION_6_ADDR
 * @value 0x28080000u
 * @resolution -
 * @brief Start address of RAM denied region 6 (512KB).
 */
#define RAM_DENIED_REGION_6_ADDR     (0x28080000u) //512KB
 
 
/**
 * @def BACKGROUND_MPU_NO
 * @value 0
 * @resolution -
 * @brief MPU region number for the background memory area.
 */
#define BACKGROUND_MPU_NO       (0)
/**
 * @def CODE_FLASH_MPU_NO
 * @value 1
 * @resolution -
 * @brief MPU region number for the code flash memory area.
 */
#define CODE_FLASH_MPU_NO       (1)
/**
 * @def WORK_FLASH_MPU_NO
 * @value 2
 * @resolution -
 * @brief MPU region number for the work flash memory area.
 */
#define WORK_FLASH_MPU_NO       (2)
/**
 * @def SRAM_MPU_NO
 * @value 3
 * @resolution -
 * @brief MPU region number for the SRAM memory area.
 */
#define SRAM_MPU_NO             (3)
/**
 * @def PERI_REGISTER_MPU_NO
 * @value 4
 * @resolution -
 * @brief MPU region number for the peripheral register memory area.
 */
#define PERI_REGISTER_MPU_NO    (4)
/**
 * @def ARM_SYS_REGISTER_MPU_NO
 * @value 5
 * @resolution -
 * @brief MPU region number for the ARM system register memory area.
 */
#define ARM_SYS_REGISTER_MPU_NO (5)
 
/**
 * @def MAKER_ON_WORK_ERASE_LAST_IDX
 * @value 2U
 * @resolution -
 * @brief Last index for marker on workflash erase.
 */
#define MAKER_ON_WORK_ERASE_LAST_IDX (2U)
 
/**
 * @def MAGIC_WORD_SOUND_VP_BASE_ADDRESS_MAIN
 * @value 2U
 * @resolution -
 * @brief addr base of magic word sound, vp main on workflash.
 */
#define MAGIC_WORD_SOUND_VP_BASE_ADDRESS_MAIN (0x1403FE84U)
 
/**
 * @def MAGIC_WORD_SOUND_VP_BASE_ADDRESS_BACKUP
 * @value 2U
 * @resolution -
 * @brief addr base of magic word sound, vp backup on workflash.
 */
#define MAGIC_WORD_SOUND_VP_BASE_ADDRESS_BACKUP (0x1403FF04U)
 
/**
 * @def MAGIC_WORD_UCOM_LENGTH
 * @value 4U
 * @resolution -
 * @brief length magic word of ucom on workflash.
 */
#define MAGIC_WORD_UCOM_LENGTH (4U)
 
/**
 * @def MAGIC_WORD_SOUND_LENGTH
 * @value 4U
 * @resolution -
 * @brief length magic word of sound on workflash.
 */
#define MAGIC_WORD_SOUND_LENGTH (4U)
 
/**
 * @def MAGIC_WORD_VP_LENGTH
 * @value 4U
 * @resolution -
 * @brief length magic word of vp on workflash.
 */
#define MAGIC_WORD_VP_LENGTH (4U)
 
/**
 * @def MAGIC_WORD_SOUND_VP_LENGTH
 * @value 8U
 * @resolution -
 * @brief length magic word of sound + vp on workflash.
 */
#define MAGIC_WORD_SOUND_VP_LENGTH (MAGIC_WORD_SOUND_LENGTH + MAGIC_WORD_VP_LENGTH)
 
/**
 * @def MAKER_ON_WORK_SIZE
 * @value 0x4U
 * @resolution -
 * @brief Size of the marker on workflash.
 */
#define MAKER_ON_WORK_SIZE (0x4U)
/**
 * @def MAGIC_WORD_BANK_A
 * @value 0xAAU
 * @resolution -
 * @brief Magic word for Flash Bank A.
 */
#define MAGIC_WORD_BANK_A               (0xAAU)
/**
 * @def MAGIC_WORD_BANK_B
 * @value 0xBBU
 * @resolution -
 * @brief Magic word for Flash Bank B.
 */
#define MAGIC_WORD_BANK_B               (0xBBU)
/**
 * @def MATCHED_ACTIVE_BANK
 * @value 1U
 * @resolution -
 * @brief Status indicating the active bank matches expectation.
 */
#define MATCHED_ACTIVE_BANK (1U)
/**
 * @def UNMATCHED_ACTIVE_BANK
 * @value 0U
 * @resolution -
 * @brief Status indicating the active bank does not match expectation.
 */
#define UNMATCHED_ACTIVE_BANK (0U)
/**
 * @def ADDR_MAKER_ON_WORK
 * @value 0x1403FE80U
 * @resolution -
 * @brief Address of the primary marker on workflash.
 */
#define ADDR_MAKER_ON_WORK            (0x1403FE80U)
/**
 * @def ADDR_BACKUP_MAKER_ON_WORK
 * @value 0x1403FF00U
 * @resolution -
 * @brief Address of the backup marker on workflash.
 */
#define ADDR_BACKUP_MAKER_ON_WORK     (0x1403FF00U)
 
/**
 * @def SECURE_NO_CLEAR_REQUEST
 * @value 0x00000000U
 * @resolution -
 * @brief Secure request code for no clear operation.
 */
#define SECURE_NO_CLEAR_REQUEST                     (0x00000000U)
/**
 * @def SECURE_CLEAR_KEY_BEFORE_RMA_REQUEST
 * @value 0x01000000U
 * @resolution -
 * @brief Secure request code to clear key before RMA.
 */
#define SECURE_CLEAR_KEY_BEFORE_RMA_REQUEST         (0x01000000U)
/**
 * @def SECURE_SET_CLK_HF0_100MHZ
 * @value 0x02000000U
 * @resolution -
 * @brief Secure request code to set HF0 clock to 100MHz.
 */
#define SECURE_SET_CLK_HF0_100MHZ                   (0x02000000U)
/**
 * @def SECURE_RESTORE_HF0_CLOCK_TO_ORIGINAL
 * @value 0x03000000U
 * @resolution -
 * @brief Secure request code to restore HF0 clock to original frequency.
 */
#define SECURE_RESTORE_HF0_CLOCK_TO_ORIGINAL        (0x03000000U)
 
/**
 * @def SECURE_CM0_RESPONSE_E_OK
 * @value 0x00010000U
 * @resolution -
 * @brief Secure CM0+ response code for success.
 */
#define SECURE_CM0_RESPONSE_E_OK                    (0x00010000U)
/**
 * @def SECURE_CM0_RESPONSE_E_NOT_OK
 * @value 0x00020000U
 * @resolution -
 * @brief Secure CM0+ response code for failure.
 */
#define SECURE_CM0_RESPONSE_E_NOT_OK                (0x00020000U)
 
/**
 * @def KEY_AREA_WORKFLASH_ERASE_LAST_IDX
 * @value 248U
 * @resolution -
 * @brief Last index for key area WorkFlash erase (Size 0x7C00UL).
 */
#define KEY_AREA_WORKFLASH_ERASE_LAST_IDX (248U) /* Size 0x7C00UL */
/**
 * @def KEY_AREA_WORKFLASH_ERASE_START_ADDR
 * @value 0x14030300U
 * @resolution -
 * @brief Start address for key area WorkFlash erase.
 */
#define KEY_AREA_WORKFLASH_ERASE_START_ADDR (0x14030300U)
 
/* The SRAM address for Integrity status */
/**
 * @def SRAM_CM0_CM7_INTEGRITY
 * @value (*((volatile uint32*)0x28013FE0U))
 * @resolution -
 * @brief SRAM address for CM0+ and CM7 integrity status.
 */
#define SRAM_CM0_CM7_INTEGRITY                   (*((volatile uint32*)0x28013FE0U))
 
/**
 * @def SRAM_CM0_CM7_KEY_INFO_BASE
 * @value (*((volatile unsigned int*)0x28013FE8U))
 * @resolution -
 * @brief Base SRAM address for CM0+ and CM7 Keys information: SHE Key 4, TypeX, MAC Key
 * 0x28013FE8 SHE key 4 information
 * 0x28013FE9 MAC key information
 * 0x28013FEB TypeX key information
 */
#define SRAM_CM0_CM7_KEY_INFO_BASE (*((volatile unsigned int*)0x28013FE8U))
 
  
/**
 * @def SRAM_CM0_CM7_KEY_INFO_SHE_KEY_4
 * @value (*((volatile unsigned char*)0x28013FE8U))
 * @resolution -
 * @brief SRAM address for CM0+ and CM7 Key information: SHE Key 4
 */
#define SRAM_CM0_CM7_KEY_INFO_SHE_KEY_4 (*((volatile unsigned char*)0x28013FE8U))
 
/**
 * @def SRAM_CM0_CM7_KEY_INFO_MAC_KEY
 * @value (*((volatile unsigned char*)0x28013FE9U))
 * @resolution -
 * @brief Base SRAM address for CM0+ and CM7 Key information: MAC Key
 */
#define SRAM_CM0_CM7_KEY_INFO_MAC_KEY (*((volatile unsigned char*)0x28013FE9U))
 
/**
 * @def SRAM_CM0_CM7_KEY_INFO_TYPE_X
 * @value (*((volatile unsigned char*)0x28013FEBU))
 * @resolution -
 * @brief Base SRAM address for CM0+ and CM7 Key information: TypeX
 */
#define SRAM_CM0_CM7_KEY_INFO_TYPE_X (*((volatile unsigned char*)0x28013FEBU))
 
/**
 * @def KEY_INFOR_THE_UNKNOWN_KEY_INIT
 * @value 0x00000000u
 * @resolution -
 * @brief Initial state for an unknown key of SHE key 4 information,
 * TypeX key information, MAC key information
 */
#define KEY_INFOR_THE_UNKNOWN_KEY_INIT   (0x00000000u)
 
/**
 * @def REPROGRAM_THE_DEVELOPMENT_KEY
 * @value 0x01u
 * @resolution -
 * @brief Reprogramming state for a development key.
 */
#define REPROGRAM_THE_DEVELOPMENT_KEY   (0x01u)
 
/**
 * @def REPROGRAM_THE_PRODUCTION_KEY_A
 * @value 0x02u
 * @resolution -
 * @brief Reprogramming state for a development key A.
 */
#define REPROGRAM_THE_PRODUCTION_KEY_A  (0x02u)
 
/**
 * @def REPROGRAM_THE_PRODUCTION_KEY_B
 * @value 0x03u
 * @resolution -
 * @brief Reprogramming state for a development key B and lifeCycleStage is NORMAL.
 */
#define REPROGRAM_THE_PRODUCTION_KEY_B_AND_NORMAL_STAGE  (0x03u)
 
/**
 * @def REPROGRAM_THE_PRODUCTION_KEY_B
 * @value 0x04u
 * @resolution -
 * @brief Reprogramming state for a development key B and lifeCycleStage is SECURE.
 */
#define REPROGRAM_THE_PRODUCTION_KEY_B_AND_SECURE_STAGE  (0x04u)
 
/**
 * @def REPROGRAM_PLAIN_CYPHER_TEXT_LENGTH
 * @value 16u
 * @resolution -
 * @brief Length of plaintext/ciphertext for reprogramming operations.
 */
#define REPROGRAM_PLAIN_CYPHER_TEXT_LENGTH (16u)
 
/**
 * @def SHEKEY4_IS_KEYVALUECHANGED
 * @value 0x01U
 * @resolution -
 * @brief Flag indicating SHE key 4 value has changed.
 */
#define SHEKEY4_IS_KEYVALUECHANGED      (0x01U)
 
/**
 * @def SHEKEY4_IS_KEYVALIDSET
 * @value 0x02U
 * @resolution -
 * @brief Flag indicating SHE key 4 validity has been set.
 */
#define SHEKEY4_IS_KEYVALIDSET          (0x02U)
 
/**
 * @def SHEKEY4_IS_KEYWRITINGSUCCESS
 * @value 0x03U
 * @resolution -
 * @brief Flag indicating SHE key 4 writing was successful.
 */
#define SHEKEY4_IS_KEYWRITINGSUCCESS    (0x03U)
 
/**
 * @def TYPEX_IS_UNKNOWN_KEY
 * @value 0x00u
 * @resolution -
 * @brief Status flag indicating key type is unknown or not determined
 */
#define TYPEX_IS_UNKNOWN_KEY (0x00u)
 
/**
 * @def TYPEX_IS_DEVELOPMENT_KEY
 * @value 0x01u
 * @resolution -
 * @brief Status flag indicating key is a development key
 */
#define TYPEX_IS_DEVELOPMENT_KEY (0x01u)
 
/**
 * @def TYPEX_IS_PRODUCTION_KEY
 * @value 0x02u
 * @resolution -
 * @brief Status flag indicating key is a production key
 */
#define TYPEX_IS_PRODUCTION_KEY (0x02u)
 
/**
 * @def TYPEXCOMMONKEY_PLAIN_CIPHER_TEXT_LENGTH
 * @value 16u
 * @resolution -
 * @brief Length of plain or cipher text for TypeX common key operations in bytes
 */
#define TYPEXCOMMONKEY_PLAIN_CIPHER_TEXT_LENGTH (16u)
 
/**
 * @def TYPEX_KEYVALUECHANGED
 * @value 0x01U
 * @resolution -
 * @brief Flag indicating key value has been changed
 */
#define TYPEX_KEYVALUECHANGED (0x01U)
 
/**
 * @def TYPEX_KEYVALIDSET
 * @value 0x02U
 * @resolution -
 * @brief Flag indicating key validity has been set
 */
#define TYPEX_KEYVALIDSET (0x02U)
 
/**
 * @def TYPEX_KEYWRITINGSUCCESS
 * @value (TYPEX_KEYVALUECHANGED | TYPEX_KEYVALIDSET)
 * @resolution -
 * @brief Combined flag indicating successful key writing operation (value changed and validity set)
 */
#define TYPEX_KEYWRITINGSUCCESS (TYPEX_KEYVALUECHANGED | TYPEX_KEYVALIDSET)
 
/**
 * @def MASTER_ECU_KEYVALUECHANGED
 * @value 0x01U
 * @resolution -
 * @brief Flag indicating key value has been changed
 */
#define MASTER_ECU_KEYVALUECHANGED (0x01U)
 
/**
 * @def MASTER_ECU_KEYVALIDSET
 * @value 0x02U
 * @resolution -
 * @brief Flag indicating key validity has been set
 */
#define MASTER_ECU_KEYVALIDSET (0x02U)
 
/**
 * @def MASTER_ECU_KEY_WRITING_SUCCESS
 * @value (MASTER_ECU_KEYVALUECHANGED | MASTER_ECU_KEYVALIDSET)
 * @resolution -
 * @brief Combined flag indicating successful key writing operation (value changed and validity set)
 */
#define MASTER_ECU_KEY_WRITING_SUCCESS          (MASTER_ECU_KEYVALUECHANGED | MASTER_ECU_KEYVALIDSET)
 
/**
 * @def MAC_KEY_IS_UNWRITTEN_KEY
 * @value 0x01u
 * @resolution -
 * @brief Status flag indicating key is a unwritten key
 */
#define MAC_KEY_IS_UNWRITTEN_KEY (0x01u)
 
/**
 * @def MAC_KEY_IS_DEVELOPMENT_KEY
 * @value 0x02u
 * @resolution -
 * @brief Status flag indicating key is a development key
 */
#define MAC_KEY_IS_DEVELOPMENT_KEY (0x02u)
 
/**
 * @def MAC_KEY_IS_PRODUCTION_KEY
 * @value 0x03u
 * @resolution -
 * @brief Status flag indicating key is a production key
 */
#define MAC_KEY_IS_PRODUCTION_KEY (0x03u)
 
/**
 * @def MAC_KEY_IN_OUT_TEXT_LENGTH
 * @value 16u
 * @resolution -
 * @brief Length of data and MAC generated text in bytes
 */
#define MAC_KEY_IN_OUT_TEXT_LENGTH (16u)
 
/**
 * @def MAC_KEY_KEYVALUECHANGED
 * @value 0x01U
 * @resolution -
 * @brief Flag indicating key value has been changed
 */
#define MAC_KEY_KEYVALUECHANGED (0x01U)
 
/**
 * @def MAC_KEY_KEYVALIDSET
 * @value 0x02U
 * @resolution -
 * @brief Flag indicating key validity has been set
 */
#define MAC_KEY_KEYVALIDSET (0x02U)
 
/**
 * @def MAC_KEY_WRITING_SUCCESS
 * @value (MAC_KEY_KEYVALUECHANGED | MAC_KEY_KEYVALIDSET)
 * @resolution -
 * @brief Combined flag indicating successful key writing operation (value changed and validity set)
 */
#define MAC_KEY_WRITING_SUCCESS             (MAC_KEY_KEYVALUECHANGED | MAC_KEY_KEYVALIDSET)
 
/**
 * @def CM7_NOT_STARTED
 * @value 0x00U
 * @resolution -
 * @brief Flag indicating core CM7 has not yet started up
 */
#define CM7_NOT_STARTED (0x00u)
 
/**
 * @def CM7_STARTUP_COMPTELE
 * @value 0xAAU
 * @resolution -
 * @brief Flag indicating core CM7 startup has been completed
 */
#define CM7_STARTUP_COMPTELE (0xAAu)
 
/**
 * @def SRAM_CM0_CM7_CM7_STARTUP_STATE
 * @value (*((volatile uint8*)0x28013FECU))
 * @resolution -
 * @brief SRAM address for sharing CM7_Startup state between CM0+ and CM7
 */
#define SRAM_CM0_CM7_CM7_STARTUP_STATE (*((volatile uint8*)0x28013FECU))
 
/**
 * @def SHE_CIDKEEPER_MAC_KEY_OFFSET
 * @value 0U
 * @resolution -
 * @brief Offset for the MAC key in the SHE CID keeper storage.
 */
#define SHE_CIDKEEPER_MAC_KEY_OFFSET (0U)
/**
 * @def SHE_CIDKEEPER_MASTER_KEY_OFFSET
 * @value 4U
 * @resolution -
 * @brief Offset for the Master ECU key in the SHE CID keeper storage.
 */
#define SHE_CIDKEEPER_MASTER_KEY_OFFSET (4U)
/**
 * @def SHE_CIDKEEPER_CID_SIZE
 * @value 4U
 * @resolution -
 * @brief Size of the CID in bytes for SHE keys.
 */
#define SHE_CIDKEEPER_CID_SIZE (4U)
/**
 * @def SHE_CIDKEEPER_NUM_KEYS
 * @value 2U
 * @resolution -
 * @brief Number of keys managed by the SHE CID keeper.
 */
#define SHE_CIDKEEPER_NUM_KEYS (2U)
/**
 * @def CRYPTO_30_LIBCV_MASK_SHE_M2_COUNTER
 * @value 0xFFFFFFF0u
 * @resolution -
 * @brief Mask to extract the SHE M2 counter value from a larger word.
 */
#define CRYPTO_30_LIBCV_MASK_SHE_M2_COUNTER (0xFFFFFFF0u)
/**
 * @def Crypto_30_LibCv_She_ConvertCounter
 * @value (((value) & CRYPTO_30_LIBCV_MASK_SHE_M2_COUNTER) >> 4)
 * @resolution -
 * @brief Converts a raw counter value to the SHE M2 counter format.
 */
#define Crypto_30_LibCv_She_ConvertCounter(value) (((value) & CRYPTO_30_LIBCV_MASK_SHE_M2_COUNTER) >> 4)
 
/**
 * @def CM0P_SCS_BASE
 * @value 0xE000E000u
 * @resolution -
 * @brief Base address for the Cortex-M0+ System Control Space (SCS).
 */
#define CM0P_SCS_BASE                 (0xE000E000u)
/**
 * @def CM0P_SCS_IPR(x)
 * @value REG(uint32, CM0P_SCS_BASE, 0x400u + (x * 4u))
 * @resolution -
 * @brief Macro to access Cortex-M0+ SCS Interrupt Priority Registers.
 */
#define CM0P_SCS_IPR(x)               REG(uint32, CM0P_SCS_BASE, 0x400u + (x * 4u)) //0-7
/**
 * @def CM0P_SCS_ISER
 * @value REG(uint32, CM0P_SCS_BASE, 0x100u)
 * @resolution -
 * @brief Macro to access Cortex-M0+ SCS Interrupt Set-Enable Register.
 */
#define CM0P_SCS_ISER                 REG(uint32, CM0P_SCS_BASE, 0x100u)
/**
 * @def CM0P_SCS_ICSR
 * @value REG(uint32, CM0P_SCS_BASE, 0xD04u)
 * @resolution -
 * @brief Macro to access Cortex-M0+ SCS Interrupt Control and State Register.
 */
#define CM0P_SCS_ICSR                 REG(uint32, CM0P_SCS_BASE, 0xD04u)
/**
 * @def CM0P_SCS_VTOR
 * @value REG(uint32, CM0P_SCS_BASE, 0xD08u)
 * @resolution -
 * @brief Macro to access Cortex-M0+ SCS Vector Table Offset Register.
 */
#define CM0P_SCS_VTOR                 REG(uint32, CM0P_SCS_BASE, 0xD08u)
 
/**
 * @def CPUSS_CM0_SYSTEM_INT_CTL(x)
 * @value REG(uint32, CPUSS_BASE, 0x8000u + (x * 4u))
 * @resolution -
 * @brief Macro to access CPUSS CM0+ System Interrupt Control registers.
 */
#define CPUSS_CM0_SYSTEM_INT_CTL(x)   REG(uint32, CPUSS_BASE, 0x8000u + (x * 4u)) //0-352
/**
 * @def CPUSS_CM0_INT_STATUS(x)
 * @value REG(uint32, CPUSS_BASE, 0x1100u + (x * 4u))
 * @resolution -
 * @brief Macro to access CPUSS CM0+ Interrupt Status registers.
 */
#define CPUSS_CM0_INT_STATUS(x)       REG(uint32, CPUSS_BASE, 0x1100u + (x * 4u)) //0-7
/**
 * @def      SILICON_ID_TYPE
 * @value    0x01u
 * @resolution -
 * @brief    Identifier for the silicon ID type.
 */
#define SILICON_ID_TYPE (0x01u)
/**
 * @def      LIFE_CYCLE_STATE_UNDEFINE
 * @value    0XFFu
 * @resolution -
 * @brief    Value representing an undefined or unknown lifecycle state.
 */
#define LIFE_CYCLE_STATE_UNDEFINE (0XFFu)
/**
 * @def      PROTECTION_STATE_UNDEFINE
 * @value    0XFFu
 * @resolution -
 * @brief    Value representing an undefined or unknown protection state.
 */
#define PROTECTION_STATE_UNDEFINE (0XFFu)
 
#define SRAM_CM0_CM7_STEP_RECORD   (*((volatile uint32 *)0x28013FD8U))
#define SRAM_CM0_CM7_CM7_STARTUP_STATE_SHARED   (*((volatile uint8 *)0x28013FD4U))
#define SRAM_CM0_CM7_ISBOOTOK_FLG0        (*((volatile uint8 *)0x28013FCCU))
#define SRAM_CM0_CM7_ISBOOTOK_FLG1        (*((volatile uint8 *)0x28013FCDU))
#define SRAM_CM0_CM7_ISBOOTOK_FLG2        (*((volatile uint8 *)0x28013FCEU))
#define SRAM_CM0_CM7_ISBOOTOK_FLG3        (*((volatile uint8 *)0x28013FCFU))
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
 
/**
 * @type uint32
 * @var Exterrnal_Clear_Rma_Request
 * @brief Stores an external request for clearing RMA (Return Material Authorization) related data.
 * @unit -
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0        |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:----------:|:---:|:---:|:---:|:---:|
 * |- |-    |-    |-    |-    |
 */
static uint32 Exterrnal_Clear_Rma_Request = SECURE_NO_CLEAR_REQUEST;
/**
 * @type boolean
 * @var DAP_isPwAuthen
 * @brief Flag indicating if the password for Debug Access Port (DAP) has been successfully authenticated.
 * @unit -
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0    |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:------:|:---:|:---:|:---:|:---:|
 * |-   |-    |-    |-    |-    |
 */
static boolean DAP_isPwAuthen = FALSE; /* Flag the password has been successfully authenticated */
/**
 * @type const uint8[]
 * @var Dap_EPH
 * @brief Hardcoded array containing the correct hashed password for DAP.
 * @unit byte
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0                         |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:--------------------------:|:---:|:---:|:---:|:---:|
 * |DAP_CORRECT_HASHED_PASSWORD |-    |-    |-    |-    |
 */
static const uint8 Dap_EPH[HASH_DAP_LENGTH] = DAP_CORRECT_HASHED_PASSWORD;  /* Hard Code - Hashed Password DAP */
/**
 * @type uint8[]
 * @var Dap_User_Buffer
 * @brief Buffer to store password from user, random number from CM0+, and encrypted random number from user for DAP.
 * @unit byte
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0    |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:------:|:---:|:---:|:---:|:---:|
 * |-   |-    |-    |-    |-    |
 */
static uint8 Dap_User_Buffer[PASSWORD_DAP_LENGTH] = {0U}; /* Buffer to store password from User, Random number from CM0, Encrypted random number from User */
/**
 * @type uint8
 * @var Repro_KeyCalloutStatus
 * @brief Status variable for key reprogramming callout.
 * @unit -
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:---:|:---:|:---:|:---:|:---:|
 * |-   |-    |-    |-    |-    |
 */
static uint8 Repro_KeyCalloutStatus = 0u;
/**
 * @type uint8
 * @var Repro_KeyCalloutStatus
 * @brief Status variable for key TypeX callout.
 * @unit -
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:---:|:---:|:---:|:---:|:---:|
 * |-   |-    |-    |-    |-    |
 */
static uint8 TypeX_KeycalloutStatus = 0u;
/**
 * @type uint8
 * @var Mac_KeyCalloutStatus
 * @brief Flag indicating successful writing of the MAC key.
 * @unit -
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0    |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:------:|:---:|:---:|:---:|:---:|
 * |-|-    |-    |-    |-    |
 */
static uint8 Mac_KeyCalloutStatus = 0u;     /* Flag the write MAC key successfully */
/**
 * @type uint8
 * @var Master_KeyCalloutStatus
 * @brief Flag indicating successful writing of the Master ECU key.
 * @unit -
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0    |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:------:|:---:|:---:|:---:|:---:|
 * |-|-    |-    |-    |-    |
 */
static uint8 Master_KeyCalloutStatus = 0u;  /* Flag the write Master ECU key successfully */
/**
 * @type Crypto_30_LibCv_KeyStorageType[]
 * @var SheKeyStorage
 * @brief Buffer to store CID (Chip ID) of MAC key and Master ECU key.
 * @unit -
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0                                  |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:---:|:---:|:---:|:---:|:---:|
 * |-|-    |-    |-    |-    |
 */
static Crypto_30_LibCv_KeyStorageType SheKeyStorage[ARRAY_SIZE_8BYTE];  /* Buffer to store CID of MAC key and Master ECU key*/
 
/**
 * @type uint8[]
 * @var Repro_CipherTextProductKey
 * @brief Defines the CipherText for AES-128-CBC decryption using the Production Key.
 * @unit -
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:---:|:---:|:---:|:---:|:---:|
 * |-|-    |-    |-    |-    |
 */
 
static const uint8 Repro_CipherTextProductKey[REPROGRAM_PLAIN_CYPHER_TEXT_LENGTH] = { 0x5Au, 0x0Du, 0xB5u, 0xC3u, 0x87u, 0x71u, 0x84u, 0xFCu, 0x4Fu, 0x8Au, 0x5Au, 0xA2u, 0x37u, 0xF6u, 0x7Bu, 0x3Eu };
 
/**
 * @type uint8[]
 * @var Repro_PlainTextProductKeyA
 * @brief Defines the PlainText for AES-128-CBC encryption using the "PRODUCTION_KEY_A".
 * @unit -
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:---:|:---:|:---:|:---:|:---:|
 * |-|-    |-    |-    |-    |
 */
#if 0 /* The stub code remains for testing purposes. */
/* key value stub: 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11 */
static const uint8 Repro_PlainTextProductKeyA[REPROGRAM_PLAIN_CYPHER_TEXT_LENGTH] = { 0x51u, 0xE1u, 0x8Fu, 0x0Cu, 0x2Cu, 0x7Du, 0x22u, 0x6Eu, 0x43u, 0xBAu, 0xE5u, 0xD0u, 0x1Bu, 0xAAu, 0x6Du, 0xE8u };
#else
/* production key A */
static const uint8 Repro_PlainTextProductKeyA[REPROGRAM_PLAIN_CYPHER_TEXT_LENGTH] = { 0x8Cu, 0xD3u, 0x5Du, 0x49u, 0x23u, 0xC4u, 0x65u, 0x47u, 0x6Bu, 0x8Fu, 0x0Cu, 0xC0u, 0xB3u, 0x54u, 0xC9u, 0x95u };
#endif
/**
 * @type uint8[]
 * @var Repro_PlainTextProductKeyB
 * @brief Defines the PlainText for AES-128-CBC encryption using the "PRODUCTION_KEY_B".
 * @unit -
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:---:|:---:|:---:|:---:|:---:|
 * |-|-    |-    |-    |-    |
 */
#if 0 /* The stub code remains for testing purposes. */
/* key value stub: 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22 */
static const uint8 Repro_PlainTextProductKeyB[REPROGRAM_PLAIN_CYPHER_TEXT_LENGTH] = { 0x7Du, 0xF8u, 0x23u, 0x59u, 0x74u, 0xC0u, 0x5Au, 0x80u, 0x93u, 0x29u, 0x09u, 0xB0u, 0x98u, 0x9Du, 0x6Fu, 0x04u };
#else
/* production key B */
static const uint8 Repro_PlainTextProductKeyB[REPROGRAM_PLAIN_CYPHER_TEXT_LENGTH] = { 0xDDu, 0x14u, 0x60u, 0x72u, 0xD0u, 0xA7u, 0x7Cu, 0x47u, 0x67u, 0xFBu, 0x7Fu, 0x7Cu, 0xB2u, 0xD7u, 0x17u, 0x85u };
#endif
/**
 * @type uint8[]
 * @var g_TypeX_PlainText
 * @brief Defines the PlainText for TypeX Key.
 * @unit -
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:---:|:---:|:---:|:---:|:---:|
 * |-|-    |-    |-    |-    |
 */
static const uint8 g_TypeX_PlainText[ARRAY_SIZE_16BYTE] = {0xD8u, 0x10u, 0x5Bu, 0xC1u, 0x76u, 0x24u, 0xD9u, 0x82u, 0x62u, 0xFEu, 0xBDu, 0x67u, 0x9Fu, 0xBCu, 0xDFu, 0x95u}; /* The plaintext used for TypeX Common Key determination */
/**
 * @type uint8[]
 * @var g_TypeX_CipherText
 * @brief Defines the CipherText for TypeX Key.
 * @unit -
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:---:|:---:|:---:|:---:|:---:|
 * |-|-    |-    |-    |-    |
 */
static const uint8 g_TypeX_CipherText[ARRAY_SIZE_16BYTE] = {0x34u, 0x9Fu, 0x4Fu, 0x41u, 0x5Du, 0x7Du, 0xD9u, 0x6Bu, 0x06u, 0xFCu, 0x27u, 0x5Eu, 0x26u, 0x02u, 0xFCu, 0x59u}; /* The cyphertext of g_TypeX_PlainText (encrypted with DEVELOPMENT key) used for TypeX Common Key determination */
 
/**
 * @type uint8[]
 * @var Mac_Data
 * @brief Defines the Mac data input for MAC generation key
 * @unit -
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:---:|:---:|:---:|:---:|:---:|
 * |-|-    |-    |-    |-    |
 */
static const uint8 Mac_Data[ARRAY_SIZE_16BYTE] = {0xE7u, 0xFBu, 0x58u, 0x02u, 0x0Cu, 0xE6u, 0xE8u, 0x34u, 0x82u, 0x90u, 0xC0u, 0xBCu, 0x3Cu, 0x04u, 0x37u, 0x5Cu};
 
/**
 * @type uint8[]
 * @var Mac_Dev_Verify
 * @brief Defines the Mac Development verify for MAC key
 * @unit -
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:---:|:---:|:---:|:---:|:---:|
 * |-|-    |-    |-    |-    |
 */
static const uint8 Mac_Dev_Verify[ARRAY_SIZE_16BYTE] = {0xFAu, 0x84u, 0x54u, 0x00u, 0xF9u, 0x02u, 0xE4u, 0x4Au, 0xC0u, 0x38u, 0x94u, 0xE0u, 0xB4u, 0x3Au, 0xE5u, 0x41u};
 
/**
 * @type uint8[]
 * @var Mac_Full0_Verify
 * @brief Defines the Mac Full 0 key verify for MAC key
 * @unit -
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:---:|:---:|:---:|:---:|:---:|
 * |-|-    |-    |-    |-    |
 */
static const uint8 Mac_Full0_Verify[ARRAY_SIZE_16BYTE] = {0x9Du, 0xA9u, 0x01u, 0x3Fu, 0x52u, 0xF3u, 0x01u, 0x6Au, 0x0Bu, 0x48u, 0x81u, 0xEBu, 0x0Fu, 0xFAu, 0x15u, 0xC3u};
 
/**
 * @type uint8
 * @var ISR1_Handler_TriggerFlag
 * @brief This variable is used for tracking ISR1_Handler.
 * @unit -
 * @scope Global Variable
 * @section -
 * @par Initial setting
 * |RAM0        |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:----------:|:---:|:---:|:---:|:---:|
 * |- |-    |-    |-    |-    |
 */
uint8 ISR1_Handler_TriggerFlag;
 
/**
 * @type volatile unsigned long
 * @var intSleep
 * @brief Status variable indicating sleep state, controlled by IPC messages.
 * @unit -
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0        |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:----------:|:---:|:---:|:---:|:---:|
 * |- |-    |-    |-    |-    |
 */
static volatile unsigned long intSleep = 0x00000000U;
/**
 * @type uint8[]
 * @var dap_R
 * @brief Buffer to store random number for DAP authentication.
 * @unit byte
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:---:|:---:|:---:|:---:|:---:|
 * |- |-    |-    |-    |-    |
 */
static uint8 dap_R[ARRAY_SIZE_16BYTE] = {0u};
/**
 * @type uint8[]
 * @var bank_write
 * @brief Array containing magic words for writing to workflash, indicating bank status.
 * @unit -
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0                                    |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:--------------------------------------:|:---:|:---:|:---:|:---:|
 * |-|-    |-    |-    |-    |
 */
static uint8 bank_write[MAKER_ON_WORK_SIZE] = {MAGIC_WORD_BANK_A, MAGIC_WORD_BANK_A, MAGIC_WORD_BANK_A, MAGIC_WORD_BANK_A};
/**
 * @type uint8[]
 * @var version_write
 * @brief Array storing the current memory layout version to be written to flash.
 * @unit -
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0                                                                               |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:----------------------------------------------------------------------------------:|:---:|:---:|:---:|:---:|
 * |-|-    |-    |-    |-    |
 */
static uint8 version_write[WORKFLASH_FLAG_SIZE] __ALIGNED(32) = {LAYOUT_MAJOR_0, LAYOUT_MAJOR_1, LAYOUT_MINOR_0, LAYOUT_MINOR_1, \
                                                                  LAYOUT_RELEASE_0, LAYOUT_RELEASE_1, LAYOUT_PATCH_0, LAYOUT_PATCH_1};
/**
 * @type uint8[]
 * @var version_read
 * @brief Buffer to read the memory layout version from flash.
 * @unit -
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:---:|:---:|:---:|:---:|:---:|
 * |- |-    |-    |-    |-    |
 */
static uint8 version_read[WORKFLASH_FLAG_SIZE] __ALIGNED(32) = {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u};
/**
 * @type uint8[]
 * @var getSeed
 * @brief Buffer to store the generated seed.
 * @unit -
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:---:|:---:|:---:|:---:|:---:|
 * |- |-    |-    |-    |-    |
 */
static uint8 getSeed[ARRAY_SIZE_16BYTE] = { 0u };
 
/**
 * @type uint16
 * @var ResetCounter
 * @brief Counter for system resets, used by DualBankManager.
 * @unit -
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:---:|:---:|:---:|:---:|:---:|
 * |-    |-    |- |-    |-    |
 */
__attribute__ ((section(".SRAM0_Retention"))) /* 0x28007FF0 */ /* DualBankManager - RESET_COUNTER_VAR */
uint16 ResetCounter;
/**
 * @type uint16
 * @var Dummy_Padding1
 * @brief Padding variable for memory allocation in SRAM0_Retention section.
 * @unit -
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:---:|:---:|:---:|:---:|:---:|
 * |-    |-    |- |-    |-    |
 */
__attribute__ ((section(".SRAM0_Retention"))) /* 0x28007FF2 */ /* DualBankManager - SWITCHBANK_STATUS */
/* QAC Deviations: (No 3211) This is padding number for memory allocation. This warning no affect to the behavior. */
uint16 Dummy_Padding1;
/**
 * @type uint16
 * @var AppStatus
 * @brief Status variable for the application, used by DualBankManager.
 * @unit -
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:---:|:---:|:---:|:---:|:---:|
 * |-    |-    |- |-    |-    |
 */
__attribute__ ((section(".SRAM0_Retention"))) /* 0x28007FF4 */ /* DualBankManager - APP_STATUS_VAR */
uint16 AppStatus;
/**
 * @type uint16
 * @var Dummy_Padding2
 * @brief Padding variable for memory allocation in SRAM0_Retention section.
 * @unit -
 * @scope Local Variable
 * @section RAM0
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:---:|:---:|:---:|:---:|:---:|
 * |-    |-    |- |-    |-    |
 */
__attribute__ ((section(".SRAM0_Retention"))) /* 0x28007FF6 */ /* DualBankManager - Reserved */
/* QAC Deviations: (No 3211) This is padding number for memory allocation. This warning no affect to the behavior. */
uint16 Dummy_Padding2;
 
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
static FUNC(Std_ReturnType, CRYPTO_30_LIBCV_CODE) Security_SheKeyGetSheIndex(
  Crypto_30_LibCv_SizeOfKeyElementsType elementIndex,
  P2VAR(Crypto_30_LibCv_SizeOfSheKeysType, AUTOMATIC, AUTOMATIC) indexSheKeyPtr);
static void Security_ProcessCidSaveToNvm(void);
static void Security_ProcessCidRestoreFromNvm(void);
static Std_ReturnType Security_HandleReadStage(uint8 *lifeCycleState, uint8 *protectionState);
static void Security_SheKey4Info_Processing(void);
static void Security_TypeXCommonKeyInfo_Processing(void);
static void Security_KeyInfoInitializationAndProcessing(void);
static void vHsm_CM7_Startup_Check(volatile stc_MCWDT_t *base);
static void vHsm_WatchdogTimerInit(volatile stc_MCWDT_t *base);
static void Security_DAPHandler(uint32 dap_Status);
static FUNC(boolean, VHSM_CODE) handleApplVerificationStatus(void);
 
#if (MEM_MAGIC_FLAG == STD_ON)
static FUNC(void, VHSM_CODE) vHsm_MasterKeyIsValid(void);
static FUNC(void, VHSM_CODE) updateDualBankMagicWord(void);
static FUNC(void, VHSM_CODE) vHsm_HandleMemoryLayoutVersion(void);
#endif /*(MEM_MAGIC_FLAG == STD_ON)*/
 
static FUNC(boolean, VHSM_CODE) check_cm7_sleep_status(void);
static FUNC(void, VHSM_CODE) cm0p_cache_off(void);
static FUNC(void, VHSM_CODE) cm0p_cache_on(void);
static FUNC(void, VHSM_CODE) switch_regulator_sleep_entry(void);
static FUNC(void, VHSM_CODE) switch_regulator_sleep_exit(void);
static FUNC(void, VHSM_CODE) crypto_hw_disable(void);
static FUNC(void, VHSM_CODE) crypto_hw_enable(void);
 
/**********************************************************************************************************************
 *  FUNCTIONS Definition
 *********************************************************************************************************************/
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32_t |cycles |Number of CPU cycles to delay. |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |void |- |No return value. |
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
 * @brief Delays execution for a specified number of CPU cycles.
 * @note This is a stub function that currently performs no operation. In a full implementation,
 * it would introduce a delay of 'cycles' CPU clock cycles.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
void Cy_SysLib_DelayCycles(uint32_t cycles){
 
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
 * |uint32_t |savedIntrStatus |Returns a value representing the interrupt status before entering the critical section. |
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
 * @brief Enters a critical section by disabling interrupts.
 * @note This is a stub function that currently returns 0. In a full implementation,
 * it would disable interrupts and return the previous interrupt status to be
 * restored by `Cy_SysLib_ExitCriticalSection`.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
uint32_t Cy_SysLib_EnterCriticalSection(void){
  return 0u;
}
 
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32_t |savedIntrStatus |The interrupt status to restore, typically obtained from `Cy_SysLib_EnterCriticalSection`. |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |void |- |No return value. |
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
 * @brief Exits a critical section by restoring the previous interrupt status.
 * @note This is a stub function that currently performs no operation. In a full implementation,
 * it would restore the interrupt status to the value provided by `savedIntrStatus`.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
void Cy_SysLib_ExitCriticalSection(uint32_t savedIntrStatus){
 
}
 
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |Crypto_30_LibCv_SizeOfKeyElementsType |elementIndex |Index of the key element to search for. |
 * |Crypto_30_LibCv_SizeOfSheKeysType* |indexSheKeyPtr |Pointer to store the found SHE key index. |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |Std_ReturnType |retVal |E_OK if the SHE key index is found; E_NOT_OK otherwise. |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |Crypto_30_LibCv_SizeOfSheKeysType* |indexSheKeyPtr |Updated with the SHE key index if found. |
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
 * |Crypto_30_LibCv_SheKeysIterType |i |Loop counter for iterating through SHE keys. |
 * @brief Retrieves the SHE key index based on the provided key element index.
 * @note This function iterates through the list of SHE keys to find a match for the given
 * `elementIndex`. If a match is found, the corresponding SHE key index is stored in
 * `indexSheKeyPtr`, and `E_OK` is returned. Otherwise, `E_NOT_OK` is returned.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
static FUNC(Std_ReturnType, CRYPTO_30_LIBCV_CODE) Security_SheKeyGetSheIndex(
  Crypto_30_LibCv_SizeOfKeyElementsType elementIndex,
  P2VAR(Crypto_30_LibCv_SizeOfSheKeysType, AUTOMATIC, AUTOMATIC) indexSheKeyPtr)
{
Crypto_30_LibCv_SheKeysIterType i;
Std_ReturnType retVal = E_NOT_OK;
 
SRAM_CM0_CM7_STEP_RECORD = 75u;
/* Get index of SHE key in list. */
 for (i = 0u; i < Crypto_30_LibCv_GetSizeOfSheKeys(); i++)
{
  if (Crypto_30_LibCv_GetKeyElementsKeyIdxOfSheKeys(i) == elementIndex)
  {
    *indexSheKeyPtr = (Crypto_30_LibCv_SizeOfSheKeysType)i; /* SBSW_CRYPTO_30_LIBCV_STACK_VARIABLE_AS_PTR */ /* QAC Deviations: (No 2814) Pointer indexSheKeyPtr has been already evaluated at Security_ProcessCidRestoreFromNvm() where this function was called. */
    retVal = E_OK;
    break;
  }
}
SRAM_CM0_CM7_STEP_RECORD = 76u;
return retVal;
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
 * |void |- |No return value. |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8 |Mac_KeyCalloutStatus |Status of MAC key write operation. |
 * |uint8 |Master_KeyCalloutStatus |Status of Master ECU key write operation. |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8 |Mac_KeyCalloutStatus |Set to `E_NOT_OK` after processing if `E_OK` before. |
 * |uint8 |Master_KeyCalloutStatus |Set to `E_NOT_OK` after processing if `E_OK` before. |
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
 * |Std_ReturnType |retval |Return value from Csm_KeyElementGet. |
 * |uint32 |getKeyLength |Length of the key element to get. |
 * |boolean |dataChanged |Flag indicating if key data was changed and needs NVM write. |
 * |boolean |getMacKeyResult |Flag indicating successful retrieval of MAC key CID. |
 * |boolean |getMasterKeyResult |Flag indicating successful retrieval of Master ECU key CID. |
 * @brief Processes and saves CID (Chip ID) values of SHE keys to NVM.
 * @note This function retrieves the CID values for the MAC Key and Master ECU Key.
 */
/* author FPT*/
/* date 2024-07-24 */
/************************************************************************************************/
static void Security_ProcessCidSaveToNvm(void)
{
  Std_ReturnType retval;
  uint32 getKeyLength = SHE_CIDKEEPER_CID_SIZE;
  boolean getMacKeyResult = FALSE;
  boolean getMasterKeyResult = FALSE;
 
  /* Get CID value MAC Key */
  if (MAC_KEY_WRITING_SUCCESS == (Mac_KeyCalloutStatus & MAC_KEY_WRITING_SUCCESS))
  {
SRAM_CM0_CM7_STEP_RECORD = 170u;
    retval = Csm_KeyElementGet(
        CsmConf_CsmKey_CsmKey_She_MAC,
        CryptoConf_CryptoKeyElement_Crypto_30_LibCv_She_Counter,
        &SheKeyStorage[SHE_CIDKEEPER_MAC_KEY_OFFSET],
        &getKeyLength);
SRAM_CM0_CM7_STEP_RECORD = 171u;
    if (E_OK == retval)
    {
      getMacKeyResult = TRUE;
SRAM_CM0_CM7_STEP_RECORD = 172u;
    }
  }
 
  /* Get CID value Master ECU Key*/
  if (MASTER_ECU_KEY_WRITING_SUCCESS == (Master_KeyCalloutStatus & MASTER_ECU_KEY_WRITING_SUCCESS))
  {
    getKeyLength = SHE_CIDKEEPER_CID_SIZE;
SRAM_CM0_CM7_STEP_RECORD = 173u;
    retval = Csm_KeyElementGet(
        CsmConf_CsmKey_CsmKey_She_MasterEcuKey,
        CryptoConf_CryptoKeyElement_Crypto_30_LibCv_She_Counter,
        &SheKeyStorage[SHE_CIDKEEPER_MASTER_KEY_OFFSET],
        &getKeyLength);
SRAM_CM0_CM7_STEP_RECORD = 174u;
    if (E_OK == retval)
    {
      getMasterKeyResult = TRUE;
SRAM_CM0_CM7_STEP_RECORD = 175u;
    }
  }
 
  /* Write to NVM */
  if((getMacKeyResult == TRUE) || (getMasterKeyResult == TRUE))
  {
SRAM_CM0_CM7_STEP_RECORD = 176u;
    (void)vHsm_NvM_WriteBlock(NvMConf_NvMBlockDescriptor_Keys_Immediate_CID, SheKeyStorage);
SRAM_CM0_CM7_STEP_RECORD = 177u;
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
 * |void |- |No return value. |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |Crypto_30_LibCv_KeyStorageType[] |SheKeyStorage |Buffer containing CID values for SHE keys. |
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
 * |Std_ReturnType |retval |Return value from NVM read and key element search/set operations. |
 * |uint8 |sheIndexMac |SHE key index for the MAC key. |
 * |uint8 |sheIndexMaster |SHE key index for the Master ECU key. |
 * |Crypto_30_LibCv_SizeOfKeyElementsType |elementIndexMac |Key element index for the MAC key. |
 * |Crypto_30_LibCv_SizeOfKeyElementsType |elementIndexMaster |Key element index for the Master ECU key. |
 * @brief Restores CID (Chip ID) values of SHE keys from NVM to RAM.
 * @note This function reads the CID values for SHE keys (MAC Key and Master ECU Key) from the
 * NVM block `NvMConf_NvMBlockDescriptor_Keys_Immediate_CID`.
 */
/* author FPT */
/* date 2024-07-24 */
/************************************************************************************************/
static void Security_ProcessCidRestoreFromNvm(void)
{
  Std_ReturnType retval;
  uint8 sheIndexMac = 0U;
  uint8 sheIndexMaster = 0U;
  Crypto_30_LibCv_SizeOfKeyElementsType elementIndexMac = 0U;
  Crypto_30_LibCv_SizeOfKeyElementsType elementIndexMaster = 0U;
  Crypto_30_LibCv_KeyStorageType zero_buffer[ARRAY_SIZE_8BYTE] = {0u};
 
SRAM_CM0_CM7_STEP_RECORD = 58u;
  retval = vHsm_NvM_ReadBlock(NvMConf_NvMBlockDescriptor_Keys_Immediate_CID, SheKeyStorage);
SRAM_CM0_CM7_STEP_RECORD = 59u;
  if (E_OK != retval)
  {
SRAM_CM0_CM7_STEP_RECORD = 60u;
    (void)vHsm_NvM_WriteBlock(NvMConf_NvMBlockDescriptor_Keys_Immediate_CID, zero_buffer);
SRAM_CM0_CM7_STEP_RECORD = 61u;
    retval = vHsm_NvM_ReadBlock(NvMConf_NvMBlockDescriptor_Keys_Immediate_CID, SheKeyStorage);
SRAM_CM0_CM7_STEP_RECORD = 62u;
  }
 
  /* Proceed only if NVM read was successful */
  if (E_OK == retval)
  {
SRAM_CM0_CM7_STEP_RECORD = 63u;
    retval = Crypto_30_LibCv_Local_KeyElementSearch(
        CryptoConf_CryptoKey_She_MAC_Key,
        CryptoConf_CryptoKeyElement_Crypto_30_LibCv_Mac_Key_She,
        &elementIndexMac);
SRAM_CM0_CM7_STEP_RECORD = 64u;
    if (E_OK == retval)
    {
SRAM_CM0_CM7_STEP_RECORD = 65u;
      retval = Security_SheKeyGetSheIndex(elementIndexMac, &sheIndexMac);
SRAM_CM0_CM7_STEP_RECORD = 66u;
      if (E_OK == retval)
      {
SRAM_CM0_CM7_STEP_RECORD = 67u;
        /* Write CID from NVM to RAM Key area for MAC Key */
        (void)Crypto_30_LibCv_KeyElementSetInternalStandardWithCryptoKeyId(
            CryptoConf_CryptoKey_She_MAC_Key,
            Crypto_30_LibCv_GetKeyElementsCounterIdxOfSheKeys(sheIndexMac),
            &SheKeyStorage[SHE_CIDKEEPER_MAC_KEY_OFFSET],
            SHE_CIDKEEPER_CID_SIZE);
SRAM_CM0_CM7_STEP_RECORD = 68u;
      }
    }
SRAM_CM0_CM7_STEP_RECORD = 69u;
    retval = Crypto_30_LibCv_Local_KeyElementSearch(
        CryptoConf_CryptoKey_She_MasterEcuKey,
        CryptoConf_CryptoKeyElement_Crypto_30_LibCv_She_AES_NISTSP80038B,
        &elementIndexMaster);
SRAM_CM0_CM7_STEP_RECORD = 70u;
    if (E_OK == retval)
    {
SRAM_CM0_CM7_STEP_RECORD = 71u;
      retval = Security_SheKeyGetSheIndex(elementIndexMaster, &sheIndexMaster);
SRAM_CM0_CM7_STEP_RECORD = 72u;
      if (E_OK == retval)
      {
SRAM_CM0_CM7_STEP_RECORD = 73u;
        /* Write CID from NVM to RAM Key area for Master ECU Key */
        (void)Crypto_30_LibCv_KeyElementSetInternalStandardWithCryptoKeyId(
            CryptoConf_CryptoKey_She_MasterEcuKey,
            Crypto_30_LibCv_GetKeyElementsCounterIdxOfSheKeys(sheIndexMaster),
            &SheKeyStorage[SHE_CIDKEEPER_MASTER_KEY_OFFSET],
            SHE_CIDKEEPER_CID_SIZE);
SRAM_CM0_CM7_STEP_RECORD = 74u;
      }
    }
  }
}
 
/************************************************************************************************/
/**
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |Std_ReturnType|ReturnValue|E_OK if the state was read successfully, E_NOT_OK otherwise.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint8* |lifeCycleState|Pointer to a variable that will be updated with the current device lifecycle state.|
 * |uint8* |protectionState|Pointer to a variable that will be updated with the current device protection state.|
 * @par       Reference variables
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
 * @par       Output variables
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
 * @par       Reference registers
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
 * @par       Output registers
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
 * @par       Automatic variables
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |cy_en_srom_driver_status_t|sromDrvStatus|Holds the return status from the SROM API call.|
 * |Std_ReturnType|ReturnValue|Holds the final return status of the function.|
 * |un_srom_api_args_t|params|Structure to hold arguments for the SROM API call.|
 * |un_srom_api_resps_t|getResp|Structure to hold the response from the SROM API call.|
 * @brief     Reads the current lifecycle and protection state of the device using the SROM API.
 * @note      This is a wrapper for the `CY_SROM_OP_SILICON_ID` SROM command. If the API call fails, the output parameters are set to an "undefined" state (0xFF).
 */
/* author     FPT */
/* date      2025-09-24 */
/************************************************************************************************/
static Std_ReturnType Security_HandleReadStage(uint8 *lifeCycleState, uint8 *protectionState)
{
  cy_en_srom_driver_status_t sromDrvStatus;
  Std_ReturnType ReturnValue = E_NOT_OK;
  un_srom_api_args_t params = {0u};
  un_srom_api_resps_t getResp = {0u};
 
SRAM_CM0_CM7_STEP_RECORD = 114u;
  params.SiId.arg0.Opcode = (uint32_t)CY_SROM_OP_SILICON_ID;
  params.SiId.arg0.IdType = SILICON_ID_TYPE;
SRAM_CM0_CM7_STEP_RECORD = 115u;
  sromDrvStatus = Cy_Srom_CallApi(&params, &getResp);
SRAM_CM0_CM7_STEP_RECORD = 116u;
  if (sromDrvStatus == CY_SROM_DR_SUCCEEDED)
  {
SRAM_CM0_CM7_STEP_RECORD = 117u;
    ReturnValue      = E_OK;
    *lifeCycleState  = (uint8)(getResp.SiId.resp0.IdType1.LifeCycleState); /* QAC Deviations: (No 2814) Pointer lifeCycleState has been already evaluated at Security_SheKey4Info_Processing() where this function was called. */
    *protectionState = (uint8)(getResp.SiId.resp0.IdType1.ProtectionState); /* QAC Deviations: (No 2814) Pointer protectionState has been already evaluated at Security_SheKey4Info_Processing() where this function was called. */
  }
  else
  {
SRAM_CM0_CM7_STEP_RECORD = 118u;
    *lifeCycleState  = (uint8)LIFE_CYCLE_STATE_UNDEFINE; /* QAC Deviations: (No 2814) Pointer lifeCycleState has been already evaluated at Security_SheKey4Info_Processing() where this function was called. */
    *protectionState = (uint8)PROTECTION_STATE_UNDEFINE; /* QAC Deviations: (No 2814) Pointer protectionState has been already evaluated at Security_SheKey4Info_Processing() where this function was called. */
  }
 
  return ReturnValue;
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
 * |void |- |No return value. |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |const uint8[] |Repro_CipherTextProductKey |CipherText for decryption using SHE Key 4. |
 * |const uint8[] |Repro_PlainTextProductKeyA |Expected PlainText for "PRODUCTION_KEY_A". |
 * |const uint8[] |Repro_PlainTextProductKeyB |Expected PlainText for "PRODUCTION_KEY_B". |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8 |SRAM_CM0_CM7_KEY_INFO_SHE_KEY_4 |Updated with the determined SHE Key 4 info (development/production key). |
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
 * |Std_ReturnType |retVal |Return value from key search and decrypt operations. |
 * |boolean |Repro_IsKeyProductFound |Flag to indicate if the expected production key is found. |
 * |Crypto_30_LibCv_SizeOfKeyElementsType |elementIndex |Index of the SHE Key 4 element. |
 * |uint32 |Repro_Inputlength |Input length for the decryption operation. |
 * |uint32 |Repro_Outputlength |Output length after decryption. |
 * |uint8[] |Repro_Plaintext |Buffer to store decrypted PlainText. |
 * |uint8 |Repro_SheKey4_Info |Result info about SHE Key 4 (unknown, development, production A/B). |
 * |uint32 |ArrIdx |Loop index for array comparison. |
 * @brief
 *    Processes and determines the type of SHE Key 4 (development key, production key A, or production key B).
 *    The function performs decryption and compares the result with reference plaintexts to identify the key type.
 * @note
 *   - This function first checks if SHE Key 4 is valid.
 *   - It then attempts to decrypt a reference CipherText using the actual key, compares the output with two reference PlainTexts for "PRODUCTION_KEY_A" and "PRODUCTION_KEY_B".
 *   - The result is updated in `SRAM_CM0_CM7_KEY_INFO_SHE_KEY_4`.
 */
/* author FPT */
/* date 2024-07-24 */
/************************************************************************************************/
static void Security_SheKey4Info_Processing(void)
{
  Std_ReturnType retVal;
  boolean Repro_IsKeyProductFound;
  Crypto_30_LibCv_SizeOfKeyElementsType elementIndex;
  uint32 Repro_Inputlength  = REPROGRAM_PLAIN_CYPHER_TEXT_LENGTH;
  uint32 Repro_Outputlength = REPROGRAM_PLAIN_CYPHER_TEXT_LENGTH;
  uint8 Repro_Plaintext[REPROGRAM_PLAIN_CYPHER_TEXT_LENGTH];
  uint8 Repro_SheKey4_Info = REPROGRAM_THE_DEVELOPMENT_KEY;
  uint32 ArrIdx;
  uint8 lifeCycleState;
  uint8 protectionState;
 
SRAM_CM0_CM7_STEP_RECORD = 97u;
  retVal = Crypto_30_LibCv_Local_KeyElementSearch(
    CryptoConf_CryptoKey_She_Key4,
    CryptoConf_CryptoKeyElement_Crypto_30_LibCv_Cipher_Key_She_key4,
    &elementIndex);
SRAM_CM0_CM7_STEP_RECORD = 98u;
  /* QAC Deviations: (No 3383) Configuration and Generation rule of Crypto module is made sure the overflow does not occur. */
  /* Check if the Key element is valid */
  if ((E_OK == retVal) && (Crypto_30_LibCv_IsKeyElementValid(elementIndex)) )
  {
SRAM_CM0_CM7_STEP_RECORD = 99u;
    /* Verify Production Key */
    retVal |= Csm_Decrypt(
              CsmConf_CsmJob_CsmJob_Check_SheKey4Info,
              CRYPTO_OPERATIONMODE_SINGLECALL,
              Repro_CipherTextProductKey,
              Repro_Inputlength,
              Repro_Plaintext,
              &Repro_Outputlength);
SRAM_CM0_CM7_STEP_RECORD = 100u;
    if((E_OK == retVal) && (REPROGRAM_PLAIN_CYPHER_TEXT_LENGTH == Repro_Outputlength))
    {
      Repro_IsKeyProductFound = TRUE;
SRAM_CM0_CM7_STEP_RECORD = 101u;
      for(ArrIdx = 0u; ArrIdx < Repro_Outputlength; ArrIdx ++)
      {
        if(Repro_Plaintext[ArrIdx] != Repro_PlainTextProductKeyA[ArrIdx])
        {
          Repro_IsKeyProductFound = FALSE;
SRAM_CM0_CM7_STEP_RECORD = 102u;
          break;
        }
      }
SRAM_CM0_CM7_STEP_RECORD = 103u;
      if (TRUE == Repro_IsKeyProductFound)
      {
        Repro_SheKey4_Info = REPROGRAM_THE_PRODUCTION_KEY_A;
SRAM_CM0_CM7_STEP_RECORD = 104u;
      }
      else
      {
        /* Verify Production Key B if Production Key A is not correct */
        Repro_IsKeyProductFound = TRUE;
SRAM_CM0_CM7_STEP_RECORD = 105u;
        for(ArrIdx = 0u; ArrIdx < Repro_Outputlength; ArrIdx ++)
        {
          if(Repro_Plaintext[ArrIdx] != Repro_PlainTextProductKeyB[ArrIdx])
          {
            Repro_IsKeyProductFound = FALSE;
SRAM_CM0_CM7_STEP_RECORD = 106u;
            break;
          }
        }
SRAM_CM0_CM7_STEP_RECORD = 107u;
        if (TRUE == Repro_IsKeyProductFound)
        {
SRAM_CM0_CM7_STEP_RECORD = 108u;
          retVal = Security_HandleReadStage(&lifeCycleState, &protectionState);
SRAM_CM0_CM7_STEP_RECORD = 109u;
          if( (lifeCycleState == CY_LIFE_CYCLE_STATE_NORMAL_PROVISIONED) || (lifeCycleState == CY_LIFE_CYCLE_STATE_NORMAL) )
          {
            Repro_SheKey4_Info = REPROGRAM_THE_PRODUCTION_KEY_B_AND_NORMAL_STAGE;
SRAM_CM0_CM7_STEP_RECORD = 110u;
          }
          else if ( (lifeCycleState == CY_LIFE_CYCLE_STATE_SECURE) || (lifeCycleState == CY_LIFE_CYCLE_STATE_SEC_W_DBG) || (lifeCycleState == CY_LIFE_CYCLE_STATE_RMA) )
          {
            Repro_SheKey4_Info = REPROGRAM_THE_PRODUCTION_KEY_B_AND_SECURE_STAGE;
SRAM_CM0_CM7_STEP_RECORD = 111u;
          }
          else
          {
            /* DO NOTHING */
          }
        }
      }
    }
  }
  else
  {
    /* Do nothing */
  }
SRAM_CM0_CM7_STEP_RECORD = 112u;
  /* Write the SheKey4_Info into SRAM */
  SRAM_CM0_CM7_KEY_INFO_SHE_KEY_4 = Repro_SheKey4_Info;
SRAM_CM0_CM7_STEP_RECORD = 113u;
}
 
/************************************************************************************************/
/**
 * @par Arguments
 * |Type         |Name        |Description                                                    |
 * |:-----------:|:----------:|:-------------------------------------------------------------:|
 * |const uint8* |dataPtr     |Pointer to the input data to be authenticated by CMAC.         |
 * |uint32       |length      |Length of the input data in bytes.                             |
 * |const uint8* |keyPtr      |Pointer to the secret key used for AES-CMAC calculation.       |
 * |uint8*       |outputPtr   |Pointer to the buffer where the CMAC result will be stored.    |
 * |eslt_WorkSpaceCMACAES*|workspace|Pointer to the workspace for CMAC operations.           |
 * @par Return value
 * |Type             |Name  |Description                                      |
 * |:---------------:|:-----|:------------------------------------------------|
 * |Std_ReturnType   |retVal|E_OK if the CMAC calculation is successful,      |
 * |                 |      |E_NOT_OK otherwise.                              |
 * @par Argument specified address output
 * |Type   |Name      |Description                               |
 * |:------|:---------|:------------------------------------------|
 * |uint8* |outputPtr |CMAC authentication code is written here.  |
 * @par Reference variables
 * |Type   |Name      |Description                                   |
 * |:------|:---------|:----------------------------------------------|
 * |- |- |- |
 * @par Output variables
 * |Type   |Name      |Description                                   |
 * |:------|:---------|:----------------------------------------------|
 * |uint8* |outputPtr |Buffer containing the calculated CMAC value.   |
 * @par Reference registers
 * |Type   |Name      |Description                                   |
 * |:------|:---------|:----------------------------------------------|
 * |- |- |- |
 * @par Output registers
 * |Type   |Name      |Description                                   |
 * |:------|:---------|:----------------------------------------------|
 * |- |- |- |
 * @par Automatic variables
 * |Type    |Name      |Description                                            |
 * |:-------|:---------|:-----------------------------------------------------|
 * |Std_ReturnType|retVal|Return value for each Crypto operation step.         |
 * @brief
 *    Calculates an AES-CMAC authentication code for the given input data using the provided key.
 *    This function initializes the workspace, sets up the CMAC context with the key, processes the input data,
 *    and finalizes the calculation to produce the CMAC (authentication code).
 * @note
 *   - This function is typically used as part of the Key Update Flow (see diagram below) to generate MAC values such as M1, M2, M3, M4, M5.
 *   - The calculated MAC can be used for message authentication between Generator, Diagnose Tester, and ECU, ensuring integrity and authenticity during key updates.
 */
/* author FPT*/
/* date 2025-08-04 */
/************************************************************************************************/
static Std_ReturnType Security_MasterECUKey_CalCmac(
  const uint8* dataPtr,
  uint32 length,
  const uint8* keyPtr,
  uint8* outputPtr,
  eslt_WorkSpaceCMACAES* workspace)
{
  Std_ReturnType retVal = E_NOT_OK;
 
  /* #10 Init work space */
  if (esl_initWorkSpaceHeader(&workspace->header, /* SBSW_CRYPTO_30_LIBCV_INIT_ESL_STACK_WORKSPACE */ /* QAC Deviations: (No 2814) Pointer workspace has been already evaluated at Security_MasterECU_Key_Processing() where this function was called. */
    ESL_MAXSIZEOF_WS_CMACAES,
    CRYPTO_30_LIBCV_WATCHDOG_PTR ) == ESL_ERC_NO_ERROR)
  {
    /* #15 Init CMAC */
    if (esl_initCMACAES128( workspace, /* SBSW_CRYPTO_30_LIBCV_ESL_STACK_WORKSPACE_WITH_KEY_PTR */
      CRYPTO_30_LIBCV_CMACAES_MAX_KEY_SIZE,
      (P2CONST( eslt_Byte, AUTOMATIC, CRYPTO_30_LIBCV_CRYPTOCV_APPL_VAR ))keyPtr ) == ESL_ERC_NO_ERROR)
    {
 
      /* #25 Update Calculation */
      if (esl_updateCMACAES128(workspace, /* SBSW_CRYPTO_30_LIBCV_ESL_STACK_WORKSPACE_WITH_DATA_PTR */
        (eslt_Length)length,
        (P2CONST( eslt_Byte, AUTOMATIC, CRYPTO_30_LIBCV_CRYPTOCV_APPL_VAR ))dataPtr ) == ESL_ERC_NO_ERROR)
      {
        /* Finalize */
        if (esl_finalizeCMACAES128(workspace, /* SBSW_CRYPTO_30_LIBCV_ESL_STACK_WORKSPACE_WITH_OUTPUT_PTR */
          outputPtr ) == ESL_ERC_NO_ERROR)
        {
          retVal = E_OK;
        }
      }
    }
  }
 
  return retVal;
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
 * |void |- |Function does not return a value |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8 |Mac_Data |Reference data input buffer for Mac key comparison |
 * |uint8 |Mac_Dev_Verify |Reference Mac data verify buffer for Mac key type determination |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8 |SRAM_CM0_CM7_KEY_INFO_MAC_KEY |SRAM memory location updated with Mac key information |
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
 * |Std_ReturnType |retVal |Status of Crypto operations |
 * |Crypto_30_LibCv_SizeOfKeyElementsType |elementIndex |Index of crypto key element |
 * |uint32 |DataInputLength |Length of Mac data input (16 bytes) |
 * |uint32 |DataOutputLength |Length of Mac key (16 bytes) |
 * |uint8 |DataOutput[MAC_KEY_IN_OUT_TEXT_LENGTH] |Buffer to store encrypted result |
 * |uint8 |keyInfo |Information about Mac key type (development/production) |
 * |uint32 |ArrIdx |Loop counter for array comparison |
 * @brief Processes Mac key information to determine key type and updates SRAM memory
 * @note Function generate a known data input and compares the result with a reference mac data verify to determine if a production, development or unwritten key is installed
 */
/* author FPT */
/* date 2025-07-31 */
static void Security_Mac_Key_Processing(void)
{
  Std_ReturnType retVal;
  Crypto_30_LibCv_SizeOfKeyElementsType elementIndex = ZERO_NUM;
  uint32 DataInputLength  = MAC_KEY_IN_OUT_TEXT_LENGTH;
  uint32 DataOutputLength = MAC_KEY_IN_OUT_TEXT_LENGTH;
  uint8 DataOutput[MAC_KEY_IN_OUT_TEXT_LENGTH];
  uint8 keyInfo = MAC_KEY_IS_UNWRITTEN_KEY;
  boolean MacDevVerifyResult = TRUE;
  uint32 ArrIdx;
 
SRAM_CM0_CM7_STEP_RECORD = 85u;
  retVal = Crypto_30_LibCv_Local_KeyElementSearch(
      CryptoConf_CryptoKey_She_MAC_Key,
      CryptoConf_CryptoKeyElement_Crypto_30_LibCv_Mac_Key_She,
      &elementIndex);
SRAM_CM0_CM7_STEP_RECORD = 86u;
  /* QAC Deviations: (No 3383) Configuration and Generation rule of Crypto module is made sure the overflow does not occur. */
  /* Check if the Key element is valid */
  if ((E_OK == retVal) && (Crypto_30_LibCv_IsKeyElementValid(elementIndex)) )
  {
SRAM_CM0_CM7_STEP_RECORD = 87u;
    retVal = Csm_MacGenerate(
                      CsmConf_CsmJob_CsmJob_MAC_Generation,
                      CRYPTO_OPERATIONMODE_SINGLECALL,
                      Mac_Data,
                      DataInputLength,
                      DataOutput,
                      &DataOutputLength);
SRAM_CM0_CM7_STEP_RECORD = 88u;
    if(E_OK == retVal)
    {
      keyInfo = MAC_KEY_IS_DEVELOPMENT_KEY;
SRAM_CM0_CM7_STEP_RECORD = 89u;
      /* Verify if MAC_Key is Development Key */
      for(ArrIdx = 0u; ArrIdx < DataOutputLength; ArrIdx ++)
      {
        if(DataOutput[ArrIdx] != Mac_Dev_Verify[ArrIdx])
        {
SRAM_CM0_CM7_STEP_RECORD = 90u;
          MacDevVerifyResult = FALSE;
          break;
        }
      }
SRAM_CM0_CM7_STEP_RECORD = 91u;
      if (MacDevVerifyResult == FALSE)
      {
        keyInfo = MAC_KEY_IS_UNWRITTEN_KEY;
SRAM_CM0_CM7_STEP_RECORD = 92u;
        /* Verify if MAC_Key is Full 0 Key */
        for(ArrIdx = 0u; ArrIdx < DataOutputLength; ArrIdx ++)
        {
          if(DataOutput[ArrIdx] != Mac_Full0_Verify[ArrIdx])
          {
SRAM_CM0_CM7_STEP_RECORD = 93u;
            keyInfo = MAC_KEY_IS_PRODUCTION_KEY;
            break;
          }
        }
SRAM_CM0_CM7_STEP_RECORD = 94u;
      }
      else
      {
        /* Do nothing */
      }
    }
  }
  else
  {
    /* Do nothing */
  }
 
  /* Write the TypeXCommonKeyInfo into SRAM */
SRAM_CM0_CM7_STEP_RECORD = 95u;
  SRAM_CM0_CM7_KEY_INFO_MAC_KEY = keyInfo;
SRAM_CM0_CM7_STEP_RECORD = 96u;
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
 * |void |- |Function does not return a value |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8 |g_TypeX_PlainText |Reference plaintext buffer for TypeX key comparison |
 * |uint8 |g_TypeX_CipherText |Reference ciphertext buffer for TypeX key type determination |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8 |SRAM_CM0_CM7_KEY_INFO_TYPE_X |SRAM memory location updated with TypeX key information |
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
 * |Std_ReturnType |retVal |Status of Crypto operations |
 * |Crypto_30_LibCv_SizeOfKeyElementsType |elementIndexTypeX |Index of crypto key element |
 * |uint32 |TypeXSeedLength |Length of TypeX seed (16 bytes) |
 * |uint32 |TypeXKeyLength |Length of TypeX key (16 bytes) |
 * |uint8 |TypeXKey[TYPEXCOMMONKEY_PLAIN_CIPHER_TEXT_LENGTH] |Buffer to store encrypted result |
 * |uint8 |TypeXCommonKeyInfo |Information about TypeX key type (development/production) |
 * |uint32 |ArrIdx |Loop counter for array comparison |
 * @brief Processes TypeX common key information to determine key type and updates SRAM memory
 * @note Function encrypts a known plaintext and compares the result with a reference ciphertext to determine if a production or development key is installed
 */
/* author FPT */
/* date 2025-07-24 */
/************************************************************************************************/
static void Security_TypeXCommonKeyInfo_Processing(void)
{
  Std_ReturnType retVal;
  Crypto_30_LibCv_SizeOfKeyElementsType elementIndexTypeX = ZERO_NUM;
  uint32 TypeXSeedLength  = TYPEXCOMMONKEY_PLAIN_CIPHER_TEXT_LENGTH;
  uint32 TypeXKeyLength = TYPEXCOMMONKEY_PLAIN_CIPHER_TEXT_LENGTH;
  uint8 TypeXKey[TYPEXCOMMONKEY_PLAIN_CIPHER_TEXT_LENGTH];
  uint8 TypeXCommonKeyInfo = TYPEX_IS_DEVELOPMENT_KEY;
  uint32 ArrIdx;
 
SRAM_CM0_CM7_STEP_RECORD = 119u;
  retVal = Crypto_30_LibCv_Local_KeyElementSearch(
      CryptoConf_CryptoKey_She_TypeX_Encypt_Key,
      CryptoConf_CryptoKeyElement_Crypto_30_LibCv_She_AES_NISTSP80038A,
      &elementIndexTypeX);
SRAM_CM0_CM7_STEP_RECORD = 120u;
  /* QAC Deviations: (No 3383) Configuration and Generation rule of Crypto module is made sure the overflow does not occur. */
  /* Check if the Key element is valid */
  if ((E_OK == retVal) && (Crypto_30_LibCv_IsKeyElementValid(elementIndexTypeX)) )
  {
SRAM_CM0_CM7_STEP_RECORD = 121u;
    retVal = Csm_Encrypt(
                      CsmConf_CsmJob_CsmJob_TypeX_Encypt,
                      CRYPTO_OPERATIONMODE_SINGLECALL,
                      g_TypeX_PlainText,
                      TypeXSeedLength,
                      TypeXKey,
                      &TypeXKeyLength);
SRAM_CM0_CM7_STEP_RECORD = 122u;
    if(E_OK == retVal)
    {
SRAM_CM0_CM7_STEP_RECORD = 123u;
      for(ArrIdx = 0u; ArrIdx < TypeXKeyLength; ArrIdx ++)
      {
        if(TypeXKey[ArrIdx] != g_TypeX_CipherText[ArrIdx])
        {
          TypeXCommonKeyInfo = TYPEX_IS_PRODUCTION_KEY;
SRAM_CM0_CM7_STEP_RECORD = 124u;
          break;
        }
      }
SRAM_CM0_CM7_STEP_RECORD = 125u;
    }
  }
  else
  {
    /* Do nothing */
  }
 
  /* Write the TypeXCommonKeyInfo into SRAM */
SRAM_CM0_CM7_STEP_RECORD = 126u;
  SRAM_CM0_CM7_KEY_INFO_TYPE_X = TypeXCommonKeyInfo;
SRAM_CM0_CM7_STEP_RECORD = 127u;
}
 
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 *
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 *
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 *
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 *
 * @par Reference registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 *
 * @par Output registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 *
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |Std_ReturnType|retVal|Return value from key element search function|
 * |Crypto_30_LibCv_SizeOfKeyElementsType|elementIndex|Index of the searched key element|
 *
 * @brief  Initializes and processes key information for reprogramming and security. Ensures SHE Key4 is valid, processes MAC and key info, and updates NVM write status.
 * @note   This function checks the validity of SHE Key4 and sets it as valid if necessary. It then executes a series of security-related key processing operations and marks the NVM write as finished.
 */
static void Security_KeyInfoInitializationAndProcessing(void)
{
  Std_ReturnType retVal;
  Crypto_30_LibCv_SizeOfKeyElementsType elementIndex;
 
SRAM_CM0_CM7_STEP_RECORD = 77u;
  /* Reprogramming Key */
  retVal = Crypto_30_LibCv_Local_KeyElementSearch(
    CryptoConf_CryptoKey_She_Key4,
    CryptoConf_CryptoKeyElement_Crypto_30_LibCv_Cipher_Key_She_key4,
    &elementIndex);
SRAM_CM0_CM7_STEP_RECORD = 78u;
  if ( (E_OK == retVal) && (!(Crypto_30_LibCv_IsKeyElementValid(elementIndex))) )
  {
SRAM_CM0_CM7_STEP_RECORD = 79u;
    /* Set the key to be valid the first time */
    // (void)Csm_KeySetValid(CsmConf_CsmKey_CsmKey_Reprogramming);
    SRAM_CM0_CM7_KEYSETVALID_REPRO = 1u;
SRAM_CM0_CM7_STEP_RECORD = 80u;
  }
SRAM_CM0_CM7_STEP_RECORD = 81u;
  Security_Mac_Key_Processing();
SRAM_CM0_CM7_STEP_RECORD = 82u;
  Security_SheKey4Info_Processing();
SRAM_CM0_CM7_STEP_RECORD = 83u;
  Security_TypeXCommonKeyInfo_Processing();
SRAM_CM0_CM7_STEP_RECORD = 84u;
}
 
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |cryptoKeyId |Identifier of the Crypto Key whose value has changed. |
 * |uint32 |keyElementId |Identifier of the specific key element within the Crypto Key. |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |void |- |No return value. |
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
 * |uint8 |Repro_KeyCalloutStatus |Updated with `SHEKEY4_IS_KEYVALUECHANGED` if SHE Key 4's value has changed. |
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
 * @brief Callout function invoked when a cryptographic key's value has changed.
 * @note This function is a callback from the Crypto driver. It checks if the changed key
 * is `CsmConf_CsmKey_CsmKey_Reprogramming` (associated with SHE Key 4) and if the
 * specific key element is `CryptoConf_CryptoKeyElement_Crypto_30_LibCv_Cipher_Key_She_key4`.
 * If both conditions are met, it sets the `SHEKEY4_IS_KEYVALUECHANGED` bit in
 * `Repro_KeyCalloutStatus` to indicate that SHE Key 4's value has been modified.
 */
/* author FPT */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(void, CRYPTO_30_LIBCV_APPL_CODE) Crypto_30_LibCv_KeyValueChanged_Callout( uint32 cryptoKeyId, uint32 keyElementId)
{
  if((CryptoConf_CryptoKey_She_Key4 == cryptoKeyId) && (CryptoConf_CryptoKeyElement_Crypto_30_LibCv_Cipher_Key_She_key4 == keyElementId))
  {
    Repro_KeyCalloutStatus |= SHEKEY4_IS_KEYVALUECHANGED;
  }
  else if ((CryptoConf_CryptoKey_She_TypeX_Encypt_Key == cryptoKeyId) && (CryptoConf_CryptoKeyElement_Crypto_30_LibCv_She_AES_NISTSP80038A == keyElementId))
  {
    TypeX_KeycalloutStatus |= TYPEX_KEYVALUECHANGED;
  }
  else if ((CryptoConf_CryptoKey_She_MasterEcuKey == cryptoKeyId) && (CryptoConf_CryptoKeyElement_Crypto_30_LibCv_She_AES_NISTSP80038B == keyElementId))
  {
    Master_KeyCalloutStatus |= MASTER_ECU_KEYVALUECHANGED;
  }
  else if ((CryptoConf_CryptoKey_She_MAC_Key == cryptoKeyId) && (CryptoConf_CryptoKeyElement_Crypto_30_LibCv_She_AES_NISTSP80038B == keyElementId))
  {
    Mac_KeyCalloutStatus |= MAC_KEY_KEYVALUECHANGED;
  }
}
 
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |cryptoKeyId |Identifier of the Crypto Key whose validity state is being set. |
 * |boolean |validity |The new validity state (TRUE for valid, FALSE for invalid). |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |void |- |No return value. |
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
 * |uint8 |Repro_KeyCalloutStatus |Updated with `SHEKEY4_IS_KEYVALIDSET` if SHE Key 4's validity is set. |
 * |uint8 |Mac_KeyCalloutStatus |Set to `E_OK` if MAC key validity is set. |
 * |uint8 |Master_KeyCalloutStatus |Set to `E_OK` if Master ECU key validity is set. |
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
 * @brief Callout function invoked when a cryptographic key's validity is set.
 * @note This function is a callback from the Crypto driver. It updates various global status
 * flags based on which key's validity is being set:
 * - If SHE Key 4's validity is set to `CRYPTO_30_LIBCV_KEYELEMENTSTATE_VALID_MASK` and its
 * value has previously changed (indicated by `SHEKEY4_IS_KEYVALUECHANGED`), then
 * `SHEKEY4_IS_KEYVALIDSET` is set in `Repro_KeyCalloutStatus`.
 * - If MAC Key's validity is set to `CRYPTO_30_LIBCV_KEYELEMENTSTATE_VALID_MASK`, then
 * `Mac_KeyCalloutStatus` is set to `E_OK`.
 * - If Master ECU Key's validity is set to `CRYPTO_30_LIBCV_KEYELEMENTSTATE_VALID_MASK`,
 * then `Master_KeyCalloutStatus` is set to `E_OK`.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(void, CRYPTO_30_LIBCV_APPL_CODE) Crypto_30_LibCv_KeyValiditySet_Callout( uint32 cryptoKeyId, boolean validity)
{
  if ((CryptoConf_CryptoKey_She_Key4 == cryptoKeyId) && (CRYPTO_30_LIBCV_KEYELEMENTSTATE_VALID_MASK == validity) &&
  (SHEKEY4_IS_KEYVALUECHANGED == (Repro_KeyCalloutStatus & SHEKEY4_IS_KEYVALUECHANGED)))
  {
    Repro_KeyCalloutStatus |= SHEKEY4_IS_KEYVALIDSET;
  }
  else if ((CryptoConf_CryptoKey_She_MAC_Key == cryptoKeyId) && (CRYPTO_30_LIBCV_KEYELEMENTSTATE_VALID_MASK == validity) &&
  (MAC_KEY_KEYVALUECHANGED == (Mac_KeyCalloutStatus & MAC_KEY_KEYVALUECHANGED)))
  {
    Mac_KeyCalloutStatus |= MAC_KEY_KEYVALIDSET;
  }
  else if ((CryptoConf_CryptoKey_She_MasterEcuKey == cryptoKeyId) && (CRYPTO_30_LIBCV_KEYELEMENTSTATE_VALID_MASK == validity) &&
  (MASTER_ECU_KEYVALUECHANGED == (Master_KeyCalloutStatus & MASTER_ECU_KEYVALUECHANGED)))
  {
    Master_KeyCalloutStatus |= MASTER_ECU_KEYVALIDSET;
  }
  else if ((CryptoConf_CryptoKey_She_TypeX_Encypt_Key == cryptoKeyId) && (CRYPTO_30_LIBCV_KEYELEMENTSTATE_VALID_MASK == validity) &&
  (TYPEX_KEYVALUECHANGED == (TypeX_KeycalloutStatus & TYPEX_KEYVALUECHANGED)))
  {
    TypeX_KeycalloutStatus |= TYPEX_KEYVALIDSET;
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
 * |void |- |No return value. |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |USED_IPC_CHANNEL |The IPC channel currently in use. |
 * |uint32 |IPC_NOTIFY_INT_NUMBER |IPC interrupt number for notification. |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |volatile unsigned long |intSleep |Updated with the received IPC data. |
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
 * |uint32 |intCm7_0_Data |Data received from CM7_0 via IPC. |
 * |uint32 |interruptMasked |Mask indicating the status of IPC interrupts. |
 * @brief Interrupt Service Routine (ISR) for IPC notifications.
 * @note This ISR is triggered by IPC notifications. It checks if an interrupt is pending on
 * `USED_IPC_CHANNEL`.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
void IpcNotifyInt_ISR(void)
{
    uint32 intCm7_0_Data;
    uint32 interruptMasked =
            Cy_IPC_Drv_ExtractAcquireMask
            (
                Cy_IPC_Drv_GetInterruptStatusMasked
                (
                    Cy_IPC_Drv_GetIntrBaseAddr(IPC_NOTIFY_INT_NUMBER)
                )
            );
    if ((interruptMasked & (1uL << USED_IPC_CHANNEL)) != 0ul)
    {
        Cy_IPC_Drv_ClearInterrupt
        (
            /* QAC Deviations: (No 1279) This macro is provided by Cypress Semiconductor, So, this warning can ignore and doesn't affect to the current behavior. */
            Cy_IPC_Drv_GetIntrBaseAddr(IPC_NOTIFY_INT_NUMBER),
            CY_IPC_NO_NOTIFICATION,
            (1uL << USED_IPC_CHANNEL)
        );
     
        if(CY_IPC_DRV_SUCCESS == Cy_IPC_Drv_ReadMsgWord(Cy_IPC_Drv_GetIpcBaseAddress(USED_IPC_CHANNEL), (uint32_t *)&intCm7_0_Data))
        {
          intSleep = intCm7_0_Data;
        }
        /* QAC Deviations: (No 1279) This macro is provided by Cypress Semiconductor, So, this warning can ignore and doesn't affect to the current behavior. */
        (void)Cy_IPC_Drv_LockRelease(Cy_IPC_Drv_GetIpcBaseAddress(USED_IPC_CHANNEL), CY_IPC_NO_NOTIFICATION);
    }
 
}
 
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:------------------------------:|:--------:|:-----------------------------------------------:|
 * |volatile stc_MCWDT_t * |base |Pointer to the MCWDT register base address. |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |void |- |No return value. |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |volatile stc_MCWDT_t * |base |The MCWDT hardware instance to be checked and configured. |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |CM7_NOT_STARTED |Constant indicating CM7 is not started. |
 * |uint32 |CM7_STARTUP_COMPTELE |Constant indicating CM7 startup is complete. |
 * |uint32 |SRAM_CM0_CM7_CM7_STARTUP_STATE |Startup state value stored in SRAM. |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |MCWDT_t::unLOCK |base->unLOCK |Register for locking/unlocking MCWDT configuration. |
 * |MCWDT_t::CTR[0].unCTL |base->CTR[0].unCTL |Control register for WatchDog Timer channel 0. |
 * @par Output registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |MCWDT_t::unLOCK |base->unLOCK |Updated to lock/unlock MCWDT registers. |
 * |MCWDT_t::CTR[0].unCTL |base->CTR[0].unCTL |Updated to disable WatchDog Timer channel 0. |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |CM7_StartupState |Current startup state of CM7 core. |
 * @brief Checks the CM7 startup state. If startup is complete, unlocks and disables the MCWDT,
 * then relocks the configuration registers and waits for the WatchDog to disable.
 * @note The function does nothing if CM7 startup is not complete.
 */
/* author FPT */
/* date 2025-08-06 */
/************************************************************************************************/
 
static void vHsm_CM7_Startup_Check(volatile stc_MCWDT_t *base)
{
  uint32 CM7_StartupState = CM7_NOT_STARTED;
  CM7_StartupState = SRAM_CM0_CM7_CM7_STARTUP_STATE;
 
  if (CM7_StartupState == CM7_STARTUP_COMPTELE)
  {
    /* Write LOCK register to unlock the MCWDT configuration registers */
    base->unLOCK.stcField.u2MCWDT_LOCK = 1U; /* QAC Deviations: (No 2814) Pointer base has been already evaluated at vHsm_MainFunctionCyclic_Callout() where this function was called. */
    base->unLOCK.stcField.u2MCWDT_LOCK = 2U;
 
    /* Write CTL register to disable WatchDog */
    base->CTR[0].unCTL.stcField.u1ENABLE = 0U;
 
    /* Write LOCK register to lock the MCWDT configuration registers */
    base->unLOCK.stcField.u2MCWDT_LOCK = 3U;
   
    /* Wait until WatchDog is disable */
    while(base->CTR[0].unCTL.stcField.u1ENABLED != 0U);
  }
  else
  {
    /* Do nothing */
  }
}
 
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:------------------------------:|:--------:|:-----------------------------------------------:|
 * |volatile stc_MCWDT_t * |base |Pointer to the MCWDT register base address. |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |void |- |No return value. |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |volatile stc_MCWDT_t * |base |The MCWDT hardware instance to be initialized. |
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
 * |MCWDT_t::unLOCK |base->unLOCK |Register for locking/unlocking MCWDT configuration. |
 * |MCWDT_t::CTR[0].unCTL |base->CTR[0].unCTL |Control register for WatchDog Timer channel 0. |
 * |MCWDT_t::CTR[0].unUPPER_LIMIT |base->CTR[0].unUPPER_LIMIT |Upper limit register for WatchDog Timer channel 0. |
 * |MCWDT_t::unCPU_SELECT |base->unCPU_SELECT |CPU selection register. |
 * |MCWDT_t::CTR[0].unCONFIG |base->CTR[0].unCONFIG |Configuration register for WatchDog Timer channel 0. |
 * |MCWDT_t::unSERVICE |base->unSERVICE |Service register for WatchDog Timer. |
 * @par Output registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |MCWDT_t::unLOCK |base->unLOCK |Updated to lock/unlock MCWDT registers. |
 * |MCWDT_t::CTR[0].unCTL |base->CTR[0].unCTL |Updated to enable/disable WatchDog Timer channel 0. |
 * |MCWDT_t::CTR[0].unUPPER_LIMIT |base->CTR[0].unUPPER_LIMIT |Set to specify timeout period. |
 * |MCWDT_t::unCPU_SELECT |base->unCPU_SELECT |Set to select CPU core (CM0+). |
 * |MCWDT_t::CTR[0].unCONFIG |base->CTR[0].unCONFIG |Set fault action for upper limit. |
 * |MCWDT_t::unSERVICE |base->unSERVICE |Written to reset WatchDog Timer. |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @brief Initializes the WatchDog Timer (MCWDT) with a timeout of 1900ms (62259 cycles),
 * sets the owner CPU to CM0+, configures the upper limit action to FAULT_THEN_RESET,
 * resets and enables the WatchDog, and locks the configuration registers.
 * @note The function waits for hardware status transitions after enabling/disabling the WatchDog.
 */
/* author FPT */
/* date 2025-08-06 */
/************************************************************************************************/
static void vHsm_WatchdogTimerInit(volatile stc_MCWDT_t *base)
{
    /* Write LOCK register to unlock the MCWDT configuration registers */
    base->unLOCK.stcField.u2MCWDT_LOCK = 1U; /* QAC Deviations: (No 2814) Pointer base has been already evaluated at vHsm_InitThree_Callout() where this function was called. */
    base->unLOCK.stcField.u2MCWDT_LOCK = 2U;
 
    /* Write CTL register to disable WatchDog */
    base->CTR[0].unCTL.stcField.u1ENABLE = 0U;
   
    /* Wait until WatchDog is disable */
    while(base->CTR[0].unCTL.stcField.u1ENABLED != 0ul);
 
    /* Set UPPER_LIMIT register value to 1900ms = 62259 clock cycles */
    base->CTR[0].unUPPER_LIMIT.stcField.u16UPPER_LIMIT = 62259U;
   
    /* Set CPU_SELECT register to CM0+ */
    base->unCPU_SELECT.stcField.u2CPU_SEL = 0U;
   
    /* Set UPPER_ACTION bit to FAULT_THEN_RESET */
    base->CTR[0].unCONFIG.stcField.u2UPPER_ACTION = 2U;
 
    /* Write SERVICE register to reset WatchDog Timer */
    base->unSERVICE.stcField.u1CTR0_SERVICE = 1U;
 
    /* Write CTL register to enable WatchDog */
    base->CTR[0].unCTL.stcField.u1ENABLE = 1U;
   
    /* Write LOCK register to lock the MCWDT configuration registers */
    base->unLOCK.stcField.u2MCWDT_LOCK = 3U;
   
    /* Wait until status is changed */
    while(base->CTR[0].unCTL.stcField.u1ENABLED != 1U);
 
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
 * |void |- |No return value. |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |const uint8[] |Dap_EPH |Hardcoded correct hashed password for DAP. |
 * |volatile boolean |DAP_isPwAuthen |Flag indicating if DAP password has been authenticated. |
 * |uint8[] |Dap_User_Buffer |Buffer for user password, random number, and encrypted random number. |
 * |uint8[] |dap_R |Buffer for generated random number. |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |volatile boolean |DAP_isPwAuthen |Set to TRUE upon successful password authentication, then FALSE after key verification. |
 * |uint8[] |Dap_User_Buffer |Reset to 0s or filled with random number/encrypted random number. |
 * |uint8[] |dap_R |Reset to 0s. |
 * @par Reference registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |un_CPUSS_AP_CTL_t |0x40201414U |Access Port Control Register (CPUSS_AP_CTL). |
 * @par Output registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |un_CPUSS_AP_CTL_t |getUnAP_CTL->stcField.u1CM0_ENABLE |Set to 1ul to enable CM0+ debug access. |
 * |un_CPUSS_AP_CTL_t |getUnAP_CTL->stcField.u1CM7_ENABLE |Set to 1ul to enable CM7 debug access. |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |volatile un_CPUSS_AP_CTL_t* |getUnAP_CTL |Pointer to CPUSS Access Port Control Register. |
 * |uint32 |dap_Status |Current status received from IPC DAP channel. |
 * |uint8 |i |Loop counter. |
 * |uint8[] |dap_PH |Buffer to store hashed password from user. |
 * |uint32 |hashResLen |Length of the hashing result. |
 * |Std_ReturnType |retVal |Return value from CSM cryptographic operations. |
 * |uint8[] |resultEncrypt |Buffer to store encrypted random number. |
 * |uint32 |pResultEncryptLength |Length of the encrypted result. |
 * |uint32 |rnResultLengthPtr |Length of the random number result. |
 * @brief Handles Debug Access Port (DAP) authentication requests via IPC.
 * @note This function processes IPC messages from the DAP channel for authentication.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
static void Security_DAPHandler(uint32 dap_Status)
{
  /* 0x40201414 Access port control CPUSS_AP_CTL */
  volatile un_CPUSS_AP_CTL_t * getUnAP_CTL =  (volatile un_CPUSS_AP_CTL_t *)0x40201414U;
  uint8 i;
  uint8 dap_PH[HASH_DAP_LENGTH] = {0};
  uint32 hashResLen = HASH_DAP_LENGTH;
  Std_ReturnType retVal;
  uint8 resultEncrypt[RANDOM_NUMBER_DAP_LENGTH] = {0};
  uint32 pResultEncryptLength = RANDOM_NUMBER_DAP_LENGTH;
  uint32 rnResultLengthPtr = RANDOM_NUMBER_DAP_LENGTH;
  uint8 isStatusOk = TRUE;
 
  /* Check Status Code */
  switch (dap_Status)
  {
    /* Step 1: Receive password address request from User */
    case STATUS_DAP_REQUEST_PW_ADDR:
    {
      /* Write Status Code STATUS_DAP_SEND_PW_ADDR to DATA0, write Dap_User_Buffer's address to DATA1 */
      (void)Cy_IPC_Drv_SendMsgWord_2(Cy_IPC_Drv_GetIpcBaseAddress(IPC_DAP_LIFECYCLE_CHANNEL), (uint32_t)(1u << IPC_CM0_SECURITY_INT_NUMBER), STATUS_DAP_SEND_PW_ADDR, (uint32_t)&Dap_User_Buffer);
      break;
    }
   
    /* Step 2: Receive password verify request from User */
    case STATUS_DAP_RECEIVE_P:
    {
      /* Start password verify */
      /* Hashing received password and compare with Hashed password is stored in the product */
      retVal = Csm_Hash(CsmConf_CsmJob_CsmJob_DAP_Hash,
                        CRYPTO_OPERATIONMODE_SINGLECALL,
                        (const uint8 *)Dap_User_Buffer,
                        PASSWORD_DAP_LENGTH,
                        dap_PH,
                        &hashResLen);
      if ((E_OK == retVal) && (HASH_DAP_LENGTH == hashResLen))
      {
        for (i = 0u; i < HASH_DAP_LENGTH; i++)
        {
          if ( dap_PH[i] != Dap_EPH[i] )
          {
            /* Wrong password, set Status Code password inconsistent to DATA0 */
            (void)Cy_IPC_Drv_SendMsgWord(Cy_IPC_Drv_GetIpcBaseAddress(IPC_DAP_LIFECYCLE_CHANNEL), (uint32_t)(1u << IPC_CM0_SECURITY_INT_NUMBER), STATUS_DAP_PW_INCONSISTENT);
            /* Reset user password buffer to init value */
            VStdLib_MemSet(Dap_User_Buffer, 0u, PASSWORD_DAP_LENGTH);
            isStatusOk = FALSE;
            break;
          }
        }
      }
      else
      {
        /* Set Status Code Hash fail to DATA0 */
        (void)Cy_IPC_Drv_SendMsgWord(Cy_IPC_Drv_GetIpcBaseAddress(IPC_DAP_LIFECYCLE_CHANNEL), (uint32_t)(1u << IPC_CM0_SECURITY_INT_NUMBER), STATUS_DAP_HASH_FAIL);
        /* Reset user password buffer to init value */
        VStdLib_MemSet(Dap_User_Buffer ,0u ,PASSWORD_DAP_LENGTH);
        isStatusOk = FALSE;
      }
     
      /* Password consistency */
      if ( TRUE == isStatusOk )
      {
        /* Next, generate to R: Random generate */
        retVal = Csm_RandomGenerate(CsmConf_CsmJob_CsmJob_Random_Drbg, dap_R, &rnResultLengthPtr);
        /* Check RandomGenerate job status */
        if ( (E_OK == retVal) && (RANDOM_NUMBER_DAP_LENGTH == rnResultLengthPtr) )
        {
          /* Set flag the password has been successfully authenticated */
          DAP_isPwAuthen = TRUE;
          /* Write generated random number to user buffer */
          VStdMemCpy(Dap_User_Buffer, dap_R, rnResultLengthPtr);
          /* Set Status Code send random number to DATA0 */
          (void)Cy_IPC_Drv_SendMsgWord(Cy_IPC_Drv_GetIpcBaseAddress(IPC_DAP_LIFECYCLE_CHANNEL), (1ul << IPC_CM0_SECURITY_INT_NUMBER), STATUS_DAP_SEND_R);
        }
        else
        {
          /* Set Status Code random generate fail to DATA0 */
          (void)Cy_IPC_Drv_SendMsgWord(Cy_IPC_Drv_GetIpcBaseAddress(IPC_DAP_LIFECYCLE_CHANNEL), (1ul << IPC_CM0_SECURITY_INT_NUMBER), STATUS_DAP_RN_FAIL);
          /* Reset user password buffer to init value */
          VStdLib_MemSet(Dap_User_Buffer, 0u, PASSWORD_DAP_LENGTH);
        }
      }
     
      break;
    }
   
    /* Step 3: Receive Key ER (Encrypted random number ) from User */
    case STATUS_DAP_RECEIVE_KEY_ER:
    {
      /* Check if the password has been successfully authenticated */
      if (TRUE == DAP_isPwAuthen)
      {
        DAP_isPwAuthen = FALSE; /* Reset Password authen flag */
        /* Encrypt RandomNumber R for Verify */
        retVal = Csm_Encrypt(CsmConf_CsmJob_CsmJob_DAP_CR,
                             CRYPTO_OPERATIONMODE_SINGLECALL,
                             dap_R,
                             RANDOM_NUMBER_DAP_LENGTH,
                             resultEncrypt,
                             &pResultEncryptLength);
        /* Check Encrypt job status */
        if ( (E_OK == retVal) && (KEY_ER_DAP_LENGTH == pResultEncryptLength) )
        {
          for ( i = 0u; i < RANDOM_NUMBER_DAP_LENGTH; i++ )
          {
            if ( resultEncrypt[i] != Dap_User_Buffer[i] )
            {
              /* Verify job status result NOT_OK */
              /* Set Status Code Key authentication fail to DATA0 */
              (void)Cy_IPC_Drv_SendMsgWord(Cy_IPC_Drv_GetIpcBaseAddress(IPC_DAP_LIFECYCLE_CHANNEL), (1ul << IPC_CM0_SECURITY_INT_NUMBER), STATUS_DAP_AUTHEN_NOT_OK);
              isStatusOk = FALSE;
              break;
            }
          }
        }
        else
        {
          /* Set Status Code to Encrypt job fail */
          (void)Cy_IPC_Drv_SendMsgWord(Cy_IPC_Drv_GetIpcBaseAddress(IPC_DAP_LIFECYCLE_CHANNEL), (1ul << IPC_CM0_SECURITY_INT_NUMBER), STATUS_DAP_ENCRYPT_JOB_NOT_OK);
          isStatusOk = FALSE;
        }
 
        /* Verify OK */
        if ( TRUE == isStatusOk )
        {
          /* Enable Debug Access Port */
          getUnAP_CTL->stcField.u1CM0_ENABLE = 1ul;
          getUnAP_CTL->stcField.u1CM7_ENABLE = 1ul;
          /* Set Status Code Key authentication pass to DATA0 */
          (void)Cy_IPC_Drv_SendMsgWord(Cy_IPC_Drv_GetIpcBaseAddress(IPC_DAP_LIFECYCLE_CHANNEL), (1ul << IPC_CM0_SECURITY_INT_NUMBER), STATUS_DAP_AUTHEN_OK);
        }
 
        /* Reset random number buffer to init value */
        VStdLib_MemSet(dap_R, 0u, RANDOM_NUMBER_DAP_LENGTH);
        /* Reset user buffer to init value */
        VStdLib_MemSet(Dap_User_Buffer, 0u, PASSWORD_DAP_LENGTH);
      }
      else
      {
        /* Password has not been successfully authenticated */
        /* Set Status Code to Key authentication fail */
        (void)Cy_IPC_Drv_SendMsgWord(Cy_IPC_Drv_GetIpcBaseAddress(IPC_DAP_LIFECYCLE_CHANNEL), (1ul << IPC_CM0_SECURITY_INT_NUMBER), STATUS_DAP_AUTHEN_NOT_OK);
      }
 
      break;
    }
 
    default:
      break;
  }
 
  /* Release IPC DAP after sending the message to release the IPC DAP channel */
  /* QAC Deviations: (No 1279) This macro is provided by Cypress Semiconductor, So, this warning can ignore and doesn't affect to the current behavior. */
  (void)Cy_IPC_Drv_LockRelease(Cy_IPC_Drv_GetIpcBaseAddress(IPC_DAP_LIFECYCLE_CHANNEL), CY_IPC_NO_NOTIFICATION);
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
 * |void |- |No return value. |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |IPC_CM0_SECURITY_INT_NUMBER |IPC interrupt number for CM0+ security. |
 * |uint32 |IPC_DAP_LIFECYCLE_CHANNEL |IPC channel for life cycle stage management. |
 * |uint32 |Exterrnal_Clear_Rma_Request |External request for clearing RMA. |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8 |ISR1_Handler_TriggerFlag |Set to 1u if `SECURE_CLEAR_KEY_BEFORE_RMA_REQUEST` is received. |
 * |uint32 |Exterrnal_Clear_Rma_Request |Updated with the received external request. |
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
 * |uint32 |ExtRequest |External request data received via IPC. |
 * |uint32 |CM0_Response |Response to CM7, indicating success or failure of clock operations. |
 * |uint32 |interruptMasked |Mask indicating the status of IPC interrupts. |
 * @brief Interrupt Service Routine (ISR) for interrupt source 1, handling security-related IPC messages.
 * @note This ISR handles various IPC messages related to security.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
void ISR1_Handler(void)
{
  uint32 ExtRequest;
  uint32 CM0_Response = SECURE_CM0_RESPONSE_E_NOT_OK;
  uint32 interruptMasked = Cy_IPC_Drv_ExtractAcquireMask
  (
      Cy_IPC_Drv_GetInterruptStatusMasked
      (
          Cy_IPC_Drv_GetIntrBaseAddr(IPC_CM0_SECURITY_INT_NUMBER)
      )
  );
 
  /********************************* Clear RMA or DAP *********************************/
  if ((interruptMasked & (1uL << IPC_DAP_LIFECYCLE_CHANNEL)) != 0ul)
  {
    Cy_IPC_Drv_ClearInterrupt
    (
      /* QAC Deviations: (No 1279) This macro is provided by Cypress Semiconductor, So, this warning can ignore and doesn't affect to the current behavior. */
      Cy_IPC_Drv_GetIntrBaseAddr(IPC_CM0_SECURITY_INT_NUMBER),
      CY_IPC_NO_NOTIFICATION,
      (1uL << IPC_DAP_LIFECYCLE_CHANNEL)
    );
 
    if(CY_IPC_DRV_SUCCESS == Cy_IPC_Drv_ReadMsgWord(Cy_IPC_Drv_GetIpcBaseAddress(IPC_DAP_LIFECYCLE_CHANNEL), (uint32_t *)&ExtRequest))
    {
      (void)Cy_IPC_Drv_LockRelease(Cy_IPC_Drv_GetIpcBaseAddress(IPC_DAP_LIFECYCLE_CHANNEL), CY_IPC_NO_NOTIFICATION);
      if(SECURE_CLEAR_KEY_BEFORE_RMA_REQUEST == ExtRequest)
      {
        ISR1_Handler_TriggerFlag = 1u;
        Exterrnal_Clear_Rma_Request = ExtRequest;
      }
      else if(SECURE_SET_CLK_HF0_100MHZ == ExtRequest)
      {
        if(E_OK == ClockSetToFLL100MHz())
        {
          CM0_Response = SECURE_CM0_RESPONSE_E_OK;
        }
 
        (void)Cy_IPC_Drv_SendMsgWord(Cy_IPC_Drv_GetIpcBaseAddress(IPC_DAP_LIFECYCLE_CHANNEL), (1ul << IPC_CM0_SECURITY_INT_NUMBER), CM0_Response);
        (void)Cy_IPC_Drv_LockRelease(Cy_IPC_Drv_GetIpcBaseAddress(IPC_DAP_LIFECYCLE_CHANNEL), CY_IPC_NO_NOTIFICATION);
      }
      else if(SECURE_RESTORE_HF0_CLOCK_TO_ORIGINAL == ExtRequest)
      {
        if(E_OK == ClockRestoreToPLL160MHz())
        {
          CM0_Response = SECURE_CM0_RESPONSE_E_OK;
        }
 
        (void)Cy_IPC_Drv_SendMsgWord(Cy_IPC_Drv_GetIpcBaseAddress(IPC_DAP_LIFECYCLE_CHANNEL), (1ul << IPC_CM0_SECURITY_INT_NUMBER), CM0_Response);
        (void)Cy_IPC_Drv_LockRelease(Cy_IPC_Drv_GetIpcBaseAddress(IPC_DAP_LIFECYCLE_CHANNEL), CY_IPC_NO_NOTIFICATION);
      }
      else if ((STATUS_DAP_REQUEST_PW_ADDR == ExtRequest) || (STATUS_DAP_RECEIVE_P == ExtRequest) || (STATUS_DAP_RECEIVE_KEY_ER == ExtRequest))
      {
        /* DAP */
        Security_DAPHandler(ExtRequest);
      }
      else
      {
        /* Do nothing */
      }
    }
  }
}
 
#if (MEM_MAGIC_FLAG == STD_ON)
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |void |- |No return value. |
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
 * |Crypto_30_LibCv_SizeOfKeyElementsType |elementIndex |Index of the key element. |
 * |Std_ReturnType |retVal |Return value for cryptographic operations. |
 * |uint32[] |HSM_UID |Buffer to store Unique ID from hardware. |
 * |uint8[] |HSM_UID_1byte |Buffer to store Unique ID in byte format. |
 * |uint32 |getKeyLength |Length of the key to get. |
 * |un_srom_api_args_t |params |Parameters for SROM API call to read UID. |
 * |un_srom_api_resps_t |getResp |Response from SROM API call. |
 * @brief Checks and sets the validity of the Master ECU Key based on Unique ID.
 * @note This function reads the Unique ID (UID) of the device using the SROM API.
 * It then converts the UID into a byte array format. This UID is subsequently
 * used to set the `CsmKey_She_Info` key and validate the `She_MasterEcuKey`.
 * If the `She_MasterEcuKey` is not yet valid, it is set as valid for the first time.
 * This is crucial for establishing trust in the master key based on the device's unique identifier.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
static FUNC(void, VHSM_CODE) vHsm_MasterKeyIsValid(void)
{
  Crypto_30_LibCv_SizeOfKeyElementsType elementIndex = ZERO_NUM;
  Std_ReturnType retVal = E_OK;
 
  /* Read UID */
  uint32 HSM_UID[UID_32_BIT_SIZE];
  /* QAC Deviations: (No 2981) HSM_UID_1byte should be initiallized to set the default value. Current byte 0->3 was not used*/
  uint8 HSM_UID_1byte[UID_1_BYTE_SIZE + ONE_NUM] = {ZERO_NUM};/* +1 padding to match with UID_32_BIT_SIZE*4 */
  uint32 getKeyLength = UID_1_BYTE_SIZE;
  un_srom_api_args_t  params = {ZERO_NUM};
  un_srom_api_resps_t getResp   = {ZERO_NUM};
 
SRAM_CM0_CM7_STEP_RECORD = 49u;
  // read Unique ID (11 bytes)
  params.RdUnId.arg0.Opcode = (uint32_t)CY_SROM_OP_READ_UNIQUE_ID;
SRAM_CM0_CM7_STEP_RECORD = 50u;
  /* QAC Deviations: (No 1840) 'CY_ASSERT' is static code from Infineon. So, this warning can ignore and doesn't affect to the current behavior.*/
  CY_ASSERT(Cy_Srom_CallApi(&params, &getResp) == (cy_en_srom_driver_status_t)CY_SROM_DR_SUCCEEDED);
  HSM_UID[0] = getResp.RdUnId.resp2.DIE_ID1;
  HSM_UID[1] = getResp.RdUnId.resp1.DIE_ID0;
  HSM_UID[2] = getResp.RdUnId.resp0.ErrorCode;
 
  HSM_UID_1byte[4] = (uint8)(HSM_UID[0] >> SHIFT_24_BIT);
  HSM_UID_1byte[5] = (uint8)(HSM_UID[0] >> SHIFT_16_BIT);
  HSM_UID_1byte[6] = (uint8)(HSM_UID[0] >> SHIFT_8_BIT);
  HSM_UID_1byte[7] = (uint8)(HSM_UID[0]);
  HSM_UID_1byte[8] = (uint8)(HSM_UID[1] >> SHIFT_24_BIT);
  HSM_UID_1byte[9] = (uint8)(HSM_UID[1] >> SHIFT_16_BIT);
  HSM_UID_1byte[10] = (uint8)(HSM_UID[1] >> SHIFT_8_BIT);
  HSM_UID_1byte[11] = (uint8)(HSM_UID[1]);
  HSM_UID_1byte[12] = (uint8)(HSM_UID[2] >> SHIFT_16_BIT);
  HSM_UID_1byte[13] = (uint8)(HSM_UID[2] >> SHIFT_8_BIT);
  HSM_UID_1byte[14] = (uint8)(HSM_UID[2]);
SRAM_CM0_CM7_STEP_RECORD = 51u;
  /* Write UID to She_info */
  Csm_KeySetValid(CsmConf_CsmKey_CsmKey_She_Info);
SRAM_CM0_CM7_STEP_RECORD = 52u;
  Csm_KeyElementSet(
      CsmConf_CsmKey_CsmKey_She_Info,
      CryptoConf_CryptoKeyElement_Crypto_30_LibCv_She_UId,
      HSM_UID_1byte,
      getKeyLength);
SRAM_CM0_CM7_STEP_RECORD = 53u;
  Csm_KeySetValid(CsmConf_CsmKey_CsmKey_She_Info);
SRAM_CM0_CM7_STEP_RECORD = 54u;
  retVal = Crypto_30_LibCv_Local_KeyElementSearch(
    CryptoConf_CryptoKey_She_MasterEcuKey,
    CryptoConf_CryptoKeyElement_Crypto_30_LibCv_She_AES_NISTSP80038B,
    &elementIndex);
SRAM_CM0_CM7_STEP_RECORD = 55u;
  /* QAC Deviations: (No 3383) Configuration and Generation rule of Crypto module is made sure the overflow does not occur. */
  /* Check if the Key element is valid */
  if ((retVal == E_OK) && (!(Crypto_30_LibCv_IsKeyElementValid(elementIndex))) )
  {
SRAM_CM0_CM7_STEP_RECORD = 56u;
    /* Set the key to be valid the first time */
    // Csm_KeySetValid(CsmConf_CsmKey_CsmKey_She_MasterEcuKey);
    SRAM_CM0_CM7_KEYSETVALID_MASTERECU = 1u;
SRAM_CM0_CM7_STEP_RECORD = 57u;
  }
}
 
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |void |- |No return value. |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8[] |bank_write |Array holding the magic word to be written to the active bank. |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8[] |bank_write |Updated with new magic word values if conditions are met. |
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
 * |uint8 |idx |Loop counter for array operations and address calculation. |
 * |Std_ReturnType |retVal |Local variable for results of memory operations. |
 * |uint8 |BankStatus |Local variable to indicate if the active bank matches the expected magic word. |
 * |uint8 |BufferSoundVPMain |Local buffer for Sound and VP magic word data from main area. |
 * |uint8 |BufferSoundVPbackup |Local buffer for Sound and VP magic word data from backup area. |
 * @brief Checks the integrity of the active bank magic word. If a mismatch is detected, updates both main and backup bank magic words (uCom, Sound, and VP) in flash memory, ensuring data consistency and reliability of the dual bank system.
 * @note This function is designed for systems using dual-bank flash memory architecture. It verifies magic word consistency and restores the correct values if necessary. All address calculations are properly bounded and controlled, ensuring safe operations.
 */
static FUNC(void, VHSM_CODE) updateDualBankMagicWord(void)
{
  uint8 idx;
  Std_ReturnType retVal;
  uint8 BankStatus = MATCHED_ACTIVE_BANK;
  uint8 BufferSoundVPMain[MAGIC_WORD_SOUND_VP_LENGTH];
  uint8 BufferSoundVPbackup[MAGIC_WORD_SOUND_VP_LENGTH];
 
  /* memset BufferSoundVPMain, BufferSoundVPbackup to 0 */
  for (idx = 0; idx < MAGIC_WORD_SOUND_VP_LENGTH; idx++)
  {
    BufferSoundVPMain[idx] = 0x00U;
    BufferSoundVPbackup[idx] = 0x00U;
  }
 
  if ((APP_B_OK == AppStatus) || (APP_B_FAIL == AppStatus))
  {
    bank_write[0] = MAGIC_WORD_BANK_B;
    bank_write[1] = MAGIC_WORD_BANK_B;
    bank_write[2] = MAGIC_WORD_BANK_B;
    bank_write[3] = MAGIC_WORD_BANK_B;
  }
 
  /* check bank magic word */
  for (idx = ZERO_NUM; idx < MAKER_ON_WORK_SIZE; idx++)
  {
    /* QAC Deviations: (No 3383) The overflow does not occur because the address arithmetic is well-bounded and controlled.
    The logic ensures that all address calculations remain within valid memory ranges.*/
    if (bank_write[idx] != (*(uint8 *)(ADDR_MAKER_ON_WORK + idx)))
    {
      BankStatus = UNMATCHED_ACTIVE_BANK;
      break;
    }
  }
 
  if (UNMATCHED_ACTIVE_BANK == BankStatus)
  {
    /* Read magic word of Sound and VP main and backup */
    for (idx = 0; idx < MAGIC_WORD_SOUND_VP_LENGTH; idx++)
    {
      BufferSoundVPMain[idx] = (*(uint8 *)(MAGIC_WORD_SOUND_VP_BASE_ADDRESS_MAIN + idx));
      BufferSoundVPbackup[idx] = (*(uint8 *)(MAGIC_WORD_SOUND_VP_BASE_ADDRESS_BACKUP + idx));
    }
 
    /* Magic word main process */
    retVal = vMem_30_Traveo2Cyp01_Erase(ZERO_NUM, ADDR_MAKER_ON_WORK, WORKFLASH_ERASE_SIZE);
    if (retVal == E_OK)
    {
      do {
        vMem_30_Traveo2Cyp01_MainFunction();
      } while(vMem_30_Traveo2Cyp01_GetJobResult(ZERO_NUM) == VMEM_JOB_PENDING);
 
      /* write uCom magic word into main area */
      retVal = vMem_30_Traveo2Cyp01_Write(ZERO_NUM, ADDR_MAKER_ON_WORK, (uint8*)&bank_write[0], MAGIC_WORD_UCOM_LENGTH);
      if (retVal == E_OK)
      {
        do {
          vMem_30_Traveo2Cyp01_MainFunction();
        } while(vMem_30_Traveo2Cyp01_GetJobResult(ZERO_NUM) == VMEM_JOB_PENDING);
      }
 
      /* write Sound magic word into main area */
      retVal = vMem_30_Traveo2Cyp01_Write(ZERO_NUM, ADDR_MAKER_ON_WORK + MAGIC_WORD_UCOM_LENGTH, (uint8*)&BufferSoundVPMain[0], MAGIC_WORD_SOUND_LENGTH);
      if (retVal == E_OK)
      {
        do {
          vMem_30_Traveo2Cyp01_MainFunction();
        } while(vMem_30_Traveo2Cyp01_GetJobResult(ZERO_NUM) == VMEM_JOB_PENDING);
      }
     
      /* write VP magic word into main area */
      retVal = vMem_30_Traveo2Cyp01_Write(ZERO_NUM, ADDR_MAKER_ON_WORK + MAGIC_WORD_UCOM_LENGTH + MAGIC_WORD_SOUND_LENGTH, (uint8*)&BufferSoundVPMain[MAGIC_WORD_SOUND_LENGTH], MAGIC_WORD_VP_LENGTH);
      if (retVal == E_OK)
      {
        do {
          vMem_30_Traveo2Cyp01_MainFunction();
        } while(vMem_30_Traveo2Cyp01_GetJobResult(ZERO_NUM) == VMEM_JOB_PENDING);
      }
    }
 
    /* Magic word backup process */
    retVal = vMem_30_Traveo2Cyp01_Erase(ZERO_NUM, ADDR_BACKUP_MAKER_ON_WORK, WORKFLASH_ERASE_SIZE);
    if (retVal == E_OK)
    {
      do {
        vMem_30_Traveo2Cyp01_MainFunction();
      } while(vMem_30_Traveo2Cyp01_GetJobResult(ZERO_NUM) == VMEM_JOB_PENDING);
 
      /* write uCom magic word into backup area */
      retVal = vMem_30_Traveo2Cyp01_Write(ZERO_NUM, ADDR_BACKUP_MAKER_ON_WORK, (uint8*)&bank_write[0], MAGIC_WORD_UCOM_LENGTH);
      if (retVal == E_OK)
      {
        do {
          vMem_30_Traveo2Cyp01_MainFunction();
        } while(vMem_30_Traveo2Cyp01_GetJobResult(ZERO_NUM) == VMEM_JOB_PENDING);
      }
 
      /* write Sound magic word into backup area */
      retVal = vMem_30_Traveo2Cyp01_Write(ZERO_NUM, ADDR_BACKUP_MAKER_ON_WORK + MAGIC_WORD_UCOM_LENGTH, (uint8*)&BufferSoundVPbackup[0], MAGIC_WORD_SOUND_LENGTH);
      if (retVal == E_OK)
      {
        do {
          vMem_30_Traveo2Cyp01_MainFunction();
        } while(vMem_30_Traveo2Cyp01_GetJobResult(ZERO_NUM) == VMEM_JOB_PENDING);
      }
     
      /* write VP magic word into backup area */
      retVal = vMem_30_Traveo2Cyp01_Write(ZERO_NUM, ADDR_BACKUP_MAKER_ON_WORK + MAGIC_WORD_UCOM_LENGTH + MAGIC_WORD_SOUND_LENGTH, (uint8*)&BufferSoundVPbackup[MAGIC_WORD_SOUND_LENGTH], MAGIC_WORD_VP_LENGTH);
      if (retVal == E_OK)
      {
        do {
          vMem_30_Traveo2Cyp01_MainFunction();
        } while(vMem_30_Traveo2Cyp01_GetJobResult(ZERO_NUM) == VMEM_JOB_PENDING);
      }
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
 * |void |- |No return value. |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8[] |version_write |Array containing the current memory layout version to be written. |
 * |uint8[] |version_read |Buffer to read the memory layout version from flash. |
 * |uint32 |WORKFLASH_FLAG_SIZE |Size of the WorkFlash flag in bytes. |
 * |uint32 |WORKFLASH_ERASE_LAST_IDX |Last index for WorkFlash erase operations. |
 * |uint32 |WORKFLASH_ERASE_SIZE |Size of WorkFlash erase block in bytes. |
 * |uint32 |WORKFLASH_ERASE_START_ADDR |Start address for WorkFlash erase operations. |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8[] |version_read |Updated with the memory layout version read from flash. |
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
 * |uint8 |LayoutStatus |Status indicating if the memory layout is old or new. |
 * |uint8 |verReadIdx |Loop index for version read. |
 * |uint32 |EraseWFIdx |Loop index for erasing WorkFlash. |
 * @brief Handles memory layout versioning by erasing and rewriting Work Flash if a new layout is detected.
 * @note This function reads the current memory layout version from NVM
 * (`NvMConf_NvMBlockDescriptor_MemoryLayout_Version`) into `version_read`.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
static FUNC(void, VHSM_CODE) vHsm_HandleMemoryLayoutVersion(void)
{
  uint8 LayoutStatus = WORKFLASH_OLD_LAYOUT;
  uint8 verReadIdx;
  uint32 EraseWFIdx;
 
  // read version
  (void) vHsm_NvM_ReadBlock(NvMConf_NvMBlockDescriptor_MemoryLayout_Version, &version_read);
 
  // check version
  for (verReadIdx = ZERO_NUM; verReadIdx < WORKFLASH_FLAG_SIZE; verReadIdx++)
  {
    if (version_read[verReadIdx] != version_write[verReadIdx])
    {
      LayoutStatus = WORKFLASH_NEW_LAYOUT;
      break;
    }
  }
 
  if (LayoutStatus == WORKFLASH_NEW_LAYOUT)
  {
    SRAM_CM0_CM7_WORKFLASH_ERASE_PROCESS = CM0_DEBUG_WORKFLASH_ERASE_BY_LAYOUT_START;
    SRAM_CM0_CM7_WORKFLASH_ERASE_BY_LAYOUT = CM0_DEBUG_WORKFLASH_ERASE_BY_LAYOUT;
    // erase full work flash
    for(EraseWFIdx = ZERO_NUM; EraseWFIdx < WORKFLASH_ERASE_LAST_IDX; EraseWFIdx ++)
    {
      /* QAC Deviations: (No 3383) The overflow does not occur because the address arithmetic is well-bounded and controlled.
      The logic ensures that all address calculations remain within valid memory ranges.*/
      vMem_30_Traveo2Cyp01_Erase(0u, (WORKFLASH_ERASE_START_ADDR + (WORKFLASH_ERASE_SIZE * EraseWFIdx)), WORKFLASH_ERASE_SIZE);
      do {
        vMem_30_Traveo2Cyp01_MainFunction();
      } while(vMem_30_Traveo2Cyp01_GetJobResult(ZERO_NUM) == VMEM_JOB_PENDING);
    }
 
    SRAM_CM0_CM7_WORKFLASH_ERASE_PROCESS = CM0_DEBUG_WORKFLASH_ERASE_FINISH;
    // write version
    (void) vHsm_NvM_WriteBlock(NvMConf_NvMBlockDescriptor_MemoryLayout_Version, &version_write);
  }
}
#endif /*(MEM_MAGIC_FLAG == STD_ON)*/
 
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8 |IntegrityState |The new integrity state to be written to SRAM. |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |void |- |No return value. |
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
 * |uint32 |SRAM_CM0_CM7_INTEGRITY |Updated with the provided `IntegrityState`. |
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
 * @brief Updates the integrity status shared between CM0+ and CM7 in SRAM.
 * @note This function writes the provided `IntegrityState` directly to the `SRAM_CM0_CM7_INTEGRITY`
 * memory address.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(void, VHSM_CODE) UpdateIntegrityStateIntoWorkFlash(uint8 IntegrityState)
{
  SRAM_CM0_CM7_INTEGRITY = IntegrityState;
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
 * |boolean |isApplSecBootOk |TRUE if application secure boot is considered OK; FALSE otherwise. |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint16 |ResetCounter |Global counter for system resets. |
 * |uint32 |RESET_COUNTER_LIMIT |Maximum allowed value for `ResetCounter` before secure boot fails. |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint16 |ResetCounter |Reset to 0U after evaluation. |
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
 * |boolean |isApplSecBootOk |Local flag to determine the application's secure boot status. |
 * @brief Handles and evaluates the application's secure boot verification status.
 * @note This function determines if the application's secure boot is considered successful
 * based on the `ResetCounter`.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
static FUNC(boolean, VHSM_CODE) handleApplVerificationStatus(void)
{
  /* QAC Deviations: (No 2981) isApplSecBootOk should be set to default value because if ResetCounter > RESET_COUNTER_LIMIT, the random
  number occured */
  boolean isApplSecBootOk = FALSE;
 
SRAM_CM0_CM7_STEP_RECORD = 46u;
  if (RESET_COUNTER_LIMIT >= ResetCounter)
  {
SRAM_CM0_CM7_STEP_RECORD = 47u;
    isApplSecBootOk = TRUE;
  }
SRAM_CM0_CM7_STEP_RECORD = 48u;
  ResetCounter = 0U;
 
//  return isApplSecBootOk;
  return TRUE; /* Secureboot disable */
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
 * |Std_ReturnType |retVal |E_OK if the erase operation is successful; E_NOT_OK otherwise. |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |KEY_AREA_WORKFLASH_ERASE_LAST_IDX |Last index for key area WorkFlash erase. |
 * |uint32 |WORKFLASH_ERASE_SIZE |Size of WorkFlash erase block in bytes. |
 * |uint32 |KEY_AREA_WORKFLASH_ERASE_START_ADDR |Start address for key area WorkFlash erase. |
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
 * |uint32 |i |Loop counter for erase operations. |
 * @brief Erases the key information area in Work Flash.
 * @note This function performs a block erase operation on the designated key area
 * within Work Flash. It iterates from `KEY_AREA_WORKFLASH_ERASE_START_ADDR` up to
 * `KEY_AREA_WORKFLASH_ERASE_LAST_IDX`, erasing `WORKFLASH_ERASE_SIZE` bytes at each step.
 * The `vMem_30_Traveo2Cyp01_MainFunction()` is called repeatedly after each erase
 * request to ensure the job completes before proceeding. This function is typically
 * called in scenarios requiring the clearing of sensitive key data, such as before
 * returning the device for RMA (Return Material Authorization).
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
Std_ReturnType ClearKeyInfoBeforeRma(void)
{
  Std_ReturnType retVal = E_OK;
  uint32 i;
 
SRAM_CM0_CM7_STEP_RECORD = 178u;
  SRAM_CM0_CM7_WORKFLASH_ERASE_PROCESS = CM0_DEBUG_WORKFLASH_ERASE_BY_CLEARKEY_RMA_START;
  SRAM_CM0_CM7_WORKFLASH_ERASE_BY_CLEARKEY_RMA = CM0_DEBUG_WORKFLASH_ERASE_BY_CLEARKEY_RMA;
  // erase key area in workflash
  for(i = ZERO_NUM; i < KEY_AREA_WORKFLASH_ERASE_LAST_IDX; i ++)
  {
SRAM_CM0_CM7_STEP_RECORD = 179u;
    /* QAC Deviations: (No 3383) The overflow does not occur because the address arithmetic is well-bounded and controlled.
    The logic ensures that all address calculations remain within valid memory ranges.*/
    retVal |= vMem_30_Traveo2Cyp01_Erase(0u, (KEY_AREA_WORKFLASH_ERASE_START_ADDR + (WORKFLASH_ERASE_SIZE * i)), WORKFLASH_ERASE_SIZE);
SRAM_CM0_CM7_STEP_RECORD = 180u;
    do {
SRAM_CM0_CM7_STEP_RECORD = 181u;
      vMem_30_Traveo2Cyp01_MainFunction();
SRAM_CM0_CM7_STEP_RECORD = 182u;
    } while(vMem_30_Traveo2Cyp01_GetJobResult(ZERO_NUM) == VMEM_JOB_PENDING);
SRAM_CM0_CM7_STEP_RECORD = 183u;
  }
SRAM_CM0_CM7_STEP_RECORD = 184u;
 
  if(retVal != E_OK)
  {
    SRAM_CM0_CM7_WORKFLASH_ERASE_BY_CLEARKEY_RMA = CM0_DEBUG_WORKFLASH_ERASE_BY_CLEARKEY_RMA_FAIL;
  }
  SRAM_CM0_CM7_WORKFLASH_ERASE_PROCESS = CM0_DEBUG_WORKFLASH_ERASE_FINISH;
  return retVal;
}
 
/* NS - Implement for Deep Sleep optimization */
/* Check if CM7 has transitioned to DeepSleep. */
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |boolean |ret |TRUE if both CM7_0 and CM7_1 cores are in DeepSleep mode; FALSE otherwise. |
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
 * |CPUSS->unCM7_0_STATUS |CM7_0 Status Register |Status of CM7_0 core, including SLEEPING and SLEEPDEEP bits. |
 * |CPUSS->unCM7_1_STATUS |CM7_1 Status Register |Status of CM7_1 core, including SLEEPING and SLEEPDEEP bits. |
 * @par Output registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |boolean |ret |Local variable to store the return status. |
 * @brief Checks if both Cortex-M7 cores (CM7_0 and CM7_1) have entered DeepSleep mode.
 * @note This function reads the `SLEEPING` and `SLEEPDEEP` bits from the status
 * registers of both CM7_0 and CM7_1 cores in the CPUSS. If both cores are indicated
 * as being `SLEEPING` AND in `SLEEPDEEP` state, the function returns TRUE,
 * otherwise FALSE. This is part of the Deep Sleep optimization to ensure all cores
 * are in a low-power state before the system enters Deep Sleep.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
static FUNC(boolean, VHSM_CODE) check_cm7_sleep_status(void)
{
  boolean ret = FALSE;
  /* QAC Deviations: (No 1279) This macro define for register access and provided by Infineon. So, this warning can ignore and doesn't affect to the current behavior. */
  if ( (CPUSS->unCM7_0_STATUS.stcField.u1SLEEPING == 0x1U) &&  
       (CPUSS->unCM7_0_STATUS.stcField.u1SLEEPDEEP == 0x1U) &&  
       (CPUSS->unCM7_1_STATUS.stcField.u1SLEEPING == 0x1U) &&  
       (CPUSS->unCM7_1_STATUS.stcField.u1SLEEPDEEP == 0x1U) )  
  {
    ret = TRUE;
  }
 
  return ret;
}
 
/**
 * @def      FLASHC_CM0_PWR_OFF
 * @value    0x00000000U
 * @resolution -
 * @brief    Power off state value for the CM0 Flash Controller.
 */
#define FLASHC_CM0_PWR_OFF  (0x00000000U)
 
/**
 * @def      FLASHC_CM0_PWR_EN
 * @value    0x00000003U
 * @resolution -
 * @brief    Power enable value for the CM0 Flash Controller.
 */
#define FLASHC_CM0_PWR_EN   (0x00000003U)
 
/**
 * @def      FLASHC_CM0_WT_KEY
 * @value    0x05FA0000U
 * @resolution -
 * @brief    Key value required to write to the CM0 Flash Controller register.
 */
#define FLASHC_CM0_WT_KEY   (0x05FA0000U)
 
/**
 * @def      FLASHC_CMD_WAIT
 * @value    10U
 * @resolution -
 * @brief    Wait time (in arbitrary units) after issuing a Flash command.
 */
#define FLASHC_CMD_WAIT     (10U)
 
/**
 * @def      FLASHC_POWER_WAIT
 * @value    310U
 * @resolution -
 * @brief    Wait time (in arbitrary units) for Flash Controller power-up sequence.
 */
#define FLASHC_POWER_WAIT   (310U)
 
/**
 * @def      CRYPTO_PWR_OFF
 * @value    0x00000000U
 * @resolution -
 * @brief    Power off state value for the Crypto block.
 */
#define CRYPTO_PWR_OFF      (0x00000000U)
 
/**
 * @def      CRYPTO_PWR_EN
 * @value    0x00000003U
 * @resolution -
 * @brief    Power enable value for the Crypto block.
 */
#define CRYPTO_PWR_EN       (0x00000003U)
 
/**
 * @def      CRYPTO_BUSY_WAIT
 * @value    160U
 * @resolution -
 * @brief    Wait time (in arbitrary units) for the Crypto block to become idle.
 */
#define CRYPTO_BUSY_WAIT    (160U)
 
/**
 * @def      CRYPTO_POWER_WAIT
 * @value    160U
 * @resolution -
 * @brief    Wait time (in arbitrary units) for the Crypto block power-up sequence.
 */
#define CRYPTO_POWER_WAIT   (160U)
 
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |void |- |No return value. |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |- |- |- |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |FLASHC->unFLASH_CMD |Flash Controller Command Register |Used for cache invalidation. |
 * |FLASHC->unCM0_CA_CTL0 |CM0+ Cache Control Register 0 |Used to disable cache. |
 * |FLASHC->unCM0_CA_CTL1 |CM0+ Cache Control Register 1 |Used to power off cache. |
 * @par Output registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |FLASHC->unFLASH_CMD |Flash Controller Command Register |Updated with invalidation command. |
 * |FLASHC->unCM0_CA_CTL0 |CM0+ Cache Control Register 0 |Cache enable bit set to 0. |
 * |FLASHC->unCM0_CA_CTL1 |CM0+ Cache Control Register 1 |Power mode set to `FLASHC_CM0_PWR_OFF`. |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |wcnt |Loop counter for delay. |
 * @brief Disables and powers off the Cortex-M0+ cache.
 * @note This function performs several steps to disable and power off the CM0+
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
static FUNC(void, VHSM_CODE) cm0p_cache_off(void)
{
  uint32 wcnt;
 
  /* QAC Deviations: (No 1279) This macro define for register access and provided by Infineon. So, this warning can ignore and doesn't affect to the current behavior*/
  FLASHC->unFLASH_CMD.stcField.u1INV = 1U;    /* Invalidation of ALL caches (for CM0+) and ALL buffers */
 
  /* QAC Deviations: (No 3383) the overflow does not occur. wcnt already check max with item FLASHC_CMD_WAIT: 10u*/
  wcnt = 0UL;
  do {
    __asm("nop");
    wcnt++;
  } while (wcnt < FLASHC_CMD_WAIT);    /* wait */
 
  /* QAC Deviations: (No 1279) This macro define for register access and provided by Infineon. So, this warning can ignore and doesn't affect to the current behavior*/
  FLASHC->unCM0_CA_CTL0.stcField.u1CA_EN = 0U;    /* disable cache */
 
  /* QAC Deviations: (No 1279) This macro define for register access and provided by Infineon. So, this warning can ignore and doesn't affect to the current behavior*/
  FLASHC->unCM0_CA_CTL1.u32Register = (FLASHC_CM0_WT_KEY | FLASHC_CM0_PWR_OFF);    /* power off cache */
 
  return;
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
 * |void |- |No return value. |
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
 * |FLASHC->unCM0_CA_CTL1 |CM0+ Cache Control Register 1 |Used to power enable cache. |
 * |FLASHC->unCM0_CA_CTL0 |CM0+ Cache Control Register 0 |Used to enable cache. |
 * @par Output registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |FLASHC->unCM0_CA_CTL1 |CM0+ Cache Control Register 1 |Power mode set to `FLASHC_CM0_PWR_EN`. |
 * |FLASHC->unCM0_CA_CTL0 |CM0+ Cache Control Register 0 |Cache enable bit set to 1. |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |wcnt |Loop counter for delay. |
 * @brief Enables and powers on the Cortex-M0+ cache.
 * @note This function performs several steps to power on and enable the CM0+
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
static FUNC(void, VHSM_CODE) cm0p_cache_on(void)
{
  uint32 wcnt;
 
  /* QAC Deviations: (No 1279) This macro define for register access and provided by Infineon. So, this warning can ignore and doesn't affect to the current behavior*/
  FLASHC->unCM0_CA_CTL1.u32Register = (FLASHC_CM0_WT_KEY | FLASHC_CM0_PWR_EN);    /* power enable cache */
 
  /* QAC Deviations: (No 3383) the overflow does not occur. wcnt already check max with item FLASHC_POWER_WAIT: 310*/
  wcnt = 0UL;
  do {
    __asm("nop");
    wcnt++;
  } while (wcnt < FLASHC_POWER_WAIT);    /* wait */
 
  /* QAC Deviations: (No 1279) This macro define for register access and provided by Infineon. So, this warning can ignore and doesn't affect to the current behavior*/
  FLASHC->unCM0_CA_CTL0.stcField.u1CA_EN = 1U;    /* enable cache */
 
  return;
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
 * |void |- |No return value. |
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
 * |un_srom_api_args_t |params |Parameters for SROM API call to load regulator trim. |
 * |un_srom_api_resps_t |getResp |Response from SROM API call. |
 * @brief Switches the regulator configuration when entering DeepSleep mode.
 * @note This function calls the SROM API `CY_SROM_OP_LoadRegulatorTrim` with the
 * `CY_SROM_LoadRegulatorTrim_DPSLP_Entry` use case. This configures the LDO (Low Dropout)
 * regulator for optimal power consumption when the system is transitioning into DeepSleep.
 * This is a critical step in power management to ensure the correct voltage supply
 * during low-power states.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
static FUNC(void, VHSM_CODE) switch_regulator_sleep_entry(void)
{
  un_srom_api_args_t  params = {0};
  un_srom_api_resps_t getResp   = {0};
 
  params.LoadRegulatorTrim.arg0.arg     = 0U;
  params.LoadRegulatorTrim.arg0.trim    = CY_SROM_LoadRegulatorTrim_LDO;
  params.LoadRegulatorTrim.arg0.usecase = CY_SROM_LoadRegulatorTrim_DPSLP_Entry;
  params.LoadRegulatorTrim.arg0.opcode  = (uint32_t)CY_SROM_OP_LoadRegulatorTrim;
 
  (void)Cy_Srom_CallApi(&params, &getResp);
 
  return;
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
 * |void |- |No return value. |
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
 * |SRSS->unPWR_REGHC_STATUS |Power Regulator HC Status Register |Used to check busy and enabled status. |
 * @par Output registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |un_srom_api_args_t |params |Parameters for SROM API call to load regulator trim. |
 * |un_srom_api_resps_t |getResp |Response from SROM API call. |
 * |bool |getStatus |Flag to check regulator status. |
 * @brief Switches the regulator configuration when exiting DeepSleep mode.
 * @note This function prepares the regulator for exiting DeepSleep mode by calling the
 * SROM API
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
static FUNC(void, VHSM_CODE) switch_regulator_sleep_exit(void)
{
  un_srom_api_args_t  params = {0};
  un_srom_api_resps_t getResp   = {0};
  bool getStatus;
 
  params.LoadRegulatorTrim.arg0.arg     = 0U;
  params.LoadRegulatorTrim.arg0.trim    = CY_SROM_LoadRegulatorTrim_LDO;
  params.LoadRegulatorTrim.arg0.usecase = (cy_en_srom_LoadRegulatorTrim_UseCase_t)CY_SROM_LoadRegulatorTrim_DPSLP_Exit;
  params.LoadRegulatorTrim.arg0.opcode  = (uint32_t)CY_SROM_OP_LoadRegulatorTrim;
 
  /* Wait until "BUSY" = 0 and "Enabled = REGHC.EN" */
  do {
      /* QAC Deviations: (No 1279) This macro define for register access and provided by Infineon. So, this warning can ignore and doesn't affect to the current behavior*/
      getStatus = ((SRSS->unPWR_REGHC_STATUS.stcField.u1REGHC_SEQ_BUSY == 1u) || (SRSS->unPWR_REGHC_STATUS.stcField.u1REGHC_ENABLED == 0u));
  } while (getStatus == (bool)TRUE);
 
  (void)Cy_Srom_CallApi(&params, &getResp);
 
  return;
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
 * |void |- |No return value. |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |CRYPTO->unSTATUS |Crypto Status Register |Used to check if Crypto module is busy. |
 * @par Output registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |CRYPTO->unCTL |Crypto Control Register |`u1ENABLED` bit set to 0. |
 * |CRYPTO->unRAM_PWR_CTL |Crypto RAM Power Control Register |`u2PWR_MODE` set to `CRYPTO_PWR_OFF`. |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |getStatus |Local variable to store Crypto busy status. |
 * |uint32 |wcnt |Loop counter for wait. |
 * @brief Disables and powers off the Crypto hardware module.
 * @note This function ensures the Crypto hardware is in an idle state before
 * disabling and powering it off. It first waits for the `u1BUSY` bit in `CRYPTO->unSTATUS`
 * to clear, indicating the module is not busy (with a timeout `CRYPTO_BUSY_WAIT`).
 * Then, it disables the Crypto module by clearing the `u1ENABLED` bit in `CRYPTO->unCTL`
 * and powers off the Crypto RAM by setting `u2PWR_MODE` in `CRYPTO->unRAM_PWR_CTL`
 * to `CRYPTO_PWR_OFF`. This is a power-saving measure for low-power modes.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
static FUNC(void, VHSM_CODE) crypto_hw_disable(void)
{
  uint32 getStatus;
  uint32 wcnt;
 
  /* Confirm idle */
  /* QAC Deviations: (No 3383) the overflow does not occur. wcnt already check max with item CRYPTO_BUSY_WAIT: 160u*/
  wcnt = 0U;
  do {
    /* QAC Deviations: (No 1279) This macro define for register access and provided by Infineon. So, this warning can ignore and doesn't affect to the current behavior*/
    getStatus = CRYPTO->unSTATUS.stcField.u1BUSY;
    wcnt++;
  } while ((getStatus != 0x0U) && (wcnt < CRYPTO_BUSY_WAIT));
 
  /* QAC Deviations: (No 1279) This macro define for register access and provided by Infineon. So, this warning can ignore and doesn't affect to the current behavior*/
  CRYPTO->unCTL.stcField.u1ENABLED = 0x0U;                      /* Disable */
  /* QAC Deviations: (No 1279) This macro define for register access and provided by Infineon. So, this warning can ignore and doesn't affect to the current behavior*/
  CRYPTO->unRAM_PWR_CTL.stcField.u2PWR_MODE = CRYPTO_PWR_OFF;    /* power off */
 
  return;
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
 * |void |- |No return value. |
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
 * |CRYPTO->unRAM_PWR_CTL |Crypto RAM Power Control Register |`u2PWR_MODE` set to `CRYPTO_PWR_EN`. |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |wcnt |Loop counter for delay. |
 * @brief Enables and powers on the Crypto hardware module.
 * @note This function powers on and enables the Crypto hardware module. It first sets
 * the `u2PWR_MODE` in `CRYPTO->unRAM_PWR_CTL` to `CRYPTO_PWR_EN` to power on the Crypto RAM.
 * A delay (`CRYPTO_POWER_WAIT`) is introduced to allow sufficient time for power-up.
 * Finally, it calls `Crypto_30_Hwa_InitMemory()` and `Crypto_30_Hwa_Init()` to re-initialize
 * the Crypto HWA. This function is used to restore the Crypto module's functionality
 * after exiting a low-power state.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
static FUNC(void, VHSM_CODE) crypto_hw_enable(void)
{
  uint32 wcnt;
 
  /* QAC Deviations: (No 1279) This macro define for register access and provided by Infineon. So, this warning can ignore and doesn't affect to the current behavior*/
  CRYPTO->unRAM_PWR_CTL.stcField.u2PWR_MODE = CRYPTO_PWR_EN;     /* power enable */
 
  /* QAC Deviations: (No 3383) the overflow does not occur. wcnt already check max with item CRYPTO_POWER_WAIT: 160u*/
  wcnt = 0UL;
  do {
    __asm("nop");
    wcnt++;
  } while (wcnt < CRYPTO_POWER_WAIT);                            /* wait */
 
  Crypto_30_Hwa_InitMemory();                                    /* Crypto Hwa ReInit */
  Crypto_30_Hwa_Init();                                          /* Crypto Hwa ReInit */
 
  return;
}
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  CALLOUT FUNCTIONS
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK UserVariables>                         DO NOT CHANGE THIS COMMENT!
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
 * |void |- |No return value. |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |boolean |isApplSecBootOk |Result of application secure boot verification. |
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
 * |uint32 |CPUSS_CM7_0_VECTOR_TABLE_BASE |Vector table base address for CM7_0. |
 * |uint32 |CPUSS_CM7_0_PWR_CTL |Power control register for CM7_0. |
 * |uint32 |CYREG_CPUSS_CM7_0_CTL->u32Register |CM7_0 Control register. |
 * |uint32 |CPUSS_CM7_1_VECTOR_TABLE_BASE |Vector table base address for CM7_1. |
 * |uint32 |CPUSS_CM7_1_PWR_CTL |Power control register for CM7_1. |
 * |uint32 |CYREG_CPUSS_CM7_1_CTL->u32Register |CM7_1 Control register. |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8 |isApplSecBootOk |Local variable storing the application secure boot status. |
 * @brief Starts the application cores (CM7_0 and CM7_1) if secure boot verification is successful.
 * @note This function is a callout responsible for initiating the application cores.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(void, VHSM_CODE) vHsm_Hal_StartApplicationCores_Callout(void)
{
  uint8 isApplSecBootOk;
SRAM_CM0_CM7_STEP_RECORD = 34u;
  isApplSecBootOk = handleApplVerificationStatus();
SRAM_CM0_CM7_STEP_RECORD = 35u;
 
SRAM_CM0_CM7_ISBOOTOK_FLG0 = isApplSecBootOk;
 
#if (MEM_MAGIC_FLAG == STD_ON)
  /* Check and set master key valid */
SRAM_CM0_CM7_STEP_RECORD = 36u;
  vHsm_MasterKeyIsValid();
SRAM_CM0_CM7_STEP_RECORD = 37u;
#endif
 
SRAM_CM0_CM7_ISBOOTOK_FLG1 = isApplSecBootOk;
 
  /* Trigger Cid Restore */
SRAM_CM0_CM7_STEP_RECORD = 38u;
  Security_ProcessCidRestoreFromNvm();
SRAM_CM0_CM7_STEP_RECORD = 39u;
 
SRAM_CM0_CM7_ISBOOTOK_FLG2 = isApplSecBootOk;
 
  /* Trigger KeyInfos Determination Processing */
SRAM_CM0_CM7_STEP_RECORD = 40u;
  Security_KeyInfoInitializationAndProcessing();
SRAM_CM0_CM7_STEP_RECORD = 41u;
 
SRAM_CM0_CM7_ISBOOTOK_FLG3 = isApplSecBootOk;
 
  /* Enable HF1 Clock for CM7 Cores */
  CLK_ROOT_SELECT |= 0x80000101U;
 
  if (TRUE == isApplSecBootOk)
  {
SRAM_CM0_CM7_STEP_RECORD = 42u;
    /* M7.0 */
    CPUSS_CM7_0_VECTOR_TABLE_BASE = 0x10090400U; /* Set vtor */
    CPUSS_CM7_0_PWR_CTL = 0x05FA0001U; /* Reset core */
    CPUSS_CM7_0_PWR_CTL = 0x05FA0003U; /* Start core */
    /* QAC Deviations: (No 1279) This macro define for register access and provided by Infineon. So, this warning can ignore and doesn't affect to the current behavior*/
    CYREG_CPUSS_CM7_0_CTL->u32Register &= (uint32_t)~(0x10U); /* Reset wait signal for CPUs */
SRAM_CM0_CM7_STEP_RECORD = 43u;
    /* M7.1 */
    CPUSS_CM7_1_VECTOR_TABLE_BASE = 0x10090400U;  /* Set vtor */
    CPUSS_CM7_1_PWR_CTL = 0x05FA0001U;  /* Reset core */
    CPUSS_CM7_1_PWR_CTL = 0x05FA0003U;  /* Start core */
    /* QAC Deviations: (No 1279) This macro define for register access and provided by Infineon. So, this warning can ignore and doesn't affect to the current behavior*/
    CYREG_CPUSS_CM7_1_CTL->u32Register &= (uint32_t)~(0x10U);  /* Reset wait signal for CPUs */
SRAM_CM0_CM7_STEP_RECORD = 44u;
  }
  else
  {
SRAM_CM0_CM7_STEP_RECORD = 45u;
    while(1); /* Wait forever due to failed verification Appl */
  }
 
}
/** @cond INTERNAL */
#define VHSM_HAL_START_SEC_RAMCODE
#include "MemMap.h"
/** @endcond */
#if (VHSM_HAL_CALLOUT_TRIGGERSOFTWARERESET == STD_ON)
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |void |- |No return value. |
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
 * |volatile boolean |loop |Control variable for the infinite loop. |
 * @brief Callout function executed after a software reset is triggered.
 * @note This function contains an infinite loop, causing the system to stay
 * here indefinitely if a software reset was not successful (i.e., if `loop`
 * remains TRUE, though it's initialized to FALSE). It serves as a fail-safe
 * mechanism to prevent further execution in an unstable state after a reset attempt.
 * This callout is only active when `VHSM_HAL_CALLOUT_TRIGGERSOFTWARERESET` is enabled.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(void, VHSM_CODE) vHsm_Hal_PostReset_Callout(void)
{
  volatile boolean loop = FALSE;
 
  while (loop == TRUE)
  {
    /* If reset was not successful stay here */
  }
}
#endif /*(VHSM_HAL_CALLOUT_TRIGGERSOFTWARERESET == STD_ON)*/
/** @cond INTERNAL */
#define VHSM_HAL_STOP_SEC_RAMCODE
#include "MemMap.h"
/** @endcond */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
 
 
/**********************************************************************************************************************
 *  CALLOUT FUNCTIONS
 *********************************************************************************************************************/
/** @cond INTERNAL */
#define VHSM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
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
 * |void |- |No return value. |
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
 * |uint32 |SRAM_CM0_CM7_KEY_INFO_BASE |Initialized to `KEY_INFOR_THE_UNKNOWN_KEY_INIT`. |
 * @par Reference registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Output registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |CPUSS_CM0_SYSTEM_INT_CTL(5u) |Configured for IRQ5. |
 * |uint32 |CM0P_SCS_ISER |IRQ0, IRQ5, IRQ6, IRQ2, IRQ3 enabled. |
 * |uint32 |CPUSS_CM0_SYSTEM_INT_CTL(7u) |Configured for IRQ2. |
 * |uint32 |CPUSS_CM0_SYSTEM_INT_CTL(1u) |Configured for IRQ3. |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @brief Initializes the vHsm system, including interrupt and IPC configurations.
 * @note This function is a callout for the overall vHsm system initialization. It performs
 * critical setup tasks:
 * 1. Calls `vHsm_StartupCallout()` for initial startup procedures.
 * 2. Maps `vHsm_Hal_ExternalRequestIsr` (IPC_INTR_STRUCT5_INTR) to IRQ5 and enables it.
 * 3. Enables IRQ0 for the flash driver and IRQ5 for vHsm_ExternalRequest interrupts.
 * 4. Enables IRQ6 for the crypto accelerator.
 * 5. Maps IPC 7 ISR to IRQ2 and enables it.
 * 6. Maps IPC 1 ISR to IRQ3 and enables it.
 * 7. Sets interrupt masks for IPC interrupt 7 and IPC interrupt 1 (for IPC4, IPC5, IPC6 channels).
 * 8. Initializes `SRAM_CM0_CM7_KEY_INFO_BASE` to `KEY_INFOR_THE_UNKNOWN_KEY_INIT`.
 * These steps establish essential communication channels and interrupt handling
 * mechanisms required for the HSM's secure operation.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(void, VHSM_CODE) vHsm_SystemInit_Callout(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK SystemInit>                             DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_SystemInit_Callout() */
  vHsm_StartupCallout();
 
  /* map vHsm_Hal_ExternalRequestIsr (IPC_INTR_STRUCT5_INTR) to IRQ5 and enable */
  /* QAC Deviations: (No 1279) This macro define for register access and provided by Infineon. So, this warning can ignore and doesn't affect to the current behavior. */
  CPUSS_CM0_SYSTEM_INT_CTL(5u) = 0x80000005u;
 
  /* Enable IRQ0 for flash driver and IRQ5 for vHsm_ExternalRequest interrupts */
  CM0P_SCS_ISER |= 0x21u;
 
  /* map crypto ISR to IRQ6 and enable (Attention: the value 45 will differ between hardware platforms. E.g. Cluster-Devices=70)  */
  // CPUSS_CM0_SYSTEM_INT_CTL(58) = 0x80000006u;
 
  /* Enable IRQ6 for crypto accelerator */
  CM0P_SCS_ISER |= 0x40u;
 
  /* map IPC 7 ISR to IRQ2 and enable */
  /* QAC Deviations: (No 1279) This macro define for register access and provided by Infineon. So, this warning can ignore and doesn't affect to the current behavior*/
  CPUSS_CM0_SYSTEM_INT_CTL(7u) = 0x80000002u;
 
  /* Enable IRQ2 for crypto accelerator */
  CM0P_SCS_ISER |= 0x04u;
 
  /* map IPC 3 ISR to IRQ3 and enable */
  // CPUSS_CM0_SYSTEM_INT_CTL(3) = 0x80000003u;
 
 
  /* map IPC 1 ISR to IRQ3 and enable */
  /* QAC Deviations: (No 1279) This macro define for register access and provided by Infineon. So, this warning can ignore and doesn't affect to the current behavior*/
  CPUSS_CM0_SYSTEM_INT_CTL(1u) = 0x80000003u;
  /* Enable IRQ3 */
  CM0P_SCS_ISER |= 0x08u;
 
 
  /* Set interrupt mask for IPC interrupt 7 */
  Cy_IPC_Drv_SetInterruptMask(
        Cy_IPC_Drv_GetIntrBaseAddr(7u),
        0u,
        (1uL << 7u)
    );
   
  /* Set interrupt mask (IPC6 -check m0 alive) and (IPC3 - DAP Feature, RMA) for IPC interrupt 1 */
  Cy_IPC_Drv_SetInterruptMask(
        Cy_IPC_Drv_GetIntrBaseAddr(1u),
        0u,
        ((1uL << 3u) | (1uL << 6u))
    );
 
  SRAM_CM0_CM7_KEY_INFO_BASE = KEY_INFOR_THE_UNKNOWN_KEY_INIT;
SRAM_CM0_CM7_CM7_STARTUP_STATE_SHARED = SRAM_CM0_CM7_CM7_STARTUP_STATE;
  SRAM_CM0_CM7_CM7_STARTUP_STATE = CM7_NOT_STARTED;
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
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
 * |void |- |No return value. |
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
 * @brief Callout function executed during the first startup of the vHsm module.
 * @note This function is intended for custom initialization procedures that need to be
 * performed only once when the vHsm module starts for the very first time (e.g., after
 * a power-on reset or initial flashing). The current implementation is a placeholder
 * for user-specific code.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(void, VHSM_CODE) vHsm_FirstStartup_Callout(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK FirstStartup>                           DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_FirstStartup_Callout() */
  Std_ReturnType retVal;
  Crypto_30_LibCv_SizeOfKeyElementsType elementIndex = ZERO_NUM;
 
  retVal = Crypto_30_LibCv_Local_KeyElementSearch(
    CryptoConf_CryptoKey_She_MasterEcuKey,
    CryptoConf_CryptoKeyElement_Crypto_30_LibCv_She_AES_NISTSP80038B,
    &elementIndex);
 
  /* Check if the Key element is valid */
  if ((retVal == E_OK) && (!(Crypto_30_LibCv_IsKeyElementValid(elementIndex))) )
  {
    Csm_KeySetValid(CsmConf_CsmKey_CsmKey_She_MasterEcuKey);
  }
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
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
 * |void |- |No return value. |
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
 * @brief Callout function invoked when an invalid NVM block is detected.
 * @note This function is a placeholder for user-defined error handling or recovery
 * procedures to be executed when the NVM module detects an invalid block.
 * This could indicate data corruption or unexpected NVM content. Implementations
 * might include logging the error, attempting repair, or triggering a system reset.
 */
 /* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(void, VHSM_CODE) vHsm_NvM_InvalidBlockDetected_Callout(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK InvalidBlock>                           DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_NvM_InvalidBlockDetected_Callout() */
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
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
 * |void |- |No return value. |
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
 * @brief Callout function for the first stage of vHsm initialization (InitOne).
 * @note This function performs early initialization steps for the vHsm module
 * and its dependencies.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(void, VHSM_CODE) vHsm_InitOne_Callout(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK InitOne>                               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_InitOne_Callout() */
 
  /* Workaround for ESCAN00111503 - TRNG is stuck in endless loop when prefetching is used. */
  Crypto_30_Hwa_Hw_Init();
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Call automatically detected initialization functions. */
  /* Calls can be avoided by encapsulate them with a preprocessor opened in pre and closed in post user block. */
 
  /* Initialization phase INIT_MEMORY */
  CryIf_InitMemory();
  Crypto_30_Hwa_InitMemory();
  Crypto_30_LibCv_InitMemory();
  Csm_InitMemory();
  vMemAccM_InitMemory();
 
  /* Initialization phase INIT_ONE */
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK InitOne_Post>                           DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_InitOne_Callout() */
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
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
 * |void |- |No return value. |
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
 * |uint32 |FLASHC_FLASH_CTL |Updated to suppress ECC errors. |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @brief Callout function for the second stage of vHsm initialization (InitTwo).
 * @note This function performs a broader range of module initializations and system configurations
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(void, VHSM_CODE) vHsm_InitTwo_Callout(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK InitTwo>                                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_InitTwo_Callout() */
 
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Call automatically detected initialization functions. */
  /* Calls can be avoided by encapsulate them with a preprocessor opened in pre and closed in post user block. */
  Crypto_30_Hwa_Init();
  Crypto_30_LibCv_Init();
  Fls_30_vMemAccM_Init();
  vMemAccM_Init();
  CryIf_Init();
  Fee_30_SmallSector_Init();
  Csm_Init();
  NvM_Init();
 
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK InitTwo_Post>                           DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_InitTwo_Callout() */
  CM0_Debug_Init();
#if (VHSM_OS_SUPPORT == STD_OFF)
  /* Enable interrupts globally (compiler dependent) */
# if defined VHSM_COMP_GREENHILLS
  __MSR(__PRIMASK, 0x0U);
# elif defined VHSM_COMP_IAR
  __set_PRIMASK(0x0U);
# endif
#endif
  /* Suppress ECC errors */
  FLASHC_FLASH_CTL |= (FLASH_WORK_ERR_SILENT);
#if (MEM_MAGIC_FLAG == STD_ON)
  vHsm_HandleMemoryLayoutVersion();
#endif
  updateDualBankMagicWord();
  /* Disable slient mode */
  /* Keep SILENT_MODE to avoid workflash error */
  // FLASHC_FLASH_CTL &= ~(FLASH_WORK_ERR_SILENT);
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}
 
#if (VHSM_NVM_PRE_READ_ALL == STD_ON)
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |void |- |No return value. |
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
 * @brief Callout function for pre-reading all NVM blocks, if enabled.
 * @note This function is a placeholder for custom logic that needs to execute
 * before the third stage of vHsm initialization (`InitThree`), specifically
 * when `VHSM_NVM_PRE_READ_ALL` is enabled. It is typically used to pre-fetch
 * all NVM data, ensuring that data is available in RAM before it is needed
 * by later initialization steps.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(void, VHSM_CODE) vHsm_InitThree_Pre_Callout(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK InitThree_Pre>                          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
 
  /* Add implementation of vHsm_InitThree_Pre_Callout() */
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
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
 * |void |- |No return value. |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8[] |getSeed |Buffer to store the generated random seed. |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8[] |getSeed |Updated with a newly generated random seed. |
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
 * |uint32 |seedlength |Length of the seed to generate. |
 * |Crypto_30_LibCv_SizeOfKeyElementsType |elementIndexTypeX |Index for the SHE TypeX encryption key. |
 * |Std_ReturnType |retValTypeX |Return value for cryptographic operations. |
 * @brief Callout function for the third stage of vHsm initialization (InitThree).
 * @note This function performs cryptographic initializations:
 * 1. Generates a random seed using `Csm_RandomGenerate()` with `CsmJob_Random`.
 * 2. Sets the `CsmKey_Random` key as valid and seeds the random number generator
 * using `Csm_RandomSeed()`.
 * 3. Searches for the `She_TypeX_Encypt_Key` element. If found and not yet valid,
 * it sets this key as valid.
 * 4. Conditionally calls `KeyM_MainFunction()` and `KeyM_Cert_IsBusy()` if `KEYM_H` is defined,
 * to ensure KeyM startup is finished.
 * 5. Conditionally calls `vHsm_Hal_StartApplicationCores_Callout()` if `VHSM_START_APPL_BEFORE_SECUBOOT` is defined.
 * This stage ensures that cryptographic services are properly initialized and ready for use.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(void, VHSM_CODE) vHsm_InitThree_Callout(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK InitThree>                             DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_InitThree_Callout() */
  uint32 seedlength = 16u;
  Crypto_30_LibCv_SizeOfKeyElementsType elementIndexTypeX = ZERO_NUM;
  Std_ReturnType retValTypeX;
 
  /*Call the random generate csm job TRNG */
  Csm_RandomGenerate(CsmConf_CsmJob_CsmJob_Random, getSeed, &seedlength);
    /* Call Set key valid */
  Csm_KeySetValid(CsmConf_CsmKey_CsmKey_Random);
  /* Call random seed */
  Csm_RandomSeed(CsmConf_CsmKey_CsmKey_Random, getSeed, seedlength);
 
  retValTypeX = Crypto_30_LibCv_Local_KeyElementSearch(
    CryptoConf_CryptoKey_She_TypeX_Encypt_Key,
    CryptoConf_CryptoKeyElement_Crypto_30_LibCv_She_AES_NISTSP80038A,
    &elementIndexTypeX);
 
  /* QAC Deviations: (No 3383) Configuration and Generation rule of Crypto module is made sure the overflow does not occur. */
  /* Check if the Key element is valid */
  if ((retValTypeX == E_OK) && (!(Crypto_30_LibCv_IsKeyElementValid(elementIndexTypeX))) )
  {
    /* Set the key to be valid the first time */
    // Csm_KeySetValid(CsmConf_CsmKey_CsmKey_TypeX_Encypt);
    SRAM_CM0_CM7_KEYSETVALID_TYPEX = 1u;
  }
 
  /* Initialize MCWDT[1] */
SRAM_CM0_CM7_STEP_RECORD = 18u;
  vHsm_WatchdogTimerInit(MCWDT1);
SRAM_CM0_CM7_STEP_RECORD = 19u;
#if defined KEYM_H
  /* Ensure Startup Handling of KeyM is finished, task state is busy during startup */
SRAM_CM0_CM7_STEP_RECORD = 20u;
  do
  {
SRAM_CM0_CM7_STEP_RECORD = 22u;
    KeyM_MainFunction();
SRAM_CM0_CM7_STEP_RECORD = 23u;
  } while(KeyM_Cert_IsBusy());
SRAM_CM0_CM7_STEP_RECORD = 24u;
#endif /* KEYM_H */
 
#ifdef VHSM_START_APPL_BEFORE_SECUBOOT
SRAM_CM0_CM7_STEP_RECORD = 25u;
  vHsm_Hal_StartApplicationCores_Callout();
SRAM_CM0_CM7_STEP_RECORD = 26u;
#endif
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Call automatically detected initialization functions. */
  /* Calls can be avoided by encapsulate them with a preprocessor opened in pre and closed in post user block. */
SRAM_CM0_CM7_STEP_RECORD = 27u;
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK InitThree_Post>                         DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_InitThree_Callout() */
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
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
 * |void |- |No return value. |
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
 * @brief Callout function to start the application cores after vHsm initialization.
 * @note This function is responsible for the final steps before jumping to the main application.
 * It ensures that critical cryptographic hardware (TRNG) is properly configured by
 * entering and exiting a `Crypto_30_Hwa_CRYPTO_30_HWA_EXCLUSIVE_AREA_3` critical section
 * to enable TRNG interrupts if `CRYPTO_30_HWA_TRNG_PREFETCH_WITH_INTERRUPT` is enabled.
 * If `VHSM_START_APPL_BEFORE_SECUBOOT` is not defined, it then calls `vHsm_Hal_StartApplicationCores()`
 * to actually initiate the application cores.
 * This function also includes placeholders for pre-application start and post-application start
 * custom implementations.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(void, VHSM_CODE) vHsm_StartApplicationCores_Callout(void)
{
  /* The application cores shall be started in this callout */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK PreApplStart>                           DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_PreApplicationStart_Callout() */
SRAM_CM0_CM7_STEP_RECORD = 28u;
  SchM_Enter_Crypto_30_Hwa_CRYPTO_30_HWA_EXCLUSIVE_AREA_3();
SRAM_CM0_CM7_STEP_RECORD = 29u;
# if (CRYPTO_30_HWA_TRNG_PREFETCH_WITH_INTERRUPT == STD_ON) /* COV_CRYPTO_30_HWA_HARDWARE_DEPENDENT_FEATURE */
  Crypto_30_Hwa_Hw_TrngEnableIrq();
SRAM_CM0_CM7_STEP_RECORD = 30u;
# endif
  SchM_Exit_Crypto_30_Hwa_CRYPTO_30_HWA_EXCLUSIVE_AREA_3();
SRAM_CM0_CM7_STEP_RECORD = 31u;
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
 
 /**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK ApplStart>                              DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#ifndef VHSM_START_APPL_BEFORE_SECUBOOT
SRAM_CM0_CM7_STEP_RECORD = 32u;
 vHsm_Hal_StartApplicationCores();
SRAM_CM0_CM7_STEP_RECORD = 33u;
#endif
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
 
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK PostApplStart>                          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_PostApplicationStart_Callout() */
 
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
 
}
 
#if (VHSM_SECURE_BOOT == STD_ON)
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |vHsm_SecureBootGroupIterType |secureBootGroupIndex |Index of the secure boot group. |
 * |uint32 |secureBootGroupId |Identifier of the secure boot group. |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |boolean |allowAutostart |TRUE if autostart is allowed for this group; FALSE otherwise. |
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
 * @brief Callout function to determine if autostart is allowed for a secure boot group.
 * @note This function is a placeholder that decides whether a specific secure boot group
 * should be allowed to autostart.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(boolean, VHSM_CODE) vHsm_Custom_IsSecureBootAllowAutostart_Callout(
  vHsm_SecureBootGroupIterType secureBootGroupIndex,
  uint32 secureBootGroupId)
{
  /* Decide if the autostart shall be performed for this group or not.
   *  E.g. Use the current reset vectors to make a decision. */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK SecureBootAllowAutostart>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_Custom_IsSecureBootAllowAutostart_Callout() */
  (void)secureBootGroupIndex;
  (void)secureBootGroupId;
  return FALSE;
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}
 
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |vHsm_SecureBootGroupIterType |secureBootGroupIndex |Index of the secure boot group. |
 * |uint32 |secureBootGroupId |Identifier of the secure boot group. |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |boolean |allowCyclicVerification |TRUE if cyclic verification is allowed for this group; FALSE otherwise. |
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
 * @brief Callout function to determine if cyclic verification is allowed for a secure boot group.
 * @note This function determines whether the cyclic verification process should be performed
 * for a specific secure boot group.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(boolean, VHSM_CODE) vHsm_Custom_IsSecureBootAllowCyclicVerification_Callout(
  vHsm_SecureBootGroupIterType secureBootGroupIndex,
  uint32 secureBootGroupId)
{
  /* Decide if the cycclic verification shall be performed for this group or not. */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK SecureBootAllowCyclicVerification>      DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_Custom_IsSecureBootAllowCyclicVerification_Callout() */
 
 
   return TRUE;
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}
#endif
 
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |cryptoKeyId |Identifier of the cryptographic key related to the sanction. |
 * |vHsm_SecureBootInfoType* |vHsm_SecureBootInfoPtr |Pointer to structure containing secure boot information. |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |Std_ReturnType |retVal |E_OK if the sanction measure is applied successfully. |
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
 * @brief Callout function to perform a sanction measure when secure boot fails for a segment.
 * @note This function is invoked when the secure boot verification fails for a particular segment.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(Std_ReturnType, VHSM_CODE) vHsm_Custom_SecureBootSanction_Callout(uint32 cryptoKeyId,
  P2VAR(vHsm_SecureBootInfoType, AUTOMATIC, VHSM_APPL_VAR) vHsm_SecureBootInfoPtr)
{
  /* The secure boot failed for this segment.
     Perform a measure, e.g. write something to the error log or perform a reset. */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK SecureBootSanction>                     DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_Custom_SecureBootSanction_Callout() */
  (void)cryptoKeyId;
  (void)vHsm_SecureBootInfoPtr;
 
  return E_OK;
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}
 
#if(VHSM_SECURE_BOOT_SEGMENT_SUCCESS_CALLOUT == STD_ON)
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |cryptoKeyId |Identifier of the cryptographic key related to the successful segment. |
 * |vHsm_SecureBootInfoType* |vHsm_SecureBootInfoPtr |Pointer to structure containing secure boot information. |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |void |- |No return value. |
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
 * @brief Callout function invoked when a secure boot segment successfully passes verification.
 * @note This function is a placeholder for custom logic to be executed when a secure boot
 * segment successfully completes its verification. This could be used for logging,
 * updating status flags, or performing other actions that depend on the successful
 * verification of a specific code segment. This callout is only enabled if
 * `VHSM_SECURE_BOOT_SEGMENT_SUCCESS_CALLOUT` is active.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(void, VHSM_CODE) vHsm_SecureBoot_SegmentSuccess_Callout(
  uint32 cryptoKeyId,
  P2VAR(vHsm_SecureBootInfoType, AUTOMATIC, VHSM_APPL_VAR) vHsm_SecureBootInfoPtr)
{
  /* The secure boot was successful this segment. */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK SecureBootSuccess>                     DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_SecureBoot_SegmentSuccess_Callout() */
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}
#endif
 
# if (VHSM_SECURE_BOOT_UPDATE == STD_ON) || (VHSM_VERMETHOD_EXTERNAL_SL_AVAILABLE == STD_ON)
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |secureBootGroupId |Identifier of the secure boot group. |
 * |uint32 |versionOfCurrentSegmentTable |Version of the currently active segment table. |
 * |const uint8* |segmentTableStartPtr |Pointer to the start of the new segment table. |
 * |uint32 |segmentListLength |Length of the new segment list. |
 * |uint32* |newRevisionPtr |Pointer to the new revision value. |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |Std_ReturnType |retVal |E_OK if the new revision is acceptable; E_NOT_OK otherwise. |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |versionOfCurrentSegmentTable |Currently active segment table version. |
 * |uint32* |newRevisionPtr |New revision value to be checked. |
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
 * |Std_ReturnType |retVal |Local return value for the function. |
 * @brief Callout function to validate a new revision during secure boot update.
 * @note This function is a placeholder for custom logic to verify the acceptability
 * of a `newRevisionPtr` during a secure boot update. For instance, an implementation
 * could compare `versionOfCurrentSegmentTable` with `*newRevisionPtr` to ensure
 * the new revision is strictly greater than the old one, returning `E_NOT_OK` if
 * the revision is not acceptable (e.g., a downgrade attempt). The current implementation
 * simply returns `E_OK`, allowing any new revision. This callout is enabled when
 * `VHSM_SECURE_BOOT_UPDATE` or `VHSM_VERMETHOD_EXTERNAL_SL_AVAILABLE` is active.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(Std_ReturnType, VHSM_CODE) vHsm_SecureBoot_Revision_Callout(
  uint32 secureBootGroupId,
  uint32 lastStoredRevision,
  P2CONST(uint8, AUTOMATIC, VHSM_APPL_VAR) segmentTableStartPtr,
  uint32 segmentListLength,
  P2VAR(uint32, AUTOMATIC, VHSM_APPL_VAR) newRevisionPtr)
{
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK SecureBoot_Revision>              DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  Std_ReturnType retVal = E_OK;
 
  /* e.g. Check that revision is bigger than the old one and reject the update.
  if (lastStoredRevision >= *newRevisionPtr)
  {
  retVal = E_NOT_OK;
  }
   */
 
  return retVal;
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}
#endif
 
# if (VHSM_VERMETHOD_EXTERNAL_SL_AVAILABLE == STD_ON)
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |const uint8* |address |Start address of the memory region to be cleared from cache. |
 * |uint32 |length |Length of the memory region to be cleared. |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |void |- |No return value. |
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
 * @brief Callout function for clearing cache entries related to secure boot.
 * @note This function is a placeholder to implement platform-specific cache clearing
 * operations for a given memory region defined by `address` and `length`. This is
 * typically required during secure boot updates or verification processes to ensure
 * that the CPU always fetches the most recent code/data from memory rather than
 * stale cache entries. This callout is enabled when `VHSM_VERMETHOD_EXTERNAL_SL_AVAILABLE`
 * is active.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(void, VHSM_CODE) vHsm_SecureBoot_CacheClearing_Callout(
  P2CONST(uint8, AUTOMATIC, VHSM_APPL_VAR) address,
  uint32 length)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK SecureBoot_CacheClearing>              DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}
 
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |groupIdx |Index of the secure boot group. |
 * |vHsm_SecureBootRecoveryReasonType |recoveryReason |Reason for the secure boot recovery. |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |boolean |performRecovery |TRUE if a recovery measure should be performed; FALSE otherwise. |
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
 * @brief Callout function to decide whether to perform a secure boot recovery measure.
 * @note This function is a placeholder that determines if a recovery measure should be
 * initiated after a secure boot issue. The decision can be based on `groupIdx` and
 * `recoveryReason`. The current implementation always returns `FALSE`, meaning no
 * recovery is performed by default. In a real system, this could trigger fallback
 * mechanisms or alternate boot sequences. This callout is enabled when
 * `VHSM_VERMETHOD_EXTERNAL_SL_AVAILABLE` is active.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(boolean, VHSM_CODE) vHsm_SecureBoot_PerformRecovery_Callout(
  uint32 groupIdx,
  vHsm_SecureBootRecoveryReasonType recoveryReason)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK SecureBoot_PerformRecovery>              DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  (void)groupIdx;
  (void)recoveryReason;
 
  return FALSE;
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}
# endif
 
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |void |- |No return value. |
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
 * @brief Triggers a software reset of the system.
 * @note This function is a callout that initiates a software reset of the microcontroller.
 * It does so by calling `vHsm_Hal_TriggerSoftwareReset()`, which would contain the
 * platform-specific code to perform the reset. This is a critical function often
 * used for error recovery, firmware updates, or transitions between different
 * operational modes.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(void, VHSM_CODE) vHsm_TriggerSoftwareReset_Callout(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK TriggerSoftwareReset>                   DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_TriggerSoftwareReset_Callout() */
  vHsm_Hal_TriggerSoftwareReset();
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
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
 * |void |- |No return value. |
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
 * @brief Callout function to process NVM blocks.
 * @note This function is a placeholder for custom logic that needs to be executed
 * to process NVM (Non-Volatile Memory) blocks. This could involve reading, writing,
 * or validating data in specific NVM blocks based on application requirements.
 * The current implementation is empty, serving as a hook for user-defined NVM operations.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(void, VHSM_CODE) vHsm_NvM_ProcessBlock_Callout(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK ProcessBlock>                           DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_NvM_ProcessBlock_Callout() */
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
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
 * |void |- |No return value. |
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
 * @brief Executes main functions for NVM-related modules in a cyclic manner.
 * @note This function serves as a central point for calling the `MainFunction`
 * of various NVM-related modules, ensuring their regular processing. This includes:
 * `NvM_MainFunction()`, `Fee_30_SmallSector_MainFunction()`, `Fls_30_vMemAccM_MainFunction()`,
 * `vMemAccM_MainFunction()`, and `vMem_30_Traveo2Cyp01_MainFunction()`. These calls
 * ensure that NVM operations, flash management, and memory access mechanisms
 * are processed periodically. This function also includes a post-user block for
 * additional custom calls to `Fls_30_vMemAccM_MainFunction()`.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(void, VHSM_CODE) vHsm_NvMainFunctions_Callout(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK NvMainFunctions>                        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_NvMainFunctions_Callout() */
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Call automatically detected memory functions. */
  /* Calls can be avoided by encapsulate them with a preprocessor opened in pre and closed in post user block. */
  NvM_MainFunction();
  Fee_30_SmallSector_MainFunction();
  Fls_30_vMemAccM_MainFunction();
  vMemAccM_MainFunction();
  vMem_30_Traveo2Cyp01_MainFunction();
  vMemAccM_MainFunction();
  Fls_30_vMemAccM_MainFunction();
 
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK NvMainFunctions_Post>                   DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
 
  Fls_30_vMemAccM_MainFunction();
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}
 
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 *
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 *
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 *
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8|ISR1_Handler_TriggerFlag|Flag indicating if ISR1_Handler triggered during key clear|
 * |uint8|Exterrnal_Clear_Rma_Request|Request status for secure key clear before RMA|
 * |uint8|Repro_KeyCalloutStatus|Status for SHE Key4 writing operation|
 * |uint8|TypeX_KeycalloutStatus|Status for TypeX key writing operation|
 * |uint8|Master_KeyCalloutStatus|Status for Master ECU key writing operation|
 * |uint8|Mac_KeyCalloutStatus|Status for MAC key writing operation|
 * |uint8|intSleep|Sleep mode indicator|
 *
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8|ISR1_Handler_TriggerFlag|Reset to 0u at the start of tracking ISR1_Handler|
 * |uint8|Exterrnal_Clear_Rma_Request|Updated to SECURE_NO_CLEAR_REQUEST after processing|
 * |uint8|Repro_KeyCalloutStatus|Reset to 0u after successful SHE Key4 writing|
 * |uint8|TypeX_KeycalloutStatus|Reset to 0u after successful TypeX key writing|
 * |uint8|Master_KeyCalloutStatus|Reset to 0u after successful Master ECU key writing|
 * |uint8|Mac_KeyCalloutStatus|Reset to 0u after successful MAC key writing|
 *
 * @par Reference registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |SRSS->unPWR_CTL.u32Register|Power control register|Used to check deep sleep readiness|
 *
 * @par Output registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 *
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |boolean|getResult|Result of checking CM7 sleep status|
 *
 * @brief  Main cyclic callout function for HSM. Handles deep sleep entry, custom main function call, secure key clear before RMA, key info processing, and startup check.
 * @note   This function manages periodic security actions, including entering deep sleep if required, handling key clear before RMA requests, processing key info updates following successful key writing, and performing startup checks.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(void, VHSM_CODE) vHsm_MainFunctionCyclic_Callout(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK MainFunctionCyclic>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_MainFunctionCyclic_Callout() */
  boolean getResult;
 
SRAM_CM0_CM7_STEP_RECORD = 141u;
  if( GO_TO_SLEEP == intSleep )
  {
    /* DeepSleep */
    /* QAC Deviations: (No 1279) This macro define for register access and provided by Infineon. So, this warning can ignore and doesn't affect to the current behavior*/
    if(0u != _FLD2VAL(SRSS_PWR_CTL_LPM_READY, SRSS->unPWR_CTL.u32Register))  
    {
SRAM_CM0_CM7_STEP_RECORD = 142u;
      getResult = check_cm7_sleep_status();
SRAM_CM0_CM7_STEP_RECORD = 143u;
      if (getResult == TRUE)
      {
SRAM_CM0_CM7_STEP_RECORD = 144u;
        crypto_hw_disable();
SRAM_CM0_CM7_STEP_RECORD = 145u;
        switch_regulator_sleep_entry();
SRAM_CM0_CM7_STEP_RECORD = 146u;
        cm0p_cache_off();
SRAM_CM0_CM7_STEP_RECORD = 147u;
        Cy_SysPm_DeepSleep(CY_SYSPM_WAIT_FOR_INTERRUPT);
SRAM_CM0_CM7_STEP_RECORD = 148u;
        cm0p_cache_on();
SRAM_CM0_CM7_STEP_RECORD = 149u;
        switch_regulator_sleep_exit();
SRAM_CM0_CM7_STEP_RECORD = 150u;
        crypto_hw_enable();
SRAM_CM0_CM7_STEP_RECORD = 151u;
      }
    }
  }
  else{
    /* NOP */
  }
SRAM_CM0_CM7_STEP_RECORD = 152u;
  vHsm_Custom_MainFunction();
SRAM_CM0_CM7_STEP_RECORD = 153u;
  /* Start tracking ISR1_Handler if it trigger during this time*/
  ISR1_Handler_TriggerFlag = 0u;
  if (SECURE_CLEAR_KEY_BEFORE_RMA_REQUEST == Exterrnal_Clear_Rma_Request)
  {
SRAM_CM0_CM7_STEP_RECORD = 154u;
    ClearKeyInfoBeforeRma();
SRAM_CM0_CM7_STEP_RECORD = 155u;
    /* If ISR1_Handler trigger at this time, ignore set value for Exterrnal_Clear_Rma_Request*/
    DisableAllInterrupts();
SRAM_CM0_CM7_STEP_RECORD = 156u;
    if(ISR1_Handler_TriggerFlag == 0u)
    {
      Exterrnal_Clear_Rma_Request = SECURE_NO_CLEAR_REQUEST;
SRAM_CM0_CM7_STEP_RECORD = 157u;
    }
SRAM_CM0_CM7_STEP_RECORD = 158u;
    EnableAllInterrupts();
SRAM_CM0_CM7_STEP_RECORD = 159u;
  }
 
  if (SHEKEY4_IS_KEYWRITINGSUCCESS == (Repro_KeyCalloutStatus & SHEKEY4_IS_KEYWRITINGSUCCESS))
  {
SRAM_CM0_CM7_STEP_RECORD = 160u;
    Security_SheKey4Info_Processing();
    Repro_KeyCalloutStatus = 0u;
SRAM_CM0_CM7_STEP_RECORD = 161u;
  }
 
  if (TYPEX_KEYWRITINGSUCCESS == (TypeX_KeycalloutStatus & TYPEX_KEYWRITINGSUCCESS))
  {
SRAM_CM0_CM7_STEP_RECORD = 162u;
    Security_TypeXCommonKeyInfo_Processing();
    TypeX_KeycalloutStatus = 0u;
SRAM_CM0_CM7_STEP_RECORD = 163u;
  }
 
  if ((MASTER_ECU_KEY_WRITING_SUCCESS == (Master_KeyCalloutStatus & MASTER_ECU_KEY_WRITING_SUCCESS)) ||
      (MAC_KEY_WRITING_SUCCESS == (Mac_KeyCalloutStatus & MAC_KEY_WRITING_SUCCESS)))
  {
SRAM_CM0_CM7_STEP_RECORD = 164u;
    Security_ProcessCidSaveToNvm();
    Master_KeyCalloutStatus = 0u;
SRAM_CM0_CM7_STEP_RECORD = 165u;
    if (MAC_KEY_WRITING_SUCCESS == (Mac_KeyCalloutStatus & MAC_KEY_WRITING_SUCCESS))
    {
SRAM_CM0_CM7_STEP_RECORD = 166u;
      Security_Mac_Key_Processing();
      Mac_KeyCalloutStatus = 0u;
SRAM_CM0_CM7_STEP_RECORD = 167u;
    }
  }
SRAM_CM0_CM7_STEP_RECORD = 168u;
  vHsm_CM7_Startup_Check(MCWDT1);
SRAM_CM0_CM7_STEP_RECORD = 169u;
 
  if (SRAM_CM0_CM7_MAIN_FUNCTION_FREEZE < UINT16_MAX)
  {
    SRAM_CM0_CM7_MAIN_FUNCTION_FREEZE++;
  }
  else
  {
    SRAM_CM0_CM7_MAIN_FUNCTION_FREEZE = 0;
  }
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Call automatically detected cyclic functions. */
  /* Calls can be avoided by encapsulate them with a preprocessor opened in pre and closed in post user block. */
 
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK MainFunctionCyclic_Post>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}
 
#if(VHSM_LOG_EVENT_CALLOUT_ENABLED == STD_ON)
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |logEventId |Identifier of the log event. |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |void |- |No return value. |
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
 * @brief Callout function for logging events.
 * @note This function is a placeholder for custom event logging logic. It is
 * invoked when a specific log event (`logEventId`) occurs within the vHsm module.
 * Implementations might include writing the event to a diagnostic buffer,
 * triggering a notification, or storing it in NVM. This callout is enabled
 * if `VHSM_LOG_EVENT_CALLOUT_ENABLED` is active.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(void, VHSM_CODE) vHsm_Log_Event_Callout(uint32 logEventId)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK EventCallout>                           DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_Log_Event_Callout() */
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}
#endif
 
#if(VHSM_LOG_THRESHOLD_CALLOUT_ENABLED == STD_ON)
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |logEventId |Identifier of the log event associated with the threshold. |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |void |- |No return value. |
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
 * @brief Callout function invoked when a log fill level threshold is reached.
 * @note This function is a placeholder for custom logic to be executed when
 * the internal log buffer for a specific `logEventId` reaches a predefined
 * fill level threshold. Implementations might involve triggering data offloading,
 * signaling a warning, or taking other preventive measures to avoid log overflow.
 * This callout is enabled if `VHSM_LOG_THRESHOLD_CALLOUT_ENABLED` is active.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(void, VHSM_CODE) vHsm_Log_FillLevelThreshold_Callout(uint32 logEventId)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK FillLevelThresholdCallout>              DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_Log_FillLevelThreshold_Callout() */
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}
#endif
 
#if (VHSM_LOG_TIMESTAMP_CALLOUT_ENABLED == STD_ON)
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |LogEventId |Identifier of the log event for which to retrieve a timestamp. |
 * |uint8* |timestampPtr |Pointer to a buffer where the timestamp will be stored. |
 * |uint32* |timestampLengthPtr |Pointer to a variable holding the expected timestamp length, and will store the actual length. |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |void |- |No return value. |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8* |timestampPtr |Buffer filled with timestamp data. |
 * |uint32* |timestampLengthPtr |Updated with the actual length of the retrieved timestamp. |
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
 * @brief Callout function to retrieve a timestamp for a given log event.
 * @note This function is a placeholder for custom logic to provide a timestamp
 * for a specific `LogEventId`. The timestamp data should be written to the
 * `timestampPtr` buffer, and its actual length updated in `timestampLengthPtr`.
 * This is used for logging mechanisms that require time information for events.
 * This callout is enabled if `VHSM_LOG_TIMESTAMP_CALLOUT_ENABLED` is active.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(void, VHSM_CODE) vHsm_Log_GetTimestamp_Callout(
  uint32 LogEventId,
  P2VAR(uint8, AUTOMATIC, VHSM_APPL_VAR) timestampPtr,
  P2VAR(uint32, AUTOMATIC, VHSM_APPL_VAR) timestampLengthPtr)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK GetTimetsampCallout>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_Log_GetTimestamp_Callout() */
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
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
 * |Std_ReturnType |retVal |E_OK if the RAM loop should be entered; E_NOT_OK otherwise. |
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
 * |Std_ReturnType |retVal |Local variable to store the return status. |
 * @brief Callout function to determine if the RAM loop should be entered.
 * @note This function serves as a hook to decide whether the main RAM loop
 * (a continuous execution loop in RAM) should be initiated. The current
 * implementation always returns `E_OK`, meaning the RAM loop is always
 * entered. In specific scenarios, `retVal` could be set to `E_NOT_OK` to
 * prevent entering the RAM loop, for example, during a critical error or
 * before a system shutdown.
 */
/* author Vector Informatik GmbH */

/* date 2024-07-24 */
/************************************************************************************************/
FUNC(Std_ReturnType, VHSM_CODE) vHsm_PreRamLoop_Callout(void)
{
  Std_ReturnType retVal = E_OK;
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK PreRamLoop>                                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_PreRamLoop_Callout() */
  /* If Ramloop shall not be entered, set retVal to E_NOT_OK. */
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
 return retVal;
}
 
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8 |operation |The type of flash operation to perform. |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |Std_ReturnType |retVal |E_OK if the flash operation is successful; E_NOT_OK otherwise. |
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
 * @brief Callout function for performing custom flash operations.
 * @note This function serves as a hook to implement custom flash operations
 * based on the `operation` parameter. It is a placeholder where specific
 * flash erase, write, or read operations can be integrated as needed by
 * the application. The current implementation returns `E_OK`, indicating
 * success without performing any specific flash operation.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(Std_ReturnType, VHSM_CODE) vHsm_FlashOperation_Callout(uint8 operation)
{
  /* Callout to for flash operations */
  /**********************************************************************************************************************
  * DO NOT CHANGE THIS COMMENT!           <USERBLOCK FlashOperation>                         DO NOT CHANGE THIS COMMENT!
  *********************************************************************************************************************/
  /* Add implementation of vHsm_FlashOperation_Callout() */
  return E_OK;
 
  /**********************************************************************************************************************
  * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
  *********************************************************************************************************************/
}
 
#if(VHSM_JOB_PROCESSING_CALLOUT == STD_ON)
 
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |jobObjectId |Identifier of the cryptographic job object. |
 * |Crypto_JobType* |jobPtr |Pointer to the cryptographic job structure. |
 * |boolean |isValid |Boolean indicating if the job is considered valid by the HSM. |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |Std_ReturnType |retVal |E_OK if the job processing is allowed; E_NOT_OK to disallow. |
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
 * @brief Callout function to implement validity checks for cryptographic jobs.
 * @note This function serves as a hook to enforce custom rules or restrictions
 * on the processing of cryptographic jobs.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(Std_ReturnType, VHSM_CODE) vHsm_CryptoJobProcessing_Callout(
  uint32 jobObjectId,
  P2VAR(Crypto_JobType, AUTOMATIC, VHSM_APPL_VAR) jobPtr,
  boolean isValid)
{
  /* Callout to implement crypto job validity checks */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK CryptoJobProcessing>                   DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_CryptoJobProcessing_Callout()
     e.g. disallow processing of jobs on specific driver objects during runtime */
 
  return E_OK;
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}
 
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32 |jobObjectId |Identifier of the key management job object. |
 * |vHsm_KeyM_JobType* |jobPtr |Pointer to the key management job structure. |
 * |boolean |isValid |Boolean indicating if the job is considered valid by the HSM. |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |Std_ReturnType |retVal |E_OK if the key job processing is allowed; E_NOT_OK to disallow. |
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
 * @brief Callout function to implement validity checks for key management jobs.
 * @note This function serves as a hook to enforce custom rules or restrictions
 * on key management operations.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(Std_ReturnType, VHSM_CODE) vHsm_KeyJobProcessing_Callout(
  uint32 jobObjectId,
  P2VAR(vHsm_KeyM_JobType, AUTOMATIC, VHSM_APPL_VAR) jobPtr,
  boolean isValid)
{
  /* Callout to implement crypto job validity checks */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK KeyJobProcessing>                   DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_KeyJobProcessing_Callout()
     e.g. disallow processing of key operations on specific keys during runtime */
 
  return E_OK;
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}
#endif
/** @cond INTERNAL */
#define VHSM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
 
 
#if(VHSM_ENABLE_RAM_LOOP_CALLOUT == STD_ON)
 
# define VHSM_START_SEC_RAMCODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
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
 * |Std_ReturnType |retVal |E_OK if the RAM loop should continue; E_NOT_OK to exit the loop. |
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
 * |Std_ReturnType |retVal |Local variable to store the return status. |
 * @brief Callout function for the RAM loop, if enabled.
 * @note This function provides a hook for custom code that needs to be executed
 * repeatedly within the RAM loop. It can be used for tasks that must run
 * continuously after basic initialization but before the main application
 * fully takes over. The current implementation always returns `E_OK`, causing
 * the RAM loop to continue indefinitely. `retVal` could be set to `E_NOT_OK`
 * to exit the RAM loop under specific conditions. This callout is enabled
 * if `VHSM_ENABLE_RAM_LOOP_CALLOUT` is active.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(Std_ReturnType, VHSM_CODE) vHsm_RamLoop_Callout(void)
{
  Std_ReturnType retVal = E_OK;
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK RamLoop>                                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_RamLoop_Callout() */
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
 return retVal;
}
/** @cond INTERNAL */
# define VHSM_STOP_SEC_RAMCODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif
 
#if (VHSM_FIRMWARE_UPDATE == STD_ON)
 
#define VHSM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
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
 * |void |- |No return value. |
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
 * @brief Callout function executed before jumping to the updater during a firmware update.
 * @note This function provides a hook for custom actions that need to be performed
 * immediately before the system transitions to the firmware updater (bootloader).
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(void, VHSM_CODE) vHsm_FirmwareUpdate_PreJmpToUpdater_Callout(void)
{
  /* Jump to updater will be performed after this callout */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK PreJmpToUpdaterStart>                   DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_FirmwareUpdate_PreJmpToUpdater_Callout()
     e.g. disable Systick interrupt when OS is used. */
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}
/** @cond INTERNAL */
#define VHSM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
 
# define VHSM_START_SEC_CODE_MAC_CALLOUT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/** @endcond */
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8* |keyPtr |Pointer to a buffer where the secret MAC key will be stored. |
 * |uint32* |length |Pointer to a variable holding the expected key length, and will store the actual length. |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |Std_ReturnType |retVal |E_OK if the MAC key is successfully retrieved; E_NOT_OK otherwise. |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8* |keyPtr |Buffer filled with the secret MAC key. |
 * |uint32* |length |Updated with the actual length of the retrieved MAC key. |
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
 * |uint8 |i |Loop counter for key population. |
 * @brief Callout function to retrieve the secret MAC key for firmware updates.
 * @note This function is a placeholder that should be replaced with code to
 * securely retrieve the secret MAC key shared with the vHsm Bootloader.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(Std_ReturnType, VHSM_CODE) vHsm_FirmwareUpdate_GetMacKey_Callout(
  P2VAR(uint8, AUTOMATIC, VHSM_APPL_VAR) keyPtr,
  P2VAR(uint32, AUTOMATIC, VHSM_APPL_VAR) length)
{
  /* Get the secret mac key shared with vHsm Bootloader. */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK FirmwareUpdate_GetMacKey>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_FirmwareUpdate_GetMacKey_Callout() */
  /* The following lines needs to be replaced with code getting a secret key shared with the vHsm Bootloader. */
  uint8 i;
  for(i=0u; i < *length; i++)
  {
    keyPtr[i] = i;
  }
 
  return E_OK;
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}
/** @cond INTERNAL */
# define VHSM_STOP_SEC_CODE_MAC_CALLOUT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
 
# if (VHSM_FIRMWARE_UPDATE_RECRYPTION == STD_ON)
 
#  define VHSM_START_SEC_CODE_CIPHER_CALLOUT
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/** @endcond */
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8* |keyPtr |Pointer to a buffer where the secret cipher key will be stored. |
 * |uint32* |length |Pointer to a variable holding the expected key length, and will store the actual length. |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |Std_ReturnType |retVal |E_OK if the cipher key is successfully retrieved; E_NOT_OK otherwise. |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8* |keyPtr |Buffer filled with the secret cipher key. |
 * |uint32* |length |Updated with the actual length of the retrieved cipher key. |
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
 * |uint8 |i |Loop counter for key population. |
 * @brief Callout function to retrieve the secret cipher key for firmware update decryption.
 * @note This function is a placeholder that should be replaced with code to securely
 * retrieve the secret cipher key used for re-encryption or decryption during firmware updates.
 */
/* author Vector Informatik GmbH */
/* date 2024-07-24 */
/************************************************************************************************/
FUNC(Std_ReturnType, VHSM_CODE) vHsm_FirmwareUpdate_GetCipherKey_Callout(
  P2VAR(uint8, AUTOMATIC, VHSM_APPL_VAR) keyPtr,
  P2VAR(uint32, AUTOMATIC, VHSM_APPL_VAR) length)
{
  /* Get the secret key cipher shared with vHsm Bootloader. */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK FirmwareUpdate_GetCipherKey>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
  /* Add implementation of vHsm_FirmwareUpdate_GetCipherKey_Callout() */
  /* The following lines needs to be replaced with code getting a secret key shared with the vHsm Bootloader. */
  uint8 i;
  for(i=0u; i < *length; i++)
  {
    keyPtr[i] = i;
  }
 
  return E_OK;
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>                                       DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}
/** @cond INTERNAL */
#  define VHSM_STOP_SEC_CODE_CIPHER_CALLOUT
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/** @endcond */
# endif /* (VHSM_FIRMWARE_UPDATE_RECRYPTION == STD_ON) */
 
#endif /* (VHSM_FIRMWARE_UPDATE == STD_ON) */
 
#if 0
#endif
 
void CM0_Debug_Init(void)
{
  SRAM_CM0_CM7_SHARED_STACK_PTR_PEAK = 0xFFFFFFFF;
  SRAM_CM0_CM7_CUSTOM_JOB_PROCESS = 0xFF;
  SRAM_CM0_CM7_MAIN_FUNCTION_FREEZE = 0x0000;
  SRAM_CM0_CM7_WORKFLASH_ERASE_PROCESS = 0x00;
  SRAM_CM0_CM7_KEYSETVALID_REPRO      = 0u;
  SRAM_CM0_CM7_KEYSETVALID_MASTERECU  = 0u;
  SRAM_CM0_CM7_KEYSETVALID_TYPEX      = 0u;
}
 
void CM0_Debug_Get_SP(void)
{
  uint32 local_variable;
  uint32 sp = (uint32)&local_variable;
 
  if (sp < SRAM_CM0_CM7_SHARED_STACK_PTR_PEAK)
  {
    SRAM_CM0_CM7_SHARED_STACK_PTR_PEAK = sp;
  }
}
 
/**********************************************************************************************************************
 *  END OF FILE: VHSM_CALLOUT_STUBS.C
 *********************************************************************************************************************/
 
 