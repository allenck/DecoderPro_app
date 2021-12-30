#ifndef ACELAADDRESS_H
#define ACELAADDRESS_H

#include <QObject>
#include "manager.h"

class AcelaNode;
class Logger;
class AcelaSystemConnectionMemo;
class AcelaAddress : public QObject
{
  Q_OBJECT
 public:
  explicit AcelaAddress(QObject *parent = nullptr);
  /*public*/  static int getNodeAddressFromSystemName(QString systemName, AcelaSystemConnectionMemo* memo);
  /*public*/  static AcelaNode* getNodeFromSystemName(QString systemName, AcelaSystemConnectionMemo* memo);
  /*public*/  static int getBitFromSystemName(QString systemName, QString prefix);
  /*public*/  static Manager::NameValidity validSystemNameFormat(/*@Nonnull*/ QString systemName, QChar type, QString prefix);
  /*public*/  static bool validSystemNameConfig(QString systemName, QChar type, AcelaSystemConnectionMemo* memo);
  /*public*/  static bool validSystemNameConfig(QString systemName, AcelaSystemConnectionMemo* memo);
  /*public*/  static QString convertSystemNameToAlternate(QString systemName, QString prefix);
  /*public*/  static QString normalizeSystemName(QString systemName, QString prefix);
  /*public*/  static QString makeSystemName(QString type, int nAddress, int bitNum, AcelaSystemConnectionMemo* memo);
  /*public*/  static QString getUserNameFromSystemName(QString systemName, QString prefix);
 signals:

 private:
  static Logger* log;
  static /*final*/ int MINSENSORADDRESS;// = 0;
  static /*final*/ int MAXSENSORADDRESS;// = AcelaNode.MAXSENSORBITS * AcelaNode.MAXNODE -1;
  static /*final*/ int MINOUTPUTADDRESS;// = 0;
  static /*final*/ int MAXOUTPUTADDRESS;// = AcelaNode.MAXOUTPUTBITS * AcelaNode.MAXNODE -1;

};

#endif // ACELAADDRESS_H
