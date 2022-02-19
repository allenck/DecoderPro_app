#ifndef DEFAULTDIGITALBOOLEANACTIONMANAGERXML_H
#define DEFAULTDIGITALBOOLEANACTIONMANAGERXML_H

#include "abstractmanagerxml.h"

class DefaultDigitalBooleanActionManagerXml : public AbstractManagerXml
{
  Q_OBJECT
 public:
  explicit DefaultDigitalBooleanActionManagerXml(QObject *parent = nullptr);
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  void setStoreElementClass(QDomElement actions);
  /*public*/  bool load(QDomElement sharedAction, QDomElement perNodeAction)override;
  /*public*/  void loadActions(QDomElement actions);

  /*public*/  int loadOrder()const override;

 private:
  static Logger* log;
 private:
  /*private*/ /*final*/ QMap<QString, Class/*<?>*/*> xmlClasses = QMap<QString, Class/*<?>*/*>();

 protected:
  /*protected*/ void replaceActionManager();

};

#endif // DEFAULTDIGITALBOOLEANACTIONMANAGERXML_H
