//===========================================================================
//
// This confidential and proprietary software may be used only as authorised
// by a licensing agreement from TC Applied Technologies Ltd.
//
// (C) COPYRIGHT 2004 TC Applied Technologies Ltd. (ALL RIGHTS RESERVED)
//
// Unauthorized use, duplication or distribution of this software is
// strictly prohibited by law.
//
// The entire notice above must be reproduced on all authorised copies and
// copies may only be made to the extent permitted by a licensing agreement
// from TC Applied Technologies Ltd.
//
/****************************************************************************
 * board specific configuration and routines

 this is where the OEM will put his board specific pin configurations.

****************************************************************************/

#include "TCTasking.h"
#include "TCTypes.h"
#include "coreDefs.h"
#include "targetBoard.h"
#include "lhl.h"
#include "lhlbri.h"
#include "targetConfigCSR.h"
#include "lhlIRM.h"


static uint32 audioPortDefault;

/* Multifunction pin configuration
*   every boards needs a configuration for multifunction pins.
*   you *must* change these settings to reflect your hardware
*
*/
void targetBoardInit(void)
{
    uint32 chipID;
    //Example of target board init.

    chipID = *((volatile uint32 *) GPCSR_CHIP_ID);

    if ((chipID & 0xf)== 0xf) //DICE JR
    {
        //setting up chip select NCS2 for DICE JR only
        *((volatile uint32 *) MEM_SCSLR2) = 0x02080000;
        *((volatile uint32 *) MEM_SMSKR2) = 0x00000020;//SRAM, 512kb, set 0
        *((volatile uint32 *) MEM_SMTMGR_SET0) = 0x10000841;
        *((volatile uint32 *) MEM_SMCTLR) = 0x20f; //set0=8bit all other sets 16 bits


        //------------------------------------------------------
        //                3           2            1           0
        //        Bit No 1098 7654 3210 9876 5432 1098 7654 3210
        //------------------------------------------------------
        // GPCSR_AUDIO_SEL  0000 0000 0000 0011 1110 1000 1010 1010
        //             HEX     0    0    0    3    e    8    a    a
        //---------------------------------------------------------
        // AES0_RX          .... .... .... .... .... .... .... ..00  AES0 Rx Source is off
        // AES1_RX          .... .... .... .... .... .... .... 00..  AES1 Rx Source is off
        // AES2_RX          .... .... .... .... .... .... ..00 ....  AES2 Rx Source is off
        // AES3_RX          .... .... .... .... .... .... 00.. ....  AES3 Rx Source is off
        // AO0_0            .... .... .... .... .... ...0 .... ....  Port0 Line 0 is InS0_0
        // AO0_1            .... .... .... .... .... ..0. .... ....  Port0 Line 1 is InS0_1
        // AO0_2            .... .... .... .... .... 00.. .... ....  Port0 Line 2 is InS0_2
        // AO0_3            .... .... .... .... ..00 .... .... ....  Port0 Line 3 is InS0_3
        // AO1_0            .... .... .... .... .0.. .... .... ....  Port1 Line 0 is InS1_0
        // AO1_1            .... .... .... .... 0... .... .... ....  Port1 Line 1 is InS1_1
        // AO1_2            .... .... .... ...0 .... .... .... ....  Port1 Line 2 is InS1_2
        // AO1_3            .... .... .... ..0. .... .... .... ....  Port1 Line 3 is InS1_3
        audioPortDefault = 0x0000;



        //DICE JR configuration, use SPI b for EVM
        //------------------------------------------------------
        //                3           2            1           0
        //        Bit No 1098 7654 3210 9876 5432 1098 7654 3210
        //------------------------------------------------------
        // GPCSR_GPIO_SEL   0000 0000 0000 0001 1110 0011 0100 1100
        //             HEX     0    0    0    1    e    3    4    c
        //---------------------------------------------------------
        // GPIO0            .... .... .... .... .... .... .... ...0  No CLKE, use GPIO
        // SPI              .... .... .... .... .... .... .... .00.  No SPI
        // GPIO1            .... .... .... .... .... .... .... 0...  No CS2, use GPIO
        // GPIO2            .... .... .... .... .... .... ...0 ....  GPIO2
        // GPIO3            .... .... .... .... .... .... ..0. ....  GPIO3
        // GPIO4            .... .... .... .... .... .... 01.. ....  EXTFBR in/WCK
        // GPIO5            .... .... .... .... .... ..11 .... ....  WCK out
        // GPIO6            .... .... .... .... .... .1.. .... ....  MCK1
        // GPIO7            .... .... .... .... .... 1... .... ....  FCK1
        // GPIO8            .... .... .... .... ...1 .... .... ....  BCK1
        // ENC2             .... .... .... .... ..1. .... .... ....  No Encoder, use GPIO
        // GPIO12           .... .... .... .... .1.. .... .... ....  WCKI
        // GPIO13           .... .... .... .... 1... .... .... ....  WCKO
        // ENC1             .... .... .... ...1 .... .... .... ....  No Encoder, use GPIO
        *((volatile uint32 *) GPCSR_GPIO_SEL) = 0x1ff40;
    }
    else //DICE Mini
    {
        //------------------------------------------------------
        //                3           2            1           0
        //        Bit No 1098 7654 3210 9876 5432 1098 7654 3210
        //------------------------------------------------------
        // GPCSR_AUDIO_SEL  0000 0000 0000 0011 1101 1000 0100 0000
        //             HEX     0    0    0    3    d    8    4    0
        //---------------------------------------------------------
        // AES0_RX          .... .... .... .... .... .... .... ..00  AES0 Rx Source is off
        // AES1_RX          .... .... .... .... .... .... .... 00..  AES1 Rx Source is off
        // AES2_RX          .... .... .... .... .... .... ..00 ....  AES2 Rx Source is off
        // AES3_RX          .... .... .... .... .... .... 01.. ....  AES3 Rx Source is Port0
        // AO0_0            .... .... .... .... .... ...0 .... ....  Port0 Line 0 is InS0_0
        // AO0_1            .... .... .... .... .... ..0. .... ....  Port0 Line 1 is InS0_1
        // AO0_2            .... .... .... .... .... 10.. .... ....  Port0 Line 2 is ADAT0
        // AO0_3            .... .... .... .... ..01 .... .... ....  Port0 Line 3 is AES3
        // AO1_0            .... .... .... .... .1.. .... .... ....  Port1 Line 0 is AES0
        // AO1_1            .... .... .... .... 1... .... .... ....  Port1 Line 1 is AES1
        // AO1_2            .... .... .... ...1 .... .... .... ....  Port1 Line 2 is AES2
        // AO1_3            .... .... .... ..1. .... .... .... ....  Port1 Line 3 is AES3
        audioPortDefault = 0x3d840;




        //DICE Mini configuration, use SPI a for EVM
        //------------------------------------------------------
        //                3           2            1           0
        //        Bit No 1098 7654 3210 9876 5432 1098 7654 3210
        //------------------------------------------------------
        // GPCSR_GPIO_SEL   0000 0000 0000 0001 1110 0011 0100 0010
        //             HEX     0    0    0    1    e    3    4    2
        //---------------------------------------------------------
        // GPIO0            .... .... .... .... .... .... .... ...0  GPIO0 not CLKE, NOT ON MINI
        // SPI              .... .... .... .... .... .... .... .01.  SPI a
        // GPIO1            .... .... .... .... .... .... .... 0...  GPIO1 (don't care SPI)
        // GPIO2            .... .... .... .... .... .... ...0 ....  GPIO2 (don't care SPI)
        // GPIO3            .... .... .... .... .... .... ..0. ....  GPIO3
        // GPIO4            .... .... .... .... .... .... 01.. ....  EXTFBR in/WCK
        // GPIO5            .... .... .... .... .... ..11 .... ....  WCK out
        // GPIO6            .... .... .... .... .... .0.. .... ....  GPIO6
        // GPIO7            .... .... .... .... .... 0... .... ....  GPIO7
        // GPIO8            .... .... .... .... ...0 .... .... ....  GPIO8
        // ENC2             .... .... .... .... ..1. .... .... ....  No Encoder, use GPIO
        // GPIO12           .... .... .... .... .1.. .... .... ....  WCKI, NOT ON MINI
        // GPIO13           .... .... .... .... 1... .... .... ....  WCKO, NOT ON MINI
        // ENC1             .... .... .... ...1 .... .... .... ....  No Encoder, use GPIO, NOT ON MINI
        *((volatile uint32 *) GPCSR_GPIO_SEL) = 0x1e342;
    }

    *((volatile uint32 *) GPCSR_AUDIO_SEL) = audioPortDefault;

    //---------------------------------------------------------
    //                   3           2            1           0
    //           Bit No 1098 7654 3210 9876 5432 1098 7654 3210
    //---------------------------------------------------------
    //                  0000 0000 0000 0000 0000 0000 0000 1000
    // GPIO_A_DDR  HEX     0    0    0    0    0    0    0    8
    //---------------------------------------------------------
    // GPIO0            .... .... .... .... .... .... .... ...0  Input
    // GPIO1            .... .... .... .... .... .... .... ..1.  Input
    // GPIO2            .... .... .... .... .... .... .... .1..  Input (pin used for other func)
    // GPIO3            .... .... .... .... .... .... .... 1...  Output, controls SPI on Mini Microboard
    // GPIO4            .... .... .... .... .... .... ...1 ....  Input
    // GPIO5            .... .... .... .... .... .... ..1. ....  Input
    // GPIO6            .... .... .... .... .... .... .0.. ....  Input
    // GPIO7            .... .... .... .... .... .... 0... ....  Input
    // GPIO8            .... .... .... .... .... ...0 .... ....  Input
    // GPIO9            .... .... .... .... .... ..1. .... ....  Input
    // GPIO10           .... .... .... .... .... .1.. .... ....  Input
    // GPIO11           .... .... .... .... .... 1... .... ....  Input
    // GPIO12           .... .... .... .... ...0 .... .... ....  Input (pin used for other func)
    // GPIO13           .... .... .... .... ..0. .... .... ....  Input (pin used for other func)
    // GPIO14           .... .... .... .... .0.. .... .... ....  Input (pin used for other func)
    *((volatile uint32 *) GPIO_A_DDR) = 0xe3e;
    *((volatile uint32 *) GPIO_A_DR) = 0x0;   //turn off all GPIO outputs

}

static BOOL targetAVSTriggerEnabled;
// For debugging, enable GPIO for AVS error trigger
void targetEnableAVSTrigger (void)
{
    //This board uses the WCLK out BNC for this, that is GPIO5
    *((volatile uint32 *) GPCSR_GPIO_SEL) = (*((volatile uint32 *) GPCSR_GPIO_SEL) & (~0x300)); //GPIO5 functionality
    *((volatile uint32 *) GPIO_A_DDR) |= 1<<5;
    targetAVSTriggerEnabled = TRUE;
}

void targetSignalAVSTrigger (void)
{
    if (targetAVSTriggerEnabled)
    {
        *((volatile uint32 *) GPIO_A_DR) |= 1<<5; //Set GPIO5 (WCKO)
        *((volatile uint32 *) GPIO_A_DR) &= ~(1<<5); //Clear GPIO5 (WCKO)
    }
}


// Some of the modes use the first optical as SPDIF instead of ADAT (Port0-2)

void targetChangeAudioPorts (uint8 mode)
{
    uint32 port;
    switch (mode)
    {
        default:
        case APM_NORMAL: port = audioPortDefault; break;
        case APM_TOS:    port = (audioPortDefault & 0xfffff3cf) | 0x00000410; break;
        case APM_ALL_INS:port = 0; break;
    }
    *((volatile uint32 *) GPCSR_AUDIO_SEL) = port;
}


BOOL isChipDiceJR (void)
{
    uint32 chipID;

    chipID = *((volatile uint32 *) GPCSR_CHIP_ID);

    return (chipID== 0x0100000f);
}


static uint16 ledMsk;

static void updateLED(void)
{
    *((volatile uint32 *) GPIO_A_DR) = ledMsk;
    return;
}

void targetSetAllLED (uint16 msk)
{
    if (ledMsk != msk)
    {
        ledMsk = msk;
        updateLED();
    }
}

void targetSetLED (TGT_LED led, TGT_LED_STATE state)
{
    uint16 msk;

    msk = ledMsk;
    if (state==TGT_LED_OFF)
        msk &= ~(1<<led);
    else if (state==TGT_LED_ON)
        msk |= 1<<led;
    else if(state==TGT_LED_TGL)
        msk ^= 1<<led;
    targetSetAllLED (msk);
}


// This function is called by the system when it needs to perform a
// soft reset. If you need to reset any specific hardware do it here
void targetBoardPrepareReset(void)
{
    //this function will assure that the board is ready for reset
  targetSetMinConfigROM();
  lhlSetIRMEnabled(FALSE);
  lhlBriForceBusReset();

  TCTaskWait(500);  //enough for computer to determine the device has gone with new LLC fix.
}

