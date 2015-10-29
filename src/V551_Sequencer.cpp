/*
 * V551 Sequencer Header Implementation
 * Author: Nikolaos Karastathis
 * Version: 0.0a
 */

// My Includes
#include "V551_Sequencer.h"


//namespace Ui{

// Constructor
V551_Sequencer::V551_Sequencer (int32_t ctrlHandle, uint32_t bAddress):controllerHandle (ctrlHandle), baseAddress (bAddress)
{
    //controllerHandle = ctrlHandle;
    //baseAddress = bAddress;
}

// Read Fixed Code of Module @ BA + 0xFA
CVErrorCodes V551_Sequencer::ReadModuleFixedCode (uint16_t & moduleFixedCode)
{
    return CAENVME_ReadCycle (controllerHandle, baseAddress + 0xFA, &moduleFixedCode, cvA32_U_DATA, cvD16);
}

// Read Manufacturer's Specs of Module @ BA + FC
CVErrorCodes V551_Sequencer::ReadModuleManufacturerSpecs (uint16_t & moduleManufacturerSpecs)
{
    return CAENVME_ReadCycle (controllerHandle, baseAddress + 0xFC, &moduleManufacturerSpecs, cvA32_U_DATA, cvD16);
}

//	Read Version and Serial number of Module @ BA + FE
CVErrorCodes V551_Sequencer::ReadModuleVersionSerial (uint16_t & moduleVersionSerial)
{
    return CAENVME_ReadCycle (controllerHandle, baseAddress + 0xFE, &moduleVersionSerial, cvA32_U_DATA, cvD16);
}

//Interrupts
CVErrorCodes V551_Sequencer::WriteInterruptVectorRegister (unsigned int statusId)
{
    if (statusId > 255)
        statusId = 255;		//maximum value of statusId is 255

    return CAENVME_WriteCycle (controllerHandle, baseAddress, &statusId, cvA32_U_DATA, cvD16);
}

// Interrupt Level @ BA + 0x2
CVErrorCodes V551_Sequencer::WriteInterruptLevelRegister (unsigned int interruptLevel)
{
    if (interruptLevel > 7)
        interruptLevel = 7;	// 7 is the max level of IACK cycle

    return CAENVME_WriteCycle (controllerHandle, baseAddress + 0x2, &interruptLevel, cvA32_U_DATA, cvD16);
}

//Clear Module -- Clears (just) on access @ BA + 0x4
CVErrorCodes V551_Sequencer::ClearModule ()
{
    uint16_t pattern = 0;	//16bit -> 16 zeros, needed just for access @ BA+0x4

    return CAENVME_WriteCycle (controllerHandle, baseAddress + 0x4, &pattern, cvA32_U_DATA, cvD16);

}

//Software Trigger -- Access starts conversion cycle @ BA + 0x6
CVErrorCodes V551_Sequencer::SoftwareTrigger ()
{
    uint16_t pattern = 0;

    return CAENVME_WriteCycle (controllerHandle, baseAddress + 0x6, &pattern, cvA32_U_DATA, cvD16);
}

// Read Status Register @ BA+0x8
CVErrorCodes V551_Sequencer::ReadStatusRegister (bool & internalDelay, bool & veto, bool & autoTrigger, bool & dataReady, bool & busy, bool & activeSequence)
{
    uint16_t pattern = 0;	//initialize 16bit pattern by filling it with zeros and get the pattern from...

    CVErrorCodes droopy = CAENVME_ReadCycle (controllerHandle, baseAddress + 0x8, &pattern, cvA32_U_DATA, cvD16);
    if (droopy != cvSuccess)
        return droopy;

    //Now check with bitwise "AND" if each bit is set:
    internalDelay = pattern & 0x1;	//checks LSB
    veto = pattern & 0x2;
    autoTrigger = pattern & 0x4;
    dataReady = pattern & 0x8;
    busy = pattern & 0x10;
    activeSequence = pattern & 0x20;

    return droopy;
}

// Write Status Register @ BA + 0x8
CVErrorCodes V551_Sequencer::WriteStatusRegister (bool internalDelay, bool veto, bool autoTrigger)
{
    uint16_t pattern = (autoTrigger << 2) | (veto << 1) | (internalDelay);

    return CAENVME_WriteCycle (controllerHandle, baseAddress + 0x8, &pattern, cvA32_U_DATA, cvD16);
}

// Read Test Register @ BA+0xA
CVErrorCodes V551_Sequencer::ReadTestRegister (bool & testMode, bool & clockLevel, bool & shiftInLevel, bool & testPulseLevel)
{
    uint16_t pattern = 0;
    CVErrorCodes droopy = CAENVME_ReadCycle (controllerHandle, baseAddress + 0xA, &pattern, cvA32_U_DATA, cvD16);
    if (droopy != cvSuccess)
        return droopy;

    testMode = pattern & 0x1;
    clockLevel = pattern & 0x2;
    shiftInLevel = pattern & 0x4;
    testPulseLevel = pattern & 0x8;

    return droopy;

}

// Write Test Register @ BA+0xA
CVErrorCodes V551_Sequencer::WriteTestRegister (bool testMode, bool clockLevel, bool shiftInLevel, bool testPulseLevel)
{
    uint16_t pattern = (testPulseLevel << 3) | (shiftInLevel << 2) | (clockLevel << 1) | testMode;
    return CAENVME_WriteCycle (controllerHandle, baseAddress + 0xA, &pattern, cvA32_U_DATA, cvD16);
}

// Read Number of channels @ BA + 0xC
CVErrorCodes V551_Sequencer::ReadNumberOfChannels (unsigned int &numberOfChannels)
{
    uint16_t pattern = 0;
    CVErrorCodes droopy = CAENVME_ReadCycle (controllerHandle, baseAddress + 0xC, &pattern,
                                             cvA32_U_DATA, cvD16);
    if (droopy != cvSuccess)
        return droopy;

    numberOfChannels = pattern & 0x7FF;	//0x7FF = (dec) 2047 = (bin) 11111111111
    return droopy;
}

// Write Number of channels @ BA + 0xC
CVErrorCodes V551_Sequencer::WriteNumberOfChannels (unsigned int numberOfChannels)
{
    if (numberOfChannels > 2047)
        numberOfChannels = 2047;	// max number of channels is 2047

    return CAENVME_WriteCycle (controllerHandle, baseAddress + 0xC, &numberOfChannels, cvA32_U_DATA, cvD16);
}


// Read T1 Register @ BA + 0xE (T1 = Trigger to Hold Delay)
// t1 = 500 + T1*10 ns  , 0<=T1<=255
CVErrorCodes V551_Sequencer::ReadT1Register (unsigned int &T1)
{
    uint16_t pattern = 0;

    CVErrorCodes droopy = CAENVME_ReadCycle (controllerHandle, baseAddress + 0xE, &pattern, cvA32_U_DATA, cvD16);

    if (droopy != cvSuccess)
        return droopy;

    T1 = pattern & 0xFF;	// 0xFF = (dec) 255 = (bin) 111111111

    return droopy;
}

// Write T1 Register @ BA + 0x0E (T1 = Trigger to Hold Delay)
// t1 = 500 + T1*10 ns  , 0<=T1<=255
CVErrorCodes V551_Sequencer::WriteT1Register (unsigned int T1)
{
    if (T1 > 255)
        T1 = 255;			//no need for <0 as T1 is UNsigned int

    return CAENVME_WriteCycle (controllerHandle, baseAddress + 0xE, &T1, cvA32_U_DATA, cvD16);
}

// Read T2 Register @ BA + 0x10 (T2 = Hold to Sequence Delay)
// t2 = 130 + T2*20 (+/-) 10 ns , 10<=T2<=511
CVErrorCodes V551_Sequencer::ReadT2Register (unsigned int &T2)
{
    uint16_t pattern = 0;

    CVErrorCodes droopy = CAENVME_ReadCycle (controllerHandle, baseAddress + 0x10, &pattern, cvA32_U_DATA, cvD16);
    if (droopy != cvSuccess)
        return droopy;

    T2 = pattern & 0x1FF;	// 0x1FF = (dec) 511 = (bin) 111111111

    return droopy;
}

// Write T2 Register @ BA + 0x10 (T2 = Hold to Sequence Delay)
// t2 = 130 + T2*20 (+/-) 10 ns , 10<=T2<=511
CVErrorCodes V551_Sequencer::WriteT2Register (unsigned int T2)
{
    if (T2 > 511)
        T2 = 511;
    if (T2 < 10)
        T2 = 10;

    return CAENVME_WriteCycle (controllerHandle, baseAddress + 0x10, &T2, cvA32_U_DATA, cvD16);
}

// Read T3 Register @ BA + 0x12 (T3 = Active Clock Duration)
// t3 = T3*20 ns , 1<=T3<=T4 , T3<=255
CVErrorCodes V551_Sequencer::ReadT3Register (unsigned int &T3)
{
    uint16_t pattern = 0;
    CVErrorCodes droopy = CAENVME_ReadCycle (controllerHandle, baseAddress + 0x12, &pattern, cvA32_U_DATA, cvD16);
    if (droopy != cvSuccess)
        return droopy;

    T3 = pattern & 0xFF;
    return droopy;
}

// Write T3 Register @ BA + 0x12 (T3 = Active Clock Duration)
// t3 = T3*20 ns , 1<=T3<=T4 , T3<=255
CVErrorCodes V551_Sequencer::WriteT3Register (unsigned int T3)
{
    if (T3 > 255)
        T3 = 255;
    if (T3 < 1)
        T3 = 1;

    return CAENVME_WriteCycle (controllerHandle, baseAddress + 0x12, &T3, cvA32_U_DATA, cvD16);
}

// Read T4 Register @ BA + 0x14 (T4 = Period of CLOCK and CONVERT sequence)
// t4 = 20 + T4*20 ns , 1<=T4<=511
CVErrorCodes V551_Sequencer::ReadT4Register (unsigned int &T4)
{
    uint16_t pattern = 0;
    CVErrorCodes droopy = CAENVME_ReadCycle (controllerHandle, baseAddress + 0x14, &pattern, cvA32_U_DATA, cvD16);

    if (droopy != cvSuccess)
        return droopy;

    T4 = pattern & 0x1FF;
    return droopy;
}

// Write T4 Register @ BA + 0x14 (T4 = Period of CLOCK and CONVERT sequence)
// t4 = 20 + T4*20 ns , 1<=T4<=511
CVErrorCodes V551_Sequencer::WriteT4Register (unsigned int T4)
{
    if (T4 < 1)
        T4 = 1;
    if (T4 > 511)
        T4 = 511;

    return CAENVME_WriteCycle (controllerHandle, baseAddress + 0x14, &T4, cvA32_U_DATA, cvD16);
}

// Read T5 Register @ BA + 0x16 (T5 = Clock to Convert Delay)
// t5 = 40 + T5*20 ns , 2<=T5<=511
CVErrorCodes V551_Sequencer::ReadT5Register (unsigned int &T5)
{
    uint16_t pattern = 0;
    CVErrorCodes droopy = CAENVME_ReadCycle (controllerHandle, baseAddress + 0x16, &pattern, cvA32_U_DATA, cvD16);
    if (droopy != cvSuccess)
        return droopy;

    T5 = pattern & 0x1FF;
    return droopy;
}

// Write T5 Register @ BA + 0x16 (T5 = Clock to Convert Delay)
// t5 = 40 + T5*20 ns , 2<=T5<=511
CVErrorCodes V551_Sequencer::WriteT5Register (unsigned int T5)
{
    if (T5 < 2)
        T5 = 2;
    if (T5 > 511)
        T5 = 511;

    return CAENVME_WriteCycle (controllerHandle, baseAddress + 0x16, &T5, cvA32_U_DATA, cvD16);
}

// Write Internal DAC -> Full value 0xFFF = (dec) 4095 = +5V 50mA (max)
CVErrorCodes V551_Sequencer::WriteInternalDAC (unsigned int DACValue)
{
    if (DACValue > 4095)
        DACValue = 4095;

    return CAENVME_WriteCycle (controllerHandle, baseAddress + 0x18, &DACValue, cvA32_U_DATA, cvD16);
}


//}				//end of namespace
