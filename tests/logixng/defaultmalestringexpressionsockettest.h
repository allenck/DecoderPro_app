#ifndef DEFAULTMALESTRINGEXPRESSIONSOCKETTEST_H
#define DEFAULTMALESTRINGEXPRESSIONSOCKETTEST_H

#include "malesockettestbase.h"
#include "abstractstringexpression.h"
#include "jmriexception.h"
#include "runtimeexception.h"

class StringExpressionDebugConfig;
class DefaultMaleStringExpressionSocketTest : public MaleSocketTestBase
{
  Q_OBJECT
 public:
  explicit DefaultMaleStringExpressionSocketTest(QObject *parent = nullptr);
  Q_INVOKABLE /*public*/  void setUp()override;
  Q_INVOKABLE /*public*/  void tearDown()override;

 public slots:
  /*public*/  void testCtor();
  /*public*/  void testEvaluate() /*throws JmriException*/;
  /*public*/  void testVetoableChange();
  /*public*/  void testCompareSystemNameSuffix();

 private:
  /**
   * This expression is different from StringExpressionMemory and is used to test the
   * male socket->
   */
  /*private*/ class MyStringExpression : public AbstractStringExpression {

      JmriException* je = nullptr;
      RuntimeException* re = nullptr;
      QString result = "";
      bool _vetoChange = false;
public:
      MyStringExpression(QString sysName) : AbstractStringExpression(sysName, ""){
          //super(sysName, null);
      }
      QObject* bself() override {return (QObject*)this;}
   protected:
      //@Override
      /*protected*/ void registerListenersForThisClass() {
          // Do nothing
      }

      //@Override
      /*protected*/ void unregisterListenersForThisClass() {
          // Do nothing
      }

      //@Override
      /*protected*/ void disposeMe() {
          throw new UnsupportedOperationException("Not supported.");
      }
public:
      //@Override
      /*public*/  QString getShortDescription(QLocale locale) {
          return "My short description";
      }

      //@Override
      /*public*/  QString getLongDescription(QLocale locale) {
          return "My long description";
      }

      //@Override
      /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
          throw new UnsupportedOperationException("Not supported.");
      }

      //@Override
      /*public*/  int getChildCount() {
          return 0;
      }

      //@Override
      /*public*/  Category getCategory() {
          return Category::COMMON;
      }

      //@Override
      /*public*/  void setup() {
          throw new UnsupportedOperationException("Not supported.");
      }

      //@Override
      /*public*/  QString evaluate() /*throws JmriException */{
          if (je != nullptr) throw je;
          if (re != nullptr) throw re;
          return result;
      }
//public slots:
      //@Override
      /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws PropertyVetoException*/ {
          if (_vetoChange) throw new PropertyVetoException("Veto change", evt);
      }
public:
      //@Override
      /*public*/  Base* getDeepCopy(QMap<QString, QString> map, QMap<QString, QString> map1) /*throws JmriException*/ {
          throw new UnsupportedOperationException("Not supported");
      }

      //@Override
      /*public*/  Base* deepCopyChildren(Base* base, QMap<QString, QString> map, QMap<QString, QString> map1) /*throws JmriException */{
          throw new UnsupportedOperationException("Not supported");
      }
    friend class DefaultMaleStringExpressionSocketTest;
  };
 protected:
  /*protected*/ QString getNewSystemName()override;

};

#endif // DEFAULTMALESTRINGEXPRESSIONSOCKETTEST_H
