#include <PythonQt.h>
#include <PythonQtConversion.h>
#include "test0.h"



void PythonQt_init_Test(PyObject* module) {
PythonQt::priv()->registerClass(&TestBase::staticMetaObject, "Test", PythonQtCreateObject<PythonQtWrapper_TestBase>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_TestBase>, module, 0);
PythonQt::priv()->registerClass(&TestIntermediate::staticMetaObject, "Test", PythonQtCreateObject<PythonQtWrapper_TestIntermediate>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_TestIntermediate>, module, 0);
PythonQt::priv()->registerClass(&TestPrimary::staticMetaObject, "Test", PythonQtCreateObject<PythonQtWrapper_TestPrimary>, PythonQtSetInstanceWrapperOnShell<PythonQtShell_TestPrimary>, module, 0);


}
