#include "defaultfemaledigitalexpressionsocket.h"
#include "maledigitalexpressionsocket.h"
#include "defaultdigitalexpressionmanager.h"
#include "instancemanager.h"
/**
 * Default implementation of the Female Digital Expression socket
 */
///*public*/  class DefaultFemaleDigitalExpressionSocket extends AbstractFemaleSocket
//        implements FemaleDigitalExpressionSocket {

    /*public*/ DefaultFemaleDigitalExpressionSocket::DefaultFemaleDigitalExpressionSocket(Base* parent,
                   FemaleSocketListener* listener, QString name, QObject* parentObj)
     : AbstractFemaleSocket(parent, listener, name, parentObj)
    {
        //super(parent, listener, name);
     setObjectName("DefaultFemaleDigitalExpressionSocket");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool DefaultFemaleDigitalExpressionSocket::isCompatible(MaleSocket* socket) {
        return dynamic_cast<MaleDigitalExpressionSocket*>(socket->bself());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool DefaultFemaleDigitalExpressionSocket::evaluate() /*throws JmriException*/ {
        if (AbstractFemaleSocket::isConnected()) {
            return ((MaleDigitalExpressionSocket*)AbstractFemaleSocket::getConnectedSocket()->bself())
                    ->evaluate();
        } else {
            return false;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DefaultFemaleDigitalExpressionSocket::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "?");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DefaultFemaleDigitalExpressionSocket::getLongDescription(QLocale locale) {
        return tr(/*locale,*/ "? %1").arg(AbstractFemaleSocket::getName());
    }

    //@Override
    /*public*/  QHash<Category*, QList<QString> > DefaultFemaleDigitalExpressionSocket::getConnectableClasses() {
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->getExpressionClasses();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultFemaleDigitalExpressionSocket::disposeMe() {
        // Do nothing
    }
