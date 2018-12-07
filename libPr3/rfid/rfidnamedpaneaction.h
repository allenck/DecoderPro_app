#ifndef RFIDNAMEDPANEACTION_H
#define RFIDNAMEDPANEACTION_H
#include "jmrinamedpaneaction.h"

class RfidSystemConnectionMemo;
class RfidNamedPaneAction : public JmriNamedPaneAction
{
public:
 /*public*/ RfidNamedPaneAction(QString s, WindowInterface* wi, QString paneClass, RfidSystemConnectionMemo* memo);
 /*public*/ RfidNamedPaneAction(QString s, QIcon i, WindowInterface* wi, QString paneClass, RfidSystemConnectionMemo* memo);
 /*public*/ JmriPanel* makePanel();

private:
 static Logger* log;
 RfidSystemConnectionMemo* memo;

};

#endif // RFIDNAMEDPANEACTION_H
