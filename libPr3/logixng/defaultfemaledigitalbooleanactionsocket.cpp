#include "defaultfemaledigitalbooleanactionsocket.h"
#include "instancemanager.h"
#include "defaultdigitalbooleanactionmanager.h"

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
     setObjectName("DefaultFemaleDigitalBooleanActionSocket");
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
        return tr(/*locale,*/ "!b ");
    }

    //@Override
    /*public*/  QString DefaultFemaleDigitalBooleanActionSocket::getLongDescription(QLocale locale) {
        return tr(/*locale, */"!b %1").arg(getName());
    }

    //@Override
    /*public*/  QHash<Category *, QList<QString> > DefaultFemaleDigitalBooleanActionSocket::getConnectableClasses() {
        return ((DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager"))->getActionClasses();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultFemaleDigitalBooleanActionSocket::disposeMe() {
        // Do nothing
    }
