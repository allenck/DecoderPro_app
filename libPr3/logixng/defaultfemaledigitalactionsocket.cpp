#include "defaultfemaledigitalactionsocket.h"
#include "instancemanager.h"
#include "defaultdigitalactionmanager.h"

/**
 * Default implementation of the Female Digital Action socket
 */
///*public*/  class DefaultFemaleDigitalActionSocket
//        extends AbstractFemaleSocket
//        implements FemaleDigitalActionSocket {


    /*public*/  DefaultFemaleDigitalActionSocket::DefaultFemaleDigitalActionSocket(Base* parentObject,
                                                  FemaleSocketListener* listener, QString name, QObject* parent )
      : AbstractFemaleSocket(parentObject, listener, name, parent)
    {
        //super(parent, listener, name);
      setObjectName("DefaultFemaleDigitalActionSocket");
    }

    //@Override
    /*public*/  bool DefaultFemaleDigitalActionSocket::isCompatible(MaleSocket* socket) {
     QObject* obj = (QObject*)socket;
     MaleDigitalActionSocket* mas = qobject_cast<MaleDigitalActionSocket*>(socket->bself());
        //return qobject_cast<MaleDigitalActionSocket*>(socket->bself());
     return mas;
    }

    //@Override
    /*public*/  void DefaultFemaleDigitalActionSocket::execute() /*throws JmriException*/ {
        if (AbstractFemaleSocket::isConnected()) {
            ((MaleDigitalActionSocket*)AbstractFemaleSocket::getConnectedSocket()->bself())->execute();
        }
    }

    //@Override
    /*public*/  QString DefaultFemaleDigitalActionSocket::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "!");
    }

    //@Override
    /*public*/  QString DefaultFemaleDigitalActionSocket::getLongDescription(QLocale locale) {
        return tr(/*locale, */"! %1").arg(AbstractFemaleSocket::getName());
    }

    //@Override
    /*public*/  QHash<Category *, QList<QString> > DefaultFemaleDigitalActionSocket::getConnectableClasses() {
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->getActionClasses();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultFemaleDigitalActionSocket::disposeMe() {
        // Do nothing
    }

    /*public*/ QString DefaultFemaleDigitalActionSocket::getClassName()
    {
     return "jmri.jmrit.logixng.implementation.DefaultFemaleDigitalActionSocket";
    }
