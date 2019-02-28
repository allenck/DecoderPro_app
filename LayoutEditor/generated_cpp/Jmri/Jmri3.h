#include <PythonQt.h>
#include <QObject>
#include <QVariant>
#include <basicrosterentry.h>
#include <dcclocoaddress.h>
#include <dccthrottle.h>
#include <listselectionmodel.h>
#include <locoaddress.h>
#include <namedbean.h>
#include <propertychangeevent.h>
#include <propertychangelistener.h>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qdatastream.h>
#include <qdatetime.h>
#include <qdom.h>
#include <qevent.h>
#include <qfile.h>
#include <qlocale.h>
#include <qmetaobject.h>
#include <qobject.h>
#include <qstringlist.h>
#include <qurl.h>
#include <qvector.h>
#include <roster.h>
#include <rosterentry.h>
#include <route.h>
#include <routemanager.h>
#include <sensor.h>
#include <sensormanager.h>
#include <serialportadapter.h>
#include <shutdownmanager.h>
#include <shutdowntask.h>
#include <siglet.h>
#include <signalhead.h>
#include <sound.h>
#include <systemconnectionmemo.h>
#include <tablecolumn.h>
#include <tablecolumnmodel.h>
#include <throttle.h>
#include <throttlemanager.h>
#include <turnout.h>
#include <turnoutmanager.h>
#include <turnoutoperation.h>
#include <vetoablechangesupport.h>
#include <windowlistener.h>
#include <xmlfile.h>



class PythonQtShell_Roster : public Roster
{
public:
    PythonQtShell_Roster(QObject*  parent = 0):Roster(parent),_wrapper(NULL) {}
    PythonQtShell_Roster(QString  rosterFilename):Roster(rosterFilename),_wrapper(NULL) {}

   ~PythonQtShell_Roster();

virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtWrapper_Roster : public QObject
{ Q_OBJECT
public:
public slots:
Roster* new_Roster(QObject*  parent = 0);
Roster* new_Roster(QString  rosterFilename);
void delete_Roster(Roster* obj) { delete obj; } 
   QString  static_Roster_AllEntries(QLocale  arg__1);
   QString  static_Roster__AllEntries(QLocale  locale);
   void addEntry(Roster* theWrappedObject, RosterEntry*  e);
   void addPropertyChangeListener(Roster* theWrappedObject, PropertyChangeListener*  l);
   void addPropertyChangeListener(Roster* theWrappedObject, QString  propertyName, PropertyChangeListener*  listener);
   void addRosterGroup(Roster* theWrappedObject, QString  str);
   void addRosterGroup(Roster* theWrappedObject, RosterGroup*  rg);
   bool  checkEntry(Roster* theWrappedObject, QList<RosterEntry* >  list, int  i, QString  roadName, QString  roadNumber, QString  dccAddress, QString  mfg, QString  decoderModel, QString  decoderFamily, QString  id, QString  group);
   bool  checkEntry(Roster* theWrappedObject, int  i, QString  roadName, QString  roadNumber, QString  dccAddress, QString  mfg, QString  decoderModel, QString  decoderFamily, QString  id, QString  group);
   void copyRosterGroupList(Roster* theWrappedObject, QString  oldName, QString  newName);
   void delRosterGroupList(Roster* theWrappedObject, QString  str);
   void dispose(Roster* theWrappedObject);
   RosterEntry*  entryFromTitle(Roster* theWrappedObject, QString  title);
   void entryIdChanged(Roster* theWrappedObject, RosterEntry*  r);
   QString  fileFromTitle(Roster* theWrappedObject, QString  title);
   void firePropertyChange(Roster* theWrappedObject, QString  p, QVariant  old, QVariant  n);
   QSet<QString >  getAllAttributeKeys(Roster* theWrappedObject);
   Roster*  static_Roster_getDefault();
   QString  getDefaultRosterGroup(Roster* theWrappedObject);
   QList<RosterEntry* >  getEntriesInGroup(Roster* theWrappedObject, QString  group);
   QList<RosterEntry* >  getEntriesMatchingCriteria(Roster* theWrappedObject, QString  roadName, QString  roadNumber, QString  dccAddress, QString  mfg, QString  decoderMfgID, QString  decoderVersionID, QString  id, QString  group);
   QList<RosterEntry* >  getEntriesWithAttributeKey(Roster* theWrappedObject, QString  key);
   QList<RosterEntry* >  getEntriesWithAttributeKeyValue(Roster* theWrappedObject, QString  key, QString  value);
   RosterEntry*  getEntry(Roster* theWrappedObject, int  i);
   RosterEntry*  getEntryForId(Roster* theWrappedObject, QString  id);
   RosterEntry*  getGroupEntry(Roster* theWrappedObject, QString  group, int  i);
   int  getGroupIndex(Roster* theWrappedObject, QString  group, RosterEntry*  re);
   QVector<QString >  getRosterGroupList(Roster* theWrappedObject);
   QString  static_Roster_getRosterGroupName(QString  rosterGroup);
   QString  static_Roster_getRosterGroupProperty(QString  name);
   QMap<QString , RosterGroup* >  getRosterGroups(Roster* theWrappedObject);
   QString  getRosterIndexFileName(Roster* theWrappedObject);
   QString  getRosterIndexPath(Roster* theWrappedObject);
   QString  getRosterLocation(Roster* theWrappedObject);
   QString  getSelectedRosterGroup(Roster* theWrappedObject);
   Roster*  static_Roster_instance();
   QString  static_Roster_makeValidFilename(QString  entry);
   QList<RosterEntry* >  matchingList(Roster* theWrappedObject, QString  roadName, QString  roadNumber, QString  dccAddress, QString  mfg, QString  decoderMfgID, QString  decoderVersionID, QString  id);
   int  numEntries(Roster* theWrappedObject);
   int  numGroupEntries(Roster* theWrappedObject, QString  group);
   void reindex(Roster* theWrappedObject);
   void removeEntry(Roster* theWrappedObject, RosterEntry*  e);
   void removePropertyChangeListener(Roster* theWrappedObject, PropertyChangeListener*  l);
   void removePropertyChangeListener(Roster* theWrappedObject, QString  propertyName, PropertyChangeListener*  listener);
   void renameRosterGroupList(Roster* theWrappedObject, QString  oldName, QString  newName);
   void rosterGroupRenamed(Roster* theWrappedObject, QString  oldName, QString  newName);
   void setDefaultRosterGroup(Roster* theWrappedObject, QString  defaultRosterGroup);
   void setRosterIndexFileName(Roster* theWrappedObject, QString  fileName);
   void setRosterLocation(Roster* theWrappedObject, QString  f);
   void writeFile(Roster* theWrappedObject, QFile*  file);
   void writeFile(Roster* theWrappedObject, QString  name);
   void writeRoster(Roster* theWrappedObject);
void py_set_pcs(Roster* theWrappedObject, PropertyChangeSupport*  pcs){ theWrappedObject->pcs = pcs; }
PropertyChangeSupport*  py_get_pcs(Roster* theWrappedObject){ return theWrappedObject->pcs; }
};





class PythonQtShell_RosterEntry : public RosterEntry
{
public:
    PythonQtShell_RosterEntry(QDomElement  e):RosterEntry(e),_wrapper(NULL) {}
    PythonQtShell_RosterEntry(QObject*  parent = 0):RosterEntry(parent),_wrapper(NULL) {}
    PythonQtShell_RosterEntry(QString  fileName, QObject*  parent = 0):RosterEntry(fileName, parent),_wrapper(NULL) {}
    PythonQtShell_RosterEntry(RosterEntry*  pEntry, QString  pID, QObject*  parent = 0):RosterEntry(pEntry, pID, parent),_wrapper(NULL) {}
    PythonQtShell_RosterEntry(const RosterEntry&  arg__1):RosterEntry(arg__1),_wrapper(NULL) {}

   ~PythonQtShell_RosterEntry();

virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual void deleteAttribute(QString  key);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual QString  getAttribute(QString  key);
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
virtual void timerEvent(QTimerEvent*  event);
virtual QString  titleString();
virtual QString  toString();

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_RosterEntry : public RosterEntry
{ public:
inline QDomElement  promoted_createTextElement(QDomDocument  doc, QString  tagName, QString  text) { return this->createTextElement(doc, tagName, text); }
inline void py_q_deleteAttribute(QString  key) { RosterEntry::deleteAttribute(key); }
inline QString  py_q_getAttribute(QString  key) { return RosterEntry::getAttribute(key); }
inline QStringList  py_q_getAttributeList() { return RosterEntry::getAttributeList(); }
inline QString  py_q_getDccAddress() { return RosterEntry::getDccAddress(); }
inline DccLocoAddress*  py_q_getDccLocoAddress() { return RosterEntry::getDccLocoAddress(); }
inline QString  py_q_getId() { return RosterEntry::getId(); }
inline int  py_q_getMaxSpeedPCT() { return RosterEntry::getMaxSpeedPCT(); }
inline QString  py_q_getShuntingFunction() { return RosterEntry::getShuntingFunction(); }
inline bool  py_q_isLongAddress() { return RosterEntry::isLongAddress(); }
inline bool  py_q_isOpen() { return RosterEntry::isOpen(); }
inline void py_q_putAttribute(QString  key, QString  value) { RosterEntry::putAttribute(key, value); }
inline void py_q_setOpen(bool  boo) { RosterEntry::setOpen(boo); }
inline QString  py_q_titleString() { return RosterEntry::titleString(); }
inline QString  py_q_toString() { return RosterEntry::toString(); }
};

class PythonQtWrapper_RosterEntry : public QObject
{ Q_OBJECT
public:
public slots:
RosterEntry* new_RosterEntry(QDomElement  e);
RosterEntry* new_RosterEntry(QObject*  parent = 0);
RosterEntry* new_RosterEntry(QString  fileName, QObject*  parent = 0);
RosterEntry* new_RosterEntry(RosterEntry*  pEntry, QString  pID, QObject*  parent = 0);
RosterEntry* new_RosterEntry(const RosterEntry&  arg__1);
void delete_RosterEntry(RosterEntry* obj) { delete obj; } 
   void addPropertyChangeListener(RosterEntry* theWrappedObject, PropertyChangeListener*  l);
   void changeDateUpdated(RosterEntry* theWrappedObject);
   QDomElement  createTextElement(RosterEntry* theWrappedObject, QDomDocument  doc, QString  tagName, QString  text);
   void py_q_deleteAttribute(RosterEntry* theWrappedObject, QString  key){  (((PythonQtPublicPromoter_RosterEntry*)theWrappedObject)->py_q_deleteAttribute(key));}
   void ensureFilenameExists(RosterEntry* theWrappedObject);
   void firePropertyChange(RosterEntry* theWrappedObject, QString  p, QVariant  old, QVariant  n);
   LocoAddress*  getAddress(RosterEntry* theWrappedObject, QDomElement  element);
   QString  py_q_getAttribute(RosterEntry* theWrappedObject, QString  key){  return (((PythonQtPublicPromoter_RosterEntry*)theWrappedObject)->py_q_getAttribute(key));}
   QStringList  py_q_getAttributeList(RosterEntry* theWrappedObject){  return (((PythonQtPublicPromoter_RosterEntry*)theWrappedObject)->py_q_getAttributeList());}
   QSet<QString >  getAttributes(RosterEntry* theWrappedObject);
   QString  getComment(RosterEntry* theWrappedObject);
   QDateTime  getDateModified(RosterEntry* theWrappedObject);
   QString  getDateUpdated(RosterEntry* theWrappedObject);
   QString  py_q_getDccAddress(RosterEntry* theWrappedObject){  return (((PythonQtPublicPromoter_RosterEntry*)theWrappedObject)->py_q_getDccAddress());}
   DccLocoAddress*  py_q_getDccLocoAddress(RosterEntry* theWrappedObject){  return (((PythonQtPublicPromoter_RosterEntry*)theWrappedObject)->py_q_getDccLocoAddress());}
   QString  getDecoderComment(RosterEntry* theWrappedObject);
   QString  getDecoderFamily(RosterEntry* theWrappedObject);
   QString  getDecoderModel(RosterEntry* theWrappedObject);
   QString  static_RosterEntry_getDefaultOwner();
   QString  getFileName(RosterEntry* theWrappedObject);
   QString  getFunctionImage(RosterEntry* theWrappedObject, int  fn);
   QString  getFunctionLabel(RosterEntry* theWrappedObject, int  fn);
   bool  getFunctionLockable(RosterEntry* theWrappedObject, int  fn);
   QString  getFunctionSelectedImage(RosterEntry* theWrappedObject, int  fn);
   QList<RosterGroup* >  getGroups(RosterEntry* theWrappedObject);
   QList<RosterGroup* >  getGroups(RosterEntry* theWrappedObject, Roster*  roster);
   QString  getIconPath(RosterEntry* theWrappedObject);
   QString  py_q_getId(RosterEntry* theWrappedObject){  return (((PythonQtPublicPromoter_RosterEntry*)theWrappedObject)->py_q_getId());}
   QString  getImagePath(RosterEntry* theWrappedObject);
   int  getMAXFNNUM(RosterEntry* theWrappedObject);
   int  py_q_getMaxSpeedPCT(RosterEntry* theWrappedObject){  return (((PythonQtPublicPromoter_RosterEntry*)theWrappedObject)->py_q_getMaxSpeedPCT());}
   QString  getMfg(RosterEntry* theWrappedObject);
   QString  getModel(RosterEntry* theWrappedObject);
   QString  getOwner(RosterEntry* theWrappedObject);
   QString  getPathName(RosterEntry* theWrappedObject);
   LocoAddress::Protocol  getProtocol(RosterEntry* theWrappedObject);
   QString  getProtocolAsString(RosterEntry* theWrappedObject);
   int  getRfidTag(RosterEntry* theWrappedObject);
   QString  getRoadName(RosterEntry* theWrappedObject);
   QString  getRoadNumber(RosterEntry* theWrappedObject);
   QString  py_q_getShuntingFunction(RosterEntry* theWrappedObject){  return (((PythonQtPublicPromoter_RosterEntry*)theWrappedObject)->py_q_getShuntingFunction());}
   QString  getSoundLabel(RosterEntry* theWrappedObject, int  fn);
   QString  getURL(RosterEntry* theWrappedObject);
   bool  py_q_isLongAddress(RosterEntry* theWrappedObject){  return (((PythonQtPublicPromoter_RosterEntry*)theWrappedObject)->py_q_isLongAddress());}
   bool  py_q_isOpen(RosterEntry* theWrappedObject){  return (((PythonQtPublicPromoter_RosterEntry*)theWrappedObject)->py_q_isOpen());}
   void loadAttributes(RosterEntry* theWrappedObject, QDomElement  e3);
   void loadFunctions(RosterEntry* theWrappedObject, QDomElement  e3);
   void py_q_putAttribute(RosterEntry* theWrappedObject, QString  key, QString  value){  (((PythonQtPublicPromoter_RosterEntry*)theWrappedObject)->py_q_putAttribute(key, value));}
   void readFile(RosterEntry* theWrappedObject);
   void removePropertyChangeListener(RosterEntry* theWrappedObject, PropertyChangeListener*  l);
   void setComment(RosterEntry* theWrappedObject, QString  s);
   void setDateModified(RosterEntry* theWrappedObject, QDateTime  date);
   void setDateModified(RosterEntry* theWrappedObject, QString  date) throw (ParseException) ;
   void setDateUpdated(RosterEntry* theWrappedObject, QString  s);
   void setDccAddress(RosterEntry* theWrappedObject, QString  s);
   void setDecoderComment(RosterEntry* theWrappedObject, QString  s);
   void setDecoderFamily(RosterEntry* theWrappedObject, QString  s);
   void setDecoderModel(RosterEntry* theWrappedObject, QString  s);
   void static_RosterEntry_setDefaultOwner(QString  n);
   void setFileName(RosterEntry* theWrappedObject, QString  s);
   void setFunctionImage(RosterEntry* theWrappedObject, int  fn, QString  s);
   void setFunctionLabel(RosterEntry* theWrappedObject, int  fn, QString  label);
   void setFunctionLockable(RosterEntry* theWrappedObject, int  fn, bool  lockable);
   void setFunctionSelectedImage(RosterEntry* theWrappedObject, int  fn, QString  s);
   void setIconPath(RosterEntry* theWrappedObject, QString  s);
   void setId(RosterEntry* theWrappedObject, QString  s);
   void setImagePath(RosterEntry* theWrappedObject, QString  s);
   void setLongAddress(RosterEntry* theWrappedObject, bool  b);
   void setMaxSpeedPCT(RosterEntry* theWrappedObject, int  maxSpeedPCT);
   void setMfg(RosterEntry* theWrappedObject, QString  s);
   void setModel(RosterEntry* theWrappedObject, QString  s);
   void py_q_setOpen(RosterEntry* theWrappedObject, bool  boo){  (((PythonQtPublicPromoter_RosterEntry*)theWrappedObject)->py_q_setOpen(boo));}
   void setOwner(RosterEntry* theWrappedObject, QString  s);
   void setProtocol(RosterEntry* theWrappedObject, LocoAddress::Protocol  protocol);
   void setRfidTag(RosterEntry* theWrappedObject, QString  tag);
   void setRoadName(RosterEntry* theWrappedObject, QString  s);
   void setRoadNumber(RosterEntry* theWrappedObject, QString  s);
   void setShuntingFunction(RosterEntry* theWrappedObject, QString  fn);
   void setSoundLabel(RosterEntry* theWrappedObject, int  fn, QString  label);
   void setURL(RosterEntry* theWrappedObject, QString  s);
   QDomElement  store(RosterEntry* theWrappedObject, QDomDocument  doc);
   QString  py_q_titleString(RosterEntry* theWrappedObject){  return (((PythonQtPublicPromoter_RosterEntry*)theWrappedObject)->py_q_titleString());}
   QString  py_q_toString(RosterEntry* theWrappedObject){  return (((PythonQtPublicPromoter_RosterEntry*)theWrappedObject)->py_q_toString());}
   void updateFile(RosterEntry* theWrappedObject);
   void warnShortLong(RosterEntry* theWrappedObject, QString  id);
   QVector<QString >  wrapComment(RosterEntry* theWrappedObject, QString  comment, int  textSpace);
    QString py_toString(RosterEntry*);
};





class PythonQtShell_Route : public Route
{
public:
    PythonQtShell_Route(QString  systemName, QString  userName = "", QObject*  parent = 0):Route(systemName, userName, parent),_wrapper(NULL) {}

   ~PythonQtShell_Route();

virtual void activateRoute();
virtual bool  addOutputSensor(QString  arg__1, int  arg__2);
virtual bool  addOutputTurnout(QString  arg__1, int  arg__2);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(PropertyChangeListener*  l, QString  beanRef, const QString  listenerRef);
virtual bool  addSensorToRoute(QString  arg__1, int  arg__2);
virtual bool  canLock();
virtual void childEvent(QChildEvent*  event);
virtual void clearOutputSensors();
virtual void clearOutputTurnouts();
virtual void clearRouteSensors();
virtual int  compareSystemNameSuffix(QString  suffix1, QString  suffix2, NamedBean*  n);
virtual int  compareTo(NamedBean*  n2);
virtual void customEvent(QEvent*  event);
virtual void deActivateRoute();
virtual QString  describeState(int  state);
virtual void dispose();
virtual bool  equals(QObject*  obj);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual QString  getBeanType();
virtual QString  getComment();
virtual QString  getControlTurnout();
virtual int  getControlTurnoutState();
virtual Turnout*  getCtlTurnout();
virtual QString  getDisplayName();
virtual bool  getEnabled();
virtual QString  getFullyFormattedDisplayName();
virtual QString  getListenerRef(PropertyChangeListener*  l);
virtual QList<QString >*  getListenerRefs();
virtual QString  getLockControlTurnout();
virtual int  getLockControlTurnoutState();
virtual Turnout*  getLockCtlTurnout();
virtual bool  getLocked();
virtual int  getNumOutputSensors();
virtual int  getNumOutputTurnouts();
virtual int  getNumPropertyChangeListeners();
virtual QString  getOutputScriptName();
virtual Sensor*  getOutputSensor(int  arg__1);
virtual QString  getOutputSensorByIndex(int  arg__1);
virtual int  getOutputSensorSetState(QString  arg__1);
virtual int  getOutputSensorState(int  k);
virtual QString  getOutputSoundName();
virtual Turnout*  getOutputTurnout(int  arg__1);
virtual QString  getOutputTurnoutByIndex(int  arg__1);
virtual int  getOutputTurnoutSetState(QString  arg__1);
virtual int  getOutputTurnoutState(int  k);
virtual QVariant  getProperty(QString  key);
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners();
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners(QString  name);
virtual QSet<QString >  getPropertyKeys();
virtual int  getRouteCommandDelay();
virtual Sensor*  getRouteSensor(int  arg__1);
virtual int  getRouteSensorMode(int  index);
virtual QString  getRouteSensorName(int  arg__1);
virtual int  getState();
virtual QString  getSystemName() const;
virtual Sensor*  getTurnoutsAlgdSensor();
virtual QString  getTurnoutsAlignedSensor();
virtual QString  getUserName();
virtual bool  hashCode();
virtual bool  isOutputSensorIncluded(QString  arg__1);
virtual bool  isOutputTurnoutIncluded(QString  arg__1);
virtual void removeProperty(QString  key);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void setComment(QString  comment);
virtual void setControlTurnout(QString  arg__1);
virtual void setControlTurnoutState(int  arg__1);
virtual void setEnabled(bool  arg__1);
virtual void setLockControlTurnout(QString  arg__1);
virtual void setLockControlTurnoutState(int  arg__1);
virtual void setLocked(bool  arg__1);
virtual void setOutputScriptName(QString  arg__1);
virtual void setOutputSoundName(QString  arg__1);
virtual void setProperty(QString  key, QVariant  value);
virtual void setRoute();
virtual void setRouteCommandDelay(int  arg__1);
virtual void setState(int  arg__1);
virtual void setSysName(QString  s);
virtual void setTurnoutsAlignedSensor(QString  arg__1);
virtual void setUserName(QString  s);
virtual void timerEvent(QTimerEvent*  event);
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);
virtual void vetoableChange(PropertyChangeEvent*  evt) throw (PropertyVetoException);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_Route : public Route
{ public:
inline void py_q_activateRoute() { Route::activateRoute(); }
inline bool  py_q_addOutputSensor(QString  arg__1, int  arg__2) { return Route::addOutputSensor(arg__1, arg__2); }
inline bool  py_q_addOutputTurnout(QString  arg__1, int  arg__2) { return Route::addOutputTurnout(arg__1, arg__2); }
inline bool  py_q_addSensorToRoute(QString  arg__1, int  arg__2) { return Route::addSensorToRoute(arg__1, arg__2); }
inline bool  py_q_canLock() { return Route::canLock(); }
inline void py_q_clearOutputSensors() { Route::clearOutputSensors(); }
inline void py_q_clearOutputTurnouts() { Route::clearOutputTurnouts(); }
inline void py_q_clearRouteSensors() { Route::clearRouteSensors(); }
inline void py_q_deActivateRoute() { Route::deActivateRoute(); }
inline QString  py_q_getControlTurnout() { return Route::getControlTurnout(); }
inline int  py_q_getControlTurnoutState() { return this->getControlTurnoutState(); }
inline Turnout*  py_q_getCtlTurnout() { return Route::getCtlTurnout(); }
inline bool  py_q_getEnabled() { return Route::getEnabled(); }
inline QString  py_q_getLockControlTurnout() { return Route::getLockControlTurnout(); }
inline int  py_q_getLockControlTurnoutState() { return this->getLockControlTurnoutState(); }
inline Turnout*  py_q_getLockCtlTurnout() { return Route::getLockCtlTurnout(); }
inline bool  py_q_getLocked() { return Route::getLocked(); }
inline int  py_q_getNumOutputSensors() { return Route::getNumOutputSensors(); }
inline int  py_q_getNumOutputTurnouts() { return this->getNumOutputTurnouts(); }
inline QString  py_q_getOutputScriptName() { return Route::getOutputScriptName(); }
inline Sensor*  py_q_getOutputSensor(int  arg__1) { return Route::getOutputSensor(arg__1); }
inline QString  py_q_getOutputSensorByIndex(int  arg__1) { return Route::getOutputSensorByIndex(arg__1); }
inline int  py_q_getOutputSensorSetState(QString  arg__1) { return Route::getOutputSensorSetState(arg__1); }
inline int  py_q_getOutputSensorState(int  k) { return this->getOutputSensorState(k); }
inline QString  py_q_getOutputSoundName() { return Route::getOutputSoundName(); }
inline Turnout*  py_q_getOutputTurnout(int  arg__1) { return Route::getOutputTurnout(arg__1); }
inline QString  py_q_getOutputTurnoutByIndex(int  arg__1) { return Route::getOutputTurnoutByIndex(arg__1); }
inline int  py_q_getOutputTurnoutSetState(QString  arg__1) { return this->getOutputTurnoutSetState(arg__1); }
inline int  py_q_getOutputTurnoutState(int  k) { return this->getOutputTurnoutState(k); }
inline int  py_q_getRouteCommandDelay() { return this->getRouteCommandDelay(); }
inline Sensor*  py_q_getRouteSensor(int  arg__1) { return Route::getRouteSensor(arg__1); }
inline int  py_q_getRouteSensorMode(int  index) { return this->getRouteSensorMode(index); }
inline QString  py_q_getRouteSensorName(int  arg__1) { return Route::getRouteSensorName(arg__1); }
inline Sensor*  py_q_getTurnoutsAlgdSensor() { return Route::getTurnoutsAlgdSensor(); }
inline QString  py_q_getTurnoutsAlignedSensor() { return Route::getTurnoutsAlignedSensor(); }
inline bool  py_q_isOutputSensorIncluded(QString  arg__1) { return Route::isOutputSensorIncluded(arg__1); }
inline bool  py_q_isOutputTurnoutIncluded(QString  arg__1) { return Route::isOutputTurnoutIncluded(arg__1); }
inline void py_q_setControlTurnout(QString  arg__1) { Route::setControlTurnout(arg__1); }
inline void py_q_setControlTurnoutState(int  arg__1) { Route::setControlTurnoutState(arg__1); }
inline void py_q_setEnabled(bool  arg__1) { Route::setEnabled(arg__1); }
inline void py_q_setLockControlTurnout(QString  arg__1) { Route::setLockControlTurnout(arg__1); }
inline void py_q_setLockControlTurnoutState(int  arg__1) { Route::setLockControlTurnoutState(arg__1); }
inline void py_q_setLocked(bool  arg__1) { Route::setLocked(arg__1); }
inline void py_q_setOutputScriptName(QString  arg__1) { Route::setOutputScriptName(arg__1); }
inline void py_q_setOutputSoundName(QString  arg__1) { Route::setOutputSoundName(arg__1); }
inline void py_q_setRoute() { Route::setRoute(); }
inline void py_q_setRouteCommandDelay(int  arg__1) { Route::setRouteCommandDelay(arg__1); }
inline void py_q_setTurnoutsAlignedSensor(QString  arg__1) { Route::setTurnoutsAlignedSensor(arg__1); }
};

class PythonQtWrapper_Route : public QObject
{ Q_OBJECT
public:
public slots:
Route* new_Route(QString  systemName, QString  userName = "", QObject*  parent = 0);
void delete_Route(Route* obj) { delete obj; } 
   void activateRoute(Route* theWrappedObject);
   void py_q_activateRoute(Route* theWrappedObject){  (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_activateRoute());}
   bool  addOutputSensor(Route* theWrappedObject, QString  arg__1, int  arg__2);
   bool  py_q_addOutputSensor(Route* theWrappedObject, QString  arg__1, int  arg__2){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_addOutputSensor(arg__1, arg__2));}
   bool  addOutputTurnout(Route* theWrappedObject, QString  arg__1, int  arg__2);
   bool  py_q_addOutputTurnout(Route* theWrappedObject, QString  arg__1, int  arg__2){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_addOutputTurnout(arg__1, arg__2));}
   bool  addSensorToRoute(Route* theWrappedObject, QString  arg__1, int  arg__2);
   bool  py_q_addSensorToRoute(Route* theWrappedObject, QString  arg__1, int  arg__2){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_addSensorToRoute(arg__1, arg__2));}
   bool  canLock(Route* theWrappedObject);
   bool  py_q_canLock(Route* theWrappedObject){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_canLock());}
   void clearOutputSensors(Route* theWrappedObject);
   void py_q_clearOutputSensors(Route* theWrappedObject){  (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_clearOutputSensors());}
   void clearOutputTurnouts(Route* theWrappedObject);
   void py_q_clearOutputTurnouts(Route* theWrappedObject){  (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_clearOutputTurnouts());}
   void clearRouteSensors(Route* theWrappedObject);
   void py_q_clearRouteSensors(Route* theWrappedObject){  (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_clearRouteSensors());}
   void deActivateRoute(Route* theWrappedObject);
   void py_q_deActivateRoute(Route* theWrappedObject){  (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_deActivateRoute());}
   QString  getControlTurnout(Route* theWrappedObject);
   QString  py_q_getControlTurnout(Route* theWrappedObject){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_getControlTurnout());}
   int  getControlTurnoutState(Route* theWrappedObject);
   int  py_q_getControlTurnoutState(Route* theWrappedObject){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_getControlTurnoutState());}
   Turnout*  getCtlTurnout(Route* theWrappedObject);
   Turnout*  py_q_getCtlTurnout(Route* theWrappedObject){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_getCtlTurnout());}
   bool  getEnabled(Route* theWrappedObject);
   bool  py_q_getEnabled(Route* theWrappedObject){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_getEnabled());}
   QString  getLockControlTurnout(Route* theWrappedObject);
   QString  py_q_getLockControlTurnout(Route* theWrappedObject){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_getLockControlTurnout());}
   int  getLockControlTurnoutState(Route* theWrappedObject);
   int  py_q_getLockControlTurnoutState(Route* theWrappedObject){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_getLockControlTurnoutState());}
   Turnout*  getLockCtlTurnout(Route* theWrappedObject);
   Turnout*  py_q_getLockCtlTurnout(Route* theWrappedObject){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_getLockCtlTurnout());}
   bool  getLocked(Route* theWrappedObject);
   bool  py_q_getLocked(Route* theWrappedObject){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_getLocked());}
   int  getNumOutputSensors(Route* theWrappedObject);
   int  py_q_getNumOutputSensors(Route* theWrappedObject){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_getNumOutputSensors());}
   int  getNumOutputTurnouts(Route* theWrappedObject);
   int  py_q_getNumOutputTurnouts(Route* theWrappedObject){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_getNumOutputTurnouts());}
   QString  getOutputScriptName(Route* theWrappedObject);
   QString  py_q_getOutputScriptName(Route* theWrappedObject){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_getOutputScriptName());}
   Sensor*  getOutputSensor(Route* theWrappedObject, int  arg__1);
   Sensor*  py_q_getOutputSensor(Route* theWrappedObject, int  arg__1){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_getOutputSensor(arg__1));}
   QString  getOutputSensorByIndex(Route* theWrappedObject, int  arg__1);
   QString  py_q_getOutputSensorByIndex(Route* theWrappedObject, int  arg__1){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_getOutputSensorByIndex(arg__1));}
   int  getOutputSensorSetState(Route* theWrappedObject, QString  arg__1);
   int  py_q_getOutputSensorSetState(Route* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_getOutputSensorSetState(arg__1));}
   int  getOutputSensorState(Route* theWrappedObject, int  k);
   int  py_q_getOutputSensorState(Route* theWrappedObject, int  k){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_getOutputSensorState(k));}
   QString  getOutputSoundName(Route* theWrappedObject);
   QString  py_q_getOutputSoundName(Route* theWrappedObject){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_getOutputSoundName());}
   Turnout*  getOutputTurnout(Route* theWrappedObject, int  arg__1);
   Turnout*  py_q_getOutputTurnout(Route* theWrappedObject, int  arg__1){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_getOutputTurnout(arg__1));}
   QString  getOutputTurnoutByIndex(Route* theWrappedObject, int  arg__1);
   QString  py_q_getOutputTurnoutByIndex(Route* theWrappedObject, int  arg__1){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_getOutputTurnoutByIndex(arg__1));}
   int  getOutputTurnoutSetState(Route* theWrappedObject, QString  arg__1);
   int  py_q_getOutputTurnoutSetState(Route* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_getOutputTurnoutSetState(arg__1));}
   int  getOutputTurnoutState(Route* theWrappedObject, int  k);
   int  py_q_getOutputTurnoutState(Route* theWrappedObject, int  k){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_getOutputTurnoutState(k));}
   int  getRouteCommandDelay(Route* theWrappedObject);
   int  py_q_getRouteCommandDelay(Route* theWrappedObject){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_getRouteCommandDelay());}
   Sensor*  getRouteSensor(Route* theWrappedObject, int  arg__1);
   Sensor*  py_q_getRouteSensor(Route* theWrappedObject, int  arg__1){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_getRouteSensor(arg__1));}
   int  getRouteSensorMode(Route* theWrappedObject, int  index);
   int  py_q_getRouteSensorMode(Route* theWrappedObject, int  index){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_getRouteSensorMode(index));}
   QString  getRouteSensorName(Route* theWrappedObject, int  arg__1);
   QString  py_q_getRouteSensorName(Route* theWrappedObject, int  arg__1){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_getRouteSensorName(arg__1));}
   Sensor*  getTurnoutsAlgdSensor(Route* theWrappedObject);
   Sensor*  py_q_getTurnoutsAlgdSensor(Route* theWrappedObject){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_getTurnoutsAlgdSensor());}
   QString  getTurnoutsAlignedSensor(Route* theWrappedObject);
   QString  py_q_getTurnoutsAlignedSensor(Route* theWrappedObject){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_getTurnoutsAlignedSensor());}
   bool  isOutputSensorIncluded(Route* theWrappedObject, QString  arg__1);
   bool  py_q_isOutputSensorIncluded(Route* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_isOutputSensorIncluded(arg__1));}
   bool  isOutputTurnoutIncluded(Route* theWrappedObject, QString  arg__1);
   bool  py_q_isOutputTurnoutIncluded(Route* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_isOutputTurnoutIncluded(arg__1));}
   void setControlTurnout(Route* theWrappedObject, QString  arg__1);
   void py_q_setControlTurnout(Route* theWrappedObject, QString  arg__1){  (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_setControlTurnout(arg__1));}
   void setControlTurnoutState(Route* theWrappedObject, int  arg__1);
   void py_q_setControlTurnoutState(Route* theWrappedObject, int  arg__1){  (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_setControlTurnoutState(arg__1));}
   void setEnabled(Route* theWrappedObject, bool  arg__1);
   void py_q_setEnabled(Route* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_setEnabled(arg__1));}
   void setLockControlTurnout(Route* theWrappedObject, QString  arg__1);
   void py_q_setLockControlTurnout(Route* theWrappedObject, QString  arg__1){  (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_setLockControlTurnout(arg__1));}
   void setLockControlTurnoutState(Route* theWrappedObject, int  arg__1);
   void py_q_setLockControlTurnoutState(Route* theWrappedObject, int  arg__1){  (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_setLockControlTurnoutState(arg__1));}
   void setLocked(Route* theWrappedObject, bool  arg__1);
   void py_q_setLocked(Route* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_setLocked(arg__1));}
   void setOutputScriptName(Route* theWrappedObject, QString  arg__1);
   void py_q_setOutputScriptName(Route* theWrappedObject, QString  arg__1){  (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_setOutputScriptName(arg__1));}
   void setOutputSoundName(Route* theWrappedObject, QString  arg__1);
   void py_q_setOutputSoundName(Route* theWrappedObject, QString  arg__1){  (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_setOutputSoundName(arg__1));}
   void setRoute(Route* theWrappedObject);
   void py_q_setRoute(Route* theWrappedObject){  (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_setRoute());}
   void setRouteCommandDelay(Route* theWrappedObject, int  arg__1);
   void py_q_setRouteCommandDelay(Route* theWrappedObject, int  arg__1){  (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_setRouteCommandDelay(arg__1));}
   void setTurnoutsAlignedSensor(Route* theWrappedObject, QString  arg__1);
   void py_q_setTurnoutsAlignedSensor(Route* theWrappedObject, QString  arg__1){  (((PythonQtPublicPromoter_Route*)theWrappedObject)->py_q_setTurnoutsAlignedSensor(arg__1));}
};





class PythonQtShell_RouteManager : public RouteManager
{
public:
    PythonQtShell_RouteManager(QObject*  parent = nullptr):RouteManager(parent),_wrapper(NULL) {}

   ~PythonQtShell_RouteManager();

virtual void Register(NamedBean*  s);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual void deleteRoute(Route*  arg__1);
virtual void deregister(NamedBean*  s);
virtual void dispose();
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual NamedBean*  getBeanBySystemName(QString  systemName);
virtual NamedBean*  getBeanByUserName(QString  userName);
virtual QString  getBeanTypeHandled();
virtual Route*  getBySystemName(QString  arg__1);
virtual Route*  getByUserName(QString  arg__1);
virtual QString  getEntryToolTip();
virtual NamedBean*  getNamedBean(QString  name);
virtual QSet<NamedBean* >  getNamedBeanSet();
virtual Route*  getRoute(QString  arg__1);
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList();
virtual QString  getSystemPrefix();
virtual int  getXMLOrder();
virtual QString  makeSystemName(QString  s);
virtual Route*  newRoute(QString  arg__1);
virtual QString  normalizeSystemName(QString  inputName);
virtual void propertyChange(PropertyChangeEvent*  e);
virtual Route*  provideRoute(QString  arg__1, QString  arg__2);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void timerEvent(QTimerEvent*  event);
virtual char  typeLetter();
virtual Manager::NameValidity  validSystemNameFormat(QString  arg__1);
virtual void vetoableChange(PropertyChangeEvent*  evt);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_RouteManager : public RouteManager
{ public:
inline void py_q_deleteRoute(Route*  arg__1) { RouteManager::deleteRoute(arg__1); }
inline void py_q_dispose() { RouteManager::dispose(); }
inline Route*  py_q_getBySystemName(QString  arg__1) { return RouteManager::getBySystemName(arg__1); }
inline Route*  py_q_getByUserName(QString  arg__1) { return RouteManager::getByUserName(arg__1); }
inline Route*  py_q_getRoute(QString  arg__1) { return RouteManager::getRoute(arg__1); }
inline Route*  py_q_newRoute(QString  arg__1) { return RouteManager::newRoute(arg__1); }
inline Route*  py_q_provideRoute(QString  arg__1, QString  arg__2) { return RouteManager::provideRoute(arg__1, arg__2); }
};

class PythonQtWrapper_RouteManager : public QObject
{ Q_OBJECT
public:
public slots:
RouteManager* new_RouteManager(QObject*  parent = nullptr);
void delete_RouteManager(RouteManager* obj) { delete obj; } 
   void deleteRoute(RouteManager* theWrappedObject, Route*  arg__1);
   void py_q_deleteRoute(RouteManager* theWrappedObject, Route*  arg__1){  (((PythonQtPublicPromoter_RouteManager*)theWrappedObject)->py_q_deleteRoute(arg__1));}
   void py_q_dispose(RouteManager* theWrappedObject){  (((PythonQtPublicPromoter_RouteManager*)theWrappedObject)->py_q_dispose());}
   Route*  getBySystemName(RouteManager* theWrappedObject, QString  arg__1);
   Route*  py_q_getBySystemName(RouteManager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_RouteManager*)theWrappedObject)->py_q_getBySystemName(arg__1));}
   Route*  getByUserName(RouteManager* theWrappedObject, QString  arg__1);
   Route*  py_q_getByUserName(RouteManager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_RouteManager*)theWrappedObject)->py_q_getByUserName(arg__1));}
   Route*  getRoute(RouteManager* theWrappedObject, QString  arg__1);
   Route*  py_q_getRoute(RouteManager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_RouteManager*)theWrappedObject)->py_q_getRoute(arg__1));}
   Route*  newRoute(RouteManager* theWrappedObject, QString  arg__1);
   Route*  py_q_newRoute(RouteManager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_RouteManager*)theWrappedObject)->py_q_newRoute(arg__1));}
   Route*  provideRoute(RouteManager* theWrappedObject, QString  arg__1, QString  arg__2);
   Route*  py_q_provideRoute(RouteManager* theWrappedObject, QString  arg__1, QString  arg__2){  return (((PythonQtPublicPromoter_RouteManager*)theWrappedObject)->py_q_provideRoute(arg__1, arg__2));}
};





class PythonQtShell_Sensor : public Sensor
{
public:
    PythonQtShell_Sensor(QObject*  parent = 0):Sensor(parent),_wrapper(NULL) {}
    PythonQtShell_Sensor(QString  sysName, QObject*  parent = 0):Sensor(sysName, parent),_wrapper(NULL) {}
    PythonQtShell_Sensor(QString  sysName, QString  userName, QObject*  parent = 0):Sensor(sysName, userName, parent),_wrapper(NULL) {}

   ~PythonQtShell_Sensor();

virtual void addPropertyChangeListener(PropertyChangeListener*  arg__1) const;
virtual bool  canInvert();
virtual void childEvent(QChildEvent*  event);
virtual int  compareSystemNameSuffix(QString  suffix1, QString  suffix2, NamedBean*  n);
virtual int  compareTo(NamedBean*  n2);
virtual void customEvent(QEvent*  event);
virtual QString  describeState(int  state);
virtual void dispose() const;
virtual bool  equals(QObject*  obj);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual QString  getBeanType();
virtual QString  getComment();
virtual QString  getDisplayName();
virtual QString  getFullyFormattedDisplayName();
virtual bool  getInverted() const;
virtual int  getKnownState() const;
virtual QString  getListenerRef(PropertyChangeListener*  l);
virtual QList<QString >*  getListenerRefs();
virtual int  getNumPropertyChangeListeners();
virtual QVariant  getProperty(QString  key);
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners();
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners(QString  name);
virtual QSet<QString >  getPropertyKeys();
virtual int  getRawState() const;
virtual long  getSensorDebounceGoingActiveTimer() const;
virtual long  getSensorDebounceGoingInActiveTimer() const;
virtual int  getState();
virtual QString  getSystemName() const;
virtual QString  getUserName();
virtual bool  hashCode();
virtual void removeProperty(QString  key);
virtual void removePropertyChangeListener(PropertyChangeListener*  arg__1) const;
virtual void requestUpdateFromLayout() const;
virtual void setComment(QString  comment);
virtual void setInverted(bool  arg__1) const;
virtual void setKnownState(int  arg__1);
virtual void setProperty(QString  key, QVariant  value);
virtual void setSensorDebounceGoingActiveTimer(long  arg__1) const;
virtual void setSensorDebounceGoingInActiveTimer(long  arg__1) const;
virtual void setState(int  arg__1);
virtual void setSysName(QString  s);
virtual void setUserName(QString  s);
virtual void timerEvent(QTimerEvent*  event);
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);
virtual bool  useDefaultTimerSettings() const;
virtual void useDefaultTimerSettings(bool  arg__1) const;
virtual void vetoableChange(PropertyChangeEvent*  evt) throw (PropertyVetoException);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_Sensor : public Sensor
{ public:
inline void py_q_addPropertyChangeListener(PropertyChangeListener*  arg__1) const { Sensor::addPropertyChangeListener(arg__1); }
inline bool  py_q_canInvert() { return Sensor::canInvert(); }
inline void py_q_dispose() const { Sensor::dispose(); }
inline bool  py_q_getInverted() const { return Sensor::getInverted(); }
inline int  py_q_getKnownState() const { return Sensor::getKnownState(); }
inline int  py_q_getRawState() const { return Sensor::getRawState(); }
inline long  py_q_getSensorDebounceGoingActiveTimer() const { return Sensor::getSensorDebounceGoingActiveTimer(); }
inline long  py_q_getSensorDebounceGoingInActiveTimer() const { return Sensor::getSensorDebounceGoingInActiveTimer(); }
inline void py_q_removePropertyChangeListener(PropertyChangeListener*  arg__1) const { Sensor::removePropertyChangeListener(arg__1); }
inline void py_q_requestUpdateFromLayout() const { Sensor::requestUpdateFromLayout(); }
inline void py_q_setInverted(bool  arg__1) const { Sensor::setInverted(arg__1); }
inline void py_q_setKnownState(int  arg__1) { Sensor::setKnownState(arg__1); }
inline void py_q_setSensorDebounceGoingActiveTimer(long  arg__1) const { Sensor::setSensorDebounceGoingActiveTimer(arg__1); }
inline void py_q_setSensorDebounceGoingInActiveTimer(long  arg__1) const { Sensor::setSensorDebounceGoingInActiveTimer(arg__1); }
inline bool  py_q_useDefaultTimerSettings() const { return Sensor::useDefaultTimerSettings(); }
inline void py_q_useDefaultTimerSettings(bool  arg__1) const { Sensor::useDefaultTimerSettings(arg__1); }
};

class PythonQtWrapper_Sensor : public QObject
{ Q_OBJECT
public:
public slots:
Sensor* new_Sensor(QObject*  parent = 0);
Sensor* new_Sensor(QString  sysName, QObject*  parent = 0);
Sensor* new_Sensor(QString  sysName, QString  userName, QObject*  parent = 0);
void delete_Sensor(Sensor* obj) { delete obj; } 
   void py_q_addPropertyChangeListener(Sensor* theWrappedObject, PropertyChangeListener*  arg__1) const{  (((PythonQtPublicPromoter_Sensor*)theWrappedObject)->py_q_addPropertyChangeListener(arg__1));}
   bool  canInvert(Sensor* theWrappedObject);
   bool  py_q_canInvert(Sensor* theWrappedObject){  return (((PythonQtPublicPromoter_Sensor*)theWrappedObject)->py_q_canInvert());}
   void py_q_dispose(Sensor* theWrappedObject) const{  (((PythonQtPublicPromoter_Sensor*)theWrappedObject)->py_q_dispose());}
   bool  getInverted(Sensor* theWrappedObject) const;
   bool  py_q_getInverted(Sensor* theWrappedObject) const{  return (((PythonQtPublicPromoter_Sensor*)theWrappedObject)->py_q_getInverted());}
   int  getKnownState(Sensor* theWrappedObject) const;
   int  py_q_getKnownState(Sensor* theWrappedObject) const{  return (((PythonQtPublicPromoter_Sensor*)theWrappedObject)->py_q_getKnownState());}
   int  getRawState(Sensor* theWrappedObject) const;
   int  py_q_getRawState(Sensor* theWrappedObject) const{  return (((PythonQtPublicPromoter_Sensor*)theWrappedObject)->py_q_getRawState());}
   long  getSensorDebounceGoingActiveTimer(Sensor* theWrappedObject) const;
   long  py_q_getSensorDebounceGoingActiveTimer(Sensor* theWrappedObject) const{  return (((PythonQtPublicPromoter_Sensor*)theWrappedObject)->py_q_getSensorDebounceGoingActiveTimer());}
   long  getSensorDebounceGoingInActiveTimer(Sensor* theWrappedObject) const;
   long  py_q_getSensorDebounceGoingInActiveTimer(Sensor* theWrappedObject) const{  return (((PythonQtPublicPromoter_Sensor*)theWrappedObject)->py_q_getSensorDebounceGoingInActiveTimer());}
   void py_q_removePropertyChangeListener(Sensor* theWrappedObject, PropertyChangeListener*  arg__1) const{  (((PythonQtPublicPromoter_Sensor*)theWrappedObject)->py_q_removePropertyChangeListener(arg__1));}
   void requestUpdateFromLayout(Sensor* theWrappedObject) const;
   void py_q_requestUpdateFromLayout(Sensor* theWrappedObject) const{  (((PythonQtPublicPromoter_Sensor*)theWrappedObject)->py_q_requestUpdateFromLayout());}
   void setInverted(Sensor* theWrappedObject, bool  arg__1) const;
   void py_q_setInverted(Sensor* theWrappedObject, bool  arg__1) const{  (((PythonQtPublicPromoter_Sensor*)theWrappedObject)->py_q_setInverted(arg__1));}
   void setKnownState(Sensor* theWrappedObject, int  arg__1);
   void py_q_setKnownState(Sensor* theWrappedObject, int  arg__1){  (((PythonQtPublicPromoter_Sensor*)theWrappedObject)->py_q_setKnownState(arg__1));}
   void setSensorDebounceGoingActiveTimer(Sensor* theWrappedObject, long  arg__1) const;
   void py_q_setSensorDebounceGoingActiveTimer(Sensor* theWrappedObject, long  arg__1) const{  (((PythonQtPublicPromoter_Sensor*)theWrappedObject)->py_q_setSensorDebounceGoingActiveTimer(arg__1));}
   void setSensorDebounceGoingInActiveTimer(Sensor* theWrappedObject, long  arg__1) const;
   void py_q_setSensorDebounceGoingInActiveTimer(Sensor* theWrappedObject, long  arg__1) const{  (((PythonQtPublicPromoter_Sensor*)theWrappedObject)->py_q_setSensorDebounceGoingInActiveTimer(arg__1));}
   bool  useDefaultTimerSettings(Sensor* theWrappedObject) const;
   bool  py_q_useDefaultTimerSettings(Sensor* theWrappedObject) const{  return (((PythonQtPublicPromoter_Sensor*)theWrappedObject)->py_q_useDefaultTimerSettings());}
   void useDefaultTimerSettings(Sensor* theWrappedObject, bool  arg__1) const;
   void py_q_useDefaultTimerSettings(Sensor* theWrappedObject, bool  arg__1) const{  (((PythonQtPublicPromoter_Sensor*)theWrappedObject)->py_q_useDefaultTimerSettings(arg__1));}
void py_set_thisAddr(Sensor* theWrappedObject, int  thisAddr){ theWrappedObject->thisAddr = thisAddr; }
int  py_get_thisAddr(Sensor* theWrappedObject){ return theWrappedObject->thisAddr; }
};





class PythonQtShell_SensorManager : public SensorManager
{
public:
    PythonQtShell_SensorManager(QObject*  parent = nullptr):SensorManager(parent),_wrapper(NULL) {}

   ~PythonQtShell_SensorManager();

virtual void Register(NamedBean*  s);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual bool  allowMultipleAdditions(QString  arg__1);
virtual void childEvent(QChildEvent*  event);
virtual QString  createSystemName(QString  arg__1, QString  arg__2) const;
virtual void customEvent(QEvent*  event);
virtual void deregister(NamedBean*  s);
virtual void dispose() const;
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual NamedBean*  getBeanBySystemName(QString  systemName);
virtual NamedBean*  getBeanByUserName(QString  userName);
virtual QString  getBeanTypeHandled();
virtual Sensor*  getBySystemName(QString  arg__1);
virtual Sensor*  getByUserName(QString  arg__1);
virtual long  getDefaultSensorDebounceGoingActive();
virtual long  getDefaultSensorDebounceGoingInActive();
virtual QString  getEntryToolTip();
virtual NamedBean*  getNamedBean(QString  name);
virtual QSet<NamedBean* >  getNamedBeanSet();
virtual QString  getNextValidAddress(QString  arg__1, QString  arg__2);
virtual Sensor*  getSensor(QString  arg__1) const;
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList();
virtual QString  getSystemPrefix();
virtual int  getXMLOrder();
virtual QString  makeSystemName(QString  s);
virtual Sensor*  newSensor(QString  arg__1, QString  arg__2);
virtual QString  normalizeSystemName(QString  inputName);
virtual void propertyChange(PropertyChangeEvent*  e);
virtual Sensor*  provideSensor(QString  arg__1);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void setDefaultSensorDebounceGoingActive(long  arg__1);
virtual void setDefaultSensorDebounceGoingInActive(long  arg__1);
virtual void timerEvent(QTimerEvent*  event);
virtual char  typeLetter();
virtual void updateAll() const;
virtual Manager::NameValidity  validSystemNameFormat(QString  arg__1);
virtual void vetoableChange(PropertyChangeEvent*  evt);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_SensorManager : public SensorManager
{ public:
inline bool  py_q_allowMultipleAdditions(QString  arg__1) { return SensorManager::allowMultipleAdditions(arg__1); }
inline QString  py_q_createSystemName(QString  arg__1, QString  arg__2) const { return SensorManager::createSystemName(arg__1, arg__2); }
inline void py_q_dispose() const { SensorManager::dispose(); }
inline Sensor*  py_q_getBySystemName(QString  arg__1) { return SensorManager::getBySystemName(arg__1); }
inline Sensor*  py_q_getByUserName(QString  arg__1) { return SensorManager::getByUserName(arg__1); }
inline long  py_q_getDefaultSensorDebounceGoingActive() { return SensorManager::getDefaultSensorDebounceGoingActive(); }
inline long  py_q_getDefaultSensorDebounceGoingInActive() { return SensorManager::getDefaultSensorDebounceGoingInActive(); }
inline QString  py_q_getNextValidAddress(QString  arg__1, QString  arg__2) { return SensorManager::getNextValidAddress(arg__1, arg__2); }
inline Sensor*  py_q_getSensor(QString  arg__1) const { return SensorManager::getSensor(arg__1); }
inline Sensor*  py_q_newSensor(QString  arg__1, QString  arg__2) { return SensorManager::newSensor(arg__1, arg__2); }
inline Sensor*  py_q_provideSensor(QString  arg__1) { return SensorManager::provideSensor(arg__1); }
inline void py_q_setDefaultSensorDebounceGoingActive(long  arg__1) { SensorManager::setDefaultSensorDebounceGoingActive(arg__1); }
inline void py_q_setDefaultSensorDebounceGoingInActive(long  arg__1) { SensorManager::setDefaultSensorDebounceGoingInActive(arg__1); }
inline void py_q_updateAll() const { SensorManager::updateAll(); }
};

class PythonQtWrapper_SensorManager : public QObject
{ Q_OBJECT
public:
public slots:
SensorManager* new_SensorManager(QObject*  parent = nullptr);
void delete_SensorManager(SensorManager* obj) { delete obj; } 
   bool  allowMultipleAdditions(SensorManager* theWrappedObject, QString  arg__1);
   bool  py_q_allowMultipleAdditions(SensorManager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_SensorManager*)theWrappedObject)->py_q_allowMultipleAdditions(arg__1));}
   QString  createSystemName(SensorManager* theWrappedObject, QString  arg__1, QString  arg__2) const;
   QString  py_q_createSystemName(SensorManager* theWrappedObject, QString  arg__1, QString  arg__2) const{  return (((PythonQtPublicPromoter_SensorManager*)theWrappedObject)->py_q_createSystemName(arg__1, arg__2));}
   void py_q_dispose(SensorManager* theWrappedObject) const{  (((PythonQtPublicPromoter_SensorManager*)theWrappedObject)->py_q_dispose());}
   Sensor*  getBySystemName(SensorManager* theWrappedObject, QString  arg__1);
   Sensor*  py_q_getBySystemName(SensorManager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_SensorManager*)theWrappedObject)->py_q_getBySystemName(arg__1));}
   Sensor*  getByUserName(SensorManager* theWrappedObject, QString  arg__1);
   Sensor*  py_q_getByUserName(SensorManager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_SensorManager*)theWrappedObject)->py_q_getByUserName(arg__1));}
   long  getDefaultSensorDebounceGoingActive(SensorManager* theWrappedObject);
   long  py_q_getDefaultSensorDebounceGoingActive(SensorManager* theWrappedObject){  return (((PythonQtPublicPromoter_SensorManager*)theWrappedObject)->py_q_getDefaultSensorDebounceGoingActive());}
   long  getDefaultSensorDebounceGoingInActive(SensorManager* theWrappedObject);
   long  py_q_getDefaultSensorDebounceGoingInActive(SensorManager* theWrappedObject){  return (((PythonQtPublicPromoter_SensorManager*)theWrappedObject)->py_q_getDefaultSensorDebounceGoingInActive());}
   QString  getNextValidAddress(SensorManager* theWrappedObject, QString  arg__1, QString  arg__2);
   QString  py_q_getNextValidAddress(SensorManager* theWrappedObject, QString  arg__1, QString  arg__2){  return (((PythonQtPublicPromoter_SensorManager*)theWrappedObject)->py_q_getNextValidAddress(arg__1, arg__2));}
   Sensor*  getSensor(SensorManager* theWrappedObject, QString  arg__1) const;
   Sensor*  py_q_getSensor(SensorManager* theWrappedObject, QString  arg__1) const{  return (((PythonQtPublicPromoter_SensorManager*)theWrappedObject)->py_q_getSensor(arg__1));}
   Sensor*  newSensor(SensorManager* theWrappedObject, QString  arg__1, QString  arg__2);
   Sensor*  py_q_newSensor(SensorManager* theWrappedObject, QString  arg__1, QString  arg__2){  return (((PythonQtPublicPromoter_SensorManager*)theWrappedObject)->py_q_newSensor(arg__1, arg__2));}
   Sensor*  provideSensor(SensorManager* theWrappedObject, QString  arg__1);
   Sensor*  py_q_provideSensor(SensorManager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_SensorManager*)theWrappedObject)->py_q_provideSensor(arg__1));}
   void setDefaultSensorDebounceGoingActive(SensorManager* theWrappedObject, long  arg__1);
   void py_q_setDefaultSensorDebounceGoingActive(SensorManager* theWrappedObject, long  arg__1){  (((PythonQtPublicPromoter_SensorManager*)theWrappedObject)->py_q_setDefaultSensorDebounceGoingActive(arg__1));}
   void setDefaultSensorDebounceGoingInActive(SensorManager* theWrappedObject, long  arg__1);
   void py_q_setDefaultSensorDebounceGoingInActive(SensorManager* theWrappedObject, long  arg__1){  (((PythonQtPublicPromoter_SensorManager*)theWrappedObject)->py_q_setDefaultSensorDebounceGoingInActive(arg__1));}
   void updateAll(SensorManager* theWrappedObject) const;
   void py_q_updateAll(SensorManager* theWrappedObject) const{  (((PythonQtPublicPromoter_SensorManager*)theWrappedObject)->py_q_updateAll());}
};





class PythonQtShell_SerialPortAdapter : public SerialPortAdapter
{
public:
    PythonQtShell_SerialPortAdapter(SystemConnectionMemo*  connectionMemo, QObject*  parent = 0):SerialPortAdapter(connectionMemo, parent),_wrapper(NULL) {}

   ~PythonQtShell_SerialPortAdapter();

virtual void _connect(QString  arg__1, int  arg__2);
virtual void autoConfigure();
virtual void childEvent(QChildEvent*  event);
virtual void configure();
virtual void configureBaudRate(QString  arg__1);
virtual void configureOption1(QString  value);
virtual void configureOption2(QString  value);
virtual void configureOption3(QString  value);
virtual void configureOption4(QString  value);
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
virtual SystemConnectionMemo*  getSystemConnectionMemo();
virtual QString  getSystemPrefix();
virtual QString  getUserName();
virtual bool  isDirty();
virtual bool  isOptionAdvanced(QString  option);
virtual bool  isRestartRequired();
virtual QString  openPort(QString  arg__1, QString  arg__2);
virtual void recover();
virtual void setAdvertisementName(QString  arg__1);
virtual void setDisabled(bool  disabled);
virtual void setHostName(QString  arg__1);
virtual void setManufacturer(QString  manufacturer);
virtual void setMdnsConfigure(bool  arg__1);
virtual void setOptionState(QString  option, QString  value);
virtual void setPort(QString  arg__1);
virtual void setServiceType(QString  arg__1);
virtual void setSystemConnectionMemo(SystemConnectionMemo*  connectionMemo);
virtual void setSystemPrefix(QString  systemPrefix);
virtual void setUserName(QString  userName);
virtual bool  status();
virtual void timerEvent(QTimerEvent*  event);
virtual QStringList  validBaudRates();

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_SerialPortAdapter : public SerialPortAdapter
{ public:
inline void py_q_configureBaudRate(QString  arg__1) { SerialPortAdapter::configureBaudRate(arg__1); }
inline QString  py_q_getCurrentBaudRate() { return SerialPortAdapter::getCurrentBaudRate(); }
inline QString  py_q_getCurrentPortName() { return SerialPortAdapter::getCurrentPortName(); }
inline QVector<QString >  py_q_getPortNames() { return SerialPortAdapter::getPortNames(); }
inline QString  py_q_openPort(QString  arg__1, QString  arg__2) { return SerialPortAdapter::openPort(arg__1, arg__2); }
inline void py_q_setPort(QString  arg__1) { SerialPortAdapter::setPort(arg__1); }
inline QStringList  py_q_validBaudRates() { return SerialPortAdapter::validBaudRates(); }
};

class PythonQtWrapper_SerialPortAdapter : public QObject
{ Q_OBJECT
public:
public slots:
SerialPortAdapter* new_SerialPortAdapter(SystemConnectionMemo*  connectionMemo, QObject*  parent = 0);
void delete_SerialPortAdapter(SerialPortAdapter* obj) { delete obj; } 
   void configureBaudRate(SerialPortAdapter* theWrappedObject, QString  arg__1);
   void py_q_configureBaudRate(SerialPortAdapter* theWrappedObject, QString  arg__1){  (((PythonQtPublicPromoter_SerialPortAdapter*)theWrappedObject)->py_q_configureBaudRate(arg__1));}
   QString  getCurrentBaudRate(SerialPortAdapter* theWrappedObject);
   QString  py_q_getCurrentBaudRate(SerialPortAdapter* theWrappedObject){  return (((PythonQtPublicPromoter_SerialPortAdapter*)theWrappedObject)->py_q_getCurrentBaudRate());}
   QString  py_q_getCurrentPortName(SerialPortAdapter* theWrappedObject){  return (((PythonQtPublicPromoter_SerialPortAdapter*)theWrappedObject)->py_q_getCurrentPortName());}
   QVector<QString >  getPortNames(SerialPortAdapter* theWrappedObject);
   QVector<QString >  py_q_getPortNames(SerialPortAdapter* theWrappedObject){  return (((PythonQtPublicPromoter_SerialPortAdapter*)theWrappedObject)->py_q_getPortNames());}
   QString  openPort(SerialPortAdapter* theWrappedObject, QString  arg__1, QString  arg__2);
   QString  py_q_openPort(SerialPortAdapter* theWrappedObject, QString  arg__1, QString  arg__2){  return (((PythonQtPublicPromoter_SerialPortAdapter*)theWrappedObject)->py_q_openPort(arg__1, arg__2));}
   void py_q_setPort(SerialPortAdapter* theWrappedObject, QString  arg__1){  (((PythonQtPublicPromoter_SerialPortAdapter*)theWrappedObject)->py_q_setPort(arg__1));}
   QStringList  validBaudRates(SerialPortAdapter* theWrappedObject);
   QStringList  py_q_validBaudRates(SerialPortAdapter* theWrappedObject){  return (((PythonQtPublicPromoter_SerialPortAdapter*)theWrappedObject)->py_q_validBaudRates());}
};





class PythonQtShell_ShutDownManager : public ShutDownManager
{
public:
    PythonQtShell_ShutDownManager(QObject*  parent = 0):ShutDownManager(parent),_wrapper(NULL) {}

   ~PythonQtShell_ShutDownManager();

virtual void _register(ShutDownTask*  arg__1);
virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual void deregister(ShutDownTask*  arg__1);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual bool  isShuttingDown();
virtual bool  restart();
virtual bool  shutdown();
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_ShutDownManager : public ShutDownManager
{ public:
inline void py_q__register(ShutDownTask*  arg__1) { ShutDownManager::_register(arg__1); }
inline void py_q_deregister(ShutDownTask*  arg__1) { ShutDownManager::deregister(arg__1); }
inline bool  py_q_isShuttingDown() { return ShutDownManager::isShuttingDown(); }
inline bool  py_q_restart() { return this->restart(); }
inline bool  py_q_shutdown() { return this->shutdown(); }
};

class PythonQtWrapper_ShutDownManager : public QObject
{ Q_OBJECT
public:
public slots:
ShutDownManager* new_ShutDownManager(QObject*  parent = 0);
void delete_ShutDownManager(ShutDownManager* obj) { delete obj; } 
   void _register(ShutDownManager* theWrappedObject, ShutDownTask*  arg__1);
   void py_q__register(ShutDownManager* theWrappedObject, ShutDownTask*  arg__1){  (((PythonQtPublicPromoter_ShutDownManager*)theWrappedObject)->py_q__register(arg__1));}
   void deregister(ShutDownManager* theWrappedObject, ShutDownTask*  arg__1);
   void py_q_deregister(ShutDownManager* theWrappedObject, ShutDownTask*  arg__1){  (((PythonQtPublicPromoter_ShutDownManager*)theWrappedObject)->py_q_deregister(arg__1));}
   bool  isShuttingDown(ShutDownManager* theWrappedObject);
   bool  py_q_isShuttingDown(ShutDownManager* theWrappedObject){  return (((PythonQtPublicPromoter_ShutDownManager*)theWrappedObject)->py_q_isShuttingDown());}
   bool  restart(ShutDownManager* theWrappedObject);
   bool  py_q_restart(ShutDownManager* theWrappedObject){  return (((PythonQtPublicPromoter_ShutDownManager*)theWrappedObject)->py_q_restart());}
   bool  shutdown(ShutDownManager* theWrappedObject);
   bool  py_q_shutdown(ShutDownManager* theWrappedObject){  return (((PythonQtPublicPromoter_ShutDownManager*)theWrappedObject)->py_q_shutdown());}
};





class PythonQtShell_ShutDownTask : public ShutDownTask
{
public:
    PythonQtShell_ShutDownTask():ShutDownTask(),_wrapper(NULL) {}

   ~PythonQtShell_ShutDownTask();

virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual bool  execute();
virtual QString  getName();
virtual bool  isComplete();
virtual bool  isParallel();
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_ShutDownTask : public ShutDownTask
{ public:
inline bool  py_q_execute() { return ShutDownTask::execute(); }
inline QString  py_q_getName() { return ShutDownTask::getName(); }
inline bool  py_q_isComplete() { return ShutDownTask::isComplete(); }
inline bool  py_q_isParallel() { return ShutDownTask::isParallel(); }
};

class PythonQtWrapper_ShutDownTask : public QObject
{ Q_OBJECT
public:
public slots:
ShutDownTask* new_ShutDownTask();
void delete_ShutDownTask(ShutDownTask* obj) { delete obj; } 
   bool  execute(ShutDownTask* theWrappedObject);
   bool  py_q_execute(ShutDownTask* theWrappedObject){  return (((PythonQtPublicPromoter_ShutDownTask*)theWrappedObject)->py_q_execute());}
   QString  getName(ShutDownTask* theWrappedObject);
   QString  py_q_getName(ShutDownTask* theWrappedObject){  return (((PythonQtPublicPromoter_ShutDownTask*)theWrappedObject)->py_q_getName());}
   bool  isComplete(ShutDownTask* theWrappedObject);
   bool  py_q_isComplete(ShutDownTask* theWrappedObject){  return (((PythonQtPublicPromoter_ShutDownTask*)theWrappedObject)->py_q_isComplete());}
   bool  isParallel(ShutDownTask* theWrappedObject);
   bool  py_q_isParallel(ShutDownTask* theWrappedObject){  return (((PythonQtPublicPromoter_ShutDownTask*)theWrappedObject)->py_q_isParallel());}
};





class PythonQtShell_Siglet : public Siglet
{
public:
    PythonQtShell_Siglet(QObject*  parent = 0):Siglet(parent),_wrapper(NULL) {}
    PythonQtShell_Siglet(QString  name, QObject*  parent = 0):Siglet(name, parent),_wrapper(NULL) {}

   ~PythonQtShell_Siglet();

virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual void defineIO();
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual bool  handle();
virtual void init();
virtual void setOutput();
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_Siglet : public Siglet
{ public:
inline bool  promoted_handle() { return this->handle(); }
inline void promoted_init() { this->init(); }
inline void py_q_defineIO() { Siglet::defineIO(); }
inline bool  py_q_handle() { return Siglet::handle(); }
inline void py_q_init() { Siglet::init(); }
inline void py_q_setOutput() { Siglet::setOutput(); }
};

class PythonQtWrapper_Siglet : public QObject
{ Q_OBJECT
public:
public slots:
Siglet* new_Siglet(QObject*  parent = 0);
Siglet* new_Siglet(QString  name, QObject*  parent = 0);
void delete_Siglet(Siglet* obj) { delete obj; } 
   void defineIO(Siglet* theWrappedObject);
   void py_q_defineIO(Siglet* theWrappedObject){  (((PythonQtPublicPromoter_Siglet*)theWrappedObject)->py_q_defineIO());}
   bool  py_q_handle(Siglet* theWrappedObject){  return (((PythonQtPublicPromoter_Siglet*)theWrappedObject)->py_q_handle());}
   void py_q_init(Siglet* theWrappedObject){  (((PythonQtPublicPromoter_Siglet*)theWrappedObject)->py_q_init());}
   void setOutput(Siglet* theWrappedObject);
   void py_q_setOutput(Siglet* theWrappedObject){  (((PythonQtPublicPromoter_Siglet*)theWrappedObject)->py_q_setOutput());}
void py_set_inputs(Siglet* theWrappedObject, QVector<NamedBean* >  inputs){ theWrappedObject->inputs = inputs; }
QVector<NamedBean* >  py_get_inputs(Siglet* theWrappedObject){ return theWrappedObject->inputs; }
void py_set_outputs(Siglet* theWrappedObject, QVector<NamedBean* >  outputs){ theWrappedObject->outputs = outputs; }
QVector<NamedBean* >  py_get_outputs(Siglet* theWrappedObject){ return theWrappedObject->outputs; }
};





class PythonQtShell_SignalHead : public SignalHead
{
public:
    PythonQtShell_SignalHead(QObject*  parent = 0):SignalHead(parent),_wrapper(NULL) {}
    PythonQtShell_SignalHead(QString  systemName, QObject*  parent):SignalHead(systemName, parent),_wrapper(NULL) {}
    PythonQtShell_SignalHead(QString  systemName, QString  userName, QObject*  parent):SignalHead(systemName, userName, parent),_wrapper(NULL) {}

   ~PythonQtShell_SignalHead();

virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(PropertyChangeListener*  l, QString  beanRef, const QString  listenerRef);
virtual void childEvent(QChildEvent*  event);
virtual int  compareSystemNameSuffix(QString  suffix1, QString  suffix2, NamedBean*  n);
virtual int  compareTo(NamedBean*  n2);
virtual void customEvent(QEvent*  event);
virtual QString  describeState(int  state);
virtual void dispose();
virtual bool  equals(QObject*  obj);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual int  getAppearance();
virtual QString  getAppearanceName();
virtual QString  getAppearanceName(int  arg__1);
virtual QString  getBeanType();
virtual QString  getComment();
virtual QString  getDisplayName();
virtual QString  getFullyFormattedDisplayName();
virtual bool  getHeld();
virtual QString  getListenerRef(PropertyChangeListener*  l);
virtual QList<QString >*  getListenerRefs();
virtual bool  getLit();
virtual int  getNumPropertyChangeListeners();
virtual QVariant  getProperty(QString  key);
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners();
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners(QString  name);
virtual QSet<QString >  getPropertyKeys();
virtual int  getState();
virtual QString  getSystemName() const;
virtual QString  getUserName();
virtual QVector<QString >  getValidStateNames();
virtual QVector<int >  getValidStates();
virtual bool  hashCode();
virtual void removeProperty(QString  key);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void setAppearance(int  arg__1);
virtual void setComment(QString  comment);
virtual void setHeld(bool  arg__1);
virtual void setLit(bool  arg__1);
virtual void setProperty(QString  key, QVariant  value);
virtual void setState(int  arg__1);
virtual void setSysName(QString  s);
virtual void setUserName(QString  s);
virtual void timerEvent(QTimerEvent*  event);
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);
virtual void vetoableChange(PropertyChangeEvent*  evt) throw (PropertyVetoException);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_SignalHead : public SignalHead
{ public:
inline int  py_q_getAppearance() { return SignalHead::getAppearance(); }
inline QString  py_q_getAppearanceName() { return SignalHead::getAppearanceName(); }
inline QString  py_q_getAppearanceName(int  arg__1) { return SignalHead::getAppearanceName(arg__1); }
inline bool  py_q_getHeld() { return SignalHead::getHeld(); }
inline bool  py_q_getLit() { return SignalHead::getLit(); }
inline QVector<QString >  py_q_getValidStateNames() { return SignalHead::getValidStateNames(); }
inline QVector<int >  py_q_getValidStates() { return SignalHead::getValidStates(); }
inline void py_q_setAppearance(int  arg__1) { SignalHead::setAppearance(arg__1); }
inline void py_q_setHeld(bool  arg__1) { SignalHead::setHeld(arg__1); }
inline void py_q_setLit(bool  arg__1) { SignalHead::setLit(arg__1); }
};

class PythonQtWrapper_SignalHead : public QObject
{ Q_OBJECT
public:
public slots:
SignalHead* new_SignalHead(QObject*  parent = 0);
SignalHead* new_SignalHead(QString  systemName, QObject*  parent);
SignalHead* new_SignalHead(QString  systemName, QString  userName, QObject*  parent);
void delete_SignalHead(SignalHead* obj) { delete obj; } 
   int  getAppearance(SignalHead* theWrappedObject);
   int  py_q_getAppearance(SignalHead* theWrappedObject){  return (((PythonQtPublicPromoter_SignalHead*)theWrappedObject)->py_q_getAppearance());}
   QString  getAppearanceName(SignalHead* theWrappedObject);
   QString  py_q_getAppearanceName(SignalHead* theWrappedObject){  return (((PythonQtPublicPromoter_SignalHead*)theWrappedObject)->py_q_getAppearanceName());}
   QString  getAppearanceName(SignalHead* theWrappedObject, int  arg__1);
   QString  py_q_getAppearanceName(SignalHead* theWrappedObject, int  arg__1){  return (((PythonQtPublicPromoter_SignalHead*)theWrappedObject)->py_q_getAppearanceName(arg__1));}
   bool  getHeld(SignalHead* theWrappedObject);
   bool  py_q_getHeld(SignalHead* theWrappedObject){  return (((PythonQtPublicPromoter_SignalHead*)theWrappedObject)->py_q_getHeld());}
   bool  getLit(SignalHead* theWrappedObject);
   bool  py_q_getLit(SignalHead* theWrappedObject){  return (((PythonQtPublicPromoter_SignalHead*)theWrappedObject)->py_q_getLit());}
   QVector<QString >  getValidStateNames(SignalHead* theWrappedObject);
   QVector<QString >  py_q_getValidStateNames(SignalHead* theWrappedObject){  return (((PythonQtPublicPromoter_SignalHead*)theWrappedObject)->py_q_getValidStateNames());}
   QVector<int >  getValidStates(SignalHead* theWrappedObject);
   QVector<int >  py_q_getValidStates(SignalHead* theWrappedObject){  return (((PythonQtPublicPromoter_SignalHead*)theWrappedObject)->py_q_getValidStates());}
   void setAppearance(SignalHead* theWrappedObject, int  arg__1);
   void py_q_setAppearance(SignalHead* theWrappedObject, int  arg__1){  (((PythonQtPublicPromoter_SignalHead*)theWrappedObject)->py_q_setAppearance(arg__1));}
   void setHeld(SignalHead* theWrappedObject, bool  arg__1);
   void py_q_setHeld(SignalHead* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_SignalHead*)theWrappedObject)->py_q_setHeld(arg__1));}
   void setLit(SignalHead* theWrappedObject, bool  arg__1);
   void py_q_setLit(SignalHead* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_SignalHead*)theWrappedObject)->py_q_setLit(arg__1));}
};





class PythonQtShell_Sound : public Sound
{
public:
    PythonQtShell_Sound(QString  path, QObject*  parent = nullptr) throw (NullPointerException):Sound(path, parent),_wrapper(NULL) {}
    PythonQtShell_Sound(QUrl*  url, QObject*  parent = nullptr) throw (NullPointerException):Sound(url, parent),_wrapper(NULL) {}

   ~PythonQtShell_Sound();


  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtWrapper_Sound : public QObject
{ Q_OBJECT
public:
public slots:
Sound* new_Sound(QString  path, QObject*  parent = nullptr) throw (NullPointerException);
Sound* new_Sound(QUrl*  url, QObject*  parent = nullptr) throw (NullPointerException);
void delete_Sound(Sound* obj) { delete obj; } 
   void loop(Sound* theWrappedObject);
   void loop(Sound* theWrappedObject, int  count);
   void play(Sound* theWrappedObject);
   void stop(Sound* theWrappedObject);
};





class PythonQtShell_SystemConnectionMemo : public SystemConnectionMemo
{
public:
    PythonQtShell_SystemConnectionMemo(QString  Prefix = "I", QString  userName = "Internal", QObject*  parent = 0):SystemConnectionMemo(Prefix, userName, parent),_wrapper(NULL) {}
    PythonQtShell_SystemConnectionMemo(const SystemConnectionMemo&  arg__1):SystemConnectionMemo(arg__1),_wrapper(NULL) {}

   ~PythonQtShell_SystemConnectionMemo();

virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual QObject*  get(QString  T);
virtual bool  provides(QString  c);
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_SystemConnectionMemo : public SystemConnectionMemo
{ public:
inline void promoted_addToActionList() { this->addToActionList(); }
inline void promoted_notifyPropertyChangeListener(QString  property, QVariant  oldValue, QVariant  newValue) { this->notifyPropertyChangeListener(property, oldValue, newValue); }
inline void promoted_removeFromActionList() { this->removeFromActionList(); }
inline QObject*  py_q_get(QString  T) { return SystemConnectionMemo::get(T); }
inline bool  py_q_provides(QString  c) { return SystemConnectionMemo::provides(c); }
};

class PythonQtWrapper_SystemConnectionMemo : public QObject
{ Q_OBJECT
public:
public slots:
SystemConnectionMemo* new_SystemConnectionMemo(QString  Prefix = "I", QString  userName = "Internal", QObject*  parent = 0);
SystemConnectionMemo* new_SystemConnectionMemo(const SystemConnectionMemo&  arg__1);
void delete_SystemConnectionMemo(SystemConnectionMemo* obj) { delete obj; } 
   void _register(SystemConnectionMemo* theWrappedObject);
   void addToActionList(SystemConnectionMemo* theWrappedObject);
   void dispose(SystemConnectionMemo* theWrappedObject);
   QObject*  get(SystemConnectionMemo* theWrappedObject, QString  T);
   QObject*  py_q_get(SystemConnectionMemo* theWrappedObject, QString  T){  return (((PythonQtPublicPromoter_SystemConnectionMemo*)theWrappedObject)->py_q_get(T));}
   bool  getDisabled(SystemConnectionMemo* theWrappedObject);
   QString  getSystemPrefix(SystemConnectionMemo* theWrappedObject);
   QString  getUserName(SystemConnectionMemo* theWrappedObject);
   bool  isDirty(SystemConnectionMemo* theWrappedObject);
   bool  isRestartRequired(SystemConnectionMemo* theWrappedObject);
   void notifyPropertyChangeListener(SystemConnectionMemo* theWrappedObject, QString  property, QVariant  oldValue, QVariant  newValue);
   bool  provides(SystemConnectionMemo* theWrappedObject, QString  c);
   bool  py_q_provides(SystemConnectionMemo* theWrappedObject, QString  c){  return (((PythonQtPublicPromoter_SystemConnectionMemo*)theWrappedObject)->py_q_provides(c));}
   void removeFromActionList(SystemConnectionMemo* theWrappedObject);
   void setDisabled(SystemConnectionMemo* theWrappedObject, bool  disabled);
   bool  setSystemPrefix(SystemConnectionMemo* theWrappedObject, QString  systemPrefix);
   bool  setUserName(SystemConnectionMemo* theWrappedObject, QString  name);
};





class PythonQtShell_TableColumn : public TableColumn
{
public:
    PythonQtShell_TableColumn(QObject*  parent = 0):TableColumn(parent),_wrapper(NULL) {}
    PythonQtShell_TableColumn(int  modelIndex, QObject*  parent = 0):TableColumn(modelIndex, parent),_wrapper(NULL) {}
    PythonQtShell_TableColumn(int  modelIndex, int  width, QObject*  parent = 0):TableColumn(modelIndex, width, parent),_wrapper(NULL) {}

   ~PythonQtShell_TableColumn();

virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtWrapper_TableColumn : public QObject
{ Q_OBJECT
public:
public slots:
TableColumn* new_TableColumn(QObject*  parent = 0);
TableColumn* new_TableColumn(int  modelIndex, QObject*  parent = 0);
TableColumn* new_TableColumn(int  modelIndex, int  width, QObject*  parent = 0);
void delete_TableColumn(TableColumn* obj) { delete obj; } 
   void addPropertyChangeListener(TableColumn* theWrappedObject, PropertyChangeListener*  listener);
   QVariant  getHeaderValue(TableColumn* theWrappedObject);
   QVariant  getIdentifier(TableColumn* theWrappedObject);
   int  getMaxWidth(TableColumn* theWrappedObject);
   int  getMinWidth(TableColumn* theWrappedObject);
   int  getModelIndex(TableColumn* theWrappedObject);
   int  getPreferredWidth(TableColumn* theWrappedObject);
   bool  getResizable(TableColumn* theWrappedObject);
   int  getWidth(TableColumn* theWrappedObject);
   void removePropertyChangeListener(TableColumn* theWrappedObject, PropertyChangeListener*  listener);
   void setHeaderValue(TableColumn* theWrappedObject, QVariant  headerValue);
   void setIdentifier(TableColumn* theWrappedObject, QVariant  identifier);
   void setMaxWidth(TableColumn* theWrappedObject, int  maxWidth);
   void setMinWidth(TableColumn* theWrappedObject, int  minWidth);
   void setModelIndex(TableColumn* theWrappedObject, int  modelIndex);
   void setPreferredWidth(TableColumn* theWrappedObject, int  preferredWidth);
   void setResizable(TableColumn* theWrappedObject, bool  isResizable);
   void setWidth(TableColumn* theWrappedObject, int  width);
};





class PythonQtShell_TableColumnModel : public TableColumnModel
{
public:
    PythonQtShell_TableColumnModel(QObject*  parent = 0):TableColumnModel(parent),_wrapper(NULL) {}

   ~PythonQtShell_TableColumnModel();

virtual void addColumn(TableColumn*  arg__1);
virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual TableColumn*  getColumn(int  arg__1);
virtual int  getColumnCount();
virtual int  getColumnIndex(QObject*  arg__1);
virtual int  getColumnIndexAtX(int  arg__1);
virtual int  getColumnMargin();
virtual bool  getColumnSelectionAllowed();
virtual int  getSelectedColumnCount();
virtual QList<int >  getSelectedColumns();
virtual ListSelectionModel*  getSelectionModel();
virtual int  getTotalColumnWidth();
virtual void moveColumn(int  arg__1, int  arg__2);
virtual void removeColumn(TableColumn*  arg__1);
virtual void setColumnMargin(int  arg__1);
virtual void setColumnSelectionAllowed(bool  arg__1);
virtual void setSelectionModel(ListSelectionModel*  arg__1);
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_TableColumnModel : public TableColumnModel
{ public:
inline void py_q_addColumn(TableColumn*  arg__1) { TableColumnModel::addColumn(arg__1); }
inline TableColumn*  py_q_getColumn(int  arg__1) { return TableColumnModel::getColumn(arg__1); }
inline int  py_q_getColumnCount() { return TableColumnModel::getColumnCount(); }
inline int  py_q_getColumnIndex(QObject*  arg__1) { return TableColumnModel::getColumnIndex(arg__1); }
inline int  py_q_getColumnIndexAtX(int  arg__1) { return TableColumnModel::getColumnIndexAtX(arg__1); }
inline int  py_q_getColumnMargin() { return TableColumnModel::getColumnMargin(); }
inline bool  py_q_getColumnSelectionAllowed() { return TableColumnModel::getColumnSelectionAllowed(); }
inline int  py_q_getSelectedColumnCount() { return TableColumnModel::getSelectedColumnCount(); }
inline QList<int >  py_q_getSelectedColumns() { return TableColumnModel::getSelectedColumns(); }
inline ListSelectionModel*  py_q_getSelectionModel() { return TableColumnModel::getSelectionModel(); }
inline int  py_q_getTotalColumnWidth() { return TableColumnModel::getTotalColumnWidth(); }
inline void py_q_moveColumn(int  arg__1, int  arg__2) { TableColumnModel::moveColumn(arg__1, arg__2); }
inline void py_q_removeColumn(TableColumn*  arg__1) { TableColumnModel::removeColumn(arg__1); }
inline void py_q_setColumnMargin(int  arg__1) { TableColumnModel::setColumnMargin(arg__1); }
inline void py_q_setColumnSelectionAllowed(bool  arg__1) { TableColumnModel::setColumnSelectionAllowed(arg__1); }
inline void py_q_setSelectionModel(ListSelectionModel*  arg__1) { TableColumnModel::setSelectionModel(arg__1); }
};

class PythonQtWrapper_TableColumnModel : public QObject
{ Q_OBJECT
public:
public slots:
TableColumnModel* new_TableColumnModel(QObject*  parent = 0);
void delete_TableColumnModel(TableColumnModel* obj) { delete obj; } 
   void addColumn(TableColumnModel* theWrappedObject, TableColumn*  arg__1);
   void py_q_addColumn(TableColumnModel* theWrappedObject, TableColumn*  arg__1){  (((PythonQtPublicPromoter_TableColumnModel*)theWrappedObject)->py_q_addColumn(arg__1));}
   TableColumn*  getColumn(TableColumnModel* theWrappedObject, int  arg__1);
   TableColumn*  py_q_getColumn(TableColumnModel* theWrappedObject, int  arg__1){  return (((PythonQtPublicPromoter_TableColumnModel*)theWrappedObject)->py_q_getColumn(arg__1));}
   int  getColumnCount(TableColumnModel* theWrappedObject);
   int  py_q_getColumnCount(TableColumnModel* theWrappedObject){  return (((PythonQtPublicPromoter_TableColumnModel*)theWrappedObject)->py_q_getColumnCount());}
   int  getColumnIndex(TableColumnModel* theWrappedObject, QObject*  arg__1);
   int  py_q_getColumnIndex(TableColumnModel* theWrappedObject, QObject*  arg__1){  return (((PythonQtPublicPromoter_TableColumnModel*)theWrappedObject)->py_q_getColumnIndex(arg__1));}
   int  getColumnIndexAtX(TableColumnModel* theWrappedObject, int  arg__1);
   int  py_q_getColumnIndexAtX(TableColumnModel* theWrappedObject, int  arg__1){  return (((PythonQtPublicPromoter_TableColumnModel*)theWrappedObject)->py_q_getColumnIndexAtX(arg__1));}
   int  getColumnMargin(TableColumnModel* theWrappedObject);
   int  py_q_getColumnMargin(TableColumnModel* theWrappedObject){  return (((PythonQtPublicPromoter_TableColumnModel*)theWrappedObject)->py_q_getColumnMargin());}
   bool  getColumnSelectionAllowed(TableColumnModel* theWrappedObject);
   bool  py_q_getColumnSelectionAllowed(TableColumnModel* theWrappedObject){  return (((PythonQtPublicPromoter_TableColumnModel*)theWrappedObject)->py_q_getColumnSelectionAllowed());}
   int  getSelectedColumnCount(TableColumnModel* theWrappedObject);
   int  py_q_getSelectedColumnCount(TableColumnModel* theWrappedObject){  return (((PythonQtPublicPromoter_TableColumnModel*)theWrappedObject)->py_q_getSelectedColumnCount());}
   QList<int >  getSelectedColumns(TableColumnModel* theWrappedObject);
   QList<int >  py_q_getSelectedColumns(TableColumnModel* theWrappedObject){  return (((PythonQtPublicPromoter_TableColumnModel*)theWrappedObject)->py_q_getSelectedColumns());}
   ListSelectionModel*  getSelectionModel(TableColumnModel* theWrappedObject);
   ListSelectionModel*  py_q_getSelectionModel(TableColumnModel* theWrappedObject){  return (((PythonQtPublicPromoter_TableColumnModel*)theWrappedObject)->py_q_getSelectionModel());}
   int  getTotalColumnWidth(TableColumnModel* theWrappedObject);
   int  py_q_getTotalColumnWidth(TableColumnModel* theWrappedObject){  return (((PythonQtPublicPromoter_TableColumnModel*)theWrappedObject)->py_q_getTotalColumnWidth());}
   void moveColumn(TableColumnModel* theWrappedObject, int  arg__1, int  arg__2);
   void py_q_moveColumn(TableColumnModel* theWrappedObject, int  arg__1, int  arg__2){  (((PythonQtPublicPromoter_TableColumnModel*)theWrappedObject)->py_q_moveColumn(arg__1, arg__2));}
   void removeColumn(TableColumnModel* theWrappedObject, TableColumn*  arg__1);
   void py_q_removeColumn(TableColumnModel* theWrappedObject, TableColumn*  arg__1){  (((PythonQtPublicPromoter_TableColumnModel*)theWrappedObject)->py_q_removeColumn(arg__1));}
   void setColumnMargin(TableColumnModel* theWrappedObject, int  arg__1);
   void py_q_setColumnMargin(TableColumnModel* theWrappedObject, int  arg__1){  (((PythonQtPublicPromoter_TableColumnModel*)theWrappedObject)->py_q_setColumnMargin(arg__1));}
   void setColumnSelectionAllowed(TableColumnModel* theWrappedObject, bool  arg__1);
   void py_q_setColumnSelectionAllowed(TableColumnModel* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_TableColumnModel*)theWrappedObject)->py_q_setColumnSelectionAllowed(arg__1));}
   void setSelectionModel(TableColumnModel* theWrappedObject, ListSelectionModel*  arg__1);
   void py_q_setSelectionModel(TableColumnModel* theWrappedObject, ListSelectionModel*  arg__1){  (((PythonQtPublicPromoter_TableColumnModel*)theWrappedObject)->py_q_setSelectionModel(arg__1));}
};





class PythonQtShell_Throttle : public Throttle
{
public:
    PythonQtShell_Throttle(QObject*  parent = 0):Throttle(parent),_wrapper(NULL) {}

   ~PythonQtShell_Throttle();

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
virtual bool  getIsForward();
virtual QVector<PropertyChangeListener* >*  getListeners();
virtual LocoAddress*  getLocoAddress();
virtual BasicRosterEntry*  getRosterEntry();
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
virtual void setIsForward(bool  arg__1);
virtual void setRosterEntry(BasicRosterEntry*  arg__1);
virtual void setSpeedSetting(float  arg__1);
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_Throttle : public Throttle
{ public:
inline void py_q_addPropertyChangeListener(PropertyChangeListener*  arg__1) { Throttle::addPropertyChangeListener(arg__1); }
inline bool  py_q_getF0() { return Throttle::getF0(); }
inline bool  py_q_getF0Momentary() { return Throttle::getF0Momentary(); }
inline bool  py_q_getF1() { return Throttle::getF1(); }
inline bool  py_q_getF10() { return Throttle::getF10(); }
inline bool  py_q_getF10Momentary() { return Throttle::getF10Momentary(); }
inline bool  py_q_getF11() { return Throttle::getF11(); }
inline bool  py_q_getF11Momentary() { return Throttle::getF11Momentary(); }
inline bool  py_q_getF12() { return Throttle::getF12(); }
inline bool  py_q_getF12Momentary() { return Throttle::getF12Momentary(); }
inline bool  py_q_getF13() { return Throttle::getF13(); }
inline bool  py_q_getF13Momentary() { return Throttle::getF13Momentary(); }
inline bool  py_q_getF14() { return Throttle::getF14(); }
inline bool  py_q_getF14Momentary() { return Throttle::getF14Momentary(); }
inline bool  py_q_getF15() { return Throttle::getF15(); }
inline bool  py_q_getF15Momentary() { return Throttle::getF15Momentary(); }
inline bool  py_q_getF16() { return Throttle::getF16(); }
inline bool  py_q_getF16Momentary() { return Throttle::getF16Momentary(); }
inline bool  py_q_getF17() { return Throttle::getF17(); }
inline bool  py_q_getF17Momentary() { return Throttle::getF17Momentary(); }
inline bool  py_q_getF18() { return Throttle::getF18(); }
inline bool  py_q_getF18Momentary() { return Throttle::getF18Momentary(); }
inline bool  py_q_getF19() { return Throttle::getF19(); }
inline bool  py_q_getF19Momentary() { return Throttle::getF19Momentary(); }
inline bool  py_q_getF1Momentary() { return Throttle::getF1Momentary(); }
inline bool  py_q_getF2() { return Throttle::getF2(); }
inline bool  py_q_getF20() { return Throttle::getF20(); }
inline bool  py_q_getF20Momentary() { return Throttle::getF20Momentary(); }
inline bool  py_q_getF21() { return Throttle::getF21(); }
inline bool  py_q_getF21Momentary() { return Throttle::getF21Momentary(); }
inline bool  py_q_getF22() { return Throttle::getF22(); }
inline bool  py_q_getF22Momentary() { return Throttle::getF22Momentary(); }
inline bool  py_q_getF23() { return Throttle::getF23(); }
inline bool  py_q_getF23Momentary() { return Throttle::getF23Momentary(); }
inline bool  py_q_getF24() { return Throttle::getF24(); }
inline bool  py_q_getF24Momentary() { return Throttle::getF24Momentary(); }
inline bool  py_q_getF25() { return Throttle::getF25(); }
inline bool  py_q_getF25Momentary() { return Throttle::getF25Momentary(); }
inline bool  py_q_getF26() { return Throttle::getF26(); }
inline bool  py_q_getF26Momentary() { return Throttle::getF26Momentary(); }
inline bool  py_q_getF27() { return Throttle::getF27(); }
inline bool  py_q_getF27Momentary() { return Throttle::getF27Momentary(); }
inline bool  py_q_getF28() { return Throttle::getF28(); }
inline bool  py_q_getF28Momentary() { return Throttle::getF28Momentary(); }
inline bool  py_q_getF2Momentary() { return Throttle::getF2Momentary(); }
inline bool  py_q_getF3() { return Throttle::getF3(); }
inline bool  py_q_getF3Momentary() { return Throttle::getF3Momentary(); }
inline bool  py_q_getF4() { return Throttle::getF4(); }
inline bool  py_q_getF4Momentary() { return Throttle::getF4Momentary(); }
inline bool  py_q_getF5() { return Throttle::getF5(); }
inline bool  py_q_getF5Momentary() { return Throttle::getF5Momentary(); }
inline bool  py_q_getF6() { return Throttle::getF6(); }
inline bool  py_q_getF6Momentary() { return Throttle::getF6Momentary(); }
inline bool  py_q_getF7() { return Throttle::getF7(); }
inline bool  py_q_getF7Momentary() { return Throttle::getF7Momentary(); }
inline bool  py_q_getF8() { return Throttle::getF8(); }
inline bool  py_q_getF8Momentary() { return Throttle::getF8Momentary(); }
inline bool  py_q_getF9() { return Throttle::getF9(); }
inline bool  py_q_getF9Momentary() { return Throttle::getF9Momentary(); }
inline bool  py_q_getIsForward() { return Throttle::getIsForward(); }
inline QVector<PropertyChangeListener* >*  py_q_getListeners() { return Throttle::getListeners(); }
inline LocoAddress*  py_q_getLocoAddress() { return Throttle::getLocoAddress(); }
inline BasicRosterEntry*  py_q_getRosterEntry() { return Throttle::getRosterEntry(); }
inline float  py_q_getSpeedSetting() { return Throttle::getSpeedSetting(); }
inline void py_q_removePropertyChangeListener(PropertyChangeListener*  arg__1) { Throttle::removePropertyChangeListener(arg__1); }
inline void py_q_setF0(bool  arg__1) { Throttle::setF0(arg__1); }
inline void py_q_setF0Momentary(bool  arg__1) { Throttle::setF0Momentary(arg__1); }
inline void py_q_setF1(bool  arg__1) { Throttle::setF1(arg__1); }
inline void py_q_setF10(bool  arg__1) { Throttle::setF10(arg__1); }
inline void py_q_setF10Momentary(bool  arg__1) { Throttle::setF10Momentary(arg__1); }
inline void py_q_setF11(bool  arg__1) { Throttle::setF11(arg__1); }
inline void py_q_setF11Momentary(bool  arg__1) { Throttle::setF11Momentary(arg__1); }
inline void py_q_setF12(bool  arg__1) { Throttle::setF12(arg__1); }
inline void py_q_setF12Momentary(bool  arg__1) { Throttle::setF12Momentary(arg__1); }
inline void py_q_setF13(bool  arg__1) { Throttle::setF13(arg__1); }
inline void py_q_setF13Momentary(bool  arg__1) { Throttle::setF13Momentary(arg__1); }
inline void py_q_setF14(bool  arg__1) { Throttle::setF14(arg__1); }
inline void py_q_setF14Momentary(bool  arg__1) { Throttle::setF14Momentary(arg__1); }
inline void py_q_setF15(bool  arg__1) { Throttle::setF15(arg__1); }
inline void py_q_setF15Momentary(bool  arg__1) { Throttle::setF15Momentary(arg__1); }
inline void py_q_setF16(bool  arg__1) { Throttle::setF16(arg__1); }
inline void py_q_setF16Momentary(bool  arg__1) { Throttle::setF16Momentary(arg__1); }
inline void py_q_setF17(bool  arg__1) { Throttle::setF17(arg__1); }
inline void py_q_setF17Momentary(bool  arg__1) { Throttle::setF17Momentary(arg__1); }
inline void py_q_setF18(bool  arg__1) { Throttle::setF18(arg__1); }
inline void py_q_setF18Momentary(bool  arg__1) { Throttle::setF18Momentary(arg__1); }
inline void py_q_setF19(bool  arg__1) { Throttle::setF19(arg__1); }
inline void py_q_setF19Momentary(bool  arg__1) { Throttle::setF19Momentary(arg__1); }
inline void py_q_setF1Momentary(bool  arg__1) { Throttle::setF1Momentary(arg__1); }
inline void py_q_setF2(bool  arg__1) { Throttle::setF2(arg__1); }
inline void py_q_setF20(bool  arg__1) { Throttle::setF20(arg__1); }
inline void py_q_setF20Momentary(bool  arg__1) { Throttle::setF20Momentary(arg__1); }
inline void py_q_setF21(bool  arg__1) { Throttle::setF21(arg__1); }
inline void py_q_setF21Momentary(bool  arg__1) { Throttle::setF21Momentary(arg__1); }
inline void py_q_setF22(bool  arg__1) { Throttle::setF22(arg__1); }
inline void py_q_setF22Momentary(bool  arg__1) { Throttle::setF22Momentary(arg__1); }
inline void py_q_setF23(bool  arg__1) { Throttle::setF23(arg__1); }
inline void py_q_setF23Momentary(bool  arg__1) { Throttle::setF23Momentary(arg__1); }
inline void py_q_setF24(bool  arg__1) { Throttle::setF24(arg__1); }
inline void py_q_setF24Momentary(bool  arg__1) { Throttle::setF24Momentary(arg__1); }
inline void py_q_setF25(bool  arg__1) { Throttle::setF25(arg__1); }
inline void py_q_setF25Momentary(bool  arg__1) { Throttle::setF25Momentary(arg__1); }
inline void py_q_setF26(bool  arg__1) { Throttle::setF26(arg__1); }
inline void py_q_setF26Momentary(bool  arg__1) { Throttle::setF26Momentary(arg__1); }
inline void py_q_setF27(bool  arg__1) { Throttle::setF27(arg__1); }
inline void py_q_setF27Momentary(bool  arg__1) { Throttle::setF27Momentary(arg__1); }
inline void py_q_setF28(bool  arg__1) { Throttle::setF28(arg__1); }
inline void py_q_setF28Momentary(bool  arg__1) { Throttle::setF28Momentary(arg__1); }
inline void py_q_setF2Momentary(bool  arg__1) { Throttle::setF2Momentary(arg__1); }
inline void py_q_setF3(bool  arg__1) { Throttle::setF3(arg__1); }
inline void py_q_setF3Momentary(bool  arg__1) { Throttle::setF3Momentary(arg__1); }
inline void py_q_setF4(bool  arg__1) { Throttle::setF4(arg__1); }
inline void py_q_setF4Momentary(bool  arg__1) { Throttle::setF4Momentary(arg__1); }
inline void py_q_setF5(bool  arg__1) { Throttle::setF5(arg__1); }
inline void py_q_setF5Momentary(bool  arg__1) { Throttle::setF5Momentary(arg__1); }
inline void py_q_setF6(bool  arg__1) { Throttle::setF6(arg__1); }
inline void py_q_setF6Momentary(bool  arg__1) { Throttle::setF6Momentary(arg__1); }
inline void py_q_setF7(bool  arg__1) { Throttle::setF7(arg__1); }
inline void py_q_setF7Momentary(bool  arg__1) { Throttle::setF7Momentary(arg__1); }
inline void py_q_setF8(bool  arg__1) { Throttle::setF8(arg__1); }
inline void py_q_setF8Momentary(bool  arg__1) { Throttle::setF8Momentary(arg__1); }
inline void py_q_setF9(bool  arg__1) { Throttle::setF9(arg__1); }
inline void py_q_setF9Momentary(bool  arg__1) { Throttle::setF9Momentary(arg__1); }
inline void py_q_setIsForward(bool  arg__1) { Throttle::setIsForward(arg__1); }
inline void py_q_setRosterEntry(BasicRosterEntry*  arg__1) { Throttle::setRosterEntry(arg__1); }
inline void py_q_setSpeedSetting(float  arg__1) { Throttle::setSpeedSetting(arg__1); }
};

class PythonQtWrapper_Throttle : public QObject
{ Q_OBJECT
public:
public slots:
Throttle* new_Throttle(QObject*  parent = 0);
void delete_Throttle(Throttle* obj) { delete obj; } 
   void addPropertyChangeListener(Throttle* theWrappedObject, PropertyChangeListener*  arg__1);
   void py_q_addPropertyChangeListener(Throttle* theWrappedObject, PropertyChangeListener*  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_addPropertyChangeListener(arg__1));}
   bool  getF0(Throttle* theWrappedObject);
   bool  py_q_getF0(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF0());}
   bool  getF0Momentary(Throttle* theWrappedObject);
   bool  py_q_getF0Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF0Momentary());}
   bool  getF1(Throttle* theWrappedObject);
   bool  py_q_getF1(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF1());}
   bool  getF10(Throttle* theWrappedObject);
   bool  py_q_getF10(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF10());}
   bool  getF10Momentary(Throttle* theWrappedObject);
   bool  py_q_getF10Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF10Momentary());}
   bool  getF11(Throttle* theWrappedObject);
   bool  py_q_getF11(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF11());}
   bool  getF11Momentary(Throttle* theWrappedObject);
   bool  py_q_getF11Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF11Momentary());}
   bool  getF12(Throttle* theWrappedObject);
   bool  py_q_getF12(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF12());}
   bool  getF12Momentary(Throttle* theWrappedObject);
   bool  py_q_getF12Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF12Momentary());}
   bool  getF13(Throttle* theWrappedObject);
   bool  py_q_getF13(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF13());}
   bool  getF13Momentary(Throttle* theWrappedObject);
   bool  py_q_getF13Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF13Momentary());}
   bool  getF14(Throttle* theWrappedObject);
   bool  py_q_getF14(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF14());}
   bool  getF14Momentary(Throttle* theWrappedObject);
   bool  py_q_getF14Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF14Momentary());}
   bool  getF15(Throttle* theWrappedObject);
   bool  py_q_getF15(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF15());}
   bool  getF15Momentary(Throttle* theWrappedObject);
   bool  py_q_getF15Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF15Momentary());}
   bool  getF16(Throttle* theWrappedObject);
   bool  py_q_getF16(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF16());}
   bool  getF16Momentary(Throttle* theWrappedObject);
   bool  py_q_getF16Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF16Momentary());}
   bool  getF17(Throttle* theWrappedObject);
   bool  py_q_getF17(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF17());}
   bool  getF17Momentary(Throttle* theWrappedObject);
   bool  py_q_getF17Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF17Momentary());}
   bool  getF18(Throttle* theWrappedObject);
   bool  py_q_getF18(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF18());}
   bool  getF18Momentary(Throttle* theWrappedObject);
   bool  py_q_getF18Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF18Momentary());}
   bool  getF19(Throttle* theWrappedObject);
   bool  py_q_getF19(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF19());}
   bool  getF19Momentary(Throttle* theWrappedObject);
   bool  py_q_getF19Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF19Momentary());}
   bool  getF1Momentary(Throttle* theWrappedObject);
   bool  py_q_getF1Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF1Momentary());}
   bool  getF2(Throttle* theWrappedObject);
   bool  py_q_getF2(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF2());}
   bool  getF20(Throttle* theWrappedObject);
   bool  py_q_getF20(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF20());}
   bool  getF20Momentary(Throttle* theWrappedObject);
   bool  py_q_getF20Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF20Momentary());}
   bool  getF21(Throttle* theWrappedObject);
   bool  py_q_getF21(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF21());}
   bool  getF21Momentary(Throttle* theWrappedObject);
   bool  py_q_getF21Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF21Momentary());}
   bool  getF22(Throttle* theWrappedObject);
   bool  py_q_getF22(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF22());}
   bool  getF22Momentary(Throttle* theWrappedObject);
   bool  py_q_getF22Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF22Momentary());}
   bool  getF23(Throttle* theWrappedObject);
   bool  py_q_getF23(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF23());}
   bool  getF23Momentary(Throttle* theWrappedObject);
   bool  py_q_getF23Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF23Momentary());}
   bool  getF24(Throttle* theWrappedObject);
   bool  py_q_getF24(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF24());}
   bool  getF24Momentary(Throttle* theWrappedObject);
   bool  py_q_getF24Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF24Momentary());}
   bool  getF25(Throttle* theWrappedObject);
   bool  py_q_getF25(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF25());}
   bool  getF25Momentary(Throttle* theWrappedObject);
   bool  py_q_getF25Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF25Momentary());}
   bool  getF26(Throttle* theWrappedObject);
   bool  py_q_getF26(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF26());}
   bool  getF26Momentary(Throttle* theWrappedObject);
   bool  py_q_getF26Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF26Momentary());}
   bool  getF27(Throttle* theWrappedObject);
   bool  py_q_getF27(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF27());}
   bool  getF27Momentary(Throttle* theWrappedObject);
   bool  py_q_getF27Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF27Momentary());}
   bool  getF28(Throttle* theWrappedObject);
   bool  py_q_getF28(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF28());}
   bool  getF28Momentary(Throttle* theWrappedObject);
   bool  py_q_getF28Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF28Momentary());}
   bool  getF2Momentary(Throttle* theWrappedObject);
   bool  py_q_getF2Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF2Momentary());}
   bool  getF3(Throttle* theWrappedObject);
   bool  py_q_getF3(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF3());}
   bool  getF3Momentary(Throttle* theWrappedObject);
   bool  py_q_getF3Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF3Momentary());}
   bool  getF4(Throttle* theWrappedObject);
   bool  py_q_getF4(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF4());}
   bool  getF4Momentary(Throttle* theWrappedObject);
   bool  py_q_getF4Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF4Momentary());}
   bool  getF5(Throttle* theWrappedObject);
   bool  py_q_getF5(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF5());}
   bool  getF5Momentary(Throttle* theWrappedObject);
   bool  py_q_getF5Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF5Momentary());}
   bool  getF6(Throttle* theWrappedObject);
   bool  py_q_getF6(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF6());}
   bool  getF6Momentary(Throttle* theWrappedObject);
   bool  py_q_getF6Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF6Momentary());}
   bool  getF7(Throttle* theWrappedObject);
   bool  py_q_getF7(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF7());}
   bool  getF7Momentary(Throttle* theWrappedObject);
   bool  py_q_getF7Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF7Momentary());}
   bool  getF8(Throttle* theWrappedObject);
   bool  py_q_getF8(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF8());}
   bool  getF8Momentary(Throttle* theWrappedObject);
   bool  py_q_getF8Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF8Momentary());}
   bool  getF9(Throttle* theWrappedObject);
   bool  py_q_getF9(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF9());}
   bool  getF9Momentary(Throttle* theWrappedObject);
   bool  py_q_getF9Momentary(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getF9Momentary());}
   bool  getIsForward(Throttle* theWrappedObject);
   bool  py_q_getIsForward(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getIsForward());}
   QVector<PropertyChangeListener* >*  getListeners(Throttle* theWrappedObject);
   QVector<PropertyChangeListener* >*  py_q_getListeners(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getListeners());}
   LocoAddress*  getLocoAddress(Throttle* theWrappedObject);
   LocoAddress*  py_q_getLocoAddress(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getLocoAddress());}
   BasicRosterEntry*  getRosterEntry(Throttle* theWrappedObject);
   BasicRosterEntry*  py_q_getRosterEntry(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getRosterEntry());}
   float  getSpeedSetting(Throttle* theWrappedObject);
   float  py_q_getSpeedSetting(Throttle* theWrappedObject){  return (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_getSpeedSetting());}
   void removePropertyChangeListener(Throttle* theWrappedObject, PropertyChangeListener*  arg__1);
   void py_q_removePropertyChangeListener(Throttle* theWrappedObject, PropertyChangeListener*  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_removePropertyChangeListener(arg__1));}
   void setF0(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF0(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF0(arg__1));}
   void setF0Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF0Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF0Momentary(arg__1));}
   void setF1(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF1(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF1(arg__1));}
   void setF10(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF10(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF10(arg__1));}
   void setF10Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF10Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF10Momentary(arg__1));}
   void setF11(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF11(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF11(arg__1));}
   void setF11Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF11Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF11Momentary(arg__1));}
   void setF12(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF12(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF12(arg__1));}
   void setF12Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF12Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF12Momentary(arg__1));}
   void setF13(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF13(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF13(arg__1));}
   void setF13Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF13Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF13Momentary(arg__1));}
   void setF14(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF14(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF14(arg__1));}
   void setF14Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF14Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF14Momentary(arg__1));}
   void setF15(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF15(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF15(arg__1));}
   void setF15Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF15Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF15Momentary(arg__1));}
   void setF16(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF16(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF16(arg__1));}
   void setF16Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF16Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF16Momentary(arg__1));}
   void setF17(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF17(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF17(arg__1));}
   void setF17Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF17Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF17Momentary(arg__1));}
   void setF18(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF18(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF18(arg__1));}
   void setF18Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF18Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF18Momentary(arg__1));}
   void setF19(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF19(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF19(arg__1));}
   void setF19Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF19Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF19Momentary(arg__1));}
   void setF1Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF1Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF1Momentary(arg__1));}
   void setF2(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF2(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF2(arg__1));}
   void setF20(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF20(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF20(arg__1));}
   void setF20Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF20Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF20Momentary(arg__1));}
   void setF21(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF21(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF21(arg__1));}
   void setF21Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF21Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF21Momentary(arg__1));}
   void setF22(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF22(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF22(arg__1));}
   void setF22Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF22Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF22Momentary(arg__1));}
   void setF23(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF23(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF23(arg__1));}
   void setF23Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF23Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF23Momentary(arg__1));}
   void setF24(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF24(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF24(arg__1));}
   void setF24Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF24Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF24Momentary(arg__1));}
   void setF25(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF25(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF25(arg__1));}
   void setF25Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF25Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF25Momentary(arg__1));}
   void setF26(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF26(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF26(arg__1));}
   void setF26Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF26Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF26Momentary(arg__1));}
   void setF27(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF27(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF27(arg__1));}
   void setF27Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF27Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF27Momentary(arg__1));}
   void setF28(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF28(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF28(arg__1));}
   void setF28Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF28Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF28Momentary(arg__1));}
   void setF2Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF2Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF2Momentary(arg__1));}
   void setF3(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF3(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF3(arg__1));}
   void setF3Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF3Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF3Momentary(arg__1));}
   void setF4(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF4(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF4(arg__1));}
   void setF4Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF4Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF4Momentary(arg__1));}
   void setF5(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF5(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF5(arg__1));}
   void setF5Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF5Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF5Momentary(arg__1));}
   void setF6(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF6(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF6(arg__1));}
   void setF6Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF6Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF6Momentary(arg__1));}
   void setF7(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF7(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF7(arg__1));}
   void setF7Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF7Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF7Momentary(arg__1));}
   void setF8(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF8(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF8(arg__1));}
   void setF8Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF8Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF8Momentary(arg__1));}
   void setF9(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF9(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF9(arg__1));}
   void setF9Momentary(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setF9Momentary(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setF9Momentary(arg__1));}
   void setIsForward(Throttle* theWrappedObject, bool  arg__1);
   void py_q_setIsForward(Throttle* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setIsForward(arg__1));}
   void setRosterEntry(Throttle* theWrappedObject, BasicRosterEntry*  arg__1);
   void py_q_setRosterEntry(Throttle* theWrappedObject, BasicRosterEntry*  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setRosterEntry(arg__1));}
   void setSpeedSetting(Throttle* theWrappedObject, float  arg__1);
   void py_q_setSpeedSetting(Throttle* theWrappedObject, float  arg__1){  (((PythonQtPublicPromoter_Throttle*)theWrappedObject)->py_q_setSpeedSetting(arg__1));}
};





class PythonQtShell_ThrottleManager : public ThrottleManager
{
public:
    PythonQtShell_ThrottleManager(QObject*  parent = 0):ThrottleManager(parent),_wrapper(NULL) {}

   ~PythonQtShell_ThrottleManager();

virtual bool  addressStillRequired(DccLocoAddress*  arg__1);
virtual bool  addressTypeUnique();
virtual void attachListener(DccLocoAddress*  arg__1, PropertyChangeListener*  arg__2);
virtual bool  canBeLongAddress(int  arg__1);
virtual bool  canBeShortAddress(int  arg__1);
virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual LocoAddress*  getAddress(QString  arg__1, LocoAddress::Protocol  arg__2);
virtual LocoAddress*  getAddress(QString  arg__1, QString  arg__2);
virtual QList<LocoAddress::Protocol >  getAddressProtocolTypes();
virtual QString  getAddressTypeString(LocoAddress::Protocol  arg__1);
virtual QStringList  getAddressTypes();
virtual int  getMode(int  arg__1);
virtual LocoAddress::Protocol  getProtocolFromString(QString  arg__1);
virtual QVariant  getThrottleInfo(DccLocoAddress*  arg__1, QString  arg__2);
virtual QString  getUserName();
virtual bool  hasDispatchFunction();
virtual void removeListener(DccLocoAddress*  arg__1, PropertyChangeListener*  arg__2);
virtual int  supportedSpeedModes();
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_ThrottleManager : public ThrottleManager
{ public:
inline bool  py_q_addressStillRequired(DccLocoAddress*  arg__1) { return ThrottleManager::addressStillRequired(arg__1); }
inline bool  py_q_addressTypeUnique() { return ThrottleManager::addressTypeUnique(); }
inline void py_q_attachListener(DccLocoAddress*  arg__1, PropertyChangeListener*  arg__2) { ThrottleManager::attachListener(arg__1, arg__2); }
inline bool  py_q_canBeLongAddress(int  arg__1) { return ThrottleManager::canBeLongAddress(arg__1); }
inline bool  py_q_canBeShortAddress(int  arg__1) { return ThrottleManager::canBeShortAddress(arg__1); }
inline LocoAddress*  py_q_getAddress(QString  arg__1, LocoAddress::Protocol  arg__2) { return ThrottleManager::getAddress(arg__1, arg__2); }
inline LocoAddress*  py_q_getAddress(QString  arg__1, QString  arg__2) { return ThrottleManager::getAddress(arg__1, arg__2); }
inline QList<LocoAddress::Protocol >  py_q_getAddressProtocolTypes() { return ThrottleManager::getAddressProtocolTypes(); }
inline QString  py_q_getAddressTypeString(LocoAddress::Protocol  arg__1) { return ThrottleManager::getAddressTypeString(arg__1); }
inline QStringList  py_q_getAddressTypes() { return ThrottleManager::getAddressTypes(); }
inline int  py_q_getMode(int  arg__1) { return ThrottleManager::getMode(arg__1); }
inline LocoAddress::Protocol  py_q_getProtocolFromString(QString  arg__1) { return ThrottleManager::getProtocolFromString(arg__1); }
inline QVariant  py_q_getThrottleInfo(DccLocoAddress*  arg__1, QString  arg__2) { return ThrottleManager::getThrottleInfo(arg__1, arg__2); }
inline QString  py_q_getUserName() { return ThrottleManager::getUserName(); }
inline bool  py_q_hasDispatchFunction() { return ThrottleManager::hasDispatchFunction(); }
inline void py_q_removeListener(DccLocoAddress*  arg__1, PropertyChangeListener*  arg__2) { ThrottleManager::removeListener(arg__1, arg__2); }
inline int  py_q_supportedSpeedModes() { return ThrottleManager::supportedSpeedModes(); }
};

class PythonQtWrapper_ThrottleManager : public QObject
{ Q_OBJECT
public:
public slots:
ThrottleManager* new_ThrottleManager(QObject*  parent = 0);
void delete_ThrottleManager(ThrottleManager* obj) { delete obj; } 
   bool  addressStillRequired(ThrottleManager* theWrappedObject, DccLocoAddress*  arg__1);
   bool  py_q_addressStillRequired(ThrottleManager* theWrappedObject, DccLocoAddress*  arg__1){  return (((PythonQtPublicPromoter_ThrottleManager*)theWrappedObject)->py_q_addressStillRequired(arg__1));}
   bool  addressTypeUnique(ThrottleManager* theWrappedObject);
   bool  py_q_addressTypeUnique(ThrottleManager* theWrappedObject){  return (((PythonQtPublicPromoter_ThrottleManager*)theWrappedObject)->py_q_addressTypeUnique());}
   void attachListener(ThrottleManager* theWrappedObject, DccLocoAddress*  arg__1, PropertyChangeListener*  arg__2);
   void py_q_attachListener(ThrottleManager* theWrappedObject, DccLocoAddress*  arg__1, PropertyChangeListener*  arg__2){  (((PythonQtPublicPromoter_ThrottleManager*)theWrappedObject)->py_q_attachListener(arg__1, arg__2));}
   bool  canBeLongAddress(ThrottleManager* theWrappedObject, int  arg__1);
   bool  py_q_canBeLongAddress(ThrottleManager* theWrappedObject, int  arg__1){  return (((PythonQtPublicPromoter_ThrottleManager*)theWrappedObject)->py_q_canBeLongAddress(arg__1));}
   bool  canBeShortAddress(ThrottleManager* theWrappedObject, int  arg__1);
   bool  py_q_canBeShortAddress(ThrottleManager* theWrappedObject, int  arg__1){  return (((PythonQtPublicPromoter_ThrottleManager*)theWrappedObject)->py_q_canBeShortAddress(arg__1));}
   LocoAddress*  getAddress(ThrottleManager* theWrappedObject, QString  arg__1, LocoAddress::Protocol  arg__2);
   LocoAddress*  py_q_getAddress(ThrottleManager* theWrappedObject, QString  arg__1, LocoAddress::Protocol  arg__2){  return (((PythonQtPublicPromoter_ThrottleManager*)theWrappedObject)->py_q_getAddress(arg__1, arg__2));}
   LocoAddress*  getAddress(ThrottleManager* theWrappedObject, QString  arg__1, QString  arg__2);
   LocoAddress*  py_q_getAddress(ThrottleManager* theWrappedObject, QString  arg__1, QString  arg__2){  return (((PythonQtPublicPromoter_ThrottleManager*)theWrappedObject)->py_q_getAddress(arg__1, arg__2));}
   QList<LocoAddress::Protocol >  getAddressProtocolTypes(ThrottleManager* theWrappedObject);
   QList<LocoAddress::Protocol >  py_q_getAddressProtocolTypes(ThrottleManager* theWrappedObject){  return (((PythonQtPublicPromoter_ThrottleManager*)theWrappedObject)->py_q_getAddressProtocolTypes());}
   QString  getAddressTypeString(ThrottleManager* theWrappedObject, LocoAddress::Protocol  arg__1);
   QString  py_q_getAddressTypeString(ThrottleManager* theWrappedObject, LocoAddress::Protocol  arg__1){  return (((PythonQtPublicPromoter_ThrottleManager*)theWrappedObject)->py_q_getAddressTypeString(arg__1));}
   QStringList  getAddressTypes(ThrottleManager* theWrappedObject);
   QStringList  py_q_getAddressTypes(ThrottleManager* theWrappedObject){  return (((PythonQtPublicPromoter_ThrottleManager*)theWrappedObject)->py_q_getAddressTypes());}
   int  getMode(ThrottleManager* theWrappedObject, int  arg__1);
   int  py_q_getMode(ThrottleManager* theWrappedObject, int  arg__1){  return (((PythonQtPublicPromoter_ThrottleManager*)theWrappedObject)->py_q_getMode(arg__1));}
   LocoAddress::Protocol  getProtocolFromString(ThrottleManager* theWrappedObject, QString  arg__1);
   LocoAddress::Protocol  py_q_getProtocolFromString(ThrottleManager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_ThrottleManager*)theWrappedObject)->py_q_getProtocolFromString(arg__1));}
   QVariant  getThrottleInfo(ThrottleManager* theWrappedObject, DccLocoAddress*  arg__1, QString  arg__2);
   QVariant  py_q_getThrottleInfo(ThrottleManager* theWrappedObject, DccLocoAddress*  arg__1, QString  arg__2){  return (((PythonQtPublicPromoter_ThrottleManager*)theWrappedObject)->py_q_getThrottleInfo(arg__1, arg__2));}
   QString  getUserName(ThrottleManager* theWrappedObject);
   QString  py_q_getUserName(ThrottleManager* theWrappedObject){  return (((PythonQtPublicPromoter_ThrottleManager*)theWrappedObject)->py_q_getUserName());}
   bool  hasDispatchFunction(ThrottleManager* theWrappedObject);
   bool  py_q_hasDispatchFunction(ThrottleManager* theWrappedObject){  return (((PythonQtPublicPromoter_ThrottleManager*)theWrappedObject)->py_q_hasDispatchFunction());}
   ThrottleManager*  static_ThrottleManager_instance();
   void removeListener(ThrottleManager* theWrappedObject, DccLocoAddress*  arg__1, PropertyChangeListener*  arg__2);
   void py_q_removeListener(ThrottleManager* theWrappedObject, DccLocoAddress*  arg__1, PropertyChangeListener*  arg__2){  (((PythonQtPublicPromoter_ThrottleManager*)theWrappedObject)->py_q_removeListener(arg__1, arg__2));}
   int  supportedSpeedModes(ThrottleManager* theWrappedObject);
   int  py_q_supportedSpeedModes(ThrottleManager* theWrappedObject){  return (((PythonQtPublicPromoter_ThrottleManager*)theWrappedObject)->py_q_supportedSpeedModes());}
};





class PythonQtShell_Turnout : public Turnout
{
public:
    PythonQtShell_Turnout(QObject*  parent = 0):Turnout(parent),_wrapper(NULL) {}
    PythonQtShell_Turnout(QString  sysName, QObject*  parent = 0):Turnout(sysName, parent),_wrapper(NULL) {}
    PythonQtShell_Turnout(QString  sysName, QString  userName, QObject*  parent = 0):Turnout(sysName, userName, parent),_wrapper(NULL) {}

   ~PythonQtShell_Turnout();

virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(PropertyChangeListener*  l, QString  beanRef, const QString  listenerRef);
virtual bool  canInvert() const;
virtual bool  canLock(int  arg__1);
virtual void childEvent(QChildEvent*  event);
virtual int  compareSystemNameSuffix(QString  suffix1, QString  suffix2, NamedBean*  n);
virtual int  compareTo(NamedBean*  n2);
virtual void customEvent(QEvent*  event);
virtual QString  describeState(int  state);
virtual void dispose();
virtual void enableLockOperation(int  arg__1, bool  arg__2);
virtual bool  equals(QObject*  obj);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
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
virtual bool  getLocked(int  arg__1);
virtual int  getNumPropertyChangeListeners();
virtual int  getNumberOutputBits();
virtual int  getPossibleLockModes();
virtual QVariant  getProperty(QString  key);
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners();
virtual QList<PropertyChangeListener* >*  getPropertyChangeListeners(QString  name);
virtual QSet<QString >  getPropertyKeys();
virtual bool  getReportLocked();
virtual Sensor*  getSecondSensor();
virtual int  getState();
virtual float  getStraightLimit();
virtual QString  getStraightSpeed();
virtual QString  getSystemName() const;
virtual TurnoutOperation*  getTurnoutOperation();
virtual QString  getUserName();
virtual QStringList  getValidDecoderNames();
virtual QStringList  getValidFeedbackNames();
virtual int  getValidFeedbackTypes();
virtual bool  hashCode();
virtual bool  isConsistentState();
virtual void provideFirstFeedbackSensor(QString  arg__1) throw (JmriException) ;
virtual void provideSecondFeedbackSensor(QString  arg__1) throw (JmriException) ;
virtual void removeProperty(QString  key);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void requestUpdateFromLayout();
virtual void setBinaryOutput(bool  arg__1);
virtual void setCommandedState(int  arg__1);
virtual void setComment(QString  comment);
virtual void setControlType(int  arg__1);
virtual void setDecoderName(QString  arg__1);
virtual void setDivergingSpeed(QString  arg__1) const throw (JmriException) ;
virtual void setFeedbackMode(QString  arg__1);
virtual void setFeedbackMode(int  arg__1);
virtual void setInhibitOperation(bool  arg__1);
virtual void setInitialKnownStateFromFeedback();
virtual void setInverted(bool  arg__1);
virtual void setLocked(int  arg__1, bool  arg__2);
virtual void setNumberOutputBits(int  arg__1);
virtual void setProperty(QString  key, QVariant  value);
virtual void setReportLocked(bool  arg__1);
virtual void setState(int  arg__1);
virtual void setStraightSpeed(QString  arg__1) const throw (JmriException) ;
virtual void setSysName(QString  s);
virtual void setTurnoutOperation(TurnoutOperation*  arg__1);
virtual void setUserName(QString  s);
virtual void timerEvent(QTimerEvent*  event);
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);
virtual void vetoableChange(PropertyChangeEvent*  evt) throw (PropertyVetoException);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_Turnout : public Turnout
{ public:
inline bool  py_q_canInvert() const { return Turnout::canInvert(); }
inline bool  py_q_canLock(int  arg__1) { return Turnout::canLock(arg__1); }
inline void py_q_enableLockOperation(int  arg__1, bool  arg__2) { Turnout::enableLockOperation(arg__1, arg__2); }
inline int  py_q_getCommandedState() { return Turnout::getCommandedState(); }
inline int  py_q_getControlType() { return Turnout::getControlType(); }
inline QString  py_q_getDecoderName() { return Turnout::getDecoderName(); }
inline float  py_q_getDivergingLimit() { return Turnout::getDivergingLimit(); }
inline QString  py_q_getDivergingSpeed() { return Turnout::getDivergingSpeed(); }
inline int  py_q_getFeedbackMode() { return Turnout::getFeedbackMode(); }
inline QString  py_q_getFeedbackModeName() { return Turnout::getFeedbackModeName(); }
inline Sensor*  py_q_getFirstSensor() { return Turnout::getFirstSensor(); }
inline bool  py_q_getInhibitOperation() { return Turnout::getInhibitOperation(); }
inline bool  py_q_getInverted() { return Turnout::getInverted(); }
inline int  py_q_getKnownState() { return Turnout::getKnownState(); }
inline bool  py_q_getLocked(int  arg__1) { return Turnout::getLocked(arg__1); }
inline int  py_q_getNumberOutputBits() { return Turnout::getNumberOutputBits(); }
inline int  py_q_getPossibleLockModes() { return Turnout::getPossibleLockModes(); }
inline bool  py_q_getReportLocked() { return Turnout::getReportLocked(); }
inline Sensor*  py_q_getSecondSensor() { return Turnout::getSecondSensor(); }
inline float  py_q_getStraightLimit() { return Turnout::getStraightLimit(); }
inline QString  py_q_getStraightSpeed() { return Turnout::getStraightSpeed(); }
inline TurnoutOperation*  py_q_getTurnoutOperation() { return Turnout::getTurnoutOperation(); }
inline QStringList  py_q_getValidDecoderNames() { return Turnout::getValidDecoderNames(); }
inline QStringList  py_q_getValidFeedbackNames() { return Turnout::getValidFeedbackNames(); }
inline int  py_q_getValidFeedbackTypes() { return Turnout::getValidFeedbackTypes(); }
inline bool  py_q_isConsistentState() { return Turnout::isConsistentState(); }
inline void py_q_provideFirstFeedbackSensor(QString  arg__1) throw (JmriException)  { Turnout::provideFirstFeedbackSensor(arg__1); }
inline void py_q_provideSecondFeedbackSensor(QString  arg__1) throw (JmriException)  { Turnout::provideSecondFeedbackSensor(arg__1); }
inline void py_q_requestUpdateFromLayout() { Turnout::requestUpdateFromLayout(); }
inline void py_q_setBinaryOutput(bool  arg__1) { Turnout::setBinaryOutput(arg__1); }
inline void py_q_setCommandedState(int  arg__1) { Turnout::setCommandedState(arg__1); }
inline void py_q_setControlType(int  arg__1) { Turnout::setControlType(arg__1); }
inline void py_q_setDecoderName(QString  arg__1) { Turnout::setDecoderName(arg__1); }
inline void py_q_setDivergingSpeed(QString  arg__1) const throw (JmriException)  { Turnout::setDivergingSpeed(arg__1); }
inline void py_q_setFeedbackMode(QString  arg__1) { Turnout::setFeedbackMode(arg__1); }
inline void py_q_setFeedbackMode(int  arg__1) { Turnout::setFeedbackMode(arg__1); }
inline void py_q_setInhibitOperation(bool  arg__1) { Turnout::setInhibitOperation(arg__1); }
inline void py_q_setInitialKnownStateFromFeedback() { Turnout::setInitialKnownStateFromFeedback(); }
inline void py_q_setInverted(bool  arg__1) { Turnout::setInverted(arg__1); }
inline void py_q_setLocked(int  arg__1, bool  arg__2) { Turnout::setLocked(arg__1, arg__2); }
inline void py_q_setNumberOutputBits(int  arg__1) { Turnout::setNumberOutputBits(arg__1); }
inline void py_q_setReportLocked(bool  arg__1) { Turnout::setReportLocked(arg__1); }
inline void py_q_setStraightSpeed(QString  arg__1) const throw (JmriException)  { Turnout::setStraightSpeed(arg__1); }
inline void py_q_setTurnoutOperation(TurnoutOperation*  arg__1) { Turnout::setTurnoutOperation(arg__1); }
};

class PythonQtWrapper_Turnout : public QObject
{ Q_OBJECT
public:
public slots:
Turnout* new_Turnout(QObject*  parent = 0);
Turnout* new_Turnout(QString  sysName, QObject*  parent = 0);
Turnout* new_Turnout(QString  sysName, QString  userName, QObject*  parent = 0);
void delete_Turnout(Turnout* obj) { delete obj; } 
   bool  canInvert(Turnout* theWrappedObject) const;
   bool  py_q_canInvert(Turnout* theWrappedObject) const{  return (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_canInvert());}
   bool  canLock(Turnout* theWrappedObject, int  arg__1);
   bool  py_q_canLock(Turnout* theWrappedObject, int  arg__1){  return (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_canLock(arg__1));}
   void enableLockOperation(Turnout* theWrappedObject, int  arg__1, bool  arg__2);
   void py_q_enableLockOperation(Turnout* theWrappedObject, int  arg__1, bool  arg__2){  (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_enableLockOperation(arg__1, arg__2));}
   int  getCommandedState(Turnout* theWrappedObject);
   int  py_q_getCommandedState(Turnout* theWrappedObject){  return (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_getCommandedState());}
   int  getControlType(Turnout* theWrappedObject);
   int  py_q_getControlType(Turnout* theWrappedObject){  return (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_getControlType());}
   QString  getDecoderName(Turnout* theWrappedObject);
   QString  py_q_getDecoderName(Turnout* theWrappedObject){  return (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_getDecoderName());}
   float  getDivergingLimit(Turnout* theWrappedObject);
   float  py_q_getDivergingLimit(Turnout* theWrappedObject){  return (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_getDivergingLimit());}
   QString  getDivergingSpeed(Turnout* theWrappedObject);
   QString  py_q_getDivergingSpeed(Turnout* theWrappedObject){  return (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_getDivergingSpeed());}
   int  getFeedbackMode(Turnout* theWrappedObject);
   int  py_q_getFeedbackMode(Turnout* theWrappedObject){  return (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_getFeedbackMode());}
   QString  getFeedbackModeName(Turnout* theWrappedObject);
   QString  py_q_getFeedbackModeName(Turnout* theWrappedObject){  return (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_getFeedbackModeName());}
   Sensor*  getFirstSensor(Turnout* theWrappedObject);
   Sensor*  py_q_getFirstSensor(Turnout* theWrappedObject){  return (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_getFirstSensor());}
   bool  getInhibitOperation(Turnout* theWrappedObject);
   bool  py_q_getInhibitOperation(Turnout* theWrappedObject){  return (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_getInhibitOperation());}
   bool  getInverted(Turnout* theWrappedObject);
   bool  py_q_getInverted(Turnout* theWrappedObject){  return (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_getInverted());}
   int  getKnownState(Turnout* theWrappedObject);
   int  py_q_getKnownState(Turnout* theWrappedObject){  return (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_getKnownState());}
   bool  getLocked(Turnout* theWrappedObject, int  arg__1);
   bool  py_q_getLocked(Turnout* theWrappedObject, int  arg__1){  return (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_getLocked(arg__1));}
   int  getNumberOutputBits(Turnout* theWrappedObject);
   int  py_q_getNumberOutputBits(Turnout* theWrappedObject){  return (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_getNumberOutputBits());}
   int  getPossibleLockModes(Turnout* theWrappedObject);
   int  py_q_getPossibleLockModes(Turnout* theWrappedObject){  return (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_getPossibleLockModes());}
   bool  getReportLocked(Turnout* theWrappedObject);
   bool  py_q_getReportLocked(Turnout* theWrappedObject){  return (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_getReportLocked());}
   Sensor*  getSecondSensor(Turnout* theWrappedObject);
   Sensor*  py_q_getSecondSensor(Turnout* theWrappedObject){  return (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_getSecondSensor());}
   float  getStraightLimit(Turnout* theWrappedObject);
   float  py_q_getStraightLimit(Turnout* theWrappedObject){  return (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_getStraightLimit());}
   QString  getStraightSpeed(Turnout* theWrappedObject);
   QString  py_q_getStraightSpeed(Turnout* theWrappedObject){  return (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_getStraightSpeed());}
   TurnoutOperation*  getTurnoutOperation(Turnout* theWrappedObject);
   TurnoutOperation*  py_q_getTurnoutOperation(Turnout* theWrappedObject){  return (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_getTurnoutOperation());}
   QStringList  getValidDecoderNames(Turnout* theWrappedObject);
   QStringList  py_q_getValidDecoderNames(Turnout* theWrappedObject){  return (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_getValidDecoderNames());}
   QStringList  getValidFeedbackNames(Turnout* theWrappedObject);
   QStringList  py_q_getValidFeedbackNames(Turnout* theWrappedObject){  return (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_getValidFeedbackNames());}
   int  getValidFeedbackTypes(Turnout* theWrappedObject);
   int  py_q_getValidFeedbackTypes(Turnout* theWrappedObject){  return (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_getValidFeedbackTypes());}
   int  static_Turnout_invertTurnoutState(int  inState);
   bool  isConsistentState(Turnout* theWrappedObject);
   bool  py_q_isConsistentState(Turnout* theWrappedObject){  return (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_isConsistentState());}
   void provideFirstFeedbackSensor(Turnout* theWrappedObject, QString  arg__1) throw (JmriException) ;
   void py_q_provideFirstFeedbackSensor(Turnout* theWrappedObject, QString  arg__1) throw (JmriException) {  (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_provideFirstFeedbackSensor(arg__1));}
   void provideSecondFeedbackSensor(Turnout* theWrappedObject, QString  arg__1) throw (JmriException) ;
   void py_q_provideSecondFeedbackSensor(Turnout* theWrappedObject, QString  arg__1) throw (JmriException) {  (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_provideSecondFeedbackSensor(arg__1));}
   void requestUpdateFromLayout(Turnout* theWrappedObject);
   void py_q_requestUpdateFromLayout(Turnout* theWrappedObject){  (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_requestUpdateFromLayout());}
   void setBinaryOutput(Turnout* theWrappedObject, bool  arg__1);
   void py_q_setBinaryOutput(Turnout* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_setBinaryOutput(arg__1));}
   void setCommandedState(Turnout* theWrappedObject, int  arg__1);
   void py_q_setCommandedState(Turnout* theWrappedObject, int  arg__1){  (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_setCommandedState(arg__1));}
   void setControlType(Turnout* theWrappedObject, int  arg__1);
   void py_q_setControlType(Turnout* theWrappedObject, int  arg__1){  (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_setControlType(arg__1));}
   void setDecoderName(Turnout* theWrappedObject, QString  arg__1);
   void py_q_setDecoderName(Turnout* theWrappedObject, QString  arg__1){  (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_setDecoderName(arg__1));}
   void setDivergingSpeed(Turnout* theWrappedObject, QString  arg__1) const throw (JmriException) ;
   void py_q_setDivergingSpeed(Turnout* theWrappedObject, QString  arg__1) const throw (JmriException) {  (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_setDivergingSpeed(arg__1));}
   void setFeedbackMode(Turnout* theWrappedObject, QString  arg__1);
   void py_q_setFeedbackMode(Turnout* theWrappedObject, QString  arg__1){  (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_setFeedbackMode(arg__1));}
   void setFeedbackMode(Turnout* theWrappedObject, int  arg__1);
   void py_q_setFeedbackMode(Turnout* theWrappedObject, int  arg__1){  (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_setFeedbackMode(arg__1));}
   void setInhibitOperation(Turnout* theWrappedObject, bool  arg__1);
   void py_q_setInhibitOperation(Turnout* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_setInhibitOperation(arg__1));}
   void setInitialKnownStateFromFeedback(Turnout* theWrappedObject);
   void py_q_setInitialKnownStateFromFeedback(Turnout* theWrappedObject){  (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_setInitialKnownStateFromFeedback());}
   void setInverted(Turnout* theWrappedObject, bool  arg__1);
   void py_q_setInverted(Turnout* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_setInverted(arg__1));}
   void setLocked(Turnout* theWrappedObject, int  arg__1, bool  arg__2);
   void py_q_setLocked(Turnout* theWrappedObject, int  arg__1, bool  arg__2){  (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_setLocked(arg__1, arg__2));}
   void setNumberOutputBits(Turnout* theWrappedObject, int  arg__1);
   void py_q_setNumberOutputBits(Turnout* theWrappedObject, int  arg__1){  (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_setNumberOutputBits(arg__1));}
   void setReportLocked(Turnout* theWrappedObject, bool  arg__1);
   void py_q_setReportLocked(Turnout* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_setReportLocked(arg__1));}
   void setStraightSpeed(Turnout* theWrappedObject, QString  arg__1) const throw (JmriException) ;
   void py_q_setStraightSpeed(Turnout* theWrappedObject, QString  arg__1) const throw (JmriException) {  (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_setStraightSpeed(arg__1));}
   void setTurnoutOperation(Turnout* theWrappedObject, TurnoutOperation*  arg__1);
   void py_q_setTurnoutOperation(Turnout* theWrappedObject, TurnoutOperation*  arg__1){  (((PythonQtPublicPromoter_Turnout*)theWrappedObject)->py_q_setTurnoutOperation(arg__1));}
};





class PythonQtShell_TurnoutManager : public TurnoutManager
{
public:
    PythonQtShell_TurnoutManager(QObject*  parent = nullptr):TurnoutManager(parent),_wrapper(NULL) {}

   ~PythonQtShell_TurnoutManager();

virtual void Register(NamedBean*  s);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual bool  allowMultipleAdditions(QString  arg__1);
virtual int  askControlType(QString  arg__1);
virtual int  askNumControlBits(QString  arg__1);
virtual void childEvent(QChildEvent*  event);
virtual QString  createSystemName(QString  arg__1, QString  arg__2) const;
virtual void customEvent(QEvent*  event);
virtual void deregister(NamedBean*  s);
virtual void dispose();
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual NamedBean*  getBeanBySystemName(QString  systemName);
virtual NamedBean*  getBeanByUserName(QString  userName);
virtual QString  getBeanTypeHandled();
virtual Turnout*  getBySystemName(QString  arg__1);
virtual Turnout*  getByUserName(QString  arg__1);
virtual QString  getClosedText();
virtual QString  getDefaultClosedSpeed() const;
virtual QString  getDefaultThrownSpeed() const;
virtual QString  getEntryToolTip();
virtual NamedBean*  getNamedBean(QString  name);
virtual QSet<NamedBean* >  getNamedBeanSet();
virtual QString  getNextValidAddress(QString  arg__1, QString  arg__2) const;
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList();
virtual QString  getSystemPrefix();
virtual QString  getThrownText();
virtual Turnout*  getTurnout(QString  arg__1);
virtual QStringList  getValidOperationTypes();
virtual int  getXMLOrder();
virtual bool  isControlTypeSupported(QString  arg__1);
virtual bool  isNumControlBitsSupported(QString  arg__1);
virtual QString  makeSystemName(QString  s);
virtual Turnout*  newTurnout(QString  arg__1, QString  arg__2) const;
virtual QString  normalizeSystemName(QString  inputName);
virtual void propertyChange(PropertyChangeEvent*  e);
virtual Turnout*  provideTurnout(QString  arg__1);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void setDefaultClosedSpeed(QString  arg__1) const;
virtual void setDefaultThrownSpeed(QString  arg__1) const;
virtual void timerEvent(QTimerEvent*  event);
virtual char  typeLetter();
virtual Manager::NameValidity  validSystemNameFormat(QString  arg__1);
virtual void vetoableChange(PropertyChangeEvent*  evt);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_TurnoutManager : public TurnoutManager
{ public:
inline bool  py_q_allowMultipleAdditions(QString  arg__1) { return TurnoutManager::allowMultipleAdditions(arg__1); }
inline int  py_q_askControlType(QString  arg__1) { return TurnoutManager::askControlType(arg__1); }
inline int  py_q_askNumControlBits(QString  arg__1) { return TurnoutManager::askNumControlBits(arg__1); }
inline QString  py_q_createSystemName(QString  arg__1, QString  arg__2) const { return TurnoutManager::createSystemName(arg__1, arg__2); }
inline Turnout*  py_q_getBySystemName(QString  arg__1) { return TurnoutManager::getBySystemName(arg__1); }
inline Turnout*  py_q_getByUserName(QString  arg__1) { return TurnoutManager::getByUserName(arg__1); }
inline QString  py_q_getClosedText() { return TurnoutManager::getClosedText(); }
inline QString  py_q_getDefaultClosedSpeed() const { return TurnoutManager::getDefaultClosedSpeed(); }
inline QString  py_q_getDefaultThrownSpeed() const { return TurnoutManager::getDefaultThrownSpeed(); }
inline QString  py_q_getNextValidAddress(QString  arg__1, QString  arg__2) const { return TurnoutManager::getNextValidAddress(arg__1, arg__2); }
inline QString  py_q_getThrownText() { return TurnoutManager::getThrownText(); }
inline Turnout*  py_q_getTurnout(QString  arg__1) { return TurnoutManager::getTurnout(arg__1); }
inline QStringList  py_q_getValidOperationTypes() { return TurnoutManager::getValidOperationTypes(); }
inline bool  py_q_isControlTypeSupported(QString  arg__1) { return TurnoutManager::isControlTypeSupported(arg__1); }
inline bool  py_q_isNumControlBitsSupported(QString  arg__1) { return TurnoutManager::isNumControlBitsSupported(arg__1); }
inline Turnout*  py_q_newTurnout(QString  arg__1, QString  arg__2) const { return TurnoutManager::newTurnout(arg__1, arg__2); }
inline Turnout*  py_q_provideTurnout(QString  arg__1) { return TurnoutManager::provideTurnout(arg__1); }
inline void py_q_setDefaultClosedSpeed(QString  arg__1) const { TurnoutManager::setDefaultClosedSpeed(arg__1); }
inline void py_q_setDefaultThrownSpeed(QString  arg__1) const { TurnoutManager::setDefaultThrownSpeed(arg__1); }
};

class PythonQtWrapper_TurnoutManager : public QObject
{ Q_OBJECT
public:
public slots:
TurnoutManager* new_TurnoutManager(QObject*  parent = nullptr);
void delete_TurnoutManager(TurnoutManager* obj) { delete obj; } 
   bool  allowMultipleAdditions(TurnoutManager* theWrappedObject, QString  arg__1);
   bool  py_q_allowMultipleAdditions(TurnoutManager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_TurnoutManager*)theWrappedObject)->py_q_allowMultipleAdditions(arg__1));}
   int  askControlType(TurnoutManager* theWrappedObject, QString  arg__1);
   int  py_q_askControlType(TurnoutManager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_TurnoutManager*)theWrappedObject)->py_q_askControlType(arg__1));}
   int  askNumControlBits(TurnoutManager* theWrappedObject, QString  arg__1);
   int  py_q_askNumControlBits(TurnoutManager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_TurnoutManager*)theWrappedObject)->py_q_askNumControlBits(arg__1));}
   QString  createSystemName(TurnoutManager* theWrappedObject, QString  arg__1, QString  arg__2) const;
   QString  py_q_createSystemName(TurnoutManager* theWrappedObject, QString  arg__1, QString  arg__2) const{  return (((PythonQtPublicPromoter_TurnoutManager*)theWrappedObject)->py_q_createSystemName(arg__1, arg__2));}
   Turnout*  getBySystemName(TurnoutManager* theWrappedObject, QString  arg__1);
   Turnout*  py_q_getBySystemName(TurnoutManager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_TurnoutManager*)theWrappedObject)->py_q_getBySystemName(arg__1));}
   Turnout*  getByUserName(TurnoutManager* theWrappedObject, QString  arg__1);
   Turnout*  py_q_getByUserName(TurnoutManager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_TurnoutManager*)theWrappedObject)->py_q_getByUserName(arg__1));}
   QString  getClosedText(TurnoutManager* theWrappedObject);
   QString  py_q_getClosedText(TurnoutManager* theWrappedObject){  return (((PythonQtPublicPromoter_TurnoutManager*)theWrappedObject)->py_q_getClosedText());}
   QString  getDefaultClosedSpeed(TurnoutManager* theWrappedObject) const;
   QString  py_q_getDefaultClosedSpeed(TurnoutManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_TurnoutManager*)theWrappedObject)->py_q_getDefaultClosedSpeed());}
   QString  getDefaultThrownSpeed(TurnoutManager* theWrappedObject) const;
   QString  py_q_getDefaultThrownSpeed(TurnoutManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_TurnoutManager*)theWrappedObject)->py_q_getDefaultThrownSpeed());}
   QString  getNextValidAddress(TurnoutManager* theWrappedObject, QString  arg__1, QString  arg__2) const;
   QString  py_q_getNextValidAddress(TurnoutManager* theWrappedObject, QString  arg__1, QString  arg__2) const{  return (((PythonQtPublicPromoter_TurnoutManager*)theWrappedObject)->py_q_getNextValidAddress(arg__1, arg__2));}
   QString  getThrownText(TurnoutManager* theWrappedObject);
   QString  py_q_getThrownText(TurnoutManager* theWrappedObject){  return (((PythonQtPublicPromoter_TurnoutManager*)theWrappedObject)->py_q_getThrownText());}
   Turnout*  getTurnout(TurnoutManager* theWrappedObject, QString  arg__1);
   Turnout*  py_q_getTurnout(TurnoutManager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_TurnoutManager*)theWrappedObject)->py_q_getTurnout(arg__1));}
   QStringList  getValidOperationTypes(TurnoutManager* theWrappedObject);
   QStringList  py_q_getValidOperationTypes(TurnoutManager* theWrappedObject){  return (((PythonQtPublicPromoter_TurnoutManager*)theWrappedObject)->py_q_getValidOperationTypes());}
   bool  isControlTypeSupported(TurnoutManager* theWrappedObject, QString  arg__1);
   bool  py_q_isControlTypeSupported(TurnoutManager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_TurnoutManager*)theWrappedObject)->py_q_isControlTypeSupported(arg__1));}
   bool  isNumControlBitsSupported(TurnoutManager* theWrappedObject, QString  arg__1);
   bool  py_q_isNumControlBitsSupported(TurnoutManager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_TurnoutManager*)theWrappedObject)->py_q_isNumControlBitsSupported(arg__1));}
   Turnout*  newTurnout(TurnoutManager* theWrappedObject, QString  arg__1, QString  arg__2) const;
   Turnout*  py_q_newTurnout(TurnoutManager* theWrappedObject, QString  arg__1, QString  arg__2) const{  return (((PythonQtPublicPromoter_TurnoutManager*)theWrappedObject)->py_q_newTurnout(arg__1, arg__2));}
   Turnout*  provideTurnout(TurnoutManager* theWrappedObject, QString  arg__1);
   Turnout*  py_q_provideTurnout(TurnoutManager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_TurnoutManager*)theWrappedObject)->py_q_provideTurnout(arg__1));}
   void setDefaultClosedSpeed(TurnoutManager* theWrappedObject, QString  arg__1) const;
   void py_q_setDefaultClosedSpeed(TurnoutManager* theWrappedObject, QString  arg__1) const{  (((PythonQtPublicPromoter_TurnoutManager*)theWrappedObject)->py_q_setDefaultClosedSpeed(arg__1));}
   void setDefaultThrownSpeed(TurnoutManager* theWrappedObject, QString  arg__1) const;
   void py_q_setDefaultThrownSpeed(TurnoutManager* theWrappedObject, QString  arg__1) const{  (((PythonQtPublicPromoter_TurnoutManager*)theWrappedObject)->py_q_setDefaultThrownSpeed(arg__1));}
};





class PythonQtShell_TurnoutOperation : public TurnoutOperation
{
public:
    PythonQtShell_TurnoutOperation(QString  n, QObject*  parent = 0):TurnoutOperation(n, parent),_wrapper(NULL) {}
    PythonQtShell_TurnoutOperation(TurnoutOperation&  arg__1):TurnoutOperation(arg__1),_wrapper(NULL) {}

   ~PythonQtShell_TurnoutOperation();

virtual void childEvent(QChildEvent*  event);
virtual int  compareTo(QObject*  other);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual QString  getName();
virtual TurnoutOperation*  makeCopy(QString  n);
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_TurnoutOperation : public TurnoutOperation
{ public:
inline void promoted_setFeedbackModes(int  fm) { this->setFeedbackModes(fm); }
inline int  py_q_compareTo(QObject*  other) { return TurnoutOperation::compareTo(other); }
inline QString  py_q_getName() { return TurnoutOperation::getName(); }
inline TurnoutOperation*  py_q_makeCopy(QString  n) { return TurnoutOperation::makeCopy(n); }
};

class PythonQtWrapper_TurnoutOperation : public QObject
{ Q_OBJECT
public:
public slots:
TurnoutOperation* new_TurnoutOperation(QString  n, QObject*  parent = 0);
TurnoutOperation* new_TurnoutOperation(TurnoutOperation&  arg__1);
void delete_TurnoutOperation(TurnoutOperation* obj) { delete obj; } 
   void addPropertyChangeListener(TurnoutOperation* theWrappedObject, PropertyChangeListener*  l);
   int  compareTo(TurnoutOperation* theWrappedObject, QObject*  other);
   int  py_q_compareTo(TurnoutOperation* theWrappedObject, QObject*  other){  return (((PythonQtPublicPromoter_TurnoutOperation*)theWrappedObject)->py_q_compareTo(other));}
   void dispose(TurnoutOperation* theWrappedObject);
   bool  equivalentTo(TurnoutOperation* theWrappedObject, TurnoutOperation*  other);
   TurnoutOperation*  getDefinitive(TurnoutOperation* theWrappedObject);
   QString  getName(TurnoutOperation* theWrappedObject);
   QString  py_q_getName(TurnoutOperation* theWrappedObject){  return (((PythonQtPublicPromoter_TurnoutOperation*)theWrappedObject)->py_q_getName());}
   bool  isDefinitive(TurnoutOperation* theWrappedObject);
   bool  isDeleted(TurnoutOperation* theWrappedObject);
   bool  isInUse(TurnoutOperation* theWrappedObject);
   bool  isNonce(TurnoutOperation* theWrappedObject);
   TurnoutOperation*  makeCopy(TurnoutOperation* theWrappedObject, QString  n);
   TurnoutOperation*  py_q_makeCopy(TurnoutOperation* theWrappedObject, QString  n){  return (((PythonQtPublicPromoter_TurnoutOperation*)theWrappedObject)->py_q_makeCopy(n));}
   TurnoutOperation*  makeNonce(TurnoutOperation* theWrappedObject, Turnout*  t);
   bool  matchFeedbackMode(TurnoutOperation* theWrappedObject, int  mode);
   void removePropertyChangeListener(TurnoutOperation* theWrappedObject, PropertyChangeListener*  l);
   bool  rename(TurnoutOperation* theWrappedObject, QString  newName);
   void setFeedbackModes(TurnoutOperation* theWrappedObject, int  fm);
   void setNonce(TurnoutOperation* theWrappedObject, bool  n);
void py_set_pcs(TurnoutOperation* theWrappedObject, PropertyChangeSupport*  pcs){ theWrappedObject->pcs = pcs; }
PropertyChangeSupport*  py_get_pcs(TurnoutOperation* theWrappedObject){ return theWrappedObject->pcs; }
};





class PythonQtShell_VetoableChangeSupport : public VetoableChangeSupport
{
public:
    PythonQtShell_VetoableChangeSupport(QObject*  source):VetoableChangeSupport(source),_wrapper(NULL) {}

   ~PythonQtShell_VetoableChangeSupport();

virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtWrapper_VetoableChangeSupport : public QObject
{ Q_OBJECT
public:
public slots:
VetoableChangeSupport* new_VetoableChangeSupport(QObject*  source);
void delete_VetoableChangeSupport(VetoableChangeSupport* obj) { delete obj; } 
   void fireVetoableChange(VetoableChangeSupport* theWrappedObject, PropertyChangeEvent*  event);
   void fireVetoableChange(VetoableChangeSupport* theWrappedObject, QString  propertyName, QVariant  oldValue, QVariant  newValue);
   void fireVetoableChange(VetoableChangeSupport* theWrappedObject, QString  propertyName, bool  oldValue, bool  newValue);
   void fireVetoableChange(VetoableChangeSupport* theWrappedObject, QString  propertyName, int  oldValue, int  newValue);
};





class PythonQtShell_WindowListener : public WindowListener
{
public:
    PythonQtShell_WindowListener():WindowListener(),_wrapper(NULL) {}

   ~PythonQtShell_WindowListener();

virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual void timerEvent(QTimerEvent*  event);
virtual void windowClosed(QCloseEvent  arg__1);
virtual void windowClosing(QCloseEvent*  arg__1);
virtual void windowDeiconified(QResizeEvent*  arg__1);
virtual void windowIconified(QResizeEvent*  arg__1);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_WindowListener : public WindowListener
{ public:
inline void py_q_windowClosed(QCloseEvent  arg__1) { WindowListener::windowClosed(arg__1); }
inline void py_q_windowClosing(QCloseEvent*  arg__1) { this->windowClosing(arg__1); }
inline void py_q_windowDeiconified(QResizeEvent*  arg__1) { WindowListener::windowDeiconified(arg__1); }
inline void py_q_windowIconified(QResizeEvent*  arg__1) { WindowListener::windowIconified(arg__1); }
};

class PythonQtWrapper_WindowListener : public QObject
{ Q_OBJECT
public:
public slots:
WindowListener* new_WindowListener();
void delete_WindowListener(WindowListener* obj) { delete obj; } 
   void windowClosed(WindowListener* theWrappedObject, QCloseEvent  arg__1);
   void py_q_windowClosed(WindowListener* theWrappedObject, QCloseEvent  arg__1){  (((PythonQtPublicPromoter_WindowListener*)theWrappedObject)->py_q_windowClosed(arg__1));}
   void windowClosing(WindowListener* theWrappedObject, QCloseEvent*  arg__1);
   void py_q_windowClosing(WindowListener* theWrappedObject, QCloseEvent*  arg__1){  (((PythonQtPublicPromoter_WindowListener*)theWrappedObject)->py_q_windowClosing(arg__1));}
   void windowDeiconified(WindowListener* theWrappedObject, QResizeEvent*  arg__1);
   void py_q_windowDeiconified(WindowListener* theWrappedObject, QResizeEvent*  arg__1){  (((PythonQtPublicPromoter_WindowListener*)theWrappedObject)->py_q_windowDeiconified(arg__1));}
   void windowIconified(WindowListener* theWrappedObject, QResizeEvent*  arg__1);
   void py_q_windowIconified(WindowListener* theWrappedObject, QResizeEvent*  arg__1){  (((PythonQtPublicPromoter_WindowListener*)theWrappedObject)->py_q_windowIconified(arg__1));}
};





class PythonQtShell_XmlFile : public XmlFile
{
public:
    PythonQtShell_XmlFile(QObject*  parent = 0):XmlFile(parent),_wrapper(NULL) {}

   ~PythonQtShell_XmlFile();

virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_XmlFile : public XmlFile
{ public:
inline bool  promoted_checkFile(QString  name) { return this->checkFile(name); }
inline QFile*  promoted_findFile(QString  name) const { return this->findFile(name); }
inline QDomElement  promoted_getRoot(QDataStream*  stream) { return this->getRoot(stream); }
};

class PythonQtWrapper_XmlFile : public QObject
{ Q_OBJECT
public:
public slots:
XmlFile* new_XmlFile(QObject*  parent = 0);
void delete_XmlFile(XmlFile* obj) { delete obj; } 
   void static_XmlFile_addDefaultInfo(QDomElement  root);
   QString  backupFileName(XmlFile* theWrappedObject, QString  name) const;
   bool  checkFile(XmlFile* theWrappedObject, QString  name);
   QString  createFileNameWithDate(XmlFile* theWrappedObject, QString  name) const;
   void static_XmlFile_dumpElement(QDomElement  name);
   QFile*  findFile(XmlFile* theWrappedObject, QString  name) const;
   QString  static_XmlFile_getDefaultDtdLocation();
   XmlFile::Validate  static_XmlFile_getDefaultValidate();
   QString  getDtdLocation(XmlFile* theWrappedObject);
   QString  getPathname(XmlFile* theWrappedObject);
   QDomElement  getRoot(XmlFile* theWrappedObject, QDataStream*  stream);
   XmlFile::Validate  getValidate(XmlFile* theWrappedObject);
   void makeBackupFile(XmlFile* theWrappedObject, QString  name) const;
   QDomDocument  static_XmlFile_newDocument(QDomElement  root);
   QDomDocument  static_XmlFile_newDocument(QDomElement  root, QString  dtd);
   void revertBackupFile(XmlFile* theWrappedObject, QString  name);
   QDomElement  rootFromFile(XmlFile* theWrappedObject, QFile*  file) throw (JDOMException);
   QDomElement  rootFromInputStream(XmlFile* theWrappedObject, QDataStream*  stream);
   QDomElement  rootFromName(XmlFile* theWrappedObject, QString  name) throw (JDOMException);
   QDomElement  rootFromURL(XmlFile* theWrappedObject, QUrl*  url) throw (JDOMException);
   void static_XmlFile_setDefaultDtdLocation(QString  v);
   void static_XmlFile_setDefaultValidate(XmlFile::Validate  v);
   void setDtdLocation(XmlFile* theWrappedObject, QString  v);
   void setValidate(XmlFile* theWrappedObject, XmlFile::Validate  v);
   void writeXML(XmlFile* theWrappedObject, QFile*  file, QDomDocument  doc) const throw (FileNotFoundException);
   QString  static_XmlFile_xmlDir();
};

