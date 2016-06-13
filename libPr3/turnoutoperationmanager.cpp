#include "turnoutoperationmanager.h"
#include "instancemanager.h"
#include "nofeedbackturnoutoperation.h"
#include "sensorturnoutoperation.h"
#include "rawturnoutoperation.h"

TurnoutOperationManager* TurnoutOperationManager::theInstance = NULL;

TurnoutOperationManager::TurnoutOperationManager(QObject *parent) :
    QObject(parent)
{
 log = new Logger("TurnoutOperationManager");
// log->setDebugEnabled(true);
 turnoutOperations = new QMap<QString,TurnoutOperation*>();
 operationTypes = new QLinkedList<TurnoutOperation*>(); // array of the defining instances of each class, held in order of appearance
 pcs = new PropertyChangeSupport(this);
}
/**
 * class to look after the collection of TurnoutOperation subclasses
 * Unlike the other xxxManager, this does not inherit from AbstractManager since
 * the resources it deals with are not DCC system resources but rather
 * purely internal state
 * @author John Harper	Copyright 2005
 *
 */
//public class TurnoutOperationManager {


//    public TurnoutOperationManager() {
//    }

/*public*/ void TurnoutOperationManager::dispose()
{
}

/*public*/ QList<TurnoutOperation*> TurnoutOperationManager::getTurnoutOperations()
{
 //synchronized (this) {
 QMutexLocker locker(&mutex);
//            Collection<TurnoutOperation> entries = turnoutOperations.values();
//            return entries.toArray(new TurnoutOperation[0]);
 QList<TurnoutOperation*> list;
 QMapIterator<QString, TurnoutOperation*> it(*turnoutOperations);
 while(it.hasNext())
 {
  it.next();
  list.append(it.value());
 }
 return list;
//        }
}

/**
 * add a new operation
 * Silently replaces any existing operation with the same name
 * @param op
 */
/*protected*/ void TurnoutOperationManager::addOperation(TurnoutOperation* op)
{
 TurnoutOperation* previous;
 if (op==NULL || op->getName().isEmpty())
 {
  log->warn("NULL operation or name in addOperation");
 }
 else
 {
//        synchronized (this) {
  QMutexLocker locker(&mutex);
  previous = turnoutOperations->insert(op->getName(), op).value();
  if (op->isDefinitive())
  {
   updateTypes(op);
  }
// }
  if (previous != NULL)
  {
   if( log->isDebugEnabled()) log->debug("replaced existing operation called "+previous->getName());
  }
 }
 firePropertyChange("Content", QVariant(), QVariant());
}

/*protected*/ void TurnoutOperationManager::removeOperation(TurnoutOperation* op)
{
 if (op==NULL || op->getName().isEmpty())
 {
  log->warn("NULL operation or name in removeOperation");
 }
 else
 {
//        synchronized (this) {
  QMutexLocker locker(&mutex);

  turnoutOperations->remove(op->getName());
//        }
 }
 firePropertyChange("Content", QVariant(), QVariant());
}

/**
 * find a TurnoutOperation by its name
 * @param name
 * @return	the operation
 */
/*public*/ TurnoutOperation* TurnoutOperationManager::getOperation(QString name)
{
//    synchronized (this) {
 QMutexLocker locker(&mutex);
 return turnoutOperations->value(name);
//    }
}

/**
 * update the list of types to include a new or updated definitive instance.
 * since order is important we retain the existing order, placing a new
 * type at the end if necessary
 * @param op	new or updated operation
 */
/*private*/ void TurnoutOperationManager::updateTypes(TurnoutOperation* op)
{
 QLinkedList<TurnoutOperation*>* newTypes = new QLinkedList<TurnoutOperation*>();
 //Iterator<TurnoutOperation> iter = operationTypes.iterator();
 bool found = false;
// while (iter.hasNext())
// {
#if 1 // TODO:
 foreach(TurnoutOperation* item, *operationTypes)
 {
  if (item->metaObject()->className()==op->metaObject()->className())
  {
   newTypes->append(op);
   found = true;
   log->debug(QString("replacing definitive instance of ")+item->metaObject()->className());
  }
  else
  {
   newTypes->append(item);
  }
 }
 if (!found)
 {
  newTypes->append(op);
  log->debug(QString("adding definitive instance of ")+op->metaObject()->className());
 }
#endif
 operationTypes = newTypes;
}

/**
 * get the one-and-only instance of this class, if necessary creating it first.
 * At creation also preload the known TurnoutOperator subclasses (done here
 * to avoid constructor ordering problems).
 *
 * There's a threading problem here, because this invokes loadOperationTypes,
 * which gets the current turnout manager, often the proxy manager, which
 * in turn invokes loadOperationTypes again.  This is bad.
 *
 * @return	the TurnoutOperationManager
 */
/*static*/ TurnoutOperationManager* TurnoutOperationManager::getInstance()
{
 if (theInstance==NULL)
 {

  // and make available
  theInstance = new TurnoutOperationManager();

  // create the default instances of each of the known operation types
  theInstance->loadOperationTypes();

 }
 return theInstance;
}

/**
 * Load the operation types given by the current TurnoutManager instance, in
 * the order given.
 * <p>
 * The order is important because the acceptable feedback modes may overlap.
 * All we do is instantiate the classes. The constructors take care of putting
 * everything in the right places. We allow multiple occurrences of the same
 * name without complaining so the Proxy stuff works.
 *
 * There's a threading problem here, because this invokes
 * gets the current turnout manager, often the proxy manager, which
 * in turn invokes loadOperationTypes again.  This is bad. It's not clear
 * why it even works.
 *
 */
/*public*/ void TurnoutOperationManager::loadOperationTypes()
{
 #if 1 // TODO:
 QStringList validTypes = ((ProxyTurnoutManager*) InstanceManager::turnoutManagerInstance())->getValidOperationTypes();
 for (int i=0; i<validTypes.length(); ++i)
 {
  QString thisClassName = "jmri."+validTypes.at(i)+"TurnoutOperation";
  if (validTypes.at(i) == NULL)
  {
   log->warn("NULL operation name in loadOperationTypes");
  }
  else if (getOperation(validTypes.at(i)) == NULL)
  {
   try
   {
//    Class<?> thisClass = Class.forName(thisClassName);
//    thisClass.newInstance();
    TurnoutOperation* thisClass;
    if(validTypes.at(i) == "NoFeedback")
     thisClass = (TurnoutOperation*)new NoFeedbackTurnoutOperation();
    else if(validTypes.at(i) == "Raw")
     thisClass = (TurnoutOperation*)new RawTurnoutOperation();
    else if(validTypes.at(i) == "Sensor")
     thisClass = (TurnoutOperation*)new SensorTurnoutOperation();

    if (log->isDebugEnabled()) { log->debug("loaded TurnoutOperation class "+thisClassName); }
} catch (ClassNotFoundException e1) { log->error("during loadOperationTypes", e1.getMessage()); }
  catch (InstantiationException e2) { log->error("during loadOperationTypes", e2.getMessage()); }
  catch (IllegalAccessException e3) { log->error("during loadOperationTypes", e3.getMessage()); }
  }
 }
#endif
}

/**
 * Find a suitable operation for this turnout, based on its feedback type.
 * The mode is passed separately so the caller can transform it
 * @param t	turnout
 * @param apparentMode	mode(s) to be used when finding a matching operation
 */
/*public*/ TurnoutOperation* TurnoutOperationManager::getMatchingOperationAlways(Turnout* t, int apparentMode)
{
 Q_UNUSED(t)
//    Iterator<TurnoutOperation> iter = operationTypes.iterator();
 TurnoutOperation* currentMatch = NULL;
 /* The loop below always returns the LAST operation
           that matches.  In the standard feedback modes,
           This currently results in returning the NoFeedback
           operation, since it is the last one added to
           operationTypes */
 //for(int i = operationTypes->count()-1; i <= 0; i--)
 foreach (TurnoutOperation* oper, *operationTypes)
//            while (iter.hasNext()) {
 {
  //TurnoutOperation* oper = operationTypes->at(i);
  if (oper->matchFeedbackMode(apparentMode))
  {
   currentMatch=oper;
  }
 }
 if(currentMatch!=NULL)
  return currentMatch;
 else
 return NULL;
}

/**
 * find the correct operation for this turnout. If operations are globally disabled,
 * return nothing
 * @param t	turnout
 * @param apparentMode	mode(s) to be used when finding a matching operation
 * @return operation
 */
/*public*/ TurnoutOperation* TurnoutOperationManager::getMatchingOperation(Turnout* t, int apparentMode)
{
 if (doOperations)
 {
  return getMatchingOperationAlways(t, apparentMode);
 }
 return NULL;
}

/*public*/ TurnoutOperation* TurnoutOperationManager::getMatchingOperationAlways(Turnout* t) {
    return getMatchingOperationAlways(t, t->getFeedbackMode());
}

/*
 * get/change status of whether operations are in use
 */
/*public*/ bool TurnoutOperationManager::getDoOperations() { return doOperations; }

/*public*/ void TurnoutOperationManager::setDoOperations(bool b)
{
 bool oldValue = doOperations;
    doOperations = b;
    firePropertyChange("doOperations", QVariant(oldValue), QVariant(b));
}

/**
 * Proxy support. Take a concatenation of operation type lists from multiple
 * systems and turn it into a single list, by eliminating duplicates and ensuring
 * that NoFeedback - which matches anything - comes at the end if it is present
 * at all.
 * @param types	list of types possibly containing dupliactes
 * @return list reduced as described above
 */
/*static public*/ QStringList TurnoutOperationManager::concatenateTypeLists(QStringList types)
{
 Logger log;
 QStringList* outTypes = new QStringList();
 bool noFeedbackWanted = false;
 for (int i=0; i<types.count(); ++i)
 {
  if (types[i] == "NoFeedback")
  {
   noFeedbackWanted = true;
  }
  else if (types[i]==NULL || types[i]==(""))
  {
   log.warn("NULL or empty operation name returned from turnout manager");
  }
  else if (!outTypes->contains(types[i]))
  {
   outTypes->append(types[i]);
  }
 }
 if (noFeedbackWanted)
 {
  outTypes->append("NoFeedback");
 }
 return *outTypes; //.toArray(new String[0]);
}

/*
 * Property change support
 */
/*public synchronized*/ void TurnoutOperationManager::addPropertyChangeListener(PropertyChangeListener* l)
{
 pcs->addPropertyChangeListener(l);
}
/*public synchronized */void TurnoutOperationManager::removePropertyChangeListener(PropertyChangeListener* l)
{
 QMutexLocker locker(&mutex);
 pcs->removePropertyChangeListener(l);
}
/*protected*/ void TurnoutOperationManager::firePropertyChange(QString p, QVariant old, QVariant n)
{ pcs->firePropertyChange(p,old,n);}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(TurnoutOperationManager.class.getName());
