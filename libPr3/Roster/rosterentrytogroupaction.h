#ifndef ROSTERENTRYTOGROUPACTION_H
#define ROSTERENTRYTOGROUPACTION_H

#include <QAction>
#include "logger.h"

class QComboBox;
class RosterGroupComboBox;
class Roster;
class RosterEntryToGroupAction : public QAction
{
 Q_OBJECT
public:
 //explicit RosterEntryToGroupAction(QObject *parent = 0);
 /*public*/ RosterEntryToGroupAction(QString s, QWidget* who);

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* event = 0);

private:
 QWidget*  _who;
 QComboBox* rosterEntry;// = new JComboBox<String>();
 RosterGroupComboBox* selections;
 Roster* roster;
 QString lastGroupSelect;// = "";
 Logger* log;

private slots:
 void rosterEntryUpdate();

};

#endif // ROSTERENTRYTOGROUPACTION_H
