#include "blockbossaction.h"
#include "instancemanager.h"
#include "signalheadmanager.h"
#include "blockbossframe.h"

//BlockBossAction::BlockBossAction(QObject *parent) :
//  AbstractAction(parent)
//{
//}
/**
 * Swing action to create and show a "Simple Signal Logic" GUI panel.
 *
 * @author	Bob Jacobsen Copyright (C) 2003
 * @version $Revision: 28746 $
 */
///*public*/ class BlockBossAction extends AbstractAction {

/**
 *
 */
///*private*/ static final long serialVersionUID = 1838689834093701766L;

/*public*/ BlockBossAction::BlockBossAction(QString s, QObject *parent) :
    AbstractAction(s, parent)
{
 //super(s);
 // disable ourself if there is no primary Signal Head manager available
 if (InstanceManager::getNullableDefault("SignalHeadManager") == NULL) {
     setEnabled(false);
 }
 common();
}
void BlockBossAction::common()
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ BlockBossAction::BlockBossAction(QObject *parent) :
    AbstractAction(tr("Simple Signal Logic"), parent)
{
 //this(java.util.ResourceBundle.getBundle("jmri.jmrit.blockboss.BlockBossBundle").getString("Simple_Signal_Logic"));
 common();
}

/*public*/ void BlockBossAction::actionPerformed(JActionEvent* /*e*/)
{
 // create the frame
 JFrame* f = new BlockBossFrame();
 f->setVisible(true);
}
