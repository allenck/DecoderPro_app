#ifndef DEFAULTMODULEMANAGERXML_H
#define DEFAULTMODULEMANAGERXML_H

#include "abstractmanagerxml.h"

class DefaultModuleManagerXml : public AbstractManagerXml
{
  Q_OBJECT
 public:
  explicit DefaultModuleManagerXml(QObject *parent = nullptr);
  /*public*/  QDomElement store(QObject* o)override;

 private:
  static Logger* log;
  /*private*/ /*final*/ QMap<QString, Class/*<?>*/*> xmlClasses = QMap<QString, Class/*<?>*/*>();

};

#endif // DEFAULTMODULEMANAGERXML_H
