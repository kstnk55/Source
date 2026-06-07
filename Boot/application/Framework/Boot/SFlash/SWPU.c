/****************************************************************************/
/* File name		: SWPU.c												*/
/*--------------------------------------------------------------------------*/
/* Customer			: Platform module										*/
/*--------------------------------------------------------------------------*/
/* CPU				: TRAVEO T2G Body/cluster model							*/
/*					: (CYT3BB/CYT4BF/CYT3DL/CYT4DN)							*/
/*--------------------------------------------------------------------------*/
/* Programmed by	: Infineon												*/
/* Date				: 2023/05/23											*/
/* Copyrights		: Nippon Seiki Co.,Ltd									*/
/* Description		: Describes application protection settings.			*/
/*--------------------------------------------------------------------------*/
/* Updated by		:														*/
/* Date				:														*/
/* Revision			:														*/
/****************************************************************************/

#include "cy_project.h"
#include "cy_si_config.h"

CY_SECTION(".cy_sflash_swpu") __USED static const cy_stc_si_app_prot_t cy_si_appprot = 
{
	.objSize				= OBJECT_SIZE,				/* Application Protection Object Size (in bytes) */
	.n_fwpu					= N_FWPU,					/* Number of FWPU Max 16 */

/* Add FWPU configuration here, if you need additional FWPU region */
/*    .fwpu0_adr.addr30       = 0x10000000>>2ul, */         /* Region address */
/*    .fwpu0_size.region_size = 0x200, */                   /* in bytes (multiple of 4) */
/*    .fwpu0_size.enable      = APP_PROT_ENABLE, */         /* FWPU0 enable */
/*    .fwpu0_sl_att.urw       = APP_PROT_ALLOW, */          /* FWPU0 Slave Attribute */
/*    .fwpu0_sl_att.prw       = APP_PROT_ALLOW, */          /* FWPU0 Slave Attribute */
/*    .fwpu0_sl_att.ns        = APP_PROT_ALLOW, */          /* FWPU0 Slave Attribute */
/*    .fwpu0_sl_att.pc_mask   = 0x00FF, */                  /* FWPU0 Slave Attribute */
                                                            /* bit0: PC0 mask (0: Prohibit, 1: Allow) */
                                                            /*  :                                     */
                                                            /* bit7: PC7 mask                         */
                                                            /* bit[8:15]: 0 */
/*    .fwpu0_ms_att.urw       = APP_PROT_ALLOW, */          /* FWPU0 Master Attribute */
/*    .fwpu0_ms_att.prw       = APP_PROT_ALLOW, */          /* FWPU0 Master Attribute */
/*    .fwpu0_ms_att.ns        = APP_PROT_ALLOW, */          /* FWPU0 Master Attribute */
/*    .fwpu0_ms_att.pc_mask   = 0x00FF, */                  /* FWPU0 Master Attribute */

	.n_erpu					= N_ERPU,					/* Number of ERPU Max 4 */
	.erpu0_offset.offset	= 0x68,						/* ERPU0 offset (Default) */
	.erpu0_size.region_size	= 0x18,						/* ERPU0 region size (Default) */
	.erpu0_size.enable		= APP_PROT_ENABLE,			/* ERPU0 enable (Default) */
	.erpu0_sl_att.urw		= APP_PROT_ALLOW,			/* ERPU0 Slave Attribute (Default) */
	.erpu0_sl_att.prw		= APP_PROT_ALLOW,			/* ERPU0 Slave Attribute (Default) */
	.erpu0_sl_att.ns		= APP_PROT_ALLOW,			/* ERPU0 Slave Attribute (Default) */
	.erpu0_sl_att.pc_mask	= 0x00FF,					/* ERPU0 Slave Attribute (Default) */
	.erpu0_ms_att.urw		= APP_PROT_ALLOW,			/* ERPU0 Master Attribute (Default) */
	.erpu0_ms_att.prw		= APP_PROT_ALLOW,			/* ERPU0 Master Attribute (Default) */
	.erpu0_ms_att.ns		= APP_PROT_ALLOW,			/* ERPU0 Master Attribute (Default) */
	.erpu0_ms_att.pc_mask	= 0x00FF,					/* ERPU0 Master Attribute (Default) */

/* Add ERPU configuration here, if you need additional ERPU region*/
/*    .erpu1_offset.offset    = , */
/*    .erpu1_size.region_size = , */
/*    .erpu1_size.enable      = , */
/*    .erpu1_sl_att.urw       = , */
/*    .erpu1_sl_att.prw       = , */
/*    .erpu1_sl_att.ns        = , */
/*    .erpu1_sl_att.pc_mask   = , */
/*    .erpu1_ms_att.urw       = , */
/*    .erpu1_ms_att.prw       = , */
/*    .erpu1_ms_att.ns        = , */
/*    .erpu1_ms_att.pc_mask   = , */

	.n_ewpu					= N_EWPU,					/* Number of EWPU Max 4 */
	.ewpu0_offset.offset	= 0x68,						/* EWPU0 offset (Default) */
	.ewpu0_size.region_size	= 0x18,						/* EWPU0 region size (Default) */
	.ewpu0_size.enable		= APP_PROT_ENABLE,			/* EWPU0 enable (Default) */
	.ewpu0_sl_att.urw		= APP_PROT_ALLOW,			/* EWPU0 Slave Attribute (Default) */
	.ewpu0_sl_att.prw		= APP_PROT_ALLOW,			/* EWPU0 Slave Attribute (Default) */
	.ewpu0_sl_att.ns		= APP_PROT_ALLOW,			/* EWPU0 Slave Attribute (Default) */
	.ewpu0_sl_att.pc_mask	= 0x00FF,					/* EWPU0 Slave Attribute (Default) */
	.ewpu0_ms_att.urw		= APP_PROT_ALLOW,			/* EWPU0 Master Attribute (Default) */
	.ewpu0_ms_att.prw		= APP_PROT_ALLOW,			/* EWPU0 Master Attribute (Default) */
	.ewpu0_ms_att.ns		= APP_PROT_ALLOW,			/* EWPU0 Master Attribute (Default) */
	.ewpu0_ms_att.pc_mask	= 0x00FF,					/* EWPU0 Master Attribute (Default) */

/* Add EWPU configuration here, if you need additional EWPU region */
/*    .ewpu1_offset.offset    = , */
/*    .ewpu1_size.region_size = , */
/*    .ewpu1_size.enable      = , */
/*    .ewpu1_sl_att.urw       = , */
/*    .ewpu1_sl_att.prw       = , */
/*    .ewpu1_sl_att.ns        = , */
/*    .ewpu1_sl_att.pc_mask   = , */
/*    .ewpu1_ms_att.urw       = , */
/*    .ewpu1_ms_att.prw       = , */
/*    .ewpu1_ms_att.ns        = , */
/*    .ewpu1_ms_att.pc_mask   = , */
};

