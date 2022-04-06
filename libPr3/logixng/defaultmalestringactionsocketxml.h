#ifndef DEFAULTMALESTRINGACTIONSOCKETXML_H
#define DEFAULTMALESTRINGACTIONSOCKETXML_H

#include "abstractmalesocketxml.h"

class DefaultMaleStringActionSocketXml : public AbstractMaleSocketXml
{
  Q_OBJECT
 public:
  explicit DefaultMaleStringActionSocketXml(QObject *parent = nullptr);
  ~DefaultMaleStringActionSocketXml() {}
  DefaultMaleStringActionSocketXml(const DefaultMaleStringActionSocketXml&) : AbstractMaleSocketXml() {}
  /*public*/ QString getClassName() override;
};
Q_DECLARE_METATYPE(DefaultMaleStringActionSocketXml)

#endif // DEFAULTMALESTRINGACTIONSOCKETXML_H
