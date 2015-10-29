/*
 * CAEN V551 Sequencer Headers
 * Author: Nikolaos Karastathis
 * Version: 0.0a
 */

#ifndef V551_SEQUENCER_H
#define V551_SEQUENCER_H


#ifndef __cplusplus
#define __cplusplus		//define C++ for CAENVMElib.h
#endif


#ifndef LINUX
#define LINUX			// recognize types
#endif

#include "/usr/include/CAENVMElib.h"


//namespace Ui{

class V551_Sequencer
{
protected:
    int32_t controllerHandle;	// the handle of V2718
    uint32_t baseAddress;	// sequencer Base address

public:
    V551_Sequencer (int32_t ctrlHandle, uint32_t bAddress);	//constructor

    // Read Fixed Code of Module @ BA + 0xFA
    CVErrorCodes ReadModuleFixedCode (uint16_t & moduleFixedCode);

    // Read Manufacturer's Specs of Module @ BA + FC
    CVErrorCodes ReadModuleManufacturerSpecs (uint16_t &
                                              moduleManufacturerSpecs);

    // Read Version and Serial number of Module @ BA + FE
    CVErrorCodes ReadModuleVersionSerial (uint16_t & moduleVersionSerial);

    //Interrupts
    CVErrorCodes WriteInterruptVectorRegister (unsigned int statusId);
    CVErrorCodes WriteInterruptLevelRegister (unsigned int interruptLevel);

    //Clear Module -- Clears on access
    CVErrorCodes ClearModule ();

    //Software Trigger -- Access starts conversion cycle
    CVErrorCodes SoftwareTrigger ();

    // Read - Write Status Register @ BA+0x8
    CVErrorCodes ReadStatusRegister (bool & internalDelay, bool & veto,
                                     bool & autoTrigger, bool & dataReady,
                                     bool & busy, bool & activeSequence);
    CVErrorCodes WriteStatusRegister (bool internalDelay, bool veto,
                                      bool autoTrigger);

    // Read - Write Test Register @ BA+0xA
    CVErrorCodes ReadTestRegister (bool & testMode, bool & clockLevel,
                                   bool & shiftInLevel,
                                   bool & testPulseLevel);
    CVErrorCodes WriteTestRegister (bool testMode, bool clockLevel,
                                    bool shiftInLevel, bool testPulseLevel);

    // Read - Write Number of channels @ BA + 0xC
    CVErrorCodes ReadNumberOfChannels (unsigned int &numberOfChannels);
    CVErrorCodes WriteNumberOfChannels (unsigned int numberOfChannels);

    // Read - Write T1 Register @ BA + 0xE (T1 = Trigger to Hold Delay)
    // t1 = 500 + T1*10 ns  , 0<=T1<=255
    CVErrorCodes ReadT1Register (unsigned int &T1);
    CVErrorCodes WriteT1Register (unsigned int T1);

    // Read - Write T2 Register @ BA + 0x10 (T2 = Hold to Sequence Delay)
    // t2 = 130 + T2*20 (+/-) 10 ns , 10<=T2<=511
    CVErrorCodes ReadT2Register (unsigned int &T2);
    CVErrorCodes WriteT2Register (unsigned int T2);

    // Read - Write T3 Register @ BA + 0x12 (T3 = Active Clock Duration)
    // t3 = T3*20 ns , 1<=T3<=T4 , T3<=255
    CVErrorCodes ReadT3Register (unsigned int &T3);
    CVErrorCodes WriteT3Register (unsigned int T3);

    // Read - Write T4 Register @ BA + 0x14 (T4 = Period of CLOCK and CONVERT sequence)
    // t4 = 20 + T4*20 ns , 1<=T4<=511
    CVErrorCodes ReadT4Register (unsigned int &T4);
    CVErrorCodes WriteT4Register (unsigned int T4);

    // Read - Write T5 Register @ BA + 0x16 (T5 = Clock to Convert Delay)
    // t5 = 40 + T5*20 ns , 2<=T5<=511
    CVErrorCodes ReadT5Register (unsigned int &T5);
    CVErrorCodes WriteT5Register (unsigned int T5);

    // Write Internal DAC -> Full value 0xFFF = +5V 50mA (max)
    CVErrorCodes WriteInternalDAC (unsigned int DACValue);


};				// end of V551_Sequencer class

//}				//end of namespace


#endif // V551_SEQUENCER_H
