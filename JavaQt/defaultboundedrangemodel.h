#ifndef DEFAULTBOUNDEDRANGEMODEL_H
#define DEFAULTBOUNDEDRANGEMODEL_H

#include "boundedrangemodel.h"
#include <QString>
#include "javaqt_global.h"

class ChangeEvent;
//class EventListenerList;
class JAVAQTSHARED_EXPORT DefaultBoundedRangeModel : public BoundedRangeModel
{
public:
    DefaultBoundedRangeModel();
    /*public*/ DefaultBoundedRangeModel(int value, int extent, int min, int max);
    /*public*/ int getValue() ;
    /*public*/ int getExtent();
    /*public*/ int getMinimum();
    /*public*/ int getMaximum();
    /*public*/ void setValue(int n);
    /*public*/ void setExtent(int n);
    /*public*/ void setMinimum(int n);
    /*public*/ void setMaximum(int n);
    /*public*/ void setValueIsAdjusting(bool b) ;
    /*public*/ bool getValueIsAdjusting();
    /*public*/ void setRangeProperties(int newValue, int newExtent, int newMin, int newMax, bool adjusting);
    /*public*/ void addChangeListener(ChangeListener* l) ;
    /*public*/ void removeChangeListener(ChangeListener* l);
//    /*public*/ ChangeListener[] getChangeListeners();
    /*public*/ QString toString();
private:
    /*private*/ int value;// = 0;
    /*private*/ int extent;// = 0;
    /*private*/ int min;// = 0;
    /*private*/ int max;// = 100;
    /*private*/ bool isAdjusting;// = false;

protected:
    /**
     * Only one <code>ChangeEvent</code> is needed per model instance since the
     * event's only (read-only) state is the source property.  The source
     * of events generated here is always "this".
     */
    /*protected*/ /*transient*/ ChangeEvent* changeEvent;// = NULL;
    /** The listeners waiting for model changes. */
//    /*protected*/ EventListenerList* listenerList;// = new EventListenerList();
    /*protected*/ void fireStateChanged();

};

#endif // DEFAULTBOUNDEDRANGEMODEL_H
