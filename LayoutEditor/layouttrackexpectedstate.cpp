#include "layouttrackexpectedstate.h"
#include "layouttrack.h"
#include "layoutturnout.h"
/**
 * Retain a LayoutTrack and its expected state.
 *
 * @author Randall Wood Copyright 2017
 * @param <T> the supported type of LayoutTrack
 */
// /*public*/ class LayoutTrackExpectedState<T extends LayoutTrack> extends Bean implements ExpectedState<T, Integer> {

template<class T>
    /*public*/ LayoutTrackExpectedState<T>::LayoutTrackExpectedState(T layoutTrack, int state, QObject *parent): LayoutTrack(parent) {
        this->layoutTrack = layoutTrack;
        this->setExpectedState(state);
    }

    //@Override
template<class T>
    /*public*/ int LayoutTrackExpectedState<T>::getExpectedState()  {
        return state;
    }

    //@Override
template<class T>
    /*public*/ void LayoutTrackExpectedState<T>::setExpectedState(int state) throw (UnsupportedOperationException) {
        int old = this->state;
        this->state = state;
        this->propertyChangeSupport->firePropertyChange("expectedState", old, state);
    }

    //@Override
template<class T>
    /*public*/ T LayoutTrackExpectedState<T>::getObject() {
        return this->layoutTrack;
    }
template class LayoutTrackExpectedState<LayoutTurnout*>;
template class LayoutTrackExpectedState<LayoutTrack*>;
