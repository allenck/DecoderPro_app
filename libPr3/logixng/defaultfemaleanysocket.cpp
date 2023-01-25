#include "defaultfemaleanysocket.h"
#include "class.h"
/**
 * Default implementation of FemaleAnySocket
 *
 * @author Daniel Bergqvist (C) 2020
 */
///*public*/ class DefaultFemaleAnySocket extends AbstractFemaleSocket implements FemaleAnySocket {

    /*public*/ DefaultFemaleAnySocket::DefaultFemaleAnySocket(Base* parent, FemaleSocketListener* listener, QString name, QObject* parentObject)
     : AbstractFemaleSocket(parent, listener, name, parentObject)
    {
        //super(parent, listener, name);
     setObjectName("DefaultFemaleAnySocket");
    }

    //@Override
    /*public*/ void DefaultFemaleAnySocket::disposeMe() {
        throw  UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/ bool DefaultFemaleAnySocket::isCompatible(MaleSocket* socket) {
        return true;
    }

    //@Override
    /*public*/ QHash<Category, QList<QString> > DefaultFemaleAnySocket::getConnectableClasses() {
     return QHash<Category, QList<QString> >();
    }

    //@Override
    /*public*/ QString DefaultFemaleAnySocket::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "*");
    }

    //@Override
    /*public*/ QString DefaultFemaleAnySocket::getLongDescription(QLocale locale) {
        return tr(/*locale,*/ "* %1").arg(AbstractFemaleSocket::getName());
    }
