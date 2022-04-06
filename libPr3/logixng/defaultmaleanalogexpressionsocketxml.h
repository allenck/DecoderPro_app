#ifndef DEFAULTMALEANALOGEXPRESSIONSOCKETXML_H
#define DEFAULTMALEANALOGEXPRESSIONSOCKETXML_H

#include "abstractmalesocketxml.h"

class DefaultMaleAnalogExpressionSocketXml : public AbstractMaleSocketXml
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit DefaultMaleAnalogExpressionSocketXml(QObject *parent = nullptr);
  ~DefaultMaleAnalogExpressionSocketXml() {}
  DefaultMaleAnalogExpressionSocketXml(const DefaultMaleAnalogExpressionSocketXml&) : AbstractMaleSocketXml() {}
  /*public*/ QString getClassName() override;
};
Q_DECLARE_METATYPE(DefaultMaleAnalogExpressionSocketXml)

#endif // DEFAULTMALEANALOGEXPRESSIONSOCKETXML_H
