#ifndef MERGSD2SIGNALHEADXML_H
#define MERGSD2SIGNALHEADXML_H
#include "namedbeanhandle.h"
#include "turnout.h"

#include <abstractnamedbeanmanagerconfigxml.h>

class MergSD2SignalHeadXml : public AbstractNamedBeanManagerConfigXML
{
 public:
  Q_INVOKABLE explicit MergSD2SignalHeadXml(QObject *parent = nullptr);
  ~MergSD2SignalHeadXml(){};
  MergSD2SignalHeadXml(const MergSD2SignalHeadXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode)override;
  NamedBeanHandle<Turnout*>* loadTurnout(QDomNode o);
  /*public*/  void load(QDomElement element, QObject* o)override;


 private:
  static Logger* log;
  QDomElement addTurnoutElement(NamedBeanHandle<Turnout*>* to, QString which);
  QDomElement addSingleTurnoutElement(Turnout* to);

};
Q_DECLARE_METATYPE(MergSD2SignalHeadXml)
#endif // MERGSD2SIGNALHEADXML_H
