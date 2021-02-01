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
#include "accessoryopsmodeprogrammerfacade.h"

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
 //SpinnerNumberModel model = new SpinnerNumberModel(0, 0, 10239, 1); // 10239 is highest DCC Long Address documented by NMRA as per 2017
 mAddrField = new QSpinBox(/*model*/);
 mAddrField->setMinimum(0);
 mAddrField->setMaximum(10239);
 mAddrField->setValue(0);
 mAddrField->setSingleStep(1);
 lowAddrLimit = 0;
 highAddrLimit = 10239;
 oldAddrValue = 3; // Default start value
 shortAddrButton = new QRadioButton(tr("Short Address"));
 longAddrButton = new QRadioButton(tr("LongAddress"));
 offsetAddrCheckBox = new QCheckBox(tr("Offset Address"));
 addressLabel = new QLabel(tr("Address:"));
 oldLongAddr = false;
 opsAccyMode = false;
 oldOpsAccyMode = false;
 opsSigMode = false;
 oldOpsSigMode = false;
 oldoffsetAddrCheckBox = false;
 programmer = NULL;
 facadeProgrammer = NULL;

 log = new Logger("ProgOpsModePane");
 oldAddrText             = "";
 oldLongAddr             = false;
 buttonPool =  QList<QRadioButton*>();
 buttonMap =  QMap<QString, QRadioButton*>();
 modeGroup 		    = new QButtonGroup();
}
/**
 * Get the selected programmer
 */
/*public*/ Programmer* ProgOpsModePane::getProgrammer()
{
 log->debug(tr("getProgrammer mLongAddrCheck.isSelected()=%1, oldLongAddr=%2, mAddrField.getValue()=%3, oldAddrValue=%4, opsAccyMode=%5, oldOpsAccyMode=%6, opsSigMode=%7, oldOpsSigMode=%8, oldoffsetAddrCheckBox=%9)").arg(longAddrButton->isChecked()).arg(oldLongAddr).arg(mAddrField->value()).arg(oldAddrValue).arg(opsAccyMode).arg(oldOpsAccyMode).arg(opsSigMode).arg(oldOpsSigMode).arg(oldoffsetAddrCheckBox));

 if (longAddrButton->isChecked() == oldLongAddr
                 && mAddrField->value() == (oldAddrValue)
                 && offsetAddrCheckBox->isChecked() == oldoffsetAddrCheckBox
                 && opsAccyMode == oldOpsAccyMode
                 && opsSigMode == oldOpsSigMode)
 {
  log->debug("getProgrammer hasn't changed");
  // hasn't changed
  if (opsAccyMode || opsSigMode) {
      return facadeProgrammer;
  } else {
      return programmer;
  }
}

// here values have changed, try to create a new one
 AddressedProgrammerManager* pm = VPtr<AddressedProgrammerManager>::asPtr(progBox->currentData());
 oldLongAddr = longAddrButton->isChecked();
 oldAddrValue = mAddrField->value();
 oldOpsAccyMode = opsAccyMode;
 oldOpsSigMode = opsSigMode;
 oldoffsetAddrCheckBox = offsetAddrCheckBox->isChecked();
 setAddrParams();

 if (pm != NULL) {
     int address = 3;
     try {
         address = mAddrField->value();
     } catch (NumberFormatException e) {
         log->error(tr("loco address \"%1\" not correct").arg(mAddrField->value()));
         programmer = NULL;
     }
     bool longAddr = longAddrButton->isChecked();
     log->debug("ops programmer for address " + QString::number(address)
             + ", long address " + longAddr);
     programmer = pm->getAddressedProgrammer(longAddr, address);
     log->debug(tr("   programmer: %1").arg(programmer->self()->metaObject()->className()));

     // whole point is to get mode...
     setProgrammerFromGui(programmer);
 } else {
     log->warn("request for ops mode programmer with no ProgrammerManager configured");
     programmer = NULL;
 }
 if (opsAccyMode) {
     log->debug("   getting AccessoryOpsModeProgrammerFacade");
     facadeProgrammer = new AccessoryOpsModeProgrammerFacade((Programmer*)programmer,
             QString(longAddrButton->isChecked() ? "accessory" : "decoder"), 200, programmer);
     return facadeProgrammer;
 } else if (opsSigMode) {
     QString addrType = offsetAddrCheckBox->isChecked() ? "signal" : "altsignal";
     log->debug(tr("   getting AccessoryOpsModeProgrammerFacade %1").arg(addrType));
     facadeProgrammer = new AccessoryOpsModeProgrammerFacade(programmer, addrType, 200, programmer);
     return facadeProgrammer;
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
 * Constructor for the Programming settings pane.
 *
 * @param direction controls layout, either BoxLayout.X_AXIS or
 *                  BoxLayout.Y_AXIS
 * @param group     A set of JButtons to display programming modes
 */
/*public*/ ProgOpsModePane::ProgOpsModePane(QBoxLayout::Direction direction, QButtonGroup* group, QWidget* parent) : ProgModeSelector(parent)
{
    modeGroup = group;
    addrGroup->addButton(shortAddrButton);
    addrGroup->addButton(longAddrButton);

    // general GUI config
    //setLayout(new BoxLayout(this, direction));
    thisLayout = new QBoxLayout(direction,this);

    // create the programmer display combo box
    QVector<AddressedProgrammerManager*> v = QVector<AddressedProgrammerManager*>();
    for (QObject* pm : *InstanceManager::getList("AddressedProgrammerManager")) {
        v.append((DefaultProgrammerManager*)pm);
    }
    thisLayout->addWidget(progBox = new QComboBox(/*v*/));
    foreach (AddressedProgrammerManager* m, v)
    {
     progBox->addItem(m->toString(), VPtr<AddressedProgrammerManager>::asQVariant(m));
    }
    // if only one, don't show
    if (progBox->count() < 2)
    {
        progBox->setVisible(false);
    }
    progBox->setCurrentIndex(progBox->findText(((DefaultProgrammerManager*)InstanceManager::getDefault("AddressedProgrammerManager"))->toString())); // set default
//    progBox.addActionListener(new java.awt.event.ActionListener() {
//        @Override
//        public void actionPerformed(java.awt.event.ActionEvent e) {
//            // new programmer selection
//            programmerSelected();
//        }
//    });
    connect(progBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(programmerSelected()));

    thisLayout->addWidget(new QLabel(tr("Program On Main")));
    thisLayout->addWidget(new QLabel(" "));
    thisLayout->addWidget(shortAddrButton);
    thisLayout->addWidget(longAddrButton);
    thisLayout->addWidget(offsetAddrCheckBox);
    offsetAddrCheckBox->setToolTip(tr("When checked, uses an alternative DCC addressing scheme."));
    QWidget* panel = new QWidget();
    //panel.setLayout(new java.awt.FlowLayout());
    FlowLayout* panelLayout = new FlowLayout(panel);
    panelLayout->addWidget(addressLabel);
    panelLayout->addWidget(mAddrField);
    mAddrField->setToolTip(tr("Enter the decoder numeric address"));
    thisLayout->addWidget(panel);
    thisLayout->addWidget(new QLabel(tr("Mode:")));

//        mAddrField.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            public void actionPerformed(java.awt.event.ActionEvent e) {
    // new programmer selection
//                programmerSelected(); // in case it has valid address now
//            }
//        });
//    shortAddrButton.addActionListener(new java.awt.event.ActionListener() {
//        @Override
//        public void actionPerformed(java.awt.event.ActionEvent e) {
//            // new programmer selection
//            programmerSelected(); // in case it has valid address now
//        }
//    });
    connect(shortAddrButton, SIGNAL(clicked(bool)), this, SLOT(programmerSelected()));

//    longAddrButton.addActionListener(new java.awt.event.ActionListener() {
//        @Override
//        public void actionPerformed(java.awt.event.ActionEvent e) {
//            // new programmer selection
//            programmerSelected(); // in case it has valid address now
//        }
//    });
    connect(longAddrButton, SIGNAL(clicked(bool)), this, SLOT(programmerSelected()));

//    offsetAddrCheckBox.addActionListener(new java.awt.event.ActionListener() {
//        @Override
//        public void actionPerformed(java.awt.event.ActionEvent e) {
//            // new programmer selection
//            programmerSelected(); // in case it has valid address now
//        }
//    });
    connect(offsetAddrCheckBox, SIGNAL(clicked(bool)), this, SLOT(programmerSelected()));

    shortAddrButton->setChecked(true);
    offsetAddrCheckBox->setChecked(false);
    offsetAddrCheckBox->setVisible(false);

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
 oldAddrValue = -1;

 // configure buttons
 int index = 0;
 QList<QString> modes = QList<QString>();
 if (getProgrammer() != NULL) {
     //modes.addAll(programmer->getSupportedModes());
  foreach(QString mode, programmer->getSupportedModes())
   modes.append(mode);
 } else {
     //modes.addAll(((AddressedProgrammerManager) progBox.getSelectedItem()).getDefaultModes());
  foreach(QString mode, (VPtr<AddressedProgrammerManager>::asPtr( progBox->currentData())->getDefaultModes()))
   modes.append(mode);
 }
 // add OPSACCBYTEMODE & OPSACCEXTBYTEMODE if possible
 if (modes.contains("OPSBYTEMODE"))
 {
     if (!modes.contains("OPSACCBYTEMODE"))
     {
         log->debug(tr("   adding button for %1 via AccessoryOpsModeProgrammerFacade").arg( ProgrammingMode::OPSACCBYTEMODE->toString()));
         modes.append("OPSACCBYTEMODE");
     }
     if (!modes.contains("OPSACCEXTBYTEMODE"))
     {
         log->debug(tr("   adding button for %1 via AccessoryOpsModeProgrammerFacade").arg( ProgrammingMode::OPSACCEXTBYTEMODE->toString()));
         modes.append("OPSACCEXTBYTEMODE");
     }
 }
 log->debug(tr("   has %1 modes").arg(modes.size()));
 for (QString mode : modes) {
     QRadioButton* button;
     // need a new button?
     if (index >= buttonPool.size()) {
         log->debug("   add button");
         button = new QRadioButton();
         buttonPool.append(button);
         modeGroup->addButton(button);
         //button.addActionListener(this);
         connect(button, SIGNAL(clicked(bool)), this, SLOT());
         thisLayout->addWidget(button); // add to GUI
     }
     // configure next button in pool
     log->debug(tr("   set for %1").arg(mode));
     button = buttonPool.value(index++);
     button->setVisible(true);
     modeGroup->addButton(button);
     button->setText(mode);
     buttonMap.insert(mode, button);
 }

 setGuiFromProgrammer();
}

/**
* Listen to buttons for mode changes
*/
/*public*/ void ProgOpsModePane::actionPerformed(JActionEvent* /*e*/)
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
 QMapIterator<QString, QRadioButton*> iter(buttonMap);
 while(iter.hasNext())
 {
  iter.next();
  if(iter.value()->isChecked())
  {
      if(getProgrammer() != NULL)
          getProgrammer()->setMode(new ProgrammingMode(iter.key()));
      return; // 1st match
  }
 }
}

void ProgOpsModePane::setProgrammerFromGui(Programmer* programmer) {
//   for (ProgrammingMode mode : buttonMap.keySet() ) {
//       if (buttonMap.get(mode).isSelected())
//           programmer.setMode(mode);
//   }
    QMapIterator<QString, QRadioButton*> iter(buttonMap);
    while(iter.hasNext())
    {
     iter.next();
     if(iter.value()->isChecked())
         programmer->setMode(new ProgrammingMode(iter.key()));
    }
}

/**
* Listen to programmer for mode changes
*/
/*public*/ void ProgOpsModePane::propertyChange(PropertyChangeEvent* e) {
  if ("Mode"==(e->getPropertyName()) && getProgrammer()->self()==(e->getSource())) {
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
 QRadioButton* button = buttonMap.value(mode->getStandardName());
 if (button == NULL)
 {
  log->error("setGuiFromProgrammer found mode \"{}\" that's not supported by the programmer" + mode->toString());
   return;
 }
 log->debug("  setting button for mode {}" + mode->toString());
 button->setChecked(true);
}

/**
 * Set address limits and field names depending on address type.
 */
void ProgOpsModePane::setAddrParams()
{
 if (opsAccyMode)
 {
     shortAddrButton->setText(tr("Decoder Address"));
     shortAddrButton->setToolTip(tr("The 9-bit decoder or board address (range 1-511)"));
     shortAddrButton->setVisible(true);
     longAddrButton->setText(tr("Accessory address"));
     longAddrButton->setToolTip(tr("The 11-bit accessory or output address (range 1-2044)"));
     offsetAddrCheckBox->setVisible(false);
     addressLabel->setText(tr("Address:"));
     if (longAddrButton->isChecked()) {
         lowAddrLimit = 1;
         highAddrLimit = 2044;
     } else {
         lowAddrLimit = 1;
         highAddrLimit = 511;
     }
 } else if (opsSigMode) {
     shortAddrButton->setVisible(false);
     longAddrButton->setVisible(false);
     offsetAddrCheckBox->setVisible(true);
     addressLabel->setText(tr("Signal address:"));
     lowAddrLimit = 1;
     highAddrLimit = 2044;
 } else {
     shortAddrButton->setText(tr("Short address"));
     shortAddrButton->setToolTip(tr("The short (one byte) address (range 1-127)"));
     shortAddrButton->setVisible(true);
     longAddrButton->setText(tr("Long address"));
     longAddrButton->setToolTip(tr("The long (two byte) decoder address (range 0-10239)"));
     offsetAddrCheckBox->setVisible(false);
     addressLabel->setText(tr("Address:"));
     if (longAddrButton->isChecked()) {
         lowAddrLimit = 0;
         highAddrLimit = 10239;
     } else {
         lowAddrLimit = 1;
         highAddrLimit = 127;
     }
 }

 log->debug(tr(
         "Setting lowAddrLimit=%1, highAddrLimit=%2").arg(lowAddrLimit).arg(highAddrLimit));
 mAddrField->setMinimum(lowAddrLimit);

 mAddrField->setMaximum(highAddrLimit);
 int address;

 try {
     address = mAddrField->value();
 } catch (NumberFormatException e) {
     log->debug(tr("loco address \"%1\" not correct").arg(mAddrField->value()));
     return;
 }
 if (address < lowAddrLimit) {
     mAddrField->setValue(lowAddrLimit);
 } else if (address > highAddrLimit) {
     mAddrField->setValue(highAddrLimit);
 }
}

// no longer needed, disconnect if still connected
/*public*/ void ProgOpsModePane::dispose() {
}
