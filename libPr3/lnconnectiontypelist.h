#ifndef LNCONNECTIONTYPELIST_H
#define LNCONNECTIONTYPELIST_H

#include <QObject>
#include "libPr3_global.h"


class LIBPR3SHARED_EXPORT LNConnectionTypeList : public QObject
{
    Q_OBJECT
public:
    explicit LNConnectionTypeList(QObject *parent = 0);
    /*public*/ QStringList getAvailableProtocolClasses();

signals:
    
public slots:
    
};

#endif // LNCONNECTIONTYPELIST_H
