#include <PythonQt.h>
#include <QObject>
#include <QVariant>
#include <abstractautomaton.h>
#include <abstractmanager.h>
#include <abstractnamedbean.h>
#include <abstractproxymanager.h>
#include <abstractsensor.h>
#include <abstractsensormanager.h>
#include <abstractserialportcontroller.h>
#include <abstractturnout.h>
#include <audio.h>
#include <audiobuffer.h>
#include <audiolistener.h>
#include <audiomanager.h>
#include <audiosource.h>
#include <commandstation.h>
#include <dcclocoaddress.h>
#include <dccthrottle.h>
#include <editor.h>
#include <eventobject.h>
#include <fileutil.h>
#include <flowlayout.h>
#include <instancemanager.h>
#include <jframe.h>
#include <jmrijframe.h>
#include <layoutblockmanager.h>
#include <light.h>
#include <lnpacketizer.h>
#include <lnportcontroller.h>
#include <lnsensor.h>
#include <lntrafficcontroller.h>
#include <lnturnout.h>
#include <locoaddress.h>
#include <loconetmessage.h>
#include <manager.h>
#include <memorymanager.h>
#include <namedbean.h>
#include <positionable.h>
#include <powermanager.h>
#include <programmermanager.h>
#include <propertychangeevent.h>
#include <propertychangelistener.h>
#include <qaction.h>
#include <qbytearray.h>
#include <qcolor.h>
#include <qcompleter.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qdatastream.h>
#include <qdir.h>
#include <qevent.h>
#include <qfile.h>
#include <qfont.h>
#include <qgraphicsproxywidget.h>
#include <qgraphicsscene.h>
#include <qgraphicssceneevent.h>
#include <qicon.h>
#include <qkeysequence.h>
#include <qlayout.h>
#include <qlayoutitem.h>
#include <qlist.h>
#include <qlocale.h>
#include <qmainwindow.h>
#include <qmargins.h>
#include <qmenu.h>
#include <qobject.h>
#include <qpaintdevice.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpoint.h>
#include <qqueue.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstringlist.h>
#include <qstyle.h>
#include <qurl.h>
#include <qvector.h>
#include <qvector3d.h>
#include <qwidget.h>
#include <reportermanager.h>
#include <routemanager.h>
#include <sensor.h>
#include <sensormanager.h>
#include <shutdownmanager.h>
#include <turnout.h>
#include <windowlistener.h>
#include "liblayouteditor_global.h"


class LIBLAYOUTEDITORSHARED_EXPORT PythonQtShell_AbstractAutomaton : public AbstractAutomaton
{
public:
    PythonQtShell_AbstractAutomaton(QObject*  parent = 0):AbstractAutomaton(parent),_wrapper(NULL) {};
    PythonQtShell_AbstractAutomaton(QString  name, QObject*  parent = 0):AbstractAutomaton(name, parent),_wrapper(NULL) {};

   ~PythonQtShell_AbstractAutomaton();

virtual void childEvent(QChildEvent*  arg__1);
virtual void customEvent(QEvent*  arg__1);
virtual bool  event(QEvent*  arg__1);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual bool  handle();
virtual void init();
virtual void timerEvent(QTimerEvent*  arg__1);

  PythonQtInstanceWrapper* _wrapper; 
};

class LIBLAYOUTEDITORSHARED_EXPORT PythonQtPublicPromoter_AbstractAutomaton : public AbstractAutomaton
{ public:
inline bool  promoted_handle() { return AbstractAutomaton::handle(); }
inline void promoted_init() { AbstractAutomaton::init(); }
inline void promoted_wait(int  milliseconds) { AbstractAutomaton::wait(milliseconds); }
};

class LIBLAYOUTEDITORSHARED_EXPORT PythonQtWrapper_AbstractAutomaton : public QObject
{ Q_OBJECT
public:
public slots:
AbstractAutomaton* new_AbstractAutomaton(QObject*  parent = 0);
AbstractAutomaton* new_AbstractAutomaton(QString  name, QObject*  parent = 0);
void delete_AbstractAutomaton(AbstractAutomaton* obj) { delete obj; } 
   void defaultName(AbstractAutomaton* theWrappedObject);
   void done(AbstractAutomaton* theWrappedObject);
   int  getCount(AbstractAutomaton* theWrappedObject);
   QString  getName(AbstractAutomaton* theWrappedObject);
   DccThrottle*  getThrottle(AbstractAutomaton* theWrappedObject, int  address, bool  longAddress);
   bool  handle(AbstractAutomaton* theWrappedObject);
   void init(AbstractAutomaton* theWrappedObject);
   void notifyAll(AbstractAutomaton* theWrappedObject);
   void notifyFailedThrottleRequest(AbstractAutomaton* theWrappedObject, DccLocoAddress*  address, QString  reason);
   void notifyThrottleFound(AbstractAutomaton* theWrappedObject, DccThrottle*  t);
   int  readServiceModeCV(AbstractAutomaton* theWrappedObject, int  CV);
   void setName(AbstractAutomaton* theWrappedObject, QString  name);
   void setTerminateSensor(AbstractAutomaton* theWrappedObject, Sensor*  ts);
   void setTurnouts(AbstractAutomaton* theWrappedObject, QList<Turnout* >  closed, QList<Turnout* >  thrown);
   void start(AbstractAutomaton* theWrappedObject, bool  bRunInThread = true);
   void stop(AbstractAutomaton* theWrappedObject);
   void wait(AbstractAutomaton* theWrappedObject, int  milliseconds);
   void waitChange(AbstractAutomaton* theWrappedObject, QVector<NamedBean* >  mInputs);
   void waitMsec(AbstractAutomaton* theWrappedObject, int  milliseconds);
   void waitSensorActive(AbstractAutomaton* theWrappedObject, QList<Sensor* >  mSensors);
   void waitSensorActive(AbstractAutomaton* theWrappedObject, Sensor*  mSensor);
   void waitSensorChange(AbstractAutomaton* theWrappedObject, QList<Sensor* >  mSensors);
   int  waitSensorChange(AbstractAutomaton* theWrappedObject, int  mState, Sensor*  mSensor);
   void waitSensorInactive(AbstractAutomaton* theWrappedObject, QList<Sensor* >  mSensors);
   void waitSensorInactive(AbstractAutomaton* theWrappedObject, Sensor*  mSensor);
   void waitSensorState(AbstractAutomaton* theWrappedObject, QList<Sensor* >  mSensors, int  state);
   void waitSensorState(AbstractAutomaton* theWrappedObject, Sensor*  mSensor, int  state);
   void waitTurnoutConsistent(AbstractAutomaton* theWrappedObject, QList<Turnout* >  mTurnouts);
   bool  writeOpsModeCV(AbstractAutomaton* theWrappedObject, int  CV, int  value, bool  longAddress, int  loco);
   bool  writeServiceModeCV(AbstractAutomaton* theWrappedObject, int  CV, int  value);
};





class LIBLAYOUTEDITORSHARED_EXPORT PythonQtShell_AbstractManager : public AbstractManager
{
public:
    PythonQtShell_AbstractManager(QObject*  parent = 0):AbstractManager(parent),_wrapper(NULL) {};

   ~PythonQtShell_AbstractManager();

virtual void Register(NamedBean*  s);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void childEvent(QChildEvent*  arg__1);
virtual void customEvent(QEvent*  arg__1);
virtual void deregister(NamedBean*  s);
virtual void dispose();
virtual bool  event(QEvent*  arg__1);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual NamedBean*  getBeanBySystemName(QString  systemName);
virtual NamedBean*  getBeanByUserName(QString  userName);
virtual NamedBean*  getNamedBean(QString  name);
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList();
virtual QString  getSystemPrefix();
virtual int  getXMLOrder();
virtual QString  makeSystemName(QString  s);
virtual void on_propertyChange(PropertyChangeEvent*  e);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void timerEvent(QTimerEvent*  arg__1);
virtual char  typeLetter();

  PythonQtInstanceWrapper* _wrapper; 
};

class LIBLAYOUTEDITORSHARED_EXPORT PythonQtPublicPromoter_AbstractManager : public AbstractManager
{ public:
inline void promoted_Register(NamedBean*  s) { AbstractManager::Register(s); }
inline void promoted_addPropertyChangeListener(PropertyChangeListener*  l) { AbstractManager::addPropertyChangeListener(l); }
inline void promoted_deregister(NamedBean*  s) { AbstractManager::deregister(s); }
inline void promoted_dispose() { AbstractManager::dispose(); }
inline void promoted_firePropertyChange(QString  p, QVariant  old, QVariant  n) { AbstractManager::firePropertyChange(p, old, n); }
inline NamedBean*  promoted_getBeanBySystemName(QString  systemName) { return AbstractManager::getBeanBySystemName(systemName); }
inline NamedBean*  promoted_getBeanByUserName(QString  userName) { return AbstractManager::getBeanByUserName(userName); }
inline QObject*  promoted_getInstanceBySystemName(QString  systemName) { return AbstractManager::getInstanceBySystemName(systemName); }
inline QObject*  promoted_getInstanceByUserName(QString  userName) { return AbstractManager::getInstanceByUserName(userName); }
inline NamedBean*  promoted_getNamedBean(QString  name) { return AbstractManager::getNamedBean(name); }
inline QStringList  promoted_getSystemNameArray() { return AbstractManager::getSystemNameArray(); }
inline QStringList  promoted_getSystemNameList() { return AbstractManager::getSystemNameList(); }
inline QString  promoted_makeSystemName(QString  s) { return AbstractManager::makeSystemName(s); }
inline void promoted_on_propertyChange(PropertyChangeEvent*  e) { AbstractManager::on_propertyChange(e); }
inline void promoted_removePropertyChangeListener(PropertyChangeListener*  l) { AbstractManager::removePropertyChangeListener(l); }
};

class LIBLAYOUTEDITORSHARED_EXPORT PythonQtWrapper_AbstractManager : public QObject
{ Q_OBJECT
public:
public slots:
AbstractManager* new_AbstractManager(QObject*  parent = 0);
void delete_AbstractManager(AbstractManager* obj) { delete obj; } 
   void Register(AbstractManager* theWrappedObject, NamedBean*  s);
   void addPropertyChangeListener(AbstractManager* theWrappedObject, PropertyChangeListener*  l);
   void deregister(AbstractManager* theWrappedObject, NamedBean*  s);
   void dispose(AbstractManager* theWrappedObject);
   void firePropertyChange(AbstractManager* theWrappedObject, QString  p, QVariant  old, QVariant  n);
   NamedBean*  getBeanBySystemName(AbstractManager* theWrappedObject, QString  systemName);
   NamedBean*  getBeanByUserName(AbstractManager* theWrappedObject, QString  userName);
   QObject*  getInstanceBySystemName(AbstractManager* theWrappedObject, QString  systemName);
   QObject*  getInstanceByUserName(AbstractManager* theWrappedObject, QString  userName);
   NamedBean*  getNamedBean(AbstractManager* theWrappedObject, QString  name);
   QStringList  getSystemNameArray(AbstractManager* theWrappedObject);
   QHash<QString , NamedBean* >*  getSystemNameHash(AbstractManager* theWrappedObject);
   QStringList  getSystemNameList(AbstractManager* theWrappedObject);
   QStringList  getUserNameList(AbstractManager* theWrappedObject);
   QString  makeSystemName(AbstractManager* theWrappedObject, QString  s);
   void on_propertyChange(AbstractManager* theWrappedObject, PropertyChangeEvent*  e);
   void registerSelf(AbstractManager* theWrappedObject);
   void removePropertyChangeListener(AbstractManager* theWrappedObject, PropertyChangeListener*  l);
};





class LIBLAYOUTEDITORSHARED_EXPORT PythonQtShell_AbstractNamedBean : public AbstractNamedBean
{
public:
    PythonQtShell_AbstractNamedBean(QObject*  parent = 0):AbstractNamedBean(parent),_wrapper(NULL) {};
    PythonQtShell_AbstractNamedBean(QString  sys, QObject*  parent = 0):AbstractNamedBean(sys, parent),_wrapper(NULL) {};
    PythonQtShell_AbstractNamedBean(QString  sys, QString  user, QObject*  parent = 0):AbstractNamedBean(sys, user, parent),_wrapper(NULL) {};

   ~PythonQtShell_AbstractNamedBean();

virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(PropertyChangeListener*  l, QString  beanRef, const QString  listenerRef);
virtual void childEvent(QChildEvent*  arg__1);
virtual void customEvent(QEvent*  arg__1);
virtual void dispose();
virtual bool  event(QEvent*  arg__1);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual QString  getComment();
virtual QString  getDisplayName();
virtual QString  getListenerRef(PropertyChangeListener*  l);
virtual QList<QString >*  getListenerRefs();
virtual int  getNumPropertyChangeListeners();
virtual QVariant  getProperty(QString  key);
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners();
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners(QString  name);
virtual QList<QString >  getPropertyKeys();
virtual int  getState();
virtual QString  getSystemName() const;
virtual QString  getUserName();
virtual bool  hashCode();
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void setComment(QString  comment);
virtual void setProperty(QString  key, QVariant  value);
virtual void setState(int  arg__1);
virtual void setUserName(QString  s);
virtual void timerEvent(QTimerEvent*  arg__1);
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);

  PythonQtInstanceWrapper* _wrapper; 
};

class LIBLAYOUTEDITORSHARED_EXPORT PythonQtPublicPromoter_AbstractNamedBean : public AbstractNamedBean
{ public:
inline void promoted_addPropertyChangeListener(PropertyChangeListener*  l) { AbstractNamedBean::addPropertyChangeListener(l); }
inline void promoted_addPropertyChangeListener(PropertyChangeListener*  l, QString  beanRef, const QString  listenerRef) { AbstractNamedBean::addPropertyChangeListener(l, beanRef, listenerRef); }
inline void promoted_dispose() { AbstractNamedBean::dispose(); }
inline void promoted_firePropertyChange(QString  p, QVariant  old, QVariant  n) { AbstractNamedBean::firePropertyChange(p, old, n); }
inline QString  promoted_getComment() { return AbstractNamedBean::getComment(); }
inline QString  promoted_getDisplayName() { return AbstractNamedBean::getDisplayName(); }
inline QString  promoted_getListenerRef(PropertyChangeListener*  l) { return AbstractNamedBean::getListenerRef(l); }
inline QList<QString >*  promoted_getListenerRefs() { return AbstractNamedBean::getListenerRefs(); }
inline int  promoted_getNumPropertyChangeListeners() { return AbstractNamedBean::getNumPropertyChangeListeners(); }
inline QVariant  promoted_getProperty(QString  key) { return AbstractNamedBean::getProperty(key); }
inline QList<PropertyChangeListener* >*  promoted_getPropertyChangeListeners() { return AbstractNamedBean::getPropertyChangeListeners(); }
inline QList<PropertyChangeListener* >*  promoted_getPropertyChangeListeners(QString  name) { return AbstractNamedBean::getPropertyChangeListeners(name); }
inline QList<QString >  promoted_getPropertyKeys() { return AbstractNamedBean::getPropertyKeys(); }
inline QString  promoted_getSystemName() const { return AbstractNamedBean::getSystemName(); }
inline QString  promoted_getUserName() { return AbstractNamedBean::getUserName(); }
inline void promoted_removePropertyChangeListener(PropertyChangeListener*  l) { AbstractNamedBean::removePropertyChangeListener(l); }
inline void promoted_setComment(QString  comment) { AbstractNamedBean::setComment(comment); }
inline void promoted_setProperty(QString  key, QVariant  value) { AbstractNamedBean::setProperty(key, value); }
inline void promoted_setUserName(QString  s) { AbstractNamedBean::setUserName(s); }
inline void promoted_updateListenerRef(PropertyChangeListener*  l, QString  newName) { AbstractNamedBean::updateListenerRef(l, newName); }
};

class LIBLAYOUTEDITORSHARED_EXPORT PythonQtWrapper_AbstractNamedBean : public QObject
{ Q_OBJECT
public:
public slots:
AbstractNamedBean* new_AbstractNamedBean(QObject*  parent = 0);
AbstractNamedBean* new_AbstractNamedBean(QString  sys, QObject*  parent = 0);
AbstractNamedBean* new_AbstractNamedBean(QString  sys, QString  user, QObject*  parent = 0);
void delete_AbstractNamedBean(AbstractNamedBean* obj) { delete obj; } 
   void addPropertyChangeListener(AbstractNamedBean* theWrappedObject, PropertyChangeListener*  l);
   void addPropertyChangeListener(AbstractNamedBean* theWrappedObject, PropertyChangeListener*  l, QString  beanRef, const QString  listenerRef);
   void dispose(AbstractNamedBean* theWrappedObject);
   void firePropertyChange(AbstractNamedBean* theWrappedObject, QString  p, QVariant  old, QVariant  n);
   QString  getComment(AbstractNamedBean* theWrappedObject);
   QString  getDisplayName(AbstractNamedBean* theWrappedObject);
   QString  getListenerRef(AbstractNamedBean* theWrappedObject, PropertyChangeListener*  l);
   QList<QString >*  getListenerRefs(AbstractNamedBean* theWrappedObject);
   int  getNumPropertyChangeListeners(AbstractNamedBean* theWrappedObject);
   QVariant  getProperty(AbstractNamedBean* theWrappedObject, QString  key);
   QList<PropertyChangeListener* >*  getPropertyChangeListeners(AbstractNamedBean* theWrappedObject);
   QList<PropertyChangeListener* >*  getPropertyChangeListeners(AbstractNamedBean* theWrappedObject, QString  name);
   QList<QString >  getPropertyKeys(AbstractNamedBean* theWrappedObject);
   QString  getSystemName(AbstractNamedBean* theWrappedObject) const;
   QString  getUserName(AbstractNamedBean* theWrappedObject);
   void removePropertyChangeListener(AbstractNamedBean* theWrappedObject, PropertyChangeListener*  l);
   void setComment(AbstractNamedBean* theWrappedObject, QString  comment);
   void setProperty(AbstractNamedBean* theWrappedObject, QString  key, QVariant  value);
   void setUserName(AbstractNamedBean* theWrappedObject, QString  s);
   void updateListenerRef(AbstractNamedBean* theWrappedObject, PropertyChangeListener*  l, QString  newName);
void py_set_pcs(AbstractNamedBean* theWrappedObject, PropertyChangeSupport*  pcs){ theWrappedObject->pcs = pcs; }
PropertyChangeSupport*  py_get_pcs(AbstractNamedBean* theWrappedObject){ return theWrappedObject->pcs; }
};





class PythonQtShell_AbstractProxyManager : public AbstractProxyManager
{
public:
    PythonQtShell_AbstractProxyManager(QObject*  parent = 0):AbstractProxyManager(parent),_wrapper(NULL) {};

   ~PythonQtShell_AbstractProxyManager();

virtual void Register(NamedBean*  s);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void childEvent(QChildEvent*  arg__1);
virtual void customEvent(QEvent*  arg__1);
virtual void deregister(NamedBean*  s);
virtual void dispose();
virtual bool  event(QEvent*  arg__1);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual NamedBean*  getBeanBySystemName(QString  systemName);
virtual NamedBean*  getBeanByUserName(QString  userName);
virtual NamedBean*  getNamedBean(QString  name);
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList();
virtual QString  getSystemPrefix();
virtual int  getXMLOrder();
virtual NamedBean*  makeBean(int  arg__1, QString  systemName, QString  userName);
virtual AbstractManager*  makeInternalManager() const;
virtual QString  makeSystemName(QString  s);
virtual void on_propertyChange(PropertyChangeEvent*  e);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void timerEvent(QTimerEvent*  arg__1);
virtual char  typeLetter();

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_AbstractProxyManager : public AbstractProxyManager
{ public:
inline void promoted_Register(NamedBean*  s) { AbstractProxyManager::Register(s); }
inline void promoted_addPropertyChangeListener(PropertyChangeListener*  l) { AbstractProxyManager::addPropertyChangeListener(l); }
inline void promoted_deregister(NamedBean*  s) { AbstractProxyManager::deregister(s); }
inline void promoted_dispose() { AbstractProxyManager::dispose(); }
inline NamedBean*  promoted_getBeanBySystemName(QString  systemName) { return AbstractProxyManager::getBeanBySystemName(systemName); }
inline NamedBean*  promoted_getBeanByUserName(QString  userName) { return AbstractProxyManager::getBeanByUserName(userName); }
inline AbstractManager*  promoted_getMgr(int  index) { return AbstractProxyManager::getMgr(index); }
inline NamedBean*  promoted_getNamedBean(QString  name) { return AbstractProxyManager::getNamedBean(name); }
inline QStringList  promoted_getSystemNameArray() { return AbstractProxyManager::getSystemNameArray(); }
inline QStringList  promoted_getSystemNameList() { return AbstractProxyManager::getSystemNameList(); }
inline QString  promoted_getSystemPrefix() { return AbstractProxyManager::getSystemPrefix(); }
inline NamedBean*  promoted_makeBean(int  arg__1, QString  systemName, QString  userName) { return AbstractProxyManager::makeBean(arg__1, systemName, userName); }
inline AbstractManager*  promoted_makeInternalManager() const { return AbstractProxyManager::makeInternalManager(); }
inline QString  promoted_makeSystemName(QString  s) { return AbstractProxyManager::makeSystemName(s); }
inline int  promoted_match(QString  systemname) { return AbstractProxyManager::match(systemname); }
inline int  promoted_matchTentative(QString  systemname) { return AbstractProxyManager::matchTentative(systemname); }
inline int  promoted_nMgrs() { return AbstractProxyManager::nMgrs(); }
inline void promoted_on_propertyChange(PropertyChangeEvent*  e) { AbstractProxyManager::on_propertyChange(e); }
inline NamedBean*  promoted_provideNamedBean(QString  name) { return AbstractProxyManager::provideNamedBean(name); }
inline void promoted_removePropertyChangeListener(PropertyChangeListener*  l) { AbstractProxyManager::removePropertyChangeListener(l); }
inline char  promoted_typeLetter() { return AbstractProxyManager::typeLetter(); }
};

class PythonQtWrapper_AbstractProxyManager : public QObject
{ Q_OBJECT
public:
public slots:
AbstractProxyManager* new_AbstractProxyManager(QObject*  parent = 0);
void delete_AbstractProxyManager(AbstractProxyManager* obj) { delete obj; } 
   void Register(AbstractProxyManager* theWrappedObject, NamedBean*  s);
   void addManager(AbstractProxyManager* theWrappedObject, Manager*  m);
   void addPropertyChangeListener(AbstractProxyManager* theWrappedObject, PropertyChangeListener*  l);
   void deregister(AbstractProxyManager* theWrappedObject, NamedBean*  s);
   void dispose(AbstractProxyManager* theWrappedObject);
   NamedBean*  getBeanBySystemName(AbstractProxyManager* theWrappedObject, QString  systemName);
   NamedBean*  getBeanByUserName(AbstractProxyManager* theWrappedObject, QString  userName);
   QList<Manager* >  getManagerList(AbstractProxyManager* theWrappedObject);
   AbstractManager*  getMgr(AbstractProxyManager* theWrappedObject, int  index);
   NamedBean*  getNamedBean(AbstractProxyManager* theWrappedObject, QString  name);
   QStringList  getSystemNameArray(AbstractProxyManager* theWrappedObject);
   QStringList  getSystemNameList(AbstractProxyManager* theWrappedObject);
   QString  getSystemPrefix(AbstractProxyManager* theWrappedObject);
   QStringList  getUserNameList(AbstractProxyManager* theWrappedObject);
   NamedBean*  makeBean(AbstractProxyManager* theWrappedObject, int  arg__1, QString  systemName, QString  userName);
   AbstractManager*  makeInternalManager(AbstractProxyManager* theWrappedObject) const;
   QString  makeSystemName(AbstractProxyManager* theWrappedObject, QString  s);
   int  match(AbstractProxyManager* theWrappedObject, QString  systemname);
   int  matchTentative(AbstractProxyManager* theWrappedObject, QString  systemname);
   int  nMgrs(AbstractProxyManager* theWrappedObject);
   NamedBean*  newNamedBean(AbstractProxyManager* theWrappedObject, QString  systemName, QString  userName);
   void on_propertyChange(AbstractProxyManager* theWrappedObject, PropertyChangeEvent*  e);
   NamedBean*  provideNamedBean(AbstractProxyManager* theWrappedObject, QString  name);
   void removePropertyChangeListener(AbstractProxyManager* theWrappedObject, PropertyChangeListener*  l);
   char  typeLetter(AbstractProxyManager* theWrappedObject);
void py_set_mgrs(AbstractProxyManager* theWrappedObject, QList<AbstractManager* >*  mgrs){ theWrappedObject->mgrs = mgrs; }
QList<AbstractManager* >*  py_get_mgrs(AbstractProxyManager* theWrappedObject){ return theWrappedObject->mgrs; }
};





class PythonQtShell_AbstractSensor : public AbstractSensor
{
public:
    PythonQtShell_AbstractSensor(QObject*  parent = 0):AbstractSensor(parent),_wrapper(NULL) {};
    PythonQtShell_AbstractSensor(QString  systemName, QObject*  parent = 0):AbstractSensor(systemName, parent),_wrapper(NULL) {};
    PythonQtShell_AbstractSensor(QString  systemName, QString  userName, QObject*  parent = 0):AbstractSensor(systemName, userName, parent),_wrapper(NULL) {};

   ~PythonQtShell_AbstractSensor();

virtual void addPropertyChangeListener(PropertyChangeListener*  arg__1) const;
virtual void childEvent(QChildEvent*  arg__1);
virtual void customEvent(QEvent*  arg__1);
virtual void dispose() const;
virtual bool  event(QEvent*  arg__1);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual QString  getComment();
virtual QString  getDisplayName();
virtual bool  getInverted();
virtual int  getKnownState() const;
virtual QString  getListenerRef(PropertyChangeListener*  l);
virtual QList<QString >*  getListenerRefs();
virtual int  getNumPropertyChangeListeners();
virtual QVariant  getProperty(QString  key);
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners();
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners(QString  name);
virtual QList<QString >  getPropertyKeys();
virtual int  getRawState();
virtual long  getSensorDebounceGoingActiveTimer();
virtual long  getSensorDebounceGoingInActiveTimer();
virtual int  getState();
virtual QString  getSystemName() const;
virtual QString  getUserName();
virtual bool  hashCode();
virtual void removePropertyChangeListener(PropertyChangeListener*  arg__1) const;
virtual void requestUpdateFromLayout() const;
virtual void setComment(QString  comment);
virtual void setInverted(bool  inverted);
virtual void setKnownState(int  s);
virtual void setProperty(QString  key, QVariant  value);
virtual void setSensorDebounceGoingActiveTimer(long  time);
virtual void setSensorDebounceGoingInActiveTimer(long  time);
virtual void setState(int  s);
virtual void setUserName(QString  s);
virtual void timerEvent(QTimerEvent*  arg__1);
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);
virtual bool  useDefaultTimerSettings();
virtual void useDefaultTimerSettings(bool  boo);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_AbstractSensor : public AbstractSensor
{ public:
inline bool  promoted_getInverted() { return AbstractSensor::getInverted(); }
inline int  promoted_getKnownState() const { return AbstractSensor::getKnownState(); }
inline int  promoted_getRawState() { return AbstractSensor::getRawState(); }
inline long  promoted_getSensorDebounceGoingActiveTimer() { return AbstractSensor::getSensorDebounceGoingActiveTimer(); }
inline long  promoted_getSensorDebounceGoingInActiveTimer() { return AbstractSensor::getSensorDebounceGoingInActiveTimer(); }
inline int  promoted_getState() { return AbstractSensor::getState(); }
inline void promoted_sensorDebounce() { AbstractSensor::sensorDebounce(); }
inline void promoted_setInverted(bool  inverted) { AbstractSensor::setInverted(inverted); }
inline void promoted_setKnownState(int  s) { AbstractSensor::setKnownState(s); }
inline void promoted_setSensorDebounceGoingActiveTimer(long  time) { AbstractSensor::setSensorDebounceGoingActiveTimer(time); }
inline void promoted_setSensorDebounceGoingInActiveTimer(long  time) { AbstractSensor::setSensorDebounceGoingInActiveTimer(time); }
inline void promoted_setState(int  s) { AbstractSensor::setState(s); }
inline bool  promoted_useDefaultTimerSettings() { return AbstractSensor::useDefaultTimerSettings(); }
inline void promoted_useDefaultTimerSettings(bool  boo) { AbstractSensor::useDefaultTimerSettings(boo); }
};

class PythonQtWrapper_AbstractSensor : public QObject
{ Q_OBJECT
public:
public slots:
AbstractSensor* new_AbstractSensor(QObject*  parent = 0);
AbstractSensor* new_AbstractSensor(QString  systemName, QObject*  parent = 0);
AbstractSensor* new_AbstractSensor(QString  systemName, QString  userName, QObject*  parent = 0);
void delete_AbstractSensor(AbstractSensor* obj) { delete obj; } 
   bool  getInverted(AbstractSensor* theWrappedObject);
   int  getKnownState(AbstractSensor* theWrappedObject) const;
   int  getRawState(AbstractSensor* theWrappedObject);
   long  getSensorDebounceGoingActiveTimer(AbstractSensor* theWrappedObject);
   long  getSensorDebounceGoingInActiveTimer(AbstractSensor* theWrappedObject);
   int  getState(AbstractSensor* theWrappedObject);
   QString  getStateName(AbstractSensor* theWrappedObject, int  arg__1);
   void sensorDebounce(AbstractSensor* theWrappedObject);
   void setInverted(AbstractSensor* theWrappedObject, bool  inverted);
   void setKnownState(AbstractSensor* theWrappedObject, int  s);
   void setOwnState(AbstractSensor* theWrappedObject, int  s);
   void setSensorDebounceGoingActiveTimer(AbstractSensor* theWrappedObject, long  time);
   void setSensorDebounceGoingInActiveTimer(AbstractSensor* theWrappedObject, long  time);
   void setState(AbstractSensor* theWrappedObject, int  s);
   bool  useDefaultTimerSettings(AbstractSensor* theWrappedObject);
   void useDefaultTimerSettings(AbstractSensor* theWrappedObject, bool  boo);
};





class PythonQtShell_AbstractSensorManager : public AbstractSensorManager
{
public:
    PythonQtShell_AbstractSensorManager(QObject*  parent = 0):AbstractSensorManager(parent),_wrapper(NULL) {};

   ~PythonQtShell_AbstractSensorManager();

virtual void Register(NamedBean*  s);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual bool  allowMultipleAdditions(QString  systemName);
virtual void childEvent(QChildEvent*  arg__1);
virtual Sensor*  createNewSensor(QString  arg__1, QString  arg__2);
virtual QString  createSystemName(QString  curAddress, QString  prefix) throw (JmriException);
virtual void customEvent(QEvent*  arg__1);
virtual void deregister(NamedBean*  s);
virtual void dispose() const;
virtual bool  event(QEvent*  arg__1);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual NamedBean*  getBeanBySystemName(QString  systemName);
virtual NamedBean*  getBeanByUserName(QString  userName);
virtual long  getDefaultSensorDebounceGoingActive();
virtual long  getDefaultSensorDebounceGoingInActive();
virtual NamedBean*  getNamedBean(QString  name);
virtual QString  getNextValidAddress(QString  curAddress, QString  prefix);
virtual Sensor*  getSensor(QString  name);
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList();
virtual QString  getSystemPrefix();
virtual int  getXMLOrder();
virtual QString  makeSystemName(QString  s);
virtual Sensor*  newSensor(QString  sysName, QString  userName);
virtual void on_propertyChange(PropertyChangeEvent*  e);
virtual Sensor*  provideSensor(QString  name);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void setDefaultSensorDebounceGoingActive(long  timer);
virtual void setDefaultSensorDebounceGoingInActive(long  timer);
virtual void timerEvent(QTimerEvent*  arg__1);
virtual char  typeLetter();
virtual void updateAll();

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_AbstractSensorManager : public AbstractSensorManager
{ public:
inline bool  promoted_allowMultipleAdditions(QString  systemName) { return AbstractSensorManager::allowMultipleAdditions(systemName); }
inline Sensor*  promoted_createNewSensor(QString  arg__1, QString  arg__2) { return AbstractSensorManager::createNewSensor(arg__1, arg__2); }
inline QString  promoted_createSystemName(QString  curAddress, QString  prefix) throw (JmriException) { return AbstractSensorManager::createSystemName(curAddress, prefix); }
inline long  promoted_getDefaultSensorDebounceGoingActive() { return AbstractSensorManager::getDefaultSensorDebounceGoingActive(); }
inline long  promoted_getDefaultSensorDebounceGoingInActive() { return AbstractSensorManager::getDefaultSensorDebounceGoingInActive(); }
inline QObject*  promoted_getInstanceBySystemName(QString  systemName) { return AbstractSensorManager::getInstanceBySystemName(systemName); }
inline QString  promoted_getNextValidAddress(QString  curAddress, QString  prefix) { return AbstractSensorManager::getNextValidAddress(curAddress, prefix); }
inline Sensor*  promoted_getSensor(QString  name) { return AbstractSensorManager::getSensor(name); }
inline int  promoted_getXMLOrder() { return AbstractSensorManager::getXMLOrder(); }
inline Sensor*  promoted_newSensor(QString  sysName, QString  userName) { return AbstractSensorManager::newSensor(sysName, userName); }
inline QString  promoted_normalizeSystemName(QString  sysName) { return AbstractSensorManager::normalizeSystemName(sysName); }
inline Sensor*  promoted_provideSensor(QString  name) { return AbstractSensorManager::provideSensor(name); }
inline void promoted_setDefaultSensorDebounceGoingActive(long  timer) { AbstractSensorManager::setDefaultSensorDebounceGoingActive(timer); }
inline void promoted_setDefaultSensorDebounceGoingInActive(long  timer) { AbstractSensorManager::setDefaultSensorDebounceGoingInActive(timer); }
inline char  promoted_typeLetter() { return AbstractSensorManager::typeLetter(); }
inline void promoted_updateAll() { AbstractSensorManager::updateAll(); }
};

class PythonQtWrapper_AbstractSensorManager : public QObject
{ Q_OBJECT
public:
public slots:
AbstractSensorManager* new_AbstractSensorManager(QObject*  parent = 0);
void delete_AbstractSensorManager(AbstractSensorManager* obj) { delete obj; } 
   bool  allowMultipleAdditions(AbstractSensorManager* theWrappedObject, QString  systemName);
   Sensor*  createNewSensor(AbstractSensorManager* theWrappedObject, QString  arg__1, QString  arg__2);
   QString  createSystemName(AbstractSensorManager* theWrappedObject, QString  curAddress, QString  prefix) throw (JmriException);
   Sensor*  getBySystemName(AbstractSensorManager* theWrappedObject, QString  key);
   Sensor*  getByUserName(AbstractSensorManager* theWrappedObject, QString  key);
   long  getDefaultSensorDebounceGoingActive(AbstractSensorManager* theWrappedObject);
   long  getDefaultSensorDebounceGoingInActive(AbstractSensorManager* theWrappedObject);
   QObject*  getInstanceBySystemName(AbstractSensorManager* theWrappedObject, QString  systemName);
   QString  getNextValidAddress(AbstractSensorManager* theWrappedObject, QString  curAddress, QString  prefix);
   Sensor*  getSensor(AbstractSensorManager* theWrappedObject, QString  name);
   int  getXMLOrder(AbstractSensorManager* theWrappedObject);
   Sensor*  newSensor(AbstractSensorManager* theWrappedObject, QString  sysName, QString  userName);
   QString  normalizeSystemName(AbstractSensorManager* theWrappedObject, QString  sysName);
   Sensor*  provideSensor(AbstractSensorManager* theWrappedObject, QString  name);
   void setDefaultSensorDebounceGoingActive(AbstractSensorManager* theWrappedObject, long  timer);
   void setDefaultSensorDebounceGoingInActive(AbstractSensorManager* theWrappedObject, long  timer);
   char  typeLetter(AbstractSensorManager* theWrappedObject);
   void updateAll(AbstractSensorManager* theWrappedObject);
};





class PythonQtPublicPromoter_AbstractSerialPortController : public AbstractSerialPortController
{ public:
inline void promoted_closeConnection() throw( Exception) { AbstractSerialPortController::closeConnection(); }
inline void promoted_resetupConnection() { AbstractSerialPortController::resetupConnection(); }
inline QVector<int >  promoted_validBaudNumber() { return AbstractSerialPortController::validBaudNumber(); }
inline QStringList  promoted_validBaudRates() { return AbstractSerialPortController::validBaudRates(); }
};

class PythonQtWrapper_AbstractSerialPortController : public QObject
{ Q_OBJECT
public:
public slots:
void delete_AbstractSerialPortController(AbstractSerialPortController* obj) { delete obj; } 
   void _connect(AbstractSerialPortController* theWrappedObject) throw( Exception);
   void closeConnection(AbstractSerialPortController* theWrappedObject) throw( Exception);
   void configureBaudRate(AbstractSerialPortController* theWrappedObject, QString  rate);
   int  currentBaudNumber(AbstractSerialPortController* theWrappedObject, QString  currentBaudRate);
   void dispose(AbstractSerialPortController* theWrappedObject);
   QString  getCurrentBaudRate(AbstractSerialPortController* theWrappedObject);
   QString  getCurrentPortName(AbstractSerialPortController* theWrappedObject);
   QString  getOptionState(AbstractSerialPortController* theWrappedObject, QString  option);
   QVector<QString >  getPortNames(AbstractSerialPortController* theWrappedObject);
   void reconnect(AbstractSerialPortController* theWrappedObject);
   void recover(AbstractSerialPortController* theWrappedObject);
   void resetupConnection(AbstractSerialPortController* theWrappedObject);
   void setDisabled(AbstractSerialPortController* theWrappedObject, bool  disabled);
   void setPort(AbstractSerialPortController* theWrappedObject, QString  port);
   QVector<int >  validBaudNumber(AbstractSerialPortController* theWrappedObject);
   QStringList  validBaudRates(AbstractSerialPortController* theWrappedObject);
};





class PythonQtShell_AbstractTurnout : public AbstractTurnout
{
public:
    PythonQtShell_AbstractTurnout(QObject*  parent = 0):AbstractTurnout(parent),_wrapper(NULL) {};
    PythonQtShell_AbstractTurnout(QString  systemName, QObject*  parent = 0):AbstractTurnout(systemName, parent),_wrapper(NULL) {};
    PythonQtShell_AbstractTurnout(QString  systemName, QString  userName, QObject*  parent = 0):AbstractTurnout(systemName, userName, parent),_wrapper(NULL) {};

   ~PythonQtShell_AbstractTurnout();

virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(PropertyChangeListener*  l, QString  beanRef, const QString  listenerRef);
virtual bool  canInvert();
virtual bool  canLock(int  turnoutLockout);
virtual void childEvent(QChildEvent*  arg__1);
virtual void customEvent(QEvent*  arg__1);
virtual void dispose();
virtual void enableLockOperation(int  turnoutLockout, bool  enabled);
virtual bool  event(QEvent*  arg__1);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual void forwardCommandChangeToLayout();
virtual void forwardCommandChangeToLayout(int  s);
virtual int  getCommandedState();
virtual QString  getComment();
virtual int  getControlType();
virtual QString  getDecoderName();
virtual QString  getDisplayName();
virtual float  getDivergingLimit();
virtual QString  getDivergingSpeed();
virtual int  getFeedbackMode();
virtual QString  getFeedbackModeName();
virtual Sensor*  getFirstSensor();
virtual bool  getInhibitOperation();
virtual bool  getInverted();
virtual int  getKnownState();
virtual QString  getListenerRef(PropertyChangeListener*  l);
virtual QList<QString >*  getListenerRefs();
virtual bool  getLocked(int  turnoutLockout);
virtual int  getNumPropertyChangeListeners();
virtual int  getNumberOutputBits();
virtual QVariant  getProperty(QString  key);
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners();
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners(QString  name);
virtual QList<QString >  getPropertyKeys();
virtual bool  getReportLocked();
virtual Sensor*  getSecondSensor();
virtual int  getState();
virtual float  getStraightLimit();
virtual QString  getStraightSpeed();
virtual QString  getSystemName() const;
virtual QString  getUserName();
virtual QStringList  getValidDecoderNames();
virtual QStringList  getValidFeedbackNames();
virtual int  getValidFeedbackTypes();
virtual bool  hashCode();
virtual bool  isConsistentState();
virtual void provideFirstFeedbackSensor(QString  pName) throw(JmriException);
virtual void provideSecondFeedbackSensor(QString  pName) throw(JmriException);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void setBinaryOutput(bool  state);
virtual void setCommandedState(int  s);
virtual void setComment(QString  comment);
virtual void setControlType(int  num);
virtual void setDecoderName(QString  decoderName);
virtual void setDivergingSpeed(QString  s) throw(JmriException);
virtual void setFeedbackMode(QString  mode) throw(IllegalArgumentException);
virtual void setFeedbackMode(int  mode) throw(IllegalArgumentException);
virtual void setInhibitOperation(bool  io);
virtual void setInitialKnownStateFromFeedback();
virtual void setInverted(bool  inverted);
virtual void setLocked(int  turnoutLockout, bool  locked);
virtual void setNumberOutputBits(int  num);
virtual void setProperty(QString  key, QVariant  value);
virtual void setReportLocked(bool  reportLocked);
virtual void setState(int  s);
virtual void setStraightSpeed(QString  s) throw(JmriException);
virtual void setUserName(QString  s);
virtual void timerEvent(QTimerEvent*  arg__1);
virtual void turnoutPushbuttonLockout(bool  locked);
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_AbstractTurnout : public AbstractTurnout
{ public:
inline bool  promoted_canInvert() { return AbstractTurnout::canInvert(); }
inline bool  promoted_canLock(int  turnoutLockout) { return AbstractTurnout::canLock(turnoutLockout); }
inline void promoted_dispose() { AbstractTurnout::dispose(); }
inline void promoted_enableLockOperation(int  turnoutLockout, bool  enabled) { AbstractTurnout::enableLockOperation(turnoutLockout, enabled); }
inline void promoted_forwardCommandChangeToLayout() { AbstractTurnout::forwardCommandChangeToLayout(); }
inline void promoted_forwardCommandChangeToLayout(int  s) { AbstractTurnout::forwardCommandChangeToLayout(s); }
inline int  promoted_getCommandedState() { return AbstractTurnout::getCommandedState(); }
inline int  promoted_getControlType() { return AbstractTurnout::getControlType(); }
inline QString  promoted_getDecoderName() { return AbstractTurnout::getDecoderName(); }
inline float  promoted_getDivergingLimit() { return AbstractTurnout::getDivergingLimit(); }
inline QString  promoted_getDivergingSpeed() { return AbstractTurnout::getDivergingSpeed(); }
inline int  promoted_getFeedbackMode() { return AbstractTurnout::getFeedbackMode(); }
inline int  promoted_getFeedbackModeForOperation() { return AbstractTurnout::getFeedbackModeForOperation(); }
inline QString  promoted_getFeedbackModeName() { return AbstractTurnout::getFeedbackModeName(); }
inline Sensor*  promoted_getFirstSensor() { return AbstractTurnout::getFirstSensor(); }
inline bool  promoted_getInhibitOperation() { return AbstractTurnout::getInhibitOperation(); }
inline bool  promoted_getInverted() { return AbstractTurnout::getInverted(); }
inline int  promoted_getKnownState() { return AbstractTurnout::getKnownState(); }
inline bool  promoted_getLocked(int  turnoutLockout) { return AbstractTurnout::getLocked(turnoutLockout); }
inline int  promoted_getNumberOutputBits() { return AbstractTurnout::getNumberOutputBits(); }
inline bool  promoted_getReportLocked() { return AbstractTurnout::getReportLocked(); }
inline Sensor*  promoted_getSecondSensor() { return AbstractTurnout::getSecondSensor(); }
inline int  promoted_getState() { return AbstractTurnout::getState(); }
inline float  promoted_getStraightLimit() { return AbstractTurnout::getStraightLimit(); }
inline QString  promoted_getStraightSpeed() { return AbstractTurnout::getStraightSpeed(); }
inline QStringList  promoted_getValidDecoderNames() { return AbstractTurnout::getValidDecoderNames(); }
inline QStringList  promoted_getValidFeedbackNames() { return AbstractTurnout::getValidFeedbackNames(); }
inline int  promoted_getValidFeedbackTypes() { return AbstractTurnout::getValidFeedbackTypes(); }
inline bool  promoted_isConsistentState() { return AbstractTurnout::isConsistentState(); }
inline void promoted_newCommandedState(int  s) { AbstractTurnout::newCommandedState(s); }
inline void promoted_newKnownState(int  s) { AbstractTurnout::newKnownState(s); }
inline void promoted_operationPropertyChange(PropertyChangeEvent*  evt) { AbstractTurnout::operationPropertyChange(evt); }
inline void promoted_provideFirstFeedbackSensor(QString  pName) throw(JmriException) { AbstractTurnout::provideFirstFeedbackSensor(pName); }
inline void promoted_provideSecondFeedbackSensor(QString  pName) throw(JmriException) { AbstractTurnout::provideSecondFeedbackSensor(pName); }
inline void promoted_sensorPropertyChange(PropertyChangeEvent*  evt) { AbstractTurnout::sensorPropertyChange(evt); }
inline void promoted_setBinaryOutput(bool  state) { AbstractTurnout::setBinaryOutput(state); }
inline void promoted_setCommandedState(int  s) { AbstractTurnout::setCommandedState(s); }
inline void promoted_setControlType(int  num) { AbstractTurnout::setControlType(num); }
inline void promoted_setDecoderName(QString  decoderName) { AbstractTurnout::setDecoderName(decoderName); }
inline void promoted_setDivergingSpeed(QString  s) throw(JmriException) { AbstractTurnout::setDivergingSpeed(s); }
inline void promoted_setFeedbackMode(QString  mode) throw(IllegalArgumentException) { AbstractTurnout::setFeedbackMode(mode); }
inline void promoted_setFeedbackMode(int  mode) throw(IllegalArgumentException) { AbstractTurnout::setFeedbackMode(mode); }
inline void promoted_setInhibitOperation(bool  io) { AbstractTurnout::setInhibitOperation(io); }
inline void promoted_setInitialKnownStateFromFeedback() { AbstractTurnout::setInitialKnownStateFromFeedback(); }
inline void promoted_setInverted(bool  inverted) { AbstractTurnout::setInverted(inverted); }
inline void promoted_setLocked(int  turnoutLockout, bool  locked) { AbstractTurnout::setLocked(turnoutLockout, locked); }
inline void promoted_setNumberOutputBits(int  num) { AbstractTurnout::setNumberOutputBits(num); }
inline void promoted_setReportLocked(bool  reportLocked) { AbstractTurnout::setReportLocked(reportLocked); }
inline void promoted_setState(int  s) { AbstractTurnout::setState(s); }
inline void promoted_setStraightSpeed(QString  s) throw(JmriException) { AbstractTurnout::setStraightSpeed(s); }
inline void promoted_turnoutPushbuttonLockout() { AbstractTurnout::turnoutPushbuttonLockout(); }
inline void promoted_turnoutPushbuttonLockout(bool  locked) { AbstractTurnout::turnoutPushbuttonLockout(locked); }
};

class PythonQtWrapper_AbstractTurnout : public QObject
{ Q_OBJECT
public:
public slots:
AbstractTurnout* new_AbstractTurnout(QObject*  parent = 0);
AbstractTurnout* new_AbstractTurnout(QString  systemName, QObject*  parent = 0);
AbstractTurnout* new_AbstractTurnout(QString  systemName, QString  userName, QObject*  parent = 0);
void delete_AbstractTurnout(AbstractTurnout* obj) { delete obj; } 
   bool  canInvert(AbstractTurnout* theWrappedObject);
   bool  canLock(AbstractTurnout* theWrappedObject, int  turnoutLockout);
   void dispose(AbstractTurnout* theWrappedObject);
   void enableLockOperation(AbstractTurnout* theWrappedObject, int  turnoutLockout, bool  enabled);
   void forwardCommandChangeToLayout(AbstractTurnout* theWrappedObject);
   void forwardCommandChangeToLayout(AbstractTurnout* theWrappedObject, int  s);
   int  getCommandedState(AbstractTurnout* theWrappedObject);
   int  getControlType(AbstractTurnout* theWrappedObject);
   QString  getDecoderName(AbstractTurnout* theWrappedObject);
   float  getDivergingLimit(AbstractTurnout* theWrappedObject);
   QString  getDivergingSpeed(AbstractTurnout* theWrappedObject);
   int  getFeedbackMode(AbstractTurnout* theWrappedObject);
   int  getFeedbackModeForOperation(AbstractTurnout* theWrappedObject);
   QString  getFeedbackModeName(AbstractTurnout* theWrappedObject);
   Sensor*  getFirstSensor(AbstractTurnout* theWrappedObject);
   bool  getInhibitOperation(AbstractTurnout* theWrappedObject);
   bool  getInverted(AbstractTurnout* theWrappedObject);
   int  getKnownState(AbstractTurnout* theWrappedObject);
   bool  getLocked(AbstractTurnout* theWrappedObject, int  turnoutLockout);
   int  getNumberOutputBits(AbstractTurnout* theWrappedObject);
   bool  getReportLocked(AbstractTurnout* theWrappedObject);
   Sensor*  getSecondSensor(AbstractTurnout* theWrappedObject);
   int  getState(AbstractTurnout* theWrappedObject);
   float  getStraightLimit(AbstractTurnout* theWrappedObject);
   QString  getStraightSpeed(AbstractTurnout* theWrappedObject);
   QStringList  getValidDecoderNames(AbstractTurnout* theWrappedObject);
   QStringList  getValidFeedbackNames(AbstractTurnout* theWrappedObject);
   int  getValidFeedbackTypes(AbstractTurnout* theWrappedObject);
   bool  isConsistentState(AbstractTurnout* theWrappedObject);
   void newCommandedState(AbstractTurnout* theWrappedObject, int  s);
   void newKnownState(AbstractTurnout* theWrappedObject, int  s);
   void operationPropertyChange(AbstractTurnout* theWrappedObject, PropertyChangeEvent*  evt);
   void provideFirstFeedbackSensor(AbstractTurnout* theWrappedObject, QString  pName) throw(JmriException);
   void provideSecondFeedbackSensor(AbstractTurnout* theWrappedObject, QString  pName) throw(JmriException);
   void sensorPropertyChange(AbstractTurnout* theWrappedObject, PropertyChangeEvent*  evt);
   void setBinaryOutput(AbstractTurnout* theWrappedObject, bool  state);
   void setCommandedState(AbstractTurnout* theWrappedObject, int  s);
   void setControlType(AbstractTurnout* theWrappedObject, int  num);
   void setDecoderName(AbstractTurnout* theWrappedObject, QString  decoderName);
   void setDivergingSpeed(AbstractTurnout* theWrappedObject, QString  s) throw(JmriException);
   void setFeedbackMode(AbstractTurnout* theWrappedObject, QString  mode) throw(IllegalArgumentException);
   void setFeedbackMode(AbstractTurnout* theWrappedObject, int  mode) throw(IllegalArgumentException);
   void setInhibitOperation(AbstractTurnout* theWrappedObject, bool  io);
   void setInitialKnownStateFromFeedback(AbstractTurnout* theWrappedObject);
   void setInverted(AbstractTurnout* theWrappedObject, bool  inverted);
   void setKnownStateToCommanded(AbstractTurnout* theWrappedObject);
   void setLocked(AbstractTurnout* theWrappedObject, int  turnoutLockout, bool  locked);
   void setNumberOutputBits(AbstractTurnout* theWrappedObject, int  num);
   void setReportLocked(AbstractTurnout* theWrappedObject, bool  reportLocked);
   void setState(AbstractTurnout* theWrappedObject, int  s);
   void setStraightSpeed(AbstractTurnout* theWrappedObject, QString  s) throw(JmriException);
   void turnoutPushbuttonLockout(AbstractTurnout* theWrappedObject);
   void turnoutPushbuttonLockout(AbstractTurnout* theWrappedObject, bool  locked);
};





class PythonQtShell_Audio : public Audio
{
public:
    PythonQtShell_Audio(QString  systemName, QObject*  parent = 0):Audio(systemName, parent),_wrapper(NULL) {};
    PythonQtShell_Audio(QString  systemName, QString  userName, QObject*  parent = 0):Audio(systemName, userName, parent),_wrapper(NULL) {};

   ~PythonQtShell_Audio();

virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(PropertyChangeListener*  l, QString  beanRef, const QString  listenerRef);
virtual void childEvent(QChildEvent*  arg__1);
virtual void customEvent(QEvent*  arg__1);
virtual void dispose();
virtual bool  event(QEvent*  arg__1);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual QString  getComment();
virtual QString  getDisplayName();
virtual QString  getListenerRef(PropertyChangeListener*  l);
virtual QList<QString >*  getListenerRefs();
virtual int  getNumPropertyChangeListeners();
virtual QVariant  getProperty(QString  key);
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners();
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners(QString  name);
virtual QList<QString >  getPropertyKeys();
virtual int  getState();
virtual QChar  getSubType();
virtual QString  getSystemName() const;
virtual QString  getUserName();
virtual bool  hashCode();
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void setComment(QString  comment);
virtual void setProperty(QString  key, QVariant  value);
virtual void setState(int  arg__1);
virtual void setUserName(QString  s);
virtual void stateChanged(int  arg__1);
virtual void timerEvent(QTimerEvent*  arg__1);
virtual QString  toString();
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_Audio : public Audio
{ public:
inline QChar  promoted_getSubType() { return Audio::getSubType(); }
inline void promoted_stateChanged(int  arg__1) { Audio::stateChanged(arg__1); }
inline QString  promoted_toString() { return Audio::toString(); }
};

class PythonQtWrapper_Audio : public QObject
{ Q_OBJECT
public:
public slots:
Audio* new_Audio(QString  systemName, QObject*  parent = 0);
Audio* new_Audio(QString  systemName, QString  userName, QObject*  parent = 0);
void delete_Audio(Audio* obj) { delete obj; } 
   QChar  getSubType(Audio* theWrappedObject);
   void stateChanged(Audio* theWrappedObject, int  arg__1);
   QString  toString(Audio* theWrappedObject);
    QString py_toString(Audio*);
};





class PythonQtShell_AudioBuffer : public AudioBuffer
{
public:
    PythonQtShell_AudioBuffer(QString  systemName, QObject*  parent = 0):AudioBuffer(systemName, parent),_wrapper(NULL) {};
    PythonQtShell_AudioBuffer(QString  systemName, QString  userName, QObject*  parent = 0):AudioBuffer(systemName, userName, parent),_wrapper(NULL) {};

   ~PythonQtShell_AudioBuffer();

virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(PropertyChangeListener*  l, QString  beanRef, const QString  listenerRef);
virtual void childEvent(QChildEvent*  arg__1);
virtual void customEvent(QEvent*  arg__1);
virtual void dispose();
virtual bool  event(QEvent*  arg__1);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual QString  getComment();
virtual QString  getDisplayName();
virtual long  getEndLoopPoint();
virtual int  getFormat();
virtual int  getFrameSize();
virtual int  getFrequency();
virtual long  getLength();
virtual QString  getListenerRef(PropertyChangeListener*  l);
virtual QList<QString >*  getListenerRefs();
virtual int  getNumPropertyChangeListeners();
virtual QVariant  getProperty(QString  key);
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners();
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners(QString  name);
virtual QList<QString >  getPropertyKeys();
virtual long  getStartLoopPoint();
virtual int  getState();
virtual QChar  getSubType();
virtual QString  getSystemName() const;
virtual QString  getURL();
virtual QString  getUserName();
virtual bool  hashCode();
virtual bool  isStreamed();
virtual bool  isStreamedForced();
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void setComment(QString  comment);
virtual void setEndLoopPoint(long  arg__1);
virtual void setInputStream(QDataStream*  arg__1);
virtual void setProperty(QString  key, QVariant  value);
virtual void setStartLoopPoint(long  arg__1);
virtual void setState(int  arg__1);
virtual void setStreamed(bool  arg__1);
virtual void setURL(QString  arg__1);
virtual void setUserName(QString  s);
virtual void stateChanged(int  arg__1);
virtual void timerEvent(QTimerEvent*  arg__1);
virtual QString  toString();
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_AudioBuffer : public AudioBuffer
{ public:
inline long  promoted_getEndLoopPoint() { return AudioBuffer::getEndLoopPoint(); }
inline int  promoted_getFormat() { return AudioBuffer::getFormat(); }
inline int  promoted_getFrameSize() { return AudioBuffer::getFrameSize(); }
inline int  promoted_getFrequency() { return AudioBuffer::getFrequency(); }
inline long  promoted_getLength() { return AudioBuffer::getLength(); }
inline long  promoted_getStartLoopPoint() { return AudioBuffer::getStartLoopPoint(); }
inline QString  promoted_getURL() { return AudioBuffer::getURL(); }
inline bool  promoted_isStreamed() { return AudioBuffer::isStreamed(); }
inline bool  promoted_isStreamedForced() { return AudioBuffer::isStreamedForced(); }
inline void promoted_setEndLoopPoint(long  arg__1) { AudioBuffer::setEndLoopPoint(arg__1); }
inline void promoted_setInputStream(QDataStream*  arg__1) { AudioBuffer::setInputStream(arg__1); }
inline void promoted_setStartLoopPoint(long  arg__1) { AudioBuffer::setStartLoopPoint(arg__1); }
inline void promoted_setStreamed(bool  arg__1) { AudioBuffer::setStreamed(arg__1); }
inline void promoted_setURL(QString  arg__1) { AudioBuffer::setURL(arg__1); }
};

class PythonQtWrapper_AudioBuffer : public QObject
{ Q_OBJECT
public:
public slots:
AudioBuffer* new_AudioBuffer(QString  systemName, QObject*  parent = 0);
AudioBuffer* new_AudioBuffer(QString  systemName, QString  userName, QObject*  parent = 0);
void delete_AudioBuffer(AudioBuffer* obj) { delete obj; } 
   long  getEndLoopPoint(AudioBuffer* theWrappedObject);
   int  getFormat(AudioBuffer* theWrappedObject);
   int  getFrameSize(AudioBuffer* theWrappedObject);
   int  getFrequency(AudioBuffer* theWrappedObject);
   long  getLength(AudioBuffer* theWrappedObject);
   long  getStartLoopPoint(AudioBuffer* theWrappedObject);
   QString  getURL(AudioBuffer* theWrappedObject);
   bool  isStreamed(AudioBuffer* theWrappedObject);
   bool  isStreamedForced(AudioBuffer* theWrappedObject);
   void setEndLoopPoint(AudioBuffer* theWrappedObject, long  arg__1);
   void setInputStream(AudioBuffer* theWrappedObject, QDataStream*  arg__1);
   void setStartLoopPoint(AudioBuffer* theWrappedObject, long  arg__1);
   void setStreamed(AudioBuffer* theWrappedObject, bool  arg__1);
   void setURL(AudioBuffer* theWrappedObject, QString  arg__1);
    QString py_toString(AudioBuffer*);
};





class PythonQtShell_AudioListener : public AudioListener
{
public:
    PythonQtShell_AudioListener(QObject*  parent = 0):AudioListener(parent),_wrapper(NULL) {};
    PythonQtShell_AudioListener(QString  systemName, QObject*  parent = 0):AudioListener(systemName, parent),_wrapper(NULL) {};
    PythonQtShell_AudioListener(QString  systemName, QString  userName, QObject*  parent = 0):AudioListener(systemName, userName, parent),_wrapper(NULL) {};

   ~PythonQtShell_AudioListener();

virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(PropertyChangeListener*  l, QString  beanRef, const QString  listenerRef);
virtual void childEvent(QChildEvent*  arg__1);
virtual void customEvent(QEvent*  arg__1);
virtual void dispose();
virtual bool  event(QEvent*  arg__1);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual QString  getComment();
virtual QVector3D  getCurrentOrientation(int  arg__1);
virtual QVector3D  getCurrentPosition();
virtual QString  getDisplayName();
virtual float  getGain();
virtual QString  getListenerRef(PropertyChangeListener*  l);
virtual QList<QString >*  getListenerRefs();
virtual float  getMetersPerUnit();
virtual int  getNumPropertyChangeListeners();
virtual QVector3D  getOrientation(int  arg__1);
virtual QVector3D  getPosition();
virtual QVariant  getProperty(QString  key);
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners();
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners(QString  name);
virtual QList<QString >  getPropertyKeys();
virtual int  getState();
virtual QChar  getSubType();
virtual QString  getSystemName() const;
virtual QString  getUserName();
virtual QVector3D  getVelocity();
virtual bool  hashCode();
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void resetCurrentPosition();
virtual void setComment(QString  comment);
virtual void setGain(float  arg__1);
virtual void setMetersPerUnit(float  arg__1);
virtual void setOrientation(QVector3D  arg__1, QVector3D  arg__2);
virtual void setPosition(QVector3D  arg__1);
virtual void setPosition(float  arg__1, float  arg__2);
virtual void setPosition(float  arg__1, float  arg__2, float  arg__3);
virtual void setProperty(QString  key, QVariant  value);
virtual void setState(int  arg__1);
virtual void setUserName(QString  s);
virtual void setVelocity(QVector3D  arg__1);
virtual void stateChanged(int  arg__1);
virtual void timerEvent(QTimerEvent*  arg__1);
virtual QString  toString();
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_AudioListener : public AudioListener
{ public:
inline QVector3D  promoted_getCurrentOrientation(int  arg__1) { return AudioListener::getCurrentOrientation(arg__1); }
inline QVector3D  promoted_getCurrentPosition() { return AudioListener::getCurrentPosition(); }
inline float  promoted_getGain() { return AudioListener::getGain(); }
inline float  promoted_getMetersPerUnit() { return AudioListener::getMetersPerUnit(); }
inline QVector3D  promoted_getOrientation(int  arg__1) { return AudioListener::getOrientation(arg__1); }
inline QVector3D  promoted_getPosition() { return AudioListener::getPosition(); }
inline QVector3D  promoted_getVelocity() { return AudioListener::getVelocity(); }
inline void promoted_resetCurrentPosition() { AudioListener::resetCurrentPosition(); }
inline void promoted_setGain(float  arg__1) { AudioListener::setGain(arg__1); }
inline void promoted_setMetersPerUnit(float  arg__1) { AudioListener::setMetersPerUnit(arg__1); }
inline void promoted_setOrientation(QVector3D  arg__1, QVector3D  arg__2) { AudioListener::setOrientation(arg__1, arg__2); }
inline void promoted_setPosition(QVector3D  arg__1) { AudioListener::setPosition(arg__1); }
inline void promoted_setPosition(float  arg__1, float  arg__2) { AudioListener::setPosition(arg__1, arg__2); }
inline void promoted_setPosition(float  arg__1, float  arg__2, float  arg__3) { AudioListener::setPosition(arg__1, arg__2, arg__3); }
inline void promoted_setVelocity(QVector3D  arg__1) { AudioListener::setVelocity(arg__1); }
};

class PythonQtWrapper_AudioListener : public QObject
{ Q_OBJECT
public:
public slots:
AudioListener* new_AudioListener(QObject*  parent = 0);
AudioListener* new_AudioListener(QString  systemName, QObject*  parent = 0);
AudioListener* new_AudioListener(QString  systemName, QString  userName, QObject*  parent = 0);
void delete_AudioListener(AudioListener* obj) { delete obj; } 
   QVector3D  getCurrentOrientation(AudioListener* theWrappedObject, int  arg__1);
   QVector3D  getCurrentPosition(AudioListener* theWrappedObject);
   float  getGain(AudioListener* theWrappedObject);
   float  getMetersPerUnit(AudioListener* theWrappedObject);
   QVector3D  getOrientation(AudioListener* theWrappedObject, int  arg__1);
   QVector3D  getPosition(AudioListener* theWrappedObject);
   QVector3D  getVelocity(AudioListener* theWrappedObject);
   void resetCurrentPosition(AudioListener* theWrappedObject);
   void setGain(AudioListener* theWrappedObject, float  arg__1);
   void setMetersPerUnit(AudioListener* theWrappedObject, float  arg__1);
   void setOrientation(AudioListener* theWrappedObject, QVector3D  arg__1, QVector3D  arg__2);
   void setPosition(AudioListener* theWrappedObject, QVector3D  arg__1);
   void setPosition(AudioListener* theWrappedObject, float  arg__1, float  arg__2);
   void setPosition(AudioListener* theWrappedObject, float  arg__1, float  arg__2, float  arg__3);
   void setVelocity(AudioListener* theWrappedObject, QVector3D  arg__1);
    QString py_toString(AudioListener*);
};





class PythonQtShell_AudioManager : public AudioManager
{
public:
    PythonQtShell_AudioManager(QObject*  parent = 0):AudioManager(parent),_wrapper(NULL) {};

   ~PythonQtShell_AudioManager();

virtual void Register(NamedBean*  s);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void childEvent(QChildEvent*  arg__1);
virtual void cleanUp();
virtual void customEvent(QEvent*  arg__1);
virtual void deregister(NamedBean*  s);
virtual void dispose();
virtual bool  event(QEvent*  arg__1);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual Audio*  getAudio(QString  arg__1);
virtual NamedBean*  getBeanBySystemName(QString  systemName);
virtual NamedBean*  getBeanByUserName(QString  userName);
virtual Audio*  getBySystemName(QString  arg__1);
virtual Audio*  getByUserName(QString  arg__1);
virtual NamedBean*  getNamedBean(QString  name);
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList();
virtual QStringList  getSystemNameList(QChar  arg__1);
virtual QStringList  getSystemNameList(char  arg__1);
virtual QString  getSystemPrefix();
virtual int  getXMLOrder();
virtual void init();
virtual QString  makeSystemName(QString  s);
virtual Audio*  newAudio(QString  arg__1, QString  arg__2);
virtual void on_propertyChange(PropertyChangeEvent*  e);
virtual Audio*  provideAudio(QString  arg__1);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void timerEvent(QTimerEvent*  arg__1);
virtual char  typeLetter();

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_AudioManager : public AudioManager
{ public:
inline void promoted_cleanUp() { AudioManager::cleanUp(); }
inline Audio*  promoted_getAudio(QString  arg__1) { return AudioManager::getAudio(arg__1); }
inline Audio*  promoted_getBySystemName(QString  arg__1) { return AudioManager::getBySystemName(arg__1); }
inline Audio*  promoted_getByUserName(QString  arg__1) { return AudioManager::getByUserName(arg__1); }
inline QStringList  promoted_getSystemNameList() { return AudioManager::getSystemNameList(); }
inline QStringList  promoted_getSystemNameList(QChar  arg__1) { return AudioManager::getSystemNameList(arg__1); }
inline QStringList  promoted_getSystemNameList(char  arg__1) { return AudioManager::getSystemNameList(arg__1); }
inline void promoted_init() { AudioManager::init(); }
inline Audio*  promoted_newAudio(QString  arg__1, QString  arg__2) { return AudioManager::newAudio(arg__1, arg__2); }
inline Audio*  promoted_provideAudio(QString  arg__1) { return AudioManager::provideAudio(arg__1); }
};

class PythonQtWrapper_AudioManager : public QObject
{ Q_OBJECT
public:
public slots:
AudioManager* new_AudioManager(QObject*  parent = 0);
void delete_AudioManager(AudioManager* obj) { delete obj; } 
   void cleanUp(AudioManager* theWrappedObject);
   Audio*  getAudio(AudioManager* theWrappedObject, QString  arg__1);
   Audio*  getBySystemName(AudioManager* theWrappedObject, QString  arg__1);
   Audio*  getByUserName(AudioManager* theWrappedObject, QString  arg__1);
   QStringList  getSystemNameList(AudioManager* theWrappedObject);
   QStringList  getSystemNameList(AudioManager* theWrappedObject, QChar  arg__1);
   QStringList  getSystemNameList(AudioManager* theWrappedObject, char  arg__1);
   void init(AudioManager* theWrappedObject);
   Audio*  newAudio(AudioManager* theWrappedObject, QString  arg__1, QString  arg__2);
   Audio*  provideAudio(AudioManager* theWrappedObject, QString  arg__1);
};





class PythonQtShell_AudioSource : public AudioSource
{
public:
    PythonQtShell_AudioSource(QObject*  parent = 0):AudioSource(parent),_wrapper(NULL) {};
    PythonQtShell_AudioSource(QString  systemName, QObject*  parent = 0):AudioSource(systemName, parent),_wrapper(NULL) {};
    PythonQtShell_AudioSource(QString  systemName, QString  userName, QObject*  parent = 0):AudioSource(systemName, userName, parent),_wrapper(NULL) {};

   ~PythonQtShell_AudioSource();

virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(PropertyChangeListener*  l, QString  beanRef, const QString  listenerRef);
virtual void childEvent(QChildEvent*  arg__1);
virtual void customEvent(QEvent*  arg__1);
virtual void dispose();
virtual bool  event(QEvent*  arg__1);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual void fadeIn();
virtual void fadeOut();
virtual AudioBuffer*  getAssignedBuffer();
virtual QString  getAssignedBufferName();
virtual QString  getComment();
virtual QVector3D  getCurrentPosition();
virtual QString  getDisplayName();
virtual float  getDopplerFactor();
virtual int  getFadeIn();
virtual int  getFadeOut();
virtual float  getGain();
virtual QString  getListenerRef(PropertyChangeListener*  l);
virtual QList<QString >*  getListenerRefs();
virtual int  getMaxLoops();
virtual float  getMaximumDistance();
virtual int  getMinLoops();
virtual int  getNumLoops();
virtual int  getNumPropertyChangeListeners();
virtual float  getPitch();
virtual QVector3D  getPosition();
virtual QVariant  getProperty(QString  key);
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners();
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners(QString  name);
virtual QList<QString >  getPropertyKeys();
virtual float  getReferenceDistance();
virtual float  getRollOffFactor();
virtual int  getState();
virtual QChar  getSubType();
virtual QString  getSystemName() const;
virtual QString  getUserName();
virtual QVector3D  getVelocity();
virtual bool  hashCode();
virtual bool  isBound();
virtual bool  isLooped();
virtual bool  isPositionRelative();
virtual bool  isQueued();
virtual int  numProcessedBuffers();
virtual int  numQueuedBuffers();
virtual void pause();
virtual void play();
virtual bool  queueBuffer(AudioBuffer*  arg__1);
virtual bool  queueBuffers(QQueue<AudioBuffer* >  arg__1);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void resetCurrentPosition();
virtual void resume();
virtual void rewind();
virtual void setAssignedBuffer(AudioBuffer*  arg__1);
virtual void setAssignedBuffer(QString  arg__1);
virtual void setComment(QString  comment);
virtual void setDopplerFactor(float  arg__1);
virtual void setFadeIn(int  arg__1);
virtual void setFadeOut(int  arg__1);
virtual void setGain(float  arg__1);
virtual void setLooped(bool  arg__1);
virtual void setMaxLoops(int  arg__1);
virtual void setMaximumDistance(float  arg__1);
virtual void setMinLoops(int  arg__1);
virtual void setPitch(float  arg__1);
virtual void setPosition(QVector3D  arg__1);
virtual void setPosition(float  arg__1, float  arg__2);
virtual void setPosition(float  arg__1, float  arg__2, float  arg__3);
virtual void setPositionRelative(bool  arg__1);
virtual void setProperty(QString  key, QVariant  value);
virtual void setReferenceDistance(float  arg__1);
virtual void setRollOffFactor(float  arg__1);
virtual void setState(int  arg__1);
virtual void setUserName(QString  s);
virtual void setVelocity(QVector3D  arg__1);
virtual void stateChanged(int  arg__1);
virtual void stop();
virtual void timerEvent(QTimerEvent*  arg__1);
virtual QString  toString();
virtual void togglePause();
virtual void togglePlay();
virtual bool  unqueueBuffers();
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_AudioSource : public AudioSource
{ public:
inline void promoted_fadeIn() { AudioSource::fadeIn(); }
inline void promoted_fadeOut() { AudioSource::fadeOut(); }
inline AudioBuffer*  promoted_getAssignedBuffer() { return AudioSource::getAssignedBuffer(); }
inline QString  promoted_getAssignedBufferName() { return AudioSource::getAssignedBufferName(); }
inline QVector3D  promoted_getCurrentPosition() { return AudioSource::getCurrentPosition(); }
inline float  promoted_getDopplerFactor() { return AudioSource::getDopplerFactor(); }
inline int  promoted_getFadeIn() { return AudioSource::getFadeIn(); }
inline int  promoted_getFadeOut() { return AudioSource::getFadeOut(); }
inline float  promoted_getGain() { return AudioSource::getGain(); }
inline int  promoted_getMaxLoops() { return AudioSource::getMaxLoops(); }
inline float  promoted_getMaximumDistance() { return AudioSource::getMaximumDistance(); }
inline int  promoted_getMinLoops() { return AudioSource::getMinLoops(); }
inline int  promoted_getNumLoops() { return AudioSource::getNumLoops(); }
inline float  promoted_getPitch() { return AudioSource::getPitch(); }
inline QVector3D  promoted_getPosition() { return AudioSource::getPosition(); }
inline float  promoted_getReferenceDistance() { return AudioSource::getReferenceDistance(); }
inline float  promoted_getRollOffFactor() { return AudioSource::getRollOffFactor(); }
inline QVector3D  promoted_getVelocity() { return AudioSource::getVelocity(); }
inline bool  promoted_isBound() { return AudioSource::isBound(); }
inline bool  promoted_isLooped() { return AudioSource::isLooped(); }
inline bool  promoted_isPositionRelative() { return AudioSource::isPositionRelative(); }
inline bool  promoted_isQueued() { return AudioSource::isQueued(); }
inline int  promoted_numProcessedBuffers() { return AudioSource::numProcessedBuffers(); }
inline int  promoted_numQueuedBuffers() { return AudioSource::numQueuedBuffers(); }
inline void promoted_pause() { AudioSource::pause(); }
inline void promoted_play() { AudioSource::play(); }
inline bool  promoted_queueBuffer(AudioBuffer*  arg__1) { return AudioSource::queueBuffer(arg__1); }
inline bool  promoted_queueBuffers(QQueue<AudioBuffer* >  arg__1) { return AudioSource::queueBuffers(arg__1); }
inline void promoted_resetCurrentPosition() { AudioSource::resetCurrentPosition(); }
inline void promoted_resume() { AudioSource::resume(); }
inline void promoted_rewind() { AudioSource::rewind(); }
inline void promoted_setAssignedBuffer(AudioBuffer*  arg__1) { AudioSource::setAssignedBuffer(arg__1); }
inline void promoted_setAssignedBuffer(QString  arg__1) { AudioSource::setAssignedBuffer(arg__1); }
inline void promoted_setDopplerFactor(float  arg__1) { AudioSource::setDopplerFactor(arg__1); }
inline void promoted_setFadeIn(int  arg__1) { AudioSource::setFadeIn(arg__1); }
inline void promoted_setFadeOut(int  arg__1) { AudioSource::setFadeOut(arg__1); }
inline void promoted_setGain(float  arg__1) { AudioSource::setGain(arg__1); }
inline void promoted_setLooped(bool  arg__1) { AudioSource::setLooped(arg__1); }
inline void promoted_setMaxLoops(int  arg__1) { AudioSource::setMaxLoops(arg__1); }
inline void promoted_setMaximumDistance(float  arg__1) { AudioSource::setMaximumDistance(arg__1); }
inline void promoted_setMinLoops(int  arg__1) { AudioSource::setMinLoops(arg__1); }
inline void promoted_setPitch(float  arg__1) { AudioSource::setPitch(arg__1); }
inline void promoted_setPosition(QVector3D  arg__1) { AudioSource::setPosition(arg__1); }
inline void promoted_setPosition(float  arg__1, float  arg__2) { AudioSource::setPosition(arg__1, arg__2); }
inline void promoted_setPosition(float  arg__1, float  arg__2, float  arg__3) { AudioSource::setPosition(arg__1, arg__2, arg__3); }
inline void promoted_setPositionRelative(bool  arg__1) { AudioSource::setPositionRelative(arg__1); }
inline void promoted_setReferenceDistance(float  arg__1) { AudioSource::setReferenceDistance(arg__1); }
inline void promoted_setRollOffFactor(float  arg__1) { AudioSource::setRollOffFactor(arg__1); }
inline void promoted_setVelocity(QVector3D  arg__1) { AudioSource::setVelocity(arg__1); }
inline void promoted_stop() { AudioSource::stop(); }
inline void promoted_togglePause() { AudioSource::togglePause(); }
inline void promoted_togglePlay() { AudioSource::togglePlay(); }
inline bool  promoted_unqueueBuffers() { return AudioSource::unqueueBuffers(); }
};

class PythonQtWrapper_AudioSource : public QObject
{ Q_OBJECT
public:
public slots:
AudioSource* new_AudioSource(QObject*  parent = 0);
AudioSource* new_AudioSource(QString  systemName, QObject*  parent = 0);
AudioSource* new_AudioSource(QString  systemName, QString  userName, QObject*  parent = 0);
void delete_AudioSource(AudioSource* obj) { delete obj; } 
   void fadeIn(AudioSource* theWrappedObject);
   void fadeOut(AudioSource* theWrappedObject);
   AudioBuffer*  getAssignedBuffer(AudioSource* theWrappedObject);
   QString  getAssignedBufferName(AudioSource* theWrappedObject);
   QVector3D  getCurrentPosition(AudioSource* theWrappedObject);
   float  getDopplerFactor(AudioSource* theWrappedObject);
   int  getFadeIn(AudioSource* theWrappedObject);
   int  getFadeOut(AudioSource* theWrappedObject);
   float  getGain(AudioSource* theWrappedObject);
   int  getMaxLoops(AudioSource* theWrappedObject);
   float  getMaximumDistance(AudioSource* theWrappedObject);
   int  getMinLoops(AudioSource* theWrappedObject);
   int  getNumLoops(AudioSource* theWrappedObject);
   float  getPitch(AudioSource* theWrappedObject);
   QVector3D  getPosition(AudioSource* theWrappedObject);
   float  getReferenceDistance(AudioSource* theWrappedObject);
   float  getRollOffFactor(AudioSource* theWrappedObject);
   QVector3D  getVelocity(AudioSource* theWrappedObject);
   bool  isBound(AudioSource* theWrappedObject);
   bool  isLooped(AudioSource* theWrappedObject);
   bool  isPositionRelative(AudioSource* theWrappedObject);
   bool  isQueued(AudioSource* theWrappedObject);
   int  numProcessedBuffers(AudioSource* theWrappedObject);
   int  numQueuedBuffers(AudioSource* theWrappedObject);
   void pause(AudioSource* theWrappedObject);
   void play(AudioSource* theWrappedObject);
   bool  queueBuffer(AudioSource* theWrappedObject, AudioBuffer*  arg__1);
   bool  queueBuffers(AudioSource* theWrappedObject, QQueue<AudioBuffer* >  arg__1);
   void resetCurrentPosition(AudioSource* theWrappedObject);
   void resume(AudioSource* theWrappedObject);
   void rewind(AudioSource* theWrappedObject);
   void setAssignedBuffer(AudioSource* theWrappedObject, AudioBuffer*  arg__1);
   void setAssignedBuffer(AudioSource* theWrappedObject, QString  arg__1);
   void setDopplerFactor(AudioSource* theWrappedObject, float  arg__1);
   void setFadeIn(AudioSource* theWrappedObject, int  arg__1);
   void setFadeOut(AudioSource* theWrappedObject, int  arg__1);
   void setGain(AudioSource* theWrappedObject, float  arg__1);
   void setLooped(AudioSource* theWrappedObject, bool  arg__1);
   void setMaxLoops(AudioSource* theWrappedObject, int  arg__1);
   void setMaximumDistance(AudioSource* theWrappedObject, float  arg__1);
   void setMinLoops(AudioSource* theWrappedObject, int  arg__1);
   void setPitch(AudioSource* theWrappedObject, float  arg__1);
   void setPosition(AudioSource* theWrappedObject, QVector3D  arg__1);
   void setPosition(AudioSource* theWrappedObject, float  arg__1, float  arg__2);
   void setPosition(AudioSource* theWrappedObject, float  arg__1, float  arg__2, float  arg__3);
   void setPositionRelative(AudioSource* theWrappedObject, bool  arg__1);
   void setReferenceDistance(AudioSource* theWrappedObject, float  arg__1);
   void setRollOffFactor(AudioSource* theWrappedObject, float  arg__1);
   void setVelocity(AudioSource* theWrappedObject, QVector3D  arg__1);
   void stop(AudioSource* theWrappedObject);
   void togglePause(AudioSource* theWrappedObject);
   void togglePlay(AudioSource* theWrappedObject);
   bool  unqueueBuffers(AudioSource* theWrappedObject);
    QString py_toString(AudioSource*);
};





class PythonQtShell_CommandStation : public CommandStation
{
public:
    PythonQtShell_CommandStation(QObject*  parent = 0):CommandStation(parent),_wrapper(NULL) {};

   ~PythonQtShell_CommandStation();

virtual void childEvent(QChildEvent*  arg__1);
virtual void customEvent(QEvent*  arg__1);
virtual bool  event(QEvent*  arg__1);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual QString  getSystemPrefix();
virtual QString  getUserName();
virtual void sendPacket(QByteArray  arg__1, int  arg__2);
virtual void timerEvent(QTimerEvent*  arg__1);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_CommandStation : public CommandStation
{ public:
inline QString  promoted_getSystemPrefix() { return CommandStation::getSystemPrefix(); }
inline QString  promoted_getUserName() { return CommandStation::getUserName(); }
inline void promoted_sendPacket(QByteArray  arg__1, int  arg__2) { CommandStation::sendPacket(arg__1, arg__2); }
};

class PythonQtWrapper_CommandStation : public QObject
{ Q_OBJECT
public:
public slots:
CommandStation* new_CommandStation(QObject*  parent = 0);
void delete_CommandStation(CommandStation* obj) { delete obj; } 
   QString  getSystemPrefix(CommandStation* theWrappedObject);
   QString  getUserName(CommandStation* theWrappedObject);
   void sendPacket(CommandStation* theWrappedObject, QByteArray  arg__1, int  arg__2);
};





class PythonQtShell_DccLocoAddress : public DccLocoAddress
{
public:
    PythonQtShell_DccLocoAddress(const DccLocoAddress&  l, QObject*  parent = 0):DccLocoAddress(l, parent),_wrapper(NULL) {};
    PythonQtShell_DccLocoAddress(int  number, bool  isLong, QObject*  parent = 0):DccLocoAddress(number, isLong, parent),_wrapper(NULL) {};

   ~PythonQtShell_DccLocoAddress();

virtual void childEvent(QChildEvent*  arg__1);
virtual void customEvent(QEvent*  arg__1);
virtual bool  event(QEvent*  arg__1);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual int  getNumber();
virtual void timerEvent(QTimerEvent*  arg__1);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_DccLocoAddress : public DccLocoAddress
{ public:
inline int  promoted_getNumber() { return DccLocoAddress::getNumber(); }
};

class PythonQtWrapper_DccLocoAddress : public QObject
{ Q_OBJECT
public:
public slots:
DccLocoAddress* new_DccLocoAddress(const DccLocoAddress&  l, QObject*  parent = 0);
DccLocoAddress* new_DccLocoAddress(int  number, bool  isLong, QObject*  parent = 0);
void delete_DccLocoAddress(DccLocoAddress* obj) { delete obj; } 
   int  getNumber(DccLocoAddress* theWrappedObject);
   int  hashCode(DccLocoAddress* theWrappedObject);
   bool  isLongAddress(DccLocoAddress* theWrappedObject);
   bool  __eq__(DccLocoAddress* theWrappedObject, DccLocoAddress*  a);
   QString  toString(DccLocoAddress* theWrappedObject);
    QString py_toString(DccLocoAddress*);
};





class PythonQtShell_DccThrottle : public DccThrottle
{
public:
    PythonQtShell_DccThrottle():DccThrottle(),_wrapper(NULL) {};

   ~PythonQtShell_DccThrottle();

virtual void addPropertyChangeListener(PropertyChangeListener*  arg__1);
virtual void childEvent(QChildEvent*  arg__1);
virtual void customEvent(QEvent*  arg__1);
virtual bool  event(QEvent*  arg__1);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual bool  getF0();
virtual bool  getF0Momentary();
virtual bool  getF1();
virtual bool  getF10();
virtual bool  getF10Momentary();
virtual bool  getF11();
virtual bool  getF11Momentary();
virtual bool  getF12();
virtual bool  getF12Momentary();
virtual bool  getF13();
virtual bool  getF13Momentary();
virtual bool  getF14();
virtual bool  getF14Momentary();
virtual bool  getF15();
virtual bool  getF15Momentary();
virtual bool  getF16();
virtual bool  getF16Momentary();
virtual bool  getF17();
virtual bool  getF17Momentary();
virtual bool  getF18();
virtual bool  getF18Momentary();
virtual bool  getF19();
virtual bool  getF19Momentary();
virtual bool  getF1Momentary();
virtual bool  getF2();
virtual bool  getF20();
virtual bool  getF20Momentary();
virtual bool  getF21();
virtual bool  getF21Momentary();
virtual bool  getF22();
virtual bool  getF22Momentary();
virtual bool  getF23();
virtual bool  getF23Momentary();
virtual bool  getF24();
virtual bool  getF24Momentary();
virtual bool  getF25();
virtual bool  getF25Momentary();
virtual bool  getF26();
virtual bool  getF26Momentary();
virtual bool  getF27();
virtual bool  getF27Momentary();
virtual bool  getF28();
virtual bool  getF28Momentary();
virtual bool  getF2Momentary();
virtual bool  getF3();
virtual bool  getF3Momentary();
virtual bool  getF4();
virtual bool  getF4Momentary();
virtual bool  getF5();
virtual bool  getF5Momentary();
virtual bool  getF6();
virtual bool  getF6Momentary();
virtual bool  getF7();
virtual bool  getF7Momentary();
virtual bool  getF8();
virtual bool  getF8Momentary();
virtual bool  getF9();
virtual bool  getF9Momentary();
virtual bool  getIsForward();
virtual QVector<PropertyChangeListener* >*  getListeners();
virtual LocoAddress*  getLocoAddress();
virtual float  getSpeedIncrement();
virtual float  getSpeedSetting();
virtual int  getSpeedStepMode();
virtual void removePropertyChangeListener(PropertyChangeListener*  arg__1);
virtual void setF0(bool  arg__1);
virtual void setF0Momentary(bool  arg__1);
virtual void setF1(bool  arg__1);
virtual void setF10(bool  arg__1);
virtual void setF10Momentary(bool  arg__1);
virtual void setF11(bool  arg__1);
virtual void setF11Momentary(bool  arg__1);
virtual void setF12(bool  arg__1);
virtual void setF12Momentary(bool  arg__1);
virtual void setF13(bool  arg__1);
virtual void setF13Momentary(bool  arg__1);
virtual void setF14(bool  arg__1);
virtual void setF14Momentary(bool  arg__1);
virtual void setF15(bool  arg__1);
virtual void setF15Momentary(bool  arg__1);
virtual void setF16(bool  arg__1);
virtual void setF16Momentary(bool  arg__1);
virtual void setF17(bool  arg__1);
virtual void setF17Momentary(bool  arg__1);
virtual void setF18(bool  arg__1);
virtual void setF18Momentary(bool  arg__1);
virtual void setF19(bool  arg__1);
virtual void setF19Momentary(bool  arg__1);
virtual void setF1Momentary(bool  arg__1);
virtual void setF2(bool  arg__1);
virtual void setF20(bool  arg__1);
virtual void setF20Momentary(bool  arg__1);
virtual void setF21(bool  arg__1);
virtual void setF21Momentary(bool  arg__1);
virtual void setF22(bool  arg__1);
virtual void setF22Momentary(bool  arg__1);
virtual void setF23(bool  arg__1);
virtual void setF23Momentary(bool  arg__1);
virtual void setF24(bool  arg__1);
virtual void setF24Momentary(bool  arg__1);
virtual void setF25(bool  arg__1);
virtual void setF25Momentary(bool  arg__1);
virtual void setF26(bool  arg__1);
virtual void setF26Momentary(bool  arg__1);
virtual void setF27(bool  arg__1);
virtual void setF27Momentary(bool  arg__1);
virtual void setF28(bool  arg__1);
virtual void setF28Momentary(bool  arg__1);
virtual void setF2Momentary(bool  arg__1);
virtual void setF3(bool  arg__1);
virtual void setF3Momentary(bool  arg__1);
virtual void setF4(bool  arg__1);
virtual void setF4Momentary(bool  arg__1);
virtual void setF5(bool  arg__1);
virtual void setF5Momentary(bool  arg__1);
virtual void setF6(bool  arg__1);
virtual void setF6Momentary(bool  arg__1);
virtual void setF7(bool  arg__1);
virtual void setF7Momentary(bool  arg__1);
virtual void setF8(bool  arg__1);
virtual void setF8Momentary(bool  arg__1);
virtual void setF9(bool  arg__1);
virtual void setF9Momentary(bool  arg__1);
virtual void setIsForward(bool  arg__1);
virtual void setSpeedSetting(float  arg__1);
virtual void setSpeedStepMode(int  arg__1);
virtual void timerEvent(QTimerEvent*  arg__1);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_DccThrottle : public DccThrottle
{ public:
inline float  promoted_getSpeedIncrement() { return DccThrottle::getSpeedIncrement(); }
inline int  promoted_getSpeedStepMode() { return DccThrottle::getSpeedStepMode(); }
inline void promoted_setSpeedStepMode(int  arg__1) { DccThrottle::setSpeedStepMode(arg__1); }
};

class PythonQtWrapper_DccThrottle : public QObject
{ Q_OBJECT
public:
public slots:
DccThrottle* new_DccThrottle();
void delete_DccThrottle(DccThrottle* obj) { delete obj; } 
   float  getSpeedIncrement(DccThrottle* theWrappedObject);
   int  getSpeedStepMode(DccThrottle* theWrappedObject);
   void setSpeedStepMode(DccThrottle* theWrappedObject, int  arg__1);
};





class PythonQtShell_Editor : public Editor
{
public:
    PythonQtShell_Editor(QString  name, QWidget*  parent):Editor(name, parent),_wrapper(NULL) {};
    PythonQtShell_Editor(QString  name, bool  saveSize, bool  savePosition, QWidget*  parent = 0):Editor(name, saveSize, savePosition, parent),_wrapper(NULL) {};
    PythonQtShell_Editor(QWidget*  parent = 0):Editor(parent),_wrapper(NULL) {};

   ~PythonQtShell_Editor();

virtual void actionEvent(QActionEvent*  arg__1);
virtual void addHelpMenu(QString  ref, bool  direct);
virtual void changeEvent(QEvent*  arg__1);
virtual void childEvent(QChildEvent*  arg__1);
virtual void contextMenuEvent(QContextMenuEvent*  event);
virtual QMenu*  createPopupMenu();
virtual void customEvent(QEvent*  arg__1);
virtual int  devType() const;
virtual void dragEnterEvent(QDragEnterEvent*  arg__1);
virtual void dragLeaveEvent(QDragLeaveEvent*  arg__1);
virtual void dragMoveEvent(QDragMoveEvent*  arg__1);
virtual void dropEvent(QDropEvent*  arg__1);
virtual void enterEvent(QEvent*  arg__1);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual void focusInEvent(QFocusEvent*  arg__1);
virtual bool  focusNextPrevChild(bool  next);
virtual void focusOutEvent(QFocusEvent*  arg__1);
virtual QString  getTitle();
virtual void handleModified();
virtual int  heightForWidth(int  arg__1) const;
virtual void hideEvent(QHideEvent*  arg__1);
virtual void init(QString  name);
virtual void initComponents();
virtual void inputMethodEvent(QInputMethodEvent*  arg__1);
virtual QVariant  inputMethodQuery(Qt::InputMethodQuery  arg__1) const;
virtual void keyPressEvent(QKeyEvent*  arg__1);
virtual void keyReleaseEvent(QKeyEvent*  arg__1);
virtual void languageChange();
virtual void leaveEvent(QEvent*  arg__1);
virtual int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
virtual QSize  minimumSizeHint() const;
virtual void mouseDoubleClickEvent(QMouseEvent*  arg__1);
virtual void mouseMoveEvent(QMouseEvent*  arg__1);
virtual void mousePressEvent(QMouseEvent*  arg__1);
virtual void mouseReleaseEvent(QMouseEvent*  arg__1);
virtual void moveEvent(QMoveEvent*  e);
virtual QPaintEngine*  paintEngine() const;
virtual void paintEvent(QPaintEvent*  arg__1);
virtual void putItem(Positionable*  l);
virtual void repaint();
virtual void resizeEvent(QResizeEvent*  e);
virtual void setNextLocation(Positionable*  arg__1);
virtual void setTitle();
virtual void showEvent(QShowEvent*  arg__1);
virtual QSize  sizeHint() const;
virtual void storeValues();
virtual void tabletEvent(QTabletEvent*  arg__1);
virtual void targetWindowClosing(bool  save);
virtual void targetWindowClosingEvent(QCloseEvent*  arg__1);
virtual void timerEvent(QTimerEvent*  arg__1);
virtual bool  useGlobalFlag();
virtual void wheelEvent(QWheelEvent*  arg__1);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_Editor : public Editor
{ public:
inline void promoted_addBackgroundEditor() { Editor::addBackgroundEditor(); }
inline void promoted_addClock() { Editor::addClock(); }
inline void promoted_addIconEditor() { Editor::addIconEditor(); }
inline void promoted_addLeftTOEditor() { Editor::addLeftTOEditor(); }
inline void promoted_addLightEditor() { Editor::addLightEditor(); }
inline void promoted_addMemoryEditor() { Editor::addMemoryEditor(); }
inline void promoted_addReporterEditor() { Editor::addReporterEditor(); }
inline void promoted_addRightTOEditor() { Editor::addRightTOEditor(); }
inline void promoted_addSensorEditor() { Editor::addSensorEditor(); }
inline void promoted_addSignalHeadEditor() { Editor::addSignalHeadEditor(); }
inline void promoted_addSignalMastEditor() { Editor::addSignalMastEditor(); }
inline void promoted_addSlip() { Editor::addSlip(); }
inline void promoted_addSlipTOEditor() { Editor::addSlipTOEditor(); }
inline void promoted_addTextEditor() { Editor::addTextEditor(); }
inline void promoted_addToTarget(Positionable*  l) { Editor::addToTarget(l); }
inline void promoted_addTurnoutL() { Editor::addTurnoutL(); }
inline void promoted_addTurnoutR() { Editor::addTurnoutR(); }
inline Editor*  promoted_changeView(QString  className) { return Editor::changeView(className); }
inline void promoted_dockSelections(Positionable*  p) { Editor::dockSelections(p); }
inline int  promoted_getItemX(Positionable*  p, int  deltaX) { return Editor::getItemX(p, deltaX); }
inline int  promoted_getItemY(Positionable*  p, int  deltaY) { return Editor::getItemY(p, deltaY); }
inline QList<Positionable* >  promoted_getSelectedItems(QGraphicsSceneMouseEvent*  event) { return Editor::getSelectedItems(event); }
inline QList<Positionable* >  promoted_getSelectedItems(QPointF  pt) { return Editor::getSelectedItems(pt); }
inline QSizeF  promoted_getTargetPanelSize() { return Editor::getTargetPanelSize(); }
inline QString  promoted_getTitle() { return Editor::getTitle(); }
inline void promoted_init(QString  name) { Editor::init(name); }
inline void promoted_locoMarkerFromInput() { Editor::locoMarkerFromInput(); }
inline void promoted_locoMarkerFromRoster() { Editor::locoMarkerFromRoster(); }
inline void promoted_makeSelectionGroup(QGraphicsSceneMouseEvent*  event) { Editor::makeSelectionGroup(event); }
inline void promoted_modifySelectionGroup(Positionable*  selection, QGraphicsSceneMouseEvent*  event) { Editor::modifySelectionGroup(selection, event); }
inline void promoted_moveItem(Positionable*  p, int  deltaX, int  deltaY) { Editor::moveItem(p, deltaX, deltaY); }
inline void promoted_putBackground() { Editor::putBackground(); }
inline Positionable*  promoted_putIcon() { return Editor::putIcon(); }
inline void promoted_putItem(Positionable*  l) { Editor::putItem(l); }
inline void promoted_removeFromTarget(Positionable*  l) { Editor::removeFromTarget(l); }
inline void promoted_removeMarkers() { Editor::removeMarkers(); }
inline void promoted_removeSelections(Positionable*  p) { Editor::removeSelections(p); }
inline void promoted_repaint() { Editor::repaint(); }
inline void promoted_setNextLocation(Positionable*  arg__1) { Editor::setNextLocation(arg__1); }
inline void promoted_setPaintScale(double  newScale) { Editor::setPaintScale(newScale); }
inline void promoted_setSecondSelectionGroup(QList<Positionable* >  list) { Editor::setSecondSelectionGroup(list); }
inline void promoted_setSelectionsDockingLocation(Positionable*  p) { Editor::setSelectionsDockingLocation(p); }
inline void promoted_setSelectionsHidden(bool  enabled, Positionable*  p) { Editor::setSelectionsHidden(enabled, p); }
inline bool  promoted_setSelectionsPositionable(bool  enabled, Positionable*  p) { return Editor::setSelectionsPositionable(enabled, p); }
inline void promoted_setSelectionsRotation(int  k, Positionable*  p) { Editor::setSelectionsRotation(k, p); }
inline void promoted_setSelectionsScale(double  s, Positionable*  p) { Editor::setSelectionsScale(s, p); }
inline void promoted_setTargetPanel(QGraphicsScene*  targetPanel, JmriJFrame*  frame) { Editor::setTargetPanel(targetPanel, frame); }
inline void promoted_setTargetPanelSize(int  w, int  h) { Editor::setTargetPanelSize(w, h); }
inline bool  promoted_setTextAttributes(Positionable*  p, QMenu*  popup) { return Editor::setTextAttributes(p, popup); }
inline void promoted_setTitle() { Editor::setTitle(); }
inline void promoted_setToolTip(QString  tt) { Editor::setToolTip(tt); }
inline bool  promoted_showAlignPopup(Positionable*  p) { return Editor::showAlignPopup(p); }
inline void promoted_targetWindowClosing(bool  save) { Editor::targetWindowClosing(save); }
inline void promoted_targetWindowClosingEvent(QCloseEvent*  arg__1) { Editor::targetWindowClosingEvent(arg__1); }
inline bool  promoted_useGlobalFlag() { return Editor::useGlobalFlag(); }
};

class PythonQtWrapper_Editor : public QObject
{ Q_OBJECT
public:
public slots:
Editor* new_Editor(QString  name, QWidget*  parent);
Editor* new_Editor(QString  name, bool  saveSize, bool  savePosition, QWidget*  parent = 0);
Editor* new_Editor(QWidget*  parent = 0);
void delete_Editor(Editor* obj) { delete obj; } 
   void addClock(Editor* theWrappedObject);
   void addToTarget(Editor* theWrappedObject, Positionable*  l);
   bool  allControlling(Editor* theWrappedObject);
   bool  allPositionable(Editor* theWrappedObject);
   Editor*  changeView(Editor* theWrappedObject, QString  className);
   void clearBackgroundColor(Editor* theWrappedObject);
   bool  deletePanel(Editor* theWrappedObject);
   void displayLevelChange(Editor* theWrappedObject, Positionable*  l);
   void dispose(Editor* theWrappedObject, bool  clear);
   void disposeLoadData(Editor* theWrappedObject);
   void dockSelections(Editor* theWrappedObject, Positionable*  p);
   void drawSelectRect(Editor* theWrappedObject, int  x, int  y);
   int  getAnchorX(Editor* theWrappedObject);
   int  getAnchorY(Editor* theWrappedObject);
   QColor  getBackgroundColor(Editor* theWrappedObject);
   QList<Positionable* >  getContents(Editor* theWrappedObject);
   bool  getFlag(Editor* theWrappedObject, int  whichOption, bool  localFlag);
   int  getItemX(Editor* theWrappedObject, Positionable*  p, int  deltaX);
   int  getItemY(Editor* theWrappedObject, Positionable*  p, int  deltaY);
   QString  getName(Editor* theWrappedObject);
   double  getPaintScale(Editor* theWrappedObject);
   QRectF  getSelectRect(Editor* theWrappedObject);
   QList<Positionable* >  getSelectedItems(Editor* theWrappedObject, QGraphicsSceneMouseEvent*  event);
   QList<Positionable* >  getSelectedItems(Editor* theWrappedObject, QPointF  pt);
   JFrame*  getTargetFrame(Editor* theWrappedObject);
   QGraphicsScene*  getTargetPanel(Editor* theWrappedObject);
   QSizeF  getTargetPanelSize(Editor* theWrappedObject);
   QString  getTitle(Editor* theWrappedObject);
   void init(Editor* theWrappedObject, QString  name);
   bool  isEditable(Editor* theWrappedObject);
   bool  isPanelMenuVisible(Editor* theWrappedObject);
   void loadFailed(Editor* theWrappedObject);
   bool  loadOK(Editor* theWrappedObject);
   void makeSelectionGroup(Editor* theWrappedObject, QGraphicsSceneMouseEvent*  event);
   void modifySelectionGroup(Editor* theWrappedObject, Positionable*  selection, QGraphicsSceneMouseEvent*  event);
   void moveItem(Editor* theWrappedObject, Positionable*  p, int  deltaX, int  deltaY);
   void paint(Editor* theWrappedObject, QGraphicsScene*  g);
   void putItem(Editor* theWrappedObject, Positionable*  l);
   bool  removeFromContents(Editor* theWrappedObject, Positionable*  l);
   void removeFromTarget(Editor* theWrappedObject, Positionable*  l);
   void removeSelections(Editor* theWrappedObject, Positionable*  p);
   void repaint(Editor* theWrappedObject);
   void setAllControlling(Editor* theWrappedObject, bool  state);
   void setAllEditable(Editor* theWrappedObject, bool  state);
   void setAllPositionable(Editor* theWrappedObject, bool  state);
   void setAllShowTooltip(Editor* theWrappedObject, bool  state);
   void setBackgroundColor(Editor* theWrappedObject, QColor  col);
   void setDefaultColors(Editor* theWrappedObject);
   void setDefaultToolTip(Editor* theWrappedObject, QString  dtt);
   void setDirty(Editor* theWrappedObject, bool  bDirty = true);
   void setDisplayLevelMenu(Editor* theWrappedObject, Positionable*  p, QMenu*  popup);
   void setGlobalSetsLocalFlag(Editor* theWrappedObject, bool  set);
   void setHiddenMenu(Editor* theWrappedObject, Positionable*  p, QMenu*  popup);
   void setHighlightColor(Editor* theWrappedObject, QColor  color);
   void setName(Editor* theWrappedObject, QString  name);
   void setNextLocation(Editor* theWrappedObject, Positionable*  arg__1);
   void setPaintScale(Editor* theWrappedObject, double  newScale);
   void setPanelMenuVisible(Editor* theWrappedObject, bool  state);
   void setPositionableMenu(Editor* theWrappedObject, Positionable*  p, QMenu*  popup);
   void setRemoveMenu(Editor* theWrappedObject, Positionable*  p, QMenu*  popup);
   void setSecondSelectionGroup(Editor* theWrappedObject, QList<Positionable* >  list);
   void setSelectGroupColor(Editor* theWrappedObject, QColor  color);
   void setSelectRectColor(Editor* theWrappedObject, QColor  color);
   void setSelectRectStroke(Editor* theWrappedObject, Qt::PenStyle  stroke);
   void setSelectionsDockingLocation(Editor* theWrappedObject, Positionable*  p);
   void setSelectionsHidden(Editor* theWrappedObject, bool  enabled, Positionable*  p);
   void setSelectionsRotation(Editor* theWrappedObject, int  k, Positionable*  p);
   void setSelectionsScale(Editor* theWrappedObject, double  s, Positionable*  p);
   bool  setShowAlignmentMenu(Editor* theWrappedObject, Positionable*  p, QMenu*  popup);
   void setShowCoordinates(Editor* theWrappedObject, bool  state);
   bool  setShowCoordinatesMenu(Editor* theWrappedObject, Positionable*  p, QMenu*  popup);
   void setShowHidden(Editor* theWrappedObject, bool  state);
   void setShowTooltipMenu(Editor* theWrappedObject, Positionable*  p, QMenu*  popup);
   void setTargetPanel(Editor* theWrappedObject, QGraphicsScene*  targetPanel, JmriJFrame*  frame);
   void setTargetPanelSize(Editor* theWrappedObject, int  w, int  h);
   bool  setTextAttributes(Editor* theWrappedObject, Positionable*  p, QMenu*  popup);
   void setTitle(Editor* theWrappedObject);
   void setToolTip(Editor* theWrappedObject, QString  tt);
   void setUseGlobalFlag(Editor* theWrappedObject, bool  set);
   bool  showAlignPopup(Editor* theWrappedObject, Positionable*  p);
   bool  showCoordinates(Editor* theWrappedObject);
   bool  showHidden(Editor* theWrappedObject);
   bool  showTooltip(Editor* theWrappedObject);
   void targetWindowClosing(Editor* theWrappedObject, bool  save);
   void targetWindowClosingEvent(Editor* theWrappedObject, QCloseEvent*  arg__1);
   bool  useGlobalFlag(Editor* theWrappedObject);
void py_set_frameLocationX(Editor* theWrappedObject, int  frameLocationX){ theWrappedObject->frameLocationX = frameLocationX; }
int  py_get_frameLocationX(Editor* theWrappedObject){ return theWrappedObject->frameLocationX; }
void py_set_frameLocationY(Editor* theWrappedObject, int  frameLocationY){ theWrappedObject->frameLocationY = frameLocationY; }
int  py_get_frameLocationY(Editor* theWrappedObject){ return theWrappedObject->frameLocationY; }
};





class PythonQtShell_EventObject : public EventObject
{
public:
    PythonQtShell_EventObject(QObject*  source, QObject*  parent = 0):EventObject(source, parent),_wrapper(NULL) {};

   ~PythonQtShell_EventObject();

virtual void childEvent(QChildEvent*  arg__1);
virtual void customEvent(QEvent*  arg__1);
virtual bool  event(QEvent*  arg__1);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual void timerEvent(QTimerEvent*  arg__1);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtWrapper_EventObject : public QObject
{ Q_OBJECT
public:
public slots:
EventObject* new_EventObject(QObject*  source, QObject*  parent = 0);
void delete_EventObject(EventObject* obj) { delete obj; } 
   QObject*  getSource(EventObject* theWrappedObject);
   QString  toString(EventObject* theWrappedObject);
    QString py_toString(EventObject*);
};





class PythonQtShell_FileUtil : public FileUtil
{
public:
    PythonQtShell_FileUtil(QObject*  parent = 0):FileUtil(parent),_wrapper(NULL) {};

   ~PythonQtShell_FileUtil();

virtual void childEvent(QChildEvent*  arg__1);
virtual void customEvent(QEvent*  arg__1);
virtual bool  event(QEvent*  arg__1);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual void timerEvent(QTimerEvent*  arg__1);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtWrapper_FileUtil : public QObject
{ Q_OBJECT
public:
public slots:
FileUtil* new_FileUtil(QObject*  parent = 0);
void delete_FileUtil(FileUtil* obj) { delete obj; } 
   void static_FileUtil_createDirectory(QString  path);
   QUrl  static_FileUtil_fileToURL(QFile*  file);
   QUrl  static_FileUtil_findExternalFilename(QString  path);
   QUrl  static_FileUtil_findURL(QString  path);
   QUrl  static_FileUtil_findURL(QString  path, QStringList  searchPaths);
   QString  static_FileUtil_getAbsoluteFilename(QString  path);
   QString  static_FileUtil_getExternalFilename(QString  pName);
   QString  static_FileUtil_getHomePath();
   QString  static_FileUtil_getPortableFilename(QString  filename);
   QString  static_FileUtil_getPortableFilename(QString  filename, bool  ignoreUserFilesPath, bool  ignoreProfilePath);
   QString  static_FileUtil_getPreferencesPath();
   QString  static_FileUtil_getProfilePath();
   QString  static_FileUtil_getProgramPath();
   QString  static_FileUtil_getScriptsPath();
   QString  static_FileUtil_getUserFilesPath();
   QString  static_FileUtil_getUserResourcePath();
   bool  static_FileUtil_isPortableFilename(QString  filename);
   void static_FileUtil_logFilePaths();
   QString  static_FileUtil_pathFromPortablePath(QString  path);
   QString  static_FileUtil_sanitizeFilename(QString  name);
   void static_FileUtil_setProfilePath(QString  path);
   void static_FileUtil_setProgramPath(QDir  path);
   void static_FileUtil_setProgramPath(QString  path);
   void static_FileUtil_setScriptsPath(QString  path);
   void static_FileUtil_setUserFilesPath(QString  path);
};





class PythonQtShell_FlowLayout : public FlowLayout
{
public:
    PythonQtShell_FlowLayout(QWidget*  parent, int  margin = -1, int  hSpacing = -1, int  vSpacing = -1):FlowLayout(parent, margin, hSpacing, vSpacing),_wrapper(NULL) {};
    PythonQtShell_FlowLayout(int  margin = -1, int  hSpacing = -1, int  vSpacing = -1):FlowLayout(margin, hSpacing, vSpacing),_wrapper(NULL) {};

   ~PythonQtShell_FlowLayout();

virtual void addItem(QLayoutItem*  item);
virtual void childEvent(QChildEvent*  e);
virtual int  count() const;
virtual void customEvent(QEvent*  arg__1);
virtual bool  event(QEvent*  arg__1);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual Qt::Orientations  expandingDirections() const;
virtual QRect  geometry() const;
virtual int  indexOf(QWidget*  arg__1) const;
virtual void invalidate();
virtual bool  isEmpty() const;
virtual QLayoutItem*  itemAt(int  index) const;
virtual QLayout*  layout();
virtual QSize  maximumSize() const;
virtual QSize  minimumSize() const;
virtual void setGeometry(const QRect&  rect);
virtual QLayoutItem*  takeAt(int  index);
virtual void timerEvent(QTimerEvent*  arg__1);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_FlowLayout : public FlowLayout
{ public:
inline void promoted_addItem(QLayoutItem*  item) { FlowLayout::addItem(item); }
inline int  promoted_count() const { return FlowLayout::count(); }
inline Qt::Orientations  promoted_expandingDirections() const { return FlowLayout::expandingDirections(); }
inline QLayoutItem*  promoted_itemAt(int  index) const { return FlowLayout::itemAt(index); }
inline QSize  promoted_minimumSize() const { return FlowLayout::minimumSize(); }
inline void promoted_setGeometry(const QRect&  rect) { FlowLayout::setGeometry(rect); }
inline QLayoutItem*  promoted_takeAt(int  index) { return FlowLayout::takeAt(index); }
};

class PythonQtWrapper_FlowLayout : public QObject
{ Q_OBJECT
public:
public slots:
FlowLayout* new_FlowLayout(QWidget*  parent, int  margin = -1, int  hSpacing = -1, int  vSpacing = -1);
FlowLayout* new_FlowLayout(int  margin = -1, int  hSpacing = -1, int  vSpacing = -1);
void delete_FlowLayout(FlowLayout* obj) { delete obj; } 
   void addItem(FlowLayout* theWrappedObject, QLayoutItem*  item);
   int  count(FlowLayout* theWrappedObject) const;
   Qt::Orientations  expandingDirections(FlowLayout* theWrappedObject) const;
   bool  hasHeightForWidth(FlowLayout* theWrappedObject) const;
   int  heightForWidth(FlowLayout* theWrappedObject, int  arg__1) const;
   int  horizontalSpacing(FlowLayout* theWrappedObject) const;
   QLayoutItem*  itemAt(FlowLayout* theWrappedObject, int  index) const;
   QSize  minimumSize(FlowLayout* theWrappedObject) const;
   void setGeometry(FlowLayout* theWrappedObject, const QRect&  rect);
   QSize  sizeHint(FlowLayout* theWrappedObject) const;
   QLayoutItem*  takeAt(FlowLayout* theWrappedObject, int  index);
   int  verticalSpacing(FlowLayout* theWrappedObject) const;
};





class PythonQtShell_InstanceManager : public InstanceManager
{
public:
    PythonQtShell_InstanceManager(QObject*  parent = 0):InstanceManager(parent),_wrapper(NULL) {};

   ~PythonQtShell_InstanceManager();

virtual void childEvent(QChildEvent*  arg__1);
virtual void customEvent(QEvent*  arg__1);
virtual bool  event(QEvent*  arg__1);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual void timerEvent(QTimerEvent*  arg__1);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_InstanceManager : public InstanceManager
{ public:
static inline void promoted_addPropertyChangeListener(PropertyChangeListener*  l) { InstanceManager::addPropertyChangeListener(l); }
inline void promoted_addReporterManager(ReporterManager*  p) { InstanceManager::addReporterManager(p); }
inline void promoted_addSensorManager(SensorManager*  p) { InstanceManager::addSensorManager(p); }
inline void promoted_addShutdownManager(ShutDownManager*  p) { InstanceManager::addShutdownManager(p); }
inline void promoted_addSignalHeadManager(SignalHeadManager*  p) { InstanceManager::addSignalHeadManager(p); }
inline void promoted_init() { InstanceManager::init(); }
inline void promoted_notifyPropertyChangeListener(QString  property, QVariant  oldValue, QVariant  newValue) { InstanceManager::notifyPropertyChangeListener(property, oldValue, newValue); }
};

class PythonQtWrapper_InstanceManager : public QObject
{ Q_OBJECT
public:
public slots:
InstanceManager* new_InstanceManager(QObject*  parent = 0);
void delete_InstanceManager(InstanceManager* obj) { delete obj; } 
   void static_InstanceManager_addPropertyChangeListener(PropertyChangeListener*  l);
   void addReporterManager(InstanceManager* theWrappedObject, ReporterManager*  p);
   void addSensorManager(InstanceManager* theWrappedObject, SensorManager*  p);
   void addShutdownManager(InstanceManager* theWrappedObject, ShutDownManager*  p);
   void addSignalHeadManager(InstanceManager* theWrappedObject, SignalHeadManager*  p);
   AudioManager*  static_InstanceManager_audioManagerInstance();
   CommandStation*  static_InstanceManager_commandStationInstance();
   QString  static_InstanceManager_contentsToString();
   void static_InstanceManager_deregister(QObject*  item, QString  type);
   QObject*  static_InstanceManager_getDefault(QString  type);
   QList<QObject* >*  static_InstanceManager_getList(QString  type);
   void init(InstanceManager* theWrappedObject);
   InstanceManager*  static_InstanceManager_instance();
   LayoutBlockManager*  static_InstanceManager_layoutBlockManagerInstance();
   MemoryManager*  static_InstanceManager_memoryManagerInstance();
   void notifyPropertyChangeListener(InstanceManager* theWrappedObject, QString  property, QVariant  oldValue, QVariant  newValue);
   PowerManager*  static_InstanceManager_powerManagerInstance();
   ProgrammerManager*  static_InstanceManager_programmerManagerInstance();
   void static_InstanceManager_removePropertyChangeListener(PropertyChangeListener*  l);
   ReporterManager*  static_InstanceManager_reporterManagerInstance();
   void static_InstanceManager_reset(QString  type);
   RouteManager*  static_InstanceManager_routeManagerInstance();
   SensorManager*  static_InstanceManager_sensorManagerInstance();
   void static_InstanceManager_setCommandStation(CommandStation*  p);
   void static_InstanceManager_setDefault(QString  type, QObject*  val);
   void static_InstanceManager_setLayoutBlockManager(LayoutBlockManager*  p);
   void static_InstanceManager_setPowerManager(PowerManager*  p);
   void static_InstanceManager_setProgrammerManager(ProgrammerManager*  p);
   void static_InstanceManager_setReporterManager(ReporterManager*  p);
   void static_InstanceManager_setSensorManager(SensorManager*  p);
   void static_InstanceManager_setShutDownManager(ShutDownManager*  p);
   void static_InstanceManager_setSignalHeadManager(SignalHeadManager*  p);
   void static_InstanceManager_setSignalMastManager(SignalMastManager*  p);
   ShutDownManager*  static_InstanceManager_shutDownManagerInstance();
   SignalHeadManager*  static_InstanceManager_signalHeadManagerInstance();
   SignalMastManager*  static_InstanceManager_signalMastManagerInstance();
   void static_InstanceManager_store(QObject*  item, QString  type);
};





class PythonQtShell_JFrame : public JFrame
{
public:
    PythonQtShell_JFrame(QString  _title, QWidget*  parent = 0):JFrame(_title, parent),_wrapper(NULL) {};
    PythonQtShell_JFrame(QWidget*  parent = 0):JFrame(parent),_wrapper(NULL) {};
    PythonQtShell_JFrame(const JFrame&  arg__1):JFrame(arg__1),_wrapper(NULL) {};

   ~PythonQtShell_JFrame();

virtual void actionEvent(QActionEvent*  arg__1);
virtual void changeEvent(QEvent*  arg__1);
virtual void childEvent(QChildEvent*  arg__1);
virtual void contextMenuEvent(QContextMenuEvent*  event);
virtual QMenu*  createPopupMenu();
virtual void customEvent(QEvent*  arg__1);
virtual int  devType() const;
virtual void dragEnterEvent(QDragEnterEvent*  arg__1);
virtual void dragLeaveEvent(QDragLeaveEvent*  arg__1);
virtual void dragMoveEvent(QDragMoveEvent*  arg__1);
virtual void dropEvent(QDropEvent*  arg__1);
virtual void enterEvent(QEvent*  arg__1);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual void focusInEvent(QFocusEvent*  arg__1);
virtual bool  focusNextPrevChild(bool  next);
virtual void focusOutEvent(QFocusEvent*  arg__1);
virtual QString  getTitle();
virtual void handleModified();
virtual int  heightForWidth(int  arg__1) const;
virtual void hideEvent(QHideEvent*  arg__1);
virtual void inputMethodEvent(QInputMethodEvent*  arg__1);
virtual QVariant  inputMethodQuery(Qt::InputMethodQuery  arg__1) const;
virtual void keyPressEvent(QKeyEvent*  arg__1);
virtual void keyReleaseEvent(QKeyEvent*  arg__1);
virtual void languageChange();
virtual void leaveEvent(QEvent*  arg__1);
virtual int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
virtual QSize  minimumSizeHint() const;
virtual void mouseDoubleClickEvent(QMouseEvent*  arg__1);
virtual void mouseMoveEvent(QMouseEvent*  arg__1);
virtual void mousePressEvent(QMouseEvent*  arg__1);
virtual void mouseReleaseEvent(QMouseEvent*  arg__1);
virtual void moveEvent(QMoveEvent*  arg__1);
virtual QPaintEngine*  paintEngine() const;
virtual void paintEvent(QPaintEvent*  arg__1);
virtual void resizeEvent(QResizeEvent*  arg__1);
virtual void showEvent(QShowEvent*  arg__1);
virtual QSize  sizeHint() const;
virtual void tabletEvent(QTabletEvent*  arg__1);
virtual void timerEvent(QTimerEvent*  arg__1);
virtual void wheelEvent(QWheelEvent*  arg__1);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_JFrame : public JFrame
{ public:
inline void promoted_frameInit() { JFrame::frameInit(); }
inline QString  promoted_getTitle() { return JFrame::getTitle(); }
inline void promoted_handleModified() { JFrame::handleModified(); }
};

class PythonQtWrapper_JFrame : public QObject
{ Q_OBJECT
public:
public slots:
JFrame* new_JFrame(QString  _title, QWidget*  parent = 0);
JFrame* new_JFrame(QWidget*  parent = 0);
JFrame* new_JFrame(const JFrame&  arg__1);
void delete_JFrame(JFrame* obj) { delete obj; } 
   void addWindowListener(JFrame* theWrappedObject, WindowListener*  l);
   void dispose(JFrame* theWrappedObject);
   void frameInit(JFrame* theWrappedObject);
   QWidget*  getContentPane(JFrame* theWrappedObject);
   QPoint  getLocationOnScreen(JFrame* theWrappedObject);
   QSize  getMaximumSize(JFrame* theWrappedObject);
   QSize  getPreferredSize(JFrame* theWrappedObject);
   QString  getTitle(JFrame* theWrappedObject);
   QWidget*  getTopLevelAncestor(JFrame* theWrappedObject);
   void handleModified(JFrame* theWrappedObject);
   void setAlwaysOnTop(JFrame* theWrappedObject, bool  checked);
   void setDefaultCloseOperation(JFrame* theWrappedObject, int  operation);
   void setLocation(JFrame* theWrappedObject, QPoint  p);
   void setLocation(JFrame* theWrappedObject, int  x, int  y);
   void setMenuBar(JFrame* theWrappedObject, QMenuBar*  menubar);
   void setTitle(JFrame* theWrappedObject, QString  _title);
   QString  title(JFrame* theWrappedObject);
   void toFront(JFrame* theWrappedObject);
   void windowClosing(JFrame* theWrappedObject, QCloseEvent*  e);
};





class PythonQtShell_JmriJFrame : public JmriJFrame
{
public:
    PythonQtShell_JmriJFrame(QString  name, QWidget*  parent = 0):JmriJFrame(name, parent),_wrapper(NULL) {};
    PythonQtShell_JmriJFrame(QString  name, bool  saveSize, bool  savePosition, QWidget*  parent = 0):JmriJFrame(name, saveSize, savePosition, parent),_wrapper(NULL) {};
    PythonQtShell_JmriJFrame(QWidget*  parent = 0):JmriJFrame(parent),_wrapper(NULL) {};
    PythonQtShell_JmriJFrame(bool  saveSize, bool  savePosition, QWidget*  parent = 0):JmriJFrame(saveSize, savePosition, parent),_wrapper(NULL) {};

   ~PythonQtShell_JmriJFrame();

virtual void actionEvent(QActionEvent*  arg__1);
virtual void addHelpMenu(QString  ref, bool  direct);
virtual void changeEvent(QEvent*  arg__1);
virtual void childEvent(QChildEvent*  arg__1);
virtual void contextMenuEvent(QContextMenuEvent*  event);
virtual QMenu*  createPopupMenu();
virtual void customEvent(QEvent*  arg__1);
virtual int  devType() const;
virtual void dragEnterEvent(QDragEnterEvent*  arg__1);
virtual void dragLeaveEvent(QDragLeaveEvent*  arg__1);
virtual void dragMoveEvent(QDragMoveEvent*  arg__1);
virtual void dropEvent(QDropEvent*  arg__1);
virtual void enterEvent(QEvent*  arg__1);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual void focusInEvent(QFocusEvent*  arg__1);
virtual bool  focusNextPrevChild(bool  next);
virtual void focusOutEvent(QFocusEvent*  arg__1);
virtual QString  getTitle();
virtual void handleModified();
virtual int  heightForWidth(int  arg__1) const;
virtual void hideEvent(QHideEvent*  arg__1);
virtual void initComponents();
virtual void inputMethodEvent(QInputMethodEvent*  arg__1);
virtual QVariant  inputMethodQuery(Qt::InputMethodQuery  arg__1) const;
virtual void keyPressEvent(QKeyEvent*  arg__1);
virtual void keyReleaseEvent(QKeyEvent*  arg__1);
virtual void languageChange();
virtual void leaveEvent(QEvent*  arg__1);
virtual int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
virtual QSize  minimumSizeHint() const;
virtual void mouseDoubleClickEvent(QMouseEvent*  arg__1);
virtual void mouseMoveEvent(QMouseEvent*  arg__1);
virtual void mousePressEvent(QMouseEvent*  arg__1);
virtual void mouseReleaseEvent(QMouseEvent*  arg__1);
virtual void moveEvent(QMoveEvent*  e);
virtual QPaintEngine*  paintEngine() const;
virtual void paintEvent(QPaintEvent*  arg__1);
virtual void resizeEvent(QResizeEvent*  e);
virtual void showEvent(QShowEvent*  arg__1);
virtual QSize  sizeHint() const;
virtual void storeValues();
virtual void tabletEvent(QTabletEvent*  arg__1);
virtual void timerEvent(QTimerEvent*  arg__1);
virtual void wheelEvent(QWheelEvent*  arg__1);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_JmriJFrame : public JmriJFrame
{ public:
inline void promoted_addHelpMenu(QString  ref, bool  direct) { JmriJFrame::addHelpMenu(ref, direct); }
inline QString  promoted_getTitle() { return JmriJFrame::getTitle(); }
inline void promoted_handleModified() { JmriJFrame::handleModified(); }
inline void promoted_initComponents() { JmriJFrame::initComponents(); }
inline void promoted_moveEvent(QMoveEvent*  e) { JmriJFrame::moveEvent(e); }
inline void promoted_resizeEvent(QResizeEvent*  e) { JmriJFrame::resizeEvent(e); }
inline void promoted_setShutDownTask() { JmriJFrame::setShutDownTask(); }
inline void promoted_storeValues() { JmriJFrame::storeValues(); }
};

class PythonQtWrapper_JmriJFrame : public QObject
{ Q_OBJECT
public:
public slots:
JmriJFrame* new_JmriJFrame(QString  name, QWidget*  parent = 0);
JmriJFrame* new_JmriJFrame(QString  name, bool  saveSize, bool  savePosition, QWidget*  parent = 0);
JmriJFrame* new_JmriJFrame(QWidget*  parent = 0);
JmriJFrame* new_JmriJFrame(bool  saveSize, bool  savePosition, QWidget*  parent = 0);
void delete_JmriJFrame(JmriJFrame* obj) { delete obj; } 
   void addHelpMenu(JmriJFrame* theWrappedObject, QString  ref, bool  direct);
   void dispose(JmriJFrame* theWrappedObject);
   void generateWindowRef(JmriJFrame* theWrappedObject);
   QWidget*  getContentPane(JmriJFrame* theWrappedObject);
   QList<JmriJFrame* >*  static_JmriJFrame_getFrameList();
   bool  getModifiedFlag(JmriJFrame* theWrappedObject);
   QString  getName(JmriJFrame* theWrappedObject);
   QString  getTitle(JmriJFrame* theWrappedObject);
   QString  getWindowFrameRef(JmriJFrame* theWrappedObject);
   void handleModified(JmriJFrame* theWrappedObject);
   void init(JmriJFrame* theWrappedObject);
   void initComponents(JmriJFrame* theWrappedObject);
   void markWindowModified(JmriJFrame* theWrappedObject, bool  yes);
   void moveEvent(JmriJFrame* theWrappedObject, QMoveEvent*  e);
   void resizeEvent(JmriJFrame* theWrappedObject, QResizeEvent*  e);
   void setAlwaysOnTop(JmriJFrame* theWrappedObject, bool  checked);
   void setLocation(JmriJFrame* theWrappedObject, int  x, int  y);
   void setModifiedFlag(JmriJFrame* theWrappedObject, bool  flag);
   void setName(JmriJFrame* theWrappedObject, QString  name);
   void setShutDownTask(JmriJFrame* theWrappedObject);
   void setTitle(JmriJFrame* theWrappedObject, QString  _title);
   void setWindowTitle(JmriJFrame* theWrappedObject, const QString&  title);
   void storeValues(JmriJFrame* theWrappedObject);
};





class PythonQtShell_LayoutBlockManager : public LayoutBlockManager
{
public:
    PythonQtShell_LayoutBlockManager(QObject*  parent = 0):LayoutBlockManager(parent),_wrapper(NULL) {};
    PythonQtShell_LayoutBlockManager(const LayoutBlockManager&  arg__1):LayoutBlockManager(arg__1),_wrapper(NULL) {};

   ~PythonQtShell_LayoutBlockManager();

virtual void Register(NamedBean*  s);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void childEvent(QChildEvent*  arg__1);
virtual void customEvent(QEvent*  arg__1);
virtual void deregister(NamedBean*  s);
virtual void dispose();
virtual bool  event(QEvent*  arg__1);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual NamedBean*  getBeanBySystemName(QString  systemName);
virtual NamedBean*  getBeanByUserName(QString  userName);
virtual NamedBean*  getNamedBean(QString  name);
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList();
virtual QString  getSystemPrefix();
virtual int  getXMLOrder();
virtual QString  makeSystemName(QString  s);
virtual void on_propertyChange(PropertyChangeEvent*  e);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void timerEvent(QTimerEvent*  arg__1);
virtual char  typeLetter();

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_LayoutBlockManager : public LayoutBlockManager
{ public:
inline QString  promoted_getSystemPrefix() { return LayoutBlockManager::getSystemPrefix(); }
inline int  promoted_getXMLOrder() { return LayoutBlockManager::getXMLOrder(); }
inline char  promoted_typeLetter() { return LayoutBlockManager::typeLetter(); }
};

class PythonQtWrapper_LayoutBlockManager : public QObject
{ Q_OBJECT
public:
public slots:
LayoutBlockManager* new_LayoutBlockManager(QObject*  parent = 0);
LayoutBlockManager* new_LayoutBlockManager(const LayoutBlockManager&  arg__1);
void delete_LayoutBlockManager(LayoutBlockManager* obj) { delete obj; } 
   void addBadBeanError(LayoutBlockManager* theWrappedObject);
   void enableAdvancedRouting(LayoutBlockManager* theWrappedObject, bool  boo);
   QCompleter*  getCompleter(LayoutBlockManager* theWrappedObject, QString  text, bool  bIncludeUserNames = false);
   long  getLastRoutingChange(LayoutBlockManager* theWrappedObject);
   Sensor*  getStabilisedSensor(LayoutBlockManager* theWrappedObject);
   QString  getSystemPrefix(LayoutBlockManager* theWrappedObject);
   int  getXMLOrder(LayoutBlockManager* theWrappedObject);
   void initializeLayoutBlockPaths(LayoutBlockManager* theWrappedObject);
   LayoutBlockManager*  static_LayoutBlockManager_instance();
   bool  isAdvancedRoutingEnabled(LayoutBlockManager* theWrappedObject);
   bool  routingStablised(LayoutBlockManager* theWrappedObject);
   void setLastRoutingChange(LayoutBlockManager* theWrappedObject);
   void setStabilisedSensor(LayoutBlockManager* theWrappedObject, QString  pName) throw (JmriException);
   void turnOffWarning(LayoutBlockManager* theWrappedObject);
   char  typeLetter(LayoutBlockManager* theWrappedObject);
   bool  warn(LayoutBlockManager* theWrappedObject);
};





class PythonQtShell_Light : public Light
{
public:
    PythonQtShell_Light(QObject*  parent = 0):Light(parent),_wrapper(NULL) {};
    PythonQtShell_Light(QString  sysName, QObject*  parent = 0):Light(sysName, parent),_wrapper(NULL) {};
    PythonQtShell_Light(QString  sysName, QString  userName, QObject*  parent = 0):Light(sysName, userName, parent),_wrapper(NULL) {};

   ~PythonQtShell_Light();

virtual void activateLight();
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(PropertyChangeListener*  l, QString  beanRef, const QString  listenerRef);
virtual void childEvent(QChildEvent*  arg__1);
virtual void clearLightControls();
virtual void customEvent(QEvent*  arg__1);
virtual void deactivateLight();
virtual void dispose();
virtual bool  event(QEvent*  arg__1);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual QString  getComment();
virtual double  getCurrentIntensity();
virtual QString  getDisplayName();
virtual bool  getEnabled();
virtual QString  getListenerRef(PropertyChangeListener*  l);
virtual QList<QString >*  getListenerRefs();
virtual double  getMaxIntensity();
virtual double  getMinIntensity();
virtual int  getNumPropertyChangeListeners();
virtual QVariant  getProperty(QString  key);
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners();
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners(QString  name);
virtual QList<QString >  getPropertyKeys();
virtual int  getState();
virtual QString  getSystemName() const;
virtual double  getTargetIntensity();
virtual double  getTransitionTime();
virtual QString  getUserName();
virtual bool  hashCode();
virtual bool  isIntensityVariable();
virtual bool  isTransitionAvailable();
virtual bool  isTransitioning();
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void setComment(QString  comment);
virtual void setEnabled(bool  state);
virtual void setMaxIntensity(double  intensity);
virtual void setMinIntensity(double  intensity);
virtual void setProperty(QString  key, QVariant  value);
virtual void setState(int  newState);
virtual void setTargetIntensity(double  intensity);
virtual void setTransitionTime(double  minutes);
virtual void setUserName(QString  s);
virtual void timerEvent(QTimerEvent*  arg__1);
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_Light : public Light
{ public:
inline void promoted_activateLight() { this->activateLight(); }
inline void promoted_clearLightControls() { this->clearLightControls(); }
inline void promoted_deactivateLight() { this->deactivateLight(); }
inline double  promoted_getCurrentIntensity() { return this->getCurrentIntensity(); }
inline bool  promoted_getEnabled() { return this->getEnabled(); }
inline double  promoted_getMaxIntensity() { return this->getMaxIntensity(); }
inline double  promoted_getMinIntensity() { return this->getMinIntensity(); }
inline int  promoted_getState() { return this->getState(); }
inline double  promoted_getTargetIntensity() { return this->getTargetIntensity(); }
inline double  promoted_getTransitionTime() { return this->getTransitionTime(); }
inline bool  promoted_isIntensityVariable() { return this->isIntensityVariable(); }
inline bool  promoted_isTransitionAvailable() { return this->isTransitionAvailable(); }
inline bool  promoted_isTransitioning() { return this->isTransitioning(); }
inline void promoted_setEnabled(bool  state) { this->setEnabled(state); }
inline void promoted_setMaxIntensity(double  intensity) { this->setMaxIntensity(intensity); }
inline void promoted_setMinIntensity(double  intensity) { this->setMinIntensity(intensity); }
inline void promoted_setState(int  newState) { this->setState(newState); }
inline void promoted_setTargetIntensity(double  intensity) { this->setTargetIntensity(intensity); }
inline void promoted_setTransitionTime(double  minutes) { this->setTransitionTime(minutes); }
};

class PythonQtWrapper_Light : public QObject
{ Q_OBJECT
public:
public slots:
Light* new_Light(QObject*  parent = 0);
Light* new_Light(QString  sysName, QObject*  parent = 0);
Light* new_Light(QString  sysName, QString  userName, QObject*  parent = 0);
void delete_Light(Light* obj) { delete obj; } 
   void activateLight(Light* theWrappedObject);
   void clearLightControls(Light* theWrappedObject);
   void deactivateLight(Light* theWrappedObject);
   double  getCurrentIntensity(Light* theWrappedObject);
   bool  getEnabled(Light* theWrappedObject);
   double  getMaxIntensity(Light* theWrappedObject);
   double  getMinIntensity(Light* theWrappedObject);
   int  getState(Light* theWrappedObject);
   double  getTargetIntensity(Light* theWrappedObject);
   double  getTransitionTime(Light* theWrappedObject);
   bool  isIntensityVariable(Light* theWrappedObject);
   bool  isTransitionAvailable(Light* theWrappedObject);
   bool  isTransitioning(Light* theWrappedObject);
   void setEnabled(Light* theWrappedObject, bool  state);
   void setMaxIntensity(Light* theWrappedObject, double  intensity);
   void setMinIntensity(Light* theWrappedObject, double  intensity);
   void setState(Light* theWrappedObject, int  newState);
   void setTargetIntensity(Light* theWrappedObject, double  intensity);
   void setTransitionTime(Light* theWrappedObject, double  minutes);
};





class PythonQtShell_LnPacketizer : public LnPacketizer
{
public:
    PythonQtShell_LnPacketizer(QObject*  parent = 0):LnPacketizer(parent),_wrapper(NULL) {};

   ~PythonQtShell_LnPacketizer();

virtual void childEvent(QChildEvent*  arg__1);
virtual void customEvent(QEvent*  arg__1);
virtual bool  event(QEvent*  arg__1);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual bool  isXmtBusy();
virtual void sendLocoNetMessage(LocoNetMessage*  m);
virtual bool  status();
virtual void timerEvent(QTimerEvent*  arg__1);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_LnPacketizer : public LnPacketizer
{ public:
inline bool  promoted_isXmtBusy() { return LnPacketizer::isXmtBusy(); }
inline void promoted_sendLocoNetMessage(LocoNetMessage*  m) { LnPacketizer::sendLocoNetMessage(m); }
inline bool  promoted_status() { return LnPacketizer::status(); }
};

class PythonQtWrapper_LnPacketizer : public QObject
{ Q_OBJECT
public:
public slots:
LnPacketizer* new_LnPacketizer(QObject*  parent = 0);
void delete_LnPacketizer(LnPacketizer* obj) { delete obj; } 
   void connectPort(LnPacketizer* theWrappedObject, LnPortController*  p);
   void disconnectPort(LnPacketizer* theWrappedObject, LnPortController*  p);
   QString  static_LnPacketizer_hexStringFromBytes(const QByteArray&  a);
   bool  isXmtBusy(LnPacketizer* theWrappedObject);
   void sendLocoNetMessage(LnPacketizer* theWrappedObject, LocoNetMessage*  m);
   void startThreads(LnPacketizer* theWrappedObject);
   bool  status(LnPacketizer* theWrappedObject);
void py_set_baStream(LnPacketizer* theWrappedObject, QByteArray*  baStream){ theWrappedObject->baStream = baStream; }
QByteArray*  py_get_baStream(LnPacketizer* theWrappedObject){ return theWrappedObject->baStream; }
void py_set_controller(LnPacketizer* theWrappedObject, LnPortController*  controller){ theWrappedObject->controller = controller; }
LnPortController*  py_get_controller(LnPacketizer* theWrappedObject){ return theWrappedObject->controller; }
void py_set_istream(LnPacketizer* theWrappedObject, QDataStream*  istream){ theWrappedObject->istream = istream; }
QDataStream*  py_get_istream(LnPacketizer* theWrappedObject){ return theWrappedObject->istream; }
void py_set_ostream(LnPacketizer* theWrappedObject, QDataStream*  ostream){ theWrappedObject->ostream = ostream; }
QDataStream*  py_get_ostream(LnPacketizer* theWrappedObject){ return theWrappedObject->ostream; }
void py_set_xmtList(LnPacketizer* theWrappedObject, QLinkedList<QByteArray* >*  xmtList){ theWrappedObject->xmtList = xmtList; }
QLinkedList<QByteArray* >*  py_get_xmtList(LnPacketizer* theWrappedObject){ return theWrappedObject->xmtList; }
};





class PythonQtWrapper_LnPortController : public QObject
{ Q_OBJECT
public:
public slots:
void delete_LnPortController(LnPortController* obj) { delete obj; } 
   QDataStream*  getInputStream(LnPortController* theWrappedObject);
   QDataStream*  getOutputStream(LnPortController* theWrappedObject);
   bool  okToSend(LnPortController* theWrappedObject);
   void setCommandStationType(LnPortController* theWrappedObject, QString  name);
   void setDisabled(LnPortController* theWrappedObject, bool  disabled);
   void setTurnoutHandling(LnPortController* theWrappedObject, QString  value);
   bool  status(LnPortController* theWrappedObject);
};





class PythonQtShell_LnSensor : public LnSensor
{
public:
    PythonQtShell_LnSensor(QString  systemName, LnTrafficController*  tc = NULL, QString  prefix = "L", QObject*  parent = 0):LnSensor(systemName, tc, prefix, parent),_wrapper(NULL) {};
    PythonQtShell_LnSensor(QString  systemName, QString  userName, LnTrafficController*  tc = NULL, QString  prefix = "L", QObject*  parent = 0):LnSensor(systemName, userName, tc, prefix, parent),_wrapper(NULL) {};

   ~PythonQtShell_LnSensor();

virtual void addPropertyChangeListener(PropertyChangeListener*  arg__1) const;
virtual void childEvent(QChildEvent*  arg__1);
virtual void customEvent(QEvent*  arg__1);
virtual void dispose();
virtual bool  event(QEvent*  arg__1);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual QString  getComment();
virtual QString  getDisplayName();
virtual bool  getInverted();
virtual int  getKnownState() const;
virtual QString  getListenerRef(PropertyChangeListener*  l);
virtual QList<QString >*  getListenerRefs();
virtual int  getNumPropertyChangeListeners();
virtual QVariant  getProperty(QString  key);
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners();
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners(QString  name);
virtual QList<QString >  getPropertyKeys();
virtual int  getRawState();
virtual long  getSensorDebounceGoingActiveTimer();
virtual long  getSensorDebounceGoingInActiveTimer();
virtual int  getState();
virtual QString  getSystemName() const;
virtual QString  getUserName();
virtual bool  hashCode();
virtual void removePropertyChangeListener(PropertyChangeListener*  arg__1) const;
virtual void requestUpdateFromLayout() const;
virtual void setComment(QString  comment);
virtual void setInverted(bool  inverted);
virtual void setKnownState(int  s);
virtual void setProperty(QString  key, QVariant  value);
virtual void setSensorDebounceGoingActiveTimer(long  time);
virtual void setSensorDebounceGoingInActiveTimer(long  time);
virtual void setState(int  s);
virtual void setUserName(QString  s);
virtual void timerEvent(QTimerEvent*  arg__1);
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);
virtual bool  useDefaultTimerSettings();
virtual void useDefaultTimerSettings(bool  boo);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_LnSensor : public LnSensor
{ public:
inline void promoted_dispose() { LnSensor::dispose(); }
inline void promoted_requestUpdateFromLayout() const { LnSensor::requestUpdateFromLayout(); }
inline void promoted_setKnownState(int  s) { LnSensor::setKnownState(s); }
};

class PythonQtWrapper_LnSensor : public QObject
{ Q_OBJECT
public:
public slots:
LnSensor* new_LnSensor(QString  systemName, LnTrafficController*  tc = NULL, QString  prefix = "L", QObject*  parent = 0);
LnSensor* new_LnSensor(QString  systemName, QString  userName, LnTrafficController*  tc = NULL, QString  prefix = "L", QObject*  parent = 0);
void delete_LnSensor(LnSensor* obj) { delete obj; } 
   void dispose(LnSensor* theWrappedObject);
   void requestUpdateFromLayout(LnSensor* theWrappedObject) const;
   void setKnownState(LnSensor* theWrappedObject, int  s);
};





class PythonQtShell_LnTrafficController : public LnTrafficController
{
public:
    PythonQtShell_LnTrafficController():LnTrafficController(),_wrapper(NULL) {};

   ~PythonQtShell_LnTrafficController();

virtual void childEvent(QChildEvent*  arg__1);
virtual void customEvent(QEvent*  arg__1);
virtual bool  event(QEvent*  arg__1);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual bool  isXmtBusy();
virtual void sendLocoNetMessage(LocoNetMessage*  arg__1);
virtual bool  status();
virtual void timerEvent(QTimerEvent*  arg__1);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_LnTrafficController : public LnTrafficController
{ public:
inline bool  promoted_isXmtBusy() { return LnTrafficController::isXmtBusy(); }
inline void promoted_sendLocoNetMessage(LocoNetMessage*  arg__1) { LnTrafficController::sendLocoNetMessage(arg__1); }
inline bool  promoted_status() { return LnTrafficController::status(); }
};

class PythonQtWrapper_LnTrafficController : public QObject
{ Q_OBJECT
public:
public slots:
LnTrafficController* new_LnTrafficController();
void delete_LnTrafficController(LnTrafficController* obj) { delete obj; } 
   int  getReceivedByteCount(LnTrafficController* theWrappedObject);
   int  getReceivedMsgCount(LnTrafficController* theWrappedObject);
   int  getTransmittedMsgCount(LnTrafficController* theWrappedObject);
   bool  isXmtBusy(LnTrafficController* theWrappedObject);
   void resetStatistics(LnTrafficController* theWrappedObject);
   void sendLocoNetMessage(LnTrafficController* theWrappedObject, LocoNetMessage*  arg__1);
   bool  status(LnTrafficController* theWrappedObject);
};





class PythonQtShell_LnTurnout : public LnTurnout
{
public:
    PythonQtShell_LnTurnout(QString  prefix, int  number, LnTrafficController*  controller, QObject*  parent = 0):LnTurnout(prefix, number, controller, parent),_wrapper(NULL) {};

   ~PythonQtShell_LnTurnout();

virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(PropertyChangeListener*  l, QString  beanRef, const QString  listenerRef);
virtual bool  canInvert();
virtual bool  canLock(int  turnoutLockout);
virtual void childEvent(QChildEvent*  arg__1);
virtual void customEvent(QEvent*  arg__1);
virtual void dispose();
virtual void enableLockOperation(int  turnoutLockout, bool  enabled);
virtual bool  event(QEvent*  arg__1);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual void forwardCommandChangeToLayout(int  newstate);
virtual int  getCommandedState();
virtual QString  getComment();
virtual int  getControlType();
virtual QString  getDecoderName();
virtual QString  getDisplayName();
virtual float  getDivergingLimit();
virtual QString  getDivergingSpeed();
virtual int  getFeedbackMode();
virtual QString  getFeedbackModeName();
virtual Sensor*  getFirstSensor();
virtual bool  getInhibitOperation();
virtual bool  getInverted();
virtual int  getKnownState();
virtual QString  getListenerRef(PropertyChangeListener*  l);
virtual QList<QString >*  getListenerRefs();
virtual bool  getLocked(int  turnoutLockout);
virtual int  getNumPropertyChangeListeners();
virtual int  getNumberOutputBits();
virtual QVariant  getProperty(QString  key);
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners();
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners(QString  name);
virtual QList<QString >  getPropertyKeys();
virtual bool  getReportLocked();
virtual Sensor*  getSecondSensor();
virtual int  getState();
virtual float  getStraightLimit();
virtual QString  getStraightSpeed();
virtual QString  getSystemName() const;
virtual QString  getUserName();
virtual QStringList  getValidDecoderNames();
virtual QStringList  getValidFeedbackNames();
virtual int  getValidFeedbackTypes();
virtual bool  hashCode();
virtual bool  isConsistentState();
virtual void provideFirstFeedbackSensor(QString  pName) throw(JmriException);
virtual void provideSecondFeedbackSensor(QString  pName) throw(JmriException);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void setBinaryOutput(bool  state);
virtual void setCommandedState(int  s);
virtual void setComment(QString  comment);
virtual void setControlType(int  num);
virtual void setDecoderName(QString  decoderName);
virtual void setDivergingSpeed(QString  s) throw(JmriException);
virtual void setFeedbackMode(QString  mode) throw(IllegalArgumentException);
virtual void setFeedbackMode(int  mode) throw(IllegalArgumentException);
virtual void setInhibitOperation(bool  io);
virtual void setInitialKnownStateFromFeedback();
virtual void setInverted(bool  inverted);
virtual void setLocked(int  turnoutLockout, bool  locked);
virtual void setNumberOutputBits(int  num);
virtual void setProperty(QString  key, QVariant  value);
virtual void setReportLocked(bool  reportLocked);
virtual void setState(int  s);
virtual void setStraightSpeed(QString  s) throw(JmriException);
virtual void setUserName(QString  s);
virtual void timerEvent(QTimerEvent*  arg__1);
virtual void turnoutPushbuttonLockout(bool  _pushButtonLockout);
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_LnTurnout : public LnTurnout
{ public:
inline bool  promoted_canInvert() { return LnTurnout::canInvert(); }
inline void promoted_dispose() { LnTurnout::dispose(); }
inline void promoted_forwardCommandChangeToLayout(int  newstate) { LnTurnout::forwardCommandChangeToLayout(newstate); }
inline void promoted_turnoutPushbuttonLockout(bool  _pushButtonLockout) { LnTurnout::turnoutPushbuttonLockout(_pushButtonLockout); }
};

class PythonQtWrapper_LnTurnout : public QObject
{ Q_OBJECT
public:
public slots:
LnTurnout* new_LnTurnout(QString  prefix, int  number, LnTrafficController*  controller, QObject*  parent = 0);
void delete_LnTurnout(LnTurnout* obj) { delete obj; } 
   bool  canInvert(LnTurnout* theWrappedObject);
   void dispose(LnTurnout* theWrappedObject);
   void forwardCommandChangeToLayout(LnTurnout* theWrappedObject, int  newstate);
   int  getNumber(LnTurnout* theWrappedObject);
   void sendOpcSwReqMessage(LnTurnout* theWrappedObject, int  state, bool  on);
   void sendSetOffMessage(LnTurnout* theWrappedObject, int  state);
   void turnoutPushbuttonLockout(LnTurnout* theWrappedObject, bool  _pushButtonLockout);
};


