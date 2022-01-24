#ifndef ROSTERGROUPSELECTOR_H
#define ROSTERGROUPSELECTOR_H

#include <QComboBox>
#include "propertychangeevent.h"
#include "propertychangelistener.h"

class RosterGroupSelector
{
 //Q_OBJECT
public:
 //explicit RosterGroupSelector(QWidget* parent = 0);
 /*public*/ /*final*/ static QString SELECTED_ROSTER_GROUP; //= "selectedRosterGroup";

 virtual /*public*/ QString getSelectedRosterGroup() {return "";}

 virtual /*public*/ void addPropertyChangeListener(PropertyChangeListener* listener){}

  virtual /*public*/ void addPropertyChangeListener(QString /*propertyName*/, PropertyChangeListener* /*listener*/) {}

  virtual /*public*/ void removePropertyChangeListener(PropertyChangeListener* listener){}

 virtual /*public*/ void removePropertyChangeListener(QString /*propertyName*/, PropertyChangeListener* /*listener*/) {}
 virtual QObject* self() =0;

signals:
 //void propertyChange(PropertyChangeEvent*);

public slots:
};
Q_DECLARE_INTERFACE(RosterGroupSelector, "RosterGroupSelector")
#endif // ROSTERGROUPSELECTOR_H
