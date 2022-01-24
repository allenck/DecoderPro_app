#ifndef OPERATIONSSETTINGSPANEL_H
#define OPERATIONSSETTINGSPANEL_H

#include "operationspreferencespanel.h"
#include "jtextfield.h"
#include "jlabel.h"
#include "jbutton.h"
#include <QRadioButton>
#include "jcheckbox.h"
#include "jcombobox.h"
#include "jtextarea.h"

namespace Operations
{

 class OperationsSettingsPanel : public OperationsPreferencesPanel
 {
   Q_OBJECT
  public:
   OperationsSettingsPanel(QWidget *parent = nullptr);
   /*public*/ QString getTabbedPreferencesTitle() override;
   /*public*/ QString getPreferencesTooltip() override;
   /*public*/ void savePreferences() override;
   /*public*/ bool isDirty() override;
   /*public*/ QString className() override {return "jmri.jmrit.operations.OperationsSettingsPanel";}

  public slots:
   /*public*/ void buttonActionPerformed(QWidget* src) override;
   /*public*/ void checkBoxActionPerformed(QWidget* src) override;
   /*public*/ void propertyChange(PropertyChangeEvent* e);

  private:
   static Logger* log;
   // labels
   /*private*/ /*final*/ JLabel* textIconNorth = new JLabel(tr("Northbound Train Icon Color"));
   /*private*/ /*final*/ JLabel* textIconSouth = new JLabel(tr("Southbound Train Icon Color"));
   /*private*/ /*final*/ JLabel* textIconEast = new JLabel(tr("Eastbound Train Icon Color"));
   /*private*/ /*final*/ JLabel* textIconWest = new JLabel(tr("Westbound Train Icon Color"));
   /*private*/ /*final*/ JLabel* textIconLocal = new JLabel(tr("witcher Icon Color"));
   /*private*/ /*final*/ JLabel* textIconTerminate = new JLabel(tr("Terminated Train Icon Color"));

   // major buttons
   /*private*/ /*final*/ JButton* backupButton = new JButton(tr("Backup"));
   /*private*/ /*final*/ JButton* restoreButton = new JButton(tr("Restore"));
   /*private*/ /*final*/ JButton* saveButton = new JButton(tr("Save"));

   // radio buttons
   /*private*/ /*final*/ QRadioButton*  scaleZ = new QRadioButton("Z"); // NOI18N
   /*private*/ /*final*/ QRadioButton*  scaleN = new QRadioButton("N"); // NOI18N
   /*private*/ /*final*/ QRadioButton*  scaleTT = new QRadioButton("TT"); // NOI18N
   /*private*/ /*final*/ QRadioButton*  scaleHOn3 = new QRadioButton("HOn3"); // NOI18N
   /*private*/ /*final*/ QRadioButton*  scaleOO = new QRadioButton("OO"); // NOI18N
   /*private*/ /*final*/ QRadioButton*  scaleHO = new QRadioButton("HO"); // NOI18N
   /*private*/ /*final*/ QRadioButton*  scaleSn3 = new QRadioButton("Sn3"); // NOI18N
   /*private*/ /*final*/ QRadioButton*  scaleS = new QRadioButton("S"); // NOI18N
   /*private*/ /*final*/ QRadioButton*  scaleOn3 = new QRadioButton("On3"); // NOI18N
   /*private*/ /*final*/ QRadioButton*  scaleO = new QRadioButton("O"); // NOI18N
   /*private*/ /*final*/ QRadioButton*  scaleG = new QRadioButton("G"); // NOI18N

   /*private*/ /*final*/ QRadioButton*  typeDesc = new QRadioButton(tr("Descriptive"));
   /*private*/ /*final*/ QRadioButton*  typeAAR = new QRadioButton(tr("AAR"));

   /*private*/ /*final*/ QRadioButton*  feetUnit = new QRadioButton(tr("Feet"));
   /*private*/ /*final*/ QRadioButton*  meterUnit = new QRadioButton(tr("Meter"));

   // check boxes
   /*final*/ JCheckBox* eastCheckBox = new JCheckBox(tr("East/West"));
   /*final*/ JCheckBox* northCheckBox = new JCheckBox(tr("North/South"));
   /*private*/ /*final*/ JCheckBox* mainMenuCheckBox = new JCheckBox(tr("Add Operations Menu to Main Menu"));
   /*private*/ /*final*/ JCheckBox* closeOnSaveCheckBox = new JCheckBox(tr("Close Windows on Save"));
   /*private*/ /*final*/ JCheckBox* autoSaveCheckBox = new JCheckBox(tr("Auto Save"));
   /*private*/ /*final*/ JCheckBox* autoBackupCheckBox = new JCheckBox(tr("Auto Backup"));
   /*private*/ /*final*/ JCheckBox* iconCheckBox = new JCheckBox(tr("Enable Icon SetX&Y"));
   /*private*/ /*final*/ JCheckBox* appendCheckBox = new JCheckBox(tr("Append Loco Number"));

   // text field
   JTextField* panelTextField = new JTextField(30);
   JTextField* railroadNameTextField = new JTextField(35);
   JTextField* maxLengthTextField = new JTextField(5);
   JTextField* maxEngineSizeTextField = new JTextField(3);
   JTextField* hptTextField = new JTextField(3);
   JTextField* switchTimeTextField = new JTextField(3);
   JTextField* travelTimeTextField = new JTextField(3);
   JTextField* yearTextField = new JTextField(4);

   // combo boxes
   /*private*/ /*final*/ JComboBox* northComboBox = new JComboBox();
   /*private*/ /*final*/ JComboBox* southComboBox = new JComboBox();
   /*private*/ /*final*/ JComboBox* eastComboBox = new JComboBox();
   /*private*/ /*final*/ JComboBox* westComboBox = new JComboBox();
   /*private*/ /*final*/ JComboBox* localComboBox = new JComboBox();
   /*private*/ /*final*/ JComboBox* terminateComboBox = new JComboBox();

   // text area
   /*private*/ /*final*/ JTextArea* commentTextArea = new JTextArea(2, 80);

   /*private*/ void save();
   /*private*/ void checkRoutes();
   /*private*/ int getSelectedScale();
   /*private*/ void setCarTypes() ;
   /*private*/ void setDirectionCheckBox(int direction);
   /*private*/ void setLengthUnit();
   /*private*/ void loadIconComboBox(JComboBox* comboBox);
   /*private*/ void setScale();

 };
}
#endif // OPERATIONSSETTINGSPANEL_H
