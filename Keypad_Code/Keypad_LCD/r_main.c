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
* Creation Date: 8/20/2019
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
 uint8_t temp = 0;
 
 /* RS Register Select pin */
#define RS_PIN                     P3.1
/* Display Enable pin */	
#define EN_PIN                     P3.0	
/* Data bus port */
#define DATA_PORT                  P6

void Display_Delay(int n);
void Delay(void);

void Init_lcd (void); 
void Write_com_lcd (unsigned char c); 
void Write_com_lcd1 (unsigned char c);
void Write_char_lcd (unsigned char c); 
void Write_string_lcd (const char *s); 
void Clear_lcd (void); 
void Goto_lcd (unsigned char pos);
void enable_e(void);
 

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
    
    #if 0
    PM3 = PM3 & 0xfd;
    P3 = P3 | 0x02;
    R_Wait(1000);
    P3 = P3 & 0xfd;
    #endif
    
    //enable_e();
    Display_Delay(40);
    #if 0
    PM14 = PM14 & 0xBF;
    P14 = P14 | 0x40;
    R_Wait(1000);
    P14 = P14 & 0xBF;
    #endif
    
    
    hdwinit();
    R_PORT_7_ScanLine_Output();
    
    Init_lcd(); // LCD Initialization
    Clear_lcd(); // Reset LCD and move to start position
    
    #if 0
    RS_PIN =1;
    R_Wait(1000);
    RS_PIN =0;
    #endif

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
					 
				
					 Write_com_lcd(0x01);
    					 Display_Delay(50000);
    					 Clear_lcd();
    					 Write_string_lcd("FREQ=474000000");
					
				}
				if(((scanInput & SCANKEY_7_1 ) == 0x04) && (pressTypeRow == 0x1))
				{
					 Write_com_lcd(0x01);
    					 Display_Delay(50000);
    					 Clear_lcd();
    					 Write_string_lcd("FREQ=482000000");
				}
				if(((scanInput & SCANKEY_7_2 ) == 0x02) && (pressTypeRow == 0x1))
				{
					 Write_com_lcd(0x01);
    					 Display_Delay(50000);
    					 Clear_lcd();
    					 Write_string_lcd("FREQ=490000000");
				}
				if(((scanInput & SCANKEY_7_3 ) == 0x01) && (pressTypeRow == 0x1))
				{
					 Write_com_lcd(0x01);
    					 Display_Delay(50000);
    					 Clear_lcd();
    					 Write_string_lcd("FREQ=498000000");
				}
				
				if(((scanInput & SCANKEY_7_0 ) == 0x08) && (pressTypeRow == 0x10))
				{
					 Write_com_lcd(0x01);
    					 Display_Delay(50000);
    					 Clear_lcd();
    					 Write_string_lcd("FREQ UP");
				}
				if(((scanInput & SCANKEY_7_1 ) == 0x04) && (pressTypeRow == 0x10))
				{
					 Write_com_lcd(0x01);
    					 Display_Delay(50000);
    					 Clear_lcd();
    					 Write_string_lcd("FREQ DOWN");	
				}
				if(((scanInput & SCANKEY_7_2 ) == 0x02) && (pressTypeRow == 0x10))
				{
					 Write_com_lcd(0x01);
    					 Display_Delay(50000);
    					 Clear_lcd();
    					 Write_string_lcd("SLOPE");
				}
				if(((scanInput & SCANKEY_7_3 ) == 0x01) && (pressTypeRow == 0x10))
				{
					 Write_com_lcd(0x01);
    					 Display_Delay(50000);
    					 Clear_lcd();
    					 Write_string_lcd("SAVE");
				}
				
				if(((scanInput & SCANKEY_7_0 ) == 0x08) && (pressTypeRow == 0x8))
				{
					 Write_com_lcd(0x01);
    					 Display_Delay(50000);
    					 Clear_lcd();
    					 Write_string_lcd("CH UP");
				}
				if(((scanInput & SCANKEY_7_1 ) == 0x04) && (pressTypeRow == 0x8))
				{
					 Write_com_lcd(0x01);
    					 Display_Delay(50000);
    					 Clear_lcd();
    					 Write_string_lcd("CH DOWN");
				}
				if(((scanInput & SCANKEY_7_2 ) == 0x02) && (pressTypeRow == 0x8))
				{  
					 Write_com_lcd(0x01);
    					 Display_Delay(50000);
    					 Clear_lcd();
    					 Write_string_lcd("SET");
				}
				if(((scanInput & SCANKEY_7_3 ) == 0x01) && (pressTypeRow == 0x8))
				{
					 Write_com_lcd(0x01);
    					 Display_Delay(50000);
    					 Clear_lcd();
    					 Write_string_lcd("SELECT");
				}
				
				if(((scanInput & SCANKEY_7_0 ) == 0x08) && (pressTypeRow == 0x4))
				{
					 Write_com_lcd(0x01);
    					 Display_Delay(50000);
    					 Clear_lcd();
    					 Write_string_lcd("FAV UP");
				}
				if(((scanInput & SCANKEY_7_1 ) == 0x04) && (pressTypeRow == 0x4))
				{
					 Write_com_lcd(0x01);
    					 Display_Delay(50000);
    					 Clear_lcd();
    					 Write_string_lcd("FAV DOWN");
				}
				if(((scanInput & SCANKEY_7_2 ) == 0x02) && (pressTypeRow == 0x4))
				{
					 Write_com_lcd(0x01);
    					 Display_Delay(50000);
    					 Clear_lcd();
    					 Write_string_lcd("FAV+ PLAN");
				}
				if(((scanInput & SCANKEY_7_3 ) == 0x01) && (pressTypeRow == 0x4))
				{
					 Write_com_lcd(0x01);
    					 Display_Delay(50000);
    					 Clear_lcd();
    					 Write_string_lcd("MER BER");
				}
				
				pressTypeRow = 0x00;
				R_PORT_7_ScanLine_Output();
			}
	       }
	    	   
    }
    if(temp == 1)
    {
	    Write_com_lcd(0x01);
    	    Display_Delay(50000);
    	    Clear_lcd();
    	    Write_string_lcd("PLAN UP");
    }
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

void Init_lcd (void) 
{ 

	RS_PIN = 0; // write control bytes
	Display_Delay(7000);
	
	Write_com_lcd1(2);
	enable_e();
	Display_Delay(7000);
	
	Write_com_lcd(0x28); // 4 bit mode, 
	Display_Delay(7000);
	
	Write_com_lcd(0x08); // display off
	Display_Delay(7000);
	
	Write_com_lcd(0x0C); // display on, blink curson off
	Display_Delay(7000);
	
	Write_com_lcd(0x06);// entry mode 
	Display_Delay(7000);
	
}

void Write_com_lcd1(unsigned char c)
{
	RS_PIN = 0;
	DATA_PORT  = (DATA_PORT    & 0xF0) | (c >> 4);
	enable_e();
	//Display_Delay(39);
	
	DATA_PORT  = (DATA_PORT    & 0xF0) | (c & 0x0F);
	enable_e();
	//Display_Delay(39);

}

void Write_com_lcd(unsigned char c)// send command to lcd 

{
	
	RS_PIN = 0; // write the command 
	DATA_PORT  = (DATA_PORT    & 0xF0) | (c >> 4);
	enable_e();
	//Display_Delay(39);
	
	DATA_PORT  = (DATA_PORT    & 0xF0) | (c & 0x0F);
	enable_e();
	//Display_Delay(39);
}

void Write_char_lcd(unsigned char c)
{

	RS_PIN = 1; // write charactsers
	DATA_PORT   = (DATA_PORT   & 0xF0) | (c >> 4);
	enable_e();
	//Display_Delay(39);
	
	DATA_PORT   = (DATA_PORT   & 0xF0) | (c & 0x0F);
	enable_e();
	Display_Delay(39);
} 

void Write_string_lcd(const char  *s)

{
	RS_PIN = 1; // write characters
	while(*s)
	Write_char_lcd(*s++);
	
}

void Clear_lcd(void)

{
	RS_PIN = 0;
	Write_com_lcd(0x80);
	Display_Delay(39);
}

void Goto_lcd(unsigned char pos)
{
	RS_PIN = 0;
	Write_com_lcd(0x80+pos);
}

void Display_Delay(int n)
{
	while(n--)
    {
    	R_TMR_RJ0_Start();
	while ( TRJIF0 == 1U);
	R_TMR_RJ0_Stop();
    }
	
	
}

void enable_e() {
EN_PIN=1;
//Display_Delay(39);

NOP();
NOP();

NOP();
NOP();
NOP();
//#if 0
NOP();
NOP();
NOP();
NOP();

NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
//#endif


EN_PIN= 0;
 //Display_Delay(39);
//R_Wait(1);

NOP();
NOP();
NOP();

NOP();
NOP();
//#if 0
NOP();
NOP();
NOP();
NOP();

NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
NOP();
//#endif

}


/* End user code. Do not edit comment generated here */
