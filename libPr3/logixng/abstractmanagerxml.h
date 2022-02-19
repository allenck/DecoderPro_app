#ifndef ABSTRACTMANAGERXML_H
#define ABSTRACTMANAGERXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class Class;
class MaleSocket;
class AbstractManagerXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  explicit AbstractManagerXml(QObject *parent = nullptr) : AbstractNamedBeanManagerConfigXML(parent) {}
  /*public*/  QDomElement storeMaleSocket(MaleSocket* maleSocket);
  /*public*/  void loadMaleSocket(QDomElement element, MaleSocket* maleSocket);

 private:
  /*private*/ /*final*/ QMap<QString, /*Class<?>*/Class*> xmlClasses = QMap<QString, /*Class<?>*/Class*>();
  static Logger* log;

  friend class DefaultAnalogExpressionManagerXml;
};

#endif // ABSTRACTMANAGERXML_H
