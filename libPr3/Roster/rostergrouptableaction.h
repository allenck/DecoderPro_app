#ifndef ROSTERGROUPTABLEACTION_H
#define ROSTERGROUPTABLEACTION_H

#include "jmriabstractaction.h"
#include "rostergrouptableframe.h"
#include "libPr3_global.h"

class RosterGroupTableModel;
class RosterGroupTableFrame;
class WindowInterface;
class JmriPanel;
class LIBPR3SHARED_EXPORT RosterGroupTableAction : public JmriAbstractAction
{
 Q_OBJECT
public:
 explicit RosterGroupTableAction(QObject *parent = 0);
 /*public*/ RosterGroupTableAction(QString s, WindowInterface* wi);
 /*public*/ RosterGroupTableAction(QString s, QIcon i, WindowInterface* wi);
 /*public*/ RosterGroupTableAction(QString s, QObject* parent);
 ///*public*/ RosterGroupTableAction(QObject* parent);
 ~RosterGroupTableAction() {}
 RosterGroupTableAction(const RosterGroupTableAction& other) : JmriAbstractAction(other.text(), other.parent()) {}
 /*public*/ void addToFrame(RosterGroupTableFrame* f);
 /*public*/ JmriPanel* makePanel();

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);
 void comboSelected(/*ActionEvent* e,*/ QString group);

private:
 void common();
 RosterGroupTableModel* m;
 RosterGroupTableFrame* f;
 void createModel();
 void setTitle();
 QString helpTarget();

};
Q_DECLARE_METATYPE(RosterGroupTableAction)

class MyRosterGroupTableFrame : public RosterGroupTableFrame
{
 Q_OBJECT
 RosterGroupTableAction* self;
public:
 MyRosterGroupTableFrame(RosterGroupTableModel* m, QString helpTarget, RosterGroupTableAction* self);
 /**
  * Include an "add" button
  */
 void extras();

};

#endif // ROSTERGROUPTABLEACTION_H
