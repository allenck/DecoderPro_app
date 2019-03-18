#ifndef JMRICLIENTPORTCONTROLLER_H
#define JMRICLIENTPORTCONTROLLER_H
#include "abstractnetworkportcontroller.h"

class JMRIClientSystemConnectionMemo;
class JMRIClientPortController : public AbstractNetworkPortController
{
public:
// JMRIClientPortController();
 /*public*/ SystemConnectionMemo* getSystemConnectionMemo();

protected:
 /*protected*/ JMRIClientPortController(JMRIClientSystemConnectionMemo* connectionMemo);
 /*protected*/ void resetupConnection();

};

#endif // JMRICLIENTPORTCONTROLLER_H
