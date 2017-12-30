#ifndef XMLADAPTER_H
#define XMLADAPTER_H
#include <QObject>
#include <QtXml>
#include "exceptions.h"
#include "configxmlmanager.h"
#include "level.h"
#include "liblayouteditor_global.h"

/**
 * Interface assumed during configuration operations.
 *
 * @author Bob Jacobsen  Copyright (c) 2002
 * @version $Revision: 18102 $
 * @see ConfigXmlManager
 */
class ConfigXmlManager;
/*public*/ /*interface*/ class LIBLAYOUTEDITORSHARED_EXPORT XmlAdapter : public QObject {
    Q_OBJECT
public:
    /**
     * Create a set of configured objects from their
     * XML description
     * @param e Top-level XML element containing the description
     * @throws Exception when a error prevents creating the objects as
     *          as required by the input XML.
     * @return true if successful
     */
    /*public*/ virtual bool load(QDomElement /*e*/) throw (Exception) { return false;}

    /**
      * Create a set of configured objects from their XML description.
      *
      * @param shared  Top-level XML element containing the common, multi-node
      *                elements of the description
      * @param perNode Top-level XML element containing the private, single-node
      *                elements of the description
      * @throws Exception when a error prevents creating the objects as as
      *                   required by the input XML.
      * @return true if successful
      */
     /*public*/ virtual bool load(QDomElement /*shared*/, QDomElement /*perNode*/)  {return false;} //throws Exception;

 /**
     * Determine if this set of configured objects should
     * be loaded after basic GUI construction is completed
     * @return true to defer loading
     * @since 2.11.2
     */
    /*public*/ virtual bool loadDeferred() {return false;}

    /**
     * Create a set of configured objects from their
     * XML description, using an auxiliary object.
     * <P>
     * For example, the auxilary object o might be a manager or GUI of some type
     * that needs to be informed as each object is created.
     *
     * @param e Top-level XML element containing the description
     * @param o Implementation-specific Object needed for the conversion
     * @throws Exception when a error prevents creating the objects as
     *          as required by the input XML.
     */
    /*public*/ virtual void load(QDomElement /*e*/, QObject* /*o*/) throw (Exception) {}

 /**
      * Create a set of configured objects from their XML description, using an
      * auxiliary object.
      * <P>
      * For example, the auxilary object o might be a manager or GUI of some type
      * that needs to be informed as each object is created.
      *
      * @param shared  Top-level XML element containing the common description
      * @param perNode Top-level XML element containing the per-node description
      * @param o       Implementation-specific Object needed for the conversion
      * @throws Exception when a error prevents creating the objects as as
      *                   required by the input XML.
      */
     /*public*/ virtual void load(QDomElement /*shared*/, QDomElement /*perNode*/, QObject* /*o*/) {} //throws Exception;

 /**
     * Store the
     * @param o The object to be recorded.  Specific XmlAdapter
     *          implementations will require this to be of a specific
     *          type; that binding is done in ConfigXmlManager.
     * @return The XML representation QDomElement
     */
    /*public*/ virtual QDomElement store(QObject* o)
    {
     Q_UNUSED(o)
     return QDomElement();
    }

/**
  * Store the object in XML
  *
  * @param o      The object to be recorded. Specific XmlAdapter
  *               implementations will require this to be of a specific type;
  *               that binding is done in ConfigXmlManager.
  * @param shared true if the returned element should be the common XML and
  *               false if the returned element should be per-node.
  * @return The XML representation Element
  */
 /*public*/ virtual QDomElement store(QObject* o, bool shared)
 {
  if (shared)
  {
     return store(o);
  }
  return QDomElement();
 }

 /*public*/ virtual int loadOrder() { return 0;}

    /**
     * Invoke common handling of errors that
     * happen during the "load" process.
     *
     * This is part of the interface to ensure that
     * all the necessary classes provide it; eventually
     * it will be coupled to a reporting mechanism of some
     * sort.
     *
     * @param description description of error encountered
     * @param systemName System name of bean being handled, may be null
     * @param userName used name of the bean being handled, may be null
     * @param exception Any exception being handled in the processing, may be null
     * @throws JmriConfigureXmlException in place for later expansion;
     *         should be propagated upward to higher-level error handling
     */
    /*public*/ virtual void creationErrorEncountered (
                Level* /*level*/,
                QString /*description*/,
                QString /*systemName*/,
                QString /*userName*/,
                Throwable* /*exception*/
            ) throw (JmriConfigureXmlException) {}

    /*public*/ virtual void setConfigXmlManager(ConfigXmlManager* /*c*/) {}
    friend class PanelEditorXml;
    friend class AbstractSignalHeadManagerXml;
    friend class ControlPanelEditorXml;
};
#endif // XMLADAPTER_H
