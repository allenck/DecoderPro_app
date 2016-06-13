#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <QObject>
#include "errormemo.h"

class ErrorMemo;
class ErrorHandler : public QObject
{
    Q_OBJECT
public:
    explicit ErrorHandler(QObject *parent = 0);
    /*public*/ void handle(ErrorMemo* e);
    /*public*/ void done();

signals:

public slots:
private:
 Logger log;
};

#endif // ERRORHANDLER_H
