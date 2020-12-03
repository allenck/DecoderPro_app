#include "abstractxmladapter.h"
#include "errormemo.h"
#include "loggerfactory.h"

AbstractXmlAdapter::AbstractXmlAdapter(QObject *parent)
 :    XmlAdapter()
{
 this->parent = parent;
 doc = QDomDocument();
 errorHandler = XmlAdapter::getDefaultExceptionHandler();
}
/**
 * Abstract class to provide basic error handling for XmlAdapter
 *
 * @author Bob Jacobsen  Copyright (c) 2009
 * @version $Revision: 18102 $
 * @see XmlAdapter
 */

//public abstract class AbstractXmlAdapter implements XmlAdapter {
    
/**
 * Provide common handling of errors that
 * happen during the "load" process.
 *
 * Simple implementation just sends message to
 * standard logging; needs to be given a plug-in
 * structure for e.g. posting a Swing dialog, etc.
 *
 * @param description description of error encountered
 * @param systemName System name of bean being handled, may be NULL
 * @param userName used name of the bean being handled, may be NULL
 * @param exception Any exception being handled in the processing, may be NULL
 * @throws JmriConfigureXmlException in place for later expansion;
 *         should be propagated upward to higher-level error handling
 */
/*public*/ void AbstractXmlAdapter::handleException (
            QString description,
            QString systemName,
            QString operation,
            QString userName,
            Exception* exception
        ) /*throw (JmriConfigureXmlException)*/
{
 if (errorHandler != nullptr)
 {
  this->errorHandler->handle(new ErrorMemo(this, operation, description, systemName, userName, exception));
 }
}

//@Override
/*public*/ bool AbstractXmlAdapter::load(QDomElement /*e*/) throw (Exception)
{
 throw new UnsupportedOperationException("One of the other load methods must be implemented.");
}

//@Override
/*public*/ bool AbstractXmlAdapter::load(QDomElement shared, QDomElement perNode) //throws Exception
{
 Q_UNUSED(perNode);
 return this->load(shared);
}

//@Override
/*public*/ void AbstractXmlAdapter::load(QDomElement shared, QDomElement /*perNode*/, QObject* o) throw (JmriConfigureXmlException)
{
 //this->load(shared, o);
}

/**
 * Determine if this set of configured objects should
 * be loaded after basic GUI construction is completed.
 * <p>
 * Default behaviour is to load when requested.
 * Classes that should wait until basic GUI is constructed
 * should override this method and return true
 * @return true to defer loading
 * @see jmri.configurexml.XmlAdapter#loadDeferred()
 * @since 2.11.2
 */
/*public*/ bool AbstractXmlAdapter::loadDeferred() const
{
 return false;
}

/**
* Used for determining which order to load items from XML files in.
*/
/*public*/ int AbstractXmlAdapter::loadOrder() const
{
 return 50;
}

/*public*/ void AbstractXmlAdapter::setConfigXmlManager(ConfigXmlManager* c) { this->c = c; }

/*protected*/ ConfigXmlManager* AbstractXmlAdapter::getConfigXmlManager() { return c; }

/** {@inheritDoc} */
//@Override
/*public*/ QDomElement AbstractXmlAdapter::store(/*@Nonnull*/ QObject* o, bool shared) {
    if (shared) {
        return XmlAdapter::store(o);
    }
    return QDomElement();
}

/** {@inheritDoc} */
//@Override
/*public*/ void AbstractXmlAdapter::setExceptionHandler(ErrorHandler* errorHandler) {
    this->errorHandler = errorHandler;
}

/** {@inheritDoc} */
//@Override
/*public*/ ErrorHandler* AbstractXmlAdapter::getExceptionHandler() {
    return this->errorHandler;
}

/**
 * Service method to handle attribute input of
 * boolean  (true/yes vs false/no) values.  Not being present
 * is not an error. Not parsing (which shouldn't happen due to
 * the XML Schema checks) invokes the default error handler.
 * @param element the element to parse.
 * @param name element attribute name.
 * @param def default value if name not present in element.
 * @return boolean value of attribute, else default if not present or error.
 */
 /*final*/ /*public*/ bool AbstractXmlAdapter::getAttributeBooleanValue(/*@Nonnull*/ QDomElement element, /*@Nonnull*/ QString name, bool def) {
    QString a;
    QString val = QString();
    try {
        a = element.attribute(name);
        if (a == "") return def;
        val = a/*.getValue()*/;
        if ( val == ("yes") || val == ("true") ) return true;  // non-externalized strings
        if ( val == ("no") || val == ("false") ) return false;
        return def;
    } catch (Exception ex) {
        log->debug("caught exception", ex);
        ErrorMemo* em = new ErrorMemo(this,
                                        "getAttributeBooleanValue threw exception",
                                        "element: "+element.tagName(),
                                        "attribute: "+name,
                                        "value: "+val,
                                        &ex);
        getExceptionHandler()->handle(em);
        return def;
    }
}

/**
 * Service method to handle attribute input of
 * integer values.  Not being present
 * is not an error. Not parsing (which shouldn't happen due to
 * the XML Schema checks) invokes the default error handler.
 * @param element the element to parse.
 * @param name element attribute name.
 * @param def default value if name not present in element.
 * @return integer value of attribute, else default if not present or error.
 */
/*final*/ /*public*/ int AbstractXmlAdapter::getAttributeIntegerValue(/*@Nonnull*/ QDomElement element, /*@Nonnull*/ QString name, int def) {
    QString a;
    QString val = QString();
    bool bok;
        a = element.attribute(name);
        if (a == "") return def;
        val = a/*.getValue()*/;
        return a.toInt(&bok);
    if(!bok) {
        log->debug("caught exception"/*, ex*/);
        ErrorMemo* em = new ErrorMemo(this,
                                        "getAttributeIntegerValue threw exception",
                                        "element: "+element.tagName(),
                                        "attribute: "+name,
                                        "value: "+val,
                                        new Throwable());
        getExceptionHandler()->handle(em);
        return def;
    }
}
#if 0
/**
 * Service method to handle attribute input of
 * double values.  Not being present
 * is not an error. Not parsing (which shouldn't happen due to
 * the XML Schema checks) invokes the default error handler.
 * @param element the element to parse.
 * @param name element attribute name.
 * @param def default value if name not present in element.
 * @return double value of attribute, else default if not present or error.
 */
final public double getAttributeDoubleValue(@Nonnull Element element, @Nonnull String name, double def) {
    Attribute a;
    String val = null;
    try {
        a = element.getAttribute(name);
        if (a == null) return def;
        val = a.getValue();
        return a.getDoubleValue();
    } catch (Exception ex) {
        log.debug("caught exception", ex);
        ErrorMemo em = new ErrorMemo(this,
                                        "getAttributeDoubleValue threw exception",
                                        "element: "+element.getName(),
                                        "attribute: "+name,
                                        "value: "+val,
                                        ex);
        getExceptionHandler().handle(em);
        return def;
    }
}

/**
 * Service method to handle attribute input of
 * float values.  Not being present
 * is not an error. Not parsing (which shouldn't happen due to
 * the XML Schema checks) invokes the default error handler.
 *
 * @param element the element to parse.
 * @param name element attribute name.
 * @param def default value if name not present in element.
 * @return float value of attribute, else default if not present or error.
 */
final public float getAttributeFloatValue(@Nonnull Element element, @Nonnull String name, float def) {
    Attribute a;
    String val = null;
    try {
        a = element.getAttribute(name);
        if (a == null) return def;
        val = a.getValue();
        return a.getFloatValue();
    } catch (Exception ex) {
        log.debug("caught exception", ex);
        ErrorMemo em = new ErrorMemo(this,
                                        "getAttributeFloatValue threw exception",
                                        "element: "+element.getName(),
                                        "attribute: "+name,
                                        "value: "+val,
                                        ex);
        getExceptionHandler().handle(em);
        return def;
    }
}
#endif
/*private*/ /*final*/ /*static*/ Logger* AbstractXmlAdapter::log = LoggerFactory::getLogger("AbstractXmlAdapter");
//}
void AbstractXmlAdapter::setDoc(QDomDocument doc) { this->doc = doc;}
