#ifndef ROSTERENTRYSELECTORPANEL_H
#define ROSTERENTRYSELECTORPANEL_H

#include <QWidget>
#include "rosterentrycombobox.h"
#include "rostergroupcombobox.h"
#include <QFormLayout>

class LIBPR3SHARED_EXPORT RosterEntrySelectorPanel : public QFrame
{
    Q_OBJECT
public:
    //explicit RosterEntrySelectorPanel(QWidget *parent = 0);
    /*public*/ RosterEntrySelectorPanel(QWidget *parent = 0);
    /*public*/ RosterEntrySelectorPanel(RosterEntry* re, QString rg, QWidget *parent = 0);
    /*public*/ QList<RosterEntry*>* getSelectedRosterEntries();
    /*public*/ void setSelectedRosterEntry(RosterEntry* re);
    /*public*/ void setSelectedRosterEntryAndGroup(RosterEntry* re, QString rg);
    /*public*/ QString getSelectedRosterGroup();
    /*public*/ void setSelectedRosterGroup(QString rg);
    /*public*/ RosterEntryComboBox* getRosterEntryComboBox();
    /*public*/ RosterGroupComboBox* getRosterGroupComboBox();
    /*public*/ void setEnabled(bool enabled);
    /*public*/ bool isEnabled();
    /*public*/ QString getNonSelectedItem();
    /*public*/ void setNonSelectedItem(QString itemText);

signals:
    void propertyChange(PropertyChangeEvent*);
public slots:
    void on_rosterGroup_changed(QString text);
    void on_rosterEntryPropertyChange(QString,QList<RosterEntry*>*,QList<RosterEntry*>*);

private:
    /*private*/ RosterEntryComboBox* entryCombo;
    /*private*/ RosterGroupComboBox* groupCombo;
QHBoxLayout* horizontalLayout;
void init(RosterEntry* re, QString rg);

};

#endif // ROSTERENTRYSELECTORPANEL_H
