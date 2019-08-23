/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR 
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE 
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software 
* and to discontinue the availability of this software.  By using this software, 
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_main.c
* Version      : CodeGenerator for RL78/G14 V1.01.01 [11 Oct 2011]
* Device(s)    : R5F104FF
* Tool-Chain   : CA78K0R
* Description  : This file implements main function.
* Creation Date: 8/19/2019
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
/* Start user code for include. Do not edit comment generated here */
#include "KEY_INTERRUPT.h"
//#include "iodefine.h"
#include "Port.h"
#include "Timer.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
#define KEYPRESS_12_0 0x01
#define KEYPRESS_12_1 0x02
#define KEYPRESS_12_2 0x04
#define KEYPRESS_12_3 0x08
#define KEYPRESS_12_4 0x10

#define SCANKEY_7_0 0x08
#define SCANKEY_7_1 0x04
#define SCANKEY_7_2 0x02
#define SCANKEY_7_3 0x01

 uint8_t pressed_key =0;
 uint8_t keyevent =0;
 uint8_t pressTypeRow = 0;
 uint8_t scanInput =0 ;
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
    /* Start user code. Do not edit comment generated here */
    
    
   // DI(); /* Disable interrupt */
    hdwinit();
    
    R_PORT_7_ScanLine_Output();

    //#if 0
    while(1)
    {
	    if(((P12 & 0x1f) == 0x1f) &&(pressTypeRow == 0))
	    {
			NOP();
	    }
	    else 
	    {
			if(pressTypeRow == 0)
			{
 				keyevent = P12;
				keyevent = ~keyevent;
				if(keyevent & KEYPRESS_12_0)
					pressTypeRow |=KEYPRESS_12_0;
				if(keyevent & KEYPRESS_12_1)
					pressTypeRow |=KEYPRESS_12_1;
				if(keyevent & KEYPRESS_12_2)
					pressTypeRow |=KEYPRESS_12_2;
				if(keyevent & KEYPRESS_12_3)
					pressTypeRow |=KEYPRESS_12_3;
				if(keyevent & KEYPRESS_12_4)
					pressTypeRow |=KEYPRESS_12_4;
				R_PORT_7_ScanLine_Input();
				R_Wait(30);
    			}
			else
			{
					
				scanInput = P7;
				if(((scanInput & SCANKEY_7_0) == 0x08 ) && (pressTypeRow == 0x1))
				{
					R_Wait(1);//PLAN UP
				}
				if(((scanInput & SCANKEY_7_1 ) == 0x04) && (pressTypeRow == 0x1))
				{

					R_Wait(1);//PLAN DOWN
				}
				if(((scanInput & SCANKEY_7_2 ) == 0x02) && (pressTypeRow == 0x1))
				{
					R_Wait(1);//4 CH
				}
				if(((scanInput & SCANKEY_7_3 ) == 0x01) && (pressTypeRow == 0x1))
				{
					R_Wait(1);//EXIT
				}
				
				if(((scanInput & SCANKEY_7_0 ) == 0x08) && (pressTypeRow == 0x10))
				{
					R_Wait(1);//FREQ UP
				}
				if(((scanInput & SCANKEY_7_1 ) == 0x04) && (pressTypeRow == 0x10))
				{
					R_Wait(1);//FREQ DOWN
				}
				if(((scanInput & SCANKEY_7_2 ) == 0x02) && (pressTypeRow == 0x10))
				{
					R_Wait(1);//SLOPE
				}
				if(((scanInput & SCANKEY_7_3 ) == 0x01) && (pressTypeRow == 0x10))
				{
					R_Wait(1);//SAVE
				}
				
				if(((scanInput & SCANKEY_7_0 ) == 0x08) && (pressTypeRow == 0x8))
				{
					R_Wait(1);//CH UP
				}
				if(((scanInput & SCANKEY_7_1 ) == 0x04) && (pressTypeRow == 0x8))
				{
					R_Wait(1);//CH DOWN
				}
				if(((scanInput & SCANKEY_7_2 ) == 0x02) && (pressTypeRow == 0x8))
				{
					R_Wait(1);//SET
				}
				if(((scanInput & SCANKEY_7_3 ) == 0x01) && (pressTypeRow == 0x8))
				{
					R_Wait(1);//SELECT
				}
				
				if(((scanInput & SCANKEY_7_0 ) == 0x08) && (pressTypeRow == 0x4))
				{
					R_Wait(1);//FAV UP
				}
				if(((scanInput & SCANKEY_7_1 ) == 0x04) && (pressTypeRow == 0x4))
				{
					R_Wait(1);//FAV DOWN
				}
				if(((scanInput & SCANKEY_7_2 ) == 0x02) && (pressTypeRow == 0x4))
				{
					R_Wait(1);//PLAN
				}
				if(((scanInput & SCANKEY_7_3 ) == 0x01) && (pressTypeRow == 0x4))
				{
					R_Wait(1);//MER
				}
				
				pressTypeRow = 0x00;
				R_PORT_7_ScanLine_Output();
			}
	       }
	    	   
    }
  //  #endif
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
void R_Wait(int n)
{
    while(n--)
    {
    	R_TAU0_Channel0_Start();                    /* Channel0 operation start */
	while (!TMIF00)
	{
	;
	}
	R_TAU0_Channel0_Stop();
    }
}    


/* End user code. Do not edit comment generated here */