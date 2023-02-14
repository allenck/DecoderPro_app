#ifndef LOGIXXML_H
#define LOGIXXML_H

#include "abstractnamedbeanmanagerconfigxml.h"

class LogixXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE LogixXml(QObject *parent= nullptr);
  ~LogixXml() {}
  LogixXml(const LogixXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o) override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode)override;

  /*public*/ virtual void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef){}
  /*public*/ virtual void addPropertyChangeListener(/*@Nonnull*/ QString propertyName, /*@Nonnull*/ PropertyChangeListener* listener,
                                                    QString name, QString listenerRef) {}
  /*public*/ virtual void updateListenerRef(/*@Nonnull*/ PropertyChangeListener* l, QString newName){}

};
Q_DECLARE_METATYPE(LogixXml)
#endif // LOGIXXML_H
