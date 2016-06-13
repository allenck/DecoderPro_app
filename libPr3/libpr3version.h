#ifndef LIBPR3VERSION_H
#define LIBPR3VERSION_H

#include <QObject>
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT  libPr3Version : public QObject
{
 Q_OBJECT
public:
 explicit libPr3Version(QObject *parent = 0);
 static QString buildVersion();
    
signals:
    
public slots:
    
};

#endif // LIBPR3VERSION_H
