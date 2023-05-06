#include "abstractmanagerxml.h"
#include "malesocket.h"
#include "loggerfactory.h"
#include "runtimeexception.h"
#include "malesocketxml.h"
#include "class.h"
#include "abstractmalesocket.h"


/**
 * Provides the functionality for configuring ActionManagers
 *
 * @author Dave Duchamp Copyright (c) 2007
 * @author Daniel Bergqvist Copyright (c) 2018
 */
///*public*/  abstract class AbstractManagerXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {



    /**
     * Store data for a MaleSocket
     *
     * @param maleSocket the socket to store
     * @return Element containing the complete info
     */
    /*public*/  QDomElement AbstractManagerXml::storeMaleSocket(MaleSocket* maleSocket) {
        QDomElement element = doc.createElement("MaleSocket");

        Base* m = maleSocket;
        if(!maleSocket)
         return QDomElement();
        while (qobject_cast<AbstractMaleSocket*>(m->bself())) {
            MaleSocket* ms = (AbstractMaleSocket*) m->bself();

            try {
                QDomElement e = ConfigXmlManager::elementFromObject(ms->bself());
                if (!e.isNull()) {
                    element.appendChild(e);
                } else {
                    throw new RuntimeException(QString("Cannot load xml configurator for ") + ms->bself()->metaObject()->className());
                }
            } catch (RuntimeException* e) {
                log->error(tr("Error storing maleSocket: %1").arg(e->toString()), e);
            }

            m = ms->getObject();
        }

        return (element);
    }

    /**
     * Utility method to load the individual DigitalActionBean objects. If
     * there's no additional info needed for a specific action type, invoke
     * this with the parent of the set of DigitalActionBean elements.
     *
     * @param element Element containing the MaleSocket element to load.
     * @param maleSocket the socket to load
     */
    /*public*/  void AbstractManagerXml::loadMaleSocket(QDomElement element, MaleSocket* maleSocket) {

        QMap<QString, QMap<MaleSocketXml*, QDomElement>> maleSocketXmlClasses = QMap<QString, QMap<MaleSocketXml*, QDomElement>>();

        QDomElement elementMaleSocket = element.firstChildElement("MaleSocket");
        if (elementMaleSocket.isNull()) {
            throw new IllegalArgumentException("maleSocket is null");
        }

        QDomNodeList children = elementMaleSocket.childNodes();
        log->debug(QString("Found ") + QString::number(children.size()) + " male sockets");  // NOI18N

        for (int i=0; i< children.size(); i++) {
            QDomElement e = children.at(i).toElement();
            QString className = e.attribute("class");
//            log.error("className: " + className);

            Class* clazz = xmlClasses.value(className);

            if (clazz == nullptr) {
                try {
                    clazz = Class::forName(className);
                    xmlClasses.insert(className, clazz);
                } catch (ClassNotFoundException* ex) {
                    log->error("cannot load class " + className, ex);
                }
            }

            if (clazz != nullptr) {
                /*Constructor<?>*/Class* c = nullptr;
                try {
                    c = clazz->getConstructor();
                } catch (NoSuchMethodException* /*| SecurityException*/ ex) {
                    log->error("cannot create constructor", ex);
                }

                if (c != nullptr) {
                    try {
                        MaleSocketXml* o = (MaleSocketXml*)(c->newInstance());

                        QMap<MaleSocketXml*, QDomElement> entry = {{o, e}};
//                                new HashMap.SimpleEntry<>(o, e);
                        maleSocketXmlClasses.insert(className, entry);
                    } catch (InstantiationException*  /*| IllegalAccessException | IllegalArgumentException | InvocationTargetException*/ ex) {
                        log->error("cannot create object", ex);
                    }
                }
            }
        }

        Base* m = maleSocket;
        while (qobject_cast<MaleSocket*>(m->bself())) {
            MaleSocket* ms = (MaleSocket*) m->bself();

            QString cName = ConfigXmlManager::adapterName(ms->bself());
            QMapIterator<MaleSocketXml*, QDomElement> entry(maleSocketXmlClasses.value(cName));

            try {
                entry.key()->load(entry.value(), ms);
            } catch (RuntimeException* ex) {
                log->error(tr("Error storing maleSocket: %1").arg(ex->toString()), ex);
            }

            m = ms->getObject();
        }

    }


    /*private*/ /*final*/ /*static*/ Logger* AbstractManagerXml::log =LoggerFactory::getLogger("AbstractManagerXml");
