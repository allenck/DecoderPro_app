#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <QObject>
#include "propertychangesupport.h"

class AppContext : public QObject
{
 Q_OBJECT
public:
 explicit AppContext(QObject *parent = nullptr);
 /*public*/ static /*final*/ QString EVENT_QUEUE_KEY;// = new StringBuffer("EventQueue");
 /*public*/ bool isDisposed();

 /**
  * If any <code>PropertyChangeListeners</code> have been registered,
  * the <code>changeSupport</code> field describes them.
  *
  * @see #addPropertyChangeListener
  * @see #removePropertyChangeListener
  * @see #firePropertyChange
  */

 /*public*/ static /*final*/ QString DISPOSED_PROPERTY_NAME;//; = "disposed";
 /*public*/ static /*final*/ QString GUI_DISPOSED;// = "guidisposed";
 /*public*/ /*final*/ static AppContext* getAppContext();

signals:

public slots:

private:
 /*private*/ PropertyChangeSupport* changeSupport;// = null;
 /*private*/ bool _isDisposed;// = false; // true if AppContext is disposed

#if 0
 /*private*/ static /*final*/ Map<ThreadGroup, AppContext> threadGroup2appContext =
         Collections.synchronizedMap(new IdentityHashMap<ThreadGroup, AppContext>());

 /**
  * Returns a set containing all <code>AppContext</code>s.
  */
 /*public*/ static QSet<AppContext*> getAppContexts() {
     return QSet<AppContext>(threadGroup2appContext.values());
 }
#endif
 /* The main "system" AppContext, used by everything not otherwise
    contained in another AppContext.
  */
 /*private*/ static AppContext* mainAppContext;// = null;
#if 0
 /*
  * The hash map associated with this AppContext.  A private delegate
  * is used instead of subclassing HashMap so as to avoid all of
  * HashMap's potentially risky methods, such as clear(), elements(),
  * putAll(), etc.
  */
 /*private*/ /*final*/ HashMap table = new HashMap();

 /*private*/ /*final*/ ThreadGroup threadGroup;
#endif
 /*
  * The total number of AppContexts, system-wide.  This number is
  * incremented at the beginning of the constructor, and decremented
  * at the end of dispose().  getAppContext() checks to see if this
  * number is 1.  If so, it returns the sole AppContext without
  * checking Thread.currentThread().
  */
 /*private*/ static int numAppContexts;



};

#endif // APPCONTEXT_H
