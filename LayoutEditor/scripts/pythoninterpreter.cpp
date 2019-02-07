#include"pythoninterpreter.h"
#include "PythonQt.h"

PythonInterpreter::PythonInterpreter()
{

}

/*public*/ void PythonInterpreter::execfile(QTextStream* s)
{
 QString text = s->readAll();
 PythonQt::self()->getMainModule().evalScript(text);

}

/*public*/ void exec(QString text)
{
 PythonQt::self()->getMainModule().evalScript(text);
}

/*public*/ PyObject eval(QString s)
{
}
