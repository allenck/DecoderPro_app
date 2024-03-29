#ifndef DIGITALEXPRESSIONMANAGERTEST_H
#define DIGITALEXPRESSIONMANAGERTEST_H

#include <abstractmanagertestbase.h>
#include <QMainWindow>
#include "femalesocketlistener.h"
#include "abstractbase.h"
#include "digitalexpressionbean.h"

class MyExpression;
class DigitalExpressionManager;
class DigitalExpressionManagerTest : public AbstractManagerTestBase
{
  Q_OBJECT
 public:
  explicit DigitalExpressionManagerTest(QObject *parent = nullptr) : AbstractManagerTestBase(parent){}
  Q_INVOKABLE /*public*/  void setUp();
  Q_INVOKABLE /*public*/  void tearDown();

 public slots:
  /*public*/  void testRegisterExpression();
  /*public*/  void testCreateFemaleSocket();
  /*public*/  void testGetBeanTypeHandled();
  /*public*/  void testInstance();

 private:
  /*private*/ DigitalExpressionManager* _m;

};

/*private*/ /*static*/ class MyExpression : public AbstractBase, public DigitalExpressionBean {
Q_OBJECT
  Q_INTERFACES(DigitalExpressionBean)
 public:
   /*public*/ MyExpression(QString sys) /*throws BadSystemNameException*/ : AbstractBase(sys){
       //super(sys);
   }
    QString getClass() const override {return ".MyExpression";}

     QObject* bself() override {return (QObject*)this;}
     QObject* self() override {return (QObject*)this;}
     void addPropertyChangeListener(PropertyChangeListener* l) override {AbstractNamedBean::addPropertyChangeListener(l);}


   /** {@inheritDoc} */
   //@Override
   /*public*/  void notifyChangedResult(bool oldResult, bool newResult) {
       throw new UnsupportedOperationException("Not supported");
   }
protected:
   //@Override
   /*protected*/ void registerListenersForThisClass() {
       throw new UnsupportedOperationException("Not supported");
   }

   //@Override
   /*protected*/ void unregisterListenersForThisClass() {
       throw new UnsupportedOperationException("Not supported");
   }

   //@Override
   /*protected*/ void disposeMe() {
       throw new UnsupportedOperationException("Not supported");
   }
public:
   //@Override
   /*public*/  void setState(int s) /*throws JmriException*/ {
       throw new UnsupportedOperationException("Not supported");
   }

   //@Override
   /*public*/  int getState() {
       throw new UnsupportedOperationException("Not supported");
   }

   //@Override
   /*public*/  QString getBeanType() {
       throw new UnsupportedOperationException("Not supported");
   }

   //@Override
   /*public*/  QString getShortDescription(QLocale locale) {
       throw new UnsupportedOperationException("Not supported");
   }

   //@Override
   /*public*/  QString getLongDescription(QLocale locale) {
       throw new UnsupportedOperationException("Not supported");
   }

   //@Override
   /*public*/  Base* getParent() const  {
       throw new UnsupportedOperationException("Not supported");
   }

   //@Override
   /*public*/  void setParent(Base* parent) {
       throw new UnsupportedOperationException("Not supported");
   }

   //@Override
   /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
       throw new UnsupportedOperationException("Not supported");
   }

   //@Override
   /*public*/  int getChildCount() {
       throw new UnsupportedOperationException("Not supported");
   }

   //@Override
   /*public*/  Category getCategory() {
       throw new UnsupportedOperationException("Not supported");
   }

   //@Override
   /*public*/  void setup() {
       throw new UnsupportedOperationException("Not supported");
   }

   //@Override
   /*public*/  bool evaluate() /*throws JmriException*/ {
       throw new UnsupportedOperationException("Not supported");
   }

   //@Override
   /*public*/  Base* getDeepCopy(QMap<QString, QString> map, QMap<QString, QString> map1) /*throws JmriException */{
       throw new UnsupportedOperationException("Not supported");
   }

   //@Override
   /*public*/  Base* deepCopyChildren(Base* base, QMap<QString, QString> map,QMap<QString, QString> map1) /*throws JmriException*/ {
       throw new UnsupportedOperationException("Not supported");
   }
 /*public*/  void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef)override{
  AbstractNamedBean::addPropertyChangeListener(listener, name,listenerRef);
 }
 /*public*/  void addPropertyChangeListener(/*@Nonnull*/ QString propertyName, /*@Nonnull*/ PropertyChangeListener* listener,
                                                   QString name, QString listenerRef) override {
  AbstractNamedBean::addPropertyChangeListener(propertyName, listener, name, listenerRef);
 }
 /*public*/ void updateListenerRef(PropertyChangeListener* l, QString newName) override {AbstractNamedBean::updateListenerRef(l, newName);}
 /*public*/ void vetoableChange(/*@Nonnull*/ PropertyChangeEvent* evt) override {AbstractNamedBean::vetoableChange(evt);}
 /*public*/ QString getListenerRef(/*@Nonnull*/ PropertyChangeListener* l) override {return  AbstractNamedBean::getListenerRef(l);}
 /*public*/ QList<QString> getListenerRefs() override {return AbstractNamedBean::getListenerRefs();}
 /*public*/ int getNumPropertyChangeListeners() override {return  AbstractNamedBean::getNumPropertyChangeListeners();}
 /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(/*@Nonnull*/ QString name)override {
  return AbstractNamedBean::getPropertyChangeListenersByReference(name);
 }
};
/*private*/ /*static*/ class MyFemaleSocketListener11 : public FemaleSocketListener {
    ////@Override
    /*public*/  void connected(FemaleSocket* socket) {
        // Do nothing
    }

    ////@Override
    /*public*/  void disconnected(FemaleSocket* socket) {
        // Do nothing
    }
};

#endif // DIGITALEXPRESSIONMANAGERTEST_H
