#ifndef REMOVEROSTERENTRYTOGROUPACTION_H
#define REMOVEROSTERENTRYTOGROUPACTION_H

#include <QAction>
#include "logger.h"

class RosterEntrySelectorPanel;
class QLabel;
class QPushButton;
class JmriJFrame;
class RemoveRosterEntryToGroupAction : public QAction
{
 Q_OBJECT
public:
 //explicit RemoveRosterEntryToGroupAction(QObject *parent = 0);
 /*public*/ RemoveRosterEntryToGroupAction(QString s, QWidget* who);

signals:

public slots:
 /*public*/ void okPressed();
 /*public*/ void dispose();
 /*public*/ void actionPerformed(ActionEvent* /*event*/ = 0);


private:
 QWidget* _who;
 QString curRosterGroup;
 JmriJFrame* frame;// = null;
 //    JComboBox typeBox;
 QLabel* jLabel;// = new JLabel("Select the Group");
 RosterEntrySelectorPanel* rosterBox;
 QPushButton* okButton;// = new JButton("Remove");
 QPushButton* cancelButton;// = new JButton("Exit");
 bool userOK(QString entry);
 Logger* log;
};

#endif // REMOVEROSTERENTRYTOGROUPACTION_H
