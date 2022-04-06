#ifndef DEFAULTMALEDIGITALBOOLEANACTIONSOCKETXML_H
#define DEFAULTMALEDIGITALBOOLEANACTIONSOCKETXML_H

#include "abstractmalesocketxml.h"

class DefaultMaleDigitalBooleanActionSocketXml : public AbstractMaleSocketXml
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit DefaultMaleDigitalBooleanActionSocketXml(QObject *parent = nullptr);
  ~DefaultMaleDigitalBooleanActionSocketXml() {}
  DefaultMaleDigitalBooleanActionSocketXml(const DefaultMaleDigitalBooleanActionSocketXml&) : AbstractMaleSocketXml() {}
  /*public*/ QString getClassName() override;

};
Q_DECLARE_METATYPE(DefaultMaleDigitalBooleanActionSocketXml)
#endif // DEFAULTMALEDIGITALBOOLEANACTIONSOCKETXML_H
