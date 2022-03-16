#ifndef ABSTRACTBASETESTBASE_H
#define ABSTRACTBASETESTBASE_H

#include <QObject>
#include "base.h"
#include "category.h"
#include "abstractbase.h"

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
protected:
      //@Override
      /*protected*/ void registerListenersForThisClass() {
          throw new UnsupportedOperationException("Not supported.");
      }

      //@Override
      /*protected*/ void unregisterListenersForThisClass() {
          throw new UnsupportedOperationException("Not supported.");
      }

      //@Override
      /*protected*/ void disposeMe() {
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
      /*public*/  Base* getParent() {
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
      /*public*/  Category* getCategory() {
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
   friend class AbstractBaseTestBase;
  };
 protected:
  /*protected*/ Base* _base;
  /*protected*/ MaleSocket* _baseMaleSocket;
  /*protected*/ Category* _category;
  /*protected*/ bool _isExternal;

};

#endif // ABSTRACTBASETESTBASE_H