/**
 * @file vHsm_Callout_Stubs.h
 * @brief Callout stubs header for vHsm
 * @details Header file for vHsm callout stub macros and types.
 */
#if !defined (VHSM_CALLOUT_STUBS_H)
# define VHSM_CALLOUT_STUBS_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Macros                                                **
*******************************************************************************/
/**
 * @def			DAP_CORRECT_HASHED_PASSWORD
 * @value		-
 * @resolution	-
 * @brief 		DAP correct hashed password
 */
#define DAP_CORRECT_HASHED_PASSWORD              {0xa8u, 0xfau, 0xedu, 0x6au, 0xbbu, 0xf3u, 0x5cu, 0x12u,\
                                                  0xa4u, 0xb2u, 0x6eu, 0x40u, 0xf6u, 0xfeu, 0xb1u, 0x9du,\
                                                  0x73u, 0x6du, 0x90u, 0x04u, 0x5cu, 0x83u, 0xb9u, 0xf9u,\
                                                  0xa3u, 0x1fu, 0x63u, 0x8du, 0x32u, 0x3eu, 0x68u, 0x11u}

#define SRAM_CM0_CM7_KEYSETVALID_REPRO      (*((volatile uint8 *)0x28013FB0U))
#define SRAM_CM0_CM7_KEYSETVALID_MASTERECU  (*((volatile uint8 *)0x28013FB1U))
#define SRAM_CM0_CM7_KEYSETVALID_TYPEX      (*((volatile uint8 *)0x28013FB2U))

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/** @cond INTERNAL */
Std_ReturnType ClearKeyInfoBeforeRma(void);
FUNC(void, VHSM_CODE) UpdateIntegrityStateIntoWorkFlash(uint8 IntegrityState);
Std_ReturnType ClockSetToFLL100MHz(void);
Std_ReturnType ClockRestoreToPLL160MHz(void);

extern void IpcNotifyInt_ISR(void);
extern void ISR1_Handler(void);
extern void Crypto_30_Hwa_Hw_Init(void);

extern void CM0_Debug_Init(void);

/**********************************************************************************************************************
 *  GLOBAL VARIABLES
 *********************************************************************************************************************/
extern uint16 ResetCounter;
extern uint16 Dummy_Padding1;
extern uint16 AppStatus;
extern uint16 Dummy_Padding2;

#endif /* VHSM_CALLOUT_STUBS_H */
/** @endcond */
