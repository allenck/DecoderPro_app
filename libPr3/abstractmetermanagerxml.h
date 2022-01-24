#ifndef ABSTRACTMETERMANAGERXML_H
#define ABSTRACTMETERMANAGERXML_H
#include "abstractnamedbeanmanagerconfigxml.h"

class AbstractMeterManagerXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  AbstractMeterManagerXml(QObject* parent = nullptr);
  /*public*/ QDomElement store(QObject* o);
  /*public*/ void setStoreElementClass(QDomElement meters);
  /*public*/ bool load(QDomElement sharedMeters, QDomElement perNodeMemories) throw (JmriConfigureXmlException) override;
  /*public*/ void loadMeters(QDomElement meters);
  /*public*/ int loadOrder() const override;
 private:
  static Logger* log;
};

#endif // ABSTRACTMETERMANAGERXML_H
