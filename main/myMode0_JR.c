//===========================================================================
//
// This confidential and proprietary software may be used only as authorised
// by a licensing agreement from TC Applied Technologies Ltd.
//
// (C) COPYRIGHT 2005 TC Applied Technologies Ltd. (ALL RIGHTS RESERVED)
//
// Unauthorized use, duplication or distribution of this software is  
// strictly prohibited by law.
//
// The entire notice above must be reproduced on all authorised copies and
// copies may only be made to the extent permitted by a licensing agreement
// from TC Applied Technologies Ltd.
//
/****************************************************************************
	
	Purpose:	myMode0_JR.c, this is the channel configuration for DICE JR
	            in mode 0.
	            Configuration:  28x28 AES, Analog and ADAT @32k-48k
	
	Revisions:
		created 13/06/2007 ml
		

****************************************************************************/

#include "TCTypes.h"
#include "ErrorCodes.h"
#include "TCTasking.h"
#include "dal.h"

#include "diceDriver.h"
#include "dicedriverInterface.h"

#include "targetBoard.h"
#include "myModes.h"




// We need to define how we present ourselves to the PC and Mac driver. We will
// need to specify our Isco channel layout, names for ASIO and CoreAudio etc.
// Starting and stopping the 1394 Isoc streams will be handled by the DiceDriver
// module.
//


// The settings below are shared for all configurations within this mode.

#define MY_DEVICE_SUPPORTED_CLK_CAPS (	DD_CP_RATE_32   | DD_CP_RATE_44_1    |\
										DD_CP_RATE_48   | DD_CP_RATE_88_2    |\
										DD_CP_RATE_96   | DD_CP_RATE_176_4   |\
										DD_CP_RATE_192  | DD_CP_SOURCE_AES1    |\
										DD_CP_SOURCE_AES2 | DD_CP_SOURCE_AES3	   |\
										DD_CP_SOURCE_AES4 | DD_CP_SOURCE_AES_ANY |\
										DD_CP_SOURCE_WC   | DD_CP_SOURCE_ARX1    |\
										DD_CP_SOURCE_ARX2 | DD_CP_SOURCE_INT       )

#define MY_DEVICE_SUPPORTED_CLK_SRC_NAMES "AES12\\AES34\\AES56\\AES78\\AES_ANY\\Word Clock\\Unused\\Unused\\Internal\\\\"

#define MY_INPUT_DEVICES  (DEVICE_BIT(DEV_AES_RX) | DEVICE_BIT(DEV_AVS_ADO1) | \
	                       DEVICE_BIT(DEV_INS_RX0) | DEVICE_BIT(DEV_INS_RX1))

#define MY_OUTPUT_DEVICES (DEVICE_BIT(DEV_AES_TX) | DEVICE_BIT(DEV_AVS_ADI1) | \
	                       DEVICE_BIT(DEV_INS_TX0) | DEVICE_BIT(DEV_INS_TX1))



//===========================================================================
// LOW MODE CONFIGURATIONS
//===========================================================================

#define MY_NB_TX_ISOC_STREAMS_LOW 2
static STREAM_CONFIG myDriverTxConfigLow[MY_NB_TX_ISOC_STREAMS_LOW] =
{
//	Audio  Midi  Names as they appear on computer sepperated by '\' and terminated by "\\"
	{8,    1,    "AES1\\AES2\\AES3\\AES4\\AES5\\AES6\\AES7\\AES8\\\\", 0x0000},
	{8,    0,    "AN1\\AN2\\AN3\\AN4\\AN5\\AN6\\AN7\\AN8\\\\",0x0000}
};


#define MY_NB_RX_ISOC_STREAMS_LOW 2
static STREAM_CONFIG myDriverRxConfigLow[MY_NB_RX_ISOC_STREAMS_LOW] =
{
//	Audio  Midi  Names as they appear on computer sepperated by '\' and terminated by "\\"	
	{8,    1,    "AES1\\AES2\\AES3\\AES4\\AES5\\AES6\\AES7\\AES8\\\\", 0x0000},
	{8,    0,    "AN1\\AN2\\AN3\\AN4\\AN5\\AN6\\AN7\\AN8\\\\",0x0000}
};

static HRESULT routeLow (void)
{
	dalSetRoute(eDAL_INTERFACE_1, TX_AES0_CHL,  RX_AVS1_CH0);
	dalSetRoute(eDAL_INTERFACE_1, TX_AES0_CHR,  RX_AVS1_CH1);
	dalSetRoute(eDAL_INTERFACE_1, TX_AES1_CHL,  RX_AVS1_CH2);
	dalSetRoute(eDAL_INTERFACE_1, TX_AES1_CHR,  RX_AVS1_CH3);
	dalSetRoute(eDAL_INTERFACE_1, TX_AES2_CHL,  RX_AVS1_CH4);
	dalSetRoute(eDAL_INTERFACE_1, TX_AES2_CHR,  RX_AVS1_CH5);
	dalSetRoute(eDAL_INTERFACE_1, TX_AES3_CHL,  RX_AVS1_CH6);
	dalSetRoute(eDAL_INTERFACE_1, TX_AES3_CHR,  RX_AVS1_CH7);
	dalSetRoute(eDAL_INTERFACE_1, TX_INS1_CH0_7,  RX_AVS1_CH8_15);		
	
	dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH0, RX_AES0_CHL);
	dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH1, RX_AES0_CHR);
	dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH2, RX_AES1_CHL);
	dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH3, RX_AES1_CHR);
	dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH4, RX_AES2_CHL);
	dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH5, RX_AES2_CHR);
	dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH6, RX_AES3_CHL);
	dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH7, RX_AES3_CHR);
	dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH8_15, RX_INS1_CH0_7);		
	return NO_ERROR;
}


static STREAM_CFG myDriverConfigureLow =
{
	myDriverTxConfigLow,
	MY_NB_TX_ISOC_STREAMS_LOW,
	myDriverRxConfigLow,
	MY_NB_RX_ISOC_STREAMS_LOW
};






//===========================================================================
// MID MODE CONFIGURATIONS
//===========================================================================

#define MY_NB_TX_ISOC_STREAMS_MID 2
static STREAM_CONFIG myDriverTxConfigMid[MY_NB_TX_ISOC_STREAMS_MID] =
{
//	Audio  Midi  Names as they appear on computer sepperated by '\' and terminated by "\\"	
	{8,    1,    "AES1\\AES2\\AES3\\AES4\\AES5\\AES6\\AES7\\AES8\\\\", 0x0000},
	{8,    0,    "AN1\\AN2\\AN3\\AN4\\AN5\\AN6\\AN7\\AN8\\\\",0x0000}
};

#define MY_NB_RX_ISOC_STREAMS_MID 2 
static STREAM_CONFIG myDriverRxConfigMid[MY_NB_RX_ISOC_STREAMS_MID] =
{
//	Audio  Midi  Names as they appear on computer sepperated by '\' and terminated by "\\"
	{8,    1,    "AES1\\AES2\\AES3\\AES4\\AES5\\AES6\\AES7\\AES8\\\\", 0x0000},
	{8,    0,    "AN1\\AN2\\AN3\\AN4\\AN5\\AN6\\AN7\\AN8\\\\",0x0000}
};

static HRESULT routeMid (void)
{
	dalSetRoute(eDAL_INTERFACE_1, TX_AES0_CHL,  RX_AVS1_CH0);
	dalSetRoute(eDAL_INTERFACE_1, TX_AES0_CHR,  RX_AVS1_CH1);
	dalSetRoute(eDAL_INTERFACE_1, TX_AES1_CHL,  RX_AVS1_CH2);
	dalSetRoute(eDAL_INTERFACE_1, TX_AES1_CHR,  RX_AVS1_CH3);
	dalSetRoute(eDAL_INTERFACE_1, TX_AES2_CHL,  RX_AVS1_CH4);
	dalSetRoute(eDAL_INTERFACE_1, TX_AES2_CHR,  RX_AVS1_CH5);
	dalSetRoute(eDAL_INTERFACE_1, TX_AES3_CHL,  RX_AVS1_CH6);
	dalSetRoute(eDAL_INTERFACE_1, TX_AES3_CHR,  RX_AVS1_CH7);
	dalSetRoute(eDAL_INTERFACE_1, TX_INS1_CH0_7,  RX_AVS1_CH8_15);		
	
	dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH0, RX_AES0_CHL);
	dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH1, RX_AES0_CHR);
	dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH2, RX_AES1_CHL);
	dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH3, RX_AES1_CHR);
	dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH4, RX_AES2_CHL);
	dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH5, RX_AES2_CHR);
	dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH6, RX_AES3_CHL);
	dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH7, RX_AES3_CHR);
	dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH8_15, RX_INS1_CH0_7);		
	return NO_ERROR;
}

static STREAM_CFG myDriverConfigureMid =
{
	myDriverTxConfigMid,
	MY_NB_TX_ISOC_STREAMS_MID,
	myDriverRxConfigMid,
	MY_NB_RX_ISOC_STREAMS_MID
};



//===========================================================================
// HIGH MODE CONFIGURATIONS
//===========================================================================

#define MY_NB_TX_ISOC_STREAMS_HIGH 2
static STREAM_CONFIG myDriverTxConfigHigh[MY_NB_TX_ISOC_STREAMS_HIGH] =
{
//	Audio  Midi  Names as they appear on computer sepperated by '\' and terminated by "\\"
	{8,    1,    "AES1\\AES2\\AES3\\AES4\\AES5\\AES6\\AES7\\AES8\\\\", 0x0000},
	{8,    0,    "AN1\\AN2\\AN3\\AN4\\AN5\\AN6\\AN7\\AN8\\\\",0x0000}
};

#define MY_NB_RX_ISOC_STREAMS_HIGH 2 
static STREAM_CONFIG myDriverRxConfigHigh[MY_NB_RX_ISOC_STREAMS_HIGH] =
{
	{8,    1,    "AES1\\AES2\\AES3\\AES4\\AES5\\AES6\\AES7\\AES8\\\\", 0x0000},
	{8,    0,    "AN1\\AN2\\AN3\\AN4\\AN5\\AN6\\AN7\\AN8\\\\",0x0000}
};

static HRESULT routeHigh (void)
{
	dalSetRoute(eDAL_INTERFACE_1, TX_AES0_CHL,  RX_AVS1_CH0);
	dalSetRoute(eDAL_INTERFACE_1, TX_AES0_CHR,  RX_AVS1_CH1);
	dalSetRoute(eDAL_INTERFACE_1, TX_AES1_CHL,  RX_AVS1_CH2);
	dalSetRoute(eDAL_INTERFACE_1, TX_AES1_CHR,  RX_AVS1_CH3);
	dalSetRoute(eDAL_INTERFACE_1, TX_AES2_CHL,  RX_AVS1_CH4);
	dalSetRoute(eDAL_INTERFACE_1, TX_AES2_CHR,  RX_AVS1_CH5);
	dalSetRoute(eDAL_INTERFACE_1, TX_AES3_CHL,  RX_AVS1_CH6);
	dalSetRoute(eDAL_INTERFACE_1, TX_AES3_CHR,  RX_AVS1_CH7);
	dalSetRoute(eDAL_INTERFACE_1, TX_INS1_CH0_7,  RX_AVS1_CH8_15);		
	
	dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH0, RX_AES0_CHL);
	dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH1, RX_AES0_CHR);
	dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH2, RX_AES1_CHL);
	dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH3, RX_AES1_CHR);
	dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH4, RX_AES2_CHL);
	dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH5, RX_AES2_CHR);
	dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH6, RX_AES3_CHL);
	dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH7, RX_AES3_CHR);
	dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH8_15, RX_INS1_CH0_7);		
	return NO_ERROR;
}

static STREAM_CFG myDriverConfigureHigh =
{
	myDriverTxConfigHigh,
	MY_NB_TX_ISOC_STREAMS_HIGH,
	myDriverRxConfigHigh,
	MY_NB_RX_ISOC_STREAMS_HIGH
};




//===========================================================================
// GENERIC STUFF
//===========================================================================



static uint32 bInitFlags;

static HRESULT routeMode (DAL_RATE_MODE_ENUM ratemode)
{
	switch (ratemode)
	{
		default:
		case eDAL_RATE_MODE_LOW: return routeLow();
		case eDAL_RATE_MODE_MID: return routeMid();
		case eDAL_RATE_MODE_HIGH: return routeHigh();
	}
	return NO_ERROR;
}


static HRESULT initMode(uint32 initFlags)
{
	bInitFlags = initFlags;

	targetChangeAudioPorts (APM_NORMAL);

    insSetClockPortI2S		(INS_ID1, INS_MCK_256BR, true);
    insRxSetDataFormatI2S	(INS_ID1, INS_LN0, true);
	insRxSetDataFormatI2S	(INS_ID1, INS_LN1, true);
	insRxSetDataFormatI2S	(INS_ID1, INS_LN2, true);
	insRxSetDataFormatI2S	(INS_ID1, INS_LN3, true);
    insTxSetDataFormatI2S	(INS_ID1, INS_LN0, true);
	insTxSetDataFormatI2S	(INS_ID1, INS_LN1, true);
	insTxSetDataFormatI2S	(INS_ID1, INS_LN2, true);
	insTxSetDataFormatI2S	(INS_ID1, INS_LN3, true);

	return NO_ERROR;
}

static HRESULT msgFunc (MYMODE_MSG msg, uint32 data0, uint32 data1)
{
	return NO_ERROR;
}

MODE_CFG modeCfg0_JR = {
	&myDriverConfigureLow,
	&myDriverConfigureMid,
	&myDriverConfigureHigh,
	MY_INPUT_DEVICES,
	MY_OUTPUT_DEVICES,
	MY_DEVICE_SUPPORTED_CLK_CAPS,
	MY_DEVICE_SUPPORTED_CLK_SRC_NAMES,
	routeMode,
	initMode,
	msgFunc,
	"DICE JR EVM 28/28"
};


