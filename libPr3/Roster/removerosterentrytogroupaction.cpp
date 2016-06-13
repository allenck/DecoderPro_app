#include "removerosterentrytogroupaction.h"
#include "jmrijframe.h"
#include <QPushButton>
#include <QLabel>
#include "rosterentryselectorpanel.h"
#include <QBoxLayout>
#include "flowlayout.h"
#include "rosterentry.h"
#include <QMessageBox>

//RemoveRosterEntryToGroupAction::RemoveRosterEntryToGroupAction(QObject *parent) :
//  QAction(parent)
//{
//}
/**
 * Remove a locomotive from a roster grouping.
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
 * @version	$Revision: 29396 $
 */
// /*public*/ class RemoveRosterEntryToGroupAction extends AbstractAction {

/**
 *
 */
//private static final long serialVersionUID = 3631492408927497941L;

/**
 * @param s   Name of this action, e.g. in menus
 * @param who Component that action is associated with, used to ensure
 *            proper position in of dialog boxes
 */
/*public*/ RemoveRosterEntryToGroupAction::RemoveRosterEntryToGroupAction(QString s, QWidget* who) : QAction(s, who)
{
 //super(s);
 _who = who;
 frame = NULL;
 //    JComboBox typeBox;
 jLabel = new QLabel("Select the Group");
 okButton = new QPushButton("Remove");
 cancelButton = new QPushButton("Exit");
 log = new Logger("RemoveRosterEntryToGroupAction");
}


/*public*/ void RemoveRosterEntryToGroupAction::actionPerformed(ActionEvent* /*event*/)
{
 frame = new JmriJFrame("Remove Loco from Group");
 rosterBox = new RosterEntrySelectorPanel();
 rosterBox->getRosterGroupComboBox()->setAllEntriesEnabled(false);
//    frame.getContentPane().setLayout(new BoxLayout(frame.getContentPane(), BoxLayout.Y_AXIS));
 QWidget* centralWidget = new QWidget();
 QVBoxLayout* centralWidgetLayout = new QVBoxLayout;
 centralWidget->setLayout(centralWidgetLayout);
 frame->setCentralWidget(centralWidget);
 QWidget* p;
 p = new QWidget();
 FlowLayout* pLayout;
 p->setLayout(pLayout = new FlowLayout());
 pLayout->addWidget(jLabel);
 pLayout->addWidget(rosterBox);
 //frame.getContentPane().add(p);
 centralWidgetLayout->addWidget(p);

 {
  p = new QWidget();
  FlowLayout* pLayout;
  p->setLayout(pLayout = new FlowLayout());
  pLayout->addWidget(okButton);
//     okButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            okPressed();
//        }
//     });
  connect(okButton, SIGNAL(clicked()), this, SLOT( okPressed()));
  pLayout->addWidget(cancelButton);
//     cancelButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            dispose();
//        }
//     });
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(dispose()));
  //frame.getContentPane().add(p);
  centralWidgetLayout->addWidget(p);
  }
 frame->pack();
 frame->setVisible(true);

}

/**
 * Can provide some mechanism to prompt for user for one last chance to
 * change his/her mind
 *
 * @return true if user says to continue
 */
bool RemoveRosterEntryToGroupAction::userOK(QString entry)
{
//    return (JOptionPane.YES_OPTION
//            == JOptionPane.showConfirmDialog(_who,
//                    "Delete roster group " + entry,
//                    "Delete roster group " + entry + "?", JOptionPane.YES_NO_OPTION));
 int retval = QMessageBox::question(NULL, "Delete roster group " + entry, "Delete roster group " + entry + "?", QMessageBox::Yes | QMessageBox::No);
 return (retval == QMessageBox::Yes);
}

//    // initialize logging
//    static Logger log = LoggerFactory.getLogger(RemoveRosterEntryToGroupAction.class.getName());

/*public*/ void RemoveRosterEntryToGroupAction::okPressed()
{
 QString group = rosterBox->getSelectedRosterGroup();
 log->info("Selected " + group);
 if (group != "" && group!=(Roster::ALLENTRIES))
 {
  if (rosterBox->getSelectedRosterEntries()->length() != 0)
  {
   RosterEntry* re = rosterBox->getSelectedRosterEntries()->at(0);
   log->info("Preparing to remove " + re->getId() + " from " + group);
   re->deleteAttribute(Roster::getRosterGroupProperty(group));
   re->updateFile();
   Roster::writeRosterFile();
   rosterBox->getRosterEntryComboBox()->update();
  }
 }
 frame->pack();

}

/*public*/ void RemoveRosterEntryToGroupAction::dispose()
{
 frame->dispose();
}
