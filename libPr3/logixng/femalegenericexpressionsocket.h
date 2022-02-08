#ifndef FEMALEGENERICEXPRESSIONSOCKET_H
#define FEMALEGENERICEXPRESSIONSOCKET_H
#include "femalesocket.h"
/**
 * A generic female socket
 */
/*public*/ /*interface*/class FemaleGenericExpressionSocket
        : public FemaleSocket {
Q_INTERFACES(FemaleSocket)
 public:
    /*public*/ enum  SocketType {DIGITAL, ANALOG, STRING, GENERIC};
//        DIGITAL("SocketTypeDigital"),
//        ANALOG("SocketTypeAnalog"),
//        STRING("SocketTypeString"),
//        GENERIC("SocketTypeGeneric");

        /*private*/ /*final*/ QString _bundleName;

//        /*private*/ SocketType(QString bundleName) {
//            _bundleName = bundleName;
//        }

        //@Override
        /*public*/static QString toString(SocketType t) {
           switch(t)
           {
            case  DIGITAL: return QString("Digital");
           case  ANALOG: return QString("Analog");
            case  STRING: return QString("String");
            case  GENERIC: return QString("Generic");
           }
           return QString("Unknown");
        }



    /**
     * Get the current active socket.
     * @return the currently active socket or null if no socket is active
     */
    /*public*/ FemaleSocket* getCurrentActiveSocket();

    /**
     * Set the type of the socket.
     *
     * @param socketType the type of socket.
     * @throws SocketAlreadyConnectedException if the socket is already
     * connected and if the new type doesn't match the currently connected
     * socket.
     */
    /*public*/ void setSocketType(SocketType socketType)
            /*throws SocketAlreadyConnectedException*/;

    /**
     * Get the type of the socket.
     *
     * @return the type of socket
     */
    /*public*/ virtual SocketType getSocketType()=0;

    /**
     * Evaluate this expression.
     * <P>
     * This method validates the expression without doing any convertation of
     * the return value.
     * <P>
     * The parameter isCompleted is used if the expression should be evaluated
     * more than once. For example, the Count expression is not completed until
     * its child expression has been true and false a number of times.
     *
     * @return the result of the evaluation. This is of the same class as
     * parentValue.
     * @throws JmriException when an exception occurs
     */
    //@CheckForNull
    /*public*/ virtual QVariant evaluateGeneric() /*throws JmriException*/=0;

};
  Q_DECLARE_INTERFACE(FemaleGenericExpressionSocket, "FemaleGenericExpressionSocket")
#endif // FEMALEGENERICEXPRESSIONSOCKET_H
