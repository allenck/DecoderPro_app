#ifndef ABSTRACTMANAGERXML_H
#define ABSTRACTMANAGERXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class AbstractManagerXml : public AbstractNamedBeanManagerConfigXML
{
 public:
  explicit AbstractManagerXml(QObject *parent = nullptr);

 private:
  /*private*/ /*final*/ QMap<QString, QString> xmlClasses = QMap<QString, QString>();

};

#endif // ABSTRACTMANAGERXML_H
