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

    Purpose:    myMode0_JR.c, this is the channel configuration for DICE JR
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

#define MIDI    0




// We need to define how we present ourselves to the PC and Mac driver. We will
// need to specify our Isco channel layout, names for ASIO and CoreAudio etc.
// Starting and stopping the 1394 Isoc streams will be handled by the DiceDriver
// module.
//


// The settings below are shared for all configurations within this mode.

#define MY_DEVICE_SUPPORTED_CLK_CAPS (  DD_CP_RATE_32 | DD_CP_RATE_44_1 |\
                    DD_CP_RATE_48 | DD_CP_SOURCE_WC )

#define MY_DEVICE_SUPPORTED_CLK_SRC_NAMES "Unused\\Unused\\Unused\\Unused\\Unused\\Axum Clock\\Unused\\Unused\\Unused\\\\"

//#define MY_INPUT_DEVICES  (DEVICE_BIT(DEV_INS_RX0) | DEVICE_BIT(DEV_INS_RX1))

//#define MY_OUTPUT_DEVICES (DEVICE_BIT(DEV_INS_TX0) | DEVICE_BIT(DEV_INS_TX1))
#define MY_INPUT_DEVICES  (DEVICE_BIT(DEV_AVS_ADO1) | DEVICE_BIT(DEV_AVS_ADO2) |\
                           DEVICE_BIT(DEV_MIXER_RX) |\
                           DEVICE_BIT(DEV_INS_RX0) | DEVICE_BIT(DEV_INS_RX1))

#define MY_OUTPUT_DEVICES (DEVICE_BIT(DEV_AVS_ADI1) | DEVICE_BIT(DEV_AVS_ADI2) |\
                           DEVICE_BIT(DEV_MIXER_TX0) | DEVICE_BIT(DEV_MIXER_TX1) |\
                           DEVICE_BIT(DEV_INS_RX0) | DEVICE_BIT(DEV_INS_RX1))


//===========================================================================
// LOW MODE CONFIGURATIONS
//===========================================================================

#define MY_NB_TX_ISOC_STREAMS_LOW 1
static STREAM_CONFIG myDriverTxConfigLow[MY_NB_TX_ISOC_STREAMS_LOW] =
{
//  Audio  Midi  Names as they appear on computer sepperated by '\' and terminated by "\\"
    {16,   MIDI,    "CH1\\CH2\\CH3\\CH4\\CH5\\CH6\\CH7\\CH8\\CH9\\CH10\\CH11\\CH12\\CH13\\CH14\\CH15\\CH16\\\\", 0x0000},
};


#define MY_NB_RX_ISOC_STREAMS_LOW 1
static STREAM_CONFIG myDriverRxConfigLow[MY_NB_RX_ISOC_STREAMS_LOW] =
{
//  Audio  Midi  Names as they appear on computer sepperated by '\' and terminated by "\\"
    {16,   MIDI,    "CH1\\CH2\\CH3\\CH4\\CH5\\CH6\\CH7\\CH8\\CH9\\CH10\\CH11\\CH12\\CH13\\CH14\\CH15\\CH16\\\\", 0x0000},
};

static HRESULT routeLow (void)
{
    dalSetRoute(eDAL_INTERFACE_1, TX_INS0_CH0_7,  RX_AVS1_CH0_7);
    dalSetRoute(eDAL_INTERFACE_1, TX_INS1_CH0_7,  RX_AVS1_CH8_15);

    dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH0_7,  RX_INS0_CH0_7);
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

#define MY_NB_TX_ISOC_STREAMS_MID 1
static STREAM_CONFIG myDriverTxConfigMid[MY_NB_TX_ISOC_STREAMS_MID] =
{
//  Audio  Midi  Names as they appear on computer sepperated by '\' and terminated by "\\"
    {16,   MIDI,    "CH1\\CH2\\CH3\\CH4\\CH5\\CH6\\CH7\\CH8\\CH9\\CH10\\CH11\\CH12\\CH13\\CH14\\CH15\\CH16\\\\", 0x0000},
};

#define MY_NB_RX_ISOC_STREAMS_MID 1
static STREAM_CONFIG myDriverRxConfigMid[MY_NB_RX_ISOC_STREAMS_MID] =
{
//  Audio  Midi  Names as they appear on computer sepperated by '\' and terminated by "\\"
    {16,   MIDI,    "CH1\\CH2\\CH3\\CH4\\CH5\\CH6\\CH7\\CH8\\CH9\\CH10\\CH11\\CH12\\CH13\\CH14\\CH15\\CH16\\\\", 0x0000},
};

static HRESULT routeMid (void)
{
    dalSetRoute(eDAL_INTERFACE_1, TX_INS0_CH0_7,  RX_AVS1_CH0_7);
    dalSetRoute(eDAL_INTERFACE_1, TX_INS1_CH0_7,  RX_AVS1_CH8_15);

    dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH0_7,  RX_INS0_CH0_7);
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

#define MY_NB_TX_ISOC_STREAMS_HIGH 1
static STREAM_CONFIG myDriverTxConfigHigh[MY_NB_TX_ISOC_STREAMS_HIGH] =
{
//  Audio  Midi  Names as they appear on computer sepperated by '\' and terminated by "\\"
    {16,   MIDI,    "CH1\\CH2\\CH3\\CH4\\CH5\\CH6\\CH7\\CH8\\CH9\\CH10\\CH11\\CH12\\CH13\\CH14\\CH15\\CH16\\\\", 0x0000},
};

#define MY_NB_RX_ISOC_STREAMS_HIGH 1
static STREAM_CONFIG myDriverRxConfigHigh[MY_NB_RX_ISOC_STREAMS_HIGH] =
{
    {16,   MIDI,    "CH1\\CH2\\CH3\\CH4\\CH5\\CH6\\CH7\\CH8\\CH9\\CH10\\CH11\\CH12\\CH13\\CH14\\CH15\\CH16\\\\", 0x0000},
};

static HRESULT routeHigh (void)
{
    dalSetRoute(eDAL_INTERFACE_1, TX_INS0_CH0_7,  RX_AVS1_CH0_7);
    dalSetRoute(eDAL_INTERFACE_1, TX_INS1_CH0_7,  RX_AVS1_CH8_15);

    dalSetRoute(eDAL_INTERFACE_1, TX_AVS1_CH0_7,  RX_INS0_CH0_7);
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

    insSetClockPort (INS_ID0, INS_MCK_256BR, INS_BCK_64FS, INS_FSYN_LEN_32BIT, 0, 1, 0, true);

    insRxSetDataFormat  (INS_ID0, INS_LN0, INS_MODE_I2S, 0, INS_SHFL_24MSB_FRST_LJST, true);
    insRxSetDataFormat  (INS_ID0, INS_LN1, INS_MODE_I2S, 0, INS_SHFL_24MSB_FRST_LJST, true);
    insRxSetDataFormat  (INS_ID0, INS_LN2, INS_MODE_I2S, 0, INS_SHFL_24MSB_FRST_LJST, true);
    insRxSetDataFormat  (INS_ID0, INS_LN3, INS_MODE_I2S, 0, INS_SHFL_24MSB_FRST_LJST, true);
    insTxSetDataFormat  (INS_ID0, INS_LN0, INS_MODE_I2S, 0, INS_SHFL_24MSB_FRST_LJST, true);
    insTxSetDataFormat  (INS_ID0, INS_LN1, INS_MODE_I2S, 0, INS_SHFL_24MSB_FRST_LJST, true);
    insTxSetDataFormat  (INS_ID0, INS_LN2, INS_MODE_I2S, 0, INS_SHFL_24MSB_FRST_LJST, true);
    insTxSetDataFormat  (INS_ID0, INS_LN3, INS_MODE_I2S, 0, INS_SHFL_24MSB_FRST_LJST, true);

    insSetClockPort (INS_ID1, INS_MCK_256BR, INS_BCK_64FS, INS_FSYN_LEN_32BIT, 0, 1, 0, true);
    insRxSetDataFormat  (INS_ID1, INS_LN0, INS_MODE_I2S, 0, INS_SHFL_24MSB_FRST_LJST, true);
    insRxSetDataFormat  (INS_ID1, INS_LN1, INS_MODE_I2S, 0, INS_SHFL_24MSB_FRST_LJST, true);
    insRxSetDataFormat  (INS_ID1, INS_LN2, INS_MODE_I2S, 0, INS_SHFL_24MSB_FRST_LJST, true);
    insRxSetDataFormat  (INS_ID1, INS_LN3, INS_MODE_I2S, 0, INS_SHFL_24MSB_FRST_LJST, true);
    insTxSetDataFormat  (INS_ID1, INS_LN0, INS_MODE_I2S, 0, INS_SHFL_24MSB_FRST_LJST, true);
    insTxSetDataFormat  (INS_ID1, INS_LN1, INS_MODE_I2S, 0, INS_SHFL_24MSB_FRST_LJST, true);
    insTxSetDataFormat  (INS_ID1, INS_LN2, INS_MODE_I2S, 0, INS_SHFL_24MSB_FRST_LJST, true);
    insTxSetDataFormat  (INS_ID1, INS_LN3, INS_MODE_I2S, 0, INS_SHFL_24MSB_FRST_LJST, true);

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
    "Axum FireWire 16/16"
};


