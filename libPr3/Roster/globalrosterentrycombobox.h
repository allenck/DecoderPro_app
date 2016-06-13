#ifndef GLOBALROSTERENTRYCOMBOBOX_H
#define GLOBALROSTERENTRYCOMBOBOX_H
#include "rosterentrycombobox.h"

class GlobalRosterEntryComboBox : public RosterEntryComboBox
{
    Q_OBJECT
public:
    explicit GlobalRosterEntryComboBox(QWidget *parent = 0);
    /*public*/ GlobalRosterEntryComboBox(Roster* roster, QWidget* parent = 0);
    GlobalRosterEntryComboBox(QString roadName,
            QString roadNumber,
            QString dccAddress,
            QString mfg,
            QString decoderMfgID,
            QString decoderVersionID,
            QString id, QWidget* parent = 0);
    /*public*/ GlobalRosterEntryComboBox(Roster* roster,
            QString roadName,
            QString roadNumber,
            QString dccAddress,
            QString mfg,
            QString decoderMfgID,
            QString decoderVersionID,
            QString id, QWidget* parent = 0);
    /*public*/ void update();
    /*public*/ void update(QString roadName,
                           QString roadNumber,
                           QString dccAddress,
                           QString mfg,
                           QString decoderMfgID,
                           QString decoderVersionID,
                           QString id);

signals:

public slots:

};

#endif // GLOBALROSTERENTRYCOMBOBOX_H
