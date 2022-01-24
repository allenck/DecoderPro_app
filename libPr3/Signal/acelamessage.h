#ifndef ACELAMESSAGE_H
#define ACELAMESSAGE_H
#include "abstractmrmessage.h"

class AcelaMessage : public AbstractMRMessage
{
  Q_OBJECT
 public:
  AcelaMessage(QObject* parent = nullptr);
  /*final*/ static const int POLL_TIMEOUT = 250;
  /*public*/ AcelaMessage(int i, QObject* parent = nullptr);
  /*public*/ AcelaMessage(AcelaMessage* m, QObject* parent=nullptr);
  /*public*/ AcelaMessage(QString m, QObject* parent=nullptr);
  /*public*/ QString toString()override;
  static /*public*/ AcelaMessage* getAcelaVersionMsg();
  static /*public*/ AcelaMessage* getAcelaResetMsg();
  static /*public*/ AcelaMessage* getAcelaOnlineMsg();
  static /*public*/ AcelaMessage* getAcelaPollNodesMsg();
  static /*public*/ AcelaMessage* getAcelaPollSensorsMsg();
  static /*public*/ AcelaMessage* getAcelaConfigSensorMsg();

};
#endif // ACELAMESSAGE_H
