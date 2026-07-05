/**
 * @file      CoreIso_ConfigData.c
 * @brief     Public header: CoreIso_ConfigData.h
 * @details   Overview: Contains configuration data for the Core Isolation module, including protection settings for bus masters and peripheral protection units (PPUs).
 */
 
 
/******************************************************************************************************
 * COPYRIGHT
 * -------------------------------------------------------------------------------------------------------------------
 *
 *
 * -------------------------------------------------------------------------------------------------------------------
 * LICENSE
 * -------------------------------------------------------------------------------------------------------------------
 *
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: CoreIso_ConfigData.c
 *   Generation Time: Monday, 19 May 2025 21:05:48
 *           Project: Security
 *          Delivery:
 *      Tool Version: 1.5.3
 *
 *
 *********************************************************************************************************************/
 
 
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "CoreIso_ConfigData.h"
 
 
 
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
 
 
/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
 
 
/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
 
 
/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA PROTOTYPES
**********************************************************************************************************************/
 
 
 
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
 
# define COREISO_START_SEC_CONST
# include "CoreIso_MemMap.h"
 
/******************************************************************************************************
  CoreIso_PcControlConfig
******************************************************************************************************/
/**
  * @type    CoreIso_PcControlCfgType[]
  * @var     CoreIso_PcControlConfig
  * @brief   Configuration array for bus master control settings, including ID, privilege, security, and protection context.
  * @unit    -
  * @scope   Global Variable
  * @section -
  * @par     Initial setting
  * |RAM0   |RAM1   |RAM2   |RAM3   |RAM4   | 
  * |:-----:|:-----:|:-----:|:-----:|:-----:|
  * |-      |-      |-      |-      |-      |
*/
CONST(CoreIso_PcControlCfgType, AUTOMATIC) CoreIso_PcControlConfig[COREISO_NR_OF_MASTER] = {
    /* Index          busMasterId                   prviSetting             secureSetting  protContext */
  { /*     0 */   CPUSS_MS_ID_CM0, (bool)COREISO_PRIVILEGE_MODE,     (bool)COREISO_SECURE, CY_PROT_PC5 },
  { /*     1 */ CPUSS_MS_ID_SLOW0, (bool)COREISO_PRIVILEGE_MODE, (bool)COREISO_NON_SECURE, CY_PROT_PC2 },
  { /*     2 */ CPUSS_MS_ID_FAST0, (bool)COREISO_PRIVILEGE_MODE, (bool)COREISO_NON_SECURE, CY_PROT_PC3 },
  { /*     3 */ CPUSS_MS_ID_FAST1, (bool)COREISO_PRIVILEGE_MODE, (bool)COREISO_NON_SECURE, CY_PROT_PC4 },
  { /*     4 */ CPUSS_MS_ID_CM7_1, (bool)COREISO_PRIVILEGE_MODE, (bool)COREISO_NON_SECURE, CY_PROT_PC7 },
  { /*     5 */ CPUSS_MS_ID_CM7_0, (bool)COREISO_PRIVILEGE_MODE, (bool)COREISO_NON_SECURE, CY_PROT_PC6 },
  { /*     6 */    CPUSS_MS_ID_TC, (bool)COREISO_PRIVILEGE_MODE,     (bool)COREISO_SECURE, CY_PROT_PC2 },
};
 
/**********************************************************************************************************************
  CoreIso_PPUSlaveProtAttrDefault
******************************************************************************************************/
/**
  * @type    CoreIso_PPUProtConfigType[]
  * @var     CoreIso_PPUSlaveProtAttrDefault
  * @brief   Default protection attributes for PPU slaves, defining user/privileged permissions and security levels for each protection context.
  * @unit    -
  * @scope   Global Variable
  * @section -
  * @par     Initial setting
  * |RAM0   |RAM1   |RAM2   |RAM3   |RAM4   |
  * |:-----:|:-----:|:-----:|:-----:|:-----:|
  * |-      |-      |-      |-      |-      |
*/
CONST(CoreIso_PPUProtConfigType, AUTOMATIC) CoreIso_PPUSlaveProtAttrDefault[COREISO_PROT_PC_NR] = {
    /* Index    ProtContext      Attribute.userPermission    Attribute.privPermission        Attribute.secure  */
  { /*     0 */ CY_PROT_PC1, {            CY_PROT_PERM_RW,            CY_PROT_PERM_RW,     COREISO_NON_SECURE } },
  { /*     1 */ CY_PROT_PC2, {            CY_PROT_PERM_RW,            CY_PROT_PERM_RW,         COREISO_SECURE } },
  { /*     2 */ CY_PROT_PC3, {      CY_PROT_PERM_DISABLED,      CY_PROT_PERM_DISABLED,         COREISO_SECURE } },
  { /*     3 */ CY_PROT_PC4, {      CY_PROT_PERM_DISABLED,      CY_PROT_PERM_DISABLED,         COREISO_SECURE } },
  { /*     4 */ CY_PROT_PC5, {            CY_PROT_PERM_RW,            CY_PROT_PERM_RW,         COREISO_SECURE } },
  { /*     5 */ CY_PROT_PC6, {            CY_PROT_PERM_RW,            CY_PROT_PERM_RW,     COREISO_NON_SECURE } },
  { /*     6 */ CY_PROT_PC7, {            CY_PROT_PERM_RW,            CY_PROT_PERM_RW,     COREISO_NON_SECURE } },
};
 
/******************************************************************************************************
  CoreIso_PPUMasterProtAttrDefault
******************************************************************************************************/
/**
  * @type    CoreIso_PPUProtConfigType[]
  * @var     CoreIso_PPUMasterProtAttrDefault
  * @brief   Default protection attributes for PPU masters, defining user/privileged permissions and security levels for each protection context.
  * @unit    -
  * @scope   Global Variable
  * @section -
  * @par     Initial setting
  * |RAM0   |RAM1   |RAM2   |RAM3   |RAM4   |
  * |:-----:|:-----:|:-----:|:-----:|:-----:|
  * |-      |-      |-      |-      |-      |
*/
CONST(CoreIso_PPUProtConfigType, AUTOMATIC) CoreIso_PPUMasterProtAttrDefault[COREISO_PROT_PC_NR] = {
    /* Index    ProtContext      Attribute.userPermission    Attribute.privPermission        Attribute.secure  */
  { /*     0 */ CY_PROT_PC1, {            CY_PROT_PERM_RW,            CY_PROT_PERM_RW,     COREISO_NON_SECURE } },
  { /*     1 */ CY_PROT_PC2, {             CY_PROT_PERM_R,             CY_PROT_PERM_R,         COREISO_SECURE } },
  { /*     2 */ CY_PROT_PC3, {             CY_PROT_PERM_R,             CY_PROT_PERM_R,         COREISO_SECURE } },
  { /*     3 */ CY_PROT_PC4, {             CY_PROT_PERM_R,             CY_PROT_PERM_R,         COREISO_SECURE } },
  { /*     4 */ CY_PROT_PC5, {            CY_PROT_PERM_RW,            CY_PROT_PERM_RW,         COREISO_SECURE } },
  { /*     5 */ CY_PROT_PC6, {             CY_PROT_PERM_R,             CY_PROT_PERM_R,         COREISO_SECURE } },
  { /*     6 */ CY_PROT_PC7, {             CY_PROT_PERM_R,             CY_PROT_PERM_R,         COREISO_SECURE } },
};
 
#if (COREISO_NR_OF_PPU_SLAVE_CONFIG > 0u)
/******************************************************************************************************
  CoreIso_PPUSlaveProtConfig
******************************************************************************************************/
/**
  * @type    CoreIso_PPUProtConfigType[]
  * @var     CoreIso_PPUSlaveProtConfig
  * @brief   Array holding specific protection context configurations for PPU slaves. Each entry defines permissions and security for a given context.
  * @unit    -
  * @scope   Local Variable
  * @section CONST
  * @par     Initial setting
  * |RAM0   |RAM1   |RAM2   |RAM3   |RAM4   |
  * |:-----:|:-----:|:-----:|:-----:|:-----:|
  * |-      |-      |-      |-      |-      |
*/
static CONST(CoreIso_PPUProtConfigType, AUTOMATIC) CoreIso_PPUSlaveProtConfig[COREISO_NR_OF_PPU_SLAVE_CONFIG] = {
    /* Index               ProtContext    Attribute.userPermission  Attribute.privPermission        Attribute.secure  */
  { /*     0 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PERI_SECURE */
  { /*     1 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PERI_SECURE */
  { /*     2 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PERI_GR1_GROUP */
  { /*     3 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PERI_GR1_GROUP */
  { /*     4 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PERI_GR1_BOOT */
  { /*     5 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PERI_GR1_BOOT */
  { /*     6 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PERI_MS_BOOT */
  { /*     7 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PERI_MS_BOOT */
  { /*     8 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_CRYPTO_MAIN */
  { /*     9 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_CRYPTO_MAIN */
  { /*    10 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_CRYPTO_CRYPTO */
  { /*    11 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_CRYPTO_CRYPTO */
  { /*    12 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_CRYPTO_KEY0 */
  { /*    13 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_CRYPTO_KEY0 */
  { /*    14 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_CRYPTO_KEY1 */
  { /*    15 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_CRYPTO_KEY1 */
  { /*    16 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_CRYPTO_BUF */
  { /*    17 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_CRYPTO_BUF */
  { /*    18 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_CPUSS_CM0_INT */
  { /*    19 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_CPUSS_CM0_INT */
  { /*    20 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_CPUSS_CM7_0_INT */
  { /*    21 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_CPUSS_CM7_1_INT */
  { /*    22 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_IPC_INTR_STRUCT6_INTR */
  { /*    23 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_IPC_INTR_STRUCT6_INTR */
  { /*    24 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PROT_SMPU_MAIN */
  { /*    25 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PROT_SMPU_MAIN */
  { /*    26 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PROT_MPU0_MAIN */
  { /*    27 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PROT_MPU0_MAIN */
  { /*    28 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PROT_MPU5_MAIN */
  { /*    29 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PROT_MPU5_MAIN */
  { /*    30 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PROT_MPU9_MAIN */
  { /*    31 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PROT_MPU9_MAIN */
  { /*    32 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PROT_MPU10_MAIN */
  { /*    33 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PROT_MPU10_MAIN */
  { /*    34 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PROT_MPU13_MAIN */
  { /*    35 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PROT_MPU13_MAIN */
  { /*    36 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PROT_MPU14_MAIN */
  { /*    37 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PROT_MPU14_MAIN */
  { /*    38 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PROT_MPU15_MAIN */
  { /*    39 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PROT_MPU15_MAIN */
  { /*    40 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_FLASHC_CM7_0 */
  { /*    41 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_FLASHC_CM7_1 */
  { /*    42 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_FLASHC_CRYPTO */
  { /*    43 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_FLASHC_CRYPTO */
  { /*    44 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_TCPWM1_GRP0_CNT11_CNT */
  { /*    45 */        COREISO_PC_CM0P, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_TCPWM1_GRP0_CNT11_CNT */
  { /*    46 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_TCPWM1_GRP0_CNT13_CNT */
  { /*    47 */        COREISO_PC_CM0P, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_TCPWM1_GRP0_CNT13_CNT */
  { /*    48 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_TCPWM1_GRP0_CNT56_CNT */
  { /*    49 */        COREISO_PC_CM0P, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_TCPWM1_GRP0_CNT56_CNT */
  { /*    50 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_TCPWM1_GRP0_CNT59_CNT */
  { /*    51 */        COREISO_PC_CM0P, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_TCPWM1_GRP0_CNT59_CNT */
  { /*    52 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_TCPWM1_GRP0_CNT60_CNT */
  { /*    53 */        COREISO_PC_CM0P, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_TCPWM1_GRP0_CNT60_CNT */
  { /*    54 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_LIN0_CH14_CH */
  { /*    55 */        COREISO_PC_CM0P, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_LIN0_CH14_CH */
  { /*    56 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_CANFD1_CH2_CH */
  { /*    57 */        COREISO_PC_CM0P, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_CANFD1_CH2_CH */
  { /*    58 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_SCB2 */
  { /*    59 */        COREISO_PC_CM0P, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_SCB2 */
  { /*    60 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_SCB4 */
  { /*    61 */        COREISO_PC_CM0P, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_SCB4 */
  { /*    62 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_SCB5 */
  { /*    63 */        COREISO_PC_CM0P, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_SCB5 */
  { /*    64 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_SCB7 */
  { /*    65 */        COREISO_PC_CM0P, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_SCB7 */
  { /*    66 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_SCB9 */
  { /*    67 */        COREISO_PC_CM0P, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_SCB9 */
  { /*    68 */        COREISO_PC_CM71, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_SCB10 */
  { /*    69 */        COREISO_PC_CM0P, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_SCB10 */
  { /*    70 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH7_CH */
  { /*    71 */        COREISO_PC_CM0P, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH7_CH */
  { /*    72 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH11_CH */
  { /*    73 */        COREISO_PC_CM0P, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH11_CH */
  { /*    74 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH14_CH */
  { /*    75 */        COREISO_PC_CM0P, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH14_CH */
  { /*    76 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH16_CH */
  { /*    77 */        COREISO_PC_CM0P, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH16_CH */
  { /*    78 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH18_CH */
  { /*    79 */        COREISO_PC_CM0P, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH18_CH */
  { /*    80 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH20_CH */
  { /*    81 */        COREISO_PC_CM0P, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH20_CH */
  { /*    82 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH25_CH */
  { /*    83 */        COREISO_PC_CM0P, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH25_CH */
  { /*    84 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH26_CH */
  { /*    85 */        COREISO_PC_CM0P, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH26_CH */
  { /*    86 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH27_CH */
  { /*    87 */        COREISO_PC_CM0P, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH27_CH */
  { /*    88 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH28_CH */
  { /*    89 */        COREISO_PC_CM0P, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH28_CH */
  { /*    90 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH29_CH */
  { /*    91 */        COREISO_PC_CM0P, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH29_CH */
  { /*    92 */        COREISO_PC_CM70, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH30_CH */
  { /*    93 */        COREISO_PC_CM0P, {    CY_PROT_PERM_DISABLED,    CY_PROT_PERM_DISABLED,         COREISO_SECURE } }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH30_CH */
};
#endif /* (COREISO_NR_OF_PPU_SLAVE_CONFIG > 0u) */
 
 
#if (COREISO_NR_OF_PPU_MASTER_CONFIG > 0u)
/******************************************************************************************************
  CoreIso_PPUMasterProtConfig
******************************************************************************************************/
/**
  * @type    CoreIso_PPUProtConfigType[]
  * @var     CoreIso_PPUMasterProtConfig
  * @brief   Array holding specific protection context configurations for PPU masters. Each entry defines permissions and security for a given context.
  * @unit    -
  * @scope   Global Variable
  * @section CONST
  * @par     Initial setting
  * |RAM0   |RAM1   |RAM2   |RAM3   |RAM4   |
  * |:-----:|:-----:|:-----:|:-----:|:-----:|
  * |-      |-      |-      |-      |-      |
*/
CONST(CoreIso_PPUProtConfigType, AUTOMATIC) CoreIso_PPUMasterProtConfig[COREISO_NR_OF_PPU_MASTER_CONFIG] = {
    /* Index               ProtContext    Attribute.userPermission  Attribute.privPermission        Attribute.secure  */
};
#endif /* (COREISO_NR_OF_PPU_MASTER_CONFIG > 0u) */
 
/******************************************************************************************************
  CoreIso_PPUFxConfig
******************************************************************************************************/
/**
  * @type    CoreIso_PPUFxConfigType[]
  * @var     CoreIso_PPUFxConfig
  * @brief   Configuration array for Fixed Peripheral Protection Units (PPUFx), linking slave and master protection settings to specific peripheral structures.
  * @unit    -
  * @scope   Global Variable
  * @section CONST
  * @par     Initial setting
  * |RAM0   |RAM1   |RAM2   |RAM3   |RAM4   |
  * |:-----:|:-----:|:-----:|:-----:|:-----:|
  * |-      |-      |-      |-      |-      |
*/
CONST(CoreIso_PPUFxConfigType, AUTOMATIC) CoreIso_PPUFxConfig[COREISO_NR_OF_PPU_CONFIGURED] = {
    /* Index    ProtSlaveConfig  ProtMasterConfig   PPUFxStruct                     ProtSlaveConfig                    ProtMasterConfig */
  { /*     0 */              2u,               0u,           1u,    &CoreIso_PPUSlaveProtConfig[0u],                           NULL_PTR }, /* PERI_MS_PPU_FX_PERI_SECURE */
  { /*     1 */              2u,               0u,           3u,    &CoreIso_PPUSlaveProtConfig[2u],                           NULL_PTR }, /* PERI_MS_PPU_FX_PERI_GR1_GROUP */
  { /*     2 */              2u,               0u,          12u,    &CoreIso_PPUSlaveProtConfig[4u],                           NULL_PTR }, /* PERI_MS_PPU_FX_PERI_GR1_BOOT */
  { /*     3 */              2u,               0u,          21u,    &CoreIso_PPUSlaveProtConfig[6u],                           NULL_PTR }, /* PERI_MS_PPU_FX_PERI_MS_BOOT */
  { /*     4 */              2u,               0u,          23u,    &CoreIso_PPUSlaveProtConfig[8u],                           NULL_PTR }, /* PERI_MS_PPU_FX_CRYPTO_MAIN */
  { /*     5 */              2u,               0u,          24u,   &CoreIso_PPUSlaveProtConfig[10u],                           NULL_PTR }, /* PERI_MS_PPU_FX_CRYPTO_CRYPTO */
  { /*     6 */              2u,               0u,          26u,   &CoreIso_PPUSlaveProtConfig[12u],                           NULL_PTR }, /* PERI_MS_PPU_FX_CRYPTO_KEY0 */
  { /*     7 */              2u,               0u,          27u,   &CoreIso_PPUSlaveProtConfig[14u],                           NULL_PTR }, /* PERI_MS_PPU_FX_CRYPTO_KEY1 */
  { /*     8 */              2u,               0u,          28u,   &CoreIso_PPUSlaveProtConfig[16u],                           NULL_PTR }, /* PERI_MS_PPU_FX_CRYPTO_BUF */
  { /*     9 */              2u,               0u,          33u,   &CoreIso_PPUSlaveProtConfig[18u],                           NULL_PTR }, /* PERI_MS_PPU_FX_CPUSS_CM0_INT */
  { /*    10 */              1u,               0u,          34u,   &CoreIso_PPUSlaveProtConfig[20u],                           NULL_PTR }, /* PERI_MS_PPU_FX_CPUSS_CM7_0_INT */
  { /*    11 */              1u,               0u,          35u,   &CoreIso_PPUSlaveProtConfig[21u],                           NULL_PTR }, /* PERI_MS_PPU_FX_CPUSS_CM7_1_INT */
  { /*    12 */              2u,               0u,          54u,   &CoreIso_PPUSlaveProtConfig[22u],                           NULL_PTR }, /* PERI_MS_PPU_FX_IPC_INTR_STRUCT6_INTR */
  { /*    13 */              2u,               0u,          56u,   &CoreIso_PPUSlaveProtConfig[24u],                           NULL_PTR }, /* PERI_MS_PPU_FX_PROT_SMPU_MAIN */
  { /*    14 */              2u,               0u,          57u,   &CoreIso_PPUSlaveProtConfig[26u],                           NULL_PTR }, /* PERI_MS_PPU_FX_PROT_MPU0_MAIN */
  { /*    15 */              2u,               0u,          58u,   &CoreIso_PPUSlaveProtConfig[28u],                           NULL_PTR }, /* PERI_MS_PPU_FX_PROT_MPU5_MAIN */
  { /*    16 */              2u,               0u,          59u,   &CoreIso_PPUSlaveProtConfig[30u],                           NULL_PTR }, /* PERI_MS_PPU_FX_PROT_MPU9_MAIN */
  { /*    17 */              2u,               0u,          60u,   &CoreIso_PPUSlaveProtConfig[32u],                           NULL_PTR }, /* PERI_MS_PPU_FX_PROT_MPU10_MAIN */
  { /*    18 */              2u,               0u,          61u,   &CoreIso_PPUSlaveProtConfig[34u],                           NULL_PTR }, /* PERI_MS_PPU_FX_PROT_MPU13_MAIN */
  { /*    19 */              2u,               0u,          62u,   &CoreIso_PPUSlaveProtConfig[36u],                           NULL_PTR }, /* PERI_MS_PPU_FX_PROT_MPU14_MAIN */
  { /*    20 */              2u,               0u,          63u,   &CoreIso_PPUSlaveProtConfig[38u],                           NULL_PTR }, /* PERI_MS_PPU_FX_PROT_MPU15_MAIN */
  { /*    21 */              1u,               0u,          68u,   &CoreIso_PPUSlaveProtConfig[40u],                           NULL_PTR }, /* PERI_MS_PPU_FX_FLASHC_CM7_0 */
  { /*    22 */              1u,               0u,          69u,   &CoreIso_PPUSlaveProtConfig[41u],                           NULL_PTR }, /* PERI_MS_PPU_FX_FLASHC_CM7_1 */
  { /*    23 */              2u,               0u,          70u,   &CoreIso_PPUSlaveProtConfig[42u],                           NULL_PTR }, /* PERI_MS_PPU_FX_FLASHC_CRYPTO */
  { /*    24 */              2u,               0u,         449u,   &CoreIso_PPUSlaveProtConfig[44u],                           NULL_PTR }, /* PERI_MS_PPU_FX_TCPWM1_GRP0_CNT11_CNT */
  { /*    25 */              2u,               0u,         451u,   &CoreIso_PPUSlaveProtConfig[46u],                           NULL_PTR }, /* PERI_MS_PPU_FX_TCPWM1_GRP0_CNT13_CNT */
  { /*    26 */              2u,               0u,         494u,   &CoreIso_PPUSlaveProtConfig[48u],                           NULL_PTR }, /* PERI_MS_PPU_FX_TCPWM1_GRP0_CNT56_CNT */
  { /*    27 */              2u,               0u,         497u,   &CoreIso_PPUSlaveProtConfig[50u],                           NULL_PTR }, /* PERI_MS_PPU_FX_TCPWM1_GRP0_CNT59_CNT */
  { /*    28 */              2u,               0u,         498u,   &CoreIso_PPUSlaveProtConfig[52u],                           NULL_PTR }, /* PERI_MS_PPU_FX_TCPWM1_GRP0_CNT60_CNT */
  { /*    29 */              2u,               0u,         567u,   &CoreIso_PPUSlaveProtConfig[54u],                           NULL_PTR }, /* PERI_MS_PPU_FX_LIN0_CH14_CH */
  { /*    30 */              2u,               0u,         580u,   &CoreIso_PPUSlaveProtConfig[56u],                           NULL_PTR }, /* PERI_MS_PPU_FX_CANFD1_CH2_CH */
  { /*    31 */              2u,               0u,         590u,   &CoreIso_PPUSlaveProtConfig[58u],                           NULL_PTR }, /* PERI_MS_PPU_FX_SCB2 */
  { /*    32 */              2u,               0u,         592u,   &CoreIso_PPUSlaveProtConfig[60u],                           NULL_PTR }, /* PERI_MS_PPU_FX_SCB4 */
  { /*    33 */              2u,               0u,         593u,   &CoreIso_PPUSlaveProtConfig[62u],                           NULL_PTR }, /* PERI_MS_PPU_FX_SCB5 */
  { /*    34 */              2u,               0u,         595u,   &CoreIso_PPUSlaveProtConfig[64u],                           NULL_PTR }, /* PERI_MS_PPU_FX_SCB7 */
  { /*    35 */              2u,               0u,         597u,   &CoreIso_PPUSlaveProtConfig[66u],                           NULL_PTR }, /* PERI_MS_PPU_FX_SCB9 */
  { /*    36 */              2u,               0u,         598u,   &CoreIso_PPUSlaveProtConfig[68u],                           NULL_PTR }, /* PERI_MS_PPU_FX_SCB10 */
  { /*    37 */              2u,               0u,         612u,   &CoreIso_PPUSlaveProtConfig[70u],                           NULL_PTR }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH7_CH */
  { /*    38 */              2u,               0u,         616u,   &CoreIso_PPUSlaveProtConfig[72u],                           NULL_PTR }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH11_CH */
  { /*    39 */              2u,               0u,         619u,   &CoreIso_PPUSlaveProtConfig[74u],                           NULL_PTR }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH14_CH */
  { /*    40 */              2u,               0u,         621u,   &CoreIso_PPUSlaveProtConfig[76u],                           NULL_PTR }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH16_CH */
  { /*    41 */              2u,               0u,         623u,   &CoreIso_PPUSlaveProtConfig[78u],                           NULL_PTR }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH18_CH */
  { /*    42 */              2u,               0u,         625u,   &CoreIso_PPUSlaveProtConfig[80u],                           NULL_PTR }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH20_CH */
  { /*    43 */              2u,               0u,         630u,   &CoreIso_PPUSlaveProtConfig[82u],                           NULL_PTR }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH25_CH */
  { /*    44 */              2u,               0u,         631u,   &CoreIso_PPUSlaveProtConfig[84u],                           NULL_PTR }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH26_CH */
  { /*    45 */              2u,               0u,         632u,   &CoreIso_PPUSlaveProtConfig[86u],                           NULL_PTR }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH27_CH */
  { /*    46 */              2u,               0u,         633u,   &CoreIso_PPUSlaveProtConfig[88u],                           NULL_PTR }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH28_CH */
  { /*    47 */              2u,               0u,         634u,   &CoreIso_PPUSlaveProtConfig[90u],                           NULL_PTR }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH29_CH */
  { /*    48 */              2u,               0u,         635u,   &CoreIso_PPUSlaveProtConfig[92u],                           NULL_PTR }, /* PERI_MS_PPU_FX_PASS0_SAR0_CH30_CH */
};
 
# define COREISO_STOP_SEC_CONST
# include "CoreIso_MemMap.h"

 
/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
 
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
 
 
/**********************************************************************************************************************
 *  END OF FILE: CoreIso_ConfigData.c
 *********************************************************************************************************************/
 
 