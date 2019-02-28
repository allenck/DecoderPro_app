#include <PythonQt.h>
#include <QObject>
#include <QVariant>
#include <abstractsensormanager.h>
#include <abstractturnoutmanager.h>
#include <defaultprogrammermanager.h>
#include <editor.h>
#include <editscene.h>
#include <jframe.h>
#include <jmrijframe.h>
#include <layouteditor.h>
#include <light.h>
#include <lncommandstationtype.h>
#include <lnpowermanager.h>
#include <lnreportermanager.h>
#include <lnsensormanager.h>
#include <lntrafficcontroller.h>
#include <lnturnoutmanager.h>
#include <locoaddress.h>
#include <loconetinterface.h>
#include <loconetmessage.h>
#include <loconetsystemconnectionmemo.h>
#include <logger.h>
#include <logixmanager.h>
#include <manager.h>
#include <memorymanager.h>
#include <multiiconeditor.h>
#include <namedbean.h>
#include <networkportadapter.h>
#include <paneleditor.h>
#include <panelmenu.h>
#include <portadapter.h>
#include <positionable.h>
#include <positionablelabel.h>
#include <powermanager.h>
#include <proglistener.h>
#include <programmermanager.h>
#include <programmingmode.h>
#include <propertychangeevent.h>
#include <propertychangelistener.h>
#include <propertychangesupport.h>
#include <proxylightmanager.h>
#include <proxysensormanager.h>
#include <proxyturnoutmanager.h>
#include <qaction.h>
#include <qactiongroup.h>
#include <qbytearray.h>
#include <qcolor.h>
#include <qcompleter.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qdatastream.h>
#include <qevent.h>
#include <qfont.h>
#include <qfontinfo.h>
#include <qfontmetrics.h>
#include <qgraphicsitem.h>
#include <qgraphicsproxywidget.h>
#include <qgraphicsscene.h>
#include <qgraphicssceneevent.h>
#include <qicon.h>
#include <qkeysequence.h>
#include <qlabel.h>
#include <qlayout.h>
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
#include <qpixmap.h>
#include <qpoint.h>
#include <qrect.h>
#include <qregion.h>
#include <qscrollarea.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstringlist.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qvector.h>
#include <qwidget.h>
#include <reportermanager.h>
#include <rfidsensormanager.h>
#include <sensor.h>
#include <systemconnectionmemo.h>
#include <throttlemanager.h>
#include <turnout.h>
#include <windowlistener.h>



class PythonQtShell_LnTurnoutManager : public LnTurnoutManager
{
public:
    PythonQtShell_LnTurnoutManager(LnTrafficController*  fastcontroller, LnTrafficController*  throttledcontroller, QString  prefix, bool  mTurnoutNoRetry, QObject*  parent = 0):LnTurnoutManager(fastcontroller, throttledcontroller, prefix, mTurnoutNoRetry, parent),_wrapper(NULL) {}

   ~PythonQtShell_LnTurnoutManager();

virtual void Register(NamedBean*  s);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual bool  allowMultipleAdditions(QString  systemName);
virtual int  askControlType(QString  systemName);
virtual int  askNumControlBits(QString  systemName);
virtual void childEvent(QChildEvent*  event);
virtual Turnout*  createNewTurnout(QString  systemName, QString  userName);
virtual QString  createSystemName(QString  curAddress, QString  prefix);
virtual void customEvent(QEvent*  event);
virtual void deregister(NamedBean*  s);
virtual void dispose();
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual NamedBean*  getBeanBySystemName(QString  systemName);
virtual NamedBean*  getBeanByUserName(QString  userName);
virtual QString  getBeanTypeHandled();
virtual Turnout*  getBySystemName(QString  name);
virtual Turnout*  getByUserName(QString  key);
virtual QString  getClosedText();
virtual QString  getDefaultClosedSpeed();
virtual QString  getDefaultThrownSpeed();
virtual QString  getEntryToolTip();
virtual NamedBean*  getNamedBean(QString  name);
virtual QSet<NamedBean* >  getNamedBeanSet();
virtual QString  getNextValidAddress(QString  curAddress, QString  prefix);
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList();
virtual QString  getSystemPrefix();
virtual QString  getThrownText();
virtual Turnout*  getTurnout(QString  name);
virtual QStringList  getValidOperationTypes();
virtual int  getXMLOrder();
virtual bool  isControlTypeSupported(QString  systemName);
virtual bool  isNumControlBitsSupported(QString  systemName);
virtual QString  makeSystemName(QString  s);
virtual Turnout*  newTurnout(QString  systemName, QString  userName);
virtual QString  normalizeSystemName(QString  inputName);
virtual void propertyChange(PropertyChangeEvent*  e);
virtual Turnout*  provideTurnout(QString  name);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void setDefaultClosedSpeed(QString  speed);
virtual void setDefaultThrownSpeed(QString  speed);
virtual void timerEvent(QTimerEvent*  event);
virtual char  typeLetter();
virtual Manager::NameValidity  validSystemNameFormat(QString  arg__1);
virtual void vetoableChange(PropertyChangeEvent*  evt);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_LnTurnoutManager : public LnTurnoutManager
{ public:
inline Turnout*  py_q_createNewTurnout(QString  systemName, QString  userName) { return LnTurnoutManager::createNewTurnout(systemName, userName); }
inline void py_q_dispose() { LnTurnoutManager::dispose(); }
inline QString  py_q_getSystemPrefix() { return LnTurnoutManager::getSystemPrefix(); }
};

class PythonQtWrapper_LnTurnoutManager : public QObject
{ Q_OBJECT
public:
public slots:
LnTurnoutManager* new_LnTurnoutManager(LnTrafficController*  fastcontroller, LnTrafficController*  throttledcontroller, QString  prefix, bool  mTurnoutNoRetry, QObject*  parent = 0);
void delete_LnTurnoutManager(LnTurnoutManager* obj) { delete obj; } 
   Turnout*  py_q_createNewTurnout(LnTurnoutManager* theWrappedObject, QString  systemName, QString  userName){  return (((PythonQtPublicPromoter_LnTurnoutManager*)theWrappedObject)->py_q_createNewTurnout(systemName, userName));}
   void py_q_dispose(LnTurnoutManager* theWrappedObject){  (((PythonQtPublicPromoter_LnTurnoutManager*)theWrappedObject)->py_q_dispose());}
   QString  py_q_getSystemPrefix(LnTurnoutManager* theWrappedObject){  return (((PythonQtPublicPromoter_LnTurnoutManager*)theWrappedObject)->py_q_getSystemPrefix());}
};





class PythonQtShell_LocoAddress : public LocoAddress
{
public:
    PythonQtShell_LocoAddress():LocoAddress(),_wrapper(NULL) {}

   ~PythonQtShell_LocoAddress();

virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual int  getNumber();
virtual LocoAddress::Protocol  getProtocol();
virtual void timerEvent(QTimerEvent*  event);
virtual QString  toString();

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_LocoAddress : public LocoAddress
{ public:
inline int  py_q_getNumber() { return LocoAddress::getNumber(); }
inline LocoAddress::Protocol  py_q_getProtocol() { return LocoAddress::getProtocol(); }
inline QString  py_q_toString() { return LocoAddress::toString(); }
};

class PythonQtWrapper_LocoAddress : public QObject
{ Q_OBJECT
public:
public slots:
LocoAddress* new_LocoAddress();
void delete_LocoAddress(LocoAddress* obj) { delete obj; } 
   LocoAddress::Protocol  static_LocoAddress_getByPeopleName(QString  pName);
   LocoAddress::Protocol  static_LocoAddress_getByShortName(QString  shName);
   int  getNumber(LocoAddress* theWrappedObject);
   int  py_q_getNumber(LocoAddress* theWrappedObject){  return (((PythonQtPublicPromoter_LocoAddress*)theWrappedObject)->py_q_getNumber());}
   QString  static_LocoAddress_getPeopleName(LocoAddress::Protocol  p);
   LocoAddress::Protocol  getProtocol(LocoAddress* theWrappedObject);
   LocoAddress::Protocol  py_q_getProtocol(LocoAddress* theWrappedObject){  return (((PythonQtPublicPromoter_LocoAddress*)theWrappedObject)->py_q_getProtocol());}
   QString  static_LocoAddress_getShortName(LocoAddress::Protocol  p);
   QString  toString(LocoAddress* theWrappedObject);
   QString  py_q_toString(LocoAddress* theWrappedObject){  return (((PythonQtPublicPromoter_LocoAddress*)theWrappedObject)->py_q_toString());}
    QString py_toString(LocoAddress*);
};





class PythonQtShell_LocoNetInterface : public LocoNetInterface
{
public:
    PythonQtShell_LocoNetInterface(QObject*  parent = 0):LocoNetInterface(parent),_wrapper(NULL) {}

   ~PythonQtShell_LocoNetInterface();

virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual void sendLocoNetMessage(LocoNetMessage*  arg__1);
virtual bool  status();
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_LocoNetInterface : public LocoNetInterface
{ public:
inline void py_q_sendLocoNetMessage(LocoNetMessage*  arg__1) { LocoNetInterface::sendLocoNetMessage(arg__1); }
inline bool  py_q_status() { return LocoNetInterface::status(); }
};

class PythonQtWrapper_LocoNetInterface : public QObject
{ Q_OBJECT
public:
public slots:
LocoNetInterface* new_LocoNetInterface(QObject*  parent = 0);
void delete_LocoNetInterface(LocoNetInterface* obj) { delete obj; } 
   void sendLocoNetMessage(LocoNetInterface* theWrappedObject, LocoNetMessage*  arg__1);
   void py_q_sendLocoNetMessage(LocoNetInterface* theWrappedObject, LocoNetMessage*  arg__1){  (((PythonQtPublicPromoter_LocoNetInterface*)theWrappedObject)->py_q_sendLocoNetMessage(arg__1));}
   bool  status(LocoNetInterface* theWrappedObject);
   bool  py_q_status(LocoNetInterface* theWrappedObject){  return (((PythonQtPublicPromoter_LocoNetInterface*)theWrappedObject)->py_q_status());}
};





class PythonQtShell_LocoNetMessage : public LocoNetMessage
{
public:
    PythonQtShell_LocoNetMessage(QVector<char >  contents, QObject*  parent = 0):LocoNetMessage(contents, parent),_wrapper(NULL) {}
    PythonQtShell_LocoNetMessage(QVector<int >  contents, QObject*  parent = 0):LocoNetMessage(contents, parent),_wrapper(NULL) {}
    PythonQtShell_LocoNetMessage(const LocoNetMessage&  original, QObject*  parent = 0):LocoNetMessage(original, parent),_wrapper(NULL) {}
    PythonQtShell_LocoNetMessage(int  len, QObject*  parent = 0):LocoNetMessage(len, parent),_wrapper(NULL) {}

   ~PythonQtShell_LocoNetMessage();

virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_LocoNetMessage : public LocoNetMessage
{ public:
static inline bool  promoted_highBit(int  val) { return highBit(val); }
static inline int  promoted_highByte(int  val) { return highByte(val); }
static inline int  promoted_lowByte(int  val) { return lowByte(val); }
};

class PythonQtWrapper_LocoNetMessage : public QObject
{ Q_OBJECT
public:
public slots:
LocoNetMessage* new_LocoNetMessage(QVector<char >  contents, QObject*  parent = 0);
LocoNetMessage* new_LocoNetMessage(QVector<int >  contents, QObject*  parent = 0);
LocoNetMessage* new_LocoNetMessage(const LocoNetMessage&  original, QObject*  parent = 0);
LocoNetMessage* new_LocoNetMessage(int  len, QObject*  parent = 0);
void delete_LocoNetMessage(LocoNetMessage* obj) { delete obj; } 
   bool  checkParity(LocoNetMessage* theWrappedObject);
   bool  equals(LocoNetMessage* theWrappedObject, QObject*  o);
   int  getElement(LocoNetMessage* theWrappedObject, int  n);
   int  getNumDataElements(LocoNetMessage* theWrappedObject);
   int  getOpCode(LocoNetMessage* theWrappedObject);
   QString  getOpCodeHex(LocoNetMessage* theWrappedObject);
   QVector<int >  getPeerXfrData(LocoNetMessage* theWrappedObject);
   int  hashCode(LocoNetMessage* theWrappedObject);
   bool  static_LocoNetMessage_highBit(int  val);
   int  static_LocoNetMessage_highByte(int  val);
   int  inputRepAddr(LocoNetMessage* theWrappedObject);
   int  static_LocoNetMessage_lowByte(int  val);
   LocoNetMessage*  static_LocoNetMessage_makePeerXfr(int  src, int  dst, QVector<int >  d, int  code);
   LocoNetMessage*  static_LocoNetMessage_makePeerXfr2(int  src, int  dsth, int  dstl, int  svAdrh, int  svAdrl, QVector<int >  d, int  code);
   int  sensorAddr(LocoNetMessage* theWrappedObject);
   void setElement(LocoNetMessage* theWrappedObject, int  n, int  v);
   void setOpCode(LocoNetMessage* theWrappedObject, int  i);
   void setParity(LocoNetMessage* theWrappedObject);
   QByteArray  toByteArray(LocoNetMessage* theWrappedObject);
   QVector<char >  toCharArray(LocoNetMessage* theWrappedObject);
   QString  toMonitorString(LocoNetMessage* theWrappedObject);
   QString  toMonitorString(LocoNetMessage* theWrappedObject, QString  prefix);
   QString  toString(LocoNetMessage* theWrappedObject);
   int  turnoutAddr(LocoNetMessage* theWrappedObject);
    QString py_toString(LocoNetMessage*);
void py_set__dataBytes(LocoNetMessage* theWrappedObject, QVector<int >  _dataBytes){ theWrappedObject->_dataBytes = _dataBytes; }
QVector<int >  py_get__dataBytes(LocoNetMessage* theWrappedObject){ return theWrappedObject->_dataBytes; }
};





class PythonQtShell_LocoNetSystemConnectionMemo : public LocoNetSystemConnectionMemo
{
public:
    PythonQtShell_LocoNetSystemConnectionMemo(QObject*  parent = 0):LocoNetSystemConnectionMemo(parent),_wrapper(NULL) {}

   ~PythonQtShell_LocoNetSystemConnectionMemo();

virtual void childEvent(QChildEvent*  event);
virtual void configureManagers();
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual Manager*  get(QString  T);
virtual bool  provides(QString  type);
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_LocoNetSystemConnectionMemo : public LocoNetSystemConnectionMemo
{ public:
inline void py_q_configureManagers() { LocoNetSystemConnectionMemo::configureManagers(); }
inline Manager*  py_q_get(QString  T) { return LocoNetSystemConnectionMemo::get(T); }
inline bool  py_q_provides(QString  type) { return LocoNetSystemConnectionMemo::provides(type); }
};

class PythonQtWrapper_LocoNetSystemConnectionMemo : public QObject
{ Q_OBJECT
public:
public slots:
LocoNetSystemConnectionMemo* new_LocoNetSystemConnectionMemo(QObject*  parent = 0);
void delete_LocoNetSystemConnectionMemo(LocoNetSystemConnectionMemo* obj) { delete obj; } 
   void configureCommandStation(LocoNetSystemConnectionMemo* theWrappedObject, LnCommandStationType*  type, bool  mTurnoutNoRetry, bool  mTurnoutExtraSpace, bool  mTranspondingAvailable);
   void configureManagers(LocoNetSystemConnectionMemo* theWrappedObject);
   void py_q_configureManagers(LocoNetSystemConnectionMemo* theWrappedObject){  (((PythonQtPublicPromoter_LocoNetSystemConnectionMemo*)theWrappedObject)->py_q_configureManagers());}
   void dispose(LocoNetSystemConnectionMemo* theWrappedObject);
   Manager*  py_q_get(LocoNetSystemConnectionMemo* theWrappedObject, QString  T){  return (((PythonQtPublicPromoter_LocoNetSystemConnectionMemo*)theWrappedObject)->py_q_get(T));}
   LnClockControl*  getClockControl(LocoNetSystemConnectionMemo* theWrappedObject);
   LnLightManager*  getLightManager(LocoNetSystemConnectionMemo* theWrappedObject);
   LnTrafficController*  getLnTrafficController(LocoNetSystemConnectionMemo* theWrappedObject);
   LnPowerManager*  getPowerManager(LocoNetSystemConnectionMemo* theWrappedObject);
   DefaultProgrammerManager*  getProgrammerManager(LocoNetSystemConnectionMemo* theWrappedObject);
   LnReporterManager*  getReporterManager(LocoNetSystemConnectionMemo* theWrappedObject);
   LnSensorManager*  getSensorManager(LocoNetSystemConnectionMemo* theWrappedObject);
   ThrottleManager*  getThrottleManager(LocoNetSystemConnectionMemo* theWrappedObject);
   LnTurnoutManager*  getTurnoutManager(LocoNetSystemConnectionMemo* theWrappedObject);
   bool  py_q_provides(LocoNetSystemConnectionMemo* theWrappedObject, QString  type){  return (((PythonQtPublicPromoter_LocoNetSystemConnectionMemo*)theWrappedObject)->py_q_provides(type));}
   void setLnTrafficController(LocoNetSystemConnectionMemo* theWrappedObject, LnTrafficController*  lt);
   void setProgrammerManager(LocoNetSystemConnectionMemo* theWrappedObject, DefaultProgrammerManager*  p);
   void setThrottleManager(LocoNetSystemConnectionMemo* theWrappedObject, ThrottleManager*  t);
};





class PythonQtShell_Logger : public Logger
{
public:
    PythonQtShell_Logger(QString  name = "", QObject*  parent = 0):Logger(name, parent),_wrapper(NULL) {}
    PythonQtShell_Logger(const Logger&  arg__1):Logger(arg__1),_wrapper(NULL) {}

   ~PythonQtShell_Logger();

virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtWrapper_Logger : public QObject
{ Q_OBJECT
public:
public slots:
Logger* new_Logger(QString  name = "", QObject*  parent = 0);
Logger* new_Logger(const Logger&  arg__1);
void delete_Logger(Logger* obj) { delete obj; } 
   void debug(Logger* theWrappedObject, QString  s);
   void static_Logger_error(QString  s, QVariant  ex = QVariant());
   void info(Logger* theWrappedObject, QString  s);
   bool  isDebugEnabled(Logger* theWrappedObject);
   bool  isInfoEnabled(Logger* theWrappedObject);
   bool  isTraceEnabled(Logger* theWrappedObject);
   void sendError(Logger* theWrappedObject, QString  arg__1);
   void setDebugEnabled(Logger* theWrappedObject, bool  bState);
   void setInfoEnabled(Logger* theWrappedObject, bool  bState);
   void setTraceEnabled(Logger* theWrappedObject, bool  bState);
   void trace(Logger* theWrappedObject, QString  s);
   void warn(Logger* theWrappedObject, QString  s);
};





class PythonQtShell_LogixManager : public LogixManager
{
public:
    PythonQtShell_LogixManager(QObject*  parent = 0):LogixManager(parent),_wrapper(NULL) {}

   ~PythonQtShell_LogixManager();

virtual void Register(NamedBean*  s);
virtual void activateAllLogixs();
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual void deregister(NamedBean*  s);
virtual void dispose();
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual NamedBean*  getBeanBySystemName(QString  systemName);
virtual NamedBean*  getBeanByUserName(QString  userName);
virtual QString  getBeanTypeHandled();
virtual QString  getEntryToolTip();
virtual bool  getLoadDisabled();
virtual NamedBean*  getNamedBean(QString  name);
virtual QSet<NamedBean* >  getNamedBeanSet();
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList();
virtual QString  getSystemPrefix();
virtual int  getXMLOrder();
virtual QString  makeSystemName(QString  s);
virtual QString  normalizeSystemName(QString  inputName);
virtual void propertyChange(PropertyChangeEvent*  e);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void setLoadDisabled(bool  arg__1);
virtual void timerEvent(QTimerEvent*  event);
virtual char  typeLetter();
virtual Manager::NameValidity  validSystemNameFormat(QString  arg__1);
virtual void vetoableChange(PropertyChangeEvent*  evt);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_LogixManager : public LogixManager
{ public:
inline void py_q_activateAllLogixs() { LogixManager::activateAllLogixs(); }
inline bool  py_q_getLoadDisabled() { return LogixManager::getLoadDisabled(); }
inline void py_q_setLoadDisabled(bool  arg__1) { LogixManager::setLoadDisabled(arg__1); }
};

class PythonQtWrapper_LogixManager : public QObject
{ Q_OBJECT
public:
public slots:
LogixManager* new_LogixManager(QObject*  parent = 0);
void delete_LogixManager(LogixManager* obj) { delete obj; } 
   void activateAllLogixs(LogixManager* theWrappedObject);
   void py_q_activateAllLogixs(LogixManager* theWrappedObject){  (((PythonQtPublicPromoter_LogixManager*)theWrappedObject)->py_q_activateAllLogixs());}
   bool  getLoadDisabled(LogixManager* theWrappedObject);
   bool  py_q_getLoadDisabled(LogixManager* theWrappedObject){  return (((PythonQtPublicPromoter_LogixManager*)theWrappedObject)->py_q_getLoadDisabled());}
   void setLoadDisabled(LogixManager* theWrappedObject, bool  arg__1);
   void py_q_setLoadDisabled(LogixManager* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_LogixManager*)theWrappedObject)->py_q_setLoadDisabled(arg__1));}
};





class PythonQtShell_Manager : public Manager
{
public:
    PythonQtShell_Manager(QObject*  parent = 0):Manager(parent),_wrapper(NULL) {}

   ~PythonQtShell_Manager();

virtual void Register(NamedBean*  arg__1);
virtual void addPropertyChangeListener(PropertyChangeListener*  arg__1);
virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual void deregister(NamedBean*  arg__1);
virtual void dispose();
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual NamedBean*  getBeanBySystemName(QString  arg__1);
virtual NamedBean*  getBeanByUserName(QString  arg__1);
virtual QString  getBeanTypeHandled();
virtual QString  getEntryToolTip();
virtual NamedBean*  getNamedBean(QString  arg__1);
virtual QSet<NamedBean* >  getNamedBeanSet();
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList();
virtual QString  getSystemPrefix();
virtual int  getXMLOrder();
virtual QString  makeSystemName(QString  arg__1);
virtual QString  normalizeSystemName(QString  arg__1);
virtual void removePropertyChangeListener(PropertyChangeListener*  arg__1);
virtual void timerEvent(QTimerEvent*  event);
virtual char  typeLetter();
virtual Manager::NameValidity  validSystemNameFormat(QString  arg__1);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_Manager : public Manager
{ public:
inline void py_q_Register(NamedBean*  arg__1) { Manager::Register(arg__1); }
inline void py_q_addPropertyChangeListener(PropertyChangeListener*  arg__1) { Manager::addPropertyChangeListener(arg__1); }
inline void py_q_deregister(NamedBean*  arg__1) { Manager::deregister(arg__1); }
inline void py_q_dispose() { Manager::dispose(); }
inline NamedBean*  py_q_getBeanBySystemName(QString  arg__1) { return Manager::getBeanBySystemName(arg__1); }
inline NamedBean*  py_q_getBeanByUserName(QString  arg__1) { return Manager::getBeanByUserName(arg__1); }
inline QString  py_q_getBeanTypeHandled() { return Manager::getBeanTypeHandled(); }
inline QString  py_q_getEntryToolTip() { return Manager::getEntryToolTip(); }
inline NamedBean*  py_q_getNamedBean(QString  arg__1) { return Manager::getNamedBean(arg__1); }
inline QSet<NamedBean* >  py_q_getNamedBeanSet() { return Manager::getNamedBeanSet(); }
inline QStringList  py_q_getSystemNameArray() { return Manager::getSystemNameArray(); }
inline QStringList  py_q_getSystemNameList() { return Manager::getSystemNameList(); }
inline QString  py_q_getSystemPrefix() { return Manager::getSystemPrefix(); }
inline int  py_q_getXMLOrder() { return Manager::getXMLOrder(); }
inline QString  py_q_makeSystemName(QString  arg__1) { return Manager::makeSystemName(arg__1); }
inline QString  py_q_normalizeSystemName(QString  arg__1) { return Manager::normalizeSystemName(arg__1); }
inline void py_q_removePropertyChangeListener(PropertyChangeListener*  arg__1) { Manager::removePropertyChangeListener(arg__1); }
inline char  py_q_typeLetter() { return Manager::typeLetter(); }
inline Manager::NameValidity  py_q_validSystemNameFormat(QString  arg__1) { return Manager::validSystemNameFormat(arg__1); }
};

class PythonQtWrapper_Manager : public QObject
{ Q_OBJECT
public:
public slots:
Manager* new_Manager(QObject*  parent = 0);
void delete_Manager(Manager* obj) { delete obj; } 
   void Register(Manager* theWrappedObject, NamedBean*  arg__1);
   void py_q_Register(Manager* theWrappedObject, NamedBean*  arg__1){  (((PythonQtPublicPromoter_Manager*)theWrappedObject)->py_q_Register(arg__1));}
   void addPropertyChangeListener(Manager* theWrappedObject, PropertyChangeListener*  arg__1);
   void py_q_addPropertyChangeListener(Manager* theWrappedObject, PropertyChangeListener*  arg__1){  (((PythonQtPublicPromoter_Manager*)theWrappedObject)->py_q_addPropertyChangeListener(arg__1));}
   void deregister(Manager* theWrappedObject, NamedBean*  arg__1);
   void py_q_deregister(Manager* theWrappedObject, NamedBean*  arg__1){  (((PythonQtPublicPromoter_Manager*)theWrappedObject)->py_q_deregister(arg__1));}
   void dispose(Manager* theWrappedObject);
   void py_q_dispose(Manager* theWrappedObject){  (((PythonQtPublicPromoter_Manager*)theWrappedObject)->py_q_dispose());}
   NamedBean*  getBeanBySystemName(Manager* theWrappedObject, QString  arg__1);
   NamedBean*  py_q_getBeanBySystemName(Manager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_Manager*)theWrappedObject)->py_q_getBeanBySystemName(arg__1));}
   NamedBean*  getBeanByUserName(Manager* theWrappedObject, QString  arg__1);
   NamedBean*  py_q_getBeanByUserName(Manager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_Manager*)theWrappedObject)->py_q_getBeanByUserName(arg__1));}
   QString  getBeanTypeHandled(Manager* theWrappedObject);
   QString  py_q_getBeanTypeHandled(Manager* theWrappedObject){  return (((PythonQtPublicPromoter_Manager*)theWrappedObject)->py_q_getBeanTypeHandled());}
   QString  getEntryToolTip(Manager* theWrappedObject);
   QString  py_q_getEntryToolTip(Manager* theWrappedObject){  return (((PythonQtPublicPromoter_Manager*)theWrappedObject)->py_q_getEntryToolTip());}
   NamedBean*  getNamedBean(Manager* theWrappedObject, QString  arg__1);
   NamedBean*  py_q_getNamedBean(Manager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_Manager*)theWrappedObject)->py_q_getNamedBean(arg__1));}
   QSet<NamedBean* >  getNamedBeanSet(Manager* theWrappedObject);
   QSet<NamedBean* >  py_q_getNamedBeanSet(Manager* theWrappedObject){  return (((PythonQtPublicPromoter_Manager*)theWrappedObject)->py_q_getNamedBeanSet());}
   QStringList  getSystemNameArray(Manager* theWrappedObject);
   QStringList  py_q_getSystemNameArray(Manager* theWrappedObject){  return (((PythonQtPublicPromoter_Manager*)theWrappedObject)->py_q_getSystemNameArray());}
   QStringList  getSystemNameList(Manager* theWrappedObject);
   QStringList  py_q_getSystemNameList(Manager* theWrappedObject){  return (((PythonQtPublicPromoter_Manager*)theWrappedObject)->py_q_getSystemNameList());}
   QString  getSystemPrefix(Manager* theWrappedObject);
   QString  py_q_getSystemPrefix(Manager* theWrappedObject){  return (((PythonQtPublicPromoter_Manager*)theWrappedObject)->py_q_getSystemPrefix());}
   int  static_Manager_getSystemPrefixLength(QString  inputName) throw (NamedBean::BadSystemNameException);
   int  getXMLOrder(Manager* theWrappedObject);
   int  py_q_getXMLOrder(Manager* theWrappedObject){  return (((PythonQtPublicPromoter_Manager*)theWrappedObject)->py_q_getXMLOrder());}
   bool  static_Manager_isLegacySystemPrefix(QString  prefix);
   QString  makeSystemName(Manager* theWrappedObject, QString  arg__1);
   QString  py_q_makeSystemName(Manager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_Manager*)theWrappedObject)->py_q_makeSystemName(arg__1));}
   QString  normalizeSystemName(Manager* theWrappedObject, QString  arg__1);
   QString  py_q_normalizeSystemName(Manager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_Manager*)theWrappedObject)->py_q_normalizeSystemName(arg__1));}
   void removePropertyChangeListener(Manager* theWrappedObject, PropertyChangeListener*  arg__1);
   void py_q_removePropertyChangeListener(Manager* theWrappedObject, PropertyChangeListener*  arg__1){  (((PythonQtPublicPromoter_Manager*)theWrappedObject)->py_q_removePropertyChangeListener(arg__1));}
   int  static_Manager_startsWithLegacySystemPrefix(QString  prefix);
   char  typeLetter(Manager* theWrappedObject);
   char  py_q_typeLetter(Manager* theWrappedObject){  return (((PythonQtPublicPromoter_Manager*)theWrappedObject)->py_q_typeLetter());}
   Manager::NameValidity  validSystemNameFormat(Manager* theWrappedObject, QString  arg__1);
   Manager::NameValidity  py_q_validSystemNameFormat(Manager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_Manager*)theWrappedObject)->py_q_validSystemNameFormat(arg__1));}
};





class PythonQtShell_MemoryManager : public MemoryManager
{
public:
    PythonQtShell_MemoryManager(QObject*  parent = 0):MemoryManager(parent),_wrapper(NULL) {}

   ~PythonQtShell_MemoryManager();

virtual void Register(NamedBean*  s);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual void deregister(NamedBean*  s);
virtual void dispose();
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual NamedBean*  getBeanBySystemName(QString  systemName);
virtual NamedBean*  getBeanByUserName(QString  userName);
virtual QString  getBeanTypeHandled();
virtual QString  getEntryToolTip();
virtual NamedBean*  getNamedBean(QString  name);
virtual QSet<NamedBean* >  getNamedBeanSet();
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList();
virtual QString  getSystemPrefix();
virtual int  getXMLOrder();
virtual QString  makeSystemName(QString  s);
virtual QString  normalizeSystemName(QString  inputName);
virtual void propertyChange(PropertyChangeEvent*  e);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void timerEvent(QTimerEvent*  event);
virtual char  typeLetter();
virtual Manager::NameValidity  validSystemNameFormat(QString  arg__1);
virtual void vetoableChange(PropertyChangeEvent*  evt);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtWrapper_MemoryManager : public QObject
{ Q_OBJECT
public:
public slots:
MemoryManager* new_MemoryManager(QObject*  parent = 0);
void delete_MemoryManager(MemoryManager* obj) { delete obj; } 
};





class PythonQtShell_MultiIconEditor : public MultiIconEditor
{
public:
    PythonQtShell_MultiIconEditor(int  nIcons, QWidget*  parent = 0):MultiIconEditor(nIcons, parent),_wrapper(NULL) {}

   ~PythonQtShell_MultiIconEditor();

virtual void actionEvent(QActionEvent*  event);
virtual void changeEvent(QEvent*  arg__1);
virtual void childEvent(QChildEvent*  event);
virtual void closeEvent(QCloseEvent*  event);
virtual void contextMenuEvent(QContextMenuEvent*  event);
virtual void customEvent(QEvent*  event);
virtual int  devType() const;
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
virtual bool  hasHeightForWidth() const;
virtual int  heightForWidth(int  arg__1) const;
virtual void hideEvent(QHideEvent*  event);
virtual void initPainter(QPainter*  painter) const;
virtual void inputMethodEvent(QInputMethodEvent*  arg__1);
virtual QVariant  inputMethodQuery(Qt::InputMethodQuery  arg__1) const;
virtual void keyPressEvent(QKeyEvent*  event);
virtual void keyReleaseEvent(QKeyEvent*  event);
virtual void leaveEvent(QEvent*  event);
virtual int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
virtual QSize  minimumSizeHint() const;
virtual void mouseDoubleClickEvent(QMouseEvent*  event);
virtual void mouseMoveEvent(QMouseEvent*  event);
virtual void mousePressEvent(QMouseEvent*  event);
virtual void mouseReleaseEvent(QMouseEvent*  event);
virtual void moveEvent(QMoveEvent*  event);
virtual bool  nativeEvent(const QByteArray&  eventType, void*  message, long*  result);
virtual QPaintEngine*  paintEngine() const;
virtual void paintEvent(QPaintEvent*  event);
virtual QPaintDevice*  redirected(QPoint*  offset) const;
virtual void resizeEvent(QResizeEvent*  event);
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

class PythonQtWrapper_MultiIconEditor : public QObject
{ Q_OBJECT
public:
public slots:
MultiIconEditor* new_MultiIconEditor(int  nIcons, QWidget*  parent = 0);
void delete_MultiIconEditor(MultiIconEditor* obj) { delete obj; } 
   void complete(MultiIconEditor* theWrappedObject);
   void dispose(MultiIconEditor* theWrappedObject);
   QString  getIconName(MultiIconEditor* theWrappedObject, int  iconNum);
   void setIcon(MultiIconEditor* theWrappedObject, int  iconNum, QString  label, QString  name);
};





class PythonQtShell_MyGraphicsItemGroup : public MyGraphicsItemGroup
{
public:
    PythonQtShell_MyGraphicsItemGroup():MyGraphicsItemGroup(),_wrapper(NULL) {}

   ~PythonQtShell_MyGraphicsItemGroup();

virtual QRectF  boundingRect() const;
virtual bool  isObscuredBy(const QGraphicsItem*  item) const;
virtual QPainterPath  opaqueArea() const;
virtual void paint(QPainter*  painter, const QStyleOptionGraphicsItem*  option, QWidget*  widget = nullptr);
virtual int  type() const;

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_MyGraphicsItemGroup : public MyGraphicsItemGroup
{ public:
inline int  py_q_type() const { return MyGraphicsItemGroup::type(); }
};

class PythonQtWrapper_MyGraphicsItemGroup : public QObject
{ Q_OBJECT
public:
Q_ENUMS(enum_1 )
enum enum_1{
  Type = MyGraphicsItemGroup::Type};
public slots:
MyGraphicsItemGroup* new_MyGraphicsItemGroup();
void delete_MyGraphicsItemGroup(MyGraphicsItemGroup* obj) { delete obj; } 
   QString  name(MyGraphicsItemGroup* theWrappedObject);
   void setName(MyGraphicsItemGroup* theWrappedObject, QString  name);
   int  py_q_type(MyGraphicsItemGroup* theWrappedObject) const{  return (((PythonQtPublicPromoter_MyGraphicsItemGroup*)theWrappedObject)->py_q_type());}
};





class PythonQtShell_NamedBean : public NamedBean
{
public:
    PythonQtShell_NamedBean(QObject*  parent = 0):NamedBean(parent),_wrapper(NULL) {}
    PythonQtShell_NamedBean(QString  name, QObject*  parent = 0):NamedBean(name, parent),_wrapper(NULL) {}
    PythonQtShell_NamedBean(const NamedBean&  arg__1):NamedBean(arg__1),_wrapper(NULL) {}

   ~PythonQtShell_NamedBean();

virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(PropertyChangeListener*  l, QString  name, const QString  listenerRef);
virtual void childEvent(QChildEvent*  event);
virtual int  compareSystemNameSuffix(QString  suffix1, QString  suffix2, NamedBean*  n2);
virtual int  compareTo(NamedBean*  n2);
virtual void customEvent(QEvent*  event);
virtual QString  describeState(int  arg__1);
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
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners(QString  name);
virtual QSet<QString >  getPropertyKeys();
virtual int  getState();
virtual QString  getSystemName();
virtual QString  getUserName();
virtual bool  hashCode();
virtual void removeProperty(QString  arg__1);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
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

class PythonQtPublicPromoter_NamedBean : public NamedBean
{ public:
inline void py_q_addPropertyChangeListener(PropertyChangeListener*  l) { NamedBean::addPropertyChangeListener(l); }
inline void py_q_addPropertyChangeListener(PropertyChangeListener*  l, QString  name, const QString  listenerRef) { NamedBean::addPropertyChangeListener(l, name, listenerRef); }
inline int  py_q_compareSystemNameSuffix(QString  suffix1, QString  suffix2, NamedBean*  n2) { return NamedBean::compareSystemNameSuffix(suffix1, suffix2, n2); }
inline int  py_q_compareTo(NamedBean*  n2) { return NamedBean::compareTo(n2); }
inline QString  py_q_describeState(int  arg__1) { return NamedBean::describeState(arg__1); }
inline void py_q_dispose() { NamedBean::dispose(); }
inline bool  py_q_equals(QObject*  obj) { return NamedBean::equals(obj); }
inline QString  py_q_getBeanType() { return NamedBean::getBeanType(); }
inline QString  py_q_getComment() { return NamedBean::getComment(); }
inline QString  py_q_getDisplayName() { return NamedBean::getDisplayName(); }
inline QString  py_q_getFullyFormattedDisplayName() { return NamedBean::getFullyFormattedDisplayName(); }
inline QString  py_q_getListenerRef(PropertyChangeListener*  l) { return NamedBean::getListenerRef(l); }
inline QList<QString >*  py_q_getListenerRefs() { return NamedBean::getListenerRefs(); }
inline int  py_q_getNumPropertyChangeListeners() { return NamedBean::getNumPropertyChangeListeners(); }
inline QVariant  py_q_getProperty(QString  key) { return NamedBean::getProperty(key); }
inline QList<PropertyChangeListener* >*  py_q_getPropertyChangeListeners(QString  name) { return NamedBean::getPropertyChangeListeners(name); }
inline QSet<QString >  py_q_getPropertyKeys() { return NamedBean::getPropertyKeys(); }
inline int  py_q_getState() { return NamedBean::getState(); }
inline QString  py_q_getSystemName() { return NamedBean::getSystemName(); }
inline QString  py_q_getUserName() { return NamedBean::getUserName(); }
inline bool  py_q_hashCode() { return NamedBean::hashCode(); }
inline void py_q_removeProperty(QString  arg__1) { NamedBean::removeProperty(arg__1); }
inline void py_q_removePropertyChangeListener(PropertyChangeListener*  l) { NamedBean::removePropertyChangeListener(l); }
inline void py_q_setComment(QString  comment) { NamedBean::setComment(comment); }
inline void py_q_setProperty(QString  key, QVariant  value) { NamedBean::setProperty(key, value); }
inline void py_q_setState(int  arg__1) { NamedBean::setState(arg__1); }
inline void py_q_setUserName(QString  s) { NamedBean::setUserName(s); }
inline void py_q_updateListenerRef(PropertyChangeListener*  l, QString  newName) { NamedBean::updateListenerRef(l, newName); }
inline void py_q_vetoableChange(PropertyChangeEvent*  arg__1) { NamedBean::vetoableChange(arg__1); }
};

class PythonQtWrapper_NamedBean : public QObject
{ Q_OBJECT
public:
public slots:
NamedBean* new_NamedBean(QObject*  parent = 0);
NamedBean* new_NamedBean(QString  name, QObject*  parent = 0);
NamedBean* new_NamedBean(const NamedBean&  arg__1);
void delete_NamedBean(NamedBean* obj) { delete obj; } 
   void addPropertyChangeListener(NamedBean* theWrappedObject, PropertyChangeListener*  l);
   void py_q_addPropertyChangeListener(NamedBean* theWrappedObject, PropertyChangeListener*  l){  (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_addPropertyChangeListener(l));}
   void addPropertyChangeListener(NamedBean* theWrappedObject, PropertyChangeListener*  l, QString  name, const QString  listenerRef);
   void py_q_addPropertyChangeListener(NamedBean* theWrappedObject, PropertyChangeListener*  l, QString  name, const QString  listenerRef){  (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_addPropertyChangeListener(l, name, listenerRef));}
   int  compareSystemNameSuffix(NamedBean* theWrappedObject, QString  suffix1, QString  suffix2, NamedBean*  n2);
   int  py_q_compareSystemNameSuffix(NamedBean* theWrappedObject, QString  suffix1, QString  suffix2, NamedBean*  n2){  return (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_compareSystemNameSuffix(suffix1, suffix2, n2));}
   int  compareTo(NamedBean* theWrappedObject, NamedBean*  n2);
   int  py_q_compareTo(NamedBean* theWrappedObject, NamedBean*  n2){  return (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_compareTo(n2));}
   QString  describeState(NamedBean* theWrappedObject, int  arg__1);
   QString  py_q_describeState(NamedBean* theWrappedObject, int  arg__1){  return (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_describeState(arg__1));}
   void dispose(NamedBean* theWrappedObject);
   void py_q_dispose(NamedBean* theWrappedObject){  (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_dispose());}
   bool  equals(NamedBean* theWrappedObject, QObject*  obj);
   bool  py_q_equals(NamedBean* theWrappedObject, QObject*  obj){  return (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_equals(obj));}
   QString  getBeanType(NamedBean* theWrappedObject);
   QString  py_q_getBeanType(NamedBean* theWrappedObject){  return (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_getBeanType());}
   QString  getComment(NamedBean* theWrappedObject);
   QString  py_q_getComment(NamedBean* theWrappedObject){  return (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_getComment());}
   QString  getDisplayName(NamedBean* theWrappedObject);
   QString  py_q_getDisplayName(NamedBean* theWrappedObject){  return (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_getDisplayName());}
   QString  getFullyFormattedDisplayName(NamedBean* theWrappedObject);
   QString  py_q_getFullyFormattedDisplayName(NamedBean* theWrappedObject){  return (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_getFullyFormattedDisplayName());}
   QString  getListenerRef(NamedBean* theWrappedObject, PropertyChangeListener*  l);
   QString  py_q_getListenerRef(NamedBean* theWrappedObject, PropertyChangeListener*  l){  return (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_getListenerRef(l));}
   QList<QString >*  getListenerRefs(NamedBean* theWrappedObject);
   QList<QString >*  py_q_getListenerRefs(NamedBean* theWrappedObject){  return (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_getListenerRefs());}
   int  getNumPropertyChangeListeners(NamedBean* theWrappedObject);
   int  py_q_getNumPropertyChangeListeners(NamedBean* theWrappedObject){  return (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_getNumPropertyChangeListeners());}
   QVariant  getProperty(NamedBean* theWrappedObject, QString  key);
   QVariant  py_q_getProperty(NamedBean* theWrappedObject, QString  key){  return (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_getProperty(key));}
   QList<PropertyChangeListener* >*  getPropertyChangeListeners(NamedBean* theWrappedObject, QString  name);
   QList<PropertyChangeListener* >*  py_q_getPropertyChangeListeners(NamedBean* theWrappedObject, QString  name){  return (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_getPropertyChangeListeners(name));}
   QSet<QString >  getPropertyKeys(NamedBean* theWrappedObject);
   QSet<QString >  py_q_getPropertyKeys(NamedBean* theWrappedObject){  return (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_getPropertyKeys());}
   int  getState(NamedBean* theWrappedObject);
   int  py_q_getState(NamedBean* theWrappedObject){  return (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_getState());}
   QString  getSystemName(NamedBean* theWrappedObject);
   QString  py_q_getSystemName(NamedBean* theWrappedObject){  return (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_getSystemName());}
   QString  getUserName(NamedBean* theWrappedObject);
   QString  py_q_getUserName(NamedBean* theWrappedObject){  return (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_getUserName());}
   bool  hashCode(NamedBean* theWrappedObject);
   bool  py_q_hashCode(NamedBean* theWrappedObject){  return (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_hashCode());}
   QString  static_NamedBean_normalizeUserName(QString  arg__1);
   void removeProperty(NamedBean* theWrappedObject, QString  arg__1);
   void py_q_removeProperty(NamedBean* theWrappedObject, QString  arg__1){  (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_removeProperty(arg__1));}
   void removePropertyChangeListener(NamedBean* theWrappedObject, PropertyChangeListener*  l);
   void py_q_removePropertyChangeListener(NamedBean* theWrappedObject, PropertyChangeListener*  l){  (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_removePropertyChangeListener(l));}
   void setComment(NamedBean* theWrappedObject, QString  comment);
   void py_q_setComment(NamedBean* theWrappedObject, QString  comment){  (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_setComment(comment));}
   void setProperty(NamedBean* theWrappedObject, QString  key, QVariant  value);
   void py_q_setProperty(NamedBean* theWrappedObject, QString  key, QVariant  value){  (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_setProperty(key, value));}
   void setState(NamedBean* theWrappedObject, int  arg__1);
   void py_q_setState(NamedBean* theWrappedObject, int  arg__1){  (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_setState(arg__1));}
   void setUserName(NamedBean* theWrappedObject, QString  s);
   void py_q_setUserName(NamedBean* theWrappedObject, QString  s){  (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_setUserName(s));}
   void updateListenerRef(NamedBean* theWrappedObject, PropertyChangeListener*  l, QString  newName);
   void py_q_updateListenerRef(NamedBean* theWrappedObject, PropertyChangeListener*  l, QString  newName){  (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_updateListenerRef(l, newName));}
   void vetoableChange(NamedBean* theWrappedObject, PropertyChangeEvent*  arg__1);
   void py_q_vetoableChange(NamedBean* theWrappedObject, PropertyChangeEvent*  arg__1){  (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_vetoableChange(arg__1));}
};





class PythonQtShell_NetworkPortAdapter : public NetworkPortAdapter
{
public:
    PythonQtShell_NetworkPortAdapter(QObject*  parent = 0):NetworkPortAdapter(parent),_wrapper(NULL) {}

   ~PythonQtShell_NetworkPortAdapter();

virtual void _connect(QString  arg__1, int  arg__2);
virtual void autoConfigure();
virtual void childEvent(QChildEvent*  event);
virtual void configure();
virtual void configureOption1(QString  arg__1);
virtual void configureOption2(QString  arg__1);
virtual void configureOption3(QString  arg__1);
virtual void configureOption4(QString  arg__1);
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
virtual QStringList  getOptionChoices(QString  arg__1);
virtual QString  getOptionDisplayName(QString  arg__1);
virtual QString  getOptionState(QString  arg__1);
virtual QStringList  getOptions();
virtual QDataStream*  getOutputStream();
virtual int  getPort();
virtual QString  getServiceType();
virtual SystemConnectionMemo*  getSystemConnectionMemo();
virtual QString  getSystemPrefix();
virtual QString  getUserName();
virtual bool  isDirty();
virtual bool  isOptionAdvanced(QString  arg__1);
virtual bool  isRestartRequired();
virtual void recover();
virtual void setAdvertisementName(QString  arg__1);
virtual void setDisabled(bool  arg__1);
virtual void setHostName(QString  arg__1);
virtual void setManufacturer(QString  arg__1);
virtual void setMdnsConfigure(bool  arg__1);
virtual void setOptionState(QString  arg__1, QString  arg__2);
virtual void setPort(QString  arg__1);
virtual void setPort(int  arg__1);
virtual void setServiceType(QString  arg__1);
virtual void setSystemConnectionMemo(SystemConnectionMemo*  arg__1);
virtual void setSystemPrefix(QString  arg__1);
virtual void setUserName(QString  arg__1);
virtual bool  status();
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_NetworkPortAdapter : public NetworkPortAdapter
{ public:
inline void py_q__connect(QString  arg__1, int  arg__2) { NetworkPortAdapter::_connect(arg__1, arg__2); }
inline void py_q_autoConfigure() { NetworkPortAdapter::autoConfigure(); }
inline void py_q_configure() { NetworkPortAdapter::configure(); }
inline QString  py_q_getAdvertisementName() { return NetworkPortAdapter::getAdvertisementName(); }
inline QString  py_q_getCurrentPortName() { return NetworkPortAdapter::getCurrentPortName(); }
inline QString  py_q_getHostName() { return NetworkPortAdapter::getHostName(); }
inline bool  py_q_getMdnsConfigure() { return NetworkPortAdapter::getMdnsConfigure(); }
inline int  py_q_getPort() { return NetworkPortAdapter::getPort(); }
inline QString  py_q_getServiceType() { return NetworkPortAdapter::getServiceType(); }
inline void py_q_setAdvertisementName(QString  arg__1) { NetworkPortAdapter::setAdvertisementName(arg__1); }
inline void py_q_setHostName(QString  arg__1) { NetworkPortAdapter::setHostName(arg__1); }
inline void py_q_setMdnsConfigure(bool  arg__1) { NetworkPortAdapter::setMdnsConfigure(arg__1); }
inline void py_q_setPort(QString  arg__1) { NetworkPortAdapter::setPort(arg__1); }
inline void py_q_setPort(int  arg__1) { NetworkPortAdapter::setPort(arg__1); }
inline void py_q_setServiceType(QString  arg__1) { NetworkPortAdapter::setServiceType(arg__1); }
inline bool  py_q_status() { return NetworkPortAdapter::status(); }
};

class PythonQtWrapper_NetworkPortAdapter : public QObject
{ Q_OBJECT
public:
public slots:
NetworkPortAdapter* new_NetworkPortAdapter(QObject*  parent = 0);
void delete_NetworkPortAdapter(NetworkPortAdapter* obj) { delete obj; } 
   void _connect(NetworkPortAdapter* theWrappedObject, QString  arg__1, int  arg__2);
   void py_q__connect(NetworkPortAdapter* theWrappedObject, QString  arg__1, int  arg__2){  (((PythonQtPublicPromoter_NetworkPortAdapter*)theWrappedObject)->py_q__connect(arg__1, arg__2));}
   void autoConfigure(NetworkPortAdapter* theWrappedObject);
   void py_q_autoConfigure(NetworkPortAdapter* theWrappedObject){  (((PythonQtPublicPromoter_NetworkPortAdapter*)theWrappedObject)->py_q_autoConfigure());}
   void py_q_configure(NetworkPortAdapter* theWrappedObject){  (((PythonQtPublicPromoter_NetworkPortAdapter*)theWrappedObject)->py_q_configure());}
   QString  getAdvertisementName(NetworkPortAdapter* theWrappedObject);
   QString  py_q_getAdvertisementName(NetworkPortAdapter* theWrappedObject){  return (((PythonQtPublicPromoter_NetworkPortAdapter*)theWrappedObject)->py_q_getAdvertisementName());}
   QString  py_q_getCurrentPortName(NetworkPortAdapter* theWrappedObject){  return (((PythonQtPublicPromoter_NetworkPortAdapter*)theWrappedObject)->py_q_getCurrentPortName());}
   QString  getHostName(NetworkPortAdapter* theWrappedObject);
   QString  py_q_getHostName(NetworkPortAdapter* theWrappedObject){  return (((PythonQtPublicPromoter_NetworkPortAdapter*)theWrappedObject)->py_q_getHostName());}
   bool  getMdnsConfigure(NetworkPortAdapter* theWrappedObject);
   bool  py_q_getMdnsConfigure(NetworkPortAdapter* theWrappedObject){  return (((PythonQtPublicPromoter_NetworkPortAdapter*)theWrappedObject)->py_q_getMdnsConfigure());}
   int  getPort(NetworkPortAdapter* theWrappedObject);
   int  py_q_getPort(NetworkPortAdapter* theWrappedObject){  return (((PythonQtPublicPromoter_NetworkPortAdapter*)theWrappedObject)->py_q_getPort());}
   QString  getServiceType(NetworkPortAdapter* theWrappedObject);
   QString  py_q_getServiceType(NetworkPortAdapter* theWrappedObject){  return (((PythonQtPublicPromoter_NetworkPortAdapter*)theWrappedObject)->py_q_getServiceType());}
   void setAdvertisementName(NetworkPortAdapter* theWrappedObject, QString  arg__1);
   void py_q_setAdvertisementName(NetworkPortAdapter* theWrappedObject, QString  arg__1){  (((PythonQtPublicPromoter_NetworkPortAdapter*)theWrappedObject)->py_q_setAdvertisementName(arg__1));}
   void setHostName(NetworkPortAdapter* theWrappedObject, QString  arg__1);
   void py_q_setHostName(NetworkPortAdapter* theWrappedObject, QString  arg__1){  (((PythonQtPublicPromoter_NetworkPortAdapter*)theWrappedObject)->py_q_setHostName(arg__1));}
   void setMdnsConfigure(NetworkPortAdapter* theWrappedObject, bool  arg__1);
   void py_q_setMdnsConfigure(NetworkPortAdapter* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_NetworkPortAdapter*)theWrappedObject)->py_q_setMdnsConfigure(arg__1));}
   void setPort(NetworkPortAdapter* theWrappedObject, QString  arg__1);
   void py_q_setPort(NetworkPortAdapter* theWrappedObject, QString  arg__1){  (((PythonQtPublicPromoter_NetworkPortAdapter*)theWrappedObject)->py_q_setPort(arg__1));}
   void setPort(NetworkPortAdapter* theWrappedObject, int  arg__1);
   void py_q_setPort(NetworkPortAdapter* theWrappedObject, int  arg__1){  (((PythonQtPublicPromoter_NetworkPortAdapter*)theWrappedObject)->py_q_setPort(arg__1));}
   void setServiceType(NetworkPortAdapter* theWrappedObject, QString  arg__1);
   void py_q_setServiceType(NetworkPortAdapter* theWrappedObject, QString  arg__1){  (((PythonQtPublicPromoter_NetworkPortAdapter*)theWrappedObject)->py_q_setServiceType(arg__1));}
   bool  py_q_status(NetworkPortAdapter* theWrappedObject){  return (((PythonQtPublicPromoter_NetworkPortAdapter*)theWrappedObject)->py_q_status());}
};





class PythonQtShell_PanelEditor : public PanelEditor
{
public:
    PythonQtShell_PanelEditor(QString  name, QWidget*  parent = nullptr):PanelEditor(name, parent),_wrapper(NULL) {}
    PythonQtShell_PanelEditor(QWidget*  parent = nullptr):PanelEditor(parent),_wrapper(NULL) {}
    PythonQtShell_PanelEditor(const PanelEditor&  arg__1):PanelEditor(arg__1),_wrapper(NULL) {}

   ~PythonQtShell_PanelEditor();

virtual void actionEvent(QActionEvent*  event);
virtual void addHelpMenu(QString  ref, bool  direct);
virtual void changeEvent(QEvent*  arg__1);
virtual void childEvent(QChildEvent*  event);
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
virtual void init(QString  name);
virtual void initComponents();
virtual void initPainter(QPainter*  painter) const;
virtual void initView();
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
virtual void paint(QGraphicsScene*  g);
virtual QPaintEngine*  paintEngine() const;
virtual void paintEvent(QPaintEvent*  event);
virtual void paintTargetPanel(QGraphicsScene*  g);
virtual void putItem(Positionable*  l);
virtual QPaintDevice*  redirected(QPoint*  offset) const;
virtual void repaint();
virtual void resizeEvent(QResizeEvent*  e);
virtual void setAllEditable(bool  state);
virtual void setNextLocation(Positionable*  obj);
virtual void setRemoveMenu(Positionable*  p, QMenu*  popup);
virtual void setScroll(int  state);
virtual void setTitle();
virtual void setUseGlobalFlag(bool  set);
virtual void setVisible(bool  visible);
virtual QPainter*  sharedPainter() const;
virtual void showEvent(QShowEvent*  event);
virtual void showPopUp(Positionable*  p, QGraphicsSceneMouseEvent*  event);
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

class PythonQtPublicPromoter_PanelEditor : public PanelEditor
{ public:
inline void promoted_addColorMenuEntry(QMenu*  menu, QActionGroup*  colorButtonGroup, QString  name, QColor  color) { this->addColorMenuEntry(menu, colorButtonGroup, name, color); }
inline void promoted_backgroundPopUp(QGraphicsSceneMouseEvent*  event) { this->backgroundPopUp(event); }
inline void promoted_copyItem(Positionable*  p) { this->copyItem(p); }
inline void promoted_init(QString  name) { this->init(name); }
inline void promoted_makeColorMenu(QMenu*  colorMenu) { this->makeColorMenu(colorMenu); }
inline void promoted_pasteItem(QGraphicsSceneMouseEvent*  e) { this->pasteItem(e); }
inline void promoted_pasteItemPopUp(QGraphicsSceneMouseEvent*  event) { this->pasteItemPopUp(event); }
inline void promoted_repaint() { this->repaint(); }
inline void promoted_setNextLocation(Positionable*  obj) { this->setNextLocation(obj); }
inline void promoted_showAddItemPopUp(QGraphicsSceneMouseEvent*  event, QMenu*  popup) { this->showAddItemPopUp(event, popup); }
inline void promoted_showMultiSelectPopUp(QGraphicsSceneMouseEvent*  event, Positionable*  p) { this->showMultiSelectPopUp(event, p); }
inline void promoted_showPopUp(Positionable*  p, QGraphicsSceneMouseEvent*  event) { this->showPopUp(p, event); }
inline void py_q_init(QString  name) { PanelEditor::init(name); }
inline void py_q_initView() { PanelEditor::initView(); }
inline void py_q_putItem(Positionable*  l) { PanelEditor::putItem(l); }
inline void py_q_repaint() { PanelEditor::repaint(); }
inline void py_q_setNextLocation(Positionable*  obj) { PanelEditor::setNextLocation(obj); }
inline void py_q_setRemoveMenu(Positionable*  p, QMenu*  popup) { PanelEditor::setRemoveMenu(p, popup); }
inline void py_q_showPopUp(Positionable*  p, QGraphicsSceneMouseEvent*  event) { PanelEditor::showPopUp(p, event); }
inline void py_q_windowClosing(QCloseEvent*  e) { PanelEditor::windowClosing(e); }
};

class PythonQtWrapper_PanelEditor : public QObject
{ Q_OBJECT
public:
public slots:
PanelEditor* new_PanelEditor(QString  name, QWidget*  parent = nullptr);
PanelEditor* new_PanelEditor(QWidget*  parent = nullptr);
PanelEditor* new_PanelEditor(const PanelEditor&  arg__1);
void delete_PanelEditor(PanelEditor* obj) { delete obj; } 
   void addColorMenuEntry(PanelEditor* theWrappedObject, QMenu*  menu, QActionGroup*  colorButtonGroup, QString  name, QColor  color);
   void backgroundPopUp(PanelEditor* theWrappedObject, QGraphicsSceneMouseEvent*  event);
   void copyItem(PanelEditor* theWrappedObject, Positionable*  p);
   void py_q_init(PanelEditor* theWrappedObject, QString  name){  (((PythonQtPublicPromoter_PanelEditor*)theWrappedObject)->py_q_init(name));}
   void py_q_initView(PanelEditor* theWrappedObject){  (((PythonQtPublicPromoter_PanelEditor*)theWrappedObject)->py_q_initView());}
   void makeColorMenu(PanelEditor* theWrappedObject, QMenu*  colorMenu);
   void pasteItem(PanelEditor* theWrappedObject, QGraphicsSceneMouseEvent*  e);
   void pasteItemPopUp(PanelEditor* theWrappedObject, QGraphicsSceneMouseEvent*  event);
   void py_q_putItem(PanelEditor* theWrappedObject, Positionable*  l){  (((PythonQtPublicPromoter_PanelEditor*)theWrappedObject)->py_q_putItem(l));}
   void py_q_repaint(PanelEditor* theWrappedObject){  (((PythonQtPublicPromoter_PanelEditor*)theWrappedObject)->py_q_repaint());}
   void py_q_setNextLocation(PanelEditor* theWrappedObject, Positionable*  obj){  (((PythonQtPublicPromoter_PanelEditor*)theWrappedObject)->py_q_setNextLocation(obj));}
   void py_q_setRemoveMenu(PanelEditor* theWrappedObject, Positionable*  p, QMenu*  popup){  (((PythonQtPublicPromoter_PanelEditor*)theWrappedObject)->py_q_setRemoveMenu(p, popup));}
   void showAddItemPopUp(PanelEditor* theWrappedObject, QGraphicsSceneMouseEvent*  event, QMenu*  popup);
   void showMultiSelectPopUp(PanelEditor* theWrappedObject, QGraphicsSceneMouseEvent*  event, Positionable*  p);
   void py_q_showPopUp(PanelEditor* theWrappedObject, Positionable*  p, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_PanelEditor*)theWrappedObject)->py_q_showPopUp(p, event));}
   void py_q_windowClosing(PanelEditor* theWrappedObject, QCloseEvent*  e){  (((PythonQtPublicPromoter_PanelEditor*)theWrappedObject)->py_q_windowClosing(e));}
void py_set__debug(PanelEditor* theWrappedObject, bool  _debug){ theWrappedObject->_debug = _debug; }
bool  py_get__debug(PanelEditor* theWrappedObject){ return theWrappedObject->_debug; }
};





class PythonQtShell_PanelMenu : public PanelMenu
{
public:
    PythonQtShell_PanelMenu(QWidget*  parent = nullptr):PanelMenu(parent),_wrapper(NULL) {}

   ~PythonQtShell_PanelMenu();

virtual void actionEvent(QActionEvent*  arg__1);
virtual void changeEvent(QEvent*  arg__1);
virtual void childEvent(QChildEvent*  event);
virtual void closeEvent(QCloseEvent*  event);
virtual void contextMenuEvent(QContextMenuEvent*  event);
virtual void customEvent(QEvent*  event);
virtual int  devType() const;
virtual void dragEnterEvent(QDragEnterEvent*  event);
virtual void dragLeaveEvent(QDragLeaveEvent*  event);
virtual void dragMoveEvent(QDragMoveEvent*  event);
virtual void dropEvent(QDropEvent*  event);
virtual void enterEvent(QEvent*  arg__1);
virtual bool  event(QEvent*  arg__1);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual void focusInEvent(QFocusEvent*  event);
virtual bool  focusNextPrevChild(bool  next);
virtual void focusOutEvent(QFocusEvent*  event);
virtual bool  hasHeightForWidth() const;
virtual int  heightForWidth(int  arg__1) const;
virtual void hideEvent(QHideEvent*  arg__1);
virtual void initPainter(QPainter*  painter) const;
virtual void inputMethodEvent(QInputMethodEvent*  arg__1);
virtual QVariant  inputMethodQuery(Qt::InputMethodQuery  arg__1) const;
virtual void keyPressEvent(QKeyEvent*  arg__1);
virtual void keyReleaseEvent(QKeyEvent*  event);
virtual void leaveEvent(QEvent*  arg__1);
virtual int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
virtual QSize  minimumSizeHint() const;
virtual void mouseDoubleClickEvent(QMouseEvent*  event);
virtual void mouseMoveEvent(QMouseEvent*  arg__1);
virtual void mousePressEvent(QMouseEvent*  arg__1);
virtual void mouseReleaseEvent(QMouseEvent*  arg__1);
virtual void moveEvent(QMoveEvent*  event);
virtual bool  nativeEvent(const QByteArray&  eventType, void*  message, long*  result);
virtual QPaintEngine*  paintEngine() const;
virtual void paintEvent(QPaintEvent*  arg__1);
virtual QPaintDevice*  redirected(QPoint*  offset) const;
virtual void resizeEvent(QResizeEvent*  event);
virtual void setVisible(bool  visible);
virtual QPainter*  sharedPainter() const;
virtual void showEvent(QShowEvent*  event);
virtual QSize  sizeHint() const;
virtual void tabletEvent(QTabletEvent*  event);
virtual void timerEvent(QTimerEvent*  arg__1);
virtual void wheelEvent(QWheelEvent*  arg__1);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtWrapper_PanelMenu : public QObject
{ Q_OBJECT
public:
public slots:
PanelMenu* new_PanelMenu(QWidget*  parent = nullptr);
void delete_PanelMenu(PanelMenu* obj) { delete obj; } 
   void addEditorPanel(PanelMenu* theWrappedObject, Editor*  panel);
   void deletePanel(PanelMenu* theWrappedObject, Editor*  panel);
   Editor*  getEditorByName(PanelMenu* theWrappedObject, QString  name);
   QList<Editor* >*  getEditorPanelList(PanelMenu* theWrappedObject);
   QList<LayoutEditor* >*  getLayoutEditorPanelList(PanelMenu* theWrappedObject);
   int  getNumberOfPanels(PanelMenu* theWrappedObject);
   PanelMenu*  static_PanelMenu_instance();
   bool  isPanelNameUsed(PanelMenu* theWrappedObject, QString  name);
   void renameEditorPanel(PanelMenu* theWrappedObject, Editor*  panel);
   void updateEditorPanel(PanelMenu* theWrappedObject, Editor*  panel);
    bool __nonzero__(PanelMenu* obj) { return !obj->isEmpty(); }
};





class PythonQtShell_PortAdapter : public PortAdapter
{
public:
    PythonQtShell_PortAdapter(QObject*  parent = 0):PortAdapter(parent),_wrapper(NULL) {}

   ~PythonQtShell_PortAdapter();

virtual void _connect();
virtual void childEvent(QChildEvent*  event);
virtual void configure();
virtual void configureOption1(QString  arg__1);
virtual void configureOption2(QString  arg__1);
virtual void configureOption3(QString  arg__1);
virtual void configureOption4(QString  arg__1);
virtual void customEvent(QEvent*  event);
virtual void dispose();
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual QString  getCurrentPortName();
virtual bool  getDisabled();
virtual QDataStream*  getInputStream();
virtual QString  getManufacturer();
virtual QString  getOption1Name();
virtual QString  getOption2Name();
virtual QString  getOption3Name();
virtual QString  getOption4Name();
virtual QStringList  getOptionChoices(QString  arg__1);
virtual QString  getOptionDisplayName(QString  arg__1);
virtual QString  getOptionState(QString  arg__1);
virtual QStringList  getOptions();
virtual QDataStream*  getOutputStream();
virtual SystemConnectionMemo*  getSystemConnectionMemo();
virtual QString  getSystemPrefix();
virtual QString  getUserName();
virtual bool  isDirty();
virtual bool  isOptionAdvanced(QString  arg__1);
virtual bool  isRestartRequired();
virtual void recover();
virtual void setDisabled(bool  arg__1);
virtual void setManufacturer(QString  arg__1);
virtual void setOptionState(QString  arg__1, QString  arg__2);
virtual void setSystemConnectionMemo(SystemConnectionMemo*  arg__1);
virtual void setSystemPrefix(QString  arg__1);
virtual void setUserName(QString  arg__1);
virtual bool  status();
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_PortAdapter : public PortAdapter
{ public:
inline void py_q__connect() { PortAdapter::_connect(); }
inline void py_q_configure() { PortAdapter::configure(); }
inline void py_q_configureOption1(QString  arg__1) { PortAdapter::configureOption1(arg__1); }
inline void py_q_configureOption2(QString  arg__1) { PortAdapter::configureOption2(arg__1); }
inline void py_q_configureOption3(QString  arg__1) { PortAdapter::configureOption3(arg__1); }
inline void py_q_configureOption4(QString  arg__1) { PortAdapter::configureOption4(arg__1); }
inline void py_q_dispose() { PortAdapter::dispose(); }
inline QString  py_q_getCurrentPortName() { return PortAdapter::getCurrentPortName(); }
inline bool  py_q_getDisabled() { return PortAdapter::getDisabled(); }
inline QDataStream*  py_q_getInputStream() { return PortAdapter::getInputStream(); }
inline QString  py_q_getManufacturer() { return PortAdapter::getManufacturer(); }
inline QString  py_q_getOption1Name() { return PortAdapter::getOption1Name(); }
inline QString  py_q_getOption2Name() { return PortAdapter::getOption2Name(); }
inline QString  py_q_getOption3Name() { return PortAdapter::getOption3Name(); }
inline QString  py_q_getOption4Name() { return PortAdapter::getOption4Name(); }
inline QStringList  py_q_getOptionChoices(QString  arg__1) { return PortAdapter::getOptionChoices(arg__1); }
inline QString  py_q_getOptionDisplayName(QString  arg__1) { return PortAdapter::getOptionDisplayName(arg__1); }
inline QString  py_q_getOptionState(QString  arg__1) { return PortAdapter::getOptionState(arg__1); }
inline QStringList  py_q_getOptions() { return PortAdapter::getOptions(); }
inline QDataStream*  py_q_getOutputStream() { return PortAdapter::getOutputStream(); }
inline SystemConnectionMemo*  py_q_getSystemConnectionMemo() { return PortAdapter::getSystemConnectionMemo(); }
inline QString  py_q_getSystemPrefix() { return PortAdapter::getSystemPrefix(); }
inline QString  py_q_getUserName() { return PortAdapter::getUserName(); }
inline bool  py_q_isDirty() { return PortAdapter::isDirty(); }
inline bool  py_q_isOptionAdvanced(QString  arg__1) { return PortAdapter::isOptionAdvanced(arg__1); }
inline bool  py_q_isRestartRequired() { return PortAdapter::isRestartRequired(); }
inline void py_q_recover() { PortAdapter::recover(); }
inline void py_q_setDisabled(bool  arg__1) { PortAdapter::setDisabled(arg__1); }
inline void py_q_setManufacturer(QString  arg__1) { PortAdapter::setManufacturer(arg__1); }
inline void py_q_setOptionState(QString  arg__1, QString  arg__2) { PortAdapter::setOptionState(arg__1, arg__2); }
inline void py_q_setSystemConnectionMemo(SystemConnectionMemo*  arg__1) { PortAdapter::setSystemConnectionMemo(arg__1); }
inline void py_q_setSystemPrefix(QString  arg__1) { PortAdapter::setSystemPrefix(arg__1); }
inline void py_q_setUserName(QString  arg__1) { PortAdapter::setUserName(arg__1); }
inline bool  py_q_status() { return PortAdapter::status(); }
};

class PythonQtWrapper_PortAdapter : public QObject
{ Q_OBJECT
public:
public slots:
PortAdapter* new_PortAdapter(QObject*  parent = 0);
void delete_PortAdapter(PortAdapter* obj) { delete obj; } 
   void _connect(PortAdapter* theWrappedObject);
   void py_q__connect(PortAdapter* theWrappedObject){  (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q__connect());}
   void configure(PortAdapter* theWrappedObject);
   void py_q_configure(PortAdapter* theWrappedObject){  (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_configure());}
   void configureOption1(PortAdapter* theWrappedObject, QString  arg__1);
   void py_q_configureOption1(PortAdapter* theWrappedObject, QString  arg__1){  (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_configureOption1(arg__1));}
   void configureOption2(PortAdapter* theWrappedObject, QString  arg__1);
   void py_q_configureOption2(PortAdapter* theWrappedObject, QString  arg__1){  (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_configureOption2(arg__1));}
   void configureOption3(PortAdapter* theWrappedObject, QString  arg__1);
   void py_q_configureOption3(PortAdapter* theWrappedObject, QString  arg__1){  (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_configureOption3(arg__1));}
   void configureOption4(PortAdapter* theWrappedObject, QString  arg__1);
   void py_q_configureOption4(PortAdapter* theWrappedObject, QString  arg__1){  (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_configureOption4(arg__1));}
   void dispose(PortAdapter* theWrappedObject);
   void py_q_dispose(PortAdapter* theWrappedObject){  (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_dispose());}
   QString  getCurrentPortName(PortAdapter* theWrappedObject);
   QString  py_q_getCurrentPortName(PortAdapter* theWrappedObject){  return (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_getCurrentPortName());}
   bool  getDisabled(PortAdapter* theWrappedObject);
   bool  py_q_getDisabled(PortAdapter* theWrappedObject){  return (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_getDisabled());}
   QDataStream*  getInputStream(PortAdapter* theWrappedObject);
   QDataStream*  py_q_getInputStream(PortAdapter* theWrappedObject){  return (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_getInputStream());}
   QString  getManufacturer(PortAdapter* theWrappedObject);
   QString  py_q_getManufacturer(PortAdapter* theWrappedObject){  return (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_getManufacturer());}
   QString  getOption1Name(PortAdapter* theWrappedObject);
   QString  py_q_getOption1Name(PortAdapter* theWrappedObject){  return (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_getOption1Name());}
   QString  getOption2Name(PortAdapter* theWrappedObject);
   QString  py_q_getOption2Name(PortAdapter* theWrappedObject){  return (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_getOption2Name());}
   QString  getOption3Name(PortAdapter* theWrappedObject);
   QString  py_q_getOption3Name(PortAdapter* theWrappedObject){  return (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_getOption3Name());}
   QString  getOption4Name(PortAdapter* theWrappedObject);
   QString  py_q_getOption4Name(PortAdapter* theWrappedObject){  return (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_getOption4Name());}
   QStringList  getOptionChoices(PortAdapter* theWrappedObject, QString  arg__1);
   QStringList  py_q_getOptionChoices(PortAdapter* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_getOptionChoices(arg__1));}
   QString  getOptionDisplayName(PortAdapter* theWrappedObject, QString  arg__1);
   QString  py_q_getOptionDisplayName(PortAdapter* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_getOptionDisplayName(arg__1));}
   QString  getOptionState(PortAdapter* theWrappedObject, QString  arg__1);
   QString  py_q_getOptionState(PortAdapter* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_getOptionState(arg__1));}
   QStringList  getOptions(PortAdapter* theWrappedObject);
   QStringList  py_q_getOptions(PortAdapter* theWrappedObject){  return (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_getOptions());}
   QDataStream*  getOutputStream(PortAdapter* theWrappedObject);
   QDataStream*  py_q_getOutputStream(PortAdapter* theWrappedObject){  return (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_getOutputStream());}
   SystemConnectionMemo*  getSystemConnectionMemo(PortAdapter* theWrappedObject);
   SystemConnectionMemo*  py_q_getSystemConnectionMemo(PortAdapter* theWrappedObject){  return (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_getSystemConnectionMemo());}
   QString  getSystemPrefix(PortAdapter* theWrappedObject);
   QString  py_q_getSystemPrefix(PortAdapter* theWrappedObject){  return (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_getSystemPrefix());}
   QString  getUserName(PortAdapter* theWrappedObject);
   QString  py_q_getUserName(PortAdapter* theWrappedObject){  return (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_getUserName());}
   bool  isDirty(PortAdapter* theWrappedObject);
   bool  py_q_isDirty(PortAdapter* theWrappedObject){  return (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_isDirty());}
   bool  isOptionAdvanced(PortAdapter* theWrappedObject, QString  arg__1);
   bool  py_q_isOptionAdvanced(PortAdapter* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_isOptionAdvanced(arg__1));}
   bool  isRestartRequired(PortAdapter* theWrappedObject);
   bool  py_q_isRestartRequired(PortAdapter* theWrappedObject){  return (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_isRestartRequired());}
   void recover(PortAdapter* theWrappedObject);
   void py_q_recover(PortAdapter* theWrappedObject){  (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_recover());}
   void setDisabled(PortAdapter* theWrappedObject, bool  arg__1);
   void py_q_setDisabled(PortAdapter* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_setDisabled(arg__1));}
   void setManufacturer(PortAdapter* theWrappedObject, QString  arg__1);
   void py_q_setManufacturer(PortAdapter* theWrappedObject, QString  arg__1){  (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_setManufacturer(arg__1));}
   void setOptionState(PortAdapter* theWrappedObject, QString  arg__1, QString  arg__2);
   void py_q_setOptionState(PortAdapter* theWrappedObject, QString  arg__1, QString  arg__2){  (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_setOptionState(arg__1, arg__2));}
   void setSystemConnectionMemo(PortAdapter* theWrappedObject, SystemConnectionMemo*  arg__1);
   void py_q_setSystemConnectionMemo(PortAdapter* theWrappedObject, SystemConnectionMemo*  arg__1){  (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_setSystemConnectionMemo(arg__1));}
   void setSystemPrefix(PortAdapter* theWrappedObject, QString  arg__1);
   void py_q_setSystemPrefix(PortAdapter* theWrappedObject, QString  arg__1){  (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_setSystemPrefix(arg__1));}
   void setUserName(PortAdapter* theWrappedObject, QString  arg__1);
   void py_q_setUserName(PortAdapter* theWrappedObject, QString  arg__1){  (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_setUserName(arg__1));}
   bool  status(PortAdapter* theWrappedObject);
   bool  py_q_status(PortAdapter* theWrappedObject){  return (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_status());}
};





class PythonQtShell_Positionable : public Positionable
{
public:
    PythonQtShell_Positionable(QString  text, QWidget*  parent = 0):Positionable(text, parent),_wrapper(NULL) {}
    PythonQtShell_Positionable(QWidget*  parent = 0):Positionable(parent),_wrapper(NULL) {}

   ~PythonQtShell_Positionable();

virtual void actionEvent(QActionEvent*  event);
virtual void changeEvent(QEvent*  arg__1);
virtual void childEvent(QChildEvent*  event);
virtual void closeEvent(QCloseEvent*  event);
virtual bool  contains(int  arg__1, int  arg__2);
virtual void contextMenuEvent(QContextMenuEvent*  ev);
virtual void customEvent(QEvent*  event);
virtual Positionable*  deepClone();
virtual int  devType() const;
virtual void doMouseClicked(QGraphicsSceneMouseEvent*  arg__1);
virtual void doMouseDragged(QGraphicsSceneMouseEvent*  arg__1);
virtual void doMouseEntered(QGraphicsSceneMouseEvent*  arg__1);
virtual void doMouseExited(QGraphicsSceneMouseEvent*  arg__1);
virtual void doMouseMoved(QGraphicsSceneMouseEvent*  arg__1);
virtual void doMousePressed(QGraphicsSceneMouseEvent*  arg__1);
virtual void doMouseReleased(QGraphicsSceneMouseEvent*  arg__1);
virtual bool  doViemMenu();
virtual void dragEnterEvent(QDragEnterEvent*  event);
virtual void dragLeaveEvent(QDragLeaveEvent*  event);
virtual void dragMoveEvent(QDragMoveEvent*  event);
virtual void dropEvent(QDropEvent*  event);
virtual void enterEvent(QEvent*  event);
virtual bool  event(QEvent*  e);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual Positionable*  finishClone(Positionable*  arg__1);
virtual void focusInEvent(QFocusEvent*  ev);
virtual bool  focusNextPrevChild(bool  next);
virtual void focusOutEvent(QFocusEvent*  ev);
virtual QColor  getBackground();
virtual QRectF  getBounds(QRectF  arg__1);
virtual int  getDegrees();
virtual int  getDisplayLevel();
virtual Editor*  getEditor();
virtual QFont  getFont();
virtual QColor  getForeground();
virtual QString  getGroupName();
virtual int  getHeight();
virtual QPointF  getLocation();
virtual QString  getNameString();
virtual NamedBean*  getNamedBean();
virtual bool  getSaveOpaque();
virtual double  getScale();
virtual QString  getTooltip();
virtual bool  getViewCoordinates();
virtual int  getWidth();
virtual int  getX();
virtual int  getY();
virtual bool  hasHeightForWidth() const;
virtual int  heightForWidth(int  arg__1) const;
virtual void hideEvent(QHideEvent*  event);
virtual void initPainter(QPainter*  painter) const;
virtual void inputMethodEvent(QInputMethodEvent*  arg__1);
virtual QVariant  inputMethodQuery(Qt::InputMethodQuery  arg__1) const;
virtual void invalidate();
virtual bool  isControlling();
virtual bool  isEditable();
virtual bool  isHidden();
virtual bool  isOpaque();
virtual bool  isPositionable();
virtual bool  isVisible();
virtual void keyPressEvent(QKeyEvent*  ev);
virtual void keyReleaseEvent(QKeyEvent*  event);
virtual void languageChange();
virtual void leaveEvent(QEvent*  event);
virtual int  maxHeight();
virtual int  maxWidth();
virtual int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
virtual QSize  minimumSizeHint() const;
virtual void mouseDoubleClickEvent(QMouseEvent*  event);
virtual void mouseMoveEvent(QMouseEvent*  ev);
virtual void mousePressEvent(QMouseEvent*  ev);
virtual void mouseReleaseEvent(QMouseEvent*  ev);
virtual void moveEvent(QMoveEvent*  event);
virtual bool  nativeEvent(const QByteArray&  eventType, void*  message, long*  result);
virtual void paint(QGraphicsScene*  arg__1);
virtual QPaintEngine*  paintEngine() const;
virtual void paintEvent(QPaintEvent*  arg__1);
virtual QPaintDevice*  redirected(QPoint*  offset) const;
virtual void remove();
virtual bool  requestFocusInWindow();
virtual void resizeEvent(QResizeEvent*  event);
virtual void rotate(int  arg__1);
virtual void setBackground(QColor  arg__1);
virtual void setControlling(bool  arg__1);
virtual bool  setDisableControlMenu(QMenu*  arg__1);
virtual void setDisplayLevel(int  arg__1);
virtual bool  setEditIconMenu(QMenu*  arg__1);
virtual bool  setEditItemMenu(QMenu*  arg__1);
virtual void setEditable(bool  arg__1);
virtual void setEditor(Editor*  arg__1);
virtual void setForeground(QColor  arg__1);
virtual void setHidden(bool  arg__1);
virtual void setLevel(int  arg__1);
virtual void setLocation(QPointF  arg__1);
virtual void setLocation(int  arg__1, int  arg__2);
virtual void setOpaque(bool  arg__1);
virtual void setPositionable(bool  arg__1);
virtual bool  setRotateMenu(QMenu*  arg__1);
virtual bool  setRotateOrthogonalMenu(QMenu*  arg__1);
virtual void setScale(double  arg__1);
virtual bool  setScaleMenu(QMenu*  arg__1);
virtual void setShowTooltip(bool  arg__1);
virtual void setSize(int  arg__1, int  arg__2);
virtual bool  setTextEditMenu(QMenu*  arg__1);
virtual void setViewCoordinates(bool  arg__1);
virtual void setVisible(bool  b);
virtual QPainter*  sharedPainter() const;
virtual void showEvent(QShowEvent*  event);
virtual void showHidden();
virtual bool  showPopUp(QMenu*  arg__1);
virtual bool  showToolTip();
virtual QSize  sizeHint() const;
virtual bool  storeItem();
virtual void tabletEvent(QTabletEvent*  event);
virtual void timerEvent(QTimerEvent*  event);
virtual bool  updateScene();
virtual void updateSize();
virtual void wheelEvent(QWheelEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_Positionable : public Positionable
{ public:
inline bool  py_q_contains(int  arg__1, int  arg__2) { return Positionable::contains(arg__1, arg__2); }
inline Positionable*  py_q_deepClone() { return Positionable::deepClone(); }
inline void py_q_doMouseClicked(QGraphicsSceneMouseEvent*  arg__1) { Positionable::doMouseClicked(arg__1); }
inline void py_q_doMouseDragged(QGraphicsSceneMouseEvent*  arg__1) { Positionable::doMouseDragged(arg__1); }
inline void py_q_doMouseEntered(QGraphicsSceneMouseEvent*  arg__1) { Positionable::doMouseEntered(arg__1); }
inline void py_q_doMouseExited(QGraphicsSceneMouseEvent*  arg__1) { Positionable::doMouseExited(arg__1); }
inline void py_q_doMouseMoved(QGraphicsSceneMouseEvent*  arg__1) { Positionable::doMouseMoved(arg__1); }
inline void py_q_doMousePressed(QGraphicsSceneMouseEvent*  arg__1) { Positionable::doMousePressed(arg__1); }
inline void py_q_doMouseReleased(QGraphicsSceneMouseEvent*  arg__1) { Positionable::doMouseReleased(arg__1); }
inline bool  py_q_doViemMenu() { return Positionable::doViemMenu(); }
inline Positionable*  py_q_finishClone(Positionable*  arg__1) { return Positionable::finishClone(arg__1); }
inline QColor  py_q_getBackground() { return Positionable::getBackground(); }
inline QRectF  py_q_getBounds(QRectF  arg__1) { return Positionable::getBounds(arg__1); }
inline int  py_q_getDegrees() { return Positionable::getDegrees(); }
inline int  py_q_getDisplayLevel() { return Positionable::getDisplayLevel(); }
inline Editor*  py_q_getEditor() { return Positionable::getEditor(); }
inline QFont  py_q_getFont() { return Positionable::getFont(); }
inline QColor  py_q_getForeground() { return Positionable::getForeground(); }
inline QString  py_q_getGroupName() { return Positionable::getGroupName(); }
inline int  py_q_getHeight() { return Positionable::getHeight(); }
inline QPointF  py_q_getLocation() { return Positionable::getLocation(); }
inline QString  py_q_getNameString() { return Positionable::getNameString(); }
inline NamedBean*  py_q_getNamedBean() { return Positionable::getNamedBean(); }
inline bool  py_q_getSaveOpaque() { return Positionable::getSaveOpaque(); }
inline double  py_q_getScale() { return Positionable::getScale(); }
inline QString  py_q_getTooltip() { return Positionable::getTooltip(); }
inline bool  py_q_getViewCoordinates() { return Positionable::getViewCoordinates(); }
inline int  py_q_getWidth() { return Positionable::getWidth(); }
inline int  py_q_getX() { return Positionable::getX(); }
inline int  py_q_getY() { return Positionable::getY(); }
inline void py_q_invalidate() { Positionable::invalidate(); }
inline bool  py_q_isControlling() { return Positionable::isControlling(); }
inline bool  py_q_isEditable() { return Positionable::isEditable(); }
inline bool  py_q_isHidden() { return Positionable::isHidden(); }
inline bool  py_q_isOpaque() { return Positionable::isOpaque(); }
inline bool  py_q_isPositionable() { return Positionable::isPositionable(); }
inline bool  py_q_isVisible() { return Positionable::isVisible(); }
inline void py_q_languageChange() { Positionable::languageChange(); }
inline int  py_q_maxHeight() { return Positionable::maxHeight(); }
inline int  py_q_maxWidth() { return Positionable::maxWidth(); }
inline void py_q_paint(QGraphicsScene*  arg__1) { Positionable::paint(arg__1); }
inline void py_q_remove() { Positionable::remove(); }
inline bool  py_q_requestFocusInWindow() { return Positionable::requestFocusInWindow(); }
inline void py_q_rotate(int  arg__1) { Positionable::rotate(arg__1); }
inline void py_q_setBackground(QColor  arg__1) { Positionable::setBackground(arg__1); }
inline void py_q_setControlling(bool  arg__1) { Positionable::setControlling(arg__1); }
inline bool  py_q_setDisableControlMenu(QMenu*  arg__1) { return Positionable::setDisableControlMenu(arg__1); }
inline void py_q_setDisplayLevel(int  arg__1) { Positionable::setDisplayLevel(arg__1); }
inline bool  py_q_setEditIconMenu(QMenu*  arg__1) { return Positionable::setEditIconMenu(arg__1); }
inline bool  py_q_setEditItemMenu(QMenu*  arg__1) { return Positionable::setEditItemMenu(arg__1); }
inline void py_q_setEditable(bool  arg__1) { Positionable::setEditable(arg__1); }
inline void py_q_setEditor(Editor*  arg__1) { Positionable::setEditor(arg__1); }
inline void py_q_setForeground(QColor  arg__1) { Positionable::setForeground(arg__1); }
inline void py_q_setHidden(bool  arg__1) { Positionable::setHidden(arg__1); }
inline void py_q_setLevel(int  arg__1) { Positionable::setLevel(arg__1); }
inline void py_q_setLocation(QPointF  arg__1) { Positionable::setLocation(arg__1); }
inline void py_q_setLocation(int  arg__1, int  arg__2) { Positionable::setLocation(arg__1, arg__2); }
inline void py_q_setOpaque(bool  arg__1) { Positionable::setOpaque(arg__1); }
inline void py_q_setPositionable(bool  arg__1) { Positionable::setPositionable(arg__1); }
inline bool  py_q_setRotateMenu(QMenu*  arg__1) { return Positionable::setRotateMenu(arg__1); }
inline bool  py_q_setRotateOrthogonalMenu(QMenu*  arg__1) { return Positionable::setRotateOrthogonalMenu(arg__1); }
inline void py_q_setScale(double  arg__1) { Positionable::setScale(arg__1); }
inline bool  py_q_setScaleMenu(QMenu*  arg__1) { return Positionable::setScaleMenu(arg__1); }
inline void py_q_setShowTooltip(bool  arg__1) { Positionable::setShowTooltip(arg__1); }
inline void py_q_setSize(int  arg__1, int  arg__2) { Positionable::setSize(arg__1, arg__2); }
inline bool  py_q_setTextEditMenu(QMenu*  arg__1) { return Positionable::setTextEditMenu(arg__1); }
inline void py_q_setViewCoordinates(bool  arg__1) { Positionable::setViewCoordinates(arg__1); }
inline void py_q_setVisible(bool  b) { Positionable::setVisible(b); }
inline void py_q_showHidden() { Positionable::showHidden(); }
inline bool  py_q_showPopUp(QMenu*  arg__1) { return Positionable::showPopUp(arg__1); }
inline bool  py_q_showToolTip() { return Positionable::showToolTip(); }
inline bool  py_q_storeItem() { return Positionable::storeItem(); }
inline bool  py_q_updateScene() { return Positionable::updateScene(); }
inline void py_q_updateSize() { Positionable::updateSize(); }
};

class PythonQtWrapper_Positionable : public QObject
{ Q_OBJECT
public:
public slots:
Positionable* new_Positionable(QString  text, QWidget*  parent = 0);
Positionable* new_Positionable(QWidget*  parent = 0);
void delete_Positionable(Positionable* obj) { delete obj; } 
   bool  contains(Positionable* theWrappedObject, int  arg__1, int  arg__2);
   bool  py_q_contains(Positionable* theWrappedObject, int  arg__1, int  arg__2){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_contains(arg__1, arg__2));}
   Positionable*  deepClone(Positionable* theWrappedObject);
   Positionable*  py_q_deepClone(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_deepClone());}
   void doMouseClicked(Positionable* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1);
   void py_q_doMouseClicked(Positionable* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_doMouseClicked(arg__1));}
   void doMouseDragged(Positionable* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1);
   void py_q_doMouseDragged(Positionable* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_doMouseDragged(arg__1));}
   void doMouseEntered(Positionable* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1);
   void py_q_doMouseEntered(Positionable* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_doMouseEntered(arg__1));}
   void doMouseExited(Positionable* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1);
   void py_q_doMouseExited(Positionable* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_doMouseExited(arg__1));}
   void doMouseMoved(Positionable* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1);
   void py_q_doMouseMoved(Positionable* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_doMouseMoved(arg__1));}
   void doMousePressed(Positionable* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1);
   void py_q_doMousePressed(Positionable* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_doMousePressed(arg__1));}
   void doMouseReleased(Positionable* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1);
   void py_q_doMouseReleased(Positionable* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_doMouseReleased(arg__1));}
   bool  doViemMenu(Positionable* theWrappedObject);
   bool  py_q_doViemMenu(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_doViemMenu());}
   Positionable*  finishClone(Positionable* theWrappedObject, Positionable*  arg__1);
   Positionable*  py_q_finishClone(Positionable* theWrappedObject, Positionable*  arg__1){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_finishClone(arg__1));}
   QColor  getBackground(Positionable* theWrappedObject);
   QColor  py_q_getBackground(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_getBackground());}
   QRectF  getBounds(Positionable* theWrappedObject, QRectF  arg__1);
   QRectF  py_q_getBounds(Positionable* theWrappedObject, QRectF  arg__1){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_getBounds(arg__1));}
   int  getDegrees(Positionable* theWrappedObject);
   int  py_q_getDegrees(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_getDegrees());}
   int  getDisplayLevel(Positionable* theWrappedObject);
   int  py_q_getDisplayLevel(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_getDisplayLevel());}
   Editor*  getEditor(Positionable* theWrappedObject);
   Editor*  py_q_getEditor(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_getEditor());}
   QFont  getFont(Positionable* theWrappedObject);
   QFont  py_q_getFont(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_getFont());}
   QColor  getForeground(Positionable* theWrappedObject);
   QColor  py_q_getForeground(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_getForeground());}
   QString  getGroupName(Positionable* theWrappedObject);
   QString  py_q_getGroupName(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_getGroupName());}
   int  getHeight(Positionable* theWrappedObject);
   int  py_q_getHeight(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_getHeight());}
   QGraphicsItem*  getItem(Positionable* theWrappedObject);
   QPointF  getLocation(Positionable* theWrappedObject);
   QPointF  py_q_getLocation(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_getLocation());}
   QString  getNameString(Positionable* theWrappedObject);
   QString  py_q_getNameString(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_getNameString());}
   NamedBean*  getNamedBean(Positionable* theWrappedObject);
   NamedBean*  py_q_getNamedBean(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_getNamedBean());}
   bool  getSaveOpaque(Positionable* theWrappedObject);
   bool  py_q_getSaveOpaque(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_getSaveOpaque());}
   double  getScale(Positionable* theWrappedObject);
   double  py_q_getScale(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_getScale());}
   QString  getTooltip(Positionable* theWrappedObject);
   QString  py_q_getTooltip(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_getTooltip());}
   bool  getViewCoordinates(Positionable* theWrappedObject);
   bool  py_q_getViewCoordinates(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_getViewCoordinates());}
   int  getWidth(Positionable* theWrappedObject);
   int  py_q_getWidth(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_getWidth());}
   int  getX(Positionable* theWrappedObject);
   int  py_q_getX(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_getX());}
   int  getY(Positionable* theWrappedObject);
   int  py_q_getY(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_getY());}
   void invalidate(Positionable* theWrappedObject);
   void py_q_invalidate(Positionable* theWrappedObject){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_invalidate());}
   bool  isControlling(Positionable* theWrappedObject);
   bool  py_q_isControlling(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_isControlling());}
   bool  isEditable(Positionable* theWrappedObject);
   bool  py_q_isEditable(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_isEditable());}
   bool  py_q_isHidden(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_isHidden());}
   bool  isOpaque(Positionable* theWrappedObject);
   bool  py_q_isOpaque(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_isOpaque());}
   bool  isPositionable(Positionable* theWrappedObject);
   bool  py_q_isPositionable(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_isPositionable());}
   bool  py_q_isVisible(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_isVisible());}
   void languageChange(Positionable* theWrappedObject);
   void py_q_languageChange(Positionable* theWrappedObject){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_languageChange());}
   int  maxHeight(Positionable* theWrappedObject);
   int  py_q_maxHeight(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_maxHeight());}
   int  maxWidth(Positionable* theWrappedObject);
   int  py_q_maxWidth(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_maxWidth());}
   void paint(Positionable* theWrappedObject, QGraphicsScene*  arg__1);
   void py_q_paint(Positionable* theWrappedObject, QGraphicsScene*  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_paint(arg__1));}
   void remove(Positionable* theWrappedObject);
   void py_q_remove(Positionable* theWrappedObject){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_remove());}
   bool  requestFocusInWindow(Positionable* theWrappedObject);
   bool  py_q_requestFocusInWindow(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_requestFocusInWindow());}
   void rotate(Positionable* theWrappedObject, int  arg__1);
   void py_q_rotate(Positionable* theWrappedObject, int  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_rotate(arg__1));}
   void setBackground(Positionable* theWrappedObject, QColor  arg__1);
   void py_q_setBackground(Positionable* theWrappedObject, QColor  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setBackground(arg__1));}
   void setControlling(Positionable* theWrappedObject, bool  arg__1);
   void py_q_setControlling(Positionable* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setControlling(arg__1));}
   bool  setDisableControlMenu(Positionable* theWrappedObject, QMenu*  arg__1);
   bool  py_q_setDisableControlMenu(Positionable* theWrappedObject, QMenu*  arg__1){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setDisableControlMenu(arg__1));}
   void setDisplayLevel(Positionable* theWrappedObject, int  arg__1);
   void py_q_setDisplayLevel(Positionable* theWrappedObject, int  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setDisplayLevel(arg__1));}
   bool  setEditIconMenu(Positionable* theWrappedObject, QMenu*  arg__1);
   bool  py_q_setEditIconMenu(Positionable* theWrappedObject, QMenu*  arg__1){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setEditIconMenu(arg__1));}
   bool  setEditItemMenu(Positionable* theWrappedObject, QMenu*  arg__1);
   bool  py_q_setEditItemMenu(Positionable* theWrappedObject, QMenu*  arg__1){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setEditItemMenu(arg__1));}
   void setEditable(Positionable* theWrappedObject, bool  arg__1);
   void py_q_setEditable(Positionable* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setEditable(arg__1));}
   void setEditor(Positionable* theWrappedObject, Editor*  arg__1);
   void py_q_setEditor(Positionable* theWrappedObject, Editor*  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setEditor(arg__1));}
   void setForeground(Positionable* theWrappedObject, QColor  arg__1);
   void py_q_setForeground(Positionable* theWrappedObject, QColor  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setForeground(arg__1));}
   void py_q_setHidden(Positionable* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setHidden(arg__1));}
   void setItem(Positionable* theWrappedObject, QGraphicsTextItem*  item);
   void setLevel(Positionable* theWrappedObject, int  arg__1);
   void py_q_setLevel(Positionable* theWrappedObject, int  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setLevel(arg__1));}
   void setLocation(Positionable* theWrappedObject, QPointF  arg__1);
   void py_q_setLocation(Positionable* theWrappedObject, QPointF  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setLocation(arg__1));}
   void setLocation(Positionable* theWrappedObject, int  arg__1, int  arg__2);
   void py_q_setLocation(Positionable* theWrappedObject, int  arg__1, int  arg__2){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setLocation(arg__1, arg__2));}
   void setOpaque(Positionable* theWrappedObject, bool  arg__1);
   void py_q_setOpaque(Positionable* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setOpaque(arg__1));}
   void setPositionable(Positionable* theWrappedObject, bool  arg__1);
   void py_q_setPositionable(Positionable* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setPositionable(arg__1));}
   bool  setRotateMenu(Positionable* theWrappedObject, QMenu*  arg__1);
   bool  py_q_setRotateMenu(Positionable* theWrappedObject, QMenu*  arg__1){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setRotateMenu(arg__1));}
   bool  setRotateOrthogonalMenu(Positionable* theWrappedObject, QMenu*  arg__1);
   bool  py_q_setRotateOrthogonalMenu(Positionable* theWrappedObject, QMenu*  arg__1){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setRotateOrthogonalMenu(arg__1));}
   void setScale(Positionable* theWrappedObject, double  arg__1);
   void py_q_setScale(Positionable* theWrappedObject, double  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setScale(arg__1));}
   bool  setScaleMenu(Positionable* theWrappedObject, QMenu*  arg__1);
   bool  py_q_setScaleMenu(Positionable* theWrappedObject, QMenu*  arg__1){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setScaleMenu(arg__1));}
   void setShowTooltip(Positionable* theWrappedObject, bool  arg__1);
   void py_q_setShowTooltip(Positionable* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setShowTooltip(arg__1));}
   void setSize(Positionable* theWrappedObject, int  arg__1, int  arg__2);
   void py_q_setSize(Positionable* theWrappedObject, int  arg__1, int  arg__2){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setSize(arg__1, arg__2));}
   bool  setTextEditMenu(Positionable* theWrappedObject, QMenu*  arg__1);
   bool  py_q_setTextEditMenu(Positionable* theWrappedObject, QMenu*  arg__1){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setTextEditMenu(arg__1));}
   void setViewCoordinates(Positionable* theWrappedObject, bool  arg__1);
   void py_q_setViewCoordinates(Positionable* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setViewCoordinates(arg__1));}
   void py_q_setVisible(Positionable* theWrappedObject, bool  b){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setVisible(b));}
   void showHidden(Positionable* theWrappedObject);
   void py_q_showHidden(Positionable* theWrappedObject){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_showHidden());}
   bool  showPopUp(Positionable* theWrappedObject, QMenu*  arg__1);
   bool  py_q_showPopUp(Positionable* theWrappedObject, QMenu*  arg__1){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_showPopUp(arg__1));}
   bool  showToolTip(Positionable* theWrappedObject);
   bool  py_q_showToolTip(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_showToolTip());}
   bool  storeItem(Positionable* theWrappedObject);
   bool  py_q_storeItem(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_storeItem());}
   bool  updateScene(Positionable* theWrappedObject);
   bool  py_q_updateScene(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_updateScene());}
   void updateSize(Positionable* theWrappedObject);
   void py_q_updateSize(Positionable* theWrappedObject){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_updateSize());}
void py_set__handleGroup(Positionable* theWrappedObject, MyGraphicsItemGroup*  _handleGroup){ theWrappedObject->_handleGroup = _handleGroup; }
MyGraphicsItemGroup*  py_get__handleGroup(Positionable* theWrappedObject){ return theWrappedObject->_handleGroup; }
void py_set__itemGroup(Positionable* theWrappedObject, MyGraphicsItemGroup*  _itemGroup){ theWrappedObject->_itemGroup = _itemGroup; }
MyGraphicsItemGroup*  py_get__itemGroup(Positionable* theWrappedObject){ return theWrappedObject->_itemGroup; }
};





class PythonQtShell_PositionableLabel : public PositionableLabel
{
public:
    PythonQtShell_PositionableLabel(QString  s, Editor*  editor, Positionable*  parent = 0):PositionableLabel(s, editor, parent),_wrapper(NULL) {}
    PythonQtShell_PositionableLabel(QWidget*  parent = 0):PositionableLabel(parent),_wrapper(NULL) {}

   ~PythonQtShell_PositionableLabel();

virtual void actionEvent(QActionEvent*  event);
virtual void changeEvent(QEvent*  arg__1);
virtual void childEvent(QChildEvent*  event);
virtual void closeEvent(QCloseEvent*  event);
virtual bool  contains(int  arg__1, int  arg__2);
virtual void contextMenuEvent(QContextMenuEvent*  ev);
virtual void customEvent(QEvent*  event);
virtual Positionable*  deepClone();
virtual int  devType() const;
virtual void dispose();
virtual void doMouseClicked(QGraphicsSceneMouseEvent*  event);
virtual void doMouseDragged(QGraphicsSceneMouseEvent*  event);
virtual void doMouseEntered(QGraphicsSceneMouseEvent*  event);
virtual void doMouseExited(QGraphicsSceneMouseEvent*  event);
virtual void doMouseMoved(QGraphicsSceneMouseEvent*  event);
virtual void doMousePressed(QGraphicsSceneMouseEvent*  event);
virtual void doMouseReleased(QGraphicsSceneMouseEvent*  event);
virtual bool  doViemMenu();
virtual void dragEnterEvent(QDragEnterEvent*  event);
virtual void dragLeaveEvent(QDragLeaveEvent*  event);
virtual void dragMoveEvent(QDragMoveEvent*  event);
virtual void dropEvent(QDropEvent*  event);
virtual void enterEvent(QEvent*  event);
virtual bool  event(QEvent*  e);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual Positionable*  finishClone(Positionable*  p);
virtual void focusInEvent(QFocusEvent*  ev);
virtual bool  focusNextPrevChild(bool  next);
virtual void focusOutEvent(QFocusEvent*  ev);
virtual QColor  getBackground();
virtual QRectF  getBounds(QRectF  arg__1 = QRectF());
virtual int  getDegrees();
virtual int  getDisplayLevel();
virtual Editor*  getEditor();
virtual QFont  getFont();
virtual QColor  getForeground();
virtual QString  getGroupName();
virtual int  getHeight();
virtual QPointF  getLocation();
virtual QString  getNameString();
virtual NamedBean*  getNamedBean();
virtual bool  getSaveOpaque();
virtual double  getScale();
virtual QString  getTooltip();
virtual bool  getViewCoordinates();
virtual int  getWidth();
virtual int  getX();
virtual int  getY();
virtual bool  hasHeightForWidth() const;
virtual int  heightForWidth(int  arg__1) const;
virtual void hideEvent(QHideEvent*  event);
virtual void initPainter(QPainter*  painter) const;
virtual void inputMethodEvent(QInputMethodEvent*  arg__1);
virtual QVariant  inputMethodQuery(Qt::InputMethodQuery  arg__1) const;
virtual void invalidate();
virtual bool  isControlling();
virtual bool  isEditable();
virtual bool  isHidden();
virtual bool  isOpaque();
virtual bool  isPositionable();
virtual bool  isVisible();
virtual void keyPressEvent(QKeyEvent*  ev);
virtual void keyReleaseEvent(QKeyEvent*  event);
virtual void languageChange();
virtual void leaveEvent(QEvent*  event);
virtual int  maxHeight();
virtual int  maxWidth();
virtual int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
virtual QSize  minimumSizeHint() const;
virtual void mouseDoubleClickEvent(QMouseEvent*  event);
virtual void mouseMoveEvent(QMouseEvent*  ev);
virtual void mousePressEvent(QMouseEvent*  ev);
virtual void mouseReleaseEvent(QMouseEvent*  ev);
virtual void moveEvent(QMoveEvent*  event);
virtual bool  nativeEvent(const QByteArray&  eventType, void*  message, long*  result);
virtual void paint(QGraphicsScene*  arg__1);
virtual QPaintEngine*  paintEngine() const;
virtual void paintEvent(QPaintEvent*  arg__1);
virtual QPaintDevice*  redirected(QPoint*  offset) const;
virtual void remove();
virtual bool  requestFocusInWindow();
virtual void resizeEvent(QResizeEvent*  event);
virtual void rotate(int  deg);
virtual void setBackground(QColor  bg);
virtual void setControlling(bool  enabled);
virtual bool  setDisableControlMenu(QMenu*  popup);
virtual void setDisplayLevel(int  l);
virtual bool  setEditIconMenu(QMenu*  popup);
virtual bool  setEditItemMenu(QMenu*  popup);
virtual void setEditable(bool  enabled);
virtual void setEditor(Editor*  ed);
virtual void setForeground(QColor  c);
virtual void setHidden(bool  hide);
virtual void setLevel(int  l);
virtual void setLocation(int  x, int  y);
virtual void setOpaque(bool  isOpaque);
virtual void setPositionable(bool  enabled);
virtual bool  setRotateMenu(QMenu*  popup);
virtual bool  setRotateOrthogonalMenu(QMenu*  popup);
virtual void setScale(double  s);
virtual bool  setScaleMenu(QMenu*  popup);
virtual void setShowTooltip(bool  set);
virtual void setSize(int  x, int  y);
virtual bool  setTextEditMenu(QMenu*  popup);
virtual void setViewCoordinates(bool  enabled);
virtual void setVisible(bool  b);
virtual QPainter*  sharedPainter() const;
virtual void showEvent(QShowEvent*  event);
virtual void showHidden();
virtual bool  showPopUp(QMenu*  popup);
virtual bool  showToolTip();
virtual QSize  sizeHint() const;
virtual bool  storeItem();
virtual void tabletEvent(QTabletEvent*  event);
virtual void timerEvent(QTimerEvent*  event);
virtual bool  updateScene();
virtual void updateSize();
virtual void wheelEvent(QWheelEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_PositionableLabel : public PositionableLabel
{ public:
inline void promoted_editIcon() { this->editIcon(); }
inline Positionable*  py_q_deepClone() { return PositionableLabel::deepClone(); }
inline void py_q_dispose() { PositionableLabel::dispose(); }
inline void py_q_doMouseClicked(QGraphicsSceneMouseEvent*  event) { PositionableLabel::doMouseClicked(event); }
inline void py_q_doMouseDragged(QGraphicsSceneMouseEvent*  event) { PositionableLabel::doMouseDragged(event); }
inline void py_q_doMouseEntered(QGraphicsSceneMouseEvent*  event) { PositionableLabel::doMouseEntered(event); }
inline void py_q_doMouseExited(QGraphicsSceneMouseEvent*  event) { PositionableLabel::doMouseExited(event); }
inline void py_q_doMouseMoved(QGraphicsSceneMouseEvent*  event) { PositionableLabel::doMouseMoved(event); }
inline void py_q_doMousePressed(QGraphicsSceneMouseEvent*  event) { PositionableLabel::doMousePressed(event); }
inline void py_q_doMouseReleased(QGraphicsSceneMouseEvent*  event) { PositionableLabel::doMouseReleased(event); }
inline bool  py_q_doViemMenu() { return PositionableLabel::doViemMenu(); }
inline Positionable*  py_q_finishClone(Positionable*  p) { return PositionableLabel::finishClone(p); }
inline QColor  py_q_getBackground() { return PositionableLabel::getBackground(); }
inline QRectF  py_q_getBounds(QRectF  arg__1 = QRectF()) { return PositionableLabel::getBounds(arg__1); }
inline int  py_q_getDegrees() { return PositionableLabel::getDegrees(); }
inline int  py_q_getDisplayLevel() { return PositionableLabel::getDisplayLevel(); }
inline Editor*  py_q_getEditor() { return PositionableLabel::getEditor(); }
inline QFont  py_q_getFont() { return PositionableLabel::getFont(); }
inline QColor  py_q_getForeground() { return PositionableLabel::getForeground(); }
inline int  py_q_getHeight() { return PositionableLabel::getHeight(); }
inline QString  py_q_getNameString() { return PositionableLabel::getNameString(); }
inline NamedBean*  py_q_getNamedBean() { return PositionableLabel::getNamedBean(); }
inline bool  py_q_getSaveOpaque() { return PositionableLabel::getSaveOpaque(); }
inline double  py_q_getScale() { return PositionableLabel::getScale(); }
inline QString  py_q_getTooltip() { return PositionableLabel::getTooltip(); }
inline bool  py_q_getViewCoordinates() { return PositionableLabel::getViewCoordinates(); }
inline int  py_q_getWidth() { return PositionableLabel::getWidth(); }
inline bool  py_q_isControlling() { return PositionableLabel::isControlling(); }
inline bool  py_q_isEditable() { return PositionableLabel::isEditable(); }
inline bool  py_q_isHidden() { return PositionableLabel::isHidden(); }
inline bool  py_q_isOpaque() { return PositionableLabel::isOpaque(); }
inline bool  py_q_isPositionable() { return PositionableLabel::isPositionable(); }
inline bool  py_q_isVisible() { return PositionableLabel::isVisible(); }
inline int  py_q_maxHeight() { return PositionableLabel::maxHeight(); }
inline int  py_q_maxWidth() { return PositionableLabel::maxWidth(); }
inline void py_q_remove() { PositionableLabel::remove(); }
inline void py_q_rotate(int  deg) { PositionableLabel::rotate(deg); }
inline void py_q_setBackground(QColor  bg) { PositionableLabel::setBackground(bg); }
inline void py_q_setControlling(bool  enabled) { PositionableLabel::setControlling(enabled); }
inline bool  py_q_setDisableControlMenu(QMenu*  popup) { return PositionableLabel::setDisableControlMenu(popup); }
inline void py_q_setDisplayLevel(int  l) { PositionableLabel::setDisplayLevel(l); }
inline bool  py_q_setEditIconMenu(QMenu*  popup) { return PositionableLabel::setEditIconMenu(popup); }
inline bool  py_q_setEditItemMenu(QMenu*  popup) { return PositionableLabel::setEditItemMenu(popup); }
inline void py_q_setEditable(bool  enabled) { PositionableLabel::setEditable(enabled); }
inline void py_q_setEditor(Editor*  ed) { PositionableLabel::setEditor(ed); }
inline void py_q_setForeground(QColor  c) { PositionableLabel::setForeground(c); }
inline void py_q_setHidden(bool  hide) { PositionableLabel::setHidden(hide); }
inline void py_q_setLevel(int  l) { PositionableLabel::setLevel(l); }
inline void py_q_setOpaque(bool  isOpaque) { PositionableLabel::setOpaque(isOpaque); }
inline void py_q_setPositionable(bool  enabled) { PositionableLabel::setPositionable(enabled); }
inline bool  py_q_setRotateMenu(QMenu*  popup) { return PositionableLabel::setRotateMenu(popup); }
inline bool  py_q_setRotateOrthogonalMenu(QMenu*  popup) { return PositionableLabel::setRotateOrthogonalMenu(popup); }
inline void py_q_setScale(double  s) { PositionableLabel::setScale(s); }
inline bool  py_q_setScaleMenu(QMenu*  popup) { return PositionableLabel::setScaleMenu(popup); }
inline void py_q_setShowTooltip(bool  set) { PositionableLabel::setShowTooltip(set); }
inline void py_q_setSize(int  x, int  y) { PositionableLabel::setSize(x, y); }
inline bool  py_q_setTextEditMenu(QMenu*  popup) { return PositionableLabel::setTextEditMenu(popup); }
inline void py_q_setViewCoordinates(bool  enabled) { PositionableLabel::setViewCoordinates(enabled); }
inline void py_q_setVisible(bool  b) { PositionableLabel::setVisible(b); }
inline void py_q_showHidden() { PositionableLabel::showHidden(); }
inline bool  py_q_showPopUp(QMenu*  popup) { return PositionableLabel::showPopUp(popup); }
inline bool  py_q_storeItem() { return PositionableLabel::storeItem(); }
inline bool  py_q_updateScene() { return PositionableLabel::updateScene(); }
inline void py_q_updateSize() { PositionableLabel::updateSize(); }
};

class PythonQtWrapper_PositionableLabel : public QObject
{ Q_OBJECT
public:
public slots:
PositionableLabel* new_PositionableLabel(QString  s, Editor*  editor, Positionable*  parent = 0);
PositionableLabel* new_PositionableLabel(QWidget*  parent = 0);
void delete_PositionableLabel(PositionableLabel* obj) { delete obj; } 
   Positionable*  py_q_deepClone(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_deepClone());}
   void dispose(PositionableLabel* theWrappedObject);
   void py_q_dispose(PositionableLabel* theWrappedObject){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_dispose());}
   void py_q_doMouseClicked(PositionableLabel* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_doMouseClicked(event));}
   void py_q_doMouseDragged(PositionableLabel* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_doMouseDragged(event));}
   void py_q_doMouseEntered(PositionableLabel* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_doMouseEntered(event));}
   void py_q_doMouseExited(PositionableLabel* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_doMouseExited(event));}
   void py_q_doMouseMoved(PositionableLabel* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_doMouseMoved(event));}
   void py_q_doMousePressed(PositionableLabel* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_doMousePressed(event));}
   void py_q_doMouseReleased(PositionableLabel* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_doMouseReleased(event));}
   bool  py_q_doViemMenu(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_doViemMenu());}
   void editIcon(PositionableLabel* theWrappedObject);
   Positionable*  py_q_finishClone(PositionableLabel* theWrappedObject, Positionable*  p){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_finishClone(p));}
   QColor  py_q_getBackground(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getBackground());}
   QRectF  py_q_getBounds(PositionableLabel* theWrappedObject, QRectF  arg__1 = QRectF()){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getBounds(arg__1));}
   int  py_q_getDegrees(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getDegrees());}
   int  py_q_getDisplayLevel(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getDisplayLevel());}
   Editor*  py_q_getEditor(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getEditor());}
   QFont  py_q_getFont(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getFont());}
   QColor  py_q_getForeground(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getForeground());}
   int  py_q_getHeight(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getHeight());}
   QString  py_q_getNameString(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getNameString());}
   NamedBean*  py_q_getNamedBean(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getNamedBean());}
   QSize  getPreferredSize(PositionableLabel* theWrappedObject);
   bool  py_q_getSaveOpaque(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getSaveOpaque());}
   double  py_q_getScale(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getScale());}
   QSize  getSize(PositionableLabel* theWrappedObject);
   QObject*  getTextComponent(PositionableLabel* theWrappedObject);
   QString  py_q_getTooltip(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getTooltip());}
   QString  getUnRotatedText(PositionableLabel* theWrappedObject);
   bool  py_q_getViewCoordinates(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getViewCoordinates());}
   int  py_q_getWidth(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getWidth());}
   bool  isActive(PositionableLabel* theWrappedObject);
   bool  isBackground(PositionableLabel* theWrappedObject);
   bool  isControl(PositionableLabel* theWrappedObject);
   bool  py_q_isControlling(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_isControlling());}
   bool  py_q_isEditable(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_isEditable());}
   bool  py_q_isHidden(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_isHidden());}
   bool  isIcon(PositionableLabel* theWrappedObject);
   bool  py_q_isOpaque(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_isOpaque());}
   bool  py_q_isPositionable(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_isPositionable());}
   bool  isRotated(PositionableLabel* theWrappedObject);
   bool  isText(PositionableLabel* theWrappedObject);
   bool  py_q_isVisible(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_isVisible());}
   int  py_q_maxHeight(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_maxHeight());}
   int  maxHeightTrue(PositionableLabel* theWrappedObject);
   int  py_q_maxWidth(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_maxWidth());}
   int  maxWidthTrue(PositionableLabel* theWrappedObject);
   void py_q_remove(PositionableLabel* theWrappedObject){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_remove());}
   void py_q_rotate(PositionableLabel* theWrappedObject, int  deg){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_rotate(deg));}
   void saveOpaque(PositionableLabel* theWrappedObject, bool  set);
   void py_q_setBackground(PositionableLabel* theWrappedObject, QColor  bg){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setBackground(bg));}
   void setBackgroundColor(PositionableLabel* theWrappedObject, QColor  color);
   void py_q_setControlling(PositionableLabel* theWrappedObject, bool  enabled){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setControlling(enabled));}
   void setDegrees(PositionableLabel* theWrappedObject, int  deg);
   bool  py_q_setDisableControlMenu(PositionableLabel* theWrappedObject, QMenu*  popup){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setDisableControlMenu(popup));}
   void py_q_setDisplayLevel(PositionableLabel* theWrappedObject, int  l){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setDisplayLevel(l));}
   bool  py_q_setEditIconMenu(PositionableLabel* theWrappedObject, QMenu*  popup){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setEditIconMenu(popup));}
   bool  py_q_setEditItemMenu(PositionableLabel* theWrappedObject, QMenu*  popup){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setEditItemMenu(popup));}
   void py_q_setEditable(PositionableLabel* theWrappedObject, bool  enabled){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setEditable(enabled));}
   void py_q_setEditor(PositionableLabel* theWrappedObject, Editor*  ed){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setEditor(ed));}
   void setFont(PositionableLabel* theWrappedObject, const QFont&  font);
   void py_q_setForeground(PositionableLabel* theWrappedObject, QColor  c){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setForeground(c));}
   void py_q_setHidden(PositionableLabel* theWrappedObject, bool  hide){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setHidden(hide));}
   void py_q_setLevel(PositionableLabel* theWrappedObject, int  l){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setLevel(l));}
   void py_q_setOpaque(PositionableLabel* theWrappedObject, bool  isOpaque){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setOpaque(isOpaque));}
   void py_q_setPositionable(PositionableLabel* theWrappedObject, bool  enabled){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setPositionable(enabled));}
   bool  py_q_setRotateMenu(PositionableLabel* theWrappedObject, QMenu*  popup){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setRotateMenu(popup));}
   bool  py_q_setRotateOrthogonalMenu(PositionableLabel* theWrappedObject, QMenu*  popup){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setRotateOrthogonalMenu(popup));}
   void py_q_setScale(PositionableLabel* theWrappedObject, double  s){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setScale(s));}
   bool  py_q_setScaleMenu(PositionableLabel* theWrappedObject, QMenu*  popup){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setScaleMenu(popup));}
   void py_q_setShowTooltip(PositionableLabel* theWrappedObject, bool  set){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setShowTooltip(set));}
   void py_q_setSize(PositionableLabel* theWrappedObject, int  x, int  y){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setSize(x, y));}
   void setStyleSheet(PositionableLabel* theWrappedObject);
   void setSuperText(PositionableLabel* theWrappedObject, QString  text);
   void setText(PositionableLabel* theWrappedObject, QString  text);
   bool  py_q_setTextEditMenu(PositionableLabel* theWrappedObject, QMenu*  popup){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setTextEditMenu(popup));}
   void setTooltip(PositionableLabel* theWrappedObject, QString  tip);
   void py_q_setViewCoordinates(PositionableLabel* theWrappedObject, bool  enabled){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setViewCoordinates(enabled));}
   void py_q_setVisible(PositionableLabel* theWrappedObject, bool  b){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setVisible(b));}
   void py_q_showHidden(PositionableLabel* theWrappedObject){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_showHidden());}
   bool  py_q_showPopUp(PositionableLabel* theWrappedObject, QMenu*  popup){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_showPopUp(popup));}
   bool  showTooltip(PositionableLabel* theWrappedObject);
   bool  py_q_storeItem(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_storeItem());}
   bool  py_q_updateScene(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_updateScene());}
   void py_q_updateSize(PositionableLabel* theWrappedObject){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_updateSize());}
};





class PythonQtShell_PowerManager : public PowerManager
{
public:
    PythonQtShell_PowerManager(QObject*  parent = 0):PowerManager(parent),_wrapper(NULL) {}
    PythonQtShell_PowerManager(const PowerManager&  arg__1):PowerManager(arg__1),_wrapper(NULL) {}

   ~PythonQtShell_PowerManager();

virtual void addPropertyChangeListener(PropertyChangeListener*  arg__1);
virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual void dispose();
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual int  getPower();
virtual QString  getUserName();
virtual void removePropertyChangeListener(PropertyChangeListener*  arg__1);
virtual void setPower(int  arg__1);
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_PowerManager : public PowerManager
{ public:
inline void py_q_addPropertyChangeListener(PropertyChangeListener*  arg__1) { PowerManager::addPropertyChangeListener(arg__1); }
inline void py_q_dispose() { PowerManager::dispose(); }
inline int  py_q_getPower() { return PowerManager::getPower(); }
inline QString  py_q_getUserName() { return PowerManager::getUserName(); }
inline void py_q_removePropertyChangeListener(PropertyChangeListener*  arg__1) { PowerManager::removePropertyChangeListener(arg__1); }
inline void py_q_setPower(int  arg__1) { PowerManager::setPower(arg__1); }
};

class PythonQtWrapper_PowerManager : public QObject
{ Q_OBJECT
public:
public slots:
PowerManager* new_PowerManager(QObject*  parent = 0);
PowerManager* new_PowerManager(const PowerManager&  arg__1);
void delete_PowerManager(PowerManager* obj) { delete obj; } 
   void addPropertyChangeListener(PowerManager* theWrappedObject, PropertyChangeListener*  arg__1);
   void py_q_addPropertyChangeListener(PowerManager* theWrappedObject, PropertyChangeListener*  arg__1){  (((PythonQtPublicPromoter_PowerManager*)theWrappedObject)->py_q_addPropertyChangeListener(arg__1));}
   void dispose(PowerManager* theWrappedObject);
   void py_q_dispose(PowerManager* theWrappedObject){  (((PythonQtPublicPromoter_PowerManager*)theWrappedObject)->py_q_dispose());}
   int  getPower(PowerManager* theWrappedObject);
   int  py_q_getPower(PowerManager* theWrappedObject){  return (((PythonQtPublicPromoter_PowerManager*)theWrappedObject)->py_q_getPower());}
   QString  getUserName(PowerManager* theWrappedObject);
   QString  py_q_getUserName(PowerManager* theWrappedObject){  return (((PythonQtPublicPromoter_PowerManager*)theWrappedObject)->py_q_getUserName());}
   void removePropertyChangeListener(PowerManager* theWrappedObject, PropertyChangeListener*  arg__1);
   void py_q_removePropertyChangeListener(PowerManager* theWrappedObject, PropertyChangeListener*  arg__1){  (((PythonQtPublicPromoter_PowerManager*)theWrappedObject)->py_q_removePropertyChangeListener(arg__1));}
   void setPower(PowerManager* theWrappedObject, int  arg__1);
   void py_q_setPower(PowerManager* theWrappedObject, int  arg__1){  (((PythonQtPublicPromoter_PowerManager*)theWrappedObject)->py_q_setPower(arg__1));}
void py_set_pcs(PowerManager* theWrappedObject, PropertyChangeSupport*  pcs){ theWrappedObject->pcs = pcs; }
PropertyChangeSupport*  py_get_pcs(PowerManager* theWrappedObject){ return theWrappedObject->pcs; }
};





class PythonQtShell_ProgListener : public ProgListener
{
public:
    PythonQtShell_ProgListener(QObject*  parent = 0):ProgListener(parent),_wrapper(NULL) {}

   ~PythonQtShell_ProgListener();

virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual void programmingOpReply(int  value, int  status);
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_ProgListener : public ProgListener
{ public:
inline void py_q_programmingOpReply(int  value, int  status) { ProgListener::programmingOpReply(value, status); }
};

class PythonQtWrapper_ProgListener : public QObject
{ Q_OBJECT
public:
public slots:
ProgListener* new_ProgListener(QObject*  parent = 0);
void delete_ProgListener(ProgListener* obj) { delete obj; } 
   void py_q_programmingOpReply(ProgListener* theWrappedObject, int  value, int  status){  (((PythonQtPublicPromoter_ProgListener*)theWrappedObject)->py_q_programmingOpReply(value, status));}
};





class PythonQtShell_ProgrammerManager : public ProgrammerManager
{
public:
    PythonQtShell_ProgrammerManager(QObject*  parent = 0):ProgrammerManager(parent),_wrapper(NULL) {}

   ~PythonQtShell_ProgrammerManager();

virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual QList<ProgrammingMode* >  getDefaultModes();
virtual QString  getUserName();
virtual bool  isAddressedModePossible();
virtual bool  isGlobalProgrammerAvailable();
virtual void timerEvent(QTimerEvent*  event);
virtual QString  toString();

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtWrapper_ProgrammerManager : public QObject
{ Q_OBJECT
public:
public slots:
ProgrammerManager* new_ProgrammerManager(QObject*  parent = 0);
void delete_ProgrammerManager(ProgrammerManager* obj) { delete obj; } 
    QString py_toString(ProgrammerManager*);
};





class PythonQtShell_ProgrammingMode : public ProgrammingMode
{
public:
    PythonQtShell_ProgrammingMode(QString  standardName, QString  localName = "standardName", QObject*  parent = nullptr):ProgrammingMode(standardName, localName, parent),_wrapper(NULL) {}

   ~PythonQtShell_ProgrammingMode();

virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtWrapper_ProgrammingMode : public QObject
{ Q_OBJECT
public:
public slots:
ProgrammingMode* new_ProgrammingMode(QString  standardName, QString  localName = "standardName", QObject*  parent = nullptr);
void delete_ProgrammingMode(ProgrammingMode* obj) { delete obj; } 
   bool  equals(ProgrammingMode* theWrappedObject, QObject*  o);
   QString  getStandardName(ProgrammingMode* theWrappedObject);
   int  hashCode(ProgrammingMode* theWrappedObject);
   QString  toString(ProgrammingMode* theWrappedObject);
    QString py_toString(ProgrammingMode*);
};





class PythonQtShell_PropertyChangeEvent : public PropertyChangeEvent
{
public:
    PythonQtShell_PropertyChangeEvent(QObject*  source, QString  propertyName, QObject*  oldValue, QObject*  newValue, QObject*  parent = 0):PropertyChangeEvent(source, propertyName, oldValue, newValue, parent),_wrapper(NULL) {}
    PythonQtShell_PropertyChangeEvent(QObject*  source, QString  propertyName, QVariant  oldValue, QVariant  newValue, QObject*  parent = 0):PropertyChangeEvent(source, propertyName, oldValue, newValue, parent),_wrapper(NULL) {}

   ~PythonQtShell_PropertyChangeEvent();

virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtWrapper_PropertyChangeEvent : public QObject
{ Q_OBJECT
public:
public slots:
PropertyChangeEvent* new_PropertyChangeEvent(QObject*  source, QString  propertyName, QObject*  oldValue, QObject*  newValue, QObject*  parent = 0);
PropertyChangeEvent* new_PropertyChangeEvent(QObject*  source, QString  propertyName, QVariant  oldValue, QVariant  newValue, QObject*  parent = 0);
void delete_PropertyChangeEvent(PropertyChangeEvent* obj) { delete obj; } 
   void appendTo(PropertyChangeEvent* theWrappedObject, QString  sb);
   QVariant  getNewValue(PropertyChangeEvent* theWrappedObject);
   QVariant  getOldValue(PropertyChangeEvent* theWrappedObject);
   QVariant  getPropagationId(PropertyChangeEvent* theWrappedObject);
   QString  getPropertyName(PropertyChangeEvent* theWrappedObject);
   void setPropagationId(PropertyChangeEvent* theWrappedObject, QVariant  propagationId);
   QString  toString(PropertyChangeEvent* theWrappedObject);
    QString py_toString(PropertyChangeEvent*);
void py_set_source(PropertyChangeEvent* theWrappedObject, QObject*  source){ theWrappedObject->source = source; }
QObject*  py_get_source(PropertyChangeEvent* theWrappedObject){ return theWrappedObject->source; }
};





class PythonQtShell_PropertyChangeListener : public PropertyChangeListener
{
public:
    PythonQtShell_PropertyChangeListener(QObject*  parent = 0):PropertyChangeListener(parent),_wrapper(NULL) {}

   ~PythonQtShell_PropertyChangeListener();

virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual void propertyChange(PropertyChangeEvent*  e);
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_PropertyChangeListener : public PropertyChangeListener
{ public:
inline void py_q_propertyChange(PropertyChangeEvent*  e) { PropertyChangeListener::propertyChange(e); }
};

class PythonQtWrapper_PropertyChangeListener : public QObject
{ Q_OBJECT
public:
public slots:
PropertyChangeListener* new_PropertyChangeListener(QObject*  parent = 0);
void delete_PropertyChangeListener(PropertyChangeListener* obj) { delete obj; } 
   void py_q_propertyChange(PropertyChangeListener* theWrappedObject, PropertyChangeEvent*  e){  (((PythonQtPublicPromoter_PropertyChangeListener*)theWrappedObject)->py_q_propertyChange(e));}
};





class PythonQtShell_PropertyChangeSupport : public PropertyChangeSupport
{
public:
    PythonQtShell_PropertyChangeSupport(QObject*  sourceBean, QObject*  parent = 0):PropertyChangeSupport(sourceBean, parent),_wrapper(NULL) {}

   ~PythonQtShell_PropertyChangeSupport();

virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtWrapper_PropertyChangeSupport : public QObject
{ Q_OBJECT
public:
public slots:
PropertyChangeSupport* new_PropertyChangeSupport(QObject*  sourceBean, QObject*  parent = 0);
void delete_PropertyChangeSupport(PropertyChangeSupport* obj) { delete obj; } 
   void addPropertyChangeListener(PropertyChangeSupport* theWrappedObject, PropertyChangeListener*  listener);
   void addPropertyChangeListener(PropertyChangeSupport* theWrappedObject, QString  propertyName, PropertyChangeListener*  listener);
   void fireIndexedPropertyChange(PropertyChangeSupport* theWrappedObject, QString  propertyName, int  index, QVariant  oldValue, QVariant  newValue);
   void fireIndexedPropertyChange(PropertyChangeSupport* theWrappedObject, QString  propertyName, int  index, bool  oldValue, bool  newValue);
   void fireIndexedPropertyChange(PropertyChangeSupport* theWrappedObject, QString  propertyName, int  index, int  oldValue, int  newValue);
   void firePropertyChange(PropertyChangeSupport* theWrappedObject, PropertyChangeEvent*  event);
   void firePropertyChange(PropertyChangeSupport* theWrappedObject, QString  propertyName, QVariant  oldValue, QVariant  newValue);
   void firePropertyChange(PropertyChangeSupport* theWrappedObject, QString  propertyName, bool  oldValue, bool  newValue);
   QList<PropertyChangeListener* >*  getPropertyChangeListeners(PropertyChangeSupport* theWrappedObject);
   QList<PropertyChangeListener* >*  getPropertyChangeListeners(PropertyChangeSupport* theWrappedObject, QString  propertyName);
   bool  hasListeners(PropertyChangeSupport* theWrappedObject, QString  propertyName);
   void removePropertyChangeListener(PropertyChangeSupport* theWrappedObject, PropertyChangeListener*  listener);
   void removePropertyChangeListener(PropertyChangeSupport* theWrappedObject, QString  propertyName, PropertyChangeListener*  listener);
};





class PythonQtShell_ProxyLightManager : public ProxyLightManager
{
public:
    PythonQtShell_ProxyLightManager(QObject*  parent = 0):ProxyLightManager(parent),_wrapper(NULL) {}

   ~PythonQtShell_ProxyLightManager();

virtual void Register(NamedBean*  s);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual void deregister(NamedBean*  s);
virtual void dispose();
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual NamedBean*  getBeanBySystemName(QString  systemName);
virtual NamedBean*  getBeanByUserName(QString  userName);
virtual QString  getBeanTypeHandled();
virtual QString  getEntryToolTip();
virtual Manager*  getMgr(int  index);
virtual NamedBean*  getNamedBean(QString  name);
virtual QSet<NamedBean* >  getNamedBeanSet();
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList();
virtual QString  getSystemPrefix();
virtual QStringList  getUserNameList();
virtual int  getXMLOrder();
virtual NamedBean*  makeBean(int  i, QString  systemName, QString  userName);
virtual Manager*  makeInternalManager() const;
virtual QString  makeSystemName(QString  s);
virtual int  match(QString  systemname);
virtual int  matchTentative(QString  arg__1);
virtual int  nMgrs();
virtual QString  normalizeSystemName(QString  systemName);
virtual void propertyChange(PropertyChangeEvent*  e);
virtual NamedBean*  provideNamedBean(QString  name);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void timerEvent(QTimerEvent*  event);
virtual char  typeLetter();
virtual Manager::NameValidity  validSystemNameFormat(QString  systemName);
virtual void vetoableChange(PropertyChangeEvent*  evt);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_ProxyLightManager : public ProxyLightManager
{ public:
inline NamedBean*  promoted_makeBean(int  i, QString  systemName, QString  userName) { return this->makeBean(i, systemName, userName); }
inline Manager*  promoted_makeInternalManager() const { return this->makeInternalManager(); }
inline int  py_q_getXMLOrder() { return ProxyLightManager::getXMLOrder(); }
inline NamedBean*  py_q_makeBean(int  i, QString  systemName, QString  userName) { return ProxyLightManager::makeBean(i, systemName, userName); }
inline Manager*  py_q_makeInternalManager() const { return ProxyLightManager::makeInternalManager(); }
inline QString  py_q_normalizeSystemName(QString  systemName) { return ProxyLightManager::normalizeSystemName(systemName); }
inline Manager::NameValidity  py_q_validSystemNameFormat(QString  systemName) { return ProxyLightManager::validSystemNameFormat(systemName); }
};

class PythonQtWrapper_ProxyLightManager : public QObject
{ Q_OBJECT
public:
public slots:
ProxyLightManager* new_ProxyLightManager(QObject*  parent = 0);
void delete_ProxyLightManager(ProxyLightManager* obj) { delete obj; } 
   void activateAllLights(ProxyLightManager* theWrappedObject);
   bool  allowMultipleAdditions(ProxyLightManager* theWrappedObject, QString  systemName);
   QString  convertSystemNameToAlternate(ProxyLightManager* theWrappedObject, QString  systemName);
   Light*  getBySystemName(ProxyLightManager* theWrappedObject, QString  systemName);
   Light*  getByUserName(ProxyLightManager* theWrappedObject, QString  userName);
   Light*  getLight(ProxyLightManager* theWrappedObject, QString  name);
   int  py_q_getXMLOrder(ProxyLightManager* theWrappedObject){  return (((PythonQtPublicPromoter_ProxyLightManager*)theWrappedObject)->py_q_getXMLOrder());}
   NamedBean*  py_q_makeBean(ProxyLightManager* theWrappedObject, int  i, QString  systemName, QString  userName){  return (((PythonQtPublicPromoter_ProxyLightManager*)theWrappedObject)->py_q_makeBean(i, systemName, userName));}
   Manager*  py_q_makeInternalManager(ProxyLightManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_ProxyLightManager*)theWrappedObject)->py_q_makeInternalManager());}
   Light*  newLight(ProxyLightManager* theWrappedObject, QString  systemName, QString  userName);
   NamedBean*  newNamedBean(ProxyLightManager* theWrappedObject, QString  systemName, QString  userName);
   QString  py_q_normalizeSystemName(ProxyLightManager* theWrappedObject, QString  systemName){  return (((PythonQtPublicPromoter_ProxyLightManager*)theWrappedObject)->py_q_normalizeSystemName(systemName));}
   Light*  provideLight(ProxyLightManager* theWrappedObject, QString  name);
   bool  supportsVariableLights(ProxyLightManager* theWrappedObject, QString  systemName);
   bool  validSystemNameConfig(ProxyLightManager* theWrappedObject, QString  systemName);
   Manager::NameValidity  py_q_validSystemNameFormat(ProxyLightManager* theWrappedObject, QString  systemName){  return (((PythonQtPublicPromoter_ProxyLightManager*)theWrappedObject)->py_q_validSystemNameFormat(systemName));}
};





class PythonQtShell_ProxySensorManager : public ProxySensorManager
{
public:
    PythonQtShell_ProxySensorManager(QObject*  parent = nullptr):ProxySensorManager(parent),_wrapper(NULL) {}

   ~PythonQtShell_ProxySensorManager();

virtual void Register(NamedBean*  s);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual void deregister(NamedBean*  s);
virtual void dispose();
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual NamedBean*  getBeanBySystemName(QString  systemName);
virtual NamedBean*  getBeanByUserName(QString  userName);
virtual QString  getBeanTypeHandled();
virtual QString  getEntryToolTip();
virtual Manager*  getMgr(int  index);
virtual NamedBean*  getNamedBean(QString  name);
virtual QSet<NamedBean* >  getNamedBeanSet();
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList();
virtual QString  getSystemPrefix();
virtual QStringList  getUserNameList();
virtual int  getXMLOrder();
virtual Sensor*  makeBean(int  i, QString  systemName, QString  userName);
virtual Manager*  makeInternalManager() const;
virtual QString  makeSystemName(QString  s);
virtual int  match(QString  systemname);
virtual int  matchTentative(QString  arg__1);
virtual int  nMgrs();
virtual QString  normalizeSystemName(QString  inputName);
virtual NamedBean*  provideNamedBean(QString  name);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void timerEvent(QTimerEvent*  event);
virtual char  typeLetter();
virtual Manager::NameValidity  validSystemNameFormat(QString  arg__1);
virtual void vetoableChange(PropertyChangeEvent*  evt);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_ProxySensorManager : public ProxySensorManager
{ public:
inline Sensor*  promoted_makeBean(int  i, QString  systemName, QString  userName) { return this->makeBean(i, systemName, userName); }
inline Manager*  promoted_makeInternalManager() const { return this->makeInternalManager(); }
inline int  py_q_getXMLOrder() { return ProxySensorManager::getXMLOrder(); }
inline Sensor*  py_q_makeBean(int  i, QString  systemName, QString  userName) { return ProxySensorManager::makeBean(i, systemName, userName); }
inline Manager*  py_q_makeInternalManager() const { return ProxySensorManager::makeInternalManager(); }
};

class PythonQtWrapper_ProxySensorManager : public QObject
{ Q_OBJECT
public:
public slots:
ProxySensorManager* new_ProxySensorManager(QObject*  parent = nullptr);
void delete_ProxySensorManager(ProxySensorManager* obj) { delete obj; } 
   bool  allowMultipleAdditions(ProxySensorManager* theWrappedObject, QString  systemName);
   QString  createSystemName(ProxySensorManager* theWrappedObject, QString  curAddress, QString  prefix) throw (JmriException);
   Sensor*  getBySystemName(ProxySensorManager* theWrappedObject, QString  sName);
   Sensor*  getByUserName(ProxySensorManager* theWrappedObject, QString  userName);
   QCompleter*  getCompleter(ProxySensorManager* theWrappedObject, QString  text);
   long  getDefaultSensorDebounceGoingActive(ProxySensorManager* theWrappedObject);
   long  getDefaultSensorDebounceGoingInActive(ProxySensorManager* theWrappedObject);
   QString  getNextValidAddress(ProxySensorManager* theWrappedObject, QString  curAddress, QString  prefix) throw (JmriException);
   Sensor*  getSensor(ProxySensorManager* theWrappedObject, QString  name);
   int  py_q_getXMLOrder(ProxySensorManager* theWrappedObject){  return (((PythonQtPublicPromoter_ProxySensorManager*)theWrappedObject)->py_q_getXMLOrder());}
   Sensor*  py_q_makeBean(ProxySensorManager* theWrappedObject, int  i, QString  systemName, QString  userName){  return (((PythonQtPublicPromoter_ProxySensorManager*)theWrappedObject)->py_q_makeBean(i, systemName, userName));}
   Manager*  py_q_makeInternalManager(ProxySensorManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_ProxySensorManager*)theWrappedObject)->py_q_makeInternalManager());}
   Sensor*  newSensor(ProxySensorManager* theWrappedObject, QString  systemName, QString  userName);
   Sensor*  provideSensor(ProxySensorManager* theWrappedObject, QString  sName);
   void setDefaultSensorDebounceGoingActive(ProxySensorManager* theWrappedObject, long  timer);
   void setDefaultSensorDebounceGoingInActive(ProxySensorManager* theWrappedObject, long  timer);
   void updateAll(ProxySensorManager* theWrappedObject);
};





class PythonQtShell_ProxyTurnoutManager : public ProxyTurnoutManager
{
public:
    PythonQtShell_ProxyTurnoutManager(QObject*  parent = 0):ProxyTurnoutManager(parent),_wrapper(NULL) {}

   ~PythonQtShell_ProxyTurnoutManager();

virtual void Register(NamedBean*  s);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual void deregister(NamedBean*  s);
virtual void dispose();
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual NamedBean*  getBeanBySystemName(QString  systemName);
virtual NamedBean*  getBeanByUserName(QString  userName);
virtual QString  getBeanTypeHandled();
virtual QString  getEntryToolTip();
virtual Manager*  getMgr(int  index);
virtual NamedBean*  getNamedBean(QString  name);
virtual QSet<NamedBean* >  getNamedBeanSet();
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList();
virtual QString  getSystemPrefix();
virtual QStringList  getUserNameList();
virtual int  getXMLOrder();
virtual NamedBean*  makeBean(int  i, QString  systemName, QString  userName);
virtual Manager*  makeInternalManager() const;
virtual QString  makeSystemName(QString  s);
virtual int  match(QString  systemname);
virtual int  matchTentative(QString  arg__1);
virtual int  nMgrs();
virtual QString  normalizeSystemName(QString  inputName);
virtual NamedBean*  provideNamedBean(QString  name);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void timerEvent(QTimerEvent*  event);
virtual char  typeLetter();
virtual Manager::NameValidity  validSystemNameFormat(QString  arg__1);
virtual void vetoableChange(PropertyChangeEvent*  evt);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_ProxyTurnoutManager : public ProxyTurnoutManager
{ public:
inline NamedBean*  promoted_makeBean(int  i, QString  systemName, QString  userName) { return this->makeBean(i, systemName, userName); }
inline Manager*  promoted_makeInternalManager() const { return this->makeInternalManager(); }
inline int  py_q_getXMLOrder() { return ProxyTurnoutManager::getXMLOrder(); }
inline NamedBean*  py_q_makeBean(int  i, QString  systemName, QString  userName) { return ProxyTurnoutManager::makeBean(i, systemName, userName); }
inline Manager*  py_q_makeInternalManager() const { return ProxyTurnoutManager::makeInternalManager(); }
};

class PythonQtWrapper_ProxyTurnoutManager : public QObject
{ Q_OBJECT
public:
public slots:
ProxyTurnoutManager* new_ProxyTurnoutManager(QObject*  parent = 0);
void delete_ProxyTurnoutManager(ProxyTurnoutManager* obj) { delete obj; } 
   void addManager(ProxyTurnoutManager* theWrappedObject, Manager*  m);
   bool  allowMultipleAdditions(ProxyTurnoutManager* theWrappedObject, QString  systemName);
   int  askControlType(ProxyTurnoutManager* theWrappedObject, QString  systemName);
   int  askNumControlBits(ProxyTurnoutManager* theWrappedObject, QString  systemName);
   QString  createSystemName(ProxyTurnoutManager* theWrappedObject, QString  curAddress, QString  prefix) throw (JmriException);
   Turnout*  getBySystemName(ProxyTurnoutManager* theWrappedObject, QString  systemName);
   Turnout*  getByUserName(ProxyTurnoutManager* theWrappedObject, QString  userName);
   QString  getClosedText(ProxyTurnoutManager* theWrappedObject);
   QCompleter*  getCompleter(ProxyTurnoutManager* theWrappedObject, QString  text);
   QString  getDefaultClosedSpeed(ProxyTurnoutManager* theWrappedObject);
   QString  getDefaultThrownSpeed(ProxyTurnoutManager* theWrappedObject);
   QString  getNextValidAddress(ProxyTurnoutManager* theWrappedObject, QString  curAddress, QString  prefix) throw (JmriException);
   QString  getThrownText(ProxyTurnoutManager* theWrappedObject);
   Turnout*  getTurnout(ProxyTurnoutManager* theWrappedObject, QString  name);
   QStringList  getValidOperationTypes(ProxyTurnoutManager* theWrappedObject);
   int  py_q_getXMLOrder(ProxyTurnoutManager* theWrappedObject){  return (((PythonQtPublicPromoter_ProxyTurnoutManager*)theWrappedObject)->py_q_getXMLOrder());}
   bool  isControlTypeSupported(ProxyTurnoutManager* theWrappedObject, QString  systemName);
   bool  isNumControlBitsSupported(ProxyTurnoutManager* theWrappedObject, QString  systemName);
   NamedBean*  py_q_makeBean(ProxyTurnoutManager* theWrappedObject, int  i, QString  systemName, QString  userName){  return (((PythonQtPublicPromoter_ProxyTurnoutManager*)theWrappedObject)->py_q_makeBean(i, systemName, userName));}
   Manager*  py_q_makeInternalManager(ProxyTurnoutManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_ProxyTurnoutManager*)theWrappedObject)->py_q_makeInternalManager());}
   Turnout*  newTurnout(ProxyTurnoutManager* theWrappedObject, QString  systemName, QString  userName);
   void setDefaultClosedSpeed(ProxyTurnoutManager* theWrappedObject, QString  speed) throw (JmriException);
   void setDefaultThrownSpeed(ProxyTurnoutManager* theWrappedObject, QString  speed) throw (JmriException);
};





class PythonQtShell_ReporterManager : public ReporterManager
{
public:
    PythonQtShell_ReporterManager(QObject*  parent = 0):ReporterManager(parent),_wrapper(NULL) {}

   ~PythonQtShell_ReporterManager();

virtual void Register(NamedBean*  s);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual bool  allowMultipleAdditions(QString  arg__1) const;
virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual void deregister(NamedBean*  s);
virtual void dispose();
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual NamedBean*  getBeanBySystemName(QString  systemName);
virtual NamedBean*  getBeanByUserName(QString  userName);
virtual QString  getBeanTypeHandled();
virtual QString  getEntryToolTip();
virtual NamedBean*  getNamedBean(QString  name);
virtual QSet<NamedBean* >  getNamedBeanSet();
virtual QString  getNextValidAddress(QString  arg__1, QString  arg__2) const;
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList() const;
virtual QString  getSystemPrefix();
virtual int  getXMLOrder();
virtual QString  makeSystemName(QString  s);
virtual QString  normalizeSystemName(QString  inputName);
virtual void propertyChange(PropertyChangeEvent*  e);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void timerEvent(QTimerEvent*  event);
virtual char  typeLetter();
virtual Manager::NameValidity  validSystemNameFormat(QString  arg__1);
virtual void vetoableChange(PropertyChangeEvent*  evt);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_ReporterManager : public ReporterManager
{ public:
inline bool  py_q_allowMultipleAdditions(QString  arg__1) const { return ReporterManager::allowMultipleAdditions(arg__1); }
inline QString  py_q_getNextValidAddress(QString  arg__1, QString  arg__2) const { return ReporterManager::getNextValidAddress(arg__1, arg__2); }
inline QStringList  py_q_getSystemNameList() const { return ReporterManager::getSystemNameList(); }
};

class PythonQtWrapper_ReporterManager : public QObject
{ Q_OBJECT
public:
public slots:
ReporterManager* new_ReporterManager(QObject*  parent = 0);
void delete_ReporterManager(ReporterManager* obj) { delete obj; } 
   bool  allowMultipleAdditions(ReporterManager* theWrappedObject, QString  arg__1) const;
   bool  py_q_allowMultipleAdditions(ReporterManager* theWrappedObject, QString  arg__1) const{  return (((PythonQtPublicPromoter_ReporterManager*)theWrappedObject)->py_q_allowMultipleAdditions(arg__1));}
   QString  getNextValidAddress(ReporterManager* theWrappedObject, QString  arg__1, QString  arg__2) const;
   QString  py_q_getNextValidAddress(ReporterManager* theWrappedObject, QString  arg__1, QString  arg__2) const{  return (((PythonQtPublicPromoter_ReporterManager*)theWrappedObject)->py_q_getNextValidAddress(arg__1, arg__2));}
   QStringList  py_q_getSystemNameList(ReporterManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_ReporterManager*)theWrappedObject)->py_q_getSystemNameList());}
};





class PythonQtShell_RfidSensorManager : public RfidSensorManager
{
public:
    PythonQtShell_RfidSensorManager(QObject*  parent = 0):RfidSensorManager(parent),_wrapper(NULL) {}
    PythonQtShell_RfidSensorManager(QString  prefix, QObject*  parent = 0):RfidSensorManager(prefix, parent),_wrapper(NULL) {}

   ~PythonQtShell_RfidSensorManager();

virtual void Register(NamedBean*  s);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual bool  allowMultipleAdditions(QString  systemName);
virtual void childEvent(QChildEvent*  event);
virtual QString  createSystemName(QString  curAddress, QString  prefix) throw (JmriException);
virtual void customEvent(QEvent*  event);
virtual void deregister(NamedBean*  s);
virtual void dispose();
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual NamedBean*  getBeanBySystemName(QString  systemName);
virtual NamedBean*  getBeanByUserName(QString  userName);
virtual QString  getBeanTypeHandled();
virtual Sensor*  getBySystemName(QString  key);
virtual Sensor*  getByUserName(QString  key);
virtual long  getDefaultSensorDebounceGoingActive();
virtual long  getDefaultSensorDebounceGoingInActive();
virtual QString  getEntryToolTip();
virtual NamedBean*  getNamedBean(QString  name);
virtual QSet<NamedBean* >  getNamedBeanSet();
virtual QString  getNextValidAddress(QString  curAddress, QString  prefix);
virtual Sensor*  getSensor(QString  name);
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList();
virtual QString  getSystemPrefix();
virtual int  getXMLOrder();
virtual QString  makeSystemName(QString  s);
virtual Sensor*  newSensor(QString  sysName, QString  userName);
virtual QString  normalizeSystemName(QString  sysName);
virtual Sensor*  provideSensor(QString  name);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void setDefaultSensorDebounceGoingActive(long  timer);
virtual void setDefaultSensorDebounceGoingInActive(long  timer);
virtual void timerEvent(QTimerEvent*  event);
virtual char  typeLetter();
virtual void updateAll();
virtual Manager::NameValidity  validSystemNameFormat(QString  arg__1);
virtual void vetoableChange(PropertyChangeEvent*  evt);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_RfidSensorManager : public RfidSensorManager
{ public:
inline void py_q_dispose() { RfidSensorManager::dispose(); }
inline QString  py_q_getSystemPrefix() { return RfidSensorManager::getSystemPrefix(); }
};

class PythonQtWrapper_RfidSensorManager : public QObject
{ Q_OBJECT
public:
public slots:
RfidSensorManager* new_RfidSensorManager(QObject*  parent = 0);
RfidSensorManager* new_RfidSensorManager(QString  prefix, QObject*  parent = 0);
void delete_RfidSensorManager(RfidSensorManager* obj) { delete obj; } 
   void py_q_dispose(RfidSensorManager* theWrappedObject){  (((PythonQtPublicPromoter_RfidSensorManager*)theWrappedObject)->py_q_dispose());}
   QString  py_q_getSystemPrefix(RfidSensorManager* theWrappedObject){  return (((PythonQtPublicPromoter_RfidSensorManager*)theWrappedObject)->py_q_getSystemPrefix());}
   void message(RfidSensorManager* theWrappedObject, QString  m);
};


