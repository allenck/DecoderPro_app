#ifndef IMPORTCONDITIONAL_H
#define IMPORTCONDITIONAL_H

#include <QObject>

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

};

#endif // IMPORTCONDITIONAL_H
