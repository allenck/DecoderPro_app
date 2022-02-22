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
#include "joptionpane.h"
#include <QButtonGroup>
#include "proxysensormanager.h"
#include "abstractsignalheadmanager.h"
#include "savemenu.h"
#include "panelmenu.h"
#include "loggerfactory.h"
#include "storemenu.h"
#include "gridbaglayout.h"
#include "jseparator.h"
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

/*private*/ /*static*/ /*final*/ QString BlockBossFrame::SIMPLE_SIGNAL_LOGIC;// = "Simple_Signal_Logic";
/*private*/ /*static*/ /*final*/ QString BlockBossFrame::LIMITED_SPEED = "Limited_Speed";
/*private*/ /*static*/ /*final*/ QString BlockBossFrame::RESTRICTING_SPEED = "Restricting_Speed";
/*private*/ /*static*/ /*final*/ QString BlockBossFrame::WITH_FLASHING_YELLOW = "With_Flashing_Yellow";
/*private*/ /*static*/ /*final*/ QString BlockBossFrame::PROTECTS_SENSOR = "Protects Sensor/s:";
/*private*/ /*static*/ /*final*/ QString BlockBossFrame::IS_DISTANT_SIGNAL = "Is_Distant_Signal";
/*private*/ /*static*/ /*final*/ QString BlockBossFrame::PROTECTS_SIGNAL = "Protects Signal:";

// /*public*/ class BlockBossFrame extends jmri.util.JmriJFrame {

/*public*/ BlockBossFrame::BlockBossFrame(QString frameName, QWidget *parent) : JmriJFrame(frameName, false, true, parent)
{

 init();
}

void BlockBossFrame::init()
{
 blockBossLogicProvider = (BlockBossLogicProvider*)InstanceManager::getDefault("BlockBossLogicProvider");

 getContentPane()->setLayout(new QVBoxLayout());//getContentPane(), BoxLayout.Y_AXIS));

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
 sLimitBox  = new JCheckBox(tr("Limited Speed"));
 sRestrictingBox = new JCheckBox(tr("Restricting Speed"));
 tmRestrictingBox = new JCheckBox(tr("Restricting Speed"));
 //tmRestrictingBox->setModel(sRestrictingBox->getModel());
 tmLimitBox = new JCheckBox(tr("Limited Speed"));
 //        tmLimitBox.setModel(sLimitBox.getModel());
 fmLimitBox  = new JCheckBox(tr("Limited Speed"));
 //        fmLimitBox.setModel(sLimitBox.getModel());

 tdLimitBox = new JCheckBox(tr("Limited Speed"));
 tdRestrictingBox = new JCheckBox(tr("Restricting Speed"));
 fdLimitBox = new JCheckBox(tr("Limited Speed"));
 //fdLimitBox.setModel(tdLimitBox.getModel());
 fdRestrictingBox = new JCheckBox(tr("Restricting Speed"));
 //fdRestrictingBox.setModel(tdRestrictingBox.getModel());

 sFlashBox  = new JCheckBox(tr("With Flashing Yellow"));
 tmFlashBox = new JCheckBox(tr("With Flashing Yellow"));
 //        tmFlashBox.setModel(sFlashBox.getModel());
 tdFlashBox = new JCheckBox(tr("With Flashing Yellow"));
 //        tdFlashBox.setModel(sFlashBox.getModel());
 fFlashBox  = new JCheckBox(tr("With Flashing Yellow"));
 //        fFlashBox.setModel(sFlashBox.getModel());

sDistantBox  = new JCheckBox(tr("Is Distant Signal"));
tmDistantBox = new JCheckBox(tr("Is Distant Signal"));
//        tmDistantBox.setModel(sDistantBox.getModel());
tdDistantBox = new JCheckBox(tr("Is Distant Signal"));
//        tdDistantBox.setModel(sDistantBox.getModel());
fDistantBox  = new JCheckBox(tr("Is Distant Signal"));
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
 //buttonSingle.addActionListener(a);
 connect(buttonSingle, &JButton::clicked, [=]{ buttonClicked();});
 //buttonTrailMain.addActionListener(a);
 connect(buttonTrailMain, &JButton::clicked, [=]{ buttonClicked();});
 //buttonTrailDiv.addActionListener(a);
 connect(buttonTrailDiv, &JButton::clicked, [=]{ buttonClicked();});
 //buttonFacing.addActionListener(a);
 connect(buttonFacing, &JButton::clicked, [=]{ buttonClicked();});

 // share sensor data models
 tmSensorComboBox1->setModel(sSensorComboBox1->getModel());
 tdSensorComboBox1->setModel(sSensorComboBox1->getModel());
 fSensorComboBox1->setModel(sSensorComboBox1->getModel());

 tmSensorComboBox2->setModel(sSensorComboBox2->getModel());
 tdSensorComboBox2->setModel(sSensorComboBox2->getModel());
 fSensorComboBox2->setModel(sSensorComboBox2->getModel());

 tmSensorComboBox3->setModel(sSensorComboBox3->getModel());
 tdSensorComboBox3->setModel(sSensorComboBox3->getModel());
 fSensorComboBox3->setModel(sSensorComboBox3->getModel());

 tmSensorComboBox4->setModel(sSensorComboBox4->getModel());
 tdSensorComboBox4->setModel(sSensorComboBox4->getModel());
 fSensorComboBox4->setModel(sSensorComboBox4->getModel());

 tmSensorComboBox5->setModel(sSensorComboBox5->getModel());
 tdSensorComboBox5->setModel(sSensorComboBox5->getModel());
 fSensorComboBox5->setModel(sSensorComboBox5->getModel());
 // share turnout data model
 tmProtectTurnoutComboBox->setModel(tdProtectTurnoutComboBox->getModel());
 fProtectTurnoutComboBox->setModel(tdProtectTurnoutComboBox->getModel());

 tdNextSignalComboBox1->setModel(sNextSignalComboBox1->getModel());
 tdNextSignalComboBox1Alt->setModel(sNextSignalComboBox1Alt->getModel());
 tmNextSignalComboBox1->setModel(sNextSignalComboBox1->getModel());
 tmNextSignalComboBox1Alt->setModel(sNextSignalComboBox1Alt->getModel());
 fNextSignalComboBox1->setModel(sNextSignalComboBox1->getModel());
 fNextSignalComboBox1Alt->setModel(sNextSignalComboBox1Alt->getModel());

 // configure sensor combobox options
 setupComboBox(sSensorComboBox1, false, true, true);
 setupComboBox(sSensorComboBox2, false, true, true);
 setupComboBox(sSensorComboBox3, false, true, true);
 setupComboBox(sSensorComboBox4, false, true, true);
 setupComboBox(sSensorComboBox5, false, true, true);
 setupComboBox(tmSensorComboBox1, false, true, true);
 setupComboBox(tmSensorComboBox2, false, true, true);
 setupComboBox(tmSensorComboBox3, false, true, true);
 setupComboBox(tmSensorComboBox4, false, true, true);
 setupComboBox(tmSensorComboBox5, false, true, true);
 setupComboBox(tdSensorComboBox1, false, true, true);
 setupComboBox(tdSensorComboBox2, false, true, true);
 setupComboBox(tdSensorComboBox3, false, true, true);
 setupComboBox(tdSensorComboBox4, false, true, true);
 setupComboBox(tdSensorComboBox5, false, true, true);
 setupComboBox(fSensorComboBox1, false, true, true);
 setupComboBox(fSensorComboBox2, false, true, true);
 setupComboBox(fSensorComboBox3, false, true, true);
 setupComboBox(fSensorComboBox4, false, true, true);
 setupComboBox(fSensorComboBox5, false, true, true);
 // configure turnout combobox options
 setupComboBox(tdProtectTurnoutComboBox, false, true, true);
 setupComboBox(tmProtectTurnoutComboBox, false, true, true);
 setupComboBox(fProtectTurnoutComboBox, false, true, true);
 // configure next signal combobox options
 setupComboBox(sNextSignalComboBox1, false, true, true);
 setupComboBox(sNextSignalComboBox1Alt, false, true, true);
 setupComboBox(tdNextSignalComboBox1, false, true, true);
 setupComboBox(tdNextSignalComboBox1Alt, false, true, true);
 setupComboBox(tmNextSignalComboBox1, false, true, true);
 setupComboBox(tmNextSignalComboBox1Alt, false, true, true);
 setupComboBox(fNextSignalComboBox1, false, true, true);
 setupComboBox(fNextSignalComboBox1Alt, false, true, true);
 setupComboBox(fNextSignalComboBox2, false, true, true);
 setupComboBox(fNextSignalComboBox2Alt, false, true, true);
 // configure next sensor combobox options
 setupComboBox(fNextSensorComboBox1, false, true, true);
 setupComboBox(fNextSensorComboBox1Alt, false, true, true);
 setupComboBox(fNextSensorComboBox2, false, true, true);
 setupComboBox(fNextSensorComboBox2Alt, false, true, true);

 // add top part of GUI, holds signal head name to drive
 JPanel* line = new JPanel(new FlowLayout());
 line->layout()->addWidget(new JLabel(tr("For Signal Head:")));
 setupComboBox(outSignalHeadComboBox, true, true, true);
 line->layout()->addWidget(outSignalHeadComboBox);
 outSignalHeadComboBox->setToolTip(outSignalHeadTooltip);
// outSignalHeadComboBox.addActionListener(e ->
 connect(outSignalHeadComboBox, &NamedBeanComboBox::currentTextChanged, [=]{
     // user hit enter, use this name to fill in the rest of the fields
     activate();});

 getContentPane()->layout()->addWidget(line);

 line = new JPanel();
 line->setLayout(new QVBoxLayout());//line, BoxLayout.Y_AXIS));
 buttonSingle->setToolTip(buttonSingleTooltip);
 line->layout()->addWidget(buttonSingle);
 buttonTrailMain->setToolTip(buttonTrailMainTooltip);
 line->layout()->addWidget(buttonTrailMain);
 buttonTrailDiv->setToolTip(buttonTrailDivTooltip);
 line->layout()->addWidget(buttonTrailDiv);
 buttonFacing->setToolTip(buttonFacingTooltip);
 line->layout()->addWidget(buttonFacing);
// line.setAlignmentX(0.5f);
 getContentPane()->layout()->addWidget(line);

 getContentPane()->layout()->addWidget(new JSeparator(/*Qt::Horizontal*/));

 // fill in the specific panels for the modes
 getContentPane()->layout()->addWidget(fillModeSingle());
 getContentPane()->layout()->addWidget(fillModeTrailMain());
 getContentPane()->layout()->addWidget(fillModeTrailDiv());
 getContentPane()->layout()->addWidget(fillModeFacing());

 line = new JPanel();
 line->layout()->addWidget(new JLabel(tr("Approach Lighting Sensor:")));
 line->layout()->addWidget(approachSensor1ComboBox);
 setupComboBox(approachSensor1ComboBox, false, true, true);
 approachSensor1ComboBox->setToolTip(approachSensor1Tooltip);
// line.setAlignmentX(0.5f);
 getContentPane()->layout()->addWidget(line);

 // add comment element
 line = new JPanel();
 line->setLayout(new FlowLayout());
 line->layout()->addWidget(new JLabel(tr("Comment")));
 line->layout()->addWidget(commentField = new JTextField(30));
 commentField->setToolTip(tr("Your notes will be stored with this SSL"));
 getContentPane()->layout()->addWidget(line);

 // add status bar above buttons
 line = new JPanel();
 line->setLayout(new FlowLayout());
 statusBar = new JLabel(tr("Start by selecting a Signal Head at the top"));
 QFont f = statusBar->getFont();
 f.setPointSize(.9 * commentField->getFont().pointSizeF());
 statusBar->setFont(f); // a bit smaller
 statusBar->setForeground(Qt::gray);
 line->layout()->addWidget(statusBar);
 getContentPane()->layout()->addWidget(line);

 getContentPane()->layout()->addWidget(new JSeparator(/*SwingConstants.HORIZONTAL)*/));

 JPanel* buttons = new JPanel();
 buttons->setLayout(new FlowLayout());
 // add OK button at bottom

 _delete = new JButton(tr("Delete"));
 buttons->layout()->addWidget(_delete);
 //delete.addActionListener(e -> deletePressed());
 connect(_delete, &JButton::clicked, [=] {deletePressed();});
 _delete->setEnabled(false);

 cancel = new JButton(tr("Cancel"));
 buttons->layout()->addWidget(cancel);
 connect(cancel, &JButton::clicked, [=] {cancelPressed();});

 apply = new JButton(tr("Apply"));
 apply->setToolTip(tr("Press to create/update logic for this Signal Head."));
 buttons->layout()->addWidget(apply);
 apply->setEnabled(false);

 connect(apply, &JButton::clicked, [=] { applyPressed();});
 getContentPane()->layout()->addWidget(buttons);

 pack();
 // set a definite mode selection, which also repacks.
 buttonSingle->setChecked(true);
 buttonClicked();
}

QWidget* BlockBossFrame::fillModeSingle()
{
 GridBagLayout* modeSingleLayout;
 modeSingle->setLayout(modeSingleLayout = new GridBagLayout());

 GridBagConstraints constraints =  GridBagConstraints();
    constraints.anchor = GridBagConstraints::EAST;
    constraints.gridheight = 1;
    constraints.gridwidth = 1;
    constraints.ipadx = 0;
    constraints.ipady = 0;
    Insets* insets = new Insets(2, 3, 2, 3); // top, left, bottom, right
    constraints.insets = insets;
    constraints.weightx = 1;
    constraints.weighty = 1;

    constraints.fill = GridBagConstraints::NONE;
    constraints.gridx = 0;
    constraints.gridy = 0;
    insets->top = 9;
    insets->bottom = 9;

    modeSingleLayout->addWidget(new JLabel(tr("Protects Sensor/s:")), constraints);
    constraints.fill = GridBagConstraints::HORIZONTAL;
    constraints.gridx = 1;
    sSensorComboBox1->setToolTip(sensorFieldTooltip);
    modeSingleLayout->addWidget(sSensorComboBox1, constraints);
    constraints.gridx = 2;
    sSensorComboBox2->setToolTip(sensorFieldTooltip);
    modeSingleLayout->addWidget(sSensorComboBox2, constraints);
    constraints.gridx = 3;
    sSensorComboBox3->setToolTip(sensorFieldTooltip);
    modeSingleLayout->addWidget(sSensorComboBox3, constraints);
    constraints.gridx = 4;
    sSensorComboBox4->setToolTip(sensorFieldTooltip);
    modeSingleLayout->addWidget(sSensorComboBox4, constraints);
    constraints.gridx = 5;
    sSensorComboBox5->setToolTip(sensorFieldTooltip);
    modeSingleLayout->addWidget(sSensorComboBox5, constraints);

    insets->top = 2;
    constraints.gridx = 0;
    constraints.gridy = 1;
    constraints.fill = GridBagConstraints::NONE;

    modeSingleLayout->addWidget(new JLabel(tr("Protects Signal:")), constraints);
    constraints.fill = GridBagConstraints::HORIZONTAL;
    constraints.gridx = 1;
    sNextSignalComboBox1->setToolTip(highSignalFieldTooltip);
    modeSingleLayout->addWidget(sNextSignalComboBox1, constraints);
    constraints.gridx = 2;
    sNextSignalComboBox1Alt->setToolTip(nextSignalFieldTooltip);
    modeSingleLayout->addWidget(sNextSignalComboBox1Alt, constraints);
    constraints.gridx = 3;
    constraints.gridwidth = 2;
    // ??
    JPanel* q = new JPanel();
    q->setLayout(new FlowLayout());
    q->layout()->addWidget(sLimitBox);
    q->layout()->addWidget(sRestrictingBox);
    sLimitBox->setToolTip(limitBoxTooltip);
    sRestrictingBox->setToolTip(restrictingBoxTooltip);
    modeSingleLayout->addWidget(q, constraints);

    constraints.gridy = 6;
    constraints.gridx = 1;
    constraints.gridwidth = 2;
    constraints.anchor = GridBagConstraints::WEST;
    insets->bottom = 9;
    sFlashBox->setToolTip(flashBoxTooltip);
    modeSingleLayout->addWidget(sFlashBox, constraints);

    constraints.gridx = 3;
    sDistantBox->setToolTip(distantBoxTooltip);
    modeSingleLayout->addWidget(sDistantBox, constraints);
    return modeSingle;
}

QWidget* BlockBossFrame::fillModeTrailMain() {
 GridBagLayout* modeTrailMainLayout;
 modeTrailMain->setLayout(modeTrailMainLayout = new GridBagLayout());

 GridBagConstraints constraints = GridBagConstraints();
 constraints.anchor = GridBagConstraints::EAST;
 constraints.gridheight = 1;
 constraints.gridwidth = 1;
 constraints.ipadx = 0;
 constraints.ipady = 0;
 Insets* insets = new Insets(2, 3, 2, 3); // top, left, bottom, right
 constraints.insets = insets;
 constraints.weightx = 1;
 constraints.weighty = 1;

 constraints.fill = GridBagConstraints::NONE;
 constraints.gridx = 0;
 constraints.gridy = 0;
 insets->top = 9;
 insets->bottom = 9;
 modeTrailMainLayout->addWidget(new JLabel(tr("Protects Sensor/s:")), constraints);
 constraints.fill = GridBagConstraints::HORIZONTAL;
 constraints.gridx = 1;
 tmSensorComboBox1->setToolTip(sensorFieldTooltip);
 modeTrailMainLayout->addWidget(tmSensorComboBox1, constraints);
 constraints.gridx = 2;
 tmSensorComboBox2->setToolTip(sensorFieldTooltip);
 modeTrailMainLayout->addWidget(tmSensorComboBox2, constraints);
 constraints.gridx = 3;
 tmSensorComboBox3->setToolTip(sensorFieldTooltip);
 modeTrailMainLayout->addWidget(tmSensorComboBox3, constraints);
 constraints.gridx = 4;
 tmSensorComboBox4->setToolTip(sensorFieldTooltip);
 modeTrailMainLayout->addWidget(tmSensorComboBox4, constraints);
 constraints.gridx = 5;
 tmSensorComboBox5->setToolTip(sensorFieldTooltip);
 modeTrailMainLayout->addWidget(tmSensorComboBox5, constraints);

 insets->top = 2;
 constraints.fill = GridBagConstraints::NONE;
 constraints.gridx = 0;
 constraints.gridy = 1;
 insets->bottom = 9;
 modeTrailMainLayout->addWidget(new JLabel(tr("Red when Turnout:")), constraints);
 constraints.fill = GridBagConstraints::HORIZONTAL;
 constraints.gridx = 1;
 tmProtectTurnoutComboBox->setToolTip(turnoutFieldTooltip);
 modeTrailMainLayout->addWidget(tmProtectTurnoutComboBox, constraints);
 constraints.gridx = 2;
 constraints.gridwidth = 2;
 modeTrailMainLayout->addWidget(new JLabel(tr("state is: %1").arg(InstanceManager::turnoutManagerInstance()->getThrownText())), constraints);
 constraints.gridwidth = 1;

 constraints.fill = GridBagConstraints::NONE;
 constraints.gridx = 0;
 constraints.gridy = 4;
 insets->bottom = 2;
 modeTrailMainLayout->addWidget(new JLabel(tr("Protects Signal:")), constraints);
 constraints.fill = GridBagConstraints::HORIZONTAL;
 constraints.gridx = 1;
 tmNextSignalComboBox1->setToolTip(highSignalFieldTooltip);
 modeTrailMainLayout->addWidget(tmNextSignalComboBox1, constraints);
 constraints.gridx = 2;
 tmNextSignalComboBox1Alt->setToolTip(nextSignalFieldTooltip);
 modeTrailMainLayout->addWidget(tmNextSignalComboBox1Alt, constraints);
 constraints.gridx = 3;
 constraints.gridwidth = 2;
 // ??
 JPanel* q = new JPanel();
 q->setLayout(new FlowLayout());
 q->layout()->addWidget(tmLimitBox);
 q->layout()->addWidget(tmRestrictingBox);
 tmLimitBox->setToolTip(limitBoxTooltip);
 tmRestrictingBox->setToolTip(restrictingBoxTooltip);
 modeTrailMainLayout->addWidget(q, constraints);

 constraints.gridy = 6;
 constraints.gridx = 1;
 constraints.gridwidth = 2;
 constraints.anchor = GridBagConstraints::WEST;
 insets->bottom = 9;
 tmFlashBox->setToolTip(flashBoxTooltip);
 modeTrailMainLayout->addWidget(tmFlashBox, constraints);

 constraints.gridx = 3;
 tmDistantBox->setToolTip(distantBoxTooltip);
 modeTrailMainLayout->addWidget(tmDistantBox, constraints);
 return modeTrailMain;
}

QWidget* BlockBossFrame::fillModeTrailDiv() {
 GridBagLayout* modeTrailDivLayout;
 modeTrailDiv->setLayout(modeTrailDivLayout = new GridBagLayout());

 GridBagConstraints constraints = GridBagConstraints();
 constraints.anchor = GridBagConstraints::EAST;
 constraints.gridheight = 1;
 constraints.gridwidth = 1;
 constraints.ipadx = 0;
 constraints.ipady = 0;
 Insets* insets = new Insets(2, 3, 2, 3); // top, left, bottom, right
 constraints.insets = insets;
 constraints.weightx = 1;
 constraints.weighty = 1;

 constraints.fill = GridBagConstraints::NONE;
 constraints.gridx = 0;
 constraints.gridy = 0;
 insets->top = 9;
 insets->bottom = 9;
 modeTrailDivLayout->addWidget(new JLabel(tr("Protects Sensor/s:")), constraints);
 constraints.fill = GridBagConstraints::HORIZONTAL;
 constraints.gridx = 1;
 tdSensorComboBox1->setToolTip(sensorFieldTooltip);
 modeTrailDivLayout->addWidget(tdSensorComboBox1, constraints);
 constraints.gridx = 2;
 tdSensorComboBox2->setToolTip(sensorFieldTooltip);
 modeTrailDivLayout->addWidget(tdSensorComboBox2, constraints);
 constraints.gridx = 3;
 tdSensorComboBox3->setToolTip(sensorFieldTooltip);
 modeTrailDivLayout->addWidget(tdSensorComboBox3, constraints);
 constraints.gridx = 4;
 tdSensorComboBox4->setToolTip(sensorFieldTooltip);
 modeTrailDivLayout->addWidget(tdSensorComboBox4, constraints);
 constraints.gridx = 5;
 tdSensorComboBox5->setToolTip(sensorFieldTooltip);
 modeTrailDivLayout->addWidget(tdSensorComboBox5, constraints);

 insets->top = 2;
 constraints.fill = GridBagConstraints::NONE;
 constraints.gridx = 0;
 constraints.gridy = 1;
 insets->bottom = 9;
 modeTrailDivLayout->addWidget(new JLabel(tr("Red_When_Turnout")), constraints);
 constraints.fill = GridBagConstraints::HORIZONTAL;
 constraints.gridx = 1;
 tdProtectTurnoutComboBox->setToolTip(turnoutFieldTooltip);
 modeTrailDivLayout->addWidget(tdProtectTurnoutComboBox, constraints);
 constraints.gridx = 2;
 constraints.gridwidth = 2;
 modeTrailDivLayout->addWidget(new JLabel(tr("state is: %1").arg(InstanceManager::turnoutManagerInstance()->getClosedText())), constraints);
 constraints.gridwidth = 1;

 constraints.fill = GridBagConstraints::NONE;
 constraints.gridx = 0;
 constraints.gridy = 4;
 insets->bottom = 2;
 modeTrailDivLayout->addWidget(new JLabel(tr("Protects Signal:")), constraints);
 constraints.fill = GridBagConstraints::HORIZONTAL;
 constraints.gridx = 1;
 tdNextSignalComboBox1->setToolTip(highSignalFieldTooltip);
 modeTrailDivLayout->addWidget(tdNextSignalComboBox1, constraints);
 constraints.gridx = 2;
 tdNextSignalComboBox1Alt->setToolTip(nextSignalFieldTooltip);
 modeTrailDivLayout->addWidget(tdNextSignalComboBox1Alt, constraints);
 constraints.gridx = 3;
 constraints.gridwidth = 2;
 // ??
 JPanel* q = new JPanel();
 q->setLayout(new FlowLayout());
 q->layout()->addWidget(tdLimitBox);
 q->layout()->addWidget(tdRestrictingBox);
 tdLimitBox->setToolTip(limitBoxTooltip);
 tdRestrictingBox->setToolTip(restrictingBoxTooltip);
 modeTrailDivLayout->addWidget(q, constraints);

 constraints.gridy = 6;
 constraints.gridx = 1;
 constraints.gridwidth = 2;
 constraints.anchor = GridBagConstraints::WEST;
 insets->bottom = 9;
 tdFlashBox->setToolTip(flashBoxTooltip);
 modeTrailDivLayout->addWidget(tdFlashBox, constraints);

 constraints.gridx = 3;
 tdDistantBox->setToolTip(distantBoxTooltip);
 modeTrailDivLayout->addWidget(tdDistantBox, constraints);

 return modeTrailDiv;
}

QWidget* BlockBossFrame::fillModeFacing() {
 GridBagLayout* modeFacingLayout;
 modeFacing->setLayout(modeFacingLayout =new GridBagLayout());

        GridBagConstraints constraints =  GridBagConstraints();
        constraints.anchor = GridBagConstraints::EAST;
        constraints.gridheight = 1;
        constraints.gridwidth = 1;
        constraints.ipadx = 0;
        constraints.ipady = 0;
        Insets* insets = new Insets(2, 3, 2, 3); // top, left, bottom, right
        constraints.insets = insets;
        constraints.weightx = 1;
        constraints.weighty = 1;

        constraints.fill = GridBagConstraints::NONE;
        constraints.gridx = 0;
        constraints.gridy = 0;
        insets->top = 9;
        insets->bottom = 9;
        modeFacingLayout->addWidget(new JLabel(tr("Protects Sensor/s:")), constraints);
        constraints.fill = GridBagConstraints::HORIZONTAL;
        constraints.gridx = 1;
        fSensorComboBox1->setToolTip(sensorFieldTooltip);
        modeFacingLayout->addWidget(fSensorComboBox1, constraints);
        constraints.gridx = 2;
        fSensorComboBox2->setToolTip(sensorFieldTooltip);
        modeFacingLayout->addWidget(fSensorComboBox2, constraints);
        constraints.gridx = 3;
        fSensorComboBox3->setToolTip(sensorFieldTooltip);
        modeFacingLayout->addWidget(fSensorComboBox3, constraints);
        constraints.gridx = 4;
        fSensorComboBox4->setToolTip(sensorFieldTooltip);
        modeFacingLayout->addWidget(fSensorComboBox4, constraints);
        constraints.gridx = 5;
        fSensorComboBox5->setToolTip(sensorFieldTooltip);
        modeFacingLayout->addWidget(fSensorComboBox5, constraints);

        insets->top = 2;
        constraints.fill = GridBagConstraints::NONE;
        constraints.gridx = 0;
        constraints.gridy = 1;
        insets->bottom = 9;
        modeFacingLayout->addWidget(new JLabel(tr("Watches Turnout")), constraints);
        constraints.fill = GridBagConstraints::HORIZONTAL;
        constraints.gridx = 1;
        fProtectTurnoutComboBox->setToolTip(turnoutFieldTooltip);
        modeFacingLayout->addWidget(fProtectTurnoutComboBox, constraints);

        constraints.fill = GridBagConstraints::NONE;
        constraints.gridx = 0;
        constraints.gridy = 2;
        insets->bottom = 2;
        modeFacingLayout->addWidget(new JLabel(tr("To Protect Signal:")), constraints);
        constraints.fill = GridBagConstraints::HORIZONTAL;
        constraints.gridx = 1;
        fNextSignalComboBox1->setToolTip(highSignalFieldTooltip);
        modeFacingLayout->addWidget(fNextSignalComboBox1, constraints);
        constraints.gridx = 2;
        fNextSignalComboBox1Alt->setToolTip(nextSignalFieldTooltip);
        modeFacingLayout->addWidget(fNextSignalComboBox1Alt, constraints);
        constraints.gridx = 3;
        constraints.gridwidth = 2;
        // ??
        JPanel* q = new JPanel();
        q->setLayout(new FlowLayout());
        q->layout()->addWidget(fmLimitBox);
        q->layout()->addWidget(fmRestrictingBox);
        fmLimitBox->setToolTip(limitBoxTooltip);
        fmRestrictingBox->setToolTip(restrictingBoxTooltip);
        modeFacingLayout->addWidget(q, constraints);

        constraints.fill = GridBagConstraints::NONE;
        constraints.gridwidth = 1;
        constraints.gridx = 0;
        constraints.gridy = 3;
        insets->bottom = 9;
        modeFacingLayout->addWidget(new JLabel(tr("and Sensor/s:")), constraints);
        constraints.fill = GridBagConstraints::HORIZONTAL;
        constraints.gridx = 1;
        fNextSensorComboBox1->setToolTip(sensorFieldTooltip);
        modeFacingLayout->addWidget(fNextSensorComboBox1, constraints);
        constraints.gridx = 2;
        fNextSensorComboBox1Alt->setToolTip(sensorFieldTooltip);
        modeFacingLayout->addWidget(fNextSensorComboBox1Alt, constraints);
        constraints.gridx = 3;
        constraints.gridwidth = 2;
        modeFacingLayout->addWidget(new JLabel(tr("When watched Turnout''s state is: %1").arg(InstanceManager::turnoutManagerInstance()->getClosedText())), constraints);
        constraints.gridwidth = 1;

        constraints.fill = GridBagConstraints::NONE;
        constraints.gridx = 0;
        constraints.gridy = 4;
        insets->bottom = 2;
        modeFacingLayout->addWidget(new JLabel(tr("and Protect Signal:")), constraints);
        constraints.fill = GridBagConstraints::HORIZONTAL;
        constraints.gridx = 1;
        fNextSignalComboBox2->setToolTip(highSignalFieldTooltip);
        modeFacingLayout->addWidget(fNextSignalComboBox2, constraints);
        constraints.gridx = 2;
        fNextSignalComboBox2Alt->setToolTip(nextSignalFieldTooltip);
        modeFacingLayout->addWidget(fNextSignalComboBox2Alt, constraints);
        constraints.gridx = 3;
        constraints.gridwidth = 2;

        q = new JPanel();
        q->setLayout(new FlowLayout());
        q->layout()->addWidget(fdLimitBox);
        q->layout()->addWidget(fdRestrictingBox);
        fdLimitBox->setToolTip(limitBoxTooltip);
        fdRestrictingBox->setToolTip(restrictingBoxTooltip);
        modeFacingLayout->addWidget(q, constraints);

        constraints.fill = GridBagConstraints::NONE;
        constraints.gridwidth = 1;
        constraints.gridx = 0;
        constraints.gridy = 5;
        insets->bottom = 9;
        modeFacingLayout->addWidget(new JLabel(tr("and Sensor/s:")), constraints);
        constraints.fill = GridBagConstraints::HORIZONTAL;
        constraints.gridx = 1;
        fNextSensorComboBox2->setToolTip(sensorFieldTooltip);
        modeFacingLayout->addWidget(fNextSensorComboBox2, constraints);
        constraints.gridx = 2;
        fNextSensorComboBox2Alt->setToolTip(sensorFieldTooltip);
        modeFacingLayout->addWidget(fNextSensorComboBox2Alt, constraints);
        constraints.gridx = 3;
        constraints.gridwidth = 2;
        modeFacingLayout->addWidget(new JLabel(tr("When watched Turnout''s state is: %1").arg(InstanceManager::turnoutManagerInstance()->getThrownText())), constraints);
        constraints.gridwidth = 1;

        constraints.gridy = 6;
        constraints.gridx = 1;
        constraints.gridwidth = 2;
        constraints.anchor = GridBagConstraints::WEST;
        insets->bottom = 9;
        fFlashBox->setToolTip(flashBoxTooltip);
        modeFacingLayout->addWidget(fFlashBox, constraints);

        constraints.gridx = 3;
        fDistantBox->setToolTip(distantBoxTooltip);
        modeFacingLayout->addWidget(fDistantBox, constraints);

        return modeFacing;
}

/*private*/ void BlockBossFrame::applyPressed() {
 SignalHead* head = sh; // temp used here for SignalHead being operated on

 // check signal head selected
 if (head == nullptr) {
     head = (SignalHead*)(outSignalHeadComboBox->getSelectedItem())->self();
     statusBar->setText(tr("SSL created for Signal Head %1").arg(outSignalHeadComboBox->getSelectedItemDisplayName()));
 } else {
     statusBar->setText(tr("SSL updated for Signal Head %1").arg(outSignalHeadComboBox->getSelectedItemDisplayName()));
 }

 try {
     BlockBossLogic* b = BlockBossLogic::getStoppedObject(head->getDisplayName());
     b->setApproachSensor1(approachSensor1ComboBox->getSelectedItemDisplayName());
     if (buttonSingle->isChecked()) {
         loadSingle(b);
     } else if (buttonTrailMain->isChecked()) {
         loadTrailMain(b);
     } else if (buttonTrailDiv->isChecked()) {
         loadTrailDiv(b);
     } else if (buttonFacing->isChecked()) {
         loadFacing(b);
     } else {
         log->error("no SSL type radio button was selected"); // NOI18N
         return;
     }
     cancel->setText(tr("Close")); // when Apply has been clicked at least once, this is not Cancel
 } catch (IllegalArgumentException* e) {
     statusBar->setText(tr("An error occurred creating the Simple Signal Logic.\nCheck the Console log for more information."));
     JOptionPane::showMessageDialog(this,
             tr("An error occurred creating the Simple Signal Logic.\nCheck the Console log for more information."),
             tr("Error"),
             JOptionPane::ERROR_MESSAGE);
 }
}

/*private*/ void BlockBossFrame::cancelPressed() {
 // close pane
 this->setVisible(false);
 statusBar->setText("");
 JmriJFrame::dispose();
}

/*private*/ void BlockBossFrame::deletePressed() {
 BlockBossLogic* b = BlockBossLogic::getStoppedObject(outSignalHeadComboBox->getSelectedItemDisplayName());
 blockBossLogicProvider->remove(b);
 statusBar->setText(tr("SSL deleted for Signal Head %1").arg(outSignalHeadComboBox->getSelectedItemDisplayName()));
 outSignalHeadComboBox->setSelectedIndex(-1);
 clearFields();
}

void BlockBossFrame::loadSingle(BlockBossLogic* b) {
 b->setSensor1(sSensorComboBox1->getSelectedItemDisplayName());
 b->setSensor2(sSensorComboBox2->getSelectedItemDisplayName());
 b->setSensor3(sSensorComboBox3->getSelectedItemDisplayName());
 b->setSensor4(sSensorComboBox4->getSelectedItemDisplayName());
 b->setSensor5(sSensorComboBox5->getSelectedItemDisplayName());
 b->setMode(BlockBossLogic::SINGLEBLOCK);

 b->setWatchedSignal1(sNextSignalComboBox1->getSelectedItemDisplayName(), sFlashBox->isSelected());
 b->setWatchedSignal1Alt(sNextSignalComboBox1Alt->getSelectedItemDisplayName());
 b->setLimitSpeed1(sLimitBox->isSelected());
 b->setRestrictingSpeed1(sRestrictingBox->isSelected());
 b->setDistantSignal(sDistantBox->isSelected());

 b->setComment(commentField->text());

 blockBossLogicProvider->_register(b);
 b->start();
}

void BlockBossFrame::loadTrailMain(BlockBossLogic* b) {
 b->setSensor1(tmSensorComboBox1->getSelectedItemDisplayName());
 b->setSensor2(tmSensorComboBox2->getSelectedItemDisplayName());
 b->setSensor3(tmSensorComboBox3->getSelectedItemDisplayName());
 b->setSensor4(tmSensorComboBox4->getSelectedItemDisplayName());
 b->setSensor5(tmSensorComboBox5->getSelectedItemDisplayName());
 b->setMode(BlockBossLogic::TRAILINGMAIN);

 b->setTurnout(tmProtectTurnoutComboBox->getSelectedItemDisplayName());

 b->setWatchedSignal1(tmNextSignalComboBox1->getSelectedItemDisplayName(), tmFlashBox->isSelected());
 b->setWatchedSignal1Alt(tmNextSignalComboBox1Alt->getSelectedItemDisplayName());
 b->setLimitSpeed1(tmLimitBox->isSelected());
 b->setRestrictingSpeed1(tmRestrictingBox->isSelected());
 b->setDistantSignal(tmDistantBox->isSelected());

 b->setComment(commentField->text());

 blockBossLogicProvider->_register(b);
 b->start();
}

void BlockBossFrame::loadTrailDiv(BlockBossLogic* b) {
 b->setSensor1(tdSensorComboBox1->getSelectedItemDisplayName());
 b->setSensor2(tdSensorComboBox2->getSelectedItemDisplayName());
 b->setSensor3(tdSensorComboBox3->getSelectedItemDisplayName());
 b->setSensor4(tdSensorComboBox4->getSelectedItemDisplayName());
 b->setSensor5(tdSensorComboBox5->getSelectedItemDisplayName());
 b->setMode(BlockBossLogic::TRAILINGDIVERGING);

 b->setTurnout(tdProtectTurnoutComboBox->getSelectedItemDisplayName());

 b->setWatchedSignal1(tdNextSignalComboBox1->getSelectedItemDisplayName(), tdFlashBox->isSelected());
 b->setWatchedSignal1Alt(tdNextSignalComboBox1Alt->getSelectedItemDisplayName());
 b->setLimitSpeed2(tdLimitBox->isSelected());
 b->setRestrictingSpeed1(tdRestrictingBox->isSelected());
 b->setDistantSignal(tdDistantBox->isSelected());

 b->setComment(commentField->text());

 blockBossLogicProvider->_register(b);
 b->start();
}

void BlockBossFrame::loadFacing(BlockBossLogic* b) {
 b->setSensor1(fSensorComboBox1->getSelectedItemDisplayName());
 b->setSensor2(fSensorComboBox2->getSelectedItemDisplayName());
 b->setSensor3(fSensorComboBox3->getSelectedItemDisplayName());
 b->setSensor4(fSensorComboBox4->getSelectedItemDisplayName());
 b->setSensor5(fSensorComboBox5->getSelectedItemDisplayName());
 b->setMode(BlockBossLogic::FACING);

 b->setTurnout(fProtectTurnoutComboBox->getSelectedItemDisplayName());

 b->setWatchedSignal1(fNextSignalComboBox1->getSelectedItemDisplayName(), fFlashBox->isSelected());
 b->setWatchedSignal1Alt(fNextSignalComboBox1Alt->getSelectedItemDisplayName());
 b->setWatchedSignal2(fNextSignalComboBox2->getSelectedItemDisplayName());
 b->setWatchedSignal2Alt(fNextSignalComboBox2Alt->getSelectedItemDisplayName());
 b->setWatchedSensor1(fNextSensorComboBox1->getSelectedItemDisplayName());
 b->setWatchedSensor1Alt(fNextSensorComboBox1Alt->getSelectedItemDisplayName());
 b->setWatchedSensor2(fNextSensorComboBox2->getSelectedItemDisplayName());
 b->setWatchedSensor2Alt(fNextSensorComboBox2Alt->getSelectedItemDisplayName());
 b->setLimitSpeed1(fmLimitBox->isSelected());
 b->setRestrictingSpeed1(fmRestrictingBox->isSelected());
 b->setLimitSpeed2(fdLimitBox->isSelected());
 b->setRestrictingSpeed2(fdRestrictingBox->isSelected());

 b->setDistantSignal(fDistantBox->isSelected());

 b->setComment(commentField->text());

 blockBossLogicProvider->_register(b);
 b->start();
}

/*private*/ void BlockBossFrame::clearFields() {
  approachSensor1ComboBox->setSelectedIndex(-1);

  sSensorComboBox1->setSelectedIndex(-1);
  sSensorComboBox2->setSelectedIndex(-1);
  sSensorComboBox3->setSelectedIndex(-1);
  sSensorComboBox4->setSelectedIndex(-1);
  sSensorComboBox5->setSelectedIndex(-1);

  tmProtectTurnoutComboBox->setSelectedIndex(-1);

  sNextSignalComboBox1->setSelectedIndex(-1);
  sNextSignalComboBox1Alt->setSelectedIndex(-1);

  fNextSignalComboBox2->setSelectedIndex(-1);
  fNextSignalComboBox2Alt->setSelectedIndex(-1);

  fNextSensorComboBox1->setSelectedIndex(-1);
  fNextSensorComboBox1Alt->setSelectedIndex(-1);
  fNextSensorComboBox2->setSelectedIndex(-1);
  fNextSensorComboBox2Alt->setSelectedIndex(-1);

  sLimitBox->setSelected(false);
  sRestrictingBox->setSelected(false);
  tdLimitBox->setSelected(false);
  tdRestrictingBox->setSelected(false);
  sFlashBox->setSelected(false);
  sDistantBox->setSelected(false);

  commentField->setText("");

  buttonClicked();
}
void BlockBossFrame::activate() // SLOT[]
{
 // check signal head exists
 if (sh == nullptr && outSignalHeadComboBox->getSelectedItem() == nullptr) {
     // head not exist, just title the window and leave
     setTitle(tr("Simple Signal Logic"));
     apply->setEnabled(false);
     _delete->setEnabled(false);
     return;
 }

 // find existing logic
 BlockBossLogic* b;
 if (sh != nullptr) {
     b = blockBossLogicProvider->provide(sh);
 } else {
     b = blockBossLogicProvider->provide(outSignalHeadComboBox->getSelectedItemDisplayName());
 }
 apply->setEnabled(true);
 _delete->setEnabled(true);

 setTitle(tr("Simple Signal Logic for %1").arg(outSignalHeadComboBox->getSelectedItemDisplayName()));

 approachSensor1ComboBox->setSelectedItemByName(b->getApproachSensor1());

 sSensorComboBox1->setSelectedItemByName(b->getSensor1());
 sSensorComboBox2->setSelectedItemByName(b->getSensor2());
 sSensorComboBox3->setSelectedItemByName(b->getSensor3());
 sSensorComboBox4->setSelectedItemByName(b->getSensor4());
 sSensorComboBox5->setSelectedItemByName(b->getSensor5());

 tmProtectTurnoutComboBox->setSelectedItemByName(b->getTurnout());


 sNextSignalComboBox1->setSelectedItemByName(b->getWatchedSignal1());
 sNextSignalComboBox1Alt->setSelectedItemByName(b->getWatchedSignal1Alt());

 fNextSignalComboBox2->setSelectedItemByName(b->getWatchedSignal2());
 fNextSignalComboBox2Alt->setSelectedItemByName(b->getWatchedSignal2Alt());

 fNextSensorComboBox1->setSelectedItemByName(b->getWatchedSensor1());
 fNextSensorComboBox1Alt->setSelectedItemByName(b->getWatchedSensor1Alt());
 fNextSensorComboBox2->setSelectedItemByName(b->getWatchedSensor2());
 fNextSensorComboBox2Alt->setSelectedItemByName(b->getWatchedSensor2Alt());

 sLimitBox->setSelected(b->getLimitSpeed1());
 sRestrictingBox->setSelected(b->getRestrictingSpeed1());
 tdLimitBox->setChecked(b->getLimitSpeed2());
 tdRestrictingBox->setChecked(b->getRestrictingSpeed2());
 sFlashBox->setSelected(b->getUseFlash());
 sDistantBox->setSelected(b->getDistantSignal());

 commentField->setText(b->getComment());

 int mode = b->getMode();
 if (mode == BlockBossLogic::SINGLEBLOCK) {
     buttonSingle->setChecked(true);
 } else if (mode == BlockBossLogic::TRAILINGMAIN) {
     buttonTrailMain->setChecked(true);
 } else if (mode == BlockBossLogic::TRAILINGDIVERGING) {
     buttonTrailDiv->setChecked(true);
 } else if (mode == BlockBossLogic::FACING) {
     buttonFacing->setChecked(true);
 }

 statusBar->setText(tr("Check or change the SSL configuration on this pane and click [%1]").arg(tr("Apply")));
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
 sh = nullptr;
 outSignalHeadComboBox->setSelectedItemByName(name);
 outSignalHeadComboBox->setEnabled(true);
 activate();
}

/*public*/ QString BlockBossFrame::getClassName()
{
 return "jmri.jmrit.blockboss.BlockBossFrame";
}

/**
 * Set up editable NamedBeanComboBoxes for SSL pane.
 * Copied from LayoutEditor
 * @see jmri.jmrit.display.layoutEditor.LayoutEditor#setupComboBox(NamedBeanComboBox, boolean, boolean, boolean)
 * @author G. Warner 2017
 *
 * @param inComboBox     the editable NamedBeanComboBoxes to set up
 * @param inValidateMode boolean: if true, typed in text is validated; if
 *                       false input text is not
 * @param inEnable       boolean to enable / disable the NamedBeanComboBox
 * @param inFirstBlank   boolean to enable / disable the first item being
 *                       blank
 */
/*private*/ /*static*/ void BlockBossFrame::setupComboBox(/*@Nonnull*/ NamedBeanComboBox/*<?>*/* inComboBox, bool inValidateMode, bool inEnable, bool inFirstBlank) {
    log->debug("SSL setupComboBox called");
    inComboBox->setEnabled(inEnable);
    inComboBox->setEditable(false);
    inComboBox->setValidatingInput(inValidateMode);
    inComboBox->setSelectedItem(nullptr);
    inComboBox->setAllowNull(inFirstBlank);
//    JComboBoxUtil::setupComboBoxMaxRows(inComboBox);
    inComboBox->setSelectedIndex(-1);
}

/*private*/ /*static*/ /*final*/ Logger* BlockBossFrame::log = LoggerFactory::getLogger("BlockBossFrame");
