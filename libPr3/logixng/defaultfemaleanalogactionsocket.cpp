#include "defaultfemaleanalogactionsocket.h"
#include "defaultanalogactionmanager.h"
#include "instancemanager.h"
#include "base.h"
#include "femalesocketlistener.h"
#include "defaultmaleanalogactionsocket.h"
/**
 * Default implementation of the Female Analog Action socket
 */
///*public*/  final class DefaultFemaleAnalogActionSocket
//        extends AbstractFemaleSocket
//        implements FemaleAnalogActionSocket {

    /*public*/  DefaultFemaleAnalogActionSocket::DefaultFemaleAnalogActionSocket(Base* parent, FemaleSocketListener* listener,
                                                                                 QString name, QObject* parentObject) : AbstractFemaleSocket(parent, listener, name, parentObject) {
        //super(parent, listener, name);
        setObjectName("DefaultFemaleAnalogActionSocket");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool DefaultFemaleAnalogActionSocket::isCompatible(MaleSocket *socket) {
     QObject* obj = socket->bself();
     if(!obj) return false;
     MaleAnalogActionSocket* s = qobject_cast<MaleAnalogActionSocket*>(obj);
     return s;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QHash<Category *, QList<QString> > DefaultFemaleAnalogActionSocket::getConnectableClasses() {
        return ((DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager"))->getActionClasses();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultFemaleAnalogActionSocket::setValue(double value) /*throws JmriException*/ {
        if (AbstractFemaleSocket::isConnected()) {
            ((MaleAnalogActionSocket*)AbstractFemaleSocket::getConnectedSocket()->bself())->setValue(value);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DefaultFemaleAnalogActionSocket::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "!~");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DefaultFemaleAnalogActionSocket::getLongDescription(QLocale locale) {
        return tr(/*locale, */"!~ %1").arg(AbstractFemaleSocket::getName());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultFemaleAnalogActionSocket::disposeMe() {
        // Do nothing
    }
