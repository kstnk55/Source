/***************************************************************************//**
* \file bsp_tviic2d6m_327bga_device_revc_evk_revb.h
*
* \brief
* Project specific header
*
* \note
* It contains references to all generated header files and should
* not be modified.
*
********************************************************************************
* \copyright
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef BB_BSP_TVIIC2D6M_327BGA_DEVICE_REVC_EVK_REVB_H
#define BB_BSP_TVIIC2D6M_327BGA_DEVICE_REVC_EVK_REVB_H

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
/******************************************************************************/

// tviic2d6m - 327-BGA Package devices
    
// #if (CY_USE_PSVP == 0) (--> Silicon), project setting CY_USE_PSVP should be changed to '0'
// select the supported or required device accordingly
  
#if (CY_USE_PSVP == 0) && ( defined(CYT4DNJBAS) || defined(CYT4DNJBBS) || \
                              defined(CYT4DNJBCS) || defined(CYT4DNJBDS) || \
                              defined(CYT4DNJBES) || defined(CYT4DNJBFS) || \
                              defined(CYT4DNJBGS) || defined(CYT4DNJBHS) || \
                              defined(CYT4DNJBJS) || defined(CYT4DNJBKS) || \
                              defined(CYT4DNJBLS) || defined(CYT4DNJBMS) || \
                              defined(CYT4DNJBNS) || defined(CYT4DNJBPS) || \
                              defined(CYT4DNJBQS) || defined(CYT4DNJBRS) || \
                              defined(CYT4DNJBSS) || defined(CYT4DNJBTS) || \
                              defined(CYT4DNJBUS) || defined(CYT4DNJBVS) || \
                              defined(CYT4DNJBWS) || defined(CYT4DNJBXS) || \
                              defined(CYT4DNJBYS) || defined(CYT4DNJBZS) )
    
/******************************************************************************/
/******************************************************************************/

//                              CPU Board Entities

/******************************************************************************/
/******************************************************************************/

/******************************************************************************/
/*                      USER LED's                                            */
/******************************************************************************/    

#define CY_USER_LED1_PORT                       GPIO_PRT6 		// LED1
#define CY_USER_LED1_PIN                        2
#define CY_USER_LED1_PIN_MUX                    P6_2_GPIO
    
#define CY_USER_LED2_PORT                       GPIO_PRT6 		// LED2
#define CY_USER_LED2_PIN                        3
#define CY_USER_LED2_PIN_MUX                    P6_3_GPIO
    
#define CY_USER_LED3_PORT                       GPIO_PRT6 		// LED3
#define CY_USER_LED3_PIN                        4
#define CY_USER_LED3_PIN_MUX                    P6_4_GPIO


/******************************************************************************/
/*                      USER BUTTON's                                         */
/******************************************************************************/

#define CY_USER_BUTTON_LEFT_PORT                GPIO_PRT11 		// SW3
#define CY_USER_BUTTON_LEFT_PIN                 7
#define CY_USER_BUTTON_LEFT_PIN_MUX             P11_7_GPIO
  
#define CY_USER_BUTTON_RIGHT_PORT               GPIO_PRT6 		// SW6
#define CY_USER_BUTTON_RIGHT_PIN                7
#define CY_USER_BUTTON_RIGHT_PIN_MUX            P6_7_GPIO
    
#define CY_USER_BUTTON_UP_PORT                  GPIO_PRT7 		// SW7
#define CY_USER_BUTTON_UP_PIN                   1
#define CY_USER_BUTTON_UP_PIN_MUX               P7_1_GPIO
  
#define CY_USER_BUTTON_WAKE_PORT                GPIO_PRT3 		// SW5
#define CY_USER_BUTTON_WAKE_PIN                 1
#define CY_USER_BUTTON_WAKE_PIN_MUX             P3_1_GPIO
#define CY_USER_BUTTON_WAKE_SOURCE              CY_SYSPM_WAKEUP_PIN0    // HIBERNATE_WAKEUP[0]
    
/* Setup GPIO for BUTTONs interrupt sources */
#define CY_USER_BUTTON_LEFT_IRQN                ioss_interrupts_gpio_dpslp_11_IRQn
#define CY_USER_BUTTON_RIGHT_IRQN               ioss_interrupts_gpio_dpslp_6_IRQn
#define CY_USER_BUTTON_UP_IRQN                  ioss_interrupts_gpio_dpslp_7_IRQn
#define CY_USER_BUTTON_WAKE_IRQN                ioss_interrupts_gpio_dpslp_3_IRQn


/******************************************************************************/
/*                      ADC POT                                               */
/******************************************************************************/

#define CY_ADC_POT_PORT                         GPIO_PRT7
#define CY_ADC_POT_PIN                          0
#define CY_ADC_POT_PIN_MUX                      P7_0_GPIO
  
#define CY_ADC_POT_MACRO                        PASS0_SAR0
#define CY_ADC_POT_IN_NO                        10
#define CY_ADC_POT_PCLK                         PCLK_PASS0_CLOCK_SAR0
#define CY_ADC_POT_IRQN                         pass_0_interrupts_sar_0_IRQn    // sar logical channel irq

/******************************************************************************/
/*                      SCB Mux                                               */
/******************************************************************************/
/* USB-UART Mux */
#define CY_USB_SCB_UART_TYPE                    SCB11
  
#define CY_USB_SCB_UART_RX_PORT                 GPIO_PRT0
#define CY_USB_SCB_UART_RX_PIN                  4
#define CY_USB_SCB_UART_RX_PIN_MUX              P0_4_SCB11_UART_RX

#define CY_USB_SCB_UART_TX_PORT                 GPIO_PRT0
#define CY_USB_SCB_UART_TX_PIN                  5
#define CY_USB_SCB_UART_TX_PIN_MUX              P0_5_SCB11_UART_TX

#define CY_USB_SCB_UART_PCLK                    PCLK_SCB11_CLOCK
#define CY_USB_SCB_UART_IRQN                    scb_11_interrupt_IRQn


/******************************************************************************/
/*                      SMIF0 Definitions                                     */
/******************************************************************************/
#define CY_BSP_HDR_SMIF0_AVAILABLE              // Definitions for this functionality are available

#define CY_SMIF0_CLK_INV_PORT                   GPIO_PRT24
#define CY_SMIF0_CLK_INV_PIN                    0
#define CY_SMIF0_CLK_INV_PIN_MUX                P24_0_SMIF0_SMIF0_SPIHB_CLK
    
#define CY_SMIF0_CLK_PORT                       GPIO_PRT24
#define CY_SMIF0_CLK_PIN                        1
#define CY_SMIF0_CLK_PIN_MUX                    P24_1_SMIF0_SMIF0_SPIHB_CLK
  
#define CY_SMIF0_RWDS_PORT                      GPIO_PRT23
#define CY_SMIF0_RWDS_PIN                       4
#define CY_SMIF0_RWDS_PIN_MUX                   P23_4_SMIF0_SMIF0_SPIHB_RWDS
  
#define CY_SMIF0_SELECT0_PORT                   GPIO_PRT25
#define CY_SMIF0_SELECT0_PIN                    2
#define CY_SMIF0_SELECT0_PIN_MUX                P25_2_SMIF0_SMIF0_SPIHB_SELECT0
  
#define CY_SMIF0_SELECT1_PORT                   GPIO_PRT25
#define CY_SMIF0_SELECT1_PIN                    5
#define CY_SMIF0_SELECT1_PIN_MUX                P25_5_SMIF0_SMIF0_SPIHB_SELECT1
  
#define CY_SMIF0_DATA0_PORT                     GPIO_PRT25
#define CY_SMIF0_DATA0_PIN                      0
#define CY_SMIF0_DATA0_PIN_MUX                  P25_0_SMIF0_SMIF0_SPIHB_DATA0
  
#define CY_SMIF0_DATA1_PORT                     GPIO_PRT25
#define CY_SMIF0_DATA1_PIN                      3
#define CY_SMIF0_DATA1_PIN_MUX                  P25_3_SMIF0_SMIF0_SPIHB_DATA1
  
#define CY_SMIF0_DATA2_PORT                     GPIO_PRT23
#define CY_SMIF0_DATA2_PIN                      1
#define CY_SMIF0_DATA2_PIN_MUX                  P23_1_SMIF0_SMIF0_SPIHB_DATA2
  
#define CY_SMIF0_DATA3_PORT                     GPIO_PRT23
#define CY_SMIF0_DATA3_PIN                      2
#define CY_SMIF0_DATA3_PIN_MUX                  P23_2_SMIF0_SMIF0_SPIHB_DATA3
  
#define CY_SMIF0_DATA4_PORT                     GPIO_PRT23
#define CY_SMIF0_DATA4_PIN                      0
#define CY_SMIF0_DATA4_PIN_MUX                  P23_0_SMIF0_SMIF0_SPIHB_DATA4
  
#define CY_SMIF0_DATA5_PORT                     GPIO_PRT23
#define CY_SMIF0_DATA5_PIN                      3
#define CY_SMIF0_DATA5_PIN_MUX                  P23_3_SMIF0_SMIF0_SPIHB_DATA5
  
#define CY_SMIF0_DATA6_PORT                     GPIO_PRT25
#define CY_SMIF0_DATA6_PIN                      1
#define CY_SMIF0_DATA6_PIN_MUX                  P25_1_SMIF0_SMIF0_SPIHB_DATA6
  
#define CY_SMIF0_DATA7_PORT                     GPIO_PRT25
#define CY_SMIF0_DATA7_PIN                      4
#define CY_SMIF0_DATA7_PIN_MUX                  P25_4_SMIF0_SMIF0_SPIHB_DATA7
    
#define CY_SMIF_S25FXXXS                        (0u)
#define CY_SMIF_S25FXXXL                        (1u)
#define CY_SMIF0_QUAD_MEMORY                    CY_SMIF_S25FXXXL

// IO connections P7.2 kept for Semper Flash interrupt.


/******************************************************************************/
/*                      SMIF1 Definitions                                     */
/******************************************************************************/
#define CY_BSP_HDR_SMIF1_AVAILABLE              // Definitions for this functionality are available

#define CY_SMIF1_CLK_INV_PORT                   GPIO_PRT27
#define CY_SMIF1_CLK_INV_PIN                    0
#define CY_SMIF1_CLK_INV_PIN_MUX                P27_0_SMIF0_SMIF1_SPIHB_CLK
    
#define CY_SMIF1_CLK_PORT                       GPIO_PRT27
#define CY_SMIF1_CLK_PIN                        1
#define CY_SMIF1_CLK_PIN_MUX                    P27_1_SMIF0_SMIF1_SPIHB_CLK
  
#define CY_SMIF1_RWDS_PORT                      GPIO_PRT26
#define CY_SMIF1_RWDS_PIN                       4
#define CY_SMIF1_RWDS_PIN_MUX                   P26_4_SMIF0_SMIF1_SPIHB_RWDS
  
#define CY_SMIF1_SELECT0_PORT                   GPIO_PRT28
#define CY_SMIF1_SELECT0_PIN                    2
#define CY_SMIF1_SELECT0_PIN_MUX                P28_2_SMIF0_SMIF1_SPIHB_SELECT0
  
#define CY_SMIF1_SELECT1_PORT                   GPIO_PRT28
#define CY_SMIF1_SELECT1_PIN                    5
#define CY_SMIF1_SELECT1_PIN_MUX                P28_5_SMIF0_SMIF1_SPIHB_SELECT1
  
#define CY_SMIF1_DATA0_PORT                     GPIO_PRT28
#define CY_SMIF1_DATA0_PIN                      0
#define CY_SMIF1_DATA0_PIN_MUX                  P28_0_SMIF0_SMIF1_SPIHB_DATA0
  
#define CY_SMIF1_DATA1_PORT                     GPIO_PRT28
#define CY_SMIF1_DATA1_PIN                      3
#define CY_SMIF1_DATA1_PIN_MUX                  P28_3_SMIF0_SMIF1_SPIHB_DATA1
  
#define CY_SMIF1_DATA2_PORT                     GPIO_PRT26
#define CY_SMIF1_DATA2_PIN                      1
#define CY_SMIF1_DATA2_PIN_MUX                  P26_1_SMIF0_SMIF1_SPIHB_DATA2
  
#define CY_SMIF1_DATA3_PORT                     GPIO_PRT26
#define CY_SMIF1_DATA3_PIN                      2
#define CY_SMIF1_DATA3_PIN_MUX                  P26_2_SMIF0_SMIF1_SPIHB_DATA3
  
#define CY_SMIF1_DATA4_PORT                     GPIO_PRT26
#define CY_SMIF1_DATA4_PIN                      0
#define CY_SMIF1_DATA4_PIN_MUX                  P26_0_SMIF0_SMIF1_SPIHB_DATA4
  
#define CY_SMIF1_DATA5_PORT                     GPIO_PRT26
#define CY_SMIF1_DATA5_PIN                      3
#define CY_SMIF1_DATA5_PIN_MUX                  P26_3_SMIF0_SMIF1_SPIHB_DATA5
  
#define CY_SMIF1_DATA6_PORT                     GPIO_PRT28
#define CY_SMIF1_DATA6_PIN                      1
#define CY_SMIF1_DATA6_PIN_MUX                  P28_1_SMIF0_SMIF1_SPIHB_DATA6
  
#define CY_SMIF1_DATA7_PORT                     GPIO_PRT28
#define CY_SMIF1_DATA7_PIN                      4
#define CY_SMIF1_DATA7_PIN_MUX                  P28_4_SMIF0_SMIF1_SPIHB_DATA7
    
#define CY_SMIF_S25FXXXS                        (0u)
#define CY_SMIF_S25FXXXL                        (1u)
#define CY_SMIF1_QUAD_MEMORY                    CY_SMIF_S25FXXXL
  

/******************************************************************************/
/*                      AUDIO-TDM Definitions                                 */
/******************************************************************************/

#define CY_AUDIOSS_TDM_TYPE                     TDM0_TDM_STRUCT2
  
#define CY_AUDIOSS_TDM0_TX_MCK_PORT             GPIO_PRT9
#define CY_AUDIOSS_TDM0_TX_MCK_PIN              0
#define CY_AUDIOSS_TDM0_TX_MCK_PIN_MUX          P9_0_TDM0_TDM_TX_MCK2
  
#define CY_AUDIOSS_TDM0_TX_SCK_PORT             GPIO_PRT9
#define CY_AUDIOSS_TDM0_TX_SCK_PIN              1
#define CY_AUDIOSS_TDM0_TX_SCK_PIN_MUX          P9_1_TDM0_TDM_TX_SCK2
  
#define CY_AUDIOSS_TDM0_TX_FSYNC_PORT           GPIO_PRT9
#define CY_AUDIOSS_TDM0_TX_FSYNC_PIN            2
#define CY_AUDIOSS_TDM0_TX_FSYNC_PIN_MUX        P9_2_TDM0_TDM_TX_FSYNC2
  
#define CY_AUDIOSS_TDM0_TX_SD_PORT              GPIO_PRT9
#define CY_AUDIOSS_TDM0_TX_SD_PIN               3
#define CY_AUDIOSS_TDM0_TX_SD_PIN_MUX           P9_3_TDM0_TDM_TX_SD2
  
#define CY_AUDIOSS_TDM0_RX_MCK_PORT             GPIO_PRT5
#define CY_AUDIOSS_TDM0_RX_MCK_PIN              0
#define CY_AUDIOSS_TDM0_RX_MCK_PIN_MUX          P5_0_TDM0_TDM_RX_MCK2
  
#define CY_AUDIOSS_TDM0_RX_SCK_PORT             GPIO_PRT5
#define CY_AUDIOSS_TDM0_RX_SCK_PIN              1
#define CY_AUDIOSS_TDM0_RX_SCK_PIN_MUX          P5_1_TDM0_TDM_RX_SCK2
  
#define CY_AUDIOSS_TDM0_RX_FSYNC_PORT           GPIO_PRT5
#define CY_AUDIOSS_TDM0_RX_FSYNC_PIN            2
#define CY_AUDIOSS_TDM0_RX_FSYNC_PIN_MUX        P5_2_TDM0_TDM_RX_FSYNC2
  
#define CY_AUDIOSS_TDM0_RX_SD_PORT              GPIO_PRT5
#define CY_AUDIOSS_TDM0_RX_SD_PIN               3
#define CY_AUDIOSS_TDM0_RX_SD_PIN_MUX           P5_3_TDM0_TDM_RX_SD2
  
#define CY_AUDIOSS_TDM0_TX_IRQN                 tdm_0_interrupts_tx_2_IRQn
#define CY_AUDIOSS_TDM0_RX_IRQN                 tdm_0_interrupts_rx_2_IRQn 

/* Audio Codec Communication Block */
#define CY_AUDIOSS_I2C_TYPE                     SCB1
  
#define CY_AUDIOSS_I2C_SDA_PORT                 GPIO_PRT15
#define CY_AUDIOSS_I2C_SDA_PIN                  2
#define CY_AUDIOSS_I2C_SDA_PIN_MUX              P15_2_SCB1_I2C_SDA
  
#define CY_AUDIOSS_I2C_SCL_PORT                 GPIO_PRT15
#define CY_AUDIOSS_I2C_SCL_PIN                  3
#define CY_AUDIOSS_I2C_SCL_PIN_MUX              P15_3_SCB1_I2C_SCL
  
#define CY_AUDIOSS_I2C_PCLK                     PCLK_SCB1_CLOCK
#define CY_AUDIOSS_I2C_IRQN                     scb_1_interrupt_IRQn

/******************************************************************************/
/*                      AUDIOSS PCM-PWM                                       */
/******************************************************************************/

#define CY_AUDIOSS_PWM_TYPE                     PWM0_TX0
  
#define CY_AUDIOSS_PWM0_L1P1_PORT               GPIO_PRT4
#define CY_AUDIOSS_PWM0_L1P1_PIN                0
#define CY_AUDIOSS_PWM0_L1P1_PIN_MUX            P4_0_PWM0_PWM_LINE1_P0
  
#define CY_AUDIOSS_PWM0_L1N1_PORT               GPIO_PRT4
#define CY_AUDIOSS_PWM0_L1N1_PIN                1
#define CY_AUDIOSS_PWM0_L1N1_PIN_MUX            P4_1_PWM0_PWM_LINE1_N0
    
#define CY_AUDIOSS_PWM0_L2P1_PORT               GPIO_PRT4
#define CY_AUDIOSS_PWM0_L2P1_PIN                2
#define CY_AUDIOSS_PWM0_L2P1_PIN_MUX            P4_2_PWM0_PWM_LINE2_P0
    
#define CY_AUDIOSS_PWM0_L2N1_PORT               GPIO_PRT4
#define CY_AUDIOSS_PWM0_L2N1_PIN                3
#define CY_AUDIOSS_PWM0_L2N1_PIN_MUX            P4_3_PWM0_PWM_LINE2_N0
    
#define CY_AUDIOSS_PWM0_IRQN                    pwm_0_interrupts_0_IRQn  

/******************************************************************************/
/*                      AUDIO-SG Definitions                                  */
/******************************************************************************/

// Sound Generator driver circuit is not present on board, so for testing SG fly
// wire can be connected to the external driver circuit.

#define CY_AUDIOSS_SG0_TYPE                      SG0_SG_STRUCT0
  
#define CY_AUDIOSS_SG0_AMPL_PORT                 GPIO_PRT4
#define CY_AUDIOSS_SG0_AMPL_PIN                  0
#define CY_AUDIOSS_SG0_AMPL_PIN_MUX              P4_0_SG0_SG_AMPL0 
  
#define CY_AUDIOSS_SG0_TONE_PORT                 GPIO_PRT4
#define CY_AUDIOSS_SG0_TONE_PIN                  1
#define CY_AUDIOSS_SG0_TONE_PIN_MUX              P4_1_SG0_SG_TONE0 
  
#define CY_AUDIOSS_SG0_IRQ_IRQN                  sg_0_interrupts_0_IRQn

/******************************************************************************/
/*                      AUDIO DAC Definitions                                 */
/******************************************************************************/

// No need to configure AUDIO-DAC io mux, it is available on P3 on board.

/* AUDIO-DAC Clock */
#define CY_AUDIO_DAC_MCK_PORT                   GPIO_PRT2
#define CY_AUDIO_DAC_MCK_PIN                    5
#define CY_AUDIO_DAC_MCK_PIN_MUX                P2_5_DAC0_DAC_MCK

/******************************************************************************/
/*                      GIGA ETH Port                                         */
/******************************************************************************/

#define CY_GIG_ETH_TYPE                         ETH0
#define CY_GIG_ETH_INSTANCE_NUM                 (0)
                                          
#define CY_GIG_ETH_TX_CLK_PORT                  GPIO_PRT13
#define CY_GIG_ETH_TX_CLK_PIN                   4
#define CY_GIG_ETH_TX_CLK_PIN_MUX               P13_4_ETH0_TX_CLK
                                          
#define CY_GIG_ETH_TX_CTL_PORT                  GPIO_PRT14
#define CY_GIG_ETH_TX_CTL_PIN                   0
#define CY_GIG_ETH_TX_CTL_PIN_MUX               P14_0_ETH0_TX_CTL
                                          
#define CY_GIG_ETH_TD0_PORT                     GPIO_PRT13
#define CY_GIG_ETH_TD0_PIN                      2
#define CY_GIG_ETH_TD0_PIN_MUX                  P13_2_ETH0_TXD0
                                          
#define CY_GIG_ETH_TD1_PORT                     GPIO_PRT13
#define CY_GIG_ETH_TD1_PIN                      3
#define CY_GIG_ETH_TD1_PIN_MUX                  P13_3_ETH0_TXD1
                                          
#define CY_GIG_ETH_TD2_PORT                     GPIO_PRT13     
#define CY_GIG_ETH_TD2_PIN                      6
#define CY_GIG_ETH_TD2_PIN_MUX                  P13_6_ETH0_TXD2
                                          
#define CY_GIG_ETH_TD3_PORT                     GPIO_PRT13
#define CY_GIG_ETH_TD3_PIN                      7
#define CY_GIG_ETH_TD3_PIN_MUX                  P13_7_ETH0_TXD3
                                          
#define CY_GIG_ETH_TXER_PORT                    GPIO_PRT14
#define CY_GIG_ETH_TXER_PIN                     1
#define CY_GIG_ETH_TXER_PIN_MUX                 P14_1_ETH0_TX_ER
                                          
#define CY_GIG_ETH_RX_CLK_PORT                  GPIO_PRT14
#define CY_GIG_ETH_RX_CLK_PIN                   2
#define CY_GIG_ETH_RX_CLK_PIN_MUX               P14_2_ETH0_RX_CLK
                                          
#define CY_GIG_ETH_RX_CTL_PORT                  GPIO_PRT14
#define CY_GIG_ETH_RX_CTL_PIN                   7
#define CY_GIG_ETH_RX_CTL_PIN_MUX               P14_7_ETH0_RX_CTL
                                          
#define CY_GIG_ETH_RD0_PORT                     GPIO_PRT14
#define CY_GIG_ETH_RD0_PIN                      3
#define CY_GIG_ETH_RD0_PIN_MUX                  P14_3_ETH0_RXD0
                                          
#define CY_GIG_ETH_RD1_PORT                     GPIO_PRT14
#define CY_GIG_ETH_RD1_PIN                      4
#define CY_GIG_ETH_RD1_PIN_MUX                  P14_4_ETH0_RXD1
                                          
#define CY_GIG_ETH_RD2_PORT                     GPIO_PRT14
#define CY_GIG_ETH_RD2_PIN                      5
#define CY_GIG_ETH_RD2_PIN_MUX                  P14_5_ETH0_RXD2
                                          
#define CY_GIG_ETH_RD3_PORT                     GPIO_PRT14
#define CY_GIG_ETH_RD3_PIN                      6
#define CY_GIG_ETH_RD3_PIN_MUX                  P14_6_ETH0_RXD3
                                          
#define CY_GIG_ETH_RX_ER_PORT                   GPIO_PRT30       
#define CY_GIG_ETH_RX_ER_PIN                    0
#define CY_GIG_ETH_RX_ER_PIN_MUX                P30_0_ETH0_RX_ER
                                          
#define CY_GIG_ETH_MDC_PORT                     GPIO_PRT13
#define CY_GIG_ETH_MDC_PIN                      0
#define CY_GIG_ETH_MDC_PIN_MUX                  P13_0_ETH0_MDC
                                          
#define CY_GIG_ETH_MDIO_PORT                    GPIO_PRT13
#define CY_GIG_ETH_MDIO_PIN                     1
#define CY_GIG_ETH_MDIO_PIN_MUX                 P13_1_ETH0_MDIO
                                          
#define CY_GIG_ETH_REF_CLK_PORT                 GPIO_PRT13
#define CY_GIG_ETH_REF_CLK_PIN                  5
#define CY_GIG_ETH_REF_CLK_PIN_MUX              P13_5_ETH0_REF_CLK
  
/* Setup IRQ source for 0, 1 and 2 Priority Queue */
#define CY_GIG_ETH_IRQN0                        eth_0_interrupt_eth_0_IRQn
#define CY_GIG_ETH_IRQN1                        eth_0_interrupt_eth_1_IRQn
#define CY_GIG_ETH_IRQN2                        eth_0_interrupt_eth_2_IRQn  

/******************************************************************************/
/*                      CANFD Base Board Mux                                  */
/******************************************************************************/

/* CAN1 Channel 0, short J74(2-3) for CAN RX (not a direct connection) */
#define CY_CANFD0_TYPE                          CY_CANFD1_0_TYPE
#define CY_CANFD0_RX_PORT                       GPIO_PRT2
#define CY_CANFD0_RX_PIN                        4
#define CY_CANFD0_RX_MUX                        P2_4_CANFD1_TTCAN_RX0
#define CY_CANFD0_TX_PORT                       GPIO_PRT2
#define CY_CANFD0_TX_PIN                        3
#define CY_CANFD0_TX_MUX                        P2_3_CANFD1_TTCAN_TX0
#define CY_CANFD0_PCLK                          PCLK_CANFD1_CLOCK_CAN0
#define CY_CANFD0_IRQN                          canfd_1_interrupts0_0_IRQn
  
/* CAN1 Channel 1 */    
#define CY_CANFD1_TYPE                          CY_CANFD1_1_TYPE
#define CY_CANFD1_RX_PORT                       GPIO_PRT5
#define CY_CANFD1_RX_PIN                        5
#define CY_CANFD1_RX_MUX                        P5_5_CANFD1_TTCAN_RX1
#define CY_CANFD1_TX_PORT                       GPIO_PRT5
#define CY_CANFD1_TX_PIN                        4
#define CY_CANFD1_TX_MUX                        P5_4_CANFD1_TTCAN_TX1
#define CY_CANFD1_PCLK                          PCLK_CANFD1_CLOCK_CAN1
#define CY_CANFD1_IRQN                          canfd_1_interrupts0_1_IRQn  

/******************************************************************************/
/*                      LIN Base Board Mux                                    */
/******************************************************************************/

/* LIN0 Channel 1, short J75(2-3) for LIN_EN (not a direct connection) */
#define CY_LINCH1_TYPE                          LIN0_CH1
#define CY_LINCH1_RX_PORT                       GPIO_PRT0
#define CY_LINCH1_RX_PIN                        1
#define CY_LINCH1_RX_PIN_MUX                    P0_1_LIN0_LIN_RX1
#define CY_LINCH1_TX_PORT                       GPIO_PRT0
#define CY_LINCH1_TX_PIN                        0
#define CY_LINCH1_TX_PIN_MUX                    P0_0_LIN0_LIN_TX1
#define CY_LINCH1_PCLK                          PCLK_LIN0_CLOCK_CH_EN1
#define CY_LINCH1_IRQN                          lin_0_interrupts_1_IRQn

/******************************************************************************/
/*                      CXPI Definitions                                      */
/******************************************************************************/

#define CY_CXPI0_TYPE                           CXPI0_CH1
  
// Short J88/1-2
#define CY_CXPI0_RX_PORT                        GPIO_PRT0
#define CY_CXPI0_RX_PIN                         3
#define CY_CXPI0_RX_PIN_MUX                     P0_3_CXPI0_CXPI_RX1
    
// Short J84/1-2
#define CY_CXPI0_TX_PORT                        GPIO_PRT0
#define CY_CXPI0_TX_PIN                         2
#define CY_CXPI0_TX_PIN_MUX                     P0_2_CXPI0_CXPI_TX1
    
// Short J75/1-2
#define CY_CXPI0_EN_PORT                        GPIO_PRT3
#define CY_CXPI0_EN_PIN                         4
#define CY_CXPI0_EN_PIN_MUX                     P3_4_CXPI0_CXPI_EN1

#define CY_CXPI0_CLK_PORT                       GPIO_PRT29
#define CY_CXPI0_CLK_PIN                        0
#define CY_CXPI0_CLK_PIN_MUX                    P29_0_TCPWM0_LINE28
#define CY_CXPI0_CLK_TCPWM_CNT                  TCPWM0_GRP0_CNT28
#define CY_CXPI0_CLK_TCPWM_PCLK                 PCLK_TCPWM0_CLOCKS28
  
#define CY_CXPI0_SEL_PORT                       GPIO_PRT7
#define CY_CXPI0_SEL_PIN                        7
#define CY_CXPI0_SEL_PIN_MUX                    P7_7_GPIO

#define CY_CXPI0_PCLK                           PCLK_CXPI0_CLOCK_CH_EN1
#define CY_CXPI0_IRQN                           cxpi_0_interrupts_1_IRQn 


/******************************************************************************/
/*                      SMARTIO Block                                         */
/******************************************************************************/

#define CY_SMARTIO_MACRO                        SMARTIO
#define CY_SMARTIO_PORT                         SMARTIO_PRT7
#define CY_SMARTIO_CLK                          PCLK_SMARTIO7_CLOCK
  
#define CY_SMARTIO_OUT_PORT                     GPIO_PRT7 			// P13/11
#define CY_SMARTIO_OUT_PIN                      2
#define CY_SMARTIO_OUT_PORT_MUX                 P7_2_GPIO
  
#define CY_SMARTIO_IN_PORT                      GPIO_PRT7 			// J55/15
#define CY_SMARTIO_IN_PIN                       1
#define CY_SMARTIO_IN_PORT_MUX                  P7_1_GPIO
#define CY_SMARTIO_IN_PORT_MUX_PWM              P7_1_TCPWM0_LINE21

#define CY_SMARTIO_IN2_PORT                     GPIO_PRT7 			// P13/9
#define CY_SMARTIO_IN2_PIN                      3
#define CY_SMARTIO_IN2_PORT_MUX                 P7_3_GPIO
#define CY_SMARTIO_IN2_PORT_MUX_PWM             P7_3_TCPWM0_LINE23

/* PWM PR Mode Configuration def */
#define CY_SMARTIO_TCPWM_GRP0_CNT               TCPWM0_GRP0_CNT21
#define CY_SMARTIO_TCPWM_PCLK                   PCLK_TCPWM0_CLOCKS21

#define CY_SMARTIO_TCPWM_GRP0_CNT2              TCPWM0_GRP0_CNT23
#define CY_SMARTIO_TCPWM_PCLK2                  PCLK_TCPWM0_CLOCKS23

/******************************************************************************/
/*                      Display Backlight Controls                            */
/******************************************************************************/

/* Display 1 Backlight, available on P13/3 */       
#define CY_BL_DISP1_PWM_PORT                    GPIO_PRT7
#define CY_BL_DISP1_PWM_PIN                     5
#define CY_BL_DISP1_PWM_PIN_MUX                 P7_5_GPIO  // use as GPIO for now (0% or 100% PWM)
  
/******************************************************************************/
/*                      Display #1 Definitions                                */
/******************************************************************************/
  
// Display 1 is multiplexed with Capture 0, one of them can be used at a time.

#define CY_BSP_HDR_DISP1_TTL_AVAILABLE          // Definitions for this functionality are available

#define CY_DISP1_CLK_PORT                       GPIO_PRT21
#define CY_DISP1_CLK_PIN                        1
#define CY_DISP1_CLK_PIN_MUX                    P21_1_VIDEOSS0_TTL_DSP1_CLOCK    // PCLK
    
#define CY_DISP1_CTRL0_PORT                     GPIO_PRT20
#define CY_DISP1_CTRL0_PIN                      6 
#define CY_DISP1_CTRL0_PIN_MUX                  P20_6_VIDEOSS0_TTL_DSP1_CONTROL0 // LVALID
    
#define CY_DISP1_CTRL1_PORT                     GPIO_PRT20
#define CY_DISP1_CTRL1_PIN                      7
#define CY_DISP1_CTRL1_PIN_MUX                  P20_7_VIDEOSS0_TTL_DSP1_CONTROL1 // VSYNC
    
#define CY_DISP1_CTRL2_PORT                     GPIO_PRT21
#define CY_DISP1_CTRL2_PIN                      0
#define CY_DISP1_CTRL2_PIN_MUX                  P21_0_VIDEOSS0_TTL_DSP1_CONTROL2 // DE
    
#define CY_DISP1_DATA_A0_0_PORT                 GPIO_PRT16
#define CY_DISP1_DATA_A0_0_PIN                  7
#define CY_DISP1_DATA_A0_0_PIN_MUX              P16_7_VIDEOSS0_TTL_DSP1_DATA_A00 // RED0
    
#define CY_DISP1_DATA_A0_1_PORT                 GPIO_PRT18
#define CY_DISP1_DATA_A0_1_PIN                  0
#define CY_DISP1_DATA_A0_1_PIN_MUX              P18_0_VIDEOSS0_TTL_DSP1_DATA_A01 // RED2
    
#define CY_DISP1_DATA_A0_2_PORT                 GPIO_PRT18
#define CY_DISP1_DATA_A0_2_PIN                  2
#define CY_DISP1_DATA_A0_2_PIN_MUX              P18_2_VIDEOSS0_TTL_DSP1_DATA_A02 // RED4
    
#define CY_DISP1_DATA_A0_3_PORT                 GPIO_PRT18
#define CY_DISP1_DATA_A0_3_PIN                  4
#define CY_DISP1_DATA_A0_3_PIN_MUX              P18_4_VIDEOSS0_TTL_DSP1_DATA_A03 // RED6
    
#define CY_DISP1_DATA_A0_4_PORT                 GPIO_PRT18
#define CY_DISP1_DATA_A0_4_PIN                  6
#define CY_DISP1_DATA_A0_4_PIN_MUX              P18_6_VIDEOSS0_TTL_DSP1_DATA_A04 // GREEN0
    
#define CY_DISP1_DATA_A0_5_PORT                 GPIO_PRT19
#define CY_DISP1_DATA_A0_5_PIN                  0
#define CY_DISP1_DATA_A0_5_PIN_MUX              P19_0_VIDEOSS0_TTL_DSP1_DATA_A05 // GREEN2
    
#define CY_DISP1_DATA_A0_6_PORT                 GPIO_PRT19
#define CY_DISP1_DATA_A0_6_PIN                  2
#define CY_DISP1_DATA_A0_6_PIN_MUX              P19_2_VIDEOSS0_TTL_DSP1_DATA_A06 // GREEN4
    
#define CY_DISP1_DATA_A0_7_PORT                 GPIO_PRT19
#define CY_DISP1_DATA_A0_7_PIN                  4
#define CY_DISP1_DATA_A0_7_PIN_MUX              P19_4_VIDEOSS0_TTL_DSP1_DATA_A07 // GREEN6
    
#define CY_DISP1_DATA_A0_8_PORT                 GPIO_PRT19
#define CY_DISP1_DATA_A0_8_PIN                  6
#define CY_DISP1_DATA_A0_8_PIN_MUX              P19_6_VIDEOSS0_TTL_DSP1_DATA_A08 // BLUE0
    
#define CY_DISP1_DATA_A0_9_PORT                 GPIO_PRT20
#define CY_DISP1_DATA_A0_9_PIN                  0
#define CY_DISP1_DATA_A0_9_PIN_MUX              P20_0_VIDEOSS0_TTL_DSP1_DATA_A09 // BLUE2
    
#define CY_DISP1_DATA_A0_10_PORT                GPIO_PRT20
#define CY_DISP1_DATA_A0_10_PIN                 2
#define CY_DISP1_DATA_A0_10_PIN_MUX             P20_2_VIDEOSS0_TTL_DSP1_DATA_A010// BLUE4
    
#define CY_DISP1_DATA_A0_11_PORT                GPIO_PRT20
#define CY_DISP1_DATA_A0_11_PIN                 4
#define CY_DISP1_DATA_A0_11_PIN_MUX             P20_4_VIDEOSS0_TTL_DSP1_DATA_A011// BLUE6
    
#define CY_DISP1_DATA_A1_0_PORT                 GPIO_PRT17
#define CY_DISP1_DATA_A1_0_PIN                  0
#define CY_DISP1_DATA_A1_0_PIN_MUX              P17_0_VIDEOSS0_TTL_DSP1_DATA_A10 // RED1
    
#define CY_DISP1_DATA_A1_1_PORT                 GPIO_PRT18
#define CY_DISP1_DATA_A1_1_PIN                  1
#define CY_DISP1_DATA_A1_1_PIN_MUX              P18_1_VIDEOSS0_TTL_DSP1_DATA_A11 // RED3
    
#define CY_DISP1_DATA_A1_2_PORT                 GPIO_PRT18
#define CY_DISP1_DATA_A1_2_PIN                  3
#define CY_DISP1_DATA_A1_2_PIN_MUX              P18_3_VIDEOSS0_TTL_DSP1_DATA_A12 // RED5
    
#define CY_DISP1_DATA_A1_3_PORT                 GPIO_PRT18
#define CY_DISP1_DATA_A1_3_PIN                  5
#define CY_DISP1_DATA_A1_3_PIN_MUX              P18_5_VIDEOSS0_TTL_DSP1_DATA_A13 // RED7
    
#define CY_DISP1_DATA_A1_4_PORT                 GPIO_PRT18
#define CY_DISP1_DATA_A1_4_PIN                  7
#define CY_DISP1_DATA_A1_4_PIN_MUX              P18_7_VIDEOSS0_TTL_DSP1_DATA_A14 // GREEN1
    
#define CY_DISP1_DATA_A1_5_PORT                 GPIO_PRT19
#define CY_DISP1_DATA_A1_5_PIN                  1
#define CY_DISP1_DATA_A1_5_PIN_MUX              P19_1_VIDEOSS0_TTL_DSP1_DATA_A15 // GREEN3
    
#define CY_DISP1_DATA_A1_6_PORT                 GPIO_PRT19
#define CY_DISP1_DATA_A1_6_PIN                  3
#define CY_DISP1_DATA_A1_6_PIN_MUX              P19_3_VIDEOSS0_TTL_DSP1_DATA_A16 // GREEN5
    
#define CY_DISP1_DATA_A1_7_PORT                 GPIO_PRT19
#define CY_DISP1_DATA_A1_7_PIN                  5
#define CY_DISP1_DATA_A1_7_PIN_MUX              P19_5_VIDEOSS0_TTL_DSP1_DATA_A17 // GREEN7
    
#define CY_DISP1_DATA_A1_8_PORT                 GPIO_PRT19
#define CY_DISP1_DATA_A1_8_PIN                  7
#define CY_DISP1_DATA_A1_8_PIN_MUX              P19_7_VIDEOSS0_TTL_DSP1_DATA_A18 // BLUE1
    
#define CY_DISP1_DATA_A1_9_PORT                 GPIO_PRT20
#define CY_DISP1_DATA_A1_9_PIN                  1
#define CY_DISP1_DATA_A1_9_PIN_MUX              P20_1_VIDEOSS0_TTL_DSP1_DATA_A19 // BLUE3
    
#define CY_DISP1_DATA_A1_10_PORT                GPIO_PRT20
#define CY_DISP1_DATA_A1_10_PIN                 3
#define CY_DISP1_DATA_A1_10_PIN_MUX             P20_3_VIDEOSS0_TTL_DSP1_DATA_A110// BLUE5
    
#define CY_DISP1_DATA_A1_11_PORT                GPIO_PRT20
#define CY_DISP1_DATA_A1_11_PIN                 5
#define CY_DISP1_DATA_A1_11_PIN_MUX             P20_5_VIDEOSS0_TTL_DSP1_DATA_A111// BLUE7
  
// IO connections P16.0, P16.1, P16.2 and P16.3 kept for FX3 adapter control signals.

  
/******************************************************************************/
/*                      Capture #0 Definitions                                */
/******************************************************************************/

// Capture 0 is multiplexed with Display 1, one of them can be used at a time.

#define CY_BSP_HDR_CAP0_TTL_AVAILABLE           // Definitions for this functionality are available
  
#define CY_CAP0_CLK_PORT                        GPIO_PRT15
#define CY_CAP0_CLK_PIN                         6
#define CY_CAP0_CLK_PIN_MUX                     P15_6_VIDEOSS0_TTL_CAP0_CLK      // CLK
                                          
#define CY_CAP0_DATA0_PORT                      GPIO_PRT15
#define CY_CAP0_DATA0_PIN                       7
#define CY_CAP0_DATA0_PIN_MUX                   P15_7_VIDEOSS0_TTL_CAP0_DATA0    // BLUE0
                                          
#define CY_CAP0_DATA1_PORT                      GPIO_PRT16
#define CY_CAP0_DATA1_PIN                       0
#define CY_CAP0_DATA1_PIN_MUX                   P16_0_VIDEOSS0_TTL_CAP0_DATA1    // BLUE1
                                          
#define CY_CAP0_DATA2_PORT                      GPIO_PRT16
#define CY_CAP0_DATA2_PIN                       1
#define CY_CAP0_DATA2_PIN_MUX                   P16_1_VIDEOSS0_TTL_CAP0_DATA2    // BLUE2
                                          
#define CY_CAP0_DATA3_PORT                      GPIO_PRT16
#define CY_CAP0_DATA3_PIN                       2
#define CY_CAP0_DATA3_PIN_MUX                   P16_2_VIDEOSS0_TTL_CAP0_DATA3    // BLUE3
                                          
#define CY_CAP0_DATA4_PORT                      GPIO_PRT16
#define CY_CAP0_DATA4_PIN                       3
#define CY_CAP0_DATA4_PIN_MUX                   P16_3_VIDEOSS0_TTL_CAP0_DATA4    // BLUE4
                                          
#define CY_CAP0_DATA5_PORT                      GPIO_PRT16
#define CY_CAP0_DATA5_PIN                       4
#define CY_CAP0_DATA5_PIN_MUX                   P16_4_VIDEOSS0_TTL_CAP0_DATA5    // BLUE5
                                          
#define CY_CAP0_DATA6_PORT                      GPIO_PRT16
#define CY_CAP0_DATA6_PIN                       5
#define CY_CAP0_DATA6_PIN_MUX                   P16_5_VIDEOSS0_TTL_CAP0_DATA6    // BLUE6
                                          
#define CY_CAP0_DATA7_PORT                      GPIO_PRT16
#define CY_CAP0_DATA7_PIN                       6
#define CY_CAP0_DATA7_PIN_MUX                   P16_6_VIDEOSS0_TTL_CAP0_DATA7    // BLUE7
                                          
#define CY_CAP0_DATA8_PORT                      GPIO_PRT16
#define CY_CAP0_DATA8_PIN                       7
#define CY_CAP0_DATA8_PIN_MUX                   P16_7_VIDEOSS0_TTL_CAP0_DATA8    // GREEN0
                                          
#define CY_CAP0_DATA9_PORT                      GPIO_PRT17
#define CY_CAP0_DATA9_PIN                       0
#define CY_CAP0_DATA9_PIN_MUX                   P17_0_VIDEOSS0_TTL_CAP0_DATA9    // GREEN1
                                          
#define CY_CAP0_DATA10_PORT                     GPIO_PRT18
#define CY_CAP0_DATA10_PIN                      0
#define CY_CAP0_DATA10_PIN_MUX                  P18_0_VIDEOSS0_TTL_CAP0_DATA10   // GREEN2
                                          
#define CY_CAP0_DATA11_PORT                     GPIO_PRT18
#define CY_CAP0_DATA11_PIN                      1
#define CY_CAP0_DATA11_PIN_MUX                  P18_1_VIDEOSS0_TTL_CAP0_DATA11   // GREEN3
                                          
#define CY_CAP0_DATA12_PORT                     GPIO_PRT18
#define CY_CAP0_DATA12_PIN                      2
#define CY_CAP0_DATA12_PIN_MUX                  P18_2_VIDEOSS0_TTL_CAP0_DATA12   // GREEN4
                                          
#define CY_CAP0_DATA13_PORT                     GPIO_PRT18
#define CY_CAP0_DATA13_PIN                      3
#define CY_CAP0_DATA13_PIN_MUX                  P18_3_VIDEOSS0_TTL_CAP0_DATA13   // GREEN5
                                          
#define CY_CAP0_DATA14_PORT                     GPIO_PRT18
#define CY_CAP0_DATA14_PIN                      4
#define CY_CAP0_DATA14_PIN_MUX                  P18_4_VIDEOSS0_TTL_CAP0_DATA14   // GREEN6
                                          
#define CY_CAP0_DATA15_PORT                     GPIO_PRT18
#define CY_CAP0_DATA15_PIN                      5
#define CY_CAP0_DATA15_PIN_MUX                  P18_5_VIDEOSS0_TTL_CAP0_DATA15   // GREEN7
                                          
#define CY_CAP0_DATA16_PORT                     GPIO_PRT18
#define CY_CAP0_DATA16_PIN                      6
#define CY_CAP0_DATA16_PIN_MUX                  P18_6_VIDEOSS0_TTL_CAP0_DATA16   // RED0
                                          
#define CY_CAP0_DATA17_PORT                     GPIO_PRT18
#define CY_CAP0_DATA17_PIN                      7
#define CY_CAP0_DATA17_PIN_MUX                  P18_7_VIDEOSS0_TTL_CAP0_DATA17   // RED1
                                          
#define CY_CAP0_DATA18_PORT                     GPIO_PRT19
#define CY_CAP0_DATA18_PIN                      0
#define CY_CAP0_DATA18_PIN_MUX                  P19_0_VIDEOSS0_TTL_CAP0_DATA18   // RED2
                                          
#define CY_CAP0_DATA19_PORT                     GPIO_PRT19
#define CY_CAP0_DATA19_PIN                      1
#define CY_CAP0_DATA19_PIN_MUX                  P19_1_VIDEOSS0_TTL_CAP0_DATA19   // RED3
                                          
#define CY_CAP0_DATA20_PORT                     GPIO_PRT19
#define CY_CAP0_DATA20_PIN                      2
#define CY_CAP0_DATA20_PIN_MUX                  P19_2_VIDEOSS0_TTL_CAP0_DATA20   // RED4
                                          
#define CY_CAP0_DATA21_PORT                     GPIO_PRT19
#define CY_CAP0_DATA21_PIN                      3
#define CY_CAP0_DATA21_PIN_MUX                  P19_3_VIDEOSS0_TTL_CAP0_DATA21   // RED5
                                          
#define CY_CAP0_DATA22_PORT                     GPIO_PRT19
#define CY_CAP0_DATA22_PIN                      4
#define CY_CAP0_DATA22_PIN_MUX                  P19_4_VIDEOSS0_TTL_CAP0_DATA22   // RED6
                                          
#define CY_CAP0_DATA23_PORT                     GPIO_PRT19
#define CY_CAP0_DATA23_PIN                      5
#define CY_CAP0_DATA23_PIN_MUX                  P19_5_VIDEOSS0_TTL_CAP0_DATA23   // RED7
                                          
#define CY_CAP0_DATA24_PORT                     GPIO_PRT19
#define CY_CAP0_DATA24_PIN                      6
#define CY_CAP0_DATA24_PIN_MUX                  P19_6_VIDEOSS0_TTL_CAP0_DATA24   // HSYNC
                                          
#define CY_CAP0_DATA25_PORT                     GPIO_PRT19
#define CY_CAP0_DATA25_PIN                      7
#define CY_CAP0_DATA25_PIN_MUX                  P19_7_VIDEOSS0_TTL_CAP0_DATA25   // VSYNC
                                          
#define CY_CAP0_DATA26_PORT                     GPIO_PRT20
#define CY_CAP0_DATA26_PIN                      0
#define CY_CAP0_DATA26_PIN_MUX                  P20_0_VIDEOSS0_TTL_CAP0_DATA26   // DE
  

/******************************************************************************/
/*                      FPD-LINK Definitions                                  */
/******************************************************************************/

// No need to configure FPDLINK io mux, it is a part of AMUXBUS.

/* FPDLINK 0 Enable (TP175), default J3/2-3 to 3.3V */
#define CY_FPDLINK0_BL_EN_PORT                  GPIO_PRT8
#define CY_FPDLINK0_BL_EN_PIN                   0
#define CY_FPDLINK0_BL_EN_PIN_MUX               P8_0_GPIO

/* FPDLINK 0 PWM (TP176), default J4/2-3 to 3.3V */
#define CY_FPDLINK0_BL_PWM_PORT                 GPIO_PRT8
#define CY_FPDLINK0_BL_PWM_PIN                  2
#define CY_FPDLINK0_BL_PWM_PIN_MUX              P8_2_GPIO
  
/* FPDLINK 1 Enable (TP177), default J6/2-3 to 3.3V */
#define CY_FPDLINK1_BL_EN_PORT                  GPIO_PRT8
#define CY_FPDLINK1_BL_EN_PIN                   1
#define CY_FPDLINK1_BL_EN_PIN_MUX               P8_1_GPIO
  
/* FPDLINK 1 PWM (TP178), default J5/2-3 to 3.3V */
#define CY_FPDLINK1_BL_PWM_PORT                 GPIO_PRT8
#define CY_FPDLINK1_BL_PWM_PIN                  3
#define CY_FPDLINK1_BL_PWM_PIN_MUX              P8_3_GPIO  
  
/******************************************************************************/
/*                      MIPI CSI-2 Definitions                                */
/******************************************************************************/

// No need to configure MIPI CSI io mux, it is a part of AMUXBUS.

/* MIPI IO Clock */
#define CY_MIPI_CSI_IO_CLK_PORT                 GPIO_PRT15
#define CY_MIPI_CSI_IO_CLK_PIN                  4
#define CY_MIPI_CSI_IO_CLK_PIN_MUX              P15_4_GPIO

/* MIPI Power Enable */
#define CY_MIPI_CSI_PWDN_PORT                   GPIO_PRT15
#define CY_MIPI_CSI_PWDN_PIN                    5
#define CY_MIPI_CSI_PWDN_PIN_MUX                P15_5_GPIO
  
/* MIPI CSI Communication Block */
#define CY_MIPI_CSI_I2C_TYPE                    SCB0
  
// Short J84/2-3
#define CY_MIPI_CSI_I2C_SDA_PORT                GPIO_PRT0
#define CY_MIPI_CSI_I2C_SDA_PIN                 2
#define CY_MIPI_CSI_I2C_SDA_PIN_MUX             P0_2_SCB0_I2C_SDA
  
// Short J88/2-3
#define CY_MIPI_CSI_I2C_SCL_PORT                GPIO_PRT0
#define CY_MIPI_CSI_I2C_SCL_PIN                 3
#define CY_MIPI_CSI_I2C_SCL_PIN_MUX             P0_3_SCB0_I2C_SCL
  
#define CY_MIPI_CSI_I2C_PCLK                    PCLK_SCB0_CLOCK
#define CY_MIPI_CSI_I2C_IRQN                    scb_0_interrupt_IRQn
  
/******************************************************************************/
/*                              EXT CLK PORT                                  */
/******************************************************************************/
#define CY_HF3_CLK_OUT_PORT                         GPIO_PRT3
#define CY_HF3_CLK_OUT_PIN                          3
#define CY_HF3_CLK_OUT_PIN_MUX                      P3_3_SRSS_EXT_CLK

/******************************************************************************/
/******************************************************************************/

#else // No Device Selected

    #error "Choose correct device from the device specific Datasheet."

#endif 


#ifdef __cplusplus
}
#endif

#endif /* BB_BSP_TVIIC2D6M_327BGA_DEVICE_REVC_EVK_REVB_H */

/* [] END OF FILE */
