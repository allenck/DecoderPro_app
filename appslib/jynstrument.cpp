#include "jynstrument.h"
#include "loggerfactory.h"
#include "class.h"
#include <QDomElement>

/**
 * A Jynstrument is a Jython script and associated other resources that can
 * decorate a Java class.
 *
 * @see JynstrumentFactory
 * @author Lionel Jeanson Copyright 2009
 * @since 2.7.8
 */
// /*public*/ abstract class Jynstrument extends JPanel {


    /**
     * Access to the context object to which this Jynstrument was attached when
     * it was created.
     *
     * @return the context object
     */
    /*public*/ QObject* Jynstrument::getContext() {
        return mContext;
    }

    /*public*/ void Jynstrument::setContext(QObject* context) {
        mContext = context;
    }

    /*public*/ QString Jynstrument::getJythonFile() {
        return jythonFile;
    }

    /*public*/ void Jynstrument::setJythonFile(QString jythonFile) {
        this->jythonFile = jythonFile;
    }

    /**
     * Get the folder containing the defining Jython script.
     *
     * @return the parent folder of the script
     */
    /*public*/ QString Jynstrument::getFolder() {
        return jynstrumentFolder;
    }

    /*public*/ void Jynstrument::setFolder(QString jynstrumentFolder) {
        this->jynstrumentFolder = jynstrumentFolder;
    }

    /*public*/ QString Jynstrument::getClassName() {
        return className;
    }

    /*public*/ void Jynstrument::setClassName(QString className) {
        this->className = className;
    }

    /*public*/ void Jynstrument::exit() {
        QObject* cnt = parent();
        log->debug(tr("getParent() is ") + cnt->metaObject()->className());
        if (cnt != NULL) {
//            cnt->remove(this);
//            cnt->repaint();
        }
        quit();
        setPopUpMenu(NULL);
    }

    /*public*/ bool Jynstrument::validateContext() {
        if (getExpectedContextClassName() == NULL || mContext == NULL) {
            return false;
        }
        try {
            return (Class::forName(getExpectedContextClassName())->isAssignableFrom(mContext->metaObject()->className()));
        } catch (ClassNotFoundException e) {
            log->error(tr("Class %1 not found.").arg(getExpectedContextClassName(), e.getMessage()));
        }
        return false;
    }

//    /*public*/ abstract String getExpectedContextClassName();

//    /*public*/ abstract void init();

//    /*protected*/ abstract void quit();

    /*private*/ /*final*/ /*static*/ Logger* Jynstrument::log = LoggerFactory::getLogger("Jynstrument");

    /*public*/ QMenu* Jynstrument::getPopUpMenu() {
        return myPopUpMenu;
    }

    /*public*/ void Jynstrument::setPopUpMenu(QMenu* myPopUpMenu) {
        this->myPopUpMenu = myPopUpMenu;
    }

    /*public*/ void Jynstrument::setXml(QDomElement /*e*/) {
        // do nothing by default
    }

    /*public*/ QDomElement Jynstrument::getXml() {
       return QDomElement();
   }
