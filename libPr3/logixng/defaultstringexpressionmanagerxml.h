#ifndef DEFAULTSTRINGEXPRESSIONMANAGERXML_H
#define DEFAULTSTRINGEXPRESSIONMANAGERXML_H

#include "abstractmanagerxml.h"
#include "threadingutil.h"
class DefaultStringExpressionManagerXml : public AbstractManagerXml
{
  Q_OBJECT
 public:
  explicit DefaultStringExpressionManagerXml(QObject *parent = nullptr);
  ~DefaultStringExpressionManagerXml(){}
  DefaultStringExpressionManagerXml(const DefaultStringExpressionManagerXml&) : AbstractManagerXml() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  void setStoreElementClass(QDomElement expressions);
  /*public*/  bool load(QDomElement sharedExpression, QDomElement perNodeExpression)override;
  /*public*/  void loadExpressions(QDomElement expressions);
  /*public*/  int loadOrder()const override;

 private:
  static Logger* log;
  /*private*/ /*final*/ QMap<QString, Class/*<?>*/*> xmlClasses = QMap<QString, Class/*<?>*/*>();

 protected:
  /*protected*/ void replaceExpressionManager();

};
Q_DECLARE_METATYPE(DefaultStringExpressionManagerXml)

class DSEMRun : public ThreadAction
{
  Q_OBJECT
 public:
  DSEMRun() {}
 public slots:
  void run();

};
#endif // DEFAULTSTRINGEXPRESSIONMANAGERXML_H
