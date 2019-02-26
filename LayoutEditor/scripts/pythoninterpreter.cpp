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

/*public*/ void PythonInterpreter::exec(QString text)
{
 PythonQt::self()->getMainModule().evalScript(text);
}

/*public*/ PyObject PythonInterpreter::eval(QString s)
{
}
