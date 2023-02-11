#ifndef DEFAULTMALEDIGITALEXPRESSIONSOCKETXML_H
#define DEFAULTMALEDIGITALEXPRESSIONSOCKETXML_H

#include "abstractmalesocketxml.h"

class DefaultMaleDigitalExpressionSocketXml : public AbstractMaleSocketXml
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit DefaultMaleDigitalExpressionSocketXml(QObject *parent = nullptr);
  ~DefaultMaleDigitalExpressionSocketXml() {}
  DefaultMaleDigitalExpressionSocketXml(const DefaultMaleDigitalExpressionSocketXml&) : AbstractMaleSocketXml() {}
  /*public*/ QString getClassName() override;
  /*public*/ QDomElement store(QObject* o)override;
  /*public*/ bool load(QDomElement maleSocketElement, MaleSocket* maleSocket)override;

};
Q_DECLARE_METATYPE(DefaultMaleDigitalExpressionSocketXml)
#endif // DEFAULTMALEDIGITALEXPRESSIONSOCKETXML_H
