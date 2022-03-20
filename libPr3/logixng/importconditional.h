#ifndef IMPORTCONDITIONAL_H
#define IMPORTCONDITIONAL_H

#include <QObject>

class DigitalActionBean;
class Memory;
class Light;
class AtomicBoolean;
class Sensor;
class Turnout;
class DigitalBooleanActionBean;
class ConditionalAction;
class DigitalBooleanMany;
class ConditionalVariable;
class DigitalExpressionBean;
class Logix;
class LogixNG;
class Logger;
class Conditional;
class ConditionalNG;
class ImportConditional : public QObject
{
  Q_OBJECT
 public:
  explicit ImportConditional(
    Logix* logix,
    Conditional* conditional,
    LogixNG* logixNG,
    QString sysName,
    bool dryRun, QObject *parent = nullptr);
  /*public*/  ConditionalNG* getConditionalNG();
  /*public*/  void doImport() /*throws SocketAlreadyConnectedException, JmriException*/ ;

 signals:

 private:
  static Logger* log;
  /*private*/ /*final*/ Conditional* _conditional;
  /*private*/ /*final*/ ConditionalNG* _conditionalNG;
  /*private*/ /*final*/ bool _dryRun;
  /*private*/ void buildExpression(DigitalExpressionBean* expression, QList<ConditionalVariable *> *conditionalVariables);
  /*private*/ void buildAction(DigitalBooleanMany* many, QList<ConditionalAction *> *conditionalActions);
  /*private*/ void buildAction(DigitalBooleanActionBean* action, ConditionalAction* conditionalAction);
  /*private*/ DigitalExpressionBean* getSensorExpression(
          /*@Nonnull*/ ConditionalVariable* cv,
          Sensor* sn,
          AtomicBoolean* isNegated)
          /*throws JmriException*/;
  /*private*/ DigitalExpressionBean* getTurnoutExpression(
          /*@Nonnull*/ ConditionalVariable* cv,
          Turnout* tn,
          AtomicBoolean* isNegated)
          /*throws JmriException*/;
  /*private*/ DigitalExpressionBean* getMemoryExpression(
          /*@Nonnull*/ ConditionalVariable* cv, Memory* my)
          /*throws JmriException*/;

  /*private*/ DigitalActionBean* getSensorAction(/*@Nonnull*/ ConditionalAction* ca, Sensor* sn, QString reference)/* throws JmriException*/;
  /*private*/ DigitalActionBean* getTurnoutAction(/*@Nonnull*/ ConditionalAction* ca, Turnout* tn, QString reference) /*throws JmriException*/;
  /*private*/ DigitalActionBean* getMemoryAction(/*@Nonnull*/ ConditionalAction* ca, Memory* my, QString reference) /*throws JmriException */;

};

#endif // IMPORTCONDITIONAL_H
