#ifndef SYSTEMCONNECTIONACTION_H
#define SYSTEMCONNECTIONACTION_H
#include "systemconnectionmemo.h"
#include "exceptions.h"
#include "class.h"
#include <QSet>

/**
 * Interface for a {@link javax.swing.Action} that is bound to a
 * {@link jmri.jmrix.SystemConnectionMemo}.
 *
 * @author Randall Wood (c) 2016
 */
/*public*/ /*interface*/class SystemConnectionAction : public QObject
{
 Q_OBJECT
public:
 SystemConnectionAction(QObject* parent = 0) : QObject(parent) {}
 ~SystemConnectionAction() {}
 SystemConnectionAction(const SystemConnectionAction&) : QObject() {}
    /**
     * Get the {@link jmri.jmrix.SystemConnectionMemo} this action is bound to.
     *
     * @return the SystemConnectionMemo or null if not bound.
     */
    //@CheckForNull
    /*public*/ virtual SystemConnectionMemo* getSystemConnectionMemo() {return NULL;}

    /**
     * Set the {@link jmri.jmrix.SystemConnectionMemo} this action is bound to.
     * <p>
     * Implementing classes may throw an IllegalArgumentException if the
     * implementing class requires a specific subclass of SystemConnectionMemo.
     *
     * @param memo the SystemConnectionMemo
     * @throws IllegalArgumentException if the SystemConnectionMemo is invalid
     */
    /*public*/ virtual void setSystemConnectionMemo(/*@Nonnull*/ SystemConnectionMemo* memo) throw (IllegalArgumentException) {}

    /**
     * Get a list of {@link jmri.jmrix.SystemConnectionMemo} subclasses that the
     * implementing class accepts.
     * <p>
     * If the implementing class is a subclass of a class that does accept
     * SystemConnectionMemos, but the implementing class does not accept any,
     * return an empty array instead of null.</p>
     *
     * @return Set of SystemConnectionMemo subclasses or empty array.
     */
    //@Nonnull
    /*public*/ virtual QSet</*Class<? extends SystemConnectionMemo>*/Class*> getSystemConnectionMemoClasses() {return QSet<Class*>();}
};
Q_DECLARE_METATYPE(SystemConnectionAction)
#endif // SYSTEMCONNECTIONACTION_H
