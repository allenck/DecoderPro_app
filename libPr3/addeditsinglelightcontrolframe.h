#ifndef ADDEDITSINGLELIGHTCONTROLFRAME_H
#define ADDEDITSINGLELIGHTCONTROLFRAME_H

#include <jmrijframe.h>
#include "lightcontrol.h"
#include "lightcontrolpane.h"
#include "namedbeancombobox.h"
#include "jlabel.h"
#include "jbutton.h"
#include "sensor.h"
#include "instancemanager.h"
#include "sensormanager.h"
#include "spinnernumbermodel.h"
#include "jspinner.h"
#include "windowadapter.h"

class LightControlPane;
class ComboBoxToolTipRenderer;
class AddEditSingleLightControlFrame : public JmriJFrame
{
  Q_OBJECT
 public:
  /*public*/ AddEditSingleLightControlFrame(/*@Nonnull*/ LightControlPane* pane, LightControl* ctrl);
  /*public*/ QString getClassName() override {return "jmri.jmrit.beantable.light.AddEditSingleLightControlFrame";}

 private:
  static Logger* log;
  /*final*/  LightControl* lc;
  /*private*/ JComboBox* typeBox;

  /*private*/ /*final*/  JLabel* status1 = new JLabel();

  /*private*/ /*final*/  NamedBeanComboBox/*<Sensor>*/* sensor1Box = new NamedBeanComboBox( // Sensor (1 or only)
          InstanceManager::sensorManagerInstance(), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
  /*private*/ /*final*/  NamedBeanComboBox/*<Sensor>*/* sensor2Box = new NamedBeanComboBox( // Sensor 2
          InstanceManager::sensorManagerInstance(), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);

  /*private*/ /*final*/  JLabel* f1Label = new JLabel(tr("Controller Sensor%1").arg(tr("%1:").arg(""))); // for 1 sensor
  /*private*/ /*final*/  JLabel* f1aLabel = new JLabel(tr("Controller Sensor%1").arg(tr("%1:").arg(" 2"))); // for 2nd sensor

  /*private*/ /*final*/  SpinnerNumberModel* fastHourSpinnerModel1 = new SpinnerNumberModel(0, 0, 23, 1); // 0 - 23 h
  /*private*/ /*final*/  JSpinner* fastHourSpinner1 = new JSpinner(fastHourSpinnerModel1); // Fast Clock1 hours
  /*private*/ /*final*/  SpinnerNumberModel* fastMinuteSpinnerModel1 = new SpinnerNumberModel(0, 0, 59, 1); // 0 - 59 min
  /*private*/ /*final*/  JSpinner* fastMinuteSpinner1 = new JSpinner(fastMinuteSpinnerModel1); // Fast Clock1 minutes
  /*private*/ /*final*/  JLabel* clockSep1 = new JLabel(" : ");
  /*private*/ /*final*/  JLabel* clockSep2 = new JLabel(" : ");

  /*private*/ /*final*/  SpinnerNumberModel* fastHourSpinnerModel2 = new SpinnerNumberModel(0, 0, 23, 1); // 0 - 23 h
  /*private*/ /*final*/  JSpinner* fastHourSpinner2 = new JSpinner(fastHourSpinnerModel2); // Fast Clock2 hours
  /*private*/ /*final*/  SpinnerNumberModel* fastMinuteSpinnerModel2 = new SpinnerNumberModel(0, 0, 59, 1); // 0 - 59 min
  /*private*/ /*final*/  JSpinner* fastMinuteSpinner2 = new JSpinner(fastMinuteSpinnerModel2); // Fast Clock2 minutes

  /*private*/ /*final*/  NamedBeanComboBox/*<Turnout>*/* turnoutBox = new NamedBeanComboBox( // Turnout
          InstanceManager::turnoutManagerInstance(), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
  /*private*/ /*final*/  NamedBeanComboBox/*<Sensor>*/* sensorOnBox = new NamedBeanComboBox( // Timed ON
          InstanceManager::sensorManagerInstance(), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);

  /*private*/ JComboBox* stateBox;
  /*private*/ ComboBoxToolTipRenderer* stateBoxToolTipRenderer;

  /*private*/ /*final*/  SpinnerNumberModel* timedOnSpinnerModel = new SpinnerNumberModel(0, 0, 1000000, 1); // 0 - 1,000,000 msec
  /*private*/ /*final*/  JSpinner* timedOnSpinner = new JSpinner(timedOnSpinnerModel); // Timed ON

  /*private*/ JPanel* sensorTwoPanel;

  /*private*/ /*final*/  JLabel* f2Label = new JLabel(tr("Sense for ON:"));

  /*private*/ /*final*/  int sensorActiveIndex = 0;
  /*private*/ /*final*/  int sensorInactiveIndex = 1;
  /*private*/ /*final*/  int turnoutClosedIndex = 0;
  /*private*/ /*final*/  int turnoutThrownIndex = 1;

  /*private*/ JButton* createControl;
  /*private*/ JButton* updateControl;
  /*private*/ JButton* cancelControl;

  /*final*/  LightControlPane* lcp;
  /*private*/ void init();
  /*private*/ JPanel* getButtonPanel();
  /*private*/ void setUpControlType(int ctype);
  /*private*/ void commitEdits();
  /*private*/ void notifyUser(QString message, QColor color);
  /*private*/ bool setControlInformation(LightControl* g, QList<LightControl*> currentList);
  /*private*/ void setFrameToControl(LightControl* lc);

 protected slots:
  /*protected*/ void updateControlPressed(JActionEvent* e);
  /*protected*/ void cancelControlPressed(JActionEvent* e);
  /*protected*/ void createControlPressed(JActionEvent* e);

 protected:

  friend class AESLCF_windowListener;
};

class AESLCF_windowListener : public WindowAdapter
{
  Q_OBJECT
  AddEditSingleLightControlFrame* frame;
 public:
  AESLCF_windowListener(AddEditSingleLightControlFrame* frame) {this->frame = frame;}
  void windowClosed(QCloseEvent*) override{
   frame->lcp = nullptr;
  }
  //@Override
  /*public*/ void windowClosing(QEvent* /*e*/) override{
      frame->cancelControlPressed(nullptr);
  }
};

#endif // ADDEDITSINGLELIGHTCONTROLFRAME_H
