#ifndef ABSTRACTMALESOCKETXML_H
#define ABSTRACTMALESOCKETXML_H

#include <abstractnamedbeanmanagerconfigxml.h>
#include "malesocketxml.h"


class AbstractMaleSocketXml : public AbstractNamedBeanManagerConfigXML, public MaleSocketXml
{
  Q_OBJECT
  Q_INTERFACES(MaleSocketXml)
 public:
  explicit AbstractMaleSocketXml(QObject *parent = nullptr);
  /*public*/  QDomElement store(QObject* o)override;
  //virtual QString getClassName()=0;
  /*public*/  bool load(QDomElement shared, QDomElement perNode)override;
  /*public*/  bool load(QDomElement maleSocketElement, MaleSocket* maleSocket)override;

 private:
  static Logger* log;
};

#endif // ABSTRACTMALESOCKETXML_H
