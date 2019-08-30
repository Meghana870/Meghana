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
#include "Si2165.h"
#include "Si2165_Priv.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
#define SIZE 200
void Lcd_display(void);
uint8_t count = 0;
uint8_t SLOPE_Count =0;
uint8_t count3 =0;
unsigned char tuner_data[6];
unsigned char tunerdata[6];
int frequency;

int8_t PLAN_Count = 0 ;
void calculate_tuner_value(unsigned int frequency);
char *PLAN_array[SIZE]={"P1","P2","P3","P4","P5","P6","P7"};

uint8_t CHANNEL_Count = 0;
char *CHANNEL_Number[SIZE] = {"S01","S02","S03","S04","S05","S06","S07","S08","S09","S10",
			      "E05","E06","E07","E08","E09","E10","E11","E12",
			      "S11","S12","S13","S14","S15","S16","S17","S18","S19","S20",
			      "S21","S22","S23","S24","S25","S26","S27","S28","S29","S30",
			      "S31","S32","S33","S34","S35","S36","S37","S38","S39","S40","S41",
			      "E21","E22","E23","E24","E25","E26","E27","E28","E29","E30",
			      "E31","E32","E33","E34","E35","E36","E37","E38","E39","E40",
			      "E41","E42","E43","E44","E45","E46","E47","E48","E49","E50",
			      "E51","E52","E53","E54","E55","E56","E57","E58","E59","E60",
			      "E61","E62","E63","E64","E65","E66","E67","E68","E69",
			      "E02","E03","E04","  X","  Y","  Z","Z+1","Z+2",
			      };

char *CHANNEL_Frequency[SIZE] = {"108.00","115.00","122.00","129.00","136.00","143.00","150.00","157.00","164.00","171.00",
			         "178.00","185.00","192.00","199.00","206.00","213.00","220.00","227.00",
				 "234.00","241.00","248.00","255.00","262.00","269.00","276.00","283.00","290.00","297.00",
				 "306.00","314.00","322.00","330.00","338.00","346.00","354.00","362.00","370.00","378.00",
				 "386.00","394.00","402.00","410.00","418.00","426.00","434.00","442.00","450.00","458.00","466.00",
			         "474.00","482.00","490.00","498.00","506.00","514.00","522.00","530.00","538.00","546.00",
				 "554.00","562.00","570.00","578.00","586.00","594.00","602.00","610.00","618.00","626.00",
			         "634.00","642.00","650.00","658.00","666.00","674.00","682.00","690.00","698.00","706.00",
				 "714.00","722.00","730.00","738.00","746.00","754.00","762.00","770.00","778.00","786.00",
				 "794.00","802.00","810.00","818.00","826.00","834.00","842.00","850.00","858.00",
				 " 51.00"," 58.00"," 65.00"," 72.00"," 79.00"," 86.00"," 93.00","100.00",
				};
 int CHANNEL_Frequency_Int[SIZE] = {108,115,122,129,136,143,150,157,164,171,
			         178,185,192,199,206,213,220,227,
				 234,241,248,255,262,269,276,283,290,297,
				 306,314,322,330,338,346,354,362,370,378,
				 386,394,402,410,418,426,434,442,450,458,466,
			         474,482,490,498,506,514,522,530,538,546,
				 554,562,570,578,586,594,602,610,618,626,
			         634,642,650,658,666,674,682,690,698,706,
				 714,722,730,738,746,754,762,770,778,786,
				 794,802,810,818,826,834,842,850,858,
				 51,58,65,72,79,86,93,100};

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
 
uint8_t gDemodState;

eeprom_paraA16   g_PARAI;                       /* EEPROM access parameter for interface */
uint8_t g_data_bufferW1[0x100];                 /* write data buffer area       */
uint8_t g_data_bufferW2[0x100];                 /* write data buffer area       */
uint8_t g_data_bufferR1[0x200];                 /* write data buffer area       */
uint8_t tuner_data1[] = {0x1F,0xE2,0x9B,0x68,0xC6};  
uint8_t tuner_data2[] = {0x20,0x62,0x9B,0x68,0xC6};  
uint8_t tuner_data3[] = {0x20,0xE2,0x9B,0x68,0xC6};  
uint8_t tuner_data4[] = {0x21,0x62,0x9B,0x68,0xC6};  
uint8_t tunerstatus = 0x00;
void R_IICr_Init(void);                         /* IICr initialize              */
MD_STATUS R_IICr_StopCond(void);                /* issue and wait for stop cond */
void R_EEPROM_W(eeprom_paraA16 *PARA);
MD_STATUS R_EEPROM_wait_write(void);            /* wait for write complete      */
void R_EEPROM_R(eeprom_paraA16 *PARA);
MD_STATUS R_EEPROM_wait_read(void);             /* wait for read complete       */

void I2C_Write_Demod(uint16_t regAddr, uint32_t data);
void I2C_Read_Demod(uint16_t regAddr, uint8_t data);
void I2C_Write_Tuner(uint8_t *data);
void I2C_Read_Tuner();
uint32_t GetTunerState();
uint32_t GetTunerData();
void R_IICr_SCL_Time(void);  
void Si2165_Device_init(void);
void si2165_read_status(void);
	
void dvb_frontend_ops(void);
void Si2165_Driver(void);


uint32_t ref_freq_hz;
uint8_t pll_divR;
uint8_t pll_divP;
uint8_t pll_divN;
uint8_t pll_divM;
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
    hdwinit();
    //Si2165_Driver();
    
    //#if 0
    PM14 = PM14 & 0xBF;
    P14 = P14 | 0x40;
    R_Wait(1000);
    P14 = P14 & 0xBF;
    //#endif
    
    Lcd_display();
    R_PORT_7_ScanLine_Output();
    
    Init_lcd(); // LCD Initialization
    Clear_lcd(); // Reset LCD and move to start position
    
    while(1)
    {       
	    if(((P12 & 0x1D) == 0x1D) &&(pressTypeRow == 0))
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
				//if(keyevent & KEYPRESS_12_1)
				//	pressTypeRow |=KEYPRESS_12_1;
				if(keyevent & KEYPRESS_12_2)
					pressTypeRow |=KEYPRESS_12_2;
				if(keyevent & KEYPRESS_12_3)
					pressTypeRow |=KEYPRESS_12_3;
					//P14 = P14 | 0x40;
				if(keyevent & KEYPRESS_12_4)
					pressTypeRow |=KEYPRESS_12_4;
				if(pressTypeRow !=0)
				R_PORT_7_ScanLine_Input();
				R_Wait(30);
				//P14 = P14 | 0x40;
    			}
			else
			{
					
		                scanInput = P7;
				if(((scanInput & SCANKEY_7_0) == 0x08 ) && (pressTypeRow == 0x1))
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
				if(((scanInput & SCANKEY_7_1 ) == 0x04) && (pressTypeRow == 0x1))
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
				
				if(((scanInput & SCANKEY_7_0 ) == 0x08) && (pressTypeRow == 0x8))//CH UP
				{
					
					// #if 0
					 //Write_com_lcd(0x01);
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
					  
					  //#endif
					
				}
				if(((scanInput & SCANKEY_7_1 ) == 0x04) && (pressTypeRow == 0x8))//CH DOWN
				{
					
					 //#if 0
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
					  //#endif
				}
				if(((scanInput & SCANKEY_7_2 ) == 0x02) && (pressTypeRow == 0x8))//SET
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
				if(((scanInput & SCANKEY_7_3 ) == 0x01) && (pressTypeRow == 0x4))
				{
					 Write_com_lcd(0x01);
    					 Display_Delay(50000);
    					 Clear_lcd();
    					 Write_string_lcd("MER BER");
				}
				
				pressTypeRow = 0x00;
				R_PORT_7_ScanLine_Output();
				 P14 = P14 & 0xBF;
			}
	       }
	    	   
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
	//Display_Delay(100);
	
	DATA_PORT   = (DATA_PORT   & 0xF0) | (c & 0x0F);
	enable_e();
	Display_Delay(50);
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
    
}
void enable_e() {
EN_PIN=1;
//Display_Delay(39);

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

/* End user code. Do not edit comment generated here */
