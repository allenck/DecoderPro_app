#ifndef ANALOGACTIONMANAGERTEST_H
#define ANALOGACTIONMANAGERTEST_H

#include <abstractmanagertestbase.h>
#include "abstractbase.h"
#include "analogactionbean.h"

class AnalogActionManager;
class AnalogActionManagerTest : public AbstractManagerTestBase
{
  Q_OBJECT
 public:
  explicit AnalogActionManagerTest(QObject *parent = nullptr);
  Q_INVOKABLE /*public*/  void setUp();
  Q_INVOKABLE /*public*/  void tearDown();

 public slots:
  /*public*/  void testRegisterAction();
  /*public*/  void testGetBeanTypeHandled();
  /*public*/  void testInstance();

 private:
  /*private*/ AnalogActionManager* _m;

  /*private*/ /*static*/ class MyAction : AbstractBase,  public AnalogActionBean {
  //Q_INTERFACES(AnalogActionBean)
   public:
      /*public*/  MyAction(QString sys) /*throws BadSystemNameException*/ : AbstractBase(sys){
          //super(sys);
      }
    QObject* bself() override{return (QObject*)this;}

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
      /*public*/  Base* getParent() {
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
      /*public*/  Category* getCategory() {
          throw new UnsupportedOperationException("Not supported");
      }

      //@Override
      /*public*/  void setup() {
          throw new UnsupportedOperationException("Not supported");
      }

      //@Override
      /*public*/  void setValue(double value) /*throws JmriException*/ {
          throw new UnsupportedOperationException("Not supported");
      }

      //@Override
      /*public*/  Base* getDeepCopy(QMap<QString, QString>* map, QMap<QString, QString>* map1) /*throws JmriException*/ {
          throw new UnsupportedOperationException("Not supported");
      }

      //@Override
      /*public*/  Base* deepCopyChildren(Base* base, QMap<QString, QString>* map, QMap<QString, QString>* map1) /*throws JmriException*/ {
          throw new UnsupportedOperationException("Not supported");
      }

  };
};

#endif // ANALOGACTIONMANAGERTEST_H
