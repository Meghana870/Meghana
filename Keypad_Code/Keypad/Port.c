/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011, 2015 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_port.c
* Version      : CodeGenerator for RL78/G13 V2.03.01.03 [30 Jan 2015]
* Device(s)    : R5F104FFA
* Tool-Chain   : CCRL
* Description  : This file implements device driver for PORT module.
* Creation Date: 2015/04/09
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
/* Start user code for include. Do not edit comment generated here */
#include "KEY_INTERRUPT.h"
#include "iodefine.h"
#include "Port.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_PORT_Create
* Description  : This function initializes the Port I/O.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_PORT_Create(void)
{
    P3 = _00_Pn0_OUTPUT_0 | _00_Pn1_OUTPUT_0;
    P6 = _00_Pn0_OUTPUT_0 | _00_Pn1_OUTPUT_0 | _00_Pn2_OUTPUT_0 | _00_Pn3_OUTPUT_0;
    PM3 = _00_PMn0_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _FC_PM3_DEFAULT;
    PM6 = _00_PMn0_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT | _00_PMn3_MODE_OUTPUT | _F0_PM6_DEFAULT;
	
    PMC12 = 0x00;
    PM12 |= _01_PMn0_MODE_INPUT ;
}

/* Start user code for adding. Do not edit comment generated here */
/******************************************************************************
* Function Name: R_PORT_ScanData_Low
* Description : Scanning data is clear
* Arguments : none
* Return Value : none
******************************************************************************/
void R_PORT_ScanData_Low(void)
{
    P12 &= 0b11111100;                    /* Scanning data is clear */
}
/******************************************************************************
End of function R_PORT_ScanData_Low
******************************************************************************/

/******************************************************************************
* Function Name: R_PORT_ScanData_High
* Description : Scan line setup
* Arguments : none
* Return Value : none
******************************************************************************/
void R_PORT_ScanData_High(void)
{
    P12 |= 0b00000011;                   /* Scan line setup */
}
/******************************************************************************
End of function R_PORT_ScanData_High
******************************************************************************/

/******************************************************************************
* Function Name: R_PORT_ScanLine_Input
* Description : Set scan line input port and Pull-Up resistor Connect
* Arguments : none
* Return Value : none
******************************************************************************/
void R_PORT_ScanLine_Input(void)
{
    PM12 |= 0b00000011;                  /* Set scan line input port */
    PU12 |= 0b00000011;                  /* Pull-Up resistor Connect */
}
/******************************************************************************
End of function R_PORT_ScanLine_Input
******************************************************************************/

/******************************************************************************
* Function Name: R_PORT_ScanLine_Output
* Description : Set output port
* Arguments : none
* Return Value : none
******************************************************************************/
void R_PORT_ScanLine_Output(void)
{
    PM12 &= 0b11111100;                  /* Set output port */
}
/******************************************************************************
End of function R_PORT_ScanLine_Output
******************************************************************************/

/******************************************************************************
* Function Name: R_PORT_ScanLine_SetScan
* Description : Output scan line
* Arguments : Scanning line specification
* Return Value : none
******************************************************************************/
void R_PORT_ScanLine_SetScan(uint8_t scanline)
{
    PM12 ^= (scanline & 0b00000001);     /* Output scan line */
}
/******************************************************************************
End of function R_PORT_ScanLine_SetScan
******************************************************************************/

void R_PORT_7_ScanLine_Output(void)
{
    P7 = _00_Pn0_OUTPUT_0 | _00_Pn1_OUTPUT_0 | _00_Pn2_OUTPUT_0 | _00_Pn3_OUTPUT_0;
    PM7 = _00_PMn0_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT | _00_PMn3_MODE_OUTPUT | _F0_PM7_DEFAULT;
}

void R_PORT_7_ScanLine_Input(void)
{
    PM7 = _01_PMn0_MODE_INPUT | _02_PMn1_MODE_INPUT | _04_PMn2_MODE_INPUT | _08_PMn3_MODE_INPUT | _0F_PM7_DEFAULT;
}
/* End user code. Do not edit comment generated here */