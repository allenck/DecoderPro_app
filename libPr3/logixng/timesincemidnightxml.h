#ifndef TIMESINCEMIDNIGHTXML_H
#define TIMESINCEMIDNIGHTXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class TimeSinceMidnightXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  explicit TimeSinceMidnightXml(QObject *parent = nullptr);
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode);

};

#endif // TIMESINCEMIDNIGHTXML_H
