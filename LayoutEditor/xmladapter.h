#ifndef XMLADAPTER_H
#define XMLADAPTER_H

#include <QObject>
#include <QtXml>
#include "exceptions.h"
#include "configxmlmanager.h"
#include "level.h"
#include "liblayouteditor_global.h"
#include "dialogerrorhandler.h"

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
 /*public*/ virtual bool loadDeferred()const =0;
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
    /*public*/ virtual void load(QDomElement /*e*/, QObject* /*o*/) throw (Exception) =0;

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
 /*public*/ virtual void load(QDomElement /*shared*/, QDomElement /*perNode*/, QObject* /*o*/) throw (JmriConfigureXmlException) {}

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

/*public*/ virtual int loadOrder() const =0;

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
QT_DEPRECATED/*public*/ virtual void creationErrorEncountered (
            QString description,
            QString systemName,
            QString userName,
            Exception* exception
        ) /*throw (JmriConfigureXmlException)*/
 {
  this->handleException(description, nullptr, systemName, userName, exception);
 }

 /**
      * Provide a simple handler for errors.
      *
      * Calls the configured {@link jmri.configurexml.ErrorHandler} with an
      * {@link jmri.configurexml.ErrorMemo} created using the provided
      * parameters.
      *
      * @param description description of error encountered
      * @param operation   the operation being performed, may be null
      * @param systemName  system name of bean being handled, may be null
      * @param userName    user name of the bean being handled, may be null
      * @param exception   Any exception being handled in the processing, may be
      *                    null
      * @throws JmriConfigureXmlException in place for later expansion; should be
      *                                   propagated upward to higher-level error
      *                                   handling
      */
      virtual/*public*/ void handleException(
             /*@Nonnull*/ QString /*description*/,
             /*@Nullable*/ QString /*operation*/,
             /*@Nullable*/ QString /*systemName*/,
             /*@Nullable*/ QString /*userName*/,
             /*@Nullable*/ Exception* /*exception*/)  { }/*throws JmriConfigureXmlException*/

     /**
      * Set the error handler that will handle any errors encountered while
      * parsing the XML. If not specified, the default error handler will be
      * used.
      *
      * @param errorHandler the error handler or null to ignore parser errors
      */
     /*public*/ void setExceptionHandler(ErrorHandler* errorHandler);

     /**
      * Get the current error handler.
      *
      * @return the error handler or null if no error handler is assigned
      */
     /*public*/ ErrorHandler* getExceptionHandler();

     /**
      * Get the default error handler.
      *
      * @return the default error handler
      */
     /*public*/ static ErrorHandler* getDefaultExceptionHandler() {
//         if (GraphicsEnvironment.isHeadless()) {
//             return new ErrorHandler();
//         }
         return new DialogErrorHandler();
     }
    /*public*/ virtual void setConfigXmlManager(ConfigXmlManager* /*c*/) {}
    friend class PanelEditorXml;
    friend class AbstractSignalHeadManagerXml;
    friend class ControlPanelEditorXml;
};
#endif // XMLADAPTER_H
