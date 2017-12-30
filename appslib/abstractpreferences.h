#ifndef ABSTRACTPREFERENCES_H
#define ABSTRACTPREFERENCES_H
#include "preferences.h"
#include "nodechangeevent.h"
#include "exceptions.h"

class NodeAddedEvent;
class NodeRemovedEvent;
class NodeChangeEvent;
class PreferenceChangeEvent;
class EventObject;
class StringTokenizer;
class PreferenceChangeListener;
class AbstractPreferences : public Preferences
{
 Q_OBJECT
public:
 AbstractPreferences();
 /*public*/ void put(QString key, QString value);
 /*public*/ QString get(QString key, QString def);
 /*public*/ void remove(QString key);
 /*public*/ void clear();
 /*public*/ void putInt(QString key, int value);
 /*public*/ int getInt(QString key, int def);
 /*public*/ void putLong(QString key, long value);
 /*public*/ QString name();
 /*public*/ QString absolutePath();
 /*public*/ bool isUserNode();
 /*public*/ Preferences* node(QString path);
 /*public*/ QString toString();
 /*public*/ bool nodeExists(QString path) throw (BackingStoreException);
 /*public*/ void sync() throw (BackingStoreException);
 /*public*/ void flush() throw (BackingStoreException);
 /*public*/ void removeNode() throw (BackingStoreException);
 /*public*/ void exportNode(QTextStream* os) throw (IOException, BackingStoreException);
 /*public*/ void exportSubtree(QTextStream* os) throw (IOException, BackingStoreException);
 /*public*/ Preferences* parent();
 /*public*/ QStringList childrenNames() throw (BackingStoreException);
 /*public*/ long getLong(QString key, long def);
 /*public*/ void putBoolean(QString key, bool value);
 /*public*/ bool getBoolean(QString key, bool def);
 /*public*/ void putFloat(QString key, float value);
 /*public*/ float getFloat(QString key, float def);
 /*public*/ void putDouble(QString key, double value);
 /*public*/ double getDouble(QString key, double def);
 /*public*/ QStringList keys() throw (BackingStoreException);

signals:
 void notifyPreferenceChanged(PreferenceChangeEvent*);
 void notifyNodeRemoved(NodeRemovedEvent*);
 void notifyNodeAdded(NodeAddedEvent*);

private:
 /**
  * Our name relative to parent.
  */
 /*private*/ /*final*/ QString _name;

 /**
  * Our absolute path name.
  */
 /*private*/ /*final*/ QString _absolutePath;

 /**
  * Our parent node.
  */
 /*final*/ AbstractPreferences* _parent;

 /**
  * Our root node.
  */
 /*private*/ /*final*/ AbstractPreferences* root; // Relative to this node


 /**
  * All known unremoved children of this node.  (This "cache" is consulted
  * prior to calling childSpi() or getChild().
  */
 /*private*/ QMap<QString, AbstractPreferences*>* kidCache;// = new HashMap<>();

 /**
  * This field is used to keep track of whether or not this node has
  * been removed.  Once it's set to true, it will never be reset to false.
  */
 /*private*/ bool removed;// = false;

 /**
  * Registered preference change listeners.
  */
 // /*private*/ QList<PreferenceChangeListener*>* prefListeners;// =     new PreferenceChangeListener[0];
 // NOTE: see notifyPreferenceChanged

 /**
  * Registered node change listeners.
  */
 // /*private*/ QList<NodeChangeListener*>* nodeListeners;// = new NodeChangeListener[0];
 // Note: see notifyNodeRemoved
 /*private*/ void enqueuePreferenceChangeEvent(QString key, QString newValue);
 /*private*/ Preferences* node(StringTokenizer* path);
 /*private*/ void enqueueNodeAddedEvent(Preferences* child);
 /*private*/ static /*final*/ QLinkedList<EventObject*>* eventQueue;// = new QLinkedList<EventObject*>();
 /*private*/ void sync2() throw (BackingStoreException);
 /*private*/ void flush2() throw (BackingStoreException);
 /*private*/ bool nodeExists(StringTokenizer* path) throw (BackingStoreException);
 /*private*/ void removeNode2() throw (BackingStoreException);
 /*private*/ void enqueueNodeRemovedEvent(Preferences* child);
 /*private*/ static /*final*/ QStringList EMPTY_STRING_ARRAY;// = new String[0];


protected:
 /**
  * An object whose monitor is used to lock this node.  This object
  * is used in preference to the node itself to reduce the likelihood of
  * intentional or unintentional denial of service due to a locked node.
  * To avoid deadlock, a node is <i>never</i> locked by a thread that
  * holds a lock on a descendant of that node.
  */
 /*protected*/ /*final*/ QObject* lock;// = new Object();

 /**
  * This field should be <tt>true</tt> if this node did not exist in the
  * backing store prior to the creation of this object.  The field
  * is initialized to false, but may be set to true by a subclass
  * constructor (and should not be modified thereafter).  This field
  * indicates whether a node change event should be fired when
  * creation is complete.
  */
 /*protected*/ bool newNode;// = false;
 /*protected*/ AbstractPreferences(AbstractPreferences* parent, QString name);
 /*protected*/ /*abstract*/ virtual void putSpi(QString key, QString value);
 /*protected*/ /*abstract*/ virtual QString getSpi(QString key);
 /*protected*/ /*abstract*/ virtual void removeSpi(QString key);
 /*protected*/ /*abstract*/ virtual void removeNodeSpi()throw (BackingStoreException);
 /*protected*/ /*abstract*/ virtual QStringList keysSpi()throw (BackingStoreException);
 /*protected*/ /*abstract*/ virtual QStringList childrenNamesSpi() throw (BackingStoreException);
 /*protected*/ /*abstract*/ virtual AbstractPreferences* childSpi(QString name);
 /*protected*/ /*abstract*/ virtual void flushSpi() throw (BackingStoreException);
 /*protected*/ bool isRemoved();
 /*protected*/ /*abstract*/ virtual void syncSpi() throw (BackingStoreException);
 /*protected*/ AbstractPreferences* getChild(QString nodeName) throw (BackingStoreException);
 /*protected*/ /*final*/ QList<AbstractPreferences*> cachedChildren();
 /*private*/ static /*final*/ QList<AbstractPreferences*> EMPTY_ABSTRACT_PREFS_ARRAY;//= new AbstractPreferences[0];


friend class JmriPreferencesprovider;
friend class EventDispatchThread;
friend class XmlSupport;
};
/**
 * These two classes are used to distinguish NodeChangeEvents on
 * eventQueue so the event dispatch thread knows whether to call
 * childAdded or childRemoved.
 */
/*private*/ class NodeAddedEvent : public NodeChangeEvent
{
 Q_OBJECT
    /*private*/ /*static*/ /*final*/ long serialVersionUID = -6743557530157328528L;
public:
    NodeAddedEvent(Preferences* parent, Preferences* child) : NodeChangeEvent(parent, child)
    {
        //super(parent, child);
    }
};

/*private*/ class NodeRemovedEvent : public  NodeChangeEvent
{
 Q_OBJECT
    /*private*/ /*static*/ /*final*/ long serialVersionUID = 8735497392918824837L;
public:
    NodeRemovedEvent(Preferences* parent, Preferences* child) : NodeChangeEvent(parent, child) {
        //super(parent, child);
    }
};

#endif // ABSTRACTPREFERENCES_H
