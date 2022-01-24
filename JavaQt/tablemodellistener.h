#ifndef TABLEMODELLISTENER_H
#define TABLEMODELLISTENER_H
#include <QObject>
#include "eventlistener.h"
//#include "tablemodelevent.h"
#include "javaqt_global.h"

class TableModelEvent;
class JAVAQTSHARED_EXPORT TableModelListener : public EventListener
{
 //Q_OBJECT
 Q_INTERFACES(EventListener)
public:
    /**
     * This fine grain notification tells listeners the exact range
     * of cells, rows, or columns that changed.
     */
    /*public*/ virtual void tableChanged(TableModelEvent* /*e*/ = 0) {}
    QObject* self() {return (QObject*)this;}
};
Q_DECLARE_INTERFACE(TableModelListener, "TableModelListener")
#endif // TABLEMODELLISTENER_H
