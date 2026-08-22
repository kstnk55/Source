/**
 * @file CoreIso.c
 * @brief Public header: CoreIso.h
 * @details Overview: Implementation of Core Isolation functionality for memory protection on multi-core systems
 */
 
/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  CoreIso.c
 *        \brief
 *      \details
 *********************************************************************************************************************/
 
 
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Std_Types.h"
# include "CoreIso.h"
# include "CoreIso_ConfigData.h"
 
 
 
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
 
/**
 * @def CORE_ISOLATION_MPU_NO
 * @value 7u
 * @resolution -
 * @brief Defines the number of Memory Protection Units available in the system
 */
# define CORE_ISOLATION_MPU_NO   (7u)
 
/**
 * @def CORE_ISOLATION_SMPU_NO
 * @value 16u
 * @resolution -
 * @brief Defines the number of Shared Memory Protection Units available in the system
 */
# define CORE_ISOLATION_SMPU_NO  (16u)
 
/**
 * @def NR_OF_PPU_IGNORED
 * @value 9u
 * @resolution -
 * @brief Defines the number of Peripheral Protection Units to be ignored during configuration
 */
# define NR_OF_PPU_IGNORED       (9u)
 
/**
 * @def COREISO_SMPU_NON_SECURE
 * @value 0u
 * @resolution -
 * @brief Defines the non-secure attribute value for SMPU configuration
 */
# define COREISO_SMPU_NON_SECURE (0u)
 
/**
 * @def COREISO_SMPU_SECURE
 * @value 1u
 * @resolution -
 * @brief Defines the secure attribute value for SMPU configuration
 */
# define COREISO_SMPU_SECURE     (1u)
 
/**
 * @def COREISO_PROT_SMPU_STRUCT_BASE
 * @value PROT_SMPU_SMPU_STRUCT0
 * @resolution -
 * @brief Base address of the SMPU structure registers in memory
 */
# define COREISO_PROT_SMPU_STRUCT_BASE        PROT_SMPU_SMPU_STRUCT0
 
/**
 * @def SRAM_SECURE_DTC
 * @value 0x2801BFF0U
 * @resolution -
 * @brief Memory address for the secure DTC(Diagnostic Trouble Code) region in SRAM
 */
#define SRAM_SECURE_DTC                       (0x2801BFF0U)
 
/**
 * @def BACK_GROUND_REGION
 * @value 0x00000000u
 * @resolution -
 * @brief Start Address of the background memory region
 */
# define BACK_GROUND_REGION                   (0x00000000u)
 
/**
 * @def CODE_FLASH_BANK_A_CM0P
 * @value 0x10000000u
 * @resolution -
 * @brief Start Address of CM0+ code in Flash Bank A
 */
# define CODE_FLASH_BANK_A_CM0P               (0x10000000u)
 
/**
 * @def CODE_FLASH_BANK_A_BOOT_MANAGER
 * @value 0x10090400u
 * @resolution -
 * @brief Start Address of Boot Manager code in Flash Bank A
 */
# define CODE_FLASH_BANK_A_BOOT_MANAGER       (0x10090400u)
 
/**
 * @def CODE_FLASH_BANK_A_FBL
 * @value 0x103F8000u
 * @resolution -
 * @brief Start Address of FBL (Flash Boot Loader) in Flash Bank A
 */
# define CODE_FLASH_BANK_A_FBL                (0x103F8000u)
/**
 * @def WORK_FLASH_CM7_NVM_AREA
 * @value 0x14000000u
 * @resolution -
 * @brief Start Address of CM7 NVM area (Meter, Graphic) in Work Flash (96KB + 32KB)
 */
# define WORK_FLASH_CM7_NVM_AREA             (0x14000000u)
 
/**
 * @def WORK_FLASH_CM0_NVM_AREA
 * @value 0x14018000u
 * @resolution -
 * @brief Start Address of CM0 NVM area (Security) in Work Flash - Part 1 (first 16KB)
 */
# define WORK_FLASH_CM0_NVM_AREA             (0x14018000u)
 
/**
 * @def WORK_FLASH_CM0_NVM_AREA_P2
 * @value 0x1401C000u
 * @resolution -
 * @brief Start Address of CM0 NVM area Part 2 in Work Flash (last 16KB; sub7 excluded to allow CM7 access to Bank Info at 0x1401FF00)
 */
# define WORK_FLASH_CM0_NVM_AREA_P2          (0x1401C000u)
 
/**
 * @def FLASH_SUPER_BOOT_DUALBANK
 * @value 0x17000000u
 * @resolution -
 * @brief Start Address of Flash Supervisory area for Boot and Dual Bank Manager
 */
# define FLASH_SUPER_BOOT_DUALBANK           (0x17000000u)
 
/**
 * @def SRAM_SYSTEM_RESERVE
 * @value 0x28000000u
 * @resolution -
 * @brief Start Address of System Reserve area in SRAM
 */
# define SRAM_SYSTEM_RESERVE                 (0x28000000u)
 
/**
 * @def SRAM_CMOP_RETENTION
 * @value 0x28000800u
 * @resolution -
 * @brief Start Address of CM0+ Retention area in SRAM (62KB, ends at 0x2800FFFF)
 */
# define SRAM_CMOP_RETENTION                 (0x28000800u)
 
/**
 * @def SRAM_RTE_SHARED
 * @value 0x28068000u
 * @resolution -
 * @brief Start Address of RTE, Shared code, MCAL, SDL memory (94KB, accessible by M0+/CM7-0/CM7-1)
 */
# define SRAM_RTE_SHARED                     (0x28068000u)
 
/**
 * @def SRAM_ANALYSIS_LOG
 * @value 0x2807F800u
 * @resolution -
 * @brief Start Address of Analysis Log area in SRAM
 */
# define SRAM_ANALYSIS_LOG                   (0x2807F800u)
 
/**
 * @def SRAM_METER_CACHED
 * @value 0x28040000u
 * @resolution -
 * @brief Start Address of Meter Cached data in SRAM
 */
# define SRAM_METER_CACHED                   (0x28040000u)
 
/**
 * @def SRAM_GRAPHIC_CACHED
 * @value 0x28080000u
 * @resolution -
 * @brief Start Address of Graphic Cached data in SRAM
 */
# define SRAM_GRAPHIC_CACHED                 (0x28080000u)
 
/**
 * @def PERIPHERAL_REGISTER
 * @value 0x40000000u
 * @resolution -
 * @brief Start Address of Peripheral Register space
 */
# define PERIPHERAL_REGISTER                 (0x40000000u)
 
/**
 * @def ARM_SYSTEM_SPACE
 * @value 0xE0000000u
 * @resolution -
 * @brief Start Address of ARM System space registers
 */
# define ARM_SYSTEM_SPACE                    (0xE0000000u)
 
/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
 
/**
 * @def CoreIso_GetSmpuStructCfgBase
 * @value  ((volatile CoreIso_SMPUStruct*) (COREISO_PROT_SMPU_STRUCT_BASE + (index)))
 * @resolution -
 * @brief Macro function to get the base address of specified SMPU structure
 */
# define CoreIso_GetSmpuStructCfgBase(index)            ((volatile CoreIso_SMPUStruct*) (COREISO_PROT_SMPU_STRUCT_BASE + (index)))
 
/**
 * @def CoreIso_ConfigSmpuSlaveStruct
 * @value Cy_Prot_ConfigSmpuSlaveStruct((base), (config))
 * @resolution -
 * @brief Macro function to configure an SMPU slave structure
 */
# define CoreIso_ConfigSmpuSlaveStruct(base, config)    Cy_Prot_ConfigSmpuSlaveStruct((base), (config))
 
/**
 * @def CoreIso_ConfigSmpuMasterStruct
 * @value Cy_Prot_ConfigSmpuMasterStruct((base), (config))
 * @resolution -
 * @brief Macro function to configure an SMPU master structure
 */
# define CoreIso_ConfigSmpuMasterStruct(base, config)   Cy_Prot_ConfigSmpuMasterStruct((base), (config))
 
/**
 * @def CoreIso_EnableSmpuSlaveStruct
 * @value Cy_Prot_EnableSmpuSlaveStruct((base))
 * @resolution -
 * @brief Macro function to enable an SMPU slave structure
 */
# define CoreIso_EnableSmpuSlaveStruct(base)            Cy_Prot_EnableSmpuSlaveStruct((base))
 
/**
 * @def CoreIso_DisableSmpuSlaveStruct
 * @value Cy_Prot_DisableSmpuSlaveStruct((base))
 * @resolution -
 * @brief Macro function to disable an SMPU slave structure
 */
# define CoreIso_DisableSmpuSlaveStruct(base)           Cy_Prot_DisableSmpuSlaveStruct((base))
 
/**
 * @def CoreIso_EnableSmpuMasterStruct
 * @value Cy_Prot_EnableSmpuMasterStruct((base))
 * @resolution -
 * @brief Macro function to enable an SMPU master structure
 */
# define CoreIso_EnableSmpuMasterStruct(base)           Cy_Prot_EnableSmpuMasterStruct((base))
 
/**
 * @def CoreIso_DisableSmpuMasterStruct
 * @value Cy_Prot_DisableSmpuMasterStruct((base))
 * @resolution -
 * @brief Macro function to disable an SMPU master structure
 */
# define CoreIso_DisableSmpuMasterStruct(base)          Cy_Prot_DisableSmpuMasterStruct((base))
 
/**
 * @def CoreIso_GetPcMask
 * @value (uint16_t)(1u << (PcId-1u))
 * @resolution -
 * @brief Macro function to convert a Protection Context ID to its corresponding bitmask
 */
# define CoreIso_GetPcMask(PcId)                        ((uint32_t)(1u << ((uint32_t)(PcId)-1u)))
 
/**
 * @def COREISO_LOCAL
 * @value static
 * @resolution -
 * @brief Defines function scope for local functions (static by default)
 */
#if !defined (COREISO_LOCAL) /* COV_CRYIF_ALWAYS_ON */
# define COREISO_LOCAL                                                static
#endif
 
/**
 * @def COREISO_LOCAL_INLINE
 * @value LOCAL_INLINE
 * @resolution -
 * @brief Defines function scope for local inline functions
 */
#if !defined (COREISO_LOCAL_INLINE) /* COV_CRYIF_ALWAYS_ON */
# define COREISO_LOCAL_INLINE                                         LOCAL_INLINE
#endif
 
/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
 
 
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_StatusCfgCheck(cy_en_prot_status_t status);
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_InitErrorHook(void);
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_PpuClrSlavePermissionAll(void);
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_PpuSetSlavePermission(void);
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_PpuClrMasterPermissionAll(void);
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_PpuSetMasterPermission(void);
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_PPUSlaveInit(void);
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_PPUMasterInit(void);
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_SmpuBusMasterInit(const CoreIso_SMPUProtConfigType *busMasterCfgPtr);
COREISO_LOCAL FUNC(cy_en_prot_status_t, AUTOMATIC) CoreIso_Wrapper_ConfigSmpuMasterStruct(volatile stc_PROT_SMPU_SMPU_STRUCT_t* base, const cy_stc_smpu_cfg_t* config);
COREISO_LOCAL FUNC(Std_ReturnType, AUTOMATIC) CoreIso_IsPPUFxAvailable(CONST(uint16, AUTOMATIC) ppuTarget);
 
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_SetDtcError(uint8 DtcErrCode, uint32* DtcAddressPtr);
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_DisableAllPpus(void);
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_SmpuBusMasterDisableAll(void);
COREISO_LOCAL FUNC(uint16, AUTOMATIC) CoreIso_GetInitErrorHook(void);
 
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_SMPUInit(void);
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_MPUInit(void);
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_ConfigBusMasters(void);
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_ActivePCs(void);
 
COREISO_LOCAL FUNC(cy_en_prot_status_t, AUTOMATIC)  CoreIso_Wrapper_SetActivePC(en_prot_master_t busMaster, uint32_t pc);
 
/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
/**
 * @type uint16
 * @var g_CoreIsoInitSts
 * @brief Status flag to track whether the Core Isolation module has been initialized
 * @unit -
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |- |- |- |- |- |
 */
static volatile uint16 g_CoreIsoInitSts = FALSE;
/** @cond INTERNAL */
# define COREISO_START_SEC_CONST
# include "CoreIso_MemMap.h"
/** @endcond */
/**
 * @type cy_stc_mpu_region_cfg_t[]
 * @var CoreIso_MPUConfig
 * @brief Configuration array for Memory Protection Unit regions
 * @unit -
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |-|- |- |- |- |
 */
COREISO_LOCAL CONST(cy_stc_mpu_region_cfg_t, AUTOMATIC) CoreIso_MPUConfig[CORE_ISOLATION_MPU_NO] =
{
  /* 1. BACKGROUND */
  {
    BACK_GROUND_REGION,
    CY_MPU_SIZE_64KB,
    CY_MPU_ACCESS_P_PRIV_RO,
    CY_MPU_ATTR_NORM_MEM_WT,
    CY_MPU_INST_ACCESS_EN,
    0x00u,
    CY_MPU_ENABLE
  },
  /* 2. Code Flash Region */
  {
    CODE_FLASH_BANK_A_CM0P,
    CY_MPU_SIZE_8MB,
    CY_MPU_ACCESS_P_PRIV_RO,
    CY_MPU_ATTR_NORM_MEM_WT,
    CY_MPU_INST_ACCESS_EN,
    0x00u,
    CY_MPU_ENABLE
  },
  /* 3. Work Flash Region */
  {
    WORK_FLASH_CM7_NVM_AREA,
    CY_MPU_SIZE_128KB,
    CY_MPU_ACCESS_P_PRIV_RO,
    CY_MPU_ATTR_NORM_MEM_WT,
    CY_MPU_INST_ACCESS_EN,
    0x3Fu, /* 0011 1111 - disable sub0-sub5 (M7 NvM 96KB), expose sub6-sub7 (M0 NvM at 0x14018000) */
    CY_MPU_ENABLE
  },
  /* 4. Flash Supervisory */
  {
    FLASH_SUPER_BOOT_DUALBANK,
    CY_MPU_SIZE_32KB,
    CY_MPU_ACCESS_P_PRIV_RO,
    CY_MPU_ATTR_NORM_MEM_WT,
    CY_MPU_INST_ACCESS_EN,
    0x00u,
    CY_MPU_ENABLE
  },
  /* 5. System RAM */
  {
    SRAM_SYSTEM_RESERVE,
    CY_MPU_SIZE_1MB,
    CY_MPU_ACCESS_P_PRIV_RW,
    CY_MPU_ATTR_NORM_SHR_MEM_NC,
    CY_MPU_INST_ACCESS_DIS,
    0xF6u, /* 1111 0110 - disable sub1(MICROSAR BSW),sub2(Meter Cached),sub4(Graphic),sub5-7 */
    CY_MPU_ENABLE
  },
  /* 6. Peripheral Register */
  {
    PERIPHERAL_REGISTER,
    CY_MPU_SIZE_64MB,
    CY_MPU_ACCESS_P_PRIV_RW,
    CY_MPU_ATTR_SHR_DEV,
    CY_MPU_INST_ACCESS_DIS,
    0x00u,
    CY_MPU_ENABLE
  },
  /* 7. ARM System Registers */
  {
    ARM_SYSTEM_SPACE,
    CY_MPU_SIZE_512MB,
    CY_MPU_ACCESS_P_PRIV_RW,
    CY_MPU_ATTR_STR_ORD_DEV,
    CY_MPU_INST_ACCESS_DIS,
    0x00u,
    CY_MPU_ENABLE
  },
};
/** @cond INTERNAL */
# define COREISO_STOP_SEC_CONST
# include "CoreIso_MemMap.h"
 
# define COREISO_START_SEC_CONST
# include "CoreIso_MemMap.h"
/** @endcond */
/**
 * @type CoreIso_SMPUAttribute[]
 * @var CoreIso_SmpuCm0MasterStructCfg
 * @brief Configuration array for CM0+ core master access to shared memory regions
 * @unit -
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |- |- |- |- |- |
 */
COREISO_LOCAL CONST(CoreIso_SMPUAttribute, AUTOMATIC) CoreIso_SmpuCm0MasterStructCfg[] = {
  /* Index */
  /* 0. System RAM : SRAM_METER_CACHED + SRAM_METER_NO_CACHED + Graphic */
  {
    (uint32_t *) SRAM_SYSTEM_RESERVE,
    CY_PROT_SIZE_1MB,
    0x09u, /* disable sub0(CM0+ areas) and sub3(RTE Shared 0x28060000) from blocking rule */
    CY_PROT_PERM_DISABLED,
    CY_PROT_PERM_RW,
    (bool)COREISO_SMPU_SECURE,
    (bool)0u,
    0x0017u /*Alow [bit0~2] PC1~3: HW control, [bit4] PC5: CM0*/
  },
  /* 1. System RAM : SRAM_SYSTEM_RESERVE + SRAM_CMOP_RETENTION (System Reserve 2KB + M0+ Retention 62KB, 0x28000000-0x2800FFFF) */
  {
    (uint32_t *) (SRAM_SYSTEM_RESERVE),
    CY_PROT_SIZE_64KB,
    0x00u, /* all 8 sub-regions are System Reserve + M0+ Retention ? no exclusion needed */
    CY_PROT_PERM_DISABLED,
    CY_PROT_PERM_RW,
    (bool)COREISO_SMPU_SECURE,
    (bool)0u,
    0x0017u /*Alow [bit0~2] PC1~3: HW control, [bit4] PC5: CM0*/
  },
  /* 2. Work Flash Region : M0 NvM Area(Security) - Part 1 (first 16KB, 0x14018000-0x1401BFFF) */
  {
    (uint32_t *) WORK_FLASH_CM0_NVM_AREA,
    CY_PROT_SIZE_16KB,
    0x00u,
    CY_PROT_PERM_DISABLED,
    CY_PROT_PERM_RW,
    (bool)COREISO_SMPU_SECURE,
    (bool)0u,
    0x0017u /*Alow [bit0~2] PC1~3: HW control, [bit4] PC5: CM0*/
  },
  /* 3. Work Flash Region : M0 NvM Area(Security) - Part 2 (0x1401C000; sub7=0x1401F800 excluded for Bank Info CM7 access) */
  {
    (uint32_t *) WORK_FLASH_CM0_NVM_AREA_P2,
    CY_PROT_SIZE_16KB,
    0x80u, /* disable sub7: Not used + Direct Nv Area(Bank Info. 0x1401FF00) accessible by CM7 */
    CY_PROT_PERM_DISABLED,
    CY_PROT_PERM_RW,
    (bool)COREISO_SMPU_SECURE,
    (bool)0u,
    0x0017u /*Alow [bit0~2] PC1~3: HW control, [bit4] PC5: CM0*/
  },
  /* 4. Flash Supervisory : Flash Boot, Dual Bank Manager*/
  {
    (uint32_t *) FLASH_SUPER_BOOT_DUALBANK,
    CY_PROT_SIZE_32KB,
    0u,
    CY_PROT_PERM_DISABLED,
    CY_PROT_PERM_RW,
    (bool)COREISO_SMPU_SECURE,
    (bool)0u,
    0x0017u /*Alow [bit0~2] PC1~3: HW control, [bit4] PC5: CM0*/
  },
  /* 5. Boot Manager: Vector table CM7 */
  {
    (uint32_t *) CODE_FLASH_BANK_A_BOOT_MANAGER,
    CY_PROT_SIZE_256B,
    0u,
    CY_PROT_PERM_DISABLED,
    CY_PROT_PERM_RW,
    (bool)COREISO_SMPU_SECURE,
    (bool)0u,
    0x0017u /*Alow [bit0~2] PC1~3: HW control, [bit4] PC5: CM0*/
  },
  /* 6.Peripheral: prevent Excute from CM0,CM7_0, CM7_1 */
  {
    (uint32_t *) PERIPHERAL_REGISTER,
    CY_PROT_SIZE_64MB,
    0u,
    CY_PROT_PERM_DISABLED,
    CY_PROT_PERM_RW,
    (bool)COREISO_SMPU_NON_SECURE,
    (bool)0u,
    0x007Fu /*Alow [bit0~2] PC1~3: HW control, [bit4~7]PC5:CM0 PC6,7: CM7_0,CM7_1*/
  }  
};
 
/**
 * @type CoreIso_SMPUAttribute[]
 * @var CoreIso_SmpuCm0SlaveStructCfg
 * @brief Configuration array for slave access to CM0+ protected memory regions
 * @unit -
 * @scope Local Variable
 * @section RAM
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |- |- |- |- |- |
 */
COREISO_LOCAL CONST(CoreIso_SMPUAttribute, AUTOMATIC) CoreIso_SmpuCm0SlaveStructCfg[] = {
  /* Index */
  /* 0. System RAM : SRAM_METER_CACHED + SRAM_METER_NO_CACHED + Graphic */
  {
    (uint32_t *) SRAM_SYSTEM_RESERVE,
    CY_PROT_SIZE_1MB,
    0x09u, /* disable sub0(CM0+ areas 0x28000000) and sub3(RTE Shared 0x28060000) from blocking rule */
    CY_PROT_PERM_DISABLED,
    CY_PROT_PERM_DISABLED,
    (bool)COREISO_SMPU_SECURE,
    (bool)1u,
    0x0010u /*Alow [bit4] PC5: CM0*/
  },
  /* 1. System RAM : SRAM_SYSTEM_RESERVE + SRAM_CMOP_RETENTION (System Reserve 2KB + M0+ Retention 62KB, 0x28000000-0x2800FFFF) */
  {
    (uint32_t *) (SRAM_SYSTEM_RESERVE),
    CY_PROT_SIZE_64KB,
    0x00u, /* all 8 sub-regions are System Reserve + M0+ Retention ? no exclusion needed */
    CY_PROT_PERM_DISABLED,
    CY_PROT_PERM_RW,
    (bool)COREISO_SMPU_SECURE,
    (bool)0u,
    0x0017u /*Alow [bit0~2] PC1~3: HW control, [bit4] PC5: CM0*/
  },
  /* 2. Work Flash Region : M0 NvM Area(Security) - Part 1 (first 16KB, 0x14018000-0x1401BFFF) */
  {
    (uint32_t *) WORK_FLASH_CM0_NVM_AREA,
    CY_PROT_SIZE_16KB,
    0x00u,
    CY_PROT_PERM_DISABLED,
    CY_PROT_PERM_RW,
    (bool)COREISO_SMPU_SECURE,
    (bool)0u,
    0x0017u /*Alow [bit0~2] PC1~3: HW control, [bit4] PC5: CM0*/
  },
  /* 3. Work Flash Region : M0 NvM Area(Security) - Part 2 (0x1401C000; sub7=0x1401F800 excluded for Bank Info CM7 access) */
  {
    (uint32_t *) WORK_FLASH_CM0_NVM_AREA_P2,
    CY_PROT_SIZE_16KB,
    0x80u, /* disable sub7: Not used + Direct Nv Area(Bank Info. 0x1401FF00) accessible by CM7 */
    CY_PROT_PERM_DISABLED,
    CY_PROT_PERM_RW,
    (bool)COREISO_SMPU_SECURE,
    (bool)0u,
    0x0017u /*Alow [bit0~2] PC1~3: HW control, [bit4] PC5: CM0*/
  },
  /* 4. Flash Supervisory : Flash Boot, Dual Bank Manager*/
  {
    (uint32_t *) FLASH_SUPER_BOOT_DUALBANK,
    CY_PROT_SIZE_32KB,
    0u,
    CY_PROT_PERM_DISABLED,
    CY_PROT_PERM_RX,
    (bool)COREISO_SMPU_SECURE,
    (bool)1u,
    0x0010u /*apply for [bit4] PC5: CM0 - Read Only*/
  },
  /* 5. Boot Manager: Vector table CM7 */
  {
    (uint32_t *) CODE_FLASH_BANK_A_BOOT_MANAGER,
    CY_PROT_SIZE_256B,
    0u,
    CY_PROT_PERM_DISABLED,
    CY_PROT_PERM_DISABLED,
    (bool)COREISO_SMPU_NON_SECURE,
    (bool)1u,
    0x0010u /*only [bit4] PC5: CM0 - don't have permission to access*/
  },
  /* 6.Peripheral: prevent Excute from CM0,CM7_0, CM7_1 */
  {
    (uint32_t *) PERIPHERAL_REGISTER,
    CY_PROT_SIZE_64MB,
    0u,
    CY_PROT_PERM_DISABLED,
    CY_PROT_PERM_RW,
    (bool)COREISO_SMPU_NON_SECURE,
    (bool)0u,
    0x007Fu /*Alow [bit0~2] PC1~3: HW control, [bit4~7]PC5:CM0 PC6,7: CM7_0,CM7_1*/
  }
};
  
/**
 * @type CoreIso_SMPUProtConfigType[]
 * @var CoreIso_SmpuCm0Cfg
 * @brief Protection configuration for CM0+ core in the SMPU
 * @unit -
 * @scope Local Variable
 * @section
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |-|- |- |- |- |
 */
COREISO_LOCAL CONST(CoreIso_SMPUProtConfigType, AUTOMATIC) CoreIso_SmpuCm0Cfg[] = {
  /* Index */
  /* SMPU CM0 PROTECT CONTEXT 2*/
  {
    COREISO_PC_CM0P,
    0u,
    6u,
    CoreIso_SmpuCm0SlaveStructCfg,
    CoreIso_SmpuCm0MasterStructCfg
  }
};
 
/**
 * @type CoreIso_SMPUConfigType[]
 * @var CoreIso_SmpuCfg
 * @brief Top-level SMPU configuration mapping bus masters to their protection settings
 * @unit -
 * @scope Local Variable
 * @section RAM
 * @par Initial setting
 * |RAM0 |RAM1 |RAM2 |RAM3 |RAM4 |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |-|- |- |- |- |
 */
COREISO_LOCAL CONST(CoreIso_SMPUConfigType, AUTOMATIC) CoreIso_SmpuCfg[] = {
  /*CPUSS_MS_ID_CM0,*/
  {
    CPUSS_MS_ID_CM0,
    CoreIso_SmpuCm0Cfg
  },
  /*CPUSS_MS_ID_CM7_1,*/
  {
    CPUSS_MS_ID_CM7_1,
    NULL_PTR
  },
  /*CPUSS_MS_ID_CM7_0,*/
  {
    CPUSS_MS_ID_CM7_0,
    NULL_PTR
  },    
  /*CPUSS_MS_ID_TC*/
  {
    CPUSS_MS_ID_TC,
    NULL_PTR
  }
};
/** @cond INTERNAL */
# define COREISO_STOP_SEC_CONST
# include "CoreIso_MemMap.h"
 
 
# define COREISO_START_SEC_CONST
# include "CoreIso_MemMap.h"
/** @endcond */
/**
 * @type uint16[]
 * @var CoreIso_PPUFxROMConfig
 * @brief Array of PPU fixed-group IDs that are configured by boot ROM
 * @unit -
 * @scope Local Variable
 * @section -
 * @par Initial setting
 * |ROM0 |ROM1 |ROM2 |ROM3 |ROM4 |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |-|- |- |- |- |
 */
COREISO_LOCAL CONST(uint16, AUTOMATIC) CoreIso_PPUFxROMConfig[NR_OF_PPU_IGNORED] =
{
  27u,  /* PERI_MS_PPU_FX_CRYPTO_BOOT */
  34u,  /* PERI_MS_PPU_FX_CPUSS_BOOT */
  77u,  /* PERI_MS_PPU_FX_FLASHC_FlashMgmt */
  272u, /* PERI_MS_PPU_FX_EFUSE_CTL */
  273u, /* PERI_MS_PPU_FX_EFUSE_DATA */
  82u,  /* PERI_MS_PPU_FX_SRSS_SECURE */
  69u,  /* PERI_MS_PPU_FX_FLASHC_DFT */
  274u, /* PERI_MS_PPU_FX_DFT */
  14u,  /* PERI_MS_PPU_FX_PERI_GR2_BOOT */
};
/** @cond INTERNAL */
# define COREISO_STOP_SEC_CONST
# include "CoreIso_MemMap.h"
 
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
 
# define COREISO_START_SEC_CODE
# include "CoreIso_MemMap.h"
/** @endcond */
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8 |DtcErrCode |Error code to be stored in DTC memory |
 * |uint32* |DtcAddressPtr |Pointer to the memory location where DTC value will be stored |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |void |- |No return value |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint32* |DtcAddressPtr |Memory location where DTC error code is written |
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
 * |CoreIso_DtcFlagType* |SecureBootDtc_Ptr |Pointer to DTC structure for writing the error code |
 * @brief Stores a Diagnostic Trouble Code (DTC) error to a specified memory location
 * @note This function writes a specified error code to the DTC memory region for the CM0+ core.
 * It first validates that the provided address pointer is not NULL, then casts it to
 * the appropriate structure type and writes the error code to the CoreIso-specific field.
 * After writing, the pointer is set to NULL to prevent accidental misuse.
 */
/* FPT*/
/* date 2022 */
/************************************************************************************************/
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_SetDtcError(uint8 DtcErrCode, uint32* DtcAddressPtr)
{
  CoreIso_DtcFlagType * SecureBootDtc_Ptr;
  if(DtcAddressPtr != NULL_PTR)
  {
    SecureBootDtc_Ptr = (CoreIso_DtcFlagType *) DtcAddressPtr;
    SecureBootDtc_Ptr->DTC_Block.DTC_COREISO_CM0 = DtcErrCode;
  }
 
 SecureBootDtc_Ptr = NULL_PTR;
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
 * |uint16 |status |Current initialization status of the CoreIso module (TRUE if error occurred, FALSE otherwise) |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint16 |g_CoreIsoInitSts |Global variable containing the initialization status |
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
 * @brief Retrieves the initialization error status of the CoreIso module
 * @note This function returns the current value of the global initialization status flag.
 * The flag is TRUE if an error occurred during CoreIso initialization, FALSE otherwise.
 * It is typically used to check if the memory protection initialization succeeded.
 */
/* FPT*/
/* date 2022 */
/************************************************************************************************/
COREISO_LOCAL FUNC(uint16, AUTOMATIC) CoreIso_GetInitErrorHook(void)
{
  return g_CoreIsoInitSts;
}
 
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |cy_en_prot_status_t |status |Status code returned from a protection configuration operation |
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
 * @brief Checks the status of a protection configuration operation and calls the error hook if unsuccessful
 * @note This function verifies if a protection register configuration operation was successful by
 * checking if the status equals CY_PROT_SUCCESS. If the operation failed, it calls
 * CoreIso_InitErrorHook() to indicate an initialization error. This function is used
 * throughout the CoreIso module to validate the success of memory protection operations.
 */
/* FPT*/
/* date 2022 */
/************************************************************************************************/
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_StatusCfgCheck(cy_en_prot_status_t status)
{
  if(status != CY_PROT_SUCCESS)
  {
    CoreIso_InitErrorHook();
  }
  else
  {
    /* Do nothing*/
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
 * |uint16 |g_CoreIsoInitSts |Set to TRUE to indicate initialization failure |
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
 * @brief Error handler that is called when CoreIso initialization fails
 * @note This function is called when any part of the CoreIso initialization process fails.
 */
/* FPT*/
/* date 2022 */
/************************************************************************************************/
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_InitErrorHook(void)
{
  g_CoreIsoInitSts = TRUE;
}
 
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint16 |ppuTarget |Target PPU ID to check against the ROM-configured PPU list |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |Std_ReturnType |retVal |E_OK if the PPU is available for configuration, E_NOT_OK if it should be ignored |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint16[] |CoreIso_PPUFxROMConfig |Array of PPU IDs that are configured by boot ROM and should be ignored |
 * |uint8 |NR_OF_PPU_IGNORED |Number of PPUs in the ignore list |
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
 * |Std_ReturnType |retVal |Return value indicating if PPU is available (E_OK) or should be ignored (E_NOT_OK) |
 * |uint8 |i |Loop counter for scanning through the ROM-configured PPU list |
 * @brief Checks if a PPU is available for user configuration or is already configured by boot ROM
 * @note This function verifies whether a specified PPU is already configured by the boot ROM by
 * comparing its ID against the list of ROM-configured PPUs (CoreIso_PPUFxROMConfig).
 */
/* FPT*/
/* date 2022 */
/************************************************************************************************/
COREISO_LOCAL FUNC(Std_ReturnType, AUTOMATIC) CoreIso_IsPPUFxAvailable(CONST(uint16, AUTOMATIC) ppuTarget)
{
  Std_ReturnType retVal = E_OK;
  uint8 i;
 
  /* Scan the CoreIso_PPUFxROMConfig list, return E_OK when match */
  i = 0u;
  while ((i < NR_OF_PPU_IGNORED) && (E_OK == retVal))
  {
    /* QAC Deviations: (No 1279) This macro is provided by Cypress Semiconductor, So, this warning can ignore and doesn't affect to the current behavior. */
    if (CoreIso_PeriPPUFxGrx(ppuTarget) == CoreIso_PeriPPUFxGrx(CoreIso_PPUFxROMConfig[i]))
    {
      retVal = E_NOT_OK;
    }
    i++;
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
 * |void |- |No return value |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint16 |COREISO_MAX_FX_PPU_GR |Maximum number of PPU groups to configure |
 * |uint8 |COREISO_PROT_PC_NR |Number of protection contexts in the system |
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
 * |uint8 |pcIndex |Loop counter for protection contexts |
 * |uint16 |ppuStructIndex |Loop counter for PPU structures |
 * |cy_stc_ppu_gr_cfg_t |ppuGrCfg |Configuration structure for PPU slave configuration |
 * |cy_en_prot_pc_t |pcValue |Protection context value derived from the default configuration |
 * |const CoreIso_PPUGrCfgType* |ppuGrSlaveCfg |Pointer to slave configuration for the current protection context |
 * @brief Sets default permission configurations for all PPU slave structures except those configured by boot ROM
 * @note This function initializes all Peripheral Protection Unit (PPU) slave structures with their
 * default permission settings as defined in CoreIso_PPUSlaveProtAttrDefault.
 */
/* FPT*/
/* date 2022 */
 
 /************************************************************************************************/
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_PpuClrSlavePermissionAll(void)
{
  uint8                       pcIndex;
  uint16                      ppuStructIndex;
  cy_stc_ppu_gr_cfg_t         ppuGrCfg;
  cy_en_prot_pc_t             pcValue;
  const CoreIso_PPUGrCfgType* ppuGrSlaveCfg;
 
  /* Disable permission for all PC of all PPUs (except PPU configured by Boot Rom) */
  for (ppuStructIndex = 0u; ppuStructIndex < COREISO_MAX_FX_PPU_GR; ppuStructIndex++)
  {
    if (E_OK == CoreIso_IsPPUFxAvailable(ppuStructIndex))
    {
      for (pcIndex = 0u; pcIndex < COREISO_PROT_PC_NR; pcIndex++)
      {
        pcValue = (cy_en_prot_pc_t)((uint32_t)CoreIso_GetPCSlaveDefaultAtIndex(pcIndex));
        ppuGrSlaveCfg = CoreIso_GetAttrSlaveDefaultAtIndex(pcIndex);
        ppuGrCfg.userPermission = (cy_en_prot_perm_t)((uint32_t)ppuGrSlaveCfg->userPermission);
        ppuGrCfg.privPermission = (cy_en_prot_perm_t)((uint32_t)ppuGrSlaveCfg->privPermission);
        ppuGrCfg.secure = (bool)ppuGrSlaveCfg->secure;
 
        /* QAC Deviations: (No 1279) This macro is provided by Cypress Semiconductor, So, this warning can ignore and doesn't affect to the current behavior. */
        CoreIso_StatusCfgCheck(CoreIso_ConfigPpuFixedSlaveStruct(CoreIso_PeriPPUFxGrx(ppuStructIndex),
                                pcValue, &ppuGrCfg));
      }
    }
    else
    {
      // Do nothing
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
 * |void |- |No return value |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint16 |COREISO_NR_OF_PPU_CONFIGURED |Number of PPUs configured by the user |
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
 * |uint16 |ppuStructIndex |Loop counter for PPU structures |
 * |uint8 |pcIndex |Loop counter for protection contexts |
 * |cy_stc_ppu_gr_cfg_t |ppuGrCfg |Configuration structure for PPU slave settings |
 * |cy_en_prot_pc_t |pcValue |Protection context value for current configuration |
 * |const CoreIso_PPUGrCfgType* |ppuGrSlaveCfg |Pointer to slave configuration for current PPU and PC |
 * @brief Sets user-configured permissions for PPU slave structures
 * @note This function applies user-defined permission configurations to specific Peripheral
 * Protection Unit (PPU) slave structures.
/* FPT*/
/* date 2022 */
/************************************************************************************************/
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_PpuSetSlavePermission(void)
{
  uint16               ppuStructIndex;
  uint8                pcIndex;
  cy_stc_ppu_gr_cfg_t  ppuGrCfg;
  cy_en_prot_pc_t      pcValue;
  const CoreIso_PPUGrCfgType* ppuGrSlaveCfg;
 
  /* Enable permission for specific protection context as configuration */
  for(ppuStructIndex = 0u; ppuStructIndex < COREISO_NR_OF_PPU_CONFIGURED; ppuStructIndex++)
  {
    if (E_OK == CoreIso_IsPPUFxAvailable(CoreIso_GetPPUFxStruct(ppuStructIndex)))
    {
    /* Check the current PPU has any PC configurations */
      for (pcIndex = 0u; pcIndex < CoreIso_NrPcSlaveConfigPerPPU(ppuStructIndex); pcIndex++)
      {
        pcValue = (cy_en_prot_pc_t)((uint32_t)CoreIso_GetPCSlaveCfg(ppuStructIndex, pcIndex));
        ppuGrSlaveCfg = CoreIso_GetAttrSlaveCfgAddr(ppuStructIndex, pcIndex);
        ppuGrCfg.userPermission = (cy_en_prot_perm_t)((uint32_t)ppuGrSlaveCfg->userPermission);
        ppuGrCfg.privPermission = (cy_en_prot_perm_t)((uint32_t)ppuGrSlaveCfg->privPermission);
        ppuGrCfg.secure = (bool)ppuGrSlaveCfg->secure;
   
        /* QAC Deviations: (No 1279) This macro is provided by Cypress Semiconductor, So, this warning can ignore and doesn't affect to the current behavior. */
        CoreIso_StatusCfgCheck(CoreIso_ConfigPpuFixedSlaveStruct(CoreIso_GetPPUFxStructAddr(CoreIso_GetPPUFxStruct(ppuStructIndex)),
                                pcValue, &ppuGrCfg));
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
 * |void |- |No return value |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint16 |COREISO_MAX_FX_PPU_GR |Maximum number of PPU groups to configure |
 * |uint8 |COREISO_PROT_PC_NR |Number of protection contexts in the system |
 * |CoreIso_PPUProtConfigType[] |CoreIso_PPUMasterProtAttrDefault |Default master protection attributes for each PC |
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
 * |uint8 |pcIndex |Loop counter for protection contexts |
 * |uint16 |ppuStructIndex |Loop counter for PPU structures |
 * |cy_stc_ppu_gr_cfg_t |ppuGrCfg |Configuration structure for PPU master settings |
 * |cy_en_prot_pc_t |pcValue |Protection context value for current configuration |
 * |const CoreIso_PPUGrCfgType* |ppuGrMasterCfg |Pointer to master configuration for current PC |
 * @brief Sets default permissions for all PPU master structures
 * @note This function applies default permission configurations to all Peripheral Protection Unit (PPU)
 * master structures.
 */
/* FPT*/
/* date 2022 */
/************************************************************************************************/
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_PpuClrMasterPermissionAll(void)
{
  uint8                       pcIndex;
  uint16                      ppuStructIndex;
  cy_stc_ppu_gr_cfg_t         ppuGrCfg;
  cy_en_prot_pc_t             pcValue;
  const CoreIso_PPUGrCfgType* ppuGrMasterCfg;
 
  /* Disable permission for all PC of all PPUs (except PPU configured by Boot Rom) */
  for (ppuStructIndex = 0u; ppuStructIndex < COREISO_MAX_FX_PPU_GR; ppuStructIndex++)
  {
    if (E_OK == CoreIso_IsPPUFxAvailable(ppuStructIndex))
    {
      for (pcIndex = 0u; pcIndex < COREISO_PROT_PC_NR; pcIndex++)
      {
        pcValue = (cy_en_prot_pc_t)((uint32_t)CoreIso_PPUMasterProtAttrDefault[pcIndex].ProtContext);
        ppuGrMasterCfg = CoreIso_GetAttrMasterDefaultAtIndex(pcIndex);
        ppuGrCfg.userPermission = (cy_en_prot_perm_t)((uint32_t)ppuGrMasterCfg->userPermission);
        ppuGrCfg.privPermission = (cy_en_prot_perm_t)((uint32_t)ppuGrMasterCfg->privPermission);
        ppuGrCfg.secure = (bool)ppuGrMasterCfg->secure;
   
        /* QAC Deviations: (No 1279) This macro is provided by Cypress Semiconductor, So, this warning can ignore and doesn't affect to the current behavior. */
        CoreIso_StatusCfgCheck(CoreIso_ConfigPpuFixedMasterStruct(CoreIso_PeriPPUFxGrx(ppuStructIndex),
                                pcValue, &ppuGrCfg));
      }
    }
    else
    {
      // Do nothing
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
 * |void |- |No return value |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint16 |COREISO_NR_OF_PPU_CONFIGURED |Number of PPUs configured by the user |
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
 * |uint8 |pcIndex |Loop counter for protection contexts |
 * |uint16 |ppuStructIndex |Loop counter for PPU structures |
 * |cy_stc_ppu_gr_cfg_t |ppuGrCfg |Configuration structure for PPU master settings |
 * |cy_en_prot_pc_t |pcValue |Protection context value for current configuration |
 * |const CoreIso_PPUGrCfgType* |ppuGrMasterCfg |Pointer to master configuration for current PPU and PC |
 * @brief Sets user-configured permissions for PPU master structures
 * @note This function applies user-defined permission configurations to specific Peripheral
 * Protection Unit (PPU) master structures.
 */
/* FPT*/
/* date 2022 */
/************************************************************************************************/
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_PpuSetMasterPermission(void)
{
  uint8                pcIndex;
  uint16               ppuStructIndex;
  cy_stc_ppu_gr_cfg_t  ppuGrCfg;
  cy_en_prot_pc_t      pcValue;
  const CoreIso_PPUGrCfgType* ppuGrMasterCfg;
 
  /* Enable permission for specific protection context as config */
  for(ppuStructIndex = 0u; ppuStructIndex < COREISO_NR_OF_PPU_CONFIGURED; ppuStructIndex++)
  {
    if (E_OK == CoreIso_IsPPUFxAvailable(CoreIso_GetPPUFxStruct(ppuStructIndex)))
    {
      for (pcIndex = 0u; pcIndex < CoreIso_NrPcMasterConfigPerPPU(ppuStructIndex); pcIndex++)
      {
        pcValue = (cy_en_prot_pc_t)((uint32_t)CoreIso_GetPCMasterCfg(ppuStructIndex, pcIndex));
        ppuGrMasterCfg = CoreIso_GetAttrMasterCfgAddr(ppuStructIndex, pcIndex);
        ppuGrCfg.userPermission = (cy_en_prot_perm_t)((uint32_t)ppuGrMasterCfg->userPermission);
        ppuGrCfg.privPermission = (cy_en_prot_perm_t)((uint32_t)ppuGrMasterCfg->privPermission);
        ppuGrCfg.secure = (bool)ppuGrMasterCfg->secure;
   
        /* QAC Deviations: (No 1279) This macro is provided by Cypress Semiconductor, So, this warning can ignore and doesn't affect to the current behavior. */
        CoreIso_StatusCfgCheck(CoreIso_ConfigPpuFixedMasterStruct(CoreIso_GetPPUFxStructAddr(CoreIso_GetPPUFxStruct(ppuStructIndex)),
                                pcValue, &ppuGrCfg));
      }
    }
    else
    {
      // Do nothing
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
 * @brief Initializes all PPU slave structures with appropriate permissions
 * @note This function performs the complete initialization sequence for Peripheral Protection Unit
 * (PPU) slave structures, which control access to peripheral registers. The initialization
 * follows a two-step process:
 * * 1. First, it calls CoreIso_PpuClrSlavePermissionAll() to apply default (restrictive)
 * permissions to all PPU slave structures that are not configured by the boot ROM
 * * 2. Second, it calls CoreIso_PpuSetSlavePermission() to apply user-defined permissions
 * to specific PPU slave structures based on the configuration
 * * This approach ensures that all peripherals start with restricted access, and only
 * those explicitly configured in the user settings receive specific permissions.
 * This initialization is a critical part of establishing the system security boundary.
 */
/* FPT*/
/* date 2022 */
/************************************************************************************************/
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_PPUSlaveInit(void)
{
  /* First, clear slave permissions for all PCs. */
  CoreIso_PpuClrSlavePermissionAll();
 
  /* Second, set slave permissions for all PCs. */
  CoreIso_PpuSetSlavePermission();
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
 * @brief Initializes all PPU master structures with appropriate permissions
 * @note This function performs the complete initialization sequence for Peripheral Protection Unit
 * (PPU) master structures, which control how peripherals can access system memory.
/* FPT*/
/* date 2022 */
/************************************************************************************************/
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_PPUMasterInit(void)
{
  /* Initialize master permissions in a specific order to prevent exceptions.
   * HSM core has full access at default, the permision can change by configuration
   */
 
  /* First, clear permissions for all PCs except CM0. */
  CoreIso_PpuClrMasterPermissionAll();
 
  /* Then, set permissions as configuration. */
  CoreIso_PpuSetMasterPermission();
}
 
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |volatile stc_PROT_SMPU_SMPU_STRUCT_t* |base |Base address of the SMPU structure to configure |
 * |const cy_stc_smpu_cfg_t* |config |Pointer to the SMPU configuration structure |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |cy_en_prot_status_t |status |CY_PROT_SUCCESS if configuration succeeded, error code otherwise |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |volatile stc_PROT_SMPU_SMPU_STRUCT_t* |base |SMPU register structure updated with new configuration |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |const cy_stc_smpu_cfg_t* |config |Configuration parameters for the SMPU structure |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |un_PROT_SMPU_SMPU_STRUCT_ATT1_t |base->unATT1 |SMPU master attribute register |
 * @par Output registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |un_PROT_SMPU_SMPU_STRUCT_ATT1_t |base->unATT1 |Updated SMPU master attribute register |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |cy_en_prot_status_t |status |Status variable to track function success/failure |
 * |un_PROT_SMPU_SMPU_STRUCT_ATT1_t |tProtSmpuSmpuStructAttr1 |Local copy of SMPU attribute register for modification |
 * @brief Wrapper function for configuring SMPU master structures
 * @note This function provides a low-level implementation to configure Shared Memory Protection Unit
 * (SMPU) master structures.
 */
/* FPT*/
/* date 2022 */
/************************************************************************************************/
COREISO_LOCAL FUNC(cy_en_prot_status_t, AUTOMATIC) CoreIso_Wrapper_ConfigSmpuMasterStruct(volatile stc_PROT_SMPU_SMPU_STRUCT_t* base, const cy_stc_smpu_cfg_t* config)
{
    cy_en_prot_status_t status;
    //uint32_t attReg;
    un_PROT_SMPU_SMPU_STRUCT_ATT1_t tProtSmpuSmpuStructAttr1 = {0};
   
    /* QAC Deviations: (No 1279) This macro is provided by Cypress Semiconductor, So, this warning can ignore and doesn't affect to the current behavior. */
    if(((uint32_t)config->pcMask & CY_PROT_SMPU_PC_LIMIT_MASK) != 0U)  
    {
        /* PC mask out of range - not supported in device */
        status = CY_PROT_BAD_PARAM;
    }
    else
    {
      memcpy((void*)(&tProtSmpuSmpuStructAttr1), (void*)(&base->unATT1) , sizeof(un_PROT_SMPU_SMPU_STRUCT_ATT1_t));
      /* ADDR1 is read only. Only configure ATT1 */
      /* Read Write register*/
      tProtSmpuSmpuStructAttr1.stcField.u1NS = (uint32_t)(!(config->secure));
      tProtSmpuSmpuStructAttr1.stcField.u1UW = (uint32_t)(((uint32_t)config->userPermission & (uint32_t)CY_PROT_PERM_W) >> 1u);
      tProtSmpuSmpuStructAttr1.stcField.u1PW = (uint32_t)(((uint32_t)config->privPermission & (uint32_t)CY_PROT_PERM_W) >> 1u);
      tProtSmpuSmpuStructAttr1.stcField.u1PC_MATCH = (uint32_t)config->pcMatch;
      tProtSmpuSmpuStructAttr1.stcField.u15PC_MASK_15_TO_1 = config->pcMask;
 
      // /* Read Only register*/
      // tProtSmpuSmpuStructAttr1.stcField.u1UR = (base->userPermission & CY_PROT_PERM_R);
      // tProtSmpuSmpuStructAttr1.stcField.u1UX = (base->userPermission & CY_PROT_PERM_X) >> 2;
      // tProtSmpuSmpuStructAttr1.stcField.u1PR = (base->privPermission & CY_PROT_PERM_R);
      // tProtSmpuSmpuStructAttr1.stcField.u1PX = (base->privPermission & CY_PROT_PERM_X) >> 2;
 
      base->unATT1.u32Register = tProtSmpuSmpuStructAttr1.u32Register; //attReg;
      status = (base->unATT1.u32Register != tProtSmpuSmpuStructAttr1.u32Register) ? CY_PROT_FAILURE : CY_PROT_SUCCESS;
    }
     
    return status;
}
 
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |en_prot_master_t |busMaster |Identifier of the bus master to configure |
 * |uint32 |pc |Protection context value to set for the bus master |
 * @par Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |cy_en_prot_status_t |status |CY_PROT_SUCCESS if configuration succeeded, error code otherwise |
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
 * |stc_PROT_MPU_t |PROT->CYMPU |Base address of the MPU register structure array |
 * @par Output registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |un_PROT_MPU_MS_CTL_t |addrMpu->unMS_CTL |MPU master control register updated with new PC value |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |cy_en_prot_status_t |status |Status variable to track function success/failure |
 * |un_PROT_MPU_MS_CTL_t |tProtMpuMsCtl |Local structure for MPU master control register configuration |
 * |volatile stc_PROT_MPU_t* |addrMpu |Pointer to the specific MPU register structure for the target bus master |
 * @brief Sets the active Protection Context (PC) for a specified bus master
 * @note This function configures the active Protection Context for a given bus master in the
 * Memory Protection Unit (MPU). It performs the following operations:
 * * 1. Validates that the requested PC value is within the supported range
 * 2. Prepares a control register structure with the new PC value
 * 3. For the CM0+ core specifically (CPUSS_MS_ID_CM0), also sets the saved PC value
 * which is used after exception handling
 * 4. Writes the updated control register to the hardware
 * 5. Verifies the write was successful by comparing the written value with the register
 * * Setting the active PC is a critical operation as it determines which memory regions
 * and peripherals the bus master can access based on the protection policies. This function
 * is part of the core isolation initialization sequence and helps establish security
 * boundaries between different system components.
 */
/* FPT*/
/* date 2022 */
/************************************************************************************************/
COREISO_LOCAL FUNC(cy_en_prot_status_t, AUTOMATIC)  CoreIso_Wrapper_SetActivePC(en_prot_master_t busMaster, uint32_t pc)
{
    cy_en_prot_status_t status;
    un_PROT_MPU_MS_CTL_t tProtMpuMsCtl = {0};
    /* QAC Deviations: (No 1279) This macro is provided by Cypress Semiconductor, So, this warning can ignore and doesn't affect to the current behavior. */
    volatile stc_PROT_MPU_t* addrMpu = (volatile stc_PROT_MPU_t*)(&PROT->CYMPU[busMaster]);
 
    if(pc > (uint32_t)CY_PROT_MS_PC_NR_MAX)
    {
        /* Invalid PC value - not supported in device */
        status = CY_PROT_BAD_PARAM;
    }
    else
    {
        tProtMpuMsCtl.stcField.u4PC = pc;
        if(busMaster == CPUSS_MS_ID_CM0)
        {
          tProtMpuMsCtl.stcField.u4PC_SAVED = pc;
        }
        addrMpu->unMS_CTL.u32Register = tProtMpuMsCtl.u32Register;
        status = (((uint32_t)addrMpu->unMS_CTL.stcField.u4PC != pc) ? CY_PROT_FAILURE : CY_PROT_SUCCESS);
    }
 
    return status;
}
 
/************************************************************************************************/
/**
 * @par Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |const CoreIso_SMPUProtConfigType* |busMasterCfgPtr |Pointer to SMPU configuration for a specific bus master |
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
 * |const CoreIso_SMPUAttribute* |busMasterCfgPtr->SmpuProtSlaveCfg_Ptr |Array of SMPU slave configurations |
 * |const CoreIso_SMPUAttribute* |busMasterCfgPtr->SmpuProtMasterCfg_Ptr |Array of SMPU master configurations |
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
 * |cy_en_prot_status_t |retVal |Status variable to track operation success/failure |
 * |uint8 |structCfgIdx |Loop counter for SMPU structure configurations |
 * |uint8 |numberAttr |Number of SMPU structures to configure for this bus master |
 * |uint8 |smpuStructIdxConvert |Calculated SMPU structure index based on configuration |
 * |const CoreIso_SMPUAttribute* |smpuStructCfg_Ptr |Pointer to current SMPU attribute configuration |
 * @brief Initializes SMPU structures for a specific bus master
 * @note This function configures Shared Memory Protection Unit (SMPU) structures for a specific
 * bus master based on the provided configuration.
 */
/* FPT*/
/* date 2022 */
/************************************************************************************************/
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_SmpuBusMasterInit(const CoreIso_SMPUProtConfigType *busMasterCfgPtr)
{
 
   cy_en_prot_status_t retVal = CY_PROT_SUCCESS;
  uint8 structCfgIdx;
  uint8 numberAttr;
  uint8 smpuStructIdxConvert;
  const CoreIso_SMPUAttribute *smpuStructCfg_Ptr;
  /* QAC Deviations: (No 3383) Configuration and Generation rule of CoreIso module is made sure the overflow does not occur. */
  numberAttr = (uint8)((busMasterCfgPtr->StopBaseStructIdx - busMasterCfgPtr->StartBaseStructIdx) + 1u);
  /* SMPU slave struct Init */
  for(structCfgIdx = 0u; (structCfgIdx < numberAttr) && (CY_PROT_SUCCESS == retVal); structCfgIdx++)
  {
    smpuStructIdxConvert = busMasterCfgPtr->StartBaseStructIdx + structCfgIdx;
    smpuStructCfg_Ptr    = (const CoreIso_SMPUAttribute *)(&busMasterCfgPtr->SmpuProtSlaveCfg_Ptr[structCfgIdx]);
    /* Disable Region */
    /* QAC Deviations: (No 1279) This macro is provided by Cypress Semiconductor, So, this warning can ignore and doesn't affect to the current behavior. */
    retVal = ( CoreIso_DisableSmpuSlaveStruct(CoreIso_GetSmpuStructCfgBase(smpuStructIdxConvert)) );
    /* Configure Region */
    /* QAC Deviations: (No 1279) This macro is provided by Cypress Semiconductor, So, this warning can ignore and doesn't affect to the current behavior. */
    retVal |= ( CoreIso_ConfigSmpuSlaveStruct(CoreIso_GetSmpuStructCfgBase(smpuStructIdxConvert), smpuStructCfg_Ptr) );
    /* Enable Region*/
    if(retVal == CY_PROT_SUCCESS)
    {
      /* QAC Deviations: (No 1279) This macro is provided by Cypress Semiconductor, So, this warning can ignore and doesn't affect to the current behavior. */
      retVal |= CoreIso_EnableSmpuSlaveStruct(CoreIso_GetSmpuStructCfgBase(smpuStructIdxConvert));
    }
  }
 
  if( CY_PROT_SUCCESS == retVal)
  {
    /* SMPU master struct Init */
    for(structCfgIdx = 0u; (structCfgIdx < numberAttr) && (CY_PROT_SUCCESS == retVal); structCfgIdx++)
    {
      smpuStructIdxConvert = busMasterCfgPtr->StartBaseStructIdx + structCfgIdx;
      smpuStructCfg_Ptr    = (const CoreIso_SMPUAttribute *)(&busMasterCfgPtr->SmpuProtMasterCfg_Ptr[structCfgIdx]);
      /* Disable Region */
      /* QAC Deviations: (No 1279) This macro is provided by Cypress Semiconductor, So, this warning can ignore and doesn't affect to the current behavior. */
      retVal = ( CoreIso_DisableSmpuMasterStruct(CoreIso_GetSmpuStructCfgBase(smpuStructIdxConvert)) );
      /* Configure Region */
      /* QAC Deviations: (No 1279) This macro is provided by Cypress Semiconductor, So, this warning can ignore and doesn't affect to the current behavior. */
      retVal |= ( CoreIso_Wrapper_ConfigSmpuMasterStruct(CoreIso_GetSmpuStructCfgBase(smpuStructIdxConvert), smpuStructCfg_Ptr) );
      /* Enable Region*/
      if(retVal == CY_PROT_SUCCESS)
      {
        /* QAC Deviations: (No 1279) This macro is provided by Cypress Semiconductor, So, this warning can ignore and doesn't affect to the current behavior. */
        retVal |= CoreIso_EnableSmpuMasterStruct(CoreIso_GetSmpuStructCfgBase(smpuStructIdxConvert));
      }
    }
  }
 
  if (CY_PROT_SUCCESS != retVal)
  {
    CoreIso_InitErrorHook(); // nerver return
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
 * |void |- |No return value |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint16 |COREISO_MAX_FX_PPU_GR |Maximum number of PPU groups to configure |
 * |uint8 |COREISO_PROT_PC_NR |Number of protection contexts in the system |
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
 * |uint8 |pcIndex |Loop counter for protection contexts |
 * |uint16 |ppuStructIndex |Loop counter for PPU structures |
 * |cy_stc_ppu_gr_cfg_t |ppuGrCfg |Configuration structure for PPU settings |
 * |cy_en_prot_pc_t |pcValue |Protection context value derived from loop index |
 * @brief Disables all Peripheral Protection Units by setting default permissions
 * @note This function sets default permissions for all Peripheral Protection Units (PPUs) that
 * are not configured by the boot ROM.
 */
/* FPT*/
/* date 2022 */
/************************************************************************************************/
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_DisableAllPpus(void)
{
  uint8                       pcIndex;
  uint16                      ppuStructIndex;
  cy_stc_ppu_gr_cfg_t         ppuGrCfg;
  cy_en_prot_pc_t             pcValue;
 
  /* Disable permission for all PC of all PPUs (except PPU configured by Boot Rom) */
  for (ppuStructIndex = 0u; ppuStructIndex < COREISO_MAX_FX_PPU_GR; ppuStructIndex++)
  {
    if (E_OK == CoreIso_IsPPUFxAvailable(ppuStructIndex))
    {
      for (pcIndex = 0u; pcIndex < COREISO_PROT_PC_NR; pcIndex++)
      {
        pcValue = (cy_en_prot_pc_t)((uint32_t)pcIndex);
        ppuGrCfg.userPermission = (cy_en_prot_perm_t)CY_PROT_PERM_RW;
        ppuGrCfg.privPermission = (cy_en_prot_perm_t)CY_PROT_PERM_RW;
        ppuGrCfg.secure         = (bool)COREISO_NON_SECURE;
   
        /* QAC Deviations: (No 1279) This macro is provided by Cypress Semiconductor, So, this warning can ignore and doesn't affect to the current behavior. */
        CoreIso_StatusCfgCheck(CoreIso_ConfigPpuFixedMasterStruct(CoreIso_PeriPPUFxGrx(ppuStructIndex), pcValue, &ppuGrCfg));
   
        /* QAC Deviations: (No 1279) This macro is provided by Cypress Semiconductor, So, this warning can ignore and doesn't affect to the current behavior. */
        CoreIso_StatusCfgCheck(CoreIso_ConfigPpuFixedSlaveStruct(CoreIso_PeriPPUFxGrx(ppuStructIndex), pcValue, &ppuGrCfg));
      }
    }
    else
    {
      // Do nothing
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
 * |void |- |No return value |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |CoreIso_SMPUConfigType[] |CoreIso_SmpuCfg |Array of SMPU configurations for different bus masters |
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
 * |cy_en_prot_status_t |retVal |Status variable to track operation success/failure |
 * |uint8 |structCfgIdx |Loop counter for SMPU structure configurations |
 * |uint8 |numberAttr |Number of SMPU structures to configure for current bus master |
 * |uint8 |smpuStructIdxConvert |Calculated SMPU structure index based on configuration |
 * |uint8 |sizeOfSmpuCfg |Size of the SMPU configuration array |
 * |uint8 |smpuCfgIdx |Loop counter for SMPU configurations |
 * @brief Disables all configured Shared Memory Protection Units
 * @note This function disables all Shared Memory Protection Units (SMPUs) that are configured
 * in the CoreIso_SmpuCfg array.
/* FPT*/
/* date 2022 */
/************************************************************************************************/
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_SmpuBusMasterDisableAll(void)
{
  cy_en_prot_status_t retVal = CY_PROT_SUCCESS;
  uint8 structCfgIdx;
  uint8 numberAttr;
  uint8 smpuStructIdxConvert;
  uint8 sizeOfSmpuCfg ;
  uint8 smpuCfgIdx;
 
  sizeOfSmpuCfg = sizeof(CoreIso_SmpuCfg)/sizeof(CoreIso_SMPUConfigType);
  for( smpuCfgIdx =0u; smpuCfgIdx < sizeOfSmpuCfg; smpuCfgIdx++)
  {
    if( NULL_PTR != CoreIso_SmpuCfg[smpuCfgIdx].SmpuBusMasterCfg_Ptr)
    {
      /* QAC Deviations: (No 3383) Configuration and Generation rule of CoreIso module is made sure the overflow does not occur. */
      numberAttr = (uint8)((CoreIso_SmpuCfg[smpuCfgIdx].SmpuBusMasterCfg_Ptr->StopBaseStructIdx - CoreIso_SmpuCfg[smpuCfgIdx].SmpuBusMasterCfg_Ptr->StartBaseStructIdx) + 1u);
      /* SMPU master struct DeInit */
      for(structCfgIdx = 0u; (structCfgIdx < numberAttr) && (CY_PROT_SUCCESS == retVal); structCfgIdx++)
      {
        smpuStructIdxConvert = CoreIso_SmpuCfg[smpuCfgIdx].SmpuBusMasterCfg_Ptr->StartBaseStructIdx + structCfgIdx;
        /* Disable Region */
        /* QAC Deviations: (No 1279) This macro is provided by Cypress Semiconductor, So, this warning can ignore and doesn't affect to the current behavior. */
        retVal = ( CoreIso_DisableSmpuMasterStruct(CoreIso_GetSmpuStructCfgBase(smpuStructIdxConvert)) );
      }
 
      /* SMPU slave struct DeInit */
      for(structCfgIdx = 0u; (structCfgIdx < numberAttr) && (CY_PROT_SUCCESS == retVal); structCfgIdx++)
      {
        smpuStructIdxConvert = CoreIso_SmpuCfg[smpuCfgIdx].SmpuBusMasterCfg_Ptr->StartBaseStructIdx + structCfgIdx;
        /* Disable Region */
        /* QAC Deviations: (No 1279) This macro is provided by Cypress Semiconductor, So, this warning can ignore and doesn't affect to the current behavior. */
        retVal =  CoreIso_DisableSmpuSlaveStruct(CoreIso_GetSmpuStructCfgBase(smpuStructIdxConvert));
      }
    }
  }
 
  if (CY_PROT_SUCCESS != retVal)
  {
    CoreIso_InitErrorHook(); // nerver return
  }
}
/** @cond INTERNAL */
# define COREISO_STOP_SEC_CODE
# include "CoreIso_MemMap.h"
 
 
# define COREISO_START_SEC_CODE
# include "CoreIso_MemMap.h"
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
 * |CoreIso_SMPUConfigType[] |CoreIso_SmpuCfg |Array of SMPU configurations for different bus masters |
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
 * |uint8 |sizeOfSmpuCfg |Size of the SMPU configuration array |
 * |uint8 |smpuCfgIdx |Loop counter for SMPU configurations |
 * @brief Initializes all configured Shared Memory Protection Units
 * @note This function initializes all Shared Memory Protection Units (SMPUs) that are configured
/* FPT*/
/* date 2022 */
/************************************************************************************************/
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_SMPUInit(void)
{
  uint8 sizeOfSmpuCfg ;
  uint8 smpuCfgIdx;
 
  sizeOfSmpuCfg = sizeof(CoreIso_SmpuCfg)/sizeof(CoreIso_SMPUConfigType);
  for( smpuCfgIdx =0u; smpuCfgIdx < sizeOfSmpuCfg; smpuCfgIdx++)
  {
    if( NULL_PTR != CoreIso_SmpuCfg[smpuCfgIdx].SmpuBusMasterCfg_Ptr)
    {
      CoreIso_SmpuBusMasterInit(CoreIso_SmpuCfg[smpuCfgIdx].SmpuBusMasterCfg_Ptr);
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
 * |void |- |No return value |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |cy_stc_mpu_region_cfg_t[] |CoreIso_MPUConfig |Array of MPU region configurations |
 * |uint32 |CORE_ISOLATION_MPU_NO |Number of MPU regions to configure |
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
 * |MPU registers |MPU->CTRL, MPU->RBAR, MPU->RASR |MPU control and region registers configured by Cy_MPU_Setup |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @brief Initializes the Memory Protection Unit (MPU) for CM0+
 * @note This function sets up the MPU for the CM0+ core to restrict its memory access according
 * to the configured memory regions defined in CoreIso_MPUConfig.
 */
/* FPT*/
/* date 2022 */
/************************************************************************************************/
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_MPUInit(void)
{
  /* Init the Memory Protection Unit for CM0+ */
  (void)Cy_MPU_Setup( \
    CoreIso_MPUConfig, \
    CORE_ISOLATION_MPU_NO, \
    (cy_en_mpu_privdefena_t)CY_MPU_DISABLE_USE_DEFAULT_MAP, \
    (cy_en_mpu_hfnmiena_t)CY_MPU_DISABLED_DURING_FAULT_NMI);
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
 * |uint8 |COREISO_NR_OF_MASTER |Number of bus masters to configure |
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
 * |uint8 |masterIndex |Loop counter for iterating through bus masters |
 * @brief Configures protection context attributes for all bus masters
 * @note This function configures the protection attributes for all bus masters in the system,
 * including CM0+, CM7_0, CM7_1, and other masters defined in the configuration.
/* FPT*/
/* date 2022 */
/************************************************************************************************/
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_ConfigBusMasters(void)
{
  uint8 masterIndex;
 
  /* Config protection context control for CM0, SDHC, ETH0, ETH1, CM70, CM71 and DAP masters */
  for (masterIndex = 0u; masterIndex < COREISO_NR_OF_MASTER; masterIndex++)
  {
    /* QAC Deviations: (No 3383) Configuration of CoreIso module is make sure the overflow does not occur*/
    CoreIso_StatusCfgCheck(Cy_Prot_ConfigBusMaster(
                           /*BusMasterID*/ CoreIso_GetMasterIdFrPcControlCfg(masterIndex),  \
                           /*privileged*/  CoreIso_GetPrivLevelFrPcControlCfg(masterIndex), \
                           /*secured*/     CoreIso_GetSecureSetFrPcControlCfg(masterIndex), \
                           /*PC Masked*/   CoreIso_GetPcMask(CoreIso_GetProContxtFrPcControlCfg(masterIndex))) );
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
 * |void |- |No return value |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint8 |COREISO_NR_OF_MASTER |Number of bus masters to configure |
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
 * |uint8 |masterIndex |Loop counter for iterating through bus masters |
 * @brief Activates the configured protection contexts for all bus masters
 * @note This function activates the assigned protection context for each bus master in the system.
 */
/* FPT*/
/* date 2022 */
/************************************************************************************************/
COREISO_LOCAL FUNC(void, AUTOMATIC) CoreIso_ActivePCs(void)
{
  uint8 masterIndex;
 
  /* Config protection context for CM0, SDHC, ETH0, ETH1, CM70, CM71 and DAP masters */
  for (masterIndex = 0u; masterIndex < COREISO_NR_OF_MASTER; masterIndex++)
  {
    if (CoreIso_GetMasterIdFrPcControlCfg(masterIndex) == CPUSS_MS_ID_CM0)
    {
      /* QAC Deviations: (No 4424) This type is provided by Cypress Semiconductor, So, this warning can ignore and doesn't affect to the current behavior. */
      CoreIso_StatusCfgCheck(CoreIso_Wrapper_SetActivePC(CoreIso_GetMasterIdFrPcControlCfg(masterIndex),
                                                          (uint32_t)CoreIso_GetProContxtFrPcControlCfg(masterIndex)));
    }
    else
    {
      /* QAC Deviations: (No 4424) This type is provided by Cypress Semiconductor, So, this warning can ignore and doesn't affect to the current behavior. */
      CoreIso_StatusCfgCheck(Cy_Prot_SetActivePC(CoreIso_GetMasterIdFrPcControlCfg(masterIndex),
                                                  (uint32_t)CoreIso_GetProContxtFrPcControlCfg(masterIndex)));
    }
 
    /* QAC Deviations: (No 1881) This type is provided by Cypress Semiconductor, So, this warning can ignore and doesn't affect to the current behavior. */
    if (CoreIso_GetProContxtFrPcControlCfg(masterIndex) != Cy_Prot_GetActivePC(CoreIso_GetMasterIdFrPcControlCfg(masterIndex)))
    {
      CoreIso_InitErrorHook();
    }
    else
    {
      /* Do nothing*/
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
 * |void |- |No return value |
 * @par Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint16 |g_CoreIsoInitSts |Global status flag for CoreIso initialization |
 * |uint32 |SRAM_SECURE_DTC |Memory address for the secure DTC(Diagnostic Trouble Code) region in SRAM |
 * @par Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |uint16 |g_CoreIsoInitSts |Set to FALSE at start, may be changed to TRUE if initialization fails |
 * @par Reference registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @par Output registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |MPU->CTRL |MPU control register |Set to 0 if initialization fails |
 * @par Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:---------------:|
 * |- |- |- |
 * @brief Initializes the CoreIso module to establish memory protection and core isolation
 * @note This function is the main entry point for CoreIso module initialization.
 */
/* FPT*/
/* date 2022 */
/************************************************************************************************/
FUNC(void, AUTOMATIC) CoreIso_Init(void)
{
  g_CoreIsoInitSts = FALSE;
 
  /* MPU init */
  CoreIso_MPUInit();
 
  /* SMPU & PPU init*/
  /* 1. Set Configure Attribute for Bus master */
  CoreIso_ConfigBusMasters();
 
  /* 2. Active PC context */
  CoreIso_ActivePCs();
 
  /* 3. SMPU init
    + Disable Region
    + Configured Region
    + Enable Region
  */
  CoreIso_SMPUInit();
 
  /* 4. PPU init*/
  CoreIso_PPUSlaveInit();
  CoreIso_PPUMasterInit();
 
  /* Validate Init Error Hook*/
  if(TRUE == CoreIso_GetInitErrorHook())
  {
    /* Disable All PPU*/
    CoreIso_DisableAllPpus();
    /* Disable SMPU */
    CoreIso_SmpuBusMasterDisableAll();
    /* Disable the MPU */
    /* QAC Deviations: (No 1279) This macro is provided by Cypress Semiconductor, So, this warning can ignore and doesn't affect to the current behavior. */
    MPU->CTRL = 0u;
    /* Record DTC code*/
    CoreIso_SetDtcError(TRUE, (uint32*)SRAM_SECURE_DTC);
  }
  else
  {
    CoreIso_SetDtcError(FALSE, (uint32*)SRAM_SECURE_DTC);
  }
}
/** @cond INTERNAL */
# define COREISO_STOP_SEC_CODE
# include "CoreIso_MemMap.h"
 /** @endcond */
/**********************************************************************************************************************
 *  END OF FILE: CoreIso.c
 *********************************************************************************************************************/
 
 
 
