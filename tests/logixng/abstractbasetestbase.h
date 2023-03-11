#ifndef ABSTRACTBASETESTBASE_H
#define ABSTRACTBASETESTBASE_H

#include <QObject>
#include "base.h"
#include "category.h"
#include "abstractbase.h"
#include "runnable.h"

class MaleSocket;
class FemaleSocket;
class RunnableWithIndex;
class MyBase;
class Logger;
class ConditionalNG;
class AbstractBaseTestBase : public QObject
{
  Q_OBJECT
 public:
  explicit AbstractBaseTestBase(QObject *parent = nullptr) : QObject(parent) {}
  /*public*/  /*abstract*/virtual  ConditionalNG* getConditionalNG()=0;
  /*public*/  /*final*/ QString TREE_INDENT = "   ";
  /*public*/  /*abstract*/ virtual MaleSocket* getConnectableChild()=0;
  /*public*/  /*abstract*/ virtual LogixNG* getLogixNG()=0;
  /*abstract*/ virtual /*public*/  bool addNewSocket() /*throws SocketAlreadyConnectedException*/=0;
  /*public*/  static MaleSocket* getLastMaleSocket(MaleSocket* socket);
  /*public*/  /*abstract*/virtual  QString getExpectedPrintedTree()=0;
  /*public*/  /*abstract*/virtual QString getExpectedPrintedTreeFromRoot()=0;
  /*public*/  void assertIndexOutOfBoundsException(RunnableWithIndex* r, int index, int arraySize);


 public slots:
  /*public*/  void testGetConditionalNG();
  /*public*/  void testGetLogixNG();
  /*public*/  void testMaleSocketGetConditionalNG();
  /*public*/  void testMaleSocketGetLogixNG();
  /*public*/  void testMaleSocketGetRoot();
  /*public*/  void testGetParent();
  /*public*/  void testFemaleSocketSystemName();
//  /*public*/  void testSetParentForAllChildren_WithConnectedChildren();
//  /*public*/  void testSetParentForAllChildren_WithoutConnectedChildren();
  /*public*/  void testGetPrintTree();
  /*public*/  void testMaleSocketGetPrintTree();
  /*public*/  void testGetPrintTreeWithStandardLocale();
  /*public*/  void testMaleSocketGetPrintTreeWithStandardLocale();
  /*public*/  void testGetPrintTreeFromRoot();
  /*public*/  void testGetDeepCopy() /*throws JmriException*/;
  /*public*/  void testIsActive();
  /*public*/  void testMaleSocketIsActive();
  /*public*/  void testConstants();
  /*public*/  void testNames();
  /*public*/  void testParent();
  /*public*/  void testIsEnabled();
  /*public*/  void testDispose();
  /*public*/  void testRunOnGUIDelayed();
  /*public*/  void testChildAndChildCount();
  /*public*/  void testBeanType();
  /*public*/  void testDescribeState();
  /*public*/  void testAddAndRemoveSocket() /*throws SocketAlreadyConnectedException*/;

 signals:

 private:
  static Logger* log;
//  /*private*/ void clearParent(Base* item);
//  /*private*/ void checkParent(Base* item);
  /*private*/ class MyBase : public AbstractBase {

      /*private*/ MyBase() : AbstractBase("IQ1") {
          //super("IQ1");
      }
   public:
    QObject* bself() override {return (QObject*)this;}
    void addPropertyChangeListener(PropertyChangeListener* l) override {AbstractNamedBean::addPropertyChangeListener(l);}

protected:
      //@Override
      /*protected*/ void registerListenersForThisClass() override{
          throw new UnsupportedOperationException("Not supported.");
      }

      //@Override
      /*protected*/ void unregisterListenersForThisClass() override{
          throw new UnsupportedOperationException("Not supported.");
      }

      //@Override
      /*protected*/ void disposeMe() override{
          throw new UnsupportedOperationException("Not supported.");
      }
public:
      //@Override
      /*public*/  void setState(int s) /*throws JmriException*/ {
          throw new UnsupportedOperationException("Not supported.");
      }

      //@Override
      /*public*/  int getState() {
          throw new UnsupportedOperationException("Not supported.");
      }

      //@Override
      /*public*/  QString getBeanType() {
          throw new UnsupportedOperationException("Not supported.");
      }

      //@Override
      /*public*/  QString getShortDescription(QLocale locale) {
          throw new UnsupportedOperationException("Not supported.");
      }

      //@Override
      /*public*/  QString getLongDescription(QLocale locale) {
          throw new UnsupportedOperationException("Not supported.");
      }

      //@Override
      /*public*/  Base* getParent() const{
          throw new UnsupportedOperationException("Not supported.");
      }

      //@Override
      /*public*/  void setParent(Base* parent) {
          throw new UnsupportedOperationException("Not supported.");
      }

      //@Override
      /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
          throw new UnsupportedOperationException("Not supported.");
      }

      //@Override
      /*public*/  int getChildCount() {
          throw new UnsupportedOperationException("Not supported.");
      }

      //@Override
      /*public*/  Category getCategory() {
          throw new UnsupportedOperationException("Not supported.");
      }

      //@Override
      /*public*/  void setup() {
          throw new UnsupportedOperationException("Not supported.");
      }

      //@Override
      /*public*/  Base* getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) {
          throw new UnsupportedOperationException("Not supported");
      }

      //@Override
      /*public*/  Base* deepCopyChildren(Base* original, QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throws JmriException*/ {
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
   friend class AbstractBaseTestBase;
  };
 protected:
  /*protected*/ Base* _base = nullptr;
  /*protected*/ MaleSocket* _baseMaleSocket = nullptr;
  /*protected*/ Category _category = Other();
  /*protected*/ bool _isExternal = false;

};
/**
 * Executes the method.
 * This interface is used by the method
 * {@link #assertIndexOutOfBoundsException(RunnableWithIndex, int, int)}
 */
/*public*/  /*interface*/class RunnableWithIndex  : public Runnable{
  Q_OBJECT
 public:
    /**
     * Run the method.
     * @param index the index
     */
  /*public*/  void run(int index) {}
};

#endif // ABSTRACTBASETESTBASE_H
