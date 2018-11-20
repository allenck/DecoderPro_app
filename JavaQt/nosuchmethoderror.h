#ifndef NOSUCHMETHODERROR_H
#define NOSUCHMETHODERROR_H

#include "exceptions.h"

class NoSuchMethodError : public Exception // IncompatibleClassChangeError
{
 //Q_OBJECT
public:
 explicit NoSuchMethodError(QString msg = "");

signals:

public slots:
};

#endif // NOSUCHMETHODERROR_H
