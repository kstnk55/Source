/***************************************************************************//**
* \file bsp_tviic2d6m_327bga_device_revc_evklite_reva.h
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

#ifndef BB_BSP_TVIIC2D6M_327BGA_DEVICE_REVC_EVKLITE_REVA_H
#define BB_BSP_TVIIC2D6M_327BGA_DEVICE_REVC_EVKLITE_REVA_H

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

#define CY_USER_LED1_PORT                       GPIO_PRT7 		// User LED1
#define CY_USER_LED1_PIN                        5
#define CY_USER_LED1_PIN_MUX                    P7_5_GPIO
    
#define CY_USER_LED2_PORT                       GPIO_PRT7 		// User LED2
#define CY_USER_LED2_PIN                        6
#define CY_USER_LED2_PIN_MUX                    P7_6_GPIO
    
#define CY_USER_LED3_PORT                       GPIO_PRT7 		// User LED3
#define CY_USER_LED3_PIN                        7
#define CY_USER_LED3_PIN_MUX                    P7_7_GPIO


/******************************************************************************/
/*                      USER BUTTON's                                         */
/******************************************************************************/
    
#define CY_USER_BUTTON_UP_PORT                  GPIO_PRT0 		// User Button 1
#define CY_USER_BUTTON_UP_PIN                   2
#define CY_USER_BUTTON_UP_PIN_MUX               P0_2_GPIO
  
#define CY_USER_BUTTON_WAKE_PORT                GPIO_PRT0 		// User Button 2
#define CY_USER_BUTTON_WAKE_PIN                 3
#define CY_USER_BUTTON_WAKE_PIN_MUX             P0_3_GPIO
#define CY_USER_BUTTON_WAKE_SOURCE              CY_SYSPM_WAKEUP_PIN5    // HIBERNATE_WAKEUP[0]
    
/* Setup GPIO for BUTTONs interrupt sources */
#define CY_USER_BUTTON_UP_IRQN                  ioss_interrupts_gpio_dpslp_0_IRQn
#define CY_USER_BUTTON_WAKE_IRQN                ioss_interrupts_gpio_dpslp_0_IRQn


/******************************************************************************/
/*                      ADC POT                                               */
/******************************************************************************/

#define CY_ADC_POT_PORT                         GPIO_PRT7
#define CY_ADC_POT_PIN                          4
#define CY_ADC_POT_PIN_MUX                      P7_4_GPIO
  
#define CY_ADC_POT_MACRO                        PASS0_SAR0
#define CY_ADC_POT_IN_NO                        14
#define CY_ADC_POT_PCLK                         PCLK_PASS0_CLOCK_SAR0
#define CY_ADC_POT_IRQN                         pass_0_interrupts_sar_0_IRQn    // sar logical channel irq

/******************************************************************************/
/*                      SCB Mux                                               */
/******************************************************************************/
/* USB-UART Mux */
#define CY_USB_SCB_UART_TYPE                    SCB7
  
#define CY_USB_SCB_UART_RX_PORT                 GPIO_PRT9
#define CY_USB_SCB_UART_RX_PIN                  0
#define CY_USB_SCB_UART_RX_PIN_MUX              P9_0_SCB7_UART_RX

#define CY_USB_SCB_UART_TX_PORT                 GPIO_PRT9
#define CY_USB_SCB_UART_TX_PIN                  1
#define CY_USB_SCB_UART_TX_PIN_MUX              P9_1_SCB7_UART_TX

#define CY_USB_SCB_UART_PCLK                    PCLK_SCB7_CLOCK
#define CY_USB_SCB_UART_IRQN                    scb_7_interrupt_IRQn


/******************************************************************************/
/*                      SMIF0 Definitions                                     */
/******************************************************************************/
#define CY_BSP_HDR_SMIF0_AVAILABLE              // Definitions for this functionality are available

#define CY_SMIF0_RST_PORT                       GPIO_PRT12
#define CY_SMIF0_RST_PIN                        5
#define CY_SMIF0_RST_PIN_MUX                    P12_5_GPIO

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

#define CY_SMIF1_RST_PORT                       GPIO_PRT12
#define CY_SMIF1_RST_PIN                        7
#define CY_SMIF1_RST_PIN_MUX                    P12_7_GPIO

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

#define CY_AUDIOSS_TDM_TYPE                     TDM0_TDM_STRUCT0
  
#define CY_AUDIOSS_TDM0_TX_MCK_PORT             GPIO_PRT15
#define CY_AUDIOSS_TDM0_TX_MCK_PIN              6
#define CY_AUDIOSS_TDM0_TX_MCK_PIN_MUX          P15_6_TDM0_TDM_TX_MCK0
  
#define CY_AUDIOSS_TDM0_TX_SCK_PORT             GPIO_PRT15
#define CY_AUDIOSS_TDM0_TX_SCK_PIN              7
#define CY_AUDIOSS_TDM0_TX_SCK_PIN_MUX          P15_7_TDM0_TDM_TX_SCK0
  
#define CY_AUDIOSS_TDM0_TX_FSYNC_PORT           GPIO_PRT16
#define CY_AUDIOSS_TDM0_TX_FSYNC_PIN            0
#define CY_AUDIOSS_TDM0_TX_FSYNC_PIN_MUX        P16_0_TDM0_TDM_TX_FSYNC0
  
#define CY_AUDIOSS_TDM0_TX_SD_PORT              GPIO_PRT16
#define CY_AUDIOSS_TDM0_TX_SD_PIN               1
#define CY_AUDIOSS_TDM0_TX_SD_PIN_MUX           P16_1_TDM0_TDM_TX_SD0
  
#define CY_AUDIOSS_TDM0_RX_MCK_PORT             GPIO_PRT16
#define CY_AUDIOSS_TDM0_RX_MCK_PIN              2
#define CY_AUDIOSS_TDM0_RX_MCK_PIN_MUX          P16_2_TDM0_TDM_RX_MCK0
  
#define CY_AUDIOSS_TDM0_RX_SCK_PORT             GPIO_PRT16
#define CY_AUDIOSS_TDM0_RX_SCK_PIN              3
#define CY_AUDIOSS_TDM0_RX_SCK_PIN_MUX          P16_3_TDM0_TDM_RX_SCK0
  
#define CY_AUDIOSS_TDM0_RX_FSYNC_PORT           GPIO_PRT16
#define CY_AUDIOSS_TDM0_RX_FSYNC_PIN            4
#define CY_AUDIOSS_TDM0_RX_FSYNC_PIN_MUX        P16_4_TDM0_TDM_RX_FSYNC0
  
#define CY_AUDIOSS_TDM0_RX_SD_PORT              GPIO_PRT16
#define CY_AUDIOSS_TDM0_RX_SD_PIN               5
#define CY_AUDIOSS_TDM0_RX_SD_PIN_MUX           P16_5_TDM0_TDM_RX_SD0
  
#define CY_AUDIOSS_TDM0_TX_IRQN                 tdm_0_interrupts_tx_0_IRQn
#define CY_AUDIOSS_TDM0_RX_IRQN                 tdm_0_interrupts_rx_0_IRQn 

/* Audio Codec Communication Block */
#define CY_AUDIOSS_I2C_TYPE                     SCB11
  
#define CY_AUDIOSS_I2C_SDA_PORT                 GPIO_PRT0
#define CY_AUDIOSS_I2C_SDA_PIN                  4
#define CY_AUDIOSS_I2C_SDA_PIN_MUX              P0_4_SCB11_I2C_SDA
  
#define CY_AUDIOSS_I2C_SCL_PORT                 GPIO_PRT0
#define CY_AUDIOSS_I2C_SCL_PIN                  5
#define CY_AUDIOSS_I2C_SCL_PIN_MUX              P0_5_SCB11_I2C_SCL
  
#define CY_AUDIOSS_I2C_PCLK                     PCLK_SCB11_CLOCK
#define CY_AUDIOSS_I2C_IRQN                     scb_11_interrupt_IRQn

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

/* CAN0 Channel 0 */
#define CY_CANFD0_TYPE                          CY_CANFD0_0_TYPE
#define CY_CANFD0_RX_PORT                       GPIO_PRT5
#define CY_CANFD0_RX_PIN                        1
#define CY_CANFD0_RX_MUX                        P5_1_CANFD0_TTCAN_RX0
#define CY_CANFD0_TX_PORT                       GPIO_PRT5
#define CY_CANFD0_TX_PIN                        0
#define CY_CANFD0_TX_MUX                        P5_0_CANFD0_TTCAN_TX0
#define CY_CANFD0_PCLK                          PCLK_CANFD0_CLOCK_CAN0
#define CY_CANFD0_IRQN                          canfd_0_interrupts0_0_IRQn
  
/* CAN0 Channel 1 */    
#define CY_CANFD1_TYPE                          CY_CANFD0_1_TYPE
#define CY_CANFD1_RX_PORT                       GPIO_PRT5
#define CY_CANFD1_RX_PIN                        3
#define CY_CANFD1_RX_MUX                        P5_3_CANFD0_TTCAN_RX1
#define CY_CANFD1_TX_PORT                       GPIO_PRT5
#define CY_CANFD1_TX_PIN                        2
#define CY_CANFD1_TX_MUX                        P5_2_CANFD0_TTCAN_TX1
#define CY_CANFD1_PCLK                          PCLK_CANFD0_CLOCK_CAN1
#define CY_CANFD1_IRQN                          canfd_0_interrupts0_1_IRQn  

/******************************************************************************/
/*                      LIN Base Board Mux                                    */
/******************************************************************************/

/* LIN0 Channel 0 */
#define CY_LINCH1_TYPE                          LIN0_CH0
#define CY_LINCH1_RX_PORT                       GPIO_PRT4
#define CY_LINCH1_RX_PIN                        5
#define CY_LINCH1_RX_PIN_MUX                    P4_5_LIN0_LIN_RX0
#define CY_LINCH1_TX_PORT                       GPIO_PRT4
#define CY_LINCH1_TX_PIN                        6
#define CY_LINCH1_TX_PIN_MUX                    P4_6_LIN0_LIN_TX0
#define CY_LINCH1_PCLK                          PCLK_LIN0_CLOCK_CH_EN0
#define CY_LINCH1_IRQN                          lin_0_interrupts_0_IRQn


/******************************************************************************/
/*                      SMARTIO Block                                         */
/******************************************************************************/

#define CY_SMARTIO_MACRO                        SMARTIO
#define CY_SMARTIO_PORT                         SMARTIO_PRT7
#define CY_SMARTIO_CLK                          PCLK_SMARTIO7_CLOCK
  
#define CY_SMARTIO_OUT_PORT                     GPIO_PRT7
#define CY_SMARTIO_OUT_PIN                      2
#define CY_SMARTIO_OUT_PORT_MUX                 P7_2_GPIO
  
#define CY_SMARTIO_IN_PORT                      GPIO_PRT7
#define CY_SMARTIO_IN_PIN                       1
#define CY_SMARTIO_IN_PORT_MUX                  P7_1_GPIO
#define CY_SMARTIO_IN_PORT_MUX_PWM              P7_1_TCPWM0_LINE21

#define CY_SMARTIO_IN2_PORT                     GPIO_PRT7
#define CY_SMARTIO_IN2_PIN                      3
#define CY_SMARTIO_IN2_PORT_MUX                 P7_3_GPIO
#define CY_SMARTIO_IN2_PORT_MUX_PWM             P7_3_TCPWM0_LINE23

/* PWM PR Mode Configuration def */
#define CY_SMARTIO_TCPWM_GRP0_CNT               TCPWM0_GRP0_CNT21
#define CY_SMARTIO_TCPWM_PCLK                   PCLK_TCPWM0_CLOCKS21

#define CY_SMARTIO_TCPWM_GRP0_CNT2              TCPWM0_GRP0_CNT23
#define CY_SMARTIO_TCPWM_PCLK2                  PCLK_TCPWM0_CLOCKS23

  
/******************************************************************************/
/*                      Display #1 Definitions                                */
/******************************************************************************/
  
// Display 1 is connected to the FX3

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

#define CY_DISP1_DATA_A1_0_PORT                 GPIO_PRT17
#define CY_DISP1_DATA_A1_0_PIN                  0
#define CY_DISP1_DATA_A1_0_PIN_MUX              P17_0_VIDEOSS0_TTL_DSP1_DATA_A10 // RED1
    
#define CY_DISP1_DATA_A0_1_PORT                 GPIO_PRT18
#define CY_DISP1_DATA_A0_1_PIN                  0
#define CY_DISP1_DATA_A0_1_PIN_MUX              P18_0_VIDEOSS0_TTL_DSP1_DATA_A01 // RED2
    
#define CY_DISP1_DATA_A1_1_PORT                 GPIO_PRT18
#define CY_DISP1_DATA_A1_1_PIN                  1
#define CY_DISP1_DATA_A1_1_PIN_MUX              P18_1_VIDEOSS0_TTL_DSP1_DATA_A11 // RED3

#define CY_DISP1_DATA_A0_2_PORT                 GPIO_PRT18
#define CY_DISP1_DATA_A0_2_PIN                  2
#define CY_DISP1_DATA_A0_2_PIN_MUX              P18_2_VIDEOSS0_TTL_DSP1_DATA_A02 // RED4

#define CY_DISP1_DATA_A1_2_PORT                 GPIO_PRT18
#define CY_DISP1_DATA_A1_2_PIN                  3
#define CY_DISP1_DATA_A1_2_PIN_MUX              P18_3_VIDEOSS0_TTL_DSP1_DATA_A12 // RED5

#define CY_DISP1_DATA_A0_3_PORT                 GPIO_PRT18
#define CY_DISP1_DATA_A0_3_PIN                  4
#define CY_DISP1_DATA_A0_3_PIN_MUX              P18_4_VIDEOSS0_TTL_DSP1_DATA_A03 // RED6

#define CY_DISP1_DATA_A1_3_PORT                 GPIO_PRT18
#define CY_DISP1_DATA_A1_3_PIN                  5
#define CY_DISP1_DATA_A1_3_PIN_MUX              P18_5_VIDEOSS0_TTL_DSP1_DATA_A13 // RED7

#define CY_DISP1_DATA_A0_4_PORT                 GPIO_PRT18
#define CY_DISP1_DATA_A0_4_PIN                  6
#define CY_DISP1_DATA_A0_4_PIN_MUX              P18_6_VIDEOSS0_TTL_DSP1_DATA_A04 // GREEN0
    
#define CY_DISP1_DATA_A1_4_PORT                 GPIO_PRT18
#define CY_DISP1_DATA_A1_4_PIN                  7
#define CY_DISP1_DATA_A1_4_PIN_MUX              P18_7_VIDEOSS0_TTL_DSP1_DATA_A14 // GREEN1

#define CY_DISP1_DATA_A0_5_PORT                 GPIO_PRT19
#define CY_DISP1_DATA_A0_5_PIN                  0
#define CY_DISP1_DATA_A0_5_PIN_MUX              P19_0_VIDEOSS0_TTL_DSP1_DATA_A05 // GREEN2

#define CY_DISP1_DATA_A1_5_PORT                 GPIO_PRT19
#define CY_DISP1_DATA_A1_5_PIN                  1
#define CY_DISP1_DATA_A1_5_PIN_MUX              P19_1_VIDEOSS0_TTL_DSP1_DATA_A15 // GREEN3

#define CY_DISP1_DATA_A0_6_PORT                 GPIO_PRT19
#define CY_DISP1_DATA_A0_6_PIN                  2
#define CY_DISP1_DATA_A0_6_PIN_MUX              P19_2_VIDEOSS0_TTL_DSP1_DATA_A06 // GREEN4
    
#define CY_DISP1_DATA_A1_6_PORT                 GPIO_PRT19
#define CY_DISP1_DATA_A1_6_PIN                  3
#define CY_DISP1_DATA_A1_6_PIN_MUX              P19_3_VIDEOSS0_TTL_DSP1_DATA_A16 // GREEN5

#define CY_DISP1_DATA_A0_7_PORT                 GPIO_PRT19
#define CY_DISP1_DATA_A0_7_PIN                  4
#define CY_DISP1_DATA_A0_7_PIN_MUX              P19_4_VIDEOSS0_TTL_DSP1_DATA_A07 // GREEN6
    
#define CY_DISP1_DATA_A1_7_PORT                 GPIO_PRT19
#define CY_DISP1_DATA_A1_7_PIN                  5
#define CY_DISP1_DATA_A1_7_PIN_MUX              P19_5_VIDEOSS0_TTL_DSP1_DATA_A17 // GREEN7

#define CY_DISP1_DATA_A0_8_PORT                 GPIO_PRT19
#define CY_DISP1_DATA_A0_8_PIN                  6
#define CY_DISP1_DATA_A0_8_PIN_MUX              P19_6_VIDEOSS0_TTL_DSP1_DATA_A08 // BLUE0

#define CY_DISP1_DATA_A1_8_PORT                 GPIO_PRT19
#define CY_DISP1_DATA_A1_8_PIN                  7
#define CY_DISP1_DATA_A1_8_PIN_MUX              P19_7_VIDEOSS0_TTL_DSP1_DATA_A18 // BLUE1

#define CY_DISP1_DATA_A0_9_PORT                 GPIO_PRT20
#define CY_DISP1_DATA_A0_9_PIN                  0
#define CY_DISP1_DATA_A0_9_PIN_MUX              P20_0_VIDEOSS0_TTL_DSP1_DATA_A09 // BLUE2

#define CY_DISP1_DATA_A1_9_PORT                 GPIO_PRT20
#define CY_DISP1_DATA_A1_9_PIN                  1
#define CY_DISP1_DATA_A1_9_PIN_MUX              P20_1_VIDEOSS0_TTL_DSP1_DATA_A19 // BLUE3

#define CY_DISP1_DATA_A0_10_PORT                GPIO_PRT20
#define CY_DISP1_DATA_A0_10_PIN                 2
#define CY_DISP1_DATA_A0_10_PIN_MUX             P20_2_VIDEOSS0_TTL_DSP1_DATA_A010// BLUE4

#define CY_DISP1_DATA_A1_10_PORT                GPIO_PRT20
#define CY_DISP1_DATA_A1_10_PIN                 3
#define CY_DISP1_DATA_A1_10_PIN_MUX             P20_3_VIDEOSS0_TTL_DSP1_DATA_A110// BLUE5
    
#define CY_DISP1_DATA_A0_11_PORT                GPIO_PRT20
#define CY_DISP1_DATA_A0_11_PIN                 4
#define CY_DISP1_DATA_A0_11_PIN_MUX             P20_4_VIDEOSS0_TTL_DSP1_DATA_A011// BLUE6
    
#define CY_DISP1_DATA_A1_11_PORT                GPIO_PRT20
#define CY_DISP1_DATA_A1_11_PIN                 5
#define CY_DISP1_DATA_A1_11_PIN_MUX             P20_5_VIDEOSS0_TTL_DSP1_DATA_A111// BLUE7
  

/******************************************************************************/
/*                      FPD-LINK to HDMI Definitions                          */
/******************************************************************************/

// No need to configure FPDLINK io mux, it is a part of AMUXBUS.

/* FPD to HDMI reset pin */
#define CY_FPD_HDMI_RST_PORT                    GPIO_PRT2
#define CY_FPD_HDMI_RST_PIN                     5
#define CY_FPD_HDMI_RST_PIN_MUX                 P2_5_GPIO

/* FPD to HDMI communication I2C definitions */
#define CY_FPD_HDMI_I2C_TYPE                    SCB1
  
#define CY_FPD_HDMI_I2C_SDA_PORT                GPIO_PRT15
#define CY_FPD_HDMI_I2C_SDA_PIN                 2
#define CY_FPD_HDMI_I2C_SDA_PIN_MUX             P15_2_SCB1_I2C_SDA
  
#define CY_FPD_HDMI_I2C_SCL_PORT                GPIO_PRT15
#define CY_FPD_HDMI_I2C_SCL_PIN                 3
#define CY_FPD_HDMI_I2C_SCL_PIN_MUX             P15_3_SCB1_I2C_SCL
  
#define CY_FPD_HDMI_I2C_PCLK                    PCLK_SCB1_CLOCK
#define CY_FPD_HDMI_I2C_IRQN                    scb_1_interrupt_IRQn

/* FPD to HDMI audio definitions */
#define CY_FPD_HDMI_TDM_TYPE                    TDM0_TDM_STRUCT3
#define CY_FPD_HDMI_TDM_TX_IRQN                 tdm_0_interrupts_tx_3_IRQn

#define CY_FPD_HDMI_TX_SCK_PORT                 GPIO_PRT11
#define CY_FPD_HDMI_TX_SCK_PIN                  5
#define CY_FPD_HDMI_TX_SCK_PIN_MUX              P11_5_TDM0_TDM_TX_SCK3
  
#define CY_FPD_HDMI_TX_FSYNC_PORT               GPIO_PRT11
#define CY_FPD_HDMI_TX_FSYNC_PIN                6
#define CY_FPD_HDMI_TX_FSYNC_PIN_MUX            P11_6_TDM0_TDM_TX_FSYNC3
  
#define CY_FPD_HDMI_TX_SD_PORT                  GPIO_PRT11
#define CY_FPD_HDMI_TX_SD_PIN                   7
#define CY_FPD_HDMI_TX_SD_PIN_MUX               P11_7_TDM0_TDM_TX_SD3


/******************************************************************************/
/*                      MIPI CSI-2 Definitions                                */
/******************************************************************************/

// No need to configure MIPI CSI io mux, it is a part of AMUXBUS.

/* MIPI power enable */
#define CY_MIPI_CSI_IO_PE_PORT                  GPIO_PRT12
#define CY_MIPI_CSI_IO_PE_PIN                   3
#define CY_MIPI_CSI_IO_PE_PIN_MUX               P12_3_GPIO

/* MIPI Low power mode enable */
#define CY_MIPI_CSI_IO_LE_PORT                  GPIO_PRT12
#define CY_MIPI_CSI_IO_LE_PIN                   4
#define CY_MIPI_CSI_IO_LE_PIN_MUX               P12_4_GPIO
  
/* MIPI CSI Communication Block */
#define CY_MIPI_CSI_I2C_TYPE                    SCB10
  
#define CY_MIPI_CSI_I2C_SDA_PORT                GPIO_PRT0
#define CY_MIPI_CSI_I2C_SDA_PIN                 0
#define CY_MIPI_CSI_I2C_SDA_PIN_MUX             P0_0_SCB10_I2C_SDA
  
#define CY_MIPI_CSI_I2C_SCL_PORT                GPIO_PRT0
#define CY_MIPI_CSI_I2C_SCL_PIN                 1
#define CY_MIPI_CSI_I2C_SCL_PIN_MUX             P0_1_SCB10_I2C_SCL
  
#define CY_MIPI_CSI_I2C_PCLK                    PCLK_SCB10_CLOCK
#define CY_MIPI_CSI_I2C_IRQN                    scb_10_interrupt_IRQn
  
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

#endif /* BB_BSP_TVIIC2D6M_327BGA_DEVICE_REVC_EVKLITE_REVA_H */


/* [] END OF FILE */
