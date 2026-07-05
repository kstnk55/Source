/**
 * @file Platform_Traveo2_vHsm.c
 * @brief Public header: vHsm.h, vHsm_Hal_Cfg.h
 * @details Overview: Platform-specific implementation for vHSM on Traveo II microcontroller
 */

#include "vHsm.h"
#include "vHsm_Hal_Cfg.h"

/* Cypress LLD */
#if (VHSM_HAL_OBJECTINFO == STD_ON)
#include "CySldCrypto_Interrupt.h"
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
 * @brief Interrupt Service Routine for the Traveo II cryptographic hardware accelerator
 * @note This function is called by the OS when a cryptographic hardware accelerator interrupt occurs.
 */
/* author Vector Informatik GmbH */
/* date 2023 */
/************************************************************************************************/
/* Handler for crypto accelerator interrupts */
/* QAC deviation: (No 3408) This is Vector code implement. So, this warning can ignore and doesn't affect to the current behavior. */
void Os_Isr_CryptoHandler(void) 
{
#if (VHSM_HAL_OBJECTINFO == STD_ON)
  CySldCrypto_Isr_Cat1();
#endif
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
 * @brief Main task function for the Vector Hardware Security Module (vHSM)
 * @note This function implements the main task for the vHSM module and is scheduled by the
 *       operating system.
 */
/* author Vector Informatik GmbH */
/* date 2023 */
/************************************************************************************************/
/* main task */
/* QAC deviation: (No 3408) This is Vector code implement. So, this warning can ignore and doesn't affect to the current behavior. */
void Os_Task_vHsmTask(void) 
{
  vHsm_StartupCallout();
  vHsm_Main();
  (void)TerminateTask();
}
