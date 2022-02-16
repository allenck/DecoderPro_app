#ifndef DEFAULTSTRINGEXPRESSIONMANAGERXML_H
#define DEFAULTSTRINGEXPRESSIONMANAGERXML_H

#include "abstractmanagerxml.h"

class DefaultStringExpressionManagerXml : public AbstractManagerXml
{
  Q_OBJECT
 public:
  explicit DefaultStringExpressionManagerXml(QObject *parent = nullptr);
  /*public*/  QDomElement store(QObject* o)override;

 private:
  static Logger* log;
  /*private*/ /*final*/ QMap<QString, Class/*<?>*/*> xmlClasses = QMap<QString, Class/*<?>*/*>();

};

#endif // DEFAULTSTRINGEXPRESSIONMANAGERXML_H
