#ifndef DEFAULTMALEANALOGEXPRESSIONSOCKETXML_H
#define DEFAULTMALEANALOGEXPRESSIONSOCKETXML_H

#include "abstractmalesocketxml.h"

class DefaultMaleAnalogExpressionSocketXml : public AbstractMaleSocketXml
{
  Q_OBJECT
 public:
  explicit DefaultMaleAnalogExpressionSocketXml(QObject *parent = nullptr);
  /*public*/ QString getClassName() override;
};

#endif // DEFAULTMALEANALOGEXPRESSIONSOCKETXML_H
