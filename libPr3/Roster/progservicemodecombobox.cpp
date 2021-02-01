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
#include "lnprogrammermanager.h"
#include <QMenu>
#include <QDebug>
#include "vptr.h"

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
 if (progBox == NULL)
  return NULL;
 if(progBox->count() == 1)
  progBox->setCurrentIndex(0);
 log->debug(tr("progBox: %1 items, current index %2, current text '%3'").arg(progBox->count()).arg(progBox->currentIndex()).arg(progBox->currentText()));
 QVariant v = progBox->itemData(progBox->currentIndex());
 DefaultProgrammerManager* pm = VPtr<DefaultProgrammerManager>::asPtr(progBox->currentData());
 if (pm == NULL)
  return NULL;
 return pm->getGlobalProgrammer();
}

/**
 * Are any of the modes selected?
 * @return true
 */
/*public*/ bool isSelected() {
    return true;
}

/*protected*/ QList<DefaultProgrammerManager*> getMgrList()
{
 QList<DefaultProgrammerManager*> list = QList<DefaultProgrammerManager*>();
 for(QObject* o : *InstanceManager::getList("GlobalProgrammerManager"))
 {
  list.append((DefaultProgrammerManager*)o);
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
 QVector<DefaultProgrammerManager*> v =  QVector<DefaultProgrammerManager*>();
 // create the programmer display combo box
 for (DefaultProgrammerManager* pm : getMgrList()) {
     Programmer* globProg = nullptr;
     if (pm != nullptr) {
         globProg = pm->getGlobalProgrammer();
     }
     if (globProg != nullptr) {
         v.append(pm);
         log->debug(tr("ProgSMCombo added programmer %1 as item %2").arg(
                 (pm != nullptr ? pm->metaObject()->className() : "null")).arg(v.size()));
         // listen for changes
         globProg->addPropertyChangeListener((PropertyChangeListener*)this);
     }
 }

 layout->addWidget(progLabel);
 layout->addWidget(progBox = new QComboBox());
 for(DefaultProgrammerManager* pm : v)
 {
  log->debug(tr("ProgBox add: '%1'").arg(pm->toString()));
  const QVariant v = VPtr<DefaultProgrammerManager>::asQVariant(pm);
  progBox->addItem(pm->toString(), v);
  progBox->setItemData(progBox->currentIndex(), v);
 }
 // if only one, don't show is confusing to user, so show combo with just 1 choice)
 QVariant v1 = progBox->itemData(progBox->currentIndex(), Qt::UserRole);
 progBox->setCurrentText(((DefaultProgrammerManager*)InstanceManager::getDefault("GlobalProgrammerManager"))->toString()); // set default
 log->debug(tr("progBox: %1 items, current index %2, current text '%3'").arg(progBox->count()).arg(progBox->currentIndex()).arg(progBox->currentText()));
 if(progBox->count() == 1)
  progBox->setCurrentIndex(0);
// progBox.addActionListener(new ActionListener() {
//     @Override
//     public void actionPerformed(ActionEvent e) {
 connect(progBox, &QComboBox::currentTextChanged, [=]{
         // new programmer selection
         programmerSelected();
 });

 // install items in GUI
 layout->addWidget(new JLabel(tr("Mode:")));

 layout->addWidget(modeBox);

 // and execute the setup for 1st time
 programmerSelected();
}

/**
 * reload the interface with the new programmers
 */
void ProgServiceModeComboBox::programmerSelected()
{
 //DefaultComboBoxModel<ProgrammingMode*> model = new DefaultComboBoxModel<ProgrammingMode*>();
 modeBox->clear();
 Programmer* p = getProgrammer();
 if (p!=NULL)
 {
  QList<QString> modeList = getProgrammer()->getSupportedModes();
  foreach(QString mode, modeList )
  {
   modeBox->addItem(mode, VPtr<ProgrammingMode>::asQVariant(new ProgrammingMode(mode)));
  }
 }
}

/**
 * Listen to box for mode changes
 */
/*public*/ void ProgServiceModeComboBox::actionPerformed(JActionEvent* /*e*/) {
 // convey change to programmer
 log->debug("Selected mode: " + modeBox->currentText());
 getProgrammer()->setMode(VPtr<ProgrammingMode>::asPtr(modeBox->itemData(modeBox->currentIndex())));
}

/**
 * Listen to programmer for mode changes
 */
/*public*/ void ProgServiceModeComboBox::propertyChange(PropertyChangeEvent* e) {
 if ("Mode"==(e->getPropertyName()) && getProgrammer()->self()==(e->getSource()))
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
