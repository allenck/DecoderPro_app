#include "defaultfemalestringexpressionsocket.h"
#include "defaultmalestringexpressionsocket.h"
#include "defaultstringexpressionmanager.h"
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
            return ((DefaultMaleStringExpressionSocket*)getConnectedSocket()->bself())->evaluate();
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
    /*public*/   QHash<Category*, QList</*Class<? extends Base>*/QString>> DefaultFemaleStringExpressionSocket::getConnectableClasses() {
        return ((DefaultStringExpressionManager*)InstanceManager::getDefault("StringExpressionManager"))->getExpressionClasses();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/   void DefaultFemaleStringExpressionSocket::disposeMe() {
        // Do nothing
    }
