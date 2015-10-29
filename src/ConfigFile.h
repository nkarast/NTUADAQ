#ifndef CONFIGFILE_H
#define CONFIGFILE_H


// C++ Includes
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <map>
#include <stdint.h>
#include <string>
#include <sstream>

// ROOT Includes
#include <TEnv.h>
//#include <TObjArray.h>
//#include <TObjString.h>
//#include <TString.h>
//#include "TSystem.h"

class TEnv;

class ConfigFile
{
public:
    enum runtype_t{
        runtypeData = 0,
        runtypePedestals = 1
    };

    // Functions
    ConfigFile(const char* filename=0);
    ~ConfigFile();

    int loadConfiguration();

    // Readout Variables
    uint32_t C_HEADER_BEGIN_MARKER;
    uint32_t C_HEADER_END_MARKER;
    uint32_t C_EVENT_BEGIN_MARKER;
    uint32_t C_EVENT_END_MARKER;
    uint32_t C_TRAILER_BEGIN_MARKER;
    uint32_t C_TRAILER_END_MARKER;

    std::string C_headerBeginMarker;
    std::string C_headerEndMarker;
    std::string C_eventBeginMarker;
    std::string C_eventEndMarker;
    std::string C_trailerBeginMarker;
    std::string C_trailerEndMarker;

    uint32_t C_BA_SEQUENCER;
    std::string C_baSequencer;

    short int C_isThereGenerator;
    uint32_t C_BA_GATE_GENERATOR;
    std::string C_baGateGenerator;
    short int C_CH0_UPPER_DISPLAY;
    short int C_CH0_LOWER_DISPLAY;
    short int C_CH1_UPPER_DISPLAY;
    short int C_CH1_LOWER_DISPLAY;

    std::vector<uint32_t> C_BA_CRAMS;
    std::vector<std::string> C_baCRAMSStringVector;
    std::vector<const char*> C_baCRAMSInputVector;

    short int C_T1_;
    short int C_T2_;
    short int C_T3_;
    short int C_T4_;
    short int C_T5_;

    short int C_NUMBER_OF_CRAMS;
    short int C_NUM_OF_GASSIPLEX_CHANNELS;
    short int C_NUM_OF_GASSIPLEX_CHANNELS_DCN;// =   NUM_OF_GASSIPLEX_CHANNELS/32;

    short int C_IRQ_TIMEOUT;
    short int C_enableMaxEventNumber;
    short int C_MAX_NUMBER_OF_EVENTS;

    std::string C_CONFIGURATION_FILE_PATH;
    std::string C_MAPPING_FILE_PATH;
    int C_DISPLAY_REFRESH_RATE;
     void tester();

     int C_runNumber;

private:
    short int error;
    std::string C_myConfigFile;

    //const void usage(const char* ourName) const;



};

#endif // CONFIGFILE_H
