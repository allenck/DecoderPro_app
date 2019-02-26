
#include "pythonwrappers.h"
#include "jframe.h"
#include "PythonQt.h"
#include <QDebug>
#include "PythonQt_QtAll.h"
#include "lntrafficcontroller.h"
//#include "generated_cpp/jmri/jmri0.h"
//#include "generated_cpp/jmri/jmri1.h"
//#include "generated_cpp/jmri/jmri2.h"

#include "generated_cpp/Jmri/Jmri0.h"
#include "generated_cpp/Jmri/Jmri1.h"
#include "generated_cpp/Jmri/Jmri2.h"
#include "generated_cpp/Jmri/Jmri3.h"

#include "generated_cpp/test/test0.h"

void PythonQt_init_Jmri(PyObject*);
void PythonQt_init_Test(PyObject*);

PythonWrappers::PythonWrappers(QObject *parent) :
  QObject(parent)
{
}

void PythonWrappers::defineClasses()
{

 PythonQt_QtAll::init();
 PythonQt_init_Jmri(nullptr);
 PythonQt_init_Test(nullptr);


}
