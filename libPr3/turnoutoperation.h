#ifndef TURNOUTOPERATION_H
#define TURNOUTOPERATION_H
#include <QString>
#include <QObject>
//#include "comparable.h"
#include "abstractturnout.h"


class Turnout;
class TurnoutOperator;
class LIBPR3SHARED_EXPORT TurnoutOperation  : public QObject//: Comparable<QObject>
{
 Q_OBJECT
public:
    explicit TurnoutOperation(QString n,QObject *parent = 0);
    TurnoutOperation(TurnoutOperation&);
    /**
     * factory to make a copy of an operation identical in all respects except
     * the name
     * @param n	name for new copy
     * @return TurnoutOperation of same concrete class as this
     */
    /*public abstract*/ virtual TurnoutOperation* makeCopy(QString n);
    /**
     * get the descriptive name of the operation
     * @return	name
     */
    /*public*/ virtual QString getName();
    /**
     * ordering so operations can be sorted, using their name
     * @param other	other TurnoutOperation object
     * @return usual compareTo return values
     */
    /*public*/ virtual int compareTo(QObject* other);
    /**
     *
     * @param other another TurnoutOperation
     * @return true if the two operations are equivalent, i.e. same subclass and same parameters
     */
    /*public abstract*/ /*virtual*/ bool equivalentTo(TurnoutOperation* other);
    /**
     * rename an operation
     * @param newName
     * @return true iff the name was changed to the new value - otherwise name is unchanged
     */
    /*public*/ bool rename(QString newName);
    /**
     * get the definitive operation for this parameter variation
     * @return definitive operation
     */
    /*public*/ TurnoutOperation* getDefinitive();
    /**
     *
     * @return	true iff this is the "defining instance" of the class,
     * which we determine by the name of the instance being the same
     * as the prefix of the class
     */
    /*public*/ bool isDefinitive();
    /**
     * Get an instance of the operator for this operation type, set up
     * and started to do its thing in a private thread for the specified turnout.
     * @param	t	the turnout to apply the operation to
     * @return		the operator
     */
#if 0 // TODO:
    /*public abstract*/virtual TurnoutOperator* getOperator(AbstractTurnout* t);
#endif
    /**
     * delete all knowledge of this operation. Reset any turnouts using
     * it to the default
     *
     */
    /*public*/ void dispose();
    /*public*/ bool isDeleted();
    /**
     * see if operation is in use (needed by the UI)
     * @return true iff any turnouts are using it
     */
    /*public*/ bool isInUse();
    /**
     * Nonce support. A nonce is a TurnoutOperation created specifically for
     * one turnout, which can't be directly referred to by name. It does
     * have a name, which is the turnout it was created for, prefixed by "*"
     * @return true if this object is a nonce
     */
    /*public*/ bool isNonce();
    /*public*/ void setNonce(bool n);
    /*public*/ TurnoutOperation* makeNonce(Turnout* t);

    /*
     * property change support
     */
    PropertyChangeSupport* pcs;// = new PropertyChangeSupport(this);

    /*public synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l);
    /*public synchronized*/ void removePropertyChangeListener(PropertyChangeListener* l);
    /**
     * @param mode feedback mode for a turnout
     * @return	true iff this operation's feedback mode is one we know how to deal with
     */
    /*public*/ bool matchFeedbackMode(int mode);

signals:
    void propertyChange(PropertyChangeEvent*);

public slots:
private:
 QString name;
 int feedbackModes;
 bool nonce;		// created just for one turnout and not reusable
 QObject *parent;

protected:
    /**
     * set feedback modes - part of construction but done separately for
     * ordering problems
     * @param fm	valid feedback modes for this class
     */
    /*protected*/ void setFeedbackModes(int fm);
 friend class TurnoutOperationManager;
};

#endif // TURNOUTOPERATION_H
