#ifndef ABSTRACTMESSAGETESTBASE_H
#define ABSTRACTMESSAGETESTBASE_H

#include <QObject>
#include "abstractmessage.h"

class AbstractMessageTestBase : public QObject
{
    Q_OBJECT
public:
    explicit AbstractMessageTestBase(QObject *parent = nullptr);
    /*abstract*/ /*public*/ virtual void setUp() {}
public slots:
    /*public*/ void testCtor();
    /*public*/ void testToString();
    /*public*/ void testToMonitorString();

signals:

public slots:
protected:
    /*protected*/ AbstractMessage* m = nullptr; // set in setUp

};

#endif // ABSTRACTMESSAGETESTBASE_H
