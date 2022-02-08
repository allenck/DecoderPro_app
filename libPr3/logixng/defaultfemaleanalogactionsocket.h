#ifndef DEFAULTFEMALEANALOGACTIONSOCKET_H
#define DEFAULTFEMALEANALOGACTIONSOCKET_H

#include "abstractfemalesocket.h"
#include "femaleanalogactionsocket.h"
#include <QObject>

class Base;
class FemaleSocketListener;
class DefaultFemaleAnalogActionSocket : public AbstractFemaleSocket, public FemaleAnalogActionSocket
{
//  /home/allen/Projects/DecoderPro/fossil/DecoderPro_app/libPr3/logixng/defaultfemaleanalogactionsocketfactory.h:34: error: ambiguous conversion from derived class 'DefaultFemaleAnalogActionSocket' to base class 'FemaleSocket':
//      class DefaultFemaleAnalogActionSocket -> class AbstractFemaleSocket -> class FemaleSocket
//      class DefaultFemaleAnalogActionSocket -> class FemaleAnalogActionSocket -> class FemaleSocket

  Q_OBJECT
  Q_INTERFACES(FemaleAnalogActionSocket)
 public:
  /*public*/  DefaultFemaleAnalogActionSocket(Base* parentObject, FemaleSocketListener* listener, QString name, QObject* parent= nullptr);
  /*public*/  bool isCompatible(MaleSocket* socket)override;
  /*public*/  QMap<Category*, QList</*Class<? extends Base>*/Base*>> getConnectableClasses()override;
  /*public*/  void setValue(double value) /*throws JmriException*/override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void disposeMe()override;

  QObject* self() override {return (QObject*)this;}
  QString getUserName() const override {return AbstractFemaleSocket::getUserName();}
  /*public*/ void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl) override
  {
   AbstractFemaleSocket::getUsageDetail(level, bean, report, cdl);
  }
};

#endif // DEFAULTFEMALEANALOGACTIONSOCKET_H
