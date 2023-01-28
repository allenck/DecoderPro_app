#ifndef EXPRESSIONS_LOGDATAXML_H
#define EXPRESSIONS_LOGDATAXML_H

#include <abstractnamedbeanmanagerconfigxml.h>
namespace Expressions
{
 class LogDataXml : public AbstractNamedBeanManagerConfigXML
 {
   Q_OBJECT
  public:
   Q_INVOKABLE LogDataXml(QObject* parent = nullptr);
   ~LogDataXml() {}
   LogDataXml(const LogDataXml&){}
   /*public*/  QDomElement store(QObject* o)override;
   /*public*/  bool load(QDomElement shared, QDomElement perNode)override;

  private:
   static Logger* log;
 };
}
Q_DECLARE_METATYPE(Expressions::LogDataXml)
#endif // EXPRESSIONS_LOGDATAXML_H
