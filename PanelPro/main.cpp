#include "panelpro.h"
#include <QApplication>
#include "myapplication.h"
#ifdef SCRIPTING_ENABLED
#include "PythonQt.h"
#include "PythonQt_QtAll.h"
#endif
//void myMessageOutput(QtMsgType type, const char *msg)
//{
// switch (type)
// {
// case QtDebugMsg:
//     fprintf(stderr, "Debug: %s\n", msg);
//     break;
// case QtWarningMsg:
//     fprintf(stderr, "Warning: %s\n", msg);
//     break;
// case QtCriticalMsg:
//     fprintf(stderr, "Critical: %s\n", msg);
//     break;
// case QtFatalMsg:
//     fprintf(stderr, "Fatal: %s\n", msg);
//     abort();
// }
//}

int main(int argc, char *argv[])
{
 QCoreApplication::setApplicationName("PanelPro");
 QCoreApplication::setOrganizationName("ACK Software");

 //qInstallMsgHandler(myMessageOutput);

 MyApplication a(argc, argv);
#ifdef SCRIPTING_ENABLED
 PythonQt::init(PythonQt::IgnoreSiteModule | PythonQt::RedirectStdOut);
 PythonQt_QtAll::init();
#endif
// PanelPro w(0);
// w.show();
 PanelPro::main(argv);

 return a.exec();
}
