#ifndef ROSTERGROUPCOMBOBOX_H
#define ROSTERGROUPCOMBOBOX_H

#include <QComboBox>
#include "roster.h"

class LIBPR3SHARED_EXPORT RosterGroupComboBox : public QComboBox
{
    Q_OBJECT
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
