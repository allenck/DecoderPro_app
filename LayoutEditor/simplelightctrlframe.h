#ifndef SIMPLELIGHTCTRLFRAME_H
#define SIMPLELIGHTCTRLFRAME_H
#include "jmrijframe.h"

class Logger;
class JActionEvent;
class QCheckBox;
class QPushButton;
class DecimalFormat;
class Light;
class JTextField;
class QLabel;
class SimpleLightCtrlFrame : public JmriJFrame
{
 Q_OBJECT
public:
 explicit SimpleLightCtrlFrame(QWidget *parent = 0);
 /*public*/ QString getClassName();

signals:

public slots:
 /*public*/ void offButtonActionPerformed(JActionEvent* e = 0);
 /*public*/ void onButtonActionPerformed(JActionEvent* e = 0);
 /*public*/ void intensityButtonActionPerformed(JActionEvent* e = 0);
 /*public*/ void applyButtonActionPerformed(JActionEvent* e = 0);
 /*public*/ void statusButtonActionPerformed(JActionEvent* e = 0);
 /*public*/ void propertyChange(PropertyChangeEvent* e);

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
 Logger* log;
 /*private*/ void updateLightStatusFields(bool flag);
};

#endif // SIMPLELIGHTCTRLFRAME_H
