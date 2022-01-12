#include <PythonQt.h>
#include <QObject>
#include <QTextEdit>
#include <QVariant>
#include <abstractnamedbean.h>
#include <block.h>
#include <defaultprogrammermanager.h>
#include <editscene.h>
#include <jmrijframe.h>
#include <jtextarea.h>
#include <layouteditor.h>
#include <layoutturnout.h>
#include <listselectionmodel.h>
#include <lncommandstationtype.h>
#include <lnpacketizer.h>
#include <lnportcontroller.h>
#include <lnsensor.h>
#include <lntrafficcontroller.h>
#include <lnturnout.h>
#include <locoaddress.h>
#include <loconetinterface.h>
#include <loconetmessage.h>
#include <loconetsystemconnectionmemo.h>
#include <logger.h>
#include <multiiconeditor.h>
#include <namedbean.h>
#include <networkportadapter.h>
#include <paneleditor.h>
#include <panelmenu.h>
#include <portadapter.h>
#include <positionable.h>
#include <positionablelabel.h>
#include <proglistener.h>
#include <programmingmode.h>
#include <propertychangeevent.h>
#include <propertychangelistener.h>
#include <propertychangesupport.h>
#include <qaction.h>
#include <qactiongroup.h>
#include <qbytearray.h>
#include <qcolor.h>
#include <qcoreevent.h>
#include <qcursor.h>
#include <qdatastream.h>
#include <qevent.h>
#include <qfont.h>
#include <qfontinfo.h>
#include <qfontmetrics.h>
#include <qgraphicsitem.h>
#include <qgraphicsproxywidget.h>
#include <qgraphicssceneevent.h>
#include <qicon.h>
#include <qkeysequence.h>
#include <qlayout.h>
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
#include <qpixmap.h>
#include <qpoint.h>
#include <qrect.h>
#include <qregexp.h>
#include <qregion.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstatusbar.h>
#include <qstringlist.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qtextcursor.h>
#include <qtextdocument.h>
#include <qtextedit.h>
#include <qtextformat.h>
#include <qurl.h>
#include <qvector.h>
#include <qwidget.h>
#include <sensor.h>
#include <signalhead.h>
#include <systemconnectionmemo.h>
#include <turnout.h>
#include <turnoutoperation.h>
#include <windowlistener.h>



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
   QString  getText(JTextArea* theWrappedObject);
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
void py_set_windowFrameRef(JmriJFrame* theWrappedObject, QString  windowFrameRef){ theWrappedObject->windowFrameRef = windowFrameRef; }
QString  py_get_windowFrameRef(JmriJFrame* theWrappedObject){ return theWrappedObject->windowFrameRef; }
void py_set_windowMenu(JmriJFrame* theWrappedObject, QMenu*  windowMenu){ theWrappedObject->windowMenu = windowMenu; }
QMenu*  py_get_windowMenu(JmriJFrame* theWrappedObject){ return theWrappedObject->windowMenu; }
};





class PythonQtShell_LayoutEditor : public LayoutEditor
{
public:
    PythonQtShell_LayoutEditor(QString  name = "My Layout", QWidget*  parent = 0):LayoutEditor(name, parent),_wrapper(NULL) {}
    PythonQtShell_LayoutEditor(const LayoutEditor&  arg__1):LayoutEditor(arg__1),_wrapper(NULL) {}

   ~PythonQtShell_LayoutEditor();

virtual int  computeDirectionAB(LayoutTurnout*  track);
virtual int  computeDirectionAC(LayoutTurnout*  track);
virtual int  computeDirectionAD(LayoutTurnout*  track);
virtual int  computeDirectionBC(LayoutTurnout*  track);
virtual int  computeDirectionBD(LayoutTurnout*  track);
virtual int  computeDirectionCD(LayoutTurnout*  track);
virtual bool  deletePanel();
virtual void displayRemoveWarning(LayoutTrack*  track, QList<QString >  itemList, QString  typeKey);
virtual void dispose();
virtual void init(QString  name);
virtual void initView();
virtual void keyPressEvent(QKeyEvent*  event);
virtual void mouseClicked(QGraphicsSceneMouseEvent*  event);
virtual void mouseMoved(QGraphicsSceneMouseEvent*  event);
virtual void mousePressed(QGraphicsSceneMouseEvent*  event);
virtual void mouseReleased(QGraphicsSceneMouseEvent*  event);
virtual void newPanelDefaults();
virtual void putItem(Positionable*  l);
virtual void redrawPanel();
virtual void repaint();
virtual void setAllEditable(bool  editable);
virtual void setNextLocation(Positionable*  obj);
virtual void setScroll(QString  value);
virtual void setScroll(int  state);
virtual void showPopUp(Positionable*  p, QGraphicsSceneMouseEvent*  event);
virtual void targetWindowClosingEvent(QCloseEvent*  e);
virtual void vetoableChange(PropertyChangeEvent*  evt);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_LayoutEditor : public LayoutEditor
{ public:
inline void promoted_assignBlockToSelection() { this->assignBlockToSelection(); }
inline void promoted_common() { this->common(); }
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
inline int  py_q_computeDirectionAB(LayoutTurnout*  track) { return LayoutEditor::computeDirectionAB(track); }
inline int  py_q_computeDirectionAC(LayoutTurnout*  track) { return LayoutEditor::computeDirectionAC(track); }
inline int  py_q_computeDirectionAD(LayoutTurnout*  track) { return LayoutEditor::computeDirectionAD(track); }
inline int  py_q_computeDirectionBC(LayoutTurnout*  track) { return LayoutEditor::computeDirectionBC(track); }
inline int  py_q_computeDirectionBD(LayoutTurnout*  track) { return LayoutEditor::computeDirectionBD(track); }
inline int  py_q_computeDirectionCD(LayoutTurnout*  track) { return LayoutEditor::computeDirectionCD(track); }
inline bool  py_q_deletePanel() { return LayoutEditor::deletePanel(); }
inline void py_q_displayRemoveWarning(LayoutTrack*  track, QList<QString >  itemList, QString  typeKey) { LayoutEditor::displayRemoveWarning(track, itemList, typeKey); }
inline void py_q_dispose() { LayoutEditor::dispose(); }
inline void py_q_init(QString  name) { LayoutEditor::init(name); }
inline void py_q_initView() { LayoutEditor::initView(); }
inline void py_q_keyPressEvent(QKeyEvent*  event) { LayoutEditor::keyPressEvent(event); }
inline void py_q_mouseClicked(QGraphicsSceneMouseEvent*  event) { LayoutEditor::mouseClicked(event); }
inline void py_q_mouseMoved(QGraphicsSceneMouseEvent*  event) { LayoutEditor::mouseMoved(event); }
inline void py_q_mousePressed(QGraphicsSceneMouseEvent*  event) { LayoutEditor::mousePressed(event); }
inline void py_q_mouseReleased(QGraphicsSceneMouseEvent*  event) { LayoutEditor::mouseReleased(event); }
inline void py_q_newPanelDefaults() { LayoutEditor::newPanelDefaults(); }
inline void py_q_putItem(Positionable*  l) { LayoutEditor::putItem(l); }
inline void py_q_redrawPanel() { LayoutEditor::redrawPanel(); }
inline void py_q_repaint() { LayoutEditor::repaint(); }
inline void py_q_setAllEditable(bool  editable) { LayoutEditor::setAllEditable(editable); }
inline void py_q_setNextLocation(Positionable*  obj) { LayoutEditor::setNextLocation(obj); }
inline void py_q_setScroll(QString  value) { LayoutEditor::setScroll(value); }
inline void py_q_setScroll(int  state) { LayoutEditor::setScroll(state); }
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
   int  computeDirectionAB(LayoutEditor* theWrappedObject, LayoutTurnout*  track);
   int  py_q_computeDirectionAB(LayoutEditor* theWrappedObject, LayoutTurnout*  track){  return (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_computeDirectionAB(track));}
   int  computeDirectionAC(LayoutEditor* theWrappedObject, LayoutTurnout*  track);
   int  py_q_computeDirectionAC(LayoutEditor* theWrappedObject, LayoutTurnout*  track){  return (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_computeDirectionAC(track));}
   int  computeDirectionAD(LayoutEditor* theWrappedObject, LayoutTurnout*  track);
   int  py_q_computeDirectionAD(LayoutEditor* theWrappedObject, LayoutTurnout*  track){  return (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_computeDirectionAD(track));}
   int  computeDirectionBC(LayoutEditor* theWrappedObject, LayoutTurnout*  track);
   int  py_q_computeDirectionBC(LayoutEditor* theWrappedObject, LayoutTurnout*  track){  return (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_computeDirectionBC(track));}
   int  computeDirectionBD(LayoutEditor* theWrappedObject, LayoutTurnout*  track);
   int  py_q_computeDirectionBD(LayoutEditor* theWrappedObject, LayoutTurnout*  track){  return (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_computeDirectionBD(track));}
   int  computeDirectionCD(LayoutEditor* theWrappedObject, LayoutTurnout*  track);
   int  py_q_computeDirectionCD(LayoutEditor* theWrappedObject, LayoutTurnout*  track){  return (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_computeDirectionCD(track));}
   bool  containsSignalHead(LayoutEditor* theWrappedObject, SignalHead*  head);
   bool  containsSignalMast(LayoutEditor* theWrappedObject, SignalMast*  mast);
   bool  deletePanel(LayoutEditor* theWrappedObject);
   bool  py_q_deletePanel(LayoutEditor* theWrappedObject){  return (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_deletePanel());}
   void displayRemoveWarning(LayoutEditor* theWrappedObject, LayoutTrack*  track, QList<QString >  itemList, QString  typeKey);
   void py_q_displayRemoveWarning(LayoutEditor* theWrappedObject, LayoutTrack*  track, QList<QString >  itemList, QString  typeKey){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_displayRemoveWarning(track, itemList, typeKey));}
   void dispose(LayoutEditor* theWrappedObject);
   void py_q_dispose(LayoutEditor* theWrappedObject){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_dispose());}
   void drawSelectionRect(LayoutEditor* theWrappedObject, EditScene*  g2);
   int  getAnchorX(LayoutEditor* theWrappedObject);
   int  getAnchorY(LayoutEditor* theWrappedObject);
   bool  getAntialiasingOn(LayoutEditor* theWrappedObject);
   bool  getAutoBlockAssignment(LayoutEditor* theWrappedObject);
   QString  getClassName(LayoutEditor* theWrappedObject);
   const QIcon  getColourIcon(LayoutEditor* theWrappedObject, QColor  color);
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
   QList<PositionableLabel* >  getLabelImageList(LayoutEditor* theWrappedObject);
   QString  getLayoutName(LayoutEditor* theWrappedObject);
   QList<LayoutTrack* >  getLayoutTrackSelection(LayoutEditor* theWrappedObject);
   QList<LayoutTrack* >  getLayoutTracks(LayoutEditor* theWrappedObject);
   QList<LayoutTurnout* >  getLayoutTurnouts(LayoutEditor* theWrappedObject);
   QList<LayoutTurnout* >  getLayoutTurnoutsAndSlips(LayoutEditor* theWrappedObject);
   double  getMaxZoom(LayoutEditor* theWrappedObject);
   double  getMinZoom(LayoutEditor* theWrappedObject);
   bool  getOpenDispatcherOnLoad(LayoutEditor* theWrappedObject);
   QRectF  getPanelBounds(LayoutEditor* theWrappedObject);
   QList<Positionable* >*  getPositionalSelection(LayoutEditor* theWrappedObject);
   EditScene*  getScene(LayoutEditor* theWrappedObject);
   bool  getScroll(LayoutEditor* theWrappedObject);
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
   bool  isDrawLayoutTracksLabel(LayoutEditor* theWrappedObject);
   bool  isEditable(LayoutEditor* theWrappedObject);
   bool  isIncludedTurnoutSkipped(LayoutEditor* theWrappedObject);
   bool  isTurnoutDrawUnselectedLeg(LayoutEditor* theWrappedObject);
   bool  isTurnoutFillControlCircles(LayoutEditor* theWrappedObject);
   void keyPressEvent(LayoutEditor* theWrappedObject, QKeyEvent*  event);
   void py_q_keyPressEvent(LayoutEditor* theWrappedObject, QKeyEvent*  event){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_keyPressEvent(event));}
   QRectF  layoutEditorControlCircleRectAt(LayoutEditor* theWrappedObject, QPointF  inPoint);
   QRectF  layoutEditorControlRectAt(LayoutEditor* theWrappedObject, QPointF  inPoint);
   void py_q_mouseClicked(LayoutEditor* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_mouseClicked(event));}
   void py_q_mouseMoved(LayoutEditor* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_mouseMoved(event));}
   void py_q_mousePressed(LayoutEditor* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_mousePressed(event));}
   void py_q_mouseReleased(LayoutEditor* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_mouseReleased(event));}
   void newPanelDefaults(LayoutEditor* theWrappedObject);
   void py_q_newPanelDefaults(LayoutEditor* theWrappedObject){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_newPanelDefaults());}
   void paintTargetPanel(LayoutEditor* theWrappedObject, EditScene*  g2);
   void py_q_putItem(LayoutEditor* theWrappedObject, Positionable*  l){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_putItem(l));}
   void redrawPanel(LayoutEditor* theWrappedObject);
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
   void setAllEditable(LayoutEditor* theWrappedObject, bool  editable);
   void py_q_setAllEditable(LayoutEditor* theWrappedObject, bool  editable){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_setAllEditable(editable));}
   void setAllPositionable(LayoutEditor* theWrappedObject, bool  state);
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
   void setDirty(LayoutEditor* theWrappedObject);
   void setDirty(LayoutEditor* theWrappedObject, bool  b);
   void setDrawGrid(LayoutEditor* theWrappedObject, bool  state);
   void setDrawLayoutTracksLabel(LayoutEditor* theWrappedObject, bool  state);
   void setHighlightSelectedBlock(LayoutEditor* theWrappedObject, bool  state);
   void setIncludedTurnoutSkipped(LayoutEditor* theWrappedObject, bool  boo);
   void setLayoutDimensions(LayoutEditor* theWrappedObject, int  windowW, int  windowH, int  x, int  y, int  panelW, int  panelH, bool  merge);
   void setLayoutDimensions(LayoutEditor* theWrappedObject, int  windowWidth, int  windowHeight, int  windowX, int  windowY, int  panelWidth, int  panelHeight);
   void setLayoutName(LayoutEditor* theWrappedObject, QString  name);
   void py_q_setNextLocation(LayoutEditor* theWrappedObject, Positionable*  obj){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_setNextLocation(obj));}
   void setOpenDispatcherOnLoad(LayoutEditor* theWrappedObject, bool  boo);
   void setPanelBounds(LayoutEditor* theWrappedObject, QRectF  newBounds);
   void setScroll(LayoutEditor* theWrappedObject, QString  value);
   void py_q_setScroll(LayoutEditor* theWrappedObject, QString  value){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_setScroll(value));}
   void setScroll(LayoutEditor* theWrappedObject, int  state);
   void py_q_setScroll(LayoutEditor* theWrappedObject, int  state){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_setScroll(state));}
   void setSelectionRect(LayoutEditor* theWrappedObject, QRectF  selectionRect);
   void setSelectionsScale(LayoutEditor* theWrappedObject, double  s, Positionable*  p);
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
   void setTurnoutFillControlCircles(LayoutEditor* theWrappedObject, bool  state);
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
   void targetWindowClosingEvent(LayoutEditor* theWrappedObject, QCloseEvent*  e);
   void py_q_targetWindowClosingEvent(LayoutEditor* theWrappedObject, QCloseEvent*  e){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_targetWindowClosingEvent(e));}
   QString  toString(LayoutEditor* theWrappedObject);
   QRectF  trackControlCircleRectAt(LayoutEditor* theWrappedObject, QPointF  inPoint);
   QRectF  trackEditControlRectAt(LayoutEditor* theWrappedObject, QPointF  inPoint);
   void translate(LayoutEditor* theWrappedObject, float  xTranslation, float  yTranslation);
   bool  translateTrack(LayoutEditor* theWrappedObject, float  xDel, float  yDel);
   QRectF  unionToPanelBounds(LayoutEditor* theWrappedObject, QRectF  bounds);
   bool  validatePhysicalTurnout(LayoutEditor* theWrappedObject, QString  inTurnoutName, QWidget*  openPane = 0);
   void vetoableChange(LayoutEditor* theWrappedObject, PropertyChangeEvent*  evt);
   void py_q_vetoableChange(LayoutEditor* theWrappedObject, PropertyChangeEvent*  evt){  (((PythonQtPublicPromoter_LayoutEditor*)theWrappedObject)->py_q_vetoableChange(evt));}
    QString py_toString(LayoutEditor*);
void py_set__labelImage(LayoutEditor* theWrappedObject, QVector<PositionableLabel* >*  _labelImage){ theWrappedObject->_labelImage = _labelImage; }
QVector<PositionableLabel* >*  py_get__labelImage(LayoutEditor* theWrappedObject){ return theWrappedObject->_labelImage; }
void py_set__layoutTrackSelection(LayoutEditor* theWrappedObject, QList<LayoutTrack* >  _layoutTrackSelection){ theWrappedObject->_layoutTrackSelection = _layoutTrackSelection; }
QList<LayoutTrack* >  py_get__layoutTrackSelection(LayoutEditor* theWrappedObject){ return theWrappedObject->_layoutTrackSelection; }
void py_set__positionableSelection(LayoutEditor* theWrappedObject, QList<Positionable* >*  _positionableSelection){ theWrappedObject->_positionableSelection = _positionableSelection; }
QList<Positionable* >*  py_get__positionableSelection(LayoutEditor* theWrappedObject){ return theWrappedObject->_positionableSelection; }
void py_set_backgroundImage(LayoutEditor* theWrappedObject, QVector<PositionableLabel* >*  backgroundImage){ theWrappedObject->backgroundImage = backgroundImage; }
QVector<PositionableLabel* >*  py_get_backgroundImage(LayoutEditor* theWrappedObject){ return theWrappedObject->backgroundImage; }
void py_set_circleDiameter(LayoutEditor* theWrappedObject, double  circleDiameter){ theWrappedObject->circleDiameter = circleDiameter; }
double  py_get_circleDiameter(LayoutEditor* theWrappedObject){ return theWrappedObject->circleDiameter; }
void py_set_circleRadius(LayoutEditor* theWrappedObject, double  circleRadius){ theWrappedObject->circleRadius = circleRadius; }
double  py_get_circleRadius(LayoutEditor* theWrappedObject){ return theWrappedObject->circleRadius; }
void py_set_labelImage(LayoutEditor* theWrappedObject, QList<PositionableLabel* >  labelImage){ theWrappedObject->labelImage = labelImage; }
QList<PositionableLabel* >  py_get_labelImage(LayoutEditor* theWrappedObject){ return theWrappedObject->labelImage; }
};





class PythonQtShell_LayoutTurnout : public LayoutTurnout
{
public:
    PythonQtShell_LayoutTurnout(QString  id, LayoutEditor*  models):LayoutTurnout(id, models),_wrapper(NULL) {}

   ~PythonQtShell_LayoutTurnout();

virtual bool  canRemove();
virtual void checkForNonContiguousBlocks(QMap<QString , QList<QSet<QString >* >* >  blockNamesToTrackNameSetsMap);
virtual bool  checkForUnAssignedBlocks();
virtual void collectContiguousTracksNamesInBlockNamed(QString  blockName, QSet<QString >*  TrackNameSet);
virtual void invalidate(EditScene*  g2);
virtual bool  isMainline();
virtual void propertyChange(PropertyChangeEvent*  e);
virtual void reCheckBlockBoundary() const;
virtual QObject*  self();
virtual QString  toString();

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_LayoutTurnout : public LayoutTurnout
{ public:
inline bool  py_q_canRemove() { return LayoutTurnout::canRemove(); }
inline void py_q_checkForNonContiguousBlocks(QMap<QString , QList<QSet<QString >* >* >  blockNamesToTrackNameSetsMap) { LayoutTurnout::checkForNonContiguousBlocks(blockNamesToTrackNameSetsMap); }
inline bool  py_q_checkForUnAssignedBlocks() { return LayoutTurnout::checkForUnAssignedBlocks(); }
inline void py_q_collectContiguousTracksNamesInBlockNamed(QString  blockName, QSet<QString >*  TrackNameSet) { LayoutTurnout::collectContiguousTracksNamesInBlockNamed(blockName, TrackNameSet); }
inline void py_q_invalidate(EditScene*  g2) { LayoutTurnout::invalidate(g2); }
inline bool  py_q_isMainline() { return LayoutTurnout::isMainline(); }
inline void py_q_propertyChange(PropertyChangeEvent*  e) { LayoutTurnout::propertyChange(e); }
inline void py_q_reCheckBlockBoundary() const { LayoutTurnout::reCheckBlockBoundary(); }
inline QObject*  py_q_self() { return LayoutTurnout::self(); }
inline QString  py_q_toString() { return LayoutTurnout::toString(); }
};

class PythonQtWrapper_LayoutTurnout : public QObject
{ Q_OBJECT
public:
public slots:
LayoutTurnout* new_LayoutTurnout(QString  id, LayoutEditor*  models);
void delete_LayoutTurnout(LayoutTurnout* obj) { delete obj; } 
   bool  canRemove(LayoutTurnout* theWrappedObject);
   bool  py_q_canRemove(LayoutTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_canRemove());}
   void checkForNonContiguousBlocks(LayoutTurnout* theWrappedObject, QMap<QString , QList<QSet<QString >* >* >  blockNamesToTrackNameSetsMap);
   void py_q_checkForNonContiguousBlocks(LayoutTurnout* theWrappedObject, QMap<QString , QList<QSet<QString >* >* >  blockNamesToTrackNameSetsMap){  (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_checkForNonContiguousBlocks(blockNamesToTrackNameSetsMap));}
   bool  checkForUnAssignedBlocks(LayoutTurnout* theWrappedObject);
   bool  py_q_checkForUnAssignedBlocks(LayoutTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_checkForUnAssignedBlocks());}
   void collectContiguousTracksNamesInBlockNamed(LayoutTurnout* theWrappedObject, QString  blockName, QSet<QString >*  TrackNameSet);
   void py_q_collectContiguousTracksNamesInBlockNamed(LayoutTurnout* theWrappedObject, QString  blockName, QSet<QString >*  TrackNameSet){  (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_collectContiguousTracksNamesInBlockNamed(blockName, TrackNameSet));}
   void dispose(LayoutTurnout* theWrappedObject);
   QList<QString >  getBeanReferences(LayoutTurnout* theWrappedObject, QString  pointName);
   QString  getBlockBName(LayoutTurnout* theWrappedObject);
   QStringList  getBlockBoundaries(LayoutTurnout* theWrappedObject);
   QString  getBlockCName(LayoutTurnout* theWrappedObject);
   QString  getBlockDName(LayoutTurnout* theWrappedObject);
   QString  getBlockName(LayoutTurnout* theWrappedObject);
   LayoutTrack*  getConnectA(LayoutTurnout* theWrappedObject);
   LayoutTrack*  getConnectB(LayoutTurnout* theWrappedObject);
   LayoutTrack*  getConnectC(LayoutTurnout* theWrappedObject);
   LayoutTrack*  getConnectD(LayoutTurnout* theWrappedObject);
   int  getContinuingSense(LayoutTurnout* theWrappedObject);
   bool  getHidden(LayoutTurnout* theWrappedObject);
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
   void py_q_propertyChange(LayoutTurnout* theWrappedObject, PropertyChangeEvent*  e){  (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_propertyChange(e));}
   void reCheckBlockBoundary(LayoutTurnout* theWrappedObject) const;
   void py_q_reCheckBlockBoundary(LayoutTurnout* theWrappedObject) const{  (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_reCheckBlockBoundary());}
   void remove(LayoutTurnout* theWrappedObject);
   void removeBeanReference(LayoutTurnout* theWrappedObject, NamedBean*  nb);
   void removeSML(LayoutTurnout* theWrappedObject, SignalMast*  signalMast) const;
   QObject*  py_q_self(LayoutTurnout* theWrappedObject){  return (((PythonQtPublicPromoter_LayoutTurnout*)theWrappedObject)->py_q_self());}
   void setAdditionalEditPopUpMenu(LayoutTurnout* theWrappedObject, QMenu*  popup);
   void setAdditionalViewPopUpMenu(LayoutTurnout* theWrappedObject, QMenu*  popup);
   void setConnectA(LayoutTurnout* theWrappedObject, LayoutTrack*  o, int  type);
   void setConnectB(LayoutTurnout* theWrappedObject, LayoutTrack*  o, int  type);
   void setConnectC(LayoutTurnout* theWrappedObject, LayoutTrack*  o, int  type);
   void setConnectD(LayoutTurnout* theWrappedObject, LayoutTrack*  o, int  type);
   void setContinuingSense(LayoutTurnout* theWrappedObject, int  sense);
   void setHidden(LayoutTurnout* theWrappedObject, bool  hide);
   void setLayoutBlockBByName(LayoutTurnout* theWrappedObject, QString  name);
   void setLayoutBlockByName(LayoutTurnout* theWrappedObject, QString  name);
   void setLayoutBlockCByName(LayoutTurnout* theWrappedObject, QString  name);
   void setLayoutBlockDByName(LayoutTurnout* theWrappedObject, QString  name);
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
void py_set_itemGroup(LayoutTurnout* theWrappedObject, QGraphicsItemGroup*  itemGroup){ theWrappedObject->itemGroup = itemGroup; }
QGraphicsItemGroup*  py_get_itemGroup(LayoutTurnout* theWrappedObject){ return theWrappedObject->itemGroup; }
void py_set_linkedTurnoutName(LayoutTurnout* theWrappedObject, QString  linkedTurnoutName){ theWrappedObject->linkedTurnoutName = linkedTurnoutName; }
QString  py_get_linkedTurnoutName(LayoutTurnout* theWrappedObject){ return theWrappedObject->linkedTurnoutName; }
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

virtual bool  canInvert() const;
virtual bool  canLock(int  turnoutLockout);
virtual QString  describeState(int  state);
virtual void dispose();
virtual void enableLockOperation(int  turnoutLockout, bool  enabled);
virtual void forwardCommandChangeToLayout(int  newstate);
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
virtual void turnoutPushbuttonLockout(bool  _pushButtonLockout);
virtual void vetoableChange(PropertyChangeEvent*  evt);

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





class PythonQtShell_LocoAddress : public LocoAddress
{
public:
    PythonQtShell_LocoAddress(QObject*  parent = 0):LocoAddress(parent),_wrapper(NULL) {}

   ~PythonQtShell_LocoAddress();

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

class PythonQtPublicPromoter_LocoAddress : public LocoAddress
{ public:
inline bool  py_q_equals(QObject*  a) { return LocoAddress::equals(a); }
inline int  py_q_getNumber() const { return LocoAddress::getNumber(); }
inline LocoAddress::Protocol  py_q_getProtocol() const { return LocoAddress::getProtocol(); }
inline int  py_q_hashCode() const { return LocoAddress::hashCode(); }
inline QString  py_q_toString() { return LocoAddress::toString(); }
};

class PythonQtWrapper_LocoAddress : public QObject
{ Q_OBJECT
public:
public slots:
LocoAddress* new_LocoAddress(QObject*  parent = 0);
void delete_LocoAddress(LocoAddress* obj) { delete obj; } 
   bool  equals(LocoAddress* theWrappedObject, QObject*  a);
   bool  py_q_equals(LocoAddress* theWrappedObject, QObject*  a){  return (((PythonQtPublicPromoter_LocoAddress*)theWrappedObject)->py_q_equals(a));}
   LocoAddress::Protocol  static_LocoAddress_getByPeopleName(QString  pName);
   LocoAddress::Protocol  static_LocoAddress_getByShortName(QString  shName);
   int  getNumber(LocoAddress* theWrappedObject) const;
   int  py_q_getNumber(LocoAddress* theWrappedObject) const{  return (((PythonQtPublicPromoter_LocoAddress*)theWrappedObject)->py_q_getNumber());}
   QString  static_LocoAddress_getPeopleName(LocoAddress::Protocol  p);
   LocoAddress::Protocol  getProtocol(LocoAddress* theWrappedObject) const;
   LocoAddress::Protocol  py_q_getProtocol(LocoAddress* theWrappedObject) const{  return (((PythonQtPublicPromoter_LocoAddress*)theWrappedObject)->py_q_getProtocol());}
   QString  static_LocoAddress_getShortName(LocoAddress::Protocol  p);
   int  hashCode(LocoAddress* theWrappedObject) const;
   int  py_q_hashCode(LocoAddress* theWrappedObject) const{  return (((PythonQtPublicPromoter_LocoAddress*)theWrappedObject)->py_q_hashCode());}
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
virtual LocoNetSystemConnectionMemo*  getSystemConnectionMemo();
virtual void sendLocoNetMessage(LocoNetMessage*  arg__1);
virtual void setSystemConnectionMemo(LocoNetSystemConnectionMemo*  arg__1);
virtual bool  status();
virtual void timerEvent(QTimerEvent*  event);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_LocoNetInterface : public LocoNetInterface
{ public:
inline LocoNetSystemConnectionMemo*  py_q_getSystemConnectionMemo() { return LocoNetInterface::getSystemConnectionMemo(); }
inline void py_q_sendLocoNetMessage(LocoNetMessage*  arg__1) { LocoNetInterface::sendLocoNetMessage(arg__1); }
inline void py_q_setSystemConnectionMemo(LocoNetSystemConnectionMemo*  arg__1) { LocoNetInterface::setSystemConnectionMemo(arg__1); }
inline bool  py_q_status() { return LocoNetInterface::status(); }
};

class PythonQtWrapper_LocoNetInterface : public QObject
{ Q_OBJECT
public:
public slots:
LocoNetInterface* new_LocoNetInterface(QObject*  parent = 0);
void delete_LocoNetInterface(LocoNetInterface* obj) { delete obj; } 
   LocoNetSystemConnectionMemo*  getSystemConnectionMemo(LocoNetInterface* theWrappedObject);
   LocoNetSystemConnectionMemo*  py_q_getSystemConnectionMemo(LocoNetInterface* theWrappedObject){  return (((PythonQtPublicPromoter_LocoNetInterface*)theWrappedObject)->py_q_getSystemConnectionMemo());}
   void sendLocoNetMessage(LocoNetInterface* theWrappedObject, LocoNetMessage*  arg__1);
   void py_q_sendLocoNetMessage(LocoNetInterface* theWrappedObject, LocoNetMessage*  arg__1){  (((PythonQtPublicPromoter_LocoNetInterface*)theWrappedObject)->py_q_sendLocoNetMessage(arg__1));}
   void setSystemConnectionMemo(LocoNetInterface* theWrappedObject, LocoNetSystemConnectionMemo*  arg__1);
   void py_q_setSystemConnectionMemo(LocoNetInterface* theWrappedObject, LocoNetSystemConnectionMemo*  arg__1){  (((PythonQtPublicPromoter_LocoNetInterface*)theWrappedObject)->py_q_setSystemConnectionMemo(arg__1));}
   bool  status(LocoNetInterface* theWrappedObject);
   bool  py_q_status(LocoNetInterface* theWrappedObject){  return (((PythonQtPublicPromoter_LocoNetInterface*)theWrappedObject)->py_q_status());}
};





class PythonQtShell_LocoNetMessage : public LocoNetMessage
{
public:
    PythonQtShell_LocoNetMessage():LocoNetMessage(),_wrapper(NULL) {}
    PythonQtShell_LocoNetMessage(LocoNetMessage*  original):LocoNetMessage(original),_wrapper(NULL) {}
    PythonQtShell_LocoNetMessage(QString  s):LocoNetMessage(s),_wrapper(NULL) {}
    PythonQtShell_LocoNetMessage(QVector<char >  contents, QObject*  parent = 0):LocoNetMessage(contents, parent),_wrapper(NULL) {}
    PythonQtShell_LocoNetMessage(QVector<int >  contents, QObject*  parent = 0):LocoNetMessage(contents, parent),_wrapper(NULL) {}
    PythonQtShell_LocoNetMessage(const LocoNetMessage&  original, QObject*  parent = 0):LocoNetMessage(original, parent),_wrapper(NULL) {}
    PythonQtShell_LocoNetMessage(int  len, QObject*  parent = 0):LocoNetMessage(len, parent),_wrapper(NULL) {}

   ~PythonQtShell_LocoNetMessage();


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
LocoNetMessage* new_LocoNetMessage();
LocoNetMessage* new_LocoNetMessage(LocoNetMessage*  original);
LocoNetMessage* new_LocoNetMessage(QString  s);
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
};





class PythonQtShell_LocoNetSystemConnectionMemo : public LocoNetSystemConnectionMemo
{
public:
    PythonQtShell_LocoNetSystemConnectionMemo(QObject*  parent = 0):LocoNetSystemConnectionMemo(parent),_wrapper(NULL) {}
    PythonQtShell_LocoNetSystemConnectionMemo(QString  prefix, QString  name):LocoNetSystemConnectionMemo(prefix, name),_wrapper(NULL) {}

   ~PythonQtShell_LocoNetSystemConnectionMemo();

virtual void _register();
virtual void dispose();
virtual bool  provides(QString  type);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_LocoNetSystemConnectionMemo : public LocoNetSystemConnectionMemo
{ public:
inline void py_q__register() { LocoNetSystemConnectionMemo::_register(); }
inline void py_q_dispose() { LocoNetSystemConnectionMemo::dispose(); }
inline bool  py_q_provides(QString  type) { return LocoNetSystemConnectionMemo::provides(type); }
};

class PythonQtWrapper_LocoNetSystemConnectionMemo : public QObject
{ Q_OBJECT
public:
public slots:
LocoNetSystemConnectionMemo* new_LocoNetSystemConnectionMemo(QObject*  parent = 0);
LocoNetSystemConnectionMemo* new_LocoNetSystemConnectionMemo(QString  prefix, QString  name);
void delete_LocoNetSystemConnectionMemo(LocoNetSystemConnectionMemo* obj) { delete obj; } 
   void _register(LocoNetSystemConnectionMemo* theWrappedObject);
   void py_q__register(LocoNetSystemConnectionMemo* theWrappedObject){  (((PythonQtPublicPromoter_LocoNetSystemConnectionMemo*)theWrappedObject)->py_q__register());}
   void configureCommandStation(LocoNetSystemConnectionMemo* theWrappedObject, LnCommandStationType*  type, bool  mTurnoutNoRetry, bool  mTurnoutExtraSpace, bool  mTranspondingAvailable);
   void configureManagers(LocoNetSystemConnectionMemo* theWrappedObject);
   void dispose(LocoNetSystemConnectionMemo* theWrappedObject);
   void py_q_dispose(LocoNetSystemConnectionMemo* theWrappedObject){  (((PythonQtPublicPromoter_LocoNetSystemConnectionMemo*)theWrappedObject)->py_q_dispose());}
   LnClockControl*  getClockControl(LocoNetSystemConnectionMemo* theWrappedObject);
   LnLightManager*  getLightManager(LocoNetSystemConnectionMemo* theWrappedObject);
   LnTrafficController*  getLnTrafficController(LocoNetSystemConnectionMemo* theWrappedObject);
   DefaultProgrammerManager*  getProgrammerManager(LocoNetSystemConnectionMemo* theWrappedObject);
   bool  provides(LocoNetSystemConnectionMemo* theWrappedObject, QString  type);
   bool  py_q_provides(LocoNetSystemConnectionMemo* theWrappedObject, QString  type){  return (((PythonQtPublicPromoter_LocoNetSystemConnectionMemo*)theWrappedObject)->py_q_provides(type));}
   void resetProgrammer(LocoNetSystemConnectionMemo* theWrappedObject);
   void setLnTrafficController(LocoNetSystemConnectionMemo* theWrappedObject, LnTrafficController*  lt);
   void setProgrammerManager(LocoNetSystemConnectionMemo* theWrappedObject, DefaultProgrammerManager*  p);
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
   void debug(Logger* theWrappedObject, QString  s) const;
   void info(Logger* theWrappedObject, QString  s);
   bool  isDebugEnabled(Logger* theWrappedObject) const;
   bool  isInfoEnabled(Logger* theWrappedObject);
   bool  isTraceEnabled(Logger* theWrappedObject);
   void sendError(Logger* theWrappedObject, QString  arg__1);
   void setDebugEnabled(Logger* theWrappedObject, bool  bState);
   void setInfoEnabled(Logger* theWrappedObject, bool  bState);
   void setTraceEnabled(Logger* theWrappedObject, bool  bState);
   void trace(Logger* theWrappedObject, QString  s);
   void warn(Logger* theWrappedObject, QString  s) const;
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

virtual void addPropertyChangeListener(PropertyChangeListener*  arg__1);
virtual void addPropertyChangeListener(PropertyChangeListener*  arg__1, QString  arg__2, const QString  arg__3);
virtual void addPropertyChangeListener(QString  arg__1, PropertyChangeListener*  arg__2);
virtual void addPropertyChangeListener(QString  arg__1, PropertyChangeListener*  arg__2, QString  arg__3, QString  arg__4);
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
virtual QString  getListenerRef(PropertyChangeListener*  arg__1);
virtual QList<QString >*  getListenerRefs();
virtual int  getNumPropertyChangeListeners();
virtual QVariant  getProperty(QString  key);
virtual QVector<PropertyChangeListener* >  getPropertyChangeListenersByReference(QString  name);
virtual QSet<QString >  getPropertyKeys();
virtual int  getState();
virtual QString  getSystemName() const;
virtual QString  getUserName() const;
virtual uint  hashCode();
virtual void removeProperty(QString  arg__1);
virtual void removePropertyChangeListener(PropertyChangeListener*  arg__1);
virtual void removePropertyChangeListener(QString  arg__1, PropertyChangeListener*  arg__2);
virtual void setComment(QString  arg__1);
virtual void setProperty(QString  key, QVariant  arg__2);
virtual void setState(int  arg__1);
virtual void setUserName(QString  s);
virtual void timerEvent(QTimerEvent*  event);
virtual void updateListenerRef(PropertyChangeListener*  l, QString  arg__2);
virtual void vetoableChange(PropertyChangeEvent*  arg__1);

  const QMetaObject* metaObject() const;
  int qt_metacall(QMetaObject::Call call, int id, void** args);
  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_NamedBean : public NamedBean
{ public:
inline void py_q_addPropertyChangeListener(PropertyChangeListener*  arg__1) { NamedBean::addPropertyChangeListener(arg__1); }
inline void py_q_addPropertyChangeListener(PropertyChangeListener*  arg__1, QString  arg__2, const QString  arg__3) { NamedBean::addPropertyChangeListener(arg__1, arg__2, arg__3); }
inline void py_q_addPropertyChangeListener(QString  arg__1, PropertyChangeListener*  arg__2) { NamedBean::addPropertyChangeListener(arg__1, arg__2); }
inline void py_q_addPropertyChangeListener(QString  arg__1, PropertyChangeListener*  arg__2, QString  arg__3, QString  arg__4) { NamedBean::addPropertyChangeListener(arg__1, arg__2, arg__3, arg__4); }
inline int  py_q_compareSystemNameSuffix(QString  suffix1, QString  suffix2, NamedBean*  n2) { return NamedBean::compareSystemNameSuffix(suffix1, suffix2, n2); }
inline int  py_q_compareTo(NamedBean*  n2) { return NamedBean::compareTo(n2); }
inline QString  py_q_describeState(int  arg__1) { return NamedBean::describeState(arg__1); }
inline void py_q_dispose() { NamedBean::dispose(); }
inline bool  py_q_equals(QObject*  obj) { return NamedBean::equals(obj); }
inline QString  py_q_getBeanType() { return NamedBean::getBeanType(); }
inline QString  py_q_getComment() { return NamedBean::getComment(); }
inline QString  py_q_getDisplayName() { return NamedBean::getDisplayName(); }
inline QString  py_q_getFullyFormattedDisplayName() { return NamedBean::getFullyFormattedDisplayName(); }
inline QString  py_q_getListenerRef(PropertyChangeListener*  arg__1) { return NamedBean::getListenerRef(arg__1); }
inline QList<QString >*  py_q_getListenerRefs() { return NamedBean::getListenerRefs(); }
inline int  py_q_getNumPropertyChangeListeners() { return NamedBean::getNumPropertyChangeListeners(); }
inline QVariant  py_q_getProperty(QString  key) { return NamedBean::getProperty(key); }
inline QVector<PropertyChangeListener* >  py_q_getPropertyChangeListenersByReference(QString  name) { return NamedBean::getPropertyChangeListenersByReference(name); }
inline QSet<QString >  py_q_getPropertyKeys() { return NamedBean::getPropertyKeys(); }
inline int  py_q_getState() { return NamedBean::getState(); }
inline QString  py_q_getSystemName() const { return this->getSystemName(); }
inline QString  py_q_getUserName() const { return NamedBean::getUserName(); }
inline uint  py_q_hashCode() { return NamedBean::hashCode(); }
inline void py_q_removeProperty(QString  arg__1) { NamedBean::removeProperty(arg__1); }
inline void py_q_removePropertyChangeListener(PropertyChangeListener*  arg__1) { NamedBean::removePropertyChangeListener(arg__1); }
inline void py_q_removePropertyChangeListener(QString  arg__1, PropertyChangeListener*  arg__2) { NamedBean::removePropertyChangeListener(arg__1, arg__2); }
inline void py_q_setComment(QString  arg__1) { NamedBean::setComment(arg__1); }
inline void py_q_setProperty(QString  key, QVariant  arg__2) { NamedBean::setProperty(key, arg__2); }
inline void py_q_setState(int  arg__1) { NamedBean::setState(arg__1); }
inline void py_q_setUserName(QString  s) { NamedBean::setUserName(s); }
inline void py_q_updateListenerRef(PropertyChangeListener*  l, QString  arg__2) { NamedBean::updateListenerRef(l, arg__2); }
inline void py_q_vetoableChange(PropertyChangeEvent*  arg__1) { NamedBean::vetoableChange(arg__1); }
};

class PythonQtWrapper_NamedBean : public QObject
{ Q_OBJECT
public:
Q_ENUMS(STATES )
enum STATES{
  UNKNOWN = NamedBean::UNKNOWN,   INCONSISTENT = NamedBean::INCONSISTENT};
public slots:
NamedBean* new_NamedBean(QObject*  parent = 0);
NamedBean* new_NamedBean(QString  name, QObject*  parent = 0);
NamedBean* new_NamedBean(const NamedBean&  arg__1);
void delete_NamedBean(NamedBean* obj) { delete obj; } 
   void addPropertyChangeListener(NamedBean* theWrappedObject, PropertyChangeListener*  arg__1);
   void py_q_addPropertyChangeListener(NamedBean* theWrappedObject, PropertyChangeListener*  arg__1){  (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_addPropertyChangeListener(arg__1));}
   void addPropertyChangeListener(NamedBean* theWrappedObject, PropertyChangeListener*  arg__1, QString  arg__2, const QString  arg__3);
   void py_q_addPropertyChangeListener(NamedBean* theWrappedObject, PropertyChangeListener*  arg__1, QString  arg__2, const QString  arg__3){  (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_addPropertyChangeListener(arg__1, arg__2, arg__3));}
   void addPropertyChangeListener(NamedBean* theWrappedObject, QString  arg__1, PropertyChangeListener*  arg__2);
   void py_q_addPropertyChangeListener(NamedBean* theWrappedObject, QString  arg__1, PropertyChangeListener*  arg__2){  (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_addPropertyChangeListener(arg__1, arg__2));}
   void addPropertyChangeListener(NamedBean* theWrappedObject, QString  arg__1, PropertyChangeListener*  arg__2, QString  arg__3, QString  arg__4);
   void py_q_addPropertyChangeListener(NamedBean* theWrappedObject, QString  arg__1, PropertyChangeListener*  arg__2, QString  arg__3, QString  arg__4){  (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_addPropertyChangeListener(arg__1, arg__2, arg__3, arg__4));}
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
   QString  getListenerRef(NamedBean* theWrappedObject, PropertyChangeListener*  arg__1);
   QString  py_q_getListenerRef(NamedBean* theWrappedObject, PropertyChangeListener*  arg__1){  return (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_getListenerRef(arg__1));}
   QList<QString >*  getListenerRefs(NamedBean* theWrappedObject);
   QList<QString >*  py_q_getListenerRefs(NamedBean* theWrappedObject){  return (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_getListenerRefs());}
   int  getNumPropertyChangeListeners(NamedBean* theWrappedObject);
   int  py_q_getNumPropertyChangeListeners(NamedBean* theWrappedObject){  return (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_getNumPropertyChangeListeners());}
   QVariant  getProperty(NamedBean* theWrappedObject, QString  key);
   QVariant  py_q_getProperty(NamedBean* theWrappedObject, QString  key){  return (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_getProperty(key));}
   QVector<PropertyChangeListener* >  getPropertyChangeListenersByReference(NamedBean* theWrappedObject, QString  name);
   QVector<PropertyChangeListener* >  py_q_getPropertyChangeListenersByReference(NamedBean* theWrappedObject, QString  name){  return (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_getPropertyChangeListenersByReference(name));}
   QSet<QString >  getPropertyKeys(NamedBean* theWrappedObject);
   QSet<QString >  py_q_getPropertyKeys(NamedBean* theWrappedObject){  return (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_getPropertyKeys());}
   int  getState(NamedBean* theWrappedObject);
   int  py_q_getState(NamedBean* theWrappedObject){  return (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_getState());}
   QString  getSystemName(NamedBean* theWrappedObject) const;
   QString  py_q_getSystemName(NamedBean* theWrappedObject) const{  return (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_getSystemName());}
   QString  getUserName(NamedBean* theWrappedObject) const;
   QString  py_q_getUserName(NamedBean* theWrappedObject) const{  return (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_getUserName());}
   uint  hashCode(NamedBean* theWrappedObject);
   uint  py_q_hashCode(NamedBean* theWrappedObject){  return (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_hashCode());}
   QString  static_NamedBean_normalizeUserName(QString  arg__1);
   void removeProperty(NamedBean* theWrappedObject, QString  arg__1);
   void py_q_removeProperty(NamedBean* theWrappedObject, QString  arg__1){  (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_removeProperty(arg__1));}
   void removePropertyChangeListener(NamedBean* theWrappedObject, PropertyChangeListener*  arg__1);
   void py_q_removePropertyChangeListener(NamedBean* theWrappedObject, PropertyChangeListener*  arg__1){  (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_removePropertyChangeListener(arg__1));}
   void removePropertyChangeListener(NamedBean* theWrappedObject, QString  arg__1, PropertyChangeListener*  arg__2);
   void py_q_removePropertyChangeListener(NamedBean* theWrappedObject, QString  arg__1, PropertyChangeListener*  arg__2){  (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_removePropertyChangeListener(arg__1, arg__2));}
   void setComment(NamedBean* theWrappedObject, QString  arg__1);
   void py_q_setComment(NamedBean* theWrappedObject, QString  arg__1){  (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_setComment(arg__1));}
   void setProperty(NamedBean* theWrappedObject, QString  key, QVariant  arg__2);
   void py_q_setProperty(NamedBean* theWrappedObject, QString  key, QVariant  arg__2){  (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_setProperty(key, arg__2));}
   void setState(NamedBean* theWrappedObject, int  arg__1);
   void py_q_setState(NamedBean* theWrappedObject, int  arg__1){  (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_setState(arg__1));}
   void setUserName(NamedBean* theWrappedObject, QString  s);
   void py_q_setUserName(NamedBean* theWrappedObject, QString  s){  (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_setUserName(s));}
   void updateListenerRef(NamedBean* theWrappedObject, PropertyChangeListener*  l, QString  arg__2);
   void py_q_updateListenerRef(NamedBean* theWrappedObject, PropertyChangeListener*  l, QString  arg__2){  (((PythonQtPublicPromoter_NamedBean*)theWrappedObject)->py_q_updateListenerRef(l, arg__2));}
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
virtual QString  className();
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
virtual SystemConnectionMemo*  getSystemConnectionMemo() const;
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
inline QString  py_q_className() { return this->className(); }
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
   QString  className(NetworkPortAdapter* theWrappedObject);
   QString  py_q_className(NetworkPortAdapter* theWrappedObject){  return (((PythonQtPublicPromoter_NetworkPortAdapter*)theWrappedObject)->py_q_className());}
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

virtual void showPopUp(Positionable*  p, QGraphicsSceneMouseEvent*  event);

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
inline void py_q_showPopUp(Positionable*  p, QGraphicsSceneMouseEvent*  event) { PanelEditor::showPopUp(p, event); }
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
   QString  getClassName(PanelEditor* theWrappedObject);
   void init(PanelEditor* theWrappedObject, QString  name);
   void initView(PanelEditor* theWrappedObject);
   void makeColorMenu(PanelEditor* theWrappedObject, QMenu*  colorMenu);
   void pasteItem(PanelEditor* theWrappedObject, QGraphicsSceneMouseEvent*  e);
   void pasteItemPopUp(PanelEditor* theWrappedObject, QGraphicsSceneMouseEvent*  event);
   void repaint(PanelEditor* theWrappedObject);
   void setNextLocation(PanelEditor* theWrappedObject, Positionable*  obj);
   void setRemoveMenu(PanelEditor* theWrappedObject, Positionable*  p, QMenu*  popup);
   void showAddItemPopUp(PanelEditor* theWrappedObject, QGraphicsSceneMouseEvent*  event, QMenu*  popup);
   void showMultiSelectPopUp(PanelEditor* theWrappedObject, QGraphicsSceneMouseEvent*  event, Positionable*  p);
   void showPopUp(PanelEditor* theWrappedObject, Positionable*  p, QGraphicsSceneMouseEvent*  event);
   void py_q_showPopUp(PanelEditor* theWrappedObject, Positionable*  p, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_PanelEditor*)theWrappedObject)->py_q_showPopUp(p, event));}
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
virtual SystemConnectionMemo*  getSystemConnectionMemo() const;
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
inline SystemConnectionMemo*  py_q_getSystemConnectionMemo() const { return PortAdapter::getSystemConnectionMemo(); }
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
   SystemConnectionMemo*  getSystemConnectionMemo(PortAdapter* theWrappedObject) const;
   SystemConnectionMemo*  py_q_getSystemConnectionMemo(PortAdapter* theWrappedObject) const{  return (((PythonQtPublicPromoter_PortAdapter*)theWrappedObject)->py_q_getSystemConnectionMemo());}
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
    PythonQtShell_Positionable():Positionable(),_wrapper(NULL) {}

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
virtual QRectF  getBounds(QRectF  arg__1 = QRectF());
virtual QString  getClass();
virtual int  getDegrees();
virtual int  getDisplayLevel();
virtual Editor*  getEditor();
virtual QFont  getFont();
virtual QColor  getForeground();
virtual QString  getGroupName();
virtual int  getHeight();
virtual QString  getId();
virtual QPointF  getLocation();
virtual QString  getNameString();
virtual NamedBean*  getNamedBean();
virtual bool  getSaveOpaque();
virtual double  getScale();
virtual QString  getToolTip();
virtual bool  getViewCoordinates();
virtual int  getWidth();
virtual int  getX();
virtual int  getY();
virtual bool  isControlling();
virtual bool  isEditable();
virtual bool  isHidden();
virtual bool  isOpaque();
virtual bool  isPositionable();
virtual bool  isVisible();
virtual void languageChange();
virtual int  maxHeight();
virtual int  maxWidth();
virtual void paint(EditScene*  arg__1);
virtual void remove();
virtual bool  requestFocusInWindow();
virtual void rotate(int  arg__1);
virtual QObject*  self();
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
virtual void setId(QString  arg__1);
virtual void setLevel(int  arg__1);
virtual void setLocation(QPointF  arg__1);
virtual void setLocation(int  arg__1, int  arg__2);
virtual void setOpaque(bool  arg__1);
virtual void setPositionable(bool  arg__1);
virtual bool  setRotateMenu(QMenu*  arg__1);
virtual bool  setRotateOrthogonalMenu(QMenu*  arg__1);
virtual void setScale(double  arg__1);
virtual bool  setScaleMenu(QMenu*  arg__1);
virtual void setShowToolTip(bool  arg__1);
virtual void setSize(int  arg__1, int  arg__2);
virtual bool  setTextEditMenu(QMenu*  arg__1);
virtual void setToolTip(QString  tip);
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
inline bool  py_q_contains(int  arg__1, int  arg__2) { return Positionable::contains(arg__1, arg__2); }
inline Positionable*  py_q_deepClone() { return this->deepClone(); }
inline void py_q_doMouseClicked(QGraphicsSceneMouseEvent*  arg__1) { Positionable::doMouseClicked(arg__1); }
inline void py_q_doMouseDragged(QGraphicsSceneMouseEvent*  arg__1) { Positionable::doMouseDragged(arg__1); }
inline void py_q_doMouseEntered(QGraphicsSceneMouseEvent*  arg__1) { Positionable::doMouseEntered(arg__1); }
inline void py_q_doMouseExited(QGraphicsSceneMouseEvent*  arg__1) { Positionable::doMouseExited(arg__1); }
inline void py_q_doMouseMoved(QGraphicsSceneMouseEvent*  arg__1) { Positionable::doMouseMoved(arg__1); }
inline void py_q_doMousePressed(QGraphicsSceneMouseEvent*  arg__1) { Positionable::doMousePressed(arg__1); }
inline void py_q_doMouseReleased(QGraphicsSceneMouseEvent*  arg__1) { Positionable::doMouseReleased(arg__1); }
inline bool  py_q_doViemMenu() { return Positionable::doViemMenu(); }
inline Positionable*  py_q_finishClone(Positionable*  arg__1) { return this->finishClone(arg__1); }
inline QColor  py_q_getBackground() { return Positionable::getBackground(); }
inline QRectF  py_q_getBounds(QRectF  arg__1 = QRectF()) { return Positionable::getBounds(arg__1); }
inline QString  py_q_getClass() { return Positionable::getClass(); }
inline int  py_q_getDegrees() { return Positionable::getDegrees(); }
inline int  py_q_getDisplayLevel() { return this->getDisplayLevel(); }
inline Editor*  py_q_getEditor() { return this->getEditor(); }
inline QFont  py_q_getFont() { return Positionable::getFont(); }
inline QColor  py_q_getForeground() { return Positionable::getForeground(); }
inline QString  py_q_getGroupName() { return Positionable::getGroupName(); }
inline int  py_q_getHeight() { return Positionable::getHeight(); }
inline QString  py_q_getId() { return Positionable::getId(); }
inline QPointF  py_q_getLocation() { return Positionable::getLocation(); }
inline QString  py_q_getNameString() { return Positionable::getNameString(); }
inline NamedBean*  py_q_getNamedBean() { return Positionable::getNamedBean(); }
inline bool  py_q_getSaveOpaque() { return Positionable::getSaveOpaque(); }
inline double  py_q_getScale() { return Positionable::getScale(); }
inline QString  py_q_getToolTip() { return Positionable::getToolTip(); }
inline bool  py_q_getViewCoordinates() { return Positionable::getViewCoordinates(); }
inline int  py_q_getWidth() { return Positionable::getWidth(); }
inline int  py_q_getX() { return this->getX(); }
inline int  py_q_getY() { return this->getY(); }
inline bool  py_q_isControlling() { return this->isControlling(); }
inline bool  py_q_isEditable() { return this->isEditable(); }
inline bool  py_q_isHidden() { return this->isHidden(); }
inline bool  py_q_isOpaque() { return Positionable::isOpaque(); }
inline bool  py_q_isPositionable() { return this->isPositionable(); }
inline bool  py_q_isVisible() { return Positionable::isVisible(); }
inline void py_q_languageChange() { Positionable::languageChange(); }
inline int  py_q_maxHeight() { return this->maxHeight(); }
inline int  py_q_maxWidth() { return this->maxWidth(); }
inline void py_q_paint(EditScene*  arg__1) { Positionable::paint(arg__1); }
inline void py_q_remove() { Positionable::remove(); }
inline bool  py_q_requestFocusInWindow() { return Positionable::requestFocusInWindow(); }
inline void py_q_rotate(int  arg__1) { Positionable::rotate(arg__1); }
inline QObject*  py_q_self() { return this->self(); }
inline void py_q_setBackground(QColor  arg__1) { Positionable::setBackground(arg__1); }
inline void py_q_setControlling(bool  arg__1) { this->setControlling(arg__1); }
inline bool  py_q_setDisableControlMenu(QMenu*  arg__1) { return Positionable::setDisableControlMenu(arg__1); }
inline void py_q_setDisplayLevel(int  arg__1) { this->setDisplayLevel(arg__1); }
inline bool  py_q_setEditIconMenu(QMenu*  arg__1) { return Positionable::setEditIconMenu(arg__1); }
inline bool  py_q_setEditItemMenu(QMenu*  arg__1) { return Positionable::setEditItemMenu(arg__1); }
inline void py_q_setEditable(bool  arg__1) { this->setEditable(arg__1); }
inline void py_q_setEditor(Editor*  arg__1) { this->setEditor(arg__1); }
inline void py_q_setForeground(QColor  arg__1) { Positionable::setForeground(arg__1); }
inline void py_q_setHidden(bool  arg__1) { this->setHidden(arg__1); }
inline void py_q_setId(QString  arg__1) { Positionable::setId(arg__1); }
inline void py_q_setLevel(int  arg__1) { Positionable::setLevel(arg__1); }
inline void py_q_setLocation(QPointF  arg__1) { Positionable::setLocation(arg__1); }
inline void py_q_setLocation(int  arg__1, int  arg__2) { Positionable::setLocation(arg__1, arg__2); }
inline void py_q_setOpaque(bool  arg__1) { Positionable::setOpaque(arg__1); }
inline void py_q_setPositionable(bool  arg__1) { this->setPositionable(arg__1); }
inline bool  py_q_setRotateMenu(QMenu*  arg__1) { return Positionable::setRotateMenu(arg__1); }
inline bool  py_q_setRotateOrthogonalMenu(QMenu*  arg__1) { return Positionable::setRotateOrthogonalMenu(arg__1); }
inline void py_q_setScale(double  arg__1) { Positionable::setScale(arg__1); }
inline bool  py_q_setScaleMenu(QMenu*  arg__1) { return Positionable::setScaleMenu(arg__1); }
inline void py_q_setShowToolTip(bool  arg__1) { this->setShowToolTip(arg__1); }
inline void py_q_setSize(int  arg__1, int  arg__2) { Positionable::setSize(arg__1, arg__2); }
inline bool  py_q_setTextEditMenu(QMenu*  arg__1) { return Positionable::setTextEditMenu(arg__1); }
inline void py_q_setToolTip(QString  tip) { Positionable::setToolTip(tip); }
inline void py_q_setViewCoordinates(bool  arg__1) { Positionable::setViewCoordinates(arg__1); }
inline void py_q_setVisible(bool  b) { Positionable::setVisible(b); }
inline void py_q_showHidden() { this->showHidden(); }
inline bool  py_q_showPopUp(QMenu*  arg__1) { return Positionable::showPopUp(arg__1); }
inline bool  py_q_showToolTip() { return this->showToolTip(); }
inline bool  py_q_storeItem() { return Positionable::storeItem(); }
inline bool  py_q_updateScene() { return Positionable::updateScene(); }
inline void py_q_updateSize() { Positionable::updateSize(); }
};

class PythonQtWrapper_Positionable : public QObject
{ Q_OBJECT
public:
public slots:
Positionable* new_Positionable();
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
   QRectF  getBounds(Positionable* theWrappedObject, QRectF  arg__1 = QRectF());
   QRectF  py_q_getBounds(Positionable* theWrappedObject, QRectF  arg__1 = QRectF()){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_getBounds(arg__1));}
   QString  getClass(Positionable* theWrappedObject);
   QString  py_q_getClass(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_getClass());}
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
   QString  getId(Positionable* theWrappedObject);
   QString  py_q_getId(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_getId());}
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
   QString  getToolTip(Positionable* theWrappedObject);
   QString  py_q_getToolTip(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_getToolTip());}
   bool  getViewCoordinates(Positionable* theWrappedObject);
   bool  py_q_getViewCoordinates(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_getViewCoordinates());}
   int  getWidth(Positionable* theWrappedObject);
   int  py_q_getWidth(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_getWidth());}
   int  getX(Positionable* theWrappedObject);
   int  py_q_getX(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_getX());}
   int  getY(Positionable* theWrappedObject);
   int  py_q_getY(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_getY());}
   bool  isControlling(Positionable* theWrappedObject);
   bool  py_q_isControlling(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_isControlling());}
   bool  isEditable(Positionable* theWrappedObject);
   bool  py_q_isEditable(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_isEditable());}
   bool  isHidden(Positionable* theWrappedObject);
   bool  py_q_isHidden(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_isHidden());}
   bool  isOpaque(Positionable* theWrappedObject);
   bool  py_q_isOpaque(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_isOpaque());}
   bool  isPositionable(Positionable* theWrappedObject);
   bool  py_q_isPositionable(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_isPositionable());}
   bool  isVisible(Positionable* theWrappedObject);
   bool  py_q_isVisible(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_isVisible());}
   void languageChange(Positionable* theWrappedObject);
   void py_q_languageChange(Positionable* theWrappedObject){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_languageChange());}
   int  maxHeight(Positionable* theWrappedObject);
   int  py_q_maxHeight(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_maxHeight());}
   int  maxWidth(Positionable* theWrappedObject);
   int  py_q_maxWidth(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_maxWidth());}
   void paint(Positionable* theWrappedObject, EditScene*  arg__1);
   void py_q_paint(Positionable* theWrappedObject, EditScene*  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_paint(arg__1));}
   void remove(Positionable* theWrappedObject);
   void py_q_remove(Positionable* theWrappedObject){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_remove());}
   bool  requestFocusInWindow(Positionable* theWrappedObject);
   bool  py_q_requestFocusInWindow(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_requestFocusInWindow());}
   void rotate(Positionable* theWrappedObject, int  arg__1);
   void py_q_rotate(Positionable* theWrappedObject, int  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_rotate(arg__1));}
   QObject*  self(Positionable* theWrappedObject);
   QObject*  py_q_self(Positionable* theWrappedObject){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_self());}
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
   void setHidden(Positionable* theWrappedObject, bool  arg__1);
   void py_q_setHidden(Positionable* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setHidden(arg__1));}
   void setId(Positionable* theWrappedObject, QString  arg__1);
   void py_q_setId(Positionable* theWrappedObject, QString  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setId(arg__1));}
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
   void setShowToolTip(Positionable* theWrappedObject, bool  arg__1);
   void py_q_setShowToolTip(Positionable* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setShowToolTip(arg__1));}
   void setSize(Positionable* theWrappedObject, int  arg__1, int  arg__2);
   void py_q_setSize(Positionable* theWrappedObject, int  arg__1, int  arg__2){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setSize(arg__1, arg__2));}
   bool  setTextEditMenu(Positionable* theWrappedObject, QMenu*  arg__1);
   bool  py_q_setTextEditMenu(Positionable* theWrappedObject, QMenu*  arg__1){  return (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setTextEditMenu(arg__1));}
   void setToolTip(Positionable* theWrappedObject, QString  tip);
   void py_q_setToolTip(Positionable* theWrappedObject, QString  tip){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setToolTip(tip));}
   void setViewCoordinates(Positionable* theWrappedObject, bool  arg__1);
   void py_q_setViewCoordinates(Positionable* theWrappedObject, bool  arg__1){  (((PythonQtPublicPromoter_Positionable*)theWrappedObject)->py_q_setViewCoordinates(arg__1));}
   void setVisible(Positionable* theWrappedObject, bool  b);
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
    PythonQtShell_PositionableLabel(Positionable*  parent = 0):PositionableLabel(parent),_wrapper(NULL) {}
    PythonQtShell_PositionableLabel(QString  s, Editor*  editor, Positionable*  parent = 0):PositionableLabel(s, editor, parent),_wrapper(NULL) {}

   ~PythonQtShell_PositionableLabel();

virtual Positionable*  deepClone();
virtual void dispose();
virtual void doMouseClicked(QGraphicsSceneMouseEvent*  event);
virtual void doMouseDragged(QGraphicsSceneMouseEvent*  event);
virtual void doMouseEntered(QGraphicsSceneMouseEvent*  event);
virtual void doMouseExited(QGraphicsSceneMouseEvent*  event);
virtual void doMouseMoved(QGraphicsSceneMouseEvent*  event);
virtual void doMousePressed(QGraphicsSceneMouseEvent*  event);
virtual void doMouseReleased(QGraphicsSceneMouseEvent*  event);
virtual bool  doViemMenu();
virtual Positionable*  finishClone(Positionable*  p);
virtual QColor  getBackground();
virtual QRectF  getBounds(QRectF  arg__1 = QRectF());
virtual QString  getClassName();
virtual int  getDegrees();
virtual int  getDisplayLevel();
virtual Editor*  getEditor();
virtual QFont  getFont();
virtual QColor  getForeground();
virtual int  getHeight();
virtual QString  getNameString();
virtual NamedBean*  getNamedBean();
virtual bool  getSaveOpaque();
virtual double  getScale();
virtual QString  getToolTip();
virtual bool  getViewCoordinates();
virtual int  getWidth();
virtual bool  isControlling();
virtual bool  isEditable();
virtual bool  isHidden();
virtual bool  isOpaque();
virtual bool  isPositionable();
virtual bool  isVisible();
virtual int  maxHeight();
virtual int  maxWidth();
virtual void mousePressEvent(QMouseEvent*  ev);
virtual void remove();
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
virtual void setOpaque(bool  isOpaque);
virtual void setPositionable(bool  enabled);
virtual bool  setRotateMenu(QMenu*  popup);
virtual bool  setRotateOrthogonalMenu(QMenu*  popup);
virtual void setScale(double  s);
virtual bool  setScaleMenu(QMenu*  popup);
virtual void setShowToolTip(bool  set);
virtual bool  setTextEditMenu(QMenu*  popup);
virtual void setToolTip(QString  tip);
virtual void setViewCoordinates(bool  enabled);
virtual void setVisible(bool  b);
virtual void showHidden();
virtual bool  showPopUp(QMenu*  popup);
virtual bool  storeItem();
virtual bool  updateScene();
virtual void updateSize();

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
inline QString  py_q_getClassName() { return PositionableLabel::getClassName(); }
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
inline QString  py_q_getToolTip() { return PositionableLabel::getToolTip(); }
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
inline void py_q_mousePressEvent(QMouseEvent*  ev) { PositionableLabel::mousePressEvent(ev); }
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
inline void py_q_setShowToolTip(bool  set) { PositionableLabel::setShowToolTip(set); }
inline bool  py_q_setTextEditMenu(QMenu*  popup) { return PositionableLabel::setTextEditMenu(popup); }
inline void py_q_setToolTip(QString  tip) { PositionableLabel::setToolTip(tip); }
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
PositionableLabel* new_PositionableLabel(Positionable*  parent = 0);
PositionableLabel* new_PositionableLabel(QString  s, Editor*  editor, Positionable*  parent = 0);
void delete_PositionableLabel(PositionableLabel* obj) { delete obj; } 
   Positionable*  deepClone(PositionableLabel* theWrappedObject);
   Positionable*  py_q_deepClone(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_deepClone());}
   void dispose(PositionableLabel* theWrappedObject);
   void py_q_dispose(PositionableLabel* theWrappedObject){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_dispose());}
   void doMouseClicked(PositionableLabel* theWrappedObject, QGraphicsSceneMouseEvent*  event);
   void py_q_doMouseClicked(PositionableLabel* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_doMouseClicked(event));}
   void doMouseDragged(PositionableLabel* theWrappedObject, QGraphicsSceneMouseEvent*  event);
   void py_q_doMouseDragged(PositionableLabel* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_doMouseDragged(event));}
   void doMouseEntered(PositionableLabel* theWrappedObject, QGraphicsSceneMouseEvent*  event);
   void py_q_doMouseEntered(PositionableLabel* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_doMouseEntered(event));}
   void doMouseExited(PositionableLabel* theWrappedObject, QGraphicsSceneMouseEvent*  event);
   void py_q_doMouseExited(PositionableLabel* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_doMouseExited(event));}
   void doMouseMoved(PositionableLabel* theWrappedObject, QGraphicsSceneMouseEvent*  event);
   void py_q_doMouseMoved(PositionableLabel* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_doMouseMoved(event));}
   void doMousePressed(PositionableLabel* theWrappedObject, QGraphicsSceneMouseEvent*  event);
   void py_q_doMousePressed(PositionableLabel* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_doMousePressed(event));}
   void doMouseReleased(PositionableLabel* theWrappedObject, QGraphicsSceneMouseEvent*  event);
   void py_q_doMouseReleased(PositionableLabel* theWrappedObject, QGraphicsSceneMouseEvent*  event){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_doMouseReleased(event));}
   bool  doViemMenu(PositionableLabel* theWrappedObject);
   bool  py_q_doViemMenu(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_doViemMenu());}
   void editIcon(PositionableLabel* theWrappedObject);
   Positionable*  finishClone(PositionableLabel* theWrappedObject, Positionable*  p);
   Positionable*  py_q_finishClone(PositionableLabel* theWrappedObject, Positionable*  p){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_finishClone(p));}
   QColor  getBackground(PositionableLabel* theWrappedObject);
   QColor  py_q_getBackground(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getBackground());}
   QRectF  getBounds(PositionableLabel* theWrappedObject, QRectF  arg__1 = QRectF());
   QRectF  py_q_getBounds(PositionableLabel* theWrappedObject, QRectF  arg__1 = QRectF()){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getBounds(arg__1));}
   QString  getClassName(PositionableLabel* theWrappedObject);
   QString  py_q_getClassName(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getClassName());}
   int  getDegrees(PositionableLabel* theWrappedObject);
   int  py_q_getDegrees(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getDegrees());}
   int  getDisplayLevel(PositionableLabel* theWrappedObject);
   int  py_q_getDisplayLevel(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getDisplayLevel());}
   Editor*  getEditor(PositionableLabel* theWrappedObject);
   Editor*  py_q_getEditor(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getEditor());}
   QFont  getFont(PositionableLabel* theWrappedObject);
   QFont  py_q_getFont(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getFont());}
   QColor  getForeground(PositionableLabel* theWrappedObject);
   QColor  py_q_getForeground(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getForeground());}
   int  getHeight(PositionableLabel* theWrappedObject);
   int  py_q_getHeight(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getHeight());}
   QPointF  getLocation(PositionableLabel* theWrappedObject);
   QString  getNameString(PositionableLabel* theWrappedObject);
   QString  py_q_getNameString(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getNameString());}
   NamedBean*  getNamedBean(PositionableLabel* theWrappedObject);
   NamedBean*  py_q_getNamedBean(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getNamedBean());}
   QSize  getPreferredSize(PositionableLabel* theWrappedObject);
   bool  getSaveOpaque(PositionableLabel* theWrappedObject);
   bool  py_q_getSaveOpaque(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getSaveOpaque());}
   double  getScale(PositionableLabel* theWrappedObject);
   double  py_q_getScale(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getScale());}
   QSize  getSize(PositionableLabel* theWrappedObject);
   QString  getToolTip(PositionableLabel* theWrappedObject);
   QString  py_q_getToolTip(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getToolTip());}
   QString  getUnRotatedText(PositionableLabel* theWrappedObject);
   bool  getViewCoordinates(PositionableLabel* theWrappedObject);
   bool  py_q_getViewCoordinates(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getViewCoordinates());}
   int  getWidth(PositionableLabel* theWrappedObject);
   int  py_q_getWidth(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_getWidth());}
   int  getX(PositionableLabel* theWrappedObject);
   int  getY(PositionableLabel* theWrappedObject);
   bool  isActive(PositionableLabel* theWrappedObject);
   bool  isBackground(PositionableLabel* theWrappedObject);
   bool  isControl(PositionableLabel* theWrappedObject);
   bool  isControlling(PositionableLabel* theWrappedObject);
   bool  py_q_isControlling(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_isControlling());}
   bool  isEditable(PositionableLabel* theWrappedObject);
   bool  py_q_isEditable(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_isEditable());}
   bool  isHidden(PositionableLabel* theWrappedObject);
   bool  py_q_isHidden(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_isHidden());}
   bool  isIcon(PositionableLabel* theWrappedObject);
   bool  isOpaque(PositionableLabel* theWrappedObject);
   bool  py_q_isOpaque(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_isOpaque());}
   bool  isPositionable(PositionableLabel* theWrappedObject);
   bool  py_q_isPositionable(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_isPositionable());}
   bool  isRotated(PositionableLabel* theWrappedObject);
   bool  isText(PositionableLabel* theWrappedObject);
   bool  isVisible(PositionableLabel* theWrappedObject);
   bool  py_q_isVisible(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_isVisible());}
   int  maxHeight(PositionableLabel* theWrappedObject);
   int  py_q_maxHeight(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_maxHeight());}
   int  maxHeightTrue(PositionableLabel* theWrappedObject);
   int  maxWidth(PositionableLabel* theWrappedObject);
   int  py_q_maxWidth(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_maxWidth());}
   int  maxWidthTrue(PositionableLabel* theWrappedObject);
   void mousePressEvent(PositionableLabel* theWrappedObject, QMouseEvent*  ev);
   void py_q_mousePressEvent(PositionableLabel* theWrappedObject, QMouseEvent*  ev){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_mousePressEvent(ev));}
   void remove(PositionableLabel* theWrappedObject);
   void py_q_remove(PositionableLabel* theWrappedObject){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_remove());}
   void rotate(PositionableLabel* theWrappedObject, int  deg);
   void py_q_rotate(PositionableLabel* theWrappedObject, int  deg){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_rotate(deg));}
   void saveOpaque(PositionableLabel* theWrappedObject, bool  set);
   QObject*  self(PositionableLabel* theWrappedObject);
   void setBackground(PositionableLabel* theWrappedObject, QColor  bg);
   void py_q_setBackground(PositionableLabel* theWrappedObject, QColor  bg){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setBackground(bg));}
   void setBackgroundColor(PositionableLabel* theWrappedObject, QColor  color);
   void setControlling(PositionableLabel* theWrappedObject, bool  enabled);
   void py_q_setControlling(PositionableLabel* theWrappedObject, bool  enabled){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setControlling(enabled));}
   void setDegrees(PositionableLabel* theWrappedObject, int  deg);
   bool  setDisableControlMenu(PositionableLabel* theWrappedObject, QMenu*  popup);
   bool  py_q_setDisableControlMenu(PositionableLabel* theWrappedObject, QMenu*  popup){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setDisableControlMenu(popup));}
   void setDisplayLevel(PositionableLabel* theWrappedObject, int  l);
   void py_q_setDisplayLevel(PositionableLabel* theWrappedObject, int  l){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setDisplayLevel(l));}
   bool  setEditIconMenu(PositionableLabel* theWrappedObject, QMenu*  popup);
   bool  py_q_setEditIconMenu(PositionableLabel* theWrappedObject, QMenu*  popup){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setEditIconMenu(popup));}
   bool  setEditItemMenu(PositionableLabel* theWrappedObject, QMenu*  popup);
   bool  py_q_setEditItemMenu(PositionableLabel* theWrappedObject, QMenu*  popup){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setEditItemMenu(popup));}
   void setEditable(PositionableLabel* theWrappedObject, bool  enabled);
   void py_q_setEditable(PositionableLabel* theWrappedObject, bool  enabled){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setEditable(enabled));}
   void setEditor(PositionableLabel* theWrappedObject, Editor*  ed);
   void py_q_setEditor(PositionableLabel* theWrappedObject, Editor*  ed){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setEditor(ed));}
   void setFont(PositionableLabel* theWrappedObject, const QFont&  font);
   void setForeground(PositionableLabel* theWrappedObject, QColor  c);
   void py_q_setForeground(PositionableLabel* theWrappedObject, QColor  c){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setForeground(c));}
   void setHidden(PositionableLabel* theWrappedObject, bool  hide);
   void py_q_setHidden(PositionableLabel* theWrappedObject, bool  hide){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setHidden(hide));}
   void setLevel(PositionableLabel* theWrappedObject, int  l);
   void py_q_setLevel(PositionableLabel* theWrappedObject, int  l){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setLevel(l));}
   void setLocation(PositionableLabel* theWrappedObject, QPointF  arg__1);
   void setLocation(PositionableLabel* theWrappedObject, int  x, int  y);
   void setOpaque(PositionableLabel* theWrappedObject, bool  isOpaque);
   void py_q_setOpaque(PositionableLabel* theWrappedObject, bool  isOpaque){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setOpaque(isOpaque));}
   void setPositionable(PositionableLabel* theWrappedObject, bool  enabled);
   void py_q_setPositionable(PositionableLabel* theWrappedObject, bool  enabled){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setPositionable(enabled));}
   bool  setRotateMenu(PositionableLabel* theWrappedObject, QMenu*  popup);
   bool  py_q_setRotateMenu(PositionableLabel* theWrappedObject, QMenu*  popup){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setRotateMenu(popup));}
   bool  setRotateOrthogonalMenu(PositionableLabel* theWrappedObject, QMenu*  popup);
   bool  py_q_setRotateOrthogonalMenu(PositionableLabel* theWrappedObject, QMenu*  popup){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setRotateOrthogonalMenu(popup));}
   void setScale(PositionableLabel* theWrappedObject, double  s);
   void py_q_setScale(PositionableLabel* theWrappedObject, double  s){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setScale(s));}
   bool  setScaleMenu(PositionableLabel* theWrappedObject, QMenu*  popup);
   bool  py_q_setScaleMenu(PositionableLabel* theWrappedObject, QMenu*  popup){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setScaleMenu(popup));}
   void setShowToolTip(PositionableLabel* theWrappedObject, bool  set);
   void py_q_setShowToolTip(PositionableLabel* theWrappedObject, bool  set){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setShowToolTip(set));}
   void setSize(PositionableLabel* theWrappedObject, int  x, int  y);
   void setStyleSheet(PositionableLabel* theWrappedObject);
   void setSuperText(PositionableLabel* theWrappedObject, QString  text);
   void setText(PositionableLabel* theWrappedObject, QString  text);
   bool  setTextEditMenu(PositionableLabel* theWrappedObject, QMenu*  popup);
   bool  py_q_setTextEditMenu(PositionableLabel* theWrappedObject, QMenu*  popup){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setTextEditMenu(popup));}
   void setToolTip(PositionableLabel* theWrappedObject, QString  tip);
   void py_q_setToolTip(PositionableLabel* theWrappedObject, QString  tip){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setToolTip(tip));}
   void setViewCoordinates(PositionableLabel* theWrappedObject, bool  enabled);
   void py_q_setViewCoordinates(PositionableLabel* theWrappedObject, bool  enabled){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setViewCoordinates(enabled));}
   void setVisible(PositionableLabel* theWrappedObject, bool  b);
   void py_q_setVisible(PositionableLabel* theWrappedObject, bool  b){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_setVisible(b));}
   void showHidden(PositionableLabel* theWrappedObject);
   void py_q_showHidden(PositionableLabel* theWrappedObject){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_showHidden());}
   bool  showPopUp(PositionableLabel* theWrappedObject, QMenu*  popup);
   bool  py_q_showPopUp(PositionableLabel* theWrappedObject, QMenu*  popup){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_showPopUp(popup));}
   bool  showToolTip(PositionableLabel* theWrappedObject);
   bool  storeItem(PositionableLabel* theWrappedObject);
   bool  py_q_storeItem(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_storeItem());}
   bool  updateScene(PositionableLabel* theWrappedObject);
   bool  py_q_updateScene(PositionableLabel* theWrappedObject){  return (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_updateScene());}
   void updateSize(PositionableLabel* theWrappedObject);
   void py_q_updateSize(PositionableLabel* theWrappedObject){  (((PythonQtPublicPromoter_PositionableLabel*)theWrappedObject)->py_q_updateSize());}
};





class PythonQtShell_ProgListener : public ProgListener
{
public:
    PythonQtShell_ProgListener():ProgListener(),_wrapper(NULL) {}

   ~PythonQtShell_ProgListener();

virtual void programmingOpReply(int  value, int  status);
virtual QObject*  self();

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_ProgListener : public ProgListener
{ public:
inline void py_q_programmingOpReply(int  value, int  status) { this->programmingOpReply(value, status); }
inline QObject*  py_q_self() { return this->self(); }
};

class PythonQtWrapper_ProgListener : public QObject
{ Q_OBJECT
public:
public slots:
ProgListener* new_ProgListener();
void delete_ProgListener(ProgListener* obj) { delete obj; } 
   void py_q_programmingOpReply(ProgListener* theWrappedObject, int  value, int  status){  (((PythonQtPublicPromoter_ProgListener*)theWrappedObject)->py_q_programmingOpReply(value, status));}
   QObject*  py_q_self(ProgListener* theWrappedObject){  return (((PythonQtPublicPromoter_ProgListener*)theWrappedObject)->py_q_self());}
};





class PythonQtShell_ProgrammingMode : public ProgrammingMode
{
public:
    PythonQtShell_ProgrammingMode(QString  standardName, QObject*  parent = nullptr):ProgrammingMode(standardName, parent),_wrapper(NULL) {}
    PythonQtShell_ProgrammingMode(QString  standardName, QString  localName, QObject*  parent = nullptr):ProgrammingMode(standardName, localName, parent),_wrapper(NULL) {}

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
ProgrammingMode* new_ProgrammingMode(QString  standardName, QObject*  parent = nullptr);
ProgrammingMode* new_ProgrammingMode(QString  standardName, QString  localName, QObject*  parent = nullptr);
void delete_ProgrammingMode(ProgrammingMode* obj) { delete obj; } 
   bool  equals(ProgrammingMode* theWrappedObject, QObject*  o);
   QString  getStandardName(ProgrammingMode* theWrappedObject);
   int  hashCode(ProgrammingMode* theWrappedObject);
   bool  __eq__(ProgrammingMode* theWrappedObject, ProgrammingMode&  o);
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
    PythonQtShell_PropertyChangeListener():PropertyChangeListener(),_wrapper(NULL) {}

   ~PythonQtShell_PropertyChangeListener();

virtual void propertyChange(PropertyChangeEvent*  e);
virtual QObject*  self();

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_PropertyChangeListener : public PropertyChangeListener
{ public:
inline void py_q_propertyChange(PropertyChangeEvent*  e) { PropertyChangeListener::propertyChange(e); }
inline QObject*  py_q_self() { return this->self(); }
};

class PythonQtWrapper_PropertyChangeListener : public QObject
{ Q_OBJECT
public:
public slots:
PropertyChangeListener* new_PropertyChangeListener();
void delete_PropertyChangeListener(PropertyChangeListener* obj) { delete obj; } 
   void py_q_propertyChange(PropertyChangeListener* theWrappedObject, PropertyChangeEvent*  e){  (((PythonQtPublicPromoter_PropertyChangeListener*)theWrappedObject)->py_q_propertyChange(e));}
   QObject*  self(PropertyChangeListener* theWrappedObject);
   QObject*  py_q_self(PropertyChangeListener* theWrappedObject){  return (((PythonQtPublicPromoter_PropertyChangeListener*)theWrappedObject)->py_q_self());}
};





class PythonQtShell_PropertyChangeSupport : public PropertyChangeSupport
{
public:
    PythonQtShell_PropertyChangeSupport():PropertyChangeSupport(),_wrapper(NULL) {}

   ~PythonQtShell_PropertyChangeSupport();

virtual void addPropertyChangeListener(PropertyChangeListener*  listener);
virtual void addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);
virtual void firePropertyChange(QString  propertyName, QVariant  oldValue, QVariant  newValue) const;
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners() const;
virtual QVector<PropertyChangeListener* >  getPropertyChangeListeners(QString  propertyName);
virtual void removePropertyChangeListener(PropertyChangeListener*  listener);
virtual void removePropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener);

  PythonQtInstanceWrapper* _wrapper; 
};

class PythonQtPublicPromoter_PropertyChangeSupport : public PropertyChangeSupport
{ public:
inline void py_q_addPropertyChangeListener(PropertyChangeListener*  listener) { PropertyChangeSupport::addPropertyChangeListener(listener); }
inline void py_q_addPropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener) { PropertyChangeSupport::addPropertyChangeListener(propertyName, listener); }
inline void py_q_firePropertyChange(QString  propertyName, QVariant  oldValue, QVariant  newValue) const { PropertyChangeSupport::firePropertyChange(propertyName, oldValue, newValue); }
inline QVector<PropertyChangeListener* >  py_q_getPropertyChangeListeners() const { return PropertyChangeSupport::getPropertyChangeListeners(); }
inline QVector<PropertyChangeListener* >  py_q_getPropertyChangeListeners(QString  propertyName) { return PropertyChangeSupport::getPropertyChangeListeners(propertyName); }
inline void py_q_removePropertyChangeListener(PropertyChangeListener*  listener) { PropertyChangeSupport::removePropertyChangeListener(listener); }
inline void py_q_removePropertyChangeListener(QString  propertyName, PropertyChangeListener*  listener) { PropertyChangeSupport::removePropertyChangeListener(propertyName, listener); }
};

class PythonQtWrapper_PropertyChangeSupport : public QObject
{ Q_OBJECT
public:
public slots:
PropertyChangeSupport* new_PropertyChangeSupport();
void delete_PropertyChangeSupport(PropertyChangeSupport* obj) { delete obj; } 
   void addPropertyChangeListener(PropertyChangeSupport* theWrappedObject, PropertyChangeListener*  listener);
   void py_q_addPropertyChangeListener(PropertyChangeSupport* theWrappedObject, PropertyChangeListener*  listener){  (((PythonQtPublicPromoter_PropertyChangeSupport*)theWrappedObject)->py_q_addPropertyChangeListener(listener));}
   void addPropertyChangeListener(PropertyChangeSupport* theWrappedObject, QString  propertyName, PropertyChangeListener*  listener);
   void py_q_addPropertyChangeListener(PropertyChangeSupport* theWrappedObject, QString  propertyName, PropertyChangeListener*  listener){  (((PythonQtPublicPromoter_PropertyChangeSupport*)theWrappedObject)->py_q_addPropertyChangeListener(propertyName, listener));}
   void fireIndexedPropertyChange(PropertyChangeSupport* theWrappedObject, QString  propertyName, int  index, QVariant  oldValue, QVariant  newValue);
   void firePropertyChange(PropertyChangeSupport* theWrappedObject, PropertyChangeEvent*  event);
   void firePropertyChange(PropertyChangeSupport* theWrappedObject, QString  propertyName, QVariant  oldValue, QVariant  newValue) const;
   void py_q_firePropertyChange(PropertyChangeSupport* theWrappedObject, QString  propertyName, QVariant  oldValue, QVariant  newValue) const{  (((PythonQtPublicPromoter_PropertyChangeSupport*)theWrappedObject)->py_q_firePropertyChange(propertyName, oldValue, newValue));}
   QVector<PropertyChangeListener* >  getPropertyChangeListeners(PropertyChangeSupport* theWrappedObject) const;
   QVector<PropertyChangeListener* >  py_q_getPropertyChangeListeners(PropertyChangeSupport* theWrappedObject) const{  return (((PythonQtPublicPromoter_PropertyChangeSupport*)theWrappedObject)->py_q_getPropertyChangeListeners());}
   QVector<PropertyChangeListener* >  getPropertyChangeListeners(PropertyChangeSupport* theWrappedObject, QString  propertyName);
   QVector<PropertyChangeListener* >  py_q_getPropertyChangeListeners(PropertyChangeSupport* theWrappedObject, QString  propertyName){  return (((PythonQtPublicPromoter_PropertyChangeSupport*)theWrappedObject)->py_q_getPropertyChangeListeners(propertyName));}
   void removePropertyChangeListener(PropertyChangeSupport* theWrappedObject, PropertyChangeListener*  listener);
   void py_q_removePropertyChangeListener(PropertyChangeSupport* theWrappedObject, PropertyChangeListener*  listener){  (((PythonQtPublicPromoter_PropertyChangeSupport*)theWrappedObject)->py_q_removePropertyChangeListener(listener));}
   void removePropertyChangeListener(PropertyChangeSupport* theWrappedObject, QString  propertyName, PropertyChangeListener*  listener);
   void py_q_removePropertyChangeListener(PropertyChangeSupport* theWrappedObject, QString  propertyName, PropertyChangeListener*  listener){  (((PythonQtPublicPromoter_PropertyChangeSupport*)theWrappedObject)->py_q_removePropertyChangeListener(propertyName, listener));}
};


