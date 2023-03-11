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
      void addPropertyChangeListener(PropertyChangeListener* l) override {AbstractNamedBean::addPropertyChangeListener(l);}

   protected:
      //@Override
      /*protected*/ void registerListenersForThisClass() override{
          // Do nothing
      }

      //@Override
      /*protected*/ void unregisterListenersForThisClass()override {
          // Do nothing
      }

      //@Override
      /*protected*/ void disposeMe() override{
          throw new UnsupportedOperationException("Not supported.");
      }
public:
      //@Override
      /*public*/  QString getShortDescription(QLocale /*locale*/) override{
          return "My short description";
      }

      //@Override
      /*public*/  QString getLongDescription(QLocale /*locale*/)override{
          return "My long description";
      }

      //@Override
      /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ override{
          throw new UnsupportedOperationException("Not supported.");
      }

      //@Override
      /*public*/  int getChildCount() override{
          return 0;
      }

      //@Override
      /*public*/  Category getCategory() override{
          return Category::COMMON;
      }

      //@Override
      /*public*/  void setup() override{
          throw new UnsupportedOperationException("Not supported.");
      }

      //@Override
      /*public*/  QString evaluate() /*throws JmriException */override{
          if (je != nullptr) throw je;
          if (re != nullptr) throw re;
          return result;
      }
//public slots:
      //@Override
      /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws PropertyVetoException*/ override{
          if (_vetoChange) throw new PropertyVetoException("Veto change", evt);
      }
public:
      //@Override
      /*public*/  Base* getDeepCopy(QMap<QString, QString>* /*map*/, QMap<QString, QString>* /*map1*/) /*throws JmriException*/override {
          throw new UnsupportedOperationException("Not supported");
      }

      //@Override
      /*public*/  Base* deepCopyChildren(Base* /*base*/, QMap<QString, QString>* /*map*/, QMap<QString, QString>* /*map1*/) /*throws JmriException */override{
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
      ///*public*/ void vetoableChange(/*@Nonnull*/ PropertyChangeEvent* evt) override {AbstractNamedBean::vetoableChange(evt);}
      /*public*/ QString getListenerRef(/*@Nonnull*/ PropertyChangeListener* l) override {return  AbstractNamedBean::getListenerRef(l);}
      /*public*/ QList<QString> getListenerRefs() override {return AbstractNamedBean::getListenerRefs();}
      /*public*/ int getNumPropertyChangeListeners() override {return  AbstractNamedBean::getNumPropertyChangeListeners();}
      /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(/*@Nonnull*/ QString name)override {
       return AbstractNamedBean::getPropertyChangeListenersByReference(name);
      }
    friend class DefaultMaleStringExpressionSocketTest;
  };
 protected:
  /*protected*/ QString getNewSystemName()override;

};

#endif // DEFAULTMALESTRINGEXPRESSIONSOCKETTEST_H
