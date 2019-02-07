#include "jmri0.h"
#include <PythonQtConversion.h>
#include <PythonQtMethodInfo.h>
#include <PythonQtSignalReceiver.h>
#include <QVariant>
#include <abstractmanager.h>
#include <abstractproxymanager.h>
#include <audio.h>
#include <audiobuffer.h>
#include <dcclocoaddress.h>
#include <dccthrottle.h>
#include <defaultlogixmanager.h>
#include <editor.h>
#include <jframe.h>
#include <jmrijframe.h>
#include <layoutblockmanager.h>
#include <lnportcontroller.h>
#include <lntrafficcontroller.h>
#include <locoaddress.h>
#include <loconetmessage.h>
#include <positionable.h>
#include <sensor.h>
#include <turnout.h>

PythonQtShell_AbstractAutomaton::~PythonQtShell_AbstractAutomaton() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
bool  PythonQtShell_AbstractAutomaton::handle()
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
  return AbstractAutomaton::handle();
}
void PythonQtShell_AbstractAutomaton::init()
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
  AbstractAutomaton::init();
}
AbstractAutomaton* PythonQtWrapper_AbstractAutomaton::new_AbstractAutomaton(QObject*  parent)
{ 
return new PythonQtShell_AbstractAutomaton(parent); }

AbstractAutomaton* PythonQtWrapper_AbstractAutomaton::new_AbstractAutomaton(QString  name, QObject*  parent)
{ 
return new PythonQtShell_AbstractAutomaton(name, parent); }

void PythonQtWrapper_AbstractAutomaton::defaultName(AbstractAutomaton* theWrappedObject)
{
  ( theWrappedObject->defaultName());
}

void PythonQtWrapper_AbstractAutomaton::done(AbstractAutomaton* theWrappedObject)
{
  ( theWrappedObject->done());
}

int  PythonQtWrapper_AbstractAutomaton::getCount(AbstractAutomaton* theWrappedObject)
{
  return ( theWrappedObject->getCount());
}

QString  PythonQtWrapper_AbstractAutomaton::getName(AbstractAutomaton* theWrappedObject)
{
  return ( theWrappedObject->getName());
}

DccThrottle*  PythonQtWrapper_AbstractAutomaton::getThrottle(AbstractAutomaton* theWrappedObject, int  address, bool  longAddress)
{
  return ( theWrappedObject->getThrottle(address, longAddress));
}

bool  PythonQtWrapper_AbstractAutomaton::handle(AbstractAutomaton* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractAutomaton*)theWrappedObject)->promoted_handle());
}

void PythonQtWrapper_AbstractAutomaton::init(AbstractAutomaton* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_AbstractAutomaton*)theWrappedObject)->promoted_init());
}

void PythonQtWrapper_AbstractAutomaton::notifyAll(AbstractAutomaton* theWrappedObject)
{
  ( theWrappedObject->notifyAll());
}

void PythonQtWrapper_AbstractAutomaton::notifyFailedThrottleRequest(AbstractAutomaton* theWrappedObject, DccLocoAddress*  address, QString  reason)
{
  ( theWrappedObject->notifyFailedThrottleRequest(address, reason));
}

void PythonQtWrapper_AbstractAutomaton::notifyThrottleFound(AbstractAutomaton* theWrappedObject, DccThrottle*  t)
{
  ( theWrappedObject->notifyThrottleFound(t));
}

int  PythonQtWrapper_AbstractAutomaton::readServiceModeCV(AbstractAutomaton* theWrappedObject, int  CV)
{
  return ( theWrappedObject->readServiceModeCV(CV));
}

void PythonQtWrapper_AbstractAutomaton::setName(AbstractAutomaton* theWrappedObject, QString  name)
{
  ( theWrappedObject->setName(name));
}

void PythonQtWrapper_AbstractAutomaton::setTerminateSensor(AbstractAutomaton* theWrappedObject, Sensor*  ts)
{
  ( theWrappedObject->setTerminateSensor(ts));
}

void PythonQtWrapper_AbstractAutomaton::setTurnouts(AbstractAutomaton* theWrappedObject, QList<Turnout* >  closed, QList<Turnout* >  thrown)
{
  ( theWrappedObject->setTurnouts(closed, thrown));
}

void PythonQtWrapper_AbstractAutomaton::start(AbstractAutomaton* theWrappedObject, bool  bRunInThread)
{
  ( theWrappedObject->start(bRunInThread));
}

void PythonQtWrapper_AbstractAutomaton::stop(AbstractAutomaton* theWrappedObject)
{
  ( theWrappedObject->stop());
}

void PythonQtWrapper_AbstractAutomaton::wait(AbstractAutomaton* theWrappedObject, int  milliseconds)
{
  ( ((PythonQtPublicPromoter_AbstractAutomaton*)theWrappedObject)->promoted_wait(milliseconds));
}

void PythonQtWrapper_AbstractAutomaton::waitChange(AbstractAutomaton* theWrappedObject, QVector<NamedBean* >  mInputs)
{
  ( theWrappedObject->waitChange(mInputs));
}

void PythonQtWrapper_AbstractAutomaton::waitMsec(AbstractAutomaton* theWrappedObject, int  milliseconds)
{
  ( theWrappedObject->waitMsec(milliseconds));
}

void PythonQtWrapper_AbstractAutomaton::waitSensorActive(AbstractAutomaton* theWrappedObject, QList<Sensor* >  mSensors)
{
  ( theWrappedObject->waitSensorActive(mSensors));
}

void PythonQtWrapper_AbstractAutomaton::waitSensorActive(AbstractAutomaton* theWrappedObject, Sensor*  mSensor)
{
  ( theWrappedObject->waitSensorActive(mSensor));
}

void PythonQtWrapper_AbstractAutomaton::waitSensorChange(AbstractAutomaton* theWrappedObject, QList<Sensor* >  mSensors)
{
  ( theWrappedObject->waitSensorChange(mSensors));
}

int  PythonQtWrapper_AbstractAutomaton::waitSensorChange(AbstractAutomaton* theWrappedObject, int  mState, Sensor*  mSensor)
{
  return ( theWrappedObject->waitSensorChange(mState, mSensor));
}

void PythonQtWrapper_AbstractAutomaton::waitSensorInactive(AbstractAutomaton* theWrappedObject, QList<Sensor* >  mSensors)
{
  ( theWrappedObject->waitSensorInactive(mSensors));
}

void PythonQtWrapper_AbstractAutomaton::waitSensorInactive(AbstractAutomaton* theWrappedObject, Sensor*  mSensor)
{
  ( theWrappedObject->waitSensorInactive(mSensor));
}

void PythonQtWrapper_AbstractAutomaton::waitSensorState(AbstractAutomaton* theWrappedObject, QList<Sensor* >  mSensors, int  state)
{
  ( theWrappedObject->waitSensorState(mSensors, state));
}

void PythonQtWrapper_AbstractAutomaton::waitSensorState(AbstractAutomaton* theWrappedObject, Sensor*  mSensor, int  state)
{
  ( theWrappedObject->waitSensorState(mSensor, state));
}

void PythonQtWrapper_AbstractAutomaton::waitTurnoutConsistent(AbstractAutomaton* theWrappedObject, QList<Turnout* >  mTurnouts)
{
  ( theWrappedObject->waitTurnoutConsistent(mTurnouts));
}

bool  PythonQtWrapper_AbstractAutomaton::writeOpsModeCV(AbstractAutomaton* theWrappedObject, int  CV, int  value, bool  longAddress, int  loco)
{
  return ( theWrappedObject->writeOpsModeCV(CV, value, longAddress, loco));
}

bool  PythonQtWrapper_AbstractAutomaton::writeServiceModeCV(AbstractAutomaton* theWrappedObject, int  CV, int  value)
{
  return ( theWrappedObject->writeServiceModeCV(CV, value));
}



PythonQtShell_AbstractManager::~PythonQtShell_AbstractManager() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_AbstractManager::Register(NamedBean*  s0)
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
  AbstractManager::Register(s0);
}
void PythonQtShell_AbstractManager::addPropertyChangeListener(PropertyChangeListener*  l0)
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
  AbstractManager::addPropertyChangeListener(l0);
}
void PythonQtShell_AbstractManager::deregister(NamedBean*  s0)
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
  AbstractManager::deregister(s0);
}
void PythonQtShell_AbstractManager::dispose()
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
  AbstractManager::dispose();
}
NamedBean*  PythonQtShell_AbstractManager::getBeanBySystemName(QString  systemName0)
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
  return AbstractManager::getBeanBySystemName(systemName0);
}
NamedBean*  PythonQtShell_AbstractManager::getBeanByUserName(QString  userName0)
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
  return AbstractManager::getBeanByUserName(userName0);
}
NamedBean*  PythonQtShell_AbstractManager::getNamedBean(QString  name0)
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
  return AbstractManager::getNamedBean(name0);
}
QStringList  PythonQtShell_AbstractManager::getSystemNameArray()
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
  return AbstractManager::getSystemNameArray();
}
QStringList  PythonQtShell_AbstractManager::getSystemNameList()
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
  return AbstractManager::getSystemNameList();
}
QString  PythonQtShell_AbstractManager::makeSystemName(QString  s0)
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
  return AbstractManager::makeSystemName(s0);
}
void PythonQtShell_AbstractManager::propertyChange(PropertyChangeEvent*  e0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("propertyChange");
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
  AbstractManager::propertyChange(e0);
}
void PythonQtShell_AbstractManager::removePropertyChangeListener(PropertyChangeListener*  l0)
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
  AbstractManager::removePropertyChangeListener(l0);
}
void PythonQtShell_AbstractManager::vetoableChange(PropertyChangeEvent*  evt0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("vetoableChange");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&evt0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  AbstractManager::vetoableChange(evt0);
}
AbstractManager* PythonQtWrapper_AbstractManager::new_AbstractManager(QObject*  parent)
{ 
return new PythonQtShell_AbstractManager(parent); }

void PythonQtWrapper_AbstractManager::Register(AbstractManager* theWrappedObject, NamedBean*  s)
{
  ( ((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->promoted_Register(s));
}

void PythonQtWrapper_AbstractManager::addPropertyChangeListener(AbstractManager* theWrappedObject, PropertyChangeListener*  l)
{
  ( ((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->promoted_addPropertyChangeListener(l));
}

void PythonQtWrapper_AbstractManager::deregister(AbstractManager* theWrappedObject, NamedBean*  s)
{
  ( ((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->promoted_deregister(s));
}

void PythonQtWrapper_AbstractManager::dispose(AbstractManager* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->promoted_dispose());
}

void PythonQtWrapper_AbstractManager::firePropertyChange(AbstractManager* theWrappedObject, QString  p, QVariant  old, QVariant  n)
{
  ( ((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->promoted_firePropertyChange(p, old, n));
}

void PythonQtWrapper_AbstractManager::fireVetoableChange(AbstractManager* theWrappedObject, QString  p, QVariant  old, QVariant  n)
{
  ( ((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->promoted_fireVetoableChange(p, old, n));
}

NamedBean*  PythonQtWrapper_AbstractManager::getBeanBySystemName(AbstractManager* theWrappedObject, QString  systemName)
{
  return ( ((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->promoted_getBeanBySystemName(systemName));
}

NamedBean*  PythonQtWrapper_AbstractManager::getBeanByUserName(AbstractManager* theWrappedObject, QString  userName)
{
  return ( ((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->promoted_getBeanByUserName(userName));
}

QObject*  PythonQtWrapper_AbstractManager::getInstanceBySystemName(AbstractManager* theWrappedObject, QString  systemName)
{
  return ( ((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->promoted_getInstanceBySystemName(systemName));
}

QObject*  PythonQtWrapper_AbstractManager::getInstanceByUserName(AbstractManager* theWrappedObject, QString  userName)
{
  return ( ((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->promoted_getInstanceByUserName(userName));
}

NamedBean*  PythonQtWrapper_AbstractManager::getNamedBean(AbstractManager* theWrappedObject, QString  name)
{
  return ( ((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->promoted_getNamedBean(name));
}

QList<NamedBean*>*  PythonQtWrapper_AbstractManager::getNamedBeanList(AbstractManager* theWrappedObject)
{
  return ( theWrappedObject->getNamedBeanList());
}

QSet<NamedBean* >  PythonQtWrapper_AbstractManager::getNamedBeanSet(AbstractManager* theWrappedObject)
{
  return ( theWrappedObject->getNamedBeanSet());
}

QStringList  PythonQtWrapper_AbstractManager::getSystemNameArray(AbstractManager* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->promoted_getSystemNameArray());
}

QHash<QString , NamedBean* >*  PythonQtWrapper_AbstractManager::getSystemNameHash(AbstractManager* theWrappedObject)
{
  return ( theWrappedObject->getSystemNameHash());
}

QStringList  PythonQtWrapper_AbstractManager::getSystemNameList(AbstractManager* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->promoted_getSystemNameList());
}

QStringList  PythonQtWrapper_AbstractManager::getUserNameList(AbstractManager* theWrappedObject)
{
  return ( theWrappedObject->getUserNameList());
}

QString  PythonQtWrapper_AbstractManager::makeSystemName(AbstractManager* theWrappedObject, QString  s)
{
  return ( ((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->promoted_makeSystemName(s));
}

QString  PythonQtWrapper_AbstractManager::normalizeSystemName(AbstractManager* theWrappedObject, QString  inputName)
{
  return ( theWrappedObject->normalizeSystemName(inputName));
}

void PythonQtWrapper_AbstractManager::propertyChange(AbstractManager* theWrappedObject, PropertyChangeEvent*  e)
{
  ( ((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->promoted_propertyChange(e));
}

void PythonQtWrapper_AbstractManager::registerSelf(AbstractManager* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->promoted_registerSelf());
}

void PythonQtWrapper_AbstractManager::removePropertyChangeListener(AbstractManager* theWrappedObject, PropertyChangeListener*  l)
{
  ( ((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->promoted_removePropertyChangeListener(l));
}

void PythonQtWrapper_AbstractManager::vetoableChange(AbstractManager* theWrappedObject, PropertyChangeEvent*  evt)
{
  ( ((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->promoted_vetoableChange(evt));
}



PythonQtShell_AbstractProxyManager::~PythonQtShell_AbstractProxyManager() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_AbstractProxyManager::Register(NamedBean*  s0)
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
  AbstractProxyManager::Register(s0);
}
void PythonQtShell_AbstractProxyManager::addPropertyChangeListener(PropertyChangeListener*  l0)
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
  AbstractProxyManager::addPropertyChangeListener(l0);
}
void PythonQtShell_AbstractProxyManager::deregister(NamedBean*  s0)
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
  AbstractProxyManager::deregister(s0);
}
void PythonQtShell_AbstractProxyManager::dispose()
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
  AbstractProxyManager::dispose();
}
NamedBean*  PythonQtShell_AbstractProxyManager::getBeanBySystemName(QString  systemName0)
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
  return AbstractProxyManager::getBeanBySystemName(systemName0);
}
NamedBean*  PythonQtShell_AbstractProxyManager::getBeanByUserName(QString  userName0)
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
  return AbstractProxyManager::getBeanByUserName(userName0);
}
Manager*  PythonQtShell_AbstractProxyManager::getMgr(int  index0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getMgr");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"Manager*" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      Manager* returnValue;
    void* args[2] = {NULL, (void*)&index0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getMgr", methodInfo, result);
        } else {
          returnValue = *((Manager**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return AbstractProxyManager::getMgr(index0);
}
NamedBean*  PythonQtShell_AbstractProxyManager::getNamedBean(QString  name0)
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
  return AbstractProxyManager::getNamedBean(name0);
}
QStringList  PythonQtShell_AbstractProxyManager::getSystemNameArray()
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
  return AbstractProxyManager::getSystemNameArray();
}
QStringList  PythonQtShell_AbstractProxyManager::getSystemNameList()
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
  return AbstractProxyManager::getSystemNameList();
}
QStringList  PythonQtShell_AbstractProxyManager::getUserNameList()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getUserNameList");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getUserNameList", methodInfo, result);
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
  return AbstractProxyManager::getUserNameList();
}
NamedBean*  PythonQtShell_AbstractProxyManager::makeBean(int  arg__1, QString  arg__2, QString  arg__3)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("makeBean");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"NamedBean*" , "int" , "QString" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(4, argumentList);
      NamedBean* returnValue;
    void* args[4] = {NULL, (void*)&arg__1, (void*)&arg__2, (void*)&arg__3};
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
  return AbstractProxyManager::makeBean(arg__1, arg__2, arg__3);
}
Manager*  PythonQtShell_AbstractProxyManager::makeInternalManager() const
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("makeInternalManager");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"Manager*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      Manager* returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("makeInternalManager", methodInfo, result);
        } else {
          returnValue = *((Manager**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return AbstractProxyManager::makeInternalManager();
}
QString  PythonQtShell_AbstractProxyManager::makeSystemName(QString  s0)
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
  return AbstractProxyManager::makeSystemName(s0);
}
int  PythonQtShell_AbstractProxyManager::match(QString  systemname0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("match");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      int returnValue;
    void* args[2] = {NULL, (void*)&systemname0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("match", methodInfo, result);
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
  return AbstractProxyManager::match(systemname0);
}
int  PythonQtShell_AbstractProxyManager::matchTentative(QString  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("matchTentative");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"int" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      int returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("matchTentative", methodInfo, result);
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
  return AbstractProxyManager::matchTentative(arg__1);
}
int  PythonQtShell_AbstractProxyManager::nMgrs()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("nMgrs");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("nMgrs", methodInfo, result);
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
  return AbstractProxyManager::nMgrs();
}
void PythonQtShell_AbstractProxyManager::propertyChange(PropertyChangeEvent*  e0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("propertyChange");
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
  AbstractProxyManager::propertyChange(e0);
}
NamedBean*  PythonQtShell_AbstractProxyManager::provideNamedBean(QString  name0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("provideNamedBean");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("provideNamedBean", methodInfo, result);
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
  return AbstractProxyManager::provideNamedBean(name0);
}
void PythonQtShell_AbstractProxyManager::removePropertyChangeListener(PropertyChangeListener*  l0)
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
  AbstractProxyManager::removePropertyChangeListener(l0);
}
void PythonQtShell_AbstractProxyManager::vetoableChange(PropertyChangeEvent*  evt0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("vetoableChange");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&evt0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  AbstractProxyManager::vetoableChange(evt0);
}
AbstractProxyManager* PythonQtWrapper_AbstractProxyManager::new_AbstractProxyManager(QObject*  parent)
{ 
return new PythonQtShell_AbstractProxyManager(parent); }

void PythonQtWrapper_AbstractProxyManager::Register(AbstractProxyManager* theWrappedObject, NamedBean*  s)
{
  ( ((PythonQtPublicPromoter_AbstractProxyManager*)theWrappedObject)->promoted_Register(s));
}

void PythonQtWrapper_AbstractProxyManager::addManager(AbstractProxyManager* theWrappedObject, Manager*  m)
{
  ( theWrappedObject->addManager(m));
}

void PythonQtWrapper_AbstractProxyManager::addPropertyChangeListener(AbstractProxyManager* theWrappedObject, PropertyChangeListener*  l)
{
  ( ((PythonQtPublicPromoter_AbstractProxyManager*)theWrappedObject)->promoted_addPropertyChangeListener(l));
}

void PythonQtWrapper_AbstractProxyManager::deregister(AbstractProxyManager* theWrappedObject, NamedBean*  s)
{
  ( ((PythonQtPublicPromoter_AbstractProxyManager*)theWrappedObject)->promoted_deregister(s));
}

void PythonQtWrapper_AbstractProxyManager::dispose(AbstractProxyManager* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_AbstractProxyManager*)theWrappedObject)->promoted_dispose());
}

NamedBean*  PythonQtWrapper_AbstractProxyManager::getBeanBySystemName(AbstractProxyManager* theWrappedObject, QString  systemName)
{
  return ( ((PythonQtPublicPromoter_AbstractProxyManager*)theWrappedObject)->promoted_getBeanBySystemName(systemName));
}

NamedBean*  PythonQtWrapper_AbstractProxyManager::getBeanByUserName(AbstractProxyManager* theWrappedObject, QString  userName)
{
  return ( ((PythonQtPublicPromoter_AbstractProxyManager*)theWrappedObject)->promoted_getBeanByUserName(userName));
}

Manager*  PythonQtWrapper_AbstractProxyManager::getDefaultManager(AbstractProxyManager* theWrappedObject)
{
  return ( theWrappedObject->getDefaultManager());
}

QList<Manager* >  PythonQtWrapper_AbstractProxyManager::getDisplayOrderManagerList(AbstractProxyManager* theWrappedObject)
{
  return ( theWrappedObject->getDisplayOrderManagerList());
}

Manager*  PythonQtWrapper_AbstractProxyManager::getInternalManager(AbstractProxyManager* theWrappedObject)
{
  return ( theWrappedObject->getInternalManager());
}

QList<Manager* >  PythonQtWrapper_AbstractProxyManager::getManagerList(AbstractProxyManager* theWrappedObject)
{
  return ( theWrappedObject->getManagerList());
}

Manager*  PythonQtWrapper_AbstractProxyManager::getMgr(AbstractProxyManager* theWrappedObject, int  index)
{
  return ( ((PythonQtPublicPromoter_AbstractProxyManager*)theWrappedObject)->promoted_getMgr(index));
}

NamedBean*  PythonQtWrapper_AbstractProxyManager::getNamedBean(AbstractProxyManager* theWrappedObject, QString  name)
{
  return ( ((PythonQtPublicPromoter_AbstractProxyManager*)theWrappedObject)->promoted_getNamedBean(name));
}

QList<NamedBean*>*  PythonQtWrapper_AbstractProxyManager::getNamedBeanList(AbstractProxyManager* theWrappedObject)
{
  return ( theWrappedObject->getNamedBeanList());
}

QSet<NamedBean* >  PythonQtWrapper_AbstractProxyManager::getNamedBeanSet(AbstractProxyManager* theWrappedObject)
{
  return ( theWrappedObject->getNamedBeanSet());
}

QStringList  PythonQtWrapper_AbstractProxyManager::getSystemNameAddedOrderList(AbstractProxyManager* theWrappedObject)
{
  return ( theWrappedObject->getSystemNameAddedOrderList());
}

QStringList  PythonQtWrapper_AbstractProxyManager::getSystemNameArray(AbstractProxyManager* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractProxyManager*)theWrappedObject)->promoted_getSystemNameArray());
}

QStringList  PythonQtWrapper_AbstractProxyManager::getSystemNameList(AbstractProxyManager* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractProxyManager*)theWrappedObject)->promoted_getSystemNameList());
}

QString  PythonQtWrapper_AbstractProxyManager::getSystemPrefix(AbstractProxyManager* theWrappedObject)
{
  return ( theWrappedObject->getSystemPrefix());
}

QStringList  PythonQtWrapper_AbstractProxyManager::getUserNameList(AbstractProxyManager* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractProxyManager*)theWrappedObject)->promoted_getUserNameList());
}

NamedBean*  PythonQtWrapper_AbstractProxyManager::makeBean(AbstractProxyManager* theWrappedObject, int  arg__1, QString  arg__2, QString  arg__3)
{
  return ( ((PythonQtPublicPromoter_AbstractProxyManager*)theWrappedObject)->promoted_makeBean(arg__1, arg__2, arg__3));
}

Manager*  PythonQtWrapper_AbstractProxyManager::makeInternalManager(AbstractProxyManager* theWrappedObject) const
{
  return ( ((PythonQtPublicPromoter_AbstractProxyManager*)theWrappedObject)->promoted_makeInternalManager());
}

QString  PythonQtWrapper_AbstractProxyManager::makeSystemName(AbstractProxyManager* theWrappedObject, QString  s)
{
  return ( ((PythonQtPublicPromoter_AbstractProxyManager*)theWrappedObject)->promoted_makeSystemName(s));
}

int  PythonQtWrapper_AbstractProxyManager::match(AbstractProxyManager* theWrappedObject, QString  systemname)
{
  return ( ((PythonQtPublicPromoter_AbstractProxyManager*)theWrappedObject)->promoted_match(systemname));
}

int  PythonQtWrapper_AbstractProxyManager::matchTentative(AbstractProxyManager* theWrappedObject, QString  arg__1)
{
  return ( ((PythonQtPublicPromoter_AbstractProxyManager*)theWrappedObject)->promoted_matchTentative(arg__1));
}

int  PythonQtWrapper_AbstractProxyManager::nMgrs(AbstractProxyManager* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractProxyManager*)theWrappedObject)->promoted_nMgrs());
}

NamedBean*  PythonQtWrapper_AbstractProxyManager::newNamedBean(AbstractProxyManager* theWrappedObject, QString  systemName, QString  userName)
{
  return ( theWrappedObject->newNamedBean(systemName, userName));
}

QString  PythonQtWrapper_AbstractProxyManager::normalizeSystemName(AbstractProxyManager* theWrappedObject, QString  inputName)
{
  return ( theWrappedObject->normalizeSystemName(inputName));
}

void PythonQtWrapper_AbstractProxyManager::propertyChange(AbstractProxyManager* theWrappedObject, PropertyChangeEvent*  e)
{
  ( ((PythonQtPublicPromoter_AbstractProxyManager*)theWrappedObject)->promoted_propertyChange(e));
}

NamedBean*  PythonQtWrapper_AbstractProxyManager::provideNamedBean(AbstractProxyManager* theWrappedObject, QString  name)
{
  return ( ((PythonQtPublicPromoter_AbstractProxyManager*)theWrappedObject)->promoted_provideNamedBean(name));
}

void PythonQtWrapper_AbstractProxyManager::removePropertyChangeListener(AbstractProxyManager* theWrappedObject, PropertyChangeListener*  l)
{
  ( ((PythonQtPublicPromoter_AbstractProxyManager*)theWrappedObject)->promoted_removePropertyChangeListener(l));
}

char  PythonQtWrapper_AbstractProxyManager::typeLetter(AbstractProxyManager* theWrappedObject)
{
  return ( theWrappedObject->typeLetter());
}

void PythonQtWrapper_AbstractProxyManager::updateNamedBeanSet(AbstractProxyManager* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_AbstractProxyManager*)theWrappedObject)->promoted_updateNamedBeanSet());
}

void PythonQtWrapper_AbstractProxyManager::updateOrderList(AbstractProxyManager* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_AbstractProxyManager*)theWrappedObject)->promoted_updateOrderList());
}



PythonQtShell_AbstractSensor::~PythonQtShell_AbstractSensor() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_AbstractSensor::addPropertyChangeListener(PropertyChangeListener*  arg__1) const
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
  AbstractSensor::addPropertyChangeListener(arg__1);
}
bool  PythonQtShell_AbstractSensor::canInvert()
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
  return AbstractSensor::canInvert();
}
void PythonQtShell_AbstractSensor::dispose() const
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
  AbstractSensor::dispose();
}
bool  PythonQtShell_AbstractSensor::getInverted()
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
  return AbstractSensor::getInverted();
}
int  PythonQtShell_AbstractSensor::getKnownState() const
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
  return AbstractSensor::getKnownState();
}
int  PythonQtShell_AbstractSensor::getRawState()
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
  return AbstractSensor::getRawState();
}
long  PythonQtShell_AbstractSensor::getSensorDebounceGoingActiveTimer()
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
  return AbstractSensor::getSensorDebounceGoingActiveTimer();
}
long  PythonQtShell_AbstractSensor::getSensorDebounceGoingInActiveTimer()
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
  return AbstractSensor::getSensorDebounceGoingInActiveTimer();
}
void PythonQtShell_AbstractSensor::removePropertyChangeListener(PropertyChangeListener*  arg__1) const
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
  AbstractSensor::removePropertyChangeListener(arg__1);
}
void PythonQtShell_AbstractSensor::requestUpdateFromLayout() const
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
  AbstractSensor::requestUpdateFromLayout();
}
void PythonQtShell_AbstractSensor::setInverted(bool  inverted0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setInverted");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&inverted0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  AbstractSensor::setInverted(inverted0);
}
void PythonQtShell_AbstractSensor::setKnownState(int  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setKnownState");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int"};
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
  AbstractSensor::setKnownState(s0);
}
void PythonQtShell_AbstractSensor::setSensorDebounceGoingActiveTimer(long  time0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setSensorDebounceGoingActiveTimer");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "long"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&time0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  AbstractSensor::setSensorDebounceGoingActiveTimer(time0);
}
void PythonQtShell_AbstractSensor::setSensorDebounceGoingInActiveTimer(long  time0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setSensorDebounceGoingInActiveTimer");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "long"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&time0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  AbstractSensor::setSensorDebounceGoingInActiveTimer(time0);
}
bool  PythonQtShell_AbstractSensor::useDefaultTimerSettings()
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
  return AbstractSensor::useDefaultTimerSettings();
}
void PythonQtShell_AbstractSensor::useDefaultTimerSettings(bool  boo0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("useDefaultTimerSettings");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&boo0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  AbstractSensor::useDefaultTimerSettings(boo0);
}
AbstractSensor* PythonQtWrapper_AbstractSensor::new_AbstractSensor(QObject*  parent)
{ 
return new PythonQtShell_AbstractSensor(parent); }

AbstractSensor* PythonQtWrapper_AbstractSensor::new_AbstractSensor(QString  systemName, QObject*  parent)
{ 
return new PythonQtShell_AbstractSensor(systemName, parent); }

AbstractSensor* PythonQtWrapper_AbstractSensor::new_AbstractSensor(QString  systemName, QString  userName, QObject*  parent)
{ 
return new PythonQtShell_AbstractSensor(systemName, userName, parent); }

bool  PythonQtWrapper_AbstractSensor::getInverted(AbstractSensor* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->promoted_getInverted());
}

int  PythonQtWrapper_AbstractSensor::getKnownState(AbstractSensor* theWrappedObject) const
{
  return ( ((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->promoted_getKnownState());
}

int  PythonQtWrapper_AbstractSensor::getRawState(AbstractSensor* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->promoted_getRawState());
}

long  PythonQtWrapper_AbstractSensor::getSensorDebounceGoingActiveTimer(AbstractSensor* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->promoted_getSensorDebounceGoingActiveTimer());
}

long  PythonQtWrapper_AbstractSensor::getSensorDebounceGoingInActiveTimer(AbstractSensor* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->promoted_getSensorDebounceGoingInActiveTimer());
}

int  PythonQtWrapper_AbstractSensor::getState(AbstractSensor* theWrappedObject)
{
  return ( theWrappedObject->getState());
}

QString  PythonQtWrapper_AbstractSensor::getStateName(AbstractSensor* theWrappedObject, int  arg__1)
{
  return ( theWrappedObject->getStateName(arg__1));
}

void PythonQtWrapper_AbstractSensor::sensorDebounce(AbstractSensor* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->promoted_sensorDebounce());
}

void PythonQtWrapper_AbstractSensor::setInverted(AbstractSensor* theWrappedObject, bool  inverted)
{
  ( ((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->promoted_setInverted(inverted));
}

void PythonQtWrapper_AbstractSensor::setKnownState(AbstractSensor* theWrappedObject, int  s)
{
  ( ((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->promoted_setKnownState(s));
}

void PythonQtWrapper_AbstractSensor::setOwnState(AbstractSensor* theWrappedObject, int  s)
{
  ( theWrappedObject->setOwnState(s));
}

void PythonQtWrapper_AbstractSensor::setSensorDebounceGoingActiveTimer(AbstractSensor* theWrappedObject, long  time)
{
  ( ((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->promoted_setSensorDebounceGoingActiveTimer(time));
}

void PythonQtWrapper_AbstractSensor::setSensorDebounceGoingInActiveTimer(AbstractSensor* theWrappedObject, long  time)
{
  ( ((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->promoted_setSensorDebounceGoingInActiveTimer(time));
}

void PythonQtWrapper_AbstractSensor::setState(AbstractSensor* theWrappedObject, int  s)
{
  ( theWrappedObject->setState(s));
}

bool  PythonQtWrapper_AbstractSensor::useDefaultTimerSettings(AbstractSensor* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->promoted_useDefaultTimerSettings());
}

void PythonQtWrapper_AbstractSensor::useDefaultTimerSettings(AbstractSensor* theWrappedObject, bool  boo)
{
  ( ((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->promoted_useDefaultTimerSettings(boo));
}



PythonQtShell_AbstractSensorManager::~PythonQtShell_AbstractSensorManager() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
Sensor*  PythonQtShell_AbstractSensorManager::createNewSensor(QString  arg__1, QString  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("createNewSensor");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("createNewSensor", methodInfo, result);
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
  return AbstractSensorManager::createNewSensor(arg__1, arg__2);
}
int  PythonQtShell_AbstractSensorManager::getXMLOrder()
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
  return AbstractSensorManager::getXMLOrder();
}
char  PythonQtShell_AbstractSensorManager::typeLetter()
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
  return AbstractSensorManager::typeLetter();
}
AbstractSensorManager* PythonQtWrapper_AbstractSensorManager::new_AbstractSensorManager(QObject*  parent)
{ 
return new PythonQtShell_AbstractSensorManager(parent); }

bool  PythonQtWrapper_AbstractSensorManager::allowMultipleAdditions(AbstractSensorManager* theWrappedObject, QString  systemName)
{
  return ( theWrappedObject->allowMultipleAdditions(systemName));
}

Sensor*  PythonQtWrapper_AbstractSensorManager::createNewSensor(AbstractSensorManager* theWrappedObject, QString  arg__1, QString  arg__2)
{
  return ( ((PythonQtPublicPromoter_AbstractSensorManager*)theWrappedObject)->promoted_createNewSensor(arg__1, arg__2));
}

QString  PythonQtWrapper_AbstractSensorManager::createSystemName(AbstractSensorManager* theWrappedObject, QString  curAddress, QString  prefix) throw (JmriException)
{
  return ( theWrappedObject->createSystemName(curAddress, prefix));
}

Sensor*  PythonQtWrapper_AbstractSensorManager::getBySystemName(AbstractSensorManager* theWrappedObject, QString  key)
{
  return ( theWrappedObject->getBySystemName(key));
}

Sensor*  PythonQtWrapper_AbstractSensorManager::getByUserName(AbstractSensorManager* theWrappedObject, QString  key)
{
  return ( theWrappedObject->getByUserName(key));
}

long  PythonQtWrapper_AbstractSensorManager::getDefaultSensorDebounceGoingActive(AbstractSensorManager* theWrappedObject)
{
  return ( theWrappedObject->getDefaultSensorDebounceGoingActive());
}

long  PythonQtWrapper_AbstractSensorManager::getDefaultSensorDebounceGoingInActive(AbstractSensorManager* theWrappedObject)
{
  return ( theWrappedObject->getDefaultSensorDebounceGoingInActive());
}

QObject*  PythonQtWrapper_AbstractSensorManager::getInstanceBySystemName(AbstractSensorManager* theWrappedObject, QString  systemName)
{
  return ( ((PythonQtPublicPromoter_AbstractSensorManager*)theWrappedObject)->promoted_getInstanceBySystemName(systemName));
}

QString  PythonQtWrapper_AbstractSensorManager::getNextValidAddress(AbstractSensorManager* theWrappedObject, QString  curAddress, QString  prefix)
{
  return ( theWrappedObject->getNextValidAddress(curAddress, prefix));
}

Sensor*  PythonQtWrapper_AbstractSensorManager::getSensor(AbstractSensorManager* theWrappedObject, QString  name)
{
  return ( theWrappedObject->getSensor(name));
}

int  PythonQtWrapper_AbstractSensorManager::getXMLOrder(AbstractSensorManager* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractSensorManager*)theWrappedObject)->promoted_getXMLOrder());
}

Sensor*  PythonQtWrapper_AbstractSensorManager::newSensor(AbstractSensorManager* theWrappedObject, QString  sysName, QString  userName)
{
  return ( theWrappedObject->newSensor(sysName, userName));
}

QString  PythonQtWrapper_AbstractSensorManager::normalizeSystemName(AbstractSensorManager* theWrappedObject, QString  sysName)
{
  return ( ((PythonQtPublicPromoter_AbstractSensorManager*)theWrappedObject)->promoted_normalizeSystemName(sysName));
}

Sensor*  PythonQtWrapper_AbstractSensorManager::provideSensor(AbstractSensorManager* theWrappedObject, QString  name)
{
  return ( theWrappedObject->provideSensor(name));
}

void PythonQtWrapper_AbstractSensorManager::setDefaultSensorDebounceGoingActive(AbstractSensorManager* theWrappedObject, long  timer)
{
  ( theWrappedObject->setDefaultSensorDebounceGoingActive(timer));
}

void PythonQtWrapper_AbstractSensorManager::setDefaultSensorDebounceGoingInActive(AbstractSensorManager* theWrappedObject, long  timer)
{
  ( theWrappedObject->setDefaultSensorDebounceGoingInActive(timer));
}

char  PythonQtWrapper_AbstractSensorManager::typeLetter(AbstractSensorManager* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractSensorManager*)theWrappedObject)->promoted_typeLetter());
}

void PythonQtWrapper_AbstractSensorManager::updateAll(AbstractSensorManager* theWrappedObject)
{
  ( theWrappedObject->updateAll());
}



void PythonQtWrapper_AbstractSerialPortController::_connect(AbstractSerialPortController* theWrappedObject)
{
  ( theWrappedObject->_connect());
}

void PythonQtWrapper_AbstractSerialPortController::closeConnection(AbstractSerialPortController* theWrappedObject) throw( Exception)
{
  ( ((PythonQtPublicPromoter_AbstractSerialPortController*)theWrappedObject)->promoted_closeConnection());
}

void PythonQtWrapper_AbstractSerialPortController::configureBaudRate(AbstractSerialPortController* theWrappedObject, QString  rate)
{
  ( theWrappedObject->configureBaudRate(rate));
}

int  PythonQtWrapper_AbstractSerialPortController::currentBaudNumber(AbstractSerialPortController* theWrappedObject, QString  currentBaudRate)
{
  return ( ((PythonQtPublicPromoter_AbstractSerialPortController*)theWrappedObject)->promoted_currentBaudNumber(currentBaudRate));
}

void PythonQtWrapper_AbstractSerialPortController::dispose(AbstractSerialPortController* theWrappedObject)
{
  ( theWrappedObject->dispose());
}

QString  PythonQtWrapper_AbstractSerialPortController::getCurrentBaudRate(AbstractSerialPortController* theWrappedObject)
{
  return ( theWrappedObject->getCurrentBaudRate());
}

QString  PythonQtWrapper_AbstractSerialPortController::getCurrentPortName(AbstractSerialPortController* theWrappedObject)
{
  return ( theWrappedObject->getCurrentPortName());
}

QString  PythonQtWrapper_AbstractSerialPortController::getOptionState(AbstractSerialPortController* theWrappedObject, QString  option)
{
  return ( theWrappedObject->getOptionState(option));
}

QVector<QString >  PythonQtWrapper_AbstractSerialPortController::getPortNames(AbstractSerialPortController* theWrappedObject)
{
  return ( theWrappedObject->getPortNames());
}

void PythonQtWrapper_AbstractSerialPortController::reconnect(AbstractSerialPortController* theWrappedObject)
{
  ( theWrappedObject->reconnect());
}

void PythonQtWrapper_AbstractSerialPortController::recover(AbstractSerialPortController* theWrappedObject)
{
  ( theWrappedObject->recover());
}

void PythonQtWrapper_AbstractSerialPortController::resetupConnection(AbstractSerialPortController* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_AbstractSerialPortController*)theWrappedObject)->promoted_resetupConnection());
}

void PythonQtWrapper_AbstractSerialPortController::setDisabled(AbstractSerialPortController* theWrappedObject, bool  disabled)
{
  ( theWrappedObject->setDisabled(disabled));
}

void PythonQtWrapper_AbstractSerialPortController::setPort(AbstractSerialPortController* theWrappedObject, QString  port)
{
  ( ((PythonQtPublicPromoter_AbstractSerialPortController*)theWrappedObject)->promoted_setPort(port));
}

QVector<int >  PythonQtWrapper_AbstractSerialPortController::validBaudNumber(AbstractSerialPortController* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractSerialPortController*)theWrappedObject)->promoted_validBaudNumber());
}

QStringList  PythonQtWrapper_AbstractSerialPortController::validBaudRates(AbstractSerialPortController* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractSerialPortController*)theWrappedObject)->promoted_validBaudRates());
}



PythonQtShell_AbstractTurnout::~PythonQtShell_AbstractTurnout() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
bool  PythonQtShell_AbstractTurnout::canInvert()
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
  return AbstractTurnout::canInvert();
}
bool  PythonQtShell_AbstractTurnout::canLock(int  turnoutLockout0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("canLock");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&turnoutLockout0};
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
  return AbstractTurnout::canLock(turnoutLockout0);
}
void PythonQtShell_AbstractTurnout::dispose()
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
  AbstractTurnout::dispose();
}
void PythonQtShell_AbstractTurnout::enableLockOperation(int  turnoutLockout0, bool  enabled1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("enableLockOperation");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
    void* args[3] = {NULL, (void*)&turnoutLockout0, (void*)&enabled1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  AbstractTurnout::enableLockOperation(turnoutLockout0, enabled1);
}
void PythonQtShell_AbstractTurnout::forwardCommandChangeToLayout()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("forwardCommandChangeToLayout");
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
  AbstractTurnout::forwardCommandChangeToLayout();
}
void PythonQtShell_AbstractTurnout::forwardCommandChangeToLayout(int  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("forwardCommandChangeToLayout");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int"};
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
  AbstractTurnout::forwardCommandChangeToLayout(s0);
}
int  PythonQtShell_AbstractTurnout::getCommandedState()
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
  return AbstractTurnout::getCommandedState();
}
int  PythonQtShell_AbstractTurnout::getControlType()
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
  return AbstractTurnout::getControlType();
}
QString  PythonQtShell_AbstractTurnout::getDecoderName()
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
  return AbstractTurnout::getDecoderName();
}
float  PythonQtShell_AbstractTurnout::getDivergingLimit()
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
  return AbstractTurnout::getDivergingLimit();
}
QString  PythonQtShell_AbstractTurnout::getDivergingSpeed()
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
  return AbstractTurnout::getDivergingSpeed();
}
int  PythonQtShell_AbstractTurnout::getFeedbackMode()
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
  return AbstractTurnout::getFeedbackMode();
}
QString  PythonQtShell_AbstractTurnout::getFeedbackModeName()
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
  return AbstractTurnout::getFeedbackModeName();
}
Sensor*  PythonQtShell_AbstractTurnout::getFirstSensor()
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
  return AbstractTurnout::getFirstSensor();
}
bool  PythonQtShell_AbstractTurnout::getInhibitOperation()
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
  return AbstractTurnout::getInhibitOperation();
}
bool  PythonQtShell_AbstractTurnout::getInverted()
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
  return AbstractTurnout::getInverted();
}
int  PythonQtShell_AbstractTurnout::getKnownState()
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
  return AbstractTurnout::getKnownState();
}
bool  PythonQtShell_AbstractTurnout::getLocked(int  turnoutLockout0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getLocked");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&turnoutLockout0};
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
  return AbstractTurnout::getLocked(turnoutLockout0);
}
int  PythonQtShell_AbstractTurnout::getNumberOutputBits()
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
  return AbstractTurnout::getNumberOutputBits();
}
int  PythonQtShell_AbstractTurnout::getPossibleLockModes()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getPossibleLockModes");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getPossibleLockModes", methodInfo, result);
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
  return AbstractTurnout::getPossibleLockModes();
}
bool  PythonQtShell_AbstractTurnout::getReportLocked()
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
  return AbstractTurnout::getReportLocked();
}
Sensor*  PythonQtShell_AbstractTurnout::getSecondSensor()
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
  return AbstractTurnout::getSecondSensor();
}
int  PythonQtShell_AbstractTurnout::getState()
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
  return AbstractTurnout::getState();
}
float  PythonQtShell_AbstractTurnout::getStraightLimit()
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
  return AbstractTurnout::getStraightLimit();
}
QString  PythonQtShell_AbstractTurnout::getStraightSpeed()
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
  return AbstractTurnout::getStraightSpeed();
}
QStringList  PythonQtShell_AbstractTurnout::getValidDecoderNames()
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
  return AbstractTurnout::getValidDecoderNames();
}
QStringList  PythonQtShell_AbstractTurnout::getValidFeedbackNames()
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
  return AbstractTurnout::getValidFeedbackNames();
}
int  PythonQtShell_AbstractTurnout::getValidFeedbackTypes()
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
  return AbstractTurnout::getValidFeedbackTypes();
}
bool  PythonQtShell_AbstractTurnout::isConsistentState()
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
  return AbstractTurnout::isConsistentState();
}
void PythonQtShell_AbstractTurnout::provideFirstFeedbackSensor(QString  pName0) throw(JmriException)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("provideFirstFeedbackSensor");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&pName0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  AbstractTurnout::provideFirstFeedbackSensor(pName0);
}
void PythonQtShell_AbstractTurnout::provideSecondFeedbackSensor(QString  pName0) throw(JmriException)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("provideSecondFeedbackSensor");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&pName0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  AbstractTurnout::provideSecondFeedbackSensor(pName0);
}
void PythonQtShell_AbstractTurnout::requestUpdateFromLayout()
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
  AbstractTurnout::requestUpdateFromLayout();
}
void PythonQtShell_AbstractTurnout::setBinaryOutput(bool  state0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setBinaryOutput");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&state0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  AbstractTurnout::setBinaryOutput(state0);
}
void PythonQtShell_AbstractTurnout::setCommandedState(int  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setCommandedState");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int"};
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
  AbstractTurnout::setCommandedState(s0);
}
void PythonQtShell_AbstractTurnout::setControlType(int  num0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setControlType");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&num0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  AbstractTurnout::setControlType(num0);
}
void PythonQtShell_AbstractTurnout::setDecoderName(QString  decoderName0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setDecoderName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&decoderName0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  AbstractTurnout::setDecoderName(decoderName0);
}
void PythonQtShell_AbstractTurnout::setDivergingSpeed(QString  s0) throw(JmriException)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setDivergingSpeed");
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
  AbstractTurnout::setDivergingSpeed(s0);
}
void PythonQtShell_AbstractTurnout::setFeedbackMode(QString  mode0) throw(IllegalArgumentException)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setFeedbackMode");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&mode0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  AbstractTurnout::setFeedbackMode(mode0);
}
void PythonQtShell_AbstractTurnout::setFeedbackMode(int  mode0) throw(IllegalArgumentException)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setFeedbackMode");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&mode0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  AbstractTurnout::setFeedbackMode(mode0);
}
void PythonQtShell_AbstractTurnout::setInhibitOperation(bool  io0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setInhibitOperation");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&io0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  AbstractTurnout::setInhibitOperation(io0);
}
void PythonQtShell_AbstractTurnout::setInitialKnownStateFromFeedback()
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
  AbstractTurnout::setInitialKnownStateFromFeedback();
}
void PythonQtShell_AbstractTurnout::setInverted(bool  inverted0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setInverted");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&inverted0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  AbstractTurnout::setInverted(inverted0);
}
void PythonQtShell_AbstractTurnout::setLocked(int  turnoutLockout0, bool  locked1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setLocked");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
    void* args[3] = {NULL, (void*)&turnoutLockout0, (void*)&locked1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  AbstractTurnout::setLocked(turnoutLockout0, locked1);
}
void PythonQtShell_AbstractTurnout::setNumberOutputBits(int  num0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setNumberOutputBits");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&num0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  AbstractTurnout::setNumberOutputBits(num0);
}
void PythonQtShell_AbstractTurnout::setReportLocked(bool  reportLocked0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setReportLocked");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&reportLocked0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  AbstractTurnout::setReportLocked(reportLocked0);
}
void PythonQtShell_AbstractTurnout::setState(int  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setState");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int"};
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
  AbstractTurnout::setState(s0);
}
void PythonQtShell_AbstractTurnout::setStraightSpeed(QString  s0) throw(JmriException)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setStraightSpeed");
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
  AbstractTurnout::setStraightSpeed(s0);
}
void PythonQtShell_AbstractTurnout::turnoutPushbuttonLockout(bool  locked0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("turnoutPushbuttonLockout");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&locked0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  AbstractTurnout::turnoutPushbuttonLockout(locked0);
}
AbstractTurnout* PythonQtWrapper_AbstractTurnout::new_AbstractTurnout(QObject*  parent)
{ 
return new PythonQtShell_AbstractTurnout(parent); }

AbstractTurnout* PythonQtWrapper_AbstractTurnout::new_AbstractTurnout(QString  systemName, QObject*  parent)
{ 
return new PythonQtShell_AbstractTurnout(systemName, parent); }

AbstractTurnout* PythonQtWrapper_AbstractTurnout::new_AbstractTurnout(QString  systemName, QString  userName, QObject*  parent)
{ 
return new PythonQtShell_AbstractTurnout(systemName, userName, parent); }

bool  PythonQtWrapper_AbstractTurnout::canInvert(AbstractTurnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_canInvert());
}

bool  PythonQtWrapper_AbstractTurnout::canLock(AbstractTurnout* theWrappedObject, int  turnoutLockout)
{
  return ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_canLock(turnoutLockout));
}

QString  PythonQtWrapper_AbstractTurnout::describeState(AbstractTurnout* theWrappedObject, int  state)
{
  return ( theWrappedObject->describeState(state));
}

void PythonQtWrapper_AbstractTurnout::dispose(AbstractTurnout* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_dispose());
}

void PythonQtWrapper_AbstractTurnout::enableLockOperation(AbstractTurnout* theWrappedObject, int  turnoutLockout, bool  enabled)
{
  ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_enableLockOperation(turnoutLockout, enabled));
}

void PythonQtWrapper_AbstractTurnout::forwardCommandChangeToLayout(AbstractTurnout* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_forwardCommandChangeToLayout());
}

void PythonQtWrapper_AbstractTurnout::forwardCommandChangeToLayout(AbstractTurnout* theWrappedObject, int  s)
{
  ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_forwardCommandChangeToLayout(s));
}

QString  PythonQtWrapper_AbstractTurnout::getBeanType(AbstractTurnout* theWrappedObject)
{
  return ( theWrappedObject->getBeanType());
}

int  PythonQtWrapper_AbstractTurnout::getCommandedState(AbstractTurnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_getCommandedState());
}

int  PythonQtWrapper_AbstractTurnout::getControlType(AbstractTurnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_getControlType());
}

QString  PythonQtWrapper_AbstractTurnout::getDecoderName(AbstractTurnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_getDecoderName());
}

float  PythonQtWrapper_AbstractTurnout::getDivergingLimit(AbstractTurnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_getDivergingLimit());
}

QString  PythonQtWrapper_AbstractTurnout::getDivergingSpeed(AbstractTurnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_getDivergingSpeed());
}

int  PythonQtWrapper_AbstractTurnout::getFeedbackMode(AbstractTurnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_getFeedbackMode());
}

int  PythonQtWrapper_AbstractTurnout::getFeedbackModeForOperation(AbstractTurnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_getFeedbackModeForOperation());
}

QString  PythonQtWrapper_AbstractTurnout::getFeedbackModeName(AbstractTurnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_getFeedbackModeName());
}

Sensor*  PythonQtWrapper_AbstractTurnout::getFirstSensor(AbstractTurnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_getFirstSensor());
}

bool  PythonQtWrapper_AbstractTurnout::getInhibitOperation(AbstractTurnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_getInhibitOperation());
}

bool  PythonQtWrapper_AbstractTurnout::getInverted(AbstractTurnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_getInverted());
}

int  PythonQtWrapper_AbstractTurnout::getKnownState(AbstractTurnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_getKnownState());
}

bool  PythonQtWrapper_AbstractTurnout::getLocked(AbstractTurnout* theWrappedObject, int  turnoutLockout)
{
  return ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_getLocked(turnoutLockout));
}

int  PythonQtWrapper_AbstractTurnout::getNumberOutputBits(AbstractTurnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_getNumberOutputBits());
}

bool  PythonQtWrapper_AbstractTurnout::getReportLocked(AbstractTurnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_getReportLocked());
}

Sensor*  PythonQtWrapper_AbstractTurnout::getSecondSensor(AbstractTurnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_getSecondSensor());
}

int  PythonQtWrapper_AbstractTurnout::getState(AbstractTurnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_getState());
}

float  PythonQtWrapper_AbstractTurnout::getStraightLimit(AbstractTurnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_getStraightLimit());
}

QString  PythonQtWrapper_AbstractTurnout::getStraightSpeed(AbstractTurnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_getStraightSpeed());
}

QStringList  PythonQtWrapper_AbstractTurnout::getValidDecoderNames(AbstractTurnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_getValidDecoderNames());
}

QStringList  PythonQtWrapper_AbstractTurnout::getValidFeedbackNames(AbstractTurnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_getValidFeedbackNames());
}

int  PythonQtWrapper_AbstractTurnout::getValidFeedbackTypes(AbstractTurnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_getValidFeedbackTypes());
}

bool  PythonQtWrapper_AbstractTurnout::isConsistentState(AbstractTurnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_isConsistentState());
}

void PythonQtWrapper_AbstractTurnout::newCommandedState(AbstractTurnout* theWrappedObject, int  s)
{
  ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_newCommandedState(s));
}

void PythonQtWrapper_AbstractTurnout::newKnownState(AbstractTurnout* theWrappedObject, int  s)
{
  ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_newKnownState(s));
}

void PythonQtWrapper_AbstractTurnout::operationPropertyChange(AbstractTurnout* theWrappedObject, PropertyChangeEvent*  evt)
{
  ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_operationPropertyChange(evt));
}

void PythonQtWrapper_AbstractTurnout::provideFirstFeedbackSensor(AbstractTurnout* theWrappedObject, QString  pName) throw(JmriException)
{
  ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_provideFirstFeedbackSensor(pName));
}

void PythonQtWrapper_AbstractTurnout::provideSecondFeedbackSensor(AbstractTurnout* theWrappedObject, QString  pName) throw(JmriException)
{
  ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_provideSecondFeedbackSensor(pName));
}

void PythonQtWrapper_AbstractTurnout::requestUpdateFromLayout(AbstractTurnout* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_requestUpdateFromLayout());
}

void PythonQtWrapper_AbstractTurnout::sensorPropertyChange(AbstractTurnout* theWrappedObject, PropertyChangeEvent*  evt)
{
  ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_sensorPropertyChange(evt));
}

void PythonQtWrapper_AbstractTurnout::setBinaryOutput(AbstractTurnout* theWrappedObject, bool  state)
{
  ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_setBinaryOutput(state));
}

void PythonQtWrapper_AbstractTurnout::setCommandedState(AbstractTurnout* theWrappedObject, int  s)
{
  ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_setCommandedState(s));
}

void PythonQtWrapper_AbstractTurnout::setControlType(AbstractTurnout* theWrappedObject, int  num)
{
  ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_setControlType(num));
}

void PythonQtWrapper_AbstractTurnout::setDecoderName(AbstractTurnout* theWrappedObject, QString  decoderName)
{
  ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_setDecoderName(decoderName));
}

void PythonQtWrapper_AbstractTurnout::setDivergingSpeed(AbstractTurnout* theWrappedObject, QString  s) throw(JmriException)
{
  ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_setDivergingSpeed(s));
}

void PythonQtWrapper_AbstractTurnout::setFeedbackMode(AbstractTurnout* theWrappedObject, QString  mode) throw(IllegalArgumentException)
{
  ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_setFeedbackMode(mode));
}

void PythonQtWrapper_AbstractTurnout::setFeedbackMode(AbstractTurnout* theWrappedObject, int  mode) throw(IllegalArgumentException)
{
  ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_setFeedbackMode(mode));
}

void PythonQtWrapper_AbstractTurnout::setInhibitOperation(AbstractTurnout* theWrappedObject, bool  io)
{
  ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_setInhibitOperation(io));
}

void PythonQtWrapper_AbstractTurnout::setInitialKnownStateFromFeedback(AbstractTurnout* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_setInitialKnownStateFromFeedback());
}

void PythonQtWrapper_AbstractTurnout::setInverted(AbstractTurnout* theWrappedObject, bool  inverted)
{
  ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_setInverted(inverted));
}

void PythonQtWrapper_AbstractTurnout::setKnownStateToCommanded(AbstractTurnout* theWrappedObject)
{
  ( theWrappedObject->setKnownStateToCommanded());
}

void PythonQtWrapper_AbstractTurnout::setLocked(AbstractTurnout* theWrappedObject, int  turnoutLockout, bool  locked)
{
  ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_setLocked(turnoutLockout, locked));
}

void PythonQtWrapper_AbstractTurnout::setNumberOutputBits(AbstractTurnout* theWrappedObject, int  num)
{
  ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_setNumberOutputBits(num));
}

void PythonQtWrapper_AbstractTurnout::setReportLocked(AbstractTurnout* theWrappedObject, bool  reportLocked)
{
  ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_setReportLocked(reportLocked));
}

void PythonQtWrapper_AbstractTurnout::setState(AbstractTurnout* theWrappedObject, int  s)
{
  ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_setState(s));
}

void PythonQtWrapper_AbstractTurnout::setStraightSpeed(AbstractTurnout* theWrappedObject, QString  s) throw(JmriException)
{
  ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_setStraightSpeed(s));
}

void PythonQtWrapper_AbstractTurnout::turnoutPushbuttonLockout(AbstractTurnout* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_turnoutPushbuttonLockout());
}

void PythonQtWrapper_AbstractTurnout::turnoutPushbuttonLockout(AbstractTurnout* theWrappedObject, bool  locked)
{
  ( ((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->promoted_turnoutPushbuttonLockout(locked));
}



PythonQtShell_AddressedProgrammerManager::~PythonQtShell_AddressedProgrammerManager() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
QString  PythonQtShell_AddressedProgrammerManager::getUserName()
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
  return AddressedProgrammerManager::getUserName();
}
bool  PythonQtShell_AddressedProgrammerManager::isAddressedModePossible()
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
  return AddressedProgrammerManager::isAddressedModePossible();
}
QString  PythonQtShell_AddressedProgrammerManager::toString()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("toString");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("toString", methodInfo, result);
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
  return AddressedProgrammerManager::toString();
}
AddressedProgrammerManager* PythonQtWrapper_AddressedProgrammerManager::new_AddressedProgrammerManager(QObject*  parent)
{ 
return new PythonQtShell_AddressedProgrammerManager(parent); }

QString  PythonQtWrapper_AddressedProgrammerManager::getUserName(AddressedProgrammerManager* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AddressedProgrammerManager*)theWrappedObject)->promoted_getUserName());
}

bool  PythonQtWrapper_AddressedProgrammerManager::isAddressedModePossible(AddressedProgrammerManager* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AddressedProgrammerManager*)theWrappedObject)->promoted_isAddressedModePossible());
}

QString  PythonQtWrapper_AddressedProgrammerManager::toString(AddressedProgrammerManager* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AddressedProgrammerManager*)theWrappedObject)->promoted_toString());
}

QString PythonQtWrapper_AddressedProgrammerManager::py_toString(AddressedProgrammerManager* obj) { return obj->toString(); }


PythonQtShell_Audio::~PythonQtShell_Audio() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
QChar  PythonQtShell_Audio::getSubType()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSubType");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QChar"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QChar returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSubType", methodInfo, result);
        } else {
          returnValue = *((QChar*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return Audio::getSubType();
}
void PythonQtShell_Audio::stateChanged(int  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("stateChanged");
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
  Audio::stateChanged(arg__1);
}
QString  PythonQtShell_Audio::toString()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("toString");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("toString", methodInfo, result);
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
  return Audio::toString();
}
Audio* PythonQtWrapper_Audio::new_Audio(QString  systemName, QObject*  parent)
{ 
return new PythonQtShell_Audio(systemName, parent); }

Audio* PythonQtWrapper_Audio::new_Audio(QString  systemName, QString  userName, QObject*  parent)
{ 
return new PythonQtShell_Audio(systemName, userName, parent); }

QChar  PythonQtWrapper_Audio::getSubType(Audio* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Audio*)theWrappedObject)->promoted_getSubType());
}

void PythonQtWrapper_Audio::stateChanged(Audio* theWrappedObject, int  arg__1)
{
  ( ((PythonQtPublicPromoter_Audio*)theWrappedObject)->promoted_stateChanged(arg__1));
}

QString  PythonQtWrapper_Audio::toString(Audio* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Audio*)theWrappedObject)->promoted_toString());
}

QString PythonQtWrapper_Audio::py_toString(Audio* obj) { return obj->toString(); }


PythonQtShell_AudioBuffer::~PythonQtShell_AudioBuffer() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
long  PythonQtShell_AudioBuffer::getEndLoopPoint()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getEndLoopPoint");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getEndLoopPoint", methodInfo, result);
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
  return AudioBuffer::getEndLoopPoint();
}
int  PythonQtShell_AudioBuffer::getFormat()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getFormat");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getFormat", methodInfo, result);
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
  return AudioBuffer::getFormat();
}
int  PythonQtShell_AudioBuffer::getFrameSize()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getFrameSize");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getFrameSize", methodInfo, result);
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
  return AudioBuffer::getFrameSize();
}
int  PythonQtShell_AudioBuffer::getFrequency()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getFrequency");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getFrequency", methodInfo, result);
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
  return AudioBuffer::getFrequency();
}
long  PythonQtShell_AudioBuffer::getLength()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getLength");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getLength", methodInfo, result);
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
  return AudioBuffer::getLength();
}
long  PythonQtShell_AudioBuffer::getStartLoopPoint()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getStartLoopPoint");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getStartLoopPoint", methodInfo, result);
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
  return AudioBuffer::getStartLoopPoint();
}
QChar  PythonQtShell_AudioBuffer::getSubType()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSubType");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QChar"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QChar returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSubType", methodInfo, result);
        } else {
          returnValue = *((QChar*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return AudioBuffer::getSubType();
}
QString  PythonQtShell_AudioBuffer::getURL()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getURL");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getURL", methodInfo, result);
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
  return AudioBuffer::getURL();
}
bool  PythonQtShell_AudioBuffer::isStreamed()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("isStreamed");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("isStreamed", methodInfo, result);
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
  return AudioBuffer::isStreamed();
}
bool  PythonQtShell_AudioBuffer::isStreamedForced()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("isStreamedForced");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("isStreamedForced", methodInfo, result);
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
  return AudioBuffer::isStreamedForced();
}
void PythonQtShell_AudioBuffer::setEndLoopPoint(long  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setEndLoopPoint");
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
  AudioBuffer::setEndLoopPoint(arg__1);
}
void PythonQtShell_AudioBuffer::setInputStream(QDataStream*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setInputStream");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QDataStream*"};
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
  AudioBuffer::setInputStream(arg__1);
}
void PythonQtShell_AudioBuffer::setStartLoopPoint(long  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setStartLoopPoint");
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
  AudioBuffer::setStartLoopPoint(arg__1);
}
void PythonQtShell_AudioBuffer::setStreamed(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setStreamed");
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
  AudioBuffer::setStreamed(arg__1);
}
void PythonQtShell_AudioBuffer::setURL(QString  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setURL");
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
  AudioBuffer::setURL(arg__1);
}
void PythonQtShell_AudioBuffer::stateChanged(int  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("stateChanged");
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
  AudioBuffer::stateChanged(arg__1);
}
QString  PythonQtShell_AudioBuffer::toString()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("toString");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("toString", methodInfo, result);
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
  return AudioBuffer::toString();
}
AudioBuffer* PythonQtWrapper_AudioBuffer::new_AudioBuffer(QString  systemName, QObject*  parent)
{ 
return new PythonQtShell_AudioBuffer(systemName, parent); }

AudioBuffer* PythonQtWrapper_AudioBuffer::new_AudioBuffer(QString  systemName, QString  userName, QObject*  parent)
{ 
return new PythonQtShell_AudioBuffer(systemName, userName, parent); }

long  PythonQtWrapper_AudioBuffer::getEndLoopPoint(AudioBuffer* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioBuffer*)theWrappedObject)->promoted_getEndLoopPoint());
}

int  PythonQtWrapper_AudioBuffer::getFormat(AudioBuffer* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioBuffer*)theWrappedObject)->promoted_getFormat());
}

int  PythonQtWrapper_AudioBuffer::getFrameSize(AudioBuffer* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioBuffer*)theWrappedObject)->promoted_getFrameSize());
}

int  PythonQtWrapper_AudioBuffer::getFrequency(AudioBuffer* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioBuffer*)theWrappedObject)->promoted_getFrequency());
}

long  PythonQtWrapper_AudioBuffer::getLength(AudioBuffer* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioBuffer*)theWrappedObject)->promoted_getLength());
}

long  PythonQtWrapper_AudioBuffer::getStartLoopPoint(AudioBuffer* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioBuffer*)theWrappedObject)->promoted_getStartLoopPoint());
}

QString  PythonQtWrapper_AudioBuffer::getURL(AudioBuffer* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioBuffer*)theWrappedObject)->promoted_getURL());
}

bool  PythonQtWrapper_AudioBuffer::isStreamed(AudioBuffer* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioBuffer*)theWrappedObject)->promoted_isStreamed());
}

bool  PythonQtWrapper_AudioBuffer::isStreamedForced(AudioBuffer* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioBuffer*)theWrappedObject)->promoted_isStreamedForced());
}

void PythonQtWrapper_AudioBuffer::setEndLoopPoint(AudioBuffer* theWrappedObject, long  arg__1)
{
  ( ((PythonQtPublicPromoter_AudioBuffer*)theWrappedObject)->promoted_setEndLoopPoint(arg__1));
}

void PythonQtWrapper_AudioBuffer::setInputStream(AudioBuffer* theWrappedObject, QDataStream*  arg__1)
{
  ( ((PythonQtPublicPromoter_AudioBuffer*)theWrappedObject)->promoted_setInputStream(arg__1));
}

void PythonQtWrapper_AudioBuffer::setStartLoopPoint(AudioBuffer* theWrappedObject, long  arg__1)
{
  ( ((PythonQtPublicPromoter_AudioBuffer*)theWrappedObject)->promoted_setStartLoopPoint(arg__1));
}

void PythonQtWrapper_AudioBuffer::setStreamed(AudioBuffer* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_AudioBuffer*)theWrappedObject)->promoted_setStreamed(arg__1));
}

void PythonQtWrapper_AudioBuffer::setURL(AudioBuffer* theWrappedObject, QString  arg__1)
{
  ( ((PythonQtPublicPromoter_AudioBuffer*)theWrappedObject)->promoted_setURL(arg__1));
}

QString PythonQtWrapper_AudioBuffer::py_toString(AudioBuffer* obj) { return obj->toString(); }


PythonQtShell_AudioListener::~PythonQtShell_AudioListener() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
QVector3D  PythonQtShell_AudioListener::getCurrentOrientation(int  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getCurrentOrientation");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QVector3D" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      QVector3D returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getCurrentOrientation", methodInfo, result);
        } else {
          returnValue = *((QVector3D*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return AudioListener::getCurrentOrientation(arg__1);
}
QVector3D  PythonQtShell_AudioListener::getCurrentPosition()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getCurrentPosition");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QVector3D"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QVector3D returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getCurrentPosition", methodInfo, result);
        } else {
          returnValue = *((QVector3D*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return AudioListener::getCurrentPosition();
}
float  PythonQtShell_AudioListener::getGain()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getGain");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getGain", methodInfo, result);
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
  return AudioListener::getGain();
}
float  PythonQtShell_AudioListener::getMetersPerUnit()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getMetersPerUnit");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getMetersPerUnit", methodInfo, result);
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
  return AudioListener::getMetersPerUnit();
}
QVector3D  PythonQtShell_AudioListener::getOrientation(int  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getOrientation");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QVector3D" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      QVector3D returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getOrientation", methodInfo, result);
        } else {
          returnValue = *((QVector3D*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return AudioListener::getOrientation(arg__1);
}
QVector3D  PythonQtShell_AudioListener::getPosition()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getPosition");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QVector3D"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QVector3D returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getPosition", methodInfo, result);
        } else {
          returnValue = *((QVector3D*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return AudioListener::getPosition();
}
QChar  PythonQtShell_AudioListener::getSubType()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSubType");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QChar"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QChar returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSubType", methodInfo, result);
        } else {
          returnValue = *((QChar*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return AudioListener::getSubType();
}
QVector3D  PythonQtShell_AudioListener::getVelocity()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getVelocity");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QVector3D"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QVector3D returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getVelocity", methodInfo, result);
        } else {
          returnValue = *((QVector3D*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return AudioListener::getVelocity();
}
void PythonQtShell_AudioListener::resetCurrentPosition()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("resetCurrentPosition");
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
  AudioListener::resetCurrentPosition();
}
void PythonQtShell_AudioListener::setGain(float  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setGain");
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
  AudioListener::setGain(arg__1);
}
void PythonQtShell_AudioListener::setMetersPerUnit(float  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setMetersPerUnit");
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
  AudioListener::setMetersPerUnit(arg__1);
}
void PythonQtShell_AudioListener::setOrientation(QVector3D  arg__1, QVector3D  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setOrientation");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QVector3D" , "QVector3D"};
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
  AudioListener::setOrientation(arg__1, arg__2);
}
void PythonQtShell_AudioListener::setPosition(QVector3D  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setPosition");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QVector3D"};
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
  AudioListener::setPosition(arg__1);
}
void PythonQtShell_AudioListener::setPosition(float  arg__1, float  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setPosition");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "float" , "float"};
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
  AudioListener::setPosition(arg__1, arg__2);
}
void PythonQtShell_AudioListener::setPosition(float  arg__1, float  arg__2, float  arg__3)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setPosition");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "float" , "float" , "float"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(4, argumentList);
    void* args[4] = {NULL, (void*)&arg__1, (void*)&arg__2, (void*)&arg__3};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  AudioListener::setPosition(arg__1, arg__2, arg__3);
}
void PythonQtShell_AudioListener::setVelocity(QVector3D  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setVelocity");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QVector3D"};
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
  AudioListener::setVelocity(arg__1);
}
void PythonQtShell_AudioListener::stateChanged(int  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("stateChanged");
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
  AudioListener::stateChanged(arg__1);
}
QString  PythonQtShell_AudioListener::toString()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("toString");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("toString", methodInfo, result);
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
  return AudioListener::toString();
}
AudioListener* PythonQtWrapper_AudioListener::new_AudioListener(QObject*  parent)
{ 
return new PythonQtShell_AudioListener(parent); }

AudioListener* PythonQtWrapper_AudioListener::new_AudioListener(QString  systemName, QObject*  parent)
{ 
return new PythonQtShell_AudioListener(systemName, parent); }

AudioListener* PythonQtWrapper_AudioListener::new_AudioListener(QString  systemName, QString  userName, QObject*  parent)
{ 
return new PythonQtShell_AudioListener(systemName, userName, parent); }

QVector3D  PythonQtWrapper_AudioListener::getCurrentOrientation(AudioListener* theWrappedObject, int  arg__1)
{
  return ( ((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->promoted_getCurrentOrientation(arg__1));
}

QVector3D  PythonQtWrapper_AudioListener::getCurrentPosition(AudioListener* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->promoted_getCurrentPosition());
}

float  PythonQtWrapper_AudioListener::getGain(AudioListener* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->promoted_getGain());
}

float  PythonQtWrapper_AudioListener::getMetersPerUnit(AudioListener* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->promoted_getMetersPerUnit());
}

QVector3D  PythonQtWrapper_AudioListener::getOrientation(AudioListener* theWrappedObject, int  arg__1)
{
  return ( ((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->promoted_getOrientation(arg__1));
}

QVector3D  PythonQtWrapper_AudioListener::getPosition(AudioListener* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->promoted_getPosition());
}

QVector3D  PythonQtWrapper_AudioListener::getVelocity(AudioListener* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->promoted_getVelocity());
}

void PythonQtWrapper_AudioListener::resetCurrentPosition(AudioListener* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->promoted_resetCurrentPosition());
}

void PythonQtWrapper_AudioListener::setGain(AudioListener* theWrappedObject, float  arg__1)
{
  ( ((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->promoted_setGain(arg__1));
}

void PythonQtWrapper_AudioListener::setMetersPerUnit(AudioListener* theWrappedObject, float  arg__1)
{
  ( ((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->promoted_setMetersPerUnit(arg__1));
}

void PythonQtWrapper_AudioListener::setOrientation(AudioListener* theWrappedObject, QVector3D  arg__1, QVector3D  arg__2)
{
  ( ((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->promoted_setOrientation(arg__1, arg__2));
}

void PythonQtWrapper_AudioListener::setPosition(AudioListener* theWrappedObject, QVector3D  arg__1)
{
  ( ((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->promoted_setPosition(arg__1));
}

void PythonQtWrapper_AudioListener::setPosition(AudioListener* theWrappedObject, float  arg__1, float  arg__2)
{
  ( ((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->promoted_setPosition(arg__1, arg__2));
}

void PythonQtWrapper_AudioListener::setPosition(AudioListener* theWrappedObject, float  arg__1, float  arg__2, float  arg__3)
{
  ( ((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->promoted_setPosition(arg__1, arg__2, arg__3));
}

void PythonQtWrapper_AudioListener::setVelocity(AudioListener* theWrappedObject, QVector3D  arg__1)
{
  ( ((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->promoted_setVelocity(arg__1));
}

QString PythonQtWrapper_AudioListener::py_toString(AudioListener* obj) { return obj->toString(); }


PythonQtShell_AudioManager::~PythonQtShell_AudioManager() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_AudioManager::Register(NamedBean*  s0)
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
  AudioManager::Register(s0);
}
void PythonQtShell_AudioManager::addPropertyChangeListener(PropertyChangeListener*  l0)
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
  AudioManager::addPropertyChangeListener(l0);
}
void PythonQtShell_AudioManager::cleanup()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("cleanup");
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
  AudioManager::cleanup();
}
void PythonQtShell_AudioManager::deregister(NamedBean*  s0)
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
  AudioManager::deregister(s0);
}
void PythonQtShell_AudioManager::dispose()
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
  AudioManager::dispose();
}
Audio*  PythonQtShell_AudioManager::getAudio(QString  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getAudio");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"Audio*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      Audio* returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getAudio", methodInfo, result);
        } else {
          returnValue = *((Audio**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return AudioManager::getAudio(arg__1);
}
NamedBean*  PythonQtShell_AudioManager::getBeanBySystemName(QString  systemName0)
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
  return AudioManager::getBeanBySystemName(systemName0);
}
NamedBean*  PythonQtShell_AudioManager::getBeanByUserName(QString  userName0)
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
  return AudioManager::getBeanByUserName(userName0);
}
Audio*  PythonQtShell_AudioManager::getBySystemName(QString  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getBySystemName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"Audio*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      Audio* returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getBySystemName", methodInfo, result);
        } else {
          returnValue = *((Audio**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return AudioManager::getBySystemName(arg__1);
}
Audio*  PythonQtShell_AudioManager::getByUserName(QString  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getByUserName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"Audio*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      Audio* returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getByUserName", methodInfo, result);
        } else {
          returnValue = *((Audio**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return AudioManager::getByUserName(arg__1);
}
NamedBean*  PythonQtShell_AudioManager::getNamedBean(QString  name0)
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
  return AudioManager::getNamedBean(name0);
}
QStringList  PythonQtShell_AudioManager::getSystemNameArray()
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
  return AudioManager::getSystemNameArray();
}
QStringList  PythonQtShell_AudioManager::getSystemNameList()
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
  return AudioManager::getSystemNameList();
}
QStringList  PythonQtShell_AudioManager::getSystemNameList(QChar  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemNameList");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QStringList" , "QChar"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      QStringList returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
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
  return AudioManager::getSystemNameList(arg__1);
}
QStringList  PythonQtShell_AudioManager::getSystemNameList(char  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSystemNameList");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QStringList" , "char"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      QStringList returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
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
  return AudioManager::getSystemNameList(arg__1);
}
void PythonQtShell_AudioManager::init()
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
  AudioManager::init();
}
QString  PythonQtShell_AudioManager::makeSystemName(QString  s0)
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
  return AudioManager::makeSystemName(s0);
}
Audio*  PythonQtShell_AudioManager::newAudio(QString  arg__1, QString  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("newAudio");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"Audio*" , "QString" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
      Audio* returnValue;
    void* args[3] = {NULL, (void*)&arg__1, (void*)&arg__2};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("newAudio", methodInfo, result);
        } else {
          returnValue = *((Audio**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return AudioManager::newAudio(arg__1, arg__2);
}
void PythonQtShell_AudioManager::propertyChange(PropertyChangeEvent*  e0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("propertyChange");
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
  AudioManager::propertyChange(e0);
}
Audio*  PythonQtShell_AudioManager::provideAudio(QString  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("provideAudio");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"Audio*" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      Audio* returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("provideAudio", methodInfo, result);
        } else {
          returnValue = *((Audio**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return AudioManager::provideAudio(arg__1);
}
void PythonQtShell_AudioManager::removePropertyChangeListener(PropertyChangeListener*  l0)
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
  AudioManager::removePropertyChangeListener(l0);
}
void PythonQtShell_AudioManager::vetoableChange(PropertyChangeEvent*  evt0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("vetoableChange");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&evt0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  AudioManager::vetoableChange(evt0);
}
AudioManager* PythonQtWrapper_AudioManager::new_AudioManager(QObject*  parent)
{ 
return new PythonQtShell_AudioManager(parent); }

void PythonQtWrapper_AudioManager::cleanup(AudioManager* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_AudioManager*)theWrappedObject)->promoted_cleanup());
}

Audio*  PythonQtWrapper_AudioManager::getAudio(AudioManager* theWrappedObject, QString  arg__1)
{
  return ( ((PythonQtPublicPromoter_AudioManager*)theWrappedObject)->promoted_getAudio(arg__1));
}

Audio*  PythonQtWrapper_AudioManager::getBySystemName(AudioManager* theWrappedObject, QString  arg__1)
{
  return ( ((PythonQtPublicPromoter_AudioManager*)theWrappedObject)->promoted_getBySystemName(arg__1));
}

Audio*  PythonQtWrapper_AudioManager::getByUserName(AudioManager* theWrappedObject, QString  arg__1)
{
  return ( ((PythonQtPublicPromoter_AudioManager*)theWrappedObject)->promoted_getByUserName(arg__1));
}

QStringList  PythonQtWrapper_AudioManager::getSystemNameList(AudioManager* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioManager*)theWrappedObject)->promoted_getSystemNameList());
}

QStringList  PythonQtWrapper_AudioManager::getSystemNameList(AudioManager* theWrappedObject, QChar  arg__1)
{
  return ( ((PythonQtPublicPromoter_AudioManager*)theWrappedObject)->promoted_getSystemNameList(arg__1));
}

QStringList  PythonQtWrapper_AudioManager::getSystemNameList(AudioManager* theWrappedObject, char  arg__1)
{
  return ( ((PythonQtPublicPromoter_AudioManager*)theWrappedObject)->promoted_getSystemNameList(arg__1));
}

void PythonQtWrapper_AudioManager::init(AudioManager* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_AudioManager*)theWrappedObject)->promoted_init());
}

Audio*  PythonQtWrapper_AudioManager::newAudio(AudioManager* theWrappedObject, QString  arg__1, QString  arg__2)
{
  return ( ((PythonQtPublicPromoter_AudioManager*)theWrappedObject)->promoted_newAudio(arg__1, arg__2));
}

Audio*  PythonQtWrapper_AudioManager::provideAudio(AudioManager* theWrappedObject, QString  arg__1)
{
  return ( ((PythonQtPublicPromoter_AudioManager*)theWrappedObject)->promoted_provideAudio(arg__1));
}



PythonQtShell_AudioSource::~PythonQtShell_AudioSource() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_AudioSource::fadeIn()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("fadeIn");
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
  AudioSource::fadeIn();
}
void PythonQtShell_AudioSource::fadeOut()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("fadeOut");
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
  AudioSource::fadeOut();
}
AudioBuffer*  PythonQtShell_AudioSource::getAssignedBuffer()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getAssignedBuffer");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"AudioBuffer*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      AudioBuffer* returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getAssignedBuffer", methodInfo, result);
        } else {
          returnValue = *((AudioBuffer**)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return AudioSource::getAssignedBuffer();
}
QString  PythonQtShell_AudioSource::getAssignedBufferName()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getAssignedBufferName");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getAssignedBufferName", methodInfo, result);
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
  return AudioSource::getAssignedBufferName();
}
QVector3D  PythonQtShell_AudioSource::getCurrentPosition()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getCurrentPosition");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QVector3D"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QVector3D returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getCurrentPosition", methodInfo, result);
        } else {
          returnValue = *((QVector3D*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return AudioSource::getCurrentPosition();
}
int  PythonQtShell_AudioSource::getFadeIn()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getFadeIn");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getFadeIn", methodInfo, result);
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
  return AudioSource::getFadeIn();
}
int  PythonQtShell_AudioSource::getFadeOut()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getFadeOut");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getFadeOut", methodInfo, result);
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
  return AudioSource::getFadeOut();
}
float  PythonQtShell_AudioSource::getGain()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getGain");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getGain", methodInfo, result);
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
  return AudioSource::getGain();
}
int  PythonQtShell_AudioSource::getMaxLoops()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getMaxLoops");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getMaxLoops", methodInfo, result);
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
  return AudioSource::getMaxLoops();
}
float  PythonQtShell_AudioSource::getMaximumDistance()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getMaximumDistance");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getMaximumDistance", methodInfo, result);
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
  return AudioSource::getMaximumDistance();
}
int  PythonQtShell_AudioSource::getMinLoops()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getMinLoops");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getMinLoops", methodInfo, result);
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
  return AudioSource::getMinLoops();
}
int  PythonQtShell_AudioSource::getNumLoops()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNumLoops");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getNumLoops", methodInfo, result);
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
  return AudioSource::getNumLoops();
}
float  PythonQtShell_AudioSource::getPitch()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getPitch");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getPitch", methodInfo, result);
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
  return AudioSource::getPitch();
}
QVector3D  PythonQtShell_AudioSource::getPosition()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getPosition");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QVector3D"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QVector3D returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getPosition", methodInfo, result);
        } else {
          returnValue = *((QVector3D*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return AudioSource::getPosition();
}
float  PythonQtShell_AudioSource::getReferenceDistance()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getReferenceDistance");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getReferenceDistance", methodInfo, result);
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
  return AudioSource::getReferenceDistance();
}
float  PythonQtShell_AudioSource::getRollOffFactor()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getRollOffFactor");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getRollOffFactor", methodInfo, result);
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
  return AudioSource::getRollOffFactor();
}
QChar  PythonQtShell_AudioSource::getSubType()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSubType");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QChar"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QChar returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getSubType", methodInfo, result);
        } else {
          returnValue = *((QChar*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return AudioSource::getSubType();
}
QVector3D  PythonQtShell_AudioSource::getVelocity()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getVelocity");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"QVector3D"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(1, argumentList);
      QVector3D returnValue;
    void* args[1] = {NULL};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("getVelocity", methodInfo, result);
        } else {
          returnValue = *((QVector3D*)args[0]);
        }
      }
    }
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return returnValue;
  } else {
    PyErr_Clear();
  }
}
  return AudioSource::getVelocity();
}
bool  PythonQtShell_AudioSource::isBound()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("isBound");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("isBound", methodInfo, result);
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
  return AudioSource::isBound();
}
bool  PythonQtShell_AudioSource::isLooped()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("isLooped");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("isLooped", methodInfo, result);
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
  return AudioSource::isLooped();
}
bool  PythonQtShell_AudioSource::isPositionRelative()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("isPositionRelative");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("isPositionRelative", methodInfo, result);
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
  return AudioSource::isPositionRelative();
}
bool  PythonQtShell_AudioSource::isQueued()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("isQueued");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("isQueued", methodInfo, result);
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
  return AudioSource::isQueued();
}
int  PythonQtShell_AudioSource::numProcessedBuffers()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("numProcessedBuffers");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("numProcessedBuffers", methodInfo, result);
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
  return AudioSource::numProcessedBuffers();
}
int  PythonQtShell_AudioSource::numQueuedBuffers()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("numQueuedBuffers");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("numQueuedBuffers", methodInfo, result);
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
  return AudioSource::numQueuedBuffers();
}
void PythonQtShell_AudioSource::pause()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("pause");
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
  AudioSource::pause();
}
void PythonQtShell_AudioSource::play()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("play");
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
  AudioSource::play();
}
bool  PythonQtShell_AudioSource::queueBuffer(AudioBuffer*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("queueBuffer");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "AudioBuffer*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("queueBuffer", methodInfo, result);
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
  return AudioSource::queueBuffer(arg__1);
}
bool  PythonQtShell_AudioSource::queueBuffers(QQueue<AudioBuffer* >  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("queueBuffers");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "QQueue<AudioBuffer* >"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&arg__1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) {
      args[0] = PythonQtConv::ConvertPythonToQt(methodInfo->parameters().at(0), result, false, NULL, &returnValue);
      if (args[0]!=&returnValue) {
        if (args[0]==NULL) {
          PythonQt::priv()->handleVirtualOverloadReturnError("queueBuffers", methodInfo, result);
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
  return AudioSource::queueBuffers(arg__1);
}
void PythonQtShell_AudioSource::resetCurrentPosition()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("resetCurrentPosition");
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
  AudioSource::resetCurrentPosition();
}
void PythonQtShell_AudioSource::resume()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("resume");
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
  AudioSource::resume();
}
void PythonQtShell_AudioSource::rewind()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("rewind");
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
  AudioSource::rewind();
}
void PythonQtShell_AudioSource::setAssignedBuffer(AudioBuffer*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setAssignedBuffer");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "AudioBuffer*"};
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
  AudioSource::setAssignedBuffer(arg__1);
}
void PythonQtShell_AudioSource::setAssignedBuffer(QString  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setAssignedBuffer");
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
  AudioSource::setAssignedBuffer(arg__1);
}
void PythonQtShell_AudioSource::setFadeIn(int  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setFadeIn");
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
  AudioSource::setFadeIn(arg__1);
}
void PythonQtShell_AudioSource::setFadeOut(int  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setFadeOut");
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
  AudioSource::setFadeOut(arg__1);
}
void PythonQtShell_AudioSource::setGain(float  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setGain");
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
  AudioSource::setGain(arg__1);
}
void PythonQtShell_AudioSource::setLooped(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setLooped");
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
  AudioSource::setLooped(arg__1);
}
void PythonQtShell_AudioSource::setMaxLoops(int  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setMaxLoops");
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
  AudioSource::setMaxLoops(arg__1);
}
void PythonQtShell_AudioSource::setMaximumDistance(float  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setMaximumDistance");
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
  AudioSource::setMaximumDistance(arg__1);
}
void PythonQtShell_AudioSource::setMinLoops(int  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setMinLoops");
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
  AudioSource::setMinLoops(arg__1);
}
void PythonQtShell_AudioSource::setPitch(float  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setPitch");
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
  AudioSource::setPitch(arg__1);
}
void PythonQtShell_AudioSource::setPosition(QVector3D  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setPosition");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QVector3D"};
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
  AudioSource::setPosition(arg__1);
}
void PythonQtShell_AudioSource::setPosition(float  arg__1, float  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setPosition");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "float" , "float"};
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
  AudioSource::setPosition(arg__1, arg__2);
}
void PythonQtShell_AudioSource::setPosition(float  arg__1, float  arg__2, float  arg__3)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setPosition");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "float" , "float" , "float"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(4, argumentList);
    void* args[4] = {NULL, (void*)&arg__1, (void*)&arg__2, (void*)&arg__3};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  AudioSource::setPosition(arg__1, arg__2, arg__3);
}
void PythonQtShell_AudioSource::setPositionRelative(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setPositionRelative");
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
  AudioSource::setPositionRelative(arg__1);
}
void PythonQtShell_AudioSource::setReferenceDistance(float  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setReferenceDistance");
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
  AudioSource::setReferenceDistance(arg__1);
}
void PythonQtShell_AudioSource::setRollOffFactor(float  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setRollOffFactor");
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
  AudioSource::setRollOffFactor(arg__1);
}
void PythonQtShell_AudioSource::setVelocity(QVector3D  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setVelocity");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QVector3D"};
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
  AudioSource::setVelocity(arg__1);
}
void PythonQtShell_AudioSource::stateChanged(int  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("stateChanged");
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
  AudioSource::stateChanged(arg__1);
}
void PythonQtShell_AudioSource::stop()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("stop");
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
  AudioSource::stop();
}
QString  PythonQtShell_AudioSource::toString()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("toString");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("toString", methodInfo, result);
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
  return AudioSource::toString();
}
void PythonQtShell_AudioSource::togglePause()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("togglePause");
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
  AudioSource::togglePause();
}
void PythonQtShell_AudioSource::togglePlay()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("togglePlay");
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
  AudioSource::togglePlay();
}
bool  PythonQtShell_AudioSource::unqueueBuffers()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("unqueueBuffers");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("unqueueBuffers", methodInfo, result);
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
  return AudioSource::unqueueBuffers();
}
AudioSource* PythonQtWrapper_AudioSource::new_AudioSource(QObject*  parent)
{ 
return new PythonQtShell_AudioSource(parent); }

AudioSource* PythonQtWrapper_AudioSource::new_AudioSource(QString  systemName, QObject*  parent)
{ 
return new PythonQtShell_AudioSource(systemName, parent); }

AudioSource* PythonQtWrapper_AudioSource::new_AudioSource(QString  systemName, QString  userName, QObject*  parent)
{ 
return new PythonQtShell_AudioSource(systemName, userName, parent); }

void PythonQtWrapper_AudioSource::fadeIn(AudioSource* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_fadeIn());
}

void PythonQtWrapper_AudioSource::fadeOut(AudioSource* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_fadeOut());
}

AudioBuffer*  PythonQtWrapper_AudioSource::getAssignedBuffer(AudioSource* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_getAssignedBuffer());
}

QString  PythonQtWrapper_AudioSource::getAssignedBufferName(AudioSource* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_getAssignedBufferName());
}

QVector3D  PythonQtWrapper_AudioSource::getCurrentPosition(AudioSource* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_getCurrentPosition());
}

float  PythonQtWrapper_AudioSource::getDopplerFactor(AudioSource* theWrappedObject)
{
  return ( theWrappedObject->getDopplerFactor());
}

int  PythonQtWrapper_AudioSource::getFadeIn(AudioSource* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_getFadeIn());
}

int  PythonQtWrapper_AudioSource::getFadeOut(AudioSource* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_getFadeOut());
}

float  PythonQtWrapper_AudioSource::getGain(AudioSource* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_getGain());
}

int  PythonQtWrapper_AudioSource::getMaxLoops(AudioSource* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_getMaxLoops());
}

float  PythonQtWrapper_AudioSource::getMaximumDistance(AudioSource* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_getMaximumDistance());
}

int  PythonQtWrapper_AudioSource::getMinLoops(AudioSource* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_getMinLoops());
}

int  PythonQtWrapper_AudioSource::getNumLoops(AudioSource* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_getNumLoops());
}

float  PythonQtWrapper_AudioSource::getPitch(AudioSource* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_getPitch());
}

QVector3D  PythonQtWrapper_AudioSource::getPosition(AudioSource* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_getPosition());
}

float  PythonQtWrapper_AudioSource::getReferenceDistance(AudioSource* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_getReferenceDistance());
}

float  PythonQtWrapper_AudioSource::getRollOffFactor(AudioSource* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_getRollOffFactor());
}

QVector3D  PythonQtWrapper_AudioSource::getVelocity(AudioSource* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_getVelocity());
}

bool  PythonQtWrapper_AudioSource::isBound(AudioSource* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_isBound());
}

bool  PythonQtWrapper_AudioSource::isLooped(AudioSource* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_isLooped());
}

bool  PythonQtWrapper_AudioSource::isPositionRelative(AudioSource* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_isPositionRelative());
}

bool  PythonQtWrapper_AudioSource::isQueued(AudioSource* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_isQueued());
}

int  PythonQtWrapper_AudioSource::numProcessedBuffers(AudioSource* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_numProcessedBuffers());
}

int  PythonQtWrapper_AudioSource::numQueuedBuffers(AudioSource* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_numQueuedBuffers());
}

void PythonQtWrapper_AudioSource::pause(AudioSource* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_pause());
}

void PythonQtWrapper_AudioSource::play(AudioSource* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_play());
}

bool  PythonQtWrapper_AudioSource::queueBuffer(AudioSource* theWrappedObject, AudioBuffer*  arg__1)
{
  return ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_queueBuffer(arg__1));
}

bool  PythonQtWrapper_AudioSource::queueBuffers(AudioSource* theWrappedObject, QQueue<AudioBuffer* >  arg__1)
{
  return ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_queueBuffers(arg__1));
}

void PythonQtWrapper_AudioSource::resetCurrentPosition(AudioSource* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_resetCurrentPosition());
}

void PythonQtWrapper_AudioSource::resume(AudioSource* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_resume());
}

void PythonQtWrapper_AudioSource::rewind(AudioSource* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_rewind());
}

void PythonQtWrapper_AudioSource::setAssignedBuffer(AudioSource* theWrappedObject, AudioBuffer*  arg__1)
{
  ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_setAssignedBuffer(arg__1));
}

void PythonQtWrapper_AudioSource::setAssignedBuffer(AudioSource* theWrappedObject, QString  arg__1)
{
  ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_setAssignedBuffer(arg__1));
}

void PythonQtWrapper_AudioSource::setDopplerFactor(AudioSource* theWrappedObject, float  arg__1)
{
  ( theWrappedObject->setDopplerFactor(arg__1));
}

void PythonQtWrapper_AudioSource::setFadeIn(AudioSource* theWrappedObject, int  arg__1)
{
  ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_setFadeIn(arg__1));
}

void PythonQtWrapper_AudioSource::setFadeOut(AudioSource* theWrappedObject, int  arg__1)
{
  ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_setFadeOut(arg__1));
}

void PythonQtWrapper_AudioSource::setGain(AudioSource* theWrappedObject, float  arg__1)
{
  ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_setGain(arg__1));
}

void PythonQtWrapper_AudioSource::setLooped(AudioSource* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_setLooped(arg__1));
}

void PythonQtWrapper_AudioSource::setMaxLoops(AudioSource* theWrappedObject, int  arg__1)
{
  ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_setMaxLoops(arg__1));
}

void PythonQtWrapper_AudioSource::setMaximumDistance(AudioSource* theWrappedObject, float  arg__1)
{
  ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_setMaximumDistance(arg__1));
}

void PythonQtWrapper_AudioSource::setMinLoops(AudioSource* theWrappedObject, int  arg__1)
{
  ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_setMinLoops(arg__1));
}

void PythonQtWrapper_AudioSource::setPitch(AudioSource* theWrappedObject, float  arg__1)
{
  ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_setPitch(arg__1));
}

void PythonQtWrapper_AudioSource::setPosition(AudioSource* theWrappedObject, QVector3D  arg__1)
{
  ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_setPosition(arg__1));
}

void PythonQtWrapper_AudioSource::setPosition(AudioSource* theWrappedObject, float  arg__1, float  arg__2)
{
  ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_setPosition(arg__1, arg__2));
}

void PythonQtWrapper_AudioSource::setPosition(AudioSource* theWrappedObject, float  arg__1, float  arg__2, float  arg__3)
{
  ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_setPosition(arg__1, arg__2, arg__3));
}

void PythonQtWrapper_AudioSource::setPositionRelative(AudioSource* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_setPositionRelative(arg__1));
}

void PythonQtWrapper_AudioSource::setReferenceDistance(AudioSource* theWrappedObject, float  arg__1)
{
  ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_setReferenceDistance(arg__1));
}

void PythonQtWrapper_AudioSource::setRollOffFactor(AudioSource* theWrappedObject, float  arg__1)
{
  ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_setRollOffFactor(arg__1));
}

void PythonQtWrapper_AudioSource::setVelocity(AudioSource* theWrappedObject, QVector3D  arg__1)
{
  ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_setVelocity(arg__1));
}

void PythonQtWrapper_AudioSource::stop(AudioSource* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_stop());
}

void PythonQtWrapper_AudioSource::togglePause(AudioSource* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_togglePause());
}

void PythonQtWrapper_AudioSource::togglePlay(AudioSource* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_togglePlay());
}

bool  PythonQtWrapper_AudioSource::unqueueBuffers(AudioSource* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->promoted_unqueueBuffers());
}

QString PythonQtWrapper_AudioSource::py_toString(AudioSource* obj) { return obj->toString(); }


PythonQtShell_CommandStation::~PythonQtShell_CommandStation() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
QString  PythonQtShell_CommandStation::getSystemPrefix()
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
  return CommandStation::getSystemPrefix();
}
QString  PythonQtShell_CommandStation::getUserName()
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
  return CommandStation::getUserName();
}
void PythonQtShell_CommandStation::sendPacket(QByteArray  arg__1, int  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("sendPacket");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QByteArray" , "int"};
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
  CommandStation::sendPacket(arg__1, arg__2);
}
CommandStation* PythonQtWrapper_CommandStation::new_CommandStation(QObject*  parent)
{ 
return new PythonQtShell_CommandStation(parent); }

QString  PythonQtWrapper_CommandStation::getSystemPrefix(CommandStation* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_CommandStation*)theWrappedObject)->promoted_getSystemPrefix());
}

QString  PythonQtWrapper_CommandStation::getUserName(CommandStation* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_CommandStation*)theWrappedObject)->promoted_getUserName());
}

void PythonQtWrapper_CommandStation::sendPacket(CommandStation* theWrappedObject, QByteArray  arg__1, int  arg__2)
{
  ( ((PythonQtPublicPromoter_CommandStation*)theWrappedObject)->promoted_sendPacket(arg__1, arg__2));
}



PythonQtShell_DccLocoAddress::~PythonQtShell_DccLocoAddress() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
int  PythonQtShell_DccLocoAddress::getNumber()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNumber");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getNumber", methodInfo, result);
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
  return DccLocoAddress::getNumber();
}
QString  PythonQtShell_DccLocoAddress::toString()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("toString");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("toString", methodInfo, result);
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
  return DccLocoAddress::toString();
}
DccLocoAddress* PythonQtWrapper_DccLocoAddress::new_DccLocoAddress(const DccLocoAddress&  l, QObject*  parent)
{ 
return new PythonQtShell_DccLocoAddress(l, parent); }

DccLocoAddress* PythonQtWrapper_DccLocoAddress::new_DccLocoAddress(int  number, bool  isLong, QObject*  parent)
{ 
return new PythonQtShell_DccLocoAddress(number, isLong, parent); }

int  PythonQtWrapper_DccLocoAddress::getNumber(DccLocoAddress* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_DccLocoAddress*)theWrappedObject)->promoted_getNumber());
}

int  PythonQtWrapper_DccLocoAddress::hashCode(DccLocoAddress* theWrappedObject)
{
  return ( theWrappedObject->hashCode());
}

bool  PythonQtWrapper_DccLocoAddress::isLongAddress(DccLocoAddress* theWrappedObject)
{
  return ( theWrappedObject->isLongAddress());
}

bool  PythonQtWrapper_DccLocoAddress::__eq__(DccLocoAddress* theWrappedObject, DccLocoAddress*  a)
{
  return ( (*theWrappedObject)== a);
}

QString  PythonQtWrapper_DccLocoAddress::toString(DccLocoAddress* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_DccLocoAddress*)theWrappedObject)->promoted_toString());
}

QString PythonQtWrapper_DccLocoAddress::py_toString(DccLocoAddress* obj) { return obj->toString(); }


PythonQtShell_DccThrottle::~PythonQtShell_DccThrottle() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_DccThrottle::addPropertyChangeListener(PropertyChangeListener*  arg__1)
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
  DccThrottle::addPropertyChangeListener(arg__1);
}
bool  PythonQtShell_DccThrottle::getF0()
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
  return DccThrottle::getF0();
}
bool  PythonQtShell_DccThrottle::getF0Momentary()
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
  return DccThrottle::getF0Momentary();
}
bool  PythonQtShell_DccThrottle::getF1()
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
  return DccThrottle::getF1();
}
bool  PythonQtShell_DccThrottle::getF10()
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
  return DccThrottle::getF10();
}
bool  PythonQtShell_DccThrottle::getF10Momentary()
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
  return DccThrottle::getF10Momentary();
}
bool  PythonQtShell_DccThrottle::getF11()
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
  return DccThrottle::getF11();
}
bool  PythonQtShell_DccThrottle::getF11Momentary()
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
  return DccThrottle::getF11Momentary();
}
bool  PythonQtShell_DccThrottle::getF12()
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
  return DccThrottle::getF12();
}
bool  PythonQtShell_DccThrottle::getF12Momentary()
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
  return DccThrottle::getF12Momentary();
}
bool  PythonQtShell_DccThrottle::getF13()
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
  return DccThrottle::getF13();
}
bool  PythonQtShell_DccThrottle::getF13Momentary()
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
  return DccThrottle::getF13Momentary();
}
bool  PythonQtShell_DccThrottle::getF14()
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
  return DccThrottle::getF14();
}
bool  PythonQtShell_DccThrottle::getF14Momentary()
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
  return DccThrottle::getF14Momentary();
}
bool  PythonQtShell_DccThrottle::getF15()
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
  return DccThrottle::getF15();
}
bool  PythonQtShell_DccThrottle::getF15Momentary()
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
  return DccThrottle::getF15Momentary();
}
bool  PythonQtShell_DccThrottle::getF16()
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
  return DccThrottle::getF16();
}
bool  PythonQtShell_DccThrottle::getF16Momentary()
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
  return DccThrottle::getF16Momentary();
}
bool  PythonQtShell_DccThrottle::getF17()
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
  return DccThrottle::getF17();
}
bool  PythonQtShell_DccThrottle::getF17Momentary()
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
  return DccThrottle::getF17Momentary();
}
bool  PythonQtShell_DccThrottle::getF18()
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
  return DccThrottle::getF18();
}
bool  PythonQtShell_DccThrottle::getF18Momentary()
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
  return DccThrottle::getF18Momentary();
}
bool  PythonQtShell_DccThrottle::getF19()
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
  return DccThrottle::getF19();
}
bool  PythonQtShell_DccThrottle::getF19Momentary()
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
  return DccThrottle::getF19Momentary();
}
bool  PythonQtShell_DccThrottle::getF1Momentary()
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
  return DccThrottle::getF1Momentary();
}
bool  PythonQtShell_DccThrottle::getF2()
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
  return DccThrottle::getF2();
}
bool  PythonQtShell_DccThrottle::getF20()
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
  return DccThrottle::getF20();
}
bool  PythonQtShell_DccThrottle::getF20Momentary()
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
  return DccThrottle::getF20Momentary();
}
bool  PythonQtShell_DccThrottle::getF21()
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
  return DccThrottle::getF21();
}
bool  PythonQtShell_DccThrottle::getF21Momentary()
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
  return DccThrottle::getF21Momentary();
}
bool  PythonQtShell_DccThrottle::getF22()
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
  return DccThrottle::getF22();
}
bool  PythonQtShell_DccThrottle::getF22Momentary()
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
  return DccThrottle::getF22Momentary();
}
bool  PythonQtShell_DccThrottle::getF23()
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
  return DccThrottle::getF23();
}
bool  PythonQtShell_DccThrottle::getF23Momentary()
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
  return DccThrottle::getF23Momentary();
}
bool  PythonQtShell_DccThrottle::getF24()
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
  return DccThrottle::getF24();
}
bool  PythonQtShell_DccThrottle::getF24Momentary()
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
  return DccThrottle::getF24Momentary();
}
bool  PythonQtShell_DccThrottle::getF25()
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
  return DccThrottle::getF25();
}
bool  PythonQtShell_DccThrottle::getF25Momentary()
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
  return DccThrottle::getF25Momentary();
}
bool  PythonQtShell_DccThrottle::getF26()
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
  return DccThrottle::getF26();
}
bool  PythonQtShell_DccThrottle::getF26Momentary()
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
  return DccThrottle::getF26Momentary();
}
bool  PythonQtShell_DccThrottle::getF27()
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
  return DccThrottle::getF27();
}
bool  PythonQtShell_DccThrottle::getF27Momentary()
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
  return DccThrottle::getF27Momentary();
}
bool  PythonQtShell_DccThrottle::getF28()
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
  return DccThrottle::getF28();
}
bool  PythonQtShell_DccThrottle::getF28Momentary()
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
  return DccThrottle::getF28Momentary();
}
bool  PythonQtShell_DccThrottle::getF2Momentary()
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
  return DccThrottle::getF2Momentary();
}
bool  PythonQtShell_DccThrottle::getF3()
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
  return DccThrottle::getF3();
}
bool  PythonQtShell_DccThrottle::getF3Momentary()
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
  return DccThrottle::getF3Momentary();
}
bool  PythonQtShell_DccThrottle::getF4()
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
  return DccThrottle::getF4();
}
bool  PythonQtShell_DccThrottle::getF4Momentary()
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
  return DccThrottle::getF4Momentary();
}
bool  PythonQtShell_DccThrottle::getF5()
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
  return DccThrottle::getF5();
}
bool  PythonQtShell_DccThrottle::getF5Momentary()
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
  return DccThrottle::getF5Momentary();
}
bool  PythonQtShell_DccThrottle::getF6()
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
  return DccThrottle::getF6();
}
bool  PythonQtShell_DccThrottle::getF6Momentary()
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
  return DccThrottle::getF6Momentary();
}
bool  PythonQtShell_DccThrottle::getF7()
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
  return DccThrottle::getF7();
}
bool  PythonQtShell_DccThrottle::getF7Momentary()
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
  return DccThrottle::getF7Momentary();
}
bool  PythonQtShell_DccThrottle::getF8()
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
  return DccThrottle::getF8();
}
bool  PythonQtShell_DccThrottle::getF8Momentary()
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
  return DccThrottle::getF8Momentary();
}
bool  PythonQtShell_DccThrottle::getF9()
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
  return DccThrottle::getF9();
}
bool  PythonQtShell_DccThrottle::getF9Momentary()
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
  return DccThrottle::getF9Momentary();
}
bool  PythonQtShell_DccThrottle::getIsForward()
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
  return DccThrottle::getIsForward();
}
QVector<PropertyChangeListener* >*  PythonQtShell_DccThrottle::getListeners()
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
  return DccThrottle::getListeners();
}
LocoAddress*  PythonQtShell_DccThrottle::getLocoAddress()
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
  return DccThrottle::getLocoAddress();
}
float  PythonQtShell_DccThrottle::getSpeedIncrement()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSpeedIncrement");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getSpeedIncrement", methodInfo, result);
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
  return DccThrottle::getSpeedIncrement();
}
float  PythonQtShell_DccThrottle::getSpeedSetting()
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
  return DccThrottle::getSpeedSetting();
}
int  PythonQtShell_DccThrottle::getSpeedStepMode()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getSpeedStepMode");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getSpeedStepMode", methodInfo, result);
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
  return DccThrottle::getSpeedStepMode();
}
void PythonQtShell_DccThrottle::removePropertyChangeListener(PropertyChangeListener*  arg__1)
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
  DccThrottle::removePropertyChangeListener(arg__1);
}
void PythonQtShell_DccThrottle::setF0(bool  arg__1)
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
  DccThrottle::setF0(arg__1);
}
void PythonQtShell_DccThrottle::setF0Momentary(bool  arg__1)
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
  DccThrottle::setF0Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setF1(bool  arg__1)
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
  DccThrottle::setF1(arg__1);
}
void PythonQtShell_DccThrottle::setF10(bool  arg__1)
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
  DccThrottle::setF10(arg__1);
}
void PythonQtShell_DccThrottle::setF10Momentary(bool  arg__1)
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
  DccThrottle::setF10Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setF11(bool  arg__1)
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
  DccThrottle::setF11(arg__1);
}
void PythonQtShell_DccThrottle::setF11Momentary(bool  arg__1)
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
  DccThrottle::setF11Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setF12(bool  arg__1)
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
  DccThrottle::setF12(arg__1);
}
void PythonQtShell_DccThrottle::setF12Momentary(bool  arg__1)
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
  DccThrottle::setF12Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setF13(bool  arg__1)
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
  DccThrottle::setF13(arg__1);
}
void PythonQtShell_DccThrottle::setF13Momentary(bool  arg__1)
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
  DccThrottle::setF13Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setF14(bool  arg__1)
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
  DccThrottle::setF14(arg__1);
}
void PythonQtShell_DccThrottle::setF14Momentary(bool  arg__1)
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
  DccThrottle::setF14Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setF15(bool  arg__1)
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
  DccThrottle::setF15(arg__1);
}
void PythonQtShell_DccThrottle::setF15Momentary(bool  arg__1)
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
  DccThrottle::setF15Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setF16(bool  arg__1)
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
  DccThrottle::setF16(arg__1);
}
void PythonQtShell_DccThrottle::setF16Momentary(bool  arg__1)
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
  DccThrottle::setF16Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setF17(bool  arg__1)
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
  DccThrottle::setF17(arg__1);
}
void PythonQtShell_DccThrottle::setF17Momentary(bool  arg__1)
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
  DccThrottle::setF17Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setF18(bool  arg__1)
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
  DccThrottle::setF18(arg__1);
}
void PythonQtShell_DccThrottle::setF18Momentary(bool  arg__1)
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
  DccThrottle::setF18Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setF19(bool  arg__1)
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
  DccThrottle::setF19(arg__1);
}
void PythonQtShell_DccThrottle::setF19Momentary(bool  arg__1)
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
  DccThrottle::setF19Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setF1Momentary(bool  arg__1)
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
  DccThrottle::setF1Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setF2(bool  arg__1)
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
  DccThrottle::setF2(arg__1);
}
void PythonQtShell_DccThrottle::setF20(bool  arg__1)
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
  DccThrottle::setF20(arg__1);
}
void PythonQtShell_DccThrottle::setF20Momentary(bool  arg__1)
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
  DccThrottle::setF20Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setF21(bool  arg__1)
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
  DccThrottle::setF21(arg__1);
}
void PythonQtShell_DccThrottle::setF21Momentary(bool  arg__1)
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
  DccThrottle::setF21Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setF22(bool  arg__1)
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
  DccThrottle::setF22(arg__1);
}
void PythonQtShell_DccThrottle::setF22Momentary(bool  arg__1)
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
  DccThrottle::setF22Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setF23(bool  arg__1)
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
  DccThrottle::setF23(arg__1);
}
void PythonQtShell_DccThrottle::setF23Momentary(bool  arg__1)
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
  DccThrottle::setF23Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setF24(bool  arg__1)
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
  DccThrottle::setF24(arg__1);
}
void PythonQtShell_DccThrottle::setF24Momentary(bool  arg__1)
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
  DccThrottle::setF24Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setF25(bool  arg__1)
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
  DccThrottle::setF25(arg__1);
}
void PythonQtShell_DccThrottle::setF25Momentary(bool  arg__1)
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
  DccThrottle::setF25Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setF26(bool  arg__1)
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
  DccThrottle::setF26(arg__1);
}
void PythonQtShell_DccThrottle::setF26Momentary(bool  arg__1)
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
  DccThrottle::setF26Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setF27(bool  arg__1)
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
  DccThrottle::setF27(arg__1);
}
void PythonQtShell_DccThrottle::setF27Momentary(bool  arg__1)
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
  DccThrottle::setF27Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setF28(bool  arg__1)
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
  DccThrottle::setF28(arg__1);
}
void PythonQtShell_DccThrottle::setF28Momentary(bool  arg__1)
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
  DccThrottle::setF28Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setF2Momentary(bool  arg__1)
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
  DccThrottle::setF2Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setF3(bool  arg__1)
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
  DccThrottle::setF3(arg__1);
}
void PythonQtShell_DccThrottle::setF3Momentary(bool  arg__1)
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
  DccThrottle::setF3Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setF4(bool  arg__1)
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
  DccThrottle::setF4(arg__1);
}
void PythonQtShell_DccThrottle::setF4Momentary(bool  arg__1)
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
  DccThrottle::setF4Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setF5(bool  arg__1)
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
  DccThrottle::setF5(arg__1);
}
void PythonQtShell_DccThrottle::setF5Momentary(bool  arg__1)
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
  DccThrottle::setF5Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setF6(bool  arg__1)
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
  DccThrottle::setF6(arg__1);
}
void PythonQtShell_DccThrottle::setF6Momentary(bool  arg__1)
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
  DccThrottle::setF6Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setF7(bool  arg__1)
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
  DccThrottle::setF7(arg__1);
}
void PythonQtShell_DccThrottle::setF7Momentary(bool  arg__1)
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
  DccThrottle::setF7Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setF8(bool  arg__1)
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
  DccThrottle::setF8(arg__1);
}
void PythonQtShell_DccThrottle::setF8Momentary(bool  arg__1)
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
  DccThrottle::setF8Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setF9(bool  arg__1)
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
  DccThrottle::setF9(arg__1);
}
void PythonQtShell_DccThrottle::setF9Momentary(bool  arg__1)
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
  DccThrottle::setF9Momentary(arg__1);
}
void PythonQtShell_DccThrottle::setIsForward(bool  arg__1)
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
  DccThrottle::setIsForward(arg__1);
}
void PythonQtShell_DccThrottle::setSpeedSetting(float  arg__1)
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
  DccThrottle::setSpeedSetting(arg__1);
}
void PythonQtShell_DccThrottle::setSpeedStepMode(int  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setSpeedStepMode");
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
  DccThrottle::setSpeedStepMode(arg__1);
}
DccThrottle* PythonQtWrapper_DccThrottle::new_DccThrottle(QObject*  parent)
{ 
return new PythonQtShell_DccThrottle(parent); }

DccThrottle* PythonQtWrapper_DccThrottle::new_DccThrottle(const DccThrottle&  arg__1)
{ 
return new PythonQtShell_DccThrottle(arg__1); }

float  PythonQtWrapper_DccThrottle::getSpeedIncrement(DccThrottle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_DccThrottle*)theWrappedObject)->promoted_getSpeedIncrement());
}

int  PythonQtWrapper_DccThrottle::getSpeedStepMode(DccThrottle* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_DccThrottle*)theWrappedObject)->promoted_getSpeedStepMode());
}

void PythonQtWrapper_DccThrottle::setSpeedStepMode(DccThrottle* theWrappedObject, int  arg__1)
{
  ( ((PythonQtPublicPromoter_DccThrottle*)theWrappedObject)->promoted_setSpeedStepMode(arg__1));
}



PythonQtShell_DefaultLogixManager::~PythonQtShell_DefaultLogixManager() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
DefaultLogixManager* PythonQtWrapper_DefaultLogixManager::new_DefaultLogixManager(QObject*  parent)
{ 
return new PythonQtShell_DefaultLogixManager(parent); }

void PythonQtWrapper_DefaultLogixManager::activateAllLogixs(DefaultLogixManager* theWrappedObject)
{
  ( theWrappedObject->activateAllLogixs());
}

bool  PythonQtWrapper_DefaultLogixManager::getLoadDisabled(DefaultLogixManager* theWrappedObject)
{
  return ( theWrappedObject->getLoadDisabled());
}

QString  PythonQtWrapper_DefaultLogixManager::getSystemPrefix(DefaultLogixManager* theWrappedObject)
{
  return ( theWrappedObject->getSystemPrefix());
}

int  PythonQtWrapper_DefaultLogixManager::getXMLOrder(DefaultLogixManager* theWrappedObject)
{
  return ( theWrappedObject->getXMLOrder());
}

DefaultLogixManager*  PythonQtWrapper_DefaultLogixManager::static_DefaultLogixManager_instance()
{
  return (DefaultLogixManager::instance());
}

void PythonQtWrapper_DefaultLogixManager::setLoadDisabled(DefaultLogixManager* theWrappedObject, bool  s)
{
  ( theWrappedObject->setLoadDisabled(s));
}

char  PythonQtWrapper_DefaultLogixManager::typeLetter(DefaultLogixManager* theWrappedObject)
{
  return ( theWrappedObject->typeLetter());
}



DefaultMemoryManager* PythonQtWrapper_DefaultMemoryManager::new_DefaultMemoryManager(QObject*  parent)
{ 
return new DefaultMemoryManager(parent); }

QString  PythonQtWrapper_DefaultMemoryManager::getSystemPrefix(DefaultMemoryManager* theWrappedObject)
{
  return ( theWrappedObject->getSystemPrefix());
}



PythonQtShell_Editor::~PythonQtShell_Editor() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_Editor::addHelpMenu(QString  ref0, bool  direct1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("addHelpMenu");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
    void* args[3] = {NULL, (void*)&ref0, (void*)&direct1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Editor::addHelpMenu(ref0, direct1);
}
void PythonQtShell_Editor::componentMoved(QMoveEvent*  e0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("componentMoved");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QMoveEvent*"};
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
  Editor::componentMoved(e0);
}
void PythonQtShell_Editor::componentResized(QResizeEvent*  e0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("componentResized");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QResizeEvent*"};
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
  Editor::componentResized(e0);
}
void PythonQtShell_Editor::dispose()
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
  Editor::dispose();
}
QString  PythonQtShell_Editor::getClassName()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getClassName");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getClassName", methodInfo, result);
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
  return Editor::getClassName();
}
QVariant  PythonQtShell_Editor::getProperty(QString  key0)
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
  return Editor::getProperty(key0);
}
QString  PythonQtShell_Editor::getTitle()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getTitle");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getTitle", methodInfo, result);
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
  return Editor::getTitle();
}
void PythonQtShell_Editor::handleModified()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("handleModified");
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
  Editor::handleModified();
}
void PythonQtShell_Editor::init(QString  name0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("init");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&name0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Editor::init(name0);
}
void PythonQtShell_Editor::initComponents()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("initComponents");
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
  Editor::initComponents();
}
void PythonQtShell_Editor::initView()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("initView");
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
  Editor::initView();
}
void PythonQtShell_Editor::paint(QGraphicsScene*  g0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("paint");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QGraphicsScene*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&g0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Editor::paint(g0);
}
void PythonQtShell_Editor::paintTargetPanel(QGraphicsScene*  g0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("paintTargetPanel");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QGraphicsScene*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&g0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Editor::paintTargetPanel(g0);
}
void PythonQtShell_Editor::putItem(Positionable*  l0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("putItem");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "Positionable*"};
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
  Editor::putItem(l0);
}
void PythonQtShell_Editor::repaint()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("repaint");
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
  Editor::repaint();
}
void PythonQtShell_Editor::setAllEditable(bool  state0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setAllEditable");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&state0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Editor::setAllEditable(state0);
}
void PythonQtShell_Editor::setNextLocation(Positionable*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setNextLocation");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "Positionable*"};
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
  Editor::setNextLocation(arg__1);
}
void PythonQtShell_Editor::setRemoveMenu(Positionable*  p0, QMenu*  popup1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setRemoveMenu");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "Positionable*" , "QMenu*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
    void* args[3] = {NULL, (void*)&p0, (void*)&popup1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Editor::setRemoveMenu(p0, popup1);
}
void PythonQtShell_Editor::setScroll(int  state0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setScroll");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&state0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Editor::setScroll(state0);
}
void PythonQtShell_Editor::setTitle()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setTitle");
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
  Editor::setTitle();
}
void PythonQtShell_Editor::setUseGlobalFlag(bool  set0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setUseGlobalFlag");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&set0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Editor::setUseGlobalFlag(set0);
}
void PythonQtShell_Editor::showPopUp(Positionable*  arg__1, QMouseEvent*  arg__2)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("showPopUp");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "Positionable*" , "QMouseEvent*"};
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
  Editor::showPopUp(arg__1, arg__2);
}
void PythonQtShell_Editor::storeValues()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("storeValues");
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
  Editor::storeValues();
}
void PythonQtShell_Editor::targetWindowClosing(bool  save0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("targetWindowClosing");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&save0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Editor::targetWindowClosing(save0);
}
void PythonQtShell_Editor::targetWindowClosingEvent(QCloseEvent*  e0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("targetWindowClosingEvent");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QCloseEvent*"};
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
  Editor::targetWindowClosingEvent(e0);
}
bool  PythonQtShell_Editor::useGlobalFlag()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("useGlobalFlag");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("useGlobalFlag", methodInfo, result);
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
  return Editor::useGlobalFlag();
}
void PythonQtShell_Editor::vetoableChange(PropertyChangeEvent*  evt0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("vetoableChange");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&evt0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  Editor::vetoableChange(evt0);
}
void PythonQtShell_Editor::windowClosing(QCloseEvent*  e0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("windowClosing");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QCloseEvent*"};
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
  Editor::windowClosing(e0);
}
Editor* PythonQtWrapper_Editor::new_Editor(QString  name, QWidget*  parent)
{ 
return new PythonQtShell_Editor(name, parent); }

Editor* PythonQtWrapper_Editor::new_Editor(QString  name, bool  saveSize, bool  savePosition, QWidget*  parent)
{ 
return new PythonQtShell_Editor(name, saveSize, savePosition, parent); }

Editor* PythonQtWrapper_Editor::new_Editor(QWidget*  parent)
{ 
return new PythonQtShell_Editor(parent); }

void PythonQtWrapper_Editor::addClock(Editor* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_addClock());
}

void PythonQtWrapper_Editor::addRpsReporter(Editor* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_addRpsReporter());
}

void PythonQtWrapper_Editor::addToTarget(Editor* theWrappedObject, Positionable*  l)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_addToTarget(l));
}

bool  PythonQtWrapper_Editor::allControlling(Editor* theWrappedObject)
{
  return ( theWrappedObject->allControlling());
}

bool  PythonQtWrapper_Editor::allPositionable(Editor* theWrappedObject)
{
  return ( theWrappedObject->allPositionable());
}

Editor*  PythonQtWrapper_Editor::changeView(Editor* theWrappedObject, QString  className)
{
  return ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_changeView(className));
}

void PythonQtWrapper_Editor::clearBackgroundColor(Editor* theWrappedObject)
{
  ( theWrappedObject->clearBackgroundColor());
}

bool  PythonQtWrapper_Editor::deletePanel(Editor* theWrappedObject)
{
  return ( theWrappedObject->deletePanel());
}

void PythonQtWrapper_Editor::displayLevelChange(Editor* theWrappedObject, Positionable*  l)
{
  ( theWrappedObject->displayLevelChange(l));
}

void PythonQtWrapper_Editor::dispose(Editor* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_dispose());
}

void PythonQtWrapper_Editor::dispose(Editor* theWrappedObject, bool  clear)
{
  ( theWrappedObject->dispose(clear));
}

void PythonQtWrapper_Editor::disposeLoadData(Editor* theWrappedObject)
{
  ( theWrappedObject->disposeLoadData());
}

void PythonQtWrapper_Editor::dockSelections(Editor* theWrappedObject, Positionable*  p)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_dockSelections(p));
}

void PythonQtWrapper_Editor::drawSelectRect(Editor* theWrappedObject, int  x, int  y)
{
  ( theWrappedObject->drawSelectRect(x, y));
}

int  PythonQtWrapper_Editor::getAnchorX(Editor* theWrappedObject)
{
  return ( theWrappedObject->getAnchorX());
}

int  PythonQtWrapper_Editor::getAnchorY(Editor* theWrappedObject)
{
  return ( theWrappedObject->getAnchorY());
}

QColor  PythonQtWrapper_Editor::getBackgroundColor(Editor* theWrappedObject)
{
  return ( theWrappedObject->getBackgroundColor());
}

QList<Positionable* >  PythonQtWrapper_Editor::getContents(Editor* theWrappedObject)
{
  return ( theWrappedObject->getContents());
}

Editor*  PythonQtWrapper_Editor::static_Editor_getEditor(QString  name)
{
  return (Editor::getEditor(name));
}

QVector<Editor* >  PythonQtWrapper_Editor::static_Editor_getEditors()
{
  return (Editor::getEditors());
}

QList<Editor* >  PythonQtWrapper_Editor::static_Editor_getEditors(QString  type)
{
  return (Editor::getEditors(type));
}

bool  PythonQtWrapper_Editor::getFlag(Editor* theWrappedObject, int  whichOption, bool  localFlag)
{
  return ( theWrappedObject->getFlag(whichOption, localFlag));
}

int  PythonQtWrapper_Editor::getItemX(Editor* theWrappedObject, Positionable*  p, int  deltaX)
{
  return ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_getItemX(p, deltaX));
}

int  PythonQtWrapper_Editor::getItemY(Editor* theWrappedObject, Positionable*  p, int  deltaY)
{
  return ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_getItemY(p, deltaY));
}

QString  PythonQtWrapper_Editor::getName(Editor* theWrappedObject)
{
  return ( theWrappedObject->getName());
}

double  PythonQtWrapper_Editor::getPaintScale(Editor* theWrappedObject)
{
  return ( theWrappedObject->getPaintScale());
}

const QScrollArea*  PythonQtWrapper_Editor::getPanelScrollPane(Editor* theWrappedObject)
{
  return ( theWrappedObject->getPanelScrollPane());
}

QString  PythonQtWrapper_Editor::getScrollable(Editor* theWrappedObject)
{
  return ( theWrappedObject->getScrollable());
}

QRectF  PythonQtWrapper_Editor::getSelectRect(Editor* theWrappedObject)
{
  return ( theWrappedObject->getSelectRect());
}

QList<Positionable* >*  PythonQtWrapper_Editor::getSelectedItems(Editor* theWrappedObject, QGraphicsSceneMouseEvent*  event)
{
  return ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_getSelectedItems(event));
}

QList<Positionable* >*  PythonQtWrapper_Editor::getSelectedItems(Editor* theWrappedObject, QPointF  pt)
{
  return ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_getSelectedItems(pt));
}

JFrame*  PythonQtWrapper_Editor::getTargetFrame(Editor* theWrappedObject)
{
  return ( theWrappedObject->getTargetFrame());
}

QGraphicsScene*  PythonQtWrapper_Editor::getTargetPanel(Editor* theWrappedObject)
{
  return ( theWrappedObject->getTargetPanel());
}

QSizeF  PythonQtWrapper_Editor::getTargetPanelSize(Editor* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_getTargetPanelSize());
}

QString  PythonQtWrapper_Editor::getTitle(Editor* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_getTitle());
}

void PythonQtWrapper_Editor::init(Editor* theWrappedObject, QString  name)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_init(name));
}

void PythonQtWrapper_Editor::initView(Editor* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_initView());
}

bool  PythonQtWrapper_Editor::isEditable(Editor* theWrappedObject)
{
  return ( theWrappedObject->isEditable());
}

bool  PythonQtWrapper_Editor::isPanelMenuVisible(Editor* theWrappedObject)
{
  return ( theWrappedObject->isPanelMenuVisible());
}

void PythonQtWrapper_Editor::loadFailed(Editor* theWrappedObject)
{
  ( theWrappedObject->loadFailed());
}

bool  PythonQtWrapper_Editor::loadOK(Editor* theWrappedObject)
{
  return ( theWrappedObject->loadOK());
}

void PythonQtWrapper_Editor::makeSelectionGroup(Editor* theWrappedObject, QGraphicsSceneMouseEvent*  event)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_makeSelectionGroup(event));
}

void PythonQtWrapper_Editor::modifySelectionGroup(Editor* theWrappedObject, Positionable*  selection, QGraphicsSceneMouseEvent*  event)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_modifySelectionGroup(selection, event));
}

void PythonQtWrapper_Editor::moveItem(Editor* theWrappedObject, Positionable*  p, int  deltaX, int  deltaY)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_moveItem(p, deltaX, deltaY));
}

void PythonQtWrapper_Editor::newPanelDefaults(Editor* theWrappedObject)
{
  ( theWrappedObject->newPanelDefaults());
}

void PythonQtWrapper_Editor::paint(Editor* theWrappedObject, QGraphicsScene*  g)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_paint(g));
}

void PythonQtWrapper_Editor::paintTargetPanel(Editor* theWrappedObject, QGraphicsScene*  g)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_paintTargetPanel(g));
}

void PythonQtWrapper_Editor::putItem(Editor* theWrappedObject, Positionable*  l)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_putItem(l));
}

bool  PythonQtWrapper_Editor::removeFromContents(Editor* theWrappedObject, Positionable*  l)
{
  return ( theWrappedObject->removeFromContents(l));
}

void PythonQtWrapper_Editor::removeFromTarget(Editor* theWrappedObject, Positionable*  l)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_removeFromTarget(l));
}

void PythonQtWrapper_Editor::removeSelections(Editor* theWrappedObject, Positionable*  p)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_removeSelections(p));
}

void PythonQtWrapper_Editor::repaint(Editor* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_repaint());
}

void PythonQtWrapper_Editor::setAllControlling(Editor* theWrappedObject, bool  state)
{
  ( theWrappedObject->setAllControlling(state));
}

void PythonQtWrapper_Editor::setAllEditable(Editor* theWrappedObject, bool  state)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_setAllEditable(state));
}

void PythonQtWrapper_Editor::setBackgroundColor(Editor* theWrappedObject, QColor  col)
{
  ( theWrappedObject->setBackgroundColor(col));
}

void PythonQtWrapper_Editor::setDefaultColors(Editor* theWrappedObject)
{
  ( theWrappedObject->setDefaultColors());
}

void PythonQtWrapper_Editor::setDefaultToolTip(Editor* theWrappedObject, QString  dtt)
{
  ( theWrappedObject->setDefaultToolTip(dtt));
}

void PythonQtWrapper_Editor::setDirty(Editor* theWrappedObject, bool  bDirty)
{
  ( theWrappedObject->setDirty(bDirty));
}

void PythonQtWrapper_Editor::setDisplayLevelMenu(Editor* theWrappedObject, Positionable*  p, QMenu*  popup)
{
  ( theWrappedObject->setDisplayLevelMenu(p, popup));
}

void PythonQtWrapper_Editor::setGlobalSetsLocalFlag(Editor* theWrappedObject, bool  set)
{
  ( theWrappedObject->setGlobalSetsLocalFlag(set));
}

void PythonQtWrapper_Editor::setHiddenMenu(Editor* theWrappedObject, Positionable*  p, QMenu*  popup)
{
  ( theWrappedObject->setHiddenMenu(p, popup));
}

void PythonQtWrapper_Editor::setHighlightColor(Editor* theWrappedObject, QColor  color)
{
  ( theWrappedObject->setHighlightColor(color));
}

void PythonQtWrapper_Editor::setName(Editor* theWrappedObject, QString  name)
{
  ( theWrappedObject->setName(name));
}

void PythonQtWrapper_Editor::setNextLocation(Editor* theWrappedObject, Positionable*  arg__1)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_setNextLocation(arg__1));
}

void PythonQtWrapper_Editor::setPaintScale(Editor* theWrappedObject, double  newScale)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_setPaintScale(newScale));
}

void PythonQtWrapper_Editor::setPanelMenu(Editor* theWrappedObject, bool  state)
{
  ( theWrappedObject->setPanelMenu(state));
}

void PythonQtWrapper_Editor::setPositionableMenu(Editor* theWrappedObject, Positionable*  p, QMenu*  popup)
{
  ( theWrappedObject->setPositionableMenu(p, popup));
}

void PythonQtWrapper_Editor::setRemoveMenu(Editor* theWrappedObject, Positionable*  p, QMenu*  popup)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_setRemoveMenu(p, popup));
}

void PythonQtWrapper_Editor::setScroll(Editor* theWrappedObject, QString  strState)
{
  ( theWrappedObject->setScroll(strState));
}

void PythonQtWrapper_Editor::setScroll(Editor* theWrappedObject, int  state)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_setScroll(state));
}

void PythonQtWrapper_Editor::setSelectGroupColor(Editor* theWrappedObject, QColor  color)
{
  ( theWrappedObject->setSelectGroupColor(color));
}

void PythonQtWrapper_Editor::setSelectRectColor(Editor* theWrappedObject, QColor  color)
{
  ( theWrappedObject->setSelectRectColor(color));
}

void PythonQtWrapper_Editor::setSelectRectStroke(Editor* theWrappedObject, Qt::PenStyle  stroke)
{
  ( theWrappedObject->setSelectRectStroke(stroke));
}

void PythonQtWrapper_Editor::setSelectionsDockingLocation(Editor* theWrappedObject, Positionable*  p)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_setSelectionsDockingLocation(p));
}

void PythonQtWrapper_Editor::setSelectionsHidden(Editor* theWrappedObject, bool  enabled, Positionable*  p)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_setSelectionsHidden(enabled, p));
}

void PythonQtWrapper_Editor::setSelectionsRotation(Editor* theWrappedObject, int  k, Positionable*  p)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_setSelectionsRotation(k, p));
}

void PythonQtWrapper_Editor::setSelectionsScale(Editor* theWrappedObject, double  s, Positionable*  p)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_setSelectionsScale(s, p));
}

bool  PythonQtWrapper_Editor::setShowAlignmentMenu(Editor* theWrappedObject, Positionable*  p, QMenu*  popup)
{
  return ( theWrappedObject->setShowAlignmentMenu(p, popup));
}

void PythonQtWrapper_Editor::setShowCoordinates(Editor* theWrappedObject, bool  state)
{
  ( theWrappedObject->setShowCoordinates(state));
}

bool  PythonQtWrapper_Editor::setShowCoordinatesMenu(Editor* theWrappedObject, Positionable*  p, QMenu*  popup)
{
  return ( theWrappedObject->setShowCoordinatesMenu(p, popup));
}

void PythonQtWrapper_Editor::setShowTooltipMenu(Editor* theWrappedObject, Positionable*  p, QMenu*  popup)
{
  ( theWrappedObject->setShowTooltipMenu(p, popup));
}

void PythonQtWrapper_Editor::setTargetPanelSize(Editor* theWrappedObject, int  w, int  h)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_setTargetPanelSize(w, h));
}

bool  PythonQtWrapper_Editor::setTextAttributes(Editor* theWrappedObject, Positionable*  p, QMenu*  popup)
{
  return ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_setTextAttributes(p, popup));
}

void PythonQtWrapper_Editor::setTitle(Editor* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_setTitle());
}

void PythonQtWrapper_Editor::setToolTip(Editor* theWrappedObject, QString  tt)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_setToolTip(tt));
}

void PythonQtWrapper_Editor::setUseGlobalFlag(Editor* theWrappedObject, bool  set)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_setUseGlobalFlag(set));
}

bool  PythonQtWrapper_Editor::showAlignPopup(Editor* theWrappedObject, Positionable*  p)
{
  return ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_showAlignPopup(p));
}

bool  PythonQtWrapper_Editor::showCoordinates(Editor* theWrappedObject)
{
  return ( theWrappedObject->showCoordinates());
}

bool  PythonQtWrapper_Editor::showHidden(Editor* theWrappedObject)
{
  return ( theWrappedObject->showHidden());
}

void PythonQtWrapper_Editor::showPopUp(Editor* theWrappedObject, Positionable*  arg__1, QMouseEvent*  arg__2)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_showPopUp(arg__1, arg__2));
}

void PythonQtWrapper_Editor::showPopUp(Editor* theWrappedObject, Positionable*  p, QGraphicsSceneMouseEvent*  arg__2)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_showPopUp(p, arg__2));
}

bool  PythonQtWrapper_Editor::showToolTip(Editor* theWrappedObject)
{
  return ( theWrappedObject->showToolTip());
}

void PythonQtWrapper_Editor::showToolTip(Editor* theWrappedObject, Positionable*  selection, QGraphicsSceneMouseEvent*  event)
{
  ( theWrappedObject->showToolTip(selection, event));
}

void PythonQtWrapper_Editor::targetWindowClosing(Editor* theWrappedObject, bool  save)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_targetWindowClosing(save));
}

void PythonQtWrapper_Editor::targetWindowClosingEvent(Editor* theWrappedObject, QCloseEvent*  e)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_targetWindowClosingEvent(e));
}

bool  PythonQtWrapper_Editor::useGlobalFlag(Editor* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_useGlobalFlag());
}

void PythonQtWrapper_Editor::vetoableChange(Editor* theWrappedObject, PropertyChangeEvent*  evt)
{
  ( ((PythonQtPublicPromoter_Editor*)theWrappedObject)->promoted_vetoableChange(evt));
}



PythonQtShell_JFrame::~PythonQtShell_JFrame() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_JFrame::dispose()
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
  JFrame::dispose();
}
QString  PythonQtShell_JFrame::getTitle()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getTitle");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getTitle", methodInfo, result);
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
  return JFrame::getTitle();
}
void PythonQtShell_JFrame::setTitle(QString  _title0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setTitle");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&_title0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  JFrame::setTitle(_title0);
}
JFrame* PythonQtWrapper_JFrame::new_JFrame(QString  _title, QWidget*  parent)
{ 
return new PythonQtShell_JFrame(_title, parent); }

JFrame* PythonQtWrapper_JFrame::new_JFrame(QWidget*  parent)
{ 
return new PythonQtShell_JFrame(parent); }

JFrame* PythonQtWrapper_JFrame::new_JFrame(const JFrame&  arg__1)
{ 
return new PythonQtShell_JFrame(arg__1); }

void PythonQtWrapper_JFrame::addWindowListener(JFrame* theWrappedObject, WindowListener*  l)
{
  ( theWrappedObject->addWindowListener(l));
}

void PythonQtWrapper_JFrame::dispose(JFrame* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_JFrame*)theWrappedObject)->promoted_dispose());
}

void PythonQtWrapper_JFrame::frameInit(JFrame* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_JFrame*)theWrappedObject)->promoted_frameInit());
}

QWidget*  PythonQtWrapper_JFrame::getContentPane(JFrame* theWrappedObject)
{
  return ( theWrappedObject->getContentPane());
}

QPoint  PythonQtWrapper_JFrame::getLocation(JFrame* theWrappedObject)
{
  return ( theWrappedObject->getLocation());
}

QPoint  PythonQtWrapper_JFrame::getLocationOnScreen(JFrame* theWrappedObject)
{
  return ( theWrappedObject->getLocationOnScreen());
}

QSize  PythonQtWrapper_JFrame::getMaximumSize(JFrame* theWrappedObject)
{
  return ( theWrappedObject->getMaximumSize());
}

QSize  PythonQtWrapper_JFrame::getPreferredSize(JFrame* theWrappedObject)
{
  return ( theWrappedObject->getPreferredSize());
}

QString  PythonQtWrapper_JFrame::getTitle(JFrame* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_JFrame*)theWrappedObject)->promoted_getTitle());
}

QWidget*  PythonQtWrapper_JFrame::getTopLevelAncestor(JFrame* theWrappedObject)
{
  return ( theWrappedObject->getTopLevelAncestor());
}

void PythonQtWrapper_JFrame::reSizeToFitOnScreen(JFrame* theWrappedObject)
{
  ( theWrappedObject->reSizeToFitOnScreen());
}

void PythonQtWrapper_JFrame::removeWindowListener(JFrame* theWrappedObject, WindowListener*  l)
{
  ( theWrappedObject->removeWindowListener(l));
}

void PythonQtWrapper_JFrame::setAlwaysOnTop(JFrame* theWrappedObject, bool  checked)
{
  ( theWrappedObject->setAlwaysOnTop(checked));
}

void PythonQtWrapper_JFrame::setDefaultCloseOperation(JFrame* theWrappedObject, int  operation)
{
  ( theWrappedObject->setDefaultCloseOperation(operation));
}

void PythonQtWrapper_JFrame::setLocation(JFrame* theWrappedObject, QPoint  p)
{
  ( theWrappedObject->setLocation(p));
}

void PythonQtWrapper_JFrame::setLocation(JFrame* theWrappedObject, int  x, int  y)
{
  ( theWrappedObject->setLocation(x, y));
}

void PythonQtWrapper_JFrame::setMenuBar(JFrame* theWrappedObject, QMenuBar*  menubar)
{
  ( theWrappedObject->setMenuBar(menubar));
}

void PythonQtWrapper_JFrame::setTitle(JFrame* theWrappedObject, QString  _title)
{
  ( ((PythonQtPublicPromoter_JFrame*)theWrappedObject)->promoted_setTitle(_title));
}

QString  PythonQtWrapper_JFrame::title(JFrame* theWrappedObject)
{
  return ( theWrappedObject->title());
}

void PythonQtWrapper_JFrame::toFront(JFrame* theWrappedObject)
{
  ( theWrappedObject->toFront());
}



PythonQtShell_JmriJFrame::~PythonQtShell_JmriJFrame() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_JmriJFrame::addHelpMenu(QString  ref0, bool  direct1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("addHelpMenu");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
    void* args[3] = {NULL, (void*)&ref0, (void*)&direct1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  JmriJFrame::addHelpMenu(ref0, direct1);
}
void PythonQtShell_JmriJFrame::componentMoved(QMoveEvent*  e0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("componentMoved");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QMoveEvent*"};
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
  JmriJFrame::componentMoved(e0);
}
void PythonQtShell_JmriJFrame::componentResized(QResizeEvent*  e0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("componentResized");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QResizeEvent*"};
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
  JmriJFrame::componentResized(e0);
}
void PythonQtShell_JmriJFrame::dispose()
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
  JmriJFrame::dispose();
}
QString  PythonQtShell_JmriJFrame::getClassName()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getClassName");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getClassName", methodInfo, result);
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
  return JmriJFrame::getClassName();
}
QVariant  PythonQtShell_JmriJFrame::getProperty(QString  key0)
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
  return JmriJFrame::getProperty(key0);
}
QString  PythonQtShell_JmriJFrame::getTitle()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getTitle");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getTitle", methodInfo, result);
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
  return JmriJFrame::getTitle();
}
void PythonQtShell_JmriJFrame::handleModified()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("handleModified");
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
  JmriJFrame::handleModified();
}
void PythonQtShell_JmriJFrame::initComponents()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("initComponents");
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
  JmriJFrame::initComponents();
}
void PythonQtShell_JmriJFrame::setTitle(QString  _title0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setTitle");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&_title0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  JmriJFrame::setTitle(_title0);
}
void PythonQtShell_JmriJFrame::storeValues()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("storeValues");
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
  JmriJFrame::storeValues();
}
void PythonQtShell_JmriJFrame::windowClosing(QCloseEvent*  e0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("windowClosing");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QCloseEvent*"};
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
  JmriJFrame::windowClosing(e0);
}
JmriJFrame* PythonQtWrapper_JmriJFrame::new_JmriJFrame(QString  name, QWidget*  parent)
{ 
return new PythonQtShell_JmriJFrame(name, parent); }

JmriJFrame* PythonQtWrapper_JmriJFrame::new_JmriJFrame(QString  name, bool  saveSize, bool  savePosition, QWidget*  parent)
{ 
return new PythonQtShell_JmriJFrame(name, saveSize, savePosition, parent); }

JmriJFrame* PythonQtWrapper_JmriJFrame::new_JmriJFrame(QWidget*  parent)
{ 
return new PythonQtShell_JmriJFrame(parent); }

JmriJFrame* PythonQtWrapper_JmriJFrame::new_JmriJFrame(bool  saveSize, bool  savePosition, QWidget*  parent)
{ 
return new PythonQtShell_JmriJFrame(saveSize, savePosition, parent); }

void PythonQtWrapper_JmriJFrame::addHelpMenu(JmriJFrame* theWrappedObject, QString  ref, bool  direct)
{
  ( ((PythonQtPublicPromoter_JmriJFrame*)theWrappedObject)->promoted_addHelpMenu(ref, direct));
}

void PythonQtWrapper_JmriJFrame::addNotify(JmriJFrame* theWrappedObject)
{
  ( theWrappedObject->addNotify());
}

void PythonQtWrapper_JmriJFrame::componentMoved(JmriJFrame* theWrappedObject, QMoveEvent*  e)
{
  ( ((PythonQtPublicPromoter_JmriJFrame*)theWrappedObject)->promoted_componentMoved(e));
}

void PythonQtWrapper_JmriJFrame::componentResized(JmriJFrame* theWrappedObject, QResizeEvent*  e)
{
  ( ((PythonQtPublicPromoter_JmriJFrame*)theWrappedObject)->promoted_componentResized(e));
}

void PythonQtWrapper_JmriJFrame::dispose(JmriJFrame* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_JmriJFrame*)theWrappedObject)->promoted_dispose());
}

bool  PythonQtWrapper_JmriJFrame::eventFilter(JmriJFrame* theWrappedObject, QObject*  target, QEvent*  event)
{
  return ( theWrappedObject->eventFilter(target, event));
}

void PythonQtWrapper_JmriJFrame::generateWindowRef(JmriJFrame* theWrappedObject)
{
  ( theWrappedObject->generateWindowRef());
}

bool  PythonQtWrapper_JmriJFrame::getAllowInFrameServlet(JmriJFrame* theWrappedObject)
{
  return ( theWrappedObject->getAllowInFrameServlet());
}

QString  PythonQtWrapper_JmriJFrame::getClassName(JmriJFrame* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_JmriJFrame*)theWrappedObject)->promoted_getClassName());
}

QWidget*  PythonQtWrapper_JmriJFrame::getContentPane(JmriJFrame* theWrappedObject)
{
  return ( theWrappedObject->getContentPane());
}

bool  PythonQtWrapper_JmriJFrame::getEscapeKeyClosesWindow(JmriJFrame* theWrappedObject)
{
  return ( theWrappedObject->getEscapeKeyClosesWindow());
}

JmriJFrame*  PythonQtWrapper_JmriJFrame::static_JmriJFrame_getFrame(QString  name)
{
  return (JmriJFrame::getFrame(name));
}

QList<JmriJFrame* >*  PythonQtWrapper_JmriJFrame::static_JmriJFrame_getFrameList()
{
  return (JmriJFrame::getFrameList());
}

QWidget*  PythonQtWrapper_JmriJFrame::getGlassPane(JmriJFrame* theWrappedObject)
{
  return ( theWrappedObject->getGlassPane());
}

bool  PythonQtWrapper_JmriJFrame::getModifiedFlag(JmriJFrame* theWrappedObject)
{
  return ( theWrappedObject->getModifiedFlag());
}

QString  PythonQtWrapper_JmriJFrame::getName(JmriJFrame* theWrappedObject)
{
  return ( theWrappedObject->getName());
}

QVariant  PythonQtWrapper_JmriJFrame::getProperty(JmriJFrame* theWrappedObject, QString  key)
{
  return ( ((PythonQtPublicPromoter_JmriJFrame*)theWrappedObject)->promoted_getProperty(key));
}

bool  PythonQtWrapper_JmriJFrame::getSavePosition(JmriJFrame* theWrappedObject)
{
  return ( theWrappedObject->getSavePosition());
}

bool  PythonQtWrapper_JmriJFrame::getSaveSize(JmriJFrame* theWrappedObject)
{
  return ( theWrappedObject->getSaveSize());
}

QString  PythonQtWrapper_JmriJFrame::getTitle(JmriJFrame* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_JmriJFrame*)theWrappedObject)->promoted_getTitle());
}

QString  PythonQtWrapper_JmriJFrame::getWindowFrameRef(JmriJFrame* theWrappedObject)
{
  return ( theWrappedObject->getWindowFrameRef());
}

void PythonQtWrapper_JmriJFrame::handleModified(JmriJFrame* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_JmriJFrame*)theWrappedObject)->promoted_handleModified());
}

void PythonQtWrapper_JmriJFrame::init(JmriJFrame* theWrappedObject, bool  saveSize, bool  savePosition)
{
  ( theWrappedObject->init(saveSize, savePosition));
}

void PythonQtWrapper_JmriJFrame::initComponents(JmriJFrame* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_JmriJFrame*)theWrappedObject)->promoted_initComponents());
}

void PythonQtWrapper_JmriJFrame::makePrivateWindow(JmriJFrame* theWrappedObject)
{
  ( theWrappedObject->makePrivateWindow());
}

void PythonQtWrapper_JmriJFrame::markWindowModified(JmriJFrame* theWrappedObject, bool  yes)
{
  ( theWrappedObject->markWindowModified(yes));
}

void PythonQtWrapper_JmriJFrame::moveEvent(JmriJFrame* theWrappedObject, QMoveEvent*  e)
{
  ( theWrappedObject->moveEvent(e));
}

void PythonQtWrapper_JmriJFrame::resizeEvent(JmriJFrame* theWrappedObject, QResizeEvent*  e)
{
  ( theWrappedObject->resizeEvent(e));
}

void PythonQtWrapper_JmriJFrame::setAllowInFrameServlet(JmriJFrame* theWrappedObject, bool  allow)
{
  ( theWrappedObject->setAllowInFrameServlet(allow));
}

void PythonQtWrapper_JmriJFrame::setAlwaysOnTop(JmriJFrame* theWrappedObject, bool  checked)
{
  ( theWrappedObject->setAlwaysOnTop(checked));
}

void PythonQtWrapper_JmriJFrame::setContentPane(JmriJFrame* theWrappedObject, QWidget*  arg__1)
{
  ( theWrappedObject->setContentPane(arg__1));
}

void PythonQtWrapper_JmriJFrame::setEscapeKeyClosesWindow(JmriJFrame* theWrappedObject, bool  closesWindow)
{
  ( theWrappedObject->setEscapeKeyClosesWindow(closesWindow));
}

void PythonQtWrapper_JmriJFrame::setFrameLocation(JmriJFrame* theWrappedObject)
{
  ( theWrappedObject->setFrameLocation());
}

void PythonQtWrapper_JmriJFrame::setFrameRef(JmriJFrame* theWrappedObject, QString  windowFrameRef)
{
  ( theWrappedObject->setFrameRef(windowFrameRef));
}

void PythonQtWrapper_JmriJFrame::setGlassPane(JmriJFrame* theWrappedObject, QWidget*  glassPane)
{
  ( theWrappedObject->setGlassPane(glassPane));
}

void PythonQtWrapper_JmriJFrame::setLocation(JmriJFrame* theWrappedObject, int  x, int  y)
{
  ( theWrappedObject->setLocation(x, y));
}

void PythonQtWrapper_JmriJFrame::setModifiedFlag(JmriJFrame* theWrappedObject, bool  flag)
{
  ( theWrappedObject->setModifiedFlag(flag));
}

void PythonQtWrapper_JmriJFrame::setName(JmriJFrame* theWrappedObject, QString  name)
{
  ( theWrappedObject->setName(name));
}

void PythonQtWrapper_JmriJFrame::setSavePosition(JmriJFrame* theWrappedObject, bool  save)
{
  ( theWrappedObject->setSavePosition(save));
}

void PythonQtWrapper_JmriJFrame::setSaveSize(JmriJFrame* theWrappedObject, bool  save)
{
  ( theWrappedObject->setSaveSize(save));
}

void PythonQtWrapper_JmriJFrame::setShutDownTask(JmriJFrame* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_JmriJFrame*)theWrappedObject)->promoted_setShutDownTask());
}

void PythonQtWrapper_JmriJFrame::setTitle(JmriJFrame* theWrappedObject, QString  _title)
{
  ( ((PythonQtPublicPromoter_JmriJFrame*)theWrappedObject)->promoted_setTitle(_title));
}

void PythonQtWrapper_JmriJFrame::setWindowTitle(JmriJFrame* theWrappedObject, const QString&  title)
{
  ( theWrappedObject->setWindowTitle(title));
}

void PythonQtWrapper_JmriJFrame::storeValues(JmriJFrame* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_JmriJFrame*)theWrappedObject)->promoted_storeValues());
}

void PythonQtWrapper_JmriJFrame::windowClosing(JmriJFrame* theWrappedObject, QCloseEvent*  e)
{
  ( ((PythonQtPublicPromoter_JmriJFrame*)theWrappedObject)->promoted_windowClosing(e));
}



PythonQtShell_LayoutBlockManager::~PythonQtShell_LayoutBlockManager() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_LayoutBlockManager::Register(NamedBean*  s0)
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
  LayoutBlockManager::Register(s0);
}
void PythonQtShell_LayoutBlockManager::addPropertyChangeListener(PropertyChangeListener*  l0)
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
  LayoutBlockManager::addPropertyChangeListener(l0);
}
void PythonQtShell_LayoutBlockManager::deregister(NamedBean*  s0)
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
  LayoutBlockManager::deregister(s0);
}
void PythonQtShell_LayoutBlockManager::dispose()
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
  LayoutBlockManager::dispose();
}
NamedBean*  PythonQtShell_LayoutBlockManager::getBeanBySystemName(QString  systemName0)
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
  return LayoutBlockManager::getBeanBySystemName(systemName0);
}
NamedBean*  PythonQtShell_LayoutBlockManager::getBeanByUserName(QString  userName0)
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
  return LayoutBlockManager::getBeanByUserName(userName0);
}
NamedBean*  PythonQtShell_LayoutBlockManager::getNamedBean(QString  name0)
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
  return LayoutBlockManager::getNamedBean(name0);
}
QStringList  PythonQtShell_LayoutBlockManager::getSystemNameArray()
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
  return LayoutBlockManager::getSystemNameArray();
}
QStringList  PythonQtShell_LayoutBlockManager::getSystemNameList()
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
  return LayoutBlockManager::getSystemNameList();
}
QString  PythonQtShell_LayoutBlockManager::makeSystemName(QString  s0)
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
  return LayoutBlockManager::makeSystemName(s0);
}
void PythonQtShell_LayoutBlockManager::removePropertyChangeListener(PropertyChangeListener*  l0)
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
  LayoutBlockManager::removePropertyChangeListener(l0);
}
void PythonQtShell_LayoutBlockManager::vetoableChange(PropertyChangeEvent*  evt0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("vetoableChange");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "PropertyChangeEvent*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&evt0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  LayoutBlockManager::vetoableChange(evt0);
}
LayoutBlockManager* PythonQtWrapper_LayoutBlockManager::new_LayoutBlockManager(QObject*  parent)
{ 
return new PythonQtShell_LayoutBlockManager(parent); }

LayoutBlockManager* PythonQtWrapper_LayoutBlockManager::new_LayoutBlockManager(const LayoutBlockManager&  arg__1)
{ 
return new PythonQtShell_LayoutBlockManager(arg__1); }

void PythonQtWrapper_LayoutBlockManager::addBadBeanError(LayoutBlockManager* theWrappedObject)
{
  ( theWrappedObject->addBadBeanError());
}

void PythonQtWrapper_LayoutBlockManager::enableAdvancedRouting(LayoutBlockManager* theWrappedObject, bool  boo)
{
  ( theWrappedObject->enableAdvancedRouting(boo));
}

QCompleter*  PythonQtWrapper_LayoutBlockManager::getCompleter(LayoutBlockManager* theWrappedObject, QString  text, bool  bIncludeUserNames)
{
  return ( theWrappedObject->getCompleter(text, bIncludeUserNames));
}

long  PythonQtWrapper_LayoutBlockManager::getLastRoutingChange(LayoutBlockManager* theWrappedObject)
{
  return ( theWrappedObject->getLastRoutingChange());
}

Sensor*  PythonQtWrapper_LayoutBlockManager::getStabilisedSensor(LayoutBlockManager* theWrappedObject)
{
  return ( theWrappedObject->getStabilisedSensor());
}

QString  PythonQtWrapper_LayoutBlockManager::getSystemPrefix(LayoutBlockManager* theWrappedObject)
{
  return ( theWrappedObject->getSystemPrefix());
}

int  PythonQtWrapper_LayoutBlockManager::getXMLOrder(LayoutBlockManager* theWrappedObject)
{
  return ( theWrappedObject->getXMLOrder());
}

void PythonQtWrapper_LayoutBlockManager::initializeLayoutBlockPaths(LayoutBlockManager* theWrappedObject)
{
  ( theWrappedObject->initializeLayoutBlockPaths());
}

LayoutBlockManager*  PythonQtWrapper_LayoutBlockManager::static_LayoutBlockManager_instance()
{
  return (LayoutBlockManager::instance());
}

bool  PythonQtWrapper_LayoutBlockManager::isAdvancedRoutingEnabled(LayoutBlockManager* theWrappedObject)
{
  return ( theWrappedObject->isAdvancedRoutingEnabled());
}

bool  PythonQtWrapper_LayoutBlockManager::isAssignableFromType(LayoutBlockManager* theWrappedObject)
{
  return ( theWrappedObject->isAssignableFromType());
}

bool  PythonQtWrapper_LayoutBlockManager::routingStablised(LayoutBlockManager* theWrappedObject)
{
  return ( theWrappedObject->routingStablised());
}

void PythonQtWrapper_LayoutBlockManager::setLastRoutingChange(LayoutBlockManager* theWrappedObject)
{
  ( theWrappedObject->setLastRoutingChange());
}

void PythonQtWrapper_LayoutBlockManager::setStabilisedSensor(LayoutBlockManager* theWrappedObject, QString  pName) throw (JmriException)
{
  ( theWrappedObject->setStabilisedSensor(pName));
}

void PythonQtWrapper_LayoutBlockManager::turnOffWarning(LayoutBlockManager* theWrappedObject)
{
  ( theWrappedObject->turnOffWarning());
}

char  PythonQtWrapper_LayoutBlockManager::typeLetter(LayoutBlockManager* theWrappedObject)
{
  return ( theWrappedObject->typeLetter());
}

bool  PythonQtWrapper_LayoutBlockManager::warn(LayoutBlockManager* theWrappedObject)
{
  return ( theWrappedObject->warn());
}



PythonQtShell_Light::~PythonQtShell_Light() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_Light::activateLight()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("activateLight");
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
  Light::activateLight();
}
void PythonQtShell_Light::clearLightControls()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("clearLightControls");
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
  Light::clearLightControls();
}
void PythonQtShell_Light::deactivateLight()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("deactivateLight");
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
  Light::deactivateLight();
}
double  PythonQtShell_Light::getCurrentIntensity()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getCurrentIntensity");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getCurrentIntensity", methodInfo, result);
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
  return Light::getCurrentIntensity();
}
bool  PythonQtShell_Light::getEnabled()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getEnabled");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getEnabled", methodInfo, result);
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
  return Light::getEnabled();
}
double  PythonQtShell_Light::getMaxIntensity()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getMaxIntensity");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getMaxIntensity", methodInfo, result);
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
  return Light::getMaxIntensity();
}
double  PythonQtShell_Light::getMinIntensity()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getMinIntensity");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getMinIntensity", methodInfo, result);
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
  return double();
}
int  PythonQtShell_Light::getState()
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
  return Light::getState();
}
double  PythonQtShell_Light::getTargetIntensity()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getTargetIntensity");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getTargetIntensity", methodInfo, result);
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
  return Light::getTargetIntensity();
}
double  PythonQtShell_Light::getTransitionTime()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getTransitionTime");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getTransitionTime", methodInfo, result);
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
  return Light::getTransitionTime();
}
bool  PythonQtShell_Light::isIntensityVariable()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("isIntensityVariable");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("isIntensityVariable", methodInfo, result);
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
  return Light::isIntensityVariable();
}
bool  PythonQtShell_Light::isTransitionAvailable()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("isTransitionAvailable");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("isTransitionAvailable", methodInfo, result);
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
  return Light::isTransitionAvailable();
}
bool  PythonQtShell_Light::isTransitioning()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("isTransitioning");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("isTransitioning", methodInfo, result);
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
  return Light::isTransitioning();
}
void PythonQtShell_Light::setEnabled(bool  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setEnabled");
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
  Light::setEnabled(arg__1);
}
void PythonQtShell_Light::setMaxIntensity(double  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setMaxIntensity");
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
  Light::setMaxIntensity(arg__1);
}
void PythonQtShell_Light::setMinIntensity(double  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setMinIntensity");
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
  Light::setMinIntensity(arg__1);
}
void PythonQtShell_Light::setState(int  arg__1)
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
  Light::setState(arg__1);
}
void PythonQtShell_Light::setTargetIntensity(double  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setTargetIntensity");
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
  Light::setTargetIntensity(arg__1);
}
void PythonQtShell_Light::setTransitionTime(double  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setTransitionTime");
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
  Light::setTransitionTime(arg__1);
}
Light* PythonQtWrapper_Light::new_Light(QObject*  parent)
{ 
return new PythonQtShell_Light(parent); }

Light* PythonQtWrapper_Light::new_Light(QString  sysName, QObject*  parent)
{ 
return new PythonQtShell_Light(sysName, parent); }

Light* PythonQtWrapper_Light::new_Light(QString  sysName, QString  userName, QObject*  parent)
{ 
return new PythonQtShell_Light(sysName, userName, parent); }

void PythonQtWrapper_Light::activateLight(Light* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_Light*)theWrappedObject)->promoted_activateLight());
}

void PythonQtWrapper_Light::clearLightControls(Light* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_Light*)theWrappedObject)->promoted_clearLightControls());
}

void PythonQtWrapper_Light::deactivateLight(Light* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_Light*)theWrappedObject)->promoted_deactivateLight());
}

double  PythonQtWrapper_Light::getCurrentIntensity(Light* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Light*)theWrappedObject)->promoted_getCurrentIntensity());
}

bool  PythonQtWrapper_Light::getEnabled(Light* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Light*)theWrappedObject)->promoted_getEnabled());
}

double  PythonQtWrapper_Light::getMaxIntensity(Light* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Light*)theWrappedObject)->promoted_getMaxIntensity());
}

double  PythonQtWrapper_Light::getMinIntensity(Light* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Light*)theWrappedObject)->promoted_getMinIntensity());
}

int  PythonQtWrapper_Light::getState(Light* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Light*)theWrappedObject)->promoted_getState());
}

double  PythonQtWrapper_Light::getTargetIntensity(Light* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Light*)theWrappedObject)->promoted_getTargetIntensity());
}

double  PythonQtWrapper_Light::getTransitionTime(Light* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Light*)theWrappedObject)->promoted_getTransitionTime());
}

bool  PythonQtWrapper_Light::isIntensityVariable(Light* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Light*)theWrappedObject)->promoted_isIntensityVariable());
}

bool  PythonQtWrapper_Light::isTransitionAvailable(Light* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Light*)theWrappedObject)->promoted_isTransitionAvailable());
}

bool  PythonQtWrapper_Light::isTransitioning(Light* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_Light*)theWrappedObject)->promoted_isTransitioning());
}

void PythonQtWrapper_Light::setEnabled(Light* theWrappedObject, bool  arg__1)
{
  ( ((PythonQtPublicPromoter_Light*)theWrappedObject)->promoted_setEnabled(arg__1));
}

void PythonQtWrapper_Light::setMaxIntensity(Light* theWrappedObject, double  arg__1)
{
  ( ((PythonQtPublicPromoter_Light*)theWrappedObject)->promoted_setMaxIntensity(arg__1));
}

void PythonQtWrapper_Light::setMinIntensity(Light* theWrappedObject, double  arg__1)
{
  ( ((PythonQtPublicPromoter_Light*)theWrappedObject)->promoted_setMinIntensity(arg__1));
}

void PythonQtWrapper_Light::setState(Light* theWrappedObject, int  arg__1)
{
  ( ((PythonQtPublicPromoter_Light*)theWrappedObject)->promoted_setState(arg__1));
}

void PythonQtWrapper_Light::setTargetIntensity(Light* theWrappedObject, double  arg__1)
{
  ( ((PythonQtPublicPromoter_Light*)theWrappedObject)->promoted_setTargetIntensity(arg__1));
}

void PythonQtWrapper_Light::setTransitionTime(Light* theWrappedObject, double  arg__1)
{
  ( ((PythonQtPublicPromoter_Light*)theWrappedObject)->promoted_setTransitionTime(arg__1));
}



PythonQtShell_LnPacketizer::~PythonQtShell_LnPacketizer() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
bool  PythonQtShell_LnPacketizer::isXmtBusy()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("isXmtBusy");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("isXmtBusy", methodInfo, result);
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
  return LnPacketizer::isXmtBusy();
}
void PythonQtShell_LnPacketizer::sendLocoNetMessage(LocoNetMessage*  m0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("sendLocoNetMessage");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "LocoNetMessage*"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&m0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  LnPacketizer::sendLocoNetMessage(m0);
}
bool  PythonQtShell_LnPacketizer::status()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("status");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("status", methodInfo, result);
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
  return LnPacketizer::status();
}
LnPacketizer* PythonQtWrapper_LnPacketizer::new_LnPacketizer(QObject*  parent)
{ 
return new PythonQtShell_LnPacketizer(parent); }

void PythonQtWrapper_LnPacketizer::connectPort(LnPacketizer* theWrappedObject, LnPortController*  p)
{
  ( theWrappedObject->connectPort(p));
}

void PythonQtWrapper_LnPacketizer::disconnectPort(LnPacketizer* theWrappedObject, LnPortController*  p)
{
  ( theWrappedObject->disconnectPort(p));
}

QString  PythonQtWrapper_LnPacketizer::static_LnPacketizer_hexStringFromBytes(const QByteArray&  a)
{
  return (LnPacketizer::hexStringFromBytes(a));
}

bool  PythonQtWrapper_LnPacketizer::isXmtBusy(LnPacketizer* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_LnPacketizer*)theWrappedObject)->promoted_isXmtBusy());
}

void PythonQtWrapper_LnPacketizer::sendLocoNetMessage(LnPacketizer* theWrappedObject, LocoNetMessage*  m)
{
  ( ((PythonQtPublicPromoter_LnPacketizer*)theWrappedObject)->promoted_sendLocoNetMessage(m));
}

void PythonQtWrapper_LnPacketizer::startThreads(LnPacketizer* theWrappedObject)
{
  ( theWrappedObject->startThreads());
}

bool  PythonQtWrapper_LnPacketizer::status(LnPacketizer* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_LnPacketizer*)theWrappedObject)->promoted_status());
}



QDataStream*  PythonQtWrapper_LnPortController::getInputStream(LnPortController* theWrappedObject)
{
  return ( theWrappedObject->getInputStream());
}

QDataStream*  PythonQtWrapper_LnPortController::getOutputStream(LnPortController* theWrappedObject)
{
  return ( theWrappedObject->getOutputStream());
}

bool  PythonQtWrapper_LnPortController::okToSend(LnPortController* theWrappedObject)
{
  return ( theWrappedObject->okToSend());
}

void PythonQtWrapper_LnPortController::setCommandStationType(LnPortController* theWrappedObject, QString  name)
{
  ( theWrappedObject->setCommandStationType(name));
}

void PythonQtWrapper_LnPortController::setDisabled(LnPortController* theWrappedObject, bool  disabled)
{
  ( theWrappedObject->setDisabled(disabled));
}

void PythonQtWrapper_LnPortController::setTurnoutHandling(LnPortController* theWrappedObject, QString  value)
{
  ( theWrappedObject->setTurnoutHandling(value));
}

bool  PythonQtWrapper_LnPortController::status(LnPortController* theWrappedObject)
{
  return ( theWrappedObject->status());
}



void PythonQtWrapper_LnPowerManager::dispose(LnPowerManager* theWrappedObject)
{
  ( theWrappedObject->dispose());
}

int  PythonQtWrapper_LnPowerManager::getPower(LnPowerManager* theWrappedObject)
{
  return ( theWrappedObject->getPower());
}

bool  PythonQtWrapper_LnPowerManager::isPowerOff(LnPowerManager* theWrappedObject)
{
  return ( theWrappedObject->isPowerOff());
}

bool  PythonQtWrapper_LnPowerManager::isPowerOn(LnPowerManager* theWrappedObject)
{
  return ( theWrappedObject->isPowerOn());
}

bool  PythonQtWrapper_LnPowerManager::isPowerUnknown(LnPowerManager* theWrappedObject)
{
  return ( theWrappedObject->isPowerUnknown());
}

void PythonQtWrapper_LnPowerManager::setPower(LnPowerManager* theWrappedObject, int  v)
{
  ( theWrappedObject->setPower(v));
}



PythonQtShell_LnSensor::~PythonQtShell_LnSensor() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
void PythonQtShell_LnSensor::addPropertyChangeListener(PropertyChangeListener*  arg__1) const
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
  LnSensor::addPropertyChangeListener(arg__1);
}
bool  PythonQtShell_LnSensor::canInvert()
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
  return LnSensor::canInvert();
}
void PythonQtShell_LnSensor::dispose()
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
  LnSensor::dispose();
}
bool  PythonQtShell_LnSensor::getInverted()
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
  return LnSensor::getInverted();
}
int  PythonQtShell_LnSensor::getKnownState() const
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
  return LnSensor::getKnownState();
}
int  PythonQtShell_LnSensor::getRawState()
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
  return LnSensor::getRawState();
}
long  PythonQtShell_LnSensor::getSensorDebounceGoingActiveTimer()
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
  return LnSensor::getSensorDebounceGoingActiveTimer();
}
long  PythonQtShell_LnSensor::getSensorDebounceGoingInActiveTimer()
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
  return LnSensor::getSensorDebounceGoingInActiveTimer();
}
void PythonQtShell_LnSensor::removePropertyChangeListener(PropertyChangeListener*  arg__1) const
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
  LnSensor::removePropertyChangeListener(arg__1);
}
void PythonQtShell_LnSensor::requestUpdateFromLayout() const
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
  LnSensor::requestUpdateFromLayout();
}
void PythonQtShell_LnSensor::setInverted(bool  inverted0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setInverted");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&inverted0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  LnSensor::setInverted(inverted0);
}
void PythonQtShell_LnSensor::setKnownState(int  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setKnownState");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int"};
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
  LnSensor::setKnownState(s0);
}
void PythonQtShell_LnSensor::setSensorDebounceGoingActiveTimer(long  time0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setSensorDebounceGoingActiveTimer");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "long"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&time0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  LnSensor::setSensorDebounceGoingActiveTimer(time0);
}
void PythonQtShell_LnSensor::setSensorDebounceGoingInActiveTimer(long  time0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setSensorDebounceGoingInActiveTimer");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "long"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&time0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  LnSensor::setSensorDebounceGoingInActiveTimer(time0);
}
bool  PythonQtShell_LnSensor::useDefaultTimerSettings()
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
  return LnSensor::useDefaultTimerSettings();
}
void PythonQtShell_LnSensor::useDefaultTimerSettings(bool  boo0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("useDefaultTimerSettings");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&boo0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  LnSensor::useDefaultTimerSettings(boo0);
}
LnSensor* PythonQtWrapper_LnSensor::new_LnSensor(QString  systemName, LnTrafficController*  tc, QString  prefix, QObject*  parent)
{ 
return new PythonQtShell_LnSensor(systemName, tc, prefix, parent); }

LnSensor* PythonQtWrapper_LnSensor::new_LnSensor(QString  systemName, QString  userName, LnTrafficController*  tc, QString  prefix, QObject*  parent)
{ 
return new PythonQtShell_LnSensor(systemName, userName, tc, prefix, parent); }

void PythonQtWrapper_LnSensor::dispose(LnSensor* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_LnSensor*)theWrappedObject)->promoted_dispose());
}

void PythonQtWrapper_LnSensor::requestUpdateFromLayout(LnSensor* theWrappedObject) const
{
  ( ((PythonQtPublicPromoter_LnSensor*)theWrappedObject)->promoted_requestUpdateFromLayout());
}

void PythonQtWrapper_LnSensor::setKnownState(LnSensor* theWrappedObject, int  s)
{
  ( ((PythonQtPublicPromoter_LnSensor*)theWrappedObject)->promoted_setKnownState(s));
}



PythonQtShell_LnTrafficController::~PythonQtShell_LnTrafficController() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
bool  PythonQtShell_LnTrafficController::isXmtBusy()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("isXmtBusy");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("isXmtBusy", methodInfo, result);
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
  return LnTrafficController::isXmtBusy();
}
void PythonQtShell_LnTrafficController::sendLocoNetMessage(LocoNetMessage*  arg__1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("sendLocoNetMessage");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "LocoNetMessage*"};
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
  LnTrafficController::sendLocoNetMessage(arg__1);
}
bool  PythonQtShell_LnTrafficController::status()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("status");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("status", methodInfo, result);
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
  return LnTrafficController::status();
}
LnTrafficController* PythonQtWrapper_LnTrafficController::new_LnTrafficController()
{ 
return new PythonQtShell_LnTrafficController(); }

int  PythonQtWrapper_LnTrafficController::getReceivedByteCount(LnTrafficController* theWrappedObject)
{
  return ( theWrappedObject->getReceivedByteCount());
}

int  PythonQtWrapper_LnTrafficController::getReceivedMsgCount(LnTrafficController* theWrappedObject)
{
  return ( theWrappedObject->getReceivedMsgCount());
}

int  PythonQtWrapper_LnTrafficController::getTransmittedMsgCount(LnTrafficController* theWrappedObject)
{
  return ( theWrappedObject->getTransmittedMsgCount());
}

LnTrafficController*  PythonQtWrapper_LnTrafficController::instance(LnTrafficController* theWrappedObject)
{
  return ( theWrappedObject->instance());
}

bool  PythonQtWrapper_LnTrafficController::isXmtBusy(LnTrafficController* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_LnTrafficController*)theWrappedObject)->promoted_isXmtBusy());
}

void PythonQtWrapper_LnTrafficController::resetStatistics(LnTrafficController* theWrappedObject)
{
  ( theWrappedObject->resetStatistics());
}

void PythonQtWrapper_LnTrafficController::sendLocoNetMessage(LnTrafficController* theWrappedObject, LocoNetMessage*  arg__1)
{
  ( ((PythonQtPublicPromoter_LnTrafficController*)theWrappedObject)->promoted_sendLocoNetMessage(arg__1));
}

bool  PythonQtWrapper_LnTrafficController::status(LnTrafficController* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_LnTrafficController*)theWrappedObject)->promoted_status());
}



PythonQtShell_LnTurnout::~PythonQtShell_LnTurnout() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
bool  PythonQtShell_LnTurnout::canInvert()
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
  return LnTurnout::canInvert();
}
bool  PythonQtShell_LnTurnout::canLock(int  turnoutLockout0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("canLock");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&turnoutLockout0};
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
  return LnTurnout::canLock(turnoutLockout0);
}
void PythonQtShell_LnTurnout::dispose()
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
  LnTurnout::dispose();
}
void PythonQtShell_LnTurnout::enableLockOperation(int  turnoutLockout0, bool  enabled1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("enableLockOperation");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
    void* args[3] = {NULL, (void*)&turnoutLockout0, (void*)&enabled1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  LnTurnout::enableLockOperation(turnoutLockout0, enabled1);
}
void PythonQtShell_LnTurnout::forwardCommandChangeToLayout(int  newstate0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("forwardCommandChangeToLayout");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&newstate0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  LnTurnout::forwardCommandChangeToLayout(newstate0);
}
int  PythonQtShell_LnTurnout::getCommandedState()
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
  return LnTurnout::getCommandedState();
}
int  PythonQtShell_LnTurnout::getControlType()
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
  return LnTurnout::getControlType();
}
QString  PythonQtShell_LnTurnout::getDecoderName()
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
  return LnTurnout::getDecoderName();
}
float  PythonQtShell_LnTurnout::getDivergingLimit()
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
  return LnTurnout::getDivergingLimit();
}
QString  PythonQtShell_LnTurnout::getDivergingSpeed()
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
  return LnTurnout::getDivergingSpeed();
}
int  PythonQtShell_LnTurnout::getFeedbackMode()
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
  return LnTurnout::getFeedbackMode();
}
QString  PythonQtShell_LnTurnout::getFeedbackModeName()
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
  return LnTurnout::getFeedbackModeName();
}
Sensor*  PythonQtShell_LnTurnout::getFirstSensor()
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
  return LnTurnout::getFirstSensor();
}
bool  PythonQtShell_LnTurnout::getInhibitOperation()
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
  return LnTurnout::getInhibitOperation();
}
bool  PythonQtShell_LnTurnout::getInverted()
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
  return LnTurnout::getInverted();
}
int  PythonQtShell_LnTurnout::getKnownState()
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
  return LnTurnout::getKnownState();
}
bool  PythonQtShell_LnTurnout::getLocked(int  turnoutLockout0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getLocked");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"bool" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
      bool returnValue;
    void* args[2] = {NULL, (void*)&turnoutLockout0};
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
  return LnTurnout::getLocked(turnoutLockout0);
}
int  PythonQtShell_LnTurnout::getNumberOutputBits()
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
  return LnTurnout::getNumberOutputBits();
}
int  PythonQtShell_LnTurnout::getPossibleLockModes()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getPossibleLockModes");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getPossibleLockModes", methodInfo, result);
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
  return LnTurnout::getPossibleLockModes();
}
bool  PythonQtShell_LnTurnout::getReportLocked()
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
  return LnTurnout::getReportLocked();
}
Sensor*  PythonQtShell_LnTurnout::getSecondSensor()
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
  return LnTurnout::getSecondSensor();
}
int  PythonQtShell_LnTurnout::getState()
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
  return LnTurnout::getState();
}
float  PythonQtShell_LnTurnout::getStraightLimit()
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
  return LnTurnout::getStraightLimit();
}
QString  PythonQtShell_LnTurnout::getStraightSpeed()
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
  return LnTurnout::getStraightSpeed();
}
QStringList  PythonQtShell_LnTurnout::getValidDecoderNames()
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
  return LnTurnout::getValidDecoderNames();
}
QStringList  PythonQtShell_LnTurnout::getValidFeedbackNames()
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
  return LnTurnout::getValidFeedbackNames();
}
int  PythonQtShell_LnTurnout::getValidFeedbackTypes()
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
  return LnTurnout::getValidFeedbackTypes();
}
bool  PythonQtShell_LnTurnout::isConsistentState()
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
  return LnTurnout::isConsistentState();
}
void PythonQtShell_LnTurnout::provideFirstFeedbackSensor(QString  pName0) throw(JmriException)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("provideFirstFeedbackSensor");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&pName0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  LnTurnout::provideFirstFeedbackSensor(pName0);
}
void PythonQtShell_LnTurnout::provideSecondFeedbackSensor(QString  pName0) throw(JmriException)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("provideSecondFeedbackSensor");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&pName0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  LnTurnout::provideSecondFeedbackSensor(pName0);
}
void PythonQtShell_LnTurnout::requestUpdateFromLayout()
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
  LnTurnout::requestUpdateFromLayout();
}
void PythonQtShell_LnTurnout::setBinaryOutput(bool  state0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setBinaryOutput");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&state0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  LnTurnout::setBinaryOutput(state0);
}
void PythonQtShell_LnTurnout::setCommandedState(int  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setCommandedState");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int"};
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
  LnTurnout::setCommandedState(s0);
}
void PythonQtShell_LnTurnout::setControlType(int  num0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setControlType");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&num0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  LnTurnout::setControlType(num0);
}
void PythonQtShell_LnTurnout::setDecoderName(QString  decoderName0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setDecoderName");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&decoderName0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  LnTurnout::setDecoderName(decoderName0);
}
void PythonQtShell_LnTurnout::setDivergingSpeed(QString  s0) throw(JmriException)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setDivergingSpeed");
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
  LnTurnout::setDivergingSpeed(s0);
}
void PythonQtShell_LnTurnout::setFeedbackMode(QString  mode0) throw(IllegalArgumentException)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setFeedbackMode");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "QString"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&mode0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  LnTurnout::setFeedbackMode(mode0);
}
void PythonQtShell_LnTurnout::setFeedbackMode(int  mode0) throw(IllegalArgumentException)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setFeedbackMode");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&mode0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  LnTurnout::setFeedbackMode(mode0);
}
void PythonQtShell_LnTurnout::setInhibitOperation(bool  io0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setInhibitOperation");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&io0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  LnTurnout::setInhibitOperation(io0);
}
void PythonQtShell_LnTurnout::setInitialKnownStateFromFeedback()
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
  LnTurnout::setInitialKnownStateFromFeedback();
}
void PythonQtShell_LnTurnout::setInverted(bool  inverted0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setInverted");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&inverted0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  LnTurnout::setInverted(inverted0);
}
void PythonQtShell_LnTurnout::setLocked(int  turnoutLockout0, bool  locked1)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setLocked");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(3, argumentList);
    void* args[3] = {NULL, (void*)&turnoutLockout0, (void*)&locked1};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  LnTurnout::setLocked(turnoutLockout0, locked1);
}
void PythonQtShell_LnTurnout::setNumberOutputBits(int  num0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setNumberOutputBits");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&num0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  LnTurnout::setNumberOutputBits(num0);
}
void PythonQtShell_LnTurnout::setReportLocked(bool  reportLocked0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setReportLocked");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&reportLocked0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  LnTurnout::setReportLocked(reportLocked0);
}
void PythonQtShell_LnTurnout::setState(int  s0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setState");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "int"};
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
  LnTurnout::setState(s0);
}
void PythonQtShell_LnTurnout::setStraightSpeed(QString  s0) throw(JmriException)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("setStraightSpeed");
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
  LnTurnout::setStraightSpeed(s0);
}
void PythonQtShell_LnTurnout::turnoutPushbuttonLockout(bool  _pushButtonLockout0)
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("turnoutPushbuttonLockout");
  PyObject* obj = PyBaseObject_Type.tp_getattro((PyObject*)_wrapper, name);
  if (obj) {
    static const char* argumentList[] ={"" , "bool"};
    static const PythonQtMethodInfo* methodInfo = PythonQtMethodInfo::getCachedMethodInfoFromArgumentList(2, argumentList);
    void* args[2] = {NULL, (void*)&_pushButtonLockout0};
    PyObject* result = PythonQtSignalTarget::call(obj, methodInfo, args, true);
    if (result) { Py_DECREF(result); } 
    Py_DECREF(obj);
    return;
  } else {
    PyErr_Clear();
  }
}
  LnTurnout::turnoutPushbuttonLockout(_pushButtonLockout0);
}
LnTurnout* PythonQtWrapper_LnTurnout::new_LnTurnout(QString  prefix, int  number, LnTrafficController*  controller, QObject*  parent)
{ 
return new PythonQtShell_LnTurnout(prefix, number, controller, parent); }

bool  PythonQtWrapper_LnTurnout::canInvert(LnTurnout* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_LnTurnout*)theWrappedObject)->promoted_canInvert());
}

void PythonQtWrapper_LnTurnout::dispose(LnTurnout* theWrappedObject)
{
  ( ((PythonQtPublicPromoter_LnTurnout*)theWrappedObject)->promoted_dispose());
}

void PythonQtWrapper_LnTurnout::forwardCommandChangeToLayout(LnTurnout* theWrappedObject, int  newstate)
{
  ( ((PythonQtPublicPromoter_LnTurnout*)theWrappedObject)->promoted_forwardCommandChangeToLayout(newstate));
}

int  PythonQtWrapper_LnTurnout::getNumber(LnTurnout* theWrappedObject)
{
  return ( theWrappedObject->getNumber());
}

void PythonQtWrapper_LnTurnout::sendOpcSwReqMessage(LnTurnout* theWrappedObject, int  state, bool  on)
{
  ( theWrappedObject->sendOpcSwReqMessage(state, on));
}

void PythonQtWrapper_LnTurnout::sendSetOffMessage(LnTurnout* theWrappedObject, int  state)
{
  ( theWrappedObject->sendSetOffMessage(state));
}

void PythonQtWrapper_LnTurnout::turnoutPushbuttonLockout(LnTurnout* theWrappedObject, bool  _pushButtonLockout)
{
  ( ((PythonQtPublicPromoter_LnTurnout*)theWrappedObject)->promoted_turnoutPushbuttonLockout(_pushButtonLockout));
}



PythonQtShell_LocoAddress::~PythonQtShell_LocoAddress() {
  PythonQtPrivate* priv = PythonQt::priv();
  if (priv) { priv->shellClassDeleted(this); }
}
int  PythonQtShell_LocoAddress::getNumber()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("getNumber");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("getNumber", methodInfo, result);
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
  return LocoAddress::getNumber();
}
QString  PythonQtShell_LocoAddress::toString()
{
if (_wrapper && (((PyObject*)_wrapper)->ob_refcnt > 0)) {
  static PyObject* name = PyString_FromString("toString");
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
          PythonQt::priv()->handleVirtualOverloadReturnError("toString", methodInfo, result);
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
  return LocoAddress::toString();
}
LocoAddress* PythonQtWrapper_LocoAddress::new_LocoAddress()
{ 
return new PythonQtShell_LocoAddress(); }

int  PythonQtWrapper_LocoAddress::getNumber(LocoAddress* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_LocoAddress*)theWrappedObject)->promoted_getNumber());
}

QString  PythonQtWrapper_LocoAddress::toString(LocoAddress* theWrappedObject)
{
  return ( ((PythonQtPublicPromoter_LocoAddress*)theWrappedObject)->promoted_toString());
}

QString PythonQtWrapper_LocoAddress::py_toString(LocoAddress* obj) { return obj->toString(); }

