#ifndef _DVB_SI2165_H
#define _DVB_SI2165_H

void I2C_Write_Demod(uint16_t regAddr, uint8_t data);
void I2C_Read_Demod(uint16_t regAddr, uint8_t data);
void I2C_Write_Tuner(uint8_t *data);
void I2C_Read_Tuner();
uint32_t GetTunerState();
uint32_t GetTunerData();
void Si2165_Device_init(void);
void Write_Delay(void);

enum {
	SI2165_MODE_OFF = 0x00,
	SI2165_MODE_PLL_EXT = 0x20,
	SI2165_MODE_PLL_XTAL = 0x21
};

enum fe_status {
	FE_NONE			= 0x00,
	FE_HAS_SIGNAL		= 0x01,
	FE_HAS_CARRIER		= 0x02,
	FE_HAS_VITERBI		= 0x04,
	FE_HAS_SYNC		= 0x08,
	FE_HAS_LOCK		= 0x10,
	FE_TIMEDOUT		= 0x20,
	FE_REINIT		= 0x40,
};
enum modulation {
	OOK,
	FSK,
	UNDEF
};
enum fe_modulation {
	QPSK,
	QAM_16,
	QAM_32,
	QAM_64,
	QAM_128,
	QAM_256,
	QAM_AUTO,
	VSB_8,
	VSB_16,
	PSK_8,
	APSK_16,
	APSK_32,
	DQPSK,
	QAM_4_NR,
};
enum fe_delivery_system {
	SYS_UNDEFINED,
	SYS_DVBC_ANNEX_A,
	SYS_DVBC_ANNEX_B,
	SYS_DVBT,
	SYS_DSS,
	SYS_DVBS,
	SYS_DVBS2,
	SYS_DVBH,
	SYS_ISDBT,
	SYS_ISDBS,
	SYS_ISDBC,
	SYS_ATSC,
	SYS_ATSCMH,
	SYS_DTMB,
	SYS_CMMB,
	SYS_DAB,
	SYS_DVBT2,
	SYS_TURBO,
	SYS_DVBC_ANNEX_C,
};
//uint8_t ReceiveData;

struct si2165_platform_data {
	/*
	 * frontend
	 * returned by driver
	 */
	struct dvb_frontend **fe;

	/* external clock or XTAL */
	uint8_t chip_mode;

	/* frequency of external clock or xtal in Hz
	 * possible values: 4000000, 16000000, 20000000, 240000000, 27000000
	 */
	uint32_t ref_freq_hz;

	/* invert the spectrum */
	int inversion;
};


#endif /* _DVB_SI2165_H */