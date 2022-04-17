#ifndef DEFAULTSTRINGACTIONMANAGERXML_H
#define DEFAULTSTRINGACTIONMANAGERXML_H

#include "abstractmanagerxml.h"

class DefaultStringActionManagerXml : public AbstractManagerXml
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit DefaultStringActionManagerXml(QObject *parent = nullptr);
  ~DefaultStringActionManagerXml() {}
  DefaultStringActionManagerXml(const DefaultStringActionManagerXml&) : AbstractManagerXml() {}
  /*public*/  QDomElement store(QObject *o);
  /*public*/  void setStoreElementClass(QDomElement actions);
  /*public*/  bool load(QDomElement sharedAction, QDomElement perNodeAction);
  /*public*/  void loadActions(QDomElement actions);

 private:
  static Logger* log;
  /*private*/ /*final*/ QMap<QString, Class/*<?>*/*> xmlClasses = QMap<QString, Class/*<?>*/*>();
  /*public*/  int loadOrder()const override;

 protected:
  /*protected*/ void replaceActionManager();

};
Q_DECLARE_METATYPE(DefaultStringActionManagerXml)
#endif // DEFAULTSTRINGACTIONMANAGERXML_H
