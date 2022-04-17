#ifndef DEFAULTANALOGACTIONMANAGERXML_H
#define DEFAULTANALOGACTIONMANAGERXML_H

#include "abstractmanagerxml.h"
#include <QMainWindow>

class DefaultAnalogActionManagerXml : public AbstractManagerXml
{
  Q_OBJECT

 public:
  Q_INVOKABLE explicit DefaultAnalogActionManagerXml(QObject *parent = nullptr);
  ~DefaultAnalogActionManagerXml() {}
  DefaultAnalogActionManagerXml(const DefaultAnalogActionManagerXml&) : AbstractManagerXml(){}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  void setStoreElementClass(QDomElement actions);
  /*public*/  void loadActions(QDomElement actions);
  /*public*/ bool load(QDomElement sharedAction, QDomElement perNodeAction)override;
  /*public*/  int loadOrder() const override;

 private:
  static Logger* log;
  /*private*/ /*final*/ QMap<QString, Class/*<?>*/*> xmlClasses = QMap<QString, Class/*<?>*/*>();

 protected:
  /*protected*/ void replaceActionManager();

};
Q_DECLARE_METATYPE(DefaultAnalogActionManagerXml)
#endif // DEFAULTANALOGACTIONMANAGERXML_H
