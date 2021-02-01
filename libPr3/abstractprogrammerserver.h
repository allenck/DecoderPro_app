#ifndef ABSTRACTPROGRAMMERSERVER_H
#define ABSTRACTPROGRAMMERSERVER_H

#include <QObject>
#include "programmer.h"

class Logger;
class AbstractProgrammerServer : public QObject, public ProgListener
{
  Q_OBJECT
  Q_INTERFACES(ProgListener)
 public:
  explicit AbstractProgrammerServer(QObject *parent = nullptr);
  /*abstract*/ virtual /*public*/ void sendStatus(int CV, int value, int status) throw (IOException) =0;
  /*abstract*/ virtual /*public*/ void sendNotAvailableStatus() throw (IOException) =0;
  /*abstract*/ virtual /*public*/ void parseRequest(QString statusString) throw (JmriException, IOException) = 0;
  /*public*/ void writeCV(ProgrammingMode* mode, int CV, int value);
  /*public*/ void readCV(ProgrammingMode* mode, int CV);
  /*public*/ void programmingOpReply(int value, int status) override;
  /*public*/ void dispose();

 signals:

 public slots:

 private:
  /*private*/ Programmer* p = nullptr;
  static Logger* log;

 protected:
  /*protected*/ int lastCV = -1;
  /*protected*/ Programmer* getProgrammer(QObject *parent);

};

#endif // ABSTRACTPROGRAMMERSERVER_H
