/*
 * CAEN V550 CRAMS Headers' Implementation
 * Author: Nikolaos Karastathis
 * Version: 0.0a
 */

// My Includes
#include "V550_CRAMS.h"




/* In general, internal registers are accessed in D16 mode, while FIFO and
 * ped/thresh memory are accessed in D32 mode. */

//namespace Ui{


//Constructor of Class
V550_CRAMS::V550_CRAMS (int32_t ctrlHandle, uint32_t bAddress):controllerHandle (ctrlHandle),
    baseAddress (bAddress)
{
    // controllerHandle = ctrlHandle;
    // baseAddress = bAddress;
}

// Read Fixed Code of Module @ BA + 0xFA
CVErrorCodes V550_CRAMS::ReadModuleFixedCode (uint16_t & moduleFixedCode)
{

    return CAENVME_ReadCycle (controllerHandle, baseAddress + 0xFA, &moduleFixedCode, cvA32_U_DATA, cvD16);

}

// Read Manufacturer Specifications @ BA + 0xFC
CVErrorCodes V550_CRAMS::ReadModuleManufacturerSpecs (uint16_t &moduleManufacturerSpecs)
{

    return CAENVME_ReadCycle (controllerHandle, baseAddress + 0xFC, &moduleManufacturerSpecs, cvA32_U_DATA, cvD16);

}

// Read Board's Version and Serial Number @ BA + 0xFE
CVErrorCodes V550_CRAMS::ReadModuleVersionSerial (uint16_t &moduleVersionSerial)
{

    return CAENVME_ReadCycle (controllerHandle, baseAddress + 0xFE, &moduleVersionSerial, cvA32_U_DATA, cvD16);

}

// Write Test Pattern Register @ BA + 0x14/0x16 for Ch0/Ch1
CVErrorCodes V550_CRAMS::WriteTestPatterRegister (bool whichFIFO, uint16_t testPattern)
{
    uint32_t address = 0;
    whichFIFO ? address = baseAddress + 0x16 : address = baseAddress + 0x14;
    return CAENVME_WriteCycle (controllerHandle, address, &testPattern, cvA32_U_DATA, cvD16);
}

// Read Word Counter Register @ BA + 0x10/0x12 for Ch0/Ch1
CVErrorCodes V550_CRAMS::ReadWordCounterRegister (bool whichFIFO, int &words)
{
    uint32_t address = 0;
    whichFIFO ? address = baseAddress + 0x12 : address = baseAddress + 0x10;
    uint16_t pattern = 0;
    CVErrorCodes droopy = CAENVME_ReadCycle (controllerHandle, address, &pattern, cvA32_U_DATA, cvD16);
    if (droopy != cvSuccess)
        return droopy;

    words = (int) (pattern & 0x7FF);
    return droopy;		//or return cvSuccess
}

// Read FIFO's @ BA + 0x8/0xC for Ch0/Ch1 (Simple Read Cycle)
CVErrorCodes V550_CRAMS::ReadFIFO (bool whichFIFO, uint32_t * data)
{
    uint32_t address = 0;
    whichFIFO ? address = baseAddress + 0xC : address = baseAddress + 0x8;

    return CAENVME_ReadCycle (controllerHandle, address, data, cvA32_U_DATA, cvD32);

}

// Read FIFO's @ BA + 0x8/0xC for Ch0/Ch1 (FIFOBLT Read Cycle)
CVErrorCodes V550_CRAMS::ReadFIFOBLT (bool whichFIFO, uint32_t * data, int size, int *count)
{
    uint32_t address = 0;
    whichFIFO ? address = baseAddress + 0xC : address = baseAddress + 0x8;
    return CAENVME_FIFOBLTReadCycle (controllerHandle, address, data, size, cvA32_U_BLT, cvD32, count);
    //changed that to FIFOBLTReadCycle from BLTReadCycle. It's new function after 2.3 of lib.
}

// Write Clear Module Register @ BA + 0x6 - VME access clears module
CVErrorCodes V550_CRAMS::ClearModule ()
{
    uint16_t pattern = 0;
    return CAENVME_WriteCycle (controllerHandle, baseAddress + 0x6, &pattern, cvA32_U_DATA, cvD16);
}

// Read Number of Detector Channels to be read out (in step of 32)
// @ BA + 0x4  min = 32 -> DCN=1  , max = 2016 -> DCN = 63   (DCN = chan/32)
// We need 96 channels for a gassiplex chip so numOfChansADCi = 3
CVErrorCodes V550_CRAMS::ReadNumberOfChannels (unsigned int &numOfChansADC0, unsigned int &numOfChansADC1)
{
    uint16_t pattern = 0;
    CVErrorCodes droopy = CAENVME_ReadCycle (controllerHandle, baseAddress + 0x4, &pattern, cvA32_U_DATA, cvD16);
    if (droopy != cvSuccess)
        return droopy;

    numOfChansADC0 = pattern & 0x3F;	//0x3F = (bin) 111111
    numOfChansADC1 = (pattern & 0xFC0) >> 6;	//0xFC0 = (bin) 111111000000
    return droopy;
}

// Write Number of Detector Channels to be read out (in step of 32)
// @ BA + 0x4  min = 32 -> DCN=1  , max = 2016 -> DCN = 63   (DCN = chan/32)
// We need 96 channels for a gassiplex chip so numOfChansADCi = 3
CVErrorCodes V550_CRAMS::WriteNumberOfChannels (unsigned int numOfChansADC0, unsigned int numOfChansADC1)
{
    if (numOfChansADC0 > 63)
        numOfChansADC0 = 63;

    if (numOfChansADC1 > 63)
        numOfChansADC1 = 63;

    uint16_t pattern = numOfChansADC0 | (numOfChansADC1 << 6);

    return CAENVME_WriteCycle (controllerHandle, baseAddress + 0x4, &pattern, cvA32_U_DATA, cvD16);
}

// Read Status Register @ BA + 0x02
CVErrorCodes V550_CRAMS::ReadStatusRegister (bool & testMode, bool & memOwner, bool & DRDYChan0, bool & DRDYChan1, FIFOStatus & fifo0status, FIFOStatus & fifo1status)
{
    uint16_t pattern = 0;
    CVErrorCodes droopy = CAENVME_ReadCycle (controllerHandle, baseAddress + 0x2, &pattern, cvA32_U_DATA, cvD16);
    if (droopy != cvSuccess)
        return droopy;

    testMode = pattern & 0x1;
    memOwner = pattern & 0x2;
    DRDYChan0 = !(pattern & 0x4);
    DRDYChan1 = !(pattern & 0x8);

    // FIFOStatus fifo0status
    uint16_t fifo0pattern = pattern & 0x150;

    if (fifo0pattern == 0x150)
        fifo0status = FIFONotEmpty;
    else if (fifo0pattern == 0x140)
        fifo0status = FIFOEmpty;
    else if (fifo0pattern == 0x110)
        fifo0status = FIFOHalfFull;
    else if (fifo0pattern == 0x10)
        fifo0status = FIFOFull;	// or 0x50? (mine)
    else
        fifo0status = FIFOUndefined;

    // FIFOStatus fifo1status

    uint16_t fifo1pattern = pattern & 0x2A0;

    if (fifo1pattern == 0x2A0)
        fifo1status = FIFONotEmpty;
    else if (fifo1pattern == 0x280)
        fifo1status = FIFOEmpty;
    else if (fifo1pattern == 0x220)
        fifo1status = FIFOHalfFull;
    else if (fifo1pattern == 0x20)
        fifo1status = FIFOFull;	// or 0xA0? (mine)
    else
        fifo1status = FIFOUndefined;

    return droopy;

}



// Write Status Register @ BA + 0x02
CVErrorCodes V550_CRAMS::WriteStatusRegister (bool testMode, bool memOwner)
{
    uint16_t pattern = (memOwner << 1) | testMode;
    return CAENVME_WriteCycle (controllerHandle, baseAddress + 0x2, &pattern, cvA32_U_DATA, cvD16);

}

// Write Interrupt Register @ BA + 0x0 [Not sure about that]
CVErrorCodes V550_CRAMS::WriteInterruptRegister (unsigned int statusId, unsigned int interruptLevel)
{
    uint16_t pattern = 0;
    if (statusId > 255)
        statusId = 255;		//TODO: maybe throw an error instead of reassigning
    if (interruptLevel > 7)
        interruptLevel = 7;	//TODO: maybe throw an error instead of reassigning
    pattern = (interruptLevel << 8) | statusId;

    return CAENVME_WriteCycle (controllerHandle, baseAddress, &pattern, cvA32_U_DATA, cvD16);
}


/* Set Pedestal And Thresholds Algorithm
        * The idea behind that is pretty simple. Numbers don't have a certain base
        * humans just use representations of numbers for their own convenienve.
        * So if a numbered address in hex is incremented by 4, the increment will be
        * the same in dec.
        *
        * The algorithm for accessing the addresses of different channels is:
        * 1) Take the BASE address of module
        * 2) ADD with the first Address of PED/THRESH register (2000 for chan0, 4000 for chan1)
        * 3) Take the number of channel (0-2047)
        * 4) Left bit shift by 2 and add it to the whole address
        *
        * And for some crazy reason that works!
        *
        * Use it as black box. After all, remember: ignorance is bliss!
        */

// Read Pedestals Threshold @ BA + 0x2000/0x2004/0x3FFC for Pedestal & Threshold d.c.0 / Pedestal & Threshold d.c.1 / Pedestal & Threshold d.c. 2047 (CHANNEL 0)
// @ BA + 0x4000/0x4004/0x5FFC  Pedestal & Threshold d.c.0 / Pedestal & Threshold d.c.1 / Pedestal & Threshold d.c. 2047 (CHANNEL 1)
CVErrorCodes V550_CRAMS::ReadPedestalThreshold (bool whichFIFO, unsigned int channel, unsigned int &pedestal, unsigned int &threshold)
{
    if (channel > 2047)
        channel = 2047;

    uint32_t address = 0;
    whichFIFO ? address = baseAddress + 0x4000 + (channel << 2) : address =
                baseAddress + 0x2000 + (channel << 2);

    uint32_t pattern = 0;
    CVErrorCodes droopy = CAENVME_ReadCycle (controllerHandle, address, &pattern, cvA32_U_DATA, cvD32);

    if (droopy != cvSuccess)
        return droopy;


    threshold = pattern & 0xFFF;
    pedestal = (pattern & 0xFFF000) >> 12;	//changed that from 0xFFF

    return droopy;

}	//read_ped_thres

// Write Pedestals Threshold @ BA + 0x2000/0x2004/0x3FFC for Pedestal & Threshold d.c.0 / Pedestal & Threshold d.c.1 / Pedestal & Threshold d.c. 2047 (CHANNEL 0)
// @ BA + 0x4000/0x4004/0x5FFC  Pedestal & Threshold d.c.0 / Pedestal & Threshold d.c.1 / Pedestal & Threshold d.c. 2047 (CHANNEL 1)
CVErrorCodes V550_CRAMS::WritePedestalThreshold (bool whichFIFO, unsigned int channel, unsigned int pedestal, unsigned int threshold)
{
    if (channel > 2047)
        channel = 2047;
    if (threshold > 4095)
        threshold = 4095;		//that's a dozen of "1" = max value that a 12bit reg can hold
    if (pedestal > 4095)
        pedestal = 4095;		//that's a dozen of "1" = max value that a 12bit reg can hold
    uint32_t address = 0;
    whichFIFO ? address = baseAddress + 0x4000 + (channel << 2) : address = baseAddress + 0x2000 + (channel << 2);

    uint32_t pattern = threshold | (pedestal << 12);
    return CAENVME_WriteCycle (controllerHandle, address, &pattern, cvA32_U_DATA, cvD32);
}


//}
