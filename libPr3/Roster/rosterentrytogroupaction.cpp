#include "rosterentrytogroupaction.h"
#include "roster.h"
#include <QComboBox>
#include "rostergroupcombobox.h"
#include "inputdialog.h"
#include "rosterentry.h"

//RosterEntryToGroupAction::RosterEntryToGroupAction(QObject *parent) :
//  QAction(parent)
//{
//}
/**
 * Associate a Roster Entry to a Roster Group
 *
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <P>
 * @author	Kevin Dickerson Copyright (C) 2009
 * @version	$Revision: 28746 $
 */
///*public*/ class RosterEntryToGroupAction extends AbstractAction {

/**
 *
 */
// private static final long serialVersionUID = 583406343893394954L;

/**
 * @param s Name of this action, e.g. in menus
 * @param who Component that action is associated with, used to ensure
 * proper position in of dialog boxes
 */
/*public*/ RosterEntryToGroupAction::RosterEntryToGroupAction(QString s, QWidget* who)
 : QAction(s, who)
{
 //super(s);
 _who = who;
 rosterEntry = new QComboBox();
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 log = new Logger("RosterEntryToGroupAction");
 lastGroupSelect = "";
}


/*public*/ void RosterEntryToGroupAction::actionPerformed(ActionEvent* event)
{
 roster = Roster::instance();

 selections = new RosterGroupComboBox();
 selections->setObjectName("selections");
 selections->setAllEntriesEnabled(false);
 selections->setVisible(true);
 selections->setEnabled(true);
 if (lastGroupSelect != "")
 {
  selections->setCurrentIndex(selections->findText(lastGroupSelect));
 }

 rosterEntryUpdate();
// selections.addActionListener(new ActionListener() {
//     /*public*/ void actionPerformed(ActionEvent e) {
//         rosterEntryUpdate();
//     }
// });
 connect(selections, SIGNAL(currentIndexChanged(QString)), this, SLOT(rosterEntryUpdate()));
// int retval = JOptionPane.showOptionDialog(_who,
//         "Select the roster entry and the group to assign it to\nA Roster Entry can belong to multiple groups. ", "Add Roster Entry to Group",
//         0, JOptionPane.INFORMATION_MESSAGE, null,
//         new Object[]{"Cancel", "OK", selections, rosterEntry}, null);
 QList<QWidget*> list = QList<QWidget*>();
 list << rosterEntry << (QComboBox*)selections;
 InputDialog* dlg = new InputDialog("Select the roster entry and the group to assign it to\nA Roster Entry can belong to multiple groups. ", list, "Add Roster Entry to Group");
 int retval = dlg->exec();

 log->debug(tr("Dialog value ") + QString::number(retval) + " selected " + QString::number(selections->currentIndex()) + ":"
         + selections->currentText() + ", " + QString::number(rosterEntry->currentIndex()) + ":" + rosterEntry->currentText());
 if (retval != QDialog::Accepted)
 {
     return;
 }

 QString selEntry = rosterEntry->currentText();
 lastGroupSelect = selections->currentText();
 RosterEntry* re = roster->entryFromTitle(selEntry);
 QString selGroup = Roster::getRosterGroupProperty( selections->currentText());
 re->putAttribute(selGroup, "yes");
 Roster::writeRosterFile();
 re->updateFile();
 actionPerformed(event);
}

void RosterEntryToGroupAction::rosterEntryUpdate()
{
 if (rosterEntry != NULL)
 {
  rosterEntry->clear();
 }
 QString group = roster->getRosterGroupPrefix() + selections->currentText();
 for (int i = 0; i < roster->numEntries(); i++)
 {
  RosterEntry* r = roster->getEntry(i);
  if (r->getAttribute(group) == "")
  {
   rosterEntry->addItem(r->titleString());
  }
 }
}
