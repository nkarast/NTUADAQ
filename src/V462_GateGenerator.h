/*
 * V462 Dual Gate Generator Headers
 *
 * Author:  Nikolaos Karastathis (c) 2010
 * Version: 0.0a
 *
 */


#ifndef V462_GATEGENERATOR_H
#define V462_GATEGENERATOR_H

#ifndef __cplusplus
#define __cplusplus
#endif

#ifndef LINUX
#define LINUX
#endif

#include "/usr/include/CAENVMElib.h"


//namespace Ui{


class V462_GateGenerator
{
protected:
    int32_t controllerHandle;
    uint32_t baseAddress;

public:
    //constructor
    V462_GateGenerator (int32_t ctrlHandle, uint32_t bAddress);

    // Read Fixed Code of Module @ BA + 0xFA
    CVErrorCodes ReadModuleFixedCode (uint16_t & moduleFixedCode);

    // Read Manufacturer's Specs of Module @ BA + FC
    CVErrorCodes ReadModuleManufacturerSpecs (uint16_t &moduleManufacturerSpecs);

    // Read Version and Serial number of Module @ BA + FE
    CVErrorCodes ReadModuleVersionSerial (uint16_t & moduleVersionSerial);

    // Ch0 - Upper Display @ BA + 0x2
    CVErrorCodes SetChannel0UpperDisplay (unsigned int upperDisplayCh0);

    // Ch0 - Lower Display @ BA + 0x4
    CVErrorCodes SetChannel0LowerDisplay (unsigned int lowerDisplayCh0);

    // Ch1 - Lower Display @ BA + 0x6
    CVErrorCodes SetChannel1UpperDisplay (unsigned int upperDisplayCh1);

    // Ch1 - Lower Display @ BA + 0x8
    CVErrorCodes SetChannel1LowerDisplay (unsigned int lowerDisplayCh1);

    //Create Test Pulse (for Debugging)
    CVErrorCodes GenerateTestPulse ();

};//end of class V462




//}//end of namespace

#endif
