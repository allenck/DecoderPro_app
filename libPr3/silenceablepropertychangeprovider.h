#ifndef SILENCEABLEPROPERTYCHANGEPROVIDER_H
#define SILENCEABLEPROPERTYCHANGEPROVIDER_H
#include "propertychangeprovider.h"

/**
 * Sometimes an external object needs to be able to mute property changes to
 * prevent bottlenecks in constrained systems (e.g. when reading a file that may
 * add a large number of Turnouts or Sensors to JMRI's internal representation
 * of the model railroad).
 *
 * @author Randall Wood Copyright 2020
 */
/*public*/ /*interface*/ class SilenceablePropertyChangeProvider : PropertyChangeProvider {
    Q_INTERFACES(PropertyChangeProvider)
 public:
    /**
     * Suppress sending {@link PropertyChangeEvent}s for the named property.
     * <p>
     * Stopping the suppression of sending change events may send a
     * PropertyChangeEvent if the property changed while silenced, but otherwise
     * should not fire a PropertyChangeEvent.
     *
     * @param propertyName the name of the property to mute
     * @param silenced     true if events are to be suppressed; false otherwise
     * @throws IllegalArgumentException if propertyName represents a property
     *                                  that should not be silenced
     */
  /*public*/ virtual void setPropertyChangesSilenced(/*@Nonnull*/ QString /*propertyName*/, bool /*silenced*/) {}
};
Q_DECLARE_INTERFACE(SilenceablePropertyChangeProvider, "SilenceablePropertyChangeProvider")
#endif // SILENCEABLEPROPERTYCHANGEPROVIDER_H
