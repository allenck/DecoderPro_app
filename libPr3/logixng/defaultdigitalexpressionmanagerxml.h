#ifndef DEFAULTDIGITALEXPRESSIONMANAGERXML_H
#define DEFAULTDIGITALEXPRESSIONMANAGERXML_H

#include "abstractmanagerxml.h"

class DefaultDigitalExpressionManagerXml : public AbstractManagerXml
{
  Q_OBJECT
 public:
  explicit DefaultDigitalExpressionManagerXml(QObject *parent = nullptr);

 private:
  static Logger* log;
};

#endif // DEFAULTDIGITALEXPRESSIONMANAGERXML_H
