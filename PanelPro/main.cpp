#include "panelpro.h"
#include <QApplication>
#include "myapplication.h"
#ifdef SCRIPTING_ENABLED
#include "PythonQt.h"
#include "PythonQt_QtAll.h"
#include "pythonwrappers.h"

#include <QVBoxLayout>
#include <QGroupBox>
#include <QTextBrowser>
#include <QLineEdit>
#include <QPushButton>
#endif // end SCRIPTING_ENABLED

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
 QApplication::setStyle("GTK+");

 MyApplication a(argc, argv);
#ifdef SCRIPTING_ENABLED
 PythonQt::init(PythonQt::RedirectStdOut);
 PythonWrappers::defineClasses();

# if 0 // test Python install
 // get the __main__ python module
 PythonQtObjectPtr mainModule = PythonQt::self()->getMainModule();

 // evaluate a simple python script and receive the result a qvariant:
 QVariant result = mainModule.evalScript("19*2+4", Py_eval_input);

 // create a small Qt GUI
 QVBoxLayout*  vbox = new QVBoxLayout;
 QGroupBox*    box  = new QGroupBox;
 QTextBrowser* browser = new QTextBrowser(box);
 QLineEdit*    edit = new QLineEdit(box);
 QPushButton*  button = new QPushButton(box);
 button->setObjectName("button1");
 edit->setObjectName("edit");
 browser->setObjectName("browser");
 vbox->addWidget(browser);
 vbox->addWidget(edit);
 vbox->addWidget(button);
 box->setLayout(vbox);

 // make the groupbox to the python under the name "box"
 mainModule.addObject("box", box);

 // evaluate the python script which is defined in the resources
 mainModule.evalFile(":resources/GettingStarted.py");

 // define a python method that appends the passed text to the browser
 mainModule.evalScript("def appendText(text):\n  box.browser.append(text)");
 // shows how to call the method with a text that will be append to the browser
 mainModule.call("appendText", QVariantList() << "The ultimate answer is ");
 PythonQt::init(PythonQt::IgnoreSiteModule | PythonQt::RedirectStdOut);
 PythonQt_QtAll::init();
# endif // end SCRIPTING_ENABLED

#endif
// PanelPro w(0);
// w.show();
 PanelPro::main(argv);

 return a.exec();
}
