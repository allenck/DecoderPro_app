#ifndef DEFAULTANALOGEXPRESSIONMANAGERXML_H
#define DEFAULTANALOGEXPRESSIONMANAGERXML_H
#include "abstractmanagerxml.h"
#include "threadingutil.h"

class DefaultAnalogExpressionManagerXml : public AbstractManagerXml
{
  Q_OBJECT
 public:
  DefaultAnalogExpressionManagerXml(QObject* parent = nullptr);
  ~DefaultAnalogExpressionManagerXml() {}
  DefaultAnalogExpressionManagerXml(const DefaultAnalogExpressionManagerXml&) : AbstractManagerXml() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  void setStoreElementClass(QDomElement expressions);
  /*public*/  bool load(QDomElement sharedExpression, QDomElement perNodeExpression)override;
  /*public*/  void loadExpressions(QDomElement expressions);
  /*public*/  int loadOrder() const override;

 private:
  static Logger* log;
 protected:    /*protected*/ void replaceExpressionManager();

};
Q_DECLARE_METATYPE(DefaultAnalogExpressionManagerXml)

class DAEMRun : public ThreadAction
{
  Q_OBJECT
 public:
  DAEMRun() : ThreadAction() {}
 public slots:
  void run();
};
#endif // DEFAULTANALOGEXPRESSIONMANAGERXML_H
