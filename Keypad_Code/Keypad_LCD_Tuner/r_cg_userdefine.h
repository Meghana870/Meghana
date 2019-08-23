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
* File Name    : r_cg_userdefine.h
* Version      : CodeGenerator for RL78/G14 V1.01.01 [11 Oct 2011]
* Device(s)    : R5F104FF
* Tool-Chain   : CA78K0R
* Description  : This file includes user definition.
* Creation Date: 7/29/2019
***********************************************************************************************************************/

#ifndef _USER_DEF_H
#define _USER_DEF_H

/***********************************************************************************************************************
User definitions
***********************************************************************************************************************/

/* Start user code for function. Do not edit comment generated here */

#define PAGE_16     (0x0FU)                 /* page size is 16bytes */
#define PAGE_32     (0x1FU)                 /* page size is 32bytes */
#define PAGE_64     (0x3FU)                 /* page size is 64bytes */
#define PAGE_128    (0x7FU)                 /* page size is 128bytes */
#define PAGE_256    (0xFFU)                 /* page size is 256bytes */

#define MEMORY_2K   (0x1U)                  /* 2Kbits:256bytes */
#define MEMORY_4K   (0x2U)                  /* 4Kbits:512bytes */
#define MEMORY_8K   (0x4U)                  /* 8Kbits:1Kbytes */
#define MEMORY_16K  (0x8U)                  /* 16Kbits:2Kbytes */
#define MEMORY_32K  (0x10U)                 /* 32Kbits:4Kbytes */
#define MEMORY_64K  (0x20U)                 /* 64Kbits:8Kbytes */
#define MEMORY_128K (0x40U)                 /* 128Kbits:16Kbytes */
#define MEMORY_256K (0x80U)                 /* 256Kbits:32Kbytes */
#define MEMORY_512K (0x100U)                /* 512Kbits:64Kbytes */
/*#define MEMORY_1M (0x200U)                1Mbits:128Kbytes */

#define ADDR0BIT    (0b00000000)            /* slave address is not used as cell address */
#define ADDR1BIT    (0b00000001)            /* slave address include MSB of cell address */
#define ADDR2BIT    (0b00000011)            /* slave address include MSB 2bits of cell address */
#define ADDR3BIT    (0b00000111)            /* slave address include MSB 3bits of cell address */
#define ADDR4BIT    (0b00001111)            /* mask MSB 4bits of cell address */
#define ADDR5BIT    (0b00011111)            /* mask MSB 3bits of cell address */
#define ADDR6BIT    (0b00111111)            /* mask MSB 2bits of cell address */
#define ADDR7BIT    (0b01111111)            /* mask MSB of cell address */
#define ADDR8BIT    (0b11111111)            /* not mask cell address */


#define I2C_OK      (0x00U)                 /* complete operation   */
#define PARA_ERR    (0x20U)                 /* parameter error      */
#define NO_ACK1     (0x40U)                 /* slave error          */
#define NO_ACK2     (0x41U)                 /* EEPROM address error */
#define NO_ACK3     (0x42U)                 /* slave data error     */
#define BUS_ERR     (0x60U)                 /* I2C bus error        */

#define TRANSMIT    (0x80U)                 /* 0x80 transmit slave addr.    */
#define TxHiADDR    (TRANSMIT + 1U)         /* 0x81 transmit high addr.     */
#define TxLoADDR    (TRANSMIT + 2U)         /* 0x82 transmit Low addr.      */
#define TxData      (TRANSMIT + 0x20U)      /* 0xA0 transmit data           */
#define AFT_TX      (TxData + 1U)           /* 0xA1 data warite wait time   */
#define RECEIVE     (TRANSMIT + 0x40U)      /* 0xC0 transmit slave addr.    */
#define RxHiADDR    (RECEIVE + 1U)          /* 0xC1 transmit high addr.     */
#define RxLoADDR    (RECEIVE + 2U)          /* 0xC2 transmit Low addr.      */
#define ReStart     (RECEIVE + 3U)          /* 0xC3 transmit slave addr.    */
#define RxData      (RECEIVE + 0x20U)       /* 0xE0 receive mode (not last) */
#define RxLast      (RxData + 1U)           /* 0xE1 receive mode (last data)*/
#define TRNSEND     (0x00U)                 /* 0x00 transfer complete       */

#define SVAMSK      (0b11111110)            /* mask R/W bit of slave addr   */
#define TUNER_ADDR 0xC2
#define TUNER_ADDR1 0xC3
#define DEMOD_ADDR 0xC8
#define DEMOD 0x1
#define TUNER 0x2
//DEMOD States
#define DemodIdle 0x20
#define DemodAddrW 0x21
#define DemodAddrWH 0x22
#define DemodAddrWL 0x23
#define DemodDataW  0x24
#define DemodAddrR  0x25
#define DemodAddrRH 0x26
#define DemodAddrRL 0x27 
#define DemodRRead 0x28
#define DemodRReadData 0x29

//Tuner States
#define TunerIdle 0x30
#define TunerDataW 0x31
#define TunerAddrR 0x32
#define TunerWRestart 0x33
#define TunerReadData 0x34

typedef enum {                              /* EEPROM list */
    R1EX24002A      = 0x00U,                /* 2Kbits EEPROM 16bytes/page   */
    R1EX24004A,                             /* 4Kbits EEPROM 16bytes/page   */
    R1EX24008A,                             /* 8Kbits EEPROM 16bytes/page   */
    R1EX24016A,                             /* 16Kbits EEPROM 16bytes/page  */
    R1EX24032A,                             /* 32Kbits EEPROM 32bytes/page  */
    R1EX24064A,                             /* 64Kbits EEPROM 32bytes/page  */
    R1EX24128B,                             /* 128Kbits EEPROM 64bytes/page */
    R1EX24256B,                             /* 256Kbits EEPROM 64bytes/page */
    R1EX24512B,                             /* 512Kbits EEPROM 128bytes/page */
    EEPROM_MAX,                             /* Device end */
    HN58W241000I                            /* 1Mbits EEPROM 256bytes/page  */
} eeprom_name;

/* This structure is use to pass the parameter for EEPROM read/warite function */
typedef struct {                            /* EEPROM access parameter      */
    uint8_t slaveaddr;                      /* I2C bus slave device address */
    uint16_t eepromaddr;                    /* EEPROM cell address to access */
    uint8_t *bufferaddr;                    /* data buffer address          */
    uint16_t number;                        /* data number to access        */
} eeprom_paraA16;

/* This structure define EEPROM specification */
typedef struct {                            /* EEPROM address information   */
    uint16_t page_size;                     /* page size:mask data          */
    uint16_t rom_size;                      /* EEPROM memory size(256bytes unit) */
    uint8_t  addr_mask;                     /* mask data for I2C slave address */
    uint8_t  mask2;                         /* mask for EEPROM cell address */
} eeprom_info;



#define EEPROM_BASE (0xA0U)                 /* slave EEPROM addr base */

/* I2C bus control parameters*/
#define SCLLOWW     (0x05U)                 /* Low level width */
#define SCLHIGHW    (0x02U)                 /* high level width */
#define RETRYCNT    (9U)                    /* max SCL pulse number */

/* define use I2C channel here */

#define IIC11 (1)

#if IIC00
#define SAUmEN      SAU0EN                  /* Peripheral enable register */
#define SPSm        SPS0                    /* Serial clock select register */
#define SMRmn       SMR00                   /* Serial mode register */
#define SCRmn       SCR00                   /* Serial communication operation setting register */
#define SDRmn       SDR00                   /* Serial data register */
#define SIOr        SIO00                   /* Serial data register(lowwer 8 bit) */
#define SSRmn       SSR00                   /* Serial status register */
#define SIRmn       SIR00                   /* Serial flag clear trigger register */
#define SSmL        SS0L                    /* Serial channel start register */
#define STmL        ST0L                    /* Serial channel stop register */
#define TRGONn      (0b00000001)            /* for trigger SS00/ST00 */
#define SOEmL       SOE0L                   /* Serial output enable register */
#define SOEON       (TRGONn)                /* for turn on SOE00 */
#define SOEOFF      (uint8_t)(~SOEON)       /* for turn off SOE00 */
#define SOm         SO0                     /* Serial output register */
#define SDAHIGH     (TRGONn)                /* for rise SDA up */
#define SDALOW      (~SDAHIGH)              /* for fall SDA down */
#define SCLHIGH     (TRGONn * 0x100U)       /* for rise SCL up */
#define SCLLOW      (~SCLHIGH)              /* for fall SCL down */
#define SCLSDAHIGH  (SCLHIGH | SDAHIGH)     /* for rise SDA and SCL up */
#define PM_IICr     PM1                     /* port mode register for IICr */
#define PM_SDAr     PM1_bit.no1             /* port mode register bit for SDA */
#define PM_SCLr     PM1_bit.no0             /* port mode register bit for SCL */
#define POM_IICr    POM1                    /* Port output mode registe */
#define P_IICr      P1                      /* port register for IICr */
#define P_SDAr      P1_bit.no1              /* port register for SDA */
#define P_SCLr      P1_bit.no0              /* port register for SCL */
#define SDAINMODE   (0b00000010)            /* for set PM for SDA to input */
#define SDAOUTMODE  (0b11111100)            /* for clear PM to output */
#define SDASCLON    (uint8_t)(~SDAOUTMODE)  /* set SCL and SDA */
#define IICIFr      IICIF00                 /* interrupt request flag   */
#define IICMKr      IICMK00                 /* interrupt mask register  */
#define IICPR0r     IICPR000                /* interrupt priority flag  */
#define IICPR1r     IICPR100                /* interrupt priority flag  */
#endif

#if (PINNO > 44U)
#if IIC01
#define SAUmEN      SAU0EN                  /* Peripheral enable register */
#define SPSm        SPS0                    /* Serial clock select register */
#define SMRmn       SMR01                   /* Serial mode register */
#define SCRmn       SCR01                   /* Serial communication operation setting register */
#define SDRmn       SDR01                   /* Serial data register */
#define SIOr        SIO01                   /* Serial data register(lowwer 8 bit) */
#define SSRmn       SSR01                   /* Serial status register */
#define SIRmn       SIR01                   /* Serial flag clear trigger register */
#define SSmL        SS0L                    /* Serial channel start register */
#define STmL        ST0L                    /* Serial channel stop register */
#define TRGONn      (0b00000010)            /* for trigger SS01/ST01 */
#define SOEmL       SOE0L                   /* Serial output enable register */
#define SOEON       (TRGONn)                /* for turn on SOE01 */
#define SOEOFF      (uint8_t)(~SOEON)       /* for turn off SOE01 */
#define SOm         SO0                     /* Serial output register */
#define SDAHIGH     (TRGONn)                /* for rise SDA up */
#define SDALOW      (~SDAHIGH)              /* for fall SDA down */
#define SCLHIGH     (TRGONn * 0x100U)       /* for rise SCL up */
#define SCLLOW      (~SCLHIGH)              /* for fall SCL down */
#define SCLSDAHIGH  (SCLHIGH | SDAHIGH)     /* for rise SDA and SCL up */
#if (PINNO > 64U)
#define PM_IICr     PM4                     /* port mode register for IICr */
#define PM_SDAr     PM4_bit.no4             /* port mode register bit for SDA */
#define PM_SCLr     PM4_bit.no3             /* port mode register bit for SCL */
#define POM_IICr    POM4                    /* Port output mode registe */
#define P_IICr      P4                      /* port register for IICr */
#define P_SDAr      P4_bit.no4              /* port register for SDA */
#define P_SCLr      P4_bit.no3              /* port register for SCL */
#else
#define PM_IICr     PM7                     /* port mode register for IICr */
#define PM_SDAr     PM7_bit.no4             /* port mode register bit for SDA */
#define PM_SCLr     PM7_bit.no5             /* port mode register bit for SCL */
#define POM_IICr    POM7                    /* Port output mode registe */
#define P_IICr      P7                      /* port register for IICr */
#define P_SDAr      P7_bit.no4              /* port register for SDA */
#define P_SCLr      P7_bit.no5              /* port register for SCL */
#endif
#define SDAINMODE   (0b00010000)            /* for set PM for SDA to input */
#define SDAOUTMODE  (0b11100111)            /* for clear PM to output */
#define SDASCLON    (uint8_t)(~SDAOUTMODE)  /* set SCL and SDA */
#define IICIFr      IICIF01                 /* interrupt request flag   */
#define IICMKr      IICMK01                 /* interrupt mask register  */
#define IICPR0r     IICPR001                /* interrupt priority flag  */
#define IICPR1r     IICPR101                /* interrupt priority flag  */
#endif
#endif

#if (PINNO > 52U)
#if IIC10
#define SAUmEN      SAU0EN                  /* Peripheral enable register */
#define SPSm        SPS0                    /* Serial clock select register */
#define SMRmn       SMR02                   /* Serial mode register */
#define SCRmn       SCR02                   /* Serial communication operation setting register */
#define SDRmn       SDR02                   /* Serial data register */
#define SIOr        SIO10                   /* Serial data register(lowwer 8 bit) */
#define SSRmn       SSR02                   /* Serial status register */
#define SIRmn       SIR02                   /* Serial flag clear trigger register */
#define SSmL        SS0L                    /* Serial channel start register */
#define STmL        ST0L                    /* Serial channel stop register */
#define TRGONn      (0b00000100)            /* for trigger SS02/ST02 */
#define SOEmL       SOE0L                   /* Serial output enable register */
#define SOEON       (TRGONn)                /* for turn on SOE02 */
#define SOEOFF      (uint8_t)(~SOEON)       /* for turn off SOE02 */
#define SOm         SO0                     /* Serial output register */
#define SDAHIGH     (TRGONn)                /* for rise SDA up */
#define SDALOW      (~SDAHIGH)              /* for fall SDA down */
#define SCLHIGH     (TRGONn * 0x100U)       /* for rise SCL up */
#define SCLLOW      (~SCLHIGH)              /* for fall SCL down */
#define SCLSDAHIGH  (SCLHIGH | SDAHIGH)     /* for rise SDA and SCL up */
#define PM_IICr     PM0                     /* port mode register for IICr */
#define PM_SDAr     PM0_bit.no3             /* port mode register bit for SDA */
#define PM_SCLr     PM0_bit.no4             /* port mode register bit for SCL */
#define POM_IICr    POM0                    /* Port output mode registe */
#define P_IICr      P0                      /* port register for IICr */
#define P_SDAr      P0_bit.no3              /* port register for SDA */
#define P_SCLr      P0_bit.no4              /* port register for SCL */
#define SDAINMODE   (0b00001000)            /* for set PM for SDA to input */
#define SDAOUTMODE  (0b11100111)            /* for clear PM to output */
#define SDASCLON    (uint8_t)(~SDAOUTMODE)  /* set SCL and SDA */
#define IICIFr      IICIF10                 /* interrupt request flag   */
#define IICMKr      IICMK10                 /* interrupt mask register  */
#define IICPR0r     IICPR010                /* interrupt priority flag  */
#define IICPR1r     IICPR110                /* interrupt priority flag  */
#endif
#endif

#if IIC11
#define SAUmEN      SAU0EN                  /* Peripheral enable register */
#define SPSm        SPS0                    /* Serial clock select register */
#define SMRmn       SMR03                   /* Serial mode register */
#define SCRmn       SCR03                   /* Serial communication operation setting register */
#define SDRmn       SDR03                   /* Serial data register */
#define SIOr        SIO11                   /* Serial data register(lowwer 8 bit) */
#define SSRmn       SSR03                   /* Serial status register */
#define SIRmn       SIR03                   /* Serial flag clear trigger register */
#define SSmL        SS0L                    /* Serial channel start register */
#define STmL        ST0L                    /* Serial channel stop register */
#define TRGONn      (0b00001000)            /* for trigger SS03/ST03 */
#define SOEmL       SOE0L                   /* Serial output enable register */
#define SOEON       (TRGONn)                /* for turn on SOE03 */
#define SOEOFF      (uint8_t)(~SOEON)       /* for turn off SOE03 */
#define SOm         SO0                     /* Serial output register */
#define SDAHIGH     (TRGONn)                /* for rise SDA up */
#define SDALOW      (~SDAHIGH)              /* for fall SDA down */
#define SCLHIGH     (TRGONn * 0x100U)       /* for rise SCL up */
#define SCLLOW      (~SCLHIGH)              /* for fall SCL down */
#define SCLSDAHIGH  (SCLHIGH | SDAHIGH)     /* for rise SDA and SCL up */
#if (PINNO == 20U)
#define PM_IICr     PM1                     /* port mode register for IICr */
#define PM_SDAr     PM1_bit.no7             /* port mode register bit for SDA */
#define POM_IICr    POM1                    /* Port output mode registe */
#define P_SDAr      P1_bit.no7              /* port register for SDA */
#define SDAINMODE   (0b10000000)            /* for set PM for SDA to input */
#define SDAOUTMODE  (0b01111111)            /* for clear PM to output */
#else
#define PM_IICr     PM1                     /* port mode register for IICr */
#define PM_SDAr     PM1_bit.no1             /* port mode register bit for SDA */
#define POM_IICr    POM1                    /* Port output mode registe */ /*Varun Change */
#define P_SDAr      P1_bit.no1              /* port register for SDA */ /*Varun Change*/
#define SDAINMODE   (0b00000010)            /* for set PM for SDA to input */ /*Varun Change */
#define SDAOUTMODE  (0b11111101)            /* for clear PM to output */ /*Varun Change */
#endif
#define PM_SCLr     PM1_bit.no0             /* port mode register bit for SCL */
#define P_IICr      P3                      /* port register for IICr */
#define P_SCLr      P1_bit.no0              /* port register for SCL *//*Varun Change */
#define SDASCLON    (uint8_t)(~SDAOUTMODE)  /* set SCL and SDA */
#define IICIFr      IICIF11                 /* interrupt request flag   */
#define IICMKr      IICMK11                 /* interrupt mask register  */
#define IICPR0r     IICPR011                /* interrupt priority flag  */
#define IICPR1r     IICPR111                /* interrupt priority flag  */
#endif

#if (PINNO > 25U)
#if IIC20
#define SAUmEN      SAU1EN                  /* Peripheral enable register */
#define SPSm        SPS1                    /* Serial clock select register */
#define SMRmn       SMR10                   /* Serial mode register */
#define SCRmn       SCR10                   /* Serial communication operation setting register */
#define SDRmn       SDR10                   /* Serial data register */
#define SIOr        SIO20                   /* Serial data register(lowwer 8 bit) */
#define SSRmn       SSR10                   /* Serial status register */
#define SIRmn       SIR10                   /* Serial flag clear trigger register */
#define SSmL        SS1L                    /* Serial channel start register */
#define STmL        ST1L                    /* Serial channel stop register */
#define TRGONn      (0b00000001)            /* for trigger SS10/ST10 */
#define SOEmL       SOE1L                   /* Serial output enable register */
#define SOEON       (TRGONn)                /* for turn on SOE10 */
#define SOEOFF      (uint8_t)(~SOEON)       /* for turn off SOE10 */
#define SOm         SO1                     /* Serial output register */
#define SDAHIGH     (TRGONn)                /* for rise SDA up */
#define SDALOW      (~SDAHIGH)              /* for fall SDA down */
#define SCLHIGH     (TRGONn * 0x100U)       /* for rise SCL up */
#define SCLLOW      (~SCLHIGH)              /* for fall SCL down */
#define SCLSDAHIGH  (SCLHIGH | SDAHIGH)     /* for rise SDA and SCL up */
#define PM_IICr     PM1                     /* port mode register for IICr */
#define PM_SDAr     PM1_bit.no4             /* port mode register bit for SDA */
#define PM_SCLr     PM1_bit.no5             /* port mode register bit for SCL */
#define POM_IICr    POM1                    /* Port output mode registe */
#define P_IICr      P1                      /* port register for IICr */
#define P_SDAr      P1_bit.no4              /* port register for SDA */
#define P_SCLr      P1_bit.no5              /* port register for SCL */
#define SDAINMODE   (0b00010000)            /* for set PM for SDA to input */
#define SDAOUTMODE  (0b11001111)            /* for clear PM to output */
#define SDASCLON    (uint8_t)(~SDAOUTMODE)  /* set SCL and SDA */
#define IICIFr      IICIF20                 /* interrupt request flag   */
#define IICMKr      IICMK20                 /* interrupt mask register  */
#define IICPR0r     IICPR020                /* interrupt priority flag  */
#define IICPR1r     IICPR120                /* interrupt priority flag  */
#endif
#endif

#if (PINNO >30U)
#if IIC21
#define SAUmEN      SAU1EN                  /* Peripheral enable register */
#define SPSm        SPS1                    /* Serial clock select register */
#define SMRmn       SMR11                   /* Serial mode register */
#define SCRmn       SCR11                   /* Serial communication operation setting register */
#define SDRmn       SDR11                   /* Serial data register */
#define SIOr        SIO21                   /* Serial data register(lowwer 8 bit) */
#define SSRmn       SSR11                   /* Serial status register */
#define SIRmn       SIR11                   /* Serial flag clear trigger register */
#define SSmL        SS1L                    /* Serial channel start register */
#define STmL        ST1L                    /* Serial channel stop register */
#define TRGONn      (0b00000010)            /* for trigger SS11/ST11 */
#define SOEmL       SOE1L                   /* Serial output enable register */
#define SOEON       (TRGONn)                /* for turn on SOE11 */
#define SOEOFF      (uint8_t)(~SOEON)       /* for turn off SOE11 */
#define SOm         SO1                     /* Serial output register */
#define SDAHIGH     (TRGONn)                /* for rise SDA up */
#define SDALOW      (~SDAHIGH)              /* for fall SDA down */
#define SCLHIGH     (TRGONn * 0x100U)       /* for rise SCL up */
#define SCLLOW      (~SCLHIGH)              /* for fall SCL down */
#define SCLSDAHIGH  (SCLHIGH | SDAHIGH)     /* for rise SDA and SCL up */
#define PM_IICr     PM7                     /* port mode register for IICr */
#define PM_SDAr     PM7_bit.no1             /* port mode register bit for SDA */
#define PM_SCLr     PM7_bit.no0             /* port mode register bit for SCL */
#define POM_IICr    POM7                    /* Port output mode registe */
#define P_IICr      P7                      /* port register for IICr */
#define P_SDAr      P7_bit.no1              /* port register for SDA */
#define P_SCLr      P7_bit.no0              /* port register for SCL */
#define SDAINMODE   (0b00000010)            /* for set PM for SDA to input */
#define SDAOUTMODE  (0b11111100)            /* for clear PM to output */
#define SDASCLON    (uint8_t)(~SDAOUTMODE)  /* set SCL and SDA */
#define IICIFr      IICIF21                 /* interrupt request flag   */
#define IICMKr      IICMK21                 /* interrupt mask register  */
#define IICPR0r     IICPR021                /* interrupt priority flag  */
#define IICPR1r     IICPR121                /* interrupt priority flag  */
#endif
#endif

#if (PINNO > 64U)
#if IIC30
#define SAUmEN      SAU1EN                  /* Peripheral enable register */
#define SPSm        SPS1                    /* Serial clock select register */
#define SMRmn       SMR12                   /* Serial mode register */
#define SCRmn       SCR12                   /* Serial communication operation setting register */
#define SDRmn       SDR12                   /* Serial data register */
#define SIOr        SIO30                   /* Serial data register(lowwer 8 bit) */
#define SSRmn       SSR12                   /* Serial status register */
#define SIRmn       SIR12                   /* Serial flag clear trigger register */
#define SSmL        SS1L                    /* Serial channel start register */
#define STmL        ST1L                    /* Serial channel stop register */
#define TRGONn      (0b00000100)            /* for trigger SS12/ST12 */
#define SOEmL       SOE1L                   /* Serial output enable register */
#define SOEON       (TRGONn)                /* for turn on SOE12 */
#define SOEOFF      (uint8_t)(~SOEON)       /* for turn off SOE12 */
#define SOm         SO1                     /* Serial output register */
#define SDAHIGH     (TRGONn)                /* for rise SDA up */
#define SDALOW      (~SDAHIGH)              /* for fall SDA down */
#define SCLHIGH     (TRGONn * 0x100U)       /* for rise SCL up */
#define SCLLOW      (~SCLHIGH)              /* for fall SCL down */
#define SCLSDAHIGH  (SCLHIGH | SDAHIGH)     /* for rise SDA and SCL up */
#define PM_IICr     PM14                    /* port mode register for IICr */
#define PM_SDAr     PM14_bit.no3            /* port mode register bit for SDA */
#define PM_SCLr     PM14_bit.no2            /* port mode register bit for SCL */
#define POM_IICr    POM14                   /* Port output mode registe */
#define P_IICr      P14                     /* port register for IICr */
#define P_SDAr      P14_bit.no3             /* port register for SDA */
#define P_SCLr      P14_bit.no2             /* port register for SCL */
#define SDAINMODE   (0b00001000)            /* for set PM for SDA to input */
#define SDAOUTMODE  (0b11110011)            /* for clear PM to output */
#define SDASCLON    (uint8_t)(~SDAOUTMODE)  /* set SCL and SDA */
#define IICIFr      IICIF30                 /* interrupt request flag   */
#define IICMKr      IICMK30                 /* interrupt mask register  */
#define IICPR0r     IICPR030                /* interrupt priority flag  */
#define IICPR1r     IICPR130                /* interrupt priority flag  */
#endif

#if IIC31
#define SAUmEN      SAU1EN                  /* Peripheral enable register */
#define SPSm        SPS1                    /* Serial clock select register */
#define SMRmn       SMR13                   /* Serial mode register */
#define SCRmn       SCR13                   /* Serial communication operation setting register */
#define SDRmn       SDR13                   /* Serial data register */
#define SIOr        SIO31                   /* Serial data register(lowwer 8 bit) */
#define SSRmn       SSR13                   /* Serial status register */
#define SIRmn       SIR13                   /* Serial flag clear trigger register */
#define SSmL        SS1L                    /* Serial channel start register */
#define STmL        ST1L                    /* Serial channel stop register */
#define TRGONn      (0b00001000)            /* for trigger SS13/ST13 */
#define SOEmL       SOE1L                   /* Serial output enable register */
#define SOEON       (TRGONn)                /* for turn on SOE13 */
#define SOEOFF      (uint8_t)(~SOEON)       /* for turn off SOE13 */
#define SOm         SO1                     /* Serial output register */
#define SDAHIGH     (TRGONn)                /* for rise SDA up */
#define SDALOW      (~SDAHIGH)              /* for fall SDA down */
#define SCLHIGH     (TRGONn * 0x100U)       /* for rise SCL up */
#define SCLLOW      (~SCLHIGH)              /* for fall SCL down */
#define SCLSDAHIGH  (SCLHIGH | SDAHIGH)     /* for rise SDA and SCL up */
#define PM_IICr     PM5                     /* port mode register for IICr */
#define PM_SDAr     PM5_bit.no3             /* port mode register bit for SDA */
#define PM_SCLr     PM5_bit.no4             /* port mode register bit for SCL */
#define POM_IICr    POM5                    /* Port output mode registe */
#define P_IICr      P5                      /* port register for IICr */
#define P_SDAr      P5_bit.no3              /* port register for SDA */
#define P_SCLr      P5_bit.no4              /* port register for SCL */
#define SDAINMODE   (0b00001000)            /* for set PM for SDA to input */
#define SDAOUTMODE  (0b11100111)            /* for clear PM to output */
#define SDASCLON    (uint8_t)(~SDAOUTMODE)  /* set SCL and SDA */
#define IICIFr      IICIF31                 /* interrupt request flag   */
#define IICMKr      IICMK31                 /* interrupt mask register  */
#define IICPR0r     IICPR031                /* interrupt priority flag  */
#define IICPR1r     IICPR131                /* interrupt priority flag  */
#endif
#endif





/* End user code. Do not edit comment generated here */
#endif
