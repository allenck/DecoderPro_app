#include <PythonQt.h>
#include <QObject>
#include <QVariant>
#include <abstractautomaton.h>
#include <abstractlightmanager.h>
#include <abstractmanager.h>
#include <abstractnamedbean.h>
#include <abstractportcontroller.h>
#include <abstractpowermanager.h>
#include <abstractreportermanager.h>
#include <abstractsensor.h>
#include <abstractsensormanager.h>
#include <abstractserialportcontroller.h>
#include <abstractshutdowntask.h>
#include <abstractturnout.h>
#include <abstractturnoutmanager.h>
#include <audio.h>
#include <audiobuffer.h>
#include <audiolistener.h>
#include <audiomanager.h>
#include <audiosource.h>
#include <basicrosterentry.h>
#include <beaninterface.h>
#include <beantabledatamodel.h>
#include <beantableframe.h>
#include <beantablemodel.h>
#include <block.h>
#include <blockmanager.h>
#include <commandstation.h>
#include <controlpaneleditor.h>
#include <dcclocoaddress.h>
#include <dccthrottle.h>
#include <defaultlogixmanager.h>
#include <editor.h>
#include <editscene.h>
#include <jframe.h>
#include <jmrijframe.h>
#include <jtable.h>
#include <light.h>
#include <locoaddress.h>
#include <manager.h>
#include <namedbean.h>
#include <positionable.h>
#include <positionablelabel.h>
#include <propertychangeevent.h>
#include <propertychangelistener.h>
#include <qabstractitemmodel.h>
#include <qaction.h>
#include <qbytearray.h>
#include <qcolor.h>
#include <qcompleter.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qdatastream.h>
#include <qdom.h>
#include <qevent.h>
#include <qfont.h>
#include <qfontinfo.h>
#include <qfontmetrics.h>
#include <qgraphicsproxywidget.h>
#include <qgraphicsscene.h>
#include <qgraphicssceneevent.h>
#include <qicon.h>
#include <qkeysequence.h>
#include <qlayout.h>
#include <qlocale.h>
#include <qmainwindow.h>
#include <qmargins.h>
#include <qmenu.h>
#include <qmetaobject.h>
#include <qobject.h>
#include <qpaintdevice.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qpushbutton.h>
#include <qqueue.h>
#include <qrect.h>
#include <qregion.h>
#include <qscrollarea.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstatusbar.h>
#include <qstringlist.h>
#include <qstyle.h>
#include <qvector.h>
#include <qvector3d.h>
#include <qwidget.h>
#include <rosterentry.h>
#include <sensor.h>
#include <systemconnectionmemo.h>
#include <turnout.h>
#include <turnoutoperation.h>
#include <windowlistener.h>



class PythonQtShell_AbstractAutomaton : public AbstractAutomaton
{
public:
    PythonQtShell_AbstractAutomaton(QObject*  parent = 0):AbstractAutomaton(parent),_wrapper(NULL) {}
    PythonQtShell_AbstractAutomaton(QString  name, QObject*  parent = 0):AbstractAutomaton(name, parent),_wrapper(NULL) {}

   ~PythonQtShell_AbstractAutomaton();

virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual bool  handle();
virtual void init();
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_AbstractAutomaton : public AbstractAutomaton
{ public:
inline bool  promoted_handle() { return this->handle(); }
inline void promoted_wait(int  milliseconds) { this->wait(milliseconds); }
inline bool  py_q_handle() { return AbstractAutomaton::handle(); }
inline void py_q_init() { AbstractAutomaton::init(); }
};

class PythonQtWrapper_AbstractAutomaton : public QObject
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
   DccThrottle*  getThrottle(AbstractAutomaton* theWrappedObject, BasicRosterEntry*  re);
   DccThrottle*  getThrottle(AbstractAutomaton* theWrappedObject, int  address, bool  longAddress);
   bool  handle(AbstractAutomaton* theWrappedObject);
   bool  py_q_handle(AbstractAutomaton* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractAutomaton*)theWrappedObject)->py_q_handle());}
   void py_q_init(AbstractAutomaton* theWrappedObject){  (((PythonQtPublicPromoter_AbstractAutomaton*)theWrappedObject)->py_q_init());}
   void notifyAll(AbstractAutomaton* theWrappedObject);
   void notifyFailedThrottleRequest(AbstractAutomaton* theWrappedObject, DccLocoAddress*  address, QString  reason);
   void notifyThrottleFound(AbstractAutomaton* theWrappedObject, DccThrottle*  t);
   int  readServiceModeCV(AbstractAutomaton* theWrappedObject, QString  CV);
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
   bool  writeOpsModeCV(AbstractAutomaton* theWrappedObject, QString  CV, int  value, bool  longAddress, int  loco);
   bool  writeServiceModeCV(AbstractAutomaton* theWrappedObject, QString  CV, int  value);
};





class PythonQtShell_AbstractLightManager : public AbstractLightManager
{
public:
    PythonQtShell_AbstractLightManager(SystemConnectionMemo*  memo, QObject*  parent = 0):AbstractLightManager(memo, parent),_wrapper(NULL) {}

   ~PythonQtShell_AbstractLightManager();

virtual void Register(NamedBean*  s) const;
virtual void activateAllLights();
virtual void addDataListener(QObject*  e);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual bool  allowMultipleAdditions(QString  systemName);
virtual void childEvent(QChildEvent*  event);
virtual QString  convertSystemNameToAlternate(QString  systemName);
virtual Light*  createNewLight(QString  arg__1, QString  arg__2);
virtual void customEvent(QEvent*  event);
virtual void deleteBean(NamedBean*  arg__1, QString  arg__2) throw (PropertyVetoException) ;
virtual void deregister(NamedBean*  s) const;
virtual void dispose();
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual NamedBean*  getBeanBySystemName(QString  systemName) const;
virtual NamedBean*  getBeanByUserName(QString  arg__1) const;
virtual QString  getBeanTypeHandled(bool  plural) const;
virtual Light*  getBySystemName(QString  name) const;
virtual Light*  getByUserName(QString  key) const;
virtual QString  getEntryToolTip();
virtual Light*  getLight(QString  name);
virtual SystemConnectionMemo*  getMemo() const;
virtual NamedBean*  getNamedBean(QString  name) const;
virtual QString  getNamedBeanClass() const;
virtual QSet<NamedBean* >  getNamedBeanSet();
virtual int  getObjectCount();
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners();
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners(QString  propertyName);
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList();
virtual QString  getSystemPrefix() const;
virtual int  getXMLOrder() const;
virtual QString  makeSystemName(QString  s, bool  logErrors = true, QLocale  locale = QLocale()) const;
virtual Light*  newLight(QString  systemName, QString  userName);
virtual QString  normalizeSystemName(QString  systemName);
virtual void propertyChange(PropertyChangeEvent*  e);
virtual Light*  provide(QString  name) throw (IllegalArgumentException)
;
virtual Light*  provideLight(QString  name);
virtual void removeDataListener(QObject*  e);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void removePropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual bool  supportsVariableLights(QString  systemName);
virtual void timerEvent(QTimerEvent*  event);
virtual QString  toString();
virtual char  typeLetter() const;
virtual bool  validSystemNameConfig(QString  arg__1) const;
virtual Manager::NameValidity  validSystemNameFormat(QString  systemName) const;
virtual void vetoableChange(PropertyChangeEvent*  evt);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_AbstractLightManager : public AbstractLightManager
{ public:
inline Light*  promoted_createNewLight(QString  arg__1, QString  arg__2) { return this->createNewLight(arg__1, arg__2); }
inline void py_q_activateAllLights() { AbstractLightManager::activateAllLights(); }
inline bool  py_q_allowMultipleAdditions(QString  systemName) { return AbstractLightManager::allowMultipleAdditions(systemName); }
inline QString  py_q_convertSystemNameToAlternate(QString  systemName) { return AbstractLightManager::convertSystemNameToAlternate(systemName); }
inline Light*  py_q_createNewLight(QString  arg__1, QString  arg__2) { return AbstractLightManager::createNewLight(arg__1, arg__2); }
inline QString  py_q_getBeanTypeHandled(bool  plural) const { return AbstractLightManager::getBeanTypeHandled(plural); }
inline Light*  py_q_getBySystemName(QString  name) const { return AbstractLightManager::getBySystemName(name); }
inline Light*  py_q_getByUserName(QString  key) const { return AbstractLightManager::getByUserName(key); }
inline QString  py_q_getEntryToolTip() { return AbstractLightManager::getEntryToolTip(); }
inline Light*  py_q_getLight(QString  name) { return AbstractLightManager::getLight(name); }
inline int  py_q_getXMLOrder() const { return AbstractLightManager::getXMLOrder(); }
inline Light*  py_q_newLight(QString  systemName, QString  userName) { return AbstractLightManager::newLight(systemName, userName); }
inline QString  py_q_normalizeSystemName(QString  systemName) { return AbstractLightManager::normalizeSystemName(systemName); }
inline Light*  py_q_provideLight(QString  name) { return AbstractLightManager::provideLight(name); }
inline bool  py_q_supportsVariableLights(QString  systemName) { return AbstractLightManager::supportsVariableLights(systemName); }
inline char  py_q_typeLetter() const { return AbstractLightManager::typeLetter(); }
};

class PythonQtWrapper_AbstractLightManager : public QObject
{ Q_OBJECT
public:
public slots:
AbstractLightManager* new_AbstractLightManager(SystemConnectionMemo*  memo, QObject*  parent = 0);
void delete_AbstractLightManager(AbstractLightManager* obj) { delete obj; } 
   void py_q_activateAllLights(AbstractLightManager* theWrappedObject){  (((PythonQtPublicPromoter_AbstractLightManager*)theWrappedObject)->py_q_activateAllLights());}
   bool  py_q_allowMultipleAdditions(AbstractLightManager* theWrappedObject, QString  systemName){  return (((PythonQtPublicPromoter_AbstractLightManager*)theWrappedObject)->py_q_allowMultipleAdditions(systemName));}
   QString  py_q_convertSystemNameToAlternate(AbstractLightManager* theWrappedObject, QString  systemName){  return (((PythonQtPublicPromoter_AbstractLightManager*)theWrappedObject)->py_q_convertSystemNameToAlternate(systemName));}
   Light*  createNewLight(AbstractLightManager* theWrappedObject, QString  arg__1, QString  arg__2);
   Light*  py_q_createNewLight(AbstractLightManager* theWrappedObject, QString  arg__1, QString  arg__2){  return (((PythonQtPublicPromoter_AbstractLightManager*)theWrappedObject)->py_q_createNewLight(arg__1, arg__2));}
   QString  py_q_getBeanTypeHandled(AbstractLightManager* theWrappedObject, bool  plural) const{  return (((PythonQtPublicPromoter_AbstractLightManager*)theWrappedObject)->py_q_getBeanTypeHandled(plural));}
   Light*  py_q_getBySystemName(AbstractLightManager* theWrappedObject, QString  name) const{  return (((PythonQtPublicPromoter_AbstractLightManager*)theWrappedObject)->py_q_getBySystemName(name));}
   Light*  py_q_getByUserName(AbstractLightManager* theWrappedObject, QString  key) const{  return (((PythonQtPublicPromoter_AbstractLightManager*)theWrappedObject)->py_q_getByUserName(key));}
   QString  py_q_getEntryToolTip(AbstractLightManager* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractLightManager*)theWrappedObject)->py_q_getEntryToolTip());}
   Light*  py_q_getLight(AbstractLightManager* theWrappedObject, QString  name){  return (((PythonQtPublicPromoter_AbstractLightManager*)theWrappedObject)->py_q_getLight(name));}
   int  py_q_getXMLOrder(AbstractLightManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_AbstractLightManager*)theWrappedObject)->py_q_getXMLOrder());}
   Light*  py_q_newLight(AbstractLightManager* theWrappedObject, QString  systemName, QString  userName){  return (((PythonQtPublicPromoter_AbstractLightManager*)theWrappedObject)->py_q_newLight(systemName, userName));}
   QString  py_q_normalizeSystemName(AbstractLightManager* theWrappedObject, QString  systemName){  return (((PythonQtPublicPromoter_AbstractLightManager*)theWrappedObject)->py_q_normalizeSystemName(systemName));}
   Light*  py_q_provideLight(AbstractLightManager* theWrappedObject, QString  name){  return (((PythonQtPublicPromoter_AbstractLightManager*)theWrappedObject)->py_q_provideLight(name));}
   bool  py_q_supportsVariableLights(AbstractLightManager* theWrappedObject, QString  systemName){  return (((PythonQtPublicPromoter_AbstractLightManager*)theWrappedObject)->py_q_supportsVariableLights(systemName));}
   char  py_q_typeLetter(AbstractLightManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_AbstractLightManager*)theWrappedObject)->py_q_typeLetter());}
    QString py_toString(AbstractLightManager*);
};





class PythonQtShell_AbstractManager : public AbstractManager
{
public:
    PythonQtShell_AbstractManager(QObject*  parent = 0):AbstractManager(parent),_wrapper(NULL) {}
    PythonQtShell_AbstractManager(SystemConnectionMemo*  memo, QObject*  parent = 0):AbstractManager(memo, parent),_wrapper(NULL) {}

   ~PythonQtShell_AbstractManager();

virtual void Register(NamedBean*  s) const;
virtual void addDataListener(QObject*  e);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual void deleteBean(NamedBean*  arg__1, QString  arg__2) throw (PropertyVetoException) ;
virtual void deregister(NamedBean*  s) const;
virtual void dispose();
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual NamedBean*  getBeanBySystemName(QString  systemName) const;
virtual NamedBean*  getBeanByUserName(QString  arg__1) const;
virtual QString  getBeanTypeHandled(bool  plural) const;
virtual QString  getEntryToolTip();
virtual SystemConnectionMemo*  getMemo() const;
virtual NamedBean*  getNamedBean(QString  name) const;
virtual QString  getNamedBeanClass() const;
virtual QSet<NamedBean* >  getNamedBeanSet();
virtual int  getObjectCount();
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners();
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners(QString  propertyName);
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList();
virtual QString  getSystemPrefix() const;
virtual int  getXMLOrder() const;
virtual QString  makeSystemName(QString  s, bool  logErrors = true, QLocale  locale = QLocale()) const;
virtual QString  normalizeSystemName(QString  inputName) const;
virtual void propertyChange(PropertyChangeEvent*  e);
virtual void removeDataListener(QObject*  e);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void removePropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual void timerEvent(QTimerEvent*  event);
virtual QString  toString();
virtual char  typeLetter() const;
virtual Manager::NameValidity  validSystemNameFormat(QString  systemName) const;
virtual void vetoableChange(PropertyChangeEvent*  evt);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_AbstractManager : public AbstractManager
{ public:
inline void promoted_fireDataListenersAdded(int  start, int  end, NamedBean*  changedBean) { this->fireDataListenersAdded(start, end, changedBean); }
inline void promoted_fireDataListenersRemoved(int  start, int  end, NamedBean*  changedBean) { this->fireDataListenersRemoved(start, end, changedBean); }
inline void promoted_fireIndexedPropertyChange(QString  p, int  pos, QVariant  old, QVariant  n) const { this->fireIndexedPropertyChange(p, pos, old, n); }
inline void promoted_firePropertyChange(QString  p, QVariant  old, QVariant  n) const { this->firePropertyChange(p, old, n); }
inline void promoted_fireVetoableChange(QString  p, QVariant  old, QVariant  n) { this->fireVetoableChange(p, old, n); }
inline QObject*  promoted_getInstanceBySystemName(QString  systemName) { return this->getInstanceBySystemName(systemName); }
inline QObject*  promoted_getInstanceByUserName(QString  userName) { return this->getInstanceByUserName(userName); }
inline void promoted_handleUserNameUniqueness(NamedBean*  s) const { this->handleUserNameUniqueness(s); }
inline void promoted_registerSelf() { this->registerSelf(); }
inline void promoted_registerUserName(NamedBean*  s) const { this->registerUserName(s); }
inline void py_q_Register(NamedBean*  s) const { AbstractManager::Register(s); }
inline void py_q_addDataListener(QObject*  e) { AbstractManager::addDataListener(e); }
inline void py_q_addPropertyChangeListener(PropertyChangeListener*  l) { AbstractManager::addPropertyChangeListener(l); }
inline void py_q_addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener) { AbstractManager::addPropertyChangeListener(propertyName, listener); }
inline void py_q_deregister(NamedBean*  s) const { AbstractManager::deregister(s); }
inline void py_q_dispose() { AbstractManager::dispose(); }
inline NamedBean*  py_q_getBeanBySystemName(QString  systemName) const { return AbstractManager::getBeanBySystemName(systemName); }
inline SystemConnectionMemo*  py_q_getMemo() const { return AbstractManager::getMemo(); }
inline NamedBean*  py_q_getNamedBean(QString  name) const { return AbstractManager::getNamedBean(name); }
inline QSet<NamedBean* >  py_q_getNamedBeanSet() { return AbstractManager::getNamedBeanSet(); }
inline int  py_q_getObjectCount() { return AbstractManager::getObjectCount(); }
inline QVector<PropertyChangeListener* >  py_q_getPropertyChangeListeners() { return AbstractManager::getPropertyChangeListeners(); }
inline QVector<PropertyChangeListener* >  py_q_getPropertyChangeListeners(QString  propertyName) { return AbstractManager::getPropertyChangeListeners(propertyName); }
inline QStringList  py_q_getSystemNameArray() { return AbstractManager::getSystemNameArray(); }
inline QStringList  py_q_getSystemNameList() { return AbstractManager::getSystemNameList(); }
inline QString  py_q_getSystemPrefix() const { return AbstractManager::getSystemPrefix(); }
inline QString  py_q_makeSystemName(QString  s, bool  logErrors = true, QLocale  locale = QLocale()) const { return AbstractManager::makeSystemName(s, logErrors, locale); }
inline QString  py_q_normalizeSystemName(QString  inputName) const { return AbstractManager::normalizeSystemName(inputName); }
inline void py_q_propertyChange(PropertyChangeEvent*  e) { AbstractManager::propertyChange(e); }
inline void py_q_removeDataListener(QObject*  e) { AbstractManager::removeDataListener(e); }
inline void py_q_removePropertyChangeListener(PropertyChangeListener*  l) { AbstractManager::removePropertyChangeListener(l); }
inline void py_q_removePropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener) { AbstractManager::removePropertyChangeListener(propertyName, listener); }
inline Manager::NameValidity  py_q_validSystemNameFormat(QString  systemName) const { return AbstractManager::validSystemNameFormat(systemName); }
inline void py_q_vetoableChange(PropertyChangeEvent*  evt) { AbstractManager::vetoableChange(evt); }
};

class PythonQtWrapper_AbstractManager : public QObject
{ Q_OBJECT
public:
public slots:
AbstractManager* new_AbstractManager(QObject*  parent = 0);
AbstractManager* new_AbstractManager(SystemConnectionMemo*  memo, QObject*  parent = 0);
void delete_AbstractManager(AbstractManager* obj) { delete obj; } 
   void py_q_Register(AbstractManager* theWrappedObject, NamedBean*  s) const{  (((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->py_q_Register(s));}
   void py_q_addDataListener(AbstractManager* theWrappedObject, QObject*  e){  (((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->py_q_addDataListener(e));}
   void py_q_addPropertyChangeListener(AbstractManager* theWrappedObject, PropertyChangeListener*  l){  (((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->py_q_addPropertyChangeListener(l));}
   void py_q_addPropertyChangeListener(AbstractManager* theWrappedObject, QString  propertyName, PropertyChangeListener*  listener){  (((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->py_q_addPropertyChangeListener(propertyName, listener));}
   void py_q_deregister(AbstractManager* theWrappedObject, NamedBean*  s) const{  (((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->py_q_deregister(s));}
   void py_q_dispose(AbstractManager* theWrappedObject){  (((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->py_q_dispose());}
   void fireDataListenersAdded(AbstractManager* theWrappedObject, int  start, int  end, NamedBean*  changedBean);
   void fireDataListenersRemoved(AbstractManager* theWrappedObject, int  start, int  end, NamedBean*  changedBean);
   void fireIndexedPropertyChange(AbstractManager* theWrappedObject, QString  p, int  pos, QVariant  old, QVariant  n) const;
   void firePropertyChange(AbstractManager* theWrappedObject, QString  p, QVariant  old, QVariant  n) const;
   void fireVetoableChange(AbstractManager* theWrappedObject, QString  p, QVariant  old, QVariant  n);
   QString  getAutoSystemName(AbstractManager* theWrappedObject) const;
   NamedBean*  py_q_getBeanBySystemName(AbstractManager* theWrappedObject, QString  systemName) const{  return (((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->py_q_getBeanBySystemName(systemName));}
   QObject*  getInstanceBySystemName(AbstractManager* theWrappedObject, QString  systemName);
   QObject*  getInstanceByUserName(AbstractManager* theWrappedObject, QString  userName);
   SystemConnectionMemo*  py_q_getMemo(AbstractManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->py_q_getMemo());}
   NamedBean*  py_q_getNamedBean(AbstractManager* theWrappedObject, QString  name) const{  return (((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->py_q_getNamedBean(name));}
   QSet<NamedBean* >  py_q_getNamedBeanSet(AbstractManager* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->py_q_getNamedBeanSet());}
   int  py_q_getObjectCount(AbstractManager* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->py_q_getObjectCount());}
   QVector<PropertyChangeListener* >  py_q_getPropertyChangeListeners(AbstractManager* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->py_q_getPropertyChangeListeners());}
   QVector<PropertyChangeListener* >  py_q_getPropertyChangeListeners(AbstractManager* theWrappedObject, QString  propertyName){  return (((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->py_q_getPropertyChangeListeners(propertyName));}
   QStringList  py_q_getSystemNameArray(AbstractManager* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->py_q_getSystemNameArray());}
   QHash<QString , NamedBean* >*  getSystemNameHash(AbstractManager* theWrappedObject);
   QStringList  py_q_getSystemNameList(AbstractManager* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->py_q_getSystemNameList());}
   QString  py_q_getSystemPrefix(AbstractManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->py_q_getSystemPrefix());}
   QStringList  getUserNameList(AbstractManager* theWrappedObject);
   void handleUserNameUniqueness(AbstractManager* theWrappedObject, NamedBean*  s) const;
   QString  py_q_makeSystemName(AbstractManager* theWrappedObject, QString  s, bool  logErrors = true, QLocale  locale = QLocale()) const{  return (((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->py_q_makeSystemName(s, logErrors, locale));}
   QString  py_q_normalizeSystemName(AbstractManager* theWrappedObject, QString  inputName) const{  return (((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->py_q_normalizeSystemName(inputName));}
   void py_q_propertyChange(AbstractManager* theWrappedObject, PropertyChangeEvent*  e){  (((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->py_q_propertyChange(e));}
   void registerSelf(AbstractManager* theWrappedObject);
   void registerUserName(AbstractManager* theWrappedObject, NamedBean*  s) const;
   void py_q_removeDataListener(AbstractManager* theWrappedObject, QObject*  e){  (((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->py_q_removeDataListener(e));}
   void py_q_removePropertyChangeListener(AbstractManager* theWrappedObject, PropertyChangeListener*  l){  (((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->py_q_removePropertyChangeListener(l));}
   void py_q_removePropertyChangeListener(AbstractManager* theWrappedObject, QString  propertyName, PropertyChangeListener*  listener){  (((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->py_q_removePropertyChangeListener(propertyName, listener));}
   void setDataListenerMute(AbstractManager* theWrappedObject, bool  m);
   void updateAutoNumber(AbstractManager* theWrappedObject, QString  systemName) const;
   Manager::NameValidity  py_q_validSystemNameFormat(AbstractManager* theWrappedObject, QString  systemName) const{  return (((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->py_q_validSystemNameFormat(systemName));}
   void py_q_vetoableChange(AbstractManager* theWrappedObject, PropertyChangeEvent*  evt){  (((PythonQtPublicPromoter_AbstractManager*)theWrappedObject)->py_q_vetoableChange(evt));}
    QString py_toString(AbstractManager*);
void py_set_pcs(AbstractManager* theWrappedObject, PropertyChangeSupport*  pcs){ theWrappedObject->pcs = pcs; }
PropertyChangeSupport*  py_get_pcs(AbstractManager* theWrappedObject){ return theWrappedObject->pcs; }
void py_set_vcs(AbstractManager* theWrappedObject, VetoableChangeSupport*  vcs){ theWrappedObject->vcs = vcs; }
VetoableChangeSupport*  py_get_vcs(AbstractManager* theWrappedObject){ return theWrappedObject->vcs; }
};





class PythonQtShell_AbstractNamedBean : public AbstractNamedBean
{
public:
    PythonQtShell_AbstractNamedBean(QObject*  parent = 0):AbstractNamedBean(parent),_wrapper(NULL) {}
    PythonQtShell_AbstractNamedBean(QString  sys, QObject*  parent = 0):AbstractNamedBean(sys, parent),_wrapper(NULL) {}
    PythonQtShell_AbstractNamedBean(QString  sys, QString  user, QObject*  parent = 0):AbstractNamedBean(sys, user, parent),_wrapper(NULL) {}

   ~PythonQtShell_AbstractNamedBean();

virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(PropertyChangeListener*  l, QString  beanRef, const QString  listenerRef);
virtual void addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  l, QString  beanRef, QString  listenerRef);
virtual void addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual void childEvent(QChildEvent*  event);
virtual int  compareSystemNameSuffix(QString  suffix1, QString  suffix2, NamedBean*  n);
virtual int  compareTo(NamedBean*  n2);
virtual void customEvent(QEvent*  event);
virtual QString  describeState(int  state);
virtual void dispose();
virtual bool  equals(QObject*  obj);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual QString  getBeanType();
virtual QString  getComment();
virtual QString  getDisplayName();
virtual QString  getFullyFormattedDisplayName();
virtual QString  getListenerRef(PropertyChangeListener*  l);
virtual QList<QString >*  getListenerRefs();
virtual int  getNumPropertyChangeListeners();
virtual QVariant  getProperty(QString  key);
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners();
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners(QString  name);
virtual QVector<PropertyChangeListener* >  getPropertyChangeListenersByReference(QString  propertyName);
virtual QSet<QString >  getPropertyKeys();
virtual int  getState();
virtual QString  getSystemName() const;
virtual QString  getUserName() const;
virtual uint  hashCode();
virtual void removeProperty(QString  key);
virtual void removePropertyChangeListener(PropertyChangeListener*  listener);
virtual void removePropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual void setComment(QString  comment);
virtual void setProperty(QString  key, QVariant  value);
virtual void setState(int  arg__1);
virtual void setUserName(QString  s) throw (NamedBean::BadUserNameException) ;
virtual void timerEvent(QTimerEvent*  event);
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);
virtual void vetoableChange(PropertyChangeEvent*  evt) throw (PropertyVetoException) ;

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_AbstractNamedBean : public AbstractNamedBean
{ public:
inline void promoted_firePropertyChange(QString  p, QVariant  old, QVariant  n) const { this->firePropertyChange(p, old, n); }
inline void py_q_addPropertyChangeListener(PropertyChangeListener*  l) { AbstractNamedBean::addPropertyChangeListener(l); }
inline void py_q_addPropertyChangeListener(PropertyChangeListener*  l, QString  beanRef, const QString  listenerRef) { AbstractNamedBean::addPropertyChangeListener(l, beanRef, listenerRef); }
inline void py_q_addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  l, QString  beanRef, QString  listenerRef) { AbstractNamedBean::addPropertyChangeListener(propertyName, l, beanRef, listenerRef); }
inline void py_q_addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener) { AbstractNamedBean::addPropertyChangeListener(propertyName, listener); }
inline int  py_q_compareSystemNameSuffix(QString  suffix1, QString  suffix2, NamedBean*  n) { return AbstractNamedBean::compareSystemNameSuffix(suffix1, suffix2, n); }
inline QString  py_q_describeState(int  state) { return AbstractNamedBean::describeState(state); }
inline void py_q_dispose() { AbstractNamedBean::dispose(); }
inline bool  py_q_equals(QObject*  obj) { return AbstractNamedBean::equals(obj); }
inline QString  py_q_getComment() { return AbstractNamedBean::getComment(); }
inline QString  py_q_getDisplayName() { return AbstractNamedBean::getDisplayName(); }
inline QString  py_q_getFullyFormattedDisplayName() { return AbstractNamedBean::getFullyFormattedDisplayName(); }
inline QString  py_q_getListenerRef(PropertyChangeListener*  l) { return AbstractNamedBean::getListenerRef(l); }
inline QList<QString >*  py_q_getListenerRefs() { return AbstractNamedBean::getListenerRefs(); }
inline int  py_q_getNumPropertyChangeListeners() { return AbstractNamedBean::getNumPropertyChangeListeners(); }
inline QVariant  py_q_getProperty(QString  key) { return AbstractNamedBean::getProperty(key); }
inline QVector<PropertyChangeListener* >  py_q_getPropertyChangeListeners() { return AbstractNamedBean::getPropertyChangeListeners(); }
inline QVector<PropertyChangeListener* >  py_q_getPropertyChangeListeners(QString  name) { return AbstractNamedBean::getPropertyChangeListeners(name); }
inline QVector<PropertyChangeListener* >  py_q_getPropertyChangeListenersByReference(QString  propertyName) { return AbstractNamedBean::getPropertyChangeListenersByReference(propertyName); }
inline QSet<QString >  py_q_getPropertyKeys() { return AbstractNamedBean::getPropertyKeys(); }
inline QString  py_q_getSystemName() const { return AbstractNamedBean::getSystemName(); }
inline QString  py_q_getUserName() const { return AbstractNamedBean::getUserName(); }
inline uint  py_q_hashCode() { return AbstractNamedBean::hashCode(); }
inline void py_q_removeProperty(QString  key) { AbstractNamedBean::removeProperty(key); }
inline void py_q_removePropertyChangeListener(PropertyChangeListener*  listener) { AbstractNamedBean::removePropertyChangeListener(listener); }
inline void py_q_removePropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener) { AbstractNamedBean::removePropertyChangeListener(propertyName, listener); }
inline void py_q_setComment(QString  comment) { AbstractNamedBean::setComment(comment); }
inline void py_q_setProperty(QString  key, QVariant  value) { AbstractNamedBean::setProperty(key, value); }
inline void py_q_setUserName(QString  s) throw (NamedBean::BadUserNameException)  { AbstractNamedBean::setUserName(s); }
inline void py_q_updateListenerRef(PropertyChangeListener*  l, QString  newName) { AbstractNamedBean::updateListenerRef(l, newName); }
inline void py_q_vetoableChange(PropertyChangeEvent*  evt) throw (PropertyVetoException)  { AbstractNamedBean::vetoableChange(evt); }
};

class PythonQtWrapper_AbstractNamedBean : public QObject
{ Q_OBJECT
public:
public slots:
AbstractNamedBean* new_AbstractNamedBean(QObject*  parent = 0);
AbstractNamedBean* new_AbstractNamedBean(QString  sys, QObject*  parent = 0);
AbstractNamedBean* new_AbstractNamedBean(QString  sys, QString  user, QObject*  parent = 0);
void delete_AbstractNamedBean(AbstractNamedBean* obj) { delete obj; } 
   void py_q_addPropertyChangeListener(AbstractNamedBean* theWrappedObject, PropertyChangeListener*  l){  (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_addPropertyChangeListener(l));}
   void py_q_addPropertyChangeListener(AbstractNamedBean* theWrappedObject, PropertyChangeListener*  l, QString  beanRef, const QString  listenerRef){  (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_addPropertyChangeListener(l, beanRef, listenerRef));}
   void py_q_addPropertyChangeListener(AbstractNamedBean* theWrappedObject, QString  propertyName, PropertyChangeListener*  l, QString  beanRef, QString  listenerRef){  (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_addPropertyChangeListener(propertyName, l, beanRef, listenerRef));}
   void py_q_addPropertyChangeListener(AbstractNamedBean* theWrappedObject, QString  propertyName, PropertyChangeListener*  listener){  (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_addPropertyChangeListener(propertyName, listener));}
   int  py_q_compareSystemNameSuffix(AbstractNamedBean* theWrappedObject, QString  suffix1, QString  suffix2, NamedBean*  n){  return (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_compareSystemNameSuffix(suffix1, suffix2, n));}
   QString  py_q_describeState(AbstractNamedBean* theWrappedObject, int  state){  return (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_describeState(state));}
   void py_q_dispose(AbstractNamedBean* theWrappedObject){  (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_dispose());}
   bool  py_q_equals(AbstractNamedBean* theWrappedObject, QObject*  obj){  return (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_equals(obj));}
   void firePropertyChange(AbstractNamedBean* theWrappedObject, QString  p, QVariant  old, QVariant  n) const;
   QString  py_q_getComment(AbstractNamedBean* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_getComment());}
   QString  py_q_getDisplayName(AbstractNamedBean* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_getDisplayName());}
   QString  py_q_getFullyFormattedDisplayName(AbstractNamedBean* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_getFullyFormattedDisplayName());}
   QString  py_q_getListenerRef(AbstractNamedBean* theWrappedObject, PropertyChangeListener*  l){  return (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_getListenerRef(l));}
   QList<QString >*  py_q_getListenerRefs(AbstractNamedBean* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_getListenerRefs());}
   int  py_q_getNumPropertyChangeListeners(AbstractNamedBean* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_getNumPropertyChangeListeners());}
   QVariant  py_q_getProperty(AbstractNamedBean* theWrappedObject, QString  key){  return (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_getProperty(key));}
   QVector<PropertyChangeListener* >  getPropertyChangeListeners(AbstractNamedBean* theWrappedObject);
   QVector<PropertyChangeListener* >  py_q_getPropertyChangeListeners(AbstractNamedBean* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_getPropertyChangeListeners());}
   QVector<PropertyChangeListener* >  getPropertyChangeListeners(AbstractNamedBean* theWrappedObject, QString  name);
   QVector<PropertyChangeListener* >  py_q_getPropertyChangeListeners(AbstractNamedBean* theWrappedObject, QString  name){  return (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_getPropertyChangeListeners(name));}
   QVector<PropertyChangeListener* >  py_q_getPropertyChangeListenersByReference(AbstractNamedBean* theWrappedObject, QString  propertyName){  return (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_getPropertyChangeListenersByReference(propertyName));}
   QSet<QString >  py_q_getPropertyKeys(AbstractNamedBean* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_getPropertyKeys());}
   QString  py_q_getSystemName(AbstractNamedBean* theWrappedObject) const{  return (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_getSystemName());}
   QString  py_q_getUserName(AbstractNamedBean* theWrappedObject) const{  return (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_getUserName());}
   uint  py_q_hashCode(AbstractNamedBean* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_hashCode());}
   bool  __lt__(AbstractNamedBean* theWrappedObject, const AbstractNamedBean&  e2);
   bool  __eq__(AbstractNamedBean* theWrappedObject, const AbstractNamedBean&  e2);
   uint  qHash(AbstractNamedBean* theWrappedObject, const AbstractNamedBean&  arg__1, uint  arg__2);
   void py_q_removeProperty(AbstractNamedBean* theWrappedObject, QString  key){  (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_removeProperty(key));}
   void py_q_removePropertyChangeListener(AbstractNamedBean* theWrappedObject, PropertyChangeListener*  listener){  (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_removePropertyChangeListener(listener));}
   void py_q_removePropertyChangeListener(AbstractNamedBean* theWrappedObject, QString  propertyName, PropertyChangeListener*  listener){  (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_removePropertyChangeListener(propertyName, listener));}
   void py_q_setComment(AbstractNamedBean* theWrappedObject, QString  comment){  (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_setComment(comment));}
   void py_q_setProperty(AbstractNamedBean* theWrappedObject, QString  key, QVariant  value){  (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_setProperty(key, value));}
   void py_q_setUserName(AbstractNamedBean* theWrappedObject, QString  s) throw (NamedBean::BadUserNameException) {  (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_setUserName(s));}
   void py_q_updateListenerRef(AbstractNamedBean* theWrappedObject, PropertyChangeListener*  l, QString  newName){  (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_updateListenerRef(l, newName));}
   void py_q_vetoableChange(AbstractNamedBean* theWrappedObject, PropertyChangeEvent*  evt) throw (PropertyVetoException) {  (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_vetoableChange(evt));}
void py_set_pcs(AbstractNamedBean* theWrappedObject, PropertyChangeSupport*  pcs){ theWrappedObject->pcs = pcs; }
PropertyChangeSupport*  py_get_pcs(AbstractNamedBean* theWrappedObject){ return theWrappedObject->pcs; }
};





class PythonQtShell_AbstractPortController : public AbstractPortController
{
public:
    PythonQtShell_AbstractPortController(SystemConnectionMemo*  connectionMemo, QObject*  parent = 0):AbstractPortController(connectionMemo, parent),_wrapper(NULL) {}

   ~PythonQtShell_AbstractPortController();

virtual void _connect(QString  arg__1, int  arg__2);
virtual void autoConfigure();
virtual void childEvent(QChildEvent*  event);
virtual QString  className();
virtual void configure();
virtual void configureOption1(QString  value);
virtual void configureOption2(QString  value);
virtual void configureOption3(QString  value);
virtual void configureOption4(QString  value);
virtual void customEvent(QEvent*  event);
virtual void dispose();
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual QString  getAdvertisementName();
virtual QString  getCurrentPortName();
virtual bool  getDisabled();
virtual QString  getHostName();
virtual QDataStream*  getInputStream();
virtual QString  getManufacturer();
virtual bool  getMdnsConfigure();
virtual QString  getOption1Name();
virtual QString  getOption2Name();
virtual QString  getOption3Name();
virtual QString  getOption4Name();
virtual QStringList  getOptionChoices(QString  option);
virtual QString  getOptionDisplayName(QString  option);
virtual QString  getOptionState(QString  option);
virtual QStringList  getOptions();
virtual QDataStream*  getOutputStream();
virtual int  getPort();
virtual QString  getServiceType();
virtual SystemConnectionMemo*  getSystemConnectionMemo() const;
virtual QString  getSystemPrefix();
virtual QString  getUserName();
virtual bool  isDirty();
virtual bool  isOptionAdvanced(QString  option);
virtual bool  isRestartRequired();
virtual void recover();
virtual void setAdvertisementName(QString  arg__1);
virtual void setDisabled(bool  disabled);
virtual void setHostName(QString  arg__1);
virtual void setManufacturer(QString  manufacturer);
virtual void setMdnsConfigure(bool  arg__1);
virtual void setOptionState(QString  option, QString  value);
virtual void setPort(QString  arg__1);
virtual void setPort(int  arg__1);
virtual void setServiceType(QString  arg__1);
virtual void setSystemConnectionMemo(SystemConnectionMemo*  connectionMemo);
virtual void setSystemPrefix(QString  systemPrefix);
virtual void setUserName(QString  userName);
virtual bool  status();
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_AbstractPortController : public AbstractPortController
{ public:
inline void promoted_purgeStream(QDataStream*  serialStream) { this->purgeStream(serialStream); }
static inline void promoted_safeSleep(long  milliseconds, QString  s) { safeSleep(milliseconds, s); }
inline void promoted_setClosed() { this->setClosed(); }
inline void promoted_setOpened() { this->setOpened(); }
inline void py_q_configureOption1(QString  value) { AbstractPortController::configureOption1(value); }
inline void py_q_configureOption2(QString  value) { AbstractPortController::configureOption2(value); }
inline void py_q_configureOption3(QString  value) { AbstractPortController::configureOption3(value); }
inline void py_q_configureOption4(QString  value) { AbstractPortController::configureOption4(value); }
inline void py_q_dispose() { AbstractPortController::dispose(); }
inline QString  py_q_getCurrentPortName() { return AbstractPortController::getCurrentPortName(); }
inline bool  py_q_getDisabled() { return AbstractPortController::getDisabled(); }
inline QDataStream*  py_q_getInputStream() { return AbstractPortController::getInputStream(); }
inline QString  py_q_getManufacturer() { return AbstractPortController::getManufacturer(); }
inline QString  py_q_getOption1Name() { return AbstractPortController::getOption1Name(); }
inline QString  py_q_getOption2Name() { return AbstractPortController::getOption2Name(); }
inline QString  py_q_getOption3Name() { return AbstractPortController::getOption3Name(); }
inline QString  py_q_getOption4Name() { return AbstractPortController::getOption4Name(); }
inline QStringList  py_q_getOptionChoices(QString  option) { return AbstractPortController::getOptionChoices(option); }
inline QString  py_q_getOptionDisplayName(QString  option) { return AbstractPortController::getOptionDisplayName(option); }
inline QString  py_q_getOptionState(QString  option) { return AbstractPortController::getOptionState(option); }
inline QStringList  py_q_getOptions() { return AbstractPortController::getOptions(); }
inline QDataStream*  py_q_getOutputStream() { return AbstractPortController::getOutputStream(); }
inline SystemConnectionMemo*  py_q_getSystemConnectionMemo() const { return AbstractPortController::getSystemConnectionMemo(); }
inline QString  py_q_getSystemPrefix() { return AbstractPortController::getSystemPrefix(); }
inline QString  py_q_getUserName() { return AbstractPortController::getUserName(); }
inline bool  py_q_isDirty() { return AbstractPortController::isDirty(); }
inline bool  py_q_isOptionAdvanced(QString  option) { return AbstractPortController::isOptionAdvanced(option); }
inline bool  py_q_isRestartRequired() { return AbstractPortController::isRestartRequired(); }
inline void py_q_recover() { AbstractPortController::recover(); }
inline void py_q_setDisabled(bool  disabled) { AbstractPortController::setDisabled(disabled); }
inline void py_q_setManufacturer(QString  manufacturer) { AbstractPortController::setManufacturer(manufacturer); }
inline void py_q_setOptionState(QString  option, QString  value) { AbstractPortController::setOptionState(option, value); }
inline void py_q_setSystemConnectionMemo(SystemConnectionMemo*  connectionMemo) { AbstractPortController::setSystemConnectionMemo(connectionMemo); }
inline void py_q_setSystemPrefix(QString  systemPrefix) { AbstractPortController::setSystemPrefix(systemPrefix); }
inline void py_q_setUserName(QString  userName) { AbstractPortController::setUserName(userName); }
inline bool  py_q_status() { return AbstractPortController::status(); }
};

class PythonQtWrapper_AbstractPortController : public QObject
{ Q_OBJECT
public:
public slots:
AbstractPortController* new_AbstractPortController(SystemConnectionMemo*  connectionMemo, QObject*  parent = 0);
void delete_AbstractPortController(AbstractPortController* obj) { delete obj; } 
   void py_q_configureOption1(AbstractPortController* theWrappedObject, QString  value){  (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_configureOption1(value));}
   void py_q_configureOption2(AbstractPortController* theWrappedObject, QString  value){  (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_configureOption2(value));}
   void py_q_configureOption3(AbstractPortController* theWrappedObject, QString  value){  (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_configureOption3(value));}
   void py_q_configureOption4(AbstractPortController* theWrappedObject, QString  value){  (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_configureOption4(value));}
   void py_q_dispose(AbstractPortController* theWrappedObject){  (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_dispose());}
   QString  py_q_getCurrentPortName(AbstractPortController* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_getCurrentPortName());}
   bool  py_q_getDisabled(AbstractPortController* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_getDisabled());}
   QDataStream*  py_q_getInputStream(AbstractPortController* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_getInputStream());}
   QString  py_q_getManufacturer(AbstractPortController* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_getManufacturer());}
   QString  py_q_getOption1Name(AbstractPortController* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_getOption1Name());}
   QString  py_q_getOption2Name(AbstractPortController* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_getOption2Name());}
   QString  py_q_getOption3Name(AbstractPortController* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_getOption3Name());}
   QString  py_q_getOption4Name(AbstractPortController* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_getOption4Name());}
   QStringList  py_q_getOptionChoices(AbstractPortController* theWrappedObject, QString  option){  return (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_getOptionChoices(option));}
   QString  py_q_getOptionDisplayName(AbstractPortController* theWrappedObject, QString  option){  return (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_getOptionDisplayName(option));}
   QString  py_q_getOptionState(AbstractPortController* theWrappedObject, QString  option){  return (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_getOptionState(option));}
   QStringList  py_q_getOptions(AbstractPortController* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_getOptions());}
   QDataStream*  py_q_getOutputStream(AbstractPortController* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_getOutputStream());}
   SystemConnectionMemo*  py_q_getSystemConnectionMemo(AbstractPortController* theWrappedObject) const{  return (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_getSystemConnectionMemo());}
   QString  py_q_getSystemPrefix(AbstractPortController* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_getSystemPrefix());}
   QString  py_q_getUserName(AbstractPortController* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_getUserName());}
   bool  py_q_isDirty(AbstractPortController* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_isDirty());}
   bool  py_q_isOptionAdvanced(AbstractPortController* theWrappedObject, QString  option){  return (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_isOptionAdvanced(option));}
   bool  py_q_isRestartRequired(AbstractPortController* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_isRestartRequired());}
   void purgeStream(AbstractPortController* theWrappedObject, QDataStream*  serialStream);
   void py_q_recover(AbstractPortController* theWrappedObject){  (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_recover());}
   void static_AbstractPortController_safeSleep(long  milliseconds, QString  s);
   void setClosed(AbstractPortController* theWrappedObject);
   void py_q_setDisabled(AbstractPortController* theWrappedObject, bool  disabled){  (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_setDisabled(disabled));}
   void py_q_setManufacturer(AbstractPortController* theWrappedObject, QString  manufacturer){  (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_setManufacturer(manufacturer));}
   void setOpened(AbstractPortController* theWrappedObject);
   void py_q_setOptionState(AbstractPortController* theWrappedObject, QString  option, QString  value){  (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_setOptionState(option, value));}
   void py_q_setSystemConnectionMemo(AbstractPortController* theWrappedObject, SystemConnectionMemo*  connectionMemo){  (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_setSystemConnectionMemo(connectionMemo));}
   void py_q_setSystemPrefix(AbstractPortController* theWrappedObject, QString  systemPrefix){  (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_setSystemPrefix(systemPrefix));}
   void py_q_setUserName(AbstractPortController* theWrappedObject, QString  userName){  (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_setUserName(userName));}
   bool  py_q_status(AbstractPortController* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractPortController*)theWrappedObject)->py_q_status());}
};





class PythonQtShell_AbstractPowerManager : public AbstractPowerManager
{
public:
    PythonQtShell_AbstractPowerManager(SystemConnectionMemo*  memo, QObject*  parent = 0):AbstractPowerManager(memo, parent),_wrapper(NULL) {}

   ~PythonQtShell_AbstractPowerManager();

virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual void dispose();
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual int  getPower();
virtual QString  getUserName();
virtual bool  implementsIdle();
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void setPower(int  arg__1);
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_AbstractPowerManager : public AbstractPowerManager
{ public:
inline void promoted_firePropertyChange(QString  p, QVariant  old, QVariant  n) { this->firePropertyChange(p, old, n); }
inline void py_q_addPropertyChangeListener(PropertyChangeListener*  l) { AbstractPowerManager::addPropertyChangeListener(l); }
inline QString  py_q_getUserName() { return AbstractPowerManager::getUserName(); }
inline void py_q_removePropertyChangeListener(PropertyChangeListener*  l) { AbstractPowerManager::removePropertyChangeListener(l); }
};

class PythonQtWrapper_AbstractPowerManager : public QObject
{ Q_OBJECT
public:
public slots:
AbstractPowerManager* new_AbstractPowerManager(SystemConnectionMemo*  memo, QObject*  parent = 0);
void delete_AbstractPowerManager(AbstractPowerManager* obj) { delete obj; } 
   void py_q_addPropertyChangeListener(AbstractPowerManager* theWrappedObject, PropertyChangeListener*  l){  (((PythonQtPublicPromoter_AbstractPowerManager*)theWrappedObject)->py_q_addPropertyChangeListener(l));}
   void firePropertyChange(AbstractPowerManager* theWrappedObject, QString  p, QVariant  old, QVariant  n);
   QString  py_q_getUserName(AbstractPowerManager* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractPowerManager*)theWrappedObject)->py_q_getUserName());}
   void py_q_removePropertyChangeListener(AbstractPowerManager* theWrappedObject, PropertyChangeListener*  l){  (((PythonQtPublicPromoter_AbstractPowerManager*)theWrappedObject)->py_q_removePropertyChangeListener(l));}
};





class PythonQtShell_AbstractReporterManager : public AbstractReporterManager
{
public:
    PythonQtShell_AbstractReporterManager(SystemConnectionMemo*  memo, QObject*  parent = 0):AbstractReporterManager(memo, parent),_wrapper(NULL) {}

   ~PythonQtShell_AbstractReporterManager();

virtual void Register(NamedBean*  s) const;
virtual void addDataListener(QObject*  e);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual bool  allowMultipleAdditions(QString  systemName) const;
virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual void deleteBean(NamedBean*  arg__1, QString  arg__2) throw (PropertyVetoException) ;
virtual void deregister(NamedBean*  s) const;
virtual void dispose();
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual NamedBean*  getBeanBySystemName(QString  systemName) const;
virtual NamedBean*  getBeanByUserName(QString  arg__1) const;
virtual QString  getBeanTypeHandled(bool  plural) const;
virtual NamedBean*  getBySystemName(QString  name) const;
virtual NamedBean*  getByUserName(QString  key) const;
virtual QString  getEntryToolTip();
virtual SystemConnectionMemo*  getMemo() const;
virtual NamedBean*  getNamedBean(QString  name) const;
virtual QString  getNamedBeanClass() const;
virtual QSet<NamedBean* >  getNamedBeanSet();
virtual QString  getNextValidAddress(QString  curAddress, QString  prefix) const;
virtual int  getObjectCount();
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners();
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners(QString  propertyName);
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList() const;
virtual QString  getSystemPrefix() const;
virtual int  getXMLOrder() const;
virtual QString  makeSystemName(QString  s, bool  logErrors = true, QLocale  locale = QLocale()) const;
virtual QString  normalizeSystemName(QString  inputName) const;
virtual void propertyChange(PropertyChangeEvent*  e);
virtual void removeDataListener(QObject*  e);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void removePropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual void timerEvent(QTimerEvent*  event);
virtual QString  toString();
virtual char  typeLetter() const;
virtual Manager::NameValidity  validSystemNameFormat(QString  systemName) const;
virtual void vetoableChange(PropertyChangeEvent*  evt);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_AbstractReporterManager : public AbstractReporterManager
{ public:
inline bool  py_q_allowMultipleAdditions(QString  systemName) const { return AbstractReporterManager::allowMultipleAdditions(systemName); }
inline QString  py_q_getBeanTypeHandled(bool  plural) const { return AbstractReporterManager::getBeanTypeHandled(plural); }
inline NamedBean*  py_q_getBySystemName(QString  name) const { return AbstractReporterManager::getBySystemName(name); }
inline NamedBean*  py_q_getByUserName(QString  key) const { return AbstractReporterManager::getByUserName(key); }
inline QString  py_q_getNextValidAddress(QString  curAddress, QString  prefix) const { return AbstractReporterManager::getNextValidAddress(curAddress, prefix); }
inline int  py_q_getXMLOrder() const { return AbstractReporterManager::getXMLOrder(); }
inline char  py_q_typeLetter() const { return AbstractReporterManager::typeLetter(); }
};

class PythonQtWrapper_AbstractReporterManager : public QObject
{ Q_OBJECT
public:
public slots:
AbstractReporterManager* new_AbstractReporterManager(SystemConnectionMemo*  memo, QObject*  parent = 0);
void delete_AbstractReporterManager(AbstractReporterManager* obj) { delete obj; } 
   bool  py_q_allowMultipleAdditions(AbstractReporterManager* theWrappedObject, QString  systemName) const{  return (((PythonQtPublicPromoter_AbstractReporterManager*)theWrappedObject)->py_q_allowMultipleAdditions(systemName));}
   QString  py_q_getBeanTypeHandled(AbstractReporterManager* theWrappedObject, bool  plural) const{  return (((PythonQtPublicPromoter_AbstractReporterManager*)theWrappedObject)->py_q_getBeanTypeHandled(plural));}
   NamedBean*  py_q_getBySystemName(AbstractReporterManager* theWrappedObject, QString  name) const{  return (((PythonQtPublicPromoter_AbstractReporterManager*)theWrappedObject)->py_q_getBySystemName(name));}
   NamedBean*  py_q_getByUserName(AbstractReporterManager* theWrappedObject, QString  key) const{  return (((PythonQtPublicPromoter_AbstractReporterManager*)theWrappedObject)->py_q_getByUserName(key));}
   QString  py_q_getNextValidAddress(AbstractReporterManager* theWrappedObject, QString  curAddress, QString  prefix) const{  return (((PythonQtPublicPromoter_AbstractReporterManager*)theWrappedObject)->py_q_getNextValidAddress(curAddress, prefix));}
   int  py_q_getXMLOrder(AbstractReporterManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_AbstractReporterManager*)theWrappedObject)->py_q_getXMLOrder());}
   char  py_q_typeLetter(AbstractReporterManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_AbstractReporterManager*)theWrappedObject)->py_q_typeLetter());}
    QString py_toString(AbstractReporterManager*);
};





class PythonQtShell_AbstractSensor : public AbstractSensor
{
public:
    PythonQtShell_AbstractSensor(QObject*  parent = 0):AbstractSensor(parent),_wrapper(NULL) {}
    PythonQtShell_AbstractSensor(QString  systemName, QObject*  parent = 0):AbstractSensor(systemName, parent),_wrapper(NULL) {}
    PythonQtShell_AbstractSensor(QString  systemName, QString  userName, QObject*  parent = 0):AbstractSensor(systemName, userName, parent),_wrapper(NULL) {}

   ~PythonQtShell_AbstractSensor();

virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(PropertyChangeListener*  l, QString  beanRef, const QString  listenerRef);
virtual void addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  l, QString  beanRef, QString  listenerRef);
virtual void addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual bool  canInvert();
virtual void childEvent(QChildEvent*  event);
virtual int  compareSystemNameSuffix(QString  suffix1, QString  suffix2, NamedBean*  n);
virtual int  compareTo(NamedBean*  n2);
virtual void customEvent(QEvent*  event);
virtual QString  describeState(int  state);
virtual void dispose();
virtual bool  equals(QObject*  obj);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual QString  getBeanType();
virtual int  getCommandedState();
virtual QString  getComment();
virtual QString  getDisplayName();
virtual QString  getFullyFormattedDisplayName();
virtual bool  getInverted() const;
virtual int  getKnownState() const;
virtual QString  getListenerRef(PropertyChangeListener*  l);
virtual QList<QString >*  getListenerRefs();
virtual int  getNumPropertyChangeListeners();
virtual QVariant  getProperty(QString  key);
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners();
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners(QString  name);
virtual QVector<PropertyChangeListener* >  getPropertyChangeListenersByReference(QString  propertyName);
virtual QSet<QString >  getPropertyKeys();
virtual int  getRawState() const;
virtual long  getSensorDebounceGoingActiveTimer() const;
virtual long  getSensorDebounceGoingInActiveTimer() const;
virtual int  getState();
virtual QString  getSystemName() const;
virtual bool  getUseDefaultTimerSettings();
virtual QString  getUserName() const;
virtual uint  hashCode();
virtual void removeProperty(QString  key);
virtual void removePropertyChangeListener(PropertyChangeListener*  listener);
virtual void removePropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual void requestUpdateFromLayout() const;
virtual void setCommandedState(int  s);
virtual void setComment(QString  comment);
virtual void setInverted(bool  inverted);
virtual void setKnownState(int  s);
virtual void setProperty(QString  key, QVariant  value);
virtual void setSensorDebounceGoingActiveTimer(long  time) const;
virtual void setSensorDebounceGoingInActiveTimer(long  time);
virtual void setState(int  s);
virtual void setUseDefaultTimerSettings(bool  boo);
virtual void setUserName(QString  s) throw (NamedBean::BadUserNameException) ;
virtual void timerEvent(QTimerEvent*  event);
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);
virtual bool  useDefaultTimerSettings();
virtual void useDefaultTimerSettings(bool  boo);
virtual void vetoableChange(PropertyChangeEvent*  evt) throw (PropertyVetoException) ;

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_AbstractSensor : public AbstractSensor
{ public:
inline void promoted_sensorDebounce() { this->sensorDebounce(); }
inline bool  py_q_canInvert() { return AbstractSensor::canInvert(); }
inline QString  py_q_describeState(int  state) { return AbstractSensor::describeState(state); }
inline QString  py_q_getBeanType() { return AbstractSensor::getBeanType(); }
inline bool  py_q_getInverted() const { return AbstractSensor::getInverted(); }
inline int  py_q_getKnownState() const { return AbstractSensor::getKnownState(); }
inline int  py_q_getRawState() const { return AbstractSensor::getRawState(); }
inline long  py_q_getSensorDebounceGoingActiveTimer() const { return AbstractSensor::getSensorDebounceGoingActiveTimer(); }
inline long  py_q_getSensorDebounceGoingInActiveTimer() const { return AbstractSensor::getSensorDebounceGoingInActiveTimer(); }
inline int  py_q_getState() { return AbstractSensor::getState(); }
inline bool  py_q_getUseDefaultTimerSettings() { return AbstractSensor::getUseDefaultTimerSettings(); }
inline void py_q_setInverted(bool  inverted) { AbstractSensor::setInverted(inverted); }
inline void py_q_setKnownState(int  s) { AbstractSensor::setKnownState(s); }
inline void py_q_setSensorDebounceGoingActiveTimer(long  time) const { AbstractSensor::setSensorDebounceGoingActiveTimer(time); }
inline void py_q_setSensorDebounceGoingInActiveTimer(long  time) { AbstractSensor::setSensorDebounceGoingInActiveTimer(time); }
inline void py_q_setState(int  s) { AbstractSensor::setState(s); }
inline void py_q_setUseDefaultTimerSettings(bool  boo) { AbstractSensor::setUseDefaultTimerSettings(boo); }
inline bool  py_q_useDefaultTimerSettings() { return AbstractSensor::useDefaultTimerSettings(); }
inline void py_q_useDefaultTimerSettings(bool  boo) { AbstractSensor::useDefaultTimerSettings(boo); }
};

class PythonQtWrapper_AbstractSensor : public QObject
{ Q_OBJECT
public:
public slots:
AbstractSensor* new_AbstractSensor(QObject*  parent = 0);
AbstractSensor* new_AbstractSensor(QString  systemName, QObject*  parent = 0);
AbstractSensor* new_AbstractSensor(QString  systemName, QString  userName, QObject*  parent = 0);
void delete_AbstractSensor(AbstractSensor* obj) { delete obj; } 
   bool  py_q_canInvert(AbstractSensor* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->py_q_canInvert());}
   QString  py_q_describeState(AbstractSensor* theWrappedObject, int  state){  return (((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->py_q_describeState(state));}
   QString  py_q_getBeanType(AbstractSensor* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->py_q_getBeanType());}
   bool  py_q_getInverted(AbstractSensor* theWrappedObject) const{  return (((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->py_q_getInverted());}
   int  py_q_getKnownState(AbstractSensor* theWrappedObject) const{  return (((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->py_q_getKnownState());}
   int  py_q_getRawState(AbstractSensor* theWrappedObject) const{  return (((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->py_q_getRawState());}
   long  py_q_getSensorDebounceGoingActiveTimer(AbstractSensor* theWrappedObject) const{  return (((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->py_q_getSensorDebounceGoingActiveTimer());}
   long  py_q_getSensorDebounceGoingInActiveTimer(AbstractSensor* theWrappedObject) const{  return (((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->py_q_getSensorDebounceGoingInActiveTimer());}
   int  py_q_getState(AbstractSensor* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->py_q_getState());}
   QString  getStateName(AbstractSensor* theWrappedObject, int  arg__1);
   bool  py_q_getUseDefaultTimerSettings(AbstractSensor* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->py_q_getUseDefaultTimerSettings());}
   void sensorDebounce(AbstractSensor* theWrappedObject);
   void py_q_setInverted(AbstractSensor* theWrappedObject, bool  inverted){  (((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->py_q_setInverted(inverted));}
   void py_q_setKnownState(AbstractSensor* theWrappedObject, int  s){  (((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->py_q_setKnownState(s));}
   void setOwnState(AbstractSensor* theWrappedObject, int  s);
   void py_q_setSensorDebounceGoingActiveTimer(AbstractSensor* theWrappedObject, long  time) const{  (((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->py_q_setSensorDebounceGoingActiveTimer(time));}
   void py_q_setSensorDebounceGoingInActiveTimer(AbstractSensor* theWrappedObject, long  time){  (((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->py_q_setSensorDebounceGoingInActiveTimer(time));}
   void py_q_setState(AbstractSensor* theWrappedObject, int  s){  (((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->py_q_setState(s));}
   void py_q_setUseDefaultTimerSettings(AbstractSensor* theWrappedObject, bool  boo){  (((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->py_q_setUseDefaultTimerSettings(boo));}
   bool  py_q_useDefaultTimerSettings(AbstractSensor* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->py_q_useDefaultTimerSettings());}
   void py_q_useDefaultTimerSettings(AbstractSensor* theWrappedObject, bool  boo){  (((PythonQtPublicPromoter_AbstractSensor*)theWrappedObject)->py_q_useDefaultTimerSettings(boo));}
};





class PythonQtShell_AbstractSensorManager : public AbstractSensorManager
{
public:
    PythonQtShell_AbstractSensorManager(QObject*  parent = 0):AbstractSensorManager(parent),_wrapper(NULL) {}
    PythonQtShell_AbstractSensorManager(SystemConnectionMemo*  memo, QObject*  parent = nullptr):AbstractSensorManager(memo, parent),_wrapper(NULL) {}

   ~PythonQtShell_AbstractSensorManager();

virtual void Register(NamedBean*  s) const;
virtual void addDataListener(QObject*  e);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual bool  allowMultipleAdditions(QString  systemName);
virtual void childEvent(QChildEvent*  event);
virtual Sensor*  createNewSensor(QString  arg__1, QString  arg__2);
virtual QString  createSystemName(QString  curAddress, QString  prefix) const throw (JmriException) ;
virtual void customEvent(QEvent*  event);
virtual void deleteBean(NamedBean*  arg__1, QString  arg__2) throw (PropertyVetoException) ;
virtual void deregister(NamedBean*  s) const;
virtual void dispose() const;
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual NamedBean*  getBeanBySystemName(QString  systemName) const;
virtual NamedBean*  getBeanByUserName(QString  arg__1) const;
virtual QString  getBeanTypeHandled(bool  plural) const;
virtual NamedBean*  getBySystemName(QString  key) const;
virtual NamedBean*  getByUserName(QString  key) const;
virtual long  getDefaultSensorDebounceGoingActive();
virtual long  getDefaultSensorDebounceGoingInActive();
virtual QString  getEntryToolTip();
virtual SystemConnectionMemo*  getMemo() const;
virtual NamedBean*  getNamedBean(QString  name) const;
virtual QString  getNamedBeanClass() const;
virtual QSet<NamedBean* >  getNamedBeanSet();
virtual QString  getNextValidAddress(QString  curAddress, QString  prefix);
virtual int  getObjectCount();
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners();
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners(QString  propertyName);
virtual Sensor*  getSensor(QString  name) const;
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList();
virtual QString  getSystemPrefix() const;
virtual int  getXMLOrder() const;
virtual bool  isPullResistanceConfigurable();
virtual QString  makeSystemName(QString  s, bool  logErrors = true, QLocale  locale = QLocale()) const;
virtual Sensor*  newSensor(QString  sysName, QString  userName);
virtual QString  normalizeSystemName(QString  sysName) const;
virtual Sensor*  provide(QString  name) throw (IllegalArgumentException)
;
virtual Sensor*  provideSensor(QString  name);
virtual void removeDataListener(QObject*  e);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void removePropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual void setDefaultSensorDebounceGoingActive(long  timer);
virtual void setDefaultSensorDebounceGoingInActive(long  timer);
virtual void timerEvent(QTimerEvent*  event);
virtual QString  toString();
virtual char  typeLetter() const;
virtual void updateAll() const;
virtual Manager::NameValidity  validSystemNameFormat(QString  systemName) const;
virtual void vetoableChange(PropertyChangeEvent*  evt);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_AbstractSensorManager : public AbstractSensorManager
{ public:
inline Sensor*  promoted_createNewSensor(QString  arg__1, QString  arg__2) { return this->createNewSensor(arg__1, arg__2); }
inline QObject*  promoted_getInstanceBySystemName(QString  systemName) { return this->getInstanceBySystemName(systemName); }
inline QString  promoted_normalizeSystemName(QString  sysName) const { return this->normalizeSystemName(sysName); }
inline bool  py_q_allowMultipleAdditions(QString  systemName) { return AbstractSensorManager::allowMultipleAdditions(systemName); }
inline Sensor*  py_q_createNewSensor(QString  arg__1, QString  arg__2) { return AbstractSensorManager::createNewSensor(arg__1, arg__2); }
inline QString  py_q_createSystemName(QString  curAddress, QString  prefix) const throw (JmriException)  { return AbstractSensorManager::createSystemName(curAddress, prefix); }
inline QString  py_q_getBeanTypeHandled(bool  plural) const { return AbstractSensorManager::getBeanTypeHandled(plural); }
inline NamedBean*  py_q_getBySystemName(QString  key) const { return AbstractSensorManager::getBySystemName(key); }
inline NamedBean*  py_q_getByUserName(QString  key) const { return AbstractSensorManager::getByUserName(key); }
inline long  py_q_getDefaultSensorDebounceGoingActive() { return AbstractSensorManager::getDefaultSensorDebounceGoingActive(); }
inline long  py_q_getDefaultSensorDebounceGoingInActive() { return AbstractSensorManager::getDefaultSensorDebounceGoingInActive(); }
inline QString  py_q_getNextValidAddress(QString  curAddress, QString  prefix) { return AbstractSensorManager::getNextValidAddress(curAddress, prefix); }
inline Sensor*  py_q_getSensor(QString  name) const { return AbstractSensorManager::getSensor(name); }
inline int  py_q_getXMLOrder() const { return AbstractSensorManager::getXMLOrder(); }
inline Sensor*  py_q_newSensor(QString  sysName, QString  userName) { return AbstractSensorManager::newSensor(sysName, userName); }
inline QString  py_q_normalizeSystemName(QString  sysName) const { return AbstractSensorManager::normalizeSystemName(sysName); }
inline Sensor*  py_q_provideSensor(QString  name) { return AbstractSensorManager::provideSensor(name); }
inline void py_q_setDefaultSensorDebounceGoingActive(long  timer) { AbstractSensorManager::setDefaultSensorDebounceGoingActive(timer); }
inline void py_q_setDefaultSensorDebounceGoingInActive(long  timer) { AbstractSensorManager::setDefaultSensorDebounceGoingInActive(timer); }
inline char  py_q_typeLetter() const { return AbstractSensorManager::typeLetter(); }
inline void py_q_updateAll() const { AbstractSensorManager::updateAll(); }
};

class PythonQtWrapper_AbstractSensorManager : public QObject
{ Q_OBJECT
public:
public slots:
AbstractSensorManager* new_AbstractSensorManager(QObject*  parent = 0);
AbstractSensorManager* new_AbstractSensorManager(SystemConnectionMemo*  memo, QObject*  parent = nullptr);
void delete_AbstractSensorManager(AbstractSensorManager* obj) { delete obj; } 
   bool  py_q_allowMultipleAdditions(AbstractSensorManager* theWrappedObject, QString  systemName){  return (((PythonQtPublicPromoter_AbstractSensorManager*)theWrappedObject)->py_q_allowMultipleAdditions(systemName));}
   Sensor*  createNewSensor(AbstractSensorManager* theWrappedObject, QString  arg__1, QString  arg__2);
   Sensor*  py_q_createNewSensor(AbstractSensorManager* theWrappedObject, QString  arg__1, QString  arg__2){  return (((PythonQtPublicPromoter_AbstractSensorManager*)theWrappedObject)->py_q_createNewSensor(arg__1, arg__2));}
   QString  py_q_createSystemName(AbstractSensorManager* theWrappedObject, QString  curAddress, QString  prefix) const throw (JmriException) {  return (((PythonQtPublicPromoter_AbstractSensorManager*)theWrappedObject)->py_q_createSystemName(curAddress, prefix));}
   QString  py_q_getBeanTypeHandled(AbstractSensorManager* theWrappedObject, bool  plural) const{  return (((PythonQtPublicPromoter_AbstractSensorManager*)theWrappedObject)->py_q_getBeanTypeHandled(plural));}
   NamedBean*  py_q_getBySystemName(AbstractSensorManager* theWrappedObject, QString  key) const{  return (((PythonQtPublicPromoter_AbstractSensorManager*)theWrappedObject)->py_q_getBySystemName(key));}
   NamedBean*  py_q_getByUserName(AbstractSensorManager* theWrappedObject, QString  key) const{  return (((PythonQtPublicPromoter_AbstractSensorManager*)theWrappedObject)->py_q_getByUserName(key));}
   long  py_q_getDefaultSensorDebounceGoingActive(AbstractSensorManager* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractSensorManager*)theWrappedObject)->py_q_getDefaultSensorDebounceGoingActive());}
   long  py_q_getDefaultSensorDebounceGoingInActive(AbstractSensorManager* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractSensorManager*)theWrappedObject)->py_q_getDefaultSensorDebounceGoingInActive());}
   QObject*  getInstanceBySystemName(AbstractSensorManager* theWrappedObject, QString  systemName);
   QString  py_q_getNextValidAddress(AbstractSensorManager* theWrappedObject, QString  curAddress, QString  prefix){  return (((PythonQtPublicPromoter_AbstractSensorManager*)theWrappedObject)->py_q_getNextValidAddress(curAddress, prefix));}
   Sensor*  py_q_getSensor(AbstractSensorManager* theWrappedObject, QString  name) const{  return (((PythonQtPublicPromoter_AbstractSensorManager*)theWrappedObject)->py_q_getSensor(name));}
   int  py_q_getXMLOrder(AbstractSensorManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_AbstractSensorManager*)theWrappedObject)->py_q_getXMLOrder());}
   Sensor*  py_q_newSensor(AbstractSensorManager* theWrappedObject, QString  sysName, QString  userName){  return (((PythonQtPublicPromoter_AbstractSensorManager*)theWrappedObject)->py_q_newSensor(sysName, userName));}
   QString  py_q_normalizeSystemName(AbstractSensorManager* theWrappedObject, QString  sysName) const{  return (((PythonQtPublicPromoter_AbstractSensorManager*)theWrappedObject)->py_q_normalizeSystemName(sysName));}
   Sensor*  py_q_provideSensor(AbstractSensorManager* theWrappedObject, QString  name){  return (((PythonQtPublicPromoter_AbstractSensorManager*)theWrappedObject)->py_q_provideSensor(name));}
   void py_q_setDefaultSensorDebounceGoingActive(AbstractSensorManager* theWrappedObject, long  timer){  (((PythonQtPublicPromoter_AbstractSensorManager*)theWrappedObject)->py_q_setDefaultSensorDebounceGoingActive(timer));}
   void py_q_setDefaultSensorDebounceGoingInActive(AbstractSensorManager* theWrappedObject, long  timer){  (((PythonQtPublicPromoter_AbstractSensorManager*)theWrappedObject)->py_q_setDefaultSensorDebounceGoingInActive(timer));}
   char  py_q_typeLetter(AbstractSensorManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_AbstractSensorManager*)theWrappedObject)->py_q_typeLetter());}
   void py_q_updateAll(AbstractSensorManager* theWrappedObject) const{  (((PythonQtPublicPromoter_AbstractSensorManager*)theWrappedObject)->py_q_updateAll());}
    QString py_toString(AbstractSensorManager*);
};





class PythonQtShell_AbstractSerialPortController : public AbstractSerialPortController
{
public:
    PythonQtShell_AbstractSerialPortController(SystemConnectionMemo*  connectionMemo, QObject*  parent = 0):AbstractSerialPortController(connectionMemo, parent),_wrapper(NULL) {}

   ~PythonQtShell_AbstractSerialPortController();

virtual void _connect();
virtual void autoConfigure();
virtual void childEvent(QChildEvent*  event);
virtual QString  className();
virtual void closeConnection() throw( Exception);
virtual void configure();
virtual void configureBaudRate(QString  rate);
virtual void configureOption1(QString  value);
virtual void configureOption2(QString  value);
virtual void configureOption3(QString  value);
virtual void configureOption4(QString  value);
virtual int  currentBaudNumber(QString  currentBaudRate);
virtual void customEvent(QEvent*  event);
virtual void dispose();
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual QString  getAdvertisementName();
virtual QString  getCurrentBaudRate();
virtual QString  getCurrentPortName();
virtual bool  getDisabled();
virtual QString  getHostName();
virtual QDataStream*  getInputStream();
virtual QString  getManufacturer();
virtual bool  getMdnsConfigure();
virtual QString  getOption1Name();
virtual QString  getOption2Name();
virtual QString  getOption3Name();
virtual QString  getOption4Name();
virtual QStringList  getOptionChoices(QString  option);
virtual QString  getOptionDisplayName(QString  option);
virtual QString  getOptionState(QString  option);
virtual QStringList  getOptions();
virtual QDataStream*  getOutputStream();
virtual int  getPort();
virtual QVector<QString >  getPortNames();
virtual QString  getServiceType();
virtual SystemConnectionMemo*  getSystemConnectionMemo() const;
virtual QString  getSystemPrefix();
virtual QString  getUserName();
virtual bool  isDirty();
virtual bool  isOptionAdvanced(QString  option);
virtual bool  isRestartRequired();
virtual QString  openPort(QString  arg__1, QString  arg__2);
virtual void recover();
virtual void resetupConnection();
virtual void setAdvertisementName(QString  arg__1);
virtual void setDisabled(bool  disabled);
virtual void setHostName(QString  arg__1);
virtual void setManufacturer(QString  manufacturer);
virtual void setMdnsConfigure(bool  arg__1);
virtual void setOptionState(QString  option, QString  value);
virtual void setPort(QString  port);
virtual void setServiceType(QString  arg__1);
virtual void setSystemConnectionMemo(SystemConnectionMemo*  connectionMemo);
virtual void setSystemPrefix(QString  systemPrefix);
virtual void setUserName(QString  userName);
virtual bool  status();
virtual void timerEvent(QTimerEvent*  event);
virtual QVector<int >  validBaudNumbers();
virtual QStringList  validBaudRates();

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_AbstractSerialPortController : public AbstractSerialPortController
{ public:
inline void promoted_closeConnection() throw( Exception) { this->closeConnection(); }
inline void promoted_resetupConnection() { this->resetupConnection(); }
inline void py_q__connect() { AbstractSerialPortController::_connect(); }
inline void py_q_closeConnection() throw( Exception) { AbstractSerialPortController::closeConnection(); }
inline void py_q_configureBaudRate(QString  rate) { AbstractSerialPortController::configureBaudRate(rate); }
inline int  py_q_currentBaudNumber(QString  currentBaudRate) { return AbstractSerialPortController::currentBaudNumber(currentBaudRate); }
inline void py_q_dispose() { AbstractSerialPortController::dispose(); }
inline QString  py_q_getCurrentBaudRate() { return AbstractSerialPortController::getCurrentBaudRate(); }
inline QString  py_q_getCurrentPortName() { return AbstractSerialPortController::getCurrentPortName(); }
inline QString  py_q_getOptionState(QString  option) { return AbstractSerialPortController::getOptionState(option); }
inline QVector<QString >  py_q_getPortNames() { return AbstractSerialPortController::getPortNames(); }
inline void py_q_recover() { AbstractSerialPortController::recover(); }
inline void py_q_resetupConnection() { AbstractSerialPortController::resetupConnection(); }
inline void py_q_setDisabled(bool  disabled) { AbstractSerialPortController::setDisabled(disabled); }
inline void py_q_setPort(QString  port) { AbstractSerialPortController::setPort(port); }
inline QVector<int >  py_q_validBaudNumbers() { return AbstractSerialPortController::validBaudNumbers(); }
inline QStringList  py_q_validBaudRates() { return AbstractSerialPortController::validBaudRates(); }
};

class PythonQtWrapper_AbstractSerialPortController : public QObject
{ Q_OBJECT
public:
public slots:
AbstractSerialPortController* new_AbstractSerialPortController(SystemConnectionMemo*  connectionMemo, QObject*  parent = 0);
void delete_AbstractSerialPortController(AbstractSerialPortController* obj) { delete obj; } 
   void py_q__connect(AbstractSerialPortController* theWrappedObject){  (((PythonQtPublicPromoter_AbstractSerialPortController*)theWrappedObject)->py_q__connect());}
   void closeConnection(AbstractSerialPortController* theWrappedObject) throw( Exception);
   void py_q_closeConnection(AbstractSerialPortController* theWrappedObject) throw( Exception){  (((PythonQtPublicPromoter_AbstractSerialPortController*)theWrappedObject)->py_q_closeConnection());}
   void py_q_configureBaudRate(AbstractSerialPortController* theWrappedObject, QString  rate){  (((PythonQtPublicPromoter_AbstractSerialPortController*)theWrappedObject)->py_q_configureBaudRate(rate));}
   int  currentBaudNumber(AbstractSerialPortController* theWrappedObject, QString  currentBaudRate);
   int  py_q_currentBaudNumber(AbstractSerialPortController* theWrappedObject, QString  currentBaudRate){  return (((PythonQtPublicPromoter_AbstractSerialPortController*)theWrappedObject)->py_q_currentBaudNumber(currentBaudRate));}
   void py_q_dispose(AbstractSerialPortController* theWrappedObject){  (((PythonQtPublicPromoter_AbstractSerialPortController*)theWrappedObject)->py_q_dispose());}
   QString  py_q_getCurrentBaudRate(AbstractSerialPortController* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractSerialPortController*)theWrappedObject)->py_q_getCurrentBaudRate());}
   QString  py_q_getCurrentPortName(AbstractSerialPortController* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractSerialPortController*)theWrappedObject)->py_q_getCurrentPortName());}
   QString  py_q_getOptionState(AbstractSerialPortController* theWrappedObject, QString  option){  return (((PythonQtPublicPromoter_AbstractSerialPortController*)theWrappedObject)->py_q_getOptionState(option));}
   QVector<QString >  py_q_getPortNames(AbstractSerialPortController* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractSerialPortController*)theWrappedObject)->py_q_getPortNames());}
   void reconnect(AbstractSerialPortController* theWrappedObject);
   void py_q_recover(AbstractSerialPortController* theWrappedObject){  (((PythonQtPublicPromoter_AbstractSerialPortController*)theWrappedObject)->py_q_recover());}
   void resetupConnection(AbstractSerialPortController* theWrappedObject);
   void py_q_resetupConnection(AbstractSerialPortController* theWrappedObject){  (((PythonQtPublicPromoter_AbstractSerialPortController*)theWrappedObject)->py_q_resetupConnection());}
   void py_q_setDisabled(AbstractSerialPortController* theWrappedObject, bool  disabled){  (((PythonQtPublicPromoter_AbstractSerialPortController*)theWrappedObject)->py_q_setDisabled(disabled));}
   void py_q_setPort(AbstractSerialPortController* theWrappedObject, QString  port){  (((PythonQtPublicPromoter_AbstractSerialPortController*)theWrappedObject)->py_q_setPort(port));}
   QVector<int >  validBaudNumbers(AbstractSerialPortController* theWrappedObject);
   QVector<int >  py_q_validBaudNumbers(AbstractSerialPortController* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractSerialPortController*)theWrappedObject)->py_q_validBaudNumbers());}
   QStringList  py_q_validBaudRates(AbstractSerialPortController* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractSerialPortController*)theWrappedObject)->py_q_validBaudRates());}
};





class PythonQtShell_AbstractShutDownTask : public AbstractShutDownTask
{
public:
    PythonQtShell_AbstractShutDownTask(QString  name, QObject*  parent = 0):AbstractShutDownTask(name, parent),_wrapper(NULL) {}

   ~PythonQtShell_AbstractShutDownTask();

virtual bool  call() throw (Exception) ;
virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual bool  execute();
virtual QString  getName();
virtual bool  isComplete();
virtual bool  isParallel();
virtual bool  isShutdownAllowed();
virtual void run();
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_AbstractShutDownTask : public AbstractShutDownTask
{ public:
inline QString  py_q_getName() { return AbstractShutDownTask::getName(); }
};

class PythonQtWrapper_AbstractShutDownTask : public QObject
{ Q_OBJECT
public:
public slots:
AbstractShutDownTask* new_AbstractShutDownTask(QString  name, QObject*  parent = 0);
void delete_AbstractShutDownTask(AbstractShutDownTask* obj) { delete obj; } 
   QString  py_q_getName(AbstractShutDownTask* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractShutDownTask*)theWrappedObject)->py_q_getName());}
};





class PythonQtShell_AbstractTurnout : public AbstractTurnout
{
public:
    PythonQtShell_AbstractTurnout(QObject*  parent = 0):AbstractTurnout(parent),_wrapper(NULL) {}
    PythonQtShell_AbstractTurnout(QString  systemName, QObject*  parent = 0):AbstractTurnout(systemName, parent),_wrapper(NULL) {}
    PythonQtShell_AbstractTurnout(QString  systemName, QString  userName, QObject*  parent = 0):AbstractTurnout(systemName, userName, parent),_wrapper(NULL) {}

   ~PythonQtShell_AbstractTurnout();

virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(PropertyChangeListener*  l, QString  beanRef, const QString  listenerRef);
virtual void addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  l, QString  beanRef, QString  listenerRef);
virtual void addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual bool  canInvert() const;
virtual bool  canLock(int  turnoutLockout);
virtual void childEvent(QChildEvent*  event);
virtual int  compareSystemNameSuffix(QString  suffix1, QString  suffix2, NamedBean*  n);
virtual int  compareTo(NamedBean*  n2);
virtual void customEvent(QEvent*  event);
virtual QString  describeState(int  state);
virtual void dispose();
virtual void enableLockOperation(int  turnoutLockout, bool  enabled);
virtual bool  equals(QObject*  obj);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual void forwardCommandChangeToLayout();
virtual void forwardCommandChangeToLayout(int  s);
virtual QString  getBeanType();
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
virtual QString  getFullyFormattedDisplayName();
virtual bool  getInhibitOperation();
virtual bool  getInverted();
virtual int  getKnownState();
virtual QString  getListenerRef(PropertyChangeListener*  l);
virtual QList<QString >*  getListenerRefs();
virtual bool  getLocked(int  turnoutLockout);
virtual int  getNumPropertyChangeListeners();
virtual int  getNumberOutputBits();
virtual int  getPossibleLockModes();
virtual QVariant  getProperty(QString  key);
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners();
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners(QString  name);
virtual QVector<PropertyChangeListener* >  getPropertyChangeListenersByReference(QString  propertyName);
virtual QSet<QString >  getPropertyKeys();
virtual bool  getReportLocked();
virtual Sensor*  getSecondSensor();
virtual int  getState();
virtual float  getStraightLimit();
virtual QString  getStraightSpeed();
virtual QString  getSystemName() const;
virtual TurnoutOperation*  getTurnoutOperation();
virtual QString  getUserName() const;
virtual QStringList  getValidDecoderNames();
virtual QVector<QString >  getValidFeedbackNames();
virtual int  getValidFeedbackTypes();
virtual uint  hashCode();
virtual bool  isConsistentState();
virtual void provideFirstFeedbackSensor(QString  pName) throw(JmriException) ;
virtual void provideSecondFeedbackSensor(QString  pName) throw(JmriException) ;
virtual void removeProperty(QString  key);
virtual void removePropertyChangeListener(PropertyChangeListener*  listener);
virtual void removePropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual void requestUpdateFromLayout();
virtual void setBinaryOutput(bool  state);
virtual void setCommandedState(int  s);
virtual void setComment(QString  comment);
virtual void setControlType(int  num);
virtual void setDecoderName(QString  decoderName);
virtual void setDivergingSpeed(QString  s) const throw(JmriException) ;
virtual void setFeedbackMode(QString  mode) throw(IllegalArgumentException) ;
virtual void setFeedbackMode(int  mode) throw(IllegalArgumentException) ;
virtual void setInhibitOperation(bool  io);
virtual void setInitialKnownStateFromFeedback();
virtual void setInverted(bool  inverted);
virtual void setLocked(int  turnoutLockout, bool  locked);
virtual void setNumberOutputBits(int  num);
virtual void setProperty(QString  key, QVariant  value);
virtual void setReportLocked(bool  reportLocked);
virtual void setState(int  s);
virtual void setStraightSpeed(QString  s) const throw(JmriException) ;
virtual void setTurnoutOperation(TurnoutOperation*  toper);
virtual void setUserName(QString  s) throw (NamedBean::BadUserNameException) ;
virtual void timerEvent(QTimerEvent*  event);
virtual void turnoutPushbuttonLockout(bool  locked);
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);
virtual void vetoableChange(PropertyChangeEvent*  evt) throw (PropertyVetoException) ;

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_AbstractTurnout : public AbstractTurnout
{ public:
inline void promoted_forwardCommandChangeToLayout() { this->forwardCommandChangeToLayout(); }
inline void promoted_forwardCommandChangeToLayout(int  s) { this->forwardCommandChangeToLayout(s); }
inline int  promoted_getFeedbackModeForOperation() { return this->getFeedbackModeForOperation(); }
inline void promoted_newCommandedState(int  s) { this->newCommandedState(s); }
inline void promoted_newKnownState(int  s) { this->newKnownState(s); }
inline void promoted_operationPropertyChange(PropertyChangeEvent*  evt) { this->operationPropertyChange(evt); }
inline void promoted_sensorPropertyChange(PropertyChangeEvent*  evt) { this->sensorPropertyChange(evt); }
inline void promoted_turnoutPushbuttonLockout() { this->turnoutPushbuttonLockout(); }
inline void promoted_turnoutPushbuttonLockout(bool  locked) { this->turnoutPushbuttonLockout(locked); }
inline bool  py_q_canInvert() const { return AbstractTurnout::canInvert(); }
inline bool  py_q_canLock(int  turnoutLockout) { return AbstractTurnout::canLock(turnoutLockout); }
inline QString  py_q_describeState(int  state) { return AbstractTurnout::describeState(state); }
inline void py_q_dispose() { AbstractTurnout::dispose(); }
inline void py_q_enableLockOperation(int  turnoutLockout, bool  enabled) { AbstractTurnout::enableLockOperation(turnoutLockout, enabled); }
inline void py_q_forwardCommandChangeToLayout() { AbstractTurnout::forwardCommandChangeToLayout(); }
inline void py_q_forwardCommandChangeToLayout(int  s) { AbstractTurnout::forwardCommandChangeToLayout(s); }
inline QString  py_q_getBeanType() { return AbstractTurnout::getBeanType(); }
inline int  py_q_getCommandedState() { return AbstractTurnout::getCommandedState(); }
inline int  py_q_getControlType() { return AbstractTurnout::getControlType(); }
inline QString  py_q_getDecoderName() { return AbstractTurnout::getDecoderName(); }
inline float  py_q_getDivergingLimit() { return AbstractTurnout::getDivergingLimit(); }
inline QString  py_q_getDivergingSpeed() { return AbstractTurnout::getDivergingSpeed(); }
inline int  py_q_getFeedbackMode() { return AbstractTurnout::getFeedbackMode(); }
inline QString  py_q_getFeedbackModeName() { return AbstractTurnout::getFeedbackModeName(); }
inline Sensor*  py_q_getFirstSensor() { return AbstractTurnout::getFirstSensor(); }
inline bool  py_q_getInhibitOperation() { return AbstractTurnout::getInhibitOperation(); }
inline bool  py_q_getInverted() { return AbstractTurnout::getInverted(); }
inline int  py_q_getKnownState() { return AbstractTurnout::getKnownState(); }
inline bool  py_q_getLocked(int  turnoutLockout) { return AbstractTurnout::getLocked(turnoutLockout); }
inline int  py_q_getNumberOutputBits() { return AbstractTurnout::getNumberOutputBits(); }
inline bool  py_q_getReportLocked() { return AbstractTurnout::getReportLocked(); }
inline Sensor*  py_q_getSecondSensor() { return AbstractTurnout::getSecondSensor(); }
inline int  py_q_getState() { return AbstractTurnout::getState(); }
inline float  py_q_getStraightLimit() { return AbstractTurnout::getStraightLimit(); }
inline QString  py_q_getStraightSpeed() { return AbstractTurnout::getStraightSpeed(); }
inline TurnoutOperation*  py_q_getTurnoutOperation() { return AbstractTurnout::getTurnoutOperation(); }
inline QStringList  py_q_getValidDecoderNames() { return AbstractTurnout::getValidDecoderNames(); }
inline QVector<QString >  py_q_getValidFeedbackNames() { return AbstractTurnout::getValidFeedbackNames(); }
inline int  py_q_getValidFeedbackTypes() { return AbstractTurnout::getValidFeedbackTypes(); }
inline bool  py_q_isConsistentState() { return AbstractTurnout::isConsistentState(); }
inline void py_q_provideFirstFeedbackSensor(QString  pName) throw(JmriException)  { AbstractTurnout::provideFirstFeedbackSensor(pName); }
inline void py_q_provideSecondFeedbackSensor(QString  pName) throw(JmriException)  { AbstractTurnout::provideSecondFeedbackSensor(pName); }
inline void py_q_requestUpdateFromLayout() { AbstractTurnout::requestUpdateFromLayout(); }
inline void py_q_setBinaryOutput(bool  state) { AbstractTurnout::setBinaryOutput(state); }
inline void py_q_setCommandedState(int  s) { AbstractTurnout::setCommandedState(s); }
inline void py_q_setControlType(int  num) { AbstractTurnout::setControlType(num); }
inline void py_q_setDecoderName(QString  decoderName) { AbstractTurnout::setDecoderName(decoderName); }
inline void py_q_setDivergingSpeed(QString  s) const throw(JmriException)  { AbstractTurnout::setDivergingSpeed(s); }
inline void py_q_setFeedbackMode(QString  mode) throw(IllegalArgumentException)  { AbstractTurnout::setFeedbackMode(mode); }
inline void py_q_setFeedbackMode(int  mode) throw(IllegalArgumentException)  { AbstractTurnout::setFeedbackMode(mode); }
inline void py_q_setInhibitOperation(bool  io) { AbstractTurnout::setInhibitOperation(io); }
inline void py_q_setInitialKnownStateFromFeedback() { AbstractTurnout::setInitialKnownStateFromFeedback(); }
inline void py_q_setInverted(bool  inverted) { AbstractTurnout::setInverted(inverted); }
inline void py_q_setLocked(int  turnoutLockout, bool  locked) { AbstractTurnout::setLocked(turnoutLockout, locked); }
inline void py_q_setNumberOutputBits(int  num) { AbstractTurnout::setNumberOutputBits(num); }
inline void py_q_setReportLocked(bool  reportLocked) { AbstractTurnout::setReportLocked(reportLocked); }
inline void py_q_setState(int  s) { AbstractTurnout::setState(s); }
inline void py_q_setStraightSpeed(QString  s) const throw(JmriException)  { AbstractTurnout::setStraightSpeed(s); }
inline void py_q_setTurnoutOperation(TurnoutOperation*  toper) { AbstractTurnout::setTurnoutOperation(toper); }
inline void py_q_turnoutPushbuttonLockout(bool  locked) { AbstractTurnout::turnoutPushbuttonLockout(locked); }
};

class PythonQtWrapper_AbstractTurnout : public QObject
{ Q_OBJECT
public:
public slots:
AbstractTurnout* new_AbstractTurnout(QObject*  parent = 0);
AbstractTurnout* new_AbstractTurnout(QString  systemName, QObject*  parent = 0);
AbstractTurnout* new_AbstractTurnout(QString  systemName, QString  userName, QObject*  parent = 0);
void delete_AbstractTurnout(AbstractTurnout* obj) { delete obj; } 
   bool  py_q_canInvert(AbstractTurnout* theWrappedObject) const{  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_canInvert());}
   bool  py_q_canLock(AbstractTurnout* theWrappedObject, int  turnoutLockout){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_canLock(turnoutLockout));}
   QString  py_q_describeState(AbstractTurnout* theWrappedObject, int  state){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_describeState(state));}
   void py_q_dispose(AbstractTurnout* theWrappedObject){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_dispose());}
   void py_q_enableLockOperation(AbstractTurnout* theWrappedObject, int  turnoutLockout, bool  enabled){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_enableLockOperation(turnoutLockout, enabled));}
   void forwardCommandChangeToLayout(AbstractTurnout* theWrappedObject);
   void py_q_forwardCommandChangeToLayout(AbstractTurnout* theWrappedObject){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_forwardCommandChangeToLayout());}
   void forwardCommandChangeToLayout(AbstractTurnout* theWrappedObject, int  s);
   void py_q_forwardCommandChangeToLayout(AbstractTurnout* theWrappedObject, int  s){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_forwardCommandChangeToLayout(s));}
   QString  py_q_getBeanType(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getBeanType());}
   int  py_q_getCommandedState(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getCommandedState());}
   int  py_q_getControlType(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getControlType());}
   QString  py_q_getDecoderName(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getDecoderName());}
   float  py_q_getDivergingLimit(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getDivergingLimit());}
   QString  py_q_getDivergingSpeed(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getDivergingSpeed());}
   int  py_q_getFeedbackMode(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getFeedbackMode());}
   int  getFeedbackModeForOperation(AbstractTurnout* theWrappedObject);
   QString  py_q_getFeedbackModeName(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getFeedbackModeName());}
   Sensor*  py_q_getFirstSensor(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getFirstSensor());}
   bool  py_q_getInhibitOperation(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getInhibitOperation());}
   bool  py_q_getInverted(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getInverted());}
   int  py_q_getKnownState(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getKnownState());}
   bool  py_q_getLocked(AbstractTurnout* theWrappedObject, int  turnoutLockout){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getLocked(turnoutLockout));}
   int  py_q_getNumberOutputBits(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getNumberOutputBits());}
   bool  py_q_getReportLocked(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getReportLocked());}
   Sensor*  py_q_getSecondSensor(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getSecondSensor());}
   int  py_q_getState(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getState());}
   float  py_q_getStraightLimit(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getStraightLimit());}
   QString  py_q_getStraightSpeed(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getStraightSpeed());}
   TurnoutOperation*  py_q_getTurnoutOperation(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getTurnoutOperation());}
   QStringList  py_q_getValidDecoderNames(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getValidDecoderNames());}
   QVector<QString >  py_q_getValidFeedbackNames(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getValidFeedbackNames());}
   int  py_q_getValidFeedbackTypes(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getValidFeedbackTypes());}
   bool  py_q_isConsistentState(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_isConsistentState());}
   void newCommandedState(AbstractTurnout* theWrappedObject, int  s);
   void newKnownState(AbstractTurnout* theWrappedObject, int  s);
   void operationPropertyChange(AbstractTurnout* theWrappedObject, PropertyChangeEvent*  evt);
   void py_q_provideFirstFeedbackSensor(AbstractTurnout* theWrappedObject, QString  pName) throw(JmriException) {  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_provideFirstFeedbackSensor(pName));}
   void py_q_provideSecondFeedbackSensor(AbstractTurnout* theWrappedObject, QString  pName) throw(JmriException) {  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_provideSecondFeedbackSensor(pName));}
   void py_q_requestUpdateFromLayout(AbstractTurnout* theWrappedObject){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_requestUpdateFromLayout());}
   void sensorPropertyChange(AbstractTurnout* theWrappedObject, PropertyChangeEvent*  evt);
   void py_q_setBinaryOutput(AbstractTurnout* theWrappedObject, bool  state){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setBinaryOutput(state));}
   void py_q_setCommandedState(AbstractTurnout* theWrappedObject, int  s){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setCommandedState(s));}
   void py_q_setControlType(AbstractTurnout* theWrappedObject, int  num){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setControlType(num));}
   void py_q_setDecoderName(AbstractTurnout* theWrappedObject, QString  decoderName){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setDecoderName(decoderName));}
   void py_q_setDivergingSpeed(AbstractTurnout* theWrappedObject, QString  s) const throw(JmriException) {  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setDivergingSpeed(s));}
   void py_q_setFeedbackMode(AbstractTurnout* theWrappedObject, QString  mode) throw(IllegalArgumentException) {  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setFeedbackMode(mode));}
   void py_q_setFeedbackMode(AbstractTurnout* theWrappedObject, int  mode) throw(IllegalArgumentException) {  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setFeedbackMode(mode));}
   void py_q_setInhibitOperation(AbstractTurnout* theWrappedObject, bool  io){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setInhibitOperation(io));}
   void py_q_setInitialKnownStateFromFeedback(AbstractTurnout* theWrappedObject){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setInitialKnownStateFromFeedback());}
   void py_q_setInverted(AbstractTurnout* theWrappedObject, bool  inverted){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setInverted(inverted));}
   void setKnownStateToCommanded(AbstractTurnout* theWrappedObject);
   void py_q_setLocked(AbstractTurnout* theWrappedObject, int  turnoutLockout, bool  locked){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setLocked(turnoutLockout, locked));}
   void py_q_setNumberOutputBits(AbstractTurnout* theWrappedObject, int  num){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setNumberOutputBits(num));}
   void py_q_setReportLocked(AbstractTurnout* theWrappedObject, bool  reportLocked){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setReportLocked(reportLocked));}
   void py_q_setState(AbstractTurnout* theWrappedObject, int  s){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setState(s));}
   void py_q_setStraightSpeed(AbstractTurnout* theWrappedObject, QString  s) const throw(JmriException) {  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setStraightSpeed(s));}
   void py_q_setTurnoutOperation(AbstractTurnout* theWrappedObject, TurnoutOperation*  toper){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setTurnoutOperation(toper));}
   void turnoutPushbuttonLockout(AbstractTurnout* theWrappedObject);
   void turnoutPushbuttonLockout(AbstractTurnout* theWrappedObject, bool  locked);
   void py_q_turnoutPushbuttonLockout(AbstractTurnout* theWrappedObject, bool  locked){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_turnoutPushbuttonLockout(locked));}
};





class PythonQtShell_AbstractTurnoutManager : public AbstractTurnoutManager
{
public:
    PythonQtShell_AbstractTurnoutManager(SystemConnectionMemo*  memo, QObject*  parent = 0):AbstractTurnoutManager(memo, parent),_wrapper(NULL) {}

   ~PythonQtShell_AbstractTurnoutManager();

virtual void Register(NamedBean*  s) const;
virtual void addDataListener(QObject*  e);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual bool  allowMultipleAdditions(QString  systemName);
virtual int  askControlType(QString  systemName);
virtual int  askNumControlBits(QString  systemName);
virtual void childEvent(QChildEvent*  event);
virtual Turnout*  createNewTurnout(QString  systemName, QString  userName) const;
virtual QString  createSystemName(QString  curAddress, QString  prefix) const;
virtual void customEvent(QEvent*  event);
virtual void deleteBean(NamedBean*  arg__1, QString  arg__2) throw (PropertyVetoException) ;
virtual void deregister(NamedBean*  s) const;
virtual void dispose();
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual NamedBean*  getBeanBySystemName(QString  systemName) const;
virtual NamedBean*  getBeanByUserName(QString  arg__1) const;
virtual QString  getBeanTypeHandled(bool  plural) const;
virtual Turnout*  getBySystemName(QString  name) const;
virtual Turnout*  getByUserName(QString  key) const;
virtual QString  getClosedText();
virtual QString  getDefaultClosedSpeed() const;
virtual QString  getDefaultThrownSpeed() const;
virtual QString  getEntryToolTip();
virtual SystemConnectionMemo*  getMemo() const;
virtual NamedBean*  getNamedBean(QString  name) const;
virtual QString  getNamedBeanClass() const;
virtual QSet<NamedBean* >  getNamedBeanSet();
virtual QString  getNextValidAddress(QString  curAddress, QString  prefix) const;
virtual int  getObjectCount();
virtual int  getOutputInterval();
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners();
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners(QString  propertyName);
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList();
virtual QString  getSystemPrefix() const;
virtual QString  getThrownText();
virtual Turnout*  getTurnout(QString  name) const;
virtual QStringList  getValidOperationTypes();
virtual int  getXMLOrder() const;
virtual bool  isControlTypeSupported(QString  systemName);
virtual bool  isNumControlBitsSupported(QString  systemName);
virtual QString  makeSystemName(QString  s, bool  logErrors = true, QLocale  locale = QLocale()) const;
virtual Turnout*  newTurnout(QString  systemName, QString  userName) const;
virtual QString  normalizeSystemName(QString  inputName) const;
virtual void propertyChange(PropertyChangeEvent*  e);
virtual Turnout*  provide(QString  name) const throw (IllegalArgumentException) ;
virtual Turnout*  provideTurnout(QString  name) const;
virtual void removeDataListener(QObject*  e);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void removePropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual void setDefaultClosedSpeed(QString  speed) const;
virtual void setDefaultThrownSpeed(QString  speed) const;
virtual void setOutputInterval(int  newInterval);
virtual void timerEvent(QTimerEvent*  event);
virtual QString  toString();
virtual char  typeLetter() const;
virtual Manager::NameValidity  validSystemNameFormat(QString  systemName) const;
virtual void vetoableChange(PropertyChangeEvent*  evt);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_AbstractTurnoutManager : public AbstractTurnoutManager
{ public:
inline Turnout*  promoted_createNewTurnout(QString  systemName, QString  userName) const { return this->createNewTurnout(systemName, userName); }
inline bool  py_q_allowMultipleAdditions(QString  systemName) { return AbstractTurnoutManager::allowMultipleAdditions(systemName); }
inline int  py_q_askControlType(QString  systemName) { return AbstractTurnoutManager::askControlType(systemName); }
inline int  py_q_askNumControlBits(QString  systemName) { return AbstractTurnoutManager::askNumControlBits(systemName); }
inline Turnout*  py_q_createNewTurnout(QString  systemName, QString  userName) const { return this->createNewTurnout(systemName, userName); }
inline QString  py_q_createSystemName(QString  curAddress, QString  prefix) const { return AbstractTurnoutManager::createSystemName(curAddress, prefix); }
inline QString  py_q_getBeanTypeHandled(bool  plural) const { return AbstractTurnoutManager::getBeanTypeHandled(plural); }
inline Turnout*  py_q_getBySystemName(QString  name) const { return AbstractTurnoutManager::getBySystemName(name); }
inline Turnout*  py_q_getByUserName(QString  key) const { return AbstractTurnoutManager::getByUserName(key); }
inline QString  py_q_getClosedText() { return AbstractTurnoutManager::getClosedText(); }
inline QString  py_q_getDefaultClosedSpeed() const { return AbstractTurnoutManager::getDefaultClosedSpeed(); }
inline QString  py_q_getDefaultThrownSpeed() const { return AbstractTurnoutManager::getDefaultThrownSpeed(); }
inline QString  py_q_getEntryToolTip() { return AbstractTurnoutManager::getEntryToolTip(); }
inline QString  py_q_getNextValidAddress(QString  curAddress, QString  prefix) const { return AbstractTurnoutManager::getNextValidAddress(curAddress, prefix); }
inline int  py_q_getOutputInterval() { return AbstractTurnoutManager::getOutputInterval(); }
inline QString  py_q_getThrownText() { return AbstractTurnoutManager::getThrownText(); }
inline Turnout*  py_q_getTurnout(QString  name) const { return AbstractTurnoutManager::getTurnout(name); }
inline QStringList  py_q_getValidOperationTypes() { return AbstractTurnoutManager::getValidOperationTypes(); }
inline int  py_q_getXMLOrder() const { return AbstractTurnoutManager::getXMLOrder(); }
inline bool  py_q_isControlTypeSupported(QString  systemName) { return AbstractTurnoutManager::isControlTypeSupported(systemName); }
inline bool  py_q_isNumControlBitsSupported(QString  systemName) { return AbstractTurnoutManager::isNumControlBitsSupported(systemName); }
inline Turnout*  py_q_newTurnout(QString  systemName, QString  userName) const { return AbstractTurnoutManager::newTurnout(systemName, userName); }
inline Turnout*  py_q_provideTurnout(QString  name) const { return AbstractTurnoutManager::provideTurnout(name); }
inline void py_q_setDefaultClosedSpeed(QString  speed) const { AbstractTurnoutManager::setDefaultClosedSpeed(speed); }
inline void py_q_setDefaultThrownSpeed(QString  speed) const { AbstractTurnoutManager::setDefaultThrownSpeed(speed); }
inline void py_q_setOutputInterval(int  newInterval) { AbstractTurnoutManager::setOutputInterval(newInterval); }
inline char  py_q_typeLetter() const { return AbstractTurnoutManager::typeLetter(); }
};

class PythonQtWrapper_AbstractTurnoutManager : public QObject
{ Q_OBJECT
public:
public slots:
AbstractTurnoutManager* new_AbstractTurnoutManager(SystemConnectionMemo*  memo, QObject*  parent = 0);
void delete_AbstractTurnoutManager(AbstractTurnoutManager* obj) { delete obj; } 
   bool  py_q_allowMultipleAdditions(AbstractTurnoutManager* theWrappedObject, QString  systemName){  return (((PythonQtPublicPromoter_AbstractTurnoutManager*)theWrappedObject)->py_q_allowMultipleAdditions(systemName));}
   int  py_q_askControlType(AbstractTurnoutManager* theWrappedObject, QString  systemName){  return (((PythonQtPublicPromoter_AbstractTurnoutManager*)theWrappedObject)->py_q_askControlType(systemName));}
   int  py_q_askNumControlBits(AbstractTurnoutManager* theWrappedObject, QString  systemName){  return (((PythonQtPublicPromoter_AbstractTurnoutManager*)theWrappedObject)->py_q_askNumControlBits(systemName));}
   Turnout*  createNewTurnout(AbstractTurnoutManager* theWrappedObject, QString  systemName, QString  userName) const;
   Turnout*  py_q_createNewTurnout(AbstractTurnoutManager* theWrappedObject, QString  systemName, QString  userName) const{  return (((PythonQtPublicPromoter_AbstractTurnoutManager*)theWrappedObject)->py_q_createNewTurnout(systemName, userName));}
   QString  py_q_createSystemName(AbstractTurnoutManager* theWrappedObject, QString  curAddress, QString  prefix) const{  return (((PythonQtPublicPromoter_AbstractTurnoutManager*)theWrappedObject)->py_q_createSystemName(curAddress, prefix));}
   QString  py_q_getBeanTypeHandled(AbstractTurnoutManager* theWrappedObject, bool  plural) const{  return (((PythonQtPublicPromoter_AbstractTurnoutManager*)theWrappedObject)->py_q_getBeanTypeHandled(plural));}
   Turnout*  py_q_getBySystemName(AbstractTurnoutManager* theWrappedObject, QString  name) const{  return (((PythonQtPublicPromoter_AbstractTurnoutManager*)theWrappedObject)->py_q_getBySystemName(name));}
   Turnout*  py_q_getByUserName(AbstractTurnoutManager* theWrappedObject, QString  key) const{  return (((PythonQtPublicPromoter_AbstractTurnoutManager*)theWrappedObject)->py_q_getByUserName(key));}
   QString  py_q_getClosedText(AbstractTurnoutManager* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnoutManager*)theWrappedObject)->py_q_getClosedText());}
   QString  py_q_getDefaultClosedSpeed(AbstractTurnoutManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_AbstractTurnoutManager*)theWrappedObject)->py_q_getDefaultClosedSpeed());}
   QString  py_q_getDefaultThrownSpeed(AbstractTurnoutManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_AbstractTurnoutManager*)theWrappedObject)->py_q_getDefaultThrownSpeed());}
   QString  py_q_getEntryToolTip(AbstractTurnoutManager* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnoutManager*)theWrappedObject)->py_q_getEntryToolTip());}
   QString  py_q_getNextValidAddress(AbstractTurnoutManager* theWrappedObject, QString  curAddress, QString  prefix) const{  return (((PythonQtPublicPromoter_AbstractTurnoutManager*)theWrappedObject)->py_q_getNextValidAddress(curAddress, prefix));}
   int  py_q_getOutputInterval(AbstractTurnoutManager* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnoutManager*)theWrappedObject)->py_q_getOutputInterval());}
   QString  py_q_getThrownText(AbstractTurnoutManager* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnoutManager*)theWrappedObject)->py_q_getThrownText());}
   Turnout*  py_q_getTurnout(AbstractTurnoutManager* theWrappedObject, QString  name) const{  return (((PythonQtPublicPromoter_AbstractTurnoutManager*)theWrappedObject)->py_q_getTurnout(name));}
   QStringList  py_q_getValidOperationTypes(AbstractTurnoutManager* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnoutManager*)theWrappedObject)->py_q_getValidOperationTypes());}
   int  py_q_getXMLOrder(AbstractTurnoutManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_AbstractTurnoutManager*)theWrappedObject)->py_q_getXMLOrder());}
   bool  py_q_isControlTypeSupported(AbstractTurnoutManager* theWrappedObject, QString  systemName){  return (((PythonQtPublicPromoter_AbstractTurnoutManager*)theWrappedObject)->py_q_isControlTypeSupported(systemName));}
   bool  py_q_isNumControlBitsSupported(AbstractTurnoutManager* theWrappedObject, QString  systemName){  return (((PythonQtPublicPromoter_AbstractTurnoutManager*)theWrappedObject)->py_q_isNumControlBitsSupported(systemName));}
   Turnout*  py_q_newTurnout(AbstractTurnoutManager* theWrappedObject, QString  systemName, QString  userName) const{  return (((PythonQtPublicPromoter_AbstractTurnoutManager*)theWrappedObject)->py_q_newTurnout(systemName, userName));}
   Turnout*  py_q_provideTurnout(AbstractTurnoutManager* theWrappedObject, QString  name) const{  return (((PythonQtPublicPromoter_AbstractTurnoutManager*)theWrappedObject)->py_q_provideTurnout(name));}
   void py_q_setDefaultClosedSpeed(AbstractTurnoutManager* theWrappedObject, QString  speed) const{  (((PythonQtPublicPromoter_AbstractTurnoutManager*)theWrappedObject)->py_q_setDefaultClosedSpeed(speed));}
   void py_q_setDefaultThrownSpeed(AbstractTurnoutManager* theWrappedObject, QString  speed) const{  (((PythonQtPublicPromoter_AbstractTurnoutManager*)theWrappedObject)->py_q_setDefaultThrownSpeed(speed));}
   void py_q_setOutputInterval(AbstractTurnoutManager* theWrappedObject, int  newInterval){  (((PythonQtPublicPromoter_AbstractTurnoutManager*)theWrappedObject)->py_q_setOutputInterval(newInterval));}
   char  py_q_typeLetter(AbstractTurnoutManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_AbstractTurnoutManager*)theWrappedObject)->py_q_typeLetter());}
    QString py_toString(AbstractTurnoutManager*);
};





class PythonQtShell_Audio : public Audio
{
public:
    PythonQtShell_Audio(QString  systemName, QObject*  parent = 0):Audio(systemName, parent),_wrapper(NULL) {}
    PythonQtShell_Audio(QString  systemName, QString  userName, QObject*  parent = 0):Audio(systemName, userName, parent),_wrapper(NULL) {}

   ~PythonQtShell_Audio();

virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(PropertyChangeListener*  l, QString  beanRef, const QString  listenerRef);
virtual void addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  l, QString  beanRef, QString  listenerRef);
virtual void addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual void childEvent(QChildEvent*  event);
virtual int  compareSystemNameSuffix(QString  suffix1, QString  suffix2, NamedBean*  n);
virtual int  compareTo(NamedBean*  n2);
virtual void customEvent(QEvent*  event);
virtual QString  describeState(int  state);
virtual void dispose();
virtual bool  equals(QObject*  obj);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual QString  getBeanType();
virtual QString  getComment();
virtual QString  getDisplayName();
virtual QString  getFullyFormattedDisplayName();
virtual QString  getListenerRef(PropertyChangeListener*  l);
virtual QList<QString >*  getListenerRefs();
virtual int  getNumPropertyChangeListeners();
virtual QVariant  getProperty(QString  key);
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners();
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners(QString  name);
virtual QVector<PropertyChangeListener* >  getPropertyChangeListenersByReference(QString  propertyName);
virtual QSet<QString >  getPropertyKeys();
virtual int  getState();
virtual QChar  getSubType();
virtual QString  getSystemName() const;
virtual QString  getUserName() const;
virtual uint  hashCode();
virtual void removeProperty(QString  key);
virtual void removePropertyChangeListener(PropertyChangeListener*  listener);
virtual void removePropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual void setComment(QString  comment);
virtual void setProperty(QString  key, QVariant  value);
virtual void setState(int  arg__1);
virtual void setUserName(QString  s) throw (NamedBean::BadUserNameException) ;
virtual void stateChanged(int  arg__1);
virtual void timerEvent(QTimerEvent*  event);
virtual QString  toString();
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);
virtual void vetoableChange(PropertyChangeEvent*  evt) throw (PropertyVetoException) ;

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_Audio : public Audio
{ public:
inline QChar  py_q_getSubType() { return Audio::getSubType(); }
inline void py_q_stateChanged(int  arg__1) { Audio::stateChanged(arg__1); }
inline QString  py_q_toString() { return Audio::toString(); }
};

class PythonQtWrapper_Audio : public QObject
{ Q_OBJECT
public:
public slots:
Audio* new_Audio(QString  systemName, QObject*  parent = 0);
Audio* new_Audio(QString  systemName, QString  userName, QObject*  parent = 0);
void delete_Audio(Audio* obj) { delete obj; } 
   QChar  getSubType(Audio* theWrappedObject);
   QChar  py_q_getSubType(Audio* theWrappedObject){  return (((PythonQtPublicPromoter_Audio*)theWrappedObject)->py_q_getSubType());}
   void stateChanged(Audio* theWrappedObject, int  arg__1);
   void py_q_stateChanged(Audio* theWrappedObject, int  arg__1){  (((PythonQtPublicPromoter_Audio*)theWrappedObject)->py_q_stateChanged(arg__1));}
   QString  toString(Audio* theWrappedObject);
   QString  py_q_toString(Audio* theWrappedObject){  return (((PythonQtPublicPromoter_Audio*)theWrappedObject)->py_q_toString());}
    QString py_toString(Audio*);
};





class PythonQtShell_AudioBuffer : public AudioBuffer
{
public:
    PythonQtShell_AudioBuffer(QString  systemName, QObject*  parent = 0):AudioBuffer(systemName, parent),_wrapper(NULL) {}
    PythonQtShell_AudioBuffer(QString  systemName, QString  userName, QObject*  parent = 0):AudioBuffer(systemName, userName, parent),_wrapper(NULL) {}

   ~PythonQtShell_AudioBuffer();

virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(PropertyChangeListener*  l, QString  beanRef, const QString  listenerRef);
virtual void addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  l, QString  beanRef, QString  listenerRef);
virtual void addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual void childEvent(QChildEvent*  event);
virtual int  compareSystemNameSuffix(QString  suffix1, QString  suffix2, NamedBean*  n);
virtual int  compareTo(NamedBean*  n2);
virtual void customEvent(QEvent*  event);
virtual QString  describeState(int  state);
virtual void dispose();
virtual bool  equals(QObject*  obj);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual QString  getBeanType();
virtual QString  getComment();
virtual QString  getDisplayName();
virtual long  getEndLoopPoint();
virtual int  getFormat();
virtual int  getFrameSize();
virtual int  getFrequency();
virtual QString  getFullyFormattedDisplayName();
virtual long  getLength();
virtual QString  getListenerRef(PropertyChangeListener*  l);
virtual QList<QString >*  getListenerRefs();
virtual int  getNumPropertyChangeListeners();
virtual QVariant  getProperty(QString  key);
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners();
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners(QString  name);
virtual QVector<PropertyChangeListener* >  getPropertyChangeListenersByReference(QString  propertyName);
virtual QSet<QString >  getPropertyKeys();
virtual long  getStartLoopPoint();
virtual int  getState();
virtual QChar  getSubType();
virtual QString  getSystemName() const;
virtual QString  getURL();
virtual QString  getUserName() const;
virtual uint  hashCode();
virtual bool  isStreamed();
virtual bool  isStreamedForced();
virtual void removeProperty(QString  key);
virtual void removePropertyChangeListener(PropertyChangeListener*  listener);
virtual void removePropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual void setComment(QString  comment);
virtual void setEndLoopPoint(long  arg__1);
virtual void setInputStream(QDataStream*  arg__1);
virtual void setProperty(QString  key, QVariant  value);
virtual void setStartLoopPoint(long  arg__1);
virtual void setState(int  arg__1);
virtual void setStreamed(bool  arg__1);
virtual void setURL(QString  arg__1);
virtual void setUserName(QString  s) throw (NamedBean::BadUserNameException) ;
virtual void stateChanged(int  arg__1);
virtual void timerEvent(QTimerEvent*  event);
virtual QString  toString();
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);
virtual void vetoableChange(PropertyChangeEvent*  evt) throw (PropertyVetoException) ;

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_AudioBuffer : public AudioBuffer
{ public:
inline long  py_q_getEndLoopPoint() { return AudioBuffer::getEndLoopPoint(); }
inline int  py_q_getFormat() { return AudioBuffer::getFormat(); }
inline int  py_q_getFrameSize() { return AudioBuffer::getFrameSize(); }
inline int  py_q_getFrequency() { return AudioBuffer::getFrequency(); }
inline long  py_q_getLength() { return AudioBuffer::getLength(); }
inline long  py_q_getStartLoopPoint() { return AudioBuffer::getStartLoopPoint(); }
inline QString  py_q_getURL() { return AudioBuffer::getURL(); }
inline bool  py_q_isStreamed() { return AudioBuffer::isStreamed(); }
inline bool  py_q_isStreamedForced() { return AudioBuffer::isStreamedForced(); }
inline void py_q_setEndLoopPoint(long  arg__1) { AudioBuffer::setEndLoopPoint(arg__1); }
inline void py_q_setInputStream(QDataStream*  arg__1) { AudioBuffer::setInputStream(arg__1); }
inline void py_q_setStartLoopPoint(long  arg__1) { AudioBuffer::setStartLoopPoint(arg__1); }
inline void py_q_setStreamed(bool  arg__1) { AudioBuffer::setStreamed(arg__1); }
inline void py_q_setURL(QString  arg__1) { AudioBuffer::setURL(arg__1); }
};

class PythonQtWrapper_AudioBuffer : public QObject
{ Q_OBJECT
public:
public slots:
AudioBuffer* new_AudioBuffer(QString  systemName, QObject*  parent = 0);
AudioBuffer* new_AudioBuffer(QString  systemName, QString  userName, QObject*  parent = 0);
void delete_AudioBuffer(AudioBuffer* obj) { delete obj; } 
   long  getEndLoopPoint(AudioBuffer* theWrappedObject);
   long  py_q_getEndLoopPoint(AudioBuffer* theWrappedObject){  return (((PythonQtPublicPromoter_AudioBuffer*)theWrappedObject)->py_q_getEndLoopPoint());}
   int  getFormat(AudioBuffer* theWrappedObject);
   int  py_q_getFormat(AudioBuffer* theWrappedObject){  return (((PythonQtPublicPromoter_AudioBuffer*)theWrappedObject)->py_q_getFormat());}
   int  getFrameSize(AudioBuffer* theWrappedObject);
   int  py_q_getFrameSize(AudioBuffer* theWrappedObject){  return (((PythonQtPublicPromoter_AudioBuffer*)theWrappedObject)->py_q_getFrameSize());}
   int  getFrequency(AudioBuffer* theWrappedObject);
   int  py_q_getFrequency(AudioBuffer* theWrappedObject){  return (((PythonQtPublicPromoter_AudioBuffer*)theWrappedObject)->py_q_getFrequency());}
   long  getLength(AudioBuffer* theWrappedObject);
   long  py_q_getLength(AudioBuffer* theWrappedObject){  return (((PythonQtPublicPromoter_AudioBuffer*)theWrappedObject)->py_q_getLength());}
   long  getStartLoopPoint(AudioBuffer* theWrappedObject);
   long  py_q_getStartLoopPoint(AudioBuffer* theWrappedObject){  return (((PythonQtPublicPromoter_AudioBuffer*)theWrappedObject)->py_q_getStartLoopPoint());}
   QString  getURL(AudioBuffer* theWrappedObject);
   QString  py_q_getURL(AudioBuffer* theWrappedObject){  return (((PythonQtPublicPromoter_AudioBuffer*)theWrappedObject)->py_q_getURL());}
   bool  isStreamed(AudioBuffer* theWrappedObject);
   bool  py_q_isStreamed(AudioBuffer* theWrappedObject){  return (((PythonQtPublicPromoter_AudioBuffer*)theWrappedObject)->py_q_isStreamed());}
   bool  isStreamedForced(AudioBuffer* theWrappedObject);
   bool  py_q_isStreamedForced(AudioBuffer* theWrappedObject){  return (((PythonQtPublicPromoter_AudioBuffer*)theWrappedObject)->py_q_isStreamedForced());}
   void setEndLoopPoint(AudioBuffer* theWrappedObject, long  arg__1);
   void py_q_setEndLoopPoint(AudioBuffer* theWrappedObject, long  arg__1){  (((PythonQtPublicPromoter_AudioBuffer*)theWrappedObject)->py_q_setEndLoopPoint(arg__1));}
   void setInputStream(AudioBuffer* theWrappedObject, QDataStream*  arg__1);
   void py_q_setInputStream(AudioBuffer* theWrappedObject, QDataStream*  arg__1){  (((PythonQtPublicPromoter_AudioBuffer*)theWrappedObject)->py_q_setInputStream(arg__1));}
   void setStartLoopPoint(AudioBuffer* theWrappedObject, long  arg__1);
   void py_q_setStartLoopPoint(AudioBuffer* theWrappedObject, long  arg__1){  (((PythonQtPublicPromoter_AudioBuffer*)theWrappedObject)->py_q_setStartLoopPoint(arg__1));}
   void setStreamed(AudioBuffer* theWrappedObject, bool  arg__1);
   void py_q_setStreamed(AudioBuffer* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_AudioBuffer*)theWrappedObject)->py_q_setStreamed(arg__1));}
   void setURL(AudioBuffer* theWrappedObject, QString  arg__1);
   void py_q_setURL(AudioBuffer* theWrappedObject, QString  arg__1){  (((PythonQtPublicPromoter_AudioBuffer*)theWrappedObject)->py_q_setURL(arg__1));}
    QString py_toString(AudioBuffer*);
};





class PythonQtShell_AudioListener : public AudioListener
{
public:
    PythonQtShell_AudioListener(QObject*  parent = 0):AudioListener(parent),_wrapper(NULL) {}
    PythonQtShell_AudioListener(QString  systemName, QObject*  parent = 0):AudioListener(systemName, parent),_wrapper(NULL) {}
    PythonQtShell_AudioListener(QString  systemName, QString  userName, QObject*  parent = 0):AudioListener(systemName, userName, parent),_wrapper(NULL) {}

   ~PythonQtShell_AudioListener();

virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(PropertyChangeListener*  l, QString  beanRef, const QString  listenerRef);
virtual void addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  l, QString  beanRef, QString  listenerRef);
virtual void addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual void childEvent(QChildEvent*  event);
virtual int  compareSystemNameSuffix(QString  suffix1, QString  suffix2, NamedBean*  n);
virtual int  compareTo(NamedBean*  n2);
virtual void customEvent(QEvent*  event);
virtual QString  describeState(int  state);
virtual void dispose();
virtual bool  equals(QObject*  obj);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual QString  getBeanType();
virtual QString  getComment();
virtual QVector3D  getCurrentOrientation(int  arg__1);
virtual QVector3D  getCurrentPosition();
virtual QString  getDisplayName();
virtual QString  getFullyFormattedDisplayName();
virtual float  getGain();
virtual QString  getListenerRef(PropertyChangeListener*  l);
virtual QList<QString >*  getListenerRefs();
virtual float  getMetersPerUnit();
virtual int  getNumPropertyChangeListeners();
virtual QVector3D  getOrientation(int  arg__1);
virtual QVector3D  getPosition();
virtual QVariant  getProperty(QString  key);
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners();
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners(QString  name);
virtual QVector<PropertyChangeListener* >  getPropertyChangeListenersByReference(QString  propertyName);
virtual QSet<QString >  getPropertyKeys();
virtual int  getState();
virtual QChar  getSubType();
virtual QString  getSystemName() const;
virtual QString  getUserName() const;
virtual QVector3D  getVelocity();
virtual uint  hashCode();
virtual void removeProperty(QString  key);
virtual void removePropertyChangeListener(PropertyChangeListener*  listener);
virtual void removePropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
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
virtual void setUserName(QString  s) throw (NamedBean::BadUserNameException) ;
virtual void setVelocity(QVector3D  arg__1);
virtual void stateChanged(int  arg__1);
virtual void timerEvent(QTimerEvent*  event);
virtual QString  toString();
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);
virtual void vetoableChange(PropertyChangeEvent*  evt) throw (PropertyVetoException) ;

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_AudioListener : public AudioListener
{ public:
inline QVector3D  py_q_getCurrentOrientation(int  arg__1) { return AudioListener::getCurrentOrientation(arg__1); }
inline QVector3D  py_q_getCurrentPosition() { return AudioListener::getCurrentPosition(); }
inline float  py_q_getGain() { return AudioListener::getGain(); }
inline float  py_q_getMetersPerUnit() { return AudioListener::getMetersPerUnit(); }
inline QVector3D  py_q_getOrientation(int  arg__1) { return AudioListener::getOrientation(arg__1); }
inline QVector3D  py_q_getPosition() { return AudioListener::getPosition(); }
inline QVector3D  py_q_getVelocity() { return AudioListener::getVelocity(); }
inline void py_q_resetCurrentPosition() { AudioListener::resetCurrentPosition(); }
inline void py_q_setGain(float  arg__1) { AudioListener::setGain(arg__1); }
inline void py_q_setMetersPerUnit(float  arg__1) { AudioListener::setMetersPerUnit(arg__1); }
inline void py_q_setOrientation(QVector3D  arg__1, QVector3D  arg__2) { AudioListener::setOrientation(arg__1, arg__2); }
inline void py_q_setPosition(QVector3D  arg__1) { AudioListener::setPosition(arg__1); }
inline void py_q_setPosition(float  arg__1, float  arg__2) { AudioListener::setPosition(arg__1, arg__2); }
inline void py_q_setPosition(float  arg__1, float  arg__2, float  arg__3) { AudioListener::setPosition(arg__1, arg__2, arg__3); }
inline void py_q_setVelocity(QVector3D  arg__1) { AudioListener::setVelocity(arg__1); }
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
   QVector3D  py_q_getCurrentOrientation(AudioListener* theWrappedObject, int  arg__1){  return (((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->py_q_getCurrentOrientation(arg__1));}
   QVector3D  getCurrentPosition(AudioListener* theWrappedObject);
   QVector3D  py_q_getCurrentPosition(AudioListener* theWrappedObject){  return (((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->py_q_getCurrentPosition());}
   float  getGain(AudioListener* theWrappedObject);
   float  py_q_getGain(AudioListener* theWrappedObject){  return (((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->py_q_getGain());}
   float  getMetersPerUnit(AudioListener* theWrappedObject);
   float  py_q_getMetersPerUnit(AudioListener* theWrappedObject){  return (((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->py_q_getMetersPerUnit());}
   QVector3D  getOrientation(AudioListener* theWrappedObject, int  arg__1);
   QVector3D  py_q_getOrientation(AudioListener* theWrappedObject, int  arg__1){  return (((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->py_q_getOrientation(arg__1));}
   QVector3D  getPosition(AudioListener* theWrappedObject);
   QVector3D  py_q_getPosition(AudioListener* theWrappedObject){  return (((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->py_q_getPosition());}
   QVector3D  getVelocity(AudioListener* theWrappedObject);
   QVector3D  py_q_getVelocity(AudioListener* theWrappedObject){  return (((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->py_q_getVelocity());}
   void resetCurrentPosition(AudioListener* theWrappedObject);
   void py_q_resetCurrentPosition(AudioListener* theWrappedObject){  (((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->py_q_resetCurrentPosition());}
   void setGain(AudioListener* theWrappedObject, float  arg__1);
   void py_q_setGain(AudioListener* theWrappedObject, float  arg__1){  (((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->py_q_setGain(arg__1));}
   void setMetersPerUnit(AudioListener* theWrappedObject, float  arg__1);
   void py_q_setMetersPerUnit(AudioListener* theWrappedObject, float  arg__1){  (((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->py_q_setMetersPerUnit(arg__1));}
   void setOrientation(AudioListener* theWrappedObject, QVector3D  arg__1, QVector3D  arg__2);
   void py_q_setOrientation(AudioListener* theWrappedObject, QVector3D  arg__1, QVector3D  arg__2){  (((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->py_q_setOrientation(arg__1, arg__2));}
   void setPosition(AudioListener* theWrappedObject, QVector3D  arg__1);
   void py_q_setPosition(AudioListener* theWrappedObject, QVector3D  arg__1){  (((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->py_q_setPosition(arg__1));}
   void setPosition(AudioListener* theWrappedObject, float  arg__1, float  arg__2);
   void py_q_setPosition(AudioListener* theWrappedObject, float  arg__1, float  arg__2){  (((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->py_q_setPosition(arg__1, arg__2));}
   void setPosition(AudioListener* theWrappedObject, float  arg__1, float  arg__2, float  arg__3);
   void py_q_setPosition(AudioListener* theWrappedObject, float  arg__1, float  arg__2, float  arg__3){  (((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->py_q_setPosition(arg__1, arg__2, arg__3));}
   void setVelocity(AudioListener* theWrappedObject, QVector3D  arg__1);
   void py_q_setVelocity(AudioListener* theWrappedObject, QVector3D  arg__1){  (((PythonQtPublicPromoter_AudioListener*)theWrappedObject)->py_q_setVelocity(arg__1));}
    QString py_toString(AudioListener*);
};





class PythonQtShell_AudioManager : public AudioManager
{
public:
    PythonQtShell_AudioManager(QObject*  parent = 0):AudioManager(parent),_wrapper(NULL) {}

   ~PythonQtShell_AudioManager();

virtual void Register(NamedBean*  s) const;
virtual void addDataListener(QObject*  e);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual void childEvent(QChildEvent*  event);
virtual void cleanup();
virtual void customEvent(QEvent*  event);
virtual void deleteBean(NamedBean*  arg__1, QString  arg__2) throw (PropertyVetoException) ;
virtual void deregister(NamedBean*  s) const;
virtual void dispose();
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual Audio*  getAudio(QString  arg__1);
virtual NamedBean*  getBeanBySystemName(QString  systemName) const;
virtual NamedBean*  getBeanByUserName(QString  arg__1) const;
virtual QString  getBeanTypeHandled(bool  plural) const;
virtual Audio*  getBySystemName(QString  arg__1) const;
virtual Audio*  getByUserName(QString  arg__1) const;
virtual QString  getEntryToolTip();
virtual SystemConnectionMemo*  getMemo() const;
virtual NamedBean*  getNamedBean(QString  name) const;
virtual QString  getNamedBeanClass() const;
virtual QSet<NamedBean* >  getNamedBeanSet(QChar  subType);
virtual int  getObjectCount();
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners();
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners(QString  propertyName);
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList();
virtual QStringList  getSystemNameList(QChar  arg__1);
virtual QStringList  getSystemNameList(char  arg__1);
virtual QString  getSystemPrefix() const;
virtual int  getXMLOrder() const;
virtual void init();
virtual QString  makeSystemName(QString  s, bool  logErrors = true, QLocale  locale = QLocale()) const;
virtual Audio*  newAudio(QString  arg__1, QString  arg__2);
virtual QString  normalizeSystemName(QString  inputName) const;
virtual void propertyChange(PropertyChangeEvent*  e);
virtual Audio*  provideAudio(QString  arg__1);
virtual void removeDataListener(QObject*  e);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void removePropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual void timerEvent(QTimerEvent*  event);
virtual QString  toString();
virtual char  typeLetter() const;
virtual Manager::NameValidity  validSystemNameFormat(QString  systemName) const;
virtual void vetoableChange(PropertyChangeEvent*  evt);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_AudioManager : public AudioManager
{ public:
inline void py_q_cleanup() { AudioManager::cleanup(); }
inline Audio*  py_q_getAudio(QString  arg__1) { return AudioManager::getAudio(arg__1); }
inline Audio*  py_q_getBySystemName(QString  arg__1) const { return this->getBySystemName(arg__1); }
inline Audio*  py_q_getByUserName(QString  arg__1) const { return this->getByUserName(arg__1); }
inline QString  py_q_getNamedBeanClass() const { return AudioManager::getNamedBeanClass(); }
inline QSet<NamedBean* >  py_q_getNamedBeanSet(QChar  subType) { return this->getNamedBeanSet(subType); }
inline QStringList  py_q_getSystemNameList() { return AudioManager::getSystemNameList(); }
inline QStringList  py_q_getSystemNameList(QChar  arg__1) { return AudioManager::getSystemNameList(arg__1); }
inline QStringList  py_q_getSystemNameList(char  arg__1) { return AudioManager::getSystemNameList(arg__1); }
inline int  py_q_getXMLOrder() const { return AudioManager::getXMLOrder(); }
inline void py_q_init() { AudioManager::init(); }
inline Audio*  py_q_newAudio(QString  arg__1, QString  arg__2) { return AudioManager::newAudio(arg__1, arg__2); }
inline Audio*  py_q_provideAudio(QString  arg__1) { return AudioManager::provideAudio(arg__1); }
};

class PythonQtWrapper_AudioManager : public QObject
{ Q_OBJECT
public:
public slots:
AudioManager* new_AudioManager(QObject*  parent = 0);
void delete_AudioManager(AudioManager* obj) { delete obj; } 
   void cleanup(AudioManager* theWrappedObject);
   void py_q_cleanup(AudioManager* theWrappedObject){  (((PythonQtPublicPromoter_AudioManager*)theWrappedObject)->py_q_cleanup());}
   Audio*  getAudio(AudioManager* theWrappedObject, QString  arg__1);
   Audio*  py_q_getAudio(AudioManager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_AudioManager*)theWrappedObject)->py_q_getAudio(arg__1));}
   Audio*  getBySystemName(AudioManager* theWrappedObject, QString  arg__1) const;
   Audio*  py_q_getBySystemName(AudioManager* theWrappedObject, QString  arg__1) const{  return (((PythonQtPublicPromoter_AudioManager*)theWrappedObject)->py_q_getBySystemName(arg__1));}
   Audio*  getByUserName(AudioManager* theWrappedObject, QString  arg__1) const;
   Audio*  py_q_getByUserName(AudioManager* theWrappedObject, QString  arg__1) const{  return (((PythonQtPublicPromoter_AudioManager*)theWrappedObject)->py_q_getByUserName(arg__1));}
   QString  py_q_getNamedBeanClass(AudioManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_AudioManager*)theWrappedObject)->py_q_getNamedBeanClass());}
   QSet<NamedBean* >  getNamedBeanSet(AudioManager* theWrappedObject, QChar  subType);
   QSet<NamedBean* >  py_q_getNamedBeanSet(AudioManager* theWrappedObject, QChar  subType){  return (((PythonQtPublicPromoter_AudioManager*)theWrappedObject)->py_q_getNamedBeanSet(subType));}
   QStringList  py_q_getSystemNameList(AudioManager* theWrappedObject){  return (((PythonQtPublicPromoter_AudioManager*)theWrappedObject)->py_q_getSystemNameList());}
   QStringList  getSystemNameList(AudioManager* theWrappedObject, QChar  arg__1);
   QStringList  py_q_getSystemNameList(AudioManager* theWrappedObject, QChar  arg__1){  return (((PythonQtPublicPromoter_AudioManager*)theWrappedObject)->py_q_getSystemNameList(arg__1));}
   QStringList  getSystemNameList(AudioManager* theWrappedObject, char  arg__1);
   QStringList  py_q_getSystemNameList(AudioManager* theWrappedObject, char  arg__1){  return (((PythonQtPublicPromoter_AudioManager*)theWrappedObject)->py_q_getSystemNameList(arg__1));}
   int  py_q_getXMLOrder(AudioManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_AudioManager*)theWrappedObject)->py_q_getXMLOrder());}
   void init(AudioManager* theWrappedObject);
   void py_q_init(AudioManager* theWrappedObject){  (((PythonQtPublicPromoter_AudioManager*)theWrappedObject)->py_q_init());}
   Audio*  newAudio(AudioManager* theWrappedObject, QString  arg__1, QString  arg__2);
   Audio*  py_q_newAudio(AudioManager* theWrappedObject, QString  arg__1, QString  arg__2){  return (((PythonQtPublicPromoter_AudioManager*)theWrappedObject)->py_q_newAudio(arg__1, arg__2));}
   Audio*  provideAudio(AudioManager* theWrappedObject, QString  arg__1);
   Audio*  py_q_provideAudio(AudioManager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_AudioManager*)theWrappedObject)->py_q_provideAudio(arg__1));}
    QString py_toString(AudioManager*);
};





class PythonQtShell_AudioSource : public AudioSource
{
public:
    PythonQtShell_AudioSource(QObject*  parent = 0):AudioSource(parent),_wrapper(NULL) {}
    PythonQtShell_AudioSource(QString  systemName, QObject*  parent = 0):AudioSource(systemName, parent),_wrapper(NULL) {}
    PythonQtShell_AudioSource(QString  systemName, QString  userName, QObject*  parent = 0):AudioSource(systemName, userName, parent),_wrapper(NULL) {}

   ~PythonQtShell_AudioSource();

virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(PropertyChangeListener*  l, QString  beanRef, const QString  listenerRef);
virtual void addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  l, QString  beanRef, QString  listenerRef);
virtual void addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual void childEvent(QChildEvent*  event);
virtual int  compareSystemNameSuffix(QString  suffix1, QString  suffix2, NamedBean*  n);
virtual int  compareTo(NamedBean*  n2);
virtual void customEvent(QEvent*  event);
virtual QString  describeState(int  state);
virtual void dispose();
virtual bool  equals(QObject*  obj);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual void fadeIn();
virtual void fadeOut();
virtual AudioBuffer*  getAssignedBuffer();
virtual QString  getAssignedBufferName();
virtual QString  getBeanType();
virtual QString  getComment();
virtual QVector3D  getCurrentPosition();
virtual QString  getDisplayName();
virtual float  getDopplerFactor();
virtual int  getFadeIn();
virtual int  getFadeOut();
virtual QString  getFullyFormattedDisplayName();
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
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners();
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners(QString  name);
virtual QVector<PropertyChangeListener* >  getPropertyChangeListenersByReference(QString  propertyName);
virtual QSet<QString >  getPropertyKeys();
virtual float  getReferenceDistance();
virtual float  getRollOffFactor();
virtual int  getState();
virtual QChar  getSubType();
virtual QString  getSystemName() const;
virtual QString  getUserName() const;
virtual QVector3D  getVelocity();
virtual uint  hashCode();
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
virtual void removeProperty(QString  key);
virtual void removePropertyChangeListener(PropertyChangeListener*  listener);
virtual void removePropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
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
virtual void setUserName(QString  s) throw (NamedBean::BadUserNameException) ;
virtual void setVelocity(QVector3D  arg__1);
virtual void stateChanged(int  arg__1);
virtual void stop();
virtual void timerEvent(QTimerEvent*  event);
virtual QString  toString();
virtual void togglePause();
virtual void togglePlay();
virtual bool  unqueueBuffers();
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);
virtual void vetoableChange(PropertyChangeEvent*  evt) throw (PropertyVetoException) ;

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_AudioSource : public AudioSource
{ public:
inline void py_q_fadeIn() { AudioSource::fadeIn(); }
inline void py_q_fadeOut() { AudioSource::fadeOut(); }
inline AudioBuffer*  py_q_getAssignedBuffer() { return AudioSource::getAssignedBuffer(); }
inline QString  py_q_getAssignedBufferName() { return AudioSource::getAssignedBufferName(); }
inline QVector3D  py_q_getCurrentPosition() { return AudioSource::getCurrentPosition(); }
inline float  py_q_getDopplerFactor() { return AudioSource::getDopplerFactor(); }
inline int  py_q_getFadeIn() { return AudioSource::getFadeIn(); }
inline int  py_q_getFadeOut() { return AudioSource::getFadeOut(); }
inline float  py_q_getGain() { return AudioSource::getGain(); }
inline int  py_q_getMaxLoops() { return AudioSource::getMaxLoops(); }
inline float  py_q_getMaximumDistance() { return AudioSource::getMaximumDistance(); }
inline int  py_q_getMinLoops() { return AudioSource::getMinLoops(); }
inline int  py_q_getNumLoops() { return AudioSource::getNumLoops(); }
inline float  py_q_getPitch() { return AudioSource::getPitch(); }
inline QVector3D  py_q_getPosition() { return AudioSource::getPosition(); }
inline float  py_q_getReferenceDistance() { return AudioSource::getReferenceDistance(); }
inline float  py_q_getRollOffFactor() { return AudioSource::getRollOffFactor(); }
inline QVector3D  py_q_getVelocity() { return AudioSource::getVelocity(); }
inline bool  py_q_isBound() { return AudioSource::isBound(); }
inline bool  py_q_isLooped() { return AudioSource::isLooped(); }
inline bool  py_q_isPositionRelative() { return AudioSource::isPositionRelative(); }
inline bool  py_q_isQueued() { return AudioSource::isQueued(); }
inline int  py_q_numProcessedBuffers() { return AudioSource::numProcessedBuffers(); }
inline int  py_q_numQueuedBuffers() { return AudioSource::numQueuedBuffers(); }
inline void py_q_pause() { AudioSource::pause(); }
inline void py_q_play() { AudioSource::play(); }
inline bool  py_q_queueBuffer(AudioBuffer*  arg__1) { return AudioSource::queueBuffer(arg__1); }
inline bool  py_q_queueBuffers(QQueue<AudioBuffer* >  arg__1) { return AudioSource::queueBuffers(arg__1); }
inline void py_q_resetCurrentPosition() { AudioSource::resetCurrentPosition(); }
inline void py_q_resume() { AudioSource::resume(); }
inline void py_q_rewind() { AudioSource::rewind(); }
inline void py_q_setAssignedBuffer(AudioBuffer*  arg__1) { AudioSource::setAssignedBuffer(arg__1); }
inline void py_q_setAssignedBuffer(QString  arg__1) { AudioSource::setAssignedBuffer(arg__1); }
inline void py_q_setDopplerFactor(float  arg__1) { AudioSource::setDopplerFactor(arg__1); }
inline void py_q_setFadeIn(int  arg__1) { AudioSource::setFadeIn(arg__1); }
inline void py_q_setFadeOut(int  arg__1) { AudioSource::setFadeOut(arg__1); }
inline void py_q_setGain(float  arg__1) { AudioSource::setGain(arg__1); }
inline void py_q_setLooped(bool  arg__1) { AudioSource::setLooped(arg__1); }
inline void py_q_setMaxLoops(int  arg__1) { AudioSource::setMaxLoops(arg__1); }
inline void py_q_setMaximumDistance(float  arg__1) { AudioSource::setMaximumDistance(arg__1); }
inline void py_q_setMinLoops(int  arg__1) { AudioSource::setMinLoops(arg__1); }
inline void py_q_setPitch(float  arg__1) { AudioSource::setPitch(arg__1); }
inline void py_q_setPosition(QVector3D  arg__1) { AudioSource::setPosition(arg__1); }
inline void py_q_setPosition(float  arg__1, float  arg__2) { AudioSource::setPosition(arg__1, arg__2); }
inline void py_q_setPosition(float  arg__1, float  arg__2, float  arg__3) { AudioSource::setPosition(arg__1, arg__2, arg__3); }
inline void py_q_setPositionRelative(bool  arg__1) { AudioSource::setPositionRelative(arg__1); }
inline void py_q_setReferenceDistance(float  arg__1) { AudioSource::setReferenceDistance(arg__1); }
inline void py_q_setRollOffFactor(float  arg__1) { AudioSource::setRollOffFactor(arg__1); }
inline void py_q_setVelocity(QVector3D  arg__1) { AudioSource::setVelocity(arg__1); }
inline void py_q_stop() { AudioSource::stop(); }
inline void py_q_togglePause() { AudioSource::togglePause(); }
inline void py_q_togglePlay() { AudioSource::togglePlay(); }
inline bool  py_q_unqueueBuffers() { return AudioSource::unqueueBuffers(); }
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
   void py_q_fadeIn(AudioSource* theWrappedObject){  (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_fadeIn());}
   void fadeOut(AudioSource* theWrappedObject);
   void py_q_fadeOut(AudioSource* theWrappedObject){  (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_fadeOut());}
   AudioBuffer*  getAssignedBuffer(AudioSource* theWrappedObject);
   AudioBuffer*  py_q_getAssignedBuffer(AudioSource* theWrappedObject){  return (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_getAssignedBuffer());}
   QString  getAssignedBufferName(AudioSource* theWrappedObject);
   QString  py_q_getAssignedBufferName(AudioSource* theWrappedObject){  return (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_getAssignedBufferName());}
   QVector3D  getCurrentPosition(AudioSource* theWrappedObject);
   QVector3D  py_q_getCurrentPosition(AudioSource* theWrappedObject){  return (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_getCurrentPosition());}
   float  getDopplerFactor(AudioSource* theWrappedObject);
   float  py_q_getDopplerFactor(AudioSource* theWrappedObject){  return (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_getDopplerFactor());}
   int  getFadeIn(AudioSource* theWrappedObject);
   int  py_q_getFadeIn(AudioSource* theWrappedObject){  return (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_getFadeIn());}
   int  getFadeOut(AudioSource* theWrappedObject);
   int  py_q_getFadeOut(AudioSource* theWrappedObject){  return (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_getFadeOut());}
   float  getGain(AudioSource* theWrappedObject);
   float  py_q_getGain(AudioSource* theWrappedObject){  return (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_getGain());}
   int  getMaxLoops(AudioSource* theWrappedObject);
   int  py_q_getMaxLoops(AudioSource* theWrappedObject){  return (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_getMaxLoops());}
   float  getMaximumDistance(AudioSource* theWrappedObject);
   float  py_q_getMaximumDistance(AudioSource* theWrappedObject){  return (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_getMaximumDistance());}
   int  getMinLoops(AudioSource* theWrappedObject);
   int  py_q_getMinLoops(AudioSource* theWrappedObject){  return (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_getMinLoops());}
   int  getNumLoops(AudioSource* theWrappedObject);
   int  py_q_getNumLoops(AudioSource* theWrappedObject){  return (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_getNumLoops());}
   float  getPitch(AudioSource* theWrappedObject);
   float  py_q_getPitch(AudioSource* theWrappedObject){  return (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_getPitch());}
   QVector3D  getPosition(AudioSource* theWrappedObject);
   QVector3D  py_q_getPosition(AudioSource* theWrappedObject){  return (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_getPosition());}
   float  getReferenceDistance(AudioSource* theWrappedObject);
   float  py_q_getReferenceDistance(AudioSource* theWrappedObject){  return (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_getReferenceDistance());}
   float  getRollOffFactor(AudioSource* theWrappedObject);
   float  py_q_getRollOffFactor(AudioSource* theWrappedObject){  return (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_getRollOffFactor());}
   QVector3D  getVelocity(AudioSource* theWrappedObject);
   QVector3D  py_q_getVelocity(AudioSource* theWrappedObject){  return (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_getVelocity());}
   bool  isBound(AudioSource* theWrappedObject);
   bool  py_q_isBound(AudioSource* theWrappedObject){  return (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_isBound());}
   bool  isLooped(AudioSource* theWrappedObject);
   bool  py_q_isLooped(AudioSource* theWrappedObject){  return (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_isLooped());}
   bool  isPositionRelative(AudioSource* theWrappedObject);
   bool  py_q_isPositionRelative(AudioSource* theWrappedObject){  return (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_isPositionRelative());}
   bool  isQueued(AudioSource* theWrappedObject);
   bool  py_q_isQueued(AudioSource* theWrappedObject){  return (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_isQueued());}
   int  numProcessedBuffers(AudioSource* theWrappedObject);
   int  py_q_numProcessedBuffers(AudioSource* theWrappedObject){  return (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_numProcessedBuffers());}
   int  numQueuedBuffers(AudioSource* theWrappedObject);
   int  py_q_numQueuedBuffers(AudioSource* theWrappedObject){  return (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_numQueuedBuffers());}
   void pause(AudioSource* theWrappedObject);
   void py_q_pause(AudioSource* theWrappedObject){  (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_pause());}
   void play(AudioSource* theWrappedObject);
   void py_q_play(AudioSource* theWrappedObject){  (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_play());}
   bool  queueBuffer(AudioSource* theWrappedObject, AudioBuffer*  arg__1);
   bool  py_q_queueBuffer(AudioSource* theWrappedObject, AudioBuffer*  arg__1){  return (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_queueBuffer(arg__1));}
   bool  queueBuffers(AudioSource* theWrappedObject, QQueue<AudioBuffer* >  arg__1);
   bool  py_q_queueBuffers(AudioSource* theWrappedObject, QQueue<AudioBuffer* >  arg__1){  return (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_queueBuffers(arg__1));}
   void resetCurrentPosition(AudioSource* theWrappedObject);
   void py_q_resetCurrentPosition(AudioSource* theWrappedObject){  (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_resetCurrentPosition());}
   void resume(AudioSource* theWrappedObject);
   void py_q_resume(AudioSource* theWrappedObject){  (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_resume());}
   void rewind(AudioSource* theWrappedObject);
   void py_q_rewind(AudioSource* theWrappedObject){  (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_rewind());}
   void setAssignedBuffer(AudioSource* theWrappedObject, AudioBuffer*  arg__1);
   void py_q_setAssignedBuffer(AudioSource* theWrappedObject, AudioBuffer*  arg__1){  (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_setAssignedBuffer(arg__1));}
   void setAssignedBuffer(AudioSource* theWrappedObject, QString  arg__1);
   void py_q_setAssignedBuffer(AudioSource* theWrappedObject, QString  arg__1){  (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_setAssignedBuffer(arg__1));}
   void setDopplerFactor(AudioSource* theWrappedObject, float  arg__1);
   void py_q_setDopplerFactor(AudioSource* theWrappedObject, float  arg__1){  (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_setDopplerFactor(arg__1));}
   void setFadeIn(AudioSource* theWrappedObject, int  arg__1);
   void py_q_setFadeIn(AudioSource* theWrappedObject, int  arg__1){  (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_setFadeIn(arg__1));}
   void setFadeOut(AudioSource* theWrappedObject, int  arg__1);
   void py_q_setFadeOut(AudioSource* theWrappedObject, int  arg__1){  (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_setFadeOut(arg__1));}
   void setGain(AudioSource* theWrappedObject, float  arg__1);
   void py_q_setGain(AudioSource* theWrappedObject, float  arg__1){  (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_setGain(arg__1));}
   void setLooped(AudioSource* theWrappedObject, bool  arg__1);
   void py_q_setLooped(AudioSource* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_setLooped(arg__1));}
   void setMaxLoops(AudioSource* theWrappedObject, int  arg__1);
   void py_q_setMaxLoops(AudioSource* theWrappedObject, int  arg__1){  (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_setMaxLoops(arg__1));}
   void setMaximumDistance(AudioSource* theWrappedObject, float  arg__1);
   void py_q_setMaximumDistance(AudioSource* theWrappedObject, float  arg__1){  (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_setMaximumDistance(arg__1));}
   void setMinLoops(AudioSource* theWrappedObject, int  arg__1);
   void py_q_setMinLoops(AudioSource* theWrappedObject, int  arg__1){  (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_setMinLoops(arg__1));}
   void setPitch(AudioSource* theWrappedObject, float  arg__1);
   void py_q_setPitch(AudioSource* theWrappedObject, float  arg__1){  (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_setPitch(arg__1));}
   void setPosition(AudioSource* theWrappedObject, QVector3D  arg__1);
   void py_q_setPosition(AudioSource* theWrappedObject, QVector3D  arg__1){  (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_setPosition(arg__1));}
   void setPosition(AudioSource* theWrappedObject, float  arg__1, float  arg__2);
   void py_q_setPosition(AudioSource* theWrappedObject, float  arg__1, float  arg__2){  (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_setPosition(arg__1, arg__2));}
   void setPosition(AudioSource* theWrappedObject, float  arg__1, float  arg__2, float  arg__3);
   void py_q_setPosition(AudioSource* theWrappedObject, float  arg__1, float  arg__2, float  arg__3){  (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_setPosition(arg__1, arg__2, arg__3));}
   void setPositionRelative(AudioSource* theWrappedObject, bool  arg__1);
   void py_q_setPositionRelative(AudioSource* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_setPositionRelative(arg__1));}
   void setReferenceDistance(AudioSource* theWrappedObject, float  arg__1);
   void py_q_setReferenceDistance(AudioSource* theWrappedObject, float  arg__1){  (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_setReferenceDistance(arg__1));}
   void setRollOffFactor(AudioSource* theWrappedObject, float  arg__1);
   void py_q_setRollOffFactor(AudioSource* theWrappedObject, float  arg__1){  (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_setRollOffFactor(arg__1));}
   void setVelocity(AudioSource* theWrappedObject, QVector3D  arg__1);
   void py_q_setVelocity(AudioSource* theWrappedObject, QVector3D  arg__1){  (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_setVelocity(arg__1));}
   void stop(AudioSource* theWrappedObject);
   void py_q_stop(AudioSource* theWrappedObject){  (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_stop());}
   void togglePause(AudioSource* theWrappedObject);
   void py_q_togglePause(AudioSource* theWrappedObject){  (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_togglePause());}
   void togglePlay(AudioSource* theWrappedObject);
   void py_q_togglePlay(AudioSource* theWrappedObject){  (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_togglePlay());}
   bool  unqueueBuffers(AudioSource* theWrappedObject);
   bool  py_q_unqueueBuffers(AudioSource* theWrappedObject){  return (((PythonQtPublicPromoter_AudioSource*)theWrappedObject)->py_q_unqueueBuffers());}
    QString py_toString(AudioSource*);
};





class PythonQtShell_BasicRosterEntry : public BasicRosterEntry
{
public:
    PythonQtShell_BasicRosterEntry():BasicRosterEntry(),_wrapper(NULL) {}

   ~PythonQtShell_BasicRosterEntry();

virtual void deleteAttribute(QString  key);
virtual QString  getAttribute(QString  arg__1);
virtual QStringList  getAttributeList();
virtual QString  getDccAddress();
virtual DccLocoAddress*  getDccLocoAddress();
virtual QString  getId();
virtual int  getMaxSpeedPCT();
virtual QString  getShuntingFunction();
virtual bool  isLongAddress();
virtual bool  isOpen();
virtual void putAttribute(QString  key, QString  value);
virtual void setOpen(bool  boo);
virtual QDomElement  store();
virtual QString  titleString();
virtual QString  toString();

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_BasicRosterEntry : public BasicRosterEntry
{ public:
inline void py_q_deleteAttribute(QString  key) { this->deleteAttribute(key); }
inline QString  py_q_getAttribute(QString  arg__1) { return BasicRosterEntry::getAttribute(arg__1); }
inline QStringList  py_q_getAttributeList() { return this->getAttributeList(); }
inline QString  py_q_getDccAddress() { return this->getDccAddress(); }
inline DccLocoAddress*  py_q_getDccLocoAddress() { return this->getDccLocoAddress(); }
inline QString  py_q_getId() { return this->getId(); }
inline int  py_q_getMaxSpeedPCT() { return this->getMaxSpeedPCT(); }
inline QString  py_q_getShuntingFunction() { return this->getShuntingFunction(); }
inline bool  py_q_isLongAddress() { return this->isLongAddress(); }
inline bool  py_q_isOpen() { return this->isOpen(); }
inline void py_q_putAttribute(QString  key, QString  value) { this->putAttribute(key, value); }
inline void py_q_setOpen(bool  boo) { this->setOpen(boo); }
inline QDomElement  py_q_store() { return BasicRosterEntry::store(); }
inline QString  py_q_titleString() { return BasicRosterEntry::titleString(); }
inline QString  py_q_toString() { return this->toString(); }
};

class PythonQtWrapper_BasicRosterEntry : public QObject
{ Q_OBJECT
public:
public slots:
BasicRosterEntry* new_BasicRosterEntry();
void delete_BasicRosterEntry(BasicRosterEntry* obj) { delete obj; } 
   void deleteAttribute(BasicRosterEntry* theWrappedObject, QString  key);
   void py_q_deleteAttribute(BasicRosterEntry* theWrappedObject, QString  key){  (((PythonQtPublicPromoter_BasicRosterEntry*)theWrappedObject)->py_q_deleteAttribute(key));}
   QString  getAttribute(BasicRosterEntry* theWrappedObject, QString  arg__1);
   QString  py_q_getAttribute(BasicRosterEntry* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_BasicRosterEntry*)theWrappedObject)->py_q_getAttribute(arg__1));}
   QStringList  getAttributeList(BasicRosterEntry* theWrappedObject);
   QStringList  py_q_getAttributeList(BasicRosterEntry* theWrappedObject){  return (((PythonQtPublicPromoter_BasicRosterEntry*)theWrappedObject)->py_q_getAttributeList());}
   QString  getDccAddress(BasicRosterEntry* theWrappedObject);
   QString  py_q_getDccAddress(BasicRosterEntry* theWrappedObject){  return (((PythonQtPublicPromoter_BasicRosterEntry*)theWrappedObject)->py_q_getDccAddress());}
   DccLocoAddress*  getDccLocoAddress(BasicRosterEntry* theWrappedObject);
   DccLocoAddress*  py_q_getDccLocoAddress(BasicRosterEntry* theWrappedObject){  return (((PythonQtPublicPromoter_BasicRosterEntry*)theWrappedObject)->py_q_getDccLocoAddress());}
   QString  getId(BasicRosterEntry* theWrappedObject);
   QString  py_q_getId(BasicRosterEntry* theWrappedObject){  return (((PythonQtPublicPromoter_BasicRosterEntry*)theWrappedObject)->py_q_getId());}
   int  getMaxSpeedPCT(BasicRosterEntry* theWrappedObject);
   int  py_q_getMaxSpeedPCT(BasicRosterEntry* theWrappedObject){  return (((PythonQtPublicPromoter_BasicRosterEntry*)theWrappedObject)->py_q_getMaxSpeedPCT());}
   QString  getShuntingFunction(BasicRosterEntry* theWrappedObject);
   QString  py_q_getShuntingFunction(BasicRosterEntry* theWrappedObject){  return (((PythonQtPublicPromoter_BasicRosterEntry*)theWrappedObject)->py_q_getShuntingFunction());}
   bool  isLongAddress(BasicRosterEntry* theWrappedObject);
   bool  py_q_isLongAddress(BasicRosterEntry* theWrappedObject){  return (((PythonQtPublicPromoter_BasicRosterEntry*)theWrappedObject)->py_q_isLongAddress());}
   bool  isOpen(BasicRosterEntry* theWrappedObject);
   bool  py_q_isOpen(BasicRosterEntry* theWrappedObject){  return (((PythonQtPublicPromoter_BasicRosterEntry*)theWrappedObject)->py_q_isOpen());}
   void putAttribute(BasicRosterEntry* theWrappedObject, QString  key, QString  value);
   void py_q_putAttribute(BasicRosterEntry* theWrappedObject, QString  key, QString  value){  (((PythonQtPublicPromoter_BasicRosterEntry*)theWrappedObject)->py_q_putAttribute(key, value));}
   void setOpen(BasicRosterEntry* theWrappedObject, bool  boo);
   void py_q_setOpen(BasicRosterEntry* theWrappedObject, bool  boo){  (((PythonQtPublicPromoter_BasicRosterEntry*)theWrappedObject)->py_q_setOpen(boo));}
   QDomElement  store(BasicRosterEntry* theWrappedObject);
   QDomElement  py_q_store(BasicRosterEntry* theWrappedObject){  return (((PythonQtPublicPromoter_BasicRosterEntry*)theWrappedObject)->py_q_store());}
   QString  titleString(BasicRosterEntry* theWrappedObject);
   QString  py_q_titleString(BasicRosterEntry* theWrappedObject){  return (((PythonQtPublicPromoter_BasicRosterEntry*)theWrappedObject)->py_q_titleString());}
   QString  toString(BasicRosterEntry* theWrappedObject);
   QString  py_q_toString(BasicRosterEntry* theWrappedObject){  return (((PythonQtPublicPromoter_BasicRosterEntry*)theWrappedObject)->py_q_toString());}
    QString py_toString(BasicRosterEntry*);
};





class PythonQtShell_BeanInterface : public BeanInterface
{
public:
    PythonQtShell_BeanInterface():BeanInterface(),_wrapper(NULL) {}

   ~PythonQtShell_BeanInterface();

virtual QVariant  getIndexedProperty(QString  arg__1, int  arg__2);
virtual QVariant  getProperty(QString  arg__1);
virtual QSet<QString >  getPropertyNames();
virtual bool  hasIndexedProperty(QString  arg__1);
virtual bool  hasProperty(QString  arg__1);
virtual void setIndexedProperty(QString  arg__1, int  arg__2, QVariant  arg__3);
virtual void setProperty(QString  arg__1, QVariant  arg__2);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_BeanInterface : public BeanInterface
{ public:
inline QVariant  py_q_getIndexedProperty(QString  arg__1, int  arg__2) { return BeanInterface::getIndexedProperty(arg__1, arg__2); }
inline QVariant  py_q_getProperty(QString  arg__1) { return BeanInterface::getProperty(arg__1); }
inline QSet<QString >  py_q_getPropertyNames() { return BeanInterface::getPropertyNames(); }
inline bool  py_q_hasIndexedProperty(QString  arg__1) { return BeanInterface::hasIndexedProperty(arg__1); }
inline bool  py_q_hasProperty(QString  arg__1) { return BeanInterface::hasProperty(arg__1); }
inline void py_q_setIndexedProperty(QString  arg__1, int  arg__2, QVariant  arg__3) { BeanInterface::setIndexedProperty(arg__1, arg__2, arg__3); }
inline void py_q_setProperty(QString  arg__1, QVariant  arg__2) { BeanInterface::setProperty(arg__1, arg__2); }
};

class PythonQtWrapper_BeanInterface : public QObject
{ Q_OBJECT
public:
public slots:
BeanInterface* new_BeanInterface();
void delete_BeanInterface(BeanInterface* obj) { delete obj; } 
   QVariant  getIndexedProperty(BeanInterface* theWrappedObject, QString  arg__1, int  arg__2);
   QVariant  py_q_getIndexedProperty(BeanInterface* theWrappedObject, QString  arg__1, int  arg__2){  return (((PythonQtPublicPromoter_BeanInterface*)theWrappedObject)->py_q_getIndexedProperty(arg__1, arg__2));}
   QVariant  getProperty(BeanInterface* theWrappedObject, QString  arg__1);
   QVariant  py_q_getProperty(BeanInterface* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_BeanInterface*)theWrappedObject)->py_q_getProperty(arg__1));}
   QSet<QString >  getPropertyNames(BeanInterface* theWrappedObject);
   QSet<QString >  py_q_getPropertyNames(BeanInterface* theWrappedObject){  return (((PythonQtPublicPromoter_BeanInterface*)theWrappedObject)->py_q_getPropertyNames());}
   bool  hasIndexedProperty(BeanInterface* theWrappedObject, QString  arg__1);
   bool  py_q_hasIndexedProperty(BeanInterface* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_BeanInterface*)theWrappedObject)->py_q_hasIndexedProperty(arg__1));}
   bool  hasProperty(BeanInterface* theWrappedObject, QString  arg__1);
   bool  py_q_hasProperty(BeanInterface* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_BeanInterface*)theWrappedObject)->py_q_hasProperty(arg__1));}
   void setIndexedProperty(BeanInterface* theWrappedObject, QString  arg__1, int  arg__2, QVariant  arg__3);
   void py_q_setIndexedProperty(BeanInterface* theWrappedObject, QString  arg__1, int  arg__2, QVariant  arg__3){  (((PythonQtPublicPromoter_BeanInterface*)theWrappedObject)->py_q_setIndexedProperty(arg__1, arg__2, arg__3));}
   void setProperty(BeanInterface* theWrappedObject, QString  arg__1, QVariant  arg__2);
   void py_q_setProperty(BeanInterface* theWrappedObject, QString  arg__1, QVariant  arg__2){  (((PythonQtPublicPromoter_BeanInterface*)theWrappedObject)->py_q_setProperty(arg__1, arg__2));}
};





class PythonQtShell_BeanTableDataModel : public BeanTableDataModel
{
public:
    PythonQtShell_BeanTableDataModel(QObject*  parent = 0):BeanTableDataModel(parent),_wrapper(NULL) {}

   ~PythonQtShell_BeanTableDataModel();

virtual void addToPopUp(QMenu*  popup);
virtual void clickOn(NamedBean*  arg__1);
virtual int  columnCount(const QModelIndex&  parent) const;
virtual void configDeleteColumn(JTable*  table);
virtual void configValueColumn(JTable*  table);
virtual QPushButton*  configureButton();
virtual void configureTable(JTable*  table);
virtual QVariant  data(const QModelIndex&  index, int  role) const;
virtual Qt::ItemFlags  flags(const QModelIndex&  index) const;
virtual QString  getBeanType();
virtual NamedBean*  getBySystemName(QString  name) const;
virtual NamedBean*  getByUserName(QString  name);
virtual QString  getColumnClass(int  col) const;
virtual Manager*  getManager();
virtual QString  getMasterClassName();
virtual int  getPreferredWidth(int  col);
virtual QString  getValue(QString  systemName) const;
virtual QVariant  headerData(int  section, Qt::Orientation  orientation, int  role) const;
virtual void init();
virtual bool  matchPropertyName(PropertyChangeEvent*  e);
virtual void propertyChange(PropertyChangeEvent*  e);
virtual int  rowCount(const QModelIndex&  parent) const;
virtual bool  setData(const QModelIndex&  index, const QVariant&  value, int  role);
virtual void setManager(Manager*  arg__1);
virtual void updateNameList();

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_BeanTableDataModel : public BeanTableDataModel
{ public:
inline void promoted_On_itemClicked(QModelIndex  arg__1) { this->On_itemClicked(arg__1); }
inline void promoted_addMouseListenerToHeader(JTable*  table) { this->addMouseListenerToHeader(table); }
inline void promoted_clickOn(NamedBean*  arg__1) { this->clickOn(arg__1); }
inline void promoted_configDeleteColumn(JTable*  table) { this->configDeleteColumn(table); }
inline void promoted_configValueColumn(JTable*  table) { this->configValueColumn(table); }
inline void promoted_deleteBean(int  row, int  col) { this->deleteBean(row, col); }
inline QString  promoted_getBeanType() { return this->getBeanType(); }
inline NamedBean*  promoted_getBySystemName(QString  name) const { return this->getBySystemName(name); }
inline NamedBean*  promoted_getByUserName(QString  name) { return this->getByUserName(name); }
inline Manager*  promoted_getManager() { return this->getManager(); }
inline QString  promoted_getMasterClassName() { return this->getMasterClassName(); }
inline int  promoted_getPropertyColumnCount() const { return this->getPropertyColumnCount(); }
inline bool  promoted_matchPropertyName(PropertyChangeEvent*  e) { return this->matchPropertyName(e); }
inline void promoted_onColumnSelected(QObject*  obj) { this->onColumnSelected(obj); }
inline void promoted_setColumnToHoldButton(JTable*  table, int  column, QPushButton*  sample = NULL) { this->setColumnToHoldButton(table, column, sample); }
inline void promoted_setManager(Manager*  arg__1) { this->setManager(arg__1); }
inline void promoted_showPopup(QPoint  p) { this->showPopup(p); }
inline void promoted_showTableHeaderPopup(QMouseEvent*  e, JTable*  table) { this->showTableHeaderPopup(e, table); }
inline void promoted_showTableHeaderPopup(const QPoint&  arg__1) { this->showTableHeaderPopup(arg__1); }
inline void promoted_updateNameList() { this->updateNameList(); }
inline void py_q_addToPopUp(QMenu*  popup) { BeanTableDataModel::addToPopUp(popup); }
inline void py_q_clickOn(NamedBean*  arg__1) { BeanTableDataModel::clickOn(arg__1); }
inline int  py_q_columnCount(const QModelIndex&  parent) const { return BeanTableDataModel::columnCount(parent); }
inline void py_q_configDeleteColumn(JTable*  table) { BeanTableDataModel::configDeleteColumn(table); }
inline void py_q_configValueColumn(JTable*  table) { BeanTableDataModel::configValueColumn(table); }
inline QPushButton*  py_q_configureButton() { return BeanTableDataModel::configureButton(); }
inline void py_q_configureTable(JTable*  table) { BeanTableDataModel::configureTable(table); }
inline QVariant  py_q_data(const QModelIndex&  index, int  role) const { return BeanTableDataModel::data(index, role); }
inline Qt::ItemFlags  py_q_flags(const QModelIndex&  index) const { return BeanTableDataModel::flags(index); }
inline QString  py_q_getBeanType() { return BeanTableDataModel::getBeanType(); }
inline NamedBean*  py_q_getBySystemName(QString  name) const { return BeanTableDataModel::getBySystemName(name); }
inline NamedBean*  py_q_getByUserName(QString  name) { return BeanTableDataModel::getByUserName(name); }
inline QString  py_q_getColumnClass(int  col) const { return BeanTableDataModel::getColumnClass(col); }
inline Manager*  py_q_getManager() { return BeanTableDataModel::getManager(); }
inline QString  py_q_getMasterClassName() { return BeanTableDataModel::getMasterClassName(); }
inline int  py_q_getPreferredWidth(int  col) { return BeanTableDataModel::getPreferredWidth(col); }
inline QString  py_q_getValue(QString  systemName) const { return BeanTableDataModel::getValue(systemName); }
inline QVariant  py_q_headerData(int  section, Qt::Orientation  orientation, int  role) const { return BeanTableDataModel::headerData(section, orientation, role); }
inline void py_q_init() { BeanTableDataModel::init(); }
inline bool  py_q_matchPropertyName(PropertyChangeEvent*  e) { return BeanTableDataModel::matchPropertyName(e); }
inline void py_q_propertyChange(PropertyChangeEvent*  e) { BeanTableDataModel::propertyChange(e); }
inline int  py_q_rowCount(const QModelIndex&  parent) const { return BeanTableDataModel::rowCount(parent); }
inline bool  py_q_setData(const QModelIndex&  index, const QVariant&  value, int  role) { return BeanTableDataModel::setData(index, value, role); }
inline void py_q_setManager(Manager*  arg__1) { BeanTableDataModel::setManager(arg__1); }
inline void py_q_updateNameList() { BeanTableDataModel::updateNameList(); }
};

class PythonQtWrapper_BeanTableDataModel : public QObject
{ Q_OBJECT
public:
public slots:
BeanTableDataModel* new_BeanTableDataModel(QObject*  parent = 0);
void delete_BeanTableDataModel(BeanTableDataModel* obj) { delete obj; } 
   void addMouseListenerToHeader(BeanTableDataModel* theWrappedObject, JTable*  table);
   void addToPopUp(BeanTableDataModel* theWrappedObject, QMenu*  popup);
   void py_q_addToPopUp(BeanTableDataModel* theWrappedObject, QMenu*  popup){  (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_addToPopUp(popup));}
   void clickOn(BeanTableDataModel* theWrappedObject, NamedBean*  arg__1);
   void py_q_clickOn(BeanTableDataModel* theWrappedObject, NamedBean*  arg__1){  (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_clickOn(arg__1));}
   int  columnCount(BeanTableDataModel* theWrappedObject, const QModelIndex&  parent) const;
   int  py_q_columnCount(BeanTableDataModel* theWrappedObject, const QModelIndex&  parent) const{  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_columnCount(parent));}
   void configDeleteColumn(BeanTableDataModel* theWrappedObject, JTable*  table);
   void py_q_configDeleteColumn(BeanTableDataModel* theWrappedObject, JTable*  table){  (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_configDeleteColumn(table));}
   void configValueColumn(BeanTableDataModel* theWrappedObject, JTable*  table);
   void py_q_configValueColumn(BeanTableDataModel* theWrappedObject, JTable*  table){  (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_configValueColumn(table));}
   QPushButton*  configureButton(BeanTableDataModel* theWrappedObject);
   QPushButton*  py_q_configureButton(BeanTableDataModel* theWrappedObject){  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_configureButton());}
   void configureTable(BeanTableDataModel* theWrappedObject, JTable*  table);
   void py_q_configureTable(BeanTableDataModel* theWrappedObject, JTable*  table){  (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_configureTable(table));}
   void copyName(BeanTableDataModel* theWrappedObject, int  arg__1);
   QVariant  data(BeanTableDataModel* theWrappedObject, const QModelIndex&  index, int  role) const;
   QVariant  py_q_data(BeanTableDataModel* theWrappedObject, const QModelIndex&  index, int  role) const{  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_data(index, role));}
   void deleteBean(BeanTableDataModel* theWrappedObject, int  row, int  col);
   void dispose(BeanTableDataModel* theWrappedObject);
   Qt::ItemFlags  flags(BeanTableDataModel* theWrappedObject, const QModelIndex&  index) const;
   Qt::ItemFlags  py_q_flags(BeanTableDataModel* theWrappedObject, const QModelIndex&  index) const{  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_flags(index));}
   QString  getBeanType(BeanTableDataModel* theWrappedObject);
   QString  py_q_getBeanType(BeanTableDataModel* theWrappedObject){  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_getBeanType());}
   NamedBean*  getBySystemName(BeanTableDataModel* theWrappedObject, QString  name) const;
   NamedBean*  py_q_getBySystemName(BeanTableDataModel* theWrappedObject, QString  name) const{  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_getBySystemName(name));}
   NamedBean*  getByUserName(BeanTableDataModel* theWrappedObject, QString  name);
   NamedBean*  py_q_getByUserName(BeanTableDataModel* theWrappedObject, QString  name){  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_getByUserName(name));}
   QString  getColumnClass(BeanTableDataModel* theWrappedObject, int  col) const;
   QString  py_q_getColumnClass(BeanTableDataModel* theWrappedObject, int  col) const{  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_getColumnClass(col));}
   int  getDisplayDeleteMsg(BeanTableDataModel* theWrappedObject);
   Manager*  getManager(BeanTableDataModel* theWrappedObject);
   Manager*  py_q_getManager(BeanTableDataModel* theWrappedObject){  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_getManager());}
   QString  getMasterClassName(BeanTableDataModel* theWrappedObject);
   QString  py_q_getMasterClassName(BeanTableDataModel* theWrappedObject){  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_getMasterClassName());}
   int  getPreferredWidth(BeanTableDataModel* theWrappedObject, int  col);
   int  py_q_getPreferredWidth(BeanTableDataModel* theWrappedObject, int  col){  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_getPreferredWidth(col));}
   int  getPropertyColumnCount(BeanTableDataModel* theWrappedObject) const;
   QString  getValue(BeanTableDataModel* theWrappedObject, QString  systemName) const;
   QString  py_q_getValue(BeanTableDataModel* theWrappedObject, QString  systemName) const{  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_getValue(systemName));}
   QVariant  headerData(BeanTableDataModel* theWrappedObject, int  section, Qt::Orientation  orientation, int  role) const;
   QVariant  py_q_headerData(BeanTableDataModel* theWrappedObject, int  section, Qt::Orientation  orientation, int  role) const{  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_headerData(section, orientation, role));}
   void py_q_init(BeanTableDataModel* theWrappedObject){  (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_init());}
   bool  matchPropertyName(BeanTableDataModel* theWrappedObject, PropertyChangeEvent*  e);
   bool  py_q_matchPropertyName(BeanTableDataModel* theWrappedObject, PropertyChangeEvent*  e){  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_matchPropertyName(e));}
   void moveBean(BeanTableDataModel* theWrappedObject, int  arg__1);
   void persistTable(BeanTableDataModel* theWrappedObject, JTable*  table);
   void py_q_propertyChange(BeanTableDataModel* theWrappedObject, PropertyChangeEvent*  e){  (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_propertyChange(e));}
   void removeName(BeanTableDataModel* theWrappedObject, int  arg__1);
   void renameBean(BeanTableDataModel* theWrappedObject, int  arg__1);
   int  rowCount(BeanTableDataModel* theWrappedObject, const QModelIndex&  parent) const;
   int  py_q_rowCount(BeanTableDataModel* theWrappedObject, const QModelIndex&  parent) const{  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_rowCount(parent));}
   void setColumnToHoldButton(BeanTableDataModel* theWrappedObject, JTable*  table, int  column, QPushButton*  sample = NULL);
   bool  setData(BeanTableDataModel* theWrappedObject, const QModelIndex&  index, const QVariant&  value, int  role);
   bool  py_q_setData(BeanTableDataModel* theWrappedObject, const QModelIndex&  index, const QVariant&  value, int  role){  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_setData(index, value, role));}
   void setDisplayDeleteMsg(BeanTableDataModel* theWrappedObject, int  boo);
   void setManager(BeanTableDataModel* theWrappedObject, Manager*  arg__1);
   void py_q_setManager(BeanTableDataModel* theWrappedObject, Manager*  arg__1){  (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_setManager(arg__1));}
   void setPropertyColumnsVisible(BeanTableDataModel* theWrappedObject, JTable*  table, bool  visible);
   void showTableHeaderPopup(BeanTableDataModel* theWrappedObject, QMouseEvent*  e, JTable*  table);
   void stopPersistingTable(BeanTableDataModel* theWrappedObject, JTable*  table);
   void updateNameList(BeanTableDataModel* theWrappedObject);
   void py_q_updateNameList(BeanTableDataModel* theWrappedObject){  (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_updateNameList());}
};





class PythonQtShell_BeanTableFrame : public BeanTableFrame
{
public:
    PythonQtShell_BeanTableFrame(BeanTableDataModel*  model, QString  helpTarget, JTable*  dataTab, QWidget*  parent = 0):BeanTableFrame(model, helpTarget, dataTab, parent),_wrapper(NULL) {}
    PythonQtShell_BeanTableFrame(QString  s, QWidget*  parent = 0):BeanTableFrame(s, parent),_wrapper(NULL) {}
    PythonQtShell_BeanTableFrame(QWidget*  parent = 0):BeanTableFrame(parent),_wrapper(NULL) {}

   ~PythonQtShell_BeanTableFrame();

virtual void actionEvent(QActionEvent*  event);
virtual void addHelpMenu(QString  ref, bool  direct);
virtual void addToBottomBox(QWidget*  comp, QString  c);
virtual void changeEvent(QEvent*  arg__1);
virtual void childEvent(QChildEvent*  event);
virtual bool  closedNormally();
virtual void componentMoved(QMoveEvent*  e);
virtual void componentResized(QResizeEvent*  e);
virtual void contextMenuEvent(QContextMenuEvent*  event);
virtual QMenu*  createPopupMenu();
virtual void customEvent(QEvent*  event);
virtual int  devType() const;
virtual void dispose();
virtual void dragEnterEvent(QDragEnterEvent*  event);
virtual void dragLeaveEvent(QDragLeaveEvent*  event);
virtual void dragMoveEvent(QDragMoveEvent*  event);
virtual void dropEvent(QDropEvent*  event);
virtual void enterEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  target, QEvent*  event);
virtual void focusInEvent(QFocusEvent*  event);
virtual bool  focusNextPrevChild(bool  next);
virtual void focusOutEvent(QFocusEvent*  event);
virtual QString  getClassName();
virtual QVariant  getProperty(QString  key);
virtual QString  getTitle();
virtual void handleModified();
virtual bool  hasHeightForWidth() const;
virtual int  heightForWidth(int  arg__1) const;
virtual void initComponents();
virtual void initPainter(QPainter*  painter) const;
virtual void inputMethodEvent(QInputMethodEvent*  arg__1);
virtual QVariant  inputMethodQuery(Qt::InputMethodQuery  arg__1) const;
virtual void keyPressEvent(QKeyEvent*  event);
virtual void keyReleaseEvent(QKeyEvent*  event);
virtual void languageChange();
virtual void leaveEvent(QEvent*  event);
virtual int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
virtual QSize  minimumSizeHint() const;
virtual void mouseDoubleClickEvent(QMouseEvent*  event);
virtual void mouseMoveEvent(QMouseEvent*  event);
virtual void mousePressEvent(QMouseEvent*  event);
virtual void mouseReleaseEvent(QMouseEvent*  event);
virtual void moveEvent(QMoveEvent*  e);
virtual bool  nativeEvent(const QByteArray&  eventType, void*  message, long*  result);
virtual void pack();
virtual QPaintEngine*  paintEngine() const;
virtual void paintEvent(QPaintEvent*  event);
virtual QPaintDevice*  redirected(QPoint*  offset) const;
virtual void resizeEvent(QResizeEvent*  e);
virtual void setEnabled(bool  b);
virtual void setTitle(QString  _title);
virtual void setVisible(bool  visible);
virtual QPainter*  sharedPainter() const;
virtual void showEvent(QShowEvent*  event);
virtual QSize  sizeHint() const;
virtual void storeValues();
virtual void tabletEvent(QTabletEvent*  event);
virtual void timerEvent(QTimerEvent*  event);
virtual void wheelEvent(QWheelEvent*  event);
virtual void windowClosing(QCloseEvent*  e);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_BeanTableFrame : public BeanTableFrame
{ public:
inline void promoted_addToBottomBox(QWidget*  comp, QString  c) { this->addToBottomBox(comp, c); }
inline QWidget*  promoted_getBottomBox() { return this->getBottomBox(); }
inline void py_q_addToBottomBox(QWidget*  comp, QString  c) { BeanTableFrame::addToBottomBox(comp, c); }
inline void py_q_dispose() { BeanTableFrame::dispose(); }
inline QString  py_q_getClassName() { return BeanTableFrame::getClassName(); }
};

class PythonQtWrapper_BeanTableFrame : public QObject
{ Q_OBJECT
public:
public slots:
BeanTableFrame* new_BeanTableFrame(BeanTableDataModel*  model, QString  helpTarget, JTable*  dataTab, QWidget*  parent = 0);
BeanTableFrame* new_BeanTableFrame(QString  s, QWidget*  parent = 0);
BeanTableFrame* new_BeanTableFrame(QWidget*  parent = 0);
void delete_BeanTableFrame(BeanTableFrame* obj) { delete obj; } 
   void addToBottomBox(BeanTableFrame* theWrappedObject, QWidget*  comp, QString  c);
   void py_q_addToBottomBox(BeanTableFrame* theWrappedObject, QWidget*  comp, QString  c){  (((PythonQtPublicPromoter_BeanTableFrame*)theWrappedObject)->py_q_addToBottomBox(comp, c));}
   void py_q_dispose(BeanTableFrame* theWrappedObject){  (((PythonQtPublicPromoter_BeanTableFrame*)theWrappedObject)->py_q_dispose());}
   QWidget*  getBottomBox(BeanTableFrame* theWrappedObject);
   QString  py_q_getClassName(BeanTableFrame* theWrappedObject){  return (((PythonQtPublicPromoter_BeanTableFrame*)theWrappedObject)->py_q_getClassName());}
};





class PythonQtShell_BeanTableModel : public BeanTableModel
{
public:
    PythonQtShell_BeanTableModel(QObject*  parent = 0):BeanTableModel(parent),_wrapper(NULL) {}

   ~PythonQtShell_BeanTableModel();

virtual Manager*  getManager() const;

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_BeanTableModel : public BeanTableModel
{ public:
inline Manager*  py_q_getManager() const { return BeanTableModel::getManager(); }
};

class PythonQtWrapper_BeanTableModel : public QObject
{ Q_OBJECT
public:
public slots:
BeanTableModel* new_BeanTableModel(QObject*  parent = 0);
void delete_BeanTableModel(BeanTableModel* obj) { delete obj; } 
   int  columnCount(BeanTableModel* theWrappedObject, const QModelIndex&  parent) const;
   QVariant  data(BeanTableModel* theWrappedObject, const QModelIndex&  index, int  role) const;
   Qt::ItemFlags  flags(BeanTableModel* theWrappedObject, const QModelIndex&  index) const;
   QString  getColumnClass(BeanTableModel* theWrappedObject, int  c);
   Manager*  getManager(BeanTableModel* theWrappedObject) const;
   Manager*  py_q_getManager(BeanTableModel* theWrappedObject) const{  return (((PythonQtPublicPromoter_BeanTableModel*)theWrappedObject)->py_q_getManager());}
   QVariant  headerData(BeanTableModel* theWrappedObject, int  section, Qt::Orientation  orientation, int  role) const;
   int  rowCount(BeanTableModel* theWrappedObject, const QModelIndex&  parent) const;
};





class PythonQtShell_Block : public Block
{
public:
    PythonQtShell_Block(QString  systemName, QString  userName = "", QObject*  parent = 0):Block(systemName, userName, parent),_wrapper(NULL) {}

   ~PythonQtShell_Block();

virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(PropertyChangeListener*  l, QString  beanRef, const QString  listenerRef);
virtual void addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  l, QString  beanRef, QString  listenerRef);
virtual void addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual void childEvent(QChildEvent*  event);
virtual int  compareSystemNameSuffix(QString  suffix1, QString  suffix2, NamedBean*  n);
virtual int  compareTo(NamedBean*  n2);
virtual void customEvent(QEvent*  event);
virtual QString  describeState(int  state);
virtual void dispose();
virtual bool  equals(QObject*  obj);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual QString  getBeanType();
virtual QString  getComment();
virtual QString  getDisplayName();
virtual QString  getFullyFormattedDisplayName();
virtual QString  getListenerRef(PropertyChangeListener*  l);
virtual QList<QString >*  getListenerRefs();
virtual int  getNumPropertyChangeListeners();
virtual QVariant  getProperty(QString  key);
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners();
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners(QString  name);
virtual QVector<PropertyChangeListener* >  getPropertyChangeListenersByReference(QString  propertyName);
virtual QSet<QString >  getPropertyKeys();
virtual int  getState();
virtual QString  getSystemName() const;
virtual QString  getUserName() const;
virtual void goingActive();
virtual void goingInactive();
virtual void goingInconsistent();
virtual void goingUnknown();
virtual uint  hashCode();
virtual void removeProperty(QString  key);
virtual void removePropertyChangeListener(PropertyChangeListener*  listener);
virtual void removePropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual void setComment(QString  comment);
virtual void setProperty(QString  key, QVariant  value);
virtual bool  setSensor(QString  pName);
virtual void setState(int  v);
virtual void setUserName(QString  s) throw (NamedBean::BadUserNameException) ;
virtual void setValue(QVariant  value);
virtual void timerEvent(QTimerEvent*  event);
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);
virtual void vetoableChange(PropertyChangeEvent*  evt) throw (PropertyVetoException) ;

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_Block : public Block
{ public:
inline bool  py_q_equals(QObject*  obj) { return Block::equals(obj); }
inline int  py_q_getState() { return Block::getState(); }
inline void py_q_goingActive() { Block::goingActive(); }
inline void py_q_goingInactive() { Block::goingInactive(); }
inline void py_q_goingInconsistent() { Block::goingInconsistent(); }
inline void py_q_goingUnknown() { Block::goingUnknown(); }
inline bool  py_q_setSensor(QString  pName) { return Block::setSensor(pName); }
inline void py_q_setState(int  v) { Block::setState(v); }
inline void py_q_setValue(QVariant  value) { Block::setValue(value); }
};

class PythonQtWrapper_Block : public QObject
{ Q_OBJECT
public:
public slots:
Block* new_Block(QString  systemName, QString  userName = "", QObject*  parent = 0);
void delete_Block(Block* obj) { delete obj; } 
   void addBlockDenyList(Block* theWrappedObject, Block*  blk);
   void addBlockDenyList(Block* theWrappedObject, QString  pName);
   bool  py_q_equals(Block* theWrappedObject, QObject*  obj){  return (((PythonQtPublicPromoter_Block*)theWrappedObject)->py_q_equals(obj));}
   QString  getBlockSpeed(Block* theWrappedObject);
   int  getCurvature(Block* theWrappedObject);
   QList<QString >*  getDeniedBlocks(Block* theWrappedObject);
   int  getDirection(Block* theWrappedObject);
   float  getLengthCm(Block* theWrappedObject);
   float  getLengthIn(Block* theWrappedObject);
   float  getLengthMm(Block* theWrappedObject);
   LocoAddress*  getLocoAddress(Block* theWrappedObject, QString  rep);
   bool  getPermissiveWorking(Block* theWrappedObject);
   Sensor*  getSensor(Block* theWrappedObject);
   float  getSpeedLimit(Block* theWrappedObject);
   int  py_q_getState(Block* theWrappedObject){  return (((PythonQtPublicPromoter_Block*)theWrappedObject)->py_q_getState());}
   QString  getStateString(Block* theWrappedObject);
   QVariant  getValue(Block* theWrappedObject);
   void goingActive(Block* theWrappedObject);
   void py_q_goingActive(Block* theWrappedObject){  (((PythonQtPublicPromoter_Block*)theWrappedObject)->py_q_goingActive());}
   void goingInactive(Block* theWrappedObject);
   void py_q_goingInactive(Block* theWrappedObject){  (((PythonQtPublicPromoter_Block*)theWrappedObject)->py_q_goingInactive());}
   void goingInconsistent(Block* theWrappedObject);
   void py_q_goingInconsistent(Block* theWrappedObject){  (((PythonQtPublicPromoter_Block*)theWrappedObject)->py_q_goingInconsistent());}
   void goingUnknown(Block* theWrappedObject);
   void py_q_goingUnknown(Block* theWrappedObject){  (((PythonQtPublicPromoter_Block*)theWrappedObject)->py_q_goingUnknown());}
   bool  isBlockDenied(Block* theWrappedObject, Block*  deny);
   bool  isBlockDenied(Block* theWrappedObject, QString  deny);
   bool  isReportingCurrent(Block* theWrappedObject);
   void removeBlockDenyList(Block* theWrappedObject, Block*  blk);
   void removeBlockDenyList(Block* theWrappedObject, QString  blk);
   void setAllocated(Block* theWrappedObject, bool  boo);
   void setBlockSpeed(Block* theWrappedObject, QString  s) throw (JmriException);
   void setBlockSpeedName(Block* theWrappedObject, QString  s);
   void setCurvature(Block* theWrappedObject, int  c);
   void setDirection(Block* theWrappedObject, int  direction);
   void setLength(Block* theWrappedObject, float  l);
   void setPermissiveWorking(Block* theWrappedObject, bool  w);
   void setReportingCurrent(Block* theWrappedObject, bool  reportingCurrent);
   bool  setSensor(Block* theWrappedObject, QString  pName);
   bool  py_q_setSensor(Block* theWrappedObject, QString  pName){  return (((PythonQtPublicPromoter_Block*)theWrappedObject)->py_q_setSensor(pName));}
   void py_q_setState(Block* theWrappedObject, int  v){  (((PythonQtPublicPromoter_Block*)theWrappedObject)->py_q_setState(v));}
   void setValue(Block* theWrappedObject, QVariant  value);
   void py_q_setValue(Block* theWrappedObject, QVariant  value){  (((PythonQtPublicPromoter_Block*)theWrappedObject)->py_q_setValue(value));}
   QString  toDebugString(Block* theWrappedObject);
};





class PythonQtShell_BlockManager : public BlockManager
{
public:
    PythonQtShell_BlockManager(QObject*  parent = 0):BlockManager(parent),_wrapper(NULL) {}
    PythonQtShell_BlockManager(const BlockManager&  arg__1):BlockManager(arg__1),_wrapper(NULL) {}

   ~PythonQtShell_BlockManager();

virtual QString  getBeanTypeHandled(bool  plural) const;
virtual QString  getNamedBeanClass() const;
virtual QString  getSystemPrefix() const;
virtual int  getXMLOrder() const;
virtual void propertyChange(PropertyChangeEvent*  e);
virtual Block*  provide(QString  name) const throw (IllegalArgumentException) ;
virtual char  typeLetter() const;
virtual void vetoableChange(PropertyChangeEvent*  arg__1);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_BlockManager : public BlockManager
{ public:
inline QString  py_q_getBeanTypeHandled(bool  plural) const { return BlockManager::getBeanTypeHandled(plural); }
inline QString  py_q_getNamedBeanClass() const { return BlockManager::getNamedBeanClass(); }
inline QString  py_q_getSystemPrefix() const { return BlockManager::getSystemPrefix(); }
inline int  py_q_getXMLOrder() const { return BlockManager::getXMLOrder(); }
inline void py_q_propertyChange(PropertyChangeEvent*  e) { BlockManager::propertyChange(e); }
inline Block*  py_q_provide(QString  name) const throw (IllegalArgumentException)  { return BlockManager::provide(name); }
inline char  py_q_typeLetter() const { return BlockManager::typeLetter(); }
inline void py_q_vetoableChange(PropertyChangeEvent*  arg__1) { BlockManager::vetoableChange(arg__1); }
};

class PythonQtWrapper_BlockManager : public QObject
{ Q_OBJECT
public:
public slots:
BlockManager* new_BlockManager(QObject*  parent = 0);
BlockManager* new_BlockManager(const BlockManager&  arg__1);
void delete_BlockManager(BlockManager* obj) { delete obj; } 
   Block*  createNewBlock(BlockManager* theWrappedObject, QString  systemName, QString  userName) const;
   Block*  createNewBlock(BlockManager* theWrappedObject, QString  userName) const;
   QString  getBeanTypeHandled(BlockManager* theWrappedObject, bool  plural) const;
   QString  py_q_getBeanTypeHandled(BlockManager* theWrappedObject, bool  plural) const{  return (((PythonQtPublicPromoter_BlockManager*)theWrappedObject)->py_q_getBeanTypeHandled(plural));}
   Block*  getBlock(BlockManager* theWrappedObject, QString  name) const;
   QList<Block* >  getBlocksOccupiedByRosterEntry(BlockManager* theWrappedObject, RosterEntry*  re);
   Block*  getByDisplayName(BlockManager* theWrappedObject, QString  key);
   Block*  getBySystemName(BlockManager* theWrappedObject, QString  name) const;
   Block*  getByUserName(BlockManager* theWrappedObject, QString  key) const;
   QCompleter*  getCompleter(BlockManager* theWrappedObject, QString  text);
   QString  getDefaultSpeed(BlockManager* theWrappedObject);
   QString  getNamedBeanClass(BlockManager* theWrappedObject) const;
   QString  py_q_getNamedBeanClass(BlockManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_BlockManager*)theWrappedObject)->py_q_getNamedBeanClass());}
   QString  getSystemPrefix(BlockManager* theWrappedObject) const;
   QString  py_q_getSystemPrefix(BlockManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_BlockManager*)theWrappedObject)->py_q_getSystemPrefix());}
   int  getXMLOrder(BlockManager* theWrappedObject) const;
   int  py_q_getXMLOrder(BlockManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_BlockManager*)theWrappedObject)->py_q_getXMLOrder());}
   bool  isSavedPathInfo(BlockManager* theWrappedObject);
   void py_q_propertyChange(BlockManager* theWrappedObject, PropertyChangeEvent*  e){  (((PythonQtPublicPromoter_BlockManager*)theWrappedObject)->py_q_propertyChange(e));}
   Block*  provide(BlockManager* theWrappedObject, QString  name) const throw (IllegalArgumentException) ;
   Block*  py_q_provide(BlockManager* theWrappedObject, QString  name) const throw (IllegalArgumentException) {  return (((PythonQtPublicPromoter_BlockManager*)theWrappedObject)->py_q_provide(name));}
   Block*  provideBlock(BlockManager* theWrappedObject, QString  name) const;
   void setDefaultSpeed(BlockManager* theWrappedObject, QString  speed) throw (JmriException);
   void setSavedPathInfo(BlockManager* theWrappedObject, bool  save);
   qint64  timeSinceLastLayoutPowerOn(BlockManager* theWrappedObject) const;
   char  typeLetter(BlockManager* theWrappedObject) const;
   char  py_q_typeLetter(BlockManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_BlockManager*)theWrappedObject)->py_q_typeLetter());}
   void py_q_vetoableChange(BlockManager* theWrappedObject, PropertyChangeEvent*  arg__1){  (((PythonQtPublicPromoter_BlockManager*)theWrappedObject)->py_q_vetoableChange(arg__1));}
void py_set_shutDownTask(BlockManager* theWrappedObject, ShutDownTask*  shutDownTask){ theWrappedObject->shutDownTask = shutDownTask; }
ShutDownTask*  py_get_shutDownTask(BlockManager* theWrappedObject){ return theWrappedObject->shutDownTask; }
};





class PythonQtShell_CommandStation : public CommandStation
{
public:
    PythonQtShell_CommandStation():CommandStation(),_wrapper(NULL) {}

   ~PythonQtShell_CommandStation();

virtual QString  getSystemPrefix();
virtual QString  getUserName();
virtual bool  sendPacket(QByteArray  arg__1, int  arg__2);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_CommandStation : public CommandStation
{ public:
inline QString  py_q_getSystemPrefix() { return CommandStation::getSystemPrefix(); }
inline QString  py_q_getUserName() { return CommandStation::getUserName(); }
inline bool  py_q_sendPacket(QByteArray  arg__1, int  arg__2) { return CommandStation::sendPacket(arg__1, arg__2); }
};

class PythonQtWrapper_CommandStation : public QObject
{ Q_OBJECT
public:
public slots:
CommandStation* new_CommandStation();
void delete_CommandStation(CommandStation* obj) { delete obj; } 
   QString  getSystemPrefix(CommandStation* theWrappedObject);
   QString  py_q_getSystemPrefix(CommandStation* theWrappedObject){  return (((PythonQtPublicPromoter_CommandStation*)theWrappedObject)->py_q_getSystemPrefix());}
   QString  getUserName(CommandStation* theWrappedObject);
   QString  py_q_getUserName(CommandStation* theWrappedObject){  return (((PythonQtPublicPromoter_CommandStation*)theWrappedObject)->py_q_getUserName());}
   bool  sendPacket(CommandStation* theWrappedObject, QByteArray  arg__1, int  arg__2);
   bool  py_q_sendPacket(CommandStation* theWrappedObject, QByteArray  arg__1, int  arg__2){  return (((PythonQtPublicPromoter_CommandStation*)theWrappedObject)->py_q_sendPacket(arg__1, arg__2));}
};





class PythonQtShell_ControlPanelEditor : public ControlPanelEditor
{
public:
    PythonQtShell_ControlPanelEditor(QString  name, QWidget*  parent = 0):ControlPanelEditor(name, parent),_wrapper(NULL) {}
    PythonQtShell_ControlPanelEditor(QWidget*  parent = 0):ControlPanelEditor(parent),_wrapper(NULL) {}
    PythonQtShell_ControlPanelEditor(const ControlPanelEditor&  other):ControlPanelEditor(other),_wrapper(NULL) {}

   ~PythonQtShell_ControlPanelEditor();

virtual void actionEvent(QActionEvent*  event);
virtual void addHelpMenu(QString  ref, bool  direct);
virtual void changeEvent(QEvent*  arg__1);
virtual void childEvent(QChildEvent*  event);
virtual bool  closedNormally();
virtual void componentMoved(QMoveEvent*  e);
virtual void componentResized(QResizeEvent*  e);
virtual void contextMenuEvent(QContextMenuEvent*  event);
virtual QMenu*  createPopupMenu();
virtual void customEvent(QEvent*  event);
virtual bool  deletePanel();
virtual int  devType() const;
virtual void dispose();
virtual void dragLeaveEvent(QDragLeaveEvent*  event);
virtual void enterEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  target, QEvent*  event);
virtual void focusInEvent(QFocusEvent*  event);
virtual bool  focusNextPrevChild(bool  next);
virtual void focusOutEvent(QFocusEvent*  event);
virtual QString  getClassName();
virtual QVariant  getProperty(QString  key);
virtual QString  getTitle();
virtual void handleModified();
virtual bool  hasHeightForWidth() const;
virtual int  heightForWidth(int  arg__1) const;
virtual void init(QString  name);
virtual void initComponents();
virtual void initPainter(QPainter*  painter) const;
virtual void initView();
virtual void inputMethodEvent(QInputMethodEvent*  arg__1);
virtual QVariant  inputMethodQuery(Qt::InputMethodQuery  arg__1) const;
virtual void keyPressEvent(QKeyEvent*  e);
virtual void keyReleaseEvent(QKeyEvent*  e);
virtual void languageChange();
virtual void leaveEvent(QEvent*  event);
virtual int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
virtual QSize  minimumSizeHint() const;
virtual void mouseClicked(QGraphicsSceneMouseEvent*  event);
virtual void mouseDoubleClickEvent(QMouseEvent*  event);
virtual void mouseDragged(QGraphicsSceneMouseEvent*  event);
virtual void mouseEntered(QGraphicsSceneMouseEvent*  event);
virtual void mouseExited(QGraphicsSceneMouseEvent*  event);
virtual void mouseMoveEvent(QMouseEvent*  event);
virtual void mouseMoved(QGraphicsSceneMouseEvent*  event);
virtual void mousePressEvent(QMouseEvent*  event);
virtual void mousePressed(QGraphicsSceneMouseEvent*  event);
virtual void mouseReleaseEvent(QMouseEvent*  event);
virtual void mouseReleased(QGraphicsSceneMouseEvent*  event);
virtual void mouseWheelMoved(QGraphicsSceneWheelEvent*  arg__1);
virtual void moveEvent(QMoveEvent*  e);
virtual bool  nativeEvent(const QByteArray&  eventType, void*  message, long*  result);
virtual void newPanelDefaults();
virtual void pack();
virtual void paint(QGraphicsScene*  g);
virtual QPaintEngine*  paintEngine() const;
virtual void paintEvent(QPaintEvent*  event);
virtual void paintTargetPanel(QGraphicsScene*  g);
virtual void putItem(Positionable*  l);
virtual QPaintDevice*  redirected(QPoint*  offset) const;
virtual void redrawPanel();
virtual void repaint();
virtual void resizeEvent(QResizeEvent*  e);
virtual void setAllEditable(bool  edit);
virtual void setAllPositionable(bool  state);
virtual void setEnabled(bool  b);
virtual void setNextLocation(Positionable*  obj);
virtual void setRemoveMenu(Positionable*  p, QMenu*  popup);
virtual void setScroll(int  state);
virtual void setSelectionsRotation(int  k, Positionable*  p);
virtual void setSelectionsScale(double  s, Positionable*  p);
virtual void setTitle();
virtual void setUseGlobalFlag(bool  set);
virtual void setVisible(bool  visible);
virtual QPainter*  sharedPainter() const;
virtual void showEvent(QShowEvent*  event);
virtual QSize  sizeHint() const;
virtual void storeValues();
virtual void tabletEvent(QTabletEvent*  event);
virtual void targetWindowClosing(bool  save);
virtual void targetWindowClosingEvent(QCloseEvent*  e);
virtual void timerEvent(QTimerEvent*  event);
virtual bool  useGlobalFlag();
virtual void vetoableChange(PropertyChangeEvent*  evt);
virtual void wheelEvent(QWheelEvent*  event);
virtual void windowClosing(QCloseEvent*  e);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_ControlPanelEditor : public ControlPanelEditor
{ public:
inline void promoted_copyItem(Positionable*  p) { this->copyItem(p); }
inline void promoted_disableMenus() { this->disableMenus(); }
inline Positionable*  promoted_getCopySelection(QGraphicsSceneMouseEvent*  event) { return this->getCopySelection(event); }
inline Positionable*  promoted_getCurrentSelection(QGraphicsSceneMouseEvent*  event) { return this->getCurrentSelection(event); }
inline QList<Positionable* >*  promoted_getSelectionGroup() { return this->getSelectionGroup(); }
inline void promoted_highlight(Positionable*  pos) { this->highlight(pos); }
inline void promoted_init(QString  name) { this->init(name); }
inline void promoted_makeCircuitMenu() { this->makeCircuitMenu(); }
inline void promoted_makeCircuitMenu(bool  edit) { this->makeCircuitMenu(edit); }
inline void promoted_makeDataFlavors() { this->makeDataFlavors(); }
inline void promoted_makeDrawMenu() { this->makeDrawMenu(); }
inline void promoted_makeEditMenu() { this->makeEditMenu(); }
inline void promoted_makeIconMenu() { this->makeIconMenu(); }
inline void promoted_makeMarkerMenu() { this->makeMarkerMenu(); }
inline void promoted_makeOptionMenu() { this->makeOptionMenu(); }
inline void promoted_makeWarrantMenu(bool  arg__1, bool  arg__2) { this->makeWarrantMenu(arg__1, arg__2); }
inline void promoted_makeZoomMenu() { this->makeZoomMenu(); }
inline void promoted_paintTargetPanel(QGraphicsScene*  g) { this->paintTargetPanel(g); }
inline void promoted_setSecondSelectionGroup(QList<Positionable* >*  list) { this->setSecondSelectionGroup(list); }
inline void promoted_setSelectionsRotation(int  k, Positionable*  p) { this->setSelectionsRotation(k, p); }
inline void promoted_setSelectionsScale(double  s, Positionable*  p) { this->setSelectionsScale(s, p); }
inline void promoted_showPopUp(Positionable*  p, QGraphicsSceneMouseEvent*  event) { this->showPopUp(p, event); }
inline void promoted_targetWindowClosingEvent(QCloseEvent*  e) { this->targetWindowClosingEvent(e); }
inline QString  py_q_getClassName() { return ControlPanelEditor::getClassName(); }
inline void py_q_init(QString  name) { ControlPanelEditor::init(name); }
inline void py_q_initView() { ControlPanelEditor::initView(); }
inline void py_q_keyPressEvent(QKeyEvent*  e) { ControlPanelEditor::keyPressEvent(e); }
inline void py_q_keyReleaseEvent(QKeyEvent*  e) { ControlPanelEditor::keyReleaseEvent(e); }
inline void py_q_mouseClicked(QGraphicsSceneMouseEvent*  event) { ControlPanelEditor::mouseClicked(event); }
inline void py_q_mouseDragged(QGraphicsSceneMouseEvent*  event) { ControlPanelEditor::mouseDragged(event); }
inline void py_q_mouseEntered(QGraphicsSceneMouseEvent*  event) { ControlPanelEditor::mouseEntered(event); }
inline void py_q_mouseExited(QGraphicsSceneMouseEvent*  event) { ControlPanelEditor::mouseExited(event); }
inline void py_q_mouseMoved(QGraphicsSceneMouseEvent*  event) { ControlPanelEditor::mouseMoved(event); }
inline void py_q_mousePressed(QGraphicsSceneMouseEvent*  event) { ControlPanelEditor::mousePressed(event); }
inline void py_q_mouseReleased(QGraphicsSceneMouseEvent*  event) { ControlPanelEditor::mouseReleased(event); }
inline void py_q_paintTargetPanel(QGraphicsScene*  g) { ControlPanelEditor::paintTargetPanel(g); }
inline void py_q_setAllEditable(bool  edit) { ControlPanelEditor::setAllEditable(edit); }
inline void py_q_setNextLocation(Positionable*  obj) { ControlPanelEditor::setNextLocation(obj); }
inline void py_q_setSelectionsRotation(int  k, Positionable*  p) { ControlPanelEditor::setSelectionsRotation(k, p); }
inline void py_q_setSelectionsScale(double  s, Positionable*  p) { ControlPanelEditor::setSelectionsScale(s, p); }
inline void py_q_setTitle() { ControlPanelEditor::setTitle(); }
inline void py_q_setUseGlobalFlag(bool  set) { ControlPanelEditor::setUseGlobalFlag(set); }
inline void py_q_targetWindowClosingEvent(QCloseEvent*  e) { ControlPanelEditor::targetWindowClosingEvent(e); }
};

class PythonQtWrapper_ControlPanelEditor : public QObject
{ Q_OBJECT
public:
public slots:
ControlPanelEditor* new_ControlPanelEditor(QString  name, QWidget*  parent = 0);
ControlPanelEditor* new_ControlPanelEditor(QWidget*  parent = 0);
ControlPanelEditor* new_ControlPanelEditor(const ControlPanelEditor&  other);
void delete_ControlPanelEditor(ControlPanelEditor* obj) { delete obj; } 
   void copyItem(ControlPanelEditor* theWrappedObject, Positionable*  p);
   void disableMenus(ControlPanelEditor* theWrappedObject);
   QString  py_q_getClassName(ControlPanelEditor* theWrappedObject){  return (((PythonQtPublicPromoter_ControlPanelEditor*)theWrappedObject)->py_q_getClassName());}
   QList<Positionable* >*  getClipGroup(ControlPanelEditor* theWrappedObject);
   Positionable*  getCopySelection(ControlPanelEditor* theWrappedObject, QGraphicsSceneMouseEvent*  event);
   Positionable*  getCurrentSelection(ControlPanelEditor* theWrappedObject, QGraphicsSceneMouseEvent*  event);
   QList<Positionable* >*  getSelectionGroup(ControlPanelEditor* theWrappedObject);
   bool  getShapeSelect(ControlPanelEditor* theWrappedObject);
   void highlight(ControlPanelEditor* theWrappedObject, Positionable*  pos);
   void py_q_init(ControlPanelEditor* theWrappedObject, QString  name){  (((PythonQtPublicPromoter_ControlPanelEditor*)theWrappedObject)->py_q_init(name));}
   void py_q_initView(ControlPanelEditor* theWrappedObject){  (((PythonQtPublicPromoter_ControlPanelEditor*)theWrappedObject)->py_q_initView());}
   void py_q_keyPressEvent(ControlPanelEditor* theWrappedObject, QKeyEvent*  e){  (((PythonQtPublicPromoter_ControlPanelEditor*)theWrappedObject)->py_q_keyPressEvent(e));}
   void py_q_keyReleaseEvent(ControlPanelEditor* theWrappedObject, QKeyEvent*  e){  (((PythonQtPublicPromoter_ControlPanelEditor*)theWrappedObject)->py_q_keyReleaseEvent(e));}
   void loadComplete(ControlPanelEditor* theWrappedObject);
   void makeCircuitMenu(ControlPanelEditor* theWrappedObject);
   void makeDataFlavors(ControlPanelEditor* theWrappedObject);
   void makeDrawMenu(ControlPanelEditor* theWrappedObject);
   void makeEditMenu(ControlPanelEditor* theWrappedObject);
   void makeIconMenu(ControlPanelEditor* theWrappedObject);
   void makeMarkerMenu(ControlPanelEditor* theWrappedObject);
   void makeOptionMenu(ControlPanelEditor* theWrappedObject);
   void makeWarrantMenu(ControlPanelEditor* theWrappedObject, bool  arg__1, bool  arg__2);
   void makeZoomMenu(ControlPanelEditor* theWrappedObject);
   void py_q_mouseClicked(ControlPanelEditor* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_ControlPanelEditor*)theWrappedObject)->py_q_mouseClicked(event));}
   void py_q_mouseDragged(ControlPanelEditor* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_ControlPanelEditor*)theWrappedObject)->py_q_mouseDragged(event));}
   void py_q_mouseEntered(ControlPanelEditor* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_ControlPanelEditor*)theWrappedObject)->py_q_mouseEntered(event));}
   void py_q_mouseExited(ControlPanelEditor* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_ControlPanelEditor*)theWrappedObject)->py_q_mouseExited(event));}
   void py_q_mouseMoved(ControlPanelEditor* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_ControlPanelEditor*)theWrappedObject)->py_q_mouseMoved(event));}
   void py_q_mousePressed(ControlPanelEditor* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_ControlPanelEditor*)theWrappedObject)->py_q_mousePressed(event));}
   void py_q_mouseReleased(ControlPanelEditor* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_ControlPanelEditor*)theWrappedObject)->py_q_mouseReleased(event));}
   void py_q_paintTargetPanel(ControlPanelEditor* theWrappedObject, QGraphicsScene*  g){  (((PythonQtPublicPromoter_ControlPanelEditor*)theWrappedObject)->py_q_paintTargetPanel(g));}
   void resetEditor(ControlPanelEditor* theWrappedObject);
   void py_q_setAllEditable(ControlPanelEditor* theWrappedObject, bool  edit){  (((PythonQtPublicPromoter_ControlPanelEditor*)theWrappedObject)->py_q_setAllEditable(edit));}
   void setColorMenu(ControlPanelEditor* theWrappedObject, QMenu*  popup, QWidget*  pos, int  type);
   void setCopyMenu(ControlPanelEditor* theWrappedObject, Positionable*  p, QMenu*  popup);
   void py_q_setNextLocation(ControlPanelEditor* theWrappedObject, Positionable*  obj){  (((PythonQtPublicPromoter_ControlPanelEditor*)theWrappedObject)->py_q_setNextLocation(obj));}
   void setSecondSelectionGroup(ControlPanelEditor* theWrappedObject, QList<Positionable* >*  list);
   void setSelectionGroup(ControlPanelEditor* theWrappedObject, QList<Positionable* >*  group);
   void py_q_setSelectionsRotation(ControlPanelEditor* theWrappedObject, int  k, Positionable*  p){  (((PythonQtPublicPromoter_ControlPanelEditor*)theWrappedObject)->py_q_setSelectionsRotation(k, p));}
   void py_q_setSelectionsScale(ControlPanelEditor* theWrappedObject, double  s, Positionable*  p){  (((PythonQtPublicPromoter_ControlPanelEditor*)theWrappedObject)->py_q_setSelectionsScale(s, p));}
   void setShapeSelect(ControlPanelEditor* theWrappedObject, bool  set);
   void py_q_setTitle(ControlPanelEditor* theWrappedObject){  (((PythonQtPublicPromoter_ControlPanelEditor*)theWrappedObject)->py_q_setTitle());}
   void py_q_setUseGlobalFlag(ControlPanelEditor* theWrappedObject, bool  set){  (((PythonQtPublicPromoter_ControlPanelEditor*)theWrappedObject)->py_q_setUseGlobalFlag(set));}
   void showPopUp(ControlPanelEditor* theWrappedObject, Positionable*  p, QGraphicsSceneMouseEvent*  event);
   void py_q_targetWindowClosingEvent(ControlPanelEditor* theWrappedObject, QCloseEvent*  e){  (((PythonQtPublicPromoter_ControlPanelEditor*)theWrappedObject)->py_q_targetWindowClosingEvent(e));}
void py_set__debug(ControlPanelEditor* theWrappedObject, bool  _debug){ theWrappedObject->_debug = _debug; }
bool  py_get__debug(ControlPanelEditor* theWrappedObject){ return theWrappedObject->_debug; }
};





class PythonQtShell_DccLocoAddress : public DccLocoAddress
{
public:
    PythonQtShell_DccLocoAddress(QObject*  parent = 0):DccLocoAddress(parent),_wrapper(NULL) {}
    PythonQtShell_DccLocoAddress(const DccLocoAddress&  l, QObject*  parent = 0):DccLocoAddress(l, parent),_wrapper(NULL) {}
    PythonQtShell_DccLocoAddress(int  number, LocoAddress::Protocol  protocol, QObject*  parent = 0):DccLocoAddress(number, protocol, parent),_wrapper(NULL) {}
    PythonQtShell_DccLocoAddress(int  number, bool  isLong, QObject*  parent = 0):DccLocoAddress(number, isLong, parent),_wrapper(NULL) {}

   ~PythonQtShell_DccLocoAddress();

virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  equals(QObject*  a);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual int  getNumber() const;
virtual LocoAddress::Protocol  getProtocol() const;
virtual int  hashCode() const;
virtual void timerEvent(QTimerEvent*  event);
virtual QString  toString();

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_DccLocoAddress : public DccLocoAddress
{ public:
inline bool  py_q_equals(QObject*  a) { return DccLocoAddress::equals(a); }
inline int  py_q_getNumber() const { return DccLocoAddress::getNumber(); }
inline LocoAddress::Protocol  py_q_getProtocol() const { return DccLocoAddress::getProtocol(); }
inline int  py_q_hashCode() const { return DccLocoAddress::hashCode(); }
inline QString  py_q_toString() { return DccLocoAddress::toString(); }
};

class PythonQtWrapper_DccLocoAddress : public QObject
{ Q_OBJECT
public:
public slots:
DccLocoAddress* new_DccLocoAddress(QObject*  parent = 0);
DccLocoAddress* new_DccLocoAddress(const DccLocoAddress&  l, QObject*  parent = 0);
DccLocoAddress* new_DccLocoAddress(int  number, LocoAddress::Protocol  protocol, QObject*  parent = 0);
DccLocoAddress* new_DccLocoAddress(int  number, bool  isLong, QObject*  parent = 0);
void delete_DccLocoAddress(DccLocoAddress* obj) { delete obj; } 
   bool  py_q_equals(DccLocoAddress* theWrappedObject, QObject*  a){  return (((PythonQtPublicPromoter_DccLocoAddress*)theWrappedObject)->py_q_equals(a));}
   int  py_q_getNumber(DccLocoAddress* theWrappedObject) const{  return (((PythonQtPublicPromoter_DccLocoAddress*)theWrappedObject)->py_q_getNumber());}
   LocoAddress::Protocol  py_q_getProtocol(DccLocoAddress* theWrappedObject) const{  return (((PythonQtPublicPromoter_DccLocoAddress*)theWrappedObject)->py_q_getProtocol());}
   int  py_q_hashCode(DccLocoAddress* theWrappedObject) const{  return (((PythonQtPublicPromoter_DccLocoAddress*)theWrappedObject)->py_q_hashCode());}
   bool  isLongAddress(DccLocoAddress* theWrappedObject);
   QString  py_q_toString(DccLocoAddress* theWrappedObject){  return (((PythonQtPublicPromoter_DccLocoAddress*)theWrappedObject)->py_q_toString());}
    QString py_toString(DccLocoAddress*);
};





class PythonQtShell_DccThrottle : public DccThrottle
{
public:
    PythonQtShell_DccThrottle(QObject*  parent = 0):DccThrottle(parent),_wrapper(NULL) {}
    PythonQtShell_DccThrottle(const DccThrottle&  arg__1):DccThrottle(arg__1),_wrapper(NULL) {}

   ~PythonQtShell_DccThrottle();

virtual void addPropertyChangeListener(PropertyChangeListener*  arg__1);
virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
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
virtual bool  getFunction(int  functionNum);
virtual bool  getFunctionMomentary(int  fN);
virtual QVector<bool >  getFunctions();
virtual QVector<bool >  getFunctionsMomentary();
virtual bool  getIsForward();
virtual QVector<PropertyChangeListener* >*  getListeners();
virtual LocoAddress*  getLocoAddress();
virtual BasicRosterEntry*  getRosterEntry();
virtual float  getSpeedIncrement();
virtual float  getSpeedSetting();
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
virtual void setFunction(int  functionNum, bool  newState);
virtual void setFunctionMomentary(int  momFuncNum, bool  state);
virtual void setIsForward(bool  arg__1);
virtual void setRosterEntry(BasicRosterEntry*  arg__1);
virtual void setSpeedSetting(float  arg__1);
virtual void setSpeedSetting(float  speed, bool  allowDuplicates, bool  allowDuplicatesOnStop);
virtual void setSpeedSettingAgain(float  speed);
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_DccThrottle : public DccThrottle
{ public:
inline float  py_q_getSpeedIncrement() { return DccThrottle::getSpeedIncrement(); }
};

class PythonQtWrapper_DccThrottle : public QObject
{ Q_OBJECT
public:
public slots:
DccThrottle* new_DccThrottle(QObject*  parent = 0);
DccThrottle* new_DccThrottle(const DccThrottle&  arg__1);
void delete_DccThrottle(DccThrottle* obj) { delete obj; } 
   float  getSpeedIncrement(DccThrottle* theWrappedObject);
   float  py_q_getSpeedIncrement(DccThrottle* theWrappedObject){  return (((PythonQtPublicPromoter_DccThrottle*)theWrappedObject)->py_q_getSpeedIncrement());}
};





class PythonQtShell_DefaultLogixManager : public DefaultLogixManager
{
public:
    PythonQtShell_DefaultLogixManager(QObject*  parent = 0):DefaultLogixManager(parent),_wrapper(NULL) {}

   ~PythonQtShell_DefaultLogixManager();

virtual void activateAllLogixs();
virtual QString  getBeanTypeHandled(bool  plural) const;
virtual QString  getNamedBeanClass() const;
virtual QString  getSystemPrefix() const;
virtual int  getXMLOrder() const;
virtual void setLoadDisabled(bool  s);
virtual char  typeLetter() const;

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_DefaultLogixManager : public DefaultLogixManager
{ public:
inline void py_q_activateAllLogixs() { DefaultLogixManager::activateAllLogixs(); }
inline QString  py_q_getBeanTypeHandled(bool  plural) const { return DefaultLogixManager::getBeanTypeHandled(plural); }
inline QString  py_q_getNamedBeanClass() const { return DefaultLogixManager::getNamedBeanClass(); }
inline QString  py_q_getSystemPrefix() const { return DefaultLogixManager::getSystemPrefix(); }
inline int  py_q_getXMLOrder() const { return DefaultLogixManager::getXMLOrder(); }
inline void py_q_setLoadDisabled(bool  s) { DefaultLogixManager::setLoadDisabled(s); }
inline char  py_q_typeLetter() const { return DefaultLogixManager::typeLetter(); }
};

class PythonQtWrapper_DefaultLogixManager : public QObject
{ Q_OBJECT
public:
public slots:
DefaultLogixManager* new_DefaultLogixManager(QObject*  parent = 0);
void delete_DefaultLogixManager(DefaultLogixManager* obj) { delete obj; } 
   void activateAllLogixs(DefaultLogixManager* theWrappedObject);
   void py_q_activateAllLogixs(DefaultLogixManager* theWrappedObject){  (((PythonQtPublicPromoter_DefaultLogixManager*)theWrappedObject)->py_q_activateAllLogixs());}
   QString  getBeanTypeHandled(DefaultLogixManager* theWrappedObject, bool  plural) const;
   QString  py_q_getBeanTypeHandled(DefaultLogixManager* theWrappedObject, bool  plural) const{  return (((PythonQtPublicPromoter_DefaultLogixManager*)theWrappedObject)->py_q_getBeanTypeHandled(plural));}
   QString  getNamedBeanClass(DefaultLogixManager* theWrappedObject) const;
   QString  py_q_getNamedBeanClass(DefaultLogixManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_DefaultLogixManager*)theWrappedObject)->py_q_getNamedBeanClass());}
   QString  getSystemPrefix(DefaultLogixManager* theWrappedObject) const;
   QString  py_q_getSystemPrefix(DefaultLogixManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_DefaultLogixManager*)theWrappedObject)->py_q_getSystemPrefix());}
   int  getXMLOrder(DefaultLogixManager* theWrappedObject) const;
   int  py_q_getXMLOrder(DefaultLogixManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_DefaultLogixManager*)theWrappedObject)->py_q_getXMLOrder());}
   DefaultLogixManager*  static_DefaultLogixManager_instance();
   void setLoadDisabled(DefaultLogixManager* theWrappedObject, bool  s);
   void py_q_setLoadDisabled(DefaultLogixManager* theWrappedObject, bool  s){  (((PythonQtPublicPromoter_DefaultLogixManager*)theWrappedObject)->py_q_setLoadDisabled(s));}
   char  typeLetter(DefaultLogixManager* theWrappedObject) const;
   char  py_q_typeLetter(DefaultLogixManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_DefaultLogixManager*)theWrappedObject)->py_q_typeLetter());}
};


