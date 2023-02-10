#ifndef DEBUGGERMALEANALOGEXPRESSIONSOCKETFACTORY_H
#define DEBUGGERMALEANALOGEXPRESSIONSOCKETFACTORY_H

#include <QObject>
#include "maleanalogexpressionsocketfactory.h"
#include "abstractmalesocket.h"


class DebuggerMaleAnalogExpressionSocketFactory : public QObject, public MaleAnalogExpressionSocketFactory
{
  Q_OBJECT
  Q_INTERFACES(MaleAnalogExpressionSocketFactory)
 public:
  explicit DebuggerMaleAnalogExpressionSocketFactory(QObject *parent = nullptr) : QObject(parent){}
  /*public*/ AbstractMaleSocket *encapsulateMaleSocket(BaseManager/*<MaleAnalogExpressionSocket>*/* manager, AbstractMaleSocket *maleSocket) override;

  QObject* self() override {return (QObject*)this;}
 signals:

};

#endif // DEBUGGERMALEANALOGEXPRESSIONSOCKETFACTORY_H
