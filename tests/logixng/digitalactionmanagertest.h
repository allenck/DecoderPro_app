#ifndef DIGITALACTIONMANAGERTEST_H
#define DIGITALACTIONMANAGERTEST_H

#include <abstractmanagertestbase.h>
#include "abstractbase.h"
#include "digitalactionbean.h"

class MyAction03;
class DigitalActionManager;
class DigitalActionManagerTest : public AbstractManagerTestBase
{
  Q_OBJECT
 public:
  explicit DigitalActionManagerTest(QObject *parent = nullptr) : AbstractManagerTestBase(parent) {}
  Q_INVOKABLE /*public*/  void setUp();
  Q_INVOKABLE /*public*/  void tearDown();

 public slots:
  /*public*/  void testRegisterAction();
  /*public*/  void testGetBeanTypeHandled();
  /*public*/  void testInstance();

 private:
  /*private*/ DigitalActionManager* _m;

};

/*private*/ /*static*/ class MyAction03 : public AbstractBase, public DigitalActionBean {
Q_OBJECT
  Q_INTERFACES(DigitalActionBean)
 public:
    /*public*/  MyAction03(QString sys) /*throws BadSystemNameException*/ : AbstractBase(sys) {
        //super(sys);
   setObjectName("MyAction");
    }

  QObject* bself() override{return (QObject*)this;}
 protected:
    //@Override
    /*protected*/ void registerListenersForThisClass() override{
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*protected*/ void unregisterListenersForThisClass() override{
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*protected*/ void disposeMe() override{
        throw new UnsupportedOperationException("Not supported");
    }
public:
    //@Override
    /*public*/  void setState(int s) /*throws JmriException*/override {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  int getState() override{
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  QString getBeanType() override{
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  QString getShortDescription(QLocale locale) override{
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  QString getLongDescription(QLocale locale) override{
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  Base* getParent() {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  void setParent(Base* parent)override {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  FemaleSocket* getChild(int index)/* throws IllegalArgumentException, UnsupportedOperationException*/override {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  int getChildCount()override {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  Category* getCategory() override{
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  void setup() override{
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  void execute() /*throws JmriException*/ override{
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  Base* getDeepCopy(QMap<QString, QString>* map, QMap<QString, QString>* map1) /*throws JmriException*/override {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  Base* deepCopyChildren(Base* base, QMap<QString, QString>* map, QMap<QString, QString>* map1) /*throws JmriException*/override {
        throw new UnsupportedOperationException("Not supported");
    }

};

#endif // DIGITALACTIONMANAGERTEST_H
