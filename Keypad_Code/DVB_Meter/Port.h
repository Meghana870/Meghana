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
* File Name    : r_cg_port.h
* Version      : CodeGenerator for RL78/G14 V1.01.01 [11 Oct 2011]
* Device(s)    : R5F104FF
* Tool-Chain   : CA78K0R
* Description  : This file implements device driver for PORT module.
* Creation Date: 7/1/2019
***********************************************************************************************************************/

#ifndef PORT_H
#define PORT_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/* Port Mode Register (PMm) */
/* Pmn pin I/O mode selection (PMm7 - PMm0) */
#define _01_PMn0_NOT_USE        (0x01U) /* not use Pn0 as digital I/O */
#define _01_PMn0_MODE_INPUT     (0x01U) /* use Pn0 as input mode */
#define _00_PMn0_MODE_OUTPUT    (0x00U) /* use Pn0 as output mode */
#define _02_PMn1_NOT_USE        (0x02U) /* not use Pn1 as digital I/O */
#define _02_PMn1_MODE_INPUT     (0x02U) /* use Pn1 as input mode */
#define _00_PMn1_MODE_OUTPUT    (0x00U) /* use Pn1 as output mode */
#define _04_PMn2_NOT_USE        (0x04U) /* not use Pn2 as digital I/O */
#define _04_PMn2_MODE_INPUT     (0x04U) /* use Pn2 as input mode */
#define _00_PMn2_MODE_OUTPUT    (0x00U) /* use Pn2 as output mode */
#define _08_PMn3_NOT_USE        (0x08U) /* not use Pn3 as digital I/O */
#define _08_PMn3_MODE_INPUT     (0x08U) /* use Pn3 as input mode */
#define _00_PMn3_MODE_OUTPUT    (0x00U) /* use Pn3 as output mode */
#define _10_PMn4_NOT_USE        (0x10U) /* not use Pn4 as digital I/O */
#define _10_PMn4_MODE_INPUT     (0x10U) /* use Pn4 as input mode */
#define _00_PMn4_MODE_OUTPUT    (0x00U) /* use Pn4 as output mode */
#define _20_PMn5_NOT_USE        (0x20U) /* not use Pn5 as digital I/O */
#define _20_PMn5_MODE_INPUT     (0x20U) /* use Pn5 as input mode */
#define _00_PMn5_MODE_OUTPUT    (0x00U) /* use Pn5 as output mode */
#define _40_PMn6_NOT_USE        (0x40U) /* not use Pn6 as digital I/O */
#define _40_PMn6_MODE_INPUT     (0x40U) /* use Pn6 as input mode */
#define _00_PMn6_MODE_OUTPUT    (0x00U) /* use Pn6 as output mode */
#define _80_PMn7_NOT_USE        (0x80U) /* not use Pn7 as digital I/O */
#define _80_PMn7_MODE_INPUT     (0x80U) /* use Pn7 as input mode */
#define _00_PMn7_MODE_OUTPUT    (0x00U) /* use Pn7 as output mode */

/* Port Register (Pm) */
/* Pmn pin data (Pm0 to Pm7) */
#define _00_Pn0_OUTPUT_0        (0x00U) /* Pn0 output 0 */
#define _01_Pn0_OUTPUT_1        (0x01U) /* Pn0 output 1 */
#define _00_Pn1_OUTPUT_0        (0x00U) /* Pn1 output 0 */
#define _02_Pn1_OUTPUT_1        (0x02U) /* Pn1 output 1 */
#define _00_Pn2_OUTPUT_0        (0x00U) /* Pn2 output 0 */
#define _04_Pn2_OUTPUT_1        (0x04U) /* Pn2 output 1 */
#define _00_Pn3_OUTPUT_0        (0x00U) /* Pn3 output 0 */
#define _08_Pn3_OUTPUT_1        (0x08U) /* Pn3 output 1 */
#define _00_Pn4_OUTPUT_0        (0x00U) /* Pn4 output 0 */
#define _10_Pn4_OUTPUT_1        (0x10U) /* Pn4 output 1 */
#define _00_Pn5_OUTPUT_0        (0x00U) /* Pn5 output 0 */
#define _20_Pn5_OUTPUT_1        (0x20U) /* Pn5 output 1 */
#define _00_Pn6_OUTPUT_0        (0x00U) /* Pn6 output 0 */
#define _40_Pn6_OUTPUT_1        (0x40U) /* Pn6 output 1 */
#define _00_Pn7_OUTPUT_0        (0x00U) /* Pn7 output 0 */
#define _80_Pn7_OUTPUT_1        (0x80U) /* Pn7 output 1 */

/* Pull-up Resistor Option Register (PUm) */
/* Pmn pin on-chip pull-up resistor selection (PUmn) */
#define _00_PUn0_PULLUP_OFF     (0x00U) /* Pn0 pull-up resistor not connected */
#define _01_PUn0_PULLUP_ON      (0x01U) /* Pn0 pull-up resistor connected */
#define _00_PUn1_PULLUP_OFF     (0x00U) /* Pn1 pull-up resistor not connected */
#define _02_PUn1_PULLUP_ON      (0x02U) /* Pn1 pull-up resistor connected */
#define _00_PUn2_PULLUP_OFF     (0x00U) /* Pn2 Pull-up resistor not connected */
#define _04_PUn2_PULLUP_ON      (0x04U) /* Pn2 pull-up resistor connected */
#define _00_PUn3_PULLUP_OFF     (0x00U) /* Pn3 pull-up resistor not connected */
#define _08_PUn3_PULLUP_ON      (0x08U) /* Pn3 pull-up resistor connected */
#define _00_PUn4_PULLUP_OFF     (0x00U) /* Pn4 pull-up resistor not connected */
#define _10_PUn4_PULLUP_ON      (0x10U) /* Pn4 pull-up resistor connected */
#define _00_PUn5_PULLUP_OFF     (0x00U) /* Pn5 pull-up resistor not connected */
#define _20_PUn5_PULLUP_ON      (0x20U) /* Pn5 pull-up resistor connected */
#define _00_PUn6_PULLUP_OFF     (0x00U) /* Pn6 pull-up resistor not connected */
#define _40_PUn6_PULLUP_ON      (0x40U) /* Pn6 pull-up resistor connected */
#define _00_PUn7_PULLUP_OFF     (0x00U) /* Pn7 pull-up resistor not connected */
#define _80_PUn7_PULLUP_ON      (0x80U) /* Pn7 pull-up resistor connected */

/* Port Input Mode Register (PIMm) */
/* Pmn pin input buffer selection (PIMmn) */
#define _00_PIMn0_TTL_OFF       (0x00U) /* set Pn0 normal input buffer */
#define _01_PIMn0_TTL_ON        (0x01U) /* set Pn0 TTL input buffer */
#define _00_PIMn1_TTL_OFF       (0x00U) /* set Pn1 normal input buffer */
#define _02_PIMn1_TTL_ON        (0x02U) /* set Pn1 TTL input buffer */
#define _00_PIMn2_TTL_OFF       (0x00U) /* set Pn2 normal input buffer */
#define _04_PIMn2_TTL_ON        (0x04U) /* set Pn2 TTL input buffer */
#define _00_PIMn3_TTL_OFF       (0x00U) /* set Pn3 normal input buffer */
#define _08_PIMn3_TTL_ON        (0x08U) /* set Pn3 TTL input buffer */
#define _00_PIMn4_TTL_OFF       (0x00U) /* set Pn4 normal input buffer */
#define _10_PIMn4_TTL_ON        (0x10U) /* set Pn4 TTL input buffer */
#define _00_PIMn5_TTL_OFF       (0x00U) /* set Pn5 normal input buffer */
#define _20_PIMn5_TTL_ON        (0x20U) /* set Pn5 TTL input buffer */
#define _00_PIMn6_TTL_OFF       (0x00U) /* set Pn6 normal input buffer */
#define _40_PIMn6_TTL_ON        (0x40U) /* set Pn6 TTL input buffer */
#define _00_PIMn7_TTL_OFF       (0x00U) /* set Pn7 normal input buffer */
#define _80_PIMn7_TTL_ON        (0x80U) /* set Pn7 TTL input buffer */

/* Port Output Mode Register (POMm) */
/* Pmn pin output mode selection (POMmn) */
#define _00_POMn0_NCH_OFF       (0x00U) /* set Pn0 output normal mode */
#define _01_POMn0_NCH_ON        (0x01U) /* set Pn0 output N-ch open-drain mode */
#define _00_POMn1_NCH_OFF       (0x00U) /* set Pn1 output normal mode */
#define _02_POMn1_NCH_ON        (0x02U) /* set Pn1 output N-ch open-drain mode */
#define _00_POMn2_NCH_OFF       (0x00U) /* set Pn2 output normal mode */
#define _04_POMn2_NCH_ON        (0x04U) /* set Pn2 output N-ch open-drain mode */
#define _00_POMn3_NCH_OFF       (0x00U) /* set Pn3 output normal mode */
#define _08_POMn3_NCH_ON        (0x08U) /* set Pn3 output N-ch open-drain mode */
#define _00_POMn4_NCH_OFF       (0x00U) /* set Pn4 output normal mode */
#define _10_POMn4_NCH_ON        (0x10U) /* set Pn4 output N-ch open-drain mode */
#define _00_POMn5_NCH_OFF       (0x00U) /* set Pn5 output normal mode */
#define _20_POMn5_NCH_ON        (0x20U) /* set Pn5 output N-ch open-drain mode */
#define _00_POMn6_NCH_OFF       (0x00U) /* set Pn6 output normal mode */
#define _40_POMn6_NCH_ON        (0x40U) /* set Pn6 output N-ch open-drain mode */
#define _00_POMn7_NCH_OFF       (0x00U) /* set Pn7 output normal mode */
#define _80_POMn7_NCH_ON        (0x80U) /* set Pn7 output N-ch open-drain mode */

/* Port Operation Mode Register (PMCm) */
/* Pmn pin digital input buffer selection (PMCmn) */
#define _01_PMCn0_NOT_USE       (0x01U) /* not use Pn0 digital input */
#define _00_PMCn0_DI_ON         (0x00U) /* enable Pn0 digital input */
#define _02_PMCn1_NOT_USE       (0x02U) /* not use Pn1 digital input */
#define _00_PMCn1_DI_ON         (0x00U) /* enable Pn1 digital input */
#define _04_PMCn2_NOT_USE       (0x04U) /* not use Pn2 digital input */
#define _00_PMCn2_DI_ON         (0x00U) /* enable Pn2 digital input */
#define _08_PMCn3_NOT_USE       (0x08U) /* not use Pn3 digital input */
#define _00_PMCn3_DI_ON         (0x00U) /* enable Pn3 digital input */
#define _10_PMCn4_NOT_USE       (0x10U) /* not use Pn4 digital input */
#define _00_PMCn4_DI_ON         (0x00U) /* enable Pn4 digital input */
#define _20_PMCn5_NOT_USE       (0x20U) /* not use Pn5 digital input */
#define _00_PMCn5_DI_ON         (0x00U) /* enable Pn5 digital input */
#define _40_PMCn6_NOT_USE       (0x40U) /* not use Pn6 digital input */
#define _00_PMCn6_DI_ON         (0x00U) /* enable Pn6 digital input */
#define _80_PMCn7_NOT_USE       (0x80U) /* not use Pn7 digital input */
#define _00_PMCn7_DI_ON         (0x00U) /* enable Pn7 digital input */

/* AD port configuration register (ADPC) */
/* Analog input/digital input switching (ADPC3 - ADPC0) */
#define _00_ADPC_DI_OFF         (0x00U) /* use P20 - P27 as analog input */
#define _08_ADPC_DI_ON          (0x08U) /* use P27 as digital input */
#define _07_ADPC_DI_ON          (0x07U) /* use P26 - P27 as digital input */
#define _06_ADPC_DI_ON          (0x06U) /* use P25 - P27 as digital input */
#define _05_ADPC_DI_ON          (0x05U) /* use P24 - P27 as digital input */
#define _04_ADPC_DI_ON          (0x04U) /* use P23 - P27 as digital input */
#define _03_ADPC_DI_ON          (0x03U) /* use P22 - P27 as digital input */
#define _02_ADPC_DI_ON          (0x02U) /* use P21 - P27 as digital input */
#define _01_ADPC_DI_ON          (0x01U) /* use P20 - P27 as digital input */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _FC_PM0_DEFAULT         (0xFCU) /* PM0 default value */
#define _FC_PM3_DEFAULT         (0xFCU) /* PM3 default value */
#define _FC_PM4_DEFAULT         (0xFCU) /* PM4 default value */
#define _FC_PM5_DEFAULT         (0xFCU) /* PM5 default value */
#define _F0_PM6_DEFAULT         (0xF0U) /* PM6 default value */
#define _F0_PM7_DEFAULT         (0xF0U) /* PM7 default value */
#define _FE_PM12_DEFAULT        (0xFEU) /* PM12 default value */
#define _3F_PM14_DEFAULT        (0x3FU) /* PM14 default value */
#define _FE_PMC12_DEFAULT       (0xFEU) /* PMC12 default value */
#define _7F_PMC14_DEFAULT       (0x7FU) /* PMC14 default value */
#define _0F_PM7_DEFAULT         (0x0FU)

/* Start user code for function. Do not edit comment generated here */
#define SIZE 200

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
void calculate_tuner_value(unsigned int frequency);

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

uint8_t count = 0;
uint8_t SLOPE_Count =0;
uint8_t count3 =0;

unsigned char tunerdata[6];
int frequency;

uint8_t PLAN_Count = 0 ;
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
			         "178.00","185.00","192.00","199.00","206.00","213.00","220.00","227.00"
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

void R_PORT_ScanData_Low(void);
void R_PORT_ScanData_High(void);
void R_PORT_ScanLine_Input(void);
void R_PORT_ScanLine_Output(void);
void R_PORT_ScanLine_SetScan(uint8_t scanline);

void R_PORT_7_ScanLine_Output(void);
void R_PORT_7_ScanLine_Input(void);

/* End user code. Do not edit comment generated here */
#endif
