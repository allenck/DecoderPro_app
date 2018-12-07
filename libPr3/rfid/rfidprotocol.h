#ifndef RFIDPROTOCOL_H
#define RFIDPROTOCOL_H
#include <QObject>

class Logger;
class AbstractMRReply;
class RfidProtocol : public QObject
{
  Q_OBJECT
 public:
  /*public*/ RfidProtocol(QObject* parent = nullptr);
  /*public*/ RfidProtocol(QChar concentratorFirst, QChar concentratorLast, int portPosition, QObject* parent = nullptr);
  /*public*/ QString getTag(AbstractMRReply* msg);
 /*public*/ bool providesChecksum();
  virtual /*abstract*/ /*public*/ QString getCheckSum(AbstractMRReply* msg);
  virtual /*abstract*/ /*public*/ bool isValid(AbstractMRReply* msg);
  virtual /*abstract*/ /*public*/ bool endOfMessage(AbstractMRReply* msg);
  virtual /*abstract*/ /*public*/ QString initString();
 /*public*/ QChar getReaderPort(AbstractMRReply* msg);
 /*public*/ QString toMonitorString(AbstractMRReply* msg);

 private:
  void common(QChar concentratorFirst, QChar concentratorLast, int portPosition);
  static Logger* log;
  /*private*/ static /*final*/ QByteArray hexCodes;// = QByteArray['f' + 1];
  /*private*/ static int charToNibble(char c);

 protected:
    /*protected*/ bool isConcentrator;
    /*protected*/ QChar concentratorFirst;
    /*protected*/ QChar concentratorLast;
    /*protected*/ int portPosition;
  /*protected*/ static QByteArray convertHexString(QString s);


};

#endif // RFIDPROTOCOL_H
