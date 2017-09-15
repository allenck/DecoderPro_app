#include "serveraction.h"
#include "server.h"
#include "serverframe.h"

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

/*public*/ ServerAction::ServerAction(QString s, QObject *parent) :
 QAction(s, parent)
{
 //super(s);
 // Get a server instance to cause the config to be read and the server
 // started if necessary
 Server::getInstance();
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ ServerAction::ServerAction(QObject *parent) :
  QAction("LocoNetOverTcp Server", parent)
{
 //this("LocoNetOverTcp Server");
 // Get a server instance to cause the config to be read and the server
 // started if necessary
 Server::getInstance();
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ void ServerAction::actionPerformed(ActionEvent* /*e*/)
{
 ServerFrame* f = ServerFrame::getInstance();
 f->setVisible(true);
}
