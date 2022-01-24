#include <PythonQt.h>
#include <QObject>
#include <QVariant>
#include <abstractautomaton.h>
#include <abstractnamedbean.h>
#include <abstractportcontroller.h>
#include <abstractsensor.h>
#include <abstractserialportcontroller.h>
#include <abstractshutdowntask.h>
#include <abstractturnout.h>
#include <audio.h>
#include <audiobuffer.h>
#include <audiolistener.h>
#include <audiosource.h>
#include <basicrosterentry.h>
#include <beaninterface.h>
#include <beantabledatamodel.h>
#include <beantableframe.h>
#include <beantablemodel.h>
#include <block.h>
#include <controlpaneleditor.h>
#include <dcclocoaddress.h>
#include <dccthrottle.h>
#include <defaultprogrammermanager.h>
#include <editor.h>
#include <editscene.h>
#include <eventobject.h>
#include <fileutil.h>
#include <flowlayout.h>
#include <jframe.h>
#include <jlabel.h>
#include <jlist.h>
#include <jmrijframe.h>
#include <jtable.h>
#include <locoaddress.h>
#include <namedbean.h>
#include <positionable.h>
#include <propertychangeevent.h>
#include <propertychangelistener.h>
#include <qabstractitemdelegate.h>
#include <qabstractitemmodel.h>
#include <qaction.h>
#include <qbrush.h>
#include <qbytearray.h>
#include <qcolor.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qdatastream.h>
#include <qdir.h>
#include <qdom.h>
#include <qevent.h>
#include <qfile.h>
#include <qfont.h>
#include <qfontinfo.h>
#include <qfontmetrics.h>
#include <qgraphicsitem.h>
#include <qgraphicsproxywidget.h>
#include <qgraphicsscene.h>
#include <qgraphicssceneevent.h>
#include <qgraphicsview.h>
#include <qgraphicswidget.h>
#include <qicon.h>
#include <qitemselectionmodel.h>
#include <qkeysequence.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qlayoutitem.h>
#include <qline.h>
#include <qlistview.h>
#include <qlocale.h>
#include <qmainwindow.h>
#include <qmargins.h>
#include <qmenu.h>
#include <qmetaobject.h>
#include <qobject.h>
#include <qpaintdevice.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qpalette.h>
#include <qpen.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qpolygon.h>
#include <qpushbutton.h>
#include <qqueue.h>
#include <qrect.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstatusbar.h>
#include <qstringlist.h>
#include <qstyle.h>
#include <qstyleditemdelegate.h>
#include <qstyleoption.h>
#include <qtableview.h>
#include <qtextstream.h>
#include <qtransform.h>
#include <qurl.h>
#include <qvector.h>
#include <qvector3d.h>
#include <qwidget.h>
#include <sensor.h>
#include <systemconnectionmemo.h>
#include <tablecolumn.h>
#include <tablecolumnmodel.h>
#include <turnout.h>
#include <turnoutoperation.h>
#include <windowlistener.h>



class PythonQtShell_AbstractAutomaton : public AbstractAutomaton
{
public:
    PythonQtShell_AbstractAutomaton(QObject*  parent = 0):AbstractAutomaton(parent),_wrapper(NULL) {}
    PythonQtShell_AbstractAutomaton(QString  name, QObject*  parent = 0):AbstractAutomaton(name, parent),_wrapper(NULL) {}

   ~PythonQtShell_AbstractAutomaton();

virtual bool  handle();
virtual void init();
virtual QObject*  self();

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
inline QObject*  py_q_self() { return AbstractAutomaton::self(); }
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
   DccThrottle*  getThrottle(AbstractAutomaton* theWrappedObject, BasicRosterEntry*  re, int  waitSecs);
   DccThrottle*  getThrottle(AbstractAutomaton* theWrappedObject, int  address, bool  longAddress);
   DccThrottle*  getThrottle(AbstractAutomaton* theWrappedObject, int  address, bool  longAddress, int  waitSecs);
   bool  handle(AbstractAutomaton* theWrappedObject);
   bool  py_q_handle(AbstractAutomaton* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractAutomaton*)theWrappedObject)->py_q_handle());}
   void py_q_init(AbstractAutomaton* theWrappedObject){  (((PythonQtPublicPromoter_AbstractAutomaton*)theWrappedObject)->py_q_init());}
   void notifyAll(AbstractAutomaton* theWrappedObject);
   void notifyFailedThrottleRequest(AbstractAutomaton* theWrappedObject, DccLocoAddress*  address, QString  reason);
   void notifyThrottleFound(AbstractAutomaton* theWrappedObject, DccThrottle*  t);
   int  readServiceModeCV(AbstractAutomaton* theWrappedObject, QString  CV);
   QObject*  self(AbstractAutomaton* theWrappedObject);
   QObject*  py_q_self(AbstractAutomaton* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractAutomaton*)theWrappedObject)->py_q_self());}
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
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners() const;
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
virtual void setUserName(QString  s);
virtual void timerEvent(QTimerEvent*  event);
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);
virtual void vetoableChange(PropertyChangeEvent*  arg__1);

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
inline QVector<PropertyChangeListener* >  py_q_getPropertyChangeListeners() const { return AbstractNamedBean::getPropertyChangeListeners(); }
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
inline void py_q_setUserName(QString  s) { AbstractNamedBean::setUserName(s); }
inline void py_q_updateListenerRef(PropertyChangeListener*  l, QString  newName) { AbstractNamedBean::updateListenerRef(l, newName); }
inline void py_q_vetoableChange(PropertyChangeEvent*  arg__1) { AbstractNamedBean::vetoableChange(arg__1); }
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
   QVector<PropertyChangeListener* >  getPropertyChangeListeners(AbstractNamedBean* theWrappedObject) const;
   QVector<PropertyChangeListener* >  py_q_getPropertyChangeListeners(AbstractNamedBean* theWrappedObject) const{  return (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_getPropertyChangeListeners());}
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
   void py_q_setUserName(AbstractNamedBean* theWrappedObject, QString  s){  (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_setUserName(s));}
   void py_q_updateListenerRef(AbstractNamedBean* theWrappedObject, PropertyChangeListener*  l, QString  newName){  (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_updateListenerRef(l, newName));}
   void py_q_vetoableChange(AbstractNamedBean* theWrappedObject, PropertyChangeEvent*  arg__1){  (((PythonQtPublicPromoter_AbstractNamedBean*)theWrappedObject)->py_q_vetoableChange(arg__1));}
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
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners() const;
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
virtual void setUserName(QString  s);
virtual void timerEvent(QTimerEvent*  event);
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);
virtual bool  useDefaultTimerSettings();
virtual void useDefaultTimerSettings(bool  boo);
virtual void vetoableChange(PropertyChangeEvent*  arg__1);

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





class PythonQtShell_AbstractSerialPortController : public AbstractSerialPortController
{
public:
    PythonQtShell_AbstractSerialPortController(SystemConnectionMemo*  connectionMemo, QObject*  parent = 0):AbstractSerialPortController(connectionMemo, parent),_wrapper(NULL) {}

   ~PythonQtShell_AbstractSerialPortController();

virtual void _connect();
virtual void autoConfigure();
virtual void childEvent(QChildEvent*  event);
virtual QString  className();
virtual void closeConnection();
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
inline void promoted_closeConnection() { this->closeConnection(); }
inline void promoted_resetupConnection() { this->resetupConnection(); }
inline void py_q__connect() { AbstractSerialPortController::_connect(); }
inline void py_q_closeConnection() { AbstractSerialPortController::closeConnection(); }
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
   void closeConnection(AbstractSerialPortController* theWrappedObject);
   void py_q_closeConnection(AbstractSerialPortController* theWrappedObject){  (((PythonQtPublicPromoter_AbstractSerialPortController*)theWrappedObject)->py_q_closeConnection());}
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

virtual bool  call();
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

virtual bool  canInvert() const;
virtual bool  canLock(int  turnoutLockout);
virtual QString  describeState(int  state);
virtual void dispose();
virtual void enableLockOperation(int  turnoutLockout, bool  enabled);
virtual void forwardCommandChangeToLayout();
virtual void forwardCommandChangeToLayout(int  s);
virtual QString  getBeanType();
virtual int  getCommandedState();
virtual int  getControlType();
virtual QString  getDecoderName();
virtual float  getDivergingLimit();
virtual QString  getDivergingSpeed();
virtual int  getFeedbackMode();
virtual QString  getFeedbackModeName();
virtual Sensor*  getFirstSensor();
virtual bool  getInhibitOperation();
virtual bool  getInverted();
virtual int  getKnownState();
virtual Turnout*  getLeadingTurnout();
virtual bool  getLocked(int  turnoutLockout);
virtual int  getNumberOutputBits();
virtual bool  getReportLocked();
virtual Sensor*  getSecondSensor();
virtual int  getState();
virtual float  getStraightLimit();
virtual QString  getStraightSpeed();
virtual TurnoutOperation*  getTurnoutOperation();
virtual QStringList  getValidDecoderNames();
virtual QVector<QString >  getValidFeedbackNames();
virtual int  getValidFeedbackTypes();
virtual bool  isCanFollow();
virtual bool  isConsistentState();
virtual bool  isFollowingCommandedState();
virtual void propertyChange(PropertyChangeEvent*  evt);
virtual void provideFirstFeedbackSensor(QString  pName);
virtual void provideSecondFeedbackSensor(QString  pName);
virtual void requestUpdateFromLayout();
virtual QObject*  self();
virtual void setBinaryOutput(bool  state);
virtual void setCommandedState(int  s);
virtual void setCommandedStateAtInterval(int  s);
virtual void setControlType(int  num);
virtual void setDecoderName(QString  decoderName);
virtual void setDivergingSpeed(QString  s) const;
virtual void setFeedbackMode(QString  mode);
virtual void setFeedbackMode(int  mode);
virtual void setFollowingCommandedState(bool  following);
virtual void setInhibitOperation(bool  io);
virtual void setInitialKnownStateFromFeedback();
virtual void setInverted(bool  inverted);
virtual void setLeadingTurnout(Turnout*  turnout);
virtual void setLeadingTurnout(Turnout*  turnout, bool  followingCommandedState);
virtual void setLocked(int  turnoutLockout, bool  locked);
virtual void setNumberOutputBits(int  num);
virtual void setReportLocked(bool  reportLocked);
virtual void setState(int  s);
virtual void setStraightSpeed(QString  s) const;
virtual void setTurnoutOperation(TurnoutOperation*  toper);
virtual void turnoutPushbuttonLockout(bool  locked);
virtual void vetoableChange(PropertyChangeEvent*  evt);

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
inline Turnout*  py_q_getLeadingTurnout() { return AbstractTurnout::getLeadingTurnout(); }
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
inline bool  py_q_isCanFollow() { return AbstractTurnout::isCanFollow(); }
inline bool  py_q_isConsistentState() { return AbstractTurnout::isConsistentState(); }
inline bool  py_q_isFollowingCommandedState() { return AbstractTurnout::isFollowingCommandedState(); }
inline void py_q_propertyChange(PropertyChangeEvent*  evt) { AbstractTurnout::propertyChange(evt); }
inline void py_q_provideFirstFeedbackSensor(QString  pName) { AbstractTurnout::provideFirstFeedbackSensor(pName); }
inline void py_q_provideSecondFeedbackSensor(QString  pName) { AbstractTurnout::provideSecondFeedbackSensor(pName); }
inline void py_q_requestUpdateFromLayout() { AbstractTurnout::requestUpdateFromLayout(); }
inline QObject*  py_q_self() { return AbstractTurnout::self(); }
inline void py_q_setBinaryOutput(bool  state) { AbstractTurnout::setBinaryOutput(state); }
inline void py_q_setCommandedState(int  s) { AbstractTurnout::setCommandedState(s); }
inline void py_q_setCommandedStateAtInterval(int  s) { AbstractTurnout::setCommandedStateAtInterval(s); }
inline void py_q_setControlType(int  num) { AbstractTurnout::setControlType(num); }
inline void py_q_setDecoderName(QString  decoderName) { AbstractTurnout::setDecoderName(decoderName); }
inline void py_q_setDivergingSpeed(QString  s) const { AbstractTurnout::setDivergingSpeed(s); }
inline void py_q_setFeedbackMode(QString  mode) { AbstractTurnout::setFeedbackMode(mode); }
inline void py_q_setFeedbackMode(int  mode) { AbstractTurnout::setFeedbackMode(mode); }
inline void py_q_setFollowingCommandedState(bool  following) { AbstractTurnout::setFollowingCommandedState(following); }
inline void py_q_setInhibitOperation(bool  io) { AbstractTurnout::setInhibitOperation(io); }
inline void py_q_setInitialKnownStateFromFeedback() { AbstractTurnout::setInitialKnownStateFromFeedback(); }
inline void py_q_setInverted(bool  inverted) { AbstractTurnout::setInverted(inverted); }
inline void py_q_setLeadingTurnout(Turnout*  turnout) { AbstractTurnout::setLeadingTurnout(turnout); }
inline void py_q_setLeadingTurnout(Turnout*  turnout, bool  followingCommandedState) { AbstractTurnout::setLeadingTurnout(turnout, followingCommandedState); }
inline void py_q_setLocked(int  turnoutLockout, bool  locked) { AbstractTurnout::setLocked(turnoutLockout, locked); }
inline void py_q_setNumberOutputBits(int  num) { AbstractTurnout::setNumberOutputBits(num); }
inline void py_q_setReportLocked(bool  reportLocked) { AbstractTurnout::setReportLocked(reportLocked); }
inline void py_q_setState(int  s) { AbstractTurnout::setState(s); }
inline void py_q_setStraightSpeed(QString  s) const { AbstractTurnout::setStraightSpeed(s); }
inline void py_q_setTurnoutOperation(TurnoutOperation*  toper) { AbstractTurnout::setTurnoutOperation(toper); }
inline void py_q_turnoutPushbuttonLockout(bool  locked) { AbstractTurnout::turnoutPushbuttonLockout(locked); }
inline void py_q_vetoableChange(PropertyChangeEvent*  evt) { AbstractTurnout::vetoableChange(evt); }
};

class PythonQtWrapper_AbstractTurnout : public QObject
{ Q_OBJECT
public:
public slots:
AbstractTurnout* new_AbstractTurnout(QObject*  parent = 0);
AbstractTurnout* new_AbstractTurnout(QString  systemName, QObject*  parent = 0);
AbstractTurnout* new_AbstractTurnout(QString  systemName, QString  userName, QObject*  parent = 0);
void delete_AbstractTurnout(AbstractTurnout* obj) { delete obj; } 
   bool  canInvert(AbstractTurnout* theWrappedObject) const;
   bool  py_q_canInvert(AbstractTurnout* theWrappedObject) const{  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_canInvert());}
   bool  canLock(AbstractTurnout* theWrappedObject, int  turnoutLockout);
   bool  py_q_canLock(AbstractTurnout* theWrappedObject, int  turnoutLockout){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_canLock(turnoutLockout));}
   QString  describeState(AbstractTurnout* theWrappedObject, int  state);
   QString  py_q_describeState(AbstractTurnout* theWrappedObject, int  state){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_describeState(state));}
   void dispose(AbstractTurnout* theWrappedObject);
   void py_q_dispose(AbstractTurnout* theWrappedObject){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_dispose());}
   void enableLockOperation(AbstractTurnout* theWrappedObject, int  turnoutLockout, bool  enabled);
   void py_q_enableLockOperation(AbstractTurnout* theWrappedObject, int  turnoutLockout, bool  enabled){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_enableLockOperation(turnoutLockout, enabled));}
   void forwardCommandChangeToLayout(AbstractTurnout* theWrappedObject);
   void py_q_forwardCommandChangeToLayout(AbstractTurnout* theWrappedObject){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_forwardCommandChangeToLayout());}
   void forwardCommandChangeToLayout(AbstractTurnout* theWrappedObject, int  s);
   void py_q_forwardCommandChangeToLayout(AbstractTurnout* theWrappedObject, int  s){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_forwardCommandChangeToLayout(s));}
   QString  getBeanType(AbstractTurnout* theWrappedObject);
   QString  py_q_getBeanType(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getBeanType());}
   int  getCommandedState(AbstractTurnout* theWrappedObject);
   int  py_q_getCommandedState(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getCommandedState());}
   int  getControlType(AbstractTurnout* theWrappedObject);
   int  py_q_getControlType(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getControlType());}
   QString  getDecoderName(AbstractTurnout* theWrappedObject);
   QString  py_q_getDecoderName(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getDecoderName());}
   float  getDivergingLimit(AbstractTurnout* theWrappedObject);
   float  py_q_getDivergingLimit(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getDivergingLimit());}
   QString  getDivergingSpeed(AbstractTurnout* theWrappedObject);
   QString  py_q_getDivergingSpeed(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getDivergingSpeed());}
   int  getFeedbackMode(AbstractTurnout* theWrappedObject);
   int  py_q_getFeedbackMode(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getFeedbackMode());}
   int  getFeedbackModeForOperation(AbstractTurnout* theWrappedObject);
   QString  getFeedbackModeName(AbstractTurnout* theWrappedObject);
   QString  py_q_getFeedbackModeName(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getFeedbackModeName());}
   Sensor*  getFirstSensor(AbstractTurnout* theWrappedObject);
   Sensor*  py_q_getFirstSensor(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getFirstSensor());}
   bool  getInhibitOperation(AbstractTurnout* theWrappedObject);
   bool  py_q_getInhibitOperation(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getInhibitOperation());}
   bool  getInverted(AbstractTurnout* theWrappedObject);
   bool  py_q_getInverted(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getInverted());}
   int  getKnownState(AbstractTurnout* theWrappedObject);
   int  py_q_getKnownState(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getKnownState());}
   Turnout*  getLeadingTurnout(AbstractTurnout* theWrappedObject);
   Turnout*  py_q_getLeadingTurnout(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getLeadingTurnout());}
   bool  getLocked(AbstractTurnout* theWrappedObject, int  turnoutLockout);
   bool  py_q_getLocked(AbstractTurnout* theWrappedObject, int  turnoutLockout){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getLocked(turnoutLockout));}
   int  getNumberOutputBits(AbstractTurnout* theWrappedObject);
   int  py_q_getNumberOutputBits(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getNumberOutputBits());}
   bool  getReportLocked(AbstractTurnout* theWrappedObject);
   bool  py_q_getReportLocked(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getReportLocked());}
   Sensor*  getSecondSensor(AbstractTurnout* theWrappedObject);
   Sensor*  py_q_getSecondSensor(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getSecondSensor());}
   int  getState(AbstractTurnout* theWrappedObject);
   int  py_q_getState(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getState());}
   float  getStraightLimit(AbstractTurnout* theWrappedObject);
   float  py_q_getStraightLimit(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getStraightLimit());}
   QString  getStraightSpeed(AbstractTurnout* theWrappedObject);
   QString  py_q_getStraightSpeed(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getStraightSpeed());}
   TurnoutOperation*  getTurnoutOperation(AbstractTurnout* theWrappedObject);
   TurnoutOperation*  py_q_getTurnoutOperation(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getTurnoutOperation());}
   QStringList  getValidDecoderNames(AbstractTurnout* theWrappedObject);
   QStringList  py_q_getValidDecoderNames(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getValidDecoderNames());}
   QVector<QString >  getValidFeedbackNames(AbstractTurnout* theWrappedObject);
   QVector<QString >  py_q_getValidFeedbackNames(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getValidFeedbackNames());}
   int  getValidFeedbackTypes(AbstractTurnout* theWrappedObject);
   int  py_q_getValidFeedbackTypes(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_getValidFeedbackTypes());}
   bool  isCanFollow(AbstractTurnout* theWrappedObject);
   bool  py_q_isCanFollow(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_isCanFollow());}
   bool  isConsistentState(AbstractTurnout* theWrappedObject);
   bool  py_q_isConsistentState(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_isConsistentState());}
   bool  isFollowingCommandedState(AbstractTurnout* theWrappedObject);
   bool  py_q_isFollowingCommandedState(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_isFollowingCommandedState());}
   void newCommandedState(AbstractTurnout* theWrappedObject, int  s);
   void newKnownState(AbstractTurnout* theWrappedObject, int  s);
   void operationPropertyChange(AbstractTurnout* theWrappedObject, PropertyChangeEvent*  evt);
   void py_q_propertyChange(AbstractTurnout* theWrappedObject, PropertyChangeEvent*  evt){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_propertyChange(evt));}
   void provideFirstFeedbackSensor(AbstractTurnout* theWrappedObject, QString  pName);
   void py_q_provideFirstFeedbackSensor(AbstractTurnout* theWrappedObject, QString  pName){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_provideFirstFeedbackSensor(pName));}
   void provideSecondFeedbackSensor(AbstractTurnout* theWrappedObject, QString  pName);
   void py_q_provideSecondFeedbackSensor(AbstractTurnout* theWrappedObject, QString  pName){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_provideSecondFeedbackSensor(pName));}
   void requestUpdateFromLayout(AbstractTurnout* theWrappedObject);
   void py_q_requestUpdateFromLayout(AbstractTurnout* theWrappedObject){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_requestUpdateFromLayout());}
   QObject*  self(AbstractTurnout* theWrappedObject);
   QObject*  py_q_self(AbstractTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_self());}
   void sensorPropertyChange(AbstractTurnout* theWrappedObject, PropertyChangeEvent*  evt);
   void setBinaryOutput(AbstractTurnout* theWrappedObject, bool  state);
   void py_q_setBinaryOutput(AbstractTurnout* theWrappedObject, bool  state){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setBinaryOutput(state));}
   void setCommandedState(AbstractTurnout* theWrappedObject, int  s);
   void py_q_setCommandedState(AbstractTurnout* theWrappedObject, int  s){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setCommandedState(s));}
   void setCommandedStateAtInterval(AbstractTurnout* theWrappedObject, int  s);
   void py_q_setCommandedStateAtInterval(AbstractTurnout* theWrappedObject, int  s){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setCommandedStateAtInterval(s));}
   void setControlType(AbstractTurnout* theWrappedObject, int  num);
   void py_q_setControlType(AbstractTurnout* theWrappedObject, int  num){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setControlType(num));}
   void setDecoderName(AbstractTurnout* theWrappedObject, QString  decoderName);
   void py_q_setDecoderName(AbstractTurnout* theWrappedObject, QString  decoderName){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setDecoderName(decoderName));}
   void setDivergingSpeed(AbstractTurnout* theWrappedObject, QString  s) const;
   void py_q_setDivergingSpeed(AbstractTurnout* theWrappedObject, QString  s) const{  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setDivergingSpeed(s));}
   void setFeedbackMode(AbstractTurnout* theWrappedObject, QString  mode);
   void py_q_setFeedbackMode(AbstractTurnout* theWrappedObject, QString  mode){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setFeedbackMode(mode));}
   void setFeedbackMode(AbstractTurnout* theWrappedObject, int  mode);
   void py_q_setFeedbackMode(AbstractTurnout* theWrappedObject, int  mode){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setFeedbackMode(mode));}
   void setFollowingCommandedState(AbstractTurnout* theWrappedObject, bool  following);
   void py_q_setFollowingCommandedState(AbstractTurnout* theWrappedObject, bool  following){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setFollowingCommandedState(following));}
   void setInhibitOperation(AbstractTurnout* theWrappedObject, bool  io);
   void py_q_setInhibitOperation(AbstractTurnout* theWrappedObject, bool  io){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setInhibitOperation(io));}
   void setInitialKnownStateFromFeedback(AbstractTurnout* theWrappedObject);
   void py_q_setInitialKnownStateFromFeedback(AbstractTurnout* theWrappedObject){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setInitialKnownStateFromFeedback());}
   void setInverted(AbstractTurnout* theWrappedObject, bool  inverted);
   void py_q_setInverted(AbstractTurnout* theWrappedObject, bool  inverted){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setInverted(inverted));}
   void setKnownStateToCommanded(AbstractTurnout* theWrappedObject);
   void setLeadingTurnout(AbstractTurnout* theWrappedObject, Turnout*  turnout);
   void py_q_setLeadingTurnout(AbstractTurnout* theWrappedObject, Turnout*  turnout){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setLeadingTurnout(turnout));}
   void setLeadingTurnout(AbstractTurnout* theWrappedObject, Turnout*  turnout, bool  followingCommandedState);
   void py_q_setLeadingTurnout(AbstractTurnout* theWrappedObject, Turnout*  turnout, bool  followingCommandedState){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setLeadingTurnout(turnout, followingCommandedState));}
   void setLocked(AbstractTurnout* theWrappedObject, int  turnoutLockout, bool  locked);
   void py_q_setLocked(AbstractTurnout* theWrappedObject, int  turnoutLockout, bool  locked){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setLocked(turnoutLockout, locked));}
   void setNumberOutputBits(AbstractTurnout* theWrappedObject, int  num);
   void py_q_setNumberOutputBits(AbstractTurnout* theWrappedObject, int  num){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setNumberOutputBits(num));}
   void setReportLocked(AbstractTurnout* theWrappedObject, bool  reportLocked);
   void py_q_setReportLocked(AbstractTurnout* theWrappedObject, bool  reportLocked){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setReportLocked(reportLocked));}
   void setState(AbstractTurnout* theWrappedObject, int  s);
   void py_q_setState(AbstractTurnout* theWrappedObject, int  s){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setState(s));}
   void setStraightSpeed(AbstractTurnout* theWrappedObject, QString  s) const;
   void py_q_setStraightSpeed(AbstractTurnout* theWrappedObject, QString  s) const{  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setStraightSpeed(s));}
   void setTurnoutOperation(AbstractTurnout* theWrappedObject, TurnoutOperation*  toper);
   void py_q_setTurnoutOperation(AbstractTurnout* theWrappedObject, TurnoutOperation*  toper){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_setTurnoutOperation(toper));}
   void turnoutPushbuttonLockout(AbstractTurnout* theWrappedObject);
   void turnoutPushbuttonLockout(AbstractTurnout* theWrappedObject, bool  locked);
   void py_q_turnoutPushbuttonLockout(AbstractTurnout* theWrappedObject, bool  locked){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_turnoutPushbuttonLockout(locked));}
   void vetoableChange(AbstractTurnout* theWrappedObject, PropertyChangeEvent*  evt);
   void py_q_vetoableChange(AbstractTurnout* theWrappedObject, PropertyChangeEvent*  evt){  (((PythonQtPublicPromoter_AbstractTurnout*)theWrappedObject)->py_q_vetoableChange(evt));}
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
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners() const;
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
virtual void setUserName(QString  s);
virtual void stateChanged(int  arg__1);
virtual void timerEvent(QTimerEvent*  event);
virtual QString  toString();
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);
virtual void vetoableChange(PropertyChangeEvent*  arg__1);

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
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners() const;
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
virtual void setUserName(QString  s);
virtual void stateChanged(int  arg__1);
virtual void timerEvent(QTimerEvent*  event);
virtual QString  toString();
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);
virtual void vetoableChange(PropertyChangeEvent*  arg__1);

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
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners() const;
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
virtual void setUserName(QString  s);
virtual void setVelocity(QVector3D  arg__1);
virtual void stateChanged(int  arg__1);
virtual void timerEvent(QTimerEvent*  event);
virtual QString  toString();
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);
virtual void vetoableChange(PropertyChangeEvent*  arg__1);

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
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners() const;
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
virtual void setUserName(QString  s);
virtual void setVelocity(QVector3D  arg__1);
virtual void stateChanged(int  arg__1);
virtual void stop();
virtual void timerEvent(QTimerEvent*  event);
virtual QString  toString();
virtual void togglePause();
virtual void togglePlay();
virtual bool  unqueueBuffers();
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);
virtual void vetoableChange(PropertyChangeEvent*  arg__1);

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
virtual void dispose();
virtual Qt::ItemFlags  flags(const QModelIndex&  index) const;
virtual QString  getBeanType();
virtual NamedBean*  getBySystemName(QString  name) const;
virtual NamedBean*  getByUserName(QString  name);
virtual QString  getCellToolTip(JTable*  table, int  row, int  col) const;
virtual QString  getColumnClass(int  col) const;
virtual QString  getMasterClassName();
virtual int  getPreferredWidth(int  col);
virtual QString  getValue(QString  systemName);
virtual QString  getValue(QString  systemName) const;
virtual QVariant  headerData(int  section, Qt::Orientation  orientation, int  role) const;
virtual void init();
virtual bool  matchPropertyName(PropertyChangeEvent*  e);
virtual void propertyChange(PropertyChangeEvent*  e);
virtual int  rowCount(const QModelIndex&  parent) const;
virtual QObject*  self();
virtual void setColumnIdentities(JTable*  table);
virtual bool  setData(const QModelIndex&  index, const QVariant&  value, int  role);
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
inline QString  promoted_getMasterClassName() { return this->getMasterClassName(); }
inline int  promoted_getPropertyColumnCount() const { return this->getPropertyColumnCount(); }
inline bool  promoted_matchPropertyName(PropertyChangeEvent*  e) { return this->matchPropertyName(e); }
inline void promoted_onColumnSelected(QObject*  obj) { this->onColumnSelected(obj); }
inline void promoted_setColumnIdentities(JTable*  table) { this->setColumnIdentities(table); }
inline void promoted_setColumnToHoldButton(JTable*  table, int  column, QPushButton*  sample = NULL) { this->setColumnToHoldButton(table, column, sample); }
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
inline void py_q_dispose() { BeanTableDataModel::dispose(); }
inline Qt::ItemFlags  py_q_flags(const QModelIndex&  index) const { return BeanTableDataModel::flags(index); }
inline QString  py_q_getBeanType() { return BeanTableDataModel::getBeanType(); }
inline NamedBean*  py_q_getBySystemName(QString  name) const { return BeanTableDataModel::getBySystemName(name); }
inline NamedBean*  py_q_getByUserName(QString  name) { return BeanTableDataModel::getByUserName(name); }
inline QString  py_q_getCellToolTip(JTable*  table, int  row, int  col) const { return BeanTableDataModel::getCellToolTip(table, row, col); }
inline QString  py_q_getColumnClass(int  col) const { return BeanTableDataModel::getColumnClass(col); }
inline QString  py_q_getMasterClassName() { return BeanTableDataModel::getMasterClassName(); }
inline int  py_q_getPreferredWidth(int  col) { return BeanTableDataModel::getPreferredWidth(col); }
inline QString  py_q_getValue(QString  systemName) { return BeanTableDataModel::getValue(systemName); }
inline QString  py_q_getValue(QString  systemName) const { return BeanTableDataModel::getValue(systemName); }
inline QVariant  py_q_headerData(int  section, Qt::Orientation  orientation, int  role) const { return BeanTableDataModel::headerData(section, orientation, role); }
inline void py_q_init() { BeanTableDataModel::init(); }
inline bool  py_q_matchPropertyName(PropertyChangeEvent*  e) { return BeanTableDataModel::matchPropertyName(e); }
inline void py_q_propertyChange(PropertyChangeEvent*  e) { BeanTableDataModel::propertyChange(e); }
inline int  py_q_rowCount(const QModelIndex&  parent) const { return BeanTableDataModel::rowCount(parent); }
inline QObject*  py_q_self() { return BeanTableDataModel::self(); }
inline void py_q_setColumnIdentities(JTable*  table) { BeanTableDataModel::setColumnIdentities(table); }
inline bool  py_q_setData(const QModelIndex&  index, const QVariant&  value, int  role) { return BeanTableDataModel::setData(index, value, role); }
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
   void py_q_dispose(BeanTableDataModel* theWrappedObject){  (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_dispose());}
   void editComment(BeanTableDataModel* theWrappedObject, int  row, int  column);
   Qt::ItemFlags  flags(BeanTableDataModel* theWrappedObject, const QModelIndex&  index) const;
   Qt::ItemFlags  py_q_flags(BeanTableDataModel* theWrappedObject, const QModelIndex&  index) const{  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_flags(index));}
   QString  getBeanType(BeanTableDataModel* theWrappedObject);
   QString  py_q_getBeanType(BeanTableDataModel* theWrappedObject){  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_getBeanType());}
   NamedBean*  getBySystemName(BeanTableDataModel* theWrappedObject, QString  name) const;
   NamedBean*  py_q_getBySystemName(BeanTableDataModel* theWrappedObject, QString  name) const{  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_getBySystemName(name));}
   NamedBean*  getByUserName(BeanTableDataModel* theWrappedObject, QString  name);
   NamedBean*  py_q_getByUserName(BeanTableDataModel* theWrappedObject, QString  name){  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_getByUserName(name));}
   QString  getCellToolTip(BeanTableDataModel* theWrappedObject, JTable*  table, int  row, int  col) const;
   QString  py_q_getCellToolTip(BeanTableDataModel* theWrappedObject, JTable*  table, int  row, int  col) const{  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_getCellToolTip(table, row, col));}
   QString  getColumnClass(BeanTableDataModel* theWrappedObject, int  col) const;
   QString  py_q_getColumnClass(BeanTableDataModel* theWrappedObject, int  col) const{  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_getColumnClass(col));}
   int  getDisplayDeleteMsg(BeanTableDataModel* theWrappedObject);
   QString  getMasterClassName(BeanTableDataModel* theWrappedObject);
   QString  py_q_getMasterClassName(BeanTableDataModel* theWrappedObject){  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_getMasterClassName());}
   int  getPreferredWidth(BeanTableDataModel* theWrappedObject, int  col);
   int  py_q_getPreferredWidth(BeanTableDataModel* theWrappedObject, int  col){  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_getPreferredWidth(col));}
   int  getPropertyColumnCount(BeanTableDataModel* theWrappedObject) const;
   QString  getValue(BeanTableDataModel* theWrappedObject, QString  systemName);
   QString  py_q_getValue(BeanTableDataModel* theWrappedObject, QString  systemName){  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_getValue(systemName));}
   QString  getValue(BeanTableDataModel* theWrappedObject, QString  systemName) const;
   QString  py_q_getValue(BeanTableDataModel* theWrappedObject, QString  systemName) const{  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_getValue(systemName));}
   QVariant  headerData(BeanTableDataModel* theWrappedObject, int  section, Qt::Orientation  orientation, int  role) const;
   QVariant  py_q_headerData(BeanTableDataModel* theWrappedObject, int  section, Qt::Orientation  orientation, int  role) const{  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_headerData(section, orientation, role));}
   void py_q_init(BeanTableDataModel* theWrappedObject){  (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_init());}
   bool  matchPropertyName(BeanTableDataModel* theWrappedObject, PropertyChangeEvent*  e);
   bool  py_q_matchPropertyName(BeanTableDataModel* theWrappedObject, PropertyChangeEvent*  e){  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_matchPropertyName(e));}
   void moveBean(BeanTableDataModel* theWrappedObject, int  arg__1, int  col);
   void persistTable(BeanTableDataModel* theWrappedObject, JTable*  table);
   void py_q_propertyChange(BeanTableDataModel* theWrappedObject, PropertyChangeEvent*  e){  (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_propertyChange(e));}
   void removeName(BeanTableDataModel* theWrappedObject, int  arg__1);
   void renameBean(BeanTableDataModel* theWrappedObject, int  arg__1);
   int  rowCount(BeanTableDataModel* theWrappedObject, const QModelIndex&  parent) const;
   int  py_q_rowCount(BeanTableDataModel* theWrappedObject, const QModelIndex&  parent) const{  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_rowCount(parent));}
   QObject*  py_q_self(BeanTableDataModel* theWrappedObject){  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_self());}
   void setColumnIdentities(BeanTableDataModel* theWrappedObject, JTable*  table);
   void py_q_setColumnIdentities(BeanTableDataModel* theWrappedObject, JTable*  table){  (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_setColumnIdentities(table));}
   void setColumnToHoldButton(BeanTableDataModel* theWrappedObject, JTable*  table, int  column, QPushButton*  sample = NULL);
   bool  setData(BeanTableDataModel* theWrappedObject, const QModelIndex&  index, const QVariant&  value, int  role);
   bool  py_q_setData(BeanTableDataModel* theWrappedObject, const QModelIndex&  index, const QVariant&  value, int  role){  return (((PythonQtPublicPromoter_BeanTableDataModel*)theWrappedObject)->py_q_setData(index, value, role));}
   void setDisplayDeleteMsg(BeanTableDataModel* theWrappedObject, int  boo);
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
virtual QColor  getBackground();
virtual QString  getClassName();
virtual QFont  getFont();
virtual QColor  getForeground();
virtual QVariant  getProperty(QString  key);
virtual QString  getTitle();
virtual void handleModified();
virtual bool  hasHeightForWidth() const;
virtual int  heightForWidth(int  arg__1) const;
virtual void hideEvent(QHideEvent*  arg__1);
virtual void initComponents();
virtual void initPainter(QPainter*  painter) const;
virtual void inputMethodEvent(QInputMethodEvent*  arg__1);
virtual QVariant  inputMethodQuery(Qt::InputMethodQuery  arg__1) const;
virtual bool  isOpaque();
virtual QWidget*  jself();
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
virtual void setBackground(QColor  arg__1);
virtual void setEnabled(bool  b);
virtual void setFont(QFont  arg__1);
virtual void setOpaque(bool  arg__1);
virtual void setTitle(QString  _title);
virtual void setVisible(bool  visible);
virtual QPainter*  sharedPainter() const;
virtual void showEvent(QShowEvent*  arg__1);
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
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners() const;
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
virtual void setUserName(QString  s);
virtual void setValue(QVariant  value);
virtual void timerEvent(QTimerEvent*  event);
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);
virtual void vetoableChange(PropertyChangeEvent*  arg__1);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_Block : public Block
{ public:
inline bool  py_q_equals(QObject*  obj) { return Block::equals(obj); }
inline QString  py_q_getBeanType() { return Block::getBeanType(); }
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
   QString  py_q_getBeanType(Block* theWrappedObject){  return (((PythonQtPublicPromoter_Block*)theWrappedObject)->py_q_getBeanType());}
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
   void setBlockSpeed(Block* theWrappedObject, QString  s);
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





class PythonQtShell_ControlPanelEditor : public ControlPanelEditor
{
public:
    PythonQtShell_ControlPanelEditor(QString  name, QWidget*  parent = 0):ControlPanelEditor(name, parent),_wrapper(NULL) {}
    PythonQtShell_ControlPanelEditor(QWidget*  parent = 0):ControlPanelEditor(parent),_wrapper(NULL) {}
    PythonQtShell_ControlPanelEditor(const ControlPanelEditor&  other):ControlPanelEditor(other),_wrapper(NULL) {}

   ~PythonQtShell_ControlPanelEditor();

virtual void mouseClicked(QGraphicsSceneMouseEvent*  event);
virtual void mouseDragged(QGraphicsSceneMouseEvent*  event);
virtual void mouseMoved(QGraphicsSceneMouseEvent*  event);
virtual void mousePressed(QGraphicsSceneMouseEvent*  event);
virtual void mouseReleased(QGraphicsSceneMouseEvent*  event);
virtual void setAllEditable(bool  edit);

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
inline void py_q_mouseClicked(QGraphicsSceneMouseEvent*  event) { ControlPanelEditor::mouseClicked(event); }
inline void py_q_mouseDragged(QGraphicsSceneMouseEvent*  event) { ControlPanelEditor::mouseDragged(event); }
inline void py_q_mouseMoved(QGraphicsSceneMouseEvent*  event) { ControlPanelEditor::mouseMoved(event); }
inline void py_q_mousePressed(QGraphicsSceneMouseEvent*  event) { ControlPanelEditor::mousePressed(event); }
inline void py_q_mouseReleased(QGraphicsSceneMouseEvent*  event) { ControlPanelEditor::mouseReleased(event); }
inline void py_q_setAllEditable(bool  edit) { ControlPanelEditor::setAllEditable(edit); }
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
   QString  getClassName(ControlPanelEditor* theWrappedObject);
   QList<Positionable* >*  getClipGroup(ControlPanelEditor* theWrappedObject);
   Positionable*  getCopySelection(ControlPanelEditor* theWrappedObject, QGraphicsSceneMouseEvent*  event);
   Positionable*  getCurrentSelection(ControlPanelEditor* theWrappedObject, QGraphicsSceneMouseEvent*  event);
   QList<Positionable* >*  getSelectionGroup(ControlPanelEditor* theWrappedObject);
   bool  getShapeSelect(ControlPanelEditor* theWrappedObject);
   void highlight(ControlPanelEditor* theWrappedObject, Positionable*  pos);
   void init(ControlPanelEditor* theWrappedObject, QString  name);
   void initView(ControlPanelEditor* theWrappedObject);
   void keyPressEvent(ControlPanelEditor* theWrappedObject, QKeyEvent*  e);
   void keyReleaseEvent(ControlPanelEditor* theWrappedObject, QKeyEvent*  e);
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
   void mouseEntered(ControlPanelEditor* theWrappedObject, QGraphicsSceneMouseEvent*  event);
   void mouseExited(ControlPanelEditor* theWrappedObject, QGraphicsSceneMouseEvent*  event);
   void py_q_mouseMoved(ControlPanelEditor* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_ControlPanelEditor*)theWrappedObject)->py_q_mouseMoved(event));}
   void py_q_mousePressed(ControlPanelEditor* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_ControlPanelEditor*)theWrappedObject)->py_q_mousePressed(event));}
   void py_q_mouseReleased(ControlPanelEditor* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_ControlPanelEditor*)theWrappedObject)->py_q_mouseReleased(event));}
   void paintTargetPanel(ControlPanelEditor* theWrappedObject, QGraphicsScene*  g);
   void resetEditor(ControlPanelEditor* theWrappedObject);
   void py_q_setAllEditable(ControlPanelEditor* theWrappedObject, bool  edit){  (((PythonQtPublicPromoter_ControlPanelEditor*)theWrappedObject)->py_q_setAllEditable(edit));}
   void setColorMenu(ControlPanelEditor* theWrappedObject, QMenu*  popup, QWidget*  pos, int  type);
   void setCopyMenu(ControlPanelEditor* theWrappedObject, Positionable*  p, QMenu*  popup);
   void setNextLocation(ControlPanelEditor* theWrappedObject, Positionable*  obj);
   void setSecondSelectionGroup(ControlPanelEditor* theWrappedObject, QList<Positionable* >*  list);
   void setSelectionGroup(ControlPanelEditor* theWrappedObject, QList<Positionable* >*  group);
   void setSelectionsRotation(ControlPanelEditor* theWrappedObject, int  k, Positionable*  p);
   void setSelectionsScale(ControlPanelEditor* theWrappedObject, double  s, Positionable*  p);
   void setShapeSelect(ControlPanelEditor* theWrappedObject, bool  set);
   void setTitle(ControlPanelEditor* theWrappedObject);
   void showPopUp(ControlPanelEditor* theWrappedObject, Positionable*  p, QGraphicsSceneMouseEvent*  event);
   void targetWindowClosingEvent(ControlPanelEditor* theWrappedObject, QCloseEvent*  e);
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
    PythonQtShell_DccThrottle():DccThrottle(),_wrapper(NULL) {}

   ~PythonQtShell_DccThrottle();

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
virtual bool  getFunction(int  arg__1);
virtual bool  getFunctionMomentary(int  arg__1);
virtual QVector<bool >  getFunctions();
virtual QVector<bool >  getFunctionsMomentary();
virtual bool  getIsForward();
virtual QVector<PropertyChangeListener* >*  getListeners();
virtual LocoAddress*  getLocoAddress();
virtual BasicRosterEntry*  getRosterEntry();
virtual float  getSpeedIncrement();
virtual float  getSpeedSetting();
virtual QObject*  self();
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
virtual void setFunction(int  arg__1, bool  arg__2);
virtual void setFunctionMomentary(int  arg__1, bool  arg__2);
virtual void setIsForward(bool  arg__1);
virtual void setRosterEntry(BasicRosterEntry*  arg__1);
virtual void setSpeedSetting(float  arg__1);
virtual void setSpeedSetting(float  arg__1, bool  arg__2, bool  arg__3);
virtual void setSpeedSettingAgain(float  arg__1);

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
DccThrottle* new_DccThrottle();
void delete_DccThrottle(DccThrottle* obj) { delete obj; } 
   float  getSpeedIncrement(DccThrottle* theWrappedObject);
   float  py_q_getSpeedIncrement(DccThrottle* theWrappedObject){  return (((PythonQtPublicPromoter_DccThrottle*)theWrappedObject)->py_q_getSpeedIncrement());}
};





class PythonQtShell_DefaultProgrammerManager : public DefaultProgrammerManager
{
public:
    PythonQtShell_DefaultProgrammerManager(QObject*  parent = 0):DefaultProgrammerManager(parent),_wrapper(NULL) {}
    PythonQtShell_DefaultProgrammerManager(const DefaultProgrammerManager&  arg__1):DefaultProgrammerManager(arg__1),_wrapper(NULL) {}

   ~PythonQtShell_DefaultProgrammerManager();

virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual QList<QString >  getDefaultModes();
virtual QString  getUserName();
virtual bool  isAddressedModePossible();
virtual bool  isAddressedModePossible(DccLocoAddress*  l);
virtual bool  isGlobalProgrammerAvailable();
virtual QObject*  self();
virtual void timerEvent(QTimerEvent*  event);
virtual QString  toString();

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_DefaultProgrammerManager : public DefaultProgrammerManager
{ public:
inline QList<QString >  py_q_getDefaultModes() { return DefaultProgrammerManager::getDefaultModes(); }
inline QString  py_q_getUserName() { return DefaultProgrammerManager::getUserName(); }
inline bool  py_q_isAddressedModePossible() { return DefaultProgrammerManager::isAddressedModePossible(); }
inline bool  py_q_isAddressedModePossible(DccLocoAddress*  l) { return DefaultProgrammerManager::isAddressedModePossible(l); }
inline bool  py_q_isGlobalProgrammerAvailable() { return DefaultProgrammerManager::isGlobalProgrammerAvailable(); }
inline QObject*  py_q_self() { return DefaultProgrammerManager::self(); }
inline QString  py_q_toString() { return DefaultProgrammerManager::toString(); }
};

class PythonQtWrapper_DefaultProgrammerManager : public QObject
{ Q_OBJECT
public:
public slots:
DefaultProgrammerManager* new_DefaultProgrammerManager(QObject*  parent = 0);
DefaultProgrammerManager* new_DefaultProgrammerManager(const DefaultProgrammerManager&  arg__1);
void delete_DefaultProgrammerManager(DefaultProgrammerManager* obj) { delete obj; } 
   QList<QString >  getDefaultModes(DefaultProgrammerManager* theWrappedObject);
   QList<QString >  py_q_getDefaultModes(DefaultProgrammerManager* theWrappedObject){  return (((PythonQtPublicPromoter_DefaultProgrammerManager*)theWrappedObject)->py_q_getDefaultModes());}
   QString  getUserName(DefaultProgrammerManager* theWrappedObject);
   QString  py_q_getUserName(DefaultProgrammerManager* theWrappedObject){  return (((PythonQtPublicPromoter_DefaultProgrammerManager*)theWrappedObject)->py_q_getUserName());}
   bool  isAddressedModePossible(DefaultProgrammerManager* theWrappedObject);
   bool  py_q_isAddressedModePossible(DefaultProgrammerManager* theWrappedObject){  return (((PythonQtPublicPromoter_DefaultProgrammerManager*)theWrappedObject)->py_q_isAddressedModePossible());}
   bool  isAddressedModePossible(DefaultProgrammerManager* theWrappedObject, DccLocoAddress*  l);
   bool  py_q_isAddressedModePossible(DefaultProgrammerManager* theWrappedObject, DccLocoAddress*  l){  return (((PythonQtPublicPromoter_DefaultProgrammerManager*)theWrappedObject)->py_q_isAddressedModePossible(l));}
   bool  isGlobalProgrammerAvailable(DefaultProgrammerManager* theWrappedObject);
   bool  py_q_isGlobalProgrammerAvailable(DefaultProgrammerManager* theWrappedObject){  return (((PythonQtPublicPromoter_DefaultProgrammerManager*)theWrappedObject)->py_q_isGlobalProgrammerAvailable());}
   QObject*  self(DefaultProgrammerManager* theWrappedObject);
   QObject*  py_q_self(DefaultProgrammerManager* theWrappedObject){  return (((PythonQtPublicPromoter_DefaultProgrammerManager*)theWrappedObject)->py_q_self());}
   QString  toString(DefaultProgrammerManager* theWrappedObject);
   QString  py_q_toString(DefaultProgrammerManager* theWrappedObject){  return (((PythonQtPublicPromoter_DefaultProgrammerManager*)theWrappedObject)->py_q_toString());}
    QString py_toString(DefaultProgrammerManager*);
};





class PythonQtShell_EditScene : public EditScene
{
public:
    PythonQtShell_EditScene(QObject*  parent = 0):EditScene(parent),_wrapper(NULL) {}
    PythonQtShell_EditScene(QRectF  arg__1, QObject*  parent = 0):EditScene(arg__1, parent),_wrapper(NULL) {}
    PythonQtShell_EditScene(qreal  x, qreal  y, qreal  width, qreal  height, QObject*  parent = 0):EditScene(x, y, width, height, parent),_wrapper(NULL) {}

   ~PythonQtShell_EditScene();

virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual void drawBackground(QPainter*  painter, const QRectF&  rect);
virtual void drawForeground(QPainter*  painter, const QRectF&  rect);
virtual void drawItems(QPainter*  painter, int  numItems, QGraphicsItem**  items, const QStyleOptionGraphicsItem*  options, QWidget*  widget = nullptr);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual void focusInEvent(QFocusEvent*  event);
virtual void focusOutEvent(QFocusEvent*  event);
virtual void helpEvent(QGraphicsSceneHelpEvent*  event);
virtual void inputMethodEvent(QInputMethodEvent*  event);
virtual QVariant  inputMethodQuery(Qt::InputMethodQuery  query) const;
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtWrapper_EditScene : public QObject
{ Q_OBJECT
public:
public slots:
EditScene* new_EditScene(QObject*  parent = 0);
EditScene* new_EditScene(QRectF  arg__1, QObject*  parent = 0);
EditScene* new_EditScene(qreal  x, qreal  y, qreal  width, qreal  height, QObject*  parent = 0);
void delete_EditScene(EditScene* obj) { delete obj; } 
   QColor  getBackground(EditScene* theWrappedObject);
   QWidget*  getTopLevelAncestor(EditScene* theWrappedObject);
   void repaint(EditScene* theWrappedObject);
};





class PythonQtShell_EventObject : public EventObject
{
public:
    PythonQtShell_EventObject(QObject*  source, QObject*  parent = 0):EventObject(source, parent),_wrapper(NULL) {}

   ~PythonQtShell_EventObject();

virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
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
    PythonQtShell_FileUtil(QObject*  parent = 0):FileUtil(parent),_wrapper(NULL) {}

   ~PythonQtShell_FileUtil();

virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
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
   QTextStream*  static_FileUtil_findInputStream(QString  path);
   QTextStream*  static_FileUtil_findInputStream(QString  path, FileUtil::Location  locations);
   QTextStream*  static_FileUtil_findInputStream(QString  path, QStringList  searchPaths);
   QList<QString >*  static_FileUtil_findProgramPath();
   QUrl  static_FileUtil_findURL(QString  path);
   QUrl  static_FileUtil_findURL(QString  path, FileUtil::Location  locations);
   QUrl  static_FileUtil_findURL(QString  path, FileUtil::Location  locations, QStringList  searchPaths);
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
   QString  static_FileUtil_locateFile(QDir  start, QString  fileName);
   void static_FileUtil_logFilePaths();
   QString  static_FileUtil_pathFromPortablePath(QString  path);
   QString  static_FileUtil_readURL(QUrl  url);
   QString  static_FileUtil_sanitizeFilename(QString  name);
   void static_FileUtil_setProfilePath(QString  path);
   void static_FileUtil_setProgramPath(QString  path);
};





class PythonQtShell_FlowLayout : public FlowLayout
{
public:
    PythonQtShell_FlowLayout(QWidget*  parent, int  margin = -1, int  hSpacing = -1, int  vSpacing = -1):FlowLayout(parent, margin, hSpacing, vSpacing),_wrapper(NULL) {}
    PythonQtShell_FlowLayout(int  margin = -1, int  hSpacing = -1, int  vSpacing = -1):FlowLayout(margin, hSpacing, vSpacing),_wrapper(NULL) {}

   ~PythonQtShell_FlowLayout();

virtual void addItem(QLayoutItem*  item);
virtual void childEvent(QChildEvent*  e);
virtual QSizePolicy::ControlTypes  controlTypes() const;
virtual int  count() const;
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
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
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_FlowLayout : public FlowLayout
{ public:
inline void py_q_addItem(QLayoutItem*  item) { FlowLayout::addItem(item); }
inline int  py_q_count() const { return FlowLayout::count(); }
inline Qt::Orientations  py_q_expandingDirections() const { return FlowLayout::expandingDirections(); }
inline QLayoutItem*  py_q_itemAt(int  index) const { return FlowLayout::itemAt(index); }
inline QSize  py_q_minimumSize() const { return FlowLayout::minimumSize(); }
inline void py_q_setGeometry(const QRect&  rect) { FlowLayout::setGeometry(rect); }
inline QLayoutItem*  py_q_takeAt(int  index) { return FlowLayout::takeAt(index); }
};

class PythonQtWrapper_FlowLayout : public QObject
{ Q_OBJECT
public:
public slots:
FlowLayout* new_FlowLayout(QWidget*  parent, int  margin = -1, int  hSpacing = -1, int  vSpacing = -1);
FlowLayout* new_FlowLayout(int  margin = -1, int  hSpacing = -1, int  vSpacing = -1);
void delete_FlowLayout(FlowLayout* obj) { delete obj; } 
   void py_q_addItem(FlowLayout* theWrappedObject, QLayoutItem*  item){  (((PythonQtPublicPromoter_FlowLayout*)theWrappedObject)->py_q_addItem(item));}
   int  py_q_count(FlowLayout* theWrappedObject) const{  return (((PythonQtPublicPromoter_FlowLayout*)theWrappedObject)->py_q_count());}
   Qt::Orientations  py_q_expandingDirections(FlowLayout* theWrappedObject) const{  return (((PythonQtPublicPromoter_FlowLayout*)theWrappedObject)->py_q_expandingDirections());}
   bool  hasHeightForWidth(FlowLayout* theWrappedObject) const;
   int  heightForWidth(FlowLayout* theWrappedObject, int  arg__1) const;
   int  horizontalSpacing(FlowLayout* theWrappedObject) const;
   QLayoutItem*  py_q_itemAt(FlowLayout* theWrappedObject, int  index) const{  return (((PythonQtPublicPromoter_FlowLayout*)theWrappedObject)->py_q_itemAt(index));}
   QSize  py_q_minimumSize(FlowLayout* theWrappedObject) const{  return (((PythonQtPublicPromoter_FlowLayout*)theWrappedObject)->py_q_minimumSize());}
   void py_q_setGeometry(FlowLayout* theWrappedObject, const QRect&  rect){  (((PythonQtPublicPromoter_FlowLayout*)theWrappedObject)->py_q_setGeometry(rect));}
   QSize  sizeHint(FlowLayout* theWrappedObject) const;
   QLayoutItem*  py_q_takeAt(FlowLayout* theWrappedObject, int  index){  return (((PythonQtPublicPromoter_FlowLayout*)theWrappedObject)->py_q_takeAt(index));}
   int  verticalSpacing(FlowLayout* theWrappedObject) const;
    bool __nonzero__(FlowLayout* obj) { return !obj->isEmpty(); }
};





class PythonQtShell_JFrame : public JFrame
{
public:
    PythonQtShell_JFrame(QString  _title, QWidget*  parent = nullptr):JFrame(_title, parent),_wrapper(NULL) {}
    PythonQtShell_JFrame(QWidget*  parent = nullptr):JFrame(parent),_wrapper(NULL) {}
    PythonQtShell_JFrame(const JFrame&  arg__1):JFrame(arg__1),_wrapper(NULL) {}

   ~PythonQtShell_JFrame();

virtual void actionEvent(QActionEvent*  event);
virtual void changeEvent(QEvent*  arg__1);
virtual void childEvent(QChildEvent*  event);
virtual bool  closedNormally();
virtual void componentMoved(QMoveEvent*  arg__1);
virtual void componentResized(QResizeEvent*  arg__1);
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
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual void focusInEvent(QFocusEvent*  event);
virtual bool  focusNextPrevChild(bool  next);
virtual void focusOutEvent(QFocusEvent*  event);
virtual QColor  getBackground();
virtual QFont  getFont();
virtual QColor  getForeground();
virtual QString  getTitle();
virtual bool  hasHeightForWidth() const;
virtual int  heightForWidth(int  arg__1) const;
virtual void hideEvent(QHideEvent*  arg__1);
virtual void initPainter(QPainter*  painter) const;
virtual void inputMethodEvent(QInputMethodEvent*  arg__1);
virtual QVariant  inputMethodQuery(Qt::InputMethodQuery  arg__1) const;
virtual bool  isOpaque();
virtual QWidget*  jself();
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
virtual void moveEvent(QMoveEvent*  event);
virtual bool  nativeEvent(const QByteArray&  eventType, void*  message, long*  result);
virtual void pack();
virtual QPaintEngine*  paintEngine() const;
virtual void paintEvent(QPaintEvent*  event);
virtual QPaintDevice*  redirected(QPoint*  offset) const;
virtual void resizeEvent(QResizeEvent*  event);
virtual void setBackground(QColor  arg__1);
virtual void setEnabled(bool  b);
virtual void setFont(QFont  arg__1);
virtual void setOpaque(bool  arg__1);
virtual void setTitle(QString  _title);
virtual void setVisible(bool  visible);
virtual QPainter*  sharedPainter() const;
virtual void showEvent(QShowEvent*  arg__1);
virtual QSize  sizeHint() const;
virtual void tabletEvent(QTabletEvent*  event);
virtual void timerEvent(QTimerEvent*  event);
virtual void wheelEvent(QWheelEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_JFrame : public JFrame
{ public:
inline void promoted_frameInit() { this->frameInit(); }
inline void promoted_hideEvent(QHideEvent*  arg__1) { this->hideEvent(arg__1); }
inline QString  promoted_paramString() { return this->paramString(); }
inline void promoted_showEvent(QShowEvent*  arg__1) { this->showEvent(arg__1); }
inline bool  py_q_closedNormally() { return JFrame::closedNormally(); }
inline void py_q_componentMoved(QMoveEvent*  arg__1) { JFrame::componentMoved(arg__1); }
inline void py_q_componentResized(QResizeEvent*  arg__1) { JFrame::componentResized(arg__1); }
inline void py_q_dispose() { JFrame::dispose(); }
inline QColor  py_q_getBackground() { return JFrame::getBackground(); }
inline QFont  py_q_getFont() { return JFrame::getFont(); }
inline QColor  py_q_getForeground() { return JFrame::getForeground(); }
inline QString  py_q_getTitle() { return JFrame::getTitle(); }
inline void py_q_hideEvent(QHideEvent*  arg__1) { JFrame::hideEvent(arg__1); }
inline bool  py_q_isOpaque() { return JFrame::isOpaque(); }
inline QWidget*  py_q_jself() { return JFrame::jself(); }
inline void py_q_languageChange() { JFrame::languageChange(); }
inline void py_q_pack() { JFrame::pack(); }
inline void py_q_setBackground(QColor  arg__1) { JFrame::setBackground(arg__1); }
inline void py_q_setEnabled(bool  b) { JFrame::setEnabled(b); }
inline void py_q_setFont(QFont  arg__1) { JFrame::setFont(arg__1); }
inline void py_q_setOpaque(bool  arg__1) { JFrame::setOpaque(arg__1); }
inline void py_q_setTitle(QString  _title) { JFrame::setTitle(_title); }
inline void py_q_setVisible(bool  visible) { JFrame::setVisible(visible); }
inline void py_q_showEvent(QShowEvent*  arg__1) { JFrame::showEvent(arg__1); }
};

class PythonQtWrapper_JFrame : public QObject
{ Q_OBJECT
public:
public slots:
JFrame* new_JFrame(QString  _title, QWidget*  parent = nullptr);
JFrame* new_JFrame(QWidget*  parent = nullptr);
JFrame* new_JFrame(const JFrame&  arg__1);
void delete_JFrame(JFrame* obj) { delete obj; } 
   void addPropertyChangeListener(JFrame* theWrappedObject, PropertyChangeListener*  arg__1);
   void addWindowListener(JFrame* theWrappedObject, WindowListener*  l);
   bool  closedNormally(JFrame* theWrappedObject);
   bool  py_q_closedNormally(JFrame* theWrappedObject){  return (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_closedNormally());}
   void componentMoved(JFrame* theWrappedObject, QMoveEvent*  arg__1);
   void py_q_componentMoved(JFrame* theWrappedObject, QMoveEvent*  arg__1){  (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_componentMoved(arg__1));}
   void componentResized(JFrame* theWrappedObject, QResizeEvent*  arg__1);
   void py_q_componentResized(JFrame* theWrappedObject, QResizeEvent*  arg__1){  (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_componentResized(arg__1));}
   void dispose(JFrame* theWrappedObject);
   void py_q_dispose(JFrame* theWrappedObject){  (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_dispose());}
   void firePropertyChange(JFrame* theWrappedObject, QString  arg__1, QVariant  arg__2, QVariant  arg__3);
   void firePropertyChange(JFrame* theWrappedObject, QString  pName, QObject*  _old, QObject*  _new);
   void frameInit(JFrame* theWrappedObject);
   QColor  getBackground(JFrame* theWrappedObject);
   QColor  py_q_getBackground(JFrame* theWrappedObject){  return (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_getBackground());}
   int  getExtendedState(JFrame* theWrappedObject);
   QFont  getFont(JFrame* theWrappedObject);
   QFont  py_q_getFont(JFrame* theWrappedObject){  return (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_getFont());}
   QColor  getForeground(JFrame* theWrappedObject);
   QColor  py_q_getForeground(JFrame* theWrappedObject){  return (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_getForeground());}
   QPoint  getLocation(JFrame* theWrappedObject);
   QPoint  getLocationOnScreen(JFrame* theWrappedObject);
   QSize  getMaximumSize(JFrame* theWrappedObject);
   QSize  getPreferredSize(JFrame* theWrappedObject);
   int  getState(JFrame* theWrappedObject);
   QString  getTitle(JFrame* theWrappedObject);
   QString  py_q_getTitle(JFrame* theWrappedObject){  return (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_getTitle());}
   QWidget*  getTopLevelAncestor(JFrame* theWrappedObject);
   QVector<WindowListener* >  getWindowListeners(JFrame* theWrappedObject);
   void py_q_hideEvent(JFrame* theWrappedObject, QHideEvent*  arg__1){  (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_hideEvent(arg__1));}
   bool  isOpaque(JFrame* theWrappedObject);
   bool  py_q_isOpaque(JFrame* theWrappedObject){  return (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_isOpaque());}
   bool  isResizable(JFrame* theWrappedObject);
   QWidget*  jself(JFrame* theWrappedObject);
   QWidget*  py_q_jself(JFrame* theWrappedObject){  return (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_jself());}
   void languageChange(JFrame* theWrappedObject);
   void py_q_languageChange(JFrame* theWrappedObject){  (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_languageChange());}
   void pack(JFrame* theWrappedObject);
   void py_q_pack(JFrame* theWrappedObject){  (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_pack());}
   QString  paramString(JFrame* theWrappedObject);
   void reSizeToFitOnScreen(JFrame* theWrappedObject);
   void removeAll(JFrame* theWrappedObject);
   void removePropertyChangeListener(JFrame* theWrappedObject, PropertyChangeListener*  arg__1);
   void removeWindowListener(JFrame* theWrappedObject, WindowListener*  l);
   void setAlwaysOnTop(JFrame* theWrappedObject, bool  checked);
   void setBackground(JFrame* theWrappedObject, QColor  arg__1);
   void py_q_setBackground(JFrame* theWrappedObject, QColor  arg__1){  (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_setBackground(arg__1));}
   void setBounds(JFrame* theWrappedObject, QRect  r);
   void setDefaultCloseOperation(JFrame* theWrappedObject, int  operation);
   void py_q_setEnabled(JFrame* theWrappedObject, bool  b){  (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_setEnabled(b));}
   void setExtendedState(JFrame* theWrappedObject, int  s);
   void py_q_setFont(JFrame* theWrappedObject, QFont  arg__1){  (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_setFont(arg__1));}
   void setLocation(JFrame* theWrappedObject, QPoint  p);
   void setLocation(JFrame* theWrappedObject, int  x, int  y);
   void setMenuBar(JFrame* theWrappedObject, QMenuBar*  menubar);
   void setOpaque(JFrame* theWrappedObject, bool  arg__1);
   void py_q_setOpaque(JFrame* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_setOpaque(arg__1));}
   void setResizable(JFrame* theWrappedObject, bool  resizable);
   void setState(JFrame* theWrappedObject, int  state);
   void setTitle(JFrame* theWrappedObject, QString  _title);
   void py_q_setTitle(JFrame* theWrappedObject, QString  _title){  (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_setTitle(_title));}
   void py_q_setVisible(JFrame* theWrappedObject, bool  visible){  (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_setVisible(visible));}
   void py_q_showEvent(JFrame* theWrappedObject, QShowEvent*  arg__1){  (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_showEvent(arg__1));}
   QString  title(JFrame* theWrappedObject);
   void toFront(JFrame* theWrappedObject);
void py_set__closed(JFrame* theWrappedObject, bool  _closed){ theWrappedObject->_closed = _closed; }
bool  py_get__closed(JFrame* theWrappedObject){ return theWrappedObject->_closed; }
};





class PythonQtPublicPromoter_JFrameItem : public JFrameItem
{ public:
inline QString  py_q_getClassName() { return JFrameItem::getClassName(); }
};

class PythonQtWrapper_JFrameItem : public QObject
{ Q_OBJECT
public:
public slots:
void delete_JFrameItem(JFrameItem* obj) { delete obj; } 
   QString  py_q_getClassName(JFrameItem* theWrappedObject){  return (((PythonQtPublicPromoter_JFrameItem*)theWrappedObject)->py_q_getClassName());}
   QString  toString(JFrameItem* theWrappedObject);
    QString py_toString(JFrameItem*);
};





class PythonQtShell_JLabel : public JLabel
{
public:
    PythonQtShell_JLabel(QString  text, QWidget*  parent = 0):JLabel(text, parent),_wrapper(NULL) {}
    PythonQtShell_JLabel(QString  text, int  horizontalAlignment, QWidget*  parent = 0):JLabel(text, horizontalAlignment, parent),_wrapper(NULL) {}
    PythonQtShell_JLabel(QWidget*  parent = 0):JLabel(parent),_wrapper(NULL) {}

   ~PythonQtShell_JLabel();

virtual void actionEvent(QActionEvent*  event);
virtual void changeEvent(QEvent*  arg__1);
virtual void childEvent(QChildEvent*  event);
virtual void closeEvent(QCloseEvent*  event);
virtual void contextMenuEvent(QContextMenuEvent*  ev);
virtual void customEvent(QEvent*  event);
virtual int  devType() const;
virtual void dragEnterEvent(QDragEnterEvent*  event);
virtual void dragLeaveEvent(QDragLeaveEvent*  event);
virtual void dragMoveEvent(QDragMoveEvent*  event);
virtual void dropEvent(QDropEvent*  event);
virtual void enterEvent(QEvent*  event);
virtual bool  event(QEvent*  e);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual void focusInEvent(QFocusEvent*  ev);
virtual bool  focusNextPrevChild(bool  next);
virtual void focusOutEvent(QFocusEvent*  ev);
virtual QColor  getBackground();
virtual QFont  getFont();
virtual QColor  getForeground();
virtual QPointF  getLocation();
virtual bool  hasHeightForWidth() const;
virtual int  heightForWidth(int  arg__1) const;
virtual void hideEvent(QHideEvent*  event);
virtual void initPainter(QPainter*  painter) const;
virtual void inputMethodEvent(QInputMethodEvent*  arg__1);
virtual QVariant  inputMethodQuery(Qt::InputMethodQuery  arg__1) const;
virtual bool  isOpaque();
virtual QWidget*  jself();
virtual void keyPressEvent(QKeyEvent*  ev);
virtual void keyReleaseEvent(QKeyEvent*  event);
virtual void leaveEvent(QEvent*  event);
virtual int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
virtual QSize  minimumSizeHint() const;
virtual void mouseDoubleClickEvent(QMouseEvent*  event);
virtual void mouseMoveEvent(QMouseEvent*  ev);
virtual void mousePressEvent(QMouseEvent*  ev);
virtual void mouseReleaseEvent(QMouseEvent*  ev);
virtual void moveEvent(QMoveEvent*  event);
virtual bool  nativeEvent(const QByteArray&  eventType, void*  message, long*  result);
virtual QPaintEngine*  paintEngine() const;
virtual void paintEvent(QPaintEvent*  arg__1);
virtual QPaintDevice*  redirected(QPoint*  offset) const;
virtual void resizeEvent(QResizeEvent*  event);
virtual void setBackground(QColor  arg__1);
virtual void setEnabled(bool  b);
virtual void setFont(QFont  arg__1);
virtual void setName(QString  name);
virtual void setOpaque(bool  arg__1);
virtual void setVisible(bool  visible);
virtual QPainter*  sharedPainter() const;
virtual void showEvent(QShowEvent*  event);
virtual QSize  sizeHint() const;
virtual void tabletEvent(QTabletEvent*  event);
virtual void timerEvent(QTimerEvent*  event);
virtual void wheelEvent(QWheelEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_JLabel : public JLabel
{ public:
inline int  promoted_checkHorizontalKey(int  key, QString  message) { return this->checkHorizontalKey(key, message); }
inline int  promoted_checkVerticalKey(int  key, QString  message) { return this->checkVerticalKey(key, message); }
inline QColor  py_q_getBackground() { return JLabel::getBackground(); }
inline QFont  py_q_getFont() { return JLabel::getFont(); }
inline QColor  py_q_getForeground() { return JLabel::getForeground(); }
inline QPointF  py_q_getLocation() { return JLabel::getLocation(); }
inline bool  py_q_isOpaque() { return JLabel::isOpaque(); }
inline QWidget*  py_q_jself() { return JLabel::jself(); }
inline void py_q_setBackground(QColor  arg__1) { JLabel::setBackground(arg__1); }
inline void py_q_setEnabled(bool  b) { JLabel::setEnabled(b); }
inline void py_q_setFont(QFont  arg__1) { JLabel::setFont(arg__1); }
inline void py_q_setName(QString  name) { JLabel::setName(name); }
inline void py_q_setOpaque(bool  arg__1) { JLabel::setOpaque(arg__1); }
};

class PythonQtWrapper_JLabel : public QObject
{ Q_OBJECT
public:
public slots:
JLabel* new_JLabel(QString  text, QWidget*  parent = 0);
JLabel* new_JLabel(QString  text, int  horizontalAlignment, QWidget*  parent = 0);
JLabel* new_JLabel(QWidget*  parent = 0);
void delete_JLabel(JLabel* obj) { delete obj; } 
   int  checkHorizontalKey(JLabel* theWrappedObject, int  key, QString  message);
   int  checkVerticalKey(JLabel* theWrappedObject, int  key, QString  message);
   void firePropertyChange(JLabel* theWrappedObject, QString  propertyName, QVariant  oldValue, QVariant  newValue);
   QColor  getBackground(JLabel* theWrappedObject);
   QColor  py_q_getBackground(JLabel* theWrappedObject){  return (((PythonQtPublicPromoter_JLabel*)theWrappedObject)->py_q_getBackground());}
   int  getBaseline(JLabel* theWrappedObject, int  w, int  h);
   int  getDisplayedMnemonic(JLabel* theWrappedObject);
   QFont  getFont(JLabel* theWrappedObject);
   QFont  py_q_getFont(JLabel* theWrappedObject){  return (((PythonQtPublicPromoter_JLabel*)theWrappedObject)->py_q_getFont());}
   QColor  getForeground(JLabel* theWrappedObject);
   QColor  py_q_getForeground(JLabel* theWrappedObject){  return (((PythonQtPublicPromoter_JLabel*)theWrappedObject)->py_q_getForeground());}
   int  getHorizontalAlignment(JLabel* theWrappedObject);
   int  getHorizontalTextPosition(JLabel* theWrappedObject);
   QWidget*  getLabelFor(JLabel* theWrappedObject);
   QPointF  getLocation(JLabel* theWrappedObject);
   QPointF  py_q_getLocation(JLabel* theWrappedObject){  return (((PythonQtPublicPromoter_JLabel*)theWrappedObject)->py_q_getLocation());}
   QString  getName(JLabel* theWrappedObject);
   QString  getText(JLabel* theWrappedObject);
   int  getVerticalAlignment(JLabel* theWrappedObject);
   bool  isOpaque(JLabel* theWrappedObject);
   bool  py_q_isOpaque(JLabel* theWrappedObject){  return (((PythonQtPublicPromoter_JLabel*)theWrappedObject)->py_q_isOpaque());}
   QWidget*  jself(JLabel* theWrappedObject);
   QWidget*  py_q_jself(JLabel* theWrappedObject){  return (((PythonQtPublicPromoter_JLabel*)theWrappedObject)->py_q_jself());}
   void setAlignmentX(JLabel* theWrappedObject, float  alignmentX);
   void setBackground(JLabel* theWrappedObject, QColor  arg__1);
   void py_q_setBackground(JLabel* theWrappedObject, QColor  arg__1){  (((PythonQtPublicPromoter_JLabel*)theWrappedObject)->py_q_setBackground(arg__1));}
   void setBounds(JLabel* theWrappedObject, int  x, int  y, int  w, int  h);
   void setDisplayedMnemonic(JLabel* theWrappedObject, char  aChar);
   void setDisplayedMnemonic(JLabel* theWrappedObject, int  key);
   void py_q_setEnabled(JLabel* theWrappedObject, bool  b){  (((PythonQtPublicPromoter_JLabel*)theWrappedObject)->py_q_setEnabled(b));}
   void py_q_setFont(JLabel* theWrappedObject, QFont  arg__1){  (((PythonQtPublicPromoter_JLabel*)theWrappedObject)->py_q_setFont(arg__1));}
   void setForeground(JLabel* theWrappedObject, QColor  arg__1);
   void setHorizontalAlignment(JLabel* theWrappedObject, int  alignment);
   void setHorizontalTextPosition(JLabel* theWrappedObject, int  textPosition);
   void setLabelFor(JLabel* theWrappedObject, QWidget*  c);
   void setLocation(JLabel* theWrappedObject, double  x, double  y);
   void setLocation(JLabel* theWrappedObject, int  x, int  y);
   void setName(JLabel* theWrappedObject, QString  name);
   void py_q_setName(JLabel* theWrappedObject, QString  name){  (((PythonQtPublicPromoter_JLabel*)theWrappedObject)->py_q_setName(name));}
   void setOpaque(JLabel* theWrappedObject, bool  arg__1);
   void py_q_setOpaque(JLabel* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_JLabel*)theWrappedObject)->py_q_setOpaque(arg__1));}
   void setSize(JLabel* theWrappedObject, double  x, double  y);
   void setText(JLabel* theWrappedObject, QString  text);
   void setVerticalAlignment(JLabel* theWrappedObject, int  alignment);
};





class PythonQtShell_JList : public JList
{
public:
    PythonQtShell_JList(QAbstractListModel*  model, QWidget*  parent = 0):JList(model, parent),_wrapper(NULL) {}
    PythonQtShell_JList(QList<QString >  arg__1, QWidget*  parent = 0):JList(arg__1, parent),_wrapper(NULL) {}
    PythonQtShell_JList(QWidget*  parent = 0):JList(parent),_wrapper(NULL) {}

   ~PythonQtShell_JList();

virtual void actionEvent(QActionEvent*  event);
virtual void changeEvent(QEvent*  arg__1);
virtual void childEvent(QChildEvent*  event);
virtual void closeEditor(QWidget*  editor, QAbstractItemDelegate::EndEditHint  hint);
virtual void closeEvent(QCloseEvent*  event);
virtual void commitData(QWidget*  editor);
virtual void contextMenuEvent(QContextMenuEvent*  arg__1);
virtual void currentChanged(const QModelIndex&  current, const QModelIndex&  previous);
virtual void customEvent(QEvent*  event);
virtual void dataChanged(const QModelIndex&  topLeft, const QModelIndex&  bottomRight, const QVector<int >&  roles = QVector<int>());
virtual int  devType() const;
virtual void doItemsLayout();
virtual void dragEnterEvent(QDragEnterEvent*  event);
virtual void dragLeaveEvent(QDragLeaveEvent*  e);
virtual void dragMoveEvent(QDragMoveEvent*  e);
virtual void dropEvent(QDropEvent*  e);
virtual bool  edit(const QModelIndex&  index, QAbstractItemView::EditTrigger  trigger, QEvent*  event);
virtual void editorDestroyed(QObject*  editor);
virtual void enterEvent(QEvent*  event);
virtual bool  event(QEvent*  e);
virtual bool  eventFilter(QObject*  object, QEvent*  event);
virtual void focusInEvent(QFocusEvent*  event);
virtual bool  focusNextPrevChild(bool  next);
virtual void focusOutEvent(QFocusEvent*  event);
virtual bool  hasHeightForWidth() const;
virtual int  heightForWidth(int  arg__1) const;
virtual void hideEvent(QHideEvent*  event);
virtual int  horizontalOffset() const;
virtual void horizontalScrollbarAction(int  action);
virtual void horizontalScrollbarValueChanged(int  value);
virtual QModelIndex  indexAt(const QPoint&  p) const;
virtual void initPainter(QPainter*  painter) const;
virtual void inputMethodEvent(QInputMethodEvent*  event);
virtual QVariant  inputMethodQuery(Qt::InputMethodQuery  query) const;
virtual bool  isIndexHidden(const QModelIndex&  index) const;
virtual void keyPressEvent(QKeyEvent*  event);
virtual void keyReleaseEvent(QKeyEvent*  event);
virtual void keyboardSearch(const QString&  search);
virtual void leaveEvent(QEvent*  event);
virtual int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
virtual QSize  minimumSizeHint() const;
virtual void mouseDoubleClickEvent(QMouseEvent*  event);
virtual void mouseMoveEvent(QMouseEvent*  e);
virtual void mousePressEvent(QMouseEvent*  event);
virtual void mouseReleaseEvent(QMouseEvent*  e);
virtual QModelIndex  moveCursor(QAbstractItemView::CursorAction  cursorAction, Qt::KeyboardModifiers  modifiers);
virtual void moveEvent(QMoveEvent*  event);
virtual bool  nativeEvent(const QByteArray&  eventType, void*  message, long*  result);
virtual QPaintEngine*  paintEngine() const;
virtual void paintEvent(QPaintEvent*  e);
virtual QPaintDevice*  redirected(QPoint*  offset) const;
virtual void reset();
virtual void resizeEvent(QResizeEvent*  e);
virtual void rowsAboutToBeRemoved(const QModelIndex&  parent, int  start, int  end);
virtual void rowsInserted(const QModelIndex&  parent, int  start, int  end);
virtual void scrollContentsBy(int  dx, int  dy);
virtual void scrollTo(const QModelIndex&  index, QAbstractItemView::ScrollHint  hint = QAbstractItemView::EnsureVisible);
virtual void selectAll();
virtual QList<QModelIndex >  selectedIndexes() const;
virtual QItemSelectionModel::SelectionFlags  selectionCommand(const QModelIndex&  index, const QEvent*  event = nullptr) const;
virtual void setModel(QAbstractItemModel*  model);
virtual void setRootIndex(const QModelIndex&  index);
virtual void setSelection(const QRect&  rect, QItemSelectionModel::SelectionFlags  command);
virtual void setSelectionModel(QItemSelectionModel*  selectionModel);
virtual void setVisible(bool  visible);
virtual void setupViewport(QWidget*  viewport);
virtual QPainter*  sharedPainter() const;
virtual void showEvent(QShowEvent*  event);
virtual QSize  sizeHint() const;
virtual int  sizeHintForColumn(int  column) const;
virtual int  sizeHintForRow(int  row) const;
virtual void startDrag(Qt::DropActions  supportedActions);
virtual void tabletEvent(QTabletEvent*  event);
virtual void timerEvent(QTimerEvent*  e);
virtual void updateEditorData();
virtual void updateEditorGeometries();
virtual void updateGeometries();
virtual int  verticalOffset() const;
virtual void verticalScrollbarAction(int  action);
virtual void verticalScrollbarValueChanged(int  value);
virtual QStyleOptionViewItem  viewOptions() const;
virtual bool  viewportEvent(QEvent*  event);
virtual QSize  viewportSizeHint() const;
virtual QRect  visualRect(const QModelIndex&  index) const;
virtual QRegion  visualRegionForSelection(const QItemSelection&  selection) const;
virtual void wheelEvent(QWheelEvent*  e);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtWrapper_JList : public QObject
{ Q_OBJECT
public:
public slots:
JList* new_JList(QAbstractListModel*  model, QWidget*  parent = 0);
JList* new_JList(QList<QString >  arg__1, QWidget*  parent = 0);
JList* new_JList(QWidget*  parent = 0);
void delete_JList(JList* obj) { delete obj; } 
   void ensureIndexIsVisible(JList* theWrappedObject, int  index);
   QAbstractListModel*  getModel(JList* theWrappedObject);
   int  getSelectedIndex(JList* theWrappedObject);
   QVariant  getSelectedValue(JList* theWrappedObject);
   QList<QModelIndex >  getSelectedValues(JList* theWrappedObject);
   bool  isSelectionEmpty(JList* theWrappedObject);
   QModelIndex  locationToIndex(JList* theWrappedObject, QPoint  arg__1);
   void setComponentPopupMenu(JList* theWrappedObject, QMenu*  menu);
   void setSelectedIndex(JList* theWrappedObject, int  index);
   void setSelectedValue(JList* theWrappedObject, QString  anObject, bool  shouldScroll);
   void setVisibleRowCount(JList* theWrappedObject, int  count);
};





class PythonQtShell_JTable : public JTable
{
public:
    PythonQtShell_JTable(QAbstractItemModel*  dm, QWidget*  parent = 0):JTable(dm, parent),_wrapper(NULL) {}
    PythonQtShell_JTable(QWidget*  parent = 0):JTable(parent),_wrapper(NULL) {}

   ~PythonQtShell_JTable();

virtual void actionEvent(QActionEvent*  event);
virtual void changeEvent(QEvent*  arg__1);
virtual void childEvent(QChildEvent*  event);
virtual void closeEditor(QWidget*  editor, QAbstractItemDelegate::EndEditHint  hint);
virtual void closeEvent(QCloseEvent*  event);
virtual void commitData(QWidget*  editor);
virtual void contextMenuEvent(QContextMenuEvent*  arg__1);
virtual void currentChanged(const QModelIndex&  current, const QModelIndex&  previous);
virtual void customEvent(QEvent*  event);
virtual void dataChanged(const QModelIndex&  topLeft, const QModelIndex&  bottomRight, const QVector<int >&  roles = QVector<int>());
virtual int  devType() const;
virtual void doItemsLayout();
virtual void dragEnterEvent(QDragEnterEvent*  event);
virtual void dragLeaveEvent(QDragLeaveEvent*  event);
virtual void dragMoveEvent(QDragMoveEvent*  event);
virtual void dropEvent(QDropEvent*  event);
virtual bool  edit(const QModelIndex&  index, QAbstractItemView::EditTrigger  trigger, QEvent*  event);
virtual void editorDestroyed(QObject*  editor);
virtual void enterEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  object, QEvent*  event);
virtual void focusInEvent(QFocusEvent*  event);
virtual bool  focusNextPrevChild(bool  next);
virtual void focusOutEvent(QFocusEvent*  event);
virtual bool  hasHeightForWidth() const;
virtual int  heightForWidth(int  arg__1) const;
virtual void hideEvent(QHideEvent*  event);
virtual int  horizontalOffset() const;
virtual void horizontalScrollbarAction(int  action);
virtual void horizontalScrollbarValueChanged(int  value);
virtual QModelIndex  indexAt(const QPoint&  p) const;
virtual void initPainter(QPainter*  painter) const;
virtual void inputMethodEvent(QInputMethodEvent*  event);
virtual QVariant  inputMethodQuery(Qt::InputMethodQuery  query) const;
virtual bool  isIndexHidden(const QModelIndex&  index) const;
virtual void keyPressEvent(QKeyEvent*  event);
virtual void keyReleaseEvent(QKeyEvent*  event);
virtual void keyboardSearch(const QString&  search);
virtual void leaveEvent(QEvent*  event);
virtual int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
virtual QSize  minimumSizeHint() const;
virtual void mouseDoubleClickEvent(QMouseEvent*  event);
virtual void mouseMoveEvent(QMouseEvent*  event);
virtual void mousePressEvent(QMouseEvent*  event);
virtual void mouseReleaseEvent(QMouseEvent*  event);
virtual QModelIndex  moveCursor(QAbstractItemView::CursorAction  cursorAction, Qt::KeyboardModifiers  modifiers);
virtual void moveEvent(QMoveEvent*  event);
virtual bool  nativeEvent(const QByteArray&  eventType, void*  message, long*  result);
virtual QPaintEngine*  paintEngine() const;
virtual void paintEvent(QPaintEvent*  e);
virtual QPaintDevice*  redirected(QPoint*  offset) const;
virtual void reset();
virtual void resizeEvent(QResizeEvent*  event);
virtual void rowsAboutToBeRemoved(const QModelIndex&  parent, int  start, int  end);
virtual void rowsInserted(const QModelIndex&  parent, int  start, int  end);
virtual void scrollContentsBy(int  dx, int  dy);
virtual void scrollTo(const QModelIndex&  index, QAbstractItemView::ScrollHint  hint = QAbstractItemView::EnsureVisible);
virtual void selectAll();
virtual QList<QModelIndex >  selectedIndexes() const;
virtual void selectionChanged(const QItemSelection&  selected, const QItemSelection&  deselected);
virtual QItemSelectionModel::SelectionFlags  selectionCommand(const QModelIndex&  index, const QEvent*  event = nullptr) const;
virtual void setModel(QAbstractItemModel*  dataModel);
virtual void setRootIndex(const QModelIndex&  index);
virtual void setSelection(const QRect&  rect, QItemSelectionModel::SelectionFlags  command);
virtual void setSelectionModel(QItemSelectionModel*  newModel);
virtual void setVisible(bool  visible);
virtual void setupViewport(QWidget*  viewport);
virtual QPainter*  sharedPainter() const;
virtual void showEvent(QShowEvent*  event);
virtual QSize  sizeHint() const;
virtual int  sizeHintForColumn(int  column) const;
virtual int  sizeHintForRow(int  row) const;
virtual void startDrag(Qt::DropActions  supportedActions);
virtual void tabletEvent(QTabletEvent*  event);
virtual void timerEvent(QTimerEvent*  event);
virtual void updateEditorData();
virtual void updateEditorGeometries();
virtual void updateGeometries();
virtual int  verticalOffset() const;
virtual void verticalScrollbarAction(int  action);
virtual void verticalScrollbarValueChanged(int  value);
virtual QStyleOptionViewItem  viewOptions() const;
virtual bool  viewportEvent(QEvent*  event);
virtual QSize  viewportSizeHint() const;
virtual QRect  visualRect(const QModelIndex&  index) const;
virtual QRegion  visualRegionForSelection(const QItemSelection&  selection) const;
virtual void wheelEvent(QWheelEvent*  arg__1);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_JTable : public JTable
{ public:
inline void promoted_columnResized(int  column, int  oldWidth, int  newWidth) { this->columnResized(column, oldWidth, newWidth); }
inline TableColumnModel*  promoted_createDefaultColumnModel() { return this->createDefaultColumnModel(); }
inline void promoted_resizeAndRepaint() { this->resizeAndRepaint(); }
inline void py_q_setModel(QAbstractItemModel*  dataModel) { JTable::setModel(dataModel); }
inline void py_q_setSelectionModel(QItemSelectionModel*  newModel) { JTable::setSelectionModel(newModel); }
};

class PythonQtWrapper_JTable : public QObject
{ Q_OBJECT
public:
public slots:
JTable* new_JTable(QAbstractItemModel*  dm, QWidget*  parent = 0);
JTable* new_JTable(QWidget*  parent = 0);
void delete_JTable(JTable* obj) { delete obj; } 
   void addColumn(JTable* theWrappedObject, TableColumn*  aColumn);
   void changeSelection(JTable* theWrappedObject, int  row, int  col, bool  arg__3, bool  arg__4);
   void clearSelection(JTable* theWrappedObject);
   int  columnAtPoint(JTable* theWrappedObject, QPoint  arg__1);
   void columnResized(JTable* theWrappedObject, int  column, int  oldWidth, int  newWidth);
   int  convertColumnIndexToModel(JTable* theWrappedObject, int  viewColumnIndex);
   int  convertColumnIndexToView(JTable* theWrappedObject, int  modelColumnIndex);
   int  convertRowIndexToModel(JTable* theWrappedObject, int  viewRowIndex);
   int  convertRowIndexToView(JTable* theWrappedObject, int  modelRowIndex);
   TableColumnModel*  createDefaultColumnModel(JTable* theWrappedObject);
   void createDefaultColumnsFromModel(JTable* theWrappedObject);
   void doLayout(JTable* theWrappedObject);
   bool  getAutoCreateColumnsFromModel(JTable* theWrappedObject);
   QAbstractItemDelegate*  getCellEditor(JTable* theWrappedObject, int  row, int  column);
   QAbstractItemDelegate*  getCellRenderer(JTable* theWrappedObject, int  row, int  column);
   TableColumn*  getColumn(JTable* theWrappedObject, QString  name);
   int  getColumnCount(JTable* theWrappedObject);
   TableColumnModel*  getColumnModel(JTable* theWrappedObject);
   QString  getColumnName(JTable* theWrappedObject, int  column);
   QColor  getGridColor(JTable* theWrappedObject);
   QAbstractItemModel*  getModel(JTable* theWrappedObject);
   QString  getName(JTable* theWrappedObject);
   int  getRowCount(JTable* theWrappedObject);
   int  getRowHeight(JTable* theWrappedObject);
   int  getRowHeight(JTable* theWrappedObject, int  arg__1);
   int  getRowMargin(JTable* theWrappedObject);
   bool  getRowSelectionAllowed(JTable* theWrappedObject);
   int  getSelectedColumn(JTable* theWrappedObject);
   int  getSelectedRow(JTable* theWrappedObject);
   QVector<int >*  getSelectedRows(JTable* theWrappedObject);
   bool  getShowHorizontalLines(JTable* theWrappedObject);
   bool  getShowVerticalLines(JTable* theWrappedObject);
   QHeaderView*  getTableHeader(JTable* theWrappedObject);
   bool  getUpdateSelectionOnSort(JTable* theWrappedObject);
   QVariant  getValueAt(JTable* theWrappedObject, int  row, int  column);
   void moveColumn(JTable* theWrappedObject, int  column, int  targetColumn);
   bool  print(JTable* theWrappedObject, JTable::PrintMode  printMode, QString  headerFormat, QString  footerFormat);
   void removeColumn(JTable* theWrappedObject, TableColumn*  aColumn);
   void resizeAndRepaint(JTable* theWrappedObject);
   int  rowAtPoint(JTable* theWrappedObject, QPoint  point);
   int  rowHeight(JTable* theWrappedObject);
   void setAutoCreateColumnsFromModel(JTable* theWrappedObject, bool  autoCreateColumnsFromModel);
   void setAutoResizeMode(JTable* theWrappedObject, int  mode);
   void setColumnModel(JTable* theWrappedObject, TableColumnModel*  columnModel);
   void setDefaultEditor(JTable* theWrappedObject, QString  arg__1, QStyledItemDelegate*  arg__2);
   void setDefaultRenderer(JTable* theWrappedObject, QString  arg__1, QObject*  arg__2);
   void setGridColor(JTable* theWrappedObject, QColor  gridColor);
   void setIntercellSpacing(JTable* theWrappedObject, QSize  intercellSpacing);
   void py_q_setModel(JTable* theWrappedObject, QAbstractItemModel*  dataModel){  (((PythonQtPublicPromoter_JTable*)theWrappedObject)->py_q_setModel(dataModel));}
   void setName(JTable* theWrappedObject, QString  name);
   void setRowHeight(JTable* theWrappedObject, int  row, int  rowHeight);
   void setRowHeight(JTable* theWrappedObject, int  rowHeight);
   void setRowMargin(JTable* theWrappedObject, int  rowMargin);
   void setRowSelectionAllowed(JTable* theWrappedObject, bool  arg__1);
   void setRowSelectionInterval(JTable* theWrappedObject, int  index0, int  index1);
   void setSelectionMode(JTable* theWrappedObject, int  selectionMode);
   void py_q_setSelectionModel(JTable* theWrappedObject, QItemSelectionModel*  newModel){  (((PythonQtPublicPromoter_JTable*)theWrappedObject)->py_q_setSelectionModel(newModel));}
   void setShowGrid(JTable* theWrappedObject, bool  showGrid);
   void setShowHorizontalLines(JTable* theWrappedObject, bool  showHorizontalLines);
   void setShowVerticalLines(JTable* theWrappedObject, bool  showVerticalLines);
   void setUpdateSelectionOnSort(JTable* theWrappedObject, bool  update);
};


