#ifndef DEFAULTMODULEMANAGERXML_H
#define DEFAULTMODULEMANAGERXML_H

#include "abstractmanagerxml.h"

class DefaultModuleManagerXml : public AbstractManagerXml
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit DefaultModuleManagerXml(QObject *parent = nullptr);
  ~DefaultModuleManagerXml() {}
  DefaultModuleManagerXml(const DefaultModuleManagerXml&) : AbstractManagerXml() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  void setStoreElementClass(QDomElement expressions);
  /*public*/  bool load(QDomElement sharedExpression, QDomElement perNodeExpression)override;
  /*public*/  void loadTables(QDomElement expressions);
  /*public*/  int loadOrder() const override;

 private:
  static Logger* log;
  /*private*/ /*final*/ QMap<QString, Class/*<?>*/*> xmlClasses = QMap<QString, Class/*<?>*/*>();

 protected:
  /*protected*/ void replaceExpressionManager();

};
Q_DECLARE_METATYPE(DefaultModuleManagerXml)
#endif // DEFAULTMODULEMANAGERXML_H
