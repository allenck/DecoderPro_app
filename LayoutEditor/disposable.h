#ifndef DISPOSABLE_H
#define DISPOSABLE_H
#include <QtCore>

/**
 * Interface that indicates that a class has a {@link #dispose()} method that
 * can be called without arguments.
 * <p>
 * Notably, when classes with this method are removed from the
 * {@link jmri.InstanceManager}, this method is called on those classes to allow
 * them to take any required actions when removed from the InstanceManager.
 *
 * @author Randall Wood Copyright 2017
 */
/*public*/ /*interface*/ class Disposable {

    /**
     * Called when disposing of a disposable.
     * <p>
     * <strong>Note</strong> there are no assurances this method will not be
     * called multiple times against a single instance of this Disposable. It is
     * the responsibility of this Disposable to protect itself and the
     * application from ensuring that calling this method multiple times has no
     * unwanted side effects.
     */
    virtual /*public*/ void dispose() =0;
};
Q_DECLARE_INTERFACE(Disposable, "Disposable")
#endif // DISPOSABLE_H
