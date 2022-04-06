#ifndef DEFAULTMALESTRINGEXPRESSIONSOCKETXML_H
#define DEFAULTMALESTRINGEXPRESSIONSOCKETXML_H

#include "abstractmalesocketxml.h"

class DefaultMaleStringExpressionSocketXml : public AbstractMaleSocketXml
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit DefaultMaleStringExpressionSocketXml(QObject *parent = nullptr);
  ~DefaultMaleStringExpressionSocketXml() {}
  DefaultMaleStringExpressionSocketXml(const DefaultMaleStringExpressionSocketXml&) : AbstractMaleSocketXml() {}
  /*public*/ QString getClassName() override;
};
Q_DECLARE_METATYPE(DefaultMaleStringExpressionSocketXml)

#endif // DEFAULTMALESTRINGEXPRESSIONSOCKETXML_H
