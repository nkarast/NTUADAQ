/*
 * CAEN V550A CRAM Header
 * Author: Nikolaos Karastathis
 * Version: 0.0a
 */

#ifndef V550_CRAMS_H
#define V550_CRAMS_H

#ifndef __cplusplus
#define __cplusplus
#endif

#ifndef LINUX
#define LINUX //Get Types
#endif

#include "/usr/include/CAENVMElib.h"

/*
 * A successful "cheat" is to define FIFOs with a boolean variable.
 * We have FIFO-0 and FIFO-1, so we map it to "FALSE" (0) and "TRUE" (1)
 * conditions of a bool.
 *
 */

//namespace Ui{

class V550_CRAMS {

protected:
    int32_t controllerHandle;
    uint32_t baseAddress;

public:
    enum FIFOStatus {
        FIFOEmpty = 0,		//FIFO has no data
        FIFONotEmpty = 1,		// FIFO has some data
        FIFOHalfFull = 2,		// FIFO is half full
        FIFOFull = 3,		// FIFO is full
        FIFOUndefined = -1	// Cannot Determine FIFO Status (negative value means Error)
    };

    //Constructor of Class
    V550_CRAMS (int32_t ctrlHandle, uint32_t bAddress);

    // Read Fixed Code of Module @ BA + 0xFA
    CVErrorCodes ReadModuleFixedCode (uint16_t & moduleFixedCode);

    // Read Manufacturer Specifications @ BA + 0xFC
    CVErrorCodes ReadModuleManufacturerSpecs (uint16_t &moduleManufacturerSpecs);

    // Read Board's Version and Serial Number @ BA + 0xFE
    CVErrorCodes ReadModuleVersionSerial (uint16_t & moduleVersionSerial);

    // Write Test Pattern Register @ BA + 0x14/0x16 for Ch0/Ch1
    CVErrorCodes WriteTestPatterRegister (bool whichFIFO, uint16_t testPattern);

    // Read Word Counter Register @ BA + 0x10/0x12 for Ch0/Ch1
    CVErrorCodes ReadWordCounterRegister (bool whichFIFO, int &words);

    // Read FIFO's @ BA + 0x8/0xC for Ch0/Ch1
    // ReadFIFO for simple read cycle and ReadFIFOBLT for BLT Read
    CVErrorCodes ReadFIFO (bool whichFIFO, uint32_t *data);
    CVErrorCodes ReadFIFOBLT (bool whichFIFO, uint32_t *data, int size, int *count);

    // Write Clear Module Register @ BA + 0x6 - VME access clears module
    CVErrorCodes ClearModule ();	//no need to create variable

    // Read - Write Number of Detector Channels to be read out (in step of 32)
    // @ BA + 0x4  min = 32 -> DCN=1  , max = 2016 -> DCN = 63   (DCN = chan/32)
    // We need 96 channels for a gassiplex chip so numOfChansADCi = 3
    CVErrorCodes ReadNumberOfChannels (unsigned int &numOfChansADC0, unsigned int &numOfChansADC1);
    CVErrorCodes WriteNumberOfChannels (unsigned int numOfChansADC0, unsigned int numOfChansADC1);

    // Read - Write Status Register @ BA + 0x2
    CVErrorCodes ReadStatusRegister (bool & testMode, bool & memOwner, bool & DRDYChan0, bool & DRDYChan1, FIFOStatus & fifo0status, FIFOStatus & fifo1status);
    CVErrorCodes WriteStatusRegister (bool testMode, bool memOwner);

    // Write Interrupt Register @ BA + 0x0
    CVErrorCodes WriteInterruptRegister (unsigned int statusId, unsigned int interruptLevel);

    // Read - Write Pedestals Threshold @ BA + 0x2000/0x2004/0x3FFC for Pedestal & Threshold d.c.0 / Pedestal & Threshold d.c.1 / Pedestal & Threshold d.c. 2047 (CHANNEL 0)
    // @ BA + 0x4000/0x4004/0x5FFC  Pedestal & Threshold d.c.0 / Pedestal & Threshold d.c.1 / Pedestal & Threshold d.c. 2047 (CHANNEL 1)
    CVErrorCodes ReadPedestalThreshold (bool whichFIFO, unsigned int channel, unsigned int &pedestal, unsigned int &threshold);
    CVErrorCodes WritePedestalThreshold (bool whichFIFO, unsigned int channel, unsigned int pedestal, unsigned int threshold);


}; // end of class

//} //end of namespace


#endif
