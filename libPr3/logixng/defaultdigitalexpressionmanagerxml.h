#ifndef DEFAULTDIGITALEXPRESSIONMANAGERXML_H
#define DEFAULTDIGITALEXPRESSIONMANAGERXML_H

#include "abstractmanagerxml.h"

class DefaultDigitalExpressionManagerXml : public AbstractManagerXml
{
  Q_OBJECT
 public:
  explicit DefaultDigitalExpressionManagerXml(QObject *parent = nullptr);
  ~DefaultDigitalExpressionManagerXml() {}
  DefaultDigitalExpressionManagerXml(const DefaultDigitalExpressionManagerXml&) : AbstractManagerXml() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  void setStoreElementClass(QDomElement expressions);
  /*public*/  bool load(QDomElement sharedExpression, QDomElement perNodeExpression)override;
  /*public*/  void loadExpressions(QDomElement expressions);
  /*public*/  int loadOrder()const override;

 private:
  static Logger* log;
  /*private*/ /*final*/ QMap<QString, Class/*<?>>*/*> xmlClasses = QMap<QString, Class/*<?>>*/*>();

 protected:
  /*protected*/ void replaceExpressionManager();

};
Q_DECLARE_METATYPE(DefaultDigitalExpressionManagerXml)
#endif // DEFAULTDIGITALEXPRESSIONMANAGERXML_H
