#ifndef DEFAULTANALOGACTIONMANAGERXML_H
#define DEFAULTANALOGACTIONMANAGERXML_H

#include "abstractmanagerxml.h"
#include <QMainWindow>

class DefaultAnalogActionManagerXml : public AbstractManagerXml
{
  Q_OBJECT

 public:
  explicit DefaultAnalogActionManagerXml(QObject *parent = nullptr);
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



#endif // DEFAULTANALOGACTIONMANAGERXML_H
