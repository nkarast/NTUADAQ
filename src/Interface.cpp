// My Includes
#include "ConfigFile.h"
#include "Interface.h"
#include "ui_interface.h"
// ----
#include "V551_Sequencer.h"
#include "V550_CRAMS.h"
#include "V462_GateGenerator.h"

#include <QWidget>

#define DEBUG 0
#define DEBUG_READOUT 1
#define DEBUG_INIT 1
#define DEBUG_DEMUX 1
#define DEBUG_DEMUX_PLOT 0

class V551_Sequencer;
class V550_CRAMS;
class V462_GateGenerator;


QRootCanvas::QRootCanvas(QWidget *parent) :
             QWidget(parent, 0), fCanvas(0)
{
   setMinimumSize(600, 500);
   setMouseTracking(kTRUE);

   int wid = gVirtualX->AddWindow((ULong_t)winId(),600,400);
   fCanvas = new TCanvas("Root Canvas",width(),height(),wid);
}

void QRootCanvas::mouseMoveEvent(QMouseEvent *e)
{
   if (fCanvas) {
      if (e->buttons() & Qt::LeftButton) {
         fCanvas->HandleInput(kButton1Motion, e->x(), e->y());
      } else if (e->buttons() & Qt::MidButton) {
         fCanvas->HandleInput(kButton2Motion, e->x(), e->y());
      } else if (e->buttons() & Qt::RightButton) {
         fCanvas->HandleInput(kButton3Motion, e->x(), e->y());
      } else {
         fCanvas->HandleInput(kMouseMotion, e->x(), e->y());
      }
   }
}

void QRootCanvas::mousePressEvent( QMouseEvent *e )
{
   if (fCanvas) {
      switch (e->button()) {
         case Qt::LeftButton :
            fCanvas->HandleInput(kButton1Down, e->x(), e->y());
            break;
         case Qt::MidButton :
            fCanvas->HandleInput(kButton2Down, e->x(), e->y());
            break;
         case Qt::RightButton :
            // does not work properly on Linux...
#ifdef WIN32
            fCanvas->HandleInput(kButton3Down, e->x(), e->y());
#endif
            break;
         default:
            break;
      }
   }
}

void QRootCanvas::mouseReleaseEvent( QMouseEvent *e )
{
   if (fCanvas) {
      switch (e->button()) {
         case Qt::LeftButton :
            fCanvas->HandleInput(kButton1Up, e->x(), e->y());
            break;
         case Qt::MidButton :
            fCanvas->HandleInput(kButton2Up, e->x(), e->y());
            break;
         case Qt::RightButton :
            // does not work properly on Linux...
#ifdef WIN32
            fCanvas->HandleInput(kButton3Up, e->x(), e->y());
#endif
            break;
         default:
            break;
      }
   }
}

void QRootCanvas::resizeEvent( QResizeEvent * )
{
   if (fCanvas) {
      fCanvas->Resize();
      fCanvas->Update();
   }
}

void QRootCanvas::paintEvent( QPaintEvent * )
{
   if (fCanvas) {
      fCanvas->Resize();
      fCanvas->Update();
   }
}

//using namespace Ui;

/// #################################################################################
/// #                                                                               #
/// #                 CONSTRUCTOR - CONNECTIONS - DESTRUCTOR                        #
/// #                                                                               #
/// #################################################################################
/// Constructor
Interface::Interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Interface)//, Sequencer(0),GateGenerator(0)
{
    // Setup UI
    ui->setupUi(this);
    ui->stopCycleCheckBox->hide();
    ui->configurationFilePathLineEdit->setText("/home/nick/NTUADAQ_ALLTOP/inputFiles/daq.conf");

    setLogEntry("[INFO] Program has started.\n");

    lockExpertMode();
    // --- uncheck initializeCheckbox if is checked (shouldn't)
    ui->initializeCheckBox->setEnabled(false);
    ui->initializeCheckBox->setCheckState(Qt::Unchecked);
    //-----
    setUpCRAMSLineEdits();
    if(DEBUG){
        std::cout << "SetupUi, Lock ExpertMode and SetUpCRAMSLineEdit, reading conf file" << std::endl;
    }
    readConfFile();
    if(DEBUG){
    std::cout << " THE NUMBER OF CRAMS IS " << NUMBER_OF_CRAMS << std::endl;
    }
    //std::cout << "run number is " << runNumber << std::endl;
    setUpConfigurationTab();

    QVBoxLayout *l = new QVBoxLayout(ui->displayWidget);
    l->addWidget(canvas = new QRootCanvas(ui->displayWidget));
    fRootTimer = new QTimer( this );
    QObject::connect( fRootTimer, SIGNAL(timeout()), this, SLOT(handle_root_events()) );
    fRootTimer->start( 20 );

    // --- Zero init
    runInfo.eventNumber = 0;


//    tqt = new TQtWidget(ui->displayWidget);
//    c1 = new TCanvas(tqt);
//    tqt = new TQtWidget(ui->displayWidget, "Display Canvas", Qt::SubWindow, "TRUE");
//    c1 = new TCanvas(tqt);
//    c1->Divide(2, 2);

//    Create();
    c1ff = new TCanvas("Weight","Weight",800,600);
    c1ff->Divide(2,1);
    dummyIndex =0;
    h1ff = new TH1F("Chamber X", "Chamber X", 96,0,96);
    h2ff = new TH1F("Chamber Y", "Chamber Y", 96,0,96);
    ///---
    c1fff = new TCanvas("No Weight","No Weight",800,600);
    c1fff->Divide(2,1);
    h1fff = new TH1F("Chamber X (NO.W)", "Chamber X (NO.W)", 96,0,96);
    h2fff = new TH1F("Chamber Y (NO.W", "Chamber Y (NO.W)", 96,0,96);


    /// ****

    c2gg = new TCanvas("Weight (No Cut)","Weight (No Cut)",800,600);
    c2gg->Divide(2,1);
    c2ggg = new TCanvas("No Weight (No Cut)","No Weight (No Cut)",800,600);
    c2ggg->Divide(2,1);
    h1gg = new TH1F("Chamber X (NC)", "Chamber X(NC)", 96,0,96);
    h2gg = new TH1F("Chamber Y (NC)", "Chamber Y (NC)", 96,0,96);
    h1ggg = new TH1F("Chamber X (NWNC)", "Chamber X (NWNC)", 96,0,96);
    h2ggg = new TH1F("Chamber Y (NWNC)", "Chamber Y (NWNC)", 96,0,96);

    /// Connects
    // 1. Ui setup
    connect(ui->gateGeneratorCheckBox, SIGNAL(stateChanged(int)), this, SLOT(unlockGateGeneratorConf(int)));
    connect(ui->maxNumEventsCheckBox, SIGNAL(stateChanged(int)), this, SLOT(enableMaxNumberEvents(int)));
    connect(ui->numberOfCRAMSSpinBox, SIGNAL(valueChanged(int)), this, SLOT(changeNumberOfCrams(int)));
    connect(ui->configurationFilePathLineEdit, SIGNAL(textChanged(QString)), this, SLOT(loadConfiguration()));

    // 2. Buttons
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->unlockButton, SIGNAL(clicked()), this, SLOT(unlockExpertMode()));
    connect(ui->resetDefaultsButton, SIGNAL(clicked()), this, SLOT(resetDefaultConfig()));
    connect(ui->applyConfigButton, SIGNAL(clicked()), this, SLOT(applyConfiguration()));
    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startDAQThread()));
    connect(ui->initializeButton, SIGNAL(clicked()), this, SLOT(initializeDAQ()));
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(stopDAQCycle()));
    connect(ui->cancelInitializationButton, SIGNAL(clicked()), this, SLOT(cancelInitialization()));
    connect(ui->clearLogButton, SIGNAL(clicked()), ui->logTextEdit, SLOT(clear()));
    connect(ui->helpButton, SIGNAL(clicked()), this, SLOT(clicked1()));
    //connect(&watcher, SIGNAL(finished()), this, SLOT(updateRootCanvas()));

    // 3. Functions


}

/// Destructor
Interface::~Interface()
{
    delete ui;
}

/// #################################################################################
/// #                                                                               #
/// #                               D   E   B   U   G                               #
/// #                                                                               #
/// #################################################################################

void Interface::demux(uint32_t dataWord, int &chNumber, int &chData){
        chNumber 	= (dataWord & 0x7FF000) >> 12;
        chData  	= (dataWord & 0xFFF);
}


/// ---------------------------------------------------------------------------------

/// #################################################################################
/// #                                                                               #
/// #                         UI MODIFICATION, LOCK UP, SETUP                       #
/// #                                                                               #
/// #################################################################################
/// Tester function for debugging
void Interface::tester() {

    std::cout << " # Debug: Tester returned! Value of t2SpinBox is " << ui->t2SpinBox->value() << std::endl;
}

/// Lock expert mode
void Interface::lockExpertMode(){

    // Disable timing editing
    ui->    t1SpinBox-> setEnabled(false);
    ui->    t2SpinBox-> setEnabled(false);
    ui->    t3SpinBox-> setEnabled(false);
    ui->    t4SpinBox-> setEnabled(false);
    ui->    t5SpinBox-> setEnabled(false);

    // Enable readout markers editing
    ui->    headerBeginLineEdit->  setEnabled(false);
    ui->    headerEndLineEdit->    setEnabled(false);
    ui->    eventBeginLineEdit->   setEnabled(false);
    ui->    eventEndLineEdit->     setEnabled(false);
    ui->    trailerBeginLineEdit->  setEnabled(false);
    ui->    trailerEndLineEdit->    setEnabled(false);

    // Enable FEC values editing
    ui->    numOfChansSpinBox->    setEnabled(false);
    ui->    IRQTimeoutSpinBox->    setEnabled(false);

    setLogEntry("[INFO] Configuration locked for non-expert users.\n");
}

/// Lock gate generator configuration
void Interface::lockGateGeneratorConf(){
    ui->CH0LowerSpinBox->setEnabled(false);
    ui->CH0UpperSpinBox->setEnabled(false);
    ui->CH1LowerSpinBox->setEnabled(false);
    ui->CH1UpperSpinBox->setEnabled(false);

    ui->BAGateGeneratorLineEdit->setEnabled(false);

}

/// Read configuration file via ConfigFile class
void Interface::readConfFile(){
    ConfigFile *reader = new ConfigFile(ui->configurationFilePathLineEdit->text().toLatin1());
// Debugging:
    reader->tester();

    // Copy ConfigFile variables to "global" interface variables.
    HEADER_BEGIN_MARKER = reader->C_HEADER_BEGIN_MARKER;
    headerBeginMarker = reader->C_headerBeginMarker;

    HEADER_END_MARKER = reader->C_HEADER_END_MARKER;
    headerEndMarker = reader->C_headerEndMarker;

    EVENT_BEGIN_MARKER = reader->C_EVENT_BEGIN_MARKER;
    eventBeginMarker = reader->C_eventBeginMarker;

    EVENT_END_MARKER = reader->C_EVENT_END_MARKER;
    eventEndMarker = reader->C_eventEndMarker;

    TRAILER_BEGIN_MARKER = reader->C_TRAILER_BEGIN_MARKER;
    trailerBeginMarker = reader->C_trailerBeginMarker;

    TRAILER_END_MARKER = reader->C_TRAILER_END_MARKER;
    trailerEndMarker = reader-> C_trailerEndMarker;

    baCramsStringVector = reader->C_baCRAMSStringVector;
    baCramsVector = reader->C_BA_CRAMS;

    BA_SEQUENCER = reader->C_BA_SEQUENCER;
    baSequencer = reader->C_baSequencer;

    _T1_ = reader->C_T1_;
    _T2_ = reader->C_T2_;
    _T3_ = reader->C_T3_;
    _T4_ = reader->C_T4_;
    _T5_ = reader->C_T5_;

    NUMBER_OF_CRAMS = reader->C_NUMBER_OF_CRAMS;
    NUM_OF_GASSIPLEX_CHANNELS = reader->C_NUM_OF_GASSIPLEX_CHANNELS;
    NUM_OF_GASSIPLEX_CHANNELS_DCN = NUM_OF_GASSIPLEX_CHANNELS/32;// =   NUM_OF_GASSIPLEX_CHANNELS/32;


    isThereGenerator = reader->C_isThereGenerator;
    if(isThereGenerator == 1 ) {
        BA_GATE_GENERATOR = reader->C_BA_GATE_GENERATOR;
        baGateGenerator = reader->C_baGateGenerator;

        CH0_UPPER_DISPLAY = reader->C_CH0_UPPER_DISPLAY;
        CH0_LOWER_DISPLAY = reader->C_CH0_LOWER_DISPLAY;
        CH1_UPPER_DISPLAY = reader->C_CH1_UPPER_DISPLAY;
        CH1_LOWER_DISPLAY = reader->C_CH1_LOWER_DISPLAY;
    }//if isThereGenerator
    //else{
    //  ui->gateGeneratorCheckBox->checkState();
    //lockGateGeneratorConf();
    //}


    IRQ_TIMEOUT = reader->C_IRQ_TIMEOUT;
    enableMaxEventNumber = reader->C_enableMaxEventNumber;
    MAX_NUMBER_OF_EVENTS = reader->C_MAX_NUMBER_OF_EVENTS;

    CONFIGURATION_FILE_PATH =  reader->C_CONFIGURATION_FILE_PATH;
    MAPPING_FILE_PATH = reader->C_MAPPING_FILE_PATH;
    DISPLAY_REFRESH_RATE = reader->C_DISPLAY_REFRESH_RATE;

    runInfo.runNumber = reader->C_runNumber;

    setLogEntry("[INFO] Configuration file read.\n");

}

/// Setup the configuration tab using the values read from file (readConfFile())
void Interface::setUpConfigurationTab(){

    //QString qs = baSequencer.c_str();
    // Sequencer Group Box
    ui->BASequencerLineEdit->setText((QString) baSequencer.c_str());
    ui->t1SpinBox->setValue(_T1_);
    ui->t2SpinBox->setValue(_T2_);
    ui->t3SpinBox->setValue(_T3_);
    ui->t4SpinBox->setValue(_T4_);
    ui->t5SpinBox->setValue(_T5_);

    // Readout Markers Group Box
    ui->headerBeginLineEdit->setText((QString) headerBeginMarker.c_str());
    ui->headerEndLineEdit->setText((QString) headerEndMarker.c_str());
    ui->eventBeginLineEdit->setText((QString) eventBeginMarker.c_str());
    ui->eventEndLineEdit->setText((QString) eventEndMarker.c_str());
    ui->trailerBeginLineEdit->setText((QString) trailerBeginMarker.c_str());
    ui->trailerEndLineEdit->setText((QString) trailerEndMarker.c_str());

    // Gate Generator Group Box
    if(isThereGenerator == 0){
        lockGateGeneratorConf();
    }
    else if(isThereGenerator == 1){
        ui->gateGeneratorCheckBox->setCheckState(Qt::Checked);
        ui->BAGateGeneratorLineEdit->setText((QString) baGateGenerator.c_str());
        ui->CH0UpperSpinBox->setValue(CH0_UPPER_DISPLAY);
        ui->CH0LowerSpinBox->setValue(CH0_LOWER_DISPLAY);
        ui->CH1UpperSpinBox->setValue(CH1_UPPER_DISPLAY);
        ui->CH1LowerSpinBox->setValue(CH1_LOWER_DISPLAY);
    }

    // Misc Group Box
    ui->numOfChansSpinBox->setValue(NUM_OF_GASSIPLEX_CHANNELS);
    ui->IRQTimeoutSpinBox->setValue(IRQ_TIMEOUT);
    ui->configurationFilePathLineEdit->setText((QString) CONFIGURATION_FILE_PATH.c_str());
    ui->mappingFilePathLineEdit->setText((QString) MAPPING_FILE_PATH.c_str());


    if(enableMaxEventNumber==1){
        ui->maxNumEventsCheckBox->setCheckState(Qt::Checked);
        ui->maxNumOfEventsSpinBox->setEnabled(true);
        ui->maxNumOfEventsSpinBox->setValue(MAX_NUMBER_OF_EVENTS);
    }
    else if(enableMaxEventNumber==0){
        ui->maxNumEventsCheckBox->setCheckState(Qt::Unchecked);
        ui->maxNumOfEventsSpinBox->setEnabled(false);
    }



    //CRAMS
    ui->numberOfCRAMSSpinBox->setValue(baCramsVector.size());

    for(unsigned short int k=0; k<baCramsVector.size();k++){
        cramsLineEdit[k]->setEnabled(true);
        cramsLineEdit[k]->setText((QString) baCramsStringVector.at(k).c_str());
    }

    ui->runNumberSpinBox->setValue(runInfo.runNumber);

    ui->displayRefreshRateSpinBox->setValue(DISPLAY_REFRESH_RATE);

}

/// Setup the ui for CRAMS BA configuration
void Interface::setUpCRAMSLineEdits(){

    QString cramsNames[] = {"CRAMS 0:", "CRAMS 1:", "CRAMS 2:", "CRAMS 3:", "CRAMS 4:", "CRAMS 5:", "CRAMS 6:", "CRAMS 7:","CRAMS 8:", "CRAMS 9:"};
    QLabel *cramsLabels[10];

    QGroupBox *baGroupBox = new QGroupBox();
    QVBoxLayout *vbox = new QVBoxLayout;

    for (int i = 0; i<10; i++){
        cramsLabels[i] = new QLabel(cramsNames[i], baGroupBox);
        cramsLineEdit[i] = new QLineEdit(baGroupBox);
        cramsLineEdit[i]->setEnabled(false);
       vbox->addWidget(cramsLabels[i]);
       vbox->addWidget(cramsLineEdit[i]);
    }
    vbox->addStretch(1);

    baGroupBox->setLayout(vbox);
    ui->cramsGridLayout->addWidget(baGroupBox);

}

std::string Interface::getTimeStamp(){
    std::string timeStamp;
    time_t timeNow;
    time(&timeNow);
    tm *ptr = gmtime(&timeNow);
    std::stringstream pp;
    pp<<"[" << ptr->tm_mday << "/" << ptr->tm_mon+1 << "/" << ptr->tm_year+1900 << "-" << ptr->tm_hour << ":" << ptr->tm_min << ":" << ptr->tm_sec <<"]-->> ";
    pp>>timeStamp;
    return timeStamp;

}

void Interface::setLogEntry(const char *entry){
    ui->logTextEdit->insertPlainText(getTimeStamp().c_str());
    ui->logTextEdit->insertPlainText(entry);
}

/// ---------------------------------------------------------------------------------


/// #################################################################################
/// #                                                                               #
/// #                         DAQ CYCLE AND READOUT FUNCTIONS                       #
/// #                                                                               #
/// #################################################################################

/// -----------------------*         Main Functions       *--------------------------
/// Initialize the devices and files
int Interface::initialize(){

    CVErrorCodes droopy;
    //int dripple;
    // Initializing controller
    std::cout << "#Interface::initialize() : Initializing Controller. Please Wait..." << std::endl;

    droopy = CAENVME_Init(cvV2718, 0, 0, &controllerHandle);
    if (droopy != cvSuccess){
        std::cout << "#Interface::initialize() : Error while initializing controller." << std::endl;
        setLogEntry("[FATAL] Error while initializing controller.\n");
        // return droopy;
    }//if droopy
    else{
        std::clog << "#Interface::initialize() : Controller initialized successfully!" << std::endl;
        setLogEntry("[INFO] Controller initialized successfully.\n");
    }

    int dripple = 0;
    dripple = initializeHardware();
    if(dripple < 0){
        std::cerr << "#Interface::initialize : Error while initializing hardware." << std::endl;
        setLogEntry("[FATAL] Error while initializing hardware.\n");
        return dripple;
    }
    else{
        std::clog << "#Interface::initialize : Hardware initialized successfully!" << std::endl;
        setLogEntry("[INFO] Hardware initialized successfully.\n");
    }


    dripple = initializeInputFiles(ui->mappingFilePathLineEdit->text().toStdString().c_str());
    if(dripple < 0){
        std::cerr << "#Interface::initialize : Error while initializing input files." << std::endl;
        setLogEntry("[FATAL] Error while initializing input files.\n");
        return dripple;
    }
    else{
        std::clog << "#Interface::initialize : Input files initialized successfully!" << std::endl;
        setLogEntry("[INFO] Input files initialized successfully.\n");
    }

//    int dripple; // debug line
    dripple = initializeOutputFiles();
    if(dripple < 0){
        std::cerr << "#Interface::initialize : Error while initializing output files." << std::endl;
        setLogEntry("[FATAL] Error while initializing output files.\n");
        return dripple;
    }
    else{
        std::clog << "#Interface::initialize : Output files initialized successfully!" << std::endl;
        setLogEntry("[INFO] Output files initialized successfully.\n");
    }

    if(dripple<0){
        ui->initializeCheckBox->setCheckState(Qt::Unchecked);
    }
    else{
         ui->initializeCheckBox->setCheckState(Qt::Checked);
         ui->cancelInitializationButton->setEnabled(true);
         ui->startButton->setEnabled(true);
    }
    return dripple;
}

/// Initialize hardware (Controller, Sequencer, CRAMS, Gate Generator)
int Interface::initializeHardware(){

    std::cout << "#Interface::initializeHardware : Starting Init..." << std::endl;

    /// Create the pointers for the modules and set their BA.
    Sequencer = new V551_Sequencer(controllerHandle, BA_SEQUENCER);
    if(isThereGenerator == 1) GateGenerator = new V462_GateGenerator(controllerHandle, BA_GATE_GENERATOR);
    //  std::vector<V550_CRAMS*> CRAMS;
    CRAMS.resize(ui->numberOfCRAMSSpinBox->value());
    for(int i=0; i<ui->numberOfCRAMSSpinBox->value(); i++){
        CRAMS.at(i) = new V550_CRAMS(controllerHandle, baCramsVector.at(i));
    }


    std::cout << "#Interface:: initializeHardware : Initializing Sequencer..." << std::endl;
    CVErrorCodes droopy;

    /// ** Initializing Gate Generator **
    /// Write Status Register
    droopy = Sequencer->WriteStatusRegister(0,1,0);
    if(droopy != cvSuccess){
        std::cerr << "#Interface::initializeHardware : Error while writing sequencer's write status register." << std::endl;
        return droopy;
    }
        /// Debugging previous step::: Write status reg (@ seq)
    if(DEBUG){
        bool intDelay, veto, autotrigger, drdy, busy, activeSequence;
        droopy = Sequencer->ReadStatusRegister(intDelay, veto, autotrigger, drdy, busy, activeSequence);
        if (droopy != cvSuccess) {
            std::cerr << "#Interface::initializeHardware: Error while Reading Status Register of Sequencer after setting veto" << std::endl;
        }
        else {
            std::cout << "@@ Interface::initializeHardware: Sequencer Status Register : \n Internal Delay (0) = " << intDelay << "\n Veto (1) = " << veto << "\n Auto Trigger (0) = " << autotrigger << "\n Data Ready = " << drdy << "\n Busy = " << busy << "\n Active Sequence = " << activeSequence << std::endl;
        }
    }
    /// Write Test Register + Debug
    droopy = Sequencer->WriteTestRegister(0,0,0,0);
    if(droopy != cvSuccess){
        std::cerr << "#Interface::initializeHardware() : Error while writing sequencer's test register." << std::endl;
        return droopy;
    }

    /// Debugging previous step::: Write test reg (@ seq)
    if(DEBUG){
        bool testmode, clocklvl, shiftlvl, testpulselvl;
        droopy = Sequencer->ReadTestRegister(testmode, clocklvl, shiftlvl, testpulselvl);
        if(droopy != cvSuccess){
            std::cerr << "@@Interface::initializeHardware() : Sequencer test register." << std::endl;
            return droopy;
        }
        else{
            std::cout << "@@Interface::initializeHardware() : Sequencer Test Register \n TestMode (0) = " << testmode << "\n Clock Lvl (0) = " << clocklvl << "\n Shift Lvl (0) = " << shiftlvl << "\n Test Pulse Lvl (0) = " << testpulselvl << std::endl;
        }
    }

    /// Write Num of Chans Register + Debug
    droopy = Sequencer->WriteNumberOfChannels(NUM_OF_GASSIPLEX_CHANNELS);
    if(droopy != cvSuccess){
        std::cerr << "#Interface::initializeHardware() : Error while writing sequencer's number of channels register." << std::endl;
        return droopy;
    }
    /// Debugging previous step::: Write numOfChans reg (@ seq)
    if(DEBUG){
        unsigned int nchan;
        droopy = Sequencer->ReadNumberOfChannels(nchan);
        if(droopy != cvSuccess){
            std::cerr << "#Interface::initializeHardware() : Error while reading number of channels." << std::endl;
            return droopy;
        }
        else{
            std::cout << "@@Interface::initializeHardware() : Number of Channels is (96) = " << nchan << std::endl;
        }
    }

    /// Write timing registers (all 5) + Debug
    /// --- T1 ----
    droopy = Sequencer->WriteT1Register(_T1_);
    if(droopy != cvSuccess){
        std::cerr << "#Interface::initializeHardware() : Error while writing sequencer's T1 register." << std::endl;
        return droopy;
    }
    /// Debugging previous step::: Write t1 reg (@ seq)
    if(DEBUG){
        unsigned int t1;
        droopy = Sequencer->ReadT1Register(t1);
        if(droopy!=cvSuccess){
            std::cerr << "@@Interface::initializeHardware() : Error while sequencer's reading t1 register." << std::endl;
        }
        else{
            std::cout << "@@Interface::initializeHardware() : T1 Register is (30) " << t1 << std::endl;
        }
    }
    /// --- T2 ----
    droopy = Sequencer->WriteT2Register(_T2_);
    if(droopy!=cvSuccess){
        std::cerr << "#Interface::initializeHardware() : Error while writing sequencer's T2 register." << std::endl;
        return droopy;
    }
    /// Debugging previous step::: Write t2 reg (@ seq)
    if(DEBUG){
        unsigned int t2;
        droopy = Sequencer->ReadT2Register(t2);
        if(droopy != cvSuccess){
            std::cerr << "#Interface::initializeHardware() : Error while reading sequencer's t2 register." << std::endl;
        }
        else{
            std::cout << "@@Interface::initializeHardware() : T2 (10) = " << t2 << std::endl;
        }
    }
    /// --- T3 ----
    droopy = Sequencer->WriteT3Register(_T3_);
    if(droopy!=cvSuccess){
        std::cerr << "#Interface::initializeHardware() : Error while writing sequencer's T3 register." << std::endl;
        return droopy;
    }
    /// Debugging previous step::: Write t3 reg (@ seq)
    if(DEBUG){
        unsigned int t3;
        droopy = Sequencer->ReadT3Register(t3);
        if(droopy != cvSuccess){
            std::cerr << "#Interface::initializeHardware() : Error while reading sequencer's t3 register." << std::endl;
        }
        else{
            std::cout << "@@Interface::initializeHardware() : T3 (5) = " << t3 << std::endl;
        }
    }
    /// --- T4 ----
    droopy = Sequencer->WriteT4Register(_T4_);
    if(droopy!=cvSuccess){
        std::cerr << "#Interface::initializeHardware() : Error while writing sequencer's T4 register." << std::endl;
        return droopy;
    }
    /// Debugging previous step::: Write t4 reg (@ seq)
    if(DEBUG){
        unsigned int t4;
        droopy = Sequencer->ReadT4Register(t4);
        if(droopy != cvSuccess){
            std::cerr << "#Interface::initializeHardware() : Error while reading sequencer's t4 register." << std::endl;
        }
        else{
            std::cout << "@@Interface::initializeHardware() : T4 (49) = " << t4 << std::endl;
        }
    }
    /// --- T5 ----
    droopy = Sequencer->WriteT5Register(_T5_);
    if(droopy!=cvSuccess){
        std::cerr << "#Interface::initializeHardware() : Error while writing sequencer's T5 register." << std::endl;
        return droopy;
    }
    /// Debugging previous step::: Write t5 reg (@ seq)
    if(DEBUG){
        unsigned int t5;
        droopy = Sequencer->ReadT5Register(t5);
        if(droopy != cvSuccess){
            std::cerr << "#Interface::initializeHardware() : Error while reading sequencer's t5 register." << std::endl;
        }
        else{
            std::cout << "@@Interface::initializeHardware() : T5 (13) = " << t5 << std::endl;
        }
    }

    /// ** Initializing Gate Generator **
    if(isThereGenerator==1){

        std::cout << "#Interface::initializeHardware() : Initializing Gate Generator..." << std::endl;
        droopy = GateGenerator->SetChannel0UpperDisplay(CH0_UPPER_DISPLAY);
        if(droopy != cvSuccess){
            std::cerr << "#Interface::initializeHardware() : Error while setting gate generator's channel 0 upper display." << std::endl;
            return droopy;
        }
        droopy = GateGenerator->SetChannel0LowerDisplay(CH0_LOWER_DISPLAY);
        if(droopy != cvSuccess){
            std::cerr << "#Interface::initializeHardware() : Error while setting gate generator's channel 0 lower display." << std::endl;
            return droopy;
        }
        droopy = GateGenerator->SetChannel1UpperDisplay(CH1_UPPER_DISPLAY);
        if(droopy != cvSuccess){
            std::cerr << "#Interface::initializeHardware() : Error while setting gate generator's channel 1 upper display." << std::endl;
            return droopy;
        }
        droopy = GateGenerator->SetChannel1LowerDisplay(CH1_LOWER_DISPLAY);
        if(droopy != cvSuccess){
            std::cerr << "#Interface::initializeHardware() : Error while setting gate generator's channel 1 lower display." << std::endl;
            return droopy;
        }

        std::cout << "#Interface::initializeHardware() : Gate generator initialized." << std::endl;
    }


    /// ** Initializing CRAMS **
    std::cout << "Interface::initializeHardware() : Initializing CRAMS..." << std::endl;
    for(int i=0; i<ui->numberOfCRAMSSpinBox->value(); i++){
        droopy = CRAMS.at(i)->WriteNumberOfChannels(NUM_OF_GASSIPLEX_CHANNELS_DCN, NUM_OF_GASSIPLEX_CHANNELS_DCN);
        if(droopy!=cvSuccess){
            std::cerr << "#Interface::initializeHardware() : Error while writing CRAMS[" << i << "] DCN register." << std::endl;
            break;
        }
        /// Debugging DCN's
        if(DEBUG){
            unsigned int DCN0,DCN1;
            droopy = CRAMS.at(i)->ReadNumberOfChannels(DCN0,DCN1);
            if(droopy != cvSuccess){
                std::cerr << "@@Interface::initializeHardware() : Error while reading CRAMS[" << i << "] DCN register." << std::endl;
            }
            else{
                std::cout << "@@Interface::initializeHardware() : * CRAMS[" << i << "] DCN's (3,3) = " << DCN0 << ", " << DCN1 << std::endl;
            }
        }

        /// Switch Memory owner to VME to set ped/thres
        droopy = CRAMS.at(i)->WriteStatusRegister(0,0);
        if(droopy != cvSuccess){
            std::cerr << "#Interface::initializeHardware() : Error while writing CRAMS[" << i << "]  status register." << std::endl;
            break;
        }

        /// Debugging mem owner
        if(DEBUG){
            V550_CRAMS::FIFOStatus fifo0status, fifo1status;
            bool testMode, memOwner, DRDYChan0, DRDYChan1;
            droopy = CRAMS.at(i)->ReadStatusRegister(testMode, memOwner, DRDYChan0, DRDYChan1, fifo0status, fifo1status);
            if(droopy!=cvSuccess){
                std::cerr << "@@Interface::initializeHardware() : Error while reading CRAMS[" << i << "]  status register." << std::endl;
                break;
            }
            else{
                std::cout << "@@Interface::initializeHardware() : CRAMS[" << i << "] is in status:\n fifo0status = " << fifo0status << "\n fifo1status" << fifo1status << std::endl;
            }
        }
        /// Looping to set ped/thres
        std::cout << "#Interface::initializeHardware() : Setting Pedestals & Thresholds to zero..." << std::endl;
        for(int j=0; j< 2; j++){
            for(int t=0; t< NUM_OF_GASSIPLEX_CHANNELS; t++){
                if( (droopy = CRAMS.at(i)->WritePedestalThreshold(j,t,0,0)) != cvSuccess ){
                    std::cerr << "#Interface::initializeHardware() : Error while setting pedestals and thresholds (CRAMS:" << i << ", FIFO:" << j << ", Channel:" << t << ")." << std::endl;
                }
                /// Debugging
                if(DEBUG){
                    unsigned int ped, thres;
                    if( (droopy = CRAMS.at(i)->ReadPedestalThreshold(j,t,ped,thres)) != cvSuccess ){
                        std::cerr << "@@Interface::initializeHardware() : Error while reading pedestals and thresholds (CRAMS:" << i << ", FIFO:" << j << ", Channel:" << t << ")." << std::endl;
                    }
                    else{
                        std::cout << "@@Interface::initializeHardware() : Reading Pedestal/Thresholds (0,0) : \t\t CRAM= " << i << "\t FIFO= " << j << "\t Chann= " << t << "\t VALUES = " << ped << ", " << thres << std::endl;
                    } /// end of debug

                }
            }//looping on chans
        }//looping on fifos
        /// Switching memory back to conversion logic
        droopy = CRAMS.at(i)->WriteStatusRegister(0,1);
        if(droopy != cvSuccess){
            std::cerr << "#Interface::initializeHardware() : Error while switching memory owner back to conversion logic (CRAMS" << i << ")." << std::endl;
            break;
        }
        /// Debugging
        if(DEBUG){
            V550_CRAMS::FIFOStatus fifo0status, fifo1status;
            bool testMode, memOwner, DRDYChan0, DRDYChan1;
            droopy = CRAMS.at(i)->ReadStatusRegister(testMode, memOwner, DRDYChan0, DRDYChan1, fifo0status, fifo1status);
            if (droopy != cvSuccess) {
                std::cout << "@@Interface::initializeHardware() : Error while reading CRAMS" << i << "'s status register after switching owner." << std::endl;
                break;
            }
            else {
                std::cout << "@@Interface::initializeHardware() : CRAMS[" << i << "] is in this status: \n fifo0status=" << fifo0status << "\n fifo1status=" << fifo1status << "\n DRDYChan0=" << DRDYChan0 << "\n DRDYChan1" << DRDYChan1 << "\n testMode=" << testMode << "\n memOwner=" << memOwner << std::endl;
            }
        }
        /// I set the status/id equal to the (dec) indicator of the CRAMS 0-3
        droopy = CRAMS.at(i)->WriteInterruptRegister(0,i);
        if(droopy != cvSuccess){
            std::cerr << "#Interface::initializeHardware() : Error while writing CRAMS" << i << "'s interrupt register." << std::endl;
            break;
        }
        /// Debugging
        if(DEBUG){
            V550_CRAMS::FIFOStatus fifo0status, fifo1status;
            bool testMode, memOwner, DRDYChan0, DRDYChan1;
            droopy = CRAMS.at(i)->ReadStatusRegister(testMode, memOwner, DRDYChan0, DRDYChan1, fifo0status, fifo1status);
            if (droopy != cvSuccess){
                std::cout << "@@Interface::initializeHardware() : Error while reading CRAMS"<<i<<"'s staturs register after setting interrupt registers." << std::endl;
                break;
            }
            else {
                std::cout << "@@Interface::initializeHardware() : Status register (0's): 0 \n CRAMS[" << i << "] is in this status: \n fifo0status=" << fifo0status << "\n fifo1status=" << fifo1status << "\n DRDYChan0=" << DRDYChan0 << "\n DRDYChan1" << DRDYChan1 << "\n testMode=" << testMode << "\n memOwner=" << memOwner << std::endl;
            }
        }
    }//for each crams


    /// ** Finalizing Sequencer Initialization **
    /// Write sequencer's interrupt vector register
    unsigned int seqStatusId = (BA_SEQUENCER >> 16 ) & 0xFF;
    droopy = Sequencer->WriteInterruptVectorRegister(seqStatusId);
    if(droopy != cvSuccess){
        std::cerr << "#Interface::initializeHardware : Error while writing sequencer's interrupt vector register." << std::endl;
        return droopy;
    }
    /// Write sequencer's interrupt level register
    droopy = Sequencer->WriteInterruptLevelRegister(1);
    if(droopy != cvSuccess){
        std::cerr << "#Interface::initializeHardware : Error while writing sequencer's interrupt level register." << std::endl;
        return droopy;
    }
    /// Clearing Module
    droopy = Sequencer->ClearModule();
    if(droopy != cvSuccess){
        std::cerr << "#Interface::initializeHardware : Error while clearing module after setting interrupt vector & level." << std::endl;
        return droopy;
    }
    /// Removing Sequencer's veto
    droopy = Sequencer->WriteStatusRegister(0,0,0);
    if(droopy != cvSuccess){
        std::cerr << "#Interface::initializeHardware : Error while removing sequencer's veto." << std::endl;
    }
    /// Debugging
    if(DEBUG) {
        bool intDelay, veto, autotrigger, drdy, busy, activeSequence;
        droopy = Sequencer->ReadStatusRegister(intDelay, veto, autotrigger, drdy, busy, activeSequence);
        if(droopy != cvSuccess){
            std::cerr << "@@Interface::initializeHardware : Error while reading sequencer's status register for the last time." << std::endl;
        }
        else{
            std::cout << "@@Interface::initializeHardware : Sequencer's Status Register: \n Internal Delay (0): " << intDelay << "\t Veto (0): " << veto << "\t Autotrigger (0): " << autotrigger << "\t DRDY (0): " <<drdy << "\t ActiveSequence(0) : " << activeSequence << std::endl;
        }
    }

    return droopy;
}

/// Initialize output files for writing (open readout file and write header)
int Interface::initializeOutputFiles(){
    int dripple = 0;
    handleOutputFilename();
    if(DEBUG)   std::cout << "@@Interface :: initialize :: Outputfilename is:" << outputFilename << std::endl;
    files.readout.open(outputFilename.c_str(), std::ios::out| std::ios::binary | std::ios::trunc ); //remove trunc after debug
    if(!files.readout.is_open()){
        dripple = -1;
    }
    dripple = generateHeader();
    return dripple;
}

/// Initialize input files (currently reads the mapping file)
int Interface::initializeInputFiles(const char *mapFilename){

    if(DEBUG) std::cout << "@@Interface::initializeInputFiles: Mapfilename is  " << mapFilename << std::endl;
    std::ifstream input(mapFilename);
    if(!input.is_open()){
        std::cerr << "#Interface::Initialize::initializeInputFiles : Cannot open mapping file." << std::endl;
        return -1;
    }
    std::string tmp[NUM_OF_GASSIPLEX_CHANNELS][2];
    int mapIntArray[NUM_OF_GASSIPLEX_CHANNELS][2];
    for(int i=0; i<NUM_OF_GASSIPLEX_CHANNELS; i++){
        for(int j=0; j<2; j++){
            input >> tmp[i][j];
            mapIntArray[i][j] = atoi(tmp[i][j].c_str());
        }
        chMap[i]=mapIntArray[i][1];
    }

//    //@@ Debug
//    for(int k=0; k<NUM_OF_GASSIPLEX_CHANNELS; k++){
//        std::cout << k << "\t" << chMap[k] << std::endl;
//    }
    input.close();
    return 0;
}

/// Wait for trigger (modifies the curCommand variable)
int Interface::waitForTrigger(command &curCommand){
    std::cout << "#Interface::WaitForTrigger : Enabling 0x1 with IRQEnable..." << std::endl;
    CVErrorCodes droopy;
    droopy = CAENVME_IRQEnable(controllerHandle, 0x1);
    if(droopy != cvSuccess){
        std::cerr << "#Interface::waitForTrigger() : Error while enabling interrupt request." << std::endl;
        return droopy;
    }
    std::cout << "#Interface::waitForTrigger() : Starting IRQWait on masked line 0x1 for " << IRQ_TIMEOUT << " milliseconds..." << std::endl;
    droopy = CAENVME_IRQWait(controllerHandle, 0x1, IRQ_TIMEOUT);
    if(droopy == cvSuccess){
        curCommand = TriggerArrived;
        std::cout << "#Interface::waitForTrigger : Trigger Arrived!" << std::endl;
        return droopy;
    }
    else if (droopy == cvTimeoutError) {
        curCommand = NoTrigger;
        std::cout << "#Interface::waitForTrigger : No triggers arrived! Timeout." << std::endl;
        droopy = cvSuccess; // there is no error to return, just no triggers
        return droopy;
    }
    else if(droopy != cvSuccess){
        std::cerr << "#Interface::waitForTrigger : Error while waiting for trigger." << std::endl;
    }

    return droopy;
}

/// The readout function. Loops on all CRAMS and FIFOs
int Interface::readout(){
    if((runInfo.eventNumber==0)||(runInfo.eventNumber%100==0)){
        //setLogEntry("[INFO] Readout in process.\n");
        std::stringstream tt;
        tt << "[INFO] Readout In process. Event Number = "<< runInfo.eventNumber<<".\n" ;
        std::string temp;
        setLogEntry(temp.c_str());
    }
    CVErrorCodes droopy;
    int numberOfWords = 0;
    int numberOfWordsRead = 0;
    int dripple = 0;
    /// Debugging numberOfWords
    std::cout << "@@DAQCycle::readout : Created and initialized to zero : numberOfWords=" << numberOfWords << " and numberOfWordsRead=" << numberOfWordsRead << std::endl;

    /// Creating readoutVector and initializing it to zero
    uint32_t readoutVector[NUM_OF_GASSIPLEX_CHANNELS];
    for(int k=0; k<NUM_OF_GASSIPLEX_CHANNELS; k++){
        readoutVector[k] = 0;
        if(DEBUG) std::cout << "@@DAQCycle::readout : After initialization readoutVector[" << k << "] = " << readoutVector[k] << std::endl;

    }

    /// Creating a union between hex/dec/char
    union{
        uint32_t hexadecimal;
        char bytes[4];
        int decimal;
    }representation;

    dripple = generateEventDataTop();
    if(dripple < 0){
        std::cerr << "#DAQCycle::readout()::generateEventDataTop() : Error while generating Event Data Top Header." << std::endl;
        return dripple;
    }

    // -----
//    if(runInfo.eventNumber%DISPLAY_REFRESH_RATE == 0){


//    }

    if(runInfo.eventNumber%100 ==0) std::cout << "~~~~~~~~~~~~~~~~~~~~~~~ EVENT : " << runInfo.eventNumber << " ~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
    /// Looping over CRAMS' and FIFO's
    for(int i=0; i < ui->numberOfCRAMSSpinBox->value(); i++){
        for(int j=0; j<2; j++){
            droopy = CRAMS.at(i)->ReadWordCounterRegister(j, numberOfWords);
            if(droopy!=cvSuccess){
                std::cerr << "#DAQCycle::readout : Error while reading word counter register of CRAMS" <<i << "  during readout." << std::endl;
                break;
            }
            /// Debugging RWC
            if(DEBUG) std::cout << "@@DAQCycle::readout : After read word counter register @ CRAMS" << i << " and for FIFO" << j << " numberOfWords is " << numberOfWords << std::endl;

            droopy = CRAMS.at(i)->ReadFIFOBLT(j, readoutVector, numberOfWords*4, &numberOfWordsRead);
            if(droopy != cvSuccess){
                std::cerr << "#DAQCycle::readout : Error while reading FIFO" << j << " in CRAMS" << i << " in BLT mode." << std::endl;
                break;
            }

            /// Debugging
            if(DEBUG) std::cout << "@@DAQCycle::readout : How many words are read??? Answer: " << numberOfWordsRead/4 << std::endl;

            // Exw parei to readoutVector mou edw
//            if(runInfo.eventNumber % DISPLAY_REFRESH_RATE == 0 || runInfo.eventNumber==1){
//                std::vector<uint32_t> temp;
//                for(unsigned int k=0;k<dataContainer.size(); k++){
//                    temp[k]=readoutVector[k];
//                }
//                dataContainer.push_back(temp);
//                temp.clear();
//            }


            if(files.readout.good()){
                /// Writing to file the number of CRAM
                representation.decimal = htonl(i);
                files.readout.write(representation.bytes, 4);

                /// Writing to file the number of FIFO
                representation.decimal = htonl(j);
                files.readout.write(representation.bytes, 4);

                /// Writing to file the number of words read
                representation.decimal = htonl(numberOfWordsRead/4);
                files.readout.write(representation.bytes, 4);

                for(int t=0; (t < numberOfWordsRead/4) && (t < 100); t++){
                    representation.hexadecimal = htonl(readoutVector[t]);
                    files.readout.write(representation.bytes, 4);
                    /// Debugging:
                    if((DEBUG_DEMUX) && ((runInfo.eventNumber==1) || (runInfo.eventNumber%1 ==0)) ){
                        demux(readoutVector[t],debugChan,debugData);
                        if(j==0){
                            if(debugData>30){
                            h1ff->Fill(chMap[debugChan], debugData);
                            h1fff->Fill(chMap[debugChan], 1.0);
                            }

                            h1gg->Fill(chMap[debugChan], debugData);
                            h1ggg->Fill(chMap[debugChan], 1.0);

                        }
                        else{
                            if(debugData>30){
                            h2ff->Fill(chMap[debugChan],debugData);
                            h2fff->Fill(chMap[debugChan], 1.0);
                            }

                            h2gg->Fill(chMap[debugChan], debugData);
                            h2ggg->Fill(chMap[debugChan], 1.0);
                        }
                        dummyIndex++;
                        if(DEBUG) std::cout << "@@DAQCycle::readout : Debugging readoutVector, for \t" << t << "\t (Chan,Data): " << debugChan << debugData  << std::endl;
                    }
                    else{
                        if(DEBUG) std::cout << "@@DAQCycle::readout : Debugging readoutVector, for \t" << t << "\t -> " << readoutVector[t] << std::endl;
                    }

                    /// DEBUG_DEMUX : Plot a histo every 500 events
            /*        if((DEBUG_DEMUX_PLOT) && (runInfo.eventNumber%DISPLAY_REFRESH_RATE==0)){
                        std::vector<uint32_t> dataCont;
                        for(int t=0; (t < numberOfWordsRead/4) && (t < 100); t++){
                            dataCont.push_back(readoutVector[t]);
                            }
                        startDisplayThread(dataCont, j);
                        std::cout << "Starting Display Thread. Num of Ev=" << runInfo.eventNumber << endl;
                    }//if((DEBUG_DEMUX) && (runInfo.eventNumber%500==0)){
            */
                }// looping and write
            }
            else{
                std::cerr << "#DAQCycle::readout : Fatal Error. File is not good() for writing." << std::endl;
                break;
            }

            /// Putting values for readout back to zero
            numberOfWords = 0;
            numberOfWordsRead = 0;
            for(int v = 0; v< NUM_OF_GASSIPLEX_CHANNELS; v++){
                readoutVector[v] = 0;
            }

        }//fifo looping

        /// Flushing after each FIFO is read
        files.readout.flush();

    }//crams looping
      if(runInfo.eventNumber % DISPLAY_REFRESH_RATE == 0 || runInfo.eventNumber==1){
          display();
      }

    std::cout << "Loop ended writing data bot" << std::endl;
    dripple = generateEventDataBot();
    if(dripple < 0){
        std::cerr << "#DAQCycle::readout()::generateEventDataBot() : Error while generating Event Data Bottom Header." << std::endl;
        return dripple;
    }


//    tqt = new TQtWidget(ui->displayWidget);
//    c1 = new TCanvas(tqt);
//    c1->cd();

//    HistoFill();

//    h1->Draw();

    /// Incrementing event Number
    std::cout << "@@DAQCycle::readout : Readout ended incrementing event number." << std::endl;
    dataContainer.clear();
    runInfo.eventNumber++;

    //if(DEBUG && DEBUG_READOUT) CVErrorCodes droopy = cvSuccess;
//    return droopy; //shouldn't this be dripple?

    //DEBUG
    //int dripple = 0;
    return dripple;
}


/// Finalize the daq cycle. Write footer and delete pointers
int Interface::finalize(){

    int dripple = generateTrailer();
    
    // *** debug
                c1ff->cd();
                c1ff->cd(1);
		h1ff->Draw();
		c1ff->cd(2);
		h2ff->Draw();
                c1ff->SaveAs("Weight_withCut.gif");

                c1fff->cd(1);
                h1fff->Draw();
                c1fff->cd(2);
                h2fff->Draw();
                c1fff->SaveAs("NoWeight_withCut.gif");

                c2gg->cd();
                c2gg->cd(1);
                h1gg->Draw();
                c2gg->cd(2);
                h2gg->Draw();
                c2gg->SaveAs("Weight_noCut.gif");

                c2ggg->cd();
                c2ggg->cd(1);
                h1ggg->Draw();
                c2ggg->cd(2);
                h2ggg->Draw();
                c2ggg->SaveAs("NoWeight_noCut.gif");

                rootFile = new TFile(rootFilename.c_str(), "recreate");
                h1ff->Write();
                h2ff->Write();
                h1fff->Write();
                h2fff->Write();
                h1gg->Write();
                h2gg->Write();
                h1ggg->Write();
                h2ggg->Write();

                rootFile->Close();

                /// **--
		std::cout << "dummyIndex = "  << dummyIndex << std::endl;
    
    // *** debug
    
    //-- changed 17/9/2011 to increment runNum
    runInfo.runNumber++;
    //---
    if(Sequencer) delete Sequencer;
    if(isThereGenerator==1 && GateGenerator) delete GateGenerator;
    for(unsigned int k=0; k<CRAMS.size(); k++){
        if(CRAMS.at(k)) delete CRAMS.at(k);
    }
	if(files.readout.is_open()) files.readout.close();
    // --- return initializeCheckBox CheckState back to unchecked
    ui->initializeCheckBox->setCheckState(Qt::Unchecked);
    // ---
    setLogEntry("[INFO] Run finalized.\n");
    loadConfiguration();
    setUpConfigurationTab();
    return dripple;
}

/// -----------------------*         Marker Functions       *--------------------------
/// Generate header (called when initializing output files)
int Interface::generateHeader(){
    int dripple = 0;
    if(files.readout.good()){
        union{
            uint32_t hexadecimal;
            char bytes[4];
            int integer;
        }header;

        /// 1. Header Begin
        header.hexadecimal = htonl(HEADER_BEGIN_MARKER);
        files.readout.write(header.bytes, 4);

        /// 2. Run Number
        header.integer = htonl(runInfo.runNumber);
        files.readout.write(header.bytes, 4);

        /// Date and Time
        time(&curTime);
        tm *ptr = gmtime(&curTime);
        /// 3. Start date of run
        header.integer = htonl((ptr->tm_year + 1900)*10000 + (ptr->tm_mon +1)*100 + ptr->tm_mday);
        files.readout.write(header.bytes,4);
        /// 4. Start time of run
        header.integer = htonl((ptr->tm_hour+1)*10000 + (ptr->tm_min + 1)*100 + ptr->tm_sec);
        files.readout.write(header.bytes, 4);
        /// 5. Type of run
        header.integer = htonl(runInfo.runType);
        files.readout.write(header.bytes, 4);
        /// 6. Header End
        header.hexadecimal = htonl(HEADER_END_MARKER);
        files.readout.write(header.bytes, 4);

        return dripple;
    }
    else{
        dripple = -1 ;
        return dripple;
    }
}

/// Generate the part of event data block which lies before the data (called inside readout())
int Interface::generateEventDataTop(){
    int dripple = 0;
    if(files.readout.good()){
        union{
            int integer;
            uint32_t hexadecimal;
            char bytes[4];
        }eventTop;

        /// 1. Event begin
        eventTop.hexadecimal = htonl(EVENT_BEGIN_MARKER);
        files.readout.write(eventTop.bytes, 4);

        /// 2. Event number
        eventTop.integer = htonl(runInfo.eventNumber);
        files.readout.write(eventTop.bytes, 4);

        /// 3. Start time of event
        time(&curTime);
        tm *ptr = gmtime(&curTime);
        eventTop.integer = htonl((ptr->tm_hour+1)*10000 + (ptr->tm_min + 1)*100 + ptr->tm_sec);
        files.readout.write(eventTop.bytes, 4);


        return dripple;

    }
    else{
        dripple = -1 ;
        return dripple;
    }
}

/// Generate the last part of event data block (called when the readout of an event is finished by readout())
int Interface::generateEventDataBot(){
    int dripple = 0;
    if(files.readout.good()){
        union {
            int integer;
            uint32_t hexadecimal;
            char bytes[4];
        }eventBot;

        eventBot.hexadecimal = htonl(EVENT_END_MARKER);
        files.readout.write(eventBot.bytes, 4);
    }
    else{
        dripple = -1;
        std::cerr << "#Interface::generateEventDataBot : Readout file is not good for writing." << std::endl;
    }

    return dripple;
}

/// Generate trailer (used to be called in the destructor of DAQ Class. NOW?????)
int Interface::generateTrailer(){
    int dripple = 0;
    if(files.readout.good()){
        union{
            int integer;
            char bytes[4];
            uint32_t hexadecimal;
        }trailer;

        /// 1. Trailer begin
        trailer.hexadecimal = htonl(TRAILER_BEGIN_MARKER);
        files.readout.write(trailer.bytes, 4);

        /// 2. Number of events in run
        trailer.integer = htonl(runInfo.eventNumber);
        files.readout.write(trailer.bytes, 4);

        /// 3. End Date
        time(&curTime);
        tm *ptr = gmtime(&curTime);
        trailer.integer = htonl( (ptr->tm_year + 1900)*10000 + (ptr->tm_mon + 1)*100 + ptr->tm_mday );
        files.readout.write(trailer.bytes, 4);

        /// 4. End time
        trailer.integer = htonl((ptr->tm_hour +1 )*10000 + (ptr->tm_min +1 )*100 + ptr->tm_sec);
        files.readout.write(trailer.bytes, 4);

        /// 5. Trailer end
        trailer.hexadecimal = htonl(TRAILER_END_MARKER);
        files.readout.write(trailer.bytes, 4);

        return dripple;
    }
    else{
        dripple = -1;
        return dripple;
    }
}

/// -----------------------*         Handler Functions       *--------------------------

/// Handle the run number
void Interface::handleRunNumber(){
    std::ofstream runNumberFile;
    runNumberFile.open("/home/nick/NTUADAQ_ALLTOP/inputFiles/runNumber.conf", std::ios::trunc);
    runNumberFile << "runNumber: " << runInfo.runNumber << std::endl;
    runNumberFile.close();
}

/// Handle the outputFilename for the readout file
void Interface::handleOutputFilename(){

    char special = '#';
    if(runInfo.runType == 0){
        special = 'D';
    }
    else if(runInfo.runType == 1){
        special = 'p';
    }
    else if(runInfo.runType == 2){
        special = 'T';
    }

    if(DEBUG) std::cout << "@@Interface::handleOutputFilename : runNumber is " << runInfo.runNumber << " and type " << runInfo.runType << std::endl;
    std::stringstream ss;
    ss << "run" << runInfo.runNumber << special << ".dat";
    ss >> outputFilename;

    std::stringstream xx;
    xx << "run" << runInfo.runNumber << special << ".root";
    xx >> rootFilename;

}

/// Reads a readoutVector during readout and mapps it according to a map file
void Interface::getReadoutVectorValues(uint32_t inputVector[]){
    unsigned int chNumber;
    unsigned int chData;
    for(int i=0; i<NUM_OF_GASSIPLEX_CHANNELS; i++){
        chNumber = (inputVector[i] & 0x7FF000) >> 12;
        chData   = (inputVector[i]& 0xFFF);
    }

}


//void Interface::OnRefreshTimer(){
//    gApplication->StartIdleing();
//    gSystem->InnerLoop();
//    gApplication->StopIdleing();
//}

//void Interface::Create(){
////    int wid = gVirtualX->AddWindow((ULong_t)getid(), getWidth(), getHeight());
//    int wid = gVirtualX->AddWindow((ULong_t)ui->displayWidget->winId(), 1010, 650);
////    fCanvas = new TCanvas("fCanvas", getWidth(), getHeight(), wid);
//    TCanvas *fCanvas = new TCanvas("fCanvas", 1010, 650, wid);
//    TH1F *f1 = new TH1F("h1","h1",200,0,100);
//    fCanvas->cd();
//    f1->Fill(10,10);
//    f1->Draw();
//    fCanvas->Update();
//}


void Interface::HistoFill(){
    if((runInfo.runNumber == 1) | (runInfo.runNumber%DISPLAY_REFRESH_RATE ==0)){
        h1->Fill(runInfo.runNumber, 1);
    }
}

/// #################################################################################
/// #                                                                               #
/// #                                    SLOTS                                      #
/// #                                                                               #
/// #################################################################################

/// Resets the configuration tab to its default values from the config file
void Interface::resetDefaultConfig(){
    readConfFile();
    setUpConfigurationTab();
    setLogEntry("[INFO] Configuration reset to default.\n");
}

/// Initializes the enableMaxEventNumber accordingly
void Interface::enableMaxNumberEvents(int state){
    if(state == 0){
        ui->maxNumOfEventsSpinBox->setEnabled(false);
        enableMaxEventNumber = 0 ;
    }
    else if(state == 2){
        ui->maxNumOfEventsSpinBox->setEnabled(true);
        enableMaxEventNumber = 1;
        ui->maxNumOfEventsSpinBox->setValue(MAX_NUMBER_OF_EVENTS);
    }


}

/// Reads the widgets of configuration tab and initializes the member variables
void Interface::applyConfiguration(){

    std::stringstream ss;

    // ----------
    headerBeginMarker = ui->headerBeginLineEdit->text().toStdString();
    ss << headerBeginMarker;
    ss >> std::hex >> HEADER_BEGIN_MARKER;
    ss.clear();
    if(DEBUG) std::cout << "@@Interface::applyConfiguration : HEADER BEGIN =" << std::hex << HEADER_BEGIN_MARKER << std::dec << std::endl;

    headerEndMarker = ui->headerEndLineEdit->text().toStdString();
    ss << headerEndMarker;
    ss >> std::hex >> HEADER_END_MARKER;
    ss.clear();
    if(DEBUG) std::cout << "@@Interface::applyConfiguration : HEADER END =" << std::hex << HEADER_END_MARKER << std::dec << std::endl;

    eventBeginMarker   = ui->eventBeginLineEdit->text().toStdString();
    ss << eventBeginMarker;
    ss >> std::hex >> EVENT_BEGIN_MARKER;
    ss.clear();
    if(DEBUG) std::cout << "@@Interface::applyConfiguration : EVENT BEGIN =" << std::hex << EVENT_BEGIN_MARKER << std::dec << std::endl;

    eventEndMarker      = ui->eventEndLineEdit->text().toStdString();
    ss << eventEndMarker;
    ss >> std::hex >> EVENT_END_MARKER;
    ss.clear();
    if(DEBUG) std::cout << "@@Interface::applyConfiguration : EVENT END =" << std::hex << EVENT_END_MARKER << std::dec << std::endl;

    trailerBeginMarker = ui->trailerBeginLineEdit->text().toStdString();
    ss << trailerBeginMarker;
    ss >> std::hex >> TRAILER_BEGIN_MARKER;
    ss.clear();
    if(DEBUG) std::cout << "@@Interface::applyConfiguration : TRAILER BEGIN =" << std::hex << TRAILER_BEGIN_MARKER << std::dec << std::endl;

    trailerEndMarker = ui->trailerEndLineEdit->text().toStdString();;
    ss << trailerEndMarker;
    ss >> std::hex >> TRAILER_END_MARKER;
    ss.clear();
    if(DEBUG) std::cout << "@@Interface::applyConfiguration : TRAILER END =" << std::hex << TRAILER_END_MARKER << std::dec << std::endl;


    /*
    * Gassiplex Stuff
    */
    NUM_OF_GASSIPLEX_CHANNELS = ui->numOfChansSpinBox->value();
    if(DEBUG) std::cout << "@@Interface::applyConfiguration : Num of Chans = " << NUM_OF_GASSIPLEX_CHANNELS << std::endl;


    NUM_OF_GASSIPLEX_CHANNELS_DCN = NUM_OF_GASSIPLEX_CHANNELS / 32;
    if(DEBUG) std::cout << "@@Interface::applyConfiguration : DCN = " << NUM_OF_GASSIPLEX_CHANNELS_DCN << std::endl;

    /*
   * NO OF CRAMS
   */
    NUMBER_OF_CRAMS = ui->numberOfCRAMSSpinBox->value();
    if(DEBUG) std::cout << "@@Interface::applyConfiguration : Num of CRAMS = " << NUMBER_OF_CRAMS << std::endl;

    /*
   * Base addresses
   */
    baSequencer = ui->BASequencerLineEdit->text().toStdString();
    ss << baSequencer;
    ss >> std::hex >> BA_SEQUENCER;
    ss.clear();
    if(DEBUG) std::cout << "@@Interface::applyConfiguration : BA_SEQUENCER = " << std::hex << BA_SEQUENCER << std::endl;

    // read CRAMS ba's
    baCramsStringVector.resize(ui->numberOfCRAMSSpinBox->value());
    if(DEBUG) std::cout << "@@Interface::applyConfiguration : Size of BA CRAMS STring VEctor = " << baCramsStringVector.size() << std::endl;

    baCramsVector.resize(ui->numberOfCRAMSSpinBox->value());
    if(DEBUG) std::cout << "@@Interface::applyConfiguration : Size of BA CRAMS VEctor = " << baCramsVector.size() << std::endl;

    for(int k=0; k<ui->numberOfCRAMSSpinBox->value(); k++){
        ss << cramsLineEdit[k]->text().toStdString();
        ss >> std::hex >> baCramsVector.at(k);
        ss.clear();
        if(DEBUG) std::cout << "@@Interface::applyConfiguration : baCramsVector.at(" << k << ") = " << std::hex << baCramsVector.at(k) << std::dec << std::endl;
    }

    /*
    * Timing Constants
    */
    _T1_ = ui->t1SpinBox->value();
    if(DEBUG) std::cout << "@@Interface::applyConfiguration :t1 val = " << _T1_ << std::endl;
    _T2_ = ui->t2SpinBox->value();
    if(DEBUG) std::cout << "@@Interface::applyConfiguration :t2 val = " << _T2_ << std::endl;
    _T3_ = ui->t3SpinBox->value();
    if(DEBUG) std::cout << "@@Interface::applyConfiguration :t3 val = " << _T3_ << std::endl;
    _T4_ = ui->t4SpinBox->value();
    if(DEBUG) std::cout << "@@Interface::applyConfiguration :t4 val = " << _T4_ << std::endl;
    _T5_ = ui->t5SpinBox->value();
    if(DEBUG) std::cout << "@@Interface::applyConfiguration :t5 val = " << _T5_ << std::endl;

    IRQ_TIMEOUT = ui->IRQTimeoutSpinBox->value();
    if(DEBUG) std::cout << "@@Interface::applyConfiguration :IRQ val = " << IRQ_TIMEOUT << std::endl;

    if(ui->maxNumEventsCheckBox->isChecked()){
        enableMaxEventNumber = 1;
        MAX_NUMBER_OF_EVENTS = ui->maxNumOfEventsSpinBox->value();
        if(DEBUG) std::cout << "@@Interface::applyConfiguration: MAX NUM OF EVENTS = " << MAX_NUMBER_OF_EVENTS << std::endl;

    }
    else{
        enableMaxEventNumber = 0;
    }

    if(ui->gateGeneratorCheckBox->isChecked()){
        isThereGenerator = 1;
        if(isThereGenerator == 1){
            baGateGenerator = ui->BAGateGeneratorLineEdit->text().toStdString();
            ss << baGateGenerator;
            ss >> std::hex >> BA_GATE_GENERATOR;
            ss.clear();

            if(DEBUG) std::cout << "@@Interface::applyConfiguration: ba Gate Generator: " << std::hex << BA_GATE_GENERATOR << std::dec << std::endl;

            CH0_UPPER_DISPLAY = ui->CH0UpperSpinBox->value();
            if(DEBUG) std::cout << "@@Interface::applyConfiguration: CH0 U " << CH0_UPPER_DISPLAY << std::endl;
            CH0_LOWER_DISPLAY = ui->CH0LowerSpinBox->value();
            if(DEBUG) std::cout << "@@Interface::applyConfiguration: CH0 L " << CH0_LOWER_DISPLAY << std::endl;
            CH1_UPPER_DISPLAY = ui->CH1UpperSpinBox->value();
            if(DEBUG) std::cout << "@@Interface::applyConfiguration: CH1 U " << CH1_UPPER_DISPLAY << std::endl;
            CH1_LOWER_DISPLAY = ui->CH1LowerSpinBox->value();
            if(DEBUG) std::cout << "@@Interface::applyConfiguration: CH1 L " << CH1_LOWER_DISPLAY << std::endl;
        }// if is checked
        else{
            isThereGenerator = 0;
        }

    }




    CONFIGURATION_FILE_PATH = ui->configurationFilePathLineEdit->text().toStdString();
    if(DEBUG) std::cout << "@@Interface::applyConfiguration: CONFIG FILE PATH: " << CONFIGURATION_FILE_PATH << std::endl;

    MAPPING_FILE_PATH = ui->mappingFilePathLineEdit->text().toStdString();
    if(DEBUG) std::cout << "@@Interface::applyConfiguration: MAPPIGN FILE PATH" << MAPPING_FILE_PATH << std::endl;

    runInfo.runNumber = ui->runNumberSpinBox->value();
    if(DEBUG) std::cout << "@@Interface::applyConfiguration: Run Number = " << runInfo.runNumber << std::endl;

    handleRunNumber();

    // DEBUG
    if(DEBUG) {
        for(int j=0; j<ui->numberOfCRAMSSpinBox-> value(); j++){
            std::cout << "@@Interface::applyCRAMS DEBUG Addresses " << j << " : " <<  std::hex << baCramsVector.at(j) << std::dec << std::endl;
        }
    }
    dataContainer.resize(NUMBER_OF_CRAMS*2);

    setLogEntry("[INFO] Applied new configuration.\n");

}

/// Loads new configuration if config file path is changed
void Interface::loadConfiguration(){
    readConfFile();
    setUpConfigurationTab();

    setLogEntry("[INFO] New configuration is loaded via file.\n");
}

/// Enables/Disables a CRAMS LineEdit
void Interface::changeNumberOfCrams(int newVal){
    for(int k=0; k<newVal; k++){
        cramsLineEdit[k]->setEnabled(true);
    }
    for(int k=newVal; k<10; k++){
        cramsLineEdit[k]->setEnabled(false);
    }
}

/// If the gate generator checkbox is checked/unchecked enables/disables the
/// children widgets and sets the isThereGateGenerator value.
void Interface::unlockGateGeneratorConf(int state){
    //    bool checker = ui->t1SpinBox->isEnabled();


    if(state==2){
        ui->CH0LowerSpinBox->setEnabled(true);
        ui->CH0UpperSpinBox->setEnabled(true);
        ui->CH1LowerSpinBox->setEnabled(true);
        ui->CH1UpperSpinBox->setEnabled(true);

        ui->BAGateGeneratorLineEdit->setText((QString) baGateGenerator.c_str());
        ui->CH0LowerSpinBox->setValue(CH0_UPPER_DISPLAY);
        ui->CH0UpperSpinBox->setValue(CH0_LOWER_DISPLAY);
        ui->CH1LowerSpinBox->setValue(CH1_UPPER_DISPLAY);
        ui->CH1UpperSpinBox->setValue(CH1_LOWER_DISPLAY);

        ui->BAGateGeneratorLineEdit->setEnabled(true);
        isThereGenerator = 1;
    }
    else if(state==0){
        lockGateGeneratorConf();
        isThereGenerator = 0;
    }


}

/// Unlocks expert mode
void Interface::unlockExpertMode(){
    bool checker = ui->t1SpinBox->isEnabled();
    // Enable timing editing
    ui->    t1SpinBox-> setEnabled(!checker);
    ui->    t2SpinBox-> setEnabled(!checker);
    ui->    t3SpinBox-> setEnabled(!checker);
    ui->    t4SpinBox-> setEnabled(!checker);
    ui->    t5SpinBox-> setEnabled(!checker);

    // Enable readout markers editing
    ui->    headerBeginLineEdit->   setEnabled(!checker);
    ui->    headerEndLineEdit->     setEnabled(!checker);
    ui->    eventBeginLineEdit->    setEnabled(!checker);
    ui->    eventEndLineEdit->      setEnabled(!checker);
    ui->    trailerBeginLineEdit->   setEnabled(!checker);
    ui->    trailerEndLineEdit->     setEnabled(!checker);

    // Enable FEC values editing
    ui->    numOfChansSpinBox-> setEnabled(!checker);
    ui->    IRQTimeoutSpinBox-> setEnabled(!checker);

    if(!checker){
        ui->unlockButton->setText("Lock");
        setLogEntry("[INFO] Expert mode unlocked.\n");
    }
    else{
        ui->unlockButton->setText("Unlock");
        setLogEntry("[INFO] Expert mode locked.\n");
    }
}

/// Waits for triggers and starts DAQ Cycle
void Interface::startDAQCycle(){

    // Debug
    if(DEBUG) std::cout << "StartDAQ button pressed!!" << std::endl;

    // Debug
    if(DEBUG) {
        if(ui->stopCycleCheckBox->isChecked()){
            std::cout << "@@Interface::startDAQCycle : StopCycleCheckBox is checked" << std::endl;
        }
        else{
            std::cout << "@@Interface::startDAQCycle : StopCycleCheckBox is unchecked" << std::endl;
        }
    }
    ui->stopCycleCheckBox->setChecked(false);

    // Debug
    if(DEBUG) {
        if(ui->stopCycleCheckBox->isChecked()){
            std::cout << "@@Interface::startDAQCycle : StopCycleCheckBox is checked" << std::endl;
        }
        else{
            std::cout << "@@Interface::startDAQCycle : StopCycleCheckBox is unchecked" << std::endl;
        }
    }

    // Entering a log entry about starting run
    setLogEntry("[INFO] Starting new run.\n");

    // When the run starts you can stop it by stop button but you cannot press start again
    ui->stopButton->setEnabled(true);
    ui->startButton->setEnabled(false);

    //debug
    if(DEBUG) std::cout << "@@Interface::startDAQCycle : Starting if(enableMaxEventNumber) " << std::endl;
   if(enableMaxEventNumber==1){
       curCommand = NoTrigger;

       // debug
       if(DEBUG) std::cout << "@@Interface::startDAQCycle : curCommand is :  " << curCommand << ".. Staring while loop.. " << std::endl;
       while(runInfo.eventNumber < ui->maxNumOfEventsSpinBox->value()){//MAX_NUMBER_OF_EVENTS){
           int dripple = waitForTrigger(curCommand);

           if(ui->stopCycleCheckBox->checkState()==2){
               curCommand = CloseRun;
           }

            if(curCommand == NoTrigger){
                std::cout << "#Interface::startDAQCycle(DAQCycle::waitForTrigger) : No triggers arrived. Closing run and reseting hardware." << std::endl;
                //dripple = initialize();   --- change it to do sth
                if(dripple < 0 ){
                    std::cerr << "#Interface::startDAQCycle(DAQCycle::waitForTrigger) : Error while resetting hardware." << std::endl;
                    break;
                   }
               }
            else if(curCommand == TriggerArrived){
                std::cout << "#Interface::startDAQCycle(DAQCycle::waitForTrigger) : Trigger Arrived. Starting readout!" << std::endl;
                dripple = readout();
                if(dripple < 0){
                    std::cerr << "#Interface::startDAQCycle(DAQCycle::waitForTrigger) : Error while reading out data." << std::endl;
                   }
               }
            else if(curCommand == CloseRun){
                //dripple = finalize();  eixa finalize edw 8elei apla break afou to finalize to kanei eksw apo th loop
                break;
                if(dripple<0) {
                    std::cerr << "#Interface::startDAQCycle(4) : Error while finalizing run." << std::endl;
                }
            }


       }//while
       int dripple = finalize(); // ends the file and DAQ modules when the loop is over
       if(dripple<0) {
           std::cerr << "#Interface::startDAQCycle(2) : Error while finalizing run." << std::endl;
       }

   }//if
   else{
       while(curCommand != CloseRun){
           int dripple = waitForTrigger(curCommand);

           if(ui->stopCycleCheckBox->checkState()==2) curCommand = CloseRun;

           if(curCommand == NoTrigger){
               std::cout << "#Interface::startDAQCycle(DAQCycle::waitForTrigger) : No triggers arrived. Closing run and reseting hardware." << std::endl;
              //  dripple = initialize(); -- change it to do sth
               if(dripple < 0 ){
                   std::cerr << "#Interface::startDAQCycle(DAQCycle::waitForTrigger) : Error while resetting hardware." << std::endl;
                   break;
               }
           }
           else if(curCommand == TriggerArrived){
               std::cout << "#Interface::startDAQCycle(DAQCycle::waitForTrigger) : Trigger Arrived. Starting readout!" << std::endl;
               dripple = readout();
               if(dripple < 0){
                   std::cerr << "#Interface::startDAQCycle(DAQCycle::waitForTrigger) : Error while reading out data." << std::endl;
                   break;
               }
           }
           else if(curCommand == CloseRun){
               //dripple = finalize(); eixa finalize edw 8elei apla break afou to finalize to kanei eksw apo th loop
               break;
               if(dripple < 0){
                   std::cerr << "#Interface::startDAQCycle(3) : Error while finalizing run." << std::endl;
               }
           }

       }//while
        int dripple = finalize(); // ends the file and DAQ modules when the loop is over
        if(dripple<0) {
            std::cerr << "#Interface::startDAQCycle(4) : Error while finalizing run." << std::endl;
        }
   }//else

}


/// Stops daq cycle by checking the stopDAQCycle checkbox
void Interface::stopDAQCycle(){
    ui->stopCycleCheckBox->setChecked(true);
    setLogEntry("[INFO] Stopping current run.\n");
    runInfo.eventNumber=0;
}

/// Initializes VME create communication, modules and files.
void Interface::initializeDAQ(){
    int dripple = initialize();
    if(dripple<0){
        std::cerr << "#Interface::initialize() : FATAL ERROR! Cannot initialize run." << std::endl;
    }
}

void Interface::cancelInitialization(){
    if(Sequencer) delete Sequencer;
    if(isThereGenerator==1){
        if(GateGenerator) delete GateGenerator;
    }
    for(int k=0; k<ui->numberOfCRAMSSpinBox->value(); k++){
        if(CRAMS.at(k)) delete CRAMS.at(k);
    }

    if(files.readout.is_open()){
        files.readout.close();
    }

    ui->initializeCheckBox->setCheckState(Qt::Unchecked);
    ui->startButton->setEnabled(false);
    setLogEntry("[INFO] Initialization cancelled.\n");
}

/// Testing for ROOT display
void Interface::display(){

//    std::cout<< " ~~~~~~ starting display ~~~~~~~~~~~~~~~~~~ " << std::endl;
//    c1->cd();
//    TH1F *f1 = new TH1F("h1","h1", 400,0,400);
//    f1->Fill(100,100);
//    f1->Draw();
// //   for(unsigned int i = 0; i<dataContainer.size();i++){
//        for(unsigned int j =0; j<dataContainer.at(i).size(); j++){
//            unsigned int chNumber;
//            unsigned int chData;
//                chNumber = ((dataContainer.at(i)).at(j) & 0x7FF000) >> 12;
//                chData   = ((dataContainer.at(i)).at(j) & 0xFFF);
//                histoContainer.at(i)->Fill(chMap[chNumber],chData);
//            }
//    }

//    /// EDW XREAIZOMAI TO MAPPING !!!!!

//  //  for(unsigned int k=0; k<histoContainer.size(); k++){
//        c1->cd(k+1);
//        histoContainer.at(k)->Draw();
//    }
}

void Interface::setupCanvas(){
    c1 = new TCanvas("Online Display", "Online Display", 700, 1100);
    if(NUMBER_OF_CRAMS<6){
        c1->Divide(2,NUMBER_OF_CRAMS);
    }
    else if(NUMBER_OF_CRAMS == 6){
        c1->Divide(3,4);
    }
    else if(NUMBER_OF_CRAMS == 7){
        c1->Divide(2,7);
    }
    else if(NUMBER_OF_CRAMS == 8){
        c1->Divide(4,4);
    }
    else if(NUMBER_OF_CRAMS == 9){
        c1->Divide(3,6);
    }

    /// Initialize Histograms
    for(unsigned int k=0; k< dataContainer.size(); k++){
        std::stringstream ss;
        ss << "Chamber " << k ;
        std::string name;
        ss >> name;
        histoContainer.at(k) = new TH1F(name.c_str(), name.c_str(), NUM_OF_GASSIPLEX_CHANNELS-1,0,NUM_OF_GASSIPLEX_CHANNELS-1);
        ss.clear();
    }
}


void Interface::startDAQThread(){
    QFuture<void> future = QtConcurrent::run(this, &Interface::startDAQCycle);
    //watcher.setFuture(future);
}


void Interface::startDisplayThread(std::vector<uint32_t> vec, int whichFifo){
    QFuture<void> future2 = QtConcurrent::run(this, &Interface::displayCycle, vec, whichFifo);
}

void Interface::displayCycle(std::vector<uint32_t> vec, int whichFifo){

    delete gDirectory->FindObject("h1f");
    delete gDirectory->FindObject("h2f");

    canvas->setUpdatesEnabled(kFALSE);
    //
    // Create a one dimensional histogram (one float per bin)
    // and fill it following the distribution in function sqroot.
    //
    canvas->getCanvas()->cd();
    canvas->getCanvas()->Divide(2,1);
    canvas->getCanvas()->GetFrame()->SetFillColor(42);
    canvas->getCanvas()->GetFrame()->SetBorderMode(-1);
    canvas->getCanvas()->GetFrame()->SetBorderSize(0);
    TH1F *h1f = new TH1F("Chamber X","Chamber X",96,0,96);
    TH1F *h2f = new TH1F("Chamber Y","Chamber Y",96,0,96);
    h1f->SetFillColor(45);
    h2f->SetFillColor(45);
    for(int h=0; h < vec.size(); h++){
        demux(vec.at(h), debugChan, debugData);
        if(whichFifo==0){
            h1f->Fill(chMap[debugChan],debugData);
        }
        else{
            h2f->Fill(chMap[debugChan],debugData);
        }
    }
    canvas->getCanvas()->cd(1);
    h1f->Draw();
    canvas->getCanvas()->cd(2);
    h2f->Draw();
    canvas->getCanvas()->Modified();
    canvas->getCanvas()->Update();

}


void Interface::clicked1()
{
   /*TFormula *form1 = new TFormula("form1","abs(sin(x)/x)");
   TF1 *sqroot = new TF1("sqroot","x*gaus(0) + [3]*form1",0,10);
   sqroot->SetParameters(10,4,1,20);
*/
   // hack to keep the histogram displayed on the canvas while resizing
   // waiting for any Qt expert to fix this...
   canvas->setUpdatesEnabled(kFALSE);
   //
   // Create a one dimensional histogram (one float per bin)
   // and fill it following the distribution in function sqroot.
   //
   delete gDirectory->FindObject("h1f");
   canvas->getCanvas()->cd();
   canvas->getCanvas()->Divide(2,1);
   canvas->getCanvas()->cd(1);
   canvas->getCanvas()->GetFrame()->SetFillColor(42);
   canvas->getCanvas()->GetFrame()->SetBorderMode(-1);
   canvas->getCanvas()->GetFrame()->SetBorderSize(0);
   TH1F *h1f = new TH1F("h1f","Test random numbers",200,0,10);
   h1f->SetFillColor(45);
   h1f->FillRandom("gaus",10000);
   h1f->Draw();
   canvas->getCanvas()->Modified();
   canvas->getCanvas()->Update();
}

void Interface::handle_root_events()
{
   //call the inner loop of ROOT
   gSystem->ProcessEvents();
}

