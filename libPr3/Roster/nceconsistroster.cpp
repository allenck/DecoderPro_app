#include "nceconsistroster.h"
#include "nceconsistrosterentry.h"
#include <QComboBox>
#include <rosterentry.h> // for VPtr
#include "roster.h"
#include "instancemanager.h"
#include "file.h"


NceConsistRoster::NceConsistRoster(QObject *parent) :
    XmlFile(parent)
{
 log = new Logger("NceConsistRoster");
 _list =  QList<NceConsistRosterEntry*>();
dirty = false;
setProperty("InstanceManagerAutoDefault", "true");
setProperty("InstanceManagerAutoInitialize", "true");

}
/**
 * NCE Consist Roster manages and manipulates a roster of consists.
 * <P>
 * It works with the "consist-roster-config" XML DTD to load and store its
 * information.
 * <P>
 * This is an in-memory representation of the roster xml file (see below for
 * constants defining name and location). As such, this class is also
 * responsible for the "dirty bit" handling to ensure it gets written. As a
 * temporary reliability enhancement, all changes to this structure are now
 * being written to a backup file, and a copy is made when the file is opened.
 * <P>
 * Multiple Roster objects don't make sense, so we use an "instance" member to
 * navigate to a single one.
 * <P>
 * This predates the "XmlFile" base class, so doesn't use it. Not sure whether
 * it should...
 * <P>
 * The only bound property is the list of s; a PropertyChangedEvent is fired
 * every time that changes.
 * <P>
 * The entries are stored in an ArrayList, sorted alphabetically. That sort is
 * done manually each time an entry is added.
 *
 * @author Bob Jacobsen Copyright (C) 2001; Dennis Miller Copyright 2004
 * @author Daniel Boudreau (C) 2008
 * @version $Revision: 17977 $
 * @see NceConsistRosterEntry
 */
// /*public*/ class NceConsistRoster extends XmlFile {

/** record the single instance of Roster **/
///*private*/ /*static*/ NceConsistRoster* NceConsistRoster::_instance = NULL;

///*public*/ /*synchronized*/ /*static*/ void NceConsistRoster::resetInstance() { _instance = NULL; }

/**
 * @return The NCE consist roster object
 * @deprecated JMRI Since 4.4 instance() shouldn't be used, convert to JMRI multi-system support structure
 */
//@Deprecated
/*public*/ /*static*/ /*synchronized*/ NceConsistRoster* NceConsistRoster::instance()
{
 return static_cast<NceConsistRoster*>(InstanceManager::getDefault("NceConsistRoster"));
}

/**
 * Add a RosterEntry object to the in-memory Roster.
 * @param e Entry to add
 */
/*public*/ void NceConsistRoster::addEntry(NceConsistRosterEntry* e) {
    if (log->isDebugEnabled()) log->debug("Add entry "+e->toString());
    int i = _list.size()-1;// Last valid index
    while (i>=0) {
        // compareToIgnoreCase not present in Java 1.1.8
        if (e->getId().toUpper().compare(_list.at(i)->getId().toUpper()) > 0 )
            break; // I can never remember whether I want break or continue here
        i--;
    }
    _list.insert(i+1, e);
    setDirty(true);
    //firePropertyChange("add", NULL, e);
    emit propertyChange(new PropertyChangeEvent(this, "add", QVariant(), VPtr<NceConsistRosterEntry>::asQVariant(e)));
}

/**
 * Remove a RosterEntry object from the in-memory Roster.  This
 * does not delete the file for the RosterEntry!
 * @param e Entry to remove
 */
/*public*/ void NceConsistRoster::removeEntry(NceConsistRosterEntry* e) {
    if (log->isDebugEnabled()) log->debug("Remove entry "+e->toString());
    _list.removeAt(_list.indexOf(e));
    setDirty(true);
    //firePropertyChange("remove", QVariant(), e);
    emit propertyChange(new PropertyChangeEvent(this, "remove", QVariant(), VPtr<NceConsistRosterEntry>::asQVariant(e)));

}

/**
 * @return Number of entries in the Roster
 */
/*public*/ int NceConsistRoster::numEntries() { return _list.size(); }

/**
 * Return a combo box containing the entire ConsistRoster.
 * <P>
 * This is based on a single model, so it can be updated
 * when the ConsistRoster changes.
 *
 */
/*public*/ QComboBox* NceConsistRoster::fullRosterComboBox() {
    return matchingComboBox(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}

/**
 * Get a JComboBox representing the choices that match.
 * There's 10 elements.
 */
/*public*/ QComboBox* NceConsistRoster::matchingComboBox(QString roadName, QString roadNumber,
        QString consistNumber, QString eng1Address, QString eng2Address,
        QString eng3Address, QString eng4Address, QString eng5Address,
        QString eng6Address, QString id) {
    QList<NceConsistRosterEntry*> l = matchingList(roadName, roadNumber, consistNumber, eng1Address,
            eng2Address, eng3Address, eng4Address, eng5Address,
            eng6Address, id);
    QComboBox* b = new QComboBox();
    for (int i = 0; i < l.size(); i++) {
        NceConsistRosterEntry* r = _list.at(i);
        b->addItem(r->titleString());
    }
    return b;
}

/*public*/ void NceConsistRoster::updateComboBox(QComboBox* box) {
   QList<NceConsistRosterEntry*> l = matchingList(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    box->clear();
    for (int i = 0; i < l.size(); i++) {
        NceConsistRosterEntry* r = _list.at(i);
        box->addItem(r->titleString());
    }
}

/**
 * Return RosterEntry from a "title" string, ala selection in matchingComboBox
 */
/*public*/ NceConsistRosterEntry* NceConsistRoster::entryFromTitle(QString title ) {
    for (int i = 0; i < numEntries(); i++) {
        NceConsistRosterEntry* r = _list.at(i);
        if (r->titleString()==(title)) return r;
    }
    return NULL;
}


/**
 *	Get a List of entries matching some information. The list may have
 *  NULL contents.
 */
/*public*/ QList<NceConsistRosterEntry*> NceConsistRoster::matchingList(QString roadName, QString roadNumber,
        QString consistNumber, QString eng1Address, QString eng2Address,
        QString eng3Address, QString eng4Address, QString eng5Address,
        QString eng6Address, QString id) {
    QList<NceConsistRosterEntry*> l =  QList<NceConsistRosterEntry*>();
    for (int i = 0; i < numEntries(); i++)
    {
        if (checkEntry(i, roadName, roadNumber, consistNumber, eng1Address,
                eng2Address, eng3Address, eng4Address, eng5Address,
                eng6Address, id))
            l.append(_list.at(i));
    }
    return l;
}

/**
 * Check if an entry consistent with specific properties. A NULL String
 * entry always matches. Strings are used for convenience in GUI building.
 *
 */
/*public*/ bool NceConsistRoster::checkEntry(int i, QString roadName, QString roadNumber,
        QString consistNumber, QString loco1Address, QString loco2Address,
        QString loco3Address, QString loco4Address, QString loco5Address,
        QString loco6Address, QString id ) {
    NceConsistRosterEntry* r = _list.at(i);
    if (id != "" && id!=(r->getId())) return false;
    if (roadName != NULL && roadName!=(r->getRoadName())) return false;
    if (roadNumber != NULL && roadNumber!=(r->getRoadNumber())) return false;
    if (consistNumber != NULL && consistNumber!=(r->getConsistNumber())) return false;
    if (loco1Address != NULL && loco1Address!=(r->getLoco1DccAddress())) return false;
    if (loco2Address != NULL && loco2Address!=(r->getLoco2DccAddress())) return false;
    if (loco3Address != NULL && loco3Address!=(r->getLoco3DccAddress())) return false;
    if (loco4Address != NULL && loco4Address!=(r->getLoco4DccAddress())) return false;
    if (loco5Address != NULL && loco5Address!=(r->getLoco5DccAddress())) return false;
    if (loco6Address != NULL && loco6Address!=(r->getLoco6DccAddress())) return false;
    return true;
}

/**
 * Write the entire roster to a file. This does not do backup; that has
 * to be done separately. See writeRosterFile() for a function that
 * finds the default location, does a backup and then calls this.
 * @param name Filename for new file, including path info as needed.
 * @throws IOException
 */
void NceConsistRoster::writeFile(QString name) throw (FileNotFoundException, IOException)
{
 if (log->isDebugEnabled()) log->debug("writeFile "+name);
 // This is taken in large part from "Java and XML" page 368
 QFile* file = findFile(name)->toQfile();
 if (file == NULL)
 {
  file = new QFile(name);
 }
    // create root element
    //QDomDocument doc;
    //QDomDocument doc = newDocument(root, dtdLocation+"consist-roster-config.dtd");

//    // add XSLT processing instruction
//    QMap<QString, QString> m =  QMap<QString, QString>();
//    m.insert("type", "text/xsl");
//    m.insert("href", xsltLocation+"consistRoster.xsl");
//    QDomProcessingInstruction p = new QDomProcessingInstruction("xml-stylesheet", m);
//    doc.appendhild(0,p);
 QDomProcessingInstruction xmlProcessingInstruction = doc.createProcessingInstruction("xml", "version=\"1.0\"  encoding=\"UTF-8\"");
 doc.appendChild(xmlProcessingInstruction);
 xmlProcessingInstruction = doc.createProcessingInstruction("xml-stylesheet", "type=\"text/xsl\" href=\"/xml/XSLT/roster2array.xsl\"");
 doc.appendChild(xmlProcessingInstruction);
 QDomElement root = doc.createElement("consist-roster-config");

    //Check the Comment and Decoder Comment fields for line breaks and
    //convert them to a processor directive for storage in XML
    //Note: this is also done in the LocoFile.java class to do
    //the same thing in the indidvidual locomotive roster files
    //Note: these changes have to be undone after writing the file
    //since the memory version of the roster is being changed to the
 //file version for writing
 for (int i=0; i<numEntries(); i++)
 {

  //Extract the RosterEntry at this index and inspect the Comment and
  //Decoder Comment fields to change any \n characters to <?p?> processor
  //directives so they can be stored in the xml file and converted
  //back when the file is read.
  NceConsistRosterEntry* r = _list.at(i);
  QString tempComment = r->getComment();
  QString buf;// = new StringBuffer();

  //transfer tempComment to xmlComment one character at a time, except
  //when \n is found.  In that case, insert <?p?>
  for (int k = 0; k < tempComment.length(); k++)
  {
   //if (tempComment.startsWith("\n", k))
   if(tempComment.mid(k).startsWith("\n"))
   {
    buf.append("<?p?>");
   }
   else
   {
    buf.append(tempComment.mid(k, k + 1));
   }
  }
  r->setComment(buf/*.toString()*/);
 }
 //All Comments and Decoder Comment line feeds have been changed to processor directives


 // add top-level elements
 QDomElement values;
 root.appendChild(values = doc.createElement("roster"));
 // add entries
 for (int i=0; i<numEntries(); i++)
 {
  values.appendChild(_list.at(i)->store(doc));
 }
 writeXML(file, doc);

 //Now that the roster has been rewritten in file form we need to
 //restore the RosterEntry object to its normal \n state for the
    //Comment and Decoder comment fields, otherwise it can cause problems in
 //other parts of the program (e.g. in copying a roster)
 for (int i=0; i<numEntries(); i++)
 {
  NceConsistRosterEntry* r = _list.at(i);
  QString xmlComment = r->getComment();
  QString buf;// = new StringBuffer();

  for (int k = 0; k < xmlComment.length(); k++)
  {
   //if (xmlComment.startsWith("<?p?>", k))
   if(xmlComment.mid(k).startsWith("<?p?>"))
   {
                buf.append("\n");
                k = k + 4;
            }
            else {
                 buf.append(xmlComment.mid(k, k + 1));
            }
        }
        r->setComment(buf/*.toString()*/);

    }

    // done - roster now stored, so can't be dirty
    setDirty(false);
}

/**
 * Read the contents of a roster XML file into this object. Note that this does not
 * clear any existing entries.
 */
//@SuppressWarnings("unchecked")
void NceConsistRoster::readFile(QString name) throw (JDOMException, IOException) {
    // find root
    doc = QDomDocument("consist-roster-config");
    QDomElement root = doc.documentElement();
    if (root==QDomElement()) {
        log->debug("ConsistRoster file could not be read");
        return;
    }
    //if (log->isDebugEnabled()) XmlFile.dumpElement(root);

    // decode type, invoke proper processing routine if a decoder file
    if (root.firstChildElement("roster") != QDomElement()) {
        QDomNodeList l = root.firstChildElement("roster").elementsByTagName("consist");
        if (log->isDebugEnabled()) log->debug("readFile sees "+QString::number(l.size())+" children");
        for (int i=0; i<l.size(); i++) {
            addEntry(new NceConsistRosterEntry(l.at(i).toElement()));
        }

        //Scan the object to check the Comment and Decoder Comment fields for
        //any <?p?> processor directives and change them to back \n characters
        for (int i = 0; i < numEntries(); i++) {
            //Get a RosterEntry object for this index
            NceConsistRosterEntry* r = _list.at(i);

            //Extract the Comment field and create a new string for output
            QString tempComment = r->getComment();
            QString buf;// = new StringBuffer();

            //transfer tempComment to xmlComment one character at a time, except
            //when <?p?> is found.  In that case, insert a \n and skip over those
            //characters in tempComment.
            for (int k = 0; k < tempComment.length(); k++)
            {
                //if (tempComment.startsWith("<?p?>", k))
                if(tempComment.mid(k).startsWith("<?p?>"))
                {
                    buf.append("\n");
                    k = k + 4;
                }
                else {
                    buf.append(tempComment.mid(k, k + 1));
                }
            }
            r->setComment(buf/*.toString()*/);
        }


    }
    else {
        log->error("Unrecognized ConsistRoster file contents in file: "+name);
    }
}

void NceConsistRoster::setDirty(bool b) {dirty = b;}
bool NceConsistRoster::isDirty() {return dirty;}

/*public*/ void NceConsistRoster::dispose() {
    if (log->isDebugEnabled()) log->debug("dispose");
    if (dirty) log->error("Dispose invoked on dirty ConsistRoster");
}

/**
 * Store the roster in the default place, including making a backup if needed
 */
/*public*/ void NceConsistRoster::writeRosterFile() {
    makeBackupFile(defaultNceConsistRosterFilename());
    try {
        writeFile(defaultNceConsistRosterFilename());
    } catch (Exception e) {
        Logger::error("Exception while writing the new ConsistRoster file, may not be complete: "+e.getMessage());
    }
}

/**
 * update the in-memory Roster to be consistent with
 * the current roster file.  This removes the existing roster entries!
 */

/*public*/ void NceConsistRoster::reloadRosterFile() {
    // clear existing
    _list.clear();
    // and read new
    try {
        readFile(defaultNceConsistRosterFilename());
    } catch (Exception e) {
        log->error("Exception during ConsistRoster reading: "+e.getMessage());
    }
}


/**
 * Return the filename String for the default ConsistRoster file, including location.
 */
/*public*/ /*static*/ QString NceConsistRoster::defaultNceConsistRosterFilename() { return Roster::getDefault()->getRosterLocation()+NceConsistRosterFileName;}

/*public*/ /*static*/ void NceConsistRoster::setNceConsistRosterFileName(QString name) { NceConsistRosterFileName = name; }
/*private*/ /*static*/ QString NceConsistRoster::NceConsistRosterFileName = "ConsistRoster.xml";

// since we can't do a "super(this)" in the ctor to inherit from PropertyChangeSupport, we'll
// reflect to it.
// Note that dispose() doesn't act on these.  Its not clear whether it should...
//java.beans.PropertyChangeSupport pcs = new java.beans.PropertyChangeSupport(this);

///*public*/ synchronized void addPropertyChangeListener(java.beans.PropertyChangeListener l) {
//    pcs.addPropertyChangeListener(l);
//}

/*protected*/ void NceConsistRoster::firePropertyChange(QString p, QVariant old, QVariant n) {
    //pcs.firePropertyChange(p,old,n);
    emit propertyChange(new PropertyChangeEvent(this, p, old, n));
}

///*public*/ synchronized void removePropertyChangeListener(java.beans.PropertyChangeListener l) {
//    pcs.removePropertyChangeListener(l);
//}

/**
 * Notify that the ID of an entry has changed.  This doesn't actually change the
 * ConsistRoster per se, but triggers recreation.
 */
/*public*/ void NceConsistRoster::entryIdChanged(NceConsistRosterEntry* r)
{
 log->debug("EntryIdChanged");

 // order may be wrong! Sort
 QList<NceConsistRosterEntry*> rarray =  QList<NceConsistRosterEntry*>();
 for (int i=0; i<rarray.length(); i++) rarray.append( _list.at(i));
 //TODO:   jmri.util.StringUtil.sortUpperCase(rarray);
 for (int i=0; i<rarray.length(); i++)
        _list.replace(i,rarray[i]);

    firePropertyChange("change", QVariant(), VPtr<NceConsistRosterEntry>::asQVariant(r));
}

//@Override
/*public*/ void NceConsistRoster::initialize()
{
    if (checkFile(defaultNceConsistRosterFilename()))
    {
     try
     {
            readFile(defaultNceConsistRosterFilename());
     } catch (IOException  e) {
      log->error(tr("Exception during ConsistRoster reading: %1").arg(e.getMessage()));
     }
     catch ( JDOMException e) {
      log->error(tr("Exception during ConsistRoster reading: %1").arg(e.getMessage()));
    }
  }
}
