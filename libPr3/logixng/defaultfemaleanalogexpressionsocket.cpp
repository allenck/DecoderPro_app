#include "defaultfemaleanalogexpressionsocket.h"
#include "femalesocketlistener.h"
#include "maleanalogexpressionsocket.h"
#include "analogexpressionmanager.h"
#include "instancemanager.h"
/**
 * Default implementation of the Female Analog Expression socket
 */
///*public*/  class DefaultFemaleAnalogExpressionSocket extends AbstractFemaleSocket
//        implements FemaleAnalogExpressionSocket {


    /*public*/  DefaultFemaleAnalogExpressionSocket::DefaultFemaleAnalogExpressionSocket(Base* parent, FemaleSocketListener* listener,
                                                                                         QString name, QObject* parentObject)
     : AbstractFemaleSocket(parent, listener, name, parentObject)
    {
        //super(parent, listener, name);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool DefaultFemaleAnalogExpressionSocket::isCompatible(MaleSocket* socket) {
        return qobject_cast<MaleAnalogExpressionSocket*>(socket->self());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  double DefaultFemaleAnalogExpressionSocket::evaluate() /*throws JmriException*/ {
        if (isConnected()) {
            return ((MaleAnalogExpressionSocket)getConnectedSocket()).evaluate();
        } else {
            return 0.0;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool DefaultFemaleAnalogExpressionSocket::getTriggerOnChange() {
        throw new UnsupportedOperationException("Not supported");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultFemaleAnalogExpressionSocket::setTriggerOnChange(bool triggerOnChange) {
        throw new UnsupportedOperationException("Not supported");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DefaultFemaleAnalogExpressionSocket::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "?");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DefaultFemaleAnalogExpressionSocket::getLongDescription(QLocale locale) {
        return tr(/*locale,*/ "? %1").arg(AbstractFemaleSocket::getName());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QMap<Category*, QList</*Class<? extends Base>*/Base*>> DefaultFemaleAnalogExpressionSocket::getConnectableClasses() {
        return ((AnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager"))->getExpressionClasses();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultFemaleAnalogExpressionSocket::disposeMe() {
        // Do nothing
    }
