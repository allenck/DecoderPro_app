#ifndef ACTIVEFLAG_H
#define ACTIVEFLAG_H

#include <QObject>
#include "libPr3_global.h"


class LIBPR3SHARED_EXPORT ActiveFlag : public QObject
{
    Q_OBJECT
public:
    explicit ActiveFlag(QObject *parent = 0);
    static /*public*/ void setActive();
    static /*public*/ bool isActive();
signals:
    
public slots:
private:
    static /*private*/ bool flag;// = false;

};

#endif // ACTIVEFLAG_H
