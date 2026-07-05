/**
 * @file SSFTxxx_M0P_SoftVer_DEF.h
 * @brief Software version definitions for TraveoII (SHRV819) (This module provided by Nippon Seiki should be left unchanged by FPT.)
 * @details Header file containing software version macros for TraveoII. 
 */
/************************************************************************************************/
/* Model(Theme No.)		： SHRV819																*/
/* File Name			： SSFTxxx_M0P_SoftVer_DEF.h											*/
/*----------------------------------------------------------------------------------------------*/
/* CPU					： TraveoII																*/
/* Date					： 2024/07/12															*/
/*----------------------------------------------------------------------------------------------*/
/* Programmed by		： 																		*/
/* Copyrights			： Nippon Seiki Co.,Ltd.												*/
/*----------------------------------------------------------------------------------------------*/
/* Update by		: $Author: Hasegawa Keita (A01A091495) $									*/
/* Date 			: $Date: 2025/01/14 17:33:27JST $											*/
/* Version			: $Revision: 1.6 $													*/
/************************************************************************************************/
#ifndef M0P_SOFTVER_DEF_H
#define M0P_SOFTVER_DEF_H


/*■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■*/
/*■																						■*/
/*■	メーカー機種コード																	■*/
/*■																						■*/
/*■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■*/

#define		M0P_MAKER_MODEL_CODE1			( 'S' )					// ﾒｰｶｰ機種ｺｰﾄﾞ 1 桁目
#define		M0P_MAKER_MODEL_CODE2			( 'H' )					// ﾒｰｶｰ機種ｺｰﾄﾞ 2 桁目
#define		M0P_MAKER_MODEL_CODE3			( 'R' )					// ﾒｰｶｰ機種ｺｰﾄﾞ 3 桁目
#define		M0P_MAKER_MODEL_CODE4			( 'V' )					// ﾒｰｶｰ機種ｺｰﾄﾞ 4 桁目
#define		M0P_MAKER_MODEL_CODE5			( '8' )					// ﾒｰｶｰ機種ｺｰﾄﾞ 5 桁目
#define		M0P_MAKER_MODEL_CODE6			( '1' )					// ﾒｰｶｰ機種ｺｰﾄﾞ 6 桁目
#define		M0P_MAKER_MODEL_CODE7			( '9' )					// ﾒｰｶｰ機種ｺｰﾄﾞ 7 桁目

/*■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■*/
/*■																						■*/
/*■	ソフト識別子																		■*/
/*■																						■*/
/*■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■*/

#define		M0P_SOFTWARE_DISCRIMINATION1	( '_' )					// ｿﾌﾄｳｪｱ識別子 1 桁目

#define		M0P_SOFTWARE_DISCRIMINATION2	( 'B' )					// ｿﾌﾄｳｪｱ識別子 2 桁目

#define		M0P_SOFTWARE_DISCRIMINATION3	( '_' )					// ｿﾌﾄｳｪｱ識別子 3 桁目

/*■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■*/
/*■																						■*/
/*■	ソフトウェアバージョン																■*/
/*■																						■*/
/*■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■*/

#define		M0P_SOFTWARE_VERSION1			( '0' )					// ｿﾌﾄｳｪｱﾊﾞｰｼﾞｮﾝ 2 桁目
#define		M0P_SOFTWARE_VERSION2			( '9' )					// ｿﾌﾄｳｪｱﾊﾞｰｼﾞｮﾝ 3 桁目
#define		M0P_SOFTWARE_VERSION3			( '6' )					// ｿﾌﾄｳｪｱﾊﾞｰｼﾞｮﾝ 4 桁目
#define		M0P_SOFTWARE_VERSION4			( '1' )					// ｿﾌﾄｳｪｱﾊﾞｰｼﾞｮﾝ 5 桁目
#define		M0P_SOFTWARE_VERSION5			( '0' )					// ｿﾌﾄｳｪｱﾊﾞｰｼﾞｮﾝ 6 桁目
#define		M0P_SOFTWARE_VERSION6			( '0' )					// ｿﾌﾄｳｪｱﾊﾞｰｼﾞｮﾝ 7 桁目

/* M0 Software version */
#define M0_SOFTWARE_VERSION_SIZE (32u)

#endif /* M0P_SOFTVER_DEF_H */
