#ifndef DEFAULTSTRINGACTIONMANAGERXML_H
#define DEFAULTSTRINGACTIONMANAGERXML_H

#include "abstractmanagerxml.h"

class DefaultStringActionManagerXml : public AbstractManagerXml
{
  Q_OBJECT
 public:
  explicit DefaultStringActionManagerXml(QObject *parent = nullptr);
  /*public*/  QDomElement store(QObject *o);
  /*public*/  void setStoreElementClass(QDomElement actions);
  /*public*/  bool load(QDomElement sharedAction, QDomElement perNodeAction);
  /*public*/  void loadActions(QDomElement actions);

 private:
  static Logger* log;
  /*private*/ /*final*/ QMap<QString,/* Class<?>*/QString> xmlClasses = QMap<QString,/* Class<?>*/QString>();

 protected:
  /*protected*/ void replaceActionManager();

};

#endif // DEFAULTSTRINGACTIONMANAGERXML_H
