#include "warrantframe.h"
#include "instancemanager.h"
#include "warrantmanager.h"
#include "warrant.h"
#include "jtextfield.h"
#include <QComboBox>
#include "blockorder.h"
#include "throttlesetting.h"
#include <QRadioButton>
#include <QBoxLayout>
#include "oblock.h"
#include "dcclocoaddress.h"
#include "borderlayout.h"
#include <QTabWidget>
#include <QThread>
#include "oblockmanager.h"
#include <QMessageBox>
#include "roster.h"
#include "rosterentry.h"
#include "opath.h"
#include "portal.h"
#include "savemenu.h"
#include <QMenuBar>
#include "warranttableaction.h"
#include "gridbagconstraints.h"
#include "flowlayout.h"
#include <QGroupBox>
#include <QButtonGroup>
#include <QRadioButton>
#include "picklistmodel.h"
#include "oblockmanager.h"
#include "warranttablemodel.h"
#include "rosterentry.h"
#include "tablecolumn.h"
#include "tablecolumnmodel.h"
#include "defaulttablecolumnmodel.h"
#include "speedutil.h"
#include "decimalformat.h"
#include "logix/learnthrottleframe.h"
#include "joptionpane.h"

#include <QSizePolicy>
//WarrantFrame::WarrantFrame(QWidget *parent) :
//    JmriJFrame(parent)
//{
//}
/**
 * WarrantFame creates and edits Warrants
 * <P>
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 * This class is a window for creating and editing Warrants.
 * <p>
 * @author	Pete Cressman  Copyright (C) 2009, 2010
 */
// /*public*/ class WarrantFrame extends jmri.util.JmriJFrame implements ActionListener, PropertyChangeListener {

    //static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.logix.WarrantBundle");
    /*static*/ int WarrantFrame::STRUT_SIZE = 10;
    /*static*/ int WarrantFrame::ROW_HEIGHT;
/*static*/ QColor WarrantFrame::myGreen =  QColor(0, 100, 0);


/**
*  Constructor for existing warrant
*/
/*public*/ WarrantFrame::WarrantFrame(QString warrantName, QWidget *parent) : WarrantRoute(parent)
{
 //super(false, false);
 init0();
 _warrant = ((WarrantManager*)InstanceManager::getDefault("WarrantManager"))->getWarrant(warrantName);
 _create = false;
 setup(_warrant);
 init();
 if (routeIsValid() != NULL) { findRoute(); }
}
/**
 * Constructor for opening an existing warrant for editing
 */
/*protected*/ WarrantFrame::WarrantFrame(Warrant* w)
{
 //super();
 init0();
 _saveWarrant = w;
 // temp unregistered version until editing is saved.
 _warrant = new Warrant(_saveWarrant->getSystemName(), _saveWarrant->getUserName());
 _create = false;
 setup(_saveWarrant);
 init();
 if (routeIsValid() != NULL)
 {
  findRoute();
 }
}
/**
*  Constructor for new warrant and GUI
*/
/*public*/ WarrantFrame::WarrantFrame(Warrant* warrant, bool create, QWidget *parent) : WarrantRoute( parent)
{
 //super(false, false);
 init0();
 _warrant = warrant;
 if (!create) {
     // this is a concatenation of warrants
     setup(_warrant);
     create = true;  // allows warrant to be registered
 } else {
     getRoster();    // also done in setup()
 }
 _create = create;
 init();
}
/*private*/ void WarrantFrame::init0()
{
 log = new Logger("WarrantFrame");
 _orders = new QList <BlockOrder*>();
 _throttleCommands = new QList <ThrottleSetting*>();
 _learnThrottle = NULL;
 _locoAddress = NULL;
  _originBlockBox = new JTextField();
 _destBlockBox = new JTextField();
 _viaBlockBox =  new JTextField();
 _avoidBlockBox =  new JTextField();
 _originPathBox = new QComboBox();
 _destPathBox = new QComboBox();
 _viaPathBox = new QComboBox();
 _avoidPathBox = new QComboBox();
 _originPortalBox = new QComboBox();     // exit
 _destPortalBox = new QComboBox();       // entrance
 _rosterBox = new QComboBox();
 _dccNumBox = new JTextField();
 _trainNameBox = new JTextField();
 _throttleFactorBox =  new JTextField();
 _runProtect = new QRadioButton(tr("RunProtected")/*, true*/);
 _runProtect->setChecked(true);
 _runBlind = new QRadioButton(tr("RunBlind")/*, false*/);
 _halt = new QRadioButton(tr("Halt")/*, false*/);
 _resume = new QRadioButton(tr("Resume")/*, false*/);
 _abort = new QRadioButton(tr("Abort")/*, false*/);
 _invisible = new QRadioButton();
  _statusBox = new JTextField(30);

  _searchDepth =  new JTextField();
  _searchStatus =  new JTextField();
  _maxBlocks = 20;
}

/**
 * Set up params from an existing warrant. note that _warrant is unregistered.
 * warrant may be registered.
 */
/*private*/ void WarrantFrame::setup(Warrant* warrant)
{
 _origin->setOrder(warrant->getfirstOrder());
 _destination->setOrder(warrant->getLastOrder());
 _via->setOrder(warrant->getViaOrder());
 _avoid->setOrder(warrant->getAvoidOrder());
 QList<BlockOrder*>* list = warrant->getBlockOrders();
 QList<BlockOrder*> orders = QList<BlockOrder*>(/*list.size()*/);
 for (int i = 0; i < list->size(); i++) {
     orders.append(new BlockOrder(list->at(i)));
 }
 setOrders(orders);      // makes copy

 QList<ThrottleSetting*>* tList = warrant->getThrottleCommands();
 for (int i = 0; i < tList->size(); i++) {
     ThrottleSetting* ts = new ThrottleSetting(tList->at(i));
     _throttleCommands->append(ts);
 }
 setTrainName(warrant->getTrainName());
 WarrantRoute::setTrainInfo(warrant->getTrainId());
 _warrant->setTrainName(warrant->getTrainName());
//        _warrant->setTrainId(warrant.getTrainId());
 _runBlind->setChecked(warrant->getRunBlind());
 _warrant->setRunBlind(warrant->getRunBlind());
}

/*private*/ void WarrantFrame::init()
{
// doSize(_originBlockBox, 500, 200);
// doSize(_destBlockBox, 500, 200);
// doSize(_viaBlockBox, 500, 200);
// doSize(_avoidBlockBox, 500, 200);
// doSize(_originPathBox, 500, 200);
// doSize(_destPathBox, 500, 200);
// doSize(_viaPathBox, 500, 200);
// doSize(_avoidPathBox, 500, 200);
// doSize(_originPortalBox, 500, 200);
// doSize(_destPortalBox, 500, 200);
// doSize(_searchDepth, 30, 10);
// doSize(_searchStatus, 50, 30);

// _routeModel = new RouteTableModel(this);
 _commandModel = new ThrottleTableModel(this);

 QWidget* contentPane = new QWidget();
 //contentPane->setLayout(new BorderLayout(5/*,5*/));
 QVBoxLayout* contentPaneLayout;
 contentPane->setLayout(contentPaneLayout = new QVBoxLayout);
 setCentralWidget(contentPane);
#if 1
    //((BorderLayout*)contentPane->layout())->addWidget(makeTopPanel(), BorderLayout::North);
 contentPaneLayout->addWidget(makeTopPanel(),0, Qt::AlignTop);

 _tabbedPane = new QTabWidget();
 _tabbedPane->setMinimumWidth(400);
 QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
 sizePolicy.setHorizontalStretch(0);
 sizePolicy.setVerticalStretch(0);
 sizePolicy.setHeightForWidth(_tabbedPane->sizePolicy().hasHeightForWidth());
 _tabbedPane->setSizePolicy(sizePolicy);
 //_tabbedPane->addTab(tr("Define Route"), makeFindRouteTabPanel());
 _tabbedPane->addTab(makeFindRouteTabPanel(), tr("Define Route"));
 //_tabbedPane.addTab(tr("Record/Playback Script"), makeSetPowerTabPanel());
 _tabbedPane->addTab(makeSetPowerTabPanel(),tr("Record/Playback Script"));
 contentPaneLayout->addWidget(_tabbedPane, /*BorderLayout::Center*/0, Qt::AlignCenter);

 contentPaneLayout->addWidget(makeEditableButtonPanel(), /*BorderLayout::South*/0, Qt::AlignBottom);
 if (_orders->size() > 0)
 {
     _tabbedPane->setCurrentIndex(1);
 }
#endif
 addWindowListener(new WFWindowListener(this));
// {
//             //@Override
//             public void windowClosing(java.awt.event.WindowEvent e) {
//                 close();
//             }
//         });
 makeMenus();
// setContentPane(contentPane);
 setCentralWidget(contentPane);
 setLocation(0,100);
 setVisible(true);
 adjustSize();
}

/*private*/ QWidget* WarrantFrame::makeTopPanel() {
    QWidget* topPanel = new QWidget();
    //topPanel.setLayout(new BoxLayout(topPanel, BoxLayout.Y_AXIS));
    QVBoxLayout* topPanelLayout = new QVBoxLayout(topPanel);

    QWidget* panel = new QWidget();
    //panel.setLayout(new BoxLayout(panel, BoxLayout.X_AXIS));
    QHBoxLayout* panelLayout = new QHBoxLayout(panel);
    panelLayout->addStrut(2*STRUT_SIZE);
    panelLayout->addWidget(new QLabel(tr("SystemName")));
    panelLayout->addStrut(STRUT_SIZE);
    _sysNameBox =  new JTextField(_warrant->getSystemName());
    _sysNameBox->setBackground(QColor(Qt::white));
    _sysNameBox->setEnabled(false);
    panelLayout->addWidget(_sysNameBox);
    panelLayout->addStrut(2*STRUT_SIZE);
    panelLayout->addStrut(STRUT_SIZE);
    panelLayout->addWidget(new QLabel(tr("UserName")));
    panelLayout->addStrut(STRUT_SIZE);
    _userNameBox =  new JTextField(_warrant->getUserName());
    panelLayout->addWidget(_userNameBox);
    panelLayout->addStrut(2*STRUT_SIZE);
    topPanelLayout->addWidget(panel);
    topPanelLayout->addStrut(STRUT_SIZE);

    return topPanel;
}

/*private*/ QWidget* WarrantFrame::makeFindRouteTabPanel()
{
 QWidget* tab1 = new QWidget();
 //tab1.setLayout(new BoxLayout(tab1, BoxLayout.LINE_AXIS));
 QHBoxLayout* tab1lLayout = new QHBoxLayout(tab1);
 tab1lLayout->addStrut((STRUT_SIZE));

 QWidget* topLeft = new QWidget();
 //topLeft.setLayout(new BoxLayout(topLeft, BoxLayout.PAGE_AXIS));
 QVBoxLayout* topLeftLayout = new QVBoxLayout(topLeft);

 topLeftLayout->addWidget(makeBlockPanels());

 topLeftLayout->addStrut((2 * STRUT_SIZE));
 tab1lLayout->addWidget(topLeft);

 tab1lLayout->addStrut((STRUT_SIZE));
 QWidget* topRight = new QWidget();
 //topRight.setLayout(new BoxLayout(topRight, BoxLayout.LINE_AXIS));
 QHBoxLayout* topRightLayout = new QHBoxLayout(topRight);

 QWidget* panel = new QWidget();
 //panel.setLayout(new BoxLayout(panel, BoxLayout.PAGE_AXIS));
 QVBoxLayout* panelLayout = new QVBoxLayout(panel);
 panelLayout->addStrut((2 * STRUT_SIZE));
 _calculateButton = new QPushButton(tr("Calculate"));
 _calculateButton->setMaximumSize(_calculateButton->sizeHint());
// _calculateButton.addActionListener(new ActionListener() {
//     public void actionPerformed(ActionEvent e) {
//         calculate();
//     }
// });
 QWidget* p = new QWidget();
 //p.setLayout(new BoxLayout(p, BoxLayout.PAGE_AXIS));
 QVBoxLayout* pLayout = new QVBoxLayout(p);
 QWidget* pp = new QWidget();
 //pp.setLayout(new FlowLayout(FlowLayout.CENTER));
 FlowLayout* ppLayout = new FlowLayout();
 ppLayout->addWidget(new QLabel(("Calculate Route")));
 pLayout->addWidget(pp);
 {
 pp = new QWidget();
 //pp.setLayout(new FlowLayout(FlowLayout.CENTER));
 FlowLayout* ppLayout = new FlowLayout();
 ppLayout->addWidget(_calculateButton);
 pLayout->addWidget(pp);
 panelLayout->addWidget(p);
 panelLayout->addStrut((2 * STRUT_SIZE));

 _stopButton = new QPushButton(tr("Stop"));
 _stopButton->setMaximumSize(_stopButton->sizeHint());
// _stopButton.addActionListener(new ActionListener() {
//     public void actionPerformed(ActionEvent e) {
//         stopRouteFinder();
//     }
// });
 connect(_stopButton, SIGNAL(clicked()), this, SLOT(stopRouteFinder()));

   int numBlocks =((OBlockManager*) InstanceManager::getDefault("OBlockManager"))->getSystemNameList().size();
 if (numBlocks / 6 > getDepth()) {
     setDepth(numBlocks / 6);
 }
 panelLayout->addWidget(searchDepthPanel(true));
}
 {
 p = new QWidget();
 //p.setLayout(new BoxLayout(p, BoxLayout.PAGE_AXIS));
 QVBoxLayout* pLayout = new QVBoxLayout(p);
// pLayout->addWidget(makeTextBoxPanel(true, _searchStatus, "SearchRoute", NULL));
 _searchStatus->setEnabled(false);
 //pLayout->add(Box.createVerticalGlue());
 panelLayout->addWidget(p);

 _searchStatus->setBackground(QColor(Qt::white));
 _searchStatus->setEnabled(false);
 }
 {
 p = new QWidget();
 pp = new QWidget();
 //pp.setLayout(new FlowLayout(FlowLayout.CENTER));
 FlowLayout* ppLayout = new FlowLayout(pp);
 ppLayout->addWidget(_stopButton);
 pLayout->addWidget(pp, /*BorderLayout.SOUTH*/0, Qt::AlignBottom);
 panelLayout->addWidget(p);
 //panelLayout->addWidget(Box.createRigidArea(new Dimension(10,
//         topLeft.getPreferredSize().height - panel.getPreferredSize().height)));
 panelLayout->addStrut((STRUT_SIZE));
 //panelLayout->addWidget(Box.createVerticalGlue());
 topRightLayout->addWidget(panel);
 topRightLayout->addStrut((STRUT_SIZE));

 PickListModel* pickListModel = PickListModel::oBlockPickModelInstance();
 topRightLayout->addWidget(/*new JScrollPane*/(pickListModel->makePickTable()));
 QSize dim = topRight->sizeHint();
 topRight->setMinimumSize(dim);
 tab1lLayout->addWidget(topRight);
 tab1lLayout->addStrut((STRUT_SIZE));
 }
 return tab1;
}

/*private*/ void WarrantFrame::calculate()
{
    clearWarrant();
    if (_originBlockOrder!=NULL) {
        int depth = _maxBlocks;
        try {
            depth = _searchDepth->text().toInt();
        } catch (NumberFormatException nfe) {
            depth = _maxBlocks;
        }
//        _routeFinder = new RouteFinder(this, _originBlockOrder, _destBlockOrder,
//                                        _viaBlockOrder, _avoidBlockOrder, depth);
//        new QThread(_routeFinder).start();
        //javax.swing.SwingUtilities.invokeLater(_routeFinder);
    }

}
/*private*/ QWidget* WarrantFrame::makeSetPowerTabPanel() {
    QWidget* tab2 = new QWidget();
    //tab2.setLayout(new BoxLayout(tab2, BoxLayout.Y_AXIS));
    QVBoxLayout* tab2Layout = new QVBoxLayout(tab2);

    tab2Layout->addWidget(makeTabMidPanel());

    QWidget* panel = new QWidget();
    //panel.setLayout(new BoxLayout(panel, BoxLayout.X_AXIS));
    QHBoxLayout* panelLayout = new QHBoxLayout(panel);
#if 1
    panelLayout->addStrut(STRUT_SIZE);
    panelLayout->addWidget(makeBorderedTrainPanel());
    panelLayout->addStrut(STRUT_SIZE);
    panelLayout->addWidget(makeRecordPanel());
    panelLayout->addStrut(STRUT_SIZE);
    panelLayout->addWidget(makePlaybackPanel());
    panelLayout->addStrut(STRUT_SIZE);
    tab2Layout->addWidget(panel);
#endif
 {
  panel = new QWidget();
  QHBoxLayout* panelLayout = new QHBoxLayout(panel);
  QString status = getIdleMessage();
  //panelLayout->addWidget(makeTextBoxPanel(false, _statusBox, "Status", false));
  _statusBox->setMinimumSize( QSize(300, _statusBox->sizeHint().height()));
  _statusBox->setMaximumSize( QSize(900, _statusBox->sizeHint().height()));
  _statusBox->setText(status);
  panelLayout->addWidget(_statusBox);
  tab2Layout->addWidget(panel);
 }
 return tab2;
}
/*private*/ QString  WarrantFrame::getIdleMessage()
{
 switch (_warrant->getRunMode())
 {
  case Warrant::MODE_NONE:
   if (getOrders()->size() == 0) {
       return tr("Blank Warrant");
   } else if (getAddress() == NULL || getAddress().length() == 0) {
       return tr("Locomotive not Assigned.");
   }
   break;
  case Warrant::MODE_LEARN:
   return tr("Learn Mode in Block %1.").arg(
           _warrant->getCurrentBlockOrder()->getBlock()->getDisplayName());
  case Warrant::MODE_RUN:
  case Warrant::MODE_MANUAL:
   return _warrant->getRunningMessage();
 }
 return tr("Idle");
}

/*private*/ QWidget* WarrantFrame::makeBorderedTrainPanel()
{
 QWidget* trainPanel = makeTrainPanel();

 QGroupBox* edge = new QGroupBox();
// edge.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(java.awt.Color.BLACK),
//         tr("SetPower"),
//         javax.swing.border.TitledBorder.CENTER,
//         javax.swing.border.TitledBorder.TOP));
 QString     gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";
 edge->setStyleSheet(gbStyleSheet);
 QVBoxLayout* edgeLayout = new QVBoxLayout(edge);
 edgeLayout->addWidget(trainPanel);
 return edge;
}

/*private*/ QWidget* WarrantFrame::makeRecordPanel()
{
    QWidget* learnPanel = new QWidget();
    //learnPanel.setLayout(new BoxLayout(learnPanel, BoxLayout.Y_AXIS));
    QVBoxLayout* learnPanelLayout = new QVBoxLayout(learnPanel);

    QPushButton* startButton = new QPushButton(tr("Start"));
//    startButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            runLearnModeTrain();
//        }
//    });
    connect(startButton, SIGNAL(clicked()), this, SLOT(runLearnModeTrain()));
    QPushButton* stopButton = new QPushButton(tr("Stop"));
//    stopButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            stopRunTrain();
//        }
//    });
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stopRunTrain()));
    //startButton->setAlignment(/*JComponent.CENTER_ALIGNMENT*/Qt::AlignCenter);
    //stopButton->setAlignment(/*JComponent.CENTER_ALIGNMENT*/Qt::AlignCenter);
    learnPanelLayout->addWidget(startButton, 0, Qt::AlignCenter);
    learnPanelLayout->addStrut((STRUT_SIZE));
    learnPanelLayout->addWidget(stopButton, 0, Qt::AlignCenter);
    //learnPanelLayout->addWidget(Box.createRigidArea(new QSize(30+stopButton.getPreferredSize().width,10)));

    QGroupBox* edge = new QGroupBox("Learn Mode");
    QVBoxLayout* edgeLayout = new QVBoxLayout(edge);
    QString     gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";

    edge->setStyleSheet(gbStyleSheet);
//    edge.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(java.awt.Color.BLACK),
//                                                    tr("LearnMode"),
//                                                    javax.swing.border.TitledBorder.CENTER,
//                                                    javax.swing.border.TitledBorder.TOP));
    edgeLayout->addWidget(learnPanel);
    return edge;
}

/*private*/ QWidget* WarrantFrame::makePlaybackPanel() {
    QWidget* runPanel = new QWidget();
    //runPanel.setLayout(new BoxLayout(runPanel, BoxLayout.X_AXIS));
    QHBoxLayout* runPanelLayout = new QHBoxLayout(runPanel);
    runPanelLayout->addStrut(STRUT_SIZE);

    QWidget* panel = new QWidget();
    //panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
    QVBoxLayout* panelLayout = new QVBoxLayout(panel);
    panelLayout->addStrut(STRUT_SIZE);
    QButtonGroup* group = new QButtonGroup();
    group->addButton(_runProtect);
    group->addButton(_runBlind);
    panelLayout->addWidget(_runProtect);
    panelLayout->addWidget(_runBlind);
    runPanelLayout->addWidget(panel);
    runPanelLayout->addStrut(STRUT_SIZE);
    _runBlind->setChecked(_warrant->getRunBlind());

 {
    panel = new QWidget();
    //panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
    QVBoxLayout* panelLayout = new QVBoxLayout(panel);
    //panelLayout->addWidget((STRUT_SIZE));
    QWidget* bPanel = new QWidget();
    FlowLayout* bPanelLayout = new FlowLayout(bPanel);
    //bPanel.setLayout(new FlowLayout(FlowLayout.CENTER));
    QPushButton* runButton = new QPushButton(tr("ARun"));
    //    runButton.addActionListener(new ActionListener() {
    //        /*public*/ void actionPerformed(ActionEvent e) {
    //            runTrain(Warrant::MODE_RUN);
    //        }
    //    });
    connect(runButton, SIGNAL(clicked()), this, SLOT(on_runButtonClicked()));
    bPanelLayout->addWidget(runButton);
    panelLayout->addWidget(bPanel);
    //panelLayout->addWidget((STRUT_SIZE));
    }
    {
    panel = new QWidget();
    //panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
    QVBoxLayout* panelLayout = new QVBoxLayout(panel);
    group = new QButtonGroup();
    QSignalMapper* mapper = new QSignalMapper;
    group->addButton(_halt);
    group->addButton(_resume);
    group->addButton(_abort);
    group->addButton(_invisible);
    panelLayout->addWidget(_halt);
    panelLayout->addWidget(_resume);
    panelLayout->addWidget(_abort);
    runPanelLayout->addWidget(panel);
//    _halt.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            doControlCommand(Warrant::HALT);
//            }
//        });
    mapper->setMapping(_halt, Warrant::HALT);
    connect(_halt, SIGNAL(clicked()), mapper, SLOT(map()));
//    _resume.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            doControlCommand(Warrant::RESUME);
//            }
//        });
    mapper->setMapping(_halt, Warrant::RESUME);
    connect(_resume, SIGNAL(clicked()), mapper, SLOT(map()));

//    _abort.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            doControlCommand(Warrant::ABORT);
//            }
//        });
    mapper->setMapping(_halt, Warrant::ABORT);
    connect(_abort, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(doControlCommand(int)));
    runPanelLayout->addWidget(panel);
    }
    QWidget* edge = new QWidget();
    QVBoxLayout* edgeLayout = new QVBoxLayout(edge);
    QString     gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";

//    edge.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(java.awt.Color.BLACK),
//                                                    tr("RunTrain"),
//                                                    javax.swing.border.TitledBorder.CENTER,
//                                                    javax.swing.border.TitledBorder.TOP));
    edgeLayout->addWidget(runPanel);
    return edge;
}

void WarrantFrame::on_throttleFactorBoxLeave()
{
 // Transient variable, just verify it is a float.
 //            try {
 //                Float.parseFloat(_throttleFactorBox.getText());
 //            } catch (NumberFormatException nfe) {
 //                JOptionPane.showMessageDialog(NULL, tr("MustBeFloat"),
 //                        tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
 //                _throttleFactorBox.setText("1.0");
 //            }
}
void WarrantFrame::on_runButtonClicked()
{
 runTrain(Warrant::MODE_RUN);
}

/*private*/ QWidget* WarrantFrame::makeTabMidPanel()
{
 QWidget* midPanel = new QWidget();
 //midPanel.setLayout(new BoxLayout(midPanel, BoxLayout.Y_AXIS));
 QVBoxLayout* midPanelLayout = new QVBoxLayout(midPanel);

 QWidget* tablePanel = new QWidget();
 //tablePanel.setLayout(new BoxLayout(tablePanel, BoxLayout.LINE_AXIS));
 QHBoxLayout*tablePanelLayout = new QHBoxLayout(tablePanel);
 _routePanel = makeRouteTablePanel();
 tablePanelLayout->addWidget(_routePanel);
 tablePanelLayout->addStrut(5);
 tablePanelLayout->addWidget(makeThrottleTablePanel());
 bool show = (_throttleCommands->size() > 0);
 showCommands(show);
 QWidget* buttonPanel = new QWidget();
 //buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.LINE_AXIS));
 QHBoxLayout* buttonPanelLayout = new QHBoxLayout(buttonPanel);
 QButtonGroup* group = new QButtonGroup();
 QRadioButton* showRoute = new QRadioButton(tr("showRoute")/*, !show*/);
 QRadioButton* showScript = new QRadioButton(tr("showScript")/*, show*/);
 showScript->setChecked(true);
 group->addButton(showRoute);
 group->addButton(showScript);
 buttonPanelLayout->addWidget(showRoute);
 buttonPanelLayout->addWidget(showScript);
//            showRoute.addActionListener(new ActionListener() {
//                public void actionPerformed(ActionEvent e) {
//                    showCommands(false);
//                }
//            });
 connect(showRoute, SIGNAL(toggled(bool)), this, SLOT(showCommands(bool)));
//            showScript.addActionListener(new ActionListener() {
//                public void actionPerformed(ActionEvent e) {
//                    showCommands(true);
//                }
//            });
 midPanelLayout->addWidget(buttonPanel);
 midPanelLayout->addStrut(STRUT_SIZE);
 midPanelLayout->addWidget(tablePanel);
 midPanelLayout->addStrut(STRUT_SIZE);

 return midPanel;
}
/*private*/ void WarrantFrame::showCommands(bool setCmds)
{
 _routePanel->setVisible(!setCmds);
 _commandPanel->setVisible(setCmds);
}
/*private*/ QWidget* WarrantFrame::makeThrottleTablePanel()
{
 _commandTable = new JTable(_commandModel);
 _commandTable->setColumnModel(new DefaultTableColumnModel(_commandTable));
 //_commandTable.setDefaultEditor(JComboBox.class, new jmri.jmrit.symbolicprog.ValueEditor());
 for (int i = 0; i < _commandModel->columnCount(QModelIndex()); i++)
 {
  int width = _commandModel->getPreferredWidth(i);
  _commandTable->getColumnModel()->addColumn(new TableColumn());
  _commandTable->getColumnModel()->getColumn(i)->setPreferredWidth(width);
 }
 //_throttlePane = new JScrollPane(_commandTable);
 ROW_HEIGHT = _commandTable->getRowHeight(0);
// QSize dim = _commandTable->sizeHint();
// dim.setheight(ROW_HEIGHT * 8);
 //_throttlePane.getViewport().setPreferredSize(dim);

 QWidget* buttonPanel = new QWidget();
 //buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.PAGE_AXIS));
 QVBoxLayout* buttonPanelLayout = new QVBoxLayout(buttonPanel);
 buttonPanelLayout->addStrut(3 * STRUT_SIZE);

 QPushButton* insertButton = new QPushButton(tr("Insert Row"));
// insertButton.addActionListener(new ActionListener() {
//     public void actionPerformed(ActionEvent e) {
//         insertRow();
//     }
// });
 connect(insertButton, SIGNAL(clicked()), this, SLOT(insertRow()));
 buttonPanelLayout->addWidget(insertButton);
 buttonPanelLayout->addStrut(2 * STRUT_SIZE);

 QPushButton* deleteButton = new QPushButton(tr("Delete Row"));
// deleteButton.addActionListener(new ActionListener() {
//     public void actionPerformed(ActionEvent e) {
//         deleteRow();
//     }
// });
 connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteRow()));
 buttonPanelLayout->addWidget(deleteButton);
 //buttonPanelLayout->addWidget(Box.createVerticalStrut(3*STRUT_SIZE));

 _commandPanel = new QWidget();
 //_commandPanel.setLayout(new BoxLayout(_commandPanel, BoxLayout.PAGE_AXIS));
 QVBoxLayout* commandPanelLayout = new QVBoxLayout(_commandPanel);
 QLabel* title = new QLabel(tr("Throttle Commands"));
 QWidget* panel = new QWidget();
 //panel.setLayout(new BoxLayout(panel, BoxLayout.LINE_AXIS));
 QHBoxLayout* panelLayout = new QHBoxLayout(panel);
 QWidget* p = new QWidget();
 QVBoxLayout* pLayout = new QVBoxLayout(p);
 pLayout->addWidget(/*_throttlePane*/_commandTable);
 panelLayout->addWidget(p);
 buttonPanelLayout->addStrut(STRUT_SIZE);
 panelLayout->addWidget(buttonPanel);
 buttonPanelLayout->addStrut(STRUT_SIZE);
 commandPanelLayout->addWidget(title);
 commandPanelLayout->addWidget(panel);
 //commandPanelLayout->addWidget(Box.createGlue());
 return _commandPanel;
}

/*private*/ void WarrantFrame::insertRow() {
        int row = _commandTable->getSelectedRow();
        if (row < 0) {
            showWarning(tr("Select a row from the table to add or delete a row"));
            return;
        }
        _throttleCommands->insert(row+1, new ThrottleSetting(0, NULL, NULL, NULL));
        _commandModel->fireTableDataChanged();
        _commandTable->setRowSelectionInterval(row, row);
    }

    /*private*/ void WarrantFrame::deleteRow() {
        int row = _commandTable->getSelectedRow();
        if (row < 0) {
            showWarning(tr("Select a row from the table to add or delete a row"));
            return;
        }
        ThrottleSetting* cmd = _throttleCommands->at(row);
        if (cmd != NULL) {
            QString c = cmd->getCommand();
            if (c != NULL && c.trimmed().toUpper()==("NOOP")) {
                showWarning(tr("A block synchronization marker cannot be deleted."));
                return;
            }
            long time = cmd->getTime();
            if ((row + 1) < _throttleCommands->size()) {
                time += _throttleCommands->at(row + 1)->getTime();
                _throttleCommands->at(row + 1)->setTime(time);
            }
        }
        _throttleCommands->removeAt(row);
        _commandModel->fireTableDataChanged();
    }

/**
* Save, Cancel, Delete buttons
*/
/*private*/ QWidget* WarrantFrame::makeEditableButtonPanel()
{
 QWidget* buttonPanel = new QWidget();
 //buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.X_AXIS));
 FlowLayout* buttonPanelLayout = new FlowLayout(buttonPanel);
 //buttonPanelLayout->addStrut(10*STRUT_SIZE);

// QWidget* panel = new QWidget();
// //panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
// QVBoxLayout* panelLayout = new QVBoxLayout(panel);
 QPushButton* saveButton = new QPushButton(tr("Save"));
//    saveButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            save();
//        }
//    });
 connect(saveButton, SIGNAL(clicked()), this, SLOT(save()));
// panelLayout->addWidget(saveButton);
// panelLayout->addStrut(STRUT_SIZE);
// buttonPanelLayout->addWidget(panel);
 buttonPanelLayout->addWidget(saveButton);
 //buttonPanelLayout->addStrut(3*STRUT_SIZE);
 {
//  panel = new QWidget();
//  //panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
//  QVBoxLayout* panelLayout = new QVBoxLayout(panel);

  QPushButton* copyButton = new QPushButton(tr("Copy"));
//    copyButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            copy();
//        }
//    });
  connect(copyButton, SIGNAL(clicked()), this, SLOT(copy()));
//  panelLayout->addWidget(copyButton);
//  panelLayout->addStrut(STRUT_SIZE);
//  buttonPanelLayout->addWidget(panel);
  buttonPanelLayout->addWidget(copyButton);
  //buttonPanelLayout->addWidget(3*STRUT_SIZE));
 }
 {
//  panel = new QWidget();
//  //panel.setLayout(new BoxLayout(panel, BoxLayout.PAGE_AXIS));
//  QVBoxLayout* panelLayout = new QVBoxLayout(panel);
  QPushButton* cancelButton = new QPushButton(tr("Cancel"));
//  cancelButton.addActionListener(new ActionListener() {
//      public void actionPerformed(ActionEvent e) {
//          close();
//      }
//  });
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
//  panelLayout->addWidget(cancelButton);
//  panelLayout->addStrut(STRUT_SIZE);
//  buttonPanelLayout->addWidget(panel);
  buttonPanelLayout->addWidget(cancelButton);
  //buttonPanelLayout->add((3 * STRUT_SIZE));
 }
 {
//  panel = new QWidget();
////  panel.setLayout(new BoxLayout(panel, BoxLayout.PAGE_AXIS));
  QPushButton* deleteButton = new QPushButton(tr("Delete"));
//  deleteButton.addActionListener(new ActionListener() {
//      public void actionPerformed(ActionEvent e) {
//          InstanceManager.getDefault(WarrantManager.class).deregister(_warrant);
//          _warrant.dispose();
//          WarrantTableAction.updateWarrantMenu();
//          close();
//      }
//  });
  connect(deleteButton, SIGNAL(clicked()), this, SLOT(on_deleteButtonClicked()));
//  panelLayout->addWidget(deleteButton);
//  panelLayout->addStrut(STRUT_SIZE);
//  buttonPanelLayout->addWidget(panel);
  buttonPanelLayout->addWidget(deleteButton);
  //buttonPanelLayout->addWidget(Box.createHorizontalGlue());
 }
 return buttonPanel;
}
void WarrantFrame::on_deleteButtonClicked()
{
 ((WarrantManager*)
 InstanceManager::getDefault("WarrantManager"))->deregister(_warrant);
 _warrant->dispose();
 //WarrantTableAction::updateWarrantMenu();
  close();
}

///*private*/ QWidget* WarrantFrame::makeTextBoxPanel(bool vertical, JTextField* textField, QString label, bool editable) {
//    QWidget* panel = makeBoxPanel(vertical, textField, label);
//    textField->setEnabled(editable);
//    textField->setBackground(QColor(Qt::white));
//    return panel;
//}



/*private*/ void WarrantFrame::doControlCommand(int cmd) {
    if (log->isDebugEnabled()) log->debug("actionPerformed on doControlCommand  cmd= "+cmd);
    if (_warrant->getRunMode() != Warrant::MODE_RUN) {
//        JOptionPane.showMessageDialog(this, java.text.MessageFormat.format(
//                tr("NotRunning"), _warrant->getDisplayName()),
//                tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
     QMessageBox::warning(this, tr("Warning"), tr("Warrant \"%1\" not set for running.").arg( _warrant->getDisplayName()));
    } else {
        _warrant->controlRunTrain(cmd);
    }
    _invisible->setChecked(true);
}


/*private*/ void WarrantFrame::makeMenus() {
    setTitle(tr("Warrant \"%1\"").arg(_warrant->getDisplayName()));
    QMenuBar* menuBar = new QMenuBar();
    QMenu* fileMenu = new QMenu(tr("File"));
    fileMenu->addMenu(new SaveMenu());
    menuBar->addMenu(fileMenu);
    setMenuBar(menuBar);
//    addHelpMenu("package.jmri.jmrit.logix.WarrantTable", true);
}

/*private*/ void WarrantFrame::clearCommands()
{
    _throttleCommands = new QList<ThrottleSetting*>();
    _commandModel->fireTableDataChanged();
    _searchStatus->setText("");
}

/*private*/ bool WarrantFrame::setTrainInfo(QString name, bool isAddress) {
    if (log->isDebugEnabled()) log->debug("setTrainInfo for: "+name+" isAddress= "+isAddress);
    if (isAddress)  {
        _dccNumBox->setText(name);
    }
    if (name != NULL && name.length()>0) {
        _train = NULL;
        if (isAddress)  {
            int index = name.indexOf('(');
            if (index >= 0) {
                name = name.mid(0, index);
            }
            QList<RosterEntry*> l = Roster::getDefault()->matchingList(NULL, NULL, name, NULL, NULL, NULL, NULL );
            if (l.size() > 0) {
                _train = l.at(0);
            }
        } else {
            _train = Roster::getDefault()->entryFromTitle(name);
        }
        if (_train !=NULL) {
            _trainNameBox->setText(_train->getRoadNumber());
            _dccNumBox->setText(_train->getDccLocoAddress()->toString());
            //_rosterBox->setSelectedItem(_train->getId());
            _rosterBox->setCurrentIndex(_rosterBox->findText(_train->getId()));
        } else {
            _trainNameBox->setText("");
            if (!isAddress) {
                _dccNumBox->setText("");
                //_rosterBox->setSelectedItem(tr("Address not in Roster."));
                _rosterBox->setCurrentIndex(_rosterBox->findText(tr("Address not in Roster.")));
            } else {
                //_rosterBox->setSelectedItem(" ");
                _rosterBox->setCurrentIndex(_rosterBox->findText(" "));
            }
            return false;
        }
    }
//    if (_tabbedPane!=NULL) {
//        _tabbedPane->invalidate();
//    }
    return true;
}
#if 0
/*public*/ void actionPerformed(ActionEvent e) {
    Object obj = e.getSource();
    _thisActionEventId = e.getID();
    if (log->isDebugEnabled()) log->debug("actionPerformed: source "+((Component)obj).getName()+
                 " id= "+e.getID()+", ActionCommand= "+e.getActionCommand());
    doAction(obj);
}

void doAction(Object obj) {
    if (obj instanceof JTextField)
    {
        JTextField box = (JTextField)obj;
        //String text = box.getText();
        if (box == _originBlockBox) {
            setOriginBlock();
        } else if (box == _destBlockBox) {
            setDestinationBlock();
        } else if (box == _viaBlockBox) {
            setViaBlock();
        } else if (box == _avoidBlockBox) {
            setAvoidBlock();
        }
    } else {
        JComboBox box = (JComboBox)obj;
        if (box == _originPathBox) {
            setPortalBox(_originPathBox, _originPortalBox, _originBlockOrder);
        } else if (box == _originPortalBox) {
            _originBlockOrder->setExitName((String)_originPortalBox.getSelectedItem());
        } else if (box == _destPathBox) {
            setPortalBox(_destPathBox, _destPortalBox, _destBlockOrder);
        } else if (box == _destPortalBox) {
            _destBlockOrder->setEntryName((String)_destPortalBox.getSelectedItem());
        } else if (box == _viaPathBox) {
            String pathName = (String)_viaPathBox.getSelectedItem();
            _viaBlockOrder->setPathName(pathName);
        } else if (box == _avoidPathBox) {
            String pathName = (String)_avoidPathBox.getSelectedItem();
            _avoidBlockOrder->setPathName(pathName);
        }
        clearWarrant();
    }
}
#endif



/*private*/ void WarrantFrame::setPortalBox(QComboBox* pathBox, QComboBox* portalBox, BlockOrder* order) {
    if(log->isDebugEnabled()) log->debug("setPortalBox: block= "+order->getBlock()->getDisplayName());
    portalBox->clear();
    QString pathName =pathBox->currentText();
    order->setPathName(pathName);
    OPath* path = order->getPath();
    if (path != NULL) {
        Portal* portal = path->getFromPortal();
        if (portal!=NULL) {
            QString name = portal->getName();
            if (name!=NULL) { portalBox->addItem(name); }
        }
        portal = path->getToPortal();
        if (portal!=NULL) {
            QString name = portal->getName();
            if (name!=NULL) { portalBox->addItem(name); }
        }
        if (log->isDebugEnabled()) log->debug("setPortalBox: Path "+path->getName()+
                     " set in block "+order->getBlock()->getDisplayName());
    } else {
        if (log->isDebugEnabled()) log->debug("setPortalBox: Path set to NULL in block"
                     +order->getBlock()->getDisplayName());
    }
}

///*private*/ bool WarrantFrame::setOriginBlock() {
//    OBlock* block = getEndPointBlock(_originBlockBox);
//    bool result = true;
//    if (block == NULL) {
//        result = false;
//    } else {
//        if (_originBlockOrder!= NULL && block==_originBlockOrder->getBlock() &&
//                pathIsValid(block, _originBlockOrder->getPathName())) {
//            return true;
//        } else {
//            if (pathsAreValid(block)) {
//                _originBlockOrder = new BlockOrder(block);
//                if (!setPathBox(_originPathBox, _originPortalBox, block)) {
//                    result = false;
//                    _originBlockBox->setText("");
//                }
//            } else {
//                _originBlockBox->setText("");
//                result = false;
//            }
//        }
//    }
//    if (!result) {
//        _originPathBox->clear();
//        _originPortalBox->clear();
//    }
//    return result;
//}

///*private*/ bool WarrantFrame::setDestinationBlock() {
//    OBlock* block = getEndPointBlock(_destBlockBox);
//    bool result = true;
//    if (block == NULL) {
//        result = false;
//    } else {
//        if (_destBlockOrder!= NULL && block==_destBlockOrder->getBlock() &&
//                pathIsValid(block, _destBlockOrder->getPathName())) {
//            return true;
//        } else {
//            if (pathsAreValid(block)) {
//                _destBlockOrder = new BlockOrder(block);
//                if (!setPathBox(_destPathBox, _destPortalBox, block)) {
//                    result = false;
//                    _destBlockBox->setText("");
//                }
//            } else {
//                _destBlockBox->setText("");
//                result = false;
//            }
//        }
//    }
//    if (!result) {
//        _originPathBox->clear();
//        _originPortalBox->clear();
//    }
//    return result;
//}

///*private*/ bool WarrantFrame::setViaBlock() {
//    OBlock* block = getEndPointBlock(_viaBlockBox);
//    if (block == NULL) {
//        _viaPathBox->clear();
//        _viaBlockOrder = NULL;
//        return true;
//    } else {
//        if (_viaBlockOrder!=NULL && block==_viaBlockOrder->getBlock() &&
//                pathIsValid(block, _viaBlockOrder->getPathName())) {
//            return true;
//        } else {
//            if (pathsAreValid(block)) {
//                _viaBlockOrder = new BlockOrder(block);
//                if (!setPathBox(_viaPathBox, NULL, block)) {
//                    _viaPathBox->clear();
//                    _viaBlockBox->setText("");
//                    return false;
//                }
//            }
//        }
//    }
//    return false;
//}

///*private*/ bool WarrantFrame::setAvoidBlock() {
//    OBlock* block = getEndPointBlock(_avoidBlockBox);
//    if (block == NULL) {
//        _avoidPathBox->clear();
//        _avoidBlockOrder = NULL;
//        return true;
//    } else {
//        if (_avoidBlockOrder!=NULL && block==_avoidBlockOrder->getBlock() &&
//                pathIsValid(block, _avoidBlockOrder->getPathName())) {
//            return true;
//        } else {
//            if (pathsAreValid(block)) {
//                _avoidBlockOrder = new BlockOrder(block);
//                if (!setPathBox(_avoidPathBox, NULL, block)) {
//                    _avoidPathBox->clear();
//                    _avoidBlockBox->setText("");
//                    return false;
//                }
//            }
//        }
//    }
//    return false;
//}

/*private*/ void WarrantFrame::clearWarrant() {
 if (_warrant != NULL) {
     _warrant->deAllocate();
     _warrant->stopWarrant(false);
     _warrant->removePropertyChangeListener((PropertyChangeListener*)this);
     //disconnect(_warrant->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }

}

/*protected*/ Warrant* WarrantFrame::getWarrant() {
        return _warrant;
    }

/*protected*/ void WarrantFrame::setStatusText(QString msg, QColor c) {
    _statusBox->setForeground(c);
    _statusBox->setText(msg);
}


/******************* Learn or Run a train *******************/
/**
 * all non-NULL returns are fatal
 * @return
 */
/*private*/ QString WarrantFrame::checkTrainId() {
    QString msg = NULL;
    if (_warrant->getRunMode()!=Warrant::MODE_NONE) {
        msg = tr("Train \"%1\" is currently running.").arg( _trainNameBox->text());
        return msg;
    }
    if (_orders->size()==0) {
     msg = tr("No Route defined from \"%1\" to \"%2\".").arg(
             _originBlockBox->text()).arg(_destBlockBox->text());
        return msg;
    }
    if (_train!=NULL) {
        _locoAddress = _train->getDccLocoAddress();
        if (_locoAddress==NULL) {
            _locoAddress = getLocoAddress();
        }

    } else {
        _locoAddress = getLocoAddress();
    }
    if (_locoAddress==NULL) {
        msg = tr("Please select a train to run.");
    }
    _statusBox->setText(msg);
    return msg;
}

/**
 * non-NULL returns not necessarily fatal, but may require used decision or action
 */
/*private*/ QString WarrantFrame::setupRun() {
    QString msg = NULL;
    msg = _warrant->allocateRoute(false,_orders);
    if (msg==NULL) {
        msg = _warrant->setRoute(0, _orders);
    }
    if (msg==NULL) {
        msg = _warrant->checkStartBlock();
    }
    return msg;
}
#if 0
/*private*/ void runLearnModeTrain() {
    String msg = checkTrainId();
    if (msg==NULL) {
        msg = setupRun();
    }
    if (msg==NULL) {
        if (_throttleCommands->size() > 0) {
            if (JOptionPane.showConfirmDialog(this, tr("deleteCommand"),
               tr("QuestionTitle"), JOptionPane.YES_NO_OPTION,
                   JOptionPane.QUESTION_MESSAGE) == JOptionPane.NO_OPTION) {
                return;
            }
            _throttleCommands = new ArrayList <ThrottleSetting>();
            _commandModel.fireTableDataChanged();
        }
        if (_learnThrottle==NULL) {
            _learnThrottle = new LearnThrottleFrame(this);
        } else {
            _learnThrottle.setVisible(true);
        }
        msg = _warrant->setThrottleFactor(_throttleFactorBox.getText());
    }
    if (msg==NULL) {
        msg = _warrant->checkRoute();
    }
    if (msg==NULL) {
        String trainName = _trainNameBox.getText();
        if (trainName!=NULL && trainName.length()>0) {
            _warrant->setTrainName(trainName);
        }
        _startTime = System.currentTimeMillis();
        _warrant->addPropertyChangeListener(this);
       msg = _warrant->setRunMode(Warrant::MODE_LEARN, _locoAddress, _learnThrottle,
                                      _throttleCommands, _runBlind.isSelected());
    }
    if (msg!=NULL) {
        stopRunTrain();
        _statusBox.setText(msg);
       JOptionPane.showMessageDialog(this, msg, tr("WarningTitle"),
                                      JOptionPane.WARNING_MESSAGE);
    }
}
#endif
/*private*/ void WarrantFrame::runTrain(int mode) {
    QString msg = checkTrainId();
    if (msg!=NULL) {
//        JOptionPane.showMessageDialog(this, msg, tr("WarningTitle"),
//                                      JOptionPane.WARNING_MESSAGE);
     QMessageBox::warning(this, tr("Warning"), msg);
        return;
    }
    if (_throttleCommands==NULL || _throttleCommands->size()==0)
    {
        /*JOptionPane.showMessageDialog(this, java.text.MessageFormat.format(
                tr("NoCommands"),_warrant->getDisplayName()),
                      tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);*/
          QMessageBox::warning(this, tr("Warning"), tr("Warrant \%1\" has no throttle commands.").arg(_warrant->getDisplayName()));

        _warrant->deAllocate();
        _statusBox->setText(msg);
       return;
    }
    msg = setupRun();
    if (msg!=NULL) {
//        if (JOptionPane.NO_OPTION == JOptionPane.showConfirmDialog(this,
//                java.text.MessageFormat.format(WarrantTableAction::tr("OkToRun"),
//                msg), WarrantTableAction::tr("WarningTitle"),
//                JOptionPane.YES_NO_OPTION, JOptionPane.WARNING_MESSAGE)) {
     if(QMessageBox::warning(this, tr("Warning"), msg, QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
     {
            _warrant->deAllocate();
            _statusBox->setText(msg);
            return;
        }
    }
    QString trainName = _trainNameBox->text();
    if (trainName!=NULL && trainName.length()>0) {
        _warrant->setTrainName(trainName);
    }
    _warrant->addPropertyChangeListener((PropertyChangeListener*)this);
    //connect(_warrant->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)) );
    msg = _warrant->setRunMode(Warrant::MODE_RUN, _locoAddress, NULL,_throttleCommands, _runBlind->isChecked());
    if (msg!=NULL) {
        _statusBox->setText(msg);
        stopRunTrain();
//        JOptionPane.showMessageDialog(this, msg,
//                            tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
        QMessageBox::warning(this, tr("Warning"), msg);

        return;
    }
}

/*protected*/ void WarrantFrame::stopRunTrain() {
    _warrant->deAllocate();
    QString msg = _warrant->setRunMode(Warrant::MODE_NONE, NULL, NULL, NULL, false);
    _warrant->removePropertyChangeListener((PropertyChangeListener*)this);
    //disconnect(_warrant->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)) );

    if (_learnThrottle!=NULL) {
        _learnThrottle->setSpeedSetting(-0.5F);
        _learnThrottle->setSpeedSetting(0.0F);
        _learnThrottle->dispose();
        _learnThrottle = NULL;
    }
}
/**
 * Property names from Warrant: "runMode" - from setRunMode "controlChange"
 * - from controlRunTrain "blockChange" - from goingActive "allocate" - from
 * allocateRoute, deAllocate "setRoute" - from setRoute, goingActive
 * Property names from Engineer: "Command" - from run "SpeedRestriction" -
 * ThrottleRamp run Property names from RouteFinder: "RouteSearch" - from
 * run
 */
//@Override
/*public*/ void WarrantFrame::propertyChange(PropertyChangeEvent* e)
{
 QString property = e->getPropertyName();
 if (log->isDebugEnabled()) log->debug("propertyChange \""+property+
                                     "\" old= "+e->getOldValue().toString()+" new= "+e->getNewValue().toString()+
                                     " source= "+QString(e->getSource()->metaObject()->className()));
 if (property==("DnDrop"))
 {
     doAction(e->getSource());
 }
 else if (qobject_cast<Warrant*>(e->getSource()) != NULL && _warrant==(e->getSource()))
 {
  switch (_warrant->getRunMode())
  {
   case Warrant::MODE_NONE:
   {
    _warrant->removePropertyChangeListener((PropertyChangeListener*)this);
    //disconnect(_warrant->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    int oldMode =  e->getOldValue().toInt();
    int newMode =  e->getNewValue().toInt();
    if (oldMode != Warrant::MODE_NONE)
    {
     OBlock* block = _warrant->getCurrentBlockOrder()->getBlock();
     int state = block->getState();
     if ((state & OBlock::OCCUPIED) > 0 || (state & OBlock::DARK) > 0
             || _runBlind->isChecked())
     {
      setStatusText(
                tr("Warrant %2 ended for train \"%1\". Now occupying block \"%3\".").arg(
                        _warrant->getTrainName()).arg(
                        _warrant->getDisplayName()).arg(
                        block->getDisplayName()), myGreen);
     }
     else
     {
      setStatusText(
                tr("Train \"%1\" ABORTED. (warrant%2)").arg(
                        _warrant->getTrainName()).arg(
                        _warrant->getDisplayName()), myGreen);
     }
    }
   break;
   }
   case Warrant::MODE_LEARN:
   {
    if (property==("blockChange"))
    {
     OBlock* oldBlock =  VPtr<OBlock>::asPtr(e->getOldValue());
     OBlock* newBlock = VPtr<OBlock>::asPtr(e->getNewValue());
     if (newBlock == NULL)
     {
      stopRunTrain();
      setStatusText(
              tr("Warrant %1 Location of \"%3\" unknown. Train left route at block \"%2\".").arg(
                      _warrant->getDisplayName()).arg(
                      oldBlock->getDisplayName()).arg(
                      _warrant->getTrainName()), QColor(Qt::red));
     }
     else
     {
      setThrottleCommand("NoOp", tr("Mark"), VPtr<OBlock>::asPtr( e->getNewValue())->getDisplayName());
      setStatusText(
              tr("Train \"%1\" entering block \"%2\".").arg(
                      _warrant->getTrainName()).arg(
                      newBlock->getDisplayName()), myGreen);
     }
    } else if (property==("abortLearn")) {
        stopRunTrain();
        int oldIdx = e->getOldValue().toInt();
        int newIdx =  e->getNewValue().toInt();
        if (oldIdx > newIdx) {
            setStatusText(
                    tr("Recording of warrant \"%2\" ABORTED. Block %1 occupied ahead. ").arg(
                            _warrant->getBlockAt(oldIdx)->getDisplayName()).arg(
                            _warrant->getDisplayName()), QColor(Qt::red));
        } else {
            setStatusText(
                    tr("Train \"%1\" ABORTED. (warrant %2)").arg(
                _warrant->getTrainName()).arg(
                            _warrant->getDisplayName()), QColor(Qt::red));
         }
     }
     else
    {
        setStatusText(tr("Learn Mode in Block %1.").arg(
                _warrant->getCurrentBlockOrder()->getBlock()->getDisplayName()), QColor(Qt::black));
     }
    break;
    }
   case Warrant::MODE_RUN:
   case Warrant::MODE_MANUAL:
   {
    if (e->getPropertyName()==("blockChange"))
    {
     OBlock* oldBlock = VPtr<OBlock>::asPtr(e->getOldValue());
     OBlock* newBlock = VPtr<OBlock>::asPtr( e->getNewValue());
     if (newBlock == NULL)
     {
      setStatusText(
              tr("Warrant %1 Location of \"%3}\" unknown. Train left route at block \"%2\".").arg(
                      _warrant->getDisplayName()).arg(
                      oldBlock->getDisplayName()).arg(
                      _warrant->getTrainName()), QColor(Qt::red));
     } else {
         setStatusText(
                 tr("Train \"%1\" entering block \"%2\".").arg(
                         _warrant->getTrainName()).arg(
                         newBlock->getDisplayName()), myGreen);
     }
    } else if (e->getPropertyName()==("blockRelease")) {
        OBlock* block = VPtr<OBlock>::asPtr(e->getNewValue());
        long et = (QDateTime::currentMSecsSinceEpoch() - block->_entryTime) / 1000;
        setStatusText(tr("Train \"%1\" leaving block \"%2\". Occupied block for %3 minutes %4 seconds.").arg(
                _warrant->getTrainName()).arg( block->getDisplayName()).arg( et / 60).arg(
                et % 60),  myGreen);
    } else if (e->getPropertyName()==("SpeedRestriction")) {
        setStatusText(tr("Train \"%1\" speed set to %3 in block \%2\".").arg(
                _warrant->getTrainName(), _warrant->getCurrentBlockOrder()
                        ->getBlock()->getDisplayName(), e->getNewValue().toString()), QColor(Qt::black));
    } else if (e->getPropertyName()==("runMode")) {
        int oldMode =  e->getOldValue().toInt();
        int newMode =  e->getNewValue().toInt();
        if (oldMode == Warrant::MODE_NONE) {
            if (newMode != Warrant::MODE_NONE) {
                setStatusText(tr("Warrant %2 started for train \"%1\" in block \"%3\" in %4 mode.").arg(
                        _warrant->getTrainName()).arg( _warrant->getDisplayName()).arg(
                        _warrant->getCurrentBlockOrder()->getBlock()
                                ->getDisplayName(),
                        (Warrant::modeName(newMode))), myGreen);
                if (_warrant->getState()==Warrant::HALT) {
//                    JOptionPane.showMessageDialog(this, _warrant.getRunningMessage(),
//                        tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
          QMessageBox::warning(this, tr("Warning"), _warrant->getRunningMessage());
                }
            }
        } else {
            setStatusText(tr("Train \"%1\" mode change from &3 to %4. (warrant %2)").arg(
                    _warrant->getTrainName()).arg( _warrant->getDisplayName()).arg(
                    Warrant::modeName(oldMode)).arg(
                    Warrant::modeName(newMode)), QColor(Qt::black));
        }
    } else if (e->getPropertyName()==("controlChange")) {
        int runState =  e->getOldValue().toInt();
        int newCntrl =  e->getNewValue().toInt();
        QString stateStr = NULL;
        if (runState < 0) {
            stateStr = Warrant::modeName(runState);
        } else {
         stateStr = Warrant::RUN_STATE[runState].replace("%1",
                    _warrant->getCurrentBlockOrder()->getBlock()
                            ->getDisplayName());
        }
        setStatusText(tr("Control set to %3 on train \"%1\" from state%2").arg(
                _warrant->getTrainName()).arg( stateStr,
                Warrant::CNTRL_CMDS[newCntrl]),
                QColor(Qt::black));
       } else if (e->getPropertyName()==("throttleFail")) {
           setStatusText(tr("No throttle for train %1 due to %2").arg(
                   _warrant->getTrainName()).arg( e->getNewValue().toString()), QColor(Qt::red));
    }
    break;
   }
  }
 }
 //invalidate();
}

/*protected*/ void WarrantFrame::setThrottleCommand(QString cmd, QString value)
 {
     QString bName = tr("NoBlock");
     BlockOrder* bo = _warrant->getCurrentBlockOrder();
     if (bo != NULL) {
         OBlock* block = bo->getBlock();
         if (block != NULL) {
             bName = block->getDisplayName();
         }
     }
     setThrottleCommand(cmd, value, bName);
 }

/*protected*/ void WarrantFrame::setSpeedCommand(float speed) {
    if (_warrant->getSpeedUtil()->profileHasSpeedInfo()) {
        _speed = _warrant->getSpeedUtil()->getTrackSpeed(speed);  // mm/ms
    } else {
        _speed = 0.0;
    }
    setThrottleCommand("speed", QString::number(speed, 'g',2));
}

 /*private*/ void WarrantFrame::setThrottleCommand(QString cmd, QString value, QString bName) {
     qint64 endTime = QDateTime::currentMSecsSinceEpoch();
     long time = endTime - _startTime;
     _startTime = endTime;
     _throttleCommands->append(new ThrottleSetting(time, cmd, value, bName));
     _commandModel->fireTableDataChanged();

//     scrollCommandTable(_commandModel->getRowCount());
 }
#if 0
/*private*/ void scrollCommandTable(int row) {
 JScrollBar bar = _throttlePane.getVerticalScrollBar();
 bar.setValue(row*ROW_HEIGHT);
//        bar.setValue(bar.getMaximum());
}


#endif







/************************* Route Table ******************************/
//class RouteTableModel extends AbstractTableModel {
//    /*public*/ static final int BLOCK_COLUMN = 0;
//    /*public*/ static final int ENTER_PORTAL_COL =1;
//    /*public*/ static final int PATH_COLUMN = 2;
//    /*public*/ static final int DEST_PORTAL_COL = 3;
//    /*public*/ static final int NUMCOLS = 4;

/*public*/ WFRouteTableModel::WFRouteTableModel(WarrantFrame* frame) {
 //super();
this->frame = frame;
}

/*public*/ int WFRouteTableModel::columnCount(const QModelIndex &/*parent*/) const
{
 return NUMCOLS;
}

/*public*/ int WFRouteTableModel::rowCount(const QModelIndex &/*parent*/) const
{
 return frame->_orders->size();
}

/*public*/ QVariant  WFRouteTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
{
 switch (section) {
     case BLOCK_COLUMN: return tr("Block or Sensor Name");
     case ENTER_PORTAL_COL: return tr("Entry Portal");
     case PATH_COLUMN: return tr("Path");
     case DEST_PORTAL_COL: return tr("Exit Portal");
 }
}
return QVariant();
}

/*public*/ Qt::ItemFlags WFRouteTableModel::flags(const QModelIndex &/*index*/) const
{
 return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
///*public*/ Class<?> getColumnClass(int col) {
//    return String.class;
//}

/*public*/ int WFRouteTableModel::getPreferredWidth(int /*col*/)
{
return  JTextField(20).getPreferredSize().width();
}

/*public*/ QVariant WFRouteTableModel::data(const QModelIndex &index, int role) const
{
Logger* log = new Logger("RouteTableModel");
if(role == Qt::DisplayRole)
{
  int row = index.row();
 // some error checking
 if (row >= frame->_orders->size()){
     log->debug("row is greater than _orders");
     return "";
 }
 BlockOrder* bo = frame->_orders->at(row);
 // some error checking
 if (bo == NULL){
     log->debug("BlockOrder is NULL");
     return "";
 }
 switch (index.column()) {
     case BLOCK_COLUMN:
         return bo->getBlock()->getDisplayName();
     case ENTER_PORTAL_COL:
         return bo->getEntryName();
     case PATH_COLUMN:
         return bo->getPathName();
     case DEST_PORTAL_COL:
         if (row==frame->_orders->size()-1) { return ""; }
         return bo->getExitName();
 }
}
return QVariant();
}

/*public*/ bool WFRouteTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
if(role == Qt::EditRole || role == Qt::EditRole)
{
int row = index.row();
beginResetModel();
 BlockOrder* bo = frame->_orders->at(row);
 OBlock* block = NULL;
 switch (index.column()) {
     case BLOCK_COLUMN:
         block = ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getOBlock(value.toString());
         if (block != NULL) { bo->setBlock(block); }
         break;
     case ENTER_PORTAL_COL:
         bo->setEntryName(value.toString());
         break;
     case PATH_COLUMN:
         bo->setPathName(value.toString());
         break;
     case DEST_PORTAL_COL:
         bo->setExitName(value.toString());
         break;
 }
 //fireTableRowsUpdated(row, row);
 endResetModel();
}
return true;
}
void WFRouteTableModel::fireTableDataChanged()
{
beginResetModel();
endResetModel();
}
/*private*/ void WarrantFrame::copy()
{
 CreateWarrantFrame* f = new CreateWarrantFrame();
 f->setVisible(true);
 try {
     f->initComponents();
     f->concatenate(_saveWarrant, NULL);
 } catch (Exception ex) {
     log->error("error making CreateWarrantFrame"/*, ex*/);
 }
 dispose();
}

// shut down, but don't dispose

/*private*/ void WarrantFrame::close() {
 clearTempWarrant();
 stopRunTrain();
}
//};

/**
 * Called by WarrantTableAction before closing the editing of this warrant
 * @return true if this warrant or its pre-editing version is running
 */
/*public*/ bool WarrantFrame::isRunning() {
    if (_warrant->getRunMode() != Warrant::MODE_NONE ||
            (_saveWarrant != nullptr && _saveWarrant->getRunMode() != Warrant::MODE_NONE)) {
        JOptionPane::showMessageDialog(this, tr("Cannot create or edit this warrant while warrant \"%1\" is running. ").arg(_warrant->getDisplayName()),
                tr("Warning"), JOptionPane::WARNING_MESSAGE);
        return true;
    }
    return false;
}

/*private*/ bool WarrantFrame::save()
{
 QString msg = routeIsValid();
 if (msg!=NULL)
 {
//     JOptionPane.showMessageDialog(this, tr("SaveError")+" - "+msg,
//             Bundle.getMessage("WarningTitle"), JOptionPane.WARNING_MESSAGE);
  QMessageBox::warning(this, tr("Warning"),tr("Route not valid.")+" - "+msg);
     return false;
 }
 msg = checkLocoAddress();
 if (msg==NULL) {
     if (_throttleCommands->size()==0) {
         msg = tr("Warrant \"%1}\" has no throttle commands.").arg( _warrant->getDisplayName());
     }
 }
 if (msg!=NULL)
 {
//     int result = JOptionPane.showConfirmDialog(this, msg+Bundle.getMessage("SaveQuestion"), Bundle.getMessage("QuestionTitle"),
//             JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE);
//     if (result==JOptionPane.NO_OPTION) {
  if(QMessageBox::question(this, tr("Question"), tr("Do you want to continue to save?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
         return false;
 }
 if (_saveWarrant != NULL) {
     _warrant = _saveWarrant;        // _warrant now registered.
 }
 _warrant->setDccAddress(getTrainId());
 _warrant->setTrainName(getTrainName());
 _warrant->setRunBlind(_runBlind->isChecked());
 _warrant->setUserName(_userNameBox->text());

 _warrant->setViaOrder(getViaBlockOrder());
 _warrant->setAvoidOrder(getAvoidBlockOrder());
 _warrant->setBlockOrders(getOrders());
 _warrant->setThrottleCommands(_throttleCommands);

 if (log->isDebugEnabled()) log->debug("warrant saved _train "+getTrainId()+", name= "+getTrainName());

 if (_create) {((WarrantManager*)
    InstanceManager::getDefault("WarrantManager"))->Register(_warrant);
  //WarrantTableAction::updateWarrantMenu();
 }
 WarrantTableFrame::getDefault()->getModel()->fireTableDataChanged();
 return true;
}

/*protected*/ void WarrantFrame::setWarrant(Warrant* w)
{
 _warrant = w;
 _sysNameBox->setText(w->getSystemName());
 _userNameBox->setText(w->getUserName());
}
/************************* Throttle Table ******************************/

//class ThrottleTableModel extends AbstractTableModel {
///*public*/ static final int ROW_NUM = 0;
///*public*/ static final int TIME_COLUMN = 1;
///*public*/ static final int COMMAND_COLUMN =2;
///*public*/ static final int VALUE_COLUMN =3;
///*public*/ static final int BLOCK_COLUMN = 4;
///*public*/ static final int NUMCOLS = 5;

/*public*/ ThrottleTableModel::ThrottleTableModel(WarrantFrame *frame)
{
 //super();
this->frame = frame;
 threeDigit = new DecimalFormat("0.000");

}

/*public*/ int ThrottleTableModel::columnCount(const QModelIndex &/*parent*/) const
{
 return NUMCOLS;
}

/*public*/ int ThrottleTableModel::rowCount(const QModelIndex &/*parent*/) const
{
 return frame->_throttleCommands->size();
}

/*public*/ QVariant ThrottleTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
{
 switch (section) {
     case ROW_NUM: return "#";
     case TIME_COLUMN: return tr("ET (msec)");
     case COMMAND_COLUMN: return tr("Command");
     case VALUE_COLUMN: return tr("Value");
     case BLOCK_COLUMN: return tr("Block or Sensor Name");
     case SPEED_COLUMN:
          return tr("Speed (mm/sec)");
 }
}
return QVariant();
}


/*public*/ Qt::ItemFlags ThrottleTableModel::flags(const QModelIndex &index) const
{
 if (index.row()==ROW_NUM) { return Qt::ItemIsEnabled | Qt::ItemIsSelectable; }
 return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

///*public*/ Class<?> getColumnClass(int col)
///{
//    return String.class;
//}

/*public*/ int ThrottleTableModel::getPreferredWidth(int col) {
 switch (col) {
     case ROW_NUM:
     return  JTextField(2).getPreferredSize().width();
     case TIME_COLUMN:
     return  JTextField(7).getPreferredSize().width();
     case COMMAND_COLUMN:
     return  JTextField(9).getPreferredSize().width();
     case VALUE_COLUMN:
     return  JTextField(8).getPreferredSize().width();
     case BLOCK_COLUMN:
     return  JTextField(40).getPreferredSize().width();
 }
 return  JTextField(12).getPreferredSize().width();
}

/*public*/ QVariant ThrottleTableModel::data(const QModelIndex &index, int role) const
{
if(role == Qt::DisplayRole)
{
Logger* log = new Logger("ThrottleTableModel");
int row = index.row();
int col = index.column();
// some error checking
if (row >= frame->_throttleCommands->size()){
     log->debug("row is greater than throttle command size");
     return QVariant();
 }
 ThrottleSetting* ts = frame->_throttleCommands->at(row);
 if (ts == NULL){
     log->debug("Throttle setting is NULL!");
     return "";
 }
 switch (col)
 {
  case ROW_NUM:
      return (row+1);
  case TIME_COLUMN:
      return QVariant((int)ts->getTime());
  case COMMAND_COLUMN:
      return ts->getCommand();
  case VALUE_COLUMN:
      //if ("SpeedStep"==IgnoreCase(ts->getCommand()))
  if(QString::compare("SpeedStep",ts->getCommand(),Qt::CaseInsensitive)==0)
      {
          switch (ts->getValue().toInt()) {
              case DccThrottle::SpeedStepMode14:
              return ("14");
          case DccThrottle::SpeedStepMode27:
              return ("27");
          case DccThrottle::SpeedStepMode28:
              return ("28");
          }
          return ("128");
      } else if (QString::compare("Mark",ts->getValue(),Qt::CaseInsensitive)==0) {
          return tr("Mark");
      }
      return ts->getValue();
  case BLOCK_COLUMN:
         return ts->getBeanDisplayName();
  case SPEED_COLUMN:
     return threeDigit->format(ts->getSpeed() * 1000);
 }
}
return QVariant();
}

/*public*/ bool ThrottleTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
if(role == Qt::EditRole || role == Qt::DisplayRole)
{
  int row = index.row();
  int col = index.column();
 ThrottleSetting* ts = frame->_throttleCommands->at(row);
 QString msg = NULL;
 switch (col)
 {
  case TIME_COLUMN:
  {
   long time = 0;
   try {
       time = value.toLongLong();
       if (time < 0) {
           msg =  tr("%1 is not a valid Elapsed Time.").arg(value.toString());
       }
       ts->setTime(time);
   } catch (NumberFormatException nfe) {
       msg = tr("%1 is not a valid Elapsed Time.").arg(value.toString());
   }
   break;
  }
  case COMMAND_COLUMN:
  {
         QString cmd = value.toString();
         if (cmd == NULL || cmd.length()==0){
             msg = tr("NULL %1 Value").arg("CommandCol");
             break;
         }
         cmd = cmd.trimmed().toUpper();
         if ("SPEED"==(cmd)) {
             ts->setCommand("Speed");
         } else if ("SPEEDSTEP"==(cmd)) {
             ts->setCommand("SpeedStep");
         } else if ("FORWARD"==(cmd)) {
             ts->setCommand("Forward");
         } else if (cmd.startsWith("F")) {
             try {
                 int cmdNum = (cmd.mid(1)).toInt();
                 if (cmdNum < 0 || 28 < cmdNum) {
                     msg = tr("Function Keys are labeled from F0 to F28. ");
                 } else {
                     ts->setCommand(cmd);
                 }
             } catch (Exception e) {
                 msg = tr("Function Keys are labeled from F0 to F28. ");
             }
         } else if (cmd.startsWith("LOCKF")) {
             try {
                 int cmdNum = cmd.mid(5).toInt();
                 if (cmdNum < 0 || 28 < cmdNum) {
                     msg = tr("Function Key Locks (to non-momentary) are labeled from LockF0 to LockF28.");
                 } else {
                     ts->setCommand(cmd);
                 }
             } catch (Exception e) {
                 msg = tr("Function Key Locks (to non-momentary) are labeled from LockF0 to LockF28.");
             }
         } else if ("NOOP"==(cmd)) {
             msg = tr("A block synchronization marker cannot be inserted. %1").arg(value.toString());
         } else if (ts->getCommand()!=NULL && ts->getCommand()==("NoOp")) {
             msg =  tr("A block synchronization marker cannot be changed.  Only the elapsed time can be modified. %1").arg(value.toString());
         } else if ("SENSOR"==(cmd) || "SET SENSOR"==(cmd) || "SET"==(cmd)) {
             ts->setCommand("Set Sensor");
         } else if ("WAIT SENSOR"==(cmd) || "WAIT"==(cmd)) {
             ts->setCommand("Wait Sensor");
         } else if ("RUN WARRANT"==(cmd)) {
             ts->setCommand("Run Warrant");
         } else {
             msg = tr("\"%1\" is an invalid Command").arg(value.toString());
         }
         break;
 }
     case VALUE_COLUMN:
     {
      if (value == QVariant() || value.toString().length()==0){
             msg =  tr("NULLValue %1").arg(tr("Value"));
             break;
         }
      bool resetBlockColumn = true;

         QString cmd = ts->getCommand().toUpper();
          if ("SPEED"==(cmd)) {
             try {
                 float speed = value.toFloat();
                 if (speed < 0.0f || 1.0f < speed) {
                     msg = tr("Speed must be a number from 0.0 to 1.0");
                 }
             } catch (Exception e) {
                 msg = tr("Speed must be a number from 0.0 to 1.0");
             }
             ts->setValue(value.toString());
         } else if ("SPEEDSTEP"==(cmd)) {
             int stepMode = DccThrottle::SpeedStepMode128;
             try {
                 switch (value.toInt()) {
                     case 14:
                         stepMode = DccThrottle::SpeedStepMode14;
                         break;
                     case 27:
                         stepMode = DccThrottle::SpeedStepMode27;
                         break;
                     case 28:
                         stepMode = DccThrottle::SpeedStepMode28;
                         break;
                     case 128:
                         stepMode = DccThrottle::SpeedStepMode128;
                         break;
                 }
                 msg = tr("StepMode must be 14, 27, 28, or 128.");
             } catch (Exception e) {
                 msg = tr("Invalid Number");
             }
             ts->setValue(QString::number(stepMode));
         } else if (QString::compare("FORWARD",cmd,Qt::CaseInsensitive)==0)
          {
//                try {
//                    Boolean.parseBoolean(value.totring());
//                } catch (Exception e) {
//                    msg = tr("invalid Boolean.  Please enter true or false.");
//                }
             ts->setValue(value.toString());
         } else if (cmd.startsWith("F")) {
//                try {
//                    Boolean.parseBoolean(value.totring());
//                } catch (Exception e) {
//                    msg = tr("invalidBoolean");
//                }
             ts->setValue(value.toString());
         } else if (cmd.startsWith("LOCKF")) {
//                try {
//                    Boolean.parseBoolean(value.totring());
//                } catch (Exception e) {
//                    msg = tr("invalidBoolean");
//                }
             ts->setValue(value.toString());
         } else if ("SET SENSOR"==(cmd) || "WAIT SENSOR"==(cmd)) {
             QString v = value.toString().toUpper();
             if ("ACTIVE"==(v) || "INACTIVE"==(v)) {
                 ts->setValue(value.toString());
             } else {
                 msg = tr("badSensorCommand");
             }
         } else if ("RUN WARRANT"==(cmd)) {
             try {
                 int num = value.toInt();
                 ts->setValue(value.toString());
             } catch (NumberFormatException nfe) {
                 msg  =tr("\"%1\" is an invalid value for Command \"%2\".").arg(value.toString()).arg(cmd);
             }
         }
          else {
                ts->setValue(nullptr);
            }
            if (resetBlockColumn) {
                ts->setNamedBeanHandle(getPreviousBlockHandle(row));
            }
         break;
     }
     case BLOCK_COLUMN:
     {
      if (ts==nullptr || ts->getCommand()=="" )
      {
          msg = tr("Enter a value in the %1 column first.").arg(tr("Command"));
          break;
      }
      QString cmd = ts->getCommand().toUpper();
      if ("SET SENSOR" ==(cmd) || "WAIT SENSOR" ==(cmd))
      {
          try {
              Sensor* s = InstanceManager::sensorManagerInstance()->getSensor(value.toString());
              if (s != nullptr) {
                  ts->setNamedBean(cmd, value.toString());
              } else {
                  msg = tr("Sensor \"%1\" not found.").arg(value.toString());
              }
          } catch (Exception ex) {
              msg = tr("Sensor \"%1\" not found.").arg(value.toString()) + ex.getMessage();
          }
      }
      else if ("NOOP" == (cmd))
      {
          msg = tr("Cannot change the block of a synchronization marker.  Only the elapsed time can be modified. %1").arg(value.toString());
      }
      else if ("RUN WARRANT" ==(cmd))
      {
       try
       {
           Warrant* w = ((WarrantManager*)InstanceManager::getDefault("WarrantManager"))->getWarrant(value.toString());
           if (w != nullptr)
           {
               ts->setNamedBean(cmd, value.toString());
           } else {
               msg = tr("Warrant \"%1\" not found.").arg(value.toString());
           }
       } catch (Exception ex) {
           msg = tr("Warrant \"%1\" not found.").arg(value.toString()) + ex.getMessage();
       }
      }
      else {
          NamedBeanHandle<NamedBean*>* bh = getPreviousBlockHandle(row);
          if (bh != nullptr) {
              QString name = bh->getBean()->getDisplayName();
              if (name!=(value.toString())) {
                  msg = tr("This command must be in block \"%1\".").arg(name);
                  ts->setNamedBeanHandle(bh);
              }
          }
      }
      break;
  }
  case SPEED_COLUMN:
       break;
   default:
    break;
 }
 if (msg != NULL) {
//        JOptionPane.showMessageDialog(NULL, msg,
//                tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
     QMessageBox::warning(NULL, tr("Warning"), msg);
 } else {
     //fireTableRowsUpdated(row, row);
     beginResetModel();
     endResetModel();
 }
 }
 return false;
}

///*private*/ QString ThrottleTableModel::getPreviousBlockName(int row) {
//    for (int i=row; i>0; i--) {
//        QString name = frame->_throttleCommands->at(i-1)->getBlockName();
//        OBlock* b = ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getOBlock(name);
//        if (b!=NULL) {
//            return name;
//        }
//    }
//    return "StartBlock";
//}
/*private*/ NamedBeanHandle <NamedBean*>* ThrottleTableModel::getPreviousBlockHandle(int row)
{
    for (int i = row; i > 0; i--) {
        NamedBeanHandle <NamedBean*>* bh = frame->_throttleCommands->at(i - 1)->getNamedBeanHandle();
        //if (bh != null && (bh.getBean() instanceof OBlock))
        if(bh!= nullptr && qobject_cast<OBlock*>(bh->getBean()))
        {
            return bh;
        }
    }
    return nullptr;
}
void ThrottleTableModel::fireTableDataChanged()
{
 beginResetModel();
 endResetModel();
}
/*public*/ QString WarrantFrame::getClassName()
{
 return "jmri.jmrit.logix.WarrantFrame";
}

//};

