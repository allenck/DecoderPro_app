#include "controlpaneleditor.h"
#include "instancemanager.h"
#include <QMenuBar>
#include "configxmlmanager.h"
#include "itempalette.h"
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDrag>
#include <QMimeData>
#include "turnouticon.h"
#include "sensoricon.h"
#include "signalheadicon.h"
#include "lighticon.h"
#include "editscene.h"
#include "positionablepopuputil.h"
#include <QRectF>
#include "locoicon.h"
#include "lememoryicon.h"
#include "analogclock2display.h"
//#include "../Tables/libtables.h"
#include "indicatortrackicon.h"
#include "multiiconeditor.h"
#include "memoryinputicon.h"
#include "memorycomboicon.h"
#include "memoryspinnericon.h"
#include "circuitbuilder.h"
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include "oblockmanager.h"
#include <QClipboard>
#include <QApplication>
#include "storexmluseraction.h"
#include "positionablejcomponent.h"
#include "imageindexeditor.h"
#include "coordinateedit.h"
#include "shapedrawer.h"
#include "warranttableaction.h"
#include "dataflavor.h"
#include "reportericon.h"
#include <QGraphicsSceneDragDropEvent>
#include <QPointF>
#include "proxyreportermanager.h"
#include "helputil.h"
#include "indicatorturnouticon.h"
#include "indicatortrackicon.h"
#include "indicatorturnouticonxml.h"
#include "indicatortrackiconxml.h"
#include "turnouticon.h"
#include "turnouticonxml.h"
#include "sensoricon.h"
#include "sensoriconxml.h"
#include "lighticon.h"
#include "lighticonxml.h"
#include "signalheadicon.h"
#include "signalheadiconxml.h"
#include "signalmasticonxml.h"
#include "lememoryiconxml.h"
#include "memorycomboiconxml.h"
#include "memoryinputiconxml.h"
#include "memoryspinnericonxml.h"
#include "reportericonxml.h"
#include "multisensoriconxml.h"
#include "multisensoricon.h"
#include "helputil.h"
#include "helpbroker.h"
#include "portalicon.h"
#include "positionableshape.h"
#include "positionablepolygon.h"
#include "indicatortrack.h"
#include <QKeyEvent>
#include "listedtableaction.h"
#include "oblocktableaction.h"
#include <QGraphicsView>
#include "linkingobject.h"
#include "joptionpane.h"
#include <QSignalMapper>
#include "analogclock2displayxml.h"

ControlPanelEditor::ControlPanelEditor(QWidget *parent) :
    Editor(parent)
{
 init("NoName");

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
 * Note that higher numbers appear behind lower numbers.
 * <P>
 * The "contents" List keeps track of all the objects added to the target
 * frame for later manipulation.
 * Extends the behavior it shares with PanelPro
 * DnD implemented at JDK 1.2 for backward compatibility
 * <P>
 * @author  Pete Cressman Copyright: Copyright (c) 2009, 2010, 2011
 * @version $Revision: 21062 $
 *
 */

///*public*/ class ControlPanelEditor extends Editor implements DropTargetListener, ClipboardOwner, KeyListener {


//    /*public*/ ControlPanelEditor() {
//    }

/*public*/ /*static*/ /*final*/ QString ControlPanelEditor::POSITIONABLE_LIST_FLAVOR = QString("application/x-java-jvm-local-objectref") +
           ";class=jmri.jmrit.display.controlPanelEditor.ControlPanelEditor";

/*public*/ ControlPanelEditor::ControlPanelEditor(QString name, QWidget *parent) : Editor(name, parent)
{
 //super(name);
 init(name);
}
ControlPanelEditor::~ControlPanelEditor()
{
 delete log;
 delete _itemPalette;
}

/*protected*/ void ControlPanelEditor::init(QString /*name*/)
{
 log = new Logger("ControlPanelEditor");
 setObjectName("ControlPanelEditor");
 setProperty("JavaClassName", "jmri.jmrit.display.controlPanelEditor.ControlPanelEditor");

 initComponents();
 _debug = true;
 setAcceptDrops(true);
 _fitX = 0;
 _fitY = 0;
 _clickTime = 0;
 _warrantMenu = nullptr;
 _circuitMenu = nullptr;
 _editorMenu = nullptr;
 _drawMenu = nullptr;
 _markerMenu = nullptr;
 //libTables = nullptr;
 _portalIconMap = nullptr;

 useGlobalFlagBox = new QAction(tr("Override individual Position & Control settings "),this);
 useGlobalFlagBox->setCheckable(true);
 positionableBox = new QAction(tr("All panel items can be repositioned"),this);
 positionableBox->setCheckable(true);
 controllingBox = new QAction(tr("Panel items control layout"),this);
 controllingBox->setCheckable(true);
 hiddenBox = new QAction(tr("Show all hidden items"), this);
 hiddenBox->setCheckable(true);
 disableShapeSelect = new QAction(tr("Disable Selecting Shapes"), this);
 disableShapeSelect->setCheckable(true);
 scrollBoth = new QAction(tr("Both scrollbars"), this);
 scrollBoth->setCheckable(true);
 scrollNone = new QAction(tr("No scrollbars"), this);
 scrollNone->setCheckable(true);
 scrollHorizontal = new QAction(tr("Horizontal only"),this);
 scrollHorizontal->setCheckable(true);
 scrollVertical = new QAction(tr("Vertical only"), this);
 scrollVertical->setCheckable(true);
 showTooltipBox = new QAction(tr("Show tooltips for all items"),this);
 showTooltipBox->setCheckable(true);
 _regular = true;	// true when TO_ARROW shows entry into ToBlock
 _hide = false;	// true when arrow should NOT show entry into ToBlock
 _disablePortalSelection = true;		// only select PortalIcon in CircuitBuilder
 _secondSelectionGroup = nullptr;
 setVisible(false);
 _debug = log->isDebugEnabled();
//    java.awt.Container contentPane = this.getContentPane();
//    contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.Y_AXIS));
// QWidget* contentPane = getContentPane();
// contentPane->setObjectName("contentPane");
// contentPane->setLayout(new QVBoxLayout());
// //this->setCentralWidget(contentPane);

 // make menus
 setGlobalSetsLocalFlag(false);
 setUseGlobalFlag(false);
 _menuBar = new QMenuBar();
 _circuitBuilder = new CircuitBuilder(this);
 _shapeDrawer = new ShapeDrawer(this);
 makeDrawMenu();
 makeWarrantMenu(true, true);
 makeIconMenu();
 makeZoomMenu();
 makeMarkerMenu();
 makeOptionMenu();
 makeEditMenu();
 makeFileMenu();
 //_menuBar->addMenu(HelpUtil::instance()->makeHelpMenu("package.jmri.jmrit.display.ControlPanelEditor", true));

 setMenuBar(_menuBar);
 addHelpMenu("package.jmri.jmrit.display.ControlPanelEditor", true);

 Editor::setTargetPanel((EditScene*)nullptr, nullptr);
 Editor::setTargetPanelSize(300, 300);
// if(editScene == nullptr)
// {
//  editScene = new EditScene();
//  editPanel = new QGraphicsView(editScene);
// }
 editScene = (EditScene*)Editor::getTargetPanel();
 editScene->setObjectName("editScene");
 //_itemPalette = new ItemPalette(tr("Item Palette"), this);
 editPanel->setDragMode(QGraphicsView::NoDrag);
 editPanel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
 editPanel->setObjectName("editPanel");
 connect(editScene, SIGNAL(sceneDropEvent(QGraphicsSceneDragDropEvent*)), this, SLOT(dropEvent(QGraphicsSceneDragDropEvent*)));
 connect(editScene, SIGNAL(sceneMousePress(QGraphicsSceneMouseEvent*)), this, SLOT(mousePressed(QGraphicsSceneMouseEvent*)));
 connect(editScene, SIGNAL(sceneMouseRelease(QGraphicsSceneMouseEvent*)), this, SLOT(mouseReleased(QGraphicsSceneMouseEvent*)));
 connect(editScene, SIGNAL(sceneMouseMove(QGraphicsSceneMouseEvent*)), this, SLOT(mouseMoved(QGraphicsSceneMouseEvent*)));
 connect(editScene, SIGNAL(sceneMouseRelease(QGraphicsSceneMouseEvent*)), this, SLOT(mouseClicked(QGraphicsSceneMouseEvent*)));
 //connect(editScene, SIGNAL(sceneMouseDoubleClick(QGraphicsSceneMouseEvent*)), this, SLOT(mouseDoubleClicked(QGraphicsSceneMouseEvent*)));
// makeDataFlavors();
    // set scrollbar initial state
//    setScroll(SCROLL_BOTH);
//    scrollBoth.setSelected(true);
//    super.setDefaultToolTip(new ToolTip(NULL,0,0,new Font("Serif", Font.PLAIN, 12),
//                                        Color.black, new Color(255, 250, 210), Color.black));
 // register the resulting panel for later configuration
 ((ConfigureManager*)InstanceManager::getNullableDefault("ConfigureManager"))->registerUser(this);
 pack();
 setVisible(true);
//    addKeyListener(this);
}

/*protected*/ void ControlPanelEditor::makeIconMenu() {
 _iconMenu = new QMenu(tr("Add Items"));
 _menuBar->addMenu(_iconMenu/*, 0*/);
 QAction* mi = new QAction(tr("Item Palette"),this);
// mi.addActionListener(new ActionListener() {
//     Editor editor;

//     ActionListener init(Editor ed) {
//         editor = ed;
//         return this;
//     }
//     @Override
//     public void actionPerformed(ActionEvent e) {
 connect(mi, &QAction::triggered, [=]{
  if (_itemPalette==nullptr) {
      _itemPalette = new ItemPalette(tr("Item Pallette"), this);
  }
  _itemPalette->setVisible(true);
 });
//     }
// }.init(this));
//         mi.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_P, ActionEvent.CTRL_MASK));

 _iconMenu->addAction(mi);

 _iconMenu->addAction(new OBlockTableAction(tr("Occupancy Blocks"),this));
 mi = (QAction*) _iconMenu->actions().at(1);
 //        mi.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_B, ActionEvent.CTRL_MASK));

 mi = new QAction(tr("Circuit Builder"),this);
 //mi.addActionListener((ActionEvent event) -> {
 connect(mi, &QAction::triggered, [=]{
     _circuitBuilder->openCBWindow();
 });
 //        mi.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_T, ActionEvent.CTRL_MASK));

 _iconMenu->addAction(mi);

 _iconMenu->addAction(new ListedTableAction(tr("Item Tables"),this));
 mi = (QAction*) _iconMenu->actions().at(3);
// setMenuAcceleratorKey(mi, KeyEvent.VK_T);
}

/*protected*/ void ControlPanelEditor::makeCircuitMenu() {
    if (_circuitMenu==nullptr) {
        _circuitMenu = _circuitBuilder->makeMenu();
    }
    _menuBar->insertMenu(_menuBar->actions().at(0),_circuitMenu/*, 0*/);
}

/*protected*/ void ControlPanelEditor::makeCircuitMenu(bool edit)
{
 if (edit) {
  if (_circuitMenu == nullptr)
  {
      _circuitMenu = _circuitBuilder->makeMenu();
      //int idx = _menuBar->getComponentIndex(_warrantMenu);
      //_menuBar->insertMenu(_circuitMenu, _warrantMenu);
      _menuBar->addMenu(_circuitMenu);
     // _menuBar.revalidate();
  }
 } else if (_circuitMenu != nullptr) {
     _circuitBuilder->closeCBWindow();
     _circuitMenu = nullptr;
 }
}

/*protected*/ void ControlPanelEditor::makeDrawMenu()
{
 if (_drawMenu==nullptr)
 {
  _drawMenu = _shapeDrawer->makeMenu();
  _drawMenu->addAction(disableShapeSelect);
//    disableShapeSelect.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent event) {
  connect(disableShapeSelect, &QAction::triggered, [=]{
            _disableShapeSelection = disableShapeSelect->isChecked();
//        }
    });
 }
 if(_menuBar->actions().count() == 0)
  _menuBar->addMenu(_drawMenu);
 else
  _menuBar->insertMenu(_menuBar->actions().at(0), _drawMenu/*, 0*/);
}

/*public*/ bool ControlPanelEditor::getShapeSelect() {
    return !_disableShapeSelection;
}

/*public*/ void ControlPanelEditor::setShapeSelect(bool set) {
    _disableShapeSelection = !set;
    disableShapeSelect->setChecked(_disableShapeSelection);
}

/*public*/ ShapeDrawer* ControlPanelEditor::getShapeDrawer()
{
 return _shapeDrawer;
}
/*protected*/ void ControlPanelEditor::makeZoomMenu()
{
 _zoomMenu = new QMenu(tr("Zoom"));
 _menuBar->insertMenu(_menuBar->actions().at(0),_zoomMenu/*, 0*/);
 QAction* addItem = new QAction(tr("No Zoom"),this);
 _zoomMenu->addAction(addItem);
//    addItem.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                zoomRestore();
//            }
//        });
 connect(addItem, SIGNAL(triggered()), this, SLOT(zoomRestore()));
#if 1
 PositionableJComponent* z = new PositionableJComponent(this);
    z->setScale(getPaintScale());
    //addItem.addActionListener(CoordinateEdit::getZoomEditAction(z));
    _zoomMenu->addAction(CoordinateEdit::getZoomEditAction(z,this));

#endif
 addItem = new QAction(tr("Zoom To Fit"),this);
 _zoomMenu->addAction(addItem);
// addItem.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                zoomToFit();
//            }
//        });
 connect(addItem, SIGNAL(triggered()), this, SLOT(zoomToFit()));
}

/*protected*/ void ControlPanelEditor::makeWarrantMenu(bool edit, bool addMenu)
{
 QMenu* oldMenu = _warrantMenu;
 _warrantMenu = WarrantTableAction::getDefault()->makeWarrantMenu(edit);
 if (_warrantMenu == nullptr) {
     _warrantMenu = new QMenu(tr("Warrant"));
#if 1 // TODO:
     QSignalMapper* sm = new QSignalMapper(this);
     QAction* aboutItem = new QAction(tr("About Warrants"),this);
     sm->setMapping(aboutItem,aboutItem);
     HelpUtil::getGlobalHelpBroker()->enableHelpOnButton(aboutItem, "package.jmri.jmrit.logix.Warrant", nullptr);
     _warrantMenu->addAction(aboutItem);
     aboutItem = new QAction(tr("About OBlocks & Portals"),this);
     sm->setMapping(aboutItem,aboutItem);
     HelpUtil::getGlobalHelpBroker()->enableHelpOnButton(aboutItem, "package.jmri.jmrit.logix.OBlockTable", nullptr);
     _warrantMenu->addAction(aboutItem);
     aboutItem = new QAction(tr("About Circuit Builder"),this);
     sm->setMapping(aboutItem,aboutItem);
     HelpUtil::getGlobalHelpBroker()->enableHelpOnButton(aboutItem, "package.jmri.jmrit.display.CircuitBuilder", nullptr);
     _warrantMenu->addAction(aboutItem);
     //aboutItem.addActionListener((ActionEvent event) -> {
     connect(aboutItem, &QAction::triggered, [=]{
         makeCircuitMenu(true);
//                openCircuitWindow();
     });
#endif
 } else {
     makeCircuitMenu(edit);
 }
 if (edit) {
     QAction* item = new QAction(tr("Open Circuit Builder"));
     _warrantMenu->addAction(item);
     //item.addActionListener((ActionEvent event) -> {
     connect(item, &QAction::triggered, [=]{
         _circuitBuilder->openCBWindow();
     });
 }
#if 1 // TODO:
 if (addMenu) {
     _menuBar->addMenu(_warrantMenu/*, 0*/);
 } else if (oldMenu != nullptr) {
     int idx = _menuBar->actions().indexOf((QAction*)oldMenu);
     _menuBar->removeAction((QAction*)oldMenu);
     _menuBar->addMenu(_warrantMenu/*, idx*/);

 }
 //_menuBar->revalidate();
#endif
}

/*protected*/ void ControlPanelEditor::makeMarkerMenu() {
    _markerMenu = new QMenu(tr("Marker"));
    _menuBar->addMenu(_markerMenu);
    QAction* act = new QAction(tr("Add Loco"),this);
//    _markerMenu.add(new AbstractAction(tr("AddLoco")){
//        /*public*/ void actionPerformed(ActionEvent e) {
    connect(act, &QAction::triggered, [=]{
            locoMarkerFromInput();
//        }
    });
    _markerMenu->addAction(act);
    Editor* editor = (Editor*)this;
    act = new QAction(tr("Add Loco from roster"),this);
//    _markerMenu.add(new AbstractAction(tr("AddLocoRoster")){
//        /*public*/ void actionPerformed(ActionEvent e) {
    connect(act, &QAction::triggered, [=]{
            locoMarkerFromRoster();
//        }
    });
    _markerMenu->addAction(act);
//    _markerMenu.add(new AbstractAction(tr("RemoveMarkers")){
//        /*public*/ void actionPerformed(ActionEvent e) {
//            removeMarkers();
//        }
//    });
    act = new QAction(tr("Remove markers"),this);
    _markerMenu->addAction(act);
    connect(act, SIGNAL(triggered()), editor, SLOT(removeMarkers()));
}

/*protected*/ void ControlPanelEditor::makeOptionMenu()
{
 _optionMenu = new QMenu(tr("Option"));
 _menuBar->insertMenu(_menuBar->actions().at(0), _optionMenu/*, 0*/);
 // use globals item
 _optionMenu->addAction(useGlobalFlagBox);
//    useGlobalFlagBox.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                setUseGlobalFlag(useGlobalFlagBox.isSelected());
//            }
//        });
 connect(useGlobalFlagBox, SIGNAL(toggled(bool)), this, SLOT(setUseGlobalFlag(bool)));
 useGlobalFlagBox->setChecked(useGlobalFlag());
 // positionable item
 _optionMenu->addAction(positionableBox);
//    positionableBox.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                setAllPositionable(positionableBox.isSelected());
//            }
//        });
 connect(positionableBox, SIGNAL(toggled(bool)), this, SLOT(setAllPositionable(bool)));
 positionableBox->setChecked(allPositionable());
 // controlable item
 _optionMenu->addAction(controllingBox);
//    controllingBox.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                setAllControlling(controllingBox.isSelected());
//            }
//        });
 connect(controllingBox, SIGNAL(toggled(bool)), this, SLOT(setAllControlling(bool)));
 controllingBox->setChecked(allControlling());
 // hidden item
 _optionMenu->addAction(hiddenBox);
//    hiddenBox.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                setShowHidden(hiddenBox.isSelected());
//            }
//        });
 connect(hiddenBox, SIGNAL(toggled(bool)), this, SLOT(setShowHidden(bool)));
 hiddenBox->setChecked(showHidden());

 _optionMenu->addAction(showTooltipBox);
//    showTooltipBox.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            setAllShowTooltip(showTooltipBox.isSelected());
//        }
//    });
 connect(showTooltipBox, SIGNAL(toggled(bool)), this, SLOT(setAllShowToolTip(bool)));
 showTooltipBox->setChecked(showToolTip());
// QGraphicsView already has scrollbars
 // Show/Hide Scroll Bars
 QMenu* scrollMenu = new QMenu(tr("Panel scrollbars"));
 _optionMenu->addMenu(scrollMenu);
 QActionGroup* scrollGroup = new QActionGroup(this);
 scrollGroup->addAction(scrollBoth);
 scrollMenu->addAction(scrollBoth);
// scrollBoth.addActionListener(new ActionListener() {
//         /*public*/ void actionPerformed(ActionEvent event) {
 connect(scrollBoth, &QAction::triggered, [=]{
  editPanel->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
  editPanel->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
 });
 scrollGroup->addAction(scrollNone);
 scrollMenu->addAction(scrollNone);
// scrollNone.addActionListener(new ActionListener() {
//         /*public*/ void actionPerformed(ActionEvent event) {
 connect(scrollNone, &QAction::triggered, [=]{
  editPanel->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
  editPanel->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
 });
 scrollGroup->addAction(scrollHorizontal);
 scrollMenu->addAction(scrollHorizontal);
// scrollHorizontal.addActionListener(new ActionListener() {
//         /*public*/ void actionPerformed(ActionEvent event) {
 connect(scrollHorizontal, &QAction::triggered, [=]{
  editPanel->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
  editPanel->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
 });
 scrollGroup->addAction(scrollVertical);
 scrollMenu->addAction(scrollVertical);
// scrollVertical.addActionListener(new ActionListener() {
//         /*public*/ void actionPerformed(ActionEvent event) {
 connect(scrollVertical, &QAction::triggered, [=]{
  editPanel->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
  editPanel->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
 });
}

/*private*/ void ControlPanelEditor::makeFileMenu() {
    _fileMenu = new QMenu(tr("File"));
    _menuBar->insertMenu(_menuBar->actions().at(0),_fileMenu/*, 0*/);

//    _fileMenu->addAction(new NewPanelAction(tr("New Panel...")));

    StoreXmlUserAction* act = new StoreXmlUserAction(tr("Save Panels..."),this);
    QAction* savePanelsAction = new QAction(tr("Save Panels..."),this);
    _fileMenu->addAction(savePanelsAction);
    connect(savePanelsAction, SIGNAL(triggered()), act, SLOT(actionPerformed()));
    QAction* storeIndexItem = new QAction(tr("Store Image Index"),this);
    _fileMenu->addAction(storeIndexItem);
//    storeIndexItem.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                jmri.jmrit.catalog.ImageIndexEditor.storeImageIndex();
//            }
//        });
    connect(storeIndexItem, SIGNAL(triggered()), this, SLOT(storeImageIndexAction()));
    QAction* editItem = new QAction(tr("Rename Panel"),this);
    PositionableJComponent* z = new PositionableJComponent((Editor*)this);
    z->setScale(getPaintScale());
    //editItem->addMenu(CoordinateEdit::getNameEditAction(z));
//    _fileMenu->addAction(CoordinateEdit::getNameEditAction(z));
    _fileMenu->addAction(editItem);

    editItem = new QAction(tr("Create/Edit Image Index"),this);
    _fileMenu->addAction(editItem);
//    editItem.addActionListener(new ActionListener() {
//            ControlPanelEditor panelEd;
//            /*public*/ void actionPerformed(ActionEvent e) {
//                ImageIndexEditor ii = ImageIndexEditor.instance(panelEd);
//                ii.pack();
//                ii.setVisible(true);
//            }
//            ActionListener init(ControlPanelEditor pe) {
//                panelEd = pe;
//                return this;
//            }
//        }.init(this));
    CPEditItemActionListener* eial = new CPEditItemActionListener();
    eial->init(this);
    connect(editItem, SIGNAL(triggered()), eial, SLOT(actionPerformed()));
    editItem = new QAction(tr("Change view to Panel Editor"),this);
    _fileMenu->addAction(editItem);

//    editItem.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent event) {
    connect(editItem, &QAction::triggered, [=]{
            changeView("jmri.jmrit.display.panelEditor.PanelEditor");
            _itemPalette->dispose();
//            }
    });
    _fileMenu->addSeparator();
    QAction* deleteItem = new QAction(tr("Delete This Panel..."),this);
    _fileMenu->addAction(deleteItem);
//    deleteItem.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                if (deletePanel() ) {
//                    dispose(true);
//                }
//            }
//        });
    connect(deleteItem, SIGNAL(triggered()), this, SLOT(deleteAction()));

    _fileMenu->addSeparator();
    editItem = new QAction(tr("Close Editor"),this);
    _fileMenu->addAction(editItem);
//    editItem.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent event) {
    connect(editItem, &QAction::triggered, [=]{
                setAllEditable(false);
//            }
        });
}
void CPEditItemActionListener::actionPerformed(JActionEvent *)
{
    ImageIndexEditor* ii = ImageIndexEditor::instance(panelEd);
    ii->pack();
    ii->setVisible(true);
}
CPEditItemActionListener* CPEditItemActionListener::init(ControlPanelEditor *ed)
{
  panelEd = ed;
 return this;

}

void ControlPanelEditor::deleteAction()
{
 if (deletePanel() )
 {
  dispose(true);
 }
}

void ControlPanelEditor::storeImageIndexAction()
{
 ImageIndexEditor::storeImageIndex();
}

/**
 * Create an Edit menu to support cut/copy/paste.
 * An incredible hack to get some semblance of CCP between panels.  The hack works for
 * one of two problems.
 * 1. Invoking a copy to the system clipboard causes a delayed repaint placed on the
 *    EventQueue whenever ScrollBars are invoked.  This repaint ends with a NULL
 *    pointer exception at
 *    javax.swing.plaf.basic.BasicScrollPaneUI.paint(BasicScrollPaneUI.java:90)
 *    This error occurs regardless of the method used to put the copy in the
 *    clipboard - JDK 1.2 style or 1.4 TransferHandler
 *    Fixed! Get the plaf glue (BasicScrollPaneUI) and call installUI(_panelScrollPane)
 *    See copyToClipboard() below, line 527 (something the Java code should have done)
 *    No scrollbars - no problem.  Hack does not fix this problem.
 * 2. The clipboard provides a shallow copy of what was placed there.  For things that
 *    have an icon Map (ArrayLists) the Tranferable data is shallow.  The Hack to
 *    work around this is:  Place a reference to the panel copying to the clipboad
 *    in the clipboard and let the pasting panel callback to the copying panel
 *    to get the data.
 *    See public ArrayList<Positionable> getClipGroup() {} below.
 */
/*protected*/ void ControlPanelEditor::makeEditMenu() {
    _editMenu = new QMenu("Edit");
    _menuBar->insertMenu(_menuBar->actions().at(0), _editMenu/*, 0*/);
//    _editMenu.setMnemonic(KeyEvent.VK_E);
/*
Tutorial recommended method not satisfactory.
    TransferActionListener actionListener = new TransferActionListener();
    JMenuItem menuItem = new JMenuItem("Cut");
    menuItem.setActionCommand((String)TransferHandler.getCutAction().getValue(Action.NAME));
    menuItem.addActionListener(actionListener);
    menuItem.setAccelerator(
      KeyStroke.getKeyStroke(KeyEvent.VK_X, ActionEvent.CTRL_MASK));
    menuItem.setMnemonic(KeyEvent.VK_T);
    _editMenu.add(menuItem);

    menuItem = new JMenuItem("Copy");
    menuItem.setActionCommand((String)TransferHandler.getCopyAction().getValue(Action.NAME));
    menuItem.addActionListener(actionListener);
    menuItem.setAccelerator(
      KeyStroke.getKeyStroke(KeyEvent.VK_C, ActionEvent.CTRL_MASK));
    menuItem.setMnemonic(KeyEvent.VK_C);
    _editMenu.add(menuItem);

    menuItem = new JMenuItem("Paste");
    menuItem.setActionCommand((String)TransferHandler.getPasteAction().getValue(Action.NAME));
    menuItem.addActionListener(actionListener);
    menuItem.setAccelerator(
      KeyStroke.getKeyStroke(KeyEvent.VK_V, ActionEvent.CTRL_MASK));
    menuItem.setMnemonic(KeyEvent.VK_P);
    _editMenu.add(menuItem);
    */

    QAction* menuItem = new QAction(tr("Cut"),this);
//    menuItem.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                copyToClipboard();
//                removeSelections(NULL);
//            }
//        });
//    menuItem.setAccelerator(
//      KeyStroke.getKeyStroke(KeyEvent.VK_X, ActionEvent.CTRL_MASK));
//    menuItem.setMnemonic(KeyEvent.VK_T);
    _editMenu->addAction(menuItem);
    connect(menuItem, SIGNAL(triggered()), this, SLOT(actionCut()));

    menuItem = new QAction(tr("Copy"), this);
//    menuItem.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                copyToClipboard();
//            }
//        });
//    menuItem.setAccelerator(
//      KeyStroke.getKeyStroke(KeyEvent.VK_C, ActionEvent.CTRL_MASK));
//    menuItem.setMnemonic(KeyEvent.VK_C);
    _editMenu->addAction(menuItem);
    connect(menuItem, SIGNAL(triggered()), this, SLOT(copyToClipboard()));

    menuItem = new QAction(tr("Paste"), this);
//    menuItem.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                pasteFromClipboard();
//            }
//        });
//    menuItem.setAccelerator(
//      KeyStroke.getKeyStroke(KeyEvent.VK_V, ActionEvent.CTRL_MASK));
//    menuItem.setMnemonic(KeyEvent.VK_P);
    _editMenu->addAction(menuItem);
    connect(menuItem, SIGNAL(triggered()), this, SLOT(pasteFromClipboard()));

    menuItem = new QAction(tr("Select All"),this);
//    menuItem.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                _selectionGroup = _contents;
//                _targetPanel.repaint();
//            }
//        });
//    menuItem.setAccelerator(
//      KeyStroke.getKeyStroke(KeyEvent.VK_A, ActionEvent.CTRL_MASK));
    _editMenu->addAction(menuItem);
    connect(menuItem, SIGNAL(triggered()), this, SLOT(selectAllAction()));

}
void ControlPanelEditor::actionCut()
{
 copyToClipboard();
 removeSelections(nullptr);
}
void ControlPanelEditor::selectAllAction()
{
  QList <Positionable*> l = _contents->toList();
 QList <Positionable*>* list = &l;
 _selectionGroup = list;
 //_targetPanel->repaint();

}

/**
 * *********************** end Menus ************************
 */
/*public*/ CircuitBuilder* ControlPanelEditor::getCircuitBuilder()
{
 return _circuitBuilder;
}

/*private*/ void ControlPanelEditor::pasteFromClipboard() {
#if 0
    Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
    DataFlavor[] flavors = clipboard.getAvailableDataFlavors();
    for (int k=0; k<flavors.length; k++) {
        if (_positionableListDataFlavor.equals(flavors[k])) {
            Point pt = _targetPanel.getMousePosition(true);
            try{
//                    ArrayList clipGroup = (ArrayList)clipboard.getData(_positionableListDataFlavor);
                ControlPanelEditor ed =
                    (ControlPanelEditor)clipboard.getData(_positionableListDataFlavor);
                ArrayList<Positionable> clipGroup = ed.getClipGroup();
                if (clipGroup!=NULL && clipGroup.size()>0) {
                    Positionable pos = clipGroup.get(0);
                    int minX = pos.getLocation().x;
                    int minY = pos.getLocation().y;
                    // locate group at mouse point
                    for (int i=1; i<clipGroup.size(); i++) {
                        pos = clipGroup.get(i);
                        minX = qMin(minX, pos.getLocation().x);
                        minY = qMin(minY, pos.getLocation().y);
                    }
                    if (_pastePending) {
                        abortPasteItems();
                    }
                    _selectionGroup = new ArrayList<Positionable>();
                    for (int i=0; i<clipGroup.size(); i++) {
                        //pos = clipGroup.get(i).deepClone();
                        pos = clipGroup.get(i);
                        // make positionable belong to this editor
                        pos.setEditor(this);
                        pos.setLocation(pos.getLocation().x+pt.x-minX, pos.getLocation().y+pt.y-minY);
                        // now set display level in the pane.
                        pos.setDisplayLevel(pos.getDisplayLevel());
                        putItem(pos);
                        pos.updateSize();
                        pos.setVisible(true);
                        _selectionGroup->add(pos);
                        if (pos instanceof PositionableIcon) {
                            jmri.NamedBean bean = pos.getNamedBean();
                            if (bean!=NULL) {
                                ((PositionableIcon)pos).displayState(bean.getState());
                            }
                        }
                        if (_debug) log.debug("Paste Added at ("+pos.getLocation().x+", "+pos.getLocation().y+")");
                    }
                }
                return;
            } catch(IOException ioe) {
                log.warn("Editor Paste caught IOException", ioe);
            } catch(UnsupportedFlavorException ufe) {
                log.warn("Editor Paste caught UnsupportedFlavorException",ufe);
            }
        }
    }
#endif
}

/*
* The editor instance is dragged.  When dropped this editor will reference
* the list of positionables (_clipGroup) for pasting
*/
/*private*/ void ControlPanelEditor::copyToClipboard() {
    if (_selectionGroup!=nullptr) {
        QList <Positionable*>* dragGroup = new QList <Positionable*>();

        for (int i=0; i<_selectionGroup->size(); i++) {
            Positionable* pos = _selectionGroup->at(i)->deepClone();
            dragGroup->append(pos);
            removeFromTarget(pos);   // cloned item gets added to _targetPane during cloning
        }
        if (_debug) log->debug("copyToClipboard: cloned _selectionGroup, size= "+_selectionGroup->size());
//            abortPasteItems(dragGroup);
        _clipGroup = dragGroup;

        QClipboard* clipboard =/* Toolkit.getDefaultToolkit().getSystemClipboard();*/ QApplication::clipboard();
//        clipboard.setContents(new PositionableListDnD(this), this);
//        // workaround to recognize CCP
//        getPanelScrollPane().getUI().installUI(getPanelScrollPane());
//            clipboard.setContents(new PositionableListDnD(dragGroup), NULL);
        if (_debug) log->debug("copyToClipboard: setContents _selectionGroup, size= "+_selectionGroup->size());

    } else {
        _clipGroup = nullptr;
    }
}

/*public*/ QList <Positionable*>* ControlPanelEditor::getClipGroup()
{
 if (_debug) log->debug(QString("getClipGroup: _clipGroup")+(_clipGroup==nullptr?"=nullptr":", size= "+_clipGroup->size()));
 if (_clipGroup==nullptr)
 {
  return nullptr;
 }
 QList<Positionable*>* clipGrp = new QList<Positionable*>();
 for (int i=0; i<_clipGroup->size(); i++)
 {
  Positionable* pos = _clipGroup->at(i)->deepClone();
  clipGrp->append(pos);
  removeFromTarget(pos);   // cloned item gets added to _targetPane during cloning
 }
 return clipGrp;
}
#if 0
///// implementation of ClipboardOwner
/*public*/ void lostOwnership(Clipboard clipboard, Transferable contents) {
       /* don't care */
    if (_debug) log.debug("lostOwnership: content flavor[0] = "+contents.getTransferDataFlavors()[0]);
}
#endif
// override
/*public*/ void ControlPanelEditor::setAllEditable(bool edit)
{
 if (edit)
 {
  if (_editorMenu!=nullptr)
  {
   _menuBar->removeAction(_editorMenu->menuAction());
   //_editorMenu->setVisible(false);
  }
  if (_markerMenu!=nullptr)
  {
   _menuBar->removeAction(_markerMenu->menuAction());
 //  _markerMenu->setVisible(false);
  }
  if (_warrantMenu!=nullptr)
  {
   _menuBar->removeAction(_warrantMenu->menuAction());
   //_warrantMenu->setVisible(false);
  }
  if (_drawMenu==nullptr)
  {
   makeDrawMenu();
  }
  else
  {
   _menuBar->insertMenu(_menuBar->actions().at(0), _drawMenu/*, 0*/);
   //_drawMenu->setVisible(true);
  }
  if (_circuitMenu==nullptr)
  {
   makeCircuitMenu();
  }
  else
  {
   _menuBar->insertMenu(_menuBar->actions().at(0), _circuitMenu/*, 0*/);
   //_circuitMenu->setVisible(true);
  }
  if(_warrantMenu == nullptr)
   makeWarrantMenu(true, true);

  if (_iconMenu==nullptr)
  {
   makeIconMenu();
  }
  else
  {
   _menuBar->insertMenu(_menuBar->actions().at(0), _iconMenu/*, 0*/);
   //_iconMenu->setVisible(true);
  }
  if (_zoomMenu==nullptr)
  {
   makeZoomMenu();
  }
  else
  {
   _menuBar->insertMenu(_menuBar->actions().at(0),_zoomMenu/*, 0*/);
   //_zoomMenu->setVisible(true);
  }
  if (_optionMenu==nullptr)
  {
    makeOptionMenu();
  }
  else
  {
   _menuBar->insertMenu(_menuBar->actions().at(0),_optionMenu/*, 0*/);
   //_optionMenu->setVisible(true);
  }
  if (_editMenu==nullptr)
  {
   makeEditMenu();
  }
  else
  {
   _menuBar->insertMenu(_menuBar->actions().at(0),_editMenu/*, 0*/);
   //_editMenu->setVisible(true);
  }
  if (_fileMenu==nullptr)
  {
    makeFileMenu();
  }
  else
  {
   _menuBar->insertMenu(_menuBar->actions().at(0),_fileMenu/*, 0*/);
   //_fileMenu->setVisible(true);
  }
 }
 else
 {
  if (_fileMenu!=nullptr)
  {
   _menuBar->removeAction(_fileMenu->menuAction());
   //_fileMenu->setVisible(false);
  }
  if (_editMenu!=nullptr)
  {
   _menuBar->removeAction(_editMenu->menuAction());
   //_editMenu->setVisible(false);
  }
  if (_optionMenu!=nullptr)
  {
   _menuBar->removeAction(_optionMenu->menuAction());
   //_menuBar->setVisible(false);
  }
  if (_zoomMenu!=nullptr)
  {
   _menuBar->removeAction(_zoomMenu->menuAction());
   //_zoomMenu->setVisible(false);
  }
  if (_iconMenu!=nullptr)
  {
   _menuBar->removeAction(_iconMenu->menuAction());
   //_iconMenu->setVisible(false);
  }
  if (_warrantMenu!=nullptr)
  {
   _menuBar->removeAction(_warrantMenu->menuAction());
   //_warrantMenu->setVisible(false);
  }
  if (_circuitMenu!=nullptr)
  {
   _menuBar->removeAction(_circuitMenu->menuAction());
   //_circuitMenu->setVisible(false);
  }
  if (_drawMenu!=nullptr)
  {
   _menuBar->removeAction(_drawMenu->menuAction());
   //_drawMenu->setVisible(false);
  }
  if (((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getSystemNameList().size() > 1)
  {
   makeWarrantMenu(true, true);
  }
  if (_markerMenu==nullptr)
  {
   makeMarkerMenu();
  }
  else
  {
   _menuBar->insertMenu(_menuBar->actions().at(0),_markerMenu/*, 0*/);
   //_markerMenu->setVisible(true);
  }
  if (_editorMenu==nullptr)
  {
   _editorMenu = new QMenu(tr("Edit"));
//            _editorMenu.add(new AbstractAction(tr("OpenEditor")) {
//                    /*public*/ void actionPerformed(ActionEvent e) {
//                        setAllEditable(true);
//                    }
//             });
   QAction* act = new QAction(tr("Open Editor"),this);
   connect(act, SIGNAL(triggered(bool)), this, SLOT(setAllEditable(bool)));
  }
  _menuBar->insertMenu(_menuBar->actions().at(0),_editorMenu/*, 0*/);
 }
 Editor::setAllEditable(edit);
 setTitle();
 // _menuBar->validate();
}

// override
/*public*/ void ControlPanelEditor::setUseGlobalFlag(bool set) {
    positionableBox->setEnabled(set);
    //positionableBox.invalidate();
    controllingBox->setEnabled(set);
    //controllingBox.invalidate();
    Editor::setUseGlobalFlag(set);
}

/*private*/ void ControlPanelEditor::zoomRestore() // SLOT
{
 QList <Positionable*> contents = getContents();
 for (int i=0; i<contents.size(); i++) {
        Positionable* p = contents.at(i);
        ((Positionable*)p)->setLocation(((Positionable*)p)->getX()+_fitX, ((Positionable*)p)->getY()+_fitY);
    }
    setPaintScale(1.0);
    getTargetPanel()->views().at(0)->scale(1.0,1.0);
}

/*private*/ void ControlPanelEditor::zoomToFit() // SLOT
{
    double minX = 1000.0;
    double maxX = 0.0;
    double minY = 1000.0;
    double maxY = 0.0;
    QList <Positionable*> contents = getContents();
    for (int i=0; i<contents.size(); i++) {
        Positionable* p = contents.at(i);
        minX = qMin((double)p->getX(), minX);
        minY = qMin((double)p->getY(), minY);
        maxX = qMax((double)p->getX()+p->getWidth(), maxX);
        maxY = qMax((double)p->getY()+p->getHeight(), maxY);
    }
    _fitX = (int)qFloor(minX);
    _fitY = (int)qFloor(minY);

    QRectF dv = editScene->sceneRect();
    double ratioX = dv.width()/(maxX-minX);
    double ratioY = dv.height()/(maxY-minY);
    double ratio = qMin(ratioX, ratioY);
    setPaintScale(ratio);
    getTargetPanel()->views().at(0)->scale(ratio,ratio);
}

//@Override
/*public*/ void ControlPanelEditor::setTitle() {
    QString name = getName();
    if (name.isNull() || name.length() == 0) {
        name =tr("Untitled");
    }
    QString ending = " " + tr("Editor");
    QString defaultName = tr("ControlPanelEditor");
    defaultName = defaultName.mid(0, defaultName.length() - ending.length());
    if (name.endsWith(ending)) {
        name = name.mid(0, name.length() - ending.length());
    }
    if (name == (defaultName)) {
        name = tr("Untitled") + "(" + name + ")";
    }
   if (isEditable()) {
        JmriJFrame::setTitle(name + " " + tr("Editor"));
    } else {
        JmriJFrame::setTitle(name);
    }
    setName(name);
}

// all content loaded from file.
/*public*/ void ControlPanelEditor::loadComplete() {
 log->debug("loadComplete");
}

/**
 * After construction, initialize all the widgets to their saved config settings.
 */
/*public*/ void ControlPanelEditor::initView() {
//        editableBox.setSelected(isEditable());
    positionableBox->setChecked(allPositionable());
    controllingBox->setChecked(allControlling());
    //showCoordinatesBox.setSelected(showCoordinates());
    showTooltipBox->setChecked(showToolTip());
    hiddenBox->setChecked(showHidden());
//    switch (_scrollState) {
//        case SCROLL_NONE:
//            scrollNone.setSelected(true);
//            break;
//        case SCROLL_BOTH:
//            scrollBoth.setSelected(true);
//            break;
//        case SCROLL_HORIZONTAL:
//            scrollHorizontal.setSelected(true);
//            break;
//        case SCROLL_VERTICAL:
//            scrollVertical.setSelected(true);
//            break;
//    }
}

/***************** Overriden methods of Editor *******************/

/*protected*/ Positionable* ControlPanelEditor::getCurrentSelection(QGraphicsSceneMouseEvent* event)
{
 bool bMetaDown =event->modifiers()&Qt::MetaModifier;
 bool bControlDown = event->modifiers()&Qt::ControlModifier;
 bool bAltDown = event->modifiers() & Qt::AltModifier;
 bool bShiftDown = event->modifiers()& Qt::ShiftModifier;

 if (_pastePending && !bPopupTrigger && !bMetaDown && !bAltDown) {
     return getCopySelection(event);
 }
 QList <Positionable*>* selections = getSelectedItems(event);
 if(selections->count() > 0)
  log->debug(tr("getCurrentSelection: %1 selections").arg(selections->count()));
 if( (_disableShapeSelection || _disablePortalSelection) && selections->count())
 {
  QList<Positionable*>* list = new QList<Positionable*>();
  QListIterator<Positionable*> it(*selections);
  while (it.hasNext())
  {
   Positionable* pos = it.next();
   if (_disableShapeSelection && qobject_cast<PositionableShape*>(pos->self())) {
       continue;
   }
   if (_disablePortalSelection && qobject_cast<PortalIcon*>(pos->self())) {
       continue;
   }
   list->append(pos);
  }
  selections = list;
 }
 Positionable* selection = nullptr;
 if (selections->size() > 0)
 {
  if (bControlDown)
  {
   if (bShiftDown && selections->size() > 3)
   {
    if (_manualSelection) {
        // selection made - don't change it
        deselectSelectionGroup();
        return _currentSelection;
    }
    // show list
    QVector<QString> selects = QVector<QString>(selections->size());
    QListIterator<Positionable*> iter(*selections);
    int i = 0;
    while (iter.hasNext())
    {
     Positionable* pos = iter.next();
     if (qobject_cast<NamedBean*>(pos->self())) {
         selects.replace(i++, ((NamedBean*) pos->self())->getDisplayName());
     } else {
         selects.replace(i++,pos->getNameString());
     }
    }
    QVariantList vl = QVariantList();
    foreach(QString str, selects)
     vl.append(str);
    QVariant select = JOptionPane::showInputDialog(this, tr("Icons are stacked over each other.\nSelect the one you want."),
            tr("Question"), JOptionPane::QUESTION_MESSAGE,
            QIcon(), vl, QVariant());
    if (select != QVariant())
    {
     QListIterator<Positionable*> iter(*selections);
     while (iter.hasNext())
     {
      Positionable* pos = iter.next();
      QString name;
      if (qobject_cast<NamedBean*>(pos->self())) {
          name = ((NamedBean*) pos->self())->getDisplayName();
      } else {
          name = pos->getNameString();
      }
      if (( select.toString()) == (name)) {
          _manualSelection = true;
          return pos;
      }
     }
    } else {
        selection = selections->at(selections->size() - 1);
    }
   } else {
       // select bottom-most item over the background, otherwise take the background item
       selection = selections->at(selections->size() - 1);
       if (selection->getDisplayLevel() <= BKG && selections->size() > 1) {
           selection = selections->at(selections->size() - 2);
       }
//              _manualSelection = false;
   }
  } else {
      if (bShiftDown && selections->size() > 1) {
          selection = selections->at(1);
      } else {
          selection = selections->at(0);
      }
      if (selection->getDisplayLevel() <= BKG) {
          selection = nullptr;
      }
      _manualSelection = false;
  }
 }
 if (!isEditable() && selection != nullptr && selection->isHidden()) {
     selection = nullptr;
 }
 return selection;
}

/*protected*/ Positionable* ControlPanelEditor::getCopySelection(QGraphicsSceneMouseEvent* event) {
    if (_selectionGroup==nullptr) {
        return nullptr;
    }
    double x = event->scenePos().x();
    double y = event->scenePos().y();

    for (int i=0; i<_selectionGroup->size(); i++) {
        Positionable* p = _selectionGroup->at(i);
        QRect rect2D =  QRect(p->getX()*_paintScale,
                                                           p->getY()*_paintScale,
                                                           p->maxWidth()*_paintScale,
                                                           p->maxHeight()*_paintScale);
        if (rect2D.contains(QPoint(x, y))) {
            return p;
        }
    }
    return nullptr;
}
#if 0
/*********** KeyListener *********/
/*public*/ void keyTyped(KeyEvent e) {
}
#endif
/*public*/ void ControlPanelEditor::keyPressEvent(QKeyEvent* e)
{
// if (_selectionGroup==nullptr) {
//     return;
// }
 log->debug(tr("key pressed, _currentSelection is %1").arg(_currentSelection?_lastSelection->self()->metaObject()->className():"null"));
 if(_lastSelection!= nullptr && qobject_cast<PositionableJPanel*>(_lastSelection->self()))
 {
  ((PositionableJPanel*)_lastSelection->self())->getWidget()->keyPressEvent(e);
 }
 int x = 0;
 int y = 0;
 switch (e->key())
 {
  case Qt::Key_Up:
  case Qt::Key_Up | Qt::KeypadModifier:
  case Qt::Key_8 | Qt::KeypadModifier:
      y = -1;
      break;
  case Qt::Key_Down:
 case Qt::Key_Down | Qt::KeypadModifier:
  case Qt::Key_2 | Qt::KeypadModifier:
      y = 1;
      break;
  case Qt::Key_Left:
 case Qt::Key_Left | Qt::KeypadModifier:
  case Qt::Key_4 | Qt::KeypadModifier:
      x = -1;
      break;
  case Qt::Key_Right:
 case Qt::Key_Right | Qt::KeypadModifier:
  case Qt::Key_6 | Qt::KeypadModifier:
      x = 1;
      break;
  case Qt::Key_D:
  case Qt::Key_Delete:
  case Qt::Key_Minus:
      _shapeDrawer->_delete();
      break;
  case Qt::Key_A:
  case Qt::Key_Insert:
  case Qt::Key_Plus:
      _shapeDrawer->add(e->modifiers()&Qt::ShiftModifier);
      break;
 default:
  QWidget::keyPressEvent(e);
  return;
 }
 for (int i=0; i<_selectionGroup->size(); i++){
     moveItem(_selectionGroup->at(i), x, y);
 }
 repaint();
}

/*public*/ void ControlPanelEditor::keyReleaseEvent(QKeyEvent* e)
{
 if(_lastSelection!= nullptr && qobject_cast<PositionableJPanel*>(_lastSelection->self()))
 {
  ((PositionableJPanel*)_lastSelection->self())->getWidget()->keyPressEvent(e);
 }

}

/*********** Mouse ***************/

/*public*/ void ControlPanelEditor::mousePressed(QGraphicsSceneMouseEvent* event)
{
 bPopupTrigger = event->buttons()& Qt::RightButton;

 _mouseDownTime = QDateTime::currentMSecsSinceEpoch();
 //setToolTip(NULL); // ends tooltip if displayed
 if (_debug)
  log->debug("mousePressed at ("+QString::number(event->scenePos().x())+","+QString::number(event->scenePos().y())+") _dragging="+(_dragging?"yes":"no"));
 //  " _selectionGroup= "+(_selectionGroup==NULL?"NULL":_selectionGroup->size()));
 bool circuitBuilder =  _circuitBuilder->saveSelectionGroup(_selectionGroup);
 _anchorX = event->scenePos().x();
 _anchorY = event->scenePos().y();
 _lastX = _anchorX;
 _lastY = _anchorY;

 _currentSelection = getCurrentSelection(event);
 if(_currentSelection == nullptr)
  return;
 _lastSelection = _currentSelection;

 // if (!event.isPopupTrigger() && !event.isMetaDown() && !event.isAltDown() && !circuitBuilder) {
 if (!(event->buttons()&Qt::RightButton) && !(event->modifiers()&Qt::MetaModifier) && !(event->modifiers()&Qt::AltModifier) && !circuitBuilder)
 {
  _shapeDrawer->doMousePressed(event, _currentSelection);
  if (_currentSelection != nullptr)
  {
   _currentSelection->doMousePressed(event);
   if (isEditable())
   {
    if (!(event->modifiers()&Qt::ControlModifier)
            && (_selectionGroup != nullptr && !_selectionGroup->contains(_currentSelection)))
    {
     if (_pastePending)
     {
      abortPasteItems();
     }
     deselectSelectionGroup();
    }
   }
  }
  else
  {
   _highlightcomponent = QRectF();
   if (_pastePending)
   {
    abortPasteItems();
   }
   deselectSelectionGroup();
  }
 }
 else if (_currentSelection == nullptr || (_selectionGroup != nullptr && !_selectionGroup->contains(_currentSelection)))
 {
  deselectSelectionGroup();
 }

// if(qobject_cast<PositionableJPanel*>(_currentSelection->self()) != nullptr)
// {
//  //((MemoryInputIcon*)_currentSelection)->mousePressed(event);
//  ((PositionableJPanel*)_currentSelection->self())->getWidget()->mousePressEvent(event);
//  return;
// }

 _circuitBuilder->doMousePressed(event, _currentSelection);

 if(_targetPanel != nullptr)
  _targetPanel->repaint(); // needed for ToolTip
 else if(editScene != nullptr)
  editScene->repaint();
// paint(editScene);
}

/*public*/ void ControlPanelEditor::mouseReleased(QGraphicsSceneMouseEvent* event)
{
 bool bMetaDown =event->modifiers()&Qt::MetaModifier;
 bool bControlDown = event->modifiers()&Qt::ControlModifier;
 bool bAltDown = event->modifiers() & Qt::AltModifier;
 bool bShiftDown = event->modifiers()& Qt::ShiftModifier;

 _mouseDownTime = 0;
 //setToolTip(nullptr); // ends tooltip if displayed
 if (_debug) log->debug("mouseReleased at ("+QString::number(event->scenePos().x())+","+QString::number(event->scenePos().y())+") dragging= "+(_dragging?"yes":"no")
                           +" pastePending= "+(_pastePending?"yes":"no")+" selectRect "+(_selectRect==QRectF()?"=":"!")+"= nullptr");
 //" _selectionGroup= "+(_selectionGroup==nullptr?"NULL":_selectionGroup->size()));
 dragPos = QPointF();
 if (_dragging)
 {
  mouseDragged(event);
 }
 Positionable* selection = getCurrentSelection(event);

 //if ((event.isPopupTrigger() || event.isMetaDown() || event.isAltDown()) && !_dragging)
 if(/*(event->buttons()& Qt::RightButton)*/(bPopupTrigger || /*(event->modifiers()&Qt::MetaModifier)*/ bMetaDown) && !_dragging)
 {
  if (selection!=nullptr)
  {
   _highlightcomponent = QRectF();
   if(qobject_cast<MemoryInputIcon*>(selection->self()) != nullptr ||qobject_cast<MemorySpinnerIcon*>(selection->self()) != nullptr|| qobject_cast<MemoryComboIcon*>(selection->self())!= nullptr )
   {
    _highlightcomponent = selection->getBounds(QRectF());
    //((PositionableLabel*)selection)->_itemGroup->setFocus();
    ((PositionableJPanel*)selection->self())->getWidget()->mouseReleaseEvent(event);
//    if(_highlightcomponent.width() > 1000)
//     qDebug() << tr("_highlightcomponent width = %1").arg(_highlightcomponent.width());
//   }
//   else
    if(qobject_cast<PositionableJPanel*>(selection->self())!=nullptr)
    {
     _highlightcomponent = selection->getBounds(QRectF());
//     if(_highlightcomponent.width() > 1000)
//      qDebug() << tr("_highlightcomponent width = %1").arg(_highlightcomponent.width());
     if(event->button()&Qt::RightButton)
      showPopUp(selection, event);
    }
   }
   else
   {
    _highlightcomponent = selection->getBounds(QRectF());
//    if(_highlightcomponent.width() > 1000)
//     qDebug() << tr("_highlightcomponent width = %1").arg(_highlightcomponent.width());
    if(event->button()&Qt::RightButton)
     showPopUp(selection, event);
//   else
//    selection->setFocus();
   }
  }
  else if (!_selectRect.isNull())
  {
   emit selectionRect(_selectRect, event);
   makeSelectionGroup(event);
  }
 }
 else
 {
  if (selection!=nullptr)
  {
   //if (!event.isControlDown() && !event.isShiftDown())
   if(!(event->modifiers()&Qt::ControlModifier) && !(event->modifiers()& Qt::ShiftModifier))
   {
    selection->doMouseReleased(event);
   }
   if((qobject_cast<MemoryInputIcon*>(selection->self()) != nullptr)
      || (qobject_cast<MemorySpinnerIcon*>(selection->self()) != nullptr)
      || (qobject_cast<MemoryComboIcon*>(selection->self())!= nullptr))
   {
    //((MemoryInputIcon*)_currentSelection)->mousePressed(event);
    ((PositionableJPanel*)selection->self())->getWidget()->mouseReleaseEvent(event);
    //return;
   }
  }
  // when dragging, don't change selection group
  if (_pastePending && _dragging)
  {
      pasteItems();
  }
  if (isEditable())
  {
   if (_shapeDrawer->doMouseReleased(selection, event))
   {
    _selectRect = QRectF();
   }
   if (selection!=nullptr && !_circuitBuilder->doMouseReleased(selection, event))
   {
    if (!_dragging)
    {
     modifySelectionGroup(selection, event);
    }
   }
   if (!_selectRect.isNull())
   {
    emit selectionRect(_selectRect,event);
    makeSelectionGroup(event);
   }
  }
  if (_pastePending && _dragging)
  {
   pasteItems();
  }
 }
 _currentSelection = nullptr;
 _selectRect = QRectF();

 // if not sending MouseClicked, do it here
//    if (jmri.util.swing.SwingSettings.getNonStandardMouseEvent())
 mouseClicked(event);

 _dragging = false;
 if(_targetPanel != nullptr)
  _targetPanel->repaint(); // needed for ToolTip
 else if(editScene != nullptr)
  editScene->repaint(); // needed for ToolTip
 //paint(editScene);
//        if (_debug) log.debug("mouseReleased at ("+event.getX()+","+event.getY()+
//        " _selectionGroup= "+(_selectionGroup==NULL?"NULL":_selectionGroup->size()));
}

/*public*/ void ControlPanelEditor::mouseClicked(QGraphicsSceneMouseEvent* event)
{
 bool bControlDown = event->modifiers() & Qt::ControlModifier;
 bool bShiftDown = event->modifiers() & Qt::ShiftModifier;
 bool bRightButton = event->buttons() & Qt::RightButton;

 //if (jmri.util.swing.SwingSettings.getNonStandardMouseEvent())
 {
  qint64 time = QDateTime::currentMSecsSinceEpoch();
  if (time-_clickTime < 20)
  {
   return;
  }
  _clickTime = time;
 }

 //setToolTip(NULL); // ends tooltip if displayed
 if (_debug) log->debug("mouseClicked at ("+QString::number(event->scenePos().x())+","+QString::number(event->scenePos().y())+")");

 Positionable* selection = getCurrentSelection(event);
 if (_shapeDrawer->doMouseClicked(event))
 {
  paint(editScene);

  return;
 }

 //if (event.isPopupTrigger() || event.isMetaDown() || event.isAltDown())
 if((event->buttons()&Qt::RightButton)!=0 || (event->modifiers()&Qt::MetaModifier)!= 0 ||(event->modifiers()&Qt::AltModifier)!=0)
 {
  if (selection!=nullptr)
  {
   _highlightcomponent = QRectF();
   showPopUp(selection, event);
  }
 }
 else if (selection!=nullptr)
 {
   //if (!_circuitBuilder.doMouseClicked(selection, event) &&
//                    !event.isControlDown() && !event.isShiftDown() )
   if(!_circuitBuilder->doMouseClicked(getSelectedItems(event), event) )
   {
    selection->doMouseClicked(event);
   }
   if (qobject_cast<IndicatorTrack*>(selection->self()))
   {
    WarrantTableAction::mouseClickedOnBlock(((IndicatorTrack*) selection)->getOccBlock());
   }
  }
  if(!isEditable())
  {
   deselectSelectionGroup();
   _currentSelection = nullptr;
   _highlightcomponent = QRectF();
  }
 //_targetPanel->repaint(); // needed for ToolTip

 paint(editScene);
}

/*public*/ void ControlPanelEditor::mouseDragged(QGraphicsSceneMouseEvent* event)
{
    //if (_debug) log.debug("mouseDragged at ("+event.getX()+","+event.getY()+")");
 setToolTip(nullptr); // ends tooltip if displayed

 if (_circuitBuilder->doMouseDragged(_currentSelection, event) ) {  // is  preventing dragging! ACK
     return;
 }
 //if (!event.isPopupTrigger() && !event.isMetaDown() && !event.isAltDown() && (isEditable() || _currentSelection instanceof LocoIcon))
 if(!(event->buttons()& Qt::RightButton)
    && !(event->modifiers()& Qt::MetaModifier)
    && !(event->modifiers()& Qt::AltModifier)
    && !_shapeDrawer->doMouseDragged(event)
    && (isEditable() || qobject_cast<LocoIcon*>(_currentSelection->self())!=0))
 {
  moveIt:
  if (_currentSelection != nullptr
//      && qobject_cast<PositionableLabel*>(_currentSelection->self())
//      && getFlag(OPTION_POSITION, ((PositionableLabel*)_currentSelection)->isPositionable())
      && _currentSelection->isPositionable()
      )
  {
   int deltaX = event->scenePos().x() - _lastX;
   int deltaY = event->scenePos().y() - _lastY;
   int minX = getItemX(_currentSelection, deltaX);
   int minY = getItemY(_currentSelection, deltaY);
   if (_selectionGroup!=nullptr && _selectionGroup->contains(_currentSelection))
   {
    for (int i=0; i<_selectionGroup->size(); i++)
    {
     minX = qMin(getItemX(_selectionGroup->at(i), deltaX), minX);
     minY = qMin(getItemY(_selectionGroup->at(i), deltaY), minY);
    }
   }
   if (minX<0 || minY<0)
   {
    // Don't allow move beyond the left or top borders
    //goto moveIt;
    return;

//        // or use this choice:
//        // Expand the panel to the left or top as needed by the move
//        // Probably not the preferred solution - use the above break
//        if (_selectionGroup!=NULL && _selectionGroup->contains((QObject*)_currentSelection)) {
//            QList <Positionable*> allItems = getContents();
//            for (int i=0; i<allItems.size(); i++){
//                moveItem(allItems.at(i), -deltaX, -deltaY);
//            }
//        } else {
//            moveItem(_currentSelection, -deltaX, -deltaY);
//        }

    }
    if (_selectionGroup!=nullptr && _selectionGroup->contains(_currentSelection))
    {
     for (int i=0; i<_selectionGroup->size(); i++)
     {
      moveItem(_selectionGroup->at(i), deltaX, deltaY);
     }
     _highlightcomponent = QRectF();
    }
    else
    {
     if(qobject_cast<PositionablePolygon*>(_currentSelection->self()))
     {

     }
      moveItem(_currentSelection, deltaX, deltaY);
    }
      // don't highlight LocoIcon in edit mode
//      if (isEditable())
//      {
//       //_highlightcomponent = QRectF(((PositionableLabel*)_currentSelection)->getX(), ((PositionableLabel*)_currentSelection)->getY(),((PositionableLabel*)_currentSelection)->maxWidth(), ((PositionableLabel*)_currentSelection)->maxHeight());
//          if(qobject_cast<MemoryInputIcon*>((QObject*)_currentSelection) != NULL || qobject_cast<MemorySpinnerIcon*>((QObject*)_currentSelection)!= NULL || qobject_cast<MemoryComboIcon*>((QObject*)_currentSelection)!= NULL)
//              _highlightcomponent = _currentSelection->getBounds(QRectF());
//          else
//       _highlightcomponent =((PositionableLabel*)_currentSelection)->_itemGroup->boundingRect();
////          if(_highlightcomponent.width() > 1000)
////           qDebug() << tr("_highlightcomponent width = %1").arg(_highlightcomponent.width());
////       if(_highlightcomponent.x() == 0 && _highlightcomponent.y()  == 0 )
////       {
////        _highlightcomponent.setTopLeft(event->scenePos());
////       }
//      }
//     }
//    }
//    else
//    {
    }
    else if ((isEditable() && _selectionGroup==nullptr))
    {
     drawSelectRect(event->scenePos().x(), event->scenePos().y());
    }
   }
  _dragging = true;
  _lastX = event->scenePos().x();
  _lastY = event->scenePos().y();
  if(_targetPanel != nullptr)
  _targetPanel->repaint(); // needed for ToolTip
 else if(editScene != nullptr)
  editScene->repaint(); // needed for ToolTip
  //paint(editScene);

}

//@Override
/*public*/ void ControlPanelEditor::mouseMoved(QGraphicsSceneMouseEvent* event)
{
    //if (_debug) log.debug("mouseMoved at ("+event.getX()+","+event.getY()+")");
    //if (_dragging || event.isPopupTrigger() || event.isMetaDown() || event.isAltDown())
 dLoc = event->scenePos();
 if(_dragging || (event->buttons()&Qt::LeftButton)
    || (event->buttons()& Qt::RightButton)
    || (event->modifiers()& Qt::MetaModifier)
    || (event->modifiers()&Qt::AltModifier))
 {
  mouseDragged(event);
  return;
 }

 //if (!(event.isShiftDown() && event.isControlDown()) && !_shapeDrawer.doMouseMoved(event))
 if(!((event->modifiers()&Qt::ShiftModifier)
    && (event->modifiers()&Qt::ControlModifier))
    &&!(_shapeDrawer->doMouseMoved(event)))
 {
  Positionable* selection = getCurrentSelection(event);
  if (selection != nullptr && selection->getDisplayLevel() > BKG
      && selection->showToolTip()) {
      //showToolTip(selection, event);
      //selection->highlightlabel(true);
  } else {
     // setToolTip("");
  }
 }
 paint(editScene);
 if(_targetPanel != nullptr)
  _targetPanel->repaint(); // needed for ToolTip
 else if(editScene != nullptr)
  editScene->repaint();
 //paint(editScene);

}

//@Override
/*public*/ void ControlPanelEditor::mouseEntered(QGraphicsSceneMouseEvent * /*event*/) {
    if(_targetPanel != nullptr)
  _targetPanel->repaint(); // needed for ToolTip
 else if(editScene != nullptr)
  editScene->repaint();
}

//@Override
/*public*/ void ControlPanelEditor::mouseExited(QGraphicsSceneMouseEvent * event) {
    //setToolTip("");
    _targetPanel->repaint();  // needed for ToolTip
}
#if 0
/*public*/ void ControlPanelEditor::mouseDoubleClicked(QGraphicsSceneMouseEvent *event)
{
 //setToolTip(""); // ends tooltip if displayed
 log->debug(tr("mouseClicked at (%1,%2)").arg(event->screenPos().x()).arg(event->screenPos().y()));

 Positionable* selection = getCurrentSelection(event);
 if (_shapeDrawer->doMouseClicked(event)) {
    return;
 }

 //if (event.isPopupTrigger() || event.isMetaDown() || event.isAltDown()) {
 if((event->buttons()&Qt::RightButton) || (event->modifiers()& Qt::MetaModifier) || (event->modifiers()&Qt::AltModifier))
 {
  if (selection != NULL)
  {
      _highlightcomponent = QRectF();
      showPopUp(selection, event);
  }
 }
 else
  if (selection != NULL)
  {
    if (!_circuitBuilder->doMouseClicked(getSelectedItems(event), event)) {
        selection->doMouseClicked(event);
    }
    if (qobject_cast<IndicatorTrack*>(selection)) {
        WarrantTableAction::mouseClickedOnBlock(((IndicatorTrack*) selection)->getOccBlock());
    }
 }
 if (!isEditable())
 {
  deselectSelectionGroup();
  _currentSelection = NULL;
  _highlightcomponent = QRectF();
 }
}
#endif
#if 0
/*public*/ void mouseEntered(MouseEvent event) {
}

/*public*/ void mouseExited(MouseEvent event) {
    setToolTip(NULL);
    //_targetPanel.repaint();  // needed for ToolTip
    paint(editScene);

}
#endif

/*************** implementation of Abstract Editor methods ***********/

/**
 * The target window has been requested to close, don't delete it at this
 *   time.  Deletion must be accomplished via the Delete this panel menu item.
 */
/*protected*/ void ControlPanelEditor::targetWindowClosingEvent(QCloseEvent* e) {
    ImageIndexEditor::checkImageIndex();
    targetWindowClosing(true);
}

#if 0
/*protected*/ void paintTargetPanel(Graphics g) {
}
#endif
/**
 * Set an object's location when it is created.
 */
/*public*/ void ControlPanelEditor::setNextLocation(Positionable* obj) {
    obj->setLocation(0, 0);
}

/**
* Set up selections for a paste.  Note a copy of _selectionGroup is made that is
* NOT in the _contents.  This disconnected ArrayList is added to the _contents
* when (if) a paste is made.  The disconnected _selectionGroup can be dragged to
* a new location.
*/
/*protected*/ void ControlPanelEditor::copyItem(Positionable* p) {
    if (_debug) log->debug("Enter copyItem: _selectionGroup "+(_selectionGroup!=nullptr ?
                                              "size= "+QString::number(_selectionGroup->size()) : "null"));
    // If popup menu hit again, Paste selections and make another copy
    if (_pastePending) {
        pasteItems();
    }
    if (_selectionGroup!=nullptr && !_selectionGroup->contains(p)) {
        _selectionGroup = new QList<Positionable*>();
    }
    if (_selectionGroup==nullptr) {
        _selectionGroup = new QList <Positionable*>();
        _selectionGroup->append(p);
    }
    QList<Positionable*>* selectionGroup =  new QList<Positionable*>();
    for (int i=0; i<_selectionGroup->size(); i++) {
        Positionable* pos = _selectionGroup->at(i)->deepClone();
        selectionGroup->append(pos);
    }
    _selectionGroup = selectionGroup;  // group is now disconnected
    _pastePending = true;
//        if (_debug) log.debug("Exit copyItem: _selectionGroup->size()= "+_selectionGroup->size());
}

void ControlPanelEditor::pasteItems() {
    if (_selectionGroup!=nullptr) {
        for (int i=0; i<_selectionGroup->size(); i++) {
            Positionable* pos = _selectionGroup->at(i);
            //if (pos instanceof PositionableIcon)
            if(qobject_cast<PositionableIcon*>(pos->self())!=nullptr)
            {
                NamedBean* bean = ((PositionableIcon*)pos)->getNamedBean();
                if (bean!=nullptr) {
                    ((PositionableIcon*)pos)->displayState(bean->getState());
                }
            }
            putItem(pos);
            if (_debug) log->debug("Add "+((PositionableLabel*)_selectionGroup->at(i))->getNameString());
        }
    }
    _pastePending = false;
}

/**
* Showing the popup of a member of _selectionGroup causes an image to be placed
* in to the _targetPanel.  If the objects are not put into _contents (putItem(p))
* the image will persist.  Thus set these transitory object invisible.
*/
void ControlPanelEditor::abortPasteItems() {
    if (_debug) log->debug("abortPasteItems: _selectionGroup"+
                          (_selectionGroup==nullptr?"=NULL":(".size="+QString::number(_selectionGroup->size()))));
    if (_selectionGroup!=nullptr) {
        for (int i=0; i<_selectionGroup->size(); i++) {
            _selectionGroup->at(i)->setVisible(false);
            _selectionGroup->at(i)->remove();
        }
    }
    _selectionGroup = new QList<Positionable*>();
    _pastePending = false;
}

/**
* Add an action to copy the Positionable item and the group to which is may belong.
*/
/*public*/ void ControlPanelEditor::setCopyMenu(Positionable* p, QMenu* popup)
{
  QAction* edit = new QAction(tr("Duplicate"),this);
  DuplicateActionListener* dal = new DuplicateActionListener();
  dal->init(p, this);
//    edit.addActionListener(new ActionListener() {
//        Positionable comp;
//        /*public*/ void actionPerformed(ActionEvent e) {
//            copyItem(comp);
//        }
//        ActionListener init(Positionable pos) {
//            comp = pos;
//            return this;
//        }
//    }.init(p));
    popup->addAction(edit);
    connect(edit, SIGNAL(triggered()), dal, SLOT(actionPerformed()));
}

//@Override
/*protected*/ void ControlPanelEditor::setSelectionsScale(double s, Positionable* p) {
    if (_circuitBuilder->saveSelectionGroup(_selectionGroup)) {
        p->setScale(s);
    } else {
        Editor::setSelectionsScale(s, p);
    }
}

//@Override
/*protected*/ void ControlPanelEditor::setSelectionsRotation(int k, Positionable* p) {
    if (_circuitBuilder->saveSelectionGroup(_selectionGroup)) {
        p->rotate(k);
    } else {
        Editor::setSelectionsRotation(k, p);
    }
}

/**
 * Create popup for a Positionable object Popup items common to all
 * positionable objects are done before and after the items that pertain
 * only to specific Positionable types.
 */
//@Override
/*protected*/ void ControlPanelEditor::showPopUp(Positionable* p, QGraphicsSceneMouseEvent* event) {
 if (!( p->_itemGroup->isVisible()))
 {
     return;     // component must be showing on the screen to determine its location
 }
 QMenu* popup = new QMenu();

 PositionablePopupUtil* util = p->getPopupUtility();
 if (p->isEditable())
 {
  // items common to all
  if (p->doViemMenu())
  {
   popup->addAction(new QAction(p->getNameString(),this));
   setPositionableMenu(p, popup);
   if (p->isPositionable()) {
       setShowCoordinatesMenu(p, popup);
       setShowAlignmentMenu(p, popup);
   }
   setDisplayLevelMenu(p, popup);
   setHiddenMenu(p, popup);
   popup->addSeparator();
   setCopyMenu(p, popup);
  }

  // items with defaults or using overrides
  bool popupSet = false;
//            popupSet |= p.setRotateOrthogonalMenu(popup);
  popupSet |= p->setRotateMenu(popup);
  popupSet |= p->setScaleMenu(popup);
  if (popupSet) {
      popup->addSeparator();
      popupSet = false;
  }
  popupSet = p->setEditItemMenu(popup);
  if (popupSet) {
      popup->addSeparator();
      popupSet = false;
  }
  if (qobject_cast<PositionableLabel*>(p->self())) {
      PositionableLabel* pl = (PositionableLabel*) p;
      if (!pl->isIcon())
      {
       setColorMenu(popup, pl, ColorDialog::BORDER);
       setColorMenu(popup, pl, ColorDialog::MARGIN);
       setColorMenu(popup, pl, ColorDialog::FONT);
       setColorMenu(popup, pl, ColorDialog::TEXT);
//                    popupSet |= p.setTextEditMenu(popup);
       popupSet |= setTextAttributes(p, popup);
      }
      else if (qobject_cast<SensorIcon*>(p->self()))
      {
       popup->addAction(CoordinateEdit::getTextEditAction(p, "OverlayText", this));
       if (pl->isText()) {
           setColorMenu(popup, (QWidget*) p, ColorDialog::BORDER);
           popupSet |= setTextAttributes(p, popup);
//                        popupSet |= pl.setEditTextMenu(popup);
       }
      }
  } else if (qobject_cast<PositionableJPanel*>(p->self())) {
      setColorMenu(popup, (QWidget*) p, ColorDialog::BORDER);
      setColorMenu(popup, (QWidget*) p, ColorDialog::MARGIN);
      setColorMenu(popup, (QWidget*) p, ColorDialog::FONT);
      popupSet |= setTextAttributes(p, popup);
  }

  if (qobject_cast<LinkingObject*>(p->self())) {
      ((LinkingObject*) p)->setLinkMenu(popup);
  }

  if (popupSet) {
      popup->addSeparator();
      popupSet = false;
  }
  p->setDisableControlMenu(popup);
  if (util != nullptr) {
      util->setAdditionalEditPopUpMenu(popup);
  }
  // for Positionables with unique settings
  p->showPopUp(popup);

  if (p->doViemMenu()) {
      setShowToolTipMenu(p, popup);
      setRemoveMenu(p, popup);
  }
 } else {
  if (qobject_cast<LocoIcon*>(p->self())) {
      setCopyMenu(p, popup);
  }
  p->showPopUp(popup);
  if (util != nullptr) {
      util->setAdditionalViewPopUpMenu(popup);
  }
 }
//    popup->show(/*(Component)*/ p, p->getWidth() / 2 + (int) ((getPaintScale() - 1.0) * p->getX()),
//            p->getHeight() / 2 + (int) ((getPaintScale() - 1.0) * p->getY()));

 popup->exec(QCursor::pos());
 _currentSelection = nullptr;
}

/*public*/ void ControlPanelEditor::setColorMenu(QMenu* popup, /*JComponent*/QWidget* pos, int type) {
    QString title;
    switch (type ) {
        case ColorDialog::BORDER:
            title = tr("Edit Border settings (onpanel)");
            break;
        case ColorDialog::MARGIN:
            title = tr("Edit Margin settings (onpanel)");
            break;
        case ColorDialog::FONT:
            title = tr("Edit Font settings (onpanel)");
            break;
        case ColorDialog::TEXT:
            title = tr("Edit Text Content & settings");
            break;
        default:
            title = tr("Untitled");
            return;
    }
    QAction* edit = new QAction(title, this);
//    edit.addActionListener((ActionEvent event) -> {
//        new ColorDialog(this, pos, type, null);
//    });
    CPEEditListener* listener = new CPEEditListener(type, pos, this);
    connect(edit, SIGNAL(triggered(bool)), listener, SLOT(actionPerformed()));
    popup->addAction(edit);
}

DuplicateActionListener* DuplicateActionListener::init(Positionable* pos, ControlPanelEditor* edit)
{
 comp = pos;
 this->edit = edit;
 return this;
}
void DuplicateActionListener::actionPerformed(JActionEvent *)
{
 edit->copyItem(comp);
}



/********************* Circuitbuilder ************************************/

/*protected*/ void ControlPanelEditor::disableMenus() {
    _warrantMenu->setEnabled(false);
    _iconMenu->setEnabled(false);
    _zoomMenu->setEnabled(false);
    _optionMenu->setEnabled(false);
    _editMenu->setEnabled(false);
    _fileMenu->setEnabled(false);
}

/*public*/ void ControlPanelEditor::resetEditor() {
    // enable menus
    _warrantMenu->setEnabled(true);
    _iconMenu->setEnabled(true);
    _zoomMenu->setEnabled(true);
    _optionMenu->setEnabled(true);
    _editMenu->setEnabled(true);
    _fileMenu->setEnabled(true);
    // reset colors
    _highlightcomponent = QRectF();
//    TargetPane targetPane = (TargetPane)getTargetPanel();
//    targetPane.setDefaultColors();
    setSelectionGroup(nullptr);
    _disablePortalSelection = true;
}

/*protected*/ void ControlPanelEditor::highlight(Positionable* pos) {
    if (pos==nullptr) {
        _highlightcomponent = QRectF();
    } else {
        _highlightcomponent =  QRectF(pos->getX(), pos->getY(),
                                        pos->maxWidth(), pos->maxHeight());
    }
    repaint();
}

/*public*/ void ControlPanelEditor::setSelectionGroup(QList<Positionable*>* group) {
    _highlightcomponent = QRectF();
//        _currentSelection = nullptr;		need non-NULL for Portal dragging in CircuitBuilder
    _selectionGroup = group;
    //repaint();
}

/*protected*/ QList<Positionable*>* ControlPanelEditor::getSelectionGroup() {
    return _selectionGroup;
}

/*private*/ void ControlPanelEditor::makePortalIconMap()
{
 _portalIconMap =  new QMap<QString, NamedIcon*>();
 _portalIconMap->insert(PortalIcon::VISIBLE,
         new NamedIcon("resources/icons/throttles/RoundRedCircle20.png", "resources/icons/throttles/RoundRedCircle20.png"));
 _portalIconMap->insert(PortalIcon::PATH,
         new NamedIcon("resources/icons/greenSquare.gif", "resources/icons/greenSquare.gif"));
 _portalIconMap->insert(PortalIcon::HIDDEN,
         new NamedIcon("resources/icons/Invisible.gif", "resources/icons/Invisible.gif"));
 _portalIconMap->insert(PortalIcon::TO_ARROW,
         new NamedIcon("resources/icons/track/toArrow.gif", "resources/icons/track/toArrow.gif"));
 _portalIconMap->insert(PortalIcon::FROM_ARROW,
         new NamedIcon("resources/icons/track/fromArrow.gif", "resources/icons/track/fromArrow.gif"));
}

/*protected*/ NamedIcon* ControlPanelEditor::getPortalIcon(QString name)
{
 if (_portalIconMap == nullptr || _portalIconMap->isEmpty())
 {		// set defaults
     makePortalIconMap();
 }
 return _portalIconMap->value(name);
}
/*public*/ QMap<QString, NamedIcon*>* ControlPanelEditor::getPortalIconMap() {
 if (_portalIconMap == nullptr || _portalIconMap->isEmpty())
 {		// set defaults
  makePortalIconMap();
 }
 return _portalIconMap;
}

/*public*/ void ControlPanelEditor::setDefaultPortalIcons(QMap<QString, NamedIcon*>* map)
{
 _portalIconMap = map;
 QVectorIterator<Positionable*> it(  *_contents);
 while (it.hasNext())
 {
  Positionable* pos = it.next();
  //f (pos instanceof PortalIcon)
  if(qobject_cast<PortalIcon*>(pos->self()) != nullptr)
  {
   ((PortalIcon*) pos)->initMap();
  }
 }
}


/**************************** DnD **************************************/

/*protected*/ void ControlPanelEditor::makeDataFlavors() {
//        _targetPanel.setTransferHandler(new DnDIconHandler(this));
    try {
        _positionableDataFlavor = new DataFlavor(POSITIONABLE_FLAVOR);
        _namedIconDataFlavor = new DataFlavor(ImageIndexEditor::IconDataFlavorMime);
        _positionableListDataFlavor = new DataFlavor(POSITIONABLE_LIST_FLAVOR);
    } catch (ClassNotFoundException cnfe) {
//        cnfe.printStackTrace();
    }
//    new DropTarget(this, DnDConstants.ACTION_COPY_OR_MOVE, this);
}

#if 0
/*************************** DropTargetListener ************************/

/*public*/ void dragExit(DropTargetEvent evt) {}
/*public*/ void dragEnter(DropTargetDragEvent evt) {}
/*public*/ void dragOver(DropTargetDragEvent evt) {}
/*public*/ void dropActionChanged(DropTargetDragEvent evt) {}

//@SuppressWarnings("unchecked")
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="SBSC_USE_STRINGBUFFER_CONCATENATION")
// Only used occasionally, so inefficient String processing not really a problem
// though it would be good to fix it if you're working in this area
/*public*/ void drop(DropTargetDropEvent evt) {
    try {
        //Point pt = evt.getLocation(); coords relative to entire window
        Point pt = _targetPanel.getMousePosition(true);
        Transferable tr = evt.getTransferable();
        if (_debug) {
            DataFlavor[] flavors = tr.getTransferDataFlavors();
            String flavor = "";
            for (int i=0; i<flavors.length; i++) {
                flavor += flavors[i].getrepresentativeClass().getName()+", ";
            }
            log.debug("Editor Drop: flavor classes= "+flavor);
        }
        if (tr.isDataFlavorSupported(_positionableDataFlavor)) {
            Positionable item = (Positionable)tr.getTransferData(_positionableDataFlavor);
            if (item==NULL) {
//                    if (_debug) log.debug("Drop of NULL POSITIONABLE_FLAVOR");
                JOptionPane.showMessageDialog(NULL, ItemPalette.rbp.getString("noRowSelected"),
                        ItemPalette.rb.getString("warnTitle"), JOptionPane.WARNING_MESSAGE);
                return;
            }
            item.setLocation(pt.x, pt.y);
            // now set display level in the pane.
            item.setDisplayLevel(item.getDisplayLevel());
            item.setEditor(this);
            putItem(item);
            item.updateSize();
            //if (_debug) log.debug("Drop positionable "+item.getNameString()+
            //                                    " as "+item.getClass().getName()+
            //                                    ", w= "+item.maxWidth()+", h= "+item.maxHeight());
            evt.dropComplete(true);
            return;
        } else if (tr.isDataFlavorSupported(_namedIconDataFlavor)) {
              NamedIcon newIcon = new NamedIcon((NamedIcon)tr.getTransferData(_namedIconDataFlavor));
              String url = newIcon.getURL();
              NamedIcon icon = NamedIcon.getIconByName(url);
              PositionableLabel ni = new PositionableLabel(icon, this);
              ni.setPopupUtility(NULL);        // no text
              // infer a background icon from the size
              if (icon.getIconHeight()>500 || icon.getIconWidth()>600) {
                  ni.setDisplayLevel(BKG);
              } else {
                  ni.setDisplayLevel(ICONS);
              }
              ni.setLocation(pt.x, pt.y);
              ni.setEditor(this);
              putItem(ni);
              ni.updateSize();
              evt.dropComplete(true);
              return;
        } else if (tr.isDataFlavorSupported(DataFlavor.stringFlavor)) {
            String text = (String)tr.getTransferData(DataFlavor.stringFlavor);
            PositionableLabel l = new PositionableLabel(text, this);
            l.setSize(l.getPreferredSize().width, l.getPreferredSize().height);
            l.setDisplayLevel(LABELS);
            l.setLocation(pt.x, pt.y);
            l.setEditor(this);
            putItem(l);
            evt.dropComplete(true);
        } else if (tr.isDataFlavorSupported(_positionableListDataFlavor)) {
            ArrayList<Positionable> dragGroup =
                    (ArrayList<Positionable>)tr.getTransferData(_positionableListDataFlavor);
            for (int i=0; i<dragGroup.size(); i++) {
                Positionable pos = dragGroup.get(i);
                pos.setEditor(this);
                putItem(pos);
                pos.updateSize();
                if (_debug) log.debug("DnD Add "+pos.getNameString());
            }
        } else {
            log.warn("Editor DropTargetListener  supported DataFlavors not available at drop from "
                     +tr.getClass().getName());
        }
    } catch(IOException ioe) {
        log.warn("Editor DropTarget caught IOException", ioe);
    } catch(UnsupportedFlavorException ufe) {
        log.warn("Editor DropTarget caught UnsupportedFlavorException",ufe);
    }
    if (_debug) log.debug("Editor DropTargetListener drop REJECTED!");
    evt.rejectDrop();
}

static /*protected*/ class PositionableListDnD implements Transferable {
    ControlPanelEditor _sourceEditor;
    DataFlavor _dataFlavor;

    PositionableListDnD(ControlPanelEditor source) {
        _sourceEditor = source;
        try {
            _dataFlavor = new DataFlavor(POSITIONABLE_LIST_FLAVOR);
        } catch (ClassNotFoundException cnfe) {
            cnfe.printStackTrace();
        }
    }

    /*public*/ Object getTransferData(DataFlavor flavor) throws UnsupportedFlavorException,IOException {
        if (log.isDebugEnabled()) log.debug("PositionableListDnD.getTransferData:");
        if (flavor.equals(_dataFlavor)) {
            return _sourceEditor;
        }
        throw new UnsupportedFlavorException(flavor);
    }

    /*public*/ DataFlavor[] getTransferDataFlavors() {
        return new DataFlavor[] { _dataFlavor };
    }

    /*public*/ bool isDataFlavorSupported(DataFlavor flavor) {
        if (flavor.equals(_dataFlavor)) {
            return true;
        }
        return false;
    }
//}
#endif
void ControlPanelEditor::dragEnterEvent(QDragEnterEvent *event)
{
 event->acceptProposedAction();
}
void ControlPanelEditor::dragMoveEvent(QDragMoveEvent *de)
{
 // The event needs to be accepted here
 de->accept();
}
void ControlPanelEditor::dropEvent(QGraphicsSceneDragDropEvent *event)
{
 if(event->mimeData()->hasFormat("object/x-myApplication-object"))
 {
  QByteArray objectData = event->mimeData()->data("object/x-myApplication-object");
  QDomDocument doc("myDocument");
  doc.setContent(objectData, true);
  QString representativeClass;
  QDomNodeList list = doc.childNodes();
  QDomElement e = list.at(0).toElement();
  representativeClass= e.tagName();
  if(representativeClass == "reportericon")
  {
   ReporterIconXml* xml = new ReporterIconXml();
   //xml->doc.setContent(objectData,true);
   xml->doc = doc;
//   QDomNodeList list = xml->doc.childNodes();
//   QDomElement e = list.at(0).toElement();
   xml->load(e,this);
   ReporterIcon* l = xml->getIcon();
   ((Positionable*)l)->setLocation(event->scenePos().x(), event->scenePos().y());
   addToTarget(l);
  }
  else  if(representativeClass=="turnouticon")
  {
   TurnoutIconXml* xml = new TurnoutIconXml;
   xml->doc = doc;
   log->debug(tr("drop xml data: %1").arg(xml->doc.toString()));
//   QDomNodeList list = xml->doc.childNodes();
//   QDomElement e = list.at(0).toElement();

   xml->load(e,this);
   TurnoutIcon* l = xml->getIcon();
   ((Positionable*)l)->setLocation(event->scenePos().x(), event->scenePos().y());
   l->setLevel(Editor::TURNOUTS);
   addToTarget(l);
  }
  else if(representativeClass=="sensoricon")
  {
   SensorIconXml* xml = new SensorIconXml;
   //xml->doc.setContent(QUrl::fromEncoded(xmlData.toLocal8Bit()).toString());
   xml->doc = doc;
//   QDomNodeList list = xml->doc.childNodes();
//   QDomElement e = list.at(0).toElement();
   xml->load(e,this);
   SensorIcon* l = xml->getIcon();
   ((Positionable*)l)->setLocation(event->scenePos().x(), event->scenePos().y());
   l->setLevel(Editor::SENSORS);
   l->setEditor(this);
   addToTarget(l);
  }
  else if(representativeClass=="LightIcon")
  {
   LightIconXml* xml = new LightIconXml;
   //xml->doc.setContent(QUrl::fromEncoded(xmlData.toLocal8Bit()).toString());
   xml->doc = doc;
//   QDomNodeList list = xml->doc.childNodes();
//   QDomElement e = list.at(0).toElement();
   xml->load(e,this);
   LightIcon* l = xml->getIcon();
   ((Positionable*)l)->setLocation(event->scenePos().x(), event->scenePos().y());
   l->setLevel(Editor::LIGHTS);
   addToTarget(l);
  }
  else if(representativeClass=="indicatortrackicon")
  {
   IndicatorTrackIconXml* xml = new IndicatorTrackIconXml;
   //xml->doc.setContent(QUrl::fromEncoded(xmlData.toLocal8Bit()).toString());
   xml->doc = doc;
   QDomNodeList list = xml->doc.childNodes();
   QDomElement e = list.at(0).toElement();
   xml->load(e,this);
   IndicatorTrackIcon* l = xml->getIcon();
   ((Positionable*)l)->setLocation(event->scenePos().x(), event->scenePos().y());
   l->setLevel(Editor::TURNOUTS);
   addToTarget(l);
  }
  else if(representativeClass=="indicatorturnouticon")
  {
   IndicatorTurnoutIconXml* xml = new IndicatorTurnoutIconXml;
   //xml->doc.setContent(QUrl::fromEncoded(xmlData.toLocal8Bit()).toString());
   xml->doc = doc;
   QDomNodeList list = xml->doc.childNodes();
   QDomElement e = list.at(0).toElement();
   QGraphicsScene* scene = getTargetPanel();
   //connect(scene, SIGNAL(changed(QList<QRectF>)), this, SLOT(sceneChanged(QList<QRectF>)));
   xml->load(e,this);
   IndicatorTurnoutIcon* l = xml->getIcon();
   ((Positionable*)l)->setLocation(event->scenePos().x(), event->scenePos().y());
   l->setLevel(Editor::TURNOUTS);
   addToTarget(l);
  }
  else if(representativeClass=="signalheadicon")
  {
   SignalHeadIconXml* xml = new SignalHeadIconXml;
   //xml->doc.setContent(QUrl::fromEncoded(xmlData.toLocal8Bit()).toString());
   xml->doc = doc;
//   QDomNodeList list = xml->doc.childNodes();
//   QDomElement e = list.at(0).toElement();
   xml->load(e,this);
   SignalHeadIcon* l = xml->getIcon();
   ((Positionable*)l)->setLocation(event->scenePos().x(), event->scenePos().y());
   l->setLevel(Editor::SIGNALS);
   addToTarget(l);
  }
  else if(representativeClass=="signalmasticon")
  {
   SignalMastIconXml* xml = new SignalMastIconXml;
   //xml->doc.setContent(QUrl::fromEncoded(xmlData.toLocal8Bit()).toString());
   xml->doc = doc;
   //   QDomNodeList list = xml->doc.childNodes();
   //   QDomElement e = list.at(0).toElement();
   xml->load(e,this);
   SignalMastIcon* l = xml->getIcon();
   ((Positionable*)l)->setLocation(event->scenePos().x(), event->scenePos().y());
   l->setLevel(Editor::SIGNALS);
   addToTarget(l);
  }
  else if(representativeClass=="memoryicon")
  {
      MemoryIconXml* xml = new MemoryIconXml;
      xml->doc = doc;
      QDomNodeList list = xml->doc.childNodes();
      QDomElement e = list.at(0).toElement();
      xml->load(e,this);
      MemoryIcon* l = xml->getIcon();
      l->setLevel(Editor::MEMORIES);
      l->setLocation(event->scenePos().x(), event->scenePos().y());
      //addToTarget(l); // load adds it
  }
  else if(representativeClass=="memoryInputIcon")
  {
      MemoryInputIconXml* xml = new MemoryInputIconXml;
      xml->doc = doc;
      QDomNodeList list = xml->doc.childNodes();
      QDomElement e = list.at(0).toElement();
      xml->load(e,this);
      MemoryInputIcon* l = xml->getIcon();
      l->setLocation(event->scenePos().x(), event->scenePos().y());
      l->setLevel(Editor::MEMORIES);
      addToTarget(l);
  }
  else if(representativeClass=="memoryComboIcon")
  {
      MemoryComboIconXml* xml = new MemoryComboIconXml;
      xml->doc = doc;
      QDomNodeList list = xml->doc.childNodes();
      QDomElement e = list.at(0).toElement();
      xml->load(e,this);
      MemoryComboIcon* l = xml->getIcon();
      l->setLocation(event->scenePos().x(), event->scenePos().y());
      l->setLevel(Editor::MEMORIES);
      addToTarget(l);
  }
  else if(representativeClass=="MemorySpinnerIcon")
  {
      MemorySpinnerIconXml* xml = new MemorySpinnerIconXml;
      xml->doc = doc;
      QDomNodeList list = xml->doc.childNodes();
      QDomElement e = list.at(0).toElement();
      xml->load(e,this);
      MemorySpinnerIcon* l = xml->getIcon();
      l->setLocation(event->scenePos().x(), event->scenePos().y());
      l->setLevel(Editor::MEMORIES);
      addToTarget(l);
  }
  else if(representativeClass=="positionablelabel")
  {
   PositionableLabelXml* xml = new PositionableLabelXml;
   xml->doc = doc;
   QDomNodeList list = xml->doc.childNodes();
   QDomElement e = list.at(0).toElement();
   xml->load(e,this);
   PositionableLabel* l = xml->getIcon();
   ((Positionable*)l)->setLocation(event->scenePos().x(), event->scenePos().y());
   l->setLevel(Editor::LABELS);
   addToTarget(l);
  }
  else if(representativeClass=="multisensoricon")
  {
   MultiSensorIconXml* xml = new MultiSensorIconXml;
   xml->doc = doc;
   QDomNodeList list = xml->doc.childNodes();
   QDomElement e = list.at(0).toElement();
   xml->load(e,this);
   MultiSensorIcon* l = xml->getIcon();
   ((Positionable*)l)->setLocation(event->scenePos().x(), event->scenePos().y());
   addToTarget(l);
  }
  else if(representativeClass=="fastclock")
  {
   AnalogClock2DisplayXml* xml = new AnalogClock2DisplayXml;
   xml->doc = doc;
   QDomNodeList list = xml->doc.childNodes();
   QDomElement e = list.at(0).toElement();
   xml->load(e,this);
   AnalogClock2Display* l = new AnalogClock2Display(this);//  xml->getIcon();
   ((Positionable*)l)->setLocation(event->scenePos().x(), event->scenePos().y());
   l->setOpaque(false);
   l->update();
   l->setDisplayLevel(Editor::CLOCK);
   addToTarget(l);
  }
  else if(representativeClass=="reportericon")
  {
   ReporterIconXml* xml = new ReporterIconXml;
   xml->doc = doc;
   QDomNodeList list = xml->doc.childNodes();
   QDomElement e = list.at(0).toElement();
   xml->load(e,this);
   ReporterIcon* l =  xml->getIcon();
   ((Positionable*)l)->setLocation(event->scenePos().x(), event->scenePos().y());
   l->setOpaque(false);
   l->update();
   l->setDisplayLevel(Editor::ICONS);
   addToTarget(l);
  }
  else
   log->warn(tr("representativeClass '%1' not found").arg((representativeClass==""?"'null'":representativeClass)));

 }
#if 0
 else if(text.contains(";"))
 {
     QString name = text.mid(0, text.indexOf(";"));
     QString type = text.mid(text.indexOf(";")+1);
     if(type=="TurnoutIcon")
     {
      TurnoutIcon* t = new TurnoutIcon(this);
      t->setTurnout(name);
      ((Positionable*)t)->setLocation(event->scenePos().x(), event->scenePos().y());
      putItem((Positionable*)t);
     }
     else if(type=="SensorIcon")
     {
      MultiIconEditor*   iconEditor = new MultiIconEditor(4);
         iconEditor->setIcon(0, "Active:",":/resources/icons/smallschematics/tracksegments/circuit-occupied.gif");
         iconEditor->setIcon(1, "Inactive", ":/resources/icons/smallschematics/tracksegments/circuit-empty.gif");
         iconEditor->setIcon(2, "Inconsistent:", ":/resources/icons/smallschematics/tracksegments/circuit-error.gif");
         iconEditor->setIcon(3, "Unknown:",":/resources/icons/smallschematics/tracksegments/circuit-error.gif");
         iconEditor->complete();
      SensorIcon* t = new SensorIcon(this);
      t->setIcon("SensorStateActive", iconEditor->getIcon(0));
      t->setIcon("SensorStateInactive", iconEditor->getIcon(1));
      t->setIcon("BeanStateInconsistent", iconEditor->getIcon(2));
      t->setIcon("BeanStateUnknown", iconEditor->getIcon(3));
      ((Positionable*)t)->setLocation(event->scenePos().x(), event->scenePos().y());
      t->setLevel(Editor::SENSORS);
      t->setSensor(name);
      t->setVisible(true);
      putItem((Positionable*)t);
     }
     else if(type=="SignalHeadIcon")
     {
      SignalHeadIcon* t = new SignalHeadIcon(this);
      ((Positionable*)t)->setLocation(event->scenePos().x(), event->scenePos().y());
      t->setSignalHead(name);
      putItem((Positionable*)t);
     }
     else if(type=="LightIcon")
     {
      LightIcon* t = new LightIcon(this);
      ((Positionable*)t)->setLocation(event->scenePos().x(), event->scenePos().y());
      t->setLight(name);
      putItem((Positionable*)t);
     }
     else if(type=="MemoryIcon")
     {
      MemoryIcon* t = new MemoryIcon(name,this);
      t->setLocation(event->scenePos().x(), event->scenePos().y());
//      t->setLight(name);
      t->setLevel(Editor::MEMORIES);
      putItem((Positionable*)t);
     }
     else if(type=="MemoryInputIcon")
     {
      MemoryInputIcon* t = new MemoryInputIcon(5,this);
      t->setLocation(event->scenePos().x(), event->scenePos().y());
//      t->setLight(name);
      t->setLevel(Editor::MEMORIES);
      putItem((Positionable*)t);
     }
     else if(type=="MemoryComboIcon")
     {
      MemoryComboIcon* t = new MemoryComboIcon(this, QStringList());
      t->setLocation(event->scenePos().x(), event->scenePos().y());
//      t->setLight(name);
      t->setLevel(Editor::MEMORIES);
      putItem((Positionable*)t);
     }
     else if(type=="MemorySpinnerIcon")
     {
      MemorySpinnerIcon* t = new MemorySpinnerIcon(this);
      t->setLocation(event->scenePos().x(), event->scenePos().y());
//      t->setLight(name);
      t->setLevel(Editor::MEMORIES);
      putItem((Positionable*)t);
     }
     else if(type=="AnalogClock2Display")
     {
      AnalogClock2Display* t = new AnalogClock2Display(this);
      t->setOpaque(false);
      t->update();
      t->setLocation(event->scenePos().x(), event->scenePos().y());
      t->setLevel(Editor::CLOCK);
      ((Positionable*)t)->setVisible(true);
      t->setScale(1.0);
      putItem((Positionable*)t);
      t->paint(editScene);
     }
     else if(type == "IndicatorTrackIcon")
     {
      IndicatorTrackIcon* t = new IndicatorTrackIcon(this);

      ((Positionable*)t)->setLocation(event->scenePos().x(), event->scenePos().y());
      t->setLevel(Editor::TURNOUTS);
      putItem((Positionable*)t);
     }
     else if(type == "IndicatorTurnoutIcon")
     {
      IndicatorTurnoutIcon* t = new IndicatorTurnoutIcon(this);

      ((Positionable*)t)->setLocation(event->scenePos().x(), event->scenePos().y());
      t->setLevel(Editor::TURNOUTS);
      putItem((Positionable*)t);
     }
     else if(type=="PositionableLabel")
     {
      PositionableLabel* l = new PositionableLabel(NamedIcon::getIconByName(name), /*_editor*/(Editor*)parent());
      l->setPopupUtility(NULL);        // no text
      l->setLevel(Editor::BKG);
      ((Positionable*)l)->setLocation(event->scenePos().x(), event->scenePos().y());
      putItem((Positionable*)l);
     }
 }
#endif
}
void ControlPanelEditor::sceneChanged(QList<QRectF> /*rect*/)
{
 qDebug("scene changed");
}

//void ControlPanelEditor::keyPressEvent(QKeyEvent * event)
//{
// QList<Positionable*>* l = getSelectedItems(QPointF(_lastX, _lastY));
// if(l->size() > 0)
//     _currentSelection = l->at(0);
// if(_currentSelection != NULL &&(qobject_cast<MemoryInputIcon*>((QObject*)_currentSelection) != NULL ||qobject_cast<MemorySpinnerIcon*>((QObject*)_currentSelection) != NULL|| qobject_cast<MemoryComboIcon*>((QObject*)_currentSelection)!= NULL))
//    {
//     editScene->setFocusItem(((PositionableJPanel*)_currentSelection)->widget);
//       ((PositionableJPanel*)_currentSelection)->widget->keyPressEvent(event);
//     event->setAccepted(true);
//        return;
//    }
//}
//void ControlPanelEditor::keyReleaseEvent(QKeyEvent * event)
//{
//    QList<Positionable*>* l = getSelectedItems(QPointF(_lastX, _lastY));
//    if(l->size() > 0)
//        _currentSelection = l->at(0);

//    if(_currentSelection != NULL &&(qobject_cast<MemoryInputIcon*>((QObject*)_currentSelection) != NULL ||qobject_cast<MemorySpinnerIcon*>((QObject*)_currentSelection) != NULL|| qobject_cast<MemoryComboIcon*>((QObject*)_currentSelection)!= NULL))
//    {
//        ((PositionableJPanel*)_currentSelection)->widget->keyReleaseEvent(event);
//        event->setAccepted(true);
//        return;
//    }
//}

/*protected*/ void ControlPanelEditor::setSecondSelectionGroup(QList<Positionable*>* list) {
        _secondSelectionGroup = list;
    }

//@Override
/*protected*/ void ControlPanelEditor::paintTargetPanel(QGraphicsScene* g)
{
  // needed to create PositionablePolygon
  _shapeDrawer->paint(g);
//  foreach (Positionable* p, *_contents) {
//   if(qobject_cast<PositionablePolygon*>(p) != NULL)
//    p->paint(g);
//  }


#if 1
  if (_secondSelectionGroup != NULL)
  {
//        Graphics2D g2d = (Graphics2D) g;
//        g2d.setColor(new Color(150, 150, 255));
//        g2d.setStroke(new java.awt.BasicStroke(2.0f));
  foreach (Positionable* p, *_secondSelectionGroup)
  {
      //if (!(p instanceof jmri.jmrit.display.controlPanelEditor.shape.PositionableShape)) {
   if(qobject_cast<PositionableShape*>(p->self()) == NULL)
   {
    QGraphicsRectItem* item = new QGraphicsRectItem(p->getX(), p->getY(), p->maxWidth(), p->maxHeight());
    item->setPen(QPen(QColor(150, 150, 255),2));
    if(item && item->scene())
     log->warn(tr("item already has been added %1 %2").arg(__FILE__).arg(__LINE__));
    g->addItem(item);
   }
   else
   {
    ((PositionableShape*)p)->paint(g);
   }
  }
 }
#endif
}

/*public*/ QString ControlPanelEditor::getClassName(){
 return "jmri.jmrit.display.controlpaneleditor.ControlPanelEditor";
}
