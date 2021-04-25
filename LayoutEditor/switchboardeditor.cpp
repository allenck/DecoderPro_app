#include "switchboardeditor.h"
#include "loggerfactory.h"
#include <QMenuBar>
#include <QMenu>
#include "imageicon.h"
#include <QLabel>
#include "jlabel.h"
#include <QSpinBox>
#include <QCheckBox>
#include "flowlayout.h"
#include "jpanel.h"
#include "jlabel.h"
#include <QComboBox>
#include "proxyturnoutmanager.h"
#include "instancemanager.h"
//#include "jtextarea.h"
#include "connectionnamefromsystemname.h"
#include <QStringList>
#include "newpanelaction.h"
#include "storexmluseraction.h"
#include <QGroupBox>
#include "editscene.h"
#include <QGraphicsView>
#include <QCheckBox>
#include "editor.h"
#include "defaultcatalogtreemanager.h"
#include "namedbeanhandlemanager.h"
#include "beanswitch.h"
#include "colorutil.h"
#include "jmricolorchooser.h"
#include "abstractaction.h"
#include "box.h"
#include "positionablejcomponent.h"
#include "coordinateedit.h"
#include "borderfactory.h"
#include <QGridLayout>
#include "configuremanager.h"
#include <QActionGroup>
#include "joptionpane.h"
#include <QColor>
#include "proxymanager.h"
/**
 * Provides a simple editor for adding jmri.jmrit.display.switchBoard items to a
 * JLayeredPane inside a captive JFrame. Primary use is for new users.
 * <p>
 * GUI is structured as a separate setup panel to set the visible range and type
 * plus menus.
 * <p>
 * All created objects are put insite a GridLayout grid. No special use of the
 * LayeredPane layers. Inspired by Oracle JLayeredPane demo.
 * <p>
 * The "switchlist" List keeps track of all the objects added to the target
 * frame for later manipulation. May be used in an update to store mixed
 * switchboards with more than 1 connection and more than 1 bean type/range.
 * <p>
 * No DnD as panels will be automatically populated in order of the DCC address.
 * New beans may be created from the Switchboard by right clicking an
 * unconnected switch.
 *
 * @author Pete Cressman Copyright (c) 2009, 2010, 2011
 * @author Egbert Broerse Copyright (c) 2017, 2018
 *
 */
// /*public*/ class SwitchboardEditor extends Editor {

/*static*/ /*final*/ QString SwitchboardEditor::TURNOUT = tr("Turnout");
/*static*/ /*final*/ QString SwitchboardEditor::SENSOR = tr("Sensor");
/*static*/ /*final*/ QString SwitchboardEditor::LIGHT = tr("Light");
/*private*/ /*static*/ QString SwitchboardEditor::LAYER_COMMAND = "layer";
/*private*/ /*static*/ QString SwitchboardEditor::MANU_COMMAND = "manufacturer";
/*private*/ /*static*/ QString SwitchboardEditor::SWITCHTYPE_COMMAND = "switchshape";

/**
 * Ctor
 */
/*public*/ SwitchboardEditor::SwitchboardEditor(QWidget* parent) : Editor(parent){
 common();
}

/**
 * Ctor by a given name.
 *
 * @param name title to assign to the new SwitchBoard
 */
/*public*/ SwitchboardEditor::SwitchboardEditor(QString name, QWidget* parent) : Editor(name, false, true, parent){
    //super(name, false, true);
    common();
    init(name);
}

/*public*/ SwitchboardEditor::~SwitchboardEditor()
{

}

/*private*/ void SwitchboardEditor::common()
{
 setObjectName("SwitchboardEditor");
 panelChanged = false;
 navBarPanel = nullptr;
 iconPrev = new ImageIcon(":resources/icons/misc/gui3/LafLeftArrow_m.gif");
 prev = new JLabel(iconPrev);
 iconNext = new ImageIcon(":resources/icons/misc/gui3/LafRightArrow_m.gif");
 next = new JLabel(iconNext);
 rangeMin = 1;
 rangeMax = 24;
 _range = rangeMax - rangeMin;
 minSpinner = new QSpinBox(/*new SpinnerNumberModel(rangeMin, rangeMin, rangeMax, 1)*/);
 minSpinner->setMinimum(rangeMin);
 minSpinner->setMaximum(rangeMax);
 minSpinner->setSingleStep(1);
 minSpinner->setValue(rangeMin);
 maxSpinner = new QSpinBox(/*new SpinnerNumberModel(rangeMax, rangeMin, rangeMax, 1)*/);
 maxSpinner->setMinimum(rangeMin);
 maxSpinner->setMaximum(rangeMax);
 maxSpinner->setSingleStep(1);
 maxSpinner->setValue(rangeMax);
 hideUnconnectedBox = new QAction(tr("Hide unconnected switches"),this);
 // /*private*/ TargetPane switchboardLayeredPane; // JLayeredPane
 beanTypeStrings = QStringList() <<TURNOUT << SENSOR <<LIGHT;
 columns = new QSpinBox(/*new SpinnerNumberModel(8, 1, 16, 1)*/);
 columns->setMinimum(1);
 columns->setMaximum(16);
 columns->setSingleStep(1);
 columns->setValue(8);
 switchShapeStrings = QStringList() <<
     tr("Buttons") <<
     tr("Sliders") <<
     tr("Keys") <<
     tr("Symbols");
 beanManuPrefixes = QStringList();
 interact = tr("Click to toggle state");
 noInteract = tr("Follows layout, no control");
 editToolBarPanel = nullptr;
 editToolBarScroll = nullptr;
 editorContainer = nullptr;
 defaultTextColor = QColor(Qt::black);
 hideUnconnected = new QCheckBox(tr("Hide unconnected switches"));
 help2 = new JTextArea(tr("Greyed out buttons are not connected to layout."));
 controllingBox = new QAction(tr("Panel items control layout"),this);
 controllingBox->setCheckable(true);
 hideUnconnectedBox->setCheckable(true);
 showToolTipBox = new QAction(tr("Show Tooltips for all items"),this);
 showToolTipBox->setCheckable(true);
 switchlist = QStringList();
 _switches = QList<BeanSwitch*>();
 thisLayout = nullptr;
 _editorMenu = nullptr;
 scrollBoth = new QAction(tr("Both"));
 scrollBoth->setCheckable(true);
 scrollNone = new QAction(tr("None"));
 scrollNone->setCheckable(true);
 scrollHorizontal = new QAction(tr("Horizontal"));
 scrollHorizontal->setCheckable(true);
 scrollVertical = new QAction(tr("Vertical"));
 scrollVertical->setCheckable(true);
 setFrameRef("SwitchboardEditor");
}
/**
 * Initialize the newly created SwitchBoard.
 *
 * @param name the title of the switchboard content frame
 */
//@SuppressWarnings("unchecked") // AbstractProxyManager of the right type is type-safe by definition
//@Override
/*protected*/ void SwitchboardEditor::init(QString name) {
    QWidget* contentPane = getContentPane(); // Editor
    //contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.Y_AXIS));
    thisLayout = new QVBoxLayout(contentPane);
    setVisible(false); // start with Editor window hidden
    setFrameLocation();

    // make menus
    setUseGlobalFlag(true); // allways true for a SwitchBoard
    _menuBar = new QMenuBar();
    makeOptionMenu();
    //makeEditMenu();
    makeFileMenu();
    setMenuBar(_menuBar);
    addHelpMenu("package.jmri.jmrit.display.SwitchboardEditor", true);

    switchboardLayeredPane = new TargetPane(); // extends JLayeredPane();

    switchboardLayeredPane->resize(QSize(300, 310));
    _targetPanel = switchboardLayeredPane;
#if 0
    border = BorderFactory::createTitledBorder(
            BorderFactory::createLineBorder(defaultTextColor),
            "temp",
            TitledBorder::LEADING,
            TitledBorder::ABOVE_BOTTOM,
            font(),
            defaultTextColor);
    switchboardLayeredPane.setBorder(border);
    // create contrast with background, should also specify border style
    // specify title for turnout, sensor, light, mixed? (wait for the Editor to be created)
    switchboardLayeredPane.addMouseMotionListener(this);
#endif
    border = new QGroupBox();
    QVBoxLayout* borderLayout = new QVBoxLayout(border);

    //borderLayout->addWidget(/*editPanel*/switchboardLayeredPane);

    // add control pane and layered pane to this JPanel
    JPanel* beanSetupPane = new JPanel();
    FlowLayout* beanSetupPaneLayout;
    beanSetupPane->setLayout(beanSetupPaneLayout =new FlowLayout(/*FlowLayout.TRAILING*/));
    QLabel* beanTypeTitle = new QLabel(tr("%1").arg(tr("Label")));
    beanSetupPaneLayout->addWidget(beanTypeTitle);
    beanTypeList = new QComboBox(/*beanTypeStrings*/);
    beanTypeList->addItems(beanTypeStrings);
    beanTypeList->setCurrentIndex(0); // select bean type in comboBox
    //beanTypeList.setActionCommand(LAYER_COMMAND);
    //beanTypeList.addActionListener(this);
    //connect(beanTypeList, SIGNAL(currentIndexChanged(int)),  this, SLOT());
    beanSetupPaneLayout->addWidget(beanTypeList);

    // add connection selection comboBox
    beanTypeChar = getSwitchType().at(0); // translate from selectedIndex to char
    log->debug(tr("beanTypeChar set to [%1]").arg(beanTypeChar));
    QLabel* beanManuTitle = new QLabel(tr("%1").arg(tr("Label")));
    beanSetupPaneLayout->addWidget(beanManuTitle);
    beanManuNames = new QComboBox();
    if (qobject_cast<ProxyManager*>(getManager(beanTypeChar)->self())!= nullptr)
    { // from abstractTableTabAction
        ProxyManager* proxy = qobject_cast<ProxyManager*>(getManager(beanTypeChar)->self());
        QList<AbstractManager*> managerList = proxy->getManagerList(); // picks up all managers to fetch
        for (int x = 0; x < managerList.size(); x++) {
            QString manuPrefix = managerList.value(x)->getSystemPrefix();
            log->debug(tr("Prefix = [%1]").arg(manuPrefix));
            QString manuName = ConnectionNameFromSystemName::getConnectionName(manuPrefix);
            log->debug(tr("Connection name = [%1]").arg(manuName));
            beanManuNames->addItem(manuName); // add to comboBox
            beanManuPrefixes.append(manuPrefix); // add to list
        }
    } else {
        QString manuPrefix = getManager(beanTypeChar)->getSystemPrefix();
        QString manuName = ConnectionNameFromSystemName::getConnectionName(manuPrefix);
        beanManuNames->addItem(manuName);
        beanManuPrefixes.append(manuPrefix); // add to list (as only item)
    }
    beanManuNames->setCurrentIndex(0);
//    beanManuNames.setActionCommand(MANU_COMMAND);
//    beanManuNames.addActionListener(this);
    beanSetupPaneLayout->addWidget(beanManuNames);
    thisLayout->addWidget(beanSetupPane);

    // add shape combobox
    QWidget* switchShapePane = new JPanel();
    FlowLayout* switchShapePaneLayout;
    switchShapePane->setLayout(switchShapePaneLayout =new FlowLayout(/*FlowLayout.TRAILING)*/));
    QLabel* switchShapeTitle = new QLabel(tr("%1").arg(tr("Switch shape")));
    switchShapePaneLayout->addWidget(switchShapeTitle);
    switchShapeList = new QComboBox(/*switchShapeStrings*/);
    switchShapeList->addItems(switchShapeStrings);
    switchShapeList->setCurrentIndex(0); // select Button in comboBox
    switchShapeList->setCurrentText(SWITCHTYPE_COMMAND);
//    switchShapeList.addActionListener(this);
    switchShapePaneLayout->addWidget(switchShapeList);
    // add column spinner
    QLabel* columnLabel = new QLabel(tr("Switches per row:"));
    switchShapePaneLayout->addWidget(columnLabel);
    switchShapePaneLayout->addWidget(columns);
    thisLayout->addWidget(switchShapePane);

    // checkbox on panel
    hideUnconnected->setChecked(getHideUnconnected());
    log->debug(tr("hideUnconectedBox set to %1").arg(hideUnconnectedBox->isChecked()));
    //hideUnconnectedBox.addActionListener((ActionEvent event) -> {
//        setHideUnconnected(hideUnconnected.isSelected());
//        hideUnconnectedBox.setSelected(hideUnconnected()); // also (un)check the box on the menu
//        help2.setVisible(!hideUnconnected()); // and show/hide instruction line
    //});
    connect(hideUnconnected, SIGNAL(toggled(bool)), this, SLOT(onHideUnconnected(bool)));
    connect(hideUnconnectedBox, SIGNAL(toggled(bool)), this, SLOT(onHideUnConnectedBox(bool)));
    thisLayout->addWidget(hideUnconnected);


    switchboardLayeredPane->setLayout(switchboardLayeredPaneLayout = new QGridLayout(/*3, 8)*/)); // initial layout params
    currCol = 0;
    currRow = 0;


    // TODO do some calculation from JPanel size, icon size and determine optimal cols/rows
    // Add at least 1 switch to pane to create switchList:
    addSwitchRange(1, 24,
            beanTypeList->currentIndex(),
            beanManuPrefixes.value(beanManuNames->currentIndex()),
            switchShapeList->currentIndex());

    // provide a JLayeredPane to place the switches on
    //Editor::setTargetPanel(contentPane, makeFrame(name));
    JmriJFrame* frame = makeFrame(name + " " + tr("Editor"));
    scrollArea = new QScrollArea();
    frame->setCentralWidget(scrollArea);
    scrollArea->setWidget(switchboardLayeredPane);
    scrollArea->setWidgetResizable(true);
    //Editor::getTargetFrame()->resize(550, 330); // width x height
    frame->resize(550, 330);
    // TODO: Add component listener to handle frame resizing event
    // set scrollbar initial state
    setScroll(SCROLL_NONE);
    scrollNone->setChecked(true);
//    Editor::setDefaultToolTip(new ToolTip(null, 0, 0, new Font("Serif", Font.PLAIN, 12),
//            Color.black, new Color(255, 250, 210), Color.black));

    // register the resulting panel for later configuration
    ConfigureManager* cm = static_cast<ConfigureManager*>(InstanceManager::getNullableDefault("ConfigureManager"));
    if (cm != nullptr) {
        cm->registerUser(this);
    }
    thisLayout->addWidget(createControlPanel());

    JPanel* updatePanel = new JPanel();
    FlowLayout* updatePanelLayout = new FlowLayout(updatePanel);
    QPushButton* updateButton = new QPushButton(tr("Update"));
//    updateButton.addActionListener((ActionEvent event) -> {
//        log.debug("Update clicked");
//        updatePressed();
//    });
    connect(updateButton, SIGNAL(clicked()), this, SLOT(onUpdateButton()));
    updatePanelLayout->addWidget(updateButton);
    //contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.PAGE_AXIS));
    thisLayout->addWidget(updatePanel);

    setupEditorPane(); // re-layout all the toolbar items
    updatePressed();   // refresh default Switchboard, updates all buttons
    pack();

    // TODO choose your own icons
//        class makeCatalog extends SwingWorker<CatalogPanel, Object> {
//
//            @Override
//            /*public*/ CatalogPanel doInBackground() {
//                return CatalogPanel.makeDefaultCatalog();
//            }
//        }
//        (new makeCatalog()).execute();
//        log.debug("Init SwingWorker launched");
}

void SwitchboardEditor::onUpdateButton()
{
 log->debug(tr("Update clicked"));
 updatePressed();
}

/**
 * Create a new set of switches after removing the current array.
 * <p>
 * Called by Update button click and automatically after loading a panel
 * from XML (with all saved options set).
 */
/*public*/ void SwitchboardEditor::updatePressed() {
    log->debug(tr("update _hideUnconnected = %1").arg(_hideUnconnected?"true":"false"));
    if (_hideUnconnected && !hideUnconnected->isChecked()){
        hideUnconnected->setChecked(true);
    }
    log->debug(tr("update _editable = %1").arg(_editable));
    setVisible(_editable); // show/hide editor
    log->debug(tr("update _controlLayout = %1").arg(allControlling()?"true":"false"));

    for (int i = switchlist.size() -1 ; i >= 0; i--) {
        // deleting items starting from 0 will result in skipping the even numbered items
        switchboardLayeredPane->remove(i);
    }
    QObjectList children = switchboardLayeredPane->children();
    foreach (QObject* o, children) {
     this->layout()->removeWidget((QWidget*)o);
    o->deleteLater();
    }

    delete switchboardLayeredPane->layout();
    currRow = currCol = 0;
    switchlist.clear(); // reset list
    log->debug(tr("switchlist cleared, size is now: %1").arg(switchlist.size()));
    switchboardLayeredPane->setSize(300, 300);

    // update selected address range
    _range =  minSpinner->value() -  maxSpinner->value();
    switchboardLayeredPane->setLayout(switchboardLayeredPaneLayout=new QGridLayout(/*_range % ( columns.getValue()),
             columns->value()*/)); // vertical, horizontal
    currCol = 0;
    currRow = 0;

    addSwitchRange( minSpinner->
            value(),  maxSpinner->value(),
            beanTypeList->currentIndex(),
            beanManuPrefixes.value(beanManuNames->currentIndex()),
            switchShapeList->currentIndex());
    // update the title on the switchboard to match (no) layout control
    border->setTitle(beanManuNames->currentText() + " "
            + beanTypeList->currentText() + " - "
            + (allControlling() ? interact : noInteract));
    switchboardLayeredPaneLayout->addWidget(new QLabel(tr("Click to set turnout etc.\nUse context menu to set details.")), currRow+1,0,1,getColumns(), Qt::AlignHCenter);

    pack();
    switchboardLayeredPane->update();
}

/**
 * From default or user entry in Editor, fill the _targetpane with a series
 * of Switches.
 * <p>
 * Items in range that can connect to existing beans in JMRI are active. The
 * others are greyed out. Option to later connect (new) beans to switches.
 *
 * @param rangeMin    starting ordinal of Switch address range
 * @param rangeMax    highest ordinal of Switch address range
 * @param beanType    index of selected item in Type comboBox, either T, S
 *                    or L
 * @param manuPrefix  selected item in Connection comboBox, filled from
 *                    active connections
 * @param switchShape index of selected visual presentation of Switch shape
 *                    selected in Type comboBox, choose either a JButton
 *                    showing the name or (to do) a graphic image
 */
/*private*/ void SwitchboardEditor::addSwitchRange(int rangeMin, int rangeMax, int beanType, QString manuPrefix, int switchShape) {
    log->debug(tr("_hideUnconnected = %1").arg(getHideUnconnected()));
    QString name;
    BeanSwitch* _switch;
    NamedBean* nb = nullptr;
    QString _manu = manuPrefix; // cannot use All group as in Tables
    QString _insert = "";
    if (_manu.startsWith("M")) {
        _insert = "+"; // for CANbus.MERG On event
    }
    for (int i = rangeMin; i <= rangeMax; i++)
    {
     switch (beanType)
     {
      case 0:
          name = _manu + "T" + _insert + QString::number(i);
          nb = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getTurnout(name);
          break;
      case 1:
          name = _manu + "S" + _insert + QString::number(i);
          nb = InstanceManager::sensorManagerInstance()->getSensor(name);
          break;
      case 2:
          name = _manu + "L" + _insert + QString::number(i);
          nb = (NamedBean*)InstanceManager::lightManagerInstance()->getLight(name);
          break;
      default:
          log->error(tr("addSwitchRange: cannot parse bean name. manuPrefix = %1; i = %2").arg(manuPrefix).arg(i));
          return;
        }
        if (nb == nullptr && getHideUnconnected()) {
            continue; // skip i
        }
        _switch = new BeanSwitch(i, nb, name, switchShape, this); // add button instance i
        if (nb == nullptr) {
            _switch->setEnabled(false); // not connected
        } else {
            // set switch to display current bean state
            _switch->displayState(nb->getState());
        }
        _switch->setVisible(true);
        _switch->repaint();

        switchboardLayeredPaneLayout->addWidget(_switch, currRow, currCol++);
        if(currCol== getColumns())
        {
         currCol = 0;
         currRow++;
        }

        switchlist.append(name); // add to total number of switches on JLayeredPane
        log->debug(tr("Added switch %1").arg(name));
    }
    switchboardLayeredPaneLayout->update();
}

/**
 * Create the setup pane for the top of the frame. From layeredpane demo
 */
/*private*/ QGroupBox* SwitchboardEditor::createControlPanel() {
    QGroupBox* controls = new QGroupBox();
    QVBoxLayout* controlsLayout = new QVBoxLayout(controls);

    // navigation top row and to set range
    navBarPanel = new JPanel();
    //navBarPanel.setLayout(new BoxLayout(navBarPanel, BoxLayout.X_AXIS));
    QHBoxLayout* navBarPanelLayout = new QHBoxLayout(navBarPanel);

    navBarPanelLayout->addWidget(prev);
#if 0 // TODO:
    prev.addMouseListener(new MouseAdapter() {
        @Override
        /*public*/ void mouseClicked(MouseEvent e) {
            int oldMin = (Integer) minSpinner.getValue();
            int oldMax = (Integer) maxSpinner.getValue();
            _range = oldMax - oldMin;
            minSpinner.setValue(Math.max(rangeMin, oldMin - _range - 1));
            maxSpinner.setValue(Math.max(oldMax - _range - 1, Math.max(rangeMax, oldMax - _range - 1)));
            log.debug("oldMin ={}, oldMax ={}", oldMin, oldMax);
            //rangeMin = (Integer) minSpinner.getValue();
            //rangeMax = (Integer) maxSpinner.getValue();
        }
    });
#endif
    prev->setToolTip(tr("Previous range"));
    navBarPanelLayout->addWidget(new QLabel(tr("%1").arg(tr("From"))));
    navBarPanelLayout->addWidget(minSpinner);
    navBarPanelLayout->addWidget(new JLabel(tr("%1").arg(tr("UpTo"))));
    navBarPanelLayout->addWidget(maxSpinner);
    navBarPanelLayout->addWidget(next);
#if 0 // TODO:

    next.addMouseListener(new MouseAdapter() {
        @Override
        /*public*/ void mouseClicked(MouseEvent e) {
            int oldMin = (Integer) minSpinner.getValue();
            int oldMax = (Integer) maxSpinner.getValue();
            _range = oldMax - oldMin;
            minSpinner.setValue(oldMax + 1);
            maxSpinner.setValue(oldMax + _range + 1);
            //rangeMin = (Integer) minSpinner.getValue();
            //rangeMax = (Integer) maxSpinner.getValue();
        }
    });
#endif
    next->setToolTip(tr("Next range"));
    navBarPanelLayout->addWidget(Box::createHorizontalGlue());

    // put on which Frame?
    controlsLayout->addWidget(navBarPanel); // on 2nd Editor Panel
    //super.getTargetFrame().add(navBarPanel); // on (top of) Switchboard Frame/Panel

    //controls.setBorder(BorderFactory.createTitledBorder(tr("SelectRangeTitle")));
    controls->setTitle(tr("Address range to display"));
    return controls;
}

/*private*/ void SwitchboardEditor::setupEditorPane() {
    // Initial setup for both horizontal and vertical
    //Container contentPane = getContentPane();

    //remove these (if present) so we can add them back (without duplicates)
    if (editorContainer != nullptr) {
        editorContainer->setVisible(false);
        thisLayout->removeWidget(editorContainer);
    }

//        if (helpBarPanel != null) {
//            contentPane.remove(helpBarPanel);
//        }
    editToolBarPanel = new JPanel();
    //editToolBarPanel.setLayout(new BoxLayout(editToolBarPanel, BoxLayout.PAGE_AXIS));
    QVBoxLayout* editToolBarPanelLayout = new QVBoxLayout(editToolBarPanel);

    QGroupBox* innerBorderPanel = new QGroupBox();
    innerBorderPanel->resize(100,40);
    //innerBorderPanel.setLayout(new BoxLayout(innerBorderPanel, BoxLayout.PAGE_AXIS));
    QVBoxLayout* innerBorderPanelLayout = new QVBoxLayout(innerBorderPanel);
    innerBorderPanelLayout->setObjectName("BorderPanelLayout");
    //TitledBorder TitleBorder = BorderFactory.createTitledBorder(tr("SwitchboardHelpTitle"));
    innerBorderPanel->setTitle(tr("Help"));
    //innerBorderPanel.setBorder(TitleBorder);
    innerBorderPanelLayout->addWidget(new QLabel(tr("Click to set turnout etc.\nUse context menu to set details.")));
    // help2 explains: dimmed icons = unconnected
    innerBorderPanelLayout->addWidget(help2 = new JTextArea(tr("Greyed out buttons are not connected to layout.")));
    if (!getHideUnconnected()) {
        help2->setVisible(false); // hide this panel when hideUnconnected() is set to false from menu or checkbox
    }
    thisLayout->addWidget(innerBorderPanel);

    //Dimension screenDim = Toolkit.getDefaultToolkit().getScreenSize();

    editToolBarScroll = new QScrollArea(/*editToolBarPanel*/);
    editToolBarScroll->setWidget(editToolBarPanel);
    height = 60; //editToolBarScroll.getPreferredSize().height;
    editorContainer = new JPanel();
    //editorContainer.setLayout(new BoxLayout(editorContainer, BoxLayout.PAGE_AXIS));
    QVBoxLayout* editorContainerLayout = new QVBoxLayout(editorContainer);
    editorContainerLayout->addWidget(editToolBarScroll);
    editorContainer->setMinimumSize(QSize(width, height));
    editorContainer->resize(QSize(width, height));

//        helpBarPanel = new JPanel();
//        helpBarPanel.add(helpBar);
//        for (Component c : helpBar.getComponents()) {
//            if (c instanceof JTextArea) {
//                JTextArea j = (JTextArea) c;
//                //j.setSize(new Dimension(width, j.getSize().height));
//                j.setLineWrap(true);
//                j.setWrapStyleWord(true);
//            }
//        }
//        contentPane.setLayout(new BoxLayout(contentPane, false ? BoxLayout.LINE_AXIS : BoxLayout.PAGE_AXIS));
//        contentPane.add(editToolBarContainer);
//        contentPane.add(helpBarPanel);
    //helpBarPanel.setVisible(isEditable() && showHelpBar);
}

//@Override
/*protected*/ void SwitchboardEditor::makeOptionMenu() {
    _optionMenu = new QMenu(tr("Options"));
    _menuBar->addMenu(_optionMenu/*, 0*/);
    // controllable item
    _optionMenu->addAction(controllingBox);
//    controllingBox.addActionListener((ActionEvent event) -> {
//        setAllControlling(controllingBox.isSelected());
//        // update the title on the switchboard to match (no) layout control
//        border.setTitle(beanManuNames.getSelectedItem().toString() + " "
//                + beanTypeList.getSelectedItem().toString() + " - "
//                + (allControlling() ? interact : noInteract));
//        switchboardLayeredPane.repaint();
//        log.debug("border title updated");
//    });
    connect(controllingBox, SIGNAL(triggered()), this, SLOT(onControllingBox()));
    controllingBox->setChecked(allControlling());
    // hideUnconnected item
    _optionMenu->addAction(hideUnconnectedBox);
//    hideUnconnectedBox.addActionListener((ActionEvent event) -> {
//        setHideUnconnected(hideUnconnectedBox.isSelected());
//        hideUnconnected.setSelected(hideUnconnected()); // also (un)check the box on the editor
//        help2.setVisible(!hideUnconnected()); // and show/hide instruction line
//    });
    connect(hideUnconnectedBox, SIGNAL(triggered()), this, SLOT(onHideConnectedBox()));
    hideUnconnectedBox->setChecked(getHideUnconnected());

    // show tooltip item
    _optionMenu->addAction(showToolTipBox);
    //showToolTipBox.addActionListener((ActionEvent e) -> {
//        setAllShowToolTip(showToolTipBox->isChecked());
//    });
    connect(showToolTipBox, SIGNAL(triggered()), this, SLOT(onShowToolTipBox()));
    showToolTipBox->setChecked(showToolTip());

    // Show/Hide Scroll Bars
    QMenu* scrollMenu = new QMenu(tr("ComboBoxScrollable"));
    _optionMenu->addMenu(scrollMenu);
    QActionGroup* scrollGroup = new QActionGroup(this);
    scrollGroup->addAction(scrollBoth);
    scrollMenu->addAction(scrollBoth);
//    scrollBoth.addActionListener((ActionEvent event) -> {
//        setScroll(SCROLL_BOTH);
//    });
    scrollGroup->addAction(scrollNone);
    scrollMenu->addAction(scrollNone);
//    scrollNone.addActionListener((ActionEvent event) -> {
//        setScroll(SCROLL_NONE);
//    });
    scrollGroup->addAction(scrollHorizontal);
    scrollMenu->addAction(scrollHorizontal);
//    scrollHorizontal.addActionListener((ActionEvent event) -> {
//        setScroll(SCROLL_HORIZONTAL);
//    });
    scrollGroup->addAction(scrollVertical);
    scrollMenu->addAction(scrollVertical);
//    scrollVertical.addActionListener((ActionEvent event) -> {
//        setScroll(SCROLL_VERTICAL);
//    });

    // add background color menu item
    QAction* backgroundColorMenuItem = new QAction(tr("Set Background Color%1").arg("..."),this);
    _optionMenu->addAction(backgroundColorMenuItem);

//    backgroundColorMenuItem.addActionListener((ActionEvent event) -> {
//        Color desiredColor = JmriColorChooser.showDialog(this,
//                             tr("SetBackgroundColor", ""),
//                             defaultBackgroundColor);
//        if (desiredColor!=null && !defaultBackgroundColor == (desiredColor)) {
//           // if new bgColor matches the defaultTextColor, ask user as labels will become unreadable
//           if (desiredColor == (defaultTextColor)) {
//              int retval = JOptionPane.showOptionDialog(null,
//                           tr("ColorIdenticalWarning"), tr("WarningTitle"),
//                           0, JOptionPane.INFORMATION_MESSAGE, null,
//                           new Object[]{tr("ButtonOK"), tr("ButtonCancel")}, null);
//              log.debug("Retval: {}", retval);
//              if (retval != 0) {
//                 return;
//              }
//           }
//           defaultBackgroundColor = desiredColor;
//           setBackgroundColor(desiredColor);
//           setDirty(true);
//           switchboardLayeredPane.repaint();
//       }
//    });
    connect(backgroundColorMenuItem, SIGNAL(triggered()), this, SLOT(onBackground()));

    // add text color menu item
    QAction* textColorMenuItem = new QAction(tr("Set Default Text Color%1").arg("..."),this);
    _optionMenu->addAction(textColorMenuItem);

//    textColorMenuItem.addActionListener((ActionEvent event) -> {
//        Color desiredColor = JmriColorChooser.showDialog(this,
//                             tr("DefaultTextColor", ""),
//                             defaultTextColor);
//        if (desiredColor!=null && !defaultTextColor == (desiredColor)) {
//           // if new defaultTextColor matches bgColor, ask user as labels will become unreadable
//           if (desiredColor == (defaultBackgroundColor)) {
//              int retval = JOptionPane.showOptionDialog(null,
//              tr("ColorIdenticalWarning"), tr("WarningTitle"),
//              0, JOptionPane.INFORMATION_MESSAGE, null,
//              new Object[]{tr("ButtonOK"), tr("ButtonCancel")}, null);
//              log.debug("Retval: {}", retval);
//              if (retval != 0) {
//                 return;
//              }
//           }
//           defaultTextColor = desiredColor;
//           setDirty(true);
//           switchboardLayeredPane.repaint();
//           JmriColorChooser.addRecentColor(desiredColor);
//        }
//    });
    connect(textColorMenuItem,  SIGNAL(triggered()), this, SLOT(onTextColor()));
}

void SwitchboardEditor::onHideConnectedBox()
{
 setHideUnconnected(hideUnconnectedBox->isChecked());
 hideUnconnected->setChecked(hideUnconnected->isChecked()); // also (un)check the box on the editor
 help2->setVisible(!hideUnconnected->isChecked()); // and show/hide instruction line
}


void SwitchboardEditor::onBackground()
{
 QColor desiredColor = JmriColorChooser::showDialog(this,
                      tr("Set Background Color%1").arg(""),
                      defaultBackgroundColor);
 if (desiredColor!=QColor() && defaultBackgroundColor != (desiredColor)) {
    // if new bgColor matches the defaultTextColor, ask user as labels will become unreadable
    if (desiredColor == (defaultTextColor)) {
       int retval = JOptionPane::showOptionDialog(nullptr,
                    tr("The text color would match the background color,\nmaking labels unreadable. Continue?"), tr("Warning"),
//                    0, JOptionPane.INFORMATION_MESSAGE, null,
//                    new Object[]{tr("ButtonOK"), tr("ButtonCancel")}, null);
                      JOptionPane::OK_CANCEL_OPTION, JOptionPane::INFORMATION_MESSAGE   );
       log->debug(tr("Retval: %1").arg(retval));
       if (retval != 0) {
          return;
       }
    }
    defaultBackgroundColor = desiredColor;
    setBackgroundColor(desiredColor);
    setDirty(true);
    switchboardLayeredPane->update();
  }
}

void SwitchboardEditor::onTextColor()
{
 QColor desiredColor = JmriColorChooser::showDialog(this,
                      tr("Set Default Text Color%1").arg(""),
                      defaultTextColor);
 if (desiredColor!=QColor() && defaultTextColor != (desiredColor))
 {
    // if new defaultTextColor matches bgColor, ask user as labels will become unreadable
    if (desiredColor == (defaultBackgroundColor)) {
       int retval = JOptionPane::showOptionDialog(nullptr,
       tr("ColorIdenticalWarning"), tr("WarningTitle"), JOptionPane::OK_CANCEL_OPTION,
                                                  JOptionPane::INFORMATION_MESSAGE);
//               0, JOptionPane::INFORMATION_MESSAGE, null,
//               new Object[]{tr("ButtonOK"), tr("ButtonCancel")}, null);
       log->debug(tr("Retval: %1").arg(retval));
       if (retval != 0) {
          return;
       }
    }
    defaultTextColor = desiredColor;
    setDirty(true);
    switchboardLayeredPane->update();
    JmriColorChooser::addRecentColor(desiredColor);
 }
}
void SwitchboardEditor::onControllingBox()
{
     setAllControlling(controllingBox->isChecked());
     // update the title on the switchboard to match (no) layout control
     border->setTitle(beanManuNames->currentText() + " "
             + beanTypeList->currentText() + " - "
             + (allControlling() ? interact : noInteract));
//     switchboardLayeredPane.repaint();
     log->debug("border title updated");
}

void SwitchboardEditor::onHideUnconnected(bool bChecked)
{
 setHideUnconnected(bChecked);
 hideUnconnectedBox->setChecked(bChecked); // also (un)check the box on the menu
 _hideUnconnected = bChecked;
 help2->setVisible(!getHideUnconnected()); // and show/hide instruction line
 updatePressed();
}

void SwitchboardEditor::onHideUnConnectedBox(bool bChecked)
{
 setHideUnconnected(bChecked);
 hideUnconnectedBox->setChecked(bChecked); // also (un)check the box on the editor
 _hideUnconnected = bChecked;
 help2->setVisible(!getHideUnconnected()); // and show/hide instruction line
 updatePressed();
}

void SwitchboardEditor::onShowToolTipBox()
{
 setAllShowToolTip(showToolTipBox->isChecked());
}

/*private*/ void SwitchboardEditor::makeFileMenu() {
    _fileMenu = new QMenu(tr("File"));
    _menuBar->insertMenu((Action*)_fileMenu, _optionMenu);
    _fileMenu->addAction(new NewPanelAction(tr("New"),(QObject*)this));

    _fileMenu->addAction(new StoreXmlUserAction(tr("Store"),this));
    QMenu* storeIndexItem = new QMenu(tr("Store Image Index"));
    _fileMenu->addMenu(storeIndexItem);

//    storeIndexItem.addActionListener((ActionEvent event) -> {
//        InstanceManager::getDefault("DefaultCatalogTreeManager").storeImageIndex();
//    });

    QAction* editItem = new QAction(tr("Rename Panel%1").arg("..."),this);
    PositionableJComponent* z = new PositionableJComponent(this);
    z->setScale(getPaintScale());
    //editItem.addActionListener(CoordinateEdit.getNameEditAction(z));

    connect(editItem, SIGNAL(triggered()), this, SLOT(onEditItem()));
    _fileMenu->addAction(editItem);

    _fileMenu->addSeparator();

    QAction* deleteItem = new QAction(tr("Delete this Panel..."),this);
    _fileMenu->addAction(deleteItem);
//    deleteItem.addActionListener((ActionEvent event) -> {
//        if (deletePanel()) {
//            dispose();
//        }
//    });
    connect(deleteItem, SIGNAL(triggered()), this, SLOT(onDeleteItem()));
    _fileMenu->addSeparator();
    editItem = new QAction(tr("Close Editor"),this);
    _fileMenu->addAction(editItem);
//    editItem.addActionListener((ActionEvent event) -> {
//        setAllEditable(false);
//        setVisible(false); // hide Editor pane
//    });
    connect(editItem, SIGNAL(triggered()), this, SLOT(onCloseEditor()));
}

void SwitchboardEditor::onStoreIndexItem()
{
 static_cast<DefaultCatalogTreeManager*>(InstanceManager::getDefault("DefaultCatalogTreeManager"))->storeImageIndex();
}

void SwitchboardEditor::onDeleteItem()
{
 if (deletePanel()) {
//     dispose();
 }
}

void SwitchboardEditor::onEditItem()
{
 CoordinateEdit* edit = new CoordinateEdit(this);
 edit->getNameEditAction(NULL);
}
void SwitchboardEditor::onCloseEditor()
{
 setAllEditable(false);
 setVisible(false); // hide Editor pane

}

/*public*/ void SwitchboardEditor::setDefaultTextColor(QString color) {
    defaultTextColor = ColorUtil::stringToColor(color);
// TODO:    JmriColorChooser::addRecentColor(ColorUtil::stringToColor(color));
}

/*public*/ QString SwitchboardEditor::getDefaultTextColor() {
    return ColorUtil::colorToColorName(defaultTextColor);
}

/*public*/ QColor SwitchboardEditor::getDefaultTextColorAsColor() {
    return defaultTextColor;
}

/**
 * Load from xml and set bg color of _targetpanel as well as variable.
 *
 * @param color RGB Color for switchboard background and beanSwitches
 */
/*public*/ void SwitchboardEditor::setDefaultBackgroundColor(QColor color) {
    setBackgroundColor(color); // via Editor
    defaultBackgroundColor = color;
}

/**
 * Get current default background color.
 *
 * @return background color of this Switchboard
 */
/*public*/ QColor SwitchboardEditor::getDefaultBackgroundColor() {
    return defaultBackgroundColor;
}

// *********************** end Menus ************************

//@Override
/*public*/ void SwitchboardEditor::setAllEditable(bool edit) {
    log->debug(tr("_editable set to %1").arg(edit));
    if (edit) {
        if (_editorMenu != nullptr) {
            _menuBar->removeAction((QAction*)_editorMenu);
        }
        if (_optionMenu == nullptr) {
            makeOptionMenu();
        } else {
            _menuBar->insertMenu((Action*)_optionMenu, windowMenu);
        }
        if (_fileMenu == nullptr) {
            makeFileMenu();
        } else {
            _menuBar->insertMenu((Action*)_fileMenu, _optionMenu);
        }
        log->debug("added File and Options menubar");
        //contentPane.SetUpdateButtonEnabled(false);
    } else {
        if (_fileMenu != nullptr) {
            _menuBar->removeAction((QAction*)_fileMenu);
        }
        if (_optionMenu != nullptr) {
            _menuBar->removeAction((QAction*)_optionMenu);
        }
        if (_editorMenu == nullptr) {
            _editorMenu = new QMenu(tr("Edit"));
            AbstractAction* act;
            _editorMenu->addAction(act = new AbstractAction(tr("Open Editor"),this));
//            {
//               // @Override
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    setAllEditable(true);
//                    log.debug("SwitchBoard Editor Open Editor menu called");
//                }
//            });
            connect(act, SIGNAL(triggered()), this, SLOT(onOpenEditor()));
        }
        _menuBar->insertMenu((Action*)_editorMenu, windowMenu);
        //contentPane.SetUpdateButtonEnabled(true);
    }
    Editor::setAllEditable(edit);
    Editor::setTitle();
//    _menuBar.revalidate();
}

void SwitchboardEditor::onOpenEditor()
{
 setAllEditable(true);
 log->debug("SwitchBoard Editor Open Editor menu called");

}
//@Override
/*public*/ void SwitchboardEditor::setUseGlobalFlag(bool set) {
    controllingBox->setEnabled(set);
    Editor::setUseGlobalFlag(set);
}

//@Override
/*public*/ void SwitchboardEditor::setTitle() {
    QString name = getName(); // get name of JFrame
    log->debug(tr("JFrame name = %1").arg(name));
    if (name == nullptr || name.length() == 0) {
        name = tr("Switchboard%1").arg("");
    }
    JmriJFrame::setTitle(name + " " + tr("Editor"));
    Editor::getTargetFrame()->setTitle(name);
}

/**
 * Control whether target panel items without a connection to the layout are
 * displayed.
 *
 * @param state true to hide all in range
 */
/*public*/ void SwitchboardEditor::setHideUnconnected(bool state) {
    _hideUnconnected = state;
    // TODO update checkbox and menu
    //if (!state) {
    // TODO hide Help2
    //}
}

/*public*/ bool SwitchboardEditor::getHideUnconnected() {
    return _hideUnconnected;
}

/**
 * Allow external reset of dirty bit.
 */
/*public*/ void SwitchboardEditor::resetDirty() {
    setDirty(false);
    savedEditMode = isEditable();
    savedControlLayout = allControlling();
}

/**
 * Allow external set of dirty bit.
 */
/*public*/ void SwitchboardEditor::setDirty(bool val) {
    panelChanged = val;
}

/*public*/ void SwitchboardEditor::setDirty() {
    setDirty(true);
}

/**
 * Check the dirty state.
 */
/*public*/ bool SwitchboardEditor::isDirty() {
    return panelChanged;
}

// ********************** load/store board *******************
/**
 * Load Range minimum.
 *
 * @param rangemin lowest address to show
 */
/*public*/ void SwitchboardEditor::setPanelMenuRangeMin(int rangemin) {
    minSpinner->setValue(rangemin);
    rangeMin = rangemin;
}

/**
 * Load Range maximum.
 *
 * @param rangemax highest address to show
 */
/*public*/ void SwitchboardEditor::setPanelMenuRangeMax(int rangemax) {
    maxSpinner->setValue(rangemax);
    rangeMax = rangemax;
}

/**
 * Store Range minimum.
 *
 * @return lowest address to show
 */
/*public*/ int SwitchboardEditor::getPanelMenuRangeMin() {
    return (int) minSpinner->value();
}

/**
 * Store Range maximum.
 *
 * @return highest address to show
 */
/*public*/ int SwitchboardEditor::getPanelMenuRangeMax() {
    return (int) maxSpinner->value();
}


// ***************** Store & Load xml ********************
/**
 * Store bean type.
 *
 * @return bean type prefix
 */
/*public*/ QString SwitchboardEditor::getSwitchType() {
    QString switchType = beanTypeList->currentText();
    if (switchType == (LIGHT)) { // switch-case doesn't work here
        typePrefix = "L";
    } else if (switchType == (SENSOR)) {
        typePrefix = "S";
    } else { // Turnout
        typePrefix = "T";
    }
    return typePrefix;
}

/**
 * Get bean type name.
 *
 * @return bean type name
 */
/*public*/ QString SwitchboardEditor::getSwitchTypeName() {
    return type;
}

/**
 * Load bean type.
 *
 * @param prefix the bean type prefix
 */
/*public*/ void SwitchboardEditor::setSwitchType(QString prefix) {
    typePrefix = prefix;
    if (typePrefix== "L")
    {
     type = LIGHT;
    }
    else if (typePrefix == "S")
    {
     type = SENSOR;
    }
    else
     // Turnout
     type = TURNOUT;
 try {
        beanTypeList->setCurrentText(type);
    } catch (IllegalArgumentException e) {
        log->error(tr("invalid bean type [%1] in Switchboard").arg(typePrefix));
    }
}

/**
 * Store connection type.
 *
 * @return bean connection prefix
 */
/*public*/ QString SwitchboardEditor::getSwitchManu() {
    return this->beanManuPrefixes.value(beanManuNames->currentIndex());
}

/**
 * Load connection type.
 *
 * @param manuPrefix connection prefix
 */
/*public*/ void SwitchboardEditor::setSwitchManu(QString manuPrefix) {
    int choice = 0;
    for (int i = 0; i < beanManuPrefixes.size(); i++) {
        if (beanManuPrefixes.value(i) == (manuPrefix)) {
            choice = i;
            break;
        }
    }
    try {
        beanManuNames->setCurrentText(beanManuPrefixes.value(choice));
    } catch (IllegalArgumentException e) {
        log->error(tr("invalid connection [%1] in Switchboard").arg(manuPrefix));
    }
}

/**
 * Store switch shape.
 *
 * @return bean shape prefix
 */
/*public*/ QString SwitchboardEditor::getSwitchShape() {
    QString shape;
    int shapeChoice = switchShapeList->currentIndex();
    switch (shapeChoice) {
        case 1:
            shape = "icon";
            break;
        case 2:
            shape = "drawing";
            break;
        case 3:
            shape = "symbol";
            break;
        default:
            // Turnout
            shape = "button";
            break;
    }
    return shape;
}

/**
 * Load switch shape.
 *
 * @param switchShape name of switch shape
 */
/*public*/ void SwitchboardEditor::setSwitchShape(QString switchShape) {
    int shape;
    if(switchShape == "icon")
            shape = 1;
    else if(switchShape ==  "drawing")
            shape = 2;
    else if(switchShape == "symbol")
            shape = 3;
    else // button
            shape = 0;

    try {
        switchShapeList->setCurrentIndex(shape);
    } catch (IllegalArgumentException e) {
        log->error(tr("invalid switch shape [%1] in Switchboard").arg(shape));
    }
}

/*public*/ void SwitchboardEditor::setBoardToolTip(QString tip) {
    setToolTip(tip);
}

/**
 * Store Switchboard column spinner.
 *
 * @return the number of switches to display per row
 */
/*public*/ int SwitchboardEditor::getColumns() {
    return columns->value();
}

/**
 * Load Switchboard column spinner.
 *
 * @param cols the number of switches to display per row (as text)
 */
/*public*/ void SwitchboardEditor::setColumns(int cols) {
    columns->setValue(cols);
}

// all content loaded from file.
/*public*/ void SwitchboardEditor::loadComplete() {
    log->debug("loadComplete");
}

/**
 * After construction, initialize all the widgets to their saved config
 * settings.
 */
//@Override
/*public*/ void SwitchboardEditor::initView() {

    controllingBox->setChecked(allControlling());

    showToolTipBox->setChecked(showToolTip());
    switch (_scrollState) {
        case SCROLL_NONE:
            scrollNone->setChecked(true);
            break;
        case SCROLL_BOTH:
            scrollBoth->setChecked(true);
            break;
        case SCROLL_HORIZONTAL:
            scrollHorizontal->setChecked(true);
            break;
        default:
            scrollVertical->setChecked(true);
    }

    log->debug("InitView done");
}

/*protected*/ Manager* SwitchboardEditor::getManager(QChar typeChar) {
    if (typeChar == 'T')
            return InstanceManager::turnoutManagerInstance();
     else if (typeChar == 'S')
            return InstanceManager::sensorManagerInstance();
     else if (typeChar =='L') // Light
            return InstanceManager::lightManagerInstance();
     else
            log->error(tr("Unexpected bean type character \"%1\" found.").arg(typeChar));
            return nullptr;
}

/**
 * KeyListener of Editor.
 *
 * @param e the key event heard
 */
//@Override
/*public*/ void SwitchboardEditor::keyPressEvent(QKeyEvent *e)
{
    int x = 0;
    int y = 0;
    switch (e->key()) {
        case Qt::Key::Key_Up:
        case Qt::Key::Key_Up | Qt::KeypadModifier:
        //case Qt::Key::Key_NUMPAD8:
            y = -1;
            break;
        case Qt::Key::Key_Down:
        case Qt::Key::Key_Down | Qt::KeypadModifier:
        //case Qt::Key::Key_NUMPAD2:
            y = 1;
            break;
        case Qt::Key::Key_Left:
        case Qt::Key::Key_Left | Qt::KeypadModifier:
        //case Qt::Key::Key_NUMPAD4:
            x = -1;
            break;
        case Qt::Key::Key_Right:
        case Qt::Key::Key_Right | Qt::KeypadModifier:
        //case KeyEvent.VK_NUMPAD6:
            x = 1;
            break;
        case Qt::Key::Key_D:
        case Qt::Key::Key_Delete:
        case Qt::Key::Key_Minus:
        case Qt::Key::Key_A:
        case Qt::Key::Key_Insert:
        case Qt::Key::Key_Plus:
            break;
        default:
            return;
    }
    if (/*e->isShiftDown()*/e->key() & Qt::ShiftModifier) {
        x *= 5;
        y *= 5;
    }
    if (_selectionGroup != nullptr) {
        for (Positionable* comp : *_selectionGroup) {
            moveItem(comp, x, y);
        }
    }
    repaint();
}
#if 0
@Override
/*public*/ void mousePressed(MouseEvent event) {
}

@Override
/*public*/ void mouseReleased(MouseEvent event) {
}

@Override
/*public*/ void mouseClicked(MouseEvent event) {
}

@Override
/*public*/ void mouseDragged(MouseEvent event) {
}

@Override
/*public*/ void mouseMoved(MouseEvent event) {
}

@Override
/*public*/ void mouseEntered(MouseEvent event) {
    _targetPanel.repaint();
}

@Override
/*public*/ void mouseExited(MouseEvent event) {
    setToolTip(null);
    _targetPanel.repaint(); // needed for ToolTip
}

/**
 * Handle close of Editor window.
 * <p>
 * Overload/override method in JmriJFrame parent, which by default is
 * permanently closing the window. Here, we just want to make it invisible,
 * so we don't dispose it (yet).
 */
//@Override
/*public*/ void SwitchboardEditor::windowClosing(QCloseEvent* e) {
    setVisible(false);
    setAllEditable(false);
}

/**
 * Handle opening of Editor window.
 * <p>
 * Overload/override method in JmriJFrame parent to reset _menuBar.
 */
//@Override
/*public*/ void SwitchboardEditor::showEvent(QShowEvent*)
{
//    _menuBar->revalidate();
}
#endif
#if 1
// ************* implementation of Abstract Editor methods **********

/**
 * The target window has been requested to close. Don't delete it at this
 * time. Deletion must be accomplished via the Delete this panel menu item.
 */
//@Override
/*protected*/ void SwitchboardEditor::targetWindowClosingEvent(QCloseEvent* e) {
    bool save = (isDirty() || (savedEditMode != isEditable())
            || (savedControlLayout != allControlling()));
    targetWindowClosing(save);
}
#endif
/**
 * Create sequence of panels, etc. for layout: JFrame contains its
 * ContentPane which contains a JPanel with BoxLayout (p1) which contains a
 * JScollPane (js) which contains the targetPane.
 * Note this is a private menuBar, looking identical to the Editor's _menuBar
 *
 * @param name title for the Switchboard
 */
/*public*/ JmriJFrame* SwitchboardEditor::makeFrame(QString name) {
    JmriJFrame* targetFrame = new JmriJFrameX(name/*, nullptr*/);
    targetFrame->setVisible(true);
    targetFrame->setFrameRef("Switchboard");
    targetFrame->setFrameLocation();

    QMenuBar* menuBar = new QMenuBar();
    editMenu = new QMenu(tr("Edit"));
    menuBar->addMenu(editMenu);
    targetFrame->setMenuBar(menuBar);
    AbstractAction* addAction = new AbstractAction(tr("Open Editor"),targetFrame);
    editMenu->addAction(addAction);
   //    {
   //        @Override
   //        /*public*/ void actionPerformed(ActionEvent e) {
   //            setVisible(true);
   //            setAllEditable(true);
   //            log.debug("SwitchBoard Open Editor menu called");c723@knobacres

   //        }
   //    });
    editMenu->addAction(addAction);
    connect(addAction, SIGNAL(triggered()), this, SLOT(onAddAction()));

    targetFrame->addHelpMenu("package.jmri.jmrit.display.SwitchboardEditor", true);
    return targetFrame;
}

void SwitchboardEditor::onAddAction()
{
 setVisible(true);
 this->getTargetFrame()->showNormal();
 setAllEditable(true);
 log->debug("SwitchBoard Open Editor menu called");
}

/*protected*/ void SwitchboardEditor::setSecondSelectionGroup(QList<Positionable*> list) {
    _secondSelectionGroup = list;
}
#if 0
@Override
/*protected*/ void paintTargetPanel(Graphics g) {
    // needed to create PositionablePolygon
    //_shapeDrawer.paint(g);
    if (_secondSelectionGroup != null) {
        Graphics2D g2d = (Graphics2D) g;
        g2d.setColor(new Color(150, 150, 255));
        g2d.setStroke(new java.awt.BasicStroke(2.0f));
        for (Positionable p : _secondSelectionGroup) {
            if (!(p instanceof jmri.jmrit.display.controlPanelEditor.shape.PositionableShape)) {
                g.drawRect(p.getX(), p.getY(), p.maxWidth(), p.maxHeight());
            }
        }
    }
}
#endif
/**
 * Get a beanSwitch object from this switchBoard panel by a given name.
 *
 * @param sName name of switch label/connected bean
 * @return beanSwitch switch object with the given name
 */
/*protected*/ BeanSwitch* SwitchboardEditor::getSwitch(QString sName) {
    for (int i = 0; i < switchlist.size(); i++) {
        log->debug(tr("comparing switch %1 to %2").arg(switchlist.at(i)).arg(sName));
        if (switchlist.value(i) == (sName)) {
            return (BeanSwitch*) switchboardLayeredPane->getComponent(i);
        } else {
            log->warn(tr("switch %1 not found on panel").arg(sName));
        }
    }
    return nullptr;
}

/*public*/ QList<BeanSwitch*> SwitchboardEditor::getSwitches() {
    _switches.clear(); // reset list
    log->debug(tr("N = %1").arg(switchlist.size()));
    for (int i = 0; i < switchlist.size(); i++) {
        _switches.append((BeanSwitch*) switchboardLayeredPane->getComponent(i));
    }
    return _switches;
}

/**
 * Set up item(s) to be copied by paste.
 * <p>
 * Not used on switchboards but has to override Editor.
 */
//@Override
/*protected*/ void SwitchboardEditor::copyItem(Positionable* p) {
}

/**
 * Set an object's location when it is created.
 * <p>
 * Not used on switchboards but has to override Editor.
 *
 * @param obj object to position
 */
//@Override
/*public*/ void SwitchboardEditor::setNextLocation(Positionable* obj) {
    obj->setLocation(0, 0);
}

/**
 * Create popup for a Positionable object.
 * <p>
 * Popup items common to all positionable objects are done before and after
 * the items that pertain only to specific Positionable types.
 * <p>
 * Not used on switchboards but has to override Editor.
 *
 * @param p     the item on the Panel
 * @param event MouseEvent heard
 */
//@Override
/*protected*/ void SwitchboardEditor::showPopUp(Positionable* p, QMouseEvent* event) {
    _currentSelection = nullptr;
}

/*protected*/ QList<Positionable*>* SwitchboardEditor::getSelectionGroup() {
    return _selectionGroup;
}

//@Override
/*public*/ QList<NamedBeanUsageReport*> SwitchboardEditor::getUsageReport(NamedBean* bean) {
    QList<NamedBeanUsageReport*> report = QList<NamedBeanUsageReport*>();
    if (bean != nullptr) {
        //getSwitches().forEach((beanSwitch) ->
     for(BeanSwitch* beanSwitch : getSwitches())
        {
            if (bean->equals(beanSwitch->getNamedBean())) {
                report.append(new NamedBeanUsageReport("SwitchBoard", getName()));
            }
        }//);
    }
    return report;
}

/*public*/ int SwitchboardEditor::getTileSize() { //tmp synchronized
    return _tileSize; // initially 100
}

/*public*/ void SwitchboardEditor::setScroll(QString strState) {
    int state = SCROLL_BOTH;
    if (strState.toLower()=="none" || strState.toLower()=="no") state = SCROLL_NONE;
    else if (strState==("horizontal")) state = SCROLL_HORIZONTAL;
    else if (strState==("vertical")) state = SCROLL_VERTICAL;
    if (_debug) log->debug("setScroll: strState= "+strState+", state= "+QString::number(state));
    setScroll(state);
}
/*public*/ void SwitchboardEditor::setScroll(int state)
{
 if(editPanel == nullptr) return; // TODO: handle for when JLayeredPane is used
    if (_debug) log->debug("setScroll "+ QString::number(state));
    switch (state) {
        case SCROLL_NONE:
            scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
            scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
            break;
        case SCROLL_BOTH:
     scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
     scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
            break;
        case SCROLL_HORIZONTAL:
     scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
     scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
            break;
        case SCROLL_VERTICAL:
     scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
     scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
            break;
    }
    _scrollState = state;
}
/*public*/ QString SwitchboardEditor::getClassName()
{
 return "jmri.jmrit.display.switchboardEditor.SwitchboardEditor";
}


/*private*/ /*final*/ /*static*/ Logger* SwitchboardEditor::log = LoggerFactory::getLogger("SwitchboardEditor");

