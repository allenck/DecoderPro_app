#include "qualifiercombiner.h"
#include "propertychangesupport.h"
#include "valuequalifier.h"

//QualifierCombiner::QualifierCombiner(QObject *parent) :
//    Qualifier(parent)
//{
//}
/**
 * Force a set of Qualifiers to work in an AND relationship
 *
 * @author			Bob Jacobsen   Copyright (C) 2011
 * @version			$Revision: -1$
 *
 */
// /*public*/ class QualifierCombiner implements Qualifier, java.beans.PropertyChangeListener {

/*public*/ QualifierCombiner::QualifierCombiner( QList<Qualifier*>* qualifiers) {
    this->qualifiers = qualifiers;

    setWatchedAvailable(availableCombinedState());

}

/*public*/ void QualifierCombiner::propertyChange(PropertyChangeEvent* e) {
    if (e->getPropertyName()==("Available"))
        // this was a change, may want to change it back
        setWatchedAvailable(availableCombinedState());  // relies on non-propogation of null changes
}

/*protected*/ void QualifierCombiner::setWatchedAvailable(bool enable) {
    qualifiers->at(0)->setWatchedAvailable(enable);
}

/*protected*/ bool QualifierCombiner::availableCombinedState()
{
    foreach (Qualifier* q, *qualifiers)
    {
        if (! q->currentDesiredState()) return false;
    }
    return true;
}
