#include "lntcpserveraction.h"
#include "lntcpserver.h"
#include "lntcpserverframe.h"

//ServerAction::ServerAction(QObject *parent) :
//  QAction(parent)
//{
//}
/**
 * Implementation of the LocoNetOverTcp LbServer Server Protocol
 *
 * @author Alex Shepherd Copyright (C) 2006
 * @version	$Revision: 28746 $
 */
// /*public*/ class ServerAction
//        extends AbstractAction {

/**
 *
 */
//private static final long serialVersionUID = -7774780042559216689L;

/*public*/ LnTcpServerAction::LnTcpServerAction(QString s, QObject *parent) :
 AbstractAction(s, parent)
{
 //super(s);
 // Get a server instance to cause the config to be read and the server
 // started if necessary
 LnTcpServer::getDefault();
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ LnTcpServerAction::LnTcpServerAction(QObject *parent) :
  AbstractAction("LocoNetOverTcp Server", parent)
{
 //this("LocoNetOverTcp Server");
 // Get a server instance to cause the config to be read and the server
 // started if necessary
 LnTcpServer::getDefault();
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ void LnTcpServerAction::actionPerformed(JActionEvent * /*e*/)
{
 LnTcpServer::getDefault()->enable();
 LnTcpServerFrame::getDefault()->setVisible(true);
}
