#ifndef DEFAULTMALEANALOGACTIONSOCKETXML_H
#define DEFAULTMALEANALOGACTIONSOCKETXML_H

#include "abstractmalesocketxml.h"

class DefaultMaleAnalogActionSocketXml : public AbstractMaleSocketXml
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit DefaultMaleAnalogActionSocketXml(QObject *parent = nullptr);
  ~DefaultMaleAnalogActionSocketXml() {}
  DefaultMaleAnalogActionSocketXml(const DefaultMaleAnalogActionSocketXml&) : AbstractMaleSocketXml() {}
  /*public*/ QString getClassName() override;
};
Q_DECLARE_METATYPE(DefaultMaleAnalogActionSocketXml)
#endif // DEFAULTMALEANALOGACTIONSOCKETXML_H
