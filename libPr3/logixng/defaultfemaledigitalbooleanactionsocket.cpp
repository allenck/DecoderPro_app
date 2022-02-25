#include "defaultfemaledigitalbooleanactionsocket.h"
#include "instancemanager.h"
#include "digitalbooleanactionmanager.h"

/**
 * Default implementation of the Female Digital Boolean Action socket
 */
///*public*/  final class DefaultFemaleDigitalBooleanActionSocket
//        extends AbstractFemaleSocket
//        implements FemaleDigitalBooleanActionSocket {


    /*public*/  DefaultFemaleDigitalBooleanActionSocket::DefaultFemaleDigitalBooleanActionSocket(Base* parent, FemaleSocketListener* listener, QString name, QObject* parentObj)
      : AbstractFemaleSocket(parent, listener, name, parentObj)
    {
        //super(parent, listener, name);
    }

    //@Override
    /*public*/  bool DefaultFemaleDigitalBooleanActionSocket::isCompatible(MaleSocket* socket) {
        return qobject_cast<MaleDigitalBooleanActionSocket*>(socket->bself());
    }

    //@Override
    /*public*/  void DefaultFemaleDigitalBooleanActionSocket::execute(bool hasChangedToTrue, bool hasChangedToFalse) /*throws JmriException*/ {
        if (isConnected()) {
            ((MaleDigitalBooleanActionSocket*)getConnectedSocket()->bself())
                    ->execute(hasChangedToTrue, hasChangedToFalse);
        }
    }

    //@Override
    /*public*/  QString DefaultFemaleDigitalBooleanActionSocket::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ " ");
    }

    //@Override
    /*public*/  QString DefaultFemaleDigitalBooleanActionSocket::getLongDescription(QLocale locale) {
        return tr(/*locale, */"DefaultFemaleDigitalBooleanActionSocket_Long %1").arg(getName());
    }

    //@Override
    /*public*/  QHash<Category *, QList<QString> > DefaultFemaleDigitalBooleanActionSocket::getConnectableClasses() {
        return ((DigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager"))->getActionClasses();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultFemaleDigitalBooleanActionSocket::disposeMe() {
        // Do nothing
    }
