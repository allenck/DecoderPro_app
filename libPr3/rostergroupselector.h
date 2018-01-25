#ifndef ROSTERGROUPSELECTOR_H
#define ROSTERGROUPSELECTOR_H

#include <QComboBox>
#include "propertychangeevent.h"

class RosterGroupSelector : public QComboBox
{
 Q_OBJECT
public:
 explicit RosterGroupSelector(QWidget* parent = 0);
 /*public*/ /*final*/ static QString SELECTED_ROSTER_GROUP; //= "selectedRosterGroup";

 virtual /*public*/ QString getSelectedRosterGroup() {return "";}

// /*public*/ void addPropertyChangeListener(PropertyChangeListener listener);

// /*public*/ void addPropertyChangeListener(String propertyName, PropertyChangeListener listener);

// /*public*/ void removePropertyChangeListener(PropertyChangeListener listener);

// /*public*/ void removePropertyChangeListener(String propertyName, PropertyChangeListener listener);


signals:
 void propertyChange(PropertyChangeEvent*);

public slots:
};

#endif // ROSTERGROUPSELECTOR_H
