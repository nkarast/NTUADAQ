#ifndef INTERFACE_H
#define INTERFACE_H

#ifndef __cplusplus
#define __cplusplus
#endif

#ifndef LINUX
#define LINUX
#endif

// Qt Includes
#include <QMainWindow>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QtConcurrentRun>
//#include <QtGui>
#include <QPushButton>
#include <QLayout>
#include <QTimer>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QShowEvent>
//#include <QFutureWatcher>



// C++ Includes
#include <iostream>
#include <stdint.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <arpa/inet.h>
#include <stdlib.h>
//#include <time.h>

// My Includes
#include "V551_Sequencer.h"
#include "V550_CRAMS.h"
#include "V462_GateGenerator.h"
#include "ConfigFile.h"

// ROOT Includes
#include <TROOT.h>
#include <TRint.h>
#include <TQObject.h>
#include <TString.h>
#include <TSystem.h>
#include <TObjArray.h>
#include <TEnv.h>
#include <TQtWidget.h>
#include <TF1.h>
#include <TGQt.h>
#include <TH1F.h>
#include <TFormula.h>
#include <TF1.h>
#include <TH1.h>
#include <TFrame.h>
#include <TTimer.h>
#include <TCanvas.h>
#include <TGedFrame.h>
#include <TGedEditor.h>
#include <TFile.h>


// QT_NAMESPACE
namespace Ui {
class Interface;
}

class V551_Sequencer;
class V550_CRAMS;
class V462_GateGenerator;

class QPaintEvent;
class QResizeEvent;
class QMouseEvent;
class QPushButton;
class QTimer;
class TCanvas;

class QRootCanvas : public QWidget
{
   Q_OBJECT

public:
   QRootCanvas( QWidget *parent = 0);
   virtual ~QRootCanvas() {}
   TCanvas* getCanvas() { return fCanvas;}

protected:
   TCanvas        *fCanvas;

   virtual void    mouseMoveEvent( QMouseEvent *e );
   virtual void    mousePressEvent( QMouseEvent *e );
   virtual void    mouseReleaseEvent( QMouseEvent *e );
   virtual void    paintEvent( QPaintEvent *e );
   virtual void    resizeEvent( QResizeEvent *e );
};



class Interface : public QMainWindow{
    Q_OBJECT

    /// #################################
    /// ##          PUBLIC             ##
    /// #################################
public:

    /// ********************************
    /// *** Constructor ~ Destructor ***
    /// ********************************
    explicit Interface(QWidget *parent = 0);
    ~Interface();

/// ##########################################
///                 DEBUG
/// ##########################################
    void demux(uint32_t, int &debugChan, int &debugData);
    int debugChan;
    int debugData;
    TH1F *h1ff;
    TH1F *h2ff;
    TCanvas *c1ff;
    TCanvas *c1fff;
    TH1F *h1fff;
    TH1F *h2fff;


    TCanvas *c2gg;
    TCanvas *c2ggg;
    TH1F *h1gg;
    TH1F *h2gg;
    TH1F *h1ggg;
    TH1F *h2ggg;



    int dummyIndex;
    TFile *rootFile;
    std::string rootFilename;
    //QFutureWatcher<int> watcher;
    /// **********************************
    /// Ui modification, locking, setting
    /// **********************************
    void tester();
    void lockExpertMode();
    void lockGateGeneratorConf();
    void readConfFile();
    //void lockConfigurationTab(); -- to be implemented when InitializeButton is pressed
    void setUpConfigurationTab();
    void setUpCRAMSLineEdits();
    std::string getTimeStamp();
    void setLogEntry(const char* entry);


    /// **********************************
    /// Configuration Variables
    /// **********************************
    // 1. Markers
    uint32_t HEADER_BEGIN_MARKER;
    std::string headerBeginMarker;

    uint32_t HEADER_END_MARKER;
    std::string headerEndMarker;

    uint32_t EVENT_BEGIN_MARKER;
    std::string eventBeginMarker;

    uint32_t EVENT_END_MARKER;
    std::string eventEndMarker;

    uint32_t TRAILER_BEGIN_MARKER;
    std::string trailerBeginMarker;

    uint32_t TRAILER_END_MARKER;
    std::string trailerEndMarker;
/// ---------------------------------------------------------
    // 2. Base Addresses
    std::vector<std::string> baCramsStringVector;
    std::vector<uint32_t> baCramsVector;
    QLineEdit *cramsLineEdit[10];   // used to set LineEdits for CRAMS BA's

    uint32_t BA_SEQUENCER;
    std::string baSequencer;

    uint32_t BA_GATE_GENERATOR;
    std::string baGateGenerator;
/// ---------------------------------------------------------
    // 3. Timing
    short int _T1_;
    short int _T2_;
    short int _T3_;
    short int _T4_;
    short int _T5_;
/// ---------------------------------------------------------
    // 4. Gate Generator Stuff
    short unsigned int isThereGenerator;
    short int CH0_UPPER_DISPLAY;
    short int CH0_LOWER_DISPLAY;
    short int CH1_UPPER_DISPLAY;
    short int CH1_LOWER_DISPLAY;
    short int IRQ_TIMEOUT;
/// ---------------------------------------------------------
    // 5. Modules' Stuff
    short int NUMBER_OF_CRAMS;
    short int NUM_OF_GASSIPLEX_CHANNELS;
    short int NUM_OF_GASSIPLEX_CHANNELS_DCN;// =   NUM_OF_GASSIPLEX_CHANNELS/32;
/// ---------------------------------------------------------
    // 6. Max number of events
    short int enableMaxEventNumber;
    short int MAX_NUMBER_OF_EVENTS;
/// ---------------------------------------------------------
    // 7. Path to conf/map file
    std::string CONFIGURATION_FILE_PATH;
    std::string MAPPING_FILE_PATH;
/// ---------------------------------------------------------
    // 8. Display
    int DISPLAY_REFRESH_RATE;


    /// ********************************
    /// *** DAQ Variables / Structs  ***
    /// ********************************
    //int runNumber; // do I really need it? == not anymore
    time_t curTime;
    std::string outputFilename;
    std::map<int, int> chMap;
/// ---------------------------------------------------------
    struct{
        int runNumber;
        int eventNumber;
        int fileNumber;
        int runType;
    }runInfo;
/// ---------------------------------------------------------
    struct{
        std::ofstream readout;
        //std::ifstream options;
    }files;
/// ---------------------------------------------------------
    enum command{
        TriggerArrived = 'T',
        NoTrigger = 'N',
        CloseRun = 'C',
        QuitRun = 'Q'
    };
    std::vector<std::vector<uint32_t> > dataContainer;
    std::vector<TH1F*> histoContainer;

    Interface::command curCommand;
    TCanvas *c1;
    TQtWidget *tqt;
    TH1F *h1;

/// ---------------------------------------------------------

    /// ********************************
    /// ***      DAQ Functions       ***
    /// ********************************

/// -------------* Initialization Functions  *---------------
    int initialize();
    int initializeHardware();
    int initializeOutputFiles();
    void startDAQCycle();
    int initializeInputFiles(const char* mapFilename);
    int finalize();
   // inline int numberOfEvents() { return runInfo.eventNumber; }

/// -----------* Trigger and Readout Functions  *------------
    int waitForTrigger(command &curCommand);
    int readout();

/// -------------* Readout Marker Functions *----------------
    int generateHeader();
    int generateTrailer();
    int generateEventDataTop();
    int generateEventDataBot();

/// ----------------------* Handlers *-----------------------
    void handleRunNumber();
    void handleOutputFilename();
    void getReadoutVectorValues(uint32_t inputVector[]);
    void display();
   // void OnRefreshTimer();  // timer to process ROOT events
    void Create(); // get the ID of the widget TCanvas
    void HistoFill();
    void displayCycle(std::vector<uint32_t> vec, int whichFifo);
    void startDisplayThread(std::vector<uint32_t> vec, int whichFifo);

    /// #################################
    /// ##           PRIVATE           ##
    /// #################################

private:
    Ui::Interface *ui;
    int32_t controllerHandle;

protected:
    V551_Sequencer *Sequencer;
    V462_GateGenerator *GateGenerator;
    std::vector<V550_CRAMS*> CRAMS;
    QRootCanvas    *canvas;
    QTimer         *fRootTimer;



    /// #################################
    /// ##         PUBLIC SLOTS        ##
    /// #################################

public slots:
    void unlockExpertMode();
    // void setCRAMSBAAddresses();
    void unlockGateGeneratorConf(int state);
    void resetDefaultConfig();
    void enableMaxNumberEvents(int state);
    void applyConfiguration();
    void loadConfiguration();
    //void applyCRAMSAddresses();
    void changeNumberOfCrams(int newVal);
//    void startDAQCycle();
    void startDAQThread();
    void stopDAQCycle();
    void initializeDAQ();
    void cancelInitialization();
    // temp
    void setupCanvas();
    void clicked1();
    void handle_root_events();
   // void updateRootCanvas();

};


#endif // INTERFACE_H
