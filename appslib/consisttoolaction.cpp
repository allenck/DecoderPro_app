#include "consisttoolaction.h"
#include "windowinterface.h"
#include "instancemanager.h"
#include "jmripanel.h"
#include "consisttoolframe.h"

//ConsistToolAction::ConsistToolAction(QObject *parent) :
//  QAction(parent)
//{
//}
/**
 * Swing action to create and register a ConsistToolFrame object
 *
 * @author Paul Bender Copyright (C) 2003
 * @version $Revision: 28746 $
 */
// /*public*/ class ConsistToolAction extends JmriAbstractAction {

/**
 *
 */
//private static final long serialVersionUID = -2206396348711181432L;

/*public*/ ConsistToolAction::ConsistToolAction(QString s, WindowInterface* wi) :
  JmriAbstractAction(s, wi)
{
 //super(s, wi);
 common();
}
void ConsistToolAction::common()
{
    // disable ourself if there is no consist manager available
 if (InstanceManager::getDefault("ConsistManager") == NULL) {
        setEnabled(false);
    }
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ ConsistToolAction::ConsistToolAction(QString s, QIcon i, WindowInterface* wi)
 : JmriAbstractAction(s, i, wi)
{
 //super(s, i, wi);
 common();
}

/*public*/ ConsistToolAction::ConsistToolAction(QString s, QObject *parent) :
  JmriAbstractAction(s, parent) {
 //super(s);
 common();
}

/*public*/ ConsistToolAction::ConsistToolAction(QObject *parent) :
  JmriAbstractAction(tr("Consist Tool"),parent) {
    //this("Consist Tool");
 common();
}

/*public*/ void ConsistToolAction::actionPerformed(ActionEvent* e) {
    ConsistToolFrame* f = new ConsistToolFrame();
    f->setVisible(true);
}

// never invoked, because we overrode actionPerformed above
/*public*/ JmriPanel* ConsistToolAction::makePanel() {
    throw new IllegalArgumentException("Should not be invoked");
}
