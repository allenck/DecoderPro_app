#ifndef DEFAULTMALEDIGITALBOOLEANACTIONSOCKETTEST_H
#define DEFAULTMALEDIGITALBOOLEANACTIONSOCKETTEST_H

#include "malesockettestbase.h"
#include <QObject>
#include "abstractdigitalbooleanaction.h"
#include "runtimeexception.h"
#include "jmriexception.h"
#include "defaultmaledigitalbooleanactionsocket.h"

class DefaultMaleDigitalBooleanActionSocketTest : public MaleSocketTestBase
{
  Q_OBJECT
 public:
  explicit DefaultMaleDigitalBooleanActionSocketTest(QObject *parent = nullptr);
  Q_INVOKABLE /*public*/  void setUp();
  Q_INVOKABLE /*public*/  void tearDown();

 public slots:
  /*public*/  void testCtor();
  /*public*/  void testEvaluate() /*throws JmriException*/;
  /*public*/  void testVetoableChange();
  /*public*/  void testCompareSystemNameSuffix();

 private:
  /**
   * This action is different from MyStringAction and is used to test the
   * male socket.
   */
  /*private*/ class MyDigitalBooleanAction : public AbstractDigitalBooleanAction {

      JmriException* je = nullptr;
      RuntimeException* re = nullptr;
      bool _hasChangedToTrue = false;
      bool _hasChangedToFalse = false;
      bool _vetoChange = false;
   public:
      MyDigitalBooleanAction(QString sysName) : AbstractDigitalBooleanAction(sysName, "") {
          //super(sysName, null);
      }
      QObject* bself() override{return (QObject*)this;}
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
      /*public*/  Category* getCategory() {
          return Category::OTHER;
      }

      //@Override
      /*public*/  void setup() {
          throw new UnsupportedOperationException("Not supported.");
      }

      //@Override
      /*public*/  void execute(bool hasChangedToTrue, bool hasChangedToFalse) /*throws JmriException*/ {
          if (je != nullptr) throw je;
          if (re != nullptr) throw re;
         _hasChangedToTrue = hasChangedToTrue;
         _hasChangedToFalse = hasChangedToFalse;
      }

      //@Override
      /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws PropertyVetoException*/override {
          if (_vetoChange) throw new PropertyVetoException("Veto change", evt);
      }

      //@Override
      /*public*/  Base* getDeepCopy(QMap<QString, QString>* map, QMap<QString, QString>* map1) /*throws JmriException*/ override{
          throw new UnsupportedOperationException("Not supported");
      }

      //@Override
      /*public*/  Base* deepCopyChildren(Base* base, QMap<QString, QString>* map, QMap<QString, QString>* map1) /*throws JmriException*/ override{
          throw new UnsupportedOperationException("Not supported");
      }
      friend class DefaultMaleDigitalBooleanActionSocketTest;
  };
 protected:
  /*protected*/ QString getNewSystemName();

};

#endif // DEFAULTMALEDIGITALBOOLEANACTIONSOCKETTEST_H
