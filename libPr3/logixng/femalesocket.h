#ifndef FEMALESOCKET_H
#define FEMALESOCKET_H
#include "base.h"
#include "socketalreadyconnectedexception.h"
#include "malesocket.h"
#include "femalesocketoperation.h"
#include "category.h"


/**
 * A LogixNG female expression socket.
 * A Expression or a Action that has children must not use
 * these directly but instead use a FemaleSocket.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
/*public*/ /*interface*/ class FemaleSocket : public virtual Base {
  Q_INTERFACES(Base)
 public:
    /**
     * Connect the male socket to this female socket.
     * @param socket the socket to connect
     * @throws SocketAlreadyConnectedException if the socket is already connected
     */
  /*public*/ virtual void _connect(MaleSocket* socket) /*throw (SocketAlreadyConnectedException)*/ {}

    /**
     * Disconnect the current connected male socket from this female socket.
     */
  /*public*/ virtual void _disconnect() {}

    /**
     * Can a connected socket be disconnected?
     * @return true if the socket can be disconnected, false otherwise
     */
    /*public*/ virtual /*default*/ bool canDisconnect() {
        return true;
    }

    /**
     * Get the connected socket.
     * @return the male socket or null if not connected
     */
  /*public*/ virtual MaleSocket* getConnectedSocket() {return nullptr;}

    /**
     * Is a male socket connected to this female socket?
     * @return true if connected
     */
  /*public*/ virtual bool isConnected(){return false;}

    /**
     * Is a particular male socket compatible with this female socket?
     * @param socket the male socket
     * @return true if the male socket can be connected to this female socket
     */
    /*public*/ virtual bool isCompatible(MaleSocket* socket)=0;

    /**
     * Validates a name for a FemaleSocket.
     * <P>
     * The name must have at least one character and only alphanumeric
     * characters. The first character must not be a digit.
     *
     * @param name the name
     * @return true if the name is valid, false otherwise
     */
    /*public*/ virtual /*default*/ bool validateName(QString name) {
        return validateName(name, false);
    }

    /**
     * Validates a name for a FemaleSocket.
     * <P>
     * The name must have at least one character and only alphanumeric
     * characters. The first character must not be a digit.
     *
     * @param name the name
     * @param ignoreDuplicateErrors true if duplicate names should be ignored,
     *                              false otherwise
     * @return true if the name is valid, false otherwise
     */
  /*public*/ virtual bool validateName(QString name, bool ignoreDuplicateErrors){}

    /**
     * Set the name of this socket.
     * <P>
     * The name must have at least one character and only alphanumeric
     * characters. The first character must not be a digit.
     *
     * @param name the name
     */
    /*public*/ virtual /*default*/ void setName(QString name) {
        setName(name, false);
    }

    /**
     * Set the name of this socket.
     * <P>
     * The name must have at least one character and only alphanumeric
     * characters. The first character must not be a digit.
     *
     * @param name the name
     * @param ignoreDuplicateErrors true if duplicate names should be ignored,
     *                              false otherwise
     */
  /*public*/ virtual void setName(QString name, bool ignoreDuplicateErrors) {}

    /**
     * Get the name of this socket.
     * @return the name
     */
    //@CheckForNull
  /*public*/ virtual QString getName() {return "";}

    /**
     * Is the operation allowed on this socket?
     * @param oper the operation to do
     * @return true if operation is allowed, false otherwise
     */
    /*public*/ /*default*/ bool isSocketOperationAllowed(FemaleSocketOperation::TYPES oper)
    {
        Base* parent = getParent();
        if (parent == nullptr) return false;

        for (int i=0; i < parent->getChildCount(); i++) {
            if (parent->getChild(i) == this) {
                return parent->isSocketOperationAllowed(i, oper);
            }
        }
        throw  IllegalArgumentException("Invalid index");
    }

    /**
     * Do an operation on this socket
     * @param oper the operation to do
     */
    /*public*/ virtual /*default*/ void doSocketOperation(FemaleSocketOperation::TYPES oper) {
        Base* parent = getParent();
        for (int i=0; i < parent->getChildCount(); i++) {
            if (parent->getChild(i) == this) {
                parent->doSocketOperation(i, oper);
                return;
            }
        }
        throw new IllegalArgumentException("Invalid index");
    }

    /**
     * Sets whenever listeners are enabled or not.
     * ConditionalNG has always listeners enabled, but Clipboard and Module
     * has never listeners enabled.
     * @param enable true if listeners should be enabled, false otherwise
     */
  /*public*/ virtual void setEnableListeners(bool enable) {}

    /**
     * Gets whenever listeners are enabled or not.
     * ConditionalNG has always listeners enabled, but Clipboard and Module
     * has never listeners enabled.
     * @return true if listeners should be enabled, false otherwise
     */
  /*public*/ virtual bool getEnableListeners(){return false;}

    /**
     * Am I an ancestor to this maleSocket?
     *
     * @param maleSocket the maleSocket that could be a child
     * @return true if this oject is an ancestor to the maleSocket object
     */
    /*public*/ virtual /*default*/ bool isAncestor(MaleSocket* maleSocket) {
        Base* base = maleSocket;
        while ((base != nullptr) && (base != this)) {
            base = base->getParent();
        }
        return base == this;
    }

    /**
     * Get a set of classes that are compatible with this female socket.
     *
     * @return a set of entries with category and class
     */
    /*public*/ virtual QHash<Category*, QList</*Class<? extends Base>*/ QString> > getConnectableClasses()=0;

    /** {@inheritDoc} */
    //@Override
    /*default*/ /*public*/ void setup() override{
        if (isConnected()) {
            getConnectedSocket()->setup();
        }
    }
  /*public*/ virtual QString getClassName() =0;//{return "jmri.jmrit.logixng.FemaleSocket";}

 //virtual QObject* self() =0;
};
Q_DECLARE_INTERFACE(FemaleSocket, "FemaleSocket");
#endif // FEMALESOCKET_H
