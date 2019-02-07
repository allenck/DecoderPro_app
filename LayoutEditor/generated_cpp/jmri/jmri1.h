#include <PythonQt.h>
#include <QObject>
#include <QVariant>
#include <abstractmanager.h>
#include <abstractproxymanager.h>
#include <abstractsensormanager.h>
#include <dcclocoaddress.h>
#include <dccthrottle.h>
#include <editor.h>
#include <light.h>
#include <locoaddress.h>
#include <loconetinterface.h>
#include <loconetmessage.h>
#include <memorymanager.h>
#include <positionable.h>
#include <programmermanager.h>
#include <proxylightmanager.h>
#include <proxysensormanager.h>
#include <proxyturnoutmanager.h>
#include <reportermanager.h>
#include <routemanager.h>
#include <sensor.h>
#include <siglet.h>
#include <signalhead.h>
#include <sound.h>
#include <throttle.h>
#include <turnout.h>



class PythonQtShell_LocoNetInterface : public LocoNetInterface
{
public:
    PythonQtShell_LocoNetInterface(QObject*  parent = 0):LocoNetInterface(parent),_wrapper(NULL) {};

   ~PythonQtShell_LocoNetInterface();

virtual void sendLocoNetMessage(LocoNetMessage*  arg__1);
virtual bool  status();

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_LocoNetInterface : public LocoNetInterface
{ public:
inline void promoted_sendLocoNetMessage(LocoNetMessage*  arg__1) { LocoNetInterface::sendLocoNetMessage(arg__1); }
inline bool  promoted_status() { return LocoNetInterface::status(); }
};

class PythonQtWrapper_LocoNetInterface : public QObject
{ Q_OBJECT
public:
public slots:
LocoNetInterface* new_LocoNetInterface(QObject*  parent = 0);
void delete_LocoNetInterface(LocoNetInterface* obj) { delete obj; } 
   void sendLocoNetMessage(LocoNetInterface* theWrappedObject, LocoNetMessage*  arg__1);
   bool  status(LocoNetInterface* theWrappedObject);
};





class PythonQtShell_LocoNetMessage : public LocoNetMessage
{
public:
    PythonQtShell_LocoNetMessage(QVector<char >  contents, QObject*  parent = 0):LocoNetMessage(contents, parent),_wrapper(NULL) {};
    PythonQtShell_LocoNetMessage(QVector<int >  contents, QObject*  parent = 0):LocoNetMessage(contents, parent),_wrapper(NULL) {};
    PythonQtShell_LocoNetMessage(const LocoNetMessage&  original, QObject*  parent = 0):LocoNetMessage(original, parent),_wrapper(NULL) {};
    PythonQtShell_LocoNetMessage(int  len, QObject*  parent = 0):LocoNetMessage(len, parent),_wrapper(NULL) {};

   ~PythonQtShell_LocoNetMessage();


  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_LocoNetMessage : public LocoNetMessage
{ public:
static inline bool  promoted_highBit(int  val) { return LocoNetMessage::highBit(val); }
static inline int  promoted_highByte(int  val) { return LocoNetMessage::highByte(val); }
static inline int  promoted_lowByte(int  val) { return LocoNetMessage::lowByte(val); }
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





class PythonQtShell_MemoryManager : public MemoryManager
{
public:
    PythonQtShell_MemoryManager(QObject*  parent = 0):MemoryManager(parent),_wrapper(NULL) {};

   ~PythonQtShell_MemoryManager();

virtual void Register(NamedBean*  s);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void deregister(NamedBean*  s);
virtual void dispose();
virtual NamedBean*  getBeanBySystemName(QString  systemName);
virtual NamedBean*  getBeanByUserName(QString  userName);
virtual NamedBean*  getNamedBean(QString  name);
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList();
virtual QString  makeSystemName(QString  s);
virtual void propertyChange(PropertyChangeEvent*  e);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void vetoableChange(PropertyChangeEvent*  evt);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtWrapper_MemoryManager : public QObject
{ Q_OBJECT
public:
public slots:
MemoryManager* new_MemoryManager(QObject*  parent = 0);
void delete_MemoryManager(MemoryManager* obj) { delete obj; } 
};





class PythonQtShell_Positionable : public Positionable
{
public:
    PythonQtShell_Positionable(QString  text, QWidget*  parent = 0):Positionable(text, parent),_wrapper(NULL) {};
    PythonQtShell_Positionable(QWidget*  parent = 0):Positionable(parent),_wrapper(NULL) {};

   ~PythonQtShell_Positionable();

virtual bool  contains(int  arg__1, int  arg__2);
virtual Positionable*  deepClone();
virtual void doMouseClicked(QGraphicsSceneMouseEvent*  arg__1);
virtual void doMouseDragged(QGraphicsSceneMouseEvent*  arg__1);
virtual void doMouseEntered(QGraphicsSceneMouseEvent*  arg__1);
virtual void doMouseExited(QGraphicsSceneMouseEvent*  arg__1);
virtual void doMouseMoved(QGraphicsSceneMouseEvent*  arg__1);
virtual void doMousePressed(QGraphicsSceneMouseEvent*  arg__1);
virtual void doMouseReleased(QGraphicsSceneMouseEvent*  arg__1);
virtual bool  doViemMenu();
virtual Positionable*  finishClone(Positionable*  arg__1);
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
virtual void invalidate();
virtual bool  isControlling();
virtual bool  isEditable();
virtual bool  isHidden();
virtual bool  isOpaque();
virtual bool  isPositionable();
virtual bool  isVisible();
virtual int  maxHeight();
virtual int  maxWidth();
virtual void paint(QGraphicsScene*  arg__1);
virtual void remove();
virtual bool  requestFocusInWindow();
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
virtual void showHidden();
virtual bool  showPopUp(QMenu*  arg__1);
virtual bool  showToolTip();
virtual bool  storeItem();
virtual bool  updateScene();
virtual void updateSize();

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_Positionable : public Positionable
{ public:
inline bool  promoted_contains(int  arg__1, int  arg__2) { return Positionable::contains(arg__1, arg__2); }
inline Positionable*  promoted_deepClone() { return Positionable::deepClone(); }
inline void promoted_doMouseClicked(QGraphicsSceneMouseEvent*  arg__1) { Positionable::doMouseClicked(arg__1); }
inline void promoted_doMouseDragged(QGraphicsSceneMouseEvent*  arg__1) { Positionable::doMouseDragged(arg__1); }
inline void promoted_doMouseEntered(QGraphicsSceneMouseEvent*  arg__1) { Positionable::doMouseEntered(arg__1); }
inline void promoted_doMouseExited(QGraphicsSceneMouseEvent*  arg__1) { Positionable::doMouseExited(arg__1); }
inline void promoted_doMouseMoved(QGraphicsSceneMouseEvent*  arg__1) { Positionable::doMouseMoved(arg__1); }
inline void promoted_doMousePressed(QGraphicsSceneMouseEvent*  arg__1) { Positionable::doMousePressed(arg__1); }
inline void promoted_doMouseReleased(QGraphicsSceneMouseEvent*  arg__1) { Positionable::doMouseReleased(arg__1); }
inline bool  promoted_doViemMenu() { return Positionable::doViemMenu(); }
inline Positionable*  promoted_finishClone(Positionable*  arg__1) { return Positionable::finishClone(arg__1); }
inline QColor  promoted_getBackground() { return Positionable::getBackground(); }
inline QRectF  promoted_getBounds(QRectF  arg__1) { return Positionable::getBounds(arg__1); }
inline int  promoted_getDegrees() { return Positionable::getDegrees(); }
inline int  promoted_getDisplayLevel() { return Positionable::getDisplayLevel(); }
inline Editor*  promoted_getEditor() { return Positionable::getEditor(); }
inline QFont  promoted_getFont() { return Positionable::getFont(); }
inline QColor  promoted_getForeground() { return Positionable::getForeground(); }
inline QString  promoted_getGroupName() { return Positionable::getGroupName(); }
inline int  promoted_getHeight() { return Positionable::getHeight(); }
inline QPointF  promoted_getLocation() { return Positionable::getLocation(); }
inline QString  promoted_getNameString() { return Positionable::getNameString(); }
inline NamedBean*  promoted_getNamedBean() { return Positionable::getNamedBean(); }
inline bool  promoted_getSaveOpaque() { return Positionable::getSaveOpaque(); }
inline double  promoted_getScale() { return Positionable::getScale(); }
inline QString  promoted_getTooltip() { return Positionable::getTooltip(); }
inline bool  promoted_getViewCoordinates() { return Positionable::getViewCoordinates(); }
inline int  promoted_getWidth() { return Positionable::getWidth(); }
inline int  promoted_getX() { return Positionable::getX(); }
inline int  promoted_getY() { return Positionable::getY(); }
inline void promoted_invalidate() { Positionable::invalidate(); }
inline bool  promoted_isControlling() { return Positionable::isControlling(); }
inline bool  promoted_isEditable() { return Positionable::isEditable(); }
inline bool  promoted_isHidden() { return Positionable::isHidden(); }
inline bool  promoted_isOpaque() { return Positionable::isOpaque(); }
inline bool  promoted_isPositionable() { return Positionable::isPositionable(); }
inline bool  promoted_isVisible() { return Positionable::isVisible(); }
inline int  promoted_maxHeight() { return Positionable::maxHeight(); }
inline int  promoted_maxWidth() { return Positionable::maxWidth(); }
inline void promoted_paint(QGraphicsScene*  arg__1) { Positionable::paint(arg__1); }
inline void promoted_remove() { Positionable::remove(); }
inline bool  promoted_requestFocusInWindow() { return Positionable::requestFocusInWindow(); }
inline void promoted_rotate(int  arg__1) { Positionable::rotate(arg__1); }
inline void promoted_setBackground(QColor  arg__1) { Positionable::setBackground(arg__1); }
inline void promoted_setControlling(bool  arg__1) { Positionable::setControlling(arg__1); }
inline bool  promoted_setDisableControlMenu(QMenu*  arg__1) { return Positionable::setDisableControlMenu(arg__1); }
inline void promoted_setDisplayLevel(int  arg__1) { Positionable::setDisplayLevel(arg__1); }
inline bool  promoted_setEditIconMenu(QMenu*  arg__1) { return Positionable::setEditIconMenu(arg__1); }
inline bool  promoted_setEditItemMenu(QMenu*  arg__1) { return Positionable::setEditItemMenu(arg__1); }
inline void promoted_setEditable(bool  arg__1) { Positionable::setEditable(arg__1); }
inline void promoted_setEditor(Editor*  arg__1) { Positionable::setEditor(arg__1); }
inline void promoted_setForeground(QColor  arg__1) { Positionable::setForeground(arg__1); }
inline void promoted_setHidden(bool  arg__1) { Positionable::setHidden(arg__1); }
inline void promoted_setLevel(int  arg__1) { Positionable::setLevel(arg__1); }
inline void promoted_setLocation(QPointF  arg__1) { Positionable::setLocation(arg__1); }
inline void promoted_setLocation(int  arg__1, int  arg__2) { Positionable::setLocation(arg__1, arg__2); }
inline void promoted_setOpaque(bool  arg__1) { Positionable::setOpaque(arg__1); }
inline void promoted_setPositionable(bool  arg__1) { Positionable::setPositionable(arg__1); }
inline bool  promoted_setRotateMenu(QMenu*  arg__1) { return Positionable::setRotateMenu(arg__1); }
inline bool  promoted_setRotateOrthogonalMenu(QMenu*  arg__1) { return Positionable::setRotateOrthogonalMenu(arg__1); }
inline void promoted_setScale(double  arg__1) { Positionable::setScale(arg__1); }
inline bool  promoted_setScaleMenu(QMenu*  arg__1) { return Positionable::setScaleMenu(arg__1); }
inline void promoted_setShowTooltip(bool  arg__1) { Positionable::setShowTooltip(arg__1); }
inline void promoted_setSize(int  arg__1, int  arg__2) { Positionable::setSize(arg__1, arg__2); }
inline bool  promoted_setTextEditMenu(QMenu*  arg__1) { return Positionable::setTextEditMenu(arg__1); }
inline void promoted_setViewCoordinates(bool  arg__1) { Positionable::setViewCoordinates(arg__1); }
inline void promoted_setVisible(bool  b) { Positionable::setVisible(b); }
inline void promoted_showHidden() { Positionable::showHidden(); }
inline bool  promoted_showPopUp(QMenu*  arg__1) { return Positionable::showPopUp(arg__1); }
inline bool  promoted_showToolTip() { return Positionable::showToolTip(); }
inline bool  promoted_storeItem() { return Positionable::storeItem(); }
inline bool  promoted_updateScene() { return Positionable::updateScene(); }
inline void promoted_updateSize() { Positionable::updateSize(); }
};

class PythonQtWrapper_Positionable : public QObject
{ Q_OBJECT
public:
public slots:
Positionable* new_Positionable(QString  text, QWidget*  parent = 0);
Positionable* new_Positionable(QWidget*  parent = 0);
void delete_Positionable(Positionable* obj) { delete obj; } 
   bool  contains(Positionable* theWrappedObject, int  arg__1, int  arg__2);
   Positionable*  deepClone(Positionable* theWrappedObject);
   void doMouseClicked(Positionable* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1);
   void doMouseDragged(Positionable* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1);
   void doMouseEntered(Positionable* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1);
   void doMouseExited(Positionable* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1);
   void doMouseMoved(Positionable* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1);
   void doMousePressed(Positionable* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1);
   void doMouseReleased(Positionable* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1);
   bool  doViemMenu(Positionable* theWrappedObject);
   Positionable*  finishClone(Positionable* theWrappedObject, Positionable*  arg__1);
   QColor  getBackground(Positionable* theWrappedObject);
   QRectF  getBounds(Positionable* theWrappedObject, QRectF  arg__1);
   int  getDegrees(Positionable* theWrappedObject);
   int  getDisplayLevel(Positionable* theWrappedObject);
   Editor*  getEditor(Positionable* theWrappedObject);
   QFont  getFont(Positionable* theWrappedObject);
   QColor  getForeground(Positionable* theWrappedObject);
   QString  getGroupName(Positionable* theWrappedObject);
   int  getHeight(Positionable* theWrappedObject);
   QGraphicsItem*  getItem(Positionable* theWrappedObject);
   QPointF  getLocation(Positionable* theWrappedObject);
   QString  getNameString(Positionable* theWrappedObject);
   NamedBean*  getNamedBean(Positionable* theWrappedObject);
   bool  getSaveOpaque(Positionable* theWrappedObject);
   double  getScale(Positionable* theWrappedObject);
   QString  getTooltip(Positionable* theWrappedObject);
   bool  getViewCoordinates(Positionable* theWrappedObject);
   int  getWidth(Positionable* theWrappedObject);
   int  getX(Positionable* theWrappedObject);
   int  getY(Positionable* theWrappedObject);
   void invalidate(Positionable* theWrappedObject);
   bool  isControlling(Positionable* theWrappedObject);
   bool  isEditable(Positionable* theWrappedObject);
   bool  isHidden(Positionable* theWrappedObject);
   bool  isOpaque(Positionable* theWrappedObject);
   bool  isPositionable(Positionable* theWrappedObject);
   bool  isVisible(Positionable* theWrappedObject);
   int  maxHeight(Positionable* theWrappedObject);
   int  maxWidth(Positionable* theWrappedObject);
   void paint(Positionable* theWrappedObject, QGraphicsScene*  arg__1);
   void remove(Positionable* theWrappedObject);
   bool  requestFocusInWindow(Positionable* theWrappedObject);
   void rotate(Positionable* theWrappedObject, int  arg__1);
   void setBackground(Positionable* theWrappedObject, QColor  arg__1);
   void setControlling(Positionable* theWrappedObject, bool  arg__1);
   bool  setDisableControlMenu(Positionable* theWrappedObject, QMenu*  arg__1);
   void setDisplayLevel(Positionable* theWrappedObject, int  arg__1);
   bool  setEditIconMenu(Positionable* theWrappedObject, QMenu*  arg__1);
   bool  setEditItemMenu(Positionable* theWrappedObject, QMenu*  arg__1);
   void setEditable(Positionable* theWrappedObject, bool  arg__1);
   void setEditor(Positionable* theWrappedObject, Editor*  arg__1);
   void setForeground(Positionable* theWrappedObject, QColor  arg__1);
   void setHidden(Positionable* theWrappedObject, bool  arg__1);
   void setItem(Positionable* theWrappedObject, QGraphicsTextItem*  item);
   void setLevel(Positionable* theWrappedObject, int  arg__1);
   void setLocation(Positionable* theWrappedObject, QPointF  arg__1);
   void setLocation(Positionable* theWrappedObject, int  arg__1, int  arg__2);
   void setOpaque(Positionable* theWrappedObject, bool  arg__1);
   void setPositionable(Positionable* theWrappedObject, bool  arg__1);
   bool  setRotateMenu(Positionable* theWrappedObject, QMenu*  arg__1);
   bool  setRotateOrthogonalMenu(Positionable* theWrappedObject, QMenu*  arg__1);
   void setScale(Positionable* theWrappedObject, double  arg__1);
   bool  setScaleMenu(Positionable* theWrappedObject, QMenu*  arg__1);
   void setShowTooltip(Positionable* theWrappedObject, bool  arg__1);
   void setSize(Positionable* theWrappedObject, int  arg__1, int  arg__2);
   bool  setTextEditMenu(Positionable* theWrappedObject, QMenu*  arg__1);
   void setViewCoordinates(Positionable* theWrappedObject, bool  arg__1);
   void setVisible(Positionable* theWrappedObject, bool  b);
   void showHidden(Positionable* theWrappedObject);
   bool  showPopUp(Positionable* theWrappedObject, QMenu*  arg__1);
   bool  showToolTip(Positionable* theWrappedObject);
   bool  storeItem(Positionable* theWrappedObject);
   bool  updateScene(Positionable* theWrappedObject);
   void updateSize(Positionable* theWrappedObject);
};





class PythonQtShell_ProgrammerManager : public ProgrammerManager
{
public:
    PythonQtShell_ProgrammerManager(QObject*  parent = 0):ProgrammerManager(parent),_wrapper(NULL) {};

   ~PythonQtShell_ProgrammerManager();

virtual QString  getUserName();
virtual bool  isAddressedModePossible();
virtual QString  toString();

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





class PythonQtShell_ProxyLightManager : public ProxyLightManager
{
public:
    PythonQtShell_ProxyLightManager(QObject*  parent = 0):ProxyLightManager(parent),_wrapper(NULL) {};

   ~PythonQtShell_ProxyLightManager();

virtual void Register(NamedBean*  s);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void deregister(NamedBean*  s);
virtual void dispose();
virtual NamedBean*  getBeanBySystemName(QString  systemName);
virtual NamedBean*  getBeanByUserName(QString  userName);
virtual Manager*  getMgr(int  index);
virtual NamedBean*  getNamedBean(QString  name);
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList();
virtual QStringList  getUserNameList();
virtual NamedBean*  makeBean(int  i, QString  systemName, QString  userName);
virtual Manager*  makeInternalManager() const;
virtual QString  makeSystemName(QString  s);
virtual int  match(QString  systemname);
virtual int  matchTentative(QString  arg__1);
virtual int  nMgrs();
virtual void propertyChange(PropertyChangeEvent*  e);
virtual NamedBean*  provideNamedBean(QString  name);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void vetoableChange(PropertyChangeEvent*  evt);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_ProxyLightManager : public ProxyLightManager
{ public:
inline NamedBean*  promoted_makeBean(int  i, QString  systemName, QString  userName) { return ProxyLightManager::makeBean(i, systemName, userName); }
inline Manager*  promoted_makeInternalManager() const { return ProxyLightManager::makeInternalManager(); }
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
   int  getXMLOrder(ProxyLightManager* theWrappedObject);
   NamedBean*  makeBean(ProxyLightManager* theWrappedObject, int  i, QString  systemName, QString  userName);
   Manager*  makeInternalManager(ProxyLightManager* theWrappedObject) const;
   Light*  newLight(ProxyLightManager* theWrappedObject, QString  systemName, QString  userName);
   NamedBean*  newNamedBean(ProxyLightManager* theWrappedObject, QString  systemName, QString  userName);
   QString  normalizeSystemName(ProxyLightManager* theWrappedObject, QString  systemName);
   Light*  provideLight(ProxyLightManager* theWrappedObject, QString  name);
   bool  supportsVariableLights(ProxyLightManager* theWrappedObject, QString  systemName);
   bool  validSystemNameConfig(ProxyLightManager* theWrappedObject, QString  systemName);
};





class PythonQtShell_ProxySensorManager : public ProxySensorManager
{
public:
    PythonQtShell_ProxySensorManager(QObject*  parent = nullptr):ProxySensorManager(parent),_wrapper(NULL) {};

   ~PythonQtShell_ProxySensorManager();

virtual void Register(NamedBean*  s);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void deregister(NamedBean*  s);
virtual void dispose();
virtual NamedBean*  getBeanBySystemName(QString  systemName);
virtual NamedBean*  getBeanByUserName(QString  userName);
virtual Manager*  getMgr(int  index);
virtual NamedBean*  getNamedBean(QString  name);
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList();
virtual QStringList  getUserNameList();
virtual Sensor*  makeBean(int  i, QString  systemName, QString  userName);
virtual Manager*  makeInternalManager() const;
virtual QString  makeSystemName(QString  s);
virtual int  match(QString  systemname);
virtual int  matchTentative(QString  arg__1);
virtual int  nMgrs();
virtual NamedBean*  provideNamedBean(QString  name);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void vetoableChange(PropertyChangeEvent*  evt);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_ProxySensorManager : public ProxySensorManager
{ public:
inline Sensor*  promoted_makeBean(int  i, QString  systemName, QString  userName) { return ProxySensorManager::makeBean(i, systemName, userName); }
inline Manager*  promoted_makeInternalManager() const { return ProxySensorManager::makeInternalManager(); }
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
   int  getXMLOrder(ProxySensorManager* theWrappedObject);
   Sensor*  makeBean(ProxySensorManager* theWrappedObject, int  i, QString  systemName, QString  userName);
   Manager*  makeInternalManager(ProxySensorManager* theWrappedObject) const;
   Sensor*  newSensor(ProxySensorManager* theWrappedObject, QString  systemName, QString  userName);
   Sensor*  provideSensor(ProxySensorManager* theWrappedObject, QString  sName);
   void setDefaultSensorDebounceGoingActive(ProxySensorManager* theWrappedObject, long  timer);
   void setDefaultSensorDebounceGoingInActive(ProxySensorManager* theWrappedObject, long  timer);
   void updateAll(ProxySensorManager* theWrappedObject);
};





class PythonQtShell_ProxyTurnoutManager : public ProxyTurnoutManager
{
public:
    PythonQtShell_ProxyTurnoutManager(QObject*  parent = 0):ProxyTurnoutManager(parent),_wrapper(NULL) {};

   ~PythonQtShell_ProxyTurnoutManager();

virtual void Register(NamedBean*  s);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void deregister(NamedBean*  s);
virtual void dispose();
virtual NamedBean*  getBeanBySystemName(QString  systemName);
virtual NamedBean*  getBeanByUserName(QString  userName);
virtual Manager*  getMgr(int  index);
virtual NamedBean*  getNamedBean(QString  name);
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList();
virtual QStringList  getUserNameList();
virtual NamedBean*  makeBean(int  i, QString  systemName, QString  userName);
virtual Manager*  makeInternalManager() const;
virtual QString  makeSystemName(QString  s);
virtual int  match(QString  systemname);
virtual int  matchTentative(QString  arg__1);
virtual int  nMgrs();
virtual NamedBean*  provideNamedBean(QString  name);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void vetoableChange(PropertyChangeEvent*  evt);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_ProxyTurnoutManager : public ProxyTurnoutManager
{ public:
inline NamedBean*  promoted_makeBean(int  i, QString  systemName, QString  userName) { return ProxyTurnoutManager::makeBean(i, systemName, userName); }
inline Manager*  promoted_makeInternalManager() const { return ProxyTurnoutManager::makeInternalManager(); }
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
   int  getXMLOrder(ProxyTurnoutManager* theWrappedObject);
   bool  isControlTypeSupported(ProxyTurnoutManager* theWrappedObject, QString  systemName);
   bool  isNumControlBitsSupported(ProxyTurnoutManager* theWrappedObject, QString  systemName);
   NamedBean*  makeBean(ProxyTurnoutManager* theWrappedObject, int  i, QString  systemName, QString  userName);
   Manager*  makeInternalManager(ProxyTurnoutManager* theWrappedObject) const;
   Turnout*  newTurnout(ProxyTurnoutManager* theWrappedObject, QString  systemName, QString  userName);
   void setDefaultClosedSpeed(ProxyTurnoutManager* theWrappedObject, QString  speed) throw (JmriException);
   void setDefaultThrownSpeed(ProxyTurnoutManager* theWrappedObject, QString  speed) throw (JmriException);
};





class PythonQtShell_ReporterManager : public ReporterManager
{
public:
    PythonQtShell_ReporterManager(QObject*  parent = 0):ReporterManager(parent),_wrapper(NULL) {};

   ~PythonQtShell_ReporterManager();

virtual void Register(NamedBean*  s);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual bool  allowMultipleAdditions(QString  arg__1) const;
virtual void deregister(NamedBean*  s);
virtual void dispose();
virtual NamedBean*  getBeanBySystemName(QString  systemName);
virtual NamedBean*  getBeanByUserName(QString  userName);
virtual NamedBean*  getNamedBean(QString  name);
virtual QString  getNextValidAddress(QString  arg__1, QString  arg__2) const;
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList() const;
virtual QString  makeSystemName(QString  s);
virtual void propertyChange(PropertyChangeEvent*  e);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void vetoableChange(PropertyChangeEvent*  evt);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_ReporterManager : public ReporterManager
{ public:
inline bool  promoted_allowMultipleAdditions(QString  arg__1) const { return ReporterManager::allowMultipleAdditions(arg__1); }
inline QString  promoted_getNextValidAddress(QString  arg__1, QString  arg__2) const { return ReporterManager::getNextValidAddress(arg__1, arg__2); }
inline QStringList  promoted_getSystemNameList() const { return ReporterManager::getSystemNameList(); }
};

class PythonQtWrapper_ReporterManager : public QObject
{ Q_OBJECT
public:
public slots:
ReporterManager* new_ReporterManager(QObject*  parent = 0);
void delete_ReporterManager(ReporterManager* obj) { delete obj; } 
   bool  allowMultipleAdditions(ReporterManager* theWrappedObject, QString  arg__1) const;
   QString  getNextValidAddress(ReporterManager* theWrappedObject, QString  arg__1, QString  arg__2) const;
   QStringList  getSystemNameList(ReporterManager* theWrappedObject) const;
};





class PythonQtShell_RouteManager : public RouteManager
{
public:
    PythonQtShell_RouteManager(QObject*  parent = nullptr):RouteManager(parent),_wrapper(NULL) {};

   ~PythonQtShell_RouteManager();

virtual void Register(NamedBean*  s);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void deregister(NamedBean*  s);
virtual void dispose();
virtual NamedBean*  getBeanBySystemName(QString  systemName);
virtual NamedBean*  getBeanByUserName(QString  userName);
virtual NamedBean*  getNamedBean(QString  name);
virtual QStringList  getSystemNameArray();
virtual QStringList  getSystemNameList();
virtual QString  makeSystemName(QString  s);
virtual void propertyChange(PropertyChangeEvent*  e);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void vetoableChange(PropertyChangeEvent*  evt);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_RouteManager : public RouteManager
{ public:
inline void promoted_dispose() { RouteManager::dispose(); }
};

class PythonQtWrapper_RouteManager : public QObject
{ Q_OBJECT
public:
public slots:
RouteManager* new_RouteManager(QObject*  parent = nullptr);
void delete_RouteManager(RouteManager* obj) { delete obj; } 
   void dispose(RouteManager* theWrappedObject);
};





class PythonQtShell_Sensor : public Sensor
{
public:
    PythonQtShell_Sensor(QObject*  parent = 0):Sensor(parent),_wrapper(NULL) {};
    PythonQtShell_Sensor(QString  sysName, QObject*  parent):Sensor(sysName, parent),_wrapper(NULL) {};
    PythonQtShell_Sensor(QString  sysName, QString  userName, QObject*  parent):Sensor(sysName, userName, parent),_wrapper(NULL) {};

   ~PythonQtShell_Sensor();

virtual void addPropertyChangeListener(PropertyChangeListener*  arg__1) const;
virtual bool  canInvert();
virtual void dispose() const;
virtual bool  getInverted() const;
virtual int  getKnownState() const;
virtual int  getRawState() const;
virtual long  getSensorDebounceGoingActiveTimer() const;
virtual long  getSensorDebounceGoingInActiveTimer() const;
virtual void removePropertyChangeListener(PropertyChangeListener*  arg__1) const;
virtual void requestUpdateFromLayout() const;
virtual void setInverted(bool  arg__1) const;
virtual void setKnownState(int  arg__1);
virtual void setSensorDebounceGoingActiveTimer(long  arg__1) const;
virtual void setSensorDebounceGoingInActiveTimer(long  arg__1) const;
virtual bool  useDefaultTimerSettings() const;
virtual void useDefaultTimerSettings(bool  arg__1) const;

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_Sensor : public Sensor
{ public:
inline void promoted_addPropertyChangeListener(PropertyChangeListener*  arg__1) const { Sensor::addPropertyChangeListener(arg__1); }
inline bool  promoted_canInvert() { return Sensor::canInvert(); }
inline void promoted_dispose() const { Sensor::dispose(); }
inline bool  promoted_getInverted() const { return Sensor::getInverted(); }
inline int  promoted_getKnownState() const { return Sensor::getKnownState(); }
inline int  promoted_getRawState() const { return Sensor::getRawState(); }
inline long  promoted_getSensorDebounceGoingActiveTimer() const { return Sensor::getSensorDebounceGoingActiveTimer(); }
inline long  promoted_getSensorDebounceGoingInActiveTimer() const { return Sensor::getSensorDebounceGoingInActiveTimer(); }
inline void promoted_removePropertyChangeListener(PropertyChangeListener*  arg__1) const { Sensor::removePropertyChangeListener(arg__1); }
inline void promoted_requestUpdateFromLayout() const { Sensor::requestUpdateFromLayout(); }
inline void promoted_setInverted(bool  arg__1) const { Sensor::setInverted(arg__1); }
inline void promoted_setKnownState(int  arg__1) { Sensor::setKnownState(arg__1); }
inline void promoted_setSensorDebounceGoingActiveTimer(long  arg__1) const { Sensor::setSensorDebounceGoingActiveTimer(arg__1); }
inline void promoted_setSensorDebounceGoingInActiveTimer(long  arg__1) const { Sensor::setSensorDebounceGoingInActiveTimer(arg__1); }
inline bool  promoted_useDefaultTimerSettings() const { return Sensor::useDefaultTimerSettings(); }
inline void promoted_useDefaultTimerSettings(bool  arg__1) const { Sensor::useDefaultTimerSettings(arg__1); }
};

class PythonQtWrapper_Sensor : public QObject
{ Q_OBJECT
public:
public slots:
Sensor* new_Sensor(QObject*  parent = 0);
Sensor* new_Sensor(QString  sysName, QObject*  parent);
Sensor* new_Sensor(QString  sysName, QString  userName, QObject*  parent);
void delete_Sensor(Sensor* obj) { delete obj; } 
   void addPropertyChangeListener(Sensor* theWrappedObject, PropertyChangeListener*  arg__1) const;
   bool  canInvert(Sensor* theWrappedObject);
   void dispose(Sensor* theWrappedObject) const;
   bool  getInverted(Sensor* theWrappedObject) const;
   int  getKnownState(Sensor* theWrappedObject) const;
   int  getRawState(Sensor* theWrappedObject) const;
   long  getSensorDebounceGoingActiveTimer(Sensor* theWrappedObject) const;
   long  getSensorDebounceGoingInActiveTimer(Sensor* theWrappedObject) const;
   void removePropertyChangeListener(Sensor* theWrappedObject, PropertyChangeListener*  arg__1) const;
   void requestUpdateFromLayout(Sensor* theWrappedObject) const;
   void setInverted(Sensor* theWrappedObject, bool  arg__1) const;
   void setKnownState(Sensor* theWrappedObject, int  arg__1);
   void setSensorDebounceGoingActiveTimer(Sensor* theWrappedObject, long  arg__1) const;
   void setSensorDebounceGoingInActiveTimer(Sensor* theWrappedObject, long  arg__1) const;
   bool  useDefaultTimerSettings(Sensor* theWrappedObject) const;
   void useDefaultTimerSettings(Sensor* theWrappedObject, bool  arg__1) const;
void py_set_thisAddr(Sensor* theWrappedObject, int  thisAddr){ theWrappedObject->thisAddr = thisAddr; }
int  py_get_thisAddr(Sensor* theWrappedObject){ return theWrappedObject->thisAddr; }
};





class PythonQtShell_Siglet : public Siglet
{
public:
    PythonQtShell_Siglet(QObject*  parent = 0):Siglet(parent),_wrapper(NULL) {};
    PythonQtShell_Siglet(QString  name, QObject*  parent = 0):Siglet(name, parent),_wrapper(NULL) {};

   ~PythonQtShell_Siglet();

virtual void defineIO();
virtual bool  handle();
virtual void init();
virtual void setOutput();

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_Siglet : public Siglet
{ public:
inline void promoted_defineIO() { Siglet::defineIO(); }
inline bool  promoted_handle() { return Siglet::handle(); }
inline void promoted_init() { Siglet::init(); }
inline void promoted_setOutput() { Siglet::setOutput(); }
};

class PythonQtWrapper_Siglet : public QObject
{ Q_OBJECT
public:
public slots:
Siglet* new_Siglet(QObject*  parent = 0);
Siglet* new_Siglet(QString  name, QObject*  parent = 0);
void delete_Siglet(Siglet* obj) { delete obj; } 
   void defineIO(Siglet* theWrappedObject);
   bool  handle(Siglet* theWrappedObject);
   void init(Siglet* theWrappedObject);
   void setOutput(Siglet* theWrappedObject);
void py_set_inputs(Siglet* theWrappedObject, QVector<NamedBean* >  inputs){ theWrappedObject->inputs = inputs; }
QVector<NamedBean* >  py_get_inputs(Siglet* theWrappedObject){ return theWrappedObject->inputs; }
void py_set_outputs(Siglet* theWrappedObject, QVector<NamedBean* >  outputs){ theWrappedObject->outputs = outputs; }
QVector<NamedBean* >  py_get_outputs(Siglet* theWrappedObject){ return theWrappedObject->outputs; }
};





class PythonQtShell_SignalHead : public SignalHead
{
public:
    PythonQtShell_SignalHead(QObject*  parent = 0):SignalHead(parent),_wrapper(NULL) {};
    PythonQtShell_SignalHead(QString  systemName, QObject*  parent):SignalHead(systemName, parent),_wrapper(NULL) {};
    PythonQtShell_SignalHead(QString  systemName, QString  userName, QObject*  parent):SignalHead(systemName, userName, parent),_wrapper(NULL) {};

   ~PythonQtShell_SignalHead();

virtual int  getAppearance();
virtual QString  getAppearanceName();
virtual QString  getAppearanceName(int  arg__1);
virtual bool  getHeld();
virtual bool  getLit();
virtual QVector<QString >  getValidStateNames();
virtual QVector<int >  getValidStates();
virtual void setAppearance(int  arg__1);
virtual void setHeld(bool  arg__1);
virtual void setLit(bool  arg__1);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_SignalHead : public SignalHead
{ public:
inline int  promoted_getAppearance() { return SignalHead::getAppearance(); }
inline QString  promoted_getAppearanceName() { return SignalHead::getAppearanceName(); }
inline QString  promoted_getAppearanceName(int  arg__1) { return SignalHead::getAppearanceName(arg__1); }
inline bool  promoted_getHeld() { return SignalHead::getHeld(); }
inline bool  promoted_getLit() { return SignalHead::getLit(); }
inline QVector<QString >  promoted_getValidStateNames() { return SignalHead::getValidStateNames(); }
inline QVector<int >  promoted_getValidStates() { return SignalHead::getValidStates(); }
inline void promoted_setAppearance(int  arg__1) { SignalHead::setAppearance(arg__1); }
inline void promoted_setHeld(bool  arg__1) { SignalHead::setHeld(arg__1); }
inline void promoted_setLit(bool  arg__1) { SignalHead::setLit(arg__1); }
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
   QString  getAppearanceName(SignalHead* theWrappedObject);
   QString  getAppearanceName(SignalHead* theWrappedObject, int  arg__1);
   bool  getHeld(SignalHead* theWrappedObject);
   bool  getLit(SignalHead* theWrappedObject);
   QVector<QString >  getValidStateNames(SignalHead* theWrappedObject);
   QVector<int >  getValidStates(SignalHead* theWrappedObject);
   void setAppearance(SignalHead* theWrappedObject, int  arg__1);
   void setHeld(SignalHead* theWrappedObject, bool  arg__1);
   void setLit(SignalHead* theWrappedObject, bool  arg__1);
};





class PythonQtShell_Sound : public Sound
{
public:
    PythonQtShell_Sound(QString  path, QObject*  parent = nullptr) throw (NullPointerException):Sound(path, parent),_wrapper(NULL) {};
    PythonQtShell_Sound(QUrl*  url, QObject*  parent = nullptr) throw (NullPointerException):Sound(url, parent),_wrapper(NULL) {};

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





class PythonQtShell_Throttle : public Throttle
{
public:
    PythonQtShell_Throttle(QObject*  parent = 0):Throttle(parent),_wrapper(NULL) {};

   ~PythonQtShell_Throttle();

virtual void addPropertyChangeListener(PropertyChangeListener*  arg__1);
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
virtual void setSpeedSetting(float  arg__1);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_Throttle : public Throttle
{ public:
inline void promoted_addPropertyChangeListener(PropertyChangeListener*  arg__1) { Throttle::addPropertyChangeListener(arg__1); }
inline bool  promoted_getF0() { return Throttle::getF0(); }
inline bool  promoted_getF0Momentary() { return Throttle::getF0Momentary(); }
inline bool  promoted_getF1() { return Throttle::getF1(); }
inline bool  promoted_getF10() { return Throttle::getF10(); }
inline bool  promoted_getF10Momentary() { return Throttle::getF10Momentary(); }
inline bool  promoted_getF11() { return Throttle::getF11(); }
inline bool  promoted_getF11Momentary() { return Throttle::getF11Momentary(); }
inline bool  promoted_getF12() { return Throttle::getF12(); }
inline bool  promoted_getF12Momentary() { return Throttle::getF12Momentary(); }
inline bool  promoted_getF13() { return Throttle::getF13(); }
inline bool  promoted_getF13Momentary() { return Throttle::getF13Momentary(); }
inline bool  promoted_getF14() { return Throttle::getF14(); }
inline bool  promoted_getF14Momentary() { return Throttle::getF14Momentary(); }
inline bool  promoted_getF15() { return Throttle::getF15(); }
inline bool  promoted_getF15Momentary() { return Throttle::getF15Momentary(); }
inline bool  promoted_getF16() { return Throttle::getF16(); }
inline bool  promoted_getF16Momentary() { return Throttle::getF16Momentary(); }
inline bool  promoted_getF17() { return Throttle::getF17(); }
inline bool  promoted_getF17Momentary() { return Throttle::getF17Momentary(); }
inline bool  promoted_getF18() { return Throttle::getF18(); }
inline bool  promoted_getF18Momentary() { return Throttle::getF18Momentary(); }
inline bool  promoted_getF19() { return Throttle::getF19(); }
inline bool  promoted_getF19Momentary() { return Throttle::getF19Momentary(); }
inline bool  promoted_getF1Momentary() { return Throttle::getF1Momentary(); }
inline bool  promoted_getF2() { return Throttle::getF2(); }
inline bool  promoted_getF20() { return Throttle::getF20(); }
inline bool  promoted_getF20Momentary() { return Throttle::getF20Momentary(); }
inline bool  promoted_getF21() { return Throttle::getF21(); }
inline bool  promoted_getF21Momentary() { return Throttle::getF21Momentary(); }
inline bool  promoted_getF22() { return Throttle::getF22(); }
inline bool  promoted_getF22Momentary() { return Throttle::getF22Momentary(); }
inline bool  promoted_getF23() { return Throttle::getF23(); }
inline bool  promoted_getF23Momentary() { return Throttle::getF23Momentary(); }
inline bool  promoted_getF24() { return Throttle::getF24(); }
inline bool  promoted_getF24Momentary() { return Throttle::getF24Momentary(); }
inline bool  promoted_getF25() { return Throttle::getF25(); }
inline bool  promoted_getF25Momentary() { return Throttle::getF25Momentary(); }
inline bool  promoted_getF26() { return Throttle::getF26(); }
inline bool  promoted_getF26Momentary() { return Throttle::getF26Momentary(); }
inline bool  promoted_getF27() { return Throttle::getF27(); }
inline bool  promoted_getF27Momentary() { return Throttle::getF27Momentary(); }
inline bool  promoted_getF28() { return Throttle::getF28(); }
inline bool  promoted_getF28Momentary() { return Throttle::getF28Momentary(); }
inline bool  promoted_getF2Momentary() { return Throttle::getF2Momentary(); }
inline bool  promoted_getF3() { return Throttle::getF3(); }
inline bool  promoted_getF3Momentary() { return Throttle::getF3Momentary(); }
inline bool  promoted_getF4() { return Throttle::getF4(); }
inline bool  promoted_getF4Momentary() { return Throttle::getF4Momentary(); }
inline bool  promoted_getF5() { return Throttle::getF5(); }
inline bool  promoted_getF5Momentary() { return Throttle::getF5Momentary(); }
inline bool  promoted_getF6() { return Throttle::getF6(); }
inline bool  promoted_getF6Momentary() { return Throttle::getF6Momentary(); }
inline bool  promoted_getF7() { return Throttle::getF7(); }
inline bool  promoted_getF7Momentary() { return Throttle::getF7Momentary(); }
inline bool  promoted_getF8() { return Throttle::getF8(); }
inline bool  promoted_getF8Momentary() { return Throttle::getF8Momentary(); }
inline bool  promoted_getF9() { return Throttle::getF9(); }
inline bool  promoted_getF9Momentary() { return Throttle::getF9Momentary(); }
inline bool  promoted_getIsForward() { return Throttle::getIsForward(); }
inline QVector<PropertyChangeListener* >*  promoted_getListeners() { return Throttle::getListeners(); }
inline LocoAddress*  promoted_getLocoAddress() { return Throttle::getLocoAddress(); }
inline float  promoted_getSpeedSetting() { return Throttle::getSpeedSetting(); }
inline void promoted_removePropertyChangeListener(PropertyChangeListener*  arg__1) { Throttle::removePropertyChangeListener(arg__1); }
inline void promoted_setF0(bool  arg__1) { Throttle::setF0(arg__1); }
inline void promoted_setF0Momentary(bool  arg__1) { Throttle::setF0Momentary(arg__1); }
inline void promoted_setF1(bool  arg__1) { Throttle::setF1(arg__1); }
inline void promoted_setF10(bool  arg__1) { Throttle::setF10(arg__1); }
inline void promoted_setF10Momentary(bool  arg__1) { Throttle::setF10Momentary(arg__1); }
inline void promoted_setF11(bool  arg__1) { Throttle::setF11(arg__1); }
inline void promoted_setF11Momentary(bool  arg__1) { Throttle::setF11Momentary(arg__1); }
inline void promoted_setF12(bool  arg__1) { Throttle::setF12(arg__1); }
inline void promoted_setF12Momentary(bool  arg__1) { Throttle::setF12Momentary(arg__1); }
inline void promoted_setF13(bool  arg__1) { Throttle::setF13(arg__1); }
inline void promoted_setF13Momentary(bool  arg__1) { Throttle::setF13Momentary(arg__1); }
inline void promoted_setF14(bool  arg__1) { Throttle::setF14(arg__1); }
inline void promoted_setF14Momentary(bool  arg__1) { Throttle::setF14Momentary(arg__1); }
inline void promoted_setF15(bool  arg__1) { Throttle::setF15(arg__1); }
inline void promoted_setF15Momentary(bool  arg__1) { Throttle::setF15Momentary(arg__1); }
inline void promoted_setF16(bool  arg__1) { Throttle::setF16(arg__1); }
inline void promoted_setF16Momentary(bool  arg__1) { Throttle::setF16Momentary(arg__1); }
inline void promoted_setF17(bool  arg__1) { Throttle::setF17(arg__1); }
inline void promoted_setF17Momentary(bool  arg__1) { Throttle::setF17Momentary(arg__1); }
inline void promoted_setF18(bool  arg__1) { Throttle::setF18(arg__1); }
inline void promoted_setF18Momentary(bool  arg__1) { Throttle::setF18Momentary(arg__1); }
inline void promoted_setF19(bool  arg__1) { Throttle::setF19(arg__1); }
inline void promoted_setF19Momentary(bool  arg__1) { Throttle::setF19Momentary(arg__1); }
inline void promoted_setF1Momentary(bool  arg__1) { Throttle::setF1Momentary(arg__1); }
inline void promoted_setF2(bool  arg__1) { Throttle::setF2(arg__1); }
inline void promoted_setF20(bool  arg__1) { Throttle::setF20(arg__1); }
inline void promoted_setF20Momentary(bool  arg__1) { Throttle::setF20Momentary(arg__1); }
inline void promoted_setF21(bool  arg__1) { Throttle::setF21(arg__1); }
inline void promoted_setF21Momentary(bool  arg__1) { Throttle::setF21Momentary(arg__1); }
inline void promoted_setF22(bool  arg__1) { Throttle::setF22(arg__1); }
inline void promoted_setF22Momentary(bool  arg__1) { Throttle::setF22Momentary(arg__1); }
inline void promoted_setF23(bool  arg__1) { Throttle::setF23(arg__1); }
inline void promoted_setF23Momentary(bool  arg__1) { Throttle::setF23Momentary(arg__1); }
inline void promoted_setF24(bool  arg__1) { Throttle::setF24(arg__1); }
inline void promoted_setF24Momentary(bool  arg__1) { Throttle::setF24Momentary(arg__1); }
inline void promoted_setF25(bool  arg__1) { Throttle::setF25(arg__1); }
inline void promoted_setF25Momentary(bool  arg__1) { Throttle::setF25Momentary(arg__1); }
inline void promoted_setF26(bool  arg__1) { Throttle::setF26(arg__1); }
inline void promoted_setF26Momentary(bool  arg__1) { Throttle::setF26Momentary(arg__1); }
inline void promoted_setF27(bool  arg__1) { Throttle::setF27(arg__1); }
inline void promoted_setF27Momentary(bool  arg__1) { Throttle::setF27Momentary(arg__1); }
inline void promoted_setF28(bool  arg__1) { Throttle::setF28(arg__1); }
inline void promoted_setF28Momentary(bool  arg__1) { Throttle::setF28Momentary(arg__1); }
inline void promoted_setF2Momentary(bool  arg__1) { Throttle::setF2Momentary(arg__1); }
inline void promoted_setF3(bool  arg__1) { Throttle::setF3(arg__1); }
inline void promoted_setF3Momentary(bool  arg__1) { Throttle::setF3Momentary(arg__1); }
inline void promoted_setF4(bool  arg__1) { Throttle::setF4(arg__1); }
inline void promoted_setF4Momentary(bool  arg__1) { Throttle::setF4Momentary(arg__1); }
inline void promoted_setF5(bool  arg__1) { Throttle::setF5(arg__1); }
inline void promoted_setF5Momentary(bool  arg__1) { Throttle::setF5Momentary(arg__1); }
inline void promoted_setF6(bool  arg__1) { Throttle::setF6(arg__1); }
inline void promoted_setF6Momentary(bool  arg__1) { Throttle::setF6Momentary(arg__1); }
inline void promoted_setF7(bool  arg__1) { Throttle::setF7(arg__1); }
inline void promoted_setF7Momentary(bool  arg__1) { Throttle::setF7Momentary(arg__1); }
inline void promoted_setF8(bool  arg__1) { Throttle::setF8(arg__1); }
inline void promoted_setF8Momentary(bool  arg__1) { Throttle::setF8Momentary(arg__1); }
inline void promoted_setF9(bool  arg__1) { Throttle::setF9(arg__1); }
inline void promoted_setF9Momentary(bool  arg__1) { Throttle::setF9Momentary(arg__1); }
inline void promoted_setIsForward(bool  arg__1) { Throttle::setIsForward(arg__1); }
inline void promoted_setSpeedSetting(float  arg__1) { Throttle::setSpeedSetting(arg__1); }
};

class PythonQtWrapper_Throttle : public QObject
{ Q_OBJECT
public:
public slots:
Throttle* new_Throttle(QObject*  parent = 0);
void delete_Throttle(Throttle* obj) { delete obj; } 
   void addPropertyChangeListener(Throttle* theWrappedObject, PropertyChangeListener*  arg__1);
   bool  getF0(Throttle* theWrappedObject);
   bool  getF0Momentary(Throttle* theWrappedObject);
   bool  getF1(Throttle* theWrappedObject);
   bool  getF10(Throttle* theWrappedObject);
   bool  getF10Momentary(Throttle* theWrappedObject);
   bool  getF11(Throttle* theWrappedObject);
   bool  getF11Momentary(Throttle* theWrappedObject);
   bool  getF12(Throttle* theWrappedObject);
   bool  getF12Momentary(Throttle* theWrappedObject);
   bool  getF13(Throttle* theWrappedObject);
   bool  getF13Momentary(Throttle* theWrappedObject);
   bool  getF14(Throttle* theWrappedObject);
   bool  getF14Momentary(Throttle* theWrappedObject);
   bool  getF15(Throttle* theWrappedObject);
   bool  getF15Momentary(Throttle* theWrappedObject);
   bool  getF16(Throttle* theWrappedObject);
   bool  getF16Momentary(Throttle* theWrappedObject);
   bool  getF17(Throttle* theWrappedObject);
   bool  getF17Momentary(Throttle* theWrappedObject);
   bool  getF18(Throttle* theWrappedObject);
   bool  getF18Momentary(Throttle* theWrappedObject);
   bool  getF19(Throttle* theWrappedObject);
   bool  getF19Momentary(Throttle* theWrappedObject);
   bool  getF1Momentary(Throttle* theWrappedObject);
   bool  getF2(Throttle* theWrappedObject);
   bool  getF20(Throttle* theWrappedObject);
   bool  getF20Momentary(Throttle* theWrappedObject);
   bool  getF21(Throttle* theWrappedObject);
   bool  getF21Momentary(Throttle* theWrappedObject);
   bool  getF22(Throttle* theWrappedObject);
   bool  getF22Momentary(Throttle* theWrappedObject);
   bool  getF23(Throttle* theWrappedObject);
   bool  getF23Momentary(Throttle* theWrappedObject);
   bool  getF24(Throttle* theWrappedObject);
   bool  getF24Momentary(Throttle* theWrappedObject);
   bool  getF25(Throttle* theWrappedObject);
   bool  getF25Momentary(Throttle* theWrappedObject);
   bool  getF26(Throttle* theWrappedObject);
   bool  getF26Momentary(Throttle* theWrappedObject);
   bool  getF27(Throttle* theWrappedObject);
   bool  getF27Momentary(Throttle* theWrappedObject);
   bool  getF28(Throttle* theWrappedObject);
   bool  getF28Momentary(Throttle* theWrappedObject);
   bool  getF2Momentary(Throttle* theWrappedObject);
   bool  getF3(Throttle* theWrappedObject);
   bool  getF3Momentary(Throttle* theWrappedObject);
   bool  getF4(Throttle* theWrappedObject);
   bool  getF4Momentary(Throttle* theWrappedObject);
   bool  getF5(Throttle* theWrappedObject);
   bool  getF5Momentary(Throttle* theWrappedObject);
   bool  getF6(Throttle* theWrappedObject);
   bool  getF6Momentary(Throttle* theWrappedObject);
   bool  getF7(Throttle* theWrappedObject);
   bool  getF7Momentary(Throttle* theWrappedObject);
   bool  getF8(Throttle* theWrappedObject);
   bool  getF8Momentary(Throttle* theWrappedObject);
   bool  getF9(Throttle* theWrappedObject);
   bool  getF9Momentary(Throttle* theWrappedObject);
   bool  getIsForward(Throttle* theWrappedObject);
   QVector<PropertyChangeListener* >*  getListeners(Throttle* theWrappedObject);
   LocoAddress*  getLocoAddress(Throttle* theWrappedObject);
   float  getSpeedSetting(Throttle* theWrappedObject);
   void removePropertyChangeListener(Throttle* theWrappedObject, PropertyChangeListener*  arg__1);
   void setF0(Throttle* theWrappedObject, bool  arg__1);
   void setF0Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setF1(Throttle* theWrappedObject, bool  arg__1);
   void setF10(Throttle* theWrappedObject, bool  arg__1);
   void setF10Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setF11(Throttle* theWrappedObject, bool  arg__1);
   void setF11Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setF12(Throttle* theWrappedObject, bool  arg__1);
   void setF12Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setF13(Throttle* theWrappedObject, bool  arg__1);
   void setF13Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setF14(Throttle* theWrappedObject, bool  arg__1);
   void setF14Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setF15(Throttle* theWrappedObject, bool  arg__1);
   void setF15Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setF16(Throttle* theWrappedObject, bool  arg__1);
   void setF16Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setF17(Throttle* theWrappedObject, bool  arg__1);
   void setF17Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setF18(Throttle* theWrappedObject, bool  arg__1);
   void setF18Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setF19(Throttle* theWrappedObject, bool  arg__1);
   void setF19Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setF1Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setF2(Throttle* theWrappedObject, bool  arg__1);
   void setF20(Throttle* theWrappedObject, bool  arg__1);
   void setF20Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setF21(Throttle* theWrappedObject, bool  arg__1);
   void setF21Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setF22(Throttle* theWrappedObject, bool  arg__1);
   void setF22Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setF23(Throttle* theWrappedObject, bool  arg__1);
   void setF23Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setF24(Throttle* theWrappedObject, bool  arg__1);
   void setF24Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setF25(Throttle* theWrappedObject, bool  arg__1);
   void setF25Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setF26(Throttle* theWrappedObject, bool  arg__1);
   void setF26Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setF27(Throttle* theWrappedObject, bool  arg__1);
   void setF27Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setF28(Throttle* theWrappedObject, bool  arg__1);
   void setF28Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setF2Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setF3(Throttle* theWrappedObject, bool  arg__1);
   void setF3Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setF4(Throttle* theWrappedObject, bool  arg__1);
   void setF4Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setF5(Throttle* theWrappedObject, bool  arg__1);
   void setF5Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setF6(Throttle* theWrappedObject, bool  arg__1);
   void setF6Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setF7(Throttle* theWrappedObject, bool  arg__1);
   void setF7Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setF8(Throttle* theWrappedObject, bool  arg__1);
   void setF8Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setF9(Throttle* theWrappedObject, bool  arg__1);
   void setF9Momentary(Throttle* theWrappedObject, bool  arg__1);
   void setIsForward(Throttle* theWrappedObject, bool  arg__1);
   void setSpeedSetting(Throttle* theWrappedObject, float  arg__1);
};





class PythonQtShell_Turnout : public Turnout
{
public:
    PythonQtShell_Turnout(QObject*  parent = 0):Turnout(parent),_wrapper(NULL) {};
    PythonQtShell_Turnout(QString  sysName, QObject*  parent):Turnout(sysName, parent),_wrapper(NULL) {};
    PythonQtShell_Turnout(QString  sysName, QString  userName, QObject*  parent):Turnout(sysName, userName, parent),_wrapper(NULL) {};

   ~PythonQtShell_Turnout();

virtual bool  canInvert() const;
virtual bool  canLock(int  arg__1);
virtual void enableLockOperation(int  arg__1, bool  arg__2);
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
virtual bool  getLocked(int  arg__1);
virtual int  getNumberOutputBits();
virtual int  getPossibleLockModes();
virtual bool  getReportLocked();
virtual Sensor*  getSecondSensor();
virtual float  getStraightLimit();
virtual QString  getStraightSpeed();
virtual QStringList  getValidDecoderNames();
virtual QStringList  getValidFeedbackNames();
virtual int  getValidFeedbackTypes();
virtual bool  isConsistentState();
virtual void provideFirstFeedbackSensor(QString  arg__1) throw (JmriException) ;
virtual void provideSecondFeedbackSensor(QString  arg__1) throw (JmriException) ;
virtual void requestUpdateFromLayout();
virtual void setBinaryOutput(bool  arg__1);
virtual void setCommandedState(int  arg__1);
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
virtual void setReportLocked(bool  arg__1);
virtual void setStraightSpeed(QString  arg__1) const throw (JmriException) ;

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_Turnout : public Turnout
{ public:
inline bool  promoted_canInvert() const { return Turnout::canInvert(); }
inline bool  promoted_canLock(int  arg__1) { return Turnout::canLock(arg__1); }
inline void promoted_enableLockOperation(int  arg__1, bool  arg__2) { Turnout::enableLockOperation(arg__1, arg__2); }
inline int  promoted_getCommandedState() { return Turnout::getCommandedState(); }
inline int  promoted_getControlType() { return Turnout::getControlType(); }
inline QString  promoted_getDecoderName() { return Turnout::getDecoderName(); }
inline float  promoted_getDivergingLimit() { return Turnout::getDivergingLimit(); }
inline QString  promoted_getDivergingSpeed() { return Turnout::getDivergingSpeed(); }
inline int  promoted_getFeedbackMode() { return Turnout::getFeedbackMode(); }
inline QString  promoted_getFeedbackModeName() { return Turnout::getFeedbackModeName(); }
inline Sensor*  promoted_getFirstSensor() { return Turnout::getFirstSensor(); }
inline bool  promoted_getInhibitOperation() { return Turnout::getInhibitOperation(); }
inline bool  promoted_getInverted() { return Turnout::getInverted(); }
inline int  promoted_getKnownState() { return Turnout::getKnownState(); }
inline bool  promoted_getLocked(int  arg__1) { return Turnout::getLocked(arg__1); }
inline int  promoted_getNumberOutputBits() { return Turnout::getNumberOutputBits(); }
inline int  promoted_getPossibleLockModes() { return Turnout::getPossibleLockModes(); }
inline bool  promoted_getReportLocked() { return Turnout::getReportLocked(); }
inline Sensor*  promoted_getSecondSensor() { return Turnout::getSecondSensor(); }
inline float  promoted_getStraightLimit() { return Turnout::getStraightLimit(); }
inline QString  promoted_getStraightSpeed() { return Turnout::getStraightSpeed(); }
inline QStringList  promoted_getValidDecoderNames() { return Turnout::getValidDecoderNames(); }
inline QStringList  promoted_getValidFeedbackNames() { return Turnout::getValidFeedbackNames(); }
inline int  promoted_getValidFeedbackTypes() { return Turnout::getValidFeedbackTypes(); }
inline bool  promoted_isConsistentState() { return Turnout::isConsistentState(); }
inline void promoted_provideFirstFeedbackSensor(QString  arg__1) throw (JmriException)  { Turnout::provideFirstFeedbackSensor(arg__1); }
inline void promoted_provideSecondFeedbackSensor(QString  arg__1) throw (JmriException)  { Turnout::provideSecondFeedbackSensor(arg__1); }
inline void promoted_requestUpdateFromLayout() { Turnout::requestUpdateFromLayout(); }
inline void promoted_setBinaryOutput(bool  arg__1) { Turnout::setBinaryOutput(arg__1); }
inline void promoted_setCommandedState(int  arg__1) { Turnout::setCommandedState(arg__1); }
inline void promoted_setControlType(int  arg__1) { Turnout::setControlType(arg__1); }
inline void promoted_setDecoderName(QString  arg__1) { Turnout::setDecoderName(arg__1); }
inline void promoted_setDivergingSpeed(QString  arg__1) const throw (JmriException)  { Turnout::setDivergingSpeed(arg__1); }
inline void promoted_setFeedbackMode(QString  arg__1) { Turnout::setFeedbackMode(arg__1); }
inline void promoted_setFeedbackMode(int  arg__1) { Turnout::setFeedbackMode(arg__1); }
inline void promoted_setInhibitOperation(bool  arg__1) { Turnout::setInhibitOperation(arg__1); }
inline void promoted_setInitialKnownStateFromFeedback() { Turnout::setInitialKnownStateFromFeedback(); }
inline void promoted_setInverted(bool  arg__1) { Turnout::setInverted(arg__1); }
inline void promoted_setLocked(int  arg__1, bool  arg__2) { Turnout::setLocked(arg__1, arg__2); }
inline void promoted_setNumberOutputBits(int  arg__1) { Turnout::setNumberOutputBits(arg__1); }
inline void promoted_setReportLocked(bool  arg__1) { Turnout::setReportLocked(arg__1); }
inline void promoted_setStraightSpeed(QString  arg__1) const throw (JmriException)  { Turnout::setStraightSpeed(arg__1); }
};

class PythonQtWrapper_Turnout : public QObject
{ Q_OBJECT
public:
public slots:
Turnout* new_Turnout(QObject*  parent = 0);
Turnout* new_Turnout(QString  sysName, QObject*  parent);
Turnout* new_Turnout(QString  sysName, QString  userName, QObject*  parent);
void delete_Turnout(Turnout* obj) { delete obj; } 
   bool  canInvert(Turnout* theWrappedObject) const;
   bool  canLock(Turnout* theWrappedObject, int  arg__1);
   void enableLockOperation(Turnout* theWrappedObject, int  arg__1, bool  arg__2);
   int  getCommandedState(Turnout* theWrappedObject);
   int  getControlType(Turnout* theWrappedObject);
   QString  getDecoderName(Turnout* theWrappedObject);
   float  getDivergingLimit(Turnout* theWrappedObject);
   QString  getDivergingSpeed(Turnout* theWrappedObject);
   int  getFeedbackMode(Turnout* theWrappedObject);
   QString  getFeedbackModeName(Turnout* theWrappedObject);
   Sensor*  getFirstSensor(Turnout* theWrappedObject);
   bool  getInhibitOperation(Turnout* theWrappedObject);
   bool  getInverted(Turnout* theWrappedObject);
   int  getKnownState(Turnout* theWrappedObject);
   bool  getLocked(Turnout* theWrappedObject, int  arg__1);
   int  getNumberOutputBits(Turnout* theWrappedObject);
   int  getPossibleLockModes(Turnout* theWrappedObject);
   bool  getReportLocked(Turnout* theWrappedObject);
   Sensor*  getSecondSensor(Turnout* theWrappedObject);
   float  getStraightLimit(Turnout* theWrappedObject);
   QString  getStraightSpeed(Turnout* theWrappedObject);
   QStringList  getValidDecoderNames(Turnout* theWrappedObject);
   QStringList  getValidFeedbackNames(Turnout* theWrappedObject);
   int  getValidFeedbackTypes(Turnout* theWrappedObject);
   int  static_Turnout_invertTurnoutState(int  inState);
   bool  isConsistentState(Turnout* theWrappedObject);
   void provideFirstFeedbackSensor(Turnout* theWrappedObject, QString  arg__1) throw (JmriException) ;
   void provideSecondFeedbackSensor(Turnout* theWrappedObject, QString  arg__1) throw (JmriException) ;
   void requestUpdateFromLayout(Turnout* theWrappedObject);
   void setBinaryOutput(Turnout* theWrappedObject, bool  arg__1);
   void setCommandedState(Turnout* theWrappedObject, int  arg__1);
   void setControlType(Turnout* theWrappedObject, int  arg__1);
   void setDecoderName(Turnout* theWrappedObject, QString  arg__1);
   void setDivergingSpeed(Turnout* theWrappedObject, QString  arg__1) const throw (JmriException) ;
   void setFeedbackMode(Turnout* theWrappedObject, QString  arg__1);
   void setFeedbackMode(Turnout* theWrappedObject, int  arg__1);
   void setInhibitOperation(Turnout* theWrappedObject, bool  arg__1);
   void setInitialKnownStateFromFeedback(Turnout* theWrappedObject);
   void setInverted(Turnout* theWrappedObject, bool  arg__1);
   void setLocked(Turnout* theWrappedObject, int  arg__1, bool  arg__2);
   void setNumberOutputBits(Turnout* theWrappedObject, int  arg__1);
   void setReportLocked(Turnout* theWrappedObject, bool  arg__1);
   void setStraightSpeed(Turnout* theWrappedObject, QString  arg__1) const throw (JmriException) ;
};


