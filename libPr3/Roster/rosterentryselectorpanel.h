#ifndef ROSTERENTRYSELECTORPANEL_H
#define ROSTERENTRYSELECTORPANEL_H

#include <QWidget>
#include "rosterentrycombobox.h"
#include "rostergroupcombobox.h"
#include <QFormLayout>
#include "jframe.h"

class LIBPR3SHARED_EXPORT RosterEntrySelectorPanel : public JFrame, public RosterEntrySelector, public RosterGroupSelector
{
    Q_OBJECT
    Q_INTERFACES(RosterEntrySelector RosterGroupSelector)
public:
    //explicit RosterEntrySelectorPanel(QWidget *parent = 0);
    /*public*/ RosterEntrySelectorPanel(QWidget *parent = 0);
    /*public*/ RosterEntrySelectorPanel(RosterEntry* re, QString rg, QWidget *parent = 0);
    /*public*/ QList<RosterEntry*>* getSelectedRosterEntries() override;
    /*public*/ void setSelectedRosterEntry(RosterEntry* re);
    /*public*/ void setSelectedRosterEntryAndGroup(RosterEntry* re, QString rg);
    /*public*/ QString getSelectedRosterGroup() override;
    /*public*/ void setSelectedRosterGroup(QString rg);
    /*public*/ RosterEntryComboBox* getRosterEntryComboBox();
    /*public*/ RosterGroupComboBox* getRosterGroupComboBox();
    /*public*/ void setEnabled(bool enabled) override;
    /*public*/ bool isEnabled();
    /*public*/ QString getNonSelectedItem();
    /*public*/ void setNonSelectedItem(QString itemText);
  QObject* self() override{return (QObject*)this;}

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

 protected:
/*protected*/ void fireSelectedRosterEntriesPropertyChange(QObject* oldValue, QObject* newValue);

};

#endif // ROSTERENTRYSELECTORPANEL_H
