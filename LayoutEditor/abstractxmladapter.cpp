#include "abstractxmladapter.h"

AbstractXmlAdapter::AbstractXmlAdapter(QObject *parent)
 :    XmlAdapter()
{
 this->parent = parent;
 doc = QDomDocument();
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
/*public*/ void AbstractXmlAdapter::creationErrorEncountered (
            Level* level,
            QString description,
            QString systemName,
            QString userName,
            Throwable* exception
        ) throw (JmriConfigureXmlException)
{
    ConfigXmlManager::creationErrorEncountered(
            NULL, NULL,
            description, systemName, userName, exception
    );
}

//@Override
/*public*/ bool AbstractXmlAdapter::load(QDomElement /*e*/) throw (Exception)
{
    throw new UnsupportedOperationException("Either load(one of the other load methods must be implemented.");
}

//@Override
/*public*/ bool AbstractXmlAdapter::load(QDomElement shared, QDomElement /*perNode*/) //throws Exception
{
    return this->load(shared);
}

//@Override
/*public*/ void AbstractXmlAdapter::load(QDomElement shared, QDomElement /*perNode*/, QObject* o) //throws Exception
{
//    this->load(shared, o);
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
/*public*/ bool AbstractXmlAdapter::loadDeferred()
{
 return false;
}

/**
* Used for determining which order to load items from XML files in.
*/
/*public*/ int AbstractXmlAdapter::loadOrder()
{
 return 50;
}

/*public*/ void AbstractXmlAdapter::setConfigXmlManager(ConfigXmlManager* c) { this->c = c; }

/*protected*/ ConfigXmlManager* AbstractXmlAdapter::getConfigXmlManager() { return c; }



//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(AbstractXmlAdapter.class.getName());
//}
void AbstractXmlAdapter::setDoc(QDomDocument doc) { this->doc = doc;}
