#ifndef IMPORTLOGIX_H
#define IMPORTLOGIX_H

#include <QObject>

class Logger;
class Logix;
class LogixNG;
class ImportLogix : public QObject
{
  Q_OBJECT
 public:
  explicit ImportLogix(Logix* logix, QObject *parent = nullptr);
  /*public*/  ImportLogix(Logix* logix, bool allowSystemImport, QObject* parent=nullptr);
  /*public*/  ImportLogix(Logix* logix, bool allowSystemImport, bool dryRun, QObject* parent=nullptr);
  /*public*/  void doImport() /*throws JmriException*/;
  /*public*/  LogixNG* getLogixNG();

 signals:

 private:
  static Logger* log;
  /*private*/ /*final*/ Logix* _logix;
  /*private*/ /*final*/ LogixNG* _logixNG;
  /*private*/ /*final*/ bool _dryRun;
  void common(Logix* logix, bool allowSystemImport, bool dryRun = false);
};

#endif // IMPORTLOGIX_H
