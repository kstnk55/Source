/**
 * @file CoreIso.h
 * @brief Public header for Core Isolation
 * @details Overview: Core Isolation module header for configuring memory protection and access control between processor cores
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
 *     file  CoreIso.h
 *      brief  
 *      details  
 *********************************************************************************************************************/
#if !defined (COREISO_H)
# define COREISO_H
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Std_Types.h"
# include "cy_prot.h"
 
 
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
 
 
/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
 
 
/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/**
 * @type stc_PROT_SMPU_SMPU_STRUCT_t
 * @brief SMPU struct configuration type definition
 */
typedef stc_PROT_SMPU_SMPU_STRUCT_t CoreIso_SMPUStruct;
 
/**
 * @type cy_stc_smpu_cfg_t
 * @brief SMPU attribute configuration type definition
 */
typedef cy_stc_smpu_cfg_t           CoreIso_SMPUAttribute;
 
/**
 * @brief Configuration structure for SMPU protection settings with context and region definitions
 * @datasize Variable size structure containing protection context, index values, and two pointers (varies based on platform)
 */
typedef struct sCoreIso_SMPUProtConfigType
{
  cy_en_prot_pc_t      ProtContext;                                             /**< Protection context identifier for access control */
  uint8                StartBaseStructIdx;                                      /**< Starting index for SMPU base structure configuration */
  uint8                StopBaseStructIdx;                                       /**< Ending index for SMPU base structure configuration */
  P2CONST(CoreIso_SMPUAttribute, AUTOMATIC, AUTOMATIC) SmpuProtSlaveCfg_Ptr;    /**< Pointer to SMPU slave configuration attributes */
  P2CONST(CoreIso_SMPUAttribute, AUTOMATIC, AUTOMATIC) SmpuProtMasterCfg_Ptr;   /**< Pointer to SMPU master configuration attributes */
} CoreIso_SMPUProtConfigType;
 
/**
 * @brief Top-level SMPU configuration structure linking bus master ID with protection settings
 * @datasize 8 bytes + pointer size (12 bytes on 32-bit platforms)
 */
typedef struct sCoreIso_SMPUConfigType
{
  en_prot_master_t BusMasterId;                                                     /**< Bus master identifier for SMPU configuration */
  P2CONST(CoreIso_SMPUProtConfigType, AUTOMATIC, AUTOMATIC) SmpuBusMasterCfg_Ptr;   /**< Pointer to SMPU bus master protection configuration */
} CoreIso_SMPUConfigType;
 
/**
 * @brief Union structure for diagnostic trouble code flags related to core isolation
 * @datasize 4 bytes (32-bit union)
 */
typedef union sCoreIso_DtcFlagType
{
  uint32 SecureBootDtc;           /**< Full 32-bit DTC value for secure boot operations */
  struct{
    uint8 Reserved_byte0 :8;      /**< Reserved byte 0 - not used */
    uint8 Reserved_byte1 :8;      /**< Reserved byte 1 - not used */
    uint8 DTC_COREISO_CM0:4;      /**< DTC flags specific to core isolation on CM0 processor */
    uint8 Resvered2      :4;      /**< Reserved bits */
    uint8 Resvered3      :8;      /**< Reserved byte 3 - not used */
  } DTC_Block;
} CoreIso_DtcFlagType;
 
/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
 
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/** @cond INTERNAL */
# define COREISO_START_SEC_CODE
# include "CoreIso_MemMap.h"
 
/**********************************************************************************************************************
 *  CoreIso_Init()
 *********************************************************************************************************************/
/*! \brief         Init for core isolation feauture
 *  \details       This function initilize PPU Slave -> SMPU Main -> PC -> SMPU Slave/Master Region -> PPU Master
 *  \param         -
 *  \return        -
 *  \pre           -
 *  \context       -
 *  \reentrant     -
 *  \synchronous   -
 *********************************************************************************************************************/
extern FUNC(void, AUTOMATIC) CoreIso_Init(void);
 
# define COREISO_STOP_SEC_CODE
# include "CoreIso_MemMap.h"
/** @endcond */
#endif /* COREISO_H */
 
/**********************************************************************************************************************
 *  END OF FILE: CoreIso.h
 *********************************************************************************************************************/
