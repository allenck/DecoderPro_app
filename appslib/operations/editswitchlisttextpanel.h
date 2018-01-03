#ifndef EDITSWITCHLISTTEXTPANEL_H
#define EDITSWITCHLISTTEXTPANEL_H

#include "operationspreferencespanel.h"
class JTextField;
namespace Operations
{
 class EditSwitchListTextPanel : public OperationsPreferencesPanel
 {
  Q_OBJECT
 public:
  EditSwitchListTextPanel(QWidget* parent = 0);
  /*public*/ QString getTabbedPreferencesTitle();
  /*public*/ QString getPreferencesTooltip();
  /*public*/ void savePreferences();
  /*public*/ bool isDirty();
 public slots:
  /*public*/ void buttonActionPerformed(QWidget* ae);

 private:
  // major buttons
  QPushButton* saveButton;//= new JButton(Bundle.getMessage("Save"));
  QPushButton* resetButton;//= new JButton(rb.getString("Reset"));

  // text fields
  JTextField* switchListForTextField;//= new JTextField(60);
  JTextField* scheduledWorkTextField;//= new JTextField(60);

  JTextField* departsAtTextField;//= new JTextField(60);
  JTextField* departsAtExpectedArrivalTextField;//= new JTextField(60);
  JTextField* departedExpectedTextField;//= new JTextField(60);

  JTextField* visitNumberTextField;//= new JTextField(60);
  JTextField* visitNumberDepartedTextField;//= new JTextField(60);
  JTextField* visitNumberTerminatesTextField;//= new JTextField(60);
  JTextField* visitNumberTerminatesDepartedTextField;//= new JTextField(60);
  JTextField* visitNumberDoneTextField;//= new JTextField(60);

  JTextField* trainDirectionChangeTextField;//= new JTextField(60);
  JTextField* noCarPickUpsTextField;//= new JTextField(60);
  JTextField* noCarDropsTextField;//= new JTextField(60);
  JTextField* trainDoneTextField;//= new JTextField(60);
  JTextField* trainDepartsCarsTextField;//= new JTextField(60);
  JTextField* trainDepartsLoadsTextField;//= new JTextField(60);

  JTextField* switchListByTrackTextField;//= new JTextField(60);
  JTextField* holdCarTextField;//= new JTextField(60);

 };
}
#endif // EDITSWITCHLISTTEXTPANEL_H
