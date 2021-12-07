#ifndef SIMPLELIGHTCTRLFRAME_H
#define SIMPLELIGHTCTRLFRAME_H
#include "jmrijframe.h"
#include "propertychangelistener.h"
#include "namedbeancombobox.h"
#include "jlabel.h"

class Logger;
class JActionEvent;
class QCheckBox;
class QPushButton;
class DecimalFormat;
class Light;
class JTextField;
class SimpleLightCtrlFrame : public JmriJFrame, public PropertyChangeListener
{
 Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
public:
 explicit SimpleLightCtrlFrame(QWidget *parent = 0);
 /*public*/ QString getClassName() override;
  QObject* self() override {return (QObject*)this;}

signals:

public slots:
 /*public*/ void offButtonActionPerformed(JActionEvent* e = 0);
 /*public*/ void onButtonActionPerformed(JActionEvent* e = 0);
 /*public*/ void intensityButtonActionPerformed(JActionEvent* e = 0);
 /*public*/ void applyButtonActionPerformed(JActionEvent* e = 0);
 /*public*/ void statusButtonActionPerformed(JActionEvent* e = 0);
 /*public*/ void propertyChange(PropertyChangeEvent* e) override;

private:
 DecimalFormat* threeDigits; // newDecimalFormat("000");
 DecimalFormat* oneDigits; // newDecimalFormat("0");
 DecimalFormat* oneDotTwoDigits; // newDecimalFormat("0.00");

 Light* light;// = null;
 QString newState;// = "";

 // GUI member declarations
 QLabel* textAdrLabel; // newjavax.swing.JLabel();
 JTextField* adrTextField; // newjavax.swing.JTextField(5);
 QPushButton* statusButton; // newjavax.swing.JButton();

 QPushButton* onButton; // newjavax.swing.JButton();
 QPushButton* offButton; // newjavax.swing.JButton();

 QLabel* textStateLabel; // newjavax.swing.JLabel();
 QLabel* nowStateTextField; // newjavax.swing.JLabel();
 JLabel* nowControllersTextField = new JLabel();
 QLabel* textIsEnabledLabel; // newjavax.swing.JLabel();
 QCheckBox* statusIsEnabledCheckBox; // newjavax.swing.JCheckBox();
 QLabel* textIsVariableLabel; // newjavax.swing.JLabel();
 QCheckBox* statusIsVariableCheckBox; // newjavax.swing.JCheckBox();
 QLabel* textIsTransitionLabel; // newjavax.swing.JLabel();
 QCheckBox* statusIsTransitionCheckBox; // newjavax.swing.JCheckBox();

 QLabel* intensityTextLabel1; // newjavax.swing.JLabel();
 QLabel* nowIntensityLabel; // newjavax.swing.JLabel();
 JTextField* intensityTextField; // newjavax.swing.JTextField(4);
 QLabel* intensityTextLabel2; // newjavax.swing.JLabel();
 QPushButton* intensityButton; // newjavax.swing.JButton();

 QLabel* intensityMinTextLabel; // newjavax.swing.JLabel();
 QLabel* nowIntensityMinLabel; // newjavax.swing.JLabel();
 JTextField* intensityMinTextField; // newjavax.swing.JTextField(4);
 QLabel* intensityMaxTextLabel; // newjavax.swing.JLabel();
 QLabel* nowIntensityMaxLabel; // newjavax.swing.JLabel();
 JTextField* intensityMaxTextField; // newjavax.swing.JTextField(4);
 QLabel* transitionTimeTextLabel; // newjavax.swing.JLabel();
 QLabel* nowTransitionTimeLabel; // newjavax.swing.JLabel();
 JTextField* transitionTimeTextField; // newjavax.swing.JTextField(4);

 QPushButton* applyButton; // newjavax.swing.JButton();
 /*private*/ /*final*/ NamedBeanComboBox/*<Light>*/* to1;
 /*private*/ PropertyChangeListener* _parentLightListener = nullptr;
 /*private*/ void setControlFrameActive(bool showLight);

 Logger* log;
 /*private*/ void resetLightToCombo();
 /*private*/ void updateLightStatusFields(bool flag);
 friend class SLCFPropertyChangeListener;
};

class SLCFPropertyChangeListener : public QObject, public PropertyChangeListener
{
  Q_OBJECT
  SimpleLightCtrlFrame* slcf;
 public:
  SLCFPropertyChangeListener(SimpleLightCtrlFrame* slcf) {this->slcf = slcf;}
  QObject* self() override {return (QObject*)this;}
 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e)override {
      slcf->log->debug(tr("recv propChange: %1 %2 -> %3").arg(e->getPropertyName(), e->getOldValue().toString(), e->getNewValue().toString()));
      slcf->updateLightStatusFields(false);
  }
};

#endif // SIMPLELIGHTCTRLFRAME_H
