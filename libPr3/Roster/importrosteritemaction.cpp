#include "importrosteritemaction.h"
#include "jmripanel.h"
#include "fileutil.h"
#include "locofile.h"
#include <QFile>
#include "file.h"

ImportRosterItemAction::ImportRosterItemAction(QObject *parent) :
  AbstractRosterItemAction(tr("Import Roster"), (WindowInterface*)parent)
{
 log = new Logger("ImportRosterItemAction");
}
/**
 * Import a locomotive XML file as a new RosterEntry.
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
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <P>
 * @author	Bob Jacobsen Copyright (C) 2001, 2002
 * @version	$Revision: 29336 $
 * @see jmri.jmrit.roster.AbstractRosterItemAction
 * @see jmri.jmrit.XmlFile
 */
// /*public*/ class ImportRosterItemAction extends AbstractRosterItemAction {

/**
 *
 */
//private static final long serialVersionUID = 7656609516525647086L;

/*public*/ ImportRosterItemAction::ImportRosterItemAction(QString s, WindowInterface* wi) :
  AbstractRosterItemAction(s, wi) {
    //super(s, wi);
 log = new Logger("ImportRosterItemAction");
}

/*public*/ ImportRosterItemAction::ImportRosterItemAction(QString s, QIcon i, WindowInterface* wi) :
  AbstractRosterItemAction(s,i,wi) {
    //super(s, i, wi);
 log = new Logger("ImportRosterItemAction");
}

/*public*/ ImportRosterItemAction::ImportRosterItemAction(QString pName, QWidget* pWho) :
  AbstractRosterItemAction(pName, pWho) {
    //super(pName, pWho);
 log = new Logger("ImportRosterItemAction");
}

//@Override
/*protected*/ bool ImportRosterItemAction::selectFrom()
{
 return AbstractRosterItemAction::selectNewFromFile();
}

//@Override
bool ImportRosterItemAction::selectTo()
{
 return AbstractRosterItemAction::selectNewToEntryID();
}

//@Override
bool ImportRosterItemAction::doTransfer()
{
 // read the file for the "from" entry, create a new entry, write it out
 // ensure preferences will be found for read
 FileUtil::createDirectory(LocoFile::getFileLocation());

 // read it
 LocoFile* lf = new LocoFile();  // used as a temporary
 QDomElement lroot;
 try {
     lroot = lf->rootFromFile(mFromFile).cloneNode().toElement();
 } catch (Exception* e) {
     log->error("Exception while loading loco XML file: " + mFullFromFilename + " exception: " + e->getMessage());
     return false;
 }

 return loadEntryFromElement(lroot);
}

/*protected*/ bool ImportRosterItemAction::loadEntryFromElement(QDomElement lroot) {
    // create a new entry from XML info - find the element
    QDomElement loco = lroot.firstChildElement("locomotive");
    mToEntry = new RosterEntry(loco);

    // set the filename from the ID
    mToEntry->setId(mToID);
    mToEntry->setFileName(""); // to force recreation
    mToEntry->ensureFilenameExists();

    // transfer the contents to a new file
    LocoFile* newLocoFile = new LocoFile();
    QFile* fout = new QFile(LocoFile::getFileLocation() + mToEntry->getFileName());
    newLocoFile->writeFile(fout, lroot, mToEntry);

    return true;
}

// never invoked, because we overrode actionPerformed above
//@Override
/*public*/ JmriPanel* ImportRosterItemAction::makePanel()
{
    throw new IllegalArgumentException("Should not be invoked");
}
