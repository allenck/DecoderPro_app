#ifndef LOGDATAXML_H
#define LOGDATAXML_H

#include <abstractnamedbeanmanagerconfigxml.h>
namespace Actions
{
 class LogDataXml : public AbstractNamedBeanManagerConfigXML
 {
   Q_OBJECT
  public:
   LogDataXml(QObject* parent = nullptr);
   ~LogDataXml() {}
   LogDataXml(const LogDataXml&){}
   /*public*/  QDomElement store(QObject* o)override;
   /*public*/  bool load(QDomElement shared, QDomElement perNode)override;

  private:
   static Logger* log;
 };
}
//Q_DECLARE_METATYPE(Actions::LogDataXml)
#endif // LOGDATAXML_H
