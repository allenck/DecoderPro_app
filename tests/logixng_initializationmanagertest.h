#ifndef LOGIXNG_INITIALIZATIONMANAGERTEST_H
#define LOGIXNG_INITIALIZATIONMANAGERTEST_H

#include <QObject>
#include "atomicboolean.h"
#include "actionatomicboolean.h"

class LogixNG_InitializationManagerTest : public QObject
{
    Q_OBJECT
public:
    explicit LogixNG_InitializationManagerTest(QObject *parent = nullptr);

public slots:
    /*public*/  void testInitialization() /*throws SocketAlreadyConnectedException */;
    Q_INVOKABLE /*public*/  void setUp();
    Q_INVOKABLE /*public*/  void tearDown();
signals:

private:
    QList<AtomicBoolean*> abList = QList<AtomicBoolean*>();
    /*private*/ AtomicBoolean *getAB();
    /*private*/ bool checkAB();

};
/*private*/ /*static*/ /*final*/ class MyAction : public ActionAtomicBoolean {
Q_OBJECT
    /*private*/ /*final*/ AtomicBoolean* _ab;
    /*private*/ /*final*/ PrintWriter* _printWriter;
    /*private*/ /*final*/ long _delay;
 public:
    /*public*/  MyAction(
            QString userName,
            AtomicBoolean* ab,
            PrintWriter* printWriter,
            long delay) : ActionAtomicBoolean(ab, false);
    /*public*/  void execute()override;
    /*public*/  static LogixNG* getLogixNG(
            QString systemName,
            QString userName,
            AtomicBoolean* ab,
            PrintWriter* printWriter,
            long delay,
            int threadID)
            /*throws SocketAlreadyConnectedException*/ ;
    /*public*/  static LogixNG* getLogixNG(
            QString systemName,
            QString userName,
            AtomicBoolean* ab,
            PrintWriter* printWriter,
            long delay,
            int threadID)
            /*throws SocketAlreadyConnectedException*/;

};

#endif // LOGIXNG_INITIALIZATIONMANAGERTEST_H
