#ifndef LOGIXACTIONTEST_H
#define LOGIXACTIONTEST_H

#include <QObject>
#include "exceptions.h"

class LogixActionTest : public QObject
{
 Q_OBJECT
public:
 explicit LogixActionTest(QObject *parent = nullptr);
 Q_INVOKABLE/*public*/ void setUp();
 Q_INVOKABLE/*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testLogixAction() throw (Exception);

};

#endif // LOGIXACTIONTEST_H
