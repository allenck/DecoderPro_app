#include "abstractmanagerxml.h"
#include "loggerfactory.h"

/**
 * Provides the functionality for configuring ActionManagers
 *
 * @author Dave Duchamp Copyright (c) 2007
 * @author Daniel Bergqvist Copyright (c) 2018
 */
// /*public*/  abstract class AbstractManagerXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {



/**
 * Store data for a MaleSocket
 *
 * @param maleSocket the socket to store
 * @return QDomElement containing the complete info
 */
/*public*/  QDomElement storeMaleSocket(MaleSocket maleSocket) {
    QDomElement QDomElement = doc.createElement("MaleSocket");

    Base m = maleSocket;
    while (m instanceof MaleSocket) {
        MaleSocket ms = (MaleSocket) m;

        try {
            QDomElement e = ConfigXmlManager.elementFromObject(ms);
            if (e != null) {
                element.addContent(e);
            } else {
                throw new RuntimeException("Cannot load xml configurator for " + ms.getClass().getName());
            }
        } catch (RuntimeException e) {
            log.error("Error storing maleSocket: {}", e, e);
        }

        m = ms.getObject();
    }

    return (element);
}

/**
 * Utility method to load the individual DigitalActionBean objects. If
 * there's no additional info needed for a specific action type, invoke
 * this with the parent of the set of DigitalActionBean elements.
 *
 * @param QDomElement QDomElement containing the MaleSocket QDomElement to load.
 * @param maleSocket the socket to load
 */
/*public*/  void loadMaleSocket(QDomElement element, MaleSocket maleSocket) {

    Map<String, Map.Entry<MaleSocketXml, Element>> maleSocketXmlClasses = new HashMap<>();

    QDomElement elementMaleSocket = element.getChild("MaleSocket");
    if (elementMaleSocket == null) {
        throw new IllegalArgumentException("maleSocket is null");
    }

    List<Element> children = elementMaleSocket.getChildren();
    log.debug("Found " + children.size() + " male sockets");  // NOI18N

    for (QDomElement e : children) {

        String className = e.getAttribute("class").getValue();
//            log.error("className: " + className);

        Class<?> clazz = xmlClasses.get(className);

        if (clazz == null) {
            try {
                clazz = Class.forName(className);
                xmlClasses.put(className, clazz);
            } catch (ClassNotFoundException ex) {
                log.error("cannot load class " + className, ex);
            }
        }

        if (clazz != null) {
            Constructor<?> c = null;
            try {
                c = clazz.getConstructor();
            } catch (NoSuchMethodException | SecurityException ex) {
                log.error("cannot create constructor", ex);
            }

            if (c != null) {
                try {
                    MaleSocketXml o = (MaleSocketXml)c.newInstance();

                    Map.Entry<MaleSocketXml, Element> entry =
                            new HashMap.SimpleEntry<>(o, e);
                    maleSocketXmlClasses.put(className, entry);
                } catch (InstantiationException | IllegalAccessException | IllegalArgumentException | InvocationTargetException ex) {
                    log.error("cannot create object", ex);
                }
            }
        }
    }

    Base m = maleSocket;
    while (m instanceof MaleSocket) {
        MaleSocket ms = (MaleSocket) m;

        String cName = ConfigXmlManager.adapterName(ms);
        Map.Entry<MaleSocketXml, Element> entry = maleSocketXmlClasses.get(cName);

        try {
            entry.getKey().load(entry.getValue(), ms);
        } catch (RuntimeException ex) {
            log.error("Error storing maleSocket: {}", ex, ex);
        }

        m = ms.getObject();
    }

}


