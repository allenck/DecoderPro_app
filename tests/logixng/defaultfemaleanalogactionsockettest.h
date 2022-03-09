#ifndef DEFAULTFEMALEANALOGACTIONSOCKETTEST_H
#define DEFAULTFEMALEANALOGACTIONSOCKETTEST_H

#include "femalesockettestbase.h"
#include "manager.h"
#include "defaultfemaleanalogactionsocket.h"
#include "analogactionmemory.h"

class Memory;
class MyAnalogActionMemory;

class DefaultFemaleAnalogActionSocketTest : public FemaleSocketTestBase
{
    Q_OBJECT
public:
    DefaultFemaleAnalogActionSocketTest(QObject* parent = nullptr);
//    /*public*/ /*final*/ ExpectedException* thrown = ExpectedException::none();
      Q_INVOKABLE /*public*/  void setUp();
      Q_INVOKABLE /*public*/  void tearDown();

public slots:
//    /*public*/  void testBundleClass();
    /*public*/  void testGetName();
    /*public*/  void testGetDescription();
    /*public*/  void testSetValue() /*throws Exception*/;
    /*public*/  void testGetConnectableClasses();
//    /*public*/  void testCategory();

private:
    /*private*/ QString _memorySystemName;
    /*private*/ Memory* _memory;
    /*private*/ MyAnalogActionMemory* _action;

protected:
    /*protected*/ Manager/*<? extends NamedBean>*/* getManager()override;
    /*protected*/ FemaleSocket* getFemaleSocket(QString name)override;
    /*protected*/ bool hasSocketBeenSetup()override;

    friend class DFAAFemaleSocketListener;
    friend class DFAA2FemaleSocketListener;
};

class DFAAFemaleSocketListener : public QObject, public FemaleSocketListener
{
    Q_OBJECT
  Q_INTERFACES(FemaleSocketListener)
    DefaultFemaleAnalogActionSocketTest* test;
public:
    DFAAFemaleSocketListener(DefaultFemaleAnalogActionSocketTest* test=nullptr)
        : QObject()
    { this->test = test; }
    //@Override
    /*public*/  void connected(FemaleSocket* socket) {
    }

    //@Override
    /*public*/  void disconnected(FemaleSocket* socket) {
    }
};

/*private*/ class MyAnalogActionMemory : public AnalogActionMemory {
    Q_OBJECT
    /*private*/ bool _hasBeenSetup = false;
  public:
    /*public*/ MyAnalogActionMemory(QString systemName) : AnalogActionMemory(systemName, nullptr)
    {
     //super(systemName, null);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void setup() override {
        _hasBeenSetup = true;
    }
 friend class DefaultFemaleAnalogActionSocketTest;
};

class DFAA2FemaleSocketListener : public QObject, public FemaleSocketListener
{
    Q_OBJECT
  Q_INTERFACES(FemaleSocketListener)
    DefaultFemaleAnalogActionSocketTest* test;

public:
    DFAA2FemaleSocketListener(DefaultFemaleAnalogActionSocketTest* test)
        : QObject()
    { this->test = test;}
    //@Override
    /*public*/  void connected(FemaleSocket* socket) override{
    test->flag->set(true);
    }

    //@Override
    /*public*/  void disconnected(FemaleSocket* socket) override {
    test->flag->set(true);
    }
};

#endif // DEFAULTFEMALEANALOGACTIONSOCKETTEST_H
