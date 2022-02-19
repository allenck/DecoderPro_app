#ifndef DEFAULTSTRINGEXPRESSIONMANAGERXML_H
#define DEFAULTSTRINGEXPRESSIONMANAGERXML_H

#include "abstractmanagerxml.h"

class DefaultStringExpressionManagerXml : public AbstractManagerXml
{
  Q_OBJECT
 public:
  explicit DefaultStringExpressionManagerXml(QObject *parent = nullptr);
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  void setStoreElementClass(QDomElement expressions);
  /*public*/  bool load(QDomElement sharedExpression, QDomElement perNodeExpression)override;
  /*public*/  void loadExpressions(QDomElement expressions);
  /*public*/  int loadOrder()const override;

 private:
  static Logger* log;
  /*private*/ /*final*/ QMap<QString, Class/*<?>*/*> xmlClasses = QMap<QString, Class/*<?>*/*>();

 protected:
  /*protected*/ void replaceExpressionManager();

};

#endif // DEFAULTSTRINGEXPRESSIONMANAGERXML_H