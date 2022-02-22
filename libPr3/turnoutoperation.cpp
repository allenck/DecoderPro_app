#include "turnoutoperation.h"
#include "turnoutoperationmanager.h"
#include "turnoutmanager.h"
#include "turnoutoperator.h"
#include "instancemanager.h"
#include "proxyturnoutmanager.h"

//TurnoutOperation::TurnoutOperation(QString n, QObject *parent) :
//    Comparable(parent)
//{
//    feedbackModes = 0;
//    nonce = false;		// created just for one turnout and not reusable
//    name = n;
//    TurnoutOperationManager.getInstance()->addOperation(this);
//    pcs = new SwingPropertyChangeSupport(this, nullptr);
//}
/**
 * Framework for automating reliable turnout operation. This interface allows
 * a particular style (e.g. retries) to be implemented and then to have multiple
 * instances for variations in parameters if required
 * <p>
 * This mechanism is designed to extensible to allow new operation types (e.g.
 * for Tortoise-style point machines) and to allow individual system types to
 * change it, for example to allow operation with alternative feedback arrangements.
 * <p>
 * The TurnoutOperation class is at the heart of things, although there are
 * several other classes, partly to fit in with JMRI's package structure. Each
 * specific retry scheme has its own concrete subclass of TurnoutOperation. One
 * instance of each such class is created at startup. It has the same name as
 * the prefix to the class, and is called the "defining instance". Further instances
 * can exist with different parameter values (e.g. number of retries).
 * <p>
 * The TurnoutOperationManager class (only one instance) keeps track of the
 * instances and can retrieve them by name. It can also supply a suitable TurnoutOperation
 * for a given turnout, based on the feedback type, if the turnout does not identify
 * one for itself.
 * <p>
 * Each AbstractTurnout may have a reference to a TurnoutOperation class, which
 * may be unique to this turnout or may be shared. When the turnout is thrown, if
 * it has its own TurnoutOperation, this is used (unless the turnout has selected
 * no automation). Otherwise, the TurnoutOperationManager is asked to find one.
 * <p>
 * The TurnoutOperation has a factory method (getOperation) which is called when
 * a turnout is operated, to supply the operator. Each subclass of TurnoutOperation
 * has a corresponding subclass of TurnoutOperator, which contains the logic for
 * the retry scheme. Each operator runs in its own thread, which terminates when
 * the operation is complete. If another operation of the same turnout is made before
 * the first one completes, the older thread terminates itself when it realises
 * it is no longer the active operation for the turnout.
 * <p>
 * The parameters of a TurnoutOperation can be edited. Each subclass has its own
 * xxxTurnoutOperationConfig class, which knows how to display the parameters in a
 * JPanel and gather them up again and store them afterwards.
 * <p>
 * Each subclass also has its own xxxTurnoutOperationXml class, which knows how
 * to store the information in an XML element, and restore it.
 * <p>
 * The current code defines two operations, NoFeedback and Sensor. Because these
 * have so much in common (only the xxxTurnoutOperator class has any differences),
 * most of them is implemented in the CommonTurnout... classes. This family is not
 * part of the general structure, although it can be reused if it helps.
 * <p>
 * <b>Extensibility</b>
 * <p>
 * To write a new type of operation:
 * <p>
 * 1. Create the xxxTurnoutOperation class
 * 2. Create the xxxTurnoutOperator class, including the logic for what you're trying to do
 * 3. Create the xxxTurnoutOperationConfig class - the CommonTurnoutOperationConfig class
 * can be used as a reference
 * 4. Create the xxxTurnoutOperationXml class - again the Common... class can be used
 * as a reference
 * 5. Add the prefix to the class name (e.g. "Tortoise") to the list
 * AbstractTurnoutManager.validOperationTypes, otherwise
 * it will not be instantiated at startup and hence will not be available
 * <p>
 * To change the behavior for a particular system type:
 * <p>
 * There are some functions which can be overridden in the system-specific subclasses
 * to change default behaviour if desired. These mechanisms are orthogonal to the operation
 * subclasses.
 * <p>
 * 1. Override AbstractTurnoutManager.getValidOperationTypes to change the operation types
 * allowed for this system.
 * 2. Override AbstractTurnout.getFeedbackModeForOperation to map system-specific feedback
 * modes into modes that the general classes know about.
 * 3. Override AbstractTurnout.getTurnoutOperator if you want to do something <i>really</i>
 * different.
 *
 * @author John Harper	Copyright 2005
 *
 */
//public abstract class TurnoutOperation implements Comparable<Object> {

TurnoutOperation::TurnoutOperation(QString n, QObject *parent) : SwingPropertyChangeSupport(this, parent)
{
 feedbackModes = 0;
 nonce = false;		// created just for one turnout and not reusable
 name = n;
 this->parent = parent;
 TurnoutOperationManager::getInstance()->addOperation(this);
 pcs = new SwingPropertyChangeSupport(this, nullptr);
}

TurnoutOperation::TurnoutOperation(TurnoutOperation & other) : SwingPropertyChangeSupport(this, parent)
{this->parent = other.parent;
 this->name = other.name;
 this->feedbackModes = other.feedbackModes;
 this->nonce = other.nonce;
 pcs = new SwingPropertyChangeSupport(this, nullptr);
}

/**
 * factory to make a copy of an operation identical in all respects except
 * the name
 * @param n	name for new copy
 * @return TurnoutOperation of same concrete class as this
 */
/*public*/ /*abstract*/ TurnoutOperation* TurnoutOperation::makeCopy(QString n)
{
 return new TurnoutOperation(n);
}

/**
 * set feedback modes - part of construction but done separately for
 * ordering problems
 * @param fm	valid feedback modes for this class
 */
/*protected*/ void TurnoutOperation::setFeedbackModes(int fm) {
    feedbackModes = fm;
}

/**
 * get the descriptive name of the operation
 * @return	name
 */
/*public*/ QString TurnoutOperation::getName() { return name; }

/**
 * ordering so operations can be sorted, using their name
 * @param other	other TurnoutOperation object
 * @return usual compareTo return values
 */
/*public*/ int TurnoutOperation::compareTo(QObject* other)
{
 return (int) (name==(((TurnoutOperation*)other)->getName()));
//        return name==(((TurnoutOperation)other).name);
}

/**
 *
 * @param other another TurnoutOperation
 * @return true if the two operations are equivalent, i.e. same subclass and same parameters
 */
/*public abstract*/ bool TurnoutOperation::equivalentTo(TurnoutOperation* /*other*/)
{
 return false;
}

/**
 * rename an operation
 * @param newName
 * @return true iff the name was changed to the new value - otherwise name is unchanged
 */
/*public*/ bool TurnoutOperation::rename(QString newName) {
    bool result = false;
    TurnoutOperationManager* mgr = TurnoutOperationManager::getInstance();
    if (!isDefinitive() && mgr->getOperation(newName)==NULL) {
        mgr->removeOperation(this);
        name = newName;
        setNonce(false);
        mgr->addOperation(this);
        result = true;
    }
    return result;
}

/**
* get the definitive operation for this parameter variation
* @return definitive operation
*/
/*public*/ TurnoutOperation* TurnoutOperation::getDefinitive() {
#if 1 // TODO:

//QStringList myClass = this->getClass().getName().split(".");
//QString finalClass = myClass[myClass.length-1];
QString finalClass = this->metaObject()->className();
QString mySubclass = finalClass.mid(0, finalClass.indexOf("TurnoutOperation"));
return TurnoutOperationManager::getInstance()->getOperation(mySubclass);
#else
//return NULL;
 return this;
#endif
}
/**
*
* @return	true iff this is the "defining instance" of the class,
* which we determine by the name of the instance being the same
* as the prefix of the class
*/
/*public*/ bool TurnoutOperation::isDefinitive() {
#if 1 // DONE:

//QStringList classNames = jmri.util.StringUtil.split(this.getClass().getName(), ".");
//QString className = classNames[classNames.length-1];
QString className = this->metaObject()->className();
QString opName = getName()+"TurnoutOperation";
//return (className ==(opName));
return QString::compare(className, opName,Qt::CaseInsensitive) == 0;
#else
//return false;
 return true;
#endif
}
/**
* Get an instance of the operator for this operation type, set up
* and started to do its thing in a private thread for the specified turnout.
* @param	t	the turnout to apply the operation to
* @return		the operator
*/
//public abstract TurnoutOperator getOperator(AbstractTurnout t);

/**
* delete all knowledge of this operation. Reset any turnouts using
* it to the default
*
*/
/*public*/ void TurnoutOperation::dispose()
{
if (!isDefinitive())
{
TurnoutOperationManager::getInstance()->removeOperation(this);
name = "*deleted";
pcs->firePropertyChange("Deleted", QVariant(), QVariant());		// this will remove all dangling references
}
}

/*public*/ bool TurnoutOperation::isDeleted() {
    return (name==("*deleted"));
}

/**
* see if operation is in use (needed by the UI)
* @return true iff any turnouts are using it
*/
/*public*/ bool TurnoutOperation::isInUse() {
bool result = false;
#if 1 // TODO:
TurnoutManager* tm = InstanceManager::turnoutManagerInstance();
QStringList turnouts = ((ProxyTurnoutManager*)tm)->AbstractProxyManager::getSystemNameList();
QStringListIterator iter(turnouts);
while (iter.hasNext())
{
 Turnout* t = (Turnout*)((ProxyTurnoutManager*)tm)->AbstractProxyManager::getBySystemName(iter.next())->self();
 if (t!=NULL && ((AbstractTurnout*)t)->getTurnoutOperation() == this)
 {
  result = true;
  break;
 }
}
#endif
return result;
}

/**
* Nonce support. A nonce is a TurnoutOperation created specifically for
* one turnout, which can't be directly referred to by name. It does
* have a name, which is the turnout it was created for, prefixed by "*"
* @return true if this object is a nonce
*/
/*public*/ bool TurnoutOperation::isNonce() { return nonce; }
/*public*/ void TurnoutOperation::setNonce(bool n) {
nonce = n;
TurnoutOperationManager::getInstance()->firePropertyChange("Content", QVariant(), QVariant());
}

/*public*/ TurnoutOperation* TurnoutOperation::makeNonce(Turnout* t)
{
    TurnoutOperation* op = makeCopy("*"+t->getSystemName());
    op->setNonce(true);
    return op;
}

///*
// * property change support
// */
///*public synchronized*/ void TurnoutOperation::addPropertyChangeListener(PropertyChangeListener* l) {
//    pcs->SwingPropertyChangeSupport::addPropertyChangeListener(l);
//}
///*public synchronized*/ void TurnoutOperation::removePropertyChangeListener(PropertyChangeListener* l) {
//    pcs->removePropertyChangeListener(l);
//}

/**
 * @param mode feedback mode for a turnout
 * @return	true iff this operation's feedback mode is one we know how to deal with
 */
/*public*/ bool TurnoutOperation::matchFeedbackMode(int mode) {
    return (mode & feedbackModes) != 0;
}

//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(TurnoutOperation.class.getName());
