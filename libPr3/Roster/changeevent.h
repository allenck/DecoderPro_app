#ifndef CHANGEEVENT_H
#define CHANGEEVENT_H
#include "eventobject.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT ChangeEvent : public EventObject
{
    Q_OBJECT
public:
    //explicit ChangeEvent(QObject *parent = 0);
    /*public*/ ChangeEvent(QObject* source, QObject *parent = 0);

signals:

public slots:

};

#endif // CHANGEEVENT_H
