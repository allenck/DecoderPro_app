#ifndef ANALOGACTIONLIGHTINTENSITYXML_H
#define ANALOGACTIONLIGHTINTENSITYXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class AnalogActionLightIntensityXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit AnalogActionLightIntensityXml(QObject *parent = nullptr);
  ~AnalogActionLightIntensityXml() {}
  AnalogActionLightIntensityXml(const AnalogActionLightIntensityXml&) :AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;

};
Q_DECLARE_METATYPE(AnalogActionLightIntensityXml)
#endif // ANALOGACTIONLIGHTINTENSITYXML_H
