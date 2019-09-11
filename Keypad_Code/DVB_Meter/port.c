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
* File Name    : r_cg_port.c
* Version      : CodeGenerator for RL78/G14 V1.01.01 [11 Oct 2011]
* Device(s)    : R5F104FF
* Tool-Chain   : CA78K0R
* Description  : This file implements device driver for PORT module.
* Creation Date: 7/1/2019
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
/* Start user code for include. Do not edit comment generated here */
#include "Si2165.h"
#include "Si2165_Priv.h"
#include "Port.h"
#include "Timer.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
void Keypad_SET(void);
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
void R_PORT_7_ScanLine_Output(void)
{
	P7 =0xf0;
	PM7 = _00_PMn0_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT | _00_PMn3_MODE_OUTPUT | _F0_PM7_DEFAULT;
}

void R_PORT_7_ScanLine_Input(void)
{
	PM7 = _01_PMn0_MODE_INPUT | _02_PMn1_MODE_INPUT | _04_PMn2_MODE_INPUT | _08_PMn3_MODE_INPUT | _0F_PM7_DEFAULT;
}

void Lcd_display(void)
{
	Init_lcd(); // LCD Initialization
	Clear_lcd(); // Reset LCD and move to start position
	  
	Write_com_lcd(0x01);
	Display_Delay(5000);
	Clear_lcd();
	Goto_lcd(0x02);
	Display_Delay(5000);
	Write_string_lcd("SHARP VISION");
	Display_Delay(5000);
	Write_com_lcd(0xC0);
	Display_Delay(5000);
	Goto_lcd(0x45);
	Display_Delay(5000);
	Write_string_lcd("AS 985");
	    
	Delay();
	    
	Write_com_lcd(0x01);
	Display_Delay(5000);
	Clear_lcd();
	Goto_lcd(0x03);
	Display_Delay(5000);
	Write_string_lcd("QAM METER");
	Display_Delay(5000);
	Write_com_lcd(0xC0);
	Display_Delay(5000);
	Goto_lcd(0x40);
	Display_Delay(5000);
	Write_string_lcd("ANALOG + OPTICAL");
	    
	Delay();
	    
	Write_com_lcd(0x01);
	Display_Delay(5000);
	Clear_lcd();
	Goto_lcd(0x01);
	Display_Delay(5000);
	Write_string_lcd("ANALOG SYSTEMS");
	Display_Delay(5000);
	Write_com_lcd(0xC0);
	Display_Delay(5000);
	Goto_lcd(0x40);
	Display_Delay(5000);
	Write_string_lcd("BATTERY:>>>>");
	    
	Delay();
	    
	Write_com_lcd(0x01);
	Display_Delay(5000);
	Clear_lcd();
	Goto_lcd(0x00);
	Display_Delay(5000);
	Write_string_lcd("S01=108.00");
	Display_Delay(5000);
	Write_com_lcd(0xC0);
	Display_Delay(5000);
	Goto_lcd(0x40);
	Display_Delay(5000);
	Write_string_lcd("DC:00 NOR QAM P1");
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
	
	DATA_PORT  = (DATA_PORT    & 0xF0) | (c & 0x0F);
	enable_e();
}

void Write_com_lcd(unsigned char c)// send command to lcd 
{
	RS_PIN = 0; // write the command 
	DATA_PORT  = (DATA_PORT    & 0xF0) | (c >> 4);
	enable_e();
	
	DATA_PORT  = (DATA_PORT    & 0xF0) | (c & 0x0F);
	enable_e();
}

void Write_char_lcd(unsigned char c)
{
	RS_PIN = 1; // write charactsers
	DATA_PORT   = (DATA_PORT   & 0xF0) | (c >> 4);
	enable_e();
	
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

void Delay(void)
{
	Display_Delay(5000000);
	Display_Delay(5000000);
	Display_Delay(5000000);
	Display_Delay(5000000);
	Display_Delay(5000000);
	Display_Delay(5000000);
	Display_Delay(5000000);
	Display_Delay(5000000);
	Display_Delay(5000000);
	Display_Delay(5000000);
	Display_Delay(5000000);
	Display_Delay(5000000);
	Display_Delay(5000000);
	Display_Delay(5000000);
	Display_Delay(5000000);
	Display_Delay(5000000);
	Display_Delay(5000000);
	Display_Delay(5000000);
	Display_Delay(5000000);
	Display_Delay(5000000);
	Display_Delay(5000000);
	Display_Delay(5000000);
	Display_Delay(5000000);
	Display_Delay(5000000);
	Display_Delay(5000000);
	Display_Delay(5000000);
	Display_Delay(5000000);
	Display_Delay(5000000);
}
void enable_e() 
{
	EN_PIN=1;
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
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();

	EN_PIN= 0; 
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
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
}

void Keypad(void)
{
	R_PORT_7_ScanLine_Output();
	Init_lcd(); // LCD Initialization
	Clear_lcd(); // Reset LCD and move to start position
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
					if(((scanInput & SCANKEY_7_0) == 0x08 ) && (pressTypeRow == 0x1))//PLAN UP
					{
						Write_com_lcd(0xC0);
						Display_Delay(5000);
						Goto_lcd(0x4e);
					 	Display_Delay(5000);
					 	Write_string_lcd(PLAN_array[PLAN_Count]);
						Delay();
						PLAN_Count++;
						if(PLAN_Count == 7)
						{
							PLAN_Count=0;	 
						}
					}
					if(((scanInput & SCANKEY_7_1 ) == 0x04) && (pressTypeRow == 0x1))//PLAN DOWN
					{
						Write_com_lcd(0xC0);
						Display_Delay(5000);
					 	Goto_lcd(0x4e);
					 	Display_Delay(5000);
					 	Write_string_lcd(PLAN_array[PLAN_Count]);
						Delay();
						PLAN_Count--; 
						if(PLAN_Count == -1)
						{
							PLAN_Count = 6;
						}
					}
					if(((scanInput & SCANKEY_7_2 ) == 0x02) && (pressTypeRow == 0x1))//4 CH
					{
						Write_com_lcd(0x01);
						Display_Delay(50000);
	    					Clear_lcd();
						Write_string_lcd("FREQ=490000000");
					}
					if(((scanInput & SCANKEY_7_3 ) == 0x01) && (pressTypeRow == 0x1))//EXIT
					{
						Write_com_lcd(0x01);
						Display_Delay(50000);
	    					Clear_lcd();
	    					Write_string_lcd("FREQ=498000000");
					}
					if(((scanInput & SCANKEY_7_0 ) == 0x08) && (pressTypeRow == 0x10))//FREQ UP
					{
						Write_com_lcd(0x01);
	    					Display_Delay(50000);
	    					Clear_lcd();
	    					Write_string_lcd("FREQ UP");
					}
					if(((scanInput & SCANKEY_7_1 ) == 0x04) && (pressTypeRow == 0x10))//FREQ DOWN
					{
						Write_com_lcd(0x01);
	    					Display_Delay(50000);
	    					Clear_lcd();
	    					Write_string_lcd("FREQ DOWN");	
					}
					if(((scanInput & SCANKEY_7_2 ) == 0x02) && (pressTypeRow == 0x10)) //SLOPE
					{
					 
					  
					
					}
					if(((scanInput & SCANKEY_7_3 ) == 0x01) && (pressTypeRow == 0x10))//SAVE
					{
						Write_com_lcd(0x01);
	    					Display_Delay(50000);
	    					Clear_lcd();
	    					Write_string_lcd("SAVE");
					}
					if(((scanInput & SCANKEY_7_0 ) == 0x08) && (pressTypeRow == 0x8))//CH UP
					{
						Display_Delay(5000);
						Goto_lcd(0x00);
						Display_Delay(5000);
						Write_string_lcd(CHANNEL_Number[CHANNEL_Count]);
						Display_Delay(5000);
						Goto_lcd(0x04);
						Display_Delay(5000);
						Write_string_lcd(CHANNEL_Frequency[CHANNEL_Count]);
						Delay();
						CHANNEL_Count++;
						 
						frequency = CHANNEL_Frequency_Int[CHANNEL_Count];
						calculate_tuner_value(frequency);
						I2C_Write_Tuner(tunerdata); 
						 
						if(CHANNEL_Count == 106)
						{
							CHANNEL_Count=0;	 
						}
					}
					if(((scanInput & SCANKEY_7_1 ) == 0x04) && (pressTypeRow == 0x8))//CH DOWN
					{
						 Display_Delay(5000);
						 Goto_lcd(0x00);
						 Display_Delay(5000);
						 Write_string_lcd(CHANNEL_Number[CHANNEL_Count]);
						 Display_Delay(5000);
						 Goto_lcd(0x04);
						 Display_Delay(5000);
						 Write_string_lcd(CHANNEL_Frequency[CHANNEL_Count]);
						 Delay();
						 CHANNEL_Count--;
						 if(CHANNEL_Count == -1)
						 {
					         	CHANNEL_Count = 105;
						 }
					}
					if(((scanInput & SCANKEY_7_2 ) == 0x02) && (pressTypeRow == 0x8)) //SET
					{  	 
						 Write_com_lcd(0x01);
						 Display_Delay(5000);
						 Clear_lcd();
						 Goto_lcd(0x00);
						 Display_Delay(5000);
						 Write_string_lcd("QAM  SYMBOL");
						 Display_Delay(5000);
						 Write_com_lcd(0xC0);
						 Display_Delay(5000);
						 //Goto_lcd(0x40);
						 Display_Delay(5000);
						 Write_string_lcd("016  1.000    P1");
						// Keypad_SET();
					 
					}
					if(((scanInput & SCANKEY_7_3 ) == 0x01) && (pressTypeRow == 0x8))//SELECT
					{
						 Write_com_lcd(0x01);
	    					 Display_Delay(50000);
	    					 Clear_lcd();
	    					 Write_string_lcd("SELECT");
					}
					if(((scanInput & SCANKEY_7_0 ) == 0x08) && (pressTypeRow == 0x4))//FAV UP
					{
						 Write_com_lcd(0x01);
	    					 Display_Delay(50000);
	    					 Clear_lcd();
	    					 Write_string_lcd("FAV UP");
					}
					if(((scanInput & SCANKEY_7_1 ) == 0x04) && (pressTypeRow == 0x4))//FAV DOWN
					{
						Write_com_lcd(0x01);
	    					 Display_Delay(50000);
	    					 Clear_lcd();
	    					 Write_string_lcd("FAV DOWN");
					}
					if(((scanInput & SCANKEY_7_2 ) == 0x02) && (pressTypeRow == 0x4))//FAV+ PLAN
					{
						count++;
					if((count % 2) != 0 )
					       {
						        Display_Delay(5000);
							Write_com_lcd(0xC0);
							Display_Delay(5000);
							Goto_lcd(0x46);
							Display_Delay(5000);
							Write_string_lcd("FAV");
							Delay();
					       }
					       if((count % 2) == 0 )
					       {
						        Display_Delay(5000);
							Write_com_lcd(0xC0);
							Display_Delay(5000);
							Goto_lcd(0x46);
							Display_Delay(5000);
							Write_string_lcd("NOR");
							Delay();
					       }
					      
				}
				if(((scanInput & SCANKEY_7_3 ) == 0x01) && (pressTypeRow == 0x4))//MER BER
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
    
}
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
void calculate_tuner_value(unsigned int frequency) {
	
	unsigned short temp =(frequency + 36.125)/.0625;
	tunerdata[0] = temp >> 8;
	tunerdata[1] = (temp & 0xff);
	tunerdata[2] = 0x9b;
	tunerdata[4] = 0xC6;
	if(frequency > 47 &&  frequency < 125)
	{
		tunerdata[3] = 0xA8;
	}
	if(frequency > 125 &&  frequency < 366)
	{
		tunerdata[3] = 0xA8;
	}
	if(frequency > 366 &&  frequency < 622)
	{
		tunerdata[3] = 0x68;
	}
	if(frequency > 622 &&  frequency < 726)
	{
		tunerdata[3] = 0xA8;
	}
	if(frequency > 726 &&  frequency < 862)
	{
		tunerdata[3] = 0xE8;
	}
}
#if 0
void Keypad_SET(void)
{
	R_PORT_7_ScanLine_Output();
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
				if(((scanInput & SCANKEY_7_2 ) == 0x02) && (pressTypeRow == 0x10)) //SLOPE
				{
					 count3++;
					 if(count3 == 0x01)
					 {
					 Write_com_lcd(0xC0);
					 Display_Delay(5000);
					 //Goto_lcd(0x40);
					 Display_Delay(5000);
					 Write_string_lcd("032");
					 }
					 if(count3 == 0x02)
					 {
					 Write_com_lcd(0xC0);
					 Display_Delay(5000);
					 //Goto_lcd(0x40);
					 Display_Delay(5000);
					 Write_string_lcd("064");
					 }
					 if(count3 == 0x03)
					 {
					 Write_com_lcd(0xC0);
					 Display_Delay(5000);
					 //Goto_lcd(0x40);
					 Display_Delay(5000);
					 Write_string_lcd("128");
					 }
					 if(count3 == 0x04)
					 {
					 Write_com_lcd(0xC0);
					 Display_Delay(5000);
					 //Goto_lcd(0x40);
					 Display_Delay(5000);
					 Write_string_lcd("256");
					 }
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
				if(((scanInput & SCANKEY_7_2 ) == 0x02) && (pressTypeRow == 0x8)) //SET
				{  
					 
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
				if(((scanInput & SCANKEY_7_2 ) == 0x02) && (pressTypeRow == 0x4))//FAV+ PLAN
				{
					 SLOPE_Count ++;
					 if(SLOPE_Count == 0x1)
					 {
					 Write_com_lcd(0xC0);
					 Display_Delay(5000);
					 Goto_lcd(0x4e);
					 Display_Delay(5000);
					 Write_string_lcd("P2");
					 Delay();
					 }
					 if(SLOPE_Count == 0x2)
					 {
					 Write_com_lcd(0xC0);
					 Display_Delay(5000);
					 Goto_lcd(0x4e);
					 Display_Delay(5000);
					 Write_string_lcd("P3");
					 //Display_Delay(50000000);
					 Delay();
					 }
					 if(SLOPE_Count == 0x3)
					 {
					 Write_com_lcd(0xC0);
					 Display_Delay(5000);
					 Goto_lcd(0x4e);
					 Display_Delay(5000);
					 Write_string_lcd("P4");
					 Display_Delay(5000);
					 Delay();
					 }
					 if(SLOPE_Count == 0x4)
					 {
					 Write_com_lcd(0xC0);
					 Display_Delay(5000);
					 Goto_lcd(0x4e);
					 Display_Delay(5000);
					 Write_string_lcd("P5");
					 Display_Delay(5000);
					 Delay();
					 }
					 if(SLOPE_Count == 0x5)
					 {
					 Write_com_lcd(0xC0);
					 Display_Delay(5000);
					 Goto_lcd(0x4e);
					 Display_Delay(5000);
					 Write_string_lcd("P6");
					 Display_Delay(5000);
					 Delay();
					 }
					 if(SLOPE_Count == 0x6)
					 {
					 Write_com_lcd(0xC0);
					 Display_Delay(5000);
					 Goto_lcd(0x4e);
					 Display_Delay(5000);
					 Write_string_lcd("P7");
					 Display_Delay(5000);
					 Delay();
					 }
				}
				
				pressTypeRow = 0x00;
				R_PORT_7_ScanLine_Output();
				
				
			}
	      } 
	    	   
    }
    

}
#endif

/* End user code. Do not edit comment generated here */
