#ifndef BLOCKBOSSFRAME_H
#define BLOCKBOSSFRAME_H

#include "jmrijframe.h"
#include <QRadioButton>
#include <QCheckBox>
#include "logger.h"

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
    QWidget* modeSingle             ;//= new QWidget();
    QRadioButton* buttonSingle;
    JTextField*  sSensorField1      ;//= new JTextField(6);
    JTextField*  sSensorField2      ;//= new JTextField(6);
    JTextField*  sSensorField3      ;//= new JTextField(6);
    JTextField*  sSensorField4      ;//= new JTextField(6);
    JTextField*  sSensorField5      ;//= new JTextField(6);
    JTextField*  sNextSignalField1  ;//= new JTextField(6);
    JTextField*  sNextSignalField1Alt ;//= new JTextField(6);
    QCheckBox* sLimitBox;
    QCheckBox* sFlashBox;
    QCheckBox* sDistantBox;

    QWidget* modeTrailMain              ;//= new QWidget();
    QRadioButton* buttonTrailMain;
    JTextField*  tmSensorField1         ;//= new JTextField(6);
    JTextField*  tmSensorField2         ;//= new JTextField(6);
    JTextField*  tmSensorField3         ;//= new JTextField(6);
    JTextField*  tmSensorField4         ;//= new JTextField(6);
    JTextField*  tmSensorField5         ;//= new JTextField(6);
    JTextField*  tmProtectTurnoutField  ;//= new JTextField(6);
    JTextField*  tmNextSignalField1     ;//= new JTextField(6);
    JTextField*  tmNextSignalField1Alt  ;//= new JTextField(6);
    QCheckBox* tmLimitBox;
    QCheckBox* tmFlashBox;
    QCheckBox* tmDistantBox;

    QWidget* modeTrailDiv               ;//= new QWidget();
    QRadioButton* buttonTrailDiv;
    JTextField*  tdSensorField1         ;//= new JTextField(6);
    JTextField*  tdSensorField2         ;//= new JTextField(6);
    JTextField*  tdSensorField3         ;//= new JTextField(6);
    JTextField*  tdSensorField4         ;//= new JTextField(6);
    JTextField*  tdSensorField5         ;//= new JTextField(6);
    JTextField*  tdProtectTurnoutField  ;//= new JTextField(6);
    JTextField*  tdNextSignalField1     ;//= new JTextField(6);
    JTextField*  tdNextSignalField1Alt  ;//= new JTextField(6);
    QCheckBox* tdLimitBox;
    QCheckBox* tdFlashBox;
    QCheckBox* tdDistantBox;

    QWidget*modeFacing             ;//= new QWidget();
    QRadioButton* buttonFacing;
    JTextField*  fSensorField1      ;//= new JTextField(6);
    JTextField*  fSensorField2      ;//= new JTextField(6);
    JTextField*  fSensorField3      ;//= new JTextField(6);
    JTextField*  fSensorField4      ;//= new JTextField(6);
    JTextField*  fSensorField5      ;//= new JTextField(6);
    JTextField*  fProtectTurnoutField ;//= new JTextField(6);
    JTextField*  fNextSignalField1  ;//= new JTextField(6);
    JTextField*  fNextSignalField1Alt ;//= new JTextField(6);
    JTextField*  fNextSignalField2  ;//= new JTextField(6);
    JTextField*  fNextSignalField2Alt;// = ;//new JTextField(6);
    JTextField*  fNextSensorField1  ;//= new JTextField(6);
    JTextField*  fNextSensorField1Alt ;//= new JTextField(6);
    JTextField*  fNextSensorField2  ;//= new JTextField(6);
    JTextField*  fNextSensorField2Alt ;//= new JTextField(6);
    QCheckBox* fmLimitBox;
    QCheckBox* fdLimitBox;
    QCheckBox* fFlashBox;
    QCheckBox* fDistantBox;

    JTextField*  outSignalField;
    JTextField*  approachSensorField1;

    JTextField*  commentField;

//    static final java.util.ResourceBundle rbt = java.util.ResourceBundle.getBundle("jmri.jmrit.blockboss.BlockBossBundle");

    QString buttonSingleTooltip ;//= tr("In_direction_of_traffic");
    QString buttonTrailMainTooltip ;//= tr("Signal_head_for_main_track")
//        + tr("through_turnout_in_either_direction");
    QString buttonTrailDivTooltip ;//= tr("Signal_head_for_branching_track")
//        + tr("through_turnout_in_either_direction");
    QString buttonFacingTooltip ;//= tr("Single_signal_head_on_single")
//        + tr("track_facing_double_track");
    QString outSignalFieldTooltip ;//=  tr("Enter_a_new_signal_head_number,_or")
//        + tr("enter_an_existing_signal_head_number")
//        + tr("then_hit_return_to_load_its_information.");
    QString approachSensor1Tooltip ;//= tr("Enter_sensor_that_lights_this_signal_or")
//        + tr("leave_blank_for_always_on.");
    QString sensorFieldTooltip ;//=  tr("Sensor_active_sets_this_signal_to_Red.");
    QString turnoutFieldTooltip ;//= tr("Enter_protected_turnout_number_here.");
    QString flashBoxTooltip ;//= tr("One_aspect_faster_than_yellow_displays")
//        + tr("flashing_yellow,_rather_than_green.");
    QString limitBoxTooltip ;//= tr("Limits_the_fastest_aspect_displayed")
//        + tr("to_yellow,_rather_than_green.");
    QString nextSignalFieldTooltip ;//= tr("Enter_the_low_speed_signal_head_for_this_track.")
//        + tr("For_dual_head_signals_the_fastest_aspect_is_protected.");
    QString highSignalFieldTooltip ;//= tr("Enter_the_high_speed_signal_head_for_this_track.")
//        + tr("For_dual_head_signals_the_fastest_aspect_is_protected.");
   QString distantBoxTooltip ;//= tr("Mirrors_the_protected_(following)_signal's_status")
//        + tr("unless_over_ridden_by_an_intermediate_stop_sensor.");

 Logger* log;
 QWidget* fillModeSingle();
 QWidget* fillModeTrailMain();
 QWidget* fillModeTrailDiv();
 QWidget* fillModeFacing();
 void loadSingle(BlockBossLogic* b);
 void loadTrailMain(BlockBossLogic* b) ;
 void loadTrailDiv(BlockBossLogic* b);
 void loadFacing(BlockBossLogic* b);

private slots:
   void buttonClicked(); // SLOT[]
   void activate(); // SLOT[]
   void okPressed();
   void on_sSensorField1_textChanged(QString);
   void on_sSensorField2_textChanged(QString);
   void on_sSensorField3_textChanged(QString);
   void on_sSensorField4_textChanged(QString);
   void on_sSensorField5_textChanged(QString);
   void on_sNextSignalField1_textChanged(QString);
   void on_sNextSignalField1Alt_textChanged(QString);

   void on_tmSensorField1_textChanged(QString);
   void on_tmSensorField2_textChanged(QString);
   void on_tmSensorField3_textChanged(QString);
   void on_tmSensorField4_textChanged(QString);
   void on_tmSensorField5_textChanged(QString);
   void on_tmProtectTurnoutField_textChanged(QString);
   void on_tmNextSignalField1_textChanged(QString);
   void on_tmNextSignalField1Alt_textChanged(QString);

   void on_tdSensorField1_textChanged(QString);
   void on_tdSensorField2_textChanged(QString);
   void on_tdSensorField3_textChanged(QString);
   void on_tdSensorField4_textChanged(QString);
   void on_tdSensorField5_textChanged(QString);
   void on_tdProtectTurnoutField_textChanged(QString);
   void on_tdNextSignalField1_textChanged(QString);
   void on_tdNextSignalField1Alt_textChanged(QString);

   void on_fSensorField1_textChanged(QString);
   void on_fSensorField2_textChanged(QString);
   void on_fSensorField3_textChanged(QString);
   void on_fSensorField4_textChanged(QString);
   void on_fSensorField5_textChanged(QString);
   void on_fProtectTurnoutField_textChanged(QString);
   void on_fNextSignalField1_textChanged(QString);
   void on_fNextSignalField1Alt_textChanged(QString);
   void on_fNextSignalField2_textChanged(QString);
   void on_fNextSignalField2Alt_textChanged(QString);
   void on_fNextSensorField1_textChanged(QString);
   void on_fNextSensorField1Alt_textChanged(QString);
   void on_fNextSensorField2_textChanged(QString);
   void on_fNextSensorField2Alt_textChanged(QString);

};

#endif // BLOCKBOSSFRAME_H
