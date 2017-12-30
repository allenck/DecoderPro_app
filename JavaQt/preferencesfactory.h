#ifndef PREFERENCESFACTORY_H
#define PREFERENCESFACTORY_H

class Preferences;
/**
 * A factory object that generates Preferences objects.  Providers of
 * new {@link Preferences} implementations should provide corresponding
 * <tt>PreferencesFactory</tt> implementations so that the new
 * <tt>Preferences</tt> implementation can be installed in place of the
 * platform-specific default implementation.
 *
 * <p><strong>This class is for <tt>Preferences</tt> implementers only.
 * Normal users of the <tt>Preferences</tt> facility should have no need to
 * consult this documentation.</strong>
 *
 * @author  Josh Bloch
 * @see     Preferences
 * @since   1.4
 */
/*public*/ /*interface*/class PreferencesFactory {
public:
    /**
     * Returns the system root preference node.  (Multiple calls on this
     * method will return the same object reference.)
     * @return the system root preference node
     */
    virtual Preferences* systemRoot() {return NULL;}

    /**
     * Returns the user root preference node corresponding to the calling
     * user.  In a server, the returned value will typically depend on
     * some implicit client-context.
     * @return the user root preference node corresponding to the calling
     * user
     */
    virtual Preferences* userRoot() {return NULL;}
};

#endif // PREFERENCESFACTORY_H
