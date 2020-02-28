#include "filehistoryxml.h"
#include "instancemanager.h"

FileHistoryXml::FileHistoryXml(QObject *parent) :
  AbstractXmlAdapter(parent)
{
}
/**
 * Load/Store FileHistory objects.
 * <p>
 * This interacts somewhat differently with the ConfigureXML system. FileHistory
 * objects are _not_ registed with the manager, but rather handled explicitly by
 * them. The "load()" method is therefore a null-op here.
 *
 * @author Bob Jacobsen Copyright (c) 2010
 * @version $Revision: 28771 $
 */
// /*public*/ class FileHistoryXml extends jmri.configurexml.AbstractXmlAdapter {

/**
 * Usual configurexml method, this one doesn't do anything because the
 * content is explicitly loaded from the file
 */
/*public*/ bool FileHistoryXml::load(QDomElement e) throw (Exception) {
    return true;
}

/**
 * Load RevHistory from an element.
 *
 * <p>
 * If no RevHistory already present in InstanceManager, creates one and adds
 * this.
 * <P>
 * Then adds, instead of replacing, the history information
 */
/*public*/ bool FileHistoryXml::loadDirectly(QDomElement e) throw (Exception)
{
 if (e.tagName() != ("filehistory"))
 {
  throw Exception("Unexpected element name: " + e.tagName());
 }

 FileHistory* rmain = (FileHistory*)InstanceManager::getDefault("FileHistory");

 FileHistory* r = loadFileHistory(e);
 rmain->addOperation("Load", "", r);

 return true;
}

/*static*/ /*public*/ FileHistory* FileHistoryXml::loadFileHistory(QDomElement e)
{
 FileHistory* r = new FileHistory();

 QDomNodeList list = e.elementsByTagName("operation");
 for (int i = 0; i < list.size(); i++) {
     loadOperation(r, list.at(i).toElement());
 }
 return r;
}

/*static*/ /*public*/ void FileHistoryXml::loadOperation(FileHistory* r, QDomElement e)
{
 QDomElement s;

 QString type = "";
 s = e.firstChildElement("type");
 if (!s.isNull())
 {
  type = s.text();
 }

 QString date = "";
 s = e.firstChildElement("date");
 if (!s.isNull())
 {
  date = s.text();
 }

 QString filename = "";
 s = e.firstChildElement("filename");
 if (!s.isNull())
 {
  filename = s.text();
 }

 FileHistory* filehistory = NULL;
 s = e.firstChildElement("filehistory");
 if (!s.isNull())
 {
  filehistory = loadFileHistory(s);
 }

 r->addOperation(type, date, filename, filehistory);
}

/**
 * Create a set of configured objects from their XML description, using an
 * auxiliary object.
 * <P>
 * For example, the auxilary object o might be a manager or GUI of some type
 * that needs to be informed as each object is created.
 *
 * @param e Top-level XML element containing the description
 * @param o Implementation-specific Object needed for the conversion
 * @throws Exception when a error prevents creating the objects as as
 *                   required by the input XML.
 */
/*public*/ void FileHistoryXml::load(QDomElement /*e*/, QObject* /*o*/) throw (Exception) {
    throw new Exception("Method not coded");
}

/**
 * Store the
 *
 * @param o The object to be recorded. Specific XmlAdapter implementations
 *          will require this to be of a specific type; that binding is done
 *          in ConfigXmlManager.
 * @return The XML representation Element
 */
/*public*/ QDomElement FileHistoryXml::store(QObject* o) {
    return storeDirectly(o,doc);
}

/*static*/ int FileHistoryXml::defaultDepth = 5;

/*static*/ /*public*/ QDomElement FileHistoryXml::storeDirectly(QObject* o, QDomDocument doc)
{
 /*final*/ FileHistory* r = (FileHistory*) o;
 if (r == NULL)
 {
  return QDomElement();  // no file history object, not recording
 }
 QDomElement e = historyElement(r, defaultDepth, doc);

//    // add one more element for this store
//    FileHistory::OperationMemo rev
//            = r->new OperationMemo() {
//                {
//                    type = "Store";
//                    date = (new java.util.Date()).toString();
//                    filename = "";
//                    history = null;
//                }
//            };

    e.appendChild(
            operationElement(new MyOperationMemo, 10, doc));
//    );
 // and return
 return e;
}

MyOperationMemo::MyOperationMemo()
{
 type = "Store";
 date = QDateTime::currentDateTime().toString();
 filename = "";
 history = NULL;
}

/*static*/ QDomElement FileHistoryXml::historyElement(FileHistory* r, int depth, QDomDocument doc)
{
 QList<FileHistory::OperationMemo*> list = r->getList();

 QDomElement e = doc.createElement("filehistory");

 for (int i = 0; i < list.size(); i++)
 {
  QDomElement operation = operationElement(list.at(i), depth, doc);
  e.appendChild(operation);
 }

 return e;
}

/*static*/ QDomElement FileHistoryXml::operationElement(FileHistory::OperationMemo* r, int depth, QDomDocument doc)
{
 QDomElement rev = doc.createElement("operation");

 QDomElement revnumber = doc.createElement("type");
 revnumber.appendChild(doc.createTextNode(r->type));
 rev.appendChild(revnumber);

 QDomElement date = doc.createElement("date");
 date.appendChild(doc.createTextNode(r->date));
 rev.appendChild(date);

 QDomElement authorinitials = doc.createElement("filename");
 authorinitials.appendChild(doc.createTextNode(r->filename));
 rev.appendChild(authorinitials);

 if (r->history != NULL && depth >= 1)
 {
  rev.appendChild(historyElement(r->history, depth - 1, doc));
 }

 return rev;
}
