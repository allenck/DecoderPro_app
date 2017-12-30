#include "globalrosterentrycombobox.h"

//GlobalRosterEntryComboBox::GlobalRosterEntryComboBox(QWidget *parent) :
//    RosterEntryComboBox(parent)
//{
//}
/**
 * A {@link RosterEntryComboBox} that lists all roster entries in the Roster
 * without respect to a roster group.
 *
 * @author Randall Wood Copyright (C) 2011
 * @version $Revision: $
 * @see RosterEntryComboBox
 */
// /*public*/ class GlobalRosterEntryComboBox extends RosterEntryComboBox {

/**
 * Create a combo box with all roster entries in the default Roster::
 */
/*public*/ GlobalRosterEntryComboBox::GlobalRosterEntryComboBox(QWidget *parent) :
        RosterEntryComboBox(Roster::instance(), Roster::ALLENTRIES, NULL, NULL, NULL, NULL, NULL, NULL, NULL, parent)
{
    //super(Roster::instance(), Roster::_ALLENTRIES, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}

/**
 * Create a combo box with all roster entries in an arbitrary Roster::
 * @param roster
 */
/*public*/ GlobalRosterEntryComboBox::GlobalRosterEntryComboBox(Roster* roster, QWidget *parent) : RosterEntryComboBox(roster, Roster::ALLENTRIES, NULL, NULL, NULL, NULL, NULL, NULL, NULL, parent)
{
    //super(roster, Roster::_ALLENTRIES, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}

/**
 * Create a combo box with roster entries in the default Roster matching the
 * specified attributes.
 *
 * @param roadName
 * @param roadNumber
 * @param dccAddress
 * @param mfg
 * @param decoderMfgID
 * @param decoderVersionID
 * @param id
 */
/*public*/ GlobalRosterEntryComboBox::GlobalRosterEntryComboBox(QString roadName,
        QString roadNumber,
        QString dccAddress,
        QString mfg,
        QString decoderMfgID,
        QString decoderVersionID,
        QString id, QWidget* parent) :
    RosterEntryComboBox(Roster::instance(),
            Roster::ALLENTRIES,
            roadName,
            roadNumber,
            dccAddress,
            mfg,
            decoderMfgID,
            decoderVersionID,
            id, parent)
{
}

/**
 * Create a combo box with roster entries in an arbitrary Roster matching
 * the specified attributes.
 *
 * @param roster
 * @param roadName
 * @param roadNumber
 * @param dccAddress
 * @param mfg
 * @param decoderMfgID
 * @param decoderVersionID
 * @param id
 */
/*public*/ GlobalRosterEntryComboBox::GlobalRosterEntryComboBox(Roster* roster,
        QString roadName,
        QString roadNumber,
        QString dccAddress,
        QString mfg,
        QString decoderMfgID,
        QString decoderVersionID,
        QString id, QWidget* parent) :
    RosterEntryComboBox(roster,
            Roster::ALLENTRIES,
            roadName,
            roadNumber,
            dccAddress,
            mfg,
            decoderMfgID,
            decoderVersionID,
            id, parent)
{
}

//@Override
/*public*/ void GlobalRosterEntryComboBox::update()
{
    RosterEntryComboBox::update(Roster::ALLENTRIES,
            _roadName,
            _roadNumber,
            _dccAddress,
            _mfg,
            _decoderMfgID,
            _decoderVersionID,
            _id);
}

//@Override
/*public*/ void GlobalRosterEntryComboBox::update(QString roadName,
        QString roadNumber,
        QString dccAddress,
        QString mfg,
        QString decoderMfgID,
        QString decoderVersionID,
        QString id)
{
    RosterEntryComboBox::update(Roster::ALLENTRIES,
            roadName,
            roadNumber,
            dccAddress,
            mfg,
            decoderMfgID,
            decoderVersionID,
            id);
}
