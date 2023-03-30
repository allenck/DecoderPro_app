#ifndef DEFAULTFEMALEDIGITALEXPRESSIONSOCKET_H
#define DEFAULTFEMALEDIGITALEXPRESSIONSOCKET_H

#include "abstractfemalesocket.h"
#include "femaledigitalexpressionsocket.h"

class DefaultFemaleDigitalExpressionSocket : public AbstractFemaleSocket, public FemaleDigitalExpressionSocket
{
  Q_OBJECT
  Q_INTERFACES(FemaleDigitalExpressionSocket)
 public:
  DefaultFemaleDigitalExpressionSocket(Base* parent, FemaleSocketListener* listener, QString name, QObject* parentObj = nullptr);
  /*public*/  bool isCompatible(MaleSocket* socket)override;
  /*public*/  bool evaluate() /*throws JmriException*/override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale) override;
  /*public*/  QHash<Category, QList</*Class<? extends Base>*/QString>> getConnectableClasses()override;
  /*public*/  void disposeMe()override;
  /*public*/  QString getClassName() override {return "jmri.jmrit.logixng.implementation.DefaultFemaleDigitalExpressionSocket";}
  /*public*/ QString getClass()const override {return "jmri.jmrit.logixng.implementation.DefaultFemaleDigitalExpressionSocket";}

  QObject* bself() override{return (QObject*)this;}

  /*public*/ /*default*/ virtual bool isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper) override {}
  /*public*/  /*default*/ virtual void doSocketOperation(int index, FemaleSocketOperation::TYPES oper) override {}
  /*public*/ virtual QString toString() override {return getLongDescription(QLocale());}

};

#endif // DEFAULTFEMALEDIGITALEXPRESSIONSOCKET_H
