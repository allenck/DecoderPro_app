#include "defaultfemalestringactionsocket.h"
#include "instancemanager.h"
#include "stringactionmanager.h"
#include "malestringactionsocket.h"
#include "defaultstringactionmanager.h"
#include "defaultmalestringactionsocket.h"
/**
 * Default implementation of the Female String Action socket
 */
///*public*/  final class DefaultFemaleStringActionSocket
//        extends AbstractFemaleSocket
//        implements FemaleStringActionSocket {

    /*public*/  DefaultFemaleStringActionSocket::DefaultFemaleStringActionSocket(Base* parent, FemaleSocketListener* listener, QString name, QObject* parentObject)
    : AbstractFemaleSocket(parent, listener, name, parentObject){
        //super(parent, listener, name);
    }

    //@Override
    /*public*/  bool DefaultFemaleStringActionSocket::isCompatible(MaleSocket* socket) {
        return qobject_cast<DefaultMaleStringActionSocket*>(socket->bself());
    }

    //@Override
    /*public*/  void DefaultFemaleStringActionSocket::setValue(QString value) /*throws JmriException*/ {
        if (AbstractFemaleSocket::isConnected()) {
            ((DefaultMaleStringActionSocket*)AbstractFemaleSocket::getConnectedSocket()->bself())->setValue(value);
        }
    }

    //@Override
    /*public*/  QString DefaultFemaleStringActionSocket::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "!s");
    }

    //@Override
    /*public*/  QString DefaultFemaleStringActionSocket::getLongDescription(QLocale locale) {
        return tr(/*locale,*/ "!s %1").arg(AbstractFemaleSocket::getName());
    }

    //@Override
    /*public*/  QHash<Category, QList<QString> > DefaultFemaleStringActionSocket::getConnectableClasses() {
        return ((DefaultStringActionManager*)InstanceManager::getDefault("StringActionManager"))->getActionClasses();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultFemaleStringActionSocket::disposeMe() {
        // Do nothing
    }
