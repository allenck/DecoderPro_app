#ifndef TURNOUTOPERATIONMANAGER_H
#define TURNOUTOPERATIONMANAGER_H

#include <QObject>
#include "logger.h"
#include "turnoutoperation.h"
#include <QMutex>
#include <QLinkedList>
class LIBPR3SHARED_EXPORT TurnoutOperationManager : public QObject
{
    Q_OBJECT
public:
 explicit TurnoutOperationManager(QObject *parent = 0);
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
 QT_DEPRECATED static TurnoutOperationManager* getInstance();
 bool doOperations;			// global on/off switch
 /*public*/ void dispose();
 /*public*/ QList<TurnoutOperation*> getTurnoutOperations();
 /*public*/ TurnoutOperation* getOperation(QString name);
 /*public*/ void loadOperationTypes();
 /**
  * Find a suitable operation for this turnout, based on its feedback type.
  * The mode is passed separately so the caller can transform it
  * @param t	turnout
  * @param apparentMode	mode(s) to be used when finding a matching operation
  */
 /*public*/ TurnoutOperation* getMatchingOperationAlways(Turnout* t, int apparentMode);
 /**
  * find the correct operation for this turnout. If operations are globally disabled,
  * return nothing
  * @param t	turnout
  * @param apparentMode	mode(s) to be used when finding a matching operation
  * @return operation
  */
 /*public*/ TurnoutOperation* getMatchingOperation(Turnout* t, int apparentMode);
 /*public*/ TurnoutOperation* getMatchingOperationAlways(Turnout* t);
 /*
  * get/change status of whether operations are in use
  */
 /*public*/ bool getDoOperations();
 /*public*/ void setDoOperations(bool b);
 static /*public*/ QStringList concatenateTypeLists(QStringList types);
 /*public synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l);
 /*public synchronized */void removePropertyChangeListener(PropertyChangeListener* l);

signals:
    
public slots:
private:
 Logger* log;
 /*private*/ QMap<QString,TurnoutOperation*>* turnoutOperations; //= new TreeMap<String,TurnoutOperation>();
 /*private*/ QLinkedList<TurnoutOperation*>* operationTypes; // = new LinkedList<TurnoutOperation>(); // array of the defining instances of each class, held in order of appearance
 /*private*/ static TurnoutOperationManager* theInstance;
 QMutex mutex;
 /*private*/ void updateTypes(TurnoutOperation* op);
 PropertyChangeSupport* pcs;// = new PropertyChangeSupport(this);
 static TurnoutOperationManager* getDefault();

protected:
 /*protected*/ void addOperation(TurnoutOperation* op);
 /*protected*/ void removeOperation(TurnoutOperation* op);
 /*protected*/ void firePropertyChange(QString p, QVariant old, QVariant n);
 friend class TurnoutOperation;
 friend class TurnoutOperationFrame;
};

#endif // TURNOUTOPERATIONMANAGER_H
