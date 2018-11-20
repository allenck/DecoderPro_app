#include "progservicemodecombobox.h"
#include "instancemanager.h"
#include <QComboBox>
#include <QLabel>
#include "flowlayout.h"
#include "abstractprogrammer.h"
#include "slotmanager.h"
#include "globalprogrammermanager.h"
#include "defaultcomboboxmodel.h"
#include "rosterentry.h"
#include "programmingmode.h"
#include "defaultprogrammermanager.h"

//ProgServiceModeComboBox::ProgServiceModeComboBox(QWidget *parent) :
//    ProgModeSelector(parent)
//{
//}
/**
 * Provide a JPanel with a JComboBox to configure the service mode programmer.
 * <P>
 * The using code should get a configured programmer with getProgrammer. Since
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
///*public*/ class ProgServiceModeComboBox extends ProgModeSelector implements java.beans.PropertyChangeListener {


/**
 * Get the configured programmer
 */
/*public*/ Programmer* ProgServiceModeComboBox::getProgrammer()
{
 if (progBox == NULL) return NULL;
 GlobalProgrammerManager* pm = VPtr<GlobalProgrammerManager>::asPtr(progBox->itemData(progBox->currentIndex()));
 if (pm == NULL) return NULL;
 return pm->getGlobalProgrammer();
}

/**
 * Are any of the modes selected?
 * @return true
 */
/*public*/ bool isSelected() {
    return true;
}

/*protected*/ QList<GlobalProgrammerManager*> getMgrList()
{
 //return InstanceManager::getList("GlobalProgrammerManager");
 QList<GlobalProgrammerManager*> list;
 QObjectList objectList = InstanceManager::getList("GlobalProgrammerManager");
 foreach(QObject* o, objectList)
 {
  GlobalProgrammerManager* globalProgrammerManager = (GlobalProgrammerManager*)o;
  list.append(globalProgrammerManager);
 }
 return list;
}


/*public*/ ProgServiceModeComboBox::ProgServiceModeComboBox(QBoxLayout::Direction direction, QWidget* parent) : ProgModeSelector(parent)
{
 log = new Logger("ProgServiceModeComboBox");
 //modeBox = new JComboBox<ProgrammingMode>();
 progBox = NULL;
 modeBox = new QComboBox();
 //modeBox.addActionListener(this);
 connect(modeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(actionPerformed()));

 // general GUI config
 QBoxLayout* layout;
 setLayout(layout = new QBoxLayout(direction));
 layout->setContentsMargins(0,0,0,0);

 // create the programmer display combo box
 //progBox = new JComboBox<GlobalProgrammerManager>();
 progBox = new QComboBox();
 QVector<GlobalProgrammerManager*> v =  QVector<GlobalProgrammerManager*>();
 QList<GlobalProgrammerManager*> mgrList = getMgrList();
 if (!mgrList.isEmpty())
 {
  foreach (GlobalProgrammerManager* pm, mgrList)
  {
   if (pm != NULL && pm->getGlobalProgrammer() != NULL)
   {
    v.append(pm);
    progBox->addItem(pm->getUserName(), VPtr<GlobalProgrammerManager>::asQVariant(pm));
    // listen for changes
    // TODO : pm.getGlobalProgrammer().addPropertyChangeListener(this);
    AbstractProgrammer* pgmr = (AbstractProgrammer*) ((DefaultProgrammerManager*)pm)->getGlobalProgrammer();
    connect(pgmr->propertyChangeSupport, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   }
  }
 }
 layout->addWidget(progBox/* = new QComboBox<GlobalProgrammerManager>(v)*/);
 // if only one, don't show
 if (progBox->count()<2)
 {
  progBox->setVisible(false);
 }
 else
 {
  progBox->setCurrentIndex(progBox->findText(((GlobalProgrammerManager*)InstanceManager::getDefault("GlobalProgrammerManager"))->getUserName())); // set default
//             progBox.addActionListener(new ActionListener(){
//                 public void actionPerformed(ActionEvent e) {
//                     // new programmer selection
//                     programmerSelected();
//                 }
//             });
  connect(progBox, SIGNAL(currentIndexChanged(int)), this, SLOT(programmerSelected()));
 }

 // install items in GUI
 layout->addWidget(new QLabel(tr("Programming Mode")));

 layout->addWidget(modeBox);

 // and execute the setup for 1st time
 programmerSelected();
}
/**
 * reload the interface with the new programmers
 */
void ProgServiceModeComboBox::programmerSelected()
{
#if 0
 DefaultComboBoxModel<ProgrammingMode*>* model = new DefaultComboBoxModel<ProgrammingMode*>();
 Programmer* p = getProgrammer();
 if (p!=NULL)
 {
  foreach (ProgrammingMode* mode, getProgrammer()->getSupportedModes())
  {
   model->addElement(mode);
  }
 }
 //modeBox->setModel(model);
 for(int i = 0; i < model->getSize(); i++)
 {
  ProgrammingMode* mode = model->getElementAt(i);
  modeBox->addItem(mode->getStandardName(), VPtr<ProgrammingMode>::asQVariant(mode));
 }
#endif
 modeBox->clear();
 Programmer* p = getProgrammer();
 if (p!=NULL)
 {
  QList<ProgrammingMode*> modeList = getProgrammer()->getSupportedModes();
  foreach(ProgrammingMode* mode, modeList )
  {
   modeBox->addItem(mode->getStandardName(), VPtr<ProgrammingMode>::asQVariant(mode));
  }
 }
}

/**
 * Listen to box for mode changes
 */
/*public*/ void ProgServiceModeComboBox::actionPerformed(ActionEvent* /*e*/) {
 // convey change to programmer
 log->debug("Selected mode: " + modeBox->currentText());
 getProgrammer()->setMode(VPtr<ProgrammingMode>::asPtr(modeBox->itemData(modeBox->currentIndex())));
}

/**
 * Listen to programmer for mode changes
 */
/*public*/ void ProgServiceModeComboBox::propertyChange(PropertyChangeEvent* e) {
 if ("Mode"==(e->getPropertyName()) && getProgrammer()==(e->getSource()))
 {
  // mode changed in programmer, change GUI here if needed
  if (isSelected())
  {  // if we're not holding a current mode, don't update
   modeBox->setCurrentIndex(modeBox->findText(VPtr<ProgrammingMode>::asPtr(e->getNewValue())->getStandardName()));
  }
 }
}

// no longer needed, disconnect if still connected
/*public*/ void ProgServiceModeComboBox::dispose() {
}
