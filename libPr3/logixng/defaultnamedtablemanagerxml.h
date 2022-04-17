#ifndef DEFAULTNAMEDTABLEMANAGERXML_H
#define DEFAULTNAMEDTABLEMANAGERXML_H

#include "abstractmanagerxml.h"
#include "threadingutil.h"

class DefaultNamedTableManagerXml : public AbstractManagerXml
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit DefaultNamedTableManagerXml(QObject *parent = nullptr);
  ~DefaultNamedTableManagerXml() {}
  DefaultNamedTableManagerXml(const DefaultNamedTableManagerXml&) : AbstractManagerXml() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  void setStoreElementClass(QDomElement expressions);
  /*public*/  bool load(QDomElement sharedExpression, QDomElement perNodeExpression)override;
  /*public*/  void loadTables(QDomElement expressions);
  /*public*/  int loadOrder()const override;

 private:
  static Logger* log;
  /*private*/ /*final*/ QMap<QString, Class/*<?>*/*> xmlClasses = QMap<QString, Class/*<?>*/*>();

 protected:
  /*protected*/ void replaceExpressionManager();

};
Q_DECLARE_METATYPE(DefaultNamedTableManagerXml)

class DNTMRun : public ThreadAction
{
  Q_OBJECT
 public:
  DNTMRun() {}
 public slots:
  void run();
};
#endif // DEFAULTNAMEDTABLEMANAGERXML_H
