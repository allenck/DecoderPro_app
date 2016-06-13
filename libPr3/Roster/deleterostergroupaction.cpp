#include "deleterostergroupaction.h"
#include "jmripanel.h"
#include <QMessageBox>
//#include "beans.h"
#include "inputdialog.h"
#include "roster.h"
#include <QComboBox>

DeleteRosterGroupAction::DeleteRosterGroupAction(QObject *parent) :
  JmriAbstractAction((WindowInterface*)parent)
{
 common();
}
/**
 * Remove roster group.
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
 * @version	$Revision: 28771 $
 */
// /*public*/ class DeleteRosterGroupAction extends JmriAbstractAction {

/**
 *
 */
//private static final long serialVersionUID = -5645990386314165982L;

/*public*/ DeleteRosterGroupAction::DeleteRosterGroupAction(QString s, WindowInterface* wi)
 : JmriAbstractAction(s, (QObject*)wi)
{
 //super(s, wi);
 common();
}

/*public*/ DeleteRosterGroupAction::DeleteRosterGroupAction(QString s, QIcon i, WindowInterface* wi)
 : JmriAbstractAction(s, i, (WindowInterface*)wi)
{
 //super(s, i, wi);
 common();
}

/**
 * @param s   Name of this action, e.g. in menus
 * @param who Component that action is associated with, used to ensure
 *            proper position in of dialog boxes
 */
/*public*/ DeleteRosterGroupAction::DeleteRosterGroupAction(QString s, QWidget* who)
 : JmriAbstractAction(s, who)
{
 //super(s);
 common();
 _who = who;
}

void DeleteRosterGroupAction::common()
{
 _who = NULL;
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/**
 * Call setParameter("group", oldName) prior to calling
 * actionPerformed(event) to bypass the roster group selection dialog if the
 * name of the group to be copied is already known and is not the
 * selectedRosterGroup property of the WindowInterface.
 *
 * @param event
 */
//@Override
/*public*/ void DeleteRosterGroupAction::actionPerformed(ActionEvent* event)
{
 QString group = "";
#if 0 // TODO:
 if (Beans.hasProperty(wi, "selectedRosterGroup")) {
     group = (String) Beans.getProperty(wi, "selectedRosterGroup");
 }
#endif
 // null might be valid output from getting the selectedRosterGroup,
 // so we have to check for null again.
 if (group == "")
 {
//     group = (String) JOptionPane.showInputDialog(_who,
//             "<html><b>Delete roster group</b><br>Roster entries in the group are not deleted.</html>",
//             "Delete Roster Group",
//             JOptionPane.INFORMATION_MESSAGE,
//             null,
//             Roster.instance().getRosterGroupList().toArray(),
//             null);
  QComboBox* box;
  box->addItems( Roster::instance()->getRosterGroupList().toList());
  InputDialog* dlg = new InputDialog("<html><b>Delete roster group</b><br>Roster entries in the group are not deleted.</html>", box, "Delete Roster Group");
  group = dlg->value();
 }
 // can't delete the roster itself (ALLENTRIES and null represent the roster)
 if (group == "" || group==(Roster::ALLENTRIES)) {
     return;
 }
 // prompt for one last chance
 if (!userOK(group))
 {
  return;
 }

 // delete the roster grouping
 Roster::instance()->delRosterGroupList(group);
 Roster::writeRosterFile();
}

/**
 * Can provide some mechanism to prompt for user for one last chance to
 * change his/her mind
 *
 * @return true if user says to continue
 */
bool DeleteRosterGroupAction::userOK(QString entry) {
 QStringList titles = QStringList() << "Delete" << "Cancel";
    // TODO: I18N
    // TODO: replace "Are you sure..." string with JPanel containing string
    //       and checkbox silencing this message in the future
//    return (JOptionPane.YES_OPTION == JOptionPane.showOptionDialog(_who,
//            "Are you sure you want to delete roster group \"" + entry + "\"?",
//            "Delete Roster Group \"" + entry + "\"",
//            JOptionPane.YES_NO_OPTION,
//            JOptionPane.QUESTION_MESSAGE,
//            null,
//            titles,
//            null));
    int reply = QMessageBox::question(_who, tr("Delete Roster Group") + "\"" + entry + "\"", tr("Are you sure you want to delete roster group")+ "\"" + entry + "\"", QMessageBox::Yes | QMessageBox::No);
    return (reply == QMessageBox::Yes);
}

// never invoked, because we overrode actionPerformed above
//@Override
/*public*/ JmriPanel* DeleteRosterGroupAction::makePanel() {
    throw new IllegalArgumentException("Should not be invoked");
}
