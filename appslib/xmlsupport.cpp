#include "xmlsupport.h"
#include "exceptions.h"
#include <QMessageBox>
#include "preferences.h"
#include "abstractpreferences.h"
#include "transformerfactory.h"

XmlSupport::XmlSupport(QObject *parent) : QObject(parent)
{

}
/**
 * XML Support for java.util.prefs. Methods to import and export preference
 * nodes and subtrees.
 *
 * @author  Josh Bloch and Mark Reinhold
 * @see     Preferences
 * @since   1.4
 */
//class XmlSupport {
    // The required DTD URI for exported preferences
/*private*/ /*static*/ /*final*/ QString XmlSupport::PREFS_DTD_URI =
    "http://java.sun.com/dtd/preferences.dtd";

// The actual DTD corresponding to the URI
/*private*/ /*static*/ /*final*/ QString XmlSupport::PREFS_DTD =
    QString("<?xml version=\"1.0\" encoding=\"UTF-8\"?>") +

    "<!-- DTD for preferences -->"               +

    "<!ELEMENT preferences (root) >"             +
    "<!ATTLIST preferences"                      +
    " EXTERNAL_XML_VERSION CDATA \"0.0\"  >"     +

    "<!ELEMENT root (map, node*) >"              +
    "<!ATTLIST root"                             +
    "          type (system|user) #REQUIRED >"   +

    "<!ELEMENT node (map, node*) >"              +
    "<!ATTLIST node"                             +
    "          name CDATA #REQUIRED >"           +

    "<!ELEMENT map (entry*) >"                   +
    "<!ATTLIST map"                              +
    "  MAP_XML_VERSION CDATA \"0.0\"  >"         +
    "<!ELEMENT entry EMPTY >"                    +
    "<!ATTLIST entry"                            +
    "          key CDATA #REQUIRED"              +
    "          value CDATA #REQUIRED >"          ;
/**
 * Version number for the format exported preferences files.
 */
/*private*/ /*static*/ /*final*/ QString XmlSupport::EXTERNAL_XML_VERSION = "1.0";

/*
 * Version number for the internal map files.
 */
/*private*/ /*static*/ /*final*/ QString XmlSupport::MAP_XML_VERSION = "1.0";

/**
 * Export the specified preferences node and, if subTree is true, all
 * subnodes, to the specified output stream.  Preferences are exported as
 * an XML document conforming to the definition in the Preferences spec.
 *
 * @throws IOException if writing to the specified output stream
 *         results in an <tt>IOException</tt>.
 * @throws BackingStoreException if preference data cannot be read from
 *         backing store.
 * @throws IllegalStateException if this node (or an ancestor) has been
 *         removed with the {@link Preferences#removeNode()} method.
 */
/*static*/ void XmlSupport::_export(QTextStream* os, /*final*/ Preferences* p, bool subTree)
    throw (IOException, BackingStoreException)
{
    if (((AbstractPreferences*)p)->isRemoved())
        throw new IllegalStateException("Node has been removed");
    QDomDocument doc = /*createPrefsDoc*/QDomDocument("preferences");
    QDomElement preferences =  doc.documentElement() ;
    preferences.setAttribute("EXTERNAL_XML_VERSION", EXTERNAL_XML_VERSION);
    QDomElement xmlRoot =  preferences.appendChild(doc.createElement("root")).toElement();
    xmlRoot.setAttribute("type", (p->isUserNode() ? "user" : "system"));

    // Get bottom-up list of nodes from p to root, excluding root
    QList<Preferences*> ancestors = QList<Preferences*>();

    for (Preferences* kid = p, *dad = kid->parent(); dad != NULL;
                               kid = dad, dad = kid->parent())
    {
        ancestors.append(kid);
    }
    QDomElement e = xmlRoot;
    for (int i=ancestors.size()-1; i >= 0; i--) {
        e.appendChild(doc.createElement("map"));
        e = e.appendChild(doc.createElement("node")).toElement();
        e.setAttribute("name", ancestors.at(i)->name());
    }
    putPreferencesInXml(e, doc, p, subTree);

    writeDoc(doc, os);
}

/**
 * Put the preferences in the specified Preferences node into the
 * specified XML element which is assumed to represent a node
 * in the specified XML document which is assumed to conform to
 * PREFS_DTD.  If subTree is true, create children of the specified
 * XML node conforming to all of the children of the specified
 * Preferences node and recurse.
 *
 * @throws BackingStoreException if it is not possible to read
 *         the preferences or children out of the specified
 *         preferences node.
 */
/*private*/ /*static*/ void XmlSupport::putPreferencesInXml(QDomElement elt, QDomDocument doc,
           Preferences* prefs, bool subTree) throw (BackingStoreException)
{
    QList<Preferences*> kidsCopy = QList<Preferences*>();
    QStringList kidNames =QStringList();

    // Node is locked to export its contents and get a
    // copy of children, then lock is released,
    // and, if subTree = true, recursive calls are made on children
    /*synchronized (((AbstractPreferences)prefs).lock)*/ {
        // Check if this node was concurrently removed. If yes
        // remove it from XML Document and return.
        if (((AbstractPreferences*)prefs)->isRemoved()) {
            elt.parentNode().removeChild(elt);
            return;
        }
        // Put map in xml element
        QStringList keys = prefs->keys();
        QDomElement map =  elt.appendChild(doc.createElement("map")).toElement();
        for (int i=0; i<keys.length(); i++) {
            QDomElement entry =
                map.appendChild(doc.createElement("entry")).toElement();
            entry.setAttribute("key", keys[i]);
            // NEXT STATEMENT THROWS NULL PTR EXC INSTEAD OF ASSERT FAIL
            entry.setAttribute("value", prefs->get(keys.at(i), NULL));
        }
        // Recurse if appropriate
        if (subTree) {
            /* Get a copy of kids while lock is held */
            kidNames = prefs->childrenNames();
            kidsCopy = QVector<Preferences*>(kidNames.length()).toList();
            for (int i = 0; i <  kidNames.length(); i++)
                kidsCopy.replace(i, prefs->node(kidNames.at(i)));
        }
        // release lock
    }

    if (subTree) {
        for (int i=0; i < kidNames.length(); i++) {
            QDomElement xmlKid =
                elt.appendChild(doc.createElement("node")).toElement();
            xmlKid.setAttribute("name", kidNames.at(i));
            putPreferencesInXml(xmlKid, doc, kidsCopy.at(i), subTree);
        }
    }
}

/**
 * Import preferences from the specified input stream, which is assumed
 * to contain an XML document in the format described in the Preferences
 * spec.
 *
 * @throws IOException if reading from the specified output stream
 *         results in an <tt>IOException</tt>.
 * @throws InvalidPreferencesFormatException Data on input stream does not
 *         constitute a valid XML document with the mandated document type.
 */
/*static*/ void XmlSupport::importPreferences(QTextStream* is)
    //throws IOException, InvalidPreferencesFormatException
{
//    try {
        QDomDocument doc = loadPrefsDoc(is);
        QString xmlVersion =
            doc.documentElement().attribute("EXTERNAL_XML_VERSION");
        if (xmlVersion.compare(EXTERNAL_XML_VERSION) > 0)
            //throw new InvalidPreferencesFormatException(
         QMessageBox::critical(NULL, tr("error"),
            "Exported preferences file format version " + xmlVersion +
            " is not supported. This java installation can read" +
            " versions " + EXTERNAL_XML_VERSION + " or older. You may need" +
            " to install a newer version of JDK.");

        QDomElement xmlRoot =  doc.documentElement().childNodes().at(0).toElement();

        Preferences* prefsRoot =
            (xmlRoot.attribute("type")==("user") ?
                        Preferences::userRoot() : Preferences::systemRoot());
        ImportSubtree(prefsRoot, xmlRoot);
//    } catch(SAXException e) {
//        throw new InvalidPreferencesFormatException(e);
//    }
}
#if 0
/**
 * Create a new prefs XML document.
 */
/*private*/ static Document createPrefsDoc( String qname ) {
    try {
        DOMImplementation di = DocumentBuilderFactory.newInstance().
            newDocumentBuilder().getDOMImplementation();
        DocumentType dt = di.createDocumentType(qname, NULL, PREFS_DTD_URI);
        return di.createDocument(NULL, qname, dt);
    } catch(ParserConfigurationException e) {
        throw new AssertionError(e);
    }
}
#endif
/**
 * Load an XML document from specified input stream, which must
 * have the requisite DTD URI.
 */
/*private*/ /*static*/ QDomDocument XmlSupport::loadPrefsDoc(QTextStream* in)
    //throws SAXException, IOException
{
#if 0
    DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
    dbf.setIgnoringElementContentWhitespace(true);
    dbf.setValidating(true);
    dbf.setCoalescing(true);
    dbf.setIgnoringComments(true);
    try {
        DocumentBuilder db = dbf.newDocumentBuilder();
        db.setEntityResolver(new Resolver());
        db.setErrorHandler(new EH());
        return db.parse(new InputSource(in));
    } catch (ParserConfigurationException e) {
        throw new AssertionError(e);
    }
#endif
    QDomDocument doc;
    doc.setContent(in->device());
    return doc;
}

/**
 * Write XML document to the specified output stream.
 */
/*private*/ /*static*/ /*final*/ void XmlSupport::writeDoc(QDomDocument doc, QTextStream* out)
    throw (IOException)
{
#if 0
    try {
        TransformerFactory* tf = TransformerFactory::newInstance();
        try {
            tf->setAttribute("indent-number", new Integer(2));
        } catch (IllegalArgumentException iae) {
            //Ignore the IAE. Should not fail the writeout even the
            //transformer provider does not support "indent-number".
        }
        Transformer t = tf.newTransformer();
        t.setOutputProperty(OutputKeys.DOCTYPE_SYSTEM, doc.getDoctype().getSystemId());
        t.setOutputProperty(OutputKeys.INDENT, "yes");
        //Transformer resets the "indent" info if the "result" is a StreamResult with
        //an OutputStream object embedded, creating a Writer object on top of that
        //OutputStream object however works.
        t.transform(new DOMSource(doc),
                    new StreamResult(new BufferedWriter(new OutputStreamWriter(out, "UTF-8"))));
    } catch(TransformerException e) {
        throw new AssertionError(e);
    }
#endif
 out->setCodec("UTF-8");
 //QString sXml = doc.toString();
 doc.save(*out, 2);
}

/**
 * Recursively traverse the specified preferences node and store
 * the described preferences into the system or current user
 * preferences tree, as appropriate.
 */
/*private*/ /*static*/ void XmlSupport::ImportSubtree(Preferences* prefsNode, QDomElement xmlNode) {
    QDomNodeList xmlKids = xmlNode.childNodes();
    int numXmlKids = xmlKids.length();
    /*
     * We first lock the node, import its contents and get
     * child nodes. Then we unlock the node and go to children
     * Since some of the children might have been concurrently
     * deleted we check for this.
     */
    QVector<Preferences*> prefsKids;
    /* Lock the node */
//    /*synchronized*/ (((AbstractPreferences*)prefsNode)->lock)
    {
        //If removed, return silently
        if (((AbstractPreferences*)prefsNode)->isRemoved())
            return;

        // Import any preferences at this node
        QDomElement firstXmlKid =  xmlKids.item(0).toElement();
        ImportPrefs(prefsNode, firstXmlKid);
        prefsKids = QVector<Preferences*>(numXmlKids - 1);

        // Get involved children
        for (int i=1; i < numXmlKids; i++) {
            QDomElement xmlKid =  xmlKids.item(i).toElement();
            prefsKids.replace(i-1, prefsNode->node(xmlKid.attribute("name")));
        }
    } // unlocked the node
    // import children
    for (int i=1; i < numXmlKids; i++)
        ImportSubtree(prefsKids[i-1], xmlKids.item(i).toElement());
}

/**
 * Import the preferences described by the specified XML element
 * (a map from a preferences document) into the specified
 * preferences node.
 */
/*private*/ /*static*/ void XmlSupport::ImportPrefs(Preferences* prefsNode, QDomElement map) {
    QDomNodeList entries = map.childNodes();
    for (int i=0, numEntries = entries.length(); i < numEntries; i++) {
        QDomElement entry = entries.item(i).toElement();
        prefsNode->put(entry.attribute("key"),
                      entry.attribute("value"));
    }
}
#if 0
/**
 * Export the specified Map<String,String> to a map document on
 * the specified OutputStream as per the prefs DTD.  This is used
 * as the internal (undocumented) format for FileSystemPrefs.
 *
 * @throws IOException if writing to the specified output stream
 *         results in an <tt>IOException</tt>.
 */
static void exportMap(OutputStream os, Map<String, String> map) throws IOException {
    Document doc = createPrefsDoc("map");
    QDomElement xmlMap = doc.getDocumentElement( ) ;
    xmlMap.setAttribute("MAP_XML_VERSION", MAP_XML_VERSION);

    for (Iterator<Map.Entry<String, String>> i = map.entrySet().iterator(); i.hasNext(); ) {
        Map.Entry<String, String> e = i.next();
        QDomElement xe = (Element)
            xmlMap.appendChild(doc.createElement("entry"));
        xe.setAttribute("key",   e.getKey());
        xe.setAttribute("value", e.getValue());
    }

    writeDoc(doc, os);
}

/**
 * Import Map from the specified input stream, which is assumed
 * to contain a map document as per the prefs DTD.  This is used
 * as the internal (undocumented) format for FileSystemPrefs.  The
 * key-value pairs specified in the XML document will be put into
 * the specified Map.  (If this Map is empty, it will contain exactly
 * the key-value pairs int the XML-document when this method returns.)
 *
 * @throws IOException if reading from the specified output stream
 *         results in an <tt>IOException</tt>.
 * @throws InvalidPreferencesFormatException Data on input stream does not
 *         constitute a valid XML document with the mandated document type.
 */
static void importMap(InputStream is, Map<String, String> m)
    throws IOException, InvalidPreferencesFormatException
{
    try {
        Document doc = loadPrefsDoc(is);
        QDomElement xmlMap = doc.getDocumentElement();
        // check version
        String mapVersion = xmlMap.getAttribute("MAP_XML_VERSION");
        if (mapVersion.compareTo(MAP_XML_VERSION) > 0)
            throw new InvalidPreferencesFormatException(
            "Preferences map file format version " + mapVersion +
            " is not supported. This java installation can read" +
            " versions " + MAP_XML_VERSION + " or older. You may need" +
            " to install a newer version of JDK.");

        NodeList entries = xmlMap.getChildNodes();
        for (int i=0, numEntries=entries.getLength(); i<numEntries; i++) {
            QDomElement entry = (Element) entries.item(i);
            m.put(entry.getAttribute("key"), entry.getAttribute("value"));
        }
    } catch(SAXException e) {
        throw new InvalidPreferencesFormatException(e);
    }
}

/*private*/ static class Resolver implements EntityResolver {
    /*public*/ InputSource resolveEntity(String pid, String sid)
        throws SAXException
    {
        if (sid==(PREFS_DTD_URI)) {
            InputSource is;
            is = new InputSource(new StringReader(PREFS_DTD));
            is.setSystemId(PREFS_DTD_URI);
            return is;
        }
        throw new SAXException("Invalid system identifier: " + sid);
    }
}

/*private*/ static class EH implements ErrorHandler {
    /*public*/ void error(SAXParseException x) throws SAXException {
        throw x;
    }
    /*public*/ void fatalError(SAXParseException x) throws SAXException {
        throw x;
    }
    /*public*/ void warning(SAXParseException x) throws SAXException {
        throw x;
    }
}
#endif
