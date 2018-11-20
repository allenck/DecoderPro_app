#include "jmri1.h"
#include <PythonQtConversion.h>
#include <PythonQtMethodInfo.h>
#include <PythonQtSignalReceiver.h>
#include <QVariant>
#include <abstractmanager.h>
#include <abstractsensormanager.h>
#include <dcclocoaddress.h>
#include <dccthrottle.h>
#include <editor.h>
#include <light.h>
#include <locoaddress.h>
#include <manager.h>
#include <namedbean.h>
#include <positionable.h>
#include <powermanager.h>
#include <qbytearray.h>
#include <qcolor.h>
#include <qcoreevent.h>
#include <qfont.h>
#include <qlist.h>
#include <qmetaobject.h>
#include <qobject.h>
#include <qpoint.h>
#include <qrect.h>
#include <qstringlist.h>
#include <qvector.h>
#include <sensor.h>
#include <turnout.h>

PythonQtShell_MemoryManager::~PythonQtShell_MemoryManager() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_MemoryManager::Register(NamedBean*  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("Register");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "NamedBean*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&s0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  MemoryManager::Register(s0);
}
void PythonQtShell_MemoryManager::addPropertyChangeListener(PropertyChangeListener*  l0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("addPropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&l0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  MemoryManager::addPropertyChangeListener(l0);
}
void PythonQtShell_MemoryManager::childEvent(QChildEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("childEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QChildEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  MemoryManager::childEvent(arg__1);
}
void PythonQtShell_MemoryManager::customEvent(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("customEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  MemoryManager::customEvent(arg__1);
}
void PythonQtShell_MemoryManager::deregister(NamedBean*  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("deregister");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "NamedBean*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&s0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  MemoryManager::deregister(s0);
}
void PythonQtShell_MemoryManager::dispose()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("dispose");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={""};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  MemoryManager::dispose();
}
bool  PythonQtShell_MemoryManager::event(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("event");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("event", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return MemoryManager::event(arg__1);
}
bool  PythonQtShell_MemoryManager::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("eventFilter");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QObject*" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      bool returnValue;
    void* args[3] = {NULL, (void*)&arg__1, (void*)&arg__2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("eventFilter", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return MemoryManager::eventFilter(arg__1, arg__2);
}
NamedBean*  PythonQtShell_MemoryManager::getBeanBySystemName(QString  systemName0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getBeanBySystemName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"NamedBean*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      NamedBean* returnValue;
    void* args[2] = {NULL, (void*)&systemName0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getBeanBySystemName", methodInfo, result);
        } else {
          returnValue = *((NamedBean**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return MemoryManager::getBeanBySystemName(systemName0);
}
NamedBean*  PythonQtShell_MemoryManager::getBeanByUserName(QString  userName0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getBeanByUserName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"NamedBean*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      NamedBean* returnValue;
    void* args[2] = {NULL, (void*)&userName0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getBeanByUserName", methodInfo, result);
        } else {
          returnValue = *((NamedBean**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return MemoryManager::getBeanByUserName(userName0);
}
NamedBean*  PythonQtShell_MemoryManager::getNamedBean(QString  name0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNamedBean");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"NamedBean*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      NamedBean* returnValue;
    void* args[2] = {NULL, (void*)&name0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getNamedBean", methodInfo, result);
        } else {
          returnValue = *((NamedBean**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return MemoryManager::getNamedBean(name0);
}
QList<NamedBean* >*  PythonQtShell_MemoryManager::getNamedBeanList()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNamedBeanList");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QList<NamedBean* >*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QList<NamedBean* >* returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getNamedBeanList", methodInfo, result);
        } else {
          returnValue = *((QList<NamedBean* >**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return MemoryManager::getNamedBeanList();
}
QStringList  PythonQtShell_MemoryManager::getSystemNameArray()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemNameArray");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QStringList"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QStringList returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSystemNameArray", methodInfo, result);
        } else {
          returnValue = *((QStringList*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return MemoryManager::getSystemNameArray();
}
QStringList  PythonQtShell_MemoryManager::getSystemNameList()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemNameList");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QStringList"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QStringList returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSystemNameList", methodInfo, result);
        } else {
          returnValue = *((QStringList*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return MemoryManager::getSystemNameList();
}
QString  PythonQtShell_MemoryManager::getSystemPrefix()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemPrefix");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSystemPrefix", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return MemoryManager::getSystemPrefix();
}
int  PythonQtShell_MemoryManager::getXMLOrder()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getXMLOrder");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getXMLOrder", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return MemoryManager::getXMLOrder();
}
QString  PythonQtShell_MemoryManager::makeSystemName(QString  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("makeSystemName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      QString returnValue;
    void* args[2] = {NULL, (void*)&s0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("makeSystemName", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return MemoryManager::makeSystemName(s0);
}
void PythonQtShell_MemoryManager::on_propertyChange(PropertyChangeEvent*  e0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("on_propertyChange");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&e0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  MemoryManager::on_propertyChange(e0);
}
void PythonQtShell_MemoryManager::removePropertyChangeListener(PropertyChangeListener*  l0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("removePropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&l0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  MemoryManager::removePropertyChangeListener(l0);
}
void PythonQtShell_MemoryManager::timerEvent(QTimerEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("timerEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QTimerEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  MemoryManager::timerEvent(arg__1);
}
char  PythonQtShell_MemoryManager::typeLetter()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("typeLetter");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"char"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      char returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("typeLetter", methodInfo, result);
        } else {
          returnValue = *((char*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return MemoryManager::typeLetter();
}
MemoryManager* PythonQtWrapper_MemoryManager::new_MemoryManager(QObject*  parent)
{ 
return new PythonQtShell_MemoryManager(parent); }



PythonQtShell_NamedBean::~PythonQtShell_NamedBean() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_NamedBean::addPropertyChangeListener(PropertyChangeListener*  l0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("addPropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&l0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  NamedBean::addPropertyChangeListener(l0);
}
void PythonQtShell_NamedBean::addPropertyChangeListener(PropertyChangeListener*  l0, QString  name1, const QString  listenerRef2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("addPropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*" , "QString" , "const QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(4, argumentList);
    void* args[4] = {NULL, (void*)&l0, (void*)&name1, (void*)&listenerRef2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  NamedBean::addPropertyChangeListener(l0, name1, listenerRef2);
}
void PythonQtShell_NamedBean::childEvent(QChildEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("childEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QChildEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  NamedBean::childEvent(arg__1);
}
void PythonQtShell_NamedBean::customEvent(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("customEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  NamedBean::customEvent(arg__1);
}
void PythonQtShell_NamedBean::dispose()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("dispose");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={""};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  NamedBean::dispose();
}
bool  PythonQtShell_NamedBean::event(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("event");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("event", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return NamedBean::event(arg__1);
}
bool  PythonQtShell_NamedBean::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("eventFilter");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QObject*" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      bool returnValue;
    void* args[3] = {NULL, (void*)&arg__1, (void*)&arg__2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("eventFilter", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return NamedBean::eventFilter(arg__1, arg__2);
}
QString  PythonQtShell_NamedBean::getComment()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getComment");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getComment", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return NamedBean::getComment();
}
QString  PythonQtShell_NamedBean::getDisplayName()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getDisplayName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getDisplayName", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return NamedBean::getDisplayName();
}
QString  PythonQtShell_NamedBean::getListenerRef(PropertyChangeListener*  l0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getListenerRef");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      QString returnValue;
    void* args[2] = {NULL, (void*)&l0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getListenerRef", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return NamedBean::getListenerRef(l0);
}
QList<QString >*  PythonQtShell_NamedBean::getListenerRefs()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getListenerRefs");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QList<QString >*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QList<QString >* returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getListenerRefs", methodInfo, result);
        } else {
          returnValue = *((QList<QString >**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return NamedBean::getListenerRefs();
}
int  PythonQtShell_NamedBean::getNumPropertyChangeListeners()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNumPropertyChangeListeners");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getNumPropertyChangeListeners", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return NamedBean::getNumPropertyChangeListeners();
}
QVariant  PythonQtShell_NamedBean::getProperty(QString  key0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getProperty");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QVariant" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      QVariant returnValue;
    void* args[2] = {NULL, (void*)&key0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getProperty", methodInfo, result);
        } else {
          returnValue = *((QVariant*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return NamedBean::getProperty(key0);
}
QList<PropertyChangeListener* >*  PythonQtShell_NamedBean::getPropertyChangeListeners(QString  name0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getPropertyChangeListeners");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QList<PropertyChangeListener* >*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      QList<PropertyChangeListener* >* returnValue;
    void* args[2] = {NULL, (void*)&name0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getPropertyChangeListeners", methodInfo, result);
        } else {
          returnValue = *((QList<PropertyChangeListener* >**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return NamedBean::getPropertyChangeListeners(name0);
}
QSet<QString >  PythonQtShell_NamedBean::getPropertyKeys()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getPropertyKeys");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QList<QString >"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QSet<QString > returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getPropertyKeys", methodInfo, result);
        } else {
          returnValue = *((QSet<QString >*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return NamedBean::getPropertyKeys();
}
int  PythonQtShell_NamedBean::getState()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getState");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getState", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return NamedBean::getState();
}
QString  PythonQtShell_NamedBean::getSystemName()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSystemName", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return NamedBean::getSystemName();
}
QString  PythonQtShell_NamedBean::getUserName()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getUserName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getUserName", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return NamedBean::getUserName();
}
bool  PythonQtShell_NamedBean::hashCode()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("hashCode");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("hashCode", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return NamedBean::hashCode();
}
void PythonQtShell_NamedBean::removePropertyChangeListener(PropertyChangeListener*  l0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("removePropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&l0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  NamedBean::removePropertyChangeListener(l0);
}
void PythonQtShell_NamedBean::setComment(QString  comment0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setComment");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&comment0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  NamedBean::setComment(comment0);
}
void PythonQtShell_NamedBean::setProperty(QString  key0, QVariant  value1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setProperty");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString" , "QVariant"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
    void* args[3] = {NULL, (void*)&key0, (void*)&value1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  NamedBean::setProperty(key0, value1);
}
void PythonQtShell_NamedBean::setState(int  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setState");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  NamedBean::setState(arg__1);
}
void PythonQtShell_NamedBean::setUserName(QString  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setUserName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&s0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  NamedBean::setUserName(s0);
}
void PythonQtShell_NamedBean::timerEvent(QTimerEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("timerEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QTimerEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  NamedBean::timerEvent(arg__1);
}
void PythonQtShell_NamedBean::updateListenerRef(PropertyChangeListener*  l0, QString  newName1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("updateListenerRef");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
    void* args[3] = {NULL, (void*)&l0, (void*)&newName1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  NamedBean::updateListenerRef(l0, newName1);
}
NamedBean* PythonQtWrapper_NamedBean::new_NamedBean(QObject*  parent)
{ 
return new PythonQtShell_NamedBean(parent); }

NamedBean* PythonQtWrapper_NamedBean::new_NamedBean(QString  name, QObject*  parent)
{ 
return new PythonQtShell_NamedBean(name, parent); }

NamedBean* PythonQtWrapper_NamedBean::new_NamedBean(const NamedBean&  arg__1)
{ 
return new PythonQtShell_NamedBean(arg__1); }

void PythonQtWrapper_NamedBean::addPropertyChangeListener(NamedBean* theWrappedObject, PropertyChangeListener*  l)
{
  ( ((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->promoted_addPropertyChangeListener(l));
}

void PythonQtWrapper_NamedBean::addPropertyChangeListener(NamedBean* theWrappedObject, PropertyChangeListener*  l, QString  name, const QString  listenerRef)
{
  ( ((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->promoted_addPropertyChangeListener(l, name, listenerRef));
}

void PythonQtWrapper_NamedBean::dispose(NamedBean* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->promoted_dispose());
}

QString  PythonQtWrapper_NamedBean::getComment(NamedBean* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->promoted_getComment());
}

QString  PythonQtWrapper_NamedBean::getDisplayName(NamedBean* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->promoted_getDisplayName());
}

QString  PythonQtWrapper_NamedBean::getListenerRef(NamedBean* theWrappedObject, PropertyChangeListener*  l)
{
  return ( ((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->promoted_getListenerRef(l));
}

QList<QString >*  PythonQtWrapper_NamedBean::getListenerRefs(NamedBean* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->promoted_getListenerRefs());
}

int  PythonQtWrapper_NamedBean::getNumPropertyChangeListeners(NamedBean* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->promoted_getNumPropertyChangeListeners());
}

QVariant  PythonQtWrapper_NamedBean::getProperty(NamedBean* theWrappedObject, QString  key)
{
  return ( ((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->promoted_getProperty(key));
}

QList<PropertyChangeListener* >*  PythonQtWrapper_NamedBean::getPropertyChangeListeners(NamedBean* theWrappedObject, QString  name)
{
  return ( ((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->promoted_getPropertyChangeListeners(name));
}

QSet<QString >  PythonQtWrapper_NamedBean::getPropertyKeys(NamedBean* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->promoted_getPropertyKeys());
}

int  PythonQtWrapper_NamedBean::getState(NamedBean* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->promoted_getState());
}

QString  PythonQtWrapper_NamedBean::getSystemName(NamedBean* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->promoted_getSystemName());
}

QString  PythonQtWrapper_NamedBean::getUserName(NamedBean* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->promoted_getUserName());
}

bool  PythonQtWrapper_NamedBean::hashCode(NamedBean* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->promoted_hashCode());
}

void PythonQtWrapper_NamedBean::removePropertyChangeListener(NamedBean* theWrappedObject, PropertyChangeListener*  l)
{
  ( ((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->promoted_removePropertyChangeListener(l));
}

void PythonQtWrapper_NamedBean::setComment(NamedBean* theWrappedObject, QString  comment)
{
  ( ((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->promoted_setComment(comment));
}

void PythonQtWrapper_NamedBean::setProperty(NamedBean* theWrappedObject, QString  key, QVariant  value)
{
  ( ((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->promoted_setProperty(key, value));
}

void PythonQtWrapper_NamedBean::setState(NamedBean* theWrappedObject, int  arg__1)
{
  ( ((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->promoted_setState(arg__1));
}

void PythonQtWrapper_NamedBean::setUserName(NamedBean* theWrappedObject, QString  s)
{
  ( ((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->promoted_setUserName(s));
}

void PythonQtWrapper_NamedBean::updateListenerRef(NamedBean* theWrappedObject, PropertyChangeListener*  l, QString  newName)
{
  ( ((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->promoted_updateListenerRef(l, newName));
}



PythonQtShell_Positionable::~PythonQtShell_Positionable() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
bool  PythonQtShell_Positionable::contains(int  arg__1, int  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("contains");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "int" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      bool returnValue;
    void* args[3] = {NULL, (void*)&arg__1, (void*)&arg__2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("contains", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::contains(arg__1, arg__2);
}
Positionable*  PythonQtShell_Positionable::deepClone()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("deepClone");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"Positionable*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      Positionable* returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("deepClone", methodInfo, result);
        } else {
          returnValue = *((Positionable**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::deepClone();
}
void PythonQtShell_Positionable::doMouseClicked(QGraphicsSceneMouseEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("doMouseClicked");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QGraphicsSceneMouseEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::doMouseClicked(arg__1);
}
void PythonQtShell_Positionable::doMouseDragged(QGraphicsSceneMouseEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("doMouseDragged");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QGraphicsSceneMouseEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::doMouseDragged(arg__1);
}
void PythonQtShell_Positionable::doMouseEntered(QGraphicsSceneMouseEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("doMouseEntered");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QGraphicsSceneMouseEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::doMouseEntered(arg__1);
}
void PythonQtShell_Positionable::doMouseExited(QGraphicsSceneMouseEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("doMouseExited");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QGraphicsSceneMouseEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::doMouseExited(arg__1);
}
void PythonQtShell_Positionable::doMouseMoved(QGraphicsSceneMouseEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("doMouseMoved");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QGraphicsSceneMouseEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::doMouseMoved(arg__1);
}
void PythonQtShell_Positionable::doMousePressed(QGraphicsSceneMouseEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("doMousePressed");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QGraphicsSceneMouseEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::doMousePressed(arg__1);
}
void PythonQtShell_Positionable::doMouseReleased(QGraphicsSceneMouseEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("doMouseReleased");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QGraphicsSceneMouseEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::doMouseReleased(arg__1);
}
bool  PythonQtShell_Positionable::doViemMenu()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("doViemMenu");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("doViemMenu", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::doViemMenu();
}
Positionable*  PythonQtShell_Positionable::finishClone(Positionable*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("finishClone");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"Positionable*" , "Positionable*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      Positionable* returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("finishClone", methodInfo, result);
        } else {
          returnValue = *((Positionable**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::finishClone(arg__1);
}
QColor  PythonQtShell_Positionable::getBackground()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getBackground");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QColor"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QColor returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getBackground", methodInfo, result);
        } else {
          returnValue = *((QColor*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::getBackground();
}
QRectF  PythonQtShell_Positionable::getBounds(QRectF  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getBounds");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QRectF" , "QRectF"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      QRectF returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getBounds", methodInfo, result);
        } else {
          returnValue = *((QRectF*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::getBounds(arg__1);
}
int  PythonQtShell_Positionable::getDegrees()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getDegrees");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getDegrees", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::getDegrees();
}
int  PythonQtShell_Positionable::getDisplayLevel()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getDisplayLevel");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getDisplayLevel", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::getDisplayLevel();
}
Editor*  PythonQtShell_Positionable::getEditor()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getEditor");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"Editor*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      Editor* returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getEditor", methodInfo, result);
        } else {
          returnValue = *((Editor**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::getEditor();
}
QFont  PythonQtShell_Positionable::getFont()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getFont");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QFont"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QFont returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getFont", methodInfo, result);
        } else {
          returnValue = *((QFont*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::getFont();
}
QColor  PythonQtShell_Positionable::getForeground()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getForeground");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QColor"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QColor returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getForeground", methodInfo, result);
        } else {
          returnValue = *((QColor*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::getForeground();
}
int  PythonQtShell_Positionable::getHeight()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getHeight");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getHeight", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::getHeight();
}
QPointF  PythonQtShell_Positionable::getLocation()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getLocation");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QPointF"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QPointF returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getLocation", methodInfo, result);
        } else {
          returnValue = *((QPointF*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::getLocation();
}
QString  PythonQtShell_Positionable::getNameString()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNameString");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getNameString", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::getNameString();
}
NamedBean*  PythonQtShell_Positionable::getNamedBean()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNamedBean");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"NamedBean*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      NamedBean* returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getNamedBean", methodInfo, result);
        } else {
          returnValue = *((NamedBean**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::getNamedBean();
}
bool  PythonQtShell_Positionable::getSaveOpaque()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSaveOpaque");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSaveOpaque", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::getSaveOpaque();
}
double  PythonQtShell_Positionable::getScale()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getScale");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"double"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      double returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getScale", methodInfo, result);
        } else {
          returnValue = *((double*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::getScale();
}
bool  PythonQtShell_Positionable::getViewCoordinates()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getViewCoordinates");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getViewCoordinates", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::getViewCoordinates();
}
int  PythonQtShell_Positionable::getWidth()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getWidth");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getWidth", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::getWidth();
}
int  PythonQtShell_Positionable::getX()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getX");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getX", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::getX();
}
int  PythonQtShell_Positionable::getY()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getY");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getY", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::getY();
}
void PythonQtShell_Positionable::invalidate()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("invalidate");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={""};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::invalidate();
}
bool  PythonQtShell_Positionable::isControlling()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("isControlling");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("isControlling", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::isControlling();
}
bool  PythonQtShell_Positionable::isEditable()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("isEditable");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("isEditable", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::isEditable();
}
bool  PythonQtShell_Positionable::isHidden()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("isHidden");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("isHidden", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::isHidden();
}
bool  PythonQtShell_Positionable::isOpaque()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("isOpaque");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("isOpaque", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::isOpaque();
}
bool  PythonQtShell_Positionable::isPositionable()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("isPositionable");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("isPositionable", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::isPositionable();
}
bool  PythonQtShell_Positionable::isVisible()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("isVisible");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("isVisible", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::isVisible();
}
void PythonQtShell_Positionable::languageChange()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("languageChange");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={""};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::languageChange();
}
int  PythonQtShell_Positionable::maxHeight()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("maxHeight");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("maxHeight", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::maxHeight();
}
int  PythonQtShell_Positionable::maxWidth()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("maxWidth");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("maxWidth", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::maxWidth();
}
void PythonQtShell_Positionable::remove()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("remove");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={""};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::remove();
}
bool  PythonQtShell_Positionable::requestFocusInWindow()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("requestFocusInWindow");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("requestFocusInWindow", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::requestFocusInWindow();
}
void PythonQtShell_Positionable::rotate(int  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("rotate");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::rotate(arg__1);
}
void PythonQtShell_Positionable::setBackground(QColor  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setBackground");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QColor"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::setBackground(arg__1);
}
void PythonQtShell_Positionable::setControlling(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setControlling");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::setControlling(arg__1);
}
bool  PythonQtShell_Positionable::setDisableControlMenu(QMenu*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setDisableControlMenu");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QMenu*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("setDisableControlMenu", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::setDisableControlMenu(arg__1);
}
void PythonQtShell_Positionable::setDisplayLevel(int  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setDisplayLevel");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::setDisplayLevel(arg__1);
}
bool  PythonQtShell_Positionable::setEditIconMenu(QMenu*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setEditIconMenu");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QMenu*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("setEditIconMenu", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::setEditIconMenu(arg__1);
}
bool  PythonQtShell_Positionable::setEditItemMenu(QMenu*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setEditItemMenu");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QMenu*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("setEditItemMenu", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::setEditItemMenu(arg__1);
}
void PythonQtShell_Positionable::setEditable(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setEditable");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::setEditable(arg__1);
}
void PythonQtShell_Positionable::setEditor(Editor*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setEditor");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "Editor*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::setEditor(arg__1);
}
void PythonQtShell_Positionable::setForeground(QColor  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setForeground");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QColor"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::setForeground(arg__1);
}
void PythonQtShell_Positionable::setHidden(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setHidden");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::setHidden(arg__1);
}
void PythonQtShell_Positionable::setLocation(QPointF  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setLocation");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QPointF"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::setLocation(arg__1);
}
void PythonQtShell_Positionable::setLocation(int  arg__1, int  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setLocation");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
    void* args[3] = {NULL, (void*)&arg__1, (void*)&arg__2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::setLocation(arg__1, arg__2);
}
void PythonQtShell_Positionable::setOpaque(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setOpaque");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::setOpaque(arg__1);
}
void PythonQtShell_Positionable::setPositionable(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setPositionable");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::setPositionable(arg__1);
}
bool  PythonQtShell_Positionable::setRotateMenu(QMenu*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setRotateMenu");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QMenu*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("setRotateMenu", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::setRotateMenu(arg__1);
}
bool  PythonQtShell_Positionable::setRotateOrthogonalMenu(QMenu*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setRotateOrthogonalMenu");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QMenu*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("setRotateOrthogonalMenu", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::setRotateOrthogonalMenu(arg__1);
}
void PythonQtShell_Positionable::setScale(double  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setScale");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "double"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::setScale(arg__1);
}
bool  PythonQtShell_Positionable::setScaleMenu(QMenu*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setScaleMenu");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QMenu*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("setScaleMenu", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::setScaleMenu(arg__1);
}
void PythonQtShell_Positionable::setShowTooltip(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setShowTooltip");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::setShowTooltip(arg__1);
}
void PythonQtShell_Positionable::setSize(int  arg__1, int  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setSize");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
    void* args[3] = {NULL, (void*)&arg__1, (void*)&arg__2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::setSize(arg__1, arg__2);
}
bool  PythonQtShell_Positionable::setTextEditMenu(QMenu*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setTextEditMenu");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QMenu*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("setTextEditMenu", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::setTextEditMenu(arg__1);
}
void PythonQtShell_Positionable::setViewCoordinates(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setViewCoordinates");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::setViewCoordinates(arg__1);
}
void PythonQtShell_Positionable::setVisible(bool  b0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setVisible");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&b0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::setVisible(b0);
}
void PythonQtShell_Positionable::showHidden()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("showHidden");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={""};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::showHidden();
}
bool  PythonQtShell_Positionable::showPopUp(QMenu*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("showPopUp");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QMenu*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("showPopUp", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::showPopUp(arg__1);
}
bool  PythonQtShell_Positionable::showTooltip()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("showTooltip");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("showTooltip", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::showToolTip();
}
bool  PythonQtShell_Positionable::storeItem()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("storeItem");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("storeItem", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::storeItem();
}
bool  PythonQtShell_Positionable::updateScene()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("updateScene");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("updateScene", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Positionable::updateScene();
}
void PythonQtShell_Positionable::updateSize()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("updateSize");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={""};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Positionable::updateSize();
}
Positionable* PythonQtWrapper_Positionable::new_Positionable(QString  text, QWidget*  parent)
{ 
return new PythonQtShell_Positionable(text, parent); }

Positionable* PythonQtWrapper_Positionable::new_Positionable(QWidget*  parent)
{ 
return new PythonQtShell_Positionable(parent); }

bool  PythonQtWrapper_Positionable::contains(Positionable* theWrappedObject, int  arg__1, int  arg__2)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_contains(arg__1, arg__2));
}

Positionable*  PythonQtWrapper_Positionable::deepClone(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_deepClone());
}

void PythonQtWrapper_Positionable::doMouseClicked(Positionable* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_doMouseClicked(arg__1));
}

void PythonQtWrapper_Positionable::doMouseDragged(Positionable* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_doMouseDragged(arg__1));
}

void PythonQtWrapper_Positionable::doMouseEntered(Positionable* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_doMouseEntered(arg__1));
}

void PythonQtWrapper_Positionable::doMouseExited(Positionable* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_doMouseExited(arg__1));
}

void PythonQtWrapper_Positionable::doMouseMoved(Positionable* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_doMouseMoved(arg__1));
}

void PythonQtWrapper_Positionable::doMousePressed(Positionable* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_doMousePressed(arg__1));
}

void PythonQtWrapper_Positionable::doMouseReleased(Positionable* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_doMouseReleased(arg__1));
}

bool  PythonQtWrapper_Positionable::doViemMenu(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_doViemMenu());
}

Positionable*  PythonQtWrapper_Positionable::finishClone(Positionable* theWrappedObject, Positionable*  arg__1)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_finishClone(arg__1));
}

QColor  PythonQtWrapper_Positionable::getBackground(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_getBackground());
}

QRectF  PythonQtWrapper_Positionable::getBounds(Positionable* theWrappedObject, QRectF  arg__1)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_getBounds(arg__1));
}

int  PythonQtWrapper_Positionable::getDegrees(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_getDegrees());
}

int  PythonQtWrapper_Positionable::getDisplayLevel(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_getDisplayLevel());
}

Editor*  PythonQtWrapper_Positionable::getEditor(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_getEditor());
}

QFont  PythonQtWrapper_Positionable::getFont(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_getFont());
}

QColor  PythonQtWrapper_Positionable::getForeground(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_getForeground());
}

int  PythonQtWrapper_Positionable::getHeight(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_getHeight());
}

QGraphicsItem*  PythonQtWrapper_Positionable::getItem(Positionable* theWrappedObject)
{
  return ( theWrappedObject->getItem());
}

QPointF  PythonQtWrapper_Positionable::getLocation(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_getLocation());
}

QString  PythonQtWrapper_Positionable::getNameString(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_getNameString());
}

NamedBean*  PythonQtWrapper_Positionable::getNamedBean(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_getNamedBean());
}

bool  PythonQtWrapper_Positionable::getSaveOpaque(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_getSaveOpaque());
}

double  PythonQtWrapper_Positionable::getScale(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_getScale());
}

bool  PythonQtWrapper_Positionable::getViewCoordinates(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_getViewCoordinates());
}

int  PythonQtWrapper_Positionable::getWidth(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_getWidth());
}

int  PythonQtWrapper_Positionable::getX(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_getX());
}

int  PythonQtWrapper_Positionable::getY(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_getY());
}

void PythonQtWrapper_Positionable::invalidate(Positionable* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_invalidate());
}

bool  PythonQtWrapper_Positionable::isControlling(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_isControlling());
}

bool  PythonQtWrapper_Positionable::isEditable(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_isEditable());
}

bool  PythonQtWrapper_Positionable::isHidden(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_isHidden());
}

bool  PythonQtWrapper_Positionable::isOpaque(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_isOpaque());
}

bool  PythonQtWrapper_Positionable::isPositionable(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_isPositionable());
}

bool  PythonQtWrapper_Positionable::isVisible(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_isVisible());
}

void PythonQtWrapper_Positionable::languageChange(Positionable* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_languageChange());
}

int  PythonQtWrapper_Positionable::maxHeight(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_maxHeight());
}

int  PythonQtWrapper_Positionable::maxWidth(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_maxWidth());
}

void PythonQtWrapper_Positionable::remove(Positionable* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_remove());
}

bool  PythonQtWrapper_Positionable::requestFocusInWindow(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_requestFocusInWindow());
}

void PythonQtWrapper_Positionable::rotate(Positionable* theWrappedObject, int  arg__1)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_rotate(arg__1));
}

void PythonQtWrapper_Positionable::setBackground(Positionable* theWrappedObject, QColor  arg__1)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_setBackground(arg__1));
}

void PythonQtWrapper_Positionable::setControlling(Positionable* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_setControlling(arg__1));
}

bool  PythonQtWrapper_Positionable::setDisableControlMenu(Positionable* theWrappedObject, QMenu*  arg__1)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_setDisableControlMenu(arg__1));
}

void PythonQtWrapper_Positionable::setDisplayLevel(Positionable* theWrappedObject, int  arg__1)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_setDisplayLevel(arg__1));
}

bool  PythonQtWrapper_Positionable::setEditIconMenu(Positionable* theWrappedObject, QMenu*  arg__1)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_setEditIconMenu(arg__1));
}

bool  PythonQtWrapper_Positionable::setEditItemMenu(Positionable* theWrappedObject, QMenu*  arg__1)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_setEditItemMenu(arg__1));
}

void PythonQtWrapper_Positionable::setEditable(Positionable* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_setEditable(arg__1));
}

void PythonQtWrapper_Positionable::setEditor(Positionable* theWrappedObject, Editor*  arg__1)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_setEditor(arg__1));
}

void PythonQtWrapper_Positionable::setForeground(Positionable* theWrappedObject, QColor  arg__1)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_setForeground(arg__1));
}

void PythonQtWrapper_Positionable::setHidden(Positionable* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_setHidden(arg__1));
}

void PythonQtWrapper_Positionable::setItem(Positionable* theWrappedObject, QGraphicsTextItem*  item)
{
  ( theWrappedObject->setItem(item));
}

void PythonQtWrapper_Positionable::setLocation(Positionable* theWrappedObject, QPointF  arg__1)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_setLocation(arg__1));
}

void PythonQtWrapper_Positionable::setLocation(Positionable* theWrappedObject, int  arg__1, int  arg__2)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_setLocation(arg__1, arg__2));
}

void PythonQtWrapper_Positionable::setOpaque(Positionable* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_setOpaque(arg__1));
}

void PythonQtWrapper_Positionable::setPositionable(Positionable* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_setPositionable(arg__1));
}

bool  PythonQtWrapper_Positionable::setRotateMenu(Positionable* theWrappedObject, QMenu*  arg__1)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_setRotateMenu(arg__1));
}

bool  PythonQtWrapper_Positionable::setRotateOrthogonalMenu(Positionable* theWrappedObject, QMenu*  arg__1)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_setRotateOrthogonalMenu(arg__1));
}

void PythonQtWrapper_Positionable::setScale(Positionable* theWrappedObject, double  arg__1)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_setScale(arg__1));
}

bool  PythonQtWrapper_Positionable::setScaleMenu(Positionable* theWrappedObject, QMenu*  arg__1)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_setScaleMenu(arg__1));
}

void PythonQtWrapper_Positionable::setShowTooltip(Positionable* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_setShowTooltip(arg__1));
}

void PythonQtWrapper_Positionable::setSize(Positionable* theWrappedObject, int  arg__1, int  arg__2)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_setSize(arg__1, arg__2));
}

bool  PythonQtWrapper_Positionable::setTextEditMenu(Positionable* theWrappedObject, QMenu*  arg__1)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_setTextEditMenu(arg__1));
}

void PythonQtWrapper_Positionable::setViewCoordinates(Positionable* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_setViewCoordinates(arg__1));
}

void PythonQtWrapper_Positionable::setVisible(Positionable* theWrappedObject, bool  b)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_setVisible(b));
}

void PythonQtWrapper_Positionable::showHidden(Positionable* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_showHidden());
}

bool  PythonQtWrapper_Positionable::showPopUp(Positionable* theWrappedObject, QMenu*  arg__1)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_showPopUp(arg__1));
}

bool  PythonQtWrapper_Positionable::showTooltip(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_showTooltip());
}

bool  PythonQtWrapper_Positionable::storeItem(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_storeItem());
}

bool  PythonQtWrapper_Positionable::updateScene(Positionable* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_updateScene());
}

void PythonQtWrapper_Positionable::updateSize(Positionable* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_Positionable*)theWrappedObject)->promoted_updateSize());
}



PythonQtShell_PowerManager::~PythonQtShell_PowerManager() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_PowerManager::addPropertyChangeListener(PropertyChangeListener*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("addPropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  PowerManager::addPropertyChangeListener(arg__1);
}
void PythonQtShell_PowerManager::childEvent(QChildEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("childEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QChildEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  PowerManager::childEvent(arg__1);
}
void PythonQtShell_PowerManager::customEvent(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("customEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  PowerManager::customEvent(arg__1);
}
void PythonQtShell_PowerManager::dispose()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("dispose");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={""};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  PowerManager::dispose();
}
bool  PythonQtShell_PowerManager::event(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("event");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("event", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return PowerManager::event(arg__1);
}
bool  PythonQtShell_PowerManager::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("eventFilter");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QObject*" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      bool returnValue;
    void* args[3] = {NULL, (void*)&arg__1, (void*)&arg__2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("eventFilter", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return PowerManager::eventFilter(arg__1, arg__2);
}
int  PythonQtShell_PowerManager::getPower()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getPower");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getPower", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return PowerManager::getPower();
}
QString  PythonQtShell_PowerManager::getUserName()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getUserName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getUserName", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return PowerManager::getUserName();
}
void PythonQtShell_PowerManager::removePropertyChangeListener(PropertyChangeListener*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("removePropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  PowerManager::removePropertyChangeListener(arg__1);
}
void PythonQtShell_PowerManager::setPower(int  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setPower");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  PowerManager::setPower(arg__1);
}
void PythonQtShell_PowerManager::timerEvent(QTimerEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("timerEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QTimerEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  PowerManager::timerEvent(arg__1);
}
PowerManager* PythonQtWrapper_PowerManager::new_PowerManager(QObject*  parent)
{ 
return new PythonQtShell_PowerManager(parent); }

PowerManager* PythonQtWrapper_PowerManager::new_PowerManager(const PowerManager&  arg__1)
{ 
return new PythonQtShell_PowerManager(arg__1); }

void PythonQtWrapper_PowerManager::addPropertyChangeListener(PowerManager* theWrappedObject, PropertyChangeListener*  arg__1)
{
  ( ((PythonQtPublicPromoter_PowerManager*)theWrappedObject)->promoted_addPropertyChangeListener(arg__1));
}

void PythonQtWrapper_PowerManager::dispose(PowerManager* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_PowerManager*)theWrappedObject)->promoted_dispose());
}

int  PythonQtWrapper_PowerManager::getPower(PowerManager* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_PowerManager*)theWrappedObject)->promoted_getPower());
}

QString  PythonQtWrapper_PowerManager::getUserName(PowerManager* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_PowerManager*)theWrappedObject)->promoted_getUserName());
}

void PythonQtWrapper_PowerManager::removePropertyChangeListener(PowerManager* theWrappedObject, PropertyChangeListener*  arg__1)
{
  ( ((PythonQtPublicPromoter_PowerManager*)theWrappedObject)->promoted_removePropertyChangeListener(arg__1));
}

void PythonQtWrapper_PowerManager::setPower(PowerManager* theWrappedObject, int  arg__1)
{
  ( ((PythonQtPublicPromoter_PowerManager*)theWrappedObject)->promoted_setPower(arg__1));
}



PythonQtShell_ProgrammerManager::~PythonQtShell_ProgrammerManager() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_ProgrammerManager::childEvent(QChildEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("childEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QChildEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProgrammerManager::childEvent(arg__1);
}
void PythonQtShell_ProgrammerManager::customEvent(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("customEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProgrammerManager::customEvent(arg__1);
}
bool  PythonQtShell_ProgrammerManager::event(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("event");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("event", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProgrammerManager::event(arg__1);
}
bool  PythonQtShell_ProgrammerManager::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("eventFilter");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QObject*" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      bool returnValue;
    void* args[3] = {NULL, (void*)&arg__1, (void*)&arg__2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("eventFilter", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProgrammerManager::eventFilter(arg__1, arg__2);
}
QString  PythonQtShell_ProgrammerManager::getUserName()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getUserName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getUserName", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProgrammerManager::getUserName();
}
bool  PythonQtShell_ProgrammerManager::isAddressedModePossible()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("isAddressedModePossible");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("isAddressedModePossible", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProgrammerManager::isAddressedModePossible();
}
bool  PythonQtShell_ProgrammerManager::isGlobalProgrammerAvailable()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("isGlobalProgrammerAvailable");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("isGlobalProgrammerAvailable", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProgrammerManager::isGlobalProgrammerAvailable();
}
void PythonQtShell_ProgrammerManager::timerEvent(QTimerEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("timerEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QTimerEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProgrammerManager::timerEvent(arg__1);
}
ProgrammerManager* PythonQtWrapper_ProgrammerManager::new_ProgrammerManager(QObject*  parent)
{ 
return new PythonQtShell_ProgrammerManager(parent); }

QString  PythonQtWrapper_ProgrammerManager::getUserName(ProgrammerManager* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_ProgrammerManager*)theWrappedObject)->promoted_getUserName());
}

bool  PythonQtWrapper_ProgrammerManager::isAddressedModePossible(ProgrammerManager* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_ProgrammerManager*)theWrappedObject)->promoted_isAddressedModePossible());
}

bool  PythonQtWrapper_ProgrammerManager::isGlobalProgrammerAvailable(ProgrammerManager* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_ProgrammerManager*)theWrappedObject)->promoted_isGlobalProgrammerAvailable());
}



PythonQtShell_ProxyLightManager::~PythonQtShell_ProxyLightManager() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_ProxyLightManager::Register(NamedBean*  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("Register");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "NamedBean*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&s0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProxyLightManager::Register(s0);
}
void PythonQtShell_ProxyLightManager::addPropertyChangeListener(PropertyChangeListener*  l0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("addPropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&l0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProxyLightManager::addPropertyChangeListener(l0);
}
void PythonQtShell_ProxyLightManager::childEvent(QChildEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("childEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QChildEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProxyLightManager::childEvent(arg__1);
}
void PythonQtShell_ProxyLightManager::customEvent(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("customEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProxyLightManager::customEvent(arg__1);
}
void PythonQtShell_ProxyLightManager::deregister(NamedBean*  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("deregister");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "NamedBean*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&s0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProxyLightManager::deregister(s0);
}
void PythonQtShell_ProxyLightManager::dispose()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("dispose");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={""};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProxyLightManager::dispose();
}
bool  PythonQtShell_ProxyLightManager::event(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("event");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("event", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxyLightManager::event(arg__1);
}
bool  PythonQtShell_ProxyLightManager::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("eventFilter");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QObject*" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      bool returnValue;
    void* args[3] = {NULL, (void*)&arg__1, (void*)&arg__2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("eventFilter", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxyLightManager::eventFilter(arg__1, arg__2);
}
NamedBean*  PythonQtShell_ProxyLightManager::getBeanBySystemName(QString  systemName0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getBeanBySystemName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"NamedBean*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      NamedBean* returnValue;
    void* args[2] = {NULL, (void*)&systemName0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getBeanBySystemName", methodInfo, result);
        } else {
          returnValue = *((NamedBean**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxyLightManager::getBeanBySystemName(systemName0);
}
NamedBean*  PythonQtShell_ProxyLightManager::getBeanByUserName(QString  userName0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getBeanByUserName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"NamedBean*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      NamedBean* returnValue;
    void* args[2] = {NULL, (void*)&userName0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getBeanByUserName", methodInfo, result);
        } else {
          returnValue = *((NamedBean**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxyLightManager::getBeanByUserName(userName0);
}
NamedBean*  PythonQtShell_ProxyLightManager::getNamedBean(QString  name0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNamedBean");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"NamedBean*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      NamedBean* returnValue;
    void* args[2] = {NULL, (void*)&name0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getNamedBean", methodInfo, result);
        } else {
          returnValue = *((NamedBean**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxyLightManager::getNamedBean(name0);
}
QList<NamedBean* >*  PythonQtShell_ProxyLightManager::getNamedBeanList()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNamedBeanList");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QList<NamedBean* >*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QList<NamedBean* >* returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getNamedBeanList", methodInfo, result);
        } else {
          returnValue = *((QList<NamedBean* >**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxyLightManager::getNamedBeanList();
}
QStringList  PythonQtShell_ProxyLightManager::getSystemNameArray()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemNameArray");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QStringList"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QStringList returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSystemNameArray", methodInfo, result);
        } else {
          returnValue = *((QStringList*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxyLightManager::getSystemNameArray();
}
QStringList  PythonQtShell_ProxyLightManager::getSystemNameList()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemNameList");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QStringList"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QStringList returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSystemNameList", methodInfo, result);
        } else {
          returnValue = *((QStringList*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxyLightManager::getSystemNameList();
}
QString  PythonQtShell_ProxyLightManager::getSystemPrefix()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemPrefix");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSystemPrefix", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxyLightManager::getSystemPrefix();
}
int  PythonQtShell_ProxyLightManager::getXMLOrder()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getXMLOrder");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getXMLOrder", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxyLightManager::getXMLOrder();
}
NamedBean*  PythonQtShell_ProxyLightManager::makeBean(int  i0, QString  systemName1, QString  userName2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("makeBean");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"NamedBean*" , "int" , "QString" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(4, argumentList);
      NamedBean* returnValue;
    void* args[4] = {NULL, (void*)&i0, (void*)&systemName1, (void*)&userName2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("makeBean", methodInfo, result);
        } else {
          returnValue = *((NamedBean**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxyLightManager::makeBean(i0, systemName1, userName2);
}
Manager*  PythonQtShell_ProxyLightManager::makeInternalManager()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("makeInternalManager");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"AbstractManager*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      AbstractManager* returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("makeInternalManager", methodInfo, result);
        } else {
          returnValue = *((AbstractManager**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxyLightManager::makeInternalManager();
}
QString  PythonQtShell_ProxyLightManager::makeSystemName(QString  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("makeSystemName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      QString returnValue;
    void* args[2] = {NULL, (void*)&s0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("makeSystemName", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxyLightManager::makeSystemName(s0);
}
void PythonQtShell_ProxyLightManager::on_propertyChange(PropertyChangeEvent*  e0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("on_propertyChange");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&e0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProxyLightManager::on_propertyChange(e0);
}
void PythonQtShell_ProxyLightManager::removePropertyChangeListener(PropertyChangeListener*  l0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("removePropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&l0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProxyLightManager::removePropertyChangeListener(l0);
}
void PythonQtShell_ProxyLightManager::timerEvent(QTimerEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("timerEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QTimerEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProxyLightManager::timerEvent(arg__1);
}
char  PythonQtShell_ProxyLightManager::typeLetter()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("typeLetter");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"char"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      char returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("typeLetter", methodInfo, result);
        } else {
          returnValue = *((char*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxyLightManager::typeLetter();
}
ProxyLightManager* PythonQtWrapper_ProxyLightManager::new_ProxyLightManager(QObject*  parent)
{ 
return new PythonQtShell_ProxyLightManager(parent); }

void PythonQtWrapper_ProxyLightManager::activateAllLights(ProxyLightManager* theWrappedObject)
{
  ( theWrappedObject->activateAllLights());
}

bool  PythonQtWrapper_ProxyLightManager::allowMultipleAdditions(ProxyLightManager* theWrappedObject, QString  systemName)
{
  return ( theWrappedObject->allowMultipleAdditions(systemName));
}

QString  PythonQtWrapper_ProxyLightManager::convertSystemNameToAlternate(ProxyLightManager* theWrappedObject, QString  systemName)
{
  return ( theWrappedObject->convertSystemNameToAlternate(systemName));
}

Light*  PythonQtWrapper_ProxyLightManager::getBySystemName(ProxyLightManager* theWrappedObject, QString  systemName)
{
  return ( theWrappedObject->getBySystemName(systemName));
}

Light*  PythonQtWrapper_ProxyLightManager::getByUserName(ProxyLightManager* theWrappedObject, QString  userName)
{
  return ( theWrappedObject->getByUserName(userName));
}

Light*  PythonQtWrapper_ProxyLightManager::getLight(ProxyLightManager* theWrappedObject, QString  name)
{
  return ( theWrappedObject->getLight(name));
}

int  PythonQtWrapper_ProxyLightManager::getXMLOrder(ProxyLightManager* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_ProxyLightManager*)theWrappedObject)->promoted_getXMLOrder());
}

NamedBean*  PythonQtWrapper_ProxyLightManager::makeBean(ProxyLightManager* theWrappedObject, int  i, QString  systemName, QString  userName)
{
  return ( ((PythonQtPublicPromoter_ProxyLightManager*)theWrappedObject)->promoted_makeBean(i, systemName, userName));
}

Manager*  PythonQtWrapper_ProxyLightManager::makeInternalManager(ProxyLightManager* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_ProxyLightManager*)theWrappedObject)->promoted_makeInternalManager());
}

Light*  PythonQtWrapper_ProxyLightManager::newLight(ProxyLightManager* theWrappedObject, QString  systemName, QString  userName)
{
  return ( theWrappedObject->newLight(systemName, userName));
}

NamedBean*  PythonQtWrapper_ProxyLightManager::newNamedBean(ProxyLightManager* theWrappedObject, QString  systemName, QString  userName)
{
  return ( theWrappedObject->newNamedBean(systemName, userName));
}

QString  PythonQtWrapper_ProxyLightManager::normalizeSystemName(ProxyLightManager* theWrappedObject, QString  systemName)
{
  return ( theWrappedObject->normalizeSystemName(systemName));
}

Light*  PythonQtWrapper_ProxyLightManager::provideLight(ProxyLightManager* theWrappedObject, QString  name)
{
  return ( theWrappedObject->provideLight(name));
}

bool  PythonQtWrapper_ProxyLightManager::supportsVariableLights(ProxyLightManager* theWrappedObject, QString  systemName)
{
  return ( theWrappedObject->supportsVariableLights(systemName));
}

bool  PythonQtWrapper_ProxyLightManager::validSystemNameConfig(ProxyLightManager* theWrappedObject, QString  systemName)
{
  return ( theWrappedObject->validSystemNameConfig(systemName));
}

bool  PythonQtWrapper_ProxyLightManager::validSystemNameFormat(ProxyLightManager* theWrappedObject, QString  systemName)
{
  return ( theWrappedObject->validSystemNameFormat(systemName));
}



PythonQtShell_ProxySensorManager::~PythonQtShell_ProxySensorManager() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_ProxySensorManager::Register(NamedBean*  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("Register");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "NamedBean*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&s0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProxySensorManager::Register(s0);
}
void PythonQtShell_ProxySensorManager::addPropertyChangeListener(PropertyChangeListener*  l0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("addPropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&l0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProxySensorManager::addPropertyChangeListener(l0);
}
void PythonQtShell_ProxySensorManager::childEvent(QChildEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("childEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QChildEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProxySensorManager::childEvent(arg__1);
}
void PythonQtShell_ProxySensorManager::customEvent(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("customEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProxySensorManager::customEvent(arg__1);
}
void PythonQtShell_ProxySensorManager::deregister(NamedBean*  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("deregister");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "NamedBean*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&s0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProxySensorManager::deregister(s0);
}
void PythonQtShell_ProxySensorManager::dispose()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("dispose");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={""};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProxySensorManager::dispose();
}
bool  PythonQtShell_ProxySensorManager::event(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("event");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("event", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxySensorManager::event(arg__1);
}
bool  PythonQtShell_ProxySensorManager::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("eventFilter");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QObject*" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      bool returnValue;
    void* args[3] = {NULL, (void*)&arg__1, (void*)&arg__2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("eventFilter", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxySensorManager::eventFilter(arg__1, arg__2);
}
NamedBean*  PythonQtShell_ProxySensorManager::getBeanBySystemName(QString  systemName0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getBeanBySystemName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"NamedBean*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      NamedBean* returnValue;
    void* args[2] = {NULL, (void*)&systemName0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getBeanBySystemName", methodInfo, result);
        } else {
          returnValue = *((NamedBean**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxySensorManager::getBeanBySystemName(systemName0);
}
NamedBean*  PythonQtShell_ProxySensorManager::getBeanByUserName(QString  userName0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getBeanByUserName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"NamedBean*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      NamedBean* returnValue;
    void* args[2] = {NULL, (void*)&userName0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getBeanByUserName", methodInfo, result);
        } else {
          returnValue = *((NamedBean**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxySensorManager::getBeanByUserName(userName0);
}
//AbstractManager*  PythonQtShell_ProxySensorManager::getInternal()
//{
//if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
//  static PyObject* name = PyString_FromString("getInternal");
//  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
//  if (obj) {
//    static const char* argumentList[] ={"AbstractManager*"};
//    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
//      AbstractManager* returnValue;
//    void* args[1] = {NULL};
//    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
//    if (result) {
//      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
//      if (args[0]!=&returnValue) {
//        if (args[0]==NULL) {
//          PythonQt::priv()->handleVirtualOverloadReturnError("getInternal", methodInfo, result);
//        } else {
//          returnValue = *((AbstractManager**)args[0]);
//        }
//      }
//    }
//    if (result) { Py_DECREF(result); }
//    Py_DECREF(obj);
//    return returnValue;
//  } else {
//    PyErr_Clear();
//  }
//}
//  return ProxySensorManager::getInternal();
//}
NamedBean*  PythonQtShell_ProxySensorManager::getNamedBean(QString  name0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNamedBean");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"NamedBean*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      NamedBean* returnValue;
    void* args[2] = {NULL, (void*)&name0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getNamedBean", methodInfo, result);
        } else {
          returnValue = *((NamedBean**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxySensorManager::getNamedBean(name0);
}
QList<NamedBean* >*  PythonQtShell_ProxySensorManager::getNamedBeanList()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNamedBeanList");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QList<NamedBean* >*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QList<NamedBean* >* returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getNamedBeanList", methodInfo, result);
        } else {
          returnValue = *((QList<NamedBean* >**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxySensorManager::getNamedBeanList();
}
QStringList  PythonQtShell_ProxySensorManager::getSystemNameArray()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemNameArray");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QStringList"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QStringList returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSystemNameArray", methodInfo, result);
        } else {
          returnValue = *((QStringList*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxySensorManager::getSystemNameArray();
}
QStringList  PythonQtShell_ProxySensorManager::getSystemNameList()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemNameList");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QStringList"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QStringList returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSystemNameList", methodInfo, result);
        } else {
          returnValue = *((QStringList*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxySensorManager::getSystemNameList();
}
QString  PythonQtShell_ProxySensorManager::getSystemPrefix()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemPrefix");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSystemPrefix", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxySensorManager::getSystemPrefix();
}
int  PythonQtShell_ProxySensorManager::getXMLOrder()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getXMLOrder");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getXMLOrder", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxySensorManager::getXMLOrder();
}
Sensor*  PythonQtShell_ProxySensorManager::makeBean(int  i0, QString  systemName1, QString  userName2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("makeBean");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"Sensor*" , "int" , "QString" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(4, argumentList);
      Sensor* returnValue;
    void* args[4] = {NULL, (void*)&i0, (void*)&systemName1, (void*)&userName2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("makeBean", methodInfo, result);
        } else {
          returnValue = *((Sensor**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxySensorManager::makeBean(i0, systemName1, userName2);
}
Manager*  PythonQtShell_ProxySensorManager::makeInternalManager()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("makeInternalManager");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"AbstractManager*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      AbstractManager* returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("makeInternalManager", methodInfo, result);
        } else {
          returnValue = *((AbstractManager**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxySensorManager::makeInternalManager();
}
QString  PythonQtShell_ProxySensorManager::makeSystemName(QString  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("makeSystemName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      QString returnValue;
    void* args[2] = {NULL, (void*)&s0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("makeSystemName", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxySensorManager::makeSystemName(s0);
}
void PythonQtShell_ProxySensorManager::on_propertyChange(PropertyChangeEvent*  e0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("on_propertyChange");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&e0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProxySensorManager::on_propertyChange(e0);
}
void PythonQtShell_ProxySensorManager::removePropertyChangeListener(PropertyChangeListener*  l0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("removePropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&l0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProxySensorManager::removePropertyChangeListener(l0);
}
void PythonQtShell_ProxySensorManager::timerEvent(QTimerEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("timerEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QTimerEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProxySensorManager::timerEvent(arg__1);
}
char  PythonQtShell_ProxySensorManager::typeLetter()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("typeLetter");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"char"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      char returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("typeLetter", methodInfo, result);
        } else {
          returnValue = *((char*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxySensorManager::typeLetter();
}
ProxySensorManager* PythonQtWrapper_ProxySensorManager::new_ProxySensorManager()
{ 
return new PythonQtShell_ProxySensorManager(); }

bool  PythonQtWrapper_ProxySensorManager::allowMultipleAdditions(ProxySensorManager* theWrappedObject, QString  systemName)
{
  return ( theWrappedObject->allowMultipleAdditions(systemName));
}

QString  PythonQtWrapper_ProxySensorManager::createSystemName(ProxySensorManager* theWrappedObject, QString  curAddress, QString  prefix) throw (JmriException)
{
  return ( theWrappedObject->createSystemName(curAddress, prefix));
}

Sensor*  PythonQtWrapper_ProxySensorManager::getBySystemName(ProxySensorManager* theWrappedObject, QString  sName)
{
  return ( theWrappedObject->getBySystemName(sName));
}

Sensor*  PythonQtWrapper_ProxySensorManager::getByUserName(ProxySensorManager* theWrappedObject, QString  userName)
{
  return ( theWrappedObject->getByUserName(userName));
}

QCompleter*  PythonQtWrapper_ProxySensorManager::getCompleter(ProxySensorManager* theWrappedObject, QString  text)
{
  return ( theWrappedObject->getCompleter(text));
}

long  PythonQtWrapper_ProxySensorManager::getDefaultSensorDebounceGoingActive(ProxySensorManager* theWrappedObject)
{
  return ( theWrappedObject->getDefaultSensorDebounceGoingActive());
}

long  PythonQtWrapper_ProxySensorManager::getDefaultSensorDebounceGoingInActive(ProxySensorManager* theWrappedObject)
{
  return ( theWrappedObject->getDefaultSensorDebounceGoingInActive());
}

//AbstractManager*  PythonQtWrapper_ProxySensorManager::getInternal(ProxySensorManager* theWrappedObject)
//{
//  return ( ((PythonQtPublicPromoter_ProxySensorManager*)theWrappedObject)->promoted_getInternal());
//}

QString  PythonQtWrapper_ProxySensorManager::getNextValidAddress(ProxySensorManager* theWrappedObject, QString  curAddress, QString  prefix) throw (JmriException)
{
  return ( theWrappedObject->getNextValidAddress(curAddress, prefix));
}

Sensor*  PythonQtWrapper_ProxySensorManager::getSensor(ProxySensorManager* theWrappedObject, QString  name)
{
  return ( theWrappedObject->getSensor(name));
}

int  PythonQtWrapper_ProxySensorManager::getXMLOrder(ProxySensorManager* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_ProxySensorManager*)theWrappedObject)->promoted_getXMLOrder());
}

Sensor*  PythonQtWrapper_ProxySensorManager::makeBean(ProxySensorManager* theWrappedObject, int  i, QString  systemName, QString  userName)
{
  return ( ((PythonQtPublicPromoter_ProxySensorManager*)theWrappedObject)->promoted_makeBean(i, systemName, userName));
}

Manager*  PythonQtWrapper_ProxySensorManager::makeInternalManager(ProxySensorManager* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_ProxySensorManager*)theWrappedObject)->promoted_makeInternalManager());
}

NamedBean*  PythonQtWrapper_ProxySensorManager::newNamedBean(ProxySensorManager* theWrappedObject, QString  systemName, QString  userName)
{
  return ( ((PythonQtPublicPromoter_ProxySensorManager*)theWrappedObject)->promoted_newNamedBean(systemName, userName));
}

Sensor*  PythonQtWrapper_ProxySensorManager::newSensor(ProxySensorManager* theWrappedObject, QString  systemName, QString  userName)
{
  return ( theWrappedObject->newSensor(systemName, userName));
}

NamedBean*  PythonQtWrapper_ProxySensorManager::provideNamedBean(ProxySensorManager* theWrappedObject, QString  name)
{
  return ( ((PythonQtPublicPromoter_ProxySensorManager*)theWrappedObject)->promoted_provideNamedBean(name));
}

Sensor*  PythonQtWrapper_ProxySensorManager::provideSensor(ProxySensorManager* theWrappedObject, QString  sName)
{
  return ( theWrappedObject->provideSensor(sName));
}

void PythonQtWrapper_ProxySensorManager::setDefaultSensorDebounceGoingActive(ProxySensorManager* theWrappedObject, long  timer)
{
  ( theWrappedObject->setDefaultSensorDebounceGoingActive(timer));
}

void PythonQtWrapper_ProxySensorManager::setDefaultSensorDebounceGoingInActive(ProxySensorManager* theWrappedObject, long  timer)
{
  ( theWrappedObject->setDefaultSensorDebounceGoingInActive(timer));
}

void PythonQtWrapper_ProxySensorManager::updateAll(ProxySensorManager* theWrappedObject)
{
  ( theWrappedObject->updateAll());
}



PythonQtShell_ProxyTurnoutManager::~PythonQtShell_ProxyTurnoutManager() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_ProxyTurnoutManager::Register(NamedBean*  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("Register");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "NamedBean*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&s0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProxyTurnoutManager::Register(s0);
}
void PythonQtShell_ProxyTurnoutManager::addPropertyChangeListener(PropertyChangeListener*  l0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("addPropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&l0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProxyTurnoutManager::addPropertyChangeListener(l0);
}
void PythonQtShell_ProxyTurnoutManager::childEvent(QChildEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("childEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QChildEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProxyTurnoutManager::childEvent(arg__1);
}
void PythonQtShell_ProxyTurnoutManager::customEvent(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("customEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProxyTurnoutManager::customEvent(arg__1);
}
void PythonQtShell_ProxyTurnoutManager::deregister(NamedBean*  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("deregister");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "NamedBean*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&s0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProxyTurnoutManager::deregister(s0);
}
void PythonQtShell_ProxyTurnoutManager::dispose()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("dispose");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={""};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProxyTurnoutManager::dispose();
}
bool  PythonQtShell_ProxyTurnoutManager::event(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("event");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("event", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxyTurnoutManager::event(arg__1);
}
bool  PythonQtShell_ProxyTurnoutManager::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("eventFilter");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QObject*" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      bool returnValue;
    void* args[3] = {NULL, (void*)&arg__1, (void*)&arg__2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("eventFilter", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxyTurnoutManager::eventFilter(arg__1, arg__2);
}
NamedBean*  PythonQtShell_ProxyTurnoutManager::getBeanBySystemName(QString  systemName0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getBeanBySystemName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"NamedBean*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      NamedBean* returnValue;
    void* args[2] = {NULL, (void*)&systemName0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getBeanBySystemName", methodInfo, result);
        } else {
          returnValue = *((NamedBean**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxyTurnoutManager::getBeanBySystemName(systemName0);
}
NamedBean*  PythonQtShell_ProxyTurnoutManager::getBeanByUserName(QString  userName0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getBeanByUserName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"NamedBean*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      NamedBean* returnValue;
    void* args[2] = {NULL, (void*)&userName0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getBeanByUserName", methodInfo, result);
        } else {
          returnValue = *((NamedBean**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxyTurnoutManager::getBeanByUserName(userName0);
}
NamedBean*  PythonQtShell_ProxyTurnoutManager::getNamedBean(QString  name0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNamedBean");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"NamedBean*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      NamedBean* returnValue;
    void* args[2] = {NULL, (void*)&name0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getNamedBean", methodInfo, result);
        } else {
          returnValue = *((NamedBean**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxyTurnoutManager::getNamedBean(name0);
}
QList<NamedBean* >*  PythonQtShell_ProxyTurnoutManager::getNamedBeanList()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNamedBeanList");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QList<NamedBean* >*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QList<NamedBean* >* returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getNamedBeanList", methodInfo, result);
        } else {
          returnValue = *((QList<NamedBean* >**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxyTurnoutManager::getNamedBeanList();
}
QStringList  PythonQtShell_ProxyTurnoutManager::getSystemNameArray()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemNameArray");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QStringList"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QStringList returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSystemNameArray", methodInfo, result);
        } else {
          returnValue = *((QStringList*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxyTurnoutManager::getSystemNameArray();
}
QStringList  PythonQtShell_ProxyTurnoutManager::getSystemNameList()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemNameList");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QStringList"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QStringList returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSystemNameList", methodInfo, result);
        } else {
          returnValue = *((QStringList*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxyTurnoutManager::getSystemNameList();
}
QString  PythonQtShell_ProxyTurnoutManager::getSystemPrefix()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemPrefix");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSystemPrefix", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxyTurnoutManager::getSystemPrefix();
}
int  PythonQtShell_ProxyTurnoutManager::getXMLOrder()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getXMLOrder");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getXMLOrder", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxyTurnoutManager::getXMLOrder();
}
NamedBean*  PythonQtShell_ProxyTurnoutManager::makeBean(int  i0, QString  systemName1, QString  userName2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("makeBean");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"NamedBean*" , "int" , "QString" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(4, argumentList);
      NamedBean* returnValue;
    void* args[4] = {NULL, (void*)&i0, (void*)&systemName1, (void*)&userName2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("makeBean", methodInfo, result);
        } else {
          returnValue = *((NamedBean**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxyTurnoutManager::makeBean(i0, systemName1, userName2);
}
Manager*  PythonQtShell_ProxyTurnoutManager::makeInternalManager()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("makeInternalManager");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"AbstractManager*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      AbstractManager* returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("makeInternalManager", methodInfo, result);
        } else {
          returnValue = *((AbstractManager**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxyTurnoutManager::makeInternalManager();
}
QString  PythonQtShell_ProxyTurnoutManager::makeSystemName(QString  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("makeSystemName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      QString returnValue;
    void* args[2] = {NULL, (void*)&s0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("makeSystemName", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxyTurnoutManager::makeSystemName(s0);
}
void PythonQtShell_ProxyTurnoutManager::on_propertyChange(PropertyChangeEvent*  e0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("on_propertyChange");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&e0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProxyTurnoutManager::on_propertyChange(e0);
}
void PythonQtShell_ProxyTurnoutManager::removePropertyChangeListener(PropertyChangeListener*  l0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("removePropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&l0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProxyTurnoutManager::removePropertyChangeListener(l0);
}
void PythonQtShell_ProxyTurnoutManager::timerEvent(QTimerEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("timerEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QTimerEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ProxyTurnoutManager::timerEvent(arg__1);
}
char  PythonQtShell_ProxyTurnoutManager::typeLetter()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("typeLetter");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"char"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      char returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("typeLetter", methodInfo, result);
        } else {
          returnValue = *((char*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ProxyTurnoutManager::typeLetter();
}
ProxyTurnoutManager* PythonQtWrapper_ProxyTurnoutManager::new_ProxyTurnoutManager(QObject*  parent)
{ 
return new PythonQtShell_ProxyTurnoutManager(parent); }

void PythonQtWrapper_ProxyTurnoutManager::addManager(ProxyTurnoutManager* theWrappedObject, Manager*  m)
{
  ( theWrappedObject->addManager(m));
}

bool  PythonQtWrapper_ProxyTurnoutManager::allowMultipleAdditions(ProxyTurnoutManager* theWrappedObject, QString  systemName)
{
  return ( theWrappedObject->allowMultipleAdditions(systemName));
}

int  PythonQtWrapper_ProxyTurnoutManager::askControlType(ProxyTurnoutManager* theWrappedObject, QString  systemName)
{
  return ( theWrappedObject->askControlType(systemName));
}

int  PythonQtWrapper_ProxyTurnoutManager::askNumControlBits(ProxyTurnoutManager* theWrappedObject, QString  systemName)
{
  return ( theWrappedObject->askNumControlBits(systemName));
}

QString  PythonQtWrapper_ProxyTurnoutManager::createSystemName(ProxyTurnoutManager* theWrappedObject, QString  curAddress, QString  prefix) throw (JmriException)
{
  return ( theWrappedObject->createSystemName(curAddress, prefix));
}

Turnout*  PythonQtWrapper_ProxyTurnoutManager::getBySystemName(ProxyTurnoutManager* theWrappedObject, QString  systemName)
{
  return ( theWrappedObject->getBySystemName(systemName));
}

Turnout*  PythonQtWrapper_ProxyTurnoutManager::getByUserName(ProxyTurnoutManager* theWrappedObject, QString  userName)
{
  return ( theWrappedObject->getByUserName(userName));
}

QString  PythonQtWrapper_ProxyTurnoutManager::getClosedText(ProxyTurnoutManager* theWrappedObject)
{
  return ( theWrappedObject->getClosedText());
}

QCompleter*  PythonQtWrapper_ProxyTurnoutManager::getCompleter(ProxyTurnoutManager* theWrappedObject, QString  text)
{
  return ( theWrappedObject->getCompleter(text));
}

QString  PythonQtWrapper_ProxyTurnoutManager::getDefaultClosedSpeed(ProxyTurnoutManager* theWrappedObject)
{
  return ( theWrappedObject->getDefaultClosedSpeed());
}

QString  PythonQtWrapper_ProxyTurnoutManager::getDefaultThrownSpeed(ProxyTurnoutManager* theWrappedObject)
{
  return ( theWrappedObject->getDefaultThrownSpeed());
}

QString  PythonQtWrapper_ProxyTurnoutManager::getNextValidAddress(ProxyTurnoutManager* theWrappedObject, QString  curAddress, QString  prefix) throw (JmriException)
{
  return ( theWrappedObject->getNextValidAddress(curAddress, prefix));
}

QString  PythonQtWrapper_ProxyTurnoutManager::getThrownText(ProxyTurnoutManager* theWrappedObject)
{
  return ( theWrappedObject->getThrownText());
}

Turnout*  PythonQtWrapper_ProxyTurnoutManager::getTurnout(ProxyTurnoutManager* theWrappedObject, QString  name)
{
  return ( theWrappedObject->getTurnout(name));
}

QStringList  PythonQtWrapper_ProxyTurnoutManager::getValidOperationTypes(ProxyTurnoutManager* theWrappedObject)
{
  return ( theWrappedObject->getValidOperationTypes());
}

int  PythonQtWrapper_ProxyTurnoutManager::getXMLOrder(ProxyTurnoutManager* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_ProxyTurnoutManager*)theWrappedObject)->promoted_getXMLOrder());
}

bool  PythonQtWrapper_ProxyTurnoutManager::isControlTypeSupported(ProxyTurnoutManager* theWrappedObject, QString  systemName)
{
  return ( theWrappedObject->isControlTypeSupported(systemName));
}

bool  PythonQtWrapper_ProxyTurnoutManager::isNumControlBitsSupported(ProxyTurnoutManager* theWrappedObject, QString  systemName)
{
  return ( theWrappedObject->isNumControlBitsSupported(systemName));
}

NamedBean*  PythonQtWrapper_ProxyTurnoutManager::makeBean(ProxyTurnoutManager* theWrappedObject, int  i, QString  systemName, QString  userName)
{
  return ( ((PythonQtPublicPromoter_ProxyTurnoutManager*)theWrappedObject)->promoted_makeBean(i, systemName, userName));
}

Manager*  PythonQtWrapper_ProxyTurnoutManager::makeInternalManager(ProxyTurnoutManager* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_ProxyTurnoutManager*)theWrappedObject)->promoted_makeInternalManager());
}

NamedBean*  PythonQtWrapper_ProxyTurnoutManager::newNamedBean(ProxyTurnoutManager* theWrappedObject, QString  systemName, QString  userName)
{
  return ( ((PythonQtPublicPromoter_ProxyTurnoutManager*)theWrappedObject)->promoted_newNamedBean(systemName, userName));
}

Turnout*  PythonQtWrapper_ProxyTurnoutManager::newTurnout(ProxyTurnoutManager* theWrappedObject, QString  systemName, QString  userName)
{
  return ( theWrappedObject->newTurnout(systemName, userName));
}

void PythonQtWrapper_ProxyTurnoutManager::setDefaultClosedSpeed(ProxyTurnoutManager* theWrappedObject, QString  speed) throw (JmriException)
{
  ( theWrappedObject->setDefaultClosedSpeed(speed));
}

void PythonQtWrapper_ProxyTurnoutManager::setDefaultThrownSpeed(ProxyTurnoutManager* theWrappedObject, QString  speed) throw (JmriException)
{
  ( theWrappedObject->setDefaultThrownSpeed(speed));
}



PythonQtShell_ReporterManager::~PythonQtShell_ReporterManager() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_ReporterManager::Register(NamedBean*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("Register");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "NamedBean*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ReporterManager::Register(arg__1);
}
void PythonQtShell_ReporterManager::addPropertyChangeListener(PropertyChangeListener*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("addPropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ReporterManager::addPropertyChangeListener(arg__1);
}
bool  PythonQtShell_ReporterManager::allowMultipleAdditions(QString  systemName0) const
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("allowMultipleAdditions");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&systemName0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("allowMultipleAdditions", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ReporterManager::allowMultipleAdditions(systemName0);
}
void PythonQtShell_ReporterManager::childEvent(QChildEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("childEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QChildEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ReporterManager::childEvent(arg__1);
}
void PythonQtShell_ReporterManager::customEvent(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("customEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ReporterManager::customEvent(arg__1);
}
void PythonQtShell_ReporterManager::deregister(NamedBean*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("deregister");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "NamedBean*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ReporterManager::deregister(arg__1);
}
void PythonQtShell_ReporterManager::dispose()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("dispose");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={""};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ReporterManager::dispose();
}
bool  PythonQtShell_ReporterManager::event(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("event");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("event", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ReporterManager::event(arg__1);
}
bool  PythonQtShell_ReporterManager::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("eventFilter");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QObject*" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      bool returnValue;
    void* args[3] = {NULL, (void*)&arg__1, (void*)&arg__2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("eventFilter", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ReporterManager::eventFilter(arg__1, arg__2);
}
NamedBean*  PythonQtShell_ReporterManager::getBeanBySystemName(QString  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getBeanBySystemName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"NamedBean*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      NamedBean* returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getBeanBySystemName", methodInfo, result);
        } else {
          returnValue = *((NamedBean**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ReporterManager::getBeanBySystemName(arg__1);
}
NamedBean*  PythonQtShell_ReporterManager::getBeanByUserName(QString  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getBeanByUserName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"NamedBean*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      NamedBean* returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getBeanByUserName", methodInfo, result);
        } else {
          returnValue = *((NamedBean**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ReporterManager::getBeanByUserName(arg__1);
}
NamedBean*  PythonQtShell_ReporterManager::getNamedBean(QString  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNamedBean");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"NamedBean*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      NamedBean* returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getNamedBean", methodInfo, result);
        } else {
          returnValue = *((NamedBean**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ReporterManager::getNamedBean(arg__1);
}
QList<NamedBean* >*  PythonQtShell_ReporterManager::getNamedBeanList()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNamedBeanList");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QList<NamedBean* >*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QList<NamedBean* >* returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getNamedBeanList", methodInfo, result);
        } else {
          returnValue = *((QList<NamedBean* >**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ReporterManager::getNamedBeanList();
}
QString  PythonQtShell_ReporterManager::getNextValidAddress(QString  curAddress0, QString  prefix1) const
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNextValidAddress");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString" , "QString" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      QString returnValue;
    void* args[3] = {NULL, (void*)&curAddress0, (void*)&prefix1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getNextValidAddress", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ReporterManager::getNextValidAddress(curAddress0, prefix1);
}
QStringList  PythonQtShell_ReporterManager::getSystemNameArray()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemNameArray");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QStringList"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QStringList returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSystemNameArray", methodInfo, result);
        } else {
          returnValue = *((QStringList*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ReporterManager::getSystemNameArray();
}
QStringList  PythonQtShell_ReporterManager::getSystemNameList() const
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemNameList");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QStringList"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QStringList returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSystemNameList", methodInfo, result);
        } else {
          returnValue = *((QStringList*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ReporterManager::getSystemNameList();
}
QString  PythonQtShell_ReporterManager::getSystemPrefix()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemPrefix");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSystemPrefix", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ReporterManager::getSystemPrefix();
}
int  PythonQtShell_ReporterManager::getXMLOrder()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getXMLOrder");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getXMLOrder", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ReporterManager::getXMLOrder();
}
QString  PythonQtShell_ReporterManager::makeSystemName(QString  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("makeSystemName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      QString returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("makeSystemName", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ReporterManager::makeSystemName(arg__1);
}
void PythonQtShell_ReporterManager::removePropertyChangeListener(PropertyChangeListener*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("removePropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ReporterManager::removePropertyChangeListener(arg__1);
}
void PythonQtShell_ReporterManager::timerEvent(QTimerEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("timerEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QTimerEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ReporterManager::timerEvent(arg__1);
}
char  PythonQtShell_ReporterManager::typeLetter()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("typeLetter");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"char"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      char returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("typeLetter", methodInfo, result);
        } else {
          returnValue = *((char*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ReporterManager::typeLetter();
}
ReporterManager* PythonQtWrapper_ReporterManager::new_ReporterManager()
{ 
return new PythonQtShell_ReporterManager(); }

bool  PythonQtWrapper_ReporterManager::allowMultipleAdditions(ReporterManager* theWrappedObject, QString  systemName) const
{
  return ( ((PythonQtPublicPromoter_ReporterManager*)theWrappedObject)->promoted_allowMultipleAdditions(systemName));
}

QString  PythonQtWrapper_ReporterManager::getNextValidAddress(ReporterManager* theWrappedObject, QString  curAddress, QString  prefix) const
{
  return ( ((PythonQtPublicPromoter_ReporterManager*)theWrappedObject)->promoted_getNextValidAddress(curAddress, prefix));
}

QStringList  PythonQtWrapper_ReporterManager::getSystemNameList(ReporterManager* theWrappedObject) const
{
  return ( ((PythonQtPublicPromoter_ReporterManager*)theWrappedObject)->promoted_getSystemNameList());
}



PythonQtShell_RfidSensorManager::~PythonQtShell_RfidSensorManager() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_RfidSensorManager::Register(NamedBean*  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("Register");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "NamedBean*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&s0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  RfidSensorManager::Register(s0);
}
void PythonQtShell_RfidSensorManager::addPropertyChangeListener(PropertyChangeListener*  l0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("addPropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&l0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  RfidSensorManager::addPropertyChangeListener(l0);
}
bool  PythonQtShell_RfidSensorManager::allowMultipleAdditions(QString  systemName0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("allowMultipleAdditions");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&systemName0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("allowMultipleAdditions", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RfidSensorManager::allowMultipleAdditions(systemName0);
}
void PythonQtShell_RfidSensorManager::childEvent(QChildEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("childEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QChildEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  RfidSensorManager::childEvent(arg__1);
}
QString  PythonQtShell_RfidSensorManager::createSystemName(QString  curAddress0, QString  prefix1) throw (JmriException)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("createSystemName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString" , "QString" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      QString returnValue;
    void* args[3] = {NULL, (void*)&curAddress0, (void*)&prefix1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("createSystemName", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RfidSensorManager::createSystemName(curAddress0, prefix1);
}
void PythonQtShell_RfidSensorManager::customEvent(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("customEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  RfidSensorManager::customEvent(arg__1);
}
void PythonQtShell_RfidSensorManager::deregister(NamedBean*  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("deregister");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "NamedBean*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&s0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  RfidSensorManager::deregister(s0);
}
void PythonQtShell_RfidSensorManager::dispose()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("dispose");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={""};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  RfidSensorManager::dispose();
}
bool  PythonQtShell_RfidSensorManager::event(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("event");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("event", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RfidSensorManager::event(arg__1);
}
bool  PythonQtShell_RfidSensorManager::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("eventFilter");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QObject*" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      bool returnValue;
    void* args[3] = {NULL, (void*)&arg__1, (void*)&arg__2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("eventFilter", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RfidSensorManager::eventFilter(arg__1, arg__2);
}
NamedBean*  PythonQtShell_RfidSensorManager::getBeanBySystemName(QString  systemName0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getBeanBySystemName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"NamedBean*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      NamedBean* returnValue;
    void* args[2] = {NULL, (void*)&systemName0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getBeanBySystemName", methodInfo, result);
        } else {
          returnValue = *((NamedBean**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RfidSensorManager::getBeanBySystemName(systemName0);
}
NamedBean*  PythonQtShell_RfidSensorManager::getBeanByUserName(QString  userName0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getBeanByUserName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"NamedBean*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      NamedBean* returnValue;
    void* args[2] = {NULL, (void*)&userName0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getBeanByUserName", methodInfo, result);
        } else {
          returnValue = *((NamedBean**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RfidSensorManager::getBeanByUserName(userName0);
}
Sensor*  PythonQtShell_RfidSensorManager::getBySystemName(QString  key0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getBySystemName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"Sensor*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      Sensor* returnValue;
    void* args[2] = {NULL, (void*)&key0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getBySystemName", methodInfo, result);
        } else {
          returnValue = *((Sensor**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RfidSensorManager::getBySystemName(key0);
}
Sensor*  PythonQtShell_RfidSensorManager::getByUserName(QString  key0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getByUserName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"Sensor*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      Sensor* returnValue;
    void* args[2] = {NULL, (void*)&key0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getByUserName", methodInfo, result);
        } else {
          returnValue = *((Sensor**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RfidSensorManager::getByUserName(key0);
}
long  PythonQtShell_RfidSensorManager::getDefaultSensorDebounceGoingActive()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getDefaultSensorDebounceGoingActive");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"long"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      long returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getDefaultSensorDebounceGoingActive", methodInfo, result);
        } else {
          returnValue = *((long*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RfidSensorManager::getDefaultSensorDebounceGoingActive();
}
long  PythonQtShell_RfidSensorManager::getDefaultSensorDebounceGoingInActive()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getDefaultSensorDebounceGoingInActive");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"long"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      long returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getDefaultSensorDebounceGoingInActive", methodInfo, result);
        } else {
          returnValue = *((long*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RfidSensorManager::getDefaultSensorDebounceGoingInActive();
}
NamedBean*  PythonQtShell_RfidSensorManager::getNamedBean(QString  name0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNamedBean");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"NamedBean*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      NamedBean* returnValue;
    void* args[2] = {NULL, (void*)&name0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getNamedBean", methodInfo, result);
        } else {
          returnValue = *((NamedBean**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RfidSensorManager::getNamedBean(name0);
}
QList<NamedBean* >*  PythonQtShell_RfidSensorManager::getNamedBeanList()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNamedBeanList");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QList<NamedBean* >*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QList<NamedBean* >* returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getNamedBeanList", methodInfo, result);
        } else {
          returnValue = *((QList<NamedBean* >**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RfidSensorManager::getNamedBeanList();
}
QString  PythonQtShell_RfidSensorManager::getNextValidAddress(QString  curAddress0, QString  prefix1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNextValidAddress");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString" , "QString" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      QString returnValue;
    void* args[3] = {NULL, (void*)&curAddress0, (void*)&prefix1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getNextValidAddress", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RfidSensorManager::getNextValidAddress(curAddress0, prefix1);
}
Sensor*  PythonQtShell_RfidSensorManager::getSensor(QString  name0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSensor");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"Sensor*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      Sensor* returnValue;
    void* args[2] = {NULL, (void*)&name0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSensor", methodInfo, result);
        } else {
          returnValue = *((Sensor**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RfidSensorManager::getSensor(name0);
}
QStringList  PythonQtShell_RfidSensorManager::getSystemNameArray()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemNameArray");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QStringList"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QStringList returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSystemNameArray", methodInfo, result);
        } else {
          returnValue = *((QStringList*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RfidSensorManager::getSystemNameArray();
}
QStringList  PythonQtShell_RfidSensorManager::getSystemNameList()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemNameList");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QStringList"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QStringList returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSystemNameList", methodInfo, result);
        } else {
          returnValue = *((QStringList*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RfidSensorManager::getSystemNameList();
}
QString  PythonQtShell_RfidSensorManager::getSystemPrefix()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemPrefix");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSystemPrefix", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RfidSensorManager::getSystemPrefix();
}
int  PythonQtShell_RfidSensorManager::getXMLOrder()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getXMLOrder");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getXMLOrder", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RfidSensorManager::getXMLOrder();
}
QString  PythonQtShell_RfidSensorManager::makeSystemName(QString  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("makeSystemName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      QString returnValue;
    void* args[2] = {NULL, (void*)&s0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("makeSystemName", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RfidSensorManager::makeSystemName(s0);
}
Sensor*  PythonQtShell_RfidSensorManager::newSensor(QString  sysName0, QString  userName1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("newSensor");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"Sensor*" , "QString" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      Sensor* returnValue;
    void* args[3] = {NULL, (void*)&sysName0, (void*)&userName1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("newSensor", methodInfo, result);
        } else {
          returnValue = *((Sensor**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RfidSensorManager::newSensor(sysName0, userName1);
}
void PythonQtShell_RfidSensorManager::on_propertyChange(PropertyChangeEvent*  e0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("on_propertyChange");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&e0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  RfidSensorManager::on_propertyChange(e0);
}
Sensor*  PythonQtShell_RfidSensorManager::provideSensor(QString  name0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("provideSensor");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"Sensor*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      Sensor* returnValue;
    void* args[2] = {NULL, (void*)&name0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("provideSensor", methodInfo, result);
        } else {
          returnValue = *((Sensor**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RfidSensorManager::provideSensor(name0);
}
void PythonQtShell_RfidSensorManager::removePropertyChangeListener(PropertyChangeListener*  l0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("removePropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&l0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  RfidSensorManager::removePropertyChangeListener(l0);
}
void PythonQtShell_RfidSensorManager::setDefaultSensorDebounceGoingActive(long  timer0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setDefaultSensorDebounceGoingActive");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "long"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&timer0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  RfidSensorManager::setDefaultSensorDebounceGoingActive(timer0);
}
void PythonQtShell_RfidSensorManager::setDefaultSensorDebounceGoingInActive(long  timer0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setDefaultSensorDebounceGoingInActive");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "long"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&timer0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  RfidSensorManager::setDefaultSensorDebounceGoingInActive(timer0);
}
void PythonQtShell_RfidSensorManager::timerEvent(QTimerEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("timerEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QTimerEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  RfidSensorManager::timerEvent(arg__1);
}
char  PythonQtShell_RfidSensorManager::typeLetter()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("typeLetter");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"char"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      char returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("typeLetter", methodInfo, result);
        } else {
          returnValue = *((char*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RfidSensorManager::typeLetter();
}
void PythonQtShell_RfidSensorManager::updateAll()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("updateAll");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={""};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  RfidSensorManager::updateAll();
}
RfidSensorManager* PythonQtWrapper_RfidSensorManager::new_RfidSensorManager(QObject*  parent)
{ 
return new PythonQtShell_RfidSensorManager(parent); }

RfidSensorManager* PythonQtWrapper_RfidSensorManager::new_RfidSensorManager(QString  prefix, QObject*  parent)
{ 
return new PythonQtShell_RfidSensorManager(prefix, parent); }

void PythonQtWrapper_RfidSensorManager::dispose(RfidSensorManager* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_RfidSensorManager*)theWrappedObject)->promoted_dispose());
}

QString  PythonQtWrapper_RfidSensorManager::getSystemPrefix(RfidSensorManager* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_RfidSensorManager*)theWrappedObject)->promoted_getSystemPrefix());
}

void PythonQtWrapper_RfidSensorManager::message(RfidSensorManager* theWrappedObject, QString  m)
{
  ( theWrappedObject->message(m));
}



PythonQtShell_RouteManager::~PythonQtShell_RouteManager() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_RouteManager::Register(NamedBean*  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("Register");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "NamedBean*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&s0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  RouteManager::Register(s0);
}
void PythonQtShell_RouteManager::addPropertyChangeListener(PropertyChangeListener*  l0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("addPropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&l0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  RouteManager::addPropertyChangeListener(l0);
}
void PythonQtShell_RouteManager::childEvent(QChildEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("childEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QChildEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  RouteManager::childEvent(arg__1);
}
void PythonQtShell_RouteManager::customEvent(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("customEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  RouteManager::customEvent(arg__1);
}
void PythonQtShell_RouteManager::deregister(NamedBean*  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("deregister");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "NamedBean*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&s0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  RouteManager::deregister(s0);
}
void PythonQtShell_RouteManager::dispose()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("dispose");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={""};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  RouteManager::dispose();
}
bool  PythonQtShell_RouteManager::event(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("event");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("event", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RouteManager::event(arg__1);
}
bool  PythonQtShell_RouteManager::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("eventFilter");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QObject*" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      bool returnValue;
    void* args[3] = {NULL, (void*)&arg__1, (void*)&arg__2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("eventFilter", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RouteManager::eventFilter(arg__1, arg__2);
}
NamedBean*  PythonQtShell_RouteManager::getBeanBySystemName(QString  systemName0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getBeanBySystemName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"NamedBean*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      NamedBean* returnValue;
    void* args[2] = {NULL, (void*)&systemName0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getBeanBySystemName", methodInfo, result);
        } else {
          returnValue = *((NamedBean**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RouteManager::getBeanBySystemName(systemName0);
}
NamedBean*  PythonQtShell_RouteManager::getBeanByUserName(QString  userName0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getBeanByUserName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"NamedBean*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      NamedBean* returnValue;
    void* args[2] = {NULL, (void*)&userName0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getBeanByUserName", methodInfo, result);
        } else {
          returnValue = *((NamedBean**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RouteManager::getBeanByUserName(userName0);
}
NamedBean*  PythonQtShell_RouteManager::getNamedBean(QString  name0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNamedBean");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"NamedBean*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      NamedBean* returnValue;
    void* args[2] = {NULL, (void*)&name0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getNamedBean", methodInfo, result);
        } else {
          returnValue = *((NamedBean**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RouteManager::getNamedBean(name0);
}
QList<NamedBean* >*  PythonQtShell_RouteManager::getNamedBeanList()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNamedBeanList");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QList<NamedBean* >*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QList<NamedBean* >* returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getNamedBeanList", methodInfo, result);
        } else {
          returnValue = *((QList<NamedBean* >**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RouteManager::getNamedBeanList();
}
QStringList  PythonQtShell_RouteManager::getSystemNameArray()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemNameArray");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QStringList"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QStringList returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSystemNameArray", methodInfo, result);
        } else {
          returnValue = *((QStringList*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RouteManager::getSystemNameArray();
}
QStringList  PythonQtShell_RouteManager::getSystemNameList()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemNameList");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QStringList"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QStringList returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSystemNameList", methodInfo, result);
        } else {
          returnValue = *((QStringList*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RouteManager::getSystemNameList();
}
QString  PythonQtShell_RouteManager::getSystemPrefix()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemPrefix");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSystemPrefix", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RouteManager::getSystemPrefix();
}
int  PythonQtShell_RouteManager::getXMLOrder()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getXMLOrder");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getXMLOrder", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RouteManager::getXMLOrder();
}
QString  PythonQtShell_RouteManager::makeSystemName(QString  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("makeSystemName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      QString returnValue;
    void* args[2] = {NULL, (void*)&s0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("makeSystemName", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RouteManager::makeSystemName(s0);
}
void PythonQtShell_RouteManager::on_propertyChange(PropertyChangeEvent*  e0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("on_propertyChange");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&e0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  RouteManager::on_propertyChange(e0);
}
void PythonQtShell_RouteManager::removePropertyChangeListener(PropertyChangeListener*  l0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("removePropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&l0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  RouteManager::removePropertyChangeListener(l0);
}
void PythonQtShell_RouteManager::timerEvent(QTimerEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("timerEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QTimerEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  RouteManager::timerEvent(arg__1);
}
char  PythonQtShell_RouteManager::typeLetter()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("typeLetter");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"char"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      char returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("typeLetter", methodInfo, result);
        } else {
          returnValue = *((char*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return RouteManager::typeLetter();
}
RouteManager* PythonQtWrapper_RouteManager::new_RouteManager(QObject*  parent)
{ 
return new PythonQtShell_RouteManager(parent); }

void PythonQtWrapper_RouteManager::dispose(RouteManager* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_RouteManager*)theWrappedObject)->promoted_dispose());
}



PythonQtShell_Sensor::~PythonQtShell_Sensor() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_Sensor::addPropertyChangeListener(PropertyChangeListener*  arg__1) const
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("addPropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Sensor::addPropertyChangeListener(arg__1);
}
void PythonQtShell_Sensor::childEvent(QChildEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("childEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QChildEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Sensor::childEvent(arg__1);
}
void PythonQtShell_Sensor::customEvent(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("customEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Sensor::customEvent(arg__1);
}
void PythonQtShell_Sensor::dispose() const
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("dispose");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={""};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Sensor::dispose();
}
bool  PythonQtShell_Sensor::event(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("event");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("event", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Sensor::event(arg__1);
}
bool  PythonQtShell_Sensor::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("eventFilter");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QObject*" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      bool returnValue;
    void* args[3] = {NULL, (void*)&arg__1, (void*)&arg__2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("eventFilter", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Sensor::eventFilter(arg__1, arg__2);
}
QString  PythonQtShell_Sensor::getComment()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getComment");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getComment", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Sensor::getComment();
}
QString  PythonQtShell_Sensor::getDisplayName()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getDisplayName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getDisplayName", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Sensor::getDisplayName();
}
bool  PythonQtShell_Sensor::getInverted() const
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getInverted");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getInverted", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Sensor::getInverted();
}
int  PythonQtShell_Sensor::getKnownState() const
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getKnownState");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getKnownState", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Sensor::getKnownState();
}
QString  PythonQtShell_Sensor::getListenerRef(PropertyChangeListener*  l0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getListenerRef");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      QString returnValue;
    void* args[2] = {NULL, (void*)&l0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getListenerRef", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Sensor::getListenerRef(l0);
}
QList<QString >*  PythonQtShell_Sensor::getListenerRefs()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getListenerRefs");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QList<QString >*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QList<QString >* returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getListenerRefs", methodInfo, result);
        } else {
          returnValue = *((QList<QString >**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Sensor::getListenerRefs();
}
int  PythonQtShell_Sensor::getNumPropertyChangeListeners()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNumPropertyChangeListeners");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getNumPropertyChangeListeners", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Sensor::getNumPropertyChangeListeners();
}
QVariant  PythonQtShell_Sensor::getProperty(QString  key0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getProperty");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QVariant" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      QVariant returnValue;
    void* args[2] = {NULL, (void*)&key0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getProperty", methodInfo, result);
        } else {
          returnValue = *((QVariant*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Sensor::getProperty(key0);
}
QList<PropertyChangeListener* >*  PythonQtShell_Sensor::getPropertyChangeListeners()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getPropertyChangeListeners");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QList<PropertyChangeListener* >*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QList<PropertyChangeListener* >* returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getPropertyChangeListeners", methodInfo, result);
        } else {
          returnValue = *((QList<PropertyChangeListener* >**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Sensor::getPropertyChangeListeners();
}
QList<PropertyChangeListener* >*  PythonQtShell_Sensor::getPropertyChangeListeners(QString  name0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getPropertyChangeListeners");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QList<PropertyChangeListener* >*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      QList<PropertyChangeListener* >* returnValue;
    void* args[2] = {NULL, (void*)&name0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getPropertyChangeListeners", methodInfo, result);
        } else {
          returnValue = *((QList<PropertyChangeListener* >**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Sensor::getPropertyChangeListeners(name0);
}
QSet<QString> PythonQtShell_Sensor::getPropertyKeys()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getPropertyKeys");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QList<QString >"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QSet<QString > returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getPropertyKeys", methodInfo, result);
        } else {
          returnValue = *((QSet<QString >*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Sensor::getPropertyKeys();
}
int  PythonQtShell_Sensor::getRawState() const
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getRawState");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getRawState", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Sensor::getRawState();
}
long  PythonQtShell_Sensor::getSensorDebounceGoingActiveTimer() const
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSensorDebounceGoingActiveTimer");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"long"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      long returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSensorDebounceGoingActiveTimer", methodInfo, result);
        } else {
          returnValue = *((long*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Sensor::getSensorDebounceGoingActiveTimer();
}
long  PythonQtShell_Sensor::getSensorDebounceGoingInActiveTimer() const
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSensorDebounceGoingInActiveTimer");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"long"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      long returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSensorDebounceGoingInActiveTimer", methodInfo, result);
        } else {
          returnValue = *((long*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Sensor::getSensorDebounceGoingInActiveTimer();
}
int  PythonQtShell_Sensor::getState()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getState");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getState", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Sensor::getState();
}
QString  PythonQtShell_Sensor::getSystemName() const
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSystemName", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Sensor::getSystemName();
}
QString  PythonQtShell_Sensor::getUserName()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getUserName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getUserName", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Sensor::getUserName();
}
bool  PythonQtShell_Sensor::hashCode()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("hashCode");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("hashCode", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Sensor::hashCode();
}
void PythonQtShell_Sensor::removePropertyChangeListener(PropertyChangeListener*  arg__1) const
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("removePropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Sensor::removePropertyChangeListener(arg__1);
}
void PythonQtShell_Sensor::requestUpdateFromLayout() const
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("requestUpdateFromLayout");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={""};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Sensor::requestUpdateFromLayout();
}
void PythonQtShell_Sensor::setComment(QString  comment0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setComment");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&comment0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Sensor::setComment(comment0);
}
void PythonQtShell_Sensor::setInverted(bool  arg__1) const
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setInverted");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Sensor::setInverted(arg__1);
}
void PythonQtShell_Sensor::setKnownState(int  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setKnownState");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Sensor::setKnownState(arg__1);
}
void PythonQtShell_Sensor::setProperty(QString  key0, QVariant  value1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setProperty");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString" , "QVariant"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
    void* args[3] = {NULL, (void*)&key0, (void*)&value1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Sensor::setProperty(key0, value1);
}
void PythonQtShell_Sensor::setSensorDebounceGoingActiveTimer(long  arg__1) const
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setSensorDebounceGoingActiveTimer");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "long"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Sensor::setSensorDebounceGoingActiveTimer(arg__1);
}
void PythonQtShell_Sensor::setSensorDebounceGoingInActiveTimer(long  arg__1) const
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setSensorDebounceGoingInActiveTimer");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "long"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Sensor::setSensorDebounceGoingInActiveTimer(arg__1);
}
void PythonQtShell_Sensor::setState(int  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setState");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Sensor::setState(arg__1);
}
void PythonQtShell_Sensor::setUserName(QString  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setUserName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&s0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Sensor::setUserName(s0);
}
void PythonQtShell_Sensor::timerEvent(QTimerEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("timerEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QTimerEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Sensor::timerEvent(arg__1);
}
void PythonQtShell_Sensor::updateListenerRef(PropertyChangeListener*  l0, QString  newName1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("updateListenerRef");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
    void* args[3] = {NULL, (void*)&l0, (void*)&newName1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Sensor::updateListenerRef(l0, newName1);
}
bool  PythonQtShell_Sensor::useDefaultTimerSettings() const
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("useDefaultTimerSettings");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("useDefaultTimerSettings", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Sensor::useDefaultTimerSettings();
}
void PythonQtShell_Sensor::useDefaultTimerSettings(bool  arg__1) const
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("useDefaultTimerSettings");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Sensor::useDefaultTimerSettings(arg__1);
}
Sensor* PythonQtWrapper_Sensor::new_Sensor(QObject*  parent)
{ 
return new PythonQtShell_Sensor(parent); }

Sensor* PythonQtWrapper_Sensor::new_Sensor(QString  sysName, QObject*  parent)
{ 
return new PythonQtShell_Sensor(sysName, parent); }

Sensor* PythonQtWrapper_Sensor::new_Sensor(QString  sysName, QString  userName, QObject*  parent)
{ 
return new PythonQtShell_Sensor(sysName, userName, parent); }

void PythonQtWrapper_Sensor::addPropertyChangeListener(Sensor* theWrappedObject, PropertyChangeListener*  arg__1) const
{
  ( ((PythonQtPublicPromoter_Sensor*)theWrappedObject)->promoted_addPropertyChangeListener(arg__1));
}

void PythonQtWrapper_Sensor::dispose(Sensor* theWrappedObject) const
{
  ( ((PythonQtPublicPromoter_Sensor*)theWrappedObject)->promoted_dispose());
}

bool  PythonQtWrapper_Sensor::getInverted(Sensor* theWrappedObject) const
{
  return ( ((PythonQtPublicPromoter_Sensor*)theWrappedObject)->promoted_getInverted());
}

int  PythonQtWrapper_Sensor::getKnownState(Sensor* theWrappedObject) const
{
  return ( ((PythonQtPublicPromoter_Sensor*)theWrappedObject)->promoted_getKnownState());
}

int  PythonQtWrapper_Sensor::getRawState(Sensor* theWrappedObject) const
{
  return ( ((PythonQtPublicPromoter_Sensor*)theWrappedObject)->promoted_getRawState());
}

long  PythonQtWrapper_Sensor::getSensorDebounceGoingActiveTimer(Sensor* theWrappedObject) const
{
  return ( ((PythonQtPublicPromoter_Sensor*)theWrappedObject)->promoted_getSensorDebounceGoingActiveTimer());
}

long  PythonQtWrapper_Sensor::getSensorDebounceGoingInActiveTimer(Sensor* theWrappedObject) const
{
  return ( ((PythonQtPublicPromoter_Sensor*)theWrappedObject)->promoted_getSensorDebounceGoingInActiveTimer());
}

void PythonQtWrapper_Sensor::removePropertyChangeListener(Sensor* theWrappedObject, PropertyChangeListener*  arg__1) const
{
  ( ((PythonQtPublicPromoter_Sensor*)theWrappedObject)->promoted_removePropertyChangeListener(arg__1));
}

void PythonQtWrapper_Sensor::requestUpdateFromLayout(Sensor* theWrappedObject) const
{
  ( ((PythonQtPublicPromoter_Sensor*)theWrappedObject)->promoted_requestUpdateFromLayout());
}

void PythonQtWrapper_Sensor::setInverted(Sensor* theWrappedObject, bool  arg__1) const
{
  ( ((PythonQtPublicPromoter_Sensor*)theWrappedObject)->promoted_setInverted(arg__1));
}

void PythonQtWrapper_Sensor::setKnownState(Sensor* theWrappedObject, int  arg__1)
{
  ( ((PythonQtPublicPromoter_Sensor*)theWrappedObject)->promoted_setKnownState(arg__1));
}

void PythonQtWrapper_Sensor::setSensorDebounceGoingActiveTimer(Sensor* theWrappedObject, long  arg__1) const
{
  ( ((PythonQtPublicPromoter_Sensor*)theWrappedObject)->promoted_setSensorDebounceGoingActiveTimer(arg__1));
}

void PythonQtWrapper_Sensor::setSensorDebounceGoingInActiveTimer(Sensor* theWrappedObject, long  arg__1) const
{
  ( ((PythonQtPublicPromoter_Sensor*)theWrappedObject)->promoted_setSensorDebounceGoingInActiveTimer(arg__1));
}

bool  PythonQtWrapper_Sensor::useDefaultTimerSettings(Sensor* theWrappedObject) const
{
  return ( ((PythonQtPublicPromoter_Sensor*)theWrappedObject)->promoted_useDefaultTimerSettings());
}

void PythonQtWrapper_Sensor::useDefaultTimerSettings(Sensor* theWrappedObject, bool  arg__1) const
{
  ( ((PythonQtPublicPromoter_Sensor*)theWrappedObject)->promoted_useDefaultTimerSettings(arg__1));
}



PythonQtShell_SensorManager::~PythonQtShell_SensorManager() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SensorManager::Register(NamedBean*  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("Register");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "NamedBean*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&s0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  SensorManager::Register(s0);
}
void PythonQtShell_SensorManager::addPropertyChangeListener(PropertyChangeListener*  l0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("addPropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&l0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  SensorManager::addPropertyChangeListener(l0);
}
bool  PythonQtShell_SensorManager::allowMultipleAdditions(QString  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("allowMultipleAdditions");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("allowMultipleAdditions", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SensorManager::allowMultipleAdditions(arg__1);
}
void PythonQtShell_SensorManager::childEvent(QChildEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("childEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QChildEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  SensorManager::childEvent(arg__1);
}
QString  PythonQtShell_SensorManager::createSystemName(QString  arg__1, QString  arg__2) const
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("createSystemName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString" , "QString" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      QString returnValue;
    void* args[3] = {NULL, (void*)&arg__1, (void*)&arg__2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("createSystemName", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SensorManager::createSystemName(arg__1, arg__2);
}
void PythonQtShell_SensorManager::customEvent(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("customEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  SensorManager::customEvent(arg__1);
}
void PythonQtShell_SensorManager::deregister(NamedBean*  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("deregister");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "NamedBean*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&s0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  SensorManager::deregister(s0);
}
void PythonQtShell_SensorManager::dispose() const
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("dispose");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={""};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  SensorManager::dispose();
}
bool  PythonQtShell_SensorManager::event(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("event");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("event", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SensorManager::event(arg__1);
}
bool  PythonQtShell_SensorManager::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("eventFilter");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QObject*" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      bool returnValue;
    void* args[3] = {NULL, (void*)&arg__1, (void*)&arg__2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("eventFilter", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SensorManager::eventFilter(arg__1, arg__2);
}
NamedBean*  PythonQtShell_SensorManager::getBeanBySystemName(QString  systemName0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getBeanBySystemName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"NamedBean*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      NamedBean* returnValue;
    void* args[2] = {NULL, (void*)&systemName0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getBeanBySystemName", methodInfo, result);
        } else {
          returnValue = *((NamedBean**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SensorManager::getBeanBySystemName(systemName0);
}
NamedBean*  PythonQtShell_SensorManager::getBeanByUserName(QString  userName0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getBeanByUserName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"NamedBean*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      NamedBean* returnValue;
    void* args[2] = {NULL, (void*)&userName0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getBeanByUserName", methodInfo, result);
        } else {
          returnValue = *((NamedBean**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SensorManager::getBeanByUserName(userName0);
}
Sensor*  PythonQtShell_SensorManager::getBySystemName(QString  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getBySystemName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"Sensor*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      Sensor* returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getBySystemName", methodInfo, result);
        } else {
          returnValue = *((Sensor**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SensorManager::getBySystemName(arg__1);
}
Sensor*  PythonQtShell_SensorManager::getByUserName(QString  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getByUserName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"Sensor*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      Sensor* returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getByUserName", methodInfo, result);
        } else {
          returnValue = *((Sensor**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SensorManager::getByUserName(arg__1);
}
long  PythonQtShell_SensorManager::getDefaultSensorDebounceGoingActive()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getDefaultSensorDebounceGoingActive");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"long"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      long returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getDefaultSensorDebounceGoingActive", methodInfo, result);
        } else {
          returnValue = *((long*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SensorManager::getDefaultSensorDebounceGoingActive();
}
long  PythonQtShell_SensorManager::getDefaultSensorDebounceGoingInActive()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getDefaultSensorDebounceGoingInActive");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"long"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      long returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getDefaultSensorDebounceGoingInActive", methodInfo, result);
        } else {
          returnValue = *((long*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SensorManager::getDefaultSensorDebounceGoingInActive();
}
NamedBean*  PythonQtShell_SensorManager::getNamedBean(QString  name0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNamedBean");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"NamedBean*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      NamedBean* returnValue;
    void* args[2] = {NULL, (void*)&name0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getNamedBean", methodInfo, result);
        } else {
          returnValue = *((NamedBean**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SensorManager::getNamedBean(name0);
}
QList<NamedBean* >*  PythonQtShell_SensorManager::getNamedBeanList()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNamedBeanList");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QList<NamedBean* >*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QList<NamedBean* >* returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getNamedBeanList", methodInfo, result);
        } else {
          returnValue = *((QList<NamedBean* >**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SensorManager::getNamedBeanList();
}
QString  PythonQtShell_SensorManager::getNextValidAddress(QString  arg__1, QString  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNextValidAddress");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString" , "QString" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      QString returnValue;
    void* args[3] = {NULL, (void*)&arg__1, (void*)&arg__2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getNextValidAddress", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SensorManager::getNextValidAddress(arg__1, arg__2);
}
Sensor*  PythonQtShell_SensorManager::getSensor(QString  arg__1) const
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSensor");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"Sensor*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      Sensor* returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSensor", methodInfo, result);
        } else {
          returnValue = *((Sensor**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SensorManager::getSensor(arg__1);
}
QStringList  PythonQtShell_SensorManager::getSystemNameArray()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemNameArray");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QStringList"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QStringList returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSystemNameArray", methodInfo, result);
        } else {
          returnValue = *((QStringList*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SensorManager::getSystemNameArray();
}
QStringList  PythonQtShell_SensorManager::getSystemNameList()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemNameList");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QStringList"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QStringList returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSystemNameList", methodInfo, result);
        } else {
          returnValue = *((QStringList*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SensorManager::getSystemNameList();
}
QString  PythonQtShell_SensorManager::getSystemPrefix()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemPrefix");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSystemPrefix", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SensorManager::getSystemPrefix();
}
int  PythonQtShell_SensorManager::getXMLOrder()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getXMLOrder");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getXMLOrder", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SensorManager::getXMLOrder();
}
QString  PythonQtShell_SensorManager::makeSystemName(QString  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("makeSystemName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      QString returnValue;
    void* args[2] = {NULL, (void*)&s0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("makeSystemName", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SensorManager::makeSystemName(s0);
}
Sensor*  PythonQtShell_SensorManager::newSensor(QString  arg__1, QString  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("newSensor");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"Sensor*" , "QString" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      Sensor* returnValue;
    void* args[3] = {NULL, (void*)&arg__1, (void*)&arg__2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("newSensor", methodInfo, result);
        } else {
          returnValue = *((Sensor**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SensorManager::newSensor(arg__1, arg__2);
}
void PythonQtShell_SensorManager::on_propertyChange(PropertyChangeEvent*  e0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("on_propertyChange");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&e0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  SensorManager::on_propertyChange(e0);
}
Sensor*  PythonQtShell_SensorManager::provideSensor(QString  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("provideSensor");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"Sensor*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      Sensor* returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("provideSensor", methodInfo, result);
        } else {
          returnValue = *((Sensor**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SensorManager::provideSensor(arg__1);
}
void PythonQtShell_SensorManager::removePropertyChangeListener(PropertyChangeListener*  l0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("removePropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&l0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  SensorManager::removePropertyChangeListener(l0);
}
void PythonQtShell_SensorManager::setDefaultSensorDebounceGoingActive(long  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setDefaultSensorDebounceGoingActive");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "long"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  SensorManager::setDefaultSensorDebounceGoingActive(arg__1);
}
void PythonQtShell_SensorManager::setDefaultSensorDebounceGoingInActive(long  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setDefaultSensorDebounceGoingInActive");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "long"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  SensorManager::setDefaultSensorDebounceGoingInActive(arg__1);
}
void PythonQtShell_SensorManager::timerEvent(QTimerEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("timerEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QTimerEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  SensorManager::timerEvent(arg__1);
}
char  PythonQtShell_SensorManager::typeLetter()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("typeLetter");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"char"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      char returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("typeLetter", methodInfo, result);
        } else {
          returnValue = *((char*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SensorManager::typeLetter();
}
void PythonQtShell_SensorManager::updateAll() const
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("updateAll");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={""};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  SensorManager::updateAll();
}
SensorManager* PythonQtWrapper_SensorManager::new_SensorManager(QObject*  parent)
{ 
return new PythonQtShell_SensorManager(parent); }

bool  PythonQtWrapper_SensorManager::allowMultipleAdditions(SensorManager* theWrappedObject, QString  arg__1)
{
  return ( ((PythonQtPublicPromoter_SensorManager*)theWrappedObject)->promoted_allowMultipleAdditions(arg__1));
}

QString  PythonQtWrapper_SensorManager::createSystemName(SensorManager* theWrappedObject, QString  arg__1, QString  arg__2) const
{
  return ( ((PythonQtPublicPromoter_SensorManager*)theWrappedObject)->promoted_createSystemName(arg__1, arg__2));
}

void PythonQtWrapper_SensorManager::dispose(SensorManager* theWrappedObject) const
{
  ( ((PythonQtPublicPromoter_SensorManager*)theWrappedObject)->promoted_dispose());
}

Sensor*  PythonQtWrapper_SensorManager::getBySystemName(SensorManager* theWrappedObject, QString  arg__1)
{
  return ( ((PythonQtPublicPromoter_SensorManager*)theWrappedObject)->promoted_getBySystemName(arg__1));
}

Sensor*  PythonQtWrapper_SensorManager::getByUserName(SensorManager* theWrappedObject, QString  arg__1)
{
  return ( ((PythonQtPublicPromoter_SensorManager*)theWrappedObject)->promoted_getByUserName(arg__1));
}

long  PythonQtWrapper_SensorManager::getDefaultSensorDebounceGoingActive(SensorManager* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_SensorManager*)theWrappedObject)->promoted_getDefaultSensorDebounceGoingActive());
}

long  PythonQtWrapper_SensorManager::getDefaultSensorDebounceGoingInActive(SensorManager* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_SensorManager*)theWrappedObject)->promoted_getDefaultSensorDebounceGoingInActive());
}

QString  PythonQtWrapper_SensorManager::getNextValidAddress(SensorManager* theWrappedObject, QString  arg__1, QString  arg__2)
{
  return ( ((PythonQtPublicPromoter_SensorManager*)theWrappedObject)->promoted_getNextValidAddress(arg__1, arg__2));
}

Sensor*  PythonQtWrapper_SensorManager::getSensor(SensorManager* theWrappedObject, QString  arg__1) const
{
  return ( ((PythonQtPublicPromoter_SensorManager*)theWrappedObject)->promoted_getSensor(arg__1));
}

Sensor*  PythonQtWrapper_SensorManager::newSensor(SensorManager* theWrappedObject, QString  arg__1, QString  arg__2)
{
  return ( ((PythonQtPublicPromoter_SensorManager*)theWrappedObject)->promoted_newSensor(arg__1, arg__2));
}

Sensor*  PythonQtWrapper_SensorManager::provideSensor(SensorManager* theWrappedObject, QString  arg__1)
{
  return ( ((PythonQtPublicPromoter_SensorManager*)theWrappedObject)->promoted_provideSensor(arg__1));
}

void PythonQtWrapper_SensorManager::setDefaultSensorDebounceGoingActive(SensorManager* theWrappedObject, long  arg__1)
{
  ( ((PythonQtPublicPromoter_SensorManager*)theWrappedObject)->promoted_setDefaultSensorDebounceGoingActive(arg__1));
}

void PythonQtWrapper_SensorManager::setDefaultSensorDebounceGoingInActive(SensorManager* theWrappedObject, long  arg__1)
{
  ( ((PythonQtPublicPromoter_SensorManager*)theWrappedObject)->promoted_setDefaultSensorDebounceGoingInActive(arg__1));
}

void PythonQtWrapper_SensorManager::updateAll(SensorManager* theWrappedObject) const
{
  ( ((PythonQtPublicPromoter_SensorManager*)theWrappedObject)->promoted_updateAll());
}



PythonQtShell_ShutDownManager::~PythonQtShell_ShutDownManager() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_ShutDownManager::childEvent(QChildEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("childEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QChildEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ShutDownManager::childEvent(arg__1);
}
void PythonQtShell_ShutDownManager::customEvent(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("customEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ShutDownManager::customEvent(arg__1);
}
bool  PythonQtShell_ShutDownManager::event(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("event");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("event", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ShutDownManager::event(arg__1);
}
bool  PythonQtShell_ShutDownManager::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("eventFilter");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QObject*" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      bool returnValue;
    void* args[3] = {NULL, (void*)&arg__1, (void*)&arg__2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("eventFilter", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return ShutDownManager::eventFilter(arg__1, arg__2);
}
bool  PythonQtShell_ShutDownManager::restart()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("restart");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("restart", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return bool();
}
bool  PythonQtShell_ShutDownManager::shutdown()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("shutdown");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("shutdown", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return bool();
}
void PythonQtShell_ShutDownManager::timerEvent(QTimerEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("timerEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QTimerEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  ShutDownManager::timerEvent(arg__1);
}
ShutDownManager* PythonQtWrapper_ShutDownManager::new_ShutDownManager(QObject*  parent)
{ 
return new PythonQtShell_ShutDownManager(parent); }

bool  PythonQtWrapper_ShutDownManager::restart(ShutDownManager* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_ShutDownManager*)theWrappedObject)->promoted_restart());
}

bool  PythonQtWrapper_ShutDownManager::shutdown(ShutDownManager* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_ShutDownManager*)theWrappedObject)->promoted_shutdown());
}



PythonQtShell_Siglet::~PythonQtShell_Siglet() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_Siglet::childEvent(QChildEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("childEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QChildEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Siglet::childEvent(arg__1);
}
void PythonQtShell_Siglet::customEvent(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("customEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Siglet::customEvent(arg__1);
}
void PythonQtShell_Siglet::defineIO()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("defineIO");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={""};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Siglet::defineIO();
}
bool  PythonQtShell_Siglet::event(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("event");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("event", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Siglet::event(arg__1);
}
bool  PythonQtShell_Siglet::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("eventFilter");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QObject*" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      bool returnValue;
    void* args[3] = {NULL, (void*)&arg__1, (void*)&arg__2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("eventFilter", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Siglet::eventFilter(arg__1, arg__2);
}
bool  PythonQtShell_Siglet::handle()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("handle");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("handle", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Siglet::handle();
}
void PythonQtShell_Siglet::init()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("init");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={""};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Siglet::init();
}
void PythonQtShell_Siglet::setOutput()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setOutput");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={""};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Siglet::setOutput();
}
void PythonQtShell_Siglet::timerEvent(QTimerEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("timerEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QTimerEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Siglet::timerEvent(arg__1);
}
Siglet* PythonQtWrapper_Siglet::new_Siglet(QObject*  parent)
{ 
return new PythonQtShell_Siglet(parent); }

Siglet* PythonQtWrapper_Siglet::new_Siglet(QString  name, QObject*  parent)
{ 
return new PythonQtShell_Siglet(name, parent); }

void PythonQtWrapper_Siglet::defineIO(Siglet* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_Siglet*)theWrappedObject)->promoted_defineIO());
}

bool  PythonQtWrapper_Siglet::handle(Siglet* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Siglet*)theWrappedObject)->promoted_handle());
}

void PythonQtWrapper_Siglet::init(Siglet* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_Siglet*)theWrappedObject)->promoted_init());
}

void PythonQtWrapper_Siglet::setOutput(Siglet* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_Siglet*)theWrappedObject)->promoted_setOutput());
}



PythonQtShell_SignalHead::~PythonQtShell_SignalHead() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_SignalHead::addPropertyChangeListener(PropertyChangeListener*  l0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("addPropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&l0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  SignalHead::addPropertyChangeListener(l0);
}
void PythonQtShell_SignalHead::addPropertyChangeListener(PropertyChangeListener*  l0, QString  beanRef1, const QString  listenerRef2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("addPropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*" , "QString" , "const QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(4, argumentList);
    void* args[4] = {NULL, (void*)&l0, (void*)&beanRef1, (void*)&listenerRef2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  SignalHead::addPropertyChangeListener(l0, beanRef1, listenerRef2);
}
void PythonQtShell_SignalHead::childEvent(QChildEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("childEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QChildEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  SignalHead::childEvent(arg__1);
}
void PythonQtShell_SignalHead::customEvent(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("customEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  SignalHead::customEvent(arg__1);
}
void PythonQtShell_SignalHead::dispose()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("dispose");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={""};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  SignalHead::dispose();
}
bool  PythonQtShell_SignalHead::event(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("event");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("event", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SignalHead::event(arg__1);
}
bool  PythonQtShell_SignalHead::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("eventFilter");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QObject*" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      bool returnValue;
    void* args[3] = {NULL, (void*)&arg__1, (void*)&arg__2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("eventFilter", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SignalHead::eventFilter(arg__1, arg__2);
}
int  PythonQtShell_SignalHead::getAppearance()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getAppearance");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getAppearance", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SignalHead::getAppearance();
}
QString  PythonQtShell_SignalHead::getAppearanceName()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getAppearanceName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getAppearanceName", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SignalHead::getAppearanceName();
}
QString  PythonQtShell_SignalHead::getAppearanceName(int  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getAppearanceName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      QString returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getAppearanceName", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SignalHead::getAppearanceName(arg__1);
}
QString  PythonQtShell_SignalHead::getComment()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getComment");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getComment", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SignalHead::getComment();
}
QString  PythonQtShell_SignalHead::getDisplayName()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getDisplayName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getDisplayName", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SignalHead::getDisplayName();
}
bool  PythonQtShell_SignalHead::getHeld()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getHeld");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getHeld", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SignalHead::getHeld();
}
QString  PythonQtShell_SignalHead::getListenerRef(PropertyChangeListener*  l0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getListenerRef");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      QString returnValue;
    void* args[2] = {NULL, (void*)&l0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getListenerRef", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SignalHead::getListenerRef(l0);
}
QList<QString >*  PythonQtShell_SignalHead::getListenerRefs()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getListenerRefs");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QList<QString >*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QList<QString >* returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getListenerRefs", methodInfo, result);
        } else {
          returnValue = *((QList<QString >**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SignalHead::getListenerRefs();
}
bool  PythonQtShell_SignalHead::getLit()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getLit");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getLit", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SignalHead::getLit();
}
int  PythonQtShell_SignalHead::getNumPropertyChangeListeners()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNumPropertyChangeListeners");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getNumPropertyChangeListeners", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SignalHead::getNumPropertyChangeListeners();
}
QVariant  PythonQtShell_SignalHead::getProperty(QString  key0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getProperty");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QVariant" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      QVariant returnValue;
    void* args[2] = {NULL, (void*)&key0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getProperty", methodInfo, result);
        } else {
          returnValue = *((QVariant*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SignalHead::getProperty(key0);
}
QList<PropertyChangeListener* >*  PythonQtShell_SignalHead::getPropertyChangeListeners()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getPropertyChangeListeners");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QList<PropertyChangeListener* >*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QList<PropertyChangeListener* >* returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getPropertyChangeListeners", methodInfo, result);
        } else {
          returnValue = *((QList<PropertyChangeListener* >**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SignalHead::getPropertyChangeListeners();
}
QList<PropertyChangeListener* >*  PythonQtShell_SignalHead::getPropertyChangeListeners(QString  name0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getPropertyChangeListeners");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QList<PropertyChangeListener* >*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      QList<PropertyChangeListener* >* returnValue;
    void* args[2] = {NULL, (void*)&name0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getPropertyChangeListeners", methodInfo, result);
        } else {
          returnValue = *((QList<PropertyChangeListener* >**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SignalHead::getPropertyChangeListeners(name0);
}
QSet<QString> PythonQtShell_SignalHead::getPropertyKeys()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getPropertyKeys");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QList<QString >"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QSet<QString > returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getPropertyKeys", methodInfo, result);
        } else {
          returnValue = *((QSet<QString >*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SignalHead::getPropertyKeys();
}
int  PythonQtShell_SignalHead::getState()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getState");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getState", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SignalHead::getState();
}
QString  PythonQtShell_SignalHead::getSystemName() const
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSystemName", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SignalHead::getSystemName();
}
QString  PythonQtShell_SignalHead::getUserName()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getUserName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getUserName", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SignalHead::getUserName();
}
QVector<QString >  PythonQtShell_SignalHead::getValidStateNames()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getValidStateNames");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QVector<QString >"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QVector<QString > returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getValidStateNames", methodInfo, result);
        } else {
          returnValue = *((QVector<QString >*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SignalHead::getValidStateNames();
}
QVector<int >  PythonQtShell_SignalHead::getValidStates()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getValidStates");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QVector<int >"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QVector<int > returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getValidStates", methodInfo, result);
        } else {
          returnValue = *((QVector<int >*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SignalHead::getValidStates();
}
bool  PythonQtShell_SignalHead::hashCode()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("hashCode");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("hashCode", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return SignalHead::hashCode();
}
void PythonQtShell_SignalHead::removePropertyChangeListener(PropertyChangeListener*  l0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("removePropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&l0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  SignalHead::removePropertyChangeListener(l0);
}
void PythonQtShell_SignalHead::setAppearance(int  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setAppearance");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  SignalHead::setAppearance(arg__1);
}
void PythonQtShell_SignalHead::setComment(QString  comment0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setComment");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&comment0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  SignalHead::setComment(comment0);
}
void PythonQtShell_SignalHead::setHeld(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setHeld");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  SignalHead::setHeld(arg__1);
}
void PythonQtShell_SignalHead::setLit(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setLit");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  SignalHead::setLit(arg__1);
}
void PythonQtShell_SignalHead::setProperty(QString  key0, QVariant  value1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setProperty");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString" , "QVariant"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
    void* args[3] = {NULL, (void*)&key0, (void*)&value1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  SignalHead::setProperty(key0, value1);
}
void PythonQtShell_SignalHead::setState(int  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setState");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  SignalHead::setState(arg__1);
}
void PythonQtShell_SignalHead::setUserName(QString  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setUserName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&s0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  SignalHead::setUserName(s0);
}
void PythonQtShell_SignalHead::timerEvent(QTimerEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("timerEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QTimerEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  SignalHead::timerEvent(arg__1);
}
void PythonQtShell_SignalHead::updateListenerRef(PropertyChangeListener*  l0, QString  newName1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("updateListenerRef");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
    void* args[3] = {NULL, (void*)&l0, (void*)&newName1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  SignalHead::updateListenerRef(l0, newName1);
}
SignalHead* PythonQtWrapper_SignalHead::new_SignalHead(QObject*  parent)
{ 
return new PythonQtShell_SignalHead(parent); }

int  PythonQtWrapper_SignalHead::getAppearance(SignalHead* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_SignalHead*)theWrappedObject)->promoted_getAppearance());
}

QString  PythonQtWrapper_SignalHead::getAppearanceName(SignalHead* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_SignalHead*)theWrappedObject)->promoted_getAppearanceName());
}

QString  PythonQtWrapper_SignalHead::getAppearanceName(SignalHead* theWrappedObject, int  arg__1)
{
  return ( ((PythonQtPublicPromoter_SignalHead*)theWrappedObject)->promoted_getAppearanceName(arg__1));
}

bool  PythonQtWrapper_SignalHead::getHeld(SignalHead* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_SignalHead*)theWrappedObject)->promoted_getHeld());
}

bool  PythonQtWrapper_SignalHead::getLit(SignalHead* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_SignalHead*)theWrappedObject)->promoted_getLit());
}

QVector<QString >  PythonQtWrapper_SignalHead::getValidStateNames(SignalHead* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_SignalHead*)theWrappedObject)->promoted_getValidStateNames());
}

QVector<int >  PythonQtWrapper_SignalHead::getValidStates(SignalHead* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_SignalHead*)theWrappedObject)->promoted_getValidStates());
}

void PythonQtWrapper_SignalHead::setAppearance(SignalHead* theWrappedObject, int  arg__1)
{
  ( ((PythonQtPublicPromoter_SignalHead*)theWrappedObject)->promoted_setAppearance(arg__1));
}

void PythonQtWrapper_SignalHead::setHeld(SignalHead* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_SignalHead*)theWrappedObject)->promoted_setHeld(arg__1));
}

void PythonQtWrapper_SignalHead::setLit(SignalHead* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_SignalHead*)theWrappedObject)->promoted_setLit(arg__1));
}



PythonQtShell_Throttle::~PythonQtShell_Throttle() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_Throttle::addPropertyChangeListener(PropertyChangeListener*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("addPropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::addPropertyChangeListener(arg__1);
}
void PythonQtShell_Throttle::childEvent(QChildEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("childEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QChildEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::childEvent(arg__1);
}
void PythonQtShell_Throttle::customEvent(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("customEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::customEvent(arg__1);
}
bool  PythonQtShell_Throttle::event(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("event");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("event", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::event(arg__1);
}
bool  PythonQtShell_Throttle::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("eventFilter");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QObject*" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      bool returnValue;
    void* args[3] = {NULL, (void*)&arg__1, (void*)&arg__2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("eventFilter", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::eventFilter(arg__1, arg__2);
}
bool  PythonQtShell_Throttle::getF0()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF0");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF0", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF0();
}
bool  PythonQtShell_Throttle::getF0Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF0Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF0Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF0Momentary();
}
bool  PythonQtShell_Throttle::getF1()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF1");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF1", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF1();
}
bool  PythonQtShell_Throttle::getF10()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF10");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF10", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF10();
}
bool  PythonQtShell_Throttle::getF10Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF10Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF10Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF10Momentary();
}
bool  PythonQtShell_Throttle::getF11()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF11");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF11", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF11();
}
bool  PythonQtShell_Throttle::getF11Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF11Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF11Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF11Momentary();
}
bool  PythonQtShell_Throttle::getF12()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF12");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF12", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF12();
}
bool  PythonQtShell_Throttle::getF12Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF12Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF12Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF12Momentary();
}
bool  PythonQtShell_Throttle::getF13()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF13");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF13", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF13();
}
bool  PythonQtShell_Throttle::getF13Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF13Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF13Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF13Momentary();
}
bool  PythonQtShell_Throttle::getF14()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF14");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF14", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF14();
}
bool  PythonQtShell_Throttle::getF14Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF14Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF14Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF14Momentary();
}
bool  PythonQtShell_Throttle::getF15()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF15");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF15", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF15();
}
bool  PythonQtShell_Throttle::getF15Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF15Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF15Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF15Momentary();
}
bool  PythonQtShell_Throttle::getF16()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF16");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF16", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF16();
}
bool  PythonQtShell_Throttle::getF16Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF16Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF16Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF16Momentary();
}
bool  PythonQtShell_Throttle::getF17()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF17");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF17", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF17();
}
bool  PythonQtShell_Throttle::getF17Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF17Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF17Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF17Momentary();
}
bool  PythonQtShell_Throttle::getF18()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF18");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF18", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF18();
}
bool  PythonQtShell_Throttle::getF18Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF18Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF18Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF18Momentary();
}
bool  PythonQtShell_Throttle::getF19()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF19");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF19", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF19();
}
bool  PythonQtShell_Throttle::getF19Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF19Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF19Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF19Momentary();
}
bool  PythonQtShell_Throttle::getF1Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF1Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF1Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF1Momentary();
}
bool  PythonQtShell_Throttle::getF2()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF2");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF2", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF2();
}
bool  PythonQtShell_Throttle::getF20()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF20");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF20", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF20();
}
bool  PythonQtShell_Throttle::getF20Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF20Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF20Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF20Momentary();
}
bool  PythonQtShell_Throttle::getF21()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF21");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF21", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF21();
}
bool  PythonQtShell_Throttle::getF21Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF21Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF21Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF21Momentary();
}
bool  PythonQtShell_Throttle::getF22()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF22");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF22", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF22();
}
bool  PythonQtShell_Throttle::getF22Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF22Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF22Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF22Momentary();
}
bool  PythonQtShell_Throttle::getF23()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF23");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF23", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF23();
}
bool  PythonQtShell_Throttle::getF23Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF23Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF23Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF23Momentary();
}
bool  PythonQtShell_Throttle::getF24()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF24");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF24", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF24();
}
bool  PythonQtShell_Throttle::getF24Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF24Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF24Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF24Momentary();
}
bool  PythonQtShell_Throttle::getF25()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF25");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF25", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF25();
}
bool  PythonQtShell_Throttle::getF25Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF25Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF25Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF25Momentary();
}
bool  PythonQtShell_Throttle::getF26()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF26");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF26", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF26();
}
bool  PythonQtShell_Throttle::getF26Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF26Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF26Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF26Momentary();
}
bool  PythonQtShell_Throttle::getF27()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF27");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF27", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF27();
}
bool  PythonQtShell_Throttle::getF27Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF27Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF27Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF27Momentary();
}
bool  PythonQtShell_Throttle::getF28()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF28");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF28", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF28();
}
bool  PythonQtShell_Throttle::getF28Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF28Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF28Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF28Momentary();
}
bool  PythonQtShell_Throttle::getF2Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF2Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF2Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF2Momentary();
}
bool  PythonQtShell_Throttle::getF3()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF3");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF3", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF3();
}
bool  PythonQtShell_Throttle::getF3Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF3Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF3Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF3Momentary();
}
bool  PythonQtShell_Throttle::getF4()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF4");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF4", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF4();
}
bool  PythonQtShell_Throttle::getF4Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF4Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF4Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF4Momentary();
}
bool  PythonQtShell_Throttle::getF5()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF5");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF5", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF5();
}
bool  PythonQtShell_Throttle::getF5Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF5Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF5Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF5Momentary();
}
bool  PythonQtShell_Throttle::getF6()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF6");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF6", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF6();
}
bool  PythonQtShell_Throttle::getF6Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF6Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF6Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF6Momentary();
}
bool  PythonQtShell_Throttle::getF7()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF7");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF7", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF7();
}
bool  PythonQtShell_Throttle::getF7Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF7Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF7Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF7Momentary();
}
bool  PythonQtShell_Throttle::getF8()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF8");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF8", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF8();
}
bool  PythonQtShell_Throttle::getF8Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF8Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF8Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF8Momentary();
}
bool  PythonQtShell_Throttle::getF9()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF9");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF9", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF9();
}
bool  PythonQtShell_Throttle::getF9Momentary()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getF9Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getF9Momentary", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getF9Momentary();
}
bool  PythonQtShell_Throttle::getIsForward()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getIsForward");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getIsForward", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getIsForward();
}
QVector<PropertyChangeListener* >*  PythonQtShell_Throttle::getListeners()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getListeners");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QVector<PropertyChangeListener* >*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QVector<PropertyChangeListener* >* returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getListeners", methodInfo, result);
        } else {
          returnValue = *((QVector<PropertyChangeListener* >**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getListeners();
}
LocoAddress*  PythonQtShell_Throttle::getLocoAddress()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getLocoAddress");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"LocoAddress*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      LocoAddress* returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getLocoAddress", methodInfo, result);
        } else {
          returnValue = *((LocoAddress**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getLocoAddress();
}
float  PythonQtShell_Throttle::getSpeedSetting()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSpeedSetting");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"float"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      float returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSpeedSetting", methodInfo, result);
        } else {
          returnValue = *((float*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Throttle::getSpeedSetting();
}
void PythonQtShell_Throttle::removePropertyChangeListener(PropertyChangeListener*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("removePropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::removePropertyChangeListener(arg__1);
}
void PythonQtShell_Throttle::setF0(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF0");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF0(arg__1);
}
void PythonQtShell_Throttle::setF0Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF0Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF0Momentary(arg__1);
}
void PythonQtShell_Throttle::setF1(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF1");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF1(arg__1);
}
void PythonQtShell_Throttle::setF10(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF10");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF10(arg__1);
}
void PythonQtShell_Throttle::setF10Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF10Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF10Momentary(arg__1);
}
void PythonQtShell_Throttle::setF11(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF11");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF11(arg__1);
}
void PythonQtShell_Throttle::setF11Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF11Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF11Momentary(arg__1);
}
void PythonQtShell_Throttle::setF12(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF12");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF12(arg__1);
}
void PythonQtShell_Throttle::setF12Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF12Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF12Momentary(arg__1);
}
void PythonQtShell_Throttle::setF13(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF13");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF13(arg__1);
}
void PythonQtShell_Throttle::setF13Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF13Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF13Momentary(arg__1);
}
void PythonQtShell_Throttle::setF14(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF14");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF14(arg__1);
}
void PythonQtShell_Throttle::setF14Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF14Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF14Momentary(arg__1);
}
void PythonQtShell_Throttle::setF15(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF15");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF15(arg__1);
}
void PythonQtShell_Throttle::setF15Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF15Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF15Momentary(arg__1);
}
void PythonQtShell_Throttle::setF16(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF16");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF16(arg__1);
}
void PythonQtShell_Throttle::setF16Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF16Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF16Momentary(arg__1);
}
void PythonQtShell_Throttle::setF17(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF17");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF17(arg__1);
}
void PythonQtShell_Throttle::setF17Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF17Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF17Momentary(arg__1);
}
void PythonQtShell_Throttle::setF18(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF18");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF18(arg__1);
}
void PythonQtShell_Throttle::setF18Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF18Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF18Momentary(arg__1);
}
void PythonQtShell_Throttle::setF19(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF19");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF19(arg__1);
}
void PythonQtShell_Throttle::setF19Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF19Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF19Momentary(arg__1);
}
void PythonQtShell_Throttle::setF1Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF1Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF1Momentary(arg__1);
}
void PythonQtShell_Throttle::setF2(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF2");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF2(arg__1);
}
void PythonQtShell_Throttle::setF20(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF20");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF20(arg__1);
}
void PythonQtShell_Throttle::setF20Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF20Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF20Momentary(arg__1);
}
void PythonQtShell_Throttle::setF21(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF21");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF21(arg__1);
}
void PythonQtShell_Throttle::setF21Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF21Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF21Momentary(arg__1);
}
void PythonQtShell_Throttle::setF22(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF22");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF22(arg__1);
}
void PythonQtShell_Throttle::setF22Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF22Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF22Momentary(arg__1);
}
void PythonQtShell_Throttle::setF23(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF23");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF23(arg__1);
}
void PythonQtShell_Throttle::setF23Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF23Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF23Momentary(arg__1);
}
void PythonQtShell_Throttle::setF24(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF24");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF24(arg__1);
}
void PythonQtShell_Throttle::setF24Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF24Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF24Momentary(arg__1);
}
void PythonQtShell_Throttle::setF25(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF25");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF25(arg__1);
}
void PythonQtShell_Throttle::setF25Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF25Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF25Momentary(arg__1);
}
void PythonQtShell_Throttle::setF26(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF26");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF26(arg__1);
}
void PythonQtShell_Throttle::setF26Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF26Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF26Momentary(arg__1);
}
void PythonQtShell_Throttle::setF27(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF27");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF27(arg__1);
}
void PythonQtShell_Throttle::setF27Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF27Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF27Momentary(arg__1);
}
void PythonQtShell_Throttle::setF28(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF28");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF28(arg__1);
}
void PythonQtShell_Throttle::setF28Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF28Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF28Momentary(arg__1);
}
void PythonQtShell_Throttle::setF2Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF2Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF2Momentary(arg__1);
}
void PythonQtShell_Throttle::setF3(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF3");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF3(arg__1);
}
void PythonQtShell_Throttle::setF3Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF3Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF3Momentary(arg__1);
}
void PythonQtShell_Throttle::setF4(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF4");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF4(arg__1);
}
void PythonQtShell_Throttle::setF4Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF4Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF4Momentary(arg__1);
}
void PythonQtShell_Throttle::setF5(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF5");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF5(arg__1);
}
void PythonQtShell_Throttle::setF5Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF5Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF5Momentary(arg__1);
}
void PythonQtShell_Throttle::setF6(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF6");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF6(arg__1);
}
void PythonQtShell_Throttle::setF6Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF6Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF6Momentary(arg__1);
}
void PythonQtShell_Throttle::setF7(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF7");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF7(arg__1);
}
void PythonQtShell_Throttle::setF7Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF7Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF7Momentary(arg__1);
}
void PythonQtShell_Throttle::setF8(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF8");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF8(arg__1);
}
void PythonQtShell_Throttle::setF8Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF8Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF8Momentary(arg__1);
}
void PythonQtShell_Throttle::setF9(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF9");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF9(arg__1);
}
void PythonQtShell_Throttle::setF9Momentary(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setF9Momentary");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setF9Momentary(arg__1);
}
void PythonQtShell_Throttle::setIsForward(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setIsForward");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setIsForward(arg__1);
}
void PythonQtShell_Throttle::setSpeedSetting(float  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setSpeedSetting");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "float"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::setSpeedSetting(arg__1);
}
void PythonQtShell_Throttle::timerEvent(QTimerEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("timerEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QTimerEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Throttle::timerEvent(arg__1);
}
Throttle* PythonQtWrapper_Throttle::new_Throttle()
{ 
return new PythonQtShell_Throttle(); }

void PythonQtWrapper_Throttle::addPropertyChangeListener(Throttle* theWrappedObject, PropertyChangeListener*  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_addPropertyChangeListener(arg__1));
}

bool  PythonQtWrapper_Throttle::getF0(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF0());
}

bool  PythonQtWrapper_Throttle::getF0Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF0Momentary());
}

bool  PythonQtWrapper_Throttle::getF1(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF1());
}

bool  PythonQtWrapper_Throttle::getF10(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF10());
}

bool  PythonQtWrapper_Throttle::getF10Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF10Momentary());
}

bool  PythonQtWrapper_Throttle::getF11(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF11());
}

bool  PythonQtWrapper_Throttle::getF11Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF11Momentary());
}

bool  PythonQtWrapper_Throttle::getF12(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF12());
}

bool  PythonQtWrapper_Throttle::getF12Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF12Momentary());
}

bool  PythonQtWrapper_Throttle::getF13(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF13());
}

bool  PythonQtWrapper_Throttle::getF13Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF13Momentary());
}

bool  PythonQtWrapper_Throttle::getF14(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF14());
}

bool  PythonQtWrapper_Throttle::getF14Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF14Momentary());
}

bool  PythonQtWrapper_Throttle::getF15(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF15());
}

bool  PythonQtWrapper_Throttle::getF15Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF15Momentary());
}

bool  PythonQtWrapper_Throttle::getF16(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF16());
}

bool  PythonQtWrapper_Throttle::getF16Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF16Momentary());
}

bool  PythonQtWrapper_Throttle::getF17(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF17());
}

bool  PythonQtWrapper_Throttle::getF17Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF17Momentary());
}

bool  PythonQtWrapper_Throttle::getF18(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF18());
}

bool  PythonQtWrapper_Throttle::getF18Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF18Momentary());
}

bool  PythonQtWrapper_Throttle::getF19(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF19());
}

bool  PythonQtWrapper_Throttle::getF19Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF19Momentary());
}

bool  PythonQtWrapper_Throttle::getF1Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF1Momentary());
}

bool  PythonQtWrapper_Throttle::getF2(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF2());
}

bool  PythonQtWrapper_Throttle::getF20(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF20());
}

bool  PythonQtWrapper_Throttle::getF20Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF20Momentary());
}

bool  PythonQtWrapper_Throttle::getF21(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF21());
}

bool  PythonQtWrapper_Throttle::getF21Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF21Momentary());
}

bool  PythonQtWrapper_Throttle::getF22(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF22());
}

bool  PythonQtWrapper_Throttle::getF22Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF22Momentary());
}

bool  PythonQtWrapper_Throttle::getF23(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF23());
}

bool  PythonQtWrapper_Throttle::getF23Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF23Momentary());
}

bool  PythonQtWrapper_Throttle::getF24(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF24());
}

bool  PythonQtWrapper_Throttle::getF24Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF24Momentary());
}

bool  PythonQtWrapper_Throttle::getF25(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF25());
}

bool  PythonQtWrapper_Throttle::getF25Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF25Momentary());
}

bool  PythonQtWrapper_Throttle::getF26(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF26());
}

bool  PythonQtWrapper_Throttle::getF26Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF26Momentary());
}

bool  PythonQtWrapper_Throttle::getF27(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF27());
}

bool  PythonQtWrapper_Throttle::getF27Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF27Momentary());
}

bool  PythonQtWrapper_Throttle::getF28(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF28());
}

bool  PythonQtWrapper_Throttle::getF28Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF28Momentary());
}

bool  PythonQtWrapper_Throttle::getF2Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF2Momentary());
}

bool  PythonQtWrapper_Throttle::getF3(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF3());
}

bool  PythonQtWrapper_Throttle::getF3Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF3Momentary());
}

bool  PythonQtWrapper_Throttle::getF4(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF4());
}

bool  PythonQtWrapper_Throttle::getF4Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF4Momentary());
}

bool  PythonQtWrapper_Throttle::getF5(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF5());
}

bool  PythonQtWrapper_Throttle::getF5Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF5Momentary());
}

bool  PythonQtWrapper_Throttle::getF6(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF6());
}

bool  PythonQtWrapper_Throttle::getF6Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF6Momentary());
}

bool  PythonQtWrapper_Throttle::getF7(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF7());
}

bool  PythonQtWrapper_Throttle::getF7Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF7Momentary());
}

bool  PythonQtWrapper_Throttle::getF8(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF8());
}

bool  PythonQtWrapper_Throttle::getF8Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF8Momentary());
}

bool  PythonQtWrapper_Throttle::getF9(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF9());
}

bool  PythonQtWrapper_Throttle::getF9Momentary(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getF9Momentary());
}

bool  PythonQtWrapper_Throttle::getIsForward(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getIsForward());
}

QVector<PropertyChangeListener* >*  PythonQtWrapper_Throttle::getListeners(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getListeners());
}

LocoAddress*  PythonQtWrapper_Throttle::getLocoAddress(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getLocoAddress());
}

float  PythonQtWrapper_Throttle::getSpeedSetting(Throttle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_getSpeedSetting());
}

void PythonQtWrapper_Throttle::removePropertyChangeListener(Throttle* theWrappedObject, PropertyChangeListener*  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_removePropertyChangeListener(arg__1));
}

void PythonQtWrapper_Throttle::setF0(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF0(arg__1));
}

void PythonQtWrapper_Throttle::setF0Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF0Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setF1(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF1(arg__1));
}

void PythonQtWrapper_Throttle::setF10(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF10(arg__1));
}

void PythonQtWrapper_Throttle::setF10Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF10Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setF11(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF11(arg__1));
}

void PythonQtWrapper_Throttle::setF11Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF11Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setF12(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF12(arg__1));
}

void PythonQtWrapper_Throttle::setF12Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF12Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setF13(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF13(arg__1));
}

void PythonQtWrapper_Throttle::setF13Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF13Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setF14(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF14(arg__1));
}

void PythonQtWrapper_Throttle::setF14Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF14Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setF15(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF15(arg__1));
}

void PythonQtWrapper_Throttle::setF15Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF15Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setF16(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF16(arg__1));
}

void PythonQtWrapper_Throttle::setF16Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF16Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setF17(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF17(arg__1));
}

void PythonQtWrapper_Throttle::setF17Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF17Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setF18(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF18(arg__1));
}

void PythonQtWrapper_Throttle::setF18Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF18Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setF19(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF19(arg__1));
}

void PythonQtWrapper_Throttle::setF19Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF19Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setF1Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF1Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setF2(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF2(arg__1));
}

void PythonQtWrapper_Throttle::setF20(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF20(arg__1));
}

void PythonQtWrapper_Throttle::setF20Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF20Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setF21(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF21(arg__1));
}

void PythonQtWrapper_Throttle::setF21Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF21Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setF22(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF22(arg__1));
}

void PythonQtWrapper_Throttle::setF22Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF22Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setF23(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF23(arg__1));
}

void PythonQtWrapper_Throttle::setF23Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF23Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setF24(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF24(arg__1));
}

void PythonQtWrapper_Throttle::setF24Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF24Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setF25(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF25(arg__1));
}

void PythonQtWrapper_Throttle::setF25Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF25Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setF26(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF26(arg__1));
}

void PythonQtWrapper_Throttle::setF26Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF26Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setF27(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF27(arg__1));
}

void PythonQtWrapper_Throttle::setF27Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF27Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setF28(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF28(arg__1));
}

void PythonQtWrapper_Throttle::setF28Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF28Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setF2Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF2Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setF3(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF3(arg__1));
}

void PythonQtWrapper_Throttle::setF3Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF3Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setF4(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF4(arg__1));
}

void PythonQtWrapper_Throttle::setF4Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF4Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setF5(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF5(arg__1));
}

void PythonQtWrapper_Throttle::setF5Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF5Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setF6(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF6(arg__1));
}

void PythonQtWrapper_Throttle::setF6Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF6Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setF7(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF7(arg__1));
}

void PythonQtWrapper_Throttle::setF7Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF7Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setF8(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF8(arg__1));
}

void PythonQtWrapper_Throttle::setF8Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF8Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setF9(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF9(arg__1));
}

void PythonQtWrapper_Throttle::setF9Momentary(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setF9Momentary(arg__1));
}

void PythonQtWrapper_Throttle::setIsForward(Throttle* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setIsForward(arg__1));
}

void PythonQtWrapper_Throttle::setSpeedSetting(Throttle* theWrappedObject, float  arg__1)
{
  ( ((PythonQtPublicPromoter_Throttle*)theWrappedObject)->promoted_setSpeedSetting(arg__1));
}



PythonQtShell_Turnout::~PythonQtShell_Turnout() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_Turnout::addPropertyChangeListener(PropertyChangeListener*  l0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("addPropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&l0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::addPropertyChangeListener(l0);
}
void PythonQtShell_Turnout::addPropertyChangeListener(PropertyChangeListener*  l0, QString  beanRef1, const QString  listenerRef2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("addPropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*" , "QString" , "const QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(4, argumentList);
    void* args[4] = {NULL, (void*)&l0, (void*)&beanRef1, (void*)&listenerRef2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::addPropertyChangeListener(l0, beanRef1, listenerRef2);
}
bool  PythonQtShell_Turnout::canInvert() const
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("canInvert");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("canInvert", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::canInvert();
}
bool  PythonQtShell_Turnout::canLock(int  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("canLock");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("canLock", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::canLock(arg__1);
}
void PythonQtShell_Turnout::childEvent(QChildEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("childEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QChildEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::childEvent(arg__1);
}
void PythonQtShell_Turnout::customEvent(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("customEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::customEvent(arg__1);
}
void PythonQtShell_Turnout::dispose()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("dispose");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={""};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::dispose();
}
void PythonQtShell_Turnout::enableLockOperation(int  arg__1, bool  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("enableLockOperation");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
    void* args[3] = {NULL, (void*)&arg__1, (void*)&arg__2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::enableLockOperation(arg__1, arg__2);
}
bool  PythonQtShell_Turnout::event(QEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("event");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("event", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::event(arg__1);
}
bool  PythonQtShell_Turnout::eventFilter(QObject*  arg__1, QEvent*  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("eventFilter");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QObject*" , "QEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      bool returnValue;
    void* args[3] = {NULL, (void*)&arg__1, (void*)&arg__2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("eventFilter", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::eventFilter(arg__1, arg__2);
}
int  PythonQtShell_Turnout::getCommandedState()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getCommandedState");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getCommandedState", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getCommandedState();
}
QString  PythonQtShell_Turnout::getComment()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getComment");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getComment", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getComment();
}
int  PythonQtShell_Turnout::getControlType()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getControlType");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getControlType", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getControlType();
}
QString  PythonQtShell_Turnout::getDecoderName()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getDecoderName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getDecoderName", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getDecoderName();
}
QString  PythonQtShell_Turnout::getDisplayName()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getDisplayName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getDisplayName", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getDisplayName();
}
float  PythonQtShell_Turnout::getDivergingLimit()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getDivergingLimit");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"float"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      float returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getDivergingLimit", methodInfo, result);
        } else {
          returnValue = *((float*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getDivergingLimit();
}
QString  PythonQtShell_Turnout::getDivergingSpeed()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getDivergingSpeed");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getDivergingSpeed", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getDivergingSpeed();
}
int  PythonQtShell_Turnout::getFeedbackMode()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getFeedbackMode");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getFeedbackMode", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getFeedbackMode();
}
QString  PythonQtShell_Turnout::getFeedbackModeName()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getFeedbackModeName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getFeedbackModeName", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getFeedbackModeName();
}
Sensor*  PythonQtShell_Turnout::getFirstSensor()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getFirstSensor");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"Sensor*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      Sensor* returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getFirstSensor", methodInfo, result);
        } else {
          returnValue = *((Sensor**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getFirstSensor();
}
bool  PythonQtShell_Turnout::getInhibitOperation()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getInhibitOperation");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getInhibitOperation", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getInhibitOperation();
}
bool  PythonQtShell_Turnout::getInverted()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getInverted");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getInverted", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getInverted();
}
int  PythonQtShell_Turnout::getKnownState()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getKnownState");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getKnownState", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getKnownState();
}
QString  PythonQtShell_Turnout::getListenerRef(PropertyChangeListener*  l0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getListenerRef");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      QString returnValue;
    void* args[2] = {NULL, (void*)&l0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getListenerRef", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getListenerRef(l0);
}
QList<QString >*  PythonQtShell_Turnout::getListenerRefs()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getListenerRefs");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QList<QString >*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QList<QString >* returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getListenerRefs", methodInfo, result);
        } else {
          returnValue = *((QList<QString >**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getListenerRefs();
}
bool  PythonQtShell_Turnout::getLocked(int  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getLocked");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getLocked", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getLocked(arg__1);
}
int  PythonQtShell_Turnout::getNumPropertyChangeListeners()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNumPropertyChangeListeners");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getNumPropertyChangeListeners", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getNumPropertyChangeListeners();
}
int  PythonQtShell_Turnout::getNumberOutputBits()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNumberOutputBits");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getNumberOutputBits", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getNumberOutputBits();
}
QVariant  PythonQtShell_Turnout::getProperty(QString  key0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getProperty");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QVariant" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      QVariant returnValue;
    void* args[2] = {NULL, (void*)&key0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getProperty", methodInfo, result);
        } else {
          returnValue = *((QVariant*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getProperty(key0);
}
QList<PropertyChangeListener* >*  PythonQtShell_Turnout::getPropertyChangeListeners()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getPropertyChangeListeners");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QList<PropertyChangeListener* >*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QList<PropertyChangeListener* >* returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getPropertyChangeListeners", methodInfo, result);
        } else {
          returnValue = *((QList<PropertyChangeListener* >**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getPropertyChangeListeners();
}
QList<PropertyChangeListener* >*  PythonQtShell_Turnout::getPropertyChangeListeners(QString  name0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getPropertyChangeListeners");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QList<PropertyChangeListener* >*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      QList<PropertyChangeListener* >* returnValue;
    void* args[2] = {NULL, (void*)&name0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getPropertyChangeListeners", methodInfo, result);
        } else {
          returnValue = *((QList<PropertyChangeListener* >**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getPropertyChangeListeners(name0);
}
QSet<QString> PythonQtShell_Turnout::getPropertyKeys()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getPropertyKeys");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QList<QString >"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QSet<QString > returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getPropertyKeys", methodInfo, result);
        } else {
          returnValue = *((QSet<QString >*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getPropertyKeys();
}
bool  PythonQtShell_Turnout::getReportLocked()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getReportLocked");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getReportLocked", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getReportLocked();
}
Sensor*  PythonQtShell_Turnout::getSecondSensor()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSecondSensor");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"Sensor*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      Sensor* returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSecondSensor", methodInfo, result);
        } else {
          returnValue = *((Sensor**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getSecondSensor();
}
int  PythonQtShell_Turnout::getState()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getState");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getState", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getState();
}
float  PythonQtShell_Turnout::getStraightLimit()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getStraightLimit");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"float"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      float returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getStraightLimit", methodInfo, result);
        } else {
          returnValue = *((float*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getStraightLimit();
}
QString  PythonQtShell_Turnout::getStraightSpeed()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getStraightSpeed");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getStraightSpeed", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getStraightSpeed();
}
QString  PythonQtShell_Turnout::getSystemName() const
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSystemName", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getSystemName();
}
QString  PythonQtShell_Turnout::getUserName()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getUserName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QString returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getUserName", methodInfo, result);
        } else {
          returnValue = *((QString*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getUserName();
}
QStringList  PythonQtShell_Turnout::getValidDecoderNames()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getValidDecoderNames");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QStringList"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QStringList returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getValidDecoderNames", methodInfo, result);
        } else {
          returnValue = *((QStringList*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getValidDecoderNames();
}
QStringList  PythonQtShell_Turnout::getValidFeedbackNames()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getValidFeedbackNames");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QStringList"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QStringList returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getValidFeedbackNames", methodInfo, result);
        } else {
          returnValue = *((QStringList*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getValidFeedbackNames();
}
int  PythonQtShell_Turnout::getValidFeedbackTypes()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getValidFeedbackTypes");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      int returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getValidFeedbackTypes", methodInfo, result);
        } else {
          returnValue = *((int*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::getValidFeedbackTypes();
}
bool  PythonQtShell_Turnout::hashCode()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("hashCode");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("hashCode", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::hashCode();
}
bool  PythonQtShell_Turnout::isConsistentState()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("isConsistentState");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      bool returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("isConsistentState", methodInfo, result);
        } else {
          returnValue = *((bool*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Turnout::isConsistentState();
}
void PythonQtShell_Turnout::provideFirstFeedbackSensor(QString  arg__1) throw (JmriException)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("provideFirstFeedbackSensor");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::provideFirstFeedbackSensor(arg__1);
}
void PythonQtShell_Turnout::provideSecondFeedbackSensor(QString  arg__1) throw (JmriException)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("provideSecondFeedbackSensor");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::provideSecondFeedbackSensor(arg__1);
}
void PythonQtShell_Turnout::removePropertyChangeListener(PropertyChangeListener*  l0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("removePropertyChangeListener");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&l0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::removePropertyChangeListener(l0);
}
void PythonQtShell_Turnout::setBinaryOutput(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setBinaryOutput");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::setBinaryOutput(arg__1);
}
void PythonQtShell_Turnout::setCommandedState(int  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setCommandedState");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::setCommandedState(arg__1);
}
void PythonQtShell_Turnout::setComment(QString  comment0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setComment");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&comment0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::setComment(comment0);
}
void PythonQtShell_Turnout::setControlType(int  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setControlType");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::setControlType(arg__1);
}
void PythonQtShell_Turnout::setDecoderName(QString  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setDecoderName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::setDecoderName(arg__1);
}
void PythonQtShell_Turnout::setDivergingSpeed(QString  arg__1) const throw (JmriException)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setDivergingSpeed");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::setDivergingSpeed(arg__1);
}
void PythonQtShell_Turnout::setFeedbackMode(QString  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setFeedbackMode");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::setFeedbackMode(arg__1);
}
void PythonQtShell_Turnout::setFeedbackMode(int  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setFeedbackMode");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::setFeedbackMode(arg__1);
}
void PythonQtShell_Turnout::setInhibitOperation(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setInhibitOperation");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::setInhibitOperation(arg__1);
}
void PythonQtShell_Turnout::setInitialKnownStateFromFeedback()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setInitialKnownStateFromFeedback");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={""};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::setInitialKnownStateFromFeedback();
}
void PythonQtShell_Turnout::setInverted(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setInverted");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::setInverted(arg__1);
}
void PythonQtShell_Turnout::setLocked(int  arg__1, bool  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setLocked");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
    void* args[3] = {NULL, (void*)&arg__1, (void*)&arg__2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::setLocked(arg__1, arg__2);
}
void PythonQtShell_Turnout::setNumberOutputBits(int  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setNumberOutputBits");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::setNumberOutputBits(arg__1);
}
void PythonQtShell_Turnout::setProperty(QString  key0, QVariant  value1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setProperty");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString" , "QVariant"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
    void* args[3] = {NULL, (void*)&key0, (void*)&value1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::setProperty(key0, value1);
}
void PythonQtShell_Turnout::setReportLocked(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setReportLocked");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::setReportLocked(arg__1);
}
void PythonQtShell_Turnout::setState(int  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setState");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::setState(arg__1);
}
void PythonQtShell_Turnout::setStraightSpeed(QString  arg__1) const throw (JmriException)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setStraightSpeed");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::setStraightSpeed(arg__1);
}
void PythonQtShell_Turnout::setUserName(QString  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setUserName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&s0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::setUserName(s0);
}
void PythonQtShell_Turnout::timerEvent(QTimerEvent*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("timerEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QTimerEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::timerEvent(arg__1);
}
void PythonQtShell_Turnout::updateListenerRef(PropertyChangeListener*  l0, QString  newName1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("updateListenerRef");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeListener*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
    void* args[3] = {NULL, (void*)&l0, (void*)&newName1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Turnout::updateListenerRef(l0, newName1);
}
Turnout* PythonQtWrapper_Turnout::new_Turnout(QObject*  parent)
{ 
return new PythonQtShell_Turnout(parent); }

Turnout* PythonQtWrapper_Turnout::new_Turnout(QString  sysName, QObject*  parent)
{ 
return new PythonQtShell_Turnout(sysName, parent); }

Turnout* PythonQtWrapper_Turnout::new_Turnout(QString  sysName, QString  userName, QObject*  parent)
{ 
return new PythonQtShell_Turnout(sysName, userName, parent); }

bool  PythonQtWrapper_Turnout::canInvert(Turnout* theWrappedObject) const
{
  return ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_canInvert());
}

bool  PythonQtWrapper_Turnout::canLock(Turnout* theWrappedObject, int  arg__1)
{
  return ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_canLock(arg__1));
}

void PythonQtWrapper_Turnout::enableLockOperation(Turnout* theWrappedObject, int  arg__1, bool  arg__2)
{
  ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_enableLockOperation(arg__1, arg__2));
}

int  PythonQtWrapper_Turnout::getCommandedState(Turnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_getCommandedState());
}

int  PythonQtWrapper_Turnout::getControlType(Turnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_getControlType());
}

QString  PythonQtWrapper_Turnout::getDecoderName(Turnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_getDecoderName());
}

float  PythonQtWrapper_Turnout::getDivergingLimit(Turnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_getDivergingLimit());
}

QString  PythonQtWrapper_Turnout::getDivergingSpeed(Turnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_getDivergingSpeed());
}

int  PythonQtWrapper_Turnout::getFeedbackMode(Turnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_getFeedbackMode());
}

QString  PythonQtWrapper_Turnout::getFeedbackModeName(Turnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_getFeedbackModeName());
}

Sensor*  PythonQtWrapper_Turnout::getFirstSensor(Turnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_getFirstSensor());
}

bool  PythonQtWrapper_Turnout::getInhibitOperation(Turnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_getInhibitOperation());
}

bool  PythonQtWrapper_Turnout::getInverted(Turnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_getInverted());
}

int  PythonQtWrapper_Turnout::getKnownState(Turnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_getKnownState());
}

bool  PythonQtWrapper_Turnout::getLocked(Turnout* theWrappedObject, int  arg__1)
{
  return ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_getLocked(arg__1));
}

int  PythonQtWrapper_Turnout::getNumberOutputBits(Turnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_getNumberOutputBits());
}

bool  PythonQtWrapper_Turnout::getReportLocked(Turnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_getReportLocked());
}

Sensor*  PythonQtWrapper_Turnout::getSecondSensor(Turnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_getSecondSensor());
}

float  PythonQtWrapper_Turnout::getStraightLimit(Turnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_getStraightLimit());
}

QString  PythonQtWrapper_Turnout::getStraightSpeed(Turnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_getStraightSpeed());
}

QStringList  PythonQtWrapper_Turnout::getValidDecoderNames(Turnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_getValidDecoderNames());
}

QStringList  PythonQtWrapper_Turnout::getValidFeedbackNames(Turnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_getValidFeedbackNames());
}

int  PythonQtWrapper_Turnout::getValidFeedbackTypes(Turnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_getValidFeedbackTypes());
}

bool  PythonQtWrapper_Turnout::isConsistentState(Turnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_isConsistentState());
}

void PythonQtWrapper_Turnout::provideFirstFeedbackSensor(Turnout* theWrappedObject, QString  arg__1)
{
  ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_provideFirstFeedbackSensor(arg__1));
}

void PythonQtWrapper_Turnout::provideSecondFeedbackSensor(Turnout* theWrappedObject, QString  arg__1)
{
  ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_provideSecondFeedbackSensor(arg__1));
}

void PythonQtWrapper_Turnout::setBinaryOutput(Turnout* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_setBinaryOutput(arg__1));
}

void PythonQtWrapper_Turnout::setCommandedState(Turnout* theWrappedObject, int  arg__1)
{
  ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_setCommandedState(arg__1));
}

void PythonQtWrapper_Turnout::setControlType(Turnout* theWrappedObject, int  arg__1)
{
  ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_setControlType(arg__1));
}

void PythonQtWrapper_Turnout::setDecoderName(Turnout* theWrappedObject, QString  arg__1)
{
  ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_setDecoderName(arg__1));
}

void PythonQtWrapper_Turnout::setDivergingSpeed(Turnout* theWrappedObject, QString  arg__1) const
{
  ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_setDivergingSpeed(arg__1));
}

void PythonQtWrapper_Turnout::setFeedbackMode(Turnout* theWrappedObject, QString  arg__1)
{
  ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_setFeedbackMode(arg__1));
}

void PythonQtWrapper_Turnout::setFeedbackMode(Turnout* theWrappedObject, int  arg__1)
{
  ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_setFeedbackMode(arg__1));
}

void PythonQtWrapper_Turnout::setInhibitOperation(Turnout* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_setInhibitOperation(arg__1));
}

void PythonQtWrapper_Turnout::setInitialKnownStateFromFeedback(Turnout* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_setInitialKnownStateFromFeedback());
}

void PythonQtWrapper_Turnout::setInverted(Turnout* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_setInverted(arg__1));
}

void PythonQtWrapper_Turnout::setLocked(Turnout* theWrappedObject, int  arg__1, bool  arg__2)
{
  ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_setLocked(arg__1, arg__2));
}

void PythonQtWrapper_Turnout::setNumberOutputBits(Turnout* theWrappedObject, int  arg__1)
{
  ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_setNumberOutputBits(arg__1));
}

void PythonQtWrapper_Turnout::setReportLocked(Turnout* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_setReportLocked(arg__1));
}

void PythonQtWrapper_Turnout::setStraightSpeed(Turnout* theWrappedObject, QString  arg__1) const
{
  ( ((PythonQtPublicPromoter_Turnout*)theWrappedObject)->promoted_setStraightSpeed(arg__1));
}


