#ifndef PRINTMOREOPTIONSPANEL_H
#define PRINTMOREOPTIONSPANEL_H
#include "operationspanel.h"

class JTextField;
namespace Operations
{
 class PrintMoreOptionPanel : public OperationsPanel
 {
 public:
  PrintMoreOptionPanel(QWidget* parent = 0);
 public slots:
  /*public*/ void buttonActionPerformed(QWidget* ae);
  /*public*/ QString getTabbedPreferencesTitle();
  /*public*/ QString getPreferencesTooltip();
  /*public*/ void savePreferences();
  /*public*/ bool isDirty();

 private:
  // labels
  // major buttons
  QPushButton* saveButton;//= new JButton(Bundle.getMessage("Save"));

  // radio buttons
  // check boxes
  // text field
  JTextField* tab1TextField;//= new JTextField(2);
  JTextField* tab2TextField;//= new JTextField(2);
  JTextField* tab3TextField;//= new JTextField(2);

  // text area
  // combo boxes

 };
}
#endif // PRINTMOREOPTIONSPANEL_H
