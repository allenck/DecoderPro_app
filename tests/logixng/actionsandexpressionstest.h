#ifndef ACTIONSANDEXPRESSIONSTEST_H
#define ACTIONSANDEXPRESSIONSTEST_H

#include <QObject>

class Category;
class Logger;
class ActionsAndExpressionsTest : public QObject
{
  Q_OBJECT
 public:
  explicit ActionsAndExpressionsTest(QObject *parent = nullptr);
  Q_INVOKABLE /*public*/  void setUp();
  Q_INVOKABLE /*public*/  void tearDown() ;
  /*public*/  QHash<Category, QList<QString> > getAnalogActionClasses();
  /*public*/  QHash<Category, QList<QString> > getAnalogExpressionClasses();
  /*public*/  QHash<Category, QList</*Class<? extends Base>*/QString>> getDigitalActionClasses();
  /*public*/  QHash<Category, QList</*Class<? extends Base>*/QString>> getDigitalBooleanActionClasses();
  /*public*/  QHash<Category, QList</*Class<? extends Base>*/QString>> getDigitalExpressionClasses();
  /*public*/  QHash<Category, QList</*Class<? extends Base>*/QString>> getStringActionClasses() ;
  /*public*/  QHash<Category, QList</*Class<? extends Base>*/QString>> getStringExpressionClasses();
  /*public*/  void addClasses(QHash<Category, QList<QString> *> classes, QHash<Category, QList<QString> > newClasses);

 public slots:
  /*public*/  void testGetBeanType();

 signals:

 private:
  static Logger* log;
  /*private*/ bool errorsFound = false;
  /*private*/ void checkFolder(QString path, QString packageName, QHash<Category, QList<QString>* > registeredClasses, QStringList classesToIgnore);
  /*private*/ QString getPath(QString subFolder);
  static QString root;
};

#endif // ACTIONSANDEXPRESSIONSTEST_H
