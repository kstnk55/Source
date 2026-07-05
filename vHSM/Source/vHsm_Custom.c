/**
* @file  vHsm_Custom.c
* @brief  Public header: vHsm_Custom.h
* @details Overview: Implements the the custom crypto driver for the vHSM module. This includes handling of custom commands, key management, and cryptographic operations specific to the target hardware.
*/

 /**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#define VHSM_CUSTOM_SOURCE
 
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vHsm.h"
#include "Csm_Cfg.h"
#include "vHsm_KeyM.h"
#include "Crypto_30_LibCv.h"

#include "vHsm_Custom.h"

#include "Crypto_30_LibCv_Services.h"
#include "Crypto_30_LibCv_Curve.h"
#include "Crypto_30_LibCv_RandomSeed.h"
#include "Crypto_30_LibCv_KeyExchange.h"
#include "Crypto_30_LibCv_KeyGenerate.h"
#include "Crypto_30_LibCv_KeyDerive.h"
#include "Crypto_30_LibCv_KeySetValid.h"
#include "Crypto_30_LibCv_InternalApi.h"
#include "vHsm_Nvm.h"
#include "DualBank_Manager_FblTransition.h"
#include "vHsm_Callout_Stubs.h"
#include "cy_srom.h"
#include "SecureBootUtil.h"
#include "Crypto_30_LibCv_Cfg.h"
#include "Csm.h"
#include "Csm_Cfg.h"
#include "cy_sysclk.h"
#include "cy_project.h"
#include "cy_device_headers.h"
/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* vendor specific version information is BCD coded */
#if (  (VHSM_CUSTOM_SW_MAJOR_VERSION != (0x01U)) \
    || (VHSM_CUSTOM_SW_MINOR_VERSION != (0x01U)) \
    || (VHSM_CUSTOM_SW_PATCH_VERSION != (0x00U)) )
# error "Vendor specific version numbers of vHsm_Custom.c and vHsm_Custom.h are inconsistent"
#endif

/**********************************************************************************************************************
 * LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

#if !defined (VHSM_CUSTOM_LOCAL) /* COV_VHSM_CUSTOM_LOCAL_DEFINE */
/**
 * @def      VHSM_CUSTOM_LOCAL
 * @value    static
 * @resolution -
 * @brief    Defines the scope of local functions as static if not already defined.
 */
# define VHSM_CUSTOM_LOCAL static
#endif

#if !defined (VHSM_CUSTOM_LOCAL_INLINE) /* COV_VHSM_CUSTOM_LOCAL_DEFINE */
/**
 * @def      VHSM_CUSTOM_LOCAL_INLINE
 * @value    LOCAL_INLINE
 * @resolution -
 * @brief    Defines the scope of local inline functions if not already defined.
 */
# define VHSM_CUSTOM_LOCAL_INLINE LOCAL_INLINE
#endif

/**
 * @def      VHSM_CUSTOM_ZERO
 * @value    0u
 * @resolution -
 * @brief    Represents the integer value zero, used for initializations and comparisons.
 */
#define VHSM_CUSTOM_ZERO                                              (0u)
/**
 * @def      VHSM_CUSTOM_ONE
 * @value    1u
 * @resolution -
 * @brief    Represents the integer value one.
 */
#define VHSM_CUSTOM_ONE                                               (1u)
/**
 * @def      VHSM_CUSTOM_TEN
 * @value    10u
 * @resolution -
 * @brief    Represents the integer value ten, often used as an array size.
 */
#define VHSM_CUSTOM_TEN                                               (10u)
/**
 * @def      VHSM_CUSTOM_FOUR
 * @value    4ul
 * @resolution -
 * @brief    Represents the integer value four, used for array sizes or loop counts.
 */
#define VHSM_CUSTOM_FOUR                                              (4UL)
/**
 * @def      VHSM_CUSTOM_BUFFER_SIZE_32BYTE
 * @value    32u
 * @resolution -
 * @brief    Defines a buffer size of 32 bytes for cryptographic operations.
 */
#define VHSM_CUSTOM_BUFFER_SIZE_32BYTE                                (32u)
/**
 * @def      VHSM_CUSTOM_BUFFER_SIZE_16BYTE
 * @value    16u
 * @resolution -
 * @brief    Defines a buffer size of 16 bytes, typically for AES blocks.
 */
#define VHSM_CUSTOM_BUFFER_SIZE_16BYTE                                (16u)


/**
 * @def      VHSM_CUSTOM_BUFFER_SIZE
 * @value    16u
 * @resolution -
 * @brief    General purpose buffer size of 16 bytes.
 */
#define VHSM_CUSTOM_BUFFER_SIZE                                       (16u)
/**
 * @def      VHSM_CUSTOM_KEY_SIZE
 * @value    16u
 * @resolution -
 * @brief    Defines the standard key size of 16 bytes (128 bits).
 */
#define VHSM_CUSTOM_KEY_SIZE                                          (16u)
/**
 * @def      VHSM_CUSTOM_HSMSTATUSREGISTER_SIZE
 * @value    1u
 * @resolution -
 * @brief    Size in bytes of the HSM status register.
 */
#define VHSM_CUSTOM_HSMSTATUSREGISTER_SIZE                            (1u) /* Size of the HsmStatusRegister */
/**
 * @def      VHSM_CUSTOM_KEY_ATTR
 * @value    10u
 * @resolution -
 * @brief    A constant related to key attributes.
 */
#define VHSM_CUSTOM_KEY_ATTR                                          (10u)
/**
 * @def      VHSM_CUSTOM_CMD_GET_ID_BUFFER_SIZE
 * @value    32u
 * @resolution -
 * @brief    Buffer size for the 'Get ID' command response.
 */
#define VHSM_CUSTOM_CMD_GET_ID_BUFFER_SIZE                            (32u)
/**
 * @def      VHSM_CUSTOM_UID_SIZE
 * @value    15u
 * @resolution -
 * @brief    Size in bytes of the Unique ID (UID).
 */
#define VHSM_CUSTOM_UID_SIZE                                          (15u)
/**
 * @def      VHSM_CUSTOM_SREG_INIT_MASk
 * @value    0x80
 * @resolution -
 * @brief    Mask to check the initialization status in the status register.
 */
#define VHSM_CUSTOM_SREG_INIT_MASk                                    (0x80)
/**
 * @def      VHSM_CUSTOM_ONE_BYTE
 * @value    8u
 * @resolution -
 * @brief    Number of bits in one byte.
 */
#define VHSM_CUSTOM_ONE_BYTE                                          (8u)
/**
 * @def      VHSM_CUSTOM_DEFAULT_KEY_ELEMENT_ID
 * @value    1u
 * @resolution -
 * @brief    Default identifier for a key element.
 */
#define VHSM_CUSTOM_DEFAULT_KEY_ELEMENT_ID                            (1u)

/**
 * @def      VHSM_CUSTOM_KEYATTR_WP_MASK
 * @value    0x80
 * @resolution -
 * @brief    Mask for the Write Protection attribute of a key.
 */
#define VHSM_CUSTOM_KEYATTR_WP_MASK                                   (0x80)
/**
 * @def      VHSM_CUSTOM_KEYATTR_BP_MASK
 * @value    0x10
 * @resolution -
 * @brief    Mask for the Boot Protection attribute of a key.
 */
#define VHSM_CUSTOM_KEYATTR_BP_MASK                                   (0x10)
/**
 * @def      VHSM_CUSTOM_KEYATTR_DP_MASK
 * @value    0x08
 * @resolution -
 * @brief    Mask for the Debugger Protection attribute of a key.
 */
#define VHSM_CUSTOM_KEYATTR_DP_MASK                                   (0x08)
/**
 * @def      VHSM_CUSTOM_KEYATTR_KU_MASK
 * @value    0x40
 * @resolution -
 * @brief    Mask for the Key Usage attribute.
 */
#define VHSM_CUSTOM_KEYATTR_KU_MASK                                   (0x40)
/**
 * @def      VHSM_CUSTOM_KEYATTR_CU_MASK
 * @value    0x20
 * @resolution -
 * @brief    Mask for a custom usage attribute of a key.
 */
#define VHSM_CUSTOM_KEYATTR_CU_MASK                                   (0x20)
/**
 * @def      CLK_FREQ_IMO
 * @value    8000000ul
 * @resolution -
 * @brief    Frequency of the Internal Main Oscillator (IMO) in Hz.
 */
#define CLK_FREQ_IMO                                                  (8000000U)
/**
 * @def      CLK_FREQ_ECO
 * @value    16000000ul
 * @resolution -
 * @brief    Frequency of the External Crystal Oscillator (ECO) in Hz.
 */
#define CLK_FREQ_ECO                                                  (16000000UL)
/**
 * @def      FLL_TARGET_FREQ
 * @value    100000000ul
 * @resolution -
 * @brief    Target frequency for the Frequency Locked Loop (FLL) in Hz.
 */
#define FLL_TARGET_FREQ                                               (100000000U)
/**
 * @def      PLL_TARGET_FREQ
 * @value    160000000ul
 * @resolution -
 * @brief    Target frequency for the Phase Locked Loop (PLL) in Hz.
 */
#define PLL_TARGET_FREQ                                               (160000000UL)
/**
 * @def      WAIT_FOR_STABILIZATION
 * @value    10000ul
 * @resolution -
 * @brief    Wait time for clock stabilization, typically in loop counts or microseconds.
 */
#define WAIT_FOR_STABILIZATION                                        (10000U)
/**
 * @def      CY_SROM_OP_TRANSITION_TO_SECURE
 * @value    0x2FUL
 * @resolution -
 * @brief    SROM API opcode for transitioning the device to the SECURE lifecycle stage.
 */
#define CY_SROM_OP_TRANSITION_TO_SECURE (0x2FUL)
/**
 * @def      NOTIFY_ACKED
 * @value    0x00U
 * @resolution -
 * @brief    Status indicating that a notification has been acknowledged.
 */
#define NOTIFY_ACKED (0x00U)
/**
 * @def      APPL_NOTIFIED
 * @value    0x01U
 * @resolution -
 * @brief    Status indicating that the application has been notified.
 */
#define APPL_NOTIFIED (0x01U)
/**
 * @def      VP_SECBOOT_FAILED
 * @value    0x01U
 * @resolution -
 * @brief    Status code indicating that the secure boot for the VP (Vision Processor) has failed.
 */
#define VP_SECBOOT_FAILED (0x01U)
/**
 * @def      VP_SECBOOT_PASSED
 * @value    0x02U
 * @resolution -
 * @brief    Status code indicating that the secure boot for the VP (Vision Processor) has passed.
 */
#define VP_SECBOOT_PASSED (0x02U)
/**
 * @def      SOUND_SECBOOT_FAILED
 * @value    0x03U
 * @resolution -
 * @brief    Status code indicating that the secure boot for the Sound processor has failed.
 */
#define SOUND_SECBOOT_FAILED (0x03U)
/**
 * @def      SOUND_SECBOOT_PASSED
 * @value    0x04U
 * @resolution -
 * @brief    Status code indicating that the secure boot for the Sound processor has passed.
 */
#define SOUND_SECBOOT_PASSED (0x04U)

/**
 * @def      VHSM_CUSTOM_KEYSIZE
 * @value    64u
 * @resolution -
 * @brief    Defines a key size of 64 bytes for specific cryptographic operations.
 */
#define VHSM_CUSTOM_KEYSIZE (64u)
/**
 * @def      VHSM_CUSTOM_INPUT_KEYSIZE
 * @value    65u
 * @resolution -
 * @brief    Defines an input key size of 65 bytes, possibly for uncompressed ECC public keys.
 */
#define VHSM_CUSTOM_INPUT_KEYSIZE (65u)

/**
 * @def      VHSM_CUSTOM_DEVICE_AUTHEN_KEY_LENGTH
 * @value    ((uint8)0x10U)
 * @resolution -
 * @brief    Length of the device authentication key (16 bytes).
 */
#define VHSM_CUSTOM_DEVICE_AUTHEN_KEY_LENGTH                          ((uint8)0x10U)
/**
 * @def      VHSM_CUSTOM_DEVICE_AUTHEN_KEY_LENGTH_BUFFER_SIZE
 * @value    32u
 * @resolution -
 * @brief    Buffer size for the device authentication key data.
 */
#define VHSM_CUSTOM_DEVICE_AUTHEN_KEY_LENGTH_BUFFER_SIZE              (32u)
/**
 * @def      VHSM_CUSTOM_DEVICE_AUTHEN_KEY_LENGTH_BUFFER_STATUS
 * @value    1u
 * @resolution -
 * @brief    Size of the status field in the device authentication buffer.
 */
#define VHSM_CUSTOM_DEVICE_AUTHEN_KEY_LENGTH_BUFFER_STATUS            (1u)
/**
 * @def      VHSM_CUSTOM_DEVICE_AUTHEN_KEY_LENGTH_BUFFER_TOTAL
 * @value    (VHSM_CUSTOM_DEVICE_AUTHEN_KEY_LENGTH_BUFFER_SIZE + VHSM_CUSTOM_DEVICE_AUTHEN_KEY_LENGTH_BUFFER_STATUS)
 * @resolution -
 * @brief    Total size of the device authentication buffer, including data and status.
 */
#define VHSM_CUSTOM_DEVICE_AUTHEN_KEY_LENGTH_BUFFER_TOTAL             (VHSM_CUSTOM_DEVICE_AUTHEN_KEY_LENGTH_BUFFER_SIZE + \
                                                                      VHSM_CUSTOM_DEVICE_AUTHEN_KEY_LENGTH_BUFFER_STATUS)

/**
 * @def      CY_SROM_OP_TRANSITION_RMA
 * @value    0x28000000u
 * @resolution -
 * @brief    SROM opcode for transitioning the device to the RMA (Return Material Authorization) lifecycle stage.
 */
#define CY_SROM_OP_TRANSITION_RMA (0x28000000u)
/**
 * @def      CY_SROM_OP_OPEN_RMA
 * @value    0x29000000u
 * @resolution -
 * @brief    SROM opcode to open the device for RMA procedures.
 */
#define CY_SROM_OP_OPEN_RMA (0x29000000u)
/**
 * @def      OBJECT_SIZE
 * @value    0x00000014u
 * @resolution -
 * @brief    Size of a specific data object used in SROM commands.
 */
#define OBJECT_SIZE (0x00000014u)
/**
 * @def      COMMND_ID_TRAN_TO_RMA
 * @value    0x120028F0u
 * @resolution -
 * @brief    Command ID for the transition to RMA SROM operation.
 */
#define COMMND_ID_TRAN_TO_RMA (0x120028F0u)
/**
 * @def      COMMND_ID_OPEN_RMA
 * @value    0x120029F0u
 * @resolution -
 * @brief    Command ID for the Open RMA SROM operation.
 */
#define COMMND_ID_OPEN_RMA (0x120029F0u)
/**
 * @def      UNIQUE_ID_0
 * @value    0x030dfe10ul
 * @resolution -
 * @brief    The first 32 bits of the device's unique ID. This value is chip-specific.
 */
#define UNIQUE_ID_0 (0x030dfe10UL) // Need to change per chip
/**
 * @def      UNIQUE_ID_1
 * @value    0xb1000a0aul
 * @resolution -
 * @brief    The second 32 bits of the device's unique ID. This value is chip-specific.
 */
#define UNIQUE_ID_1 (0xb1000a0aUL) // Need to change per chip
/**
 * @def      UNIQUE_ID_2
 * @value    0x00130902ul
 * @resolution -
 * @brief    The third 32 bits of the device's unique ID. This value is chip-specific.
 */
#define UNIQUE_ID_2 (0x00130902UL) // Need to change per chip
/**
 * @def      SIGNATURE_WORD_LENGTH
 * @value    64u
 * @resolution -
 * @brief    The length of the digital signature in 32-bit words.
 */
#define SIGNATURE_WORD_LENGTH (64u)
/**
 * @def      REQ_TYPE_LENGTH
 * @value    1u
 * @resolution -
 * @brief    The length in bytes of the request type field.
 */
#define REQ_TYPE_LENGTH   (1u)
/**
 * @def      RMA_RESULT_LENGTH
 * @value    1u
 * @resolution -
 * @brief    The length in bytes of the RMA result field.
 */
#define RMA_RESULT_LENGTH   (1u)

/**
 * @def      READ_STAGE
 * @value    0x05u
 * @resolution -
 * @brief    An identifier for a 'read stage' operation.
 */
#define READ_STAGE (0x05u)
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

/**
 * @def      TRANSITION_RMA_REQ
 * @value    0x01u
 * @resolution -
 * @brief    Request type identifier for transitioning to RMA state.
 */
#define TRANSITION_RMA_REQ (0x01u)
/**
 * @def      OPEN_RMA_REQ
 * @value    0x02u
 * @resolution -
 * @brief    Request type identifier for opening the RMA state.
 */
#define OPEN_RMA_REQ (0x02u)

/**
 * @def      TRANSITION_SECURE_REQ
 * @value    0x03u
 * @resolution -
 * @brief    Request type identifier for transitioning to SECURE state.
 */
#define TRANSITION_SECURE_REQ (0x03u)
/**
 * @def      TRANSITION_SECURE_W_DEBUG_REQ
 * @value    0x04u
 * @resolution -
 * @brief    Request type identifier for transitioning to SECURE state with debug enabled.
 */
#define TRANSITION_SECURE_W_DEBUG_REQ (0x04u)

/**
 * @def      OPCODE_TRANSITION_TO_SECURE
 * @value    0x2Fu
 * @resolution -
 * @brief    Opcode for the "Transition to Secure" SROM API call.
 */
#define OPCODE_TRANSITION_TO_SECURE (0x2Fu)
/**
 * @def      SECURE
 * @value    0x0u
 * @resolution -
 * @brief    Flag indicating the SECURE mode (without debug).
 */
#define SECURE (0x0u)
/**
 * @def      SECURE_WITH_DEBUG
 * @value    0x1u
 * @resolution -
 * @brief    Flag indicating the SECURE_WITH_DEBUG mode.
 */
#define SECURE_WITH_DEBUG (0x1u)
/**
 * @def      DEAD_ACC_RESTRICT
 * @value    0x0u
 * @resolution -
 * @brief    Default value for dead access restrictions.
 */
#define DEAD_ACC_RESTRICT (0x0u)
/**
 * @def      DEAD_WD_ACC_RESTRICT
 * @value    0x0u
 * @resolution -
 * @brief    Default value for dead with-debug access restrictions.
 */
#define DEAD_WD_ACC_RESTRICT (0x0u)


/**
 * @def      SIGNATURE_START_IDX
 * @value    0x01u
 * @resolution -
 * @brief    The starting index of the signature data within a request buffer.
 */
#define SIGNATURE_START_IDX (0x01u)
/**
 * @def      REQ_TYPE_IDX
 * @value    0x00u
 * @resolution -
 * @brief    The index of the request type field within a request buffer.
 */
#define REQ_TYPE_IDX (0x00u)
/**
 * @def      SILICON_ID_TYPE
 * @value    0x01u
 * @resolution -
 * @brief    Identifier for the silicon ID type.
 */
#define SILICON_ID_TYPE (0x01u)

/**
 * @def      UID_START_IDX
 * @value    4u
 * @resolution -
 * @brief    The starting index of the UID data.
 */
#define UID_START_IDX (4u)
/**
 * @def      UID_LEN
 * @value    11u
 * @resolution -
 * @brief    The length of the relevant portion of the UID.
 */
#define UID_LEN (11u)

/**
 * @def      MAC_KEY_NO_ERR
 * @value    0u
 * @resolution -
 * @brief    Status indicating no error with the MAC key.
 */
#define MAC_KEY_NO_ERR (0u)
/**
 * @def      MAC_KEY_INVALID
 * @value    1u
 * @resolution -
 * @brief    Status indicating the MAC key is invalid.
 */
#define MAC_KEY_INVALID (1u)

/**
 * @def      AP_CTL_M0_DISABLE_POS
 * @value    0U
 * @resolution -
 * @brief    Bit position for disabling Cortex-M0 access in the Access Restrictions register.
 */
#define AP_CTL_M0_DISABLE_POS      (0U)    // [1:0]
/**
 * @def      AP_CTL_M4_DISABLE_POS
 * @value    2U
 * @resolution -
 * @brief    Bit position for disabling Cortex-M4 access in the Access Restrictions register.
 */
#define AP_CTL_M4_DISABLE_POS      (2U)    // [3:2]
/**
 * @def      AP_CTL_SYS_DISABLE_POS
 * @value    4U
 * @resolution -
 * @brief    Bit position for disabling System peripheral access in the Access Restrictions register.
 */
#define AP_CTL_SYS_DISABLE_POS     (4U)    // [5:4]
/**
 * @def      SYS_AP_MPU_ENABLE_POS
 * @value    6U
 * @resolution -
 * @brief    Bit position for enabling the System Access Port MPU.
 */
#define SYS_AP_MPU_ENABLE_POS      (6U)    // [6]
/**
 * @def      DIRECT_EXECUTE_DISABLE_POS
 * @value    7U
 * @resolution -
 * @brief    Bit position for disabling direct code execution.
 */
#define DIRECT_EXECUTE_DISABLE_POS (7U)    // [7]
/**
 * @def      FLASH_ENABLE_POS
 * @value    8U
 * @resolution -
 * @brief    Bit position for configuring Flash memory access region.
 */
#define FLASH_ENABLE_POS           (8U)    // [10:8]
/**
 * @def      RAM0_ENABLE_POS
 * @value    11U
 * @resolution -
 * @brief    Bit position for configuring RAM0 memory access region.
 */
#define RAM0_ENABLE_POS            (11U)   // [13:11]  
/**
 * @def      WORK_FLASH_ENABLE_POS
 * @value    14U
 * @resolution -
 * @brief    Bit position for configuring Work Flash memory access region.
 */
#define WORK_FLASH_ENABLE_POS      (14U)   // [15:14]
/**
 * @def      SFLASH_ENABLE_POS
 * @value    16U
 * @resolution -
 * @brief    Bit position for configuring Supervisory Flash memory access region.
 */
#define SFLASH_ENABLE_POS          (16U)   // [17:16]
/**
 * @def      MMIO_ENABLE_POS
 * @value    18U
 * @resolution -
 * @brief    Bit position for configuring Memory Mapped I/O access region.
 */
#define MMIO_ENABLE_POS            (18U)   // [19:18]

/**
 * @def      SEC_AP_CTL_M0_VAL
 * @value    0x1U
 * @resolution -
 * @brief    Access restriction value for Cortex-M0 in SECURE mode (Temporary disable).
 */
#define SEC_AP_CTL_M0_VAL          (0x1U)   // 01: Temporary disable
/**
 * @def      SEC_AP_CTL_M4_VAL
 * @value    0x1U
 * @resolution -
 * @brief    Access restriction value for Cortex-M4 in SECURE mode (Temporary disable).
 */
#define SEC_AP_CTL_M4_VAL          (0x1U)   // 01: Temporary disable  
/**
 * @def      SEC_AP_CTL_SYS_VAL
 * @value    0x0U
 * @resolution -
 * @brief    Access restriction value for System peripherals in SECURE mode (Enable).
 */
#define SEC_AP_CTL_SYS_VAL         (0x0U)   // 00: Enable
/**
 * @def      SEC_SYS_AP_MPU_VAL
 * @value    0x0U
 * @resolution -
 * @brief    Access restriction value for System AP MPU in SECURE mode (Enable).
 */
#define SEC_SYS_AP_MPU_VAL         (0x1U)   // 1: Enable
/**
 * @def      SEC_DIRECT_EXECUTE_VAL
 * @value    0x1U
 * @resolution -
 * @brief    Access restriction value for Direct Execute in SECURE mode (Disable).
 */
#define SEC_DIRECT_EXECUTE_VAL     (0x1U)   // 1: Disable (fixed)
/**
 * @def      SEC_FLASH_ENABLE_VAL
 * @value    0x0U
 * @resolution -
 * @brief    Access restriction value for Flash in SECURE mode (Entire region).
 */
#define SEC_FLASH_ENABLE_VAL       (0x0U)   // 000: Entire region
/**
 * @def      SEC_RAM0_ENABLE_VAL
 * @value    0x0U
 * @resolution -
 * @brief    Access restriction value for RAM0 in SECURE mode (Entire region).
 */
#define SEC_RAM0_ENABLE_VAL        (0x0U)   // 000: Entire region
/**
 * @def      SEC_WORK_FLASH_ENABLE_VAL
 * @value    0x0U
 * @resolution -
 * @brief    Access restriction value for Work Flash in SECURE mode (Entire region).
 */
#define SEC_WORK_FLASH_ENABLE_VAL  (0x0U)   // 00: Entire region  
/**
 * @def      SEC_SFLASH_ENABLE_VAL
 * @value    0x0U
 * @resolution -
 * @brief    Access restriction value for SFlash in SECURE mode (Entire region).
 */
#define SEC_SFLASH_ENABLE_VAL      (0x0U)   // 00: Entire region
/**
 * @def      SEC_MMIO_ENABLE_VAL
 * @value    0x1U
 * @resolution -
 * @brief    Access restriction value for MMIO in SECURE mode (Only IPC MMIO registers accessible).
 */
#define SEC_MMIO_ENABLE_VAL        (0x1U)   // 01: Only IPC MMIO registers accessible

/**
 * @def      SEC_WD_AP_CTL_M0_VAL
 * @value    0x1U
 * @resolution -
 * @brief    Access restriction value for Cortex-M0 in SECURE_W_DEBUG mode (Temporary disable).
 */
#define SEC_WD_AP_CTL_M0_VAL          (0x1U)    // 01: Temporary disable
/**
 * @def      SEC_WD_AP_CTL_M4_VAL
 * @value    0x1U
 * @resolution -
 * @brief    Access restriction value for Cortex-M4 in SECURE_W_DEBUG mode (Temporary disable).
 */
#define SEC_WD_AP_CTL_M4_VAL          (0x1U)    // 01: Temporary disable
/**
 * @def      SEC_WD_AP_CTL_SYS_VAL
 * @value    0x0U
 * @resolution -
 * @brief    Access restriction value for System peripherals in SECURE_W_DEBUG mode (Enable).
 */
#define SEC_WD_AP_CTL_SYS_VAL         (0x0U)    // 00: Enable
/**
 * @def      SEC_WD_SYS_AP_MPU_VAL
 * @value    0x0U
 * @resolution -
 * @brief    Access restriction value for System AP MPU in SECURE_W_DEBUG mode (Disable).
 */
#define SEC_WD_SYS_AP_MPU_VAL         (0x0U)    // 0: Disable
/**
 * @def      SEC_WD_DIRECT_EXECUTE_VAL
 * @value    0x1U
 * @resolution -
 * @brief    Access restriction value for Direct Execute in SECURE_W_DEBUG mode (Disable).
 */
#define SEC_WD_DIRECT_EXECUTE_VAL     (0x1U)    // 1: Disable  (fixed)
/**
 * @def      SEC_WD_FLASH_ENABLE_VAL
 * @value    0x0U
 * @resolution -
 * @brief    Access restriction value for Flash in SECURE_W_DEBUG mode (Entire region).
 */
#define SEC_WD_FLASH_ENABLE_VAL       (0x0U)    // 000: Entire region
/**
 * @def      SEC_WD_RAM0_ENABLE_VAL
 * @value    0x0U
 * @resolution -
 * @brief    Access restriction value for RAM0 in SECURE_W_DEBUG mode (Entire region).
 */
#define SEC_WD_RAM0_ENABLE_VAL        (0x0U)    // 000: Entire region
/**
 * @def      SEC_WD_WORK_FLASH_ENABLE_VAL
 * @value    0x0U
 * @resolution -
 * @brief    Access restriction value for Work Flash in SECURE_W_DEBUG mode (Entire region).
 */
#define SEC_WD_WORK_FLASH_ENABLE_VAL  (0x0U)    // 00: Entire region 
/**
 * @def      SEC_WD_SFLASH_ENABLE_VAL
 * @value    0x0U
 * @resolution -
 * @brief    Access restriction value for SFlash in SECURE_W_DEBUG mode (Entire region).
 */
#define SEC_WD_SFLASH_ENABLE_VAL      (0x0U)    // 00: Entire region 
/**
 * @def      SEC_WD_MMIO_ENABLE_VAL
 * @value    0x1U
 * @resolution -
 * @brief    Access restriction value for MMIO in SECURE_W_DEBUG mode (Only IPC MMIO registers accessible).
 */
#define SEC_WD_MMIO_ENABLE_VAL        (0x1U)    // 01: Only IPC MMIO registers accessible

/**
 * @def      SECURE_ACC_RESTRICT
 * @value    (complex bitwise operation)
 * @resolution -
 * @brief    Combines all individual access restriction values into a single 32-bit word for SECURE mode.
 */
#define SECURE_ACC_RESTRICT (\
   ((uint32)SEC_AP_CTL_M0_VAL << AP_CTL_M0_DISABLE_POS)             | \
   ((uint32)SEC_AP_CTL_M4_VAL << AP_CTL_M4_DISABLE_POS)             | \
   ((uint32)SEC_AP_CTL_SYS_VAL << AP_CTL_SYS_DISABLE_POS)           | \
   ((uint32)SEC_SYS_AP_MPU_VAL << SYS_AP_MPU_ENABLE_POS)            | \
   ((uint32)SEC_DIRECT_EXECUTE_VAL << DIRECT_EXECUTE_DISABLE_POS)   | \
   ((uint32)SEC_FLASH_ENABLE_VAL << FLASH_ENABLE_POS)               | \
   ((uint32)SEC_RAM0_ENABLE_VAL << RAM0_ENABLE_POS)                 | \
   ((uint32)SEC_WORK_FLASH_ENABLE_VAL << WORK_FLASH_ENABLE_POS)     | \
   ((uint32)SEC_SFLASH_ENABLE_VAL << SFLASH_ENABLE_POS)             | \
   ((uint32)SEC_MMIO_ENABLE_VAL << MMIO_ENABLE_POS))

/**
 * @def      SECURE_WD_ACC_RESTRICT
 * @value    (complex bitwise operation)
 * @resolution -
 * @brief    Combines all individual access restriction values into a single 32-bit word for SECURE_WITH_DEBUG mode.
 */
#define SECURE_WD_ACC_RESTRICT (\
   ((uint32)SEC_WD_AP_CTL_M0_VAL << AP_CTL_M0_DISABLE_POS)            | \
   ((uint32)SEC_WD_AP_CTL_M4_VAL << AP_CTL_M4_DISABLE_POS)            | \
   ((uint32)SEC_WD_AP_CTL_SYS_VAL << AP_CTL_SYS_DISABLE_POS)          | \
   ((uint32)SEC_WD_SYS_AP_MPU_VAL << SYS_AP_MPU_ENABLE_POS)           | \
   ((uint32)SEC_WD_DIRECT_EXECUTE_VAL << DIRECT_EXECUTE_DISABLE_POS)  | \
   ((uint32)SEC_WD_FLASH_ENABLE_VAL << FLASH_ENABLE_POS)              | \
   ((uint32)SEC_WD_RAM0_ENABLE_VAL << RAM0_ENABLE_POS)                | \
   ((uint32)SEC_WD_WORK_FLASH_ENABLE_VAL << WORK_FLASH_ENABLE_POS)    | \
   ((uint32)SEC_WD_SFLASH_ENABLE_VAL << SFLASH_ENABLE_POS)            | \
   ((uint32)SEC_WD_MMIO_ENABLE_VAL << MMIO_ENABLE_POS))


/**
 * @def      ZERO_NUM
 * @value    0U
 * @resolution -
 * @brief    Represents the integer value zero.
 */
#define ZERO_NUM (0U)
/**
 * @def      ONE_NUM
 * @value    1U
 * @resolution -
 * @brief    Represents the integer value one.
 */
#define ONE_NUM (1U)
/**
 * @def      SHIFT_8_BIT
 * @value    8U
 * @resolution -
 * @brief    Defines a left shift by 8 bits, used for byte manipulation in 32-bit words.
 */
#define SHIFT_8_BIT (8U)
/**
 * @def      SHIFT_16_BIT
 * @value    16U
 * @resolution -
 * @brief    Defines a left shift by 16 bits.
 */
#define SHIFT_16_BIT (16U)
/**
 * @def      SHIFT_24_BIT
 * @value    24U
 * @resolution -
 * @brief    Defines a left shift by 24 bits.
 */
#define SHIFT_24_BIT (24U)
/**
 * @def      UID_32_BIT_SIZE
 * @value    4U
 * @resolution -
 * @brief    Size of the UID in 32-bit words.
 */
#define UID_32_BIT_SIZE (4U)
/**
 * @def      UID_1_BYTE_SIZE
 * @value    15U
 * @resolution -
 * @brief    Size of the UID in bytes.
 */
#define UID_1_BYTE_SIZE (15U)
/**
 * @def      MASK_HF0_RESTORE_FAILED
 * @value    0x10U
 * @resolution -
 * @brief    Mask to check if the HF0 clock restore operation has failed.
 */
#define MASK_HF0_RESTORE_FAILED (0x10U)


/**
 * @def      SRAM0_NC_ECC_MASK
 * @value    0x08000000u
 * @resolution -
 * @brief    Mask used to access ECC-related status bits in SRAM0
 */
#define SRAM0_NC_ECC_MASK       (0x08000000u)


/**
 * @def      FAULT_STATUS_VALID
 * @value    0x80000000u
 * @resolution -
 * @brief    Mask to check if the fault status information is valid.
 */
#define FAULT_STATUS_VALID      (0x80000000u)


/**
 * @def      ECC_CHECK_DIS
 * @value    0x00080000u
 * @resolution -
 * @brief    Mask to disable ECC (Error Correction Code) checking mechanism.
 */
#define ECC_CHECK_DIS           (0x00080000u)

/**
 * @brief    Configuration structure for RMA (Return Material Authorization) SROM calls.
 * @datasize 28 bytes
 */
typedef struct cy_rma_config_str
{
  uint32 OpCode;      /**< SROM command opcode (e.g., CY_SROM_OP_TRANSITION_RMA). */
  uint32 ObjectSize;  /**< Size of the associated data object for the command. */
  uint32 CommandID;   /**< Specific command identifier for the operation. */
  uint32 UniqueID_0;  /**< The first 32 bits of the device's unique ID. */
  uint32 UniqueID_1;  /**< The second 32 bits of the device's unique ID. */
  uint32 UniqueID_2;  /**< The third 32 bits of the device's unique ID. */
  uint32 dataAddr;    /**< Memory address of the data associated with the command. */
} cy_rma_config_t;

/**
 * @def      VHSM_CUSTOM_KEY_DECRYPTED_LENGTH_MAX
 * @value    1015u
 * @resolution -
 * @brief    Maximum length of a decrypted key.
 */
#define  VHSM_CUSTOM_KEY_DECRYPTED_LENGTH_MAX                         (1015u)
/**
 * @def      VHSM_CUSTOM_COMMON_KEY_LENGTH
 * @value    16u
 * @resolution -
 * @brief    Length of a common symmetric key (128 bits).
 */
#define  VHSM_CUSTOM_COMMON_KEY_LENGTH                                (16u)
/**
 * @def      VHSM_CUSTOM_TAG_LENGTH
 * @value    16u
 * @resolution -
 * @brief    Length of the authentication tag in GCM mode (128 bits).
 */
#define  VHSM_CUSTOM_TAG_LENGTH                                       (16u)
/**
 * @def      VHSM_CUSTOM_IV_LENGTH
 * @value    12u
 * @resolution -
 * @brief    Length of the Initialization Vector (IV) for AES-GCM.
 */
#define  VHSM_CUSTOM_IV_LENGTH                                        (12u)
/**
 * @def      VHSM_CUSTOM_AAD_LENGTH
 * @value    16u
 * @resolution -
 * @brief    Length of the Additional Authenticated Data (AAD) for AES-GCM.
 */
#define  VHSM_CUSTOM_AAD_LENGTH                                       (16u)
/**
 * @def      VHSM_CUSTOM_KEY_ID_SIZE
 * @value    1u
 * @resolution -
 * @brief    Size in bytes of a key identifier.
 */
#define  VHSM_CUSTOM_KEY_ID_SIZE                                      (1u)
/**
 * @def      VHSM_CUSTOM_KEY_LENGTH_SIZE
 * @value    4u
 * @resolution -
 * @brief    Size in bytes of a field representing key length.
 */
#define  VHSM_CUSTOM_KEY_LENGTH_SIZE                                  (4u)
/**
 * @def      VHSM_CUSTOM_AESGCM_MAX_OUT_SIZE
 * @value    16u
 * @resolution -
 * @brief    Maximum output size for an AES-GCM operation.
 */
#define  VHSM_CUSTOM_AESGCM_MAX_OUT_SIZE                              (16u)
/**
 * @def      VHSM_CUSTOM_PK1_SIZE
 * @value    64u
 * @resolution -
 * @brief    Defines a size of 64 bytes, related to a specific public key (PK1).
 */
#define  VHSM_CUSTOM_PK1_SIZE                                         (64u)

/**
 * @def      VHSM_CUSTOM_PUBLIC_KEY_DEVICE_AUTHENTICATION_ID
 * @value    0u
 * @resolution -
 * @brief    Key ID for the public key used in device authentication.
 */
#define  VHSM_CUSTOM_PUBLIC_KEY_DEVICE_AUTHENTICATION_ID                    (0u)
/**
 * @def      VHSM_CUSTOM_SHE_KEY_TYPEX_ID
 * @value    1u
 * @resolution -
 * @brief    Key ID for the SHE key used in Type-X operations.
 */
#define  VHSM_CUSTOM_SHE_KEY_TYPEX_ID                                       (1u) 
/**
 * @def      VHSM_CUSTOM_MASTER_ECU_KEY_ID
 * @value    2u
 * @resolution -
 * @brief    Key ID for the Master ECU Key.
 */
#define  VHSM_CUSTOM_MASTER_ECU_KEY_ID                                      (2u) 
/**
 * @def      VHSM_CUSTOM_SHE_KEY_SECUREBOOT_ID
 * @value    3u
 * @resolution -
 * @brief    Key ID for the SHE key used for Secure Boot.
 */
#define  VHSM_CUSTOM_SHE_KEY_SECUREBOOT_ID                                  (3u) 
/**
 * @def      VHSM_CUSTOM_SHE_KEY_DEBUG_PORT_ID
 * @value    4u
 * @resolution -
 * @brief    Key ID for the SHE key used for Debug Port authentication.
 */
#define  VHSM_CUSTOM_SHE_KEY_DEBUG_PORT_ID                                  (4u) 
/**
 * @def      VHSM_CUSTOM_PUBLIC_KEY_DEBUG_CONNECT_ID
 * @value    5u
 * @resolution -
 * @brief    Key ID for the public key used for the debug connect sequence.
 */
#define  VHSM_CUSTOM_PUBLIC_KEY_DEBUG_CONNECT_ID                            (5u)
/**
 * @def      VHSM_CUSTOM_SHE_KEY_REPROGRAMMING_ID
 * @value    6u
 * @resolution -
 * @brief    Key ID for the SHE key used for reprogramming operations.
 */
#define  VHSM_CUSTOM_SHE_KEY_REPROGRAMMING_ID                               (6u)
/**
 * @def      CRYPTO_E_KEY_GEN_M1_M5_FAIL
 * @value    14u
 * @resolution -
 * @brief    Custom error code indicating a failure during the M1-M5 message generation for SHE key updates.
 */
#define  CRYPTO_E_KEY_GEN_M1_M5_FAIL                                  (14u)
/**
 * @def      CRYPTO_E_KEY_DECRYPT_FAIL
 * @value    15u
 * @resolution -
 * @brief    Custom error code indicating a general key decryption failure.
 */
#define  CRYPTO_E_KEY_DECRYPT_FAIL                                    (15u)
/**
 * @def      CRYPTO_E_KEY_CONVERT_PEM_FAIL
 * @value    16u
 * @resolution -
 * @brief    Custom error code indicating a failure in converting a key from PEM format.
 */
#define  CRYPTO_E_KEY_CONVERT_PEM_FAIL                                (16u)
/**
 * @def      CRYPTO_E_KEY_DECRYPT_FAIL_COMMON_KEY_EMPTY
 * @value    17u
 * @resolution -
 * @brief    Custom error code indicating decryption failed because the required common key is empty.
 */
#define  CRYPTO_E_KEY_DECRYPT_FAIL_COMMON_KEY_EMPTY                   (17u)

/**
 * @def      VHSM_CUSTOM_SIZEOF_SHE_M1_IDS
 * @value    1u
 * @resolution -
 * @brief    Size in bytes of the ID fields (ID and AuthID) in the SHE M1 message.
 */
#define VHSM_CUSTOM_SIZEOF_SHE_M1_IDS                             (1u)
/**
 * @def      VHSM_CUSTOM_SIZEOF_SHE_KEY
 * @value    16u
 * @resolution -
 * @brief    Size in bytes of a standard SHE key (128 bits).
 */
#define VHSM_CUSTOM_SIZEOF_SHE_KEY                                (16u)
/**
 * @def      VHSM_CUSTOM_SIZEOF_SHE_UPDATE_CONSTANT
 * @value    16u
 * @resolution -
 * @brief    Size in bytes of the constant used in the SHE key update protocol.
 */
#define VHSM_CUSTOM_SIZEOF_SHE_UPDATE_CONSTANT                    (16u)
/**
 * @def      VHSM_CUSTOM_SIZEOF_KDF_BUFFER
 * @value    (VHSM_CUSTOM_SIZEOF_SHE_KEY+ VHSM_CUSTOM_SIZEOF_SHE_UPDATE_CONSTANT)
 * @resolution -
 * @brief    Buffer size for the Key Derivation Function (KDF) input.
 */
#define VHSM_CUSTOM_SIZEOF_KDF_BUFFER                             (VHSM_CUSTOM_SIZEOF_SHE_KEY+ VHSM_CUSTOM_SIZEOF_SHE_UPDATE_CONSTANT)
/**
 * @def      VHSM_CUSTOM_SIZEOF_SHE_M1_UID
 * @value    15u
 * @resolution -
 * @brief    Size in bytes of the UID field in the SHE M1 message.
 */
#define VHSM_CUSTOM_SIZEOF_SHE_M1_UID                             (15u)
/**
 * @def      VHSM_CUSTOM_STARTINDEX_SHE_M1_IDS
 * @value    VHSM_CUSTOM_SIZEOF_SHE_M1_UID
 * @resolution -
 * @brief    Start index of the ID fields within the M1 message buffer.
 */
#define VHSM_CUSTOM_STARTINDEX_SHE_M1_IDS                         (VHSM_CUSTOM_SIZEOF_SHE_M1_UID)
/**
 * @def      VHSM_CUSTOM_SIZEOF_SHE_M1
 * @value    (VHSM_CUSTOM_SIZEOF_SHE_M1_UID + VHSM_CUSTOM_SIZEOF_SHE_M1_IDS)
 * @resolution -
 * @brief    Total size in bytes of the SHE M1 message.
 */
#define VHSM_CUSTOM_SIZEOF_SHE_M1                                 (VHSM_CUSTOM_SIZEOF_SHE_M1_UID + VHSM_CUSTOM_SIZEOF_SHE_M1_IDS)
/**
 * @def      VHSM_CUSTOM_SIZEOF_SHE_M4
 * @value    32u
 * @resolution -
 * @brief    Total size in bytes of the SHE M4 message.
 */
#define VHSM_CUSTOM_SIZEOF_SHE_M4                                 (32u)
/**
 * @def      VHSM_CUSTOM_SIZEOF_SHE_M4_COUNTER_FULL_BYTES
 * @value    4u
 * @resolution -
 * @brief    Size in bytes of the counter portion of the M4 message.
 */
#define VHSM_CUSTOM_SIZEOF_SHE_M4_COUNTER_FULL_BYTES              (4u)
/**
 * @def      VHSM_CUSTOM_SIZEOF_SHE_M5
 * @value    16u
 * @resolution -
 * @brief    Total size in bytes of the SHE M5 message.
 */
#define VHSM_CUSTOM_SIZEOF_SHE_M5                                 (16u)
/**
 * @def      VHSM_CUSTOM_SHE_M4_M5
 * @value    (VHSM_CUSTOM_SIZEOF_SHE_M4 + VHSM_CUSTOM_SIZEOF_SHE_M5)
 * @resolution -
 * @brief    Combined size of SHE M4 and M5 messages.
 */
#define VHSM_CUSTOM_SHE_M4_M5                                     (VHSM_CUSTOM_SIZEOF_SHE_M4 + VHSM_CUSTOM_SIZEOF_SHE_M5)
/**
 * @def      VHSM_CUSTOM_SIZEOF_SHE_M1_M5
 * @value    (VHSM_CUSTOM_SIZEOF_SHE_M1_M3 + VHSM_CUSTOM_SHE_M4_M5)
 * @resolution -
 * @brief    Combined size of all SHE key update messages from M1 to M5.
 */
#define VHSM_CUSTOM_SIZEOF_SHE_M1_M5                              (VHSM_CUSTOM_SIZEOF_SHE_M1_M3 + VHSM_CUSTOM_SHE_M4_M5)
/**
 * @def      VHSM_CUSTOM_STARTINDEX_SHE_M2
 * @value    VHSM_CUSTOM_SIZEOF_SHE_M1
 * @resolution -
 * @brief    Start index of the M2 message in a combined message buffer.
 */
#define VHSM_CUSTOM_STARTINDEX_SHE_M2                             (VHSM_CUSTOM_SIZEOF_SHE_M1)
/**
 * @def      VHSM_CUSTOM_MASK_SHE_M2_COUNTER
 * @value    0xFFFFFFF0uL
 * @resolution -
 * @brief    Mask applied to the counter value in the M2 message.
 */
#define VHSM_CUSTOM_MASK_SHE_M2_COUNTER                           (0xFFFFFFF0uL)
/**
 * @def      VHSM_CUSTOM_SIZEOF_SHE_M2
 * @value    32u
 * @resolution -
 * @brief    Total size in bytes of the SHE M2 message.
 */
#define VHSM_CUSTOM_SIZEOF_SHE_M2                                 (32u)
/**
 * @def      VHSM_CUSTOM_STARTINDEX_SHE_M3
 * @value    (VHSM_CUSTOM_STARTINDEX_SHE_M2 + VHSM_CUSTOM_SIZEOF_SHE_M2)
 * @resolution -
 * @brief    Start index of the M3 message in a combined message buffer.
 */
#define VHSM_CUSTOM_STARTINDEX_SHE_M3                             (VHSM_CUSTOM_STARTINDEX_SHE_M2 + VHSM_CUSTOM_SIZEOF_SHE_M2)
/**
 * @def      VHSM_CUSTOM_SIZEOF_SHE_M3
 * @value    16u
 * @resolution -
 * @brief    Total size in bytes of the SHE M3 message.
 */
#define VHSM_CUSTOM_SIZEOF_SHE_M3                                 (16u)
/**
 * @def      VHSM_CUSTOM_SIZEOF_SHE_M1_M3
 * @value    (VHSM_CUSTOM_SIZEOF_SHE_M1 + VHSM_CUSTOM_SIZEOF_SHE_M2 + VHSM_CUSTOM_SIZEOF_SHE_M3)
 * @resolution -
 * @brief    Combined size of SHE M1, M2, and M3 messages.
 */
#define VHSM_CUSTOM_SIZEOF_SHE_M1_M3                              (VHSM_CUSTOM_SIZEOF_SHE_M1 + VHSM_CUSTOM_SIZEOF_SHE_M2 + VHSM_CUSTOM_SIZEOF_SHE_M3)
/**
 * @def      VHSM_CUSTOM_SHE_KEY_SIZE_MAX
 * @value    32u
 * @resolution -
 * @brief    Maximum supported SHE key size in bytes.
 */
#define VHSM_CUSTOM_SHE_KEY_SIZE_MAX                              (32u)
/**
 * @def      vHsm_Custom_She_M1_BuildIds(Id, AuthId)
 * @value    (((uint8)(((Id) << 4u) & 0xF0u)) | ((uint8)((AuthId) & 0x0Fu)))
 * @resolution -
 * @brief    Packs the Key ID and Authentication ID into a single byte for the M1 message.
 */
#define vHsm_Custom_She_M1_BuildIds(Id, AuthId)                   (((uint8)((((uint8)Id) << 4u) & 0xF0u)) | ((uint8)((AuthId) & 0x0Fu)))/* Mask update SHE id */

/**
 * @def      vHsm_Custom_She_GetPtrMacConst(indexOfSheKey)
 * @value    (Crypto_30_LibCv_GetAddrSheConstants(...))
 * @resolution -
 * @brief    Macro to get a pointer to the MAC constant for a given SHE key index.
 */
#define vHsm_Custom_She_GetPtrMacConst(indexOfSheKey)             (Crypto_30_LibCv_GetAddrSheConstants(Crypto_30_LibCv_GetSheConstantsMacStartIdxOfShePage(Crypto_30_LibCv_GetShePageIdxOfSheKeys((indexOfSheKey)))))
/**
 * @def      vHsm_Custom_She_GetPtrEncConst(indexOfSheKey)
 * @value    (Crypto_30_LibCv_GetAddrSheConstants(...))
 * @resolution -
 * @brief    Macro to get a pointer to the Encryption constant for a given SHE key index.
 */
#define vHsm_Custom_She_GetPtrEncConst(indexOfSheKey)             (Crypto_30_LibCv_GetAddrSheConstants(Crypto_30_LibCv_GetSheConstantsEncStartIdxOfShePage(Crypto_30_LibCv_GetShePageIdxOfSheKeys((indexOfSheKey)))))

/**
 * @def      ENCRYPTED_KEYINFO_LENGTH
 * @value    256u
 * @resolution -
 * @brief    Length of the encrypted key information block.
 */
#define ENCRYPTED_KEYINFO_LENGTH (256u)
/**
 * @def      AES_GCM_COMMON_KEY_LENGTH
 * @value    16u
 * @resolution -
 * @brief    Length of the common key used for AES-GCM operations (128 bits).
 */
#define AES_GCM_COMMON_KEY_LENGTH (16u)
/**
 * @def      AES_GCM_IV_LENGTH
 * @value    12u
 * @resolution -
 * @brief    Length of the IV used for AES-GCM operations.
 */
#define AES_GCM_IV_LENGTH (12u)
/**
 * @def      AES_GCM_AAD_LENGTH
 * @value    16u
 * @resolution -
 * @brief    Length of the AAD used for AES-GCM operations.
 */
#define AES_GCM_AAD_LENGTH (16u)
/**
 * @def      RANDOM_KEYINFO_LENGTH
 * @value    (AES_GCM_COMMON_KEY_LENGTH + AES_GCM_IV_LENGTH + AES_GCM_AAD_LENGTH)
 * @resolution -
 * @brief    Combined length of the random key info components (Key, IV, AAD).
 */
#define RANDOM_KEYINFO_LENGTH (AES_GCM_COMMON_KEY_LENGTH + AES_GCM_IV_LENGTH + AES_GCM_AAD_LENGTH)
/**
 * @def      AES_GCM_COMMONKEY_IDX
 * @value    0u
 * @resolution -
 * @brief    Start index of the common key within the key info buffer.
 */
#define AES_GCM_COMMONKEY_IDX (0u)
/**
 * @def      AES_GCM_AAD_IDX
 * @value    (AES_GCM_COMMONKEY_IDX + AES_GCM_COMMON_KEY_LENGTH)
 * @resolution -
 * @brief    Start index of the AAD within the key info buffer.
 */
#define AES_GCM_AAD_IDX (AES_GCM_COMMONKEY_IDX + AES_GCM_COMMON_KEY_LENGTH)
/**
 * @def      AES_GCM_IV_IDX
 * @value    (AES_GCM_AAD_IDX + AES_GCM_AAD_LENGTH)
 * @resolution -
 * @brief    Start index of the IV within the key info buffer.
 */
#define AES_GCM_IV_IDX (AES_GCM_AAD_IDX + AES_GCM_AAD_LENGTH)

/**
 * @def      PUBLIC_KEY2K_ADDR
 * @value    0x17006400U
 * @resolution -
 * @brief    SFlash memory address where the 2K RSA public key is stored.
 */
#define PUBLIC_KEY2K_ADDR					(0x17006400U)
/**
 * @def      PUBLIC_KEY3K_ADDR
 * @value    0x17006900U
 * @resolution -
 * @brief    SFlash memory address where the 3K RSA public key is stored.
 */
#define PUBLIC_KEY3K_ADDR					(0x17006900U)
/**
 * @def      CHECK_PUBLIC_KEY
 * @value    0x06u
 * @resolution -
 * @brief    An identifier for a 'check public key' operation.
 */
#define CHECK_PUBLIC_KEY (0x06u)
/**
 * @def      CY_SI_PUBLIC_KEY_STRUCT_OFFSET
 * @value    8UL
 * @resolution -
 * @brief    Offset in bytes to the public key structure within a larger object.
 */
#define CY_SI_PUBLIC_KEY_STRUCT_OFFSET	(8UL)
/**
 * @def      CY_SI_PUBLIC_KEY_MODULUS_LENGTH_2K
 * @value    256UL
 * @resolution -
 * @brief    Modulus length in bytes for an RSA 2048-bit key.
 */
#define CY_SI_PUBLIC_KEY_MODULUS_LENGTH_2K	(256UL)
/**
 * @def      CY_SI_PUBLIC_KEY_MODULUS_LENGTH_3K
 * @value    384UL
 * @resolution -
 * @brief    Modulus length in bytes for an RSA 3072-bit key.
 */
#define CY_SI_PUBLIC_KEY_MODULUS_LENGTH_3K	(384UL)
/**
 * @def      CY_SI_PUBLIC_KEY_EXPLENGTH
 * @value    32UL
 * @resolution -
 * @brief    Exponent length in bytes for the RSA key.
 */
#define CY_SI_PUBLIC_KEY_EXPLENGTH		(32UL)
/**
 * @def      CY_SI_PUBLIC_KEY_SIZEOF_BYTE
 * @value    8UL
 * @resolution -
 * @brief    Size of a byte in bits.
 */
#define CY_SI_PUBLIC_KEY_SIZEOF_BYTE	(8UL)

/**
 * @def      CRYPTO_30_LIBCV_SHE_CLEARED_STATUS
 * @value    0x00u
 * @resolution -
 * @brief    Represents a cleared or default SHE status.
 */
#define CRYPTO_30_LIBCV_SHE_CLEARED_STATUS                            (0x00u) /* Cleared status */
/**
 * @def      CRYPTO_30_LIBCV_SHE_STATUS_BOOT_FINISHED
 * @value    0x08u
 * @resolution -
 * @brief    SHE status bit indicating that the secure boot process has finished.
 */
#define CRYPTO_30_LIBCV_SHE_STATUS_BOOT_FINISHED                      (0x08u) /* When the secure booting has been finished by calling either CMD_BOOT_FAILURE or CMD_BOOT_OK or if CMD_SECURE_BOOT failed in verifying BOOT_MAC. */
/**
 * @def      CRYPTO_30_LIBCV_SHE_STATUS_BOOT_OK
 * @value    0x10u
 * @resolution -
 * @brief    SHE status bit indicating that the secure boot succeeded.
 */
#define CRYPTO_30_LIBCV_SHE_STATUS_BOOT_OK                            (0x10u) /* If the secure booting (CMD_SECURE_BOOT) succeeded. If CMD_BOOT_FAILURE is called the bit is erased. */
/**
 * @def      CRYPTO_30_LIBCV_SHE_STATUS_EXT_DEBUGGER
 * @value    0x40u
 * @resolution -
 * @brief    SHE status bit indicating that an external debugger is connected.
 */
#define CRYPTO_30_LIBCV_SHE_STATUS_EXT_DEBUGGER                       (0x40u) /* If an external debugger is connected to the chip, i.e. it reflects the input for debugger activation. */

/**
 * @def      NUM_OF_EFUSE_VALUE
 * @value    25U
 * @resolution -
 * @brief    The number of eFuse values to be read or compared.
 */
#define NUM_OF_EFUSE_VALUE            (25U)
/**
 * @def      NUM_OF_SECURE_ACCESS_VALUE
 * @value    3U
 * @resolution -
 * @brief    The number of eFuse values related to secure access restrictions.
 */
#define NUM_OF_SECURE_ACCESS_VALUE    (3U)
/**
 * @def      NUM_OF_DEAD_ACCESS_VALUE
 * @value    3U
 * @resolution -
 * @brief    The number of eFuse values related to dead access restrictions.
 */
#define NUM_OF_DEAD_ACCESS_VALUE      (3U)
/**
 * @def SRAM_CM0_CM7_KEY_INFO_MAC_KEY
 * @value (*((volatile unsigned char*)0x28013FE9U))
 * @resolution -
 * @brief Base SRAM address for CM0+ and CM7 Key information: MAC Key
 */
#define SRAM_CM0_CM7_KEY_INFO_MAC_KEY (*((volatile unsigned char*)0x28013FE9U))
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

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/**
 * @brief    Defines the first 32-bit argument for the TransitionToSecure SROM API, containing opcode and flags.
 * @datasize 4 bytes
 */
typedef struct
{
	uint32_t        : 8;						/**< Reserved bits. */
	uint32_t Debug  : 8;						/**< Debug flag. 1: SECURE_WITH_DEBUG, others: SECURE. */
	uint32_t        : 8;						/**< Reserved bits. */
	uint32_t Opcode : 8;						/**< Opcode for the TransitiontoSecure SROM API. */
} trans_to_secure_arg0_t;

/**
 * @brief    Defines the second 32-bit argument for the TransitionToSecure SROM API, containing access restrictions.
 * @datasize 4 bytes
 */
typedef struct
{
	uint32_t Acc_restrict  : 32;				/**< A 32-bit field defining the access restrictions for SECURE mode. */
} trans_to_secure_arg1_t;

/**
 * @brief    Defines the third 32-bit argument for the TransitionToSecure SROM API, containing dead access restrictions.
 * @datasize 4 bytes
 */
typedef struct
{
	uint32_t Dead_Acc_restrict  : 32;			/**< A 32-bit field defining the access restrictions for DEAD mode. */
} trans_to_secure_arg2_t;

/**
 * @brief    Aggregates all arguments for the TransitionToSecure SROM API call.
 * @datasize 16 bytes
 */
typedef struct
{
	trans_to_secure_arg0_t arg0;				/**< First argument containing opcode and debug flag. */
	trans_to_secure_arg1_t arg1;				/**< Second argument containing access restrictions. */
	trans_to_secure_arg2_t arg2;				/**< Third argument containing dead access restrictions. */
	uint32_t               resv;			    /**< Reserved for future use. */
} trans_to_secure_args_t;

/**
 * @brief    A union to provide different views of the SROM API arguments, either as a structured type or a raw array of 32-bit words.
 * @datasize 16 bytes
 */
typedef union
{
	uint32_t               arg[VHSM_CUSTOM_FOUR];			/**< Raw 32-bit array view of the arguments. */
	trans_to_secure_args_t TransitionToSecure;	            /**< Structured view of the TransitionToSecure arguments. */
} srom_api_args_t;

/**
 * @brief    Enumerates the verification status of a public key stored in SFlash.
 * @datasize 4 bytes (enum size)
 */
typedef enum
{
    INVALID = 0,      /**< The public key has not been written to SFlash yet. */
    VALID = 1,        /**< The public key has been successfully written to SFlash. */
    UNKNOWN = 255,    /**< The request to check the public key's status failed. */
} VerifyKeyType;

/**
 * @brief    Enumerates the combined validity status of the 2K and 3K public keys.
 * @datasize 4 bytes (enum size)
 */
typedef enum
{
    PBKEY_2K_3K_VALID   = 0,   /**< Both 2K and 3K public keys are valid in SFlash. */
    PBKEY_3K_INVALID    = 1,   /**< The 3K public key is not written to SFlash. */
    PBKEY_2K_INVALID    = 2,   /**< The 2K public key is not written to SFlash. */
    PBKEY_2K_3K_INVALID = 3,   /**< Neither the 2K nor the 3K public key is written to SFlash. */
    PBKEY_UNKNOWN       = 255, /**< The request to check the public keys failed. */
} PBKeyStatus;

/**
 * @brief    Enumerates the types of public keys.
 * @datasize 4 bytes (enum size)
 */
typedef enum
{
    KEY_2K = 0, /**< Represents an RSA 2048-bit key. */
    KEY_3K = 1, /**< Represents an RSA 3072-bit key. */
} PBKeyType;

/**
 * @brief    Enumerates the return status codes for the Transition to Secure operation, providing detailed error information.
 * @datasize 4 bytes (enum size)
 */
typedef enum
{
    SECURE_RET_NO_ERR                                                       = 0x00, /**< Request to transition to secure mode is pending. */
    SECURE_RET_SUCCESS                                                      = 0x01, /**< MCU transition to Secure stage successful. */
    SECURE_RET_INVALID_PROTECTION                                           = 0x02, /**< Invalid Protection state. This API is not available in current protection state. */
    SECURE_RET_INVALID_HASH_OBJ2                                            = 0x03, /**< Returned when too many HASH objects are indicated in TOC2. */
    SECURE_RET_INVALID_TOC2                                                 = 0x04, /**< TOC2 has not been updated in SFlash. */
    SECURE_RET_FUSE_PGM_FAILED                                              = 0x05, /**< An eFuse bit has already been written; eFuses are write-once. */
    SECURE_RET_IPC_OR_TIMEOUT_ERR                                           = 0x06, /**< SROM IPC structure is locked or a timeout occurred. */
    SECURE_RET_EFUSE_VALUE_NOT_MATCH                                        = 0x07, /**< An eFuse value did not match the expected value. */
    SECURE_RET_EFUSE_VALUE_SECURE_ACCESS_NOT_MATCH                          = 0x08, /**< An eFuse value for secure access did not match. */
    SECURE_RET_EFUSE_VALUE_DEAD_ACCESS_NOT_MATCH                            = 0x09, /**< An eFuse value for dead access did not match. */
    SECURE_RET_HF0_CLOCK_NOT_FULLY_CONFIGURED                               = 0x0A, /**< The HF0 clock was not fully configured before the operation. */
    SECURE_RET_HF0_CLOCK_NOT_FULLY_RESTORED                                 = 0x11, /**< The HF0 clock was not fully restored after the operation. */
    SECURE_RET_INV_PROT_AND_HF0_RES_FAILED                                  = 0x12, /**< Combination of invalid protection state and HF0 restore failure. */
    SECURE_RET_INV_HASH_OBJ2_AND_HF0_RES_FAILED                             = 0x13, /**< Combination of invalid hash object and HF0 restore failure. */
    SECURE_RET_INV_TOC2_AND_HF0_RES_FAILED                                  = 0x14, /**< Combination of invalid TOC2 and HF0 restore failure. */
    SECURE_RET_FUSE_PGM_AND_HF0_RES_FAILED                                  = 0x15, /**< Combination of eFuse programming failure and HF0 restore failure. */
    SECURE_RET_IPC_TMO_ERR_AND_HF0_RES_FAILED                               = 0x16, /**< Combination of IPC/timeout error and HF0 restore failure. */
    SECURE_RET_EFUSE_VAL_CMP_AND_HF0_RES_FAILED                             = 0x17, /**< Combination of eFuse value comparison error and HF0 restore failure. */
    SECURE_RET_SEC_ACC_CMP_AND_HF0_RES_FAILED                               = 0x18, /**< Combination of secure access eFuse comparison error and HF0 restore failure. */
    SECURE_RET_DEAD_ACC_CMP_AND_HF0_RES_FAILED                              = 0x19, /**< Combination of dead access eFuse comparison error and HF0 restore failure. */
    SECURE_RET_HF0_CLK_CFG_AND_RES_FAILED                                   = 0x1A, /**< Combination of HF0 clock configuration and restore failure. */
} SecureReturnStatus;

/**
 * @brief    Enumerates the return status codes for the RMA (Return Material Authorization) operation.
 * @datasize 4 bytes (enum size)
 */
typedef enum
{
    RMA_RET_NO_ERR                              = 0, /**< Request to provide signature is pending. */
    RMA_RET_SUCCESS                             = 1, /**< MCU transition to RMA stage successful. */
    RMA_RET_INVALID_PROTECTION                  = 2, /**< Invalid Protection state. This API is not available in current protection state. */
    RMA_RET_EMB_ACTIVE                          = 3, /**< Returned by WriteRow when invoked during an active embedded operation. */
    RMA_RET_INVALID_SIGN                        = 4, /**< Returned when invalid signature is found during RMA. */
    RMA_RET_INVALID_PUBLIC_KEY                  = 5, /**< Returned when the public key structure is invalid. */
    RMA_RET_IPC_OR_TIMEOUT_ERR                  = 6, /**< SROM IPC structure is locked or a timeout occurred. */
} RMAReturnStatus;

/**
 * @brief    Enumerates the result codes for the Device Authentication random number generation sequence.
 * @datasize 4 bytes (enum size)
 */
typedef enum
{
  DEVICEAUTHEN_E_OK = 0,                  /**< The operation completed successfully. */
  DEVICEAUTHEN_E_NOT_OK = 1,              /**< A non-specific error occurred during the operation. */
  DEVICEAUTHEN_E_RANDOM_FAILED = 22,      /**< Generation of the random number failed. */
  DEVICEAUTHEN_E_ENC_RANDOM_FAILED = 23,  /**< Encryption of the random number failed. */
  DEVICEAUTHEN_E_SESSION_KEY_ERR = 24,    /**< An error occurred while getting the session key. */
} DeviceAuthenRNDType;

/**
 * @brief    Defines the structure for a public key as expected by the crypto driver, containing pointers to key components and their sizes.
 * @datasize 28 bytes
 */
typedef struct
{
	uint32_t moduloAddr;			/**< Address of the public key modulus. */
	uint32_t moduloSize;			/**< Size (in bits) of the modulus part of the public key. */
	uint32_t expAddr;				/**< Address of the public key exponent. */
	uint32_t expSize;				/**< Size (in bits) of the exponent part of the public key. */
	uint32_t barrettAddr;			/**< Address of the Barrett coefficient. */
	uint32_t inverseModuloAddr;		/**< Address of the binary inverse modulo. */
	uint32_t rBarAddr;				/**< Address of the R-bar (2^moduloLength mod modulo) value. */
} cy_si_stc_crypto_public_key_t;

/**
 * @brief    Defines the complete storage structure for an RSA 2048-bit public key, including metadata and key components.
 * @datasize 1316 bytes
 */
typedef struct
{
	uint32_t objSize;											/**< Total size of this public key object. */
	uint32_t signatureScheme;									/**< The signature scheme used with this key. */
	cy_si_stc_crypto_public_key_t publicKeyStruct;				/**< Structure containing pointers to the key components. */
	uint8_t  moduloData[CY_SI_PUBLIC_KEY_MODULUS_LENGTH_2K];			/**< Buffer for the 256-byte key modulus data. */
	uint8_t  expData[CY_SI_PUBLIC_KEY_EXPLENGTH];				/**< Buffer for the 32-byte public exponent data. */
	uint8_t  barrettData[CY_SI_PUBLIC_KEY_MODULUS_LENGTH_2K + VHSM_CUSTOM_FOUR];	/**< Buffer for the Barrett coefficient data. */
	uint8_t  inverseModuloData[CY_SI_PUBLIC_KEY_MODULUS_LENGTH_2K];	/**< Buffer for the binary inverse modulo data. */
	uint8_t  rBarData[CY_SI_PUBLIC_KEY_MODULUS_LENGTH_2K];			/**< Buffer for the R-bar data. */
} cy_si_stc_public_key_2K_t;

/**
 * @brief    Defines the complete storage structure for an RSA 3072-bit public key, including metadata and key components.
 * @datasize 1956 bytes
 */
typedef struct
{
	uint32_t objSize;											/**< Total size of this public key object. */
	uint32_t signatureScheme;									/**< The signature scheme used with this key. */
	cy_si_stc_crypto_public_key_t publicKeyStruct;				/**< Structure containing pointers to the key components. */
	uint8_t  moduloData[CY_SI_PUBLIC_KEY_MODULUS_LENGTH_3K];			/**< Buffer for the 384-byte key modulus data. */
	uint8_t  expData[CY_SI_PUBLIC_KEY_EXPLENGTH];				/**< Buffer for the 32-byte public exponent data. */
	uint8_t  barrettData[CY_SI_PUBLIC_KEY_MODULUS_LENGTH_3K + VHSM_CUSTOM_FOUR];	/**< Buffer for the Barrett coefficient data. */
	uint8_t  inverseModuloData[CY_SI_PUBLIC_KEY_MODULUS_LENGTH_3K];	/**< Buffer for the binary inverse modulo data. */
	uint8_t  rBarData[CY_SI_PUBLIC_KEY_MODULUS_LENGTH_3K];			/**< Buffer for the R-bar data. */
} cy_si_stc_public_key_3K_t;

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
/**
 * @type     uint8
 * @var      vHsm_Custom_KeyMapping[VHSM_CUSTOM_TEN]
 * @brief    Maps custom internal key IDs to the CSM (Crypto Service Manager) configuration key handles.
 * @unit     -
 * @scope    Local Variable
 * @section  -
 * @par      Initial setting
 * |RAM0     |RAM1     |RAM2     |RAM3     |RAM4     |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |[see code]      |-      |-      |-      |-      |
 */
static CONST(uint8, VHSM_CUSTOM_APPL_DATA) vHsm_Custom_KeyMapping[VHSM_CUSTOM_TEN] =
  {
    CryptoConf_CryptoKey_She_MAC_Key,
    CryptoConf_CryptoKey_She_Key2,
    CryptoConf_CryptoKey_She_Key3,
    CryptoConf_CryptoKey_She_Key4,
    CryptoConf_CryptoKey_She_Key5,
    CryptoConf_CryptoKey_vHsm_SecureBoot_Key,
    CryptoConf_CryptoKey_She_Key7,
    CryptoConf_CryptoKey_She_TypeX_Encypt_Key,
    CryptoConf_CryptoKey_She_Key9,
    CryptoConf_CryptoKey_She_Key10
  };

/**
 * @type     uint8
 * @var      aad_Buffer[AES_GCM_AAD_LENGTH]
 * @brief    Buffer to store Additional Authenticated Data (AAD) for AES-GCM operations. Initialized to zero.
 * @unit     -
 * @scope    Local Variable
 * @section  -
 * @par      Initial setting
 * |RAM0     |RAM1     |RAM2     |RAM3     |RAM4     |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |-      |-      |-      |-      |-      |
 */
static uint8 aad_Buffer[AES_GCM_AAD_LENGTH] = {0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u};

/**
 * @type     uint32
 * @var      Digital_Signature_RMA[SIGNATURE_WORD_LENGTH]
 * @brief    Buffer located in a special memory section to hold the digital signature for RMA (Return Material Authorization).
 * @unit     -
 * @scope    Local Variable
 * @section  .LifeCycleStage
 * @par      Initial setting
 * |RAM0     |RAM1     |RAM2     |RAM3     |RAM4     |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |-      |-      |-      |-      |-      |
 */
__attribute__ ((section(".LifeCycleStage")))
static uint32 Digital_Signature_RMA[SIGNATURE_WORD_LENGTH];
/**
 * @type     cy_rma_config_t
 * @var      RMAParameterConfig
 * @brief    Configuration structure located in a special memory section for setting RMA parameters.
 * @unit     -
 * @scope    Local Variable
 * @section  .LifeCycleStage
 * @par      Initial setting
 * |RAM0     |RAM1     |RAM2     |RAM3     |RAM4     |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |-      |-      |-      |-      |-      |
 */
__attribute__ ((section(".LifeCycleStage")))
static cy_rma_config_t RMAParameterConfig;

/**
 * @type     uint8
 * @var      pk1_convert_Pem[VHSM_CUSTOM_PK1_SIZE]
 * @brief    Buffer used to hold a public key after conversion from PEM format for device authentication.
 * @unit     -
 * @scope    Local Variable
 * @section  -
 * @par      Initial setting
 * |RAM0     |RAM1     |RAM2     |RAM3     |RAM4     |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |0x00      |-      |-      |-      |-      |
 */
static uint8 pk1_convert_Pem[VHSM_CUSTOM_PK1_SIZE]= {0};

/**
 * @type     uint8
 * @var      aubModulus_g_key_connection[SB_SIZE_PK_LEN_3072]
 * @brief    Global buffer to store the modulus of the public key used for debug connection.
 * @unit     -
 * @scope    Local Variable
 * @section  -
 * @par      Initial setting
 * |RAM0     |RAM1     |RAM2     |RAM3     |RAM4     |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |-      |-      |-      |-      |-      |
 */
static uint8 aubModulus_g_key_connection[SB_SIZE_PK_LEN_3072];
/**
 * @type     uint8
 * @var      aubPubExp_g_key_connection[SB_SIZE_PUBEXP]
 * @brief    Global buffer to store the public exponent of the key used for debug connection.
 * @unit     -
 * @scope    Local Variable
 * @section  -
 * @par      Initial setting
 * |RAM0     |RAM1     |RAM2     |RAM3     |RAM4     |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |-      |-      |-      |-      |-      |
 */
static uint8 aubPubExp_g_key_connection[SB_SIZE_PUBEXP];

/**
 * @type     cy_si_stc_public_key_2K_t*
 * @var      pPublicKey2K
 * @brief    Pointer that will be set to the memory address of the 2K public key structure.
 * @unit     -
 * @scope    Local Variable
 * @section  -
 * @par      Initial setting
 * |RAM0     |RAM1     |RAM2     |RAM3     |RAM4     |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |-      |-      |-      |-      |-      |
 */
static cy_si_stc_public_key_2K_t* pPublicKey2K;
/**
 * @type     cy_si_stc_public_key_3K_t*
 * @var      pPublicKey3K
 * @brief    Pointer that will be set to the memory address of the 3K public key structure.
 * @unit     -
 * @scope    Local Variable
 * @section  -
 * @par      Initial setting
 * |RAM0     |RAM1     |RAM2     |RAM3     |RAM4     |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |-      |-      |-      |-      |-      |
 */
static cy_si_stc_public_key_3K_t* pPublicKey3K;

/**
 * @type     uint32
 * @var      MarginCTL
 * @brief    Control setting for eFuse margin read operations. Default is nominal resistance.
 * @unit     -
 * @scope    Local Variable
 * @section  -
 * @par      Initial setting
 * |RAM0     |RAM1     |RAM2     |RAM3     |RAM4     |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |1      |-      |-      |-      |-      |
 */
static uint32_t MarginCTL = 1u; 
/**
 * @type     uint32
 * @var      EfuseAddr[NUM_OF_EFUSE_VALUE]
 * @brief    Array of eFuse addresses to be read and verified during security operations.
 * @unit     -
 * @scope    Local Variable
 * @section  -
 * @par      Initial setting
 * |RAM0     |RAM1     |RAM2     |RAM3     |RAM4     |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |-|-      |-      |-      |-      |
 */
static uint32_t const EfuseAddr[NUM_OF_EFUSE_VALUE] = {1U,44U,45U,46U,47U,48U,49U,50U,51U,52U,53U,54U,55U,56U,57U,58U,59U,60U,61U,62U,63U,64U,65U,66U,67U};
/**
 * @type     uint32
 * @var      SecureAccessRestrictions_EfuseAddr[NUM_OF_SECURE_ACCESS_VALUE]
 * @brief    Array of eFuse addresses corresponding to Secure Access Restriction settings.
 * @unit     -
 * @scope    Local Variable
 * @section  -
 * @par      Initial setting
 * |RAM0     |RAM1     |RAM2     |RAM3     |RAM4     |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |-|-      |-      |-      |-      |
 */
static uint32_t const SecureAccessRestrictions_EfuseAddr[NUM_OF_SECURE_ACCESS_VALUE] = {60U,61U,62U};
/**
 * @type     uint32
 * @var      DeadAccessRestrictions_EfuseAddr[NUM_OF_DEAD_ACCESS_VALUE]
 * @brief    Array of eFuse addresses corresponding to Dead Access Restriction settings.
 * @unit     -
 * @scope    Local Variable
 * @section  -
 * @par      Initial setting
 * |RAM0     |RAM1     |RAM2     |RAM3     |RAM4     |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |-|-      |-      |-      |-      |
 */
static uint32_t const DeadAccessRestrictions_EfuseAddr[NUM_OF_DEAD_ACCESS_VALUE] = {64U,65U,66U};

/**
 * @type     uint32
 * @var      g_RdEfuseValue
 * @brief    Global variable to store the result of an eFuse read operation.
 * @unit     -
 * @scope    Local Variable
 * @section  -
 * @par      Initial setting
 * |RAM0     |RAM1     |RAM2     |RAM3     |RAM4     |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |-      |-      |-      |-      |-      |
 */
static uint32_t g_RdEfuseValue = 1U;
/**
 * @type     uint32
 * @var      g_RdEfuseMarginValue50
 * @brief    Global variable to store the result of an eFuse margin read at 50% margin.
 * @unit     -
 * @scope    Local Variable
 * @section  -
 * @par      Initial setting
 * |RAM0     |RAM1     |RAM2     |RAM3     |RAM4     |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |-      |-      |-      |-      |-      |
 */
static uint32_t g_RdEfuseMarginValue50 = 0U;
/**
 * @type     uint32
 * @var      g_RdEfuseMarginValue100
 * @brief    Global variable to store the result of an eFuse margin read at 100% margin.
 * @unit     -
 * @scope    Local Variable
 * @section  -
 * @par      Initial setting
 * |RAM0     |RAM1     |RAM2     |RAM3     |RAM4     |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |-      |-      |-      |-      |-      |
 */
static uint32_t g_RdEfuseMarginValue100 = 0U;

#pragma ghs section bss = ".LargeHsmVar"
/**
 * @type     uint8
 * @var      inputHashData[SB_SIZE_PEM_2048]
 * @brief    Global variable to store the input hash data.
 * @unit     -
 * @scope    Global Variable
 * @section  -
 * @par      Initial setting
 * |RAM0     |RAM1     |RAM2     |RAM3     |RAM4     |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |-      |-      |-      |-      |-      |
 */
uint8 inputHashData[SB_SIZE_PEM_2048];                                      /* Length = 460  Bytes */

/**
 * @type     uint8
 * @var      uint8 OutEncryptedCommonKey[ENCRYPTED_KEYINFO_LENGTH]
 * @brief    Global variable to store the output Encrypted Common Key.
 * @unit     -
 * @scope    Global Variable
 * @section  -
 * @par      Initial setting
 * |RAM0     |RAM1     |RAM2     |RAM3     |RAM4     |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |-      |-      |-      |-      |-      |
 */
uint8 OutEncryptedCommonKey[ENCRYPTED_KEYINFO_LENGTH];                      /* Length = 256  Bytes */

/**
 * @type     uint8
 * @var      input_targetkey_value[VHSM_CUSTOM_KEY_DECRYPTED_LENGTH_MAX]
 * @brief    Global variable to store the input target key.
 * @unit     -
 * @scope    Global Variable
 * @section  -
 * @par      Initial setting
 * |RAM0     |RAM1     |RAM2     |RAM3     |RAM4     |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |-      |-      |-      |-      |-      |
 */
uint8 input_targetkey_value[VHSM_CUSTOM_KEY_DECRYPTED_LENGTH_MAX] = {0};    /* Length = 1015 Bytes */

/**
 * @type     uint8
 * @var      publickey_value[VHSM_CUSTOM_KEY_DECRYPTED_LENGTH_MAX]
 * @brief    Global variable to store the public key value.
 * @unit     -
 * @scope    Global Variable
 * @section  -
 * @par      Initial setting
 * |RAM0     |RAM1     |RAM2     |RAM3     |RAM4     |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |-      |-      |-      |-      |-      |
 */
uint8 publickey_value[VHSM_CUSTOM_KEY_DECRYPTED_LENGTH_MAX] = {0};          /* Length = 1015 Bytes */

/**
 * @type     cy_si_stc_public_key_2K_t
 * @var      PublicKey2K_Cmp
 * @brief    Global variable to store the zero public key (2k) for comparison.
 * @unit     -
 * @scope    Global Variable
 * @section  -
 * @par      Initial setting
 * |RAM0     |RAM1     |RAM2     |RAM3     |RAM4     |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |-      |-      |-      |-      |-      |
 */
cy_si_stc_public_key_2K_t PublicKey2K_Cmp = {0};                            /* Length = 1096 Bytes */

/**
 * @type     cy_si_stc_public_key_3K_t
 * @var      PublicKey3K_Cmp
 * @brief    Global variable to store the zero public key (3k) for comparison.
 * @unit     -
 * @scope    Global Variable
 * @section  -
 * @par      Initial setting
 * |RAM0     |RAM1     |RAM2     |RAM3     |RAM4     |
 * |:-----:|:-----:|:-----:|:-----:|:-----:|
 * |-      |-      |-      |-      |-      |
 */
cy_si_stc_public_key_3K_t PublicKey3K_Cmp = {0};                            /* Length = 1608 Bytes */
#pragma ghs section bss = default

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
static bool CompareEfuseValue(uint32_t ReadEfuseAddr);
static bool CompareEfuseValue_DeadAccess(uint32_t ReadEfuseAddr);
static bool CompareEfuseValue_SecureAccess(uint32_t ReadEfuseAddr);
static cy_en_srom_driver_status_t Cy_ReadFuseByte(uint32_t ReadEfuse_Efuseaddr);
static cy_en_srom_driver_status_t Cy_ReadFuseByteMargin(uint32_t Margin_efuseAddr, uint32_t Margin_Ctl);

static FUNC( Std_ReturnType, CRYPTO_30_LIBCV_CODE ) vHsm_Custom_SheKeyUpdateCmac(
  P2CONST( uint8, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR ) dataPtr,
  uint32 length,
  P2CONST( uint8, AUTOMATIC, AUTOMATIC ) keyPtr,
  P2VAR( uint8, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR ) outputPtr,
  P2VAR(eslt_WorkSpaceCMACAES, AUTOMATIC, CRYPTO_30_LIBCV_CRYPTOCV_APPL_VAR) workspace);

static FUNC(Std_ReturnType, CRYPTO_30_LIBCV_CODE) vHsm_Custom_SheKeyUpdateEncrypt(
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) dataPtr,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) keyPtr,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) outputPtr,
  uint8 numberOfBlocks);

static FUNC(Std_ReturnType, CRYPTO_30_LIBCV_CODE) vHsm_Custom_SheKeyUpdateMiyaguchiPreneel(
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) dataPtr,
  uint32 length,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) outputPtr);

static Crypto_30_LibCv_SizeOfSheKeysType GetIndexFromSheId(uint8 SheId);

static FUNC(Std_ReturnType, CRYPTO_30_LIBCV_CODE) vHsm_Custom_SheKeyUpdateGenM4M5(
  P2CONST(uint8, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR) m1m2m3,
  P2VAR(uint8, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR) m4m5,
  P2CONST(uint8, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR) uid,
  P2CONST(uint8, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR) KeyValue,
  uint32 CID,
  Crypto_30_LibCv_SizeOfSheKeysType indexOfSheKey);
  
static void Disable_RAM0_ECC_Check(void);

static void Clear_ECC_Fault_Trace(volatile stc_FAULT_STRUCT_t* base);

static void Enable_RAM0_ECC_Check(void);

/**********************************************************************************************************************
 *  vHsm_Custom_CMD_RND()
 *********************************************************************************************************************/
/*! \brief         The function returns a vector of 128 random bits.
                   The random number generator has to be initialized by CMD_INIT_RNG before random numbers can be
                   supplied.
 *  \details       PRNG_KEY = KDF(SECRET_KEY, PRNG_KEY_C)
                   PRNG_STATE i = ENC ECB,PRNG_KEY(PRNG_STATE i-1)
                   RND = PRNG_STATE i
 *  \return        E_OK                         Request successful.
 *                 E_NOT_OK                     Request failed.
 *********************************************************************************************************************/
 static FUNC(Std_ReturnType, VHSM_CUSTOM_CODE) vHsm_Custom_CMD_RND( P2VAR(uint8, AUTOMATIC, VHSM_CUSTOM_APPL_VAR) RND);

/**********************************************************************************************************************
 *  vHsm_Custom_CMD_EXTEND_SEED()
 *********************************************************************************************************************/
/*! \brief         The function extends the seed of the PRNG by compressing the former seed value and the
                   supplied entropy into a new seed which will be used to generate the following random numbers.
                   The random number generator has to be initialized by CMD_INIT_RNG before the seed can be extended.
 *  \details       PRNG_STATE = AES-MP(PRNG_STATE | ENTROPY)
                   PRNG_SEED = AES-MP(PRNG_SEED | ENTROPY)
 *  \return        E_OK                         Request successful.
 *                 E_NOT_OK                     Request failed.
 *********************************************************************************************************************/
 static FUNC(Std_ReturnType, VHSM_CUSTOM_CODE) vHsm_Custom_CMD_EXTEND_SEED(void);

/**********************************************************************************************************************
 *  vHsm_Custom_CMD_INIT_RND()
 *********************************************************************************************************************/
/*! \brief         The function initializes the seed and derives a key for the PRNG.
 *  \details       The function must be called before CMD_RND after every power cycle/reset. The command has to ignore
                   active debugger protection or secure boot protection flags on SECRET_KEY.
                   Note: The function may need several hundred milliseconds to return.
                   PRNG_SEED_KEY = KDF(SECRET_KEY, PRNG_SEED_KEY_C)
                   PRNG_SEED i = ENC ECB,PRNG_SEED_KEY(PRNG_SEED i-1)
                   PRNG_STATE = PRNG_SEED
 *  \return        E_OK                         Request successful.
 *                 E_NOT_OK                     Request failed.
 *********************************************************************************************************************/
 static FUNC(Std_ReturnType, VHSM_CUSTOM_CODE) vHsm_Custom_CMD_INIT_RND(void);


/**********************************************************************************************************************
 *  vHsm_Custom_XorByte()
 *********************************************************************************************************************/
/*! \brief         Xor with number of byte.
 *  \details       output = inputA xor inputB
 *  \return        None.
 *********************************************************************************************************************/
 static FUNC(void, VHSM_CUSTOM_CODE) vHsm_Custom_XorByte(uint8 *inputA, uint8 *inputB, uint8 * output, uint8 size);

/**********************************************************************************************************************
 *  vHsm_Custom_AESMP()
 *********************************************************************************************************************/
/*! \brief         Miyaguchi-Preneel one-way compression function, uses AES-ECB under the hood.
 *  \details       AES-MP(data | ENTROPY)
 *  \return        None.
 *********************************************************************************************************************/
 static FUNC(Std_ReturnType, VHSM_CUSTOM_CODE) vHsm_Custom_AESMP(uint8 *dataPtr, uint8 *entropy, uint8 jobid, uint8 keyid);

/**********************************************************************************************************************
 *  vHsm_Custom_DeviceAuthen_GenerateRandom()
 *********************************************************************************************************************/
/*! \brief         
 *  \details       
 *  \return        
 *********************************************************************************************************************/
 static FUNC(DeviceAuthenRNDType, VHSM_CUSTOM_CODE) vHsm_Custom_DeviceAuthen_GenerateRandom(uint32 sessionKeyId, uint32 randomKeyId, uint8 *outRandomPtr, uint8 *HsmStatus);

/**********************************************************************************************************************
 *  vHsm_Custom_DecryptedKeytarget()
 *********************************************************************************************************************/
/*! \brief         
 *  \details       
 *  \return        
 *********************************************************************************************************************/
static FUNC(Std_ReturnType, VHSM_CUSTOM_CODE) vHsm_Custom_DecryptedKeytarget ( 
  const uint8 *EncryptedTargetKeyPtr, 
  uint32 EncryptedTargetKeyLength, 
  uint8  *InTagPtr,
  uint32 InTaglength,
  uint8  *OutTargetKeyPtr, 
  uint32 *OutTargetKeyLengthPtr, 
  uint8  *VerifyResult);

static FUNC(Std_ReturnType, VHSM_CUSTOM_CODE) vHsm_Custom_WritePublicKey(
  const uint8 *EncryptedTargetKeyPtr, 
  uint32 EncryptedTargetKeyLength,  
  uint8  KeyID);

static FUNC(Std_ReturnType, VHSM_CUSTOM_CODE) GetEncryptedCommonKey_Info(
  const uint8 *PublicKeyPtr,
  uint32 PublicKeyLength,
  uint8 *OutCommonKeyPtr,
  uint32 *OutCommonKeyLengthPtr);

static FUNC(Std_ReturnType, CRYPTO_30_LIBCV_CODE) vHsm_Custom_SheKeyExport_M1M2M3(
  uint8 AuthenID,
  P2CONST(uint8, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR) KeyValue,
  uint16 KeyLength,
  uint8 SheKey,
  P2CONST(uint8, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR) UID,
  uint32 CID,
  uint8 FID,   
  P2VAR(uint8, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR) m1m2m3
);

static FUNC(Std_ReturnType, CRYPTO_30_LIBCV_CODE) vHsm_Custom_SheKeyUpdateGen_M1_M5(
    Crypto_30_LibCv_SizeOfSheKeysType KeyID,
    uint32 shekey_length,
    P2CONST(uint8, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR) pNewKey,
    P2VAR(uint8, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR) pResultBuffer,
    P2VAR(uint32, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR) pResultLength);

static FUNC(Std_ReturnType, VHSM_CUSTOM_CODE) vHsm_Custom_ENC_ECB_K3(
    uint32 CID,
    P2VAR(uint8, AUTOMATIC, VHSM_CUSTOM_APPL_DATA) encBuffer 
);

static FUNC(Std_ReturnType, VHSM_CUSTOM_CODE) vHsm_Custom_Check_FID(
    Crypto_30_LibCv_SizeOfSheKeysType KeyID,
    P2VAR(uint32, AUTOMATIC, VHSM_CUSTOM_APPL_DATA) CID,
    P2VAR(uint8, AUTOMATIC, VHSM_CUSTOM_APPL_DATA) FID,
    P2VAR(uint8, AUTOMATIC, VHSM_CUSTOM_APPL_DATA) SheID
);


static Std_ReturnType ReadUidRMA(void);
static SecureReturnStatus HandleTransitionSecure(void);
static SecureReturnStatus HandleTransitionSecureWithDebug(void);
static Std_ReturnType HandleReadStage(uint8 *lifeCycleState, uint8 *protectionState);
static RMAReturnStatus HandleRmaRequest(uint8 requestType, const uint8 *signature, uint8 signatureLength);
static VerifyKeyType HandleCheckPBKey(PBKeyType InputKeyType);

static FUNC(Std_ReturnType, VHSM_CUSTOM_CODE) vHsm_Custom_CheckMacKey(uint8 *outPtr);
static FUNC(Std_ReturnType, CRYPTO_30_LIBCV_CODE) vHsm_Custom_She_Cmd_Get_Status(
  P2VAR(uint8, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR) statusPtr);
/** @cond INTERNAL */
#define VHSM_CUSTOM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_19.1 */
/** @endcond */
/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
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
 * |-         |-         |-                 |
 * @brief     Initializes the custom vHSM component. This function is a placeholder for any required module-specific initialization.
 * @note      This function is called during the system startup phase. It currently performs no operations.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
FUNC(void, VHSM_CUSTOM_CODE) vHsm_Custom_Init(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Do nothing */
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
 * |-         |-         |-                 |
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
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
 * |-         |-         |-                 |
 * @brief     Initializes the memory for the custom vHSM component. This is a hook for any necessary memory setup.
 * @note      This function is called as part of the startup sequence. It currently has no implementation.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
FUNC(void, VHSM_CUSTOM_CODE) vHsm_Custom_InitMemory(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Do nothing */
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
 * |-         |-         |-                 |
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
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
 * |-         |-         |-                 |
 * @brief     Cyclic task function for the custom vHSM component, called from the vHSM main loop.
 * @note      This function provides a hook for implementing periodic tasks or state machine processing required by the custom logic.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
FUNC(void, VHSM_CODE) vHsm_Custom_MainFunction(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* This function is called from the main loop of the vHsm.
   * Special functionality can be implemented here.
   */
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint32    |objectId  |ID of the Crypto Driver Object being processed. Not directly used in this function. |
 * |Crypto_JobType*|job |(Input/Output) Pointer to the job structure containing all information for the crypto operation (service, mode, input/output buffers, etc.).|
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |Std_ReturnType|retVal|Operation result status (E_OK: success, E_NOT_OK: failure, or specific error codes like CRYPTO_E_KEY_GEN_M1_M5_FAIL).|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint8* |job->jobPrimitiveInputOutput.outputPtr |Buffer where the result of the cryptographic operation is stored.|
 * |uint32* |job->jobPrimitiveInputOutput.outputLengthPtr|Pointer to a variable that will be updated with the length of the output data.|
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
 * |Std_ReturnType|retVal|Holds the overall return value of the function.|
 * |uint8     |LifeCycleReqType|Stores the request type for lifecycle management operations.|
 * |uint8     |getStatus |Receives the status from the SHE (Secure Hardware Extension) module.|
 * |uint8[]   |RND_buffer|Buffer to hold the generated random number for server challenges.|
 * |uint8[]   |temp_buffer|Temporary buffer to combine the random number and SHE status for output.|
 * |uint8     |MacKeyErr |Stores the error status after checking the MAC key.|
 * |RMAReturnStatus|RMAResponse|Stores the result of an RMA (Return Material Authorization) request.|
 * |SecureReturnStatus|SecureResponse|Stores the result of a Transition to Secure request.|
 * |DeviceAuthenRNDType|retValStatus|Stores the detailed status of the device authentication process.|
 * |uint8     |lifeCycleState|Stores the current lifecycle state of the device.|
 * |uint8     |protectionState|Stores the current protection state of the device.|
 * |uint8[]   |inputHashData|Buffer to hold input data for a HASH operation.|
 * |uint8[]   |OutEncryptedCommonKey|Buffer to store the encrypted common key information.|
 * |PBKeyStatus|respond |Stores the aggregated status of public key verification.|
 * |VerifyKeyType|Key2KCheckingResult|Stores the verification result for the 2K public key.|
 * |VerifyKeyType|Key3KCheckingResult|Stores the verification result for the 3K public key.|
 * |uint32    |inputHashDataLength|Holds the length of the input data for hashing.|
 * |uint32    |OutEncryptedCommonKeyLength|Holds the length of the encrypted common key output.|
 * |Std_ReturnType|retval_crypto|Stores the return value from Crypto_30_LibCv library calls.|
 * |uint8     |Status_HSM|Stores the status returned from an HSM operation.|
 * |uint8     |getKeyLength|Specifies the length of the key being processed.|
 * |uint8[]   |Device_buffer_random|Buffer for random number generation in device authentication.|
 * |uint8[]   |keyData   |Buffer to hold key data for setting a key element.|
 * |uint8[]   |inputEncryptData|Buffer for data to be encrypted.|
 * |uint8     |inputEncryptDataLength|Holds the length of the encryption input data.|
 * |uint8[]   |resultData|Buffer to hold the result of an encryption or key element get operation.|
 * |uint32    |getCryptoKeyId|Stores the Crypto Driver key ID retrieved from a key info.|
 * |uint32    |getKeyElementId|Specifies the key element to be retrieved (e.g., CRYPTO_KE_MAC_KEY).|
 * |uint32    |getResultLength|Holds the length of the retrieved key element or proof.|
 * |uint8     |key_ID    |Stores the key identifier from the input data in a DECRYPT job.|
 * |uint8     |verifyresult|Stores the result of an AES-GCM tag verification.|
 * |uint8[]   |input_targetkey_value|Buffer for the encrypted target key in a DECRYPT job.|
 * |uint8[]   |tag       |Buffer for the authentication tag in an AES-GCM DECRYPT job.|
 * |uint8[]   |shekey_value|Buffer to store the decrypted SHE key.|
 * |uint8[]   |buffer_M1_M5|Buffer to store the generated M1-M5 messages for SHE key updates.|
 * |uint8[]   |publickey_value|Buffer to store the decrypted public key.|
 * |uint32    |input_targetkey_length|Holds the length of the encrypted target key.|
 * |uint32    |taglength |Holds the length of the GCM authentication tag.|
 * |uint32    |shekey_length|Holds the length of the decrypted SHE key.|
 * |uint32    |buffer_M1_M5_length|Holds the length of the M1-M5 message buffer.|
 * |uint32    |publickey_length|Holds the length of the decrypted public key.|
 * @brief     Acts as a dispatcher for custom cryptographic jobs. It processes requests for random number generation, hashing, encryption, and decryption based on the service specified in the input job structure. This function handles various custom protocols, including lifecycle management (RMA, Secure Transition), SHE key updates, and device authentication.
 * @note      This function is the central processing unit for all custom vHSM services. It is called from the generic `Crypto_30_vHsm_ProcessJob` function when the target CryptoDriverObject is the custom driver. The input `job` pointer must be valid and correctly populated by the caller (CSM).
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
FUNC(Std_ReturnType, VHSM_CUSTOM_CODE) vHsm_Custom_ProcessJob( /* COV_VHSM_CUSTOM_NOTUSED */
  uint32 objectId, /* PRQA S 3206 */ /* MD_VHSM_CUSTOM_UNUSED_PARAMETER */
  P2VAR(Crypto_JobType, AUTOMATIC, VHSM_CUSTOM_APPL_VAR) job)  /* PRQA S 3206 */ /* MD_VHSM_CUSTOM_UNUSED_PARAMETER */
{
  /* Special functionality can be implemented here.
   * The function is executed when Crypto_30_vHsm_ProcessJob() is called with the Custom driver used as CryptoDriverObject.
   * Custom algorithm modes and families can be used to specify special functionalities or existing algorithms can be used.
   */
  Std_ReturnType retVal = E_OK;

  /* CRYPTO_RANDOM Variable */
  uint8 LifeCycleReqType;
  uint8 getStatus;
  uint8 RND_buffer[VHSM_CUSTOM_BUFFER_SIZE];
  uint8 temp_buffer[VHSM_CUSTOM_BUFFER_SIZE + 1u];
  uint8 MacKeyErr;

  RMAReturnStatus RMAResponse;
  SecureReturnStatus SecureResponse;
  DeviceAuthenRNDType retValStatus = DEVICEAUTHEN_E_OK;

  /* CRYPTO_HASH Variable */
  uint8 lifeCycleState;
  uint8 protectionState;

  PBKeyStatus respond = PBKEY_2K_3K_VALID;
  VerifyKeyType Key2KCheckingResult;
  VerifyKeyType Key3KCheckingResult;

  uint32 inputHashDataLength = SB_SIZE_PEM_2048;
  uint32 OutEncryptedCommonKeyLength = ENCRYPTED_KEYINFO_LENGTH;

  /* CRYPTO_ENCRYPT Variable */
  Std_ReturnType retval_crypto;
  
  uint8 Status_HSM = E_OK;
  uint8 getKeyLength = VHSM_CUSTOM_KEYSIZE;
  uint8 Device_buffer_random[VHSM_CUSTOM_DEVICE_AUTHEN_KEY_LENGTH_BUFFER_SIZE] = {0};
  uint8 keyData[VHSM_CUSTOM_KEYSIZE];
  uint8 inputEncryptData[VHSM_CUSTOM_INPUT_KEYSIZE];
  uint8 inputEncryptDataLength = VHSM_CUSTOM_INPUT_KEYSIZE;
  uint8 resultData[VHSM_CUSTOM_KEYSIZE];
  
  uint32 getCryptoKeyId;
  uint32 getKeyElementId = CRYPTO_KE_MAC_KEY;
  uint32 getResultLength = VHSM_CUSTOM_KEYSIZE;
  
  /* CRYPTO_DECRYPT Variable */
  uint8 key_ID;
  uint8 verifyresult = E_OK;

  uint8 tag[VHSM_CUSTOM_TAG_LENGTH] = {0};
  uint8 shekey_value[VHSM_CUSTOM_SHE_KEY_SIZE_MAX] = {0};
  uint8 buffer_M1_M5[VHSM_CUSTOM_SIZEOF_SHE_M1_M5] = {0};
  
  uint32 input_targetkey_length = 0u;
  uint32 taglength = VHSM_CUSTOM_TAG_LENGTH;
  uint32 shekey_length;
  uint32 buffer_M1_M5_length = VHSM_CUSTOM_SIZEOF_SHE_M1_M5;
  uint32 publickey_length;
  
  /* Memset to zero before using */
  VStdLib_MemSet(inputHashData, 0, sizeof(inputHashData));
  VStdLib_MemSet(OutEncryptedCommonKey, 0, sizeof(OutEncryptedCommonKey));
  VStdLib_MemSet(publickey_value, 0, sizeof(publickey_value));
  VStdLib_MemSet(input_targetkey_value, 0, sizeof(input_targetkey_value));

 /* QAC Deviations: (No 2814) Configuration and Generation rule of Crypto module is made sure the no NULL_PTR occured */
  switch(job->jobPrimitiveInfo->primitiveInfo->service)
  {
  /* CRYPTO_RANDOM Job */
  /* Perform for Server Challenge Request Process Flow */
  case CRYPTO_RANDOM:
    if (job->jobPrimitiveInfo->primitiveInfo->algorithm.family == CRYPTO_ALGOFAM_RNG)
    {
      if (job->jobPrimitiveInfo->primitiveInfo->algorithm.mode == CRYPTO_ALGOMODE_NOT_SET)
      {
        retVal |= vHsm_Custom_CMD_INIT_RND();
        retVal |= vHsm_Custom_CMD_EXTEND_SEED();
        retVal |= vHsm_Custom_CMD_RND(RND_buffer);
        retVal |= vHsm_Custom_She_Cmd_Get_Status(&getStatus);
        if (retVal == E_OK)
        {
          VStdLib_MemCpy(temp_buffer, RND_buffer, VHSM_CUSTOM_BUFFER_SIZE);
          temp_buffer[VHSM_CUSTOM_BUFFER_SIZE] = getStatus;
          VStdLib_MemCpy(job->jobPrimitiveInputOutput.outputPtr, temp_buffer, VHSM_CUSTOM_BUFFER_SIZE + 1u);
          /* QAC Deviations: (No 2814) Configuration and Generation rule of Crypto module is made sure the no NULL_PTR occured */
          *job->jobPrimitiveInputOutput.outputLengthPtr = VHSM_CUSTOM_BUFFER_SIZE + 1u;
        }
        else
        {
          retVal = E_NOT_OK;
        }
      }
      else if (job->jobPrimitiveInfo->primitiveInfo->algorithm.mode == CRYPTO_ALGOMODE_CTRDRBG)
      {
        retVal = vHsm_Custom_CheckMacKey(&MacKeyErr);
        if (retVal == E_OK)
        {
          /* QAC Deviation (No. 2824): The job is a static code generated by the CSM module. Therefore, the job pointer always differs from NULL  */
          job->jobPrimitiveInputOutput.outputPtr[0] = MacKeyErr;
          *job->jobPrimitiveInputOutput.outputLengthPtr = 16u;
        }
        else
        {
          retVal = E_NOT_OK;
        }
      }
      else
      {
        retVal = E_NOT_OK;
      }
    }
    else
    {
      retVal = E_NOT_OK;
    }
    break;
  
  /* CRYPTO_HASH Job */
  case CRYPTO_HASH:
    if (job->jobPrimitiveInfo->primitiveInfo->algorithm.family == CRYPTO_ALGOFAM_SHA1)
    {
      if (job->jobPrimitiveInfo->primitiveInfo->algorithm.mode == CRYPTO_ALGOMODE_NOT_SET)
      {
        retVal = ClearKeyInfoBeforeRma();
      }
      else
      {
        retVal = E_NOT_OK;
      }
    }
    else if (job->jobPrimitiveInfo->primitiveInfo->algorithm.family == CRYPTO_ALGOFAM_SHA2_224)
    {
      if (job->jobPrimitiveInfo->primitiveInfo->algorithm.mode == CRYPTO_ALGOMODE_NOT_SET)
      {
          /* QAC Deviation (No. 2824): The job is a static code generated by the CSM module. Therefore, the job pointer always differs from NULL  */
          LifeCycleReqType = job->jobPrimitiveInputOutput.inputPtr[REQ_TYPE_IDX];

          if ((LifeCycleReqType == TRANSITION_RMA_REQ) || (LifeCycleReqType == OPEN_RMA_REQ))
          {
            /* QAC Deviations: (No 3383) Configuration and Generation rule of Csm module is made sure the overflow does not occur. */
            RMAResponse = HandleRmaRequest(
              LifeCycleReqType,
              (job->jobPrimitiveInputOutput.inputPtr + SIGNATURE_START_IDX),
              (uint8)(job->jobPrimitiveInputOutput.inputLength - REQ_TYPE_LENGTH)
            );
            job->jobPrimitiveInputOutput.outputPtr[0] = (uint8)RMAResponse;             
          }
          else if (LifeCycleReqType == TRANSITION_SECURE_REQ)
          {
            SecureResponse = HandleTransitionSecure();
            job->jobPrimitiveInputOutput.outputPtr[0] = (uint8)SecureResponse; 
          }
          else if (LifeCycleReqType == TRANSITION_SECURE_W_DEBUG_REQ)
          {
            SecureResponse = HandleTransitionSecureWithDebug();
            job->jobPrimitiveInputOutput.outputPtr[0] = (uint8)SecureResponse; 
          }
          else
          {
            retVal = E_NOT_OK;
          }
      }
      else
      {
        retVal = E_NOT_OK;
      }
    }
    else if (job->jobPrimitiveInfo->primitiveInfo->algorithm.family == CRYPTO_ALGOFAM_SHA2_256)
    {
      if (job->jobPrimitiveInfo->primitiveInfo->algorithm.mode == CRYPTO_ALGOMODE_NOT_SET)
      {
        if(job->jobPrimitiveInputOutput.inputPtr[REQ_TYPE_IDX] == READ_STAGE)
        {
          retVal = HandleReadStage(&lifeCycleState, &protectionState);
          job->jobPrimitiveInputOutput.outputPtr[0] = lifeCycleState;
          job->jobPrimitiveInputOutput.outputPtr[1] = protectionState;
        }
        else if(job->jobPrimitiveInputOutput.inputPtr[REQ_TYPE_IDX] == CHECK_PUBLIC_KEY)
        {
          Key2KCheckingResult = HandleCheckPBKey(KEY_2K);
          Key3KCheckingResult = HandleCheckPBKey(KEY_3K);
          if(Key2KCheckingResult == INVALID)
          {
            respond |= PBKEY_2K_INVALID;
          }
          if(Key3KCheckingResult == INVALID)
          {
            respond |= PBKEY_3K_INVALID;
          }
          job->jobPrimitiveInputOutput.outputPtr[0] = (uint8)respond;
        }
        else
        {
          retVal = E_NOT_OK;
        }
      }
      else
      {
        retVal = E_NOT_OK;
      }
    }
    else if (job->jobPrimitiveInfo->primitiveInfo->algorithm.family == CRYPTO_ALGOFAM_SHA2_384)
    {
      if (job->jobPrimitiveInfo->primitiveInfo->algorithm.mode == CRYPTO_ALGOMODE_NOT_SET)
      {
          VStdLib_MemCpy(inputHashData, job->jobPrimitiveInputOutput.inputPtr, inputHashDataLength);
          retVal = GetEncryptedCommonKey_Info(inputHashData, inputHashDataLength, OutEncryptedCommonKey, &OutEncryptedCommonKeyLength);
          if (retVal == E_OK)
          {
            VStdLib_MemCpy(job->jobPrimitiveInputOutput.outputPtr, OutEncryptedCommonKey, OutEncryptedCommonKeyLength);
            *job->jobPrimitiveInputOutput.outputLengthPtr = OutEncryptedCommonKeyLength;
          }
      }
      else
      {
        retVal = E_NOT_OK;
      }
    }
    else
    {
      retVal = E_NOT_OK;
    }
    break;
    
    /* CRYPTO_ENCRYPT Job */
    case CRYPTO_ENCRYPT:
      /* Custom Job Async Mode for D101 */
      if (job->jobPrimitiveInfo->primitiveInfo->algorithm.family == CRYPTO_ALGOFAM_AES)
      {
        if (job->jobPrimitiveInfo->primitiveInfo->algorithm.mode == CRYPTO_ALGOMODE_NOT_SET)
        {
          VStdLib_MemCpy(inputEncryptData, job->jobPrimitiveInputOutput.inputPtr, inputEncryptDataLength);
          /* QAC Deviations: (No 2844) vHsm_GetCryptoKeyIdOfKeyInfo is static code from Vector.So, keyIdx always generated by default.
           This warning can ignore */
          getCryptoKeyId = vHsm_GetCryptoKeyIdOfKeyInfo(inputEncryptData[VHSM_CUSTOM_KEYSIZE]);

          VStdLib_MemCpy(keyData, inputEncryptData, getKeyLength);

          retval_crypto = Crypto_30_LibCv_KeyElementSet(getCryptoKeyId, getKeyElementId, keyData, (uint32)getKeyLength);

          if (retval_crypto == E_OK)
          {
            retval_crypto = Crypto_30_LibCv_KeyValidSet(getCryptoKeyId);
            if (retval_crypto == E_OK)
            {
              retval_crypto = Crypto_30_LibCv_KeyElementGet(getCryptoKeyId, CRYPTO_KE_MAC_PROOF, resultData, &getResultLength);
              if ((retval_crypto != E_OK))
              {
                retval_crypto = Crypto_30_LibCv_KeyElementGet(getCryptoKeyId, CRYPTO_KE_CIPHER_PROOF, resultData, &getResultLength);
                if (retval_crypto == E_OK)
                {
                  VStdLib_MemCpy(job->jobPrimitiveInputOutput.outputPtr, resultData, getResultLength);
                  *job->jobPrimitiveInputOutput.outputLengthPtr = getResultLength;
                }
                else
                {
                  retVal = retval_crypto;
                }
              }
              else
              {
                VStdLib_MemCpy(job->jobPrimitiveInputOutput.outputPtr, resultData, getResultLength);
                *job->jobPrimitiveInputOutput.outputLengthPtr = getResultLength;
              }
            }
            else
            {
              retVal = retval_crypto;
            }
          }
          else
          {
            retVal = retval_crypto;
          }
        }
      }
      else if (job->jobPrimitiveInfo->primitiveInfo->algorithm.family == CRYPTO_ALGOFAM_RSA)
      {
        if (job->jobPrimitiveInfo->primitiveInfo->algorithm.mode == CRYPTO_ALGOMODE_NOT_SET)
        {
          retValStatus = vHsm_Custom_DeviceAuthen_GenerateRandom(CsmConf_CsmKey_CsmKey_DeviceAuthen_SessionKey, 
                                                        CsmConf_CsmKey_CsmKey_DeviceAuthen_RandomNumber, 
                                                        Device_buffer_random, 
                                                        &Status_HSM);
        }
        else if (job->jobPrimitiveInfo->primitiveInfo->algorithm.mode == CRYPTO_ALGOMODE_CBC)
        {
          retValStatus = vHsm_Custom_DeviceAuthen_GenerateRandom(CsmConf_CsmKey_CsmKey_WiredRepro_SessionKey, 
                                            CsmConf_CsmKey_CsmKey_WiredRepro_RandomNumber, 
                                            Device_buffer_random, 
                                            &Status_HSM);
        }
        else
        {
          retVal = E_NOT_OK;
        }

        if ((retValStatus == DEVICEAUTHEN_E_OK) && 
        ((job->jobPrimitiveInfo->primitiveInfo->algorithm.mode == CRYPTO_ALGOMODE_NOT_SET) || 
        (job->jobPrimitiveInfo->primitiveInfo->algorithm.family == CRYPTO_ALGOFAM_RSA)))
        {
          VStdLib_MemCpy(job->jobPrimitiveInputOutput.outputPtr, Device_buffer_random, 16u);
        }
        job->jobPrimitiveInputOutput.outputPtr[16] = Status_HSM;
        job->jobPrimitiveInputOutput.outputPtr[17] = (uint8)retValStatus;
        *job->jobPrimitiveInputOutput.outputLengthPtr = 18u;
      }
      else
      {
        retVal = E_NOT_OK;
      } 
      break;
    
    /* CRYPTO_DECRYPT Job */
    case CRYPTO_DECRYPT:
      if (job->jobPrimitiveInfo->primitiveInfo->algorithm.family == CRYPTO_ALGOFAM_AES)
      {
        /*get key length*/
        input_targetkey_length |= (uint32)(job->jobPrimitiveInputOutput.inputPtr[0]) << 24u;
        input_targetkey_length |= (uint32)(job->jobPrimitiveInputOutput.inputPtr[1]) << 16u;
        input_targetkey_length |= (uint32)(job->jobPrimitiveInputOutput.inputPtr[2]) << 8u;
        input_targetkey_length |= (uint32)(job->jobPrimitiveInputOutput.inputPtr[3]);

        /*get key id*/
        key_ID = job->jobPrimitiveInputOutput.inputPtr[VHSM_CUSTOM_KEY_LENGTH_SIZE];
        /*get tag*/
        VStdLib_MemCpy(tag, &(job->jobPrimitiveInputOutput.inputPtr[VHSM_CUSTOM_KEY_LENGTH_SIZE + VHSM_CUSTOM_KEY_ID_SIZE]), VHSM_CUSTOM_TAG_LENGTH);
        /*get value target key*/
        VStdLib_MemCpy(input_targetkey_value, &(job->jobPrimitiveInputOutput.inputPtr[VHSM_CUSTOM_KEY_LENGTH_SIZE + VHSM_CUSTOM_KEY_ID_SIZE + VHSM_CUSTOM_TAG_LENGTH]), input_targetkey_length);
        if (job->jobPrimitiveInfo->primitiveInfo->algorithm.mode == CRYPTO_ALGOMODE_NOT_SET)
        {
          /*Write she with data encrypt*/
          if (job->jobPrimitiveInfo->primitiveInfo->algorithm.secondaryFamily == CRYPTO_ALGOFAM_SHA1)
          {
            /*Job for gen M1-M5 she key*/
            /*Check key type*/
            if ((key_ID == VHSM_CUSTOM_SHE_KEY_TYPEX_ID) ||
                (key_ID == VHSM_CUSTOM_MASTER_ECU_KEY_ID) ||
                (key_ID == VHSM_CUSTOM_SHE_KEY_SECUREBOOT_ID) ||
                (key_ID == VHSM_CUSTOM_SHE_KEY_DEBUG_PORT_ID) ||
                (key_ID == VHSM_CUSTOM_SHE_KEY_REPROGRAMMING_ID))
            {
              /*Decrypt data*/
              retVal = vHsm_Custom_DecryptedKeytarget(input_targetkey_value, input_targetkey_length, tag, taglength, shekey_value, &shekey_length, &verifyresult);
              /*Gen M1-M5 */
              if (verifyresult == E_OK)
              {
                retVal = vHsm_Custom_SheKeyUpdateGen_M1_M5(key_ID, shekey_length, shekey_value, buffer_M1_M5, &buffer_M1_M5_length);
                /*Return data*/
                if (retVal == E_OK)
                {
                  VStdLib_MemCpy(job->jobPrimitiveInputOutput.outputPtr, buffer_M1_M5, VHSM_CUSTOM_SIZEOF_SHE_M1_M5);
                  *job->jobPrimitiveInputOutput.outputLengthPtr = buffer_M1_M5_length;
                }
                /*Return Hsm error*/
                else
                {
                  retVal = CRYPTO_E_KEY_GEN_M1_M5_FAIL;
                }
              }
              else
              {
                /*Return Hsm error*/
                if (retVal == CRYPTO_E_KEY_NOT_VALID)
                {
                  retVal = CRYPTO_E_KEY_DECRYPT_FAIL_COMMON_KEY_EMPTY;
                }
                /*Return Hsm error*/
                else
                {
                  retVal = CRYPTO_E_KEY_DECRYPT_FAIL;
                }
              }
            }
            /*Return Hsm error*/
            else
            {
              retVal = E_NOT_OK;
            }
          }
          /*Write she key with data not encrypt*/
          else if (job->jobPrimitiveInfo->primitiveInfo->algorithm.secondaryFamily == CRYPTO_ALGOFAM_SHA2_256)
          {
            /*Generate M1-M5 with raw data*/
            retVal = vHsm_Custom_SheKeyUpdateGen_M1_M5(key_ID, input_targetkey_length, input_targetkey_value, buffer_M1_M5, &buffer_M1_M5_length);
            /*Return data */
            if (retVal == E_OK)
            {
              VStdLib_MemCpy(job->jobPrimitiveInputOutput.outputPtr, buffer_M1_M5, VHSM_CUSTOM_SIZEOF_SHE_M1_M5);
              *job->jobPrimitiveInputOutput.outputLengthPtr = buffer_M1_M5_length;
            }
            /*Return Hsm error*/
            else
            {
              retVal = CRYPTO_E_KEY_GEN_M1_M5_FAIL;
            }
          }
          /*Return Hsm error*/
          else
          {
            retVal = E_NOT_OK;
          }
        }
        else if (job->jobPrimitiveInfo->primitiveInfo->algorithm.mode == CRYPTO_ALGOMODE_CBC)
        {
          /*Write public with data encrypt */
          if (job->jobPrimitiveInfo->primitiveInfo->algorithm.secondaryFamily == CRYPTO_ALGOFAM_SHA1)
          {
            /*Job for write public key*/
            if ((key_ID == VHSM_CUSTOM_PUBLIC_KEY_DEVICE_AUTHENTICATION_ID) ||
                (key_ID == VHSM_CUSTOM_PUBLIC_KEY_DEBUG_CONNECT_ID))
            {
              /*Decrypt data*/
              retVal = vHsm_Custom_DecryptedKeytarget(input_targetkey_value, input_targetkey_length, tag, taglength, publickey_value, &publickey_length, &verifyresult);
              /*Write public key*/
              if (verifyresult == E_OK)
              {
                retVal = vHsm_Custom_WritePublicKey(publickey_value, publickey_length, key_ID);
              }
              /*Return Hsm error*/
              else
              {
                /*Return Hsm error*/
                if (retVal == CRYPTO_E_KEY_NOT_VALID)
                {
                  retVal = CRYPTO_E_KEY_DECRYPT_FAIL_COMMON_KEY_EMPTY;
                }
                else
                {
                  retVal = CRYPTO_E_KEY_DECRYPT_FAIL;
                }
              }
            }
            /*Return Hsm error*/
            else
            {
              retVal = E_NOT_OK;
            }
          }
          /*Write public with data not encrypt */
          else if (job->jobPrimitiveInfo->primitiveInfo->algorithm.secondaryFamily == CRYPTO_ALGOFAM_SHA2_256)
          {
            retVal = vHsm_Custom_WritePublicKey(input_targetkey_value, input_targetkey_length, key_ID);
          }
          /*Return Hsm error*/
          else
          {
            retVal = E_NOT_OK;
          }
        }
        /*Return Hsm error*/
        else
        {
          retVal = E_NOT_OK;
        }
      }
      else
      {
        retVal = E_NOT_OK;
      }
        break;

      default:
        retVal = E_NOT_OK; // Function not supported
        break;
  }
  return retVal; /* COV_VHSM_CUSTOM_NOTUSED */
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint32    |objectId  |ID of the Crypto Driver Object being cancelled. Not used.|
 * |Crypto_JobType*|job |Pointer to the job structure to be cancelled. Not used.|
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |Std_ReturnType|-     |Always returns E_NOT_OK, as job cancellation is not supported.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
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
 * |-         |-         |-                 |
 * @brief     Handles requests to cancel a currently processing custom crypto job.
 * @note      This function is a required part of the AUTOSAR Crypto Interface, but custom core jobs cannot be cancelled. Therefore, it always returns an error.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
FUNC(Std_ReturnType, VHSM_CUSTOM_CODE) vHsm_Custom_CancelJob( /* COV_VHSM_CUSTOM_NOTUSED */
  uint32 objectId, /* PRQA S 3206 */ /* MD_VHSM_CUSTOM_UNUSED_PARAMETER */
  P2VAR(Crypto_JobType, AUTOMATIC, VHSM_CUSTOM_APPL_VAR) job) /* PRQA S 3206 */ /* MD_VHSM_CUSTOM_UNUSED_PARAMETER */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Return always with an error because core jobs can not be canceled */
  return E_NOT_OK; /* COV_VHSM_CUSTOM_NOTUSED */
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint32    |cryptoKeyId|The identifier of the crypto key where the element will be set.|
 * |uint32    |keyElementId|The identifier of the specific key element to set.|
 * |const uint8*|keyPtr  |Pointer to the buffer containing the data for the key element.|
 * |uint32    |keyLength |The length of the data in the keyPtr buffer.|
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |Std_ReturnType|retVal|Returns E_OK on success, or E_NOT_OK on failure (e.g., invalid cryptoKeyId).|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
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
 * |Std_ReturnType|retVal|Holds the return status of the operation.|
 * @brief     Sets the data of a specific element within a given cryptographic key. It acts as a custom handler.
 * @note      This function intercepts requests for specific key elements (e.g., `CryptoConf_CryptoKeyElement_CryptoKeyElement_TransitionToFblFlag`) to provide custom behavior. For all other key elements, it forwards the request to the underlying crypto library's handler `vHsm_KeyM_WriteOnceHandling_KeyElementSet`.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
FUNC(Std_ReturnType, VHSM_CUSTOM_CODE) vHsm_Custom_KeyElementSet(
  uint32 cryptoKeyId,
  uint32 keyElementId,
  P2CONST(uint8, AUTOMATIC, VHSM_CUSTOM_APPL_VAR) keyPtr,
  uint32 keyLength)
{
  Std_ReturnType retVal; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* Special functionality can be implemented here when specific key elements are requested.
   * The function is executed when Crypto_30_vHsm_KeyElementSet() is called with a key referenced as vHsmCustomKey in the vHsmKeyMapping.
   *
   * Example implementation:
   *
   * switch (keyElementId)
   * {
   * case CRYPTO_KE_CUSTOM_ToBeDefined1:
   *   // Perform custom operation1
   *   break;
   * case CRYPTO_KE_CUSTOM_ToBeDefined2:
   *   // Perform custom operation2
   *   break;
   * default:
   *   // No custom operation. Let the LibCv handle the request
   *   retVal = vHsm_KeyM_WriteOnceHandling_KeyElementSet(cryptoKeyId, keyElementId, keyPtr, keyLength);
   *   break;
   * }
   *
   */

  if(cryptoKeyId >= Crypto_30_LibCv_GetSizeOfKey())
  {
    retVal = E_NOT_OK;
  }
  else
  {
    if ((cryptoKeyId == CryptoConf_CryptoKey_CryptoKey_TransitionToFblFlag) && (keyElementId == CryptoConf_CryptoKeyElement_CryptoKeyElement_TransitionToFblFlag))
    {
      retVal = E_OK;
    }
    else
    {
      /* #100 If no custom element is requested, redirect the request to the Cryopto_30_LibCv */
      retVal = vHsm_KeyM_WriteOnceHandling_KeyElementSet(cryptoKeyId, keyElementId, keyPtr, keyLength);
    }
  }
  return retVal;
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint32    |cryptoKeyId|The identifier of the crypto key from which to get the element.|
 * |uint32    |keyElementId|The identifier of the specific key element to get.|
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |Std_ReturnType|retVal|Returns E_OK on success, or E_NOT_OK on failure.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint8* |resultPtr |Pointer to the buffer where the retrieved key element data will be stored.|
 * |uint32* |resultLengthPtr|Pointer to a variable that will be updated with the length of the retrieved data.|
 * @par       Reference variables
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |const uint8[]|vHsm_Custom_KeyMapping|Maps custom key IDs to CSM key configuration IDs to look up key flags.|
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
 * |Std_ReturnType|retVal|Holds the return status of the operation.|
 * |Crypto_30_LibCv_KeyFlagType|KeyFlags|Structure to hold the retrieved flags for a single key.|
 * |uint8     |i         |Loop counter for iterating through the key mapping.|
 * @brief     Retrieves the data of a specific element from a cryptographic key. It has special handling for a custom aggregated key attribute request.
 * @note      When called with `cryptoKeyId` matching `CryptoConf_CryptoKey_vHsm_Custom`, this function iterates through all keys defined in `vHsm_Custom_KeyMapping`, retrieves their individual protection flags (Write Protect, Debug Protect, etc.), packs these flags into a single byte for each key, and returns an array of these packed attribute bytes.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
FUNC(Std_ReturnType, VHSM_CUSTOM_CODE) vHsm_Custom_KeyElementGet(
  uint32 cryptoKeyId,
  uint32 keyElementId,
  P2VAR(uint8, AUTOMATIC, VHSM_CUSTOM_APPL_VAR) resultPtr,
  P2VAR(uint32, AUTOMATIC, VHSM_CUSTOM_APPL_VAR) resultLengthPtr)
{
  Std_ReturnType retVal = E_OK;
  Crypto_30_LibCv_KeyFlagType KeyFlags;
  uint8 i;

  (void)keyElementId;

  if(cryptoKeyId >= Crypto_30_LibCv_GetSizeOfKey())
  {
    retVal = E_NOT_OK;
  }
  else
  {
    if ((cryptoKeyId == CryptoConf_CryptoKey_vHsm_Custom) && (resultPtr != NULL_PTR) && (resultLengthPtr != NULL_PTR))
    {
      /* clear buffer */
      VStdLib_MemSet(resultPtr, 0u, VHSM_CUSTOM_TEN);
      for (i = VHSM_CUSTOM_ZERO; i < VHSM_CUSTOM_TEN; i++)
      {
        retVal = Crypto_30_LibCv_Api_GetKeyFlags((uint32)vHsm_Custom_KeyMapping[i], VHSM_CUSTOM_ONE, &KeyFlags);

        if (retVal == E_OK)
        {
            /*  Key Attr  */
            /* Bit Position: ||  7  |  6  |  5  |  4  |  3   | 2  | 1  |  0 ||
            * Key flags:     || WP  |  KU |  CU |  BP |  DP  | 0* | 0* | 0* ||
            * Note: * not use
            */
            resultPtr[i] |= (uint8)(KeyFlags.debugger_protection << 3u);
            resultPtr[i] |= (uint8)(KeyFlags.boot_protection << 4u);
            resultPtr[i] |= (uint8)(KeyFlags.cmac_usage << 5u);
            resultPtr[i] |= (uint8)(KeyFlags.key_usage << 6u);
            resultPtr[i] |= (uint8)(KeyFlags.write_protection << 7u);
            /* clear buffer */
            VStdLib_MemSet(&KeyFlags, 0u, sizeof(KeyFlags));
        }
        else
        {
          /* Do nothing */
        }
      }
      *resultLengthPtr = VHSM_CUSTOM_KEY_ATTR;
    }
    else
    {
      /* Do nothing */
    }
  }

  return retVal;
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
 * |Std_ReturnType|retVal|E_OK if successful, E_NOT_OK if any underlying CSM operation fails.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
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
 * |Std_ReturnType|retVal|Holds the return status of the operation.|
 * |uint32    |bufferSizePtr|Holds the size of the buffer for encryption, expected to be 16 bytes.|
 * |uint8[]   |keyBuff   |Buffer to hold the newly generated/encrypted seed.|
 * |uint8[]   |keyPtr_SEED|Buffer to hold the current value of the PRNG seed before encryption.|
 * |uint32    |getKeyLength|Variable to hold the length of key elements being get/set.|
 * |uint8     |SREG_RNG_INIT_Ptr|Variable to hold the RNG initialization status flag (1 for initialized).|
 * @brief     Initializes the seed and derives a key for the Pseudo-Random Number Generator (PRNG) as per SHE specification.
 * @note      This command must be called before `vHsm_Custom_CMD_RND` after every power cycle/reset. It derives the PRNG_SEED_KEY, generates the next PRNG_SEED, updates both PRNG_SEED and PRNG_STATE, and sets an internal flag indicating the RNG is initialized.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
 static FUNC(Std_ReturnType, VHSM_CUSTOM_CODE) vHsm_Custom_CMD_INIT_RND(void)
{
  Std_ReturnType retVal = E_OK;
  uint32 bufferSizePtr = VHSM_CUSTOM_BUFFER_SIZE;
  uint8 keyBuff[VHSM_CUSTOM_KEY_SIZE];
  uint8 keyPtr_SEED[VHSM_CUSTOM_KEY_SIZE];
  uint32 getKeyLength = VHSM_CUSTOM_KEY_SIZE;
  uint8 SREG_RNG_INIT_Ptr;

 /* PRNG_SEED_KEY = KDF(SECRET_KEY, PRNG_SEED_KEY_C) */
 /* Start the key derive job CsmJob_MAC_KEY_DERIVE */
  retVal |= (Std_ReturnType)Csm_JobKeyDerive(
      CsmConf_CsmJob_CsmJob_MAC_KEY_DERIVE,
      CsmConf_CsmKey_CsmKey_She_PRNG_SEED_KEY_C,
      CsmConf_CsmKey_CsmKey_She_PRNG_SEED_KEY);

  /* PRNG_SEED i = ENC ECB,PRNG_SEED_KEY(PRNG_SEED i-1) */
  /* get PRNG_SEED i-1 */
  retVal |= Csm_KeyElementGet(
    CsmConf_CsmKey_CsmKey_She_PRNG_SEED,
    CryptoConf_CryptoKeyElement_Crypto_30_LibCv_PRNG_SEED,
    keyPtr_SEED,
    &getKeyLength);
  /* Start the encryption job CsmJob_MAC_Encrypt_Seed */
  retVal |= Csm_Encrypt(
      CsmConf_CsmJob_CsmJob_MAC_Encrypt_Seed,
      CRYPTO_OPERATIONMODE_SINGLECALL,
      keyPtr_SEED,
      VHSM_CUSTOM_BUFFER_SIZE,
      keyBuff,
      &bufferSizePtr);
  
  retVal |= Csm_KeyElementSet(
      CsmConf_CsmKey_CsmKey_She_PRNG_SEED,
      CryptoConf_CryptoKeyElement_Crypto_30_LibCv_PRNG_SEED,
      keyBuff,
      getKeyLength);
  retVal |= Csm_KeySetValid(CsmConf_CsmKey_CsmKey_She_PRNG_SEED);
  /* The output has to be stored to PRNG_SEED first and must only be transferred to PRNG_STATE after completing the write transaction to PRNG_SEED. */
  /*  PRNG_STATE = PRNG_SEED  */
  retVal |= Csm_KeyElementSet(
      CsmConf_CsmKey_CsmKey_She_PRNG_STATE,
      CryptoConf_CryptoKeyElement_Crypto_30_LibCv_PRNG_STATE,
      keyBuff,
      getKeyLength);
  retVal |= Csm_KeySetValid(CsmConf_CsmKey_CsmKey_She_PRNG_STATE);

  VStdLib_MemSet(keyBuff, 0u, sizeof(keyBuff));

  if (retVal == E_OK)
  {
    /* set status initialization */
    SREG_RNG_INIT_Ptr = VHSM_CUSTOM_ONE;
    getKeyLength = 1u;
    retVal |= Csm_KeyElementSet(
        CsmConf_CsmKey_CsmKey_She_Info,
        CryptoConf_CryptoKeyElement_Crypto_30_LibCv_She_RND_INIT,
        &SREG_RNG_INIT_Ptr,
        getKeyLength);
    retVal |= Csm_KeySetValid(CsmConf_CsmKey_CsmKey_She_Info);
  }
  else
  {
    /* Do nothing */
  }

  return retVal;
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
 * |Std_ReturnType|retVal|E_OK if successful, E_NOT_OK if any underlying CSM or custom operation fails.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
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
 * |Std_ReturnType|retVal|Holds the return status of the operation.|
 * |uint8[]   |entropy   |Buffer to hold 128 bits of entropy from the hardware RNG.|
 * |uint8[]   |PRNG_STATE_Ptr|Buffer to hold the current value of the PRNG_STATE key element.|
 * |uint8[]   |PRNG_SEED_Ptr|Buffer to hold the current value of the PRNG_SEED key element.|
 * |uint32    |getKeyLength|Variable to hold the length of key elements being retrieved.|
 * @brief     Extends the PRNG seed by compressing the current seed and state with new entropy.
 * @note      This function must be called only after the PRNG has been initialized via `vHsm_Custom_CMD_INIT_RND`. It independently updates both the `PRNG_STATE` and `PRNG_SEED` by mixing each with newly gathered entropy using the Miyaguchi-Preneel one-way compression function (`vHsm_Custom_AESMP`).
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
 static FUNC(Std_ReturnType, VHSM_CUSTOM_CODE) vHsm_Custom_CMD_EXTEND_SEED(void)
{
  Std_ReturnType retVal = E_OK;
  uint8 entropy[VHSM_CUSTOM_BUFFER_SIZE];
  uint8 PRNG_STATE_Ptr[VHSM_CUSTOM_BUFFER_SIZE];
  uint8 PRNG_SEED_Ptr[VHSM_CUSTOM_BUFFER_SIZE];
  uint32 getKeyLength = VHSM_CUSTOM_KEY_SIZE;

  /* Get current PRNG_STATE */
  retVal |= Csm_KeyElementGet(
      CsmConf_CsmKey_CsmKey_She_PRNG_STATE,
      CryptoConf_CryptoKeyElement_Crypto_30_LibCv_PRNG_STATE,
      PRNG_STATE_Ptr,
      &getKeyLength);
  /* Get current PRNG_SEED */
  retVal |= Csm_KeyElementGet(
      CsmConf_CsmKey_CsmKey_She_PRNG_SEED,
      CryptoConf_CryptoKeyElement_Crypto_30_LibCv_PRNG_SEED,
      PRNG_SEED_Ptr,
      &getKeyLength);

  /* Get entropy */
  (void)esl_getBytesRNG(VHSM_CUSTOM_BUFFER_SIZE, entropy);
  /* PRNG_STATE = AES-MP(PRNG_STATE | ENTROPY) */
  retVal |= vHsm_Custom_AESMP(PRNG_STATE_Ptr, entropy, CsmConf_CsmJob_CsmJob_MAC_Extend_STATE, CsmConf_CsmKey_CsmKey_She_PRNG_STATE);
  /* clear buffer */
  VStdLib_MemSet(entropy, 0u, sizeof(entropy));
  VStdLib_MemSet(PRNG_STATE_Ptr, 0u, sizeof(PRNG_STATE_Ptr));

  /* Get entropy */
  (void)esl_getBytesRNG(VHSM_CUSTOM_BUFFER_SIZE, entropy);
  /* PRNG_SEED = AES-MP(PRNG_SEED | ENTROPY) */
  retVal |= vHsm_Custom_AESMP(PRNG_SEED_Ptr, entropy, CsmConf_CsmJob_CsmJob_MAC_Extend_SEED, CsmConf_CsmKey_CsmKey_She_PRNG_SEED);
  /* clear buffer */
  VStdLib_MemSet(entropy, 0u, sizeof(entropy));
  VStdLib_MemSet(PRNG_SEED_Ptr, 0u, sizeof(PRNG_SEED_Ptr));

  return retVal;
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint8* |RND       |(Output) Pointer to a buffer where the 128-bit random number will be stored.|
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |Std_ReturnType|retVal|E_OK if successful, E_NOT_OK if the RNG is not initialized or an error occurs.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint8* |RND       |Buffer is filled with the 16-byte generated random number.|
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
 * |Std_ReturnType|retVal|Holds the return status of the operation.|
 * |uint8[]   |PRNG_STATE_Ptr|Buffer to hold the current value of the PRNG_STATE key element.|
 * |uint8[]   |PRNG_STATE_BufferPlaintextPtr|Buffer to hold the generated random number (which is the new PRNG state).|
 * |uint8     |SREG_RNG_INIT|Flag to check if the RNG has been initialized.|
 * |uint32    |getKeyLength|Variable to hold the length of key elements being get/set.|
 * @brief     Generates a 128-bit random number according to the SHE specification.
 * @note      This function must be called only after the PRNG has been initialized via `vHsm_Custom_CMD_INIT_RND`. It generates the random number by encrypting the current PRNG state, and this result becomes both the output random number and the new PRNG state.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
 static FUNC(Std_ReturnType, VHSM_CUSTOM_CODE) vHsm_Custom_CMD_RND(
  P2VAR(uint8, AUTOMATIC, VHSM_CUSTOM_APPL_VAR) RND)
{
  Std_ReturnType retVal = E_OK;
  uint8 PRNG_STATE_Ptr[VHSM_CUSTOM_BUFFER_SIZE];
  uint8 PRNG_STATE_BufferPlaintextPtr[VHSM_CUSTOM_BUFFER_SIZE];

  uint8 SREG_RNG_INIT;

  uint32 getKeyLength = 1u;

  /* Get current RND_INIT */
  retVal |= Csm_KeyElementGet(
    CsmConf_CsmKey_CsmKey_She_Info,
    CryptoConf_CryptoKeyElement_Crypto_30_LibCv_She_RND_INIT,
    &SREG_RNG_INIT,
    &getKeyLength);

 getKeyLength = VHSM_CUSTOM_KEY_SIZE;
 if ((retVal == E_OK) && (SREG_RNG_INIT != VHSM_CUSTOM_ZERO))
 {
    /* Get current PRNG_STATE */
    retVal |= Csm_KeyElementGet(
      CsmConf_CsmKey_CsmKey_She_PRNG_STATE,
      CryptoConf_CryptoKeyElement_Crypto_30_LibCv_PRNG_STATE,
      PRNG_STATE_Ptr,
      &getKeyLength);

    retVal |= (Std_ReturnType)Csm_JobKeyDerive(
      CsmConf_CsmJob_CsmJob_MAC_KEY_DERIVE,
      CsmConf_CsmKey_CsmKey_She_PRNG_KEY_C,
      CsmConf_CsmKey_CsmKey_She_PRNG_KEY);

    /* Start the encryption job CsmJob_MAC_Encrypt_Seed */
    retVal |= Csm_Encrypt(
      CsmConf_CsmJob_CsmJob_MAC_Encrypt_STATE,
      CRYPTO_OPERATIONMODE_SINGLECALL,
      PRNG_STATE_Ptr,
      VHSM_CUSTOM_BUFFER_SIZE,
      PRNG_STATE_BufferPlaintextPtr,
      &getKeyLength);

    /* set new value to PRNG_STATE */
    retVal |= Csm_KeyElementSet(
      CsmConf_CsmKey_CsmKey_She_PRNG_STATE,
      CryptoConf_CryptoKeyElement_Crypto_30_LibCv_PRNG_STATE,
      PRNG_STATE_BufferPlaintextPtr,
      getKeyLength);
    retVal |= Csm_KeySetValid(CsmConf_CsmKey_CsmKey_She_PRNG_STATE);

    VStdLib_MemCpy(RND, PRNG_STATE_BufferPlaintextPtr, VHSM_CUSTOM_BUFFER_SIZE);
    VStdLib_MemSet(PRNG_STATE_BufferPlaintextPtr, 0u, sizeof(PRNG_STATE_BufferPlaintextPtr));
 }
 else
 {
   /* Do nothing */
 }

//  VStdLib_MemClr(SREG_RNG_INIT_Ptr, sizeof(SREG_RNG_INIT_Ptr));

 return retVal;
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint8* |inputA    |Pointer to the first input buffer for the XOR operation.|
 * |uint8* |inputB    |Pointer to the second input buffer for the XOR operation.|
 * |uint8* |output    |(Output) Pointer to the buffer where the result will be stored.|
 * |uint8     |size      |The number of bytes to XOR.|
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint8* |output    |Buffer is filled with the byte-wise XOR result of inputA and inputB.|
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
 * |uint8     |i         |Loop counter for iterating through bytes.|
 * |uint8     |j         |Index for accessing input and output arrays.|
 * |uint8     |aXORbBytes|Temporary variable to hold the result of a single byte XOR.|
 * @brief     Performs a byte-wise XOR operation between two input buffers of a given size.
 * @note      The function checks for NULL pointers before proceeding. The implementation iterates byte by byte, which is simple but may not be the most performant for large buffers.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
 static FUNC(void, VHSM_CUSTOM_CODE) vHsm_Custom_XorByte(
  uint8 *inputA,
  uint8 *inputB,
  uint8 * output,
  uint8 size)
{
  uint8 i = 0u;
  uint8 j = 0u;
  uint8 aXORbBytes;

  if((inputA != NULL_PTR) && (inputB != NULL_PTR) && (output != NULL_PTR))
  {
    /*QAC Deviations: (No 3383) j never overflow because i always check with size less than 255. 
      so, this warning can ignore and doesn't affect to the current behavior*/
    for(; i < size; i +=VHSM_CUSTOM_ONE_BYTE)
    {
      aXORbBytes = inputA[j] ^ inputB[j];
      VStdLib_MemCpyLarge(output + i, &aXORbBytes, VHSM_CUSTOM_ONE);
      j++;
    }
  }
  else
  {
    /* Do nothing */
  }
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint8* |dataPtr   |Pointer to the current state/data to be compressed.|
 * |uint8* |entropy   |Pointer to the entropy buffer to be mixed in.|
 * |uint8     |jobid     |The Csm Job ID to use for the encryption operations.|
 * |uint8     |keyid     |The Csm Key ID of the key to be updated (e.g., PRNG_STATE or PRNG_SEED).|
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |Std_ReturnType|retVal|E_OK if successful, E_NOT_OK if any underlying CSM operation fails.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
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
 * |Std_ReturnType|retVal|Holds the return status of the operation.|
 * |uint8[]   |AES_Result|Buffer to hold intermediate results of the compression.|
 * |uint8[]   |AES_key   |Buffer to hold the current value of the key being updated.|
 * |uint32    |getKeyLength|Variable to hold the length of key elements being get/set.|
 * |uint8[]   |bufferArr |Temporary buffer for XOR operations.|
 * |uint8[]   |entropy_BufferPlaintext|Buffer to hold the result of encrypting the entropy.|
 * @brief     Implements the Miyaguchi-Preneel one-way compression function using AES-ECB to update a key element with new entropy.
 * @note      This function performs a two-stage update. First, it compresses the input `dataPtr` with its current key value. Second, it compresses the result of the first stage with the provided `entropy`. The final result is written back to the key element specified by `keyid`.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
 static FUNC(Std_ReturnType, VHSM_CUSTOM_CODE) vHsm_Custom_AESMP(uint8 *dataPtr, uint8 *entropy, uint8 jobid, uint8 keyid)
{
  Std_ReturnType retVal = E_OK;
  uint8 AES_Result[VHSM_CUSTOM_BUFFER_SIZE];
  uint8 AES_key[VHSM_CUSTOM_BUFFER_SIZE];
  uint32 getKeyLength = VHSM_CUSTOM_KEY_SIZE;

  uint8 bufferArr[VHSM_CUSTOM_BUFFER_SIZE];
  uint8 entropy_BufferPlaintext[VHSM_CUSTOM_BUFFER_SIZE];

  /* Get current AES key */
  retVal |= Csm_KeyElementGet(
    (uint32)keyid,
    VHSM_CUSTOM_DEFAULT_KEY_ELEMENT_ID,
    AES_key,
    &getKeyLength);

  /* ENC ECB,OUTi-1(xi) */
  retVal |= Csm_Encrypt(
    (uint32)jobid,
    CRYPTO_OPERATIONMODE_SINGLECALL,
    dataPtr,
    VHSM_CUSTOM_BUFFER_SIZE,
    AES_Result,
    &getKeyLength);
  /* XOR:   ENC ECB,OUTi-1(xi) Xor xi Xor OUTi-1 */
  vHsm_Custom_XorByte(AES_Result, AES_key, bufferArr, VHSM_CUSTOM_BUFFER_SIZE);
  vHsm_Custom_XorByte(bufferArr, dataPtr, AES_Result, VHSM_CUSTOM_BUFFER_SIZE);

  /* set new value to AES key */
  retVal |= Csm_KeyElementSet(
    (uint32)keyid,
    VHSM_CUSTOM_DEFAULT_KEY_ELEMENT_ID,
    AES_Result,
    getKeyLength);
  retVal |= Csm_KeySetValid((uint32)keyid);

  if (retVal == E_OK)
  {
    /* ENC ECB,OUTi-1(xi) */
    retVal |= Csm_Encrypt(
      (uint32)jobid,
      CRYPTO_OPERATIONMODE_SINGLECALL,
      entropy,
      VHSM_CUSTOM_BUFFER_SIZE,
      entropy_BufferPlaintext,
      &getKeyLength);
    /* XOR:   ENC ECB,OUTi-1(xi) Xor xi Xor OUTi-1 */
    vHsm_Custom_XorByte(AES_Result, entropy_BufferPlaintext, bufferArr, VHSM_CUSTOM_BUFFER_SIZE);
    vHsm_Custom_XorByte(bufferArr, entropy, AES_Result, VHSM_CUSTOM_BUFFER_SIZE);

    /* set new value to AES key */
    retVal |= Csm_KeyElementSet(
      (uint32)keyid,
      VHSM_CUSTOM_DEFAULT_KEY_ELEMENT_ID,
      AES_Result,
      getKeyLength);
    retVal |= Csm_KeySetValid((uint32)keyid);
  }

  return retVal;
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint32    |sessionKeyId|CSM Key ID for the session key used to encrypt the random number.|
 * |uint32    |randomKeyId|CSM Key ID where the generated encrypted random number will be stored.|
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |DeviceAuthenRNDType|retVal|A detailed status code indicating success (DEVICEAUTHEN_E_OK) or the specific point of failure.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint8* |outRandomPtr|Pointer to a buffer where the raw (unencrypted) random number is stored.|
 * |uint8* |HsmStatus |Pointer to a variable that will be updated with the low-level `Std_ReturnType` status.|
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
 * |Std_ReturnType|getStatus|Holds the return status of individual CSM calls.|
 * |DeviceAuthenRNDType|retVal|Holds the final detailed return status of the function.|
 * |uint8[]   |key_temp  |Temporary buffer to hold the session key.|
 * |uint32    |key_len   |Variable to hold the length of the session key.|
 * |uint32    |seedLength|Variable to specify the desired length of the random number.|
 * |uint32    |resultLengthEncrypt|Variable to specify the length for the encryption output.|
 * |uint8[]   |RandomNumber|Buffer to hold the raw random number and the subsequent encrypted random number.|
 * |uint8[]   |key_dummy |Zeroed-out buffer used to clear the session key after use.|
 * |uint8     |length_buffer|Constant for the buffer size (32 bytes).|
 * @brief     Generates and encrypts a random number for device authentication.
 * @note      This function retrieves a session key, generates a 128-bit random number, encrypts the random number with the session key, stores the encrypted result in a specified key slot (`randomKeyId`), and then clears the session key. The raw (unencrypted) random number is returned via the `outRandomPtr`.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
static FUNC(DeviceAuthenRNDType, VHSM_CUSTOM_CODE) vHsm_Custom_DeviceAuthen_GenerateRandom(uint32 sessionKeyId, uint32 randomKeyId, uint8 *outRandomPtr, uint8 *HsmStatus)
{
  Std_ReturnType getStatus;
  DeviceAuthenRNDType retVal = DEVICEAUTHEN_E_OK;
  uint8 key_temp[VHSM_CUSTOM_DEVICE_AUTHEN_KEY_LENGTH]={0};
  uint32 key_len = VHSM_CUSTOM_DEVICE_AUTHEN_KEY_LENGTH;
  uint32 seedLength = VHSM_CUSTOM_DEVICE_AUTHEN_KEY_LENGTH;
  uint32 resultLengthEncrypt = VHSM_CUSTOM_DEVICE_AUTHEN_KEY_LENGTH;

  /*define buffer of random generate (first 16 byte) and encrypt random (16 byte) */
  uint8 RandomNumber[VHSM_CUSTOM_DEVICE_AUTHEN_KEY_LENGTH_BUFFER_SIZE] = {0u};

  uint8 key_dummy[VHSM_CUSTOM_DEVICE_AUTHEN_KEY_LENGTH] = {0};
  uint8 length_buffer = VHSM_CUSTOM_DEVICE_AUTHEN_KEY_LENGTH_BUFFER_SIZE;
  /* Session key acquisition process */
  getStatus = Csm_KeyElementGet(sessionKeyId, CryptoConf_CryptoKeyElement_Crypto_30_LibCv_AES_NISTSP80038A, key_temp, &key_len);
  
  if (getStatus == E_OK)
  {
      /* Set Session key to Encrypt job */
      getStatus = Csm_KeyElementSet(CsmConf_CsmKey_CsmKey_DeviceAuthen_Encrypt_RND, 
                                CryptoConf_CryptoKeyElement_Crypto_30_LibCv_AES_NISTSP80038A, 
                                key_temp, 
                                key_len);
      getStatus |= Csm_KeySetValid(CsmConf_CsmKey_CsmKey_DeviceAuthen_Encrypt_RND);
      /* generate random */
      getStatus |= Csm_RandomGenerate(CsmConf_CsmJob_CsmJob_DeviceAuthen_Random, &RandomNumber[0], &seedLength);
      if (getStatus == E_OK)
      {
          getStatus = Csm_Encrypt(CsmConf_CsmJob_CsmJob_DeviceAuthen_EncryptionSeed, CRYPTO_OPERATIONMODE_SINGLECALL, &RandomNumber[0], VHSM_CUSTOM_DEVICE_AUTHEN_KEY_LENGTH, &RandomNumber[16], &resultLengthEncrypt);
          if (getStatus == E_OK)
          {
              /* Store encrypted random number to RAM */
              getStatus = Csm_KeyElementSet(randomKeyId, \
                                  CryptoConf_CryptoKeyElement_Crypto_30_LibCv_AES_NISTSP80038A, &RandomNumber[16] , key_len);
              getStatus |= Csm_KeySetValid(randomKeyId);
              /* Copy raw random number to param out */
              VStdLib_MemCpy(outRandomPtr, &RandomNumber[0], length_buffer);
              /* Clear Session key */
              getStatus |= Csm_KeyElementSet(sessionKeyId, \
                              CryptoConf_CryptoKeyElement_Crypto_30_LibCv_AES_NISTSP80038A, key_dummy , key_len);
          }
          else
          {
              /* Encrypted random failed */
              retVal = DEVICEAUTHEN_E_ENC_RANDOM_FAILED;
          }
      }
      else
      {
          /* Random generate failed */
          retVal = DEVICEAUTHEN_E_RANDOM_FAILED;
      }
  }
  else
  {
      /* Session key not registered */
      retVal = DEVICEAUTHEN_E_SESSION_KEY_ERR;
  }
  *HsmStatus = getStatus; /* QAC Deviations: (No 2814) Pointer HsmStatus has been already evaluated at vHsm_Custom_ProcessJob() where this function was called. */

  return retVal;
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |const uint8*|PublicKeyPtr|Pointer to the PEM-encoded public key.|
 * |uint32    |PublicKeyLength|Length of the PEM-encoded public key.|
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |Std_ReturnType|retVal|E_OK on success, E_NOT_OK on failure, or CRYPTO_E_KEY_CONVERT_PEM_FAIL if PEM conversion fails.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint8* |OutCommonKeyPtr|Pointer to a buffer where the encrypted AES key info (key, IV, AAD) will be stored.|
 * |uint32* |OutCommonKeyLengthPtr|Pointer to a variable that will be updated with the length of the encrypted data.|
 * @par       Reference variables
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
 * @par       Output variables
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint8[]   |aad_Buffer|The global AAD buffer is updated with the randomly generated AAD.|
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
 * |uint8     |ConvertRetVal|Holds the return value from the PEM conversion utility.|
 * |Std_ReturnType|retVal|Holds the overall return status of the function.|
 * |uint8[]   |g_Random_KeyInfo_Buf|Buffer to hold the randomly generated AES key, IV, and AAD.|
 * |uint32    |g_Random_KeyInfo_Length|The length of the random key info buffer.|
 * |uint16    |auhModSiz_g|The size of the RSA modulus (2048 bits).|
 * |uint8[]   |aubModulus_g|Buffer to store the converted RSA modulus.|
 * |uint8[]   |aubPubExp_g|Buffer to store the converted RSA public exponent.|
 * @brief     Generates a random AES-GCM key bundle (key, IV, AAD), encrypts it with a provided RSA public key, and returns the encrypted bundle.
 * @note      This function is a key part of a factory key update process. It takes a public key in PEM format, converts it, generates a new symmetric key and its parameters, encrypts them using RSA-OAEP, and also stores the symmetric key parameters in a CSM key slot for later use in decryption.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
static Std_ReturnType GetEncryptedCommonKey_Info(const uint8 *PublicKeyPtr, uint32 PublicKeyLength, uint8 *OutCommonKeyPtr, uint32 *OutCommonKeyLengthPtr)
{
	uint8 ConvertRetVal;
	Std_ReturnType retVal;
	uint8 g_Random_KeyInfo_Buf[RANDOM_KEYINFO_LENGTH];
	uint32 g_Random_KeyInfo_Length = RANDOM_KEYINFO_LENGTH;
	uint16 auhModSiz_g = SB_SIZE_PK_LEN_2048;
	uint8 aubModulus_g[SB_SIZE_PK_LEN_2048];
	uint8 aubPubExp_g[SB_SIZE_PUBEXP];

	/* Convert public key */
	ConvertRetVal = nubSBSrGetPKfrmPEM(PublicKeyPtr, (uint16)PublicKeyLength, auhModSiz_g, aubModulus_g, aubPubExp_g);

	if(SB_RTN_OK == ConvertRetVal)
	{
		/* Write converted public key */
		retVal = Csm_KeyElementSet(CsmConf_CsmKey_CsmKey_FactoryKeyUpdate_Rsa_OAEP, \
							CryptoConf_CryptoKeyElement_Crypto_30_LibCv_Rsa_Modulus_2048, aubModulus_g, SB_SIZE_PK_LEN_2048);
		retVal |= Csm_KeyElementSet(CsmConf_CsmKey_CsmKey_FactoryKeyUpdate_Rsa_OAEP, \
							CryptoConf_CryptoKeyElement_Crypto_30_LibCv_Rsa_Pub_Exponent_2048, aubPubExp_g, SB_SIZE_PUBEXP);
		retVal |= Csm_KeySetValid(CsmConf_CsmKey_CsmKey_FactoryKeyUpdate_Rsa_OAEP);
		/* Random Aes Key Info */
		retVal |= Csm_RandomGenerate(
                    CsmConf_CsmJob_CsmJob_FactoryKeyUpdate_Random_KeyInfo_Aes_128_Gcm_Drbg,
                    g_Random_KeyInfo_Buf,
                    &g_Random_KeyInfo_Length);
    if ((E_OK == retVal) && (RANDOM_KEYINFO_LENGTH == g_Random_KeyInfo_Length))
    {
      /* Write Random Aes Key Info */
      retVal = Csm_KeyElementSet(CsmConf_CsmKey_CsmKey_FactoryKeyUpdate_Decrypt_AES_GCM, CryptoConf_CryptoKeyElement_Crypto_30_LibCv_AES_GCM_Common_Key, &g_Random_KeyInfo_Buf[AES_GCM_COMMONKEY_IDX], AES_GCM_COMMON_KEY_LENGTH);
      retVal |= Csm_KeyElementSet(CsmConf_CsmKey_CsmKey_FactoryKeyUpdate_Decrypt_AES_GCM, CryptoConf_CryptoKeyElement_Crypto_30_LibCv_AES_GCM_AAD, &g_Random_KeyInfo_Buf[AES_GCM_AAD_IDX], AES_GCM_AAD_LENGTH);
      retVal |= Csm_KeyElementSet(CsmConf_CsmKey_CsmKey_FactoryKeyUpdate_Decrypt_AES_GCM, CryptoConf_CryptoKeyElement_Crypto_30_LibCv_AES_GCM_IV, &g_Random_KeyInfo_Buf[AES_GCM_IV_IDX], AES_GCM_IV_LENGTH);
      Crypto_30_LibCv_CopyData(aad_Buffer, &g_Random_KeyInfo_Buf[AES_GCM_AAD_IDX], AES_GCM_AAD_LENGTH);

      retVal |= Csm_KeySetValid(CsmConf_CsmKey_CsmKey_FactoryKeyUpdate_Decrypt_AES_GCM);

      /* Encrypt Random Aes Key Info */
      retVal |= Csm_Encrypt(
            CsmConf_CsmJob_CsmJob_FactoryKeyUpdate_OAEP_Encrypt,
            CRYPTO_OPERATIONMODE_SINGLECALL,
            g_Random_KeyInfo_Buf,
            g_Random_KeyInfo_Length,
            OutCommonKeyPtr,
            OutCommonKeyLengthPtr);
    }
	}
  else
  {
    retVal = CRYPTO_E_KEY_CONVERT_PEM_FAIL;
  }
	return retVal;
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |const uint8*|EncryptedTargetKeyPtr|Pointer to the buffer containing the encrypted key data (ciphertext).|
 * |uint32    |EncryptedTargetKeyLength|Length of the ciphertext.|
 * |uint8* |InTagPtr  |Pointer to the buffer containing the AES-GCM authentication tag.|
 * |uint32    |InTaglength|Length of the authentication tag.|
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |Std_ReturnType|retVal|Returns the status from the Csm_AEADDecrypt operation (E_OK or E_NOT_OK).|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint8* |OutTargetKeyPtr|Pointer to the buffer where the decrypted key data (plaintext) will be stored.|
 * |uint32* |OutTargetKeyLengthPtr|Pointer to a variable that will be updated with the length of the plaintext.|
 * |uint8* |VerifyResult|Pointer to a variable that will be updated with the tag verification result (E_OK for success, E_NOT_OK for failure).|
 * @par       Reference variables
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint8[]   |aad_Buffer|The global Additional Authenticated Data (AAD) buffer is read for the decryption operation.|
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
 * |Std_ReturnType|retVal|Holds the return status from CSM calls.|
 * |Std_ReturnType|result_Decrypt|Stores the specific tag verification result from the AEAD decrypt call.|
 * |uint32    |keylength_decrypt|Holds the allocated size for the decryption output buffer.|
 * |uint32    |aad_length|Variable to hold the length of the AAD.|
 * @brief     Decrypts an encrypted key using AES-GCM and verifies its authentication tag.
 * @note      This function uses the AES-GCM key and parameters previously stored in the `CsmConf_CsmKey_CsmKey_FactoryKeyUpdate_Decrypt_AES_GCM` key slot. The AAD is retrieved from a global buffer. The function outputs both the decrypted plaintext and the result of the tag verification.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
static FUNC(Std_ReturnType, VHSM_CUSTOM_CODE) vHsm_Custom_DecryptedKeytarget ( 
  const uint8 *EncryptedTargetKeyPtr, 
  uint32 EncryptedTargetKeyLength, 
  uint8  *InTagPtr,
  uint32  InTaglength,
  uint8  *OutTargetKeyPtr, 
  uint32 *OutTargetKeyLengthPtr, 
  uint8  *VerifyResult)
{
  Std_ReturnType retVal;
  Std_ReturnType result_Decrypt = E_OK;
  /* QAC Deviations: (No 3383) The warning is related to the key length check. However, the KeyLength is always less than VHSM_CUSTOM_KEY_DECRYPTED_LENGTH_MAX, 
    and this condition doesn't occured overflow. This warning already covered by SQT and SIT for safe*/
  uint32 keylength_decrypt = EncryptedTargetKeyLength + VHSM_CUSTOM_AESGCM_MAX_OUT_SIZE;
  uint32  aad_length = VHSM_CUSTOM_AAD_LENGTH;
  retVal = Csm_KeyElementGet(CsmConf_CsmKey_CsmKey_FactoryKeyUpdate_Decrypt_AES_GCM, CryptoConf_CryptoKeyElement_Crypto_30_LibCv_AES_GCM_AAD, aad_Buffer, &aad_length);
  /*Decrypt data*/
  retVal |= Csm_AEADDecrypt(CsmConf_CsmJob_CsmJob_FactoryKeyUpdate_Decrypt_AES_GCM, 
                              CRYPTO_OPERATIONMODE_SINGLECALL, 
                              EncryptedTargetKeyPtr, 
                              EncryptedTargetKeyLength, 
                              aad_Buffer, 
                              VHSM_CUSTOM_AAD_LENGTH, 
                              InTagPtr, 
                              InTaglength, 
                              OutTargetKeyPtr, 
                              &keylength_decrypt, 
                              &result_Decrypt);
  if (result_Decrypt != E_OK)
  {  
      VStdLib_MemSet(OutTargetKeyPtr, 0u, keylength_decrypt);
  }
  *OutTargetKeyLengthPtr = keylength_decrypt; /* QAC Deviations: (No 2814) Pointer OutTargetKeyLengthPtr has been already evaluated at vHsm_Custom_ProcessJob() where this function was called. */
  *VerifyResult = result_Decrypt ; /* QAC Deviations: (No 2814) Pointer OutTargetKeyLengthPtr has been already evaluated at vHsm_Custom_ProcessJob() where this function was called. */
  return retVal;
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |const uint8*|EncryptedTargetKeyPtr|Pointer to the buffer containing the key data in PEM format.|
 * |uint32    |EncryptedTargetKeyLength|Length of the key data.|
 * |uint8     |KeyID     |The custom identifier for the public key being written.|
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |Std_ReturnType|retVal|E_OK on success, E_NOT_OK on failure, or CRYPTO_E_KEY_CONVERT_PEM_FAIL if PEM conversion fails.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
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
 * |Std_ReturnType|retVal|Holds the return status of the operation.|
 * |uint8     |ConvertRetVal|Holds the return status from the PEM conversion utility.|
 * |uint16    |auhModSiz_g|The size of the RSA modulus (3072 bits).|
 * |uint16    |pk1_convert_Pem_length|The size of the converted EC public key.|
 * @brief     Converts a public key from PEM format and writes it to the appropriate NvM-backed CSM key slot.
 * @note      This function acts as a dispatcher based on the provided `KeyID`. It handles writing the public key for Device Authentication (EC P-256) and the Debug Connect (RSA-3072) feature.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
static FUNC(Std_ReturnType, VHSM_CUSTOM_CODE) vHsm_Custom_WritePublicKey(
  const uint8 *EncryptedTargetKeyPtr, 
  uint32 EncryptedTargetKeyLength, 
  uint8  KeyID)
{
  /* QAC Deviations: (No 2981) retVal use for return. It should be set with default value*/
  volatile Std_ReturnType retVal = E_NOT_OK;
  uint8 ConvertRetVal;  
	uint16 auhModSiz_g = SB_SIZE_PK_LEN_3072;
  uint16 pk1_convert_Pem_length = VHSM_CUSTOM_PK1_SIZE;
    switch (KeyID)
    {
    case VHSM_CUSTOM_PUBLIC_KEY_DEVICE_AUTHENTICATION_ID:
      /*decrypt key pem*/
      ConvertRetVal = nubSBSrGetEcPKfrmPEM(EncryptedTargetKeyPtr, (uint16)EncryptedTargetKeyLength, pk1_convert_Pem, (uint16 *)&pk1_convert_Pem_length);
      if( SB_RTN_OK ==  ConvertRetVal)
      {
        /*write pk1 to NvM*/
        retVal = Csm_KeyElementSet(CsmConf_CsmKey_CsmKey_DeviceAuthen_Signature_Nist_Sec_P256R1_Verify, \
                                    CryptoConf_CryptoKeyElement_Crypto_30_LibCv_PublicKey_Nist_Sec_P256R1, pk1_convert_Pem, (uint32)pk1_convert_Pem_length);

        retVal |= Csm_KeySetValid(CsmConf_CsmKey_CsmKey_DeviceAuthen_Signature_Nist_Sec_P256R1_Verify);
      }
      else
      {
        retVal = CRYPTO_E_KEY_CONVERT_PEM_FAIL;
      }
      break;
    case VHSM_CUSTOM_PUBLIC_KEY_DEBUG_CONNECT_ID:
      /*decrypt key pem*/
      ConvertRetVal = nubSBSrGetPKfrmPEM(EncryptedTargetKeyPtr, (uint16)EncryptedTargetKeyLength, auhModSiz_g, aubModulus_g_key_connection, aubPubExp_g_key_connection);
      if( SB_RTN_OK ==  ConvertRetVal)
      {
        /*write pk-debug port to NvM*/
        retVal = Csm_KeyElementSet(CsmConf_CsmKey_CsmKey_SerialPortSecurity_SignatureVerify, \
                                    CryptoConf_CryptoKeyElement_Crypto_30_LibCv_Rsa_Modulus_SerialPort, aubModulus_g_key_connection, SB_SIZE_PK_LEN_3072);
        retVal |= Csm_KeyElementSet(CsmConf_CsmKey_CsmKey_SerialPortSecurity_SignatureVerify, \
                                    CryptoConf_CryptoKeyElement_Crypto_30_LibCv_Rsa_Pub_Exponent_SerialPort, aubPubExp_g_key_connection, SB_SIZE_PUBEXP);

        retVal |= Csm_KeySetValid(CsmConf_CsmKey_CsmKey_SerialPortSecurity_SignatureVerify);
      }
      else
      {
        retVal = CRYPTO_E_KEY_CONVERT_PEM_FAIL;
      }
      break;
    default:
      break;
    }
  return retVal;
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |const uint8*|dataPtr |Pointer to the input data for the CMAC calculation.|
 * |uint32    |length    |Length of the input data.|
 * |const uint8*|keyPtr  |Pointer to the 128-bit key for the CMAC calculation.|
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |Std_ReturnType|retVal|E_OK on success, E_NOT_OK on failure.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint8* |outputPtr |Pointer to the buffer where the 16-byte CMAC result will be stored.|
 * |eslt_WorkSpaceCMACAES*|workspace|(Input/Output) Pointer to the workspace required for the CMAC operation.|
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
 * |Std_ReturnType|retVal|Holds the return status of the operation.|
 * @brief     Calculates an AES-128 CMAC for the given data and key.
 * @note      This function is a wrapper around the `esl_` library functions for CMAC. It initializes a workspace, updates it with the input data, and finalizes the calculation to produce the CMAC tag.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
static FUNC( Std_ReturnType, CRYPTO_30_LIBCV_CODE ) vHsm_Custom_SheKeyUpdateCmac(
  P2CONST( uint8, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR ) dataPtr,
  uint32 length,
  P2CONST( uint8, AUTOMATIC, AUTOMATIC ) keyPtr,
  P2VAR( uint8, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR ) outputPtr,
  P2VAR(eslt_WorkSpaceCMACAES, AUTOMATIC, CRYPTO_30_LIBCV_CRYPTOCV_APPL_VAR) workspace)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 Init work space */
  if (esl_initWorkSpaceHeader(&workspace->header, /* SBSW_CRYPTO_30_LIBCV_INIT_ESL_STACK_WORKSPACE */ /* QAC Deviations: (No 2814) Pointer workspace has been already evaluated at vHsm_Custom_SheKeyExport_M1M2M3() where this function was called. */
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
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |const uint8*|dataPtr |Pointer to the plaintext data to be encrypted.|
 * |const uint8*|keyPtr  |Pointer to the 128-bit encryption key.|
 * |uint8     |numberOfBlocks|The number of 16-byte blocks to encrypt.|
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |Std_ReturnType|retVal|E_OK on success, E_NOT_OK on failure.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint8* |outputPtr |Pointer to the buffer where the ciphertext will be stored.|
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
 * |Std_ReturnType|retVal|Holds the return status of the operation.|
 * |eslt_ErrorCode|eslRet|Holds the return code from `esl_` library functions.|
 * |eslt_WorkSpaceAES128|workSpaceAes128|Workspace memory required by the AES library.|
 * |eslt_Length|outLength|Variable to track the length of the output data.|
 * |eslt_Length|written  |Variable to track the number of bytes written to the output.|
 * @brief     Encrypts one or more blocks of data using AES-128 in CBC mode with a zero IV.
 * @note      This is a helper function for the SHE key update protocol. It uses the underlying `esl_` crypto library to perform the encryption. Padding is disabled, so the input data length must be a multiple of the block size (16 bytes).
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
static FUNC(Std_ReturnType, CRYPTO_30_LIBCV_CODE) vHsm_Custom_SheKeyUpdateEncrypt(
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) dataPtr,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) keyPtr,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) outputPtr,
  uint8 numberOfBlocks)
{
  Std_ReturnType retVal = E_NOT_OK;
  eslt_ErrorCode eslRet;
  eslt_WorkSpaceAES128 workSpaceAes128;
  /* QAC Deviations: (No 3383) the number block is 1/2 and the size CRYPTO_30_LIBCV_AES_BLOCK_SIZE is 16. So, the issue overflow never occur.*/
  eslt_Length outLength = (eslt_Length)((eslt_Length)(numberOfBlocks) * CRYPTO_30_LIBCV_AES_BLOCK_SIZE);
  eslt_Length written;

  /* #10 Init work space */
  eslRet = esl_initWorkSpaceHeader((P2VAR(eslt_WorkSpaceHeader, AUTOMATIC, CRYPTO_30_LIBCV_CRYPTOCV_APPL_VAR))&(workSpaceAes128.header), /* SBSW_CRYPTO_30_LIBCV_INIT_ESL_STACK_WORKSPACE */
                                   ESL_MAXSIZEOF_WS_AES128,
                                   CRYPTO_30_LIBCV_WATCHDOG_PTR);

  /* #15 Init AES encryption */
  if (eslRet == ESL_ERC_NO_ERROR)
  {
    eslRet = esl_initEncryptAES128((P2VAR(eslt_WorkSpaceAES128, AUTOMATIC, CRYPTO_30_LIBCV_CRYPTOCV_APPL_VAR))&workSpaceAes128, /* SBSW_CRYPTO_30_LIBCV_ESL_STACK_WORKSPACE_WITH_KEY_PTR */
                                   (P2CONST(eslt_Byte, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR))keyPtr,
                                   ESL_BM_CBC,
                                   ESL_PM_OFF,
                                   NULL_PTR);
  }

  /* #20 encrypt data */
  if (eslRet == ESL_ERC_NO_ERROR)
  {
    /* QAC Deviations: (No 3383) the number block is 1/2 and the size CRYPTO_30_LIBCV_AES_BLOCK_SIZE is 16. So, the issue overflow never occur.*/
    eslRet = esl_encryptAES128((P2VAR(eslt_WorkSpaceAES128, AUTOMATIC, CRYPTO_30_LIBCV_CRYPTOCV_APPL_VAR))&workSpaceAes128, /* SBSW_CRYPTO_30_LIBCV_ESL_STACK_WORKSPACE_WITH_DATA_OUTPUT */
                               (eslt_Length)((eslt_Length)(numberOfBlocks) * CRYPTO_30_LIBCV_AES_BLOCK_SIZE),
                               (P2CONST(eslt_Byte, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR))dataPtr,
                               (P2VAR(eslt_Length, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR))&outLength,
                               (P2VAR(eslt_Byte, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR))outputPtr);
  }

  /* QAC Deviations: (No 3383) the number block is 1/2 and the size CRYPTO_30_LIBCV_AES_BLOCK_SIZE is 16. So, the issue overflow never occur.*/
  written = outLength;
  outLength = (eslt_Length)(((eslt_Length)numberOfBlocks * CRYPTO_30_LIBCV_AES_BLOCK_SIZE) - written);

  if (eslRet == ESL_ERC_NO_ERROR)
  {
    eslRet = esl_finalizeEncryptAES128((P2VAR(eslt_WorkSpaceAES128, AUTOMATIC, CRYPTO_30_LIBCV_CRYPTOCV_APPL_VAR))&workSpaceAes128, /* SBSW_CRYPTO_30_LIBCV_ESL_CALL_WITH_WORKSPACE_AND_BUFFERS */
                                       (P2VAR(eslt_Length, AUTOMATIC, CRYPTO_30_LIBCV_CRYPTOCV_APPL_VAR))&outLength,
                                       (P2VAR(eslt_Byte, AUTOMATIC, CRYPTO_30_LIBCV_CRYPTOCV_APPL_VAR))&outputPtr[written]);
  }
  /* QAC Deviations: (No 3383) the number block is 1/2 and the size CRYPTO_30_LIBCV_AES_BLOCK_SIZE is 16. So, the issue overflow never occur.*/
  written = (eslt_Length)(written + outLength);

  /* QAC Deviations: (No 3383) the number block is 1/2 and the size CRYPTO_30_LIBCV_AES_BLOCK_SIZE is 16. So, the issue overflow never occur.*/
  if ((eslRet == ESL_ERC_NO_ERROR) &&
      (written == ((eslt_Length)numberOfBlocks * CRYPTO_30_LIBCV_AES_BLOCK_SIZE)))
  {
    retVal = E_OK;
  }

  return retVal;
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |const uint8*|dataPtr |Pointer to the input data to be compressed.|
 * |uint32    |length    |Length of the input data, must be a multiple of 16 bytes.|
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |Std_ReturnType|retVal|E_OK on success, E_NOT_OK on failure.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint8* |outputPtr |Pointer to the buffer where the 16-byte compressed result will be stored.|
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
 * |eslt_WorkSpaceAES128Block|workSpaceAes128Block|Workspace memory required by the AES library.|
 * |Std_ReturnType|retVal|Holds the return status of the operation.|
 * |uint32    |lengthCount|A counter for the remaining length of data to process.|
 * |uint8_least|i        |Loop counter for XOR operations.|
 * |uint8[]   |Out       |Buffer to hold the intermediate AES encryption result.|
 * |uint8[]   |Out_last  |Buffer to hold the hash result from the previous block, used as the key for the current block.|
 * |uint8     |tempCalcByte|Temporary variable for the XOR calculation.|
 * |boolean   |exitLoop  |Flag to break the loop in case of an error.|
 * |eslt_ErrorCode|eslRetVal|Holds the return code from `esl_` library functions.|
 * |const uint8*|tempPlainPtr|A moving pointer to the current block of input data.|
 * @brief     Implements the Miyaguchi-Preneel one-way compression function over a buffer of data.
 * @note      This function processes the input data in 16-byte blocks. For each block, it performs the operation `H_i = AES(H_{i-1}, M_i) XOR M_i XOR H_{i-1}`, where `H_0` is a block of zeros. This is a core component of the SHE key derivation function (KDF).
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
static FUNC(Std_ReturnType, CRYPTO_30_LIBCV_CODE) vHsm_Custom_SheKeyUpdateMiyaguchiPreneel(
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) dataPtr,
  uint32 length,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) outputPtr)
{
  /*
    AES-MP(x i): OUT_i  = ENC_(ECB, OUT_i-1) (x i)  XOR x_i  XOR OUT_i-1;  i > 0;   OUT_0  = 0;
    */
  eslt_WorkSpaceAES128Block workSpaceAes128Block;
  Std_ReturnType retVal = E_NOT_OK;
  uint32 lengthCount;
  uint8_least i;
  uint8 Out[VHSM_CUSTOM_SIZEOF_SHE_KEY];
  uint8 Out_last[VHSM_CUSTOM_SIZEOF_SHE_KEY];
  uint8 tempCalcByte;
  boolean exitLoop = FALSE;
  eslt_ErrorCode eslRetVal;

  P2CONST(uint8, AUTOMATIC, CRYPTO_30_LIBCV_CRYPTOCV_APPL_VAR) tempPlainPtr = dataPtr;

  /* #10 initialize all parameters */
  /* Init Out_i-1 (Out_last) */
  Crypto_30_LibCv_SetData(Out, ZERO_NUM, VHSM_CUSTOM_SIZEOF_SHE_KEY); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_CRYPTO_30_LIBCV_STACK_ARRAY_ACCESS_WITH_SIZE */
  Crypto_30_LibCv_SetData(Out_last, ZERO_NUM, VHSM_CUSTOM_SIZEOF_SHE_KEY); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_CRYPTO_30_LIBCV_STACK_ARRAY_ACCESS_WITH_SIZE */
  lengthCount = length;

  /* #15 initialize workspace */
  if (esl_initWorkSpaceHeader((P2VAR(eslt_WorkSpaceHeader, AUTOMATIC, CRYPTO_30_LIBCV_CRYPTOCV_APPL_VAR))&workSpaceAes128Block.header, /* SBSW_CRYPTO_30_LIBCV_INIT_ESL_STACK_WORKSPACE */
    ESL_MAXSIZEOF_WS_AES128,
    CRYPTO_30_LIBCV_WATCHDOG_PTR) == ESL_ERC_NO_ERROR)
  {
    /* #20 Calculate Block-Hash until data size is reached */
    while ( (lengthCount > 0u) && (lengthCount < 0xFFFFFFFFu) && 
            (exitLoop == FALSE))
    {
      /* Set Key */
      /* #25 Set old Hash as round Key */
      eslRetVal = esl_initEncryptAES128Block((P2VAR(eslt_WorkSpaceAES128Block, AUTOMATIC, CRYPTO_30_LIBCV_CRYPTOCV_APPL_VAR))&workSpaceAes128Block,
                                             (P2CONST(eslt_Byte, AUTOMATIC, CRYPTO_30_LIBCV_CRYPTOCV_APPL_VAR))Out_last); /* SBSW_CRYPTO_30_LIBCV_WORKSPACE_STACK_WITH_STACK_BUFFERS */

      /* Encrypt */
      /* #30 Calculate new Hash */
      if (eslRetVal == ESL_ERC_NO_ERROR)
      {
        eslRetVal = esl_encryptAES128Block((P2VAR(eslt_WorkSpaceAES128Block, AUTOMATIC, CRYPTO_30_LIBCV_CRYPTOCV_APPL_VAR))&workSpaceAes128Block,
                                           tempPlainPtr,
                                           (P2VAR(eslt_Byte, AUTOMATIC, CRYPTO_30_LIBCV_CRYPTOCV_APPL_VAR))Out); /* SBSW_CRYPTO_30_LIBCV_WORKSPACE_STACK_WITH_STACK_BUFFERS_AND_PTR_AS_PARAMETER */
      }

      if (eslRetVal == ESL_ERC_NO_ERROR)
      {
        /* #35 Exor new and old hash */
        for (i = 0u; i < VHSM_CUSTOM_SIZEOF_SHE_KEY; i++)
        {
          /* Calculate Out and Out_last */
          tempCalcByte = (uint8)(Out_last[i] ^ Out[i] ^ tempPlainPtr[i]);
          Out_last[i] = tempCalcByte; /* SBSW_CRYPTO_30_LIBCV_STACK_ARRAY_ACCESS_WITH_SIZE */
          Out[i] = tempCalcByte; /* SBSW_CRYPTO_30_LIBCV_STACK_ARRAY_ACCESS_WITH_SIZE */
        }
        /* Store new data pointer */
        tempPlainPtr = &tempPlainPtr[VHSM_CUSTOM_SIZEOF_SHE_KEY];
        /* Update length */
        /* QAC Deviations: (No 3383) The overflow does not occur because the key length always less than VHSM_CUSTOM_SIZEOF_SHE_KEY. */
        lengthCount -= VHSM_CUSTOM_SIZEOF_SHE_KEY;
      }
      else
      {
        exitLoop = TRUE;
      }
    }
  }

  /* #40 Save Result */
  if (lengthCount == 0u)
  {
    retVal = E_OK;
    Crypto_30_LibCv_CopyData(outputPtr, Out, VHSM_CUSTOM_SIZEOF_SHE_KEY);
  }

  return retVal;
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint8     |AuthenID  |The identifier of the key used for authentication.|
 * |const uint8*|KeyValue|Pointer to the buffer containing the new key value to be exported.|
 * |uint16    |KeyLength |The length of the new key value (expected to be 16 bytes).|
 * |uint8     |SheKey    |The identifier of the SHE key slot being targeted.|
 * |const uint8*|UID     |Pointer to the Unique ID of the device.|
 * |uint32    |CID       |The Counter ID for the key update protocol.|
 * |uint8     |FID       |The Flag ID for the key update protocol.|
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |Std_ReturnType|retVal|E_OK on success, E_NOT_OK if any step fails (e.g., key derivation, CMAC).|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint8* |m1m2m3    |Pointer to a buffer that will be filled with the generated M1, M2, and M3 messages.|
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
 * |Std_ReturnType|retVal|Holds the return status of the operation.|
 * |uint8[]   |keyArr    |Buffer to store intermediate keys K1 and K2 derived during the process.|
 * |uint8[]   |KDFbuffer |Buffer used for the input to the Miyaguchi-Preneel KDF.|
 * |uint8[]   |encBuffer |Buffer to construct the plaintext for the M2 message before encryption.|
 * |uint32    |authKeyLength|Expected length of the authentication key.|
 * |Crypto_30_LibCv_SizeOfKeyStorageType|keyStorageIndex|Index pointing to the location of the key in storage.|
 * |eslt_WorkSpaceCMACAES|workSpaceCmacAes|Workspace required for the CMAC calculation of M3.|
 * |int       |i         |Loop counter.|
 * @brief     Generates the M1, M2, and M3 messages for the Secure Hardware Extension (SHE) key export protocol.
 * @note      This function constructs the messages according to the SHE specification. It derives intermediate keys (K1, K2) from the `AuthenID` key, encrypts the new key material to form M2, and computes a CMAC over M1 and M2 to form M3.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
static FUNC(Std_ReturnType, CRYPTO_30_LIBCV_CODE) vHsm_Custom_SheKeyExport_M1M2M3(
    uint8 AuthenID,
    P2CONST(uint8, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR) KeyValue,
    uint16 KeyLength,
    uint8 SheKey,
    P2CONST(uint8, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR) UID,
    uint32 CID,
    uint8 FID,
    P2VAR(uint8, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR) m1m2m3)
{
    Std_ReturnType retVal = E_NOT_OK;
    uint8 keyArr[VHSM_CUSTOM_SIZEOF_SHE_KEY];
    uint8 KDFbuffer[VHSM_CUSTOM_SIZEOF_SHE_KEY + VHSM_CUSTOM_SIZEOF_SHE_UPDATE_CONSTANT];
    uint8 encBuffer[VHSM_CUSTOM_BUFFER_SIZE_32BYTE];
    uint32 authKeyLength = VHSM_CUSTOM_SIZEOF_SHE_KEY;
    Crypto_30_LibCv_SizeOfKeyStorageType keyStorageIndex;
    eslt_WorkSpaceCMACAES workSpaceCmacAes;
    int i;

    /* M1: UID | SHE ID | AuthID */
    Crypto_30_LibCv_CopyData(m1m2m3, UID, VHSM_CUSTOM_SIZEOF_SHE_M1_UID);
    m1m2m3[VHSM_CUSTOM_STARTINDEX_SHE_M1_IDS] = vHsm_Custom_She_M1_BuildIds(SheKey, AuthenID);

    /* Generate K1 for M2 */
    /* QAC Deviations: (No 3383 - No 2284) Configuration and Generation rule of Crypto module is made sure the overflow does not occur. */
    if (Crypto_30_LibCv_IsKeyElementValid(Crypto_30_LibCv_GetKeyElementsKeyIdxOfSheKeys(AuthenID)))
    {
        if (Crypto_30_LibCv_Local_KeyElementGetStorageIndexBasic(Crypto_30_LibCv_GetKeyElementsKeyIdxOfSheKeys(AuthenID), &keyStorageIndex, &authKeyLength, CRYPTO_30_LIBCV_LENGTH_CHECK_EQUAL, CRYPTO_30_LIBCV_SHE_SERVICE_KEY_SERVICE) == E_OK)
        {
            /* QAC Deviations: (No 2284) vHsm_Custom_She_GetPtrEncConst is static code from Vector.So,the pointer always differ NULL.
            This warning can ignore */
            Crypto_30_LibCv_CopyData(&KDFbuffer[VHSM_CUSTOM_SIZEOF_SHE_KEY], vHsm_Custom_She_GetPtrEncConst(AuthenID), VHSM_CUSTOM_SIZEOF_SHE_UPDATE_CONSTANT);
            Crypto_30_LibCv_CopyData(KDFbuffer, Crypto_30_LibCv_GetAddrKeyStorage(keyStorageIndex), VHSM_CUSTOM_SIZEOF_SHE_KEY);

            if (vHsm_Custom_SheKeyUpdateMiyaguchiPreneel(KDFbuffer, VHSM_CUSTOM_SIZEOF_SHE_KEY + VHSM_CUSTOM_SIZEOF_SHE_UPDATE_CONSTANT, keyArr) == E_OK)
            {
                /* Prepare M2 plaintext: CID|FID|Zeros|KeyValue */
                Crypto_30_LibCv_SetData(encBuffer, ZERO_NUM, sizeof(encBuffer));

                encBuffer[0] = (uint8)((CID >> 20u) & 0xFFu);
                encBuffer[1] = (uint8)((CID >> 12u) & 0xFFu);
                encBuffer[2] = (uint8)((CID >> 4u)  & 0xFFu);
                encBuffer[3] = (uint8)(((uint8)(CID & 0x0Fu) << 4u) | ((uint8)(FID >> 2u) & 0x0Fu));
                encBuffer[4] = (uint8)(((uint8)FID << 6u) & 0xC0u);

                for (i = 5; i < 16; i++)
                {
                    encBuffer[i] = 0x00u;
                }

                Crypto_30_LibCv_CopyData(&encBuffer[16], KeyValue, KeyLength);

                /* M2: ENC_CBC,K1(IV=0)(CID|FID|"0...0"|KEYID) */
                if (vHsm_Custom_SheKeyUpdateEncrypt(encBuffer, keyArr, &m1m2m3[VHSM_CUSTOM_STARTINDEX_SHE_M2], 2u) == E_OK)
                {
                  /* Generate K2 for M3 */
                  if (Crypto_30_LibCv_Local_KeyElementGetStorageIndexBasic(Crypto_30_LibCv_GetKeyElementsKeyIdxOfSheKeys(AuthenID), &keyStorageIndex, &authKeyLength, CRYPTO_30_LIBCV_LENGTH_CHECK_EQUAL, CRYPTO_30_LIBCV_SHE_SERVICE_KEY_SERVICE) == E_OK)
                  {
                      Crypto_30_LibCv_CopyData(&KDFbuffer[VHSM_CUSTOM_SIZEOF_SHE_KEY], vHsm_Custom_She_GetPtrMacConst(AuthenID), VHSM_CUSTOM_SIZEOF_SHE_UPDATE_CONSTANT);
                      Crypto_30_LibCv_CopyData(KDFbuffer, Crypto_30_LibCv_GetAddrKeyStorage(keyStorageIndex), VHSM_CUSTOM_SIZEOF_SHE_KEY);

                      if (vHsm_Custom_SheKeyUpdateMiyaguchiPreneel(KDFbuffer, VHSM_CUSTOM_SIZEOF_SHE_KEY + VHSM_CUSTOM_SIZEOF_SHE_UPDATE_CONSTANT, keyArr) == E_OK)
                      {
                          /* Calculate M3 CMAC */
                          if (vHsm_Custom_SheKeyUpdateCmac(m1m2m3, VHSM_CUSTOM_STARTINDEX_SHE_M3, keyArr, &m1m2m3[VHSM_CUSTOM_STARTINDEX_SHE_M3], &workSpaceCmacAes) == E_OK)
                          {
                              retVal = E_OK;
                          }
                      }
                  }
                }
            }
        }
    }

    return retVal;
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |const uint8*|m1m2m3  |Pointer to the previously generated M1, M2, and M3 messages.|
 * |const uint8*|uid     |Pointer to the Unique ID of the device.|
 * |const uint8*|KeyValue|Pointer to the buffer containing the new key value.|
 * |uint32    |CID       |The Counter ID for the key update protocol.|
 * |Crypto_30_LibCv_SizeOfSheKeysType|indexOfSheKey|The index of the SHE key being updated.|
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |Std_ReturnType|retVal|E_OK on success, E_NOT_OK if any step fails.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint8* |m4m5      |Pointer to a buffer that will be filled with the generated M4 and M5 messages.|
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
 * |Std_ReturnType|retVal|Holds the return status of the operation.|
 * |uint8[]   |keyArr    |Buffer to store intermediate keys K3 and K4.|
 * |uint8[]   |KDFbuffer |Buffer used for the input to the Miyaguchi-Preneel KDF.|
 * |uint8[]   |encBuffer |Buffer to construct the plaintext for the M4 message before encryption.|
 * |eslt_WorkSpaceCMACAES|workSpaceCmacAes|Workspace required for the CMAC calculation of M5.|
 * @brief     Generates the M4 and M5 messages for the Secure Hardware Extension (SHE) key update protocol.
 * @note      This function is part of the second phase of the key update. It derives intermediate keys K3 and K4 from the new key value (`KeyValue`), encrypts the counter to form part of M4, and computes a CMAC over M4 to form M5.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
static FUNC(Std_ReturnType, CRYPTO_30_LIBCV_CODE) vHsm_Custom_SheKeyUpdateGenM4M5(
  P2CONST(uint8, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR) m1m2m3,
  P2VAR(uint8, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR) m4m5,
  P2CONST(uint8, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR) uid,
  P2CONST(uint8, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR) KeyValue,
  uint32 CID,
  Crypto_30_LibCv_SizeOfSheKeysType indexOfSheKey)
{
  Std_ReturnType retVal = E_NOT_OK;
  /* Buffer */
  uint8 keyArr[VHSM_CUSTOM_SIZEOF_SHE_KEY]; /* Key3 and Key4 */
  uint8 KDFbuffer[VHSM_CUSTOM_SIZEOF_SHE_KEY + VHSM_CUSTOM_SIZEOF_SHE_UPDATE_CONSTANT];
  uint8 encBuffer[VHSM_CUSTOM_BUFFER_SIZE_16BYTE];
  eslt_WorkSpaceCMACAES workSpaceCmacAes;

  /* Set Key_Update_Enc_C constant */
  /* QAC Deviations: (No 2284) vHsm_Custom_She_GetPtrEncConst is static code from Vector.So,the pointer always differ NULL.
  This warning can ignore */
  Crypto_30_LibCv_CopyData(&KDFbuffer[VHSM_CUSTOM_SIZEOF_SHE_KEY], vHsm_Custom_She_GetPtrEncConst(indexOfSheKey), VHSM_CUSTOM_SIZEOF_SHE_UPDATE_CONSTANT); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_CRYPTO_30_LIBCV_API_CHECKED_SIZE_ACCESS */
  Crypto_30_LibCv_CopyData(KDFbuffer, KeyValue, VHSM_CUSTOM_SIZEOF_SHE_KEY);
  /* # Generate K3 */
  if (vHsm_Custom_SheKeyUpdateMiyaguchiPreneel(KDFbuffer, VHSM_CUSTOM_SIZEOF_KDF_BUFFER, keyArr) == E_OK) /* SBSW_CRYPTO_30_LIBCV_FORWARDING_OF_KDFBUFFER_AND_KEY */
  {
    /* # Generate M4* */
    /* counter(28bits) | "1" | "0" ... "0"x99 (=128 bit) */
    (void)vHsm_Custom_ENC_ECB_K3(CID,encBuffer);

    /* # Copy UID of M4 */
    Crypto_30_LibCv_CopyData(m4m5, uid, VHSM_CUSTOM_SIZEOF_SHE_M1_UID); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_CRYPTO_30_LIBCV_STACK_ARRAY_ACCESS_WITH_SIZE */

    /* # Copy Ids of M4 */
    Crypto_30_LibCv_CopyData(&m4m5[VHSM_CUSTOM_STARTINDEX_SHE_M1_IDS], &m1m2m3[VHSM_CUSTOM_STARTINDEX_SHE_M1_IDS], VHSM_CUSTOM_SIZEOF_SHE_M1_IDS); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_CRYPTO_30_LIBCV_STACK_ARRAY_ACCESS_WITH_SIZE */

    /* # Generate and store second block of M4 */
    if (vHsm_Custom_SheKeyUpdateEncrypt(encBuffer, keyArr, &m4m5[VHSM_CUSTOM_SIZEOF_SHE_KEY], 1u) == E_OK) /* SBSW_CRYPTO_30_LIBCV_FORWARDING_OF_KEYPTR_KEY_OUTPUT */
    {
      /* Set Key_Update_Mac_C constant */
      /* QAC Deviation (No. 2824): vHsm_Custom_She_GetPtrMacConst is static code from Vector to get key configured. Therefore, the job pointer always differs from NULL  */
      Crypto_30_LibCv_CopyData(&KDFbuffer[VHSM_CUSTOM_SIZEOF_SHE_KEY], vHsm_Custom_She_GetPtrMacConst(indexOfSheKey), VHSM_CUSTOM_SIZEOF_SHE_UPDATE_CONSTANT); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_CRYPTO_30_LIBCV_API_CHECKED_SIZE_ACCESS */

      /* # Generate K4 */
      if (vHsm_Custom_SheKeyUpdateMiyaguchiPreneel(KDFbuffer, VHSM_CUSTOM_SIZEOF_KDF_BUFFER, keyArr) == E_OK) /* SBSW_CRYPTO_30_LIBCV_FORWARDING_OF_KDFBUFFER_AND_KEY */
      {
        /* Generate M5 */
        retVal = vHsm_Custom_SheKeyUpdateCmac(m4m5, 32u, keyArr, &m4m5[32], &workSpaceCmacAes); /* SBSW_CRYPTO_30_LIBCV_FORWARDING_STACK_BUFFER */
      }
    }
  }
  return retVal;
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |Crypto_30_LibCv_SizeOfSheKeysType|KeyID|The custom key identifier to be updated.|
 * |uint32    |shekey_length|The length of the new key value (must be 16 bytes).|
 * |const uint8*|pNewKey|Pointer to the buffer containing the new key value.|
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |Std_ReturnType|returnValue|E_OK on success, E_NOT_OK on failure.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint8* |pResultBuffer|Pointer to a buffer that will be filled with the complete M1-M5 message sequence.|
 * |uint32*|pResultLength|Pointer to a variable that will be updated with the total length of the M1-M5 sequence.|
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
 * |Std_ReturnType|returnValue|Holds the final return status of the function.|
 * |Std_ReturnType|retVal|Holds the intermediate return status of internal calls.|
 * |uint8[]   |m1m2m3Buffer|Buffer to hold the generated M1, M2, and M3 messages.|
 * |uint8[]   |m4m5Buffer|Buffer to hold the generated M4 and M5 messages.|
 * |uint32    |uidLength|Expected length of the UID.|
 * |Crypto_30_LibCv_SizeOfKeyStorageType|uidStorageIndex|Index pointing to the location of the UID in storage.|
 * |uint32    |counterID|The Counter ID for the key update protocol.|
 * |uint8     |FID       |The Flag ID for the key update protocol.|
 * |uint8     |sheID     |The SHE key slot identifier.|
 * |const uint8|authenticationID|The hardcoded authentication key ID used for the protocol.|
 * @brief     Orchestrates the generation of the full M1-M5 message sequence for a SHE key update.
 * @note      This function validates inputs, retrieves necessary parameters like the UID and counter, then calls helper functions to generate the M1-M3 and M4-M5 message groups, and finally concatenates them into the result buffer.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
static FUNC(Std_ReturnType, CRYPTO_30_LIBCV_CODE) vHsm_Custom_SheKeyUpdateGen_M1_M5(
    Crypto_30_LibCv_SizeOfSheKeysType KeyID, 
    uint32 shekey_length,
    P2CONST(uint8, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR) pNewKey,
    P2VAR(uint8, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR) pResultBuffer,
    P2VAR(uint32, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR) pResultLength)
{
    Std_ReturnType returnValue;
    Std_ReturnType retVal;
    uint8 m1m2m3Buffer[VHSM_CUSTOM_SIZEOF_SHE_M1_M3];
    uint8 m4m5Buffer[VHSM_CUSTOM_SHE_M4_M5];
    uint32 uidLength;
    Crypto_30_LibCv_SizeOfKeyStorageType uidStorageIndex;
    uint32 counterID;
    uint8 FID;
    uint8 sheID;
    const uint8 authenticationID = 1u;

    if (pNewKey == NULL_PTR)
    {
        returnValue = E_NOT_OK;
    }
    else if (pResultBuffer == NULL_PTR)
    {
        returnValue = E_NOT_OK;
    }
    else if (pResultLength == NULL_PTR)
    {
        returnValue = E_NOT_OK;
    }
    else if (shekey_length != VHSM_CUSTOM_SIZEOF_SHE_KEY)
    {
        returnValue = E_NOT_OK;
    }
    else
    {
        uidLength = VHSM_CUSTOM_SIZEOF_SHE_M1_UID;
        retVal = vHsm_Custom_Check_FID(KeyID, &counterID, &FID, &sheID);
        if (retVal == E_OK)
        {
            retVal = Crypto_30_LibCv_Local_KeyElementGetStorageIndex(Crypto_30_LibCv_GetSheInfoKeyRefOfSheKeyUpdate(), CRYPTO_KE_CUSTOM_SHE_UID, &uidStorageIndex,
                                                                     &uidLength, CRYPTO_30_LIBCV_LENGTH_CHECK_MIN);
            if (retVal == E_OK)
            {
                retVal = vHsm_Custom_SheKeyExport_M1M2M3(authenticationID, pNewKey, VHSM_CUSTOM_SIZEOF_SHE_KEY, sheID,
                                                         Crypto_30_LibCv_GetAddrKeyStorage(uidStorageIndex), counterID, FID, m1m2m3Buffer);
                if (retVal == E_OK)
                {
                    retVal = vHsm_Custom_SheKeyUpdateGenM4M5(m1m2m3Buffer, m4m5Buffer, Crypto_30_LibCv_GetAddrKeyStorage(uidStorageIndex),
                                                             pNewKey, counterID, authenticationID);

                    if (retVal == E_OK)
                    {
                        Crypto_30_LibCv_CopyData(pResultBuffer, m1m2m3Buffer, VHSM_CUSTOM_SIZEOF_SHE_M1_M3);
                        Crypto_30_LibCv_CopyData(&pResultBuffer[VHSM_CUSTOM_SIZEOF_SHE_M1_M3], m4m5Buffer, VHSM_CUSTOM_SHE_M4_M5);
                        *pResultLength = 112u;
                        returnValue = E_OK;
                    }
                    else
                    {
                        returnValue = E_NOT_OK;
                    }
                }
                else
                {
                    returnValue = E_NOT_OK;
                }
            }
            else
            {
                returnValue = E_NOT_OK;
            }
        }
        else
        {
            returnValue = E_NOT_OK;
        }
    }

    return returnValue;
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint32    |CID       |The Counter ID used to construct the plaintext.|
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |Std_ReturnType|retVal|E_OK on success, E_NOT_OK if the output buffer is NULL.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint8* |encBuffer |Pointer to a buffer that will be filled with the 16-byte plaintext for M4 encryption.|
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
 * |Std_ReturnType|retVal|Holds the return status of the operation.|
 * @brief     Constructs the plaintext block used in the generation of the SHE M4 message.
 * @note      This function takes the 28-bit counter `CID`, formats it into a 128-bit block as specified by SHE (`counter(28bits) | "1" | "0"...`), and places the result in the output buffer.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
static FUNC(Std_ReturnType, VHSM_CUSTOM_CODE) vHsm_Custom_ENC_ECB_K3(
    uint32 CID,
    P2VAR(uint8, AUTOMATIC, VHSM_CUSTOM_APPL_DATA) encBuffer 
)
{
    Std_ReturnType retVal = E_OK;
    if (encBuffer == NULL_PTR)
    {
      retVal = E_NOT_OK;
    }
    else
    {
      Crypto_30_LibCv_SetData(encBuffer, ZERO_NUM, 16u);
      encBuffer[0] = (uint8)(CID >> 20u);
      encBuffer[1] = (uint8)(CID >> 12u);
      encBuffer[2] = (uint8)(CID >> 4u);
      encBuffer[3] = (uint8)(CID << 4u);
      encBuffer[3] |= 0x08u;
    }
    return retVal;
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint8     |SheId     |The SHE key slot ID to search for.|
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |Crypto_30_LibCv_SizeOfSheKeysType|index|The configuration index corresponding to the `SheId`. Returns 0xFF if not found.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
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
 * |Crypto_30_LibCv_SizeOfSheKeysType|index|The found index, initialized to an invalid value.|
 * |Crypto_30_LibCv_SizeOfSheKeysType|i    |Loop counter.|
 * @brief     Finds the internal configuration index for a given SHE key slot ID.
 * @note      This function iterates through the pre-compiled SHE key configuration table to map a runtime SHE ID to its static configuration index.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
static Crypto_30_LibCv_SizeOfSheKeysType GetIndexFromSheId(uint8 SheId)
{
    Crypto_30_LibCv_SizeOfSheKeysType index = 0xFFu;
    Crypto_30_LibCv_SizeOfSheKeysType i;

    for (i = 0u; i < Crypto_30_LibCv_GetSizeOfSheKeys(); i++) 
    {
        if (Crypto_30_LibCv_GetSheIdOfSheKeys(i) == SheId)
        {
            index = i;
            break;
        }
    }
    return index;
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |Crypto_30_LibCv_SizeOfSheKeysType|KeyID|The custom key identifier being checked.|
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |Std_ReturnType|retVal|E_OK on success, E_NOT_OK if the KeyID is invalid, or if the counter overflows.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint32* |CID       |Pointer to be updated with the new Counter ID.|
 * |uint8* |FID       |Pointer to be updated with the corresponding Flag ID.|
 * |uint8* |SheID     |Pointer to be updated with the corresponding SHE key slot ID.|
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
 * |Std_ReturnType|retVal|Holds the return status of the operation.|
 * |uint32    |oldCounter|The current counter value read from key storage.|
 * |uint32    |counterLength|Expected length of the counter element (4 bytes).|
 * |Crypto_30_LibCv_SizeOfKeyStorageType|keyStorage|Index pointing to the location of the counter in storage.|
 * |boolean   |validKey|Flag to track if the input `KeyID` is valid.|
 * |Crypto_30_LibCv_SizeOfSheKeysType|indexOfSheKey|The configuration index corresponding to the `SheID`.|
 * @brief     Checks the validity of a custom key ID, retrieves its corresponding FID, SheID, and the current counter value, then increments the counter.
 * @note      This function maps a custom key update request to the correct SHE parameters. It contains a hardcoded mapping between the custom `KeyID` and the SHE `FID` and `SheID`. It also handles fetching and incrementing the anti-replay counter associated with the key.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
static FUNC(Std_ReturnType, VHSM_CUSTOM_CODE) vHsm_Custom_Check_FID(
    Crypto_30_LibCv_SizeOfSheKeysType KeyID,
    P2VAR(uint32, AUTOMATIC, VHSM_CUSTOM_APPL_DATA) CID,
    P2VAR(uint8, AUTOMATIC, VHSM_CUSTOM_APPL_DATA) FID,
    P2VAR(uint8, AUTOMATIC, VHSM_CUSTOM_APPL_DATA) SheID)
{
  Std_ReturnType retVal;
  uint32 oldCounter = 0u;
  uint32 counterLength = VHSM_CUSTOM_SIZEOF_SHE_M4_COUNTER_FULL_BYTES;
  Crypto_30_LibCv_SizeOfKeyStorageType keyStorage;
  boolean validKey = TRUE;
  Crypto_30_LibCv_SizeOfSheKeysType indexOfSheKey;

  if ((CID == NULL_PTR) || (FID == NULL_PTR) || (SheID == NULL_PTR))
  {
    retVal = E_NOT_OK;
  }
  else
  {
    switch (KeyID)
    {
      case VHSM_CUSTOM_SHE_KEY_TYPEX_ID:
        *FID = 0x02U;
        *SheID = 0x0bU;
        break;
      case VHSM_CUSTOM_MASTER_ECU_KEY_ID:
        *FID = 0x02U;
        *SheID = 0x01U;
        break;
      case VHSM_CUSTOM_SHE_KEY_SECUREBOOT_ID:
        *FID = 0x06U;
        *SheID = 0x09U;
        break;
      case VHSM_CUSTOM_SHE_KEY_DEBUG_PORT_ID:
        *FID = 0x02U;
        *SheID = 0x0aU;
        break;
      case VHSM_CUSTOM_SHE_KEY_REPROGRAMMING_ID:
        *FID = 0x02U;
        *SheID = 0x07U;
        break;
      default:
        *FID = 0xFFU;
        *SheID = 0xFFU;
        *CID = 0U;
        validKey = FALSE;
        break;
    }

    if (validKey == TRUE) 
    {
      indexOfSheKey = GetIndexFromSheId(*SheID);

      if (indexOfSheKey != 0xFFu)
      {
        retVal = Crypto_30_LibCv_Local_KeyElementGetStorageIndexBasic(Crypto_30_LibCv_GetKeyElementsCounterIdxOfSheKeys(indexOfSheKey), &keyStorage, &counterLength,
                                                                      CRYPTO_30_LIBCV_LENGTH_CHECK_EQUAL, CRYPTO_30_LIBCV_SHE_SERVICE_KEY_SERVICE);

        if (retVal == E_OK)
        {
          Crypto_30_LibCv_Local_Uint8ArrayToUint32BigEndian(&oldCounter, Crypto_30_LibCv_GetAddrKeyStorage(keyStorage));
          if(oldCounter < 0xFFFFFFFFu)
          { 
            *CID = oldCounter + 1U;
          }
          else
          {
            /* Buffer overflow*/
            retVal = E_NOT_OK;
          }
        }
        else
        {
          /*Do nothing*/
        }
      }
      else
      {
        retVal = E_NOT_OK;
      }
    }
    else
    {
      retVal = E_NOT_OK;
    }
  }

  return retVal;
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
 * |Std_ReturnType|retVal|E_OK if the UID was read successfully, E_NOT_OK otherwise.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
 * @par       Reference variables
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
 * @par       Output variables
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |cy_rma_config_t|RMAParameterConfig|The global RMA configuration structure is updated with the read UID.|
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
 * |un_srom_api_args_t|params|Structure to hold arguments for the SROM API call.|
 * |un_srom_api_resps_t|getResp|Structure to hold the response from the SROM API call.|
 * |Std_ReturnType|retVal|Holds the return status of the operation.|
 * |uint32    |uid0, uid1, uid2|Temporary variables to hold the parts of the read UID.|
 * @brief     Reads the device's Unique ID (UID) using the SROM API and updates the global RMA configuration structure with the value.
 * @note      This function is a prerequisite for RMA operations that require the device's UID. It also performs byte swapping on the UID parts to match the required endianness.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
static Std_ReturnType ReadUidRMA(void) {
   un_srom_api_args_t  params = {ZERO_NUM};
   un_srom_api_resps_t getResp= {ZERO_NUM};
   Std_ReturnType retVal = E_NOT_OK;

   uint32 uid0;
   uint32 uid1;
   uint32 uid2;

   // Read Unique ID
   params.RdUnId.arg0.Opcode = (uint32_t)CY_SROM_OP_READ_UNIQUE_ID;
   if (Cy_Srom_CallApi(&params, &getResp) == CY_SROM_DR_SUCCEEDED)
   {
    uid0 = ((getResp.RdUnId.resp0.ErrorCode & 0x0000FFu) << SHIFT_24_BIT) |
                   ((getResp.RdUnId.resp0.ErrorCode & 0x00FF00u) << SHIFT_8_BIT) |
                   ((getResp.RdUnId.resp0.ErrorCode & 0xFF0000u) >> SHIFT_8_BIT) |
                   (getResp.RdUnId.resp1.DIE_ID0 & 0xFFu);
    uid1 = ((getResp.RdUnId.resp1.DIE_ID0 & 0x0000FF00u) << SHIFT_16_BIT) |
                   ((getResp.RdUnId.resp1.DIE_ID0 & 0x00FF0000u)) |
                   ((getResp.RdUnId.resp1.DIE_ID0 & 0xFF000000u) >> SHIFT_16_BIT);
    uid2 = ((getResp.RdUnId.resp2.DIE_ID1 & 0x0000FF00u) << SHIFT_16_BIT) |
                   ((getResp.RdUnId.resp2.DIE_ID1 & 0x00FF0000u)) |
                   ((getResp.RdUnId.resp2.DIE_ID1 & 0xFF000000u) >> SHIFT_16_BIT);
     // Update RMA parameter Config
     RMAParameterConfig.UniqueID_0 = uid0;
     RMAParameterConfig.UniqueID_1 = uid1;
     RMAParameterConfig.UniqueID_2 = uid2;
     retVal = E_OK;
   }
   return retVal;
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
 * |SecureReturnStatus|retval|A detailed status code indicating success or the specific point of failure.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
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
 * |SecureReturnStatus|retval|Holds the return status of the operation.|
 * |srom_api_args_t|secure_trans_params|Structure to hold arguments for the TransitionToSecure SROM API call.|
 * |un_srom_api_resps_t|secureResp|Structure to hold the response from the SROM API call.|
 * |uint8     |Num       |Loop counter for iterating through eFuse addresses.|
 * @brief     Handles the process of transitioning the device to the SECURE lifecycle state.
 * @note      This function first changes the system clock to a safe frequency (FLL 100MHz), calls the SROM API to perform the transition, and then verifies that the correct eFuse bits have been blown by reading and comparing their values. Finally, it restores the system clock to its original frequency (PLL 160MHz).
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
static SecureReturnStatus HandleTransitionSecure(void)
{
  SecureReturnStatus retval = SECURE_RET_SUCCESS;
  srom_api_args_t secure_trans_params = {0u};
  un_srom_api_resps_t secureResp = {0u};
  uint8 Num;

  /* 1. Disable ECC Check */
  Disable_RAM0_ECC_Check();

  /* 2. Clear the fault traces of ECC */
  Clear_ECC_Fault_Trace(FAULT_STRUCT0);
  
  secure_trans_params.TransitionToSecure.arg0.Opcode = OPCODE_TRANSITION_TO_SECURE;
  secure_trans_params.TransitionToSecure.arg0.Debug = SECURE;
  secure_trans_params.TransitionToSecure.arg1.Acc_restrict = SECURE_ACC_RESTRICT;
  secure_trans_params.TransitionToSecure.arg2.Dead_Acc_restrict = DEAD_ACC_RESTRICT;


  /* 3. Perform TransitionToSecureStage job */
  /*** Set the CLK as FLL = 100MHz ***/
  if (E_OK == ClockSetToFLL100MHz()){
    /*** Call API TransitionToSecure ***/
    (void)Cy_Srom_CallApi((un_srom_api_args_t *)&secure_trans_params, &secureResp);

    if ((secureResp.resp[0] & 0xF0000000u) == 0xA0000000u){
      for (Num = 0u; Num < NUM_OF_EFUSE_VALUE; Num++)
      {
        /* Read byte adress from 0x01, 0x2C - 0x43 and compare the read value */
        if (CompareEfuseValue(EfuseAddr[Num]) != (bool)TRUE){
          /* mismatch*/
          retval = SECURE_RET_EFUSE_VALUE_NOT_MATCH;
          break;
        }
      }

      if (SECURE_RET_SUCCESS == retval){
        for (Num = 0u; Num < NUM_OF_SECURE_ACCESS_VALUE; Num++)
        {
          /* Read byte adress from 0x3C - 0x3E, and compare the read value */
          if (CompareEfuseValue_SecureAccess(SecureAccessRestrictions_EfuseAddr[Num]) != (bool)TRUE){
            /* mismatch*/
            retval = SECURE_RET_EFUSE_VALUE_SECURE_ACCESS_NOT_MATCH;
            break;
          }
        }
      }

      if (SECURE_RET_SUCCESS == retval){
        for (Num = 0u; Num < NUM_OF_DEAD_ACCESS_VALUE; Num++)
        {
          /* Read byte adress from 0x40 - 0x42, and compare the read value */
          if (CompareEfuseValue_DeadAccess(DeadAccessRestrictions_EfuseAddr[Num]) != (bool)TRUE){
            /* mismatch*/
            retval = SECURE_RET_EFUSE_VALUE_DEAD_ACCESS_NOT_MATCH;
            break;
          }
        }
      }
    } else {
      switch ((cy_en_srom_api_status_t)secureResp.resp[0])
      {
      case CY_SROM_STATUS_INVALID_PROTECTION:
        retval = SECURE_RET_INVALID_PROTECTION;
        break;
      case CY_SROM_STATUS_INVALID_TOC2_HASH_OBJECT:
        retval = SECURE_RET_INVALID_HASH_OBJ2;
        break;
      case CY_SROM_STATUS_INVALID_TOC2:
        retval = SECURE_RET_INVALID_TOC2;
        break;
      case CY_SROM_STATUS_FUSE_PGM_FAILED:
        retval = SECURE_RET_FUSE_PGM_FAILED;
        break;
      default:
        retval = SECURE_RET_IPC_OR_TIMEOUT_ERR;
        break;
      }
    }
  } else {
    retval = SECURE_RET_HF0_CLOCK_NOT_FULLY_CONFIGURED;
  }

  /***** Restore to CLK_PATH_3 as PLL = 160MHz ******/
  if(E_OK != ClockRestoreToPLL160MHz())
  {
    retval |= (SecureReturnStatus)MASK_HF0_RESTORE_FAILED;
  }

  /* 4. Enable ECC Check */
  Enable_RAM0_ECC_Check();

  return retval;
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
 * |SecureReturnStatus|retval|A detailed status code indicating success or the specific point of failure.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
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
 * |SecureReturnStatus|retval|Holds the return status of the operation.|
 * |srom_api_args_t|secure_trans_params|Structure to hold arguments for the SROM API call.|
 * |un_srom_api_resps_t|secureWDebugResp|Structure to hold the response from the SROM API call.|
 * |uint8     |Num       |Loop counter for iterating through eFuse addresses.|
 * @brief     Handles the process of transitioning the device to the SECURE lifecycle state with debug interfaces enabled.
 * @note      This function is similar to `HandleTransitionSecure` but uses different access restriction parameters (`SECURE_WD_ACC_RESTRICT`, `DEAD_WD_ACC_RESTRICT`) to keep debug ports open after the transition. It performs the same clock switching and eFuse verification steps.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
static SecureReturnStatus HandleTransitionSecureWithDebug(void)
{
  SecureReturnStatus retval = SECURE_RET_SUCCESS;
  srom_api_args_t secure_trans_params = {0u};
  un_srom_api_resps_t secureWDebugResp = {0u};
  uint8 Num;

  secure_trans_params.TransitionToSecure.arg0.Opcode = OPCODE_TRANSITION_TO_SECURE;
  secure_trans_params.TransitionToSecure.arg0.Debug = SECURE_WITH_DEBUG;
  secure_trans_params.TransitionToSecure.arg1.Acc_restrict = SECURE_WD_ACC_RESTRICT;
  secure_trans_params.TransitionToSecure.arg2.Dead_Acc_restrict = DEAD_WD_ACC_RESTRICT;

/*** Set the CLK as FLL = 100MHz ***/
  if (E_OK == ClockSetToFLL100MHz()){
    /*** Call API TransitionToSecure ***/
    (void)Cy_Srom_CallApi((un_srom_api_args_t *)&secure_trans_params, &secureWDebugResp);

    if ((secureWDebugResp.resp[0] & 0xF0000000u) == 0xA0000000u){
      for (Num = 0u; Num < NUM_OF_EFUSE_VALUE; Num++)
      {
        /* Read byte adress from 0x01, 0x2C - 0x43 and compare the read value */
        if (CompareEfuseValue(EfuseAddr[Num]) != (bool)TRUE){
          /* mismatch*/
          retval = SECURE_RET_EFUSE_VALUE_NOT_MATCH;
          break;
        }
      }

      if (SECURE_RET_SUCCESS == retval){
        for (Num = 0u; Num < NUM_OF_SECURE_ACCESS_VALUE; Num++)
        {
          /* Read byte adress from 0x3C - 0x3E, and compare the read value */
          if (CompareEfuseValue_SecureAccess(SecureAccessRestrictions_EfuseAddr[Num]) != (bool)TRUE){
            /* mismatch*/
            retval = SECURE_RET_EFUSE_VALUE_SECURE_ACCESS_NOT_MATCH;
            break;
          }
        }
      }

      if (SECURE_RET_SUCCESS == retval){
        for (Num = 0u; Num < NUM_OF_DEAD_ACCESS_VALUE; Num++)
        {
          /* Read byte adress from 0x40 - 0x42, and compare the read value */
          if (CompareEfuseValue_DeadAccess(DeadAccessRestrictions_EfuseAddr[Num]) != (bool)TRUE){
            /* mismatch*/
            retval = SECURE_RET_EFUSE_VALUE_DEAD_ACCESS_NOT_MATCH;
            break;
          }
        }
      }
    } else {
      switch ((cy_en_srom_api_status_t)secureWDebugResp.resp[0])
      {
      case CY_SROM_STATUS_INVALID_PROTECTION:
        retval = SECURE_RET_INVALID_PROTECTION;
        break;
      case CY_SROM_STATUS_INVALID_TOC2_HASH_OBJECT:
        retval = SECURE_RET_INVALID_HASH_OBJ2;
        break;
      case CY_SROM_STATUS_INVALID_TOC2:
        retval = SECURE_RET_INVALID_TOC2;
        break;
      case CY_SROM_STATUS_FUSE_PGM_FAILED:
        retval = SECURE_RET_FUSE_PGM_FAILED;
        break;
      default:
        retval = SECURE_RET_IPC_OR_TIMEOUT_ERR;
        break;
      }
    }
  } else {
    retval = SECURE_RET_HF0_CLOCK_NOT_FULLY_CONFIGURED;
  }
  
  /***** Restore to CLK_PATH_3 as PLL = 160MHz ******/
  if(E_OK != ClockRestoreToPLL160MHz())
  {
    retval |= (SecureReturnStatus)MASK_HF0_RESTORE_FAILED; 
  }

  return retval;
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
 * |Std_ReturnType|retval|E_OK if the clock was successfully restored, E_NOT_OK otherwise.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
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
 * |CPUSS_Type*|CPUSS     |Various clock control registers within the CPUSS block are modified.|
 * @par       Output registers
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |CPUSS_Type*|CPUSS     |Clock control registers are written to reconfigure the system clock.|
 * @par       Automatic variables
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |Std_ReturnType|retval|Holds the return status of the operation.|
 * |uint32    |coreClockFreq|Holds the measured core clock frequency after reconfiguration.|
 * |uint32    |Hf0ClkFrequency|Holds the measured HF0 clock frequency after reconfiguration.|
 * @brief     Restores the system clock to its normal operating frequency of 160MHz using the PLL sourced from the ECO.
 * @note      This function directly manipulates hardware clock control registers via the PDL (`Cy_SysClk_...`) functions to re-enable the PLL and switch the HF0 clock source. It then verifies that the clock frequencies are correct.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
Std_ReturnType ClockRestoreToPLL160MHz(void)
{
  Std_ReturnType retval = E_NOT_OK;
  uint32_t coreClockFreq = 0u;
  uint32_t Hf0ClkFrequency = 0u;

  /* CLK_MEM */
  CPUSS->unMEM_CLOCK_CTL.stcField.u8INT_DIV     = 0u; /* no division */

  /* CLK_SLOW */
  CPUSS->unSLOW_CLOCK_CTL.stcField.u8INT_DIV    = 1u; /* divided by 2 */

  /* QAC Deviations: (No 4424) Cy_SysClk_ClkPathSetSource provided by Infineon. So, this warning can ignore */
  (void)Cy_SysClk_ClkPathSetSource(CY_SYSCLK_HFCLK_0, CY_SYSCLK_CLKPATH_IN_ECO);
  /* QAC Deviations: (No 4424) Cy_SysClk_ClkPathSetSource provided by Infineon. So, this warning can ignore */
  (void)Cy_SysClk_PllDisable(CY_SYSCLK_HFCLK_IN_CLKPATH3);

  /* Enable interrupt */
  __enable_irq();

  /* QAC Deviations: (No 4424) Cy_SysClk_ClkPathSetSource provided by Infineon. So, this warning can ignore */
  (void)Cy_SysClk_HfClockSetSource(CY_SYSCLK_HFCLK_0, (cy_en_hf_clk_sources_t)CY_SYSCLK_HFCLK_IN_CLKPATH3);
  /* QAC Deviations: (No 4424) Cy_SysClk_ClkPathSetSource provided by Infineon. So, this warning can ignore */
  (void)Cy_SysClk_PllEnable(CY_SYSCLK_HFCLK_IN_CLKPATH3, WAIT_FOR_STABILIZATION);

  SystemCoreClockUpdate();
  /* QAC Deviations: (No 4424) Cy_SysClk_ClkPathSetSource provided by Infineon. So, this warning can ignore */
  (void)Cy_SysClk_GetHfClkFrequency(CY_SYSCLK_HFCLK_0, &Hf0ClkFrequency);
  /* QAC Deviations: (No 4424) Cy_SysClk_ClkPathSetSource provided by Infineon. So, this warning can ignore */
  (void)Cy_SysClk_GetCoreFrequency(&coreClockFreq);

  if ((coreClockFreq == (PLL_TARGET_FREQ/2u)) && (Hf0ClkFrequency == PLL_TARGET_FREQ)) {
    retval = E_OK;
  }
  
  return retval;
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
 * |Std_ReturnType|retval|E_OK if the clock was successfully set, E_NOT_OK otherwise.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
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
 * |CPUSS_Type*|CPUSS     |Various clock control registers within the CPUSS block are modified.|
 * @par       Output registers
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |CPUSS_Type*|CPUSS     |Clock control registers are written to reconfigure the system clock.|
 * @par       Automatic variables
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |Std_ReturnType|retval|Holds the return status of the operation.|
 * |uint32    |coreClockFreq|Holds the measured core clock frequency after reconfiguration.|
 * |uint32    |Hf0ClkFrequency|Holds the measured HF0 clock frequency after reconfiguration.|
 * @brief     Sets the system clock to a safe frequency of 100MHz using the FLL sourced from the IMO.
 * @note      This function is called before performing critical SROM operations. It directly manipulates hardware clock control registers via the PDL (`Cy_SysClk_...`) functions to disable the PLL and enable the FLL. It then verifies that the clock frequencies are correct.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
Std_ReturnType ClockSetToFLL100MHz(void)
{
  Std_ReturnType retval = E_NOT_OK;
  uint32_t coreClockFreq = 0u;
  uint32_t Hf0ClkFrequency = 0u;

  /* CLK_MEM */
  CPUSS->unMEM_CLOCK_CTL.stcField.u8INT_DIV     = 0u; /* no division */

  /* CLK_SLOW */
  CPUSS->unSLOW_CLOCK_CTL.stcField.u8INT_DIV    = 0u; /* no division */

  /* QAC Deviations: (No 4424) Cy_SysClk_ClkPathSetSource provided by Infineon. So, this warning can ignore */
  (void)Cy_SysClk_ClkPathSetSource(CY_SYSCLK_HFCLK_0, CY_SYSCLK_CLKPATH_IN_IMO);
  (void)Cy_SysClk_FllDisableSequence(WAIT_FOR_STABILIZATION);

  /* Enable interrupt */
  __enable_irq();

  (void)Cy_SysClk_FllConfigureStandard(CLK_FREQ_IMO, FLL_TARGET_FREQ, CY_SYSCLK_FLLPLL_OUTPUT_AUTO);
  (void)Cy_SysClk_HfClockSetSource(CY_SYSCLK_HFCLK_0, (cy_en_hf_clk_sources_t)CY_SYSCLK_HFCLK_IN_CLKPATH0);
  (void)Cy_SysClk_FllEnable(WAIT_FOR_STABILIZATION);


  SystemCoreClockUpdate();
  (void)Cy_SysClk_GetHfClkFrequency(CY_SYSCLK_HFCLK_0, &Hf0ClkFrequency);
  (void)Cy_SysClk_GetCoreFrequency(&coreClockFreq);

  if ((coreClockFreq == FLL_TARGET_FREQ) && (Hf0ClkFrequency == FLL_TARGET_FREQ)) {
    retval = E_OK;
  }

  return retval;
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint32    |ReadEfuse_Efuseaddr|The address of the eFuse byte to read.|
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |cy_en_srom_driver_status_t|retval|The status returned from the SROM API call (e.g., CY_SROM_DR_SUCCEEDED).|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
 * @par       Reference variables
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
 * @par       Output variables
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint32    |g_RdEfuseValue|The global variable is updated with the value of the read eFuse byte.|
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
 * |un_srom_api_args_t|apiArgs|Structure to hold arguments for the SROM API call.|
 * |un_srom_api_resps_t|apiResp|Structure to hold the response from the SROM API call.|
 * |cy_en_srom_driver_status_t|retval|Holds the return status of the SROM operation.|
 * @brief     Reads a single byte from a specified eFuse address using the SROM API.
 * @note      This is a wrapper function for the `CY_SROM_OP_READ_FUSE_BYTE` SROM command. The result of the read is stored in the global variable `g_RdEfuseValue`.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
static cy_en_srom_driver_status_t Cy_ReadFuseByte(uint32_t ReadEfuse_Efuseaddr)
{
  /* Prepares arguments to be passed to SROM API */
  un_srom_api_args_t apiArgs = {0UL};
  un_srom_api_resps_t apiResp = {0UL};
  cy_en_srom_driver_status_t retval;
  apiArgs.RdFuse.arg0.eFuseAddr = ReadEfuse_Efuseaddr;
  apiArgs.RdFuse.arg0.Opcode = (uint32_t)CY_SROM_OP_READ_FUSE_BYTE;

  /* Call SROM API driver and process response */
  retval = Cy_Srom_CallApi(&apiArgs, &apiResp);

  g_RdEfuseValue = apiResp.RdFuse.resp0.ReadByte;

  return retval;
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint32    |ReadEfuseAddr|The address of the eFuse byte to read and compare.|
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |bool      |retval    |`true` if the eFuse value is consistent across all margin reads, `false` otherwise.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
 * @par       Reference variables
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint32    |g_RdEfuseValue, g_RdEfuseMarginValue50, g_RdEfuseMarginValue100|Reads these global variables to compare the results of the different eFuse reads.|
 * @par       Output variables
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint32    |MarginCTL |The global margin control variable is modified.|
 * |uint32    |g_RdEfuseValue, g_RdEfuseMarginValue50, g_RdEfuseMarginValue100|These global variables are reset after comparison.|
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
 * |cy_en_srom_driver_status_t|getResult|Holds the return status from SROM API calls.|
 * |bool      |retval    |Holds the final boolean return value.|
 * @brief     Verifies the integrity of an eFuse bit by reading it at nominal, -50% margin, and +100% margin, then comparing the results.
 * @note      This function ensures that an eFuse bit is reliably programmed. It returns `true` only if all three reads (nominal, low margin, high margin) yield the exact same value.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
static bool CompareEfuseValue(uint32_t ReadEfuseAddr)
{
  /*** API Result ***/
  cy_en_srom_driver_status_t getResult;
  bool retval = false;

  /*** Call API ReadFuseByte ***/
  getResult = Cy_ReadFuseByte(ReadEfuseAddr);
  if(getResult == CY_SROM_DR_SUCCEEDED)
  {
    /*** Call API ReadFuseByteMargin MarginCTL = -50% ***/
    MarginCTL = 0u; /* 0: Low resistance */
    getResult = Cy_ReadFuseByteMargin(ReadEfuseAddr, MarginCTL);
    if(getResult == CY_SROM_DR_SUCCEEDED)
    {
      /*** Call API ReadFuseByteMargin MarginCTL = +100% ***/
      MarginCTL = 3u; /* High resistance +100% */
      getResult = Cy_ReadFuseByteMargin(ReadEfuseAddr, MarginCTL);
      if(getResult == CY_SROM_DR_SUCCEEDED)
      {
        if ((g_RdEfuseValue == g_RdEfuseMarginValue50) && (g_RdEfuseValue == g_RdEfuseMarginValue100))
        {
          // Matched
          g_RdEfuseValue = 1U;
          g_RdEfuseMarginValue50 = 0U;
          g_RdEfuseMarginValue100 = 0U;
          retval = true;
        }
      }
    }
  }

  return retval;
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint32    |ReadEfuseAddr|The address of the eFuse byte to read and compare.|
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |bool      |retval    |`true` if the read eFuse value matches the corresponding bits of the `DEAD_ACC_RESTRICT` constant, `false` otherwise.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
 * @par       Reference variables
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint32    |g_RdEfuseValue|Reads the global variable containing the result of the last eFuse read.|
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
 * |cy_en_srom_driver_status_t|getResult|Holds the return status from the SROM API call.|
 * |uint32    |DEAD_ACC_bitsValue|Temporary variable to hold the extracted bits from the `DEAD_ACC_RESTRICT` constant.|
 * |bool      |retval    |Holds the final boolean return value.|
 * @brief     Reads an eFuse byte related to dead access restrictions and compares it against the expected value from a pre-defined constant.
 * @note      This function is part of the verification process for the "Transition to Secure" operation. It ensures that the access restrictions for the DEAD lifecycle state have been correctly programmed into the eFuses.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
static bool CompareEfuseValue_DeadAccess(uint32_t ReadEfuseAddr)
{
  /*** API Result ***/
  cy_en_srom_driver_status_t getResult;
  uint32_t DEAD_ACC_bitsValue;
  bool retval = false;

  /*** Call API ReadFuseByte ***/
  getResult = Cy_ReadFuseByte(ReadEfuseAddr);
  if(getResult == CY_SROM_DR_SUCCEEDED)
  {
    /* DEAD_ACC_RESTRICT */
    /* Compare the bit value of DEAD_ACC_RESTRICT */
    if (ReadEfuseAddr == 64u) {
      DEAD_ACC_bitsValue = (DEAD_ACC_RESTRICT & 0x000000FFu);
      if (DEAD_ACC_bitsValue == g_RdEfuseValue) {
        /* Matched*/
        retval = true;
      }
    } else if (ReadEfuseAddr == 65u) {
      DEAD_ACC_bitsValue = ((DEAD_ACC_RESTRICT & 0x0000FF00u) >> 8u);
      if (DEAD_ACC_bitsValue == g_RdEfuseValue) {
        /* Matched*/
        retval = true;
      }
    } else if (ReadEfuseAddr == 66u) {
      DEAD_ACC_bitsValue = ((DEAD_ACC_RESTRICT & 0x001F0000u) >> 16u);
      if (DEAD_ACC_bitsValue == g_RdEfuseValue) {
        /* Matched*/
        retval = true;
      }
    } else {
      /* Do nothing */
    }
  }

  return retval;
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint32    |ReadEfuseAddr|The address of the eFuse byte to read and compare.|
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |bool      |retval    |`true` if the read eFuse value matches the corresponding bits of the `SECURE_ACC_RESTRICT` constant, `false` otherwise.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
 * @par       Reference variables
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint32    |g_RdEfuseValue|Reads the global variable containing the result of the last eFuse read.|
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
 * |cy_en_srom_driver_status_t|getResult|Holds the return status from the SROM API call.|
 * |uint32    |SECURE_ACC_bitsValue|Temporary variable to hold the extracted bits from the `SECURE_ACC_RESTRICT` constant.|
 * |bool      |retval    |Holds the final boolean return value.|
 * @brief     Reads an eFuse byte related to secure access restrictions and compares it against the expected value from a pre-defined constant.
 * @note      This function is part of the verification process for the "Transition to Secure" operation. It ensures that the access restrictions for the SECURE lifecycle state have been correctly programmed into the eFuses.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
static bool CompareEfuseValue_SecureAccess(uint32_t ReadEfuseAddr)
{
  /*** API Result ***/
  cy_en_srom_driver_status_t getResult;
  uint32_t SECURE_ACC_bitsValue;
  bool retval = false;

  /*** Call API ReadFuseByte ***/
  getResult = Cy_ReadFuseByte(ReadEfuseAddr);
  if(getResult == CY_SROM_DR_SUCCEEDED)
  {
    /* SECURE_ACC_RESTRICT */
    /* Compare the bit value of SECURE_ACC_RESTRICT */
    if (ReadEfuseAddr == 60u) {
      SECURE_ACC_bitsValue = (SECURE_ACC_RESTRICT & 0x000000FFu);
      if (SECURE_ACC_bitsValue == g_RdEfuseValue) {
        /* Matched*/
        retval = true;
      }
    } else if (ReadEfuseAddr == 61u) {
      SECURE_ACC_bitsValue = ((SECURE_ACC_RESTRICT & 0x0000FF00u) >> 8u);
      if (SECURE_ACC_bitsValue == g_RdEfuseValue) {
        /* Matched*/
        retval = true;
      }
    } else if (ReadEfuseAddr == 62u) {
      SECURE_ACC_bitsValue = ((SECURE_ACC_RESTRICT & 0x001F0000u) >> 16u);
      if (SECURE_ACC_bitsValue == g_RdEfuseValue) {
        /* Matched*/
        retval = true;
      }
    } else {
      /* Do nothing */
    }
  }
  
  return retval;
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint32    |Margin_efuseAddr|The address of the eFuse byte to read.|
 * |uint32    |Margin_Ctl|The margin control setting (0 for -50%, 3 for +100%).|
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |cy_en_srom_driver_status_t|retval|The status from the SROM API call, or CY_SROM_DR_API_ERROR if `Margin_Ctl` is invalid.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
 * @par       Reference variables
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
 * @par       Output variables
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint32    |g_RdEfuseMarginValue50|Global variable is updated if Margin_Ctl is 0.|
 * |uint32    |g_RdEfuseMarginValue100|Global variable is updated if Margin_Ctl is 3.|
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
 * |un_srom_api_args_t|apiArgs|Structure to hold arguments for the SROM API call.|
 * |un_srom_api_resps_t|apiResp|Structure to hold the response from the SROM API call.|
 * |cy_en_srom_driver_status_t|retval|Holds the return status of the SROM operation.|
 * @brief     Reads a single eFuse byte with a specified read margin using the SROM API.
 * @note      This is a wrapper for the `CY_SROM_OP_READ_FUSE_BYTE_MARGIN` SROM command. It stores the result in one of two global variables (`g_RdEfuseMarginValue50` or `g_RdEfuseMarginValue100`) depending on the margin control parameter.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
static cy_en_srom_driver_status_t Cy_ReadFuseByteMargin(uint32_t Margin_efuseAddr, uint32_t Margin_Ctl)
{
  /* Prepares arguments to be passed to SROM API */
  un_srom_api_args_t apiArgs = {0ul};
  un_srom_api_resps_t apiResp = {0ul};
  cy_en_srom_driver_status_t retval;
  apiArgs.RdFuseMargin.arg0.eFuseAddr = Margin_efuseAddr;
  apiArgs.RdFuseMargin.arg0.marginCtl = Margin_Ctl;
  apiArgs.RdFuseMargin.arg0.Opcode = (uint32_t)CY_SROM_OP_READ_FUSE_BYTE_MARGIN;

  /* Call SROM API driver and process response */
  retval = Cy_Srom_CallApi(&apiArgs, &apiResp);
  if(retval == CY_SROM_DR_SUCCEEDED)
  {
    if (MarginCTL == 0u) {
      /* 0: Low resistance -50% */
      g_RdEfuseMarginValue50 = apiResp.RdFuseMargin.resp0.ReadByte;
    } else if (MarginCTL == 3u) { 
      /* Higher resistance(+100% from nominal) */
      g_RdEfuseMarginValue100 = apiResp.RdFuseMargin.resp0.ReadByte;
    } else {
      /* MarginCTL parameter error */
      retval = CY_SROM_DR_API_ERROR;
    }
  }
  return retval;
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
/* date      2025-07-16 */
/************************************************************************************************/
static Std_ReturnType HandleReadStage(uint8 *lifeCycleState, uint8 *protectionState)
{
  cy_en_srom_driver_status_t sromDrvStatus;
  Std_ReturnType ReturnValue = E_NOT_OK;
  un_srom_api_args_t params = {0u};
  un_srom_api_resps_t getResp = {0u};

  params.SiId.arg0.Opcode = (uint32_t)CY_SROM_OP_SILICON_ID;
  params.SiId.arg0.IdType = SILICON_ID_TYPE;

  sromDrvStatus = Cy_Srom_CallApi(&params, &getResp);

  if (sromDrvStatus == CY_SROM_DR_SUCCEEDED)
  {
    ReturnValue      = E_OK;
    *lifeCycleState  = (uint8)(getResp.SiId.resp0.IdType1.LifeCycleState); /* QAC Deviations: (No 2814) Pointer lifeCycleState has been already evaluated at vHsm_Custom_ProcessJob() where this function was called. */
    *protectionState = (uint8)(getResp.SiId.resp0.IdType1.ProtectionState); /* QAC Deviations: (No 2814) Pointer protectionState has been already evaluated at vHsm_Custom_ProcessJob() where this function was called. */
  }
  else
  {
    *lifeCycleState  = (uint8)LIFE_CYCLE_STATE_UNDEFINE; /* QAC Deviations: (No 2814) Pointer lifeCycleState has been already evaluated at vHsm_Custom_ProcessJob() where this function was called. */
    *protectionState = (uint8)PROTECTION_STATE_UNDEFINE; /* QAC Deviations: (No 2814) Pointer protectionState has been already evaluated at vHsm_Custom_ProcessJob() where this function was called. */
  }

  return ReturnValue;
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint8     |requestType|The type of RMA request (TRANSITION_RMA_REQ or OPEN_RMA_REQ).|
 * |const uint8*|signature|Pointer to the buffer containing the digital signature for the RMA request.|
 * |uint8     |signatureLength|Length of the digital signature.|
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |RMAReturnStatus|reval|A detailed status code indicating the result of the RMA operation.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
 * @par       Reference variables
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
 * @par       Output variables
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint32[]  |Digital_Signature_RMA|The global buffer is updated with the provided signature.|
 * |cy_rma_config_t|RMAParameterConfig|The global RMA configuration structure is fully populated before the SROM call.|
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
 * |RMAReturnStatus|reval|Holds the return status of the operation.|
 * |srom_api_args_t|Rma_params|Structure to hold arguments for the SROM API call.|
 * |un_srom_api_resps_t|Rma_resp|Structure to hold the response from the SROM API call.|
 * @brief     Handles a request to transition the device to the RMA (Return Material Authorization) lifecycle state.
 * @note      This function reads the device UID, populates the RMA configuration structure with the required parameters (opcodes, signature, etc.), and then calls the SROM API to perform the state transition. It translates the SROM API response into a more detailed `RMAReturnStatus`.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
static RMAReturnStatus HandleRmaRequest(uint8 requestType, const uint8 *signature, uint8 signatureLength)
{
  RMAReturnStatus reval = RMA_RET_NO_ERR;
  srom_api_args_t Rma_params = {0u};
  un_srom_api_resps_t Rma_resp = {0u};

  if ((requestType == TRANSITION_RMA_REQ) || (requestType == OPEN_RMA_REQ))
  {
    (void)ReadUidRMA();
    VStdLib_MemCpy(Digital_Signature_RMA, signature, signatureLength);
    if (requestType == TRANSITION_RMA_REQ)
    {
      RMAParameterConfig.OpCode = CY_SROM_OP_TRANSITION_RMA;
      RMAParameterConfig.ObjectSize = OBJECT_SIZE;
      RMAParameterConfig.CommandID = COMMND_ID_TRAN_TO_RMA;
      RMAParameterConfig.dataAddr = (uint32)&Digital_Signature_RMA;
    }
    else
    {
      RMAParameterConfig.OpCode = CY_SROM_OP_OPEN_RMA;
      RMAParameterConfig.ObjectSize = OBJECT_SIZE;
      RMAParameterConfig.CommandID = COMMND_ID_OPEN_RMA;
      RMAParameterConfig.dataAddr = (uint32)&Digital_Signature_RMA;
    }

    Rma_params.arg[0] = (uint32)&RMAParameterConfig;

    (void)Cy_Srom_CallApi((un_srom_api_args_t *)&Rma_params, &Rma_resp);

    if((Rma_resp.resp[0] & 0xF0000000u) == 0xA0000000u)
    {
      reval = RMA_RET_SUCCESS;
    }
    else
    {
      switch ((cy_en_srom_api_status_t)Rma_resp.resp[0])
      {
        case CY_SROM_STATUS_INVALID_PROTECTION:
          reval = RMA_RET_INVALID_PROTECTION;
          break;
        case CY_SROM_STATUS_EMB_FAIL:
          reval = RMA_RET_EMB_ACTIVE;
          break;
        case CY_SROM_STATUS_INVALID_SIGN:
          reval = RMA_RET_INVALID_SIGN;
          break;
        case CY_SROM_STATUS_INVALID_PUBLIC_KEY:
          reval = RMA_RET_INVALID_PUBLIC_KEY;
          break;
        default: 
          reval = RMA_RET_IPC_OR_TIMEOUT_ERR;
          break;
      }
    }
  }
  return reval;
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |PBKeyType |InputKeyType|The type of public key to check (2K or 3K).|
 * @par       Return value
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |VerifyKeyType|ReturnValue|Returns `VALID` if the key is present in SFlash, `INVALID` if it is not.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
 * @par       Reference variables
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |-         |-         |-                 |
 * @par       Output variables
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |cy_si_stc_public_key_2K_t*|pPublicKey2K|Pointer is updated to point to the SFlash address for the 2K key.|
 * |cy_si_stc_public_key_3K_t*|pPublicKey3K|Pointer is updated to point to the SFlash address for the 3K key.|
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
 * |uint8     |getResult |Stores the result of the memory comparison.|
 * |VerifyKeyType|ReturnValue|Holds the final verification status.|
 * |cy_si_stc_public_key_2K_t|PublicKey2K_Cmp|A zeroed-out structure used for comparison to check if the SFlash area is empty.|
 * |cy_si_stc_public_key_3K_t|PublicKey3K_Cmp|A zeroed-out structure used for comparison to check if the SFlash area is empty.|
 * @brief     Checks if a specific public key (2K or 3K) has been provisioned into SFlash.
 * @note      This function checks for key presence by comparing the content of the key's designated SFlash region against a zeroed-out buffer. If the memory is all zeros, the key is considered not present (`INVALID`).
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
static VerifyKeyType HandleCheckPBKey(PBKeyType InputKeyType)
{
  uint8 getResult = 0u;
  VerifyKeyType ReturnValue;
  
  /* Memset to zero before using */
  VStdLib_MemSet(&PublicKey2K_Cmp, 0, sizeof(PublicKey2K_Cmp));
  VStdLib_MemSet(&PublicKey3K_Cmp, 0, sizeof(PublicKey3K_Cmp));
  
  if(InputKeyType == KEY_2K)
  {
    pPublicKey2K = (cy_si_stc_public_key_2K_t *)PUBLIC_KEY2K_ADDR;
    getResult = (uint8)VStdLib_MemCmp(&PublicKey2K_Cmp, pPublicKey2K, sizeof(cy_si_stc_public_key_2K_t));
  }
  else if(InputKeyType == KEY_3K)
  {
    pPublicKey3K = (cy_si_stc_public_key_3K_t *)PUBLIC_KEY3K_ADDR;
    getResult = (uint8)VStdLib_MemCmp(&PublicKey3K_Cmp, pPublicKey3K, sizeof(cy_si_stc_public_key_3K_t));
  }

  if(getResult == E_OK)
  {
    ReturnValue = INVALID;
  }
  else
  {
    ReturnValue = VALID;
  }

  return ReturnValue;
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
 * |Std_ReturnType|retVal|E_OK if the check was successful, E_NOT_OK if the output pointer is NULL or the key element cannot be found.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint8* |outPtr    |Pointer to a variable that will be updated with the key status (MAC_KEY_NO_ERR or MAC_KEY_INVALID).|
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
 * |Std_ReturnType|retVal|Holds the return status of the operation.|
 * |Crypto_30_LibCv_SizeOfKeyElementsType|elementIndex|The index of the MAC key element in the crypto library's internal storage.|
 * @brief     Checks if the primary SHE MAC key has been provisioned and is valid.
 * @note      This function searches for the specific key element corresponding to the SHE MAC key and checks its validity flag. The result is returned via the output pointer.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/
static FUNC(Std_ReturnType, VHSM_CUSTOM_CODE) vHsm_Custom_CheckMacKey(uint8 *outPtr)
{
  Std_ReturnType retVal;
  Crypto_30_LibCv_SizeOfKeyElementsType elementIndex = VHSM_CUSTOM_ZERO;

  // Check for null pointer
  if (outPtr == NULL_PTR)
  {
    retVal = E_NOT_OK;
  }
  else 
  {
    // Search for the MAC key element
    retVal = Crypto_30_LibCv_Local_KeyElementSearch(
        CryptoConf_CryptoKey_She_MAC_Key,
        CryptoConf_CryptoKeyElement_Crypto_30_LibCv_Mac_Key_She,
        &elementIndex);

    // Check if the key element is valid
    if (retVal == E_OK)
    {
      /* QAC Deviations: (No 3383 - No 2284) Configuration and Generation rule of Crypto module is made sure the overflow does not occur. */
      if ((uint8)Crypto_30_LibCv_IsKeyElementValid(elementIndex) == FALSE)
      {
        *outPtr = MAC_KEY_INVALID;
      }
      else
      {
        if( MAC_KEY_IS_UNWRITTEN_KEY == SRAM_CM0_CM7_KEY_INFO_MAC_KEY )
        {
          *outPtr = MAC_KEY_INVALID;
        }
        else
        {
          *outPtr = MAC_KEY_NO_ERR;
        }
      }
    }
    else
    {
      *outPtr = MAC_KEY_INVALID;
    }
  }

  return retVal;
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
 * |Std_ReturnType|retVal|E_OK if successful, E_NOT_OK if key elements cannot be retrieved.|
 * @par       Argument specified address output
 * |Type      |Name      |Description       |
 * |:--------:|:--------:|:----------------:|
 * |uint8* |statusPtr |Pointer to a variable that will be updated with the 8-bit SHE status word.|
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
 * |Std_ReturnType|retVal|Holds the return status of the operation.|
 * |Crypto_30_LibCv_SizeOfKeyStorageType|bootProtectionElementIndexPtr|Index of the boot protection flag in storage.|
 * |Crypto_30_LibCv_SizeOfKeyStorageType|debuggerProtectionElementIndexPtr|Index of the debugger protection flag in storage.|
 * |uint32    |elementLength|Expected length of the flag elements (1 byte).|
 * @brief     Retrieves the emulated SHE status byte by reading internal software flags.
 * @note      Since the hardware does not provide a direct SHE status register, this function emulates it by reading the `BOOT_PROTECTION` and `DEBUGGER_PROTECTION` flags stored as key elements and constructing the status byte according to the SHE specification.
 */
/* author     FPT */
/* date      2025-07-16 */
/************************************************************************************************/

static FUNC(Std_ReturnType, CRYPTO_30_LIBCV_CODE) vHsm_Custom_She_Cmd_Get_Status(
  P2VAR(uint8, AUTOMATIC, CRYPTO_30_LIBCV_APPL_VAR) statusPtr)
{
  Std_ReturnType retVal;
  Crypto_30_LibCv_SizeOfKeyStorageType bootProtectionElementIndexPtr = 0u;
  Crypto_30_LibCv_SizeOfKeyStorageType debuggerProtectionElementIndexPtr = 0u;
  uint32 elementLength = 1u;

  /* Init status */
  *statusPtr = CRYPTO_30_LIBCV_SHE_CLEARED_STATUS; /* SBSW_CRYPTO_30_LIBCV_PTR_ACCESS */ /* QAC Deviations: (No 2814) Pointer statusPtr has been already evaluated at vHsm_Custom_ProcessJob() where this function was called. */

  /* Get BOOT_PROTECTION and DEBUGGER_PROTECTION element id */
  retVal = Crypto_30_LibCv_Local_KeyElementGetStorageIndex(Crypto_30_LibCv_GetSheInfoKeyRefOfSheKeyUpdate(), CRYPTO_KE_CUSTOM_SHE_BOOT_PROTECTION, &bootProtectionElementIndexPtr, &elementLength, CRYPTO_30_LIBCV_LENGTH_CHECK_EQUAL); /* SBSW_CRYPTO_30_LIBCV_STACK_VARIABLE_AS_PTR */
  retVal |= Crypto_30_LibCv_Local_KeyElementGetStorageIndex(Crypto_30_LibCv_GetSheInfoKeyRefOfSheKeyUpdate(), CRYPTO_KE_CUSTOM_SHE_DEBUGGER_PROTECTION, &debuggerProtectionElementIndexPtr, &elementLength, CRYPTO_30_LIBCV_LENGTH_CHECK_EQUAL); /* SBSW_CRYPTO_30_LIBCV_STACK_VARIABLE_AS_PTR */

  if (retVal == E_OK)
  {
    /* Check boot protection */
    /* QAC Deviations: (No 2844) Crypto_30_LibCv_GetAddrKeyStorage is static code from Vector.So the pointer always differ NULL.
       This warning can ignore */
    if ((*(Crypto_30_LibCv_GetAddrKeyStorage(bootProtectionElementIndexPtr)) == 1u))
    {
      *statusPtr |= CRYPTO_30_LIBCV_SHE_STATUS_BOOT_FINISHED; /* SBSW_CRYPTO_30_LIBCV_PTR_ACCESS */
      *statusPtr |= CRYPTO_30_LIBCV_SHE_STATUS_BOOT_OK; /* SBSW_CRYPTO_30_LIBCV_PTR_ACCESS */
    }

    /* Check debugger protection */
    if ((*(Crypto_30_LibCv_GetAddrKeyStorage(debuggerProtectionElementIndexPtr)) == 0u))
    {
      *statusPtr |= CRYPTO_30_LIBCV_SHE_STATUS_EXT_DEBUGGER; /* SBSW_CRYPTO_30_LIBCV_PTR_ACCESS */
    }
  }
  else
  {
    retVal = E_NOT_OK;
  }

  return retVal;
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:----------------:|
 * |- |- |- |
 * 
 * @par       Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:----------------:|
 * |void |- |Function does not return a value|
 * 
 * @par       Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:----------------:|
 * |- |- |- |
 * 
 * @par       Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:----------------:|
 * |- |- |- |
 * 
 * @par       Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:----------------:|
 * |- |- |- |
 * 
 * @par       Reference registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:----------------:|
 * |uint32 |CPUSS->unRAM0_CTL0|RAM0 control register used to configure ECC checking|
 * 
 * @par       Output registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:----------------:|
 * |uint32 |CPUSS->unRAM0_CTL0|ECC check disable bit is set|
 * 
 * @par       Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:----------------:|
 * |- |- |- |
 * 
 * @brief     Disables ECC checking for RAM0 by setting the ECC_CHECK_DIS bit.
 * @note      This function modifies the RAM0 control register to disable ECC error detection.
 */
/* author     FPT */
/* date       2025-10-30 */
/************************************************************************************************/
static void Disable_RAM0_ECC_Check(void)
{
  CPUSS->unRAM0_CTL0.u32Register |= ECC_CHECK_DIS;
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:----------------:|
 * |volatile stc_FAULT_STRUCT_t*|base|Pointer to fault structure to be cleared|
 * 
 * @par       Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:----------------:|
 * |void |- |Function does not return a value|
 * 
 * @par       Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:----------------:|
 * |- |- |- |
 * 
 * @par       Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:----------------:|
 * |- |- |- |
 * 
 * @par       Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:----------------:|
 * |- |- |- |
 * 
 * @par       Reference registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:----------------:|
 * |uint32 |base->unMASK1|Used to apply and clear ECC fault mask|
 * |uint32 |base->unSTATUS|Used to check and clear fault status validity|
 * 
 * @par       Output registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:----------------:|
 * |uint32 |base->unMASK1|ECC fault mask cleared|
 * |uint32 |base->unSTATUS|Fault status cleared if valid|
 * 
 * @par       Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:----------------:|
 * |- |- |- |
 * 
 * @brief     Clears ECC fault trace by resetting fault mask and status registers.
 * @note      This function ensures that any valid ECC fault status is cleared and the fault mask is reset.
 */
/* author     FPT */
/* date       2025-10-30 */
/************************************************************************************************/
static void Clear_ECC_Fault_Trace(volatile stc_FAULT_STRUCT_t* base)
{
  base->unMASK1.u32Register = SRAM0_NC_ECC_MASK;                      /* Set RAMC0_NC_ECC mask */
  base->unMASK1.u32Register;                                          /* dummy read */
  base->unMASK1.u32Register = 0;                                      /* Clear All mask */
  base->unMASK1.u32Register;                                          /* dummy read */
  if ((base->unSTATUS.u32Register & FAULT_STATUS_VALID) != 0u)        /* Is fault valid? */
  {
    base->unSTATUS.u32Register = 0u;                                  /* Clear valid */
    base->unSTATUS.u32Register;                                       /* dummy read */
  }
}

/************************************************************************************************/
/**
 * @par       Arguments
 * |Type |Name |Description |
 * |:--------:|:--------:|:----------------:|
 * |- |- |- |
 * 
 * @par       Return value
 * |Type |Name |Description |
 * |:--------:|:--------:|:----------------:|
 * |void |- |Function does not return a value|
 * 
 * @par       Argument specified address output
 * |Type |Name |Description |
 * |:--------:|:--------:|:----------------:|
 * |- |- |- |
 * 
 * @par       Reference variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:----------------:|
 * |- |- |- |
 * 
 * @par       Output variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:----------------:|
 * |- |- |- |
 * 
 * @par       Reference registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:----------------:|
 * |uint32 |CPUSS->unRAM0_CTL0|RAM0 control register used to configure ECC checking|
 * 
 * @par       Output registers
 * |Type |Name |Description |
 * |:--------:|:--------:|:----------------:|
 * |uint32 |CPUSS->unRAM0_CTL0|ECC check disable bit is cleared|
 * 
 * @par       Automatic variables
 * |Type |Name |Description |
 * |:--------:|:--------:|:----------------:|
 * |- |- |- |
 * 
 * @brief     Enables ECC checking for RAM0 by clearing the ECC_CHECK_DIS bit.
 * @note      This function modifies the RAM0 control register to enable ECC error detection.
 */
/* author     FPT */
/* date       2025-10-30 */
/************************************************************************************************/
static void Enable_RAM0_ECC_Check(void)
{
  CPUSS->unRAM0_CTL0.u32Register &= (~ECC_CHECK_DIS);
}

/** @cond INTERNAL */
#define VHSM_CUSTOM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_19.1 */
/** @endcond */
/**********************************************************************************************************************
 * Module specific MISRA deviations
 *********************************************************************************************************************/
/* Module specific MISRA deviations:


MD_VHSM_CUSTOM_UNUSED_PARAMETER
Reason:       The API is designed to be the same for multiple sub components. Some implementations don't use a parameter.
Risk:         Unused parameter may be less efficient
Prevention:   Code review, tests

 */

/* SBSW_JUSTIFICATION_BEGIN
SBSW_JUSTIFICATION_END */

/* COV_JUSTIFICATION_BEGIN

\ID COV_VHSM_CUSTOM_LOCAL_DEFINE
\ACCEPT TX
\REASON VHSM_LOCAL is always defined externally.

\ID COV_VHSM_CUSTOM_NOTUSED
\ACCEPT X
\REASON Function is never referenced and therefore not used. For comparability reasons it should still be available for future vHsm Versions.

\ID COV_VHSM_CUSTOM_CUSTOM_KEY_ELEMENTS
\ACCEPT TX
\REASON The Crypto needs custom key elements, which could be defined in other modules as well.

COV_JUSTIFICATION_END */

/**********************************************************************************************************************
 *  END OF FILE: vHsm_Custom.c
 *********************************************************************************************************************/
 
