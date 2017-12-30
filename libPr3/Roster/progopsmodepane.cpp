#include "progopsmodepane.h"
#include "jtextfield.h"
#include <QRadioButton>
#include <QCheckBox>
#include <QButtonGroup>
#include "instancemanager.h"
#include "lnprogrammermanager.h"
#include "slotmanager.h"
#include "addressedprogrammermanager.h"
#include <QComboBox>
#include "rosterentry.h"
#include "flowlayout.h"
#include "programmingmode.h"
#include "programmer.h"
#include "addressedprogrammer.h"

//ProgOpsModePane::ProgOpsModePane(QWidget *parent) :
//    QWidget(parent)
//{
//}
/**
 * Provide a JPanel to configure the ops programming mode.
 * <P>
 * Note that you should call the dispose() method when you're really done, so that
 * a ProgModePane object can disconnect its listeners.
 * @author			Bob Jacobsen   Copyright (C) 2001
 * @version			$Revision: 22216 $
 */
// /*public*/ class ProgOpsModePane extends javax.swing.JPanel {

// GUI member declarations



///*public*/ ProgOpsModePane(int direction, QWidget *parent) {
//    this(direction, new QButtonGroup());
//}
void ProgOpsModePane::init()
{
 mOpsByteButton  	= new QRadioButton();
 mAddrField           = new JTextField(4);
 mLongAddrCheck        = new QCheckBox("Long address");
 log = new Logger("ProgOpsModePane");
 oldAddrText             = "";
 oldLongAddr             = false;
 buttonPool =  QList<QRadioButton*>();
 buttonMap =  QMap<ProgrammingMode*, QRadioButton*>();
 modeGroup 		    = new QButtonGroup();
}
/**
 * Get the selected programmer
 */
/*public*/ Programmer* ProgOpsModePane::getProgrammer()
{
 if ( (mLongAddrCheck->isChecked() == oldLongAddr) && mAddrField->text()==(oldAddrText) )
 {
  // hasn't changed
  return (Programmer*)programmer;
 }

 // here values have changed, try to create a new one
#if QT_VERSION < 0x050000
  AddressedProgrammerManager* pm = VPtr<AddressedProgrammerManager>::asPtr(progBox->itemData(progBox->currentIndex()));
#else
 AddressedProgrammerManager* pm = VPtr<AddressedProgrammerManager>::asPtr(progBox->itemData(progBox->currentIndex()));
#endif
 oldLongAddr = mLongAddrCheck->isChecked();
 oldAddrText = mAddrField->text();

 if (pm != NULL)
 {
  int address = 3;
  try
  {
   address = mAddrField->text().toInt();
  }
  catch (NumberFormatException e)
  {
   log->error("loco address \"{}\" not correct" + mAddrField->text());
   programmer = NULL;
  }
  bool longAddr = mLongAddrCheck->isChecked();
  log->debug("ops programmer for address " + QString::number(address)
                + ", long address " + QString::number(longAddr));
  programmer = pm->getAddressedProgrammer(longAddr, address);
  log->debug("   programmer: {}" + programmer->getAddress());

  // whole point is to get mode...
  setProgrammerFromGui(programmer);
 }
 else
 {
  log->warn("request for ops mode programmer with no ProgrammerManager configured");
  programmer = NULL;
 }
 return programmer;
}
/**
 * Are any of the modes selected?
 * @return true is any button is selected
 */
/*public*/ bool ProgOpsModePane::isSelected() {
    foreach (QRadioButton* button, buttonMap.values()) {
        if (button->isChecked()) return true;
    }
    return false;
}

/**
 * @param direction
 * @param group allows grouping of buttons across panes
 */
/*public*/ ProgOpsModePane::ProgOpsModePane(QBoxLayout::Direction direction, QButtonGroup* group, QWidget *parent)  : QWidget(parent)
{
 init();
 // save the group to use
 mModeGroup = group;

 // general GUI config
 setLayout(layout = new QBoxLayout(direction));

 // create the programmer display combo box
 QVector<AddressedProgrammerManager*>* v = new QVector<AddressedProgrammerManager*>();
 foreach (QObject* o,  *InstanceManager::getList("AddressedProgrammerManager"))
 {
  AddressedProgrammerManager* pm = (AddressedProgrammerManager*)o;
  v->append(pm);
 }
 layout->addWidget(progBox = new QComboBox); //<AddressedProgrammerManager>(v));
 foreach (AddressedProgrammerManager* m, *v)
 {
     progBox->addItem(m->getUserName(), VPtr<AddressedProgrammerManager>::asQVariant(m));
 }
 // if only one, don't show
 if (progBox->count()<2) progBox->setVisible(false);
 progBox->setCurrentIndex(progBox->findText( ((AddressedProgrammerManager*)InstanceManager::getDefault("AddressedProgrammerManager"))->getUserName())); // set default
//            progBox.addActionListener(new java.awt.event.ActionListener(){
//                public void actionPerformed(java.awt.event.ActionEvent e) {
//                    // new programmer selection
//                    programmerSelected();
//                }
//            });

 QWidget* panel = new QWidget();
 FlowLayout* panelLayout;
 panel->setLayout(panelLayout = new FlowLayout());
 panelLayout->addWidget(new QLabel("Addr:"));
 panelLayout->addWidget(mAddrField);
 layout->addWidget(panel);
 layout->addWidget(mLongAddrCheck);

//mAddrField.addActionListener(new java.awt.event.ActionListener(){
//    public void actionPerformed(java.awt.event.ActionEvent e) {
//        // new programmer selection
//        programmerSelected(); // in case has valid address now
//    }
//});
 connect(mAddrField, SIGNAL(editingFinished()), this, SLOT(programmerSelected()));
//mLongAddrCheck.addActionListener(new java.awt.event.ActionListener(){
//    public void actionPerformed(java.awt.event.ActionEvent e) {
//        // new programmer selection
//        programmerSelected(); // in case has valid address now
//    }
//});
 connect(mLongAddrCheck, SIGNAL(clicked()), this, SLOT(programmerSelected()));

 // and execute the setup for 1st time
 programmerSelected();
}
/**
 * reload the interface with the new programmers
 */
void ProgOpsModePane::programmerSelected()
{
 log->debug("programmerSelected starts with {} buttons"+ QString::number(buttonPool.size()));
 // hide buttons
 foreach (QRadioButton* button, buttonPool ) button->setVisible(false);

 // clear map
 buttonMap.clear();

 // require new programmer if possible
 oldAddrText = "";

 // configure buttons
 int index = 0;
 QList<ProgrammingMode*> modes;
 if (getProgrammer() != NULL)
 {
  modes = getProgrammer()->getSupportedModes();
 } else
 {
  //modes = ((AddressedProgrammerManager*) progBox->itemData(progBox->currentIndex()))->getDefaultModes();
  modes = (QList<ProgrammingMode*>)VPtr<AddressedProgrammerManager>::asPtr(progBox->itemData(progBox->currentIndex()))->getDefaultModes();
 }
 log->debug(tr("   has %1 modes").arg( modes.size()));
 foreach (ProgrammingMode* mode, modes)
 {
  QRadioButton* button;
  // need a new button?
  if (index >= buttonPool.size())
  {
   log->debug("   add button");
   button = new QRadioButton();
   buttonPool.append(button);
   modeGroup->addButton(button);
   //button.addActionListener(this);
   connect(button, SIGNAL(clicked()), this, SLOT(actionPerformed()));
   layout->addWidget(button); // add to GUI
  }
  // configure next button in pool
  log->debug(tr("   set for %1").arg(mode->toString()));
  button = buttonPool.at(index++);
  button->setVisible(true);
  modeGroup->addButton(button);
  button->setText(mode->toString());
  buttonMap.insert(mode, button);
 }

 setGuiFromProgrammer();
}
/**
* Listen to buttons for mode changes
*/
/*public*/ void ProgOpsModePane::actionPerformed(ActionEvent* /*e*/)
{
 // find selected button
 log->debug("Selected button: {}"/*, e.getActionCommand()*/);
// foreach (ProgrammingMode* mode, buttonMap.keys() ) {
//       if (mode.toString()==(e.getActionCommand())) {
//           log.debug("      set mode {} on {}", mode.toString(), getProgrammer());
//           if (getProgrammer() != null)
//               getProgrammer().setMode(mode);
//           return; // 1st match
//       }
//   }
 QMapIterator<ProgrammingMode*, QRadioButton*> iter(buttonMap);
 while(iter.hasNext())
 {
  iter.next();
  if(iter.value()->isChecked())
  {
      if(getProgrammer() != NULL)
          getProgrammer()->setMode(iter.key());
      return; // 1st match
  }
 }
}

void ProgOpsModePane::setProgrammerFromGui(Programmer* programmer) {
//   for (ProgrammingMode mode : buttonMap.keySet() ) {
//       if (buttonMap.get(mode).isSelected())
//           programmer.setMode(mode);
//   }
    QMapIterator<ProgrammingMode*, QRadioButton*> iter(buttonMap);
    while(iter.hasNext())
    {
     iter.next();
     if(iter.value()->isChecked())
         programmer->setMode(iter.key());
    }
}

/**
* Listen to programmer for mode changes
*/
/*public*/ void ProgOpsModePane::propertyChange(PropertyChangeEvent* e) {
  if ("Mode"==(e->getPropertyName()) && getProgrammer()==(e->getSource())) {
       // mode changed in programmer, change GUI here if needed
       if (isSelected()) {  // only change mode if we have a selected mode, in case some other selector with shared group has the selection
           setGuiFromProgrammer();
       }
   }
}

void ProgOpsModePane::setGuiFromProgrammer()
{
 if (getProgrammer() == NULL)
 {
  // no mode selected
  foreach (QRadioButton* button, buttonPool ) button->setChecked(false);
  return;
 }

 ProgrammingMode* mode = getProgrammer()->getMode();
 QRadioButton* button = buttonMap.value(mode);
 if (button == NULL)
 {
  log->error("setGuiFromProgrammer found mode \"{}\" that's not supported by the programmer" + mode->toString());
   return;
 }
 log->debug("  setting button for mode {}" + mode->toString());
 button->setChecked(true);
}

// no longer needed, disconnect if still connected
/*public*/ void ProgOpsModePane::dispose() {
}
