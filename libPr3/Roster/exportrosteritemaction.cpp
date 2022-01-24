#include "exportrosteritemaction.h"
#include "jmripanel.h"
#include "fileutil.h"
#include "locofile.h"

//ExportRosterItemAction::ExportRosterItemAction(QObject *parent) :
//  AbstractRosterItemAction(parent)
//{
//}
/**
 * Export a roster element as a new definition file.
 * <P>
 * This creates the new file containing the entry, but does <b>not</b> add it to
 * the local {@link Roster} of locomotives. This is intended for making a
 * transportable copy of entry, which can be imported via
 * {@link ImportRosterItemAction} on another system.
 *
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU Gene ral Public License for more details.
 * <P>
 * @author	Bob Jacobsen Copyright (C) 2001, 2002
 * @version	$Revision: 28746 $
 * @see jmri.jmrit.roster.ImportRosterItemAction
 * @see jmri.jmrit.XmlFile
 */
///*public*/ class ExportRosterItemAction extends AbstractRosterItemAction {

/**
 *
 */
//private static final long serialVersionUID = -6157199339046481963L;

/*public*/ ExportRosterItemAction::ExportRosterItemAction(QString pName, QWidget* pWho) : AbstractRosterItemAction(pName, pWho)
{
 //super(pName, pWho);
  log = new Logger("ExportRosterItemAction");
}

//@Override
/*protected*/ bool ExportRosterItemAction::selectFrom() {
    return selectExistingFromEntry();
}

//@Override
bool ExportRosterItemAction::selectTo() {
    return selectNewToFile();
}

//@Override
bool ExportRosterItemAction::doTransfer() {

    // read the file for the "from" entry and write it out
    // ensure preferences will be found for read
    FileUtil::createDirectory(LocoFile::getFileLocation());

    // locate the file
    //File f = new File(mFullFromFilename);
    // read it
    LocoFile* lf = new LocoFile();  // used as a temporary
    QDomElement lroot;
    try {
        lroot = lf->rootFromName(mFullFromFilename).cloneNode().toElement();
    } catch (Exception* e) {
        log->error("Exception while loading loco XML file: " + mFullFromFilename + " exception: " + e->getMessage());
        return false;
    }

    // create a new entry
    mToEntry = new RosterEntry(mFromEntry, mFromID);

    // transfer the contents to the new file
    LocoFile* newLocoFile = new LocoFile();
    // File fout = new File(mFullToFilename);
    mToEntry->setFileName(mToFilename);
    mToEntry->setId(mFromEntry->getId());
    newLocoFile->writeFile(mToFile, lroot, mToEntry);

    return true;
}

//@Override
void ExportRosterItemAction::updateRoster() {
    // exported entry is NOT added to Roster
}
