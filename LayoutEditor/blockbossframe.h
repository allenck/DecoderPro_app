#ifndef BLOCKBOSSFRAME_H
#define BLOCKBOSSFRAME_H

#include "jmrijframe.h"
#include <QRadioButton>
#include "jcheckbox.h"
#include "logger.h"
#include "blockbosslogicprovider.h"
#include "instancemanager.h"
#include "sensormanager.h"
#include "namedbeancombobox.h"
#include "jcheckbox.h"
#include "signalheadmanager.h"
#include "jbutton.h"
#include <QStatusBar>
#include "jlabel.h"
#include "jpanel.h"

class JTextField;
class BlockBossLogic;
class BlockBossFrame : public JmriJFrame
{
    Q_OBJECT
public:
    //explicit BlockBossFrame(QWidget *parent = 0);
    /*public*/ BlockBossFrame(QString frameName = tr("Simple Signal Logic"),QWidget *parent = 0);

    /*public*/ void setSignal(QString name);
    /*public*/ QString getClassName();

signals:

public slots:
private:
    void init();
    /*private*/ static /*final*/ QString SIMPLE_SIGNAL_LOGIC;// = "Simple_Signal_Logic";
    /*private*/ static /*final*/ QString LIMITED_SPEED;// = "Limited_Speed";
    /*private*/ static /*final*/ QString RESTRICTING_SPEED;// = "Restricting_Speed";
    /*private*/ static /*final*/ QString WITH_FLASHING_YELLOW;// = "With_Flashing_Yellow";
    /*private*/ static /*final*/ QString PROTECTS_SENSOR;// = "ProtectsSensor";
    /*private*/ static /*final*/ QString IS_DISTANT_SIGNAL;// = "Is_Distant_Signal";
    /*private*/ static /*final*/ QString PROTECTS_SIGNAL;// = "Protects_Signal";

    QWidget* modeSingle             ;//= new QWidget();
    QRadioButton* buttonSingle;
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<Sensor>*/* sSensorComboBox1 = new NamedBeanComboBox(
            (SensorManager*)InstanceManager::getDefault("SensorManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<Sensor>*/* sSensorComboBox2 = new NamedBeanComboBox(
            (SensorManager*)InstanceManager::getDefault("SensorManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<Sensor>*/* sSensorComboBox3 = new NamedBeanComboBox(
            (SensorManager*)InstanceManager::getDefault("SensorManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<Sensor>*/* sSensorComboBox4 = new NamedBeanComboBox(
            (SensorManager*)InstanceManager::getDefault("SensorManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<Sensor>*/* sSensorComboBox5 = new NamedBeanComboBox(
            (SensorManager*)InstanceManager::getDefault("SensorManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<SignalHead>*/* sNextSignalComboBox1 = new NamedBeanComboBox(
            (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<SignalHead>*/* sNextSignalComboBox1Alt = new NamedBeanComboBox(
            (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ JCheckBox* sLimitBox;
    /*private*/ /*final*/ JCheckBox* sRestrictingBox;
    /*private*/ /*final*/ JCheckBox* sFlashBox;
    /*private*/ /*final*/ JCheckBox* sDistantBox;

    QWidget* modeTrailMain              ;//= new QWidget();
    QRadioButton* buttonTrailMain;
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<Sensor>*/* tmSensorComboBox1 = new NamedBeanComboBox(
            (SensorManager*)InstanceManager::getDefault("SensorManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<Sensor>*/* tmSensorComboBox2 = new NamedBeanComboBox(
            (SensorManager*)InstanceManager::getDefault("SensorManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<Sensor>*/* tmSensorComboBox3 = new NamedBeanComboBox(
            (SensorManager*)InstanceManager::getDefault("SensorManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<Sensor>*/* tmSensorComboBox4 = new NamedBeanComboBox(
            (SensorManager*)InstanceManager::getDefault("SensorManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<Sensor>*/* tmSensorComboBox5 = new NamedBeanComboBox(
            (SensorManager*)InstanceManager::getDefault("SensorManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ NamedBeanComboBox/*<Turnout>*/* tmProtectTurnoutComboBox = new NamedBeanComboBox(
            InstanceManager::turnoutManagerInstance(),
            nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<SignalHead>*/* tmNextSignalComboBox1 = new NamedBeanComboBox(
            (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<SignalHead>*/* tmNextSignalComboBox1Alt = new NamedBeanComboBox(
            (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ JCheckBox* tmLimitBox;
    /*private*/ /*final*/ JCheckBox* tmRestrictingBox;
    /*private*/ /*final*/ JCheckBox* tmFlashBox;
    /*private*/ /*final*/ JCheckBox* tmDistantBox;


    QWidget* modeTrailDiv               ;//= new QWidget();
    QRadioButton* buttonTrailDiv;
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<Sensor>*/* tdSensorComboBox1 = new NamedBeanComboBox(
            (SensorManager*)InstanceManager::getDefault("SensorManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<Sensor>*/* tdSensorComboBox2 = new NamedBeanComboBox(
            (SensorManager*)InstanceManager::getDefault("SensorManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<Sensor>*/* tdSensorComboBox3 = new NamedBeanComboBox(
            (SensorManager*)InstanceManager::getDefault("SensorManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<Sensor>*/* tdSensorComboBox4 = new NamedBeanComboBox(
            (SensorManager*)InstanceManager::getDefault("SensorManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<Sensor>*/* tdSensorComboBox5 = new NamedBeanComboBox(
            (SensorManager*)InstanceManager::getDefault("SensorManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ NamedBeanComboBox/*<Turnout>*/* tdProtectTurnoutComboBox = new NamedBeanComboBox(
            InstanceManager::turnoutManagerInstance(),
            nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<SignalHead>*/* tdNextSignalComboBox1 = new NamedBeanComboBox(
            (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<SignalHead>*/* tdNextSignalComboBox1Alt = new NamedBeanComboBox(
            (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ JCheckBox* tdLimitBox;
    /*private*/ /*final*/ JCheckBox* tdRestrictingBox;
    /*private*/ /*final*/ JCheckBox* tdFlashBox;
    /*private*/ /*final*/ JCheckBox* tdDistantBox;

    QWidget* modeFacing             ;//= new QWidget();
    QRadioButton* buttonFacing;
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<Sensor>*/* fSensorComboBox1 = new NamedBeanComboBox(
            (SensorManager*)InstanceManager::getDefault("SensorManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<Sensor>*/* fSensorComboBox2 = new NamedBeanComboBox(
            (SensorManager*)InstanceManager::getDefault("SensorManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<Sensor>*/* fSensorComboBox3 = new NamedBeanComboBox(
            (SensorManager*)InstanceManager::getDefault("SensorManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<Sensor>*/* fSensorComboBox4 = new NamedBeanComboBox(
            (SensorManager*)InstanceManager::getDefault("SensorManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<Sensor>*/* fSensorComboBox5 = new NamedBeanComboBox(
            (SensorManager*)InstanceManager::getDefault("SensorManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ NamedBeanComboBox/*<Turnout>*/* fProtectTurnoutComboBox = new NamedBeanComboBox(
            InstanceManager::turnoutManagerInstance(),
            nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<SignalHead>*/* fNextSignalComboBox1 = new NamedBeanComboBox(
            (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/NamedBeanComboBox/*<SignalHead>*/*  fNextSignalComboBox1Alt = new NamedBeanComboBox(
            (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/NamedBeanComboBox/*<SignalHead>*/*  fNextSignalComboBox2 = new NamedBeanComboBox(
            (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/NamedBeanComboBox/*<SignalHead>*/*  fNextSignalComboBox2Alt = new NamedBeanComboBox(
            (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<Sensor>*/*fNextSensorComboBox1 = new NamedBeanComboBox(
            (SensorManager*)InstanceManager::getDefault("SensorManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<Sensor>*/*fNextSensorComboBox1Alt = new NamedBeanComboBox(
            (SensorManager*)InstanceManager::getDefault("SensorManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<Sensor>*/*fNextSensorComboBox2 = new NamedBeanComboBox(
            (SensorManager*)InstanceManager::getDefault("SensorManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<Sensor>*/*fNextSensorComboBox2Alt = new NamedBeanComboBox(
            (SensorManager*)InstanceManager::getDefault("SensorManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    JCheckBox* fmLimitBox;
    /*private*/ /*final*/ JCheckBox* fmRestrictingBox;
    /*private*/ /*final*/ JCheckBox* fdLimitBox;
    /*private*/ /*final*/ JCheckBox* fdRestrictingBox;
    JCheckBox* fFlashBox;
    JCheckBox* fDistantBox;

    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<Sensor>*/* approachSensor1ComboBox = new NamedBeanComboBox(
            (SensorManager*)InstanceManager::getDefault("SensorManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ /*transient*/ NamedBeanComboBox/*<SignalHead>*/* outSignalHeadComboBox = new NamedBeanComboBox(
       (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*QStatusBar*/JLabel* statusBar;
    JTextField*  commentField;
    /*private*/ /*final*/ JButton* cancel;
    /*private*/ /*final*/ JButton* _delete;
    /*private*/ /*final*/ JButton* apply;
//    static final java.util.ResourceBundle rbt = java.util.ResourceBundle.getBundle("jmri.jmrit.blockboss.BlockBossBundle");

    QString buttonSingleTooltip ;//= tr("In_direction_of_traffic");
    QString buttonTrailMainTooltip ;//= tr("Signal_head_for_main_track")
//        + tr("through_turnout_in_either_direction");
    QString buttonTrailDivTooltip ;//= tr("Signal_head_for_branching_track")
//        + tr("through_turnout_in_either_direction");
    QString buttonFacingTooltip ;//= tr("Single_signal_head_on_single")
//        + tr("track_facing_double_track");
    QString outSignalHeadTooltip ;//=  tr("Enter_a_new_signal_head_number,_or")
//        + tr("enter_an_existing_signal_head_number")
//        + tr("then_hit_return_to_load_its_information.");
    QString approachSensor1Tooltip ;//= tr("Enter_sensor_that_lights_this_signal_or")
//        + tr("leave_blank_for_always_on.");
    QString sensorFieldTooltip ;//=  tr("Sensor_active_sets_this_signal_to_Red.");
    QString turnoutFieldTooltip ;//= tr("Enter_protected_turnout_number_here.");
    QString flashBoxTooltip ;//= tr("One_aspect_faster_than_yellow_displays")
//        + tr("flashing_yellow,_rather_than_green.");
    QString limitBoxTooltip ;//= tr("Limits_the_fastest_aspect_displayed")
//        + tr("to_yellow,_rather_than_green.");Limits the fastest Appearance displayed
    /*private*/ /*final*/ QString restrictingBoxTooltip = tr("Limits_the_fastest_aspect_displayed")
            + " " + tr("to Flashing Red, rather than Green.");
    QString nextSignalFieldTooltip ;//= tr("Enter_the_low_speed_signal_head_for_this_track.")
//        + tr("For_dual_head_signals_the_fastest_aspect_is_protected.");
    QString highSignalFieldTooltip ;//= tr("Enter_the_high_speed_signal_head_for_this_track.")
//        + tr("For_dual_head_signals_the_fastest_aspect_is_protected.");
   QString distantBoxTooltip ;//= tr("Mirrors_the_protected_(following)_signal's_status")
//        + tr("unless_over_ridden_by_an_intermediate_stop_sensor.");

   /*private*/ /*final*/ /*transient*/ BlockBossLogicProvider* blockBossLogicProvider =nullptr;
   /*private*/ SignalHead* sh = nullptr;

 static Logger* log;
 QWidget* fillModeSingle();
 QWidget* fillModeTrailMain();
 QWidget* fillModeTrailDiv();
 QWidget* fillModeFacing();
 void loadSingle(BlockBossLogic* b);
 void loadTrailMain(BlockBossLogic* b) ;
 void loadTrailDiv(BlockBossLogic* b);
 void loadFacing(BlockBossLogic* b);
 /*private*/ static void setupComboBox(/*@Nonnull*/ NamedBeanComboBox/*<?>*/* inComboBox, bool inValidateMode, bool inEnable, bool inFirstBlank);
 /*private*/ void clearFields();

private slots:
   void buttonClicked(); // SLOT[]
   void activate(); // SLOT[]
   /*private*/ void applyPressed();
   /*private*/ void cancelPressed() ;
   /*private*/ void deletePressed();


//   void on_tmSensorField1_textChanged(QString);
//   void on_tmSensorField2_textChanged(QString);
//   void on_tmSensorField3_textChanged(QString);
//   void on_tmSensorField4_textChanged(QString);
//   void on_tmSensorField5_textChanged(QString);
//   void on_tmProtectTurnoutField_textChanged(QString);
//   void on_tmNextSignalField1_textChanged(QString);
//   void on_tmNextSignalField1Alt_textChanged(QString);

//   void on_tdSensorField1_textChanged(QString);
//   void on_tdSensorField2_textChanged(QString);
//   void on_tdSensorField3_textChanged(QString);
//   void on_tdSensorField4_textChanged(QString);
//   void on_tdSensorField5_textChanged(QString);
//   void on_tdProtectTurnoutField_textChanged(QString);
//   void on_tdNextSignalField1_textChanged(QString);
//   void on_tdNextSignalField1Alt_textChanged(QString);

//   void on_fSensorField1_textChanged(QString);
//   void on_fSensorField2_textChanged(QString);
//   void on_fSensorField3_textChanged(QString);
//   void on_fSensorField4_textChanged(QString);
//   void on_fSensorField5_textChanged(QString);
//   void on_fProtectTurnoutField_textChanged(QString);
//   void on_fNextSignalField1_textChanged(QString);
//   void on_fNextSignalField1Alt_textChanged(QString);
//   void on_fNextSignalField2_textChanged(QString);
//   void on_fNextSignalField2Alt_textChanged(QString);
//   void on_fNextSensorField1_textChanged(QString);
//   void on_fNextSensorField1Alt_textChanged(QString);
//   void on_fNextSensorField2_textChanged(QString);
//   void on_fNextSensorField2Alt_textChanged(QString);

};

#endif // BLOCKBOSSFRAME_H
