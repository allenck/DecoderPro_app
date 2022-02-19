#include "defaultfemalestringexpressionsocket.h"
#include "malestringexpressionsocket.h"
#include "stringexpressionmanager.h"
#include "instancemanager.h"

/**
 * Default implementation of the Female String Expression socket
 */
///*public*/   class DefaultFemaleStringExpressionSocket extends AbstractFemaleSocket
//        implements FemaleStringExpressionSocket {

    /*public*/   DefaultFemaleStringExpressionSocket::DefaultFemaleStringExpressionSocket(Base* parent, FemaleSocketListener* listener, QString name, QObject* parentObj)
 : AbstractFemaleSocket(parent, listener, name, parentObj) {
        //super(parent, listener, name);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/   bool DefaultFemaleStringExpressionSocket::isCompatible(MaleSocket* socket) {
        return qobject_cast<MaleStringExpressionSocket*>(socket->bself());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/   QString DefaultFemaleStringExpressionSocket::evaluate() /*throws JmriException*/ {
        if (AbstractFemaleSocket::isConnected()) {
            return ((MaleStringExpressionSocket*)AbstractFemaleSocket::getConnectedSocket()->bself())->evaluate();
        } else {
            return "";
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/   bool DefaultFemaleStringExpressionSocket::getTriggerOnChange() {
        throw new UnsupportedOperationException("Not supported");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/   void DefaultFemaleStringExpressionSocket::setTriggerOnChange(bool triggerOnChange) {
        throw new UnsupportedOperationException("Not supported");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/   QString DefaultFemaleStringExpressionSocket::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "?s");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/   QString DefaultFemaleStringExpressionSocket::getLongDescription(QLocale locale) {
        return tr(/*locale,*/ "?s %1").arg(AbstractFemaleSocket::getName());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/   QMap<Category*, QList</*Class<? extends Base>*/QString>*> DefaultFemaleStringExpressionSocket::getConnectableClasses() {
        return ((StringExpressionManager*)InstanceManager::getDefault("StringExpressionManager"))->getExpressionClasses();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/   void disposeMe() {
        // Do nothing
    }