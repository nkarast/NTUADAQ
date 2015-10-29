#include <QtGui/QApplication>
#include <qstatusbar.h>
#include <qmessagebox.h>
#include <qmenubar.h>
#include <qapplication.h>
#include <qimage.h>
#include <qtimer.h>

#include <stdlib.h>
#include <TApplication.h>
#include <TSystem.h>

#include "Interface.h"

int main(int argc, char *argv[])
{

    TApplication rootapp("Simple Qt ROOT Application", &argc, argv);
    QApplication a(argc, argv);
    Interface w;
    w.show();    

    QObject::connect( qApp, SIGNAL(lastWindowClosed()), qApp, SLOT(quit()) );

    // create instance of TApplication
//    TApplication *gMyRootApp = new TApplication("My Root Application", &argc, argv);
    //tell application to return from run
//    gMyRootApp->SetReturnFromRun(true);

    return a.exec();
}
