#ifndef LISTDATAEVENT_H
#define LISTDATAEVENT_H
#include "eventobject.h"
#include "javaqt_global.h"

class JAVAQTSHARED_EXPORT ListDataEvent : public EventObject
{
    Q_OBJECT
public:
    //explicit ListDataEvent(QObject *parent = 0);
    /** Identifies one or more changes in the lists contents. */
    /*public*/ static /*final*/ const int CONTENTS_CHANGED = 0;
    /** Identifies the addition of one or more contiguous items to the list */
    /*public*/ static /*final*/ const int INTERVAL_ADDED = 1;
    /** Identifies the removal of one or more contiguous items from the list */
    /*public*/ static /*final*/ const int INTERVAL_REMOVED = 2;
    /*public*/ int getType();
    /*public*/ int getIndex0();
    /*public*/ int getIndex1();
    /*public*/ ListDataEvent(QObject* source, int type, int index0, int index1, QObject *parent = 0);
    /*public*/ QString toString();

signals:

public slots:
private:
    /*private*/ int type;
    /*private*/ int index0;
    /*private*/ int index1;

};

#endif // LISTDATAEVENT_H
