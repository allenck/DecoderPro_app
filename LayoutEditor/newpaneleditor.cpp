#include "newpaneleditor.h"
#include "jtextfield.h"
#include <QBoxLayout>
#include <QComboBox>
#include <QLabel>
#include "flowlayout.h"
#include <QMenu>
#include <QMenuBar>
#include "newpanelaction.h"
#include "storexmluseraction.h"
#include "catalogtreemanager.h"
#include "instancemanager.h"
#include <QCheckBox>
#include "configuremanager.h"
#include "loggerfactory.h"
#include "warranttableaction.h"
#include "jframe.h"
#include "vptr.h"
#include "joptionpane.h"
#include "panelmenu.h"
#include "jmricolorchooser.h"
#include "class.h"
#include "xmladapter.h"

// Java PanelEditor class that will replace current one.

/**
 * Provides a simple editor for adding jmri.jmrit.display items to a captive
 * JFrame.
 * <p>
 * GUI is structured as a band of common parameters across the top, then a
 * series of things you can add.
 * <p>
 * All created objects are put specific levels depending on their type (higher
 * levels are in front):
 * <ul>
 *   <li>BKG background
 *   <li>ICONS icons and other drawing symbols
 *   <li>LABELS text labels
 *   <li>TURNOUTS turnouts and other variable track items
 *   <li>SENSORS sensors and other independently modified objects
 * </ul>
 * <p>
 * The "contents" List keeps track of all the objects added to the target frame
 * for later manipulation.
 * <p>
 * If you close the Editor window, the target is left alone and the editor
 * window is just hidden, not disposed. If you close the target, the editor and
 * target are removed, and dispose is run. To make this logic work, the
 * PanelEditor is descended from a JFrame, not a JPanel. That way it can control
 * its own visibility.
 * <p>
 * The title of the target and the editor panel are kept consistent via the
 * {#setTitle} method.
 *
 * @author Bob Jacobsen Copyright (c) 2002, 2003, 2007
 * @author Dennis Miller 2004
 * @author Howard G. Penny Copyright (c) 2005
 * @author Matthew Harris Copyright (c) 2009
 * @author Pete Cressman Copyright (c) 2009, 2010
 */
///*public*/ class PanelEditor extends Editor implements ItemListener {


/*public*/ NewPanelEditor::NewPanelEditor(QWidget *parent) : Editor(parent) {
 setProperty("JavaClassName", "jmri.jmrit.display.panelEditor.PanelEditor");

}

/*public*/ NewPanelEditor::NewPanelEditor(QString name, QWidget *parent) : Editor(name, false, true, parent) {
 setProperty("JavaClassName", "jmri.jmrit.display.panelEditor.PanelEditor");

    //super(name, false, true);
    nextX = new JTextField("0", 4);
    nextY = new JTextField("0", 4);

    editableBox = new QCheckBox(tr("CheckBoxEditable"));
    positionableBox = new QCheckBox(tr("CheckBoxPositionable"));
    controllingBox = new QCheckBox(tr("CheckBoxControlling"));
    showTooltipBox = new QCheckBox(tr("CheckBoxShowTooltips"));
    hiddenBox = new QCheckBox(tr("CheckBoxHidden"));
    menuBox = new QCheckBox(tr("CheckBoxMenuBar"));
    scrollableLabel = new JLabel(tr("ComboBoxScrollable"));
    scrollableComboBox = new QComboBox();

    labelAdd = new QPushButton(tr("ButtonAddText"));
    nextLabel = new JTextField(10);

    init(name);
}

//@Override
/*protected*/ void NewPanelEditor::init(QString name) {
#if 0 // TODO:
    Runnable r = new Runnable() {
        @Override
        /*public*/ void run() {
            try {
                // Build resource catalog and load CatalogTree.xml now
                CatalogPanel catalog = new CatalogPanel();
                catalog.createNewBranch("IFJAR", "Program Directory", "resources");
                // log.debug("init run created (var=catalog)"); // where's this used, just a test run?
            } catch (Exception ex) {
                log.error("Error trying to set up preferences {}", ex.toString());
            }
        }
    };
    Thread thr = new Thread(r);
    thr.setName("PanelEditor init");
    thr.start();
#endif
    QWidget* contentPane = this->getContentPane();
    contentPane->setLayout(new QVBoxLayout(contentPane/*, BoxLayout.Y_AXIS*/));
    // common items
    QWidget* common = new QWidget();
    FlowLayout* commonLayout;
    common->setLayout(commonLayout = new FlowLayout());
    commonLayout->addWidget(new QLabel(" x:"));
    commonLayout->addWidget(nextX);
    commonLayout->addWidget(new QLabel(" y:"));
    commonLayout->addWidget(nextY);
    contentPane->layout()->addWidget(common);
    setAllEditable(true);
    setShowHidden(true);
    Editor::setTargetPanel((EditScene*)nullptr, makeFrame(name));
    Editor::setTargetPanelSize(400, 300);
    // TODO:
//    Editor::setDefaultToolTip(new ToolTip(nullptr, 0, 0, new Font("SansSerif", Font.PLAIN, 12),
//            QColor(Qt::black),  QColor(215, 225, 255), Color.black));
    // set scrollbar initial state
    setScroll(SCROLL_BOTH);

    // add menu - not using PanelMenu, because it now
    // has other stuff in it?
    QMenuBar* menuBar = new QMenuBar();
    QMenu* fileMenu = new QMenu(tr("MenuFile"));
    menuBar->addMenu(fileMenu);
    fileMenu->addAction(new NewPanelAction(tr("MenuItemNew"), this));
    fileMenu->addAction(new StoreXmlUserAction(tr("MenuItemStore"),this));
    QAction* storeIndexItem = new QAction(tr("MIStoreImageIndex"), this);
    fileMenu->addAction(storeIndexItem);
//    storeIndexItem.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent event) {
//            InstanceManager.getDefault(CatalogTreeManager.class).storeImageIndex();
//        }
//    });
    connect(storeIndexItem, SIGNAL(triggered()), this ,SLOT(onStoreIndexItem()));
    QAction* editItem = new QAction(tr("editIndexMenu"));
//    editItem.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            ImageIndexEditor ii = InstanceManager.getDefault(ImageIndexEditor.class);
//            ii.pack();
//            ii.setVisible(true);
//        }

//    });
    connect(editItem, SIGNAL(triggered()), this, SLOT(onEditIndexMenu()));
    fileMenu->addAction(editItem);

    editItem = new QAction(tr("CPEView"));
    fileMenu->addAction(editItem);
//    editItem.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent event) {
//            changeView("jmri.jmrit.display.controlPanelEditor.ControlPanelEditor");
//        }
//    });
    connect(editItem, SIGNAL(triggered()), this, SLOT(onCPEView()));

    fileMenu->addSeparator();
    QAction* deleteItem = new QAction(tr("DeletePanel"));
    fileMenu->addAction(deleteItem);
//    deleteItem.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent event) {
//            if (deletePanel()) {
//                dispose();
//            }
//        }
//    });
    connect(deleteItem, SIGNAL(triggered()), this, SLOT(onDelete()));

    setMenuBar(menuBar);
    addHelpMenu("package.jmri.jmrit.display.PanelEditor", true);

    // allow renaming the panel
    {
        QWidget* namep = new QWidget();
        FlowLayout* namepLayout;
        namep->setLayout(namepLayout = new FlowLayout());
        QPushButton* b = new QPushButton(tr("renamePanelMenu", "..."));
#if 0 //done
        b.addActionListener(new ActionListener() {
            PanelEditor editor;

            @Override
            /*public*/ void actionPerformed(ActionEvent e) {
                // prompt for name
                String newName = JOptionPane.showInputDialog(null, tr("PromptNewName"));
                if (newName == null) {
                    return;  // cancelled
                }
                if (InstanceManager.getDefault(PanelMenu.class).isPanelNameUsed(newName)) {
                    JOptionPane.showMessageDialog(null, tr("CanNotRename"), tr("PanelExist"),
                            JOptionPane.ERROR_MESSAGE);
                    return;
                }
                if (getTargetPanel().getTopLevelAncestor() != null) {
                    ((JFrame) getTargetPanel().getTopLevelAncestor()).setTitle(newName);
                }
                editor.setTitle();
                InstanceManager.getDefault(PanelMenu.class).renameEditorPanel(editor);
            }

            ActionListener init(PanelEditor e) {
                editor = e;
                return this;
            }
        }.init(this));
#endif
        connect(b, SIGNAL(clicked(bool)), this, SLOT(onRename()));
        namepLayout->addWidget(b);
        this->getContentPane()->layout()->addWidget(namep);
    }
    // add a text label
    {
        QWidget* panel = new QWidget();
        FlowLayout* panelLayout;
        panel->setLayout(panelLayout = new FlowLayout());
        panelLayout->addWidget(labelAdd);
        labelAdd->setEnabled(false);
        labelAdd->setToolTip(tr("ToolTipWillActivate"));
        panelLayout->addWidget(nextLabel);
#if 0
        labelAdd.addActionListener(new ActionListener() {
            PanelEditor editor;

            @Override
            /*public*/ void actionPerformed(ActionEvent a) {
                editor.addLabel(nextLabel.getText());
            }

            ActionListener init(PanelEditor e) {
                editor = e;
                return this;
            }
        }.init(this));
        nextLabel.addKeyListener(new KeyAdapter() {
            @Override
            /*public*/ void keyReleased(KeyEvent a) {
                if (nextLabel.getText() == ("")) {
                    labelAdd.setEnabled(false);
                    labelAdd.setToolTipText(tr("ToolTipWillActivate"));
                } else {
                    labelAdd.setEnabled(true);
                    labelAdd.setToolTipText(null);
                }
            }
        });
#endif
        connect(labelAdd, SIGNAL(clicked(bool)), this, SLOT(onLabelAdd()));
        this->getContentPane()->layout()->addWidget(panel);
    }

    // Selection of the type of entity for the icon to represent is done from a combobox
    _addIconBox = new QComboBox();
    _addIconBox->setMinimumSize(QSize(75, 75));
    _addIconBox->setMaximumSize(QSize(200, 200));
#if 1
    ComboBoxItem* cbi = new ComboBoxItem("RightTurnout");
    _addIconBox->addItem(cbi->getName(), VPtr<ComboBoxItem>::asQVariant(cbi));
    cbi = new ComboBoxItem("LeftTurnout");
    _addIconBox->addItem(cbi->getName(), VPtr<ComboBoxItem>::asQVariant(cbi));
    cbi = new ComboBoxItem("SlipTOEditor");
    _addIconBox->addItem(cbi->getName(), VPtr<ComboBoxItem>::asQVariant(cbi));
    cbi = new ComboBoxItem("Sensor");
    _addIconBox->addItem(cbi->getName(), VPtr<ComboBoxItem>::asQVariant(cbi)); // NOI18N
    cbi = new ComboBoxItem("SignalHead");
    _addIconBox->addItem(cbi->getName(), VPtr<ComboBoxItem>::asQVariant(cbi));
    cbi = new ComboBoxItem("SignalMast");
    _addIconBox->addItem(cbi->getName(), VPtr<ComboBoxItem>::asQVariant(cbi));
    cbi = new ComboBoxItem("Memory");
    _addIconBox->addItem(cbi->getName(), VPtr<ComboBoxItem>::asQVariant(cbi));
    cbi = new ComboBoxItem("BlockLabel");
    _addIconBox->addItem(cbi->getName(), VPtr<ComboBoxItem>::asQVariant(cbi));
    cbi = new ComboBoxItem("Reporter");
    _addIconBox->addItem(cbi->getName(), VPtr<ComboBoxItem>::asQVariant(cbi));
    cbi = new ComboBoxItem("Light");
    _addIconBox->addItem(cbi->getName(), VPtr<ComboBoxItem>::asQVariant(cbi));
    cbi = new ComboBoxItem("Background");
    _addIconBox->addItem(cbi->getName(), VPtr<ComboBoxItem>::asQVariant(cbi));
    cbi = new ComboBoxItem("MultiSensor");
    _addIconBox->addItem(cbi->getName(), VPtr<ComboBoxItem>::asQVariant(cbi));
    cbi = new ComboBoxItem("RPSreporter");
    _addIconBox->addItem(cbi->getName(), VPtr<ComboBoxItem>::asQVariant(cbi));
    cbi = new ComboBoxItem("FastClock");
    _addIconBox->addItem(cbi->getName(), VPtr<ComboBoxItem>::asQVariant(cbi));
    cbi = new ComboBoxItem("Icon");
    _addIconBox->addItem(cbi->getName(), VPtr<ComboBoxItem>::asQVariant(cbi));
#endif
    _addIconBox->setCurrentIndex(-1);
    //_addIconBox->addItemListener(this);  // must be AFTER no selection is set
    connect(_addIconBox, SIGNAL(currentIndexChanged(int)), this, SLOT());
    QWidget* p1 = new QWidget();
    QVBoxLayout* p1Layout;
    p1->setLayout(p1Layout = new QVBoxLayout(p1/*, BoxLayout.Y_AXIS*/));
    QWidget* p2 = new QWidget();
    FlowLayout* p2Layout;
    p2->setLayout(p2Layout=new FlowLayout());
    p2Layout->addWidget(new QLabel(tr("selectTypeIcon")));
    p1Layout->addWidget(p2);
    p1Layout->addWidget(_addIconBox);
    contentPane->layout()->addWidget(p1);

    // edit, position, control controls
    {
        // edit mode item
        contentPane->layout()->addWidget(editableBox);
//        editableBox.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent event) {
//                setAllEditable(editableBox.isSelected());
//                hiddenCheckBoxListener();
//            }
//        });
        connect(editableBox, SIGNAL(clicked()), this, SLOT());
        editableBox->setChecked(isEditable());
        // positionable item
        contentPane->layout()->addWidget(positionableBox);
//        positionableBox.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent event) {
//                setAllPositionable(positionableBox.isSelected());
//            }
//        });
        connect(positionableBox, SIGNAL(clicked()), this, SLOT());
        positionableBox->setChecked(allPositionable());
        // controlable item
        contentPane->layout()->addWidget(controllingBox);
//        controllingBox.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent event) {
//                setAllControlling(controllingBox.isSelected());
//            }
//        });
        connect(controllingBox, SIGNAL(clicked()), this, SLOT());
        controllingBox->setChecked(allControlling());
        // hidden item
        contentPane->layout()->addWidget(hiddenBox);
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
        contentPane->layout()->addWidget(showTooltipBox);
//        showTooltipBox.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
//                setAllShowToolTip(showTooltipBox.isSelected());
//            }
//        });
        connect(showTooltipBox, SIGNAL(clicked(bool)), this, SLOT());
        showTooltipBox->setChecked(showToolTip());

        contentPane->layout()->addWidget(menuBox);
//        menuBox.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
//                setPanelMenuVisible(menuBox.isSelected());
//            }
//        });
        connect(menuBox, SIGNAL(clicked(bool)), this, SLOT());
        menuBox->setChecked(true);
#if 0
        // Show/Hide Scroll Bars
        QWidget* scrollPanel = new JPanel();
        scrollPanel.setLayout(new FlowLayout());
        scrollableLabel.setLabelFor(scrollableComboBox);
        scrollPanel.add(scrollableLabel);
        scrollPanel.add(scrollableComboBox);
        contentPane.add(scrollPanel);
        scrollableComboBox.addItem(tr("ScrollNone"));
        scrollableComboBox.addItem(tr("ScrollBoth"));
        scrollableComboBox.addItem(tr("ScrollHorizontal"));
        scrollableComboBox.addItem(tr("ScrollVertical"));
        scrollableComboBox.setSelectedIndex(SCROLL_BOTH);
        scrollableComboBox.addActionListener(new ActionListener() {
            @Override
            /*public*/ void actionPerformed(ActionEvent e) {
                setScroll(scrollableComboBox.getSelectedIndex());
            }
        });
#endif
    }
    // register the resulting panel for later configuration
    ConfigureManager* cm = static_cast<ConfigureManager*>(InstanceManager::getNullableDefault("ConfigureManager"));
    if (cm != nullptr) {
        cm->registerUser(this);
    }
#if 0
    // when this window closes, set contents of target uneditable
    addWindowListener(new java.awt.event.WindowAdapter() {

        HashMap<String, JFrameItem> iconAdderFrames;

        @Override
        /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
            Iterator<JFrameItem> iter = iconAdderFrames.values().iterator();
            while (iter.hasNext()) {
                JFrameItem frame = iter.next();
                frame.dispose();
            }
        }

        WindowAdapter init(HashMap<String, JFrameItem> f) {
            iconAdderFrames = f;
            return this;
        }
    }.init(_iconEditorFrame));
#endif
    PEWindowListener* wl = new PEWindowListener(this);
    wl->init(_iconEditorFrame);
    addWindowListener(wl );
    // and don't destroy the window
    setDefaultCloseOperation(JDialog::HIDE_ON_CLOSE);
    // move this editor panel off the panel's position
//    getTargetFrame()->setLocationRelativeTo(this);
    getTargetFrame()->pack();
    getTargetFrame()->setVisible(true);

    editScene = new EditScene(QRectF(0, 0, 600, 400), this);
    //_targetPanel = editScene;

    editPanel->setScene(editScene);
    connect(editScene, SIGNAL(sceneMouseMove(QGraphicsSceneMouseEvent*)), this, SLOT(mouseMoved(QGraphicsSceneMouseEvent*)));
    connect(editScene, SIGNAL(sceneMousePress(QGraphicsSceneMouseEvent*)), this, SLOT(mousePressed(QGraphicsSceneMouseEvent*)));
    connect(editScene, SIGNAL(sceneMouseRelease(QGraphicsSceneMouseEvent*)), this, SLOT(mouseReleased(QGraphicsSceneMouseEvent*)));
    connect(editScene, SIGNAL(sceneMouseRelease(QGraphicsSceneMouseEvent*)), this, SLOT(mouseClicked(QGraphicsSceneMouseEvent*)));
    connect(editScene, SIGNAL(sceneMouseMove(QGraphicsSceneMouseEvent*)), this, SLOT(mouseDragged(QGraphicsSceneMouseEvent*)));
    connect(editScene, SIGNAL(sceneDropEvent(QGraphicsSceneDragDropEvent*)), this, SLOT(sceneDropEvent(QGraphicsSceneDragDropEvent*)));

    log->debug("PanelEditor ctor done.");
}  // end ctor

/*public*/ PEWindowListener::PEWindowListener(NewPanelEditor *panel) { this->panel = panel;}
//@Override
/*public*/ void PEWindowListener::windowClosing(QCloseEvent* e) {
    QListIterator<JFrameItem*> iter(iconAdderFrames->values());
    while (iter.hasNext()) {
        JFrameItem* frame = iter.next();
        frame->dispose();
    }
}

PEWindowListener* PEWindowListener::init(QHash<QString, JFrameItem*>* f) {
    iconAdderFrames = f;
    return this;
}

void NewPanelEditor::onStoreIndexItem()
{
 static_cast<CatalogTreeManager*>(InstanceManager::getDefault("CatalogTreeManager"))->storeImageIndex();
}

void NewPanelEditor::onLabelAdd()
{
 addLabel(nextLabel->text());
}

void NewPanelEditor::onRename()
{
 // prompt for name
 QString newName = JOptionPane::showInputDialog(nullptr, tr("PromptNewName"));
 if (newName == nullptr) {
     return;  // cancelled
 }
 if (static_cast<PanelMenu*>(InstanceManager::getDefault("PanelMenu"))->isPanelNameUsed(newName)) {
     JOptionPane::showMessageDialog(nullptr, tr("CanNotRename"), tr("PanelExist"),
             JOptionPane::ERROR_MESSAGE);
     return;
 }
 if (((QWidget*)getTargetPanel()->parent())->window() != nullptr) {
     ((JFrame*)((QWidget*) getTargetPanel())->window())->setTitle(newName);
 }
 setTitle();
 static_cast<PanelMenu*>(InstanceManager::getDefault("PanelMenu"))->renameEditorPanel(this);
}

/**
 * Initializes the hiddencheckbox and its listener. This has been taken out
 * of the init, as checkbox is enable/disabled by the editableBox.
 */
/*private*/ void NewPanelEditor::hiddenCheckBoxListener() {
    setShowHidden(hiddenBox->isChecked());
    if (editableBox->isChecked()) {
        hiddenBox->setEnabled(false);
        hiddenBox->setChecked(true);
    } else {
        hiddenBox->setEnabled(true);
//        hiddenBox.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent event) {
//                setShowHidden(hiddenBox.isSelected());
//            }
//        });
        connect(hiddenBox, SIGNAL(clicked(bool)), this, SLOT());
    }

}

/**
 * After construction, initialize all the widgets to their saved config
 * settings.
 */
//@Override
/*public*/ void NewPanelEditor::initView() {
    editableBox->setChecked(isEditable());
    positionableBox->setChecked(allPositionable());
    controllingBox->setChecked(allControlling());
    //showCoordinatesBox.setSelected(showCoordinates());
    showTooltipBox->setChecked(showToolTip());
    hiddenBox->setChecked(showHidden());
    menuBox->setChecked(getTargetFrame()->menuBar()->isVisible());
}

//static class ComboBoxItem {

//    /*private*/ /*final*/ String name;
//    /*private*/ String bundleName;

    /*protected*/ NewPanelEditor::ComboBoxItem::ComboBoxItem(QString n) {
        name = n;
    }

    /*protected*/ QString  NewPanelEditor::ComboBoxItem::getName() {
        return name;
    }

    //@Override
    /*public*/ QString  NewPanelEditor::ComboBoxItem::toString() {
        // I18N split Bundle name
        // use NamedBeanBundle property for basic beans like "Turnout" I18N
        if ("Sensor"== (name)) {
            bundleName = "BeanNameSensor";
        } else if ("SignalHead" == (name)) {
            bundleName = "BeanNameSignalHead";
        } else if ("SignalMast" == (name)) {
            bundleName = "BeanNameSignalMast";
        } else if ("Memory" == (name)) {
            bundleName = "BeanNameMemory";
        } else if ("Reporter" == (name)) {
            bundleName = "BeanNameReporter";
        } else if ("Light" == (name)) {
            bundleName = "BeanNameLight";
        } else {
            bundleName = name;
        }
        return /*tr*/(bundleName); // use NamedBeanBundle property for basic beans like "Turnout" I18N
    }
//};

/*
 * itemListener for JComboBox.
 */
//@Override
/*public*/ void NewPanelEditor::itemStateChanged(/*ItemEvent e*/) {
    //if (e.getStateChange() == ItemEvent.SELECTED) {
        ComboBoxItem* item = VPtr<ComboBoxItem>::asPtr(_addIconBox->currentData());//(ComboBoxItem) e.getItem();
        QString name = item->getName();
        JFrameItem* frame = Editor::getIconFrame(name);
        if (frame != nullptr) {
            frame->getEditor()->reset();
            frame->setVisible(true);
        } else {
            if (name == ("FastClock")) {
                addClock();
            } else if (name == ("RPSreporter")) {
                addRpsReporter();
            } else {
                log->error(tr("Unable to open Icon Editor \"%1\"").arg(item->getName()));
            }
        }
        _addIconBox->setCurrentIndex(-1);
    //}
}

/**
 * Handle close of editor window.
 * <p>
 * Overload/override method in JmriJFrame parent, which by default is
 * permanently closing the window. Here, we just want to make it invisible,
 * so we don't dispose it (yet).
 */
//@Override
/*public*/ void NewPanelEditor::windowClosing(QCloseEvent* e) {
    setVisible(false);
}

/**
 * Create sequence of panels, etc, for layout: JFrame contains its
 * ContentPane which contains a JPanel with BoxLayout (p1) which contains a
 * JScollPane (js) which contains the targetPane
 *
 */
/*public*/ JmriJFrame* NewPanelEditor::makeFrame(QString name) {
    JmriJFrame* targetFrame = new JmriJFrame(name);
    targetFrame->setVisible(false);

    QMenuBar* menuBar = new QMenuBar();
    QMenu* editMenu = new QMenu(tr("MenuEdit"));
    menuBar->addMenu(editMenu);
//    editMenu.add(new AbstractAction(tr("OpenEditor")) {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            setVisible(true);
//        }
//    });
    QAction* openEditorAct = new QAction(tr("Open Editor"), this);
 connect(openEditorAct, SIGNAL(triggered(bool)), this, SLOT(onOpenEditor()));
    editMenu->addSeparator();
//    editMenu.add(new AbstractAction(tr("DeletePanel")) {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            if (deletePanel()) {
//                dispose();
//            }
//        }
//    });
 AbstractAction* deletePanelAct = new AbstractAction(tr("DeletePanel"),this);
 connect(deletePanelAct, SIGNAL(triggered(bool)), this, SLOT(onDeletePanel()));
    targetFrame->setMenuBar(menuBar);
    // add maker menu
    QMenu* markerMenu = new QMenu(tr("MenuMarker"));
    menuBar->addMenu(markerMenu);
//    markerMenu.add(new AbstractAction(tr("AddLoco")) {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            locoMarkerFromInput();
//        }
//    });
 AbstractAction* addLocoAct = new AbstractAction(tr("AddLoco"), this);
 connect(addLocoAct, SIGNAL(triggered()), this, SLOT(onAddLoco()));
//    markerMenu.add(new AbstractAction(tr("AddLocoRoster")) {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            locoMarkerFromRoster();
//        }
//    });
 AbstractAction* addLocoRosterAct = new AbstractAction(tr("AddLocoRoster"),this);
 connect(addLocoRosterAct, SIGNAL(triggered(bool)),this, SLOT(onAddLocoRoster()));
//    markerMenu.add(new AbstractAction(tr("RemoveMarkers"), this) {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            removeMarkers();
//        }
//    });
 AbstractAction* removeMarkersAct = new AbstractAction(tr("RemoveMarkers"),this);
connect(removeMarkersAct, SIGNAL(triggered(bool)),this, SLOT(onRemoveMarkers()));
    QMenu* warrantMenu =  WarrantTableAction::makeWarrantMenu(isEditable(), this);
    if (warrantMenu != nullptr) {
        menuBar->addMenu(warrantMenu);
    }

    targetFrame->addHelpMenu("package.jmri.jmrit.display.PanelTarget", true);
    return targetFrame;
}
void NewPanelEditor::onOpenEditor()
{
 setVisible(true);
}

void NewPanelEditor::onDeletePanel()
{
 if (deletePanel()) {
//     dispose();
 }
}

void NewPanelEditor::onAddLoco()
{
 locoMarkerFromInput();
}

void NewPanelEditor::onAddLocoRoster()
{
 locoMarkerFromRoster();
}

void NewPanelEditor::onRemoveMarkers()
{
 removeMarkers();
}


/**
 * ************* implementation of Abstract Editor methods **********
 */

/**
 * The target window has been requested to close, don't delete it at this
 * time. Deletion must be accomplished via the Delete this panel menu item.
 */
//@Override
/*protected*/ void NewPanelEditor::targetWindowClosingEvent(QCloseEvent* e) {
    targetWindowClosing(true);
}
#if 0
/**
 * Called from TargetPanel's paint method for additional drawing by editor
 * view
 */
@Override
protected void paintTargetPanel(Graphics g) {
    /*Graphics2D g2 = (Graphics2D)g;
     drawPositionableLabelBorder(g2);*/
}
#endif
/**
 * Set an object's location when it is created.
 */
//@Override
/*protected*/ void NewPanelEditor::setNextLocation(Positionable* obj) {
    int x = nextX->text().toInt();
    int y = nextY->text().toInt();
    obj->setLocation(x, y);
}

/**
 * Create popup for a Positionable object Popup items common to all
 * positionable objects are done before and after the items that pertain
 * only to specific Positionable types.
 */
//@Override
/*protected*/ void NewPanelEditor::showPopUp(Positionable* p, QGraphicsSceneMouseEvent* event) {
#if 0
    if (!((JComponent) p).isVisible()) {
        return;     // component must be showing on the screen to determine its location
    }
    JPopupMenu popup = new JPopupMenu();
    PositionablePopupUtil util = p.getPopupUtility();
    if (p.isEditable()) {
        // items for all Positionables
        if (p.doViemMenu()) {
            popup.add(p.getNameString());
            setPositionableMenu(p, popup);
            if (p.isPositionable()) {
                setShowCoordinatesMenu(p, popup);
                setShowAlignmentMenu(p, popup);
            }
            setDisplayLevelMenu(p, popup);
            setHiddenMenu(p, popup);
            popup.addSeparator();
        }

        // Positionable items with defaults or using overrides
        boolean popupSet = false;
        popupSet |= p.setRotateOrthogonalMenu(popup);
        popupSet |= p.setRotateMenu(popup);
        popupSet |= p.setScaleMenu(popup);
        if (popupSet) {
            popup.addSeparator();
            popupSet = false;
        }
        popupSet = p.setEditIconMenu(popup);
        if (popupSet) {
            popup.addSeparator();
            popupSet = false;
        }
        popupSet = p.setTextEditMenu(popup);
        if (util != null) {
            util.setFixedTextMenu(popup);
            util.setTextMarginMenu(popup);
            util.setTextBorderMenu(popup);
            util.setTextFontMenu(popup);
            util.setBackgroundMenu(popup);
            util.setTextJustificationMenu(popup);
            util.setTextOrientationMenu(popup);
            util.copyItem(popup);
            popup.addSeparator();
            util.propertyUtil(popup);
            util.setAdditionalEditPopUpMenu(popup);
            popupSet = true;
        }
        if (popupSet) {
            popup.addSeparator();
            popupSet = false;
        }
        p.setDisableControlMenu(popup);

        // for Positionables with unique item settings
        p.showPopUp(popup);

        setRemoveMenu(p, popup);
    } else {
        p.showPopUp(popup);
        if (util != null) {
            util.setAdditionalViewPopUpMenu(popup);
        }
    }
    popup.show((Component) p, p.getWidth() / 2, p.getHeight() / 2);
#endif
}

/**
 * ***************************************************
 */

//@Override
/*public*/ void NewPanelEditor::mousePressed(QGraphicsSceneMouseEvent* event) {
 bool bRightButton = ((event->buttons())&Qt::RightButton)==Qt::RightButton;
 bool bShift = ((event->modifiers())&Qt::ShiftModifier) == Qt::ShiftModifier;
 bool bMeta = ((event->modifiers())&Qt::MetaModifier) == Qt::MetaModifier;
 bool bAlt = ((event->modifiers())&Qt::AltModifier) == Qt::AltModifier;
 bool bCtrl = ((event->modifiers())&Qt::ControlModifier) == Qt::ControlModifier;

    setToolTip(""); // ends tooltip if displayed
    if (log->isDebugEnabled()) {
        log->debug(tr("mousePressed at (%1,%2) _dragging= %3").arg(event->scenePos().x()).arg(event->scenePos().y(), _dragging));
    }
    _anchorX = event->scenePos().x();
    _anchorY = event->scenePos().y();
    _lastX = _anchorX;
    _lastY = _anchorY;
#if 1
    QList<Positionable*>* selections = getSelectedItems(event);
    if (_dragging) {
        return;
    }

    if (selections->size() > 0) {
        if (/*event.isShiftDown()*/bShift && selections->size() > 1) {
            _currentSelection = selections->value(1);
        } else {
            _currentSelection = selections->value(0);
        }
        if (/*event.isPopupTrigger()*/bRightButton) {
            log->debug("mousePressed calls showPopUp");
            if (/*event.isMetaDown()*/bMeta || /*event.isAltDown()*/bAlt) {
                // if requesting a popup and it might conflict with moving, delay the request to mouseReleased
                delayedPopupTrigger = true;
            } else {
                // no possible conflict with moving, display the popup now
                if (_selectionGroup != nullptr) {
                    //Will show the copy option only
                    showMultiSelectPopUp(event, _currentSelection);
                } else {
                    showPopUp(_currentSelection, event);
                }
            }
        } else if (!bCtrl) {
            _currentSelection->doMousePressed(event);
            if (_multiItemCopyGroup != nullptr && !_multiItemCopyGroup->contains(_currentSelection)) {
                _multiItemCopyGroup = nullptr;
            }
            // _selectionGroup = null;
        }
    } else {
        if (bRightButton) {
            if (/*event.isMetaDown()*/bMeta || /*event.isAltDown()*/bAlt) {
                // if requesting a popup and it might conflict with moving, delay the request to mouseReleased
                delayedPopupTrigger = true;
            } else {
                if (_multiItemCopyGroup != nullptr) {
                    pasteItemPopUp(event);
                } else if (_selectionGroup != nullptr) {
                    showMultiSelectPopUp(event, _currentSelection);
                } else {
                    backgroundPopUp(event);
                    _currentSelection = nullptr;
                }
            }
        } else {
            _currentSelection = nullptr;
        }
    }
    // if ((event.isControlDown() || _selectionGroup!=null) && _currentSelection!=null){
    if ((/*event.isControlDown()*/bCtrl) || /*event.isMetaDown()*/bMeta || /*event.isAltDown()*/bAlt) {
        //Don't want to do anything, just want to catch it, so that the next two else ifs are not
        //executed
    } else if ((_currentSelection == nullptr && _multiItemCopyGroup == nullptr)
            || (_selectRect != QRectF() && !_selectRect.contains(_anchorX, _anchorY))) {
        _selectRect = QRectF(_anchorX, _anchorY, 0, 0);
        _selectionGroup = nullptr;
    } else {
        _selectRect = QRectF();
        _selectionGroup = nullptr;
    }
#endif
    _targetPanel->repaint(); // needed for ToolTip
}

//@Override
/*public*/ void NewPanelEditor::mouseReleased(QGraphicsSceneMouseEvent* event) {
 bool bRightButton = ((event->buttons())&Qt::RightButton)==Qt::RightButton;
 bool bShift = ((event->modifiers())&Qt::ShiftModifier) == Qt::ShiftModifier;
 bool bMeta = ((event->modifiers())&Qt::MetaModifier) == Qt::MetaModifier;
 bool bAlt = ((event->modifiers())&Qt::AltModifier) == Qt::AltModifier;
 bool bCtrl = ((event->modifiers())&Qt::ControlModifier) == Qt::ControlModifier;

 setToolTip(""); // ends tooltip if displayed
    if (log->isDebugEnabled()) {
        log->debug(QString("mouseReleased at (") + event->scenePos().x() + "," + event->scenePos().y() + ") dragging= " + (_dragging?"true":"false")
                + " selectRect is " + (_selectRect == QRectF() ? "null" : "not null"));
    }
#if 1
    QList<Positionable*>* selections = getSelectedItems(event);

    if (_dragging) {
        mouseDragged(event);
    }
    if (selections->size() > 0) {
        if (/*event.isShiftDown()*/bShift && selections->size() > 1) {
            _currentSelection = selections->value(1);
        } else {
            _currentSelection = selections->value(0);
        }
        if (_multiItemCopyGroup != nullptr && !_multiItemCopyGroup->contains(_currentSelection)) {
            _multiItemCopyGroup = nullptr;
        }
    } else {
        if ((/*event.isPopupTrigger() */bRightButton|| delayedPopupTrigger) && !_dragging) {
            if (_multiItemCopyGroup != nullptr) {
                pasteItemPopUp(event);
            } else {
                backgroundPopUp(event);
                _currentSelection = nullptr;
            }
        } else {
            _currentSelection = nullptr;

        }
    }
    /*if (event.isControlDown() && _currentSelection!=null && !event.isPopupTrigger()){
     amendSelectionGroup(_currentSelection, event);*/
    if ((/*event.isPopupTrigger()*/bRightButton || delayedPopupTrigger) && _currentSelection != nullptr && !_dragging) {
        if (_selectionGroup != nullptr) {
            //Will show the copy option only
            showMultiSelectPopUp(event, _currentSelection);

        } else {
            showPopUp(_currentSelection, event);
        }
    } else {
        if (_currentSelection != nullptr && !_dragging && !/*event.isControlDown()*/bCtrl) {
            _currentSelection->doMouseReleased(event);
        }
        if (allPositionable() && _selectRect != QRectF()) {
            if (_selectionGroup == nullptr && _dragging) {
                makeSelectionGroup(event);
            }
        }
    }
    delayedPopupTrigger = false;
    _dragging = false;
    _selectRect = QRectF();
    // if not sending MouseClicked, do it here
//    if (jmri.util.swing.SwingSettings.getNonStandardMouseEvent()) {
//        mouseClicked(event);
//    }
#endif
    _targetPanel->repaint(); // needed for ToolTip
}

//@Override
/*public*/ void NewPanelEditor::mouseDragged(QGraphicsSceneMouseEvent* event) {
    setToolTip(""); // ends tooltip if displayed
#if 0
    if ((event.isPopupTrigger()) || (!event.isMetaDown() && !event.isAltDown())) {
        if (_currentSelection != null) {
            List<Positionable> selections = getSelectedItems(event);
            if (selections.size() > 0) {
                if (selections.get(0) != _currentSelection) {
                    _currentSelection.doMouseReleased(event);
                } else {
                    _currentSelection.doMouseDragged(event);
                }
            } else {
                _currentSelection.doMouseReleased(event);
            }
        }
        return;
    }
    moveIt:
    if (_currentSelection != null && getFlag(OPTION_POSITION, _currentSelection.isPositionable())) {
        int deltaX = event.getX() - _lastX;
        int deltaY = event.getY() - _lastY;
        int minX = getItemX(_currentSelection, deltaX);
        int minY = getItemY(_currentSelection, deltaY);
        if (_selectionGroup != null && _selectionGroup.contains(_currentSelection)) {
            for (Positionable comp : *_selectionGroup) {
                minX = Math.min(getItemX(comp, deltaX), minX);
                minY = Math.min(getItemY(comp, deltaY), minY);
            }
        }
        if (minX < 0 || minY < 0) {
            break moveIt;
        }
        if (_selectionGroup != null && _selectionGroup.contains(_currentSelection)) {
            for (Positionable comp : *_selectionGroup) {
                moveItem(comp, deltaX, deltaY);
            }
            _highlightcomponent = null;
        } else {
            moveItem(_currentSelection, deltaX, deltaY);
            _highlightcomponent = new Rectangle(_currentSelection.getX(), _currentSelection.getY(),
                    _currentSelection.maxWidth(), _currentSelection.maxHeight());
        }
    } else {
        if (allPositionable() && _selectionGroup == null) {
            drawSelectRect(event.getX(), event.getY());
        }
    }
    _dragging = true;
    _lastX = event.getX();
    _lastY = event.getY();
#endif
    _targetPanel->repaint(); // needed for ToolTip
}

//@Override
/*public*/ void NewPanelEditor::mouseMoved(QGraphicsSceneMouseEvent* event) {
 bool bRightButton = ((event->buttons())&Qt::RightButton)==Qt::RightButton;
 bool bShift = ((event->modifiers())&Qt::ShiftModifier) == Qt::ShiftModifier;
 bool bMeta = ((event->modifiers())&Qt::MetaModifier) == Qt::MetaModifier;
 Q_UNUSED(bMeta);
 bool bAlt = ((event->modifiers())&Qt::AltModifier) == Qt::AltModifier;
 Q_UNUSED(bAlt);
 bool bCtrl = ((event->modifiers())&Qt::ControlModifier) == Qt::ControlModifier;

#if 1
    // log.debug("mouseMoved at ({},{})", event.getX(), event.getY());
    if (_dragging || /*event.isPopupTrigger()*/bRightButton) {
        return;
    }

    QList<Positionable*>* selections = getSelectedItems(event);
    Positionable* selection = nullptr;
    if (selections->size() > 0) {
        if (/*event.isShiftDown()*/bShift && selections->size() > 1) {
            selection = selections->value(1);
        } else {
            selection = selections->value(0);
        }
    }
    if (isEditable() && selection != nullptr && selection->getDisplayLevel() > BKG) {
        _highlightcomponent = QRectF(selection->getX(), selection->getY(), selection->maxWidth(), selection->maxHeight());
        _targetPanel->repaint();
    } else {
        _highlightcomponent = QRectF();
        _targetPanel->repaint();
    }
    if (selection != nullptr && selection->getDisplayLevel() > BKG && selection->showToolTip()) {
        showToolTip(selection, event);
        //selection.highlightlabel(true);
        _targetPanel->repaint();
    } else {
        setToolTip(nullptr);
        _highlightcomponent = QRectF();
        _targetPanel->repaint();
    }
#endif
}

//@Override
/*public*/ void NewPanelEditor::mouseClicked(QGraphicsSceneMouseEvent* event) {
 bool bRightButton = ((event->buttons())&Qt::RightButton)==Qt::RightButton;
 bool bShift = ((event->modifiers())&Qt::ShiftModifier) == Qt::ShiftModifier;
 bool bMeta = ((event->modifiers())&Qt::MetaModifier) == Qt::MetaModifier;
 Q_UNUSED(bMeta);
 bool bAlt = ((event->modifiers())&Qt::AltModifier) == Qt::AltModifier;
 Q_UNUSED(bAlt);
 bool bCtrl = ((event->modifiers())&Qt::ControlModifier) == Qt::ControlModifier;

    setToolTip(""); // ends tooltip if displayed
    if (log->isDebugEnabled()) {
        log->debug(tr("mouseClicked at (%1,%2) dragging= %3 selectRect is %4").arg(
                event->scenePos().x()).arg(event->scenePos().y()).arg(_dragging).arg((_selectRect == QRectF()) ? "null" : "not null"));
    }
#if 1
    QList<Positionable*>* selections = getSelectedItems(event);

    if (selections->size() > 0) {
        if (/*event.isShiftDown()*/bShift && selections->size() > 1) {
            _currentSelection = selections->value(1);
        } else {
            _currentSelection = selections->value(0);
        }
    } else {
        _currentSelection = nullptr;
        if (/*event.isPopupTrigger()*/bRightButton) {
            if (_multiItemCopyGroup == nullptr) {
                pasteItemPopUp(event);
            } else {
                backgroundPopUp(event);
            }
        }
    }
    if (/*event.isPopupTrigger()*/bRightButton && _currentSelection != nullptr && !_dragging) {
        if (_selectionGroup != nullptr) {
            showMultiSelectPopUp(event, _currentSelection);
        } else {
            showPopUp(_currentSelection, event);
        }
        // _selectionGroup = null; // Show popup only works for a single item

    } else {
        if (_currentSelection != nullptr && !_dragging && !/*event.isControlDown()*/bCtrl) {
            _currentSelection->doMouseClicked(event);
        }
    }
    _targetPanel->repaint(); // needed for ToolTip
    if (/*event.isControlDown()*/bCtrl && _currentSelection != nullptr && !/*event.isPopupTrigger()*/bRightButton) {
        amendSelectionGroup(_currentSelection);
    }
#endif
}

//@Override
/*public*/ void NewPanelEditor::mouseEntered(QGraphicsSceneMouseEvent* event) {
}

//@Override
/*public*/ void NewPanelEditor::mouseExited(QGraphicsSceneMouseEvent* event) {
    setToolTip("");
    _targetPanel->repaint();  // needed for ToolTip
}


//@Override
/*protected*/ void NewPanelEditor::copyItem(Positionable* p) {
    _multiItemCopyGroup = new QList<Positionable*>();
    _multiItemCopyGroup->append(p);
}

/*protected*/ void NewPanelEditor::pasteItemPopUp(/*final*/ QGraphicsSceneMouseEvent* event) {
    if (!isEditable()) {
        return;
    }
    if (_multiItemCopyGroup == nullptr) {
        return;
    }
    QMenu* popup = new QMenu();
    QAction* edit = new QAction(tr("MenuItemPaste"), this);
//    edit.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            pasteItem(event);
//        }
//    });
    connect(edit, SIGNAL(triggered(bool)), this, SLOT(onEdit()));
    setBackgroundMenu(popup);
    showAddItemPopUp(event, popup);
    popup->addAction(edit);
//    popup->show(event->getComponent(), event->x(), event->y());
    popup->exec(QCursor::pos());
}

/*protected*/ void NewPanelEditor::backgroundPopUp(QGraphicsSceneMouseEvent* event) {
    if (!isEditable()) {
        return;
    }
    QMenu* popup = new QMenu();
    setBackgroundMenu(popup);
    showAddItemPopUp(event, popup);
//    popup->show(event->getComponent(), event->x(), event->y());
}

/*protected*/ void NewPanelEditor::showMultiSelectPopUp(/*final*/ QGraphicsSceneMouseEvent* event, Positionable* p) {
    QMenu* popup = new QMenu();
    QAction* copy = new QAction(tr("MenuItemCopy"),this); // changed "edit" to "copy"
    if (p->isPositionable()) {
        setShowAlignmentMenu(p, popup);
    }
//    copy.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            _multiItemCopyGroup = new QList<Positionable*>();
//            // must make a copy or pasteItem() will hang
//            if (_selectionGroup != nullptr) {
//                for (Positionable* comp : *_selectionGroup) {
//                    _multiItemCopyGroup->append(comp);
//                }
//            }
//        }
//    });
    connect(copy, SIGNAL(triggered(bool)), this, SLOT(onCopy()));
    setMultiItemsPositionableMenu(popup); // adding Lock Position for all
    // selected items

    setRemoveMenu(p, popup);
    //showAddItemPopUp(event, popup); // no need to Add when group selected
    popup->addAction(copy);
//    popup.show(event.getComponent(), event.getX(), event.getY());
}
void NewPanelEditor::onCopy()
{
 _multiItemCopyGroup = new QList<Positionable*>();
 // must make a copy or pasteItem() will hang
 if (_selectionGroup != nullptr) {
     for (Positionable* comp : *_selectionGroup) {
         _multiItemCopyGroup->append(comp);
     }
 }

}
/*protected*/ void NewPanelEditor::showAddItemPopUp(/*final*/ QGraphicsSceneMouseEvent* event, QMenu* popup) {
    if (!isEditable()) {
        return;
    }
    QMenu* _add = new QMenu(tr("MenuItemAddItem"));
    // for items in the following list, I18N is picked up later on
    addItemPopUp(new ComboBoxItem("RightTurnout"), _add);
    addItemPopUp(new ComboBoxItem("LeftTurnout"), _add);
    addItemPopUp(new ComboBoxItem("SlipTOEditor"), _add);
    addItemPopUp(new ComboBoxItem("Sensor"), _add);
    addItemPopUp(new ComboBoxItem("SignalHead"), _add);
    addItemPopUp(new ComboBoxItem("SignalMast"), _add);
    addItemPopUp(new ComboBoxItem("Memory"), _add);
    addItemPopUp(new ComboBoxItem("BlockLabel"), _add);
    addItemPopUp(new ComboBoxItem("Reporter"), _add);
    addItemPopUp(new ComboBoxItem("Light"), _add);
    addItemPopUp(new ComboBoxItem("Background"), _add);
    addItemPopUp(new ComboBoxItem("MultiSensor"), _add);
    addItemPopUp(new ComboBoxItem("RPSreporter"), _add);
    addItemPopUp(new ComboBoxItem("FastClock"), _add);
    addItemPopUp(new ComboBoxItem("Icon"), _add);
    addItemPopUp(new ComboBoxItem("Text"), _add);
    popup->addMenu(_add);
}

/*protected*/ void NewPanelEditor::addItemPopUp(/*final*/ ComboBoxItem* item, QMenu* menu) {
#if 0 // done
    ActionListener a = new ActionListener() {
        ///*final*/ String desiredName = name;
        @Override
        /*public*/ void actionPerformed(ActionEvent e) {
            addItemViaMouseClick = true;
            getIconFrame(item.getName());
        }
//            ComboBoxItem selected;

        ActionListener init(ComboBoxItem i) {
//                selected = i;
            return this;
        }
    }.init(item);
#endif
    AddItemPopupActionListener* a = new AddItemPopupActionListener(this);
    a->init(item);

    QAction* addto = new QAction(item->toString());
    //addto->addActionListener(a);
    connect(addto, SIGNAL(triggered(bool)), a, SLOT(actionPerformed()));
    menu->addAction(addto);
}


//@Override
/*public*/ void NewPanelEditor::putItem(Positionable* l) {
    Editor::putItem(l);
    /*This allows us to catch any new items that are being pasted into the panel
     and add them to the selection group, so that the user can instantly move them around*/
    //!!!
    if (pasteItemFlag) {
        amendSelectionGroup(l);
        return;
    }
    if (addItemViaMouseClick) {
        addItemViaMouseClick = false;
        l->setLocation(_lastX, _lastY);
    }
}

/*private*/ void NewPanelEditor::amendSelectionGroup(Positionable* p) {
    if (p == nullptr) {
        return;
    }
    if (_selectionGroup == nullptr) {
        _selectionGroup = new QList<Positionable*>();
    }
    bool removed = false;
    for (int i = 0; i < _selectionGroup->size(); i++) {
        if (_selectionGroup->value(i) == p) {
            _selectionGroup->removeAt(i);
            removed = true;
            break;
        }
    }
    if (!removed) {
        _selectionGroup->append(p);
    } else if (removed && _selectionGroup->isEmpty()) {
        _selectionGroup = nullptr;
    }
    _targetPanel->repaint();
}


/*protected*/ void NewPanelEditor::pasteItem(QGraphicsSceneMouseEvent* e) {
    pasteItemFlag = true;
    XmlAdapter adapter;
    QString className;
    int x;
    int y;
    int xOrig;
    int yOrig;
#if 0
    if (_multiItemCopyGroup != nullptr) {
        QWidget* copied;
        int xoffset;
        int yoffset;
        x = _multiItemCopyGroup->value(0)->x();
        y = _multiItemCopyGroup->value(0)->y();
        xoffset = e->scenePos().x() - x;
        yoffset = e->scenePos().y() - y;
        /*We make a copy of the selected items and work off of that copy
         as amendments are made to the multiItemCopyGroup during this process
         which can result in a loop*/
        QList<Positionable*>* _copyOfMultiItemCopyGroup = new QList<Positionable*>(_multiItemCopyGroup);
        Collections.copy(_copyOfMultiItemCopyGroup, _multiItemCopyGroup);
        for (Positionable* comp : *_copyOfMultiItemCopyGroup) {
            copied = (QWidget*) comp;
            xOrig = copied.x();
            yOrig = copied.getY();
            x = xOrig + xoffset;
            y = yOrig + yoffset;
            if (x < 0) {
                x = 1;
            }
            if (y < 0) {
                y = 1;
            }
            className = ConfigXmlManager.adapterName(copied);
            copied.setLocation(x, y);
            try {
                adapter = (XmlAdapter*) Class::forName(className)->newInstance();
                QDomElement el = adapter.store(copied);
                adapter.load(el, this);
            } catch (ClassNotFoundException ex) //| InstantiationException | IllegalAccessException
//                | jmri.configurexml.JmriConfigureXmlException
//                | RuntimeException ex)
            {
                    log->debug(ex.getLocalizedMessage(), ex.getMessage());
            }
            /*We remove the original item from the list, so we end up with
             just the new items selected and allow the items to be moved around */
            amendSelectionGroup(comp);
            copied.setLocation(xOrig, yOrig);
        }
        _selectionGroup = nullptr;
    }
#endif
    pasteItemFlag = false;
    _targetPanel->repaint();
}

/**
 * Add an action to remove the Positionable item.
 */
//@Override
/*public*/ void NewPanelEditor::setRemoveMenu(Positionable* p, QMenu* popup) {
 QAction* act;
    popup->addAction(act =new AbstractAction(tr("Remove"), this));
  #if 0
    {
        Positionable comp;

        @Override
        /*public*/ void actionPerformed(ActionEvent e) {
            if (_selectionGroup == null) {
                comp.remove();
            } else {
                removeMultiItems();
            }
        }

        AbstractAction init(Positionable pos) {
            comp = pos;
            return this;
        }
    }.init(p));
#endif
}

/*private*/ void NewPanelEditor::removeMultiItems() {
    bool itemsInCopy = false;
    if (_selectionGroup == _multiItemCopyGroup) {
        itemsInCopy = true;
    }
    for (Positionable* comp : *_selectionGroup) {
        comp->remove();
    }
    //As we have removed all the items from the panel we can remove the group.
    _selectionGroup = nullptr;
    //If the items in the selection group and copy group are the same we need to
    //clear the copy group as the originals no longer exist.
    if (itemsInCopy) {
        _multiItemCopyGroup = nullptr;
    }
}

// This adds a single CheckBox in the PopupMenu to set or clear all the selected
// items "Lock Position" or Positionable setting, when clicked, all the items in
// the selection will be changed accordingly.
/*private*/ void NewPanelEditor::setMultiItemsPositionableMenu(QMenu* popup) {
    // This would do great with a "greyed" CheckBox if the multiple items have different states.
    // Then selecting the true or false state would force all to change to true or false

    QAction* lockItem = new QAction(tr("LockPosition"),this);
    lockItem->setCheckable(true);
    bool allSetToMove = false;  // used to decide the state of the checkbox shown
    int trues = 0;                 // used to see if all items have the same setting

    int size = _selectionGroup->size();

    for (int i = 0; i < size; i++) {
        Positionable* comp = _selectionGroup->value(i);

        if (!comp->isPositionable()) {
            allSetToMove = true;
            trues++;
        }

        lockItem->setChecked(allSetToMove);
#if 0
        lockItem.addActionListener(new ActionListener() {
            Positionable* comp;
            QCheckBoxMenuItem checkBox;

            @Override
            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
                comp.setPositionable(!checkBox.isSelected());
                setSelectionsPositionable(!checkBox.isSelected(), comp);
            }

            ActionListener init(Positionable pos, QCheckBoxMenuItem cb) {
                comp = pos;
                checkBox = cb;
                return this;
            }
        }.init(comp, lockItem));
#endif
    }
    // Add "~" to the Text when all items do not have the same setting,
    // until we get a "greyed" CheckBox ;) - GJM
    if ((trues != size) && (trues != 0)) {
        lockItem->setText("~ " + lockItem->text());
        // uncheck box if all not the same
        lockItem->setChecked(false);
    }
    popup->addAction(lockItem);
}

/*public*/ void NewPanelEditor::setBackgroundMenu(QMenu* popup) {
    // Panel background, not text background
    QAction* edit = new QAction(tr("FontBackgroundColor"), this);
//    edit.addActionListener((ActionEvent event) -> {
//        QColor desiredColor = JmriColorChooser::showDialog(this,
//                             tr("FontBackgroundColor"),
//                             getBackgroundColor());
//        if (desiredColor!=null ) {
//           setBackgroundColor(desiredColor);
//       }
//    });
    connect(edit, SIGNAL(triggered(bool)), this, SLOT(onEdit()));
    popup->addAction(edit);
}

void NewPanelEditor::onEdit()
{
#if 0
  QColor desiredColor = JmriColorChooser::showDialog(this,
                       tr("FontBackgroundColor"),
                       getBackgroundColor());
  if (desiredColor!=QColor())
  {
     setBackgroundColor(desiredColor);
 }
#endif
}

/*private*/ /*final*/ /*static*/ Logger* NewPanelEditor::log = LoggerFactory::getLogger("PanelEditor");

