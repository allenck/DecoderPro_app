#include "abstractnamedbeanmanagerconfigxml.h"
#include "manager.h"
#include "class.h"
#include "abstractmanager.h"

AbstractNamedBeanManagerConfigXML::AbstractNamedBeanManagerConfigXML(QObject *parent) :
    AbstractXmlAdapter(parent)
{
 log = new Logger("AbstractNamedBeanManagerConfigXML");
}
AbstractNamedBeanManagerConfigXML::~AbstractNamedBeanManagerConfigXML()
{
 delete log;
}

/**
 * Provides services for
 * configuring NamedBean manager storage.
 * <P>
 * Not a full abstract implementation by any means, rather
 * this class provides various common service routines
 * to eventual type-specific subclasses.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2009
 * @version $Revision: 19051 $
 * @since 2.3.1
 */
//public abstract class AbstractNamedBeanManagerConfigXML extends jmri.configurexml.AbstractXmlAdapter {

//public AbstractNamedBeanManagerConfigXML() {
//}

/**
 * Store common items:
 * <ul>
 * <li>user name
 * <li>comment
 * </ul>
 * @param t The NamedBean being stored
 * @param elem The JDOM element for storing the NamedBean
 */
/*protected*/ void AbstractNamedBeanManagerConfigXML::storeCommon(NamedBean* t, QDomElement elem) {
    storeUserName(t, elem);
    storeComment(t, elem);
    storeProperties(t, elem);
}

/**
 * Load common items:
 * <ul>
 * <li>comment
 * </ul>
 * The username is not loaded, because it
 * had to be provided in the ctor earlier.
 *
 * @param t The NamedBean being loaded
 * @param elem The JDOM element containing the NamedBean
 */
/*protected*/ void AbstractNamedBeanManagerConfigXML::loadCommon(NamedBean* t, QDomElement elem) {
    loadComment(t, elem);
    loadProperties(t, elem);
}

/**
 * Store the comment parameter from a NamedBean
 * @param t The NamedBean being stored
 * @param elem The JDOM element for storing the NamedBean
 */
void AbstractNamedBeanManagerConfigXML::storeComment(NamedBean* t, QDomElement elem)
{
 // add comment, if present
 if (t->getComment() != NULL)
 {
  QDomElement c = doc.createElement("comment");
  c.appendChild(doc.createTextNode(t->getComment()));
  elem.appendChild(c);
 }
}

/**
 * Store the username parameter from a NamedBean.
 * <ul>
 * <li>Before 2.9.6, this was an attribute
 * <li>Starting in 2.9.6, this was stored as both attribute and element
 * <li>Starting in 3.1/2.11.1, this will be just an element
 * </ul>
 * @param t The NamedBean being stored
 * @param elem The JDOM element for storing the NamedBean
 */
void AbstractNamedBeanManagerConfigXML::storeUserName(NamedBean* t, QDomElement elem)
{
 QString uname = t->getUserName();
 if (uname!=NULL && uname.length() > 0)
 {
  //elem.setAttribute("userName", uname); // doing this for compatibility during 2.9.* series
  QDomElement e1;
  elem.appendChild(e1=doc.createElement("userName"));
  e1.appendChild(doc.createTextNode(uname));
 }
}

/**
 * Get the username attribute from one element of
 * a list of QDomElements defining NamedBeans
 * @param beanList List, where each entry is an QDomElement
 * @param i index of QDomElement in list to examine
 */
/*protected*/ QString AbstractNamedBeanManagerConfigXML::getUserName(QDomNodeList beanList, int i)
{
 return getUserName(beanList.at(i).toElement());
}

/**
 * Get the user name from an QDomElement defining a NamedBean
 * <ul>
 * <li>Before 2.9.6, this was an attribute
 * <li>Starting in 2.9.6, this was stored as both attribute and element
 * <li>Starting in 3.1/2.11.1, this will be just an element
 * </ul>
 * @param elem The existing QDomElement
 */
/*protected*/ QString AbstractNamedBeanManagerConfigXML::getUserName(QDomElement elem)
{
 if ( !elem.firstChildElement("userName").isNull())
 {
  return elem.firstChildElement("userName").text();
 }
 if ( !elem.attribute("userName").isEmpty()) {
        return elem.attribute("userName");
 } return "";
}

/**
 * Get the system name from an QDomElement defining a NamedBean
 * <ul>
 * <li>Before 2.9.6, this was an attribute
 * <li>Starting in 2.9.6, this was stored as both attribute and element
 * <li>Starting in 3.1/2.10.1, this will be just an element
 * </ul>
 * @param elem The existing QDomElement
 */
/*protected*/ QString AbstractNamedBeanManagerConfigXML::getSystemName(QDomElement elem)
{
 if ( !elem.firstChildElement("systemName").isNull())
 {
  return elem.firstChildElement("systemName").text();
 }
 if ( !elem.attribute("systemName").isEmpty())
 {
  return elem.attribute("systemName");
 }
 return QString();
}
/**
 * Common service routine to check for and report on normalization (errors)
 * in the incoming NamedBean's name(s)
 * <p>
 * If NamedBeam.normalizeUserName changes, this may want to be updated.
 * <p>
 * Right now, this just logs. Someday, perhaps it should notify upward of
 * found issues by throwing an exception.
 * <p>
 * Package-level access to allow testing
 *
 * @param rawSystemName The proposed system name string, before
 *                      normalization
 * @param rawUserName   The proposed user name string, before normalization
 * @param manager       The NamedBeanManager that will be storing this
 */
void AbstractNamedBeanManagerConfigXML::checkNameNormalization(/*@Nonnull*/ QString rawSystemName, QString rawUserName, /*@Nonnull*/ Manager* manager) {
    // just check and log
    if (!rawUserName.isNull()) {
        QString normalizedUserName = NamedBean::normalizeUserName(rawUserName);
        if (rawUserName != (normalizedUserName)) {
            log->warn(tr("Requested user name \"%1\" for system name \"%2\" was normalized to \"%3\"").arg(
                    rawUserName).arg(rawSystemName).arg(normalizedUserName));
        }
        if (!normalizedUserName.isNull()) {
            NamedBean* bean = ((AbstractManager*)manager)->getBeanByUserName(normalizedUserName);
            if (bean != nullptr && bean->getSystemName() != (rawSystemName)) {
                log->warn(tr("User name \"%1\" already exists as system name \"%2\"").arg(normalizedUserName).arg(bean->getSystemName()));
            }
        } else {
            log->warn(tr("User name \"%1\" was normalized into null").arg(rawUserName));
        }
    }
}

/**
 * Load the comment attribute into a NamedBean
 * from one element of
 * a list of QDomElements defining NamedBeans
 * @param t The NamedBean being loaded
 * @param beanList List, where each entry is an QDomElement
 * @param i index of QDomElement in list to examine
 */
void AbstractNamedBeanManagerConfigXML::loadComment(NamedBean* t, QDomNodeList beanList, int i) {
    loadComment(t, beanList.at(i).toElement());
}

/**
 * Load the comment attribute into a NamedBean
 * from an QDomElement defining a NamedBean
 * @param t The NamedBean being loaded
 * @param elem The existing QDomElement
 */
void AbstractNamedBeanManagerConfigXML::loadComment(NamedBean* t, QDomElement elem)
{
 // load comment, if present
 QString c = elem.firstChildElement("comment").text();
 if (c != NULL)
 {
  t->setComment(c);
 }
}

/**
 * Convenience method to get a String value
 * from an Attribute in an QDomElement defining a NamedBean
 * @param elem The existing QDomElement
 * @param name name of desired Attribute
 */
QString AbstractNamedBeanManagerConfigXML::getAttributeString(QDomElement elem, QString name)
{
 QString a = elem.attribute(name);
 if (a!=NULL)
   return a;
 else
  return "";
}

/**
 * Convenience method to get a boolean value
 * from an Attribute in an QDomElement defining a NamedBean
 * @param elem The existing QDomElement
 * @param name Name of desired Attribute
 * @param def Default value for attribute
 */
bool AbstractNamedBeanManagerConfigXML::getAttributeBool(QDomElement elem, QString name, bool def)
{
 QString v = getAttributeString(elem, name);
 if (v.isEmpty())
  return def;
 else
  if (def)
  {
   return v!=("false");
  }
  else
  {
   return v!=("true");
  }
}

/**
 * Store all key/value properties
 * @param t The NamedBean being loaded
 * @param elem The existing QDomElement
 */
void AbstractNamedBeanManagerConfigXML::storeProperties(NamedBean* t, QDomElement elem)
{
    //java.util.Set<Object> s = t->getPropertyKeys();
 QSet<QString> s = t->getPropertyKeys();
 if (/*s == NULL ||*/ s.size() == 0) return;
 QDomElement ret = doc.createElement("properties");
 elem.appendChild(ret);
 foreach (QString key, s)
 {
  QString value = t->getProperty(key).toString();
  QDomElement p = doc.createElement("property");
  ret.appendChild(p);
//     p.addContent(new QDomElement("key")
//                     .setAttribute("class", key.getClass().getName())
//                     .setText(key.toString())
//                 );
  QDomElement e = doc.createElement("key");
  e.setAttribute("class", "String");
  e.appendChild(doc.createTextNode(key));
  p.appendChild(e);
  if (value != NULL)
  {
//   p.addContent(new QDomElement("value")
//               .setAttribute("class", value.getClass().getName())
//               .setText(value.toString())
//               );
   QDomElement e = doc.createElement("value");
   e.setAttribute("class", "String");
   e.appendChild(doc.createTextNode(value));
   p.appendChild(e);
  }
 }
}

/**
 * Load all key/value properties
 * @param t The NamedBean being loaded
 * @param elem The existing QDomElement
 */
void AbstractNamedBeanManagerConfigXML::loadProperties(NamedBean* t, QDomElement elem)
{
 QDomElement p = elem.firstChildElement("properties");
 if (p.isNull()) return;
 QDomNodeList pList = p.elementsByTagName("property");
 for (int i=0; i< pList.count(); i++)
 {
  QDomElement e = pList.at(i).toElement();
  QDomElement eKey = e.firstChildElement("key");
  QString keyClass;
  QString keyText;
  if(!eKey.isNull())
  {
   keyClass = e.attribute("class");
   keyText = e.text();
  }
  QDomElement eValue = e.firstChildElement("value");
  QString valueClass;
  QString valueText;
  if(!eValue.isNull())
  {
   valueClass = e.attribute("class");
   valueText = e.text();
  }
  if(keyClass != "")
  {
   t->setProperty(keyText, valueText);
  }
#if 0 // TODO:
  try
  {
   Class* cl;
    QObject* ctor;
    // create key object
    cl = Class::forName(e.firstChildElement("key").attribute("class"));
    ctor = cl.getConstructor(new Class<?>[] {String.class});
    Object key = ctor->newInstance(new Object[] {e.firstChildElement("key").text()});

    // create value object
    Object value = NULL;
    if (e.getChild("value") != NULL) {
        cl = Class.forName(e.getChild("value").getAttributeValue("class"));
        ctor = cl.getConstructor(new Class<?>[] {String.class});
        value = ctor.newInstance(new Object[] {e.getChild("value").getText()});
    }

    // store
   t.setProperty(key, value);
  }
  catch (Exception ex)
  {
   log.error("Error loading properties", ex);
  }
#endif
 }
}

//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(AbstractNamedBeanManagerConfigXML.class.getName());
//}
