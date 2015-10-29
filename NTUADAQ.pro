######################################################################
# Automatically generated by qmake (2.01a) Fri Sep 9 11:34:29 2011
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . src
INCLUDEPATH += . src

include("$(ROOTSYS)/include/rootcint.pri")

# Input
HEADERS += src/ConfigFile.h \
           src/Interface.h \
           src/V462_GateGenerator.h \
           src/V550_CRAMS.h \
           src/V551_Sequencer.h
FORMS += src/interface.ui
SOURCES += src/ConfigFile.cpp \
           src/Interface.cpp \
           src/main.cpp \
           src/V462_GateGenerator.cpp \
           src/V550_CRAMS.cpp \
           src/V551_Sequencer.cpp


win32:CONFIG(release, debug|release): LIBS += -L/usr/lib/release/ -lCAENVME -lQtCore
else:win32:CONFIG(debug, debug|release): LIBS += -L/usr/lib/debug/ -lCAENVME -lQtCore
else:symbian: LIBS += -lCAENVME -lQtCore
else:unix: LIBS += -L/usr/lib/ -lCAENVME -lQtCore

INCLUDEPATH += /usr/include
DEPENDPATH += /usr/include

win32:CONFIG(release, debug|release): LIBS += -L/home/nick/root/lib/release/ -lGpad -lCint -lCore -lGraf -lGraf3d -lHist -lGui -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lRIO -lNet -lThread -lGQt
else:win32:CONFIG(debug, debug|release): LIBS += -L/home/nick/root/lib/debug/ -lGpad -lCint -lCore -lGraf -lGraf3d -lHist -lGui -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lRIO -lNet -lThread -lGQt
else:symbian: LIBS += -lGpad -lCint -lCore -lGraf -lGraf3d -lHist -lGui -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lRIO -lNet -lThread -lGQt
else:unix: LIBS += -L/home/nick/root/lib/ -lGpad -lCint -lCore -lGraf -lGraf3d -lHist -lGui -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lRIO -lNet -lThread -lGQt

INCLUDEPATH += /home/nick/root/include
DEPENDPATH += /home/nick/root/include
