#ifndef DEFAULTDIGITALACTIONMANAGERXML_H
#define DEFAULTDIGITALACTIONMANAGERXML_H

#include "abstractmanagerxml.h"
#include <QMainWindow>

class DefaultDigitalActionManagerXml : public AbstractManagerXml
{
 public:
  explicit DefaultDigitalActionManagerXml(QObject *parent = nullptr);
  ~DefaultDigitalActionManagerXml() {}
  DefaultDigitalActionManagerXml(const DefaultDigitalActionManagerXml&) : AbstractManagerXml() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  void setStoreElementClass(QDomElement actions);
  /*public*/  bool load(QDomElement sharedAction, QDomElement perNodeAction)override;
  /*public*/  void loadActions(QDomElement actions);
  /*public*/  int loadOrder() const override;

 private:
  static Logger* log;
  /*private*/ /*final*/QMap<QString, Class/*<?>*/*> xmlClasses = QMap<QString, Class/*<?>*/*>();

 protected:
  /*protected*/ void replaceActionManager();

};
Q_DECLARE_METATYPE(DefaultDigitalActionManagerXml)
#endif // DEFAULTDIGITALACTIONMANAGERXML_H
