#ifndef DEFAULTNAMEDTABLEMANAGERXML_H
#define DEFAULTNAMEDTABLEMANAGERXML_H

#include "abstractmanagerxml.h"

class DefaultNamedTableManagerXml : public AbstractManagerXml
{
  Q_OBJECT
 public:
  explicit DefaultNamedTableManagerXml(QObject *parent = nullptr);
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  void setStoreElementClass(QDomElement expressions);
  /*public*/  bool load(QDomElement sharedExpression, QDomElement perNodeExpression)override;
  /*public*/  void loadTables(QDomElement expressions);
  /*public*/  int loadOrder()const override;

 private:
  static Logger* log;
  /*private*/ /*final*/ QMap<QString, Class/*<?>*/> xmlClasses = QMap<QString, Class/*<?>*/>();

 protected:
  /*protected*/ void replaceExpressionManager();

};

#endif // DEFAULTNAMEDTABLEMANAGERXML_H
