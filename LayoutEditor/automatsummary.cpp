#include "automatsummary.h"
#include "abstractautomaton.h"
#include "rosterentry.h"

//AutomatSummary::AutomatSummary(QObject *parent) :
//    QObject(parent)
//{
//}
AutomatSummary* AutomatSummary::self = NULL;
/**
 * A singlet providing access to information about
 * existing Automat instances.
 *<P>
 * It might not always be a singlet, however, so
 * for now we're going through an explicit instance() reference.
 *<P>
 * This can be invoked from various threads, so switches to the
 * Swing thread to notify it's own listeners.
 *
 * @author	Bob Jacobsen    Copyright (C) 2004, 2007
 * @version     $Revision: 17977 $
 */
// /*public*/ class AutomatSummary  {

/*private*/ AutomatSummary::AutomatSummary(QObject *parent ) : QObject(parent)
{
 self = NULL;
 automats = new QList<AbstractAutomaton*>();
 prop = new PropertyChangeSupport(this);
}
/*static*/ /*public*/ AutomatSummary* AutomatSummary::instance() {
    if (self == NULL) self = new AutomatSummary();
    return self;
}

///*public*/ void AutomatSummary::removePropertyChangeListener(PropertyChangeListener* p) { prop->removePropertyChangeListener(p); }
///*public*/ void AutomatSummary::addPropertyChangeListener(PropertyChangeListener* p) { prop->addPropertyChangeListener(p); }

/**
 * A newly-created AbstractAutomaton instance uses this method to
 * notify interested parties of it's existance.
 */
/*public*/ void AutomatSummary::_register(AbstractAutomaton* a)
{

    /*synchronized (automats)*/ {
        QMutexLocker locker (&mutex);
        automats->append(a);
    }

    //notify length changed
    //emit notify("Insert", QVariant(), VPtr<AbstractAutomaton>::asQVariant(a));
 prop->firePropertyChange("Insert", QVariant(), VPtr<AbstractAutomaton>::asQVariant(a));

}

/**
 * Just before exiting, an AbstractAutomaton instance uses this method to
 * notify interested parties of it's departure.
 */
/*public*/ void AutomatSummary::remove(AbstractAutomaton* a) {
    int index = indexOf(a);

    /*synchronized (automats)*/ {
        QMutexLocker locker (&mutex);

        automats->removeAt(index);
    }

    //notify length changed
    prop->firePropertyChange("Remove", QVariant(), QVariant(index));
}

/*public*/ int AutomatSummary::length() {
    int length;
    /*synchronized (automats)*/ {
        QMutexLocker locker (&mutex);

        length = automats->size();
    }
    return length;  // debugging value
}

/*public*/ AbstractAutomaton* AutomatSummary::get(int i) {
    AbstractAutomaton* retval;

    /*synchronized (automats)*/ {
        QMutexLocker locker (&mutex);

        retval = automats->at(i);
    }

    return retval;
}

/**
 * Provide a convenience method to look up
 * a managed object by it's name.
 * @since 1.7.3
 * @param name Name of the automat to be located
 * @return NULL if name not found
 */
/*public*/ AbstractAutomaton* AutomatSummary::get(QString name)
{
 AbstractAutomaton* a;
 /*synchronized (automats)*/
 {
  QMutexLocker locker (&mutex);

  for (int i=0; i<length(); i++) {
      a = automats->at(i);
      if (a->getName()==(name)) return a;
  }
 }
 return NULL;
}

/*public*/ int AutomatSummary::indexOf(AbstractAutomaton* a)
{
 int retval;
 /*synchronized (automats)*/
 {
  QMutexLocker locker (&mutex);

  retval = automats->indexOf(a);
 }
 return retval;
}

/**
 * An AbstractAutomaton instance uses this method to
 * notify interested parties that it's gone around it's
 * handle loop again.
 */
/*public*/ void AutomatSummary::loop(AbstractAutomaton* a)
{
 int i;
 /*synchronized (automats)*/
 {
  QMutexLocker locker (&mutex);

  i = automats->indexOf(a);
 }
 //notify("Count", QVariant(), QVariant(i));
 //emit notify("Count", QVariant(), QVariant(i));
 prop->firePropertyChange(new PropertyChangeEvent((QObject*)this, "Count", QVariant(), QVariant(i)));
}

//void AutomatSummary::notify(QString property, QVariant arg1, QVariant arg2){
//    Runnable* r = new Notifier(property, arg1, arg2);
//    //javax.swing.SwingUtilities.invokeLater(r); // ???
//}




//}

//    // initialize logging
//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(AutomatSummary.class.getName());
//}

///* @(#)AutomatSummary.java */
