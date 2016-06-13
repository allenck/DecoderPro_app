#ifndef ROSTERENTRYCOMBOBOX_H
#define ROSTERENTRYCOMBOBOX_H

#include <QComboBox>
#include "rosterentryselector.h"
#include "roster.h"

class LIBPR3SHARED_EXPORT RosterEntryComboBox : public QComboBox //, public RosterEntrySelector
{
    Q_OBJECT
public:
    explicit RosterEntryComboBox(QWidget *parent = 0);
    /*public*/ RosterEntryComboBox(Roster* roster, QWidget *parent = 0);
    /*public*/ RosterEntryComboBox(QString rosterGroup, QWidget *parent = 0);
    /*public*/ RosterEntryComboBox(Roster* roster, QString rosterGroup, QWidget *parent = 0);
    /*public*/ RosterEntryComboBox(QString roadName,
            QString roadNumber,
            QString dccAddress,
            QString mfg,
            QString decoderMfgID,
            QString decoderVersionID,
            QString id, QWidget *parent = 0);
    /*public*/ RosterEntryComboBox(Roster* roster,
            QString roadName,
            QString roadNumber,
            QString dccAddress,
            QString mfg,
            QString decoderMfgID,
            QString decoderVersionID,
            QString id, QWidget *parent = 0);
    /*public*/ RosterEntryComboBox(QString rosterGroup,
            QString roadName,
            QString roadNumber,
            QString dccAddress,
            QString mfg,
            QString decoderMfgID,
            QString decoderVersionID,
            QString id, QWidget *parent = 0);
    /*public*/ RosterEntryComboBox(Roster* roster,
                QString rosterGroup,
                QString roadName,
                QString roadNumber,
                QString dccAddress,
                QString mfg,
                QString decoderMfgID,
                QString decoderVersionID,
                QString id, QWidget *parent = 0);
    /*public*/ void update();
    /*public*/ /*final*/ void update(QString rosterGroup);
    /*public*/ void update(QString roadName,
                           QString roadNumber,
                           QString dccAddress,
                           QString mfg,
                           QString decoderMfgID,
                           QString decoderVersionID,
                           QString id);
    /*public*/ /*final*/ void update(QString rosterGroup,
            QString roadName,
            QString roadNumber,
            QString dccAddress,
            QString mfg,
            QString decoderMfgID,
            QString decoderVersionID,
            QString id);
    /*public*/ void setNonSelectedItem(QString itemText);
    /*public*/ QString getNonSelectedItem();
    /*public*/ QList<RosterEntry*> * getSelectedRosterEntries();
    static /*final*/ QString SELECTED_ROSTER_ENTRIES;// = "selectedRosterEntries";

signals:
    void propertyChange(QString, QList<RosterEntry*> *, QList<RosterEntry*> *);
    
public slots:
    void on_currentIndexChanged(QString text);
    /*public*/ void propertyChange(PropertyChangeEvent* pce);

private:
 Logger log;
protected:
/*protected*/ Roster* _roster;
/*protected*/ QString _group;
/*protected*/ QString _roadName;
/*protected*/ QString _roadNumber;
/*protected*/ QString _dccAddress;
/*protected*/ QString _mfg;
/*protected*/ QString _decoderMfgID;
/*protected*/ QString _decoderVersionID;
/*protected*/ QString _id;
/*protected*/ QString _nonSelectedItem;// = "Select Loco";
/*protected*/ QList<RosterEntry*>* _currentSelection;// = NULL;
/*protected*/ void fireSelectedRosterEntriesPropertyChange();
 /*protected*/ QList<RosterEntry*> * getSelectedRosterEntries(bool force);

};

#endif // ROSTERENTRYCOMBOBOX_H
