/*
 * V462 Gate Generator Headers' Implementation
 * Author: Nikolaos Karastathis (c) 2010
 * Version: 0.0a
 *
 */

// My Includes
#include "V462_GateGenerator.h"



//namespace Ui{


//constructor
V462_GateGenerator::V462_GateGenerator (int32_t ctrlHandle, uint32_t bAddress):controllerHandle(ctrlHandle), baseAddress (bAddress)
{
    //controllerHandle = ctrlHandle;
    //baseAddress = bAddress;
}

// Read Fixed Code of Module @ BA + 0xFA
CVErrorCodes V462_GateGenerator::ReadModuleFixedCode (uint16_t &moduleFixedCode)
{
    return CAENVME_ReadCycle (controllerHandle, baseAddress + 0xFA, &moduleFixedCode, cvA24_U_DATA, cvD16);
}

// Read Manufacturer's Specs of Module @ BA + FC
CVErrorCodes V462_GateGenerator::ReadModuleManufacturerSpecs (uint16_t &moduleManufacturerSpecs)
{
    return CAENVME_ReadCycle (controllerHandle, baseAddress + 0xFC, &moduleManufacturerSpecs, cvA24_U_DATA, cvD16);
}

// Read Version and Serial number of Module @ BA + FE
CVErrorCodes V462_GateGenerator::ReadModuleVersionSerial (uint16_t &moduleVersionSerial)
{
    return CAENVME_ReadCycle (controllerHandle, baseAddress + 0xFE, &moduleVersionSerial, cvA24_U_DATA, cvD16);
}

// Ch0 - Upper Display @ BA + 0x2
CVErrorCodes V462_GateGenerator::SetChannel0UpperDisplay (unsigned int upperDisplayCh0)
{
    return CAENVME_WriteCycle (controllerHandle, baseAddress + 0x2, &upperDisplayCh0, cvA24_U_DATA, cvD16);

}

// Ch0 - Lower Display @ BA + 0x4
CVErrorCodes V462_GateGenerator::SetChannel0LowerDisplay (unsigned int lowerDisplayCh0)
{
    return CAENVME_WriteCycle (controllerHandle, baseAddress + 0x4, &lowerDisplayCh0, cvA24_U_DATA, cvD16);
}



// Ch1 - Upper Display @ BA + 0x6
CVErrorCodes V462_GateGenerator::SetChannel1UpperDisplay (unsigned int upperDisplayCh1)
{
    return CAENVME_WriteCycle (controllerHandle, baseAddress + 0x6, &upperDisplayCh1, cvA24_U_DATA, cvD16);
}


// Ch1 - Lower Display @ BA + 0x8
CVErrorCodes V462_GateGenerator::SetChannel1LowerDisplay (unsigned int lowerDisplayCh1)
{
    return CAENVME_WriteCycle (controllerHandle, baseAddress + 0x8, &lowerDisplayCh1, cvA24_U_DATA, cvD16);
}

// Generate Test Pulse
CVErrorCodes V462_GateGenerator::GenerateTestPulse ()
{
    uint16_t test = 1536;
    return CAENVME_WriteCycle (controllerHandle, baseAddress, &test, cvA24_U_DATA, cvD16);
}

//}//end of namespace
