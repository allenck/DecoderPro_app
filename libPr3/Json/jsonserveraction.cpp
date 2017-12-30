#include "jsonserveraction.h"
#include "jsonserver.h"

///*public*/ class JsonServerAction extends AbstractAction {

/*public*/ JsonServerAction::JsonServerAction(QString s, QObject* parent) : AbstractAction(s, parent) {
    //super(s);
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ JsonServerAction::JsonServerAction(QObject* parent) : AbstractAction("Start Json Server", parent){
    //this(Bundle.getMessage("MenuItemStartServer"));
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

//@Override
/*public*/ void JsonServerAction::actionPerformed(ActionEvent* e) {
    JsonServer::getDefault()->start();
}
