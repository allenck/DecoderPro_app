#ifndef DEFAULTMALEDIGITALACTIONSOCKETXML_H
#define DEFAULTMALEDIGITALACTIONSOCKETXML_H

#include "abstractmalesocketxml.h"

class DefaultMaleDigitalActionSocketXml : public AbstractMaleSocketXml
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit DefaultMaleDigitalActionSocketXml(QObject *parent = nullptr);
  ~DefaultMaleDigitalActionSocketXml() {}
  DefaultMaleDigitalActionSocketXml(const DefaultMaleDigitalActionSocketXml&) : AbstractMaleSocketXml() {}
  /*public*/ QString getClassName() override;
};
Q_DECLARE_METATYPE(DefaultMaleDigitalActionSocketXml)
#endif // DEFAULTMALEDIGITALACTIONSOCKETXML_H
