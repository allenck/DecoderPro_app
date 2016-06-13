#include "paneleditor.h"
#include "ui_paneleditor.h"
#include "positionablejcomponent.h"
#include "positionablepopuputil.h"
#include "analogclock2display.h"
#include "lighticon.h"
#include "sensoricon.h"
#include <QDebug>
#include "abstractsensor.h"
#include "locoicon.h"
#include "memoryicon.h"
#include "light.h"
#include "abstractlight.h"
#include "xmladapter.h"
#include "panelmenu.h"
#include "addpaneleditordialog.h"
#include "inputdialog.h"
#include "turnouticon.h"
//#include "lcdclockframe.h"
//#include "nixieclockframe.h"
#include "signalheadicon.h"
#include "signalmasticon.h"
#include "multisensoricon.h"
#include <QGraphicsSceneDragDropEvent>
#include "iconadder.h"
#include "jtextfield.h"
#include "reportericon.h"
#include "slipturnouticon.h"
#include "helputil.h"
#include "newpanelaction.h"
#include "storexmluseraction.h"
#include "imageindexeditor.h"
#include "warranttableaction.h"

PanelEditor::PanelEditor(QWidget *parent) :
    Editor("NoName", false, true, parent),
    ui(new Ui::PanelEditor)
{
 ui->setupUi(this);
 init("NoName");
 setTitle();
}

PanelEditor::~PanelEditor()
{
    delete ui;
}
/**
 * Provides a simple editor for adding jmri.jmrit.display items
 * to a captive JFrame.
 * <P>GUI is structured as a band of common parameters across the
 * top, then a series of things you can add.
 * <P>
 * All created objects are put specific levels depending on their
 * type (higher levels are in front):
 * <UL>
 * <LI>BKG background
 * <LI>ICONS icons and other drawing symbols
 * <LI>LABELS text labels
 * <LI>TURNOUTS turnouts and other variable track items
 * <LI>SENSORS sensors and other independently modified objects
 * </UL>
 * <P>
 * The "contents" List keeps track of all the objects added to the target
 * frame for later manipulation.
 * <P>
 * If you close the Editor window, the target is left alone and
 * the editor window is just hidden, not disposed.
 * If you close the target, the editor and target are removed,
 * and dispose is run. To make this logic work, the PanelEditor
 * is descended from a JFrame, not a JPanel.  That way it
 * can control its own visibility.
 * <P>
 * The title of the target and the editor panel are kept
 * consistent via the {#setTitle} method.
 *
 * @author  Bob Jacobsen  Copyright: Copyright (c) 2002, 2003, 2007
 * @author  Dennis Miller 2004
 * @author  Howard G. Penny Copyright: Copyright (c) 2005
 * @author  Matthew Harris Copyright: Copyright (c) 2009
 * @author  Pete Cressman Copyright: Copyright (c) 2009, 2010
 *
 */

///*public*/ class PanelEditor extends Editor implements ItemListener {



#if 0
    JCheckBox editableBox = new JCheckBox(Bundle.getMessage("CheckBoxEditable"));
    JCheckBox positionableBox = new JCheckBox(Bundle.getMessage("CheckBoxPositionable"));
    JCheckBox controllingBox = new JCheckBox(Bundle.getMessage("CheckBoxControlling"));
    //JCheckBox showCoordinatesBox = new JCheckBox(Bundle.getMessage("CheckBoxShowCoordinates"));
    JCheckBox showTooltipBox = new JCheckBox(Bundle.getMessage("CheckBoxShowTooltips"));
    JCheckBox hiddenBox = new JCheckBox(Bundle.getMessage("CheckBoxHidden"));
    JCheckBox menuBox = new JCheckBox(Bundle.getMessage("CheckBoxMenuBar"));
    JLabel scrollableLabel = new JLabel(Bundle.getMessage("ComboBoxScrollable"));
    JComboBox scrollableComboBox = new JComboBox();

    JButton labelAdd = new JButton(Bundle.getMessage("ButtonAddText"));
    JTextField nextLabel = new JTextField(10);

    JComboBox _addIconBox;
#endif
//    /*public*/ PanelEditor() {}

/*public*/ PanelEditor::PanelEditor(QString name, QWidget *parent) :
        Editor(name, false, true, parent),
        ui(new Ui::PanelEditor)
{
 //super(name, false, true);
 ui->setupUi(this);

 init(name);
 setTitle();
}

/*protected*/ void PanelEditor::init(QString /*name*/)
{
 log = new Logger("PanelEditor");
 log->setDebugEnabled(false);
 _debug = log->isDebugEnabled();
 _multiItemCopyGroup = NULL;  // items gathered inside fence
 pasteItemFlag = false;
 _delete = false;
 _showCoordinates = true;
 _currentSelection = NULL;
 delayedPopupTrigger = false;
 addItemViaMouseClick = false;
 _lastX = _lastY = 0;
 bDirty = false;
 ui->menuFile->addAction(new NewPanelAction(tr("New Panel..."),this));
 ui->menuFile->addAction(new StoreXmlUserAction(tr("Save Panels..."),this));
 QAction* storeIndexItem = new QAction(tr("Store Image Index"), this);
 ui->menuFile->addAction(storeIndexItem);
#if 1 // TODO:
// storeIndexItem.addActionListener(new ActionListener() {
//     @Override
//     public void actionPerformed(ActionEvent event) {
//         jmri.jmrit.catalog.ImageIndexEditor.storeImageIndex();
//     }
// });
 connect(storeIndexItem, SIGNAL(triggered()), this, SLOT(on_storeIndexItem_triggered()));
 QAction* editItem = new QAction(tr("Create/Edit Image Index"),this);
// editItem.addActionListener(new ActionListener() {
//     PanelEditor panelEd;

//     @Override
//     public void actionPerformed(ActionEvent e) {
//         ImageIndexEditor ii = ImageIndexEditor.instance(panelEd);
//         ii.pack();
//         ii.setVisible(true);
//     }

//     ActionListener init(PanelEditor pe) {
//         panelEd = pe;
//         return this;
//     }
// }.init(this));
 EditItemActionListener* editItemActionListener = new EditItemActionListener();
 editItemActionListener->init(this);
 connect(editItem, SIGNAL(triggered()), editItemActionListener, SLOT(actionPerformed()));

 ui->menuFile->addAction(editItem);

 editItem = new QAction(tr("Change view to Control Panel Editor"), this);
 ui->menuFile->addAction(editItem);
// editItem.addActionListener(new ActionListener() {
//     @Override
//     public void actionPerformed(ActionEvent event) {
//                              while ( QWidget* w = findChild<QWidget*>() )
//                                  delete w;("jmri.jmrit.display.controlPanelEditor.ControlPanelEditor");
//     }
// });
 connect(editItem, SIGNAL(triggered()), this, SLOT(on_CPEView_triggered()));
#endif
 ui->menuFile->addSeparator();
 QAction* deleteItem = new QAction(tr("Delete This Panel..."), this);
 ui->menuFile->addAction(deleteItem);
// deleteItem.addActionListener(new ActionListener() {
//     @Override
//     public void actionPerformed(ActionEvent event) {
//         if (deletePanel()) {
//             dispose(true);
//         }
//     }
// });
 connect(deleteItem, SIGNAL(triggered()), this, SLOT(on_actionDelete_this_panel_triggered()));
 PanelMenu* pMenu = PanelMenu::instance();
 ui->menuWindow->addMenu(pMenu);
 connect(ui->menuWindow, SIGNAL(aboutToShow()), this, SLOT(on_menuWindow_aboutToShow()));
// dlg = NULL;
// addRHTurnoutDlg = NULL;
// addLHTurnoutDlg = NULL;
// addSlipTODlg = NULL;
// addSensorDlg = NULL;
// addLightDlg = NULL;
// addRPSReporterDlg = NULL;
// addReporterDlg = NULL;
// addMemoryDlg = NULL;
// addIconDlg = NULL;
 addTextLabelDlg = NULL;
// addSignalHeadDlg=NULL;
// addSignalMastDlg = NULL;
// addMultiSensorDlg = NULL;
// addBackgroundDlg = NULL;
 nextX = new JTextField(tr("Default X"),4);
 nextY = new JTextField(tr("Default Y"),4);
 menuBar()->addMenu(WarrantTableAction::makeWarrantMenu(isEditable(),this));
 menuBar()->addMenu(HelpUtil::instance()->makeHelpMenu("package.jmri.jmrit.display.PanelEditor", true, this));

 //connect(ui->actionOpenEditor, SIGNAL(triggered()), this, SLOT(on_actionOpenEditor_triggered()));


    editPanel = new QGraphicsView(ui->centralwidget);
    ui->verticalLayout->removeWidget(ui->editPanel);
    ui->verticalLayout->addWidget(editPanel);
    editPanel->setMouseTracking(true);
    editPanel->setRenderHint(QPainter::Antialiasing);

    panelWidth = 600;
    panelHeight =400;
    editScene = new EditScene(QRectF(0, 0, panelWidth, panelHeight), this);
    _targetPanel = editScene;


    editPanel->setScene(editScene);
    connect(editScene, SIGNAL(sceneMouseMove(QGraphicsSceneMouseEvent*)), this, SLOT(mouseMoved(QGraphicsSceneMouseEvent*)));
    connect(editScene, SIGNAL(sceneMousePress(QGraphicsSceneMouseEvent*)), this, SLOT(mousePressed(QGraphicsSceneMouseEvent*)));
    connect(editScene, SIGNAL(sceneMouseRelease(QGraphicsSceneMouseEvent*)), this, SLOT(mouseReleased(QGraphicsSceneMouseEvent*)));
    connect(editScene, SIGNAL(sceneMouseRelease(QGraphicsSceneMouseEvent*)), this, SLOT(mouseClicked(QGraphicsSceneMouseEvent*)));
    connect(editScene, SIGNAL(sceneMouseMove(QGraphicsSceneMouseEvent*)), this, SLOT(mouseDragged(QGraphicsSceneMouseEvent*)));
    connect(editScene, SIGNAL(sceneDropEvent(QGraphicsSceneDragDropEvent*)), this, SLOT(sceneDropEvent(QGraphicsSceneDragDropEvent*)));

    if (_debug) log->debug("PanelEditor ctor done.");
}  // end ctor

void PanelEditor::on_storeIndexItem_triggered()
{
 ImageIndexEditor::storeImageIndex();
}

void PanelEditor::on_CPEView_triggered()
{
changeView("ControlPanelEditor");
}

#if 0
/**
* Initializes the hiddencheckbox and its listener.
* This has been taken out of the init, as checkbox is
* enable/disabled by the editableBox.
*/
private void hiddenCheckBoxListener(){
    setShowHidden(hiddenBox.isSelected());
    if (editableBox.isSelected()){
        hiddenBox.setEnabled(false);
        hiddenBox.setSelected(true);
    } else {
        hiddenBox.setEnabled(true);
        hiddenBox.addActionListener(new ActionListener() {
            /*public*/ void actionPerformed(ActionEvent event) {
                setShowHidden(hiddenBox.isSelected());
            }
        });
    }

}

/**
 * After construction, initialize all the widgets to their saved config settings.
 */
/*public*/ void initView() {
    editableBox.setSelected(isEditable());
    positionableBox.setSelected(allPositionable());
    controllingBox.setSelected(allControlling());
    //showCoordinatesBox.setSelected(showCoordinates());
    showTooltipBox.setSelected(showTooltip());
    hiddenBox.setSelected(showHidden());
    menuBox.setSelected(getTargetFrame().getJMenuBar().isVisible());
}

static class ComboBoxItem {
    QString name;
    ComboBoxItem(QString n) {
        name = n;
    }
    QString getName() {
        return name;
    }
    /*public*/ QString toQString() {
        return Bundle.getMessage(name);
    }
}

int locationX = 0;
int locationY = 0;
static final int DELTA = 20;

/*
*  itemListener for JComboBox
*/
/*public*/ void itemStateChanged(ItemEvent e) {
    if (e.getStateChange() == ItemEvent.SELECTED) {
        ComboBoxItem item = (ComboBoxItem)e.getItem();
        QString name = item.getName();
        JFrameItem frame = super.getIconFrame(name);
        if (frame != NULL) {
            frame.getEditor().reset();
            frame.setVisible(true);
        } else {
            if (name.equals("FastClock")) {
                addClock();
            } else if (name.equals("RPSreporter")) {
                addRpsReporter();
            } else {
                log->error("Unable to open Icon Editor \""+item.getName()+"\"");
            }
        }
        _addIconBox.setSelectedIndex(-1);
    }
}

/**
 * Handle close of editor window.
 * <P>
 * Overload/override method in JmriJFrame parent,
 * which by default is permanently closing the window.
 * Here, we just want to make it invisible, so we
 * don't dispose it (yet).
 **/
/*public*/ void windowClosing(java.awt.event.WindowEvent e) {
    setVisible(false);
}

/**
 * Create sequence of panels, etc, for layout:
 * JFrame contains its ContentPane
 *    which contains a JPanel with BoxLayout (p1)
 *       which contains a JScollPane (js)
 *            which contains the targetPane
 *
 */
/*public*/ JmriJFrame makeFrame(QString name) {
    JmriJFrame targetFrame = new JmriJFrame(name);
    targetFrame.setVisible(false);

    JMenuBar menuBar = new JMenuBar();
    JMenu editMenu = new JMenu(Bundle.getMessage("MenuEdit"));
    menuBar.add(editMenu);
    editMenu.add(new AbstractAction(Bundle.getMessage("OpenEditor")) {
            /*public*/ void actionPerformed(ActionEvent e) {
                setVisible(true);
            }
        });
    editMenu.addSeparator();
    editMenu.add(new AbstractAction(Bundle.getMessage("DeletePanel")){
            /*public*/ void actionPerformed(ActionEvent e) {
                if (deletePanel()) {
                    dispose(true);
                }
            }
        });
    targetFrame.setJMenuBar(menuBar);
    // add maker menu
    JMenu markerMenu = new JMenu(Bundle.getMessage("MenuMarker"));
    menuBar.add(markerMenu);
    markerMenu.add(new AbstractAction(Bundle.getMessage("AddLoco")){
        /*public*/ void actionPerformed(ActionEvent e) {
            locoMarkerFromInput();
        }
    });
    markerMenu.add(new AbstractAction(Bundle.getMessage("AddLocoRoster")){
        /*public*/ void actionPerformed(ActionEvent e) {
            locoMarkerFromRoster();
        }
    });
    markerMenu.add(new AbstractAction(Bundle.getMessage("RemoveMarkers")){
        /*public*/ void actionPerformed(ActionEvent e) {
            removeMarkers();
        }
    });

    JMenu warrantMenu = jmri.jmrit.logix.WarrantTableAction.makeWarrantMenu();
    if (warrantMenu!=NULL) {
        menuBar.add(warrantMenu);
    }

    targetFrame.addHelpMenu("package.jmri.jmrit.display.PanelTarget", true);
    return targetFrame;

}

/*************** implementation of Abstract Editor methods ***********/
/**
 * The target window has been requested to close, don't delete it at this
 *   time.  Deletion must be accomplished via the Delete this panel menu item.
 */
protected void targetWindowClosingEvent(java.awt.event.WindowEvent e) {
    targetWindowClosing(true);
}
/**
 * Called from TargetPanel's paint method for additional drawing by editor view
 */
protected void paintTargetPanel(Graphics g) {
    /*Graphics2D g2 = (Graphics2D)g;
    drawPositionableLabelBorder(g2);*/
}
#endif
/**
 * Set an object's location when it is created.
 */
///*protected*/ void PanelEditor::setNextLocation(Positionable* obj)
//{
//    int x = Integer.parseInt(nextX.getText());
//    int y = Integer.parseInt(nextY.getText());
//    ((PositionableLabel*)obj)->setLocation(x,y);
//}

/**
*  Create popup for a Positionable object
* Popup items common to all positionable objects are done before
* and after the items that pertain only to specific Positionable
* types.
*/

/*protected*/ void PanelEditor::showPopUp(Positionable* pc, QGraphicsSceneMouseEvent* /*event*/)
{
 PositionableLabel* p = NULL;
 //PositionableJComponent* pj = NULL;
 if(qobject_cast<PositionableLabel*>(pc)!= NULL)
 {
  p = (PositionableLabel*)pc;
  if (!p->isVisible())
  {
   return;     // component must be showing on the screen to determine its location
  }
 }
 else
// if(qobject_cast<PositionableJComponent*>(pc)!= NULL)
// {
//  pj = (PositionableJComponent*)pc;
//  if (!pj->isVisible())
//  {
//   return;     // component must be showing on the screen to determine its location
//  }
// }
// else
  return;

 QMenu* popup = new QMenu();
 PositionablePopupUtil* util;
 if(p != NULL) util = p->getPopupUtility();
// else if(pj != NULL) util = pj->getPopupUtility();
 if (p != NULL && p->isEditable())
 {
  // items for all Positionables
  if (p->doViemMenu())
  {
   if(qobject_cast<SensorIcon*>(pc)!= NULL)
    popup->addAction(new QAction(((SensorIcon*)p)->getNameString(),this));
   else
   if(qobject_cast<LightIcon*>(pc)!= NULL)
    popup->addAction(new QAction(((LightIcon*)p)->getNameString(),this));
   else
   if(qobject_cast<TurnoutIcon*>(pc)!= NULL)
    popup->addAction(new QAction(((TurnoutIcon*)p)->getNameString(),this));
   else
   if(qobject_cast<ReporterIcon*>(pc)!= NULL)
    popup->addAction(new QAction(((ReporterIcon*)p)->getNameString(),this));
   else
   if(qobject_cast<AnalogClock2Display*>(pc)!= NULL)
    popup->addAction(new QAction(((AnalogClock2Display*)p)->getNameString(),this));
   else
   if(qobject_cast<SignalHeadIcon*>(pc)!= NULL)
    popup->addAction(new QAction(((SignalHeadIcon*)p)->getNameString(),this));
   else
   if(qobject_cast<SignalMastIcon*>(pc)!= NULL)
    popup->addAction(new QAction(((SignalMastIcon*)p)->getNameString(),this));
   else
   if(qobject_cast<MultiSensorIcon*>(pc)!= NULL)
    popup->addAction(new QAction(((MultiSensorIcon*)p)->getNameString(),this));
   else
   if(qobject_cast<SlipTurnoutIcon*>(pc)!= NULL)
    popup->addAction(new QAction(((SlipTurnoutIcon*)p)->getNameString(),this));
   else
   if(qobject_cast<PositionableLabel*>(pc)!= NULL)
    popup->addAction(new QAction(((PositionableLabel*)p)->getNameString(),this));
// TODO: add more types
   else
    popup->addAction(new QAction(p->getNameString(),this));
   setPositionableMenu((Positionable*)p, popup);
   if (p->isPositionable())
   {
    setShowCoordinatesMenu((Positionable*)p, popup);
    setShowAlignmentMenu((Positionable*)p, popup);
   }
   setDisplayLevelMenu((Positionable*)p, popup);
   setHiddenMenu((Positionable*)p, popup);
   popup->addSeparator();
  }
  // Positionable items with defaults or using overrides
  bool popupSet =false;
  if(p != NULL)
  {
   popupSet = p->setRotateOrthogonalMenu(popup);
   popupSet = p->setRotateMenu(popup);
   popupSet = p->setScaleMenu(popup);
  }
//  else
//  if(pj != NULL)
//  {
//   popupSet = pj->setRotateOrthogonalMenu(popup);
//   popupSet = pj->setRotateMenu(popup);
//   popupSet = pj->setScaleMenu(popup);
//  }
  if (popupSet)
  {
   popup->addSeparator();
   popupSet = false;
  }
  if(p != NULL)
   popupSet = p->setEditIconMenu(popup);
//  else
//  if(pj != NULL)
//   popupSet = pj->setEditIconMenu(popup);
  if (popupSet)
  {
   popup->addSeparator();
   popupSet = false;
  }
  if(p != NULL)
   popupSet = p->setTextEditMenu(popup);
//  else
//   popupSet = pj->setTextEditMenu(popup);
  if (util!=NULL)
  {
   if(((PositionableLabel*)p)->isText())
   {
    util->setFixedTextMenu(popup);
    util->setTextMarginMenu(popup);
    util->setTextBorderMenu(popup);
    util->setTextFontMenu(popup);
    util->setBackgroundMenu(popup);
    util->setTextJustificationMenu(popup);
    util->setTextOrientationMenu(popup);
   }
   util->copyItem(popup);
   popup->addSeparator();
   util->propertyUtil(popup);
   util->setAdditionalEditPopUpMenu(popup);
   popupSet = true;
  }
  if (popupSet)
  {
   popup->addSeparator();
   popupSet = false;
  }
  p->setDisableControlMenu(popup);

  // for Positionables with unique item settings
  p->showPopUp(popup);

  setRemoveMenu((Positionable*)p, popup);
 }
// else if(pj != NULL)
// {
//  ((AnalogClock2Display*)pj)->setScaleMenu(popup);
// }
 else
 {
  //p->showPopUp(popup);

  if (util!=NULL)
  {
   util->setAdditionalViewPopUpMenu(popup);
  }
 }
 //popup->show((Component)p, p.getWidth()/2, p.getHeight()/2);
 popup->exec(QCursor::pos());

}

/******************************************************/


/*public*/ void PanelEditor::mousePressed(QGraphicsSceneMouseEvent* event)
{
 bool bRightButton = ((event->buttons())&Qt::RightButton)==Qt::RightButton;
 bool bShift = ((event->modifiers())&Qt::ShiftModifier) == Qt::ShiftModifier;
 bool bMeta = ((event->modifiers())&Qt::MetaModifier) == Qt::MetaModifier;
 bool bAlt = ((event->modifiers())&Qt::AltModifier) == Qt::AltModifier;
 bool bCtrl = ((event->modifiers())&Qt::ControlModifier) == Qt::ControlModifier;

 //setToolTip(NULL); // ends tooltip if displayed
 if (_debug) log->debug("mousePressed at ("+QString("%1").arg(event->scenePos().x())+","+QString("%1").arg(event->scenePos().y())+") _dragging="+(_dragging?"true":"false") + " right button="+(bRightButton?"Down":"up"));
 _lastX = _anchorX;
 _lastY = _anchorY;
 QList <Positionable*> selections = getSelectedItems(event);
 if (_dragging)
 {
  return;
 }
 if (selections.size() > 0)
 {
  if (bShift && selections.size() > 1)
  {
   _currentSelection = selections.at(1);
  }
  else
  {
   _currentSelection = selections.at(0);
  }
  if (bRightButton) //isPopupTrigger()
  {
   if (_debug) log->debug("mousePressed calls showPopUp");
   if (!(bMeta || bAlt ))
   {
    // if requesting a popup and it might conflict with moving, delay the request to mouseReleased
    delayedPopupTrigger = true;
    _dragging = true;
   }
   else
   {
    // no possible conflict with moving, display the popup now
    if (_selectionGroup!=QList<Positionable*>())
    {
     //Will show the copy option only
     showMultiSelectPopUp(event, _currentSelection);
    }
    else
    {
     showPopUp(_currentSelection, event);
    }
   }
  }
  else if (!bCtrl)
  {
   //_currentSelection->doMousePressed(event);
   if(qobject_cast<AnalogClock2Display*>(_currentSelection)!=NULL)
    ((AnalogClock2Display*)_currentSelection)->doMousePressed(event);
   else
   if(qobject_cast<SensorIcon*>(_currentSelection)!=NULL)
    ((SensorIcon*)_currentSelection)->doMousePressed(event);
   else
   if(qobject_cast<LightIcon*>(_currentSelection)!=NULL)
    ((LightIcon*)_currentSelection)->doMousePressed(event);
   else
   if(qobject_cast<SignalHeadIcon*>(_currentSelection)!=NULL)
    ((SignalHeadIcon*)_currentSelection)->doMousePressed(event);
   else
   if(qobject_cast<SignalMastIcon*>(_currentSelection)!=NULL)
    ((SignalMastIcon*)_currentSelection)->doMousePressed(event);
   else
   if(qobject_cast<MultiSensorIcon*>(_currentSelection)!=NULL)
    ((MultiSensorIcon*)_currentSelection)->doMousePressed(event);
   else
    ((PositionableLabel*)_currentSelection)->doMousePressed(event);if (_multiItemCopyGroup!=NULL && !_multiItemCopyGroup->contains(_currentSelection))
    _multiItemCopyGroup = NULL;
//                    _selectionGroup = NULL;
  }
 }
 else
 { // Not on a selection!
  if (bRightButton)
  {
   if (event->modifiers()&Qt::MetaModifier || event->modifiers()&Qt::AltModifier)
   {
    // if requesting a popup and it might conflict with moving, delay the request to mouseReleased
    delayedPopupTrigger = true;
   }
   else
   {
    if (_multiItemCopyGroup!=NULL)
    {
     pasteItemPopUp(event);
    }
    else if (_selectionGroup!=QList<Positionable*>())
    {
     showMultiSelectPopUp(event, _currentSelection);
    }
    else
    {
     backgroundPopUp(event);
     _currentSelection = NULL;
    }
   }
  }
  else
  {
   _currentSelection = NULL;
  }
 }
 //if ((event.isControlDown() || _selectionGroup!=NULL) && _currentSelection!=NULL){
 if (bCtrl || bMeta || bAlt)
 {
 //Don't want to do anything, just want to catch it, so that the next two else ifs are not
 //executed
 }
 else if ((_currentSelection==NULL && _multiItemCopyGroup==NULL) ||
                (!_selectRect.isNull() && !_selectRect.contains(_anchorX, _anchorY)))
 {
  _selectRect =  QRect(_anchorX, _anchorY, 0, 0);
  _selectionGroup = QList<Positionable*>();
 }
 else
 {
  _selectRect = QRect();
  _selectionGroup = QList<Positionable*>();
 }
 //_targetPanel->repaint(); // needed for ToolTip
}

/*public*/ void PanelEditor::mouseReleased(QGraphicsSceneMouseEvent* event)
{
 bool bRightButton = ((event->buttons())&Qt::RightButton)==Qt::RightButton;
 Q_UNUSED(bRightButton);
 bool bShift = ((event->modifiers())&Qt::ShiftModifier) == Qt::ShiftModifier;
 bool bMeta = ((event->modifiers())&Qt::MetaModifier) == Qt::MetaModifier;
 Q_UNUSED(bMeta);
 bool bAlt = ((event->modifiers())&Qt::AltModifier) == Qt::AltModifier;
 Q_UNUSED(bAlt);
 bool bCtrl = ((event->modifiers())&Qt::ControlModifier) == Qt::ControlModifier;
 saveEvent = event;

 //setToolTip("NULL"); // ends tooltip if displayed
 if (_debug) log->debug("mouseReleased at ("+QString("%1").arg(event->scenePos().x())+","+QString("%1").arg(event->scenePos().y())+") dragging= "+(_dragging?"true":"false")
                          +" selectRect is "+(_selectRect.isNull()? "NULL":"not NULL"));
 QList <Positionable*> selections = getSelectedItems(event);

// if (_dragging)
// {
//  //mouseDragged(event);
//  delayedPopupTrigger = false;
//  _dragging = false;
//  _selectRect = QRect();
// }
 if (selections.size() > 0)
 {
  if (bShift && selections.size() > 1)
  {
   _currentSelection = selections.at(1);
  }
  else
  {
    _currentSelection = selections.at(0);
  }
  if (_multiItemCopyGroup!=NULL && !_multiItemCopyGroup->contains(_currentSelection))
   _multiItemCopyGroup = NULL;
 }

 else
 {
  if ((event->buttons()&Qt::RightButton || delayedPopupTrigger) && !_dragging)
  {
   if (_multiItemCopyGroup!=NULL)
   {
    pasteItemPopUp(event);
   }
   else
   {
    backgroundPopUp(event);
    _currentSelection = NULL;
   }
  }
  else
  {
   _currentSelection = NULL;
  }
 }
 /*if (event.isControlDown() && _currentSelection!=NULL && !event.isPopupTrigger()){
        amendSelectionGroup(_currentSelection, event);*/
 if (( delayedPopupTrigger) && _currentSelection != NULL /*&& !_dragging*/)
 {
  _dragging = false;
  if (_selectionGroup!=QList<Positionable*>())
  {
   //Will show the copy option only
    showMultiSelectPopUp(event, _currentSelection);
   }
  else
  {
   showPopUp(_currentSelection, event);
  }
 }
 else
 {
  if (_currentSelection != NULL && !_dragging && !bCtrl)
  {
   if(qobject_cast<SensorIcon*>(_currentSelection)!=NULL)
    ((SensorIcon*)_currentSelection)->doMouseReleased(event);
   else
   if(qobject_cast<PositionableJComponent*>(_currentSelection)!=NULL)
    ((PositionableJComponent*)_currentSelection)->doMouseReleased(event);
   else
   ((PositionableLabel*)_currentSelection)->doMouseReleased(event);
   addToTarget(_currentSelection);
  }
  _currentSelection = NULL; // Added to prevent calls to updateScene ACK 10-13-15
  if (allPositionable() && !_selectRect.isNull())
  {
   if (_selectionGroup==QList<Positionable*>() && _dragging)
   {
    makeSelectionGroup(event);
   }
  }
 }
 delayedPopupTrigger = false;
 _dragging = false;
 _selectRect = QRect();


 // if not sending MouseClicked, do it here
 // if (jmri.util.swing.SwingSettings.getNonStandardMouseEvent())
 //        mouseClicked(event);
 //_targetPanel.repaint(); // needed for ToolTip
 paint(_targetPanel);

}

/*public*/ void PanelEditor::mouseDragged(QGraphicsSceneMouseEvent* event)
{
 bool bRightButton = ((event->buttons())&Qt::RightButton)==Qt::RightButton;
 bool bShift = ((event->modifiers())&Qt::ShiftModifier) == Qt::ShiftModifier;
 Q_UNUSED(bShift);
 bool bMeta = ((event->modifiers())&Qt::MetaModifier) == Qt::MetaModifier;
 Q_UNUSED(bMeta);
 bool bAlt = ((event->modifiers())&Qt::AltModifier) == Qt::AltModifier;
 Q_UNUSED(bAlt);
 bool bCtrl = ((event->modifiers())&Qt::ControlModifier) == Qt::ControlModifier;
 Q_UNUSED(bCtrl);

 //setToolTip(NULL); // ends tooltip if displayed
 if (bRightButton /*|| (!bMeta && !bAlt)*/ )
 {
  if (_currentSelection!=NULL)
  {
   QList <Positionable*> selections = getSelectedItems(event);
   if (selections.size() > 0)
   {
    if (selections.at(0)!=_currentSelection)
    {
     ((PositionableLabel*)_currentSelection)->doMouseReleased(event);
    }
   }
   else
   {
    ((PositionableLabel*)_currentSelection)->doMouseReleased(event);
   }
  }
  //return;
 }

//moveIt:
 if (_currentSelection!=NULL && getFlag(OPTION_POSITION, ((PositionableLabel*)_currentSelection)->isPositionable()))
 {
  int deltaX = event->scenePos().x() - _lastX;
  int deltaY = event->scenePos().y() - _lastY;
  int minX = getItemX(_currentSelection, deltaX);
  int minY = getItemY(_currentSelection, deltaY);
  if (_selectionGroup!=QList<Positionable*>() && _selectionGroup.contains(_currentSelection))
  {
   for (int i=0; i<_selectionGroup.size(); i++)
   {
    minX = qMin(getItemX(_selectionGroup.at(i), deltaX), minX);
    minY = qMin(getItemY(_selectionGroup.at(i), deltaY), minY);
   }
  }
  if (minX<0 || minY<0 || !bRightButton)
  {
    //break moveIt;
    goto moveIt2;
  }
  if (_selectionGroup!=QList<Positionable*>() && _selectionGroup.contains(_currentSelection))
  {
   for (int i=0; i<_selectionGroup.size(); i++)
   {
     moveItem(_selectionGroup.at(i), deltaX, deltaY);
   }
   _highlightcomponent = QRectF();
  }
  else
  {
   moveItem(_currentSelection, deltaX, deltaY);
   if(qobject_cast<LightIcon*>(_currentSelection)!=NULL)
   {
    _highlightcomponent =  QRectF(((LightIcon*)_currentSelection)->getX(),((LightIcon*) _currentSelection)->getY(),((LightIcon*)_currentSelection)->maxWidth(), ((LightIcon*)_currentSelection)->maxHeight());

   }
   else
   if(qobject_cast<PositionableLabel*>(_currentSelection)!=NULL)
   {
    //_highlightcomponent =  QRect(((PositionableLabel*)_currentSelection)->getX(),((PositionableLabel*) _currentSelection)->getY(),((PositionableLabel*)_currentSelection)->maxWidth(), ((PositionableLabel*)_currentSelection)->maxHeight());
    _highlightcomponent = ((PositionableLabel*) _currentSelection)->getBounds();

   }
//   else
//   _highlightcomponent =  QRect(_currentSelection->getX(), _currentSelection->getY(),
//                                                 _currentSelection->maxWidth(), _currentSelection->maxHeight());
  }
 }
 else
 {
  if (allPositionable() && _selectionGroup==QList<Positionable*>() && bRightButton)
  {
   drawSelectRect(event->scenePos().x(), event->scenePos().y());
   paint(_targetPanel);
   return;
  }
 }
 moveIt2:
 if(bRightButton)
  _dragging = true;
 delayedPopupTrigger = false;
 _lastX = event->scenePos().x();
 _lastY = event->scenePos().y();
 //_targetPanel.repaint(); // needed for ToolTip
 //paint(_targetPanel);
 if(_currentSelection != NULL)
 {
  ((PositionableLabel*) _currentSelection)->updateScene();
 }
}

/*public*/ void PanelEditor::mouseMoved(QGraphicsSceneMouseEvent* event)
{
 bool bRightButton = ((event->buttons())&Qt::RightButton)==Qt::RightButton;
 bool bShift = ((event->modifiers())&Qt::ShiftModifier) == Qt::ShiftModifier;
 bool bMeta = ((event->modifiers())&Qt::MetaModifier) == Qt::MetaModifier;
 Q_UNUSED(bMeta);
 bool bAlt = ((event->modifiers())&Qt::AltModifier) == Qt::AltModifier;
 Q_UNUSED(bAlt);
 bool bCtrl = ((event->modifiers())&Qt::ControlModifier) == Qt::ControlModifier;
 Q_UNUSED(bCtrl);

 //if (_debug) log->debug("mouseMoved at ("+QString("%1").arg(event->scenePos().x())+","+QString("%1").arg(event->scenePos().y())+")");
 ui->statusbar->showMessage(tr("mouseMoved at (%1,%2)").arg(event->scenePos().x()).arg(event->scenePos().y()));
 if (_dragging || bRightButton) { return; }

 QList <Positionable*> selections = getSelectedItems(event);
 Positionable* selection = NULL;
 if (selections.size() > 0)
 {
  if (bShift && selections.size() > 1)
  {
    selection = selections.at(1);
  }
  else
  {
   selection = selections.at(0);
  }
 }
 if (isEditable() && selection!=NULL && ((PositionableLabel*)selection)->getDisplayLevel()>BKG)
 {
  //_highlightcomponent = QRectF(((PositionableLabel*)selection)->getX(), ((PositionableLabel*)selection)->getY(), ((PositionableLabel*)selection)->maxWidth(), ((PositionableLabel*)selection)->maxHeight());
  _highlightcomponent = ((PositionableLabel*)selection)->getBounds();
  //_targetPanel->repaint();
  paint(_targetPanel);
 }
 else
 {
  _highlightcomponent = QRectF();
  //_targetPanel->repaint();
  paint(_targetPanel);
 }
// if (selection!=NULL && ((PositionableLabel*)selection)->getDisplayLevel()>BKG && ((PositionableLabel*)selection)->showTooltip())
// {
////   showToolTip(selection, event);
//  //selection->highlightlabel(true);
//  //_targetPanel->repaint();
//  drawLabelImages(editScene);
//  paint(_targetPanel);
// }
// else
// {
//  //setToolTip(NULL);
//  _highlightcomponent = QRectF();
//  //_targetPanel->repaint();
//  paint(_targetPanel);
// }
}

/*public*/ void PanelEditor::mouseClicked(QGraphicsSceneMouseEvent* event)
{
 bool bRightButton = ((event->buttons())&Qt::RightButton)==Qt::RightButton;
 bool bShift = ((event->modifiers())&Qt::ShiftModifier) == Qt::ShiftModifier;
 bool bMeta = ((event->modifiers())&Qt::MetaModifier) == Qt::MetaModifier;
 Q_UNUSED(bMeta);
 bool bAlt = ((event->modifiers())&Qt::AltModifier) == Qt::AltModifier;
 Q_UNUSED(bAlt);
 bool bCtrl = ((event->modifiers())&Qt::ControlModifier) == Qt::ControlModifier;
 //setToolTip(NULL); // ends tooltip if displayed
 if (_debug) log->debug("mouseClicked at ("+QString("%1").arg(event->scenePos().x())+","+QString("%1").arg(event->scenePos().y())+") dragging= "+(_dragging?"true":"false") +" selectRect is "+(_selectRect.isNull()? "NULL":"not NULL"));
 QList <Positionable*> selections = getSelectedItems(event);

 if (selections.size() > 0)
 {
  if (bShift && selections.size() > 1)
  {
    _currentSelection = selections.at(1);
  }
  else
  {
   _currentSelection = selections.at(0);
  }
 }
 else
 {
  _currentSelection = NULL;
  if (bRightButton)
  {
   if (_multiItemCopyGroup==NULL)
   {
    pasteItemPopUp(event);
   }
   else
    backgroundPopUp(event);
  }
 }
 if (bRightButton && _currentSelection != NULL && !_dragging)
 {
  if (_selectionGroup!=QList<Positionable*>())
   showMultiSelectPopUp(event, _currentSelection);
  else
   showPopUp(_currentSelection, event);
  //_selectionGroup = NULL; //Show popup only works for a single item

 }
 else
 {
  if (_currentSelection != NULL && !_dragging && !bCtrl)
  {
   if(qobject_cast<AnalogClock2Display*>(_currentSelection)!=NULL)
    ((AnalogClock2Display*)_currentSelection)->doMouseClicked(event);
   else
   if(qobject_cast<LightIcon*>(_currentSelection)!=NULL)
    ((LightIcon*)_currentSelection)->doMouseClicked(event);
   else
   if(qobject_cast<SensorIcon*>(_currentSelection)!=NULL)
    ((SensorIcon*)_currentSelection)->doMouseClicked(event);
   else
   ((PositionableLabel*)_currentSelection)->doMouseClicked(event);
  }
 }
 //_targetPanel.repaint(); // needed for ToolTip
 if (bCtrl && _currentSelection!=NULL && !event->buttons()&Qt::RightButton)
 {
  amendSelectionGroup(_currentSelection);
 }
}
#if 0
/*public*/ void mouseEntered(MouseEvent event) {
}

/*public*/ void mouseExited(MouseEvent event) {
    setToolTip(NULL);
    _targetPanel.repaint();  // needed for ToolTip
}

#endif
/*protected*/ void PanelEditor::copyItem(Positionable* p)
{
 _multiItemCopyGroup = new QVector <Positionable*>();
 _multiItemCopyGroup->append(p);
}

/*protected*/ void PanelEditor::pasteItemPopUp(/*final*/ QGraphicsSceneMouseEvent* event)
{
 if (!isEditable())
  return;
 if (_multiItemCopyGroup==NULL)
        return;
 QMenu* popup = new QMenu();
 QAction* pasteAction = new QAction(tr("Paste"), this);
//    edit.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) { pasteItem(event); }
//    });
 connect(pasteAction, SIGNAL(triggered()), this, SLOT(pasteItem()));
 setBackgroundMenu(popup);
 showAddItemPopUp(event, popup);
 popup->addAction(pasteAction);
 //popup.show(event.getComponent(), event.getX(), event.getY());
 popup->exec(QCursor::pos());
}

/*protected*/ void PanelEditor::backgroundPopUp(QGraphicsSceneMouseEvent* event)
{
 if (!isEditable())
  return;
 QMenu* popup = new QMenu();
 setBackgroundMenu(popup);
 showAddItemPopUp(event, popup);
    //popup.show(event.getComponent(), event.getX(), event.getY());
 popup->exec(QCursor::pos());
}

/*protected*/ void PanelEditor::showMultiSelectPopUp(/*final*/ QGraphicsSceneMouseEvent* event, Positionable* p)
{
 QMenu* popup = new QMenu();
 QAction* copy = new QAction("Copy",this); // changed "edit" to "copy"
 if (((PositionableLabel*)p)->isPositionable())
 {
  setShowAlignmentMenu(p, popup);
 }
//    copy.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            _multiItemCopyGroup = new ArrayList <Positionable>();
//            // must make a copy or pasteItem() will hang
//            if (_selectionGroup!=NULL) {
//                for (int i=0; i<_selectionGroup.size(); i++) {
//                    _multiItemCopyGroup.add(_selectionGroup.get(i));
//                }
//            }
//        }
//    });

//    setMultiItemsPositionableMenu(popup); // adding Lock Position for all
                                          // selected items

    setRemoveMenu(p, popup);
    showAddItemPopUp(event, popup); // no need to Add when group selected
    popup->addAction(copy);
    connect(copy, SIGNAL(triggered()), this, SLOT(on_copyAction_triggered()));
    //popup.show(event.getComponent(), event.getX(), event.getY());
    popup->exec(QCursor::pos());
}
/*protected*/ void PanelEditor::showAddItemPopUp(/*final*/ QGraphicsSceneMouseEvent* /*event*/, QMenu* popup)
{
 if(!isEditable())
        return;
 QMenu* _add = new QMenu("Add Item"/*Bundle.getMessage("FontBackgroundColor")*/);
//    addItemPopUp(new ComboBoxItem("Right Hand Turnout"),_add);
 QAction* addRHTurnout = new QAction(tr("RightTurnout"), this);
 connect(addRHTurnout, SIGNAL(triggered()), this, SLOT(on_addRHTurnout_triggered()));
 _add->addAction(addRHTurnout);

 //    addItemPopUp(new ComboBoxItem("LeftTurnout"),_add);
 QAction* addLHTurnout = new QAction(tr("Left Hand Turnout"), this);
 connect(addLHTurnout, SIGNAL(triggered()), this, SLOT(on_addLHTurnout_triggered()));
 _add->addAction(addLHTurnout);

 //    addItemPopUp(new ComboBoxItem("SlipTOEditor"),_add);
 QAction* addSlipTurnout = new QAction(tr("Slip/3-way turnout/Scissor"), this);
 connect(addSlipTurnout, SIGNAL(triggered()), this, SLOT(on_addSlipTurnout_triggered()));
 _add->addAction(addSlipTurnout);

 //    addItemPopUp(new ComboBoxItem("Sensor"),_add);
 QAction* addSensorAct = new QAction(tr("Sensor"),this);
 _add->addAction(addSensorAct);
 connect(addSensorAct, SIGNAL(triggered()), this, SLOT(on_addSensor_triggered()));

 //    addItemPopUp(new ComboBoxItem("Signal Head"),_add);
 QAction* addSignalHeadAct = new QAction(tr("Signal head"),this);
 connect(addSignalHeadAct, SIGNAL(triggered()), this, SLOT(on_addSignalHead_triggered()));
 _add->addAction(addSignalHeadAct);

 //    addItemPopUp(new ComboBoxItem("Signal Mast"),_add);
 QAction* addSignalMastAct = new QAction(tr("Signal mast"),this);
 connect(addSignalMastAct, SIGNAL(triggered()), this, SLOT(on_addSignalMast_triggered()));
 _add->addAction(addSignalMastAct);

 //    addItemPopUp(new ComboBoxItem("Memory"),_add);
 QAction* addMemoryAct = new QAction(tr("Memory"),this);
 _add->addAction(addMemoryAct);
 connect(addMemoryAct, SIGNAL(triggered()), this, SLOT(on_addMemory_triggered()));

 //    addItemPopUp(new ComboBoxItem("Reporter"),_add);
 QAction* addReporterAct = new QAction(tr("Reporter"),this);
 _add->addAction(addReporterAct);
 connect(addReporterAct, SIGNAL(triggered()), this, SLOT(on_addReporter_triggered()));

 //    addItemPopUp(new ComboBoxItem("Light"),_add);
 QAction* addLightAct = new QAction(tr("Light"),this);
 _add->addAction(addLightAct);
 connect(addLightAct, SIGNAL(triggered()), this, SLOT(on_addLight_triggered()));

 //    addItemPopUp(new ComboBoxItem("Background"),_add);
 QAction* addBackgroundAct = new QAction(tr("Background"),this);
 _add->addAction(addBackgroundAct);
 connect(addBackgroundAct, SIGNAL(triggered()), this, SLOT(on_addBackground_triggered()));

 //    addItemPopUp(new ComboBoxItem("MultiSensor"),_add);
 QAction* addMultiSensorAct = new QAction(tr("MultiSensor"),this);
 _add->addAction(addMultiSensorAct);
 connect(addMultiSensorAct, SIGNAL(triggered()), this, SLOT(on_addMultiSensor_triggered()));


 //    addItemPopUp(new ComboBoxItem("RPSreporter"),_add);
 QAction* addRPSReporterAct = new QAction(tr("RPSReporter"),this);
 _add->addAction(addRPSReporterAct);
 connect(addRPSReporterAct, SIGNAL(triggered()), this, SLOT(on_addRPSReporter_triggered()));
//    addItemPopUp(new ComboBoxItem("FastClock"),_add);
 QAction* addClockAct = new QAction(tr("Fast clock"),this);
 connect(addClockAct, SIGNAL(triggered()), this, SLOT(on_addClock_triggered()));
 _add->addAction(addClockAct);

// QAction* addLcdClockAct = new QAction(tr("Lcd clock"),this);
// connect(addLcdClockAct, SIGNAL(triggered()), this, SLOT(on_addLcdClock_triggered()));
// _add->addAction(addLcdClockAct);//    addItemPopUp(new ComboBoxItem("Icon"),_add);

// QAction* addNixieClockAct = new QAction(tr("Nixie clock"),this);
// connect(addNixieClockAct, SIGNAL(triggered()), this, SLOT(on_addNixieClockAct_triggered()));
// _add->addAction(addNixieClockAct);//    addItemPopUp(new ComboBoxItem("Icon"),_add);

 QAction* addIconAct = new QAction(tr("Icon"),this);
 connect(addIconAct, SIGNAL(triggered()), this, SLOT(on_addIcon_triggered()));
 _add->addAction(addIconAct);

 //    addItemPopUp(new ComboBoxItem("Text"),_add);
 QAction* addTextLabelAct = new QAction(tr("Text/Label"),this);
 connect(addTextLabelAct, SIGNAL(triggered()), this, SLOT(on_addTextLabel_triggered()));
 _add->addAction(addTextLabelAct);
 popup->addMenu(_add);
}
#if 0

protected void addItemPopUp(final ComboBoxItem item, JMenu menu){

    ActionListener a = new ActionListener() {
        //final QString desiredName = name;
        /*public*/ void actionPerformed(ActionEvent e) {
        addItemViaMouseClick = true;
        getIconFrame(item.getName());
        }
//            ComboBoxItem selected;
        ActionListener init (ComboBoxItem i) {
//                selected = i;
            return this;
        }
    }.init(item);
    JMenuItem addto = new JMenuItem(item.toQString());
    addto.addActionListener(a);
    menu.add(addto);
}

#endif
/*public*/ void PanelEditor::putItem(Positionable* l)
{
 Editor::putItem(l);
 /*This allows us to catch any new items that are being pasted into the panel
   and add them to the selection group, so that the user can instantly move them around*/
 //!!!
 if (pasteItemFlag)
 {
  amendSelectionGroup(l);
  return;
 }
 if (addItemViaMouseClick)
 {
  addItemViaMouseClick = false;
  ((PositionableLabel*)l)->setLocation(_lastX, _lastY);
 }
}

/*private*/ void PanelEditor::amendSelectionGroup(Positionable* p)
{
 if (p==NULL) return;
 if (_selectionGroup==QList<Positionable*>())
 {
   _selectionGroup = QList <Positionable*>();
 }
 bool removed = false;
 for(int i=0; i<_selectionGroup.size();i++)
 {
  if (_selectionGroup.at(i)==p)
  {
   _selectionGroup.removeAt(i);
   removed = true;
   break;
  }
 }
 if(!removed)
  _selectionGroup.append(p);
 else if (removed && _selectionGroup.isEmpty())
  _selectionGroup=QList<Positionable*>();
//_targetPanel.repaint();
}


/*protected*/ void PanelEditor::pasteItem(/*MouseEvent e*/)
{
 //QGraphicsSceneMouseEvent* e = saveEvent;
 pasteItemFlag = true;
 //XmlAdapter* adapter;
 QString className;
// int x;
// int y;
// int xOrig;
// int yOrig;
 if (_multiItemCopyGroup!=NULL)
 {
#if 0 // TODO:
        JComponent copied;
        int xoffset;
        int yoffset;
        x = _multiItemCopyGroup.get(0).getX();
        y = _multiItemCopyGroup.get(0).getY();
        xoffset=e.getX()-x;
        yoffset=e.getY()-y;
        /*We make a copy of the selected items and work off of that copy
        as amendments are made to the multiItemCopyGroup during this process
        which can result in a loop*/
        ArrayList <Positionable> _copyOfMultiItemCopyGroup = new ArrayList<Positionable>(_multiItemCopyGroup);
        Collections.copy(_copyOfMultiItemCopyGroup, _multiItemCopyGroup);
        for(int i = 0; i<_copyOfMultiItemCopyGroup.size(); i++){
            copied = (JComponent)_copyOfMultiItemCopyGroup.get(i);
            xOrig = copied.getX();
            yOrig = copied.getY();
            x = xOrig+xoffset;
            y = yOrig+yoffset;
            if (x<0) x=1;
            if (y<0) y=1;
            className=ConfigXmlManager.adapterName(copied);
            copied.setLocation(x, y);
            try{
                adapter = (XmlAdapter)Class.forName(className).newInstance();
                Element el = adapter.store(copied);
                adapter.load(el, this);
            } catch (Exception ex) {
                log->debug(ex);
            }
            /*We remove the original item from the list, so we end up with
            just the new items selected and allow the items to be moved around */
            amendSelectionGroup(_copyOfMultiItemCopyGroup.get(i));
            copied.setLocation(xOrig, yOrig);
#endif
  }
  _selectionGroup=QList<Positionable*>();
 pasteItemFlag = false;
 //_targetPanel->repaint();
}
#if 0
/**
* Add an action to remove the Positionable item.
*/
/*public*/ void setRemoveMenu(Positionable p, JPopupMenu popup) {
    popup.add(new AbstractAction(Bundle.getMessage("Remove")) {
        Positionable comp;
        /*public*/ void actionPerformed(ActionEvent e) {
            if (_selectionGroup==NULL)
                comp.remove();
            else
                removeMultiItems();
        }
        AbstractAction init(Positionable pos) {
            comp = pos;
            return this;
        }
    }.init(p));
}

private void removeMultiItems(){
    boolean itemsInCopy = false;
    if (_selectionGroup==_multiItemCopyGroup){
        itemsInCopy=true;
    }
    for (int i=0; i<_selectionGroup.size(); i++) {
        Positionable comp = _selectionGroup.get(i);
        comp.remove();
    }
    //As we have removed all the items from the panel we can remove the group.
    _selectionGroup = NULL;
    //If the items in the selection group and copy group are the same we need to
    //clear the copy group as the originals no longer exist.
    if (itemsInCopy)
        _multiItemCopyGroup = NULL;
}

// This adds a single CheckBox in the PopupMenu to set or clear all the selected
// items "Lock Position" or Positionable setting, when clicked, all the items in
// the selection will be changed accordingly.
private void setMultiItemsPositionableMenu(JPopupMenu popup) {
    // This would do great with a "greyed" CheckBox if the multiple items have different states.
    // Then selecting the true or false state would force all to change to true or false

    JCheckBoxMenuItem lockItem = new JCheckBoxMenuItem(Bundle.getMessage("LockPosition"));
    boolean allSetToMove = false;  // used to decide the state of the checkbox shown
    int trues = 0;                 // used to see if all items have the same setting

    int size = _selectionGroup.size();

    for (int i = 0; i < size; i++) {
        Positionable comp = _selectionGroup.get(i);

        if (!comp.isPositionable()) {
            allSetToMove = true;
            trues++;
        }

        lockItem.setSelected( allSetToMove );

        lockItem.addActionListener(new ActionListener() {
            Positionable comp;
            JCheckBoxMenuItem checkBox;

            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
                comp.setPositionable(!checkBox.isSelected());
                setSelectionsPositionable(!checkBox.isSelected(), comp);
            }

            ActionListener init(Positionable pos, JCheckBoxMenuItem cb) {
                comp = pos;
                checkBox = cb;
                return this;
            }
        }.init(comp, lockItem));
    }

    // Add "~" to the Text when all items do not have the same setting,
    // until we get a "greyed" CheckBox ;) - GJM
    if ((trues != size) && (trues != 0)) {
        lockItem.setText("~ "+lockItem.getText());
        // uncheck box if all not the same
        lockItem.setSelected( false );
    }
    popup.add(lockItem);
}
#endif
/*public*/ void PanelEditor::setBackgroundMenu(QMenu* popup) {
    QMenu* edit = new QMenu(tr("Background color"));
    makeColorMenu(edit);
    popup->addMenu(edit);

}

/*protected*/ void PanelEditor::makeColorMenu(QMenu* colorMenu)
{
 QActionGroup* buttonGrp = new QActionGroup(this);
 addColorMenuEntry(colorMenu, buttonGrp, tr("Black"), QColor(Qt::black));
 addColorMenuEntry(colorMenu, buttonGrp, tr("DarkGray"),QColor(Qt::darkGray));
 addColorMenuEntry(colorMenu, buttonGrp, tr("Gray"),QColor(Qt::gray));
 addColorMenuEntry(colorMenu, buttonGrp, tr("LightGray"),QColor(Qt::lightGray));
 addColorMenuEntry(colorMenu, buttonGrp, tr("White"),QColor(Qt::white));
 addColorMenuEntry(colorMenu, buttonGrp, tr("Red"),QColor(Qt::red));
 addColorMenuEntry(colorMenu, buttonGrp, tr("Orange"),QColor(255,170,0));
 addColorMenuEntry(colorMenu, buttonGrp, tr("Yellow"),QColor(Qt::yellow));
 addColorMenuEntry(colorMenu, buttonGrp, tr("Green"),QColor(Qt::green));
 addColorMenuEntry(colorMenu, buttonGrp, tr("Blue"),QColor(Qt::blue));
 addColorMenuEntry(colorMenu, buttonGrp, tr("Magenta"),QColor(Qt::magenta));
 addColorMenuEntry(colorMenu, buttonGrp, tr("Clear"), QColor());
 connect(buttonGrp, SIGNAL(triggered(QAction*)), this, SLOT(on_backgroundColorSelection(QAction*)));
}
void PanelEditor::on_backgroundColorSelection(QAction* act)
{
 QColor color = act->data().value<QColor>();
 editPanel->setBackgroundBrush(QBrush(color, Qt::SolidPattern));
}

/*protected*/ void PanelEditor::addColorMenuEntry(QMenu* menu, QActionGroup* colorButtonGroup,
                       /*final*/ QString name, QColor color)
{
//    ActionListener a = new ActionListener() {
//        //final QString desiredName = name;
//        Color desiredColor;
//        /*public*/ void actionPerformed(ActionEvent e) {
//            if(desiredColor!=NULL)
//                setBackgroundColor(desiredColor);
//            else
//                clearBackgroundColor();
//        }
//        ActionListener init (Color c) {
//            desiredColor = c;
//            return this;
//        }
//    }.init(color);
//    JRadioButtonMenuItem r = new JRadioButtonMenuItem(name);
//    r.addActionListener(a);

//    if (color==NULL) { color = defaultBackgroundColor; }
//    setColorButton(getBackgroundColor(), color, r);
//    colorButtonGroup.add(r);
//    menu.add(r);
    QVariant var = color;
    QAction* act = new QAction( name, this);
    act->setCheckable(true);
    if( defaultBackgroundColor == color)
     act->setChecked(true);
    act->setData(var);
    colorButtonGroup->addAction(act);
    menu->addAction(act);

}
#if 0
/*protected*/ void PanelEditor::setColorButton(Color color, Color buttonColor, JRadioButtonMenuItem r) {
    if (_debug)
        log->debug("setColorButton: color="+color+" (RGB= "+(color==NULL?"":color.getRGB())+
                  ") buttonColor= "+buttonColor+" (RGB= "+(buttonColor==NULL?"":buttonColor.getRGB())+")");
    if (buttonColor!=NULL) {
        if (color!=NULL && buttonColor.getRGB() == color.getRGB()) {
             r.setSelected(true);
        } else r.setSelected(false);
    } else {
        if (color==NULL)  r.setSelected(true);
        else  r.setSelected(false);
    }
}

/******************************************************/
#endif
//// initialize logging
//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(PanelEditor.class.getName());
//}

void PanelEditor::drawLabelImages(EditScene* g2)
{
 QColor color;
 for (int i = 0; i<_contents->size();i++)
 {
  PositionableLabel* l = (PositionableLabel*)_contents->at(i);
  if(l->_itemGroup != NULL && l->_itemGroup->scene() != NULL)
  {
   Q_ASSERT(l->_itemGroup->scene()!=0);
   g2->removeItem(l->_itemGroup);
  }
  l->_itemGroup = new QGraphicsItemGroup();
  if(!l->isIcon())
  {
   color = defaultTextColor;

//   if(l->item != NULL)
//   {
//    g2->removeItem(l->item);
//    l->item = NULL;
//   }
   QGraphicsTextItem*  item = new QGraphicsTextItem(l->getUnRotatedText());
   item->setFont(l->getFont());
   item->setPos(l->getX(), l->getY());
   l->_itemGroup->addToGroup(item);
   g2->addItem(l->_itemGroup);
   if(l->getDegrees() != 0)
    //l->item->rotate(l->getDegrees());
    l->_itemGroup->setRotation(l->_itemGroup->rotation()+ l->getDegrees());
  }
  else
  {
   QString state = "BeanStateUnknown";
   QPixmap pixmap;
   if(qobject_cast<LightIcon*>(l)!=NULL)
   {
    if(((LightIcon*)l)->getIcon(((LightIcon*)l)->lightState())!=NULL)
    {
     Light* light = ((LightIcon*)l)->getLight();
     int iState = ((AbstractLight*)light)->getState();
     pixmap = QPixmap::fromImage(((LightIcon*)l)->getIcon(iState)->getImage());
//   QGraphicsPixmapItem* item = g2->addPixmap(pixmap);
     QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap,0);
    item->setPos(l->getX(), l->getY());
    if(pixmap.isNull())
        log->debug( "No pixmap "+ ((LightIcon*)l)->getIcon(iState)->getURL());

//   else
//    qDebug() << tr("pixmap h = %1, w = %2").arg(pixmap.height()).arg(pixmap.width());
     l->_itemGroup->addToGroup(item);
     g2->addItem(l->_itemGroup);
     if(l->getDegrees() != 0)
      //l->item->rotate(l->getDegrees());
      l->_itemGroup->setRotation(l->_itemGroup->rotation()+ l->getDegrees());
    }
   }
   else
   if(qobject_cast<SensorIcon*>(l) != NULL)
   {
    int iState = 0;
    if(((SensorIcon*)l)->getSensor() != NULL)
     iState=((AbstractSensor*)((SensorIcon*)l)->getSensor())->getKnownState();
//    if(l->item != NULL)
//    {
//     g2->removeItem(l->item);
//     l->item = NULL;
//    }
//    if(((SensorIcon*)l)->_state2nameMap->contains(istate))
//     state = ((SensorIcon*)l)->_state2nameMap->value(istate);
    pixmap = QPixmap::fromImage(((SensorIcon*)l)->getIcon(iState)->getImage());
    if(pixmap.isNull())
     log->debug(QString("null Sensor Icon pixmap: %1").arg(((SensorIcon*)l)->getIcon(iState)->getURL()));
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap);
    item->setPos(l->getX(), l->getY());
    l->_itemGroup->addToGroup(item);
    g2->addItem(l->_itemGroup);
   }
   else
   if(qobject_cast<LocoIcon*>(l) != NULL)
   {
    //pixmap = QPixmap::fromImage(QImage((((LocoIcon*)l)->getIcon()->getURL())));
//    if(l->item != NULL)
//    {
//     g2->removeItem(l->item);
//     l->item = NULL;
//    }
    if(l->isIcon())
    {
     pixmap = QPixmap::fromImage(((JLabel*)l)->getIcon()->getOriginalImage());
     if(pixmap.isNull())
      log->debug(QString("LocoIcon null pixmap: %1").arg(((JLabel*)l)->getIcon()->getURL()));
     QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap);
     item->setPos(l->getX(), l->getY());
     l->_itemGroup->addToGroup(item);
     //g2->addItem(l->item);
    }
    else
    {
     QGraphicsTextItem* item = new QGraphicsTextItem(l->getUnRotatedText());
     item->setPos(l->getX(), l->getY());
     l->_itemGroup->addToGroup(item);
    }
    g2->addItem(l->_itemGroup);
    if(l->getDegrees() != 0)
     //l->item->rotate(l->getDegrees());
     l->_itemGroup->setRotation(l->_itemGroup->rotation()+ l->getDegrees());

   }
   else
   if(qobject_cast<MemoryIcon*>(l) != NULL)
   {
    MemoryIcon* m = (MemoryIcon*)l;
//    if(m->item != NULL)
//    {
//     g2->removeItem(m->item);
//     m->item = NULL;
//    }
    if(m->isIcon())
    {
     pixmap = QPixmap::fromImage(((PositionableLabel*)l)->getIcon()->getImage());
     //QGraphicsPixmapItem* item = g2->addPixmap(pixmap);
             QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap, 0);
     item->setPos(l->getX(), l->getY());
     if(pixmap.isNull())
      log->debug( "No pixmap "+ ((PositionableLabel*)l)->getIcon()->getURL());
     m->_itemGroup->addToGroup(item);
    }
    else
    {

     //m->item = g2->addText("????");
     QGraphicsTextItem* item = new QGraphicsTextItem("????");
     m->_itemGroup->addToGroup(item);
     item->setPos(l->getX(), l->getY());
    }
    g2->addItem(m->_itemGroup);
    if(m->getDegrees() != 0)
     //m->item->rotate(l->getDegrees());
     m->_itemGroup->setRotation(m->_itemGroup->rotation()+ m->getDegrees());

   }
   else
   if(((PositionableIcon*)l)->getIcon(state)!=NULL)
   {
    pixmap = QPixmap::fromImage(((PositionableIcon*)l)->getIcon(state)->getImage());
//   QGraphicsPixmapItem* item = g2->addPixmap(pixmap);
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap,0);
   item->setPos(l->getX(), l->getY());
   if(pixmap.isNull())
    qDebug() << "No pixmap";
//   else
//    qDebug() << tr("pixmap h = %1, w = %2").arg(pixmap.height()).arg(pixmap.width());
    l->_itemGroup->addToGroup(item);
    g2->addItem(l->_itemGroup);
    if(l->getDegrees() != 0)
     //l->item->rotate(l->getDegrees());
     l->_itemGroup->setRotation(l->_itemGroup->rotation()+ l->getDegrees());

   }
  }
 }
}
void PanelEditor::on_actionAdd_loco_triggered()
{
 locoMarkerFromInput();
}
void PanelEditor::on_actionAdd_Loco_from_roster_triggered()
{
 locoMarkerFromRoster();
}
void PanelEditor::on_actionRemove_markers_triggered()
{
 removeMarkers();

}
void PanelEditor::on_addClock_triggered()
{
 addItemViaMouseClick = true;
 AnalogClock2Display* l = new AnalogClock2Display(this);
 l->setOpaque(false);
 l->update();
 l->setDisplayLevel(CLOCK);
//    setNextLocation(l);
 l->setLocation(_lastX, _lastY);
 l->setVisible(true);
 l->setScale(1.0);
 putItem((Positionable*)l);
 l->paint(editScene);
}
//void PanelEditor::on_addLcdClock_triggered()
//{
// addItemViaMouseClick = true;
// LcdClockFrame* l = new LcdClockFrame(this);
// l->setOpaque(false);
// l->update();
// l->setDisplayLevel(CLOCK);
////    setNextLocation(l);
// l->setLocation(_lastX, _lastY);
// l->setVisible(true);
// l->setScale(1.0);
// putItem((Positionable*)l);
// l->paint(editScene);
//}
//void PanelEditor::on_addNixieClockAct_triggered()
//{
// addItemViaMouseClick = true;
// NixieClockFrame* l = new NixieClockFrame(this);
// l->setOpaque(false);
// l->update();
// l->setDisplayLevel(CLOCK);
////    setNextLocation(l);
// l->setLocation(_lastX, _lastY);
// l->setVisible(true);
// l->setScale(1.0);
// putItem((Positionable*)l);
// l->paint(editScene);
//}
void PanelEditor::on_addSensor_triggered()
{
// QPointF pt = QPoint(_lastX, _lastY);
// if(addSensorDlg == NULL)
//  addSensorDlg = new AddPanelIconDialog("Sensor", pt, (Editor*)this);
// else
//  addSensorDlg->setSensorIcon(NULL);
// addSensorDlg->show();
 nextX->setText(QString::number(_lastX));
 nextY->setText(QString::number(_lastY));

 addSensorEditor();
}

void PanelEditor::on_addSignalHead_triggered()
{
// QPointF pt = QPoint(_lastX, _lastY);
// if(addSignalHeadDlg == NULL)
//  addSignalHeadDlg = new AddPanelIconDialog("SignalHead", pt, (Editor*)this);
// addSignalHeadDlg->show();
 addSignalHeadEditor();
}
void PanelEditor::on_addSignalMast_triggered()
{
// QPointF pt = QPoint(_lastX, _lastY);
// if(addSignalMastDlg == NULL)
//  addSignalMastDlg = new AddPanelIconDialog("SignalMast", pt, (Editor*)this);
// addSignalMastDlg->show();
 addSignalMastEditor();
}
//void PanelEditor::on_actionOpenEditor_triggered()
//{
// addItemViaMouseClick= true;
// if(dlg == NULL)
//  dlg = new AddPanelEditorDialog(this);
// dlg->show();
//}
void PanelEditor::on_addRHTurnout_triggered()
{
// QPointF pt = QPoint(_lastX, _lastY);
// if(addRHTurnoutDlg == NULL)
//  addRHTurnoutDlg = new AddPanelIconDialog("RHTurnout", pt, (Editor*)this);
// addRHTurnoutDlg->show();
 addRightTOEditor();
}
void PanelEditor::on_addLHTurnout_triggered()
{
// QPointF pt = QPoint(_lastX, _lastY);
// if(addLHTurnoutDlg == NULL)
//  addLHTurnoutDlg = new AddPanelIconDialog("LHTurnout", pt, (Editor*)this);
// addLHTurnoutDlg->show();
 addLeftTOEditor();
}
void PanelEditor::on_addSlipTurnout_triggered()
{
// QPointF pt = QPoint(_lastX, _lastY);
// if(addSlipTODlg == NULL)
//  addSlipTODlg = new AddPanelIconDialog("SlipTO", pt, (Editor*)this);
// addSlipTODlg->show();
 addSlipTOEditor();
}
void PanelEditor::on_addLight_triggered()
{
// QPointF pt = QPoint(_lastX, _lastY);
// if(addLightDlg == NULL)
//  addLightDlg = new AddPanelIconDialog("Light", pt, (Editor*)this);
// addLightDlg->show();
 addLightEditor();
}
void PanelEditor::on_addRPSReporter_triggered()
{
// QPointF pt = QPoint(_lastX, _lastY);
// if(addRPSReporterDlg == NULL)
//  addRPSReporterDlg = new AddPanelIconDialog("RPSReporter", pt, (Editor*)this);
// addRPSReporterDlg->show();
}

void PanelEditor::on_addReporter_triggered()
{
// QPointF pt = QPoint(_lastX, _lastY);
// pasteItemFlag = true;
// if(addReporterDlg == NULL)
//  addReporterDlg = new AddPanelIconDialog("Reporter", pt, (Editor*)this);
// addReporterDlg->show();
 addReporterEditor();
}
void PanelEditor::on_addMemory_triggered()
{
// QPointF pt = QPoint(_lastX, _lastY);
// if(addMemoryDlg == NULL)
//  addMemoryDlg = new AddPanelIconDialog("Memory", pt, (Editor*)this);
// addMemoryDlg->show();
 addMemoryEditor();
}
void PanelEditor::on_addIcon_triggered()
{
// QPointF pt = QPoint(_lastX, _lastY);
// if(addIconDlg == NULL)
//  addIconDlg = new AddPanelIconDialog("Icon", pt, (Editor*)this);
// addIconDlg->show();
 addIconEditor();
}
void PanelEditor::on_addTextLabel_triggered()
{
 QPointF pt = QPoint(_lastX, _lastY);
 if(addTextLabelDlg == NULL)
  addTextLabelDlg = new InputDialog("Enter text, then press OK","",NULL,this);
 if(addTextLabelDlg->exec() == QDialog::Accepted)
 {
  PositionableLabel* label = new PositionableLabel(addTextLabelDlg->value(),this);
  label->setLocation(pt.x(), pt.y());
  putItem((Positionable*)label);
 }
 addTextLabelDlg=NULL;
}
void PanelEditor::on_addMultiSensor_triggered()
{
// QPointF pt = QPoint(_lastX, _lastY);
// if(addMultiSensorDlg == NULL)
//  addMultiSensorDlg = new AddPanelIconDialog("MultiSensor", pt, (Editor*)this);
// addMultiSensorDlg->show();
 addMultiSensorEditor();
}
void PanelEditor::on_addBackground_triggered()
{
// QPointF pt = QPoint(_lastX, _lastY);
// if(addBackgroundDlg == NULL)
//     addBackgroundDlg = new AddPanelIconDialog("Background", pt, (Editor*)this);
//    addBackgroundDlg->show();
  addBackgroundEditor();
}

void PanelEditor::setLocation(int x, int y)
{
 _lastX = x;
 _lastY = y;
}
void PanelEditor::on_actionDelete_this_panel_triggered()
{
 if (deletePanel())
 {
  dispose(true);
 }
}
void PanelEditor::on_menuWindow_aboutToShow()
{
 ui->menuWindow->clear();
 PanelMenu::instance()->updatePanelMenu(ui->menuWindow);
}
void PanelEditor::closeEvent(QCloseEvent *)
{
// if(dlg != NULL)
//  dlg->close();
// if(addSensorDlg != NULL)
//  addSensorDlg->close();
// if(addRHTurnoutDlg!=NULL)
//  addRHTurnoutDlg->close();
// if(addLHTurnoutDlg!=NULL)
//  addLHTurnoutDlg->close();
// if(addSlipTODlg != NULL)
//  addSlipTODlg->close();
// if(addLightDlg != NULL)
//  addLightDlg->close();
// if(addRPSReporterDlg)
//  addRPSReporterDlg->close();
// if(addReporterDlg != NULL)
//  addReporterDlg->close();
// if(addMemoryDlg != NULL)
//  addMemoryDlg->close();
// if(addIconDlg != NULL)
//   addIconDlg->close();
 if(addTextLabelDlg != NULL)
  addTextLabelDlg->close();
}
void PanelEditor::repaint() {}
void PanelEditor::sceneDropEvent(QGraphicsSceneDragDropEvent *e)
{
 QString path = e->mimeData()->text();
 qDebug() << "drop " + path;
}
/**************** add content items from Icon Editors ********************/
/**
 * Add a sensor indicator to the target
 */
/**
 * Set an object's location when it is created.
 */
/*protected*/ void PanelEditor::setNextLocation(Positionable* obj) {
    int x = nextX->text().toInt();
    int y = nextY->text().toInt();
    obj->setLocation(x,y);
}
void PanelEditor::on_actionOpenEditor_triggered()
{
 changeView("ControlPanelEditor");
}
