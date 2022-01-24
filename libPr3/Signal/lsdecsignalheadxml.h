#ifndef LSDECSIGNALHEADXML_H
#define LSDECSIGNALHEADXML_H

#include <abstractnamedbeanmanagerconfigxml.h>
#include <QWidget>
#include "namedbeanhandle.h"
#include "turnout.h"

class LsDecSignalHeadXml : public AbstractNamedBeanManagerConfigXML
{
 public:
  explicit LsDecSignalHeadXml(QObject *parent = nullptr);
  /*public*/  QDomElement store(QObject* o) override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode)override;
  /*public*/  void load(QDomElement element, QObject* o)override;

 private:
  static Logger* log;
  QDomElement addTurnoutElement(QString name, int s);
  NamedBeanHandle<Turnout*>* loadTurnout(QDomNode o);
  int loadTurnoutStatus(QDomNode o);

};

#endif // LSDECSIGNALHEADXML_H
