/***************************************************************************//**
* \file main_cm0plus.c
*
* \brief
* Main file for CM0+
*
********************************************************************************
* \copyright
* Copyright 2016-2019, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "cy_project.h"
#include "cy_device_headers.h"

#if (CY_USE_PSVP == 1)
    #define USER_LED_PORT           CY_AB_LED_PORT
    #define USER_LED_PIN            CY_AB_LED_PIN
    #define USER_LED_PIN_MUX        CY_AB_LED_PIN_MUX
#else
    #define USER_LED_PORT           CY_CB_USER_LED1_PORT
    #define USER_LED_PIN            CY_CB_USER_LED1_PIN
    #define USER_LED_PIN_MUX        CY_CB_USER_LED1_PIN_MUX 
#endif

void IpcNotifyInt_ISR(void);

cy_stc_gpio_pin_config_t user_led_port_pin_cfg =
{
    .outVal    = 0ul,
    .driveMode = CY_GPIO_DM_STRONG_IN_OFF,
    .hsiom     = USER_LED_PIN_MUX,
    .intEdge   = 0ul,
    .intMask   = 0ul,
    .vtrip     = 0ul,
    .slewRate  = 0ul,
    .driveSel  = 0ul,
};

#define USED_IPC_CHANNEL 7
#define IPC_NOTIFY_CPU_IRQ_INDEX    CPUIntIdx2_IRQn
#define IPC_NOTIFY_INT_NUMBER   7

static cy_stc_sysint_irq_t stcSysIntIpcNotifyInt = 
{
    .sysIntSrc = (cy_en_intr_t)(cpuss_interrupts_ipc_0_IRQn + USED_IPC_CHANNEL),
    .intIdx    = IPC_NOTIFY_CPU_IRQ_INDEX,
    .isEnabled = true
};


static unsigned char sleepflag = 0;
static unsigned long intSleep = 0x00000000;


int main(void)
{
	__enable_irq();
	
    SystemInit();

    /* Enable CM7_0/1. CY_CORTEX_M7_APPL_ADDR is calculated in linker script, check it in case of problems. */
//    Cy_SysEnableApplCore(CORE_CM7_0, CY_CORTEX_M7_0_APPL_ADDR);
//    Cy_SysEnableApplCore(CORE_CM7_1, CY_CORTEX_M7_1_APPL_ADDR);
    Cy_SysEnableApplCore(CORE_CM7_0, 0x10090400);
    Cy_SysTick_DelayInUs(100000ul);
    Cy_SysEnableApplCore(CORE_CM7_1, 0x10090400);

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
//   Cy_GPIO_Pin_Init(USER_LED_PORT, USER_LED_PIN, &user_led_port_pin_cfg);

	/* IPC割り込みラインの設定 */
    Cy_SysInt_InitIRQ(&stcSysIntIpcNotifyInt);
	
    /* Setup IPC interrupt system handler */
    Cy_SysInt_SetSystemIrqVector((cy_en_intr_t)(cpuss_interrupts_ipc_0_IRQn + USED_IPC_CHANNEL), IpcNotifyInt_ISR);

    NVIC_ClearPendingIRQ(IPC_NOTIFY_CPU_IRQ_INDEX);
    NVIC_EnableIRQ(IPC_NOTIFY_CPU_IRQ_INDEX);

    Cy_IPC_Drv_SetInterruptMask
    (
        Cy_IPC_Drv_GetIntrBaseAddr(IPC_NOTIFY_INT_NUMBER),
        CY_IPC_NO_NOTIFICATION,
        (1uL << USED_IPC_CHANNEL)
    );

    for(;;)
    {
        // Wait 0.05 [s]
//        Cy_SysTick_DelayInUs(50000ul);

//        Cy_GPIO_Inv(USER_LED_PORT, USER_LED_PIN);
       	if( 0xFFFFFFFFUL == intSleep )
    	{
    		/* DeepSleep */
    		if(0u != _FLD2VAL(SRSS_PWR_CTL_LPM_READY, SRSS->unPWR_CTL.u32Register)){
					Cy_SysPm_DeepSleep(CY_SYSPM_WAIT_FOR_INTERRUPT);
    				
//    				intSleep = 0;
			}
//    		sleepflag = 0;
//    		intSleep = 0;
   		}
    }
}

/*****************************************************************************
 ** \brief IpcNotifyInt_ISR
 *****************************************************************************/
void IpcNotifyInt_ISR(void)
{
	uint32_t interruptMasked = 
            Cy_IPC_Drv_ExtractAcquireMask
            (
                Cy_IPC_Drv_GetInterruptStatusMasked
                (
                    Cy_IPC_Drv_GetIntrBaseAddr(IPC_NOTIFY_INT_NUMBER)
                )
            );
	/* 割り込みが通知チャネルによって引き起こされているかどうかを確認 */
    if (interruptMasked == (1uL << USED_IPC_CHANNEL))
    {
        /* 割り込みをクリア */
        Cy_IPC_Drv_ClearInterrupt
        (
            Cy_IPC_Drv_GetIntrBaseAddr(IPC_NOTIFY_INT_NUMBER), 
            CY_IPC_NO_NOTIFICATION,
            interruptMasked
        );
    	
    	uint32_t intCm7_0_Data;
        if(CY_IPC_DRV_SUCCESS == Cy_IPC_Drv_ReadMsgWord(Cy_IPC_Drv_GetIpcBaseAddress(USED_IPC_CHANNEL), &intCm7_0_Data))
        {
			intSleep = intCm7_0_Data;
        }
        /* ロックを解除 */
        (void)Cy_IPC_Drv_LockRelease(Cy_IPC_Drv_GetIpcBaseAddress(USED_IPC_CHANNEL), CY_IPC_NO_NOTIFICATION);
    }
	
	sleepflag = 1;
}



/* [] END OF FILE */
