#ifndef BASE_H
#define BASE_H
#include "propertychangeprovider.h"
#include "exceptions.h"
#include "propertyvetoexception.h"
#include "namedbean.h"
//#include "femalesocket.h"
#include "femalesocketoperation.h"
//#include "conditionalng.h"
//#include "logixng.h"

class MaleSocket;
class PrintTreeSettings;
class MutableInt;
class PrintWriter;
class Category;
//class FemaleSocketOperation;
class FemaleSocket;
class LogixNG;
class ConditionalNG;
class RunnableWithBase;
/*public*/ /*static*/ class PrintTreeSettings {
 public:
    PrintTreeSettings() {}
    /*public*/ bool _printLineNumbers = false;
    /*public*/ bool _printErrorHandling = true;
    /*public*/ bool _printNotConnectedSockets = true;
    /*public*/ bool _printLocalVariables = true;
};

/**
 * The base interface for LogixNG expressions and actions.
 * Used to simplify the user interface.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
/*public*/ /*interface*/class Base : public PropertyChangeProvider {
 Q_INTERFACES(PropertyChangeProvider)
 public:

    /**
     * The name of the property child count.
     * To get the number of children, use the method getChildCount().
     * This constant is used in calls to firePropertyChange().
     * The class fires a property change then a child is added or removed.
     * <p>
     * If children are removed, the field oldValue of the PropertyChange event
     * must be a List&lt;FemaleSocket&gt; with the FemaleSockets that are
     * removed from the list so that the listener can unregister itself as a
     * listener of this female socket.
     * <p>
     * If children are added, the field newValue of the PropertyChange event
     * must be a List&lt;FemaleSocket&gt; with the FemaleSockets that are
     * added to the list so that the listener can register itself as a
     * listener of this female socket.
     */
    /*public*/ static /*final*/QString PROPERTY_CHILD_COUNT;// = "ChildCount";

    /**
     * The name of the property child reorder.
     * The number of children has remained the same, but the order of children
     * has changed.
     * <p>
     * The field newValue of the PropertyChange event must be a
     * List&lt;FemaleSocket&gt; with the FemaleSockets that are reordered so
     * that the listener can update the tree.
     */
    /*public*/ static /*final*/ QString PROPERTY_CHILD_REORDER;// = "ChildReorder";

    /**
     * The socket has been connected.
     * This constant is used in calls to firePropertyChange().
     * The socket fires a property change when it is connected or disconnected.
     */
    /*public*/ static /*final*/ QString PROPERTY_SOCKET_CONNECTED;// = "SocketConnected";

    /**
     * The socket has been disconnected.
     * This constant is used in calls to firePropertyChange().
     * The socket fires a property change when it is connected or disconnected.
     */
    /*public*/ static /*final*/ QString PROPERTY_SOCKET_DISCONNECTED;// = "SocketDisconnected";

    /**
     * The last result of the expression has changed.
     * This constant is used in calls to firePropertyChange().
     */
    /*public*/ static /*final*/ QString PROPERTY_LAST_RESULT_CHANGED;// = "LastResultChanged";

    /**
     * Constant representing an "connected" state of the socket
     */
    /*public*/ static /*final*/ const int SOCKET_CONNECTED = 0x02;

    /**
     * Constant representing an "disconnected" state of the socket
     */
    /*public*/ static /*final*/const int SOCKET_DISCONNECTED = 0x04;


    /**
     * Get the system name.
     * @return the system name
     */
    /*public*/ virtual QString getSystemName() const=0;

    /**
     * Get the user name.
     * @return the user name
     */
    //@CheckReturnValue
    //@CheckForNull
    /*public*/ virtual QString getUserName() const =0;

    /**
     * Get associated comment text.
     * A LogixNG comment can have multiple lines, separated with \n.
     *
     * @return the comment or null
     */
    //@CheckReturnValue
    //@CheckForNull
    /*public*/ virtual QString getComment()=0;

    /**
     * Get the user name.
     * @param s the new user name
     */
    /*public*/ virtual void setUserName(/*@CheckForNull*/ QString s) throw (NamedBean::BadUserNameException)=0;

    /**
     * Create a deep copy of myself and my children
     * The item needs to try to lookup itself in both systemNames and userNames
     * to see if the user has given a new system name and/or a new user name.If no new system name is given, an auto system name is used.
     * If no user name is given, a null user name is used.
     *
     * @param systemNames a map of old and new system name
     * @param userNames a map of old system name and new user name
     * @return a deep copy
     * @throws jmri.JmriException in case of an error
     */
    /*public*/ virtual Base* getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames)
            throw (JmriException)=0;

    /**
     * Do a deep copy of children from the original to me.
     *
     * @param original the item to copy from
     * @param systemNames a map of old and new system name
     * @param userNames a map of old system name and new user name
     * @return myself
     * @throws jmri.JmriException in case of an error
     */
    /*public*/ virtual Base* deepCopyChildren(
            Base* original,
            QMap<QString, QString> systemNames,
            QMap<QString, QString> userNames)
            throw (JmriException)=0;

    /**
     * Set associated comment text.
     * <p>
     * Comments can be any valid text.
     *
     * @param comment the comment or null to remove an existing comment
     */
    /*public*/ virtual void setComment(/*@CheckForNull*/ QString comment)=0;

    /**
     * Get a short description of this item.
     * @return a short description
     */
    /*default*/ /*public*/ QString getShortDescription() {
        return getShortDescription(/*Locale.getDefault()*/);
    }

    /**
     * Get a long description of this item.
     * @return a long description
     */
    /*default*/ /*public*/ /*virtual*/ QString getLongDescription() {
        return getLongDescription(QLocale());
    }

    /**
     * Get a short description of this item.
     * @param locale The locale to be used
     * @return a short description
     */
    /*public*/ virtual QString getShortDescription(QLocale locale)=0;

    /**
     * Get a long description of this item.
     * @param locale The locale to be used
     * @return a long description
     */
    /*public*/ virtual QString getLongDescription(QLocale locale)=0;

    /**
     * Get the ConditionalNG of this item.
     * @return the ConditionalNG that owns this item
     */
    /*public*/ virtual ConditionalNG* getConditionalNG()=0;

    /**
     * Get the LogixNG of this item.
     * @return the LogixNG that owns this item
     */
    /*public*/ virtual LogixNG* getLogixNG()=0;

    /**
     * Get the root of the tree that this item belongs to.
     * @return the top most item in the tree
     */
    /*public*/ virtual Base* getRoot()=0;

    /**
     * Get the parent.
     * <P>
     * The following rules apply
     * <ul>
     * <li>LogixNGs has no parent. The method throws an UnsupportedOperationException if called.</li>
     * <li>Expressions and actions has the male socket that they are connected to as their parent.</li>
     * <li>Male sockets has the female socket that they are connected to as their parent.</li>
     * <li>The parent of a female sockets is the LogixNG, expression or action that
     * has this female socket.</li>
     * <li>The parent of a male sockets is the same parent as the expression or
     * action that it contains.</li>
     * </ul>
     *
     * @return the parent of this object
     */
    /*public*/ virtual Base* getParent() const =0;

    /**
     * Set the parent.
     * <P>
     * The following rules apply
     * <ul>
     * <li>ExecutionGroups has no parent. The method throws an UnsupportedOperationException if called.</li>
     * <li>LogixNGs has the execution group as its parent.</li>
     * <li>Expressions and actions has the male socket that they are connected to as their parent.</li>
     * <li>Male sockets has the female socket that they are connected to as their parent.</li>
     * <li>The parent of a female sockets is the LogixNG, expression or action that
     * has this female socket.</li>
     * <li>The parent of a male sockets is the same parent as the expression or
     * action that it contains.</li>
     * </ul>
     *
     * @param parent the new parent of this object
     */
    /*public*/ virtual void setParent(Base* parent)=0;

    /**
     * Set the parent for all the children.
     *
     * @param errors a list of potential errors
     * @return true if success, false otherwise
     */
    /*public*/ virtual bool setParentForAllChildren(QList<QString> errors)=0;

    /**
     * Get a child of this item
     * @param index the index of the child to get
     * @return the child
     * @throws IllegalArgumentException if the index is less than 0 or greater
     * or equal with the value returned by getChildCount()
     */
    /*public*/ virtual FemaleSocket* getChild(int index)
            throw (IllegalArgumentException, UnsupportedOperationException)=0;

    /**
     * Get the number of children.
     * @return the number of children
     */
    /*public*/ virtual int getChildCount()=0;

    /**
     * Is the operation allowed on this child?
     * @param index the index of the child to do the operation on
     * @param oper the operation to do
     * @return true if operation is allowed, false otherwise
     */
    /*public*/ /*default*/ virtual bool isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper)=0;
    /**
     * Do an operation on a child
     * @param index the index of the child to do the operation on
     * @param oper the operation to do
     */
    /*public*/ virtual /*default*/ void doSocketOperation(int index, FemaleSocketOperation::TYPES oper)=0;

    /**
     * Get the category.
     * @return the category
     */
    /*public*/ virtual Category* getCategory()=0;

    /**
     * Is this item active? If this item is enabled and all the parents are
     * enabled, this item is active.
     * @return true if active, false otherwise.
     */
    /*public*/ virtual bool isActive()=0;

    /**
     * Setup this object and its children.
     * This method is used to lookup system names for child sockets, turnouts,
     * sensors, and so on.
     */
    /*public*/ virtual void setup()=0;

    /**
     * Deactivate this object, so that it releases as many resources as possible
     * and no longer effects others.
     * <p>
     * For example, if this object has listeners, after a call to this method it
     * should no longer notify those listeners. Any native or system-wide
     * resources it maintains should be released, including threads, files, etc.
     * <p>
     * It is an error to invoke any other methods on this object once dispose()
     * has been called. Note, however, that there is no guarantee about behavior
     * in that case.
     * <p>
     * Afterwards, references to this object may still exist elsewhere,
     * preventing its garbage collection. But it's formally dead, and shouldn't
     * be keeping any other objects alive. Therefore, this method should null
     * out any references to other objects that this object contained.
     */
    /*public*/ virtual void dispose()=0;  // remove _all_ connections!

    /**
     * Set whenether this object is enabled or disabled.
     * If the parent is disabled, this object must also be disabled, regardless
     * of this flag.
     *
     * @param enable true if this object should be enabled, false otherwise
     */
//    public void setEnabled(bool enable);

    /**
     * Determines whether this object is enabled.
     *
     * @return true if the object is enabled, false otherwise
     */
    /*public*/ /*default*/ bool isEnabled() {
        return true;
    }

    /**
     * Register listeners if this object needs that.
     * <P>
     * Important: This method may be called more than once. Methods overriding
     * this method must ensure that listeners are not registered more than once.
     */
    /*public*/ virtual void registerListeners()=0;

    /**
     * Unregister listeners if this object needs that.
     * <P>
     * Important: This method may be called more than once. Methods overriding
     * this method must ensure that listeners are not unregistered more than once.
     */
    /*public*/ virtual void unregisterListeners()=0;

    /**
     * Print the tree to a stream.
     *
     * @param writer the stream to print the tree to
     * @param indent the indentation of each level
     * @param lineNumber the line number
     */
    /*public*/ /*default*/ void printTree(
            PrintWriter* writer,
            QString indent,
            /*MutableInt*/int lineNumber) {
        printTree(new PrintTreeSettings(), writer, indent, lineNumber);
    }

    /**
     * Print the tree to a stream.
     *
     * @param settings settings for what to print
     * @param writer the stream to print the tree to
     * @param indent the indentation of each level
     * @param lineNumber the line number
     */
    /*public*/virtual void printTree(
            PrintTreeSettings* settings,
            PrintWriter* writer,
            QString indent,
            /*MutableInt*/int lineNumber) =0;

    /**
     * Print the tree to a stream.
     *
     * @param locale The locale to be used
     * @param writer the stream to print the tree to
     * @param indent the indentation of each level
     * @param lineNumber the line number
     */
    /*public*/ /*default*/ void printTree(
            QLocale locale,
            PrintWriter* writer,
            QString indent,
            /*MutableInt*/int lineNumber) {
        printTree(new PrintTreeSettings(), locale, writer, indent, lineNumber);
    }

    /**
     * Print the tree to a stream.
     *
     * @param settings settings for what to print
     * @param locale The locale to be used
     * @param writer the stream to print the tree to
     * @param indent the indentation of each level
     * @param lineNumber the line number
     */
    /*public*/ virtual void printTree(
            PrintTreeSettings* settings,
            QLocale locale,
            PrintWriter* writer,
            QString indent,
            /*MutableInt*/int lineNumber)=0;

    /**
     * Print the tree to a stream.
     *
     * @param settings settings for what to print
     * @param locale The locale to be used
     * @param writer the stream to print the tree to
     * @param indent the indentation of each level
     * @param currentIndent the current indentation
     * @param lineNumber the line number
     */
    /*public*/ virtual void printTree(
            PrintTreeSettings* settings,
            QLocale locale,
            PrintWriter* writer,
            QString indent,
            QString currentIndent,
            /*MutableInt*/int lineNumber)=0;

    /**
     * Navigate the LogixNG tree.
     *
     * @param level  The current recursion level for debugging.
     * @param bean   The named bean that is the object of the search.
     * @param report A list of NamedBeanUsageReport usage reports.
     * @param cdl    The current ConditionalNG bean.  Null for Module searches since there is no conditional
     */
    /*public*/ virtual void getUsageTree(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl)=0;

    /**
     * Add a new NamedBeanUsageReport to the report list if there are any matches in this action or expresssion.
     * <p>
     * NamedBeanUsageReport Usage keys:
     * <ul>
     * <li>LogixNGAction</li>
     * <li>LogixNGExpression</li>
     * </ul>
     *
     * @param level  The current recursion level for debugging.
     * @param bean   The named bean that is the object of the search.
     * @param report A list of NamedBeanUsageReport usage reports.
     * @param cdl    The current ConditionalNG bean.  Null for Module searches since there is no conditional
     */
    /*public*/ virtual void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl)=0;

    /**
     * Request a call-back when a bound property changes. Bound properties are
     * the known state, commanded state, user and system names.
     *
     * @param listener    The listener. This may change in the future to be a
     *                        subclass of NamedProprtyChangeListener that
     *                        carries the name and listenerRef values internally
     * @param name        The name (either system or user) that the listener
     *                        uses for this namedBean, this parameter is used to
     *                        help determine when which listeners should be
     *                        moved when the username is moved from one bean to
     *                        another
     * @param listenerRef A textual reference for the listener, that can be
     *                        presented to the user when a delete is called
     */
    /*public*/ virtual void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef)=0;

    /**
     * Request a call-back when a bound property changes. Bound properties are
     * the known state, commanded state, user and system names.
     *
     * @param propertyName The name of the property to listen to
     * @param listener     The listener. This may change in the future to be a
     *                         subclass of NamedProprtyChangeListener that
     *                         carries the name and listenerRef values
     *                         internally
     * @param name         The name (either system or user) that the listener
     *                         uses for this namedBean, this parameter is used
     *                         to help determine when which listeners should be
     *                         moved when the username is moved from one bean to
     *                         another
     * @param listenerRef  A textual reference for the listener, that can be
     *                         presented to the user when a delete is called
     */
    /*public*/ virtual void addPropertyChangeListener(/*@Nonnull*/ QString propertyName, /*@Nonnull*/ PropertyChangeListener* listener,
            QString name, QString listenerRef)=0;

    /*public*/ virtual void updateListenerRef(/*@Nonnull*/ PropertyChangeListener* l, QString newName)=0;

    /*public*/ virtual void vetoableChange(/*@Nonnull*/ PropertyChangeEvent* evt) throw (PropertyVetoException)=0;

    /**
     * Get the textual reference for the specific listener
     *
     * @param l the listener of interest
     * @return the textual reference
     */
    //@CheckReturnValue
    /*public*/ virtual QString getListenerRef(/*@Nonnull*/ PropertyChangeListener* l)=0;

    /**
     * Returns a list of all the listeners references
     *
     * @return a list of textual references
     */
    //@CheckReturnValue
    /*public*/ virtual QList<QString> getListenerRefs()=0;

    /**
     * Returns a list of all the listeners references for this object
     * and all its children.
     *
     * @param list a list of textual references
     */
    //@CheckReturnValue
    /*public*/ virtual void getListenerRefsIncludingChildren(QList<QString> list)=0;

    /**
     * Number of current listeners. May return -1 if the information is not
     * available for some reason.
     *
     * @return the number of listeners.
     */
    //@CheckReturnValue
    /*public*/ virtual int getNumPropertyChangeListeners()=0;

    /**
     * Get a list of all the property change listeners that are registered using
     * a specific name
     *
     * @param name The name (either system or user) that the listener has
     *                 registered as referencing this namedBean
     * @return empty list if none
     */
    //@CheckReturnValue
    //@Nonnull
    /*public*/ virtual QList<PropertyChangeListener*> getPropertyChangeListenersByReference(/*@Nonnull*/ QString name)=0;

    /*public*/ /*interface*/class RunnableWithBase {
     public:
        /*public*/ void run(/*@Nonnull*/ Base* b);
    };

    /**
     * Do something on every item in the sub tree of this item.
     * @param r the action to do on all items.
     */
    /*public*/ virtual/*default*/ void forEntireTree(RunnableWithBase* r) {
        r->run(this);
        for (int i=0; i < getChildCount(); i++) {
            ((Base*)getChild(i))->forEntireTree(r);
        }
    }

    /*public*/ /*final*/ QString PRINT_LINE_NUMBERS_FORMAT = "%1:  ";

    /*public*/ virtual QString toString()=0;

    virtual QObject* self() =0;
};

Q_DECLARE_INTERFACE(Base, "Base")
#endif // BASE_H