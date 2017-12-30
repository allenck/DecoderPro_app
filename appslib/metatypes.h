#ifndef METATYPES_H
#define METATYPES_H

#include <QObject>
#include "appslib_global.h"

class APPSLIBSHARED_EXPORT Metatypes : public QObject
{
    Q_OBJECT
public:
    explicit Metatypes(QObject *parent = 0);
 static bool done;
signals:

public slots:

};

#endif // METATYPES_H
