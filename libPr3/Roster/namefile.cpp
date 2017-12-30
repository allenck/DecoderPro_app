#include "namefile.h"
#include <QSet>
NameFile::NameFile(QObject* parent) : XmlFile(parent)
{
 setObjectName("NameFile");
 _nameHash = new QHash<QString, QDomElement>();
 log = new Logger("NameFile");
}
// try to limit the JDOM to this class, so that others can manipulate...
/**
 * Represents a set of standard names and aliases in memory.
 * <P>
 * This class doesn't provide tools for defining the names {@literal &} aliases;
 * that's done manually, or at least not done here, to create the file.
 * <P>
 * Initially, we only need one of these, so we use an "instance" method to
 * locate the one associated with the "xml/names.xml" file.
 *
 * @author	Bob Jacobsen Copyright (C) 2001
 */
// /*public*/ class NameFile extends XmlFile {

// fill in abstract members
//protected List<Element> nameElementList = new ArrayList<Element>();
///*public*/ int numNames() { return nameElementList.size(); }
/*public*/ QSet<QString> NameFile::names() {
    //List<String> list = new ArrayList<String>();
    //for (int i = 0; i<nameElementList.size(); i++)
    //    list.add(nameElementList.get());
    return _nameHash->keys().toSet();
}


/*public*/ QDomElement NameFile::elementFromName(QString name) {
    return _nameHash->value(name);
}

/*static*/ NameFile* NameFile::_instance = NULL;

/*public*/ /*synchronized*/ /*static*/ NameFile* NameFile::instance() {
 Logger* log = new Logger("NameFile");
    if (_instance == NULL) {
        if (log->isDebugEnabled()) {
            log->debug("NameFile creating instance");
        }
        // create and load
        _instance = new NameFile();
        try {
            _instance->readFile(defaultNameFilename());
        } catch (Exception e) {
            log->error("Exception during name file reading: " + e.getMessage());
        }
    }
    if (log->isDebugEnabled()) {
        log->debug("NameFile returns instance " + _instance->objectName());
    }
    return _instance;
}

/**
 * Check to see if a name is present in the file
 */
/*public*/ bool NameFile::checkName(QString name) {
    return (elementFromName(name) != QDomElement());
}

/**
 * Read the contents of a NameFile XML file into this object. Note that this
 * does not clear any existing entries.
 */
void NameFile::readFile(QString name) throw (JDOMException,IOException) {
    if (log->isDebugEnabled()) {
        log->debug("readFile " + name);
    }

    // read file, find root
    QDomElement root = rootFromName(name);
    // decode type, invoke proper processing routine
    readNames(root);
}

void NameFile::readNames(QDomElement root) {

    QDomNodeList l = root.elementsByTagName("definition");
    if (log->isDebugEnabled()) {
        log->debug("readNames sees " + QString::number(l.size()) + " direct children");
    }
    for (int i = 0; i < l.size(); i++) {
        // handle each entry
        QDomElement el = l.at(i).toElement();
        storeDefinition(el);
    }
    // now recurse with "definitiongroup" children
    l = root.elementsByTagName("definitiongroup");
    if (log->isDebugEnabled()) {
        log->debug("readNames sees " + QString::number(l.size()) + " groups");
    }
    for (int i = 0; i < l.size(); i++) {
        // handle each entry
        QDomElement el = l.at(i).toElement();
        readNames(el);
    }

}

void NameFile::storeDefinition(QDomElement el) {
    QString name = el.attribute("item");
    _nameHash->insert(name, el);
}

/**
 * Return the filename String for the default file, including location. This
 * is here to allow easy override in tests.
 */
/*protected*/ /*static*/ QString NameFile::defaultNameFilename() {
    return fileLocation + nameFileName;
}

/*static*/ QString NameFile::fileLocation = "";
/*static*/ QString NameFile::nameFileName = "names.xml";
