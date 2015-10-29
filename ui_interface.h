/********************************************************************************
** Form generated from reading UI file 'interface.ui'
**
** Created: Mon Oct 3 13:18:17 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACE_H
#define UI_INTERFACE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Interface
{
public:
    QWidget *centralWindow;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *initializeButton;
    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *helpButton;
    QPushButton *closeButton;
    QPushButton *cancelInitializationButton;
    QFrame *line_3;
    QFrame *line_4;
    QTabWidget *tabWidget;
    QWidget *displayTab;
    QWidget *displayWidget;
    QWidget *sequencerTab;
    QGroupBox *sequencerGroupBox;
    QLabel *BASequencerLabel;
    QLabel *t1Label;
    QLabel *t2Label;
    QLabel *t3Label;
    QLabel *t4Label;
    QLabel *t5Label;
    QLineEdit *BASequencerLineEdit;
    QSpinBox *t1SpinBox;
    QSpinBox *t2SpinBox;
    QSpinBox *t3SpinBox;
    QSpinBox *t4SpinBox;
    QSpinBox *t5SpinBox;
    QFrame *sequencerHorizontalLine;
    QGroupBox *gateGeneratorGroupBox;
    QCheckBox *gateGeneratorCheckBox;
    QLabel *CH0UpperLabel;
    QLabel *CH0LowerLabel;
    QLabel *CH1UpperLabel;
    QLabel *CH1LowerLabel;
    QSpinBox *CH0UpperSpinBox;
    QSpinBox *CH0LowerSpinBox;
    QSpinBox *CH1UpperSpinBox;
    QSpinBox *CH1LowerSpinBox;
    QLabel *gateGeneratorBALabel;
    QLineEdit *BAGateGeneratorLineEdit;
    QFrame *line_2;
    QGroupBox *markersGroupBox;
    QLabel *headerBeginLabel;
    QLabel *headerEndLabel;
    QLabel *eventBeginLabel;
    QLabel *eventEndLabel;
    QLabel *footerBeginLabel;
    QLabel *footerEndLabel;
    QLineEdit *headerBeginLineEdit;
    QLineEdit *headerEndLineEdit;
    QLineEdit *eventBeginLineEdit;
    QLineEdit *eventEndLineEdit;
    QLineEdit *trailerBeginLineEdit;
    QLineEdit *trailerEndLineEdit;
    QGroupBox *CRAMSGroupBox;
    QWidget *gridLayoutWidget_2;
    QGridLayout *cramsGridLayout;
    QLabel *numOfCramsLabel;
    QSpinBox *numberOfCRAMSSpinBox;
    QGroupBox *miscGroupBox;
    QLabel *numOfGassiplexChansLabel;
    QCheckBox *maxNumEventsCheckBox;
    QLabel *IRQTimeoutLabel;
    QSpinBox *numOfChansSpinBox;
    QSpinBox *maxNumOfEventsSpinBox;
    QSpinBox *IRQTimeoutSpinBox;
    QFrame *line;
    QLabel *configurationFilePathLabel;
    QLineEdit *configurationFilePathLineEdit;
    QLineEdit *mappingFilePathLineEdit;
    QLabel *mappingFilePathLabel;
    QLabel *displayRefresRateLabel;
    QSpinBox *displayRefreshRateSpinBox;
    QPushButton *applyConfigButton;
    QGroupBox *runGroupBox;
    QLabel *runNumberLabel;
    QLabel *typeOfRunLabel;
    QSpinBox *runNumberSpinBox;
    QComboBox *typeOfRunComboBox;
    QPushButton *unlockButton;
    QPushButton *resetDefaultsButton;
    QWidget *logTab;
    QPlainTextEdit *logTextEdit;
    QPushButton *clearLogButton;
    QWidget *aboutTab;
    QLabel *aboutNtuaLabel;
    QLabel *aboutTitleLabel;
    QLabel *aboutVersionLabel;
    QLabel *aboutCreatedByLabel;
    QLabel *aboutMyNameLabel;
    QLabel *aboutDateLabel;
    QCheckBox *stopCycleCheckBox;
    QLabel *ntuaLabel;
    QCheckBox *initializeCheckBox;

    void setupUi(QMainWindow *Interface)
    {
        if (Interface->objectName().isEmpty())
            Interface->setObjectName(QString::fromUtf8("Interface"));
        Interface->resize(1194, 750);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Interface->sizePolicy().hasHeightForWidth());
        Interface->setSizePolicy(sizePolicy);
        Interface->setAutoFillBackground(true);
        Interface->setUnifiedTitleAndToolBarOnMac(true);
        centralWindow = new QWidget(Interface);
        centralWindow->setObjectName(QString::fromUtf8("centralWindow"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWindow->sizePolicy().hasHeightForWidth());
        centralWindow->setSizePolicy(sizePolicy1);
        centralWindow->setAutoFillBackground(false);
        gridLayoutWidget = new QWidget(centralWindow);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(1060, 410, 111, 291));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        gridLayoutWidget->setFont(font);
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        initializeButton = new QPushButton(gridLayoutWidget);
        initializeButton->setObjectName(QString::fromUtf8("initializeButton"));
        initializeButton->setFont(font);

        gridLayout->addWidget(initializeButton, 0, 0, 1, 1);

        startButton = new QPushButton(gridLayoutWidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setEnabled(false);
        startButton->setFont(font);

        gridLayout->addWidget(startButton, 3, 0, 1, 1);

        stopButton = new QPushButton(gridLayoutWidget);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));
        stopButton->setEnabled(false);
        stopButton->setFont(font);

        gridLayout->addWidget(stopButton, 4, 0, 1, 1);

        helpButton = new QPushButton(gridLayoutWidget);
        helpButton->setObjectName(QString::fromUtf8("helpButton"));
        helpButton->setFont(font);

        gridLayout->addWidget(helpButton, 6, 0, 1, 1);

        closeButton = new QPushButton(gridLayoutWidget);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setFont(font);

        gridLayout->addWidget(closeButton, 7, 0, 1, 1);

        cancelInitializationButton = new QPushButton(gridLayoutWidget);
        cancelInitializationButton->setObjectName(QString::fromUtf8("cancelInitializationButton"));
        cancelInitializationButton->setEnabled(false);

        gridLayout->addWidget(cancelInitializationButton, 1, 0, 1, 1);

        line_3 = new QFrame(gridLayoutWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_3, 2, 0, 1, 1);

        line_4 = new QFrame(gridLayoutWidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_4, 5, 0, 1, 1);

        tabWidget = new QTabWidget(centralWindow);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(20, 10, 1031, 701));
        tabWidget->setFont(font);
        displayTab = new QWidget();
        displayTab->setObjectName(QString::fromUtf8("displayTab"));
        displayWidget = new QWidget(displayTab);
        displayWidget->setObjectName(QString::fromUtf8("displayWidget"));
        displayWidget->setGeometry(QRect(10, 10, 1011, 651));
        tabWidget->addTab(displayTab, QString());
        sequencerTab = new QWidget();
        sequencerTab->setObjectName(QString::fromUtf8("sequencerTab"));
        sequencerGroupBox = new QGroupBox(sequencerTab);
        sequencerGroupBox->setObjectName(QString::fromUtf8("sequencerGroupBox"));
        sequencerGroupBox->setGeometry(QRect(10, 10, 351, 211));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setUnderline(false);
        sequencerGroupBox->setFont(font1);
        BASequencerLabel = new QLabel(sequencerGroupBox);
        BASequencerLabel->setObjectName(QString::fromUtf8("BASequencerLabel"));
        BASequencerLabel->setGeometry(QRect(0, 30, 171, 17));
        BASequencerLabel->setFont(font);
        t1Label = new QLabel(sequencerGroupBox);
        t1Label->setObjectName(QString::fromUtf8("t1Label"));
        t1Label->setGeometry(QRect(0, 70, 141, 17));
        t1Label->setFont(font);
        t2Label = new QLabel(sequencerGroupBox);
        t2Label->setObjectName(QString::fromUtf8("t2Label"));
        t2Label->setGeometry(QRect(0, 100, 161, 17));
        t2Label->setFont(font);
        t3Label = new QLabel(sequencerGroupBox);
        t3Label->setObjectName(QString::fromUtf8("t3Label"));
        t3Label->setGeometry(QRect(0, 130, 151, 17));
        t3Label->setFont(font);
        t4Label = new QLabel(sequencerGroupBox);
        t4Label->setObjectName(QString::fromUtf8("t4Label"));
        t4Label->setGeometry(QRect(0, 160, 261, 17));
        t4Label->setFont(font);
        t5Label = new QLabel(sequencerGroupBox);
        t5Label->setObjectName(QString::fromUtf8("t5Label"));
        t5Label->setGeometry(QRect(0, 190, 171, 17));
        t5Label->setFont(font);
        BASequencerLineEdit = new QLineEdit(sequencerGroupBox);
        BASequencerLineEdit->setObjectName(QString::fromUtf8("BASequencerLineEdit"));
        BASequencerLineEdit->setGeometry(QRect(210, 20, 121, 27));
        BASequencerLineEdit->setFont(font);
        t1SpinBox = new QSpinBox(sequencerGroupBox);
        t1SpinBox->setObjectName(QString::fromUtf8("t1SpinBox"));
        t1SpinBox->setGeometry(QRect(270, 60, 59, 27));
        t1SpinBox->setFont(font);
        t1SpinBox->setMaximum(255);
        t2SpinBox = new QSpinBox(sequencerGroupBox);
        t2SpinBox->setObjectName(QString::fromUtf8("t2SpinBox"));
        t2SpinBox->setGeometry(QRect(270, 90, 59, 27));
        t2SpinBox->setFont(font);
        t2SpinBox->setMinimum(10);
        t2SpinBox->setMaximum(511);
        t3SpinBox = new QSpinBox(sequencerGroupBox);
        t3SpinBox->setObjectName(QString::fromUtf8("t3SpinBox"));
        t3SpinBox->setGeometry(QRect(270, 120, 59, 27));
        t3SpinBox->setFont(font);
        t3SpinBox->setMinimum(1);
        t3SpinBox->setMaximum(255);
        t4SpinBox = new QSpinBox(sequencerGroupBox);
        t4SpinBox->setObjectName(QString::fromUtf8("t4SpinBox"));
        t4SpinBox->setGeometry(QRect(270, 150, 59, 27));
        t4SpinBox->setFont(font);
        t4SpinBox->setMinimum(1);
        t4SpinBox->setMaximum(511);
        t5SpinBox = new QSpinBox(sequencerGroupBox);
        t5SpinBox->setObjectName(QString::fromUtf8("t5SpinBox"));
        t5SpinBox->setGeometry(QRect(270, 180, 59, 27));
        t5SpinBox->setFont(font);
        t5SpinBox->setMinimum(2);
        t5SpinBox->setMaximum(511);
        sequencerHorizontalLine = new QFrame(sequencerGroupBox);
        sequencerHorizontalLine->setObjectName(QString::fromUtf8("sequencerHorizontalLine"));
        sequencerHorizontalLine->setGeometry(QRect(80, 50, 161, 16));
        sequencerHorizontalLine->setFont(font);
        sequencerHorizontalLine->setFrameShape(QFrame::HLine);
        sequencerHorizontalLine->setFrameShadow(QFrame::Sunken);
        gateGeneratorGroupBox = new QGroupBox(sequencerTab);
        gateGeneratorGroupBox->setObjectName(QString::fromUtf8("gateGeneratorGroupBox"));
        gateGeneratorGroupBox->setGeometry(QRect(690, 10, 301, 211));
        gateGeneratorGroupBox->setFont(font1);
        gateGeneratorCheckBox = new QCheckBox(gateGeneratorGroupBox);
        gateGeneratorCheckBox->setObjectName(QString::fromUtf8("gateGeneratorCheckBox"));
        gateGeneratorCheckBox->setGeometry(QRect(0, 20, 201, 22));
        gateGeneratorCheckBox->setFont(font);
        CH0UpperLabel = new QLabel(gateGeneratorGroupBox);
        CH0UpperLabel->setObjectName(QString::fromUtf8("CH0UpperLabel"));
        CH0UpperLabel->setGeometry(QRect(0, 100, 171, 17));
        CH0UpperLabel->setFont(font);
        CH0LowerLabel = new QLabel(gateGeneratorGroupBox);
        CH0LowerLabel->setObjectName(QString::fromUtf8("CH0LowerLabel"));
        CH0LowerLabel->setGeometry(QRect(0, 130, 171, 17));
        CH0LowerLabel->setFont(font);
        CH1UpperLabel = new QLabel(gateGeneratorGroupBox);
        CH1UpperLabel->setObjectName(QString::fromUtf8("CH1UpperLabel"));
        CH1UpperLabel->setGeometry(QRect(0, 160, 171, 17));
        CH1UpperLabel->setFont(font);
        CH1LowerLabel = new QLabel(gateGeneratorGroupBox);
        CH1LowerLabel->setObjectName(QString::fromUtf8("CH1LowerLabel"));
        CH1LowerLabel->setGeometry(QRect(0, 190, 171, 17));
        CH1LowerLabel->setFont(font);
        CH0UpperSpinBox = new QSpinBox(gateGeneratorGroupBox);
        CH0UpperSpinBox->setObjectName(QString::fromUtf8("CH0UpperSpinBox"));
        CH0UpperSpinBox->setGeometry(QRect(240, 90, 59, 27));
        CH0UpperSpinBox->setFont(font);
        CH0UpperSpinBox->setMaximum(100000000);
        CH0LowerSpinBox = new QSpinBox(gateGeneratorGroupBox);
        CH0LowerSpinBox->setObjectName(QString::fromUtf8("CH0LowerSpinBox"));
        CH0LowerSpinBox->setGeometry(QRect(240, 120, 59, 27));
        CH0LowerSpinBox->setFont(font);
        CH0LowerSpinBox->setMaximum(100000000);
        CH1UpperSpinBox = new QSpinBox(gateGeneratorGroupBox);
        CH1UpperSpinBox->setObjectName(QString::fromUtf8("CH1UpperSpinBox"));
        CH1UpperSpinBox->setGeometry(QRect(240, 150, 59, 27));
        CH1UpperSpinBox->setFont(font);
        CH1UpperSpinBox->setMaximum(100000000);
        CH1LowerSpinBox = new QSpinBox(gateGeneratorGroupBox);
        CH1LowerSpinBox->setObjectName(QString::fromUtf8("CH1LowerSpinBox"));
        CH1LowerSpinBox->setGeometry(QRect(240, 180, 59, 27));
        CH1LowerSpinBox->setFont(font);
        CH1LowerSpinBox->setMaximum(100000000);
        gateGeneratorBALabel = new QLabel(gateGeneratorGroupBox);
        gateGeneratorBALabel->setObjectName(QString::fromUtf8("gateGeneratorBALabel"));
        gateGeneratorBALabel->setGeometry(QRect(0, 60, 101, 17));
        gateGeneratorBALabel->setFont(font);
        BAGateGeneratorLineEdit = new QLineEdit(gateGeneratorGroupBox);
        BAGateGeneratorLineEdit->setObjectName(QString::fromUtf8("BAGateGeneratorLineEdit"));
        BAGateGeneratorLineEdit->setGeometry(QRect(180, 50, 121, 27));
        BAGateGeneratorLineEdit->setFont(font);
        line_2 = new QFrame(gateGeneratorGroupBox);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(80, 80, 141, 16));
        line_2->setFont(font);
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        markersGroupBox = new QGroupBox(sequencerTab);
        markersGroupBox->setObjectName(QString::fromUtf8("markersGroupBox"));
        markersGroupBox->setGeometry(QRect(10, 240, 341, 201));
        markersGroupBox->setFont(font1);
        headerBeginLabel = new QLabel(markersGroupBox);
        headerBeginLabel->setObjectName(QString::fromUtf8("headerBeginLabel"));
        headerBeginLabel->setGeometry(QRect(0, 30, 141, 17));
        headerBeginLabel->setFont(font);
        headerEndLabel = new QLabel(markersGroupBox);
        headerEndLabel->setObjectName(QString::fromUtf8("headerEndLabel"));
        headerEndLabel->setGeometry(QRect(0, 60, 131, 17));
        headerEndLabel->setFont(font);
        eventBeginLabel = new QLabel(markersGroupBox);
        eventBeginLabel->setObjectName(QString::fromUtf8("eventBeginLabel"));
        eventBeginLabel->setGeometry(QRect(0, 90, 171, 17));
        eventBeginLabel->setFont(font);
        eventEndLabel = new QLabel(markersGroupBox);
        eventEndLabel->setObjectName(QString::fromUtf8("eventEndLabel"));
        eventEndLabel->setGeometry(QRect(0, 120, 161, 17));
        eventEndLabel->setFont(font);
        footerBeginLabel = new QLabel(markersGroupBox);
        footerBeginLabel->setObjectName(QString::fromUtf8("footerBeginLabel"));
        footerBeginLabel->setGeometry(QRect(0, 150, 141, 17));
        footerBeginLabel->setFont(font);
        footerEndLabel = new QLabel(markersGroupBox);
        footerEndLabel->setObjectName(QString::fromUtf8("footerEndLabel"));
        footerEndLabel->setGeometry(QRect(0, 180, 131, 17));
        footerEndLabel->setFont(font);
        headerBeginLineEdit = new QLineEdit(markersGroupBox);
        headerBeginLineEdit->setObjectName(QString::fromUtf8("headerBeginLineEdit"));
        headerBeginLineEdit->setEnabled(true);
        headerBeginLineEdit->setGeometry(QRect(220, 20, 113, 27));
        headerBeginLineEdit->setFont(font);
        headerEndLineEdit = new QLineEdit(markersGroupBox);
        headerEndLineEdit->setObjectName(QString::fromUtf8("headerEndLineEdit"));
        headerEndLineEdit->setGeometry(QRect(220, 50, 113, 27));
        headerEndLineEdit->setFont(font);
        eventBeginLineEdit = new QLineEdit(markersGroupBox);
        eventBeginLineEdit->setObjectName(QString::fromUtf8("eventBeginLineEdit"));
        eventBeginLineEdit->setGeometry(QRect(220, 80, 113, 27));
        eventBeginLineEdit->setFont(font);
        eventEndLineEdit = new QLineEdit(markersGroupBox);
        eventEndLineEdit->setObjectName(QString::fromUtf8("eventEndLineEdit"));
        eventEndLineEdit->setGeometry(QRect(220, 110, 113, 27));
        eventEndLineEdit->setFont(font);
        trailerBeginLineEdit = new QLineEdit(markersGroupBox);
        trailerBeginLineEdit->setObjectName(QString::fromUtf8("trailerBeginLineEdit"));
        trailerBeginLineEdit->setGeometry(QRect(220, 140, 113, 27));
        trailerBeginLineEdit->setFont(font);
        trailerEndLineEdit = new QLineEdit(markersGroupBox);
        trailerEndLineEdit->setObjectName(QString::fromUtf8("trailerEndLineEdit"));
        trailerEndLineEdit->setGeometry(QRect(220, 170, 113, 27));
        trailerEndLineEdit->setFont(font);
        CRAMSGroupBox = new QGroupBox(sequencerTab);
        CRAMSGroupBox->setObjectName(QString::fromUtf8("CRAMSGroupBox"));
        CRAMSGroupBox->setGeometry(QRect(370, 10, 241, 651));
        CRAMSGroupBox->setFont(font1);
        gridLayoutWidget_2 = new QWidget(CRAMSGroupBox);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(0, 40, 231, 601));
        gridLayoutWidget_2->setFont(font);
        cramsGridLayout = new QGridLayout(gridLayoutWidget_2);
        cramsGridLayout->setSpacing(6);
        cramsGridLayout->setContentsMargins(11, 11, 11, 11);
        cramsGridLayout->setObjectName(QString::fromUtf8("cramsGridLayout"));
        cramsGridLayout->setContentsMargins(0, 0, 0, 0);
        numOfCramsLabel = new QLabel(CRAMSGroupBox);
        numOfCramsLabel->setObjectName(QString::fromUtf8("numOfCramsLabel"));
        numOfCramsLabel->setGeometry(QRect(0, 20, 126, 27));
        numOfCramsLabel->setFont(font);
        numberOfCRAMSSpinBox = new QSpinBox(CRAMSGroupBox);
        numberOfCRAMSSpinBox->setObjectName(QString::fromUtf8("numberOfCRAMSSpinBox"));
        numberOfCRAMSSpinBox->setGeometry(QRect(140, 20, 61, 27));
        numberOfCRAMSSpinBox->setFont(font);
        numberOfCRAMSSpinBox->setMinimum(1);
        numberOfCRAMSSpinBox->setMaximum(10);
        miscGroupBox = new QGroupBox(sequencerTab);
        miscGroupBox->setObjectName(QString::fromUtf8("miscGroupBox"));
        miscGroupBox->setGeometry(QRect(690, 240, 321, 271));
        miscGroupBox->setFont(font);
        numOfGassiplexChansLabel = new QLabel(miscGroupBox);
        numOfGassiplexChansLabel->setObjectName(QString::fromUtf8("numOfGassiplexChansLabel"));
        numOfGassiplexChansLabel->setGeometry(QRect(0, 30, 201, 17));
        numOfGassiplexChansLabel->setFont(font);
        maxNumEventsCheckBox = new QCheckBox(miscGroupBox);
        maxNumEventsCheckBox->setObjectName(QString::fromUtf8("maxNumEventsCheckBox"));
        maxNumEventsCheckBox->setGeometry(QRect(0, 60, 221, 22));
        maxNumEventsCheckBox->setFont(font);
        IRQTimeoutLabel = new QLabel(miscGroupBox);
        IRQTimeoutLabel->setObjectName(QString::fromUtf8("IRQTimeoutLabel"));
        IRQTimeoutLabel->setGeometry(QRect(0, 90, 231, 17));
        IRQTimeoutLabel->setFont(font);
        numOfChansSpinBox = new QSpinBox(miscGroupBox);
        numOfChansSpinBox->setObjectName(QString::fromUtf8("numOfChansSpinBox"));
        numOfChansSpinBox->setGeometry(QRect(230, 20, 71, 27));
        numOfChansSpinBox->setFont(font);
        numOfChansSpinBox->setMinimum(10);
        numOfChansSpinBox->setMaximum(1000);
        maxNumOfEventsSpinBox = new QSpinBox(miscGroupBox);
        maxNumOfEventsSpinBox->setObjectName(QString::fromUtf8("maxNumOfEventsSpinBox"));
        maxNumOfEventsSpinBox->setGeometry(QRect(230, 50, 71, 27));
        maxNumOfEventsSpinBox->setFont(font);
        maxNumOfEventsSpinBox->setMinimum(1);
        maxNumOfEventsSpinBox->setMaximum(100000000);
        IRQTimeoutSpinBox = new QSpinBox(miscGroupBox);
        IRQTimeoutSpinBox->setObjectName(QString::fromUtf8("IRQTimeoutSpinBox"));
        IRQTimeoutSpinBox->setGeometry(QRect(230, 80, 71, 27));
        IRQTimeoutSpinBox->setFont(font);
        IRQTimeoutSpinBox->setMaximum(100000000);
        line = new QFrame(miscGroupBox);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(90, 120, 118, 3));
        line->setFont(font);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        configurationFilePathLabel = new QLabel(miscGroupBox);
        configurationFilePathLabel->setObjectName(QString::fromUtf8("configurationFilePathLabel"));
        configurationFilePathLabel->setGeometry(QRect(0, 130, 161, 17));
        configurationFilePathLabel->setFont(font);
        configurationFilePathLineEdit = new QLineEdit(miscGroupBox);
        configurationFilePathLineEdit->setObjectName(QString::fromUtf8("configurationFilePathLineEdit"));
        configurationFilePathLineEdit->setGeometry(QRect(0, 150, 301, 27));
        configurationFilePathLineEdit->setFont(font);
        mappingFilePathLineEdit = new QLineEdit(miscGroupBox);
        mappingFilePathLineEdit->setObjectName(QString::fromUtf8("mappingFilePathLineEdit"));
        mappingFilePathLineEdit->setGeometry(QRect(0, 200, 301, 27));
        mappingFilePathLineEdit->setFont(font);
        mappingFilePathLabel = new QLabel(miscGroupBox);
        mappingFilePathLabel->setObjectName(QString::fromUtf8("mappingFilePathLabel"));
        mappingFilePathLabel->setGeometry(QRect(0, 180, 131, 17));
        mappingFilePathLabel->setFont(font);
        displayRefresRateLabel = new QLabel(miscGroupBox);
        displayRefresRateLabel->setObjectName(QString::fromUtf8("displayRefresRateLabel"));
        displayRefresRateLabel->setGeometry(QRect(0, 250, 161, 17));
        displayRefresRateLabel->setFont(font);
        displayRefreshRateSpinBox = new QSpinBox(miscGroupBox);
        displayRefreshRateSpinBox->setObjectName(QString::fromUtf8("displayRefreshRateSpinBox"));
        displayRefreshRateSpinBox->setGeometry(QRect(240, 240, 59, 27));
        displayRefreshRateSpinBox->setFont(font);
        displayRefreshRateSpinBox->setMaximum(1000000000);
        applyConfigButton = new QPushButton(sequencerTab);
        applyConfigButton->setObjectName(QString::fromUtf8("applyConfigButton"));
        applyConfigButton->setGeometry(QRect(910, 610, 97, 27));
        applyConfigButton->setFont(font);
        runGroupBox = new QGroupBox(sequencerTab);
        runGroupBox->setObjectName(QString::fromUtf8("runGroupBox"));
        runGroupBox->setGeometry(QRect(10, 500, 201, 111));
        runGroupBox->setFont(font);
        runNumberLabel = new QLabel(runGroupBox);
        runNumberLabel->setObjectName(QString::fromUtf8("runNumberLabel"));
        runNumberLabel->setGeometry(QRect(0, 30, 91, 17));
        runNumberLabel->setFont(font);
        typeOfRunLabel = new QLabel(runGroupBox);
        typeOfRunLabel->setObjectName(QString::fromUtf8("typeOfRunLabel"));
        typeOfRunLabel->setGeometry(QRect(0, 70, 81, 17));
        typeOfRunLabel->setFont(font);
        runNumberSpinBox = new QSpinBox(runGroupBox);
        runNumberSpinBox->setObjectName(QString::fromUtf8("runNumberSpinBox"));
        runNumberSpinBox->setGeometry(QRect(90, 30, 81, 27));
        runNumberSpinBox->setFont(font);
        runNumberSpinBox->setMinimum(1);
        runNumberSpinBox->setMaximum(1000000000);
        typeOfRunComboBox = new QComboBox(runGroupBox);
        typeOfRunComboBox->setObjectName(QString::fromUtf8("typeOfRunComboBox"));
        typeOfRunComboBox->setGeometry(QRect(90, 70, 85, 27));
        typeOfRunComboBox->setFont(font);
        unlockButton = new QPushButton(sequencerTab);
        unlockButton->setObjectName(QString::fromUtf8("unlockButton"));
        unlockButton->setGeometry(QRect(690, 610, 97, 27));
        unlockButton->setFont(font);
        resetDefaultsButton = new QPushButton(sequencerTab);
        resetDefaultsButton->setObjectName(QString::fromUtf8("resetDefaultsButton"));
        resetDefaultsButton->setGeometry(QRect(800, 610, 97, 27));
        resetDefaultsButton->setFont(font);
        tabWidget->addTab(sequencerTab, QString());
        logTab = new QWidget();
        logTab->setObjectName(QString::fromUtf8("logTab"));
        logTextEdit = new QPlainTextEdit(logTab);
        logTextEdit->setObjectName(QString::fromUtf8("logTextEdit"));
        logTextEdit->setGeometry(QRect(10, 10, 1011, 601));
        logTextEdit->setReadOnly(true);
        clearLogButton = new QPushButton(logTab);
        clearLogButton->setObjectName(QString::fromUtf8("clearLogButton"));
        clearLogButton->setGeometry(QRect(10, 620, 97, 27));
        tabWidget->addTab(logTab, QString());
        aboutTab = new QWidget();
        aboutTab->setObjectName(QString::fromUtf8("aboutTab"));
        aboutNtuaLabel = new QLabel(aboutTab);
        aboutNtuaLabel->setObjectName(QString::fromUtf8("aboutNtuaLabel"));
        aboutNtuaLabel->setGeometry(QRect(440, 30, 131, 121));
        aboutNtuaLabel->setFont(font);
        aboutNtuaLabel->setPixmap(QPixmap(QString::fromUtf8("../Doc_Dead/SRSDCS.v1.5/SRSDCS.v1.5/pyrforos.gif")));
        aboutNtuaLabel->setScaledContents(true);
        aboutTitleLabel = new QLabel(aboutTab);
        aboutTitleLabel->setObjectName(QString::fromUtf8("aboutTitleLabel"));
        aboutTitleLabel->setGeometry(QRect(380, 180, 291, 31));
        QFont font2;
        font2.setPointSize(19);
        font2.setBold(true);
        font2.setWeight(75);
        aboutTitleLabel->setFont(font2);
        aboutVersionLabel = new QLabel(aboutTab);
        aboutVersionLabel->setObjectName(QString::fromUtf8("aboutVersionLabel"));
        aboutVersionLabel->setGeometry(QRect(490, 220, 67, 17));
        QFont font3;
        font3.setItalic(true);
        aboutVersionLabel->setFont(font3);
        aboutCreatedByLabel = new QLabel(aboutTab);
        aboutCreatedByLabel->setObjectName(QString::fromUtf8("aboutCreatedByLabel"));
        aboutCreatedByLabel->setGeometry(QRect(380, 270, 101, 21));
        QFont font4;
        font4.setPointSize(14);
        font4.setUnderline(true);
        aboutCreatedByLabel->setFont(font4);
        aboutMyNameLabel = new QLabel(aboutTab);
        aboutMyNameLabel->setObjectName(QString::fromUtf8("aboutMyNameLabel"));
        aboutMyNameLabel->setGeometry(QRect(490, 270, 201, 17));
        QFont font5;
        font5.setPointSize(14);
        font5.setItalic(true);
        aboutMyNameLabel->setFont(font5);
        aboutDateLabel = new QLabel(aboutTab);
        aboutDateLabel->setObjectName(QString::fromUtf8("aboutDateLabel"));
        aboutDateLabel->setGeometry(QRect(500, 300, 31, 17));
        aboutDateLabel->setFont(font3);
        tabWidget->addTab(aboutTab, QString());
        stopCycleCheckBox = new QCheckBox(centralWindow);
        stopCycleCheckBox->setObjectName(QString::fromUtf8("stopCycleCheckBox"));
        stopCycleCheckBox->setEnabled(true);
        stopCycleCheckBox->setGeometry(QRect(1070, 330, 97, 22));
        stopCycleCheckBox->setFont(font);
        ntuaLabel = new QLabel(centralWindow);
        ntuaLabel->setObjectName(QString::fromUtf8("ntuaLabel"));
        ntuaLabel->setGeometry(QRect(1060, 10, 131, 121));
        ntuaLabel->setFont(font);
        ntuaLabel->setPixmap(QPixmap(QString::fromUtf8("../Doc_Dead/SRSDCS.v1.5/SRSDCS.v1.5/pyrforos.gif")));
        ntuaLabel->setScaledContents(true);
        initializeCheckBox = new QCheckBox(centralWindow);
        initializeCheckBox->setObjectName(QString::fromUtf8("initializeCheckBox"));
        initializeCheckBox->setGeometry(QRect(1170, 420, 97, 22));
        Interface->setCentralWidget(centralWindow);

        retranslateUi(Interface);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Interface);
    } // setupUi

    void retranslateUi(QMainWindow *Interface)
    {
        Interface->setWindowTitle(QApplication::translate("Interface", "NTUA DAQ Software", 0, QApplication::UnicodeUTF8));
        initializeButton->setText(QApplication::translate("Interface", "&Initialize", 0, QApplication::UnicodeUTF8));
        startButton->setText(QApplication::translate("Interface", "Star&t Cycle", 0, QApplication::UnicodeUTF8));
        stopButton->setText(QApplication::translate("Interface", "Sto&p Cycle", 0, QApplication::UnicodeUTF8));
        helpButton->setText(QApplication::translate("Interface", "&Help", 0, QApplication::UnicodeUTF8));
        closeButton->setText(QApplication::translate("Interface", "&Close", 0, QApplication::UnicodeUTF8));
        cancelInitializationButton->setText(QApplication::translate("Interface", "Ca&ncel Init", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(displayTab), QApplication::translate("Interface", "Display", 0, QApplication::UnicodeUTF8));
        sequencerGroupBox->setTitle(QApplication::translate("Interface", "Sequencer", 0, QApplication::UnicodeUTF8));
        BASequencerLabel->setText(QApplication::translate("Interface", "Sequencer Base Address", 0, QApplication::UnicodeUTF8));
        t1Label->setText(QApplication::translate("Interface", "Trigger to Hold Delay", 0, QApplication::UnicodeUTF8));
        t2Label->setText(QApplication::translate("Interface", "Hold to Sequence Delay", 0, QApplication::UnicodeUTF8));
        t3Label->setText(QApplication::translate("Interface", "Active Clock Duration", 0, QApplication::UnicodeUTF8));
        t4Label->setText(QApplication::translate("Interface", "Period of Clock and Convert Sequence", 0, QApplication::UnicodeUTF8));
        t5Label->setText(QApplication::translate("Interface", "Clock and Convert Delay", 0, QApplication::UnicodeUTF8));
        gateGeneratorGroupBox->setTitle(QApplication::translate("Interface", "Gate Generator", 0, QApplication::UnicodeUTF8));
        gateGeneratorCheckBox->setText(QApplication::translate("Interface", "Is there a Gate Generator?", 0, QApplication::UnicodeUTF8));
        CH0UpperLabel->setText(QApplication::translate("Interface", "Channel 0: Upper Display", 0, QApplication::UnicodeUTF8));
        CH0LowerLabel->setText(QApplication::translate("Interface", "Channel 0: Lower Display", 0, QApplication::UnicodeUTF8));
        CH1UpperLabel->setText(QApplication::translate("Interface", "Channel 1: Upper Display", 0, QApplication::UnicodeUTF8));
        CH1LowerLabel->setText(QApplication::translate("Interface", "Channel 1: Lower Display", 0, QApplication::UnicodeUTF8));
        gateGeneratorBALabel->setText(QApplication::translate("Interface", "Base Address", 0, QApplication::UnicodeUTF8));
        markersGroupBox->setTitle(QApplication::translate("Interface", "Readout Markers", 0, QApplication::UnicodeUTF8));
        headerBeginLabel->setText(QApplication::translate("Interface", "Header Begin Marker", 0, QApplication::UnicodeUTF8));
        headerEndLabel->setText(QApplication::translate("Interface", "Header End Marker", 0, QApplication::UnicodeUTF8));
        eventBeginLabel->setText(QApplication::translate("Interface", "Event Data Begin Marker", 0, QApplication::UnicodeUTF8));
        eventEndLabel->setText(QApplication::translate("Interface", "Event Data End Marker", 0, QApplication::UnicodeUTF8));
        footerBeginLabel->setText(QApplication::translate("Interface", "Footer Begin Marker", 0, QApplication::UnicodeUTF8));
        footerEndLabel->setText(QApplication::translate("Interface", "Footer End Marker", 0, QApplication::UnicodeUTF8));
        CRAMSGroupBox->setTitle(QApplication::translate("Interface", "CRAMS", 0, QApplication::UnicodeUTF8));
        numOfCramsLabel->setText(QApplication::translate("Interface", "Number of CRAMS", 0, QApplication::UnicodeUTF8));
        miscGroupBox->setTitle(QApplication::translate("Interface", "Misc", 0, QApplication::UnicodeUTF8));
        numOfGassiplexChansLabel->setText(QApplication::translate("Interface", "Number of Readout Channels", 0, QApplication::UnicodeUTF8));
        maxNumEventsCheckBox->setText(QApplication::translate("Interface", "Maximum Number of Events", 0, QApplication::UnicodeUTF8));
        IRQTimeoutLabel->setText(QApplication::translate("Interface", "Interrupt Request Timeout (msec)", 0, QApplication::UnicodeUTF8));
        configurationFilePathLabel->setText(QApplication::translate("Interface", "Configuration File Path:", 0, QApplication::UnicodeUTF8));
        mappingFilePathLabel->setText(QApplication::translate("Interface", "Mapping File Path:", 0, QApplication::UnicodeUTF8));
        displayRefresRateLabel->setText(QApplication::translate("Interface", "Display Refresh Rate", 0, QApplication::UnicodeUTF8));
        applyConfigButton->setText(QApplication::translate("Interface", "Apply", 0, QApplication::UnicodeUTF8));
        runGroupBox->setTitle(QApplication::translate("Interface", "Run Information", 0, QApplication::UnicodeUTF8));
        runNumberLabel->setText(QApplication::translate("Interface", "Run Number", 0, QApplication::UnicodeUTF8));
        typeOfRunLabel->setText(QApplication::translate("Interface", "Type of Run", 0, QApplication::UnicodeUTF8));
        typeOfRunComboBox->clear();
        typeOfRunComboBox->insertItems(0, QStringList()
         << QApplication::translate("Interface", "Physics", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Interface", "Pedestal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Interface", "Test", 0, QApplication::UnicodeUTF8)
        );
        unlockButton->setText(QApplication::translate("Interface", "Unlock", 0, QApplication::UnicodeUTF8));
        resetDefaultsButton->setText(QApplication::translate("Interface", "Reset Default", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(sequencerTab), QApplication::translate("Interface", "Configuration", 0, QApplication::UnicodeUTF8));
        clearLogButton->setText(QApplication::translate("Interface", "C&lear", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(logTab), QApplication::translate("Interface", "LogViewer", 0, QApplication::UnicodeUTF8));
        aboutNtuaLabel->setText(QString());
        aboutTitleLabel->setText(QApplication::translate("Interface", "NTUA DAQ SOFTWARE", 0, QApplication::UnicodeUTF8));
        aboutVersionLabel->setText(QApplication::translate("Interface", "v. 1.0beta", 0, QApplication::UnicodeUTF8));
        aboutCreatedByLabel->setText(QApplication::translate("Interface", "Created by:", 0, QApplication::UnicodeUTF8));
        aboutMyNameLabel->setText(QApplication::translate("Interface", "Nikolaos D. Karastathis", 0, QApplication::UnicodeUTF8));
        aboutDateLabel->setText(QApplication::translate("Interface", "2011", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(aboutTab), QApplication::translate("Interface", "About", 0, QApplication::UnicodeUTF8));
        stopCycleCheckBox->setText(QApplication::translate("Interface", "Stopping cycle", 0, QApplication::UnicodeUTF8));
        ntuaLabel->setText(QString());
        initializeCheckBox->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Interface: public Ui_Interface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACE_H
