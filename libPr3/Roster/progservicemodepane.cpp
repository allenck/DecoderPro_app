#include "progservicemodepane.h"
#include <QButtonGroup>
#include "instancemanager.h"
#include <lnprogrammermanager.h>
#include <QRadioButton>
#include <QBoxLayout>
#include "globalprogrammermanager.h"
#include <QComboBox>
#include "programmer.h"
#include "rosterentry.h"
#include "programmingmode.h"

//ProgServiceModePane::ProgServiceModePane(QWidget *parent) :
//    ProgModeSelector(parent)
//{
//}
/**
 * Provide a JPanel to configure the service mode programmer.
 * <P>
 * The using code should get a configured programmer with getProgrammer:: Since
 * there's only one service mode programmer, maybe this isn't critical, but
 * it's a good idea for the future.
 * <P>
 * A ProgModePane may "share" between one of these and a ProgOpsModePane,
 * which means that there might be _none_ of these buttons selected.  When
 * that happens, the mode of the underlying programmer is left unchanged
 * and no message is propagated.
 * <P>
 * Note that you should call the dispose() method when you're really done, so that
 * a ProgModePane object can disconnect its listeners.
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 * @author			Bob Jacobsen   Copyright (C) 2001
 * @version			$Revision: 22216 $
 */
// /*public*/ class ProgServiceModePane extends ProgModeSelector implements java.beans.PropertyChangeListener {

void ProgServiceModePane::init()
{
 modeGroup 		= new QButtonGroup();
 buttonMap = new QMap<QString, QRadioButton*>();
 buttonPool = new QList<QRadioButton*>();
 log = new Logger("ProgServiceModePane");
}

/**
  * Get the selected programmer
  */
/*public*/ Programmer* ProgServiceModePane::getProgrammer()
{
  return VPtr<GlobalProgrammerManager>::asPtr(progBox->itemData(progBox->currentIndex()))->getGlobalProgrammer();
}

/**
  * Are any of the modes selected?
  * @return true is any button is selected
  */
/*public*/ bool ProgServiceModePane::isSelected()
{
 foreach (QRadioButton* button, buttonMap->values())
 {
  if (button->isChecked()) return true;
 }
 return false;
}

/**
  * @param direction controls layout, either BoxLayout.X_AXIS or BoxLayout.Y_AXIS
  */
// /*public*/ ProgServiceModePane(int direction) {
//     this(direction, new javax.swing.ButtonGroup());
// }

/*protected*/ QList<GlobalProgrammerManager*>* ProgServiceModePane::getMgrList()
{
 QObjectList* objectList = InstanceManager::getList("GlobalProgrammerManager");
 QList<GlobalProgrammerManager*>* list = new  QList<GlobalProgrammerManager*>();
 foreach (QObject* o, *objectList)
 {
  GlobalProgrammerManager* mgr = (DefaultProgrammerManager*)o;
  list->append(mgr);
 }
 return list;
}

/**
  * @param direction controls layout, either BoxLayout.X_AXIS or BoxLayout.Y_AXIS
  */
/*public*/ ProgServiceModePane::ProgServiceModePane(QBoxLayout::Direction direction, QButtonGroup* group, QWidget *parent)
{
 modeGroup = group;

 // general GUI config
 setLayout(layout = new QBoxLayout(direction));

 // create the programmer display combo box
 QVector<GlobalProgrammerManager*>* v = new QVector<GlobalProgrammerManager*>();
 foreach (GlobalProgrammerManager* pm, *getMgrList())
 {
  v->append(pm);
  // listen for changes
  //pm.getGlobalProgrammer().addPropertyChangeListener(this);
  AbstractProgrammer* p =(AbstractProgrammer*) pm->getGlobalProgrammer();
  connect(p, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 layout->addWidget(progBox = new QComboBox);//<GlobalProgrammerManager>(v));
 foreach(GlobalProgrammerManager* mgr, *v)
 {
  progBox->addItem(mgr->getUserName(), VPtr<GlobalProgrammerManager>::asQVariant(mgr));
 }

 // if only one, don't show
 if (progBox->count()<2)
 {
  // no choice, so don't display, don't monitor for changes
  progBox->setVisible(false);
 }
 else
 {
  progBox->setCurrentIndex(progBox->findText(((DefaultProgrammerManager*)InstanceManager::getDefault("GlobalProgrammerManager"))->getUserName())); // set default
//   progBox.addActionListener(new java.awt.event.ActionListener(){
//         public void actionPerformed(java.awt.event.ActionEvent e) {
//             // new programmer selection
//             programmerSelected();
//         }
//     });
  connect(progBox, SIGNAL(currentIndexChanged(int)), this, SLOT(programmerSelected()));
 }

 // and execute the setup for 1st time
 programmerSelected();

 }

 /**
  * reload the interface with the new programmers
  */
 void ProgServiceModePane::programmerSelected()
 {
  log->debug("programmerSelected starts with {} buttons"+ QString::number(buttonPool->size()));
  // hide buttons
  foreach (QRadioButton* button, *buttonPool ) button->setVisible(false);

  // clear map
  buttonMap->clear();

  // configure buttons
  int index = 0;
  if (getProgrammer() == NULL) return;
  QList<QString> modes = getProgrammer()->getSupportedModes();
  log->debug("   has {} modes"+ QString::number(modes.size()));
  foreach (QString mode, modes)
  {
   QRadioButton* button;
   // need a new button?
   if (index >= buttonPool->size())
   {
    log->debug("   add button");
    button = new QRadioButton();
    buttonPool->append(button);
    modeGroup->addButton(button);
    //button.addActionListener(this);
    connect(button, SIGNAL(clicked()), this, SLOT(actionPerformed()));
    layout->addWidget(button); // add to GUI
   }
   // configure next button in pool
   log->debug("   set for "+ mode);
   button = buttonPool->value(index++);
   button->setVisible(true);
   modeGroup->addButton(button);
   button->setText(mode);
   buttonMap->insert(mode, button);
  }
  setGuiFromProgrammer();
 }

 /**
  * Listen to buttons for mode changes
  */
 /*public*/ void ProgServiceModePane::actionPerformed(JActionEvent* /*e*/)
 {
  // find selected button
  //log->debug("Selected button: {}", e.getActionCommand());
  //foreach (ProgrammingMode* mode, buttonMap->keys() )
  QMapIterator<QString, QRadioButton*> iter(*buttonMap);
  while(iter.hasNext())
  {
   iter.next();
   //if (mode->toString()==(e->getActionCommand()))
   if(iter.value()->isChecked())
   {
    log->debug("      set mode {} on {}"+iter.key() + getProgrammer()->self()->metaObject()->className());
    getProgrammer()->setMode(new ProgrammingMode(iter.key()));
    return; // 1st match
   }
  }
 }

 /**
  * Listen to programmer for mode changes
  */
 /*public*/ void ProgServiceModePane::propertyChange(PropertyChangeEvent* e)
 {
  if ("Mode"==(e->getPropertyName()) && getProgrammer()->self()==(e->getSource()))
  {
   // mode changed in programmer, change GUI here if needed
   log->debug(QString("Mode propertyChange with {}")+ (isSelected()?"true":"false"));
   if (isSelected())
   {  // only change mode if we have a selected mode, in case some other selector with shared group has the selection
    setGuiFromProgrammer();
   }
  }
 }

 void ProgServiceModePane::setGuiFromProgrammer()
 {
  QString mode = getProgrammer()->getMode()->getStandardName();
  QRadioButton* button = buttonMap->value(mode);
  log->debug("  setting button for mode "+ mode);
  if (button == NULL)
  {
   log->debug("   didn't find button, returning");
   return;
  }
  button->setChecked(true);
 }

 // no longer needed, disconnect if still connected
 /*public*/ void ProgServiceModePane::dispose()
 {
  foreach (GlobalProgrammerManager* pm, *getMgrList())
  {
//   pm->getGlobalProgrammer()->removePropertyChangeListener(this);
  }
 }
