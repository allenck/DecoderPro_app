#ifndef ROSTERGROUPCOMBOBOX_H
#define ROSTERGROUPCOMBOBOX_H

#include "rostergroupselector.h"
#include "roster.h"

class LIBPR3SHARED_EXPORT RosterGroupComboBox : public QComboBox, public RosterGroupSelector
{
    Q_OBJECT
 Q_INTERFACES(RosterGroupSelector)
public:
    //explicit RosterGroupComboBox(QObject *parent = 0);
    /*public*/ RosterGroupComboBox(Roster* roster, QWidget *parent = 0);
    /*public*/ RosterGroupComboBox(QString selection, QWidget *parent = 0);
    /*public*/ RosterGroupComboBox(Roster* roster, QString selection, QWidget *parent = 0);
    /*public*/ RosterGroupComboBox(QWidget *parent = 0);
    /*public*/ /*final*/ void update();
    /*public*/ /*final*/ void update(QString selection);
    /*public*/ QString getSelectedRosterGroup();
    /*public*/ bool isAllEntriesEnabled();
    /*public*/ void setAllEntriesEnabled(bool allEntriesEnabled);
  QObject* self() override{return (QObject*)this;}

signals:

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* pce);

private:
 void common(Roster* roster, QString selection);
    /*private*/ Roster* _roster;
    /*private*/ bool allEntriesEnabled;// = true;
    QWidget *parent;
protected:

};

#endif // ROSTERGROUPCOMBOBOX_H
