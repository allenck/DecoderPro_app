#include "consistfile.h"
#include "instancemanager.h"
#include "consistmanager.h"
#include "roster.h"
#include "fileutil.h"
#include "loggerfactory.h"
#include "rosterconfigmanager.h"
/**
 * Handle saving/restoring consist information to XML files. This class
 * manipulates files conforming to the consist-roster-config DTD.
 *
 * @author Paul Bender Copyright (C) 2008
 */
// /*public*/ class ConsistFile extends XmlFile {


/*public*/ ConsistFile::ConsistFile() {
    //super();
    consistMan = NULL;

    consistMan = qobject_cast<AbstractConsistManager*>(InstanceManager::getDefault("ConsistManager"));
    // set the location to a subdirectory of the defined roster
    // directory
    setFileLocation(Roster::getDefault()->getRosterLocation() + "roster" + File::separator + "consist");
    Roster::getDefault()->addPropertyChangeListener((PropertyChangeListener*)this);}
#if 0
/**
 * Load a Consist from the consist elements in the file.
 *
 * @param consist a JDOM element containing a consist
 */
@SuppressWarnings("unchecked")
/*private*/ void consistFromXml(QDomElement consist) {
    Attribute type, cnumber, isCLong, cID;
    Consist newConsist;

    // Read the consist address from the file and create the
    // consisit in memory if it doesn't exist already.
    cnumber = consist->getAttribute("consistNumber");
    isCLong = consist->getAttribute("longAddress");
    DccLocoAddress consistAddress;
    if (isCLong != NULL) {
        log->debug("adding consist {} with longAddress set to {}.", cnumber, isCLong.getValue());
        try {
            int number = Integer.parseInt(cnumber.getValue());
            consistAddress = new DccLocoAddress(number, isCLong.getValue().equals("yes"));
        } catch (NumberFormatException e) {
            log->debug("Consist number not an integer");
            return;
        }

    } else {
        log->debug("adding consist {} with default long address setting.", cnumber);
        consistAddress = new DccLocoAddress(
                Integer.parseInt(cnumber.getValue()),
                false);
    }
    newConsist = consistMan.getConsist(consistAddress);
    if (!(newConsist.getConsistList().isEmpty())) {
        log->debug("Consist {} is not empty.  Using version in memory.", consistAddress.toString());
        return;
    }

    // read and set the consist type
    type = consist->getAttribute("type");
    if (type != NULL) {
        // use the value read from the file
        newConsist.setConsistType((type.getValue().equals("CSAC")) ? Consist.CS_CONSIST : Consist.ADVANCED_CONSIST);
    } else {
        // use the default (DAC)
        newConsist.setConsistType(Consist.ADVANCED_CONSIST);
    }

    // Read the consist ID from the file;
    cID = consist->getAttribute("id");
    if (cID != NULL) {
        // use the value read from the file
        newConsist.setConsistID(cID.getValue());
    }

    // read each child of locomotive in the consist from the file
    // and restore it's information to memory.
    Iterator<Element> childIterator = consist->getDescendants(doc.createElementFilter("loco"));
    try {
        QDomElement e;
        do {
            e = childIterator.next();
            Attribute number, isLong, direction, position,rosterId;
            number = e.getAttribute("dccLocoAddress");
            isLong = e.getAttribute("longAddress");
            direction = e.getAttribute("locoDir");
            position = e.getAttribute("locoName");
            rosterId = e.getAttribute("locoRosterId");
            log->debug("adding Loco {}", number);
            // Use restore so we DO NOT cause send any commands
            // to the command station as we recreate the consist->
            DccLocoAddress address;
            if (isLong != NULL && direction != NULL) {
                // use the values from the file
                log->debug("using direction from file {}", direction.getValue());
                address = new DccLocoAddress(
                        Integer.parseInt(number.getValue()),
                        isLong.getValue().equals("yes"));
                newConsist.restore(address,
                        direction.getValue().equals("normal"));
            } else if (isLong == NULL && direction != NULL) {
                // use the direction from the file
                // but set as long address
                log->debug("using direction from file {}", direction.getValue());
                address = new DccLocoAddress(
                        Integer.parseInt(number.getValue()),
                        true);
                newConsist.restore(address,
                        direction.getValue().equals("normal"));
            } else if (isLong != NULL && direction == NULL) {
                // use the default direction
                // but the long/short value from the file
                address = new DccLocoAddress(
                        Integer.parseInt(number.getValue()),
                        isLong.getValue().equals("yes"));
                newConsist.restore(address, true);
            } else {
                // use the default values long address
                // and normal direction
                address = new DccLocoAddress(
                        Integer.parseInt(number.getValue()),
                        true);
                newConsist.restore(address, true);
            }
            if (position != NULL && !position.getValue().equals("mid")) {
                if (position.getValue().equals("lead")) {
                    newConsist.setPosition(address, Consist.POSITION_LEAD);
                } else if (position.getValue().equals("rear")) {
                    newConsist.setPosition(address, Consist.POSITION_TRAIL);
                }
            } else {
                Attribute midNumber = e.getAttribute("locoMidNumber");
                if (midNumber != NULL) {
                    int pos = Integer.parseInt(midNumber.getValue());
                    newConsist.setPosition(address, pos);
                }
            }
            if( rosterId != NULL ){
              newConsist.setRosterId(address,rosterId.getValue());
            }
        } while (true);
    } catch (NoSuchElementException nse) {
        log->debug("end of loco list");
    }
}
#endif
/**
 * convert a Consist to XML.
 *
 * @param consist a Consist object to write to the file
 * @return an QDomElement representing the consist->
 */
/*private*/ QDomElement ConsistFile::consistToXml(DccConsist* consist) {
    QDomElement e = doc.createElement("consist");
    e.setAttribute("id", consist->getConsistID());
    e.setAttribute("consistNumber", "" + consist->getConsistAddress()
            ->getNumber());
    e.setAttribute("longAddress", consist->getConsistAddress()
            ->isLongAddress() ? "yes" : "no");
    e.setAttribute("type", consist->getConsistType() == Consist::ADVANCED_CONSIST ? "DAC" : "CSAC");
    QList<DccLocoAddress*> addressList = consist->getConsistList();

    for (int i = 0; i < addressList.size(); i++) {
        DccLocoAddress* locoaddress = addressList.value(i);
        QDomElement eng = doc.createElement("loco");
        eng.setAttribute("dccLocoAddress", "" + locoaddress->getNumber());
        eng.setAttribute("longAddress", locoaddress->isLongAddress() ? "yes" : "no");
        eng.setAttribute("locoDir", consist->getLocoDirection(locoaddress) ? "normal" : "reverse");
        int position = consist->getPosition(locoaddress);
        if (position == Consist::POSITION_LEAD) {
            eng.setAttribute("locoName", "lead");
        } else if (position == Consist::POSITION_TRAIL) {
            eng.setAttribute("locoName", "rear");
        } else {
            eng.setAttribute("locoName", "mid");
            eng.setAttribute("locoMidNumber", "" + position);
        }
        QString rosterId = consist->getRosterId(locoaddress);
        if(rosterId!=NULL){
            eng.setAttribute("locoRosterId",rosterId);
        }
        e.appendChild(eng);
    }
    return (e);
}

/**
 * Read all consists from the default file name
 *
 */
/*public*/ void ConsistFile::readFile() throw (JDOMException, IOException) {
    readFile(defaultConsistFilename());
}

/**
 * Read all consists from a file.
 *
 * @param fileName - with location and file type
 */
//@SuppressWarnings("unchecked")
/*public*/ void ConsistFile::readFile(QString fileName) throw (JDOMException, IOException) {
    if (checkFile(fileName)) {
        QDomElement root = rootFromName(fileName);
        QDomElement roster;
        if (root == QDomElement()) {
            log->warn("consist file could not be read");
            return;
        }
        roster = root.firstChildElement("roster");
        if (roster == QDomElement()) {
            log->debug("consist file does not contain a roster entry");
            return;
        }
#if 0 // TODO
        Iterator<Element> consistIterator = root.getDescendants(doc.createElementFilter("consist"));
        try {
            QDomElement consist;
            do {
                consist = consistIterator.next();
                consistFromXml(consist);
            } while ( consistIterator.hasNext() );
        } catch (NoSuchElementException nde) {
            log->debug("end of consist list");
        }
#endif
    } else {
        log->info("Consist file does not exist.  One will be created if necessary.");
    }

}

/**
 * Write all consists to the default file name
 *
 */
/*public*/ void ConsistFile::writeFile(QList<DccLocoAddress *> consistList) throw (IOException) {
    writeFile(consistList, defaultConsistFilename());
}

/**
 * Write all consists to a file.
 *
 * @param consistList an ArrayList of consists to write
 * @param fileName    - with location and file type
 */
/*public*/ void ConsistFile::writeFile(QList<DccLocoAddress *> consistList, QString fileName) throw (IOException) {
    // create root element
#if 1
 if(consistList.isEmpty())
  throw IOException("consist list is empty!");
 QDomDocument doc = QDomDocument();
    QDomElement root = doc.createElement("consist-roster-config");
    //QDomDocument doc = newDocument(root, dtdLocation + "consist-roster-config.dtd");
    QDomProcessingInstruction dtd = doc.createProcessingInstruction("consist-roster-config", dtdLocation + "consist-roster-config.dtd");
    doc.appendChild(dtd);

    // add XSLT processing instruction
//    QMap<QString, QString> m = QMap<QString, QString>();
//    m.insert("type", "text/xsl");
//    m.insert("href", xsltLocation + "consistRoster.xsl");
//    ProcessingInstruction p = new ProcessingInstruction("xml-stylesheet", m);
    //QDomProcessingInstruction p = doc.createProcessingInstruction("text/xsl", "/xml/XSLT/panelfile-2-9-6.xsl");

    QDomProcessingInstruction p = doc.createProcessingInstruction("xml-stylesheet","type=\"text/xsl\" href=\"xsltLocation + \"consistRoster.xsl\"");
    doc.appendChild(p);
    doc.appendChild(root);

    QDomElement roster = doc.createElement("roster");

    for (int i = 0; i < consistList.size(); i++) {
        DccConsist* newConsist = consistMan->getConsist(consistList.value(i));
        roster.appendChild(consistToXml(newConsist));
    }
    root.appendChild(roster);
    try {
        if (!checkFile(fileName)) {
            //The file does not exist, create it before writing
            File* file = new File(fileName);
            File* parentDir = file->getParentFile();
            if (!parentDir->exists()) {
                if (!parentDir->mkdir()) {
                    throw (IOException());
                }
            }
            if (!file->createNewFile()) {
                throw (IOException());
            }
        }
        writeXML(findFile(fileName), doc);
    } catch (IOException ioe) {
        log->error("IO Exception " + ioe.getMessage());
        throw (ioe);
    }
#endif
}
/**
 * Defines the preferences subdirectory in which LocoFiles are kept by
 * default.
 */
/*static*/ /*private*/ QString ConsistFile::fileLocation = FileUtil::getUserFilesPath() + "roster" + File::separator + "consist";

/*static*/ /*public*/ QString ConsistFile::getFileLocation() {
    return fileLocation;
}

/*static*/ /*public*/ void ConsistFile::setFileLocation(QString loc) {
    fileLocation = loc;
    if (!fileLocation.endsWith(File::separator)) {
        fileLocation = fileLocation + File::separator;
    }
}

/**
 * Return the filename String for the default Consist file, including
 * location.
 */
/*public*/ /*static*/ QString ConsistFile::defaultConsistFilename() {
    return getFileLocation() + "consist->xml";
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void ConsistFile::propertyChange(PropertyChangeEvent* evt) {
    if (qobject_cast<Roster*>(evt->getSource()) &&
        evt->getPropertyName()== (RosterConfigManager::DIRECTORY)) {
        try {
            this->writeFile(consistMan->getConsistList()->toList());
        } catch (IOException ioe) {
            log->error("Unable to write consist information to new consist folder");
        }
    }
}
// initialize logging
/*private*/ /*final*/ /*static*/ Logger* ConsistFile::log = LoggerFactory::getLogger("ConsistFile");
