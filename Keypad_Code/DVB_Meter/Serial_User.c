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
* File Name    : r_cg_serial_user.c
* Version      : CodeGenerator for RL78/G14 V1.01.01 [11 Oct 2011]
* Device(s)    : R5F104FF
* Tool-Chain   : CA78K0R
* Description  : This file implements device driver for Serial module.
* Creation Date: 7/9/2019
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt INTIIC11 IINTIICr_New
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
/* Start user code for include. Do not edit comment generated here */
#include "Si2165_Priv.h"
#include "iodefine.h"
#include "Si2165.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/

/* Start user code for global. Do not edit comment generated here */



/* read/write parameter area */
static eeprom_paraA16   g_PARAA;                    /* EEPROM access parameter for access */
static eeprom_paraA16   g_PARAC;                    /* copy of EEPROM access parameter  */

static uint16_t	gDemodRegAddr;
static uint8_t	gDemodData;
static uint8_t	gContext;
static uint8_t gDemodState;
static uint8_t *gTunerData;
static uint8_t gTunerState ;
static uint8_t gTunerTXData=0;
static uint8_t gRTunerData;
extern uint8_t Patch_version=0x00;

/* target EEPROM Information  */
static eeprom_info EEPROM_Info;                     /* EEPROM parameter that is selected */

uint8_t g_comstatus;                                /* IIC communication status */
static uint8_t g_eeprom_type;                       /* Type select of EEPROM(eeprom_name) */


void R_IICr_Init(void);                             /* IIC00 initialize             */
MD_STATUS R_IICr_StopCond(void);                    /* issue and wait for stop cond */

MD_STATUS R_device_select(eeprom_name);             /* select target EEPROM */

void R_EEPROM_W(eeprom_paraA16 *PARA);
                                                    /* write function over page     */
MD_STATUS R_EEPROM_wait_write(void);                /* wait for write complete      */

void R_EEPROM_R(eeprom_paraA16 *PARA);
                                                    /* read function                */
MD_STATUS R_EEPROM_wait_read(void);                 /* wait for read complete       */

static void get_slave_Addr(void);                   /* get slave addr. from cell addr.*/
static void R_EEPROM_Devide(void);                  /* devied write data to page size */

static MD_STATUS check_EEPROM_Addr(eeprom_paraA16 *PARA);
                                                    /* check area is in EEPROM      */

static void R_IICr_Tx_addr1(void);                  /* wait for slave addr. transmit
                                                       and send EEPROM addres.      */
static void R_IICr_Tx_addr2(void);                  /* wait for EEPROM high addr. Tx
                                                       and send low addres.         */
static void R_IICr_Rx_RST(void);                    /* isuue reatsrt cond. for raed */

static void R_IICr_RxData_ST(void);                 /* start data receive           */
static void R_IICr_RxData(void);                    /* receive  data                */
static void R_IICr_Rx_LastData(void);               /* receive  last data and stop  */

static void R_IICr_TxDataST(void);                  /* start to transmit data       */
static void R_IICr_TxData(void);                    /* one byte data transmit end,
                                                       transmit next data if exist  */
static void R_EEPROM_next_page(void);               /* wait for EEPROM write complete */

static void R_IICr_StartCond(void);                 /* issue and wait for start cond */
static void R_IICr_send_Stop(void);                 /* issue Stop Condtion          */

static MD_STATUS R_IICr_wait_bus(void);             /* release bus by generating SCL*/
static void R_IICr_SCL_pulse(void);                 /* generate SCL pulse           */
static void R_IICr_SCL_high(void);                  /* rise up SCL                  */
static void R_IICr_SCL_low(void);                   /* fall SLC down                */
static MD_STATUS R_IICr_NACK(void);                 /* check ACK response           */
 void R_IICr_SCL_Time(void);                        /* wait for SCL low period      */
static void R_IICr_SCL_highTime(void);              /* wait for SCL high period     */

void Si2165_Driver(void);
void Si2165_Probe(void);
void dvb_frontend_ops(void);
void si2165_sleep(void);
void si2165_set_frontend_dvbc();
void si2165_set_frontend();
void si2165_set_if_freq_shift();
void si2165_read_status(void);
void si2165_set_oversamp(uint32_t dvb_rate);
void si2165_adjust_pll_divl();
void si2165_set_oversamp(uint32_t dvb_rate);

uint32_t fvco_hz;
uint32_t sys_clk;
uint32_t adc_clk;

uint32_t var;
int32_t oversamp ;
uint32_t reg_value;
uint32_t dvb_rate;
uint32_t symbol_rate;


uint32_t DR;
uint32_t m;
uint32_t FEC;

/* End user code. Do not edit comment generated here */

/* Start user code for adding. Do not edit comment generated here */

/******************************************************************************
* Function Name: R_IICr_Tx_addr1
* Description : when g_comstatus is TRANSMIT or RECEIVE,
*               check ACK for slave addr. and transmit EEPROM 1st addr.
******************************************************************************/
void R_IICr_Tx_addr1(void)
{
	g_comstatus++;                          /* change status to EEPROM addr.*/
	SIOr = 0x00;
}

/******************************************************************************
* Function Name: R_IICr_Tx_addr2
* Description : when g_comstatus is TxHiADDR or RxHiADDR,
*               check ACK for EEPROM 1st addr. and transmit EEPROM 2nd addr.
******************************************************************************/
void R_IICr_Tx_addr2(void)
{
	g_comstatus++;
	SIOr = 0x23;   /* send last address */
}

/******************************************************************************
* Function Name: R_IICr_Rx_RST
* Description : when g_comstatus is RxLoADDR,
*               check ACK for EEPROM Low addr. and  restart for read
******************************************************************************/
void R_IICr_Rx_RST(void)
{
    R_IICr_StartCond();                 /* issue ReStart Cond.      */
//    g_comstatus = ReStart;              /* change status to restart */
//    SIOr = DEMOD_ADDR/*g_PARAA.slaveaddr0xC8*/ | 1U;      /* send slave addr          */
}

/******************************************************************************
* Function Name: R_IICr_RxData_ST
* Description : when g_comstatus is ReStart,
*               check ACK for slave addr. and  start reception
******************************************************************************/
void R_IICr_RxData_ST(void)
{
    STmL = TRGONn;                      /* stop IICmn               */
    SCRmn ^= 0xC000;                    /* clear TxE00 and set RxE00 */
    SSmL = TRGONn;                      /* start IICmn receive      */

    //g_comstatus = RxData;               /* change status to data read */
    //if (g_PARAA.number == 1U)
    {
        SOEmL &= SOEOFF;                /* clear SOEm for NACK      */
//        g_comstatus = RxLast;           /* start last data read     */
    }

    SIOr = 0xFFU;                       /* release wait states      */
}
uint8_t ReceiveData = 0xFF;
/******************************************************************************
* Function Name: R_IICr_RxData
* Description : when g_comstatus is RxData,
*               store received data and check remaining data number.
*               if last data then set NACK response.
*               and start to receive data
******************************************************************************/
void R_IICr_RxData(void)
{
    //*g_PARAA.bufferaddr = SIOr;         /* store received data      */
    ReceiveData = SIOr;         /* store received data      */
    //g_PARAA.bufferaddr++;               /* change data pointer      */

    //if (--g_PARAA.number == 1U)         /* countdown data number    */
    {
        SOEmL &= SOEOFF;                /* clear SOEm for NACK      */
        g_comstatus = RxLast;           /* start last data read     */
    }

    SIOr = 0xFFU;                       /* release wait states      */
}

/******************************************************************************
* Function Name: R_IICr_RxLastData
* Description : when g_comstatus is RxLAST,
*               store received data and end receive mode
******************************************************************************/
void R_IICr_Rx_LastData(void)
{
    //*g_PARAA.bufferaddr = SIOr;         /* store received data      */
    ReceiveData = SIOr;         /* store received data      */

    STmL = TRGONn;                      /* stop IICmn               */
    SCRmn ^= 0xC000U;                   /* clear RxE00 and set TxE00 */

    SIRmn = 0x0007U;
    R_IICr_send_Stop();
    g_comstatus = TRNSEND;              /* set complete flag        */
}



/******************************************************************************
* Function Name: R_EEPROM_wait_write
* Description : wait for end of writing EEPROM
* Arguments : None
* Return Value : MD_STATUS
*       I2C_OK      : complete operation
*       PARA_ERR    : parameter error
*       NO_ACK1     : No ACK for slave address 
*       NO_ACK2     : No ACK for EEPROM addr.
*       NO_ACK3     : No ACK for data
******************************************************************************/
MD_STATUS R_EEPROM_wait_write(void)
{
    MD_STATUS   status = 0U;

    while (g_comstatus & 0b10000000)
    {
        NOP();                              /* wait for last page   */
    }

    status  = g_comstatus;                  /* read result status   */

    if (status == TRNSEND)
    {
        /*
            wait for writing end by polling
        */
        IICMKr = 1U;                        /* disable interrupt    */
        IICIFr = 0U;                        /* clear interrupt flag */

        do
        {
            SIRmn   = 0x0007U;              /* clear PEF(NACK) flag     */
            R_IICr_StartCond();             /* issue start condition    */
            SIOr    = g_PARAA.slaveaddr & SVAMSK;   /* send slave addr in write */

            while (IICIFr == 0U)
            {
                NOP();                      /* wait for INTIICmn        */
            }
            IICIFr = 0U;
        }
        while (R_IICr_NACK());

        R_IICr_send_Stop();
        IICMKr = 0U;                        /* enable interrupt        */
    }

    return (status);
}

/******************************************************************************
* Function Name: R_IICr_TxDataST
* Description : when g_comstatus is TxLoADDR,
*               send 1st data
******************************************************************************/
void R_IICr_TxDataST(void)
{
    g_comstatus = TxData;                   /* change status flag       */
    SIOr   = *g_PARAA.bufferaddr;           /* send data to IICr        */
    g_PARAA.bufferaddr++;                   /* move pointer to next data*/
}

/******************************************************************************
* Function Name: R_IICr_TxData
* Description : when g_comstatus is TxData,
*               check data number.
*               if transmit end, issue stop condition and wait write end
******************************************************************************/
void R_IICr_TxData(void)
{
    g_PARAA.number--;                       /* countdown data number    */
    if (g_PARAA.number == 0U)
    {
        /*
            end of page write data transmit and issue stop condition to
            start wariting.
        */
        R_IICr_send_Stop();                 /* issue stop condition         */

        if (g_PARAC.number > 0U)            /* check if more data to write  */
        {
            get_slave_Addr();               /* get next actual slave addr.  */
            R_EEPROM_Devide();              /* devide write data size       */

            g_comstatus = AFT_TX;           /* set status to after write wait*/

            TS0     |= 4U;                  /* start TM02(100us interval)   */
            TMIF02  = 0U;                   /* clear TM02 interrupt request */
            TMMK02  = 0U;                   /* enable INTTM02 interrupt     */
        }
        else                                /* exit if no more data to write */
        {
            g_comstatus = TRNSEND;          /* set success flag             */
        }
    }
    else
    {
        SIOr   = *g_PARAA.bufferaddr;       /* send data to IICr            */
        g_PARAA.bufferaddr++;               /* move pointer to next data    */
    }
}

/******************************************************************************
* Function Name: R_EEPROM_next_page
* Description : when g_comstatus is AFT_TX,
*               
* 
******************************************************************************/
void R_EEPROM_next_page(void)
{
    TT0     |= 4U;                          /* stop TM02(100us interval)    */
    TMIF02  = 0U;                           /* clear TM02 interrupt request */
    TMMK02  = 1U;                           /* enable INTTM02 interrupt     */
    /*
        end of page write, and start next page writing
    */
    g_comstatus = TRANSMIT;             /* send EEPROM cell addr.       */
    R_IICr_Tx_addr1();
}

/******************************************************************************
* Function Name: check_EEPROM_Addr
* Description : This function check Address is in EEPROM size. 
*               If not error, copy g_PARAI data to g_PARAC(copy for operation)
* Arguments :   address of g_PARAI(and global structure:EEPROM_Info)
*       All parameters are stored in structure PARA and EEPROM_Info
*       > uint16_t PARA.eepromaddr
*       > uint16_t PARA.number
*       > uint16_t EEPROM_Info.rom_size
* Return Value : error status
*   I2C_OK:     parameter is OK (and copy *PAPA data to g_PARAC)
*   PARA_ERR:   address over EEPROM size
******************************************************************************/
MD_STATUS check_EEPROM_Addr(eeprom_paraA16 *PARA)
{
    MD_STATUS   status = 0U;                    /* status flag of operation */
    uint32_t    cell_addr = 0U;                 /* cell addr. work area     */

    status = PARA_ERR;                          /* set temp flag            */
    cell_addr = PARA->eepromaddr;               /* read cell addr in parameter  */

    if (cell_addr <= (EEPROM_Info.rom_size << 8U))
    {
        cell_addr += PARA->number;              /* get end addr.            */
        /*
            check access end addr. and if end addr. is in EEPROM then
            set I2C_OK.
        */

        if (cell_addr <= (EEPROM_Info.rom_size << 8U))
        {
            status = I2C_OK;
            g_PARAC = *PARA;                    /* copy access parameters   */
        }
    }
    return (status);
}

/******************************************************************************
* Function Name: get_slave_Addr
* Description : This function get actual slave address.
*               In some case,  bit 3-1 of slave addr is modified.
* Arguments :   address of g_PARAI ( and global structure:EEPROM_Info)
*       All parameters are stored in structure PARA and EEPROM_Info
*       > uint8_t  g_PARAC.slaveaddr
*       > uint16_t g_PARAC.eepromaddr
*       > uint8_t  EEPROM_Info.addr_mask
* Return Value : None(structure g_PARAC.slaveaddr)
*       > uint8_t  g_PARAC.slaveaddr
* Note      : support from 2kbits upto 512kbits(Not support 1Mbits)
******************************************************************************/
void get_slave_Addr(void)
{
    uint8_t     mask = 0U;              /* mask bit data to use slave addr */
    uint8_t     slave_addr = 0U;        /* slave address                */
    uint8_t     work = 0U;
    uint16_t    cell_addr = 0U;         /* EEPROMcell address           */

    slave_addr = g_PARAC.slaveaddr;     /* get slave address in parameter */
    mask = EEPROM_Info.addr_mask;       /* get mask bit data            */
    cell_addr = g_PARAC.eepromaddr;     /* read cell addr in parameter  */

    if (mask != ADDR0BIT)
    {
        /*
            merge higher EEPROM addr. with slave addr.
        */
        slave_addr &= (uint8_t)~(mask << 1U);       /* clear merge area */
        work = (uint8_t)(cell_addr >> 8U) & mask;   /* merge addr.  */
        slave_addr |= (uint8_t)(work << 1U);        /* merge data       */

        g_PARAC.slaveaddr = slave_addr;             /* set result of procedure  */
    }
    return;
}
//#if 0
/******************************************************************************
* Function Name: R_EEPROM_Devide
* Description : This function check write Address,write data number and page size
*       and get datanumber to write in page and remaining data information
* Arguments : write parameter sttructure address g_PARAI
*       All parameters are stored in structure g_PARAI and EEPROM_Info
*       > uint8_t   g_PARAC.slaveaddr
*       > (uint16_t)g_PARAC.eepromaddr
*       > uint8_t   *g_PARAC.bufferaddr
*       > uint16_t  g_PARAC.number
*       > uint16_t  EEPROM_Info.page_size
* Return Value : None(global structure: g_PARAA and g_PARAC contents)
*       > uint8_t   g_PARAA.slaveaddr
*       > uint16_t  g_PARAA.eepromaddr
*       > uint8_t   *g_PARAA.bufferaddr
*       > uint16_t  g_PARAA.number
*       > uint16_t  g_PARAC.number(remaining)
*       > uint16_t  g_PARAC.eepromaddr(next)
*       > uint16_t  g_PARAC.bufferaddr(next)
******************************************************************************/
void R_EEPROM_Devide(void)
{
    uint16_t    page_mask = 0U;             /* page size-1 of EEPROM    */
    uint16_t    write_number = 0U;          /* data number write to page */

    /***********************************************************
        get write data number in page 
    ***********************************************************/

    page_mask = EEPROM_Info.page_size;      /* get page size mask data  */
    g_PARAA = g_PARAC;                      /* copy to access parameter */
    /*
        calculate write enable data number in page from eeprom address
    */
    write_number = (uint16_t)((g_PARAC.eepromaddr & page_mask) ^ page_mask);
    write_number++;                         /* Adjust page data number  */

    if (write_number > g_PARAC.number)      /* compare data numer to area in page */
    {                                       /* within page                  */
        write_number = g_PARAC.number;      /* set actual write data number */
        g_PARAC.number = 0U;                /* set remaining data number    */
    }
    else
    {                                       /* over page                    */
        g_PARAC.number = g_PARAC.number - write_number;  /* set remaining data number */
        g_PARAA.number = write_number;      /* set actual data number   */
    }
    g_PARAC.eepromaddr += write_number;     /* set next start Address   */
    g_PARAC.bufferaddr += write_number;     /* set next buffer address  */
}
//#endif
/******************************************************************************
* Function Name: R_IICr_StartCond
* Description : Issue start condition to I2C bus and fall SCL
* Arguments : None
* Return Value : None
******************************************************************************/
void R_IICr_StartCond(void)
{
    /* stop IICmn function and prepare to handle SCL and SDA by software */
    STmL    |= TRGONn;                      /* stop IICmn operation */
    SOEmL   &= SOEOFF;                      /* disable serial output */

    SOm     |= SDAHIGH;                     /* set SDA to high      */
    R_IICr_SCL_highTime();                  /* wait data setup time */
    SOm     |= SCLHIGH;                     /* set SCL to high      */

    /* port setting for IICr    */
 #if IIC11
    P_SDAr  = 1;                        /* set SDA port to 1    */
    P_SCLr  = 1;                        /* set SCL prot to 1    */
    PM_SDAr = 0;                        /* set SDA port to output   */
    PM_SCLr = 0;                        /* set SCL port to output   */
#else
    P_IICr  |= SDASCLON;                /* set SDA and SCL port to 1 */
    PM_IICr &= SDAOUTMODE;              /* set port to output mode  */
#endif

    /*
        issue start condition by software
    */

    R_IICr_SCL_Time();                      /* wait bus free time */
    SOm     &= SDALOW;                      /* issue IICr start condition */
    R_IICr_SCL_highTime();                  /* wait for Start Cond hold time */
    SOm     &= SCLLOW;                      /* fall SCL down to start transfer */
    R_IICr_SCL_Time();                      /* wait for SCL low width time */

    /* prepare for IIC00 function */
    SOEmL   |= SOEON;                       /* enable serial output */
    SSmL    |= TRGONn;                      /* enable IICmn operation */
}
/******************************************************************************
* Function Name: R_IICr_StopCond
* Description : Issue stop condition to I2C bus and wait for detect
* Arguments : None
* Return Value : None
*       MD_OK: bus is released
*       BUS_ERR: bus is not released(SDA line keeps low level)
******************************************************************************/
MD_STATUS R_IICr_StopCond(void)
{
    MD_STATUS status    = I2C_OK;           /* transfer control flag */

    R_IICr_send_Stop();                     /* generate stop condition */

    PM_IICr |= SDAINMODE;                   /* set SDAr line to input mode */
    if (P_SDAr == 0U)                       /* check Stop Cond is issued */
    {                                       /* bus is not released */
        status = BUS_ERR;
        if (R_IICr_wait_bus() == I2C_OK)
        {
            R_IICr_send_Stop();             /* generate stop condition */
            status = I2C_OK;
        }
    }

    PM_IICr &= SDAOUTMODE;                  /* set SDA to output mode */

    return (status);
}

/******************************************************************************
* Function Name: R_IIC0_StopCond
* Description : Issue stop condition to I2C bus
* Arguments : None
* Return Value : None
******************************************************************************/
void  R_IICr_send_Stop(void)
{
    R_IICr_SCL_highTime();              /* wait for SCL high pulse width */
    STmL    |= TRGONn;                  /* stop IICr            */
    SOEmL   &= SOEOFF;                  /* Enable SOm handling  */

    SOm     &= SDALOW;                  /* fall down SDA        */
    R_IICr_SCL_Time();                  /* wait set up time     */

    if ((SOm & SCLHIGH) == 0U)
    {
        /* SCL is low(after transfer wait) */
        R_IICr_SCL_high();              /* rize up SCL          */
    }

    SOm     |= SDAHIGH;                 /* rise up SDA          */
    R_IICr_SCL_Time();                  /* wait for rise up of SDA */
}

/******************************************************************************
* Function Name: R_IICr_wait_bus
* Description : Wait for IIC bus is released.
*       If necessary, generate SCL pulse upto 9 times. 
* Arguments : None
* Return Value : error flag
*       MD_OK: bus is released(SDA line is high level)
*       BUS_ERR: bus is not released(SDA line keeps low level)
******************************************************************************/
MD_STATUS R_IICr_wait_bus(void)
{
    uint8_t     work = 0U;                  /* set retry counter    */
    MD_STATUS   status  = I2C_OK;           /* transfer control flag */

    STmL    |= TRGONn;                      /* stop IICmn           */
    SOEmL   &= SOEOFF;                      /* disable serial output */
    SOm     |= SCLSDAHIGH;                  /* set SCLr and SDA output to high */
    PM_IICr |= SDAINMODE;                   /* set SDAr line to input mode */

    R_IICr_SCL_highTime();                  /* wait SCL high level width */

    for (work = 0U; work < RETRYCNT ; work++)
    {
        R_IICr_SCL_pulse();                 /* generate SCL pulse   */
    }

    if (P_SDAr == 0U)
    {
        status = BUS_ERR;
    }

    PM_IICr &= SDAOUTMODE;                  /* set SDAr line to output mode */
    return (status);
}

/******************************************************************************
* Function Name: R_IICr_SCL_pulse
* Description : generate SCL pulse for IIC bus by software
* Arguments : None
* Return Value : None
******************************************************************************/
void R_IICr_SCL_pulse(void)
{
    R_IICr_SCL_low();                       /* force SCLr output to low */
    R_IICr_SCL_high();                      /* rise SCLr output        */
}

/******************************************************************************
* Function Name: R_IICr_SCL_high
* Description : rise SCL pulse for IIC bus and wait pulse period
* Arguments : None
* Return Value : None
******************************************************************************/
void R_IICr_SCL_high(void)
{
    SOm |= SCLHIGH;                         /* rise SCLr output        */
    R_IICr_SCL_highTime();                  /* wait for SCL high pulse width */
}

/******************************************************************************
* Function Name: R_IICr_SCL_low
* Description : fall SCL pulse for IIC bus and wait pulse period
* Arguments : None
* Return Value : None
******************************************************************************/
void R_IICr_SCL_low(void)
{
    SOm &= SCLLOW;                          /* force SCL00 output to low */
    R_IICr_SCL_Time();                      /* wait for SCL low pulse width */
}


/******************************************************************************
* Function Name: R_IICr_NACK
* Description : check ACK response form slave 
* Arguments : None
* Return Value : NACK status
*       00:ACK
*       02:NACK
******************************************************************************/
MD_STATUS R_IICr_NACK(void)
{
    return (SSRmn & 0x0002U);                   /* return with status */
}

/******************************************************************************
* Function Name:R_IICr_SCL_Time
* Description : Wait for SCL change timing (1.3us)
* Arguments : None
* Return Value : None
******************************************************************************/
void R_IICr_SCL_Time(void)
{
    uint16_t    i = 0U;

    for (i = 1U; i < SCLLOWW; i++)
    {
        ;
    }
}

/******************************************************************************
* Function Name:R_IICr_SCL_highTime
* Description : Wait for SCL high level time (0.6us)
* Arguments : None
* Return Value : None
******************************************************************************/
void R_IICr_SCL_highTime(void)
{
    uint16_t    i = 0U;

    for (i = 1U; i < SCLHIGHW; i++)
    {
        ;
    }
}

/******************************************************************************
* Function Name:IINTIICr
* Description : IIC transfer end interrupt
* Arguments : None(g_comstatus)
*           >TRANSMIT   (0x80)          : slave addr. is transmitted
*           >TxHiADDR   (TRANSMIT+1)    : high addr. is transmitted
*           >TxLoADDR   (TRANSMIT+2)    ; high addr. is transmitted
*           >TxData     (TRANSMIT+0x20) : data is transmitted
*           >AFT_TX     (TxData+1)      : wait for data writing
*           >RECEIVE    (TRANSMIT+0x40) : slave addr. is transmitted
*           >RxHiADDR   (RECEIVE+1)     : high addr. is transmitted
*           >RxLoADDR   (RECEIVE+2)     : high addr. is transmitted
*           >ReStart    (RECEIVE +3)    : slave addr. for Rx is transmitted
*           >RxData     (RECEIVE +0x20) : data is received
*           >RxLAST     (RxData +1)     : last data is received
* Return Value : None(g_comstatus) above + below
*           >TRNSEND    (0x00)          : transfer complete(no error)
*           >NO_ACK1    (0x40)          : no ACK for slave addr.
*           >NO_ACK2    (0x41)          : no ACK fro addr.
*           >NO_ACK3    (0x42)          : no ACK for data
*           >BUS_ERR    (0x60)          : bus error(bus is occupied)
******************************************************************************/

/******************************************************************************
* Function Name:IINTTM02
* Description : 100us interval time check write is complete or not
* Arguments : None
* Return Value : None
******************************************************************************/
static void __near IINTTM02(void)
{
    SIRmn   = 0x0007U;                      /* clear PEF(NACK) flag     */

    R_IICr_StartCond();                     /* issue start condition    */

    SIOr    = g_PARAA.slaveaddr & SVAMSK;   /* send slave addr in write */
}
/******************************************************************************
* Function Name: R_IICr_Init
* Description  : This function initializes the IIC00 module.
* Arguments    : None
* Return Value : None
*******************************************************************************/
void R_IICr_Init(void)
{
#if IIC11
    P_SDAr  = 1U;                           /* set SDA port to 1    */
    P_SCLr  = 1U;                           /* set SCL port to 1    */
    PM_SCLr = 1U;                           /* set SCL port to input*/
    PM_SDAr = 1U;                           /* set SDA port to input*/
#else
    P_IICr  |= SDASCLON;                    /* set SDA & SCL port to 1      */
    PM_IICr |= SDASCLON;                    /* set SDA & SCL port to input  */
#endif

    IICMKr  = 1U;                           /* set interrupt mask   */
    IICPR0r = 0U;                           /* set priority  level2 */
    IICPR1r = 1U;
    SAUmEN  = 1U;                           /* supply clock to SAU0 */
    SPSm    = 0x0000U;                      /* select fclk as CK00 and CK01 */
    SIRmn   = 0x0007U;                      /* clear error flag     */
    SMRmn   = 0b0000000000100100;           /* set serial mode
                ||+++++|+||++|||------must be 0
                ||     | |+--|||------must be 1
                ||     | |   |||
                ||     | |   ||+------MDmn0
                ||     | |   || 0 : Transfer end interrupt
                ||     | |   ||
                ||     | |   ++-------MDmn2-mn1
                ||     | |      10 : Simplified I2C mode
                ||     | |
                ||     | +------------SISmn0(not specify)
                ||     |
                ||     +--------------STSmn
                ||              0 : software trigger only
                ||
                ++--------------------CKSmn,CCSmn
                                00 : CK00
        */

    SCRmn   = 0b0000000000010111;

    SDRmn   = /*0x5200U*/0x5200;             /* for FAST MODE(381Kbps)   *//*Assuming clock is 32 Mhz for 400Khz operation */
    SOm     |= SCLSDAHIGH;                  /* set SCLmn and SOmn       */
    POM_IICr |= SDAINMODE;                  /* set SDA to OD output     */

    PM_SDAr = 0U;                           /* set SDA port to output   */
    PM_SCLr = 0U;                           /* set SCL port to output   */

    SCRmn   |= 0b1000000000000000;          /* set TxE00                */
#if 0
    /*
    Timer(channel 02) for write time wait initialize
    */

    TAU0EN  = 1U;                           /* supplies input clock     */
    TPS0    = 0x0000U;                      /* clock is fCLK(32MHz)     */
    TMMK02  = 1U;                           /* mask INTTM02             */
    TMPR102 = 1U;                           /* set lowest priority      */
    TMPR002 = 1U;
    TMR02   = 0x0000U;                      /* TM02 is interval timer   */
    TDR02   = 3200U - 1U;                   /* interval time is 100us   */
    TO0     &= ~4U;                         /* clear timer output       */
    TOE0    &= ~4U;                         /* timer output disable     */

    R_device_select(R1EX24016A);            /* set default EEPROM parameter */
#endif
}
/*New Code */
static void __near IINTIICr_New(void)
{
	if (R_IICr_NACK() == 0U)                /* ACK response ?           */
	{
		if(gContext == DEMOD)
		{
			switch(gDemodState)
			{
				case DemodAddrW:
					SIOr = (gDemodRegAddr >> 8)&0xFF;
					gDemodState = DemodAddrWH;
					break;
				case DemodAddrWH:
					gDemodState = DemodAddrWL;
					SIOr = (gDemodRegAddr)&0xFF;
					break;
				case DemodAddrWL:
					gDemodState = DemodDataW;
					SIOr = (gDemodData) & 0xFF;
					break;
				case DemodDataW:
					R_IICr_send_Stop();
					gDemodState = DemodIdle;
					break;
				case DemodAddrR:
					gDemodState = DemodAddrRH;
					SIOr = (gDemodRegAddr >> 8)&0xFF;
					break;
				case DemodAddrRH:
					gDemodState = DemodAddrRL;
					SIOr = (gDemodRegAddr )&0xFF;
					break;
				case DemodAddrRL:
					gDemodState = DemodRRead;
					R_IICr_Rx_RST();
					SIOr = DEMOD_ADDR | 1U; 
					break;
				case DemodRRead:
					gDemodState=DemodRReadData;
					R_IICr_RxData_ST();
					break;	
				case DemodRReadData:
					gRTunerData=SIOr;
					R_IICr_Rx_LastData();
					gDemodState=DemodIdle;
					break;
			}
	    	}
    	if(gContext == TUNER)
	{
		switch(gTunerState)
		{
			case TunerDataW:
			if(gTunerTXData < 5)
				SIOr = gTunerData[gTunerTXData++]&0xFF;
			else	{
				R_IICr_send_Stop();
				gTunerState = TunerIdle;
				}
			break; 
			case TunerAddrR:
				gTunerState = TunerWRestart;
				R_IICr_Rx_RST();
				SIOr = TUNER_ADDR | 1U; 
			break;
			case TunerWRestart:
				gTunerState = TunerReadData;
				R_IICr_RxData_ST();
			break;
			case TunerReadData:
				gTunerState = TunerIdle;
				gRTunerData=SIOr;
				R_IICr_Rx_LastData();
			break;
    		}
	}
}
else
{
	SIRmn = 0x0007U;                /* clear PEF(NACK) flag         */
        R_IICr_send_Stop();             /* issue stop condition         */
	if(gContext == TUNER)
		gTunerState = TunerIdle;
	if(gContext == DEMOD)
		gDemodState = DemodIdle;
}
}
void I2C_Write_Demod(uint16_t regAddr, uint8_t data) {
	gDemodRegAddr = regAddr;
	gDemodData = data;
	gContext = DEMOD;
	R_IICr_StartCond();
	gDemodState=DemodAddrW;
	SIOr = DEMOD_ADDR;
}
void I2C_Read_Demod(uint16_t regAddr, uint8_t data) {
	gDemodRegAddr = regAddr;
	gContext = DEMOD;
	R_IICr_StartCond();
	gDemodState=DemodAddrR;
	SIOr = DEMOD_ADDR;
}

void I2C_Write_Tuner(uint8_t *data) {
	
	gTunerData = data;
	gTunerTXData = 0;
	gContext = TUNER;
	R_IICr_StartCond();
	gTunerState=TunerDataW;
	SIOr = TUNER_ADDR;
}
void I2C_Read_Tuner() {
	gContext = TUNER;
	R_IICr_StartCond();
	gTunerState=TunerAddrR;
	SIOr = TUNER_ADDR;
}
uint32_t GetTunerState() {
	return gTunerState;
}
uint32_t GetTunerData(){
	return gRTunerData;
}

void Si2165_Driver(void)
{
	Si2165_Probe();
}
void Si2165_Probe(void)
{
	/* create dvb_frontend */
	dvb_frontend_ops();
	
	/* powerup */
	I2C_Write_Demod(REG_CHIP_MODE,0x21); 	     /* Releases the Si2165 from stand by mode and specifies the clock source */
	Write_Delay();
	
	I2C_Write_Demod(REG_CHIP_REVCODE,0x03); 	   
	Write_Delay();
	
}

void dvb_frontend_ops(void)
{
	Si2165_Device_init();
	//si2165_sleep();
	si2165_set_frontend();
	si2165_read_status();
}

void Si2165_Device_init(void)
{
	I2C_Write_Demod(REG_CHIP_MODE,0x21); 	     /* Releases the Si2165 from stand by mode and specifies the clock source */
	Write_Delay();
	I2C_Write_Demod( REG_DSP_CLOCK,0x01);
	Write_Delay();
	
	/*AGC */
	I2C_Write_Demod( REG_AGC_IF_TRI,0x00);
	Write_Delay();
	I2C_Write_Demod( REG_AGC_IF_SLR,0x01);
	Write_Delay();
	I2C_Write_Demod( REG_AGC2_OUTPUT,0x00);
	Write_Delay();
	I2C_Write_Demod( REG_AGC2_CLKDIV,0x07);
	Write_Delay();
	I2C_Write_Demod( REG_RSSI_PAD_CTRL,0x00);
	Write_Delay();
	I2C_Write_Demod( REG_RSSI_ENABLE,0x00);
	Write_Delay();
	
	/* PLL */
	I2C_Write_Demod(PLL_ENABLE ,0x80); 	     /* PLL enable*/
	Write_Delay();
	PLL_init();
	
	I2C_Write_Demod(REG_CHIP_INIT,0x01);         /* To launch initialization */
	Write_Delay();
	I2C_Write_Demod(REG_START_INIT,0x01);        /* Starts initialization */
	Write_Delay();
	I2C_Read_Demod(0x0054,0x01);                 /* check for completion of initialization */
	while( ReceiveData  != 0x01)
	{
		NOP();
	}
	
	I2C_Write_Demod(REG_CHIP_INIT,0x00);         /* Stop initialization */
	Write_Delay();
	
	/* ber_pkt - default 65535 */
	I2C_Write_Demod( REG_BER_PKT,STATISTICS_PERIOD_PKT_COUNT);
	Write_Delay();
	I2C_Read_Demod( REG_PATCH_VERSION,&Patch_version);
	Write_Delay();
	I2C_Write_Demod(REG_AUTO_RESET,0x00);
	Write_Delay();
	
	/* DSP START */
	I2C_Write_Demod(REG_RST_ALL,0x00); 		/*Resets all logic without internal registers */
	Write_Delay();
	I2C_Write_Demod(REG_ADDR_JUMP1_LSB,0x00);            /* For DVB-C 0x0348 set to 0 */
	Write_Delay();
	
	
	I2C_Write_Demod(REG_WDOG_AND_BOOT,0x00);       
	Write_Delay();
	
	if (Patch_version == 0x00) 
	{
		
	}
	
	/* ts output config */
	I2C_Write_Demod(REG_TS_DATA_MODE,0x20);       
	Write_Delay();
	I2C_Write_Demod(REG_TS_TRI,0x00fe);       
	Write_Delay();
	I2C_Write_Demod(REG_TS_SLR1,0x55);
	Write_Delay();
	I2C_Write_Demod(REG_TS_SLR2,0x55);
	Write_Delay();
	I2C_Write_Demod(REG_TS_SLR3,0x55);
	Write_Delay();
	I2C_Write_Demod(REG_TS_CLK_MODE,0x01);       
	Write_Delay();
	I2C_Write_Demod(REG_TS_PARALLEL_MODE,0x00);       
	Write_Delay();
	
	
	/* DEMOD parameters and ADC settings */
	I2C_Write_Demod(REG_DVB_STANDARD,0x05);      /* For DVB-C */
	Write_Delay();
	
	
	I2C_Write_Demod(REG_ADC_RI1,0x46); 
	Write_Delay();
	I2C_Write_Demod(REG_ADC_RI3,0x00);
	Write_Delay();
	I2C_Write_Demod(REG_ADC_RI5,0x0A);
	Write_Delay();
	I2C_Write_Demod(REG_ADC_RI6,0xFF);
	Write_Delay();
	I2C_Write_Demod(REG_ADC_RI8,0x70);
	Write_Delay();
	
	I2C_Write_Demod(REG_RST_ALL,0x00); /*Resets all logic without internal registers */
	Write_Delay();
	
}
void si2165_sleep(void)
{
	/* dsp clock disable */
	I2C_Write_Demod( REG_DSP_CLOCK, 0x00);
	Write_Delay();
	/* chip mode */
	I2C_Write_Demod( REG_CHIP_MODE, 0x00);
	Write_Delay();
}

void Write_Delay(void)
{
while (gDemodState != DemodIdle)
	{
		NOP();
		NOP();
	}
}

int PLL_init()
{
	uint32_t ref_freq_hz = 8000000;
	uint8_t pll_divR = 1;
	uint8_t pll_divP = 4;
	uint8_t pll_divN = 25;
	uint8_t pll_divM = 8;
	uint8_t pll_divL = 12;
	
	#if 0
	/* ref_freq / divr must be between 4 and 16 MHz */
	if (ref_freq_hz > 16000000u)
			pll_divR = 2;

	/* now select divn and divp such that fvco is in 1624..1824 MH */
	if (1624000000u * pll_divR > ref_freq_hz * 2u * 63u)
			pll_divP = 4;

	/* is this already correct regarding rounding? */
	pll_divN = 1624000000u * pll_divR / (ref_freq_hz * 2u * pll_divP);
	#endif 
	
	fvco_hz = ref_freq_hz / pll_divR * 2u * pll_divN  * pll_divP ;
	adc_clk = fvco_hz / ( pll_divM * 4u);
	sys_clk = fvco_hz / ( pll_divL * 2u);
	
	I2C_Write_Demod(PLL_L_DIVIDER,pll_divL);
	Write_Delay();
	I2C_Write_Demod(PLL_M_DIVIDER,pll_divM);
	Write_Delay();
	
	var = ( pll_divN & 0x3f) | ((pll_divP == 1) ? 0x40 : 0x00) | 0x80 ;
	I2C_Write_Demod(PLL_P_DIVIDER,var);
	Write_Delay();
	
	I2C_Write_Demod(PLL_R_DIVIDER,pll_divR);
	Write_Delay();
}
/* End user code. Do not edit comment generated here */

void si2165_set_frontend()
{
	/* initial setting of if freq shift */
	si2165_set_if_freq_shift();
	 
	si2165_set_frontend_dvbc();
	
	/* dsp_addr_jump */
	I2C_Write_Demod( REG_ADDR_JUMP1_LSB,0x00);
	Write_Delay();
	I2C_Write_Demod( REG_ADDR_JUMP2,0x00);
	Write_Delay();
	I2C_Write_Demod( REG_ADDR_JUMP3,0x00);
	Write_Delay();
	I2C_Write_Demod( REG_ADDR_JUMP4_MSB,0x00);
	Write_Delay();
	
	/* recalc if_freq_shift if IF might has changed */
	si2165_set_if_freq_shift();
	
	/* boot/wdog status */
	I2C_Read_Demod( REG_WDOG_AND_BOOT,0x00 );
	Write_Delay();
	I2C_Write_Demod( REG_WDOG_AND_BOOT,0x00 );
	Write_Delay();
	
	/* reset all */
	I2C_Write_Demod(REG_RST_ALL,0x00);
	Write_Delay();
	
	/* gp_reg0 */
	I2C_Write_Demod( REG_GP_REG0_LSB, 0x00);
	Write_Delay();
	
	
	
}

void si2165_set_if_freq_shift()
{
	/*64 bit operation */
	/* if_freq_shift, usbdump contained 0x023ee08f; */
	I2C_Write_Demod( REG_IF_FREQ_SHIFT1_LSB,0x70);/* 24DD2F1 */
	Write_Delay();
	I2C_Write_Demod( REG_IF_FREQ_SHIFT2,0xEB);
	Write_Delay();
	I2C_Write_Demod( REG_IF_FREQ_SHIFT3,0x00);
	Write_Delay();
	I2C_Write_Demod( REG_IF_FREQ_SHIFT4_MSB,0x00);
	Write_Delay();
}


void si2165_set_frontend_dvbc()
{
	uint32_t temp;
	uint32_t modulation;
	symbol_rate = DR/(m*FEC);
        dvb_rate = symbol_rate;
	si2165_adjust_pll_divl();
	si2165_set_oversamp(dvb_rate);
	
	#if 0
	switch (modulation) {
	case QPSK:
		temp = 0x3;
		break;
	case QAM_16:
		temp = 0x7;
		break;
	case QAM_32:
		temp = 0x8;
		break;
	case QAM_64:
		temp = 0x9;
		break;
	case QAM_128:
		temp = 0xa;
		break;
	case QAM_256:
	default:
		temp = 0xb;
		break;
	}
	#endif
	 
	I2C_Write_Demod(REG_REQ_CONSTELLATION,0x07);
	Write_Delay();
	I2C_Write_Demod(REG_LOCK_TIMEOUT1_LSB,0x00);
	Write_Delay();
	I2C_Write_Demod(REG_LOCK_TIMEOUT2,0x12);
	Write_Delay();
	I2C_Write_Demod(REG_LOCK_TIMEOUT3,0x7a);
	Write_Delay();
	I2C_Write_Demod(REG_LOCK_TIMEOUT4_MSB,0x00);
	Write_Delay();
	
	I2C_Write_Demod(REG_DVB_STANDARD,0x05);
	Write_Delay();
	I2C_Write_Demod(REG_AGC2_MIN,0x50);
	Write_Delay();
	I2C_Write_Demod(REG_AGC2_KACQ,0x0e);
	Write_Delay();
	I2C_Write_Demod(REG_AGC2_KLOC,0x10);
	Write_Delay();
	I2C_Write_Demod(REG_AGC_UNFREEZE_THR,0x03);
	Write_Delay();
	I2C_Write_Demod(REG_AGC_CRESTF_DBX8,0x68);
	Write_Delay();
	I2C_Write_Demod(REG_AAF_CRESTF_DBX8,0x68);
	Write_Delay();
	I2C_Write_Demod(REG_ACI_CRESTF_DBX8,0x50);
	Write_Delay();
	I2C_Write_Demod(REG_EQ_AUTO_CONTROL,0x0D);
	Write_Delay();
	I2C_Write_Demod(REG_KP_LOCK,0x05);
	Write_Delay();
	I2C_Write_Demod(REG_CENTRAL_TAP,0x09);
	Write_Delay();
	I2C_Write_Demod(REG_UNKNOWN_350_1,0x3e);
	Write_Delay();
	I2C_Write_Demod(REG_UNKNOWN_350_2,0x80);
	Write_Delay();
	I2C_Write_Demod(REG_AUTO_RESET,0x01);
	Write_Delay();
	I2C_Write_Demod(REG_SWEEP_STEP,0x03);
	Write_Delay();
	

}
void si2165_read_status(void)
{
	uint8_t temp1;
	uint32_t temp2;
	uint32_t *status = 0;
	
	/* check packet sync lock */
	I2C_Read_Demod( REG_PS_LOCK,0x01);
	Write_Delay();
	temp1 = ReceiveData;
	
	if (temp1 & 0x01) 
		{
			*status |= FE_HAS_SIGNAL;
			*status |= FE_HAS_CARRIER;
			*status |= FE_HAS_VITERBI;
			*status |= FE_HAS_SYNC;
		}
	/* check fec_lock */
	I2C_Read_Demod( REG_FEC_LOCK,0x00);
	Write_Delay();
	temp1 = ReceiveData;
	
	if (temp1 & 0x01)
		{
			*status |= FE_HAS_SIGNAL;
			*status |= FE_HAS_CARRIER;
			*status |= FE_HAS_VITERBI;
			*status |= FE_HAS_SYNC;
			*status |= FE_HAS_LOCK;
		}
	/*CNR*/
	I2C_Read_Demod( REG_C_N,0x00);
	Write_Delay();
	temp2 = 10*log(2^(24)/ReceiveData);
	
	/*BER*/
	I2C_Write_Demod(REG_BER_AVAIL,0x01);
	Write_Delay();
	I2C_Read_Demod( REG_BER_BIT,0x00);
	Write_Delay();
	I2C_Read_Demod( REG_BER_PKT,0x00);
	Write_Delay();
	
	/* BER = REG_BER_BIT/(REG_BER_PKT*204*8); */
	
	
}
void si2165_set_oversamp(uint32_t dvb_rate)
{
	//oversamp = adc_clk;
	//oversamp <<= 23;
	//oversamp = oversamp / dvb_rate;
	//reg_value = oversamp & 0x3fffffff;
	I2C_Write_Demod(REG_OVERSAMP1_LSB,0x20);/* 397AC20 */
	Write_Delay();
	I2C_Write_Demod(REG_OVERSAMP2,0xAC);
	Write_Delay();
	I2C_Write_Demod(REG_OVERSAMP3,0x97);
	Write_Delay();
	I2C_Write_Demod(REG_OVERSAMP4_MSB,0x03);
	Write_Delay();
	
} 

void si2165_adjust_pll_divl()
{
	uint8_t pll_divL = 14;
	sys_clk = fvco_hz / ( pll_divL * 2u);
	I2C_Write_Demod(PLL_L_DIVIDER,pll_divL);
	Write_Delay();
}