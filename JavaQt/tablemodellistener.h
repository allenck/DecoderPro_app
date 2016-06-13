#ifndef TABLEMODELLISTENER_H
#define TABLEMODELLISTENER_H
#include <QObject>
#include "eventlistener.h"
//#include "tablemodelevent.h"
#include "javaqt_global.h"

class TableModelEvent;
class JAVAQTSHARED_EXPORT TableModelListener : public EventListener
{
 Q_OBJECT

public:
    /**
     * This fine grain notification tells listeners the exact range
     * of cells, rows, or columns that changed.
     */
    /*public*/ virtual void tableChanged(TableModelEvent* /*e*/ = 0) {}
};

#endif // TABLEMODELLISTENER_H
