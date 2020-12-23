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
#include "lememoryicon.h"
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
#include <QCheckBox>
#include "jtextfield.h"
#include <QPushButton>
#include <QLabel>
#include "joptionpane.h"
#include <QComboBox>
#include "xmladapter.h"
#include "class.h"
#include "lcdclockframe.h"
#include "nixieclockframe.h"

PanelEditor::PanelEditor(QWidget *parent) :
    Editor("NoName", false, true, parent),
    ui(new Ui::PanelEditor)
{
 ui->setupUi(this);
 // init("NoName");  must be called by subclass
 setTitle();
 initComponents();
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



//    /*public*/ PanelEditor() {}

/*public*/ PanelEditor::PanelEditor(QString name, QWidget *parent) :
        Editor(name, /*false*/true, true, parent),
        ui(new Ui::PanelEditor)
{
 //super(name, false, true);
 ui->setupUi(this);

 // init("NoName");  must be called by subclass
 setTitle();
 initComponents();
}

/*protected*/ void PanelEditor::init(QString name)
{
 log = new Logger("PanelEditor");
 setObjectName("PanelEditor");
 setProperty("JavaClassName", "jmri.jmrit.display.panelEditor.PanelEditor");

 log->setDebugEnabled(false);
 _debug = log->isDebugEnabled();
 _multiItemCopyGroup = nullptr;  // items gathered inside fence
 pasteItemFlag = false;
 _delete = false;
 _showCoordinates = true;
 _currentSelection = nullptr;
 delayedPopupTrigger = false;
 addItemViaMouseClick = false;
 _lastX = _lastY = 0;

 editableBox = new QCheckBox(tr("Panel items popup menus active"));
 positionableBox = new QCheckBox(tr("All panel items can be repositioned"));
 controllingBox = new QCheckBox(tr("Panel items control layout"));
 //showCoordinatesBox = new QCheckBox(tr("Show item coordinates in popup menu"));
 showTooltipBox = new QCheckBox(tr("Show Tooltips for all items"));
 hiddenBox = new QCheckBox(tr("Show all hidden Items"));
 menuBox = new QCheckBox(tr("Panel has menu"));
 scrollableLabel = new QLabel(tr("Panel scrollbars"));
 scrollableComboBox = new QComboBox();

 labelAdd = new QPushButton(tr("Add text:"));
 nextLabel = new JTextField(10);
 nextX = new JTextField(tr("0"),4);
 nextY = new JTextField(tr("0"),4);

 JmriJFrame* frame = new JmriJFrameX(name + " " + (tr("Editor")));
 QWidget* contentPane = frame->getContentPane();
 QVBoxLayout* contentPaneLayout = new QVBoxLayout(contentPane);
 QWidget* common = new QWidget();
 common->setLayout(new FlowLayout());
 common->layout()->addWidget(new QLabel(" x:"));
 common->layout()->addWidget(nextX);
 common->layout()->addWidget(new QLabel(" y:"));
 common->layout()->addWidget(nextY);
 contentPaneLayout->addWidget(common);
 //setAllEditable(true);
 setShowHidden(true);
// super.setTargetPanel(null, makeFrame(name));
// super.setTargetPanelSize(400, 300);
// super.setDefaultToolTip(new ToolTip(null, 0, 0, new Font("SansSerif", Font.PLAIN, 12),
//         Color.black, new Color(215, 225, 255), Color.black));
 // set scrollbar initial state
 setScroll(SCROLL_BOTH);
 QMenuBar* frameMenubar = new QMenuBar();
 frame->setMenuBar(frameMenubar);
 frameMenubar->addMenu(HelpUtil::instance()->makeHelpMenu("package.jmri.jmrit.display.PanelEditor", true, this));


 // allow renaming the panel
 {
     QWidget* namep = new QWidget();
     namep->setLayout(new FlowLayout());
     QPushButton* b = new QPushButton(tr("Rename Panel%1").arg("..."));
//     b.addActionListener(new ActionListener() {
//         PanelEditor editor;

//         @Override
//         public void actionPerformed(ActionEvent e) {
//             // prompt for name
//             String newName = JOptionPane.showInputDialog(null, tr("PromptNewName"));
//             if (newName == null) {
//                 return;  // cancelled
//             }
//             if (InstanceManager.getDefault(PanelMenu.class).isPanelNameUsed(newName)) {
//                 JOptionPane.showMessageDialog(null, tr("CanNotRename"), tr("PanelExist"),
//                         JOptionPane.ERROR_MESSAGE);
//                 return;
//             }
//             if (getTargetPanel().getTopLevelAncestor() != null) {
//                 ((JFrame) getTargetPanel().getTopLevelAncestor()).setTitle(newName);
//             }
//             editor.setTitle();
//             InstanceManager.getDefault(PanelMenu.class).renameEditorPanel(editor);
//         }

//         ActionListener init(PanelEditor e) {
//             editor = e;
//             return this;
//         }
//     }.init(this));
     (new RenameActionListener())->init(this);
     namep->layout()->addWidget(b);
     //this.getContentPane().add(namep);
     contentPaneLayout->addWidget(namep);
 }
 // add a text label
 {
     QWidget* panel = new QWidget();
     panel->setLayout(new FlowLayout());
     panel->layout()->addWidget(labelAdd);
     labelAdd->setEnabled(false);
     labelAdd->setToolTip(tr("This button will be active after you type text into the text box"));
     panel->layout()->addWidget(nextLabel);
//     labelAdd.addActionListener(new ActionListener() {
//         PanelEditor editor;

//         @Override
//         public void actionPerformed(ActionEvent a) {
//             editor.addLabel(nextLabel.getText());
//         }

//         ActionListener init(PanelEditor e) {
//             editor = e;
//             return this;
//         }
//     }.init(this));
     connect(labelAdd, &QPushButton::clicked, [=]{
      this->addLabel(nextLabel->text());
     });
//     nextLabel.addKeyListener(new KeyAdapter() {
//         @Override
//         public void keyReleased(KeyEvent a) {
//             if (nextLabel.getText().equals("")) {
//                 labelAdd.setEnabled(false);
//                 labelAdd.setToolTipText(tr("ToolTipWillActivate"));
//             } else {
//                 labelAdd.setEnabled(true);
//                 labelAdd.setToolTipText(null);
//             }
//         }
//     });
//     nextLabel->addKeyListener(new PEKeyListener(this));
     connect(nextLabel, &JTextField::textChanged, [=]{
      if (nextLabel->text() ==("")) {
          labelAdd->setEnabled(false);
          labelAdd->setToolTip(tr("This button will be active after you type text into the text box"));
      } else {
          labelAdd->setEnabled(true);
          labelAdd->setToolTip("");
      }
     });
  contentPaneLayout->addWidget(panel);
 }
 // Selection of the type of entity for the icon to represent is done from a combobox
 _addIconBox = new QComboBox();
// _addIconBox->setMinimumSize(QSize(75, 75));
// _addIconBox->setMaximumSize(QSize(200, 200));
 _addIconBox->addItem(tr("Right Hand Turnout"), "RightTurnout");//new ComboBoxItem("RightTurnout"));
 _addIconBox->addItem(tr("Left Hand Turnout"), "LeftTurnout");//new ComboBoxItem("LeftTurnout"));
 _addIconBox->addItem(tr("Slip/3-Way Turnout/Scissor"), "SlipTOEditor");//new ComboBoxItem("SlipTOEditor"));
 _addIconBox->addItem(tr("Sensor"), "Sensor");//new ComboBoxItem("Sensor")); // NOI18N
 _addIconBox->addItem(tr("SignalHead"), "SignalHead");//new ComboBoxItem("SignalHead"));
 _addIconBox->addItem(tr("SignalMast"), "SignalMast");//new ComboBoxItem("SignalMast"));
 _addIconBox->addItem(tr("Memory"), "Memory");//new ComboBoxItem("Memory"));
 _addIconBox->addItem(tr("Block Contents Label"), "BlockLabel");//new ComboBoxItem("BlockLabel"));
 _addIconBox->addItem(tr("Reporter"), "Reporter");//new ComboBoxItem("Reporter"));
 _addIconBox->addItem(tr("Light"), "Light");//new ComboBoxItem("Light"));
 _addIconBox->addItem(tr("Background"), "Background");//new ComboBoxItem("Background"));
 _addIconBox->addItem(tr("MultiSensor"), "MultiSensor");//new ComboBoxItem("MultiSensor"));
 _addIconBox->addItem(tr("RPS Reporter"), "RPSreporter");//new ComboBoxItem("RPSreporter"));
 _addIconBox->addItem(tr("FastClock"), "FastClock");//new ComboBoxItem("FastClock"));
 _addIconBox->addItem(tr("Icon"), "Icon");//new ComboBoxItem("Icon"));
 _addIconBox->setCurrentIndex(-1);
 //_addIconBox.addItemListener(this);  // must be AFTER no selection is set
 connect(_addIconBox, SIGNAL(currentIndexChanged(int)), this, SLOT(itemStateChanged(int)));
 QWidget* p1 = new QWidget();
 p1->setLayout(new QVBoxLayout());//p1, BoxLayout.Y_AXIS));
 QWidget* p2 = new QWidget();
 p2->setLayout(new FlowLayout());
 p2->layout()->addWidget(new QLabel(tr("Select the type of icon to Add to Panel:")));
 p1->layout()->addWidget(p2);
 p1->layout()->addWidget(_addIconBox);
 contentPaneLayout->addWidget(p1);

 // edit, position, control controls
 {
     // edit mode item
     contentPane->layout()->addWidget(editableBox);
//     editableBox.addActionListener(new ActionListener() {
//         @Override
//         public void actionPerformed(ActionEvent event) {
     connect(editableBox, &QCheckBox::clicked, [=]{
             setAllEditable(editableBox->isChecked());
             hiddenCheckBoxListener();
     });
     editableBox->setChecked(isEditable());

     // positionable item
     contentPaneLayout->addWidget(positionableBox);
//     positionableBox.addActionListener(new ActionListener() {
//         @Override
//         public void actionPerformed(ActionEvent event) {
//             setAllPositionable(positionableBox.isSelected());
//         }
//     });
     connect(positionableBox, SIGNAL(clicked(bool)), this, SLOT(setAllPositionable(bool)));
     positionableBox->setChecked(allPositionable());
     // controlable item
     contentPaneLayout->addWidget(controllingBox);
//     controllingBox.addActionListener(new ActionListener() {
//         @Override
//         public void actionPerformed(ActionEvent event) {
     connect(controllingBox, &QCheckBox::clicked, [=]{
             setAllControlling(controllingBox->isChecked());
     });
     controllingBox->setChecked(allControlling());
     // hidden item
     contentPaneLayout->addWidget(hiddenBox);
     hiddenCheckBoxListener();
     hiddenBox->setChecked(showHidden());

     /*
      contentPane.add(showCoordinatesBox);
      showCoordinatesBox.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
      setShowCoordinates(showCoordinatesBox.isSelected());
      }
      });
      showCoordinatesBox.setSelected(showCoordinates());
      */
     contentPaneLayout->addWidget(showTooltipBox);
//     showTooltipBox.addActionListener(new ActionListener() {
//         @Override
//         public void actionPerformed(ActionEvent e) {
     connect(showTooltipBox, &QCheckBox::clicked, [=]{
             setAllShowToolTip(showTooltipBox->isChecked());
     });
     showTooltipBox->setChecked(showToolTip());

     contentPaneLayout->addWidget(menuBox);
//     menuBox.addActionListener(new ActionListener() {
//         @Override
//         public void actionPerformed(ActionEvent e) {
//             setPanelMenuVisible(menuBox.isSelected());
//         }
//     });
     connect(menuBox, SIGNAL(toggled(bool)), this, SLOT(setPanelMenuVisible(bool)));
     menuBox->setChecked(true);

     // Show/Hide Scroll Bars
     QWidget* scrollPanel = new QWidget();
     scrollPanel->setLayout(new FlowLayout());
//     scrollableLabel->setLabelFor(scrollableComboBox);
     scrollPanel->layout()->addWidget(scrollableLabel);
     scrollPanel->layout()->addWidget(scrollableComboBox);
     contentPaneLayout->addWidget(scrollPanel);
     scrollableComboBox->addItem(tr("No scrollbars"));
     scrollableComboBox->addItem(tr("Both scrollbars"));
     scrollableComboBox->addItem(tr("Horizontal only"));
     scrollableComboBox->addItem(tr("Vertical only"));
     scrollableComboBox->setCurrentIndex(SCROLL_BOTH);
//     scrollableComboBox->addActionListener(new ActionListener() {
//         @Override
//         public void actionPerformed(ActionEvent e) {
     connect(scrollableComboBox, &QComboBox::currentTextChanged, [=]{
             setScroll(scrollableComboBox->currentIndex());
     });
 }
 frame->setVisible(true);
 frame->pack();

 bDirty = false;
 ui->menuFile->addAction(new NewPanelAction(tr("New Panel..."),this));
 ui->menuFile->addAction(new StoreXmlUserAction(tr("Save Panels..."),this));
 QAction* storeIndexItem = new QAction(tr("Store Image Index"), this);
 ui->menuFile->addAction(storeIndexItem);

// storeIndexItem.addActionListener(new ActionListener() {
//     @Override
//     public void actionPerformed(ActionEvent event) {
 connect(storeIndexItem, &QAction::triggered, [=]{
         ImageIndexEditor::storeImageIndex();
 });
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
 connect(editItem, &QAction::triggered, [=]{
//   while ( QWidget* w = findChild<QWidget*>() )
//       delete w;("jmri.jmrit.display.controlPanelEditor.ControlPanelEditor");
   changeView("ControlPanelEditor");
 });
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
 PanelMenu* pMenu = (PanelMenu*)InstanceManager::getDefault("PanelMenu");
 ui->menuWindow->addMenu(pMenu);
// connect(ui->menuWindow, SIGNAL(aboutToShow()), this, SLOT(on_menuWindow_aboutToShow()));
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
 QMenu* warrantMenu = WarrantTableAction::getDefault()->makeWarrantMenu(isEditable());
         if (warrantMenu != nullptr) {
            ui->menuWindow->addMenu(warrantMenu);
         }

 //connect(ui->actionOpenEditor, SIGNAL(triggered()), this, SLOT(on_actionOpenEditor_triggered()));


    editPanel = new QGraphicsView(ui->centralwidget);
    ui->verticalLayout->removeWidget(ui->editPanel);
    ui->editPanel->deleteLater();
    ui->verticalLayout->addWidget(editPanel);
    editPanel->setMouseTracking(true);
    editPanel->setRenderHint(QPainter::Antialiasing);
//    panelWidth = 600;

//    panelHeight =400;
    if(editScene == nullptr)
    {
     editScene = new EditScene(QRectF(0, 0, /*panelWidth*/600, /*panelHeight*/400), this);
     //_targetPanel = editScene;
     editPanel->setScene(editScene);
    }
    connect(editScene, SIGNAL(sceneMouseMove(QGraphicsSceneMouseEvent*)), this, SLOT(mouseMoved(QGraphicsSceneMouseEvent*)));
    connect(editScene, SIGNAL(sceneMousePress(QGraphicsSceneMouseEvent*)), this, SLOT(mousePressed(QGraphicsSceneMouseEvent*)));
    connect(editScene, SIGNAL(sceneMouseRelease(QGraphicsSceneMouseEvent*)), this, SLOT(mouseReleased(QGraphicsSceneMouseEvent*)));
    connect(editScene, SIGNAL(sceneMouseRelease(QGraphicsSceneMouseEvent*)), this, SLOT(mouseClicked(QGraphicsSceneMouseEvent*)));
    connect(editScene, SIGNAL(sceneMouseMove(QGraphicsSceneMouseEvent*)), this, SLOT(mouseDragged(QGraphicsSceneMouseEvent*)));
    connect(editScene, SIGNAL(sceneDropEvent(QGraphicsSceneDragDropEvent*)), this, SLOT(sceneDropEvent(QGraphicsSceneDragDropEvent*)));

    if (_debug) log->debug("PanelEditor ctor done.");
}  // end ctor

/*public*/ void RenameActionListener::actionPerformed(/*ActionEvent e*/) {
    // prompt for name
    QString newName = JOptionPane::showInputDialog(nullptr, tr("Enter new name:"));
    if (newName == "") {
        return;  // cancelled
    }
    if (static_cast<PanelMenu*>(InstanceManager::getDefault("PanelMenu"))->isPanelNameUsed(newName)) {
        JOptionPane::showMessageDialog(nullptr, tr("Can not rename Panel with the same name as an existing panel"), tr("Panel name already exists!"),
                JOptionPane::ERROR_MESSAGE);
        return;
    }
    if (editor->getTargetPanel()->views().at(0)->window() != nullptr) {
        ((JFrame*) editor->getTargetPanel()->views().at(0)->window())->setTitle(newName);
    }
    editor->setTitle();
    static_cast<PanelMenu*>(InstanceManager::getDefault("PanelMenu"))->renameEditorPanel(editor);
}

ActionListener* RenameActionListener::init(PanelEditor* e) {
    editor = e;
    return this;
}

/**
* Initializes the hiddencheckbox and its listener.
* This has been taken out of the init, as checkbox is
* enable/disabled by the editableBox.
*/
/*private*/ void PanelEditor::hiddenCheckBoxListener(){
    setShowHidden(hiddenBox->isChecked());
    if (editableBox->isChecked()){
        hiddenBox->setEnabled(false);
        hiddenBox->setChecked(true);
    } else {
        hiddenBox->setEnabled(true);
//        hiddenBox.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                setShowHidden(hiddenBox.isSelected());
//            }
//        });
        connect(hiddenBox, SIGNAL(clicked(bool)), this, SLOT(setShowHidden(bool)));
    }
}

/**
 * After construction, initialize all the widgets to their saved config
 * settings.
 */
//@Override
/*public*/ void PanelEditor::initView() {
#if 1
    editableBox->setChecked(isEditable());
    positionableBox->setChecked(allPositionable());
    controllingBox->setChecked(allControlling());
    //showCoordinatesBox.setSelected(showCoordinates());
    showTooltipBox->setChecked(showToolTip());
    hiddenBox->setChecked(showHidden());
    menuBox->setChecked(getTargetFrame()->menuBar()->isVisible());
#endif
}
#if 0
static class ComboBoxItem {
    QString name;
    ComboBoxItem(QString n) {
        name = n;
    }
    QString getName() {
        return name;
    }
    /*public*/ QString toQString() {
        return tr(name);
    }
}

int locationX = 0;
int locationY = 0;
static final int DELTA = 20;
#endif
/*
*  itemListener for JComboBox
*/
/*public*/ void PanelEditor::itemStateChanged(int index) {
//    if (e.getStateChange() == ItemEvent.SELECTED)
 if(index >= 0)
    {
//        ComboBoxItem item = (ComboBoxItem)e.getItem();
  QString item = _addIconBox->itemData(index).toString();
        QString name = _addIconBox->itemText(index);
        JFrameItem* frame = Editor::getIconFrame(item);
        if (frame != NULL) {
            frame->getEditor()->reset();
            frame->setVisible(true);
        } else {
            if (item == ("FastClock")) {
                addClock();
            } else if (name == ("RPSreporter")) {
                addRpsReporter();
            } else {
                log->error("Unable to open Icon Editor \""+item+"\"");
            }
        }
        _addIconBox->setCurrentIndex(-1);
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
/*public*/ void PanelEditor::windowClosing(QCloseEvent* e) {
    setVisible(false);
}
#if 0
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

    QMenuBar* menuBar = new QMenuBar();
    QMenu* editMenu = new Menu(tr("MenuEdit"));
    menuBar->addMenu(editMenu);
    editMenu.add(new AbstractAction(tr("OpenEditor")) {
            /*public*/ void actionPerformed(ActionEvent e) {
                setVisible(true);
            }
        });
    editMenu.addSeparator();
    editMenu.add(new AbstractAction(tr("DeletePanel")){
            /*public*/ void actionPerformed(ActionEvent e) {
                if (deletePanel()) {
                    dispose(true);
                }
            }
        });
    targetFrame.setJMenuBar(menuBar);
    // add maker menu
    JMenu markerMenu = new JMenu(tr("MenuMarker"));
    menuBar.add(markerMenu);
    markerMenu.add(new AbstractAction(tr("AddLoco")){
        /*public*/ void actionPerformed(ActionEvent e) {
            locoMarkerFromInput();
        }
    });
    markerMenu.add(new AbstractAction(tr("AddLocoRoster")){
        /*public*/ void actionPerformed(ActionEvent e) {
            locoMarkerFromRoster();
        }
    });
    markerMenu.add(new AbstractAction(tr("RemoveMarkers")){
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
 if(qobject_cast<PositionableLabel*>(pc->self())!= NULL)
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
   if(qobject_cast<SensorIcon*>(pc->self())!= NULL)
    popup->addAction(new QAction(((SensorIcon*)p)->getNameString(),this));
   else
   if(qobject_cast<LightIcon*>(pc->self())!= NULL)
    popup->addAction(new QAction(((LightIcon*)p)->getNameString(),this));
   else
   if(qobject_cast<TurnoutIcon*>(pc->self())!= NULL)
    popup->addAction(new QAction(((TurnoutIcon*)p)->getNameString(),this));
   else
   if(qobject_cast<ReporterIcon*>(pc->self())!= NULL)
    popup->addAction(new QAction(((ReporterIcon*)p)->getNameString(),this));
   else
   if(qobject_cast<AnalogClock2Display*>(pc->self())!= NULL)
    popup->addAction(new QAction(((AnalogClock2Display*)p)->getNameString(),this));
   else
   if(qobject_cast<SignalHeadIcon*>(pc->self())!= NULL)
    popup->addAction(new QAction(((SignalHeadIcon*)p)->getNameString(),this));
   else
   if(qobject_cast<SignalMastIcon*>(pc->self())!= NULL)
    popup->addAction(new QAction(((SignalMastIcon*)p)->getNameString(),this));
   else
   if(qobject_cast<MultiSensorIcon*>(pc->self())!= NULL)
    popup->addAction(new QAction(((MultiSensorIcon*)p)->getNameString(),this));
   else
   if(qobject_cast<SlipTurnoutIcon*>(pc->self())!= NULL)
    popup->addAction(new QAction(((SlipTurnoutIcon*)p)->getNameString(),this));
   else
   if(qobject_cast<PositionableLabel*>(pc->self())!= NULL)
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
 bool bLefttButton = ((event->buttons())&Qt::LeftButton)==Qt::LeftButton;
 bool bMiddleButton = ((event->buttons())&Qt::MiddleButton)==Qt::MiddleButton;
 bool bShift = ((event->modifiers())&Qt::ShiftModifier) == Qt::ShiftModifier;
 bool bMeta = ((event->modifiers())&Qt::MetaModifier) == Qt::MetaModifier;
 bool bAlt = ((event->modifiers())&Qt::AltModifier) == Qt::AltModifier;
 bool bCtrl = ((event->modifiers())&Qt::ControlModifier) == Qt::ControlModifier;

 //setToolTip(NULL); // ends tooltip if displayed
 if (_debug)
  log->debug("mousePressed at ("+QString("%1").arg(event->scenePos().x())+","+QString("%1").arg(event->scenePos().y())+") _dragging="+(_dragging?"true":"false") + " right button="+(bRightButton?"Down":"up"));
 _anchorX = event->scenePos().x();
 _anchorY = event->scenePos().y();
 _lastX = _anchorX;
 _lastY = _anchorY;
 QList <Positionable*>* selections = getSelectedItems(event);
 if (_dragging)
 {
  return;
 }
 if (selections->size() > 0)
 {
  if (bShift && selections->size() > 1)
  {
   _currentSelection = selections->at(1);
  }
  else
  {
   _currentSelection = selections->at(0);
  }
  if (bRightButton) //isPopupTrigger()
  {
   if (_debug) log->debug("mousePressed calls showPopUp");
   if ( (bMeta || bAlt ))
   {
    // if requesting a popup and it might conflict with moving, delay the request to mouseReleased
    delayedPopupTrigger = true;
   }
   else
   {
    // no possible conflict with moving, display the popup now
    if (_selectionGroup!=NULL)
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
   if(dynamic_cast<AnalogClock2Display*>(_currentSelection->self())!=NULL)
    _currentSelection->doMousePressed(event);
   else
   if(dynamic_cast<SensorIcon*>(_currentSelection->self())!=NULL)
    ((SensorIcon*)_currentSelection->self())->doMousePressed(event);
   else
   if(dynamic_cast<LightIcon*>(_currentSelection->self())!=NULL)
    ((LightIcon*)_currentSelection->self())->doMousePressed(event);
   else
   if(dynamic_cast<SignalHeadIcon*>(_currentSelection->self())!=NULL)
    ((SignalHeadIcon*)_currentSelection->self())->doMousePressed(event);
   else
   if(dynamic_cast<SignalMastIcon*>(_currentSelection->self())!=NULL)
    ((SignalMastIcon*)_currentSelection->self())->doMousePressed(event);
   else
   if(dynamic_cast<MultiSensorIcon*>(_currentSelection->self())!=NULL)
    ((MultiSensorIcon*)_currentSelection->self())->doMousePressed(event);
   else
    ((PositionableLabel*)_currentSelection->self())->doMousePressed(event);
   if (_multiItemCopyGroup!=NULL && !_multiItemCopyGroup->contains(_currentSelection))
    _multiItemCopyGroup = NULL;
//    _selectionGroup = NULL;
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
    else if (_selectionGroup!=NULL && !_selectionGroup->isEmpty())
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
  _selectionGroup = nullptr;
 }
 else
 {
  _selectRect = QRect();
  _selectionGroup = nullptr;
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
 QList <Positionable*>* selections = getSelectedItems(event);

 if (_dragging)
 {
  //mouseDragged(event);
  delayedPopupTrigger = false;
  _dragging = false;
  _selectRect = QRect();
  _currentSelection = nullptr;
  return;
 }
 if (selections->size() > 0)
 {
  if (bShift && selections->size() > 1)
  {
   _currentSelection = selections->at(1);
  }
  else
  {
    _currentSelection = selections->at(0);
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
  if (_selectionGroup!=NULL)
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
   if(qobject_cast<SensorIcon*>(_currentSelection->self())!=NULL)
    ((SensorIcon*)_currentSelection->self())->doMouseReleased(event);
   else
   if(qobject_cast<PositionableJComponent*>(_currentSelection->self())!=NULL)
    ((PositionableJComponent*)_currentSelection->self())->doMouseReleased(event);
   else
   ((PositionableLabel*)_currentSelection->self())->doMouseReleased(event);
   addToTarget(_currentSelection);
  }
  _currentSelection = NULL; // Added to prevent calls to updateScene ACK 10-13-15
  if (allPositionable() && !_selectRect.isNull())
  {
   if (_selectionGroup==NULL && _dragging)
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
 paint(editScene);

}

/*public*/ void PanelEditor::mouseDragged(QGraphicsSceneMouseEvent* event)
{
 bool bRightButton = ((event->buttons())&Qt::RightButton)==Qt::RightButton;
 bool bLeftButton = ((event->buttons())&Qt::LeftButton)==Qt::LeftButton;
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
   QList <Positionable*>* selections = getSelectedItems(event);
   if (selections->size() > 0)
   {
    if (selections->at(0)!=_currentSelection)
    {
     _currentSelection->doMouseReleased(event);
    }
   }
   else
   {
    _currentSelection->doMouseReleased(event);
   }
  }
  //return;
 }

//moveIt:
 if (_currentSelection!=NULL && getFlag(OPTION_POSITION, _currentSelection->isPositionable()) && bLeftButton)
 {
  int deltaX = event->scenePos().x() - _lastX;
  int deltaY = event->scenePos().y() - _lastY;
  int minX = getItemX(_currentSelection, deltaX);
  int minY = getItemY(_currentSelection, deltaY);
  if (_selectionGroup!=NULL && _selectionGroup->contains(_currentSelection))
  {
   for (int i=0; i<_selectionGroup->size(); i++)
   {
    minX = qMin(getItemX(_selectionGroup->at(i), deltaX), minX);
    minY = qMin(getItemY(_selectionGroup->at(i), deltaY), minY);
   }
  }
  if (minX<0 || minY<0 /*|| !bRightButton*/)
  {
    //break moveIt;
    goto moveIt2;
  }
  if (_selectionGroup!=NULL && _selectionGroup->contains(_currentSelection))
  {
   for (int i=0; i<_selectionGroup->size(); i++)
   {
     moveItem(_selectionGroup->at(i), deltaX, deltaY);
   }
   _highlightcomponent = QRectF();
  }
  else
  {
   moveItem(_currentSelection, deltaX, deltaY);
   if(qobject_cast<LightIcon*>(_currentSelection->self())!=NULL)
   {
    _highlightcomponent =  QRectF(_currentSelection->getX(), _currentSelection->getY(),((LightIcon*)_currentSelection->self())->maxWidth(), ((LightIcon*)_currentSelection->self())->maxHeight());
   }
   else
   if(qobject_cast<PositionableLabel*>(_currentSelection->self())!=NULL)
   {
    //_highlightcomponent =  QRect(((PositionableLabel*)_currentSelection)->getX(),((PositionableLabel*) _currentSelection)->getY(),((PositionableLabel*)_currentSelection)->maxWidth(), ((PositionableLabel*)_currentSelection)->maxHeight());
    _highlightcomponent = ((PositionableLabel*) _currentSelection->self())->getBounds();
   }
//   else
//   _highlightcomponent =  QRect(_currentSelection->getX(), _currentSelection->getY(),
//                                                 _currentSelection->maxWidth(), _currentSelection->maxHeight());
  }
 }
 else
 {
  if (allPositionable() && _selectionGroup==NULL && bRightButton)
  {
   drawSelectRect(event->scenePos().x(), event->scenePos().y());
   paint(editScene);
   return;
  }
 }
 moveIt2:
 //if(bRightButton)
  _dragging = true;
 delayedPopupTrigger = false;
 _lastX = event->scenePos().x();
 _lastY = event->scenePos().y();
 //_targetPanel.repaint(); // needed for ToolTip
 //paint(_targetPanel);
 if(_currentSelection != NULL)
 {
   _currentSelection->updateScene();
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
 QString msg = tr("mouseMoved at (%1,%2)").arg(event->scenePos().x()).arg(event->scenePos().y());
 if(_currentSelection)
  msg += tr(" selected: %1").arg(_currentSelection->self()->metaObject()->className());
 ui->statusbar->showMessage(msg);
 if (_dragging || bRightButton)
  return;

 QList <Positionable*>* selections = getSelectedItems(event);
 Positionable* selection = NULL;
 if (selections->size() > 0)
 {
  if (bShift && selections->size() > 1)
  {
    selection = selections->at(1);
  }
  else
  {
   selection = selections->at(0);
  }
 }
 if (isEditable() && selection!=NULL && qobject_cast<PositionableLabel*>(selection->self()) && ((PositionableLabel*)selection->self())->getDisplayLevel()>BKG)
 {
  //_highlightcomponent = QRectF(((PositionableLabel*)selection)->getX(), ((PositionableLabel*)selection)->getY(), ((PositionableLabel*)selection)->maxWidth(), ((PositionableLabel*)selection)->maxHeight());
  _highlightcomponent = ((PositionableLabel*)selection->self())->getBounds();
  //_targetPanel->repaint();
  paint(editScene);
 }
 else
 {
  _highlightcomponent = QRectF();
  //_targetPanel->repaint();
  paint(editScene);
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
 QList <Positionable*>* selections = getSelectedItems(event);

 if (selections->size() > 0)
 {
  if (bShift && selections->size() > 1)
  {
    _currentSelection = selections->at(1);
  }
  else
  {
   _currentSelection = selections->at(0);
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
  if (_selectionGroup!=NULL)
   showMultiSelectPopUp(event, _currentSelection);
  else
   showPopUp(_currentSelection, event);
  //_selectionGroup = NULL; //Show popup only works for a single item

 }
 else
 {
  if (_currentSelection != NULL && !_dragging && !bCtrl)
  {
   if(qobject_cast<AnalogClock2Display*>(_currentSelection->self())!=NULL)
    (_currentSelection)->doMouseClicked(event);
   else
   if(qobject_cast<LightIcon*>(_currentSelection->self())!=NULL)
    ((LightIcon*)_currentSelection)->doMouseClicked(event);
   else
   if(qobject_cast<SensorIcon*>(_currentSelection->self())!=NULL)
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
 _multiItemCopyGroup = new QList <Positionable*>();
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
 if(p == NULL)
  return;
 //if (((PositionableLabel*)p)->isPositionable())
 if(p->isPositionable())
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

    setMultiItemsPositionableMenu(popup); // adding Lock Position for all
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
 QMenu* _add = new QMenu("Add Item"/*tr("FontBackgroundColor")*/);
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

 QAction* addLcdClockAct = new QAction(tr("Lcd clock"),this);
 connect(addLcdClockAct, SIGNAL(triggered()), this, SLOT(on_addLcdClock_triggered()));
 _add->addAction(addLcdClockAct);//    addItemPopUp(new ComboBoxItem("Icon"),_add);

 QAction* addNixieClockAct = new QAction(tr("Nixie clock"),this);
 connect(addNixieClockAct, SIGNAL(triggered()), this, SLOT(on_addNixieClockAct_triggered()));
 _add->addAction(addNixieClockAct);//    addItemPopUp(new ComboBoxItem("Icon"),_add);

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
  ((Positionable*)l)->setLocation(_lastX, _lastY);
 }
}

/*private*/ void PanelEditor::amendSelectionGroup(Positionable* p)
{
 if (p==NULL) return;
 if (_selectionGroup==NULL)
 {
   _selectionGroup = new QList <Positionable*>();
 }
 bool removed = false;
 for(int i=0; i<_selectionGroup->size();i++)
 {
  if (_selectionGroup->at(i)==p)
  {
   _selectionGroup->removeAt(i);
   removed = true;
   break;
  }
 }
 if(!removed)
  _selectionGroup->append(p);
 else if (removed && _selectionGroup->isEmpty())
  _selectionGroup= new QList<Positionable*>();
//_targetPanel.repaint();
}


/*protected*/ void PanelEditor::pasteItem(QGraphicsSceneMouseEvent* e)
{
 //QGraphicsSceneMouseEvent* e = saveEvent;
 pasteItemFlag = true;
 XmlAdapter* adapter;
 QString className;
 int x;
 int y;
 int xOrig;
 int yOrig;
 if (_multiItemCopyGroup!=NULL)
 {
#if 1 // TODO:
        Positionable* copied;
        int xoffset;
        int yoffset;
        x = _multiItemCopyGroup->at(0)->getX();
        y = _multiItemCopyGroup->at(0)->getY();
        xoffset=e->pos().x()-x;
        yoffset=e->pos().y()-y;
        /*We make a copy of the selected items and work off of that copy
        as amendments are made to the multiItemCopyGroup during this process
        which can result in a loop*/
        QList <Positionable*> _copyOfMultiItemCopyGroup =  QList<Positionable*>(/*_multiItemCopyGroup*/);
        //Collections.copy(_copyOfMultiItemCopyGroup, _multiItemCopyGroup);
        foreach(Positionable* pos, *_multiItemCopyGroup)
         _copyOfMultiItemCopyGroup.append(pos);
        for(int i = 0; i<_copyOfMultiItemCopyGroup.size(); i++){
            copied = (Positionable*)_copyOfMultiItemCopyGroup.at(i);
            xOrig = copied->getX();
            yOrig = copied->getY();
            x = xOrig+xoffset;
            y = yOrig+yoffset;
            if (x<0) x=1;
            if (y<0) y=1;
            className=ConfigXmlManager::adapterName(copied->self());
            copied->setLocation(x, y);
            try{
                adapter = (XmlAdapter*)Class::forName(className)->newInstance();
                QDomElement el = adapter->store(copied->self());
                adapter->load(el, this);
            } catch (Exception ex) {
                log->debug(ex.getMessage());
            }
            /*We remove the original item from the list, so we end up with
            just the new items selected and allow the items to be moved around */
            amendSelectionGroup(_copyOfMultiItemCopyGroup.at(i));
            copied->setLocation(xOrig, yOrig);
#endif
        }
  }
  _selectionGroup=NULL;
 pasteItemFlag = false;
 //_targetPanel->repaint();
}
#if 1
/**
* Add an action to remove the Positionable item.
*/
/*public*/ void PanelEditor::setRemoveMenu(Positionable* p, QMenu* popup) {
 RemoveMenuAction* act;
    popup->addAction(act = new RemoveMenuAction(tr("Remove"), this));
//    {
//        Positionable comp;
//        /*public*/ void actionPerformed(ActionEvent e) {
//            if (_selectionGroup==NULL)
//                comp.remove();
//            else
//                removeMultiItems();
//        }
//        AbstractAction init(Positionable pos) {
//            comp = pos;
//            return this;
//        }
//    }.init(p));
    act->init(p);
}
 RemoveMenuAction::RemoveMenuAction(QString title, PanelEditor *parent) : AbstractAction(title, parent)
 {
  this->parent = parent;
  connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }

 void RemoveMenuAction::actionPerformed()
 {
  if (parent->_selectionGroup==NULL)
      comp->remove();
  else
      parent->removeMultiItems();

 }
 AbstractAction* RemoveMenuAction::init(Positionable *pos)
 {
  comp = pos;
  return this;
 }

/*private*/ void PanelEditor::removeMultiItems(){
    bool itemsInCopy = false;
    if (_selectionGroup== _multiItemCopyGroup){
        itemsInCopy=true;
    }
    for (int i=0; i<_selectionGroup->size(); i++) {
        Positionable* comp = _selectionGroup->at(i);
        comp->remove();
    }
    //As we have removed all the items from the panel we can remove the group.
    _selectionGroup = nullptr;
    //If the items in the selection group and copy group are the same we need to
    //clear the copy group as the originals no longer exist.
    if (itemsInCopy)
        _multiItemCopyGroup = nullptr;
}

// This adds a single CheckBox in the PopupMenu to set or clear all the selected
// items "Lock Position" or Positionable setting, when clicked, all the items in
// the selection will be changed accordingly.
/*private*/ void PanelEditor::setMultiItemsPositionableMenu(QMenu* popup) {
    // This would do great with a "greyed" CheckBox if the multiple items have different states.
    // Then selecting the true or false state would force all to change to true or false

    QAction* lockItem = new QAction(tr("Lock Position"));
    lockItem->setCheckable(true);
    bool allSetToMove = false;  // used to decide the state of the checkbox shown
    int trues = 0;                 // used to see if all items have the same setting

    int size = _selectionGroup->size();

    for (int i = 0; i < size; i++) {
        Positionable* comp = _selectionGroup->at(i);

        if (!comp->isPositionable()) {
            allSetToMove = true;
            trues++;
        }

        lockItem->setChecked(allSetToMove );

//        lockItem.addActionListener(new ActionListener() {
//            Positionable* comp;
//            JCheckBoxMenuItem checkBox;

//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                comp.setPositionable(!checkBox.isSelected());
//                setSelectionsPositionable(!checkBox.isSelected(), comp);
//            }

//            ActionListener init(Positionable pos, JCheckBoxMenuItem cb) {
//                comp = pos;
//                checkBox = cb;
//                return this;
//            }
//        }.init(comp, lockItem));
        LockItemListener* listener = new LockItemListener(this);
        listener->init(comp, lockItem);
    }

    // Add "~" to the Text when all items do not have the same setting,
    // until we get a "greyed" CheckBox ;) - GJM
    if ((trues != size) && (trues != 0)) {
        lockItem->setText("~ "+lockItem->text());
        // uncheck box if all not the same
        lockItem->setChecked(false );
    }
    popup->addAction(lockItem);
}
#endif

 LockItemListener::LockItemListener(PanelEditor *editor)
 {
  this->editor = editor;
 }

 void LockItemListener::actionPerformed()
 {
   comp->setPositionable(!checkBox->isChecked());
   editor->setSelectionsPositionable(!checkBox->isChecked(), comp);
 }

 ActionListener* LockItemListener::init(Positionable *pos, QAction *cb)
 {
  comp = pos;
  checkBox = cb;
  return this;
 }

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
  l->_itemGroup = new MyGraphicsItemGroup();
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
   item->setPos(((Positionable*)l)->getX(), ((Positionable*)l)->getY());
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
    item->setPos(((Positionable*)l)->getX(), ((Positionable*)l)->getY());
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
    item->setPos(((Positionable*)l)->getX(), ((Positionable*)l)->getY());
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
     pixmap = QPixmap::fromImage(((JLabel*)l)->getIcon()->getImage());
     if(pixmap.isNull())
      log->debug(QString("LocoIcon null pixmap: %1").arg(((JLabel*)l)->getIcon()->getDescription()));
     QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap);
     item->setPos(((Positionable*)l)->getX(), ((Positionable*)l)->getY());
     l->_itemGroup->addToGroup(item);
     //g2->addItem(l->item);
    }
    else
    {
     QGraphicsTextItem* item = new QGraphicsTextItem(l->getUnRotatedText());
     item->setPos(((Positionable*)l)->getX(), ((Positionable*)l)->getY());
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
     item->setPos(((Positionable*)l)->getX(), ((Positionable*)l)->getY());
     if(pixmap.isNull())
      log->debug( "No pixmap "+ ((PositionableLabel*)l)->getIcon()->getURL());
     m->_itemGroup->addToGroup(item);
    }
    else
    {

     //m->item = g2->addText("????");
     QGraphicsTextItem* item = new QGraphicsTextItem("????");
     m->_itemGroup->addToGroup(item);
     item->setPos(((Positionable*)l)->getX(), ((Positionable*)l)->getY());
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
   item->setPos(((Positionable*)l)->getX(), ((Positionable*)l)->getY());
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
 ((PositionableIcon*)l)->setOpaque(false);
 l->update();
 ((PositionableIcon*)l)->setDisplayLevel(CLOCK);
//    setNextLocation(l);
 ((PositionableJComponent*)l)->setLocation(_lastX, _lastY);
 ((PositionableIcon*)l)->setVisible(true);
 ((PositionableIcon*)l)->setScale(1.0);
 putItem((PositionableIcon*)l);
 l->paint(editScene);
}

void PanelEditor::on_addLcdClock_triggered()
{
 addItemViaMouseClick = true;
 LcdClockFrame* l = new LcdClockFrame(this);
 l->setOpaque(false);
 l->update();
 ((PositionableIcon*)l)->setDisplayLevel(CLOCK);
//    setNextLocation(l);
 l->setLocation(_lastX, _lastY);
 l->setVisible(true);
 ((PositionableIcon*)l)->setScale(1.0);
 putItem((Positionable*)l);
 ((PositionableIcon*)l)->paint(editScene);
}

void PanelEditor::on_addNixieClockAct_triggered()
{
 addItemViaMouseClick = true;
 NixieClockFrame* l = new NixieClockFrame(this);
 l->setOpaque(false);
 l->update();
 ((PositionableIcon*)l)->setDisplayLevel(CLOCK);
//    setNextLocation(l);
 l->setLocation(_lastX, _lastY);
 l->setVisible(true);
 ((PositionableIcon*)l)->setScale(1.0);
 putItem((Positionable*)l);
 ((PositionableIcon*)l)->paint(editScene);
}

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
 if(addTextLabelDlg == nullptr)
  addTextLabelDlg = new InputDialog("Enter text, then press OK","",nullptr,this);
 if(addTextLabelDlg->exec() == QDialog::Accepted)
 {
  PositionableLabel* label = new PositionableLabel(addTextLabelDlg->value(),this);
  ((Positionable*)label)->setLocation(pt.x(), pt.y());
  putItem((Positionable*)label);
 }
 addTextLabelDlg=nullptr;
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
//void PanelEditor::on_menuWindow_aboutToShow()
//{
// //ui->menuWindow->clear();
// PanelMenu::instance()->updatePanelMenu(ui->menuWindow);
//}
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
 if(addTextLabelDlg != nullptr)
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

/*public*/ QString PanelEditor::getClassName()
{
 return "jmri.jmrit.display.panelEditor.PanelEditor";
}
