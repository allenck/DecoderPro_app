#ifndef LISTSELECTIONEVENT_H
#define LISTSELECTIONEVENT_H
#include "eventobject.h"

class ListSelectionEvent : public EventObject
{
public:
 /*public*/ ListSelectionEvent(QObject* source, int firstIndex, int lastIndex,
                           bool isAdjusting);
 /*public*/ int getFirstIndex() ;
 /*public*/ int getLastIndex();
 /*public*/ bool getValueIsAdjusting();
 /*public*/ QString toString();


private:
 /*private*/ int firstIndex;
 /*private*/ int lastIndex;
 /*private*/ bool isAdjusting;


};

#endif // LISTSELECTIONEVENT_H
