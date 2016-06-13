#include "blockbossframe.h"
#include <QVBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include "jmrijframe.h"
#include "jtextfield.h"
#include <QLabel>
#include <QPushButton>
#include "blockbosslogic.h"
#include "instancemanager.h"
#include "gridbagconstraints.h"
#include "abstractsignalheadmanager.h"
#include <QMessageBox>
#include <QButtonGroup>
#include "proxysensormanager.h"
#include "abstractsignalheadmanager.h"
#include "savemenu.h"
#include "panelmenu.h"

//BlockBossFrame::BlockBossFrame(QWidget *parent) :
//    QMainWindow(parent)
//{
//}

/**
 * Provide a GUI for configuring "Simple Signal Logic" (BlockBossLogic) objects.
 * <P>
 * Provides four panels, corresponding to the four possible
 * modes described in {@link BlockBossLogic}, which
 * are then selected via radio buttons in the GUI.
 * <P>
 * The four modes are:
 * <UL>
 * <LI>Single block (s)
 * <LI>Facing point (f)
 * <LI>Trailing point main (tm)
 * <LI>Trailing point diverging (td)
 * </UL>
 * <P>
 * The multiple-panel approach to the GUI is used to make layout easier;
 * the code just flips from one to the other as the user selects a mode.
 * The individual items all share data models to simplify the logic.
 *
 * @author	Bob Jacobsen    Copyright (C) 2003, 2005
 * @version     $Revision: 17977 $
 *
 *              Revisions to add facing point sensors, approach lighting,
 *              limited speed, changed layout, and tool tips.
 *                                                  Dick Bronson (RJB) 2006

*/

// /*public*/ class BlockBossFrame extends jmri.util.JmriJFrame {


//    /*public*/ BlockBossFrame() { this(tr("Simple_Signal_Logic"));}
/*public*/ BlockBossFrame::BlockBossFrame(QString frameName, QWidget *parent) : JmriJFrame(frameName, false, true, parent)
{

 // create the frame
 //super(frameName, false, true);
    init();

 //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
 QWidget* centralWidget = new QWidget();
 QVBoxLayout* centralWidgetLayout;
 centralWidget->setLayout(centralWidgetLayout = new QVBoxLayout);
 setCentralWidget(centralWidget);
 resize(400,800);
 // add save menu item
 QMenuBar* menuBar = new QMenuBar();
 setMenuBar(menuBar);
 //ResourceBundle rb = ResourceBundle.getBundle("apps.AppsBundle");
 QMenu* fileMenu = new QMenu(tr("File"));
 menuBar->addMenu(fileMenu);
 fileMenu->addMenu(new SaveMenu());
 setMenuBar(menuBar);
 addHelpMenu(tr("package.jmri.jmrit.blockboss.BlockBossFrame"), true);
 // create GUI items
 sLimitBox  = new QCheckBox(tr("Limited Speed"));
 tmLimitBox = new QCheckBox(tr("Limited Speed"));
 //        tmLimitBox.setModel(sLimitBox.getModel());
 fmLimitBox  = new QCheckBox(tr("Limited Speed"));
 //        fmLimitBox.setModel(sLimitBox.getModel());

 tdLimitBox = new QCheckBox(tr("Limited Speed"));
 fdLimitBox  = new QCheckBox(tr("Limited Speed"));
 //        fdLimitBox.setModel(tdLimitBox.getModel());



 sFlashBox  = new QCheckBox(tr("With Flashing Yellow"));
 tmFlashBox = new QCheckBox(tr("With Flashing Yellow"));
//        tmFlashBox.setModel(sFlashBox.getModel());
tdFlashBox = new QCheckBox(tr("With Flashing Yellow"));
//        tdFlashBox.setModel(sFlashBox.getModel());
fFlashBox  = new QCheckBox(tr("With Flashing Yellow"));
//        fFlashBox.setModel(sFlashBox.getModel());

sDistantBox  = new QCheckBox(tr("Is Distant Signal"));
tmDistantBox = new QCheckBox(tr("Is Distant Signal"));
//        tmDistantBox.setModel(sDistantBox.getModel());
tdDistantBox = new QCheckBox(tr("Is Distant Signal"));
//        tdDistantBox.setModel(sDistantBox.getModel());
fDistantBox  = new QCheckBox(tr("Is Distant Signal"));
//        fDistantBox.setModel(sDistantBox.getModel());

 buttonSingle = new QRadioButton(tr("On Single Block"));
 buttonTrailMain = new QRadioButton(tr("Main Leg of Turnout"));
 buttonTrailDiv = new QRadioButton(tr("Diverging Leg of Turnout"));
 buttonFacing = new QRadioButton(tr("On Facing-Point Turnout"));
 QButtonGroup* g = new QButtonGroup();
 g->addButton(buttonSingle);
 g->addButton(buttonTrailMain);
 g->addButton(buttonTrailDiv);
 g->addButton(buttonFacing);
//        ActionListener a = new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                buttonClicked();
//            }
//        };
 //buttonSingle.addActionListener(a);
 connect(buttonSingle, SIGNAL(toggled(bool)), this, SLOT(buttonClicked()));
 //buttonTrailMain.addActionListener(a);
 connect(buttonTrailMain, SIGNAL(toggled(bool)), this, SLOT(buttonClicked()));
 //buttonTrailDiv.addActionListener(a);
 connect(buttonTrailDiv, SIGNAL(toggled(bool)), this, SLOT(buttonClicked()));
 //buttonFacing.addActionListener(a);
 connect(buttonFacing, SIGNAL(toggled(bool)), this, SLOT(buttonClicked()));

// share data models
//tmSensorField1->setDocument(sSensorField1->getDocument());
tmSensorField1->setShare(sSensorField1);
//tdSensorField1->setDocument(sSensorField1->getDocument());
tdSensorField1->setShare(sSensorField1);
//fSensorField1->setDocument(sSensorField1->getDocument());
fSensorField1->setShare(sSensorField1);

//tmSensorField2->setDocument(sSensorField2->getDocument());
tmSensorField2->setShare(sSensorField2);
//tdSensorField2->setDocument(sSensorField2->getDocument());
tdSensorField2->setShare(sSensorField2);
//fSensorField2->setDocument(sSensorField2->getDocument());
fSensorField2->setShare(sSensorField2);

//tmSensorField3->setDocument(sSensorField3->getDocument());
tmSensorField3->setShare(sSensorField3);
//tdSensorField3->setDocument(sSensorField3->getDocument());
tdSensorField3->setShare(sSensorField3);
//fSensorField3->setDocument(sSensorField3->getDocument());
fSensorField3->setShare(sSensorField3);

//tmSensorField4->setDocument(sSensorField4->getDocument());
tmSensorField4->setShare(sSensorField4);
//tdSensorField4->setDocument(sSensorField4->getDocument());
tdSensorField4->setShare(sSensorField4);
//fSensorField4->setDocument(sSensorField4->getDocument());
fSensorField4->setShare(sSensorField4);

//tmSensorField5->setDocument(sSensorField5->getDocument());
tmSensorField5->setShare(sSensorField5);
//tdSensorField5->setDocument(sSensorField5->getDocument());
tdSensorField5->setShare(sSensorField5);
//fSensorField5->setDocument(sSensorField5->getDocument());
fSensorField5->setShare(sSensorField5);

//tdProtectTurnoutField->setDocument(tmProtectTurnoutField->getDocument());
tdProtectTurnoutField->setShare(tmProtectTurnoutField);
//fProtectTurnoutField->setDocument(tmProtectTurnoutField->getDocument());
fProtectTurnoutField->setShare(tmProtectTurnoutField);

//tdNextSignalField1->setDocument(sNextSignalField1->getDocument());
tdNextSignalField1->setShare(sNextSignalField1);
//tdNextSignalField1Alt->setDocument(sNextSignalField1Alt->getDocument());
tdNextSignalField1Alt->setShare(sNextSignalField1Alt);
//tmNextSignalField1->setDocument(sNextSignalField1->getDocument());
tmNextSignalField1->setShare(sNextSignalField1);
//tmNextSignalField1Alt->setDocument(sNextSignalField1Alt->getDocument());
tmNextSignalField1->setShare(sNextSignalField1Alt);
//fNextSignalField1->setDocument(sNextSignalField1->getDocument());
fNextSignalField1->setShare(sNextSignalField1);
//fNextSignalField1Alt->setDocument(sNextSignalField1Alt->getDocument());
fNextSignalField1Alt->setShare(sNextSignalField1Alt);

 // add top part of GUI, holds signal head name to drive
 QWidget* line = new QWidget();
 line->setLayout(new QHBoxLayout());
 QHBoxLayout* lineHLayout = new QHBoxLayout;
 lineHLayout->addWidget(new   QLabel(tr("Signal Named ")));
 lineHLayout->addWidget(outSignalField= new JTextField(12));
  outSignalField->setToolTip(outSignalFieldTooltip);
 //outSignalField.addActionListener(new ActionListener() {
 //    /*public*/ void actionPerformed(ActionEvent e) {
 //        // user hit enter, use this name to fill in the rest of the fields
 //        activate();
 //    }
 //});
  //connect(outSignalField, SIGNAL(returnPressed()), this, SLOT(activate()));
  connect(outSignalField, SIGNAL(editingFinished()), this, SLOT(activate()));

 //centralWidgetLayout->addL(line, Qt::AlignHCenter);
  centralWidgetLayout->addLayout(lineHLayout);

// line = new QWidget();
// line->setLayout(new QVBoxLayout(line/*, BoxLayout.Y_AXIS*/));
  QVBoxLayout* lineVLayout = new QVBoxLayout;
 buttonSingle->setToolTip(buttonSingleTooltip);
 lineVLayout->addWidget(buttonSingle, Qt::AlignHCenter);
 buttonTrailMain->setToolTip(buttonTrailMainTooltip);
 lineVLayout->addWidget(buttonTrailMain, Qt::AlignHCenter);
 buttonTrailDiv->setToolTip(buttonTrailDivTooltip);
 lineVLayout->addWidget(buttonTrailDiv, Qt::AlignHCenter);
 buttonFacing->setToolTip(buttonFacingTooltip);
 lineVLayout->addWidget(buttonFacing, Qt::AlignHCenter);
 //line->setAlignmentX(0.5f);
 //centralWidget->layout()->addWidget(line);
 centralWidgetLayout->addLayout(lineVLayout);

 QFrame* separator = new QFrame();
   separator->setObjectName(QString::fromUtf8("line"));
   separator->setGeometry(QRect(10, 30, 571, 16));
   separator->setFrameShape(QFrame::HLine);
   separator->setFrameShadow(QFrame::Sunken);
 centralWidgetLayout->addWidget(separator);

 // fill in the specific panels for the modes
 centralWidgetLayout->addWidget(fillModeSingle());
 centralWidgetLayout->addWidget(fillModeTrailMain());
 centralWidgetLayout->addWidget(fillModeTrailDiv());
 centralWidgetLayout->addWidget(fillModeFacing());

// line = new QWidget();
// line->setLayout(new QHBoxLayout());
 lineHLayout = new QHBoxLayout;
 lineHLayout->addWidget(new QLabel(tr("Approach Lighting Sensor ")));
 lineHLayout->addWidget(approachSensorField1= new JTextField(6));
approachSensorField1->setToolTip(approachSensor1Tooltip);
// line.setAlignmentX(0.5f);
 //centralWidget->layout()->addWidget(line);
 centralWidgetLayout->addLayout(lineHLayout);

// line = new QWidget();
// line->setLayout(new QHBoxLayout());
 lineHLayout = new QHBoxLayout;
 lineHLayout->addWidget(new QLabel(tr("Comment: ")));
 lineHLayout->addWidget(commentField = new JTextField(30));
 centralWidgetLayout->addWidget(line, Qt::AlignHCenter);

 //centralWidget->layout()->addWidget(new QFrame(separator));
 centralWidgetLayout->addLayout(lineHLayout);

 // add OK button at bottom
 QPushButton* b = new QPushButton(tr("Apply"));
 // b.setAlignmentX(0.5f);
 centralWidgetLayout->addWidget(b);
 centralWidgetLayout->setAlignment(b, Qt::AlignHCenter);

 //b.addActionListener(new ActionListener(){
 //    /*public*/ void actionPerformed(ActionEvent e) {
 //        okPressed();
 //    }
 //});
 connect(b, SIGNAL(clicked()),this, SLOT(okPressed()));
 pack();
 // set a definite mode selection, which also repacks.
 buttonSingle->setChecked(true);buttonClicked();
}
void BlockBossFrame::init()
{
 log = new Logger("BlockBossFrame");
 modeSingle               = new QWidget();
 sSensorField1        = new JTextField(6);
 connect(sSensorField1, SIGNAL(textChanged(QString)), this, SLOT(on_sSensorField1_textChanged(QString)));
 sSensorField2        = new JTextField(6);
 connect(sSensorField2, SIGNAL(textChanged(QString)), this, SLOT(on_sSensorField1_textChanged(QString)));
 sSensorField3        = new JTextField(6);
 connect(sSensorField3, SIGNAL(textChanged(QString)), this, SLOT(on_sSensorField1_textChanged(QString)));
 sSensorField4        = new JTextField(6);
 connect(sSensorField4, SIGNAL(textChanged(QString)), this, SLOT(on_sSensorField1_textChanged(QString)));
 sSensorField5        = new JTextField(6);
 connect(sSensorField5, SIGNAL(textChanged(QString)), this, SLOT(on_sSensorField1_textChanged(QString)));
 sNextSignalField1    = new JTextField(10);
 connect(sNextSignalField1, SIGNAL(textChanged(QString)), this, SLOT(on_sNextSignalField1_textChanged(QString)));
 sNextSignalField1Alt = new JTextField(10);
 connect(sNextSignalField1Alt, SIGNAL(textChanged(QString)), this, SLOT(on_sNextSignalField1Alt_textChanged(QString)));

 modeTrailMain                = new QWidget();
 tmSensorField1           = new JTextField(6);
 tmSensorField2           = new JTextField(6);
 tmSensorField3           = new JTextField(6);
 tmSensorField4           = new JTextField(6);
 tmSensorField5           = new JTextField(6);
 tmProtectTurnoutField    = new JTextField(6);
 tmNextSignalField1       = new JTextField(10);
 tmNextSignalField1Alt    = new JTextField(10);
 connect(tmSensorField1, SIGNAL(textEdited(QString)), this, SLOT(on_tmSensorField1_textChanged(QString)));
 connect(tmSensorField2, SIGNAL(textEdited(QString)), this, SLOT(on_tmSensorField2_textChanged(QString)));
 connect(tmSensorField5, SIGNAL(textEdited(QString)), this, SLOT(on_tmSensorField3_textChanged(QString)));
 connect(tmSensorField5, SIGNAL(textEdited(QString)), this, SLOT(on_tmSensorField4_textChanged(QString)));
 connect(tmSensorField5, SIGNAL(textEdited(QString)), this, SLOT(on_tmSensorField5_textChanged(QString)));
 connect(tmProtectTurnoutField, SIGNAL(textEdited(QString)), this, SLOT(on_tmProtectTurnoutField_textChanged(QString)));
 connect(tmNextSignalField1, SIGNAL(textEdited(QString)), this, SLOT(on_tmNextSignalField1_textChanged(QString)));
 connect(tmNextSignalField1Alt, SIGNAL(textEdited(QString)), this, SLOT(on_tmNextSignalField1Alt_textChanged(QString)));
 modeTrailDiv                 = new QWidget();
 tdSensorField1           = new JTextField(6);
 tdSensorField2           = new JTextField(6);
 tdSensorField3           = new JTextField(6);
 tdSensorField4           = new JTextField(6);
 tdSensorField5           = new JTextField(6);
 tdProtectTurnoutField    = new JTextField(6);
 tdNextSignalField1       = new JTextField(6);
 tdNextSignalField1Alt    = new JTextField(6);
 connect(tdSensorField1, SIGNAL(textEdited(QString)), this, SLOT(on_tdSensorField1_textChanged(QString)));
 connect(tdSensorField2, SIGNAL(textEdited(QString)), this, SLOT(on_tdSensorField2_textChanged(QString)));
 connect(tdSensorField5, SIGNAL(textEdited(QString)), this, SLOT(on_tdSensorField3_textChanged(QString)));
 connect(tdSensorField5, SIGNAL(textEdited(QString)), this, SLOT(on_tdSensorField4_textChanged(QString)));
 connect(tdSensorField5, SIGNAL(textEdited(QString)), this, SLOT(on_tdSensorField5_textChanged(QString)));
 connect(tdProtectTurnoutField, SIGNAL(textEdited(QString)), this, SLOT(on_tdProtectTurnoutField_textChanged(QString)));
 connect(tdNextSignalField1, SIGNAL(textEdited(QString)), this, SLOT(on_tdNextSignalField1_textChanged(QString)));
 connect(tdNextSignalField1Alt, SIGNAL(textEdited(QString)), this, SLOT(on_tdNextSignalField1Alt_textChanged(QString)));
 modeFacing               = new QWidget();
 fSensorField1        = new JTextField(6);
 fSensorField2        = new JTextField(6);
 fSensorField3        = new JTextField(6);
 fSensorField4        = new JTextField(6);
 fSensorField5        = new JTextField(6);
 fProtectTurnoutField = new JTextField(6);
 fNextSignalField1    = new JTextField(10);
 fNextSignalField1Alt = new JTextField(10);
 fNextSignalField2    = new JTextField(10);
 fNextSignalField2Alt = new JTextField(10);
 fNextSensorField1    = new JTextField(6);
 fNextSensorField1Alt = new JTextField(6);
 fNextSensorField2    = new JTextField(6);
 fNextSensorField2Alt = new JTextField(6);
 connect(fSensorField1, SIGNAL(textEdited(QString)), this, SLOT(on_fSensorField1_textChanged(QString)));
 connect(fSensorField2, SIGNAL(textEdited(QString)), this, SLOT(on_fSensorField2_textChanged(QString)));
 connect(fSensorField3, SIGNAL(textEdited(QString)), this, SLOT(on_fSensorField3_textChanged(QString)));
 connect(fSensorField4, SIGNAL(textEdited(QString)), this, SLOT(on_fSensorField4_textChanged(QString)));
 connect(fSensorField5, SIGNAL(textEdited(QString)), this, SLOT(on_fSensorField5_textChanged(QString)));
 connect(fProtectTurnoutField, SIGNAL(textEdited(QString)), this, SLOT(on_fProtectTurnoutField_textChanged(QString)));
 connect(fNextSignalField1, SIGNAL(textEdited(QString)), this, SLOT(on_fNextSensorField1_textChanged(QString)));
 connect(fNextSignalField1Alt, SIGNAL(textEdited(QString)), this, SLOT(on_fNextSensorField1Alt_textChanged(QString)));
 connect(fNextSignalField2, SIGNAL(textEdited(QString)), this, SLOT(on_fNextSignalField2_textChanged(QString)));
 connect(fNextSignalField2Alt, SIGNAL(textEdited(QString)), this, SLOT(on_fNextSensorField2Alt_textChanged(QString)));
 connect(fNextSensorField1, SIGNAL(textEdited(QString)), this, SLOT(on_fNextSensorField1_textChanged(QString)));
 connect(fNextSensorField1Alt, SIGNAL(textEdited(QString)), this, SLOT(on_fNextSensorField1Alt_textChanged(QString)));
 connect(fNextSensorField2, SIGNAL(textEdited(QString)), this, SLOT(on_fNextSensorField2_textChanged(QString)));
 connect(fNextSensorField2Alt, SIGNAL(textEdited(QString)), this, SLOT(on_fNextSensorField2Alt_textChanged(QString)));


  buttonSingleTooltip = tr("In direction of traffic");
  buttonTrailMainTooltip = tr("Signal head for main track through turnout in either direction");
  buttonTrailDivTooltip = tr("Signal head for branching track through turnout in either direction");
  buttonFacingTooltip = tr("Single signal head on single track facing double track");
  outSignalFieldTooltip =  tr("Enter a new signal head number, or enter an existing signal head number then hit return to load its information.");
  approachSensor1Tooltip = tr("Enter sensor that lights this signal or leave blank for always on.");
  sensorFieldTooltip =  tr("Sensor active sets this signal to Red.");
  turnoutFieldTooltip = tr("Enter protected turnout number here.");
  flashBoxTooltip = tr("One aspect faster than yellow displays flashing yellow, rather than green.");
  limitBoxTooltip = tr("Limits the fastest aspect displayed to yellow, rather than green.");
  nextSignalFieldTooltip = tr("Enter the low speed signal head for this track. For dual head signals the fastest aspect is protected.");
  highSignalFieldTooltip = tr("Enter the high speed signal head for this track. For dual head signals the fastest aspect is protected.");
 distantBoxTooltip = tr("Mirrors the protected (following) signal's status unless over ridden by an intermediate stop sensor.");
}

// Panel arrangements all changed to use GridBagLayout format. RJB

QWidget* BlockBossFrame::fillModeSingle()
{
 QGridLayout* g;
 modeSingle->setLayout(g = new QGridLayout());

 GridBagConstraints* constraints = new GridBagConstraints();
    constraints->anchor = GridBagConstraints::EAST;
    constraints->gridheight = 1;
    constraints->gridwidth = 1;
    constraints->ipadx = 0;
    constraints->ipady = 0;
    Insets* insets = new Insets(2, 3, 2, 3); // top, left, bottom, right
    constraints->insets = insets;
    constraints->weightx = 1;
    constraints->weighty = 1;

    constraints->fill = GridBagConstraints::NONE;
    constraints->gridx = 0;
    constraints->gridy = 0;
    insets->top = 9;
    insets->bottom = 9;

    //modeSingle->layout()->addWidget(new QLabel(tr("Protects_Sensor/s")), constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    g->addWidget(new QLabel(tr("Protects Sensor/s")),constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->fill = GridBagConstraints::HORIZONTAL;
    constraints->gridx = 1;
    sSensorField1->setToolTip(sensorFieldTooltip);
    //modeSingle->layout()->addWidget(sSensorField1, constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    g->addWidget(sSensorField1, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 2;
    sSensorField2->setToolTip(sensorFieldTooltip);
    //modeSingle->layout()->addWidget(sSensorField2, constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    g->addWidget(sSensorField2, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 3;
    sSensorField3->setToolTip(sensorFieldTooltip);
    //modeSingle->layout()->addWidget(sSensorField3, constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    g->addWidget(sSensorField3, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 4;
    sSensorField4->setToolTip(sensorFieldTooltip);
    //modeSingle->layout()->addWidget(sSensorField4, constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    g->addWidget(sSensorField4, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 5;
    sSensorField5->setToolTip(sensorFieldTooltip);
    //modeSingle->layout()->addWidget(sSensorField5, constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    g->addWidget(sSensorField5, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());

    insets->top = 2;
    constraints->gridx = 0;
    constraints->gridy = 1;
    constraints->fill = GridBagConstraints::NONE;

    //modeSingle->layout()->addWidget(new QLabel(tr("Protects_Signal")), constraints->gridx,constraints->rowSpan(), constraints->colSpan());
     g->addWidget(new QLabel(tr("Protects Signal")), constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
     constraints->fill = GridBagConstraints::HORIZONTAL;
    constraints->gridx = 1;
    sNextSignalField1->setToolTip(highSignalFieldTooltip);
    //modeSingle->layout()->addWidget(sNextSignalField1, constraints->gridx,constraints->rowSpan(), constraints->colSpan());
     g->addWidget(sNextSignalField1, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
     constraints->gridx = 2;
    sNextSignalField1Alt->setToolTip(nextSignalFieldTooltip);
    //modeSingle->layout()->addWidget(sNextSignalField1Alt, constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    g->addWidget(sNextSignalField1Alt, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 3;
    constraints->gridwidth = 2;
    sLimitBox->setToolTip(limitBoxTooltip);
    //modeSingle->layout()->addWidget(sLimitBox, constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    g->addWidget(sLimitBox, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());

    constraints->gridy = 6;
    constraints->gridx = 1;
    constraints->gridwidth = 2;
    constraints->anchor = GridBagConstraints::WEST;
    insets->bottom = 9;
    sFlashBox->setToolTip(flashBoxTooltip);
    //modeSingle->layout()->addWidget(sFlashBox, constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    g->addWidget(sFlashBox, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());

    constraints->gridx = 3;
    sDistantBox->setToolTip(distantBoxTooltip);
    //modeSingle->layout()->addWidget(sDistantBox, constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    g->addWidget(sDistantBox, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    return modeSingle;
}

QWidget* BlockBossFrame::fillModeTrailMain() {
#if 1
    QGridLayout* g;

    modeTrailMain->setLayout(g = new QGridLayout());

    GridBagConstraints* constraints = new GridBagConstraints();
    constraints->anchor = GridBagConstraints::EAST;
    constraints->gridheight = 1;
    constraints->gridwidth = 1;
    constraints->ipadx = 0;
    constraints->ipady = 0;
    Insets* insets = new Insets(2, 3, 2, 3); // top, left, bottom, right
    constraints->insets = insets;
    constraints->weightx = 1;
    constraints->weighty = 1;

    constraints->fill = GridBagConstraints::NONE;
    constraints->gridx = 0;
    constraints->gridy = 0;
    insets->top = 9;
    insets->bottom = 9;
    g->addWidget(new QLabel(tr("_Protects_Sensor/s")), constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->fill = GridBagConstraints::HORIZONTAL;
    constraints->gridx = 1;
    tmSensorField1->setToolTip(sensorFieldTooltip);
    g->addWidget(tmSensorField1, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 2;
    tmSensorField2->setToolTip(sensorFieldTooltip);
    g->addWidget(tmSensorField2, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 3;
    tmSensorField3->setToolTip(sensorFieldTooltip);
    g->addWidget(tmSensorField3, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 4;
    tmSensorField4->setToolTip(sensorFieldTooltip);
    g->addWidget(tmSensorField4, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 5;
    tmSensorField5->setToolTip(sensorFieldTooltip);
    g->addWidget(tmSensorField5, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());

    insets->top = 2;
    constraints->fill = GridBagConstraints::NONE;
    constraints->gridx = 0;
    constraints->gridy = 1;
    insets->bottom = 9;
    g->addWidget(new QLabel(tr("Red When Turnout")), constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->fill = GridBagConstraints::HORIZONTAL;
    constraints->gridx = 1;
    tmProtectTurnoutField->setToolTip(turnoutFieldTooltip);
    g->addWidget(tmProtectTurnoutField, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 2;
    constraints->gridwidth = 2;
    g->addWidget(new QLabel(tr("Is ")+((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getThrownText()), constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridwidth = 1;

    constraints->fill = GridBagConstraints::NONE;
    constraints->gridx = 0;
    constraints->gridy = 4;
    insets->bottom = 2;
    g->addWidget(new QLabel(tr("Protects_Signal")), constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->fill = GridBagConstraints::HORIZONTAL;
    constraints->gridx = 1;
    tmNextSignalField1->setToolTip(highSignalFieldTooltip);
    g->addWidget(tmNextSignalField1, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 2;
    tmNextSignalField1Alt->setToolTip(nextSignalFieldTooltip);
    g->addWidget(tmNextSignalField1Alt, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 3;
    constraints->gridwidth = 2;
    tmLimitBox->setToolTip(limitBoxTooltip);
    g->addWidget(tmLimitBox, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());

    constraints->gridy = 6;
    constraints->gridx = 1;
    constraints->gridwidth = 2;
    constraints->anchor = GridBagConstraints::WEST;
    insets->bottom = 9;
    tmFlashBox->setToolTip(flashBoxTooltip);
    g->addWidget(tmFlashBox, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());

    constraints->gridx = 3;
    tmDistantBox->setToolTip(distantBoxTooltip);
    g->addWidget(tmDistantBox, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
#endif
    return modeTrailMain;
}

QWidget* BlockBossFrame::fillModeTrailDiv() {
#if 1
    QGridLayout* g;
    modeTrailDiv->setLayout(g = new QGridLayout());

    GridBagConstraints* constraints = new GridBagConstraints();
    constraints->anchor = GridBagConstraints::EAST;
    constraints->gridheight = 1;
    constraints->gridwidth = 1;
    constraints->ipadx = 0;
    constraints->ipady = 0;
    Insets* insets = new Insets(2, 3, 2, 3); // top, left, bottom, right
    constraints->insets = insets;
    constraints->weightx = 1;
    constraints->weighty = 1;

    constraints->fill = GridBagConstraints::NONE;
    constraints->gridx = 0;
    constraints->gridy = 0;
    insets->top = 9;
    insets->bottom = 9;
    g->addWidget(new QLabel(tr("_Protects_Sensor/s")), constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->fill = GridBagConstraints::HORIZONTAL;
    constraints->gridx = 1;
    tdSensorField1->setToolTip(sensorFieldTooltip);
    g->addWidget(tdSensorField1, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 2;
    tdSensorField2->setToolTip(sensorFieldTooltip);
    g->addWidget(tdSensorField2, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 3;
    tdSensorField3->setToolTip(sensorFieldTooltip);
    g->addWidget(tdSensorField3, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 4;
    tdSensorField4->setToolTip(sensorFieldTooltip);
    g->addWidget(tdSensorField4, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 5;
    tdSensorField5->setToolTip(sensorFieldTooltip);
    g->addWidget(tdSensorField5, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());

    insets->top = 2;
    constraints->fill = GridBagConstraints::NONE;
    constraints->gridx = 0;
    constraints->gridy = 1;
    insets->bottom = 9;
    g->addWidget(new QLabel(tr("Red When Turnout")), constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->fill = GridBagConstraints::HORIZONTAL;
    constraints->gridx = 1;
    tdProtectTurnoutField->setToolTip(turnoutFieldTooltip);
    g->addWidget(tdProtectTurnoutField, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 2;
    constraints->gridwidth = 2;
    g->addWidget(new QLabel(tr("Is_")+((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getClosedText()), constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridwidth = 1;

    constraints->fill = GridBagConstraints::NONE;
    constraints->gridx = 0;
    constraints->gridy = 4;
    insets->bottom = 2;
    g->addWidget(new QLabel(tr("Protects_Signal")), constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->fill = GridBagConstraints::HORIZONTAL;
    constraints->gridx = 1;
    tdNextSignalField1->setToolTip(highSignalFieldTooltip);
    g->addWidget(tdNextSignalField1, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 2;
    tdNextSignalField1Alt->setToolTip(nextSignalFieldTooltip);
    g->addWidget(tdNextSignalField1Alt, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 3;
    constraints->gridwidth = 2;
    tdLimitBox->setToolTip(limitBoxTooltip);
    g->addWidget(tdLimitBox, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());

    constraints->gridy = 6;
    constraints->gridx = 1;
    constraints->gridwidth = 2;
    constraints->anchor = GridBagConstraints::WEST;
    insets->bottom = 9;
    tdFlashBox->setToolTip(flashBoxTooltip);
    g->addWidget(tdFlashBox, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());

    constraints->gridx = 3;
    tdDistantBox->setToolTip(distantBoxTooltip);
    g->addWidget(tdDistantBox, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());

#endif
    return modeTrailDiv;
}

QWidget* BlockBossFrame::fillModeFacing() {
#if 1
    QGridLayout* g;
    modeFacing->setLayout(g =new QGridLayout());

    GridBagConstraints* constraints = new GridBagConstraints();
    constraints->anchor = GridBagConstraints::EAST;
    constraints->gridheight = 1;
    constraints->gridwidth = 1;
    constraints->ipadx = 0;
    constraints->ipady = 0;
    Insets* insets = new Insets(2, 3, 2, 3); // top, left, bottom, right
    constraints->insets = insets;
    constraints->weightx = 1;
    constraints->weighty = 1;

    constraints->fill = GridBagConstraints::NONE;
    constraints->gridx = 0;
    constraints->gridy = 0;
    insets->top = 9;
    insets->bottom = 9;
    g->addWidget(new QLabel(tr("Protects_Sensor/s")), constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->fill = GridBagConstraints::HORIZONTAL;
    constraints->gridx = 1;
    fSensorField1->setToolTip(sensorFieldTooltip);
    g->addWidget(fSensorField1, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 2;
    fSensorField2->setToolTip(sensorFieldTooltip);
    g->addWidget(fSensorField2, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 3;
    fSensorField3->setToolTip(sensorFieldTooltip);
    g->addWidget(fSensorField3, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 4;
    fSensorField4->setToolTip(sensorFieldTooltip);
    g->addWidget(fSensorField4, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 5;
    fSensorField5->setToolTip(sensorFieldTooltip);
    g->addWidget(fSensorField5, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());

    insets->top = 2;
    constraints->fill = GridBagConstraints::NONE;
    constraints->gridx = 0;
    constraints->gridy = 1;
    insets->bottom = 9;
    g->addWidget(new QLabel(tr("Watches_Turnout")), constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->fill = GridBagConstraints::HORIZONTAL;
    constraints->gridx = 1;
    fProtectTurnoutField->setToolTip(turnoutFieldTooltip);
    g->addWidget(fProtectTurnoutField, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());

    constraints->fill = GridBagConstraints::NONE;
    constraints->gridx = 0;
    constraints->gridy = 2;
    insets->bottom = 2;
    g->addWidget(new QLabel(tr("To_Protect_Signal")), constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->fill = GridBagConstraints::HORIZONTAL;
    constraints->gridx = 1;
    fNextSignalField1->setToolTip(highSignalFieldTooltip);
    g->addWidget(fNextSignalField1, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 2;
    fNextSignalField1Alt->setToolTip(nextSignalFieldTooltip);
    g->addWidget(fNextSignalField1Alt, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 3;
    constraints->gridwidth = 2;
    fmLimitBox->setToolTip(limitBoxTooltip);
    g->addWidget(fmLimitBox, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());

    constraints->fill = GridBagConstraints::NONE;
    constraints->gridwidth = 1;
    constraints->gridx = 0;
    constraints->gridy = 3;
    insets->bottom = 9;
    g->addWidget(new QLabel(tr("And Sensor/s")), constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->fill = GridBagConstraints::HORIZONTAL;
    constraints->gridx = 1;
    fNextSensorField1->setToolTip(sensorFieldTooltip);
    g->addWidget(fNextSensorField1, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 2;
    fNextSensorField1Alt->setToolTip(sensorFieldTooltip);
    g->addWidget(fNextSensorField1Alt,constraints->gridy, constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 3;
    constraints->gridwidth = 2;
    g->addWidget(new QLabel(tr("When Turnout is ")+((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getClosedText()), constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridwidth = 1;

    constraints->fill = GridBagConstraints::NONE;
    constraints->gridx = 0;
    constraints->gridy = 4;
    insets->bottom = 2;
    g->addWidget(new QLabel(tr("And Protect Signal")), constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->fill = GridBagConstraints::HORIZONTAL;
    constraints->gridx = 1;
    fNextSignalField2->setToolTip(highSignalFieldTooltip);
    g->addWidget(fNextSignalField2, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 2;
    fNextSignalField2Alt->setToolTip(nextSignalFieldTooltip);
    g->addWidget(fNextSignalField2Alt, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 3;
    constraints->gridwidth = 2;
    fdLimitBox->setToolTip(limitBoxTooltip);
    g->addWidget(fdLimitBox, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());

    constraints->fill = GridBagConstraints::NONE;
    constraints->gridwidth = 1;
    constraints->gridx = 0;
    constraints->gridy = 5;
    insets->bottom = 9;
    g->addWidget(new QLabel(tr("And_Sensor/s")), constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->fill = GridBagConstraints::HORIZONTAL;
    constraints->gridx = 1;
    fNextSensorField2->setToolTip(sensorFieldTooltip);
    g->addWidget(fNextSensorField2, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 2;
    fNextSensorField2Alt->setToolTip(sensorFieldTooltip);
    g->addWidget(fNextSensorField2Alt, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridx = 3;
    constraints->gridwidth = 2;
    g->addWidget(new QLabel(tr("When Turnout is ")+((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getThrownText()), constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());
    constraints->gridwidth = 1;

    constraints->gridy = 6;
    constraints->gridx = 1;
    constraints->gridwidth = 2;
    constraints->anchor = GridBagConstraints::WEST;
    insets->bottom = 9;
    fFlashBox->setToolTip(flashBoxTooltip);
    g->addWidget(fFlashBox, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());

    constraints->gridx = 3;
    fDistantBox->setToolTip(distantBoxTooltip);
    g->addWidget(fDistantBox, constraints->gridy,constraints->gridx,constraints->rowSpan(), constraints->colSpan());

#endif
    return modeFacing;
}

void BlockBossFrame::okPressed()  // SLOT[]
{
 // check signal head exists
 if (((AbstractSignalHeadManager*)InstanceManager::signalHeadManagerInstance())->getSignalHead(outSignalField->text().trimmed())==NULL)
 {
  setWindowTitle(tr("Simple Signal Logic"));
    //    JOptionPane.showMessageDialog(this,tr("Signal_head_")+outSignalField->text()+tr(" is not defined yet"));
  QMessageBox::critical(this, tr("Error"), tr("Signal head ")+outSignalField->text()+tr(" is not defined yet"));
    return;
 }
// it does
 try
 {
  BlockBossLogic* b = BlockBossLogic::getStoppedObject(outSignalField->text().trimmed());
  b->setApproachSensor1(approachSensorField1->text());
  if (buttonSingle->isChecked())
   loadSingle(b);
  else if (buttonTrailMain->isChecked())
   loadTrailMain(b);
  else if (buttonTrailDiv->isChecked())
   loadTrailDiv(b);
  else if (buttonFacing->isChecked())
   loadFacing(b);
  else
  {
   log->error(tr("no button selected?"));
   return;
  }
 }
 catch (Exception e)
 {
  log->error("An error occured creating the boss logic " + e.getMessage());
    //JOptionPane.showMessageDialog(this,"An error occured creating the Simple Signal Logic\nPlease check the console log for more information");
  QMessageBox::critical(this, tr("Error"), tr("An error occured creating the Simple Signal Logic\nPlease check the console log for more information"));
 }
}

void BlockBossFrame::loadSingle(BlockBossLogic* b) {
    b->setSensor1(sSensorField1->text());
    b->setSensor2(sSensorField2->text());
    b->setSensor3(sSensorField3->text());
    b->setSensor4(sSensorField4->text());
    b->setSensor5(sSensorField5->text());
    b->setMode(BlockBossLogic::SINGLEBLOCK);

    b->setWatchedSignal1(sNextSignalField1->text().trimmed(), sFlashBox->isChecked());
    b->setWatchedSignal1Alt(sNextSignalField1Alt->text().trimmed());
    b->setLimitSpeed1(sLimitBox->isChecked());
    b->setDistantSignal(sDistantBox->isChecked());

    b->setComment(commentField->text());

    b->retain();
    b->start();
}

void BlockBossFrame::loadTrailMain(BlockBossLogic* b) {
    b->setSensor1(tmSensorField1->text());
    b->setSensor2(tmSensorField2->text());
    b->setSensor3(tmSensorField3->text());
    b->setSensor4(tmSensorField4->text());
    b->setSensor5(tmSensorField5->text());
    b->setMode(BlockBossLogic::TRAILINGMAIN);

    b->setTurnout(tmProtectTurnoutField->text());

    b->setWatchedSignal1(tmNextSignalField1->text(), tmFlashBox->isChecked());
    b->setWatchedSignal1Alt(tmNextSignalField1Alt->text());
    b->setLimitSpeed1(tmLimitBox->isChecked());
    b->setDistantSignal(tmDistantBox->isChecked());

    b->setComment(commentField->text());

    b->retain();
    b->start();
}
void BlockBossFrame::loadTrailDiv(BlockBossLogic* b) {
    b->setSensor1(tdSensorField1->text());
    b->setSensor2(tdSensorField2->text());
    b->setSensor3(tdSensorField3->text());
    b->setSensor4(tdSensorField4->text());
    b->setSensor5(tdSensorField5->text());
    b->setMode(BlockBossLogic::TRAILINGDIVERGING);

    b->setTurnout(tdProtectTurnoutField->text());

    b->setWatchedSignal1(tdNextSignalField1->text(), tdFlashBox->isChecked());
    b->setWatchedSignal1Alt(tdNextSignalField1Alt->text());
    b->setLimitSpeed2(tdLimitBox->isChecked());
    b->setDistantSignal(tdDistantBox->isChecked());

    b->setComment(commentField->text());

    b->retain();
    b->start();
}

void BlockBossFrame::loadFacing(BlockBossLogic* b) {
    b->setSensor1(fSensorField1->text());
    b->setSensor2(fSensorField2->text());
    b->setSensor3(fSensorField3->text());
    b->setSensor4(fSensorField4->text());
    b->setSensor5(fSensorField5->text());
    b->setMode(BlockBossLogic::FACING);

    b->setTurnout(fProtectTurnoutField->text());

    b->setWatchedSignal1(fNextSignalField1->text(), fFlashBox->isChecked());
    b->setWatchedSignal1Alt(fNextSignalField1Alt->text());
    b->setWatchedSignal2(fNextSignalField2->text());
    b->setWatchedSignal2Alt(fNextSignalField2Alt->text());
    b->setWatchedSensor1(fNextSensorField1->text());
    b->setWatchedSensor1Alt(fNextSensorField1Alt->text());
    b->setWatchedSensor2(fNextSensorField2->text());
    b->setWatchedSensor2Alt(fNextSensorField2Alt->text());
    b->setLimitSpeed1(fmLimitBox->isChecked());
    b->setLimitSpeed2(fdLimitBox->isChecked());

    b->setDistantSignal(fDistantBox->isChecked());

    b->setComment(commentField->text());

    b->retain();
    b->start();
}

void BlockBossFrame::activate() // SLOT[]
{
 // check signal head exists
 if (((AbstractSignalHeadManager*)InstanceManager::signalHeadManagerInstance())->getSignalHead(outSignalField->text())==NULL)
 {
  setWindowTitle(tr("Simple Signal Logic"));
  return;
 }

 // find existing logic
 BlockBossLogic* b = BlockBossLogic::getExisting(outSignalField->text());
 if (b==NULL)
 {
  setWindowTitle(tr("Simple Signal Logic"));
  return;
 }

 setWindowTitle(tr("Signal logic for ")+outSignalField->text());

 approachSensorField1->setText(b->getApproachSensor1());

 sSensorField1->setText(b->getSensor1());
 sSensorField2->setText(b->getSensor2());
 sSensorField3->setText(b->getSensor3());
 sSensorField4->setText(b->getSensor4());
 sSensorField5->setText(b->getSensor5());

 tmProtectTurnoutField->setText(b->getTurnout());

 sNextSignalField1->setText(b->getWatchedSignal1());
 sNextSignalField1Alt->setText(b->getWatchedSignal1Alt());

 fNextSignalField2->setText(b->getWatchedSignal2());
 fNextSignalField2Alt->setText(b->getWatchedSignal2Alt());

 fNextSensorField1->setText(b->getWatchedSensor1());
 fNextSensorField1Alt->setText(b->getWatchedSensor1Alt());
 fNextSensorField2->setText(b->getWatchedSensor2());
 fNextSensorField2Alt->setText(b->getWatchedSensor2Alt());

 sLimitBox->setChecked(b->getLimitSpeed1());
 tdLimitBox->setChecked(b->getLimitSpeed2());
 sFlashBox->setChecked(b->getUseFlash());
 sDistantBox->setChecked(b->getDistantSignal());

 commentField->setText(b->getComment());

 int mode = b->getMode();
 if (mode == BlockBossLogic::SINGLEBLOCK)
  buttonSingle->setChecked(true);
 else if (mode == BlockBossLogic::TRAILINGMAIN)
  buttonTrailMain->setChecked(true);
 else if (mode == BlockBossLogic::TRAILINGDIVERGING)
  buttonTrailDiv->setChecked(true);
 else if (mode == BlockBossLogic::FACING)
  buttonFacing->setChecked(true);

 // do setup of visible panels
 buttonClicked();
}

void BlockBossFrame::buttonClicked() // SLOT[]
{
 modeSingle->setVisible(false);
 modeTrailMain->setVisible(false);
 modeTrailDiv->setVisible(false);
 modeFacing->setVisible(false);
 if (buttonSingle->isChecked())
  modeSingle->setVisible(true);
 else if (buttonTrailMain->isChecked())
  modeTrailMain->setVisible(true);
 else if (buttonTrailDiv->isChecked())
  modeTrailDiv->setVisible(true);
 else if (buttonFacing->isChecked())
  modeFacing->setVisible(true);
 else
 {
  log->debug(tr("no_button_selected?"));
 }
//    modeSingle->validate();
//    modeTrailMain->validate();
//    modeTrailDiv->validate();
//    modeFacing->validate();
    pack();
//    modeSingle.repaint();
//    modeTrailMain.repaint();
//    modeTrailDiv.repaint();
//    modeFacing.repaint();
}

/**
 * Programmatically open the frame to edit a specific signal
 */
/*public*/ void BlockBossFrame::setSignal(QString name)
{
 outSignalField->setText(name);
 activate();
}

void BlockBossFrame::on_sSensorField1_textChanged(QString s)
{
 sSensorField1->setCompleter(((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getCompleter(s));
}
void BlockBossFrame::on_sSensorField2_textChanged(QString s)
{
 sSensorField2->setCompleter(((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getCompleter(s));
}
void BlockBossFrame::on_sSensorField3_textChanged(QString s)
{
 sSensorField3->setCompleter(((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getCompleter(s));
}
void BlockBossFrame::on_sSensorField4_textChanged(QString s)
{
 sSensorField4->setCompleter(((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getCompleter(s));
}
void BlockBossFrame::on_sSensorField5_textChanged(QString s)
{
 sSensorField5->setCompleter(((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getCompleter(s));
}
void BlockBossFrame::on_sNextSignalField1_textChanged(QString s)
{
 sNextSignalField1->setCompleter(((AbstractSignalHeadManager*)InstanceManager::signalHeadManagerInstance())->getCompleter(s,true));
}
void BlockBossFrame::on_sNextSignalField1Alt_textChanged(QString s)
{
 sNextSignalField1Alt->setCompleter(((AbstractSignalHeadManager*)InstanceManager::signalHeadManagerInstance())->getCompleter(s,true));
}

void BlockBossFrame::on_tmSensorField1_textChanged(QString s)
{
 tmSensorField1->  setCompleter(((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getCompleter(s));
}
void BlockBossFrame::on_tmSensorField2_textChanged(QString s)
{
 tmSensorField2->  setCompleter(((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getCompleter(s));
}
void BlockBossFrame::on_tmSensorField3_textChanged(QString s)
{
 tmSensorField3->  setCompleter(((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getCompleter(s));
}
void BlockBossFrame::on_tmSensorField4_textChanged(QString s)
{
 tmSensorField4->  setCompleter(((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getCompleter(s));
}
void BlockBossFrame::on_tmSensorField5_textChanged(QString s)
{
 tmSensorField5->  setCompleter(((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getCompleter(s));
}
void BlockBossFrame::on_tmProtectTurnoutField_textChanged(QString s)
{
 tmProtectTurnoutField->  setCompleter(((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getCompleter(s));
}
void BlockBossFrame::on_tmNextSignalField1_textChanged(QString s)
{
 tmNextSignalField1->setCompleter(((AbstractSignalHeadManager*)InstanceManager::signalHeadManagerInstance())->getCompleter(s,true));
}
void BlockBossFrame::on_tmNextSignalField1Alt_textChanged(QString s)
{
 tmNextSignalField1Alt->setCompleter(((AbstractSignalHeadManager*)InstanceManager::signalHeadManagerInstance())->getCompleter(s,true));
}
void BlockBossFrame::on_tdSensorField1_textChanged(QString s)
{
 tdSensorField1->  setCompleter(((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getCompleter(s));
}
void BlockBossFrame::on_tdSensorField2_textChanged(QString s)
{
 tdSensorField2->  setCompleter(((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getCompleter(s));
}
void BlockBossFrame::on_tdSensorField3_textChanged(QString s)
{
 tdSensorField3->  setCompleter(((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getCompleter(s));
}
void BlockBossFrame::on_tdSensorField4_textChanged(QString s)
{
 tdSensorField4->  setCompleter(((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getCompleter(s));
}
void BlockBossFrame::on_tdSensorField5_textChanged(QString s)
{
 tdSensorField5->  setCompleter(((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getCompleter(s));
}
void BlockBossFrame::on_tdProtectTurnoutField_textChanged(QString s)
{
 tdProtectTurnoutField->  setCompleter(((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getCompleter(s));
}
void BlockBossFrame::on_tdNextSignalField1_textChanged(QString s)
{
 tdNextSignalField1->setCompleter(((AbstractSignalHeadManager*)InstanceManager::signalHeadManagerInstance())->getCompleter(s,true));
}
void BlockBossFrame::on_tdNextSignalField1Alt_textChanged(QString s)
{
 tdNextSignalField1Alt->setCompleter(((AbstractSignalHeadManager*)InstanceManager::signalHeadManagerInstance())->getCompleter(s,true));
}

void BlockBossFrame::on_fSensorField1_textChanged(QString s)
{
 fSensorField1->  setCompleter(((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getCompleter(s));
}
void BlockBossFrame::on_fSensorField2_textChanged(QString s)
{
 fSensorField2->  setCompleter(((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getCompleter(s));
}
void BlockBossFrame::on_fSensorField3_textChanged(QString s)
{
 fSensorField3->  setCompleter(((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getCompleter(s));
}
void BlockBossFrame::on_fSensorField4_textChanged(QString s)
{
 fSensorField4->  setCompleter(((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getCompleter(s));
}
void BlockBossFrame::on_fSensorField5_textChanged(QString s)
{
 fSensorField5->  setCompleter(((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getCompleter(s));
}
void BlockBossFrame::on_fProtectTurnoutField_textChanged(QString s)
{
 fProtectTurnoutField->  setCompleter(((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getCompleter(s));
}
void BlockBossFrame::on_fNextSignalField1_textChanged(QString s)
{
 fNextSignalField1->setCompleter(((AbstractSignalHeadManager*)InstanceManager::signalHeadManagerInstance())->getCompleter(s,true));
}
void BlockBossFrame::on_fNextSignalField1Alt_textChanged(QString s)
{
 fNextSignalField1Alt->setCompleter(((AbstractSignalHeadManager*)InstanceManager::signalHeadManagerInstance())->getCompleter(s,true));
}
void BlockBossFrame::on_fNextSignalField2_textChanged(QString s)
{
 fNextSignalField2->setCompleter(((AbstractSignalHeadManager*)InstanceManager::signalHeadManagerInstance())->getCompleter(s,true));
}
void BlockBossFrame::on_fNextSignalField2Alt_textChanged(QString s)
{
 fNextSignalField2Alt->setCompleter(((AbstractSignalHeadManager*)InstanceManager::signalHeadManagerInstance())->getCompleter(s,true));
}
void BlockBossFrame::on_fNextSensorField1_textChanged(QString s)
{
 fNextSensorField1->setCompleter(((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getCompleter(s));
}
void BlockBossFrame::on_fNextSensorField1Alt_textChanged(QString s)
{
 fNextSensorField1Alt->setCompleter(((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getCompleter(s));
}
void BlockBossFrame::on_fNextSensorField2_textChanged(QString s)
{
 fNextSensorField2->setCompleter(((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getCompleter(s));
}
void BlockBossFrame::on_fNextSensorField2Alt_textChanged(QString s)
{
 fNextSensorField2Alt->setCompleter(((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getCompleter(s));
}
