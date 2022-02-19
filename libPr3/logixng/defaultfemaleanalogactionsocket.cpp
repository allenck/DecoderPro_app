#include "defaultfemaleanalogactionsocket.h"
#include "analogactionmanager.h"
#include "instancemanager.h"
#include "base.h"
#include "femalesocketlistener.h"

/**
 * Default implementation of the Female Analog Action socket
 */
///*public*/  final class DefaultFemaleAnalogActionSocket
//        extends AbstractFemaleSocket
//        implements FemaleAnalogActionSocket {

    /*public*/  DefaultFemaleAnalogActionSocket::DefaultFemaleAnalogActionSocket(Base* parent, FemaleSocketListener* listener,
                                                                                 QString name, QObject* parentObject) : AbstractFemaleSocket(parent, listener, name, parentObject) {
        //super(parent, listener, name);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool DefaultFemaleAnalogActionSocket::isCompatible(MaleSocket* socket) {
        return qobject_cast<MaleAnalogActionSocket*>(socket->bself());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QMap<Category*, QList</*Class<? extends Base>*/QString>*> DefaultFemaleAnalogActionSocket::getConnectableClasses() {
        return ((AnalogActionManager*)InstanceManager::getDefault("AnalogActionManager"))->getActionClasses();
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
        return tr(/*locale, */"?~ %1").arg(AbstractFemaleSocket::getName());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultFemaleAnalogActionSocket::disposeMe() {
        // Do nothing
    }
