// My Includes
#include "ConfigFile.h"


ConfigFile::ConfigFile(const char* filename):error(0), C_myConfigFile((filename && strlen(filename)) ? filename : "")
{
    if(!error){
        error += loadConfiguration();
    }

    if(error){
        std::cout << "Error while loading configuration file." << std::endl;
    }

}


ConfigFile::~ConfigFile(){
    //empty
}

int ConfigFile::loadConfiguration(){

    // Check if file to conf file is set:
    if(C_myConfigFile==""){
        std::cerr << "#ERROR: loadConfiguration(): Configuration file has not been set." << std::endl;
        return -1;
    }

    // Check the stat of the file
    struct stat stFileInfo;
    if(stat(C_myConfigFile.c_str(), &stFileInfo)){
        std::cerr << "#ERROR: loadConfiguration(): Configuration File '" << C_myConfigFile << "' does not exist." << std::endl;
        return -1;
    }
    std::cout << "DAQ configuration file: " << C_myConfigFile << "'" << std::endl;

    // Paths...

    char pathbuff[256];
    getcwd(pathbuff, 256); // get current working directory

    std::string configurationDirectory;
    size_t lastSlash = C_myConfigFile.find_last_of("/");
    if(lastSlash != std::string::npos) {
        configurationDirectory = C_myConfigFile.substr(0, lastSlash);
        std::cout << "Configuration Directory: " << configurationDirectory << std::endl;
        chdir(configurationDirectory.c_str());
    }

    // Create TEnv and read values
    TEnv *env = new TEnv(C_myConfigFile.c_str());

    std::stringstream ss;
    C_headerBeginMarker = env->GetValue("HEADER_BEGIN_MARKER", "0x90000000");
    ss << C_headerBeginMarker;
    ss >> std::hex >> C_HEADER_BEGIN_MARKER;
    ss.clear();

    C_headerEndMarker = env->GetValue("HEADER_END_MARKER", "0x9FFFF000");
    ss << C_headerEndMarker;
    ss >> std::hex >> C_HEADER_END_MARKER;
    ss.clear();

    C_eventBeginMarker   = env->GetValue("EVENT_BEGIN_MARKER", "0x80000000");
    ss << C_eventBeginMarker;
    ss >> std::hex >> C_EVENT_BEGIN_MARKER;
    ss.clear();

    C_eventEndMarker      = env->GetValue("EVENT_END_MARKER", "0x8FFFF000");
    ss << C_eventEndMarker;
    ss >> std::hex >> C_EVENT_END_MARKER;
    ss.clear();

    C_trailerBeginMarker = env->GetValue("TRAILER_BEGIN_MARKER", "0xA0000000");
    ss << C_trailerBeginMarker;
    ss >> std::hex >> C_TRAILER_BEGIN_MARKER;
    ss.clear();

    C_trailerEndMarker = env->GetValue("TRAILER_END_MARKER", "0xAFFFF000");
    ss << C_trailerEndMarker;
    ss >> std::hex >> C_TRAILER_END_MARKER;
    ss.clear();
    /*
    * Gassiplex Stuff
    */
    C_NUM_OF_GASSIPLEX_CHANNELS = env->GetValue("NUM_OF_GASSIPLEX_CHANNELS", 96);
    C_NUM_OF_GASSIPLEX_CHANNELS_DCN = env->GetValue("NUM_OF_GASSIPLEX_CHANNELS_DCN", 3);

    /*
   * NO OF CRAMS
   */
    C_NUMBER_OF_CRAMS = env->GetValue("NUMBER_OF_CRAMS", 4);


    std::cout <<" NUmber of crams " << C_NUMBER_OF_CRAMS << std::endl;
    /*
   * Base addresses
   */
    C_baSequencer    = env->GetValue("_BA_SEQUENCER_", "0x11000000");
    ss << C_baSequencer;
    ss >> std::hex >> C_BA_SEQUENCER;
    ss.clear();

    // read CRAMS ba's
    C_baCRAMSStringVector.resize(C_NUMBER_OF_CRAMS);
    C_BA_CRAMS.resize(C_NUMBER_OF_CRAMS);

    std::cout << "Size of Vector :" << C_baCRAMSStringVector.size() << std::endl;

//    std::vector<const char*> baCramsInputVector;
//    std::vector<const char*> C_baCRAMSInputVector;
    C_baCRAMSInputVector.resize(10);
    C_baCRAMSInputVector.at(0) = "_BA_CRAMS_0_";
    C_baCRAMSInputVector.at(1) = "_BA_CRAMS_1_";
    C_baCRAMSInputVector.at(2) = "_BA_CRAMS_2_";
    C_baCRAMSInputVector.at(3) = "_BA_CRAMS_3_";
    C_baCRAMSInputVector.at(4) = "_BA_CRAMS_4_";
    C_baCRAMSInputVector.at(5) = "_BA_CRAMS_5_";
    C_baCRAMSInputVector.at(6) = "_BA_CRAMS_6_";
    C_baCRAMSInputVector.at(7) = "_BA_CRAMS_7_";
    C_baCRAMSInputVector.at(8) = "_BA_CRAMS_8_";
    C_baCRAMSInputVector.at(9) = "_BA_CRAMS_9_";

    C_baCRAMSStringVector.at(0)=env->GetValue(C_baCRAMSInputVector.at(0), "ERROR");

    for(unsigned short int i=0; i<C_baCRAMSStringVector.size(); i++){
        // baCRAMSStringVector.at(i)=env->GetValue(baCRAMSInputVector.at(i), "ERROR");
        C_baCRAMSStringVector.at(i)=env->GetValue(C_baCRAMSInputVector.at(i), "ERROR");
        ss << C_baCRAMSStringVector.at(i);
        ss >> std::hex >> C_BA_CRAMS.at(i);
        ss.clear();
        //  std::cout << " i = " << i << std::endl;
        //  std::cout << baCRAMSStringVector.at(i) << "\t" << baCRAMSInputVector.at(i) << std::endl;
    }


    /*
    * Timing Constants
    */
    C_T1_ = env->GetValue("_T1_", 30);
    C_T2_ = env->GetValue("_T2_", 10);
    C_T3_ = env->GetValue("_T3_", 5);
    C_T4_ = env->GetValue("_T4_", 49);
    C_T5_ = env->GetValue("_T5_", 13);

    C_IRQ_TIMEOUT = env->GetValue("IRQ_TIMEOUT", 1000);

    C_enableMaxEventNumber = env->GetValue("ENABLE_MAX_NUMBER_EVENTS", 1);
    C_MAX_NUMBER_OF_EVENTS = env->GetValue("MAX_EVENT_NUMBER", 5000);

    C_isThereGenerator = env->GetValue("IS_THERE_GENERATOR", 0);
    if(C_isThereGenerator == 1){
        C_baGateGenerator = env->GetValue("BA_GATE_GENERATOR", "0x100000");
        ss << C_baGateGenerator;
        ss >> std::hex >> C_BA_GATE_GENERATOR;
        ss.clear();

        C_CH0_UPPER_DISPLAY = env->GetValue("CH0_UPPER_DISPLAY", 0);
        C_CH0_LOWER_DISPLAY = env->GetValue("CH0_LOWER_DISPLAY", 6416);
        C_CH1_UPPER_DISPLAY = env->GetValue("CH1_UPPER_DISPLAY", 0);
        C_CH1_LOWER_DISPLAY = env->GetValue("CH1_UPPER_DISPLAY", 1);
    }



    C_CONFIGURATION_FILE_PATH = env->GetValue("CONFIGURATION_FILE_PATH", "ERROR");
    C_MAPPING_FILE_PATH = env->GetValue("MAPPING_FILE_PATH", "ERROR");
    C_DISPLAY_REFRESH_RATE = env->GetValue("DISPLAY_REFRESH_RATE", 100);
    delete env;

    TEnv *env2 = new TEnv("runNumber.conf");
    C_runNumber = env2->GetValue("runNumber",0);
    delete env2;

    chdir(pathbuff);
    return 0;

}


void ConfigFile::tester(){

std::cout << "HEADER BEGIN : " << C_HEADER_BEGIN_MARKER << std::endl;
std::cout << "HEADER END : " << C_HEADER_END_MARKER << std::endl;
std::cout << "EVENT BEGIN : " << C_EVENT_BEGIN_MARKER << std::endl;
std::cout << "EVENT END : " << C_EVENT_END_MARKER << std::endl;
std::cout << "TRAILER BEGIN : " << C_TRAILER_BEGIN_MARKER << std::endl;
std::cout << "TRAILER END : " << C_TRAILER_END_MARKER << std::endl;

}
