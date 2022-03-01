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

    friend class DFAADefaultFemaleAnalogActionSocket;
    friend class DFAA2DefaultFemaleAnalogActionSocket;
};

class DFAADefaultFemaleAnalogActionSocket : public DefaultFemaleAnalogActionSocket
{
    Q_OBJECT
    DefaultFemaleAnalogActionSocketTest* test;
public:
    DFAADefaultFemaleAnalogActionSocket(Base* parentObject, FemaleSocketListener* listener, QString name,DefaultFemaleAnalogActionSocketTest* test=nullptr)
        : DefaultFemaleAnalogActionSocket(parentObject, listener, name ,test)
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

class DFAA2DefaultFemaleAnalogActionSocket : public DefaultFemaleAnalogActionSocket
{
    Q_OBJECT
    DefaultFemaleAnalogActionSocketTest* test;

public:
    DFAA2DefaultFemaleAnalogActionSocket(Base* parentObject, FemaleSocketListener* listener, QString name,DefaultFemaleAnalogActionSocketTest* test)
        : DefaultFemaleAnalogActionSocket(parentObject, listener, name ,test)
    { this->test = test;}
    //@Override
    /*public*/  void connected(FemaleSocket* socket) {
    test->flag->set(true);
    }

    //@Override
    /*public*/  void disconnected(FemaleSocket* socket) {
    test->flag->set(true);
    }
};

#endif // DEFAULTFEMALEANALOGACTIONSOCKETTEST_H
