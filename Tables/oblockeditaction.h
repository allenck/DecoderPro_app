#ifndef OBLOCKEDITACTION_H
#define OBLOCKEDITACTION_H
#include "beaneditaction.h"
#include "actionevent.h"
#include "tableframes.h"
#include "reporter.h"
#include "namedbeancombobox.h"
#include "jtextfield.h"
#include "jcheckbox.h"
#include "jtextarea.h"
#include "namedbean.h"
#include <QRadioButton>
#include "jspinner.h"
#include "joptionpane.h"
#include "oblock.h"
#include "sensordebounceeditaction.h"

class OBlockEditAction : public BeanEditAction
{
  Q_OBJECT
 public:
  OBlockEditAction(JActionEvent *ae = nullptr);
  /*public*/ QVector<QString> curveOptions = QVector<QString>({noneText, gradualText, tightText, severeText});
  /*public*/ QString helpTarget();
  /*public*/ void setTablePanel(TableFrames::BlockPathJPanel* panel);
  /*public*/ QString getBeanType();
  /*public*/ NamedBean* getByUserName(QString name);

 private:
  /*private*/ static /*final*/ QString noneText;// = Bundle.getMessage("BlockNone");
  /*private*/ static /*final*/ QString gradualText;// = Bundle.getMessage("BlockGradual");
  /*private*/ static /*final*/ QString tightText;// = Bundle.getMessage("BlockTight");
  /*private*/ static /*final*/ QString severeText;// = Bundle.getMessage("BlockSevere");
  static /*final*/ QVector<QString> speedList;// = QVector<QString>();
  /*private*/ QString tabName = tr("OBlock");
  JTextField* userNameField = new JTextField(20);
  NamedBeanComboBox/*<Reporter>*/* reporterComboBox;
  JCheckBox* useCurrent = new JCheckBox();
  JTextArea* commentField = new JTextArea(3, 30);
  //JScrollPane commentFieldScroller = new JScrollPane(commentField);
  TableFrames::BlockPathJPanel* blockPathPanel;
  NamedBeanComboBox/*<Sensor>*/* sensorComboBox;
  NamedBeanComboBox/*<Sensor>*/* errorSensorComboBox;
  BeanItemPanel* sensor();
  BeanItemPanel* paths();
  BeanItemPanel* reporterDetails();
  JSpinner* lengthSpinner = new JSpinner(); // 2 digit decimal format field, initialized later as instance
  JComboBox* curvatureField = new JComboBox(curveOptions.toList());
  JCheckBox* permissiveField = new JCheckBox();
  JComboBox/*<String>*/* speedField;

  QRadioButton* inch = new QRadioButton(tr("Length in Inches"));
  QRadioButton* cm = new QRadioButton(tr("Length in Centimeters"));

  QString defaultBlockSpeedText;
  BeanItemPanel* physicalDetails();
  /*private*/ void updateLength();


 protected:
  /*protected*/ void initPanels();

  friend class OBTSaveItemAction1;
  friend class OBTResetItemAction1;
  friend class OBTResetItemAction1a;
  friend class OBTSaveItemAction2;
  friend class OBTResetItemAction2;
  friend class OBTSaveItemAction3;
  friend class OBTResetItemAction3;
};
class OBTSaveItemAction1 : public AbstractAction
{
  Q_OBJECT
  OBlockEditAction* act;
 public:
  OBTSaveItemAction1(OBlockEditAction* act) {this->act = act;}
  //@Override
  /*public*/ void actionPerformed(JActionEvent* e) override {
      if (act->sensorComboBox->getSelectedItem() == nullptr) {
          ((OBlock*)act->bean)->setSensor(nullptr);
      } else {
          ((Block*)act->bean)->setSensor(act->sensorComboBox->getSelectedItem()->getDisplayName());
      }
      if (act->errorSensorComboBox->getSelectedItem() == nullptr) {
          ((OBlock*)act->bean)->setErrorSensor(nullptr);
      } else {
          ((OBlock*)act->bean)->setErrorSensor(act->errorSensorComboBox->getSelectedItem()->getDisplayName());
      }
  }
};


class OBTResetItemAction1 : public AbstractAction {
  Q_OBJECT
  OBlockEditAction* act;
  SensorDebounceEditAction* debounce;
 public:
  OBTResetItemAction1(SensorDebounceEditAction* debounce, OBlockEditAction* act) {
   this->debounce = debounce;
   this->act = act;
  }
  //@Override
  /*public*/ void actionPerformed(JActionEvent* e) override {
      //From basic details
      act->sensorComboBox->setSelectedItem(((OBlock*)act->bean)->getSensor());
      act->errorSensorComboBox->setSelectedItem(((OBlock*)act->bean)->getErrorSensor());
      debounce->setBean(((OBlock*)act->bean)->getSensor());
      debounce->resetDebounceItems(/*e*/);
  }
};

class OBTResetItemAction1a : public AbstractAction
{
  Q_OBJECT
  OBlockEditAction* act;
 public:
  OBTResetItemAction1a(OBlockEditAction* act) {this->act = act;}
  //@Override
  /*public*/ void actionPerformed(JActionEvent* e) override{
      //clear the table?
  }
};

class OBTSaveItemAction2 : public AbstractAction
{
  Q_OBJECT
  OBlockEditAction* act;
 public:
  OBTSaveItemAction2(OBlockEditAction* act) {this->act = act;}
  //@Override
  /*public*/ void actionPerformed(JActionEvent* e) override{
      act->reporterComboBox->setSelectedItem(((Block*)act->bean)->getReporter());
      act->useCurrent->setChecked(((Block*)act->bean)->isReportingCurrent());
  }
};

class OBTResetItemAction2 : public AbstractAction {
  Q_OBJECT
  OBlockEditAction* act;
 public:
  OBTResetItemAction2(OBlockEditAction* act) {this->act = act;}
  //@Override
  /*public*/ void actionPerformed(JActionEvent e) {
      ((Block*)act->bean)->setReporter((Reporter*)act->reporterComboBox->getSelectedItem());
      ((Block*)act->bean)->setReportingCurrent(act->useCurrent->isChecked());
  }
};

class OBTSaveItemAction3 : public AbstractAction
{
  Q_OBJECT
  OBlockEditAction* act;
 public:
  OBTSaveItemAction3(OBlockEditAction* act) {this->act = act;}
  //@Override
  /*public*/ void actionPerformed(JActionEvent* e = 0) override {
      QString cName = (QString) act->curvatureField->getSelectedItem();
      if (cName == (act->noneText)) {
          ((Block*)act->bean)->setCurvature(Block::NONE);
      } else if (cName == (act->gradualText)) {
          ((Block*)act->bean)->setCurvature(Block::GRADUAL);
      } else if (cName == (act->tightText)) {
          ((Block*)act->bean)->setCurvature(Block::TIGHT);
      } else if (cName == (act->severeText)) {
          ((Block*)act->bean)->setCurvature(Block::SEVERE);
      }

      QString speed = (QString) act->speedField->getSelectedItem();
      try {
          ((Block*)act->bean)->setBlockSpeed(speed);
      } catch (JmriException ex) {
          JOptionPane::showMessageDialog(nullptr, ex.getMessage() + "\n" + speed);
          return;
      }
      if (!act->speedList.contains(speed) && !speed.contains("Global")) {
          act->speedList.append(speed);
      }
      float len = 0.0f;
      len = (float) act->lengthSpinner->getValue();
      if (act->inch->isChecked()) {
          ((Block*)act->bean)->setLength(len * 25.4f);
      } else {
          ((Block*)act->bean)->setLength(len * 10.0f);
      }
      ((Block*)act->bean)->setPermissiveWorking(act->permissiveField->isChecked());
  }
};

class OBTResetItemAction3 : public AbstractAction {
  Q_OBJECT
  OBlockEditAction* act;
 public:
  OBTResetItemAction3(OBlockEditAction* act) {this->act = act;}
  //@Override
  /*public*/ void actionPerformed(JActionEvent e) {
      act->lengthSpinner->setValue(((Block*)act->bean)->getLengthMm());

      if (((Block*)act->bean)->getCurvature() == Block::NONE) {
          act->curvatureField->setSelectedItem(0);
      } else if (((Block*)act->bean)->getCurvature() == Block::GRADUAL) {
          act->curvatureField->setSelectedItem(act->gradualText);
      } else if (((Block*)act->bean)->getCurvature() == Block::TIGHT) {
          act->curvatureField->setSelectedItem(act->tightText);
      } else if (((Block*)act->bean)->getCurvature() == Block::SEVERE) {
          act->curvatureField->setSelectedItem(act->severeText);
      }

      QString speed = ((Block*)act->bean)->getBlockSpeed();
      if (!act->speedList.contains(speed)) {
          act->speedList.append(speed);
      }

      act->speedField->setEditable(true);
      act->speedField->setSelectedItem(speed);
      float len = 0.0f;
      if (act->inch->isChecked()) {
          len = ((Block*)act->bean)->getLengthIn();
      } else {
          len = ((Block*)act->bean)->getLengthCm();
      }
      act->lengthSpinner->setValue(len);
      act->permissiveField->setChecked(((Block*)act->bean)->getPermissiveWorking());
  }

};
#endif // OBLOCKEDITACTION_H
