/**
 * @file CoreIso_ConfigData.h
 * @brief Public header for Core Isolation Configuration Data
 * @details Overview: Configuration header for Core Isolation module that defines protection settings for different processing cores and peripherals in multi-core systems
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
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: CoreIso_ConfigData.h
 *   Generation Time: Monday, 19 May 2025 21:05:48
 *           Project: Security
 *          Delivery:
 *      Tool Version: 1.5.3
 *
 *
 *********************************************************************************************************************/
#if !defined (COREISO_CONFIGDATA_H)
# define COREISO_CONFIGDATA_H
 
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Std_Types.h"
# include "cy_prot.h"
# include "cy_mpu.h"
 
 
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/**
 * @def COREISO_NON_SECURE
 * @value 0u
 * @resolution -
 * @brief Flag value indicating non-secure access mode
 */
# define COREISO_NON_SECURE                                           0u
 
/**
 * @def COREISO_SECURE
 * @value 1u
 * @resolution -
 * @brief Flag value indicating secure access mode
 */
# define COREISO_SECURE                                               1u
 
/**
 * @def COREISO_USER_MODE
 * @value 0u
 * @resolution -
 * @brief Flag value indicating user (unprivileged) mode
 */
# define COREISO_USER_MODE                                            0u
 
/**
 * @def COREISO_PRIVILEGE_MODE
 * @value 1u
 * @resolution -
 * @brief Flag value indicating privileged mode
 */
# define COREISO_PRIVILEGE_MODE                                       1u
 
/**
 * @def COREISO_MAX_FX_PPU_GR
 * @value 702u
 * @resolution -
 * @brief Maximum number of Fixed Peripheral Protection Unit (PPU) groups
 */
# define COREISO_MAX_FX_PPU_GR                                        702u
 
/**
 * @def COREISO_PROT_PC_NR
 * @value 7u
 * @resolution -
 * @brief Number of available protection contexts
 */
# define COREISO_PROT_PC_NR                                           7u
 
/**
 * @def COREISO_NR_OF_MASTER
 * @value 7u
 * @resolution -
 * @brief Number of bus masters in the system
 */
# define COREISO_NR_OF_MASTER                                         7u
 
/**
 * @def COREISO_NR_OF_PPU_CONFIGURED
 * @value 49u
 * @resolution -
 * @brief Number of Peripheral Protection Units (PPUs) configured in the system
 */
# define COREISO_NR_OF_PPU_CONFIGURED                                 49u
 
/**
 * @def COREISO_NR_OF_PPU_SLAVE_CONFIG
 * @value 94u
 * @resolution -
 * @brief Number of PPU slave configurations
 */
# define COREISO_NR_OF_PPU_SLAVE_CONFIG                               94u
 
/**
 * @def COREISO_NR_OF_PPU_MASTER_CONFIG
 * @value 0u
 * @resolution -
 * @brief Number of PPU master configurations
 */
# define COREISO_NR_OF_PPU_MASTER_CONFIG                              0u
 
/**
 * @def COREISO_CM0P_SECURITY
 * @value COREISO_SECURE
 * @resolution -
 * @brief Security setting for CM0+ core
 */
# define COREISO_CM0P_SECURITY                                        COREISO_SECURE
 
/**
 * @def COREISO_PC_CM0P
 * @value CY_PROT_PC5
 * @resolution -
 * @brief Protection context for CM0+ core
 */
# define COREISO_PC_CM0P                                              CY_PROT_PC5
 
/**
 * @def COREISO_PC_CM70
 * @value CY_PROT_PC6
 * @resolution -
 * @brief Protection context for CM7_0 core
 */
# define COREISO_PC_CM70                                              CY_PROT_PC6
 
/**
 * @def COREISO_PC_CM71
 * @value CY_PROT_PC7
 * @resolution -
 * @brief Protection context for CM7_1 core
 */
# define COREISO_PC_CM71                                              CY_PROT_PC7
 
/**
 * @def COREISO_PC_TESTCONTROL
 * @value CY_PROT_PC2
 * @resolution -
 * @brief Protection context for test control interface
 */
# define COREISO_PC_TESTCONTROL                                       CY_PROT_PC2
 
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/**
 * @def CoreIso_ConfigPpuFixedSlaveStruct
 * @value Cy_Prot_ConfigPpuFixedSlaveStruct((base), (pc), (config))
 * @resolution -
 * @brief Wrapper for Cypress PPU fixed slave structure configuration function
 */
# define CoreIso_ConfigPpuFixedSlaveStruct(base, pc, config)   Cy_Prot_ConfigPpuFixedSlaveStruct((base), (pc), (config))
 
/**
 * @def CoreIso_ConfigPpuFixedMasterStruct
 * @value Cy_Prot_ConfigPpuFixedMasterStruct((base), (pc), (config))
 * @resolution -
 * @brief Wrapper for Cypress PPU fixed master structure configuration function
 */
# define CoreIso_ConfigPpuFixedMasterStruct(base, pc, config)  Cy_Prot_ConfigPpuFixedMasterStruct((base), (pc), (config))
 
/**
 * @def CoreIso_PeriPPUFxGrx
 * @value ((volatile stc_PERI_MS_PPU_FX_t*) (&PERI_MS->PPU_FX[(index)]))
 * @resolution -
 * @brief Access to a specific peripheral PPU fixed group by index
 */
# define CoreIso_PeriPPUFxGrx(index)                           ((volatile stc_PERI_MS_PPU_FX_t*) (&PERI_MS->PPU_FX[(index)]))
 
/**
 * @def CoreIso_IsPCOfCM0P
 * @value (COREISO_PC_CM0P == (uint32)(pc))
 * @resolution -
 * @brief Check if a protection context belongs to the CM0+ core
 */
# define CoreIso_IsPCOfCM0P(pc)                                (COREISO_PC_CM0P == (uint32)(pc))
 
/**
 * @def CoreIso_GetPPUFxStruct
 * @value (CoreIso_PPUFxConfig[(index)].PPUFxStruct)
 * @resolution -
 * @brief Get the PPU fixed structure index from configuration
 */
# define CoreIso_GetPPUFxStruct(index)                         (CoreIso_PPUFxConfig[(index)].PPUFxStruct)
 
/**
 * @def CoreIso_GetPPUFxStructAddr
 * @value (CoreIso_PeriPPUFxGrx((index)))
 * @resolution -
 * @brief Get the address of a PPU fixed structure
 */
# define CoreIso_GetPPUFxStructAddr(index)                     (CoreIso_PeriPPUFxGrx((index)))
 
/**
 * @def CoreIso_NrPcSlaveConfigPerPPU
 * @value (CoreIso_PPUFxConfig[(index)].NrOfPcSlaveConfigured)
 * @resolution -
 * @brief Get the number of protection contexts configured for a PPU slave
 */
# define CoreIso_NrPcSlaveConfigPerPPU(index)                  (CoreIso_PPUFxConfig[(index)].NrOfPcSlaveConfigured)
 
/**
 * @def CoreIso_GetPCSlaveCfg
 * @value (CoreIso_PPUFxConfig[(ppuIndex)].ProtSlaveConfig[(pcIndex)].ProtContext)
 * @resolution -
 * @brief Get the protection context configuration for a PPU slave
 */
# define CoreIso_GetPCSlaveCfg(ppuIndex, pcIndex)              (CoreIso_PPUFxConfig[(ppuIndex)].ProtSlaveConfig[(pcIndex)].ProtContext)
 
/**
 * @def CoreIso_GetAttrSlaveCfgAddr
 * @value (&(CoreIso_PPUFxConfig[(ppuIndex)].ProtSlaveConfig[(pcIndex)].Attribute))
 * @resolution -
 * @brief Get the address of attribute configuration for a PPU slave
 */
# define CoreIso_GetAttrSlaveCfgAddr(ppuIndex, pcIndex)        (&(CoreIso_PPUFxConfig[(ppuIndex)].ProtSlaveConfig[(pcIndex)].Attribute))
 
/**
 * @def CoreIso_NrPcMasterConfigPerPPU
 * @value (CoreIso_PPUFxConfig[(index)].NrOfPcMasterConfigured)
 * @resolution -
 * @brief Get the number of protection contexts configured for a PPU master
 */
# define CoreIso_NrPcMasterConfigPerPPU(index)                 (CoreIso_PPUFxConfig[(index)].NrOfPcMasterConfigured)
 
/**
 * @def CoreIso_GetPCMasterCfg
 * @value (CoreIso_PPUFxConfig[(ppuIndex)].ProtMasterConfig[(pcIndex)].ProtContext)
 * @resolution -
 * @brief Get the protection context configuration for a PPU master
 */
# define CoreIso_GetPCMasterCfg(ppuIndex, pcIndex)             (CoreIso_PPUFxConfig[(ppuIndex)].ProtMasterConfig[(pcIndex)].ProtContext)
 
/**
 * @def CoreIso_GetAttrMasterCfgAddr
 * @value (&(CoreIso_PPUFxConfig[(ppuIndex)].ProtMasterConfig[(pcIndex)].Attribute))
 * @resolution -
 * @brief Get the address of attribute configuration for a PPU master
 */
# define CoreIso_GetAttrMasterCfgAddr(ppuIndex, pcIndex)       (&(CoreIso_PPUFxConfig[(ppuIndex)].ProtMasterConfig[(pcIndex)].Attribute))
 
/**
 * @def CoreIso_GetPCSlaveDefaultAtIndex
 * @value (CoreIso_PPUSlaveProtAttrDefault[(index)].ProtContext)
 * @resolution -
 * @brief Get the default protection context for a PPU slave
 */
# define CoreIso_GetPCSlaveDefaultAtIndex(index)               (CoreIso_PPUSlaveProtAttrDefault[(index)].ProtContext)
 
/**
 * @def CoreIso_GetAttrSlaveDefaultAtIndex
 * @value (&(CoreIso_PPUSlaveProtAttrDefault[(index)].Attribute))
 * @resolution -
 * @brief Get the address of default attribute configuration for a PPU slave
 */
# define CoreIso_GetAttrSlaveDefaultAtIndex(index)             (&(CoreIso_PPUSlaveProtAttrDefault[(index)].Attribute))
 
/**
 * @def CoreIso_GetPCMasterDefaultAtIndex
 * @value (CoreIso_PPUMasterProtAttrDefault[(index)].ProtContext)
 * @resolution -
 * @brief Get the default protection context for a PPU master
 */
# define CoreIso_GetPCMasterDefaultAtIndex(index)              (CoreIso_PPUMasterProtAttrDefault[(index)].ProtContext)
 
/**
 * @def CoreIso_GetAttrMasterDefaultAtIndex
 * @value (&(CoreIso_PPUMasterProtAttrDefault[(index)].Attribute))
 * @resolution -
 * @brief Get the address of default attribute configuration for a PPU master
 */
# define CoreIso_GetAttrMasterDefaultAtIndex(index)            (&(CoreIso_PPUMasterProtAttrDefault[(index)].Attribute))
 
/**
 * @def CoreIso_GetMasterIdFrPcControlCfg
 * @value (CoreIso_PcControlConfig[(index)].busMasterId)
 * @resolution -
 * @brief Get the bus master ID from protection context control configuration
 */
# define CoreIso_GetMasterIdFrPcControlCfg(index)              (CoreIso_PcControlConfig[(index)].busMasterId)
 
/**
 * @def CoreIso_GetPrivLevelFrPcControlCfg
 * @value (CoreIso_PcControlConfig[(index)].privSetting)
 * @resolution -
 * @brief Get the privilege level from protection context control configuration
 */
# define CoreIso_GetPrivLevelFrPcControlCfg(index)             (CoreIso_PcControlConfig[(index)].privSetting)
 
/**
 * @def CoreIso_GetSecureSetFrPcControlCfg
 * @value (CoreIso_PcControlConfig[(index)].secureSetting)
 * @resolution -
 * @brief Get the security setting from protection context control configuration
 */
# define CoreIso_GetSecureSetFrPcControlCfg(index)             (CoreIso_PcControlConfig[(index)].secureSetting)
 
/**
 * @def CoreIso_GetProContxtFrPcControlCfg
 * @value (CoreIso_PcControlConfig[(index)].protContext)
 * @resolution -
 * @brief Get the protection context from protection context control configuration
 */
# define CoreIso_GetProContxtFrPcControlCfg(index)             (CoreIso_PcControlConfig[(index)].protContext)
 
 
/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/**
 * @brief Configuration structure for protection context control initialization for different bus masters
 * @datasize 12 bytes
 */
typedef struct
{
  en_prot_master_t  busMasterId;          /**< Master ID of the bus master (CM0, SDHC, ETH0, ETH1, CM70, CM71, DAP) */
  bool              privSetting;          /**< Privilege level setting for the master (TRUE: privileged, FALSE: user mode) */
  bool              secureSetting;        /**< Security setting for the master (TRUE: secure, FALSE: non-secure) */
  cy_en_prot_pc_t   protContext;          /**< Protection context assigned to the master */
} CoreIso_PcControlCfgType;
 
/**
 * @brief Configuration structure for Fixed Group PPU initialization with permission settings
 * @datasize 2 bytes
 */
typedef struct
{
  cy_en_prot_perm_t userPermission : 5;   /**< User permissions for the region (read, write, or no access) */
  cy_en_prot_perm_t privPermission : 5;   /**< Privileged permissions for the region (read, write, or no access) */
  uint8             secure : 6;           /**< Security setting (0: Non-Secure, 1: Secure) */
} CoreIso_PPUGrCfgType;
 
/**
 * @brief Protection context configuration structure with attributes for a specific context
 * @datasize 4 bytes
 */
typedef struct sCoreIso_PPUProtConfigType
{
  cy_en_prot_pc_t      ProtContext : 16;  /**< Protection context to which this configuration applies */
  CoreIso_PPUGrCfgType Attribute;         /**< Protection attributes (permissions and security settings) */
} CoreIso_PPUProtConfigType;
 
/**
 * @brief Configuration structure for Fixed Peripheral Protection Units with slave and master settings
 * @datasize 12+ bytes (variable size due to pointers, depends on platform)
 */
typedef struct sCoreIso_PPUFxConfigType
{
  uint8                                                      NrOfPcSlaveConfigured;   /**< Number of protection contexts configured for slave structure */
  uint8                                                      NrOfPcMasterConfigured;  /**< Number of protection contexts configured for master structure */
  uint16                                                     PPUFxStruct;            /**< Index of the Fixed Peripheral structure for the peripheral */
  P2CONST(CoreIso_PPUProtConfigType, AUTOMATIC, AUTOMATIC)   ProtSlaveConfig;        /**< Pointer to slave protection configuration array */
  P2CONST(CoreIso_PPUProtConfigType, AUTOMATIC, AUTOMATIC)   ProtMasterConfig;       /**< Pointer to master protection configuration array */
} CoreIso_PPUFxConfigType;
 
 
/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
/** @cond INTERNAL */
# define COREISO_START_SEC_CONST
# include "CoreIso_MemMap.h"
 
/**********************************************************************************************************************
  CoreIso_PcControlConfig
**********************************************************************************************************************/
extern CONST(CoreIso_PcControlCfgType, AUTOMATIC) CoreIso_PcControlConfig[COREISO_NR_OF_MASTER];
 
/**********************************************************************************************************************
  CoreIso_PPUSlaveProtAttrDefault
**********************************************************************************************************************/
extern CONST(CoreIso_PPUProtConfigType, AUTOMATIC) CoreIso_PPUSlaveProtAttrDefault[COREISO_PROT_PC_NR];
 
/**********************************************************************************************************************
  CoreIso_PPUMasterProtAttrDefault
**********************************************************************************************************************/
extern CONST(CoreIso_PPUProtConfigType, AUTOMATIC) CoreIso_PPUMasterProtAttrDefault[COREISO_PROT_PC_NR];
 
/**********************************************************************************************************************
  CoreIso_PPUFxConfig
**********************************************************************************************************************/
extern CONST(CoreIso_PPUFxConfigType, AUTOMATIC) CoreIso_PPUFxConfig[COREISO_NR_OF_PPU_CONFIGURED];
 
# define COREISO_STOP_SEC_CONST
# include "CoreIso_MemMap.h"
/** @endcond */
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
 
#endif /* COREISO_CONFIGDATA_H */
 
/**********************************************************************************************************************
 *  END OF FILE: CoreIso_ConfigData.h
 *********************************************************************************************************************/
 
 