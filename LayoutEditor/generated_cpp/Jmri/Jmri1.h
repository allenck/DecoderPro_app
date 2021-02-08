#include <PythonQt.h>
#include <QObject>
#include <QTextEdit>
#include <QVariant>
#include <abstractnamedbean.h>
#include <audiomanager.h>
#include <block.h>
#include <dcclocoaddress.h>
#include <defaultmemorymanager.h>
#include <defaultprogrammermanager.h>
#include <editor.h>
#include <editscene.h>
#include <eventobject.h>
#include <fileutil.h>
#include <flowlayout.h>
#include <instancemanager.h>
#include <jframe.h>
#include <jlabel.h>
#include <jlist.h>
#include <jmrijframe.h>
#include <jtable.h>
#include <jtextarea.h>
#include <layoutblockmanager.h>
#include <layouteditor.h>
#include <layoutturnout.h>
#include <light.h>
#include <lightmanager.h>
#include <listselectionmodel.h>
#include <lncommandstationtype.h>
#include <lnpacketizer.h>
#include <lnportcontroller.h>
#include <lnpowermanager.h>
#include <lnreportermanager.h>
#include <lnsensor.h>
#include <lnsensormanager.h>
#include <lntrafficcontroller.h>
#include <lnturnout.h>
#include <loconetinterface.h>
#include <loconetmessage.h>
#include <loconetsystemconnectionmemo.h>
#include <namedbean.h>
#include <positionable.h>
#include <positionablelabel.h>
#include <propertychangeevent.h>
#include <propertychangelistener.h>
#include <proxylightmanager.h>
#include <proxysensormanager.h>
#include <proxyturnoutmanager.h>
#include <qabstractitemdelegate.h>
#include <qabstractitemmodel.h>
#include <qaction.h>
#include <qactiongroup.h>
#include <qbrush.h>
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
#include <qmimedata.h>
#include <qobject.h>
#include <qpaintdevice.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qpalette.h>
#include <qpen.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qpolygon.h>
#include <qrect.h>
#include <qregexp.h>
#include <qregion.h>
#include <qscrollarea.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstatusbar.h>
#include <qstringlist.h>
#include <qstyle.h>
#include <qstyleditemdelegate.h>
#include <qstyleoption.h>
#include <qtableview.h>
#include <qtextcursor.h>
#include <qtextdocument.h>
#include <qtextedit.h>
#include <qtextformat.h>
#include <qtextstream.h>
#include <qtransform.h>
#include <qurl.h>
#include <qvector.h>
#include <qwidget.h>
#include <reportermanager.h>
#include <sensor.h>
#include <sensormanager.h>
#include <signalhead.h>
#include <systemconnectionmemo.h>
#include <tablecolumn.h>
#include <tablecolumnmodel.h>
#include <throttlemanager.h>
#include <turnout.h>
#include <turnoutmanager.h>
#include <turnoutoperation.h>
#include <windowlistener.h>



class PythonQtShell_DefaultMemoryManager : public DefaultMemoryManager
{
public:
    PythonQtShell_DefaultMemoryManager(QObject*  parent = 0):DefaultMemoryManager(parent),_wrapper(NULL) {}

   ~PythonQtShell_DefaultMemoryManager();

virtual QString  getNamedBeanClass() const;
virtual QString  getSystemPrefix() const;

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_DefaultMemoryManager : public DefaultMemoryManager
{ public:
inline QString  py_q_getNamedBeanClass() const { return DefaultMemoryManager::getNamedBeanClass(); }
inline QString  py_q_getSystemPrefix() const { return DefaultMemoryManager::getSystemPrefix(); }
};

class PythonQtWrapper_DefaultMemoryManager : public QObject
{ Q_OBJECT
public:
public slots:
DefaultMemoryManager* new_DefaultMemoryManager(QObject*  parent = 0);
void delete_DefaultMemoryManager(DefaultMemoryManager* obj) { delete obj; } 
   QString  getNamedBeanClass(DefaultMemoryManager* theWrappedObject) const;
   QString  py_q_getNamedBeanClass(DefaultMemoryManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_DefaultMemoryManager*)theWrappedObject)->py_q_getNamedBeanClass());}
   QString  getSystemPrefix(DefaultMemoryManager* theWrappedObject) const;
   QString  py_q_getSystemPrefix(DefaultMemoryManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_DefaultMemoryManager*)theWrappedObject)->py_q_getSystemPrefix());}
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
void delete_EditScene(EditScene* obj) { delete obj; } 
   QColor  getBackground(EditScene* theWrappedObject);
   QWidget*  getTopLevelAncestor(EditScene* theWrappedObject);
   void repaint(EditScene* theWrappedObject);
};





class PythonQtShell_Editor : public Editor
{
public:
    PythonQtShell_Editor(QString  name, QWidget*  parent):Editor(name, parent),_wrapper(NULL) {}
    PythonQtShell_Editor(QString  name, bool  saveSize, bool  savePosition, QWidget*  parent = 0):Editor(name, saveSize, savePosition, parent),_wrapper(NULL) {}
    PythonQtShell_Editor(QWidget*  parent = 0):Editor(parent),_wrapper(NULL) {}

   ~PythonQtShell_Editor();

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
virtual void mouseClicked(QGraphicsSceneMouseEvent*  arg__1);
virtual void mouseDoubleClickEvent(QMouseEvent*  event);
virtual void mouseDragged(QGraphicsSceneMouseEvent*  arg__1);
virtual void mouseEntered(QGraphicsSceneMouseEvent*  arg__1);
virtual void mouseExited(QGraphicsSceneMouseEvent*  event);
virtual void mouseMoveEvent(QMouseEvent*  event);
virtual void mouseMoved(QGraphicsSceneMouseEvent*  arg__1);
virtual void mousePressEvent(QMouseEvent*  event);
virtual void mousePressed(QGraphicsSceneMouseEvent*  arg__1);
virtual void mouseReleaseEvent(QMouseEvent*  event);
virtual void mouseReleased(QGraphicsSceneMouseEvent*  arg__1);
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
virtual void setAllEditable(bool  state);
virtual void setAllPositionable(bool  state);
virtual void setEnabled(bool  b);
virtual void setNextLocation(Positionable*  arg__1);
virtual void setRemoveMenu(Positionable*  p, QMenu*  popup);
virtual void setScroll(int  state);
virtual void setSelectionsRotation(int  k, Positionable*  p);
virtual void setSelectionsScale(double  s, Positionable*  p);
virtual void setTitle();
virtual void setUseGlobalFlag(bool  set);
virtual void setVisible(bool  visible);
virtual QPainter*  sharedPainter() const;
virtual void showEvent(QShowEvent*  event);
virtual void showPopUp(Positionable*  arg__1, QMouseEvent*  arg__2);
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

class PythonQtPublicPromoter_Editor : public Editor
{ public:
inline void promoted_addBackgroundEditor() { this->addBackgroundEditor(); }
inline void promoted_addBlockContentsEditor() { this->addBlockContentsEditor(); }
inline void promoted_addIconEditor() { this->addIconEditor(); }
inline PositionableLabel*  promoted_addLabel(QString  text) { return this->addLabel(text); }
inline void promoted_addLeftTOEditor() { this->addLeftTOEditor(); }
inline void promoted_addLightEditor() { this->addLightEditor(); }
inline void promoted_addMemoryEditor() { this->addMemoryEditor(); }
inline JFrameItem*  promoted_addMultiSensorEditor() { return this->addMultiSensorEditor(); }
inline void promoted_addReporterEditor() { this->addReporterEditor(); }
inline void promoted_addRightTOEditor() { this->addRightTOEditor(); }
inline void promoted_addRpsReporter() { this->addRpsReporter(); }
inline void promoted_addSensorEditor() { this->addSensorEditor(); }
inline void promoted_addSignalHeadEditor() { this->addSignalHeadEditor(); }
inline void promoted_addSignalMastEditor() { this->addSignalMastEditor(); }
inline void promoted_addSlip() { this->addSlip(); }
inline void promoted_addSlipTOEditor() { this->addSlipTOEditor(); }
inline void promoted_addTextEditor() { this->addTextEditor(); }
inline void promoted_addToTarget(Positionable*  l) { this->addToTarget(l); }
inline void promoted_addTurnoutL() { this->addTurnoutL(); }
inline void promoted_addTurnoutR() { this->addTurnoutR(); }
inline Editor*  promoted_changeView(QString  className) { return this->changeView(className); }
inline void promoted_deselectSelectionGroup() { this->deselectSelectionGroup(); }
inline void promoted_dockSelections(Positionable*  p) { this->dockSelections(p); }
inline int  promoted_getItemX(Positionable*  p, int  deltaX) { return this->getItemX(p, deltaX); }
inline int  promoted_getItemY(Positionable*  p, int  deltaY) { return this->getItemY(p, deltaY); }
inline QList<Positionable* >*  promoted_getSelectedItems(QGraphicsSceneMouseEvent*  event) { return this->getSelectedItems(event); }
inline QList<Positionable* >*  promoted_getSelectedItems(QPointF  pt) { return this->getSelectedItems(pt); }
inline QSize  promoted_getTargetPanelSize() { return this->getTargetPanelSize(); }
inline double  promoted_getZoomRatio() { return this->getZoomRatio(); }
inline void promoted_init(QString  name) { this->init(name); }
inline void promoted_locoMarkerFromInput() { this->locoMarkerFromInput(); }
inline void promoted_locoMarkerFromRoster() { this->locoMarkerFromRoster(); }
inline void promoted_makeSelectionGroup(QGraphicsSceneMouseEvent*  event) { this->makeSelectionGroup(event); }
inline void promoted_modifySelectionGroup(Positionable*  selection, QGraphicsSceneMouseEvent*  event) { this->modifySelectionGroup(selection, event); }
inline void promoted_moveItem(Positionable*  p, int  deltaX, int  deltaY) { this->moveItem(p, deltaX, deltaY); }
inline void promoted_paintTargetPanel(QGraphicsScene*  g) { this->paintTargetPanel(g); }
inline void promoted_putBackground() { this->putBackground(); }
inline Positionable*  promoted_putIcon() { return this->putIcon(); }
inline void promoted_removeFromTarget(Positionable*  l) { this->removeFromTarget(l); }
inline void promoted_removeMarkers() { this->removeMarkers(); }
inline void promoted_removeSelections(Positionable*  p) { this->removeSelections(p); }
inline void promoted_repaint() { this->repaint(); }
inline void promoted_setNextLocation(Positionable*  arg__1) { this->setNextLocation(arg__1); }
inline void promoted_setPaintScale(double  newScale) { this->setPaintScale(newScale); }
inline void promoted_setScroll(int  state) { this->setScroll(state); }
inline void promoted_setSelectionsDockingLocation(Positionable*  p) { this->setSelectionsDockingLocation(p); }
inline void promoted_setSelectionsHidden(bool  enabled, Positionable*  p) { this->setSelectionsHidden(enabled, p); }
inline bool  promoted_setSelectionsPositionable(bool  enabled, Positionable*  p) { return this->setSelectionsPositionable(enabled, p); }
inline void promoted_setSelectionsRotation(int  k, Positionable*  p) { this->setSelectionsRotation(k, p); }
inline void promoted_setSelectionsScale(double  s, Positionable*  p) { this->setSelectionsScale(s, p); }
inline void promoted_setTargetPanel(EditScene*  targetPanel, JmriJFrame*  frame) { this->setTargetPanel(targetPanel, frame); }
inline void promoted_setTargetPanelSize(int  w, int  h) { this->setTargetPanelSize(w, h); }
inline bool  promoted_setTextAttributes(Positionable*  p, QMenu*  popup) { return this->setTextAttributes(p, popup); }
inline void promoted_setToolTip(QString  tt) { this->setToolTip(tt); }
inline bool  promoted_showAlignPopup(Positionable*  p) { return this->showAlignPopup(p); }
inline void promoted_showPopUp(Positionable*  arg__1, QGraphicsSceneMouseEvent*  arg__2) { this->showPopUp(arg__1, arg__2); }
inline void promoted_showPopUp(Positionable*  arg__1, QMouseEvent*  arg__2) { this->showPopUp(arg__1, arg__2); }
inline void promoted_targetWindowClosing(bool  save) { this->targetWindowClosing(save); }
inline void promoted_targetWindowClosingEvent(QCloseEvent*  e) { this->targetWindowClosingEvent(e); }
inline bool  py_q_deletePanel() { return Editor::deletePanel(); }
inline void py_q_dispose() { Editor::dispose(); }
inline QString  py_q_getTitle() { return Editor::getTitle(); }
inline void py_q_init(QString  name) { Editor::init(name); }
inline void py_q_initView() { Editor::initView(); }
inline void py_q_mouseClicked(QGraphicsSceneMouseEvent*  arg__1) { Editor::mouseClicked(arg__1); }
inline void py_q_mouseDragged(QGraphicsSceneMouseEvent*  arg__1) { Editor::mouseDragged(arg__1); }
inline void py_q_mouseEntered(QGraphicsSceneMouseEvent*  arg__1) { Editor::mouseEntered(arg__1); }
inline void py_q_mouseExited(QGraphicsSceneMouseEvent*  event) { Editor::mouseExited(event); }
inline void py_q_mouseMoved(QGraphicsSceneMouseEvent*  arg__1) { Editor::mouseMoved(arg__1); }
inline void py_q_mousePressed(QGraphicsSceneMouseEvent*  arg__1) { Editor::mousePressed(arg__1); }
inline void py_q_mouseReleased(QGraphicsSceneMouseEvent*  arg__1) { Editor::mouseReleased(arg__1); }
inline void py_q_mouseWheelMoved(QGraphicsSceneWheelEvent*  arg__1) { Editor::mouseWheelMoved(arg__1); }
inline void py_q_newPanelDefaults() { Editor::newPanelDefaults(); }
inline void py_q_paint(QGraphicsScene*  g) { Editor::paint(g); }
inline void py_q_paintTargetPanel(QGraphicsScene*  g) { Editor::paintTargetPanel(g); }
inline void py_q_putItem(Positionable*  l) { Editor::putItem(l); }
inline void py_q_redrawPanel() { Editor::redrawPanel(); }
inline void py_q_repaint() { Editor::repaint(); }
inline void py_q_setAllEditable(bool  state) { Editor::setAllEditable(state); }
inline void py_q_setAllPositionable(bool  state) { Editor::setAllPositionable(state); }
inline void py_q_setNextLocation(Positionable*  arg__1) { Editor::setNextLocation(arg__1); }
inline void py_q_setRemoveMenu(Positionable*  p, QMenu*  popup) { Editor::setRemoveMenu(p, popup); }
inline void py_q_setScroll(int  state) { Editor::setScroll(state); }
inline void py_q_setSelectionsRotation(int  k, Positionable*  p) { Editor::setSelectionsRotation(k, p); }
inline void py_q_setSelectionsScale(double  s, Positionable*  p) { Editor::setSelectionsScale(s, p); }
inline void py_q_setTitle() { Editor::setTitle(); }
inline void py_q_setUseGlobalFlag(bool  set) { Editor::setUseGlobalFlag(set); }
inline void py_q_showPopUp(Positionable*  arg__1, QMouseEvent*  arg__2) { Editor::showPopUp(arg__1, arg__2); }
inline void py_q_targetWindowClosing(bool  save) { Editor::targetWindowClosing(save); }
inline void py_q_targetWindowClosingEvent(QCloseEvent*  e) { Editor::targetWindowClosingEvent(e); }
inline bool  py_q_useGlobalFlag() { return Editor::useGlobalFlag(); }
inline void py_q_vetoableChange(PropertyChangeEvent*  evt) { Editor::vetoableChange(evt); }
};

class PythonQtWrapper_Editor : public QObject
{ Q_OBJECT
public:
public slots:
Editor* new_Editor(QString  name, QWidget*  parent);
Editor* new_Editor(QString  name, bool  saveSize, bool  savePosition, QWidget*  parent = 0);
Editor* new_Editor(QWidget*  parent = 0);
void delete_Editor(Editor* obj) { delete obj; } 
   PositionableLabel*  addLabel(Editor* theWrappedObject, QString  text);
   void addPropertyChangeListener(Editor* theWrappedObject, PropertyChangeListener*  listener);
   void addPropertyChangeListener(Editor* theWrappedObject, QString  name, PropertyChangeListener*  listener);
   void addRpsReporter(Editor* theWrappedObject);
   void addToTarget(Editor* theWrappedObject, Positionable*  l);
   bool  allControlling(Editor* theWrappedObject);
   bool  allPositionable(Editor* theWrappedObject);
   Editor*  changeView(Editor* theWrappedObject, QString  className);
   void clearBackgroundColor(Editor* theWrappedObject);
   bool  deletePanel(Editor* theWrappedObject);
   bool  py_q_deletePanel(Editor* theWrappedObject){  return (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_deletePanel());}
   void displayLevelChange(Editor* theWrappedObject, Positionable*  l);
   void py_q_dispose(Editor* theWrappedObject){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_dispose());}
   void dispose(Editor* theWrappedObject, bool  clear);
   void disposeLoadData(Editor* theWrappedObject);
   void dockSelections(Editor* theWrappedObject, Positionable*  p);
   void drawSelectRect(Editor* theWrappedObject, int  x, int  y);
   int  getAnchorX(Editor* theWrappedObject);
   int  getAnchorY(Editor* theWrappedObject);
   QColor  getBackgroundColor(Editor* theWrappedObject);
   QList<Positionable* >  getContents(Editor* theWrappedObject);
   Editor*  static_Editor_getEditor(QString  name);
   QVector<Editor* >  static_Editor_getEditors();
   QList<Editor* >  static_Editor_getEditors(QString  type);
   bool  getFlag(Editor* theWrappedObject, int  whichOption, bool  localFlag);
   JFrameItem*  getIconFrame(Editor* theWrappedObject, QString  name);
   int  getItemX(Editor* theWrappedObject, Positionable*  p, int  deltaX);
   int  getItemY(Editor* theWrappedObject, Positionable*  p, int  deltaY);
   QString  getName(Editor* theWrappedObject);
   double  getPaintScale(Editor* theWrappedObject);
   const QScrollArea*  getPanelScrollPane(Editor* theWrappedObject);
   QString  getScrollable(Editor* theWrappedObject);
   QRectF  getSelectRect(Editor* theWrappedObject);
   QList<Positionable* >*  getSelectedItems(Editor* theWrappedObject, QGraphicsSceneMouseEvent*  event);
   QList<Positionable* >*  getSelectedItems(Editor* theWrappedObject, QPointF  pt);
   JFrame*  getTargetFrame(Editor* theWrappedObject);
   EditScene*  getTargetPanel(Editor* theWrappedObject);
   QSize  getTargetPanelSize(Editor* theWrappedObject);
   QString  py_q_getTitle(Editor* theWrappedObject){  return (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_getTitle());}
   double  getZoomRatio(Editor* theWrappedObject);
   void init(Editor* theWrappedObject, QString  name);
   void py_q_init(Editor* theWrappedObject, QString  name){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_init(name));}
   void initView(Editor* theWrappedObject);
   void py_q_initView(Editor* theWrappedObject){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_initView());}
   bool  isEditable(Editor* theWrappedObject);
   bool  isPanelMenuVisible(Editor* theWrappedObject);
   void loadFailed(Editor* theWrappedObject);
   bool  loadOK(Editor* theWrappedObject);
   void makeSelectionGroup(Editor* theWrappedObject, QGraphicsSceneMouseEvent*  event);
   void modifySelectionGroup(Editor* theWrappedObject, Positionable*  selection, QGraphicsSceneMouseEvent*  event);
   void mouseClicked(Editor* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1);
   void py_q_mouseClicked(Editor* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_mouseClicked(arg__1));}
   void mouseDragged(Editor* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1);
   void py_q_mouseDragged(Editor* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_mouseDragged(arg__1));}
   void mouseEntered(Editor* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1);
   void py_q_mouseEntered(Editor* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_mouseEntered(arg__1));}
   void mouseExited(Editor* theWrappedObject, QGraphicsSceneMouseEvent*  event);
   void py_q_mouseExited(Editor* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_mouseExited(event));}
   void mouseMoved(Editor* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1);
   void py_q_mouseMoved(Editor* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_mouseMoved(arg__1));}
   void mousePressed(Editor* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1);
   void py_q_mousePressed(Editor* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_mousePressed(arg__1));}
   void mouseReleased(Editor* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1);
   void py_q_mouseReleased(Editor* theWrappedObject, QGraphicsSceneMouseEvent*  arg__1){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_mouseReleased(arg__1));}
   void mouseWheelMoved(Editor* theWrappedObject, QGraphicsSceneWheelEvent*  arg__1);
   void py_q_mouseWheelMoved(Editor* theWrappedObject, QGraphicsSceneWheelEvent*  arg__1){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_mouseWheelMoved(arg__1));}
   void moveItem(Editor* theWrappedObject, Positionable*  p, int  deltaX, int  deltaY);
   void newPanelDefaults(Editor* theWrappedObject);
   void py_q_newPanelDefaults(Editor* theWrappedObject){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_newPanelDefaults());}
   void paint(Editor* theWrappedObject, QGraphicsScene*  g);
   void py_q_paint(Editor* theWrappedObject, QGraphicsScene*  g){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_paint(g));}
   void py_q_paintTargetPanel(Editor* theWrappedObject, QGraphicsScene*  g){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_paintTargetPanel(g));}
   void putItem(Editor* theWrappedObject, Positionable*  l);
   void py_q_putItem(Editor* theWrappedObject, Positionable*  l){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_putItem(l));}
   void redrawPanel(Editor* theWrappedObject);
   void py_q_redrawPanel(Editor* theWrappedObject){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_redrawPanel());}
   bool  removeFromContents(Editor* theWrappedObject, Positionable*  l);
   void removeFromTarget(Editor* theWrappedObject, Positionable*  l);
   void removePropertyChangeListener(Editor* theWrappedObject, PropertyChangeListener*  listener);
   void removePropertyChangeListener(Editor* theWrappedObject, QString  name, PropertyChangeListener*  listener);
   void removeSelections(Editor* theWrappedObject, Positionable*  p);
   void py_q_repaint(Editor* theWrappedObject){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_repaint());}
   void setAllEditable(Editor* theWrappedObject, bool  state);
   void py_q_setAllEditable(Editor* theWrappedObject, bool  state){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_setAllEditable(state));}
   void py_q_setAllPositionable(Editor* theWrappedObject, bool  state){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_setAllPositionable(state));}
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
   void py_q_setNextLocation(Editor* theWrappedObject, Positionable*  arg__1){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_setNextLocation(arg__1));}
   void setPaintScale(Editor* theWrappedObject, double  newScale);
   void setPanelMenu(Editor* theWrappedObject, bool  state);
   void setPositionableMenu(Editor* theWrappedObject, Positionable*  p, QMenu*  popup);
   void setRemoveMenu(Editor* theWrappedObject, Positionable*  p, QMenu*  popup);
   void py_q_setRemoveMenu(Editor* theWrappedObject, Positionable*  p, QMenu*  popup){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_setRemoveMenu(p, popup));}
   void setScroll(Editor* theWrappedObject, QString  strState);
   void setScroll(Editor* theWrappedObject, int  state);
   void py_q_setScroll(Editor* theWrappedObject, int  state){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_setScroll(state));}
   void setSelectGroupColor(Editor* theWrappedObject, QColor  color);
   void setSelectRectColor(Editor* theWrappedObject, QColor  color);
   void setSelectRectStroke(Editor* theWrappedObject, Qt::PenStyle  stroke);
   void setSelectionsDockingLocation(Editor* theWrappedObject, Positionable*  p);
   void setSelectionsHidden(Editor* theWrappedObject, bool  enabled, Positionable*  p);
   void setSelectionsRotation(Editor* theWrappedObject, int  k, Positionable*  p);
   void py_q_setSelectionsRotation(Editor* theWrappedObject, int  k, Positionable*  p){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_setSelectionsRotation(k, p));}
   void setSelectionsScale(Editor* theWrappedObject, double  s, Positionable*  p);
   void py_q_setSelectionsScale(Editor* theWrappedObject, double  s, Positionable*  p){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_setSelectionsScale(s, p));}
   bool  setShowAlignmentMenu(Editor* theWrappedObject, Positionable*  p, QMenu*  popup);
   void setShowCoordinates(Editor* theWrappedObject, bool  state);
   bool  setShowCoordinatesMenu(Editor* theWrappedObject, Positionable*  p, QMenu*  popup);
   void setShowToolTipMenu(Editor* theWrappedObject, Positionable*  p, QMenu*  popup);
   void setTargetPanel(Editor* theWrappedObject, EditScene*  targetPanel, JmriJFrame*  frame);
   void setTargetPanelSize(Editor* theWrappedObject, int  w, int  h);
   bool  setTextAttributes(Editor* theWrappedObject, Positionable*  p, QMenu*  popup);
   void setTitle(Editor* theWrappedObject);
   void py_q_setTitle(Editor* theWrappedObject){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_setTitle());}
   void setToolTip(Editor* theWrappedObject, QString  tt);
   PositionableLabel*  setUpBackground(Editor* theWrappedObject, QString  name);
   void setUseGlobalFlag(Editor* theWrappedObject, bool  set);
   void py_q_setUseGlobalFlag(Editor* theWrappedObject, bool  set){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_setUseGlobalFlag(set));}
   bool  showAlignPopup(Editor* theWrappedObject, Positionable*  p);
   bool  showCoordinates(Editor* theWrappedObject);
   bool  showHidden(Editor* theWrappedObject);
   void showPopUp(Editor* theWrappedObject, Positionable*  arg__1, QGraphicsSceneMouseEvent*  arg__2);
   void py_q_showPopUp(Editor* theWrappedObject, Positionable*  arg__1, QMouseEvent*  arg__2){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_showPopUp(arg__1, arg__2));}
   bool  showToolTip(Editor* theWrappedObject);
   void showToolTip(Editor* theWrappedObject, Positionable*  selection, QGraphicsSceneMouseEvent*  event);
   void targetWindowClosing(Editor* theWrappedObject, bool  save);
   void py_q_targetWindowClosing(Editor* theWrappedObject, bool  save){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_targetWindowClosing(save));}
   void targetWindowClosingEvent(Editor* theWrappedObject, QCloseEvent*  e);
   void py_q_targetWindowClosingEvent(Editor* theWrappedObject, QCloseEvent*  e){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_targetWindowClosingEvent(e));}
   bool  useGlobalFlag(Editor* theWrappedObject);
   bool  py_q_useGlobalFlag(Editor* theWrappedObject){  return (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_useGlobalFlag());}
   void py_q_vetoableChange(Editor* theWrappedObject, PropertyChangeEvent*  evt){  (((PythonQtPublicPromoter_Editor*)theWrappedObject)->py_q_vetoableChange(evt));}
void py_set_frameLocationX(Editor* theWrappedObject, int  frameLocationX){ theWrappedObject->frameLocationX = frameLocationX; }
int  py_get_frameLocationX(Editor* theWrappedObject){ return theWrappedObject->frameLocationX; }
void py_set_frameLocationY(Editor* theWrappedObject, int  frameLocationY){ theWrappedObject->frameLocationY = frameLocationY; }
int  py_get_frameLocationY(Editor* theWrappedObject){ return theWrappedObject->frameLocationY; }
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





class PythonQtShell_InstanceManager : public InstanceManager
{
public:
    PythonQtShell_InstanceManager(QObject*  parent = 0):InstanceManager(parent),_wrapper(NULL) {}

   ~PythonQtShell_InstanceManager();

virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_InstanceManager : public InstanceManager
{ public:
inline void promoted_notifyPropertyChangeListener(QString  property, QVariant  oldValue, QVariant  newValue) { this->notifyPropertyChangeListener(property, oldValue, newValue); }
};

class PythonQtWrapper_InstanceManager : public QObject
{ Q_OBJECT
public:
public slots:
InstanceManager* new_InstanceManager(QObject*  parent = 0);
void delete_InstanceManager(InstanceManager* obj) { delete obj; } 
   AudioManager*  static_InstanceManager_AudioManagerInstance();
   void static_InstanceManager_addPropertyChangeListener(PropertyChangeListener*  l);
   void static_InstanceManager_addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  l);
   void clear(InstanceManager* theWrappedObject, QString  type);
   void clearAll(InstanceManager* theWrappedObject);
   bool  static_InstanceManager_containsDefault(QString  type);
   QString  static_InstanceManager_contentsToString();
   void static_InstanceManager_deregister(QObject*  item, QString  type);
   InstanceManager*  static_InstanceManager_getDefault();
   QObject*  static_InstanceManager_getDefault(QString  type);
   QString  static_InstanceManager_getDefaultsPropertyName(QString  clazz);
   QList<QObject* >*  getInstances(InstanceManager* theWrappedObject, QString  type);
   QList<QObject* >*  static_InstanceManager_getList(QString  type);
   QString  static_InstanceManager_getListPropertyName(QString  clazz);
   QObject*  static_InstanceManager_getNullableDefault(QString  type);
   QObject*  static_InstanceManager_getOptionalDefault(QString  type);
   bool  static_InstanceManager_isInitialized(QString  type);
   MemoryManager*  static_InstanceManager_memoryManagerInstance();
   void notifyPropertyChangeListener(InstanceManager* theWrappedObject, QString  property, QVariant  oldValue, QVariant  newValue);
   void remove(InstanceManager* theWrappedObject, QObject*  item, QString  type);
   void static_InstanceManager_removePropertyChangeListener(PropertyChangeListener*  l);
   void static_InstanceManager_removePropertyChangeListener(QString  propertyName, PropertyChangeListener*  l);
   void static_InstanceManager_reset(QString  type);
   QObject*  static_InstanceManager_setDefault(QString  type, QObject*  val);
   void static_InstanceManager_setLightManager(LightManager*  p);
   void static_InstanceManager_setReporterManager(ReporterManager*  p);
   void static_InstanceManager_setSensorManager(SensorManager*  p);
   void static_InstanceManager_setThrottleManager(ThrottleManager*  p);
   void static_InstanceManager_setTurnoutManager(TurnoutManager*  p);
   void static_InstanceManager_store(QObject*  item, QString  type);
   ThrottleManager*  static_InstanceManager_throttleManagerInstance();
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
virtual QString  getTitle();
virtual bool  hasHeightForWidth() const;
virtual int  heightForWidth(int  arg__1) const;
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
virtual void moveEvent(QMoveEvent*  event);
virtual bool  nativeEvent(const QByteArray&  eventType, void*  message, long*  result);
virtual void pack();
virtual QPaintEngine*  paintEngine() const;
virtual void paintEvent(QPaintEvent*  event);
virtual QPaintDevice*  redirected(QPoint*  offset) const;
virtual void resizeEvent(QResizeEvent*  event);
virtual void setEnabled(bool  b);
virtual void setTitle(QString  _title);
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

class PythonQtPublicPromoter_JFrame : public JFrame
{ public:
inline void promoted_frameInit() { this->frameInit(); }
inline bool  py_q_closedNormally() { return JFrame::closedNormally(); }
inline void py_q_componentMoved(QMoveEvent*  arg__1) { JFrame::componentMoved(arg__1); }
inline void py_q_componentResized(QResizeEvent*  arg__1) { JFrame::componentResized(arg__1); }
inline void py_q_dispose() { JFrame::dispose(); }
inline QString  py_q_getTitle() { return JFrame::getTitle(); }
inline void py_q_languageChange() { JFrame::languageChange(); }
inline void py_q_pack() { JFrame::pack(); }
inline void py_q_setEnabled(bool  b) { JFrame::setEnabled(b); }
inline void py_q_setTitle(QString  _title) { JFrame::setTitle(_title); }
inline void py_q_setVisible(bool  visible) { JFrame::setVisible(visible); }
};

class PythonQtWrapper_JFrame : public QObject
{ Q_OBJECT
public:
public slots:
JFrame* new_JFrame(QString  _title, QWidget*  parent = nullptr);
JFrame* new_JFrame(QWidget*  parent = nullptr);
JFrame* new_JFrame(const JFrame&  arg__1);
void delete_JFrame(JFrame* obj) { delete obj; } 
   void addWindowListener(JFrame* theWrappedObject, WindowListener*  l);
   bool  closedNormally(JFrame* theWrappedObject);
   bool  py_q_closedNormally(JFrame* theWrappedObject){  return (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_closedNormally());}
   void componentMoved(JFrame* theWrappedObject, QMoveEvent*  arg__1);
   void py_q_componentMoved(JFrame* theWrappedObject, QMoveEvent*  arg__1){  (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_componentMoved(arg__1));}
   void componentResized(JFrame* theWrappedObject, QResizeEvent*  arg__1);
   void py_q_componentResized(JFrame* theWrappedObject, QResizeEvent*  arg__1){  (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_componentResized(arg__1));}
   void dispose(JFrame* theWrappedObject);
   void py_q_dispose(JFrame* theWrappedObject){  (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_dispose());}
   void frameInit(JFrame* theWrappedObject);
   QColor  getBackground(JFrame* theWrappedObject);
   QFont  getFont(JFrame* theWrappedObject);
   QColor  getForeground(JFrame* theWrappedObject);
   QPoint  getLocation(JFrame* theWrappedObject);
   QPoint  getLocationOnScreen(JFrame* theWrappedObject);
   QSize  getMaximumSize(JFrame* theWrappedObject);
   QSize  getPreferredSize(JFrame* theWrappedObject);
   QString  getTitle(JFrame* theWrappedObject);
   QString  py_q_getTitle(JFrame* theWrappedObject){  return (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_getTitle());}
   QWidget*  getTopLevelAncestor(JFrame* theWrappedObject);
   QVector<WindowListener* >  getWindowListeners(JFrame* theWrappedObject);
   bool  isOpaque(JFrame* theWrappedObject);
   QObject*  jself(JFrame* theWrappedObject);
   void languageChange(JFrame* theWrappedObject);
   void py_q_languageChange(JFrame* theWrappedObject){  (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_languageChange());}
   void pack(JFrame* theWrappedObject);
   void py_q_pack(JFrame* theWrappedObject){  (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_pack());}
   void reSizeToFitOnScreen(JFrame* theWrappedObject);
   void removeAll(JFrame* theWrappedObject);
   void removeWindowListener(JFrame* theWrappedObject, WindowListener*  l);
   void setAlwaysOnTop(JFrame* theWrappedObject, bool  checked);
   void setBackground(JFrame* theWrappedObject, QColor  arg__1);
   void setBounds(JFrame* theWrappedObject, QRect  r);
   void setDefaultCloseOperation(JFrame* theWrappedObject, int  operation);
   void py_q_setEnabled(JFrame* theWrappedObject, bool  b){  (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_setEnabled(b));}
   void setFont(JFrame* theWrappedObject, QFont  arg__1);
   void setLocation(JFrame* theWrappedObject, QPoint  p);
   void setLocation(JFrame* theWrappedObject, int  x, int  y);
   void setMenuBar(JFrame* theWrappedObject, QMenuBar*  menubar);
   void setOpaque(JFrame* theWrappedObject, bool  arg__1);
   void setTitle(JFrame* theWrappedObject, QString  _title);
   void py_q_setTitle(JFrame* theWrappedObject, QString  _title){  (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_setTitle(_title));}
   void py_q_setVisible(JFrame* theWrappedObject, bool  visible){  (((PythonQtPublicPromoter_JFrame*)theWrappedObject)->py_q_setVisible(visible));}
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
virtual QPointF  getLocation();
virtual bool  hasHeightForWidth() const;
virtual int  heightForWidth(int  arg__1) const;
virtual void hideEvent(QHideEvent*  event);
virtual void initPainter(QPainter*  painter) const;
virtual void inputMethodEvent(QInputMethodEvent*  arg__1);
virtual QVariant  inputMethodQuery(Qt::InputMethodQuery  arg__1) const;
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
virtual void setEnabled(bool  b);
virtual void setName(QString  name);
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
inline QPointF  py_q_getLocation() { return JLabel::getLocation(); }
inline void py_q_setEnabled(bool  b) { JLabel::setEnabled(b); }
inline void py_q_setName(QString  name) { JLabel::setName(name); }
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
   int  getBaseline(JLabel* theWrappedObject, int  w, int  h);
   int  getDisplayedMnemonic(JLabel* theWrappedObject);
   QFont  getFont(JLabel* theWrappedObject);
   QFontMetrics  getFontMetrics(JLabel* theWrappedObject);
   QColor  getForeground(JLabel* theWrappedObject);
   int  getHorizontalAlignment(JLabel* theWrappedObject);
   int  getHorizontalTextPosition(JLabel* theWrappedObject);
   QWidget*  getLabelFor(JLabel* theWrappedObject);
   QPointF  getLocation(JLabel* theWrappedObject);
   QPointF  py_q_getLocation(JLabel* theWrappedObject){  return (((PythonQtPublicPromoter_JLabel*)theWrappedObject)->py_q_getLocation());}
   QString  getName(JLabel* theWrappedObject);
   QString  getText(JLabel* theWrappedObject);
   int  getVerticalAlignment(JLabel* theWrappedObject);
   bool  isOpaque(JLabel* theWrappedObject);
   QObject*  jself(JLabel* theWrappedObject);
   void setAlignmentX(JLabel* theWrappedObject, float  alignmentX);
   void setBackground(JLabel* theWrappedObject, QColor  arg__1);
   void setBounds(JLabel* theWrappedObject, int  x, int  y, int  w, int  h);
   void setDisplayedMnemonic(JLabel* theWrappedObject, char  aChar);
   void setDisplayedMnemonic(JLabel* theWrappedObject, int  key);
   void py_q_setEnabled(JLabel* theWrappedObject, bool  b){  (((PythonQtPublicPromoter_JLabel*)theWrappedObject)->py_q_setEnabled(b));}
   void setFont(JLabel* theWrappedObject, QFont  arg__1);
   void setForeground(JLabel* theWrappedObject, QColor  arg__1);
   void setHorizontalAlignment(JLabel* theWrappedObject, int  alignment);
   void setHorizontalTextPosition(JLabel* theWrappedObject, int  textPosition);
   void setLabelFor(JLabel* theWrappedObject, QWidget*  c);
   void setLocation(JLabel* theWrappedObject, double  x, double  y);
   void setLocation(JLabel* theWrappedObject, int  x, int  y);
   void setName(JLabel* theWrappedObject, QString  name);
   void py_q_setName(JLabel* theWrappedObject, QString  name){  (((PythonQtPublicPromoter_JLabel*)theWrappedObject)->py_q_setName(name));}
   void setOpaque(JLabel* theWrappedObject, bool  arg__1);
   void setSize(JLabel* theWrappedObject, double  x, double  y);
   void setText(JLabel* theWrappedObject, QString  text);
   void setVerticalAlignment(JLabel* theWrappedObject, int  alignment);
void py_set_pcs(JLabel* theWrappedObject, PropertyChangeSupport*  pcs){ theWrappedObject->pcs = pcs; }
PropertyChangeSupport*  py_get_pcs(JLabel* theWrappedObject){ return theWrappedObject->pcs; }
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





class PythonQtShell_JTextArea : public JTextArea
{
public:
    PythonQtShell_JTextArea(QString  text, QWidget*  parent = 0):JTextArea(text, parent),_wrapper(NULL) {}
    PythonQtShell_JTextArea(QString  text, int  rows, int  columns, QWidget*  parent = 0):JTextArea(text, rows, columns, parent),_wrapper(NULL) {}
    PythonQtShell_JTextArea(QWidget*  parent = 0):JTextArea(parent),_wrapper(NULL) {}
    PythonQtShell_JTextArea(int  rows, int  columns, QWidget*  parent = 0):JTextArea(rows, columns, parent),_wrapper(NULL) {}

   ~PythonQtShell_JTextArea();

virtual void actionEvent(QActionEvent*  event);
virtual bool  canInsertFromMimeData(const QMimeData*  source) const;
virtual void changeEvent(QEvent*  e);
virtual void childEvent(QChildEvent*  event);
virtual void closeEvent(QCloseEvent*  event);
virtual void contextMenuEvent(QContextMenuEvent*  e);
virtual QMimeData*  createMimeDataFromSelection() const;
virtual void customEvent(QEvent*  event);
virtual int  devType() const;
virtual void doSetTextCursor(const QTextCursor&  cursor);
virtual void dragEnterEvent(QDragEnterEvent*  e);
virtual void dragLeaveEvent(QDragLeaveEvent*  e);
virtual void dragMoveEvent(QDragMoveEvent*  e);
virtual void dropEvent(QDropEvent*  e);
virtual void enterEvent(QEvent*  event);
virtual bool  event(QEvent*  e);
virtual bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
virtual void focusInEvent(QFocusEvent*  e);
virtual bool  focusNextPrevChild(bool  next);
virtual void focusOutEvent(QFocusEvent*  e);
virtual bool  hasHeightForWidth() const;
virtual int  heightForWidth(int  arg__1) const;
virtual void hideEvent(QHideEvent*  event);
virtual void initPainter(QPainter*  painter) const;
virtual void inputMethodEvent(QInputMethodEvent*  arg__1);
virtual QVariant  inputMethodQuery(Qt::InputMethodQuery  property) const;
virtual void insertFromMimeData(const QMimeData*  source);
virtual void keyPressEvent(QKeyEvent*  e);
virtual void keyReleaseEvent(QKeyEvent*  e);
virtual void leaveEvent(QEvent*  event);
virtual QVariant  loadResource(int  type, const QUrl&  name);
virtual int  metric(QPaintDevice::PaintDeviceMetric  arg__1) const;
virtual QSize  minimumSizeHint() const;
virtual void mouseDoubleClickEvent(QMouseEvent*  e);
virtual void mouseMoveEvent(QMouseEvent*  e);
virtual void mousePressEvent(QMouseEvent*  e);
virtual void mouseReleaseEvent(QMouseEvent*  e);
virtual void moveEvent(QMoveEvent*  event);
virtual bool  nativeEvent(const QByteArray&  eventType, void*  message, long*  result);
virtual QPaintEngine*  paintEngine() const;
virtual void paintEvent(QPaintEvent*  e);
virtual QPaintDevice*  redirected(QPoint*  offset) const;
virtual void resizeEvent(QResizeEvent*  e);
virtual void scrollContentsBy(int  dx, int  dy);
virtual void setVisible(bool  visible);
virtual void setupViewport(QWidget*  viewport);
virtual QPainter*  sharedPainter() const;
virtual void showEvent(QShowEvent*  arg__1);
virtual QSize  sizeHint() const;
virtual void tabletEvent(QTabletEvent*  event);
virtual void timerEvent(QTimerEvent*  e);
virtual bool  viewportEvent(QEvent*  arg__1);
virtual QSize  viewportSizeHint() const;
virtual void wheelEvent(QWheelEvent*  e);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_JTextArea : public JTextArea
{ public:
inline void promoted_focusInEvent(QFocusEvent*  e) { this->focusInEvent(e); }
inline void promoted_focusOutEvent(QFocusEvent*  e) { this->focusOutEvent(e); }
inline int  promoted_getColumnWidth() { return this->getColumnWidth(); }
inline int  promoted_getRowHeight() { return this->getRowHeight(); }
inline void py_q_focusInEvent(QFocusEvent*  e) { JTextArea::focusInEvent(e); }
inline void py_q_focusOutEvent(QFocusEvent*  e) { JTextArea::focusOutEvent(e); }
};

class PythonQtWrapper_JTextArea : public QObject
{ Q_OBJECT
public:
public slots:
JTextArea* new_JTextArea(QString  text, QWidget*  parent = 0);
JTextArea* new_JTextArea(QString  text, int  rows, int  columns, QWidget*  parent = 0);
JTextArea* new_JTextArea(QWidget*  parent = 0);
JTextArea* new_JTextArea(int  rows, int  columns, QWidget*  parent = 0);
void delete_JTextArea(JTextArea* obj) { delete obj; } 
   void append(JTextArea* theWrappedObject, QString  str);
   void py_q_focusInEvent(JTextArea* theWrappedObject, QFocusEvent*  e){  (((PythonQtPublicPromoter_JTextArea*)theWrappedObject)->py_q_focusInEvent(e));}
   void py_q_focusOutEvent(JTextArea* theWrappedObject, QFocusEvent*  e){  (((PythonQtPublicPromoter_JTextArea*)theWrappedObject)->py_q_focusOutEvent(e));}
   int  getColumnWidth(JTextArea* theWrappedObject);
   int  getColumns(JTextArea* theWrappedObject);
   bool  getLineWrap(JTextArea* theWrappedObject);
   int  getRowHeight(JTextArea* theWrappedObject);
   int  getRows(JTextArea* theWrappedObject);
   bool  getWrapStyleWord(JTextArea* theWrappedObject);
   void setColumns(JTextArea* theWrappedObject, int  columns);
   void setEditable(JTextArea* theWrappedObject, bool  arg__1);
   void setLineWrap(JTextArea* theWrappedObject, bool  arg__1);
   void setOpaque(JTextArea* theWrappedObject, bool  arg__1);
   void setRows(JTextArea* theWrappedObject, int  rows);
   void setTabSize(JTextArea* theWrappedObject, int  width);
   void setWrapStyleWord(JTextArea* theWrappedObject, bool  arg__1);
void py_set_text(JTextArea* theWrappedObject, QString  text){ theWrappedObject->text = text; }
QString  py_get_text(JTextArea* theWrappedObject){ return theWrappedObject->text; }
};





class PythonQtShell_JmriJFrame : public JmriJFrame
{
public:
    PythonQtShell_JmriJFrame(QString  name, QWidget*  parent = nullptr):JmriJFrame(name, parent),_wrapper(NULL) {}
    PythonQtShell_JmriJFrame(QString  name, bool  saveSize, bool  savePosition, QWidget*  parent = nullptr):JmriJFrame(name, saveSize, savePosition, parent),_wrapper(NULL) {}
    PythonQtShell_JmriJFrame(QWidget*  parent = nullptr):JmriJFrame(parent),_wrapper(NULL) {}
    PythonQtShell_JmriJFrame(bool  saveSize, bool  savePosition, QWidget*  parent = nullptr):JmriJFrame(saveSize, savePosition, parent),_wrapper(NULL) {}

   ~PythonQtShell_JmriJFrame();

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

class PythonQtPublicPromoter_JmriJFrame : public JmriJFrame
{ public:
inline void promoted_handleModified() { this->handleModified(); }
inline void promoted_reSizeToFitOnScreen() { this->reSizeToFitOnScreen(); }
inline void promoted_setShutDownTask() { this->setShutDownTask(); }
inline void promoted_storeValues() { this->storeValues(); }
inline void py_q_addHelpMenu(QString  ref, bool  direct) { JmriJFrame::addHelpMenu(ref, direct); }
inline void py_q_componentMoved(QMoveEvent*  e) { JmriJFrame::componentMoved(e); }
inline void py_q_componentResized(QResizeEvent*  e) { JmriJFrame::componentResized(e); }
inline void py_q_dispose() { JmriJFrame::dispose(); }
inline bool  py_q_eventFilter(QObject*  target, QEvent*  event) { return JmriJFrame::eventFilter(target, event); }
inline QString  py_q_getClassName() { return this->getClassName(); }
inline QVariant  py_q_getProperty(QString  key) { return JmriJFrame::getProperty(key); }
inline QString  py_q_getTitle() { return JmriJFrame::getTitle(); }
inline void py_q_handleModified() { JmriJFrame::handleModified(); }
inline void py_q_initComponents() { JmriJFrame::initComponents(); }
inline void py_q_moveEvent(QMoveEvent*  e) { JmriJFrame::moveEvent(e); }
inline void py_q_resizeEvent(QResizeEvent*  e) { JmriJFrame::resizeEvent(e); }
inline void py_q_setTitle(QString  _title) { JmriJFrame::setTitle(_title); }
inline void py_q_storeValues() { JmriJFrame::storeValues(); }
inline void py_q_windowClosing(QCloseEvent*  e) { JmriJFrame::windowClosing(e); }
};

class PythonQtWrapper_JmriJFrame : public QObject
{ Q_OBJECT
public:
public slots:
JmriJFrame* new_JmriJFrame(QString  name, QWidget*  parent = nullptr);
JmriJFrame* new_JmriJFrame(QString  name, bool  saveSize, bool  savePosition, QWidget*  parent = nullptr);
JmriJFrame* new_JmriJFrame(QWidget*  parent = nullptr);
JmriJFrame* new_JmriJFrame(bool  saveSize, bool  savePosition, QWidget*  parent = nullptr);
void delete_JmriJFrame(JmriJFrame* obj) { delete obj; } 
   void addHelpMenu(JmriJFrame* theWrappedObject, QString  ref, bool  direct);
   void py_q_addHelpMenu(JmriJFrame* theWrappedObject, QString  ref, bool  direct){  (((PythonQtPublicPromoter_JmriJFrame*)theWrappedObject)->py_q_addHelpMenu(ref, direct));}
   void addNotify(JmriJFrame* theWrappedObject);
   void py_q_componentMoved(JmriJFrame* theWrappedObject, QMoveEvent*  e){  (((PythonQtPublicPromoter_JmriJFrame*)theWrappedObject)->py_q_componentMoved(e));}
   void py_q_componentResized(JmriJFrame* theWrappedObject, QResizeEvent*  e){  (((PythonQtPublicPromoter_JmriJFrame*)theWrappedObject)->py_q_componentResized(e));}
   void py_q_dispose(JmriJFrame* theWrappedObject){  (((PythonQtPublicPromoter_JmriJFrame*)theWrappedObject)->py_q_dispose());}
   bool  py_q_eventFilter(JmriJFrame* theWrappedObject, QObject*  target, QEvent*  event){  return (((PythonQtPublicPromoter_JmriJFrame*)theWrappedObject)->py_q_eventFilter(target, event));}
   void generateWindowRef(JmriJFrame* theWrappedObject);
   bool  getAllowInFrameServlet(JmriJFrame* theWrappedObject);
   QString  getClassName(JmriJFrame* theWrappedObject);
   QString  py_q_getClassName(JmriJFrame* theWrappedObject){  return (((PythonQtPublicPromoter_JmriJFrame*)theWrappedObject)->py_q_getClassName());}
   bool  getEscapeKeyClosesWindow(JmriJFrame* theWrappedObject);
   JmriJFrame*  static_JmriJFrame_getFrame(QString  name);
   QList<JmriJFrame* >*  static_JmriJFrame_getFrameList();
   QWidget*  getGlassPane(JmriJFrame* theWrappedObject);
   bool  getModifiedFlag(JmriJFrame* theWrappedObject);
   QString  getName(JmriJFrame* theWrappedObject);
   QVariant  getProperty(JmriJFrame* theWrappedObject, QString  key);
   QVariant  py_q_getProperty(JmriJFrame* theWrappedObject, QString  key){  return (((PythonQtPublicPromoter_JmriJFrame*)theWrappedObject)->py_q_getProperty(key));}
   bool  getSavePosition(JmriJFrame* theWrappedObject);
   bool  getSaveSize(JmriJFrame* theWrappedObject);
   QString  py_q_getTitle(JmriJFrame* theWrappedObject){  return (((PythonQtPublicPromoter_JmriJFrame*)theWrappedObject)->py_q_getTitle());}
   QString  getWindowFrameRef(JmriJFrame* theWrappedObject);
   void handleModified(JmriJFrame* theWrappedObject);
   void py_q_handleModified(JmriJFrame* theWrappedObject){  (((PythonQtPublicPromoter_JmriJFrame*)theWrappedObject)->py_q_handleModified());}
   void init(JmriJFrame* theWrappedObject, bool  saveSize, bool  savePosition);
   void initComponents(JmriJFrame* theWrappedObject);
   void py_q_initComponents(JmriJFrame* theWrappedObject){  (((PythonQtPublicPromoter_JmriJFrame*)theWrappedObject)->py_q_initComponents());}
   void makePrivateWindow(JmriJFrame* theWrappedObject);
   void markWindowModified(JmriJFrame* theWrappedObject, bool  yes);
   void py_q_moveEvent(JmriJFrame* theWrappedObject, QMoveEvent*  e){  (((PythonQtPublicPromoter_JmriJFrame*)theWrappedObject)->py_q_moveEvent(e));}
   void reSizeToFitOnScreen(JmriJFrame* theWrappedObject);
   void py_q_resizeEvent(JmriJFrame* theWrappedObject, QResizeEvent*  e){  (((PythonQtPublicPromoter_JmriJFrame*)theWrappedObject)->py_q_resizeEvent(e));}
   void setAllowInFrameServlet(JmriJFrame* theWrappedObject, bool  allow);
   void setAlwaysOnTop(JmriJFrame* theWrappedObject, bool  checked);
   void setContentPane(JmriJFrame* theWrappedObject, QWidget*  arg__1);
   void setEscapeKeyClosesWindow(JmriJFrame* theWrappedObject, bool  closesWindow);
   void setFrameLocation(JmriJFrame* theWrappedObject);
   void setFrameRef(JmriJFrame* theWrappedObject, QString  windowFrameRef);
   void setGlassPane(JmriJFrame* theWrappedObject, QWidget*  glassPane);
   void setLocation(JmriJFrame* theWrappedObject, int  x, int  y);
   void setModifiedFlag(JmriJFrame* theWrappedObject, bool  flag);
   void setName(JmriJFrame* theWrappedObject, QString  name);
   void setSavePosition(JmriJFrame* theWrappedObject, bool  save);
   void setSaveSize(JmriJFrame* theWrappedObject, bool  save);
   void setShutDownTask(JmriJFrame* theWrappedObject);
   void py_q_setTitle(JmriJFrame* theWrappedObject, QString  _title){  (((PythonQtPublicPromoter_JmriJFrame*)theWrappedObject)->py_q_setTitle(_title));}
   void setWindowTitle(JmriJFrame* theWrappedObject, const QString&  title);
   void storeValues(JmriJFrame* theWrappedObject);
   void py_q_storeValues(JmriJFrame* theWrappedObject){  (((PythonQtPublicPromoter_JmriJFrame*)theWrappedObject)->py_q_storeValues());}
   void windowClosing(JmriJFrame* theWrappedObject, QCloseEvent*  e);
   void py_q_windowClosing(JmriJFrame* theWrappedObject, QCloseEvent*  e){  (((PythonQtPublicPromoter_JmriJFrame*)theWrappedObject)->py_q_windowClosing(e));}
void py_set_windowMenu(JmriJFrame* theWrappedObject, QMenu*  windowMenu){ theWrappedObject->windowMenu = windowMenu; }
QMenu*  py_get_windowMenu(JmriJFrame* theWrappedObject){ return theWrappedObject->windowMenu; }
};





class PythonQtShell_LayoutBlockManager : public LayoutBlockManager
{
public:
    PythonQtShell_LayoutBlockManager(QObject*  parent = 0):LayoutBlockManager(parent),_wrapper(NULL) {}
    PythonQtShell_LayoutBlockManager(const LayoutBlockManager&  arg__1):LayoutBlockManager(arg__1),_wrapper(NULL) {}

   ~PythonQtShell_LayoutBlockManager();

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

class PythonQtPublicPromoter_LayoutBlockManager : public LayoutBlockManager
{ public:
inline QString  py_q_getBeanTypeHandled(bool  plural) const { return LayoutBlockManager::getBeanTypeHandled(plural); }
inline QString  py_q_getNamedBeanClass() const { return LayoutBlockManager::getNamedBeanClass(); }
inline int  py_q_getXMLOrder() const { return LayoutBlockManager::getXMLOrder(); }
inline char  py_q_typeLetter() const { return LayoutBlockManager::typeLetter(); }
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
   QString  py_q_getBeanTypeHandled(LayoutBlockManager* theWrappedObject, bool  plural) const{  return (((PythonQtPublicPromoter_LayoutBlockManager*)theWrappedObject)->py_q_getBeanTypeHandled(plural));}
   QCompleter*  getCompleter(LayoutBlockManager* theWrappedObject, QString  text, bool  bIncludeUserNames = false);
   NamedBean*  getFacingNamedBean(LayoutBlockManager* theWrappedObject, Block*  facingBlock, Block*  protectedBlock, LayoutEditor*  panel);
   Sensor*  getFacingSensor(LayoutBlockManager* theWrappedObject, Block*  facingBlock, Block*  protectedBlock, LayoutEditor*  panel);
   SignalHead*  getFacingSignalHead(LayoutBlockManager* theWrappedObject, Block*  facingBlock, Block*  protectedBlock);
   SignalMast*  getFacingSignalMast(LayoutBlockManager* theWrappedObject, Block*  facingBlock, Block*  protectedBlock);
   SignalMast*  getFacingSignalMast(LayoutBlockManager* theWrappedObject, Block*  facingBlock, Block*  protectedBlock, LayoutEditor*  panel);
   QObject*  getFacingSignalObject(LayoutBlockManager* theWrappedObject, Block*  facingBlock, Block*  protectedBlock);
   long  getLastRoutingChange(LayoutBlockManager* theWrappedObject);
   NamedBean*  getNamedBeanAtEndBumper(LayoutBlockManager* theWrappedObject, Block*  facingBlock, LayoutEditor*  panel);
   QString  py_q_getNamedBeanClass(LayoutBlockManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_LayoutBlockManager*)theWrappedObject)->py_q_getNamedBeanClass());}
   Sensor*  getSensorAtEndBumper(LayoutBlockManager* theWrappedObject, Block*  facingBlock, LayoutEditor*  panel);
   SignalMast*  getSignalMastAtEndBumper(LayoutBlockManager* theWrappedObject, Block*  facingBlock, LayoutEditor*  panel);
   Sensor*  getStabilisedSensor(LayoutBlockManager* theWrappedObject);
   int  py_q_getXMLOrder(LayoutBlockManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_LayoutBlockManager*)theWrappedObject)->py_q_getXMLOrder());}
   void initializeLayoutBlockPaths(LayoutBlockManager* theWrappedObject);
   bool  isAdvancedRoutingEnabled(LayoutBlockManager* theWrappedObject);
   bool  isAssignableFromType(LayoutBlockManager* theWrappedObject);
   bool  routingStablised(LayoutBlockManager* theWrappedObject);
   void setLastRoutingChange(LayoutBlockManager* theWrappedObject);
   void setStabilisedSensor(LayoutBlockManager* theWrappedObject, QString  pName) throw (JmriException);
   void turnOffWarning(LayoutBlockManager* theWrappedObject);
   char  py_q_typeLetter(LayoutBlockManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_LayoutBlockManager*)theWrappedObject)->py_q_typeLetter());}
   bool  warn(LayoutBlockManager* theWrappedObject);
    QString py_toString(LayoutBlockManager*);
};





class PythonQtShell_LayoutEditor : public LayoutEditor
{
public:
    PythonQtShell_LayoutEditor(QString  name = "My Layout", QWidget*  parent = 0):LayoutEditor(name, parent),_wrapper(NULL) {}
    PythonQtShell_LayoutEditor(const LayoutEditor&  arg__1):LayoutEditor(arg__1),_wrapper(NULL) {}

   ~PythonQtShell_LayoutEditor();

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
virtual void mouseEntered(QGraphicsSceneMouseEvent*  arg__1);
virtual void mouseExited(QGraphicsSceneMouseEvent*  event);
virtual void mouseMoveEvent(QMouseEvent*  event);
virtual void mousePressEvent(QMouseEvent*  event);
virtual void mouseReleaseEvent(QMouseEvent*  event);
virtual void moveEvent(QMoveEvent*  e);
virtual bool  nativeEvent(const QByteArray&  eventType, void*  message, long*  result);
virtual void newPanelDefaults();
virtual void pack();
virtual void paint(QGraphicsScene*  g);
virtual QPaintEngine*  paintEngine() const;
virtual void paintEvent(QPaintEvent*  event);
virtual void putItem(Positionable*  l);
virtual QPaintDevice*  redirected(QPoint*  offset) const;
virtual void redrawPanel();
virtual void repaint();
virtual void resizeEvent(QResizeEvent*  e);
virtual void setAllEditable(bool  editable);
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

class PythonQtPublicPromoter_LayoutEditor : public LayoutEditor
{ public:
inline void promoted_alignSelection(bool  alignX) { this->alignSelection(alignX); }
inline void promoted_assignBlockToSelection() { this->assignBlockToSelection(); }
inline void promoted_common() { this->common(); }
inline void promoted_drawTurnouts(EditScene*  g2) { this->drawTurnouts(g2); }
inline QList<Positionable* >  promoted_getSelectedItems(QGraphicsSceneMouseEvent*  event) { return this->getSelectedItems(event); }
inline bool  promoted_remove(QObject*  s) { return this->remove(s); }
inline void promoted_removeBackground(PositionableLabel*  b) { this->removeBackground(b); }
inline bool  promoted_removeLayoutSlip(LayoutTurnout*  o) { return this->removeLayoutSlip(o); }
inline bool  promoted_removeLayoutTurnout(LayoutTurnout*  o) { return this->removeLayoutTurnout(o); }
inline void promoted_removeMarkers() { this->removeMarkers(); }
inline void promoted_setSelectionsScale(double  s, Positionable*  p) { this->setSelectionsScale(s, p); }
inline QMenu*  promoted_setupOptionMenu(QMenuBar*  menuBar) { return this->setupOptionMenu(menuBar); }
inline void promoted_setupToolsMenu(QMenuBar*  menuBar) { this->setupToolsMenu(menuBar); }
inline bool  promoted_showAlignPopup() { return this->showAlignPopup(); }
inline void promoted_showPopUp(Positionable*  p, QGraphicsSceneMouseEvent*  event) { this->showPopUp(p, event); }
inline void promoted_targetWindowClosingEvent(QCloseEvent*  e) { this->targetWindowClosingEvent(e); }
inline void promoted_undoMoveSelection() { this->undoMoveSelection(); }
inline bool  py_q_deletePanel() { return LayoutEditor::deletePanel(); }
inline void py_q_dispose() { LayoutEditor::dispose(); }
inline QString  py_q_getClassName() { return LayoutEditor::getClassName(); }
inline void py_q_init(QString  name) { LayoutEditor::init(name); }
inline void py_q_initView() { LayoutEditor::initView(); }
inline void py_q_keyPressEvent(QKeyEvent*  event) { LayoutEditor::keyPressEvent(event); }
inline void py_q_newPanelDefaults() { LayoutEditor::newPanelDefaults(); }
inline void py_q_putItem(Positionable*  l) { LayoutEditor::putItem(l); }
inline void py_q_redrawPanel() { LayoutEditor::redrawPanel(); }
inline void py_q_repaint() { LayoutEditor::repaint(); }
inline void py_q_setAllEditable(bool  editable) { LayoutEditor::setAllEditable(editable); }
inline void py_q_setAllPositionable(bool  state) { LayoutEditor::setAllPositionable(state); }
inline void py_q_setNextLocation(Positionable*  obj) { LayoutEditor::setNextLocation(obj); }
inline void py_q_setScroll(int  state) { LayoutEditor::setScroll(state); }
inline void py_q_setSelectionsScale(double  s, Positionable*  p) { LayoutEditor::setSelectionsScale(s, p); }
inline void py_q_showPopUp(Positionable*  p, QGraphicsSceneMouseEvent*  event) { LayoutEditor::showPopUp(p, event); }
inline void py_q_targetWindowClosingEvent(QCloseEvent*  e) { LayoutEditor::targetWindowClosingEvent(e); }
inline void py_q_vetoableChange(PropertyChangeEvent*  evt) { LayoutEditor::vetoableChange(evt); }
};

class PythonQtWrapper_LayoutEditor : public QObject
{ Q_OBJECT
public:
public slots:
LayoutEditor* new_LayoutEditor(QString  name = "My Layout", QWidget*  parent = 0);
LayoutEditor* new_LayoutEditor(const LayoutEditor&  arg__1);
void delete_LayoutEditor(LayoutEditor* obj) { delete obj; } 
   void addAnchor(LayoutEditor* theWrappedObject);
   void addBackground(LayoutEditor* theWrappedObject);
   void addBlockContents(LayoutEditor* theWrappedObject);
   void addEdgeConnector(LayoutEditor* theWrappedObject);
   void addEndBumper(LayoutEditor* theWrappedObject);
   void addIcon(LayoutEditor* theWrappedObject);
   void addLabel(LayoutEditor* theWrappedObject);
   void addLayoutTrack(LayoutEditor* theWrappedObject, LayoutTrack*  trk);
   void addLayoutTurnout(LayoutEditor* theWrappedObject, int  type);
   void addLevelXing(LayoutEditor* theWrappedObject);
   void addMemory(LayoutEditor* theWrappedObject);
   void addSignalHead(LayoutEditor* theWrappedObject);
   void addSignalMast(LayoutEditor* theWrappedObject);
   void addToPopUpMenu(LayoutEditor* theWrappedObject, NamedBean*  nb, QMenu*  item, int  menu);
   void addTrackSegment(LayoutEditor* theWrappedObject);
   void addTurntable(LayoutEditor* theWrappedObject, QPointF  pt);
   void alignLayoutToGrid(LayoutEditor* theWrappedObject);
   void alignSelection(LayoutEditor* theWrappedObject, bool  alignX);
   void alignSelectionToGrid(LayoutEditor* theWrappedObject);
   bool  allControlling(LayoutEditor* theWrappedObject);
   void clearSelectionGroups(LayoutEditor* theWrappedObject);
   void common(LayoutEditor* theWrappedObject);
   bool  containsSignalHead(LayoutEditor* theWrappedObject, SignalHead*  head);
   bool  containsSignalMast(LayoutEditor* theWrappedObject, SignalMast*  mast);
   bool  py_q_deletePanel(LayoutEditor* theWrappedObject){  return (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_deletePanel());}
   void py_q_dispose(LayoutEditor* theWrappedObject){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_dispose());}
   void drawSelectionRect(LayoutEditor* theWrappedObject, EditScene*  g2);
   void drawTurnouts(LayoutEditor* theWrappedObject, EditScene*  g2);
   int  getAnchorX(LayoutEditor* theWrappedObject);
   int  getAnchorY(LayoutEditor* theWrappedObject);
   bool  getAntialiasingOn(LayoutEditor* theWrappedObject);
   bool  getAutoBlockAssignment(LayoutEditor* theWrappedObject);
   QString  py_q_getClassName(LayoutEditor* theWrappedObject){  return (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_getClassName());}
   const QIcon  getColourIcon(LayoutEditor* theWrappedObject, QColor  color);
   QPointF  static_LayoutEditor_getCoords(LayoutTrack*  layoutTrack, int  connectionType);
   QString  getDefaultAlternativeTrackColor(LayoutEditor* theWrappedObject);
   QColor  getDefaultAlternativeTrackColorColor(LayoutEditor* theWrappedObject);
   QString  getDefaultOccupiedTrackColor(LayoutEditor* theWrappedObject);
   QColor  getDefaultOccupiedTrackColorColor(LayoutEditor* theWrappedObject);
   QString  getDefaultTextColor(LayoutEditor* theWrappedObject);
   QString  getDefaultTrackColor(LayoutEditor* theWrappedObject);
   QColor  getDefaultTrackColorColor(LayoutEditor* theWrappedObject);
   bool  getDirectTurnoutControl(LayoutEditor* theWrappedObject);
   bool  getDrawGrid(LayoutEditor* theWrappedObject);
   bool  getHighlightSelectedBlock(LayoutEditor* theWrappedObject);
   QString  getLayoutName(LayoutEditor* theWrappedObject);
   QList<LayoutTrack* >*  getLayoutTracks(LayoutEditor* theWrappedObject);
   QList<LayoutTurnout* >  getLayoutTurnouts(LayoutEditor* theWrappedObject);
   QList<LayoutTurnout* >*  getLayoutTurnoutsAndSlips(LayoutEditor* theWrappedObject);
   double  getMaxZoom(LayoutEditor* theWrappedObject);
   double  getMinZoom(LayoutEditor* theWrappedObject);
   bool  getOpenDispatcherOnLoad(LayoutEditor* theWrappedObject);
   QRectF  getPanelBounds(LayoutEditor* theWrappedObject);
   EditScene*  getScene(LayoutEditor* theWrappedObject);
   bool  getScroll(LayoutEditor* theWrappedObject);
   QList<Positionable* >  getSelectedItems(LayoutEditor* theWrappedObject, QGraphicsSceneMouseEvent*  event);
   QRectF  getSelectionRect(LayoutEditor* theWrappedObject);
   bool  getShowHelpBar(LayoutEditor* theWrappedObject);
   SignalHead*  getSignalHead(LayoutEditor* theWrappedObject, QString  name);
   SignalMast*  getSignalMast(LayoutEditor* theWrappedObject, QString  name);
   bool  getSnapOnAdd(LayoutEditor* theWrappedObject);
   bool  getSnapOnMove(LayoutEditor* theWrappedObject);
   bool  getTooltipsInEdit(LayoutEditor* theWrappedObject);
   bool  getTooltipsNotEdit(LayoutEditor* theWrappedObject);
   double  getTurnoutBX(LayoutEditor* theWrappedObject);
   double  getTurnoutCX(LayoutEditor* theWrappedObject);
   QString  getTurnoutCircleColor(LayoutEditor* theWrappedObject);
   int  getTurnoutCircleSize(LayoutEditor* theWrappedObject);
   QString  getTurnoutCircleThrownColor(LayoutEditor* theWrappedObject);
   bool  getTurnoutCircles(LayoutEditor* theWrappedObject);
   double  getTurnoutWid(LayoutEditor* theWrappedObject);
   double  getXOverHWid(LayoutEditor* theWrappedObject);
   double  getXOverLong(LayoutEditor* theWrappedObject);
   double  getXOverShort(LayoutEditor* theWrappedObject);
   double  getZoom(LayoutEditor* theWrappedObject);
   bool  highlightBlock(LayoutEditor* theWrappedObject, Block*  inBlock);
   void py_q_init(LayoutEditor* theWrappedObject, QString  name){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_init(name));}
   void py_q_initView(LayoutEditor* theWrappedObject){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_initView());}
   bool  isAnimating(LayoutEditor* theWrappedObject);
   bool  isEditable(LayoutEditor* theWrappedObject);
   bool  isIncludedTurnoutSkipped(LayoutEditor* theWrappedObject);
   bool  isTurnoutDrawUnselectedLeg(LayoutEditor* theWrappedObject);
   bool  isTurnoutFillControlCircles(LayoutEditor* theWrappedObject);
   void py_q_keyPressEvent(LayoutEditor* theWrappedObject, QKeyEvent*  event){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_keyPressEvent(event));}
   QRectF  layoutEditorControlCircleRectAt(LayoutEditor* theWrappedObject, QPointF  inPoint);
   QRectF  layoutEditorControlRectAt(LayoutEditor* theWrappedObject, QPointF  inPoint);
   void py_q_newPanelDefaults(LayoutEditor* theWrappedObject){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_newPanelDefaults());}
   void paintTargetPanel(LayoutEditor* theWrappedObject, EditScene*  g2);
   void py_q_putItem(LayoutEditor* theWrappedObject, Positionable*  l){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_putItem(l));}
   void py_q_redrawPanel(LayoutEditor* theWrappedObject){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_redrawPanel());}
   bool  remove(LayoutEditor* theWrappedObject, QObject*  s);
   void removeBackground(LayoutEditor* theWrappedObject, PositionableLabel*  b);
   bool  removeFromContents(LayoutEditor* theWrappedObject, Positionable*  l);
   bool  removeLayoutSlip(LayoutEditor* theWrappedObject, LayoutTurnout*  o);
   void removeLayoutTrack(LayoutEditor* theWrappedObject, LayoutTrack*  trk);
   bool  removeLayoutTrackAndRedraw(LayoutEditor* theWrappedObject, LayoutTrack*  trk);
   bool  removeLayoutTurnout(LayoutEditor* theWrappedObject, LayoutTurnout*  o);
   void removeMarkers(LayoutEditor* theWrappedObject);
   void removeSignalHead(LayoutEditor* theWrappedObject, SignalHead*  head);
   void py_q_repaint(LayoutEditor* theWrappedObject){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_repaint());}
   void resetAwaitingIconChange(LayoutEditor* theWrappedObject);
   void rotateLayout90(LayoutEditor* theWrappedObject);
   void rotateSelection90(LayoutEditor* theWrappedObject);
   bool  scaleTrack(LayoutEditor* theWrappedObject, float  xFactor, float  yFactor);
   void py_q_setAllEditable(LayoutEditor* theWrappedObject, bool  editable){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_setAllEditable(editable));}
   void py_q_setAllPositionable(LayoutEditor* theWrappedObject, bool  state){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_setAllPositionable(state));}
   int  setAllTracksToDefaultColors(LayoutEditor* theWrappedObject);
   void setAntialiasingOn(LayoutEditor* theWrappedObject, bool  state);
   void setAutoBlockAssignment(LayoutEditor* theWrappedObject, bool  boo);
   void setAwaitingIconChange(LayoutEditor* theWrappedObject);
   void setConnections(LayoutEditor* theWrappedObject);
   void setCurrentPositionAndSize(LayoutEditor* theWrappedObject);
   void setDefaultAlternativeTrackColor(LayoutEditor* theWrappedObject, QColor  color);
   void setDefaultBackgroundColor(LayoutEditor* theWrappedObject, QColor  color);
   void setDefaultOccupiedTrackColor(LayoutEditor* theWrappedObject, QColor  color);
   void setDefaultTextColor(LayoutEditor* theWrappedObject, QColor  sColor);
   void setDefaultTrackColor(LayoutEditor* theWrappedObject, QColor  color);
   void setDirectTurnoutControl(LayoutEditor* theWrappedObject, bool  boo);
   void setDirty(LayoutEditor* theWrappedObject, bool  b = true);
   void setDrawGrid(LayoutEditor* theWrappedObject, bool  state);
   void setHighlightSelectedBlock(LayoutEditor* theWrappedObject, bool  state);
   void setIncludedTurnoutSkipped(LayoutEditor* theWrappedObject, bool  boo);
   void setLayoutDimensions(LayoutEditor* theWrappedObject, int  windowW, int  windowH, int  x, int  y, int  panelW, int  panelH, bool  merge);
   void setLayoutDimensions(LayoutEditor* theWrappedObject, int  windowWidth, int  windowHeight, int  windowX, int  windowY, int  panelWidth, int  panelHeight);
   void setLayoutName(LayoutEditor* theWrappedObject, QString  name);
   void py_q_setNextLocation(LayoutEditor* theWrappedObject, Positionable*  obj){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_setNextLocation(obj));}
   void setOpenDispatcherOnLoad(LayoutEditor* theWrappedObject, bool  boo);
   void setPanelBounds(LayoutEditor* theWrappedObject, QRectF  newBounds);
   void py_q_setScroll(LayoutEditor* theWrappedObject, int  state){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_setScroll(state));}
   void setSelectionRect(LayoutEditor* theWrappedObject, QRectF  selectionRect);
   void py_q_setSelectionsScale(LayoutEditor* theWrappedObject, double  s, Positionable*  p){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_setSelectionsScale(s, p));}
   bool  setShowAlignmentMenu(LayoutEditor* theWrappedObject, QMenu*  popup);
   void setShowHelpBar(LayoutEditor* theWrappedObject, bool  state);
   void setSize(LayoutEditor* theWrappedObject, int  w, int  h);
   void setSnapOnAdd(LayoutEditor* theWrappedObject, bool  state);
   void setSnapOnMove(LayoutEditor* theWrappedObject, bool  state);
   void setTooltipsInEdit(LayoutEditor* theWrappedObject, bool  state);
   void setTooltipsNotEdit(LayoutEditor* theWrappedObject, bool  state);
   void setTurnoutAnimation(LayoutEditor* theWrappedObject, bool  state);
   void setTurnoutBX(LayoutEditor* theWrappedObject, double  bx);
   void setTurnoutCX(LayoutEditor* theWrappedObject, double  cx);
   void setTurnoutCircleColor(LayoutEditor* theWrappedObject, QColor  color);
   void setTurnoutCircleSize(LayoutEditor* theWrappedObject, int  size);
   void setTurnoutCircleThrownColor(LayoutEditor* theWrappedObject, QColor  color);
   void setTurnoutCircles(LayoutEditor* theWrappedObject, bool  state);
   void setTurnoutDrawUnselectedLeg(LayoutEditor* theWrappedObject, bool  state);
   void setTurnoutWid(LayoutEditor* theWrappedObject, double  wid);
   void setXOverHWid(LayoutEditor* theWrappedObject, double  hwid);
   void setXOverLong(LayoutEditor* theWrappedObject, double  lg);
   void setXOverShort(LayoutEditor* theWrappedObject, double  sh);
   void setXScale(LayoutEditor* theWrappedObject, double  xSc);
   void setYScale(LayoutEditor* theWrappedObject, double  ySc);
   double  setZoom(LayoutEditor* theWrappedObject, double  zoomFactor);
   QMenu*  setupOptionMenu(LayoutEditor* theWrappedObject, QMenuBar*  menuBar);
   void setupToolsMenu(LayoutEditor* theWrappedObject, QMenuBar*  menuBar);
   bool  showAlignPopup(LayoutEditor* theWrappedObject);
   void py_q_showPopUp(LayoutEditor* theWrappedObject, Positionable*  p, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_showPopUp(p, event));}
   void sortLayoutShapesByLevel(LayoutEditor* theWrappedObject);
   void py_q_targetWindowClosingEvent(LayoutEditor* theWrappedObject, QCloseEvent*  e){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_targetWindowClosingEvent(e));}
   QString  toString(LayoutEditor* theWrappedObject);
   QRectF  trackControlCircleRectAt(LayoutEditor* theWrappedObject, QPointF  inPoint);
   QRectF  trackEditControlRectAt(LayoutEditor* theWrappedObject, QPointF  inPoint);
   void translate(LayoutEditor* theWrappedObject, float  xTranslation, float  yTranslation);
   bool  translateTrack(LayoutEditor* theWrappedObject, float  xDel, float  yDel);
   QRectF  unionToPanelBounds(LayoutEditor* theWrappedObject, QRectF  bounds);
   bool  validatePhysicalTurnout(LayoutEditor* theWrappedObject, QString  inTurnoutName, QWidget*  openPane = 0);
   void py_q_vetoableChange(LayoutEditor* theWrappedObject, PropertyChangeEvent*  evt){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_vetoableChange(evt));}
    QString py_toString(LayoutEditor*);
void py_set__labelImage(LayoutEditor* theWrappedObject, QVector<PositionableLabel* >*  _labelImage){ theWrappedObject->_labelImage = _labelImage; }
QVector<PositionableLabel* >*  py_get__labelImage(LayoutEditor* theWrappedObject){ return theWrappedObject->_labelImage; }
void py_set_backgroundImage(LayoutEditor* theWrappedObject, QVector<PositionableLabel* >*  backgroundImage){ theWrappedObject->backgroundImage = backgroundImage; }
QVector<PositionableLabel* >*  py_get_backgroundImage(LayoutEditor* theWrappedObject){ return theWrappedObject->backgroundImage; }
void py_set_labelImage(LayoutEditor* theWrappedObject, QList<PositionableLabel* >*  labelImage){ theWrappedObject->labelImage = labelImage; }
QList<PositionableLabel* >*  py_get_labelImage(LayoutEditor* theWrappedObject){ return theWrappedObject->labelImage; }
};





class PythonQtShell_LayoutTurnout : public LayoutTurnout
{
public:
    PythonQtShell_LayoutTurnout(QString  id, QPointF  c, LayoutEditor*  layoutEditor):LayoutTurnout(id, c, layoutEditor),_wrapper(NULL) {}

   ~PythonQtShell_LayoutTurnout();

virtual bool  canRemove();
virtual QList<int >  checkForFreeConnections();
virtual void checkForNonContiguousBlocks(QMap<QString , QList<QSet<QString >* >* >*  blockNamesToTrackNameSetsMap);
virtual bool  checkForUnAssignedBlocks();
virtual void collectContiguousTracksNamesInBlockNamed(QString  blockName, QSet<QString >*  TrackNameSet);
virtual void draw1(EditScene*  g2, bool  isMain, bool  isBlock);
virtual void draw2(EditScene*  g2, bool  isMain, float  railDisplacement);
virtual void drawEditControls(EditScene*  g2);
virtual void drawTurnoutControls(EditScene*  g2);
virtual int  findHitPointType(QPointF  hitPoint, bool  useRectangles, bool  requireUnconnected);
virtual QRectF  getBounds();
virtual LayoutTrack*  getConnection(int  location) throw (JmriException) ;
virtual QPointF  getCoordsForConnectionType(int  connectionType);
virtual void highlightUnconnected(EditScene*  g2, int  specificType);
virtual void invalidate(EditScene*  g2);
virtual bool  isMainline();
virtual void reCheckBlockBoundary() const;
virtual void scaleCoords(double  xFactor, double  yFactor);
virtual void setConnection(int  location, LayoutTrack*  o, int  type) throw (JmriException) ;
virtual void setCoordsCenter(QPointF  p);
virtual QMenu*  showPopup(QGraphicsSceneMouseEvent*  e);
virtual QString  toString();

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_LayoutTurnout : public LayoutTurnout
{ public:
inline void promoted_draw1(EditScene*  g2, bool  isMain, bool  isBlock) { this->draw1(g2, isMain, isBlock); }
inline void promoted_draw2(EditScene*  g2, bool  isMain, float  railDisplacement) { this->draw2(g2, isMain, railDisplacement); }
inline void promoted_drawEditControls(EditScene*  g2) { this->drawEditControls(g2); }
inline void promoted_drawTurnoutControls(EditScene*  g2) { this->drawTurnoutControls(g2); }
inline int  promoted_findHitPointType(QPointF  hitPoint, bool  useRectangles, bool  requireUnconnected) { return this->findHitPointType(hitPoint, useRectangles, requireUnconnected); }
inline void promoted_highlightUnconnected(EditScene*  g2, int  specificType) { this->highlightUnconnected(g2, specificType); }
inline void promoted_rotateCoords(double  angleDEG) { this->rotateCoords(angleDEG); }
inline QPointF  promoted_rotatePoint(QPointF  p, double  sineAng, double  cosineAng) { return this->rotatePoint(p, sineAng, cosineAng); }
inline QMenu*  promoted_showPopup(QGraphicsSceneMouseEvent*  e) { return this->showPopup(e); }
inline bool  py_q_canRemove() { return LayoutTurnout::canRemove(); }
inline QList<int >  py_q_checkForFreeConnections() { return LayoutTurnout::checkForFreeConnections(); }
inline void py_q_checkForNonContiguousBlocks(QMap<QString , QList<QSet<QString >* >* >*  blockNamesToTrackNameSetsMap) { LayoutTurnout::checkForNonContiguousBlocks(blockNamesToTrackNameSetsMap); }
inline bool  py_q_checkForUnAssignedBlocks() { return LayoutTurnout::checkForUnAssignedBlocks(); }
inline void py_q_collectContiguousTracksNamesInBlockNamed(QString  blockName, QSet<QString >*  TrackNameSet) { LayoutTurnout::collectContiguousTracksNamesInBlockNamed(blockName, TrackNameSet); }
inline void py_q_draw1(EditScene*  g2, bool  isMain, bool  isBlock) { LayoutTurnout::draw1(g2, isMain, isBlock); }
inline void py_q_draw2(EditScene*  g2, bool  isMain, float  railDisplacement) { LayoutTurnout::draw2(g2, isMain, railDisplacement); }
inline void py_q_drawEditControls(EditScene*  g2) { LayoutTurnout::drawEditControls(g2); }
inline void py_q_drawTurnoutControls(EditScene*  g2) { LayoutTurnout::drawTurnoutControls(g2); }
inline int  py_q_findHitPointType(QPointF  hitPoint, bool  useRectangles, bool  requireUnconnected) { return LayoutTurnout::findHitPointType(hitPoint, useRectangles, requireUnconnected); }
inline QRectF  py_q_getBounds() { return LayoutTurnout::getBounds(); }
inline LayoutTrack*  py_q_getConnection(int  location) throw (JmriException)  { return LayoutTurnout::getConnection(location); }
inline QPointF  py_q_getCoordsForConnectionType(int  connectionType) { return LayoutTurnout::getCoordsForConnectionType(connectionType); }
inline void py_q_highlightUnconnected(EditScene*  g2, int  specificType) { LayoutTurnout::highlightUnconnected(g2, specificType); }
inline void py_q_invalidate(EditScene*  g2) { LayoutTurnout::invalidate(g2); }
inline bool  py_q_isMainline() { return LayoutTurnout::isMainline(); }
inline void py_q_reCheckBlockBoundary() const { LayoutTurnout::reCheckBlockBoundary(); }
inline void py_q_scaleCoords(double  xFactor, double  yFactor) { LayoutTurnout::scaleCoords(xFactor, yFactor); }
inline void py_q_setConnection(int  location, LayoutTrack*  o, int  type) throw (JmriException)  { LayoutTurnout::setConnection(location, o, type); }
inline void py_q_setCoordsCenter(QPointF  p) { LayoutTurnout::setCoordsCenter(p); }
inline QMenu*  py_q_showPopup(QGraphicsSceneMouseEvent*  e) { return LayoutTurnout::showPopup(e); }
inline QString  py_q_toString() { return LayoutTurnout::toString(); }
};

class PythonQtWrapper_LayoutTurnout : public QObject
{ Q_OBJECT
public:
public slots:
LayoutTurnout* new_LayoutTurnout(QString  id, QPointF  c, LayoutEditor*  layoutEditor);
void delete_LayoutTurnout(LayoutTurnout* obj) { delete obj; } 
   void addEditPopUpMenu(LayoutTurnout* theWrappedObject, QObject*  menu);
   void addViewPopUpMenu(LayoutTurnout* theWrappedObject, QObject*  menu);
   bool  canRemove(LayoutTurnout* theWrappedObject);
   bool  py_q_canRemove(LayoutTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_canRemove());}
   QList<int >  checkForFreeConnections(LayoutTurnout* theWrappedObject);
   QList<int >  py_q_checkForFreeConnections(LayoutTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_checkForFreeConnections());}
   void checkForNonContiguousBlocks(LayoutTurnout* theWrappedObject, QMap<QString , QList<QSet<QString >* >* >*  blockNamesToTrackNameSetsMap);
   void py_q_checkForNonContiguousBlocks(LayoutTurnout* theWrappedObject, QMap<QString , QList<QSet<QString >* >* >*  blockNamesToTrackNameSetsMap){  (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_checkForNonContiguousBlocks(blockNamesToTrackNameSetsMap));}
   bool  checkForUnAssignedBlocks(LayoutTurnout* theWrappedObject);
   bool  py_q_checkForUnAssignedBlocks(LayoutTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_checkForUnAssignedBlocks());}
   void collectContiguousTracksNamesInBlockNamed(LayoutTurnout* theWrappedObject, QString  blockName, QSet<QString >*  TrackNameSet);
   void py_q_collectContiguousTracksNamesInBlockNamed(LayoutTurnout* theWrappedObject, QString  blockName, QSet<QString >*  TrackNameSet){  (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_collectContiguousTracksNamesInBlockNamed(blockName, TrackNameSet));}
   void dispose(LayoutTurnout* theWrappedObject);
   void draw1(LayoutTurnout* theWrappedObject, EditScene*  g2, bool  isMain, bool  isBlock);
   void py_q_draw1(LayoutTurnout* theWrappedObject, EditScene*  g2, bool  isMain, bool  isBlock){  (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_draw1(g2, isMain, isBlock));}
   void draw2(LayoutTurnout* theWrappedObject, EditScene*  g2, bool  isMain, float  railDisplacement);
   void py_q_draw2(LayoutTurnout* theWrappedObject, EditScene*  g2, bool  isMain, float  railDisplacement){  (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_draw2(g2, isMain, railDisplacement));}
   void drawEditControls(LayoutTurnout* theWrappedObject, EditScene*  g2);
   void py_q_drawEditControls(LayoutTurnout* theWrappedObject, EditScene*  g2){  (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_drawEditControls(g2));}
   void drawTurnoutControls(LayoutTurnout* theWrappedObject, EditScene*  g2);
   void py_q_drawTurnoutControls(LayoutTurnout* theWrappedObject, EditScene*  g2){  (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_drawTurnoutControls(g2));}
   int  findHitPointType(LayoutTurnout* theWrappedObject, QPointF  hitPoint, bool  useRectangles, bool  requireUnconnected);
   int  py_q_findHitPointType(LayoutTurnout* theWrappedObject, QPointF  hitPoint, bool  useRectangles, bool  requireUnconnected){  return (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_findHitPointType(hitPoint, useRectangles, requireUnconnected));}
   QList<QString >  getBeanReferences(LayoutTurnout* theWrappedObject, QString  pointName);
   QString  getBlockBName(LayoutTurnout* theWrappedObject);
   QStringList  getBlockBoundaries(LayoutTurnout* theWrappedObject);
   QString  getBlockCName(LayoutTurnout* theWrappedObject);
   QString  getBlockDName(LayoutTurnout* theWrappedObject);
   QString  getBlockName(LayoutTurnout* theWrappedObject);
   QRectF  getBounds(LayoutTurnout* theWrappedObject);
   QRectF  py_q_getBounds(LayoutTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_getBounds());}
   QObject*  getConnectA(LayoutTurnout* theWrappedObject);
   QObject*  getConnectB(LayoutTurnout* theWrappedObject);
   QObject*  getConnectC(LayoutTurnout* theWrappedObject);
   QObject*  getConnectD(LayoutTurnout* theWrappedObject);
   LayoutTrack*  getConnection(LayoutTurnout* theWrappedObject, int  location) throw (JmriException) ;
   LayoutTrack*  py_q_getConnection(LayoutTurnout* theWrappedObject, int  location) throw (JmriException) {  return (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_getConnection(location));}
   int  getContinuingSense(LayoutTurnout* theWrappedObject);
   QPointF  getCoordsA(LayoutTurnout* theWrappedObject);
   QPointF  getCoordsB(LayoutTurnout* theWrappedObject);
   QPointF  getCoordsC(LayoutTurnout* theWrappedObject);
   QPointF  getCoordsD(LayoutTurnout* theWrappedObject);
   QPointF  getCoordsForConnectionType(LayoutTurnout* theWrappedObject, int  connectionType);
   QPointF  py_q_getCoordsForConnectionType(LayoutTurnout* theWrappedObject, int  connectionType){  return (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_getCoordsForConnectionType(connectionType));}
   bool  getHidden(LayoutTurnout* theWrappedObject);
   int  getLinkType(LayoutTurnout* theWrappedObject);
   QString  getLinkedTurnoutName(LayoutTurnout* theWrappedObject);
   QString  getName(LayoutTurnout* theWrappedObject);
   Turnout*  getSecondTurnout(LayoutTurnout* theWrappedObject);
   QString  getSecondTurnoutName(LayoutTurnout* theWrappedObject);
   Sensor*  getSensorA(LayoutTurnout* theWrappedObject);
   QString  getSensorAName(LayoutTurnout* theWrappedObject);
   Sensor*  getSensorB(LayoutTurnout* theWrappedObject);
   QString  getSensorBName(LayoutTurnout* theWrappedObject);
   Sensor*  getSensorC(LayoutTurnout* theWrappedObject);
   QString  getSensorCName(LayoutTurnout* theWrappedObject);
   Sensor*  getSensorD(LayoutTurnout* theWrappedObject);
   QString  getSensorDName(LayoutTurnout* theWrappedObject);
   SignalHead*  getSignalA1(LayoutTurnout* theWrappedObject);
   QString  getSignalA1Name(LayoutTurnout* theWrappedObject);
   SignalHead*  getSignalA2(LayoutTurnout* theWrappedObject);
   QString  getSignalA2Name(LayoutTurnout* theWrappedObject);
   SignalHead*  getSignalA3(LayoutTurnout* theWrappedObject);
   QString  getSignalA3Name(LayoutTurnout* theWrappedObject);
   SignalMast*  getSignalAMast(LayoutTurnout* theWrappedObject) const;
   QString  getSignalAMastName(LayoutTurnout* theWrappedObject);
   SignalHead*  getSignalB1(LayoutTurnout* theWrappedObject);
   QString  getSignalB1Name(LayoutTurnout* theWrappedObject);
   SignalHead*  getSignalB2(LayoutTurnout* theWrappedObject);
   QString  getSignalB2Name(LayoutTurnout* theWrappedObject);
   SignalMast*  getSignalBMast(LayoutTurnout* theWrappedObject) const;
   QString  getSignalBMastName(LayoutTurnout* theWrappedObject);
   SignalHead*  getSignalC1(LayoutTurnout* theWrappedObject);
   QString  getSignalC1Name(LayoutTurnout* theWrappedObject);
   SignalHead*  getSignalC2(LayoutTurnout* theWrappedObject);
   QString  getSignalC2Name(LayoutTurnout* theWrappedObject);
   SignalMast*  getSignalCMast(LayoutTurnout* theWrappedObject) const;
   QString  getSignalCMastName(LayoutTurnout* theWrappedObject);
   SignalHead*  getSignalD1(LayoutTurnout* theWrappedObject);
   QString  getSignalD1Name(LayoutTurnout* theWrappedObject);
   SignalHead*  getSignalD2(LayoutTurnout* theWrappedObject);
   QString  getSignalD2Name(LayoutTurnout* theWrappedObject);
   SignalMast*  getSignalDMast(LayoutTurnout* theWrappedObject) const;
   QString  getSignalDMastName(LayoutTurnout* theWrappedObject);
   SignalHead*  getSignalHead(LayoutTurnout* theWrappedObject, int  loc);
   int  getState(LayoutTurnout* theWrappedObject);
   Turnout*  getTurnout(LayoutTurnout* theWrappedObject);
   QString  getTurnoutName(LayoutTurnout* theWrappedObject);
   int  getVersion(LayoutTurnout* theWrappedObject);
   bool  hasEnteringDoubleTrack(LayoutTurnout* theWrappedObject);
   bool  hasEnteringSingleTrack(LayoutTurnout* theWrappedObject);
   void highlightUnconnected(LayoutTurnout* theWrappedObject, EditScene*  g2, int  specificType);
   void py_q_highlightUnconnected(LayoutTurnout* theWrappedObject, EditScene*  g2, int  specificType){  (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_highlightUnconnected(g2, specificType));}
   void invalidate(LayoutTurnout* theWrappedObject, EditScene*  g2);
   void py_q_invalidate(LayoutTurnout* theWrappedObject, EditScene*  g2){  (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_invalidate(g2));}
   bool  isActive(LayoutTurnout* theWrappedObject);
   bool  isDisabled(LayoutTurnout* theWrappedObject);
   bool  isDisabledWhenOccupied(LayoutTurnout* theWrappedObject);
   bool  isInContinuingSenseState(LayoutTurnout* theWrappedObject);
   bool  isMainline(LayoutTurnout* theWrappedObject);
   bool  py_q_isMainline(LayoutTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_isMainline());}
   bool  isMainlineA(LayoutTurnout* theWrappedObject);
   bool  isMainlineB(LayoutTurnout* theWrappedObject);
   bool  isMainlineC(LayoutTurnout* theWrappedObject);
   bool  isMainlineD(LayoutTurnout* theWrappedObject);
   bool  isSecondTurnoutInverted(LayoutTurnout* theWrappedObject);
   bool  isTurnoutTypeSlip(LayoutTurnout* theWrappedObject);
   bool  isTurnoutTypeTurnout(LayoutTurnout* theWrappedObject) const;
   bool  isTurnoutTypeXover(LayoutTurnout* theWrappedObject) const;
   void reCheckBlockBoundary(LayoutTurnout* theWrappedObject) const;
   void py_q_reCheckBlockBoundary(LayoutTurnout* theWrappedObject) const{  (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_reCheckBlockBoundary());}
   void remove(LayoutTurnout* theWrappedObject);
   void removeBeanReference(LayoutTurnout* theWrappedObject, NamedBean*  nb);
   void removeSML(LayoutTurnout* theWrappedObject, SignalMast*  signalMast) const;
   void rotateCoords(LayoutTurnout* theWrappedObject, double  angleDEG);
   QPointF  rotatePoint(LayoutTurnout* theWrappedObject, QPointF  p, double  sineAng, double  cosineAng);
   void scaleCoords(LayoutTurnout* theWrappedObject, double  xFactor, double  yFactor);
   void py_q_scaleCoords(LayoutTurnout* theWrappedObject, double  xFactor, double  yFactor){  (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_scaleCoords(xFactor, yFactor));}
   void setAdditionalEditPopUpMenu(LayoutTurnout* theWrappedObject, QMenu*  popup);
   void setAdditionalViewPopUpMenu(LayoutTurnout* theWrappedObject, QMenu*  popup);
   void setConnectA(LayoutTurnout* theWrappedObject, LayoutTrack*  o, int  type);
   void setConnectB(LayoutTurnout* theWrappedObject, LayoutTrack*  o, int  type);
   void setConnectC(LayoutTurnout* theWrappedObject, LayoutTrack*  o, int  type);
   void setConnectD(LayoutTurnout* theWrappedObject, LayoutTrack*  o, int  type);
   void setConnection(LayoutTurnout* theWrappedObject, int  location, LayoutTrack*  o, int  type) throw (JmriException) ;
   void py_q_setConnection(LayoutTurnout* theWrappedObject, int  location, LayoutTrack*  o, int  type) throw (JmriException) {  (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_setConnection(location, o, type));}
   void setContinuingSense(LayoutTurnout* theWrappedObject, int  sense);
   void setCoordsA(LayoutTurnout* theWrappedObject, QPointF  p);
   void setCoordsB(LayoutTurnout* theWrappedObject, QPointF  p);
   void setCoordsC(LayoutTurnout* theWrappedObject, QPointF  p);
   void setCoordsCenter(LayoutTurnout* theWrappedObject, QPointF  p);
   void py_q_setCoordsCenter(LayoutTurnout* theWrappedObject, QPointF  p){  (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_setCoordsCenter(p));}
   void setCoordsD(LayoutTurnout* theWrappedObject, QPointF  p);
   void setHidden(LayoutTurnout* theWrappedObject, bool  hide);
   void setLayoutBlockBByName(LayoutTurnout* theWrappedObject, QString  name);
   void setLayoutBlockByName(LayoutTurnout* theWrappedObject, QString  name);
   void setLayoutBlockCByName(LayoutTurnout* theWrappedObject, QString  name);
   void setLayoutBlockDByName(LayoutTurnout* theWrappedObject, QString  name);
   void setLinkType(LayoutTurnout* theWrappedObject, int  type);
   void setLinkedTurnoutName(LayoutTurnout* theWrappedObject, QString  s);
   void setObjects(LayoutTurnout* theWrappedObject, LayoutEditor*  p);
   void setSecondTurnout(LayoutTurnout* theWrappedObject, QString  tName);
   void setSecondTurnoutInverted(LayoutTurnout* theWrappedObject, bool  inverted);
   void setSensorA(LayoutTurnout* theWrappedObject, QString  sensorName);
   void setSensorB(LayoutTurnout* theWrappedObject, QString  sensorName);
   void setSensorC(LayoutTurnout* theWrappedObject, QString  sensorName);
   void setSensorD(LayoutTurnout* theWrappedObject, QString  sensorName);
   void setSignalA1Name(LayoutTurnout* theWrappedObject, QString  signalHead);
   void setSignalA2Name(LayoutTurnout* theWrappedObject, QString  signalHead);
   void setSignalA3Name(LayoutTurnout* theWrappedObject, QString  signalHead);
   void setSignalAMast(LayoutTurnout* theWrappedObject, QString  signalMast);
   void setSignalB1Name(LayoutTurnout* theWrappedObject, QString  signalHead);
   void setSignalB2Name(LayoutTurnout* theWrappedObject, QString  signalHead);
   void setSignalBMast(LayoutTurnout* theWrappedObject, QString  signalMast);
   void setSignalC1Name(LayoutTurnout* theWrappedObject, QString  signalHead);
   void setSignalC2Name(LayoutTurnout* theWrappedObject, QString  signalHead);
   void setSignalCMast(LayoutTurnout* theWrappedObject, QString  signalMast);
   void setSignalD1Name(LayoutTurnout* theWrappedObject, QString  signalHead);
   void setSignalD2Name(LayoutTurnout* theWrappedObject, QString  signalHead);
   void setSignalDMast(LayoutTurnout* theWrappedObject, QString  signalMast);
   void setState(LayoutTurnout* theWrappedObject, int  state);
   void setTurnout(LayoutTurnout* theWrappedObject, QString  tName);
   void setVersion(LayoutTurnout* theWrappedObject, int  v);
   QMenu*  showPopup(LayoutTurnout* theWrappedObject, QGraphicsSceneMouseEvent*  e);
   QMenu*  py_q_showPopup(LayoutTurnout* theWrappedObject, QGraphicsSceneMouseEvent*  e){  return (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_showPopup(e));}
   QString  toString(LayoutTurnout* theWrappedObject);
   QString  py_q_toString(LayoutTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_toString());}
   void toggleTurnout(LayoutTurnout* theWrappedObject);
   bool  useBlockSpeed(LayoutTurnout* theWrappedObject);
    QString py_toString(LayoutTurnout*);
void py_set_blockBName(LayoutTurnout* theWrappedObject, QString  blockBName){ theWrappedObject->blockBName = blockBName; }
QString  py_get_blockBName(LayoutTurnout* theWrappedObject){ return theWrappedObject->blockBName; }
void py_set_blockCName(LayoutTurnout* theWrappedObject, QString  blockCName){ theWrappedObject->blockCName = blockCName; }
QString  py_get_blockCName(LayoutTurnout* theWrappedObject){ return theWrappedObject->blockCName; }
void py_set_blockDName(LayoutTurnout* theWrappedObject, QString  blockDName){ theWrappedObject->blockDName = blockDName; }
QString  py_get_blockDName(LayoutTurnout* theWrappedObject){ return theWrappedObject->blockDName; }
void py_set_blockName(LayoutTurnout* theWrappedObject, QString  blockName){ theWrappedObject->blockName = blockName; }
QString  py_get_blockName(LayoutTurnout* theWrappedObject){ return theWrappedObject->blockName; }
void py_set_connectA(LayoutTurnout* theWrappedObject, LayoutTrack*  connectA){ theWrappedObject->connectA = connectA; }
LayoutTrack*  py_get_connectA(LayoutTurnout* theWrappedObject){ return theWrappedObject->connectA; }
void py_set_connectAName(LayoutTurnout* theWrappedObject, QString  connectAName){ theWrappedObject->connectAName = connectAName; }
QString  py_get_connectAName(LayoutTurnout* theWrappedObject){ return theWrappedObject->connectAName; }
void py_set_connectB(LayoutTurnout* theWrappedObject, LayoutTrack*  connectB){ theWrappedObject->connectB = connectB; }
LayoutTrack*  py_get_connectB(LayoutTurnout* theWrappedObject){ return theWrappedObject->connectB; }
void py_set_connectBName(LayoutTurnout* theWrappedObject, QString  connectBName){ theWrappedObject->connectBName = connectBName; }
QString  py_get_connectBName(LayoutTurnout* theWrappedObject){ return theWrappedObject->connectBName; }
void py_set_connectC(LayoutTurnout* theWrappedObject, LayoutTrack*  connectC){ theWrappedObject->connectC = connectC; }
LayoutTrack*  py_get_connectC(LayoutTurnout* theWrappedObject){ return theWrappedObject->connectC; }
void py_set_connectCName(LayoutTurnout* theWrappedObject, QString  connectCName){ theWrappedObject->connectCName = connectCName; }
QString  py_get_connectCName(LayoutTurnout* theWrappedObject){ return theWrappedObject->connectCName; }
void py_set_connectD(LayoutTurnout* theWrappedObject, LayoutTrack*  connectD){ theWrappedObject->connectD = connectD; }
LayoutTrack*  py_get_connectD(LayoutTurnout* theWrappedObject){ return theWrappedObject->connectD; }
void py_set_connectDName(LayoutTurnout* theWrappedObject, QString  connectDName){ theWrappedObject->connectDName = connectDName; }
QString  py_get_connectDName(LayoutTurnout* theWrappedObject){ return theWrappedObject->connectDName; }
void py_set_continuingSense(LayoutTurnout* theWrappedObject, int  continuingSense){ theWrappedObject->continuingSense = continuingSense; }
int  py_get_continuingSense(LayoutTurnout* theWrappedObject){ return theWrappedObject->continuingSense; }
void py_set_disableWhenOccupied(LayoutTurnout* theWrappedObject, bool  disableWhenOccupied){ theWrappedObject->disableWhenOccupied = disableWhenOccupied; }
bool  py_get_disableWhenOccupied(LayoutTurnout* theWrappedObject){ return theWrappedObject->disableWhenOccupied; }
void py_set_disabled(LayoutTurnout* theWrappedObject, bool  disabled){ theWrappedObject->disabled = disabled; }
bool  py_get_disabled(LayoutTurnout* theWrappedObject){ return theWrappedObject->disabled; }
void py_set_dispA(LayoutTurnout* theWrappedObject, QPointF  dispA){ theWrappedObject->dispA = dispA; }
QPointF  py_get_dispA(LayoutTurnout* theWrappedObject){ return theWrappedObject->dispA; }
void py_set_dispB(LayoutTurnout* theWrappedObject, QPointF  dispB){ theWrappedObject->dispB = dispB; }
QPointF  py_get_dispB(LayoutTurnout* theWrappedObject){ return theWrappedObject->dispB; }
void py_set_itemGroup(LayoutTurnout* theWrappedObject, QGraphicsItemGroup*  itemGroup){ theWrappedObject->itemGroup = itemGroup; }
QGraphicsItemGroup*  py_get_itemGroup(LayoutTurnout* theWrappedObject){ return theWrappedObject->itemGroup; }
void py_set_linkType(LayoutTurnout* theWrappedObject, int  linkType){ theWrappedObject->linkType = linkType; }
int  py_get_linkType(LayoutTurnout* theWrappedObject){ return theWrappedObject->linkType; }
void py_set_linkedTurnoutName(LayoutTurnout* theWrappedObject, QString  linkedTurnoutName){ theWrappedObject->linkedTurnoutName = linkedTurnoutName; }
QString  py_get_linkedTurnoutName(LayoutTurnout* theWrappedObject){ return theWrappedObject->linkedTurnoutName; }
void py_set_pointA(LayoutTurnout* theWrappedObject, QPointF  pointA){ theWrappedObject->pointA = pointA; }
QPointF  py_get_pointA(LayoutTurnout* theWrappedObject){ return theWrappedObject->pointA; }
void py_set_pointB(LayoutTurnout* theWrappedObject, QPointF  pointB){ theWrappedObject->pointB = pointB; }
QPointF  py_get_pointB(LayoutTurnout* theWrappedObject){ return theWrappedObject->pointB; }
void py_set_pointC(LayoutTurnout* theWrappedObject, QPointF  pointC){ theWrappedObject->pointC = pointC; }
QPointF  py_get_pointC(LayoutTurnout* theWrappedObject){ return theWrappedObject->pointC; }
void py_set_pointD(LayoutTurnout* theWrappedObject, QPointF  pointD){ theWrappedObject->pointD = pointD; }
QPointF  py_get_pointD(LayoutTurnout* theWrappedObject){ return theWrappedObject->pointD; }
void py_set_secondTurnoutInverted(LayoutTurnout* theWrappedObject, bool  secondTurnoutInverted){ theWrappedObject->secondTurnoutInverted = secondTurnoutInverted; }
bool  py_get_secondTurnoutInverted(LayoutTurnout* theWrappedObject){ return theWrappedObject->secondTurnoutInverted; }
void py_set_secondTurnoutName(LayoutTurnout* theWrappedObject, QString  secondTurnoutName){ theWrappedObject->secondTurnoutName = secondTurnoutName; }
QString  py_get_secondTurnoutName(LayoutTurnout* theWrappedObject){ return theWrappedObject->secondTurnoutName; }
void py_set_signalA1Name(LayoutTurnout* theWrappedObject, QString  signalA1Name){ theWrappedObject->signalA1Name = signalA1Name; }
QString  py_get_signalA1Name(LayoutTurnout* theWrappedObject){ return theWrappedObject->signalA1Name; }
void py_set_signalA2Name(LayoutTurnout* theWrappedObject, QString  signalA2Name){ theWrappedObject->signalA2Name = signalA2Name; }
QString  py_get_signalA2Name(LayoutTurnout* theWrappedObject){ return theWrappedObject->signalA2Name; }
void py_set_signalA3Name(LayoutTurnout* theWrappedObject, QString  signalA3Name){ theWrappedObject->signalA3Name = signalA3Name; }
QString  py_get_signalA3Name(LayoutTurnout* theWrappedObject){ return theWrappedObject->signalA3Name; }
void py_set_signalAMast(LayoutTurnout* theWrappedObject, QString  signalAMast){ theWrappedObject->signalAMast = signalAMast; }
QString  py_get_signalAMast(LayoutTurnout* theWrappedObject){ return theWrappedObject->signalAMast; }
void py_set_signalB1Name(LayoutTurnout* theWrappedObject, QString  signalB1Name){ theWrappedObject->signalB1Name = signalB1Name; }
QString  py_get_signalB1Name(LayoutTurnout* theWrappedObject){ return theWrappedObject->signalB1Name; }
void py_set_signalB2Name(LayoutTurnout* theWrappedObject, QString  signalB2Name){ theWrappedObject->signalB2Name = signalB2Name; }
QString  py_get_signalB2Name(LayoutTurnout* theWrappedObject){ return theWrappedObject->signalB2Name; }
void py_set_signalBMast(LayoutTurnout* theWrappedObject, QString  signalBMast){ theWrappedObject->signalBMast = signalBMast; }
QString  py_get_signalBMast(LayoutTurnout* theWrappedObject){ return theWrappedObject->signalBMast; }
void py_set_signalC1Name(LayoutTurnout* theWrappedObject, QString  signalC1Name){ theWrappedObject->signalC1Name = signalC1Name; }
QString  py_get_signalC1Name(LayoutTurnout* theWrappedObject){ return theWrappedObject->signalC1Name; }
void py_set_signalC2Name(LayoutTurnout* theWrappedObject, QString  signalC2Name){ theWrappedObject->signalC2Name = signalC2Name; }
QString  py_get_signalC2Name(LayoutTurnout* theWrappedObject){ return theWrappedObject->signalC2Name; }
void py_set_signalCMast(LayoutTurnout* theWrappedObject, QString  signalCMast){ theWrappedObject->signalCMast = signalCMast; }
QString  py_get_signalCMast(LayoutTurnout* theWrappedObject){ return theWrappedObject->signalCMast; }
void py_set_signalD1Name(LayoutTurnout* theWrappedObject, QString  signalD1Name){ theWrappedObject->signalD1Name = signalD1Name; }
QString  py_get_signalD1Name(LayoutTurnout* theWrappedObject){ return theWrappedObject->signalD1Name; }
void py_set_signalD2Name(LayoutTurnout* theWrappedObject, QString  signalD2Name){ theWrappedObject->signalD2Name = signalD2Name; }
QString  py_get_signalD2Name(LayoutTurnout* theWrappedObject){ return theWrappedObject->signalD2Name; }
void py_set_signalDMast(LayoutTurnout* theWrappedObject, QString  signalDMast){ theWrappedObject->signalDMast = signalDMast; }
QString  py_get_signalDMast(LayoutTurnout* theWrappedObject){ return theWrappedObject->signalDMast; }
void py_set_tBlockAName(LayoutTurnout* theWrappedObject, QString  tBlockAName){ theWrappedObject->tBlockAName = tBlockAName; }
QString  py_get_tBlockAName(LayoutTurnout* theWrappedObject){ return theWrappedObject->tBlockAName; }
void py_set_tBlockBName(LayoutTurnout* theWrappedObject, QString  tBlockBName){ theWrappedObject->tBlockBName = tBlockBName; }
QString  py_get_tBlockBName(LayoutTurnout* theWrappedObject){ return theWrappedObject->tBlockBName; }
void py_set_tBlockCName(LayoutTurnout* theWrappedObject, QString  tBlockCName){ theWrappedObject->tBlockCName = tBlockCName; }
QString  py_get_tBlockCName(LayoutTurnout* theWrappedObject){ return theWrappedObject->tBlockCName; }
void py_set_tBlockDName(LayoutTurnout* theWrappedObject, QString  tBlockDName){ theWrappedObject->tBlockDName = tBlockDName; }
QString  py_get_tBlockDName(LayoutTurnout* theWrappedObject){ return theWrappedObject->tBlockDName; }
void py_set_turnoutName(LayoutTurnout* theWrappedObject, QString  turnoutName){ theWrappedObject->turnoutName = turnoutName; }
QString  py_get_turnoutName(LayoutTurnout* theWrappedObject){ return theWrappedObject->turnoutName; }
};





class PythonQtShell_Light : public Light
{
public:
    PythonQtShell_Light(QObject*  parent = 0):Light(parent),_wrapper(NULL) {}
    PythonQtShell_Light(QString  sysName, QObject*  parent = 0):Light(sysName, parent),_wrapper(NULL) {}
    PythonQtShell_Light(QString  sysName, QString  userName, QObject*  parent = 0):Light(sysName, userName, parent),_wrapper(NULL) {}

   ~PythonQtShell_Light();

virtual void activateLight();
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(PropertyChangeListener*  l, QString  beanRef, const QString  listenerRef);
virtual void addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  l, QString  beanRef, QString  listenerRef);
virtual void addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual void childEvent(QChildEvent*  event);
virtual void clearLightControls();
virtual int  compareSystemNameSuffix(QString  suffix1, QString  suffix2, NamedBean*  n);
virtual int  compareTo(NamedBean*  n2);
virtual void customEvent(QEvent*  event);
virtual void deactivateLight();
virtual QString  describeState(int  state);
virtual void dispose();
virtual bool  equals(QObject*  obj);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual QString  getBeanType();
virtual QString  getComment();
virtual double  getCurrentIntensity();
virtual QString  getDisplayName();
virtual bool  getEnabled();
virtual QString  getFullyFormattedDisplayName();
virtual QString  getListenerRef(PropertyChangeListener*  l);
virtual QList<QString >*  getListenerRefs();
virtual double  getMaxIntensity();
virtual double  getMinIntensity();
virtual int  getNumPropertyChangeListeners();
virtual QVariant  getProperty(QString  key);
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners();
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners(QString  name);
virtual QVector<PropertyChangeListener* >  getPropertyChangeListenersByReference(QString  propertyName);
virtual QSet<QString >  getPropertyKeys();
virtual int  getState();
virtual QString  getSystemName() const;
virtual double  getTargetIntensity();
virtual double  getTransitionTime();
virtual QString  getUserName() const;
virtual uint  hashCode();
virtual bool  isIntensityVariable();
virtual bool  isTransitionAvailable();
virtual bool  isTransitioning();
virtual void removeProperty(QString  key);
virtual void removePropertyChangeListener(PropertyChangeListener*  listener);
virtual void removePropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual void setComment(QString  comment);
virtual void setEnabled(bool  arg__1);
virtual void setMaxIntensity(double  arg__1);
virtual void setMinIntensity(double  arg__1);
virtual void setProperty(QString  key, QVariant  value);
virtual void setState(int  arg__1);
virtual void setTargetIntensity(double  arg__1);
virtual void setTransitionTime(double  arg__1);
virtual void setUserName(QString  s) throw (NamedBean::BadUserNameException) ;
virtual void timerEvent(QTimerEvent*  event);
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);
virtual void vetoableChange(PropertyChangeEvent*  evt) throw (PropertyVetoException) ;

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_Light : public Light
{ public:
inline void py_q_activateLight() { Light::activateLight(); }
inline void py_q_clearLightControls() { Light::clearLightControls(); }
inline void py_q_deactivateLight() { Light::deactivateLight(); }
inline double  py_q_getCurrentIntensity() { return Light::getCurrentIntensity(); }
inline bool  py_q_getEnabled() { return Light::getEnabled(); }
inline double  py_q_getMaxIntensity() { return Light::getMaxIntensity(); }
inline double  py_q_getMinIntensity() { return this->getMinIntensity(); }
inline int  py_q_getState() { return Light::getState(); }
inline double  py_q_getTargetIntensity() { return Light::getTargetIntensity(); }
inline double  py_q_getTransitionTime() { return Light::getTransitionTime(); }
inline bool  py_q_isIntensityVariable() { return Light::isIntensityVariable(); }
inline bool  py_q_isTransitionAvailable() { return Light::isTransitionAvailable(); }
inline bool  py_q_isTransitioning() { return Light::isTransitioning(); }
inline void py_q_setEnabled(bool  arg__1) { Light::setEnabled(arg__1); }
inline void py_q_setMaxIntensity(double  arg__1) { Light::setMaxIntensity(arg__1); }
inline void py_q_setMinIntensity(double  arg__1) { Light::setMinIntensity(arg__1); }
inline void py_q_setState(int  arg__1) { Light::setState(arg__1); }
inline void py_q_setTargetIntensity(double  arg__1) { Light::setTargetIntensity(arg__1); }
inline void py_q_setTransitionTime(double  arg__1) { Light::setTransitionTime(arg__1); }
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
   void py_q_activateLight(Light* theWrappedObject){  (((PythonQtPublicPromoter_Light*)theWrappedObject)->py_q_activateLight());}
   void clearLightControls(Light* theWrappedObject);
   void py_q_clearLightControls(Light* theWrappedObject){  (((PythonQtPublicPromoter_Light*)theWrappedObject)->py_q_clearLightControls());}
   void deactivateLight(Light* theWrappedObject);
   void py_q_deactivateLight(Light* theWrappedObject){  (((PythonQtPublicPromoter_Light*)theWrappedObject)->py_q_deactivateLight());}
   double  getCurrentIntensity(Light* theWrappedObject);
   double  py_q_getCurrentIntensity(Light* theWrappedObject){  return (((PythonQtPublicPromoter_Light*)theWrappedObject)->py_q_getCurrentIntensity());}
   bool  getEnabled(Light* theWrappedObject);
   bool  py_q_getEnabled(Light* theWrappedObject){  return (((PythonQtPublicPromoter_Light*)theWrappedObject)->py_q_getEnabled());}
   double  getMaxIntensity(Light* theWrappedObject);
   double  py_q_getMaxIntensity(Light* theWrappedObject){  return (((PythonQtPublicPromoter_Light*)theWrappedObject)->py_q_getMaxIntensity());}
   double  getMinIntensity(Light* theWrappedObject);
   double  py_q_getMinIntensity(Light* theWrappedObject){  return (((PythonQtPublicPromoter_Light*)theWrappedObject)->py_q_getMinIntensity());}
   int  py_q_getState(Light* theWrappedObject){  return (((PythonQtPublicPromoter_Light*)theWrappedObject)->py_q_getState());}
   double  getTargetIntensity(Light* theWrappedObject);
   double  py_q_getTargetIntensity(Light* theWrappedObject){  return (((PythonQtPublicPromoter_Light*)theWrappedObject)->py_q_getTargetIntensity());}
   double  getTransitionTime(Light* theWrappedObject);
   double  py_q_getTransitionTime(Light* theWrappedObject){  return (((PythonQtPublicPromoter_Light*)theWrappedObject)->py_q_getTransitionTime());}
   bool  isIntensityVariable(Light* theWrappedObject);
   bool  py_q_isIntensityVariable(Light* theWrappedObject){  return (((PythonQtPublicPromoter_Light*)theWrappedObject)->py_q_isIntensityVariable());}
   bool  isTransitionAvailable(Light* theWrappedObject);
   bool  py_q_isTransitionAvailable(Light* theWrappedObject){  return (((PythonQtPublicPromoter_Light*)theWrappedObject)->py_q_isTransitionAvailable());}
   bool  isTransitioning(Light* theWrappedObject);
   bool  py_q_isTransitioning(Light* theWrappedObject){  return (((PythonQtPublicPromoter_Light*)theWrappedObject)->py_q_isTransitioning());}
   void setEnabled(Light* theWrappedObject, bool  arg__1);
   void py_q_setEnabled(Light* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Light*)theWrappedObject)->py_q_setEnabled(arg__1));}
   void setMaxIntensity(Light* theWrappedObject, double  arg__1);
   void py_q_setMaxIntensity(Light* theWrappedObject, double  arg__1){  (((PythonQtPublicPromoter_Light*)theWrappedObject)->py_q_setMaxIntensity(arg__1));}
   void setMinIntensity(Light* theWrappedObject, double  arg__1);
   void py_q_setMinIntensity(Light* theWrappedObject, double  arg__1){  (((PythonQtPublicPromoter_Light*)theWrappedObject)->py_q_setMinIntensity(arg__1));}
   void py_q_setState(Light* theWrappedObject, int  arg__1){  (((PythonQtPublicPromoter_Light*)theWrappedObject)->py_q_setState(arg__1));}
   void setTargetIntensity(Light* theWrappedObject, double  arg__1);
   void py_q_setTargetIntensity(Light* theWrappedObject, double  arg__1){  (((PythonQtPublicPromoter_Light*)theWrappedObject)->py_q_setTargetIntensity(arg__1));}
   void setTransitionTime(Light* theWrappedObject, double  arg__1);
   void py_q_setTransitionTime(Light* theWrappedObject, double  arg__1){  (((PythonQtPublicPromoter_Light*)theWrappedObject)->py_q_setTransitionTime(arg__1));}
};





class PythonQtShell_LightManager : public LightManager
{
public:
    PythonQtShell_LightManager(SystemConnectionMemo*  memo, QObject*  parent = 0):LightManager(memo, parent),_wrapper(NULL) {}

   ~PythonQtShell_LightManager();

virtual void Register(NamedBean*  s) const;
virtual void activateAllLights();
virtual void addDataListener(QObject*  e);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual bool  allowMultipleAdditions(QString  arg__1);
virtual void childEvent(QChildEvent*  event);
virtual QString  convertSystemNameToAlternate(QString  arg__1);
virtual void customEvent(QEvent*  event);
virtual void deleteBean(NamedBean*  arg__1, QString  arg__2) throw (PropertyVetoException) ;
virtual void deregister(NamedBean*  s) const;
virtual void dispose();
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual NamedBean*  getBeanBySystemName(QString  systemName) const;
virtual NamedBean*  getBeanByUserName(QString  arg__1) const;
virtual QString  getBeanTypeHandled(bool  plural) const;
virtual Light*  getBySystemName(QString  arg__1) const;
virtual Light*  getByUserName(QString  arg__1) const;
virtual QString  getEntryToolTip();
virtual Light*  getLight(QString  arg__1);
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
virtual Light*  newLight(QString  arg__1, QString  arg__2);
virtual QString  normalizeSystemName(QString  arg__1);
virtual void propertyChange(PropertyChangeEvent*  e);
virtual Light*  provide(QString  name) throw (IllegalArgumentException)
;
virtual Light*  provideLight(QString  arg__1);
virtual void removeDataListener(QObject*  e);
virtual void removePropertyChangeListener(PropertyChangeListener*  l);
virtual void removePropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual bool  supportsVariableLights(QString  arg__1);
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

class PythonQtPublicPromoter_LightManager : public LightManager
{ public:
inline void py_q_activateAllLights() { LightManager::activateAllLights(); }
inline bool  py_q_allowMultipleAdditions(QString  arg__1) { return LightManager::allowMultipleAdditions(arg__1); }
inline QString  py_q_convertSystemNameToAlternate(QString  arg__1) { return LightManager::convertSystemNameToAlternate(arg__1); }
inline void py_q_dispose() { LightManager::dispose(); }
inline Light*  py_q_getBySystemName(QString  arg__1) const { return this->getBySystemName(arg__1); }
inline Light*  py_q_getByUserName(QString  arg__1) const { return this->getByUserName(arg__1); }
inline Light*  py_q_getLight(QString  arg__1) { return LightManager::getLight(arg__1); }
inline Light*  py_q_newLight(QString  arg__1, QString  arg__2) { return this->newLight(arg__1, arg__2); }
inline QString  py_q_normalizeSystemName(QString  arg__1) { return LightManager::normalizeSystemName(arg__1); }
inline Light*  py_q_provide(QString  name) throw (IllegalArgumentException)
 { return LightManager::provide(name); }
inline Light*  py_q_provideLight(QString  arg__1) { return LightManager::provideLight(arg__1); }
inline bool  py_q_supportsVariableLights(QString  arg__1) { return LightManager::supportsVariableLights(arg__1); }
inline QString  py_q_toString() { return LightManager::toString(); }
inline bool  py_q_validSystemNameConfig(QString  arg__1) const { return LightManager::validSystemNameConfig(arg__1); }
};

class PythonQtWrapper_LightManager : public QObject
{ Q_OBJECT
public:
public slots:
LightManager* new_LightManager(SystemConnectionMemo*  memo, QObject*  parent = 0);
void delete_LightManager(LightManager* obj) { delete obj; } 
   void activateAllLights(LightManager* theWrappedObject);
   void py_q_activateAllLights(LightManager* theWrappedObject){  (((PythonQtPublicPromoter_LightManager*)theWrappedObject)->py_q_activateAllLights());}
   bool  allowMultipleAdditions(LightManager* theWrappedObject, QString  arg__1);
   bool  py_q_allowMultipleAdditions(LightManager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_LightManager*)theWrappedObject)->py_q_allowMultipleAdditions(arg__1));}
   QString  convertSystemNameToAlternate(LightManager* theWrappedObject, QString  arg__1);
   QString  py_q_convertSystemNameToAlternate(LightManager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_LightManager*)theWrappedObject)->py_q_convertSystemNameToAlternate(arg__1));}
   void py_q_dispose(LightManager* theWrappedObject){  (((PythonQtPublicPromoter_LightManager*)theWrappedObject)->py_q_dispose());}
   Light*  getBySystemName(LightManager* theWrappedObject, QString  arg__1) const;
   Light*  py_q_getBySystemName(LightManager* theWrappedObject, QString  arg__1) const{  return (((PythonQtPublicPromoter_LightManager*)theWrappedObject)->py_q_getBySystemName(arg__1));}
   Light*  getByUserName(LightManager* theWrappedObject, QString  arg__1) const;
   Light*  py_q_getByUserName(LightManager* theWrappedObject, QString  arg__1) const{  return (((PythonQtPublicPromoter_LightManager*)theWrappedObject)->py_q_getByUserName(arg__1));}
   Light*  getLight(LightManager* theWrappedObject, QString  arg__1);
   Light*  py_q_getLight(LightManager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_LightManager*)theWrappedObject)->py_q_getLight(arg__1));}
   Light*  newLight(LightManager* theWrappedObject, QString  arg__1, QString  arg__2);
   Light*  py_q_newLight(LightManager* theWrappedObject, QString  arg__1, QString  arg__2){  return (((PythonQtPublicPromoter_LightManager*)theWrappedObject)->py_q_newLight(arg__1, arg__2));}
   QString  py_q_normalizeSystemName(LightManager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_LightManager*)theWrappedObject)->py_q_normalizeSystemName(arg__1));}
   Light*  provide(LightManager* theWrappedObject, QString  name) throw (IllegalArgumentException)
;
   Light*  py_q_provide(LightManager* theWrappedObject, QString  name) throw (IllegalArgumentException)
{  return (((PythonQtPublicPromoter_LightManager*)theWrappedObject)->py_q_provide(name));}
   Light*  provideLight(LightManager* theWrappedObject, QString  arg__1);
   Light*  py_q_provideLight(LightManager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_LightManager*)theWrappedObject)->py_q_provideLight(arg__1));}
   bool  supportsVariableLights(LightManager* theWrappedObject, QString  arg__1);
   bool  py_q_supportsVariableLights(LightManager* theWrappedObject, QString  arg__1){  return (((PythonQtPublicPromoter_LightManager*)theWrappedObject)->py_q_supportsVariableLights(arg__1));}
   QString  py_q_toString(LightManager* theWrappedObject){  return (((PythonQtPublicPromoter_LightManager*)theWrappedObject)->py_q_toString());}
   bool  validSystemNameConfig(LightManager* theWrappedObject, QString  arg__1) const;
   bool  py_q_validSystemNameConfig(LightManager* theWrappedObject, QString  arg__1) const{  return (((PythonQtPublicPromoter_LightManager*)theWrappedObject)->py_q_validSystemNameConfig(arg__1));}
    QString py_toString(LightManager*);
};





class PythonQtShell_ListSelectionModel : public ListSelectionModel
{
public:
    PythonQtShell_ListSelectionModel():ListSelectionModel(),_wrapper(NULL) {}

   ~PythonQtShell_ListSelectionModel();

virtual void addSelectionInterval(int  index0, int  index1);
virtual void clearSelection();
virtual int  getAnchorSelectionIndex();
virtual int  getLeadSelectionIndex();
virtual int  getMaxSelectionIndex();
virtual int  getMinSelectionIndex();
virtual int  getSelectionMode();
virtual bool  getValueIsAdjusting();
virtual void insertIndexInterval(int  arg__1, int  arg__2, bool  arg__3);
virtual bool  isSelectedIndex(int  index);
virtual bool  isSelectionEmpty();
virtual void removeIndexInterval(int  arg__1, int  arg__2);
virtual void removeSelectionInterval(int  arg__1, int  arg__2);
virtual void setAnchorSelectionIndex(int  arg__1);
virtual void setLeadSelectionIndex(int  arg__1);
virtual void setSelectionInterval(int  index0, int  index1);
virtual void setSelectionMode(int  arg__1);
virtual void setValueIsAdjusting(bool  arg__1);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_ListSelectionModel : public ListSelectionModel
{ public:
inline void py_q_addSelectionInterval(int  index0, int  index1) { this->addSelectionInterval(index0, index1); }
inline void py_q_clearSelection() { ListSelectionModel::clearSelection(); }
inline int  py_q_getAnchorSelectionIndex() { return ListSelectionModel::getAnchorSelectionIndex(); }
inline int  py_q_getLeadSelectionIndex() { return ListSelectionModel::getLeadSelectionIndex(); }
inline int  py_q_getMaxSelectionIndex() { return ListSelectionModel::getMaxSelectionIndex(); }
inline int  py_q_getMinSelectionIndex() { return ListSelectionModel::getMinSelectionIndex(); }
inline int  py_q_getSelectionMode() { return ListSelectionModel::getSelectionMode(); }
inline bool  py_q_getValueIsAdjusting() { return ListSelectionModel::getValueIsAdjusting(); }
inline void py_q_insertIndexInterval(int  arg__1, int  arg__2, bool  arg__3) { ListSelectionModel::insertIndexInterval(arg__1, arg__2, arg__3); }
inline bool  py_q_isSelectedIndex(int  index) { return this->isSelectedIndex(index); }
inline bool  py_q_isSelectionEmpty() { return ListSelectionModel::isSelectionEmpty(); }
inline void py_q_removeIndexInterval(int  arg__1, int  arg__2) { ListSelectionModel::removeIndexInterval(arg__1, arg__2); }
inline void py_q_removeSelectionInterval(int  arg__1, int  arg__2) { ListSelectionModel::removeSelectionInterval(arg__1, arg__2); }
inline void py_q_setAnchorSelectionIndex(int  arg__1) { ListSelectionModel::setAnchorSelectionIndex(arg__1); }
inline void py_q_setLeadSelectionIndex(int  arg__1) { ListSelectionModel::setLeadSelectionIndex(arg__1); }
inline void py_q_setSelectionInterval(int  index0, int  index1) { this->setSelectionInterval(index0, index1); }
inline void py_q_setSelectionMode(int  arg__1) { ListSelectionModel::setSelectionMode(arg__1); }
inline void py_q_setValueIsAdjusting(bool  arg__1) { ListSelectionModel::setValueIsAdjusting(arg__1); }
};

class PythonQtWrapper_ListSelectionModel : public QObject
{ Q_OBJECT
public:
Q_ENUMS(SELECTIONS )
enum SELECTIONS{
  SINGLE_SELECTION = ListSelectionModel::SINGLE_SELECTION,   SINGLE_INTERVAL_SELECTION = ListSelectionModel::SINGLE_INTERVAL_SELECTION,   MULTIPLE_INTERVAL_SELECTION = ListSelectionModel::MULTIPLE_INTERVAL_SELECTION};
public slots:
ListSelectionModel* new_ListSelectionModel();
void delete_ListSelectionModel(ListSelectionModel* obj) { delete obj; } 
   void addSelectionInterval(ListSelectionModel* theWrappedObject, int  index0, int  index1);
   void py_q_addSelectionInterval(ListSelectionModel* theWrappedObject, int  index0, int  index1){  (((PythonQtPublicPromoter_ListSelectionModel*)theWrappedObject)->py_q_addSelectionInterval(index0, index1));}
   void clearSelection(ListSelectionModel* theWrappedObject);
   void py_q_clearSelection(ListSelectionModel* theWrappedObject){  (((PythonQtPublicPromoter_ListSelectionModel*)theWrappedObject)->py_q_clearSelection());}
   int  getAnchorSelectionIndex(ListSelectionModel* theWrappedObject);
   int  py_q_getAnchorSelectionIndex(ListSelectionModel* theWrappedObject){  return (((PythonQtPublicPromoter_ListSelectionModel*)theWrappedObject)->py_q_getAnchorSelectionIndex());}
   int  getLeadSelectionIndex(ListSelectionModel* theWrappedObject);
   int  py_q_getLeadSelectionIndex(ListSelectionModel* theWrappedObject){  return (((PythonQtPublicPromoter_ListSelectionModel*)theWrappedObject)->py_q_getLeadSelectionIndex());}
   int  getMaxSelectionIndex(ListSelectionModel* theWrappedObject);
   int  py_q_getMaxSelectionIndex(ListSelectionModel* theWrappedObject){  return (((PythonQtPublicPromoter_ListSelectionModel*)theWrappedObject)->py_q_getMaxSelectionIndex());}
   int  getMinSelectionIndex(ListSelectionModel* theWrappedObject);
   int  py_q_getMinSelectionIndex(ListSelectionModel* theWrappedObject){  return (((PythonQtPublicPromoter_ListSelectionModel*)theWrappedObject)->py_q_getMinSelectionIndex());}
   int  getSelectionMode(ListSelectionModel* theWrappedObject);
   int  py_q_getSelectionMode(ListSelectionModel* theWrappedObject){  return (((PythonQtPublicPromoter_ListSelectionModel*)theWrappedObject)->py_q_getSelectionMode());}
   bool  getValueIsAdjusting(ListSelectionModel* theWrappedObject);
   bool  py_q_getValueIsAdjusting(ListSelectionModel* theWrappedObject){  return (((PythonQtPublicPromoter_ListSelectionModel*)theWrappedObject)->py_q_getValueIsAdjusting());}
   void insertIndexInterval(ListSelectionModel* theWrappedObject, int  arg__1, int  arg__2, bool  arg__3);
   void py_q_insertIndexInterval(ListSelectionModel* theWrappedObject, int  arg__1, int  arg__2, bool  arg__3){  (((PythonQtPublicPromoter_ListSelectionModel*)theWrappedObject)->py_q_insertIndexInterval(arg__1, arg__2, arg__3));}
   bool  isSelectedIndex(ListSelectionModel* theWrappedObject, int  index);
   bool  py_q_isSelectedIndex(ListSelectionModel* theWrappedObject, int  index){  return (((PythonQtPublicPromoter_ListSelectionModel*)theWrappedObject)->py_q_isSelectedIndex(index));}
   bool  isSelectionEmpty(ListSelectionModel* theWrappedObject);
   bool  py_q_isSelectionEmpty(ListSelectionModel* theWrappedObject){  return (((PythonQtPublicPromoter_ListSelectionModel*)theWrappedObject)->py_q_isSelectionEmpty());}
   void removeIndexInterval(ListSelectionModel* theWrappedObject, int  arg__1, int  arg__2);
   void py_q_removeIndexInterval(ListSelectionModel* theWrappedObject, int  arg__1, int  arg__2){  (((PythonQtPublicPromoter_ListSelectionModel*)theWrappedObject)->py_q_removeIndexInterval(arg__1, arg__2));}
   void removeSelectionInterval(ListSelectionModel* theWrappedObject, int  arg__1, int  arg__2);
   void py_q_removeSelectionInterval(ListSelectionModel* theWrappedObject, int  arg__1, int  arg__2){  (((PythonQtPublicPromoter_ListSelectionModel*)theWrappedObject)->py_q_removeSelectionInterval(arg__1, arg__2));}
   void setAnchorSelectionIndex(ListSelectionModel* theWrappedObject, int  arg__1);
   void py_q_setAnchorSelectionIndex(ListSelectionModel* theWrappedObject, int  arg__1){  (((PythonQtPublicPromoter_ListSelectionModel*)theWrappedObject)->py_q_setAnchorSelectionIndex(arg__1));}
   void setLeadSelectionIndex(ListSelectionModel* theWrappedObject, int  arg__1);
   void py_q_setLeadSelectionIndex(ListSelectionModel* theWrappedObject, int  arg__1){  (((PythonQtPublicPromoter_ListSelectionModel*)theWrappedObject)->py_q_setLeadSelectionIndex(arg__1));}
   void setSelectionInterval(ListSelectionModel* theWrappedObject, int  index0, int  index1);
   void py_q_setSelectionInterval(ListSelectionModel* theWrappedObject, int  index0, int  index1){  (((PythonQtPublicPromoter_ListSelectionModel*)theWrappedObject)->py_q_setSelectionInterval(index0, index1));}
   void setSelectionMode(ListSelectionModel* theWrappedObject, int  arg__1);
   void py_q_setSelectionMode(ListSelectionModel* theWrappedObject, int  arg__1){  (((PythonQtPublicPromoter_ListSelectionModel*)theWrappedObject)->py_q_setSelectionMode(arg__1));}
   void setValueIsAdjusting(ListSelectionModel* theWrappedObject, bool  arg__1);
   void py_q_setValueIsAdjusting(ListSelectionModel* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_ListSelectionModel*)theWrappedObject)->py_q_setValueIsAdjusting(arg__1));}
};





class PythonQtWrapper_LnCommandStationType : public QObject
{ Q_OBJECT
public:
Q_ENUMS(LnCommandStationTypes )
enum LnCommandStationTypes{
  COMMAND_STATION_UNKNOWN = LnCommandStationType::COMMAND_STATION_UNKNOWN,   COMMAND_STATION_DCS100 = LnCommandStationType::COMMAND_STATION_DCS100,   COMMAND_STATION_DCS200 = LnCommandStationType::COMMAND_STATION_DCS200,   COMMAND_STATION_DCS240 = LnCommandStationType::COMMAND_STATION_DCS240,   COMMAND_STATION_DCS210 = LnCommandStationType::COMMAND_STATION_DCS210,   COMMAND_STATION_DCS050 = LnCommandStationType::COMMAND_STATION_DCS050,   COMMAND_STATION_DCS051 = LnCommandStationType::COMMAND_STATION_DCS051,   COMMAND_STATION_DCS052 = LnCommandStationType::COMMAND_STATION_DCS052,   COMMAND_STATION_DB150 = LnCommandStationType::COMMAND_STATION_DB150,   COMMAND_STATION_LBPS = LnCommandStationType::COMMAND_STATION_LBPS,   COMMAND_STATION_MM = LnCommandStationType::COMMAND_STATION_MM,   COMMAND_STATION_IBX_TYPE_1 = LnCommandStationType::COMMAND_STATION_IBX_TYPE_1,   COMMAND_STATION_IBX_TYPE_2 = LnCommandStationType::COMMAND_STATION_IBX_TYPE_2,   COMMAND_STATION_LOCOCENTRAL = LnCommandStationType::COMMAND_STATION_LOCOCENTRAL,   COMMAND_STATION_PR3_ALONE = LnCommandStationType::COMMAND_STATION_PR3_ALONE,   COMMAND_STATION_PR2_ALONE = LnCommandStationType::COMMAND_STATION_PR2_ALONE,   COMMAND_STATION_STANDALONE = LnCommandStationType::COMMAND_STATION_STANDALONE,   COMMAND_STATION_PR4_ALONE = LnCommandStationType::COMMAND_STATION_PR4_ALONE,   COMMAND_STATION_USB_DCS240_ALONE = LnCommandStationType::COMMAND_STATION_USB_DCS240_ALONE,   COMMAND_STATION_USB_DCS52_ALONE = LnCommandStationType::COMMAND_STATION_USB_DCS52_ALONE};
public slots:
void delete_LnCommandStationType(LnCommandStationType* obj) { delete obj; } 
   QStringList  static_LnCommandStationType_commandStationNames();
   bool  equals(LnCommandStationType* theWrappedObject, LnCommandStationType*  other);
   LnCommandStationType*  static_LnCommandStationType_getByName(QString  name);
   LnCommandStationType*  static_LnCommandStationType_getByType(LnCommandStationType::LnCommandStationTypes  type);
   bool  getCanRead(LnCommandStationType* theWrappedObject);
   bool  getImplementsIdle(LnCommandStationType* theWrappedObject);
   QString  getName(LnCommandStationType* theWrappedObject);
   bool  getProgPowersOff(LnCommandStationType* theWrappedObject);
   bool  getSupportsLocoReset(LnCommandStationType* theWrappedObject);
   bool  getSupportsMultimeter(LnCommandStationType* theWrappedObject);
   ThrottleManager*  getThrottleManager(LnCommandStationType* theWrappedObject, LocoNetSystemConnectionMemo*  memo);
   LnCommandStationType::LnCommandStationTypes  getType(LnCommandStationType* theWrappedObject);
   QString  toString(LnCommandStationType* theWrappedObject);
    QString py_toString(LnCommandStationType*);
};





class PythonQtShell_LnPacketizer : public LnPacketizer
{
public:
    PythonQtShell_LnPacketizer(LocoNetSystemConnectionMemo*  m, QObject*  parent = 0):LnPacketizer(m, parent),_wrapper(NULL) {}

   ~PythonQtShell_LnPacketizer();

virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual LocoNetSystemConnectionMemo*  getSystemConnectionMemo();
virtual bool  isXmtBusy();
virtual void sendLocoNetMessage(LocoNetMessage*  m);
virtual void setSystemConnectionMemo(LocoNetSystemConnectionMemo*  m);
virtual bool  status();
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_LnPacketizer : public LnPacketizer
{ public:
inline bool  py_q_isXmtBusy() { return LnPacketizer::isXmtBusy(); }
inline void py_q_sendLocoNetMessage(LocoNetMessage*  m) { LnPacketizer::sendLocoNetMessage(m); }
inline bool  py_q_status() { return LnPacketizer::status(); }
};

class PythonQtWrapper_LnPacketizer : public QObject
{ Q_OBJECT
public:
public slots:
LnPacketizer* new_LnPacketizer(LocoNetSystemConnectionMemo*  m, QObject*  parent = 0);
void delete_LnPacketizer(LnPacketizer* obj) { delete obj; } 
   void connectPort(LnPacketizer* theWrappedObject, LnPortController*  p);
   void disconnectPort(LnPacketizer* theWrappedObject, LnPortController*  p);
   QString  static_LnPacketizer_hexStringFromBytes(const QByteArray&  a);
   bool  py_q_isXmtBusy(LnPacketizer* theWrappedObject){  return (((PythonQtPublicPromoter_LnPacketizer*)theWrappedObject)->py_q_isXmtBusy());}
   void py_q_sendLocoNetMessage(LnPacketizer* theWrappedObject, LocoNetMessage*  m){  (((PythonQtPublicPromoter_LnPacketizer*)theWrappedObject)->py_q_sendLocoNetMessage(m));}
   void startThreads(LnPacketizer* theWrappedObject);
   bool  py_q_status(LnPacketizer* theWrappedObject){  return (((PythonQtPublicPromoter_LnPacketizer*)theWrappedObject)->py_q_status());}
void py_set_baStream(LnPacketizer* theWrappedObject, QByteArray*  baStream){ theWrappedObject->baStream = baStream; }
QByteArray*  py_get_baStream(LnPacketizer* theWrappedObject){ return theWrappedObject->baStream; }
void py_set_controller(LnPacketizer* theWrappedObject, LnPortController*  controller){ theWrappedObject->controller = controller; }
LnPortController*  py_get_controller(LnPacketizer* theWrappedObject){ return theWrappedObject->controller; }
void py_set_istream(LnPacketizer* theWrappedObject, QDataStream*  istream){ theWrappedObject->istream = istream; }
QDataStream*  py_get_istream(LnPacketizer* theWrappedObject){ return theWrappedObject->istream; }
void py_set_ostream(LnPacketizer* theWrappedObject, QDataStream*  ostream){ theWrappedObject->ostream = ostream; }
QDataStream*  py_get_ostream(LnPacketizer* theWrappedObject){ return theWrappedObject->ostream; }
void py_set_rcvThread(LnPacketizer* theWrappedObject, QThread*  rcvThread){ theWrappedObject->rcvThread = rcvThread; }
QThread*  py_get_rcvThread(LnPacketizer* theWrappedObject){ return theWrappedObject->rcvThread; }
void py_set_xmtList(LnPacketizer* theWrappedObject, QLinkedList<QByteArray* >*  xmtList){ theWrappedObject->xmtList = xmtList; }
QLinkedList<QByteArray* >*  py_get_xmtList(LnPacketizer* theWrappedObject){ return theWrappedObject->xmtList; }
void py_set_xmtThread(LnPacketizer* theWrappedObject, QThread*  xmtThread){ theWrappedObject->xmtThread = xmtThread; }
QThread*  py_get_xmtThread(LnPacketizer* theWrappedObject){ return theWrappedObject->xmtThread; }
};





class PythonQtShell_LnPortController : public LnPortController
{
public:
    PythonQtShell_LnPortController(LocoNetSystemConnectionMemo*  connectionMemo, QObject*  parent = 0):LnPortController(connectionMemo, parent),_wrapper(NULL) {}

   ~PythonQtShell_LnPortController();

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
virtual SystemConnectionMemo*  getSystemConnectionMemo();
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

class PythonQtPublicPromoter_LnPortController : public LnPortController
{ public:
inline QDataStream*  py_q_getInputStream() { return LnPortController::getInputStream(); }
inline QDataStream*  py_q_getOutputStream() { return LnPortController::getOutputStream(); }
inline SystemConnectionMemo*  py_q_getSystemConnectionMemo() { return LnPortController::getSystemConnectionMemo(); }
inline void py_q_setDisabled(bool  disabled) { LnPortController::setDisabled(disabled); }
inline bool  py_q_status() { return LnPortController::status(); }
};

class PythonQtWrapper_LnPortController : public QObject
{ Q_OBJECT
public:
public slots:
LnPortController* new_LnPortController(LocoNetSystemConnectionMemo*  connectionMemo, QObject*  parent = 0);
void delete_LnPortController(LnPortController* obj) { delete obj; } 
   QDataStream*  py_q_getInputStream(LnPortController* theWrappedObject){  return (((PythonQtPublicPromoter_LnPortController*)theWrappedObject)->py_q_getInputStream());}
   QDataStream*  py_q_getOutputStream(LnPortController* theWrappedObject){  return (((PythonQtPublicPromoter_LnPortController*)theWrappedObject)->py_q_getOutputStream());}
   SystemConnectionMemo*  py_q_getSystemConnectionMemo(LnPortController* theWrappedObject){  return (((PythonQtPublicPromoter_LnPortController*)theWrappedObject)->py_q_getSystemConnectionMemo());}
   bool  okToSend(LnPortController* theWrappedObject);
   void setCommandStationType(LnPortController* theWrappedObject, LnCommandStationType*  value);
   void setCommandStationType(LnPortController* theWrappedObject, QString  name);
   void py_q_setDisabled(LnPortController* theWrappedObject, bool  disabled){  (((PythonQtPublicPromoter_LnPortController*)theWrappedObject)->py_q_setDisabled(disabled));}
   void setTranspondingAvailable(LnPortController* theWrappedObject, QString  value);
   void setTurnoutHandling(LnPortController* theWrappedObject, QString  value);
   bool  py_q_status(LnPortController* theWrappedObject){  return (((PythonQtPublicPromoter_LnPortController*)theWrappedObject)->py_q_status());}
};





class PythonQtShell_LnPowerManager : public LnPowerManager
{
public:
    PythonQtShell_LnPowerManager(LocoNetSystemConnectionMemo*  memo, QObject*  parent = 0):LnPowerManager(memo, parent),_wrapper(NULL) {}

   ~PythonQtShell_LnPowerManager();

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
virtual void setPower(int  v);
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_LnPowerManager : public LnPowerManager
{ public:
inline void py_q_dispose() { LnPowerManager::dispose(); }
inline int  py_q_getPower() { return LnPowerManager::getPower(); }
inline bool  py_q_implementsIdle() { return LnPowerManager::implementsIdle(); }
inline void py_q_setPower(int  v) { LnPowerManager::setPower(v); }
};

class PythonQtWrapper_LnPowerManager : public QObject
{ Q_OBJECT
public:
public slots:
LnPowerManager* new_LnPowerManager(LocoNetSystemConnectionMemo*  memo, QObject*  parent = 0);
void delete_LnPowerManager(LnPowerManager* obj) { delete obj; } 
   void py_q_dispose(LnPowerManager* theWrappedObject){  (((PythonQtPublicPromoter_LnPowerManager*)theWrappedObject)->py_q_dispose());}
   int  py_q_getPower(LnPowerManager* theWrappedObject){  return (((PythonQtPublicPromoter_LnPowerManager*)theWrappedObject)->py_q_getPower());}
   bool  py_q_implementsIdle(LnPowerManager* theWrappedObject){  return (((PythonQtPublicPromoter_LnPowerManager*)theWrappedObject)->py_q_implementsIdle());}
   bool  isPowerOff(LnPowerManager* theWrappedObject);
   bool  isPowerOn(LnPowerManager* theWrappedObject);
   bool  isPowerUnknown(LnPowerManager* theWrappedObject);
   void py_q_setPower(LnPowerManager* theWrappedObject, int  v){  (((PythonQtPublicPromoter_LnPowerManager*)theWrappedObject)->py_q_setPower(v));}
};





class PythonQtShell_LnReporterManager : public LnReporterManager
{
public:
    PythonQtShell_LnReporterManager(LocoNetSystemConnectionMemo*  memo, QObject*  parent = 0):LnReporterManager(memo, parent),_wrapper(NULL) {}

   ~PythonQtShell_LnReporterManager();

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

class PythonQtPublicPromoter_LnReporterManager : public LnReporterManager
{ public:
inline void py_q_dispose() { LnReporterManager::dispose(); }
inline QString  py_q_getEntryToolTip() { return LnReporterManager::getEntryToolTip(); }
inline QString  py_q_getNamedBeanClass() const { return LnReporterManager::getNamedBeanClass(); }
inline Manager::NameValidity  py_q_validSystemNameFormat(QString  systemName) const { return LnReporterManager::validSystemNameFormat(systemName); }
};

class PythonQtWrapper_LnReporterManager : public QObject
{ Q_OBJECT
public:
public slots:
LnReporterManager* new_LnReporterManager(LocoNetSystemConnectionMemo*  memo, QObject*  parent = 0);
void delete_LnReporterManager(LnReporterManager* obj) { delete obj; } 
   void py_q_dispose(LnReporterManager* theWrappedObject){  (((PythonQtPublicPromoter_LnReporterManager*)theWrappedObject)->py_q_dispose());}
   int  getBitFromSystemName(LnReporterManager* theWrappedObject, QString  systemName) const;
   QString  py_q_getEntryToolTip(LnReporterManager* theWrappedObject){  return (((PythonQtPublicPromoter_LnReporterManager*)theWrappedObject)->py_q_getEntryToolTip());}
   QString  py_q_getNamedBeanClass(LnReporterManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_LnReporterManager*)theWrappedObject)->py_q_getNamedBeanClass());}
   Manager::NameValidity  py_q_validSystemNameFormat(LnReporterManager* theWrappedObject, QString  systemName) const{  return (((PythonQtPublicPromoter_LnReporterManager*)theWrappedObject)->py_q_validSystemNameFormat(systemName));}
   QString  validateSystemNameFormat(LnReporterManager* theWrappedObject, QString  systemName, QLocale  locale);
    QString py_toString(LnReporterManager*);
};





class PythonQtShell_LnSensor : public LnSensor
{
public:
    PythonQtShell_LnSensor(QString  systemName, LnTrafficController*  tc = NULL, QString  prefix = "L", QObject*  parent = 0):LnSensor(systemName, tc, prefix, parent),_wrapper(NULL) {}
    PythonQtShell_LnSensor(QString  systemName, QString  userName, LnTrafficController*  tc = NULL, QString  prefix = "L", QObject*  parent = 0):LnSensor(systemName, userName, tc, prefix, parent),_wrapper(NULL) {}

   ~PythonQtShell_LnSensor();

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

class PythonQtPublicPromoter_LnSensor : public LnSensor
{ public:
inline void py_q_dispose() { LnSensor::dispose(); }
inline void py_q_requestUpdateFromLayout() const { LnSensor::requestUpdateFromLayout(); }
inline void py_q_setKnownState(int  s) { LnSensor::setKnownState(s); }
};

class PythonQtWrapper_LnSensor : public QObject
{ Q_OBJECT
public:
public slots:
LnSensor* new_LnSensor(QString  systemName, LnTrafficController*  tc = NULL, QString  prefix = "L", QObject*  parent = 0);
LnSensor* new_LnSensor(QString  systemName, QString  userName, LnTrafficController*  tc = NULL, QString  prefix = "L", QObject*  parent = 0);
void delete_LnSensor(LnSensor* obj) { delete obj; } 
   void py_q_dispose(LnSensor* theWrappedObject){  (((PythonQtPublicPromoter_LnSensor*)theWrappedObject)->py_q_dispose());}
   void messageFromManager(LnSensor* theWrappedObject, LocoNetMessage*  l);
   void py_q_requestUpdateFromLayout(LnSensor* theWrappedObject) const{  (((PythonQtPublicPromoter_LnSensor*)theWrappedObject)->py_q_requestUpdateFromLayout());}
   void py_q_setKnownState(LnSensor* theWrappedObject, int  s){  (((PythonQtPublicPromoter_LnSensor*)theWrappedObject)->py_q_setKnownState(s));}
};





class PythonQtShell_LnSensorManager : public LnSensorManager
{
public:
    PythonQtShell_LnSensorManager(LocoNetSystemConnectionMemo*  memo, QObject*  parent = 0):LnSensorManager(memo, parent),_wrapper(NULL) {}

   ~PythonQtShell_LnSensorManager();

virtual void Register(NamedBean*  s) const;
virtual void addDataListener(QObject*  e);
virtual void addPropertyChangeListener(PropertyChangeListener*  l);
virtual void addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual bool  allowMultipleAdditions(QString  systemName);
virtual void childEvent(QChildEvent*  event);
virtual Sensor*  createNewSensor(QString  systemName, QString  userName);
virtual QString  createSystemName(QString  curAddress, QString  prefix);
virtual void customEvent(QEvent*  event);
virtual void deleteBean(NamedBean*  arg__1, QString  arg__2) throw (PropertyVetoException) ;
virtual void deregister(NamedBean*  s) const;
virtual void dispose();
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
virtual QString  getSystemPrefix();
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
virtual void updateAll();
virtual Manager::NameValidity  validSystemNameFormat(QString  systemName) const;
virtual void vetoableChange(PropertyChangeEvent*  evt);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_LnSensorManager : public LnSensorManager
{ public:
inline bool  py_q_allowMultipleAdditions(QString  systemName) { return LnSensorManager::allowMultipleAdditions(systemName); }
inline Sensor*  py_q_createNewSensor(QString  systemName, QString  userName) { return LnSensorManager::createNewSensor(systemName, userName); }
inline QString  py_q_createSystemName(QString  curAddress, QString  prefix) { return LnSensorManager::createSystemName(curAddress, prefix); }
inline void py_q_dispose() { LnSensorManager::dispose(); }
inline QString  py_q_getNamedBeanClass() const { return LnSensorManager::getNamedBeanClass(); }
inline QString  py_q_getNextValidAddress(QString  curAddress, QString  prefix) { return LnSensorManager::getNextValidAddress(curAddress, prefix); }
inline QString  py_q_getSystemPrefix() { return LnSensorManager::getSystemPrefix(); }
inline void py_q_updateAll() { LnSensorManager::updateAll(); }
};

class PythonQtWrapper_LnSensorManager : public QObject
{ Q_OBJECT
public:
public slots:
LnSensorManager* new_LnSensorManager(LocoNetSystemConnectionMemo*  memo, QObject*  parent = 0);
void delete_LnSensorManager(LnSensorManager* obj) { delete obj; } 
   bool  py_q_allowMultipleAdditions(LnSensorManager* theWrappedObject, QString  systemName){  return (((PythonQtPublicPromoter_LnSensorManager*)theWrappedObject)->py_q_allowMultipleAdditions(systemName));}
   Sensor*  py_q_createNewSensor(LnSensorManager* theWrappedObject, QString  systemName, QString  userName){  return (((PythonQtPublicPromoter_LnSensorManager*)theWrappedObject)->py_q_createNewSensor(systemName, userName));}
   QString  py_q_createSystemName(LnSensorManager* theWrappedObject, QString  curAddress, QString  prefix){  return (((PythonQtPublicPromoter_LnSensorManager*)theWrappedObject)->py_q_createSystemName(curAddress, prefix));}
   void py_q_dispose(LnSensorManager* theWrappedObject){  (((PythonQtPublicPromoter_LnSensorManager*)theWrappedObject)->py_q_dispose());}
   QString  py_q_getNamedBeanClass(LnSensorManager* theWrappedObject) const{  return (((PythonQtPublicPromoter_LnSensorManager*)theWrappedObject)->py_q_getNamedBeanClass());}
   QString  py_q_getNextValidAddress(LnSensorManager* theWrappedObject, QString  curAddress, QString  prefix){  return (((PythonQtPublicPromoter_LnSensorManager*)theWrappedObject)->py_q_getNextValidAddress(curAddress, prefix));}
   QString  py_q_getSystemPrefix(LnSensorManager* theWrappedObject){  return (((PythonQtPublicPromoter_LnSensorManager*)theWrappedObject)->py_q_getSystemPrefix());}
   void setDefaultSensorState(LnSensorManager* theWrappedObject, QString  state);
   void setUpdateBusy(LnSensorManager* theWrappedObject);
   void setUpdateNotBusy(LnSensorManager* theWrappedObject);
   void py_q_updateAll(LnSensorManager* theWrappedObject){  (((PythonQtPublicPromoter_LnSensorManager*)theWrappedObject)->py_q_updateAll());}
    QString py_toString(LnSensorManager*);
};





class PythonQtShell_LnTrafficController : public LnTrafficController
{
public:
    PythonQtShell_LnTrafficController(LocoNetSystemConnectionMemo*  memo, QObject*  parent = nullptr):LnTrafficController(memo, parent),_wrapper(NULL) {}
    PythonQtShell_LnTrafficController(QObject*  parent = nullptr):LnTrafficController(parent),_wrapper(NULL) {}

   ~PythonQtShell_LnTrafficController();

virtual void childEvent(QChildEvent*  event);
virtual void customEvent(QEvent*  event);
virtual bool  event(QEvent*  event);
virtual bool  eventFilter(QObject*  watched, QEvent*  event);
virtual LocoNetSystemConnectionMemo*  getSystemConnectionMemo();
virtual bool  isXmtBusy();
virtual void sendLocoNetMessage(LocoNetMessage*  arg__1);
virtual void setSystemConnectionMemo(LocoNetSystemConnectionMemo*  m);
virtual bool  status();
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_LnTrafficController : public LnTrafficController
{ public:
inline LocoNetSystemConnectionMemo*  py_q_getSystemConnectionMemo() { return LnTrafficController::getSystemConnectionMemo(); }
inline bool  py_q_isXmtBusy() { return LnTrafficController::isXmtBusy(); }
inline void py_q_sendLocoNetMessage(LocoNetMessage*  arg__1) { LnTrafficController::sendLocoNetMessage(arg__1); }
inline void py_q_setSystemConnectionMemo(LocoNetSystemConnectionMemo*  m) { LnTrafficController::setSystemConnectionMemo(m); }
inline bool  py_q_status() { return LnTrafficController::status(); }
};

class PythonQtWrapper_LnTrafficController : public QObject
{ Q_OBJECT
public:
public slots:
LnTrafficController* new_LnTrafficController(LocoNetSystemConnectionMemo*  memo, QObject*  parent = nullptr);
LnTrafficController* new_LnTrafficController(QObject*  parent = nullptr);
void delete_LnTrafficController(LnTrafficController* obj) { delete obj; } 
   void dispose(LnTrafficController* theWrappedObject);
   int  getReceivedByteCount(LnTrafficController* theWrappedObject);
   int  getReceivedMsgCount(LnTrafficController* theWrappedObject);
   LocoNetSystemConnectionMemo*  py_q_getSystemConnectionMemo(LnTrafficController* theWrappedObject){  return (((PythonQtPublicPromoter_LnTrafficController*)theWrappedObject)->py_q_getSystemConnectionMemo());}
   int  getTransmittedMsgCount(LnTrafficController* theWrappedObject);
   bool  isXmtBusy(LnTrafficController* theWrappedObject);
   bool  py_q_isXmtBusy(LnTrafficController* theWrappedObject){  return (((PythonQtPublicPromoter_LnTrafficController*)theWrappedObject)->py_q_isXmtBusy());}
   void notify(LnTrafficController* theWrappedObject, LocoNetMessage*  m);
   void resetStatistics(LnTrafficController* theWrappedObject);
   void py_q_sendLocoNetMessage(LnTrafficController* theWrappedObject, LocoNetMessage*  arg__1){  (((PythonQtPublicPromoter_LnTrafficController*)theWrappedObject)->py_q_sendLocoNetMessage(arg__1));}
   void py_q_setSystemConnectionMemo(LnTrafficController* theWrappedObject, LocoNetSystemConnectionMemo*  m){  (((PythonQtPublicPromoter_LnTrafficController*)theWrappedObject)->py_q_setSystemConnectionMemo(m));}
   bool  py_q_status(LnTrafficController* theWrappedObject){  return (((PythonQtPublicPromoter_LnTrafficController*)theWrappedObject)->py_q_status());}
};





class PythonQtShell_LnTurnout : public LnTurnout
{
public:
    PythonQtShell_LnTurnout(QString  prefix, int  number, LocoNetInterface*  controller, QObject*  parent = 0):LnTurnout(prefix, number, controller, parent),_wrapper(NULL) {}

   ~PythonQtShell_LnTurnout();

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
virtual void forwardCommandChangeToLayout(int  newstate);
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
virtual void turnoutPushbuttonLockout(bool  _pushButtonLockout);
virtual void updateListenerRef(PropertyChangeListener*  l, QString  newName);
virtual void vetoableChange(PropertyChangeEvent*  evt) throw (PropertyVetoException) ;

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_LnTurnout : public LnTurnout
{ public:
inline void promoted_forwardCommandChangeToLayout(int  newstate) { this->forwardCommandChangeToLayout(newstate); }
inline void promoted_turnoutPushbuttonLockout(bool  _pushButtonLockout) { this->turnoutPushbuttonLockout(_pushButtonLockout); }
inline bool  py_q_canInvert() const { return LnTurnout::canInvert(); }
inline void py_q_dispose() { LnTurnout::dispose(); }
inline void py_q_forwardCommandChangeToLayout(int  newstate) { LnTurnout::forwardCommandChangeToLayout(newstate); }
inline void py_q_turnoutPushbuttonLockout(bool  _pushButtonLockout) { LnTurnout::turnoutPushbuttonLockout(_pushButtonLockout); }
};

class PythonQtWrapper_LnTurnout : public QObject
{ Q_OBJECT
public:
public slots:
LnTurnout* new_LnTurnout(QString  prefix, int  number, LocoNetInterface*  controller, QObject*  parent = 0);
void delete_LnTurnout(LnTurnout* obj) { delete obj; } 
   bool  py_q_canInvert(LnTurnout* theWrappedObject) const{  return (((PythonQtPublicPromoter_LnTurnout*)theWrappedObject)->py_q_canInvert());}
   void py_q_dispose(LnTurnout* theWrappedObject){  (((PythonQtPublicPromoter_LnTurnout*)theWrappedObject)->py_q_dispose());}
   void py_q_forwardCommandChangeToLayout(LnTurnout* theWrappedObject, int  newstate){  (((PythonQtPublicPromoter_LnTurnout*)theWrappedObject)->py_q_forwardCommandChangeToLayout(newstate));}
   int  getNumber(LnTurnout* theWrappedObject);
   void messageFromManager(LnTurnout* theWrappedObject, LocoNetMessage*  l);
   void sendOpcSwReqMessage(LnTurnout* theWrappedObject, int  state, bool  on);
   void sendSetOffMessage(LnTurnout* theWrappedObject, int  state);
   void setUseOffSwReqAsConfirmation(LnTurnout* theWrappedObject, bool  state);
   void py_q_turnoutPushbuttonLockout(LnTurnout* theWrappedObject, bool  _pushButtonLockout){  (((PythonQtPublicPromoter_LnTurnout*)theWrappedObject)->py_q_turnoutPushbuttonLockout(_pushButtonLockout));}
};


